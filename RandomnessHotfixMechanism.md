# 2026-08-25 服务端调整的技术原理：撤回 `validate_turn_switches` 字段

## 1. 现状：社区已知的操纵手法已失效

官方已于 2026-08-23 就"秋季锦标赛选手利用特定操作控制预报机制结果"发布说明，确认这一现象属实，将其定性为游戏机制层面的问题而非外挂/作弊；2026-08-25 官方发布[后续说明](https://www.kards.com/news/forecast-issue-and-fall-2026-tournament-results)，确认已对系统做出调整使其更难被操纵，调整不需要更新客户端。实测确认：调整生效后，社区凭对局内观察归纳出的天气预报操作规律（NZ33 代价表等，见 [Weather.md](Weather.md) §5）已经无法再稳定复现；间谍组织的环形游走规律同样测不出来（[SpyRing.md](SpyRing.md) §6）。

本文档记录调整具体改了什么、为什么不需要碰客户端一个字节就能做到。

## 2. 核心发现：`validate_turn_switches` 字段从两个独立来源里都消失了

[`evidence/bUseTurnSwitchValidation.md`](evidence/bUseTurnSwitchValidation.md) 用 2026-08-14 的真实抓包确认过，这个字段（对应原生 `AMatchControllerV2::bUseTurnSwitchValidation`，`+0x7A8`）在当时以两种独立形式出现，值均为开启：

1. **应用启动时拉取的全局功能开关列表**（跟大量其它 `feature_*`/`enable_*` 开关并列）：`"validate_turn_switches": 1`
2. **单局对局的引导数据**（`match_and_starting_data`）末尾原样回显：`"validate_turn_switches":true`

调整生效后的今天，用同样的两个来源重新核对：

- 全局功能开关列表：[`evidence/kards-live-session-api-response.json`](evidence/kards-live-session-api-response.json)（`/session` 接口的真实响应，`server_options` 字段是一段二次 JSON 编码的字符串，解码后共 149 个键）里能找到跟原证据文档同一批相邻字段——`feature_socketerror_popup_enabled`、`feature_collection_cardhelpcache`、`monitor_battle` 都还在——**但 `validate_turn_switches` 这个键完全不存在了**，不是被设成 `0`，是这个键本身没有了。
- 单局对局的引导数据：两场刚开始的新对局（`match_id=1216112469`、`1216115254`，均为 `training`/人机对局）的完整 `match_and_starting_data` 响应体，顶层只有这一个键，末尾没有任何 `validate_turn_switches` 字段——跟原证据文档"末尾原样回显"的格式对比，这个字段整个从响应体里被拿掉了。
- 独立交叉验证：用另一个抓包工具（Fiddler，跟原证据文档 2026-08-14 抓包用的是同一款工具）、在实际使用中的账号上单独抓了一份 `/session` 响应（[`evidence/kards-live-session-api-response-fiddler-2026-08-26.json`](evidence/kards-live-session-api-response-fiddler-2026-08-26.json)），跟旧版本逐键比对全部 149 个键——**唯一的差异就是 `validate_turn_switches` 被移除，其余 148 个键一个不多一个不少**。这排除了"只是这次抓包工具/账号凑巧漏看了这个字段"的可能，也排除了"整个功能开关列表被大范围重构、我们只是碰巧注意到这一处"的可能——改动精确地只涉及这一个字段。

三个独立来源（两种抓包工具、两个不同账号、两类接口）同时、完全地失去同一个字段，不太可能是巧合或者字段改名——最直接的解释就是服务端不再下发这个字段。

## 3. 为什么"不发这个字段"就足够构成修复

[`evidence/bUseTurnSwitchValidation.md`](evidence/bUseTurnSwitchValidation.md) 已经证明：这个字段在蓝图侧只被读取、从未被赋值；在 native 反汇编里也找不到任何硬编码的赋值指令（`xrefs_to_field` 查询零命中）。结论是它的值来自**反射式的服务端下发/默认值路径**——服务端把 JSON 字段按名字反射写入这个原生属性，不是客户端代码写死的常量。

`SetRandomStreamWithActionID`（[README.md](README.md) §2.2）的实现是：

```cpp
private void SetRandomStreamWithActionID(int inputActionID) {
    if (!GetMatchController->bUseTurnSwitchValidation)
        return;
    int seed = Match.match_id + inputActionID * 19390;
    cardFunctions->SetRandomStreamByMatchID(seed);
}
```

如果服务端不再发这个字段，反射赋值路径就没有源数据可写，这个 `bool` 属性就停在 UE 反射系统的默认值上。只要这个默认值是 `false`（未显式初始化的 `bool` UPROPERTY 常见默认），`SetRandomStreamWithActionID` 就会在每次调用时直接在第一行 `return`——重播种分支从此再也不会执行，`cardsRandomStream` 不再按 `match_id + CurrentActionId*19390` 在每个动作后重置，而是变成从对局开始那一次播种起连续自由推进，被 [README.md](README.md) §5 列出的所有已知消费点（天气预报、间谍组织、护航攻击、洗牌……）共享同一条不断前进的序列，不再是一个每次都能从已知输入精确复现的确定性快照。

这个改动**完全不需要更新客户端**：没有新增代码路径，没有改写任何一条现有指令，只是服务端少发了一个 JSON 字段，客户端原有的、早就写好的条件分支自己就会走向"跳过重播种"这条路。这与官方说明"已经做出调整使其更难被操纵、不需要更新客户端"的表述完全吻合，也与"客户端本地文件未被修改过"这一前提没有任何冲突——改动完全发生在服务端下发的数据里，不在二进制里。

## 4. 与实测数据的吻合程度

在这一机制假设下，同一回合内反复触发预报（`CurrentActionId` 确认冻结不变，见 [evidence/CurrentActionId-increment-logic.md](evidence/CurrentActionId-increment-logic.md)）不应该每次都得到完全相同的结果——因为驱动结果的不再是"重播种到某个固定种子"，而是"`cardsRandomStream` 已经被消费到哪一步"，后者会随着对局中任何其它消费点（不只是预报本身）被触发而持续往前走。真实测试观察到的现象与此吻合：

- 连续两次触发（中间没有其它已知消费点被触发）得到完全相同的三档结果——如果 `cardsRandomStream` 在这段时间内确实没有被消费，连续推进的模型和"重播种到同一种子"的模型在这一个特例上预测一致，不能单独区分两者。
- 后续触发里，档位结果开始逐步偏移，且不同档位偏移的时机不同——如果是连续推进模型，这正是预期的：所有档位共享同一条连续序列，只是各自处在序列里的哪个瞬时切片不同，偏移量本身取决于两次触发之间实际发生了多少次消费，而不是一个能提前预知的固定值。
- 用原来"重播种到 `match_id + CurrentActionId*19390`"公式做的多次盲测预测，命中率落在纯随机猜测的期望值附近（3 选 1 的档位，多次预测平均命中率约 22%，见下文）——如果重播种真的完全停止了，这正是预期结果：这条公式本来就不应该再对结果有任何预测力。

**目前更多是定性吻合，还没有精确到数值级别的证明**：要把"连续推进模型"验证到能精确预测具体结果的程度，需要独立确认 UE 里未显式初始化的 `bool` UPROPERTY 默认值确实是 `false`（本文档目前只是援引这是常见约定，没有对这个二进制单独反编译验证），以及完整重建"对局开始到某次预报触发之间，`cardsRandomStream` 一共被调用过多少次"这条计数——后者需要把 README §5 列出的全部消费点都在真实对局里逐一计数，目前没有这样一份完整记录。

## 5. 历史线索：间谍组织的环形游走规律，可能正是这个字段被引入之后才出现的

[SpyRing.md](SpyRing.md) §4.1 记录的"环形相邻游走"规律（新结果相对上一次只会是原地或左右相邻，不会跳到不相邻的国家）本质上是重播种机制存在时才会出现的产物——如果 `cardsRandomStream` 从对局开始起只连续推进、从不按 `CurrentActionId` 重播种，间谍组织每次抽签只会落在这条连续序列的下一段，不会表现出"结果跟本地操作计数强相关、可以靠数操作次数去精确控制落点"这种规律性。

一个合理猜测：这整套可操纵的环形规律，很可能是随"澳新军团"（ANZAC）版本引入 `validate_turn_switches` 这个开关及配套的重播种机制之后才出现的。上一个版本"国土阵线"（Homefront）里，至少在对局发起（创建对局请求）这一步，客户端根本不会把 `validate_turn_switches` 这个字段发给服务端——这一点不需要等 Homefront 版本的旧抓包，从现在版本客户端仍然保留的请求逻辑就能直接核实是否存在这个字段。如果 Homefront 版本从未启用过这个开关，那么 2026-08-25 的这次调整某种意义上不是"新增了一处过去没有的补丁"，而是**把行为改回了 ANZAC 引入这个机制之前、Homefront 版本原本就有的状态**——这与"不需要更新客户端"完全吻合：停止发送一个本来就是后来才加进去的字段，就足以让代码路径退回到它被引入之前就已经存在、只是从未被触发过的分支。

这是一个**合理猜测，不是已确认结论**——需要 Homefront 版本对局引导数据的真实抓包才能验证"该版本的响应体里完全没有这个字段"（而不只是请求体里没发），本文档目前没有这样的抓包，留作后续验证的具体方向。

## 6. 这次调整对本报告先前分析的印证与局限

本报告没能从反编译/反汇编的角度解释 [SpyRing.md](SpyRing.md) §4.3/§4.4 记录的具体矛盾——"连续 17 次挂/取消反制、连续抽出 8 张完全相同的间谍组织研发卡"这一条社区经验数据，用已确认的引擎常数精确计算后，在整数精度上找不到任何一个 `match_id` 能重现"6 次以上连续相同"，这个具体矛盾本报告至今没有给出解释，§5 的调整也不会改变这一点。

但本报告基于反编译/反汇编推导出的重播种机制，确实能解释社区归纳出的另一部分规律——天气系统 NZ33 代价表"同组代价"一项（Weather.md §5.1）、间谍组织环形相邻游走的具体步长（SpyRing.md §4.1、§4.2）——这些吻合不是拿着社区结论去反向凑出来的，是先只用引擎公开常数算出预测，再拿去对照社区数据，方向上是"先推导、后核对"。

更进一步：官方在 2026-08-25 承认存在可操纵漏洞并作出调整，调整的具体内容——撤回 `validate_turn_switches` 字段，让重播种分支不再触发——精确对应本报告 §2.2 反编译出的那一个具体代码分支，不是官方笼统地"调整了随机数系统"，而是恰好命中本报告独立反编译确认的那一个开关。这从侧面印证了本报告基于静态反编译得出的分析路径本身是准确的：如果 `SetRandomStreamWithActionID` 的实现、`bUseTurnSwitchValidation` 这个开关的作用不是本报告描述的这样，"停止发送这一个字段"就不会是一个真正能生效的修复手段。

## 7. 仍待确认的开放问题

1. **`bUseTurnSwitchValidation` 的反射默认值是否确实是 `false`**：目前只是从"字段消失+重播种行为消失"反推的合理解释，没有从二进制或 UE 反射元数据里直接确认过这个具体默认值。
2. **连续推进模型的精确验证**：需要一份从对局开始逐一计数 `cardsRandomStream` 全部消费点调用次数的真实记录，代入 §3 的连续推进假设重新计算，看能否精确复现观察到的档位偏移，而不只是方向上吻合。
3. **调整的触发条件**：目前只确认了两场 `training` 局的字段缺失，PvP 天梯、锦标赛等其它赛制是否同样缺失，或者调整本身是否分批/按账号灰度下发，尚未覆盖。
4. **§5 的历史猜测是否成立**：需要 Homefront 版本对局引导数据的真实抓包，确认该版本响应体里是否完全没有 `validate_turn_switches` 字段。

## 8. 另见

- [README.md](README.md) §2.2、§7 — 重播种公式的完整推导与开放问题列表。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该字段的完整证据链（旧值确认为开启）。
- [evidence/kards-live-session-api-response-2026-08-14.json](evidence/kards-live-session-api-response-2026-08-14.json) — 调整前的全局功能开关列表真实抓包，用于跟调整后的版本对照。
- [evidence/kards-live-session-api-response.json](evidence/kards-live-session-api-response.json) — 调整生效后的全局功能开关列表真实抓包。
- [evidence/kards-live-session-api-response-fiddler-2026-08-26.json](evidence/kards-live-session-api-response-fiddler-2026-08-26.json) — 独立用 Fiddler 在实际使用账号上抓的第二份调整后抓包，逐键比对确认唯一差异就是这个字段。
- [Weather.md](Weather.md) §3 — 天气系统的官方说明与调整后状态。
- [SpyRing.md](SpyRing.md) §4.1、§6 — 环形游走规律与调整后状态。
