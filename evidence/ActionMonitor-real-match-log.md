# 真实对局：`ActionMonitor.dll` 内存快照 + 网络抓包对照

一整局真实人机对局（`training`）里，用被动内存监控工具（[tools/ActionMonitor.cpp](../tools/ActionMonitor.cpp)，不改写任何游戏代码，纯读内存）每 5ms 轮询一次 `AMatchControllerV2` 实例的关键字段，值变化才记日志；同时用 mitmproxy 被动解密全部网络流量。两份数据独立采集，用本机提交计数 `Counter3228`（网络抓包解密出的 JSON `action_id` 字段的真实值，见 [two-distinct-action-id-counters.md](two-distinct-action-id-counters.md)）作为公共坐标对齐。

## 完整原始日志（`kards_action_monitor.log`，DLL 侧）

```
[0.000000] === ActionMonitor v3 attached (pure memory polling, no code hooks) ===
[0.000111] Module base = 0x7ff722720000
[0.001053] MatchControllerV2 instance found/changed: this=00000238ADABDDE0
[0.001086] CurrentActionId=3 Counter3228=2 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817113.381
[4.413449] CurrentActionId=4 Counter3228=2 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817117.881
[5.728158] CurrentActionId=6 Counter3228=2 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817118.383
[12.332793] CurrentActionId=6 Counter3228=3 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817125.883
[12.868067] CurrentActionId=6 Counter3228=4 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817126.383
[13.699699] CurrentActionId=6 Counter3228=5 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817127.382
[15.394445] CurrentActionId=13 Counter3228=5 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817128.383
[25.304336] CurrentActionId=13 Counter3228=6 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817138.883
[34.300273] CurrentActionId=13 Counter3228=7 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817147.884
[35.242082] CurrentActionId=13 Counter3228=8 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817148.868
[36.751164] CurrentActionId=19 Counter3228=8 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817149.869
[45.165915] CurrentActionId=19 Counter3228=9 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817158.869
[48.422715] CurrentActionId=19 Counter3228=10 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817161.870
[49.039886] CurrentActionId=19 Counter3228=11 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817162.873
[51.099142] CurrentActionId=19 Counter3228=12 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817164.871
[55.457170] CurrentActionId=19 Counter3228=13 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817168.878
[56.680113] CurrentActionId=19 Counter3228=14 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817170.378
[57.379204] CurrentActionId=19 Counter3228=15 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817170.880
[58.279248] CurrentActionId=19 Counter3228=16 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817171.882
[59.168750] CurrentActionId=19 Counter3228=17 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817172.881
[61.643980] CurrentActionId=33 Counter3228=17 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817173.881
[78.154457] CurrentActionId=33 Counter3228=18 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817191.873
[96.789205] CurrentActionId=33 Counter3228=19 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817210.375
[121.879016] CurrentActionId=33 Counter3228=20 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817235.379
[126.606191] CurrentActionId=33 Counter3228=21 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817240.377
[135.092999] CurrentActionId=33 Counter3228=22 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817248.873
[137.223054] CurrentActionId=42 Counter3228=22 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817249.873
[147.037616] CurrentActionId=42 Counter3228=23 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817260.873
[178.220051] CurrentActionId=42 Counter3228=24 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817291.874
[179.284465] CurrentActionId=42 Counter3228=25 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817292.880
[180.992903] CurrentActionId=50 Counter3228=25 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817293.881
[198.914069] CurrentActionId=50 Counter3228=26 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817312.381
[203.132271] CurrentActionId=50 Counter3228=27 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817316.885
[205.683262] CurrentActionId=50 Counter3228=28 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817319.372
[216.608999] CurrentActionId=50 Counter3228=29 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817330.377
[217.453626] CurrentActionId=50 Counter3228=30 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817330.866
[219.729638] CurrentActionId=60 Counter3228=30 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817332.368
[236.732644] CurrentActionId=60 Counter3228=31 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817350.367
[261.954060] CurrentActionId=60 Counter3228=32 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817375.368
[262.895958] CurrentActionId=60 Counter3228=33 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817376.382
[264.372737] CurrentActionId=60 Counter3228=34 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817377.882
[266.560345] CurrentActionId=68 Counter3228=34 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817379.383
[279.480611] CurrentActionId=68 Counter3228=35 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817392.882
[283.535037] CurrentActionId=68 Counter3228=36 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817396.882
[286.572383] CurrentActionId=68 Counter3228=37 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817400.371
[287.558599] CurrentActionId=68 Counter3228=38 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817401.371
[290.187876] CurrentActionId=75 Counter3228=38 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817402.371
[297.887696] CurrentActionId=75 Counter3228=39 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817411.371
[312.961964] CurrentActionId=75 Counter3228=40 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817426.371
[313.730457] CurrentActionId=75 Counter3228=41 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817427.385
[314.452177] CurrentActionId=75 Counter3228=42 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817427.869
[318.938960] CurrentActionId=75 Counter3228=43 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817432.370
[319.547526] CurrentActionId=75 Counter3228=44 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817433.382
[321.243061] CurrentActionId=75 Counter3228=45 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817434.881
[321.952407] CurrentActionId=75 Counter3228=46 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817435.381
[323.884997] CurrentActionId=75 Counter3228=47 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817437.380
[326.093732] CurrentActionId=89 Counter3228=47 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817438.380
[343.109898] CurrentActionId=89 Counter3228=48 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817456.880
[344.032560] CurrentActionId=89 Counter3228=49 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817457.381
[345.295309] CurrentActionId=89 Counter3228=50 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817458.872
[354.085913] CurrentActionId=89 Counter3228=51 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817467.882
[355.281159] CurrentActionId=89 Counter3228=52 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817468.873
[358.054652] CurrentActionId=97 Counter3228=52 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817469.874
[358.060627] CurrentActionId=99 Counter3228=52 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817469.874
[371.754701] CurrentActionId=99 Counter3228=53 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817485.374
[381.377121] CurrentActionId=99 Counter3228=54 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817494.878
[384.777808] CurrentActionId=99 Counter3228=55 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817498.373
[401.328401] CurrentActionId=99 Counter3228=56 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817514.873
[404.292143] CurrentActionId=99 Counter3228=57 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817517.869
[406.400558] CurrentActionId=107 Counter3228=57 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817518.869
[414.102467] CurrentActionId=107 Counter3228=58 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817527.869
[419.692975] CurrentActionId=107 Counter3228=59 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817533.370
[421.229416] CurrentActionId=107 Counter3228=60 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817534.874
[426.337554] CurrentActionId=107 Counter3228=61 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817539.883
[429.710441] CurrentActionId=107 Counter3228=62 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817543.374
[430.773024] CurrentActionId=107 Counter3228=63 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817544.370
[431.846884] CurrentActionId=107 Counter3228=64 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817545.374
[433.756286] CurrentActionId=118 Counter3228=64 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817546.377
[446.071605] CurrentActionId=118 Counter3228=65 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817559.875
[450.504414] CurrentActionId=118 Counter3228=66 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817563.875
[451.488043] CurrentActionId=118 Counter3228=67 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817564.869
[456.572660] CurrentActionId=118 Counter3228=68 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817570.372
[458.188504] CurrentActionId=118 Counter3228=69 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817571.882
[463.180210] CurrentActionId=118 Counter3228=70 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817576.875
[464.672485] CurrentActionId=127 Counter3228=70 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817577.875
[472.378607] CurrentActionId=127 Counter3228=71 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817585.875
[476.612134] CurrentActionId=127 Counter3228=72 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817590.381
[477.667658] CurrentActionId=127 Counter3228=73 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817591.373
[488.752135] CurrentActionId=127 Counter3228=74 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817602.371
[489.844209] CurrentActionId=127 Counter3228=75 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817603.371
[497.349758] CurrentActionId=127 Counter3228=76 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817610.879
[498.776267] CurrentActionId=127 Counter3228=77 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817612.368
[502.984505] CurrentActionId=138 Counter3228=77 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817615.869
[514.584123] CurrentActionId=138 Counter3228=78 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817628.368
[519.228609] CurrentActionId=138 Counter3228=79 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817632.877
[519.964331] CurrentActionId=138 Counter3228=80 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817633.376
[525.806150] CurrentActionId=138 Counter3228=81 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817639.373
[530.708562] CurrentActionId=138 Counter3228=82 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817644.381
[533.142299] CurrentActionId=138 Counter3228=83 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817646.869
[535.315038] CurrentActionId=138 Counter3228=84 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817648.882
[539.789381] CurrentActionId=138 Counter3228=85 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817653.373
[541.356446] CurrentActionId=138 Counter3228=86 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817654.874
[542.857411] CurrentActionId=138 Counter3228=87 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817656.377
[544.230108] CurrentActionId=138 Counter3228=88 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817657.880
[545.682945] CurrentActionId=138 Counter3228=89 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817659.382
[547.174965] CurrentActionId=138 Counter3228=90 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817660.868
[553.344257] CurrentActionId=138 Counter3228=91 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817666.867
[557.478728] CurrentActionId=138 Counter3228=92 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817670.880
[559.151885] CurrentActionId=138 Counter3228=93 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817672.871
[560.671039] CurrentActionId=138 Counter3228=94 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817674.374
[562.155207] CurrentActionId=138 Counter3228=95 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817675.876
[563.877521] CurrentActionId=138 Counter3228=96 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817677.380
[565.211202] CurrentActionId=138 Counter3228=97 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817678.881
[566.534855] CurrentActionId=138 Counter3228=98 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817680.370
[567.545214] CurrentActionId=138 Counter3228=99 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817681.373
[572.248191] CurrentActionId=138 Counter3228=100 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817685.872
[576.663146] CurrentActionId=138 Counter3228=101 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817690.379
[580.897508] CurrentActionId=138 Counter3228=102 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817694.382
[582.334065] CurrentActionId=138 Counter3228=103 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817695.869
[586.165677] CurrentActionId=138 Counter3228=104 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817699.880
[589.604406] CurrentActionId=138 Counter3228=105 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817703.374
[593.745301] CurrentActionId=138 Counter3228=106 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817707.381
[595.064461] CurrentActionId=138 Counter3228=107 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817708.869
[596.581163] CurrentActionId=138 Counter3228=108 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817710.371
[599.993956] CurrentActionId=138 Counter3228=109 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817713.372
[603.835269] CurrentActionId=180 Counter3228=109 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817714.871
[642.647454] CurrentActionId=180 Counter3228=110 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817756.372
[647.892791] CurrentActionId=180 Counter3228=111 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817761.369
[653.342638] CurrentActionId=180 Counter3228=112 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817766.874
[654.113032] CurrentActionId=180 Counter3228=113 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817767.885
[654.982870] CurrentActionId=180 Counter3228=114 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817768.375
[655.171651] CurrentActionId=180 Counter3228=114 pollState=4 shouldPollActions=1 triggerPollActions=1 lastPollTime=16817768.875
[655.521894] CurrentActionId=180 Counter3228=114 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817769.375
[655.907741] CurrentActionId=185 Counter3228=114 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817769.375
[656.372730] CurrentActionId=185 Counter3228=114 pollState=4 shouldPollActions=1 triggerPollActions=1 lastPollTime=16817769.875
[656.521657] CurrentActionId=185 Counter3228=114 pollState=4 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817770.375
[656.907261] CurrentActionId=186 Counter3228=114 pollState=0 shouldPollActions=1 triggerPollActions=0 lastPollTime=16817770.375
[659.269550] CurrentActionId=186 Counter3228=0 pollState=0 shouldPollActions=1 triggerPollActions=0 lastPollTime=0.000
```

（最后一行 `pollState=0`、`Counter3228=0` 是对局结束、`AMatchControllerV2` 实例被回收/重置后的读数，不代表对局内行为。）

## 与反制（Gotcha/`XActionPlayCardFromHand`，cardID=5）真实抓包的对照

mitmproxy 抓包里，`Counter3228=107` 和 `Counter3228=108` 对应本机连续两次对同一张反制卡（cardID=5）的提交（一次激活、一次取消，见 [SpyRing.md](../SpyRing.md) §4.6）：

```
SUBMIT: action_id=107 type=PC data={"0": "5", "1": "3", "2": "0", "3": "0", "4": "bm", ...}
SUBMIT: action_id=108 type=PC data={"0": "5", "1": "3", "2": "0", "3": "0", "4": "bm", ...}
```

对照上面 DLL 日志：`Counter3228=107`（第 595.06s 行）和 `Counter3228=108`（第 596.58s 行）两条记录里，`CurrentActionId` 都还是 `138`——跟 `Counter3228=77`（t=502.98s）时的值完全一样，这两次反制切换整个落在同一段冻结期内，直到 t=603.84s（`Counter3228` 已经推进到 109）才终于看到 `CurrentActionId` 跳到 `180`。也就是说，这次反制切换对局面预览用的种子分量，在提交后至少 7 秒（到本次采样窗口结束）里都没有任何变化，真实生效时间点无法从这份数据精确到具体是哪一次轮询回包造成的——只能确定"晚于 t=596.58s，不晚于 t=603.84s"。

## 另见

- [CurrentActionId-increment-logic.md](CurrentActionId-increment-logic.md) — 基于这份数据的结论与机制解释。
- [SpyRing.md](../SpyRing.md) §4.5/§4.6 — 这份数据回答的具体开放问题。
- [two-distinct-action-id-counters.md](two-distinct-action-id-counters.md) — `Counter3228` 与 `CurrentActionId` 的字段区分。
