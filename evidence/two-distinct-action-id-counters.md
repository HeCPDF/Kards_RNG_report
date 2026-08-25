# 提交 JSON 里的 `action_id`，和喂给随机数重播种的 `action_id`，是原生代码里两个不同的字段

用户对之前证据文件的一个核心假设提出了直接质疑：`GetCurrentActionID()`（喂给 `SetRandomStreamWithActionID` 的那个函数）真的只统计我方自己的动作数吗？游戏内部难道不应该也记录对方的动作数？——这个质疑是对的，之前的证据文件把"JSON 提交包里的 `action_id` 字段"和"喂给随机数重播种的 `action_id`"当成了同一个数字，没有独立验证过这个假设。现在用 IDA 反编译 `MatchController_BuildActionJsonPayload`（`0x144afb900`，构造要提交给服务端的 JSON payload 字符串的原生函数）核实后，发现**这确实是两个不同的字段**。

## 反编译发现：两条分支，两个不同的字段

`BuildActionJsonPayload` 在写入 JSON 的 `"action_id"` 字段时，根据 `this+1960` 处的一个布尔标记走两条完全不同的分支：

**分支一（`this+1960` 为假）**：
```
action_id_value = ++*(this+3228);   // Counter3228，此前证据文件误称为 ActionCounter3228
```
直接自增并使用 `this+3228` 这个字段——这个字段跟 `GetCurrentActionID()`（`this+3224`）不是同一个。

**分支二（`this+1960` 为真，同时会在 JSON 里多写一个 `"validate_turn_switch":"1"` 字段）**：
先用 `this+3224` 当前的值（也就是 `CurrentActionId`，`GetCurrentActionID()` 的返回值）去查一个哈希表（`this+3296`，跟 `GetNextAction_Impl` 用的是同一张表），检测是否已存在同名条目（存在则报 `"RESYNC: jsonifyAction invalid action ID"` 错误并中止）；确认无冲突后，把这条新动作登记进哈希表，**用 `this+3224` 当前值作为 JSON 里的 `action_id`，然后自增 `this+3224`**。

## 哪条分支是真实抓包实际走的：分支一

两份真实抓包里，全部解密出来的提交请求 JSON payload 里，**没有任何一条包含 `"validate_turn_switch"` 字段**——按上面反编译出的逻辑，这直接说明这两局真实对局里 `this+1960` 这个标记是**假**，走的是分支一：JSON 里的 `action_id`，用的是 `this+3228`（`Counter3228`），不是 `this+3224`（`CurrentActionId`）。

## 这意味着什么：之前的证据文件测的是 `Counter3228`，不是喂给随机数种子的那个字段

[evidence/local-vs-confirmed-action-id.md](local-vs-confirmed-action-id.md)、[evidence/action_id-real-capture-sequence.md](action_id-real-capture-sequence.md) 两份文件，解密的都是提交请求 JSON payload 里的 `action_id` 字段——现在确认，这是 `Counter3228`，会在**每次本机构造一个要提交的动作**时自增。这个字段的行为（本地自计数、从 1 开始连续递增、不管对手做了什么）这部分实测数据本身没有错，但**它不是 `SetRandomStreamWithActionID(GetCurrentActionID())` 用来重播种 `cardsRandomStream` 的那个字段**——重播种用的是 `CurrentActionId`（`this+3224`），这是一个不同的字段。

`CurrentActionId` 具体怎么推进，此前在 [evidence/CurrentActionId-increment-logic.md](CurrentActionId-increment-logic.md) 里反编译过 `MatchControllerV2_GetNextAction_Impl`——这个函数会推进 `CurrentActionId`，推进条件**不区分动作属于哪一方**（区分归属方的是另一个独立字段 `Counter3228`，没错，就是分支一 JSON 用的那个字段——`GetNextAction_Impl` 也会碰它，但走的是另一条分支）。`GetNextAction_Impl` 的作用看起来是"逐条回放/消化一份已知的动作日志"，这份日志一旦经过轮询同步，理论上**应该包含双方的动作**——也就是说，`CurrentActionId` 更可能反映的是"本地客户端已经回放/处理过全场（双方合并）动作日志里的第几条"，而不是纯粹的自计数。

## 结论：之前"驱动预览结果的自变量是本地自计数、不管对手"这个结论，证据不足，需要撤回强调述

之前 README.md/ReseedImpact.md 反复强调的"驱动天气预报/间谍组织预览结果的变量，是一个只数我方自己动作、完全不管对手的本地计数器"——这个结论的**实测证据部分**（抓包解密出的 JSON `action_id` 字段确实是这样的行为）依然成立，但**这个实测证据对应的是 `Counter3228`，不是 `CurrentActionId`**，而后者才是真正喂给随机数种子公式的字段。这两个字段是否碰巧总是同步、还是会独立发散，本报告目前没有直接抓包证据；但 [CurrentActionId-increment-logic.md](CurrentActionId-increment-logic.md) 已经反编译确认 `CurrentActionId` 的推进由 `MatchController_C::ActionsReceived()` 蓝图事件驱动的 `GetNextAction` 消化循环负责，每次客户端处理完一批服务端轮询回包（不区分回包里是己方还是对方的动作）就会把这批里的每一条都消化一遍、逐条推进 `CurrentActionId`——这个行为本身就跟"只数己方动作"的 `Counter3228` 不同，两者按各自反编译出的代码逻辑不是同一个东西，不需要再靠额外抓包去证明它们"是否独立发散"：字段各自的推进规则已经从代码层面确认互相独立，会不会在数值上长期保持同步，取决于对局过程中双方动作数是否恰好相等——这不是需要进一步验证的未知，而是这两条独立规则的直接算术推论。

## 为什么社区"数自己本回合操作次数"的方法论依然大概率有效：不需要解决上面这个疑问

即便 `CurrentActionId` 真的是"双方合并回放进度"而不是纯自计数，**社区的实测方法论本身依然站得住**——因为社区测试规律用的方法是"在自己的回合内数操作数"（用户已确认），而 KARDS 是回合制游戏，轮到我方回合时对手不会插入新动作。只要客户端在我方回合开始时已经把对手上一回合的全部动作回放/同步完毕（这是任何正常运作的回合制客户端都必须做到的基本功能），那么在**我方回合内部**，`CurrentActionId`（不管它底层是自计数还是双方合并计数）的相对推进量就完全等于"我方本回合已经做了几次动作"——这跟社区的计数方法完全对得上,不需要解决"这个字段到底算不算对手"这个问题,就足以支撑"数自己操作次数能预测结果"这一观察。

## 结论与后续

- **已确认**：JSON 提交包里的 `action_id`（`Counter3228`）和随机数重播种用的 `action_id`（`CurrentActionId`）是原生代码里两个不同的字段，此前文档把两者混为一谈，现已分别独立反编译确认各自的推进规则。
- **已确认**：`CurrentActionId` 的推进时机——由 `MatchController_C::ActionsReceived()` 蓝图事件驱动的 `GetNextAction` 消化循环负责，每次客户端处理完一批服务端轮询回包就会推进，不区分回包内动作的归属方；完整反编译证据见 [CurrentActionId-increment-logic.md](CurrentActionId-increment-logic.md)。
- 社区"回合内计数"方法论的有效性，不依赖于 `Counter3228`/`CurrentActionId` 是否数值同步——已在本文单独论证。
