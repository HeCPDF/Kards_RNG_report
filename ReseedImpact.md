# 重播种机制如何解释每一个已观察到的现象

已确认的前提（证据见 [README.md](README.md) §2.2–§2.3、[evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)、[evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)、[evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)）：2026-08-14 抓包确认的对局里 `bUseTurnSwitchValidation` 是开启的，`cardsRandomStream` 每次创建/确认动作都会重播种为 `match_id + CurrentActionId * 19390`。喂给这条公式的 `CurrentActionId`，与提交请求 JSON 里的 `action_id` 字段（`Counter3228`，只数己方构造动作、从 1 连续递增）在原生代码里是两个不同的字段（[evidence/two-distinct-action-id-counters.md](evidence/two-distinct-action-id-counters.md)）；`CurrentActionId` 由 `GetNextAction_Impl` 回放双方合并动作日志推进，不区分动作归属方（[evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md)）。本文以下用"本地计数器"统一指代 `CurrentActionId`。

社区的操作计数方法论（两次效果之间双方操作都计入、跨回合生效、按"单位"加权；结束回合仅己方计入）与上述代码行为自洽，完整权重表与来源见 [社区实测记录](社区实测记录.md) §1。

本文按现象逐条给出解释：§1 是社区"单位"与原始计数器增量的换算，§2 是各档天气"看起来变不变"的原因，§3 是漏洞的完整因果链，§4 是可查表规律的来源，§5 是覆盖的对局类型，§6 是外部计算器为什么能算对。

## 1. 社区口径下"1 次预报 = 3 个单位"，与真实抓包数据大致吻合

社区权重表把"预报单位/预报指令"记为 3 单位（来源见 [社区实测记录](社区实测记录.md) §1）。用 [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 记录的真实数据核对：第二局的两次预报之间夹了两个操作——

- 把 **J2F 鸭式**（DUCK，美国 1K 战斗机单位，`Type = ETypeEnum::fighter`）移动到前线。`card_unit_duck_us.cpp` 的 `OnMoveToFrontline` 反编译确认其效果为"+1/+1 并触发一次 `Forecast`"（带 `ability.forecast` 标签），社区口径为"预报单位"，3 单位。
- 打出**第 44 特混舰队**（TASK FORCE 44，澳新军团 2K 指令，`Type = ETypeEnum::order`，带 `ability.forecast`，打出时触发预报并对目标造成 2/3 点伤害），社区口径为"预报指令"，3 单位。

加上第二次预报自身的 3 单位，合计 `3+3+3=9` 个社区单位；真实观测到的原始 `CurrentActionId` 差值是 8 或 11。`8/9≈0.89`、`11/9≈1.2`，粗略落在"每个社区单位对应约 1 个原始 `CurrentActionId` 增量"附近，不是精确吻合。证据文件还指出，目标选择/伤害结算这类子效果可能不产生独立网络提交、但仍推进计数器（[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 副产品发现 4），因此这个差值不能当作"预报的固定间隔成本"；方向和数量级一致，足以支持本节的换算。

## 2. 为什么"连续两次预报、中间不做别的事"时 6K 看起来不变，而 2K/4K 会变

社区周期数据（[社区实测记录](社区实测记录.md) §2.1）：2K、4K 天气都是 **18 个（社区单位）操作一循环**，6K 天气是 **3 个（社区单位）操作一循环**；最简操作数可按循环数整数倍叠加（`+18x` 或 `+3x`）。

这与 [SpyRing.md](SpyRing.md) §2 用已确认 LCG 常数独立推导出的"每步固定后退约 `0.326` 格、主流游程长度 `≈3`"是同一类结构——2K/4K 的 18 单位周期、6K 的 3 单位周期，都是"多少个（加权）单位操作后，展示结果模式重复"的直接量化。据此，"连续两次预报、中间不做别的事，6K 经常看起来不变、2K/4K 会变"有定量解释：6K 循环短（3），日常操作量容易凑成 3 的倍数；2K/4K 循环长（18），同样的操作量通常凑不成 18 的倍数。

社区单位换算成原始 `CurrentActionId` 增量的精确比例系数仍需更多受控数据点才能钉死（§1），但这不影响"结果确定、可预测"这个结论。

## 3. 为什么会存在这个漏洞：确定性重播种 + 玩家可自行控制的本地计数器

三点已确认事实（推导与抓包证据分别在 README.md §1、§2.2、§2.3 和对应证据文件里），合起来构成漏洞的完整因果链：

1. `cardsRandomStream` 是公开算法的确定性 `FRandomStream`（线性同余生成器），种子完全决定输出序列，没有任何硬件熵源或不可预测输入。
2. 玩家提交动作前看到的所有预览结果（天气预报三选一、间谍组织实际抽到哪张卡等），用的种子是 `match_id + 本地计数器 * 19390`——`match_id` 在对局引导数据里就是明文可见的，本地计数器按社区权重（[社区实测记录](社区实测记录.md) §1）随双方任何一方的操作推进（结束回合例外，只有己方计入）。
3. 玩家虽然不能独占这个计数器（对手的操作也会推进它），但可以完全掌握**自己这一侧**能贡献多少：每多做一次任何计入的操作——哪怕是不花费资源、马上撤销的操作，比如激活一次反制立刻取消——这个本地计数器就会按对应权重推进，进而让种子按已知公式前进相应步数。只要能大致预判对手在这段时间内会做多少操作，或者干脆在对手行动间隙、自己回合内操作，就能把计数器精确推到目标值。

顺带澄清一个计数口径问题：社区不同测试者对"取消反制算不算一次操作"有不同约定（[社区实测记录](社区实测记录.md) §3.2 里两支视频的口径就不一致）。反编译给出的事实是，"挂反制"和"取消反制"是完全相同的提交动作类型，都会各自推进一次本地计数器（[SpyRing.md](SpyRing.md) §4.6）。

**这就是漏洞的本质**：预览结果不是"随机"给玩家看的，而是"玩家已经累计做过多少次（加权）操作"这个可掌握的输入，经过一个公开、确定性的公式算出来的。只要把"本地计数器取值 → 展示结果"这张映射表实测出来（社区已有此类工具，如 NZ33 计算器，见 [社区实测记录](社区实测记录.md) §2），就能反过来推导：当前计数器状态对应哪个结果、想要的结果需要计数器走到哪一步、还需要补做多少次不花费用的空操作。这正是社区描述的"挂反制→取消反制，不耗费用地控制天气"打法的完整原理，也是官方公告里承认的那个游戏机制问题的根源。

## 4. "跨越多次操作的可查表规律"（Weather.md 的代价表、SpyRing.md 的环形游走）

驱动预报/间谍组织这类"提交前就能看到结果"的效果的，是本地计数器 `CurrentActionId`。这个计数器**不是只数己方动作**：反编译 `GetNextAction_Impl` 确认它由"回放合并动作日志、不区分归属方"的 `ActionsReceived` 消化循环推进；社区测试方法论同样明确"双方操作都计入"（[社区实测记录](社区实测记录.md) §1），两条独立证据链指向同一结论。

所以社区计算天气/间谍组织规律时，数的是"从某个已知基准点起，双方一共做了多少（加权后的）操作"，不是"我自己做了多少操作"。社区规律里"以操作次数分段、超过阈值后行为整体切换"的现象（如"指令数大于 3 时 A/B 两档编号同时升一，持续到第 4 次预报"，见 [社区实测记录](社区实测记录.md) §2.1），本质上就是在描述这个（双方合计、加权后的）本地计数器的某种函数。

## 5. 对局类型覆盖范围

`bUseTurnSwitchValidation` 不是编译进客户端二进制的常量，而是服务端下发的值。2026-08-14 的抓包里，`training`（人机单机局）和 PvP 天梯均确认为 `true`，重播种机制在这两类对局下都是启用状态。

[RandomnessHotfixMechanism.md](RandomnessHotfixMechanism.md) §2 进一步确认：这个值的真正来源是登录 `/session` 接口，按账号会话下发，不按对局类型单独配置——因此不会出现"某个赛制启用、另一个赛制不启用"的情况，锦标赛等其他赛制大概率跟 `training`/PvP 天梯一致，只是没有直接抓包核实过。

## 6. 外部工具（如社区的天气/间谍组织计算器）为什么能算对

§3 已经给出漏洞的因果链：预览结果 = 公开确定性公式 `match_id + CurrentActionId × 19390` 喂给 `FRandomStream` 算出来的。本节只说这条链路里跟"外部计算器怎么工作"直接相关的部分。

以 [社区实测记录](社区实测记录.md) §2.1 的 NZ33 天气计算器为例，它的输入输出是"当前展示结果 + 目标展示结果 → 需要多少次行动"，不是正向算"给定操作数会得到什么结果"。这个反向查询能成立，是因为 Weather.md/SpyRing.md 从已确认 LCG 常数推出的离散步长表，本质上描述的是一张图：间谍组织的 5 个国家、天气每档内 3 个小组各 3 个效果，都构成一个环（`环[i] = (起点 + k×i) mod 环长`），每次计入的操作沿环走一个固定量。两个具体结果就是环上的两个节点，节点间的最短路径（走几步、哪个方向）只取决于环的结构，跟这两个结果各自对应的 `CurrentActionId` 绝对值无关——所以只输入两个展示结果就能反查出行动次数，不需要额外知道对局进行到第几步。

链路里另外两点背景也值得一并记下：种子公式（`FRandomStream` + `match_id` + `19390`）不含任何服务端私钥，`match_id` 在对局引导数据里就是明文；`CurrentActionId` 由 `GetNextAction_Impl` 回放双方合并动作日志推进，只在处理一次 `/actions` 轮询回包时更新，而轮询要么每 5 秒一次，要么被服务端 websocket 广播的 `matchaction` 通知立即触发（见 [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md)）。

## 7. 另见

- [README.md](README.md) — 完整机制交叉验证。
- [Weather.md](Weather.md) — 天气系统源码实现与档位结构。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律与已确认的完整周期。
- [OtherRandomCardEffects.md](OtherRandomCardEffects.md) — 护航攻击、反潜巡逻、死神降临、加压舱等结构相同/相近的卡。
- [社区实测记录](社区实测记录.md) — 社区操作计数方法论与社区实测数据（非主证据）。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该开关的证据来源。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — 服务端权威动作编号的真实取值规律。
- [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md) — 本地提交计数器与服务端确认编号的真实差异。
- [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md) — `CurrentActionId` 的完整写入路径与轮询/websocket 触发节奏。
- [evidence/ida-excerpts/](evidence/ida-excerpts/) — 上述结论依据的原始反编译代码摘录（未加工）。
