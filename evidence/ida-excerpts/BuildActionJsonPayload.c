// 反编译原文摘录，未加工。地址：0x144afb900，模块 kards-Win64-Shipping.exe。
// 符号名 MatchController_BuildActionJsonPayload 是分析过程中人工赋予的推测名。
// evidence/two-distinct-action-id-counters.md 全篇引用/描述的核心函数——用于确认提交 JSON
// 里的 action_id 字段来自 Counter3228（this+3228），不是喂给重播种公式的 CurrentActionId
// （this+3224），此前该文档只引用了两条分支各自的伪代码片段，完整原文见本文件。
// 关键地址：
//   0x144afc6b5  分支一（this+1960 为假）：action_id_value = ++*(this+3228)
//   0x144afc32c 起  分支二（this+1960 为真）：先查哈希表判重，再用 this+3224 当前值
//                    写入 JSON、随后自增 this+3224（0x144afc6a0 ++*v56）
//   0x144afc3b1  RESYNC: jsonifyAction invalid action ID（哈希表判重命中时的错误路径）

// MatchController_BuildActionJsonPayload(this, outJson, actionTypeStr, matchDataArray(unused-ish), subActionsArray, extraMatchDataPtr): builds the JSON string later encrypted+POSTed to /matches/v2/<id>/actions. Field order confirmed: action_type, player_id, [match_data if extraMatchDataPtr has text], per-item action_data array, sub_actions array, THEN validate_turn_switch (only if this+1960 flag set, literal '1'), THEN action_id (assigned from DIFFERENT counters depending on the same flag: this+3228 when flag OFF, this+3224 when flag ON), THEN local_subactions:'1' if this+1962 flag set, THEN is_knockout:'1' if action_type=='XActionEndOfTurn' and a trigger-name field at this+2008/2016 == 'knockout_8'. When flag ON, action_id assignment also does a local hash-table lookup (table at this+3296, mask at this+3312, chain via +72 offset per 80-byte entry) against the about-to-be-used counter value BEFORE incrementing -- if found, aborts with client-side error 'RESYNC: jsonifyAction invalid action ID' (calls MatchContr...
FString *__fastcall MatchController_BuildActionJsonPayload(
        AMatchControllerV2 *this,
        FString *outJson,
        FString *actionType,
        TArray_FActionDataEntry *actionData,
        TArray_FSubAction *subActions,
        FString *extraMatchStateJson)
{
  TArray_FSubAction *v6; // r12
  AMatchControllerV2 *v7; // r15
  int v8; // ebx
  __int64 v11; // r8
  __int64 v12; // r8
  __int64 v13; // rdx
  __int64 v14; // r8
  unsigned __int16 *v15; // r13
  unsigned __int16 *Data; // rcx
  __int64 v17; // r8
  FActionDataEntry *v18; // rdi
  __int64 Num; // rax
  FActionDataEntry *v20; // r14
  unsigned __int16 *v21; // rcx
  __int64 v22; // r8
  __int64 IntValue; // rdx
  __int64 v24; // rax
  __int64 *v25; // rcx
  __int64 v26; // r8
  __int64 v27; // rdi
  __int64 v28; // r8
  __int64 v29; // r8
  __int64 v30; // rax
  FSubAction *v31; // r15
  FSubAction *v32; // r12
  __int64 v33; // r8
  __int64 v34; // r8
  __int64 v35; // r8
  __int64 v36; // rdi
  __int64 v37; // r14
  unsigned __int16 *v38; // rcx
  __int64 v39; // r8
  __int64 v40; // rdx
  __int64 v41; // rdx
  __int64 *v42; // rcx
  int v43; // eax
  __int64 v44; // r8
  __int64 v45; // rdi
  int v46; // eax
  __int64 v47; // rcx
  __int64 v48; // r8
  __int64 v49; // rbx
  char v50; // di
  __int64 v51; // rsi
  int v52; // eax
  __int64 v53; // r8
  __int64 v54; // r8
  __int64 v55; // r8
  _DWORD *v56; // rsi
  int v57; // r8d
  char *v58; // rdx
  int v59; // eax
  __int64 v60; // rdx
  __int64 v61; // rbx
  wchar_t *v62; // r14
  FString *v63; // rbx
  __int64 v64; // r8
  __int64 *v65; // r14
  int v67; // ebx
  __int64 v68; // r14
  int v69; // ebx
  __int64 v70; // r14
  __int64 v71; // rdx
  __int64 v72; // r8
  __int64 v73; // r8
  __int64 v74; // rdx
  __int64 v75; // r8
  __int64 v76; // r8
  __int64 *v77; // rbx
  unsigned __int16 *v78; // rcx
  __int64 v79; // r8
  __int64 v80; // r8
  FString *v81; // rdi
  __int64 *v82; // rbx
  __int64 v83; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v84; // [rsp+48h] [rbp-B8h]
  _BYTE v85[4]; // [rsp+50h] [rbp-B0h] BYREF
  int v86; // [rsp+54h] [rbp-ACh] BYREF
  __int64 *v87; // [rsp+58h] [rbp-A8h] BYREF
  __int64 *v88; // [rsp+60h] [rbp-A0h]
  __int64 v89; // [rsp+68h] [rbp-98h] BYREF
  __int64 v90; // [rsp+70h] [rbp-90h] BYREF
  __int64 v91[2]; // [rsp+78h] [rbp-88h] BYREF
  __int64 *v92; // [rsp+88h] [rbp-78h] BYREF
  FString *v93; // [rsp+90h] [rbp-70h]
  __int64 v94[2]; // [rsp+98h] [rbp-68h] BYREF
  __int64 v95[2]; // [rsp+A8h] [rbp-58h] BYREF
  __int64 v96; // [rsp+B8h] [rbp-48h] BYREF
  int v97; // [rsp+C0h] [rbp-40h]
  int v98; // [rsp+C4h] [rbp-3Ch]
  __int64 v99; // [rsp+C8h] [rbp-38h] BYREF
  void *v100; // [rsp+D0h] [rbp-30h] BYREF
  int v101; // [rsp+D8h] [rbp-28h]
  int v102[3]; // [rsp+DCh] [rbp-24h] BYREF
  _QWORD *v103; // [rsp+E8h] [rbp-18h] BYREF
  __m128i si128; // [rsp+F0h] [rbp-10h] BYREF
  int v105; // [rsp+100h] [rbp+0h]
  int v106; // [rsp+104h] [rbp+4h] BYREF
  __int64 v107; // [rsp+108h] [rbp+8h]
  int v108; // [rsp+110h] [rbp+10h]
  __int64 v109[2]; // [rsp+118h] [rbp+18h] BYREF
  __int64 **v110; // [rsp+128h] [rbp+28h] BYREF
  __int64 *v111; // [rsp+130h] [rbp+30h]
  FString *v112; // [rsp+138h] [rbp+38h]
  TArray_FActionDataEntry *v113; // [rsp+140h] [rbp+40h]
  AMatchControllerV2 *v114; // [rsp+148h] [rbp+48h]
  TArray_FSubAction *v115; // [rsp+150h] [rbp+50h]
  FString *v116; // [rsp+158h] [rbp+58h]
  __int64 *v117; // [rsp+160h] [rbp+60h]
  __int64 v118[2]; // [rsp+168h] [rbp+68h] BYREF
  __int64 v119[2]; // [rsp+178h] [rbp+78h] BYREF
  __int64 v120[2]; // [rsp+188h] [rbp+88h] BYREF
  __int64 v121[2]; // [rsp+198h] [rbp+98h] BYREF
  __int64 v122[3]; // [rsp+1A8h] [rbp+A8h] BYREF
  __int64 v123[4]; // [rsp+1C0h] [rbp+C0h] BYREF
  __int64 v124; // [rsp+1E0h] [rbp+E0h]
  int v125; // [rsp+1E8h] [rbp+E8h]
  int v126; // [rsp+1ECh] [rbp+ECh]
  int v127; // [rsp+1F0h] [rbp+F0h]
  int v128; // [rsp+1F4h] [rbp+F4h]
  __int64 v129; // [rsp+200h] [rbp+100h]
  int v130; // [rsp+208h] [rbp+108h]
  __int64 v131[4]; // [rsp+210h] [rbp+110h] BYREF
  __int64 v132; // [rsp+230h] [rbp+130h]
  int v133; // [rsp+238h] [rbp+138h]
  int v134; // [rsp+23Ch] [rbp+13Ch]
  int v135; // [rsp+240h] [rbp+140h]
  int v136; // [rsp+244h] [rbp+144h]
  __int64 v137; // [rsp+250h] [rbp+150h]
  int v138; // [rsp+258h] [rbp+158h]

  v6 = subActions; /*0x144afb92d*/
  v7 = this; /*0x144afb93e*/
  v116 = outJson; /*0x144afb941*/
  v8 = 0; /*0x144afb945*/
  v86 = 0; /*0x144afb948*/
  v114 = this; /*0x144afb953*/
  v131[0] = 0LL; /*0x144afb95e*/
  v131[1] = 0LL; /*0x144afb965*/
  v132 = 0LL; /*0x144afb96f*/
  v133 = 0; /*0x144afb976*/
  v134 = 128; /*0x144afb97d*/
  v135 = -1; /*0x144afb987*/
  v136 = 0; /*0x144afb991*/
  v137 = 0LL; /*0x144afb998*/
  v138 = 0; /*0x144afb99f*/
  v113 = actionData; /*0x144afb9a6*/
  v112 = actionType; /*0x144afb9aa*/
  v115 = subActions; /*0x144afb9ae*/
  v117 = (__int64 *)extraMatchStateJson; /*0x144afb9b2*/
  sub_1411CE0F0((__int64)&v92, (const __m128i *)"\"", (__int64)actionType); /*0x144afb9b6*/
  sub_1411CE0F0((__int64)v94, (const __m128i *)"\"", v11); /*0x144afb9c6*/
  sub_1411D43E0(&v89, v94, actionType); /*0x144afb9d7*/
  sub_1411D4340(&v83, &v89, &v92); /*0x144afb9ea*/
  sub_1411CE0F0((__int64)&v96, (const __m128i *)"action_type", v12); /*0x144afb9fa*/
  v109[0] = (__int64)&v96; /*0x144afba06*/
  v109[1] = (__int64)&v83; /*0x144afba18*/
  sub_141219F20(v131, &v86, v109, 0LL); /*0x144afba23*/
  if ( v96 ) /*0x144afba2f*/
    FMemory_Free_Wrapper(v96); /*0x144afba31*/
  if ( v83 ) /*0x144afba3e*/
    FMemory_Free_Wrapper(v83); /*0x144afba40*/
  if ( v89 ) /*0x144afba4d*/
    FMemory_Free_Wrapper(v89); /*0x144afba4f*/
  if ( v94[0] ) /*0x144afba5b*/
    FMemory_Free_Wrapper(v94[0]); /*0x144afba5d*/
  if ( v92 ) /*0x144afba69*/
    FMemory_Free_Wrapper((__int64)v92); /*0x144afba6b*/
  v13 = *(unsigned int *)(*((_QWORD *)v7 + 429) + 2024LL); /*0x144afba7c*/
  v83 = 0LL; /*0x144afba82*/
  v84 = 0LL; /*0x144afba87*/
  sub_1411D25E0(&v83, v13); /*0x144afba8c*/
  sub_1411CE0F0((__int64)v94, (const __m128i *)"player_id", v14); /*0x144afba9c*/
  v92 = v94; /*0x144afbaa8*/
  v93 = (FString *)&v83; /*0x144afbaba*/
  sub_141219F20(v131, &v86, &v92, 0LL); /*0x144afbac5*/
  if ( v94[0] ) /*0x144afbad1*/
    FMemory_Free_Wrapper(v94[0]); /*0x144afbad3*/
  if ( v83 ) /*0x144afbae0*/
    FMemory_Free_Wrapper(v83); /*0x144afbae2*/
  v15 = (unsigned __int16 *)&chText; /*0x144afbae7*/
  if ( extraMatchStateJson->Num ) /*0x144afbaee*/
    Data = extraMatchStateJson->Data; /*0x144afbaf4*/
  else
    Data = (unsigned __int16 *)&chText; /*0x144afbaf9*/
  if ( (unsigned int)FString_EqualsIgnoreCase_Maybe(Data, (unsigned __int8 *)Buf2) ) /*0x144afbb03*/
  {
    sub_1411CE0F0((__int64)v94, (const __m128i *)"match_data", v17); /*0x144afbb17*/
    v93 = extraMatchStateJson; /*0x144afbb20*/
    v92 = v94; /*0x144afbb27*/
    sub_1412E7D90(v131, &v86, &v92, 0LL); /*0x144afbb3b*/
    if ( v94[0] ) /*0x144afbb47*/
      FMemory_Free_Wrapper(v94[0]); /*0x144afbb49*/
  }
  v18 = actionData->Data; /*0x144afbb4e*/
  v123[0] = 0LL; /*0x144afbb53*/
  v123[1] = 0LL; /*0x144afbb5a*/
  v124 = 0LL; /*0x144afbb61*/
  v125 = 0; /*0x144afbb68*/
  v128 = 0; /*0x144afbb6e*/
  v129 = 0LL; /*0x144afbb74*/
  v130 = 0; /*0x144afbb7b*/
  Num = actionData->Num; /*0x144afbb81*/
  v126 = 128; /*0x144afbb85*/
  v127 = -1; /*0x144afbb8f*/
  v20 = &v18[Num]; /*0x144afbb9d*/
  if ( v18 != v20 ) /*0x144afbba4*/
  {
    v111 = &v83; /*0x144afbbaf*/
    do /*0x144afbd0b*/
    {
      if ( v18->StrValue.Num ) /*0x144afbbb3*/
        v21 = v18->StrValue.Data; /*0x144afbbb9*/
      else
        v21 = (unsigned __int16 *)&chText; /*0x144afbbbf*/
      if ( (unsigned int)FString_EqualsIgnoreCase_Maybe(v21, (unsigned __int8 *)Buf2) ) /*0x144afbbc9*/
      {
        sub_1411CE0F0((__int64)v109, (const __m128i *)"\"", v22); /*0x144afbc05*/
        sub_1411CE0F0((__int64)v94, (const __m128i *)"\"", v26); /*0x144afbc18*/
        sub_1411D43E0(&v92, v94, &v18->StrValue); /*0x144afbc29*/
        sub_1411D4340(&v96, &v92, v109); /*0x144afbc3a*/
        v24 = v96; /*0x144afbc3f*/
        v25 = &v96; /*0x144afbc43*/
        v8 |= 0x1Eu; /*0x144afbc47*/
      }
      else
      {
        IntValue = (unsigned int)v18->IntValue; /*0x144afbbd2*/
        v8 |= 1u; /*0x144afbbdc*/
        v89 = 0LL; /*0x144afbbdf*/
        v90 = 0LL; /*0x144afbbe4*/
        sub_1411D25E0(&v89, IntValue); /*0x144afbbe9*/
        v24 = v89; /*0x144afbbee*/
        v25 = &v89; /*0x144afbbf3*/
      }
      *v25 = 0LL; /*0x144afbc4c*/
      v83 = v24; /*0x144afbc4f*/
      v84 = v25[1]; /*0x144afbc57*/
      v25[1] = 0LL; /*0x144afbc62*/
      if ( (v8 & 0x10) != 0 ) /*0x144afbc6d*/
      {
        v8 &= ~0x10u; /*0x144afbc73*/
        if ( v96 ) /*0x144afbc79*/
          FMemory_Free_Wrapper(v96); /*0x144afbc7b*/
      }
      if ( (v8 & 8) != 0 ) /*0x144afbc83*/
      {
        v8 &= ~8u; /*0x144afbc89*/
        if ( v92 ) /*0x144afbc8f*/
          FMemory_Free_Wrapper((__int64)v92); /*0x144afbc91*/
      }
      if ( (v8 & 4) != 0 ) /*0x144afbc99*/
      {
        v8 &= ~4u; /*0x144afbc9f*/
        if ( v94[0] ) /*0x144afbca5*/
          FMemory_Free_Wrapper(v94[0]); /*0x144afbca7*/
      }
      if ( (v8 & 2) != 0 ) /*0x144afbcaf*/
      {
        v8 &= ~2u; /*0x144afbcb5*/
        if ( v109[0] ) /*0x144afbcbb*/
          FMemory_Free_Wrapper(v109[0]); /*0x144afbcbd*/
      }
      if ( (v8 & 1) != 0 ) /*0x144afbcc5*/
      {
        v8 &= ~1u; /*0x144afbccc*/
        if ( v89 ) /*0x144afbcd2*/
          FMemory_Free_Wrapper(v89); /*0x144afbcd4*/
      }
      v110 = (__int64 **)v18; /*0x144afbcdc*/
      sub_1411EFA80(v123, &v86, &v110, 0LL); /*0x144afbcf0*/
      if ( v83 ) /*0x144afbcfd*/
        FMemory_Free_Wrapper(v83); /*0x144afbcff*/
      ++v18; /*0x144afbd04*/
    }
    while ( v18 != v20 ); /*0x144afbd0b*/
  }
  v99 = 0LL; /*0x144afbd28*/
  si128 = _mm_load_si128((const __m128i *)&xmmword_14707ED10); /*0x144afbd2c*/
  v100 = 0LL; /*0x144afbd31*/
  v103 = 0LL; /*0x144afbd39*/
  v107 = 0LL; /*0x144afbd3d*/
  v108 = 0; /*0x144afbd41*/
  sub_141267A90(&v99, v123); /*0x144afbd44*/
  v27 = sub_144B1E4C0(&v87, &v99); /*0x144afbd5e*/
  sub_1411CE0F0((__int64)&v92, (const __m128i *)"action_data", v28); /*0x144afbd65*/
  v111 = (__int64 *)v27; /*0x144afbd6e*/
  v110 = &v92; /*0x144afbd75*/
  sub_141219F20(v131, &v86, &v110, 0LL); /*0x144afbd89*/
  if ( v92 ) /*0x144afbd95*/
    FMemory_Free_Wrapper((__int64)v92); /*0x144afbd97*/
  if ( v87 ) /*0x144afbda4*/
    FMemory_Free_Wrapper((__int64)v87); /*0x144afbda6*/
  v30 = subActions->Num; /*0x144afbdab*/
  if ( (int)v30 > 0 ) /*0x144afbdb2*/
  {
    v31 = subActions->Data; /*0x144afbdb8*/
    v32 = &subActions->Data[v30]; /*0x144afbdc3*/
    v89 = 0LL; /*0x144afbdc6*/
    v90 = 0LL; /*0x144afbdcb*/
    if ( v31 != v32 ) /*0x144afbdd7*/
    {
      v110 = &v92; /*0x144afbde1*/
      v111 = v94; /*0x144afbde9*/
      do /*0x144afc12d*/
      {
        if ( v130 > 1 ) /*0x144afbdfe*/
        {
          sub_14121C160(v123, 0LL); /*0x144afbe17*/
          v130 = 1; /*0x144afbe23*/
          sub_14120DCD0(v123); /*0x144afbe2d*/
        }
        else
        {
          sub_1412178E0(v123); /*0x144afbe00*/
          sub_14121C160(v123, 0LL); /*0x144afbe0e*/
        }
        sub_1411CE0F0((__int64)v119, (const __m128i *)"\"", v33); /*0x144afbe3d*/
        sub_1411CE0F0((__int64)v118, (const __m128i *)"\"", v34); /*0x144afbe4d*/
        sub_1411D43E0(v122, v118, v31); /*0x144afbe60*/
        sub_1411D4340(v94, v122, v119); /*0x144afbe74*/
        sub_1411CE0F0((__int64)&v92, (const __m128i *)"name", v35); /*0x144afbe84*/
        sub_141219F20(v123, &v86, &v110, 0LL); /*0x144afbe9c*/
        if ( v92 ) /*0x144afbea8*/
          FMemory_Free_Wrapper((__int64)v92); /*0x144afbeaa*/
        if ( v94[0] ) /*0x144afbeb6*/
          FMemory_Free_Wrapper(v94[0]); /*0x144afbeb8*/
        if ( v122[0] ) /*0x144afbec7*/
          FMemory_Free_Wrapper(v122[0]); /*0x144afbec9*/
        if ( v118[0] ) /*0x144afbed5*/
          FMemory_Free_Wrapper(v118[0]); /*0x144afbed7*/
        if ( v119[0] ) /*0x144afbee3*/
          FMemory_Free_Wrapper(v119[0]); /*0x144afbee5*/
        v36 = (__int64)v31->ActionData.Data; /*0x144afbeea*/
        v37 = v36 + 40LL * v31->ActionData.Num; /*0x144afbef6*/
        if ( v36 != v37 ) /*0x144afbefd*/
        {
          v88 = &v96; /*0x144afbf07*/
          do /*0x144afc077*/
          {
            if ( *(_DWORD *)(v36 + 32) ) /*0x144afbf10*/
              v38 = *(unsigned __int16 **)(v36 + 24); /*0x144afbf16*/
            else
              v38 = (unsigned __int16 *)&chText; /*0x144afbf1c*/
            if ( (unsigned int)FString_EqualsIgnoreCase_Maybe(v38, (unsigned __int8 *)Buf2) ) /*0x144afbf26*/
            {
              sub_1411CE0F0((__int64)v91, (const __m128i *)"\"", v39); /*0x144afbf63*/
              sub_1411CE0F0((__int64)v95, (const __m128i *)"\"", v44); /*0x144afbf73*/
              sub_1411D43E0(v120, v95, v36 + 24); /*0x144afbf87*/
              sub_1411D4340(v109, v120, v91); /*0x144afbf9c*/
              v41 = v109[0]; /*0x144afbfa1*/
              v42 = v109; /*0x144afbfa5*/
              v43 = 960; /*0x144afbfa9*/
            }
            else
            {
              v40 = *(unsigned int *)(v36 + 16); /*0x144afbf2f*/
              v83 = 0LL; /*0x144afbf39*/
              v84 = 0LL; /*0x144afbf3e*/
              sub_1411D25E0(&v83, v40); /*0x144afbf43*/
              v41 = v83; /*0x144afbf48*/
              v42 = &v83; /*0x144afbf4d*/
              v43 = 32; /*0x144afbf52*/
            }
            v8 |= v43; /*0x144afbfb0*/
            *v42 = 0LL; /*0x144afbfb2*/
            v97 = *((_DWORD *)v42 + 2); /*0x144afbfb8*/
            v98 = *((_DWORD *)v42 + 3); /*0x144afbfbe*/
            v42[1] = 0LL; /*0x144afbfc1*/
            v96 = v41; /*0x144afbfc9*/
            if ( (v8 & 0x200) != 0 ) /*0x144afbfd1*/
            {
              v8 &= ~0x200u; /*0x144afbfd7*/
              if ( v109[0] ) /*0x144afbfde*/
                FMemory_Free_Wrapper(v109[0]); /*0x144afbfe0*/
            }
            if ( (v8 & 0x100) != 0 ) /*0x144afbfe9*/
            {
              v8 &= ~0x100u; /*0x144afbff2*/
              if ( v120[0] ) /*0x144afbff9*/
                FMemory_Free_Wrapper(v120[0]); /*0x144afbffb*/
            }
            if ( (v8 & 0x80u) != 0 ) /*0x144afc002*/
            {
              v8 &= ~0x80u; /*0x144afc008*/
              if ( v95[0] ) /*0x144afc00f*/
                FMemory_Free_Wrapper(v95[0]); /*0x144afc011*/
            }
            if ( (v8 & 0x40) != 0 ) /*0x144afc019*/
            {
              v8 &= ~0x40u; /*0x144afc020*/
              if ( v91[0] ) /*0x144afc026*/
                FMemory_Free_Wrapper(v91[0]); /*0x144afc028*/
            }
            if ( (v8 & 0x20) != 0 ) /*0x144afc030*/
            {
              v8 &= ~0x20u; /*0x144afc037*/
              if ( v83 ) /*0x144afc03d*/
                FMemory_Free_Wrapper(v83); /*0x144afc03f*/
            }
            v87 = (__int64 *)v36; /*0x144afc047*/
            sub_1411EFA80(v123, v85, &v87, 0LL); /*0x144afc05d*/
            if ( v96 ) /*0x144afc069*/
              FMemory_Free_Wrapper(v96); /*0x144afc06b*/
            v36 += 40LL; /*0x144afc070*/
          }
          while ( v36 != v37 ); /*0x144afc077*/
        }
        v99 = 0LL; /*0x144afc090*/
        si128 = _mm_load_si128((const __m128i *)&xmmword_14707ED10); /*0x144afc094*/
        v100 = 0LL; /*0x144afc099*/
        v103 = 0LL; /*0x144afc0a1*/
        v107 = 0LL; /*0x144afc0a5*/
        v108 = 0; /*0x144afc0a9*/
        sub_141267A90(&v99, v123); /*0x144afc0ac*/
        v45 = sub_144B1E4C0(v121, &v99); /*0x144afc0c1*/
        v46 = v90; /*0x144afc0c4*/
        if ( (_DWORD)v90 == HIDWORD(v90) ) /*0x144afc0cc*/
          v46 = sub_1411AF9E0(2064LL, &v89, (char *)&v90 + 4); /*0x144afc0dd*/
        LODWORD(v90) = v46 + 1; /*0x144afc0e5*/
        v47 = v89 + 16LL * v46; /*0x144afc0f0*/
        *(_QWORD *)v47 = 0LL; /*0x144afc0f5*/
        *(_QWORD *)v47 = *(_QWORD *)v45; /*0x144afc0fb*/
        *(_QWORD *)v45 = 0LL; /*0x144afc0fe*/
        *(_DWORD *)(v47 + 8) = *(_DWORD *)(v45 + 8); /*0x144afc104*/
        *(_DWORD *)(v47 + 12) = *(_DWORD *)(v45 + 12); /*0x144afc10a*/
        *(_QWORD *)(v45 + 8) = 0LL; /*0x144afc10d*/
        if ( v121[0] ) /*0x144afc11f*/
          FMemory_Free_Wrapper(v121[0]); /*0x144afc121*/
        ++v31; /*0x144afc126*/
      }
      while ( v31 != v32 ); /*0x144afc12d*/
    }
    sub_1411CE0F0((__int64)v118, (const __m128i *)L"]", v29); /*0x144afc13e*/
    v49 = v89; /*0x144afc143*/
    v50 = 1; /*0x144afc148*/
    v83 = 0LL; /*0x144afc14b*/
    v51 = v89 + 16LL * (int)v90; /*0x144afc159*/
    v84 = 0LL; /*0x144afc15c*/
    if ( v89 != v51 ) /*0x144afc168*/
    {
      do /*0x144afc1b2*/
      {
        if ( v50 ) /*0x144afc173*/
          v50 = 0; /*0x144afc175*/
        else
          sub_1411D2340(&v83, L",", 1LL); /*0x144afc18c*/
        v52 = *(_DWORD *)(v49 + 8); /*0x144afc191*/
        v53 = (unsigned int)(v52 - 1); /*0x144afc19e*/
        if ( !v52 ) /*0x144afc1a2*/
          v53 = 0LL; /*0x144afc1a2*/
        sub_1411D2340(&v83, *(_QWORD *)v49, v53); /*0x144afc1a6*/
        v49 += 16LL; /*0x144afc1ab*/
      }
      while ( v49 != v51 ); /*0x144afc1b2*/
    }
    sub_1411CE0F0((__int64)v119, (const __m128i *)L"[", v48); /*0x144afc1bf*/
    sub_1411D4340(v120, v119, &v83); /*0x144afc1d4*/
    sub_1411D4340(v95, v120, v118); /*0x144afc1e8*/
    sub_1411CE0F0((__int64)v91, (const __m128i *)"sub_actions", v54); /*0x144afc1f9*/
    v87 = v91; /*0x144afc206*/
    v88 = v95; /*0x144afc219*/
    sub_141219F20(v131, v85, &v87, 0LL); /*0x144afc225*/
    if ( v91[0] ) /*0x144afc232*/
      FMemory_Free_Wrapper(v91[0]); /*0x144afc234*/
    if ( v95[0] ) /*0x144afc240*/
      FMemory_Free_Wrapper(v95[0]); /*0x144afc242*/
    if ( v120[0] ) /*0x144afc251*/
      FMemory_Free_Wrapper(v120[0]); /*0x144afc253*/
    if ( v119[0] ) /*0x144afc25f*/
      FMemory_Free_Wrapper(v119[0]); /*0x144afc261*/
    if ( v83 ) /*0x144afc26e*/
      FMemory_Free_Wrapper(v83); /*0x144afc270*/
    if ( v118[0] ) /*0x144afc27c*/
      FMemory_Free_Wrapper(v118[0]); /*0x144afc27e*/
    sub_1411AE3E0(v89, (unsigned int)v90); /*0x144afc28c*/
    if ( v89 ) /*0x144afc299*/
      FMemory_Free_Wrapper(v89); /*0x144afc29b*/
    v6 = v115; /*0x144afc2a0*/
    v7 = v114; /*0x144afc2a6*/
  }
  if ( !*((_BYTE *)v7 + 1960) ) /*0x144afc2b2*/
  {
    v74 = (unsigned int)++*((_DWORD *)v7 + 807); /*0x144afc6b5*/
    v83 = 0LL; /*0x144afc6bc*/
    v84 = 0LL; /*0x144afc6c1*/
    sub_1411D25E0(&v83, v74); /*0x144afc6ca*/
    sub_1411CE0F0((__int64)v91, (const __m128i *)"action_id", v75); /*0x144afc6db*/
    v87 = v91; /*0x144afc6e8*/
    v88 = &v83; /*0x144afc6fc*/
    sub_141219F20(v131, v85, &v87, 0LL); /*0x144afc708*/
    if ( v91[0] ) /*0x144afc715*/
      FMemory_Free_Wrapper(v91[0]); /*0x144afc717*/
    if ( v83 ) /*0x144afc724*/
      FMemory_Free_Wrapper(v83); /*0x144afc726*/
    goto LABEL_177; /*0x144afc726*/
  }
  sub_1411CE0F0((__int64)v95, (const __m128i *)L"1", v29); /*0x144afc2c3*/
  sub_1411CE0F0((__int64)v91, (const __m128i *)"validate_turn_switch", v55); /*0x144afc2d4*/
  v87 = v91; /*0x144afc2e1*/
  v88 = v95; /*0x144afc2f4*/
  sub_141219F20(v131, v85, &v87, 0LL); /*0x144afc300*/
  if ( v91[0] ) /*0x144afc30d*/
    FMemory_Free_Wrapper(v91[0]); /*0x144afc30f*/
  if ( v95[0] ) /*0x144afc31b*/
    FMemory_Free_Wrapper(v95[0]); /*0x144afc31d*/
  v56 = (_DWORD *)((char *)v7 + 3224); /*0x144afc32c*/
  v57 = *((_DWORD *)v7 + 806); /*0x144afc333*/
  if ( *((_DWORD *)v7 + 812) == *((_DWORD *)v7 + 823) ) /*0x144afc339*/
    goto LABEL_132; /*0x144afc339*/
  v58 = (char *)*((_QWORD *)v7 + 413); /*0x144afc33b*/
  if ( !v58 ) /*0x144afc349*/
    v58 = (char *)v7 + 3296; /*0x144afc349*/
  v59 = *(_DWORD *)&v58[4 * (v57 & (*((_DWORD *)v7 + 828) - 1))]; /*0x144afc352*/
  if ( v59 == -1 ) /*0x144afc358*/
  {
LABEL_132:
    LODWORD(v99) = *((_DWORD *)v7 + 806); /*0x144afc378*/
    v100 = 0LL; /*0x144afc382*/
    v61 = v112->Num; /*0x144afc386*/
    v62 = v112->Data; /*0x144afc38a*/
    v101 = v61; /*0x144afc38d*/
    if ( (_DWORD)v61 ) /*0x144afc392*/
    {
      TArray_ResizeAllocation(2u, 2, v61, 0, (__int64)&v100, v61, v102); /*0x144afc4f9*/
      memcpy(v100, v62, 2 * v61); /*0x144afc50b*/
    }
    else
    {
      v102[0] = 0; /*0x144afc398*/
    }
    v67 = v113->Num; /*0x144afc51d*/
    v68 = (__int64)v113->Data; /*0x144afc527*/
    v102[1] = *(_DWORD *)(*((_QWORD *)v7 + 429) + 2024LL); /*0x144afc52a*/
    v103 = 0LL; /*0x144afc52d*/
    si128.m128i_i32[0] = v67; /*0x144afc531*/
    if ( v67 ) /*0x144afc536*/
    {
      TArray_ResizeAllocation(0x28u, 8, v67, 0, (__int64)&v103, v67, &si128.m128i_i32[1]); /*0x144afc560*/
      ExecParam_CopyConstructArrayElements_Stride40((__int64)v103, v68, v67); /*0x144afc56f*/
    }
    else
    {
      si128.m128i_i64[0] = 0LL; /*0x144afc538*/
    }
    v69 = v6->Num; /*0x144afc576*/
    v70 = (__int64)v6->Data; /*0x144afc57b*/
    si128.m128i_i64[1] = 0LL; /*0x144afc57f*/
    v105 = v69; /*0x144afc583*/
    if ( v69 ) /*0x144afc588*/
    {
      TArray_ResizeAllocation(0x20u, 8, v69, 0, (__int64)&si128.m128i_i64[1], v69, &v106); /*0x144afc5b2*/
      ExecParam_CopyConstructNestedTArray_Stride32(si128.m128i_i64[1], v70, v69); /*0x144afc5c1*/
    }
    else
    {
      v106 = 0; /*0x144afc58a*/
    }
    v87 = (__int64 *)((char *)v7 + 3224); /*0x144afc5ca*/
    v88 = &v99; /*0x144afc5d2*/
    sub_144AA2500((char *)v7 + 3240, v85, &v87, 0LL); /*0x144afc5e4*/
    ExecParam_DestructArrayOfStructPairs_Stride32(si128.m128i_i64[1], v105); /*0x144afc5f0*/
    if ( si128.m128i_i64[1] ) /*0x144afc5fc*/
      FMemory_Free_Wrapper(si128.m128i_i64[1]); /*0x144afc5fe*/
    ExecParam_DestructArrayElements_Stride40(v103, si128.m128i_i32[0]); /*0x144afc60a*/
    if ( v103 ) /*0x144afc616*/
      FMemory_Free_Wrapper((__int64)v103); /*0x144afc618*/
    if ( v100 ) /*0x144afc624*/
      FMemory_Free_Wrapper((__int64)v100); /*0x144afc626*/
    v71 = (unsigned int)*v56; /*0x144afc62b*/
    v83 = 0LL; /*0x144afc635*/
    v84 = 0LL; /*0x144afc63a*/
    sub_1411D25E0(&v83, v71); /*0x144afc63f*/
    sub_1411CE0F0((__int64)v91, (const __m128i *)"action_id", v72); /*0x144afc650*/
    v87 = v91; /*0x144afc65d*/
    v88 = &v83; /*0x144afc671*/
    sub_141219F20(v131, v85, &v87, 0LL); /*0x144afc67d*/
    if ( v91[0] ) /*0x144afc68a*/
      FMemory_Free_Wrapper(v91[0]); /*0x144afc68c*/
    if ( v83 ) /*0x144afc699*/
      FMemory_Free_Wrapper(v83); /*0x144afc69b*/
    ++*v56; /*0x144afc6a0*/
LABEL_177:
    if ( *((_BYTE *)v7 + 1962) ) /*0x144afc72b*/
    {
      sub_1411CE0F0((__int64)v95, (const __m128i *)L"1", v73); /*0x144afc740*/
      sub_1411CE0F0((__int64)v91, (const __m128i *)"local_subactions", v76); /*0x144afc751*/
      v87 = v91; /*0x144afc75e*/
      v88 = v95; /*0x144afc771*/
      sub_141219F20(v131, v85, &v87, 0LL); /*0x144afc77d*/
      if ( v91[0] ) /*0x144afc78a*/
        FMemory_Free_Wrapper(v91[0]); /*0x144afc78c*/
      if ( v95[0] ) /*0x144afc798*/
        FMemory_Free_Wrapper(v95[0]); /*0x144afc79a*/
    }
    v77 = (__int64 *)v112; /*0x144afc79f*/
    if ( v112->Num ) /*0x144afc7a3*/
      v78 = v112->Data; /*0x144afc7a9*/
    else
      v78 = (unsigned __int16 *)&chText; /*0x144afc7ae*/
    if ( !(unsigned int)FString_EqualsIgnoreCase_Maybe(v78, "XActionEndOfTurn") ) /*0x144afc7b8*/
    {
      if ( *((_DWORD *)v7 + 504) ) /*0x144afc7c5*/
        v15 = (unsigned __int16 *)*((_QWORD *)v7 + 251); /*0x144afc7ce*/
      if ( !(unsigned int)FString_EqualsIgnoreCase_Maybe(v15, "knockout_8") ) /*0x144afc7df*/
      {
        sub_1411CE0F0((__int64)v95, (const __m128i *)L"1", v79); /*0x144afc7f3*/
        sub_1411CE0F0((__int64)v91, (const __m128i *)"is_knockout", v80); /*0x144afc804*/
        v87 = v91; /*0x144afc811*/
        v88 = v95; /*0x144afc824*/
        sub_141219F20(v131, v85, &v87, 0LL); /*0x144afc830*/
        if ( v91[0] ) /*0x144afc83d*/
          FMemory_Free_Wrapper(v91[0]); /*0x144afc83f*/
        if ( v95[0] ) /*0x144afc84b*/
          FMemory_Free_Wrapper(v95[0]); /*0x144afc84d*/
      }
    }
    v99 = 0LL; /*0x144afc865*/
    si128 = _mm_load_si128((const __m128i *)&xmmword_14707ED10); /*0x144afc869*/
    v100 = 0LL; /*0x144afc86e*/
    v103 = 0LL; /*0x144afc876*/
    v107 = 0LL; /*0x144afc87a*/
    v108 = 0; /*0x144afc87e*/
    sub_141267A90(&v99, v131); /*0x144afc881*/
    v81 = v116; /*0x144afc886*/
    sub_144B1E4C0(v116, &v99); /*0x144afc891*/
    v130 = 0; /*0x144afc89d*/
    if ( v129 ) /*0x144afc8a6*/
      FMemory_Free_Wrapper(v129); /*0x144afc8a8*/
    sub_14121C160(v123, 0LL); /*0x144afc8b6*/
    if ( v124 ) /*0x144afc8c5*/
      FMemory_Free_Wrapper(v124); /*0x144afc8c7*/
    if ( v123[0] ) /*0x144afc8d6*/
      FMemory_Free_Wrapper(v123[0]); /*0x144afc8d8*/
    v138 = 0; /*0x144afc8e4*/
    if ( v137 ) /*0x144afc8ed*/
      FMemory_Free_Wrapper(v137); /*0x144afc8ef*/
    sub_14121C160(v131, 0LL); /*0x144afc8fd*/
    if ( v132 ) /*0x144afc90c*/
      FMemory_Free_Wrapper(v132); /*0x144afc90e*/
    if ( v131[0] ) /*0x144afc91d*/
      FMemory_Free_Wrapper(v131[0]); /*0x144afc91f*/
    if ( *v77 ) /*0x144afc924*/
      FMemory_Free_Wrapper(*v77); /*0x144afc92c*/
    v82 = (__int64 *)v113; /*0x144afc931*/
    ExecParam_DestructArrayElements_Stride40(&v113->Data->Name.Data, v113->Num); /*0x144afc93b*/
    if ( *v82 ) /*0x144afc940*/
      FMemory_Free_Wrapper(*v82); /*0x144afc948*/
    ExecParam_DestructArrayOfStructPairs_Stride32((__int64)v6->Data, v6->Num); /*0x144afc956*/
    if ( v6->Data ) /*0x144afc95b*/
      FMemory_Free_Wrapper((__int64)v6->Data); /*0x144afc964*/
    if ( *v117 ) /*0x144afc96d*/
      FMemory_Free_Wrapper(*v117); /*0x144afc975*/
    return v81; /*0x144afc97a*/
  }
  v60 = *((_QWORD *)v7 + 405); /*0x144afc35a*/
  while ( *(_DWORD *)(v60 + 80LL * v59) != v57 ) /*0x144afc36d*/
  {
    v59 = *(_DWORD *)(v60 + 80LL * v59 + 72); /*0x144afc36f*/
    if ( v59 == -1 ) /*0x144afc376*/
      goto LABEL_132; /*0x144afc376*/
  }
  sub_1411E56A0(v121, L"RESYNC: jsonifyAction invalid action ID");
  sub_144AFD0C0(v7, v121, 0LL); /*0x144afc3c0*/
  sub_144A92870(v7); /*0x144afc3c8*/
  v63 = v116; /*0x144afc3cd*/
  sub_1411CE0F0((__int64)v116, (const __m128i *)Buf2, v64); /*0x144afc3db*/
  v130 = 0; /*0x144afc3ea*/
  if ( v129 ) /*0x144afc3f4*/
    FMemory_Free_Wrapper(v129); /*0x144afc3f6*/
  sub_14121C160(v123, 0LL); /*0x144afc404*/
  if ( v124 ) /*0x144afc413*/
    FMemory_Free_Wrapper(v124); /*0x144afc415*/
  if ( v123[0] ) /*0x144afc424*/
    FMemory_Free_Wrapper(v123[0]); /*0x144afc426*/
  v138 = 0; /*0x144afc432*/
  if ( v137 ) /*0x144afc43c*/
    FMemory_Free_Wrapper(v137); /*0x144afc43e*/
  sub_14121C160(v131, 0LL); /*0x144afc44c*/
  if ( v132 ) /*0x144afc45b*/
    FMemory_Free_Wrapper(v132); /*0x144afc45d*/
  if ( v131[0] ) /*0x144afc46c*/
    FMemory_Free_Wrapper(v131[0]); /*0x144afc46e*/
  if ( v112->Data ) /*0x144afc477*/
    FMemory_Free_Wrapper((__int64)v112->Data); /*0x144afc47f*/
  v65 = (__int64 *)v113; /*0x144afc484*/
  ExecParam_DestructArrayElements_Stride40(&v113->Data->Name.Data, v113->Num); /*0x144afc48f*/
  if ( *v65 ) /*0x144afc494*/
    FMemory_Free_Wrapper(*v65); /*0x144afc49c*/
  ExecParam_DestructArrayOfStructPairs_Stride32((__int64)v6->Data, v6->Num); /*0x144afc4aa*/
  if ( v6->Data ) /*0x144afc4af*/
    FMemory_Free_Wrapper((__int64)v6->Data); /*0x144afc4b8*/
  if ( *v117 ) /*0x144afc4c1*/
    FMemory_Free_Wrapper(*v117); /*0x144afc4c9*/
  return v63; /*0x144afc97d*/
}
