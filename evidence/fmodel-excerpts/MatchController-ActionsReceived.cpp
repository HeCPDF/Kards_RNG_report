// FModel 反编译原文摘录，未加工。来源：H:\!Modding\Output\Exports\kards\Content\Blueprints\Logic\MatchController.cpp
// 这是 AMatchController_C（AMatchControllerV2 的蓝图子类）的完整 ExecuteUbergraph 反编译产物中
// 与 GetNextAction/CurrentActionId 推进时机相关的三段：事件入口（1938-1944 行）、
// 广播消息并跳入消化循环（1735-1744 行）、消化循环本身对 GetNextAction 的调用（465-489 行）。
// evidence/CurrentActionId-increment-logic.md "触发时机：已定位到具体的蓝图事件"一节引用，
// 此前该文档只贴出了 1938-1944 行的事件入口片段，完整三段原文见本文件。

// ==== Logic/MatchController.cpp:1938-1944 —— 事件入口本身 ====
    // (Event, Public, BlueprintEvent)
    public void ActionsReceived()
    {
        ExecuteUbergraph_MatchController(21408);

        return;
    }

// ==== Logic/MatchController.cpp:1725-1748（节选）—— Label_21408：ActionsReceived 事件跳入的位置 ====
        Label_21293:
        goto Label_9632;

        Label_21298:
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetLogic(this, CallFunc_GetLogic_Logic_34);

        CallFunc_GetLogic_Logic_34->ResolveMulliganResponse(Event_handCards, Event_deck, Event_side);

        return;

        Label_21408:
        GetGameInstanceSubsystem_3 = USubsystemBlueprintLibrary::GetGameInstanceSubsystem(this, FindObject<UClass>(nullptr, "/Script/GameplayMessageRuntime.GameplayMessageSubsystem"));

        MakeStruct_S_MonitorBattleState.E_PlayState_2_EE11CF884B9186EBC98D8289BF521339 = 0x3;

        MakeStruct_S_MonitorBattleState.TestMessage_6_371C94274D97ECA9FC7C4C996C1575B6 = "from MatchController : ActionsReceived";

        GetGameInstanceSubsystem_3->K2_BroadcastMessage(FGameplayTag("MonitorPlayState"), MakeStruct_S_MonitorBattleState);

        goto Label_5066;

        Label_21608:
        goto Label_21058;

        Label_21613:
        handleKnockoutResponse(Event_LobbyInfo);

        return;

        Label_21637:

// ==== Logic/MatchController.cpp:460-489（节选）—— Label_5066/Label_5308：GetNextAction 消化循环本体 ====

        CurrentMatchmakingWidgetWithRadar->ShowMatchup();

        return;

        Label_5066:
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetLogic(this, CallFunc_GetLogic_Logic_37);

        Not_PreBool_2 = !CallFunc_GetLogic_Logic_37->preStateDone_DoMulligan;

        BooleanAND_5 = Not_PreBool_2 && bUseActionsForMulligan;

        BooleanOR_7 = (isResyncingMatch || BooleanAND_5);

        if (!BooleanOR_7)
            goto Label_5308;

        Delay(0.1f);
        goto Label_5066;

        return;

        Label_5308:
        AMatchControllerV2::GetNextAction(CallFunc_GetNextAction_action_1, CallFunc_GetNextAction_success_1);

        if (!CallFunc_GetNextAction_success_1)
            goto Label_5446;

        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetOnlineMatch(this, CallFunc_GetOnlineMatch_onlineMatch_4);
