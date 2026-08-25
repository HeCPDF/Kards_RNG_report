# KARDS 对局生命周期随机数机制报告

来源：FModel 反编译的蓝图伪代码（`Content/Blueprints/`），交叉验证原生实现（IDA，`kards-Win64-Shipping.exe`）与真实抓包（`本地抓包目录/`，2026-08-14，`training`/AI 单机对局，经项目自带 `_codec.py` 解密）。以下所有行号均指反编译导出的 `.cpp` 伪代码文件。

本文由 Claude 编写。另见 [天气系统](Weather.md)（2K/4K/6K 预报规律）、[间谍组织](SpyRing.md)（环形分布规律）、[evidence/](evidence/)（原始证据文件）。

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

这个函数受 `AMatchControllerV2::bUseTurnSwitchValidation`（native `+0x7A8`）控制。蓝图代码里这个字段只被读取、从未被赋值；原生反汇编里也找不到任何硬编码的赋值指令（`xrefs_to_field` 查询返回零结果）——真正的原因是这个值由服务端按局下发，客户端通过反射系统写入，不是写死在代码里的常量。**真实抓包已经直接确认了下发的值**：对局引导数据（bootstrap）末尾明文带着 `"validate_turn_switches":true`，字段名跟这个原生属性高度对应。也就是说，在真实的 `training`（人机单机）对局里，这个重播种分支**是开启的**——每次创建/确认一个动作，`cardsRandomStream` 都会被重新播种。完整证据见 [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)。（这条证据尚未覆盖 PvP/天梯/锦标赛对局，不能排除那些模式下配置不同。）

有两个调用点：

```cpp
// 调用点 A：BP_OnlineMatch.cpp:9146-9150（本地构造新动作时，用本地预测值）
GetCurrentActionID = MatchController->GetCurrentActionID();
SetRandomStreamWithActionID(GetCurrentActionID);

// 调用点 B：BP_OnlineMatch.cpp:445（服务端确认动作后，用真实回传值）
SetRandomStreamWithActionID(receivedAction.action_id);
```

本地在还没提交动作、`action_id` 还是占位符 `-1` 的阶段，就已经用本地预测的 `GetCurrentActionID()` 抢先重播种（这样天气预报卡面才能在提交前就在 UI 上显示结果）；动作真正提交、服务端确认后，会用真实 `action_id` 再重播种一次。如果本地预测计数器在两次触发之间没有正确自增（比如没有走完一次完整的"创建→提交→确认"闭环），两次重播种会用同一个 `action_id`、种子完全相同，结果自然一样——这解释了"同回合内第二次开发结果一样"这个现象。

### 2.3 `action_id` 其实有两套编号：服务端确认后的权威序列，和本地投机计数器

用真实抓包解密全部提交请求的 `action_id` 字段后确认：**服务端最终确认、双方合并后的权威动作日志，是一条从 1 开始、每次恰好 +1、全程没有重置/跳过/重复的连续整数序列**。完整数据和方法见 [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)。

**但这不是客户端提交请求时填的那个数字**。进一步用服务端轮询回包（`PUT /matches/v2/<id>/actions`，服务端按 `min_action_id` 增量返回的已确认动作数组）解密出真实权威序列，逐条跟客户端自己提交的 `action_id` 字段比对后发现：客户端提交时用的 `action_id`，其实是**只数"我方自己已经创建过多少个动作"的本地投机计数器**（对应 §2.2 调用点 A 的 `GetCurrentActionID()`），完全不管对手做了什么、也不去查询对手的动作数量。一份真实对局里，我方提交的 63 个动作，本地填的 `action_id` 就是干净的 `1,2,...,63`；但服务端确认后这些动作的真实编号，随着对手动作在中间插入越来越多，逐渐涨到 `113-117`——到对局末尾，本地计数器和服务端真实编号已经相差 54。完整数据见 [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)。

这个区分很重要：**天气预报、间谍组织这类"提交前就能在 UI 上看到预览结果"的效果，用的是调用点 A 的本地投机重播种**——种子里的 `action_id` 是这个只数自己、不管对手的本地计数器，不是服务端最终权威序列。这正是社区仅凭"数自己做了几次操作"就能总结出可复现规律表的根本原因：他们凭直觉抓住的"操作次数"，跟游戏内部驱动预览结果的那个变量，本来就是同一个东西——不需要知道对手做了什么，因为这个变量原本就不管对手做了什么。§2.2 提到的"如果本地预测计数器两次触发之间没有正确自增，两次重播种会用同一个 `action_id`"这个解释依然成立，但不能简单理解成"结果会完全冻结"——具体哪一档天气容易看起来不变、哪一档容易变，取决于 Weather.md §4.1 的代价模型，不是单纯"种子变没变"这个二元判断。

## 3. 动作类型与提交流程

来源：`本地反向工程项目/matches\actions.py`/`session.py`/`PROTOCOL.md`（同一个反向工程项目对 REST 协议的重建，非本报告主题但直接支撑上面"`action_id` 如何推进"的结论），交叉验证真实抓包。

### 3.1 有哪些动作类型

客户端提交动作走 `POST /matches/v2/<match_id>/actions`，请求体是一个加密包，解密后的明文 JSON 是 `{"action_type", "player_id", "action_data", "action_id"}`。已确认的 `action_type` 取值：

| 全称 | 简写（提交时用） | 作用 |
|---|---|---|
| `XStartOfGame` | — | 对局的第一个动作，`action_id` 必须是 1，在提交 mulligan 之前抢先提交 |
| `XActionStartOfTurn` | — | 一方回合开始 |
| `PC`（`XActionPlayCardFromHand`） | `PC` | 出牌 |
| `AC`（`XActionAttackCard`） | `AC` | 攻击 |
| `ML`（`XActionMoveCardToLine`） | `ML` | 支援线推进到前线 |
| `HT`（`XActionHandTargetSelected`） | `HT` | 延迟目标选择的第二步提交（仅蓝图反编译推断，未在真实抓包中观测到） |
| `CS`（`XActionCardToDrawSelected`） | `CS` | "抽/生成 N 选 1"效果的选择结果（同样仅蓝图推断，未实测确认） |
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

`wards` 项目（第三方客户端重实现）的做法，和真实抓包观察到的行为完全吻合：本地维护一个 `current_action_id` 整数，对局引导数据返回后初始化为 `bootstrap.match.current_action_id + 1`（新对局是 `0+1=1`，与真实抓包首个 `action_id=1` 一致），每提交一次动作就直接使用当前值、随后自增 1；轮询到服务端确认的动作后，用确认动作里的最大 `action_id + 1` 校准本地计数器（防止本地/服务端计数器因为对手动作而错位）。这跟原生 `GetCurrentActionID()`（`AMatchControllerV2+0xC98`）语义一致——一个简单的本地投机计数器，配合服务端确认后的校准，不需要理解游戏内部任何复杂状态机。

## 5. `cardsRandomStream` 的已知消费点

**卡牌自身效果触发的消费点**（玩家打出某张具体卡时才会走到）：

| 位置 | 函数 | 用途 |
|---|---|---|
| `BP_CardFunctions.cpp:5265`/`5325` | `GetRandomCard(cards, skipCustomAlways, out randomCard)` | 从一组候选卡里随机取一张（先看是否有 `AlwaysSelectedAsRandom` 标记的子集，优先在子集里随机，否则全体随机）；被多张"随机摧毁/随机选目标"卡复用，例如 [SpyRing.md](SpyRing.md) §7 提到的死降/加压舱 |
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
- 真实对局里 `bUseTurnSwitchValidation` 开启，每次动作都会把它重播种为 `match_id + action_id*19390`（§2.2）。
- 服务端最终确认的权威 `action_id` 是双方合并、从 1 开始逐一递增的简单序列；但预报/间谍组织这类提交前就能看到预览的效果，用的是**我方自己的本地投机计数器**——只数我方动作、不管对手，两者是不同的编号（§2.3）。

因此：**天气预报、间谍组织、护航攻击等所有依赖 `cardsRandomStream` 的效果，其预览结果从玩家开始操作的那一刻起理论上就是完全确定的，只取决于我方自己到当前为止一共做过多少个动作**。这不需要额外假设——是这三点已确认事实的直接推论。

这正是社区仅凭对局内观察、用统计归纳法就能摸出规律（Weather.md 的 2K/4K/6K 代价表、SpyRing.md 的环形游走+完整周期），乃至据此设计出"零费用控制天气结果"打法的根本原因。官方已于 2026-08-23 发布《关于秋季锦标赛预报机制的说明》，确认"尝试利用特定操作控制预报机制结果"属实，将其定性为游戏机制层面的问题，而非外挂/作弊；截至该说明发布，尚未给出具体修复方案或补偿。

**仍未确认的一层**：`action_id`（或"双方发生过多少个动作"这个量）具体是通过什么算法映射成"天气预报显示哪张卡""间谍组织抽到哪个国家"的。Weather.md §4.2 用真实引擎 LCG 公式直接推导过一次，推导结果跟社区实测出的代价表对不上（预测 2K/4K 应有不同节奏，但实测两者完全相同）——已经排除了"每个 tier 各自独立采样一次"这个最简单的假设，指向存在某个尚未定位到的显式计数器/查表逻辑。也就是说：**"结果是确定性的、原则上可预测"这一层已确认；"具体映射公式是什么"这一层还没有**，是本报告目前唯一需要继续用 IDA 追查原生代码的部分。

## 7. 尚待确认的开放问题

1. §6 提到的"action_id → 具体展示结果"映射公式的原生实现位置。
2. `_forecastOptions`（天气预报候选缓存）具体在哪个函数里被清空/重建——字面代码显示它从未清空，但实测 2K/4K 反复预报会变化，说明清空点尚未定位到。
3. `Array_ShuffleFromStream(localDeckCardIDs, ...)` 客户端洗牌是否只是本地展示/校验用，真正决定抽牌顺序的洗牌是否发生在服务端。
4. `bUseTurnSwitchValidation` 在 PvP/天梯/锦标赛对局下是否也是开启的（目前证据只覆盖 `training`）。
5. `HT`/`CS` 两种动作类型（延迟目标选择、抽卡二选一结果）以及 `sub_actions` 的完整字段形状，目前只有蓝图反编译依据，未经真实抓包交叉验证。

## 8. 另见

- [Weather.md](Weather.md) — 天气系统实现细节 + NZ33 社区确定性代价表 + 引擎源码级推导。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律、已确认的 18 次操作完整周期、护航攻击等结构相同的卡。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该字段命名与真实取值的完整证据链。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — `action_id` 真实取值规律的完整证据链。
- [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md) — 原生 `GetNextAction_Impl` 状态机分析，及其与 `action_id` 分配规则的关系澄清。
