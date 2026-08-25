// 反编译原文摘录，未加工。地址：0x144b05910（ResetVariables_Impl）和 0x144b05bc0
// （ResetVariablesForResync_Impl），模块 kards-Win64-Shipping.exe。
// evidence/bUseTurnSwitchValidation.md 引用这两个函数作为"排除 bUseTurnSwitchValidation
// 赋值点"三条证据链之一（"两者都会清零/重置一大堆字段...但都不触碰 0x7A8"），此前该文档只有一句概括，
// 完整原文见本文件。

// ==== 0x144b05910  MatchControllerV2_ResetVariables_Impl ====
// Native impl for ResetVariables(bool). Resets a large block of match-controller state: action counter (+3228), cached match-info pointers (+3160/+3168/+3200), releases a refcounted object (+3392 area, via sub_14122A770 + manual refcount teardown -- shape matches TSharedPtr/UObject ref release), clears a dynamic array (sub_1411EEA70/sub_1411ACD70 free+realloc pattern) at +3064/+3072/+3076, clears side/mulligan-status words at +3112/+3320, destructs+frees the +3128 action-array (ExecParam_DestructArrayElements_Stride40_Offset16, same field this array uses in EnterAILobby_Impl), frees an FString at +3144, conditionally clears +3081 (state) if a2 is set, resets an FString at +1992/+2000, calls sub_144A91960 on a cached sub-object (+3432 cache, offset 2120) with +1968, rebuilds the action-log hash table at +3240 (sub_1416B78E0/sub_144A91ED0/sub_144B02F20 -- same rehash helpers used from MatchControllerV2_GetNextAction_Impl), frees the per-side counters array at +3456/+3464/+3468 (same fields grown in GetNextAction_...
__int64 __fastcall MatchControllerV2_ResetVariables_Impl(AMatchControllerV2_Layout *a1, char a2)
{
  void **p_PendingHttpRequestObj; // rcx
  __int64 v5; // rbx
  __int64 v6; // r8
  __int64 *p_Field3144; // rbx
  __int64 *p_BaseUrlA; // rbx
  __int64 v9; // rcx
  __int64 v10; // rdx
  __int64 v11; // r8
  void **p_ActionLogTablePtr; // rcx
  __int64 v13; // r8
  __int64 result; // rax
  __int64 v15; // [rsp+30h] [rbp-38h] BYREF
  __int64 v16; // [rsp+38h] [rbp-30h]
  __int128 v17; // [rsp+40h] [rbp-28h] BYREF
  char v18; // [rsp+50h] [rbp-18h] BYREF

  a1->ActionCounter3228 = 0; /*0x144b05928*/
  a1->Timestamp3168 = 0.0; /*0x144b05934*/
  a1->Timestamp3160 = 0.0; /*0x144b0593e*/
  p_PendingHttpRequestObj = &a1->PendingHttpRequestObj; /*0x144b05948*/
  v17 = 0LL; /*0x144b05952*/
  if ( p_PendingHttpRequestObj != (void **)&v17 ) /*0x144b0595b*/
  {
    *p_PendingHttpRequestObj = 0LL; /*0x144b0595d*/
    sub_14122A770(p_PendingHttpRequestObj + 1, (char *)&v17 + 8); /*0x144b05969*/
  }
  if ( *((_QWORD *)&v17 + 1) ) /*0x144b05976*/
  {
    if ( _InterlockedExchangeAdd((volatile signed __int32 *)(*((_QWORD *)&v17 + 1) + 8LL), 0xFFFFFFFF) == 1 ) /*0x144b0598c*/
    {
      v5 = *((_QWORD *)&v17 + 1); /*0x144b0598e*/
      (***((void (__fastcall ****)(_QWORD))&v17 + 1))(*((_QWORD *)&v17 + 1)); /*0x144b05999*/
      if ( _InterlockedExchangeAdd((volatile signed __int32 *)(v5 + 12), 0xFFFFFFFF) == 1 ) /*0x144b059a3*/
        (*(void (__fastcall **)(_QWORD, __int64))(**((_QWORD **)&v17 + 1) + 8LL))(*((_QWORD *)&v17 + 1), 1LL); /*0x144b059af*/
    }
  }
  a1->Ptr3200 = 0LL; /*0x144b059b7*/
  sub_1411EEA70(a1->PendingActionQueue_Data, (unsigned int)a1->PendingActionQueue_Num); /*0x144b059cb*/
  a1->PendingActionQueue_Num = 0; /*0x144b059d7*/
  if ( a1->PendingActionQueue_Max ) /*0x144b059d0*/
    sub_1411ACD70(24, 8, 0, (_DWORD)a1 + 3064, 0, (__int64)&a1->PendingActionQueue_Max); /*0x144b059fe*/
  *(_WORD *)&a1->bFlag3112 = 0; /*0x144b05a03*/
  *(_WORD *)&a1->OwnSide = 0; /*0x144b05a0b*/
  ExecParam_DestructArrayElements_Stride40_Offset16((__int64 *)a1->DeckArray_Data, a1->DeckArray_Num); /*0x144b05a20*/
  a1->DeckArray_Num = 0; /*0x144b05a2c*/
  if ( a1->DeckArray_Max ) /*0x144b05a25*/
    sub_1411ACD70(40, 8, 0, (_DWORD)a1 + 3128, 0, (__int64)&a1->DeckArray_Max); /*0x144b05a53*/
  p_Field3144 = (__int64 *)&a1->Field3144; /*0x144b05a58*/
  if ( &a1->Field3144 != (FString *)&v18 ) /*0x144b05a67*/
  {
    if ( *p_Field3144 ) /*0x144b05a69*/
      FMemory_Free_Wrapper(*p_Field3144); /*0x144b05a71*/
    *p_Field3144 = 0LL; /*0x144b05a76*/
    *(_QWORD *)&a1->Field3144.Num = 0LL; /*0x144b05a79*/
  }
  if ( a2 ) /*0x144b05a85*/
    a1->State = 0; /*0x144b05a87*/
  sub_1411CE0F0((__int64)&v15, (const __m128i *)Buf2, v6); /*0x144b05a9a*/
  p_BaseUrlA = (__int64 *)&a1->BaseUrlA; /*0x144b05aa4*/
  if ( &a1->BaseUrlA == (FString *)&v15 ) /*0x144b05aae*/
  {
    v9 = v15; /*0x144b05ae2*/
  }
  else
  {
    if ( *p_BaseUrlA ) /*0x144b05ab0*/
      FMemory_Free_Wrapper(*p_BaseUrlA); /*0x144b05ab8*/
    v9 = 0LL; /*0x144b05ac2*/
    *p_BaseUrlA = v15; /*0x144b05ac5*/
    *(_QWORD *)&a1->BaseUrlA.Num = v16; /*0x144b05acc*/
    v16 = 0LL; /*0x144b05ad6*/
    v15 = 0LL; /*0x144b05adb*/
  }
  if ( v9 ) /*0x144b05aea*/
    FMemory_Free_Wrapper(v9); /*0x144b05aec*/
  sub_144A91960((char *)a1->CachedMatchServicePtr + 2120, &a1->Field1968); /*0x144b05b06*/
  p_ActionLogTablePtr = &a1->ActionLogTablePtr; /*0x144b05b16*/
  if ( a1->ActionLogHashSize <= 1 ) /*0x144b05b19*/
  {
    sub_1416B78E0(p_ActionLogTablePtr, v10, v11); /*0x144b05b33*/
    sub_144A91ED0(&a1->ActionLogTablePtr, 0LL, v13); /*0x144b05b3d*/
  }
  else
  {
    sub_144A91ED0(p_ActionLogTablePtr, 0LL, v11); /*0x144b05b1d*/
    a1->ActionLogHashSize = 1; /*0x144b05b25*/
    sub_144B02F20(&a1->ActionLogTablePtr); /*0x144b05b2c*/
  }
  sub_144A6F780(a1->PerSideCounterArray_Data, (unsigned int)a1->PerSideCounterArray_Num); /*0x144b05b4f*/
  a1->PerSideCounterArray_Num = 0; /*0x144b05b5b*/
  if ( a1->PerSideCounterArray_Max ) /*0x144b05b54*/
    sub_1411ACD70(64, 8, 0, (_DWORD)a1 + 3456, 0, (__int64)&a1->PerSideCounterArray_Max); /*0x144b05b82*/
  *(_WORD *)&a1->Flag3236 = 0; /*0x144b05b8a*/
  a1->Field3220 = 0; /*0x144b05b92*/
  result = sub_144A928A0(a1); /*0x144b05b9a*/
  a1->Mode = 0; /*0x144b05ba4*/
  a1->bFlag3085 = 0; /*0x144b05baf*/
  return result; /*0x144b05b9f*/
}

// ==== 0x144b05bc0  MatchControllerV2_ResetVariablesForResync_Impl ====
// Native impl for execResetVariablesForResync -- a lighter-weight variant of MatchControllerV2_ResetVariables_Impl: resets action counter (+3228), releases the +3392 pending-request handle (same refcount-release shape), clears the +3064/+3072/+3076 dynamic array, resets active-side (+3321) and action id (+3224=1), rebuilds the action-log hash table (+3240, same sub_1416B78E0/sub_144A91ED0/sub_144B02F20 rehash helpers), and sets +680/+1963=1 (reconnecting/resync flags) instead of fully clearing +3081/+3144/+1992 like the full ResetVariables does. Confirms +680 is the 'IsReconnecting' flag (matches SetIsReconecting_Impl and IsReconnectMatch_Impl's first output).
__int64 __fastcall MatchControllerV2_ResetVariablesForResync_Impl(AMatchControllerV2_Layout *a1)
{
  void **p_PendingHttpRequestObj; // rcx
  __int64 v3; // rbx
  __int64 v4; // rdx
  __int64 v5; // r8
  void **p_ActionLogTablePtr; // rcx
  __int64 result; // rax
  __int64 v8; // r8
  __int128 v9; // [rsp+30h] [rbp-18h] BYREF

  a1->ActionCounter3228 = 0; /*0x144b05bd9*/
  a1->Timestamp3168 = 0.0; /*0x144b05be2*/
  a1->Timestamp3160 = 0.0; /*0x144b05be9*/
  p_PendingHttpRequestObj = &a1->PendingHttpRequestObj; /*0x144b05bf0*/
  v9 = 0LL; /*0x144b05bf7*/
  if ( p_PendingHttpRequestObj != (void **)&v9 ) /*0x144b05c00*/
  {
    *p_PendingHttpRequestObj = 0LL; /*0x144b05c02*/
    sub_14122A770(p_PendingHttpRequestObj + 1, (char *)&v9 + 8); /*0x144b05c0e*/
  }
  if ( *((_QWORD *)&v9 + 1) ) /*0x144b05c1b*/
  {
    if ( _InterlockedExchangeAdd((volatile signed __int32 *)(*((_QWORD *)&v9 + 1) + 8LL), 0xFFFFFFFF) == 1 ) /*0x144b05c31*/
    {
      v3 = *((_QWORD *)&v9 + 1); /*0x144b05c33*/
      (***((void (__fastcall ****)(_QWORD))&v9 + 1))(*((_QWORD *)&v9 + 1)); /*0x144b05c3e*/
      if ( _InterlockedExchangeAdd((volatile signed __int32 *)(v3 + 12), 0xFFFFFFFF) == 1 ) /*0x144b05c48*/
        (*(void (__fastcall **)(_QWORD, __int64))(**((_QWORD **)&v9 + 1) + 8LL))(*((_QWORD *)&v9 + 1), 1LL); /*0x144b05c54*/
    }
  }
  a1->Ptr3200 = 0LL; /*0x144b05c5c*/
  sub_1411EEA70(a1->PendingActionQueue_Data, (unsigned int)a1->PendingActionQueue_Num); /*0x144b05c70*/
  a1->PendingActionQueue_Num = 0; /*0x144b05c7c*/
  if ( a1->PendingActionQueue_Max ) /*0x144b05c75*/
    sub_1411ACD70(24, 8, 0, (_DWORD)a1 + 3064, 0, (__int64)&a1->PendingActionQueue_Max); /*0x144b05ca0*/
  a1->ActiveSide = 0; /*0x144b05cac*/
  p_ActionLogTablePtr = &a1->ActionLogTablePtr; /*0x144b05cb8*/
  a1->CurrentActionId = 1; /*0x144b05cbb*/
  if ( a1->ActionLogHashSize <= 1 ) /*0x144b05cc9*/
  {
    sub_1416B78E0(p_ActionLogTablePtr, v4, v5); /*0x144b05ce3*/
    result = sub_144A91ED0(&a1->ActionLogTablePtr, 0LL, v8); /*0x144b05ced*/
  }
  else
  {
    sub_144A91ED0(p_ActionLogTablePtr, 0LL, v5); /*0x144b05ccd*/
    a1->ActionLogHashSize = 1; /*0x144b05cd5*/
    result = sub_144B02F20(&a1->ActionLogTablePtr); /*0x144b05cdc*/
  }
  a1->Flag3237 = 0; /*0x144b05cf7*/
  a1->Field3220 = 0; /*0x144b05cfe*/
  a1->bIsReconnecting = 1; /*0x144b05d07*/
  a1->bResyncInProgress = 1; /*0x144b05d0e*/
  return result; /*0x144b05cf2*/
}
