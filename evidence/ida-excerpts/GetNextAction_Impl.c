// 反编译原文摘录，未加工。地址：0x144af2180，模块 kards-Win64-Shipping.exe。
// 符号名 MatchControllerV2_GetNextAction_Impl 是分析过程中人工赋予的推测名。
// 这是 CurrentActionId（this+3224/0xC98）推进逻辑的核心状态机，是
// evidence/CurrentActionId-increment-logic.md 全文分析的中心函数——此前该文档只引用了
// 其中几个具体地址片段（0x144af259d/0x144af27eb/0x144af2909/0x144af2978），完整原文见本文件。
// 关键地址对照（均在下方函数体内）：
//   0x144af259d  ++*(a1+3224)   —— 重复的 XActionEndOfTurn 递归跳过路径上的自增
//   0x144af27eb  ++*(a1+3224)   —— 主处理分支（非重复动作）的自增
//   0x144af2909  ++*(a1+3228)   —— 仅当动作归属方等于本地缓存己方 ID 时才自增的 Counter3228
//   0x144af2978  *(a1+3224)=1   —— 动作日志哈希表查不到下一个 slot 时，直接重置为 1
//   0x144af2a2c  "RESYNC: gap in action IDs" —— 检测到动作 ID 空洞时的重同步日志

// Native impl for GetNextAction() -- the core turn/action-log state machine. Walks the same action-log hash table as MatchControllerV2_GetMostRecentAction_Impl (Context+3240/+3248/+3292/+3296/+3304/+3312), recognizes special action-type strings "XActionStartOfTurn"/"XActionEndOfTurn"/"XActionMulligan" (via FString_EqualsIgnoreCase_Maybe / FString_NotEquals_Maybe), recurses on itself to skip duplicate/degenerate turn-boundary actions, tracks per-side action counters at Context+3464/+3456/+3468 (a growable buffer, realloc via sub_1411AF9E0), and on end-of-turn conditions rebuilds/rehashes the action-log table (sub_144A91ED0/sub_1416B78E0/sub_144B02F20) and notifies via sub_144B00F40 (same callee used by execFinishedEvaluatingActionsForReconnect). On a detected gap in action IDs it emits a "RESYNC: gap in action IDs" log line via sub_144AFD0C0 and calls sub_144A92870 (likely a resync-request trigger). VERY LARGE/COMPLEX -- only the top-level control flow was read; numerous nested helper subs (sub_144AB7700, sub_14...
__int64 __fastcall MatchControllerV2_GetNextAction_Impl(__int64 a1, __int64 a2, _BYTE *a3)
{
  int v3; // edi
  __int64 result; // rax
  char v7; // r12
  int v8; // r9d
  __int64 v9; // rdx
  __int64 v10; // r8
  __int64 v11; // rcx
  int v12; // r8d
  int v13; // edx
  __int64 v14; // r10
  int v15; // r10d
  int v16; // r8d
  int *v17; // r9
  int v18; // ecx
  int v19; // ecx
  unsigned __int64 v20; // rax
  int v21; // eax
  __int64 v22; // r8
  __int64 v23; // r9
  __int64 v24; // rcx
  __int64 v25; // rcx
  int v26; // edx
  unsigned __int16 *v27; // r15
  int v28; // esi
  unsigned __int16 *v29; // r13
  int v30; // r8d
  __int64 v31; // rdx
  int v32; // eax
  __int64 v33; // rdx
  char v34; // si
  __int64 v35; // rdx
  __int64 v36; // rdx
  int v37; // r8d
  int v38; // eax
  __int64 v39; // rdx
  __int64 v40; // rcx
  __int64 v41; // rcx
  int v42; // eax
  bool v43; // zf
  __int64 v44; // rdx
  unsigned __int16 *v45; // rcx
  unsigned __int16 *v46; // rcx
  __int64 v47; // r8
  __int64 v48; // rdx
  int v49; // eax
  __int64 v50; // rdx
  __int64 v51; // rcx
  __int64 v52; // rdx
  unsigned __int16 *v53; // rcx
  __int64 v54; // rdx
  int v55; // eax
  __int64 v56; // r8
  int v57; // eax
  __int64 v58; // rcx
  __int64 v59; // r8
  _BYTE v60[40]; // [rsp+20h] [rbp-69h] BYREF
  __int64 v61; // [rsp+48h] [rbp-41h]
  __int64 v62; // [rsp+50h] [rbp-39h]
  __int64 v63; // [rsp+58h] [rbp-31h]
  __int128 v64; // [rsp+60h] [rbp-29h] BYREF
  __int128 v65; // [rsp+70h] [rbp-19h]
  __int128 v66; // [rsp+80h] [rbp-9h] BYREF
  __int128 i; // [rsp+90h] [rbp+7h]
  __int64 v68; // [rsp+A0h] [rbp+17h]

  v3 = 0; /*0x144af219b*/
  *a3 = 0; /*0x144af21a0*/
  result = *(unsigned int *)(a1 + 3248); /*0x144af21a6*/
  v7 = 0; /*0x144af21ac*/
  v8 = *(_DWORD *)(a1 + 3224); /*0x144af21af*/
  if ( (_DWORD)result != *(_DWORD *)(a1 + 3292) )
  {
    v9 = *(_QWORD *)(a1 + 3304); /*0x144af21c1*/
    v10 = a1 + 3296; /*0x144af21c8*/
    v11 = v8 & (unsigned int)(*(_DWORD *)(a1 + 3312) - 1); /*0x144af21d7*/
    if ( !v9 ) /*0x144af21dd*/
      v9 = v10; /*0x144af21dd*/
    v12 = *(_DWORD *)(v9 + 4 * v11); /*0x144af21e1*/
    v13 = v12; /*0x144af21e5*/
    if ( v12 != -1 )
    {
      v14 = *(_QWORD *)(a1 + 3240); /*0x144af21ee*/
      while ( 1 ) /*0x144af2200*/
      {
        result = v13; /*0x144af2200*/
        if ( *(_DWORD *)(v14 + 80LL * v13) == v8 ) /*0x144af220e*/
          break; /*0x144af220e*/
        v13 = *(_DWORD *)(v14 + 80LL * v13 + 72); /*0x144af2214*/
        if ( v13 == -1 ) /*0x144af221c*/
          goto LABEL_8; /*0x144af221c*/
      }
      if ( v13 != -1 )
      {
        while ( 1 ) /*0x144af2407*/
        {
          v24 = 80LL * v12; /*0x144af2407*/
          if ( *(_DWORD *)(v14 + v24) == v8 ) /*0x144af2413*/
            break; /*0x144af2413*/
          v12 = *(_DWORD *)(v14 + v24 + 72); /*0x144af2419*/
          if ( v12 == -1 ) /*0x144af2421*/
            goto LABEL_26; /*0x144af2421*/
        }
        v35 = v24 + *(_QWORD *)(a1 + 3240); /*0x144af25ba*/
        if ( !v35 ) /*0x144af25bd*/
        {
LABEL_26:
          v25 = 0LL; /*0x144af2423*/
          v26 = 0; /*0x144af2429*/
          v62 = 0LL; /*0x144af242b*/
          v63 = 0LL; /*0x144af242f*/
          v27 = 0LL; /*0x144af2432*/
          v28 = 0; /*0x144af2438*/
          *(_QWORD *)v60 = 0xFFFFFFFFLL; /*0x144af243a*/
          *(_OWORD *)&v60[24] = 0xFFFFFFFFuLL; /*0x144af2441*/
          v61 = 0LL; /*0x144af244c*/
          goto LABEL_27; /*0x144af244c*/
        }
        sub_144AB7700(v60, v35 + 8); /*0x144af25cb*/
        v26 = v63; /*0x144af25d0*/
        v25 = v62; /*0x144af25d3*/
        v28 = *(_DWORD *)&v60[16]; /*0x144af25d7*/
        v27 = *(unsigned __int16 **)&v60[8]; /*0x144af25da*/
LABEL_27:
        *(_QWORD *)&v60[8] = 0LL; /*0x144af2453*/
        *(_QWORD *)&v60[16] = 0LL; /*0x144af2457*/
        ExecParam_DestructArrayOfStructPairs_Stride32(v25, v26); /*0x144af245b*/
        if ( v62 ) /*0x144af2467*/
          FMemory_Free_Wrapper(v62); /*0x144af2469*/
        ExecParam_DestructArrayElements_Stride40(*(_QWORD **)&v60[32], v61); /*0x144af2475*/
        if ( *(_QWORD *)&v60[32] ) /*0x144af2481*/
          FMemory_Free_Wrapper(*(__int64 *)&v60[32]); /*0x144af2483*/
        if ( *(_QWORD *)&v60[8] ) /*0x144af248f*/
          FMemory_Free_Wrapper(*(__int64 *)&v60[8]); /*0x144af2491*/
        v29 = (unsigned __int16 *)&chText; /*0x144af249d*/
        v30 = *(_DWORD *)(a1 + 3224) - 1; /*0x144af24aa*/
        if ( *(_DWORD *)(a1 + 3248) == *(_DWORD *)(a1 + 3292) ) /*0x144af24b3*/
          goto LABEL_40; /*0x144af24b3*/
        v31 = *(_QWORD *)(a1 + 3304); /*0x144af24bb*/
        if ( !v31 ) /*0x144af24d4*/
          v31 = a1 + 3296; /*0x144af24d4*/
        v32 = *(_DWORD *)(v31 + 4LL * (v30 & (unsigned int)(*(_DWORD *)(a1 + 3312) - 1))); /*0x144af24d8*/
        if ( v32 == -1 ) /*0x144af24de*/
          goto LABEL_40; /*0x144af24de*/
        v33 = *(_QWORD *)(a1 + 3240); /*0x144af24e0*/
        while ( *(_DWORD *)(v33 + 80LL * v32) != v30 ) /*0x144af24fd*/
        {
          v32 = *(_DWORD *)(v33 + 80LL * v32 + 72); /*0x144af2503*/
          if ( v32 == -1 ) /*0x144af250a*/
            goto LABEL_40; /*0x144af250a*/
        }
        v36 = *(_QWORD *)(a1 + 3304); /*0x144af25e3*/
        v37 = *(_DWORD *)(a1 + 3224) - 1; /*0x144af25fe*/
        if ( !v36 ) /*0x144af2604*/
          v36 = a1 + 3296; /*0x144af2604*/
        v38 = *(_DWORD *)(v36 + 4LL * (v37 & (unsigned int)(*(_DWORD *)(a1 + 3312) - 1))); /*0x144af2610*/
        v39 = *(_QWORD *)(a1 + 3240); /*0x144af2613*/
        while ( 1 ) /*0x144af2626*/
        {
          v40 = 80LL * v38; /*0x144af2626*/
          if ( *(_DWORD *)(v39 + v40) == v37 ) /*0x144af2632*/
            break; /*0x144af2632*/
          v38 = *(_DWORD *)(v39 + v40 + 72); /*0x144af2634*/
          if ( v38 == -1 ) /*0x144af263a*/
            goto LABEL_59; /*0x144af263a*/
        }
        v44 = v40 + *(_QWORD *)(a1 + 3240); /*0x144af2681*/
        if ( !v44 ) /*0x144af2684*/
        {
LABEL_59:
          v41 = 0LL; /*0x144af263c*/
          v42 = 0; /*0x144af2642*/
          *(_QWORD *)&v60[16] = 0LL; /*0x144af2648*/
          *(_OWORD *)v60 = 0xFFFFFFFFuLL; /*0x144af264e*/
          *(_OWORD *)&v60[24] = 0xFFFFFFFFuLL; /*0x144af2658*/
          v61 = 0LL; /*0x144af2663*/
          v62 = 0LL; /*0x144af2667*/
          v63 = 0LL; /*0x144af266b*/
          goto LABEL_60; /*0x144af266b*/
        }
        sub_144AB7700(v60, v44 + 8); /*0x144af268e*/
        v42 = *(_DWORD *)&v60[16]; /*0x144af2693*/
        v41 = *(_QWORD *)&v60[8]; /*0x144af2696*/
LABEL_60:
        if ( v42 == v28 )
        {
          if ( v42 <= 1 )
          {
LABEL_67:
            v45 = (unsigned __int16 *)&chText; /*0x144af26bc*/
            if ( v28 ) /*0x144af26c8*/
              v45 = v27; /*0x144af26c8*/
            if ( !(unsigned int)FString_EqualsIgnoreCase_Maybe(v45, "XActionStartOfTurn") ) /*0x144af26cc*/
              goto LABEL_73; /*0x144af26cc*/
            v46 = (unsigned __int16 *)&chText; /*0x144af26de*/
            v7 = 1; /*0x144af26e1*/
            if ( v28 ) /*0x144af26e7*/
              v46 = v27; /*0x144af26e7*/
            if ( !(unsigned int)FString_EqualsIgnoreCase_Maybe(v46, "XActionEndOfTurn") )
            {
LABEL_73:
              v34 = 1; /*0x144af26f8*/
              v7 = 1; /*0x144af26fb*/
LABEL_41:
              if ( (v7 & 1) != 0 ) /*0x144af2513*/
              {
                ExecParam_DestructArrayOfStructPairs_Stride32(v62, v63); /*0x144af251c*/
                if ( v62 ) /*0x144af2528*/
                  FMemory_Free_Wrapper(v62); /*0x144af252a*/
                ExecParam_DestructArrayElements_Stride40(*(_QWORD **)&v60[32], v61); /*0x144af2536*/
                if ( *(_QWORD *)&v60[32] ) /*0x144af2542*/
                  FMemory_Free_Wrapper(*(__int64 *)&v60[32]); /*0x144af2544*/
                if ( *(_QWORD *)&v60[8] ) /*0x144af2550*/
                  FMemory_Free_Wrapper(*(__int64 *)&v60[8]); /*0x144af2552*/
              }
              if ( v34 ) /*0x144af255a*/
              {
                if ( *(_BYTE *)(a1 + 1960) ) /*0x144af2560*/
                {
                  sub_1411E56A0( /*0x144af2582*/
                    &v64,
                    L"DUPLICATE END TURN IN MATCH %d action, %d",
                    *(unsigned int *)(a1 + 2028),
                    *(unsigned int *)(a1 + 3224));
                  sub_144AFD0C0(a1, &v64, 0LL); /*0x144af2591*/
                }
                ++*(_DWORD *)(a1 + 3224); /*0x144af259d*/
                result = MatchControllerV2_GetNextAction_Impl(a1, a2, a3); /*0x144af25a9*/
LABEL_124:
                if ( v27 ) /*0x144af29ee*/
                  return FMemory_Free_Wrapper((__int64)v27); /*0x144af29f3*/
                return result; /*0x144af29f3*/
              }
              *a3 = 1; /*0x144af270a*/
              v47 = *(unsigned int *)(a1 + 3224); /*0x144af2713*/
              if ( *(_DWORD *)(a1 + 3248) == *(_DWORD *)(a1 + 3292) ) /*0x144af2720*/
                goto LABEL_81; /*0x144af2720*/
              v48 = *(_QWORD *)(a1 + 3304); /*0x144af2722*/
              if ( !v48 ) /*0x144af2739*/
                v48 = a1 + 3296; /*0x144af2739*/
              v49 = *(_DWORD *)(v48 + 4LL * ((unsigned int)v47 & (*(_DWORD *)(a1 + 3312) - 1))); /*0x144af2742*/
              if ( v49 == -1 ) /*0x144af2748*/
                goto LABEL_81; /*0x144af2748*/
              v50 = *(_QWORD *)(a1 + 3240); /*0x144af274a*/
              while ( 1 ) /*0x144af2757*/
              {
                v51 = 80LL * v49; /*0x144af2757*/
                if ( *(_DWORD *)(v50 + v51) == (_DWORD)v47 ) /*0x144af2763*/
                  break; /*0x144af2763*/
                v49 = *(_DWORD *)(v50 + v51 + 72); /*0x144af2769*/
                if ( v49 == -1 ) /*0x144af276f*/
                  goto LABEL_81; /*0x144af276f*/
              }
              v54 = v51 + *(_QWORD *)(a1 + 3240); /*0x144af2841*/
              if ( !v54 ) /*0x144af2844*/
              {
LABEL_81:
                *(_OWORD *)v60 = 0xFFFFFFFFuLL; /*0x144af2771*/
                *(_QWORD *)&v60[16] = 0LL; /*0x144af2782*/
                *(_OWORD *)&v60[24] = 0xFFFFFFFFuLL; /*0x144af2786*/
                v61 = 0LL; /*0x144af2791*/
                v62 = 0LL; /*0x144af2795*/
                v63 = 0LL; /*0x144af2799*/
              }
              else
              {
                sub_144AB7700(v60, v54 + 8); /*0x144af2852*/
              }
              sub_144AB9C50(a2, v60, v47); /*0x144af27a4*/
              ExecParam_DestructArrayOfStructPairs_Stride32(v62, v63); /*0x144af27b0*/
              if ( v62 ) /*0x144af27bc*/
                FMemory_Free_Wrapper(v62); /*0x144af27be*/
              ExecParam_DestructArrayElements_Stride40(*(_QWORD **)&v60[32], v61); /*0x144af27ca*/
              if ( *(_QWORD *)&v60[32] ) /*0x144af27d6*/
                FMemory_Free_Wrapper(*(__int64 *)&v60[32]); /*0x144af27d8*/
              if ( *(_QWORD *)&v60[8] ) /*0x144af27e4*/
                FMemory_Free_Wrapper(*(__int64 *)&v60[8]); /*0x144af27e6*/
              ++*(_DWORD *)(a1 + 3224); /*0x144af27eb*/
              if ( *(_BYTE *)(a1 + 680) ) /*0x144af27f1*/
                goto LABEL_106; /*0x144af27f1*/
              if ( *(_BYTE *)(a1 + 3082) != 2 && !*(_BYTE *)(a1 + 681) && !*(_BYTE *)(a1 + 1960) )
              {
                if ( !*(_BYTE *)(a1 + 1961)
                  || (!*(_DWORD *)(a2 + 16)
                    ? (v53 = (unsigned __int16 *)&chText)
                    : (v53 = *(unsigned __int16 **)(a2 + 8)),
                      (unsigned int)FString_EqualsIgnoreCase_Maybe(v53, "XActionMulligan")) )
                {
                  if ( *(_DWORD *)(a2 + 24) == *(_DWORD *)(*(_QWORD *)(a1 + 3432) + 2024LL) ) /*0x144af2880*/
                  {
                    v55 = *(_DWORD *)(a1 + 3464); /*0x144af2882*/
                    if ( v55 == *(_DWORD *)(a1 + 3468) ) /*0x144af2892*/
                      v55 = sub_1411AF9E0(2112LL, a1 + 3456, a1 + 3468); /*0x144af28a0*/
                    *(_DWORD *)(a1 + 3464) = v55 + 1; /*0x144af28ab*/
                    sub_144AB7700(*(_QWORD *)(a1 + 3456) + ((__int64)v55 << 6), a2); /*0x144af28bf*/
                    result = MatchControllerV2_GetNextAction_Impl(a1, a2, a3); /*0x144af28cd*/
                    goto LABEL_124; /*0x144af28d2*/
                  }
                }
              }
              if ( *(_BYTE *)(a1 + 680) || *(_BYTE *)(a1 + 3082) == 2 || *(_BYTE *)(a1 + 681) ) /*0x144af28e9*/
              {
LABEL_106:
                if ( *(_DWORD *)(a2 + 24) == *(_DWORD *)(*(_QWORD *)(a1 + 3432) + 2024LL) ) /*0x144af2907*/
                  ++*(_DWORD *)(a1 + 3228); /*0x144af2909*/
                if ( *(_BYTE *)(a1 + 681) ) /*0x144af290f*/
                {
                  v56 = *(unsigned int *)(a1 + 3224); /*0x144af2922*/
                  if ( *(_DWORD *)(a1 + 3248) == *(_DWORD *)(a1 + 3292) ) /*0x144af292f*/
                    goto LABEL_116; /*0x144af292f*/
                  v52 = *(_QWORD *)(a1 + 3304); /*0x144af2931*/
                  if ( !v52 ) /*0x144af2948*/
                    v52 = a1 + 3296; /*0x144af2948*/
                  v57 = *(_DWORD *)(v52 + 4LL * ((unsigned int)v56 & (*(_DWORD *)(a1 + 3312) - 1))); /*0x144af2951*/
                  if ( v57 == -1 ) /*0x144af2957*/
                  {
LABEL_116:
                    *(_DWORD *)(a1 + 3224) = 1; /*0x144af2978*/
                    v58 = a1 + 3240; /*0x144af298d*/
                    if ( *(int *)(a1 + 3312) > 1 ) /*0x144af2990*/
                    {
                      sub_144A91ED0(v58, 0LL, v56); /*0x144af29a5*/
                      *(_DWORD *)(a1 + 3312) = 1; /*0x144af29ad*/
                      sub_144B02F20(a1 + 3240); /*0x144af29b4*/
                    }
                    else
                    {
                      sub_1416B78E0(v58, v52, v56); /*0x144af2992*/
                      sub_144A91ED0(a1 + 3240, 0LL, v59); /*0x144af299c*/
                    }
                    MatchControllerV2_OnActionsEvaluationComplete_Impl(a1); /*0x144af29bc*/
                  }
                  else
                  {
                    v52 = *(_QWORD *)(a1 + 3240); /*0x144af2959*/
                    while ( *(_DWORD *)(v52 + 80LL * v57) != (_DWORD)v56 ) /*0x144af296d*/
                    {
                      v57 = *(_DWORD *)(v52 + 80LL * v57 + 72); /*0x144af296f*/
                      if ( v57 == -1 ) /*0x144af2976*/
                        goto LABEL_116; /*0x144af2976*/
                    }
                  }
                }
              }
              if ( *(_DWORD *)(a2 + 16) ) /*0x144af29c1*/
                v29 = *(unsigned __int16 **)(a2 + 8); /*0x144af29c8*/
              result = FString_EqualsIgnoreCase_Maybe(v29, "XActionEndOfTurn"); /*0x144af29d6*/
              if ( !(_DWORD)result ) /*0x144af29dd*/
                result = sub_144AF65C0((AMatchControllerV2_Layout *)a1); /*0x144af29e6*/
              goto LABEL_124; /*0x144af29e6*/
            }
LABEL_40:
            v34 = 0; /*0x144af250c*/
            goto LABEL_41; /*0x144af250c*/
          }
          v43 = (unsigned int)FString_NotEquals_Maybe(v41, v27) == 0; /*0x144af26a9*/
        }
        else
        {
          v43 = v28 + v42 == 1; /*0x144af2675*/
        }
        v7 = 1; /*0x144af26ae*/
        if ( !v43 ) /*0x144af26b6*/
          goto LABEL_40; /*0x144af26b6*/
        goto LABEL_67; /*0x144af26b6*/
      }
    }
  }
LABEL_8:
  if ( !*(_BYTE *)(a1 + 1960) ) /*0x144af2225*/
    return result; /*0x144af2225*/
  *(_QWORD *)&v64 = 0x100000000LL; /*0x144af2232*/
  v15 = *(_DWORD *)(a1 + 3280); /*0x144af2235*/
  v16 = 0; /*0x144af2244*/
  *((_QWORD *)&v64 + 1) = a1 + 3256; /*0x144af2247*/
  LODWORD(v65) = -1; /*0x144af224b*/
  *(_QWORD *)((char *)&v65 + 4) = 0LL; /*0x144af2252*/
  if ( v15 ) /*0x144af2259*/
  {
    v17 = *(int **)(a1 + 3272); /*0x144af225b*/
    if ( !v17 ) /*0x144af2262*/
      v17 = (int *)(a1 + 3256); /*0x144af2262*/
    v18 = *v17; /*0x144af2270*/
    if ( *v17 ) /*0x144af2270*/
    {
LABEL_15:
      DWORD1(v64) = v18 & -v18; /*0x144af22a6*/
      _BitScanReverse64(&v20, 2LL * DWORD1(v64) + 1); /*0x144af22b7*/
      DWORD1(v65) = v16 + v20 - 1; /*0x144af22c0*/
      if ( SDWORD1(v65) <= v15 ) /*0x144af22c6*/
        goto LABEL_17; /*0x144af22c6*/
    }
    else
    {
      while ( 1 ) /*0x144af2280*/
      {
        v19 = v3 + 1; /*0x144af2280*/
        v16 += 32; /*0x144af2283*/
        LODWORD(v64) = v19; /*0x144af2287*/
        ++v3; /*0x144af228a*/
        DWORD2(v65) = v16; /*0x144af228c*/
        if ( v19 > (v15 - 1) / 32 ) /*0x144af2292*/
          break; /*0x144af2292*/
        LODWORD(v65) = -1; /*0x144af2297*/
        v18 = v17[v19]; /*0x144af229e*/
        if ( v18 ) /*0x144af22a4*/
          goto LABEL_15; /*0x144af22a4*/
      }
    }
    DWORD1(v65) = v15; /*0x144af22c8*/
  }
LABEL_17:
  v21 = *(_DWORD *)(a1 + 3280); /*0x144af22cc*/
  *(_QWORD *)v60 = a1 + 3240; /*0x144af22e4*/
  *(_OWORD *)&v60[24] = v65; /*0x144af22e8*/
  *(_OWORD *)&v60[8] = v64; /*0x144af22f5*/
  v22 = (unsigned int)(v21 >> 5); /*0x144af2303*/
  v23 = v21 & 0xFFFFFFE0; /*0x144af2307*/
  v68 = *(_OWORD *)&_mm_unpackhi_pd(*(__m128d *)&v60[24], *(__m128d *)&v60[24]); /*0x144af230f*/
  LODWORD(v65) = -1 << (v21 & 0x1F); /*0x144af2314*/
  DWORD1(v65) = v21; /*0x144af2318*/
  v66 = *(_OWORD *)v60; /*0x144af231f*/
  for ( i = *(_OWORD *)&v60[16]; ; sub_1411AD0E0((char *)&v66 + 8, 10LL * SHIDWORD(i), v22, v23) )
  {
    result = SHIDWORD(i); /*0x144af23a0*/
    if ( HIDWORD(i) == DWORD1(v65) && (_QWORD)i == a1 + 3256 && (_QWORD)v66 == a1 + 3240 ) /*0x144af23b5*/
      break; /*0x144af23b5*/
    if ( *(_DWORD *)(*(_QWORD *)v66 + 80LL * SHIDWORD(i)) > *(_DWORD *)(a1 + 3224) )
    {
      sub_1411E56A0(&v64, L"RESYNC: gap in action IDs", v22, v23);
      sub_144AFD0C0(a1, &v64, 0LL); /*0x144af2a2c*/
      return sub_144A92870(a1); /*0x144af2a34*/
    }
    DWORD2(i) &= ~HIDWORD(v66); /*0x144af23dd*/
  }
  return result; /*0x144af2a00*/
}
