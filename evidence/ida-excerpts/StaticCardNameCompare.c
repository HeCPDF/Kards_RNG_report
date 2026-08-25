// 反编译原文摘录，未加工。地址：0x141376EA0，模块 kards-Win64-Shipping.exe。
// Weather.md §4.2 引用（"确认：比较的是两张卡各自的 Name 属性对应的 FNameEntry 字符串内容...
// 是标准的、不区分大小写的字典序字符串比较"）用于证明 GetAllStaticCardsSortedByName 排序结果
// 不依赖任何运行时状态。这是那条排序调用链最底层的字符串比较原语，
// 属于 FName 池查找 + 宽/窄字符串比较的标准 UE 实现，语义上比较"简单"，但为了完整存档仍原样收录。
// 上游调用链：sub_144B14100（排序核心）→ sub_14137F890（比较函数）→ 本函数（0x141376EA0）
// → sub_141215A10/sub_141215870（宽/窄字符串按长度截断比较，未单独存档，属于标准 CRT 级别原语）。

__int64 __fastcall sub_141376EA0(unsigned int a1, unsigned int a2)
{
  RTL_SRWLOCK *v4; // rsi
  _BYTE *v5; // rcx
  _BYTE *v6; // rax
  int v7; // ebx
  __m128i v8; // xmm1
  _BYTE *v9; // rcx
  _BYTE *v10; // rax
  int v11; // ebx
  unsigned __int64 v12; // rbx
  unsigned __int64 v13; // rdi
  __m128i *v14; // rsi
  _BYTE *v15; // rdi
  size_t v16; // rbx
  _BYTE *v17; // rcx
  _BYTE *v18; // rdx
  __int16 v19; // ax
  int v20; // eax
  __int64 result; // rax
  __m128i v22; // [rsp+20h] [rbp-E0h] BYREF
  __m128i v23; // [rsp+30h] [rbp-D0h] BYREF
  __m128i v24; // [rsp+40h] [rbp-C0h]
  _BYTE v25[2048]; // [rsp+50h] [rbp-B0h] BYREF
  _BYTE v26[2048]; // [rsp+850h] [rbp+750h] BYREF

  if ( byte_1491102D9 ) /*0x141376ee1*/
  {
    v4 = &stru_149110540; /*0x141376ee3*/
  }
  else
  {
    v4 = (RTL_SRWLOCK *)sub_14137A830(&stru_149110540); /*0x141376ef8*/
    byte_1491102D9 = 1; /*0x141376efb*/
  }
  v22.m128i_i32[1] = (unsigned __int16)a1; /*0x141376f0a*/
  v22.m128i_i32[0] = HIWORD(a1); /*0x141376f0e*/
  v5 = (char *)v4[HIWORD(a1) + 2].Ptr + 2 * (unsigned int)(unsigned __int16)a1; /*0x141376f1e*/
  v6 = v5 + 2; /*0x141376f26*/
  v7 = *(unsigned __int16 *)v5 >> 6; /*0x141376f2c*/
  if ( (*v5 & 1) != 0 ) /*0x141376f32*/
  {
    if ( v5 == (_BYTE *)-2LL ) /*0x141376f37*/
    {
      memcpy(v26, 0LL, 2 * ((unsigned __int64)MEMORY[0xFFFFFFFFFFFFFFFE] >> 6)); /*0x141376f4d*/
      v6 = v26; /*0x141376f52*/
    }
    v23.m128i_i8[12] = 1; /*0x141376f59*/
  }
  else
  {
    if ( v5 == (_BYTE *)-2LL ) /*0x141376f63*/
    {
      memcpy(v26, 0LL, (unsigned __int64)*(unsigned __int16 *)v5 >> 6); /*0x141376f76*/
      v6 = v26; /*0x141376f7b*/
    }
    v23.m128i_i8[12] = 0; /*0x141376f82*/
  }
  v23.m128i_i64[0] = (__int64)v6; /*0x141376f87*/
  v23.m128i_i32[2] = v7; /*0x141376f8e*/
  v8 = v23; /*0x141376f97*/
  v22.m128i_i32[1] = (unsigned __int16)a2; /*0x141376fa0*/
  v22.m128i_i32[0] = HIWORD(a2); /*0x141376fa4*/
  v24 = v23; /*0x141376fb1*/
  v9 = (char *)v4[HIWORD(a2) + 2].Ptr + 2 * (unsigned int)(unsigned __int16)a2; /*0x141376fbe*/
  v10 = v9 + 2; /*0x141376fc6*/
  v11 = *(unsigned __int16 *)v9 >> 6; /*0x141376fcc*/
  if ( (*v9 & 1) != 0 ) /*0x141376fd2*/
  {
    if ( v9 == (_BYTE *)-2LL ) /*0x141376fd7*/
    {
      memcpy(v25, 0LL, 2 * ((unsigned __int64)MEMORY[0xFFFFFFFFFFFFFFFE] >> 6)); /*0x141376feb*/
      v8 = v24; /*0x141376ff0*/
      v10 = v25; /*0x141376ff5*/
    }
    v22.m128i_i8[12] = 1; /*0x141376ffa*/
  }
  else
  {
    if ( v9 == (_BYTE *)-2LL ) /*0x141377004*/
    {
      memcpy(v25, 0LL, (unsigned __int64)*(unsigned __int16 *)v9 >> 6); /*0x141377015*/
      v8 = v24; /*0x14137701a*/
      v10 = v25; /*0x14137701f*/
    }
    v22.m128i_i8[12] = 0; /*0x141377024*/
  }
  v22.m128i_i64[0] = (__int64)v10; /*0x141377029*/
  v22.m128i_i32[2] = v11; /*0x141377033*/
  v12 = _mm_srli_si128(v8, 8).m128i_u64[0]; /*0x141377049*/
  v13 = _mm_srli_si128(v22, 8).m128i_u64[0]; /*0x14137704e*/
  if ( BYTE4(v12) != BYTE4(v13) ) /*0x141377063*/
  {
    v14 = &v22; /*0x14137706c*/
    if ( !BYTE4(v12) ) /*0x141377071*/
      v14 = &v23; /*0x141377071*/
    v15 = v25; /*0x141377075*/
    if ( !BYTE4(v12) ) /*0x141377081*/
      v15 = v26; /*0x141377081*/
    v16 = v14->m128i_u32[2]; /*0x141377088*/
    memcpy(v15, (const void *)v14->m128i_i64[0], v16); /*0x141377091*/
    v14->m128i_i64[0] = (__int64)v15; /*0x141377096*/
    if ( (_DWORD)v16 ) /*0x14137709b*/
    {
      v17 = &v15[v16]; /*0x14137709d*/
      v18 = &v15[2 * v16]; /*0x1413770a1*/
      do /*0x1413770c3*/
      {
        v19 = (char)*--v17; /*0x1413770b0*/
        *((_WORD *)v18 - 1) = v19; /*0x1413770b8*/
        v18 -= 2; /*0x1413770bc*/
        LODWORD(v16) = v16 - 1; /*0x1413770c0*/
      }
      while ( (_DWORD)v16 ); /*0x1413770c3*/
    }
    v14->m128i_i8[12] = 1; /*0x1413770c5*/
    LODWORD(v12) = v23.m128i_i32[2]; /*0x1413770c9*/
    LODWORD(v13) = v22.m128i_i32[2]; /*0x1413770ce*/
  }
  v20 = v13; /*0x1413770df*/
  if ( (unsigned int)v12 < (unsigned int)v13 ) /*0x1413770e1*/
    v20 = v12; /*0x1413770e1*/
  if ( v23.m128i_i8[12] ) /*0x1413770ec*/
    result = sub_141215A10(v23.m128i_i64[0], v22.m128i_i64[0], v20); /*0x1413770ee*/
  else
    result = sub_141215870(v23.m128i_i64[0], v22.m128i_i64[0], v20); /*0x1413770f5*/
  if ( !(_DWORD)result ) /*0x1413770fc*/
    return (unsigned int)(v12 - v13); /*0x141377100*/
  return result; /*0x141377102*/
}
