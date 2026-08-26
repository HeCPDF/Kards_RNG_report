# KARDS 对局生命周期随机数机制报告

> **适用范围**：本文描述的逐动作重播种机制自 2026-08-25 起已被服务端关闭——服务端不再下发 `validate_turn_switches` 字段，文中公式不能再用来预测当前版本的对局结果。关闭的具体原理与调整前后的抓包逐键对照见 [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md)。以下是这套机制在关闭前如何运作的完整技术记录。

来源与方法：结论以 FModel 反编译的蓝图伪代码（`Content/Blueprints/`）为主线，逐条用 IDA 反编译的原生实现（`kards-Win64-Shipping.exe`）和真实抓包交叉验证。抓包有两批：2026-08-14 的 Fiddler 记录（`training` 人机对局与 PvP 天梯），以及两场 PvP 休闲对局的 mitmproxy 实时解密（[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md)）。全文行号均指本仓库 `FModel-Exports/` 下对应的反编译导出文件。

> 隐私说明：抓包中的 `match_id`、玩家账号 ID 及本机绝对路径已脱敏，证据文件中的候选编号等推导数据保留原样；如需按公式逐条复现，需用未脱敏的原始抓包重新计算。

另见 [天气系统](Weather.md)（2K/4K/6K 预报规律）、[间谍组织](SpyRing.md)（环形分布规律）、[重播种机制的现象解释](ReseedImpact.md)、[社区实测记录](社区实测记录.md)（社区数据，非主证据）与 [evidence/](evidence/)（原始证据文件）。

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

`FRandomStream` 是 Unreal 引擎自带的线性同余生成器（`Engine/Public/Math/RandomStream.h`）：每次取值前先执行 `Seed = Seed * 196314165 + 907633515 (mod 2^32)`，再用变换后 `Seed` 的高 23 位构造 `[0,1)` 区间的浮点数（`GetFraction()`），`RandRange(Min,Max)` 就是 `Min + floor(GetFraction() * (Max-Min+1))`。这套算法在 UE5.6 引擎源码里公开可读；两个 LCG 常数也已用字节搜索在 `kards-Win64-Shipping.exe` 里逐一定位，确认这个 fork 没有修改它们（[Weather.md](Weather.md) §4.2）。

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

这个函数受 `AMatchControllerV2::bUseTurnSwitchValidation`（native `+0x7A8`）控制。该字段在蓝图代码里只被读取、从未被赋值，原生反汇编里对它的写入交叉引用是零命中，说明它的值由服务端按局下发、客户端通过反射系统写入，不是编译进二进制的常量（完整证据见 [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)）。2026-08-14 的抓包里，对局引导数据末尾明文带着 `"validate_turn_switches":true`，`training`（人机单机）和 PvP 天梯对局都是开启状态——也就是说每次创建或确认一个动作，`cardsRandomStream` 都会被重新播种。

有两个调用点：

```cpp
// 调用点 A：BP_OnlineMatch.cpp:9146-9150（本地构造新动作时，用本地预测值）
GetCurrentActionID = MatchController->GetCurrentActionID();
SetRandomStreamWithActionID(GetCurrentActionID);

// 调用点 B：BP_OnlineMatch.cpp:445（服务端确认动作后，用真实回传值）
SetRandomStreamWithActionID(receivedAction.action_id);
```

动作还没提交、`action_id` 仍是占位符 `-1` 的阶段，客户端就已经用本地的 `GetCurrentActionID()` 抢先重播种一次——天气预报卡面能在提交前就把结果显示在 UI 上，靠的就是这一步；动作提交、服务端确认后，再用真实 `action_id` 重播种一次。

### 2.3 三个容易混淆的 `action_id`

"`action_id`"这个词在协议、客户端内存和随机数公式里指的是三个不同的量：

| 名称 | 存放位置 | 语义 | 证据 |
|---|---|---|---|
| 服务端权威动作编号 | 服务端确认并回传的动作日志 | 双方合并后的全局序列，从 1 开始、每次恰好 +1，全程没有重置/跳过/重复 | [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) |
| `Counter3228` | native `AMatchControllerV2+3228`，即提交请求 JSON 里的 `action_id` 字段 | 只数"我方自己已经构造过多少个提交动作" | [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)、[evidence/two-distinct-action-id-counters.md](evidence/two-distinct-action-id-counters.md) |
| `CurrentActionId` | native `AMatchControllerV2+3224`（`+0xC98`），`GetCurrentActionID()` 的返回值 | 本机回放双方合并动作日志的进度游标，即"已经消化到合并日志的第几条" | [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md) |

三者的区别都有直接证据。权威编号连续递增，是把真实抓包里全部提交请求解密后逐条读出来的。`Counter3228` 与权威编号的差距同样是实测的：一份真实对局里我方提交了 63 个动作，JSON 里填的 `action_id` 是干净的 `1,2,...,63`，同期服务端确认的真实编号已经涨到 113–117。

**喂给 `SetRandomStreamWithActionID` 的是第三个，不是提交 JSON 里那个**。原生函数 `MatchController_BuildActionJsonPayload` 构造 JSON 时，`action_id` 字段取自 `this+3228`；而 `GetCurrentActionID()` 读的是 `this+3224`。后者由 `GetNextAction_Impl`（本地回放已知动作日志的状态机）推进，推进条件不区分动作属于哪一方：反编译 `MatchController.cpp` 的 `ExecuteUbergraph_MatchController` 蓝图字节码可见，`GetNextAction_Impl` 的消化循环由蓝图事件 `MatchController_C::ActionsReceived()` 触发，客户端每处理完一批 `/actions` 轮询回包，就把这批里尚未处理的动作逐条消化、每条推进一次 `CurrentActionId`，回包里是己方还是对方的动作都一样。两个计数器是否数值相等，取决于对局中双方动作数是否相等——这是各自推进规则的直接算术推论。

社区统计操作次数的方法与这套字段区分自洽：社区数的是**两次目标效果之间双方全部操作的加权总数**（只有"己方结束回合"计入、"对手结束回合"不计入），不是"只数自己"，正对应 `CurrentActionId` 由合并日志回放推进、不区分归属方的代码行为（权重表见 [社区实测记录](社区实测记录.md) §1）。"只在自己回合内数操作"是回合制下双方计数退化为单方计数的特例，不是方法论本身。

由此可直接读出一个推论：如果两次触发效果之间 `CurrentActionId` 没有推进，两次重播种会用同一个种子。但这不等于"结果一定完全冻结"——具体哪一档天气容易看起来不变、哪一档容易变，取决于 [ReseedImpact.md](ReseedImpact.md) §2 的循环长度推导。

## 3. 动作类型与提交流程

来源：对 KARDS REST 协议的重建，并用真实抓包交叉验证。这部分不是本文主题，但直接支撑上面"动作编号如何推进"的结论。

### 3.1 有哪些动作类型

客户端提交动作走 `POST /matches/v2/<match_id>/actions`，请求体是一个加密包，解密后的明文 JSON 是 `{"action_type", "player_id", "action_data", "action_id"}`。已确认的 `action_type` 取值：

| 全称 | 简写（提交时用） | 作用 |
|---|---|---|
| `XStartOfGame` | — | 对局的第一个动作，`action_id` 必须是 1，在提交 mulligan 之前抢先提交 |
| `XActionStartOfTurn` | — | 一方回合开始 |
| `XActionPlayCardFromHand` | `PC` | 出牌 |
| `XActionAttackCard` | `AC` | 攻击 |
| `XActionMoveCardToLine` | `ML` | 支援线推进到前线 |
| `XActionHandTargetSelected` | `HT` | 延迟目标选择的第二步提交，载荷为 `{"0":触发卡牌ID,"1":选中目标ID}`；格式由蓝图反编译给出，并已在真实对局抓包中确认（[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md)） |
| `XActionCardToDrawSelected` | `CS` | "抽/生成 N 选 1"效果的选择结果；真实抓包在预报流程中观察到连续出现两个 `CS`（[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md)） |
| `XActionEndOfTurn` | — | 一方回合结束，`reason` 字段已知取值：`"endTurnButton"`（真人点结束回合）、`"timeout"`（计时器到点自动提交）、`"forced"`（被卡牌效果强制结束） |
| `XActionMulligan` | — | 起手换牌 |
| `ActionEndMatch` | — | 对局结束（走 `PUT /matches/v2/<id>`，不是 `/actions`） |
| `XActionCheat` / `ActionNewDeck` | — | 已确认存在，具体触发条件未验证 |

服务端确认后回传的动作里还会附带 `sub_actions`——`Z` 前缀命名（`ZActionChangeKredits`、`ZActionDrawCardFromDeck`、`ZActionDamageCard` 等），是游戏逻辑算出的连锁效果（战斗伤害、死亡、抽牌、增益），客户端只接收、从不自己构造。这类字段的形状只有蓝图反编译一个来源。

### 3.2 一个真实回合的完整序列

以下取自 2026-08-14 抓包逐条解密的结果：

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

固定模式是：`XActionStartOfTurn` → 0 个或多个 `PC`/`AC`/`ML` → `XActionEndOfTurn`，双方交替，直到 `ActionEndMatch`。权威编号严格连续递增、双方共用同一条序列，完整数据见 [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)。

### 3.3 提交用计数器在客户端本地怎么推进

抓包观察到的行为是：客户端本地维护一个提交用整数，对局引导数据返回后初始化为引导数据里的 `current_action_id + 1`（新对局是 `0+1=1`，与抓包里首个提交的 `action_id=1` 一致），每提交一次动作就直接使用当前值、随后自增 1；轮询到服务端确认的动作后，用确认动作里的最大编号 `+1` 校准这个计数器，防止本地与服务端因为对手动作而错位。

这个提交用计数器就是 §2.3 表里的 `Counter3228`，不是喂给随机数重播种公式的 `CurrentActionId`。

## 4. `cardsRandomStream` 的已知消费点

**卡牌自身效果触发的消费点**（玩家打出某张具体卡时才会走到）：

| 位置 | 函数 | 用途 |
|---|---|---|
| `BP_CardFunctions.cpp:5265`/`5325` | `GetRandomCard(cards, skipCustomAlways, out randomCard)` | 从一组候选卡里随机取一张（先看是否有 `AlwaysSelectedAsRandom` 标记的子集，优先在子集里随机，否则全体随机）；被多张"随机摧毁/随机选目标"卡复用，例如 [OtherRandomCardEffects.md](OtherRandomCardEffects.md) §2 的死神降临、加压舱 |
| `BP_CardFunctions.cpp:5422`/`5605` | 未定位到调用它的外层函数名 | `Array_ShuffleFromStream`，打乱 `oppositeSideUnseenCards`/`possibleChooseCards`（对方未见卡池/候选选择池） |
| `BP_CardFunctions.cpp:6618` | `SpawnCardInDeckBySide(side, card_name, spawnerID, ..., RandomWithoutShuffle, ...)` | "把卡生成到牌库"类效果的通用实现——`RandomWithoutShuffle` 为真时，直接用 `RandomIntegerInRangeFromStream(0, 牌库长度)` 算出插入位置，不整体洗牌 |
| `BP_CardFunctions.cpp:22523`（`22621` 是内部调用点） | `GiveRandomCombatKeyword(cardID, instigatorID, out keywordGiven, out success)` | 从一个战斗关键词 Set 转数组后随机取一个赋予目标单位 |
| `card_event_storm1_gale.cpp:148/156/164`（及 sunny/rain 系列同构文件） | `GetChooseSpawnCards` | 天气预报：依次从 light/medium/heavy 三个候选池各抽一张，顺序固定 |
| `card_event_spy_ring.cpp` | `ExecuteUbergraph_card_event_spy_ring` | 间谍组织：一次 `[0,4]` 抽签，映射到 5 张国家研究卡之一 |
| `card_event_convoy_attack.cpp` | `ExecuteUbergraph_card_event_convoy_attack` | 护航攻击：一次 `[0,2]` 抽签，直接作为伤害数值 |

**不依赖具体某张卡、由游戏系统/模式本身触发的消费点**：

| 位置 | 函数 | 用途 |
|---|---|---|
| `BP_CardFunctions.cpp:12365` | `ShuffleDeckBySide(sideToShuffle, ...)` | 洗牌，用 `Array_ShuffleFromStream` 打乱 `localDeckCardIDs`（是否是权威洗牌、还是仅本地校验，未确认） |
| `BP_SkirmishMode.cpp:2379/2391/2413/2435` | 未定位到外层函数名（涉及 `brawlCard` 局部变量，推测属于"混战"/Brawl 模式） | 单位被摧毁后从 `possible_attacker_spawn`/`possible_defender_spawn` 候选池里随机挑一个生成替代单位——这是本文确认的消费点里唯一不挂在具体卡牌效果上、而由游戏模式逻辑触发的一处 |

`encryptionStream` 只确认一个消费点：`BP_CardFunctions.cpp:13932`，`RandomIntegerInRangeFromStream(encryptionStream, 10000, 1000000)` 生成卡牌数值反作弊 XOR 密钥，跟对局结果无关。

> 这张表由 `Content/Blueprints/` 全目录搜索 `RandomIntFromRangeWithStream`/`RandomIntegerInRangeFromStream`/`Array_ShuffleFromStream`/`cardsRandomStream` 的字面出现位置得出，覆盖蓝图层全部消费点；原生 C++ 侧是否还有蓝图看不到的消费点无法排除（跟 `bUseTurnSwitchValidation` 一样，蓝图导出只能看到蓝图能看到的部分）。`Content/Blueprints/Effects/` 下的大量 `RandomFloat`/`RandomIntegerInRange` 调用（坦克炮口烟雾、树叶摆动、探照灯等）走 UE 全局的未播种 RNG，属于纯视觉表现层，不在表内。

## 5. 结论：天气预报、间谍组织等"随机"效果是确定性序列

把前四节和抓包证据合起来：

- `cardsRandomStream` 是以 `match_id` 为种子的确定性 `FRandomStream`，算法与常数公开（§1）。
- 抓包确认的对局里 `bUseTurnSwitchValidation` 开启，每次动作都会把它重播种为 `match_id + CurrentActionId*19390`（§2.2）。
- 提交前预览所用的种子来自 `CurrentActionId`，即本机回放双方合并动作日志的进度游标；它与提交 JSON 里的 `Counter3228`、与服务端权威编号都是不同的量（§2.3）。

因此：**天气预报、间谍组织、护航攻击等所有依赖 `cardsRandomStream` 的效果，其预览结果从玩家开始操作的那一刻起就是确定的，只取决于双方截至当前累计发生过多少个（按社区权重加权的）操作**。

这一点有直接实证：[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 记录的两场真实 PvP 休闲对局里合计 11 次天气预报，玩家实际看到的展示结果全部落在这套公式算出的候选值内，零例外。社区仅凭对局内观察、用统计归纳就能摸出规律（[社区实测记录](社区实测记录.md) §2、§3 收录的 NZ33 代价表、环形游走与完整周期），乃至据此设计出"零费用控制天气结果"的打法，根源就在这里。这套机制为什么构成一个可被利用的漏洞、玩家具体怎么利用，见 [ReseedImpact.md](ReseedImpact.md) §3。

官方于 2026-08-23 发布《关于秋季锦标赛预报机制的说明》，确认"尝试利用特定操作控制预报机制结果"属实，定性为游戏机制层面的问题而非外挂/作弊；2026-08-25 发布[后续说明](https://www.kards.com/news/forecast-issue-and-fall-2026-tournament-results)，表示已对系统做出调整使其更难被操纵、不需要更新客户端，秋季锦标赛成绩维持不变、不追究任何参赛者责任。

调整生效后，社区总结的这套操作规律（NZ33 代价表、环形游走等）已经无法稳定复现，本文的重播种公式也不能再准确预测结果：服务端撤回了 `validate_turn_switches` 字段，§2.2 的重播种分支不再触发，`cardsRandomStream` 从对局开始那一次播种起连续自由推进，不再是每个动作都能用 `match_id`+`CurrentActionId` 精确复现的快照。完整技术推导和调整前后的抓包对照见 [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md)。§1–§5 的静态推导和抓包证据本身不受影响，作为这套机制曾经如何运作的技术记录保留。

## 6. 尚待确认的开放问题

1. **社区 NZ33 代价表里"跨组代价"一项对不上**：下标↔候选变体编号的映射已经确定（资产名"无后缀/加 2/加 3"在字典序下依次对应下标 0/1/2，推导见 Weather.md §4.2）。用这套映射加已确认的 LCG 常数核对代价表，`d=15`（同小组）在 light、medium 两档都吻合，`d=3`（顺时针跨组）两档算出的方向却相反，与经验数据矛盾。矛盾成因未定位，完整推导见 Weather.md §4.2、§5.1。
2. **一次预报究竟消耗几个计数单位**：真实抓包只能确认下限为 2（类型选择、强度选择各一个 `CS` 提交），一级代表卡 `autoplay` 自动打出这一步是否单独计数尚不确定，需要受控测试核实（Weather.md §2.3）。
3. **2026-08-25 调整的两处细节**：`bUseTurnSwitchValidation` 这个 `bool` 的反射默认值是否确实是 `false`，以及"重播种停止后 `cardsRandomStream` 连续推进"这个模型能否精确复现观测到的结果——两条都还没有直接证据，现状与所需数据见 [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md) §7。

## 7. 另见

- [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md) — 2026-08-25 服务端调整的技术原理：`validate_turn_switches` 字段被撤回，重播种机制不再触发。
- [Weather.md](Weather.md) — 天气系统源码实现、档位结构与引擎源码级推导。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律与已确认的完整周期。
- [ReseedImpact.md](ReseedImpact.md) — 重播种机制如何逐条解释每一个已观察到的现象，以及漏洞的完整因果链。
- [OtherRandomCardEffects.md](OtherRandomCardEffects.md) — 护航攻击、反潜巡逻、死神降临、加压舱等结构相同/相近的卡。
- [社区实测记录](社区实测记录.md) — 社区操作计数方法论、NZ33 计算器、社区实测与术语（非主证据，仅供对照）。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该字段命名与真实取值的完整证据链。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — 服务端权威动作编号真实取值规律的完整证据链。
- [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md) — 提交用计数器与服务端确认编号的真实差异。
- [evidence/two-distinct-action-id-counters.md](evidence/two-distinct-action-id-counters.md) — `Counter3228` 与 `CurrentActionId` 是两个不同原生字段的反编译证据。
- [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md) — `GetNextAction_Impl` 状态机分析，及其与动作编号分配规则的关系。
- [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) — 两场真实 PvP 休闲对局的实时抓包：11 次天气预报全部验证已确认公式，附带 `CurrentActionId` 真实取值、`HT` 动作确认，以及与社区操作计数方法论的交叉核对数据。
