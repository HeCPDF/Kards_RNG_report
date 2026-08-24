# 重播种机制如何解释每一个已观察到的现象

真实抓包已经确认（[README.md](README.md) §2.2-2.3、[evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)、[evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)）：`bUseTurnSwitchValidation` 在真实对局里是开启的，`cardsRandomStream` 每次创建/确认动作都会重播种为 `match_id + action_id * 19390`，而 `action_id` 是双方共享、从 1 开始逐一递增的简单计数器。本文把这套确认的机制，逐条对应到社区观察到的每一个具体现象上。

## 1. "同一次预报反复打开，结果不变"

只要没有创建新动作（`action_id` 没有推进），`cardsRandomStream` 就不会被重新播种——单纯重复打开预报面板本身不创建新动作，所以看到的候选不变。

## 2. "跨越多次操作的可查表规律"（Weather.md 的代价表、SpyRing.md 的环形游走）

每次创建新动作都会重播种，所以驱动这类规律的自变量是**`action_id`**，而不是"全场累计消费流的次数"。Weather.md §4 记录的社区规律里，"指令数大于 3 时 A/B 两档编号同时升一，持续到第 4 次预报"这种"以操作次数分段、超过阈值后行为整体切换"的现象，本质上就是在描述 `action_id` 的某种函数——只是社区当时用"指令数"这个更直观的代理变量去描述它。

## 3. "同回合内第二次开发结果一样"

如果本地投机计数器 `GetCurrentActionID()` 在两次触发之间没有正确自增（比如没有走完一次完整的"创建→提交→确认"闭环），两次重播种会用同一个 `action_id`、种子完全相同，三个抽签结果自然完全一样。这是唯一一个只能用"重播种开启"来解释、跟"整场只播种一次"完全对不上的现象——真实抓包确认开启，这个解释是最终结论,不是待验证假设。

## 4. 对局类型覆盖范围

目前的真实抓包证据只覆盖 `match_type: "training"`（人机单机局）——不能排除天梯 PvP、锦标赛等其他对局类型下 `bUseTurnSwitchValidation` 的值不同（例如出于反作弊/公平性考虑，正式排位赛可能采用不同配置）。如果社区的天气/间谍组织实测大多来自天梯/锦标赛而非单机训练局，需要额外抓包才能确认那些对局下是否是同一套机制。

## 5. 另见

- [README.md](README.md) — 完整机制交叉验证。
- [Weather.md](Weather.md) — 天气规律与 NZ33 确定性代价表。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律与已确认的完整周期。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该开关的证据来源。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — `action_id` 真实取值规律。
