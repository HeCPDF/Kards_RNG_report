class Ucard_event_sunny2_heatwave_C : public UBaseCardObject
{
public:
    class UFunction* UberGraphFunction = "Function'kards/Content/Blueprints/Cards/Neutral/events/card_event_sunny2_heatwave.card_event_sunny2_heatwave_C:ExecuteUbergraph_card_event_sunny2_heatwave'";
    struct FPointerToUberGraphFrame UberGraphFrame = {};
    struct FGameplayTagContainer GameplayTags = FGameplayTagContainer({
        FGameplayTag::RequestGameplayTag(FName("subtype.sunny")),
        FGameplayTag::RequestGameplayTag(FName("subtype.lightWeather"))
    });
    FName Name = FName("card_event_sunny2_heatwave");
    FText title = FText("HEATWAVE");
    enum Type = ETypeEnum::order;
    enum faction = EFactionEnum::Neutral;
    int32 kredits = 2;
    FText Text = FText("All units get +2 attack until end of turn. Air units get +3 instead.");
    enum rarity = ERarityEnum::Common;
    enum cardSet = ECardSetEnum::OnlySpawnable;
    FSoftObjectPath OnPlayedFromHandVisualsSoft = FSoftObjectPath("/Game/Blueprints/Effects/WeatherCards/BP_WeatherCard_Heatwave.BP_WeatherCard_Heatwave_C");
    FString Notes = "Image needed to be customized";
    bool isDefenseBuff = true;

    // (Final, UbergraphFunction, HasDefaults)
    private void ExecuteUbergraph_card_event_sunny2_heatwave(int EntryPoint)
    {
        goto EntryPoint;
    
        Label_15:
        cardFunction->GetAllUnitsOnBoard(false, CallFunc_GetAllUnitsOnBoard_cards);
    
        Temp_int_Loop_Counter_Variable = 0;
    
        Temp_int_Array_Index_Variable = 0;
    
        Label_107:
        Array_Length = CallFunc_GetAllUnitsOnBoard_cards.Length;
    
        Less_IntInt = (Temp_int_Loop_Counter_Variable < Array_Length);
    
        if (!Less_IntInt)
            goto Label_672;
    
        Temp_int_Array_Index_Variable = Temp_int_Loop_Counter_Variable;
    
        CallFunc_Array_Get_Item = CallFunc_GetAllUnitsOnBoard_cards[Temp_int_Array_Index_Variable];
    
        CallFunc_Array_Get_Item->IsAirUnit(CallFunc_IsAirUnit_isIt);
    
        if (!CallFunc_IsAirUnit_isIt)
            goto Label_553;
    
        CallFunc_Array_Get_Item = CallFunc_GetAllUnitsOnBoard_cards[Temp_int_Array_Index_Variable];
    
        cardFunction->AddAttackUntilEndOfTurn(CallFunc_Array_Get_Item, cardID, 3);
    
        goto Label_479;
    
        Label_479:
        Add_IntInt = Temp_int_Loop_Counter_Variable + 1;
    
        Temp_int_Loop_Counter_Variable = Add_IntInt;
    
        goto Label_107;
    
        Label_553:
        CallFunc_Array_Get_Item = CallFunc_GetAllUnitsOnBoard_cards[Temp_int_Array_Index_Variable];
    
        cardFunction->AddAttackUntilEndOfTurn(CallFunc_Array_Get_Item, cardID, 2);
    
        return;
    
        Label_672:
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void OnPlayedFromHand(class UBaseCardObject* targetCard)
    {
        UberGraphFrame->Event_targetCard = targetCard;
    
        ExecuteUbergraph_card_event_sunny2_heatwave(15);
    
        return;
    }
};