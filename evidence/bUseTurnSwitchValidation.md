# `bUseTurnSwitchValidation`（native, `AMatchControllerV2 + 0x7A8`）

## 字段真实名称的更正

之前一版 IDA 手工重建的 `AMatchControllerV2_Layout` 结构体里，`0x7A8` 处的字段被临时命名为占位符 `bDebugMode`。

对照 Dumper-7（基于 UE 反射系统的官方字段名导出，非猜测）生成的 SDK 头文件，可以确认这是错误占位名，真实字段就是 `bUseTurnSwitchValidation`：

```
kards_classes.hpp:2920:
    bool bUseTurnSwitchValidation;   // 0x07A8(0x0001)
    (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData,
     NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
```

`BlueprintReadOnly` 与偏移量都对得上 IDA 里手动重建的字段——同一个 bool。

## 蓝图侧只读，从未被赋值

在能拿到的全部反编译蓝图源码里搜索 `bUseTurnSwitchValidation`，命中 4 个文件，全部是**读取**，没有一处赋值：

- `Content/Blueprints/Logic/BP_OnlineMatch.cpp:24524`（`SetRandomStreamWithActionID`，见 README.md §2.2）
- `Content/Blueprints/BP_Board.cpp:4413`
- `Content/Blueprints/Cards/BP_HandCard.cpp`
- `Content/Blueprints/Logic/BP_VisualController.cpp`

结论：这个开关的赋值来源**不在蓝图层**，必然来自原生 C++ 侧（构造函数默认值、按对局类型/服务端下发配置动态设置，或是编译期 Shipping/Debug 分支）。截至目前静态反汇编搜索没能在预算内定位赋值点/默认值，这仍是一个开放问题——不代表默认值就是 false，只是"蓝图代码库里看不到谁把它设成了什么"。

## 与随机数结论的关系

`bUseTurnSwitchValidation == false` 时，`SetRandomStreamWithActionID` 直接 return，`cardsRandomStream` 就不会按 `match_id + action_id*19390` 重新播种——整场对局共用同一条从 `match_id` 播种出来的确定性序列。这是 README.md §4.1 "统一结论" 的前提条件，目前的证据强度是：**蓝图代码证实了这个开关存在、被读取、且能完全跳过重播种；但触发条件/默认值仍未定位到赋值点**。
