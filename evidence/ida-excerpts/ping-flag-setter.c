// 反编译原文摘录，未加工。地址：0x144A8F5D0，模块 kards-Win64-Shipping.exe。
// 来源：IDA (idalib/ida-gui MCP) decompile。
// 这是一个只写单个 ping 标志字节（+3476，即 MatchActionsPollLoop_Impl 判断条件里的第一个标志）、
// 不 touch 任何其它字段的独立函数，是最小的"置位"原语。
// 交叉引用（xrefs_to）只有一处数据段引用（0x147e1ca18），没有任何原生 CALL 指令调用它，
// 与"BlueprintCallable 原生函数，真正调用点在蓝图字节码里"这个假设一致，但该数据地址本身
// 没有被 IDA 识别出可读的反射表字段名，不构成逐字节确认。它跟蓝图属性 triggerPollActions
// 是否对应同一个原生偏移也没有逐字节钉死——见 evidence/CurrentActionId-increment-logic.md
// "ping 标志置位路径"一节末尾的说明。真正站得住、不依赖任何原生函数归因的证据是蓝图字节码本身
// （见 evidence/ida-excerpts/BP_KardsSession-matchaction-notification.cpp）。

void __fastcall sub_144A8F5D0(__int64 a1)
{
  *(_BYTE *)(a1 + 3476) = 1; /*0x144a8f5d0*/
}
