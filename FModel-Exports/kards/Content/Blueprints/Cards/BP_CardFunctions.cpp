class ABP_CardFunctions_C : public ACardFunctionsStub
{
public:
    class USimpleConstructionScript* SimpleConstructionScript = "SimpleConstructionScript'kards/Content/Blueprints/Cards/BP_CardFunctions.BP_CardFunctions_C:SimpleConstructionScript_2'";
    class UFunction* UberGraphFunction = "Function'kards/Content/Blueprints/Cards/BP_CardFunctions.BP_CardFunctions_C:ExecuteUbergraph_BP_CardFunctions'";
    struct FPointerToUberGraphFrame UberGraphFrame = {};
    struct FRandomStream cardsRandomStream = {
        "InitialSeed": 0,
        "Seed": 0
    };
    struct FRandomStream encryptionStream = {
        "InitialSeed": 0,
        "Seed": 0
    };
    FMulticastScriptDelegate DestroyedCountChanged = ;
    FMulticastScriptDelegate OnBondVisualsUpdated = ;
    FString WasLeftMostWhenPlayedFromHandKey = "WasLeftMostCardWhenPlayedFromHand";
    FString WasRightMostWhenPlayedFromHandKey = "WasRightMostWhenPlayedFromHandKey";
    struct FActorTickFunction PrimaryActorTick = {
        "bStartWithTickEnabled": false,
        "bAllowTickOnDedicatedServer": false
    };
    TArray<FName> Tags = {
        FName("deleteAfterBattle")
    };
    class USceneComponent* DefaultSceneRoot;
    class ABP_GameState_Battle_C* GameStateRef;
    int encryptionKey2;
    class UU_CardFunctionsNotifier_C* CardFunctionsNotifier;
    bool ShouldUseHighlightForBond;

    // (Public, Delegate, BlueprintCallable, BlueprintEvent)
    public void DestroyedCountChanged__DelegateSignature()
    {
        return;
    }

    // (Public, Delegate, BlueprintCallable, BlueprintEvent)
    public void OnBondVisualsUpdated__DelegateSignature(ESideEnum side)
    {
        return;
    }

    // (Final, UbergraphFunction, HasDefaults)
    private void ExecuteUbergraph_BP_CardFunctions(int EntryPoint)
    {
        goto EntryPoint;
    
        Label_15:
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->Get Is Server Config("enable_bond_highlight", this, CallFunc_Get_Is_Server_Config_KeyTrue);
    
        ShouldUseHighlightForBond = CallFunc_Get_Is_Server_Config_KeyTrue;
    
        goto Label_832;
    
        Label_104:
        CallFunc_NotifyShowCampaignMessage_DelayBeforeShowing_ImplicitCast = Cast<double>(Event_delay);
    
        CardFunctionsNotifier->NotifyShowCampaignMessage(Event_message_1, Event_showOnce, Event_showMulliganWhenFinished, CallFunc_NotifyShowCampaignMessage_DelayBeforeShowing_ImplicitCast, Event_startOfGamea);
    
        return;
    
        Label_215:
        SpawnObject = UGameplayStatics::SpawnObject(FindObject<UBlueprintGeneratedClass>(nullptr, "kards/Content/Blueprints/Logic/U_CardFunctionsNotifier.U_CardFunctionsNotifier_C"), this);
    
        CardFunctionsNotifier = SpawnObject;
    
        return;
    
        Label_265:
        CardFunctionsNotifier->NotifyGiveStar(Event_number);
    
        return;
    
        Label_311:
        CardFunctionsNotifier->NotifyIncrementObjectiveCounter();
    
        return;
    
        Label_348:
        CardFunctionsNotifier->NotifyForceEndTurn(true);
    
        return;
    
        Label_386:
        CardFunctionsNotifier->NotiferStarCounterChanged(Event_star, Event_message, Event_starStatus);
    
        return;
    
        Label_450:
        GetTimeSeconds = UGameplayStatics::GetTimeSeconds(this);
    
        Multiply_DoubleDouble = (GetTimeSeconds * 1000);
    
        FTrunc = UKismetMathLibrary::FTrunc(Multiply_DoubleDouble);
    
        encryptionKey2 = FTrunc;
    
        goto Label_215;
    
        Label_604:
        GetGameState = UGameplayStatics::GetGameState(this);
    
        AsBP_Game_State_Battle = Cast<ABP_GameState_Battle_C>(GetGameState);
    
        bSuccess = Cast<bool>(AsBP_Game_State_Battle);
    
        if (!bSuccess)
            goto Label_604;
    
        GameStateRef = AsBP_Game_State_Battle;
    
        CreateDelegate_OutputDelegate->BindUFunction(this, FName("ReportKreditTampering"));
    
        GameStateRef->OnTamperingDetected->Add(CreateDelegate_OutputDelegate);
    
        goto Label_15;
    
        Label_784:
        ReportTamperingToSever(Event_reportReason);
    
        return;
    
        Label_808:
        ReportTamperingToSever(CustomEvent_reportReason);
    
        return;
    
        Label_832:
        return;
    }

    // (BlueprintCallable, BlueprintEvent)
    private void ReportKreditTampering(FString reportReason)
    {
        UberGraphFrame->CustomEvent_reportReason = reportReason;
    
        ExecuteUbergraph_BP_CardFunctions(808);
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void ReportTampering(FString reportReason)
    {
        UberGraphFrame->Event_reportReason = reportReason;
    
        ExecuteUbergraph_BP_CardFunctions(784);
    
        return;
    }

    // (Event, Protected, BlueprintEvent)
    protected void ReceiveBeginPlay()
    {
        ExecuteUbergraph_BP_CardFunctions(450);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void UpdateCampaignStarStatus(int star, FText*& message, ECampaignStarStatus starStatus)
    {
        UberGraphFrame->Event_star = star;
    
        UberGraphFrame->Event_message = message;
    
        UberGraphFrame->Event_starStatus = starStatus;
    
        ExecuteUbergraph_BP_CardFunctions(386);
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void ForceEndTurn()
    {
        ExecuteUbergraph_BP_CardFunctions(348);
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void IncrementObjectiveCounter()
    {
        ExecuteUbergraph_BP_CardFunctions(311);
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void GiveStarForCampaign(int number)
    {
        UberGraphFrame->Event_number = number;
    
        ExecuteUbergraph_BP_CardFunctions(265);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ShowCampaignMessage(FText*& message, bool showOnce, bool showMulliganWhenFinished, float delay, bool startOfGamea)
    {
        UberGraphFrame->Event_message_1 = message;
    
        UberGraphFrame->Event_showOnce = showOnce;
    
        UberGraphFrame->Event_showMulliganWhenFinished = showMulliganWhenFinished;
    
        UberGraphFrame->Event_delay = delay;
    
        UberGraphFrame->Event_startOfGamea = startOfGamea;
    
        ExecuteUbergraph_BP_CardFunctions(104);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void GetTargetedCard(class UBaseCardObject* callerCard, bool& hasTarget, class UBaseCardObject*& card)
    {
        IsValid = callerCard;
    
        if (!IsValid)
            goto Label_165;
    
        IsValid_1 = callerCard->targetOverride;
    
        if (!IsValid_1)
            goto Label_266;
    
        hasTarget = true;
    
        card = callerCard->targetOverride;
    
        return;
    
        Label_165:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("You should always provide GetTargetedCard with the caller", this);
    
        return;
    
        Label_266:
        IsValid_2 = callerCard->currentTarget;
    
        if (!IsValid_2)
            goto Label_388;
    
        hasTarget = true;
    
        card = callerCard->currentTarget;
    
        return;
    
        Label_388:
        hasTarget = false;
    
        card = nullptr;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetCardsPlayedThisTurn(TArray<class UBaseCardObject*>& cards)
    {
        GetAllCards(CallFunc_GetAllCards_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_74:
        Array_Length = CallFunc_GetAllCards_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_497;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCards_cards[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->enterPlayOnTurn == CallFunc_GetTurnNumber_turnNumber;
    
        if (!EqualEqual_IntInt)
            goto Label_529;
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCards_cards[Temp_int_Array_Index_Variable];
    
        Array_Add = cardsPlayed.Add(CallFunc_Array_Get_Item);
    
        goto Label_603;
    
        Label_497:
        cards = cardsPlayed;
    
        return;
    
        Label_529:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_74;
    
        Label_603:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetCardFromID(int cardID, class UBaseCardObject*& card)
    {
        GameStateRef->FetchCardFromCardID(cardID, CallFunc_FetchCardFromCardID_fetchedCard);
    
        card = CallFunc_FetchCardFromCardID_fetchedCard;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetAllUnitsOnBoard(bool includeCovertCards, TArray<class UBaseCardObject*>& cards)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_905;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->getAndDecryptDefense(CallFunc_getAndDecryptDefense_decryptedDefense);
    
        CallFunc_Array_Get_Item->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        Greater_IntInt = (CallFunc_getAndDecryptDefense_decryptedDefense > 0);
    
        Not_PreBool = !CallFunc_IsUnrevealedCovertCard_isIt;
    
        CallFunc_Array_Get_Item->IsUnit(CallFunc_IsUnit_isIt);
    
        BooleanOR = (Not_PreBool || includeCovertCards);
    
        CallFunc_Array_Get_Item->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        BooleanAND = Greater_IntInt && CallFunc_IsLocatedOnBoard_isIt;
    
        BooleanAND_1 = BooleanAND && CallFunc_IsUnit_isIt;
    
        BooleanAND_2 = BooleanAND_1 && BooleanOR;
    
        if (!BooleanAND_2)
            goto Label_937;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Array_Add = _cards.Add(CallFunc_Array_Get_Item);
    
        goto Label_1011;
    
        Label_905:
        cards = _cards;
    
        return;
    
        Label_937:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_1011:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetAllCardsOnBoard(bool includeCovertCards, TArray<class UBaseCardObject*>& cards)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_713;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        CallFunc_Array_Get_Item->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        Not_PreBool = !CallFunc_IsUnrevealedCovertCard_isIt;
    
        BooleanOR = (Not_PreBool || includeCovertCards);
    
        BooleanAND = CallFunc_IsLocatedOnBoard_isIt && BooleanOR;
    
        if (!BooleanAND)
            goto Label_745;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Array_Add = _cards.Add(CallFunc_Array_Get_Item);
    
        goto Label_819;
    
        Label_713:
        cards = _cards;
    
        return;
    
        Label_745:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_819:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetAllCardsInFrontline(bool includeCovertCards, TArray<class UBaseCardObject*>& cards)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_725;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        EqualEqual_ByteByte = ((!CallFunc_Array_Get_Item->location) == (!0x7));
    
        Not_PreBool = !CallFunc_IsUnrevealedCovertCard_isIt;
    
        BooleanOR = (Not_PreBool || includeCovertCards);
    
        BooleanAND = EqualEqual_ByteByte && BooleanOR;
    
        if (!BooleanAND)
            goto Label_757;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Array_Add = _cards.Add(CallFunc_Array_Get_Item);
    
        goto Label_831;
    
        Label_725:
        cards = _cards;
    
        return;
    
        Label_757:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_831:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetAdjacentCards(class UBaseCardObject* card, bool includeCovertCards, TArray<class UBaseCardObject*>& adjacentCards)
    {
        IsValid_2 = card;
    
        if (!IsValid_2)
            goto Label_573;
    
        _locationNumber = card->locationNumber;
    
        FetchCardsByLocation(card->location, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_244:
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Array_Length_1 = CallFunc_FetchCardsByLocation_AllCardsInLocation.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        BooleanAND = Not_PreBool && Less_IntInt;
    
        if (!BooleanAND)
            goto Label_610;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        Array_Length = _adjacentCards.Length;
    
        EqualEqual_IntInt = Array_Length == 2;
    
        if (!EqualEqual_IntInt)
            goto Label_716;
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        goto Label_642;
    
        Label_573:
        adjacentCards = TArray<adjacentCards>();
    
        return;
    
        Label_610:
        adjacentCards = _adjacentCards;
    
        return;
    
        Label_642:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_244;
    
        Label_716:
        CallFunc_Array_Get_Item = CallFunc_FetchCardsByLocation_AllCardsInLocation[Temp_int_Array_Index_Variable];
    
        cardToCheck = CallFunc_Array_Get_Item;
    
        Subtract_IntInt = _locationNumber - 1;
    
        EqualEqual_IntInt_2 = cardToCheck->locationNumber == Subtract_IntInt;
    
        if (!EqualEqual_IntInt_2)
            goto Label_1156;
    
        _lowerCard = cardToCheck;
    
        IsValid = _lowerCard;
    
        if (!IsValid)
            goto Label_1513;
    
        _lowerCard->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        Not_PreBool_1 = !CallFunc_IsUnrevealedCovertCard_isIt;
    
        BooleanOR_1 = (Not_PreBool_1 || includeCovertCards);
    
        if (!BooleanOR_1)
            return;
    
        Array_Add_1 = _adjacentCards.Add(_lowerCard);
    
        return;
    
        Label_1156:
        Add_IntInt_1 = _locationNumber + 1;
    
        EqualEqual_IntInt_1 = cardToCheck->locationNumber == Add_IntInt_1;
    
        if (!EqualEqual_IntInt_1)
            return;
    
        _higherCard = cardToCheck;
    
        IsValid_1 = _higherCard;
    
        if (!IsValid_1)
            return;
    
        _higherCard->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt_1);
    
        Not_PreBool_2 = !CallFunc_IsUnrevealedCovertCard_isIt_1;
    
        BooleanOR = (Not_PreBool_2 || includeCovertCards);
    
        if (!BooleanOR)
            return;
    
        Array_Add = _adjacentCards.Add(_higherCard);
    
        return;
    
        Label_1513:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void FullyHealCard(class UBaseCardObject* card, int healerCardID, int& HealedAmount)
    {
        IsValid = card;
    
        if (!IsValid)
            goto Label_332;
    
        card->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        Greater_IntInt = (CallFunc_getTotalDefense_totalDefense > 0);
    
        if (!Greater_IntInt)
            goto Label_332;
    
        card->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        Subtract_IntInt = card->maxDefense - CallFunc_getTotalDefense_totalDefense_1;
    
        _toHeal = Subtract_IntInt;
    
        Greater_IntInt_1 = (_toHeal > 0);
    
        if (!Greater_IntInt_1)
            goto Label_1761;
    
        goto Label_360;
    
        Label_332:
        HealedAmount = 0;
    
        return;
    
        Label_360:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_828;
    
        FetchAllCardsWithEventTrigger(0xC, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_464:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_1816;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnBeforeFullyRepaired(card, CallFunc_OnBeforeFullyRepaired_stopAction);
    
        if (!CallFunc_OnBeforeFullyRepaired_stopAction)
            goto Label_754;
    
        HealedAmount = 0;
    
        return;
    
        Label_754:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_464;
    
        Label_828:
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        card->setAndEncryptDefense(card->maxDefense, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_1729;
    
        CardFunctionsNotifier->NotifyHealCard(card->cardID, _toHeal, healerCardID);
    
        goto Label_1646;
    
        Label_1097:
        FetchAllCardsWithEventTrigger(0x2C, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1168:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt_1)
            goto Label_1097;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        NotEqual_IntInt = (CallFunc_Array_Get_Item_1->cardID !== card->cardID);
    
        if (!NotEqual_IntInt)
            goto Label_1572;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_1->OnOtherCardFullyRepaired(card, _toHeal);
    
        goto Label_1789;
    
        Label_1572:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_1168;
    
        Label_1646:
        if (!card->isSuppressed)
            goto Label_1683;
    
        return;
    
        Label_1683:
        card->OnFullyRepaired(_toHeal);
    
        return;
    
        Label_1729:
        HealedAmount = _toHeal;
    
        return;
    
        Label_1761:
        HealedAmount = 0;
    
        return;
    
        Label_1789:
        HealedAmount = _toHeal;
    
        Label_1816:
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void DestroyCard(class UBaseCardObject* card, class UBaseCardObject* destroyerCard)
    {
        IsValid = card;
    
        if (!IsValid)
            return;
    
        IsValid_1 = destroyerCard;
    
        if (!IsValid_1)
            goto Label_408;
    
        _destroyerID = destroyerCard->cardID;
    
        Label_135:
        _cardID = card->cardID;
    
        _location = card->location;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_367;
    
        ExecuteOnBeforeOtherCardDestroyed(_cardID, _destroyerID, false, false);
    
        CardFunctionsNotifier->NotifyDestroyUnit(_cardID, _destroyerID, _location);
    
        Label_367:
        ApplyRemoveCardFromBoard(_cardID, _destroyerID, true, false, false, false);
    
        return;
    
        Label_408:
        _destroyerID = 0;
    
        goto Label_135;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void DamageCard(class UBaseCardObject* card, int amount, int damagerCardID, bool isRedirected, bool fromFight, bool isFightDefenderDamage, bool& targetDestroyed)
    {
        IsValid = card;
    
        if (!IsValid)
            goto Label_409;
    
        GetCardFromID(damagerCardID, CallFunc_GetCardFromID_card);
    
        damageDealer = CallFunc_GetCardFromID_card;
    
        card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            goto Label_425;
    
        if (!isRedirected)
            goto Label_690;
    
        tmpDamage = amount;
    
        Label_190:
        ExecuteOnDealDamageAddDamageAfterCalc(card, damageDealer, tmpDamage, false, false, isRedirected, CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage);
    
        ApplyDamageToCard(card, damageDealer, CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage, isRedirected, isFightDefenderDamage);
    
        card->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        LessEqual_IntInt = (CallFunc_getTotalDefense_totalDefense <= 0);
    
        targetDestroyed = LessEqual_IntInt;
    
        return;
    
        Label_409:
        targetDestroyed = false;
    
        return;
    
        Label_425:
        Conv_NameToString = FString(damageDealer->name);
    
        Concat_StrStr = Conv_NameToString += " is trying to deal damage to a card that is not on the board, better to check";
    
        UKismetSystemLibrary::PrintString(this, Concat_StrStr, true, true, FLinearColor(1, 0.802207, 0, 1), 60, "None");
    
        targetDestroyed = false;
    
        return;
    
        Label_690:
        ExecuteOnDealDamageAddDamage(damageDealer, card, amount, false, fromFight, false, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage);
    
        tmpDamage = CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage;
    
        goto Label_190;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ShowNotification(ESideEnum sideToShow, FText*& text)
    {
        GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        EqualEqual_ByteByte = ((!sideToShow) == (!CallFunc_GetClientSide_OutClientSide));
    
        if (!EqualEqual_ByteByte)
            return;
    
        CardFunctionsNotifier->NotifyBigNotify(text);
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void PinUnit(int cardID, int instigatorID)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_169;
    
        _card->HasCustomAbility("cantBePinned", CallFunc_HasCustomAbility_doesIt);
    
        if (!CallFunc_HasCustomAbility_doesIt)
            goto Label_174;
    
        goto Label_1753;
    
        Label_169:
        return;
    
        Label_174:
        _card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            return;
    
        _card->IsUnit(CallFunc_IsUnit_isIt);
    
        if (!CallFunc_IsUnit_isIt)
            return;
    
        Temp_string_Variable = "pinned";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_613;
    
        Temp_string_Variable = "pinned";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        Array_Contains = CallFunc_Map_Find_Value.cardsGivingAbility[instigatorID];
    
        if (!Array_Contains)
            goto Label_1595;
    
        goto Label_883;
    
        Label_613:
        Array_Add = localInstigatorArry.Add(instigatorID);
    
        ChangeBuffsFromCards(_card, 1, instigatorID, 0x6, 0x8, "pinned", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = localInstigatorArry;
    
        Temp_string_Variable_1 = "pinned";
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        return;
    
        Label_883:
        _card->IsSideActive(_card->side, CallFunc_IsSideActive_active);
    
        SelectInt = (CallFunc_IsSideActive_active ? 3 : 2);
    
        Max = ((_card->pinnedTurns > SelectInt) ? _card->pinnedTurns : SelectInt);
    
        _card->pinnedTurns = Max;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyPinUnit(cardID, instigatorID);
    
        FetchAllCardsWithEventTrigger(0x3D, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1277:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherUnitPinned(_card);
    
        goto Label_1521;
    
        Label_1521:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1277;
    
        Label_1595:
        Temp_string_Variable = "pinned";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        localInstigatorArry = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        goto Label_613;
    
        Label_1753:
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void MoveUnitFromBoardToOwnersHand(class UBaseCardObject* card, int instigatorID)
    {
        card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        card->IsUnit(CallFunc_IsUnit_isIt);
    
        BooleanAND = CallFunc_IsUnit_isIt && CallFunc_IsLocatedOnBoard_isIt;
    
        if (!BooleanAND)
            goto Label_341;
    
        GetHandLocationBySide(card->originalSide, CallFunc_GetHandLocationBySide_handLocation);
    
        tmpNewLocation = CallFunc_GetHandLocationBySide_handLocation;
    
        tmpOldLocation = card->location;
    
        MoveCardFromBoardToOwnersHand(card->cardID, instigatorID, tmpOldLocation, tmpNewLocation);
    
        return;
    
        Label_341:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("MoveUnitFromBoardToOwnersHand: Card must be a unit and located on the board", this);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void SpawnCardInFrontline(FName card_name, ESideEnum side, int spawnerID, FText*& campaignName, bool giveBlitz, int& spawnedCardID, EFactionEnum salvageFaction, int locationNumber, bool makeVeteran)
    {
        TextIsEmpty = UKismetTextLibrary::TextIsEmpty(campaignName);
    
        if (!TextIsEmpty)
            goto Label_291;
    
        Label_43:
        Greater_IntInt = (spawnerID > 0);
    
        if (!Greater_IntInt)
            goto Label_164;
    
        GetCardFromID(spawnerID, CallFunc_GetCardFromID_card);
    
        gold = CallFunc_GetCardFromID_card->isGoldCard;
    
        Label_164:
        SpawnCardToBoard(card_name, side, 0x7, locationNumber, 0, gold, giveBlitz, spawnerID, 0x0, makeVeteran, CallFunc_SpawnCardToBoard_cardSpawnedID);
    
        spawnedCardID = CallFunc_SpawnCardToBoard_cardSpawnedID;
    
        return;
    
        Label_291:
        UFunctionLibrary::SetStaticCampaignName(card_name, campaignName);
    
        goto Label_43;
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveSmokescreen(int cardID, int giverID, bool RemoveAllGivers, bool skipAction)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _cardFromID = CallFunc_GetCardFromID_card;
    
        IsValid = _cardFromID;
    
        if (!IsValid)
            goto Label_917;
    
        LessEqual_IntInt = (giverID <= 0);
    
        BooleanOR = (LessEqual_IntInt || RemoveAllGivers);
    
        if (!BooleanOR)
            goto Label_997;
    
        _cardFromID->getHasSmokescreen(CallFunc_getHasSmokescreen_doesIt_1);
    
        if (!CallFunc_getHasSmokescreen_doesIt_1)
            goto Label_2876;
    
        Temp_string_Variable_2 = "smokescreen";
    
        Map_Find = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_2081;
    
        Temp_string_Variable_2 = "smokescreen";
    
        Map_Find = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value);
    
        _cardsGivingSmokescreen = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingSmokescreen[giverID];
    
        if (!Array_Contains)
            goto Label_2189;
    
        Label_609:
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_655:
        Array_Length_1 = _cardsGivingSmokescreen.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_1930;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = _cardsGivingSmokescreen[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_cardFromID, -1, CallFunc_Array_Get_Item_1, 0x6, 0x8, "smokescreen", CallFunc_ChangeBuffsFromCards_amountRemoved_2);
    
        goto Label_2385;
    
        Label_917:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("RemoveSmokescreen must have a valid card", this);
    
        return;
    
        Label_997:
        Temp_string_Variable_1 = "smokescreen";
    
        Map_Find_1 = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable_1, CallFunc_Map_Find_Value_1);
    
        Array_Contains_1 = CallFunc_Map_Find_Value_1.cardsGivingAbility[giverID];
    
        if (!Array_Contains_1)
            return;
    
        Temp_string_Variable_1 = "smokescreen";
    
        Map_Find_1 = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable_1, CallFunc_Map_Find_Value_1);
    
        _cardsGivingSmokescreen = CallFunc_Map_Find_Value_1.cardsGivingAbility;
    
        Array_RemoveItem = _cardsGivingSmokescreen.Remove(giverID);
    
        if (!Array_RemoveItem)
            goto Label_1812;
    
        ChangeBuffsFromCards(_cardFromID, -1, giverID, 0x6, 0x8, "smokescreen", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        Temp_string_Variable = "smokescreen";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingSmokescreen;
    
        Map_Add(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable, MakeStruct_CardsGivingAbility);
    
        Label_1641:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        if (!skipAction)
            goto Label_1744;
    
        Label_1688:
        _cardFromID->getHasSmokescreen(CallFunc_getHasSmokescreen_doesIt);
    
        if (!CallFunc_getHasSmokescreen_doesIt)
            goto Label_2459;
    
        return;
    
        Label_1744:
        CardFunctionsNotifier->NotifyRemoveSmokeScreen(cardID, giverID, RemoveAllGivers);
    
        goto Label_1688;
    
        Label_1812:
        UKismetSystemLibrary::PrintString(this, "Removing smokescreen but map array doesn't have it", true, true, FLinearColor(1, 0, 0.013262, 1), 555, "None");
    
        return;
    
        Label_1930:
        _cardFromID->hasSmokescreen = false;
    
        Temp_string_Variable_3 = "smokescreen";
    
        Map_Remove = _cardFromID->receivedAbilitiesFromCards.Remove(Temp_string_Variable_3);
    
        goto Label_1641;
    
        Label_2081:
        Greater_IntInt_1 = (giverID > 0);
    
        if (!Greater_IntInt_1)
            return;
    
        ChangeBuffsFromCards(_cardFromID, -1, giverID, 0x6, 0x8, "smokescreen", CallFunc_ChangeBuffsFromCards_amountRemoved_3);
    
        return;
    
        Label_2189:
        Greater_IntInt = (giverID > 0);
    
        if (!Greater_IntInt)
            goto Label_609;
    
        GetStaticCard = UFunctionLibrary::GetStaticCard(_cardFromID->name);
    
        if (!GetStaticCard->hasSmokescreen)
            return;
    
        ChangeBuffsFromCards(_cardFromID, -1, giverID, 0x6, 0x8, "smokescreen", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        return;
    
        Label_2385:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_655;
    
        Label_2459:
        FetchAllCardsWithEventTrigger(0x30, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_2530:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_2852;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item->OnOtherCardLoseSmokescreen(_cardFromID);
    
        goto Label_2778;
    
        Label_2778:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_2530;
    
        Label_2852:
        ExecuteOnOtherCardsAbilitiesChanged(_cardFromID);
    
        return;
    
        Label_2876:
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveGuard(int cardID, int instigatorID, bool skipAction, bool RemoveAllGivers)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_899;
    
        LessEqual_IntInt = (instigatorID <= 0);
    
        BooleanOR = (LessEqual_IntInt || RemoveAllGivers);
    
        if (!BooleanOR)
            goto Label_973;
    
        _card->getHasGuard(CallFunc_getHasGuard_doesIt);
    
        if (!CallFunc_getHasGuard_doesIt)
            goto Label_2423;
    
        Temp_string_Variable_2 = "guard";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_2003;
    
        Temp_string_Variable_2 = "guard";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value);
    
        Cards Giving Guard = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = Cards Giving Guard[instigatorID];
    
        if (!Array_Contains)
            goto Label_2105;
    
        Label_597:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_643:
        Array_Length = Cards Giving Guard.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1516;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = Cards Giving Guard[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "guard", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_2212;
    
        Label_899:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("RemoveGuard must have a valid card", this);
    
        return;
    
        Label_973:
        Temp_string_Variable = "guard";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value_1);
    
        Array_Contains_1 = CallFunc_Map_Find_Value_1.cardsGivingAbility[instigatorID];
    
        if (!Array_Contains_1)
            return;
    
        Temp_string_Variable = "guard";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value_1);
    
        Cards Giving Guard = CallFunc_Map_Find_Value_1.cardsGivingAbility;
    
        Array_RemoveItem = Cards Giving Guard.Remove(instigatorID);
    
        if (!Array_RemoveItem)
            goto Label_1891;
    
        ChangeBuffsFromCards(_card, -1, instigatorID, 0x6, 0x8, "guard", CallFunc_ChangeBuffsFromCards_amountRemoved_2);
    
        Array_IsEmpty = Array_IsEmpty(Cards Giving Guard);
    
        if (!Array_IsEmpty)
            goto Label_1744;
    
        Label_1516:
        _card->hasGuard = false;
    
        Temp_string_Variable_3 = "guard";
    
        Map_Remove = _card->receivedAbilitiesFromCards.Remove(Temp_string_Variable_3);
    
        Label_1656:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1707;
    
        if (!skipAction)
            goto Label_2286;
    
        Label_1707:
        if (!_card->hasGuard)
            goto Label_2354;
    
        return;
    
        Label_1744:
        Temp_string_Variable_1 = "guard";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = Cards Giving Guard;
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_1656;
    
        Label_1891:
        UKismetSystemLibrary::PrintString(this, "Removing guard but map array doesn't have it", true, true, FLinearColor(1, 0, 0.013262, 1), 555, "None");
    
        return;
    
        Label_2003:
        Greater_IntInt_1 = (instigatorID > 0);
    
        if (!Greater_IntInt_1)
            return;
    
        ChangeBuffsFromCards(_card, -1, instigatorID, 0x6, 0x8, "guard", CallFunc_ChangeBuffsFromCards_amountRemoved_3);
    
        return;
    
        Label_2105:
        Greater_IntInt = (instigatorID > 0);
    
        if (!Greater_IntInt)
            goto Label_597;
    
        ChangeBuffsFromCards(_card, -1, instigatorID, 0x6, 0x8, "guard", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        return;
    
        Label_2212:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_643;
    
        Label_2286:
        CardFunctionsNotifier->NotifyRemoveGuard(cardID, instigatorID, RemoveAllGivers);
    
        goto Label_1707;
    
        Label_2354:
        UpdateGuarded(_card->location);
    
        ExecuteOnOtherCardsAbilitiesChanged(_card);
    
        return;
    
        Label_2423:
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveAmbush(int cardID, int giverID, bool skipAction, bool removeAllGivers)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _cardFromID = CallFunc_GetCardFromID_card;
    
        IsValid = _cardFromID;
    
        if (!IsValid)
            goto Label_902;
    
        LessEqual_IntInt = (giverID <= 0);
    
        BooleanOR = (LessEqual_IntInt || removeAllGivers);
    
        if (!BooleanOR)
            goto Label_977;
    
        _cardFromID->getHasAmbush(CallFunc_getHasAmbush_doesIt);
    
        if (!CallFunc_getHasAmbush_doesIt)
            goto Label_2204;
    
        Temp_string_Variable_2 = "ambush";
    
        Map_Find = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1919;
    
        Temp_string_Variable_2 = "ambush";
    
        Map_Find = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value);
    
        _cardsGivingAmbush = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingAmbush[giverID];
    
        if (!Array_Contains)
            goto Label_2022;
    
        Label_599:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_645:
        Array_Length = _cardsGivingAmbush.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1773;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = _cardsGivingAmbush[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_cardFromID, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "ambush", CallFunc_ChangeBuffsFromCards_amountRemoved_2);
    
        goto Label_2130;
    
        Label_902:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("RemoveAmbush must have a valid card", this);
    
        return;
    
        Label_977:
        Temp_string_Variable = "ambush";
    
        Map_Find_1 = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value_1);
    
        Array_Contains_1 = CallFunc_Map_Find_Value_1.cardsGivingAbility[giverID];
    
        if (!Array_Contains_1)
            return;
    
        Temp_string_Variable = "ambush";
    
        Map_Find_1 = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value_1);
    
        _cardsGivingAmbush = CallFunc_Map_Find_Value_1.cardsGivingAbility;
    
        Array_RemoveItem = _cardsGivingAmbush.Remove(giverID);
    
        if (!Array_RemoveItem)
            return;
    
        ChangeBuffsFromCards(_cardFromID, -1, giverID, 0x6, 0x8, "ambush", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        Temp_string_Variable_1 = "ambush";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingAmbush;
    
        Map_Add(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        Label_1597:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_1648;
    
        if (!skipAction)
            goto Label_1705;
    
        Label_1648:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        ExecuteOnOtherCardsAbilitiesChanged(_cardFromID);
    
        return;
    
        Label_1705:
        CardFunctionsNotifier->NotifyRemoveAmbush(cardID, giverID, removeAllGivers);
    
        goto Label_1648;
    
        Label_1773:
        _cardFromID->hasAmbush = false;
    
        Temp_string_Variable_3 = "ambush";
    
        Map_Remove = _cardFromID->receivedAbilitiesFromCards.Remove(Temp_string_Variable_3);
    
        goto Label_1597;
    
        Label_1919:
        Greater_IntInt_1 = (giverID > 0);
    
        if (!Greater_IntInt_1)
            return;
    
        ChangeBuffsFromCards(_cardFromID, -1, giverID, 0x6, 0x8, "ambush", CallFunc_ChangeBuffsFromCards_amountRemoved_3);
    
        return;
    
        Label_2022:
        Greater_IntInt = (giverID > 0);
    
        if (!Greater_IntInt)
            goto Label_599;
    
        ChangeBuffsFromCards(_cardFromID, -1, giverID, 0x6, 0x8, "ambush", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        return;
    
        Label_2130:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_645;
    
        Label_2204:
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void PersistCustomFields(int cardID, bool refreshEffectBar)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CardFunctionsNotifier->NotifyPersistCustomFields(cardID, CallFunc_GetCardFromID_card->customName1, CallFunc_GetCardFromID_card->customName2, refreshEffectBar, CallFunc_GetCardFromID_card->customJson);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void MakeCardRetreat(const TArray<class UBaseCardObject*>*& cards, int instigatorID)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Array_Length = cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_322;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->HasCustomAbility("cantRetreat", CallFunc_HasCustomAbility_doesIt);
    
        if (!CallFunc_HasCustomAbility_doesIt)
            goto Label_678;
    
        goto Label_604;
    
        Label_322:
        Array_Length_2 = _supportLineCards.Length;
    
        Greater_IntInt_1 = (Array_Length_2 > 0);
    
        if (!Greater_IntInt_1)
            goto Label_468;
    
        ApplyMakeCardRetreat(_supportLineCards, instigatorID);
    
        goto Label_1060;
    
        Label_468:
        Array_Length_1 = _frontLineCards.Length;
    
        Greater_IntInt = (Array_Length_1 > 0);
    
        if (!Greater_IntInt)
            goto Label_1060;
    
        ApplyMakeCardRetreat(_frontLineCards, instigatorID);
    
        return;
    
        Label_604:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_678:
        CallFunc_Array_Get_Item = cards[Temp_int_Array_Index_Variable];
    
        EqualEqual_ByteByte = ((!CallFunc_Array_Get_Item->location) == (!0x7));
    
        if (!EqualEqual_ByteByte)
            goto Label_932;
    
        CallFunc_Array_Get_Item = cards[Temp_int_Array_Index_Variable];
    
        Array_Add_1 = _frontLineCards.Add(CallFunc_Array_Get_Item);
    
        return;
    
        Label_932:
        CallFunc_Array_Get_Item = cards[Temp_int_Array_Index_Variable];
    
        Array_Add = _supportLineCards.Add(CallFunc_Array_Get_Item);
    
        return;
    
        Label_1060:
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveSmokescreen(int cardID, int giverID)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CardToGive = CallFunc_GetCardFromID_card;
    
        IsValid = CardToGive;
    
        if (!IsValid)
            goto Label_561;
    
        CanCardBeBuffed(CardToGive, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            return;
    
        Greater_IntInt = (giverID > 0);
    
        if (!Greater_IntInt)
            goto Label_643;
    
        Temp_string_Variable = "smokescreen";
    
        Map_Find = Map_Find(CardToGive->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_930;
    
        Temp_string_Variable = "smokescreen";
    
        Map_Find = Map_Find(CardToGive->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        _cardsGivingSmokescreen = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingSmokescreen[giverID];
    
        if (!Array_Contains)
            goto Label_930;
    
        return;
    
        Label_561:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("giveSmokescreen must have a valid card", this);
    
        return;
    
        Label_643:
        if (!CardToGive->hasSmokescreen)
            goto Label_684;
    
        return;
    
        Label_684:
        CardToGive->hasSmokescreen = true;
    
        Label_717:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_809;
    
        CardToGive->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        if (!CallFunc_IsLocatedInDeck_isIt)
            goto Label_871;
    
        Label_809:
        RemoveGuard(cardID, cardID, false, true);
    
        ExecuteOnOtherCardsAbilitiesChanged(CardToGive);
    
        return;
    
        Label_871:
        CardFunctionsNotifier->NotifyGiverSmokeScreen(cardID, giverID);
    
        goto Label_809;
    
        Label_930:
        Array_Add = _cardsGivingSmokescreen.Add(giverID);
    
        ChangeBuffsFromCards(CardToGive, 1, giverID, 0x6, 0x8, "smokescreen", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingSmokescreen;
    
        Temp_string_Variable_1 = "smokescreen";
    
        Map_Add(CardToGive->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_717;
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveGuard(int cardID, int instigatorID)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _cardToGive = CallFunc_GetCardFromID_card;
    
        IsValid = _cardToGive;
    
        if (!IsValid)
            goto Label_549;
    
        CanCardBeBuffed(_cardToGive, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            return;
    
        Greater_IntInt = (instigatorID > 0);
    
        if (!Greater_IntInt)
            goto Label_625;
    
        Temp_string_Variable = "guard";
    
        Map_Find = Map_Find(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1142;
    
        Temp_string_Variable = "guard";
    
        Map_Find = Map_Find(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        Cards Giving Guard = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = Cards Giving Guard[instigatorID];
    
        if (!Array_Contains)
            goto Label_1142;
    
        return;
    
        Label_549:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("GiveGuard must have a valid card", this);
    
        return;
    
        Label_625:
        if (!_cardToGive->hasGuard)
            goto Label_817;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        _cardToGive->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        if (!CallFunc_IsLocatedInDeck_isIt)
            goto Label_758;
    
        Label_753:
        return;
    
        Label_758:
        CardFunctionsNotifier->NotifyGiveGuard(cardID, instigatorID);
    
        goto Label_753;
    
        Label_817:
        _cardToGive->hasGuard = true;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_1058;
    
        _cardToGive->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        if (!CallFunc_IsLocatedInDeck_isIt)
            goto Label_1004;
    
        RemoveSmokescreen(cardID, instigatorID, true, true);
    
        Label_976:
        ExecuteOnOtherCardsAbilitiesChanged(_cardToGive);
    
        return;
    
        Label_1004:
        CardFunctionsNotifier->NotifyGiveGuard(cardID, instigatorID);
    
        Label_1058:
        UpdateGuarded(_cardToGive->location);
    
        RemoveSmokescreen(cardID, instigatorID, true, false);
    
        goto Label_976;
    
        Label_1142:
        Array_Add = Cards Giving Guard.Add(instigatorID);
    
        ChangeBuffsFromCards(_cardToGive, 1, instigatorID, 0x6, 0x8, "guard", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = Cards Giving Guard;
    
        Temp_string_Variable_1 = "guard";
    
        Map_Add(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_625;
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveFury(int cardID, int giverID)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _cardToGive = CallFunc_GetCardFromID_card;
    
        IsValid = _cardToGive;
    
        if (!IsValid)
            goto Label_602;
    
        CanCardBeBuffed(_cardToGive, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            return;
    
        Conv_IntToBool = (giverID != 0);
    
        if (!Conv_IntToBool)
            goto Label_677;
    
        _cardToGive->getHasFury(CallFunc_getHasFury_doesIt);
    
        alreadyHadFury = CallFunc_getHasFury_doesIt;
    
        Temp_string_Variable_1 = "fury";
    
        Map_Find = Map_Find(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable_1, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1273;
    
        Temp_string_Variable_1 = "fury";
    
        Map_Find = Map_Find(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable_1, CallFunc_Map_Find_Value);
    
        _cardsGivingFury = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingFury[giverID];
    
        if (!Array_Contains)
            goto Label_1273;
    
        return;
    
        Label_602:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("GiveFury must have a valid card", this);
    
        return;
    
        Label_677:
        if (!_cardToGive->hasFury)
            goto Label_718;
    
        return;
    
        Label_718:
        _cardToGive->hasFury = true;
    
        Label_751:
        GreaterEqual_IntInt = (_cardToGive->attackCountThisTurn >= 2);
    
        BooleanOR = (alreadyHadFury || GreaterEqual_IntInt);
    
        if (!BooleanOR)
            goto Label_979;
    
        Label_859:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_951;
    
        _cardToGive->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        if (!CallFunc_IsLocatedInDeck_isIt)
            goto Label_1543;
    
        Label_951:
        ExecuteOnOtherCardsAbilitiesChanged(_cardToGive);
    
        return;
    
        Label_979:
        EqualEqual_IntInt = _cardToGive->attackCountThisTurn == 1;
    
        _cardToGive->HasAttackLeft(CallFunc_HasAttackLeft_doesIt);
    
        BooleanOR_1 = (CallFunc_HasAttackLeft_doesIt || EqualEqual_IntInt);
    
        if (!BooleanOR_1)
            goto Label_859;
    
        Add_IntInt = _cardToGive->attackLeft + 1;
    
        Temp_int_Variable = Add_IntInt;
    
        _cardToGive->attackLeft = Temp_int_Variable;
    
        goto Label_859;
    
        Label_1273:
        Array_Add = _cardsGivingFury.Add(giverID);
    
        ChangeBuffsFromCards(_cardToGive, 1, giverID, 0x6, 0x8, "fury", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        Temp_string_Variable = "fury";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingFury;
    
        Map_Add(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable, MakeStruct_CardsGivingAbility);
    
        goto Label_751;
    
        Label_1543:
        CardFunctionsNotifier->NotifyGiveFury(cardID, giverID);
    
        goto Label_951;
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveBlitz(int cardID, int giverID)
    {
        _alreadyHadBlitz = false;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _cardToGive = CallFunc_GetCardFromID_card;
    
        IsValid = _cardToGive;
    
        if (!IsValid)
            goto Label_615;
    
        CanCardBeBuffed(_cardToGive, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            return;
    
        _cardToGive->getHasBlitz(CallFunc_getHasBlitz_doesIt_1);
    
        _alreadyHadBlitz = CallFunc_getHasBlitz_doesIt_1;
    
        Conv_IntToBool = (giverID != 0);
    
        if (!Conv_IntToBool)
            goto Label_691;
    
        Temp_string_Variable = "blitz";
    
        Map_Find = Map_Find(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1001;
    
        Temp_string_Variable = "blitz";
    
        Map_Find = Map_Find(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        _cardsGivingBlitz = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingBlitz[giverID];
    
        if (!Array_Contains)
            goto Label_1001;
    
        return;
    
        Label_615:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("GiveBlitz must have a valid card", this);
    
        return;
    
        Label_691:
        if (!_cardToGive->hasBlitz)
            goto Label_732;
    
        return;
    
        Label_732:
        _cardToGive->hasBlitz = true;
    
        Label_765:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_973;
    
        _cardToGive->getHasBlitz(CallFunc_getHasBlitz_doesIt);
    
        NotEqual_BoolBool = (CallFunc_getHasBlitz_doesIt !== _alreadyHadBlitz);
    
        if (!NotEqual_BoolBool)
            goto Label_918;
    
        ExecuteOnOtherCardsAbilitiesChanged(_cardToGive);
    
        Label_918:
        _cardToGive->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        if (!CallFunc_IsLocatedInDeck_isIt)
            goto Label_1273;
    
        Label_973:
        ExecuteOnOtherCardsAbilitiesChanged(_cardToGive);
    
        return;
    
        Label_1001:
        Array_Add = _cardsGivingBlitz.Add(giverID);
    
        ChangeBuffsFromCards(_cardToGive, 1, giverID, 0x6, 0x8, "blitz", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        Temp_string_Variable_1 = "blitz";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingBlitz;
    
        Map_Add(_cardToGive->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_765;
    
        Label_1273:
        CardFunctionsNotifier->NotifyGiveBlitz(cardID, giverID);
    
        goto Label_973;
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveAmbush(int cardID, int giverID)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _cardFromID = CallFunc_GetCardFromID_card;
    
        IsValid = _cardFromID;
    
        if (!IsValid)
            goto Label_546;
    
        CanCardBeBuffed(_cardFromID, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_546;
    
        Conv_IntToBool = (giverID != 0);
    
        if (!Conv_IntToBool)
            goto Label_551;
    
        Temp_string_Variable = "ambush";
    
        Map_Find = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_826;
    
        Temp_string_Variable = "ambush";
    
        Map_Find = Map_Find(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        _cardsGivingAmbush = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingAmbush[giverID];
    
        if (!Array_Contains)
            goto Label_826;
    
        return;
    
        Label_546:
        return;
    
        Label_551:
        if (!_cardFromID->hasAmbush)
            goto Label_592;
    
        return;
    
        Label_592:
        _cardFromID->hasAmbush = true;
    
        Label_625:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_717;
    
        _cardFromID->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        if (!CallFunc_IsLocatedInDeck_isIt)
            goto Label_745;
    
        Label_717:
        ExecuteOnOtherCardsAbilitiesChanged(_cardFromID);
    
        return;
    
        Label_745:
        CardFunctionsNotifier->NotifyGiveAmbush(_cardFromID->cardID, giverID);
    
        goto Label_717;
    
        Label_826:
        Array_Add = _cardsGivingAmbush.Add(giverID);
    
        ChangeBuffsFromCards(_cardFromID, 1, giverID, 0x6, 0x8, "ambush", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingAmbush;
    
        Temp_string_Variable_1 = "ambush";
    
        Map_Add(_cardFromID->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_625;
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GainKreditSlot(class UBaseCardObject* cardGivingKreditSlot, ESideEnum side)
    {
        oldKredits = 0;
    
        ChangeKreditSlotsBySide(side, 1, cardGivingKreditSlot->cardID);
    
        GameStateRef->getMaxPossibleKredits(CallFunc_getMaxPossibleKredits_outputMax);
    
        Less_IntInt_1 = (oldKredits < CallFunc_getMaxPossibleKredits_outputMax);
    
        if (!Less_IntInt_1)
            goto Label_537;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        _cardsToTrigger = CallFunc_GetAllCardInBattle_AllCardsInBattle;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_298:
        Array_Length = _cardsToTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_542;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = _cardsToTrigger[Temp_int_Array_Index_Variable];
    
        if (!CallFunc_Array_Get_Item->isSuppressed)
            goto Label_621;
    
        goto Label_547;
    
        Label_537:
        return;
    
        Label_542:
        return;
    
        Label_547:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_298;
    
        Label_621:
        CallFunc_Array_Get_Item = _cardsToTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnAfterExtraKreditSlotGain(cardGivingKreditSlot, side, false);
    
        goto Label_736;
    
        Label_736:
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void LoseKreditSlot(ESideEnum side)
    {
        ChangeKreditSlotsBySide(side, -1, 0);
    
        GameStateRef->updateKreditSlotsLostBySide(side, -1);
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        _cardsToTrigger = CallFunc_GetAllCardInBattle_AllCardsInBattle;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_206:
        Array_Length = _cardsToTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_622;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = _cardsToTrigger[Temp_int_Array_Index_Variable];
    
        if (!CallFunc_Array_Get_Item->isSuppressed)
            goto Label_515;
    
        goto Label_441;
    
        Label_441:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_206;
    
        Label_515:
        CallFunc_Array_Get_Item = _cardsToTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnAfterExtraKreditSlotGain(nullptr, side, true);
    
        return;
    
        Label_622:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void SpawnNextToCard(FName card_name, int spawnerId, ESideEnum side, int& spawnedCardID, bool copySpawnerAttack, bool copySpawnerDefense, EFactionEnum salvageFaction, bool makeVeteran)
    {
        spawnedCard = 0;
    
        GetCardFromID(spawnerId, CallFunc_GetCardFromID_card);
    
        spawnerCardRef = CallFunc_GetCardFromID_card;
    
        Add_IntInt = spawnerCardRef->locationNumber + 1;
    
        SpawnCardToBoard(card_name, spawnerCardRef->side, spawnerCardRef->location, Add_IntInt, 0, spawnerCardRef->isGoldCard, false, spawnerId, salvageFaction, makeVeteran, CallFunc_SpawnCardToBoard_cardSpawnedID);
    
        spawnedCard = CallFunc_SpawnCardToBoard_cardSpawnedID;
    
        if (!copySpawnerAttack)
            goto Label_559;
    
        GetCardFromID(spawnedCard, CallFunc_GetCardFromID_card_1);
    
        CallFunc_GetCardFromID_card_1->getAndDecryptAttack(CallFunc_getAndDecryptAttack_decryptedAttack);
    
        spawnerCardRef->getAndDecryptAttack(CallFunc_getAndDecryptAttack_decryptedAttack_1);
    
        Subtract_IntInt = CallFunc_getAndDecryptAttack_decryptedAttack_1 - CallFunc_getAndDecryptAttack_decryptedAttack;
    
        ChangeAttack(CallFunc_GetCardFromID_card_1, spawnedCard, Subtract_IntInt, 0x1, false, CallFunc_ChangeAttack_qqq);
    
        Label_559:
        spawnedCardID = spawnedCard;
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void TakeControlOfEnemyUnit(class UBaseCardObject* card, int instigatorID)
    {
        card->GetOppositeSide(CallFunc_GetOppositeSide_oppositeSide);
    
        ChangeUnitOwnership(card->cardID, instigatorID, card->side, CallFunc_GetOppositeSide_oppositeSide, 0x0, false, 0x0, true);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GotchaTriggered(class UBaseCardObject* card, int instigatorID, bool stopFurtherCardActions, bool skipDiscardingOrder, bool& qqq)
    {
        TmpGotcha = card;
    
        TmpGotcha->gotchaActivated = 0;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        TmpGotcha->enterPlayOnTurn = CallFunc_GetTurnNumber_turnNumber;
    
        TmpGotcha->location = 0x8;
    
        GetHandLocationBySide = UCombatHelperFunctions::GetHandLocationBySide(TmpGotcha->side, this);
    
        RearrangeLocation(GetHandLocationBySide);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_492;
    
        Greater_IntInt = (TmpGotcha->cipher > 0);
    
        if (!Greater_IntInt)
            goto Label_1008;
    
        SetCardsSeenByCipher(TmpGotcha->cipher, TmpGotcha->cardID, TmpGotcha->side, CallFunc_SetCardsSeenByCipher_qqq);
    
        goto Label_1505;
    
        Label_492:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            return;
    
        CardFunctionsNotifier->NotifyGotchaTriggered(TmpGotcha->cardID, instigatorID, stopFurtherCardActions);
    
        FetchAllCardsWithEventTrigger(0x15, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_681:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnCounterMeasureTriggered(TmpGotcha, CallFunc_OnCounterMeasureTriggered_qqq);
    
        goto Label_934;
    
        Label_934:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_681;
    
        Label_1008:
        if (!stopFurtherCardActions)
            goto Label_1463;
    
        GameStateRef->SetStopFurtherActions(true);
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card_1);
    
        CallFunc_GetCardFromID_card_1->enterPlayOnTurn = 0;
    
        Label_1136:
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->IsOrder(CallFunc_IsOrder_isIt);
    
        BooleanAND = CallFunc_IsOrder_isIt && skipDiscardingOrder;
    
        if (!BooleanAND)
            return;
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card);
    
        JsonMakeBool = UBlueprintJsonLibrary::JsonMakeBool(skipDiscardingOrder);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(CallFunc_GetCardFromID_card->customJson, "cancelOrderRemove", JsonMakeBool);
    
        CallFunc_GetCardFromID_card->customJson = JsonMakeField;
    
        return;
    
        Label_1463:
        GameStateRef->SetStopFurtherActions(false);
    
        goto Label_1136;
    
        Label_1505:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveImmune(int cardID, int giverID, bool& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_519;
    
        CanCardBeBuffed(_card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            return;
    
        Conv_IntToBool = (giverID != 0);
    
        if (!Conv_IntToBool)
            goto Label_596;
    
        Temp_string_Variable = "immune";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_766;
    
        Temp_string_Variable = "immune";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        Array_Contains = CallFunc_Map_Find_Value.cardsGivingAbility[giverID];
    
        if (!Array_Contains)
            goto Label_1040;
    
        return;
    
        Label_519:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("GiveImmune must have a valid card", this);
    
        return;
    
        Label_596:
        if (!_card->isImmune)
            goto Label_637;
    
        return;
    
        Label_637:
        _card->isImmune = true;
    
        Label_670:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyGiveImmnue(cardID, giverID);
    
        return;
    
        Label_766:
        Array_Add = cardsGivingImmune.Add(giverID);
    
        ChangeBuffsFromCards(_card, 1, giverID, 0x6, 0x8, "immune", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        Temp_string_Variable_1 = "immune";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = cardsGivingImmune;
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_670;
    
        Label_1040:
        Temp_string_Variable = "immune";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        cardsGivingImmune = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        goto Label_766;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveImmune(int cardID, int giverID, bool& qqq, bool skipAction)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_786;
    
        LessEqual_IntInt = (giverID <= 0);
    
        if (!LessEqual_IntInt)
            goto Label_861;
    
        _card->getHasImmune(CallFunc_getHasImmune_doesIt);
    
        if (!CallFunc_getHasImmune_doesIt)
            goto Label_1804;
    
        Temp_string_Variable = "immune";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1584;
    
        Temp_string_Variable = "immune";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        cardsGivingImmune = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_529:
        Array_Length = cardsGivingImmune.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = cardsGivingImmune[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "immune", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_1730;
    
        Label_786:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("RemoveImmune must have a valid card", this);
    
        return;
    
        Label_861:
        Temp_string_Variable_2 = "immune";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        Array_Contains = CallFunc_Map_Find_Value_1.cardsGivingAbility[giverID];
    
        if (!Array_Contains)
            return;
    
        Temp_string_Variable_2 = "immune";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        cardsGivingImmune = CallFunc_Map_Find_Value_1.cardsGivingAbility;
    
        Array_RemoveItem = cardsGivingImmune.Remove(giverID);
    
        if (!Array_RemoveItem)
            return;
    
        ChangeBuffsFromCards(_card, -1, giverID, 0x6, 0x8, "immune", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        Temp_string_Variable_1 = "immune";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = cardsGivingImmune;
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        Label_1481:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        if (!skipAction)
            goto Label_1529;
    
        return;
    
        Label_1529:
        CardFunctionsNotifier->NotifyRemoveImmune(cardID, giverID);
    
        return;
    
        Label_1584:
        _card->isImmune = false;
    
        Temp_string_Variable_3 = "immune";
    
        Map_Remove = _card->receivedAbilitiesFromCards.Remove(Temp_string_Variable_3);
    
        goto Label_1481;
    
        Label_1730:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_529;
    
        Label_1804:
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void ReleaseControlOfEnemyUnit(class UBaseCardObject* card, int instigatorID, ECardLocationEnum originalLocation, ESideEnum originalSide)
    {
        card->GetOppositeSide(CallFunc_GetOppositeSide_oppositeSide);
    
        ChangeUnitOwnership(card->cardID, instigatorID, card->side, CallFunc_GetOppositeSide_oppositeSide, 0x0, true, originalLocation, true);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void IsLocationFull(ECardLocationEnum location, bool& isFull)
    {
        FetchCardsByLocation(location, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        isFull = CallFunc_FetchCardsByLocation_isLocationFull;
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveFury(int cardID, int giverID, bool skipAction)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_858;
    
        LessEqual_IntInt = (giverID <= 0);
    
        if (!LessEqual_IntInt)
            goto Label_931;
    
        _card->getHasFury(CallFunc_getHasFury_doesIt_1);
    
        if (!CallFunc_getHasFury_doesIt_1)
            goto Label_2365;
    
        Temp_string_Variable_3 = "fury";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_3, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_2092;
    
        Temp_string_Variable_3 = "fury";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_3, CallFunc_Map_Find_Value);
    
        _cardsGivingFury = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingFury[giverID];
    
        if (!Array_Contains)
            goto Label_2189;
    
        Label_557:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_603:
        Array_Length = _cardsGivingFury.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1948;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = _cardsGivingFury[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "fury", CallFunc_ChangeBuffsFromCards_amountRemoved_2);
    
        goto Label_2291;
    
        Label_858:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("RemoveFury must have a valid card", this);
    
        return;
    
        Label_931:
        Temp_string_Variable_2 = "fury";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        Array_Contains_1 = CallFunc_Map_Find_Value_1.cardsGivingAbility[giverID];
    
        if (!Array_Contains_1)
            return;
    
        Temp_string_Variable_2 = "fury";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        _cardsGivingFury = CallFunc_Map_Find_Value_1.cardsGivingAbility;
    
        Array_RemoveItem = _cardsGivingFury.Remove(giverID);
    
        if (!Array_RemoveItem)
            return;
    
        ChangeBuffsFromCards(_card, -1, giverID, 0x6, 0x8, "fury", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        Temp_string_Variable_1 = "fury";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingFury;
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        _card->getHasFury(CallFunc_getHasFury_doesIt);
    
        if (!CallFunc_getHasFury_doesIt)
            goto Label_1728;
    
        Label_1598:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        if (!skipAction)
            goto Label_1669;
    
        Label_1645:
        ExecuteOnOtherCardsAbilitiesChanged(_card);
    
        return;
    
        Label_1669:
        CardFunctionsNotifier->NotifyRemoveFury(cardID, giverID);
    
        goto Label_1645;
    
        Label_1728:
        Min = UKismetMathLibrary::Min(_card->attackLeft, 1);
    
        Conv_IntToBool = (_card->attackCountThisTurn != 0);
    
        SelectInt = (Conv_IntToBool ? 0 : Min);
    
        _card->attackLeft = SelectInt;
    
        goto Label_1598;
    
        Label_1948:
        _card->hasFury = false;
    
        Temp_string_Variable = "fury";
    
        Map_Remove = _card->receivedAbilitiesFromCards.Remove(Temp_string_Variable);
    
        goto Label_1728;
    
        Label_2092:
        Greater_IntInt_1 = (giverID > 0);
    
        if (!Greater_IntInt_1)
            return;
    
        ChangeBuffsFromCards(_card, -1, 0, 0x6, 0x8, "fury", CallFunc_ChangeBuffsFromCards_amountRemoved_3);
    
        return;
    
        Label_2189:
        Greater_IntInt = (giverID > 0);
    
        if (!Greater_IntInt)
            goto Label_557;
    
        ChangeBuffsFromCards(_card, -1, 0, 0x6, 0x8, "fury", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        return;
    
        Label_2291:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_603;
    
        Label_2365:
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void AddAttackUntilEndOfTurn(class UBaseCardObject* card, int instigatorID, int attackToAdd)
    {
        IsValid = card;
    
        if (!IsValid)
            return;
    
        NotEqual_IntInt = (attackToAdd !== 0);
    
        if (!NotEqual_IntInt)
            return;
    
        ChangeAttack(card, instigatorID, attackToAdd, 0x0, false, CallFunc_ChangeAttack_qqq);
    
        GameStateRef->AddBuffsToRemoveEndOfTurn(0x0, instigatorID);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void PlayCardDirectlyFromHand(class UBaseCardObject* card, bool toFrontline, int instigatorID, int& qqq, int locationNumber)
    {
        _oldLocation = 0x0;
    
        IsValid = card;
    
        if (!IsValid)
            goto Label_3487;
    
        _oldLocation = card->location;
    
        EqualEqual_ByteByte = ((!card->location) == (!0x4));
    
        EqualEqual_ByteByte_1 = ((!card->location) == (!0x3));
    
        BooleanOR = (EqualEqual_ByteByte_1 || EqualEqual_ByteByte);
    
        if (!BooleanOR)
            goto Label_909;
    
        card->IsGotcha(CallFunc_IsGotcha_isIt_3);
    
        if (!CallFunc_IsGotcha_isIt_3)
            goto Label_985;
    
        Greater_IntInt_1 = (card->gotchaActivated > 0);
    
        if (!Greater_IntInt_1)
            goto Label_1652;
    
        card->gotchaActivated = 0;
    
        Label_441:
        _newLocation = _oldLocation;
    
        Label_468:
        IsValid_1 = card->targetOverride;
    
        if (!IsValid_1)
            goto Label_2637;
    
        TargetOverrideID = card->targetOverride->cardID;
    
        Label_604:
        TmpCardID = card->cardID;
    
        card->IsGotcha(CallFunc_IsGotcha_isIt_2);
    
        if (!CallFunc_IsGotcha_isIt_2)
            goto Label_2665;
    
        TmpLocation = card->locationNumber;
    
        Label_757:
        CardFunctionsNotifier->NotifyPlayFromHand(TmpCardID, instigatorID, _newLocation, TmpLocation, TargetOverrideID, 0, TmpLocation, true);
    
        card->IsGotcha(CallFunc_IsGotcha_isIt_1);
    
        if (!CallFunc_IsGotcha_isIt_1)
            goto Label_2809;
    
        return;
    
        Label_909:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("PlayCardDirectly card is not in hand", this);
    
        return;
    
        Label_985:
        SwitchEnum_CmpSuccess = ((!card->side) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1517;
    
        SwitchEnum_CmpSuccess = ((!card->side) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1120;
    
        return;
    
        Label_1120:
        Temp_byte_Variable = 0x6;
    
        Temp_byte_Variable_1 = 0x7;
    
        Temp_bool_Variable = toFrontline;
    
        _newLocation = Temp_bool_Variable ? Temp_byte_Variable_1 : Temp_byte_Variable;
    
        Label_1250:
        IsLocationFull(_newLocation, CallFunc_IsLocationFull_isFull);
    
        if (!CallFunc_IsLocationFull_isFull)
            goto Label_1391;
    
        Label_1302:
        DiscardCardFromHand(card->cardID, 0, false, true, CallFunc_DiscardCardFromHand_success);
    
        qqq = 0;
    
        return;
    
        Label_1391:
        card->GetOppositeSide(CallFunc_GetOppositeSide_oppositeSide);
    
        DoesSideControlTheFrontline(CallFunc_GetOppositeSide_oppositeSide, CallFunc_DoesSideControlTheFrontline_doesHe);
    
        BooleanAND_2 = toFrontline && CallFunc_DoesSideControlTheFrontline_doesHe;
    
        if (!BooleanAND_2)
            goto Label_468;
    
        goto Label_1302;
    
        Label_1517:
        Temp_byte_Variable_2 = 0x5;
    
        Temp_byte_Variable_3 = 0x7;
    
        Temp_bool_Variable_1 = toFrontline;
    
        _newLocation = Temp_bool_Variable_1 ? Temp_byte_Variable_3 : Temp_byte_Variable_2;
    
        goto Label_1250;
    
        Label_1652:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1698:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_2487;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->IsGotcha(CallFunc_IsGotcha_isIt);
    
        EqualEqual_ByteByte_2 = ((!CallFunc_Array_Get_Item->side) == (!card->side));
    
        Greater_IntInt = (CallFunc_Array_Get_Item->gotchaActivated > _nextGotchaActivated);
    
        BooleanAND = Greater_IntInt && EqualEqual_ByteByte_2;
    
        BooleanAND_1 = BooleanAND && CallFunc_IsGotcha_isIt;
    
        if (!BooleanAND_1)
            goto Label_2413;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        _nextGotchaActivated = CallFunc_Array_Get_Item->gotchaActivated;
    
        return;
    
        Label_2413:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1698;
    
        Label_2487:
        Add_IntInt_1 = _nextGotchaActivated + 1;
    
        Temp_int_Variable = Add_IntInt_1;
    
        _nextGotchaActivated = Temp_int_Variable;
    
        card->gotchaActivated = _nextGotchaActivated;
    
        goto Label_441;
    
        Label_2637:
        TargetOverrideID = 0;
    
        goto Label_604;
    
        Label_2665:
        GreaterEqual_IntInt = (locationNumber >= 0);
    
        if (!GreaterEqual_IntInt)
            goto Label_2745;
    
        TmpLocation = locationNumber;
    
        goto Label_757;
    
        Label_2745:
        GetNextCardLocationNumber(_newLocation, CallFunc_GetNextCardLocationNumber_locationNumber);
    
        TmpLocation = CallFunc_GetNextCardLocationNumber_locationNumber;
    
        goto Label_757;
    
        Label_2809:
        CardLocationMoved(TmpCardID, instigatorID, _oldLocation, _newLocation, TmpLocation, TmpLocation, 0x8, false, false);
    
        JSON_Clear(card, "countdown_timer", CallFunc_JSON_Clear_found);
    
        if (!CallFunc_JSON_Clear_found)
            goto Label_3103;
    
        PersistCustomFields(card->cardID, false);
    
        goto Label_3077;
    
        Label_3002:
        card->getHasAlpine(CallFunc_getHasAlpine_doesIt);
    
        if (!CallFunc_getHasAlpine_doesIt)
            goto Label_3002;
    
        GiveAlpineBonus(card);
    
        return;
    
        Label_3077:
        ExecuteOnEnterPlayEvents(card, 0x2);
    
        return;
    
        Label_3103:
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        card->enterPlayOnTurn = CallFunc_GetTurnNumber_turnNumber;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        UFunctionLibrary::GetStaticKredits(card->name, CallFunc_GetStaticKredits_kredits);
    
        Min = UKismetMathLibrary::Min(3, CallFunc_GetStaticKredits_kredits);
    
        SelectInt = (card->isSalvaged ? Min : CallFunc_GetStaticKredits_kredits);
    
        card->setAndEncryptKredit(SelectInt, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        card->cardSeen = false;
    
        return;
    
        Label_3487:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void DiscardCardFromHand(int cardID, int discarderID, bool skipSubAction, bool ForceDiscard, bool& success)
    {
        Greater_IntInt = (cardID > 0);
    
        if (!Greater_IntInt)
            goto Label_764;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        tmpCardToDiscard = CallFunc_GetCardFromID_card;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_196;
    
        tmpCardToDiscard->IsLocatedInHand(CallFunc_IsLocatedInHand_isIt);
    
        if (!CallFunc_IsLocatedInHand_isIt)
            goto Label_764;
    
        Label_196:
        oldLocation = tmpCardToDiscard->location;
    
        if (!ForceDiscard)
            goto Label_780;
    
        Label_259:
        SetCardLocationAndLocNumber(cardID, 0x8, 0);
    
        RearrangeLocation(oldLocation);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_2);
    
        if (!CallFunc_IsActionProcess_ActionProcess_2)
            goto Label_363;
    
        if (!skipSubAction)
            goto Label_1050;
    
        Label_363:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_1120;
    
        if (!tmpCardToDiscard->isSuppressed)
            goto Label_1136;
    
        Label_436:
        FetchAllCardsWithEventTrigger(0x29, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_507:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1186;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardDiscarded(tmpCardToDiscard, discarderID);
    
        goto Label_1202;
    
        Label_764:
        success = false;
    
        return;
    
        Label_780:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_3);
    
        if (!CallFunc_IsActionProcess_ActionProcess_3)
            goto Label_259;
    
        GameStateRef->IsThereGameplayRestriction(tmpCardToDiscard->side, 0x5, CallFunc_IsThereGameplayRestriction_isRestricted);
    
        if (!CallFunc_IsThereGameplayRestriction_isRestricted)
            goto Label_925;
    
        success = false;
    
        return;
    
        Label_925:
        if (!tmpCardToDiscard->isSuppressed)
            goto Label_966;
    
        goto Label_259;
    
        Label_966:
        tmpCardToDiscard->OnAttemptedDiscard(CallFunc_OnAttemptedDiscard_cancelDiscard, discarderID);
    
        if (!CallFunc_OnAttemptedDiscard_cancelDiscard)
            goto Label_259;
    
        success = false;
    
        return;
    
        Label_1050:
        CardFunctionsNotifier->NotifyDiscardCard(cardID, discarderID, oldLocation, false, false);
    
        goto Label_363;
    
        Label_1120:
        success = true;
    
        return;
    
        Label_1136:
        tmpCardToDiscard->OnSuccesfulDiscard(discarderID);
    
        goto Label_436;
    
        Label_1186:
        success = true;
    
        return;
    
        Label_1202:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_507;
    
        Label_1276:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void MoveCardToTopOfOwnersDeck(int cardID, int instigatorID, int positionFromTop, int& qqq)
    {
        oldLocation = 0x0;
    
        _oldEnterPlayOnTurn = 0;
    
        MoveCardToTopOfDeck(cardID, instigatorID, positionFromTop, false);
    
        qqq = 0;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveMobilize(int cardID, int instigatorID, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_178;
    
        CanCardBeBuffed(_card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_1255;
    
        if (!_card->hasMobilize)
            goto Label_255;
    
        goto Label_1276;
    
        Label_178:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("GiveMobilize must have a valid target", this);
    
        return;
    
        Label_255:
        Temp_string_Variable = "mobilize";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_596;
    
        Temp_string_Variable = "mobilize";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        Array_Contains = CallFunc_Map_Find_Value.cardsGivingAbility[instigatorID];
    
        if (!Array_Contains)
            goto Label_1095;
    
        goto Label_870;
    
        Label_596:
        Array_Add = instigatorArry.Add(instigatorID);
    
        ChangeBuffsFromCards(_card, 1, instigatorID, 0x6, 0x8, "mobilize", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = instigatorArry;
    
        Temp_string_Variable_1 = "mobilize";
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        return;
    
        Label_870:
        _card->hasMobilize = true;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1030;
    
        CardFunctionsNotifier->NotifyGiveMobilize(cardID, instigatorID);
    
        if (!_card->isSuppressed)
            goto Label_1054;
    
        Label_1030:
        ExecuteOnOtherCardsAbilitiesChanged(_card);
    
        return;
    
        Label_1054:
        _card->OnGainMobilize();
    
        goto Label_1030;
    
        Label_1095:
        Temp_string_Variable = "mobilize";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        instigatorArry = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        goto Label_596;
    
        Label_1255:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveMobilize(int cardID, int instigatorID, bool skipAction, bool suppress, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_483;
    
        if (!_card->hasMobilize)
            goto Label_1603;
    
        FetchAllCardsWithEventTrigger(0x12, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_202:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_560;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_1->OnBeforeOtherCardLoseMobilize(_card, CallFunc_OnBeforeOtherCardLoseMobilize_dontLoseMobilize);
    
        if (!CallFunc_OnBeforeOtherCardLoseMobilize_dontLoseMobilize)
            goto Label_1460;
    
        if (!suppress)
            goto Label_1534;
    
        return;
    
        Label_483:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("RemoveMobilize must have a valid card", this);
    
        return;
    
        Label_560:
        Temp_string_Variable = "mobilize";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1228;
    
        Temp_string_Variable = "mobilize";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        instigatorArry = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_895:
        Array_Length = instigatorArry.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt_1)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = instigatorArry[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "mobilize", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_1154;
    
        Label_1154:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_895;
    
        Label_1228:
        _card->hasMobilize = false;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_1436;
    
        if (!skipAction)
            goto Label_1386;
    
        Label_1312:
        if (!_card->isSuppressed)
            goto Label_1562;
    
        Label_1348:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1436;
    
        return;
    
        Label_1386:
        CardFunctionsNotifier->NotifyRemoveMobilize(cardID);
    
        goto Label_1312;
    
        Label_1436:
        ExecuteOnOtherCardsAbilitiesChanged(_card);
    
        return;
    
        Label_1460:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_202;
    
        Label_1534:
        qqq = 0;
    
        return;
    
        Label_1562:
        _card->OnLoseMobilize();
    
        goto Label_1348;
    
        Label_1603:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void DiscardCardFromDeck(int cardID, int discarderID, bool skipTriggers, bool skipVisuals, bool& success)
    {
        Greater_IntInt = (cardID > 0);
    
        if (!Greater_IntInt)
            goto Label_858;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        tmpCardToDiscard = CallFunc_GetCardFromID_card;
    
        IsValid = tmpCardToDiscard;
    
        if (!IsValid)
            return;
    
        EqualEqual_ByteByte = ((!tmpCardToDiscard->location) == (!0x2));
    
        EqualEqual_ByteByte_1 = ((!tmpCardToDiscard->location) == (!0x1));
    
        BooleanOR = (EqualEqual_ByteByte_1 || EqualEqual_ByteByte);
    
        if (!BooleanOR)
            goto Label_536;
    
        oldLocation = tmpCardToDiscard->location;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        Not_PreBool = !skipTriggers;
    
        BooleanAND = CallFunc_IsActionProcess_ActionProcess_1 && Not_PreBool;
    
        if (!BooleanAND)
            goto Label_552;
    
        tmpCardToDiscard->OnAttemptedDiscard(CallFunc_OnAttemptedDiscard_cancelDiscard, discarderID);
    
        if (!CallFunc_OnAttemptedDiscard_cancelDiscard)
            goto Label_683;
    
        success = false;
    
        return;
    
        Label_536:
        success = false;
    
        return;
    
        Label_552:
        GameStateRef->RemoveCardFromDeckBySide(tmpCardToDiscard->side, cardID, CallFunc_RemoveCardFromDeckBySide_removedIndex);
    
        ExecuteOnAfterDeckChanged(tmpCardToDiscard->side);
    
        return;
    
        Label_683:
        SetCardLocationAndLocNumber(cardID, 0x8, 0);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_847;
    
        CardFunctionsNotifier->NotifyDiscardCard(cardID, discarderID, oldLocation, skipTriggers, skipVisuals);
    
        success = true;
    
        return;
    
        Label_847:
        success = true;
    
        Label_858:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemovePin(class UBaseCardObject* card, int& qqq)
    {
        IsValid = card;
    
        if (!IsValid)
            goto Label_687;
    
        card->IsPinned(CallFunc_IsPinned_isPinned);
    
        if (!CallFunc_IsPinned_isPinned)
            goto Label_1323;
    
        Temp_string_Variable = "pinned";
    
        Map_Find = Map_Find(card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_715;
    
        Temp_string_Variable = "pinned";
    
        Map_Find = Map_Find(card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        instigatorArry = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_430:
        Array_Length = instigatorArry.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = instigatorArry[Temp_int_Array_Index_Variable_1];
    
        ChangeBuffsFromCards(card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "pinned", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_1249;
    
        Label_687:
        qqq = 0;
    
        return;
    
        Label_715:
        card->pinnedTurns = 0;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyUnpinUnit(card->cardID);
    
        FetchAllCardsWithEventTrigger(0x3E, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_931:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt_1)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_1->OnOtherUnitUnpinned(card);
    
        goto Label_1175;
    
        Label_1175:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_931;
    
        Label_1249:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_430;
    
        Label_1323:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetAllActiveStaticCards(bool includeNotAttainable, bool includeReserved, TArray<class UBaseCardObject*>& cards)
    {
        BasicSetOnly = false;
    
        FindObject<UPlatformUtilityFunctions_C>(nullptr, "kards/Content/Library/PlatformUtilityFunctions.Default__PlatformUtilityFunctions_C")->IsChinaISBN(this, CallFunc_IsChinaISBN_is_ISBN);
    
        BasicSetOnly = CallFunc_IsChinaISBN_is_ISBN;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_127:
        GameStateRef->GetAllStaticCardsSortedByName(CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards);
    
        Array_Length = CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_705;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        if (!BasicSetOnly)
            goto Label_811;
    
        GameStateRef->GetAllStaticCardsSortedByName(CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards[Temp_int_Array_Index_Variable];
    
        EqualEqual_ByteByte = ((!0x1) == (!CallFunc_Array_Get_Item->cardSet));
    
        if (!EqualEqual_ByteByte)
            goto Label_737;
    
        Label_496:
        if (!includeReserved)
            goto Label_2267;
    
        Label_510:
        GameStateRef->GetAllStaticCardsSortedByName(CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards[Temp_int_Array_Index_Variable];
    
        CardFunctionsNotifier->NotifyCheckCardBlacklisted(CallFunc_Array_Get_Item->name, CallFunc_NotifyCheckCardBlacklisted_IsBlacklisted);
    
        if (!CallFunc_NotifyCheckCardBlacklisted_IsBlacklisted)
            goto Label_2462;
    
        goto Label_2635;
    
        Label_705:
        cards = _staticCards;
    
        return;
    
        Label_737:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_127;
    
        Label_811:
        GameStateRef->GetAllStaticCardsSortedByName(CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards[Temp_int_Array_Index_Variable];
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2252;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2252;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2252;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2252;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2252;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2252;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x9));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0xA));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0xC));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0xD));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0xF));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x10));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x11));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x12));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x13));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x14));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_496;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item->cardSet) !== (!0x15));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2189;
    
        return;
    
        Label_2189:
        FindObject<UDeckAndCollectionUtilityFunctions_C>(nullptr, "kards/Content/Library/DeckAndCollectionUtilityFunctions.Default__DeckAndCollectionUtilityFunctions_C")->isCardSetConfigActive(0x15, this, CallFunc_isCardSetConfigActive_isActive);
    
        if (!CallFunc_isCardSetConfigActive_isActive)
            return;
    
        goto Label_496;
    
        Label_2252:
        if (!includeNotAttainable)
            return;
    
        goto Label_496;
    
        Label_2267:
        GameStateRef->GetAllStaticCardsSortedByName(CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards[Temp_int_Array_Index_Variable];
    
        CardFunctionsNotifier->NotifyCheckCardReserved(CallFunc_Array_Get_Item->name, CallFunc_NotifyCheckCardReserved_IsReserved);
    
        if (!CallFunc_NotifyCheckCardReserved_IsReserved)
            goto Label_510;
    
        return;
    
        Label_2462:
        GameStateRef->GetAllStaticCardsSortedByName(CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllStaticCardsSortedByName_OutAllStaticCards[Temp_int_Array_Index_Variable];
    
        Array_Add = _staticCards.Add(CallFunc_Array_Get_Item);
    
        return;
    
        Label_2635:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void DoesSideControlTheFrontline(ESideEnum side, bool& doesHe)
    {
        GameStateRef->GetFrontlineOwnerSide(CallFunc_GetFrontlineOwnerSide_ownerSide);
    
        EqualEqual_ByteByte = ((!side) == (!CallFunc_GetFrontlineOwnerSide_ownerSide));
    
        if (!EqualEqual_ByteByte)
            goto Label_113;
    
        doesHe = true;
    
        return;
    
        Label_113:
        doesHe = false;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveBlitz(int cardID, bool& qqq, int giverID, bool skipAction)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_2290;
    
        _card->getHasBlitz(CallFunc_getHasBlitz_doesIt_1);
    
        _alreadyHadBlitz = CallFunc_getHasBlitz_doesIt_1;
    
        LessEqual_IntInt = (giverID <= 0);
    
        if (!LessEqual_IntInt)
            goto Label_839;
    
        _card->getHasBlitz(CallFunc_getHasBlitz_doesIt_2);
    
        if (!CallFunc_getHasBlitz_doesIt_2)
            return;
    
        Temp_string_Variable_3 = "blitz";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_3, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1997;
    
        Temp_string_Variable_3 = "blitz";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_3, CallFunc_Map_Find_Value);
    
        _cardsGivingBlitz = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_583:
        Array_Length = _cardsGivingBlitz.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt_1)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = _cardsGivingBlitz[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "blitz", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_2142;
    
        Label_839:
        Temp_string_Variable_2 = "blitz";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        Array_Contains = CallFunc_Map_Find_Value_1.cardsGivingAbility[giverID];
    
        if (!Array_Contains)
            return;
    
        Temp_string_Variable_2 = "blitz";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        _cardsGivingBlitz = CallFunc_Map_Find_Value_1.cardsGivingAbility;
    
        Array_RemoveItem = _cardsGivingBlitz.Remove(giverID);
    
        if (!Array_RemoveItem)
            return;
    
        ChangeBuffsFromCards(_card, -1, giverID, 0x6, 0x8, "blitz", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        Temp_string_Variable_1 = "blitz";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingBlitz;
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        Label_1455:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        _card->getHasBlitz(CallFunc_getHasBlitz_doesIt);
    
        NotEqual_BoolBool = (CallFunc_getHasBlitz_doesIt !== _alreadyHadBlitz);
    
        if (!NotEqual_BoolBool)
            goto Label_1900;
    
        FetchAllCardsWithEventTrigger(0x21, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1652:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_1900;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_1->OnOtherCardBlitzChanged(_card);
    
        goto Label_2216;
    
        Label_1900:
        if (!skipAction)
            goto Label_1938;
    
        Label_1914:
        ExecuteOnOtherCardsAbilitiesChanged(_card);
    
        return;
    
        Label_1938:
        CardFunctionsNotifier->NotifyRemoveBlitz(cardID, giverID);
    
        goto Label_1914;
    
        Label_1997:
        _card->hasBlitz = false;
    
        Temp_string_Variable = "blitz";
    
        Map_Remove = _card->receivedAbilitiesFromCards.Remove(Temp_string_Variable);
    
        goto Label_1455;
    
        Label_2142:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_583;
    
        Label_2216:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1652;
    
        Label_2290:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void WhichStrategy(EnumCampaignStrategy& Branches)
    {
        CardFunctionsNotifier->GetCampaignStrategy(CallFunc_GetCampaignStrategy_Strategy);
    
        Branches = CallFunc_GetCampaignStrategy_Strategy;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetTurnNumber(int& turnNumber)
    {
        GameStateRef->GetTurnNumber(CallFunc_GetTurnNumber_TurnNumber);
    
        turnNumber = CallFunc_GetTurnNumber_TurnNumber;
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void EndMatch(ESideEnum winnerSide, float delay)
    {
        CardFunctionsNotifier->NotifyCampaignEndMatch(winnerSide, "Campaign Condition");
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void AppendText(FText*& firstText, FText*& secondText, FText& text)
    {
        MakeStruct_FormatArgumentData.ArgumentName = "0";
    
        MakeStruct_FormatArgumentData.ArgumentValueType = 0x4;
    
        MakeStruct_FormatArgumentData.ArgumentValue = firstText;
    
        MakeStruct_FormatArgumentData.ArgumentValueInt = 0;
    
        MakeStruct_FormatArgumentData.ArgumentValueFloat = 0;
    
        MakeStruct_FormatArgumentData.ArgumentValueDouble = 0;
    
        MakeStruct_FormatArgumentData.ArgumentValueGender = 0x0;
    
        MakeStruct_FormatArgumentData_1.ArgumentName = "1";
    
        MakeStruct_FormatArgumentData_1.ArgumentValueType = 0x4;
    
        MakeStruct_FormatArgumentData_1.ArgumentValue = secondText;
    
        MakeStruct_FormatArgumentData_1.ArgumentValueInt = 0;
    
        MakeStruct_FormatArgumentData_1.ArgumentValueFloat = 0;
    
        MakeStruct_FormatArgumentData_1.ArgumentValueDouble = 0;
    
        MakeStruct_FormatArgumentData_1.ArgumentValueGender = 0x0;
    
        MakeArray_Array = [ MakeStruct_FormatArgumentData, MakeStruct_FormatArgumentData_1 ];
    
        Format = UKismetTextLibrary::Format("{0} {1}", MakeArray_Array);
    
        text = Format;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void IsUsingStrategy(EnumCampaignStrategy strategy, bool& usingIt)
    {
        CardFunctionsNotifier->GetCampaignStrategy(CallFunc_GetCampaignStrategy_Strategy);
    
        EqualEqual_ByteByte = ((!strategy) == (!CallFunc_GetCampaignStrategy_Strategy));
    
        usingIt = EqualEqual_ByteByte;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void DamageMultipleCards(const TArray<int>*& receiverIDs, int amount, int damagerCardID, TArray<int>& cardsDestroyed)
    {
        Array_Length = receiverIDs.Length;
    
        Greater_IntInt = (Array_Length > 0);
    
        if (!Greater_IntInt)
            return;
    
        ApplyDamageToMultipleCards(receiverIDs, damagerCardID, amount, CallFunc_ApplyDamageToMultipleCards_outputDestroyedCards);
    
        cardsDestroyed = CallFunc_ApplyDamageToMultipleCards_outputDestroyedCards;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void DestroyMultipleCards(const TArray<int>*& cardsToDestroy, int destroyerCardID, int& qqq)
    {
        Array_Length = cardsToDestroy.Length;
    
        Greater_IntInt = (Array_Length > 0);
    
        if (!Greater_IntInt)
            return;
    
        ApplyDestroyMultipleCards(destroyerCardID, cardsToDestroy);
    
        qqq = 0;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_AddToBoolArray(class UBaseCardObject* card, FString variableName, bool value, bool& found)
    {
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        if (!JsonHasTypedField)
            goto Label_208;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        oldArr = Conv_JsonValueToArray;
    
        Label_208:
        JsonMakeBool = UBlueprintJsonLibrary::JsonMakeBool(value);
    
        Array_Add = oldArr.Add(JsonMakeBool);
    
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(oldArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        found = true;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_AddToIntArray(class UBaseCardObject* card, FString variableName, int value, bool& found)
    {
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        if (!JsonHasTypedField)
            goto Label_208;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        oldArr = Conv_JsonValueToArray;
    
        Label_208:
        JsonMakeInt = UBlueprintJsonLibrary::JsonMakeInt(value);
    
        Array_Add = oldArr.Add(JsonMakeInt);
    
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(oldArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        found = true;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_AddToStringArray(class UBaseCardObject* card, FString variableName, FString value, bool& found)
    {
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        if (!JsonHasTypedField)
            goto Label_208;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        oldArr = Conv_JsonValueToArray;
    
        Label_208:
        JsonMakeString = UBlueprintJsonLibrary::JsonMakeString(value);
    
        Array_Add = oldArr.Add(JsonMakeString);
    
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(oldArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        found = true;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_Clear(class UBaseCardObject* card, FString variableName, bool& found)
    {
        existed = false;
    
        JsonHasField = UBlueprintJsonLibrary::JsonHasField(card->customJson, variableName);
    
        existed = JsonHasField;
    
        if (!existed)
            goto Label_221;
    
        JsonRemoveField = UBlueprintJsonLibrary::JsonRemoveField(card->customJson, variableName);
    
        card->customJson = JsonRemoveField;
    
        Label_221:
        found = existed;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_RemoveFromBoolArray(class UBaseCardObject* card, FString variableName, bool value, bool& found)
    {
        removalIndex = -1;
    
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        if (!JsonHasTypedField)
            goto Label_678;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        oldArr = Conv_JsonValueToArray;
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_293:
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Array_Length = oldArr.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        BooleanAND = Not_PreBool && Less_IntInt;
    
        if (!BooleanAND)
            goto Label_764;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = oldArr[Temp_int_Array_Index_Variable];
    
        Conv_JsonValueToBool = UBlueprintJsonLibrary::Conv_JsonValueToBool(CallFunc_Array_Get_Item);
    
        EqualEqual_BoolBool = Conv_JsonValueToBool == value;
    
        if (!EqualEqual_BoolBool)
            goto Label_1030;
    
        removalIndex = Temp_int_Array_Index_Variable;
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        goto Label_1104;
    
        Label_678:
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        found = JsonHasTypedField;
    
        return;
    
        Label_764:
        Greater_IntInt = (removalIndex > -1);
    
        if (!Greater_IntInt)
            goto Label_678;
    
        oldArr.Remove(removalIndex);
    
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(oldArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        goto Label_678;
    
        Label_1030:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_293;
    
        Label_1104:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_RemoveFromIntArray(class UBaseCardObject* card, FString variableName, int value, bool& found)
    {
        removalIndex = -1;
    
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        if (!JsonHasTypedField)
            goto Label_686;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        oldArr = Conv_JsonValueToArray;
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_293:
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Array_Length = oldArr.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        BooleanAND = Not_PreBool && Less_IntInt;
    
        if (!BooleanAND)
            goto Label_772;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = oldArr[Temp_int_Array_Index_Variable];
    
        Conv_JsonValueToInteger = UBlueprintJsonLibrary::Conv_JsonValueToInteger(CallFunc_Array_Get_Item);
    
        EqualEqual_IntInt = Conv_JsonValueToInteger == value;
    
        if (!EqualEqual_IntInt)
            goto Label_1054;
    
        removalIndex = Temp_int_Array_Index_Variable;
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        goto Label_1128;
    
        Label_686:
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        found = JsonHasTypedField;
    
        return;
    
        Label_772:
        Greater_IntInt = (removalIndex > -1);
    
        if (!Greater_IntInt)
            goto Label_1038;
    
        oldArr.Remove(removalIndex);
    
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(oldArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        goto Label_686;
    
        Label_1038:
        found = false;
    
        return;
    
        Label_1054:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_293;
    
        Label_1128:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_RemoveFromStringArray(class UBaseCardObject* card, FString variableName, FString value, bool& found)
    {
        removalIndex = -1;
    
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        JsonFound = JsonHasTypedField;
    
        if (!JsonFound)
            goto Label_430;
    
        tmpJson = card->customJson;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(tmpJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        oldArr = Conv_JsonValueToArray;
    
        EqualEqual_StrStr = variableName == "effects";
    
        if (!EqualEqual_StrStr)
            goto Label_892;
    
        Conv_StringToInt = (int32)value;
    
        Greater_IntInt = (Conv_StringToInt > 0);
    
        if (!Greater_IntInt)
            goto Label_2583;
    
        goto Label_1412;
    
        Label_430:
        found = JsonFound;
    
        return;
    
        Label_454:
        Greater_IntInt_2 = (removalIndex > -1);
    
        if (!Greater_IntInt_2)
            goto Label_822;
    
        oldArr.Remove(removalIndex);
    
        Array_Length = oldArr.Length;
    
        Greater_IntInt_1 = (Array_Length > 0);
    
        if (!Greater_IntInt_1)
            goto Label_846;
    
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(oldArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        Label_822:
        found = JsonFound;
    
        return;
    
        Label_846:
        JSON_Clear(card, variableName, CallFunc_JSON_Clear_found);
    
        goto Label_822;
    
        Label_892:
        Temp_bool_True_if_break_was_hit_Variable_1 = false;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_949:
        Not_PreBool_1 = !Temp_bool_True_if_break_was_hit_Variable_1;
    
        Array_Length_1 = oldArr.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        BooleanAND = Not_PreBool_1 && Less_IntInt;
    
        if (!BooleanAND)
            goto Label_454;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = oldArr[Temp_int_Array_Index_Variable_1];
    
        Conv_JsonValueToString = UBlueprintJsonLibrary::Conv_JsonValueToString(CallFunc_Array_Get_Item);
    
        EqualEqual_StrStr_1 = Conv_JsonValueToString == value;
    
        if (!EqualEqual_StrStr_1)
            goto Label_1338;
    
        removalIndex = Temp_int_Array_Index_Variable_1;
    
        Temp_bool_True_if_break_was_hit_Variable_1 = true;
    
        goto Label_2602;
    
        Label_1338:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_949;
    
        Label_1412:
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_1469:
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Array_Length_2 = oldArr.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_2);
    
        BooleanAND_1 = Not_PreBool && Less_IntInt_2;
    
        if (!BooleanAND_1)
            return;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_2;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1721:
        CallFunc_Array_Get_Item_1 = oldArr[Temp_int_Array_Index_Variable_2];
    
        Conv_JsonValueToString_1 = UBlueprintJsonLibrary::Conv_JsonValueToString(CallFunc_Array_Get_Item_1);
    
        ParseIntoArray = Conv_JsonValueToString_1.Split(":", /* removeEmpty = */ true);
    
        Array_Length_3 = ParseIntoArray.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_3);
    
        if (!Less_IntInt_1)
            goto Label_2385;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        SwitchInteger_CmpSuccess = (Temp_int_Array_Index_Variable !== 0);
    
        if (!SwitchInteger_CmpSuccess)
            goto Label_2050;
    
        goto Label_2311;
    
        Label_2050:
        CallFunc_Array_Get_Item_1 = oldArr[Temp_int_Array_Index_Variable_2];
    
        Conv_JsonValueToString_1 = UBlueprintJsonLibrary::Conv_JsonValueToString(CallFunc_Array_Get_Item_1);
    
        ParseIntoArray = Conv_JsonValueToString_1.Split(":", /* removeEmpty = */ true);
    
        CallFunc_Array_Get_Item_2 = ParseIntoArray[Temp_int_Array_Index_Variable];
    
        Conv_StringToInt_2 = (int32)CallFunc_Array_Get_Item_2;
    
        instigatorID = Conv_StringToInt_2;
    
        goto Label_2509;
    
        Label_2311:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_1721;
    
        Label_2385:
        Conv_StringToInt_1 = (int32)value;
    
        EqualEqual_IntInt = Conv_StringToInt_1 == instigatorID;
    
        if (!EqualEqual_IntInt)
            return;
    
        removalIndex = Temp_int_Array_Index_Variable_2;
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        return;
    
        Label_2509:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_1469;
    
        Label_2583:
        found = JsonFound;
    
        Label_2602:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_SetBool(class UBaseCardObject* card, FString variableName, bool value, bool& found)
    {
        JsonMakeBool = UBlueprintJsonLibrary::JsonMakeBool(value);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeBool);
    
        card->customJson = JsonMakeField;
    
        found = true;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_SetBoolArray(class UBaseCardObject* card, FString variableName, const TArray<bool>*& values, bool& found)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Array_Length = values.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_359;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = values[Temp_int_Array_Index_Variable];
    
        JsonMakeBool = UBlueprintJsonLibrary::JsonMakeBool(CallFunc_Array_Get_Item);
    
        Array_Add = jsonArr.Add(JsonMakeBool);
    
        goto Label_538;
    
        Label_359:
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(jsonArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        found = false;
    
        return;
    
        Label_538:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_612:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_SetInt(class UBaseCardObject* card, FString variableName, int value, bool& found)
    {
        JsonMakeInt = UBlueprintJsonLibrary::JsonMakeInt(value);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeInt);
    
        card->customJson = JsonMakeField;
    
        found = true;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_SetIntArray(class UBaseCardObject* card, FString variableName, const TArray<int>*& values, bool& found)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Array_Length = values.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_359;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = values[Temp_int_Array_Index_Variable];
    
        JsonMakeInt = UBlueprintJsonLibrary::JsonMakeInt(CallFunc_Array_Get_Item);
    
        Array_Add = jsonArr.Add(JsonMakeInt);
    
        goto Label_538;
    
        Label_359:
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(jsonArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        found = false;
    
        return;
    
        Label_538:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_612:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_SetString(class UBaseCardObject* card, FString variableName, FString value, bool& found)
    {
        JsonMakeString = UBlueprintJsonLibrary::JsonMakeString(value);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeString);
    
        card->customJson = JsonMakeField;
    
        found = true;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_SetStringArray(class UBaseCardObject* card, FString variableName, const TArray<FString>*& values, bool& found)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Array_Length = values.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_359;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = values[Temp_int_Array_Index_Variable];
    
        JsonMakeString = UBlueprintJsonLibrary::JsonMakeString(CallFunc_Array_Get_Item);
    
        Array_Add = jsonArr.Add(JsonMakeString);
    
        goto Label_538;
    
        Label_359:
        JsonMakeArray = UBlueprintJsonLibrary::JsonMakeArray(jsonArr);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(card->customJson, variableName, JsonMakeArray);
    
        card->customJson = JsonMakeField;
    
        found = false;
    
        return;
    
        Label_538:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_612:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_GetInt(class UBaseCardObject* card, FString variableName, int& value, bool& found)
    {
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x3);
    
        if (!JsonHasTypedField)
            goto Label_224;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToInteger = UBlueprintJsonLibrary::Conv_JsonValueToInteger(Conv_JsonObjectToJsonValue);
    
        value = Conv_JsonValueToInteger;
    
        found = true;
    
        return;
    
        Label_224:
        value = 0;
    
        found = false;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_GetBool(class UBaseCardObject* card, FString variableName, bool& value, bool& found)
    {
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x4);
    
        if (!JsonHasTypedField)
            goto Label_208;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToBool = UBlueprintJsonLibrary::Conv_JsonValueToBool(Conv_JsonObjectToJsonValue);
    
        value = Conv_JsonValueToBool;
    
        found = true;
    
        return;
    
        Label_208:
        value = false;
    
        found = false;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_GetString(class UBaseCardObject* card, FString variableName, FString& value, bool& found)
    {
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x2);
    
        if (!JsonHasTypedField)
            goto Label_224;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToString = UBlueprintJsonLibrary::Conv_JsonValueToString(Conv_JsonObjectToJsonValue);
    
        value = Conv_JsonValueToString;
    
        found = true;
    
        return;
    
        Label_224:
        value = "";
    
        found = false;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_GetBoolArray(class UBaseCardObject* card, FString variableName, TArray<bool>& values, bool& found)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        Array_Length = Conv_JsonValueToArray.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_561;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        CallFunc_Array_Get_Item = Conv_JsonValueToArray[Temp_int_Array_Index_Variable];
    
        Conv_JsonValueToBool = UBlueprintJsonLibrary::Conv_JsonValueToBool(CallFunc_Array_Get_Item);
    
        Array_Add = arr.Add(Conv_JsonValueToBool);
    
        goto Label_734;
    
        Label_561:
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        if (!JsonHasTypedField)
            goto Label_680;
    
        values = arr;
    
        found = false;
    
        return;
    
        Label_680:
        MakeArray_Array = [];
    
        values = MakeArray_Array;
    
        found = false;
    
        return;
    
        Label_734:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_808:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_GetIntArray(class UBaseCardObject* card, FString variableName, TArray<int>& values, bool& found)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        Array_Length = Conv_JsonValueToArray.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_569;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        CallFunc_Array_Get_Item = Conv_JsonValueToArray[Temp_int_Array_Index_Variable];
    
        Conv_JsonValueToInteger = UBlueprintJsonLibrary::Conv_JsonValueToInteger(CallFunc_Array_Get_Item);
    
        Array_Add = arr.Add(Conv_JsonValueToInteger);
    
        goto Label_742;
    
        Label_569:
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        if (!JsonHasTypedField)
            goto Label_688;
    
        values = arr;
    
        found = true;
    
        return;
    
        Label_688:
        MakeArray_Array = [];
    
        values = MakeArray_Array;
    
        found = false;
    
        return;
    
        Label_742:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_816:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void JSON_GetStringArray(class UBaseCardObject* card, FString variableName, TArray<FString>& values, bool& found)
    {
        JsonHasTypedField = UBlueprintJsonLibrary::JsonHasTypedField(card->customJson, variableName, 0x5);
    
        if (!JsonHasTypedField)
            goto Label_645;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_127:
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        Array_Length = Conv_JsonValueToArray.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_699;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(card->customJson, variableName);
    
        Conv_JsonValueToArray = UBlueprintJsonLibrary::Conv_JsonValueToArray(Conv_JsonObjectToJsonValue);
    
        CallFunc_Array_Get_Item = Conv_JsonValueToArray[Temp_int_Array_Index_Variable];
    
        Conv_JsonValueToString = UBlueprintJsonLibrary::Conv_JsonValueToString(CallFunc_Array_Get_Item);
    
        Array_Add = arr.Add(Conv_JsonValueToString);
    
        goto Label_742;
    
        Label_645:
        MakeArray_Array = [];
    
        values = MakeArray_Array;
    
        found = false;
    
        return;
    
        Label_699:
        values = arr;
    
        found = true;
    
        return;
    
        Label_742:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_127;
    
        Label_816:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void selectTargetFromHand(int cardSelectingHandTarget, int& qqq)
    {
        CardFunctionsNotifier->NotifySelectHandTargetPending(cardSelectingHandTarget);
    
        qqq = 0;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetRandomCard(TArray<class UBaseCardObject*>*& cards, bool skipCustomAlways, class UBaseCardObject*& randomCard)
    {
        Array_Length = cards.Length;
    
        Greater_IntInt = (Array_Length > 0);
    
        if (!Greater_IntInt)
            goto Label_361;
    
        if (!skipCustomAlways)
            goto Label_377;
    
        Label_126:
        Array_Length_1 = cards.Length;
    
        Subtract_IntInt = Array_Length_1 - 1;
    
        RandomIntegerInRangeFromStream = UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, 0, Subtract_IntInt);
    
        CallFunc_Array_Get_Item_1 = cards[RandomIntegerInRangeFromStream];
    
        randomCard = CallFunc_Array_Get_Item_1;
    
        return;
    
        Label_361:
        randomCard = nullptr;
    
        return;
    
        Label_377:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_423:
        Array_Length_2 = cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt)
            goto Label_902;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->CustomName1HasAttribute("AlwaysSelectedAsRandom", CallFunc_CustomName1HasAttribute_doesIt);
    
        if (!CallFunc_CustomName1HasAttribute_doesIt)
            goto Label_828;
    
        CallFunc_Array_Get_Item = cards[Temp_int_Array_Index_Variable];
    
        Array_Add = alwaysSelected.Add(CallFunc_Array_Get_Item);
    
        goto Label_1239;
    
        Label_828:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_423;
    
        Label_902:
        Array_Length_4 = alwaysSelected.Length;
    
        Greater_IntInt_1 = (Array_Length_4 > 0);
    
        if (!Greater_IntInt_1)
            goto Label_126;
    
        Array_Length_3 = alwaysSelected.Length;
    
        Subtract_IntInt_1 = Array_Length_3 - 1;
    
        RandomIntegerInRangeFromStream_1 = UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, 0, Subtract_IntInt_1);
    
        CallFunc_Array_Get_Item_2 = alwaysSelected[RandomIntegerInRangeFromStream_1];
    
        randomCard = CallFunc_Array_Get_Item_2;
    
        Label_1239:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SetCardsSeenByCipher(int numberOfCardsSeen, int instigatorID, ESideEnum side, int& qqq)
    {
        FetchAllCardsWithEventTrigger(0x1C, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_81:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_366;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card);
    
        CallFunc_Array_Get_Item->OnIntelTriggered(CallFunc_GetCardFromID_card, numberOfCardsSeen);
    
        goto Label_1124;
    
        Label_366:
        Temp_byte_Variable = 0x0;
    
        Temp_byte_Variable_1 = 0x2;
    
        Temp_byte_Variable_2 = 0x1;
    
        Temp_byte_Variable_3 = side;
    
        GetCardsInHandBySide(switch (Temp_byte_Variable_3)
        {
            case 0x0:
            {
                return Temp_byte_Variable;
                break;
            }
            case 0x1:
            {
                return Temp_byte_Variable_1;
                break;
            }
            case 0x2:
            {
                return Temp_byte_Variable_2;
                break;
            }
            default:
            {
                return Select_Default;
                break;
            }
        }, CallFunc_GetCardsInHandBySide_cards);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_597:
        Array_Length_2 = CallFunc_GetCardsInHandBySide_cards.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_2);
    
        if (!Less_IntInt_1)
            goto Label_832;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        if (!CallFunc_Array_Get_Item_1->cardSeen)
            goto Label_1272;
    
        goto Label_1198;
    
        Label_832:
        Array_IsNotEmpty = oppositeSideUnseenCards.Length > 0;
    
        if (!Array_IsNotEmpty)
            goto Label_1400;
    
        Array_ShuffleFromStream(oppositeSideUnseenCards, cardsRandomStream);
    
        Array_Length_1 = oppositeSideUnseenCards.Length;
    
        Min = UKismetMathLibrary::Min(numberOfCardsSeen, Array_Length_1);
    
        Array_Resize(oppositeSideUnseenCards, Min);
    
        ApplySetCardsSeenByCipher(oppositeSideUnseenCards, false, true);
    
        goto Label_816;
    
        Label_1124:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_81;
    
        Label_1198:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_597;
    
        Label_1272:
        CallFunc_Array_Get_Item_1 = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        Array_Add = oppositeSideUnseenCards.Add(CallFunc_Array_Get_Item_1);
    
        goto Label_816;
    
        Label_1400:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ShowTutorialMessage(FText*& message, FString abilityString, int cardID, float delay, bool& qqq)
    {
        CallFunc_NotifyShowTutorialMessage_Delay_ImplicitCast = Cast<double>(delay);
    
        CardFunctionsNotifier->NotifyShowTutorialMessage(message, abilityString, cardID, CallFunc_NotifyShowTutorialMessage_Delay_ImplicitCast);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void selectCardToDraw(int cardSelectingCardToDraw, bool selectFromTopOfDeck, bool isEffect, int& drawnCardID)
    {
        if (!selectFromTopOfDeck)
            goto Label_1445;
    
        GetCardFromID(cardSelectingCardToDraw, CallFunc_GetCardFromID_card_1);
    
        cardSelecting = CallFunc_GetCardFromID_card_1;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_116:
        GetDeckByside(cardSelecting->side, CallFunc_GetDeckByside_deckCardIDs);
    
        Array_Length = CallFunc_GetDeckByside_deckCardIDs.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_2301;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GetDeckByside(cardSelecting->side, CallFunc_GetDeckByside_deckCardIDs);
    
        CallFunc_Array_Get_Item = CallFunc_GetDeckByside_deckCardIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card);
    
        GetCardFromID(cardSelectingCardToDraw, CallFunc_GetCardFromID_card_5);
    
        CallFunc_GetCardFromID_card_5->FilterCardsToScry(CallFunc_GetCardFromID_card, CallFunc_FilterCardsToScry_isValid);
    
        if (!CallFunc_FilterCardsToScry_isValid)
            goto Label_3351;
    
        GetDeckByside(cardSelecting->side, CallFunc_GetDeckByside_deckCardIDs);
    
        CallFunc_Array_Get_Item = CallFunc_GetDeckByside_deckCardIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card);
    
        Array_Add_1 = possibleChooseCards.Add(CallFunc_GetCardFromID_card);
    
        Array_Length_2 = possibleChooseCards.Length;
    
        Greater_IntInt_2 = (Array_Length_2 > 2);
    
        if (!Greater_IntInt_2)
            goto Label_3564;
    
        CallFunc_Array_Get_Item_3 = possibleChooseCards[2];
    
        Conv_IntToString = FString(CallFunc_Array_Get_Item_3->cardID);
    
        Conv_StringToName = FName(Conv_IntToString);
    
        CallFunc_Array_Get_Item_4 = possibleChooseCards[1];
    
        CallFunc_Array_Get_Item_5 = possibleChooseCards[0];
    
        Conv_IntToString_1 = FString(CallFunc_Array_Get_Item_4->cardID);
    
        Conv_StringToName_1 = FName(Conv_IntToString_1);
    
        Conv_IntToString_2 = FString(CallFunc_Array_Get_Item_5->cardID);
    
        Conv_StringToName_2 = FName(Conv_IntToString_2);
    
        MakeArray_Array_1 = [ Conv_StringToName_2, Conv_StringToName_1, Conv_StringToName ];
    
        CardFunctionsNotifier->NotifySelectCardToDrawPending(cardSelectingCardToDraw, true, MakeArray_Array_1, false);
    
        drawnCardID = 0;
    
        return;
    
        Label_1445:
        GetCardFromID(cardSelectingCardToDraw, CallFunc_GetCardFromID_card_2);
    
        cardSelecting = CallFunc_GetCardFromID_card_2;
    
        Not_PreBool = !isEffect;
    
        GetHandLocationBySide(cardSelecting->side, CallFunc_GetHandLocationBySide_handLocation);
    
        IsLocationFull(CallFunc_GetHandLocationBySide_handLocation, CallFunc_IsLocationFull_isFull);
    
        BooleanAND = CallFunc_IsLocationFull_isFull && Not_PreBool;
    
        if (!BooleanAND)
            goto Label_1664;
    
        goto Label_808;
    
        Label_1664:
        CallFunc_GetChooseSpawnCards_cards = [];
    
        cardSelecting->GetChooseSpawnCards(CallFunc_GetChooseSpawnCards_cards, CallFunc_GetChooseSpawnCards_markAsSeen, CallFunc_GetChooseSpawnCards_keepOrder);
    
        possibleChooseCards = CallFunc_GetChooseSpawnCards_cards;
    
        if (!CallFunc_GetChooseSpawnCards_keepOrder)
            goto Label_2246;
    
        Label_1779:
        Temp_int_Variable = 0;
    
        Label_1802:
        Array_LastIndex = possibleChooseCards.Length - 1;
    
        Min = UKismetMathLibrary::Min(2, Array_LastIndex);
    
        LessEqual_IntInt = (Temp_int_Variable <= Min);
    
        if (!LessEqual_IntInt)
            goto Label_3425;
    
        if (!CallFunc_GetChooseSpawnCards_markAsSeen)
            goto Label_2096;
    
        CallFunc_Array_Get_Item_1 = possibleChooseCards[Temp_int_Variable];
    
        SetCardSeen(CallFunc_Array_Get_Item_1->cardID, cardSelectingCardToDraw, CallFunc_SetCardSeen_qqq);
    
        Label_2096:
        CallFunc_Array_Get_Item_1 = possibleChooseCards[Temp_int_Variable];
    
        Array_Add = spawnCards.Add(CallFunc_Array_Get_Item_1->name);
    
        goto Label_3490;
    
        Label_2246:
        Array_ShuffleFromStream(possibleChooseCards, cardsRandomStream);
    
        goto Label_1779;
    
        Label_2301:
        Array_Length_1 = possibleChooseCards.Length;
    
        Greater_IntInt_1 = (Array_Length_1 > 0);
    
        if (!Greater_IntInt_1)
            goto Label_3235;
    
        Array_Length_1 = possibleChooseCards.Length;
    
        Greater_IntInt = (Array_Length_1 > 1);
    
        if (!Greater_IntInt)
            goto Label_2903;
    
        CallFunc_Array_Get_Item_4 = possibleChooseCards[1];
    
        CallFunc_Array_Get_Item_5 = possibleChooseCards[0];
    
        Conv_IntToString_1 = FString(CallFunc_Array_Get_Item_4->cardID);
    
        Conv_StringToName_1 = FName(Conv_IntToString_1);
    
        Conv_IntToString_2 = FString(CallFunc_Array_Get_Item_5->cardID);
    
        Conv_StringToName_2 = FName(Conv_IntToString_2);
    
        MakeArray_Array = [ Conv_StringToName_2, Conv_StringToName_1 ];
    
        CardFunctionsNotifier->NotifySelectCardToDrawPending(cardSelectingCardToDraw, true, MakeArray_Array, false);
    
        goto Label_612;
    
        Label_2903:
        GetCardFromID(cardSelectingCardToDraw, CallFunc_GetCardFromID_card_3);
    
        CallFunc_Array_Get_Item_2 = possibleChooseCards[0];
    
        DrawSpecificCardFromDeckBySide(cardSelectingCardToDraw, CallFunc_Array_Get_Item_2->cardID, CallFunc_GetCardFromID_card_3->side, false);
    
        CallFunc_Array_Get_Item_2 = possibleChooseCards[0];
    
        GetCardFromID(cardSelectingCardToDraw, CallFunc_GetCardFromID_card_4);
    
        CallFunc_GetCardFromID_card_4->OnHandTargetSelected(CallFunc_Array_Get_Item_2->cardID, 0);
    
        Label_3235:
        GameStateRef->GetExecuteWaitPlayFromHand(CallFunc_GetExecuteWaitPlayFromHand_ShouldExecuteWait);
    
        if (!CallFunc_GetExecuteWaitPlayFromHand_ShouldExecuteWait)
            goto Label_612;
    
        GetCardFromID(cardSelectingCardToDraw, CallFunc_GetCardFromID_card_4);
    
        AfterWaitCardPlayFromHand(CallFunc_GetCardFromID_card_4, 0);
    
        goto Label_612;
    
        Label_3351:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_116;
    
        Label_3425:
        CardFunctionsNotifier->NotifySelectCardToDrawPending(cardSelectingCardToDraw, false, spawnCards, isEffect);
    
        return;
    
        Label_3490:
        Add_IntInt_1 = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt_1;
    
        goto Label_1802;
    
        Label_3564:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void CustomAbilityAdd(FString ability, int cardID, int giverID, bool skipBuffTexts, bool skipSubActions, bool skipAddToBattlelog, bool& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        cardToChange = CallFunc_GetCardFromID_card;
    
        IsValid = cardToChange;
    
        if (!IsValid)
            goto Label_467;
    
        CanCardBeBuffed(cardToChange, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_545;
    
        Map_Find = Map_Find(cardToChange->receivedAbilitiesFromCards, ability, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_561;
    
        Map_Find = Map_Find(cardToChange->receivedAbilitiesFromCards, ability, CallFunc_Map_Find_Value);
    
        _cardsGivingAbility = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingAbility[giverID];
    
        if (!Array_Contains)
            goto Label_561;
    
        qqq = false;
    
        return;
    
        Label_467:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("customAbilityAdd must have a valid card", this);
    
        Label_545:
        qqq = false;
    
        return;
    
        Label_561:
        Array_Add = _cardsGivingAbility.Add(giverID);
    
        if (!skipBuffTexts)
            goto Label_649;
    
        goto Label_1217;
    
        Label_649:
        GetCardFromID(giverID, CallFunc_GetCardFromID_card_1);
    
        instigatorCard = CallFunc_GetCardFromID_card_1;
    
        IsValid_1 = instigatorCard;
    
        if (!IsValid_1)
            goto Label_1192;
    
        Conv_NameToString = FString(instigatorCard->name);
    
        NameDetail = Conv_NameToString;
    
        instigatorCard->IsChooseOneCard(CallFunc_IsChooseOneCard_isIt);
    
        EqualEqual_IntInt = giverID == cardID;
    
        BooleanAND = CallFunc_IsChooseOneCard_isIt && EqualEqual_IntInt;
    
        if (!BooleanAND)
            goto Label_1132;
    
        Concat_StrStr = NameDetail += "_";
    
        Conv_IntToString = FString(instigatorCard->chooseOneIndex);
    
        Concat_StrStr_1 = Concat_StrStr += Conv_IntToString;
    
        NameDetail = Concat_StrStr_1;
    
        Label_1132:
        ChangeBuffsFromCards(cardToChange, -1000, giverID, 0x5, 0x6, NameDetail, CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_1464;
    
        Label_1192:
        NameDetail = "";
    
        goto Label_1132;
    
        Label_1217:
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingAbility;
    
        Map_Add(cardToChange->receivedAbilitiesFromCards, ability, MakeStruct_CardsGivingAbility);
    
        if (!skipSubActions)
            goto Label_1349;
    
        return;
    
        Label_1349:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyCustomAbilityAdd(cardID, giverID, ability, skipBuffTexts, skipAddToBattlelog);
    
        return;
    
        Label_1464:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void CustomAbilityRemove(FString ability, int cardID, int giverID, bool RemoveAllGivers, bool& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_1740;
    
        EqualEqual_StrStr_1 = ability == "destruction";
    
        BooleanAND = EqualEqual_StrStr_1 && _card->hasDestruction;
    
        if (!BooleanAND)
            goto Label_278;
    
        ChangeBuffsFromCards(_card, -1, giverID, 0x6, 0x8, "destruction", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        Label_278:
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, ability, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1839;
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, ability, CallFunc_Map_Find_Value);
    
        _cardsGivingAbility = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        GetCardFromID(giverID, CallFunc_GetCardFromID_card_1);
    
        instigatorCard = CallFunc_GetCardFromID_card_1;
    
        IsValid_1 = instigatorCard;
    
        if (!IsValid_1)
            goto Label_1945;
    
        Conv_NameToString = FString(instigatorCard->name);
    
        NameDetail = Conv_NameToString;
    
        EqualEqual_IntInt = giverID == cardID;
    
        instigatorCard->IsChooseOneCard(CallFunc_IsChooseOneCard_isIt);
    
        BooleanAND_1 = CallFunc_IsChooseOneCard_isIt && EqualEqual_IntInt;
    
        if (!BooleanAND_1)
            goto Label_993;
    
        Concat_StrStr = NameDetail += "_";
    
        Conv_IntToString = FString(instigatorCard->chooseOneIndex);
    
        Concat_StrStr_1 = Concat_StrStr += Conv_IntToString;
    
        NameDetail = Concat_StrStr_1;
    
        Label_993:
        if (!RemoveAllGivers)
            goto Label_1970;
    
        Array_Length = _cardsGivingAbility.Length;
    
        Greater_IntInt_2 = (Array_Length > 0);
    
        if (!Greater_IntInt_2)
            goto Label_2291;
    
        Len_1 = NameDetail.Length;
    
        Greater_IntInt_1 = (Len_1 > 0);
    
        if (!Greater_IntInt_1)
            goto Label_2291;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1245:
        Array_Length_1 = _cardsGivingAbility.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_2291;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        EqualEqual_StrStr = ability == "destruction";
    
        if (!EqualEqual_StrStr)
            goto Label_1621;
    
        CallFunc_Array_Get_Item = _cardsGivingAbility[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card_2);
    
        Conv_NameToString_1 = FString(CallFunc_GetCardFromID_card_2->name);
    
        NameDetail = Conv_NameToString_1;
    
        Label_1621:
        CallFunc_Array_Get_Item = _cardsGivingAbility[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, 0, CallFunc_Array_Get_Item, 0x5, 0x7, NameDetail, CallFunc_ChangeBuffsFromCards_amountRemoved_2);
    
        goto Label_2500;
    
        Label_1740:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Remove custom ability must have a valid card", this);
    
        qqq = false;
    
        return;
    
        Label_1839:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2574;
    
        CardFunctionsNotifier->NotifyCustomAbilityRemove(cardID, giverID, ability, RemoveAllGivers);
    
        return;
    
        Label_1945:
        NameDetail = "";
    
        goto Label_993;
    
        Label_1970:
        Len = NameDetail.Length;
    
        Greater_IntInt = (Len > 0);
    
        if (!Greater_IntInt)
            goto Label_2114;
    
        ChangeBuffsFromCards(_card, 0, giverID, 0x5, 0x7, NameDetail, CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        Label_2114:
        Array_RemoveItem = _cardsGivingAbility.Remove(giverID);
    
        if (!Array_RemoveItem)
            return;
    
        Array_Length_2 = _cardsGivingAbility.Length;
    
        EqualEqual_IntInt_1 = Array_Length_2 == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_2378;
    
        Label_2291:
        Map_Remove = _card->receivedAbilitiesFromCards.Remove(ability);
    
        goto Label_1839;
    
        Label_2378:
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingAbility;
    
        Map_Add(_card->receivedAbilitiesFromCards, ability, MakeStruct_CardsGivingAbility);
    
        goto Label_1839;
    
        Label_2500:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1245;
    
        Label_2574:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetAllCards(TArray<class UBaseCardObject*>& cards)
    {
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        cards = CallFunc_GetAllCardInBattle_AllCardsInBattle;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void AddDefenseToMultipleCards(const TArray<int>*& receiverIDs, int amount, int giverCardID, int& qqq)
    {
        Less_IntInt = (amount < 0);
    
        if (!Less_IntInt)
            goto Label_530;
    
        Temp_int_Loop_Counter_Variable_3 = 0;
    
        Temp_int_Array_Index_Variable_3 = 0;
    
        Label_99:
        Array_Length_3 = receiverIDs.Length;
    
        Less_IntInt_4 = (Temp_int_Loop_Counter_Variable_3 < Array_Length_3);
    
        if (!Less_IntInt_4)
            goto Label_934;
    
        Temp_int_Array_Index_Variable_3 = Temp_int_Loop_Counter_Variable_3;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        CallFunc_Array_Get_Item_3 = receiverIDs[Temp_int_Array_Index_Variable_3];
    
        GetCardFromID(CallFunc_Array_Get_Item_3, CallFunc_GetCardFromID_card_3);
    
        CallFunc_GetCardFromID_card_3->getTotalDefense(CallFunc_getTotalDefense_totalDefense_2);
    
        Add_IntInt_5 = CallFunc_getTotalDefense_totalDefense_2 + amount;
    
        CallFunc_GetCardFromID_card_3->setAndEncryptDefense(Add_IntInt_5, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        goto Label_2098;
    
        Label_530:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_576:
        Array_Length = receiverIDs.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt_1)
            goto Label_2300;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = receiverIDs[Temp_int_Array_Index_Variable_2];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card);
    
        ChangeDefense(CallFunc_GetCardFromID_card, giverCardID, amount, 0x1, false, CallFunc_ChangeDefense_qqq);
    
        goto Label_860;
    
        Label_860:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_576;
    
        Label_934:
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_980:
        Array_Length_2 = receiverIDs.Length;
    
        Less_IntInt_3 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_2);
    
        if (!Less_IntInt_3)
            goto Label_1404;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_2 = receiverIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item_2, CallFunc_GetCardFromID_card_2);
    
        CallFunc_GetCardFromID_card_2->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        CardFunctionsNotifier->NotifyGainDefense(CallFunc_Array_Get_Item_2, amount, CallFunc_getTotalDefense_totalDefense_1, giverCardID, 0x1);
    
        goto Label_1330;
    
        Label_1330:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_980;
    
        Label_1404:
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1450:
        Array_Length_1 = receiverIDs.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt_2)
            goto Label_2056;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = receiverIDs[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_1, CallFunc_GetCardFromID_card_1);
    
        CallFunc_GetCardFromID_card_1->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        Greater_IntInt = (CallFunc_getTotalDefense_totalDefense > 0);
    
        if (!Greater_IntInt)
            goto Label_2172;
    
        CallFunc_Array_Get_Item_1 = receiverIDs[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_1, CallFunc_GetCardFromID_card_1);
    
        Add_IntInt_4 = CallFunc_GetCardFromID_card_1->maxDefense + amount;
    
        CallFunc_GetCardFromID_card_1->maxDefense = Add_IntInt_4;
    
        goto Label_1982;
    
        Label_1982:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_1450;
    
        Label_2056:
        DestroyMultipleCards(cardsToDestroy, giverCardID, CallFunc_destroyMultipleCards_qqq);
    
        return;
    
        Label_2098:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_3 + 1;
    
        Temp_int_Loop_Counter_Variable_3 = Add_IntInt_3;
    
        goto Label_99;
    
        Label_2172:
        CallFunc_Array_Get_Item_1 = receiverIDs[Temp_int_Array_Index_Variable_1];
    
        Array_Add = cardsToDestroy.Add(CallFunc_Array_Get_Item_1);
    
        return;
    
        Label_2300:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void MoveUnitFromSupportToFrontLine(class UBaseCardObject* card, int instigatorID, bool& qqq)
    {
        card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            return;
    
        IsValid = card;
    
        if (!IsValid)
            goto Label_179;
    
        card->HasCustomAbility("cantMove", CallFunc_HasCustomAbility_doesIt);
    
        if (!CallFunc_HasCustomAbility_doesIt)
            goto Label_195;
    
        qqq = false;
    
        return;
    
        Label_179:
        qqq = false;
    
        return;
    
        Label_195:
        GameStateRef->GetFrontlineOwnerSide(CallFunc_GetFrontlineOwnerSide_ownerSide_1);
    
        card->GetOppositeSide(CallFunc_GetOppositeSide_oppositeSide);
    
        EqualEqual_ByteByte = ((!CallFunc_GetOppositeSide_oppositeSide) == (!CallFunc_GetFrontlineOwnerSide_ownerSide_1));
    
        if (!EqualEqual_ByteByte)
            goto Label_349;
    
        Label_333:
        qqq = false;
    
        return;
    
        Label_349:
        GameStateRef->GetFrontlineOwnerSide(CallFunc_GetFrontlineOwnerSide_ownerSide);
    
        EqualEqual_ByteByte_1 = ((!card->side) == (!CallFunc_GetFrontlineOwnerSide_ownerSide));
    
        if (!EqualEqual_ByteByte_1)
            goto Label_548;
    
        FetchCardsByLocation(0x7, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        if (!CallFunc_FetchCardsByLocation_isLocationFull)
            goto Label_548;
    
        goto Label_333;
    
        Label_548:
        GetNextCardLocationNumber(0x7, CallFunc_GetNextCardLocationNumber_locationNumber);
    
        MoveCardToFrontline(card->cardID, instigatorID, card->location, 0x7, CallFunc_GetNextCardLocationNumber_locationNumber, CallFunc_GetNextCardLocationNumber_locationNumber, true);
    
        goto Label_333;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetLocationCardBySide(class UBaseCardObject*& card, int& locationCardID, ESideEnum side)
    {
        GameStateRef->GetLocationCardBySide(side, CallFunc_GetLocationCardBySide_LocationCard, CallFunc_GetLocationCardBySide_LocationCardID);
    
        card = CallFunc_GetLocationCardBySide_LocationCard;
    
        locationCardID = CallFunc_GetLocationCardBySide_LocationCardID;
    
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void DrawSpecificCardFromDeckBySide(int instigatorID, int cardID, ESideEnum side, bool cardSeen)
    {
        GetDeckByside(side, CallFunc_GetDeckByside_deckCardIDs);
    
        Array_Contains = CallFunc_GetDeckByside_deckCardIDs[cardID];
    
        if (!Array_Contains)
            return;
    
        GameStateRef->RemoveCardFromDeckBySide(side, cardID, CallFunc_RemoveCardFromDeckBySide_removedIndex);
    
        GameStateRef->AddCardToDeckBySide(side, cardID, true, -1);
    
        DrawTopCardFromDeck(side, instigatorID, false, cardSeen, false, 0.4, false, CallFunc_DrawTopCardFromDeck_drawnCard);
    
        return;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetSupportLineLocationBySide(ESideEnum side, ECardLocationEnum& location)
    {
        EqualEqual_ByteByte_1 = ((!0x1) == (!side));
    
        if (!EqualEqual_ByteByte_1)
            goto Label_76;
    
        location = 0x5;
    
        return;
    
        Label_76:
        EqualEqual_ByteByte = ((!0x2) == (!side));
    
        if (!EqualEqual_ByteByte)
            goto Label_137;
    
        location = 0x6;
    
        Label_137:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetHandLocationBySide(ESideEnum side, ECardLocationEnum& handLocation)
    {
        EqualEqual_ByteByte = ((!side) == (!0x1));
    
        if (!EqualEqual_ByteByte)
            goto Label_70;
    
        handLocation = 0x3;
    
        return;
    
        Label_70:
        handLocation = 0x4;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void SpawnCardinHandbySide(ESideEnum side, FName card_name, int spawnerID, bool CardSeen, bool SkipDrawAnimation, bool fromOppositeSide, FString newCardText, FText*& campaignName, EFactionEnum salvageFaction, int& spawnedCardID)
    {
        TextIsEmpty = UKismetTextLibrary::TextIsEmpty(campaignName);
    
        if (!TextIsEmpty)
            goto Label_581;
    
        Label_43:
        Greater_IntInt = (spawnerID > 0);
    
        if (!Greater_IntInt)
            return;
    
        EqualEqual_ByteByte = ((!salvageFaction) == (!0x0));
    
        Temp_struct_Variable = FS_SalvagedCardInfo(false, 0x0, 0);
    
        MakeStruct_S_SalvagedCardInfo.isSalvaged_1_D83369C241D0F4E11CEDCB8250BC0D97 = true;
    
        MakeStruct_S_SalvagedCardInfo.salvageFaction_5_30136A02489F9A3E6C29FEB0A508ADD9 = salvageFaction;
    
        MakeStruct_S_SalvagedCardInfo.salvagedCardID_8_60B10C4245C90998186E6E9E7E180468 = 0;
    
        GetCardFromID(spawnerID, CallFunc_GetCardFromID_card);
    
        GetHandLocationBySide(side, CallFunc_GetHandLocationBySide_handLocation);
    
        Temp_bool_Variable = EqualEqual_ByteByte;
    
        CreateCard(side, card_name, CallFunc_GetHandLocationBySide_handLocation, 0, -1, true, CallFunc_GetCardFromID_card->isGoldCard, newCardText, CardSeen, SkipDrawAnimation, spawnerID, false, Temp_bool_Variable ? Temp_struct_Variable : MakeStruct_S_SalvagedCardInfo, false, false, fromOppositeSide, CallFunc_CreateCard_cardID);
    
        UpdateBondVisuals(side);
    
        spawnedCardID = CallFunc_CreateCard_cardID;
    
        return;
    
        Label_581:
        UFunctionLibrary::SetStaticCampaignName(card_name, campaignName);
    
        goto Label_43;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void SpawnCardonBattlefield(ESideEnum side, bool Frontline, FName card_name, int spawnerID, FText*& campaignName, bool giveBlitz, int locationNumber, EFactionEnum salvageFaction, bool makeVeteran, bool forceGoldCard, int& spawnedCardID)
    {
        Greater_IntInt = (spawnerID > 0);
    
        NotEqual_NameName = (card_name !== "None");
    
        BooleanAND = NotEqual_NameName && Greater_IntInt;
    
        if (!BooleanAND)
            goto Label_438;
    
        TextIsEmpty = UKismetTextLibrary::TextIsEmpty(campaignName);
    
        if (!TextIsEmpty)
            goto Label_466;
    
        Label_171:
        if (!Frontline)
            goto Label_499;
    
        spawnlocation = 0x7;
    
        Label_205:
        GetCardFromID(spawnerID, CallFunc_GetCardFromID_card);
    
        BooleanOR = (CallFunc_GetCardFromID_card->isGoldCard || forceGoldCard);
    
        SpawnCardToBoard(card_name, side, spawnlocation, locationNumber, 0, BooleanOR, giveBlitz, spawnerID, salvageFaction, makeVeteran, CallFunc_SpawnCardToBoard_cardSpawnedID);
    
        spawnedCardID = CallFunc_SpawnCardToBoard_cardSpawnedID;
    
        return;
    
        Label_438:
        spawnedCardID = 0;
    
        return;
    
        Label_466:
        UFunctionLibrary::SetStaticCampaignName(card_name, campaignName);
    
        goto Label_171;
    
        Label_499:
        GetSupportLineLocationBySide(side, CallFunc_GetSupportLineLocationBySide_location);
    
        spawnlocation = CallFunc_GetSupportLineLocationBySide_location;
    
        goto Label_205;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetDeckByside(ESideEnum side, TArray<int>& deckCardIDs)
    {
        GameStateRef->GetDeckBySide(side, CallFunc_GetDeckBySide_DeckCardIDs);
    
        deckCardIDs = CallFunc_GetDeckBySide_DeckCardIDs;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetDeckLocationBySide(ESideEnum side, ECardLocationEnum& deckLocation)
    {
        EqualEqual_ByteByte = ((!side) == (!0x1));
    
        if (!EqualEqual_ByteByte)
            goto Label_70;
    
        deckLocation = 0x1;
    
        return;
    
        Label_70:
        deckLocation = 0x2;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void DrawCardsFromDeckBySide(int instigatorID, ESideEnum side, int numCards, bool cardSeen, bool OpponentDraw, TArray<int>& cardsIDs, float drawDelay)
    {
        Temp_int_Variable = 1;
    
        Label_28:
        LessEqual_IntInt = (Temp_int_Variable <= numCards);
    
        if (!LessEqual_IntInt)
            goto Label_365;
    
        CallFunc_DrawTopCardFromDeck_delay_ImplicitCast = Cast<double>(drawDelay);
    
        DrawTopCardFromDeck(side, instigatorID, OpponentDraw, cardSeen, false, CallFunc_DrawTopCardFromDeck_delay_ImplicitCast, false, CallFunc_DrawTopCardFromDeck_drawnCard);
    
        Greater_IntInt = (CallFunc_DrawTopCardFromDeck_drawnCard > 0);
    
        if (!Greater_IntInt)
            goto Label_571;
    
        Array_Add_1 = drawnCards.Add(CallFunc_DrawTopCardFromDeck_drawnCard);
    
        Array_Add = cardSeenValues.Add(cardSeen);
    
        goto Label_645;
    
        Label_365:
        Array_IsEmpty = Array_IsEmpty(drawnCards);
    
        if (!Array_IsEmpty)
            goto Label_467;
    
        cardsIDs = TArray<cardsIDs>();
    
        return;
    
        Label_467:
        if (!cardSeen)
            goto Label_539;
    
        CardFunctionsNotifier->NotifyCardsSeen(drawnCards, cardSeenValues, false, false);
    
        return;
    
        Label_539:
        cardsIDs = drawnCards;
    
        return;
    
        Label_571:
        Add_IntInt = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt;
    
        goto Label_28;
    
        Label_645:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void DiscardRandomCardFromHand(ESideEnum side, int discarderID, int& discardedCardID)
    {
        GetAllCards(CallFunc_GetAllCards_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_74:
        Array_Length = CallFunc_GetAllCards_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_610;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GetHandLocationBySide = UCombatHelperFunctions::GetHandLocationBySide(side, this);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCards_cards[Temp_int_Array_Index_Variable];
    
        EqualEqual_ByteByte = ((!GetHandLocationBySide) == (!CallFunc_Array_Get_Item->location));
    
        EqualEqual_ByteByte_1 = ((!CallFunc_Array_Get_Item->side) == (!side));
    
        BooleanAND = EqualEqual_ByteByte_1 && EqualEqual_ByteByte;
    
        if (!BooleanAND)
            goto Label_832;
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCards_cards[Temp_int_Array_Index_Variable];
    
        Array_Add = possibleCards.Add(CallFunc_Array_Get_Item);
    
        goto Label_906;
    
        Label_610:
        GetRandomCard(possibleCards, false, CallFunc_GetRandomCard_randomCard);
    
        Greater_IntInt = (CallFunc_GetRandomCard_randomCard->cardID > 0);
    
        if (!Greater_IntInt)
            goto Label_778;
    
        DiscardCardFromHand(CallFunc_GetRandomCard_randomCard->cardID, discarderID, false, false, CallFunc_DiscardCardFromHand_success);
    
        Label_778:
        discardedCardID = CallFunc_GetRandomCard_randomCard->cardID;
    
        return;
    
        Label_832:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_74;
    
        Label_906:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void RemoveCardFromBoard(int cardID, int discarderID, bool& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->IsUnit(CallFunc_IsUnit_isIt);
    
        if (!CallFunc_IsUnit_isIt)
            goto Label_139;
    
        ApplyRemoveCardFromBoard(cardID, discarderID, false, false, false, false);
    
        Label_123:
        qqq = false;
    
        return;
    
        Label_139:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger(""Remove Card from Board" wants to remove HQ?", this);
    
        goto Label_123;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SpawnCardInDeckBySide(ESideEnum side, FName card_name, int spawnerID, int numberOfCards, EFactionEnum salvageFaction, bool HideFromOpponent, bool bottom, bool shuffle, bool SkipDrawAnimation, bool RandomWithoutShuffle, TArray<int>& spawnedCardIDs)
    {
        Greater_IntInt = (spawnerID > 0);
    
        if (!Greater_IntInt)
            goto Label_1362;
    
        Temp_int_Variable = 1;
    
        Label_72:
        LessEqual_IntInt = (Temp_int_Variable <= numberOfCards);
    
        if (!LessEqual_IntInt)
            goto Label_935;
    
        EqualEqual_ByteByte = ((!salvageFaction) == (!0x0));
    
        MakeStruct_S_SalvagedCardInfo.isSalvaged_1_D83369C241D0F4E11CEDCB8250BC0D97 = true;
    
        MakeStruct_S_SalvagedCardInfo.salvageFaction_5_30136A02489F9A3E6C29FEB0A508ADD9 = salvageFaction;
    
        MakeStruct_S_SalvagedCardInfo.salvagedCardID_8_60B10C4245C90998186E6E9E7E180468 = 0;
    
        GetCardFromID(spawnerID, CallFunc_GetCardFromID_card);
    
        Temp_struct_Variable = FS_SalvagedCardInfo(false, 0x0, 0);
    
        GetDeckLocationBySide(side, CallFunc_GetDeckLocationBySide_deckLocation);
    
        Temp_bool_Variable = EqualEqual_ByteByte;
    
        CreateCard(side, card_name, CallFunc_GetDeckLocationBySide_deckLocation, 0, -1, false, CallFunc_GetCardFromID_card->isGoldCard, "", false, SkipDrawAnimation, spawnerID, HideFromOpponent, Temp_bool_Variable ? Temp_struct_Variable : MakeStruct_S_SalvagedCardInfo, false, false, false, CallFunc_CreateCard_cardID);
    
        GetDeckByside(side, CallFunc_GetDeckByside_deckCardIDs);
    
        Array_Length = CallFunc_GetDeckByside_deckCardIDs.Length;
    
        RandomIntegerInRangeFromStream = UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, 0, Array_Length);
    
        SelectInt = (RandomWithoutShuffle ? RandomIntegerInRangeFromStream : -1);
    
        Not_PreBool = !bottom;
    
        GameStateRef->AddCardToDeckBySide(side, CallFunc_CreateCard_cardID, Not_PreBool, SelectInt);
    
        Array_Add = tmpspawnedcardids.Add(CallFunc_CreateCard_cardID);
    
        ExecuteOnAfterDeckChanged(side);
    
        goto Label_1288;
    
        Label_935:
        if (!shuffle)
            goto Label_1224;
    
        ShuffleDeckBySide(side, true, spawnerID, CallFunc_ShuffleDeckBySide_qqq);
    
        deckAnimationLocation = 0x3;
    
        Label_1011:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1192;
    
        GameStateRef->GetDeckBySide(side, CallFunc_GetDeckBySide_DeckCardIDs_1);
    
        CardFunctionsNotifier->NotifyNewDeck(side, CallFunc_GetDeckBySide_DeckCardIDs_1, tmpspawnedcardids, deckAnimationLocation, HideFromOpponent, shuffle);
    
        Label_1192:
        spawnedCardIDs = tmpspawnedcardids;
    
        return;
    
        Label_1224:
        if (!bottom)
            goto Label_1263;
    
        deckAnimationLocation = 0x1;
    
        goto Label_1011;
    
        Label_1263:
        deckAnimationLocation = 0x2;
    
        goto Label_1011;
    
        Label_1288:
        Add_IntInt = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt;
    
        goto Label_72;
    
        Label_1362:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void TriggerDestruction(class UBaseCardObject* card, int instigatorID, bool StealSide, bool RemoveDestruction, int& qqq)
    {
        CardOriginalSide = 0x0;
    
        IsValid = card;
    
        if (!IsValid)
            goto Label_671;
    
        CardID = card->cardID;
    
        CardOriginalSide = card->side;
    
        if (!StealSide)
            goto Label_276;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        JSON_SetInt(card, "destructionTriggerStolenOnTurn", CallFunc_GetTurnNumber_turnNumber, CallFunc_JSON_SetInt_found);
    
        Label_276:
        FetchAllCardsWithEventTrigger(0x18, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        localDestructionEffectTriggerCards = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_779;
    
        card->HasCustomAbility("destruction", CallFunc_HasCustomAbility_doesIt_1);
    
        card->CustomName1HasAttribute("StopDestructionEffect", CallFunc_CustomName1HasAttribute_doesIt);
    
        Not_PreBool = !CallFunc_CustomName1HasAttribute_doesIt;
    
        BooleanAND = Not_PreBool && card->hasDestruction;
    
        BooleanOR = (BooleanAND || CallFunc_HasCustomAbility_doesIt_1);
    
        if (!BooleanOR)
            goto Label_1674;
    
        ExecuteOnBeforeOtherCardDestroyed(CardID, instigatorID, true, false);
    
        goto Label_3253;
    
        Label_671:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("[Trigger Destruction] on an invalid card.", this);
    
        qqq = 0;
    
        return;
    
        Label_779:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_3);
    
        if (!CallFunc_IsActionProcess_ActionProcess_3)
            goto Label_3359;
    
        card->CustomName1HasAttribute("StopDestructionEffect", CallFunc_CustomName1HasAttribute_doesIt_1);
    
        Not_PreBool_1 = !CallFunc_CustomName1HasAttribute_doesIt_1;
    
        BooleanAND_1 = Not_PreBool_1 && card->hasDestruction;
    
        if (!BooleanAND_1)
            goto Label_3619;
    
        if (!StealSide)
            goto Label_1650;
    
        ConstructAndCopyCard(card, CallFunc_ConstructAndCopyCard_cardObject);
    
        localCardUsedForTriggeringDestructionEffect = CallFunc_ConstructAndCopyCard_cardObject;
    
        Temp_byte_Variable_1 = 0x1;
    
        Temp_byte_Variable_2 = 0x2;
    
        Temp_byte_Variable_3 = 0x0;
    
        Temp_byte_Variable = CardOriginalSide;
    
        localCardUsedForTriggeringDestructionEffect->side = switch (Temp_byte_Variable)
        {
            case 0x0:
            {
                return Temp_byte_Variable_3;
                break;
            }
            case 0x1:
            {
                return Temp_byte_Variable_2;
                break;
            }
            case 0x2:
            {
                return Temp_byte_Variable_1;
                break;
            }
            default:
            {
                return Select_Default;
                break;
            }
        };
    
        Label_1237:
        localCardUsedForTriggeringDestructionEffect->OnDestroyed(nullptr, true);
    
        MakeArray_Array_3 = [];
    
        ExecuteOnDestructionEffectTriggered(localCardUsedForTriggeringDestructionEffect, instigatorID, MakeArray_Array_3, localDestructionEffectTriggerCards, false, CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_2);
    
        Greater_IntInt = (CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_2 > 0);
    
        if (!Greater_IntInt)
            return;
    
        Temp_int_Variable = 1;
    
        Label_1413:
        LessEqual_IntInt = (Temp_int_Variable <= CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_2);
    
        if (!LessEqual_IntInt)
            return;
    
        localCardUsedForTriggeringDestructionEffect->OnDestroyed(nullptr, true);
    
        MakeArray_Array_2 = [];
    
        ExecuteOnDestructionEffectTriggered(localCardUsedForTriggeringDestructionEffect, instigatorID, MakeArray_Array_2, localDestructionEffectTriggerCards, false, CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_1);
    
        goto Label_1576;
    
        Label_1576:
        Add_IntInt = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt;
    
        goto Label_1413;
    
        Label_1650:
        localCardUsedForTriggeringDestructionEffect = card;
    
        goto Label_1237;
    
        Label_1674:
        card->HasCustomAbility("destruction", CallFunc_HasCustomAbility_doesIt_2);
    
        if (!CallFunc_HasCustomAbility_doesIt_2)
            return;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_2);
    
        if (!CallFunc_IsActionProcess_ActionProcess_2)
            return;
    
        Temp_byte_Variable_5 = 0x0;
    
        Temp_byte_Variable_4 = CardOriginalSide;
    
        Temp_bool_Variable = StealSide;
    
        Temp_byte_Variable_6 = 0x2;
    
        Temp_byte_Variable_7 = 0x1;
    
        card->side = Temp_bool_Variable ? switch (Temp_byte_Variable_4)
        {
            case 0x0:
            {
                return Temp_byte_Variable_5;
                break;
            }
            case 0x1:
            {
                return Temp_byte_Variable_6;
                break;
            }
            case 0x2:
            {
                return Temp_byte_Variable_7;
                break;
            }
            default:
            {
                return Select_Default_1;
                break;
            }
        } : CardOriginalSide;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_2077:
        Temp_string_Variable = "destruction";
    
        Map_Find = Map_Find(card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        Array_Length = CallFunc_Map_Find_Value.cardsGivingAbility.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_3203;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        Temp_string_Variable = "destruction";
    
        Map_Find = Map_Find(card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        CallFunc_Array_Get_Item = CallFunc_Map_Find_Value.cardsGivingAbility[Temp_int_Array_Index_Variable];
    
        localLoopCardID = CallFunc_Array_Get_Item;
    
        NotEqual_IntInt = (localLoopCardID !== CardID);
    
        if (!NotEqual_IntInt)
            goto Label_3129;
    
        GetCardFromID(localLoopCardID, CallFunc_GetCardFromID_card_1);
    
        CallFunc_GetCardFromID_card_1->OnOtherCardDestroyed(card, nullptr, true, 0x0, false, false);
    
        MakeArray_Array_1 = [ 0 ];
    
        ExecuteOnDestructionEffectTriggered(card, instigatorID, MakeArray_Array_1, localDestructionEffectTriggerCards, false, CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_3);
    
        Greater_IntInt_1 = (CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_3 > 0);
    
        if (!Greater_IntInt_1)
            return;
    
        Temp_int_Variable_1 = 1;
    
        Label_2842:
        LessEqual_IntInt_1 = (Temp_int_Variable_1 <= CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_3);
    
        if (!LessEqual_IntInt_1)
            return;
    
        GetCardFromID(localLoopCardID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->OnOtherCardDestroyed(card, nullptr, true, 0x0, false, false);
    
        MakeArray_Array = [ 0 ];
    
        ExecuteOnDestructionEffectTriggered(card, instigatorID, MakeArray_Array, localDestructionEffectTriggerCards, false, CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple);
    
        goto Label_3055;
    
        Label_3055:
        Add_IntInt_1 = Temp_int_Variable_1 + 1;
    
        Temp_int_Variable_1 = Add_IntInt_1;
    
        goto Label_2842;
    
        Label_3129:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt_2;
    
        goto Label_2077;
    
        Label_3203:
        card->side = CardOriginalSide;
    
        return;
    
        Label_3253:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            return;
    
        CardFunctionsNotifier->NotifyTriggerDestruction(CardID, instigatorID, StealSide, RemoveDestruction);
    
        return;
    
        Label_3359:
        if (!RemoveDestruction)
            return;
    
        card->HasCustomAbility("destruction", CallFunc_HasCustomAbility_doesIt);
    
        if (!CallFunc_HasCustomAbility_doesIt)
            goto Label_3488;
    
        CustomAbilityRemove("destruction", CardID, 0, true, CallFunc_CustomAbilityRemove_qqq);
    
        Label_3488:
        card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            return;
    
        card->CustomName1Add("StopDestructionEffect");
    
        PersistCustomFields(CardID, true);
    
        return;
    
        Label_3619:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ForceCardChangeLocation(int cardID, int instigatorID, ECardLocationEnum newLocation, int newLocationNumber, bool& moved, ECardLocationEnum& oldLocation, int& oldLocationNumber)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        card_ToBeForced = CallFunc_GetCardFromID_card;
    
        IsValid = card_ToBeForced;
    
        if (!IsValid)
            goto Label_218;
    
        card_ToBeForced->HasCustomAbility("cantMove", CallFunc_HasCustomAbility_doesIt);
    
        if (!CallFunc_HasCustomAbility_doesIt)
            goto Label_277;
    
        moved = false;
    
        oldLocation = 0x0;
    
        oldLocationNumber = 0;
    
        return;
    
        Label_218:
        moved = false;
    
        oldLocation = 0x0;
    
        oldLocationNumber = 0;
    
        return;
    
        Label_277:
        tmp_OldLocation = card_ToBeForced->location;
    
        tmp_OldLocationNumner = card_ToBeForced->locationNumber;
    
        EqualEqual_ByteByte = ((!tmp_OldLocation) == (!newLocation));
    
        EqualEqual_IntInt = tmp_OldLocationNumner == newLocationNumber;
    
        BooleanAND = EqualEqual_IntInt && EqualEqual_ByteByte;
    
        if (!BooleanAND)
            goto Label_562;
    
        moved = false;
    
        oldLocation = 0x0;
    
        oldLocationNumber = 0;
    
        return;
    
        Label_562:
        CardLocationMoved(cardID, instigatorID, tmp_OldLocation, newLocation, newLocationNumber, newLocationNumber, 0x7, false, false);
    
        moved = true;
    
        oldLocation = tmp_OldLocation;
    
        oldLocationNumber = tmp_OldLocationNumner;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void MakeVeteran(class UBaseCardObject* card, int& qqq)
    {
        _giveAttackIfGainingFury = false;
    
        card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        card->getHasVeteranUpgrade(CallFunc_getHasVeteranUpgrade_doesIt);
    
        card->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        Greater_IntInt = (CallFunc_getTotalDefense_totalDefense > 0);
    
        card->IsVeteran(false, CallFunc_IsVeteran_isIt);
    
        Not_PreBool_1 = !CallFunc_IsVeteran_isIt;
    
        BooleanAND_2 = Not_PreBool_1 && CallFunc_getHasVeteranUpgrade_doesIt;
    
        BooleanAND_3 = BooleanAND_2 && CallFunc_IsLocatedOnBoard_isIt;
    
        BooleanAND_4 = BooleanAND_3 && Greater_IntInt;
    
        if (!BooleanAND_4)
            goto Label_2921;
    
        GreaterEqual_IntInt = (card->attackCountThisTurn >= 2);
    
        card->getHasFury(CallFunc_getHasFury_doesIt);
    
        BooleanOR = (CallFunc_getHasFury_doesIt || GreaterEqual_IntInt);
    
        Not_PreBool = !BooleanOR;
    
        EqualEqual_IntInt = card->attackCountThisTurn == 1;
    
        card->HasAttackLeft(CallFunc_HasAttackLeft_doesIt);
    
        BooleanOR_1 = (CallFunc_HasAttackLeft_doesIt || EqualEqual_IntInt);
    
        BooleanAND = Not_PreBool && BooleanOR_1;
    
        _giveAttackIfGainingFury = BooleanAND;
    
        JSON_SetBool(card, "veteran", true, CallFunc_JSON_SetBool_found);
    
        card->getStaticVeteranUpgrade(CallFunc_getStaticVeteranUpgrade_staticVeteranCard);
    
        vet_card = CallFunc_getStaticVeteranUpgrade_staticVeteranCard;
    
        vet_card->getAndDecryptAttack(CallFunc_getAndDecryptAttack_decryptedAttack);
    
        ChangeAttack(card, card->cardID, CallFunc_getAndDecryptAttack_decryptedAttack, 0x5, false, CallFunc_ChangeAttack_qqq);
    
        vet_card->getAndDecryptDefense(CallFunc_getAndDecryptDefense_decryptedDefense);
    
        ChangeDefense(card, card->cardID, CallFunc_getAndDecryptDefense_decryptedDefense, 0x5, false, CallFunc_ChangeDefense_qqq);
    
        ChangeOperationCost(card, card->cardID, vet_card->operationCost, 0x5, false, false, false);
    
        vet_card->getTotalHeavyArmor(CallFunc_getTotalHeavyArmor_totalHeavyArmor);
    
        ChangeHeavyArmor(card, card->cardID, CallFunc_getTotalHeavyArmor_totalHeavyArmor, 0x5, false, CallFunc_ChangeHeavyArmor_qqq);
    
        card->hasAmbush = vet_card->hasAmbush;
    
        card->hasBlitz = vet_card->hasBlitz;
    
        card->hasFury = vet_card->hasFury;
    
        card->hasMobilize = vet_card->hasMobilize;
    
        card->hasShock = vet_card->hasShock;
    
        card->effectType = vet_card->effectType;
    
        card->hasDestruction = vet_card->hasDestruction;
    
        card->hasSmokescreen = vet_card->hasSmokescreen;
    
        BooleanAND_1 = vet_card->hasFury && _giveAttackIfGainingFury;
    
        if (!BooleanAND_1)
            goto Label_1997;
    
        Add_IntInt_1 = card->attackLeft + 1;
    
        Temp_int_Variable = Add_IntInt_1;
    
        card->attackLeft = Temp_int_Variable;
    
        goto Label_2349;
    
        Label_1997:
        card->HasCustomAbility("guard", CallFunc_HasCustomAbility_doesIt);
    
        if (!CallFunc_HasCustomAbility_doesIt)
            goto Label_2060;
    
        return;
    
        Label_2060:
        NotEqual_BoolBool = (card->hasGuard !== vet_card->hasGuard);
    
        if (!NotEqual_BoolBool)
            return;
    
        card->hasGuard = vet_card->hasGuard;
    
        if (!card->hasGuard)
            goto Label_2303;
    
        RemoveSmokescreen(card->cardID, 0, true, true);
    
        Label_2303:
        UpdateGuarded(card->location);
    
        return;
    
        Label_2349:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->MakeCardVeteran(card);
    
        if (!card->isSuppressed)
            goto Label_2806;
    
        Label_2463:
        FetchAllCardsWithEventTrigger(0x20, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_2534:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_2782;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardBecomingVeteran(card);
    
        goto Label_2847;
    
        Label_2782:
        ExecuteOnOtherCardsAbilitiesChanged(card);
    
        return;
    
        Label_2806:
        card->OnBecomingVeteran();
    
        goto Label_2463;
    
        Label_2847:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_2534;
    
        Label_2921:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void AddKreditsTax(class UBaseCardObject* card, int costToAdd, int instigatorID, bool& qqq)
    {
        IsValid = card;
    
        if (!IsValid)
            goto Label_340;
    
        Add_IntInt = card->KreditsTax_AsEnemyTarget + costToAdd;
    
        Max = ((Add_IntInt > 0) ? Add_IntInt : 0);
    
        card->KreditsTax_AsEnemyTarget = Max;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_324;
    
        CardFunctionsNotifier->NotifyAddKreditsTax(card->cardID, costToAdd, instigatorID);
    
        Label_324:
        qqq = false;
    
        return;
    
        Label_340:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger(""Add Kredits Tax" on an invalid card", this);
    
        qqq = false;
    
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnDestructionEffectTriggered(class UBaseCardObject* cardTriggered, int instigatorID, TArray<int>*& CardsToDestroy, TArray<class UBaseCardObject*>*& DestructionEffectTriggerCards, bool skipSuppressCheck, int& output_TriggerMultiple)
    {
        localTriggerMultiple = 0;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_74:
        Array_Length = DestructionEffectTriggerCards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_604;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = DestructionEffectTriggerCards[Temp_int_Array_Index_Variable];
    
        localCardID_inLoop = CallFunc_Array_Get_Item->cardID;
    
        if (!skipSuppressCheck)
            goto Label_710;
    
        Label_339:
        CallFunc_Array_Get_Item = DestructionEffectTriggerCards[Temp_int_Array_Index_Variable];
    
        Array_Contains = CardsToDestroy[localCardID_inLoop];
    
        CallFunc_Array_Get_Item->OnDestructionEffectTriggered(cardTriggered, instigatorID, Array_Contains, CallFunc_OnDestructionEffectTriggered_TriggerMultiple);
    
        Add_IntInt_1 = CallFunc_OnDestructionEffectTriggered_TriggerMultiple + localTriggerMultiple;
    
        localTriggerMultiple = Add_IntInt_1;
    
        goto Label_636;
    
        Label_604:
        output_TriggerMultiple = localTriggerMultiple;
    
        return;
    
        Label_636:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_74;
    
        Label_710:
        if (!cardTriggered->isSuppressed)
            goto Label_339;
    
        goto Label_747;
    
        Label_747:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void SetCountdown(int cardID, int value, bool& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        JSON_SetInt(CallFunc_GetCardFromID_card, "countdown_timer", value, CallFunc_JSON_SetInt_found);
    
        PersistCustomFields(cardID, true);
    
        qqq = false;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void DecrementCountdown(int cardID, bool& countdownFinished, bool& countdownFound)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_1);
    
        JSON_GetInt(CallFunc_GetCardFromID_card_1, "countdown_timer", CallFunc_JSON_GetInt_value, CallFunc_JSON_GetInt_found);
    
        if (!CallFunc_JSON_GetInt_found)
            goto Label_371;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        Subtract_IntInt = CallFunc_JSON_GetInt_value - 1;
    
        JSON_SetInt(CallFunc_GetCardFromID_card, "countdown_timer", Subtract_IntInt, CallFunc_JSON_SetInt_found);
    
        PersistCustomFields(cardID, true);
    
        Subtract_IntInt = CallFunc_JSON_GetInt_value - 1;
    
        LessEqual_IntInt = (Subtract_IntInt <= 0);
    
        countdownFinished = LessEqual_IntInt;
    
        countdownFound = true;
    
        return;
    
        Label_371:
        countdownFinished = false;
    
        countdownFound = false;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SuppressUnit(int cardID, int instigatorID, bool& qqq)
    {
        MakeArray_Array = [ cardID ];
    
        SuppressMultipleUnits(MakeArray_Array, instigatorID, CallFunc_SuppressMultipleUnits_qqq);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SuppressMultipleUnits(const TArray<int>*& cardsToSuppress, int instigatorID, bool& qqq)
    {
        _staticAttack = 0;
    
        _staticDefense = 0;
    
        _staticOperationCost = 0;
    
        tmpOperationCost = 0;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_3);
    
        if (!CallFunc_IsActionProcess_ActionProcess_3)
            goto Label_190;
    
        CardFunctionsNotifier->NotifySuppressMultipleUnits(cardsToSuppress, instigatorID);
    
        goto Label_7867;
    
        Label_190:
        Temp_int_Loop_Counter_Variable_3 = 0;
    
        Temp_int_Array_Index_Variable_3 = 0;
    
        Label_236:
        Array_Length = cardsToSuppress.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_3 < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1117;
    
        Temp_int_Array_Index_Variable_3 = Temp_int_Loop_Counter_Variable_3;
    
        CallFunc_Array_Get_Item = cardsToSuppress[Temp_int_Array_Index_Variable_3];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        _card->HasCustomAbility("cantBeSuppressed", CallFunc_HasCustomAbility_doesIt);
    
        _card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        Not_PreBool = !CallFunc_HasCustomAbility_doesIt;
    
        BooleanAND = CallFunc_IsLocatedOnBoard_isIt && Not_PreBool;
    
        if (!BooleanAND)
            goto Label_1284;
    
        _wasAlreadySuppressed = _card->isSuppressed;
    
        _card->isSuppressed = true;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_2);
    
        if (!CallFunc_IsActionProcess_ActionProcess_2)
            goto Label_1358;
    
        if (!_wasAlreadySuppressed)
            goto Label_5963;
    
        Label_802:
        FetchAllCardsWithEventTrigger(0x3A, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_873:
        Array_Length_2 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_2);
    
        if (!Less_IntInt_1)
            goto Label_4510;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable_2];
    
        CallFunc_Array_Get_Item_1->OnOtherCardSuppressed(_card);
    
        goto Label_6004;
    
        Label_1117:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_5541;
    
        _card->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_1268;
    
        RevealCard(_card->cardID, instigatorID, CallFunc_RevealCard_qqq);
    
        Label_1268:
        qqq = false;
    
        return;
    
        Label_1284:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_3 + 1;
    
        Temp_int_Loop_Counter_Variable_3 = Add_IntInt_3;
    
        goto Label_236;
    
        Label_1358:
        RemoveGuard(_card->cardID, 0, true, false);
    
        RemoveFury(_card->cardID, 0, true);
    
        RemoveBlitz(_card->cardID, CallFunc_RemoveBlitz_qqq, 0, true);
    
        RemoveImmune(_card->cardID, 0, CallFunc_RemoveImmune_qqq, true);
    
        RemoveAlpine(_card->cardID, CallFunc_RemoveAlpine_qqq, true, 0);
    
        RemoveAmbush(_card->cardID, 0, true, true);
    
        RemoveMobilize(_card->cardID, 0, true, true, CallFunc_RemoveMobilize_qqq);
    
        RemoveSmokescreen(_card->cardID, 0, true, true);
    
        ChangeHeavyArmor(_card, instigatorID, 0, 0x3, true, CallFunc_ChangeHeavyArmor_qqq);
    
        RemoveSalvage(_card->cardID, 0, CallFunc_RemoveSalvage_qqq, false);
    
        RemoveShock(_card->cardID, 0, true, true, CallFunc_RemoveShock_qqq);
    
        _card->hasDestruction = false;
    
        _card->exileNation = 0x0;
    
        _card->hasActivePincerEffect(CallFunc_hasActivePincerEffect_doesIt);
    
        if (!CallFunc_hasActivePincerEffect_doesIt)
            goto Label_2129;
    
        RemovePincerEffects(_card);
    
        Label_2129:
        _card->customName1 = "None";
    
        _card->customName2 = "None";
    
        _card->KreditsTax_AsEnemyTarget = 0;
    
        _card->IsVeteran(true, CallFunc_IsVeteran_isIt);
    
        _tmp_hasVeteran = CallFunc_IsVeteran_isIt;
    
        JsonHasField = UBlueprintJsonLibrary::JsonHasField(_card->customJson, "suppressionException");
    
        if (!JsonHasField)
            goto Label_4428;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(_card->customJson, "suppressionException");
    
        _customJSONException = Conv_JsonObjectToJsonValue;
    
        JsonMake = UBlueprintJsonLibrary::JsonMake();
    
        _card->customJson = JsonMake;
    
        JsonMakeField_1 = UBlueprintJsonLibrary::JsonMakeField(_card->customJson, "suppressionException", _customJSONException);
    
        _card->customJson = JsonMakeField_1;
    
        Label_2752:
        if (!_tmp_hasVeteran)
            goto Label_2921;
    
        JsonMakeBool = UBlueprintJsonLibrary::JsonMakeBool(true);
    
        JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(_card->customJson, "veteran", JsonMakeBool);
    
        _card->customJson = JsonMakeField;
    
        Label_2921:
        _card->effectType = 0x0;
    
        CallFunc_Map_Keys_Keys = [];
    
        Map_Keys(_card->receivedAbilitiesFromCards, CallFunc_Map_Keys_Keys);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_3092:
        Array_Length_5 = CallFunc_Map_Keys_Keys.Length;
    
        Less_IntInt_5 = (Temp_int_Loop_Counter_Variable < Array_Length_5);
    
        if (!Less_IntInt_5)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        MakeArray_Array = [ "trigger", "destruction", "passive", "lethal", "custom" ];
    
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Array_Contains = MakeArray_Array[CallFunc_Array_Get_Item_2];
    
        if (!Array_Contains)
            goto Label_6152;
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_3468:
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value_1);
    
        Array_Length_3 = CallFunc_Map_Find_Value_1.cardsGivingAbility.Length;
    
        Less_IntInt_3 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_3);
    
        if (!Less_IntInt_3)
            goto Label_7651;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value_1);
    
        CallFunc_Array_Get_Item_4 = CallFunc_Map_Find_Value_1.cardsGivingAbility[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_4, CallFunc_GetCardFromID_card_1);
    
        IsValid = CallFunc_GetCardFromID_card_1;
    
        if (!IsValid)
            goto Label_7793;
    
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value_1);
    
        CallFunc_Array_Get_Item_4 = CallFunc_Map_Find_Value_1.cardsGivingAbility[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_4, CallFunc_GetCardFromID_card_1);
    
        Conv_NameToString = FString(CallFunc_GetCardFromID_card_1->name);
    
        ChangeBuffsFromCards(_card, 0, CallFunc_Array_Get_Item_4, 0x5, 0x7, Conv_NameToString, CallFunc_ChangeBuffsFromCards_amountRemoved_2);
    
        goto Label_6078;
    
        Label_4428:
        JsonMake_1 = UBlueprintJsonLibrary::JsonMake();
    
        _card->customJson = JsonMake_1;
    
        goto Label_2752;
    
        Label_4510:
        GetStaticCard = UFunctionLibrary::GetStaticCard(_card->name);
    
        StaticCardRef = GetStaticCard;
    
        if (!_card->isSalvaged)
            goto Label_4829;
    
        _staticAttack = 1;
    
        _staticDefense = 1;
    
        Label_4667:
        _staticOperationCost = StaticCardRef->operationCost;
    
        _card->range = StaticCardRef->range;
    
        JSON_Clear(_card, "veteran", CallFunc_JSON_Clear_found);
    
        goto Label_4970;
    
        Label_4829:
        StaticCardRef->getAndDecryptAttack(CallFunc_getAndDecryptAttack_decryptedAttack);
    
        _staticAttack = CallFunc_getAndDecryptAttack_decryptedAttack;
    
        StaticCardRef->getAndDecryptDefense(CallFunc_getAndDecryptDefense_decryptedDefense);
    
        _staticDefense = CallFunc_getAndDecryptDefense_decryptedDefense;
    
        goto Label_4667;
    
        Label_4970:
        _card->getAndDecryptAttack(CallFunc_getAndDecryptAttack_decryptedAttack_1);
    
        Subtract_IntInt = CallFunc_getAndDecryptAttack_decryptedAttack_1 - _staticAttack;
    
        attackDifference = Subtract_IntInt;
    
        NotEqual_IntInt = (attackDifference !== 0);
    
        if (!NotEqual_IntInt)
            goto Label_5484;
    
        ChangeAttack(_card, instigatorID, _staticAttack, 0x3, false, CallFunc_ChangeAttack_qqq);
    
        Label_5185:
        _card->maxDefense = _staticDefense;
    
        _card->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        Greater_IntInt = (CallFunc_getTotalDefense_totalDefense > _staticDefense);
    
        if (!Greater_IntInt)
            goto Label_5427;
    
        ChangeDefense(_card, instigatorID, _staticDefense, 0x3, false, CallFunc_ChangeDefense_qqq);
    
        Label_5380:
        ChangeOperationCost(_card, instigatorID, _staticOperationCost, 0x3, false, false, false);
    
        return;
    
        Label_5427:
        ChangeBuffsFromCards(_card, 0, instigatorID, 0x1, 0x3, "", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_5380;
    
        Label_5484:
        ChangeBuffsFromCards(_card, 0, instigatorID, 0x0, 0x3, "", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        goto Label_5185;
    
        Label_5541:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        FetchAllCardsWithEventTrigger(0xB, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_4 = 0;
    
        Temp_int_Array_Index_Variable_5 = 0;
    
        Label_5645:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_4 < Array_Length_1);
    
        if (!Less_IntInt_2)
            return;
    
        Temp_int_Array_Index_Variable_5 = Temp_int_Loop_Counter_Variable_4;
    
        CallFunc_Array_Get_Item_5 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_5];
    
        CallFunc_Array_Get_Item_5->OnAfterOtherCardSuppressed(_card);
    
        goto Label_5889;
    
        Label_5889:
        Add_IntInt_4 = Temp_int_Loop_Counter_Variable_4 + 1;
    
        Temp_int_Loop_Counter_Variable_4 = Add_IntInt_4;
    
        goto Label_5645;
    
        Label_5963:
        _card->OnSuppressed();
    
        goto Label_802;
    
        Label_6004:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_873;
    
        Label_6078:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_3092;
    
        Label_6152:
        _tmp_customAbilityGivers.Clear();
    
        Temp_int_Loop_Counter_Variable_5 = 0;
    
        Temp_int_Array_Index_Variable_4 = 0;
    
        Label_6239:
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value);
    
        Array_Length_4 = CallFunc_Map_Find_Value.cardsGivingAbility.Length;
    
        Less_IntInt_4 = (Temp_int_Loop_Counter_Variable_5 < Array_Length_4);
    
        if (!Less_IntInt_4)
            goto Label_7267;
    
        Temp_int_Array_Index_Variable_4 = Temp_int_Loop_Counter_Variable_5;
    
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value);
    
        CallFunc_Array_Get_Item_3 = CallFunc_Map_Find_Value.cardsGivingAbility[Temp_int_Array_Index_Variable_4];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item_3 == _card->cardID;
    
        EqualEqual_IntInt_1 = CallFunc_Array_Get_Item_3 == 0;
    
        BooleanOR = (EqualEqual_IntInt_1 || EqualEqual_IntInt);
    
        if (!BooleanOR)
            goto Label_6906;
    
        goto Label_7193;
    
        Label_6906:
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value);
    
        CallFunc_Array_Get_Item_3 = CallFunc_Map_Find_Value.cardsGivingAbility[Temp_int_Array_Index_Variable_4];
    
        Array_Add = _tmp_customAbilityGivers.Add(CallFunc_Array_Get_Item_3);
    
        return;
    
        Label_7193:
        Add_IntInt_5 = Temp_int_Loop_Counter_Variable_5 + 1;
    
        Temp_int_Loop_Counter_Variable_5 = Add_IntInt_5;
    
        goto Label_6239;
    
        Label_7267:
        Array_IsEmpty = Array_IsEmpty(_tmp_customAbilityGivers);
    
        if (!Array_IsEmpty)
            goto Label_7474;
    
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Remove = _card->receivedAbilitiesFromCards.Remove(CallFunc_Array_Get_Item_2);
    
        return;
    
        Label_7474:
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _tmp_customAbilityGivers;
    
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Add(_card->receivedAbilitiesFromCards, CallFunc_Array_Get_Item_2, MakeStruct_CardsGivingAbility);
    
        return;
    
        Label_7651:
        CallFunc_Array_Get_Item_2 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable];
    
        Map_Remove_1 = _card->receivedAbilitiesFromCards.Remove(CallFunc_Array_Get_Item_2);
    
        return;
    
        Label_7793:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_3468;
    
        Label_7867:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveSalvage(int cardID, int instigatorID, int& qqq, bool skipAction)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_722;
    
        if (!_card->hasSalvage)
            goto Label_993;
    
        Temp_string_Variable = "salvage";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_798;
    
        Temp_string_Variable = "salvage";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        localInstigatorArray = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_464:
        Array_Length = localInstigatorArray.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = localInstigatorArray[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "salvage", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_919;
    
        Label_722:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("RemoveSalvage must have a valid card", this);
    
        return;
    
        Label_798:
        _card->hasSalvage = false;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyRemoveSalvage(cardID, instigatorID);
    
        return;
    
        Label_919:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_464;
    
        Label_993:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveSalvage(int cardID, int instigatorID, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_178;
    
        CanCardBeBuffed(_card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_1145;
    
        if (!_card->hasSalvage)
            goto Label_254;
    
        return;
    
        Label_178:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("GiveSalvage must have a valid target", this);
    
        return;
    
        Label_254:
        Temp_string_Variable = "salvage";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_593;
    
        Temp_string_Variable = "salvage";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        Array_Contains = CallFunc_Map_Find_Value.cardsGivingAbility[instigatorID];
    
        if (!Array_Contains)
            goto Label_986;
    
        goto Label_865;
    
        Label_593:
        Array_Add = instigatorArry.Add(instigatorID);
    
        ChangeBuffsFromCards(_card, 1, instigatorID, 0x6, 0x8, "salvage", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        Temp_string_Variable_1 = "salvage";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = instigatorArry;
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        return;
    
        Label_865:
        _card->hasSalvage = true;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyGiveSalvage(cardID, instigatorID);
    
        return;
    
        Label_986:
        Temp_string_Variable = "salvage";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        instigatorArry = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        goto Label_593;
    
        Label_1145:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveAlpine(int cardID, int& qqq, int giverID)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        CanCardBeBuffed(_card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            return;
    
        Greater_IntInt = (giverID > 0);
    
        if (!Greater_IntInt)
            goto Label_508;
    
        Temp_string_Variable = "alpine";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_429;
    
        Temp_string_Variable = "alpine";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        _cardsGivingAlpine = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Label_429:
        Array_Contains = _cardsGivingAlpine[giverID];
    
        if (!Array_Contains)
            goto Label_678;
    
        return;
    
        Label_508:
        if (!_card->hasAlpine)
            goto Label_549;
    
        return;
    
        Label_549:
        _card->hasAlpine = true;
    
        Label_582:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyGiveAlpine(cardID, giverID);
    
        return;
    
        Label_678:
        Array_Add = _cardsGivingAlpine.Add(giverID);
    
        ChangeBuffsFromCards(_card, 1, giverID, 0x6, 0x8, "alpine", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingAlpine;
    
        Temp_string_Variable_1 = "alpine";
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_582;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveAlpine(int cardID, int& qqq, bool skipAction, int giverID)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_2005;
    
        LessEqual_IntInt = (giverID <= 0);
    
        if (!LessEqual_IntInt)
            goto Label_782;
    
        _card->getHasAlpine(CallFunc_getHasAlpine_doesIt);
    
        if (!CallFunc_getHasAlpine_doesIt)
            return;
    
        Temp_string_Variable_4 = "alpine";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_4, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1785;
    
        Temp_string_Variable_4 = "alpine";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_4, CallFunc_Map_Find_Value);
    
        _alpineGivers = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_525:
        Array_Length = _alpineGivers.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = _alpineGivers[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "alpine", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_1931;
    
        Label_782:
        Temp_string_Variable_2 = "alpine";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        if (!Map_Find_1)
            return;
    
        Temp_string_Variable_2 = "alpine";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        Array_Contains = CallFunc_Map_Find_Value_1.cardsGivingAbility[giverID];
    
        if (!Array_Contains)
            return;
    
        Temp_string_Variable_2 = "alpine";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_2, CallFunc_Map_Find_Value_1);
    
        _alpineGivers = CallFunc_Map_Find_Value_1.cardsGivingAbility;
    
        Array_RemoveItem = _alpineGivers.Remove(giverID);
    
        ChangeBuffsFromCards(_card, -1, giverID, 0x6, 0x8, "alpine", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        Array_IsEmpty = Array_IsEmpty(_alpineGivers);
    
        if (!Array_IsEmpty)
            goto Label_1637;
    
        Temp_string_Variable = "alpine";
    
        Map_Remove_1 = _card->receivedAbilitiesFromCards.Remove(Temp_string_Variable);
    
        Label_1549:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->HandleRemoveAlpine(cardID, giverID);
    
        return;
    
        Label_1637:
        Temp_string_Variable_1 = "alpine";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _alpineGivers;
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_1549;
    
        Label_1785:
        _card->hasAlpine = false;
    
        Temp_string_Variable_3 = "alpine";
    
        Map_Remove = _card->receivedAbilitiesFromCards.Remove(Temp_string_Variable_3);
    
        goto Label_1549;
    
        Label_1931:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_525;
    
        Label_2005:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void StealCardFromBoardToDeck(int cardID, int instigatorID, ESideEnum deckSide, int& qqq)
    {
        oldLocation = 0x0;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _cardToSteal = CallFunc_GetCardFromID_card;
    
        oldLocation = _cardToSteal->location;
    
        ApplyRemoveCardFromBoard(cardID, instigatorID, false, false, true, false);
    
        MakeStruct_S_SalvagedCardInfo.isSalvaged_1_D83369C241D0F4E11CEDCB8250BC0D97 = _cardToSteal->isSalvaged;
    
        MakeStruct_S_SalvagedCardInfo.salvageFaction_5_30136A02489F9A3E6C29FEB0A508ADD9 = _cardToSteal->salvageFaction;
    
        MakeStruct_S_SalvagedCardInfo.salvagedCardID_8_60B10C4245C90998186E6E9E7E180468 = cardID;
    
        GetDeckLocationBySide(deckSide, CallFunc_GetDeckLocationBySide_deckLocation);
    
        CreateCard(deckSide, _cardToSteal->name, CallFunc_GetDeckLocationBySide_deckLocation, 0, -1, false, _cardToSteal->isGoldCard, "", false, false, instigatorID, false, MakeStruct_S_SalvagedCardInfo, false, false, false, CallFunc_CreateCard_cardID);
    
        GameStateRef->AddCardToDeckBySide(deckSide, CallFunc_CreateCard_cardID, true, -1);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_641;
    
        CardFunctionsNotifier->NotifyStealCardFromBoardToDeck(cardID, instigatorID, oldLocation, deckSide);
    
        Label_641:
        ShuffleDeckBySide(deckSide, false, instigatorID, CallFunc_ShuffleDeckBySide_qqq);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void RemoveMultipleCardsFromBoard(const TArray<int>*& cardIDs, int discarderID, bool& qqq)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Array_Length = cardIDs.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_432;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = cardIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->IsUnit(CallFunc_IsUnit_isIt);
    
        if (!CallFunc_IsUnit_isIt)
            goto Label_502;
    
        CallFunc_Array_Get_Item = cardIDs[Temp_int_Array_Index_Variable];
    
        ApplyRemoveCardFromBoard(CallFunc_Array_Get_Item, discarderID, false, false, true, false);
    
        goto Label_576;
    
        Label_432:
        CardFunctionsNotifier->NotifyRemoveMultipleCardsFromBoard(cardIDs, discarderID);
    
        qqq = false;
    
        return;
    
        Label_502:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_576:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SpawnMultipleCardsOnBattlefield(ESideEnum side, bool Frontline, const TArray<FName>*& cardNames, int spawnerID, bool giveBlitz, TArray<int>& spawnedCardIDs, bool makeVeteran)
    {
        isGoldCard = false;
    
        Greater_IntInt = (spawnerID > 0);
    
        Array_IsNotEmpty = cardNames.Length > 0;
    
        BooleanAND = Array_IsNotEmpty && Greater_IntInt;
    
        if (!BooleanAND)
            goto Label_771;
    
        if (!Frontline)
            goto Label_808;
    
        spawnlocation = 0x7;
    
        Label_187:
        GetCardFromID(spawnerID, CallFunc_GetCardFromID_card_2);
    
        isGoldCard = CallFunc_GetCardFromID_card_2->isGoldCard;
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_317:
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Array_Length_1 = cardNames.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        BooleanAND_1 = Not_PreBool && Less_IntInt;
    
        if (!BooleanAND_1)
            goto Label_872;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = cardNames[Temp_int_Array_Index_Variable];
    
        cardNameToSpawn = CallFunc_Array_Get_Item_1;
    
        FetchCardsByLocation(spawnlocation, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        tmpLocationFull = CallFunc_FetchCardsByLocation_isLocationFull;
    
        NotEqual_ByteByte = ((!spawnlocation) !== (!0x7));
    
        if (!NotEqual_ByteByte)
            goto Label_1855;
    
        Label_745:
        if (!tmpLocationFull)
            goto Label_2217;
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        goto Label_1781;
    
        Label_771:
        spawnedCardIDs = TArray<spawnedCardIDs>();
    
        return;
    
        Label_808:
        GetSupportLineLocationBySide(side, CallFunc_GetSupportLineLocationBySide_location);
    
        spawnlocation = CallFunc_GetSupportLineLocationBySide_location;
    
        goto Label_187;
    
        Label_872:
        Array_IsNotEmpty_1 = spawnedCardIDs.Length > 0;
    
        if (!Array_IsNotEmpty_1)
            goto Label_1744;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_1055;
    
        CardFunctionsNotifier->NotifySpawnMultipleCards(side, spawnedCardIDs, spawnerID, cardNames, spawnlocation);
    
        Label_1055:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_1101:
        Array_Length_2 = spawnedCardIDs.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt_1)
            goto Label_1712;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_2 = spawnedCardIDs[Temp_int_Array_Index_Variable_2];
    
        GetCardFromID(CallFunc_Array_Get_Item_2, CallFunc_GetCardFromID_card);
    
        cardSpawned = CallFunc_GetCardFromID_card;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2627;
    
        FetchAllCardsWithEventTrigger(0x23, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1462:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_2 < Array_Length);
    
        if (!Less_IntInt_2)
            goto Label_2820;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item->OnOtherCardCreatedAlterCard(cardSpawned, 0x3);
    
        goto Label_2996;
    
        Label_1712:
        spawnedCardIDs = spawnedCardIDs;
    
        return;
    
        Label_1744:
        spawnedCardIDs = TArray<spawnedCardIDs>();
    
        return;
    
        Label_1781:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_317;
    
        Label_1855:
        Temp_byte_Variable = 0x0;
    
        Temp_byte_Variable_1 = 0x2;
    
        Temp_byte_Variable_2 = 0x1;
    
        GameStateRef->GetFrontlineOwnerSide(CallFunc_GetFrontlineOwnerSide_ownerSide);
    
        Temp_byte_Variable_3 = side;
    
        NotEqual_ByteByte_1 = ((!CallFunc_GetFrontlineOwnerSide_ownerSide) !== (!switch (Temp_byte_Variable_3)
        {
            case 0x0:
            {
                return Temp_byte_Variable;
                break;
            }
            case 0x1:
            {
                return Temp_byte_Variable_1;
                break;
            }
            case 0x2:
            {
                return Temp_byte_Variable_2;
                break;
            }
            default:
            {
                return Select_Default;
                break;
            }
        }));
    
        if (!NotEqual_ByteByte_1)
            goto Label_2105;
    
        goto Label_745;
    
        Label_2105:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Trying to move a unit to frontline but frontline owned by the other side", this);
    
        goto Label_2553;
    
        Label_2217:
        CreateCard(side, cardNameToSpawn, spawnlocation, 0, -1, false, isGoldCard, "", false, false, spawnerID, false, FS_SalvagedCardInfo(false, 0x0, 0), true, makeVeteran, false, CallFunc_CreateCard_cardID);
    
        spawnedID = CallFunc_CreateCard_cardID;
    
        Array_Add = spawnedCardIDs.Add(spawnedID);
    
        GetCardFromID(spawnedID, CallFunc_GetCardFromID_card_1);
    
        cardSpawned = CallFunc_GetCardFromID_card_1;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        cardSpawned->enterPlayOnTurn = CallFunc_GetTurnNumber_turnNumber;
    
        goto Label_3070;
    
        Label_2553:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1101;
    
        Label_2627:
        MakeSet_Set = TArray { spawnlocation };;
    
        RefreshLocationStatus(MakeSet_Set);
    
        ExecuteOnCardLocationMoved(cardSpawned->cardID, 0x0, spawnlocation, false, 0xC);
    
        EqualEqual_ByteByte = ((!spawnlocation) == (!0x7));
    
        if (!EqualEqual_ByteByte)
            return;
    
        UpdateFrontlineIfNeeded(cardSpawned->cardID);
    
        return;
    
        Label_2820:
        ExecuteOnEnterPlayEvents(cardSpawned, 0x3);
    
        if (!giveBlitz)
            goto Label_2913;
    
        GiveBlitz(cardSpawned->cardID, spawnerID);
    
        Label_2913:
        cardSpawned->getHasAlpine(CallFunc_getHasAlpine_doesIt);
    
        if (!CallFunc_getHasAlpine_doesIt)
            goto Label_2627;
    
        GiveAlpineBonus(cardSpawned);
    
        goto Label_2627;
    
        Label_2996:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_1462;
    
        Label_3070:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SalvageMultipleUnits(const TArray<int>*& cardsToSalvage, int instigatorID, bool& qqq)
    {
        createdCardID = 0;
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card_3);
    
        salvaging side = CallFunc_GetCardFromID_card_3->side;
    
        GetHandLocationBySide = UCombatHelperFunctions::GetHandLocationBySide(salvaging side, this);
    
        salvaging hand location = GetHandLocationBySide;
    
        goto Label_185;
    
        Label_185:
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_231:
        Array_Length_2 = cardsToSalvage.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_2);
    
        if (!Less_IntInt_2)
            goto Label_687;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_2 = cardsToSalvage[Temp_int_Array_Index_Variable_2];
    
        tmpCardID = CallFunc_Array_Get_Item_2;
    
        CallFunc_Array_Get_Item_2 = cardsToSalvage[Temp_int_Array_Index_Variable_2];
    
        GetCardFromID(CallFunc_Array_Get_Item_2, CallFunc_GetCardFromID_card_2);
    
        _destroyedCard = CallFunc_GetCardFromID_card_2;
    
        IsLocationFull(salvaging hand location, CallFunc_IsLocationFull_isFull);
    
        if (!CallFunc_IsLocationFull_isFull)
            goto Label_1545;
    
        goto Label_613;
    
        Label_613:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_231;
    
        Label_687:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2934;
    
        CardFunctionsNotifier->NotifySalvageMultipleUnits(localCardIDs, instigatorID, _createdCardIDs);
    
        goto Label_1145;
    
        Label_794:
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_4 = 0;
    
        Label_840:
        Array_Length_3 = _createdCardIDs.Length;
    
        Less_IntInt_3 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_3);
    
        if (!Less_IntInt_3)
            goto Label_794;
    
        Temp_int_Array_Index_Variable_4 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_3 = _createdCardIDs[Temp_int_Array_Index_Variable_4];
    
        ExecuteOnSpawnedInHandEvents(salvaging side, CallFunc_Array_Get_Item_3);
    
        goto Label_1071;
    
        Label_1071:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_840;
    
        Label_1145:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1191:
        Array_Length_4 = _createdCardIDs.Length;
    
        Less_IntInt_4 = (Temp_int_Loop_Counter_Variable < Array_Length_4);
    
        if (!Less_IntInt_4)
            goto Label_1488;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        Temp_bool_Variable = true;
    
        Array_Add = _cardSeenArray.Add(Temp_bool_Variable);
    
        goto Label_1414;
    
        Label_1414:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1191;
    
        Label_1488:
        CardFunctionsNotifier->NotifyCardsSeen(_createdCardIDs, _cardSeenArray, false, false);
    
        return;
    
        Label_1545:
        Array_Add_1 = localCardIDs.Add(tmpCardID);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            return;
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card_1);
    
        MakeStruct_S_SalvagedCardInfo.isSalvaged_1_D83369C241D0F4E11CEDCB8250BC0D97 = true;
    
        MakeStruct_S_SalvagedCardInfo.salvageFaction_5_30136A02489F9A3E6C29FEB0A508ADD9 = CallFunc_GetCardFromID_card_1->faction;
    
        MakeStruct_S_SalvagedCardInfo.salvagedCardID_8_60B10C4245C90998186E6E9E7E180468 = tmpCardID;
    
        CreateCard(salvaging side, _destroyedCard->name, salvaging hand location, 0, -1, true, _destroyedCard->isGoldCard, "", true, false, 0, false, MakeStruct_S_SalvagedCardInfo, true, false, false, CallFunc_CreateCard_cardID);
    
        createdCardID = CallFunc_CreateCard_cardID;
    
        GetCardFromID(createdCardID, CallFunc_GetCardFromID_card);
    
        CardFunctionsNotifier->NotifyCreateNonVisualCard(CallFunc_GetCardFromID_card);
    
        FetchAllCardsWithEventTrigger(0x23, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        Temp_int_Loop_Counter_Variable_3 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_2103:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_3 < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_2459;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_3;
    
        GetCardFromID(createdCardID, CallFunc_GetCardFromID_card);
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_1->OnOtherCardCreatedAlterCard(CallFunc_GetCardFromID_card, 0x3);
    
        goto Label_2385;
    
        Label_2385:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_3 + 1;
    
        Temp_int_Loop_Counter_Variable_3 = Add_IntInt_3;
    
        goto Label_2103;
    
        Label_2459:
        Array_Add_2 = _createdCardIDs.Add(createdCardID);
    
        FetchAllCardsWithEventTrigger(0x38, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_4 = 0;
    
        Temp_int_Array_Index_Variable_3 = 0;
    
        Label_2598:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_4 < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable_3 = Temp_int_Loop_Counter_Variable_4;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_3];
    
        CallFunc_Array_Get_Item->OnOtherCardSalvaged(tmpCardID, createdCardID, instigatorID);
    
        goto Label_2860;
    
        Label_2860:
        Add_IntInt_4 = Temp_int_Loop_Counter_Variable_4 + 1;
    
        Temp_int_Loop_Counter_Variable_4 = Add_IntInt_4;
    
        goto Label_2598;
    
        Label_2934:
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ChangeOperationCost(class UBaseCardObject* card, int instigatorID, int amount, EChangeType changeType, bool isBuff, bool skipAction, bool skipAddToBattlelog)
    {
        localInstigatorID = 0;
    
        IsValid = card;
    
        if (!IsValid)
            goto Label_179;
    
        Greater_IntInt = (instigatorID > 0);
    
        if (!Greater_IntInt)
            goto Label_179;
    
        card->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_263;
    
        return;
    
        Label_179:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("invalid card for [Change Operation Cost]", this);
    
        return;
    
        Label_263:
        cardToChangeRef = card;
    
        cardToChange = cardToChangeRef->cardID;
    
        localInputAmount = amount;
    
        localInstigatorID = instigatorID;
    
        localChangeType = changeType;
    
        runResetEvents = false;
    
        goto Label_884;
    
        Label_434:
        if (!valueChanged)
            goto Label_879;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_434;
    
        if (!skipAction)
            goto Label_1676;
    
        Label_495:
        if (!cardToChangeRef->isSuppressed)
            goto Label_1762;
    
        Label_531:
        FetchAllCardsWithEventTrigger(0xA, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_602:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_1812;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt_4 = CallFunc_Array_Get_Item->cardID == cardToChange;
    
        if (!EqualEqual_IntInt_4)
            goto Label_2537;
    
        goto Label_2463;
    
        Label_879:
        return;
    
        Label_884:
        ChangeBuffsFromCards(cardToChangeRef, localInputAmount, localInstigatorID, 0x3, localChangeType, "", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        amountRemoved = CallFunc_ChangeBuffsFromCards_amountRemoved;
    
        goto Label_980;
    
        Label_980:
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1487;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1251;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2747;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2747;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2952;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2747;
    
        goto Label_3168;
    
        Label_1251:
        EqualEqual_IntInt_2 = localInputAmount == 0;
    
        if (!EqualEqual_IntInt_2)
            goto Label_1311;
    
        valueChanged = false;
    
        return;
    
        Label_1311:
        Add_IntInt_3 = cardToChangeRef->operationCost + localInputAmount;
    
        Clamp_1 = ((Add_IntInt_3 < 0) ? 0 : ((Add_IntInt_3 > 99) ? 99 : Add_IntInt_3));
    
        cardToChangeRef->operationCost = Clamp_1;
    
        valueChanged = true;
    
        return;
    
        Label_1487:
        EqualEqual_IntInt_1 = localInputAmount == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_1547;
    
        valueChanged = false;
    
        return;
    
        Label_1547:
        Add_IntInt_2 = cardToChangeRef->operationCostBuff + localInputAmount;
    
        cardToChangeRef->operationCostBuff = Add_IntInt_2;
    
        valueChanged = true;
    
        return;
    
        Label_1676:
        CardFunctionsNotifier->NotifyChangeOperationCost(cardToChange, instigatorID, localInputAmount, changeType, skipAddToBattlelog);
    
        goto Label_495;
    
        Label_1762:
        cardToChangeRef->OnAfterOperationCostChanged(instigatorID);
    
        goto Label_531;
    
        Label_1812:
        if (!runResetEvents)
            goto Label_2458;
    
        FetchAllCardsWithEventTrigger(0x9, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1897:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt_1)
            goto Label_2458;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        EqualEqual_IntInt_5 = CallFunc_Array_Get_Item_1->cardID == cardToChange;
    
        if (!EqualEqual_IntInt_5)
            goto Label_2174;
    
        goto Label_2384;
    
        Label_2174:
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        if (!CallFunc_Array_Get_Item_1->isSuppressed)
            goto Label_2270;
    
        return;
    
        Label_2270:
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_1->OnAfterOtherCardOperactionCostBuffsReset(cardToChange, instigatorID);
    
        return;
    
        Label_2384:
        Add_IntInt_4 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_4;
    
        goto Label_1897;
    
        Label_2458:
        return;
    
        Label_2463:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt_1;
    
        goto Label_602;
    
        Label_2537:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        if (!CallFunc_Array_Get_Item->isSuppressed)
            goto Label_2633;
    
        return;
    
        Label_2633:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnAfterOtherCardOperactionCostChanged(cardToChange, instigatorID);
    
        return;
    
        Label_2747:
        EqualEqual_IntInt_3 = cardToChangeRef->operationCost == localInputAmount;
    
        if (!EqualEqual_IntInt_3)
            goto Label_2833;
    
        valueChanged = false;
    
        return;
    
        Label_2833:
        Clamp = ((localInputAmount < 0) ? 0 : ((localInputAmount > 99) ? 99 : localInputAmount));
    
        cardToChangeRef->operationCost = Clamp;
    
        valueChanged = true;
    
        runResetEvents = true;
    
        return;
    
        Label_2952:
        EqualEqual_IntInt = amountRemoved == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_3012;
    
        valueChanged = false;
    
        return;
    
        Label_3012:
        localInputAmount = amountRemoved;
    
        Add_IntInt = cardToChangeRef->operationCostBuff + localInputAmount;
    
        cardToChangeRef->operationCostBuff = Add_IntInt;
    
        valueChanged = true;
    
        return;
    
        Label_3168:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RevealCard(int cardID, int instigatorID, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        cardRevealed = CallFunc_GetCardFromID_card;
    
        cardRevealed->isRevealed = true;
    
        cardRevealed->hasCovert = false;
    
        UpdateGuarded(cardRevealed->location);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1240;
    
        CardFunctionsNotifier->NotifyRevealCard(cardID, instigatorID);
    
        if (!cardRevealed->isSuppressed)
            goto Label_609;
    
        Label_290:
        FetchAllCardsWithEventTrigger(0x37, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_361:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_650;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardRevealed(cardRevealed);
    
        goto Label_1166;
    
        Label_609:
        cardRevealed->OnCardRevealed();
    
        goto Label_290;
    
        Label_650:
        cardRevealed->OnEnterPlay(0x4);
    
        FetchAllCardsWithEventTrigger(0x2B, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_759:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt_1)
            goto Label_1083;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_1->OnOtherCardEnterPlay(cardRevealed, 0x4);
    
        goto Label_1009;
    
        Label_1009:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_759;
    
        Label_1083:
        ExecuteOnCardLocationMoved(0, 0x0, cardRevealed->location, false, 0xC);
    
        qqq = 0;
    
        return;
    
        Label_1166:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_361;
    
        Label_1240:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void GetStartingSide(ESideEnum& side)
    {
        GameStateRef->GetStartingSide(CallFunc_GetStartingSide_StartingSide);
    
        side = CallFunc_GetStartingSide_StartingSide;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void GetTotalKreditsLostThisBattle(ESideEnum side, int& kreditsLost)
    {
        GameStateRef->getKreditSlotsLostBySide(side, CallFunc_getKreditSlotsLostBySide_KreditSlotsLost);
    
        kreditsLost = CallFunc_getKreditSlotsLostBySide_KreditSlotsLost;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void GetAllyNationForSide(ESideEnum side, EFactionEnum& allyNation)
    {
        Temp_byte_Variable = 0x0;
    
        GameStateRef->GetAllyFactionBySide(side, CallFunc_GetAllyFactionBySide_AllyFaction);
    
        GameStateRef->GetMainFactionBySide(side, CallFunc_GetMainFactionBySide_MainFaction);
    
        EqualEqual_ByteByte = ((!CallFunc_GetAllyFactionBySide_AllyFaction) == (!CallFunc_GetMainFactionBySide_MainFaction));
    
        Temp_bool_Variable = EqualEqual_ByteByte;
    
        allyNation = Temp_bool_Variable ? Temp_byte_Variable : CallFunc_GetAllyFactionBySide_AllyFaction;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void AddNumberToText(int cardID, FText*& numberText, EStatsTextColor color, int& qqq)
    {
        MakeStruct_FormatArgumentData.ArgumentName = "1";
    
        MakeStruct_FormatArgumentData.ArgumentValueType = 0x4;
    
        MakeStruct_FormatArgumentData.ArgumentValue = numberText;
    
        MakeStruct_FormatArgumentData.ArgumentValueInt = 0;
    
        MakeStruct_FormatArgumentData.ArgumentValueFloat = 0;
    
        MakeStruct_FormatArgumentData.ArgumentValueDouble = 0;
    
        MakeStruct_FormatArgumentData.ArgumentValueGender = 0x0;
    
        Temp_byte_Variable = color;
    
        MakeArray_Array = [ MakeStruct_FormatArgumentData ];
    
        MakeStruct_FormatArgumentData_1.ArgumentName = "1";
    
        MakeStruct_FormatArgumentData_1.ArgumentValueType = 0x4;
    
        MakeStruct_FormatArgumentData_1.ArgumentValue = numberText;
    
        MakeStruct_FormatArgumentData_1.ArgumentValueInt = 0;
    
        MakeStruct_FormatArgumentData_1.ArgumentValueFloat = 0;
    
        MakeStruct_FormatArgumentData_1.ArgumentValueDouble = 0;
    
        MakeStruct_FormatArgumentData_1.ArgumentValueGender = 0x0;
    
        Format = UKismetTextLibrary::Format("<red>{1}</>", MakeArray_Array);
    
        MakeArray_Array_1 = [ MakeStruct_FormatArgumentData_1 ];
    
        TextIsEmpty = UKismetTextLibrary::TextIsEmpty(numberText);
    
        Format_1 = UKismetTextLibrary::Format("<green>{1}</>", MakeArray_Array_1);
    
        Temp_bool_Variable = TextIsEmpty;
    
        MakeStruct_FormatArgumentData_2.ArgumentName = "2";
    
        MakeStruct_FormatArgumentData_2.ArgumentValueType = 0x4;
    
        MakeStruct_FormatArgumentData_2.ArgumentValue = switch (Temp_byte_Variable)
        {
            case 0x0:
            {
                return numberText;
                break;
            }
            case 0x1:
            {
                return Format_1;
                break;
            }
            case 0x2:
            {
                return Format;
                break;
            }
            default:
            {
                return Select_Default;
                break;
            }
        };
    
        MakeStruct_FormatArgumentData_2.ArgumentValueInt = 0;
    
        MakeStruct_FormatArgumentData_2.ArgumentValueFloat = 0;
    
        MakeStruct_FormatArgumentData_2.ArgumentValueDouble = 0;
    
        MakeStruct_FormatArgumentData_2.ArgumentValueGender = 0x0;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        UFunctionLibrary::GetStaticText(CallFunc_GetCardFromID_card->name, CallFunc_GetStaticText_text);
    
        MakeStruct_FormatArgumentData_3.ArgumentName = "1";
    
        MakeStruct_FormatArgumentData_3.ArgumentValueType = 0x4;
    
        MakeStruct_FormatArgumentData_3.ArgumentValue = CallFunc_GetStaticText_text;
    
        MakeStruct_FormatArgumentData_3.ArgumentValueInt = 0;
    
        MakeStruct_FormatArgumentData_3.ArgumentValueFloat = 0;
    
        MakeStruct_FormatArgumentData_3.ArgumentValueDouble = 0;
    
        MakeStruct_FormatArgumentData_3.ArgumentValueGender = 0x0;
    
        MakeArray_Array_2 = [ MakeStruct_FormatArgumentData_3, MakeStruct_FormatArgumentData_2 ];
    
        Format_2 = UKismetTextLibrary::Format("{1} ({2})", MakeArray_Array_2);
    
        CallFunc_GetCardFromID_card->text = Temp_bool_Variable ? CallFunc_GetStaticText_text : Format_2;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        Conv_TextToString = FString(numberText);
    
        CardFunctionsNotifier->NotifyAppendNumberToCardText(cardID, Conv_TextToString, cardID, color);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void AddIntelToCard(int cardID, int instigatorID, int amount, int& qqq)
    {
        Greater_IntInt = (cardID > 0);
    
        if (!Greater_IntInt)
            return;
    
        NotEqual_IntInt = (amount !== 0);
    
        if (!NotEqual_IntInt)
            return;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        cardToAdd = CallFunc_GetCardFromID_card;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        Add_IntInt = CallFunc_GetCardFromID_card->cipher + amount;
    
        Clamp = ((Add_IntInt < 0) ? 0 : ((Add_IntInt > 9) ? 9 : Add_IntInt));
    
        CallFunc_GetCardFromID_card->cipher = Clamp;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyAddIntelToCard(cardID, instigatorID, amount);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void TriggerDeployment(class UBaseCardObject* card, int instigatorID, int& qqq)
    {
        DeployEffectStopped = false;
    
        IsValid = card;
    
        if (!IsValid)
            goto Label_725;
    
        if (!card->hasDeployment)
            goto Label_1363;
    
        CardID = card->cardID;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        FetchAllCardsWithEventTrigger(0xE, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_255:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        BooleanAND = Not_PreBool && Less_IntInt;
    
        if (!BooleanAND)
            goto Label_833;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnBeforeOtherCardDeploymentTrigger(card, CallFunc_OnBeforeOtherCardDeploymentTrigger_cancelDeploymentEffect);
    
        DeployEffectStopped = CallFunc_OnBeforeOtherCardDeploymentTrigger_cancelDeploymentEffect;
    
        if (!CallFunc_OnBeforeOtherCardDeploymentTrigger_cancelDeploymentEffect)
            goto Label_1289;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CardFunctionsNotifier->NotifyForceCardEffectTrigger(CallFunc_Array_Get_Item, 0x9);
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        return;
    
        Label_725:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("[Trigger Destruction] on an invalid card.", this);
    
        qqq = 0;
    
        return;
    
        Label_833:
        if (!DeployEffectStopped)
            goto Label_956;
    
        NotifySideEffectTrigger(card->side, FGameplayTag("sideeffect.blockdeployment"), CallFunc_NotifySideEffectTrigger_qqq);
    
        qqq = 0;
    
        return;
    
        Label_956:
        ExecuteOnDeploymentTriggered(card, instigatorID, CallFunc_ExecuteOnDeploymentTriggered_triggerMultiple);
    
        Temp_int_Variable = 1;
    
        Label_1020:
        Add_IntInt_1 = 1 + CallFunc_ExecuteOnDeploymentTriggered_triggerMultiple;
    
        LessEqual_IntInt = (Temp_int_Variable <= Add_IntInt_1);
    
        if (!LessEqual_IntInt)
            goto Label_1261;
    
        card->OnPlayedFromHand(card->currentTarget);
    
        goto Label_1187;
    
        Label_1187:
        Add_IntInt_2 = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt_2;
    
        goto Label_1020;
    
        Label_1261:
        qqq = 0;
    
        return;
    
        Label_1289:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_255;
    
        Label_1363:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ResetUnitOperations(int cardID, int giverID, bool& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        CallFunc_GetCardFromID_card->IsUnit(CallFunc_IsUnit_isIt);
    
        BooleanAND = CallFunc_IsUnit_isIt && CallFunc_IsLocatedOnBoard_isIt;
    
        if (!BooleanAND)
            return;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->movementLeft = 1;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->getHasFury(CallFunc_getHasFury_doesIt);
    
        if (!CallFunc_getHasFury_doesIt)
            goto Label_503;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->attackLeft = 2;
    
        Label_407:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyResetUnitOperations(cardID, giverID);
    
        return;
    
        Label_503:
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->attackLeft = 1;
    
        goto Label_407;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SetCardSeen(int cardID_Seen, int instigatorID, int& qqq)
    {
        GetCardFromID(cardID_Seen, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->cardSeen = true;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        MakeArray_Array = [ true ];
    
        MakeArray_Array_1 = [ cardID_Seen ];
    
        CardFunctionsNotifier->NotifyCardsSeen(MakeArray_Array_1, MakeArray_Array, false, false);
    
        qqq = 0;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void Get_X_AndMoreAttackCardsOnBoard(ESideEnum side, TArray<int>& cardsIDs, int Attack, bool includeCovert)
    {
        LocalCardsIDs.Clear();
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_92:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_938;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        LocalCardToCheck = CallFunc_Array_Get_Item;
    
        LocalCardToCheck->IsUnit(CallFunc_IsUnit_isIt);
    
        LocalCardToCheck->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        LocalCardToCheck->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        Greater_IntInt = (CallFunc_getTotalDefense_totalDefense > 0);
    
        BooleanAND = Greater_IntInt && CallFunc_IsLocatedOnBoard_isIt;
    
        BooleanAND_1 = BooleanAND && CallFunc_IsUnit_isIt;
    
        EqualEqual_ByteByte = ((!LocalCardToCheck->side) == (!side));
    
        BooleanAND_2 = BooleanAND_1 && EqualEqual_ByteByte;
    
        if (!BooleanAND_2)
            goto Label_970;
    
        if (!includeCovert)
            goto Label_1044;
    
        Label_758:
        LocalCardToCheck->getTotalAttack(CallFunc_getTotalAttack_totalAttack);
    
        GreaterEqual_IntInt = (CallFunc_getTotalAttack_totalAttack >= Attack);
    
        if (!GreaterEqual_IntInt)
            goto Label_1100;
    
        Array_Add = LocalCardsIDs.Add(LocalCardToCheck->cardID);
    
        return;
    
        Label_938:
        cardsIDs = LocalCardsIDs;
    
        return;
    
        Label_970:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_92;
    
        Label_1044:
        LocalCardToCheck->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_758;
    
        return;
    
        Label_1100:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void MakeCardsFight(class UBaseCardObject* unitThisSide, class UBaseCardObject* unitOppositeSide, int instigatorID, int& qqq)
    {
        _final_damage_to_enemy_unit = 0;
    
        IsValid_1 = unitThisSide;
    
        if (!IsValid_1)
            goto Label_709;
    
        IsValid = unitOppositeSide;
    
        if (!IsValid)
            return;
    
        unitThisSide->getTotalAttack(CallFunc_getTotalAttack_totalAttack_1);
    
        _damage_to_enemy_unit = CallFunc_getTotalAttack_totalAttack_1;
    
        unitOppositeSide->getTotalAttack(CallFunc_getTotalAttack_totalAttack);
    
        _damage_to_my_unit = CallFunc_getTotalAttack_totalAttack;
    
        unitOppositeSide->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt_1);
    
        if (!CallFunc_IsLocatedOnBoard_isIt_1)
            goto Label_437;
    
        ExecuteOnDealDamageAddDamage(unitThisSide, unitOppositeSide, _damage_to_enemy_unit, false, true, false, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage_1);
    
        ExecuteOnDealDamageAddDamageAfterCalc(unitOppositeSide, unitThisSide, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage_1, false, false, false, CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage_1);
    
        _final_damage_to_enemy_unit = CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage_1;
    
        goto Label_622;
    
        Label_437:
        unitThisSide->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            return;
    
        ExecuteOnDealDamageAddDamage(unitOppositeSide, unitThisSide, _damage_to_my_unit, false, true, false, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage);
    
        ExecuteOnDealDamageAddDamageAfterCalc(unitThisSide, unitOppositeSide, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage, false, false, false, CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage);
    
        _final_damage_to_my_unit = CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage;
    
        return;
    
        Label_622:
        ApplyDamageToCard(unitOppositeSide, unitThisSide, _final_damage_to_enemy_unit, false, false);
    
        ApplyDamageToCard(unitThisSide, unitOppositeSide, _final_damage_to_my_unit, false, true);
    
        return;
    
        Label_709:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ChangeFrontlineLimiter(int limiter, bool remove, int& qqq)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyUpdateFrontlineLimiter(limiter, limiter, remove);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void getFrontlineLimit(bool& isFrontlineLimited)
    {
        GameStateRef->IsFrontlineLimited(CallFunc_IsFrontlineLimited_FrontlineLimited);
    
        isFrontlineLimited = CallFunc_IsFrontlineLimited_FrontlineLimited;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveShock(int cardID, int instigatorID, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_544;
    
        CanCardBeBuffed(_card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            return;
    
        Conv_IntToBool = (instigatorID != 0);
    
        if (!Conv_IntToBool)
            goto Label_622;
    
        Temp_string_Variable = "shock";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_875;
    
        Temp_string_Variable = "shock";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        _cardsGivingShock = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingShock[instigatorID];
    
        if (!Array_Contains)
            goto Label_875;
    
        return;
    
        Label_544:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("GiveShock has to have valid target", this);
    
        return;
    
        Label_622:
        if (!_card->hasShock)
            goto Label_663;
    
        return;
    
        Label_663:
        _card->hasShock = true;
    
        Label_696:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        _card->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        if (!CallFunc_IsLocatedInDeck_isIt)
            goto Label_816;
    
        Label_788:
        ExecuteOnOtherCardsAbilitiesChanged(_card);
    
        return;
    
        Label_816:
        CardFunctionsNotifier->NotifyGiveShock(cardID, instigatorID);
    
        goto Label_788;
    
        Label_875:
        Array_Add = _cardsGivingShock.Add(instigatorID);
    
        ChangeBuffsFromCards(_card, 1, instigatorID, 0x6, 0x8, "shock", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingShock;
    
        Temp_string_Variable_1 = "shock";
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_696;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveShock(int cardID, int instigatorID, bool removeAllGivers, bool skipAction, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_821;
    
        LessEqual_IntInt = (instigatorID <= 0);
    
        BooleanOR = (LessEqual_IntInt || removeAllGivers);
    
        if (!BooleanOR)
            goto Label_895;
    
        _card->getHasShock(CallFunc_getHasShock_doesIt);
    
        if (!CallFunc_getHasShock_doesIt)
            goto Label_1899;
    
        Temp_string_Variable_3 = "shock";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_3, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1680;
    
        Temp_string_Variable_3 = "shock";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_3, CallFunc_Map_Find_Value);
    
        _cardsGivingShock = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_565:
        Array_Length = _cardsGivingShock.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = _cardsGivingShock[Temp_int_Array_Index_Variable];
    
        ChangeBuffsFromCards(_card, -1, CallFunc_Array_Get_Item, 0x6, 0x8, "shock", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        goto Label_1825;
    
        Label_821:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("RemoveShock must have a valid card", this);
    
        return;
    
        Label_895:
        Conv_IntToBool = (instigatorID != 0);
    
        if (!Conv_IntToBool)
            return;
    
        Temp_string_Variable_1 = "shock";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, CallFunc_Map_Find_Value_1);
    
        Array_Contains = CallFunc_Map_Find_Value_1.cardsGivingAbility[instigatorID];
    
        if (!Array_Contains)
            return;
    
        Temp_string_Variable_1 = "shock";
    
        Map_Find_1 = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, CallFunc_Map_Find_Value_1);
    
        _cardsGivingShock = CallFunc_Map_Find_Value_1.cardsGivingAbility;
    
        Array_RemoveItem = _cardsGivingShock.Remove(instigatorID);
    
        if (!Array_RemoveItem)
            return;
    
        ChangeBuffsFromCards(_card, -1, instigatorID, 0x6, 0x8, "shock", CallFunc_ChangeBuffsFromCards_amountRemoved_1);
    
        Temp_string_Variable = "shock";
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingShock;
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable, MakeStruct_CardsGivingAbility);
    
        Label_1550:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        if (!skipAction)
            goto Label_1621;
    
        Label_1597:
        ExecuteOnOtherCardsAbilitiesChanged(_card);
    
        return;
    
        Label_1621:
        CardFunctionsNotifier->NotifyRemoveShock(cardID, instigatorID);
    
        goto Label_1597;
    
        Label_1680:
        _card->hasShock = false;
    
        Temp_string_Variable_2 = "shock";
    
        Map_Remove = _card->receivedAbilitiesFromCards.Remove(Temp_string_Variable_2);
    
        goto Label_1550;
    
        Label_1825:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_565;
    
        Label_1899:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ChangeKreditCost(class UBaseCardObject* card, int instigatorID, int amount, EChangeType changeType, bool skipCovertCheck, bool& qqq)
    {
        amountRemoved = 0;
    
        IsValid = card;
    
        if (!IsValid)
            goto Label_293;
    
        Greater_IntInt = (instigatorID > 0);
    
        if (!Greater_IntInt)
            goto Label_293;
    
        if (!skipCovertCheck)
            goto Label_385;
    
        Label_133:
        cardToChangeRef = card;
    
        cardToChange = cardToChangeRef->cardID;
    
        localInputAmount = amount;
    
        localInstigatorID = instigatorID;
    
        localChangeType = changeType;
    
        goto Label_436;
    
        Label_293:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("invalid card for [Change Kredit Cost]", this);
    
        Label_369:
        qqq = false;
    
        return;
    
        Label_385:
        CanCardBeBuffed(card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_369;
    
        goto Label_133;
    
        Label_436:
        ChangeBuffsFromCards(cardToChangeRef, localInputAmount, localInstigatorID, 0x2, localChangeType, "", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        amountRemoved = CallFunc_ChangeBuffsFromCards_amountRemoved;
    
        goto Label_532;
    
        Label_532:
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1346;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1031;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_758;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_758;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2461;
    
        goto Label_1614;
    
        Label_758:
        cardToChangeRef->getAndDecryptKredit(CallFunc_getAndDecryptKredit_decryptedKredit);
    
        EqualEqual_IntInt_3 = CallFunc_getAndDecryptKredit_decryptedKredit == localInputAmount;
    
        if (!EqualEqual_IntInt_3)
            goto Label_863;
    
        valueChanged = false;
    
        goto Label_2756;
    
        Label_863:
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_2, CallFunc_provideKeysAndFrameCount_key2_2, CallFunc_provideKeysAndFrameCount_frameCount_2);
    
        Clamp = ((localInputAmount < 0) ? 0 : ((localInputAmount > 99) ? 99 : localInputAmount));
    
        cardToChangeRef->setAndEncryptKredit(Clamp, CallFunc_provideKeysAndFrameCount_key1_2, CallFunc_provideKeysAndFrameCount_key2_2, CallFunc_provideKeysAndFrameCount_frameCount_2);
    
        valueChanged = true;
    
        return;
    
        Label_1031:
        EqualEqual_IntInt_2 = localInputAmount == 0;
    
        if (!EqualEqual_IntInt_2)
            goto Label_1091;
    
        valueChanged = false;
    
        return;
    
        Label_1091:
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        cardToChangeRef->getAndDecryptKredit(CallFunc_getAndDecryptKredit_decryptedKredit_1);
    
        Add_IntInt_2 = CallFunc_getAndDecryptKredit_decryptedKredit_1 + localInputAmount;
    
        Clamp_1 = ((Add_IntInt_2 < 0) ? 0 : ((Add_IntInt_2 > 99) ? 99 : Add_IntInt_2));
    
        cardToChangeRef->setAndEncryptKredit(Clamp_1, CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        valueChanged = true;
    
        return;
    
        Label_1346:
        EqualEqual_IntInt_1 = localInputAmount == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_1406;
    
        valueChanged = false;
    
        return;
    
        Label_1406:
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        cardToChangeRef->getAndDecryptKreditBuff(CallFunc_getAndDecryptKreditBuff_decryptedKreditBuff_1);
    
        Add_IntInt_1 = CallFunc_getAndDecryptKreditBuff_decryptedKreditBuff_1 + localInputAmount;
    
        cardToChangeRef->setAndEncryptKreditBuff(Add_IntInt_1, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        valueChanged = true;
    
        return;
    
        Label_1614:
        if (!valueChanged)
            return;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        cardToChangeRef->getTotalKreditCost(CallFunc_getTotalKreditCost_totalKreditCost);
    
        CardFunctionsNotifier->NotifySetKreditCost(cardToChange, CallFunc_getTotalKreditCost_totalKreditCost, localInstigatorID, localInputAmount, changeType, true);
    
        EqualEqual_IntInt_4 = cardToChange == localInstigatorID;
    
        if (!EqualEqual_IntInt_4)
            goto Label_2370;
    
        Label_1832:
        FetchAllCardsWithEventTrigger(0x2D, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1903:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_2354;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        NotEqual_IntInt = (CallFunc_Array_Get_Item->cardID !== cardToChange);
    
        if (!NotEqual_IntInt)
            goto Label_2280;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardKreditCostChanged(cardToChange);
    
        return;
    
        Label_2280:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt_3;
    
        goto Label_1903;
    
        Label_2354:
        qqq = false;
    
        return;
    
        Label_2370:
        if (!cardToChangeRef->isSuppressed)
            goto Label_2411;
    
        goto Label_1832;
    
        Label_2411:
        cardToChangeRef->OnAfterKreditCostChanged(localInstigatorID);
    
        goto Label_1832;
    
        Label_2461:
        EqualEqual_IntInt = amountRemoved == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_2521;
    
        valueChanged = false;
    
        return;
    
        Label_2521:
        localInputAmount = amountRemoved;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_3, CallFunc_provideKeysAndFrameCount_key2_3, CallFunc_provideKeysAndFrameCount_frameCount_3);
    
        cardToChangeRef->getAndDecryptKreditBuff(CallFunc_getAndDecryptKreditBuff_decryptedKreditBuff);
    
        Add_IntInt = CallFunc_getAndDecryptKreditBuff_decryptedKreditBuff + localInputAmount;
    
        cardToChangeRef->setAndEncryptKreditBuff(Add_IntInt, CallFunc_provideKeysAndFrameCount_key1_3, CallFunc_provideKeysAndFrameCount_key2_3, CallFunc_provideKeysAndFrameCount_frameCount_3);
    
        valueChanged = true;
    
        return;
    
        Label_2756:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ChangeHeavyArmor(class UBaseCardObject* card, int instigatorID, int amount, EChangeType changeType, bool skipAction, bool& qqq)
    {
        IsValid = card;
    
        if (!IsValid)
            goto Label_167;
    
        Greater_IntInt = (instigatorID > 0);
    
        if (!Greater_IntInt)
            goto Label_167;
    
        card->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_248;
    
        Label_151:
        qqq = false;
    
        return;
    
        Label_167:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("invalid card for [Change Heavy Armor]", this);
    
        goto Label_151;
    
        Label_248:
        cardToChangeRef = card;
    
        cardToChange = cardToChangeRef->cardID;
    
        localInputAmount = amount;
    
        localInstigatorID = instigatorID;
    
        localChangeType = changeType;
    
        goto Label_641;
    
        Label_408:
        if (!valueChanged)
            goto Label_408;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1843;
    
        cardToChangeRef->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        BooleanOR = (skipAction || CallFunc_IsLocatedInDeck_isIt);
    
        if (!BooleanOR)
            goto Label_545;
    
        return;
    
        Label_545:
        CardFunctionsNotifier->NotifyAddHeavyArmor(cardToChange, localInputAmount, localInstigatorID, localChangeType);
    
        ExecuteOnOtherCardsAbilitiesChanged(cardToChangeRef);
    
        return;
    
        Label_641:
        ChangeBuffsFromCards(cardToChangeRef, localInputAmount, localInstigatorID, 0x4, localChangeType, "", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        amountRemoved = CallFunc_ChangeBuffsFromCards_amountRemoved;
    
        goto Label_737;
    
        Label_737:
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1244;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1008;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1433;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1433;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1627;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1433;
    
        return;
    
        Label_1008:
        EqualEqual_IntInt_2 = localInputAmount == 0;
    
        if (!EqualEqual_IntInt_2)
            goto Label_1068;
    
        valueChanged = false;
    
        return;
    
        Label_1068:
        Add_IntInt_2 = cardToChangeRef->heavyArmor + localInputAmount;
    
        Clamp_1 = ((Add_IntInt_2 < 0) ? 0 : ((Add_IntInt_2 > 3) ? 3 : Add_IntInt_2));
    
        cardToChangeRef->heavyArmor = Clamp_1;
    
        valueChanged = true;
    
        return;
    
        Label_1244:
        EqualEqual_IntInt_1 = localInputAmount == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_1304;
    
        valueChanged = false;
    
        return;
    
        Label_1304:
        Add_IntInt_1 = cardToChangeRef->heavyArmorBuff + localInputAmount;
    
        cardToChangeRef->heavyArmorBuff = Add_IntInt_1;
    
        valueChanged = true;
    
        return;
    
        Label_1433:
        EqualEqual_IntInt_3 = cardToChangeRef->heavyArmor == localInputAmount;
    
        if (!EqualEqual_IntInt_3)
            goto Label_1519;
    
        valueChanged = false;
    
        return;
    
        Label_1519:
        Clamp = ((localInputAmount < 0) ? 0 : ((localInputAmount > 3) ? 3 : localInputAmount));
    
        cardToChangeRef->heavyArmor = Clamp;
    
        valueChanged = true;
    
        return;
    
        Label_1627:
        EqualEqual_IntInt = amountRemoved == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_1687;
    
        valueChanged = false;
    
        return;
    
        Label_1687:
        localInputAmount = amountRemoved;
    
        Add_IntInt = cardToChangeRef->heavyArmorBuff + localInputAmount;
    
        cardToChangeRef->heavyArmorBuff = Add_IntInt;
    
        valueChanged = true;
    
        return;
    
        Label_1843:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ChangeBuffsFromCards(class UBaseCardObject* cardToChange, int amount, int instigatorID, ECardBuffTypes buffType, EChangeType changeType, FString customDetail, int& amountRemoved)
    {
        MakeArray_Array = [ 0x1, 0x2 ];
    
        changeTypesToRemove = MakeArray_Array;
    
        MakeArray_Array_1 = [ "" ];
    
        buffTypesToRemove = MakeArray_Array_1;
    
        Greater_IntInt = (instigatorID > 0);
    
        if (!Greater_IntInt)
            goto Label_186;
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card);
    
        tempInstigatorCard = CallFunc_GetCardFromID_card;
    
        Label_186:
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_592;
    
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_592;
    
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_668;
    
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_668;
    
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2097;
    
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_668;
    
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2307;
    
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2307;
    
        SwitchEnum_CmpSuccess = ((!changeType) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2307;
    
        goto Label_6264;
    
        Label_592:
        EqualEqual_IntInt = amount == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_668;
    
        amountRemoved = 0;
    
        return;
    
        Label_668:
        GetEnumeratorUserFriendlyName_5 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.EChangeType"), changeType);
    
        GetEnumeratorUserFriendlyName_6 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.ECardBuffTypes"), buffType);
    
        Concat_StrStr_4 = GetEnumeratorUserFriendlyName_6 += "_";
    
        Concat_StrStr_5 = Concat_StrStr_4 += GetEnumeratorUserFriendlyName_5;
    
        localBuffTypeString = Concat_StrStr_5;
    
        Label_873:
        Map_Find_2 = Map_Find(cardToChange->buffsFromCards, instigatorID, CallFunc_Map_Find_Value_2);
    
        if (!Map_Find_2)
            goto Label_1843;
    
        Map_Find_2 = Map_Find(cardToChange->buffsFromCards, instigatorID, CallFunc_Map_Find_Value_2);
    
        localCardBuffData = CallFunc_Map_Find_Value_2;
    
        Label_1101:
        skipUpdateWithLocal = false;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3025;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3025;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3529;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3529;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_5862;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3529;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_6195;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_5862;
    
        SwitchEnum_CmpSuccess_1 = ((!changeType) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3025;
    
        goto Label_1528;
    
        Label_1528:
        if (!skipUpdateWithLocal)
            goto Label_1543;
    
        goto Label_2471;
    
        Label_1543:
        CallFunc_Map_Keys_Keys_2 = [];
    
        Map_Keys(localCardBuffData.BuffMap, CallFunc_Map_Keys_Keys_2);
    
        Array_IsEmpty_1 = Array_IsEmpty(CallFunc_Map_Keys_Keys_2);
    
        if (!Array_IsEmpty_1)
            goto Label_1761;
    
        Map_Remove_3 = cardToChange->buffsFromCards.Remove(instigatorID);
    
        goto Label_2065;
    
        Label_1761:
        Map_Add(cardToChange->buffsFromCards, instigatorID, localCardBuffData);
    
        return;
    
        Label_1843:
        Greater_IntInt_1 = (instigatorID > 0);
    
        if (!Greater_IntInt_1)
            goto Label_2040;
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card_1);
    
        cardName = CallFunc_GetCardFromID_card_1->title;
    
        Label_1972:
        MakeStruct_CardBuffData.CardName = cardName;
    
        localCardBuffData = MakeStruct_CardBuffData;
    
        goto Label_1101;
    
        Label_2040:
        cardName = nullptr;
    
        goto Label_1972;
    
        Label_2065:
        amountRemoved = localAmountRemoved;
    
        return;
    
        Label_2097:
        GetEnumeratorUserFriendlyName_2 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.EChangeType"), tempBuffGive);
    
        GetEnumeratorUserFriendlyName_3 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.ECardBuffTypes"), buffType);
    
        Concat_StrStr = GetEnumeratorUserFriendlyName_3 += "_";
    
        Concat_StrStr_1 = Concat_StrStr += GetEnumeratorUserFriendlyName_2;
    
        localBuffTypeString = Concat_StrStr_1;
    
        goto Label_873;
    
        Label_2307:
        GetEnumeratorUserFriendlyName_4 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.ECardBuffTypes"), buffType);
    
        Concat_StrStr_2 = GetEnumeratorUserFriendlyName_4 += "_";
    
        Concat_StrStr_3 = Concat_StrStr_2 += customDetail;
    
        localBuffTypeString = Concat_StrStr_3;
    
        goto Label_873;
    
        Label_2471:
        IsValid = tempInstigatorCard;
    
        if (!IsValid)
            return;
    
        cardToChange->isBuffedByCard(instigatorID, CallFunc_isBuffedByCard_isBuffed);
    
        if (!CallFunc_isBuffedByCard_isBuffed)
            goto Label_2806;
    
        Array_Contains_1 = tempInstigatorCard->cardsBuffedByThisCard[cardToChange->cardID];
    
        if (!Array_Contains_1)
            goto Label_2693;
    
        return;
    
        Label_2693:
        Array_Add_1 = tempInstigatorCard->cardsBuffedByThisCard.Add(cardToChange->cardID);
    
        return;
    
        Label_2806:
        Array_Contains = tempInstigatorCard->cardsBuffedByThisCard[cardToChange->cardID];
    
        if (!Array_Contains)
            return;
    
        Array_RemoveItem = tempInstigatorCard->cardsBuffedByThisCard.Remove(cardToChange->cardID);
    
        return;
    
        Label_3025:
        Map_Find_3 = Map_Find(localCardBuffData.BuffMap, localBuffTypeString, CallFunc_Map_Find_Value_3);
    
        if (!Map_Find_3)
            goto Label_3501;
    
        Map_Find_3 = Map_Find(localCardBuffData.BuffMap, localBuffTypeString, CallFunc_Map_Find_Value_3);
    
        oldAmount = CallFunc_Map_Find_Value_3;
    
        Label_3222:
        Add_IntInt_4 = oldAmount + amount;
    
        EqualEqual_IntInt_1 = Add_IntInt_4 == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_3386;
    
        Map_Remove_4 = localCardBuffData.BuffMap.Remove(localBuffTypeString);
    
        return;
    
        Label_3386:
        Add_IntInt_3 = oldAmount + amount;
    
        Map_Add(localCardBuffData.BuffMap, localBuffTypeString, Add_IntInt_3);
    
        return;
    
        Label_3501:
        oldAmount = 0;
    
        goto Label_3222;
    
        Label_3529:
        skipUpdateWithLocal = true;
    
        buffTypesToRemove.Clear();
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_3632:
        Array_Length_2 = changeTypesToRemove.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_2);
    
        if (!Less_IntInt_2)
            goto Label_4265;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_2 = changeTypesToRemove[Temp_int_Array_Index_Variable_2];
    
        GetEnumeratorUserFriendlyName_7 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.EChangeType"), CallFunc_Array_Get_Item_2);
    
        GetEnumeratorUserFriendlyName_8 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.ECardBuffTypes"), buffType);
    
        Concat_StrStr_6 = GetEnumeratorUserFriendlyName_8 += "_";
    
        Concat_StrStr_7 = Concat_StrStr_6 += GetEnumeratorUserFriendlyName_7;
    
        Array_Add_2 = buffTypesToRemove.Add(Concat_StrStr_7);
    
        GetEnumeratorUserFriendlyName = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.EChangeType"), changeType);
    
        Array_Add = buffTypesToRemove.Add(GetEnumeratorUserFriendlyName);
    
        goto Label_4191;
    
        Label_4191:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_3632;
    
        Label_4265:
        CallFunc_Map_Keys_Keys_1 = [];
    
        Map_Keys(cardToChange->buffsFromCards, CallFunc_Map_Keys_Keys_1);
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_4394:
        Array_Length = CallFunc_Map_Keys_Keys_1.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_2 < Array_Length);
    
        if (!Less_IntInt)
            goto Label_5507;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item = CallFunc_Map_Keys_Keys_1[Temp_int_Array_Index_Variable_1];
    
        localInstigatorInLoop = CallFunc_Array_Get_Item;
    
        Map_Find = Map_Find(cardToChange->buffsFromCards, localInstigatorInLoop, CallFunc_Map_Find_Value);
    
        localCardBuffDataInLoop = CallFunc_Map_Find_Value;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_4787:
        Array_Length_1 = buffTypesToRemove.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_5133;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = buffTypesToRemove[Temp_int_Array_Index_Variable];
    
        Map_Remove_2 = localCardBuffDataInLoop.BuffMap.Remove(CallFunc_Array_Get_Item_1);
    
        goto Label_5059;
    
        Label_5059:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_4787;
    
        Label_5133:
        CallFunc_Map_Keys_Keys = [];
    
        Map_Keys(localCardBuffDataInLoop.BuffMap, CallFunc_Map_Keys_Keys);
    
        Array_IsEmpty = Array_IsEmpty(CallFunc_Map_Keys_Keys);
    
        if (!Array_IsEmpty)
            goto Label_5351;
    
        Map_Remove = cardToChange->buffsFromCards.Remove(localInstigatorInLoop);
    
        goto Label_5433;
    
        Label_5351:
        Map_Add(cardToChange->buffsFromCards, localInstigatorInLoop, localCardBuffDataInLoop);
    
        return;
    
        Label_5433:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_4394;
    
        Label_5507:
        EqualEqual_ByteByte_1 = ((!changeType) == (!0x2));
    
        if (!EqualEqual_ByteByte_1)
            goto Label_5702;
    
        Map_Add(localCardBuffData.BuffMap, localBuffTypeString, amount);
    
        Label_5620:
        Map_Add(cardToChange->buffsFromCards, instigatorID, localCardBuffData);
    
        return;
    
        Label_5702:
        EqualEqual_ByteByte = ((!changeType) == (!0x3));
    
        if (!EqualEqual_ByteByte)
            return;
    
        GetEnumeratorUserFriendlyName_1 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UEnum>(nullptr, "/Script/kards.EChangeType"), changeType);
    
        Map_Add(localCardBuffData.BuffMap, GetEnumeratorUserFriendlyName_1, Temp_int_Variable);
    
        goto Label_5620;
    
        Label_5862:
        Map_Find_1 = Map_Find(localCardBuffData.BuffMap, localBuffTypeString, CallFunc_Map_Find_Value_1);
    
        if (!Map_Find_1)
            goto Label_6171;
    
        Map_Find_1 = Map_Find(localCardBuffData.BuffMap, localBuffTypeString, CallFunc_Map_Find_Value_1);
    
        Multiply_IntInt = (CallFunc_Map_Find_Value_1 * -1);
    
        localAmountRemoved = Multiply_IntInt;
    
        Map_Remove_1 = localCardBuffData.BuffMap.Remove(localBuffTypeString);
    
        return;
    
        Label_6171:
        localAmountRemoved = 0;
    
        return;
    
        Label_6195:
        Map_Add(localCardBuffData.BuffMap, localBuffTypeString, Temp_int_Variable_1);
    
        return;
    
        Label_6264:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ChangeAttack(class UBaseCardObject* card, int instigatorID, int amount, EChangeType changeType, bool skipAction, bool& qqq)
    {
        previousAttack = 0;
    
        IsValid = card;
    
        if (!IsValid)
            goto Label_393;
    
        CanCardBeBuffed(card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_472;
    
        Greater_IntInt = (instigatorID > 0);
    
        if (!Greater_IntInt)
            goto Label_393;
    
        cardToChangeRef = card;
    
        cardToChange = cardToChangeRef->cardID;
    
        localInputAmount = amount;
    
        localInstigatorID = instigatorID;
    
        localChangeType = changeType;
    
        cardToChangeRef->getTotalAttack(CallFunc_getTotalAttack_totalAttack_1);
    
        previousAttack = CallFunc_getTotalAttack_totalAttack_1;
    
        goto Label_488;
    
        Label_393:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("error in [Change Attack]", this);
    
        qqq = false;
    
        return;
    
        Label_472:
        qqq = false;
    
        return;
    
        Label_488:
        ChangeBuffsFromCards(cardToChangeRef, localInputAmount, localInstigatorID, 0x0, localChangeType, "", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        amountRemoved = CallFunc_ChangeBuffsFromCards_amountRemoved;
    
        goto Label_584;
    
        Label_584:
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1722;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1224;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_855;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_855;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2415;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_855;
    
        goto Label_1990;
    
        Label_855:
        cardToChangeRef->getAndDecryptAttack(CallFunc_getAndDecryptAttack_decryptedAttack);
    
        EqualEqual_IntInt_3 = CallFunc_getAndDecryptAttack_decryptedAttack == localInputAmount;
    
        if (!EqualEqual_IntInt_3)
            goto Label_960;
    
        valueChanged = false;
    
        goto Label_2710;
    
        Label_960:
        Clamp = ((localInputAmount < 0) ? 0 : ((localInputAmount > 99) ? 99 : localInputAmount));
    
        cardToChangeRef->maxAttack = Clamp;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_2, CallFunc_provideKeysAndFrameCount_key2_2, CallFunc_provideKeysAndFrameCount_frameCount_2);
    
        Clamp = ((localInputAmount < 0) ? 0 : ((localInputAmount > 99) ? 99 : localInputAmount));
    
        cardToChangeRef->setAndEncryptAttack(Clamp, CallFunc_provideKeysAndFrameCount_key1_2, CallFunc_provideKeysAndFrameCount_key2_2, CallFunc_provideKeysAndFrameCount_frameCount_2);
    
        valueChanged = true;
    
        return;
    
        Label_1224:
        EqualEqual_IntInt = localInputAmount == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_1284;
    
        valueChanged = false;
    
        return;
    
        Label_1284:
        cardToChangeRef->getAndDecryptAttack(CallFunc_getAndDecryptAttack_decryptedAttack_1);
    
        Add_IntInt_2 = CallFunc_getAndDecryptAttack_decryptedAttack_1 + localInputAmount;
    
        Clamp_1 = ((Add_IntInt_2 < 0) ? 0 : ((Add_IntInt_2 > 99) ? 99 : Add_IntInt_2));
    
        cardToChangeRef->maxAttack = Clamp_1;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_3, CallFunc_provideKeysAndFrameCount_key2_3, CallFunc_provideKeysAndFrameCount_frameCount_3);
    
        cardToChangeRef->getAndDecryptAttack(CallFunc_getAndDecryptAttack_decryptedAttack_1);
    
        Add_IntInt_2 = CallFunc_getAndDecryptAttack_decryptedAttack_1 + localInputAmount;
    
        Clamp_1 = ((Add_IntInt_2 < 0) ? 0 : ((Add_IntInt_2 > 99) ? 99 : Add_IntInt_2));
    
        cardToChangeRef->setAndEncryptAttack(Clamp_1, CallFunc_provideKeysAndFrameCount_key1_3, CallFunc_provideKeysAndFrameCount_key2_3, CallFunc_provideKeysAndFrameCount_frameCount_3);
    
        valueChanged = true;
    
        return;
    
        Label_1722:
        EqualEqual_IntInt_1 = localInputAmount == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_1782;
    
        valueChanged = false;
    
        return;
    
        Label_1782:
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        cardToChangeRef->getAndDecryptAttackBuff(CallFunc_getAndDecryptAttackBuff_decryptedAttackBuff_1);
    
        Add_IntInt_1 = CallFunc_getAndDecryptAttackBuff_decryptedAttackBuff_1 + localInputAmount;
    
        cardToChangeRef->setAndEncryptAttackBuff(Add_IntInt_1, CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        valueChanged = true;
    
        return;
    
        Label_1990:
        if (!valueChanged)
            return;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        cardToChangeRef->getTotalAttack(CallFunc_getTotalAttack_totalAttack);
    
        Subtract_IntInt = CallFunc_getTotalAttack_totalAttack - previousAttack;
    
        localInputAmount = Subtract_IntInt;
    
        cardToChangeRef->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        BooleanOR = (skipAction || CallFunc_IsLocatedInDeck_isIt);
    
        if (!BooleanOR)
            goto Label_2282;
    
        Label_2240:
        ExecuteAfterChangeAttackEvents(cardToChangeRef, localInputAmount, instigatorID);
    
        return;
    
        Label_2282:
        cardToChangeRef->getTotalAttack(CallFunc_getTotalAttack_totalAttack_2);
    
        CardFunctionsNotifier->NotifyGainAttack(cardToChange, localInputAmount, CallFunc_getTotalAttack_totalAttack_2, 0, localInstigatorID, false, localChangeType);
    
        goto Label_2240;
    
        Label_2415:
        EqualEqual_IntInt_2 = amountRemoved == 0;
    
        if (!EqualEqual_IntInt_2)
            goto Label_2475;
    
        valueChanged = false;
    
        return;
    
        Label_2475:
        localInputAmount = amountRemoved;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        cardToChangeRef->getAndDecryptAttackBuff(CallFunc_getAndDecryptAttackBuff_decryptedAttackBuff);
    
        Add_IntInt = CallFunc_getAndDecryptAttackBuff_decryptedAttackBuff + amountRemoved;
    
        cardToChangeRef->setAndEncryptAttackBuff(Add_IntInt, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        valueChanged = true;
    
        return;
    
        Label_2710:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ChangeDefense(class UBaseCardObject* card, int instigatorID, int amount, EChangeType changeType, bool skipAction, bool& qqq)
    {
        IsValid = card;
    
        if (!IsValid)
            goto Label_386;
    
        CanCardBeBuffed(card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_466;
    
        Greater_IntInt = (instigatorID > 0);
    
        if (!Greater_IntInt)
            goto Label_386;
    
        cardToChangeRef = card;
    
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        Greater_IntInt_1 = (CallFunc_getTotalDefense_totalDefense > 0);
    
        if (!Greater_IntInt_1)
            goto Label_3831;
    
        cardToChange = cardToChangeRef->cardID;
    
        localInputAmount = amount;
    
        localInstigatorID = instigatorID;
    
        localChangeType = changeType;
    
        goto Label_482;
    
        Label_386:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("error in [Change Defense]", this);
    
        qqq = false;
    
        return;
    
        Label_466:
        qqq = false;
    
        return;
    
        Label_482:
        ChangeBuffsFromCards(cardToChangeRef, localInputAmount, localInstigatorID, 0x1, localChangeType, "", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        amountRemoved = CallFunc_ChangeBuffsFromCards_amountRemoved;
    
        goto Label_578;
    
        Label_578:
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_3734;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1995;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_984;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_984;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_3734;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_984;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_3734;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_3734;
    
        SwitchEnum_CmpSuccess = ((!localChangeType) !== (!0x9));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_3734;
    
        goto Label_5740;
    
        Label_984:
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_2, CallFunc_provideKeysAndFrameCount_key2_2, CallFunc_provideKeysAndFrameCount_frameCount_2);
    
        Clamp = ((localInputAmount < 0) ? 0 : ((localInputAmount > 99) ? 99 : localInputAmount));
    
        cardToChangeRef->setAndEncryptDefense(Clamp, CallFunc_provideKeysAndFrameCount_key1_2, CallFunc_provideKeysAndFrameCount_key2_2, CallFunc_provideKeysAndFrameCount_frameCount_2);
    
        Clamp = ((localInputAmount < 0) ? 0 : ((localInputAmount > 99) ? 99 : localInputAmount));
    
        cardToChangeRef->maxDefense = Clamp;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_2);
    
        CardFunctionsNotifier->NotifyGainDefense(cardToChange, localInputAmount, CallFunc_getTotalDefense_totalDefense_2, localInstigatorID, changeType);
    
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        EqualEqual_IntInt = CallFunc_getTotalDefense_totalDefense_1 == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_1544;
    
        GetCardFromID(localInstigatorID, CallFunc_GetCardFromID_card);
    
        DestroyCard(cardToChangeRef, CallFunc_GetCardFromID_card);
    
        Label_1544:
        EqualEqual_ByteByte = ((!changeType) == (!0x2));
    
        if (!EqualEqual_ByteByte)
            goto Label_3847;
    
        cardToChangeRef->OnAfterDefenseIsSet();
    
        FetchAllCardsWithEventTrigger(0x6, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_3);
    
        Temp_int_Loop_Counter_Variable_3 = 0;
    
        Temp_int_Array_Index_Variable_3 = 0;
    
        Label_1696:
        Array_Length_3 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_3.Length;
    
        Less_IntInt_3 = (Temp_int_Loop_Counter_Variable_3 < Array_Length_3);
    
        if (!Less_IntInt_3)
            goto Label_3847;
    
        Temp_int_Array_Index_Variable_3 = Temp_int_Loop_Counter_Variable_3;
    
        CallFunc_Array_Get_Item_3 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_3[Temp_int_Array_Index_Variable_3];
    
        EqualEqual_IntInt_1 = cardToChangeRef->cardID == CallFunc_Array_Get_Item_3->cardID;
    
        if (!EqualEqual_IntInt_1)
            goto Label_3937;
    
        goto Label_3863;
    
        Label_1995:
        Less_IntInt_4 = (localInputAmount < 0);
    
        if (!Less_IntInt_4)
            goto Label_2544;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_9);
    
        Add_IntInt_6 = CallFunc_getTotalDefense_totalDefense_9 + localInputAmount;
    
        cardToChangeRef->setAndEncryptDefense(Add_IntInt_6, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_8);
    
        Greater_IntInt_3 = (CallFunc_getTotalDefense_totalDefense_8 > 0);
    
        if (!Greater_IntInt_3)
            goto Label_2475;
    
        Add_IntInt_5 = cardToChangeRef->maxDefense + localInputAmount;
    
        cardToChangeRef->maxDefense = Add_IntInt_5;
    
        Label_2445:
        if (!skipAction)
            goto Label_4042;
    
        Label_2459:
        qqq = false;
    
        return;
    
        Label_2475:
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card_1);
    
        DestroyCard(cardToChangeRef, CallFunc_GetCardFromID_card_1);
    
        goto Label_2445;
    
        Label_2544:
        Greater_IntInt_4 = (localInputAmount > 0);
    
        if (!Greater_IntInt_4)
            return;
    
        if (!skipAction)
            goto Label_3196;
    
        Label_2602:
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_6);
    
        Add_IntInt_4 = CallFunc_getTotalDefense_totalDefense_6 + localInputAmount;
    
        Clamp_1 = ((Add_IntInt_4 < 1) ? 1 : ((Add_IntInt_4 > 99) ? 99 : Add_IntInt_4));
    
        cardToChangeRef->setAndEncryptDefense(Clamp_1, CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_5);
    
        Greater_IntInt_2 = (CallFunc_getTotalDefense_totalDefense_5 > cardToChangeRef->maxDefense);
    
        if (!Greater_IntInt_2)
            goto Label_3050;
    
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_4);
    
        cardToChangeRef->maxDefense = CallFunc_getTotalDefense_totalDefense_4;
    
        Label_3050:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_3180;
    
        cardToChangeRef->IsLocatedInDeck(CallFunc_IsLocatedInDeck_isIt);
    
        BooleanOR = (CallFunc_IsLocatedInDeck_isIt || skipAction);
    
        if (!BooleanOR)
            goto Label_4191;
    
        Label_3180:
        qqq = false;
    
        return;
    
        Label_3196:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_2);
    
        if (!CallFunc_IsActionProcess_ActionProcess_2)
            goto Label_3670;
    
        if (!cardToChangeRef->isSuppressed)
            goto Label_3595;
    
        Label_3269:
        FetchAllCardsWithEventTrigger(0x10, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_3340:
        Array_Length_2 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt_1)
            goto Label_4929;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2[Temp_int_Array_Index_Variable];
    
        EqualEqual_ObjectObject_1 = cardToChangeRef == CallFunc_Array_Get_Item_1;
    
        if (!EqualEqual_ObjectObject_1)
            goto Label_5551;
    
        goto Label_5477;
    
        Label_3595:
        cardToChangeRef->OnBeforeGainDefense(CallFunc_OnBeforeGainDefense_stopAction);
    
        if (!CallFunc_OnBeforeGainDefense_stopAction)
            goto Label_3269;
    
        qqq = false;
    
        return;
    
        Label_3670:
        LessEqual_IntInt = (localInputAmount <= 0);
    
        if (!LessEqual_IntInt)
            goto Label_2602;
    
        qqq = false;
    
        return;
    
        Label_3734:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("change type incorrect for "Change Defense"", this);
    
        qqq = false;
    
        return;
    
        Label_3831:
        qqq = false;
    
        return;
    
        Label_3847:
        qqq = false;
    
        return;
    
        Label_3863:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_3 + 1;
    
        Temp_int_Loop_Counter_Variable_3 = Add_IntInt_3;
    
        goto Label_1696;
    
        Label_3937:
        CallFunc_Array_Get_Item_3 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_3[Temp_int_Array_Index_Variable_3];
    
        CallFunc_Array_Get_Item_3->OnAfterOtherCardDefenseIsSet(cardToChangeRef);
    
        return;
    
        Label_4042:
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_7);
    
        CardFunctionsNotifier->NotifyGainDefense(cardToChangeRef->cardID, localInputAmount, CallFunc_getTotalDefense_totalDefense_7, localInstigatorID, changeType);
    
        goto Label_2459;
    
        Label_4191:
        cardToChangeRef->getTotalDefense(CallFunc_getTotalDefense_totalDefense_3);
    
        CardFunctionsNotifier->NotifyGainDefense(cardToChange, localInputAmount, CallFunc_getTotalDefense_totalDefense_3, localInstigatorID, changeType);
    
        if (!cardToChangeRef->isSuppressed)
            goto Label_4879;
    
        Label_4349:
        FetchAllCardsWithEventTrigger(0x7, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_4420:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_2 < Array_Length);
    
        if (!Less_IntInt_2)
            goto Label_4863;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_2 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_2];
    
        EqualEqual_ObjectObject_2 = cardToChangeRef == CallFunc_Array_Get_Item_2;
    
        if (!EqualEqual_ObjectObject_2)
            goto Label_4675;
    
        goto Label_4789;
    
        Label_4675:
        CallFunc_Array_Get_Item_2 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_2];
    
        CallFunc_Array_Get_Item_2->OnAfterOtherCardGainDefense(cardToChangeRef, localInputAmount);
    
        return;
    
        Label_4789:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_4420;
    
        Label_4863:
        qqq = false;
    
        return;
    
        Label_4879:
        cardToChangeRef->OnAfterGainDefense(localInputAmount);
    
        goto Label_4349;
    
        Label_4929:
        FetchAllCardsWithEventTrigger(0x11, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_5000:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_3670;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable_1];
    
        EqualEqual_ObjectObject = cardToChangeRef == CallFunc_Array_Get_Item;
    
        if (!EqualEqual_ObjectObject)
            goto Label_5255;
    
        goto Label_5403;
    
        Label_5255:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item->OnBeforeOtherCardGainDefenseAfterAdd(cardToChangeRef, localInputAmount, CallFunc_OnBeforeOtherCardGainDefenseAfterAdd_stopAction);
    
        if (!CallFunc_OnBeforeOtherCardGainDefenseAfterAdd_stopAction)
            return;
    
        qqq = false;
    
        return;
    
        Label_5403:
        Add_IntInt = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt;
    
        goto Label_5000;
    
        Label_5477:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt_1;
    
        goto Label_3340;
    
        Label_5551:
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_1->OnBeforeOtherCardGainDefense(cardToChangeRef, localInputAmount, CallFunc_OnBeforeOtherCardGainDefense_newDefenseToAdd, CallFunc_OnBeforeOtherCardGainDefense_stopAction);
    
        if (!CallFunc_OnBeforeOtherCardGainDefense_stopAction)
            goto Label_5712;
    
        qqq = false;
    
        return;
    
        Label_5712:
        localInputAmount = CallFunc_OnBeforeOtherCardGainDefense_newDefenseToAdd;
    
        return;
    
        Label_5740:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ResetCardInBattle(class UBaseCardObject* cardToChange)
    {
        Map_IsNotEmpty = Map_IsNotEmpty(cardToChange->buffsFromCards);
    
        if (!Map_IsNotEmpty)
            goto Label_744;
    
        CallFunc_Map_Keys_Keys = [];
    
        Map_Keys(cardToChange->buffsFromCards, CallFunc_Map_Keys_Keys);
    
        localInstigatorArray = CallFunc_Map_Keys_Keys;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_249:
        Array_Length_1 = localInstigatorArray.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_1345;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = localInstigatorArray[Temp_int_Array_Index_Variable_1];
    
        localInstigatorID = CallFunc_Array_Get_Item_1;
    
        GetCardFromID(localInstigatorID, CallFunc_GetCardFromID_card);
    
        tempInstigatorCard = CallFunc_GetCardFromID_card;
    
        Array_Contains = tempInstigatorCard->cardsBuffedByThisCard[cardToChange->cardID];
    
        if (!Array_Contains)
            goto Label_1271;
    
        Array_RemoveItem = tempInstigatorCard->cardsBuffedByThisCard.Remove(cardToChange->cardID);
    
        return;
    
        Label_744:
        cardToChange->ResetCardAttributes();
    
        goto Label_782;
    
        Label_782:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        cardToChange->OnCardReset();
    
        FetchAllCardsWithEventTrigger(0x35, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_922:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt_1)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardReset(cardToChange, cardToChange->cardID);
    
        goto Label_1197;
    
        Label_1197:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_922;
    
        Label_1271:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_249;
    
        Label_1345:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteStartOfTurnEvents(int turnNumber)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2063;
    
        FetchAllCardsWithEventTrigger(0x40, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        localCardsWithTrigger = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger;
    
        Array_Length = localCardsWithTrigger.Length;
    
        EqualEqual_IntInt = Array_Length == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_202;
    
        return;
    
        Label_202:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_258:
        Array_Length_3 = localCardsWithTrigger.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable < Array_Length_3);
    
        if (!Less_IntInt_2)
            goto Label_724;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_2 = localCardsWithTrigger[Temp_int_Array_Index_Variable_1];
    
        IsValid_2 = CallFunc_Array_Get_Item_2;
    
        if (!IsValid_2)
            goto Label_1989;
    
        CallFunc_Array_Get_Item_2 = localCardsWithTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_2->CustomName1HasAttribute("startofturn0", CallFunc_CustomName1HasAttribute_doesIt_3);
    
        if (!CallFunc_CustomName1HasAttribute_doesIt_3)
            goto Label_1310;
    
        CallFunc_Array_Get_Item_2 = localCardsWithTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_2->OnStartOfTurn(turnNumber);
    
        return;
    
        Label_724:
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_770:
        Array_Length_2 = localCardsWithTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_2);
    
        if (!Less_IntInt_1)
            return;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item = localCardsWithTrigger[Temp_int_Array_Index_Variable_2];
    
        IsValid_1 = CallFunc_Array_Get_Item;
    
        if (!IsValid_1)
            goto Label_1236;
    
        CallFunc_Array_Get_Item = localCardsWithTrigger[Temp_int_Array_Index_Variable_2];
    
        CallFunc_Array_Get_Item->CustomName1HasAttribute("startofturn1", CallFunc_CustomName1HasAttribute_doesIt_2);
    
        if (!CallFunc_CustomName1HasAttribute_doesIt_2)
            return;
    
        CallFunc_Array_Get_Item = localCardsWithTrigger[Temp_int_Array_Index_Variable_2];
    
        CallFunc_Array_Get_Item->OnStartOfTurn(turnNumber);
    
        return;
    
        Label_1236:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_770;
    
        Label_1310:
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1356:
        Array_Length_1 = localCardsWithTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = localCardsWithTrigger[Temp_int_Array_Index_Variable];
    
        IsValid = CallFunc_Array_Get_Item_1;
    
        if (!IsValid)
            goto Label_1915;
    
        CallFunc_Array_Get_Item_1 = localCardsWithTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_1->CustomName1HasAttribute("startofturn0", CallFunc_CustomName1HasAttribute_doesIt);
    
        CallFunc_Array_Get_Item_1->CustomName1HasAttribute("startofturn1", CallFunc_CustomName1HasAttribute_doesIt_1);
    
        BooleanNOR = !(CallFunc_CustomName1HasAttribute_doesIt || CallFunc_CustomName1HasAttribute_doesIt_1);
    
        if (!BooleanNOR)
            return;
    
        CallFunc_Array_Get_Item_1 = localCardsWithTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_1->OnStartOfTurn(turnNumber);
    
        return;
    
        Label_1915:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_1356;
    
        Label_1989:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_258;
    
        Label_2063:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteAfterChangeAttackEvents(class UBaseCardObject* cardChanged, int changedAmount, int instigatorID)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_691;
    
        if (!cardChanged->isSuppressed)
            goto Label_558;
    
        Label_74:
        FetchAllCardsWithEventTrigger(0x5, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_145:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        NotEqual_IntInt = (CallFunc_Array_Get_Item->cardID !== cardChanged->cardID);
    
        if (!NotEqual_IntInt)
            goto Label_617;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnAfterOtherCardChangeAttack(cardChanged, changedAmount, instigatorID);
    
        return;
    
        Label_558:
        cardChanged->OnAfterChangeAttack(changedAmount, instigatorID);
    
        goto Label_74;
    
        Label_617:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_145;
    
        Label_691:
        return;
    }

    // (Event, Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void AddGameplayRestriction(ESideEnum side, EGameplayRestrictions type, int cardID, int turnsToLast)
    {
        MakeStruct_GameplayRestrictionEffect.AffectedSide = side;
    
        MakeStruct_GameplayRestrictionEffect.RestrictionType = type;
    
        MakeStruct_GameplayRestrictionEffect.CardID = cardID;
    
        MakeStruct_GameplayRestrictionEffect.TurnsRemaining = turnsToLast;
    
        GameStateRef->AddGameplayRestrictionEffect(MakeStruct_GameplayRestrictionEffect);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyAddGameplayRestrictionEffect(side, type, cardID, turnsToLast);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void RemoveGameplayRestriction(ESideEnum side, EGameplayRestrictions type, int cardID, bool removeAll, int& qqq)
    {
        GameStateRef->RemoveGameplayRestrictionEffect(side, type, cardID, removeAll);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyRemoveGameplayRestrictionEffect(side, type, cardID, removeAll);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void MakeCountAsTank(int cardID, int instigatorID, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        IsValid = CallFunc_GetCardFromID_card;
    
        if (!IsValid)
            goto Label_290;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CardToMake = CallFunc_GetCardFromID_card;
    
        CardToMake->CustomName1Add("isAlsoTank");
    
        CardToMake->CustomName1Add("CanMoveAndAttackInTheSameTurn");
    
        PersistCustomFields(CardToMake->cardID, false);
    
        goto Label_318;
    
        Label_290:
        qqq = 0;
    
        return;
    
        Label_318:
        ExecuteOnOtherCardsAbilitiesChanged(CardToMake);
    
        goto Label_342;
    
        Label_342:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetCardsOnBoardBySide(ESideEnum side, bool unitsOnly, bool includeCovertCards, TArray<class UBaseCardObject*>& cards)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_904;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        localCard = CallFunc_Array_Get_Item;
    
        localCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        localCard->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        Greater_IntInt = (CallFunc_getTotalDefense_totalDefense > 0);
    
        Not_PreBool = !CallFunc_IsUnrevealedCovertCard_isIt;
    
        localCard->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        BooleanOR = (Not_PreBool || includeCovertCards);
    
        EqualEqual_ByteByte = ((!side) == (!localCard->side));
    
        BooleanAND = EqualEqual_ByteByte && CallFunc_IsLocatedOnBoard_isIt;
    
        BooleanAND_1 = BooleanAND && BooleanOR;
    
        BooleanAND_2 = BooleanAND_1 && Greater_IntInt;
    
        if (!BooleanAND_2)
            goto Label_936;
    
        if (!unitsOnly)
            goto Label_835;
    
        localCard->IsUnit(CallFunc_IsUnit_isIt);
    
        if (!CallFunc_IsUnit_isIt)
            goto Label_1010;
    
        Label_835:
        Array_Add = _cards.Add(localCard);
    
        return;
    
        Label_904:
        cards = _cards;
    
        return;
    
        Label_936:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_1010:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetCardsInHandBySide(ESideEnum side, TArray<class UBaseCardObject*>& cards)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_580;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        localCard = CallFunc_Array_Get_Item;
    
        localCard->IsLocatedInHand(CallFunc_IsLocatedInHand_isIt);
    
        EqualEqual_ByteByte = ((!side) == (!localCard->side));
    
        BooleanAND = EqualEqual_ByteByte && CallFunc_IsLocatedInHand_isIt;
    
        if (!BooleanAND)
            goto Label_612;
    
        Array_Add = _cards.Add(localCard);
    
        goto Label_686;
    
        Label_580:
        cards = _cards;
    
        return;
    
        Label_612:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_686:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetCardsInFrontlineBySide(ESideEnum side, bool includeCovertCards, TArray<class UBaseCardObject*>& cards)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_823;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        EqualEqual_ByteByte = ((!side) == (!CallFunc_Array_Get_Item->side));
    
        CallFunc_Array_Get_Item->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        EqualEqual_ByteByte_1 = ((!CallFunc_Array_Get_Item->location) == (!0x7));
    
        Not_PreBool = !CallFunc_IsUnrevealedCovertCard_isIt;
    
        BooleanAND = EqualEqual_ByteByte && EqualEqual_ByteByte_1;
    
        BooleanOR = (Not_PreBool || includeCovertCards);
    
        BooleanAND_1 = BooleanAND && BooleanOR;
    
        if (!BooleanAND_1)
            goto Label_855;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Array_Add = _cards.Add(CallFunc_Array_Get_Item);
    
        goto Label_929;
    
        Label_823:
        cards = _cards;
    
        return;
    
        Label_855:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_929:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetCardsInSupportLineBySide(ESideEnum side, bool unitsOnly, bool includeCovertCards, TArray<class UBaseCardObject*>& cards)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1037;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        Not_PreBool = !CallFunc_IsUnrevealedCovertCard_isIt;
    
        EqualEqual_ByteByte = ((!side) == (!CallFunc_Array_Get_Item->side));
    
        BooleanOR = (Not_PreBool || includeCovertCards);
    
        GetSupportLineBySide = UCombatHelperFunctions::GetSupportLineBySide(side, this);
    
        EqualEqual_ByteByte_1 = ((!CallFunc_Array_Get_Item->location) == (!GetSupportLineBySide));
    
        BooleanAND = EqualEqual_ByteByte && EqualEqual_ByteByte_1;
    
        BooleanAND_1 = BooleanAND && BooleanOR;
    
        if (!BooleanAND_1)
            goto Label_1069;
    
        if (!unitsOnly)
            goto Label_864;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->IsUnit(CallFunc_IsUnit_isIt);
    
        if (!CallFunc_IsUnit_isIt)
            goto Label_1143;
    
        Label_864:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Array_Add = _cards.Add(CallFunc_Array_Get_Item);
    
        return;
    
        Label_1037:
        cards = _cards;
    
        return;
    
        Label_1069:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_1143:
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void AddToBattleLog(int cardID, int instigatorID, bool cardHidden, bool showAnimation)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyAddToBattlelog(cardID, instigatorID, cardHidden, showAnimation);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetKreditsBySide(ESideEnum side, int& kredits)
    {
        GameStateRef->getKreditBySide(side, CallFunc_getKreditBySide_outputKredit);
    
        kredits = CallFunc_getKreditBySide_outputKredit;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetMaxKreditsBySide(ESideEnum side, int& maxkredits)
    {
        GameStateRef->getKreditSlotBySide(side, CallFunc_getKreditSlotBySide_outputKreditSlot);
    
        maxkredits = CallFunc_getKreditSlotBySide_outputKreditSlot;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void GiveKreditsBySide(ESideEnum side, int kredits, int instigatorID, bool& qqq)
    {
        ChangeKreditsBySide(side, kredits, instigatorID);
    
        qqq = false;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetDestroyedCardsCountBySide(ESideEnum sideToGet, int& count)
    {
        GameStateRef->GetDestroyedCardsCountBySide(sideToGet, CallFunc_GetDestroyedCardsCountBySide_count);
    
        count = CallFunc_GetDestroyedCardsCountBySide_count;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetDestroyedCardsIDsThisBattle(TArray<int>& destroyedCardsIDs)
    {
        GameStateRef->GetDestroyedCardsIDs(CallFunc_GetDestroyedCardsIDs_DestroyedCardsIDs);
    
        destroyedCardsIDs = CallFunc_GetDestroyedCardsIDs_DestroyedCardsIDs;
    
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void SetRandomStreamByMatchID(int MatchID)
    {
        MakeRandomStream = UKismetMathLibrary::MakeRandomStream(MatchID);
    
        cardsRandomStream = MakeRandomStream;
    
        encryptionStream = cardsRandomStream;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ShuffleDeckBySide(ESideEnum sideToShuffle, bool skipSubAction, int instigatorID, bool& qqq)
    {
        GameStateRef->GetDeckBySide(sideToShuffle, CallFunc_GetDeckBySide_DeckCardIDs);
    
        localDeckCardIDs = CallFunc_GetDeckBySide_DeckCardIDs;
    
        Array_IsEmpty = Array_IsEmpty(localDeckCardIDs);
    
        if (!Array_IsEmpty)
            goto Label_152;
    
        goto Label_830;
    
        Label_152:
        Array_ShuffleFromStream(localDeckCardIDs, cardsRandomStream);
    
        GameStateRef->SetDeckBySide(sideToShuffle, localDeckCardIDs);
    
        ExecuteOnAfterDeckChanged(sideToShuffle);
    
        if (!skipSubAction)
            goto Label_729;
    
        goto Label_299;
    
        Label_299:
        FetchAllCardsWithEventTrigger(0x16, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_370:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card);
    
        CallFunc_Array_Get_Item->OnDeckShuffled(sideToShuffle, CallFunc_GetCardFromID_card);
    
        goto Label_655;
    
        Label_655:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_370;
    
        Label_729:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyNewDeck(sideToShuffle, localDeckCardIDs, Temp_int_Variable, 0x0, false, true);
    
        return;
    
        Label_830:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void RandomIntFromRangeWithStream(int minimum, int maximum, int& randomResult)
    {
        RandomIntegerInRangeFromStream = UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, minimum, maximum);
    
        randomResult = RandomIntegerInRangeFromStream;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ChangedPinnedTurns(int cardID, int instigatorID, int turnsToChange, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        cardToChange = CallFunc_GetCardFromID_card;
    
        IsValid = cardToChange;
    
        if (!IsValid)
            return;
    
        cardToChange->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            return;
    
        cardToChange->IsUnit(CallFunc_IsUnit_isIt);
    
        if (!CallFunc_IsUnit_isIt)
            return;
    
        Add_IntInt = cardToChange->pinnedTurns + turnsToChange;
    
        Clamp = ((Add_IntInt < 0) ? 0 : ((Add_IntInt > 5) ? 5 : Add_IntInt));
    
        cardToChange->pinnedTurns = Clamp;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyChangePinnedTurns(cardID, instigatorID, turnsToChange);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetHQ_DamagedAmountThisTurnBySide(ESideEnum sideToGet, int& damagedAmount)
    {
        GameStateRef->GetHQ_DamagedAmountThisTurn(sideToGet, CallFunc_GetHQ_DamagedAmountThisTurn_damagedAmount);
    
        damagedAmount = CallFunc_GetHQ_DamagedAmountThisTurn_damagedAmount;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetCardsPlayedFromHandThisTurn(TArray<int>& CardIDsPlayedThisTurn)
    {
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        GameStateRef->getCardsPlayedFromHandByTurn(CallFunc_GetTurnNumber_turnNumber, CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed);
    
        CardIDsPlayedThisTurn = CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ConvertCard(const TArray<int>*& cardIDs, int instigatorID, FName convertToCardName, int convertIntoCardID, bool skipTrigger, TArray<int>& newCardIDs)
    {
        _oldLocationNumber = 0;
    
        _oldLocation = 0x0;
    
        spawnedCardID = 0;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_117:
        Array_Length = cardIDs.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt)
            goto Label_453;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = cardIDs[Temp_int_Array_Index_Variable_1];
    
        _currentCardID = CallFunc_Array_Get_Item;
    
        GetCardFromID(_currentCardID, CallFunc_GetCardFromID_card_3);
    
        _oldCard = CallFunc_GetCardFromID_card_3;
    
        _oldCard->IsLocation(CallFunc_IsLocation_isIt);
    
        if (!CallFunc_IsLocation_isIt)
            goto Label_1436;
    
        goto Label_1362;
    
        Label_453:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_610;
    
        Conv_NameToString = FString(convertToCardName);
    
        CardFunctionsNotifier->NotifyConvertCard(cardIDs, instigatorID, _newCardIDs, Conv_NameToString, _oldLocation);
    
        goto Label_4555;
    
        Label_610:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_661:
        Array_Length_2 = _newCardIDs.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt_1)
            goto Label_1310;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_2 = _newCardIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item_2, CallFunc_GetCardFromID_card_1);
    
        EqualEqual_ByteByte = ((!CallFunc_GetCardFromID_card_1->location) == (!0x7));
    
        if (!EqualEqual_ByteByte)
            goto Label_1051;
    
        CallFunc_Array_Get_Item_2 = _newCardIDs[Temp_int_Array_Index_Variable];
    
        RemoveSmokescreen(CallFunc_Array_Get_Item_2, CallFunc_Array_Get_Item_2, true, false);
    
        Label_1051:
        CallFunc_Array_Get_Item_2 = _newCardIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item_2, CallFunc_GetCardFromID_card_1);
    
        CallFunc_GetCardFromID_card_1->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            goto Label_3413;
    
        CallFunc_Array_Get_Item_2 = _newCardIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item_2, CallFunc_GetCardFromID_card_1);
    
        ExecuteOnEnterPlayEvents(CallFunc_GetCardFromID_card_1, 0x5);
    
        return;
    
        Label_1310:
        if (!skipTrigger)
            goto Label_3487;
    
        goto Label_1330;
    
        Label_1330:
        newCardIDs = _newCardIDs;
    
        return;
    
        Label_1362:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_117;
    
        Label_1436:
        _oldLocation = _oldCard->location;
    
        _oldLocationNumber = _oldCard->locationNumber;
    
        goto Label_1545;
    
        Label_1545:
        _oldCard->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt_1);
    
        if (!CallFunc_IsLocatedOnBoard_isIt_1)
            goto Label_1637;
    
        ApplyRemoveCardFromBoard(_currentCardID, instigatorID, false, false, true, true);
    
        goto Label_1668;
    
        Label_1637:
        SetCardLocationAndLocNumber(_currentCardID, 0x8, 0);
    
        return;
    
        Label_1668:
        Greater_IntInt_2 = (convertIntoCardID > 0);
    
        if (!Greater_IntInt_2)
            goto Label_1767;
    
        GetCardFromID(convertIntoCardID, CallFunc_GetCardFromID_card_2);
    
        converIntoCardID_Ref = CallFunc_GetCardFromID_card_2;
    
        Label_1767:
        EqualEqual_ByteByte_1 = ((!_oldLocation) == (!0x8));
    
        if (!EqualEqual_ByteByte_1)
            goto Label_1893;
    
        GetHandLocationBySide(_oldCard->side, CallFunc_GetHandLocationBySide_handLocation);
    
        _oldLocation = CallFunc_GetHandLocationBySide_handLocation;
    
        Label_1893:
        Temp_struct_Variable = FS_SalvagedCardInfo(false, 0x0, 0);
    
        Temp_byte_Variable = 0x0;
    
        Greater_IntInt = (convertIntoCardID > 0);
    
        Greater_IntInt_1 = (convertIntoCardID > 0);
    
        Temp_bool_Variable = Greater_IntInt_1;
    
        Temp_bool_Variable_1 = converIntoCardID_Ref->isSalvaged;
    
        MakeStruct_S_SalvagedCardInfo.isSalvaged_1_D83369C241D0F4E11CEDCB8250BC0D97 = converIntoCardID_Ref->isSalvaged;
    
        MakeStruct_S_SalvagedCardInfo.salvageFaction_5_30136A02489F9A3E6C29FEB0A508ADD9 = Temp_bool_Variable_1 ? converIntoCardID_Ref->salvageFaction : Temp_byte_Variable;
    
        MakeStruct_S_SalvagedCardInfo.salvagedCardID_8_60B10C4245C90998186E6E9E7E180468 = 0;
    
        Temp_bool_Variable_2 = Greater_IntInt;
    
        EqualEqual_ByteByte_2 = ((!_oldLocation) == (!0x4));
    
        EqualEqual_ByteByte_3 = ((!_oldLocation) == (!0x3));
    
        BooleanOR = (EqualEqual_ByteByte_3 || EqualEqual_ByteByte_2);
    
        CreateCard(_oldCard->side, Temp_bool_Variable_2 ? converIntoCardID_Ref->name : convertToCardName, _oldLocation, 0, _oldLocationNumber, BooleanOR, _oldCard->isGoldCard, "", false, false, instigatorID, false, Temp_bool_Variable ? MakeStruct_S_SalvagedCardInfo : Temp_struct_Variable, true, false, false, CallFunc_CreateCard_cardID);
    
        spawnedCardID = CallFunc_CreateCard_cardID;
    
        Array_Add = _newCardIDs.Add(spawnedCardID);
    
        GetCardFromID(spawnedCardID, CallFunc_GetCardFromID_card);
    
        _spawnedCard = CallFunc_GetCardFromID_card;
    
        SwitchEnum_CmpSuccess = ((!_oldLocation) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_3108;
    
        SwitchEnum_CmpSuccess = ((!_oldLocation) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_3108;
    
        SwitchEnum_CmpSuccess = ((!_oldLocation) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_4059;
    
        SwitchEnum_CmpSuccess = ((!_oldLocation) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_4059;
    
        SwitchEnum_CmpSuccess = ((!_oldLocation) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_4262;
    
        SwitchEnum_CmpSuccess = ((!_oldLocation) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_4262;
    
        SwitchEnum_CmpSuccess = ((!_oldLocation) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_4262;
    
        return;
    
        Label_3108:
        GameStateRef->RemoveCardFromDeckBySide(_oldCard->side, _oldCard->cardID, CallFunc_RemoveCardFromDeckBySide_removedIndex);
    
        Greater_IntInt_3 = (CallFunc_RemoveCardFromDeckBySide_removedIndex > -1);
    
        if (!Greater_IntInt_3)
            return;
    
        GameStateRef->AddCardToDeckBySide(_spawnedCard->side, _spawnedCard->cardID, false, CallFunc_RemoveCardFromDeckBySide_removedIndex);
    
        ExecuteOnAfterDeckChanged(_spawnedCard->side);
    
        return;
    
        Label_3413:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_661;
    
        Label_3487:
        FetchAllCardsWithEventTrigger(0x22, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_3558:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_1);
    
        if (!Less_IntInt_2)
            return;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_2];
    
        Array_Contains = _newCardIDs[CallFunc_Array_Get_Item_1->cardID];
    
        if (!Array_Contains)
            goto Label_3853;
    
        goto Label_3985;
    
        Label_3853:
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_2];
    
        CallFunc_Array_Get_Item_1->OnOtherCardConverted(cardIDs, _newCardIDs, convertToCardName, instigatorID);
    
        return;
    
        Label_3985:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_3558;
    
        Label_4059:
        ExecuteOnSpawnedInHandEvents(_spawnedCard->side, _spawnedCard->cardID);
    
        GameStateRef->GetIsLocalClientTurn(CallFunc_GetIsLocalClientTurn_IsClientTurn);
    
        Not_PreBool = !CallFunc_GetIsLocalClientTurn_IsClientTurn;
    
        MakeArray_Array = [ _spawnedCard ];
    
        ApplySetCardsSeenByCipher(MakeArray_Array, Not_PreBool, false);
    
        Label_4262:
        InjectCardIntoLocation(_oldLocation, _oldLocationNumber, _spawnedCard->cardID);
    
        MakeSet_Set = TArray { _oldLocation };;
    
        RefreshLocationStatus(MakeSet_Set);
    
        ExecuteOnCardLocationMoved(_spawnedCard->cardID, 0x0, _oldLocation, false, 0xD);
    
        _spawnedCard->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt_2);
    
        if (!CallFunc_IsLocatedOnBoard_isIt_2)
            return;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        _spawnedCard->enterPlayOnTurn = CallFunc_GetTurnNumber_turnNumber;
    
        return;
    
        Label_4555:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void InitializeEssentialActors()
    {
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void DiscardOnDrawingWithFullHands(int cardID, int insitigatorID, ECardLocationEnum oldLocation)
    {
        SetCardLocationAndLocNumber(cardID, 0x8, 0);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyDiscardCard(cardID, insitigatorID, oldLocation, false, false);
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void DrawTopCardFromDeck(ESideEnum deckSide, int instigatorID, bool opponentDraw, bool cardSeen, bool startOfTurnDraw, double delay, bool scryingDraw, int& drawnCard)
    {
        GetTheOtherSide = UCombatHelperFunctions::GetTheOtherSide(deckSide, this);
    
        Temp_bool_Variable = opponentDraw;
    
        handSide = Temp_bool_Variable ? GetTheOtherSide : deckSide;
    
        GetHandLocationBySide(handSide, CallFunc_GetHandLocationBySide_handLocation);
    
        handLocation = CallFunc_GetHandLocationBySide_handLocation;
    
        GameStateRef->GetDeckBySide(deckSide, CallFunc_GetDeckBySide_DeckCardIDs);
    
        deckCardIDsRef = CallFunc_GetDeckBySide_DeckCardIDs;
    
        Array_IsEmpty = Array_IsEmpty(deckCardIDsRef);
    
        if (!Array_IsEmpty)
            goto Label_474;
    
        ApplyFatigueDamage(deckSide, false, CallFunc_ApplyFatigueDamage_destroyed);
    
        if (!CallFunc_ApplyFatigueDamage_destroyed)
            goto Label_446;
    
        GetTheOtherSide_1 = UCombatHelperFunctions::GetTheOtherSide(deckSide, this);
    
        HQ_DestroyedEndMatch(GetTheOtherSide_1);
    
        Label_446:
        drawnCard = 0;
    
        return;
    
        Label_474:
        drawnCardID = deckCardIDsRef[0];
    
        GetCardFromID(drawnCardID, CallFunc_GetCardFromID_card);
    
        drawnCardRef = CallFunc_GetCardFromID_card;
    
        GameStateRef->RemoveCardFromDeckBySide(deckSide, drawnCardID, CallFunc_RemoveCardFromDeckBySide_removedIndex);
    
        ExecuteOnAfterDeckChanged(deckSide);
    
        FetchCardsByLocation(handLocation, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        nextHandLocation = CallFunc_FetchCardsByLocation_QtyInLocation;
    
        isHandFull = CallFunc_FetchCardsByLocation_isLocationFull;
    
        if (!isHandFull)
            goto Label_1042;
    
        drawnCardRef->location = 0x8;
    
        Label_814:
        Conv_NameToString = FString(drawnCardRef->name);
    
        CardFunctionsNotifier->NotifyDrawCardFromDeck(instigatorID, handSide, drawnCardID, Conv_NameToString, false, scryingDraw, nextHandLocation, isHandFull, 0, "", 0, opponentDraw, delay);
    
        if (!isHandFull)
            goto Label_1274;
    
        Label_1027:
        if (!isHandFull)
            goto Label_1329;
    
        goto Label_1194;
    
        Label_1042:
        drawnCardRef->locationNumber = nextHandLocation;
    
        drawnCardRef->location = handLocation;
    
        drawnCardRef->side = handSide;
    
        goto Label_814;
    
        Label_1194:
        if (!cardSeen)
            goto Label_1242;
    
        SetCardSeen(drawnCardID, 0, CallFunc_SetCardSeen_qqq);
    
        goto Label_1475;
    
        Label_1242:
        drawnCard = drawnCardID;
    
        return;
    
        Label_1274:
        ExecuteOnDrawnFromDeck(drawnCardID, handSide, startOfTurnDraw, CallFunc_ExecuteOnDrawnFromDeck_newlyDrawnCard);
    
        goto Label_1027;
    
        Label_1329:
        drawnCardRef->getHasGameplayTag(FGameplayTag("autoplay"), CallFunc_getHasGameplayTag_hasTag);
    
        if (!CallFunc_getHasGameplayTag_hasTag)
            return;
    
        GameStateRef->AddAutoPlayCards(drawnCardRef->cardID);
    
        return;
    
        Label_1475:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void FetchAllCardsWithEventTrigger(ERegisteredCardFunction EventTrigger, TArray<class UBaseCardObject*>& cardsWithThisTrigger)
    {
        GameStateRef->FetchAllCardsWithEventTrigger(EventTrigger, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        cardsWithThisTrigger = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger;
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteEndOfTurnEvents()
    {
        newEndOfTurnCardFound = false;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        FetchAllCardsWithEventTrigger(0x19, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        ExecuteEndOfTurnQueue(Temp_object_Variable, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger, 0);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void IsTopDeckNavy(ESideEnum deckSide, bool& isNavy)
    {
        GetDeckByside(deckSide, CallFunc_GetDeckByside_deckCardIDs);
    
        Greater_IntInt = (CallFunc_GetDeckByside_deckCardIDs[0] > 0);
    
        if (!Greater_IntInt)
            goto Label_267;
    
        GetDeckByside(deckSide, CallFunc_GetDeckByside_deckCardIDs);
    
        GetCardFromID(CallFunc_GetDeckByside_deckCardIDs[0], CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->getHasGameplayTag(FGameplayTag("subtype.navy"), CallFunc_getHasGameplayTag_hasTag);
    
        localIsNavy = CallFunc_getHasGameplayTag_hasTag;
    
        Label_243:
        isNavy = localIsNavy;
    
        return;
    
        Label_267:
        localIsNavy = false;
    
        goto Label_243;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteEndOfTurnQueue(TArray<class UBaseCardObject*>*& ResolvedCards, TArray<class UBaseCardObject*>*& CardsToResolve, int RecursionLoop)
    {
        MakeVariable_MakeVariableOutput = TArray { "card_unit_mosquito_fighter", "card_unit_mosquito_fighter_bal", "card_unit_mosquito_bomber", "card_unit_mosquito_bomber_bal" };;
    
        skipEndOfTurnForSpawnedCards = MakeVariable_MakeVariableOutput;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_3 = 0;
    
        Label_145:
        Array_Length = CardsToResolve.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt)
            goto Label_502;
    
        Temp_int_Array_Index_Variable_3 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CardsToResolve[Temp_int_Array_Index_Variable_3];
    
        localCardWithTrigger = CallFunc_Array_Get_Item;
    
        localCardWithTrigger->CustomName1HasAttribute("endofturn2", CallFunc_CustomName1HasAttribute_doesIt_1);
    
        if (!CallFunc_CustomName1HasAttribute_doesIt_1)
            goto Label_1999;
    
        Array_Add_2 = endofturn2.Add(localCardWithTrigger);
    
        goto Label_1925;
    
        Label_502:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_548:
        Array_Length_3 = endofturn1.Length;
    
        Less_IntInt_3 = (Temp_int_Loop_Counter_Variable < Array_Length_3);
    
        if (!Less_IntInt_3)
            goto Label_819;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber_1);
    
        CallFunc_Array_Get_Item_3 = endofturn1[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_3->OnEndOfTurn(CallFunc_GetTurnNumber_turnNumber_1);
    
        goto Label_2204;
    
        Label_819:
        Temp_int_Loop_Counter_Variable_3 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_865:
        Array_Length_2 = endofturn2.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_3 < Array_Length_2);
    
        if (!Less_IntInt_2)
            goto Label_1136;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_3;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        CallFunc_Array_Get_Item_2 = endofturn2[Temp_int_Array_Index_Variable_2];
    
        CallFunc_Array_Get_Item_2->OnEndOfTurn(CallFunc_GetTurnNumber_turnNumber);
    
        goto Label_2278;
    
        Label_1136:
        Array_Append(ResolvedCards, CardsToResolve);
    
        FetchAllCardsWithEventTrigger(0x19, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1257:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_1654;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        Array_Contains = ResolvedCards[CallFunc_Array_Get_Item_1];
    
        Set_Contains = Set_Contains(skipEndOfTurnForSpawnedCards, CallFunc_Array_Get_Item_1->name);
    
        BooleanOR = (Array_Contains || Set_Contains);
    
        if (!BooleanOR)
            goto Label_2426;
    
        goto Label_2352;
    
        Label_1654:
        Array_IsEmpty = Array_IsEmpty(newEndOfTurnCards);
    
        if (!Array_IsEmpty)
            goto Label_1734;
    
        Label_1719:
        RemoveBuffsEndOfTurn();
    
        goto Label_2554;
    
        Label_1734:
        Add_IntInt_4 = RecursionLoop + 1;
    
        Temp_int_Variable = Add_IntInt_4;
    
        RecursionLoop = Temp_int_Variable;
    
        Greater_IntInt = (Temp_int_Variable > 5);
    
        if (!Greater_IntInt)
            goto Label_1883;
    
        goto Label_1719;
    
        Label_1883:
        ExecuteEndOfTurnQueue(ResolvedCards, newEndOfTurnCards, Temp_int_Variable);
    
        return;
    
        Label_1925:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_145;
    
        Label_1999:
        localCardWithTrigger->CustomName1HasAttribute("endofturn1", CallFunc_CustomName1HasAttribute_doesIt);
    
        if (!CallFunc_CustomName1HasAttribute_doesIt)
            goto Label_2135;
    
        Array_Add_1 = endofturn1.Add(localCardWithTrigger);
    
        return;
    
        Label_2135:
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber_2);
    
        localCardWithTrigger->OnEndOfTurn(CallFunc_GetTurnNumber_turnNumber_2);
    
        return;
    
        Label_2204:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_548;
    
        Label_2278:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_3 + 1;
    
        Temp_int_Loop_Counter_Variable_3 = Add_IntInt_3;
    
        goto Label_865;
    
        Label_2352:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_1257;
    
        Label_2426:
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        Array_Add = newEndOfTurnCards.Add(CallFunc_Array_Get_Item_1);
    
        return;
    
        Label_2554:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnBeforeLeaveBoardOrOwnerEvents(int CardLeaving, ECardLocationEnum NewLocation, ECardLocationEnum OldLocation, EOnLeavePlayMethod method)
    {
        Greater_IntInt = (CardLeaving > 0);
    
        if (!Greater_IntInt)
            goto Label_978;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        SwitchEnum_CmpSuccess = ((!OldLocation) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_218;
    
        SwitchEnum_CmpSuccess = ((!OldLocation) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_218;
    
        SwitchEnum_CmpSuccess = ((!OldLocation) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_218;
    
        return;
    
        Label_218:
        GetCardFromID(CardLeaving, CallFunc_GetCardFromID_card);
    
        localCardLeaving = CallFunc_GetCardFromID_card;
    
        localCardLeaving->hasActivePincerEffect(CallFunc_hasActivePincerEffect_doesIt);
    
        if (!CallFunc_hasActivePincerEffect_doesIt)
            goto Label_347;
    
        RemovePincerEffects(localCardLeaving);
    
        Label_347:
        if (!localCardLeaving->isSuppressed)
            goto Label_845;
    
        Label_383:
        FetchAllCardsWithEventTrigger(0x2E, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_454:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        NotEqual_IntInt = (CallFunc_Array_Get_Item->cardID !== CardLeaving);
    
        if (!NotEqual_IntInt)
            goto Label_904;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardLeaveBoardOrOwner(localCardLeaving, NewLocation, method);
    
        return;
    
        Label_845:
        localCardLeaving->OnLeaveBoardOrOwner(NewLocation, method);
    
        goto Label_383;
    
        Label_904:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_454;
    
        Label_978:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnSurvivedCombatEvents(class UBaseCardObject* cardSurviving, class UBaseCardObject* cardCombatted)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_673;
    
        if (!cardSurviving->isSuppressed)
            goto Label_549;
    
        Label_74:
        FetchAllCardsWithEventTrigger(0x3B, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_145:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        NotEqual_IntInt = (CallFunc_Array_Get_Item->cardID !== cardSurviving->cardID);
    
        if (!NotEqual_IntInt)
            goto Label_599;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardSurvivedCombat(cardSurviving, cardCombatted);
    
        return;
    
        Label_549:
        cardSurviving->OnSurvivedCombat(cardCombatted);
    
        goto Label_74;
    
        Label_599:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_145;
    
        Label_673:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void SetDeckBySide(ESideEnum deckSide, const TArray<int>*& deckCardIDs, bool& qqq)
    {
        GameStateRef->SetDeckBySide(deckSide, deckCardIDs);
    
        qqq = false;
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnAfterLeaveBoardOrOwnerEvents(int CardLeaving, ECardLocationEnum NewLocation, ECardLocationEnum OldLocation)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_960;
    
        Greater_IntInt = (CardLeaving > 0);
    
        if (!Greater_IntInt)
            return;
    
        SwitchEnum_CmpSuccess = ((!OldLocation) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_218;
    
        SwitchEnum_CmpSuccess = ((!OldLocation) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_218;
    
        SwitchEnum_CmpSuccess = ((!OldLocation) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_218;
    
        return;
    
        Label_218:
        GetCardFromID(CardLeaving, CallFunc_GetCardFromID_card);
    
        localCardLeaving = CallFunc_GetCardFromID_card;
    
        localCardLeaving->hasActivePincerEffect(CallFunc_hasActivePincerEffect_doesIt);
    
        if (!CallFunc_hasActivePincerEffect_doesIt)
            goto Label_347;
    
        RemovePincerEffects(localCardLeaving);
    
        Label_347:
        if (!localCardLeaving->isSuppressed)
            goto Label_836;
    
        Label_383:
        FetchAllCardsWithEventTrigger(0x8, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_454:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        NotEqual_IntInt = (CallFunc_Array_Get_Item->cardID !== CardLeaving);
    
        if (!NotEqual_IntInt)
            goto Label_886;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnAfterOtherCardLeaveBoardOrOwner(localCardLeaving, OldLocation);
    
        return;
    
        Label_836:
        localCardLeaving->OnAfterLeaveBoard(NewLocation);
    
        goto Label_383;
    
        Label_886:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_454;
    
        Label_960:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnEnterPlayEvents(class UBaseCardObject* cardEnterPlay, EOnEnterPlayMethod enterPlayMethod)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_678;
    
        if (!cardEnterPlay->isSuppressed)
            goto Label_440;
    
        Label_74:
        FetchAllCardsWithEventTrigger(0x2B, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_145:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->cardID == cardEnterPlay->cardID;
    
        if (!EqualEqual_IntInt)
            goto Label_564;
    
        goto Label_490;
    
        Label_440:
        cardEnterPlay->OnEnterPlay(enterPlayMethod);
    
        goto Label_74;
    
        Label_490:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_145;
    
        Label_564:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardEnterPlay(cardEnterPlay, enterPlayMethod);
    
        return;
    
        Label_678:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnSpawnedInHandEvents(ESideEnum spawnedSide, int spawnedCardID)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_805;
    
        GetCardFromID(spawnedCardID, CallFunc_GetCardFromID_card);
    
        spawnedCard = CallFunc_GetCardFromID_card;
    
        IsValid = spawnedCard;
    
        if (!IsValid)
            goto Label_177;
    
        spawnedCard->OnCardSpawnedInHand(spawnedSide);
    
        Label_177:
        FetchAllCardsWithEventTrigger(0x39, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_248:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->cardID == spawnedCardID;
    
        if (!EqualEqual_IntInt)
            goto Label_595;
    
        goto Label_521;
    
        Label_521:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_248;
    
        Label_595:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        if (!CallFunc_Array_Get_Item->isSuppressed)
            goto Label_691;
    
        return;
    
        Label_691:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardSpawnedInHand(spawnedCardID, spawnedSide);
    
        return;
    
        Label_805:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteBeforeStartOfTurnEvents()
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_418;
    
        FetchAllCardsWithEventTrigger(0x14, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_109:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnBeforeStartOfTurn();
    
        goto Label_344;
    
        Label_344:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_109;
    
        Label_418:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void ApplyPincerEffects(class UBaseCardObject* cardPlayed, class UBaseCardObject* cardTargeted)
    {
        NotEqual_ByteByte = ((!cardPlayed->location) !== (!0x8));
    
        if (!NotEqual_ByteByte)
            goto Label_505;
    
        cardPlayed->OnPincerEffectApplied(cardPlayed);
    
        JSON_SetInt(cardPlayed, "pincer_receiver", cardTargeted->cardID, CallFunc_JSON_SetInt_found);
    
        PersistCustomFields(cardPlayed->cardID, true);
    
        cardPlayed->OnPincerEffectReceived(cardPlayed);
    
        goto Label_290;
    
        Label_290:
        cardPlayed->OnPincerEffectApplied(cardTargeted);
    
        JSON_AddToIntArray(cardTargeted, "pincer_givers", cardPlayed->cardID, CallFunc_JSON_AddToIntArray_found);
    
        PersistCustomFields(cardTargeted->cardID, true);
    
        cardTargeted->OnPincerEffectReceived(cardPlayed);
    
        return;
    
        Label_505:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnDrawnFromDeck(int DrawnCardID, ESideEnum DrawnSide, bool StartOfTurnDraw, class UBaseCardObject*& newlyDrawnCard)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_772;
    
        GetCardFromID(DrawnCardID, CallFunc_GetCardFromID_card);
    
        drawnCard = CallFunc_GetCardFromID_card;
    
        IsValid = drawnCard;
    
        if (!IsValid)
            goto Label_535;
    
        drawnCard->OnCardDrawnFromDeck(StartOfTurnDraw, DrawnSide);
    
        FetchAllCardsWithEventTrigger(0x2A, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_262:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_551;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->cardID == DrawnCardID;
    
        if (!EqualEqual_IntInt)
            goto Label_649;
    
        goto Label_575;
    
        Label_535:
        newlyDrawnCard = nullptr;
    
        return;
    
        Label_551:
        newlyDrawnCard = drawnCard;
    
        return;
    
        Label_575:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_262;
    
        Label_649:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardDrawnFromDeck(DrawnCardID, StartOfTurnDraw, DrawnSide);
    
        return;
    
        Label_772:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteBeforeReceiveDamage(class UBaseCardObject* cardToReceiveDamage, class UBaseCardObject* cardToDealDamage, int damageAmount, bool isCombatDamage)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_952;
    
        if (!cardToReceiveDamage->isSuppressed)
            goto Label_687;
    
        Label_74:
        GetOpponentSide(CallFunc_GetOpponentSide_OutOpponentSide);
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card, CallFunc_GetLocationCardBySide_locationCardID, CallFunc_GetOpponentSide_OutOpponentSide);
    
        EqualEqual_IntInt_1 = cardToReceiveDamage->cardID == CallFunc_GetLocationCardBySide_locationCardID;
    
        Greater_IntInt = (damageAmount > 1);
    
        BooleanAND = EqualEqual_IntInt_1 && Greater_IntInt;
    
        if (!BooleanAND)
            goto Label_321;
    
        GameStateRef->Achievements_UpdateDealtMoreThanOneToHQ(true);
    
        Label_321:
        FetchAllCardsWithEventTrigger(0x34, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_392:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = cardToReceiveDamage->cardID == CallFunc_Array_Get_Item->cardID;
    
        if (!EqualEqual_IntInt)
            goto Label_820;
    
        goto Label_746;
    
        Label_687:
        cardToReceiveDamage->OnReceiveDamage(cardToDealDamage, damageAmount);
    
        goto Label_74;
    
        Label_746:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_392;
    
        Label_820:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardReceiveDamage(cardToDealDamage, cardToReceiveDamage, isCombatDamage, damageAmount);
    
        return;
    
        Label_952:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void AdjustCardPositionInDeck(ESideEnum deckSide, int cardToAdjust, int positionFromTop, int& qqq)
    {
        GameStateRef->RemoveCardFromDeckBySide(deckSide, cardToAdjust, CallFunc_RemoveCardFromDeckBySide_removedIndex);
    
        GameStateRef->AddCardToDeckBySide(deckSide, cardToAdjust, false, positionFromTop);
    
        ExecuteOnAfterDeckChanged(deckSide);
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnAfterDeckChanged(ESideEnum deckSide)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_427;
    
        FetchAllCardsWithEventTrigger(0x3, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_109:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnAfterDeckChanged(deckSide);
    
        goto Label_353;
    
        Label_353:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_109;
    
        Label_427:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetAllCardsPlayedThisBattle(TArray<int>& playedCardsIDs)
    {
        Temp_int_Variable = 1;
    
        Label_28:
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        LessEqual_IntInt = (Temp_int_Variable <= CallFunc_GetTurnNumber_turnNumber);
    
        if (!LessEqual_IntInt)
            goto Label_529;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_154:
        GameStateRef->getCardsPlayedFromHandByTurn(Temp_int_Variable, CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed);
    
        Array_Length = CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_561;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->getCardsPlayedFromHandByTurn(Temp_int_Variable, CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed);
    
        CallFunc_Array_Get_Item = CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed[Temp_int_Array_Index_Variable];
    
        Array_AddUnique = localAllCardsPlayed.Add(CallFunc_Array_Get_Item);
    
        goto Label_635;
    
        Label_529:
        playedCardsIDs = localAllCardsPlayed;
    
        return;
    
        Label_561:
        Add_IntInt = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt;
    
        goto Label_28;
    
        Label_635:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt_1;
    
        goto Label_154;
    
        Label_709:
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void provideKeysAndFrameCount(int& key1, int& key2, int& frameCount)
    {
        GetFrameCount = UKismetSystemLibrary::GetFrameCount();
    
        Conv_Int64ToInt = ((int32)GetFrameCount);
    
        RandomIntegerInRangeFromStream = UKismetMathLibrary::RandomIntegerInRangeFromStream(encryptionStream, 10000, 1000000);
    
        key1 = RandomIntegerInRangeFromStream;
    
        key2 = encryptionKey2;
    
        frameCount = Conv_Int64ToInt;
    
        return;
    }

    // (Private, BlueprintCallable, BlueprintEvent)
    private void ReportTamperingToSever(FString reportReason)
    {
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger(reportReason, this);
    
        CardFunctionsNotifier->NotifyFatalHeartbeat();
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void AddCustomGameplayTag(struct FGameplayTag TagToAdd, int cardToAdd, int instigatorID, int& qqq)
    {
        IsGameplayTagValid = UBlueprintGameplayTagLibrary::IsGameplayTagValid(TagToAdd);
    
        if (!IsGameplayTagValid)
            return;
    
        GetTagName = UBlueprintGameplayTagLibrary::GetTagName(TagToAdd);
    
        Conv_NameToString = FString(GetTagName);
    
        ToLower = UKismetStringLibrary::ToLower(Conv_NameToString);
    
        CustomAbilityAdd(ToLower, cardToAdd, instigatorID, true, true, false, CallFunc_CustomAbilityAdd_qqq);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void RemoveCustomGameplayTag(struct FGameplayTag TagToRemove, int cardToRemove, int instigatorID, bool removeAll, int& qqq)
    {
        GetTagName = UBlueprintGameplayTagLibrary::GetTagName(TagToRemove);
    
        Conv_NameToString = FString(GetTagName);
    
        ToLower = UKismetStringLibrary::ToLower(Conv_NameToString);
    
        CustomAbilityRemove(ToLower, cardToRemove, instigatorID, removeAll, CallFunc_CustomAbilityRemove_qqq);
    
        if (!removeAll)
            return;
    
        GetCardFromID(cardToRemove, CallFunc_GetCardFromID_card);
    
        RemoveGameplayTag = UBlueprintGameplayTagLibrary::RemoveGameplayTag(CallFunc_GetCardFromID_card->GameplayTags, TagToRemove);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void MoveMultipleCardsToTopOfOwnersDeck(const TArray<int>*& cardIDs, int instigatorID, int positionFromTop, int& qqq)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Array_Length = cardIDs.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_296;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = cardIDs[Temp_int_Array_Index_Variable];
    
        MoveCardToTopOfDeck(CallFunc_Array_Get_Item, instigatorID, positionFromTop, true);
    
        goto Label_378;
    
        Label_296:
        CardFunctionsNotifier->NotifyMoveToDeckMultipleUnits(cardIDs, instigatorID);
    
        qqq = 0;
    
        return;
    
        Label_378:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_452:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnAfterAttackEvents(class UBaseCardObject* attacker, class UBaseCardObject* defender, int damageToDefenderFinal, bool afterShockAttack, int attackCost)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_714;
    
        if (!attacker->isSuppressed)
            goto Label_440;
    
        Label_74:
        FetchAllCardsWithEventTrigger(0x4, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_145:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_452;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->cardID == attacker->cardID;
    
        if (!EqualEqual_IntInt)
            goto Label_582;
    
        goto Label_508;
    
        Label_440:
        attacker->OnAfterAttack(defender, afterShockAttack, attackCost);
    
        goto Label_74;
    
        Label_508:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_145;
    
        Label_582:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnAfterOtherCardAttacks(defender, attacker, damageToDefenderFinal, attackCost);
    
        goto Label_709;
    
        Label_714:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnCardLocationMoved(int cardID, ECardLocationEnum oldLocation, ECardLocationEnum newLocation, bool changeOwner, CardMoveReason moveReason)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_853;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        cardToMove = CallFunc_GetCardFromID_card;
    
        if (!cardToMove->isSuppressed)
            goto Label_469;
    
        Label_125:
        FetchAllCardsWithEventTrigger(0x2F, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_196:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->cardID == cardID;
    
        if (!EqualEqual_IntInt)
            goto Label_666;
    
        goto Label_592;
    
        Label_469:
        GetEnumeratorUserFriendlyName = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UUserDefinedEnum>(nullptr, "kards/Content/Structs/CardMoveReason.CardMoveReason"), moveReason);
    
        cardToMove->OnCardLocationMoved(oldLocation, newLocation, changeOwner, GetEnumeratorUserFriendlyName);
    
        goto Label_125;
    
        Label_592:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_196;
    
        Label_666:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        GetEnumeratorUserFriendlyName_1 = UKismetNodeHelperLibrary::GetEnumeratorUserFriendlyName(FindObject<UUserDefinedEnum>(nullptr, "kards/Content/Structs/CardMoveReason.CardMoveReason"), moveReason);
    
        CallFunc_Array_Get_Item->OnOtherCardLocationMoved(cardToMove, oldLocation, newLocation, changeOwner, GetEnumeratorUserFriendlyName_1);
    
        return;
    
        Label_853:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnCardMoveFromFrontline(class UBaseCardObject* cardMoved)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_724;
    
        if (!cardMoved->isSuppressed)
            goto Label_348;
    
        Label_74:
        FetchAllCardsWithEventTrigger(0x31, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_145:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions)
            goto Label_463;
    
        return;
    
        Label_348:
        cardMoved->OnMoveFromFrontline();
    
        goto Label_74;
    
        Label_389:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_145;
    
        Label_463:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->cardID == cardMoved->cardID;
    
        if (!EqualEqual_IntInt)
            goto Label_619;
    
        goto Label_389;
    
        Label_619:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardMoveFromFrontline(cardMoved);
    
        return;
    
        Label_724:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnBeforeOtherCardDestroyed(int cardDestroyedID, int AttackerID, bool TriggerNotDestroyed, bool DestroyedInCombat)
    {
        GetCardFromID(cardDestroyedID, CallFunc_GetCardFromID_card);
    
        _cardDestroyed = CallFunc_GetCardFromID_card;
    
        GetCardFromID(AttackerID, CallFunc_GetCardFromID_card_1);
    
        _attacker = CallFunc_GetCardFromID_card_1;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_785;
    
        if (!_cardDestroyed->isSuppressed)
            goto Label_520;
    
        Label_176:
        FetchAllCardsWithEventTrigger(0xF, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_247:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = cardDestroyedID == CallFunc_Array_Get_Item->cardID;
    
        if (!EqualEqual_IntInt)
            goto Label_653;
    
        goto Label_579;
    
        Label_520:
        _cardDestroyed->OnBeforeDestroyed(_attacker, TriggerNotDestroyed);
    
        goto Label_176;
    
        Label_579:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_247;
    
        Label_653:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnBeforeOtherCardDestroyed(_cardDestroyed, _attacker, TriggerNotDestroyed, DestroyedInCombat);
    
        return;
    
        Label_785:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void UpdateFrontlineIfNeeded(int instigator)
    {
        Label_0:
        GameStateRef->GetFrontlineOwnerSide(CallFunc_GetFrontlineOwnerSide_ownerSide_1);
    
        oldFrontlineOwnerSide = CallFunc_GetFrontlineOwnerSide_ownerSide_1;
    
        FetchCardsByLocation(0x7, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        EqualEqual_IntInt = CallFunc_FetchCardsByLocation_QtyInLocation == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_262;
    
        UFunctionLibrary::EnumCompareSide(oldFrontlineOwnerSide, 0x0, CallFunc_EnumCompareSide_Branches_1);
    
        SwitchEnum_CmpSuccess_1 = ((!CallFunc_EnumCompareSide_Branches_1) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_979;
    
        goto Label_1096;
    
        Label_262:
        UFunctionLibrary::EnumCompareSide(oldFrontlineOwnerSide, CallFunc_FetchCardsByLocation_FirstCard->side, CallFunc_EnumCompareSide_Branches);
    
        SwitchEnum_CmpSuccess = ((!CallFunc_EnumCompareSide_Branches) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_367;
    
        return;
    
        Label_367:
        GameStateRef->UpdateFrontlineOwnerSide(CallFunc_FetchCardsByLocation_FirstCard->side);
    
        GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        EqualEqual_ByteByte = ((!CallFunc_FetchCardsByLocation_FirstCard->side) == (!CallFunc_GetClientSide_OutClientSide));
    
        if (!EqualEqual_ByteByte)
            goto Label_568;
    
        GameStateRef->Achievements_UpdateFrontlineCaptured(true);
    
        Label_568:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        FetchAllCardsWithEventTrigger(0x1B, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_672:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        GameStateRef->GetFrontlineOwnerSide(CallFunc_GetFrontlineOwnerSide_ownerSide);
    
        CallFunc_Array_Get_Item->OnFrontlineOwnershipChange(instigator, oldFrontlineOwnerSide, CallFunc_GetFrontlineOwnerSide_ownerSide);
    
        goto Label_1022;
    
        Label_979:
        GameStateRef->UpdateFrontlineOwnerSide(0x0);
    
        goto Label_568;
    
        Label_1022:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_672;
    
        Label_1096:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnDeploymentTriggered(class UBaseCardObject* cardTriggered, int instigatorID, int& triggerMultiple)
    {
        _triggerMultipleDeployment = 0;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_577;
    
        FetchAllCardsWithEventTrigger(0x17, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_132:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_471;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnDeploymentEffectTriggered(cardTriggered, instigatorID, CallFunc_OnDeploymentEffectTriggered_TriggerMultiple);
    
        Add_IntInt_1 = _triggerMultipleDeployment + CallFunc_OnDeploymentEffectTriggered_TriggerMultiple;
    
        _triggerMultipleDeployment = Add_IntInt_1;
    
        goto Label_503;
    
        Label_471:
        triggerMultiple = _triggerMultipleDeployment;
    
        return;
    
        Label_503:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_132;
    
        Label_577:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnDealDamageAddDamageAfterCalc(class UBaseCardObject* toCard, class UBaseCardObject* damageDealer, int damageAmount, bool isCombatDamage, bool isAttackingDamage, bool isRedirected, int& finalDamage)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1984;
    
        toCard->getHasImmune(CallFunc_getHasImmune_doesIt);
    
        if (!CallFunc_getHasImmune_doesIt)
            goto Label_121;
    
        finalDamage = 0;
    
        return;
    
        Label_121:
        if (!damageDealer->isSuppressed)
            goto Label_742;
    
        tmpDamage = damageAmount;
    
        Label_184:
        runAfter.Clear();
    
        FetchAllCardsWithEventTrigger(0x26, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_307:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        BooleanAND = Not_PreBool && Less_IntInt_1;
    
        if (!BooleanAND)
            goto Label_952;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        tmpCard = CallFunc_Array_Get_Item;
    
        EqualEqual_NameName = tmpCard->name == "card_event_national_fire_service";
    
        if (!EqualEqual_NameName)
            goto Label_1656;
    
        Array_Add = runAfter.Add(tmpCard);
    
        goto Label_1582;
    
        Label_742:
        damageDealer->OnDealDamageAddDamageAfterCalc(toCard, damageAmount, isCombatDamage, isAttackingDamage, isRedirected, CallFunc_OnDealDamageAddDamageAfterCalc_damageToAdd);
    
        Add_IntInt_4 = CallFunc_OnDealDamageAddDamageAfterCalc_damageToAdd + damageAmount;
    
        Max_3 = ((Add_IntInt_4 > 0) ? Add_IntInt_4 : 0);
    
        tmpDamage = Max_3;
    
        goto Label_184;
    
        Label_952:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_998:
        Array_Length_1 = runAfter.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_1508;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = runAfter[Temp_int_Array_Index_Variable];
    
        tmpCard = CallFunc_Array_Get_Item_1;
    
        tmpCard->OnOtherCardDealDamageAddDamageAfterCalc(damageDealer, toCard, tmpDamage, isCombatDamage, isRedirected, CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_damageToAdd, CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_stopAdding);
    
        Add_IntInt_1 = CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_damageToAdd + tmpDamage;
    
        Max_1 = ((Add_IntInt_1 > 0) ? Add_IntInt_1 : 0);
    
        tmpDamage = Max_1;
    
        goto Label_1434;
    
        Label_1434:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_998;
    
        Label_1508:
        Max = ((tmpDamage > 0) ? tmpDamage : 0);
    
        finalDamage = Max;
    
        return;
    
        Label_1582:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_2;
    
        goto Label_307;
    
        Label_1656:
        NotEqual_IntInt = (tmpCard->cardID !== damageDealer->cardID);
    
        if (!NotEqual_IntInt)
            return;
    
        tmpCard->OnOtherCardDealDamageAddDamageAfterCalc(damageDealer, toCard, tmpDamage, isCombatDamage, isRedirected, CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_damageToAdd_1, CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_stopAdding_1);
    
        Add_IntInt_3 = CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_damageToAdd_1 + tmpDamage;
    
        Max_2 = ((Add_IntInt_3 > 0) ? Add_IntInt_3 : 0);
    
        tmpDamage = Max_2;
    
        if (!CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_stopAdding_1)
            return;
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        return;
    
        Label_1984:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnDealDamageAddDamage(class UBaseCardObject* _damageDealerCard, class UBaseCardObject* _damageRecieverCard, int damage, bool _fromAttack, bool fromFight, bool _isDefenderDamage, int& calculatedDamage)
    {
        if (!_damageDealerCard->isSuppressed)
            goto Label_692;
    
        _dealerCalculatedDamage = damage;
    
        Label_68:
        addDamageToReRun.Clear();
    
        FetchAllCardsWithEventTrigger(0x25, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_180:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt_1)
            goto Label_805;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardDealDamageAddDamage(_damageDealerCard, _damageRecieverCard, _dealerCalculatedDamage, _fromAttack, _isDefenderDamage, CallFunc_OnOtherCardDealDamageAddDamage_damageToAdd_1, CallFunc_OnOtherCardDealDamageAddDamage_reRunAtEnd_1);
    
        Add_IntInt_2 = _dealerCalculatedDamage + CallFunc_OnOtherCardDealDamageAddDamage_damageToAdd_1;
    
        _dealerCalculatedDamage = Add_IntInt_2;
    
        if (!CallFunc_OnOtherCardDealDamageAddDamage_reRunAtEnd_1)
            goto Label_1379;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        Array_Add = addDamageToReRun.Add(CallFunc_Array_Get_Item);
    
        goto Label_1453;
    
        Label_692:
        _damageDealerCard->OnCardDealDamage_ModifyDamageDealt(_damageRecieverCard, damage, _fromAttack, fromFight, CallFunc_OnCardDealDamage_ModifyDamageDealt_newDamage);
    
        _dealerCalculatedDamage = CallFunc_OnCardDealDamage_ModifyDamageDealt_newDamage;
    
        goto Label_68;
    
        Label_805:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_851:
        Array_Length_1 = addDamageToReRun.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_1300;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = addDamageToReRun[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_1->OnOtherCardDealDamageAddDamage(_damageDealerCard, _damageRecieverCard, _dealerCalculatedDamage, _fromAttack, _isDefenderDamage, CallFunc_OnOtherCardDealDamageAddDamage_damageToAdd, CallFunc_OnOtherCardDealDamageAddDamage_reRunAtEnd);
    
        Add_IntInt_1 = CallFunc_OnOtherCardDealDamageAddDamage_damageToAdd + _dealerCalculatedDamage;
    
        _dealerCalculatedDamage = Add_IntInt_1;
    
        goto Label_1226;
    
        Label_1226:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_851;
    
        Label_1300:
        Clamp = ((_dealerCalculatedDamage < 0) ? 0 : ((_dealerCalculatedDamage > 99) ? 99 : _dealerCalculatedDamage));
    
        calculatedDamage = Clamp;
    
        return;
    
        Label_1379:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_3;
    
        goto Label_180;
    
        Label_1453:
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void CalculateDamageDealt(class UBaseCardObject* damageDealerCard, class UBaseCardObject* damageRecieverCard, bool damageDealerIsAttacker, bool ignoreAmbush, bool ignoreHeavyArmor, bool applyBeforeAttackBuffs, int& damage, bool& doesDamageRecieverDie, bool& damageRecieverKilledBeforeAattack, bool& wasShockAttack)
    {
        BeforeAttackDamage = 0;
    
        localDoesDamageRecieverDie = false;
    
        _damageDealerCard = damageDealerCard;
    
        _damageRecieverCard = damageRecieverCard;
    
        _dealingDamageIsAttacker = damageDealerIsAttacker;
    
        _ignoreAmbush = ignoreAmbush;
    
        _damageRecieverCard->getHasImmune(CallFunc_getHasImmune_doesIt_1);
    
        if (!CallFunc_getHasImmune_doesIt_1)
            goto Label_4013;
    
        damage = 0;
    
        doesDamageRecieverDie = false;
    
        damageRecieverKilledBeforeAattack = false;
    
        wasShockAttack = false;
    
        return;
    
        Label_271:
        Temp_int_Variable_1 = 0;
    
        Temp_bool_Variable_1 = applyBeforeAttackBuffs;
    
        Not_PreBool_4 = !_dealingDamageIsAttacker;
    
        _damageDealerCard->getTotalAttack(CallFunc_getTotalAttack_totalAttack_1);
    
        Add_IntInt_2 = CallFunc_getTotalAttack_totalAttack_1 + Temp_bool_Variable_1 ? AttackerBeforeAttackAttackBuff : Temp_int_Variable_1;
    
        ExecuteOnDealDamageAddDamage(_damageDealerCard, _damageRecieverCard, Add_IntInt_2, true, false, Not_PreBool_4, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage_2);
    
        _dealerCalculatedDamage = CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage_2;
    
        Temp_int_Variable = 0;
    
        Temp_bool_Variable = applyBeforeAttackBuffs;
    
        _damageRecieverCard->getTotalAttack(CallFunc_getTotalAttack_totalAttack);
    
        Add_IntInt_1 = CallFunc_getTotalAttack_totalAttack + Temp_bool_Variable ? DefenderBeforeAttackAttackBuff : Temp_int_Variable;
    
        ExecuteOnDealDamageAddDamage(_damageRecieverCard, _damageDealerCard, Add_IntInt_1, true, false, _dealingDamageIsAttacker, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage_1);
    
        _recieverCalculatedDamage = CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage_1;
    
        goto Label_271;
    
        Label_823:
        Not_PreBool_9 = !_ignoreAmbush;
    
        _damageRecieverCard->getHasAmbush(CallFunc_getHasAmbush_doesIt);
    
        BooleanAND_8 = CallFunc_getHasAmbush_doesIt && Not_PreBool_9;
    
        if (!BooleanAND_8)
            goto Label_823;
    
        _damageDealerCard->getHasImmune(CallFunc_getHasImmune_doesIt);
    
        Not_PreBool_5 = !CallFunc_getHasImmune_doesIt;
    
        Not_PreBool_6 = !damageRecieverCard->hasBeenAttackedThisTurn;
    
        BooleanAND_4 = _dealingDamageIsAttacker && Not_PreBool_6;
    
        BooleanAND_5 = BooleanAND_4 && Not_PreBool_5;
    
        if (!BooleanAND_5)
            goto Label_2034;
    
        _damageDealerCard->IsArtillery(CallFunc_IsArtillery_isIt_1);
    
        if (!CallFunc_IsArtillery_isIt_1)
            goto Label_1204;
    
        goto Label_2176;
    
        Label_1204:
        damageRecieverCard->IsAntiAir(CallFunc_IsAntiAir_isIt);
    
        _damageDealerCard->IsBomber(CallFunc_IsBomber_isIt);
    
        Not_PreBool_7 = !CallFunc_IsAntiAir_isIt;
    
        damageRecieverCard->IsFighter(CallFunc_IsFighter_isIt);
    
        Not_PreBool_8 = !CallFunc_IsFighter_isIt;
    
        BooleanAND_6 = CallFunc_IsBomber_isIt && Not_PreBool_8;
    
        BooleanAND_7 = BooleanAND_6 && Not_PreBool_7;
    
        if (!BooleanAND_7)
            goto Label_1476;
    
        goto Label_2318;
    
        Label_1476:
        _damageDealerCard->getHasShock(CallFunc_getHasShock_doesIt);
    
        _damageRecieverCard->IsBomber(CallFunc_IsBomber_isIt_3);
    
        BooleanOR_1 = (CallFunc_IsBomber_isIt_3 || CallFunc_getHasShock_doesIt);
    
        if (!BooleanOR_1)
            goto Label_1611;
    
        goto Label_2647;
    
        Label_1611:
        Temp_int_Variable_4 = 0;
    
        Temp_bool_Variable_4 = applyBeforeAttackBuffs;
    
        _damageDealerCard->GetPassiveDefenseBuff(CallFunc_GetPassiveDefenseBuff_amount_1);
    
        _damageDealerCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_2);
    
        _damageDealerCard->getTotalHeavyArmor(CallFunc_getTotalHeavyArmor_totalHeavyArmor_1);
    
        Add_IntInt_5 = CallFunc_getTotalDefense_totalDefense_2 + CallFunc_getTotalHeavyArmor_totalHeavyArmor_1;
    
        Add_IntInt_6 = Add_IntInt_5 + CallFunc_GetPassiveDefenseBuff_amount_1;
    
        Add_IntInt_7 = Add_IntInt_6 + Temp_bool_Variable_4 ? AttackerBeforeAttackDefenseBuff : Temp_int_Variable_4;
    
        GreaterEqual_IntInt_2 = (_recieverCalculatedDamage >= Add_IntInt_7);
    
        if (!GreaterEqual_IntInt_2)
            goto Label_2879;
    
        _dealerCalculatedDamage = 0;
    
        goto Label_3932;
    
        Label_2034:
        _damageRecieverCard->IsArtillery(CallFunc_IsArtillery_isIt);
    
        Not_PreBool_13 = !_dealingDamageIsAttacker;
    
        BooleanAND_12 = Not_PreBool_13 && CallFunc_IsArtillery_isIt;
    
        if (!BooleanAND_12)
            goto Label_4763;
    
        _dealerCalculatedDamage = 0;
    
        return;
    
        Label_2176:
        _damageDealerCard->IsBomber(CallFunc_IsBomber_isIt_2);
    
        Not_PreBool_12 = !_dealingDamageIsAttacker;
    
        BooleanAND_11 = Not_PreBool_12 && CallFunc_IsBomber_isIt_2;
    
        if (!BooleanAND_11)
            return;
    
        _dealerCalculatedDamage = 0;
    
        return;
    
        Label_2318:
        _damageDealerCard->IsAntiAir(CallFunc_IsAntiAir_isIt_1);
    
        _damageDealerCard->IsFighter(CallFunc_IsFighter_isIt_1);
    
        BooleanOR = (CallFunc_IsFighter_isIt_1 || CallFunc_IsAntiAir_isIt_1);
    
        Not_PreBool_10 = !BooleanOR;
    
        _damageRecieverCard->IsBomber(CallFunc_IsBomber_isIt_1);
    
        Not_PreBool_11 = !_dealingDamageIsAttacker;
    
        BooleanAND_9 = Not_PreBool_11 && CallFunc_IsBomber_isIt_1;
    
        BooleanAND_10 = BooleanAND_9 && Not_PreBool_10;
    
        if (!BooleanAND_10)
            return;
    
        _dealerCalculatedDamage = 0;
    
        return;
    
        Label_2647:
        _damageDealerCard->IsUnit(CallFunc_IsUnit_isIt);
    
        _damageRecieverCard->getHasShock(CallFunc_getHasShock_doesIt_1);
    
        Not_PreBool = !_dealingDamageIsAttacker;
    
        BooleanAND = Not_PreBool && CallFunc_getHasShock_doesIt_1;
    
        BooleanAND_1 = BooleanAND && CallFunc_IsUnit_isIt;
    
        if (!BooleanAND_1)
            return;
    
        _dealerCalculatedDamage = 0;
    
        shockAttack = true;
    
        return;
    
        Label_2879:
        Greater_IntInt_1 = (_dealerCalculatedDamage > 0);
    
        if (!Greater_IntInt_1)
            goto Label_3276;
    
        _damageRecieverCard->GetPassiveDefenseBuff(CallFunc_GetPassiveDefenseBuff_amount);
    
        _damageRecieverCard->getTotalHeavyArmor(CallFunc_getTotalHeavyArmor_totalHeavyArmor);
    
        SelectInt = (applyBeforeAttackBuffs ? CallFunc_GetPassiveDefenseBuff_amount : 0);
    
        SelectInt_1 = (ignoreHeavyArmor ? 0 : CallFunc_getTotalHeavyArmor_totalHeavyArmor);
    
        Add_IntInt_4 = SelectInt_1 + SelectInt;
    
        Subtract_IntInt = _dealerCalculatedDamage - Add_IntInt_4;
    
        Max = ((Subtract_IntInt > 0) ? Subtract_IntInt : 0);
    
        _dealerCalculatedDamage = Max;
    
        Label_3276:
        Temp_int_Variable_3 = 0;
    
        Temp_bool_Variable_3 = applyBeforeAttackBuffs;
    
        Add_IntInt = Temp_bool_Variable_3 ? BeforeAttackDamage : Temp_int_Variable_3 + _dealerCalculatedDamage;
    
        _dealerCalculatedDamage = Add_IntInt;
    
        Temp_int_Variable_2 = 0;
    
        Temp_bool_Variable_2 = applyBeforeAttackBuffs;
    
        _damageRecieverCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        Add_IntInt_3 = CallFunc_getTotalDefense_totalDefense_1 + Temp_bool_Variable_2 ? DefenderBeforeAttackDefenseBuff : Temp_int_Variable_2;
    
        GreaterEqual_IntInt_1 = (_dealerCalculatedDamage >= Add_IntInt_3);
    
        if (!GreaterEqual_IntInt_1)
            goto Label_3672;
    
        Label_3660:
        localDoesDamageRecieverDie = true;
    
        return;
    
        Label_3672:
        _damageDealerCard->HasCustomAbility("lethal", CallFunc_HasCustomAbility_doesIt);
    
        _damageRecieverCard->IsLocation(CallFunc_IsLocation_isIt);
    
        Not_PreBool_3 = !CallFunc_IsLocation_isIt;
    
        Greater_IntInt_2 = (_dealerCalculatedDamage > 0);
    
        BooleanAND_2 = Greater_IntInt_2 && Not_PreBool_3;
    
        BooleanAND_3 = BooleanAND_2 && CallFunc_HasCustomAbility_doesIt;
    
        if (!BooleanAND_3)
            goto Label_3920;
    
        goto Label_3660;
    
        Label_3920:
        localDoesDamageRecieverDie = false;
    
        return;
    
        Label_3932:
        damage = _dealerCalculatedDamage;
    
        doesDamageRecieverDie = localDoesDamageRecieverDie;
    
        damageRecieverKilledBeforeAattack = false;
    
        wasShockAttack = shockAttack;
    
        return;
    
        Label_4013:
        if (!applyBeforeAttackBuffs)
            return;
    
        _damageDealerCard->GetBeforeAttackAttackBuff(_dealingDamageIsAttacker, CallFunc_GetBeforeAttackAttackBuff_amount_1);
    
        AttackerBeforeAttackAttackBuff = CallFunc_GetBeforeAttackAttackBuff_amount_1;
    
        _damageDealerCard->GetBeforeAttackDefenseBuff(_dealingDamageIsAttacker, CallFunc_GetBeforeAttackDefenseBuff_amount_1);
    
        AttackerBeforeAttackDefenseBuff = CallFunc_GetBeforeAttackDefenseBuff_amount_1;
    
        Not_PreBool_2 = !_dealingDamageIsAttacker;
    
        damageRecieverCard->GetBeforeAttackAttackBuff(Not_PreBool_2, CallFunc_GetBeforeAttackAttackBuff_amount);
    
        DefenderBeforeAttackAttackBuff = CallFunc_GetBeforeAttackAttackBuff_amount;
    
        Not_PreBool_1 = !_dealingDamageIsAttacker;
    
        damageRecieverCard->GetBeforeAttackDefenseBuff(Not_PreBool_1, CallFunc_GetBeforeAttackDefenseBuff_amount);
    
        DefenderBeforeAttackDefenseBuff = CallFunc_GetBeforeAttackDefenseBuff_amount;
    
        _damageDealerCard->GetBeforeAttackDamage(_dealingDamageIsAttacker, CallFunc_GetBeforeAttackDamage_amount);
    
        BeforeAttackDamage = CallFunc_GetBeforeAttackDamage_amount;
    
        Greater_IntInt = (BeforeAttackDamage > 0);
    
        if (!Greater_IntInt)
            goto Label_4614;
    
        ExecuteOnDealDamageAddDamage(_damageDealerCard, _damageRecieverCard, BeforeAttackDamage, false, false, false, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage);
    
        BeforeAttackDamage = CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage;
    
        Label_4614:
        _damageRecieverCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        GreaterEqual_IntInt = (BeforeAttackDamage >= CallFunc_getTotalDefense_totalDefense);
    
        if (!GreaterEqual_IntInt)
            return;
    
        damage = BeforeAttackDamage;
    
        doesDamageRecieverDie = true;
    
        damageRecieverKilledBeforeAattack = true;
    
        wasShockAttack = false;
    
        Label_4763:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnCardDealDamageEffects(class UBaseCardObject* toCard, class UBaseCardObject* damageDealer, int damage, bool isCombatDamage, bool CounterDamage, bool isRedirected)
    {
        GetActiveGotchasOrdered(CallFunc_GetActiveGotchasOrdered_cardIDs);
    
        activeGotchasCardIDs = CallFunc_GetActiveGotchasOrdered_cardIDs;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_101:
        Array_Length_1 = activeGotchasCardIDs.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_308;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions_2);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions_2)
            goto Label_889;
    
        return;
    
        Label_308:
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions_1);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions_1)
            goto Label_372;
    
        return;
    
        Label_372:
        IsValid = damageDealer;
    
        if (!IsValid)
            goto Label_541;
    
        if (!damageDealer->isSuppressed)
            goto Label_1198;
    
        Label_451:
        Array_Add_1 = cardsDone.Add(damageDealer->cardID);
    
        Label_541:
        FetchAllCardsWithEventTrigger(0x24, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_612:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt)
            goto Label_815;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions)
            goto Label_1367;
    
        return;
    
        Label_815:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_101;
    
        Label_889:
        CallFunc_Array_Get_Item_1 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_1, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->OnOtherCardDealDamage(damageDealer, toCard, damage, isCombatDamage, CounterDamage, isRedirected);
    
        CallFunc_Array_Get_Item_1 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_1];
    
        Array_Add_2 = cardsDone.Add(CallFunc_Array_Get_Item_1);
    
        goto Label_1293;
    
        Label_1198:
        damageDealer->OnCardDealDamage(toCard, damage, isCombatDamage, CounterDamage, isRedirected, CallFunc_OnCardDealDamage_qqq);
    
        goto Label_451;
    
        Label_1293:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_612;
    
        Label_1367:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        Array_Contains = cardsDone[CallFunc_Array_Get_Item->cardID];
    
        if (!Array_Contains)
            goto Label_1523;
    
        goto Label_1822;
    
        Label_1523:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardDealDamage(damageDealer, toCard, damage, isCombatDamage, CounterDamage, isRedirected);
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        Array_Add = cardsDone.Add(CallFunc_Array_Get_Item->cardID);
    
        return;
    
        Label_1822:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnMoveToFrontlineCardEffects(class UBaseCardObject* cardMoved, bool forceMove, int moveCost)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_382;
    
        GameStateRef->SetStopFurtherActions(false);
    
        GetActiveGotchasOrdered(CallFunc_GetActiveGotchasOrdered_cardIDs);
    
        activeGotchasCardIDs = CallFunc_GetActiveGotchasOrdered_cardIDs;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_175:
        Array_Length_1 = activeGotchasCardIDs.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_387;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions_2);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions_2)
            goto Label_1177;
    
        return;
    
        Label_382:
        return;
    
        Label_387:
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions_1);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions_1)
            goto Label_451;
    
        return;
    
        Label_451:
        EqualEqual_ByteByte = ((!cardMoved->location) == (!0x7));
    
        if (!EqualEqual_ByteByte)
            goto Label_1103;
    
        if (!cardMoved->isSuppressed)
            goto Label_1044;
    
        Label_550:
        Array_Add_1 = cardsDone.Add(cardMoved->cardID);
    
        cardMoved->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_696;
    
        goto Label_1887;
    
        Label_696:
        FetchAllCardsWithEventTrigger(0x32, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_767:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions)
            goto Label_1459;
    
        return;
    
        Label_970:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_767;
    
        Label_1044:
        cardMoved->OnMoveToFrontline(forceMove, moveCost);
    
        goto Label_550;
    
        Label_1103:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_175;
    
        Label_1177:
        CallFunc_Array_Get_Item_1 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_1, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->OnOtherCardMoveToFrontline(cardMoved, forceMove, moveCost);
    
        CallFunc_Array_Get_Item_1 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_1];
    
        Array_Add_2 = cardsDone.Add(CallFunc_Array_Get_Item_1);
    
        goto Label_970;
    
        Label_1459:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        Array_Contains = cardsDone[CallFunc_Array_Get_Item->cardID];
    
        if (!Array_Contains)
            goto Label_1615;
    
        return;
    
        Label_1615:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardMoveToFrontline(cardMoved, forceMove, moveCost);
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        Array_Add = cardsDone.Add(CallFunc_Array_Get_Item->cardID);
    
        return;
    
        Label_1887:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnCardDestroyedFunction(int cardID, ECardLocationEnum location, int attackerCardID, TArray<int>*& allCardsGettingDestroyed, bool destroyedInCombat)
    {
        Greater_IntInt = (attackerCardID > 0);
    
        if (!Greater_IntInt)
            goto Label_1000;
    
        GetCardFromID(attackerCardID, CallFunc_GetCardFromID_card);
    
        localKiller = CallFunc_GetCardFromID_card;
    
        Label_104:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2757;
    
        GameStateRef->SetUnitDestroyedThisTurn(true);
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_1);
    
        localDestroyedCard = CallFunc_GetCardFromID_card_1;
    
        FetchAllCardsWithEventTrigger(0x18, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        localDestructionEffectTriggerCards = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1;
    
        Not_PreBool_1 = !localDestroyedCard->isSuppressed;
    
        localDestroyedCard->HasCustomAbilityFromCard("destruction", localDestroyedCard->cardID, CallFunc_HasCustomAbilityFromCard_doesIt);
    
        BooleanOR = (localDestroyedCard->hasDestruction || CallFunc_HasCustomAbilityFromCard_doesIt);
    
        localDestroyedCard->CustomName1HasAttribute("StopDestructionEffect", CallFunc_CustomName1HasAttribute_doesIt);
    
        Not_PreBool_2 = !CallFunc_CustomName1HasAttribute_doesIt;
    
        BooleanAND_3 = Not_PreBool_2 && BooleanOR;
    
        BooleanAND_4 = BooleanAND_3 && Not_PreBool_1;
    
        if (!BooleanAND_4)
            goto Label_1016;
    
        localDestroyedCard->OnDestroyed(localKiller, false);
    
        ExecuteOnDestructionEffectTriggered(localDestroyedCard, attackerCardID, allCardsGettingDestroyed, localDestructionEffectTriggerCards, false, CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_3);
    
        Greater_IntInt_2 = (CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_3 > 0);
    
        if (!Greater_IntInt_2)
            goto Label_2147;
    
        Temp_int_Variable = 1;
    
        Label_840:
        LessEqual_IntInt_1 = (Temp_int_Variable <= CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_3);
    
        if (!LessEqual_IntInt_1)
            goto Label_2636;
    
        localDestroyedCard->OnDestroyed(localKiller, true);
    
        ExecuteOnDestructionEffectTriggered(localDestroyedCard, attackerCardID, allCardsGettingDestroyed, localDestructionEffectTriggerCards, false, CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_2);
    
        goto Label_2683;
    
        Label_1000:
        localKiller = nullptr;
    
        goto Label_104;
    
        Label_1016:
        FetchAllCardsWithEventTrigger(0x27, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1087:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        localLoopCard = CallFunc_Array_Get_Item;
    
        localLoopCardID = localLoopCard->cardID;
    
        NotEqual_IntInt = (localLoopCardID !== cardID);
    
        if (!NotEqual_IntInt)
            goto Label_2073;
    
        Array_Contains_1 = allCardsGettingDestroyed[localLoopCardID];
    
        localLoopCard->OnOtherCardDestroyed(localDestroyedCard, localKiller, false, location, Array_Contains_1, destroyedInCombat);
    
        localDestroyedCard->HasCustomAbilityFromCard("destruction", localLoopCardID, CallFunc_HasCustomAbilityFromCard_doesIt_1);
    
        if (!CallFunc_HasCustomAbilityFromCard_doesIt_1)
            return;
    
        ExecuteOnDestructionEffectTriggered(localDestroyedCard, attackerCardID, allCardsGettingDestroyed, localDestructionEffectTriggerCards, true, CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_1);
    
        Greater_IntInt_1 = (CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_1 > 0);
    
        if (!Greater_IntInt_1)
            return;
    
        Temp_int_Variable_1 = 1;
    
        Label_1743:
        LessEqual_IntInt = (Temp_int_Variable_1 <= CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple_1);
    
        if (!LessEqual_IntInt)
            return;
    
        Array_Contains = allCardsGettingDestroyed[localLoopCardID];
    
        localLoopCard->OnOtherCardDestroyed(localDestroyedCard, localKiller, true, location, Array_Contains, destroyedInCombat);
    
        ExecuteOnDestructionEffectTriggered(localDestroyedCard, attackerCardID, allCardsGettingDestroyed, localDestructionEffectTriggerCards, false, CallFunc_ExecuteOnDestructionEffectTriggered_output_TriggerMultiple);
    
        goto Label_1999;
    
        Label_1999:
        Add_IntInt_2 = Temp_int_Variable_1 + 1;
    
        Temp_int_Variable_1 = Add_IntInt_2;
    
        goto Label_1743;
    
        Label_2073:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1087;
    
        Label_2147:
        localKiller->GetOppositeSide(CallFunc_GetOppositeSide_oppositeSide);
    
        localDestroyedCard->HasCustomAbility("cantBeSalvaged", CallFunc_HasCustomAbility_doesIt);
    
        EqualEqual_ByteByte = ((!localDestroyedCard->side) == (!CallFunc_GetOppositeSide_oppositeSide));
    
        Not_PreBool = !CallFunc_HasCustomAbility_doesIt;
    
        localKiller->IsSideActive(localKiller->side, CallFunc_IsSideActive_active);
    
        BooleanAND = localKiller->hasSalvage && CallFunc_IsSideActive_active;
    
        BooleanAND_1 = BooleanAND && EqualEqual_ByteByte;
    
        BooleanAND_2 = BooleanAND_1 && Not_PreBool;
    
        if (!BooleanAND_2)
            return;
    
        MakeArray_Array = [ cardID ];
    
        SalvageMultipleUnits(MakeArray_Array, localKiller->cardID, CallFunc_SalvageMultipleUnits_qqq);
    
        return;
    
        Label_2636:
        localDestroyedCard->OnAfterDestroyed(localKiller, false);
    
        return;
    
        Label_2683:
        Add_IntInt_1 = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt_1;
    
        goto Label_840;
    
        Label_2757:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ApplyDamageToMultipleCards(TArray<int>*& receiverIDs, int attackerID, int damage, TArray<int>& outputDestroyedCards)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_10673;
    
        GetCardFromID(attackerID, CallFunc_GetCardFromID_card_1);
    
        attackerCard = CallFunc_GetCardFromID_card_1;
    
        Temp_int_Loop_Counter_Variable_10 = 0;
    
        Temp_int_Array_Index_Variable_11 = 0;
    
        Label_135:
        Array_Length_17 = receiverIDs.Length;
    
        Less_IntInt_15 = (Temp_int_Loop_Counter_Variable_10 < Array_Length_17);
    
        if (!Less_IntInt_15)
            goto Label_600;
    
        Temp_int_Array_Index_Variable_11 = Temp_int_Loop_Counter_Variable_10;
    
        CallFunc_Array_Get_Item_21 = receiverIDs[Temp_int_Array_Index_Variable_11];
    
        GetCardFromID(CallFunc_Array_Get_Item_21, CallFunc_GetCardFromID_card_10);
    
        tmp_receiverCard = CallFunc_GetCardFromID_card_10;
    
        ExecuteOnDealDamageAddDamage(attackerCard, tmp_receiverCard, damage, false, false, false, CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage);
    
        Array_Add_2 = damageReceivedArr.Add(CallFunc_ExecuteOnDealDamageAddDamage_calculatedDamage);
    
        Array_Add_1 = locationArr.Add(tmp_receiverCard->location);
    
        goto Label_9143;
    
        Label_600:
        Temp_bool_True_if_break_was_hit_Variable_1 = false;
    
        Temp_int_Loop_Counter_Variable_4 = 0;
    
        Temp_int_Array_Index_Variable_4 = 0;
    
        Label_657:
        Not_PreBool_1 = !Temp_bool_True_if_break_was_hit_Variable_1;
    
        Array_Length_15 = receiverIDs.Length;
    
        Less_IntInt_12 = (Temp_int_Loop_Counter_Variable_4 < Array_Length_15);
    
        BooleanAND_2 = Not_PreBool_1 && Less_IntInt_12;
    
        if (!BooleanAND_2)
            goto Label_1811;
    
        Temp_int_Array_Index_Variable_4 = Temp_int_Loop_Counter_Variable_4;
    
        CallFunc_Array_Get_Item_19 = receiverIDs[Temp_int_Array_Index_Variable_4];
    
        GetCardFromID(CallFunc_Array_Get_Item_19, CallFunc_GetCardFromID_card_7);
    
        tmp_receiverCard = CallFunc_GetCardFromID_card_7;
    
        tmp_receiverCard->getHasImmune(CallFunc_getHasImmune_doesIt);
    
        Not_PreBool_2 = !CallFunc_getHasImmune_doesIt;
    
        if (!Not_PreBool_2)
            goto Label_9291;
    
        FetchAllCardsWithEventTrigger(0x26, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_8 = 0;
    
        Label_1143:
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        BooleanAND = Not_PreBool && Less_IntInt;
    
        if (!BooleanAND)
            goto Label_9217;
    
        Temp_int_Array_Index_Variable_8 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_8];
    
        CallFunc_Array_Get_Item_18 = damageReceivedArr[Temp_int_Array_Index_Variable_4];
    
        GetCardFromID(attackerID, CallFunc_GetCardFromID_card_8);
    
        CallFunc_Array_Get_Item->OnOtherCardDealDamageAddDamageAfterCalc(CallFunc_GetCardFromID_card_8, tmp_receiverCard, CallFunc_Array_Get_Item_18, false, false, CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_damageToAdd, CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_stopAdding);
    
        CallFunc_Array_Get_Item_18 = damageReceivedArr[Temp_int_Array_Index_Variable_4];
    
        Add_IntInt_15 = CallFunc_Array_Get_Item_18 + CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_damageToAdd;
    
        Max = ((Add_IntInt_15 > 0) ? Add_IntInt_15 : 0);
    
        Array_Set(damageReceivedArr, Temp_int_Array_Index_Variable_4, Max, false);
    
        if (!CallFunc_OnOtherCardDealDamageAddDamageAfterCalc_stopAdding)
            goto Label_9352;
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        return;
    
        Label_1811:
        Temp_int_Loop_Counter_Variable_5 = 0;
    
        Temp_int_Array_Index_Variable_3 = 0;
    
        Label_1857:
        Array_Length_9 = damageReceivedArr.Length;
    
        Less_IntInt_5 = (Temp_int_Loop_Counter_Variable_5 < Array_Length_9);
    
        if (!Less_IntInt_5)
            goto Label_2159;
    
        Temp_int_Array_Index_Variable_3 = Temp_int_Loop_Counter_Variable_5;
    
        CallFunc_Array_Get_Item_7 = damageReceivedArr[Temp_int_Array_Index_Variable_3];
    
        EqualEqual_IntInt_1 = CallFunc_Array_Get_Item_7 == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_9426;
    
        _indicesOfElementsToRemove[0] = Temp_int_Array_Index_Variable_3;
    
        return;
    
        Label_2159:
        Array_Length_6 = damageReceivedArr.Length;
    
        Array_Length_7 = _indicesOfElementsToRemove.Length;
    
        EqualEqual_IntInt = Array_Length_7 == Array_Length_6;
    
        if (!EqualEqual_IntInt)
            goto Label_2366;
    
        outputDestroyedCards = TArray<outputDestroyedCards>();
    
        return;
    
        Label_2366:
        Temp_int_Loop_Counter_Variable_8 = 0;
    
        Temp_int_Array_Index_Variable_6 = 0;
    
        Label_2412:
        Array_Length_8 = _indicesOfElementsToRemove.Length;
    
        Less_IntInt_4 = (Temp_int_Loop_Counter_Variable_8 < Array_Length_8);
    
        if (!Less_IntInt_4)
            goto Label_2774;
    
        Temp_int_Array_Index_Variable_6 = Temp_int_Loop_Counter_Variable_8;
    
        CallFunc_Array_Get_Item_6 = _indicesOfElementsToRemove[Temp_int_Array_Index_Variable_6];
    
        damageReceivedArr.Remove(CallFunc_Array_Get_Item_6);
    
        CallFunc_Array_Get_Item_6 = _indicesOfElementsToRemove[Temp_int_Array_Index_Variable_6];
    
        receiverIDs.Remove(CallFunc_Array_Get_Item_6);
    
        goto Label_9500;
    
        Label_2774:
        Temp_int_Loop_Counter_Variable_6 = 0;
    
        Temp_int_Array_Index_Variable_5 = 0;
    
        Label_2820:
        Array_Length_14 = receiverIDs.Length;
    
        Less_IntInt_11 = (Temp_int_Loop_Counter_Variable_6 < Array_Length_14);
    
        if (!Less_IntInt_11)
            goto Label_3278;
    
        Temp_int_Array_Index_Variable_5 = Temp_int_Loop_Counter_Variable_6;
    
        CallFunc_Array_Get_Item_14 = damageReceivedArr[Temp_int_Array_Index_Variable_5];
    
        Greater_IntInt_2 = (CallFunc_Array_Get_Item_14 > 0);
    
        if (!Greater_IntInt_2)
            goto Label_9574;
    
        CallFunc_Array_Get_Item_15 = receiverIDs[Temp_int_Array_Index_Variable_5];
    
        GetCardFromID(CallFunc_Array_Get_Item_15, CallFunc_GetCardFromID_card_5);
    
        tmp_receiverCard = CallFunc_GetCardFromID_card_5;
    
        CallFunc_Array_Get_Item_14 = damageReceivedArr[Temp_int_Array_Index_Variable_5];
    
        ExecuteBeforeReceiveDamage(tmp_receiverCard, attackerCard, CallFunc_Array_Get_Item_14, false);
    
        return;
    
        Label_3278:
        Temp_int_Loop_Counter_Variable_9 = 0;
    
        Temp_int_Array_Index_Variable_9 = 0;
    
        Label_3324:
        Array_Length_13 = receiverIDs.Length;
    
        Less_IntInt_10 = (Temp_int_Loop_Counter_Variable_9 < Array_Length_13);
    
        if (!Less_IntInt_10)
            goto Label_4495;
    
        Temp_int_Array_Index_Variable_9 = Temp_int_Loop_Counter_Variable_9;
    
        CallFunc_Array_Get_Item_13 = receiverIDs[Temp_int_Array_Index_Variable_9];
    
        GetCardFromID(CallFunc_Array_Get_Item_13, CallFunc_GetCardFromID_card_4);
    
        tmp_receiverCard = CallFunc_GetCardFromID_card_4;
    
        tmp_receiverCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        Array_Add_3 = OldDefenseArr.Add(CallFunc_getTotalDefense_totalDefense_1);
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        CallFunc_Array_Get_Item_12 = damageReceivedArr[Temp_int_Array_Index_Variable_9];
    
        tmp_receiverCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        Subtract_IntInt = CallFunc_getTotalDefense_totalDefense_1 - CallFunc_Array_Get_Item_12;
    
        tmp_receiverCard->setAndEncryptDefense(Subtract_IntInt, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        CallFunc_Array_Get_Item_12 = damageReceivedArr[Temp_int_Array_Index_Variable_9];
    
        CallFunc_Array_Get_Item_13 = receiverIDs[Temp_int_Array_Index_Variable_9];
    
        UpdateHQ_DamagedAmountThisTurnIfNeeded(CallFunc_Array_Get_Item_13, CallFunc_Array_Get_Item_12);
    
        tmp_receiverCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        LessEqual_IntInt = (CallFunc_getTotalDefense_totalDefense <= 0);
    
        Array_Add = receiverDestroyedArr.Add(LessEqual_IntInt);
    
        tmp_receiverCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        LessEqual_IntInt = (CallFunc_getTotalDefense_totalDefense <= 0);
    
        if (!LessEqual_IntInt)
            goto Label_9648;
    
        Map_Add(destroyedCards, tmp_receiverCard->cardID, tmp_receiverCard->location);
    
        Set_Add(affectedLocations, tmp_receiverCard->location);
    
        return;
    
        Label_4495:
        CardFunctionsNotifier->NotifyDamageMultipleCards(damage, attackerID, receiverIDs, damageReceivedArr, receiverDestroyedArr, locationArr, OldDefenseArr);
    
        Temp_int_Loop_Counter_Variable_15 = 0;
    
        Temp_int_Array_Index_Variable_15 = 0;
    
        Label_4640:
        Array_Length_2 = receiverIDs.Length;
    
        Less_IntInt_14 = (Temp_int_Loop_Counter_Variable_15 < Array_Length_2);
    
        if (!Less_IntInt_14)
            goto Label_4978;
    
        Temp_int_Array_Index_Variable_15 = Temp_int_Loop_Counter_Variable_15;
    
        CallFunc_Array_Get_Item_16 = damageReceivedArr[Temp_int_Array_Index_Variable_15];
    
        CallFunc_Array_Get_Item_17 = receiverIDs[Temp_int_Array_Index_Variable_15];
    
        GetCardFromID(CallFunc_Array_Get_Item_17, CallFunc_GetCardFromID_card_6);
    
        ExecuteOnCardDealDamageEffects(CallFunc_GetCardFromID_card_6, attackerCard, CallFunc_Array_Get_Item_16, false, false, false);
    
        goto Label_9722;
    
        Label_4978:
        CallFunc_Map_Keys_Keys_3 = [];
    
        Map_Keys(destroyedCards, CallFunc_Map_Keys_Keys_3);
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_5085:
        Array_Length_12 = CallFunc_Map_Keys_Keys_3.Length;
    
        Less_IntInt_9 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_12);
    
        if (!Less_IntInt_9)
            goto Label_5322;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_11 = CallFunc_Map_Keys_Keys_3[Temp_int_Array_Index_Variable_2];
    
        ExecuteOnBeforeOtherCardDestroyed(CallFunc_Array_Get_Item_11, attackerID, false, false);
    
        goto Label_9796;
    
        Label_5322:
        CallFunc_Map_Keys_Keys_4 = [];
    
        Map_Keys(destroyedCards, CallFunc_Map_Keys_Keys_4);
    
        Temp_int_Loop_Counter_Variable_7 = 0;
    
        Temp_int_Array_Index_Variable_7 = 0;
    
        Label_5429:
        Array_Length_16 = CallFunc_Map_Keys_Keys_4.Length;
    
        Less_IntInt_13 = (Temp_int_Loop_Counter_Variable_7 < Array_Length_16);
    
        if (!Less_IntInt_13)
            goto Label_5863;
    
        Temp_int_Array_Index_Variable_7 = Temp_int_Loop_Counter_Variable_7;
    
        CallFunc_Array_Get_Item_20 = CallFunc_Map_Keys_Keys_4[Temp_int_Array_Index_Variable_7];
    
        GetCardFromID(CallFunc_Array_Get_Item_20, CallFunc_GetCardFromID_card_9);
    
        tmp_receiverCard = CallFunc_GetCardFromID_card_9;
    
        NotEqual_ByteByte_1 = ((!tmp_receiverCard->location) !== (!0x8));
    
        if (!NotEqual_ByteByte_1)
            goto Label_9870;
    
        CallFunc_Array_Get_Item_20 = CallFunc_Map_Keys_Keys_4[Temp_int_Array_Index_Variable_7];
    
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(CallFunc_Array_Get_Item_20, 0x8, tmp_receiverCard->location, 0x1);
    
        return;
    
        Label_5863:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_5909:
        Array_Length_11 = receiverIDs.Length;
    
        Less_IntInt_7 = (Temp_int_Loop_Counter_Variable < Array_Length_11);
    
        if (!Less_IntInt_7)
            goto Label_6286;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_9 = receiverIDs[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_9, CallFunc_GetCardFromID_card_2);
    
        tmp_receiverCard = CallFunc_GetCardFromID_card_2;
    
        CallFunc_Array_Get_Item_8 = damageReceivedArr[Temp_int_Array_Index_Variable_1];
    
        CardFunctionsNotifier->NotifyOnCardDealDamage(tmp_receiverCard, CallFunc_Array_Get_Item_8, attackerID, false);
    
        goto Label_9944;
    
        Label_6286:
        CallFunc_Map_Keys_Keys_2 = [];
    
        Map_Keys(destroyedCards, CallFunc_Map_Keys_Keys_2);
    
        Temp_int_Loop_Counter_Variable_3 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_6393:
        Array_Length_10 = CallFunc_Map_Keys_Keys_2.Length;
    
        Less_IntInt_6 = (Temp_int_Loop_Counter_Variable_3 < Array_Length_10);
    
        if (!Less_IntInt_6)
            goto Label_6784;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_3;
    
        CallFunc_Array_Get_Item_10 = CallFunc_Map_Keys_Keys_2[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item_10, CallFunc_GetCardFromID_card_3);
    
        NotEqual_ByteByte = ((!CallFunc_GetCardFromID_card_3->location) !== (!0x8));
    
        if (!NotEqual_ByteByte)
            goto Label_10092;
    
        CallFunc_Array_Get_Item_10 = CallFunc_Map_Keys_Keys_2[Temp_int_Array_Index_Variable];
    
        SetCardLocationAndLocNumber(CallFunc_Array_Get_Item_10, 0x8, 0);
    
        goto Label_10018;
    
        Label_6784:
        GetClientSide(CallFunc_GetClientSide_OutClientSide_1);
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card_1, CallFunc_GetLocationCardBySide_locationCardID_1, CallFunc_GetClientSide_OutClientSide_1);
    
        CallFunc_GetLocationCardBySide_card_1->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt_1);
    
        if (!CallFunc_IsLocatedOnBoard_isIt_1)
            goto Label_10212;
    
        GetOpponentSide(CallFunc_GetOpponentSide_OutOpponentSide_1);
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card, CallFunc_GetLocationCardBySide_locationCardID, CallFunc_GetOpponentSide_OutOpponentSide_1);
    
        CallFunc_GetLocationCardBySide_card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            goto Label_10322;
    
        goto Label_7028;
    
        Label_7028:
        Map_Length = destroyedCards.Length;
    
        Greater_IntInt = (Map_Length > 0);
    
        if (!Greater_IntInt)
            goto Label_7160;
    
        RefreshLocationStatus(affectedLocations);
    
        return;
    
        Label_7160:
        CallFunc_Map_Keys_Keys = [];
    
        Map_Keys(destroyedCards, CallFunc_Map_Keys_Keys);
    
        Temp_int_Loop_Counter_Variable_14 = 0;
    
        Temp_int_Array_Index_Variable_14 = 0;
    
        Label_7267:
        Array_Length_1 = CallFunc_Map_Keys_Keys.Length;
    
        Less_IntInt_8 = (Temp_int_Loop_Counter_Variable_14 < Array_Length_1);
    
        if (!Less_IntInt_8)
            goto Label_7576;
    
        Temp_int_Array_Index_Variable_14 = Temp_int_Loop_Counter_Variable_14;
    
        CallFunc_Array_Get_Item_1 = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable_14];
    
        Map_Find = Map_Find(destroyedCards, CallFunc_Array_Get_Item_1, CallFunc_Map_Find_Value);
    
        ExecuteOnCardLocationMoved(CallFunc_Array_Get_Item_1, CallFunc_Map_Find_Value, 0x8, false, 0xA);
    
        goto Label_10377;
    
        Label_7576:
        CallFunc_Map_Keys_Keys_1 = [];
    
        Map_Keys(destroyedCards, CallFunc_Map_Keys_Keys_1);
    
        destroyedCardIDs = CallFunc_Map_Keys_Keys_1;
    
        Temp_int_Loop_Counter_Variable_13 = 0;
    
        Temp_int_Array_Index_Variable_13 = 0;
    
        Label_7710:
        Array_Length_4 = destroyedCardIDs.Length;
    
        Less_IntInt_3 = (Temp_int_Loop_Counter_Variable_13 < Array_Length_4);
    
        if (!Less_IntInt_3)
            goto Label_8066;
    
        Temp_int_Array_Index_Variable_13 = Temp_int_Loop_Counter_Variable_13;
    
        CallFunc_Array_Get_Item_3 = destroyedCardIDs[Temp_int_Array_Index_Variable_13];
    
        tmpDestroyedCardID = CallFunc_Array_Get_Item_3;
    
        Map_Find_2 = Map_Find(destroyedCards, tmpDestroyedCardID, CallFunc_Map_Find_Value_2);
    
        ExecuteOnAfterLeaveBoardOrOwnerEvents(tmpDestroyedCardID, 0x8, CallFunc_Map_Find_Value_2);
    
        tmpDestroyedCardID = 0;
    
        goto Label_10451;
    
        Label_8066:
        Temp_int_Loop_Counter_Variable_12 = 0;
    
        Temp_int_Array_Index_Variable_12 = 0;
    
        Label_8112:
        Array_Length_3 = destroyedCardIDs.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_12 < Array_Length_3);
    
        if (!Less_IntInt_1)
            goto Label_8435;
    
        Temp_int_Array_Index_Variable_12 = Temp_int_Loop_Counter_Variable_12;
    
        CallFunc_Array_Get_Item_2 = destroyedCardIDs[Temp_int_Array_Index_Variable_12];
    
        Map_Find_1 = Map_Find(destroyedCards, CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value_1);
    
        ExecuteOnCardDestroyedFunction(CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value_1, attackerID, destroyedCardIDs, false);
    
        goto Label_10525;
    
        Label_8435:
        Temp_int_Loop_Counter_Variable_11 = 0;
    
        Temp_int_Array_Index_Variable_10 = 0;
    
        Label_8481:
        Array_Length_5 = receiverIDs.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_11 < Array_Length_5);
    
        if (!Less_IntInt_2)
            goto Label_8996;
    
        Temp_int_Array_Index_Variable_10 = Temp_int_Loop_Counter_Variable_11;
    
        CallFunc_Array_Get_Item_4 = damageReceivedArr[Temp_int_Array_Index_Variable_10];
    
        Greater_IntInt_1 = (CallFunc_Array_Get_Item_4 > 0);
    
        CallFunc_Array_Get_Item_5 = receiverIDs[Temp_int_Array_Index_Variable_10];
    
        GetCardFromID(CallFunc_Array_Get_Item_5, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt_2);
    
        BooleanAND_1 = CallFunc_IsLocatedOnBoard_isIt_2 && Greater_IntInt_1;
    
        if (!BooleanAND_1)
            goto Label_10599;
    
        CallFunc_Array_Get_Item_5 = receiverIDs[Temp_int_Array_Index_Variable_10];
    
        RemoveMobilize(CallFunc_Array_Get_Item_5, 0, false, false, CallFunc_RemoveMobilize_qqq);
    
        return;
    
        Label_8996:
        Temp_byte_Variable = 0x7;
    
        Set_Contains = Set_Contains(affectedLocations, Temp_byte_Variable);
    
        if (!Set_Contains)
            goto Label_9111;
    
        UpdateFrontlineIfNeeded(0);
    
        return;
    
        Label_9111:
        outputDestroyedCards = destroyedCardIDs;
    
        return;
    
        Label_9143:
        Add_IntInt_10 = Temp_int_Loop_Counter_Variable_10 + 1;
    
        Temp_int_Loop_Counter_Variable_10 = Add_IntInt_10;
    
        goto Label_135;
    
        Label_9217:
        Add_IntInt_4 = Temp_int_Loop_Counter_Variable_4 + 1;
    
        Temp_int_Loop_Counter_Variable_4 = Add_IntInt_4;
    
        goto Label_657;
    
        Label_9291:
        Array_Set(damageReceivedArr, Temp_int_Array_Index_Variable_4, Temp_int_Variable, false);
    
        return;
    
        Label_9352:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_1143;
    
        Label_9426:
        Add_IntInt_6 = Temp_int_Loop_Counter_Variable_5 + 1;
    
        Temp_int_Loop_Counter_Variable_5 = Add_IntInt_6;
    
        goto Label_1857;
    
        Label_9500:
        Add_IntInt_9 = Temp_int_Loop_Counter_Variable_8 + 1;
    
        Temp_int_Loop_Counter_Variable_8 = Add_IntInt_9;
    
        goto Label_2412;
    
        Label_9574:
        Add_IntInt_5 = Temp_int_Loop_Counter_Variable_6 + 1;
    
        Temp_int_Loop_Counter_Variable_6 = Add_IntInt_5;
    
        goto Label_2820;
    
        Label_9648:
        Add_IntInt_8 = Temp_int_Loop_Counter_Variable_9 + 1;
    
        Temp_int_Loop_Counter_Variable_9 = Add_IntInt_8;
    
        goto Label_3324;
    
        Label_9722:
        Add_IntInt_16 = Temp_int_Loop_Counter_Variable_15 + 1;
    
        Temp_int_Loop_Counter_Variable_15 = Add_IntInt_16;
    
        goto Label_4640;
    
        Label_9796:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_5085;
    
        Label_9870:
        Add_IntInt_7 = Temp_int_Loop_Counter_Variable_7 + 1;
    
        Temp_int_Loop_Counter_Variable_7 = Add_IntInt_7;
    
        goto Label_5429;
    
        Label_9944:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_5909;
    
        Label_10018:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_3 + 1;
    
        Temp_int_Loop_Counter_Variable_3 = Add_IntInt_3;
    
        goto Label_6393;
    
        Label_10092:
        CallFunc_Array_Get_Item_10 = CallFunc_Map_Keys_Keys_2[Temp_int_Array_Index_Variable];
    
        Map_Remove = destroyedCards.Remove(CallFunc_Array_Get_Item_10);
    
        return;
    
        Label_10212:
        GetOpponentSide(CallFunc_GetOpponentSide_OutOpponentSide);
    
        winningSide = CallFunc_GetOpponentSide_OutOpponentSide;
    
        Label_10262:
        HQ_DestroyedEndMatch(winningSide);
    
        outputDestroyedCards = TArray<outputDestroyedCards>();
    
        return;
    
        Label_10322:
        GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        winningSide = CallFunc_GetClientSide_OutClientSide;
    
        goto Label_10262;
    
        Label_10377:
        Add_IntInt_14 = Temp_int_Loop_Counter_Variable_14 + 1;
    
        Temp_int_Loop_Counter_Variable_14 = Add_IntInt_14;
    
        goto Label_7267;
    
        Label_10451:
        Add_IntInt_13 = Temp_int_Loop_Counter_Variable_13 + 1;
    
        Temp_int_Loop_Counter_Variable_13 = Add_IntInt_13;
    
        goto Label_7710;
    
        Label_10525:
        Add_IntInt_12 = Temp_int_Loop_Counter_Variable_12 + 1;
    
        Temp_int_Loop_Counter_Variable_12 = Add_IntInt_12;
    
        goto Label_8112;
    
        Label_10599:
        Add_IntInt_11 = Temp_int_Loop_Counter_Variable_11 + 1;
    
        Temp_int_Loop_Counter_Variable_11 = Add_IntInt_11;
    
        goto Label_8481;
    
        Label_10673:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void ApplyDamageToCard(class UBaseCardObject* toCard, class UBaseCardObject* damageDealer, int damage, bool isRedirected, bool isFightDefenderDamage)
    {
        _isDestroyed = false;
    
        toCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_5);
    
        oldDefense = CallFunc_getTotalDefense_totalDefense_5;
    
        oldLocation = toCard->location;
    
        toCardID = toCard->cardID;
    
        damageDealerID = damageDealer->cardID;
    
        finalDamage = damage;
    
        goto Label_264;
    
        Label_264:
        Greater_IntInt_3 = (finalDamage > 0);
    
        if (!Greater_IntInt_3)
            goto Label_385;
    
        ExecuteBeforeReceiveDamage(toCard, damageDealer, finalDamage, false);
    
        goto Label_519;
    
        Label_385:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_985;
    
        CardFunctionsNotifier->NotifyDamageCard(toCardID, 0, damageDealerID, false, oldLocation, oldDefense, isRedirected, isFightDefenderDamage);
    
        return;
    
        Label_519:
        damageDealer->HasCustomAbility("excess", CallFunc_HasCustomAbility_doesIt);
    
        if (!CallFunc_HasCustomAbility_doesIt)
            goto Label_1304;
    
        damageDealer->IsUnit(CallFunc_IsUnit_isIt);
    
        if (!CallFunc_IsUnit_isIt)
            goto Label_634;
    
        goto Label_1540;
    
        Label_634:
        toCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_2);
    
        Greater_IntInt_1 = (finalDamage > CallFunc_getTotalDefense_totalDefense_2);
    
        toCard->IsUnit(CallFunc_IsUnit_isIt_1);
    
        BooleanAND = CallFunc_IsUnit_isIt_1 && Greater_IntInt_1;
    
        if (!BooleanAND)
            goto Label_1775;
    
        toCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        Subtract_IntInt = finalDamage - CallFunc_getTotalDefense_totalDefense_1;
    
        excessDamage = Subtract_IntInt;
    
        toCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        finalDamage = CallFunc_getTotalDefense_totalDefense;
    
        goto Label_1861;
    
        Label_985:
        toCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_3);
    
        oldDefense = CallFunc_getTotalDefense_totalDefense_3;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        toCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_6);
    
        Subtract_IntInt_1 = CallFunc_getTotalDefense_totalDefense_6 - finalDamage;
    
        toCard->setAndEncryptDefense(Subtract_IntInt_1, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        UpdateHQ_DamagedAmountThisTurnIfNeeded(toCard->cardID, finalDamage);
    
        goto Label_2309;
    
        Label_1304:
        toCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_4);
    
        LessEqual_IntInt = (CallFunc_getTotalDefense_totalDefense_4 <= 0);
    
        _isDestroyed = LessEqual_IntInt;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            return;
    
        CardFunctionsNotifier->NotifyDamageCard(toCardID, finalDamage, damageDealerID, _isDestroyed, oldLocation, oldDefense, isRedirected, isFightDefenderDamage);
    
        return;
    
        Label_1540:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_2);
    
        if (!CallFunc_IsActionProcess_ActionProcess_2)
            return;
    
        Greater_IntInt = (excessDamage > 0);
    
        if (!Greater_IntInt)
            return;
    
        damageDealer->GetOppositeSide(CallFunc_GetOppositeSide_oppositeSide);
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card, CallFunc_GetLocationCardBySide_locationCardID, CallFunc_GetOppositeSide_oppositeSide);
    
        DamageCard(CallFunc_GetLocationCardBySide_card, excessDamage, damageDealer->cardID, false, false, false, CallFunc_DamageCard_targetDestroyed);
    
        return;
    
        Label_1775:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_3);
    
        if (!CallFunc_IsActionProcess_ActionProcess_3)
            return;
    
        ExecuteOnCardDealDamageEffects(toCard, damageDealer, finalDamage, false, false, isRedirected);
    
        return;
    
        Label_1861:
        if (!_isDestroyed)
            goto Label_2193;
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card_1, CallFunc_GetLocationCardBySide_locationCardID_1, 0x1);
    
        EqualEqual_IntInt_1 = CallFunc_GetLocationCardBySide_locationCardID_1 == toCardID;
    
        if (!EqualEqual_IntInt_1)
            goto Label_2086;
    
        winningSide = 0x2;
    
        Label_1987:
        HQ_DestroyedEndMatch(winningSide);
    
        return;
    
        Label_2015:
        ExecuteOnBeforeOtherCardDestroyed(toCardID, damageDealerID, false, false);
    
        ApplyRemoveCardFromBoard(toCardID, damageDealerID, true, false, false, false);
    
        goto Label_2015;
    
        Label_2086:
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card_2, CallFunc_GetLocationCardBySide_locationCardID_2, 0x2);
    
        EqualEqual_IntInt = CallFunc_GetLocationCardBySide_locationCardID_2 == toCardID;
    
        if (!EqualEqual_IntInt)
            return;
    
        winningSide = 0x1;
    
        goto Label_1987;
    
        Label_2193:
        if (!toCard->hasMobilize)
            return;
    
        Greater_IntInt_2 = (finalDamage > 0);
    
        if (!Greater_IntInt_2)
            return;
    
        RemoveMobilize(toCardID, 0, false, false, CallFunc_RemoveMobilize_qqq);
    
        return;
    
        Label_2309:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ApplyMakeCardRetreat(TArray<class UBaseCardObject*>*& cards, int instigatorID)
    {
        Array_Length = cards.Length;
    
        Greater_IntInt = (Array_Length > 0);
    
        if (!Greater_IntInt)
            goto Label_1927;
    
        SortCardsByLocationNumber(cards, CallFunc_SortCardsByLocationNumber_sortedCards);
    
        sortedCards = CallFunc_SortCardsByLocationNumber_sortedCards;
    
        CallFunc_Array_Get_Item_1 = cards[0];
    
        GetSupportLineBySide_2 = UCombatHelperFunctions::GetSupportLineBySide(CallFunc_Array_Get_Item_1->side, this);
    
        FetchCardsByLocation(GetSupportLineBySide_2, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        tmpSupportlineCards = CallFunc_FetchCardsByLocation_AllCardsInLocation;
    
        GetNewLocationNumbers(sortedCards, tmpSupportlineCards, CallFunc_GetNewLocationNumbers_cardIdToLocationNumber);
    
        idToLocationNumber = CallFunc_GetNewLocationNumbers_cardIdToLocationNumber;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_495:
        Array_Length_2 = sortedCards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt)
            goto Label_2988;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_2 = sortedCards[Temp_int_Array_Index_Variable_1];
    
        IsValid = CallFunc_Array_Get_Item_2;
    
        if (!IsValid)
            goto Label_2012;
    
        CallFunc_Array_Get_Item_2 = sortedCards[Temp_int_Array_Index_Variable_1];
    
        tmpCard = CallFunc_Array_Get_Item_2;
    
        EqualEqual_ByteByte = ((!tmpCard->location) == (!0x7));
    
        EqualEqual_ByteByte_1 = ((!tmpCard->location) == (!0x6));
    
        EqualEqual_ByteByte_3 = ((!tmpCard->location) == (!0x5));
    
        BooleanOR = (EqualEqual_ByteByte_3 || EqualEqual_ByteByte_1);
    
        BooleanOR_1 = (BooleanOR || EqualEqual_ByteByte);
    
        if (!BooleanOR_1)
            goto Label_2086;
    
        tmpCardID = tmpCard->cardID;
    
        tmpOldLocation = tmpCard->location;
    
        GetClientSide(CallFunc_GetClientSide_OutClientSide_1);
    
        EqualEqual_ByteByte_4 = ((!CallFunc_GetClientSide_OutClientSide_1) == (!tmpCard->side));
    
        if (!EqualEqual_ByteByte_4)
            goto Label_2176;
    
        GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        GetSupportLineBySide_1 = UCombatHelperFunctions::GetSupportLineBySide(CallFunc_GetClientSide_OutClientSide, this);
    
        tmpSupplyLineLocation = GetSupportLineBySide_1;
    
        Label_1342:
        GetHandLocationBySide = UCombatHelperFunctions::GetHandLocationBySide(tmpCard->originalSide, this);
    
        tmpHandLocation = GetHandLocationBySide;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2269;
    
        if (!tmpCard->isSuppressed)
            goto Label_2854;
    
        Label_1502:
        FetchAllCardsWithEventTrigger(0x36, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1573:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_2269;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardRetreat(tmpCard, CallFunc_OnOtherCardRetreat_stopAction);
    
        if (!CallFunc_OnOtherCardRetreat_stopAction)
            goto Label_2914;
    
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("ON OTHER RETREAT STOP ACTION NOT IMPLEMENTED YET", this);
    
        return;
    
        Label_1927:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Calling make card retreat with an empty array", this);
    
        return;
    
        Label_2012:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_495;
    
        Label_2086:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Attempted retreat on card that is not on the board", this);
    
        return;
    
        Label_2176:
        GetOpponentSide(CallFunc_GetOpponentSide_OutOpponentSide);
    
        GetSupportLineBySide = UCombatHelperFunctions::GetSupportLineBySide(CallFunc_GetOpponentSide_OutOpponentSide, this);
    
        tmpSupplyLineLocation = GetSupportLineBySide;
    
        goto Label_1342;
    
        Label_2269:
        EqualEqual_ByteByte_2 = ((!tmpCard->location) == (!0x7));
    
        if (!EqualEqual_ByteByte_2)
            goto Label_2822;
    
        tmpNewLocation = tmpSupplyLineLocation;
    
        FetchCardsByLocation(tmpSupplyLineLocation, CallFunc_FetchCardsByLocation_QtyInLocation_1, CallFunc_FetchCardsByLocation_isLocationFull_1, CallFunc_FetchCardsByLocation_AllCardsInLocation_1, CallFunc_FetchCardsByLocation_FirstCard_1, CallFunc_FetchCardsByLocation_fetchedCardsIDs_1);
    
        Not_PreBool = !CallFunc_FetchCardsByLocation_isLocationFull_1;
    
        if (!Not_PreBool)
            goto Label_2771;
    
        Subtract_IntInt = tmpCard->movementLeft - 1;
    
        Max = ((Subtract_IntInt > 0) ? Subtract_IntInt : 0);
    
        tmpCard->movementLeft = Max;
    
        Map_Find = Map_Find(idToLocationNumber, tmpCardID, CallFunc_Map_Find_Value);
    
        CardLocationMoved(tmpCardID, instigatorID, tmpOldLocation, tmpNewLocation, CallFunc_Map_Find_Value, CallFunc_Map_Find_Value, 0x9, false, false);
    
        return;
    
        Label_2771:
        MoveCardFromBoardToOwnersHand(tmpCardID, instigatorID, tmpOldLocation, tmpHandLocation);
    
        return;
    
        Label_2822:
        tmpNewLocation = tmpHandLocation;
    
        goto Label_2771;
    
        Label_2854:
        tmpCard->OnBeforeRetreat(CallFunc_OnBeforeRetreat_stopAction);
    
        if (!CallFunc_OnBeforeRetreat_stopAction)
            goto Label_1502;
    
        return;
    
        Label_2914:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_1573;
    
        Label_2988:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void AttackCard(int attackerCardID, int*& defenderCardID, bool& success)
    {
        shockAttack = false;
    
        GetCardFromID(attackerCardID, CallFunc_GetCardFromID_card_1);
    
        _attackerCard = CallFunc_GetCardFromID_card_1;
    
        GetCardFromID(defenderCardID, CallFunc_GetCardFromID_card);
    
        _defenderCard = CallFunc_GetCardFromID_card;
    
        _attackerCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_5);
    
        _attackerDefensiveValue = CallFunc_getTotalDefense_totalDefense_5;
    
        _attackerCardName = _attackerCard->name;
    
        _defenderLocation = _defenderCard->location;
    
        _defenderCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_4);
    
        _defenderDefensiveValue = CallFunc_getTotalDefense_totalDefense_4;
    
        _defenderCardName = _defenderCard->name;
    
        Greater_IntInt = (_defenderCard->KreditsTax_AsEnemyTarget > 0);
    
        if (!Greater_IntInt)
            goto Label_4706;
    
        _attackerCard->getTotalOperationCost(CallFunc_getTotalOperationCost_totalOperationCost);
    
        Add_IntInt = _defenderCard->KreditsTax_AsEnemyTarget + CallFunc_getTotalOperationCost_totalOperationCost;
    
        costToPay = Add_IntInt;
    
        goto Label_643;
    
        Label_643:
        _attackerCard->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt_1);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt_1)
            goto Label_783;
    
        RevealCard(_attackerCard->cardID, _attackerCard->cardID, CallFunc_RevealCard_qqq_1);
    
        Label_783:
        _defenderCard->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_923;
    
        RevealCard(_defenderCard->cardID, _attackerCard->cardID, CallFunc_RevealCard_qqq);
    
        Label_923:
        _defenderCard->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        _attackerCard->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt_1);
    
        BooleanAND = CallFunc_IsLocatedOnBoard_isIt_1 && CallFunc_IsLocatedOnBoard_isIt;
    
        if (!BooleanAND)
            goto Label_4775;
    
        goto Label_1058;
    
        Label_1058:
        FetchAllCardsWithEventTrigger(0x1E, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2);
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_1140:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2.Length;
    
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        BooleanAND_1 = Not_PreBool && Less_IntInt_1;
    
        if (!BooleanAND_1)
            goto Label_1725;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_2 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2[Temp_int_Array_Index_Variable_2];
    
        CallFunc_Array_Get_Item_2->OnOtherCardAttackSwitchTarget(_attackerCard, _defenderCard, CallFunc_OnOtherCardAttackSwitchTarget_newDefender);
    
        NotEqual_ObjectObject_1 = (CallFunc_OnOtherCardAttackSwitchTarget_newDefender !== _defenderCard);
    
        if (!NotEqual_ObjectObject_1)
            goto Label_1651;
    
        _defenderCard = CallFunc_OnOtherCardAttackSwitchTarget_newDefender;
    
        defenderCardID = CallFunc_OnOtherCardAttackSwitchTarget_newDefender->cardID;
    
        _defenderLocation = _defenderCard->location;
    
        goto Label_1639;
    
        Label_1639:
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        goto Label_2764;
    
        Label_1651:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_2;
    
        goto Label_1140;
    
        Label_1725:
        GameStateRef->SetStopAttack(false);
    
        tmpAttackedAndStopped = false;
    
        FetchAllCardsWithEventTrigger(0x1F, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1844:
        Array_Length_2 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt)
            goto Label_2693;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        NotEqual_IntInt = (attackerCardID !== CallFunc_Array_Get_Item->cardID);
    
        if (!NotEqual_IntInt)
            goto Label_2619;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        if (!CallFunc_Array_Get_Item->skipCardMarkers)
            goto Label_2415;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardAttacks(_attackerCard, _defenderCard, CallFunc_OnOtherCardAttacks_stopAttack, CallFunc_OnOtherCardAttacks_AttackedAndStopped);
    
        if (!CallFunc_OnOtherCardAttacks_stopAttack)
            goto Label_2393;
    
        GameStateRef->SetStopAttack(true);
    
        Label_2393:
        if (!CallFunc_OnOtherCardAttacks_AttackedAndStopped)
            goto Label_2911;
    
        tmpAttackedAndStopped = true;
    
        goto Label_3688;
    
        Label_2415:
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardAttacks(_attackerCard, _defenderCard, CallFunc_OnOtherCardAttacks_stopAttack_1, CallFunc_OnOtherCardAttacks_AttackedAndStopped_1);
    
        if (!CallFunc_OnOtherCardAttacks_stopAttack_1)
            goto Label_2597;
    
        GameStateRef->SetStopAttack(true);
    
        Label_2597:
        if (!CallFunc_OnOtherCardAttacks_AttackedAndStopped_1)
            goto Label_4690;
    
        tmpAttackedAndStopped = true;
    
        goto Label_4786;
    
        Label_2619:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt_1;
    
        goto Label_1844;
    
        Label_2693:
        GameStateRef->GetStopAttack(CallFunc_GetStopAttack_stopAttack);
    
        if (!CallFunc_GetStopAttack_stopAttack)
            return;
    
        success = true;
    
        return;
    
        Label_2764:
        Multiply_IntInt = (costToPay * -1);
    
        ChangeKreditsBySide(_attackerCard->side, Multiply_IntInt, 0);
    
        GameStateRef->addOperationKreditsSpentThisTurn(costToPay);
    
        return;
    
        Label_2911:
        _attackerCard->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt_2);
    
        if (!CallFunc_IsLocatedOnBoard_isIt_2)
            goto Label_3640;
    
        if (!_attackerCard->isSuppressed)
            goto Label_3590;
    
        Label_3002:
        FetchAllCardsWithEventTrigger(0xD, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_3073:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_2 < Array_Length);
    
        if (!Less_IntInt_2)
            goto Label_3511;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        NotEqual_ObjectObject = (CallFunc_Array_Get_Item_1 !== _attackerCard);
    
        if (!NotEqual_ObjectObject)
            goto Label_3437;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_1->OnBeforeOtherCardAttacks(_attackerCard, _defenderCard);
    
        return;
    
        Label_3437:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_3;
    
        goto Label_3073;
    
        Label_3511:
        _attackerCard->cardFunction->RemoveSmokescreen(attackerCardID, attackerCardID, true, false);
    
        return;
    
        Label_3590:
        _attackerCard->OnBeforeAttack(_defenderCard);
    
        goto Label_3002;
    
        Label_3640:
        ExecuteOnOperationKreditsSpent(_attackerCard, costToPay);
    
        success = true;
    
        return;
    
        Label_3688:
        if (!tmpAttackedAndStopped)
            goto Label_3807;
    
        _defenderCard = nullptr;
    
        damageToDefenderFinal = 0;
    
        ExecuteStoppedAttack(_attackerCard);
    
        Label_3759:
        ExecuteOnOperationKreditsSpent(_attackerCard, costToPay);
    
        success = true;
    
        return;
    
        Label_3807:
        CalculateDamageDealt(_attackerCard, _defenderCard, true, false, false, false, CallFunc_CalculateDamageDealt_damage, CallFunc_CalculateDamageDealt_doesDamageRecieverDie, CallFunc_CalculateDamageDealt_damageRecieverKilledBeforeAattack, CallFunc_CalculateDamageDealt_wasShockAttack);
    
        _damageDealtByAttacker = CallFunc_CalculateDamageDealt_damage;
    
        _defenderCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_3);
    
        GreaterEqual_IntInt_3 = (_damageDealtByAttacker >= CallFunc_getTotalDefense_totalDefense_3);
    
        _defenderDestroyed = GreaterEqual_IntInt_3;
    
        CalculateDamageDealt(_defenderCard, _attackerCard, false, false, false, false, CallFunc_CalculateDamageDealt_damage_1, CallFunc_CalculateDamageDealt_doesDamageRecieverDie_1, CallFunc_CalculateDamageDealt_damageRecieverKilledBeforeAattack_1, CallFunc_CalculateDamageDealt_wasShockAttack_1);
    
        shockAttack = CallFunc_CalculateDamageDealt_wasShockAttack_1;
    
        _damageDealtByDefender = CallFunc_CalculateDamageDealt_damage_1;
    
        _attackerCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_2);
    
        GreaterEqual_IntInt_2 = (_damageDealtByDefender >= CallFunc_getTotalDefense_totalDefense_2);
    
        _attackerDestroyed = GreaterEqual_IntInt_2;
    
        ExecuteOnDealDamageAddDamageAfterCalc(_defenderCard, _attackerCard, _damageDealtByAttacker, true, true, false, CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage_1);
    
        damageToDefenderFinal = CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage_1;
    
        _defenderCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        GreaterEqual_IntInt_1 = (damageToDefenderFinal >= CallFunc_getTotalDefense_totalDefense_1);
    
        defenderDestroyedFinal = GreaterEqual_IntInt_1;
    
        ExecuteOnDealDamageAddDamageAfterCalc(_attackerCard, _defenderCard, _damageDealtByDefender, true, false, false, CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage);
    
        damageToAttackerFinal = CallFunc_ExecuteOnDealDamageAddDamageAfterCalc_finalDamage;
    
        _attackerCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        GreaterEqual_IntInt = (damageToAttackerFinal >= CallFunc_getTotalDefense_totalDefense);
    
        attackerDestroyedFinal = GreaterEqual_IntInt;
    
        ExecuteAttackCard(_attackerCard, _defenderCard, damageToAttackerFinal, damageToDefenderFinal);
    
        ExecuteOnAfterAttackEvents(_attackerCard, _defenderCard, damageToDefenderFinal, shockAttack, costToPay);
    
        goto Label_3759;
    
        Label_4690:
        success = true;
    
        return;
    
        Label_4706:
        _attackerCard->getTotalOperationCost(CallFunc_getTotalOperationCost_totalOperationCost_1);
    
        costToPay = CallFunc_getTotalOperationCost_totalOperationCost_1;
    
        return;
    
        Label_4775:
        success = false;
    
        Label_4786:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteAttackCard(class UBaseCardObject* attacker, class UBaseCardObject* defender, int damageToAttacker, int damageToDefender)
    {
        attackerCardID = attacker->cardID;
    
        attackerOldLocation = attacker->location;
    
        defenderCardID = defender->cardID;
    
        defenderOldLocation = defender->location;
    
        finalDamageToDefender = damageToDefender;
    
        goto Label_279;
    
        Label_279:
        SetAttackerHasAttacked(attacker);
    
        defender->hasBeenAttackedThisTurn = true;
    
        defender->IsLocation(CallFunc_IsLocation_isIt);
    
        Not_PreBool = !CallFunc_IsLocation_isIt;
    
        attacker->HasCustomAbility("CantLoseShock", CallFunc_HasCustomAbility_doesIt);
    
        Not_PreBool_1 = !CallFunc_HasCustomAbility_doesIt;
    
        attacker->getHasShock(CallFunc_getHasShock_doesIt);
    
        BooleanAND = CallFunc_getHasShock_doesIt && Not_PreBool_1;
    
        BooleanAND_1 = BooleanAND && Not_PreBool;
    
        if (!BooleanAND_1)
            goto Label_716;
    
        RemoveShock(attacker->cardID, attacker->cardID, true, false, CallFunc_RemoveShock_qqq);
    
        wasShockAttack = true;
    
        goto Label_1104;
    
        Label_716:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1241;
    
        Greater_IntInt_1 = (finalDamageToDefender > 0);
    
        Not_PreBool_3 = !defender->isSuppressed;
    
        BooleanAND_3 = Greater_IntInt_1 && Not_PreBool_3;
    
        if (!BooleanAND_3)
            goto Label_928;
    
        ExecuteBeforeReceiveDamage(defender, attacker, finalDamageToDefender, true);
    
        Label_928:
        Not_PreBool_2 = !attacker->isSuppressed;
    
        Greater_IntInt_9 = (damageToAttacker > 0);
    
        BooleanAND_8 = Greater_IntInt_9 && Not_PreBool_2;
    
        if (!BooleanAND_8)
            goto Label_1651;
    
        ExecuteBeforeReceiveDamage(attacker, defender, damageToAttacker, true);
    
        goto Label_2712;
    
        Label_1104:
        attacker->getTotalDefense(CallFunc_getTotalDefense_totalDefense_4);
    
        attackerOldDefense = CallFunc_getTotalDefense_totalDefense_4;
    
        defender->getTotalDefense(CallFunc_getTotalDefense_totalDefense_3);
    
        defenderOldDefense = CallFunc_getTotalDefense_totalDefense_3;
    
        goto Label_2881;
    
        Label_1241:
        attacker->HasCustomAbility("excess", CallFunc_HasCustomAbility_doesIt_1);
    
        if (!CallFunc_HasCustomAbility_doesIt_1)
            goto Label_3097;
    
        defender->getTotalDefense(CallFunc_getTotalDefense_totalDefense_2);
    
        defender->IsUnit(CallFunc_IsUnit_isIt);
    
        Greater_IntInt_5 = (finalDamageToDefender > CallFunc_getTotalDefense_totalDefense_2);
    
        BooleanAND_2 = CallFunc_IsUnit_isIt && Greater_IntInt_5;
    
        if (!BooleanAND_2)
            goto Label_3282;
    
        defender->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        Subtract_IntInt = finalDamageToDefender - CallFunc_getTotalDefense_totalDefense;
    
        ExcessDamage = Subtract_IntInt;
    
        defender->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        finalDamageToDefender = CallFunc_getTotalDefense_totalDefense_1;
    
        goto Label_3496;
    
        Label_1651:
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        defender->getTotalDefense(CallFunc_getTotalDefense_totalDefense_8);
    
        Subtract_IntInt_2 = CallFunc_getTotalDefense_totalDefense_8 - finalDamageToDefender;
    
        defender->setAndEncryptDefense(Subtract_IntInt_2, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        Greater_IntInt_4 = (finalDamageToDefender > 0);
    
        defender->IsLocation(CallFunc_IsLocation_isIt_1);
    
        Not_PreBool_4 = !CallFunc_IsLocation_isIt_1;
    
        attacker->HasCustomAbility("lethal", CallFunc_HasCustomAbility_doesIt_3);
    
        BooleanAND_5 = Greater_IntInt_4 && CallFunc_HasCustomAbility_doesIt_3;
    
        BooleanAND_6 = BooleanAND_5 && Not_PreBool_4;
    
        defender->getTotalDefense(CallFunc_getTotalDefense_totalDefense_7);
    
        LessEqual_IntInt_1 = (CallFunc_getTotalDefense_totalDefense_7 <= 0);
    
        BooleanOR_1 = (LessEqual_IntInt_1 || BooleanAND_6);
    
        defenderDestroyed = BooleanOR_1;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        attacker->getTotalDefense(CallFunc_getTotalDefense_totalDefense_6);
    
        Subtract_IntInt_1 = CallFunc_getTotalDefense_totalDefense_6 - damageToAttacker;
    
        attacker->setAndEncryptDefense(Subtract_IntInt_1, CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        Greater_IntInt_6 = (damageToAttacker > 0);
    
        defender->HasCustomAbility("lethal", CallFunc_HasCustomAbility_doesIt_2);
    
        BooleanAND_4 = Greater_IntInt_6 && CallFunc_HasCustomAbility_doesIt_2;
    
        attacker->getTotalDefense(CallFunc_getTotalDefense_totalDefense_5);
    
        LessEqual_IntInt = (CallFunc_getTotalDefense_totalDefense_5 <= 0);
    
        BooleanOR = (LessEqual_IntInt || BooleanAND_4);
    
        attackerDestroyed = BooleanOR;
    
        UpdateHQ_DamagedAmountThisTurnIfNeeded(defender->cardID, finalDamageToDefender);
    
        goto Label_4791;
    
        Label_2712:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            return;
    
        CardFunctionsNotifier->NotifyAttackCard(attackerCardID, defenderCardID, damageToAttacker, finalDamageToDefender, attackerDestroyed, defenderDestroyed, attackerOldLocation, defenderOldLocation, attackerOldDefense, defenderOldDefense, wasShockAttack);
    
        return;
    
        Label_2881:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_2);
    
        if (!CallFunc_IsActionProcess_ActionProcess_2)
            return;
    
        Greater_IntInt = (ExcessDamage > 0);
    
        if (!Greater_IntInt)
            return;
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card, CallFunc_GetLocationCardBySide_locationCardID, defender->side);
    
        DamageCard(CallFunc_GetLocationCardBySide_card, ExcessDamage, attacker->cardID, false, false, false, CallFunc_DamageCard_targetDestroyed);
    
        return;
    
        Label_3097:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_3);
    
        if (!CallFunc_IsActionProcess_ActionProcess_3)
            return;
    
        defender->IsUnit(CallFunc_IsUnit_isIt_1);
    
        if (!CallFunc_IsUnit_isIt_1)
            return;
    
        if (!attackerDestroyed)
            goto Label_3201;
    
        goto Label_3234;
    
        Label_3201:
        ExecuteOnSurvivedCombatEvents(attacker, defender);
    
        return;
    
        Label_3234:
        if (!defenderDestroyed)
            goto Label_3249;
    
        return;
    
        Label_3249:
        ExecuteOnSurvivedCombatEvents(defender, attacker);
    
        return;
    
        Label_3282:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_4);
    
        if (!CallFunc_IsActionProcess_ActionProcess_4)
            return;
    
        Greater_IntInt_3 = (finalDamageToDefender > 0);
    
        if (!Greater_IntInt_3)
            goto Label_3407;
    
        ExecuteOnCardDealDamageEffects(defender, attacker, finalDamageToDefender, true, false, false);
    
        Label_3407:
        Greater_IntInt_8 = (damageToAttacker > 0);
    
        if (!Greater_IntInt_8)
            return;
    
        ExecuteOnCardDealDamageEffects(attacker, defender, damageToAttacker, true, true, false);
    
        return;
    
        Label_3496:
        if (!defenderDestroyed)
            goto Label_3762;
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card_1, CallFunc_GetLocationCardBySide_locationCardID_1, 0x1);
    
        EqualEqual_IntInt = CallFunc_GetLocationCardBySide_locationCardID_1 == defenderCardID;
    
        if (!EqualEqual_IntInt)
            goto Label_3655;
    
        winningSide = 0x2;
    
        Label_3627:
        HQ_DestroyedEndMatch(winningSide);
    
        return;
    
        Label_3655:
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card_2, CallFunc_GetLocationCardBySide_locationCardID_2, 0x2);
    
        EqualEqual_IntInt_1 = CallFunc_GetLocationCardBySide_locationCardID_2 == defenderCardID;
    
        if (!EqualEqual_IntInt_1)
            goto Label_4660;
    
        winningSide = 0x1;
    
        goto Label_3627;
    
        Label_3762:
        if (!defender->hasMobilize)
            goto Label_3878;
    
        Greater_IntInt_2 = (finalDamageToDefender > 0);
    
        if (!Greater_IntInt_2)
            return;
    
        RemoveMobilize(defenderCardID, 0, false, false, CallFunc_RemoveMobilize_qqq_1);
    
        return;
    
        Label_3878:
        BooleanAND_7 = attackerDestroyed && defenderDestroyed;
    
        if (!BooleanAND_7)
            goto Label_4494;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_5);
    
        if (!CallFunc_IsActionProcess_ActionProcess_5)
            goto Label_4151;
    
        ExecuteOnBeforeOtherCardDestroyed(defenderCardID, attackerCardID, false, true);
    
        ExecuteOnBeforeOtherCardDestroyed(attackerCardID, defenderCardID, false, true);
    
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(defenderCardID, 0x8, defender->location, 0x1);
    
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(attackerCardID, 0x8, attacker->location, 0x1);
    
        Label_4151:
        CardLocationMoved(defenderCardID, attackerCardID, defenderOldLocation, 0x8, 0, 0, 0xA, true, false);
    
        CardLocationMoved(attackerCardID, defenderCardID, attackerOldLocation, 0x8, 0, 0, 0xA, true, false);
    
        ExecuteOnAfterLeaveBoardOrOwnerEvents(defenderCardID, 0x8, defenderOldLocation);
    
        ExecuteOnAfterLeaveBoardOrOwnerEvents(attackerCardID, 0x8, attackerOldLocation);
    
        MakeArray_Array_1 = [ defenderCardID, attackerCardID ];
    
        ExecuteOnCardDestroyedFunction(defenderCardID, defenderOldLocation, attackerCardID, MakeArray_Array_1, true);
    
        MakeArray_Array = [ attackerCardID, defenderCardID ];
    
        ExecuteOnCardDestroyedFunction(attackerCardID, attackerOldLocation, defenderCardID, MakeArray_Array, true);
    
        return;
    
        Label_4494:
        if (!attackerDestroyed)
            goto Label_4579;
    
        ExecuteOnBeforeOtherCardDestroyed(attackerCardID, defenderCardID, false, true);
    
        ApplyRemoveCardFromBoard(attackerCardID, defenderCardID, true, true, false, false);
    
        return;
    
        Label_4579:
        if (!defenderDestroyed)
            return;
    
        ExecuteOnBeforeOtherCardDestroyed(defenderCardID, attackerCardID, false, true);
    
        ApplyRemoveCardFromBoard(defenderCardID, attackerCardID, true, true, false, false);
    
        return;
    
        Label_4660:
        if (!attackerDestroyed)
            goto Label_4675;
    
        return;
    
        Label_4675:
        if (!attacker->hasMobilize)
            return;
    
        Greater_IntInt_7 = (damageToAttacker > 0);
    
        if (!Greater_IntInt_7)
            return;
    
        RemoveMobilize(attackerCardID, 0, false, false, CallFunc_RemoveMobilize_qqq);
    
        return;
    
        Label_4791:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void SetAttackerHasAttacked(class UBaseCardObject* attacker)
    {
        attacker->CanMoveAndAttackInTheSameTurn(CallFunc_CanMoveAndAttackInTheSameTurn_canIt);
    
        if (!CallFunc_CanMoveAndAttackInTheSameTurn_canIt)
            goto Label_379;
    
        Label_55:
        Subtract_IntInt = attacker->attackLeft - 1;
    
        attacker->attackLeft = Subtract_IntInt;
    
        attacker->hasEverAttacked = true;
    
        attacker->hasAttackedThisTurn = true;
    
        Add_IntInt = attacker->attackCountThisTurn + 1;
    
        Temp_int_Variable = Add_IntInt;
    
        attacker->attackCountThisTurn = Temp_int_Variable;
    
        return;
    
        Label_379:
        Subtract_IntInt_1 = attacker->movementLeft - 1;
    
        attacker->movementLeft = Subtract_IntInt_1;
    
        goto Label_55;
    
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void ExecuteStoppedAttack(class UBaseCardObject* attacker)
    {
        SetAttackerHasAttacked(attacker);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        attacker->OnAttackStopped();
    
        CardFunctionsNotifier->NotifyStoppedAttack(attacker->cardID);
    
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void MoveCardToFrontline(int cardID, int instigatorID, ECardLocationEnum oldLocation, ECardLocationEnum newLocation, int newLocationNumber, int newNonVisualLocationNumber, bool force)
    {
        movementCost = 0;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_81;
    
        if (!force)
            goto Label_568;
    
        goto Label_761;
    
        Label_81:
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_1);
    
        tmpCardToMove = CallFunc_GetCardFromID_card_1;
    
        Temp_byte_Variable = 0x1;
    
        Temp_byte_Variable_1 = 0x0;
    
        Temp_bool_Variable = force;
    
        CardLocationMoved(cardID, instigatorID, oldLocation, newLocation, newLocationNumber, newNonVisualLocationNumber, Temp_bool_Variable ? Temp_byte_Variable : Temp_byte_Variable_1, false, false);
    
        goto Label_320;
    
        Label_320:
        tmpCardToMove->CanMoveAndAttackInTheSameTurn(CallFunc_CanMoveAndAttackInTheSameTurn_canIt);
    
        if (!CallFunc_CanMoveAndAttackInTheSameTurn_canIt)
            goto Label_711;
    
        Label_380:
        Subtract_IntInt = tmpCardToMove->movementLeft - 1;
    
        tmpCardToMove->movementLeft = Subtract_IntInt;
    
        goto Label_494;
    
        Label_494:
        ExecuteOnMoveToFrontlineCardEffects(tmpCardToMove, force, movementCost);
    
        ExecuteOnOperationKreditsSpent(tmpCardToMove, movementCost);
    
        return;
    
        Label_568:
        PayMovementCost(cardID, CallFunc_PayMovementCost_success);
    
        if (!CallFunc_PayMovementCost_success)
            return;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CallFunc_GetCardFromID_card->getTotalOperationCost(CallFunc_getTotalOperationCost_totalOperationCost);
    
        movementCost = CallFunc_getTotalOperationCost_totalOperationCost;
    
        return;
    
        Label_711:
        tmpCardToMove->attackLeft = 0;
    
        goto Label_380;
    
        Label_761:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void CardLocationMoved(int cardID, int instigatorID, ECardLocationEnum oldLocation, ECardLocationEnum newLocation, int newLocationNumber, int nonVisualLocationNumber, CardMoveReason moveReason, bool SkipAddSubAction, bool changeOwner)
    {
        MakeVariable_MakeVariableOutput = TArray { 0x5, 0x6, 0x7 };;
    
        boardLocations = MakeVariable_MakeVariableOutput;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        tmpCard = CallFunc_GetCardFromID_card;
    
        SetRightLeftMostWhenPlayed(tmpCard, newLocation);
    
        Set_Contains_2 = Set_Contains(boardLocations, newLocation);
    
        if (!Set_Contains_2)
            goto Label_1214;
    
        InjectCardIntoLocation(newLocation, nonVisualLocationNumber, cardID);
    
        goto Label_257;
    
        Label_257:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_2);
    
        if (!CallFunc_IsActionProcess_ActionProcess_2)
            goto Label_310;
    
        if (!SkipAddSubAction)
            goto Label_1256;
    
        goto Label_1356;
    
        Label_310:
        MakeSet_Set = TArray { oldLocation, newLocation };;
    
        RefreshLocationStatus(MakeSet_Set);
    
        goto Label_372;
    
        Label_372:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_638;
    
        Set_Contains = Set_Contains(boardLocations, newLocation);
    
        Set_Contains_1 = Set_Contains(boardLocations, oldLocation);
    
        BooleanOR_1 = (Set_Contains_1 || Set_Contains);
    
        if (!BooleanOR_1)
            return;
    
        ExecuteOnCardLocationMoved(cardID, oldLocation, newLocation, changeOwner, moveReason);
    
        return;
    
        Label_638:
        EqualEqual_ByteByte_2 = ((!newLocation) == (!0x7));
    
        if (!EqualEqual_ByteByte_2)
            goto Label_770;
    
        tmpCard->getHasSmokescreen(CallFunc_getHasSmokescreen_doesIt);
    
        if (!CallFunc_getHasSmokescreen_doesIt)
            return;
    
        RemoveSmokescreen(cardID, cardID, true, false);
    
        return;
    
        Label_770:
        EqualEqual_ByteByte_3 = ((!oldLocation) == (!0x7));
    
        EqualEqual_ByteByte_4 = ((!newLocation) == (!0x6));
    
        EqualEqual_ByteByte_5 = ((!newLocation) == (!0x5));
    
        BooleanOR_2 = (EqualEqual_ByteByte_4 || EqualEqual_ByteByte_5);
    
        BooleanAND_1 = BooleanOR_2 && EqualEqual_ByteByte_3;
    
        if (!BooleanAND_1)
            goto Label_1011;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        ExecuteOnCardMoveFromFrontline(tmpCard);
    
        return;
    
        Label_1011:
        NotEqual_ByteByte = ((!moveReason) !== (!0xD));
    
        EqualEqual_ByteByte = ((!newLocation) == (!0x7));
    
        EqualEqual_ByteByte_1 = ((!oldLocation) == (!0x7));
    
        BooleanOR = (EqualEqual_ByteByte_1 || EqualEqual_ByteByte);
    
        BooleanAND = BooleanOR && NotEqual_ByteByte;
    
        if (!BooleanAND)
            return;
    
        UpdateFrontlineIfNeeded(cardID);
    
        return;
    
        Label_1214:
        SetCardLocationAndLocNumber(cardID, newLocation, newLocationNumber);
    
        return;
    
        Label_1256:
        CardFunctionsNotifier->NotifyMoveCardToNewLocation(cardID, instigatorID, oldLocation, newLocation, newLocationNumber, nonVisualLocationNumber, moveReason);
    
        return;
    
        Label_1356:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void MoveCardFromBoardToOwnersHand(int cardID, int instigatorID, ECardLocationEnum OldLocation, ECardLocationEnum NewLocation)
    {
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(cardID, tmpNewLocation, OldLocation, 0x3);
    
        goto Label_54;
    
        Label_54:
        FetchCardsByLocation(NewLocation, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        tmpLocationNumber = CallFunc_FetchCardsByLocation_QtyInLocation;
    
        tmpNewLcationFull = CallFunc_FetchCardsByLocation_isLocationFull;
    
        if (!tmpNewLcationFull)
            goto Label_925;
    
        tmpNewLocation = 0x8;
    
        goto Label_208;
    
        Label_208:
        CardLocationMoved(cardID, instigatorID, OldLocation, tmpNewLocation, tmpLocationNumber, tmpLocationNumber, 0x2, false, false);
    
        goto Label_286;
    
        Label_286:
        ExecuteOnAfterLeaveBoardOrOwnerEvents(cardID, tmpNewLocation, OldLocation);
    
        goto Label_333;
    
        Label_333:
        if (!tmpNewLcationFull)
            goto Label_446;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_1350;
    
        CardFunctionsNotifier->NotifyDiscardCard(cardID, instigatorID, OldLocation, false, false);
    
        return;
    
        Label_446:
        GameStateRef->GetAllCardInBattleAsMap(CallFunc_GetAllCardInBattleAsMap_AllCardsInBattle);
    
        Map_Find = Map_Find(CallFunc_GetAllCardInBattleAsMap_AllCardsInBattle, cardID, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_650;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_4);
    
        tmpCardToMove = CallFunc_GetCardFromID_card_4;
    
        ResetCardInBattle(tmpCardToMove);
    
        return;
    
        Label_650:
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_3);
    
        CallFunc_GetCardFromID_card_3->cardSeen = true;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_847;
    
        MakeArray_Array = [ cardID ];
    
        MakeArray_Array_1 = [ true ];
    
        CardFunctionsNotifier->NotifyCardsSeen(MakeArray_Array, MakeArray_Array_1, false, false);
    
        goto Label_953;
    
        Label_847:
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_2);
    
        UpdateBondVisuals(CallFunc_GetCardFromID_card_2->side);
    
        return;
    
        Label_925:
        tmpNewLocation = NewLocation;
    
        return;
    
        Label_953:
        GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card);
    
        EqualEqual_ByteByte = ((!CallFunc_GetCardFromID_card->side) == (!CallFunc_GetClientSide_OutClientSide));
    
        if (!EqualEqual_ByteByte)
            return;
    
        GetCardFromID(instigatorID, CallFunc_GetCardFromID_card);
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_1);
    
        EqualEqual_NameName = CallFunc_GetCardFromID_card_1->name == "card_unit_railway_gun_leopold";
    
        EqualEqual_NameName_1 = CallFunc_GetCardFromID_card->name == "card_unit_railway_gun_leopold";
    
        BooleanAND = EqualEqual_NameName && EqualEqual_NameName_1;
    
        GameStateRef->leopoldMovingLeopold = BooleanAND;
    
        return;
    
        Label_1350:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void MoveCardToTopOfDeck(int cardID, int instigatorID, int position, bool skipAction)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        cardToMove = CallFunc_GetCardFromID_card;
    
        oldLocation = cardToMove->location;
    
        OriginalSide = cardToMove->originalSide;
    
        GetDeckLocationBySide(OriginalSide, CallFunc_GetDeckLocationBySide_deckLocation);
    
        newLocation = CallFunc_GetDeckLocationBySide_deckLocation;
    
        MakeSet_Set = TArray { 0x5, 0x6, 0x7 };;
    
        board = MakeSet_Set;
    
        goto Label_267;
    
        Label_267:
        Set_Contains_1 = Set_Contains(board, oldLocation);
    
        if (!Set_Contains_1)
            goto Label_386;
    
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(cardID, newLocation, oldLocation, 0x4);
    
        goto Label_1130;
    
        Label_386:
        CardLocationMoved(cardID, instigatorID, oldLocation, newLocation, 0, position, 0x3, skipAction, false);
    
        goto Label_468;
    
        Label_468:
        Set_Contains = Set_Contains(board, oldLocation);
    
        if (!Set_Contains)
            goto Label_585;
    
        ExecuteOnAfterLeaveBoardOrOwnerEvents(cardID, newLocation, oldLocation);
    
        return;
    
        Label_585:
        GameStateRef->GetAllCardInBattleAsMap(CallFunc_GetAllCardInBattleAsMap_AllCardsInBattle);
    
        Map_Find = Map_Find(CallFunc_GetAllCardInBattleAsMap_AllCardsInBattle, cardID, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_852;
    
        GameStateRef->GetAllCardInBattleAsMap(CallFunc_GetAllCardInBattleAsMap_AllCardsInBattle);
    
        Map_Find = Map_Find(CallFunc_GetAllCardInBattleAsMap_AllCardsInBattle, cardID, CallFunc_Map_Find_Value);
    
        ResetCardInBattle(CallFunc_Map_Find_Value);
    
        return;
    
        Label_852:
        GameStateRef->AddCardToDeckBySide(OriginalSide, cardID, true, position);
    
        ExecuteOnAfterDeckChanged(OriginalSide);
    
        goto Label_945;
    
        Label_945:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1130;
    
        EqualEqual_ByteByte = ((!0x3) == (!oldLocation));
    
        EqualEqual_ByteByte_1 = ((!oldLocation) == (!0x4));
    
        BooleanOR = (EqualEqual_ByteByte || EqualEqual_ByteByte_1);
    
        if (!BooleanOR)
            return;
    
        cardToMove->OnAfterCardMovedToDeckFromHand();
    
        return;
    
        Label_1130:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ApplyRemoveCardFromBoard(int cardID, int instigatorID, bool destroyed, bool destroyedInCombat, bool skipAddAction, bool converting)
    {
        Greater_IntInt = (cardID > 0);
    
        if (!Greater_IntInt)
            goto Label_853;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        leavingCardRef = CallFunc_GetCardFromID_card;
    
        oldLocation = leavingCardRef->location;
    
        goto Label_155;
    
        Label_155:
        Temp_byte_Variable_1 = 0x1;
    
        Temp_byte_Variable_2 = 0x6;
    
        Temp_byte_Variable_3 = 0x2;
    
        Temp_bool_Variable = destroyed;
    
        Temp_bool_Variable_1 = converting;
    
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(cardID, 0x8, oldLocation, Temp_bool_Variable ? Temp_byte_Variable_1 : Temp_bool_Variable_1 ? Temp_byte_Variable_2 : Temp_byte_Variable_3);
    
        goto Label_390;
    
        Label_390:
        Temp_byte_Variable = 0xD;
    
        Temp_byte_Variable_4 = 0xA;
    
        Temp_byte_Variable_5 = 0xB;
    
        Temp_bool_Variable_3 = converting;
    
        Temp_bool_Variable_2 = destroyed;
    
        CardLocationMoved(cardID, instigatorID, oldLocation, 0x8, 0, 0, Temp_bool_Variable_3 ? Temp_byte_Variable : Temp_bool_Variable_2 ? Temp_byte_Variable_4 : Temp_byte_Variable_5, true, false);
    
        goto Label_646;
    
        Label_646:
        ExecuteOnAfterLeaveBoardOrOwnerEvents(cardID, 0x8, oldLocation);
    
        if (!destroyed)
            goto Label_774;
    
        MakeArray_Array = [ cardID ];
    
        ExecuteOnCardDestroyedFunction(cardID, oldLocation, instigatorID, MakeArray_Array, destroyedInCombat);
    
        return;
    
        Label_774:
        if (!skipAddAction)
            goto Label_789;
    
        return;
    
        Label_789:
        CardFunctionsNotifier->NotifyRemoveCardFromBoard(cardID, instigatorID, oldLocation);
    
        return;
    
        Label_853:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ChangeUnitOwnership(int cardID, int instigatorID, ESideEnum fromSide, ESideEnum toSide, ECardLocationEnum fromLocation, bool releaseControl, ECardLocationEnum originalLocation, bool sendAction)
    {
        tmpOriginalLocationFull = false;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        cardToChange = CallFunc_GetCardFromID_card;
    
        oldLocation = cardToChange->location;
    
        if (!releaseControl)
            goto Label_546;
    
        FetchCardsByLocation(originalLocation, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        tmpCardsInNewlocation = CallFunc_FetchCardsByLocation_QtyInLocation;
    
        tmpOriginalLocationFull = CallFunc_FetchCardsByLocation_isLocationFull;
    
        tmpNewLocation = originalLocation;
    
        tmpLocationNumber = 0;
    
        EqualEqual_ByteByte_2 = ((!originalLocation) == (!0x7));
    
        if (!EqualEqual_ByteByte_2)
            goto Label_1502;
    
        GameStateRef->GetFrontlineOwnerSide(CallFunc_GetFrontlineOwnerSide_ownerSide);
    
        EqualEqual_ByteByte_1 = ((!CallFunc_GetFrontlineOwnerSide_ownerSide) == (!fromSide));
    
        if (!EqualEqual_ByteByte_1)
            goto Label_1502;
    
        Greater_IntInt = (tmpCardsInNewlocation > 1);
    
        if (!Greater_IntInt)
            goto Label_1977;
    
        tmpLocationNumber = cardToChange->locationNumber;
    
        Label_534:
        shouldRetreat = true;
    
        goto Label_2909;
    
        Label_546:
        cardToChange->IsUnit(CallFunc_IsUnit_isIt);
    
        if (!CallFunc_IsUnit_isIt)
            goto Label_2590;
    
        goto Label_2023;
    
        Label_617:
        SwitchEnum_CmpSuccess = ((!oldLocation) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_753;
    
        SwitchEnum_CmpSuccess = ((!oldLocation) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_753;
    
        SwitchEnum_CmpSuccess = ((!oldLocation) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2683;
    
        goto Label_2438;
    
        Label_753:
        GetSupportLineBySide = UCombatHelperFunctions::GetSupportLineBySide(toSide, this);
    
        tmpNewLocation = GetSupportLineBySide;
    
        FetchCardsByLocation(tmpNewLocation, CallFunc_FetchCardsByLocation_QtyInLocation_1, CallFunc_FetchCardsByLocation_isLocationFull_1, CallFunc_FetchCardsByLocation_AllCardsInLocation_1, CallFunc_FetchCardsByLocation_FirstCard_1, CallFunc_FetchCardsByLocation_fetchedCardsIDs_1);
    
        tmpLocationNumber = CallFunc_FetchCardsByLocation_QtyInLocation_1;
    
        if (!CallFunc_FetchCardsByLocation_isLocationFull_1)
            goto Label_928;
    
        goto Label_617;
    
        Label_928:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_2);
    
        if (!CallFunc_IsActionProcess_ActionProcess_2)
            goto Label_1008;
    
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(cardID, tmpNewLocation, oldLocation, 0x5);
    
        Label_1008:
        cardToChange->side = toSide;
    
        cardToChange->underEnemyControl = true;
    
        cardToChange->movementLeft = 1;
    
        cardToChange->getHasFury(CallFunc_getHasFury_doesIt);
    
        if (!CallFunc_getHasFury_doesIt)
            goto Label_2859;
    
        cardToChange->attackLeft = 2;
    
        Label_1235:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_1363;
    
        CardFunctionsNotifier->NotifyChangeUnitOwnership(cardID, instigatorID, oldLocation, fromSide, tmpNewLocation, toSide, false);
    
        Label_1363:
        CardLocationMoved(cardID, instigatorID, oldLocation, tmpNewLocation, tmpLocationNumber, tmpLocationNumber, 0x6, false, true);
    
        ExecuteOnAfterLeaveBoardOrOwnerEvents(cardID, tmpNewLocation, oldLocation);
    
        ExecuteOnEnterPlayEvents(cardToChange, 0x0);
    
        return;
    
        Label_1502:
        if (!tmpOriginalLocationFull)
            goto Label_1527;
    
        shouldRetreat = true;
    
        Label_1527:
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(cardID, tmpNewLocation, oldLocation, 0x5);
    
        cardToChange->side = toSide;
    
        cardToChange->underEnemyControl = false;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1780;
    
        CardFunctionsNotifier->NotifyChangeUnitOwnership(cardID, instigatorID, oldLocation, fromSide, tmpNewLocation, toSide, true);
    
        Label_1780:
        CardLocationMoved(cardID, instigatorID, oldLocation, tmpNewLocation, tmpLocationNumber, tmpLocationNumber, 0x5, false, true);
    
        ExecuteOnAfterLeaveBoardOrOwnerEvents(cardID, tmpNewLocation, oldLocation);
    
        ExecuteOnEnterPlayEvents(cardToChange, 0x0);
    
        if (!shouldRetreat)
            return;
    
        MakeArray_Array = [ cardToChange ];
    
        ApplyMakeCardRetreat(MakeArray_Array, 0);
    
        return;
    
        Label_1977:
        EqualEqual_ByteByte = ((!oldLocation) == (!0x7));
    
        if (!EqualEqual_ByteByte)
            goto Label_534;
    
        return;
    
        Label_2023:
        SwitchEnum_CmpSuccess_1 = ((!oldLocation) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2339;
    
        SwitchEnum_CmpSuccess_1 = ((!oldLocation) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2339;
    
        SwitchEnum_CmpSuccess_1 = ((!oldLocation) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2339;
    
        SwitchEnum_CmpSuccess_1 = ((!oldLocation) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2339;
    
        SwitchEnum_CmpSuccess_1 = ((!oldLocation) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2339;
    
        SwitchEnum_CmpSuccess_1 = ((!oldLocation) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2339;
    
        SwitchEnum_CmpSuccess_1 = ((!oldLocation) !== (!0x9));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2339;
    
        return;
    
        Label_2339:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Tried to take control of unit that was not on the board", this);
    
        return;
    
        Label_2438:
        EqualEqual_ByteByte_3 = ((!cardToChange->side) == (!toSide));
    
        if (!EqualEqual_ByteByte_3)
            return;
    
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Tried to take control of your own unit", this);
    
        return;
    
        Label_2590:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Tried taking control of a card that is not a unit", this);
    
        return;
    
        Label_2683:
        FetchCardsByLocation(oldLocation, CallFunc_FetchCardsByLocation_QtyInLocation_2, CallFunc_FetchCardsByLocation_isLocationFull_2, CallFunc_FetchCardsByLocation_AllCardsInLocation_2, CallFunc_FetchCardsByLocation_FirstCard_2, CallFunc_FetchCardsByLocation_fetchedCardsIDs_2);
    
        Greater_IntInt_1 = (CallFunc_FetchCardsByLocation_QtyInLocation_2 > 1);
    
        if (!Greater_IntInt_1)
            goto Label_2804;
    
        goto Label_753;
    
        Label_2804:
        tmpNewLocation = oldLocation;
    
        tmpCardsInNewlocation = 0;
    
        goto Label_928;
    
        Label_2859:
        cardToChange->attackLeft = 1;
    
        goto Label_1235;
    
        Label_2909:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void PlayCardFromHand(int cardID, int instigatorID, int NewLocationNumber, int targetCardID, int NewNonVisualLocationNumber, bool receiveFromLocal)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_1);
    
        tmpCardToPlay = CallFunc_GetCardFromID_card_1;
    
        Greater_IntInt_2 = (tmpCardToPlay->gotchaActivated > 0);
    
        if (!Greater_IntInt_2)
            goto Label_1598;
    
        Conv_JsonObjectToJsonValue = UBlueprintJsonLibrary::Conv_JsonObjectToJsonValue(tmpCardToPlay->customJson, "kreditsPayed");
    
        Conv_JsonValueToInteger = UBlueprintJsonLibrary::Conv_JsonValueToInteger(Conv_JsonObjectToJsonValue);
    
        ChangeKreditsBySide(tmpCardToPlay->side, Conv_JsonValueToInteger, cardID);
    
        goto Label_305;
    
        Label_305:
        tmpOldLocation = tmpCardToPlay->location;
    
        tmpCardToPlay->IsOrder(CallFunc_IsOrder_isIt);
    
        if (!CallFunc_IsOrder_isIt)
            goto Label_1732;
    
        tmpnewLocation = 0x8;
    
        goto Label_1871;
    
        Label_441:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_916;
    
        Array_Length = tmpCardToPlay->chooseOneCards.Length;
    
        Greater_IntInt_1 = (Array_Length > 0);
    
        SelectInt_1 = (Greater_IntInt_1 ? tmpCardToPlay->chooseOneIndex : -1);
    
        tmpChooseOneIndex = SelectInt_1;
    
        Greater_IntInt = (targetCardID > 0);
    
        if (!Greater_IntInt)
            goto Label_1950;
    
        GetCardFromID(targetCardID, CallFunc_GetCardFromID_card);
    
        tmpCardToPlay->currentTarget = CallFunc_GetCardFromID_card;
    
        Label_815:
        CardFunctionsNotifier->NotifyPlayFromHand(cardID, instigatorID, tmpnewLocation, NewLocationNumber, targetCardID, tmpChooseOneIndex, NewNonVisualLocationNumber, false);
    
        goto Label_441;
    
        Label_916:
        tmpCardToPlay->IsGotcha(CallFunc_IsGotcha_isIt);
    
        if (!CallFunc_IsGotcha_isIt)
            goto Label_1988;
    
        return;
    
        Label_981:
        JSON_Clear(tmpCardToPlay, "countdown_timer", CallFunc_JSON_Clear_found);
    
        if (!CallFunc_JSON_Clear_found)
            goto Label_1097;
    
        PersistCustomFields(tmpCardToPlay->cardID, false);
    
        goto Label_2061;
    
        Label_1097:
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber_1);
    
        tmpCardToPlay->enterPlayOnTurn = CallFunc_GetTurnNumber_turnNumber_1;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        GameStateRef->updateCardsPlayedFromHandByTurn(CallFunc_GetTurnNumber_turnNumber, tmpCardToPlay->cardID);
    
        tmpCardToPlay->IsUnit(CallFunc_IsUnit_isIt_2);
    
        if (!CallFunc_IsUnit_isIt_2)
            goto Label_981;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        UFunctionLibrary::GetStaticKredits(tmpCardToPlay->name, CallFunc_GetStaticKredits_kredits);
    
        Min = UKismetMathLibrary::Min(3, CallFunc_GetStaticKredits_kredits);
    
        SelectInt = (tmpCardToPlay->isSalvaged ? Min : CallFunc_GetStaticKredits_kredits);
    
        tmpCardToPlay->setAndEncryptKredit(SelectInt, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        goto Label_2840;
    
        Label_1598:
        tmpCardToPlay->getHasGameplayTag(FGameplayTag("autoplay"), CallFunc_getHasGameplayTag_hasTag);
    
        if (!CallFunc_getHasGameplayTag_hasTag)
            goto Label_1681;
    
        return;
    
        Label_1681:
        PayCardCost(tmpCardToPlay, cardID, targetCardID, CallFunc_PayCardCost_success);
    
        return;
    
        Label_1732:
        tmpCardToPlay->IsUnit(CallFunc_IsUnit_isIt_3);
    
        if (!CallFunc_IsUnit_isIt_3)
            return;
    
        GetSupportLineBySide = UCombatHelperFunctions::GetSupportLineBySide(tmpCardToPlay->side, this);
    
        tmpnewLocation = GetSupportLineBySide;
    
        return;
    
        Label_1871:
        tmpCardToPlay->IsGotcha(CallFunc_IsGotcha_isIt_1);
    
        if (!CallFunc_IsGotcha_isIt_1)
            return;
    
        tmpnewLocation = tmpOldLocation;
    
        return;
    
        Label_1950:
        tmpCardToPlay->currentTarget = nullptr;
    
        goto Label_815;
    
        Label_1988:
        CardLocationMoved(cardID, cardID, tmpOldLocation, tmpnewLocation, NewLocationNumber, NewNonVisualLocationNumber, 0x4, false, false);
    
        return;
    
        Label_2061:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2704;
    
        CardPlayedFromHand(tmpCardToPlay, targetCardID);
    
        goto Label_2147;
    
        Label_2147:
        GameStateRef->GetExecuteWaitPlayFromHand(CallFunc_GetExecuteWaitPlayFromHand_ShouldExecuteWait);
    
        if (!CallFunc_GetExecuteWaitPlayFromHand_ShouldExecuteWait)
            goto Label_2207;
    
        goto Label_2236;
    
        Label_2207:
        GiveAlpineBonus(tmpCardToPlay);
    
        goto Label_2231;
    
        Label_2231:
        return;
    
        Label_2236:
        tmpCardToPlay->IsUnit(CallFunc_IsUnit_isIt);
    
        EqualEqual_ByteByte = ((!tmpCardToPlay->rarity) == (!0x4));
    
        BooleanAND = EqualEqual_ByteByte && CallFunc_IsUnit_isIt;
    
        GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        EqualEqual_ByteByte_1 = ((!tmpCardToPlay->side) == (!CallFunc_GetClientSide_OutClientSide));
    
        BooleanAND_1 = BooleanAND && EqualEqual_ByteByte_1;
    
        if (!BooleanAND_1)
            return;
    
        Conv_NameToString = FString(tmpCardToPlay->name);
    
        GameStateRef->Achievements_AddEliteCopy(Conv_NameToString, tmpCardToPlay->cardID, CallFunc_Achievements_AddEliteCopy_3_eliteAchieved);
    
        if (!CallFunc_Achievements_AddEliteCopy_3_eliteAchieved)
            return;
    
        CardFunctionsNotifier->NotifyAchievementCounterDirect("3_elite", 1);
    
        return;
    
        Label_2704:
        tmpCardToPlay->IsUnit(CallFunc_IsUnit_isIt_1);
    
        if (!CallFunc_IsUnit_isIt_1)
            return;
    
        tmpCardToPlay->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            return;
    
        tmpCardToPlay->cardSeen = false;
    
        return;
    
        Label_2840:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void CardPlayedFromHand(class UBaseCardObject* cardPlayed, int targetCardID)
    {
        OnPlayedFromHandExecuted = false;
    
        _triggerMultiple = 0;
    
        MakeSet_Set = TArray { "card_event_sunny1_blue_sky", "card_event_rain1_mist", "card_event_storm1_gale" };;
    
        Set_Contains = Set_Contains(MakeSet_Set, cardPlayed->name);
    
        if (!Set_Contains)
            goto Label_267;
    
        GetCardFromID(targetCardID, CallFunc_GetCardFromID_card);
    
        cardPlayed->OnPlayedFromHand(CallFunc_GetCardFromID_card);
    
        goto Label_6853;
    
        Label_267:
        GameStateRef->SetStopFurtherActions(false);
    
        GetActiveGotchasOrdered(CallFunc_GetActiveGotchasOrdered_cardIDs);
    
        activeGotchasCardIDs = CallFunc_GetActiveGotchasOrdered_cardIDs;
    
        Temp_int_Loop_Counter_Variable_3 = 0;
    
        Temp_int_Array_Index_Variable_3 = 0;
    
        Label_400:
        Array_Length_6 = activeGotchasCardIDs.Length;
    
        Less_IntInt_6 = (Temp_int_Loop_Counter_Variable_3 < Array_Length_6);
    
        if (!Less_IntInt_6)
            goto Label_643;
    
        Temp_int_Array_Index_Variable_3 = Temp_int_Loop_Counter_Variable_3;
    
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions_2);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions_2)
            goto Label_2669;
    
        Label_602:
        CardFunctionsNotifier->NotifyStopFurtherActions();
    
        return;
    
        Label_643:
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions_1);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions_1)
            goto Label_707;
    
        goto Label_602;
    
        Label_707:
        cardPlayed->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_1113;
    
        cardPlayed->OnCovertCardPlayedFromHand();
    
        FetchAllCardsWithEventTrigger(0x3C, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_4);
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_869:
        Array_Length_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_4.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_2595;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_2 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_4[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_2->OnOtherCovertCardPlayedFromHand(cardPlayed);
    
        goto Label_3232;
    
        Label_1113:
        FetchAllCardsWithEventTrigger(0x13, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_3);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_1184:
        Array_Length_2 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_3.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt_2)
            goto Label_1539;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_3[Temp_int_Array_Index_Variable_2];
    
        NotEqual_ObjectObject = (CallFunc_Array_Get_Item_1 !== cardPlayed);
    
        if (!NotEqual_ObjectObject)
            goto Label_3306;
    
        CallFunc_Array_Get_Item_1 = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_3[Temp_int_Array_Index_Variable_2];
    
        CallFunc_Array_Get_Item_1->OnBeforeOtherCardPlayedFromHand(cardPlayed);
    
        return;
    
        Label_1539:
        cardPlayed->HasBond(CallFunc_HasBond_hasIt);
    
        Set_Contains_1 = Set_Contains(GameStateRef->activeBondFactions, cardPlayed->faction);
    
        Not_PreBool_1 = !Set_Contains_1;
    
        BooleanAND_1 = CallFunc_HasBond_hasIt && Not_PreBool_1;
    
        if (!BooleanAND_1)
            goto Label_1918;
    
        ApplyFatigueDamage(cardPlayed->side, true, CallFunc_ApplyFatigueDamage_destroyed);
    
        if (!CallFunc_ApplyFatigueDamage_destroyed)
            goto Label_1918;
    
        GetTheOtherSide = UCombatHelperFunctions::GetTheOtherSide(cardPlayed->side, this);
    
        HQ_DestroyedEndMatch(GetTheOtherSide);
    
        return;
    
        Label_1918:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2080;
    
        Greater_IntInt_2 = (cardPlayed->cipher > 0);
    
        if (!Greater_IntInt_2)
            goto Label_2080;
    
        cardPlayed->IsGotcha(CallFunc_IsGotcha_isIt);
    
        if (!CallFunc_IsGotcha_isIt)
            goto Label_3380;
    
        Label_2080:
        FetchAllCardsWithEventTrigger(0x33, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2);
    
        otherCards = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_2;
    
        FetchAllCardsWithEventTrigger(0x2B, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        Array_Append(otherCards, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger_1);
    
        if (!cardPlayed->waitWithOnOtherCardPlayedUntilHandTargetSelected)
            goto Label_3501;
    
        GameStateRef->ClearWaitPlayFromHandCards();
    
        Temp_int_Loop_Counter_Variable_6 = 0;
    
        Temp_int_Array_Index_Variable_4 = 0;
    
        Label_2325:
        Array_Length_3 = otherCards.Length;
    
        Less_IntInt_3 = (Temp_int_Loop_Counter_Variable_6 < Array_Length_3);
    
        if (!Less_IntInt_3)
            goto Label_3501;
    
        Temp_int_Array_Index_Variable_4 = Temp_int_Loop_Counter_Variable_6;
    
        CallFunc_Array_Get_Item_3 = otherCards[Temp_int_Array_Index_Variable_4];
    
        GameStateRef->AddWaitPlayFromHandCards(CallFunc_Array_Get_Item_3->cardID);
    
        goto Label_6439;
    
        Label_2595:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_3 + 1;
    
        Temp_int_Loop_Counter_Variable_3 = Add_IntInt_2;
    
        goto Label_400;
    
        Label_2669:
        CallFunc_Array_Get_Item_6 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_3];
    
        GetCardFromID(CallFunc_Array_Get_Item_6, CallFunc_GetCardFromID_card_7);
    
        CallFunc_GetCardFromID_card_7->CustomName1HasAttribute("gotchaAfterPlayFromHand", CallFunc_CustomName1HasAttribute_doesIt);
    
        if (!CallFunc_CustomName1HasAttribute_doesIt)
            goto Label_2968;
    
        CallFunc_Array_Get_Item_6 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_3];
    
        Array_Add_2 = AfterPlayFromHandActiveGotchasCardIDs.Add(CallFunc_Array_Get_Item_6);
    
        return;
    
        Label_2968:
        CallFunc_Array_Get_Item_6 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_3];
    
        GetCardFromID(CallFunc_Array_Get_Item_6, CallFunc_GetCardFromID_card_7);
    
        CallFunc_GetCardFromID_card_7->OnOtherCardPlayedFromHand(cardPlayed);
    
        CallFunc_Array_Get_Item_6 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_3];
    
        Array_Add_3 = cardsDone.Add(CallFunc_Array_Get_Item_6);
    
        return;
    
        Label_3232:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_3;
    
        goto Label_869;
    
        Label_3306:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1184;
    
        Label_3380:
        SetCardsSeenByCipher(cardPlayed->cipher, cardPlayed->cardID, cardPlayed->side, CallFunc_SetCardsSeenByCipher_qqq);
    
        goto Label_2080;
    
        Label_3501:
        cardPlayed->OnEnterPlay(0x1);
    
        EqualEqual_NameName = cardPlayed->name == "card_event_naval_engagement";
    
        if (!EqualEqual_NameName)
            goto Label_3640;
    
        OnNavalEngagementPlayed(cardPlayed);
    
        Label_3640:
        if (!cardPlayed->hasDeployment)
            goto Label_5840;
    
        FetchAllCardsWithEventTrigger(0xE, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_3758:
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        BooleanAND_2 = Not_PreBool && Less_IntInt;
    
        if (!BooleanAND_2)
            goto Label_4283;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnBeforeOtherCardDeploymentTrigger(cardPlayed, CallFunc_OnBeforeOtherCardDeploymentTrigger_cancelDeploymentEffect);
    
        if (!CallFunc_OnBeforeOtherCardDeploymentTrigger_cancelDeploymentEffect)
            goto Label_4209;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CardFunctionsNotifier->NotifyForceCardEffectTrigger(CallFunc_Array_Get_Item, 0x9);
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        return;
    
        Label_4209:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_3758;
    
        Label_4283:
        if (!CallFunc_OnBeforeOtherCardDeploymentTrigger_cancelDeploymentEffect)
            goto Label_5702;
    
        OnPlayedFromHandExecuted = false;
    
        NotifySideEffectTrigger(cardPlayed->side, FGameplayTag("sideeffect.blockdeployment"), CallFunc_NotifySideEffectTrigger_qqq);
    
        Label_4389:
        cardPlayed->IsWeatherCard(CallFunc_IsWeatherCard_isWeatherCard);
    
        if (!CallFunc_IsWeatherCard_isWeatherCard)
            goto Label_4481;
    
        GameStateRef->SetHasPlayedWeatherCardThisTurn(true);
    
        Label_4481:
        GetCardFromID(targetCardID, CallFunc_GetCardFromID_card_4);
    
        IsValid = CallFunc_GetCardFromID_card_4;
    
        BooleanAND_3 = cardPlayed->hasPincer && IsValid;
    
        if (!BooleanAND_3)
            goto Label_4680;
    
        GetCardFromID(targetCardID, CallFunc_GetCardFromID_card_5);
    
        ApplyPincerEffects(cardPlayed, CallFunc_GetCardFromID_card_5);
    
        Label_4680:
        Array_Add_1 = cardsDone.Add(cardPlayed->cardID);
    
        BooleanAND_4 = cardPlayed->waitWithOnOtherCardPlayedUntilHandTargetSelected && OnPlayedFromHandExecuted;
    
        if (!BooleanAND_4)
            goto Label_4886;
    
        GameStateRef->SetExecuteWaitPlayFromHand(true);
    
        return;
    
        Label_4886:
        GameStateRef->SetExecuteWaitPlayFromHand(false);
    
        Temp_int_Loop_Counter_Variable_4 = 0;
    
        Temp_int_Array_Index_Variable_6 = 0;
    
        Label_4969:
        Array_Length_4 = AfterPlayFromHandActiveGotchasCardIDs.Length;
    
        Less_IntInt_4 = (Temp_int_Loop_Counter_Variable_4 < Array_Length_4);
    
        if (!Less_IntInt_4)
            goto Label_5360;
    
        Temp_int_Array_Index_Variable_6 = Temp_int_Loop_Counter_Variable_4;
    
        CallFunc_Array_Get_Item_4 = AfterPlayFromHandActiveGotchasCardIDs[Temp_int_Array_Index_Variable_6];
    
        GetCardFromID(CallFunc_Array_Get_Item_4, CallFunc_GetCardFromID_card_3);
    
        _tmpOtherCard = CallFunc_GetCardFromID_card_3;
    
        Label_5222:
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions)
            goto Label_6513;
    
        return;
    
        Label_5286:
        Add_IntInt_4 = Temp_int_Loop_Counter_Variable_4 + 1;
    
        Temp_int_Loop_Counter_Variable_4 = Add_IntInt_4;
    
        goto Label_4969;
    
        Label_5360:
        Temp_int_Loop_Counter_Variable_5 = 0;
    
        Temp_int_Array_Index_Variable_5 = 0;
    
        Label_5406:
        Array_Length_5 = otherCards.Length;
    
        Less_IntInt_5 = (Temp_int_Loop_Counter_Variable_5 < Array_Length_5);
    
        if (!Less_IntInt_5)
            goto Label_5286;
    
        Temp_int_Array_Index_Variable_5 = Temp_int_Loop_Counter_Variable_5;
    
        CallFunc_Array_Get_Item_5 = otherCards[Temp_int_Array_Index_Variable_5];
    
        _tmpOtherCard = CallFunc_Array_Get_Item_5;
    
        goto Label_5222;
    
        Label_5628:
        Add_IntInt_5 = Temp_int_Loop_Counter_Variable_5 + 1;
    
        Temp_int_Loop_Counter_Variable_5 = Add_IntInt_5;
    
        goto Label_5406;
    
        Label_5702:
        EqualEqual_IntInt = targetCardID == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_5840;
    
        ExecuteOnDeploymentTriggered(cardPlayed, cardPlayed->cardID, CallFunc_ExecuteOnDeploymentTriggered_triggerMultiple);
    
        _triggerMultiple = CallFunc_ExecuteOnDeploymentTriggered_triggerMultiple;
    
        Label_5840:
        Greater_IntInt = (_triggerMultiple > 0);
    
        BooleanAND = cardPlayed->waitWithOnOtherCardPlayedUntilHandTargetSelected && Greater_IntInt;
    
        if (!BooleanAND)
            goto Label_6082;
    
        cardPlayed->SetExtraPlayTriggers(_triggerMultiple);
    
        GetCardFromID(targetCardID, CallFunc_GetCardFromID_card_1);
    
        cardPlayed->OnPlayedFromHand(CallFunc_GetCardFromID_card_1);
    
        Label_6066:
        OnPlayedFromHandExecuted = true;
    
        goto Label_4389;
    
        Label_6082:
        GetCardFromID(targetCardID, CallFunc_GetCardFromID_card_6);
    
        cardPlayed->OnPlayedFromHand(CallFunc_GetCardFromID_card_6);
    
        Greater_IntInt_1 = (_triggerMultiple > 0);
    
        if (!Greater_IntInt_1)
            goto Label_6066;
    
        Temp_int_Variable = 1;
    
        Label_6230:
        LessEqual_IntInt = (Temp_int_Variable <= _triggerMultiple);
    
        if (!LessEqual_IntInt)
            goto Label_6066;
    
        GetCardFromID(targetCardID, CallFunc_GetCardFromID_card_2);
    
        cardPlayed->OnPlayedFromHand(CallFunc_GetCardFromID_card_2);
    
        goto Label_6365;
    
        Label_6365:
        Add_IntInt_7 = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt_7;
    
        goto Label_6230;
    
        Label_6439:
        Add_IntInt_6 = Temp_int_Loop_Counter_Variable_6 + 1;
    
        Temp_int_Loop_Counter_Variable_6 = Add_IntInt_6;
    
        goto Label_2325;
    
        Label_6513:
        Array_Contains = cardsDone[_tmpOtherCard->cardID];
    
        BooleanOR = (Array_Contains || _tmpOtherCard->isSuppressed);
    
        if (!BooleanOR)
            goto Label_6670;
    
        goto Label_5628;
    
        Label_6670:
        _tmpOtherCard->OnOtherCardPlayedFromHand(cardPlayed);
    
        _tmpOtherCard->OnOtherCardEnterPlay(cardPlayed, 0x1);
    
        Array_Add = cardsDone.Add(_tmpOtherCard->cardID);
    
        return;
    
        Label_6853:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void AfterWaitCardPlayFromHand(class UBaseCardObject* cardPlayed, int targetCardID)
    {
        GameStateRef->SetExecuteWaitPlayFromHand(false);
    
        GameStateRef->SetStopFurtherActions(false);
    
        GetActiveGotchasOrdered(CallFunc_GetActiveGotchasOrdered_cardIDs);
    
        activeGotchasCardIDs = CallFunc_GetActiveGotchasOrdered_cardIDs;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_175:
        Array_Length_2 = activeGotchasCardIDs.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt_2)
            goto Label_490;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_2 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_2];
    
        GetCardFromID(CallFunc_Array_Get_Item_2, CallFunc_GetCardFromID_card_2);
    
        CallFunc_GetCardFromID_card_2->CustomName1HasAttribute("gotchaAfterPlayFromHand", CallFunc_CustomName1HasAttribute_doesIt);
    
        if (!CallFunc_CustomName1HasAttribute_doesIt)
            goto Label_1544;
    
        goto Label_1470;
    
        Label_490:
        Array_Add_1 = cardsDone.Add(cardPlayed->cardID);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_626:
        Array_Length_1 = activeGotchasCardIDs.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_1002;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = activeGotchasCardIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item_1, CallFunc_GetCardFromID_card_1);
    
        _tmpOtherCard = CallFunc_GetCardFromID_card_1;
    
        Label_879:
        GameStateRef->GetStopFurtherActions(CallFunc_GetStopFurtherActions_stopFurtherActions);
    
        if (!CallFunc_GetStopFurtherActions_stopFurtherActions)
            goto Label_1746;
    
        Label_938:
        GameStateRef->ClearWaitPlayFromHandCards();
    
        GiveAlpineBonus(cardPlayed);
    
        return;
    
        Label_1002:
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1048:
        GameStateRef->GetWaitPlayFromHandCards(CallFunc_GetWaitPlayFromHandCards_WaitPlayFromHandCards);
    
        Array_Length = CallFunc_GetWaitPlayFromHandCards_WaitPlayFromHandCards.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_2 < Array_Length);
    
        if (!Less_IntInt_1)
            goto Label_938;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_2;
    
        GameStateRef->GetWaitPlayFromHandCards(CallFunc_GetWaitPlayFromHandCards_WaitPlayFromHandCards);
    
        CallFunc_Array_Get_Item = CallFunc_GetWaitPlayFromHandCards_WaitPlayFromHandCards[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card);
    
        _tmpOtherCard = CallFunc_GetCardFromID_card;
    
        goto Label_879;
    
        Label_1396:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_1048;
    
        Label_1470:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_175;
    
        Label_1544:
        CallFunc_Array_Get_Item_2 = activeGotchasCardIDs[Temp_int_Array_Index_Variable_2];
    
        Array_Add_2 = cardsDone.Add(CallFunc_Array_Get_Item_2);
    
        goto Label_1396;
    
        Label_1672:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_626;
    
        Label_1746:
        Array_Contains = cardsDone[_tmpOtherCard->cardID];
    
        if (!Array_Contains)
            goto Label_1843;
    
        goto Label_1672;
    
        Label_1843:
        _tmpOtherCard->OnOtherCardPlayedFromHand(cardPlayed);
    
        _tmpOtherCard->OnOtherCardEnterPlay(cardPlayed, 0x1);
    
        Array_Add = cardsDone.Add(_tmpOtherCard->cardID);
    
        goto Label_2026;
    
        Label_2026:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SpawnCardToBoard(FName cardName, ESideEnum side, ECardLocationEnum location, int locationNumber, int overrideCardID, bool goldCard, bool giveBlitz, int spawnerID, EFactionEnum SalvageFaction, bool makeVeteran, int& cardSpawnedID)
    {
        EqualEqual_NameName = cardName == "None";
    
        if (!EqualEqual_NameName)
            goto Label_126;
    
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Tried to spawn a None card", this);
    
        return;
    
        Label_126:
        spawnedID = overrideCardID;
    
        FetchCardsByLocation(location, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        tmpLocationFull = CallFunc_FetchCardsByLocation_isLocationFull;
    
        NotEqual_ByteByte = ((!location) !== (!0x7));
    
        if (!NotEqual_ByteByte)
            goto Label_1079;
    
        Label_285:
        Not_PreBool = !tmpLocationFull;
    
        Greater_IntInt_1 = (overrideCardID > 0);
    
        BooleanOR = (Not_PreBool || Greater_IntInt_1);
    
        if (!BooleanOR)
            goto Label_734;
    
        Greater_IntInt = (overrideCardID > 0);
    
        if (!Greater_IntInt)
            goto Label_1468;
    
        Label_448:
        EqualEqual_IntInt = locationNumber == -1;
    
        if (!EqualEqual_IntInt)
            goto Label_1838;
    
        Label_496:
        GetCardFromID(spawnedID, CallFunc_GetCardFromID_card);
    
        cardSpawned = CallFunc_GetCardFromID_card;
    
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        cardSpawned->enterPlayOnTurn = CallFunc_GetTurnNumber_turnNumber;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            goto Label_734;
    
        cardSpawned->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_1884;
    
        ExecuteOnCovertCardSpawned(cardSpawned);
    
        Label_734:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_895;
    
        if (!giveBlitz)
            goto Label_817;
    
        GiveBlitz(spawnedID, spawnerID);
    
        Label_817:
        cardSpawned->getHasAlpine(CallFunc_getHasAlpine_doesIt);
    
        if (!CallFunc_getHasAlpine_doesIt)
            goto Label_895;
    
        GiveAlpineBonus(cardSpawned);
    
        Label_895:
        MakeSet_Set = TArray { location };;
    
        RefreshLocationStatus(MakeSet_Set);
    
        ExecuteOnCardLocationMoved(spawnedID, 0x0, location, false, 0xC);
    
        EqualEqual_ByteByte_1 = ((!location) == (!0x7));
    
        if (!EqualEqual_ByteByte_1)
            goto Label_1047;
    
        UpdateFrontlineIfNeeded(spawnedID);
    
        Label_1047:
        cardSpawnedID = spawnedID;
    
        return;
    
        Label_1079:
        GameStateRef->GetFrontlineOwnerSide(CallFunc_GetFrontlineOwnerSide_ownerSide);
    
        Temp_byte_Variable = 0x0;
    
        Temp_byte_Variable_1 = 0x2;
    
        Temp_byte_Variable_2 = 0x1;
    
        Temp_byte_Variable_3 = side;
    
        NotEqual_ByteByte_1 = ((!CallFunc_GetFrontlineOwnerSide_ownerSide) !== (!switch (Temp_byte_Variable_3)
        {
            case 0x0:
            {
                return Temp_byte_Variable;
                break;
            }
            case 0x1:
            {
                return Temp_byte_Variable_1;
                break;
            }
            case 0x2:
            {
                return Temp_byte_Variable_2;
                break;
            }
            default:
            {
                return Select_Default;
                break;
            }
        }));
    
        if (!NotEqual_ByteByte_1)
            goto Label_1329;
    
        goto Label_285;
    
        Label_1329:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Trying to move a unit to frontline but frontline owned by the other side", this);
    
        cardSpawnedID = 0;
    
        return;
    
        Label_1468:
        EqualEqual_ByteByte = ((!SalvageFaction) == (!0x0));
    
        MakeStruct_S_SalvagedCardInfo.isSalvaged_1_D83369C241D0F4E11CEDCB8250BC0D97 = true;
    
        MakeStruct_S_SalvagedCardInfo.salvageFaction_5_30136A02489F9A3E6C29FEB0A508ADD9 = SalvageFaction;
    
        MakeStruct_S_SalvagedCardInfo.salvagedCardID_8_60B10C4245C90998186E6E9E7E180468 = overrideCardID;
    
        Temp_struct_Variable = FS_SalvagedCardInfo(false, 0x0, 0);
    
        Temp_bool_Variable = EqualEqual_ByteByte;
    
        CreateCard(side, cardName, location, overrideCardID, locationNumber, false, goldCard, "", false, false, spawnerID, false, Temp_bool_Variable ? Temp_struct_Variable : MakeStruct_S_SalvagedCardInfo, false, makeVeteran, false, CallFunc_CreateCard_cardID);
    
        spawnedID = CallFunc_CreateCard_cardID;
    
        goto Label_448;
    
        Label_1838:
        InjectCardIntoLocation(location, locationNumber, spawnedID);
    
        goto Label_496;
    
        Label_1884:
        ExecuteOnEnterPlayEvents(cardSpawned, 0x3);
    
        goto Label_734;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ApplySetCardsSeenByCipher(TArray<class UBaseCardObject*>*& card, bool enemyTurn, bool showAnimation)
    {
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_51:
        Array_Length = card.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_625;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = card[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->IsLocatedInHand(CallFunc_IsLocatedInHand_isIt);
    
        if (!CallFunc_IsLocatedInHand_isIt)
            goto Label_731;
    
        CallFunc_Array_Get_Item = card[Temp_int_Array_Index_Variable];
    
        Array_Add_1 = IDs.Add(CallFunc_Array_Get_Item->cardID);
    
        Temp_bool_Variable = true;
    
        Array_Add = seen.Add(Temp_bool_Variable);
    
        CallFunc_Array_Get_Item = card[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->cardSeen = true;
    
        goto Label_805;
    
        Label_625:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CardFunctionsNotifier->NotifyCardsSeen(IDs, seen, showAnimation, enemyTurn);
    
        return;
    
        Label_731:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_51;
    
        Label_805:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void ChangeKreditsBySide(ESideEnum sideToChange, int kreditsAmount, int instigatorID)
    {
        GameStateRef->getKreditBySide(sideToChange, CallFunc_getKreditBySide_outputKredit);
    
        _oldKredits = CallFunc_getKreditBySide_outputKredit;
    
        GameStateRef->getMaxPossibleKredits(CallFunc_getMaxPossibleKredits_outputMax);
    
        Add_IntInt = _oldKredits + kreditsAmount;
    
        Clamp = ((Add_IntInt < 0) ? 0 : ((Add_IntInt > CallFunc_getMaxPossibleKredits_outputMax) ? CallFunc_getMaxPossibleKredits_outputMax : Add_IntInt));
    
        _newKredits = Clamp;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        GameStateRef->setKreditBySide(sideToChange, _newKredits, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        GameStateRef->getKreditSlotBySide(sideToChange, CallFunc_getKreditSlotBySide_outputKreditSlot);
    
        _maxKredits = CallFunc_getKreditSlotBySide_outputKreditSlot;
    
        goto Label_448;
    
        Label_448:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_572;
    
        CardFunctionsNotifier->NotifyChangeKredits(sideToChange, _oldKredits, _newKredits, _maxKredits, _maxKredits, instigatorID);
    
        return;
    
        Label_572:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void ChangeKreditSlotsBySide(ESideEnum sideToChange, int slotChangeAmount, int instigatorID)
    {
        GameStateRef->getKreditSlotBySide(sideToChange, CallFunc_getKreditSlotBySide_outputKreditSlot);
    
        oldKreditSlots = CallFunc_getKreditSlotBySide_outputKreditSlot;
    
        GameStateRef->getMaxPossibleKredits(CallFunc_getMaxPossibleKredits_outputMax);
    
        Add_IntInt = oldKreditSlots + slotChangeAmount;
    
        Clamp = ((Add_IntInt < 0) ? 0 : ((Add_IntInt > CallFunc_getMaxPossibleKredits_outputMax) ? CallFunc_getMaxPossibleKredits_outputMax : Add_IntInt));
    
        newKreditSlots = Clamp;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        GameStateRef->setKreditSlotBySide(sideToChange, newKreditSlots, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        GameStateRef->getKreditBySide(sideToChange, CallFunc_getKreditBySide_outputKredit);
    
        kredits = CallFunc_getKreditBySide_outputKredit;
    
        goto Label_448;
    
        Label_448:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_572;
    
        CardFunctionsNotifier->NotifyChangeKredits(sideToChange, kredits, kredits, oldKreditSlots, newKreditSlots, instigatorID);
    
        return;
    
        Label_572:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void SetKreditsAndKreditSlots(ESideEnum sideToSet, int newKredits, int newKreditSlots, int triggerCardID)
    {
        newKreditsClamp = 0;
    
        newKreditSlotsClamp = 0;
    
        Less_IntInt_1 = (newKredits < 0);
    
        if (!Less_IntInt_1)
            goto Label_957;
    
        Label_104:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Was asked to set resource lower than 0, setting it to 0", this);
    
        goto Label_199;
    
        Label_199:
        GameStateRef->getKreditBySide(sideToSet, CallFunc_getKreditBySide_outputKredit);
    
        oldKredits = CallFunc_getKreditBySide_outputKredit;
    
        GameStateRef->getKreditSlotBySide(sideToSet, CallFunc_getKreditSlotBySide_outputKreditSlot);
    
        oldKreditSlots = CallFunc_getKreditSlotBySide_outputKreditSlot;
    
        GameStateRef->getMaxPossibleKredits(CallFunc_getMaxPossibleKredits_outputMax_1);
    
        Clamp = ((newKredits < 0) ? 0 : ((newKredits > CallFunc_getMaxPossibleKredits_outputMax_1) ? CallFunc_getMaxPossibleKredits_outputMax_1 : newKredits));
    
        newKreditsClamp = Clamp;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        GameStateRef->setKreditBySide(sideToSet, newKreditsClamp, CallFunc_provideKeysAndFrameCount_key1_1, CallFunc_provideKeysAndFrameCount_key2_1, CallFunc_provideKeysAndFrameCount_frameCount_1);
    
        GameStateRef->getMaxPossibleKredits(CallFunc_getMaxPossibleKredits_outputMax);
    
        Clamp_1 = ((newKreditSlots < 0) ? 0 : ((newKreditSlots > CallFunc_getMaxPossibleKredits_outputMax) ? CallFunc_getMaxPossibleKredits_outputMax : newKreditSlots));
    
        newKreditSlotsClamp = Clamp_1;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        GameStateRef->setKreditSlotBySide(sideToSet, newKreditSlotsClamp, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        goto Label_833;
    
        Label_833:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_1006;
    
        CardFunctionsNotifier->NotifyChangeKredits(sideToSet, oldKredits, newKreditsClamp, oldKreditSlots, newKreditSlotsClamp, triggerCardID);
    
        return;
    
        Label_957:
        Less_IntInt = (newKreditSlots < 0);
    
        if (!Less_IntInt)
            return;
    
        goto Label_104;
    
        Label_1006:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteScryingEffectBySide(int cardToDrawID, class UBaseCardObject* cardPlayed, ESideEnum sideScrying)
    {
        GameStateRef->GetDeckBySide(sideScrying, CallFunc_GetDeckBySide_DeckCardIDs);
    
        Array_IsNotEmpty = CallFunc_GetDeckBySide_DeckCardIDs.Length > 0;
    
        if (!Array_IsNotEmpty)
            goto Label_2752;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_166:
        GameStateRef->GetDeckBySide(sideScrying, CallFunc_GetDeckBySide_DeckCardIDs);
    
        Array_Length = CallFunc_GetDeckBySide_DeckCardIDs.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_917;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetDeckBySide(sideScrying, CallFunc_GetDeckBySide_DeckCardIDs);
    
        CallFunc_Array_Get_Item = CallFunc_GetDeckBySide_DeckCardIDs[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card);
    
        cardPlayed->FilterCardsToScry(CallFunc_GetCardFromID_card, CallFunc_FilterCardsToScry_isValid);
    
        Greater_IntInt = (3 > _totalFilteredCards);
    
        BooleanAND = Greater_IntInt && CallFunc_FilterCardsToScry_isValid;
    
        if (!BooleanAND)
            goto Label_2294;
    
        GameStateRef->GetDeckBySide(sideScrying, CallFunc_GetDeckBySide_DeckCardIDs);
    
        CallFunc_Array_Get_Item = CallFunc_GetDeckBySide_DeckCardIDs[Temp_int_Array_Index_Variable];
    
        _deckCardIDs[_totalFilteredCards] = CallFunc_Array_Get_Item;
    
        Add_IntInt_3 = _totalFilteredCards + 1;
    
        Temp_int_Variable_1 = Add_IntInt_3;
    
        _totalFilteredCards = Temp_int_Variable_1;
    
        goto Label_2220;
    
        Label_917:
        EqualEqual_IntInt_1 = _totalFilteredCards == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_1063;
    
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Tried to execute scrying effect with 0 valid cards in deck", this);
    
        return;
    
        Label_1063:
        Temp_int_Variable = 0;
    
        Label_1086:
        Array_Length_2 = _deckCardIDs.Length;
    
        Min = UKismetMathLibrary::Min(Array_Length_2, 3);
    
        Subtract_IntInt = Min - 1;
    
        LessEqual_IntInt = (Temp_int_Variable <= Subtract_IntInt);
    
        if (!LessEqual_IntInt)
            goto Label_1398;
    
        CallFunc_Array_Get_Item_2 = _deckCardIDs[Temp_int_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item_2 == cardToDrawID;
    
        if (!EqualEqual_IntInt)
            goto Label_2550;
    
        goto Label_2476;
    
        Label_1398:
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1444:
        Array_Length_1 = tmpTopToBottomCardIDs.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_1834;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = tmpTopToBottomCardIDs[Temp_int_Array_Index_Variable_1];
    
        Array_RemoveItem = _deckCardIDs.Remove(CallFunc_Array_Get_Item_1);
    
        CallFunc_Array_Get_Item_1 = tmpTopToBottomCardIDs[Temp_int_Array_Index_Variable_1];
    
        Array_Add = _deckCardIDs.Add(CallFunc_Array_Get_Item_1);
    
        goto Label_2678;
    
        Label_1834:
        GameStateRef->SetDeckBySide(sideScrying, _deckCardIDs);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_2005;
    
        MakeArray_Array = [];
    
        CardFunctionsNotifier->NotifyNewDeck(sideScrying, _deckCardIDs, MakeArray_Array, 0x0, false, false);
    
        return;
    
        Label_2005:
        DrawTopCardFromDeck(sideScrying, 0, false, false, false, 0.4, true, CallFunc_DrawTopCardFromDeck_drawnCard);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess_1);
    
        if (!CallFunc_IsActionProcess_ActionProcess_1)
            return;
    
        CallFunc_Array_Get_Item_3 = _deckCardIDs[0];
    
        cardPlayed->OnHandTargetSelected(CallFunc_Array_Get_Item_3, cardPlayed->cardID);
    
        return;
    
        Label_2220:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_166;
    
        Label_2294:
        GameStateRef->GetDeckBySide(sideScrying, CallFunc_GetDeckBySide_DeckCardIDs);
    
        CallFunc_Array_Get_Item = CallFunc_GetDeckBySide_DeckCardIDs[Temp_int_Array_Index_Variable];
    
        Array_Add_2 = _deckCardIDs.Add(CallFunc_Array_Get_Item);
    
        return;
    
        Label_2476:
        Add_IntInt_2 = Temp_int_Variable + 1;
    
        Temp_int_Variable = Add_IntInt_2;
    
        goto Label_1086;
    
        Label_2550:
        CallFunc_Array_Get_Item_2 = _deckCardIDs[Temp_int_Variable];
    
        Array_Add_1 = tmpTopToBottomCardIDs.Add(CallFunc_Array_Get_Item_2);
    
        return;
    
        Label_2678:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_1444;
    
        Label_2752:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void PayCardCost(class UBaseCardObject* card, int cardID, int targetCardID, bool& success)
    {
        KreditCheckAndAutoBanIfNeeded();
    
        goto Label_35;
    
        Label_35:
        Greater_IntInt_1 = (targetCardID > 0);
    
        if (!Greater_IntInt_1)
            goto Label_437;
    
        GetCardFromID(targetCardID, CallFunc_GetCardFromID_card);
    
        targetCard = CallFunc_GetCardFromID_card;
    
        NotEqual_ByteByte = ((!card->side) !== (!targetCard->side));
    
        if (!NotEqual_ByteByte)
            goto Label_437;
    
        Greater_IntInt = (targetCard->KreditsTax_AsEnemyTarget > 0);
    
        if (!Greater_IntInt)
            goto Label_437;
    
        card->getTotalKreditCost(CallFunc_getTotalKreditCost_totalKreditCost_1);
    
        Add_IntInt = targetCard->KreditsTax_AsEnemyTarget + CallFunc_getTotalKreditCost_totalKreditCost_1;
    
        kredits = Add_IntInt;
    
        goto Label_506;
    
        Label_437:
        card->getTotalKreditCost(CallFunc_getTotalKreditCost_totalKreditCost);
    
        kredits = CallFunc_getTotalKreditCost_totalKreditCost;
    
        goto Label_659;
    
        Label_506:
        GameStateRef->getKreditBySide(card->side, CallFunc_getKreditBySide_outputKredit);
    
        Greater_IntInt_2 = (kredits > CallFunc_getKreditBySide_outputKredit);
    
        if (!Greater_IntInt_2)
            goto Label_873;
    
        errorText = "resources ";
    
        return;
    
        Label_659:
        MakeLiteralText = nullptr;
    
        EqualEqual_TextText = errorText == MakeLiteralText;
    
        if (!EqualEqual_TextText)
            goto Label_862;
    
        Multiply_IntInt = (kredits * -1);
    
        ChangeKreditsBySide(card->side, Multiply_IntInt, cardID);
    
        success = true;
    
        return;
    
        Label_862:
        success = false;
    
        Label_873:
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void PayMovementCost(int cardID, bool& success)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        _card->getTotalOperationCost(CallFunc_getTotalOperationCost_totalOperationCost);
    
        operationCost = CallFunc_getTotalOperationCost_totalOperationCost;
    
        GameStateRef->getKreditBySide(_card->side, CallFunc_getKreditBySide_outputKredit);
    
        GreaterEqual_IntInt = (CallFunc_getKreditBySide_outputKredit >= operationCost);
    
        if (!GreaterEqual_IntInt)
            goto Label_405;
    
        Multiply_IntInt = (operationCost * -1);
    
        ChangeKreditsBySide(_card->side, Multiply_IntInt, 0);
    
        GameStateRef->addOperationKreditsSpentThisTurn(operationCost);
    
        success = true;
    
        return;
    
        Label_405:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("possible cheat: pay movement cost is called when the player doesn't have enough kredits.", this);
    
        success = false;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void CreateCard(ESideEnum side, FName cardName, ECardLocationEnum location, int overrideCardID, int overrideLocationNumber, bool spawnCardInHand, bool gold, FString newCardText, bool cardSeen, bool skipDrawAnimation, int instigatorID, bool HideFromOpponent, struct FS_SalvagedCardInfo salvageInfo, bool skipAction, bool makeVeteran, bool fromOppositeSide, int& cardID)
    {
        wasFullBeforeCreating = false;
    
        _location = location;
    
        Greater_IntInt = (overrideCardID > 0);
    
        if (!Greater_IntInt)
            goto Label_635;
    
        _cardID = overrideCardID;
    
        Label_123:
        UFunctionLibrary::EnumCompareCardLocation(_location, 0x0, CallFunc_EnumCompareCardLocation_Branches);
    
        SwitchEnum_CmpSuccess = ((!CallFunc_EnumCompareCardLocation_Branches) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_744;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_EnumCompareCardLocation_Branches) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_809;
    
        goto Label_244;
    
        Label_244:
        IsLocationFull(_location, CallFunc_IsLocationFull_isFull);
    
        wasFullBeforeCreating = CallFunc_IsLocationFull_isFull;
    
        CreateCardObject(cardName, _cardID, side, _location, _locationNumber, gold, salvageInfo, CallFunc_CreateCardObject_cardObject);
    
        createdCard = CallFunc_CreateCardObject_cardObject;
    
        createdCard->cardSeen = cardSeen;
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_524;
    
        if (!skipAction)
            goto Label_945;
    
        cardID = _cardID;
    
        return;
    
        Label_524:
        EqualEqual_ByteByte_1 = ((!_location) == (!0x7));
    
        if (!EqualEqual_ByteByte_1)
            goto Label_603;
    
        RemoveSmokescreen(_cardID, _cardID, true, false);
    
        Label_603:
        cardID = _cardID;
    
        return;
    
        Label_635:
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        GameStateRef->GenerateNextCardID(CallFunc_GetTurnNumber_turnNumber, CallFunc_GenerateNextCardID_nextCardID);
    
        _cardID = CallFunc_GenerateNextCardID_nextCardID;
    
        goto Label_123;
    
        Label_744:
        GetHandLocationBySide_1 = UCombatHelperFunctions::GetHandLocationBySide(side, this);
    
        _location = GetHandLocationBySide_1;
    
        Label_809:
        Greater_IntInt_2 = (overrideLocationNumber > -1);
    
        if (!Greater_IntInt_2)
            goto Label_885;
    
        _locationNumber = overrideLocationNumber;
    
        goto Label_3112;
    
        Label_885:
        GetNextCardLocationNumber(_location, CallFunc_GetNextCardLocationNumber_locationNumber);
    
        _locationNumber = CallFunc_GetNextCardLocationNumber_locationNumber;
    
        return;
    
        Label_945:
        CardFunctionsNotifier->NotifyCreateNonVisualCard(createdCard);
    
        if (!makeVeteran)
            goto Label_1036;
    
        MakeVeteran(createdCard, CallFunc_MakeVeteran_qqq);
    
        Label_1036:
        FetchAllCardsWithEventTrigger(0x23, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1107:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1431;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardCreatedAlterCard(createdCard, 0x0);
    
        goto Label_1357;
    
        Label_1357:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1107;
    
        Label_1431:
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3043;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3043;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3043;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2092;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_2092;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_1882;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_1882;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_1882;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3043;
    
        SwitchEnum_CmpSuccess_1 = ((!_location) !== (!0x9));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_3043;
    
        return;
    
        Label_1882:
        CardFunctionsNotifier->NotifySpawnCard(side, _cardID, instigatorID, cardName, _location, overrideLocationNumber, makeVeteran);
    
        EqualEqual_ByteByte = ((!_location) == (!0x7));
    
        if (!EqualEqual_ByteByte)
            goto Label_2060;
    
        RemoveSmokescreen(_cardID, _cardID, true, false);
    
        Label_2060:
        cardID = _cardID;
    
        return;
    
        Label_2092:
        GetHandLocationBySide = UCombatHelperFunctions::GetHandLocationBySide(side, this);
    
        FetchCardsByLocation(GetHandLocationBySide, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        if (!skipAction)
            goto Label_2767;
    
        Label_2212:
        createdCard->getHasGameplayTag(FGameplayTag("autoplay"), CallFunc_getHasGameplayTag_hasTag);
    
        BooleanAND = CallFunc_getHasGameplayTag_hasTag && spawnCardInHand;
    
        Not_PreBool = !BooleanAND;
    
        BooleanAND_1 = Not_PreBool && wasFullBeforeCreating;
    
        if (!BooleanAND_1)
            goto Label_2441;
    
        createdCard->location = 0x8;
    
        Label_2441:
        if (!cardSeen)
            goto Label_2550;
    
        MakeArray_Array = [ true ];
    
        MakeArray_Array_1 = [ _cardID ];
    
        CardFunctionsNotifier->NotifyCardsSeen(MakeArray_Array_1, MakeArray_Array, false, false);
    
        goto Label_2060;
    
        Label_2550:
        if (!spawnCardInHand)
            return;
    
        ExecuteOnSpawnedInHandEvents(side, _cardID);
    
        createdCard->IsLocatedInHand(CallFunc_IsLocatedInHand_isIt);
    
        if (!CallFunc_IsLocatedInHand_isIt)
            return;
    
        createdCard->getHasGameplayTag(FGameplayTag("autoplay"), CallFunc_getHasGameplayTag_hasTag_1);
    
        if (!CallFunc_getHasGameplayTag_hasTag_1)
            return;
    
        GameStateRef->AddAutoPlayCards(_cardID);
    
        return;
    
        Label_2767:
        Subtract_IntInt = CallFunc_FetchCardsByLocation_QtyInLocation - 1;
    
        Greater_IntInt_1 = (CallFunc_FetchCardsByLocation_QtyInLocation > 9);
    
        Conv_NameToString = FString(cardName);
    
        CardFunctionsNotifier->NotifyDrawCardFromDeck(instigatorID, side, _cardID, Conv_NameToString, spawnCardInHand, skipDrawAnimation, Subtract_IntInt, Greater_IntInt_1, 0, newCardText, salvageInfo.salvagedCardID_8_60B10C4245C90998186E6E9E7E180468, fromOppositeSide, 0.4);
    
        goto Label_2212;
    
        Label_3043:
        CardFunctionsNotifier->NotifyAddToBattlelog(_cardID, instigatorID, HideFromOpponent, false);
    
        goto Label_2060;
    
        Label_3112:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ApplyFatigueDamage(ESideEnum sideToApply, bool fromBond, bool& destroyed)
    {
        GameStateRef->GetFatigueDamageBySide(sideToApply, CallFunc_GetFatigueDamageBySide_FatigueDamage);
    
        fatigueDamgeToApply = CallFunc_GetFatigueDamageBySide_FatigueDamage;
    
        goto Label_112;
    
        Label_112:
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card, CallFunc_GetLocationCardBySide_locationCardID, sideToApply);
    
        tmpLocationCard = CallFunc_GetLocationCardBySide_card;
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card, CallFunc_GetLocationCardBySide_locationCardID, sideToApply);
    
        cardID = CallFunc_GetLocationCardBySide_locationCardID;
    
        tmpLocationCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense_1);
    
        oldDefense = CallFunc_getTotalDefense_totalDefense_1;
    
        provideKeysAndFrameCount(CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        GameStateRef->GetFatigueDamageBySide(sideToApply, CallFunc_GetFatigueDamageBySide_FatigueDamage_1);
    
        Subtract_IntInt = oldDefense - CallFunc_GetFatigueDamageBySide_FatigueDamage_1;
    
        tmpLocationCard->setAndEncryptDefense(Subtract_IntInt, CallFunc_provideKeysAndFrameCount_key1, CallFunc_provideKeysAndFrameCount_key2, CallFunc_provideKeysAndFrameCount_frameCount);
    
        tmpLocationCard->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        LessEqual_IntInt = (CallFunc_getTotalDefense_totalDefense <= 0);
    
        tmpDestroy = LessEqual_IntInt;
    
        GameStateRef->IncrementFatigueDamageBySide(sideToApply);
    
        goto Label_657;
    
        Label_657:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_772;
    
        CardFunctionsNotifier->NotifyFatigueDamage(cardID, fatigueDamgeToApply, oldDefense, tmpDestroy, fromBond);
    
        goto Label_796;
    
        Label_772:
        UpdateBondVisuals(sideToApply);
    
        goto Label_1203;
    
        Label_796:
        FetchAllCardsWithEventTrigger(0x1A, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_867:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1222;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnFatigueDamage(sideToApply, fatigueDamgeToApply, fromBond);
    
        goto Label_1129;
    
        Label_1129:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_867;
    
        Label_1203:
        destroyed = tmpDestroy;
    
        Label_1222:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void HQ_DestroyedEndMatch(ESideEnum winningSide)
    {
        GetTheOtherSide = UCombatHelperFunctions::GetTheOtherSide(winningSide, this);
    
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card, CallFunc_GetLocationCardBySide_locationCardID, GetTheOtherSide);
    
        CardFunctionsNotifier->NotifyOnCardDestroyed(nullptr, CallFunc_GetLocationCardBySide_card);
    
        GameStateRef->GetMatchFinished(CallFunc_GetMatchFinished_OutFinished);
    
        if (!CallFunc_GetMatchFinished_OutFinished)
            goto Label_189;
    
        Label_184:
        return;
    
        Label_189:
        GameStateRef->SetMatchFinished(true);
    
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_184;
    
        CardFunctionsNotifier->NotifyEndMatchByDestroyingHQ(winningSide, "Victory_DestroyHQ");
    
        goto Label_184;
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RearrangeLocation(ECardLocationEnum location)
    {
        GameStateRef->FetchCardsByLocationSorted(location, CallFunc_FetchCardsByLocationSorted_cardIDs);
    
        _cardIDs = CallFunc_FetchCardsByLocationSorted_cardIDs;
    
        goto Label_92;
    
        Label_92:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_138:
        Array_Length = _cardIDs.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_452;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = _cardIDs[Temp_int_Array_Index_Variable];
    
        SetCardLocationAndLocNumber(CallFunc_Array_Get_Item, location, Temp_int_Array_Index_Variable);
    
        goto Label_378;
    
        Label_378:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_138;
    
        Label_452:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RefreshLocationStatus()
    {
        CallFunc_Set_ToArray_Result = [];
    
        Set_ToArray(affectedLocations, CallFunc_Set_ToArray_Result);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_112:
        Array_Length = CallFunc_Set_ToArray_Result.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_970;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_Set_ToArray_Result[Temp_int_Array_Index_Variable];
    
        SwitchEnum_CmpSuccess_1 = ((!CallFunc_Array_Get_Item) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_610;
    
        SwitchEnum_CmpSuccess_1 = ((!CallFunc_Array_Get_Item) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_610;
    
        SwitchEnum_CmpSuccess_1 = ((!CallFunc_Array_Get_Item) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_610;
    
        SwitchEnum_CmpSuccess_1 = ((!CallFunc_Array_Get_Item) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_610;
    
        SwitchEnum_CmpSuccess_1 = ((!CallFunc_Array_Get_Item) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess_1)
            goto Label_610;
    
        goto Label_536;
    
        Label_536:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_112;
    
        Label_610:
        CallFunc_Array_Get_Item = CallFunc_Set_ToArray_Result[Temp_int_Array_Index_Variable];
    
        RearrangeLocation(CallFunc_Array_Get_Item);
    
        CallFunc_Array_Get_Item = CallFunc_Set_ToArray_Result[Temp_int_Array_Index_Variable];
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_887;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_887;
    
        SwitchEnum_CmpSuccess = ((!CallFunc_Array_Get_Item) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_887;
    
        return;
    
        Label_887:
        CallFunc_Array_Get_Item = CallFunc_Set_ToArray_Result[Temp_int_Array_Index_Variable];
    
        UpdateGuarded(CallFunc_Array_Get_Item);
    
        return;
    
        Label_970:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ApplyDestroyMultipleCards(int destroyerCardID, TArray<int>*& cardsToDestroy)
    {
        GetCardFromID(destroyerCardID, CallFunc_GetCardFromID_card);
    
        _destroyerCard = CallFunc_GetCardFromID_card;
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_102:
        Array_Length_6 = cardsToDestroy.Length;
    
        Less_IntInt_5 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_6);
    
        if (!Less_IntInt_5)
            goto Label_674;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_5 = cardsToDestroy[Temp_int_Array_Index_Variable_2];
    
        ExecuteOnBeforeOtherCardDestroyed(CallFunc_Array_Get_Item_5, destroyerCardID, false, false);
    
        CallFunc_Array_Get_Item_5 = cardsToDestroy[Temp_int_Array_Index_Variable_2];
    
        GetCardFromID(CallFunc_Array_Get_Item_5, CallFunc_GetCardFromID_card_2);
    
        Map_Add(cardsToDestroyLocations, CallFunc_Array_Get_Item_5, CallFunc_GetCardFromID_card_2->location);
    
        CallFunc_Array_Get_Item_5 = cardsToDestroy[Temp_int_Array_Index_Variable_2];
    
        GetCardFromID(CallFunc_Array_Get_Item_5, CallFunc_GetCardFromID_card_2);
    
        Set_Add(affectedLocations, CallFunc_GetCardFromID_card_2->location);
    
        goto Label_2963;
    
        Label_674:
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_720:
        Array_Length_5 = cardsToDestroy.Length;
    
        Less_IntInt_4 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_5);
    
        if (!Less_IntInt_4)
            goto Label_1171;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_4 = cardsToDestroy[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item_4, CallFunc_GetCardFromID_card_1);
    
        NotEqual_ByteByte = ((!CallFunc_GetCardFromID_card_1->location) !== (!0x8));
    
        if (!NotEqual_ByteByte)
            goto Label_3111;
    
        CallFunc_Array_Get_Item_4 = cardsToDestroy[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item_4, CallFunc_GetCardFromID_card_1);
    
        ExecuteOnBeforeLeaveBoardOrOwnerEvents(CallFunc_Array_Get_Item_4, 0x8, CallFunc_GetCardFromID_card_1->location, 0x1);
    
        goto Label_3037;
    
        Label_1171:
        CardFunctionsNotifier->NotifyDestroyMultipleUnits(destroyerCardID, cardsToDestroyLocations);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_4 = 0;
    
        Label_1271:
        Array_Length_4 = cardsToDestroy.Length;
    
        Less_IntInt_3 = (Temp_int_Loop_Counter_Variable < Array_Length_4);
    
        if (!Less_IntInt_3)
            goto Label_1504;
    
        Temp_int_Array_Index_Variable_4 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_3 = cardsToDestroy[Temp_int_Array_Index_Variable_4];
    
        SetCardLocationAndLocNumber(CallFunc_Array_Get_Item_3, 0x8, 0);
    
        goto Label_3231;
    
        Label_1504:
        RefreshLocationStatus(affectedLocations);
    
        goto Label_1533;
    
        Label_1533:
        Temp_int_Loop_Counter_Variable_4 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1579:
        Array_Length_3 = cardsToDestroy.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable_4 < Array_Length_3);
    
        if (!Less_IntInt_2)
            goto Label_1888;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_4;
    
        CallFunc_Array_Get_Item_1 = cardsToDestroy[Temp_int_Array_Index_Variable_1];
    
        Map_Find_2 = Map_Find(cardsToDestroyLocations, CallFunc_Array_Get_Item_1, CallFunc_Map_Find_Value_2);
    
        ExecuteOnCardLocationMoved(CallFunc_Array_Get_Item_1, CallFunc_Map_Find_Value_2, 0x8, false, 0xA);
    
        goto Label_3305;
    
        Label_1888:
        Temp_int_Loop_Counter_Variable_5 = 0;
    
        Temp_int_Array_Index_Variable_3 = 0;
    
        Label_1934:
        Array_Length_2 = cardsToDestroy.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_5 < Array_Length_2);
    
        if (!Less_IntInt_1)
            goto Label_2240;
    
        Temp_int_Array_Index_Variable_3 = Temp_int_Loop_Counter_Variable_5;
    
        CallFunc_Array_Get_Item = cardsToDestroy[Temp_int_Array_Index_Variable_3];
    
        Map_Find = Map_Find(cardsToDestroyLocations, CallFunc_Array_Get_Item, CallFunc_Map_Find_Value);
    
        ExecuteOnAfterLeaveBoardOrOwnerEvents(CallFunc_Array_Get_Item, 0x8, CallFunc_Map_Find_Value);
    
        goto Label_3379;
    
        Label_2240:
        Temp_int_Loop_Counter_Variable_3 = 0;
    
        Temp_int_Array_Index_Variable_5 = 0;
    
        Label_2286:
        Array_Length_1 = cardsToDestroy.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_3 < Array_Length_1);
    
        if (!Less_IntInt)
            goto Label_2609;
    
        Temp_int_Array_Index_Variable_5 = Temp_int_Loop_Counter_Variable_3;
    
        CallFunc_Array_Get_Item_2 = cardsToDestroy[Temp_int_Array_Index_Variable_5];
    
        Map_Find_1 = Map_Find(cardsToDestroyLocations, CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value_1);
    
        ExecuteOnCardDestroyedFunction(CallFunc_Array_Get_Item_2, CallFunc_Map_Find_Value_1, destroyerCardID, cardsToDestroy, false);
    
        goto Label_3453;
    
        Label_2609:
        Temp_byte_Variable = 0x7;
    
        Set_Contains = Set_Contains(affectedLocations, Temp_byte_Variable);
    
        if (!Set_Contains)
            goto Label_2724;
    
        UpdateFrontlineIfNeeded(0);
    
        goto Label_3527;
    
        Label_2724:
        Array_Length = cardsToDestroy.Length;
    
        GreaterEqual_IntInt = (Array_Length >= 10);
    
        EqualEqual_NameName = _destroyerCard->name == "card_event_to_the_last_man";
    
        BooleanAND = EqualEqual_NameName && GreaterEqual_IntInt;
    
        if (!BooleanAND)
            return;
    
        GameStateRef->LastManKilled10 = true;
    
        return;
    
        Label_2963:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_102;
    
        Label_3037:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_720;
    
        Label_3111:
        CallFunc_Array_Get_Item_4 = cardsToDestroy[Temp_int_Array_Index_Variable];
    
        Map_Remove = cardsToDestroyLocations.Remove(CallFunc_Array_Get_Item_4);
    
        return;
    
        Label_3231:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_1271;
    
        Label_3305:
        Add_IntInt_4 = Temp_int_Loop_Counter_Variable_4 + 1;
    
        Temp_int_Loop_Counter_Variable_4 = Add_IntInt_4;
    
        goto Label_1579;
    
        Label_3379:
        Add_IntInt_5 = Temp_int_Loop_Counter_Variable_5 + 1;
    
        Temp_int_Loop_Counter_Variable_5 = Add_IntInt_5;
    
        goto Label_1934;
    
        Label_3453:
        Add_IntInt_3 = Temp_int_Loop_Counter_Variable_3 + 1;
    
        Temp_int_Loop_Counter_Variable_3 = Add_IntInt_3;
    
        goto Label_2286;
    
        Label_3527:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void SetCardLocationAndLocNumber(int cardID, ECardLocationEnum Location, int LocationNumber)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        tmpCardToSet = CallFunc_GetCardFromID_card;
    
        IsValid = tmpCardToSet;
    
        if (!IsValid)
            goto Label_215;
    
        tmpCardToSet->location = Location;
    
        EqualEqual_ByteByte = ((!tmpCardToSet->location) == (!0x8));
    
        if (!EqualEqual_ByteByte)
            goto Label_323;
    
        return;
    
        Label_215:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("[Set Card Location and Loc Number] is called on an invalid card!", this);
    
        return;
    
        Label_323:
        tmpCardToSet->locationNumber = LocationNumber;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void FetchCardsByLocation(ECardLocationEnum location, int& QtyInLocation, bool& isLocationFull, TArray<class UBaseCardObject*>& AllCardsInLocation, class UBaseCardObject*& FirstCard, TArray<int>& fetchedCardsIDs)
    {
        MaxQty = 9;
    
        TmpQty = 9;
    
        GameStateRef->FetchCardsByLocation(location, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        QtyInLocation = CallFunc_FetchCardsByLocation_QtyInLocation;
    
        isLocationFull = CallFunc_FetchCardsByLocation_isLocationFull;
    
        AllCardsInLocation = CallFunc_FetchCardsByLocation_AllCardsInLocation;
    
        FirstCard = CallFunc_FetchCardsByLocation_FirstCard;
    
        fetchedCardsIDs = CallFunc_FetchCardsByLocation_fetchedCardsIDs;
    
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void IsActionProcess(bool& ActionProcess)
    {
        GameStateRef->IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        ActionProcess = CallFunc_IsActionProcess_ActionProcess;
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void UpdateGuarded(ECardLocationEnum location)
    {
        EqualEqual_ByteByte = ((!location) == (!0x7));
    
        EqualEqual_ByteByte_1 = ((!location) == (!0x6));
    
        EqualEqual_ByteByte_2 = ((!location) == (!0x5));
    
        BooleanOR = (EqualEqual_ByteByte_2 || EqualEqual_ByteByte_1);
    
        BooleanOR_1 = (BooleanOR || EqualEqual_ByteByte);
    
        if (!BooleanOR_1)
            goto Label_752;
    
        FetchCardsByLocation(location, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_302:
        Array_Length = CallFunc_FetchCardsByLocation_AllCardsInLocation.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_757;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchCardsByLocation_AllCardsInLocation[Temp_int_Array_Index_Variable];
    
        _currentCard = CallFunc_Array_Get_Item;
    
        _currentCard->getHasGuard(CallFunc_getHasGuard_doesIt);
    
        _currentCard->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        Not_PreBool_1 = !CallFunc_IsUnrevealedCovertCard_isIt;
    
        BooleanAND = CallFunc_getHasGuard_doesIt && Not_PreBool_1;
    
        if (!BooleanAND)
            goto Label_836;
    
        if (!_currentCard->isBeingGuarded)
            goto Label_762;
    
        _currentCard->isBeingGuarded = false;
    
        goto Label_1621;
    
        Label_752:
        return;
    
        Label_757:
        return;
    
        Label_762:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_302;
    
        Label_836:
        _removeGuarded = true;
    
        GetAdjacentCards(_currentCard, true, CallFunc_GetAdjacentCards_adjacentCards);
    
        Temp_bool_True_if_break_was_hit_Variable = false;
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_937:
        Not_PreBool = !Temp_bool_True_if_break_was_hit_Variable;
    
        Array_Length_1 = CallFunc_GetAdjacentCards_adjacentCards.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        BooleanAND_3 = Not_PreBool && Less_IntInt_1;
    
        if (!BooleanAND_3)
            goto Label_1517;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item_1 = CallFunc_GetAdjacentCards_adjacentCards[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_1->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt_1);
    
        Not_PreBool_2 = !CallFunc_IsUnrevealedCovertCard_isIt_1;
    
        BooleanAND_2 = CallFunc_Array_Get_Item_1->hasGuard && Not_PreBool_2;
    
        if (!BooleanAND_2)
            goto Label_1443;
    
        if (!_currentCard->isBeingGuarded)
            goto Label_1405;
    
        Label_1382:
        _removeGuarded = false;
    
        Temp_bool_True_if_break_was_hit_Variable = true;
    
        return;
    
        Label_1405:
        _currentCard->isBeingGuarded = true;
    
        goto Label_1382;
    
        Label_1443:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_937;
    
        Label_1517:
        BooleanAND_1 = _removeGuarded && _currentCard->isBeingGuarded;
    
        if (!BooleanAND_1)
            return;
    
        _currentCard->isBeingGuarded = false;
    
        return;
    
        Label_1621:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnOtherCardsAbilitiesChanged(class UBaseCardObject* CardChanging)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_427;
    
        FetchAllCardsWithEventTrigger(0x1D, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_109:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardAbilitiesChanged(CardChanging);
    
        goto Label_353;
    
        Label_353:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_109;
    
        Label_427:
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void ConstructAndCopyCard(class UBaseCardObject* card, class UBaseCardObject*& cardObject)
    {
        GetObjectClass = UGameplayStatics::GetObjectClass(card);
    
        IsValidClass = GetObjectClass;
    
        if (!IsValidClass)
            goto Label_196;
    
        GetObjectClass = UGameplayStatics::GetObjectClass(card);
    
        SpawnObject = UGameplayStatics::SpawnObject(GetObjectClass, this);
    
        card->CopyData(SpawnObject);
    
        cardObject = SpawnObject;
    
        return;
    
        Label_196:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("CopyCard: Did not find card class for card: ", this);
    
        cardObject = nullptr;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetNextCardLocationNumber(ECardLocationEnum location, int& locationNumber)
    {
        SwitchEnum_CmpSuccess = ((!location) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_455;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_455;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_455;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_483;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_483;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_483;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_483;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_483;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_455;
    
        SwitchEnum_CmpSuccess = ((!location) !== (!0x9));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_455;
    
        return;
    
        Label_455:
        locationNumber = 0;
    
        return;
    
        Label_483:
        FetchCardsByLocation(location, CallFunc_FetchCardsByLocation_QtyInLocation, CallFunc_FetchCardsByLocation_isLocationFull, CallFunc_FetchCardsByLocation_AllCardsInLocation, CallFunc_FetchCardsByLocation_FirstCard, CallFunc_FetchCardsByLocation_fetchedCardsIDs);
    
        locationNumber = CallFunc_FetchCardsByLocation_QtyInLocation;
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemovePincerEffects(class UBaseCardObject* cardLeaving)
    {
        JSON_GetInt(cardLeaving, "pincer_receiver", CallFunc_JSON_GetInt_value, CallFunc_JSON_GetInt_found);
    
        if (!CallFunc_JSON_GetInt_found)
            goto Label_712;
    
        GetCardFromID(CallFunc_JSON_GetInt_value, CallFunc_GetCardFromID_card_2);
    
        cardLeaving->OnPincerEffectRemoved(CallFunc_GetCardFromID_card_2);
    
        cardLeaving->OnPincerEffectRemoved(cardLeaving);
    
        GetCardFromID(CallFunc_JSON_GetInt_value, CallFunc_GetCardFromID_card_2);
    
        JSON_RemoveFromIntArray(CallFunc_GetCardFromID_card_2, "pincer_givers", cardLeaving->cardID, CallFunc_JSON_RemoveFromIntArray_found);
    
        GetCardFromID(CallFunc_JSON_GetInt_value, CallFunc_GetCardFromID_card_2);
    
        JSON_GetIntArray(CallFunc_GetCardFromID_card_2, "pincer_givers", CallFunc_JSON_GetIntArray_values_1, CallFunc_JSON_GetIntArray_found_1);
    
        Array_Length_1 = CallFunc_JSON_GetIntArray_values_1.Length;
    
        EqualEqual_IntInt = Array_Length_1 == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_584;
    
        GetCardFromID(CallFunc_JSON_GetInt_value, CallFunc_GetCardFromID_card_2);
    
        JSON_Clear(CallFunc_GetCardFromID_card_2, "pincer_givers", CallFunc_JSON_Clear_found_3);
    
        Label_584:
        JSON_Clear(cardLeaving, "pincer_receiver", CallFunc_JSON_Clear_found);
    
        GetCardFromID(CallFunc_JSON_GetInt_value, CallFunc_GetCardFromID_card_2);
    
        PersistCustomFields(CallFunc_GetCardFromID_card_2->cardID, true);
    
        goto Label_1675;
    
        Label_712:
        GetCardFromID(cardLeaving->cardID, CallFunc_GetCardFromID_card);
    
        JSON_GetIntArray(CallFunc_GetCardFromID_card, "pincer_givers", CallFunc_JSON_GetIntArray_values, CallFunc_JSON_GetIntArray_found);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_868:
        Array_Length = CallFunc_JSON_GetIntArray_values.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1507;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_JSON_GetIntArray_values[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card_1);
    
        CallFunc_GetCardFromID_card_1->OnPincerEffectRemoved(CallFunc_GetCardFromID_card_1);
    
        CallFunc_Array_Get_Item = CallFunc_JSON_GetIntArray_values[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card_1);
    
        CallFunc_GetCardFromID_card_1->OnPincerEffectRemoved(cardLeaving);
    
        CallFunc_Array_Get_Item = CallFunc_JSON_GetIntArray_values[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card_1);
    
        JSON_Clear(CallFunc_GetCardFromID_card_1, "pincer_receiver", CallFunc_JSON_Clear_found_2);
    
        CallFunc_Array_Get_Item = CallFunc_JSON_GetIntArray_values[Temp_int_Array_Index_Variable];
    
        PersistCustomFields(CallFunc_Array_Get_Item, true);
    
        goto Label_1601;
    
        Label_1507:
        JSON_Clear(cardLeaving, "pincer_givers", CallFunc_JSON_Clear_found_1);
    
        PersistCustomFields(cardLeaving->cardID, true);
    
        return;
    
        Label_1601:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_868;
    
        Label_1675:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveAlpineBonus(class UBaseCardObject* card)
    {
        CanCardBeBuffed(card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_1175;
    
        card->getHasAlpine(CallFunc_getHasAlpine_doesIt);
    
        card->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        card->getTotalDefense(CallFunc_getTotalDefense_totalDefense);
    
        Greater_IntInt = (CallFunc_getTotalDefense_totalDefense > 0);
    
        BooleanAND = CallFunc_IsLocatedOnBoard_isIt && Greater_IntInt;
    
        BooleanAND_1 = BooleanAND && CallFunc_getHasAlpine_doesIt;
    
        if (!BooleanAND_1)
            return;
    
        GetAllUnitsOnBoard(false, CallFunc_GetAllUnitsOnBoard_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_360:
        Array_Length = CallFunc_GetAllUnitsOnBoard_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_906;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_GetAllUnitsOnBoard_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->getHasAlpine(CallFunc_getHasAlpine_doesIt_1);
    
        EqualEqual_ByteByte = ((!CallFunc_Array_Get_Item->side) == (!card->side));
    
        NotEqual_ObjectObject = (CallFunc_Array_Get_Item !== card);
    
        BooleanAND_2 = CallFunc_getHasAlpine_doesIt_1 && NotEqual_ObjectObject;
    
        BooleanAND_3 = BooleanAND_2 && EqualEqual_ByteByte;
    
        if (!BooleanAND_3)
            goto Label_1101;
    
        Add_IntInt_1 = bonus + 1;
    
        Temp_int_Variable = Add_IntInt_1;
    
        bonus = Temp_int_Variable;
    
        return;
    
        Label_906:
        Greater_IntInt_1 = (bonus > 0);
    
        if (!Greater_IntInt_1)
            return;
    
        ChangeAttack(card, card->cardID, bonus, 0x1, false, CallFunc_ChangeAttack_qqq);
    
        ChangeDefense(card, card->cardID, bonus, 0x1, false, CallFunc_ChangeDefense_qqq);
    
        return;
    
        Label_1101:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_360;
    
        Label_1175:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void OnNavalEngagementPlayed(class UBaseCardObject* card)
    {
        mySupportLineUnits = 0;
    
        enemySupportLineUnits = 0;
    
        GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        EqualEqual_ByteByte = ((!card->side) == (!CallFunc_GetClientSide_OutClientSide));
    
        if (!EqualEqual_ByteByte)
            return;
    
        GetClientSide(CallFunc_GetClientSide_OutClientSide_1);
    
        GetCardsInSupportLineBySide(CallFunc_GetClientSide_OutClientSide_1, false, true, CallFunc_GetCardsInSupportLineBySide_cards_1);
    
        Array_Length_1 = CallFunc_GetCardsInSupportLineBySide_cards_1.Length;
    
        mySupportLineUnits = Array_Length_1;
    
        GetOpponentSide(CallFunc_GetOpponentSide_OutOpponentSide);
    
        GetCardsInSupportLineBySide(CallFunc_GetOpponentSide_OutOpponentSide, false, true, CallFunc_GetCardsInSupportLineBySide_cards);
    
        Array_Length = CallFunc_GetCardsInSupportLineBySide_cards.Length;
    
        enemySupportLineUnits = Array_Length;
    
        EqualEqual_IntInt = enemySupportLineUnits == 5;
    
        EqualEqual_IntInt_1 = mySupportLineUnits == 5;
    
        BooleanAND = EqualEqual_IntInt_1 && EqualEqual_IntInt;
    
        if (!BooleanAND)
            return;
    
        GameStateRef->navalEngagementFull = true;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void CreateLocationNumberGapForCard(TArray<int>*& cardsInLocation, int locationNumber, int cardID)
    {
        Array_Contains = cardsInLocation[cardID];
    
        if (!Array_Contains)
            goto Label_628;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_126:
        Array_Length_1 = cardsInLocation.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_1362;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = cardsInLocation[Temp_int_Array_Index_Variable_1];
    
        NotEqual_IntInt = (cardID !== CallFunc_Array_Get_Item_1);
    
        if (!NotEqual_IntInt)
            goto Label_1288;
    
        CallFunc_Array_Get_Item_1 = cardsInLocation[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_1, CallFunc_GetCardFromID_card_1);
    
        _otherCard = CallFunc_GetCardFromID_card_1;
    
        _otherCard->locationNumber = tmpLocationNumber;
    
        Add_IntInt_2 = tmpLocationNumber + 1;
    
        Temp_int_Variable = Add_IntInt_2;
    
        tmpLocationNumber = Temp_int_Variable;
    
        return;
    
        Label_628:
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_674:
        Array_Length = cardsInLocation.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = cardsInLocation[Temp_int_Array_Index_Variable];
    
        NotEqual_IntInt_1 = (cardID !== CallFunc_Array_Get_Item);
    
        if (!NotEqual_IntInt_1)
            goto Label_1214;
    
        CallFunc_Array_Get_Item = cardsInLocation[Temp_int_Array_Index_Variable];
    
        GetCardFromID(CallFunc_Array_Get_Item, CallFunc_GetCardFromID_card);
    
        _otherCard = CallFunc_GetCardFromID_card;
    
        GreaterEqual_IntInt = (_otherCard->locationNumber >= locationNumber);
    
        if (!GreaterEqual_IntInt)
            return;
    
        Add_IntInt_3 = _otherCard->locationNumber + 1;
    
        _otherCard->locationNumber = Add_IntInt_3;
    
        return;
    
        Label_1214:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_674;
    
        Label_1288:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_126;
    
        Label_1362:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SortCardsByLocationNumber(TArray<class UBaseCardObject*>*& cardsToSort, TArray<class UBaseCardObject*>& sortedCards)
    {
        GameStateRef->SortCardsByLocationNumber(cardsToSort, CallFunc_SortCardsByLocationNumber_sortedCards);
    
        sortedCards = CallFunc_SortCardsByLocationNumber_sortedCards;
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void InjectCardIntoLocation(ECardLocationEnum location, int locationNumber, int cardID)
    {
        GameStateRef->FetchCardsByLocationSorted(location, CallFunc_FetchCardsByLocationSorted_cardIDs);
    
        CreateLocationNumberGapForCard(CallFunc_FetchCardsByLocationSorted_cardIDs, locationNumber, cardID);
    
        SetCardLocationAndLocNumber(cardID, location, locationNumber);
    
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void UpdateHQ_DamagedAmountThisTurnIfNeeded(int CardID_ToCheck, int DamagedAmount)
    {
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card_1, CallFunc_GetLocationCardBySide_locationCardID_1, 0x1);
    
        EqualEqual_IntInt_1 = CardID_ToCheck == CallFunc_GetLocationCardBySide_locationCardID_1;
    
        if (!EqualEqual_IntInt_1)
            goto Label_138;
    
        GameStateRef->UpdateHQ_DamagedAmountThisTurn(0x1, DamagedAmount);
    
        return;
    
        Label_138:
        GetLocationCardBySide(CallFunc_GetLocationCardBySide_card, CallFunc_GetLocationCardBySide_locationCardID, 0x2);
    
        EqualEqual_IntInt = CardID_ToCheck == CallFunc_GetLocationCardBySide_locationCardID;
    
        if (!EqualEqual_IntInt)
            return;
    
        GameStateRef->UpdateHQ_DamagedAmountThisTurn(0x2, DamagedAmount);
    
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void KreditCheckAndAutoBanIfNeeded()
    {
        GetEngineSubsystem = USubsystemBlueprintLibrary::GetEngineSubsystem(FindObject<UClass>(nullptr, "/Script/KardsSubsystems.ConfigSubsystem"));
    
        GetInt = GetEngineSubsystem->GetInt("can_autoban_players_kredit_check", CallFunc_GetInt_Value);
    
        if (!GetInt)
            return;
    
        GetEngineSubsystem = USubsystemBlueprintLibrary::GetEngineSubsystem(FindObject<UClass>(nullptr, "/Script/KardsSubsystems.ConfigSubsystem"));
    
        GetInt = GetEngineSubsystem->GetInt("can_autoban_players_kredit_check", CallFunc_GetInt_Value);
    
        Conv_IntToBool = (CallFunc_GetInt_Value != 0);
    
        if (!Conv_IntToBool)
            return;
    
        GameStateRef->GetOpponentSide(CallFunc_GetOpponentSide_OutOpponentSide);
    
        GameStateRef->getKreditSlotBySide(CallFunc_GetOpponentSide_OutOpponentSide, CallFunc_getKreditSlotBySide_outputKreditSlot_1);
    
        GreaterEqual_IntInt_2 = (CallFunc_getKreditSlotBySide_outputKreditSlot_1 >= 30);
    
        GameStateRef->GetClientSide(CallFunc_GetClientSide_OutClientSide_1);
    
        GameStateRef->getKreditBySide(CallFunc_GetClientSide_OutClientSide_1, CallFunc_getKreditBySide_outputKredit_1);
    
        GreaterEqual_IntInt_3 = (CallFunc_getKreditBySide_outputKredit_1 >= 30);
    
        BooleanOR_1 = (GreaterEqual_IntInt_3 || GreaterEqual_IntInt_2);
    
        if (!BooleanOR_1)
            goto Label_683;
    
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Match ongoing 10", this);
    
        Label_642:
        CardFunctionsNotifier->NotifyFatalHeartbeat();
    
        return;
    
        Label_683:
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        LessEqual_IntInt = (CallFunc_GetTurnNumber_turnNumber <= 8);
    
        if (!LessEqual_IntInt)
            return;
    
        GameStateRef->GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        GameStateRef->getKreditSlotBySide(CallFunc_GetClientSide_OutClientSide, CallFunc_getKreditSlotBySide_outputKreditSlot);
    
        GreaterEqual_IntInt = (CallFunc_getKreditSlotBySide_outputKreditSlot >= 24);
    
        GameStateRef->getKreditBySide(CallFunc_GetClientSide_OutClientSide, CallFunc_getKreditBySide_outputKredit);
    
        GreaterEqual_IntInt_1 = (CallFunc_getKreditBySide_outputKredit >= 24);
    
        BooleanOR = (GreaterEqual_IntInt_1 || GreaterEqual_IntInt);
    
        if (!BooleanOR)
            return;
    
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("Match ongoing 11", this);
    
        goto Label_642;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetActiveGotchasOrdered(TArray<int>& cardIDs)
    {
        backUpNextGotcha = 100;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_74:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        Array_Length = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_518;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        EqualEqual_NameName = CallFunc_Array_Get_Item->name == "card_event_careless_talk";
    
        if (!EqualEqual_NameName)
            goto Label_1086;
    
        UKismetSystemLibrary::PrintString(this, "bingo", true, true, FLinearColor(0, 0.66, 1, 1), 2, "None");
    
        goto Label_1012;
    
        Label_518:
        CallFunc_Map_Keys_Keys = [];
    
        Map_Keys(activeGotchas, CallFunc_Map_Keys_Keys);
    
        keys = CallFunc_Map_Keys_Keys;
    
        Label_606:
        Array_Length_1 = keys.Length;
    
        Greater_IntInt_1 = (Array_Length_1 > 0);
    
        if (!Greater_IntInt_1)
            goto Label_980;
    
        UKismetMathLibrary::MinOfIntArray(keys, CallFunc_MinOfIntArray_IndexOfMinValue, CallFunc_MinOfIntArray_MinValue);
    
        Map_Find_1 = Map_Find(activeGotchas, CallFunc_MinOfIntArray_MinValue, CallFunc_Map_Find_Value_1);
    
        Array_Add = orderedCards.Add(CallFunc_Map_Find_Value_1);
    
        UKismetMathLibrary::MinOfIntArray(keys, CallFunc_MinOfIntArray_IndexOfMinValue, CallFunc_MinOfIntArray_MinValue);
    
        keys.Remove(CallFunc_MinOfIntArray_IndexOfMinValue);
    
        goto Label_606;
    
        Label_980:
        cardIDs = orderedCards;
    
        return;
    
        Label_1012:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_74;
    
        Label_1086:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Greater_IntInt = (CallFunc_Array_Get_Item->gotchaActivated > 0);
    
        CallFunc_Array_Get_Item->IsGotcha(CallFunc_IsGotcha_isIt);
    
        BooleanAND = CallFunc_IsGotcha_isIt && Greater_IntInt;
    
        if (!BooleanAND)
            goto Label_3623;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        EqualEqual_NameName_2 = CallFunc_Array_Get_Item->name == "card_event_interception";
    
        if (!EqualEqual_NameName_2)
            goto Label_1767;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Multiply_IntInt_1 = (CallFunc_Array_Get_Item->cardID * -1);
    
        Map_Add(activeGotchas, Multiply_IntInt_1, CallFunc_Array_Get_Item->cardID);
    
        return;
    
        Label_1767:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        EqualEqual_NameName_1 = CallFunc_Array_Get_Item->name == "card_event_ultra";
    
        if (!EqualEqual_NameName_1)
            goto Label_2241;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Add_IntInt_1 = CallFunc_Array_Get_Item->cardID + 1000000;
    
        Multiply_IntInt = (Add_IntInt_1 * -1);
    
        Map_Add(activeGotchas, Multiply_IntInt, CallFunc_Array_Get_Item->cardID);
    
        return;
    
        Label_2241:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Map_Find = Map_Find(activeGotchas, CallFunc_Array_Get_Item->gotchaActivated, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_3415;
    
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Conv_IntToString = FString(CallFunc_Array_Get_Item->cardID);
    
        Concat_StrStr = "Error: two gotchas w same number, IDs: " += Conv_IntToString;
    
        Concat_StrStr_1 = Concat_StrStr += ", and: ";
    
        Map_Find = Map_Find(activeGotchas, CallFunc_Array_Get_Item->gotchaActivated, CallFunc_Map_Find_Value);
    
        Conv_IntToString_1 = FString(CallFunc_Map_Find_Value);
    
        Concat_StrStr_2 = Concat_StrStr_1 += Conv_IntToString_1;
    
        UKismetSystemLibrary::PrintString(this, Concat_StrStr_2, true, true, FLinearColor(0, 0.66, 1, 1), 2, "None");
    
        Map_Contains = activeGotchas[backUpNextGotcha];
    
        if (!Map_Contains)
            goto Label_3160;
    
        GetGameInstanceSubsystem = USubsystemBlueprintLibrary::GetGameInstanceSubsystem(this, FindObject<UClass>(nullptr, "/Script/KardsSubsystems.LoggerSubsystem"));
    
        GetGameInstanceSubsystem->LogError("BACKUP GOTCHA ACTIVATED NOW WORKING", false);
    
        return;
    
        Label_3160:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Map_Add(activeGotchas, backUpNextGotcha, CallFunc_Array_Get_Item->cardID);
    
        Add_IntInt_2 = backUpNextGotcha + 1;
    
        backUpNextGotcha = Add_IntInt_2;
    
        return;
    
        Label_3415:
        GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);
    
        CallFunc_Array_Get_Item = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable];
    
        Map_Add(activeGotchas, CallFunc_Array_Get_Item->gotchaActivated, CallFunc_Array_Get_Item->cardID);
    
        return;
    
        Label_3623:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void RemoveBuffsEndOfTurn()
    {
        GameStateRef->GetBuffsToRemoveEndOfTurn(CallFunc_GetBuffsToRemoveEndOfTurn_BuffsToRemove_1);
    
        Map_IsNotEmpty = Map_IsNotEmpty(CallFunc_GetBuffsToRemoveEndOfTurn_BuffsToRemove_1);
    
        if (!Map_IsNotEmpty)
            goto Label_1641;
    
        GameStateRef->GetBuffsToRemoveEndOfTurn(CallFunc_GetBuffsToRemoveEndOfTurn_BuffsToRemove_1);
    
        CallFunc_Map_Keys_Keys = [];
    
        Map_Keys(CallFunc_GetBuffsToRemoveEndOfTurn_BuffsToRemove_1, CallFunc_Map_Keys_Keys);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable_2 = 0;
    
        Label_267:
        Array_Length = CallFunc_Map_Keys_Keys.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable_1 < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1646;
    
        Temp_int_Array_Index_Variable_2 = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = CallFunc_Map_Keys_Keys[Temp_int_Array_Index_Variable_2];
    
        buffType = CallFunc_Array_Get_Item;
    
        GameStateRef->GetBuffsToRemoveEndOfTurn(CallFunc_GetBuffsToRemoveEndOfTurn_BuffsToRemove);
    
        Map_Find = Map_Find(CallFunc_GetBuffsToRemoveEndOfTurn_BuffsToRemove, buffType, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1683;
    
        GameStateRef->GetBuffsToRemoveEndOfTurn(CallFunc_GetBuffsToRemoveEndOfTurn_BuffsToRemove);
    
        Map_Find = Map_Find(CallFunc_GetBuffsToRemoveEndOfTurn_BuffsToRemove, buffType, CallFunc_Map_Find_Value);
    
        instigatorArray = CallFunc_Map_Find_Value.CardIDs;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_816:
        Array_Length_2 = instigatorArray.Length;
    
        Less_IntInt_2 = (Temp_int_Loop_Counter_Variable < Array_Length_2);
    
        if (!Less_IntInt_2)
            goto Label_1955;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_2 = instigatorArray[Temp_int_Array_Index_Variable];
    
        tempInstigatorID = CallFunc_Array_Get_Item_2;
    
        GetCardFromID(tempInstigatorID, CallFunc_GetCardFromID_card);
    
        tempInstigator = CallFunc_GetCardFromID_card;
    
        IsValid = tempInstigator;
    
        if (!IsValid)
            goto Label_1757;
    
        CallFunc_getCardsBuffedByThisCard_cards = [];
    
        tempInstigator->getCardsBuffedByThisCard(CallFunc_getCardsBuffedByThisCard_cards);
    
        buffedCards = CallFunc_getCardsBuffedByThisCard_cards;
    
        Temp_int_Loop_Counter_Variable_2 = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_1256:
        Array_Length_1 = buffedCards.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_2 < Array_Length_1);
    
        if (!Less_IntInt_1)
            return;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable_2;
    
        CallFunc_Array_Get_Item_1 = buffedCards[Temp_int_Array_Index_Variable_1];
    
        GetCardFromID(CallFunc_Array_Get_Item_1, CallFunc_GetCardFromID_card_1);
    
        tempBuffedCard = CallFunc_GetCardFromID_card_1;
    
        IsValid_1 = tempBuffedCard;
    
        if (!IsValid_1)
            goto Label_1831;
    
        tempBuffedCard->IsLocatedOnBoard(CallFunc_IsLocatedOnBoard_isIt);
    
        if (!CallFunc_IsLocatedOnBoard_isIt)
            return;
    
        SwitchEnum_CmpSuccess = ((!buffType) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1905;
    
        return;
    
        Label_1641:
        return;
    
        Label_1646:
        GameStateRef->ClearBuffsToRemoveEndOfTurn();
    
        return;
    
        Label_1683:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_267;
    
        Label_1757:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_816;
    
        Label_1831:
        Add_IntInt_2 = Temp_int_Loop_Counter_Variable_2 + 1;
    
        Temp_int_Loop_Counter_Variable_2 = Add_IntInt_2;
    
        goto Label_1256;
    
        Label_1905:
        ChangeAttack(tempBuffedCard, tempInstigatorID, 0, 0x4, false, CallFunc_ChangeAttack_qqq);
    
        return;
    
        Label_1955:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetNewLocationNumbers(TArray<class UBaseCardObject*>*& cardsToRetreat, TArray<class UBaseCardObject*>*& cardsInSupportline, TMap<int, int>& cardIdToLocationNumber)
    {
        Array_Length = cardsInSupportline.Length;
    
        SwitchInteger_CmpSuccess = (Array_Length !== 1);
    
        if (!SwitchInteger_CmpSuccess)
            goto Label_305;
    
        SwitchInteger_CmpSuccess = (Array_Length !== 2);
    
        if (!SwitchInteger_CmpSuccess)
            goto Label_1565;
    
        SwitchInteger_CmpSuccess = (Array_Length !== 3);
    
        if (!SwitchInteger_CmpSuccess)
            goto Label_2062;
    
        SwitchInteger_CmpSuccess = (Array_Length !== 4);
    
        if (!SwitchInteger_CmpSuccess)
            goto Label_2675;
    
        SwitchInteger_CmpSuccess = (Array_Length !== 5);
    
        if (!SwitchInteger_CmpSuccess)
            goto Label_3293;
    
        goto Label_4003;
    
        Label_305:
        Array_Length_2 = cardsToRetreat.Length;
    
        SwitchInteger_CmpSuccess_4 = (Array_Length_2 !== 1);
    
        if (!SwitchInteger_CmpSuccess_4)
            goto Label_605;
    
        SwitchInteger_CmpSuccess_4 = (Array_Length_2 !== 2);
    
        if (!SwitchInteger_CmpSuccess_4)
            goto Label_3340;
    
        SwitchInteger_CmpSuccess_4 = (Array_Length_2 !== 3);
    
        if (!SwitchInteger_CmpSuccess_4)
            goto Label_3436;
    
        SwitchInteger_CmpSuccess_4 = (Array_Length_2 !== 4);
    
        if (!SwitchInteger_CmpSuccess_4)
            goto Label_3537;
    
        SwitchInteger_CmpSuccess_4 = (Array_Length_2 !== 5);
    
        if (!SwitchInteger_CmpSuccess_4)
            goto Label_3537;
    
        return;
    
        Label_605:
        MakeArray_Array_27 = [ 1 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_27;
    
        MakeArray_Array_13 = [ 0 ];
    
        supportlineLocationNumbers = MakeArray_Array_13;
    
        Label_691:
        SortCardsByLocationNumber(cardsToRetreat, CallFunc_SortCardsByLocationNumber_sortedCards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable_1 = 0;
    
        Label_769:
        Array_Length_3 = retreatCardsLocationNumbers.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length_3);
    
        if (!Less_IntInt)
            goto Label_1112;
    
        Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_1 = CallFunc_SortCardsByLocationNumber_sortedCards[Temp_int_Array_Index_Variable_1];
    
        CallFunc_Array_Get_Item_2 = retreatCardsLocationNumbers[Temp_int_Array_Index_Variable_1];
    
        Map_Add(tmpMap, CallFunc_Array_Get_Item_1->cardID, CallFunc_Array_Get_Item_2);
    
        goto Label_3643;
    
        Label_1112:
        SortCardsByLocationNumber(Temp_object_Variable, CallFunc_SortCardsByLocationNumber_sortedCards_1);
    
        Temp_int_Loop_Counter_Variable_1 = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_1190:
        Array_Length_1 = supportlineLocationNumbers.Length;
    
        Less_IntInt_1 = (Temp_int_Loop_Counter_Variable_1 < Array_Length_1);
    
        if (!Less_IntInt_1)
            goto Label_1533;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable_1;
    
        CallFunc_Array_Get_Item = supportlineLocationNumbers[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_3 = CallFunc_SortCardsByLocationNumber_sortedCards_1[Temp_int_Array_Index_Variable];
    
        Map_Add(tmpMap, CallFunc_Array_Get_Item_3->cardID, CallFunc_Array_Get_Item);
    
        goto Label_3717;
    
        Label_1533:
        cardIdToLocationNumber = tmpMap;
    
        return;
    
        Label_1565:
        Array_Length_2 = cardsToRetreat.Length;
    
        SwitchInteger_CmpSuccess_3 = (Array_Length_2 !== 1);
    
        if (!SwitchInteger_CmpSuccess_3)
            goto Label_1966;
    
        SwitchInteger_CmpSuccess_3 = (Array_Length_2 !== 2);
    
        if (!SwitchInteger_CmpSuccess_3)
            goto Label_1865;
    
        SwitchInteger_CmpSuccess_3 = (Array_Length_2 !== 3);
    
        if (!SwitchInteger_CmpSuccess_3)
            goto Label_3791;
    
        SwitchInteger_CmpSuccess_3 = (Array_Length_2 !== 4);
    
        if (!SwitchInteger_CmpSuccess_3)
            goto Label_3791;
    
        SwitchInteger_CmpSuccess_3 = (Array_Length_2 !== 5);
    
        if (!SwitchInteger_CmpSuccess_3)
            goto Label_3897;
    
        return;
    
        Label_1865:
        MakeArray_Array_22 = [ 1, 3 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_22;
    
        MakeArray_Array_8 = [ 0, 2 ];
    
        supportlineLocationNumbers = MakeArray_Array_8;
    
        goto Label_691;
    
        Label_1966:
        MakeArray_Array_23 = [ 1 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_23;
    
        MakeArray_Array_9 = [ 0, 2 ];
    
        supportlineLocationNumbers = MakeArray_Array_9;
    
        goto Label_691;
    
        Label_2062:
        Array_Length_2 = cardsToRetreat.Length;
    
        SwitchInteger_CmpSuccess_2 = (Array_Length_2 !== 1);
    
        if (!SwitchInteger_CmpSuccess_2)
            goto Label_2574;
    
        SwitchInteger_CmpSuccess_2 = (Array_Length_2 !== 2);
    
        if (!SwitchInteger_CmpSuccess_2)
            goto Label_2468;
    
        SwitchInteger_CmpSuccess_2 = (Array_Length_2 !== 3);
    
        if (!SwitchInteger_CmpSuccess_2)
            goto Label_2468;
    
        SwitchInteger_CmpSuccess_2 = (Array_Length_2 !== 4);
    
        if (!SwitchInteger_CmpSuccess_2)
            goto Label_2362;
    
        SwitchInteger_CmpSuccess_2 = (Array_Length_2 !== 5);
    
        if (!SwitchInteger_CmpSuccess_2)
            goto Label_2362;
    
        return;
    
        Label_2362:
        MakeArray_Array_16 = [ 0, 2 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_16;
    
        MakeArray_Array_3 = [ 1, 3, 4 ];
    
        supportlineLocationNumbers = MakeArray_Array_3;
    
        goto Label_691;
    
        Label_2468:
        MakeArray_Array_19 = [ 1, 3 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_19;
    
        MakeArray_Array_4 = [ 0, 2, 4 ];
    
        supportlineLocationNumbers = MakeArray_Array_4;
    
        goto Label_691;
    
        Label_2574:
        MakeArray_Array_20 = [ 2 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_20;
    
        MakeArray_Array_5 = [ 0, 1, 3 ];
    
        supportlineLocationNumbers = MakeArray_Array_5;
    
        goto Label_691;
    
        Label_2675:
        Array_Length_2 = cardsToRetreat.Length;
    
        SwitchInteger_CmpSuccess_1 = (Array_Length_2 !== 1);
    
        if (!SwitchInteger_CmpSuccess_1)
            goto Label_3187;
    
        SwitchInteger_CmpSuccess_1 = (Array_Length_2 !== 2);
    
        if (!SwitchInteger_CmpSuccess_1)
            goto Label_3187;
    
        SwitchInteger_CmpSuccess_1 = (Array_Length_2 !== 3);
    
        if (!SwitchInteger_CmpSuccess_1)
            goto Label_3081;
    
        SwitchInteger_CmpSuccess_1 = (Array_Length_2 !== 4);
    
        if (!SwitchInteger_CmpSuccess_1)
            goto Label_3081;
    
        SwitchInteger_CmpSuccess_1 = (Array_Length_2 !== 5);
    
        if (!SwitchInteger_CmpSuccess_1)
            goto Label_2975;
    
        return;
    
        Label_2975:
        MakeArray_Array_14 = [ 0 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_14;
    
        MakeArray_Array = [ 1, 2, 3, 4 ];
    
        supportlineLocationNumbers = MakeArray_Array;
    
        goto Label_691;
    
        Label_3081:
        MakeArray_Array_15 = [ 1 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_15;
    
        MakeArray_Array_1 = [ 0, 2, 3, 4 ];
    
        supportlineLocationNumbers = MakeArray_Array_1;
    
        goto Label_691;
    
        Label_3187:
        MakeArray_Array_18 = [ 2 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_18;
    
        MakeArray_Array_2 = [ 0, 1, 3, 4 ];
    
        supportlineLocationNumbers = MakeArray_Array_2;
    
        goto Label_691;
    
        Label_3293:
        MakeMap_Map = TMap { };
    
        cardIdToLocationNumber = MakeMap_Map;
    
        return;
    
        Label_3340:
        MakeArray_Array_26 = [ 0, 2 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_26;
    
        MakeArray_Array_12 = [ 1 ];
    
        supportlineLocationNumbers = MakeArray_Array_12;
    
        goto Label_691;
    
        Label_3436:
        MakeArray_Array_25 = [ 0, 2, 3 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_25;
    
        MakeArray_Array_11 = [ 1 ];
    
        supportlineLocationNumbers = MakeArray_Array_11;
    
        goto Label_691;
    
        Label_3537:
        MakeArray_Array_24 = [ 0, 1, 3, 4 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_24;
    
        MakeArray_Array_10 = [ 2 ];
    
        supportlineLocationNumbers = MakeArray_Array_10;
    
        goto Label_691;
    
        Label_3643:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_769;
    
        Label_3717:
        Add_IntInt_1 = Temp_int_Loop_Counter_Variable_1 + 1;
    
        Temp_int_Loop_Counter_Variable_1 = Add_IntInt_1;
    
        goto Label_1190;
    
        Label_3791:
        MakeArray_Array_21 = [ 0, 2, 4 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_21;
    
        MakeArray_Array_7 = [ 1, 3 ];
    
        supportlineLocationNumbers = MakeArray_Array_7;
    
        goto Label_691;
    
        Label_3897:
        MakeArray_Array_17 = [ 0, 1, 3 ];
    
        retreatCardsLocationNumbers = MakeArray_Array_17;
    
        MakeArray_Array_6 = [ 2, 4 ];
    
        supportlineLocationNumbers = MakeArray_Array_6;
    
        goto Label_691;
    
        Label_4003:
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void CreateCardObject(FName cardName, int cardID, ESideEnum side, ECardLocationEnum location, int locationNumber, bool isGoldCard, struct FS_SalvagedCardInfo salvageInfo, class UBaseCardObject*& cardObject)
    {
        GetStaticCard = UFunctionLibrary::GetStaticCard(cardName);
    
        StaticCardRef = GetStaticCard;
    
        GetObjectClass = UGameplayStatics::GetObjectClass(StaticCardRef);
    
        IsValidClass = GetObjectClass;
    
        if (!IsValidClass)
            goto Label_696;
    
        GetObjectClass = UGameplayStatics::GetObjectClass(StaticCardRef);
    
        SpawnObject = UGameplayStatics::SpawnObject(GetObjectClass, this);
    
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->Get Is Server Config("use_bal_edits", this, CallFunc_Get_Is_Server_Config_KeyTrue);
    
        Conv_NameToString_1 = FString(SpawnObject->name);
    
        EndsWith = UKismetStringLibrary::EndsWith(Conv_NameToString_1, "_bal", 0x1);
    
        BooleanAND = EndsWith && CallFunc_Get_Is_Server_Config_KeyTrue;
    
        if (!BooleanAND)
            goto Label_795;
    
        Conv_NameToString_1 = FString(SpawnObject->name);
    
        Split = UKismetStringLibrary::Split(Conv_NameToString_1, "_bal", CallFunc_Split_LeftS, CallFunc_Split_RightS, 0x1, 0x1);
    
        Conv_StringToName = FName(CallFunc_Split_LeftS);
    
        SpawnObject->name = Conv_StringToName;
    
        UFunctionLibrary::GetStaticCardSet(SpawnObject->name, CallFunc_GetStaticCardSet_cardSet);
    
        SpawnObject->cardSet = CallFunc_GetStaticCardSet_cardSet;
    
        goto Label_2926;
    
        Label_696:
        Conv_NameToString = FString(cardName);
    
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger(Conv_NameToString, this);
    
        cardObject = nullptr;
    
        return;
    
        Label_795:
        if (!salvageInfo.isSalvaged_1_D83369C241D0F4E11CEDCB8250BC0D97)
            goto Label_851;
    
        ApplySalvageChanges(SpawnObject, salvageInfo, false);
    
        Label_851:
        SpawnObject->cardFunction = this;
    
        CardFunctionsNotifier->NotifyApplyCampaignUpgrades(SpawnObject);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_980:
        Array_Length = StaticCardRef->usedTriggers.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1277;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = StaticCardRef->usedTriggers[Temp_int_Array_Index_Variable];
    
        GameStateRef->UpdateCardFunctionTriggerMap(CallFunc_Array_Get_Item, cardID);
    
        goto Label_2720;
    
        Label_1277:
        SpawnObject->isGoldCard = isGoldCard;
    
        SpawnObject->cardID = cardID;
    
        SpawnObject->side = side;
    
        SpawnObject->originalSide = side;
    
        SpawnObject->location = location;
    
        SpawnObject->locationNumber = locationNumber;
    
        SpawnObject->movementLeft = 1;
    
        SpawnObject->maxDefense = SpawnObject->defense;
    
        SpawnObject->maxAttack = SpawnObject->attack;
    
        SpawnObject->getHasFury(CallFunc_getHasFury_doesIt);
    
        if (!CallFunc_getHasFury_doesIt)
            goto Label_2670;
    
        SpawnObject->attackLeft = 2;
    
        Label_1850:
        SpawnObject->enterPlayOnTurn = 0;
    
        UFunctionLibrary::GetStaticCampaignName(cardName, CallFunc_GetStaticCampaignName_campaignName);
    
        TextIsEmpty = UKismetTextLibrary::TextIsEmpty(CallFunc_GetStaticCampaignName_campaignName);
    
        if (!TextIsEmpty)
            goto Label_2794;
    
        Label_1966:
        GameStateRef->GetEncryptionKey(CallFunc_GetEncryptionKey_OutKey);
    
        SpawnObject->SetEncryptionKey(CallFunc_GetEncryptionKey_OutKey);
    
        SpawnObject->InitializeEncryption();
    
        GetDataTableRowFromName = FindObject<UDataTableFunctionLibrary>(nullptr, "/Script/Engine.Default__DataTableFunctionLibrary")->GetDataTableRowFromName(FindObject<UDataTable>(nullptr, "kards/Content/Structs/DT_CardImages.DT_CardImages"), SpawnObject->name, CallFunc_GetDataTableRowFromName_OutRow);
    
        if (!GetDataTableRowFromName)
            goto Label_2226;
    
        SpawnObject->SetImageDataTableRow(CallFunc_GetDataTableRowFromName_OutRow);
    
        Label_2226:
        SpawnObject->InitStaticGameplayTags();
    
        GameStateRef->GetAllCardInBattleAsMap(CallFunc_GetAllCardInBattleAsMap_AllCardsInBattle);
    
        Map_Find = Map_Find(CallFunc_GetAllCardInBattleAsMap_AllCardsInBattle, SpawnObject->cardID, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_2876;
    
        Conv_IntToString = FString(SpawnObject->cardID);
    
        Concat_StrStr = "Adding a card with id that already had been used. cardID: " += Conv_IntToString;
    
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger(Concat_StrStr, this);
    
        Label_2610:
        SpawnObject->OnCreateCard();
    
        cardObject = SpawnObject;
    
        return;
    
        Label_2670:
        SpawnObject->attackLeft = 1;
    
        goto Label_1850;
    
        Label_2720:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_980;
    
        Label_2794:
        UFunctionLibrary::GetStaticCampaignName(cardName, CallFunc_GetStaticCampaignName_campaignName);
    
        SpawnObject->campaignName = CallFunc_GetStaticCampaignName_campaignName;
    
        goto Label_1966;
    
        Label_2876:
        GameStateRef->AddCardToAllCardsInBattle(SpawnObject);
    
        goto Label_2610;
    
        Label_2926:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void ApplySalvageChanges(class UBaseCardObject* card, struct FS_SalvagedCardInfo salvageInfo, bool isVeteran)
    {
        card->isSalvaged = salvageInfo.isSalvaged_1_D83369C241D0F4E11CEDCB8250BC0D97;
    
        card->faction = salvageInfo.salvageFaction_5_30136A02489F9A3E6C29FEB0A508ADD9;
    
        card->salvageFaction = salvageInfo.salvageFaction_5_30136A02489F9A3E6C29FEB0A508ADD9;
    
        if (!isVeteran)
            goto Label_185;
    
        return;
    
        Label_185:
        card->attack = 1;
    
        card->defense = 1;
    
        Greater_IntInt = (card->kredits > 3);
    
        if (!Greater_IntInt)
            return;
    
        card->kredits = 3;
    
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetCardFunctionsNotifier(class UU_CardFunctionsNotifier_C*& OutNotifier)
    {
        OutNotifier = CardFunctionsNotifier;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetUnitDestroyedThisTurn(bool& UnitDestroyed)
    {
        GameStateRef->GetUnitDestroyedThisTurn(CallFunc_GetUnitDestroyedThisTurn_UnitDestroyed);
    
        UnitDestroyed = CallFunc_GetUnitDestroyedThisTurn_UnitDestroyed;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetClientSide(ESideEnum& OutClientSide)
    {
        GameStateRef->GetClientSide(CallFunc_GetClientSide_OutClientSide);
    
        OutClientSide = CallFunc_GetClientSide_OutClientSide;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetOpponentSide(ESideEnum& OutOpponentSide)
    {
        GameStateRef->GetOpponentSide(CallFunc_GetOpponentSide_OutOpponentSide);
    
        OutOpponentSide = CallFunc_GetOpponentSide_OutOpponentSide;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetPlayingSide(ESideEnum& OutPlayingSide)
    {
        GameStateRef->GetPlayingSide(CallFunc_GetPlayingSide_OutPlayingSide);
    
        OutPlayingSide = CallFunc_GetPlayingSide_OutPlayingSide;
    
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void InitializeSideEffectHolders()
    {
        GetStaticCard_1 = UFunctionLibrary::GetStaticCard("card_sideeffect_holder_left");
    
        GetObjectClass_1 = UGameplayStatics::GetObjectClass(GetStaticCard_1);
    
        SpawnObject = UGameplayStatics::SpawnObject(GetObjectClass_1, this);
    
        localHolderLeft = SpawnObject;
    
        localHolderLeft->cardID = 30000000;
    
        localHolderLeft->cardFunction = this;
    
        GameStateRef->AddCardToAllCardsInBattle(localHolderLeft);
    
        goto Label_250;
    
        Label_250:
        GetStaticCard = UFunctionLibrary::GetStaticCard("card_sideeffect_holder_right");
    
        GetObjectClass = UGameplayStatics::GetObjectClass(GetStaticCard);
    
        SpawnObject_1 = UGameplayStatics::SpawnObject(GetObjectClass, this);
    
        localHolderRight = SpawnObject_1;
    
        localHolderRight->cardID = 60000000;
    
        localHolderRight->cardFunction = this;
    
        GameStateRef->AddCardToAllCardsInBattle(localHolderRight);
    
        goto Label_485;
    
        Label_485:
        GameStateRef->InitializeSideEffectHolders(localHolderLeft, localHolderRight);
    
        goto Label_540;
    
        Label_540:
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void NotifyEffectTagTriggered(ESideEnum SideToNotify, struct FGameplayTag EffectTag, bool& qqq)
    {
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void NotifySideEffectTrigger(ESideEnum SideToNotify, struct FGameplayTag EffectTag, bool& qqq)
    {
        localTextToNotify = "Countermeasures are blocked";
    
        IsGameplayTagValid = UBlueprintGameplayTagLibrary::IsGameplayTagValid(EffectTag);
    
        if (!IsGameplayTagValid)
            return;
    
        MatchesTag = UBlueprintGameplayTagLibrary::MatchesTag(EffectTag, FGameplayTag("sideeffect"), false);
    
        if (!MatchesTag)
            return;
    
        GetTagName = UBlueprintGameplayTagLibrary::GetTagName(EffectTag);
    
        Conv_NameToString = FString(GetTagName);
    
        SwitchString_CmpSuccess = (Conv_NameToString !== "sideeffect.blockgotcha");
    
        if (!SwitchString_CmpSuccess)
            goto Label_416;
    
        SwitchString_CmpSuccess = (Conv_NameToString !== "sideeffect.blockdeployment");
    
        if (!SwitchString_CmpSuccess)
            goto Label_538;
    
        return;
    
        Label_416:
        localTextToNotify = "Countermeasures are blocked";
    
        Label_501:
        ShowNotification(SideToNotify, localTextToNotify);
    
        return;
    
        Label_538:
        localTextToNotify = "Deployment effects are blocked";
    
        goto Label_501;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ApplyGameplaySideEffect(ESideEnum SideToApply, struct FGameplayTag EffectTag, class UBaseCardObject* InstigatorCard, EDurationPolicy DurationPolicy, int TurnsToLast, int& qqq)
    {
        MakeStruct_GameplayEffect.EffectTag = EffectTag;
    
        MakeStruct_GameplayEffect.InstigatorCard = InstigatorCard;
    
        MakeStruct_GameplayEffect.DurationPolicy = DurationPolicy;
    
        MakeStruct_GameplayEffect.RemainingTurns = TurnsToLast;
    
        MakeStruct_GameplayEffect.EffectValue = 0;
    
        GameStateRef->GetSideEffectHolderBySide(SideToApply, CallFunc_GetSideEffectHolderBySide_EffectHolder);
    
        CallFunc_GetSideEffectHolderBySide_EffectHolder->ApplyGameplayEffect(MakeStruct_GameplayEffect);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void DoesSideEffectTagExist(ESideEnum SideToCheck, struct FGameplayTag EffectTag, bool& Exist)
    {
        GameStateRef->GetSideEffectHolderBySide(SideToCheck, CallFunc_GetSideEffectHolderBySide_EffectHolder);
    
        DoesEffectTagExist = CallFunc_GetSideEffectHolderBySide_EffectHolder->DoesEffectTagExist(EffectTag);
    
        Exist = DoesEffectTagExist;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void RemoveGameplaySideEffect(ESideEnum SideToRemove, struct FGameplayTag EffectTag, class UBaseCardObject* InstigatorCard, int& qqq)
    {
        GameStateRef->GetSideEffectHolderBySide(SideToRemove, CallFunc_GetSideEffectHolderBySide_EffectHolder);
    
        CallFunc_GetSideEffectHolderBySide_EffectHolder->RemoveGameplayEffectByInstigator(EffectTag, InstigatorCard);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetUnitTypeCountOnBoard(ESideEnum SideToGet, int& TypeCount)
    {
        GetCardsOnBoardBySide(SideToGet, true, false, CallFunc_GetCardsOnBoardBySide_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_85:
        Array_Length = CallFunc_GetCardsOnBoardBySide_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_540;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsOnBoardBySide_cards[Temp_int_Array_Index_Variable];
    
        Set_Add(LocalUnitTypes, CallFunc_Array_Get_Item->type);
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsOnBoardBySide_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->IsTank(CallFunc_IsTank_isIt);
    
        if (!CallFunc_IsTank_isIt)
            goto Label_631;
    
        Temp_byte_Variable = 0x3;
    
        Set_Add(LocalUnitTypes, Temp_byte_Variable);
    
        goto Label_705;
    
        Label_540:
        Set_Length = Set_Length(LocalUnitTypes);
    
        TypeCount = Set_Length;
    
        return;
    
        Label_631:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_85;
    
        Label_705:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void GetMainNationForSide(ESideEnum side, EFactionEnum& mainNation)
    {
        GameStateRef->GetMainFactionBySide(side, CallFunc_GetMainFactionBySide_MainFaction);
    
        mainNation = CallFunc_GetMainFactionBySide_MainFaction;
    
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void UpdateBondVisuals(ESideEnum side)
    {
        OnBondVisualsUpdated->Broadcast(side);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveRandomCombatKeyword(int cardID, int instigatorID, ECombatKeyword& keywordGiven, bool& success)
    {
        keywordPicked = 0x1;
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        CardToGive = CallFunc_GetCardFromID_card;
    
        IsValid = CardToGive;
    
        if (!IsValid)
            goto Label_959;
    
        CanCardBeBuffed(CardToGive, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            goto Label_959;
    
        Temp_int_Variable_1 = 0;
    
        Temp_int_Variable = 0;
    
        Label_211:
        MakeLiteralInt = 8;
    
        Less_IntInt = (Temp_int_Variable_1 < MakeLiteralInt);
    
        if (!Less_IntInt)
            goto Label_995;
    
        Conv_IntToByte_1 = ((uint8)Temp_int_Variable_1);
    
        GetEnumeratorValueFromIndex = UKismetNodeHelperLibrary::GetEnumeratorValueFromIndex(FindObject<UEnum>(nullptr, "/Script/kards.ECombatKeyword"), Conv_IntToByte_1);
    
        Conv_ByteToInt = ((int32)GetEnumeratorValueFromIndex);
    
        Temp_int_Variable = Conv_ByteToInt;
    
        Conv_IntToByte = ((uint8)Temp_int_Variable);
    
        GetValidValue = UKismetNodeHelperLibrary::GetValidValue(FindObject<UEnum>(nullptr, "/Script/kards.ECombatKeyword"), Conv_IntToByte);
    
        EqualEqual_ByteByte = ((!GetValidValue) == (!0x7));
    
        EqualEqual_ByteByte_1 = ((!GetValidValue) == (!0x0));
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_1);
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card_2);
    
        EqualEqual_ByteByte_2 = ((!CallFunc_GetCardFromID_card_1->location) == (!0x7));
    
        CallFunc_GetCardFromID_card_2->getHasGuard(CallFunc_getHasGuard_doesIt);
    
        CallFunc_GetCardFromID_card_2->IsFighter(CallFunc_IsFighter_isIt);
    
        BooleanOR = (CallFunc_IsFighter_isIt || CallFunc_getHasGuard_doesIt);
    
        BooleanOR_1 = (BooleanOR || EqualEqual_ByteByte_2);
    
        BooleanAND = BooleanOR_1 && EqualEqual_ByteByte;
    
        BooleanOR_2 = (BooleanAND || EqualEqual_ByteByte_1);
    
        if (!BooleanOR_2)
            goto Label_2019;
    
        goto Label_1945;
    
        Label_959:
        keywordGiven = 0x0;
    
        success = false;
    
        return;
    
        Label_995:
        CallFunc_GetCombatKeywords_keywords = [];
    
        CardToGive->GetCombatKeywords(CallFunc_GetCombatKeywords_keywords, CallFunc_GetCombatKeywords_numberOfKeywords);
    
        Set_RemoveItems(validKeywords, CallFunc_GetCombatKeywords_keywords);
    
        Set_Length = Set_Length(validKeywords);
    
        Greater_IntInt = (Set_Length > 0);
    
        if (!Greater_IntInt)
            goto Label_1909;
    
        CallFunc_Set_ToArray_Result = [];
    
        Set_ToArray(validKeywords, CallFunc_Set_ToArray_Result);
    
        Array_Length = CallFunc_Set_ToArray_Result.Length;
    
        Subtract_IntInt = Array_Length - 1;
    
        RandomIntegerInRangeFromStream = UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, 0, Subtract_IntInt);
    
        CallFunc_Array_Get_Item = CallFunc_Set_ToArray_Result[RandomIntegerInRangeFromStream];
    
        keywordPicked = CallFunc_Array_Get_Item;
    
        SwitchEnum_CmpSuccess = ((!keywordPicked) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1873;
    
        SwitchEnum_CmpSuccess = ((!keywordPicked) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2153;
    
        SwitchEnum_CmpSuccess = ((!keywordPicked) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2186;
    
        SwitchEnum_CmpSuccess = ((!keywordPicked) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2219;
    
        SwitchEnum_CmpSuccess = ((!keywordPicked) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2252;
    
        SwitchEnum_CmpSuccess = ((!keywordPicked) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2285;
    
        SwitchEnum_CmpSuccess = ((!keywordPicked) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2335;
    
        SwitchEnum_CmpSuccess = ((!keywordPicked) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_2377;
    
        goto Label_2410;
    
        Label_1873:
        keywordGiven = 0x0;
    
        success = false;
    
        return;
    
        Label_1909:
        keywordGiven = 0x0;
    
        success = false;
    
        return;
    
        Label_1945:
        Add_IntInt = Temp_int_Variable_1 + 1;
    
        Temp_int_Variable_1 = Add_IntInt;
    
        goto Label_211;
    
        Label_2019:
        Conv_IntToByte = ((uint8)Temp_int_Variable);
    
        GetValidValue = UKismetNodeHelperLibrary::GetValidValue(FindObject<UEnum>(nullptr, "/Script/kards.ECombatKeyword"), Conv_IntToByte);
    
        Set_Add(validKeywords, GetValidValue);
    
        return;
    
        Label_2153:
        GiveAmbush(cardID, instigatorID);
    
        return;
    
        Label_2186:
        GiveBlitz(cardID, instigatorID);
    
        return;
    
        Label_2219:
        GiveFury(cardID, instigatorID);
    
        return;
    
        Label_2252:
        GiveGuard(cardID, instigatorID);
    
        return;
    
        Label_2285:
        ChangeHeavyArmor(CardToGive, instigatorID, 1, 0x1, false, CallFunc_ChangeHeavyArmor_qqq);
    
        return;
    
        Label_2335:
        GiveShock(cardID, instigatorID, CallFunc_GiveShock_qqq);
    
        return;
    
        Label_2377:
        GiveSmokescreen(cardID, instigatorID);
    
        return;
    
        Label_2410:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GiveBond(int cardID, int instigatorID, int& qqq)
    {
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        _card = CallFunc_GetCardFromID_card;
    
        IsValid = _card;
    
        if (!IsValid)
            goto Label_558;
    
        CanCardBeBuffed(_card, CallFunc_CanCardBeBuffed_CanBeBuffed);
    
        if (!CallFunc_CanCardBeBuffed_CanBeBuffed)
            return;
    
        Conv_IntToBool = (instigatorID != 0);
    
        if (!Conv_IntToBool)
            goto Label_636;
    
        Temp_string_Variable = "ability.bond";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        if (!Map_Find)
            goto Label_1005;
    
        Temp_string_Variable = "ability.bond";
    
        Map_Find = Map_Find(_card->receivedAbilitiesFromCards, Temp_string_Variable, CallFunc_Map_Find_Value);
    
        _cardsGivingBond = CallFunc_Map_Find_Value.cardsGivingAbility;
    
        Array_Contains = _cardsGivingBond[instigatorID];
    
        if (!Array_Contains)
            goto Label_1005;
    
        return;
    
        Label_558:
        FindObject<UClientLoggerFunctions_C>(nullptr, "kards/Content/Library/ClientLoggerFunctions.Default__ClientLoggerFunctions_C")->DirectClientLogger("GiveShock has to have valid target", this);
    
        return;
    
        Label_636:
        _card->HasBond(CallFunc_HasBond_hasIt);
    
        if (!CallFunc_HasBond_hasIt)
            goto Label_696;
    
        return;
    
        Label_696:
        AddCustomGameplayTag(FGameplayTag("ability.bond"), _card->cardID, instigatorID, CallFunc_AddCustomGameplayTag_qqq);
    
        Label_786:
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            return;
    
        CustomAbilityRemove("bond_removed", _card->cardID, instigatorID, true, CallFunc_CustomAbilityRemove_qqq);
    
        CardFunctionsNotifier->NotifyGiveBond(_card->cardID, instigatorID);
    
        ExecuteOnOtherCardsAbilitiesChanged(_card);
    
        return;
    
        Label_1005:
        Array_Add = _cardsGivingBond.Add(instigatorID);
    
        ChangeBuffsFromCards(_card, 1, instigatorID, 0x6, 0x8, "ability.bond", CallFunc_ChangeBuffsFromCards_amountRemoved);
    
        MakeStruct_CardsGivingAbility.cardsGivingAbility = _cardsGivingBond;
    
        Temp_string_Variable_1 = "ability.bond";
    
        Map_Add(_card->receivedAbilitiesFromCards, Temp_string_Variable_1, MakeStruct_CardsGivingAbility);
    
        goto Label_786;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetCardsPlayedFromHandLastTurn(TArray<int>& CardIDsPlayedLastTurn)
    {
        GetTurnNumber(CallFunc_GetTurnNumber_turnNumber);
    
        Subtract_IntInt = CallFunc_GetTurnNumber_turnNumber - 2;
    
        GameStateRef->getCardsPlayedFromHandByTurn(Subtract_IntInt, CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed);
    
        CardIDsPlayedLastTurn = CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetCardsPlayedFromHandByTurnNumber(int TurnNumber, TArray<int>& CardIDsPlayed)
    {
        GameStateRef->getCardsPlayedFromHandByTurn(TurnNumber, CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed);
    
        CardIDsPlayed = CallFunc_getCardsPlayedFromHandByTurn_cardsPlayed;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void RemoveBond(int cardID, int instigatorID, int& qqq)
    {
        CustomAbilityAdd("bond_removed", cardID, instigatorID, false, false, false, CallFunc_CustomAbilityAdd_qqq);
    
        RemoveCustomGameplayTag(FGameplayTag("visual.highlight"), cardID, instigatorID, true, CallFunc_RemoveCustomGameplayTag_qqq);
    
        GetCardFromID(cardID, CallFunc_GetCardFromID_card);
    
        OnBondVisualsUpdated->Broadcast(CallFunc_GetCardFromID_card->side);
    
        qqq = 0;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void IsCardReserved(FName InCardName, bool& IsReserved)
    {
        CardFunctionsNotifier->NotifyCheckCardReserved(InCardName, CallFunc_NotifyCheckCardReserved_IsReserved);
    
        IsReserved = CallFunc_NotifyCheckCardReserved_IsReserved;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetDestroyedCardsIDsByTurn(int turnID, TArray<int>& destroyedCardsIDs)
    {
        GameStateRef->GetDestroyedCardsIDsByTurn(turnID, CallFunc_GetDestroyedCardsIDsByTurn_DestroyedCardsIDs);
    
        destroyedCardsIDs = CallFunc_GetDestroyedCardsIDsByTurn_DestroyedCardsIDs;
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnCovertCardSpawned(class UBaseCardObject* cardSpawned)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_578;
    
        FetchAllCardsWithEventTrigger(0x41, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_109:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            return;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        NotEqual_IntInt = (CallFunc_Array_Get_Item->cardID !== cardSpawned->cardID);
    
        if (!NotEqual_IntInt)
            goto Label_504;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCovertCardSpawned(cardSpawned);
    
        return;
    
        Label_504:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_109;
    
        Label_578:
        return;
    }

    // (Public, BlueprintCallable, BlueprintEvent)
    public void HandleExtraPlayTriggersAfterSelectHandCard(class UBaseCardObject* Card)
    {
        Card->UpdateExtraPlayTriggers(CallFunc_UpdateExtraPlayTriggers_triggerNext);
    
        if (!CallFunc_UpdateExtraPlayTriggers_triggerNext)
            return;
    
        Card->OnPlayedFromHand(nullptr);
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void SetRightLeftMostWhenPlayed(class UBaseCardObject* card, ECardLocationEnum newLocation)
    {
        MakeVariable_MakeVariableOutput = TArray { 0x5, 0x6, 0x7, 0x8 };;
    
        validNewLocations = MakeVariable_MakeVariableOutput;
    
        Temp_byte_Variable = 0x0;
    
        Temp_byte_Variable_1 = card->side;
    
        MakeLiteralByte = 0x3;
    
        MakeLiteralByte_1 = 0x4;
    
        EqualEqual_ByteByte = ((!card->location) == (!switch (Temp_byte_Variable_1)
        {
            case 0x0:
            {
                return Temp_byte_Variable;
                break;
            }
            case 0x1:
            {
                return MakeLiteralByte;
                break;
            }
            case 0x2:
            {
                return MakeLiteralByte_1;
                break;
            }
            default:
            {
                return Select_Default;
                break;
            }
        }));
    
        Set_Contains = Set_Contains(validNewLocations, newLocation);
    
        BooleanAND = EqualEqual_ByteByte && Set_Contains;
    
        if (!BooleanAND)
            goto Label_1308;
    
        EqualEqual_IntInt_1 = card->locationNumber == 0;
    
        if (!EqualEqual_IntInt_1)
            goto Label_1029;
    
        JSON_SetBool(card, WasLeftMostWhenPlayedFromHandKey, true, CallFunc_JSON_SetBool_found_1);
    
        Label_525:
        greatestIndex = 0;
    
        GetCardsInHandBySide(card->side, CallFunc_GetCardsInHandBySide_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_648:
        Array_Length = CallFunc_GetCardsInHandBySide_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1075;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        Greater_IntInt = (CallFunc_Array_Get_Item->locationNumber > greatestIndex);
    
        if (!Greater_IntInt)
            goto Label_1234;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        greatestIndex = CallFunc_Array_Get_Item->locationNumber;
    
        return;
    
        Label_1029:
        JSON_Clear(card, WasLeftMostWhenPlayedFromHandKey, CallFunc_JSON_Clear_found_1);
    
        goto Label_525;
    
        Label_1075:
        EqualEqual_IntInt = card->locationNumber == greatestIndex;
    
        if (!EqualEqual_IntInt)
            goto Label_1192;
    
        JSON_SetBool(card, WasRightMostWhenPlayedFromHandKey, true, CallFunc_JSON_SetBool_found);
    
        return;
    
        Label_1192:
        JSON_Clear(card, WasRightMostWhenPlayedFromHandKey, CallFunc_JSON_Clear_found);
    
        return;
    
        Label_1234:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_648;
    
        Label_1308:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void WasLeftMostCardWhenPlayedFromHand(class UBaseCardObject* Card, bool& WasLeftMost)
    {
        JSON_GetBool(Card, WasLeftMostWhenPlayedFromHandKey, CallFunc_JSON_GetBool_value, CallFunc_JSON_GetBool_found);
    
        WasLeftMost = CallFunc_JSON_GetBool_value;
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void WasRightMostCardWhenPlayedFromHand(class UBaseCardObject* Card, bool& WasRightMost)
    {
        JSON_GetBool(Card, WasRightMostWhenPlayedFromHandKey, CallFunc_JSON_GetBool_value, CallFunc_JSON_GetBool_found);
    
        WasRightMost = CallFunc_JSON_GetBool_value;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetAllForecastCards(bool includeNotAttainable, bool includeReserved, TArray<class UBaseCardObject*>& forecastCards)
    {
        GetAllActiveStaticCards(includeNotAttainable, includeReserved, CallFunc_GetAllActiveStaticCards_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_92:
        Array_Length = CallFunc_GetAllActiveStaticCards_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_622;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        MakeArray_Array = [ FGameplayTag("subtype.rain"), FGameplayTag("subtype.storm"), FGameplayTag("subtype.sunny") ];
    
        MakeGameplayTagContainerFromArray = UBlueprintGameplayTagLibrary::MakeGameplayTagContainerFromArray(MakeArray_Array);
    
        HasAnyTags = UBlueprintGameplayTagLibrary::HasAnyTags(MakeGameplayTagContainerFromArray, CallFunc_Array_Get_Item->GameplayTags, false);
    
        if (!HasAnyTags)
            goto Label_654;
    
        CallFunc_Array_Get_Item = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        Array_Add = outCards.Add(CallFunc_Array_Get_Item);
    
        goto Label_728;
    
        Label_622:
        forecastCards = outCards;
    
        return;
    
        Label_654:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_92;
    
        Label_728:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void MoveCardInHandToLeftMost(class UBaseCardObject* Card, bool& sucess)
    {
        previousLocation = 0;
    
        MoveCardInHandToNewIndex(Card, 0, CallFunc_MoveCardInHandToNewIndex_success);
    
        sucess = CallFunc_MoveCardInHandToNewIndex_success;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void MoveCardInHandToNewIndex(class UBaseCardObject* cardToMove, int desiredLocation, bool& success)
    {
        previousLocation = 0;
    
        thisLocation = 0;
    
        cardToMove->IsLocatedInHand(CallFunc_IsLocatedInHand_isIt);
    
        if (!CallFunc_IsLocatedInHand_isIt)
            goto Label_839;
    
        previousLocation = cardToMove->locationNumber;
    
        GetCardsInHandBySide(cardToMove->side, CallFunc_GetCardsInHandBySide_cards);
    
        Array_IsValidIndex = CallFunc_GetCardsInHandBySide_cards[desiredLocation];
    
        NotEqual_IntInt = (cardToMove->locationNumber !== desiredLocation);
    
        BooleanAND_2 = Array_IsValidIndex && NotEqual_IntInt;
    
        if (!BooleanAND_2)
            goto Label_855;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_427:
        Array_Length = CallFunc_GetCardsInHandBySide_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_871;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        thisLocation = CallFunc_Array_Get_Item->locationNumber;
    
        EqualEqual_IntInt = thisLocation == previousLocation;
    
        if (!EqualEqual_IntInt)
            goto Label_1514;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->locationNumber = desiredLocation;
    
        goto Label_1440;
    
        Label_839:
        success = false;
    
        return;
    
        Label_855:
        success = false;
    
        return;
    
        Label_871:
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetBoard(this, CallFunc_GetBoard_Board);
    
        CallFunc_GetBoard_Board->GetVisualHandCardFromID(cardToMove->cardID, CallFunc_GetVisualHandCardFromID_cardRef, CallFunc_GetVisualHandCardFromID_found);
    
        if (!CallFunc_GetVisualHandCardFromID_found)
            goto Label_2332;
    
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetBoard(this, CallFunc_GetBoard_Board);
    
        CallFunc_GetBoard_Board->GetVisualHandCardFromID(cardToMove->cardID, CallFunc_GetVisualHandCardFromID_cardRef, CallFunc_GetVisualHandCardFromID_found);
    
        CallFunc_GetVisualHandCardFromID_cardRef->blockRearrange = true;
    
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetBoard(this, CallFunc_GetBoard_Board);
    
        CallFunc_GetBoard_Board->GetVisualHandCardFromID(cardToMove->cardID, CallFunc_GetVisualHandCardFromID_cardRef, CallFunc_GetVisualHandCardFromID_found);
    
        CallFunc_GetVisualHandCardFromID_cardRef->isHoverable = false;
    
        ExecuteOnCardMovedInHand();
    
        CardFunctionsNotifier->NotifyMoveCardInHand(cardToMove->cardID, previousLocation, desiredLocation);
    
        return;
    
        Label_1440:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_427;
    
        Label_1514:
        Less_IntInt_3 = (previousLocation < desiredLocation);
    
        if (!Less_IntInt_3)
            goto Label_1949;
    
        LessEqual_IntInt_1 = (thisLocation <= desiredLocation);
    
        Less_IntInt_2 = (previousLocation < thisLocation);
    
        BooleanAND_1 = Less_IntInt_2 && LessEqual_IntInt_1;
    
        if (!BooleanAND_1)
            return;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        Subtract_IntInt = CallFunc_Array_Get_Item->locationNumber - 1;
    
        Temp_int_Variable_1 = Subtract_IntInt;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->locationNumber = Temp_int_Variable_1;
    
        return;
    
        Label_1949:
        Less_IntInt_1 = (thisLocation < previousLocation);
    
        LessEqual_IntInt = (desiredLocation <= thisLocation);
    
        BooleanAND = LessEqual_IntInt && Less_IntInt_1;
    
        if (!BooleanAND)
            return;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        Add_IntInt_1 = CallFunc_Array_Get_Item->locationNumber + 1;
    
        Temp_int_Variable = Add_IntInt_1;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->locationNumber = Temp_int_Variable;
    
        return;
    
        Label_2332:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetLeftMostCardInHand(class UBaseCardObject* Card, bool& WasFound, class UBaseCardObject*& LeftMostCard)
    {
        GetCardsInHandBySide(Card->side, CallFunc_GetCardsInHandBySide_cards);
    
        Array_IsValidIndex = CallFunc_GetCardsInHandBySide_cards[0];
    
        if (!Array_IsValidIndex)
            goto Label_537;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_175:
        Array_Length = CallFunc_GetCardsInHandBySide_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_537;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->locationNumber == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_564;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        WasFound = true;
    
        LeftMostCard = CallFunc_Array_Get_Item;
    
        return;
    
        Label_537:
        WasFound = false;
    
        LeftMostCard = nullptr;
    
        return;
    
        Label_564:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_175;
    
        Label_638:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetRightMostCardInHand(class UBaseCardObject* Card, bool& WasFound, class UBaseCardObject*& RightMostCard)
    {
        GetCardsInHandBySide(Card->side, CallFunc_GetCardsInHandBySide_cards);
    
        Array_LastIndex = CallFunc_GetCardsInHandBySide_cards.Length - 1;
    
        NotEqual_IntInt = (Array_LastIndex !== -1);
    
        if (!NotEqual_IntInt)
            goto Label_637;
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_212:
        Array_Length = CallFunc_GetCardsInHandBySide_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_637;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        Array_LastIndex = CallFunc_GetCardsInHandBySide_cards.Length - 1;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        EqualEqual_IntInt = CallFunc_Array_Get_Item->locationNumber == Array_LastIndex;
    
        if (!EqualEqual_IntInt)
            goto Label_664;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsInHandBySide_cards[Temp_int_Array_Index_Variable];
    
        WasFound = true;
    
        RightMostCard = CallFunc_Array_Get_Item;
    
        return;
    
        Label_637:
        WasFound = false;
    
        RightMostCard = nullptr;
    
        return;
    
        Label_664:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_212;
    
        Label_738:
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnCardMovedInHand()
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_418;
    
        FetchAllCardsWithEventTrigger(0x42, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_109:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_738;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardMovedToLocationInHand();
    
        goto Label_344;
    
        Label_344:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_109;
    
        Label_418:
        return;
    }

    // (Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void CanCardBeBuffed(class UBaseCardObject* Card, bool& CanBeBuffed)
    {
        Card->IsUnrevealedCovertCard(CallFunc_IsUnrevealedCovertCard_isIt);
    
        if (!CallFunc_IsUnrevealedCovertCard_isIt)
            goto Label_730;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_746;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_762;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_762;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_762;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_762;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_746;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_746;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_746;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_746;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x9));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_762;
    
        return;
    
        Label_730:
        CanBeBuffed = true;
    
        return;
    
        Label_746:
        CanBeBuffed = false;
    
        return;
    
        Label_762:
        CanBeBuffed = true;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void Forecast(class UBaseCardObject* cardTriggeringForecast, int& qqq)
    {
        MakeArray_Array = [ "card_event_sunny1_blue_sky", "card_event_rain1_mist", "card_event_storm1_gale" ];
    
        CardFunctionsNotifier->NotifySelectCardToDrawPending(cardTriggeringForecast->cardID, false, MakeArray_Array, false);
    
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetOperationKreditsSpentThisTurn(int& kreditsSpentThisTurn)
    {
        kreditsSpentThisTurn = GameStateRef->OperationKreditsSpentThisTurn;
    
        return;
    }

    // (Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetCardsInHandBySideOrdered(ESideEnum side, TArray<class UBaseCardObject*>& cards)
    {
        GetCardsInHandBySide(side, CallFunc_GetCardsInHandBySide_cards);
    
        UFunctionLibrary::SortCardsByLocationNumber(CallFunc_GetCardsInHandBySide_cards);
    
        cards = CallFunc_GetCardsInHandBySide_cards;
    
        return;
    }

    // (Public, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void ExecuteOnOperationKreditsSpent(class UBaseCardObject* cardOperated, int kreditsSpent)
    {
        IsActionProcess(CallFunc_IsActionProcess_ActionProcess);
    
        if (!CallFunc_IsActionProcess_ActionProcess)
            goto Label_588;
    
        cardOperated->OnOperationKreditsSpent(kreditsSpent);
    
        FetchAllCardsWithEventTrigger(0x44, CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_154:
        Array_Length = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_638;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        NotEqual_ObjectObject = (CallFunc_Array_Get_Item !== cardOperated);
    
        if (!NotEqual_ObjectObject)
            goto Label_514;
    
        CallFunc_Array_Get_Item = CallFunc_FetchAllCardsWithEventTrigger_cardsWithThisTrigger[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->OnOtherCardOperationKreditsSpent(cardOperated, kreditsSpent);
    
        return;
    
        Label_514:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_154;
    
        Label_588:
        return;
    }

    // (Event, Public, HasOutParms, BlueprintCallable, BlueprintEvent)
    public void UpdateChooseOneActive(bool& chooseOneActive)
    {
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetBoard(this, CallFunc_GetBoard_Board);
    
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetOnlineMatch(this, CallFunc_GetOnlineMatch_onlineMatch);
    
        Map_IsNotEmpty = Map_IsNotEmpty(CallFunc_GetOnlineMatch_onlineMatch->selectCardToDrawPending);
    
        CallFunc_GetBoard_Board->chooseOneActive = Map_IsNotEmpty;
    
        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetBoard(this, CallFunc_GetBoard_Board);
    
        chooseOneActive = CallFunc_GetBoard_Board->chooseOneActive;
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetCardsToTheLeft(class UBaseCardObject* Card, bool unitsOnly, bool includeCovert, TArray<class UBaseCardObject*>& cards)
    {
        returnCards.Clear();
    
        EqualEqual_IntInt = Card->locationNumber == 0;
    
        if (!EqualEqual_IntInt)
            goto Label_148;
    
        Label_116:
        cards = returnCards;
    
        return;
    
        Label_148:
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_116;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_116;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_116;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_116;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_116;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_819;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_819;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_819;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_116;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x9));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_116;
    
        goto Label_1585;
    
        Label_819:
        GetCardsOnBoardBySide(Card->side, unitsOnly, includeCovert, CallFunc_GetCardsOnBoardBySide_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_937:
        Array_Length = CallFunc_GetCardsOnBoardBySide_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1479;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsOnBoardBySide_cards[Temp_int_Array_Index_Variable];
    
        EqualEqual_ByteByte = ((!CallFunc_Array_Get_Item->location) == (!Card->location));
    
        Less_IntInt_1 = (CallFunc_Array_Get_Item->locationNumber < Card->locationNumber);
    
        BooleanAND = Less_IntInt_1 && EqualEqual_ByteByte;
    
        if (!BooleanAND)
            goto Label_1511;
    
        CallFunc_Array_Get_Item = CallFunc_GetCardsOnBoardBySide_cards[Temp_int_Array_Index_Variable];
    
        Array_Add = returnCards.Add(CallFunc_Array_Get_Item);
    
        return;
    
        Label_1479:
        cards = returnCards;
    
        return;
    
        Label_1511:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_937;
    
        Label_1585:
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent, BlueprintPure)
    public void GetCardsToTheRight(class UBaseCardObject* Card, bool unitsOnly, bool includeCovert, TArray<class UBaseCardObject*>& cards)
    {
        returnCards.Clear();
    
        cardsToCheck.Clear();
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x0));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1383;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x1));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1383;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x2));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1383;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x3));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1383;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x4));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1383;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x5));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1415;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x6));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1415;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x7));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1415;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x8));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1383;
    
        SwitchEnum_CmpSuccess = ((!Card->location) !== (!0x9));
    
        if (!SwitchEnum_CmpSuccess)
            goto Label_1383;
    
        goto Label_763;
    
        Label_763:
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_809:
        Array_Length = cardsToCheck.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_1351;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = cardsToCheck[Temp_int_Array_Index_Variable];
    
        EqualEqual_ByteByte = ((!CallFunc_Array_Get_Item->location) == (!Card->location));
    
        Greater_IntInt = (CallFunc_Array_Get_Item->locationNumber > Card->locationNumber);
    
        BooleanAND = Greater_IntInt && EqualEqual_ByteByte;
    
        if (!BooleanAND)
            goto Label_1675;
    
        CallFunc_Array_Get_Item = cardsToCheck[Temp_int_Array_Index_Variable];
    
        Array_Add = returnCards.Add(CallFunc_Array_Get_Item);
    
        goto Label_1749;
    
        Label_1351:
        cards = returnCards;
    
        return;
    
        Label_1383:
        cards = returnCards;
    
        return;
    
        Label_1415:
        GetCardsOnBoardBySide(Card->side, unitsOnly, includeCovert, CallFunc_GetCardsOnBoardBySide_cards);
    
        cardsToCheck = CallFunc_GetCardsOnBoardBySide_cards;
    
        Array_LastIndex = cardsToCheck.Length - 1;
    
        EqualEqual_IntInt = Array_LastIndex == Card->locationNumber;
    
        if (!EqualEqual_IntInt)
            return;
    
        cards = returnCards;
    
        return;
    
        Label_1675:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_809;
    
        Label_1749:
        return;
    }
};