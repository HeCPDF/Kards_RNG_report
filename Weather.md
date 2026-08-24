# 天气系统：从代码到"可控天气"

来源：FModel 反编译的蓝图伪代码（`Content/Blueprints/`）。行号均指本仓库 `FModel-Exports/` 下对应的反编译导出文件。核心随机流机制（`cardsRandomStream` 的播种/重播种规则）见 [README.md](README.md) §1-§2，本文只讲天气系统本身怎么用这条流。

## 1. `BP_CardFunctions` 里跟预报/随机有关的函数

`BP_CardFunctions`（蓝图侧单例，代码里叫 `cardFunction`）是全游戏所有"权威随机数"和天气预报逻辑的落脚点。跟本文主题相关的函数：

| 函数 | 位置 | 作用 |
|---|---|---|
| `RandomIntFromRangeWithStream(min, max, out result)` | `BP_CardFunctions.cpp:12423` | 唯一的随机数入口封装，内部就是一行 `UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, min, max)`。**全游戏所有卡牌**（天气、间谍组织、任何"随机抽一个"效果）都通过这个函数取随机数，没有例外的第二条路径。 |
| `SetRandomStreamByMatchID(MatchID)` | `BP_CardFunctions.cpp:12339` | 用 `MatchID` 重置 `cardsRandomStream`（详见 README §1）。 |
| `Forecast(cardTriggeringForecast, out qqq)` | `BP_CardFunctions.cpp:23533` | 玩家打出"天气预报"类卡牌时调用。这个函数本身**不产生随机数**——它只是把三张固定的"一级天气代表卡"（`card_event_sunny1_blue_sky` / `card_event_rain1_mist` / `card_event_storm1_gale`）扔给 UI 弹一个"选择要抽哪张"的面板（`NotifySelectCardToDrawPending`）。真正的随机发生在玩家选中某张代表卡之后，见下一节的 `GetChooseSpawnCards`。 |
| `GetAllForecastCards(...)` | `BP_CardFunctions.cpp:23084` | 从 `GetAllActiveStaticCards` 里按 `subtype.rain` / `subtype.storm` / `subtype.sunny` 三个 GameplayTag 筛出所有"天气系"卡牌（不分轻重级），是天气选卡候选池的上游数据源之一。 |
| `GetRandomCard(cards, skipCustomAlways, out randomCard)` | `BP_CardFunctions.cpp:5248` | 通用的"从一堆卡里随机挑一张"，被非天气类效果复用（先检查是否有打了 `AlwaysSelectedAsRandom` 标记的卡，优先在这个子集里随机；否则在全体里随机）。天气选卡没有用这个函数，是各天气代表卡自己实现了一遍三段式抽取（见下）。 |
| `ShuffleDeckBySide` / `DiscardRandomCardFromHand` / `GiveRandomCombatKeyword` | `BP_CardFunctions.cpp:12351` / `6492` / `22523` | 同样走 `cardsRandomStream`，但跟天气无关，属于洗牌/弃牌/随机赋予关键词，这里不展开，完整列表见 README §3。 |

## 2. 天气卡怎么实现：以 `card_event_sunny1_blue_sky`（"将是晴天"）为例

天气系统的卡牌全部放在 `Content/Blueprints/Cards/Neutral/events/` 下，命名规律是 `card_event_<天气类型><级别>_<卡名>`（`sunny1`=一级晴天代表卡，`sunny2_heatwave`=晴天的二级效果卡……以此类推，`rain`/`storm` 同理）。这些卡**全部位于"活跃卡池"（Active Static Cards），运行时全程被加载**——不是打出来才实例化，而是每一局开始就作为场上常驻的静态对象存在，随时可以被 `GetAllActiveStaticCards()` 枚举到。

### 2.1 每张子天气卡怎么"声明"自己是哪一类天气

`Ucard_event_sunny1_blue_sky_C` 的 `GameplayTags` 字段：

```cpp
struct FGameplayTagContainer GameplayTags = FGameplayTagContainer({
    FGameplayTag::RequestGameplayTag(FName("autoplay"))
});
```

`sunny1_blue_sky` 是"一级代表卡"，本身不带 `subtype.*` 分级标签（它只是 UI 上给玩家选的那三个选项之一）。真正携带分级信息的是各个"效果卡"，例如同目录下的 `card_event_sunny2_heatwave`：

```cpp
struct FGameplayTagContainer GameplayTags = FGameplayTagContainer({
    FGameplayTag::RequestGameplayTag(FName("subtype.sunny")),
    FGameplayTag::RequestGameplayTag(FName("subtype.lightWeather"))
});
```

即：`subtype.sunny`/`subtype.rain`/`subtype.storm` 标记"哪一种天气"，`subtype.lightWeather`/`subtype.mediumWeather`/`subtype.heavyWeather` 标记"轻/中/重（对应俗称的 2K/4K/6K）级别"。天气系统靠遍历全部活跃卡、按这两组标签分类，而不是靠一张写死的表——新增一张天气卡，只要打上正确的标签、丢进 `Neutral/events/` 目录，就会自动被下面这套逻辑收编。

### 2.2 `GetChooseSpawnCards`：三级天气怎么被随机选出来

真正的随机发生在 `sunny1_blue_sky` 自己的 `GetChooseSpawnCards`（`card_event_sunny1_blue_sky.cpp:93-209`），UI 弹出"选择天气"面板时会调用它来决定"轻/中/重三个候选各是谁"：

```cpp
public void GetChooseSpawnCards(TArray<UBaseCardObject*>& cards, bool& markAsSeen, bool& keepOrder)
{
    if (!Array_IsEmpty(_forecastOptions))
    {
        // 缓存命中：_forecastOptions 一旦非空就直接复用，整个函数直接返回，
        // 不会再消耗 cardsRandomStream 里的任何新值。
        cards = _forecastOptions;
        markAsSeen = false;
        keepOrder = true;
        return;
    }

    // 缓存未命中：遍历全部"活跃静态卡"，按 GameplayTag 分成三桶
    GetAllActiveStaticCards(true, true, /*out*/ allCards);
    for (card : allCards)
    {
        if (!card.HasTag("subtype.sunny")) continue;              // 只挑晴天系
        if (card.HasTag("subtype.heavyWeather"))  _heavyWeatherCards.Add(card);
        else if (card.HasTag("subtype.mediumWeather")) _mediumWeatherCards.Add(card);
        else if (card.HasTag("subtype.lightWeather"))  _lightWeatherCards.Add(card);
    }

    // 依次从三个桶里各随机挑一张，顺序固定：light → medium → heavy，
    // 同一条 cardsRandomStream 连续消耗三次
    randomResult = cardFunction->RandomIntFromRangeWithStream(0, _lightWeatherCards.Length - 1);
    _forecastOptions.Add(_lightWeatherCards[randomResult]);

    randomResult = cardFunction->RandomIntFromRangeWithStream(0, _mediumWeatherCards.Length - 1);
    _forecastOptions.Add(_mediumWeatherCards[randomResult]);

    randomResult = cardFunction->RandomIntFromRangeWithStream(0, _heavyWeatherCards.Length - 1);
    _forecastOptions.Add(_heavyWeatherCards[randomResult]);
}
```

要点：

1. **三个 tier 各自独立、等概率地在各自桶内抽一个下标**——不是从全体天气卡里抽，而是"轻/中/重"三次分别抽签，且顺序固定为 light→medium→heavy，共消耗 `cardsRandomStream` 三次。
2. **`_forecastOptions` 字段在这份代码里从未被清空**：一旦这局这张卡触发过一次 `GetChooseSpawnCards`，往后所有调用只要 `_forecastOptions` 非空就直接复用缓存、不再消费随机流。这是天气选项"点开预报面板结果不变"的第一层原因（缓存命中，压根没走随机）。
3. `雨（rain）`/`风暴（storm）`系的 `card_event_rain1_mist`、`card_event_storm1_gale` 是同构实现（把 `subtype.sunny` 换成 `subtype.rain`/`subtype.storm`，逻辑一模一样）。

### 2.3 桶的大小才是"6K 经常不变、2K/4K 会变"的关键

`heavyWeatherCards`（6K 级）候选池通常比 `lightWeatherCards`（2K 级）小得多——重量级天气效果本身设计的种类就少，且"回合内某张重量级天气正处于场上/冷却"时会被 `GetAllActiveStaticCards` 排除出候选。当某个 tier 的候选池只剩 1 个成员时，`RandomIntFromRangeWithStream(0, 0)` 不管 `cardsRandomStream` 内部状态如何变化，返回值永远是下标 `0`——**这不是没有随机，而是根本没得选**，跟随机数本身是否可预测无关。这解释了"6K 经常纹丝不动、2K/4K 却在变"这种不对称现象：三个 tier 用的是同一条流，但候选池大小完全不同，观察到的"稳定性"差异来自桶大小，不是三个 tier 被区别对待。

## 3. 回到社区的核心质疑：天气到底是不是"可控的伪随机"

结合 README.md §2-§4 已经交叉验证的原生机制，可以把天气系统的完整因果链拼起来：

1. 全场只有 `match_id` 播种一次（`SetRandomStreamByMatchID`），此后是否按 `action_id` 重播种取决于原生字段 `AMatchControllerV2::bUseTurnSwitchValidation`（native offset `0x7A8`，字段名已通过 Dumper-7 SDK 反射导出确认，详见 [`evidence/bUseTurnSwitchValidation.md`](evidence/bUseTurnSwitchValidation.md)）。这个字段在全部反编译到的蓝图代码里**只被读取、从未被赋值**——说明它的默认值/触发条件写在原生 C++ 里，蓝图层看不到，但**只要它是 false，`cardsRandomStream` 就整场只播种一次**，之后所有随机效果（天气三连抽、间谍组织抽卡……）都在同一条从 `match_id` 确定性生成的序列上按调用顺序连续取值。
2. 天气预报的"三连抽"（light→medium→heavy）严格按固定顺序发生，且候选池大小、每类天气卡数量都是公开可数的静态信息（活跃卡池全程加载，`GetAllActiveStaticCards` 谁都能枚举）。也就是说：**只要知道"这是本场第几次消耗 `cardsRandomStream`"，理论上就能反推出结果**——这正是 2026-08-24 那期"逻辑推理就能出"系列视频里，主播用纯粹的实测记录+归纳法（不看任何反编译代码）就能摸出规律的根本原因：规律确实存在，且是代码层面上"设计如此"，不是玄学。
3. `_forecastOptions` 永不清空的缓存机制，意味着"重复打开预报面板"这个动作本身**不会**推进随机流——但玩家能做的、真正推进流的动作（部署/激活/取消一次反制之类会触发其他随机效果或 `action_id` 计数器的操作）会。社区实测描述的"挂反制→取消反制→不耗费用地控制天气"，符合的正是这条链路：这类操作要么本身不消耗随机数、只是用来"占位"等待其他事件推进 `cardsRandomStream` 的消费位置，要么是以可预测的方式消耗固定数量的随机数——只要打法固定，序列位置就固定，天气结果自然可复现、可"控制"（准确说是"可预判/可对齐"，不是让引擎凭空产生一个你想要的值）。
4. 官方也已经在 2026-08-23 对"秋季锦标赛选手利用特定操作控制预报机制结果"一事发布说明，明确表态"技术团队和赛事团队正在进行紧急调查"，并把这个现象定性为**游戏机制**层面的问题，而不是外挂/作弊（"卡巴克"）——这与本文和 README 交叉验证出的结论（"确定性伪随机序列 + 可数的候选池 + 玩家可控的推进节奏"）完全吻合：这不是玄学，是可以从代码结构上直接解释、且官方自己也确认"结果可以被特定操作序列控制"的既有事实。截至该说明发出时，官方尚未给出具体修复方案或补偿。

**结论**：天气系统的"伪随机"不是比喻——它就是字面意义上的、以 `match_id` 为种子、按固定调用顺序推进的确定性伪随机数序列，在满足 `bUseTurnSwitchValidation == false`（尚未定位到原生赋值点/默认值，但蓝图代码证实这个分支切实存在且可达）的对局下，理论上全程可预测。社区通过对局内可观测行为（点击次数、操作类型）反推出的"规律表"，和代码交叉验证出的"同一条流按调用次序消费"完全对得上，不需要引入任何额外假设。

## 4. 社区归纳出的具体规律表（2026-08-24 弹幕/评论区整理）

以下内容来自社区观众的实测归纳，本文只做转述和框架性解释，**未逐一反编译验证每个具体的候选序号/桶内顺序**（跟第 2-3 节不同，第 2-3 节的机制描述是直接来自反编译代码的确认结论）。之所以收录，是因为它跟第 2、3 节确认的机制（三个 tier 各自独立按序抽签、桶内顺序固定、不重播种时结果由"这是第几次消费流"唯一决定）在结构上完全吻合，可以看作是"用纯粹的对局内观测，把第 3 节的抽象结论还原成一张可查表"的尝试：

- 观众把 2K、4K 两档天气各自的候选，按桶内顺序编号为 A1/A2/A3（2K）、B1/B2/B3（4K），每个编号对应晴/雨/风三条效果线里的一个具体效果（例如"A1"这一档，晴对应"+1/-1"效果、雨对应"-1/-1"效果、风对应"撤退"）；6K 档同理编号为 C1/C2/C3。这跟第 2.1-2.2 节确认的"每个 tier 桶里有若干个候选、按下标随机选一个"结构一一对应——A/B/C 就是"桶内下标"，晴/雨/风就是"这个下标对应的具体天气类型"。
- 观众发现：**如果开预报之前，本回合已经使用的指令数不超过 2，那么下一次预报的编号，有约 1/2 的概率相对当前编号"升一位"**（例如 A2→A3、B2→B3），且"A、B 两档要么同时按同一方向变化、要么其中一档变化会导致下一回合另一档跟着变化"，呈现出观众描述的"当一个序号升降时，另一个下回合必然进行升降"的联动关系。
- 如果开预报之前本回合已用指令数**大于 3**，A、B 两档编号会同时"升一"，且这个"同时升一"的状态会持续到本回合第 4 次预报为止，之后再回落到"前一次的规律"。
- 6K（C 档）呈现出一个观众描述为"C1→C2→C3→C1……"的三段循环，且 C2→C3 阶段会让 B 档"回退"一位，具体触发条件被观众描述为"AB 两档编号相等时才能进入 C2"——这类"某个 tier 的转移条件依赖于另一个 tier 当前状态"的现象，如果属实，最可能的解释仍然是"三个 tier 共享同一条 `cardsRandomStream`、按 light→medium→heavy 固定顺序连续消费"（见第 2.2 节代码），而不是天气系统真的实现了"跨 tier 状态机"——因为三次抽签用的是同一条序列上紧邻的三个值，任何"看似跨 tier 关联"的表现，都可能只是"同一个序列位置同时决定了这三次抽签结果"的自然推论,而不是三个 tier 之间真的存在数据依赖。

这套 A/B/C 编号规律，本质上是社区独立地把第 3 节"确定性序列 + 固定桶大小 + 固定调用顺序 ⇒ 结果可查表"的结论,用他们自己的记号系统重新发现了一遍——这也是为什么 Weather.md 和 SpyRing.md 都强调:这类"看似有状态机、有记忆"的规律,根源都可以追溯到同一份原生随机流基础设施,不需要在游戏逻辑层面假设任何额外的、代码里实际不存在的状态。

## 5. 另见

- [README.md](README.md) — 完整的对局生命周期随机数机制报告（播种时机、重播种触发条件、`cardsRandomStream` 全部已知消费点）。
- [SpyRing.md](SpyRing.md) — 用同一套随机流机制解释"间谍组织"卡的环形分布规律，方法论上和本文第 3 节互为印证。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该原生字段的命名更正与证据来源（IDA + Dumper-7 SDK 交叉验证）。
