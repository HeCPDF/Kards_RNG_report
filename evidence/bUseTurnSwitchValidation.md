# `bUseTurnSwitchValidation`（native, `AMatchControllerV2 + 0x7A8`）

## 字段真实名称的来源：游戏自身的蓝图字节码，不是第三方 SDK

真实字段名 `bUseTurnSwitchValidation` 的来源，是**游戏自己序列化在 `.uasset` 里的蓝图字节码**，通过 FModel 反编译直接读出来的——这是游戏自身的数据，不依赖任何第三方逆向 SDK（此前一版文档误引用了 Dumper-7 生成的 SDK 头文件作为佐证，已经去掉；那份 SDK 本身也是从同一套 UE 反射系统里导出的，参考意义不大，直接看游戏自己的蓝图数据即可）：

蓝图节点在调用一个原生 `UPROPERTY` 时，`.uasset` 里存的是对这个属性的 **`FName` 引用**（属性名本身作为反射元数据的一部分，序列化在蓝图资产里，供蓝图虚拟机在运行时按名字解析），FModel 反编译时会把这个引用还原成源码里的标识符名字。也就是说，`BP_OnlineMatch.cpp`、`BP_Board.cpp` 等反编译文件里出现的 `bUseTurnSwitchValidation` 这个名字，就是蓝图数据本身记录的名字，跟 `AMatchControllerV2` 的 `0x7A8` 偏移，是同一个原生 bool 字段的两种不同来源的观察——一个是"蓝图侧怎么引用它"，一个是"native 内存布局里它在哪"。

## 尝试在 IDA 里直接验证：字符串搜索超时，转而用 GObjects 运行时反射转储确认

按要求，尝试直接在 IDA 反汇编/字符串表里搜索字面量 `"bUseTurnSwitchValidation"`。两次尝试均超时未完成：

- `search_text`（按反汇编逐行渲染扫描）：分别以 `code_only=true` 和 `code_only=false` 跑过，均在 60 秒工具超时内没能扫完 `.text`（`0x140001000`-`0x14703d000`，约 112MB）或跨段范围，被强制中断。
- `find_regex`（走 IDA 预建的字符串表）：同样超时。

这跟这个二进制没有 PDB、且 UE 的 `FName` 很多路径下走全局名字池（而不是每处引用内联一份明文）有关，简单的行扫描/字符串表正则本身就不一定能找到。

也顺带排查了另一条路：这个字段有没有对应的原生 `exec*` thunk（`ClassName::exec<FunctionName>` 是 UHT 为 `BlueprintCallable UFUNCTION` 生成的native 调用入口，是真正能反汇编的机器码，不是蓝图字节码）。列出 `AMatchControllerV2` 全部 `exec*` 函数（共 54 个，比如 `execGetCurrentActionID`、`execResetVariables`、`execGetDetailsForDebugGame`、`execSaveCheckpointForDebugGame` 等）逐一核对，**没有任何一个名字里带 `TurnSwitch`/`Validation`**——这是符合预期的空结果：`bUseTurnSwitchValidation` 是纯 `UPROPERTY`（没有 `UFUNCTION` getter/setter），蓝图节点读取它时编译出的是直接按偏移读属性，走 Blueprint 虚拟机解释执行，根本不会生成 `exec*` thunk，所以这条路线在这个字段上必然找不到东西，不是搜索方法有问题。顺手反编译了两个最可能"顺带"提到这个字段的调试类函数（`GetDetailsForDebugGame_Impl` @ `0x144aef4b0`、`SaveCheckpointForDebugGame_Impl` 的 exec 包装 @ `0x144a94bd0`），确认前者是本地 JSON 存档/HTTP 回退加载器，完全不涉及 `0x7A8`。

真正给出确认的，是**对正在运行的游戏进程用 Dumper-7 做的运行时反射转储**（`GObjects-Dump-WithProperties.txt`）。这份文件不是从 `.exe` 静态反编译出来的，是 Dumper-7 挂进正在跑的游戏进程、直接遍历 `GObjects`/`UClass::PropertyLink` 反射链表导出的——比起在 IDA 里手动重建的、可能带占位名的结构体布局，这是更直接的一手证据。搜索命中（完整上下文已存为 [`GObjects-Dump-excerpt-MatchControllerV2.txt`](GObjects-Dump-excerpt-MatchControllerV2.txt)，收录进本仓库）：

```
[00000B31] {0x7ff4b3aed440} Class kards.MatchControllerV2
...
[000007A8] {0x21bb0e6ac80}     BoolProperty bUseTurnSwitchValidation
[000007A9] {0x21bb0e6ad00}     BoolProperty bUseActionsForMulligan
[000007AA] {0x21bb0e6ad80}     BoolProperty bUseLocalSubActions
[000007AB] {0x21bb0e6ae00}     BoolProperty isResyncingMatch
[000007B0] {0x21bb0e6ae80}     StructProperty match
```

偏移 `0x7A8`、类型 `Bool`，跟 IDA 里手动重建的字段完全对上。**结论**：字段名 `bUseTurnSwitchValidation` 现在有两条独立证据链——① 游戏自己的蓝图字节码引用（`.uasset` 数据本身）；② 对运行中进程做的反射转储（`GObjects-Dump-WithProperties.txt`）——两者互相印证，且都不依赖任何逆向 SDK 的头文件产出物。

### 顺带发现：这次转储也暴露了此前 IDA 结构体重建里的几处命名/结构误差

对比这份转储和此前 IDA 会话重建的 `AMatchControllerV2_Layout`：`0x7A9` 此前记为 `bMulliganAsActions`，真名是 `bUseActionsForMulligan`；`0x7AA` 此前是无名的 1 字节 gap，真名是 `bUseLocalSubActions`；`0x7AB` 此前记为 `bResyncInProgress`，真名是 `isResyncingMatch`（语义一致，名字不同）；更值得注意的是 `0x7B0` 起，此前曾猜测为几个独立字段（`BaseUrlA`/`MatchTypeName`/`MatchId`/`ConnectionStatus`/`BaseUrlB`），但转储显示这里实际是一个完整的 `StructProperty match`（一直到 `0x8B0` 的 `StartingData` 为止，约 256 字节）——说明这一段此前是被错误地拆成几个零散字段猜的，真实布局是一个内嵌结构体。这部分布局分析的修正本身超出本文档范围，留作后续工作，此处先如实记录下来，避免后续研究误用旧的猜测字段名。

## 蓝图侧只读，从未被赋值

在能拿到的全部反编译蓝图源码里搜索 `bUseTurnSwitchValidation`，命中 4 个文件，全部是**读取**，没有一处赋值：

- `Content/Blueprints/Logic/BP_OnlineMatch.cpp:24524`（`SetRandomStreamWithActionID`，见 README.md §2.2）
- `Content/Blueprints/BP_Board.cpp:4413`
- `Content/Blueprints/Cards/BP_HandCard.cpp`
- `Content/Blueprints/Logic/BP_VisualController.cpp`

结论：这个开关的赋值来源**不在蓝图层**，必然来自原生 C++ 侧。

## 在 IDA 里追查赋值点：native 代码里也完全找不到写入点——而这本身就是答案

按要求沿着 IDA 继续查了三条路，全部指向同一个结论：

1. **`AMatchControllerV2` 的全部 `exec*`（54 个）里没有构造函数**——列出的都是 `BlueprintCallable UFUNCTION` 的 native 入口，构造函数不是 `UFUNCTION`，不会生成 `exec*` 名字，在反汇编数据里目前也没有被单独识别/命名出来。
2. 转而检查两个最可能"重置成默认值"的候选——`MatchControllerV2_ResetVariables_Impl`（`0x144b05910`）和 `MatchControllerV2_ResetVariablesForResync_Impl`（`0x144b05bc0`），两个函数都已完整反编译并按同一偏移布局解读过。逐行确认：两者都会清零/重置一大堆字段（`ActionCounter3228`、`PendingActionQueue_*`、`DeckArray_*`、`ActionLogTablePtr` 哈希表、`bIsReconnecting`/`bResyncInProgress` 等等），**但都不触碰 `0x7A8`**。
3. 最关键的一步：用交叉引用查询（`xrefs_to_field`）直接查"整个反汇编数据里有没有任何机器码访问过 `AMatchControllerV2` 的 `0x7A8` 偏移"，返回**空结果——零个交叉引用**。

三条路径互相印证同一个结论：**这个字段在 native 机器码层面，没有任何一处硬编码的"读/写偏移 `0x7A8`"指令**。结合第一节已经确认的"蓝图侧只读、没有赋值节点"，这意味着它的值既不是蓝图设的，也不是被任何一段能反汇编到的原生代码用形如 `a1->bUseTurnSwitchValidation = x` 这样的直接偏移赋值设的。

这不是"还没找到"，而是可以给出一个具体、合理的解释：UE 的 `UPROPERTY` 默认值，本来就不是通过"某个函数里硬编码 `mov byte ptr [rax+7A8h], 1`"这种方式设置的——UHT 生成的类默认对象（CDO）构造过程，是通过反射系统按 `FProperty` 遍历、用属性自身携带的元数据初始化的；如果这个值还会被配置文件（`.ini`）或服务端下发的对局配置动态覆盖，那也是走一个**通用的、按属性名/`FProperty*` 查找的赋值路径**（同一段代码要能处理成百上千个不同属性，不可能给每个属性各写一条硬编码偏移的赋值指令）。这类"通用反射式赋值"在设计上就是不出现在针对某个具体偏移的 xref 搜索结果里的——所以"静态反汇编搜遍这个二进制,找不到显式赋值点"本身就是这类机制存在时的预期表现，而不是分析没做到位。

**结论**：截至目前，这个开关的值来自 native 反射式默认值/配置系统这一判断，有了三条独立的 IDA 证据支持（exec 函数列表为空、两个"重置"函数都不碰它、结构体字段 xref 为零），不再是单纯的"没找到，所以不知道"。具体默认值是 true 还是 false，原本认为只能靠动态调试坐实——但见下一节，已经从真实抓包里直接找到了答案，不再需要动态调试。

## 决定性证据：真实抓包里，服务端直接把这个值原样返回给客户端

两份真实抓包（Fiddler 格式，2026-08-14）里搜索 `validate_turn_switches`（跟原生字段名 `bUseTurnSwitchValidation` 高度对应——去掉 `bUse`/`Validation` 前后缀、复数形式一致），命中两处独立证据，指向同一个结论：

1. **服务端全局远程配置**（app 启动时拉取的功能开关列表，跟 `feature_socketerror_popup_enabled`、`feature_collection_cardhelpcache`、`monitor_battle` 等大量其他 `feature_*`/`enable_*` 开关并列出现在同一个 JSON 对象里）：
   ```
   "validate_turn_switches": 1
   ```
2. **单局对局创建请求体**（`POST .../lobbyplayers` 或等价的开局请求）里，客户端自己在 `extra_data` 里显式声明：
   ```
   "extra_data": { "match_type": "training", "validate_turn_switches": 1 }
   ```
   并且服务端在这局对局的**引导数据响应**（bootstrap，即 `match_and_starting_data` 所在的那个顶层响应体）末尾**原样回显**：
   ```
   ...starting_side":"left"}},"validate_turn_switches":true}
   ```

第 2 条是最强的证据：这不是一个抽象的全局配置项，而是**这一局对局自己的引导数据**里明确带着的字段，值是 `true`。结合第一节确认的"蓝图侧只读，找不到赋值节点"和上一节"native 侧也找不到硬编码赋值点"——这正好对上：这个值不是写死在客户端代码里的常量，而是**由服务端按每局对局下发**，客户端原生代码大概率就是把这个服务端下发的字段，通过反射系统直接写进了 `AMatchControllerV2::bUseTurnSwitchValidation`（这也是为什么静态反汇编搜不到硬编码赋值点——赋值路径是"从网络响应 JSON 按字段名反射写入"，不是"某处代码写死了 0x7A8"）。

**结论（更正为确定性结论）**：这两份真实抓包覆盖的对局（均为 `training`/AI 单机对局）里，`validate_turn_switches` 实际值是 **`true`（开启）**——也就是说，`SetRandomStreamWithActionID` 的重播种分支**在真实对局里是被启用的，不是被跳过的**。README.md §4.1 此前"统一结论"部分假设的"`bUseTurnSwitchValidation == false`、全场只播种一次"这个前提，在这两份真实抓包对应的对局类型下**是不成立的**——需要按这个新证据重新审视 Weather.md/SpyRing.md 里以"从未重播种"为主线的解释，具体影响见 [ReseedImpact.md](../ReseedImpact.md)（已根据这条证据更新其"目前不知道是哪种模式"的结论）。

抓包直接覆盖的只有 `match_type: "training"`（人机单机局）。PvP 天梯对局同样启用这个开关，已由持有账号、能直接在天梯对局中核实的本项目所有者确认——不是抓包证据，是直接确认。这个值是服务端按每局对局下发的字段（第 82 行已确认，不是客户端硬编码常量），所以只有 `training`/PvP 天梯之外的赛制（如锦标赛）取值仍未确认，需要那类赛制的真实抓包或直接确认才能补齐（见 [ReseedImpact.md](../ReseedImpact.md) §4）。

## 与随机数结论的关系

`bUseTurnSwitchValidation == false` 时，`SetRandomStreamWithActionID` 直接 return，`cardsRandomStream` 就不会按 `match_id + action_id*19390` 重新播种——整场对局共用同一条从 `match_id` 播种出来的确定性序列。这两份真实抓包（`training` 对局）里这个开关的值确认为 `true`，即重播种机制在这些对局里是启用的；具体影响见 [ReseedImpact.md](../ReseedImpact.md)。
