// 反编译原文摘录，未加工。地址：0x143ddce50，模块 kards-Win64-Shipping.exe。
// 符号名 UKismetMathLibrary_execRandomIntegerInRangeFromStream 是分析过程中人工赋予的推测名
// （execXxx 是 UHT 为 BlueprintCallable UFUNCTION 生成的原生调用入口，能反汇编到）。
// 这是整个报告的地基：cardsRandomStream 每次抽样调用的最终原生实现，Weather.md §4.2/README.md §1
// 引用的 LCG 公式（Seed = Seed*196314165 + 907633515 mod 2^32）就是从这个函数反编译出来的，
// 此前文档只引用了核心 4 行伪代码，完整原文（含参数解包的 UE 蓝图 VM 样板代码）见本文件。
// 关键地址：0x143ddcf64 起，LCG 状态转移与取值的 4 行核心逻辑。

__int64 __fastcall UKismetMathLibrary_execRandomIntegerInRangeFromStream(
        UKismetMathLibrary *this,
        _QWORD *a2,
        _DWORD *a3)
{
  __int64 v5; // r8
  _QWORD *v6; // rax
  _QWORD *v7; // rdi
  __int64 v8; // r8
  __int64 v9; // r8
  __int64 result; // rax
  int v11; // edx
  int v12; // ecx
  unsigned int v13; // eax
  int v14; // ecx
  _QWORD v15[5]; // [rsp+20h] [rbp-28h] BYREF
  int v16; // [rsp+58h] [rbp+10h] BYREF
  int v17; // [rsp+60h] [rbp+18h] BYREF

  v15[0] = 0LL; /*0x143ddce64*/
  a2[7] = 0LL; /*0x143ddce6c*/
  a2[8] = 0LL; /*0x143ddce70*/
  if ( a2[4] ) /*0x143ddce74*/
  {
    FFrame_Step((__int64)a2, a2[3]); /*0x143ddce83*/
  }
  else
  {
    v5 = a2[17]; /*0x143ddce8a*/
    a2[17] = *(_QWORD *)(v5 + 24); /*0x143ddce95*/
    FFrame_StepExplicitProperty(a2, (__int64)v15, (_DWORD *)v5); /*0x143ddcea1*/
  }
  v6 = (_QWORD *)a2[7]; /*0x143ddcea6*/
  v7 = v15; /*0x143ddceaa*/
  v16 = 0; /*0x143ddceb2*/
  if ( v6 ) /*0x143ddceb6*/
    v7 = v6; /*0x143ddceb6*/
  MagicStatic_FIntProperty_Guard(); /*0x143ddceba*/
  if ( a2[4] ) /*0x143ddcec2*/
  {
    FFrame_Step((__int64)a2, a2[3]); /*0x143ddced1*/
  }
  else
  {
    v8 = a2[17]; /*0x143ddced8*/
    a2[17] = *(_QWORD *)(v8 + 24); /*0x143ddcee8*/
    FFrame_StepExplicitProperty(a2, (__int64)&v16, (_DWORD *)v8); /*0x143ddceef*/
  }
  v17 = 0; /*0x143ddcef4*/
  MagicStatic_FIntProperty_Guard(); /*0x143ddcef8*/
  if ( a2[4] ) /*0x143ddcf00*/
  {
    FFrame_Step((__int64)a2, a2[3]); /*0x143ddcf0f*/
  }
  else
  {
    v9 = a2[17]; /*0x143ddcf16*/
    a2[17] = *(_QWORD *)(v9 + 24); /*0x143ddcf26*/
    FFrame_StepExplicitProperty(a2, (__int64)&v17, (_DWORD *)v9); /*0x143ddcf2d*/
  }
  result = a2[4]; /*0x143ddcf32*/
  v11 = v16; /*0x143ddcf39*/
  a2[4] = result + (result != 0); /*0x143ddcf46*/
  v12 = v17 - v11 + 1; /*0x143ddcf50*/
  if ( v12 <= 0 ) /*0x143ddcf54*/
  {
    v14 = v11; /*0x143ddcf9e*/
  }
  else
  {
    v13 = 196314165 * *((_DWORD *)v7 + 1) + 907633515;// LCG MutateSeed inlined here: Seed = Seed*196314165 + 907633515 (mod 2^32). Constants confirmed byte-exact in this compiled binary (fork), not assumed from vanilla UE5.6 source. This is the real, single native implementation behind BP_CardFunctions::RandomIntFromRangeWithStream / cardFunction->RandomIntFromRangeWithStream (Kards RNG report investigation). /*0x143ddcf64*/
    *((_DWORD *)v7 + 1) = v13; /*0x143ddcf69*/
    result = (v13 >> 9) | 0x3F800000; /*0x143ddcf6f*/
    v14 = v11 + (int)(float)((float)(*(float *)&result - 1.0) * (float)v12); /*0x143ddcf88*/
  }
  *a3 = v14; /*0x143ddcf8a*/
  return result; /*0x143ddcf8c*/
}
