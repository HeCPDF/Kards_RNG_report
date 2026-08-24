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

## 二次更正：真实抓包证明这个"更悲观"的结论也不对

用真实抓包（`本地抓包目录/{1,2}_Full.txt`）逐条解密出全部提交请求里的 `action_id` 字段后（完整数据见 [action_id-real-capture-sequence.md](action_id-real-capture-sequence.md)），发现两局真实对局里 `action_id` 全程都是**从 1 开始、每次恰好 +1、双方共享同一条序列**，没有观察到任何一次重置、跳过或重复。

这意味着上面反编译出的复杂分支逻辑（按动作类型/归属方条件递增、重置为 1、gap 检测）描述的不是"服务端最终分配给这个动作的 `action_id` 是怎么算出来的"，而更可能是**客户端本地回放/消化一份已经取得的动作列表**时用的遍历状态机——"重置为 1"对应的是"这一批本地已知动作处理完、指针归位"，不是"整场对局的计数器归零"；两件事外观相似（都叫 `CurrentActionId`/都在同一个字段上操作），但语义不同,容易被混淆。真正决定"下一个动作会拿到几号"的规则，从真实数据看极其简单——就是"双方合计发生的第几个动作"，不需要理解这里描述的任何分支条件。ReseedImpact.md 已同步做出第二次更正。
