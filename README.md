# KARDS 对局生命周期随机数机制报告

来源：FModel 反编译的蓝图伪代码（`Content/Blueprints/`），交叉验证部分原生实现（IDA，`kards-Win64-Shipping.exe`）。以下所有行号均指反编译导出的 `.cpp` 伪代码文件。

## 1. 核心随机流对象

游戏里跟"对局结果"相关的随机数几乎全部经过两个 `FRandomStream` 实例，都挂在 `BP_CardFunctions`（`cardFunctions`）这个单例上：

```cpp
// BP_CardFunctions.cpp:7-14
struct FRandomStream cardsRandomStream = { InitialSeed: 0, Seed: 0 };
struct FRandomStream encryptionStream  = { InitialSeed: 0, Seed: 0 };
```

- `cardsRandomStream`：驱动几乎所有**真正影响对局结果**的随机数（洗牌、天气预报、AI/效果的随机选卡等）。
- `encryptionStream`：驱动卡牌数值反作弊 XOR 加密的密钥生成（跟对局结果无关，纯粹是本地防篡改用）。

两者**共享同一套播种时机**——每次重新播种时，`encryptionStream` 都被直接赋值为 `cardsRandomStream` 播种后的状态（同一个种子）：

```cpp
// BP_CardFunctions.cpp:12339-12347
public void SetRandomStreamByMatchID(int MatchID) {
    cardsRandomStream = UKismetMathLibrary::MakeRandomStream(MatchID);
    encryptionStream = cardsRandomStream;
}
```

## 2. 播种时机：一共两层，其中一层可以被开关关闭

### 2.1 第一层：对局初始化时，仅用 `match_id` 播种一次

```cpp
// BP_OnlineMatch.cpp:1734-1744  (starting_hand_left 解析完成之后)
cardFunctions->SetRandomStreamByMatchID(Match.match_id);
cardFunctions->InitializeSideEffectHolders();
GameStateRef->InitialKreditAndSlotEncryption();   // 用 encryptionStream 建立卡牌数值加密
```

这是拿到 REST 返回的对局初始数据（`starting_hand_left` 等）之后立刻做的，`种子 = match_id`（不带 action_id 项）。

### 2.2 第二层：每个动作都会尝试重新播种为 `match_id + action_id*19390`

```cpp
// BP_OnlineMatch.cpp:24520-24536
private void SetRandomStreamWithActionID(int inputActionID) {
    if (!GetMatchController->bUseTurnSwitchValidation)
        return;                                   // <-- 关键：这个 flag 是 false 时，重播种整个被跳过
    int seed = Match.match_id + inputActionID * 19390;
    cardFunctions->SetRandomStreamByMatchID(seed);
}
```

**这个函数有一个前置条件 `bUseTurnSwitchValidation`。如果该 flag 为 false，重播种是空操作——`cardsRandomStream` 会保留上一次的状态继续往后走，而不是被重置到新种子。** 这个 flag 具体在什么条件下为 true/false，蓝图侧看不到赋值来源（大概率是 `AMatchControllerV2` 原生字段，可能跟对局类型/回滚校验开关有关），需要进一步在 IDA 里查找 `bUseTurnSwitchValidation` 的赋值点才能确认。

### 2.3 重播种有两个调用点——一个是"本地预测"，一个是"服务端确认后"

```cpp
// 调用点 A：BP_OnlineMatch.cpp:9146-9150（CreateAction_Init，本地正在构造一个新动作时）
GetCurrentActionID = MatchController->GetCurrentActionID();   // 本地维护的"预测下一个 action_id"计数器
SetRandomStreamWithActionID(GetCurrentActionID);

// 调用点 B：BP_OnlineMatch.cpp:445（处理已确认动作时）
SetRandomStreamWithActionID(receivedAction.action_id);        // 服务端回传的真实 action_id
```

也就是说：**本地在还没提交动作、`action_id` 还是占位符 `-1`（`CreateAction_SendActionWithSub` 里 `MakeStruct_Action2.action_id = -1;`，line 9176）的阶段，就已经用一个本地预测的 `GetCurrentActionID()` 抢先重播种并消耗随机数了**（这样天气预报卡面才能在提交前就在 UI 上显示结果）。等这个动作真正提交、服务端确认、以 `AllMatchActions` 形式回传后，会再用**真实**的 `action_id` 重播种一次，走一遍"正式"结果。

这个"本地预测 id → 提交 → 服务端确认 id"两段式设计,是我们讨论 Forecast bug 时最关键的一块拼图:如果本地预测计数器 `GetCurrentActionID()` 在同一回合内两次开发之间**没有正确自增**(比如两次触发之间没有一次真正完整走完"创建→提交→确认"的闭环),那第二次开发用来重播种的种子会跟第一次完全一样,由此产生的三个抽签结果自然也完全一样——这与之前你反馈的"同回合内第二次开发结果一样"完全吻合,且不需要依赖 `_forecastOptions` 缓存未清空这个假设。

## 3. `cardsRandomStream` 的已知消费点(会真正影响对局结果的随机数)

| 位置 | 用途 |
|---|---|
| `BP_CardFunctions.cpp:12365` | 对局开始时,用 `Array_ShuffleFromStream` 打乱各自的 `localDeckCardIDs`(**这里存疑**——大概率真正的洗牌发生在服务端,这里可能只是客户端本地重建/校验用,需要进一步确认到底是不是权威洗牌) |
| `BP_CardFunctions.cpp:5265` `:5325` | 从数组中随机取一张卡(具体上下文待查,疑似"随机效果目标"类卡牌用) |
| `BP_CardFunctions.cpp:5422` `:5605` | `Array_ShuffleFromStream`,打乱 `oppositeSideUnseenCards`/`possibleChooseCards`(对方未见卡池/候选选择池) |
| `BP_CardFunctions.cpp:6618` | 从牌库中按 `RandomIntegerInRangeFromStream` 直接抽一张(`RandomWithoutShuffle` 模式) |
| `BP_CardFunctions.cpp:22621` | 从一个 Set 转数组后随机取一个 |
| `card_event_storm1_gale.cpp:148/156/164`(及 sunny/rain 系列同构文件) | **天气预报**:依次从 light/medium/heavy 三个候选池里各抽一张(顺序固定,同一个 stream 连续消耗三次) |

`encryptionStream` 目前只确认一个消费点:

| 位置 | 用途 |
|---|---|
| `BP_CardFunctions.cpp:13932` | `RandomIntegerInRangeFromStream(encryptionStream, 10000, 1000000)` 生成 `key1`——卡牌数值反作弊 XOR 密钥的一部分,跟对局结果无关 |

> 除以上"权威随机数"外,`Content/Blueprints/Effects/`(坦克炮口烟雾、树叶摆动、探照灯等)下还有大量 `RandomFloat`/`RandomIntegerInRange` 调用,但那些都是走 UE 全局(未播种、非确定性)RNG,纯粹是视觉表现层,跟 `cardsRandomStream`/`match_id`/`action_id` 没有任何关系,不影响对局结果,此处不逐一列出。

## 4. 应用到 Forecast/Develop bug 的结论

结合前面已经确认的 `card_event_storm1_gale.GetChooseSpawnCards`:

- `_forecastOptions` 字段在该文件里**从未被清空**,一旦非空就直接复用(见前一版分析)。
- 但新的重播种机制说明,即便 `_forecastOptions` 被正确清空、每次都重新走一遍三次抽签,**只要两次开发共享同一个(本地预测或确认后的)`action_id` 种子,三个抽签结果依然会完全一致**——根因可以完全不落在 `_forecastOptions` 缓存上,而落在"本地预测 action_id 计数器没有在两次开发之间正确推进"这一层。
- 你观察到的"2k/4k 会变、6k 不变,过一回合 6k 通常又会变"这个不对称现象,**用单一重播种理论无法完整解释**(如果是同一个种子,三个 tier 应该同时冻结)。目前最合理的解释仍然是:6k(heavy)候选池本回合内候选数量太少(极端情况只有 1 个),导致不管随机数怎么变,`RandomIntegerInRangeFromStream(0, 0)` 结果都只能是下标 0——不是没随机,是没得选。这一点需要在 IDA/原生侧确认"候选池大小是否跟回合状态挂钩"(比如某张重量级天气牌本回合处于"在场/冷却"从而被排除出 `GetAllActiveStaticCards`)才能坐实,目前是待验证假设,不是确认结论。

## 4.1 统一结论(社区实测 + 原生代码交叉验证)

社区实测:把同一回合内"1次操作/2次操作/3次操作"(按需要点击/滑动的次数分类,对应不同动作类型)按顺序整理成表后,6k/4k/2k 天气选择结果呈现**可预测、会循环**的规律,并非随机波动。

这与原生代码确认的机制完全吻合:

- `bUseTurnSwitchValidation`(native offset `0x7A8`,Dumper-7 SDK 已确认)为 false 时,`SetRandomStreamWithActionID` 是空操作——`cardsRandomStream` **全场只在对局开始时用纯 `match_id` 播种一次,此后不再重播种**。
- 整场对局里所有消耗 `cardsRandomStream` 的效果(洗牌、天气预报的三次 tier 抽取、其他随机选择),都是在同一条从未重置的确定性序列上按调用顺序连续取值。
- `_forecastOptions`(SDK 确认的唯一持久字段,`Ucard_event_storm1_gale_C` offset `0x680`)决定的只是"这次要不要消耗流里接下来的新值"(整体缓存命中/未命中,无法部分命中),不影响"消耗到的值是什么"。
- 因此,按"这是全场第几次消耗这条流"来整理数据,理应能看到一张固定的、会复现的查找表——这正是社区实测观察到的"可列表、按规则循环"的现象的数学根源:同一个 `FRandomStream` 算法在同一个 `match_id` 种子下,同样的调用顺序,必然产出同样的结果序列。

**结论**:在 `bUseTurnSwitchValidation` 关闭的对局模式下(目前证据显示这可能是常规/非验证模式的默认状态,具体默认值与开关条件仍待确认),天气预报乃至其他所有依赖 `cardsRandomStream` 的随机效果,理论上在对局开始、仅凭 `match_id` 就已经完全确定,只取决于"这是本场比赛第几次消耗这条流"。这直接呼应了本报告最初讨论的问题:预测这条随机流是否可行——现在看,这条流的设计在该模式下可能从根本上就没有做到不可预测。

## 5. 尚待确认的开放问题

1. `bUseTurnSwitchValidation` 的赋值来源和触发条件(原生字段,蓝图侧不可见赋值处)。
2. `GetMatchController->GetCurrentActionID()` 这个本地预测计数器的具体自增规则——尤其是在 autoplay 连续触发同类动作时是否正确自增,是不是就是两次开发结果一致的直接原因。
3. `_heavyWeatherCards`/`_mediumWeatherCards`/`_lightWeatherCards` 候选池大小是否真的存在"回合内被排除"的机制,以及具体排除条件。
4. `Array_ShuffleFromStream(localDeckCardIDs, ...)` 客户端洗牌是否只是本地展示/校验用,真正决定抽牌顺序的洗牌是否发生在服务端(如果是纯 REST+action 回放架构,大概率真正权威的牌序来自服务端,客户端这次洗牌可能只是占位/一致性校验)。

以上第 1-3 点需要回到 IDA 里查原生实现或者用录制的对局数据反推验证,目前这份报告只到"蓝图伪代码能看到多远"为止。
