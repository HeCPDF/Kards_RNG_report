# 重播种机制如何解释每一个已观察到的现象

真实抓包已经确认（[README.md](README.md) §2.2-2.3、[evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)、[evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md)、[evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md)）：`bUseTurnSwitchValidation` 在真实对局里是开启的，`cardsRandomStream` 每次创建/确认动作都会重播种为 `match_id + CurrentActionId * 19390`。反编译进一步确认：真正喂给重播种公式的 `CurrentActionId` 字段，与提交请求 JSON 里的 `action_id` 字段（`Counter3228`，只数己方构造动作、从 1 连续递增）是原生代码里两个不同的字段——完整区分见 [evidence/two-distinct-action-id-counters.md](evidence/two-distinct-action-id-counters.md)。`CurrentActionId` 由 `GetNextAction_Impl` 回放双方合并动作日志推进，不区分动作归属方（见 [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md)）。本文以下用"本地计数器"统一指代喂给重播种公式的 `CurrentActionId`。

社区操作计数方法论（两次效果之间双方操作都计入、跨回合生效、按"单位"加权；结束回合仅己方计入）与上述代码行为自洽，完整权重表与来源见 [CommunityObservations.md](CommunityObservations.md) §1。早期版本"本地计数器只数我方自己动作、不受对手影响"的表述是错误的，已按 `ActionsReceived` 驱动的合并日志回放结论更正。

## 1. 社区口径下"1 次预报 = 3 个单位"，与真实抓包数据大致吻合

社区权重表中"预报单位/预报指令"本身是 3 单位操作（来源见 [CommunityObservations.md](CommunityObservations.md) §1）。用 [evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 记录的真实数据核对：第二局两次预报之间夹了把 **J2F 鸭式**（DUCK，美国 1K 战斗机单位，`Type = ETypeEnum::fighter`）移动到前线的操作——`card_unit_duck_us.cpp` 的 `OnMoveToFrontline` 反编译确认其效果为"+1/+1 并触发一次 `Forecast`"（带 `ability.forecast` 标签），社区口径为"预报单位"，3 单位；以及打出**第 44 特混舰队**（TASK FORCE 44，澳新军团 2K 指令，`Type = ETypeEnum::order`，`ability.forecast`，打出时触发预报并对目标造成 2/3 点伤害），社区口径为"预报指令"，3 单位。加上第二次预报自身的 3 单位，合计 `3+3+3=9` 个社区单位；真实观测到的原始 `CurrentActionId` 差值是 8 或 11。`8/9≈0.89`、`11/9≈1.2`，粗略落在"每个社区单位对应约 1 个原始 `CurrentActionId` 增量"附近，不是精确吻合——证据文件还指出目标选择/伤害结算这类子效果可能不产生独立网络提交、但仍推进计数器（[evidence/live-match-forecast-validation.md](evidence/live-match-forecast-validation.md) 副产品发现 4），因此该差值不能当作"预报固定间隔成本"，方向和数量级一致即已支持本节的换算。

## 2. 为什么"连续两次预报、中间不做别的事"时 6K 看起来不变，而 2K/4K 会变

社区周期数据（[CommunityObservations.md](CommunityObservations.md) §2.1）：2K、4K 天气都是 **18 个（社区单位）操作一循环**，6K 天气是 **3 个（社区单位）操作一循环**；最简操作数可按循环数整数倍叠加（`+18x` 或 `+3x`）。这与 [SpyRing.md](SpyRing.md) §3 用已确认 LCG 常数独立推导出的"每步固定后退约 `0.326` 格、主流游程长度 `≈3`"是同一类结构——2K/4K 的 18 单位周期、6K 的 3 单位周期，都是"多少个（加权）单位操作后，展示结果模式重复"的直接量化。据此，"连续两次预报、中间不做别的事，6K 经常看起来不变、2K/4K 会变"可以定量解释：6K 循环短（3），日常操作量容易凑成 3 的倍数；2K/4K 循环长（18），同样的操作量通常凑不成 18 的倍数。社区单位换算成原始 `CurrentActionId` 增量的精确比例系数仍需更多受控数据点才能钉死（§1），这不影响"结果确定性可预测"的结论。

## 3. 为什么会存在这个漏洞：确定性重播种 + 玩家可自行控制的本地计数器

三点已确认事实（分别在 README.md §1/§2.2/§2.3 和对应证据文件里有完整推导/抓包证据），合在一起构成了漏洞的完整因果链：

1. `cardsRandomStream` 是公开算法的确定性 `FRandomStream`（线性同余生成器），种子完全决定输出序列，没有任何硬件熵源或不可预测输入。
2. 玩家提交动作前看到的所有预览结果（天气预报三选一、间谍组织实际抽到哪张卡等），用的种子是 `match_id + 本地计数器 * 19390`——`match_id` 在对局引导数据里就是明文可见的，本地计数器按社区权重（[CommunityObservations.md](CommunityObservations.md) §1）随双方任何一方的操作推进（结束回合例外，只有己方计入）。
3. 玩家虽然不能独占这个计数器（对手的操作也会推进它），但可以完全掌握**自己这一侧**能贡献多少：每多做一次任何计入的操作（哪怕是不花费资源、马上撤销的操作，比如激活一次反制立刻取消——社区确认激活反制计一次操作、取消反制本身不计，见 [CommunityObservations.md](CommunityObservations.md) §1），这个本地计数器就会按对应权重推进，进而让种子按已知公式前进相应步数；只要能大致预判对手在这段时间内会做多少操作（或者干脆在对手行动间隙、自己回合内操作），仍然可以把计数器精确推到目标值。

**这就是漏洞的本质**：预览结果不是"随机"给玩家看的，而是"玩家已经累计做过多少次（加权）操作"这个可以掌握的输入，经过一个公开、确定性的公式算出来的。只要把"本地计数器取值 → 展示结果"这张映射表实测出来（社区已有此类工具，如 NZ33 计算器，见 [CommunityObservations.md](CommunityObservations.md) §2），就能反过来推导："我现在的计数器状态对应哪个结果，想要的结果需要计数器走到哪一步，那我只需要再做相应次数不花费用的空操作（比如反复激活/取消一次不实际使用的反制），就能把预览结果精确调整成我想要的"——这正是社区描述的"挂反制→取消反制，不耗费用地控制天气"打法的完整原理，也是官方公告里承认"存在可以被特定操作序列控制"的这个游戏机制问题的根源。

## 4. "跨越多次操作的可查表规律"（Weather.md 的代价表、SpyRing.md 的环形游走）

驱动预报/间谍组织等预提交阶段就能看到结果的效果的，是本地计数器（`CurrentActionId`）。上文引言已经更正：这个计数器**不是只数己方动作**——反编译 `GetNextAction_Impl` 确认它由"回放合并动作日志、不区分归属方"的 `ActionsReceived` 消化循环推进；社区测试方法论同样明确"双方操作都计入"（[CommunityObservations.md](CommunityObservations.md) §1），两条独立证据链指向同一结论。所以社区计算天气/间谍组织规律时，数的是"从某个已知基准点起，双方一共做了多少（加权后的）操作"，不是"我自己做了多少操作"——早期版本"KARDS 是回合制、对方不会插入新动作，所以只数自己回合内的操作也对得上"这个论证虽然在"只看自己单个回合内"这个特殊场景下不会出错，但作为通用解释是不必要的：真正的机制本来就是双方都计入，不需要局限于"自己回合内"这个前提。社区规律中"以操作次数分段、超过阈值后行为整体切换"的现象（如"指令数大于 3 时 A/B 两档编号同时升一，持续到第 4 次预报"，见 [CommunityObservations.md](CommunityObservations.md) §2.1），本质上就是在描述这个（双方合计、加权后的）本地计数器的某种函数。

## 5. 对局类型覆盖范围

`bUseTurnSwitchValidation` 是服务端随每场对局引导数据下发的值（README.md §2.2 已用 `xrefs_to_field` 排除了客户端硬编码赋值的可能），不是编译进客户端二进制的常量。本报告直接掌握的抓包只有 `match_type: "training"`（人机单机局）两份，均确认该值为 `true`；**PvP 天梯对局同样启用这个开关，已由持有账号、能直接在天梯对局中核实的本项目所有者确认**——也就是说，重播种机制在 PvP 天梯对局下同样是启用状态，跟 `training` 对局一致。因此本报告 §1-3 的全部结论覆盖 `training` 和 PvP 天梯两类对局；唯一仍未覆盖、且没有已知渠道核实的是锦标赛（tournament）等其他赛制，是否有独立于天梯的配置仍是未知。

## 6. 另见

- [README.md](README.md) — 完整机制交叉验证。
- [Weather.md](Weather.md) — 天气系统源码实现与档位结构。
- [SpyRing.md](SpyRing.md) — 间谍组织环形规律与已确认的完整周期。
- [CommunityObservations.md](CommunityObservations.md) — 社区操作计数方法论与社区实测数据（非主证据）。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该开关的证据来源。
- [evidence/action_id-real-capture-sequence.md](evidence/action_id-real-capture-sequence.md) — 服务端权威 `action_id` 真实取值规律。
- [evidence/local-vs-confirmed-action-id.md](evidence/local-vs-confirmed-action-id.md) — 本地投机计数器 vs 服务端确认编号，两套编号的真实差异（本文档结论的核心证据来源）。
