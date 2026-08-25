// 反编译原文摘录，未加工。来源：FModel 导出的蓝图反编译源码
// H:\!Modding\Output\Exports\kards\Content\Blueprints\Logic\BP_OnlineMatch.cpp
// 函数：ReceiveActionPlayCardFromHand（第 4802 行起），本摘录只截取跟社区所称"反制"
// （游戏内部名 Gotcha，对空/对海防御性"反制"手牌，玩家俗称"挂反制/取消反制"）
// 直接相关的分支（约第 4878-5132 行）。
//
// 用途：确认"挂反制"和"取消反制"在网络协议层面是同一种动作类型——不存在专门的
// "取消"动作类型，两者都是对同一张 Gotcha 手牌重复提交 XActionPlayCardFromHand，
// 客户端/服务端用 gotchaActivated 这个整数字段的取值（0=未激活，>0=激活序号）来
// 区分这次提交到底是"激活"还是"取消"：
//   - 提交时若 _card->gotchaActivated > 0（已激活）：直接置 0（取消）。
//   - 提交时若 _card->gotchaActivated == 0（未激活）：扫描同侧全部在场 Gotcha 卡，
//     取当前最大激活序号 +1，赋给这张卡（激活，带一个递增的激活顺序号）。
// 两条分支处理完都 goto 回 Label_1322，走同一段"如果是本机操作就播放 ToggleGotcha
// 动画"的收尾逻辑——两者在动作提交、动作类型、以及本文档其余部分讨论的
// GetNextAction_Impl/CurrentActionId 消化循环层面，没有任何已知的差异对待。

Label_1238:
_card->IsGotcha(CallFunc_IsGotcha_isIt_1);

if (!CallFunc_IsGotcha_isIt_1)
    goto Label_1528;

if (!playDirectly)
    goto Label_3482;

if (!ResolveSubActionsFromLocal)
    goto Label_3482;

Label_1322:
_card->IsOwnedByClientSide(CallFunc_IsOwnedByClientSide_IsOwned);

if (!CallFunc_IsOwnedByClientSide_IsOwned)
    goto Label_1523;

FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetBoard(this, CallFunc_GetBoard_Board);

CallFunc_GetBoard_Board->GetVisualHandCardFromID(_cardID, CallFunc_GetVisualHandCardFromID_cardRef, CallFunc_GetVisualHandCardFromID_found);

CallFunc_GetVisualHandCardFromID_cardRef->ToggleGotcha(false);

Label_1523:
return;

// ...(中间是同一段 ReceiveActionPlayCardFromHand 里处理普通"打出手牌"动作的分支，
//     与 Gotcha 无关，此处略去，完整原文见 BP_OnlineMatch.cpp)...

Label_3482:
Greater_IntInt = (_card->gotchaActivated > 0);

if (!Greater_IntInt)
    goto Label_3602;

// ↓↓↓ 取消反制：已激活（gotchaActivated > 0）时再次提交同一张卡的 XActionPlayCardFromHand，
//     直接把 gotchaActivated 置 0，然后走跟"激活"完全相同的收尾（Label_1322：本机则播放动画）。
_card->gotchaActivated = 0;

goto Label_1322;

Label_3602:
// ↓↓↓ 激活反制：未激活（gotchaActivated == 0）时提交同一张卡的 XActionPlayCardFromHand，
//     记录花费（getTotalKreditCost，正常打出手牌都会记录，反制无一例外），然后扫描
//     GameStateRef->GetAllCardInBattle() 里同侧全部 Gotcha 卡，取当前最大激活序号 +1
//     赋给这张卡（多张反制卡可以同时激活，按激活顺序编号）。
_card->getTotalKreditCost(CallFunc_getTotalKreditCost_totalKreditCost);

JsonMakeInt = UBlueprintJsonLibrary::JsonMakeInt(CallFunc_getTotalKreditCost_totalKreditCost);

JsonMakeField = UBlueprintJsonLibrary::JsonMakeField(_card->customJson, "kreditsPayed", JsonMakeInt);

_card->customJson = JsonMakeField;

Temp_int_Loop_Counter_Variable = 0;

Temp_int_Array_Index_Variable_1 = 0;

Label_3857:
GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);

Array_Length_1 = CallFunc_GetAllCardInBattle_AllCardsInBattle.Length;

Less_IntInt_1 = (Temp_int_Loop_Counter_Variable < Array_Length_1);

if (!Less_IntInt_1)
    goto Label_4646;

Temp_int_Array_Index_Variable_1 = Temp_int_Loop_Counter_Variable;

GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);

CallFunc_Array_Get_Item_1 = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable_1];

CallFunc_Array_Get_Item_1->IsGotcha(CallFunc_IsGotcha_isIt);

EqualEqual_ByteByte = ((!_card->side) == (!CallFunc_Array_Get_Item_1->side));

BooleanAND_1 = EqualEqual_ByteByte && CallFunc_IsGotcha_isIt;

Greater_IntInt_1 = (CallFunc_Array_Get_Item_1->gotchaActivated > _nextGotchaActivated);

BooleanAND_2 = BooleanAND_1 && Greater_IntInt_1;

if (!BooleanAND_2)
    goto Label_4572;

GameStateRef->GetAllCardInBattle(CallFunc_GetAllCardInBattle_AllCardsInBattle);

CallFunc_Array_Get_Item_1 = CallFunc_GetAllCardInBattle_AllCardsInBattle[Temp_int_Array_Index_Variable_1];

_nextGotchaActivated = CallFunc_Array_Get_Item_1->gotchaActivated;

return;

Label_4572:
Add_IntInt = Temp_int_Loop_Counter_Variable + 1;

Temp_int_Loop_Counter_Variable = Add_IntInt;

goto Label_3857;

Label_4646:
Add_IntInt_2 = _nextGotchaActivated + 1;

Temp_int_Variable = Add_IntInt_2;

_nextGotchaActivated = Temp_int_Variable;

_card->gotchaActivated = _nextGotchaActivated;

goto Label_1322;

// --- 相关的、本地纯 UI 动画函数（不提交任何网络动作，只在收到上面 ReceiveActionPlayCardFromHand
//     处理完毕后，本机侧才会调用，用来播放卡牌翻转动画/弹出提示文字）：
//     Cards/BP_HandCard.cpp:4628-4684

public void ToggleGotcha(bool skipMessage)
{
    theCard = baseCardObject;

    EqualEqual_IntInt = theCard->gotchaActivated == 0;

    if (!EqualEqual_IntInt)
        goto Label_272;

    theCard->IsOwnedByClientSide(CallFunc_IsOwnedByClientSide_IsOwned);

    if (!CallFunc_IsOwnedByClientSide_IsOwned)
        return;

    if (!HandCardLook->Widget->countermeasureActive)
        return;

    GotchaActivated();  // 纯视觉动画（卡牌飞出/归位），不触碰网络或 CurrentActionId

    if (!skipMessage)
        goto Label_569;

    Label_230:
    HandCardLook->SetCountermeasureStatus(false);

    return;

    Label_272:
    theCard->IsOwnedByClientSide(CallFunc_IsOwnedByClientSide_IsOwned_1);

    if (!CallFunc_IsOwnedByClientSide_IsOwned_1)
        return;

    FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->PlaySoundEffect(theCard->soundEnterPlay, this);

    GotchaActivated();

    if (!skipMessage)
        goto Label_465;

    Label_423:
    HandCardLook->SetCountermeasureStatus(true);

    return;

    Label_465:
    FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->BigNotify("Countermeasure activated", this);

    goto Label_423;

    Label_569:
    FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->BigNotify("Countermeasure deactivated", this);

    goto Label_230;

    return;
}
