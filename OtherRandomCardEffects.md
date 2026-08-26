# 其他经 `cardsRandomStream` 的随机效果卡

> 本文只收录**与天气系统无关、但与间谍组织结构相同/相近**的随机效果卡：护航攻击（CONVOY ATTACK）、反潜巡逻（ASW PATROL）、死神降临（DEATH FROM ABOVE）、加压舱（PRESSURIZED CABIN）。间谍组织本身见 [SpyRing.md](SpyRing.md)；社区实测数据统一收录于 [社区实测记录](社区实测记录.md) §3，不构成本文主证据。

## 1. 护航攻击（CONVOY ATTACK）

意大利[`护航攻击`](https://www.kards.com/images/card/v52/en-EN/convoy_attack.avif)（CONVOY ATTACK，"Deal 0-2 damage to any target."，官方中文文本"对 1 个目标造成 0-2 点伤害"）的实现和间谍组织几乎是同一个模子刻出来的——同样只有一行随机数，直接把结果当数值用，连中间的 switch 映射都省了：

```cpp
cardFunction->RandomIntFromRangeWithStream(0, 2, /*out*/ randomResult);
cardFunction->DamageCard(Event_targetCard, randomResult, cardID, false, false, false, /*out*/ targetDestroyed);
```

这是一次范围 `[0,2]` 的三选一抽签，结果直接作为伤害数值使用。社区用与间谍组织相同的方法实测到该卡存在 18 次操作的循环周期（0/1/2 各出现恰好 6 次），完整转述见 [社区实测记录](社区实测记录.md) §3.3。

用 [SpyRing.md](SpyRing.md) §2 同样的方法对 `RandRange(0,2)`（三等分环，不是间谍组织的五等分）重新推导：`Δ_fraction≈0.9348` 不变（它只跟 `19390`/`196314165` 这两个常数有关，与桶数无关），`3 × Δ_fraction ≈ 2.804`，即每步在三等分环上固定后退约 `0.196` 格，平均游程长度 `≈1/0.196≈5.1`——比间谍组织的 `≈3.07` 更长。这与社区"18 次结果看起来无规律、但 0/1/2 均匀各 6 次"的描述并不矛盾：三等分下平均游程变长，短期内更容易观察到"看起来杂乱"的排列。这一步只是把已确认的同一套公式代入不同的桶数，没有引入新假设。

## 2. 随机目标类卡：反潜巡逻 / 死神降临 / 加压舱

反潜巡逻（[`ASW PATROL`](https://www.kards.com/images/card/v52/en-EN/asw_patrol.avif)，USA，Brothers in Arms 系列，7 kredits，官方中文文本"额外获得 3 个指挥点槽。若美国是盟国，随机消灭 1 个敌方单位"）、死神降临（[`DEATH FROM ABOVE`](https://www.kards.com/images/card/v52/en-EN/death_from_above.avif)，USA，4 kredits，"随机消灭 1 个敌方单位"）、加压舱（[`PRESSURIZED CABIN`](https://www.kards.com/images/card/v52/en-EN/pressurized_cabin.avif)，USA，"将 1 张'B-29 超级堡垒'加入手牌。随机消灭 1 个敌方单位"）均已反编译核实，三者结构完全一致，跟间谍组织/护航攻击有一处区别：它们调用的不是 `RandomIntFromRangeWithStream` 直接指定范围，而是 `BP_CardFunctions::GetRandomCard`（`BP_CardFunctions.cpp:5248`）——先拿到敌方场上全部单位的数组，再用 `RandomIntFromRangeWithStream(0, 数组长度-1)` 在数组下标范围内抽一个。

`ASW PATROL` 的反编译（`card_event_asw_patrol.cpp:31-57`）：己方是美国盟友时，先给己方加 3 个指挥点槽，再对 `GetOppositeSide()` 一方调用 `GetCardsOnBoardBySide(oppositeSide, true, false, ...)` 取得敌方场上全部单位，数组非空时用 `GetRandomCard` 随机消灭其中 1 个——跟 `DEATH FROM ABOVE`/`PRESSURIZED CABIN` 是同一个函数、同一种调用方式，没有任何独有的额外分支。

也就是说这三张卡的"候选数量"是**动态的**（取决于对方场上有几个单位），不像间谍组织/护航攻击那样固定为 5/3。这意味着 [Weather.md](Weather.md) §4.2 / [SpyRing.md](SpyRing.md) §3 那套"固定分桶数换算等效步长"的表不能直接套用；但推导方法（[SpyRing.md](SpyRing.md) §2）仍然适用，只要把分桶数 `N` 换成当时场上的单位数，针对每一局的具体局面单独代入计算即可——不存在跨对局通用的固定分桶数常数。

这些卡的共同点是：效果里都含有"从若干个候选结果中随机选一个"这一步，而它们无一例外都要经过 `cardsRandomStream`。按 [SpyRing.md](SpyRing.md) §2 的解释框架，这些卡出现类似规律是同一套底层机制的又一次体现，而不是各自独立的巧合（社区对这几张卡也报告过类似"可预测/可复现"的反馈，见 [社区实测记录](社区实测记录.md) §3.4）。

## 3. 尚待确认的开放问题

1. **护航攻击的循环内部具体排列**：18 次的循环周期长度已由社区实测确认（[社区实测记录](社区实测记录.md) §3.3），§1 也用同一套公式换算出三等分环下的平均游程（`≈5.1`），但循环内部哪一次操作对应哪个伤害数值仍未逐项核对——需要更细颗粒度的实测（结合真实 `match_id`/`CurrentActionId` 走一遍公式），属于需要新数据而非需要新方法的问题。

## 4. 另见

- [SpyRing.md](SpyRing.md) — 间谍组织：单次重播种单次抽样的推导与模拟。
- [Weather.md](Weather.md) — 天气系统：同一次重播种后连续三次变换的结构对照。
- [社区实测记录](社区实测记录.md) — 社区对护航攻击/随机目标类卡的实测数据。
