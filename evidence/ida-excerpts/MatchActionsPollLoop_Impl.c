// 反编译原文摘录，未加工。地址：0x144afd490，模块 kards-Win64-Shipping.exe。
// 来源：IDA (idalib/ida-gui MCP) decompile，Hex-Rays 微码反编译产物。
// 用途：evidence/CurrentActionId-increment-logic.md「轮询节奏」「ping 标志置位路径」两节的直接证据来源。
// 关键点已在正文标注：+3081 是"活跃轮询"状态字段，+3476/+3477 是本文件描述的两个 ping 标志，
// +3160 是上次轮询时间戳，+3224 是 CurrentActionId（构造 min_action_id 时读出），+3392 是"是否已有轮询请求在飞行中"。

void __fastcall MatchControllerV2_MatchActionsPollLoop_Impl(LARGE_INTEGER a1)
{
  _QWORD *v2; // rbx
  __int64 v3; // rax
  __int64 v4; // rdi
  double v5; // xmm6_8
  __int64 *v6; // r15
  char v7; // al
  __int64 v8; // rsi
  __int64 v9; // rcx
  int v10; // ebx
  float v11; // xmm6_4
  const wchar_t *v12; // r8
  __int64 v13; // r8
  __int64 v14; // rcx
  _QWORD *v15; // rax
  __int64 *v16; // rax
  __int64 v17; // rcx
  __int64 v18; // rdx
  __int64 v19; // rbx
  volatile signed __int32 *v20; // rbx
  volatile signed __int32 *v21; // rbx
  __int64 v22; // rdx
  LARGE_INTEGER *v23; // rbx
  __int128 v24; // [rsp+30h] [rbp-39h] BYREF
  __int64 v25; // [rsp+40h] [rbp-29h] BYREF
  __int64 v26; // [rsp+48h] [rbp-21h] BYREF
  __int64 v27; // [rsp+50h] [rbp-19h] BYREF
  __int64 v28; // [rsp+58h] [rbp-11h]
  __int128 v29; // [rsp+60h] [rbp-9h] BYREF
  _QWORD v30[2]; // [rsp+70h] [rbp+7h] BYREF
  _BYTE v31[8]; // [rsp+80h] [rbp+17h] BYREF
  volatile signed __int32 *v32; // [rsp+88h] [rbp+1Fh]
  _BYTE v33[8]; // [rsp+90h] [rbp+27h] BYREF
  volatile signed __int32 *v34; // [rsp+98h] [rbp+2Fh]
  LARGE_INTEGER PerformanceCount; // [rsp+D0h] [rbp+67h] BYREF

  if ( *(_BYTE *)(a1.QuadPart + 3081) == 4 )
  {
    QueryPerformanceCounter(&PerformanceCount); /*0x144afd3f2*/
    v5 = (double)(int)PerformanceCount.LowPart * *(double *)&qword_1490D1670 + 16777216.0; /*0x144afd410*/
    if ( *(_BYTE *)(a1.QuadPart + 3476) || *(_BYTE *)(a1.QuadPart + 3477) || v5 - *(double *)(a1.QuadPart + 3160) >= 5.0 )
    {
      v6 = (__int64 *)(a1.QuadPart + 3392); /*0x144afd478*/
      if ( !*(_QWORD *)(a1.QuadPart + 3392) && (!*(_BYTE *)(a1.QuadPart + 1960) || *(int *)(a1.QuadPart + 3072) <= 0) )
      {
        v7 = *(_BYTE *)(a1.QuadPart + 3320); /*0x144afd49f*/
        v8 = 0LL; /*0x144afd4a6*/
        *(double *)(a1.QuadPart + 3176) = v5; /*0x144afd4a8*/
        v9 = 0LL; /*0x144afd4b0*/
        v27 = 0LL; /*0x144afd4b2*/
        *(double *)(a1.QuadPart + 3160) = v5; /*0x144afd4b6*/
        v24 = 0uLL; /*0x144afd4be*/
        v28 = 0LL; /*0x144afd4c6*/
        if ( v7 == 1 ) /*0x144afd4cc*/
          v10 = *(_DWORD *)(a1.QuadPart + 2084); /*0x144afd4ce*/
        else
          v10 = *(_DWORD *)(a1.QuadPart + 2080); /*0x144afd4d6*/
        if ( v10 < 0
          && v7 == *(_BYTE *)(a1.QuadPart + 3321)
          && !*(_BYTE *)(a1.QuadPart + 3477)
          && *(_BYTE *)(a1.QuadPart + 3236) )
        {
          *(double *)(a1.QuadPart + 3168) = v5; /*0x144afd4f8*/
        }
        else
        {
          v11 = v5 - *(double *)(a1.QuadPart + 3184); /*0x144afd515*/
          if ( *(_DWORD *)(a1.QuadPart + 2072) ) /*0x144afd519*/
            v12 = *(const wchar_t **)(a1.QuadPart + 2064); /*0x144afd521*/
          else
            v12 = &chText; /*0x144afd52a*/
          sub_1411E56A0(&v29, L"%s", v12); /*0x144afd53c*/
          if ( (_QWORD)v24 ) /*0x144afd548*/
            FMemory_Free_Wrapper(v24); /*0x144afd54a*/
          v13 = *(unsigned int *)(a1.QuadPart + 3224); /*0x144afd55a*/
          v24 = v29; /*0x144afd565*/
          sub_1411E56A0(
            v30,
            L"{ \"min_action_id\": %d, \"opponent_id\": %d, \"time_since_opponent_ping\": %d}",
            v13,
            (unsigned int)v10,
            (int)v11);
          if ( v27 ) /*0x144afd58c*/
            FMemory_Free_Wrapper(v27); /*0x144afd58e*/
          v14 = *(_QWORD *)(a1.QuadPart + 3432); /*0x144afd59b*/
          v27 = v30[0]; /*0x144afd5a2*/
          v28 = v30[1]; /*0x144afd5a9*/
          v15 = (_QWORD *)sub_144AF5120(v14, v33); /*0x144afd5b2*/
          v16 = (__int64 *)(*(__int64 (__fastcall **)(_QWORD, _BYTE *, __int64, __int128 *, __int64 *))(*(_QWORD *)*v15 + 72LL))( /*0x144afd5d4*/
                             *v15,
                             v31,
                             1LL,
                             &v24,
                             &v27);
          v17 = v16[1]; /*0x144afd5d7*/
          v18 = *v16; /*0x144afd5db*/
          v25 = *v16; /*0x144afd5de*/
          v26 = v17; /*0x144afd5e2*/
          if ( v17 ) /*0x144afd5e9*/
          {
            _InterlockedIncrement((volatile signed __int32 *)(v17 + 8)); /*0x144afd5eb*/
            v17 = v26; /*0x144afd5ef*/
          }
          if ( v6 != &v25 ) /*0x144afd5fa*/
          {
            *v6 = v18; /*0x144afd5fc*/
            v25 = 0LL; /*0x144afd607*/
            sub_14122A770(a1.QuadPart + 3400, &v26); /*0x144afd60b*/
            v17 = v26; /*0x144afd610*/
          }
          if ( v17 ) /*0x144afd61d*/
          {
            if ( _InterlockedExchangeAdd((volatile signed __int32 *)(v17 + 8), 0xFFFFFFFF) == 1 ) /*0x144afd62a*/
            {
              v19 = v26; /*0x144afd62c*/
              (**(void (__fastcall ***)(__int64))v26)(v26); /*0x144afd636*/
              if ( _InterlockedExchangeAdd((volatile signed __int32 *)(v19 + 12), 0xFFFFFFFF) == 1 ) /*0x144afd643*/
                (*(void (__fastcall **)(__int64, __int64))(*(_QWORD *)v26 + 8LL))(v26, 1LL); /*0x144afd650*/
            }
          }
          v20 = v32; /*0x144afd653*/
          if ( v32 ) /*0x144afd65a*/
          {
            if ( _InterlockedExchangeAdd(v32 + 2, 0xFFFFFFFF) == 1 ) /*0x144afd667*/
            {
              (**(void (__fastcall ***)(volatile signed __int32 *))v20)(v20); /*0x144afd66f*/
              if ( _InterlockedExchangeAdd(v20 + 3, 0xFFFFFFFF) == 1 ) /*0x144afd67c*/
                (*(void (__fastcall **)(volatile signed __int32 *, __int64))(*(_QWORD *)v20 + 8LL))(v20, 1LL); /*0x144afd689*/
            }
          }
          v21 = v34; /*0x144afd68c*/
          if ( v34 ) /*0x144afd693*/
          {
            if ( _InterlockedExchangeAdd(v34 + 2, 0xFFFFFFFF) == 1 ) /*0x144afd6a0*/
            {
              (**(void (__fastcall ***)(volatile signed __int32 *))v21)(v21); /*0x144afd6a8*/
              if ( _InterlockedExchangeAdd(v21 + 3, 0xFFFFFFFF) == 1 ) /*0x144afd6b4*/
                (*(void (__fastcall **)(volatile signed __int32 *, __int64))(*(_QWORD *)v21 + 8LL))(v21, 1LL); /*0x144afd6bf*/
            }
          }
          v22 = *v6 + 24; /*0x144afd6ca*/
          *(_BYTE *)(a1.QuadPart + 3477) = 0; /*0x144afd6ce*/
          v23 = (LARGE_INTEGER *)sub_1411D5A10(40LL, v22); /*0x144afd6da*/
          if ( v23 ) /*0x144afd6e0*/
          {
            v23->QuadPart = (LONGLONG)&off_1470799B0; /*0x144afd6e9*/
            v23[2].QuadPart = sub_1411D78D0(); /*0x144afd6f1*/
            v23->QuadPart = (LONGLONG)off_147E40E78; /*0x144afd6fc*/
            if ( byte_1491E0480 ) /*0x144afd706*/
              ((void (__fastcall *)(_QWORD))sub_1414A7EB0)((LARGE_INTEGER)a1.QuadPart); /*0x144afd70b*/
            v23[3].QuadPart = 0LL; /*0x144afd710*/
            PerformanceCount = a1; /*0x144afd71b*/
            if ( byte_1491E0480 ) /*0x144afd71f*/
              ((void (__fastcall *)(_QWORD))sub_1414A7EB0)((LARGE_INTEGER)a1.QuadPart); /*0x144afd724*/
            sub_1415CDF70(&v23[3], &PerformanceCount); /*0x144afd731*/
            v23[4] = a1; /*0x144afd736*/
          }
          sub_14451DBD0(*v6, 0LL); /*0x144afd73f*/
          v9 = v27; /*0x144afd744*/
          v8 = v24; /*0x144afd748*/
        }
        if ( v9 ) /*0x144afd757*/
        {
          FMemory_Free_Wrapper(v9); /*0x144afd759*/
          v8 = v24; /*0x144afd75e*/
        }
        if ( v8 ) /*0x144afd765*/
          FMemory_Free_Wrapper(v8); /*0x144afd76a*/
      }
    }
    else
    {
      if ( v5 - *(double *)(a1.QuadPart + 3176) > 4.0 ) /*0x144afd44b*/
      {
        ((void (__fastcall *)(_QWORD))sub_144A92630)((LARGE_INTEGER)a1.QuadPart); /*0x144afd450*/
        *(double *)(a1.QuadPart + 3176) = v5; /*0x144afd455*/
      }
      *(_QWORD *)(a1.QuadPart + 3168) = *(_QWORD *)(a1.QuadPart + 3160); /*0x144afd464*/
    }
  }
  else
  {
    v2 = (_QWORD *)(a1.QuadPart + 3688); /*0x144afd3a0*/
    if ( *(_QWORD *)(a1.QuadPart + 3688) ) /*0x144afd3a7*/
    {
      v3 = ((__int64 (__fastcall *)(_QWORD))sub_143836BF0)((LARGE_INTEGER)a1.QuadPart); /*0x144afd3b1*/
      v4 = sub_14438C5C0(v3); /*0x144afd3c4*/
      if ( sub_144315520(v4, v2) ) /*0x144afd3c7*/
        sub_14431A810(v4, *v2); /*0x144afd3d7*/
      *v2 = 0LL; /*0x144afd3de*/
    }
  }
}
