# KARDS 对局生命周期随机数机制报告

> **现状（2026-08-25）**：本文描述的操纵手法已被服务端调整关闭，具体原理（撤回 `validate_turn_switches` 字段）见 **[RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md)**。

来源：FModel 反编译的蓝图伪代码（`Content/Blueprints/`），交叉验证原生实现（IDA，`kards-Win64-Shipping.exe`）与真实抓包（2026-08-14，`training`/AI 单机对局，抓包内容已脱敏）。以下所有行号均指反编译导出的 `.cpp` 伪代码文件。

> 隐私说明：本仓库已对真实抓包中的 `match_id`、玩家账号 ID 及本机绝对路径做脱敏处理，证据文件中的候选编号等推导数据保留原样；如需按公式逐条复现，需用未脱敏的原始抓包重新计算。

另见 [天气系统](Weather.md)（2K/4K/6K 预报规律）、[间谍组织](SpyRing.md)（环形分布规律）、[社区实测记录](社区实测记录.md)（社区数据，非主证据）与 [evidence/](evidence/)（原始证据文件）。

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

这个函数受 `AMatchControllerV2::bUseTurnSwitchValidation`（native `+0x7A8`）控制。蓝图代码里这个字段只被读取、从未被赋值，原生反汇编里也找不到任何硬编码的赋值指令——它的值由服务端按局下发，客户端通过反射系统写入，不是写死在代码里的常量（完整证据见 [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)）。真实抓包里，对局引导数据末尾明文带着 `"validate_turn_switches":true`：`training`（人机单机）和 PvP 天梯对局都是开启状态，也就是说每次创建/确认一个动作，`cardsRandomStream` 都会被重新播种。2026-08-25 之后这个字段被服务端整体撤回，重播种机制随之停摆，见 [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md)。

有两个调用点：

```cpp
// 调用点 A：BP_OnlineMatch.cpp:9146-9150（本地构造新动作时，用本地预测值）
GetCurrentActionID = MatchController->GetCurrentActionID();
SetRandomStreamWithActionID(GetCurrentActionID);

// 调用点 B：BP_OnlineMatch.cpp:445（服务端确认动作后，用真实回传值）
SetRandomStreamWithActionID(receivedAction.action_id);
```

本地在还没提交动作、`action_id` 还是占位符 `-1` 的阶段，就已经用本地预测的 `GetCurrentActionID()` 抢先重播种（这样天气预报卡面才能在提交前就在 UI 上显示结果）；动作真正提交、服务端确认后，会用真实 `action_id` 再重播种一次。

### 2.3 `action_id` 有三层需要分清：服务端权威序列、JSON 提交包里的字段、真正喂给随机数种子的字段

用真实抓包解密全部提交请求的 `action_id` 字段后确认：**服务端最终确认、双方合并后的权威动作日志，是一条从 1 开始、每次恰好 +1、全程没有重置/跳过/重复的连续整数序列**。完整数据和方法见 [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)。

客户端提交请求 JSON payload 里填的 `action_id` 字段不是这个权威序列，而是一个只数"我方自己已经构造过多少个提交动作"的本地计数器：一份真实对局里，我方提交的 63 个动作，本地填的 `action_id` 就是干净的 `1,2,...,63`，跟服务端确认后的真实编号（逐渐涨到 113-117）相差越来越远。完整数据见 [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)。

**但这个"只数自己"的计数器，反编译确认之后，并不是 `SetRandomStreamWithActionID` 用来重播种的那个字段**：`MatchController_BuildActionJsonPayload`（构造 JSON payload 的原生函数）里，JSON `action_id` 字段来自 `this+3228`（`Counter3228`）；而 `GetCurrentActionID()`／喂给随机数重播种公式的，是另一个字段 `this+3224`（`CurrentActionId`），这个字段由 `GetNextAction_Impl`（本地回放/消化已知动作日志的状态机）推进，推进条件不区分动作属于哪一方——反编译 `MatchController.cpp` 的 `ExecuteUbergraph_MatchController` 蓝图字节码进一步确认，`GetNextAction_Impl` 的消化循环由 `MatchController_C::ActionsReceived()` 这个蓝图事件触发，每次客户端处理完一批服务端轮询回包（不区分回包里是己方还是对方提交的动作）就会把这批里全部尚未处理的动作逐条消化、每条都推进一次 `CurrentActionId`——即它反映的是"本地客户端已经回放过双方合并动作日志里的第几条"，不是纯粹的自计数，这一点已经从蓝图字节码直接确认，不再是推测。这两个字段是否恰好总是数值相等，取决于对局过程中双方动作数是否相等——这是各自推进规则的直接算术推论，完整反编译证据见 [evidence/two-distinct-action-id-counters.md](evidence/two-distinct-action-id-counters.md) 和 [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md)。

社区的操作计数方法论（完整版本见 [社区实测记录](社区实测记录.md) §1）与上面这套字段区分完全自洽：社区统计的是**两次目标效果之间双方全部操作的加权总数**（只有"己方结束回合"计入、"对手结束回合"不计入），而不是"只数自己"。这与 `CurrentActionId` 由 `ActionsReceived` 事件驱动的合并日志回放循环推进、不区分动作归属方的代码行为一致——"只在自己回合内数操作"只是回合制下双方计数退化为单方计数的特例，不是方法论本身。§2.2 提到的"如果本地预测计数器两次触发之间没有正确自增，两次重播种会用同一个 `action_id`"这个解释依然成立，但不能简单理解成"结果会完全冻结"——具体哪一档天气容易看起来不变、哪一档容易变，取决于 ReseedImpact.md §1 的模除运算推导，不是单纯"种子变没变"这个二元判断。

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

服务端确认后回传的动作里，还会附带 `sub_actions`——`Z` 前缀命名（`ZActionChangeKredits`、`ZActionDrawCardFromDeck`、`ZActionDamageCard` 等），是游戏逻辑计算出的连锁效果（战斗伤害、死亡、抽牌、增益），客户端只接收、从不自己构造，字段形状只有蓝图反编译依据。

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
| `BP_CardFunctions.cpp:5265`/`5325` | `GetRandomCard(cards, skipCustomAlways, out randomCard)` | 从一组候选卡里随机取一张（先看是否有 `AlwaysSelectedAsRandom` 标记的子集，优先在子集里随机，否则全体随机）；被多张"随机摧毁/随机选目标"卡复用，例如 [OtherRandomCardEffects.md](OtherRandomCardEffects.md) §2 提到的死神降临/加压舱 |
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
- 服务端最终确认的权威 `action_id` 是双方合并、从 1 开始逐一递增的简单序列；提交前预览所用的种子来自 `CurrentActionId`（本机回放双方合并动作日志的进度游标），与提交 JSON 里的 `Counter3228`（只数己方构造动作）是两个不同的字段（§2.3）。社区按"双方加权操作数"计数的方法论与前者自洽，见 [社区实测记录](社区实测记录.md) §1。

因此：**天气预报、间谍组织、护航攻击等所有依赖 `cardsRandomStream` 的效果，其预览结果从玩家开始操作的那一刻起理论上就是完全确定的，只取决于双方截至当前累计发生过多少个（按社区权重加权的）操作**。这不需要额外假设，是上面三点已确认事实的直接推论。[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 提供了直接实证：两场真实 PvP 对局（休闲模式）里合计 11 次天气预报，玩家实际看到的展示结果全部跟这套公式算出的候选值吻合，零例外。

这正是社区仅凭对局内观察、用统计归纳法就能摸出规律（[社区实测记录](社区实测记录.md) §2/§3 收录的 NZ33 代价表、环形游走与完整周期），乃至据此设计出"零费用控制天气结果"打法的根本原因。

官方已于 2026-08-23 发布《关于秋季锦标赛预报机制的说明》，确认"尝试利用特定操作控制预报机制结果"属实，将其定性为游戏机制层面的问题，而非外挂/作弊（忙活半天结果 1939 说是服务器问题，难蚌）；2026-08-25 发布[后续说明](https://www.kards.com/news/forecast-issue-and-fall-2026-tournament-results)，表示已经对系统做出调整使其更难被操纵、不需要更新客户端，秋季锦标赛成绩维持不变、不追究任何参赛者责任。调整生效后，社区总结的这套操作规律（NZ33 代价表、环形游走等）已经无法稳定复现，本文的重播种公式本身也不能再准确预测结果——原因是服务端撤回了 `validate_turn_switches` 字段，§2.2 描述的"每个动作重播种"分支从此不再触发，`cardsRandomStream` 变成从对局开始起连续自由推进，不再是每次都能从 `match_id`+`CurrentActionId` 精确复现的快照。完整技术推导和真实抓包对照见 [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md)。§1-§6 的静态推导和历史抓包证据本身没有被推翻，作为这套机制曾经可被利用的完整技术记录保留。

## 7. 尚待确认的开放问题（每条都已定性到静态分析能解决/不能解决的边界）

1. **数组下标↔候选变体编号的映射**：已解决（Weather.md §4.2）——`GetChooseSpawnCards` 每个档位的桶里只装 3 个同档位变体，资产名恰好是"无后缀/加2/加3"，字典序排序天然给出下标 0/1/2 对应变体 1/2/3。用这套映射加已确认的 LCG 常数核对社区 NZ33 代价表：`d=15`（同小组）在 light、medium 两档都吻合；`d=3`（顺时针跨组）两档算出的方向相反，跟经验数据矛盾——完整推导见 Weather.md §4.2，这一条矛盾尚未定位到成因。
2. **`_forecastOptions` 何时被清空**：已解决（Weather.md §2.2）——它不需要被清空，因为每次触发预报都是全新创建的卡实例，`_forecastOptions` 天然是空的，反编译到 `selectCardToDraw`/`GetChooseSpawnCards` 的调用链已直接证实。
3. **`bUseTurnSwitchValidation` 的完整历史与 2026-08-25 调整的具体原理**：`training` 和 PvP 天梯在调整前均已确认为 `true`；这个字段来自登录 `/session` 接口下发、由客户端在每局对局请求里原样带上，理论上不分赛制。调整后被整体撤回，导致重播种机制停摆——完整技术推导、未决细节（反射默认值是否确实是 `false`、"连续推进"模型的精确验证）见 [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md)。

## 8. 另见

- [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md) — 2026-08-25 服务端调整的技术原理：`validate_turn_switches` 字段被撤回，重播种机制不再触发。
- [Weather.md](Weather.md) — 天气系统源码实现、档位结构与引擎源码级推导（社区代价表见 社区实测记录.md §2）。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律与已确认的完整周期。
- [OtherRandomCardEffects.md](OtherRandomCardEffects.md) — 护航攻击、反潜巡逻、死神降临、加压舱等结构相同/相近的卡。
- [社区实测记录](社区实测记录.md) — 社区操作计数方法论、NZ33 计算器、社区实测与术语（非主证据，仅供对照）。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该字段命名与真实取值的完整证据链。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — `action_id` 真实取值规律的完整证据链。
- [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md) — 原生 `GetNextAction_Impl` 状态机分析，及其与 `action_id` 分配规则的关系澄清。
- [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) — 两场真实 PvP 休闲模式对局实时抓包，11 次天气预报全部验证已确认公式，附带 `CurrentActionId` 真实取值、`HT` 动作真实确认，以及跟社区操作计数方法论（见 ReseedImpact.md）交叉核对的数据。

---

本文初稿由 Claude 编写，后经 Codex 按反编译源码与官方卡牌索引整理校对。
