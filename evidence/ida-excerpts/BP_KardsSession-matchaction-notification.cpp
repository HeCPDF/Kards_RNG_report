// 反编译原文摘录，未加工。来源：FModel 导出的蓝图反编译源码
// H:\!Modding\Output\Exports\kards\Content\Blueprints\Logic\BP_KardsSession.cpp
// 约第 920-984 行，AKardsSession 处理一条 websocket 通知的分支逻辑。
// 完整调用链（从上到下）：收到 websocket 通知 → 判断是否走 websocket 通知这条路径
// (IsWebsocketNotifications) → 按通知的 message 字段做字符串分支
// ("rematch"/"challenge" 走 Rematch 解析；"matchaction" 直接触发轮询)。
//
// 用途：evidence/CurrentActionId-increment-logic.md「ping 标志置位路径」一节的直接证据来源——
// GetMatchController_2->triggerPollActions = true 这一行是蓝图属性赋值，
// 对应原生内存里 this+3476 字节（sub_144A8F5D0 单独置位的同一个字段，
// 也是 MatchActionsPollLoop_Impl 判断"是否绕开 5 秒节流"的第一个条件）。

// ...（IsWebsocketNotifications 检查之后的字符串分支）
IsWebsocketNotifications(CallFunc_IsWebsocketNotifications_yes);

if (!CallFunc_IsWebsocketNotifications_yes)
    goto Label_11675;

Set_Add(websocketChecks, CustomEvent_sender_3);

SwitchString_CmpSuccess_1 = (CustomEvent_message_3 !== "rematch");

if (!SwitchString_CmpSuccess_1)
    goto Label_11533;

SwitchString_CmpSuccess_1 = (CustomEvent_message_3 !== "challenge");

if (!SwitchString_CmpSuccess_1)
    goto Label_11533;

SwitchString_CmpSuccess_1 = (CustomEvent_message_3 !== "matchaction");

if (!SwitchString_CmpSuccess_1)
    goto Label_11478;

return;

Label_11478:
GetMatchController = AMatchControllerV2::GetMatchController(this);

GetMatchController->triggerPollActions = true;

return;

// --- 另一个分支：IsWebsocketNotifications 为假时走的"非 websocket 通知"路径，
// 只有当通知发送方是敌方玩家时才调用 resetLastPingReceivedTime()（跟上面的
// triggerPollActions 是两个不同字段/不同机制，未确认是否也影响轮询节流）：

Label_11675:
ResetPollDispatchTimer();

EqualEqual_ByteByte = ((!Logic->mySide) == (!0x0));

if (!EqualEqual_ByteByte)
    goto Label_11757;

return;

Label_11757:
FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetLogic(this, CallFunc_GetLogic_Logic_4);

CallFunc_GetLogic_Logic_4->GetEnemyPlayerID(CallFunc_GetEnemyPlayerID_playerID);

EqualEqual_IntInt = CallFunc_GetEnemyPlayerID_playerID == CustomEvent_sender_3;

if (!EqualEqual_IntInt)
    return;

GetMatchController_2 = AMatchControllerV2::GetMatchController(this);

GetMatchController_2->resetLastPingReceivedTime();

return;
