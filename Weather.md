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
2. 字面代码里 `_forecastOptions` 一旦非空就直接复用、不再消费随机流；但实测显示 2K/4K 在同一回合内反复重新预报（不插入其他操作）时结果会变化，只有 6K 大概率保持不变。也就是说，`_forecastOptions` 一定会在某处被清空/重建，只是清空点尚未在反编译代码里定位到——第 4 节给出的确定性模型直接来自实测数据，比这段代码字面上的"永久缓存"更准确。
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

### 4.2 从引擎源码解释代价数字的来源

`RandomIntFromRangeWithStream` → `UKismetMathLibrary::RandomIntegerInRangeFromStream`（`Engine/Private/KismetMathLibrary.cpp:1059`，一行转发）→ `FRandomStream::RandRange`（`Engine/Public/Math/RandomStream.h`）。`FRandomStream` 只维护一个 32 位 `Seed`，每次取值都会先执行一次线性同余变换：

```
Seed = Seed * 196314165 + 907633515   (mod 2^32)
```

`GetFraction()` 用变换后 `Seed` 的高 23 位构造出 `[0,1)` 之间的浮点数；`RandRange(Min, Max)` 就是 `Min + floor(GetFraction() * (Max - Min + 1))`。引擎头文件自己在注释里写明"低位质量很差，不要用取模运算符"（Very bad quality in the lower bits. Don't use the modulus operator），说明 Epic 刻意只取高位来避开经典 LCG 低位相关性缺陷——单次调用 `RandRange` 的统计质量本身没有问题，"环形代价"这种结构不会从单次抽样的统计特性里自然长出来。

真正可能产生这种结构的位置，是 `SetRandomStreamWithActionID` 的重播种公式（README §2.2）：`seed = match_id + action_id * 19390`。如果小组下标确实由重播种后单次抽样决定，那么把这个种子公式代入线性同余变换：

```
Seed'(action_id) = (match_id + action_id * 19390) * 196314165 + 907633515   (mod 2^32)
                  = 常数 + action_id * ((19390 * 196314165) mod 2^32)
```

也就是说，`action_id` 每增加 1，变换后的 `Seed'` 就固定增加同一个步长 `Δ = (19390 × 196314165) mod 2^32 = 1190635094`，跟原始 LCG 的性质无关——这本身是一个以 `Δ` 为步长的等差数列。`GetChooseSpawnCards` 里 light/medium/heavy 三次抽签是对同一个重播种后的 `Seed'` 连续做三次线性同余变换，也就是分别处于"变换 1 次""变换 2 次""变换 3 次"之后的状态。因为线性同余变换是仿射映射（`f(x) = A·x + C`），两个只相差一个常数 `d` 的种子，变换 `k` 次之后的差值会精确变成 `A^k · d (mod 2^32)`——`C` 在做差时会抵消掉。也就是说，light（第 1 次变换）、medium（第 2 次）、heavy（第 3 次）三个 tier，各自对应的"`action_id` 每 +1，等效种子步长是多少"并不相同：

| 变换次数 k（对应 tier） | 等效步长 `Δ_k = (19390 × 196314165^k) mod 2^32` | 换算成 3 分桶，平均多少次 `action_id` 递增会让桶下标变化 1 |
|---|---|---|
| k=1（light/2K，若按抽签顺序对应） | 1190635094 | 约 1.20 次 |
| k=2（medium/4K） | 1663813582 | 约 0.86 次 |
| k=3（heavy/6K） | 2854262182 | 约 0.50 次 |

这组精确计算出的数字，跟 NZ33 实测出的代价表对不上，而且对不上的地方本身就是一条有信息量的负面结果：如果 2K 和 4K 真的分别对应 `k=1`、`k=2` 两次不同深度的变换,按上表它们应该有明显不同的"多久变一次"节奏,但 NZ33 的数据显示 **2K 和 4K 的代价完全相同**（都是同组 15、顺时针 3、逆时针 9），只有 6K 独立不同。这排除了"三个 tier 的小组下标都是各自独立、直接对重播种后的流做一次 `RandRange` 抽样"这个最简单的假设——如果真是这样，2K 和 4K 不应该表现出一模一样的节奏。

更可能的解释是：2K 和 4K 的"当前小组下标"共享同一个计算路径或同一个显式计数器（例如两者都读同一个"本回合已使用操作数"之类的整数变量，再做一次简单的取模/查表，而不是分别各自调用一次 `RandomIntFromRangeWithStream`），只有 6K 因为候选池经常退化到只剩 1 个可选项（第 2.3 节），表现出独立的、更小的等效代价。换句话说：`_forecastOptions` 展示给玩家的具体是哪三张卡，很可能不是 `GetChooseSpawnCards` 这段蓝图代码字面呈现的"每次都各自独立抽签"，而是有另一层尚未定位到的逻辑（可能在原生 C++ 侧）先计算出一个"当前小组指针"，再用这个指针去查表——`RandomIntFromRangeWithStream` 本身出现在反编译代码里是真实的，但它计算出的下标是否就是玩家最终看到的那个下标，仍然没有被独立证实。这是本报告目前最明确、也最值得用 IDA 继续追查的开放问题：需要找到"小组指针"实际的存储位置和推进它的代码，而不是停留在对 `FRandomStream` 统计性质的推演上。

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
