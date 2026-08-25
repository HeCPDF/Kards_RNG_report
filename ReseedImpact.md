# 重播种机制如何解释每一个已观察到的现象

真实抓包已经确认（[README.md](README.md) §2.2-2.3、[evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)、[evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)）：`bUseTurnSwitchValidation` 在真实对局里是开启的，`cardsRandomStream` 每次创建/确认动作都会重播种为 `match_id + action_id * 19390`，而 `action_id` 是双方共享、从 1 开始逐一递增的简单计数器。本文把这套确认的机制，逐条对应到社区观察到的每一个具体现象上。

## 1. 第一次预报得到结果后，不做别的事、只打出另一张预报牌：2K/4K 变化，6K 不变

这是社区实测确认的现象：真实产生了新的一次抽签（不是重新打开同一个结果的 UI），2K/4K 的候选会变化，6K 保持不变。

`RandomIntFromRangeWithStream(0, _heavyWeatherCards.Length - 1)`（Weather.md §2.2）在候选池只有 1 个成员时，无论传入的随机数是什么，返回下标必然是 0——这是代码结构决定的，不是待验证的猜测。但"6K 候选池此刻是否只有 1 个成员"取决于 `GetAllActiveStaticCards` 具体筛选出多少张 `subtype.heavyWeather` 卡：已直接核实这个函数的筛选条件只有两层——按 `cardSet`（卡牌所属扩展包/是否是玩家可获取的）过滤，以及按 `NotifyCheckCardReserved` 排除"预留"卡；**函数里没有任何按"当前是否在场上/冷却中"来动态排除候选的逻辑**。也就是说，6K 候选池的大小主要由"这三张 6K 效果卡的 `cardSet`/预留状态"决定，是否随对局进程动态变化、具体这三张卡当前是否都通过筛选，还没有在这套代码里独立核实到——需要进一步确认这三张卡各自的 `cardSet` 取值和预留状态，而不是假设"场上/冷却"这种未被代码支持的排除机制。

## 2. 为什么会存在这个漏洞：确定性重播种 + 玩家可自行控制的本地计数器

三点已确认事实（分别在 README.md §1/§2.2/§2.3 和对应证据文件里有完整推导/抓包证据），合在一起构成了漏洞的完整因果链：

1. `cardsRandomStream` 是公开算法的确定性 `FRandomStream`（线性同余生成器），种子完全决定输出序列，没有任何硬件熵源或不可预测输入。
2. 玩家提交动作前看到的所有预览结果（天气预报三选一、间谍组织实际抽到哪张卡等），用的种子是 `match_id + 本地投机计数器 * 19390`——`match_id` 在对局引导数据里就是明文可见的，`本地投机计数器`（真实证据见 [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)）只在玩家自己创建新动作时递增，完全不受对手影响。
3. 玩家自己完全知道、也完全能控制"我这局已经做过多少个动作"——每多做一次任何会创建新动作的操作（哪怕是不花费资源、马上撤销的操作，比如激活一次反制立刻取消），这个本地计数器就会 +1，进而让种子按已知公式 `+ 19390` 前进一步。

**这就是漏洞的本质**：预览结果不是"随机"给玩家看的，而是"玩家自己已经做过多少次动作"这个自己完全掌握的数字，经过一个公开、确定性的公式算出来的。只要有人像 NZ33 一样，把"本地计数器取值 → 展示结果"这张映射表实测出来，就能反过来推导："我现在的本地计数器是 X，想要的天气对应计数器 Y，那我只需要再做 `Y-X` 次不花费用的空操作（比如反复切换一次不实际使用的反制），就能把预览结果精确调整成我想要的"——这正是社区描述的"挂反制→取消反制，不耗费用地控制天气"打法的完整原理，也是官方公告里承认"存在可以被特定操作序列控制"的这个游戏机制问题的根源。

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
