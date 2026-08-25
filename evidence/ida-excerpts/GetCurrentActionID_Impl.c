// 反编译原文摘录，未加工。地址：0x144aec160，模块 kards-Win64-Shipping.exe。
// evidence/CurrentActionId-increment-logic.md 引用（"后者是纯 getter：return *(unsigned int *)(a1 + 3224)"），
// 就是下面这个函数本身；此前只以行内引号引用了返回语句，完整（其实也就是全部）原文见本文件。

// Trivial getter: returns dword field Context+3224 (current action ID counter). Fully resolved, no further calls.
__int64 __fastcall MatchControllerV2_GetCurrentActionID_Impl(__int64 a1)
{
  return *(unsigned int *)(a1 + 3224); /*0x144aec166*/
}
