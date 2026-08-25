# 天气系统：从代码到"可控天气"

来源：FModel 反编译的蓝图伪代码（`Content/Blueprints/`），交叉验证 IDA 反编译的原生实现和 Unreal Engine 5.6 引擎源码。行号均指本仓库 `FModel-Exports/` 下对应的反编译导出文件。核心随机流机制（`cardsRandomStream` 的播种/重播种规则）见 [README.md](README.md) §1-§2，本文只讲天气系统本身怎么用这条流。

## 1. `BP_CardFunctions` 里跟预报/随机有关的函数

`BP_CardFunctions`（蓝图侧单例，代码里叫 `cardFunction`）是全游戏所有"权威随机数"和天气预报逻辑的落脚点。跟本文主题相关的函数：

| 函数 | 位置 | 作用 |
|---|---|---|
| `RandomIntFromRangeWithStream(min, max, out result)` | `BP_CardFunctions.cpp:12423` | 唯一的随机数入口封装，内部就是一行 `UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, min, max)`。全游戏所有卡牌（天气、间谍组织、任何"随机抽一个"效果）都通过这个函数取随机数，没有例外的第二条路径。 |
| `SetRandomStreamByMatchID(MatchID)` | `BP_CardFunctions.cpp:12339` | 用 `MatchID` 重置 `cardsRandomStream`（详见 README §1）。 |
| `Forecast(cardTriggeringForecast, out qqq)` | `BP_CardFunctions.cpp:23533` | 玩家打出"天气预报"类卡牌时调用。这个函数本身不产生随机数——它只是把三张固定的"一级天气代表卡"（`card_event_sunny1_blue_sky` / `card_event_rain1_mist` / `card_event_storm1_gale`）扔给 UI 弹一个"选择要抽哪张"的面板（`NotifySelectCardToDrawPending`）。真正的随机发生在玩家选中某张代表卡之后，见下一节的 `GetChooseSpawnCards`。 |
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

**玩家实际看到的流程，跟"打出预报卡→弹三选一"这个直觉描述不完全一样，这里先澄清一下时序（根据反馈更正）**：预报实际上是**两次连续的玩家选择**，不是"选一次、其余自动"：① `Forecast()`（§1）把三张一级天气代表卡（`sunny1`/`rain1`/`storm1`，对应晴/雨/风三种天气类型）传给 `NotifySelectCardToDrawPending` 弹面板，**由玩家选择要哪一种天气类型**，选中的这张代表卡随即被打出；② 该代表卡打出后 `OnPlayedFromHand` 触发，进而调用它自己的 `GetChooseSpawnCards`，弹出第二个面板，**再由玩家在轻/中/重三个候选里选一个**，决定最终抽到哪张具体的天气效果卡。也就是说从服务端/`action_id` 的角度看，"预报"这个玩家体验实际上对应至少两个独立的、都需要玩家操作的游戏内事件：① 天气类型选择（对应 README §3 提到的 `CS`/`XActionCardToDrawSelected` 或类似的"抽卡选择结果"动作类型）；② 天气强度选择，触发 `GetChooseSpawnCards` 消耗三次 `cardsRandomStream`。这两步各自是否推进 `action_id`、消耗几次随机数，目前还没有用真实抓包逐条核实过——是本报告一个新发现的、值得优先核实的具体验证点。

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
2. **`_forecastOptions` 不需要被清空——它天生就是空的，这一点已经从调用链上确认**。`GetChooseSpawnCards` 是在哪个对象上被调用的，直接决定了这个问题的答案：反编译 `BP_CardFunctions.cpp:selectCardToDraw`（真正触发这次三选一的入口函数）确认，调用点是 `cardSelecting->GetChooseSpawnCards(...)`（`BP_CardFunctions.cpp:5570`），而 `cardSelecting = GetCardFromID(cardSelectingCardToDraw)`（`BP_CardFunctions.cpp:5550-5552`）——也就是说，`GetChooseSpawnCards` 调用的对象，是"这次触发选择流程的那个具体卡实例"，由它自己独一无二的 `cardID` 查出来的，**不是** `GetAllActiveStaticCards()` 用来扫描标签的那个持久化静态对象。玩家每次抽到/打出一张一级天气代表卡，都是 `CreateCard` 新建出来的一个全新 `UBaseCardObject` 实例，带着自己的 `cardID`；`_forecastOptions` 是这个新实例上的 UPROPERTY，新实例创建时天然是空数组（UE 的默认零值初始化）。也就是说，**"缓存复用"这个分支在正常对局流程里根本不会被触发**——不是某处代码负责清空它，而是每一次触发预报，用来装 `_forecastOptions` 的对象本身就是全新的，没有"上一次的缓存"可言。这跟实测确认的"每次重新预报都是真实的、全新的三连抽"完全吻合，不需要假设任何未定位到的清空逻辑。（第 1 点提到的"检查了 blitz_doctrine/sabotage/heroes_of_the_soviet_union"，此前认为这几张卡实现模式不同，现在看其实是同一件事的另一种体现：它们的 `PossibleCards` 也是各自新实例上的字段，"无条件重新扫描并追加"这个写法之所以不会真的产生重复堆叠，也是因为每次调用发生在不同的新实例上，根本不会重复调用同一个对象两次。）
3. 雨（rain）/风暴（storm）系的 `card_event_rain1_mist`、`card_event_storm1_gale` 是同构实现（把 `subtype.sunny` 换成 `subtype.rain`/`subtype.storm`，逻辑一模一样）。

### 2.3 候选池大小影响可变性，但不是唯一原因

"6K 在连续两次预报之间不做别的事时经常看起来不变，2K/4K 会变"这个现象，根源不在候选池大小，而是第 4.1 节代价表本身的数字结果——完整推导见 [ReseedImpact.md](ReseedImpact.md) §1：一次完整预报固定消耗 3 个单位，连续两次预报消耗 6 个单位；6K 顺时针跨组代价是 1、环上 3 个小组，`6 ÷ 1 = 6` 步，`6 mod 3 = 0`，正好绕完两整圈落回起点；2K/4K 顺时针跨组代价是 3，`6 ÷ 3 = 2` 步，落在不同小组上。这是纯粹的代价数字代入算术，不需要假设候选池大小或其他额外机制。

## 3. 核心结论：天气结果是确定性序列，已由真实抓包证实可预测

结合 README.md §2-§4 交叉验证的原生机制和真实抓包证据：

1. 真实抓包（`本地抓包目录/`）已确认，真实对局里 `AMatchControllerV2::bUseTurnSwitchValidation`（native `+0x7A8`）是**开启**的——对局引导数据明文带着 `"validate_turn_switches":true`（详见 [`evidence/bUseTurnSwitchValidation.md`](evidence/bUseTurnSwitchValidation.md)）。这意味着 `cardsRandomStream` 每次创建/确认一个动作都会重播种为 `match_id + action_id * 19390`，而 `action_id` 是双方共享、从 1 开始逐一递增的简单计数器（详见 [`evidence/action_id-real-capture-sequence.md`](evidence/action_id-real-capture-sequence.md)）。
2. 天气预报的三连抽（light→medium→heavy）严格按固定顺序发生，候选池大小、每类天气卡数量都是公开可数的静态信息（活跃卡池全程加载，`GetAllActiveStaticCards` 谁都能枚举）。只要知道双方到目前为止一共发生过多少个动作，理论上就能反推出结果——这是社区仅凭对局内观测记录、用归纳法就能摸出规律的根本原因：规律确实存在，是代码层面设计如此，不是玄学。
3. 官方已于 2026-08-23 就"秋季锦标赛选手利用特定操作控制预报机制结果"发布说明，确认这一现象属实，技术团队和赛事团队正在调查，并将其定性为游戏机制层面的问题，而非外挂/作弊。截至该说明发布，尚未给出具体修复方案或补偿。

天气系统的"伪随机"不是比喻——它是以 `match_id` 为种子、按 `action_id` 重播种的确定性伪随机数序列，理论上全程可预测。社区通过对局内可观测行为反推出的规律表，和代码+抓包交叉验证出的机制完全吻合。为什么这套机制构成一个可被利用的漏洞、玩家具体怎么操作利用它，见 [ReseedImpact.md](ReseedImpact.md) §2。第 4.2 节从引擎源码逐位推导代价数字来源的尝试，跟 NZ33 实测代价表本身对不上，仍是一个开放问题，跟本节结论（结果确定性可预测）互不影响。

## 4. 确定性模型：NZ33「天气操作次数计算器」

社区成员 **NZ33** 制作了一个网页小工具《天气操作次数计算器》，把实测规律整理成一套参数化的图论模型，据反馈计算结果准确。本节以这个模型为准。

### 4.1 模型结构

每一档天气（2K/4K/6K）是一个大组，大组内部分成 3 个小组、按环形排列；每个小组固定装着 3 个具体效果（晴/雨/风各一个）。从当前效果切换到目标效果所需的操作次数，只取决于两者的相对位置：

| 档位 | 环大小 | 同小组代价 | 顺时针跨组代价 | 逆时针跨组代价 |
|---|---|---|---|---|
| 2K | 3 | 15 | 3 | 9 |
| 4K | 3 | 15 | 3 | 9 |
| 6K | 3 | 0 | 1 | 2 |

"代价"指：从当前展示的效果切换到目标效果，中间需要发生多少次会推进随机流的操作。6K 的顺时针跨组代价只有 1，几乎任何一次有效操作都足够让它跳到下一个小组；但同一小组内部三个效果之间的切换代价是 0，两次预报之间如果没有发生跨组事件，6K 展示的会一直是同一小组内的效果，看起来像没变。2K/4K 相反：跨组代价是 3，同组代价高达 15，通常需要至少 3 次有效操作才会跳到下一个小组——这正是 2K/4K 在同回合内不插入额外步骤也会变化、只有 6K 大概率保持不变的成因。

### 4.2 引擎算法：直接反编译确认，不依赖任何未验证的源码假设

`cardFunction->RandomIntFromRangeWithStream(min, max, out)` → `BP_CardFunctions.cpp:12423`（蓝图，FModel 反编译确认，一行转发）→ `UKismetMathLibrary::RandomIntegerInRangeFromStream`。这个原生函数在 `kards-Win64-Shipping.exe` 里的真实反编译（IDA，地址 `0x143ddce50`，已在本会话重命名为 `UKismetMathLibrary_execRandomIntegerInRangeFromStream`）如下（`v7` 指向 `FRandomStream` 结构体，`+0` 是 `InitialSeed`，`+4` 是 `Seed`；`v11`=`min`，`v12`=`max-min+1`）：

```cpp
v13 = 196314165 * *((_DWORD *)v7 + 1) + 907633515;   // Seed = Seed*196314165 + 907633515 (mod 2^32)
*((_DWORD *)v7 + 1) = v13;                            // 写回 Seed
result = (v13 >> 9) | 0x3F800000;                     // GetFraction()：取高 23 位构造 [1,2) 浮点数
v14 = v11 + (int)(float)((float)(*(float *)&result - 1.0) * (float)v12);   // Min + floor(GetFraction()*(Max-Min+1))
```

这不是从 UE5.6 引擎源码推断或假设出来的公式，是直接从这个二进制文件（Kards 使用的 UE5.6 fork）反汇编读出来的字节码，逐条对应上面四行 C 伪代码——常数 `196314165`、`907633515` 已用 `find_bytes` 在整个二进制里定位（命中 `0x140eaf4b2` 等多处，包括这个函数本身），确认这个 fork 没有修改这两个 LCG 常数。每次调用 `RandomIntFromRangeWithStream`，`Seed` 恰好做一次这样的变换，返回值恰好是这一次变换后的结果——没有隐藏的多次调用或额外处理。

`GetChooseSpawnCards`（`card_event_sunny1_blue_sky.cpp:93-209`，蓝图，FModel 反编译确认）对 light/medium/heavy 三个候选池依次各调用一次 `RandomIntFromRangeWithStream`，顺序固定；`SetRandomStreamWithActionID`（`BP_OnlineMatch.cpp:24520-24536`，蓝图，FModel 反编译确认）把 `cardsRandomStream` 重播种为 `match_id + action_id * 19390`——这两点前面章节已经交叉确认过，不再重复。

以上是本报告目前能够从 IDA/FModel 直接确认、无需任何额外假设的全部内容。

**证明：字面的"三连抽直接决定展示结果"模型，在数学上不可能产生 NZ33 记录的 2K/4K 代价相同这一现象。** 这不是猜测，是从上面已经字节级确认的 LCG 公式直接算出来的：如果 light（2K）、medium（4K）、heavy（6K）三档的展示结果，就是 `GetChooseSpawnCards` 里那三次连续调用各自返回的原始下标，那么 light 对应的是重播种后第 1 次变换的结果，medium 是第 2 次。线性同余变换是仿射映射 `f(x)=Ax+C`，两个只差常数 `d` 的种子，变换 `k` 次后的差值精确是 `A^k·d (mod 2^32)`。用已确认的 `A=196314165` 直接算：

```
A^1 mod 2^32 = 196314165
A^2 mod 2^32 = 3026498297
```

这两个数不相等，而且不存在任何巧合让它们相等——这意味着 light（k=1）和 medium（k=2）在"`action_id` 每 +1，等效位移多少"这件事上，数学上必然不同。但 NZ33 实测代价表明确记录 2K 和 4K 的代价完全相同（同组 15、顺时针 3、逆时针 9，一模一样）。**这两个事实不可能同时成立**——所以"三连抽的原始返回下标就是玩家看到的展示结果"这个假设，已经被严格证伪，不再是待验证的假设，而是被排除的可能性。

排除这个假设之后，剩下的可能性只有两类，而且已经可以逐一排查：
1. **重播种在三次抽签之间又发生了一次**（不是一次重播种后连续三次变换）——已排除：`SetRandomStreamWithActionID` 只在动作创建时调用一次（README §2.2 调用点 A），`GetChooseSpawnCards` 内部没有再次调用它或 `SetRandomStreamByMatchID` 的代码（本节反编译到的蓝图源码里没有这两个函数名出现在 `GetChooseSpawnCards` 内部）。
2. **`_lightWeatherCards`/`_mediumWeatherCards`/`_heavyWeatherCards` 数组下标，跟 NZ33 的"小组 1/2/3"编号不是简单的对应关系**——这一点用现有的静态反编译资料**无法进一步证实或证伪**：数组是 `GetAllActiveStaticCards` 遍历 `GetAllStaticCardsSortedByName()` 的结果按标签过滤而来，`GetAllStaticCardsSortedByName` 按卡牌 `Name`（即 `card_event_sunny2_heatwave`/`heatwave2`/`heatwave3` 这类字符串）做的具体排序规则、以及这个排序结果是否在所有语言/建置版本下稳定，本报告没有找到反编译依据能确认，需要运行时读取这三个数组的实际内容（内存读取或对局内添加调试输出）才能验证——这是静态反编译方法本身的边界，不是分析没做到位。

结论：驱动 2K/4K/6K 展示结果的具体机制，不是"三次连续调用的原始返回值直接展示"，这一点已经证明；真正的机制需要运行时验证才能确定，属于本报告静态分析方法论的边界，不属于待验证假设。

### 4.2.1 假设一场对局，逐步套用上面的算法（数值示例，不是真实抓包）

下面用一个**假设**的对局，把 §4.2 确认的公式从头到尾算一遍，展示这套机制实际怎么运作。`match_id` 和 `action_id` 用的是虚构数字，不对应任何真实对局；候选池大小按每档最简单的情形（3 个候选，下标 0-2）处理，不代表真实候选池一定是 3——这只是为了让计算过程可复现、可验证。

假设 `match_id = 1000000000`，玩家在本回合触发预报时，喂给 `SetRandomStreamWithActionID` 的 `action_id = 10`：

**第一步，重播种**（`BP_OnlineMatch.cpp:24520-24536`）：
```
seed = match_id + action_id * 19390 = 1000000000 + 10*19390 = 1000193900
cardsRandomStream.Seed = 1000193900
```

**第二步，`GetChooseSpawnCards` 依次调用三次 `RandomIntFromRangeWithStream(0, 2)`**（严格按 §4.2 反编译出的公式，逐次用上一步算出的 `Seed` 继续变换）：

| 第几次调用 | 变换前 Seed | `Seed = Seed*196314165+907633515 mod 2^32` | 返回下标（`floor(GetFraction()*3)`） |
|---|---|---|---|
| 1（light） | 1000193900 | 1626977479 | 1 |
| 2（medium） | 1626977479 | 4280773790 | 2 |
| 3（heavy） | 4280773790 | 431904801 | 0 |

也就是说，这次预报玩家会看到：light 桶第 1 号候选、medium 桶第 2 号候选、heavy 桶第 0 号候选。

**第三步，玩家不做别的事，立刻再打出一张预报牌**：按 ReseedImpact.md §1 已确认的"一次预报消耗 3 个本地计数器单位"，这次触发时喂给重播种公式的 `action_id` 变成 `10+3=13`：

```
seed = 1000000000 + 13*19390 = 1000251870
```

重复第二步的三次调用，结果是 light=0、medium=0、heavy=0——跟第一次（1、2、0）相比，light 和 medium 的下标变了，heavy 没变（这次示例里恰好前后两次 heavy 都落在下标 0，属于这组具体数字的巧合，不是普遍规律，因为本示例统一假设三档桶大小都是 3，不是真实的 NZ33 环形小组结构）。

这个计算过程完全可以用 §4.2 那四行反编译出的公式重新算一遍验证——本节的作用只是把公式具体落到一组数字上，让"重播种→连续三次 LCG 变换→取下标"这套机制变得可核对，不是用来复现 NZ33 代价表的具体数字（那部分仍是 §4.2 结尾指出的开放问题）。

### 4.3 小组编号与真实卡牌对照表

`Content/Blueprints/Cards/Neutral/events/` 下每种天气效果卡都有 3 个版本，文件名后缀（无后缀/2/3）对应上表模型里的小组编号 1/2/3，每张卡的效果文本能和 NZ33 计算器内部的候选数据逐一对上。9 个小组、每组 3 张（晴/雨/风各一张），共 27 张效果卡（小组 1/4/7 的卡名带官方站点卡图链接，非本仓库转载；小组 2/3/5/6/8/9 版本在官方 API 里用的内部 id 跟 FModel 导出名不是简单的加数字后缀关系，尚未逐一核实，完整已确认清单见 [`evidence/card_image_urls.json`](evidence/card_image_urls.json)）：

| 大组 | 小组 | 晴（Sunny） | 雨（Rain） | 风（Storm） |
|---|---|---|---|---|
| 2K | 1 | [`sunny2_heatwave`](https://www.kards.com/images/card/v52/en-EN/heatwave.avif) HEATWAVE — 全体+2 攻（空军+3） | [`rain2_deluge`](https://www.kards.com/images/card/v52/en-EN/deluge.avif) DELUGE — 6 点防御随机分配给友方 | [`storm2_thunderstorm`](https://www.kards.com/images/card/v52/en-EN/thunderstorm.avif) THUNDERSTORM — 3 点伤害随机分配给敌方 |
| 2K | 2 | `sunny2_heatwave2` HEATWAVE — 己方+1 攻，费用-1 | `rain2_deluge2` DELUGE — 敌方全体-1 攻 | `storm2_thunderstorm2` THUNDERSTORM — 撤退目标及同名单位 |
| 2K | 3 | `sunny2_heatwave3` HEATWAVE — 本回合部署单位对随机敌人造成等同攻击力的伤害 | `rain2_deluge3` DELUGE — 压制目标单位并抽 1 张牌 | `storm2_thunderstorm3` THUNDERSTORM — 对随机敌方单位造成 5 点伤害 |
| 4K | 4 | [`sunny3_jungle_fever`](https://www.kards.com/images/card/v52/en-EN/jungle_fever.avif) JUNGLE FEVER — 牌库顶单位加入支援线并钉住 | [`rain3_torrential_rain`](https://www.kards.com/images/card/v52/en-EN/torrential_rain.avif) TORRENTIAL RAIN — 步兵/总部+3 防，其余+2 防 | [`storm3_tropical_storm`](https://www.kards.com/images/card/v52/en-EN/tropical_storm.avif) TROPICAL STORM — 双方洗回手牌再摸等量的牌 |
| 4K | 5 | `sunny3_jungle_fever2` JUNGLE FEVER — 复制一个友方单位加入支援线并钉住 | `rain3_torrential_rain2` TORRENTIAL RAIN — 钉住全部敌方单位 | `storm3_tropical_storm2` TROPICAL STORM — 撤退目标，再摧毁一个随机敌方单位 |
| 4K | 6 | `sunny3_jungle_fever3` JUNGLE FEVER — 本回合部署/加入的单位+2 攻并获得闪击 | `rain3_torrential_rain3` TORRENTIAL RAIN — 摸 3 张牌后弃 1 张 | `storm3_tropical_storm3` TROPICAL STORM — 对敌人造成 3 点伤害，再对随机敌方单位重复两次（每次-1 伤害） |
| 6K | 7 | [`sunny4_scorching_sun`](https://www.kards.com/images/card/v52/en-EN/scorching_sun.avif) SCORCHING SUN — 手牌全部单位直接上场并钉住 | [`rain4_monsoon_rain`](https://www.kards.com/images/card/v52/en-EN/monsoon_rain.avif) MONSOON RAIN — 双方各移除 2 张手牌/场上最贵的卡 | [`storm4_cyclone`](https://www.kards.com/images/card/v52/en-EN/cyclone.avif) CYCLONE — 对敌方全体造成 2 点伤害 |
| 6K | 8 | `sunny4_scorching_sun2` SCORCHING SUN — 己方全体+3+3 | `rain4_monsoon_rain2` MONSOON RAIN — 全部单位攻/防/费用设为 2 | `storm4_cyclone2` CYCLONE — 对目标造成 6 点伤害，相邻敌方 2 点 |
| 6K | 9 | `sunny4_scorching_sun3` SCORCHING SUN — 己方空军攻击力等于费用，之后全体费用清零 | `rain4_monsoon_rain3` MONSOON RAIN — 己方步兵+2+2 并可再次行动 | `storm4_cyclone3` CYCLONE — 全体单位撤退 |

同一行（小组）内晴/雨/风互相切换走"同组代价"；切到下一个小组（组 1→2→3→1，或 4→5→6→4，或 7→8→9→7）走"顺时针代价"；反方向走"逆时针代价"。

## 5. 另见

- [README.md](README.md) — 完整的对局生命周期随机数机制报告（播种时机、重播种触发条件、`cardsRandomStream` 全部已知消费点、动作类型与提交流程）。
- [SpyRing.md](SpyRing.md) — 用同一套随机流机制解释"间谍组织"卡的环形分布规律，方法论上和本文互为印证。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该原生字段的命名更正与真实取值证据。
- [ReseedImpact.md](ReseedImpact.md) — 重播种机制如何逐条解释每一个已观察到的现象。
