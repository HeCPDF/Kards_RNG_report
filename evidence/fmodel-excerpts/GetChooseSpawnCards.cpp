// FModel 反编译原文摘录，未加工。来源：
// H:\!Modding\Output\Exports\kards\Content\Blueprints\Cards\Neutral\events\card_event_sunny1_blue_sky.cpp:93-209
// Weather.md §4.1/§4.2 引用的核心函数——按 GameplayTag 把活跃天气卡分成 light/medium/heavy
// 三个候选池（93-205 行的填桶逻辑），并依次对三个池各调用一次 RandomIntFromRangeWithStream
// （148/156/164 行，顺序固定 light→medium→heavy）。此前文档只以"填桶逻辑"、"三次抽样"等文字转述，
// 完整原文见本文件。

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
