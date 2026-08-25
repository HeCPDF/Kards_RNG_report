# `CurrentActionId`（native, `AMatchControllerV2 + 0xC98`）真实自增逻辑

`CurrentActionId`（`GetCurrentActionID()` 返回值）不是一个简单自增的小整数计数器，而是由动作日志回放状态机驱动、依赖动作类型和归属方的字段，不能单靠"对局进行到第几步"直接推算。反编译记录如下。

## 定位方法

1. `AMatchControllerV2::execGetCurrentActionID`（`0x144a93f20`）→ 调用 `MatchControllerV2_GetCurrentActionID_Impl`（`0x144aec160`），后者是纯 getter：`return *(unsigned int *)(a1 + 3224);`——确认 `CurrentActionId` 字段在原生内存布局里的真实偏移是 `+3224`（即 `0xC98`），跟此前结构体布局分析记录的一致。
2. 用 `search_text` 在 `AMatchControllerV2` 全部原生函数所在的地址段（`0x144a80000`-`0x144b20000`，约 5MB，远小于整个 `.text`，能在超时前扫完）搜索反汇编里出现的 `0C98h` 偏移引用，命中 33 处，分布在十几个不同函数里——包括至少两处 `inc dword ptr [...+0C98h]` 和三处 `mov dword ptr [...+0C98h], 1`，全部集中在 `MatchControllerV2_GetNextAction_Impl`（`0x144af2180`）和几个初始化/重置类函数里。
3. 完整反编译 `MatchControllerV2_GetNextAction_Impl`（对局的动作日志/回合状态机核心函数）确认了这些写入点各自的触发条件。原文见 [evidence/ida-excerpts/GetNextAction_Impl.c](ida-excerpts/GetNextAction_Impl.c)、[evidence/ida-excerpts/GetCurrentActionID_Impl.c](ida-excerpts/GetCurrentActionID_Impl.c)。

## 真实逻辑：不是单一的"+1"，是一个依赖动作类型和归属方的状态机

`MatchControllerV2_GetNextAction_Impl` 会在动作日志哈希表（`a1+3240` 起）里查找 `CurrentActionId` 对应的条目，然后：

- 如果查到的动作类型字符串是 `"XActionEndOfTurn"` 且是重复的（`a1+1960` 标记），记一条 `"DUPLICATE END TURN IN MATCH %d action, %d"` 日志，**递归调用自身**，并在递归前把 `CurrentActionId` 加一（`++*(a1+3224)`，地址 `0x144af259d`）——这是第一处自增。
- 走到主处理分支（非重复的正常动作）时，也会把 `CurrentActionId` 加一（`++*(a1+3224)`，地址 `0x144af27eb`）——这是第二处自增，逻辑上跟第一处是"同一件事的两条不同路径"，不是各自独立的两个计数器。
- 只有当这个动作的"所属方"字段（`*(a2+24)`）等于本地缓存的己方 ID（`*(*(a1+3432)+2024)`）时，才会额外递增另一个计数器 `Counter3228`（`a1+3228`，`++*(_DWORD *)(a1+3228)`，地址 `0x144af2909`）——说明存在一个**跟 `CurrentActionId` 平行、但只统计"自己这方"动作数量**的独立计数器，两者不是同一个东西。
- 在动作日志哈希表查不到"下一个 slot"时（`v57 == -1` 分支），会把 `CurrentActionId` **直接重置为 `1`**（`*(a1+3224) = 1`，地址 `0x144af2978`），然后重建/收缩哈希表（`sub_144A91ED0`/`sub_1416B78E0`/`sub_144B02F20`）并调用 `MatchControllerV2_OnActionsEvaluationComplete_Impl`——这看起来是"这一批已知动作全部处理完、准备好接收下一批"的信号，而不是单纯的对局内累计计数器。
- 还有一条独立的"动作 ID 出现空洞"（gap）检测路径：如果日志表里下一条动作的 ID 比 `CurrentActionId` 还大，会记一条 `"RESYNC: gap in action IDs"` 日志并触发 `sub_144A92870`（推测是重新同步请求）。

## 结论：预测 `action_id` 需要复现整套状态机，不是简单计数

预测 `CurrentActionId` 需要复现 `GetNextAction_Impl` 整套状态机，工作量跟解析抓包相当，不能单靠"对局进行到第几步"简单推算。

## 提交 JSON 里的 `action_id` 字段与 `CurrentActionId` 是两个不同的字段

提交请求 JSON payload 里的 `action_id` 字段来自 `Counter3228`（一个只在本机构造新动作时自增、按归属方过滤的独立字段——即本文件第 17 条列出的"只统计自己这方动作数量"的那个平行计数器），不是本文档反编译的 `CurrentActionId`（`this+3224`）。也就是说，抓包能直接验证的是 `Counter3228` 的行为，不能直接验证 `CurrentActionId` 的行为——上面第 5-19 节反编译出的 `GetNextAction_Impl` 状态机描述（按动作类型/归属方条件递增、查不到下一个 slot 时重置为 1、gap 检测）是 `CurrentActionId` 唯一已知的直接代码证据。完整区分见 [evidence/two-distinct-action-id-counters.md](two-distinct-action-id-counters.md)。

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

（`Logic/MatchController.cpp:1938-1944`；连同 `Label_21408`/`Label_5066`/`Label_5308` 三段的完整原文见 [evidence/fmodel-excerpts/MatchController-ActionsReceived.cpp](fmodel-excerpts/MatchController-ActionsReceived.cpp)）

**结论（已确认，不再是待定问题）**：`GetNextAction_Impl`（进而 `CurrentActionId` 的每一次推进）由 `MatchController_C::ActionsReceived()` 这个蓝图事件触发——每触发一次，就循环调用 `GetNextAction()` 把当前已知、尚未处理的动作全部消化完（每条都推进 `CurrentActionId` 并派发 `OnKardsActionEvent`），直到 `GetNextAction()` 返回失败（没有更多已知动作）为止。`ActionsReceived` 本身没有任何原生机器码 xref（在全局 FName 池里搜索字面量字符串 `"ActionsReceived"` 只命中一处、且引用它的同样只有两个数据段的反射表项，没有原生 `CALL`）——这跟 `GetNextAction` 是同一种架构：它是纯蓝图事件，只能被蓝图侧或者原生反射系统按名字动态触发（`ProcessEvent`），不会留下能反查的原生调用指令，这是 UE 蓝图事件调用机制本身的设计（按名字查表分派），不是这份二进制没有 PDB 导致的偶然限制。但这不影响结论的确定性：不管是哪一段原生网络轮询代码最终触发了它，`ActionsReceived` 这个事件本身的语义（结合第 1740 行的调试消息文本、结合它在整个 `MatchController.cpp` 里唯一的用途就是启动 `GetNextAction` 消化循环）已经足以确认——它对应的就是"客户端一次成功处理完服务端轮询回包"这个时刻，每次收到新的（无论是己方确认还是对方新提交的）动作数据后触发一次。这直接印证了"`CurrentActionId` 是本机回放合并动作日志进度指针"这一解释，不再是"更可能"的推测,而是从蓝图字节码直接读出的确定行为。

## 第二个独立写入点：`/actions` 轮询 HTTP 回调里的直接纠正逻辑

用 `search_text` 在 `AMatchControllerV2` 全部原生函数地址段重新扫描 `0C98h`（`CurrentActionId` 偏移）的全部引用（33 处），除了上面 `GetNextAction_Impl` 的两处 `inc` 之外，还发现一处此前遗漏的直接**写入**（不是自增）：`MatchController_OnActionsResponse_ProcessTick_A`（`0x144ac6090`，`/actions` 轮询请求的 HTTP 响应回调，从函数体内解析 JSON 里的 `"actions"` 数组、`"ActionEndMatch"`、`"mulligan_done"` 等字面量可以确认这个身份）。反编译其处理轮询回包数组的循环段：

```c
// v88 = 这一条轮询回来的动作自带的 action_id 字段（解析自 JSON）
if ( v88 <= *(int*)(ClosureCtx + 3224) )   // 如果这条已确认动作的编号 <= 当前 CurrentActionId
{
    if ( !FString_EqualsIgnoreCase_Maybe(actionType, "ActionEndMatch") )
    {
        if ( *(BYTE*)(ClosureCtx + 1960) )   // 跟 MatchController_BuildActionJsonPayload 里同一个标志位
        {
            *(int*)(ClosureCtx + 3224) = v88;   // 直接把 CurrentActionId 覆写成这条动作的真实编号
            PendingHttpRequest_CancelOrRelease(*(QWORD*)(ClosureCtx + 3408));  // 取消一个挂起的 HTTP 请求
        }
    }
}
sub_144AA2180(ClosureCtx + 3240, &v88, &v88);   // 把这条动作登记进动作日志哈希表（GetNextAction_Impl 读的同一张表）
```

这是一条跟 `GetNextAction_Impl` 平行、独立的写入路径，性质是**回退/纠正，不是推进**：只有当轮询回来的这条动作真实编号"小于等于"本机当前 `CurrentActionId` 时才触发——也就是本机此前投机计算出的 `CurrentActionId`"猜"得比服务端最终确认的还靠前，这里拿真实值往回修正，同时取消一个不再需要的挂起请求（很可能是一个投机性的重同步/轮询请求）。

**这条证据直接回答了"我方自己的操作会不会立刻反映到 `CurrentActionId`"这个问题**：答案是不会——`CurrentActionId` 唯一已知的两条写入路径（`GetNextAction_Impl` 的增量回放、这里的直接纠正）都挂在"处理一次 `/actions` 轮询 HTTP 回包"这个事件上，触发条件都是"收到并解析完一批服务端确认数据"，不是"本机刚创建了一个新动作"。`GetCurrentActionID()`（调用点 A 读取的那个 getter）本身只是纯读取（`return *(a1+3224)`，不做任何写入），所以本地投机重播种用的值，就是"最近一次轮询回包处理完毕后，`CurrentActionId` 停在哪"，中间发生了多少次本机点击操作、这些点击隔了多久，都不会让它提前变化——只有下一次轮询回包到达并被处理，它才可能变。这跟真实抓包里反复观察到的"本地 `Counter3228`（提交计数）已经远远超前于最终能用来准确预测展示结果的 `CurrentActionId`"这一现象（`evidence/live-match-forecast-validation.md`）完全吻合：两者进度不一致，正是因为一个是"我点了几次"，另一个是"轮询同步追上了没有"。

## 轮询节奏本身已经反编译确认：大约每 5 秒一次，不是随点击同步

反编译 `MatchControllerV2_MatchActionsPollLoop_Impl`（`0x144afd490`，每 tick 都会被调用一次的轮询驱动函数）确认了触发 `/actions` GET 请求的精确节流条件：

```c
if ( *(BYTE*)(this+3081) == 4 )   // 仅在"活跃轮询"状态下才做任何事
{
    if ( ping标志(+3476/+3477) 为真 || (当前时间 - 上次轮询时间(+3160)) >= 5.0 )   // 硬编码的 5.0 秒间隔
    {
        if ( 没有已经在飞行中的轮询请求(+3392==0) && 没有在等 mulligan 结算 )
        {
            // 构造并发出 GET 请求，请求体：
            // { "min_action_id": <当前 CurrentActionId>, "opponent_id": ..., "time_since_opponent_ping": ... }
            发出轮询请求(...)
        }
    }
}
```

关键点：

1. **轮询请求本身，会把发出这一刻的 `CurrentActionId` 当前值原样带在请求体的 `min_action_id` 字段里**——服务端据此只返回这个编号之后的新动作，这是一个标准的增量拉取协议，也再次独立确认了 `CurrentActionId` 在客户端里的核心角色：不是"我提交到第几个"，而是"我已经同步到服务端权威日志的第几条"。
2. **两次轮询之间硬编码了至少 5 秒的间隔**（`>= 5.0`，还有一个跟"ping 标志"相关的例外条件会绕开这个等待——触发条件已在下方"`ping` 标志置位路径"一节查明，是服务端 websocket 广播的 `matchaction` 通知）——也就是说，`CurrentActionId`（进而喂给随机数重播种公式的那个值）**每 5 秒左右才可能更新一次，不管这 5 秒里玩家自己点了几次鼠标、提交了几个动作，除非期间有一次 websocket 通知把这次等待提前打断**。
3. 另有一条独立分支：当没有进入"活跃轮询"状态、但 `this+3688` 存的计时器句柄非空时，会清除这个计时器（`FTimerManager::ClearTimer` 形状的调用序列）——对应"停止轮询"的收尾逻辑，跟本节主题关系不大。

**这解释了本报告这次会话反复遇到的"实测消耗的原始单位数，比按操作次数数出来的社区口径预期值更大"这一系列现象的根本原因**：不是某个具体操作类型（反制、跨回合结束回合、攻击……）的权重被漏算或算错了，而是**驱动展示结果的 `CurrentActionId`，本质上是"过去 5 秒节奏的轮询周期里，服务端权威日志追加了多少条已确认动作"，不是"玩家在这段时间里点了几次鼠标"**——这两者只有在"玩家操作节奏恰好跟 5 秒轮询周期对齐、且期间没有额外的服务端确认动作插入"这种理想情况下才会近似相等；一旦玩家连续快速点击（多次操作落在同一个轮询周期内）、或者操作间隔恰好跨过一次轮询边界（多算或少算一整个轮询周期的量），实际消耗的 `CurrentActionId` 单位数就会跟"数操作次数"这套方法论系统性地对不上——不是社区权重表哪一项错了，是这套方法论本身的前提（"操作次数≈驱动量"）只在特定节奏下才近似成立。

## `ping` 标志置位路径：已定位到具体的蓝图事件，5 秒节流有一个明确的例外

`sub_144AB7130` 是 `AMatchControllerV2` 的原生构造函数——开头把 `*(_QWORD*)a1` 写成 `AMatchControllerV2_VFT`（写虚表指针），然后把对象里约 200 个字段依次清零/置默认值，末尾一条 `mov word ptr [rdi+0D94h], 101h`（`0D94h`=3476）把 `+3476`/`+3477` 这两个字段初始化成 `1`，是构造时默认初始化的一部分，不是一个能在对局中途单独调用的"置位 ping 标志"操作（反汇编确认其函数序言只读取 `RCX` 这一个参数）。

真正的运行时置位证据有两条，互相独立：

1. `sub_144A8F5D0` 是一个独立、最小的写入点（`*(_BYTE*)(a1+3476)=1`，只做这一件事），跟 `MatchActionsPollLoop_Impl` 里判断"是否绕开节流"的第一个条件字段完全对应。
2. 更直接的证据来自蓝图字节码本身：`Logic/BP_KardsSession.cpp` 里，收到一条 `message=="matchaction"` 的 websocket 通知时，蓝图直接对 `MatchControllerV2` 的蓝图属性做了一次赋值 `triggerPollActions = true`。蓝图属性赋值在编译后是按 `FProperty` 偏移直接写内存，字段名（"触发轮询动作"）、赋值时机（收到服务端 websocket 通知）、效果预期（下次 tick 提前轮询）三者互相印证，构成完整证据链。唯一还没有闭合的一环是：`triggerPollActions` 这个蓝图属性在原生内存里究竟落在 `+3476` 还是 `+3477`（蓝图侧属性名不保证跟原生手工注释的偏移一一对应）——这一点没有再用 IDA 结构体信息逐字节核对，留作具体未闭合点，不影响下面"轮询存在一个可被 websocket 通知提前触发"这个结论的方向。

改用 FModel 反编译出的蓝图字节码定位调用点：`Logic/BP_KardsSession.cpp` 里，`AKardsSession` 处理一条 websocket 通知（先判断 `IsWebsocketNotifications()`，再对通知的 `message` 字段做字符串分支）的逻辑段中：

```cpp
SwitchString_CmpSuccess_1 = (CustomEvent_message_3 !== "matchaction");
if (!SwitchString_CmpSuccess_1)
    goto Label_11478;
return;

Label_11478:
GetMatchController = AMatchControllerV2::GetMatchController(this);
GetMatchController->triggerPollActions = true;
return;
```

（`BP_KardsSession.cpp` 约第 937-947 行）——当服务端通过 websocket 推送一条 `message == "matchaction"` 的通知时，客户端直接把 `MatchControllerV2` 上的蓝图属性 `triggerPollActions` 置为 `true`。这是一个直接的属性赋值（不是函数调用），UE 蓝图属性在原生内存里的偏移与前面反编译确认的 `this+3476`（`sub_144A8F5D0` 单独置位的那个标志、也是 `MatchActionsPollLoop_Impl` 判断条件里的第一个 ping 标志）语义完全吻合——字段名（"触发轮询动作"）、置位效果（下一次 tick 立即绕开 5 秒节流发出 `/actions` 请求）、触发场景（收到一条服务端 websocket 通知）三者互相印证，构成完整证据链。

**结论**：5 秒轮询节流存在一个明确例外——服务端不是只能被动等客户端每 5 秒问一次，而是会在**任意一方**提交新动作后，通过 websocket 主动推送一条 `matchaction` 通知给双方客户端，收到通知的一方立即绕开节流发起一次 `/actions` 轮询、把 `CurrentActionId` 推进到最新。也就是说：
- 只要网络连接（websocket）正常，`CurrentActionId` 的更新延迟主要取决于"服务端处理完一个新动作、推送通知、客户端收到通知并完成一次轮询往返"这条链路的真实网络延迟（通常远小于 5 秒），不是固定按 5 秒一拍。
- 5 秒节流只在 websocket 通知丢失/延迟、或者本地刚做完一次轮询还没到间隔时才会真正成为瓶颈；正常网络条件下，`CurrentActionId` 事实上会近似"随动作实时更新"，只是仍然要走一次轮询往返（不是本地点击的瞬间同步写入）——这跟本文档前面确认的"`CurrentActionId` 只有处理 `/actions` 轮询回包这一个事件才会写入"并不矛盾，只是把"多久才会触发下一次这样的写入"从"最多 5 秒"精确到了"通常是一次网络往返"。
- 这条结论没有区分通知的"归属方"（判断逻辑只看 `message=="matchaction"`，不检查是哪一方提交的动作），加上 §"结论（已确认）"一节已确认 `GetNextAction_Impl`/`ActionsReceived` 本身也不区分动作归属方，可以确定**无论是本方还是对方提交了新动作，服务端都会向双方广播这条 websocket 通知**——这直接、完整地回答了本文档最初要解决的问题"友方（己方）操作是否会被立刻处理"：会，但"立刻"指的是"一次网络往返之后"，不是"点击的同一帧内"，也不是本地投机计算就能提前预知的。
