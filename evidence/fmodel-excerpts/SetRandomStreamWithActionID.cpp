// FModel 反编译原文摘录，未加工。来源：H:\!Modding\Output\Exports\kards\Content\Blueprints\Logic\BP_OnlineMatch.cpp:24519-24536
// README.md §1/§2.2、ReseedImpact.md、evidence/bUseTurnSwitchValidation.md 反复引用的核心函数——
// 重播种公式 match_id + CurrentActionId*19390 的蓝图侧实现本身，也是 bUseTurnSwitchValidation
// 开关（第 24524 行）唯一的读取/生效点之一。此前各文档只以文字转述这段逻辑，完整原文见本文件。
// 另有两处调用点（BP_OnlineMatch.cpp:445、:9150），未收录，含义分别是"收到一条动作后按其
// action_id 重播种"和"用 GetCurrentActionID() 当前值重播种"，字面调用形式很短，未单独摘录。

    // (Private, HasDefaults, BlueprintCallable, BlueprintEvent)
    private void SetRandomStreamWithActionID(int inputActionID)
    {
        GetMatchController = AMatchControllerV2::GetMatchController(this);

        if (!GetMatchController->bUseTurnSwitchValidation)
            return;

        Multiply_IntInt = (inputActionID * 19390);

        FindObject<UUtilityFunctions_C>(nullptr, "kards/Content/Library/UtilityFunctions.Default__UtilityFunctions_C")->GetMatch(this, CallFunc_GetMatch_Match);

        Add_IntInt = CallFunc_GetMatch_Match.match_id + Multiply_IntInt;

        cardFunctions->SetRandomStreamByMatchID(Add_IntInt);

        return;
    }
