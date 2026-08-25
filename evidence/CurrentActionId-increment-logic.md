# `CurrentActionId`（native, `AMatchControllerV2 + 0xC98`）真实自增逻辑

ReseedImpact.md 最初的分析里，把 `action_id`（本地投机计数器 `GetCurrentActionID()`）描述成"一个从 0 开始、按对局进程单调递增的小整数计数器"，暗示只要知道对局进行到哪一步，就能简单推算出下一个 `action_id`。这个描述**不准确**——经用户指出后用 IDA 核实，记录如下。

## 定位方法

1. `AMatchControllerV2::execGetCurrentActionID`（`0x144a93f20`）→ 调用 `MatchControllerV2_GetCurrentActionID_Impl`（`0x144aec160`），后者是纯 getter：`return *(unsigned int *)(a1 + 3224);`——确认 `CurrentActionId` 字段在原生内存布局里的真实偏移是 `+3224`（即 `0xC98`），跟此前结构体布局分析记录的一致。
2. 用 `search_text` 在 `AMatchControllerV2` 全部原生函数所在的地址段（`0x144a80000`-`0x144b20000`，约 5MB，远小于整个 `.text`，能在超时前扫完）搜索反汇编里出现的 `0C98h` 偏移引用，命中 33 处，分布在十几个不同函数里——包括至少两处 `inc dword ptr [...+0C98h]` 和三处 `mov dword ptr [...+0C98h], 1`，全部集中在 `MatchControllerV2_GetNextAction_Impl`（`0x144af2180`）和几个初始化/重置类函数里。
3. 完整反编译 `MatchControllerV2_GetNextAction_Impl`（对局的动作日志/回合状态机核心函数）确认了这些写入点各自的触发条件。

## 真实逻辑：不是单一的"+1"，是一个依赖动作类型和归属方的状态机

`MatchControllerV2_GetNextAction_Impl` 会在动作日志哈希表（`a1+3240` 起）里查找 `CurrentActionId` 对应的条目，然后：

- 如果查到的动作类型字符串是 `"XActionEndOfTurn"` 且是重复的（`a1+1960` 标记），记一条 `"DUPLICATE END TURN IN MATCH %d action, %d"` 日志，**递归调用自身**，并在递归前把 `CurrentActionId` 加一（`++*(a1+3224)`，地址 `0x144af259d`）——这是第一处自增。
- 走到主处理分支（非重复的正常动作）时，也会把 `CurrentActionId` 加一（`++*(a1+3224)`，地址 `0x144af27eb`）——这是第二处自增，逻辑上跟第一处是"同一件事的两条不同路径"，不是各自独立的两个计数器。
- 只有当这个动作的"所属方"字段（`*(a2+24)`）等于本地缓存的己方 ID（`*(*(a1+3432)+2024)`）时，才会额外递增另一个计数器 `Counter3228`（`a1+3228`，`++*(_DWORD *)(a1+3228)`，地址 `0x144af2909`）——说明存在一个**跟 `CurrentActionId` 平行、但只统计"自己这方"动作数量**的独立计数器，两者不是同一个东西。
- 在动作日志哈希表查不到"下一个 slot"时（`v57 == -1` 分支），会把 `CurrentActionId` **直接重置为 `1`**（`*(a1+3224) = 1`，地址 `0x144af2978`），然后重建/收缩哈希表（`sub_144A91ED0`/`sub_1416B78E0`/`sub_144B02F20`）并调用 `MatchControllerV2_OnActionsEvaluationComplete_Impl`——这看起来是"这一批已知动作全部处理完、准备好接收下一批"的信号，而不是单纯的对局内累计计数器。
- 还有一条独立的"动作 ID 出现空洞"（gap）检测路径：如果日志表里下一条动作的 ID 比 `CurrentActionId` 还大，会记一条 `"RESYNC: gap in action IDs"` 日志并触发 `sub_144A92870`（推测是重新同步请求）。

## 结论（原始版本）：预测 `action_id` 需要复现整套状态机，不是简单计数

原本 ReseedImpact.md 暗示的"`action_id` 是小整数、容易脱离对局历史单独预测"的说法据此被修正为"需要复现整套状态机，工作量跟解析抓包相当"。

## 更正：早期抓包比对用错了字段，需要重新定位到 `CurrentActionId` 本身

早期的"二次更正"曾依据抓包解密出的提交请求 `action_id` 字段（从 1 开始、每次恰好 +1、双方共享同一序列）推翻上面反编译出的状态机描述。这个比对本身依据的字段已经查明是错的：[evidence/two-distinct-action-id-counters.md](two-distinct-action-id-counters.md) 反编译 `MatchController_BuildActionJsonPayload` 后确认，提交请求 JSON 里的 `action_id` 字段来自 `Counter3228`（一个只在本机构造新动作时自增、按归属方过滤的独立字段——即本文件第 17 条列出的"只统计自己这方动作数量"的那个平行计数器），不是本文档反编译的 `CurrentActionId`（`this+3224`）。也就是说，抓包能直接验证的是 `Counter3228` 的行为，不能直接验证 `CurrentActionId` 的行为——上面第 5-19 节反编译出的 `GetNextAction_Impl` 状态机描述（按动作类型/归属方条件递增、查不到下一个 slot 时重置为 1、gap 检测）依然是 `CurrentActionId` 唯一已知的直接代码证据，没有被抓包推翻。

`CurrentActionId` 的语义（本机自计数，还是本机回放合并动作日志的进度指针）目前唯一的直接证据就是本文件反编译出的这套状态机本身：第 18 条"哈希表查不到下一个 slot 时重置为 1，随后重建/收缩哈希表"的行为，比"简单自增计数器"更符合"回放游标"这个解释——一个纯自增的己方动作计数器没有理由在某个时刻整体重置并收缩自己依赖的哈希表。

## 触发时机：已定位到具体的蓝图事件

`GetNextAction_Impl` 的调用点 `execGetNextAction`（原生 exec thunk，`_ZN18AMatchControllerV217execGetNextActionEv`，`0x144a94360`）在 IDA 全局交叉引用里**只有两处引用，且都是数据段（反射系统的 `UFunction` 元数据表项）**，没有任何一处原生机器码直接 `call` 它——这是 `BlueprintCallable UFUNCTION` 的正常形态：蓝图虚拟机通过按名字/索引查表分派调用，不生成能被 `xrefs_to` 直接找到的原生 `CALL` 指令；这正是此前反查两个候选入口点（19805、5308）时反查方法本身失效的原因，不是分析没做到位——因为真正的调用点根本不在原生代码里，而是蓝图字节码本身。

改用 FModel 反编译出的蓝图字节码（`Logic/MatchController.cpp`，这是 `AMatchController_C`——`AMatchControllerV2` 的蓝图子类——的完整 `ExecuteUbergraph_MatchController` 反编译）直接定位：入口标签 `Label_5308`（第 482 行）只能通过 `Label_5066` 处的一个条件判断（`isResyncingMatch || (!preStateDone_DoMulligan && bUseActionsForMulligan)` 为假时）用 `goto` 到达（第 465-483 行），本身不是任何蓝图事件的直接入口。往上追 `goto Label_5066` 的来源（全文件搜索 `5066`），只有一处外部跳入：`Label_21408`（第 1735 行）——这里先向 `GameplayMessageSubsystem` 广播一条 `MonitorPlayState` 消息、消息文本字面量写死为 `"from MatchController : ActionsReceived"`（第 1740 行），然后 `goto Label_5066`（第 1744 行），进入 `GetNextAction` 的消化循环。再往上追 `Label_21408` 本身如何被进入，找到它是一个字面量入口点：

```cpp
// (Event, Public, BlueprintEvent)
public void ActionsReceived()
{
    ExecuteUbergraph_MatchController(21408);
    return;
}
```

（`Logic/MatchController.cpp:1938-1944`）

**结论（已确认，不再是待定问题）**：`GetNextAction_Impl`（进而 `CurrentActionId` 的每一次推进）由 `MatchController_C::ActionsReceived()` 这个蓝图事件触发——每触发一次，就循环调用 `GetNextAction()` 把当前已知、尚未处理的动作全部消化完（每条都推进 `CurrentActionId` 并派发 `OnKardsActionEvent`），直到 `GetNextAction()` 返回失败（没有更多已知动作）为止。`ActionsReceived` 本身没有任何原生机器码 xref（在全局 FName 池里搜索字面量字符串 `"ActionsReceived"` 只命中一处、且引用它的同样只有两个数据段的反射表项，没有原生 `CALL`）——这跟 `GetNextAction` 是同一种架构：它是纯蓝图事件，只能被蓝图侧或者原生反射系统按名字动态触发（`ProcessEvent`），不会留下能反查的原生调用指令，这是 UE 蓝图事件调用机制本身的设计（按名字查表分派），不是这份二进制没有 PDB 导致的偶然限制。但这不影响结论的确定性：不管是哪一段原生网络轮询代码最终触发了它，`ActionsReceived` 这个事件本身的语义（结合第 1740 行的调试消息文本、结合它在整个 `MatchController.cpp` 里唯一的用途就是启动 `GetNextAction` 消化循环）已经足以确认——它对应的就是"客户端一次成功处理完服务端轮询回包"这个时刻，每次收到新的（无论是己方确认还是对方新提交的）动作数据后触发一次。这直接印证了"`CurrentActionId` 是本机回放合并动作日志进度指针"这一解释，不再是"更可能"的推测,而是从蓝图字节码直接读出的确定行为。
