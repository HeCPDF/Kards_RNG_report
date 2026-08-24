class Ucard_event_spy_ring_C : public UBaseCardObject
{
public:
    class UFunction* UberGraphFunction = "Function'kards/Content/Blueprints/Cards/Soviet/Breakthrough/events/card_event_spy_ring.card_event_spy_ring_C:ExecuteUbergraph_card_event_spy_ring'";
    struct FPointerToUberGraphFrame UberGraphFrame = {};
    FName Name = FName("card_event_spy_ring");
    FText title = FText("SPY RING");
    enum Type = ETypeEnum::order;
    enum faction = EFactionEnum::Soviet;
    int32 kredits = 2;
    FText Text = FText("Add a random Research card to your hand.");
    FText flavorText = FText("The Soviet Union had an elaborate ring of secret agents working for them during WWII. One of them was Richard Sorge who worked undercover as a German journalist in both Germany and Japan and provided vital wartime intelligence before he was caught and hanged by the Japanese in 1944. Many of the spies were double agents that had infiltrated, not only the Axis ranks, but also the ranks of the Allies, f.ex. Harold “Kim” Philby, one of the Cambridge Five, who was a senior officer in Britain’s Secret Intelligence Service. Another one was Klaus Fuchs who was the primary physicist on the Manhattan Project and passed on secrets about the A-bomb to Moscow. Many of the Soviet moles continued their work long into the Cold War, most were driven by ideology, but others by money or adventure.");
    enum rarity = ERarityEnum::Uncommon;
    enum cardSet = ECardSetEnum::Breakthrough;
    bool isReserved = true;
    FString spawnCardName = "card_event_imperial_research;card_event_reich_research;card_event_royal_research;card_event_soviet_military_research;card_event_us_military_research";
    class USoundWave* soundEnterPlay = "SoundWave'kards/Content/Assets/Audio/Misc/OrdersFeb17/Enigma_17.Enigma_17'";
    FSoftObjectPath Image = FSoftObjectPath("/Game/Assets/Textures/Images/Soviet/CandidateArtwork/WE_Candidates/t_spy_ring.t_spy_ring");
    FString artist = "Soviet WWII Poster";
    FSoftObjectPath historyPhoto = FSoftObjectPath("/Game/Assets/Textures/HistoricalPhotos/SPY_RING.SPY_RING");
    struct FVector2D historyPhotoSize = FVector2D(451, 512);
    FText historyPhotoDescription = FText("Klaus Fuchs’s identification photograph at Los Alamos.");
    bool isAttackBuff = true;
    bool isDefenseBuff = true;
    int randNumber;
    FName card to spawn;

    // (Final, UbergraphFunction, HasDefaults)
    private void ExecuteUbergraph_card_event_spy_ring(int EntryPoint)
    {
        goto EntryPoint;
    
        Label_15:
        card to spawn = "card_event_royal_research";
    
        goto Label_602;
    
        Label_47:
        EqualEqual_IntInt = randNumber == 4;
    
        if (!EqualEqual_IntInt)
            goto Label_1031;
    
        card to spawn = "card_event_soviet_military_research";
    
        return;
    
        Label_123:
        EqualEqual_IntInt_1 = randNumber == 3;
    
        if (!EqualEqual_IntInt_1)
            goto Label_47;
    
        card to spawn = "card_event_imperial_research";
    
        return;
    
        Label_203:
        EqualEqual_IntInt_2 = randNumber == 2;
    
        if (!EqualEqual_IntInt_2)
            goto Label_123;
    
        card to spawn = "card_event_reich_research";
    
        return;
    
        Label_283:
        EqualEqual_IntInt_3 = randNumber == 1;
    
        if (!EqualEqual_IntInt_3)
            goto Label_203;
    
        card to spawn = "card_event_us_military_research";
    
        return;
    
        Label_363:
        EqualEqual_IntInt_4 = randNumber == 0;
    
        if (!EqualEqual_IntInt_4)
            goto Label_283;
    
        goto Label_15;
    
        Label_421:
        cardFunction->SpawnCardInHandBySide(side, card to spawn, cardID, false, false, false, "", Temp_text_Variable, 0x0, CallFunc_SpawnCardinHandbySide_spawnedCardID);
    
        goto Label_421;
    
        Label_510:
        cardFunction->RandomIntFromRangeWithStream(0, 4, CallFunc_RandomIntFromRangeWithStream_randomResult);
    
        randNumber = CallFunc_RandomIntFromRangeWithStream_randomResult;
    
        goto Label_363;
    
        Label_597:
        goto Label_510;
    
        Label_602:
        return;
    }

    // (Event, Public, BlueprintCallable, BlueprintEvent)
    public void OnPlayedFromHand(class UBaseCardObject* targetCard)
    {
        UberGraphFrame->Event_targetCard = targetCard;
    
        ExecuteUbergraph_card_event_spy_ring(597);
    
        return;
    }
};