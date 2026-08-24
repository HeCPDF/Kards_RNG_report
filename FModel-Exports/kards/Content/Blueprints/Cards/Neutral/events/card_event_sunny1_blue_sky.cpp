class Ucard_event_sunny1_blue_sky_C : public UBaseCardObject
{
public:
    class UFunction* UberGraphFunction = "Function'kards/Content/Blueprints/Cards/Neutral/events/card_event_sunny1_blue_sky.card_event_sunny1_blue_sky_C:ExecuteUbergraph_card_event_sunny1_blue_sky'";
    struct FPointerToUberGraphFrame UberGraphFrame = {};
    struct FGameplayTagContainer GameplayTags = FGameplayTagContainer({
        FGameplayTag::RequestGameplayTag(FName("autoplay"))
    });
    FName Name = FName("card_event_sunny1_blue_sky");
    FText title = FText("BLUE SKY");
    enum Type = ETypeEnum::order;
    enum faction = EFactionEnum::Neutral;
    FText Text = FText("It will be Sunny.");
    enum rarity = ERarityEnum::Common;
    enum cardSet = ECardSetEnum::OnlySpawnable;
    TArray<enum> usedTriggers = {
        OnStartofTurn
    };
    FSoftObjectPath OnPlayedFromHandVisualsSoft = FSoftObjectPath("/Game/Blueprints/Effects/WeatherCards/BP_WeatherCard_BlueSky.BP_WeatherCard_BlueSky_C");
    FName customName1 = FName("startofturn0");
    FString Notes = "Image needed to be customized";
    bool isDefenseBuff = true;
    TArray<class UBaseCardObject*> _forecastOptions;
    class UBaseCardObject* weatherCardChosen;

    // (Final, UbergraphFunction, HasDefaults)
    private void ExecuteUbergraph_card_event_sunny1_blue_sky(int EntryPoint)
    {
        goto EntryPoint;
    
        Label_10:
        cardFunction->selectCardToDraw(cardID, false, true, CallFunc_selectCardToDraw_drawnCardID);
    
        return;
    
        Label_71:
        cardFunction->GetCardFromID(Event_handTargetCardID, CallFunc_GetCardFromID_card);
    
        weatherCardChosen = CallFunc_GetCardFromID_card;
    
        return;
    
        Label_149:
        UBaseCardObject::IsSideActive(side, CallFunc_IsSideActive_active);
    
        IsValid = weatherCardChosen;
    
        BooleanAND = CallFunc_IsSideActive_active && IsValid;
    
        if (!BooleanAND)
            return;
    
        cardFunction->SpawnCardInHandBySide(side, weatherCardChosen->name, cardID, false, false, false, "", Temp_text_Variable, 0x0, CallFunc_SpawnCardInHandBySide_spawnedCardID);
    
        weatherCardChosen = nullptr;
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void OnStartOfTurn(int turnnumber)
    {
        UberGraphFrame->Event_turnnumber = turnnumber;
    
        ExecuteUbergraph_card_event_sunny1_blue_sky(149);
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void OnHandTargetSelected(int handTargetCardID, int instigatorID)
    {
        UberGraphFrame->Event_handTargetCardID = handTargetCardID;
    
        UberGraphFrame->Event_instigatorID = instigatorID;
    
        ExecuteUbergraph_card_event_sunny1_blue_sky(71);
    
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void OnPlayedFromHand(class UBaseCardObject* targetCard)
    {
        UberGraphFrame->Event_targetCard = targetCard;
    
        ExecuteUbergraph_card_event_sunny1_blue_sky(10);
    
        return;
    }

    // (Event, Public, HasOutParms, HasDefaults, BlueprintCallable, BlueprintEvent)
    public void GetChooseSpawnCards(TArray<class UBaseCardObject*>& cards, bool& markAsSeen, bool& keepOrder)
    {
        Array_IsEmpty = Array_IsEmpty(_forecastOptions);
    
        if (!Array_IsEmpty)
            goto Label_713;
    
        cardFunction->GetAllActiveStaticCards(true, true, CallFunc_GetAllActiveStaticCards_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_164:
        Array_Length = CallFunc_GetAllActiveStaticCards_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_767;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item_3 = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_3->getHasGameplayTag(FGameplayTag("subtype.sunny"), CallFunc_getHasGameplayTag_hasTag_3);
    
        if (!CallFunc_getHasGameplayTag_hasTag_3)
            goto Label_1503;
    
        CallFunc_Array_Get_Item_3 = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_3->getHasGameplayTag(FGameplayTag("subtype.heavyWeather"), CallFunc_getHasGameplayTag_hasTag_2);
    
        if (!CallFunc_getHasGameplayTag_hasTag_2)
            goto Label_1577;
    
        CallFunc_Array_Get_Item_3 = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        Array_Add_3 = _heavyWeatherCards.Add(CallFunc_Array_Get_Item_3);
    
        goto Label_2111;
    
        Label_713:
        cards = _forecastOptions;
    
        markAsSeen = false;
    
        keepOrder = true;
    
        return;
    
        Label_767:
        Array_LastIndex_2 = _lightWeatherCards.Length - 1;
    
        cardFunction->RandomIntFromRangeWithStream(0, Array_LastIndex_2, CallFunc_RandomIntFromRangeWithStream_randomResult_2);
    
        CallFunc_Array_Get_Item_2 = _lightWeatherCards[CallFunc_RandomIntFromRangeWithStream_randomResult_2];
    
        Array_Add_2 = _forecastOptions.Add(CallFunc_Array_Get_Item_2);
    
        Array_LastIndex_1 = _mediumWeatherCards.Length - 1;
    
        cardFunction->RandomIntFromRangeWithStream(0, Array_LastIndex_1, CallFunc_RandomIntFromRangeWithStream_randomResult_1);
    
        CallFunc_Array_Get_Item_1 = _mediumWeatherCards[CallFunc_RandomIntFromRangeWithStream_randomResult_1];
    
        Array_Add_1 = _forecastOptions.Add(CallFunc_Array_Get_Item_1);
    
        Array_LastIndex = _heavyWeatherCards.Length - 1;
    
        cardFunction->RandomIntFromRangeWithStream(0, Array_LastIndex, CallFunc_RandomIntFromRangeWithStream_randomResult);
    
        CallFunc_Array_Get_Item = _heavyWeatherCards[CallFunc_RandomIntFromRangeWithStream_randomResult];
    
        Array_Add = _forecastOptions.Add(CallFunc_Array_Get_Item);
    
        return;
    
        Label_1503:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_164;
    
        Label_1577:
        CallFunc_Array_Get_Item_3 = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_3->getHasGameplayTag(FGameplayTag("subtype.mediumWeather"), CallFunc_getHasGameplayTag_hasTag_1);
    
        if (!CallFunc_getHasGameplayTag_hasTag_1)
            goto Label_1846;
    
        CallFunc_Array_Get_Item_3 = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        Array_Add_5 = _mediumWeatherCards.Add(CallFunc_Array_Get_Item_3);
    
        return;
    
        Label_1846:
        CallFunc_Array_Get_Item_3 = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item_3->getHasGameplayTag(FGameplayTag("subtype.lightWeather"), CallFunc_getHasGameplayTag_hasTag);
    
        if (!CallFunc_getHasGameplayTag_hasTag)
            return;
    
        CallFunc_Array_Get_Item_3 = CallFunc_GetAllActiveStaticCards_cards[Temp_int_Array_Index_Variable];
    
        Array_Add_4 = _lightWeatherCards.Add(CallFunc_Array_Get_Item_3);
    
        return;
    
        Label_2111:
        return;
    }
};