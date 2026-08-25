# `CurrentActionId`（native, `AMatchControllerV2 + 0xC98`）真实自增逻辑

ReseedImpact.md 最初的分析里，把 `action_id`（本地投机计数器 `GetCurrentActionID()`）描述成"一个从 0 开始、按对局进程单调递增的小整数计数器"，暗示只要知道对局进行到哪一步，就能简单推算出下一个 `action_id`。这个描述**不准确**——经用户指出后用 IDA 核实，记录如下。

## 定位方法

1. `AMatchControllerV2::execGetCurrentActionID`（`0x144a93f20`）→ 调用 `MatchControllerV2_GetCurrentActionID_Impl`（`0x144aec160`），后者是纯 getter：`return *(unsigned int *)(a1 + 3224);`——确认 `CurrentActionId` 字段在原生内存布局里的真实偏移是 `+3224`（即 `0xC98`），跟此前 IDA 结构体重建标注的一致。
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

`CurrentActionId` 的语义（本机自计数，还是本机回放合并动作日志的进度指针）目前唯一的直接证据就是本文件反编译出的这套状态机本身：第 18 条"哈希表查不到下一个 slot 时重置为 1，随后重建/收缩哈希表"的行为，比"简单自增计数器"更符合"回放游标"这个解释——一个纯自增的己方动作计数器没有理由在某个时刻整体重置并收缩自己依赖的哈希表。`GetNextAction_Impl` 具体在游戏运行的什么时机被触发调用（是每次收到服务端轮询回包后自动触发，还是别的时机），需要追踪它在 `BP_Logic.cpp`/`Logic/MatchController.cpp` 里的调用点确定——这两处调用点的具体触发条件见 [two-distinct-action-id-counters.md](two-distinct-action-id-counters.md) 末尾的后续方向；用字面量常量反查调用点这条路径，在两个候选入口（19805、5308）里只有前者能追到一个仅限调试模式的函数 `loadDebugGameState()`，后者无法用同样方法定位——这是本报告静态分析方法本身的边界：`execGetNextAction` 是一个蓝图可调用的原生导出函数，蓝图侧的调用点分布在庞大的、按状态机跳转表组织的 Ubergraph 里，没有 PDB/符号名的情况下，从原生反编译单独反查"哪个具体的蓝图事件在什么时机调用了它"，需要逐个状态机跳转分支人工核对，超出反编译单个原生函数所能确定的范围。
