# 2026-08-25 服务端调整的技术原理：撤回 `validate_turn_switches` 字段

## 1. 调整的背景与结果

官方于 2026-08-23 就"秋季锦标赛选手利用特定操作控制预报机制结果"发布说明，确认这一现象属实，定性为游戏机制层面的问题而非外挂/作弊；2026-08-25 发布[后续说明](https://www.kards.com/news/forecast-issue-and-fall-2026-tournament-results)，确认已对系统做出调整使其更难被操纵，且调整不需要更新客户端：

> We have identified an issue with the Forecast mechanic that makes it possible to manipulate which weather cards are offered as choices. The cause is an unintended interaction between the Forecast code and some older game code...

调整生效后实测确认：社区凭对局内观察归纳出的天气预报操作规律（NZ33 代价表等，见 [Weather.md](Weather.md) §5.1）和间谍组织的环形游走规律（[SpyRing.md](SpyRing.md) §4.1）都已经无法再稳定复现。本文记录调整具体改了什么、为什么完全不需要碰客户端一个字节就能做到，以及这次调整对报告先前分析的印证与局限。

## 2. 核心发现：`validate_turn_switches` 字段被撤回

[evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) 用 2026-08-14 的真实抓包确认过，这个字段（对应原生 `AMatchControllerV2::bUseTurnSwitchValidation`，`+0x7A8`）当时以两种独立形式出现，值均为开启：

1. 登录时拉取的全局功能开关列表（跟大量其它 `feature_*`/`enable_*` 开关并列）：`"validate_turn_switches": 1`
2. 单局对局的引导数据（`match_and_starting_data`）末尾原样回显：`"validate_turn_switches":true`

调整生效后重新核对同样两处：

- 全局功能开关列表——裁剪后的新旧两份真实抓包见 [evidence/kards-live-session-api-response-2026-08-14.json](evidence/kards-live-session-api-response-2026-08-14.json)（旧）和 [evidence/kards-live-session-api-response-2026-08-26.json](evidence/kards-live-session-api-response-2026-08-26.json)（新；mitmproxy 和 Fiddler 两种工具分别抓到的内容逐字节一致）。新旧两份逐键比对，149 个键里唯一的差异就是 `validate_turn_switches` 被移除，其余全部一致。
- 单局对局的引导数据：客户端调用对局接口时已不再发送这个字段。

这个字段在对局接口那一侧本来就是客户端自己从登录 session 里读出来、原样带进每局创建请求的，不是对局接口单独下发的。既然它是登录会话级别的一个值，不会按对局类型单独配置，调整对 `training`、PvP 天梯等所有模式一视同仁，不会出现"这个账号的 PvP 局受影响、单机局不受影响"的情况。

## 3. 为什么撤回一个字段就够了

`bUseTurnSwitchValidation` 在蓝图侧只被读取、从未被赋值，native 反汇编里也找不到任何硬编码的赋值指令（`xrefs_to_field` 零命中，见 [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md)）。它的值来自服务端下发的 JSON 按字段名反射写入这个原生属性，不是客户端代码写死的常量。

`SetRandomStreamWithActionID`（[README.md](README.md) §2.2）：

```cpp
private void SetRandomStreamWithActionID(int inputActionID) {
    if (!GetMatchController->bUseTurnSwitchValidation)
        return;
    int seed = Match.match_id + inputActionID * 19390;
    cardFunctions->SetRandomStreamByMatchID(seed);
}
```

服务端不再发这个字段，反射赋值就没有源数据可写，这个 `bool` 停在 UE 反射系统的默认值上。如果默认值是 `false`（未显式初始化的 `bool` UPROPERTY 的常见默认），`SetRandomStreamWithActionID` 每次调用都会在第一行直接 `return`——重播种分支不再执行，`cardsRandomStream` 不再按 `match_id + CurrentActionId*19390` 逐动作重置，而是从对局开始那一次播种起连续自由推进，天气预报、间谍组织等依赖它的卡牌随机效果共用同一条不断往前走的序列。

这个改动不需要新增代码路径，也不需要改写任何一条现有指令——只是服务端少发一个字段，客户端原有的条件分支自己走向"跳过重播种"，跟官方说明的"不需要更新客户端"吻合。

## 4. 调整生效后的实测数据

在调整生效后的真实对局里做过三次独立盲测：先只根据 `match_id` 和当时确认的 `CurrentActionId`，用原公式算出预测结果，再去看游戏实际展示的候选。

| 次数 | 天气类型 | `CurrentActionId` 来源 | 预测 | 实际 | 命中档位数 |
|---|---|---|---|---|---|
| 1 | 雨 | 服务端轮询确认（136） | light=3、medium=1、heavy=3 | light=1、medium=1、heavy=1 | 1/3（medium） |
| 2 | 雨 | 服务端轮询确认（8） | light=1、medium=1、heavy=2 | light=1、medium=3、heavy=3 | 1/3（light） |
| 3 | 晴 | 内存监控工具直接读取（77） | light=1、medium=1、heavy=2 | light=3、medium=3、heavy=3 | 0/3 |

（第 3 次的 `CurrentActionId` 由 [tools/ActionMonitor.cpp](tools/ActionMonitor.cpp) 直接读内存得到，采集方式见 [evidence/ActionMonitor-real-match-log.md](evidence/ActionMonitor-real-match-log.md)。）

9 个档位预测里对了 2 个，命中率约 22%——低于三选一的纯随机基线（33%），这条公式在调整后已经没有预测力。

同一局里紧接着又在完全相同的输入（`match_id`、`CurrentActionId=77`、晴）下连续触发了 5 次预报，观察结果如何随时间变化：

| 触发次数 | light | medium | heavy |
|---|---|---|---|
| 1 | 3 | 3 | 3 |
| 2（立即重复） | 3 | 3 | 3 |
| 3 | 3 | 2 | 3 |
| 4 | 3 | 1 | 3 |
| 5 | 1 | 1 | 3 |

第 1、2 次结果完全一致，之后开始逐步偏移，且 light、medium、heavy 偏移的时间点不同，heavy 全程未变。这跟"重播种已经停止、`cardsRandomStream` 变成连续推进"的模型定性吻合：如果两次触发之间没有任何其它随机效果消费掉这条流，结果自然不变；一旦有其它消费点被触发过，流就往前走了，越靠后的档位（heavy 排在第三个）需要的推进量越大，"变得晚"也就合理。

这只是方向吻合，不足以精确证明该模型。要验证到能精确复现具体结果的程度，还需要两件东西：(1) 独立确认这个 `bool` 属性的反射默认值确实是 `false`，目前只是援引 UE 的常见约定；(2) 完整重建"两次触发之间 `cardsRandomStream` 实际被调用过多少次"这条计数，这需要把 [README.md](README.md) §4 列出的全部消费点都在真实对局里逐一计数，目前没有这样一份记录。

方法论上还有一个漏洞没堵：`CurrentActionId` 在整个回合内确认不变、只在回合结束时更新，这有可能是跟本次调整无关的固有行为——也就是说，调整前（重播种仍然开启）也可能同样是"回合内不更新"。若是如此，上面第二张表"同一回合内反复触发、结果逐步偏移"这个现象本身，就不能排除是重播种机制原本就有的正常表现，而非"重播种被关闭"的证据。要排除这个可能，需要一份调整前的旧版本、同一回合内多次触发预报的真实数据做对照组。

## 5. 历史猜测：环形游走规律的出现时间

[SpyRing.md](SpyRing.md) §4.1 记录的"环形相邻游走"规律（新结果相对上一次只会原地或左右相邻，不会跳到不相邻的国家）是重播种机制存在时才会出现的产物——如果 `cardsRandomStream` 从对局开始起只连续推进、从不按 `CurrentActionId` 重播种，间谍组织每次抽签只会落在这条连续序列的下一段，不会表现出"结果跟本地操作计数强相关"这种规律性。

一个合理猜测：这整套可操纵的环形规律，很可能是随"澳新军团"（ANZAC）版本引入 `validate_turn_switches` 这个开关及配套的重播种机制之后才出现的。上一个版本"国土阵线"（Homefront）里，至少在对局发起这一步，客户端根本不会把这个字段发给服务端——这一点从当前版本客户端仍然保留的请求逻辑就能直接核实。如果 Homefront 版本从未启用过这个开关，那么这次调整某种意义上不是"新增了一处过去没有的补丁"，而是把行为改回了 ANZAC 引入这个机制之前的状态。

这是猜测，不是结论：需要 Homefront 版本对局引导数据的真实抓包，确认该版本的响应体里是否完全没有这个字段。

## 6. 这次调整对先前分析的印证与局限

先说局限：这次调整不解释 [SpyRing.md](SpyRing.md) §4.3/§4.4 记录的那条矛盾——"连续 17 次挂/取消反制、连续抽出 8 张完全相同的间谍组织研发卡"这条社区经验数据，用已确认的引擎常数精确计算后，找不到任何 `match_id` 能重现"6 次以上连续相同"。那条矛盾至今仍是悬案。

印证有两层。第一层是本报告基于反编译推导出的重播种机制，确实解释了社区归纳出的一部分规律——天气系统 NZ33 代价表的"同组代价"一项（Weather.md §5.1）、间谍组织环形游走的具体步长（SpyRing.md §4.1、§4.2）。这些吻合是先用引擎公开常数算出预测、再去对照社区数据得到的。

第二层是这次调整本身：官方承认存在可操纵漏洞并作出调整，而调整的具体内容——撤回 `validate_turn_switches`，让重播种分支不再触发——精确对应本报告独立反编译出的那一个具体代码分支，不是笼统地"调整了随机数系统"。如果 `SetRandomStreamWithActionID` 的实现、这个开关的作用不是本报告描述的这样，"停止发送这一个字段"就不会是一个能生效的修复手段。

## 7. 仍待确认的开放问题

1. `bUseTurnSwitchValidation` 的反射默认值是否确实是 `false`：目前只是从"字段消失 + 重播种行为消失"反推的合理解释，没有从二进制或 UE 反射元数据里直接确认过。
2. 连续推进模型的精确验证：需要一份从对局开始逐一计数 `cardsRandomStream` 全部消费点调用次数的真实记录，代入 §4 重新计算，看能否精确复现观察到的偏移，而不只是方向吻合。
3. 调整是否分批/按账号灰度下发：直接确认过字段缺失的只有两场 `training` 局；该字段按登录会话下发、不分赛制（§2），但调整本身是否对所有账号同时生效没有直接核实。
4. §5 的历史猜测是否成立：需要 Homefront 版本对局引导数据的真实抓包。
5. `CurrentActionId` 回合内不变是否本来就是固有行为：见 §4 末尾，需要调整前的旧版本对照数据。

## 8. 另见

- [README.md](README.md) §2.2、§6 — 重播种公式的完整推导与开放问题列表。
- [evidence/bUseTurnSwitchValidation.md](evidence/bUseTurnSwitchValidation.md) — 该字段的完整证据链（旧值确认为开启）。
- [evidence/kards-live-session-api-response-2026-08-14.json](evidence/kards-live-session-api-response-2026-08-14.json) — 调整前的全局功能开关列表抓包结果。
- [evidence/kards-live-session-api-response-2026-08-26.json](evidence/kards-live-session-api-response-2026-08-26.json) — 调整生效后的全局功能开关列表抓包结果。
- [Weather.md](Weather.md) §3 — 天气系统的官方说明与调整后状态。
- [SpyRing.md](SpyRing.md) §4.1 — 环形游走规律及其与本次调整的关系。
