// ActionMonitor.cpp — 被动内存监控 DLL（v3：纯内存轮询，不改写任何游戏代码）。
//
// 用途：注入到 kards-Win64-Shipping.exe 后，独立线程按固定间隔（默认 5ms）只读
// AMatchControllerV2 实例上几个已确认字段（CurrentActionId、Counter3228、轮询状态、
// ping 标志、上次轮询时间），值变化才写日志，带真实墙钟时间戳。不调用任何游戏函数、
// 不修改任何游戏行为、不伪造/篡改任何要提交给服务端的数据。
//
// === 早期版本（inline hook）为什么被放弃 ===
// 早期版本尝试用 inline hook（改写目标函数开头 14 字节为跳转指令）实现，实测导致
// 游戏崩溃。用 IDA 反汇编确认了两个具体根因：
//   1. 部分目标函数（如 ping 标志置位函数、CurrentActionId 的 getter）本身只有
//      8 字节，14 字节的 patch 会砸进紧邻它的下一个函数开头，永久破坏那个函数的
//      机器码。
//   2. 另一个目标函数（MatchActionsPollLoop_Impl）开头就是一条短跳转，跳转目标
//      恰好落在 14 字节 patch 区域内部，导致分支被走到时执行到跳板中间的垃圾字节。
// 两次事故的教训是同一个：靠人工读几条反汇编去判断"这个函数开头能不能安全覆写
// 14 字节"不可靠。与其继续给 inline-hook 打补丁，不如换一个根本不改写任何游戏
// 代码的方案——纯读内存。
//
// === 当前方案：用 GObjects 反射数组直接定位运行中的 AMatchControllerV2 实例 ===
// Unreal Engine 的全局 UObject 反射数组（GObjects，TUObjectArray 布局）里，每个
// AMatchControllerV2 实例头 8 字节都是同一个类虚表指针——用它扫一遍，就能找到
// 运行中唯一的那个实例，不需要调用任何游戏函数、不需要改写任何一个字节的游戏代码。
// GObjects 的运行时地址、AMatchControllerV2 的虚表地址，以及下面用到的字段偏移
// （CurrentActionId=+3224、Counter3228=+3228、pollState=+3081、
// shouldPollActions=+3476/0xD94、triggerPollActions=+3477/0xD95、
// lastPollTime=+3160），均已用运行时反射转储和反汇编交叉确认，完整推导过程见
// evidence/CurrentActionId-increment-logic.md。
//
// 已知局限：
//   - 轮询有粒度（下面默认每 5ms 采一次），不是"事件发生的那一纳秒"，但相对于
//     本报告目前关心的"秒级到十秒级"轮询节奏问题，这个精度损失可以接受。
//   - 看不到具体动作类型字符串（友方还是敌方打了什么牌）——只看得到
//     CurrentActionId/Counter3228 这些聚合计数器的变化。要拿动作类型明细，需要配合
//     解密后的网络抓包（按提交计数 Counter3228 对齐时间戳）一起看。
//
// 编译：需要 MSVC（`cl /LD /EHa /std:c++17 /O2 ActionMonitor.cpp /link /OUT:ActionMonitor.dll`）。
// 注入：任意标准的 LoadLibrary 式 DLL 注入方式均可，本文件不含注入器代码。

#include <windows.h>
#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include <mutex>
#include <chrono>
#include <thread>

static constexpr uintptr_t IDA_IMAGE_BASE = 0x140000000ULL;

// RVA：GObjects（UE 全局 UObject 反射数组，TUObjectArray*）的运行时反射转储确认地址。
static constexpr uintptr_t RVA_GObjects           = 0x091F4060ULL;
// RVA：AMatchControllerV2 虚表指针（反编译该类原生构造函数时确认：*(QWORD*)a1 = VFT）。
static constexpr uintptr_t RVA_MatchControllerVFT = 0x147E20858ULL - IDA_IMAGE_BASE;

// AMatchControllerV2 字段偏移。CurrentActionId/Counter3228/pollState/lastPollTime
// 是纯原生字段（非 UPROPERTY，反射转储里看不到），来自反汇编直接读出的裸偏移；
// shouldPollActions/triggerPollActions 是反射转储确认的真实偏移和真实字段名。
static constexpr int OFF_CurrentActionId    = 3224; // 0xC98
static constexpr int OFF_Counter3228        = 3228; // 0xC9C
static constexpr int OFF_PollState          = 3081; // 0xC09
static constexpr int OFF_LastPollTime       = 3160; // 0xC58
static constexpr int OFF_ShouldPollActions  = 3476; // 0xD94
static constexpr int OFF_TriggerPollActions = 3477; // 0xD95

// ---- TUObjectArray（UE 标准布局，NOT AUTO-GENERATED PROPERTY 的原生字段）----
struct FUObjectItem { void* Object; uint8_t _pad[0x10]; }; // 0x18 字节/项，Object 在 +0
struct TUObjectArray
{
    FUObjectItem** Objects;   // +0x00
    uint8_t _pad8[0x8];       // +0x08
    int32_t MaxElements;      // +0x10
    int32_t NumElements;      // +0x14
    int32_t MaxChunks;        // +0x18
    int32_t NumChunks;        // +0x1C

    void* GetByIndex(int32_t index) const
    {
        constexpr int32_t kElementsPerChunk = 0x10000;
        int32_t chunkIndex = index / kElementsPerChunk;
        int32_t inChunkIdx = index % kElementsPerChunk;
        if (index < 0 || chunkIndex >= NumChunks || index >= NumElements) return nullptr;
        FUObjectItem* chunkPtr = Objects[chunkIndex];
        if (!chunkPtr) return nullptr;
        return chunkPtr[inChunkIdx].Object;
    }
};

static std::mutex g_logMutex;
static FILE* g_logFile = nullptr;

// Unix epoch 秒（带微秒），不是相对注入时刻的秒表读数——这样才能跟同时抓取的解密网络
// 报文日志（时间戳同样取自墙钟）按时间戳直接对齐，不需要额外记录"注入时刻的墙钟时间"
// 再手动换算相对秒表。
static double NowSeconds()
{
    using namespace std::chrono;
    return duration<double>(system_clock::now().time_since_epoch()).count();
}

static void LogLine(const char* fmt, ...)
{
    std::lock_guard<std::mutex> lock(g_logMutex);
    if (!g_logFile) return;
    fprintf(g_logFile, "[%.6f] ", NowSeconds());
    va_list args;
    va_start(args, fmt);
    vfprintf(g_logFile, fmt, args);
    va_end(args);
    fprintf(g_logFile, "\n");
    fflush(g_logFile);
}

// UObject 标准头部布局（UE4.20+/UE5.x 通用）：
// +0x00 vtable, +0x08 EObjectFlags ObjectFlags（4 字节）, +0x0C InternalIndex, +0x10 ClassPrivate...
// RF_ClassDefaultObject = 0x10。
static constexpr int OFF_UObject_ObjectFlags = 0x08;
static constexpr uint32_t RF_ClassDefaultObject = 0x10;

// 在 GObjects 里找第一个虚表指针等于 AMatchControllerV2 虚表、且不是 CDO（类默认对象）
// 的实例。CDO 是每个类在引擎启动时就创建好的模板对象，永远不会有真实对局数据（字段
// 全是默认零值），且通常比真实对局实例注册得更早、排在数组更靠前的位置——不排除它
// 的话，扫描第一次命中的基本必然是 CDO，读出来的字段会全程停在 0。
// 只读内存，不调用任何游戏函数，不改写任何字节。
static void* FindMatchController(uintptr_t base)
{
    TUObjectArray* gObjects = reinterpret_cast<TUObjectArray*>(base + RVA_GObjects);
    void* vft = reinterpret_cast<void*>(base + RVA_MatchControllerVFT);

    __try {
        int32_t num = gObjects->NumElements;
        for (int32_t i = 0; i < num; ++i) {
            void* obj = gObjects->GetByIndex(i);
            if (!obj) continue;
            void* objVft = *reinterpret_cast<void**>(obj); // UObject 头 8 字节就是虚表指针
            if (objVft != vft) continue;
            uint32_t flags = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(obj) + OFF_UObject_ObjectFlags);
            if (flags & RF_ClassDefaultObject) continue; // 跳过 CDO，继续找真实实例
            return obj;
        }
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        LogLine("FindMatchController: access violation while scanning GObjects (num=%d), aborting this scan.",
                 gObjects->NumElements);
        return nullptr;
    }
    return nullptr;
}

struct Snapshot
{
    uint32_t currentActionId = 0xFFFFFFFF;
    uint32_t counter3228 = 0xFFFFFFFF;
    uint8_t pollState = 0xFF;
    uint8_t shouldPoll = 0xFF;
    uint8_t triggerPoll = 0xFF;
    double lastPollTime = -1.0;
    bool valid = false;
};

static bool ReadSnapshot(void* mc, Snapshot& out)
{
    uint8_t* base = reinterpret_cast<uint8_t*>(mc);
    __try {
        out.currentActionId = *reinterpret_cast<uint32_t*>(base + OFF_CurrentActionId);
        out.counter3228     = *reinterpret_cast<uint32_t*>(base + OFF_Counter3228);
        out.pollState        = *(base + OFF_PollState);
        out.shouldPoll        = *(base + OFF_ShouldPollActions);
        out.triggerPoll       = *(base + OFF_TriggerPollActions);
        out.lastPollTime      = *reinterpret_cast<double*>(base + OFF_LastPollTime);
        out.valid = true;
        return true;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

static void PollThreadProc()
{
    HMODULE mod = GetModuleHandleA(nullptr);
    if (!mod) { LogLine("FATAL: GetModuleHandle(NULL) failed"); return; }
    uintptr_t base = reinterpret_cast<uintptr_t>(mod);
    LogLine("Module base = 0x%llx", (unsigned long long)base);

    void* mc = nullptr;
    Snapshot last;
    double lastRescan = 0.0;

    for (;;) {
        double now = NowSeconds();

        if (!mc || now - lastRescan > 2.0) {
            void* found = FindMatchController(base);
            if (found && found != mc) {
                LogLine("MatchControllerV2 instance found/changed: this=%p", found);
                mc = found;
                last = Snapshot{};
            } else if (!found) {
                mc = nullptr;
            }
            lastRescan = now;
        }

        if (mc) {
            Snapshot cur;
            if (ReadSnapshot(mc, cur)) {
                if (!last.valid ||
                    cur.currentActionId != last.currentActionId ||
                    cur.counter3228 != last.counter3228 ||
                    cur.pollState != last.pollState ||
                    cur.shouldPoll != last.shouldPoll ||
                    cur.triggerPoll != last.triggerPoll) {
                    LogLine("this=%p CurrentActionId=%u Counter3228=%u pollState=%u shouldPollActions=%u triggerPollActions=%u lastPollTime=%.3f",
                             mc, cur.currentActionId, cur.counter3228, cur.pollState,
                             cur.shouldPoll, cur.triggerPoll, cur.lastPollTime);
                    last = cur;
                }
            } else {
                LogLine("ReadSnapshot failed (access violation), instance likely destroyed, will rescan.");
                mc = nullptr;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

static DWORD WINAPI InitThread(LPVOID)
{
    // 固定绝对路径，不依赖 %TEMP% ——GetTempPathA 是在被注入的目标进程自己的环境里
    // 解析的，如果目标进程的运行环境（启动器/沙盒等）跟查看文件用的 shell 不是同一个
    // 用户态环境，两边看到的 %TEMP% 可能不一样。改成固定路径避免这个问题。
    CreateDirectoryA("C:\\KardsActionMonitor", nullptr); // 已存在也没关系，忽略返回值
    const char* path = "C:\\KardsActionMonitor\\kards_action_monitor.log";
    fopen_s(&g_logFile, path, "a");
    LogLine("=== ActionMonitor v3 attached (pure memory polling, no code hooks), log at %s ===", path);

    PollThreadProc(); // 不返回，常驻轮询
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    }
    return TRUE;
}
