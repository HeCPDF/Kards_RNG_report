# 天气系统：从代码到"可控天气"

来源：FModel 反编译的蓝图伪代码（`Content/Blueprints/`），交叉验证 IDA 反编译的原生实现和 Unreal Engine 5.6 引擎源码。行号均指本仓库 `FModel-Exports/` 下对应的反编译导出文件。核心随机流机制（`cardsRandomStream` 的播种/重播种规则）见 [README.md](README.md) §1-§2，本文只讲天气系统本身怎么用这条流。

## 1. `BP_CardFunctions` 里跟预报/随机有关的函数

`BP_CardFunctions`（蓝图侧单例，代码里叫 `cardFunction`）是全游戏所有"权威随机数"和天气预报逻辑的落脚点。跟本文主题相关的函数：

| 函数 | 位置 | 作用 |
|---|---|---|
| `RandomIntFromRangeWithStream(min, max, out result)` | `BP_CardFunctions.cpp:12423` | 唯一的随机数入口封装，内部就是一行 `UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, min, max)`。全游戏所有卡牌（天气、间谍组织、任何"随机抽一个"效果）都通过这个函数取随机数，没有例外的第二条路径。 |
| `SetRandomStreamByMatchID(MatchID)` | `BP_CardFunctions.cpp:12339` | 用 `MatchID` 重置 `cardsRandomStream`（详见 README §1）。 |
| `Forecast(cardTriggeringForecast, out qqq)` | `BP_CardFunctions.cpp:23533` | 打出带 `ability.forecast` 标签的卡牌时调用。目前带该标签的卡有：J2F 鸭式（DUCK，战斗机，移入前线时触发）、第 44 特混舰队（TASK FORCE 44，澳新军团指令）、美国气象局（US WEATHER BUREAU，指令）、阴云密布（OVERCAST，指令）、巡洋舰侦察机（CRUISER SCOUTS，日本指令）及 ANZAC/日本/USA 的若干侦察/水上飞机单位。该函数本身不产生随机数——它把三张一级天气代表卡（BLUE SKY / MIST / GALE，内部名 `card_event_sunny1_blue_sky` / `card_event_rain1_mist` / `card_event_storm1_gale`）交给 `NotifySelectCardToDrawPending` 弹面板，由玩家选择天气类型。真正的随机发生在选中代表卡之后，见下一节的 `GetChooseSpawnCards`。 |
| `GetAllForecastCards(...)` | `BP_CardFunctions.cpp:23084` | 从 `GetAllActiveStaticCards` 里按 `subtype.rain` / `subtype.storm` / `subtype.sunny` 三个 GameplayTag 筛出所有天气系卡牌（不分轻重级），是天气选卡候选池的上游数据源之一。 |
| `GetRandomCard(cards, skipCustomAlways, out randomCard)` | `BP_CardFunctions.cpp:5248` | 通用的"从一堆卡里随机挑一张"，被非天气类效果复用（先检查是否有打了 `AlwaysSelectedAsRandom` 标记的卡，优先在这个子集里随机；否则在全体里随机）。天气选卡没有用这个函数，是各天气代表卡自己实现了一遍三段式抽取（见下）。 |
| `ShuffleDeckBySide` / `DiscardRandomCardFromHand` / `GiveRandomCombatKeyword` | `BP_CardFunctions.cpp:12351` / `6492` / `22523` | 同样走 `cardsRandomStream`，但跟天气无关，属于洗牌/弃牌/随机赋予关键词，完整列表见 README §3。 |

## 2. 天气卡怎么实现：以 `card_event_sunny1_blue_sky`（"将是晴天"）为例

天气系统的卡牌全部放在 `Content/Blueprints/Cards/Neutral/events/` 下，命名规律是 `card_event_<天气类型><级别>_<卡名>`（`sunny1`=一级晴天代表卡，`sunny2_heatwave`=晴天的二级效果卡……以此类推，`rain`/`storm` 同理）。这些卡全部位于"活跃卡池"（Active Static Cards），运行时全程被加载——不是打出来才实例化，而是每一局开始就作为场上常驻的静态对象存在，随时可以被 `GetAllActiveStaticCards()` 枚举到。

### 2.1 每张子天气卡怎么声明自己是哪一类天气

`Ucard_event_sunny1_blue_sky_C` 的 `GameplayTags` 字段：

```cpp
struct FGameplayTagContainer GameplayTags = FGameplayTagContainer({
    FGameplayTag::RequestGameplayTag(FName("autoplay"))
});
```

`sunny1_blue_sky` 是一级代表卡，本身不带 `subtype.*` 分级标签（它只是 UI 上给玩家选的那三个选项之一），但带着 `autoplay` 标签——这是一个通用词条，意思是"这张卡一旦加入手牌，游戏会自动帮玩家打出它"（不需要玩家再手动点一次"出牌"）。这解释了 §2.2 描述的流程为什么只需要玩家做两次选择（天气类型、天气强度）而不是三次：玩家在第一个弹窗里选中某个天气类型后，对应的一级代表卡被加入手牌，`autoplay` 让它立刻自动打出、触发 `OnPlayedFromHand`，玩家不需要再额外操作一次"出牌"，紧接着就会看到第二个弹窗（轻/中/重三选一）。真正携带分级信息的是各个效果卡，例如同目录下的 `card_event_sunny2_heatwave`：

```cpp
struct FGameplayTagContainer GameplayTags = FGameplayTagContainer({
    FGameplayTag::RequestGameplayTag(FName("subtype.sunny")),
    FGameplayTag::RequestGameplayTag(FName("subtype.lightWeather"))
});
```

`subtype.sunny`/`subtype.rain`/`subtype.storm` 标记天气种类，`subtype.lightWeather`/`subtype.mediumWeather`/`subtype.heavyWeather` 标记轻/中/重（对应俗称的 2K/4K/6K）级别。天气系统靠遍历全部活跃卡、按这两组标签分类，而不是靠一张写死的表——新增一张天气卡，只要打上正确的标签、丢进 `Neutral/events/` 目录，就会自动被下面这套逻辑收编。

### 2.2 `GetChooseSpawnCards`：三级天气怎么被选出来

**玩家实际看到的流程，跟"打出预报卡→弹三选一"这个直觉描述不完全一样，这里先澄清一下时序**：预报实际上是**两次连续的玩家选择**，不是"选一次、其余自动"：① `Forecast()`（§1）把三张一级天气代表卡（`sunny1`/`rain1`/`storm1`，对应晴/雨/风三种天气类型）传给 `NotifySelectCardToDrawPending` 弹面板，**由玩家选择要哪一种天气类型**；② 选中的一级代表卡因 `autoplay` 标签自动打出（无需再点一次"出牌"），`OnPlayedFromHand` 触发，进而调用它自己的 `GetChooseSpawnCards`，弹出第二个面板，**再由玩家在轻/中/重三个候选里选一个**，决定最终抽到哪张具体的天气效果卡。也就是说，"预报"这个玩家体验对应两个需要玩家操作的游戏内事件：① 天气类型选择（真实抓包中对应 `CS`/`XActionCardToDrawSelected` 动作）；② 天气强度选择，触发 `GetChooseSpawnCards` 消耗三次 `cardsRandomStream`。[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 的真实抓包已观察到这两步各产生一个连续提交的 `CS` 动作、中间没有独立的 `PC`（"自动打出"）动作；这两步在 `CurrentActionId` 上的精确增量仍待受控测试单独钉死。

调用 `sunny1_blue_sky` 自己的 `GetChooseSpawnCards`（`card_event_sunny1_blue_sky.cpp:93-209`）来决定轻/中/重三个候选各是谁：

```cpp
public void GetChooseSpawnCards(TArray<UBaseCardObject*>& cards, bool& markAsSeen, bool& keepOrder)
{
    if (!Array_IsEmpty(_forecastOptions))
    {
        // 缓存分支：_forecastOptions 一旦非空就直接复用，本次调用不再消耗 cardsRandomStream
        cards = _forecastOptions;
        markAsSeen = false;
        keepOrder = true;
        return;
    }

    // 遍历全部活跃静态卡，按 GameplayTag 分成三桶
    GetAllActiveStaticCards(true, true, /*out*/ allCards);
    for (card : allCards)
    {
        if (!card.HasTag("subtype.sunny")) continue;
        if (card.HasTag("subtype.heavyWeather"))  _heavyWeatherCards.Add(card);
        else if (card.HasTag("subtype.mediumWeather")) _mediumWeatherCards.Add(card);
        else if (card.HasTag("subtype.lightWeather"))  _lightWeatherCards.Add(card);
    }

    // 依次从三个桶里各随机挑一张，顺序固定：light → medium → heavy
    randomResult = cardFunction->RandomIntFromRangeWithStream(0, _lightWeatherCards.Length - 1);
    _forecastOptions.Add(_lightWeatherCards[randomResult]);

    randomResult = cardFunction->RandomIntFromRangeWithStream(0, _mediumWeatherCards.Length - 1);
    _forecastOptions.Add(_mediumWeatherCards[randomResult]);

    randomResult = cardFunction->RandomIntFromRangeWithStream(0, _heavyWeatherCards.Length - 1);
    _forecastOptions.Add(_heavyWeatherCards[randomResult]);
}
```

要点：

1. 三个 tier 各自独立地在自己的桶内抽一个下标——不是从全体天气卡里抽，而是轻/中/重三次分别抽签，顺序固定为 light→medium→heavy，共消耗 `cardsRandomStream` 三次。
2. **`_forecastOptions` 不需要被清空——它天生就是空的，这一点已经从调用链上确认**。`GetChooseSpawnCards` 是在哪个对象上被调用的，直接决定了这个问题的答案：反编译 `BP_CardFunctions.cpp:selectCardToDraw`（真正触发这次三选一的入口函数）确认，调用点是 `cardSelecting->GetChooseSpawnCards(...)`（`BP_CardFunctions.cpp:5570`），而 `cardSelecting = GetCardFromID(cardSelectingCardToDraw)`（`BP_CardFunctions.cpp:5550-5552`）——也就是说，`GetChooseSpawnCards` 调用的对象，是"这次触发选择流程的那个具体卡实例"，由它自己独一无二的 `cardID` 查出来的，**不是** `GetAllActiveStaticCards()` 用来扫描标签的那个持久化静态对象。玩家每次抽到/打出一张一级天气代表卡，都是 `CreateCard` 新建出来的一个全新 `UBaseCardObject` 实例，带着自己的 `cardID`；`_forecastOptions` 是这个新实例上的 UPROPERTY，新实例创建时天然是空数组（UE 的默认零值初始化）。也就是说，**"缓存复用"这个分支在正常对局流程里根本不会被触发**——不是某处代码负责清空它，而是每一次触发预报，用来装 `_forecastOptions` 的对象本身就是全新的，没有"上一次的缓存"可言。这跟实测确认的"每次重新预报都是真实的、全新的三连抽"完全吻合，不需要假设任何未定位到的清空逻辑。（`blitz_doctrine`/`sabotage`/`heroes_of_the_soviet_union` 是同一件事的另一种体现：它们的 `PossibleCards` 也是各自新实例上的字段，"无条件重新扫描并追加"这个写法之所以不会真的产生重复堆叠，也是因为每次调用发生在不同的新实例上，根本不会重复调用同一个对象两次。）
3. 雨（rain）/风暴（storm）系的 `card_event_rain1_mist`、`card_event_storm1_gale` 是同构实现（把 `subtype.sunny` 换成 `subtype.rain`/`subtype.storm`，逻辑一模一样）。

### 2.3 候选池大小影响可变性，但不是唯一原因

天气展示结果是否"看起来不变"，根源不在候选池大小，而是本地计数器在两次预报之间推进了多少单位、跟第 4.2 节离散步长表之间的模运算关系——完整推导见 [ReseedImpact.md](ReseedImpact.md) §1、本文 §4.2。**一次预报固定消耗的单位数目前只能确认下限**：[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 的真实对局抓包显示预报实际只产生两个可观测的提交动作（类型选择、强度选择），至少消耗 2 个单位，第三步（自动打出）是否单独计数尚不确定，需要受控测试核实。

## 3. 核心结论：天气结果是确定性序列

结合 README.md §2-§4 交叉验证的原生机制和真实抓包证据：

1. 真实抓包已确认，真实对局里 `AMatchControllerV2::bUseTurnSwitchValidation`（native `+0x7A8`）是**开启**的——对局引导数据明文带着 `"validate_turn_switches":true`（详见 [`evidence/bUseTurnSwitchValidation.md`](evidence/bUseTurnSwitchValidation.md)）。这意味着 `cardsRandomStream` 每次创建/确认一个动作都会用 `CurrentActionId` 重播种为 `match_id + CurrentActionId * 19390`；`CurrentActionId` 是本机回放双方合并动作日志的进度游标（README §2.3），与服务端最终确认的、从 1 开始逐一递增的全局动作编号是两套不同的数（详见 [`evidence/action_id-real-capture-sequence.md`](evidence/action_id-real-capture-sequence.md)）。
2. 天气预报的三连抽（light→medium→heavy）严格按固定顺序发生，候选池大小、每类天气卡数量都是公开可数的静态信息（活跃卡池全程加载，`GetAllActiveStaticCards` 谁都能枚举）。只要知道 `match_id` 和双方到目前为止一共发生过多少个（加权）动作，理论上就能直接算出结果。
3. 官方已于 2026-08-23 就"秋季锦标赛选手利用特定操作控制预报机制结果"发布说明，确认这一现象属实，将其定性为游戏机制层面的问题而非外挂/作弊；2026-08-25 官方发布[后续说明](https://www.kards.com/news/forecast-issue-and-fall-2026-tournament-results)，确认已对系统做出调整使其更难被操纵。该调整不需要更新客户端，说明改动在服务端一侧，不影响本节引用的、直接来自 UE5.6 引擎源码的 LCG 算法本身。社区反馈调整生效后，以前摸出来的经验规律（NZ33 代价表等）已经不能再稳定复现；真实对局实测进一步确认本文公式本身在调整后也不能再准确预测结果，原因已查明：服务端不再下发 `validate_turn_switches` 字段，导致本节引用的重播种分支不再触发，完整技术推导见 [RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md)。

天气系统的"伪随机"不是比喻——它是以 `match_id` 为种子、按 `CurrentActionId` 重播种的确定性伪随机数序列，理论上全程可预测。这套机制为什么构成一个可被利用的漏洞、玩家具体怎么操作利用它，见 [ReseedImpact.md](ReseedImpact.md) §2。第 4 节从引擎源码给出档位结构和精确的离散步长表；第 5 节把这套纯代码推导跟社区实测数据对照。

## 4. 档位结构与引擎算法

本节先从反编译源码确认档位/候选池结构（§4.1），再给出引擎算法与数学推导（§4.2、§4.2.1），最后列出官方卡牌对照（§4.3）——全部只用已确认的反编译资料和引擎常数，不引用任何社区数据。跟社区实测（包括 NZ33《天气操作次数计算器》）的对照见第 5 节。

### 4.1 档位（light/medium/heavy）与候选池：源码可确认的事实

`GetChooseSpawnCards` 的填桶逻辑（`card_event_sunny1_blue_sky.cpp:93-209`）按 GameplayTag 把全部活跃天气卡分成三桶：`subtype.lightWeather` / `subtype.mediumWeather` / `subtype.heavyWeather`。档位与 `kredits` 字段的对应已直接核实：`sunny2_*`=2、`sunny3_*`=4、`sunny4_*`=6，rain/storm 同理，不存在档位错配的可能。

每个桶只装同一天气类型、同一档级下的 3 个变体（资产名"无后缀/2/3"，见 §4.3），因此每次 `GetChooseSpawnCards` 的三次抽样（light→medium→heavy）各在固定大小为 3 的桶内进行。天气类型（晴/雨/风）与档位（轻/中/重）是两个正交维度：前者由 `Forecast()` 的第一步面板决定，后者由一级代表卡的 `GetChooseSpawnCards` 第二个面板决定（§2.2）。

### 4.2 引擎算法：直接反编译确认，不依赖任何未验证的源码假设

`cardFunction->RandomIntFromRangeWithStream(min, max, out)` → `BP_CardFunctions.cpp:12423`（蓝图，FModel 反编译确认，一行转发）→ `UKismetMathLibrary::RandomIntegerInRangeFromStream`。这个原生函数在 `kards-Win64-Shipping.exe` 里对应 IDA 地址 `0x143ddce50` 的反编译如下（`v7` 指向 `FRandomStream` 结构体，`+0` 是 `InitialSeed`，`+4` 是 `Seed`；`v11`=`min`，`v12`=`max-min+1`）：

```cpp
v13 = 196314165 * *((_DWORD *)v7 + 1) + 907633515;   // Seed = Seed*196314165 + 907633515 (mod 2^32)
*((_DWORD *)v7 + 1) = v13;                            // 写回 Seed
result = (v13 >> 9) | 0x3F800000;                     // GetFraction()：取高 23 位构造 [1,2) 浮点数
v14 = v11 + (int)(float)((float)(*(float *)&result - 1.0) * (float)v12);   // Min + floor(GetFraction()*(Max-Min+1))
```

（完整反编译原文，含 UE 蓝图 VM 参数解包样板代码，见 [evidence/ida-excerpts/RandomIntegerInRangeFromStream.c](evidence/ida-excerpts/RandomIntegerInRangeFromStream.c)；`GetChooseSpawnCards` 的完整蓝图字节码原文见 [evidence/fmodel-excerpts/GetChooseSpawnCards.cpp](evidence/fmodel-excerpts/GetChooseSpawnCards.cpp)）

这不是从 UE5.6 引擎源码推断或假设出来的公式，是直接从这个二进制文件（Kards 使用的 UE5.6 fork）反汇编读出来的字节码，逐条对应上面四行 C 伪代码——常数 `196314165`、`907633515` 已用 `find_bytes` 在整个二进制里定位（命中 `0x140eaf4b2` 等多处，包括这个函数本身），确认这个 fork 没有修改这两个 LCG 常数。每次调用 `RandomIntFromRangeWithStream`，`Seed` 恰好做一次这样的变换，返回值恰好是这一次变换后的结果——没有隐藏的多次调用或额外处理。

`GetChooseSpawnCards`（`card_event_sunny1_blue_sky.cpp:93-209`，蓝图，FModel 反编译确认）对 light/medium/heavy 三个候选池依次各调用一次 `RandomIntFromRangeWithStream`，顺序固定；`SetRandomStreamWithActionID`（`BP_OnlineMatch.cpp:24520-24536`，蓝图，FModel 反编译确认）把 `cardsRandomStream` 重播种为 `match_id + action_id * 19390`——这两点前面章节已经交叉确认过，不再重复。

以上是本报告目前能够从 IDA/FModel 直接确认、无需任何额外假设的全部内容。

**数组下标↔小组编号的对应关系——已经确定，不需要运行时内存读取**。`GetAllStaticCardsSortedByName` 最终排序核心（IDA 反编译 `sub_144B14100`→比较函数 `sub_14137F890`→`sub_141376EA0`，地址 `0x141376EA0`）确认：比较的是两张卡各自的 `Name` 属性对应的 `FNameEntry` 字符串内容，落到 `sub_141215A10`/`sub_141215870`（宽/窄字符串比较，按长度截断后再比较剩余长度）——这是标准的、不区分大小写的字典序字符串比较，不涉及任何运行时才能确定的隐藏状态（`sub_141376EA0` 原文见 [evidence/ida-excerpts/StaticCardNameCompare.c](evidence/ida-excerpts/StaticCardNameCompare.c)）。`GetChooseSpawnCards` 本身的填桶逻辑（`card_event_sunny1_blue_sky.cpp:100-203`，已反编译）确认：`_lightWeatherCards`/`_mediumWeatherCards`/`_heavyWeatherCards` 各自只收集"同时带 `subtype.sunny`（或 rain/storm）标签 **且** 带对应档级标签"的卡，也就是说每个桶只包含**同一天气类型、同一档级下的 3 个候选变体**（例如 light 桶只装 `sunny2_heatwave`/`sunny2_heatwave2`/`sunny2_heatwave3` 三张），桶内保留 `GetAllActiveStaticCards` 已经排好的顺序。这三个候选的资产名恰好是"无后缀 / 加`2` / 加`3`"，按标准字典序比较，无后缀的字符串永远排在有后缀的前面（因为它是后者的真前缀），`"...2"` 又天然小于`"...3"`——所以**数组下标 0/1/2 严格对应候选变体编号 1/2/3，这是一个必然成立的字符串排序结果，不依赖任何运行时状态，也不需要逐字段读取内存来验证**。

**离散步长表：本地计数器每推进 `d` 个单位，各档展示下标怎么变**。跟 SpyRing.md §3 同样的方法（把 `Δ_seed(d) = d×19390×A^k mod 2^32` 代入离散化规则，`A^k` 换成对应档位的变换深度：light 是 `A^1`，medium 是 `A^2`，heavy 是 `A^3`），逐个整数 `d`（本地计数器步进量）测出每档在每个 `d` 下的**离散下标步长分布**（20000 次采样）：

| `d` | light（k=1）主导步长 | medium（k=2）主导步长 |
|---|---|---|
| 3 | -1（59.0%） | 0（92.0%） |
| 15 | 0（93.6%） | 0（61.3%） |
| 18 | -1（52.9%） | 0（53.2%） |

**这张表本身已经证明了一个重要结论：light（k=1）和 medium（k=2）两档在同一个 `d` 下的主导步长，通常不是同一个值**——这是因为线性同余变换是仿射映射 `f(x)=Ax+C`，两个只差常数 `d` 的种子，变换 `k` 次后的差值精确是 `A^k·d (mod 2^32)`，而 `A^1 mod 2^32 = 196314165`、`A^2 mod 2^32 = 3026498297` 这两个数不相等（也不存在任何巧合让它们相等）——所以 light 和 medium 在"本地计数器每 +1，等效位移多少"这件事上，数学上必然不同，这一点从常数本身就能严格证明，不依赖任何外部数据。`d=3` 一行正是这个证明的具体体现：light 主导"跨了一组"（59.0%），medium 主导"没跨组"（92.0%），方向相反；`d=15` 一行则显示两档**恰好**在这个具体的 `d` 上都以高概率给出"不变"——这不是矛盾，是两条各自独立的仿射映射曲线在 `d=15` 这一点偶然重合的结果，可以直接用上面的常数重新算一遍验证。

**排除了另一种可能的技术性解释：弹窗交互时序**。追踪 `NotifySelectCardToDrawPending`→`I_OnlineMatchReceiver::HandleSelectCardToDrawPending`（`BP_OnlineMatch.cpp:3920-3934`，蓝图入口 `11794`）→`AddSubActionSelectCardToDrawPending`（`BP_OnlineMatch.cpp:16193-16215+`）的完整调用链（均已反编译）确认：这个通知函数只是把**已经算好的** `spawnCards`（也就是 `GetChooseSpawnCards` 三次抽签算完之后的最终结果）打包成一条 `ZActionSelectCardToDrawPending` 记录，推进 `SelectCardToDrawPendingQueue` 这个队列——是一次性的、单向的展示通知，不是"玩家切换预览、重新计算"这种交互式循环。也就是说，UI 层不存在"来回切换类型、导致 `GetChooseSpawnCards` 被多次调用、从而让不同档位消耗到不同变换深度"这回事：`GetChooseSpawnCards` 就是在天气类型确定、代表卡自动打出后，一次性调用一遍，产生的三个结果被固定打包展示。

结论：数组下标↔候选编号的映射关系已经确定（字典序，不需要运行时验证）；light/medium/heavy 三档在同一个本地计数器步进量 `d` 下，展示下标的离散步长分布已经精确算出，且已证明 light 和 medium 两档的步长曲线在数学上通常不同（`A^1≠A^2`），只在特定的 `d` 值上偶然吻合。跟社区实测代价表（NZ33《天气操作次数计算器》）的对照见第 5 节。

### 4.2.1 假设一场对局，逐步套用上面的算法（数值示例，不是真实抓包）

下面用一个**假设**的对局，把 §4.2 确认的公式从头到尾算一遍，展示这套机制实际怎么运作。`match_id` 和 `CurrentActionId` 用的是虚构数字，不对应任何真实对局；候选池大小按每档最简单的情形（3 个候选，下标 0-2）处理，不代表真实候选池一定是 3——这只是为了让计算过程可复现、可验证。

假设 `match_id = 1000000000`，玩家在本回合触发预报时，喂给 `SetRandomStreamWithActionID` 的 `CurrentActionId = 10`：

**第一步，重播种**（`BP_OnlineMatch.cpp:24520-24536`）：
```
seed = match_id + CurrentActionId * 19390 = 1000000000 + 10*19390 = 1000193900
cardsRandomStream.Seed = 1000193900
```

**第二步，`GetChooseSpawnCards` 依次调用三次 `RandomIntFromRangeWithStream(0, 2)`**（严格按 §4.2 反编译出的公式，逐次用上一步算出的 `Seed` 继续变换）：

| 第几次调用 | 变换前 Seed | `Seed = Seed*196314165+907633515 mod 2^32` | 返回下标（`floor(GetFraction()*3)`） |
|---|---|---|---|
| 1（light） | 1000193900 | 1626977479 | 1 |
| 2（medium） | 1626977479 | 4280773790 | 2 |
| 3（heavy） | 4280773790 | 431904801 | 0 |

也就是说，这次预报玩家会看到：light 桶第 1 号候选、medium 桶第 2 号候选、heavy 桶第 0 号候选。

**第三步，玩家不做别的事，立刻再打出一张预报牌**：假设一次预报固定消耗 3 个本地计数器单位（本例的假设值，具体数字见 ReseedImpact.md §1），这次触发时喂给重播种公式的 `CurrentActionId` 变成 `10+3=13`：

```
seed = 1000000000 + 13*19390 = 1000251870
```

重复第二步的三次调用，结果是 light=0、medium=0、heavy=0——跟第一次（1、2、0）相比，light 和 medium 的下标变了，heavy 没变（这次示例里恰好前后两次 heavy 都落在下标 0，属于这组具体数字的巧合，不是普遍规律，因为本示例统一假设三档桶大小都是 3，不代表真实候选池结构一定如此）。

这个计算过程完全可以用 §4.2 那四行反编译出的公式重新算一遍验证——本节的作用只是把公式具体落到一组数字上，让"重播种→连续三次 LCG 变换→取下标"这套机制变得可核对。

### 4.3 档位/候选编号与真实卡牌对照表

`Content/Blueprints/Cards/Neutral/events/` 下每种天气效果卡都有 3 个版本，文件名后缀（无后缀/2/3）对应 §4.2 确定的候选编号 1/2/3。效果文本直接取自 FModel 反编译的 `Text` 字段，官方中文名与术语以官方卡牌索引为准（如 Pin=压制、Suppress=抑制、支援阵线、行动花费）。候选编号 1/4/7 的卡名带官方站点卡图链接，非本仓库转载；候选编号 2/3/5/6/8/9 版本在官方 API 里用的内部 id 跟 FModel 导出名不是简单的加数字后缀关系，尚未逐一核实，完整已确认清单见 [`evidence/card_image_urls.json`](evidence/card_image_urls.json)。共 9 组候选、每组 3 张（晴/雨/风各一张），27 张效果卡：

| 大组 | 小组 | 晴（Sunny） | 雨（Rain） | 风（Storm） |
|---|---|---|---|---|
| 2K | 1 | [`sunny2_heatwave`](https://www.kards.com/images/card/v52/en-EN/heatwave.avif) 热浪 HEATWAVE — 所有单位 +2 攻击力（空军 +3），直到回合结束 | [`rain2_deluge`](https://www.kards.com/images/card/v52/en-EN/deluge.avif) 暴雨 DELUGE — 增加 6 点防御力，随机分配至所有友方目标 | [`storm2_thunderstorm`](https://www.kards.com/images/card/v52/en-EN/thunderstorm.avif) 雷暴 THUNDERSTORM — 造成 3 点伤害，随机分配至所有敌方目标 |
| 2K | 2 | `sunny2_heatwave2` 热浪 HEATWAVE — 友方单位 +1 攻击力，且行动花费 -1，直到回合结束 | `rain2_deluge2` 暴雨 DELUGE — 所有敌方单位 -1 攻击力 | `storm2_thunderstorm2` 雷暴 THUNDERSTORM — 使目标单位及其同名单位撤退 |
| 2K | 3 | `sunny2_heatwave3` 热浪 HEATWAVE — 本回合部署的单位对随机敌方单位造成等同于其攻击力的伤害 | `rain2_deluge3` 暴雨 DELUGE — 抑制 1 个目标单位，抽 1 张牌 | `storm2_thunderstorm3` 雷暴 THUNDERSTORM — 对随机敌方单位造成 5 点伤害 |
| 4K | 4 | [`sunny3_jungle_fever`](https://www.kards.com/images/card/v52/en-EN/jungle_fever.avif) 丛林热 JUNGLE FEVER — 将卡组顶的单位加入支援阵线，并将其压制到回合结束 | [`rain3_torrential_rain`](https://www.kards.com/images/card/v52/en-EN/torrential_rain.avif) 骤雨 TORRENTIAL RAIN — 友方步兵和总部 +3 防御力，其他友方单位 +2 防御力 | [`storm3_tropical_storm`](https://www.kards.com/images/card/v52/en-EN/tropical_storm.avif) 热带风暴 TROPICAL STORM — 双方将所有手牌洗入卡组，抽取等同于最大洗入数量的卡牌 |
| 4K | 5 | `sunny3_jungle_fever2` 丛林热 JUNGLE FEVER — 将 1 个友方单位的复制加入支援阵线，并将其压制到回合结束 | `rain3_torrential_rain2` 骤雨 TORRENTIAL RAIN — 压制所有敌方单位 | `storm3_tropical_storm2` 热带风暴 TROPICAL STORM — 使目标单位撤退，然后随机消灭 1 个敌方单位 |
| 4K | 6 | `sunny3_jungle_fever3` 丛林热 JUNGLE FEVER — 本回合部署或加入的单位获得 +2 攻击力和闪击 | `rain3_torrential_rain3` 骤雨 TORRENTIAL RAIN — 抽 3 张牌，然后选择 1 张弃掉 | `storm3_tropical_storm3` 热带风暴 TROPICAL STORM — 对 1 个目标造成 3 点伤害，再对随机敌方单位重复两次，每次伤害 -1 |
| 6K | 7 | [`sunny4_scorching_sun`](https://www.kards.com/images/card/v52/en-EN/scorching_sun.avif) 骄阳 SCORCHING SUN — 将手中所有单位加入战场，并将其压制到回合结束 | [`rain4_monsoon_rain`](https://www.kards.com/images/card/v52/en-EN/monsoon_rain.avif) 季风雨 MONSOON RAIN — 双方移除手中和/或场上 2 张花费最高的卡牌 | [`storm4_cyclone`](https://www.kards.com/images/card/v52/en-EN/cyclone.avif) 旋风 CYCLONE — 对所有敌方目标造成 2 点伤害 |
| 6K | 8 | `sunny4_scorching_sun2` 骄阳 SCORCHING SUN — 所有友方单位 +3/+3 | `rain4_monsoon_rain2` 季风雨 MONSOON RAIN — 将所有单位的攻击力、防御力和行动花费设为 2 | `storm4_cyclone2` 旋风 CYCLONE — 对目标敌方单位造成 6 点伤害，对相邻敌方单位造成 2 点伤害 |
| 6K | 9 | `sunny4_scorching_sun3` 骄阳 SCORCHING SUN — 友方空军获得等同于其行动花费的攻击力，然后将所有友方单位的行动花费设为 0 | `rain4_monsoon_rain3` 季风雨 MONSOON RAIN — 友方步兵单位 +2/+2，且可再次行动 | `storm4_cyclone3` 旋风 CYCLONE — 所有单位撤退 |

同一行（候选编号，本表"小组"列）内晴/雨/风共享同一个抽签得出的下标——即同一次触发预报，light 档抽到的下标决定了这一行里晴/雨/风哪一个候选被选中，跟社区实测代价表的对照见第 5 节。

## 5. 与社区实测的对照

以上第 1-4 节的全部推导只用到已确认的反编译资料、IDA 字节码和 LCG 引擎常数，没有用到任何社区数据。现在拿这些结果去对照社区独立实测出的规律。

### 5.1 NZ33《天气操作次数计算器》

社区成员 NZ33 制作了一个网页小工具，把实测规律整理成参数化的图论模型：每档天气（2K/4K/6K）是一个大组，大组内分成 3 个候选（对应 §4.3 的候选编号 1/2/3），按环形排列；切换到目标候选所需的操作次数只取决于两者的相对位置：

| 档位 | 环大小 | 同组代价 | 顺时针跨组代价 | 逆时针跨组代价 |
|---|---|---|---|---|
| 2K | 3 | 15 | 3 | 9 |
| 4K | 3 | 15 | 3 | 9 |
| 6K | 3 | 0 | 1 | 2 |

社区还给出周期数字：2K、4K 天气都是 18 个（社区单位）操作一循环，6K 天气是 3 个（社区单位）操作一循环；计算器给出的最简操作数可按循环数整数倍叠加（`+18x` 或 `+3x`）。完整数据见 [社区实测记录](社区实测记录.md) §2.1。

**用第 4.2 节的离散步长表核对**：`d=15` 时，light 和 medium 两档的主导步长都是 `0`（同组、结果不变）——这跟 NZ33 报告的"2K、4K 同组代价都是 15"直接吻合，是两档同时成立。但 `d=3`（NZ33 报告的"顺时针跨组代价"）在两档上**对不上**：light 在 `d=3` 的主导步长是 `-1`（跨了一组，59.0%），medium 在 `d=3` 的主导步长却是 `0`（没跨组，92.0%，比 light 的"跨组"结论更确定）——这跟"2K/4K 顺时针跨组代价都是 3"直接矛盾。`d=15` 一项的吻合，加上 `d=3` 一项的持续矛盾，把此前"整张表都对不上、原因不明"的笼统矛盾，收窄成了具体的"哪一项对不上"：驱动展示结果的确定性机制（重播种公式 + 三次固定深度变换，第 4.2 节已排除"重播种发生多次"和"弹窗交互时序影响变换深度"这两种候选技术性解释）已经确认无误，NZ33 代价表里"同组"这一项数字有了扎实的引擎层解释，"跨组"这一项仍未被解释——可能来源包括 NZ33 数据本身的精确度（本报告没有独立核实过其原始测试数据）、或者"跨类型触发预报"这类目前没有建模进来的变量。

### 5.2 操作间隔的补充测试

一份社区测试视频记录了"操作间隔与是否保留原结果"的关系（插入 1/4 次操作保留、2/5/8 次不保留等），完整转述与定性核对见 [社区实测记录](社区实测记录.md) §2.3；因该视频未标注具体档位，无法换算成 §4.2 的精确数字，只作为定性参考。

## 6. 另见

- [README.md](README.md) — 完整的对局生命周期随机数机制报告（播种时机、重播种触发条件、`cardsRandomStream` 全部已知消费点、动作类型与提交流程）。
- [SpyRing.md](SpyRing.md) — 用同一套随机流机制解释"间谍组织"卡的环形分布规律，方法论上和本文互为印证。
- [社区实测记录](社区实测记录.md) — 社区操作计数方法论、NZ33 计算器与社区实测数据（非主证据）。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该原生字段的真实取值证据。
- [ReseedImpact.md](ReseedImpact.md) — 重播种机制如何逐条解释每一个已观察到的现象。
