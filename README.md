# KARDS 对局生命周期随机数机制报告

来源：FModel 反编译的蓝图伪代码（`Content/Blueprints/`），交叉验证原生实现（IDA，`kards-Win64-Shipping.exe`）与真实抓包（2026-08-14，`training`/AI 单机对局，抓包内容已脱敏）。以下所有行号均指反编译导出的 `.cpp` 伪代码文件。

> 隐私说明：本仓库已对真实抓包中的 `match_id`、玩家账号 ID 及本机绝对路径做脱敏处理，证据文件中的候选编号等推导数据保留原样；如需按公式逐条复现，需用未脱敏的原始抓包重新计算。

本文初稿由 Claude 编写，后经 Codex 按反编译源码与官方卡牌索引整理校对。另见 [天气系统](Weather.md)（2K/4K/6K 预报规律）、[间谍组织](SpyRing.md)（环形分布规律）、[社区观察记录](CommunityObservations.md)（社区数据，非主证据）与 [evidence/](evidence/)（原始证据文件）。

## 1. 核心随机流对象

游戏里跟对局结果相关的随机数几乎全部经过两个 `FRandomStream` 实例，都挂在 `BP_CardFunctions`（`cardFunctions`）这个单例上：

```cpp
// BP_CardFunctions.cpp:7-14
struct FRandomStream cardsRandomStream = { InitialSeed: 0, Seed: 0 };
struct FRandomStream encryptionStream  = { InitialSeed: 0, Seed: 0 };
```

- `cardsRandomStream`：驱动几乎所有真正影响对局结果的随机数（洗牌、天气预报、AI/效果的随机选卡等）。
- `encryptionStream`：驱动卡牌数值反作弊 XOR 加密的密钥生成，跟对局结果无关。

两者共享同一套播种时机——每次重新播种时，`encryptionStream` 都被直接赋值为 `cardsRandomStream` 播种后的状态：

```cpp
// BP_CardFunctions.cpp:12339-12347
public void SetRandomStreamByMatchID(int MatchID) {
    cardsRandomStream = UKismetMathLibrary::MakeRandomStream(MatchID);
    encryptionStream = cardsRandomStream;
}
```

`FRandomStream` 本身是 Unreal 引擎的线性同余生成器（`Engine/Public/Math/RandomStream.h`）：每次取值前先执行 `Seed = Seed * 196314165 + 907633515 (mod 2^32)`，再用变换后 `Seed` 的高 23 位构造 `[0,1)` 区间的浮点数（`GetFraction()`），`RandRange(Min,Max)` 就是 `Min + floor(GetFraction() * (Max-Min+1))`。这是一份公开的、可以在 UE5.6 引擎源码里直接读到的确定性算法，没有任何隐藏成分。

## 2. 播种：对局开始播一次，此后每个动作都重播种

### 2.1 对局初始化：用 `match_id` 播种一次

```cpp
// BP_OnlineMatch.cpp:1734-1744
cardFunctions->SetRandomStreamByMatchID(Match.match_id);
cardFunctions->InitializeSideEffectHolders();
GameStateRef->InitialKreditAndSlotEncryption();
```

### 2.2 每个动作都重播种为 `match_id + action_id * 19390`

```cpp
// BP_OnlineMatch.cpp:24520-24536
private void SetRandomStreamWithActionID(int inputActionID) {
    if (!GetMatchController->bUseTurnSwitchValidation)
        return;
    int seed = Match.match_id + inputActionID * 19390;
    cardFunctions->SetRandomStreamByMatchID(seed);
}
```

这个函数受 `AMatchControllerV2::bUseTurnSwitchValidation`（native `+0x7A8`）控制。蓝图代码里这个字段只被读取、从未被赋值；原生反汇编里也找不到任何硬编码的赋值指令（`xrefs_to_field` 查询返回零结果）——真正的原因是这个值由服务端按局下发，客户端通过反射系统写入，不是写死在代码里的常量。**真实抓包已经直接确认了下发的值**：对局引导数据（bootstrap）末尾明文带着 `"validate_turn_switches":true`，字段名跟这个原生属性高度对应。也就是说，在真实的 `training`（人机单机）对局里，这个重播种分支**是开启的**——每次创建/确认一个动作，`cardsRandomStream` 都会被重新播种。完整证据见 [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)。PvP 天梯对局同样开启该开关（由持有账号的本项目所有者直接核实）；锦标赛等其他赛制是否配置不同仍未覆盖，见 §7。

有两个调用点：

```cpp
// 调用点 A：BP_OnlineMatch.cpp:9146-9150（本地构造新动作时，用本地预测值）
GetCurrentActionID = MatchController->GetCurrentActionID();
SetRandomStreamWithActionID(GetCurrentActionID);

// 调用点 B：BP_OnlineMatch.cpp:445（服务端确认动作后，用真实回传值）
SetRandomStreamWithActionID(receivedAction.action_id);
```

本地在还没提交动作、`action_id` 还是占位符 `-1` 的阶段，就已经用本地预测的 `GetCurrentActionID()` 抢先重播种（这样天气预报卡面才能在提交前就在 UI 上显示结果）；动作真正提交、服务端确认后，会用真实 `action_id` 再重播种一次。如果本地预测计数器在两次触发之间没有正确自增（比如没有走完一次完整的"创建→提交→确认"闭环），两次重播种会用同一个 `action_id`、种子完全相同，结果自然一样——这解释了"同回合内第二次开发结果一样"这个现象。

### 2.3 `action_id` 有三层需要分清：服务端权威序列、JSON 提交包里的字段、真正喂给随机数种子的字段

用真实抓包解密全部提交请求的 `action_id` 字段后确认：**服务端最终确认、双方合并后的权威动作日志，是一条从 1 开始、每次恰好 +1、全程没有重置/跳过/重复的连续整数序列**。完整数据和方法见 [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)。

客户端提交请求 JSON payload 里填的 `action_id` 字段不是这个权威序列，而是一个只数"我方自己已经构造过多少个提交动作"的本地计数器：一份真实对局里，我方提交的 63 个动作，本地填的 `action_id` 就是干净的 `1,2,...,63`，跟服务端确认后的真实编号（逐渐涨到 113-117）相差越来越远。完整数据见 [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)。

**但这个"只数自己"的计数器，反编译确认之后，并不是 `SetRandomStreamWithActionID` 用来重播种的那个字段**：`MatchController_BuildActionJsonPayload`（构造 JSON payload 的原生函数）里，JSON `action_id` 字段来自 `this+3228`（`Counter3228`）；而 `GetCurrentActionID()`／喂给随机数重播种公式的，是另一个字段 `this+3224`（`CurrentActionId`），这个字段由 `GetNextAction_Impl`（本地回放/消化已知动作日志的状态机）推进，推进条件不区分动作属于哪一方——反编译 `MatchController.cpp` 的 `ExecuteUbergraph_MatchController` 蓝图字节码进一步确认，`GetNextAction_Impl` 的消化循环由 `MatchController_C::ActionsReceived()` 这个蓝图事件触发，每次客户端处理完一批服务端轮询回包（不区分回包里是己方还是对方提交的动作）就会把这批里全部尚未处理的动作逐条消化、每条都推进一次 `CurrentActionId`——即它反映的是"本地客户端已经回放过双方合并动作日志里的第几条"，不是纯粹的自计数，这一点已经从蓝图字节码直接确认，不再是推测。这两个字段是否恰好总是数值相等，取决于对局过程中双方动作数是否相等——这是各自推进规则的直接算术推论，完整反编译证据见 [evidence/two-distinct-action-id-counters.md](evidence/two-distinct-action-id-counters.md) 和 [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md)。

社区的操作计数方法论（完整版本见 [CommunityObservations.md](CommunityObservations.md) §1）与上面这套字段区分完全自洽：社区统计的是**两次目标效果之间双方全部操作的加权总数**（只有"己方结束回合"计入、"对手结束回合"不计入），而不是"只数自己"。这与 `CurrentActionId` 由 `ActionsReceived` 事件驱动的合并日志回放循环推进、不区分动作归属方的代码行为一致——"只在自己回合内数操作"只是回合制下双方计数退化为单方计数的特例，不是方法论本身。§2.2 提到的"如果本地预测计数器两次触发之间没有正确自增，两次重播种会用同一个 `action_id`"这个解释依然成立，但不能简单理解成"结果会完全冻结"——具体哪一档天气容易看起来不变、哪一档容易变，取决于 ReseedImpact.md §1 的模除运算推导，不是单纯"种子变没变"这个二元判断。

## 3. 动作类型与提交流程

来源：对 KARDS REST 协议的重建（非本报告主题，但直接支撑上面"`action_id` 如何推进"的结论），并用真实抓包交叉验证。

### 3.1 有哪些动作类型

客户端提交动作走 `POST /matches/v2/<match_id>/actions`，请求体是一个加密包，解密后的明文 JSON 是 `{"action_type", "player_id", "action_data", "action_id"}`。已确认的 `action_type` 取值：

| 全称 | 简写（提交时用） | 作用 |
|---|---|---|
| `XStartOfGame` | — | 对局的第一个动作，`action_id` 必须是 1，在提交 mulligan 之前抢先提交 |
| `XActionStartOfTurn` | — | 一方回合开始 |
| `PC`（`XActionPlayCardFromHand`） | `PC` | 出牌 |
| `AC`（`XActionAttackCard`） | `AC` | 攻击 |
| `ML`（`XActionMoveCardToLine`） | `ML` | 支援线推进到前线 |
| `HT`（`XActionHandTargetSelected`） | `HT` | 延迟目标选择的第二步提交（已由真实对局抓包确认，见 [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md)：`{"0":触发卡牌ID,"1":选中目标ID}`，格式与蓝图反编译预期一致） |
| `CS`（`XActionCardToDrawSelected`） | `CS` | "抽/生成 N 选 1"效果的选择结果（真实抓包已观察到预报流程中连续出现两个 `CS`，见 [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md)） |
| `XActionEndOfTurn` | — | 一方回合结束，`reason` 字段已知取值：`"endTurnButton"`（真人点结束回合）、`"timeout"`（计时器到点自动提交）、`"forced"`（被卡牌效果强制结束） |
| `XActionMulligan` | — | 起手换牌 |
| `ActionEndMatch` | — | 对局结束（走 `PUT /matches/v2/<id>`，不是 `/actions`） |
| `XActionCheat` / `ActionNewDeck` | — | 已知存在，具体触发条件未深入验证 |

服务端确认后回传的动作里，还会附带 `sub_actions`——`Z` 前缀命名（`ZActionChangeKredits`、`ZActionDrawCardFromDeck`、`ZActionDamageCard` 等），是游戏逻辑计算出的连锁效果（战斗伤害、死亡、抽牌、增益），客户端只接收、从不自己构造。两份真实抓包目前都没有捕捉到带 `sub_actions` 的完整确认回包（可能是轮询时机没对上），这部分内容目前只有蓝图反编译依据，未经真实数据交叉验证。

### 3.2 一个真实回合的完整序列（真实抓包，逐条解密确认）

```
XStartOfGame           action_id=1
XActionStartOfTurn     action_id=2
PC                     action_id=3
XActionEndOfTurn       action_id=4
XActionStartOfTurn     action_id=5
ML                     action_id=6
XActionEndOfTurn       action_id=7
...
```

固定模式是：`XActionStartOfTurn` → 0 个或多个 `PC`/`AC`/`ML` → `XActionEndOfTurn`，双方交替，直到 `ActionEndMatch`。`action_id` 严格连续递增，双方共用同一条序列——具体证据和完整数据见 [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)。

### 3.3 `action_id` 在客户端本地是怎么推进的

真实抓包观察到的行为是：客户端本地维护一个提交用整数，对局引导数据返回后初始化为引导数据里的 `current_action_id + 1`（新对局是 `0+1=1`，与真实抓包首个提交的 `action_id=1` 一致），每提交一次动作就直接使用当前值、随后自增 1；轮询到服务端确认的动作后，用确认动作里的最大 `action_id + 1` 校准本地计数器（防止本地/服务端计数器因为对手动作而错位）。需要强调的是：这个提交用计数器对应的是原生 `Counter3228`（JSON 里的 `action_id` 字段），不是喂给随机数重播种公式的 `CurrentActionId`（`AMatchControllerV2+0xC98`）——后者由 `GetNextAction_Impl` 回放合并动作日志推进，语义见 [evidence/two-distinct-action-id-counters.md](evidence/two-distinct-action-id-counters.md) 与 [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md)。

## 5. `cardsRandomStream` 的已知消费点

**卡牌自身效果触发的消费点**（玩家打出某张具体卡时才会走到）：

| 位置 | 函数 | 用途 |
|---|---|---|
| `BP_CardFunctions.cpp:5265`/`5325` | `GetRandomCard(cards, skipCustomAlways, out randomCard)` | 从一组候选卡里随机取一张（先看是否有 `AlwaysSelectedAsRandom` 标记的子集，优先在子集里随机，否则全体随机）；被多张"随机摧毁/随机选目标"卡复用，例如 [SpyRing.md](SpyRing.md) §7 提到的死神降临/加压舱 |
| `BP_CardFunctions.cpp:5422`/`5605` | 未定位到调用它的具体外层函数名 | `Array_ShuffleFromStream`，打乱 `oppositeSideUnseenCards`/`possibleChooseCards`（对方未见卡池/候选选择池） |
| `BP_CardFunctions.cpp:6618` | `SpawnCardInDeckBySide(side, card_name, spawnerID, ..., RandomWithoutShuffle, ...)` | "把卡生成到牌库"类效果的通用实现——`RandomWithoutShuffle` 为真时，直接用 `RandomIntegerInRangeFromStream(0, 牌库长度)` 算出插入位置，不整体洗牌 |
| `BP_CardFunctions.cpp:22523`（`22621` 是内部调用点） | `GiveRandomCombatKeyword(cardID, instigatorID, out keywordGiven, out success)` | 从一个战斗关键词 Set 转数组后随机取一个赋予目标单位 |
| `card_event_storm1_gale.cpp:148/156/164`（及 sunny/rain 系列同构文件） | `GetChooseSpawnCards` | 天气预报：依次从 light/medium/heavy 三个候选池各抽一张，顺序固定 |
| `card_event_spy_ring.cpp` | `ExecuteUbergraph_card_event_spy_ring` | 间谍组织：一次 `[0,4]` 抽签，映射到 5 张国家研究卡之一 |
| `card_event_convoy_attack.cpp` | `ExecuteUbergraph_card_event_convoy_attack` | 护航攻击：一次 `[0,2]` 抽签，直接作为伤害数值 |

**不依赖具体某张卡、由游戏系统/模式本身触发的消费点**：

| 位置 | 函数 | 用途 |
|---|---|---|
| `BP_CardFunctions.cpp:12365` | `ShuffleDeckBySide(sideToShuffle, ...)` | 洗牌，用 `Array_ShuffleFromStream` 打乱 `localDeckCardIDs`（是否是权威洗牌、还是仅本地校验，尚未确认） |
| `BP_SkirmishMode.cpp:2379/2391/2413/2435` | 未定位到外层函数名（涉及 `brawlCard` 局部变量，推测是"混战"/Brawl 模式的逻辑） | 某个游戏模式下，单位被摧毁后从 `possible_attacker_spawn`/`possible_defender_spawn` 候选池里随机挑一个生成替代单位——**这是本报告目前唯一确认的、不挂在任何具体卡牌效果上、而是游戏模式本身逻辑触发的 `cardsRandomStream` 消费点** |

`encryptionStream` 只确认一个消费点：`BP_CardFunctions.cpp:13932`，`RandomIntegerInRangeFromStream(encryptionStream, 10000, 1000000)` 生成卡牌数值反作弊 XOR 密钥，跟对局结果无关。

> `Content/Blueprints/Effects/`（坦克炮口烟雾、树叶摆动、探照灯等）下的大量 `RandomFloat`/`RandomIntegerInRange` 调用走 UE 全局（未播种、非确定性）RNG，纯视觉表现层，跟本文无关，不列出。这份表格是从 `Content/Blueprints/` 全目录搜索 `RandomIntFromRangeWithStream`/`RandomIntegerInRangeFromStream`/`Array_ShuffleFromStream`/`cardsRandomStream` 字面出现位置得到的，理论上覆盖了蓝图层全部消费点；但不能排除原生 C++ 侧还有蓝图看不到的额外消费点（跟 `bUseTurnSwitchValidation` 一样，蓝图导出只能看到蓝图能看到的部分）。

## 6. 结论：天气预报、间谍组织等"随机"效果是确定性序列

把第 1-3 节和真实抓包证据放在一起：

- `cardsRandomStream` 是以 `match_id` 为种子的确定性 `FRandomStream`，算法公开（§1）。
- 真实对局里 `bUseTurnSwitchValidation` 开启，每次动作都会把它重播种为 `match_id + CurrentActionId*19390`（§2.2）。
- 服务端最终确认的权威 `action_id` 是双方合并、从 1 开始逐一递增的简单序列；提交前预览所用的种子来自 `CurrentActionId`（本机回放双方合并动作日志的进度游标），与提交 JSON 里的 `Counter3228`（只数己方构造动作）是两个不同的字段（§2.3）。社区按"双方加权操作数"计数的方法论与前者自洽，见 [CommunityObservations.md](CommunityObservations.md) §1。

因此：**天气预报、间谍组织、护航攻击等所有依赖 `cardsRandomStream` 的效果，其预览结果从玩家开始操作的那一刻起理论上就是完全确定的，只取决于双方截至当前累计发生过多少个（按社区权重加权的）操作**。这不需要额外假设——是这三点已确认事实的直接推论。

这正是社区仅凭对局内观察、用统计归纳法就能摸出规律（[CommunityObservations.md](CommunityObservations.md) §2/§3 收录的 NZ33 代价表、环形游走与完整周期），乃至据此设计出"零费用控制天气结果"打法的根本原因。官方已于 2026-08-23 发布《关于秋季锦标赛预报机制的说明》，确认"尝试利用特定操作控制预报机制结果"属实，将其定性为游戏机制层面的问题，而非外挂/作弊；截至该说明发布，尚未给出具体修复方案或补偿。

**已证明**（Weather.md §4.2）：NZ33"2K 和 4K 代价完全相同"这条经验数据，如果套用"三次连续调用的原始返回下标固定对应 light=第1次/medium=第2次变换深度"这个最直接的模型，用已经字节级确认的 LCG 公式代入计算，数学上不可能产生（`A^1 mod 2^32 ≠ A^2 mod 2^32`，无巧合可能，进一步用具体数值算出两档档位各自的"同小组代价"最小值点确实不同，分别是 15 和 3）——这是证明，不是推测；候选数组下标↔NZ33 小组编号的映射关系本身已经解决（同一份 §4.2 反编译出排序比较函数是标准字典序字符串比较，加上桶内候选资产名恰好是"无后缀/2/3"，字典序天然给出下标 0/1/2 = 小组 1/2/3，不需要运行时数据）。"结果是确定性的、原则上可预测"这一层，除了 §1-§3 的重播种公式+本地计数器机制的静态推导外，现在还有 [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 的直接实证：两场真实 PvP 对局（休闲模式）里合计 11 次天气预报，玩家实际看到的展示结果全部跟这套确认公式算出的候选值吻合，零例外。

## 7. 尚待确认的开放问题（每条都已定性到静态分析能解决/不能解决的边界）

1. **`action_id` → 具体展示结果的精确映射公式**：数组下标↔小组编号的映射本身**已完全解决**（Weather.md §4.2）——`GetAllStaticCardsSortedByName` 的排序比较函数（`sub_141376EA0`）反编译确认是标准的、不区分大小写的 `FName` 字典序比较，`GetChooseSpawnCards` 的填桶逻辑确认每个磁级的桶只装同类型同磁级的 3 个小组变体，三者资产名恰好是"无后缀/加2/加3"，字典序天然给出下标 0/1/2 = 小组 1/2/3，不需要任何运行时数据。进一步用已确认的 LCG 常数精确计算、并排查了"前端交互时序改变变换深度"这个候选解释（反编译 `HandleSelectCardToDrawPending`→`AddSubActionSelectCardToDrawPending` 调用链确认弹窗通知是一次性的、非交互式的，排除了这个解释）后，剩下的矛盾——社区数据中"2K/4K 代价表完全相同"（[CommunityObservations.md](CommunityObservations.md) §2.1）跟已确认引擎机制算出的具体数字（light 档 15 步、medium 档 3 步）对不上——已经缩小到只剩一种可能来源：NZ33 计算器自身原始测试数据的精确度，本报告没有渠道独立核实这份第三方社区数据，这是数据来源本身的边界，不是反编译深度或方法的问题。
2. **`_forecastOptions` 何时被清空**：已解决（Weather.md §2.2）——它不需要被清空，因为每次触发预报都是全新创建的卡实例，`_forecastOptions` 天然是空的，反编译到 `selectCardToDraw`/`GetChooseSpawnCards` 的调用链已直接证实。
3. **`Array_ShuffleFromStream(localDeckCardIDs, ...)` 客户端洗牌是否权威**：本报告的反编译范围内没有找到能确认"服务端另有一套权威洗牌"或"客户端洗牌即最终牌序"的直接证据；这类问题本质是"服务端内部实现是什么"，服务端代码不在本报告的静态分析范围内（游戏客户端二进制不包含服务端逻辑），无法通过反编译客户端解决，需要抓包比对客户端预测牌序与服务端实际发牌结果才能确认。
4. **`bUseTurnSwitchValidation` 在 PvP/天梯/锦标赛下的取值**：`training` 和 PvP 天梯均已确认为 `true`（`training` 两份抓包直接证实；PvP 天梯已由持有账号的本项目所有者直接核实确认）——重播种机制在这两类对局下都是启用的。锦标赛等其他赛制是否有独立配置仍是未知，没有已知渠道核实，需要那类赛制的真实抓包或直接确认才能补齐。
5. `HT`/`CS` 的动作类型与字段形状已由真实抓包确认（`HT` 见 [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 副产品发现 2；`CS` 在预报流程中连续出现），但 `sub_actions` 的完整字段形状仍只有蓝图反编译依据。

## 8. 另见

- [Weather.md](Weather.md) — 天气系统源码实现、档位结构与引擎源码级推导（社区代价表见 CommunityObservations.md §2）。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律、已确认的 18 次操作完整周期、护航攻击等结构相同的卡。
- [CommunityObservations.md](CommunityObservations.md) — 社区操作计数方法论、NZ33 计算器、社区实测与术语（非主证据，仅供对照）。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该字段命名与真实取值的完整证据链。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — `action_id` 真实取值规律的完整证据链。
- [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md) — 原生 `GetNextAction_Impl` 状态机分析，及其与 `action_id` 分配规则的关系澄清。
- [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) — 两场真实 PvP 休闲模式对局实时抓包，11 次天气预报全部验证已确认公式，附带 `CurrentActionId` 真实取值、`HT` 动作真实确认，以及跟社区操作计数方法论（见 ReseedImpact.md）交叉核对的数据。
