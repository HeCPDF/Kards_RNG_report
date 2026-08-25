// 反编译原文摘录，未加工。地址：0x144ac6090，模块 kards-Win64-Shipping.exe。
// 符号名 MatchController_OnActionsResponse_ProcessTick_A 是分析过程中人工赋予的推测名
// （根据函数体内解析的 JSON 字面量 "actions"/"ActionEndMatch"/"mulligan_done"/"running"/"finished"
// 等推断，其真实签名 (ClosureCtx, HttpResponseObj) 未经逐字节验证，函数体本身也未逐段复核）。
// 这是 /actions 轮询请求的 HTTP 响应回调，本文件只截取跟 CurrentActionId（this+3224/0xC98）
// 直接相关的循环段，供 evidence/CurrentActionId-increment-logic.md「第二个独立写入点」一节引用；
// 完整反编译产物（含未逐段复核的连接状态机部分）见下方全文。
//
// 关键片段（数组处理循环内，处理每一条轮询回来的已确认动作）：
//
//   if ( v88 <= *(_DWORD *)(*(_QWORD *)ClosureCtx + 3224LL) )   // v88 = 这条动作自带的 action_id
//   {
//     if ( !(unsigned int)FString_EqualsIgnoreCase_Maybe(v27, "ActionEndMatch") )
//     {
//       if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 1960LL) )
//       {
//         *(_DWORD *)(*(_QWORD *)ClosureCtx + 3224LL) = v88;   // 直接覆写 CurrentActionId
//         v28 = *(_QWORD *)(*(_QWORD *)ClosureCtx + 3408LL);
//         if ( v28 )
//           PendingHttpRequest_CancelOrRelease(v28);
//       }
//     }
//   }
//   sub_144AA2180(*(_QWORD *)ClosureCtx + 3240LL, &v88, &v88);   // 登记进动作日志哈希表
//
// 完整函数体（IDA 反编译全文，未加工，含未复核部分）见文档末尾。

// === 完整反编译全文 ===
__int64 __fastcall MatchController_OnActionsResponse_ProcessTick_A(void *ClosureCtx, void *HttpResponseObj)
{
  __int64 result; // rax
  __int128 *v4; // rcx
  __int64 v6; // rbx
  __int64 v7; // rdi
  unsigned int v8; // ebx
  __int64 v9; // rax
  const wchar_t *v10; // r13
  const wchar_t *v11; // rdx
  __int64 v12; // r8
  __int64 v13; // r8
  __int64 v14; // r8
  __int64 *v15; // rbx
  unsigned int v16; // edi
  __int64 v17; // r14
  int v18; // r9d
  const wchar_t *v19; // rdx
  int *v20; // r12
  int *v21; // rbx
  int v22; // eax
  __int64 v23; // r14
  int v24; // edi
  int v25; // edi
  __int64 v26; // r14
  unsigned __int16 *v27; // rcx
  __int64 v28; // rcx
  __int64 v29; // rax
  const __m128i *v30; // rdi
  __int64 v31; // rbx
  const void *v32; // r14
  __int64 v33; // rdx
  int v34; // eax
  __int64 v35; // rdx
  __int64 v36; // r8
  unsigned __int16 *v37; // rcx
  __int64 v38; // r8
  const __m128i *v39; // rdx
  __int64 v40; // rbx
  __int64 v41; // rax
  __int64 v42; // rax
  __int64 v43; // rbx
  const void *v44; // r14
  __int64 v45; // rdx
  int v46; // eax
  __int64 v47; // rdx
  __int64 v48; // r8
  unsigned __int16 *v49; // rcx
  __int64 v50; // r8
  __int64 v51; // rbx
  __int64 v52; // rax
  unsigned __int16 *v53; // rcx
  __int64 v54; // rbx
  unsigned __int16 *v55; // rcx
  int v56; // eax
  __int64 v57; // rbx
  __int64 v58; // rcx
  __int64 v59; // rbx
  __int64 v60; // rcx
  __int64 v61; // rdi
  __int64 v62; // rbx
  __int64 v63; // rcx
  __int64 v64; // rdi
  __int64 v65; // rbx
  __int64 v66; // rbx
  __int64 v67; // rax
  __int64 v68; // rax
  __int64 v69; // rcx
  __int64 v70; // rbx
  double *v71; // rax
  double v72; // xmm1_8
  AMatchControllerV2_Layout *v73; // rcx
  __int64 v74; // rbx
  __int64 v75; // rbx
  volatile signed __int32 *v76; // rbx
  volatile signed __int32 *v77; // rbx
  int *v78; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v79; // [rsp+48h] [rbp-B8h]
  void *v80; // [rsp+50h] [rbp-B0h] BYREF
  int v81; // [rsp+58h] [rbp-A8h]
  int v82; // [rsp+5Ch] [rbp-A4h] BYREF
  void *v83; // [rsp+60h] [rbp-A0h] BYREF
  int v84; // [rsp+68h] [rbp-98h]
  int v85; // [rsp+6Ch] [rbp-94h] BYREF
  const wchar_t *v86; // [rsp+70h] [rbp-90h] BYREF
  int v87; // [rsp+78h] [rbp-88h]
  int v88; // [rsp+80h] [rbp-80h] BYREF
  unsigned __int16 *v89; // [rsp+88h] [rbp-78h] BYREF
  int v90; // [rsp+90h] [rbp-70h]
  int v91; // [rsp+98h] [rbp-68h]
  _QWORD *v92; // [rsp+A0h] [rbp-60h] BYREF
  int v93; // [rsp+A8h] [rbp-58h]
  int v94; // [rsp+ACh] [rbp-54h] BYREF
  __int64 v95; // [rsp+B0h] [rbp-50h] BYREF
  int v96; // [rsp+B8h] [rbp-48h]
  int v97; // [rsp+BCh] [rbp-44h] BYREF
  __int128 v98; // [rsp+C0h] [rbp-40h] BYREF
  __int128 v99; // [rsp+D0h] [rbp-30h] BYREF
  char v100[8]; // [rsp+E0h] [rbp-20h] BYREF
  volatile signed __int32 *v101; // [rsp+E8h] [rbp-18h]
  FMatchSideInfo out; // [rsp+F0h] [rbp-10h] BYREF
  __int64 v103[2]; // [rsp+130h] [rbp+30h] BYREF
  __int64 v104[2]; // [rsp+140h] [rbp+40h] BYREF
  __int64 v105; // [rsp+150h] [rbp+50h] BYREF
  __m128i si128; // [rsp+158h] [rbp+58h]
  __m128i v107; // [rsp+168h] [rbp+68h]
  __int64 v108; // [rsp+178h] [rbp+78h]
  __m128i v109; // [rsp+180h] [rbp+80h]
  __int64 v110; // [rsp+190h] [rbp+90h]
  int v111; // [rsp+198h] [rbp+98h]
  int v112; // [rsp+19Ch] [rbp+9Ch]
  __m128i v113; // [rsp+1A0h] [rbp+A0h]
  int v114; // [rsp+1B0h] [rbp+B0h]
  int v115; // [rsp+1B4h] [rbp+B4h]
  __int64 v116; // [rsp+1B8h] [rbp+B8h]
  __int64 v117; // [rsp+1C0h] [rbp+C0h] BYREF
  _BYTE v118[16]; // [rsp+1D0h] [rbp+D0h] BYREF
  __int64 v119; // [rsp+1E0h] [rbp+E0h] BYREF
  __int64 v120; // [rsp+1F0h] [rbp+F0h] BYREF
  _BYTE v121[16]; // [rsp+200h] [rbp+100h] BYREF
  _BYTE v122[16]; // [rsp+210h] [rbp+110h] BYREF
  _BYTE v123[16]; // [rsp+220h] [rbp+120h] BYREF
  _BYTE v124[64]; // [rsp+230h] [rbp+130h] BYREF
  __int64 v125; // [rsp+270h] [rbp+170h]
  int v126; // [rsp+278h] [rbp+178h]
  __int64 v127; // [rsp+2B8h] [rbp+1B8h]
  int v128; // [rsp+2C0h] [rbp+1C0h]
  __int64 v129; // [rsp+2C8h] [rbp+1C8h]
  int v130; // [rsp+2D0h] [rbp+1D0h]
  __int64 v131; // [rsp+2D8h] [rbp+1D8h] BYREF
  unsigned int v132; // [rsp+2E0h] [rbp+1E0h]
  __int16 v133; // [rsp+330h] [rbp+230h]
  char v134[16]; // [rsp+340h] [rbp+240h] BYREF
  char v135[16]; // [rsp+350h] [rbp+250h] BYREF
  char v136[256]; // [rsp+360h] [rbp+260h] BYREF
  char v137[112]; // [rsp+460h] [rbp+360h] BYREF
  __int16 v138; // [rsp+520h] [rbp+420h] BYREF
  LARGE_INTEGER PerformanceCount; // [rsp+528h] [rbp+428h] BYREF

  result = (__int64)&v98; /*0x144ac60a9*/
  v4 = (__int128 *)(*(_QWORD *)ClosureCtx + 3392LL); /*0x144ac60b3*/
  v98 = 0LL; /*0x144ac60bd*/
  if ( v4 != &v98 ) /*0x144ac60c5*/
  {
    *(_QWORD *)v4 = 0LL; /*0x144ac60c7*/
    result = sub_14122A770((char *)v4 + 8, (char *)&v98 + 8); /*0x144ac60d6*/
  }
  if ( *((_QWORD *)&v98 + 1) ) /*0x144ac60f0*/
  {
    result = (unsigned int)_InterlockedExchangeAdd((volatile signed __int32 *)(*((_QWORD *)&v98 + 1) + 8LL), 0xFFFFFFFF); /*0x144ac60f5*/
    if ( (_DWORD)result == 1 ) /*0x144ac60fd*/
    {
      v6 = *((_QWORD *)&v98 + 1); /*0x144ac60ff*/
      (***((void (__fastcall ****)(_QWORD))&v98 + 1))(*((_QWORD *)&v98 + 1)); /*0x144ac6109*/
      result = (unsigned int)_InterlockedExchangeAdd((volatile signed __int32 *)(v6 + 12), 0xFFFFFFFF); /*0x144ac610e*/
      if ( (_DWORD)result == 1 ) /*0x144ac6116*/
        result = (*(__int64 (__fastcall **)(_QWORD, __int64))(**((_QWORD **)&v98 + 1) + 8LL))( /*0x144ac6123*/
                   *((_QWORD *)&v98 + 1),
                   1LL);
    }
  }
  if ( *((_BYTE *)HttpResponseObj + 32) ) /*0x144ac6126*/
  {
    if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 3220LL) ) /*0x144ac614c*/
    {
      *(_BYTE *)(*(_QWORD *)ClosureCtx + 3220LL) = 0; /*0x144ac6155*/
      sub_144A92690(*(_QWORD *)ClosureCtx); /*0x144ac615f*/
    }
    v7 = *(_QWORD *)ClosureCtx; /*0x144ac6164*/
    v8 = *(_DWORD *)(*(_QWORD *)(*(_QWORD *)ClosureCtx + 3432LL) + 2180LL); /*0x144ac6179*/
    v9 = (*(__int64 (__fastcall **)(_QWORD, __int64 *))(**((_QWORD **)HttpResponseObj + 2) + 96LL))( /*0x144ac6182*/
           *((_QWORD *)HttpResponseObj + 2),
           &v117);
    sub_144AE2A80(v7, &v86, v9, v8); /*0x144ac6193*/
    if ( v117 ) /*0x144ac61a2*/
      FMemory_Free_Wrapper(v117); /*0x144ac61a4*/
    QueryPerformanceCounter(&PerformanceCount); /*0x144ac61b0*/
    *(double *)(*(_QWORD *)ClosureCtx + 3168LL) = (double)(int)PerformanceCount.LowPart * *(double *)&qword_1490D1670 /*0x144ac61dc*/
                                                + 16777216.0;
    sub_144A90FA0(v124); /*0x144ac61e4*/
    v10 = &chText; /*0x144ac61ee*/
    v11 = &chText; /*0x144ac61f5*/
    v133 = 1; /*0x144ac61f8*/
    if ( v87 ) /*0x144ac6201*/
      v11 = v86; /*0x144ac6201*/
    sub_1411CE2F0(v103, v11); /*0x144ac620b*/
    sub_144AAE2A0((unsigned int)v103, (unsigned int)v124, 0, 0, 0, 0LL, 0LL); /*0x144ac6232*/
    if ( v103[0] ) /*0x144ac623e*/
      FMemory_Free_Wrapper(v103[0]); /*0x144ac6240*/
    v12 = (unsigned int)(v126 - 1); /*0x144ac6255*/
    if ( !v126 ) /*0x144ac625b*/
      v12 = 0LL; /*0x144ac625d*/
    sub_1411D2940(*(_QWORD *)ClosureCtx + 2032LL, v125, v12); /*0x144ac6267*/
    if ( v128 ) /*0x144ac6280*/
      v13 = (unsigned int)(v128 - 1); /*0x144ac6282*/
    else
      v13 = 0LL; /*0x144ac6287*/
    sub_1411D2940(*(_QWORD *)ClosureCtx + 2104LL, v127, v13); /*0x144ac6291*/
    if ( v130 ) /*0x144ac62aa*/
      v14 = (unsigned int)(v130 - 1); /*0x144ac62ac*/
    else
      v14 = 0LL; /*0x144ac62b1*/
    sub_1411D2940(*(_QWORD *)ClosureCtx + 2120LL, v129, v14); /*0x144ac62bb*/
    v15 = (__int64 *)(*(_QWORD *)ClosureCtx + 2136LL); /*0x144ac62ca*/
    if ( v15 != &v131 ) /*0x144ac62d4*/
    {
      sub_144A6F7F0(*v15, *(unsigned int *)(*(_QWORD *)ClosureCtx + 2144LL)); /*0x144ac62dc*/
      v16 = v132; /*0x144ac62e1*/
      v17 = v131; /*0x144ac62eb*/
      v18 = *((_DWORD *)v15 + 3); /*0x144ac62f2*/
      *((_DWORD *)v15 + 2) = v132; /*0x144ac62f5*/
      if ( v16 || v18 ) /*0x144ac62ff*/
      {
        TArray_ResizeAllocation(0xE8u, 8, v16, v18, (__int64)v15, v16, (int *)v15 + 3); /*0x144ac6322*/
        sub_144A6F290(*v15, v17, v16); /*0x144ac6330*/
      }
      else
      {
        *((_DWORD *)v15 + 3) = 0; /*0x144ac6303*/
      }
    }
    v19 = &chText; /*0x144ac6343*/
    if ( v87 ) /*0x144ac6346*/
      v19 = v86; /*0x144ac6346*/
    v99 = 0LL; /*0x144ac634c*/
    sub_1411CE2F0(v104, v19); /*0x144ac6351*/
    sub_14451C3A0(&v99, v104); /*0x144ac635e*/
    if ( v104[0] ) /*0x144ac636a*/
      FMemory_Free_Wrapper(v104[0]); /*0x144ac636c*/
    sub_14451AEC0(&v99, v100, L"actions"); /*0x144ac6380*/
    v78 = 0LL; /*0x144ac638a*/
    v79 = 0LL; /*0x144ac6393*/
    v138 = 257; /*0x144ac63a3*/
    sub_144AB3CE0(&v138, v100, &v78); /*0x144ac63ac*/
    v20 = &v78[16 * (__int64)(int)v79]; /*0x144ac63bf*/
    if ( v78 != v20 ) /*0x144ac63c5*/
    {
      v21 = v78 + 14; /*0x144ac63cb*/
      do /*0x144ac6542*/
      {
        v88 = *(v21 - 14); /*0x144ac63db*/
        sub_1411CDDD0(&v89, v21 - 12); /*0x144ac63de*/
        v22 = *(v21 - 8); /*0x144ac63e3*/
        v23 = *((_QWORD *)v21 - 3); /*0x144ac63e6*/
        v92 = 0LL; /*0x144ac63ea*/
        v24 = *(v21 - 4); /*0x144ac63ee*/
        v91 = v22; /*0x144ac63f1*/
        v93 = v24; /*0x144ac63f4*/
        if ( v24 ) /*0x144ac63f9*/
        {
          TArray_ResizeAllocation(0x28u, 8, v24, 0, (__int64)&v92, v24, &v94); /*0x144ac6423*/
          ExecParam_CopyConstructArrayElements_Stride40((__int64)v92, v23, v24); /*0x144ac6432*/
        }
        else
        {
          v94 = 0; /*0x144ac63fb*/
        }
        v25 = *v21; /*0x144ac6437*/
        v26 = *((_QWORD *)v21 - 1); /*0x144ac6439*/
        v95 = 0LL; /*0x144ac643d*/
        v96 = v25; /*0x144ac6445*/
        if ( v25 ) /*0x144ac644a*/
        {
          TArray_ResizeAllocation(0x20u, 8, v25, 0, (__int64)&v95, v25, &v97); /*0x144ac6476*/
          ExecParam_CopyConstructNestedTArray_Stride32(v95, v26, v25); /*0x144ac6485*/
        }
        else
        {
          v97 = 0; /*0x144ac644e*/
        }
        if ( v88 <= *(_DWORD *)(*(_QWORD *)ClosureCtx + 3224LL) ) /*0x144ac6498*/
        {
          v27 = (unsigned __int16 *)&chText; /*0x144ac64a5*/
          if ( v90 ) /*0x144ac64a8*/
            v27 = v89; /*0x144ac64a8*/
          if ( !(unsigned int)FString_EqualsIgnoreCase_Maybe(v27, "ActionEndMatch") ) /*0x144ac64ad*/
          {
            if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 1960LL) ) /*0x144ac64b9*/
            {
              *(_DWORD *)(*(_QWORD *)ClosureCtx + 3224LL) = v88; /*0x144ac64c4*/
              v28 = *(_QWORD *)(*(_QWORD *)ClosureCtx + 3408LL); /*0x144ac64cd*/
              if ( v28 ) /*0x144ac64d7*/
                PendingHttpRequest_CancelOrRelease(v28); /*0x144ac64d9*/
            }
          }
        }
        sub_144AA2180(*(_QWORD *)ClosureCtx + 3240LL, &v88, &v88); /*0x144ac64f0*/
        ExecParam_DestructArrayOfStructPairs_Stride32(v95, v96); /*0x144ac64fc*/
        if ( v95 ) /*0x144ac6508*/
          FMemory_Free_Wrapper(v95); /*0x144ac650a*/
        ExecParam_DestructArrayElements_Stride40(v92, v93); /*0x144ac6516*/
        if ( v92 ) /*0x144ac6522*/
          FMemory_Free_Wrapper((__int64)v92); /*0x144ac6524*/
        if ( v89 ) /*0x144ac6530*/
          FMemory_Free_Wrapper((__int64)v89); /*0x144ac6532*/
        v21 += 16; /*0x144ac6537*/
      }
      while ( v21 - 14 != v20 ); /*0x144ac6542*/
    }
    v29 = *(_QWORD *)ClosureCtx; /*0x144ac6548*/
    v30 = (const __m128i *)"right"; /*0x144ac654b*/
    if ( !*(_BYTE *)(*(_QWORD *)ClosureCtx + 3236LL) ) /*0x144ac6555*/
    {
      v80 = 0LL; /*0x144ac6562*/
      v31 = *(int *)(v29 + 2112); /*0x144ac6567*/
      v32 = *(const void **)(v29 + 2104); /*0x144ac656e*/
      v81 = v31; /*0x144ac6575*/
      if ( (_DWORD)v31 ) /*0x144ac657b*/
      {
        TArray_ResizeAllocation(2u, 2, v31, 0, (__int64)&v80, v31, &v82); /*0x144ac65a9*/
        memcpy(v80, v32, 2 * v31); /*0x144ac65bc*/
      }
      else
      {
        v82 = 0; /*0x144ac657d*/
      }
      v33 = *(_QWORD *)ClosureCtx; /*0x144ac65c1*/
      if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 3320LL) == 1 ) /*0x144ac65cb*/
      {
        v34 = *(_DWORD *)(v33 + 2128); /*0x144ac65cd*/
        v35 = *(_QWORD *)(v33 + 2120); /*0x144ac65d8*/
        v36 = (unsigned int)(v34 - 1); /*0x144ac65e1*/
        if ( !v34 ) /*0x144ac65e5*/
          v36 = 0LL; /*0x144ac65e5*/
        sub_1411D2940(&v80, v35, v36); /*0x144ac65e9*/
      }
      v37 = (unsigned __int16 *)&chText; /*0x144ac65fa*/
      if ( v81 ) /*0x144ac65fd*/
        v37 = (unsigned __int16 *)v80; /*0x144ac65fd*/
      if ( !(unsigned int)FString_EqualsIgnoreCase_Maybe(v37, "mulligan_done") ) /*0x144ac6603*/
      {
        v39 = (const __m128i *)"left"; /*0x144ac660f*/
        *(_BYTE *)(*(_QWORD *)ClosureCtx + 3236LL) = 1; /*0x144ac661d*/
        v40 = *(_QWORD *)ClosureCtx; /*0x144ac6624*/
        if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 3320LL) == 1 ) /*0x144ac662e*/
          v39 = (const __m128i *)"right"; /*0x144ac662e*/
        v41 = sub_1411CE0F0((__int64)v134, v39, v38); /*0x144ac6632*/
        MatchControllerV2_GetMulliganResponseForSide_Impl(v40, v41); /*0x144ac663d*/
      }
      if ( v80 ) /*0x144ac664a*/
        FMemory_Free_Wrapper((__int64)v80); /*0x144ac664c*/
    }
    v42 = *(_QWORD *)ClosureCtx; /*0x144ac6651*/
    if ( !*(_BYTE *)(*(_QWORD *)ClosureCtx + 752LL) && !*(_BYTE *)(v42 + 761) ) /*0x144ac6661*/
    {
      v83 = 0LL; /*0x144ac666e*/
      v43 = *(int *)(v42 + 2112); /*0x144ac6673*/
      v44 = *(const void **)(v42 + 2104); /*0x144ac667a*/
      v84 = v43; /*0x144ac6681*/
      if ( (_DWORD)v43 ) /*0x144ac6687*/
      {
        TArray_ResizeAllocation(2u, 2, v43, 0, (__int64)&v83, v43, &v85); /*0x144ac66b5*/
        memcpy(v83, v44, 2 * v43); /*0x144ac66c8*/
      }
      else
      {
        v85 = 0; /*0x144ac6689*/
      }
      v45 = *(_QWORD *)ClosureCtx; /*0x144ac66cd*/
      if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 3320LL) == 2 ) /*0x144ac66d7*/
      {
        v46 = *(_DWORD *)(v45 + 2128); /*0x144ac66d9*/
        v47 = *(_QWORD *)(v45 + 2120); /*0x144ac66e4*/
        v48 = (unsigned int)(v46 - 1); /*0x144ac66ed*/
        if ( !v46 ) /*0x144ac66f1*/
          v48 = 0LL; /*0x144ac66f1*/
        sub_1411D2940(&v83, v47, v48); /*0x144ac66f5*/
      }
      v49 = (unsigned __int16 *)&chText; /*0x144ac6706*/
      if ( v84 ) /*0x144ac6709*/
        v49 = (unsigned __int16 *)v83; /*0x144ac6709*/
      if ( !(unsigned int)FString_EqualsIgnoreCase_Maybe(v49, "mulligan_done") ) /*0x144ac670f*/
      {
        *(_BYTE *)(*(_QWORD *)ClosureCtx + 752LL) = 1; /*0x144ac671b*/
        if ( !*(_BYTE *)(*(_QWORD *)ClosureCtx + 1961LL) ) /*0x144ac6725*/
        {
          sub_144A925D0(*(_QWORD *)ClosureCtx); /*0x144ac672e*/
          v51 = *(_QWORD *)ClosureCtx; /*0x144ac6733*/
          if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 3320LL) == 1 ) /*0x144ac674b*/
            v30 = (const __m128i *)"left"; /*0x144ac674b*/
          v52 = sub_1411CE0F0((__int64)v135, v30, v50); /*0x144ac6752*/
          MatchControllerV2_GetMulliganResponseForSide_Impl(v51, v52); /*0x144ac675d*/
        }
      }
      if ( v83 ) /*0x144ac676a*/
        FMemory_Free_Wrapper((__int64)v83); /*0x144ac676c*/
    }
    if ( (int)v79 > 0 ) /*0x144ac6776*/
      sub_144A91D80(*(_QWORD *)ClosureCtx); /*0x144ac677b*/
    if ( *(_DWORD *)(*(_QWORD *)ClosureCtx + 2040LL) ) /*0x144ac6783*/
      v53 = *(unsigned __int16 **)(*(_QWORD *)ClosureCtx + 2032LL); /*0x144ac678c*/
    else
      v53 = (unsigned __int16 *)&chText; /*0x144ac6795*/
    if ( (unsigned int)FString_EqualsIgnoreCase_Maybe(v53, "running") ) /*0x144ac679f*/
    {
      v54 = *(_QWORD *)ClosureCtx; /*0x144ac67ac*/
      sub_1411EEA70(*(_QWORD *)(*(_QWORD *)ClosureCtx + 3064LL), *(unsigned int *)(*(_QWORD *)ClosureCtx + 3072LL)); /*0x144ac67bc*/
      *(_DWORD *)(v54 + 3072) = 0; /*0x144ac67c8*/
      if ( *(_DWORD *)(v54 + 3076) ) /*0x144ac67cf*/
        sub_1411ACD70(24, 8, 0, v54 + 3064, 0, v54 + 3076); /*0x144ac67ef*/
      *(_BYTE *)(*(_QWORD *)ClosureCtx + 3081LL) = 0; /*0x144ac67f7*/
      if ( *(_DWORD *)(*(_QWORD *)ClosureCtx + 2040LL) ) /*0x144ac6801*/
        v55 = *(unsigned __int16 **)(*(_QWORD *)ClosureCtx + 2032LL); /*0x144ac680a*/
      else
        v55 = (unsigned __int16 *)&chText; /*0x144ac6813*/
      v56 = FString_EqualsIgnoreCase_Maybe(v55, "finished"); /*0x144ac681d*/
      v57 = *(_QWORD *)ClosureCtx; /*0x144ac6822*/
      if ( v56 ) /*0x144ac6827*/
      {
        if ( *(_DWORD *)(v57 + 2040) ) /*0x144ac6836*/
          v10 = *(const wchar_t **)(v57 + 2032); /*0x144ac683f*/
        sub_1411E56A0(v118, L"Match ended unusually with state %s", v10); /*0x144ac6857*/
        sub_144AFD0C0(v57, v118, 0LL); /*0x144ac6869*/
        v58 = *(_QWORD *)ClosureCtx + 2952LL; /*0x144ac6887*/
        si128 = _mm_load_si128((const __m128i *)&xmmword_1471A0C90); /*0x144ac688e*/
        v116 = 0LL; /*0x144ac6893*/
        v109 = si128; /*0x144ac689a*/
        v105 = 0LL; /*0x144ac68a2*/
        v113 = _mm_load_si128((const __m128i *)&xmmword_147079660); /*0x144ac68ae*/
        v108 = 0LL; /*0x144ac68b6*/
        v107 = _mm_load_si128((const __m128i *)&xmmword_1471BF900); /*0x144ac68ba*/
        v110 = -1LL; /*0x144ac68bf*/
        v111 = -1; /*0x144ac68ca*/
        v112 = 0; /*0x144ac68d1*/
        v114 = -1; /*0x144ac68d7*/
        v115 = 0; /*0x144ac68de*/
        sub_144AB9FF0(v58, &v105); /*0x144ac68e5*/
        v59 = v108; /*0x144ac68ea*/
        sub_144A65DE0(v108, v109.m128i_u32[0]); /*0x144ac68f7*/
        if ( v59 ) /*0x144ac68ff*/
          FMemory_Free_Wrapper(v59); /*0x144ac6904*/
        if ( v105 ) /*0x144ac6910*/
          FMemory_Free_Wrapper(v105); /*0x144ac6912*/
        v60 = *(_QWORD *)ClosureCtx; /*0x144ac6917*/
        if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 3320LL) == 1 ) /*0x144ac6921*/
        {
          v61 = sub_14138B420(v60 + 2320, &v119); /*0x144ac6939*/
          v62 = *(_QWORD *)ClosureCtx + 2952LL; /*0x144ac693c*/
          if ( v62 != v61 ) /*0x144ac6946*/
          {
            if ( *(_QWORD *)v62 ) /*0x144ac6948*/
              FMemory_Free_Wrapper(*(_QWORD *)v62); /*0x144ac6950*/
            *(_QWORD *)v62 = *(_QWORD *)v61; /*0x144ac6958*/
            *(_QWORD *)v61 = 0LL; /*0x144ac695b*/
            *(_DWORD *)(v62 + 8) = *(_DWORD *)(v61 + 8); /*0x144ac6961*/
            *(_DWORD *)(v62 + 12) = *(_DWORD *)(v61 + 12); /*0x144ac6967*/
            *(_QWORD *)(v61 + 8) = 0LL; /*0x144ac696a*/
          }
          v63 = v119; /*0x144ac6972*/
        }
        else
        {
          v64 = sub_14138B420(v60 + 2552, &v120); /*0x144ac6991*/
          v65 = *(_QWORD *)ClosureCtx + 2952LL; /*0x144ac6994*/
          if ( v65 != v64 ) /*0x144ac699e*/
          {
            if ( *(_QWORD *)v65 ) /*0x144ac69a0*/
              FMemory_Free_Wrapper(*(_QWORD *)v65); /*0x144ac69a8*/
            *(_QWORD *)v65 = *(_QWORD *)v64; /*0x144ac69b0*/
            *(_QWORD *)v64 = 0LL; /*0x144ac69b3*/
            *(_DWORD *)(v65 + 8) = *(_DWORD *)(v64 + 8); /*0x144ac69b9*/
            *(_DWORD *)(v65 + 12) = *(_DWORD *)(v64 + 12); /*0x144ac69bf*/
            *(_QWORD *)(v64 + 8) = 0LL; /*0x144ac69c2*/
          }
          v63 = v120; /*0x144ac69ca*/
        }
        if ( v63 ) /*0x144ac69d4*/
          FMemory_Free_Wrapper(v63); /*0x144ac69d6*/
        v66 = *(_QWORD *)ClosureCtx; /*0x144ac69db*/
        v67 = sub_144AB7AC0(v137, *(_QWORD *)ClosureCtx + 2952LL); /*0x144ac69ec*/
        sub_144A92460(v66, v67); /*0x144ac69f7*/
        memset(v136, 0, sizeof(v136)); /*0x144ac6a0b*/
        v68 = sub_144A90FA0(v136); /*0x144ac6a17*/
        sub_144ABA1D0(*(_QWORD *)(*(_QWORD *)ClosureCtx + 3432LL) + 2120LL, v68); /*0x144ac6a30*/
        sub_144A70320(v136); /*0x144ac6a3c*/
      }
      else
      {
        sub_144AEAC00(*(_QWORD *)ClosureCtx); /*0x144ac682c*/
      }
LABEL_147:
      sub_144A6F780(v78, (unsigned int)v79); /*0x144ac6c9f*/
      if ( v78 ) /*0x144ac6cb5*/
        FMemory_Free_Wrapper((__int64)v78); /*0x144ac6cb7*/
      v76 = v101; /*0x144ac6cbc*/
      if ( v101 ) /*0x144ac6cc3*/
      {
        if ( _InterlockedExchangeAdd(v101 + 2, 0xFFFFFFFF) == 1 ) /*0x144ac6cd0*/
        {
          (**(void (__fastcall ***)(volatile signed __int32 *))v76)(v76); /*0x144ac6cd8*/
          if ( _InterlockedExchangeAdd(v76 + 3, 0xFFFFFFFF) == 1 ) /*0x144ac6ce5*/
            (*(void (__fastcall **)(volatile signed __int32 *, __int64))(*(_QWORD *)v76 + 8LL))(v76, 1LL); /*0x144ac6cf2*/
        }
      }
      v77 = (volatile signed __int32 *)*((_QWORD *)&v99 + 1); /*0x144ac6cf5*/
      if ( *((_QWORD *)&v99 + 1) ) /*0x144ac6cfc*/
      {
        if ( _InterlockedExchangeAdd((volatile signed __int32 *)(*((_QWORD *)&v99 + 1) + 8LL), 0xFFFFFFFF) == 1 ) /*0x144ac6d09*/
        {
          (**(void (__fastcall ***)(volatile signed __int32 *))v77)(v77); /*0x144ac6d11*/
          if ( _InterlockedExchangeAdd(v77 + 3, 0xFFFFFFFF) == 1 ) /*0x144ac6d1d*/
            (*(void (__fastcall **)(volatile signed __int32 *, __int64))(*(_QWORD *)v77 + 8LL))(v77, 1LL); /*0x144ac6d28*/
        }
      }
      result = sub_144A70320(v124); /*0x144ac6d32*/
      if ( v86 ) /*0x144ac6d3f*/
        return FMemory_Free_Wrapper((__int64)v86); /*0x144ac6d41*/
      return result; /*0x144ac6d41*/
    }
    if ( (_BYTE)v133 /*0x144ac6a76*/
      || (v69 = *(_QWORD *)ClosureCtx,
          *(double *)(*(_QWORD *)ClosureCtx + 3160LL) - 11.0 <= *(double *)(*(_QWORD *)ClosureCtx + 3184LL)) )
    {
      if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 3221LL) ) /*0x144ac6c32*/
      {
        *(_BYTE *)(*(_QWORD *)ClosureCtx + 3237LL) = 0; /*0x144ac6c3b*/
        *(_QWORD *)(*(_QWORD *)ClosureCtx + 3200LL) = 0LL; /*0x144ac6c53*/
        *(_BYTE *)(*(_QWORD *)ClosureCtx + 3221LL) = 0; /*0x144ac6c5d*/
        v75 = *(_QWORD *)ClosureCtx; /*0x144ac6c64*/
        sub_1411E56A0(v123, L"opponent connection issue recovered in time."); /*0x144ac6c67*/
        sub_144AFD0C0(v75, v123, 0LL); /*0x144ac6c79*/
        sub_144A92720(*(_QWORD *)ClosureCtx); /*0x144ac6c81*/
      }
      goto LABEL_145; /*0x144ac6c81*/
    }
    if ( *(double *)(v69 + 3200) == 0.0 ) /*0x144ac6a87*/
      *(_QWORD *)(v69 + 3200) = *(_QWORD *)(v69 + 3168); /*0x144ac6a90*/
    if ( !*(_BYTE *)(*(_QWORD *)ClosureCtx + 3221LL) && !(unsigned __int8)sub_144AF8AA0(*(_QWORD *)ClosureCtx) ) /*0x144ac6aa3*/
    {
      v70 = *(_QWORD *)ClosureCtx; /*0x144ac6aac*/
      if ( *(double *)(*(_QWORD *)ClosureCtx + 3208LL) + 7.0 <= *(double *)(*(_QWORD *)ClosureCtx + 3168LL) ) /*0x144ac6ac7*/
      {
        sub_1411E56A0(v121, L"detecting opponent as having connection issues."); /*0x144ac6ad7*/
        sub_144AFD0C0(v70, v121, 0LL); /*0x144ac6ae9*/
        *(_BYTE *)(*(_QWORD *)ClosureCtx + 3221LL) = 1; /*0x144ac6af1*/
        *(_QWORD *)(*(_QWORD *)ClosureCtx + 3192LL) = *(_QWORD *)(*(_QWORD *)ClosureCtx + 3168LL); /*0x144ac6b02*/
        sub_144A926F0(*(_QWORD *)ClosureCtx); /*0x144ac6b0c*/
        goto LABEL_145; /*0x144ac6b11*/
      }
    }
    if ( !*(_BYTE *)(*(_QWORD *)ClosureCtx + 3237LL) ) /*0x144ac6b19*/
    {
      if ( (unsigned __int8)sub_144AF8AA0(*(_QWORD *)ClosureCtx) ) /*0x144ac6b26*/
        goto LABEL_137; /*0x144ac6b2d*/
      v71 = *(double **)ClosureCtx; /*0x144ac6b2f*/
      if ( *(_BYTE *)(*(_QWORD *)ClosureCtx + 3221LL) ) /*0x144ac6b32*/
      {
        if ( v71[396] - v71[399] <= 30.0 ) /*0x144ac6b53*/
          goto LABEL_145; /*0x144ac6b53*/
LABEL_137:
        v73 = *(AMatchControllerV2_Layout **)ClosureCtx; /*0x144ac6b86*/
        *(__m128i *)&out.Field8.Num = _mm_load_si128((const __m128i *)&xmmword_1471A0C90); /*0x144ac6b95*/
        out.Field0 = -1; /*0x144ac6b9a*/
        out.Field8.Data = 0LL; /*0x144ac6b9e*/
        *(_WORD *)&out.Flag32 = 0; /*0x144ac6ba2*/
        memset(&out._pad34[6], 0, 17); /*0x144ac6ba8*/
        MatchControllerV2_GetOtherSideInfo_Impl(v73, &out); /*0x144ac6bb8*/
        v74 = *(_QWORD *)ClosureCtx; /*0x144ac6bc8*/
        if ( *(_DWORD *)&out._pad34[14] ) /*0x144ac6bd2*/
          v10 = *(const wchar_t **)&out._pad34[6]; /*0x144ac6bd2*/
        sub_1411E56A0(v122, L"opponent has disconnected (status=%s)", v10); /*0x144ac6bda*/
        sub_144AFD0C0(v74, v122, 0LL); /*0x144ac6bec*/
        sub_1435FC330(*(_QWORD *)(*(_QWORD *)ClosureCtx + 3432LL) + 1728LL); /*0x144ac6c02*/
        *(_BYTE *)(*(_QWORD *)ClosureCtx + 3237LL) = 1; /*0x144ac6c0a*/
        if ( *(_QWORD *)&out._pad34[6] ) /*0x144ac6c18*/
          FMemory_Free_Wrapper(*(__int64 *)&out._pad34[6]); /*0x144ac6c1a*/
        if ( out.Field8.Data ) /*0x144ac6c26*/
          FMemory_Free_Wrapper((__int64)out.Field8.Data); /*0x144ac6c28*/
        goto LABEL_145; /*0x144ac6c2d*/
      }
      v72 = v71[400]; /*0x144ac6b5a*/
      if ( v72 > 0.0 && v71[396] - v72 > 60.0 ) /*0x144ac6b80*/
        goto LABEL_137; /*0x144ac6b80*/
    }
LABEL_145:
    if ( HIBYTE(v133) ) /*0x144ac6c95*/
      sub_144A92180(*(_QWORD *)ClosureCtx); /*0x144ac6c9a*/
    goto LABEL_147; /*0x144ac6c9a*/
  }
  return result; /*0x144ac6d5e*/
}
