# 重播种机制如何解释每一个已观察到的现象

真实抓包已经确认（[README.md](README.md) §2.2-2.3、[evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)、[evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)）：`bUseTurnSwitchValidation` 在真实对局里是开启的，`cardsRandomStream` 每次创建/确认动作都会重播种为 `match_id + action_id * 19390`，而 `action_id` 是双方共享、从 1 开始逐一递增的简单计数器。本文把这套确认的机制，逐条对应到社区观察到的每一个具体现象上。

## 1. "同回合内反复重新预报，只有 6K 通常不变，2K/4K 会变"（更正）

**本节最初的版本是错的**——最初写的是"重复打开预报面板不创建新动作，所以结果不变"，以及"如果本地投机计数器没有正确自增，两次重播种会用同一个 `action_id`、三个抽签结果自然完全一样"。这两种表述都暗示"要么全部三档一起冻结，要么全部一起变化"，但真实现象不是这样——经反馈更正：**同回合内反复重新预报，2K/4K 会变化，只有 6K 通常不变**。这跟"三档共享同一个种子、要么一起冻结要么一起变"这个简化模型直接矛盾：如果重播种确实发生了（种子变了），2K/4K 变化的同时 6K 不应该保持不动；如果重播种没发生（种子没变），2K/4K 也不应该变化。

真正的机制**不在"这次有没有重播种"这个二元判断上**，而在 Weather.md §4.1 已经确认的代价模型上：2K/4K 的跨组代价是 3（同组代价 15），6K 的跨组代价只有 1、同组代价是 0。也就是说三档共用的是同一条驱动流/同一个自变量在往前走，但每一档"要走多远才会跳到下一个候选"的门槛完全不同——2K/4K 门槛高，容易在"没变"和"变了"之间被观测到变化；6K 门槛极低，理论上更容易变化，但**同组代价是 0**——如果连续两次预报之间自变量的推进量不足以跨出所在的 3 元小组，6K 展示的候选可能仍然是同一个小组内的另一个效果（肉眼看起来"是不是没变"取决于玩家有没有注意到具体是哪一个效果，而不是小组编号变没变）。这跟"驱动自变量是否推进"是两回事——本节之前把"结果不变"直接等同于"自变量没推进"是错误的简化，真正决定"看起来变不变"的是这张代价表，不是重播种开关本身。

## 2. "跨越多次操作的可查表规律"（Weather.md 的代价表、SpyRing.md 的环形游走）

真实抓包已经确认（[evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)）：驱动预报/间谍组织等**预提交阶段就能看到结果**的效果的，是玩家自己的**本地投机计数器**（`GetCurrentActionID()`）——这个计数器只在我方自己创建新动作时递增，完全不管对手做了什么，不是"全场累计消费流的次数"，也不是双方合并后的服务端权威 `action_id`。这正是社区仅凭"数自己做了几次操作"就能总结出可复现规律表的根本原因：他们凭直觉抓住的"操作次数"，跟游戏内部驱动预览结果的那个变量，本来就是同一个东西——不需要知道对手做了什么。Weather.md §4 记录的社区规律里，"指令数大于 3 时 A/B 两档编号同时升一，持续到第 4 次预报"这种"以操作次数分段、超过阈值后行为整体切换"的现象，本质上就是在描述这个本地计数器的某种函数。

## 3. 对局类型覆盖范围

目前的真实抓包证据只覆盖 `match_type: "training"`（人机单机局）——不能排除天梯 PvP、锦标赛等其他对局类型下 `bUseTurnSwitchValidation` 的值不同（例如出于反作弊/公平性考虑，正式排位赛可能采用不同配置）。如果社区的天气/间谍组织实测大多来自天梯/锦标赛而非单机训练局，需要额外抓包才能确认那些对局下是否是同一套机制。

## 4. 另见

- [README.md](README.md) — 完整机制交叉验证。
- [Weather.md](Weather.md) — 天气规律与 NZ33 确定性代价表。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律与已确认的完整周期。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该开关的证据来源。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — 服务端权威 `action_id` 真实取值规律。
- [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md) — 本地投机计数器 vs 服务端确认编号，两套编号的真实差异（本文档结论的核心证据来源）。
