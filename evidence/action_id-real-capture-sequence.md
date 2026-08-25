# `action_id` 的真实取值规律：来自两份真实抓包的解密数据

这份证据直接来自本地抓包目录下的 `captures/{1,2}_Full.txt`（真实抓包，Fiddler 格式）用 `wards/matches/_codec.py` 逐条解密后的结果，不是反编译推断——这是本报告目前证据强度最高的一类来源：真实服务端接受过的、能对得上明文 JSON 的成功请求。

## 结论：`action_id` 是双方共享的单一全局计数器，逐一递增，没有例外

用 `_codec.decrypt_packet` 把两份抓包里全部 `POST .../actions` 请求体（`{"a": "<密文包>"}`）解密出来，取出每条请求明文 JSON 里的 `action_id` 字段，按抓包时间顺序排列：

- **抓包 2**（AI 对局，63 个我方提交的动作；原始 `match_id` 已脱敏）：`action_id` 序列是 `1,2,3,4,5,...,63`——**连续、无一处跳号**，逐条相差恰好 1。
- **抓包 1**（更长的一局，我方提交 62 个动作，全场最终到 `action_id=118`）：我方提交的 `action_id` 序列是 `1,2,3,4,7,8,9,10,14,15,16,20,...,117,118`——存在多处"跳号"（比如 4→7、10→14、16→20……），但**跳号处相差的量刚好等于对手（AI）在两次我方动作之间插入了多少个它自己的动作**（例如 `4→7` 中间插了 2 个，`52→63` 中间插了 10 个），跳号本身也印证了 PROTOCOL.md §8 已经写明的结论：`action_id` 是双方共用的同一条序列，不是各自独立计数。

把这两份数据放在一起看：**只要把双方的动作按真实发生顺序合并、不分先后手，`action_id` 就是从 1 开始、每次恰好 +1、绝不回退也绝不跳过的连续整数序列，全程没有观察到任何一次重置为 1、任何一次跳过不止一格、任何一次重复。**

## 与此前反编译分析的关系：这份数据实测的是 `Counter3228`，不是喂给重播种公式的 `CurrentActionId`

[evidence/two-distinct-action-id-counters.md](two-distinct-action-id-counters.md) 反编译 `MatchController_BuildActionJsonPayload` 后确认：提交请求 JSON 里写入的 `action_id` 字段（也就是本文件解密出来的这份数据）来自 `Counter3228`——一个只在本机构造新动作时自增、按归属方过滤的独立字段。喂给 `SetRandomStreamWithActionID` 重播种公式的是另一个字段 `CurrentActionId`（`this+3224`），[CurrentActionId-increment-logic.md](CurrentActionId-increment-logic.md) 反编译 `GetNextAction_Impl` 得到的那套按动作类型/归属方分支、条件重置为 1 的状态机，操作的正是 `CurrentActionId`，跟本文件解密出的 `Counter3228` 序列是两个不同的字段，两者不矛盾，各自成立。

`Counter3228` 从抓包数据看行为简单：本机每提交一次新动作就自增 1，从不重置、不跳号（抓包 1 里出现的"跳号"是服务端全局合并序列里对手插入动作导致的间隔，不是 `Counter3228` 本身跳号——`Counter3228` 只记录我方自己的动作数，序列仍是连续的 `1,2,3,...`）。`CurrentActionId` 的行为需要靠 `GetNextAction_Impl` 的反编译结果单独判断，不能用本文件这份数据替代。

## 对 ReseedImpact.md 结论的意义

本文件确认的"服务端合并后的全局 `action_id`"是一个单纯的、双方共享、逐一递增的计数——这独立证明了"预测服务端最终确认的动作编号，只需要数清楚双方一共发生过多少个动作"这一点，但这**不直接等同于**预测喂给随机数重播种公式的 `CurrentActionId`（后者由本机的 `GetNextAction_Impl` 状态机维护，语义上更接近"本机已回放到全局动作日志的第几条"，见 [CurrentActionId-increment-logic.md](CurrentActionId-increment-logic.md)）。ReseedImpact.md §3 给出的"社区回合内计数方法论有效性"论证，不依赖本文件的这份数据，也不依赖 `Counter3228`/`CurrentActionId` 是否同步。

## 局限性声明

- 这两份抓包都是**对 AI 单机对局**的记录，不是 PvP；PvP/锦标赛下 `Counter3228`/`CurrentActionId` 是否走同一套代码路径，属于 ReseedImpact.md §4 所述的数据覆盖边界，需要那些对局类型各自的抓包才能确认。
- 两份抓包都只覆盖了"正常出牌-攻击-结束回合"这类主流程动作，没有覆盖"挂反制→取消反制"这类操作在 `Counter3228`/`CurrentActionId` 序列里具体如何计数（是否每次反制切换都会各自占用一个编号，还是被合并计数）——这是下一步应该用新抓包验证的具体问题，需要新数据，不是本文件已有数据能回答的。
