# 天气系统

1939的每张卡牌都是用蓝图写的，用FModel反编译“将是晴天”，关键部分长这样

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

所有卡牌的随机数均使用这个通过蓝图定义的函数

public void RandomIntFromRangeWithStream(int minimum, int maximum, int& randomResult)
{
  RandomIntegerInRangeFromStream = UKismetMathLibrary::RandomIntegerInRangeFromStream(cardsRandomStream, minimum, maximum);
  randomResult = RandomIntegerInRangeFromStream;
  return;
}

对局开始时会拿服务器生成的对局ID作为种子。

有段native代码段是根据对局控制器中的某个属性决定是否额外用matchID+19390*actionID重设全局随机数种子。不知道会不会触发，何时触发。
> 更完整的信息请阅读 `README.md`
