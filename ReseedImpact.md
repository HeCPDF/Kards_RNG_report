# 重播种机制如何解释每一个已观察到的现象

真实抓包已经确认（[README.md](README.md) §2.2-2.3、[evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)、[evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)、[evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)）：`bUseTurnSwitchValidation` 在真实对局里是开启的，`cardsRandomStream` 每次创建/确认动作都会重播种为 `match_id + action_id * 19390`。**注意**：反编译进一步确认，真正喂给这个重播种公式的 `CurrentActionId` 字段，跟提交请求 JSON 里那个已经实测确认"只数我方自己动作、从 1 连续递增"的 `action_id` 字段（`Counter3228`），是原生代码里两个不同的字段——完整区分见 [evidence/two-distinct-action-id-counters.md](evidence/two-distinct-action-id-counters.md)。本文以下用"本地计数器"统一指代喂给重播种公式的那个变量，它的精确推进规则（是否严格自计数）尚未完全坐实，但社区"在自己回合内数操作次数"的方法论不依赖于这一点也能成立（原因见该证据文件），本文把这套确认的机制，逐条对应到社区观察到的每一个具体现象上。

## 1. 为什么 6K 在"连续两次预报、中间不做别的事"时看起来不变，而 2K/4K 会变

**一次完整的预报触发在本地计数器上消耗 3 个单位，这一点已经从代码的动作创建链上逐步反编译确认，不是照搬社区的说法**：

1. 玩家在第一个弹窗里选择天气类型（晴/雨/风）——这个选择通过 `CreateAction_InitStart("XActionCardToDrawSelected", ...)` 创建一个动作（`BP_OnlineMatch.cpp:2683-2686`）。
2. 选中的一级天气代表卡被 `SpawnCardInHandBySide` 加入手牌；因为它带 `autoplay` 标签，`BP_CardFunctions.cpp:12939-12944` 检测到这个标签后调用 `GameStateRef->AddAutoPlayCards(cardID)`，把这张卡加入一个"待自动打出"队列，不是立刻创建动作。
3. `ExecuteAutoPlayCards()`（`BP_PlayerMoves.cpp:850-899`）在稍后的时机处理这个队列，对队列里的每一张卡分别调用 `CreateAction_PlayCardFromHand_Start(...)` → `PlayCardFromHand(...)` → `CreateAction_PlayCardFromHand_End()`（`BP_PlayerMoves.cpp:877-887`）——这是一个跟第 1 步完全独立的、真实的 `XActionPlayCardFromHand` 动作创建。
4. 这次"打出"触发 `OnPlayedFromHand`，进而调用该卡自己的 `GetChooseSpawnCards`，弹出第二个面板（轻/中/重三选一）；玩家选择后，同样通过 `CreateAction_InitStart("XActionCardToDrawSelected", ...)` 创建第三个动作。

也就是说，玩家体验上的"一次预报"，在代码里对应**三个独立的、各自触发一次 `CreateAction_Init` 的动作**（天气类型选择、代表卡自动打出、天气强度选择），每一个都会推进本地计数器——这正是"1 次预报 = 3 个单位"的来源，直接从动作创建链反编译得出，不是外部经验数字。同一回合内，得到第一次预报结果后不做任何其他操作、直接再打出一张预报牌，两次预报合计在本地计数器上消耗 `3 + 3 = 6` 个单位。

NZ33 的代价表（Weather.md §4.1）给出：2K/4K 顺时针跨组代价是 3、每档小组数是 3；6K 顺时针跨组代价是 1、小组数同样是 3。把"6 个单位"代入两边：

- 2K/4K：`6 ÷ 3 = 2` 个小组跨越——3 个小组的环上走 2 步，落在跟起点不同的小组上，所以结果会变。
- 6K：`6 ÷ 1 = 6` 个小组跨越——3 个小组的环上走 6 步，`6 mod 3 = 0`，恰好绕完整整两圈，精确落回起点，所以看起来"没变"。

**6K 不是更难变，而是"连续预报两次"这个具体操作恰好推进了 6 个单位，而 6 正好是 6K 那个环绕一整圈所需单位数（3）的整数倍**——纯粹是这两个数字（连续两次预报的固定消耗量、6K 环的固定周长）巧合对齐的结果。换成连续预报三次（消耗 9 个单位），6K 会变（`9÷1=9`，`9 mod 3=6≠0`），2K/4K 也会变（`9÷3=3`，`3 mod 3=0`，反而 2K/4K 在三次预报后会绕回起点、看起来"不变"）——这个模型能反过来预测这类交叉现象，是它比"候选池大小"或任何其他解释更可取的地方：不需要额外假设，纯粹是已确认代价表数字代入已确认的"一次预报=3单位"这个事实后的算术结果。

## 2. 为什么会存在这个漏洞：确定性重播种 + 玩家可自行控制的本地计数器

三点已确认事实（分别在 README.md §1/§2.2/§2.3 和对应证据文件里有完整推导/抓包证据），合在一起构成了漏洞的完整因果链：

1. `cardsRandomStream` 是公开算法的确定性 `FRandomStream`（线性同余生成器），种子完全决定输出序列，没有任何硬件熵源或不可预测输入。
2. 玩家提交动作前看到的所有预览结果（天气预报三选一、间谍组织实际抽到哪张卡等），用的种子是 `match_id + 本地投机计数器 * 19390`——`match_id` 在对局引导数据里就是明文可见的，本地投机计数器只在玩家自己创建新动作时递增，完全不受对手影响。
3. 玩家自己完全知道、也完全能控制"我这局已经做过多少个动作"——每多做一次任何会创建新动作的操作（哪怕是不花费资源、马上撤销的操作，比如激活一次反制立刻取消——按社区确认，激活反制计一次操作，取消反制本身不计），这个本地计数器就会推进，进而让种子按已知公式前进相应步数。

**这就是漏洞的本质**：预览结果不是"随机"给玩家看的，而是"玩家自己已经做过多少次操作"这个自己完全掌握的数字，经过一个公开、确定性的公式算出来的。只要有人像 NZ33 一样，把"本地计数器取值 → 展示结果"这张映射表实测出来，就能反过来推导："我现在的计数器状态对应哪个结果，想要的结果需要计数器走到哪一步，那我只需要再做相应次数不花费用的空操作（比如反复激活/取消一次不实际使用的反制），就能把预览结果精确调整成我想要的"——这正是社区描述的"挂反制→取消反制，不耗费用地控制天气"打法的完整原理，也是官方公告里承认"存在可以被特定操作序列控制"的这个游戏机制问题的根源。

## 3. "跨越多次操作的可查表规律"（Weather.md 的代价表、SpyRing.md 的环形游走）

驱动预报/间谍组织等预提交阶段就能看到结果的效果的，是本地计数器——只在玩家自己创建新动作时推进（第 2 点的三个动作创建点是直接例子）。KARDS 是回合制游戏，轮到某一方回合时对方不会插入新动作，所以社区"在自己回合内数操作数"的方法论，跟这个本地计数器的实际推进节奏完全对得上，不需要额外假设。Weather.md §4 记录的社区规律里，"指令数大于 3 时 A/B 两档编号同时升一，持续到第 4 次预报"这种"以操作次数分段、超过阈值后行为整体切换"的现象，本质上就是在描述这个本地计数器的某种函数。

## 4. 对局类型覆盖范围

`bUseTurnSwitchValidation` 是服务端随每场对局引导数据下发的值（README.md §2.2 已用 `xrefs_to_field` 排除了客户端硬编码赋值的可能），不是编译进客户端二进制的常量。本报告直接掌握的抓包只有 `match_type: "training"`（人机单机局）两份，均确认该值为 `true`；**PvP 天梯对局同样启用这个开关，已由持有账号、能直接在天梯对局中核实的本项目所有者确认**——也就是说，重播种机制在 PvP 天梯对局下同样是启用状态，跟 `training` 对局一致。因此本报告 §1-3 的全部结论覆盖 `training` 和 PvP 天梯两类对局；唯一仍未覆盖、且没有已知渠道核实的是锦标赛（tournament）等其他赛制，是否有独立于天梯的配置仍是未知。

## 5. 另见

- [README.md](README.md) — 完整机制交叉验证。
- [Weather.md](Weather.md) — 天气规律与 NZ33 确定性代价表。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律与已确认的完整周期。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该开关的证据来源。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — 服务端权威 `action_id` 真实取值规律。
- [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md) — 本地投机计数器 vs 服务端确认编号，两套编号的真实差异（本文档结论的核心证据来源）。
