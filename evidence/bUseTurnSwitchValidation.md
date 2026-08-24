# `bUseTurnSwitchValidation`（native, `AMatchControllerV2 + 0x7A8`）

## 字段真实名称的来源：游戏自身的蓝图字节码，不是第三方 SDK

之前一版 IDA 手工重建的 `AMatchControllerV2_Layout` 结构体里，`0x7A8` 处的字段被临时命名为占位符 `bDebugMode`——这只是当时重建结构体的人随手起的名字，不代表游戏里这个字段真的叫这个。

真实字段名 `bUseTurnSwitchValidation` 的来源，是**游戏自己序列化在 `.uasset` 里的蓝图字节码**，通过 FModel 反编译直接读出来的——这是游戏自身的数据，不依赖任何第三方逆向 SDK（此前一版文档误引用了 Dumper-7 生成的 SDK 头文件作为佐证，已经去掉；那份 SDK 本身也是从同一套 UE 反射系统里导出的，参考意义不大，直接看游戏自己的蓝图数据即可）：

蓝图节点在调用一个原生 `UPROPERTY` 时，`.uasset` 里存的是对这个属性的 **`FName` 引用**（属性名本身作为反射元数据的一部分，序列化在蓝图资产里，供蓝图虚拟机在运行时按名字解析），FModel 反编译时会把这个引用还原成源码里的标识符名字。也就是说，`BP_OnlineMatch.cpp`、`BP_Board.cpp` 等反编译文件里出现的 `bUseTurnSwitchValidation` 这个名字，就是蓝图数据本身记录的名字，跟 IDA 里那个被临时叫做 `bDebugMode` 的 `0x7A8` 偏移，是同一个原生 bool 字段的两种不同来源的观察——一个是"蓝图侧怎么引用它"，一个是"native 内存布局里它在哪"。

## 尝试在 IDA 里直接验证这个名字：未能在预算内确认

按用户要求，尝试直接在 IDA 反汇编/字符串表里搜索字面量 `"bUseTurnSwitchValidation"`，用来验证这个名字是否也以明文形式存在于 `kards-Win64-Shipping.exe` 内（例如 UHT 为原生 `UCLASS` 生成的属性注册代码里，通常会把属性名作为字面量字符串传给 `FProperty` 构造函数）。两次尝试：

- `search_text`（按反汇编逐行渲染扫描）：分别以 `code_only=true` 和 `code_only=false` 跑过，均在 60 秒工具超时内没能扫完整个 `.text`（`0x140001000`-`0x14703d000`，约 112MB）或跨段范围，被强制中断，**没有得出"存在"或"不存在"的结论**。
- `find_regex`（走 IDA 预建的字符串表）：同样超时。

**没能搜到不代表这个字符串不存在**——这个二进制没有 PDB，而且 UE 的 `FName` 在很多路径下走的是全局名字池（`GNames`/`FNamePool`），运行时从名字池按索引取字符串，而不是每处引用都内联一份明文；这意味着即便属性名字符串在二进制里确实存在，它也可能只在名字池的序列化数据区出现**一次**，格式还可能经过压缩/非 ASCII 对齐编码，用简单的行扫描或字符串表正则去找，本身就不一定可靠——这跟"没有 PDB 的原生反射数据，很多东西没法直接靠搜索找到"是同一类限制，值得在这里明确记录下来，而不是silently 略过。

**结论**：这个字段名的证据链目前是——① 100% 确定来自游戏自身的蓝图字节码（不依赖第三方 SDK）；② IDA 里 `0x7A8` 处的 bool 偏移，是此前 IDA 会话通过 native 结构体重建单独确认的；③ ①②指向的是不是同一个字段，是基于"两者语义完全吻合"（一个决定要不要跳过随机数重播种的 `BlueprintReadOnly bool`）做出的合理推断，但**未能在本次 IDA 会话里，用字符串搜索这种最直接的方式，独立交叉验证这个字面量确实以明文形式出现在二进制里**——这是一个诚实的证据强度声明，不是"已经 100% 证实"。

## 蓝图侧只读，从未被赋值

在能拿到的全部反编译蓝图源码里搜索 `bUseTurnSwitchValidation`，命中 4 个文件，全部是**读取**，没有一处赋值：

- `Content/Blueprints/Logic/BP_OnlineMatch.cpp:24524`（`SetRandomStreamWithActionID`，见 README.md §2.2）
- `Content/Blueprints/BP_Board.cpp:4413`
- `Content/Blueprints/Cards/BP_HandCard.cpp`
- `Content/Blueprints/Logic/BP_VisualController.cpp`

结论：这个开关的赋值来源**不在蓝图层**，必然来自原生 C++ 侧（构造函数默认值、按对局类型/服务端下发配置动态设置，或是编译期 Shipping/Debug 分支）。截至目前静态反汇编搜索没能在预算内定位赋值点/默认值，这仍是一个开放问题——不代表默认值就是 false，只是"蓝图代码库里看不到谁把它设成了什么"。

## 与随机数结论的关系

`bUseTurnSwitchValidation == false` 时，`SetRandomStreamWithActionID` 直接 return，`cardsRandomStream` 就不会按 `match_id + action_id*19390` 重新播种——整场对局共用同一条从 `match_id` 播种出来的确定性序列。这是 README.md §4.1 "统一结论" 的前提条件，目前的证据强度是：**蓝图代码证实了这个开关存在、被读取、且能完全跳过重播种；但触发条件/默认值仍未定位到赋值点**。这个开关如果实际是**开启**的，对社区已发现规律的可用性有什么影响，见新增的 [ReseedImpact.md](../ReseedImpact.md)。
