glabel rspParseABI3
/* 07D084 80082624 7C0802A6 */  mflr    r0
/* 07D088 80082628 38A40000 */  addi    r5, r4, 0
/* 07D08C 8008262C 90010004 */  stw     r0, 4(r1)
/* 07D090 80082630 38C00000 */  li      r6, 0
/* 07D094 80082634 9421FF98 */  stwu    r1, -0x68(r1)
/* 07D098 80082638 BEE10044 */  stmw    r23, 0x44(r1)
/* 07D09C 8008263C 3B830000 */  addi    r28, r3, 0
/* 07D0A0 80082640 806338E8 */  lwz     r3, 0x38e8(r3)
/* 07D0A4 80082644 80040034 */  lwz     r0, 0x34(r4)
/* 07D0A8 80082648 38810038 */  addi    r4, r1, 0x38
/* 07D0AC 8008264C 8063002C */  lwz     r3, 0x2c(r3)
/* 07D0B0 80082650 80A50030 */  lwz     r5, 0x30(r5)
/* 07D0B4 80082654 5417027E */  clrlwi  r23, r0, 9
/* 07D0B8 80082658 4BFEAA49 */  bl      ramGetBuffer
/* 07D0BC 8008265C 2C030000 */  cmpwi   r3, 0
/* 07D0C0 80082660 4082000C */  bne     lbl_8008266C
/* 07D0C4 80082664 38600000 */  li      r3, 0
/* 07D0C8 80082668 48000518 */  b       lbl_80082B80
lbl_8008266C:
/* 07D0CC 8008266C 800D85EC */  lwz     r0, nFirstTime_2757@sda21(r13)
/* 07D0D0 80082670 56E3003A */  rlwinm  r3, r23, 0, 0, 0x1d
/* 07D0D4 80082674 80810038 */  lwz     r4, 0x38(r1)
/* 07D0D8 80082678 2C000000 */  cmpwi   r0, 0
/* 07D0DC 8008267C 7FA41A14 */  add     r29, r4, r3
/* 07D0E0 80082680 418204D8 */  beq     lbl_80082B58
/* 07D0E4 80082684 38000000 */  li      r0, 0
/* 07D0E8 80082688 900D85EC */  stw     r0, nFirstTime_2757@sda21(r13)
/* 07D0EC 8008268C 480004CC */  b       lbl_80082B58
lbl_80082690:
/* 07D0F0 80082690 83C40000 */  lwz     r30, 0(r4)
/* 07D0F4 80082694 80610038 */  lwz     r3, 0x38(r1)
/* 07D0F8 80082698 57C0463E */  srwi    r0, r30, 0x18
/* 07D0FC 8008269C 80840004 */  lwz     r4, 4(r4)
/* 07D100 800826A0 38630008 */  addi    r3, r3, 8
/* 07D104 800826A4 28000016 */  cmplwi  r0, 0x16
/* 07D108 800826A8 90610038 */  stw     r3, 0x38(r1)
/* 07D10C 800826AC 418104A4 */  bgt     lbl_80082B50
/* 07D110 800826B0 5400103A */  slwi    r0, r0, 2
/* 07D114 800826B4 7C1F002E */  lwzx    r0, r31, r0
/* 07D118 800826B8 7C0903A6 */  mtctr   r0
/* 07D11C 800826BC 4E800420 */  bctr    
.global lbl_800826C0
lbl_800826C0:
/* 07D120 800826C0 387C0000 */  addi    r3, r28, 0
/* 07D124 800826C4 38BE0000 */  addi    r5, r30, 0
/* 07D128 800826C8 48008119 */  bl      rspAADPCMDec1Fast
/* 07D12C 800826CC 48000494 */  b       lbl_80082B60
.global lbl_800826D0
lbl_800826D0:
/* 07D130 800826D0 A01C38D4 */  lhz     r0, 0x38d4(r28)
/* 07D134 800826D4 57C3043E */  clrlwi  r3, r30, 0x10
/* 07D138 800826D8 5485043E */  clrlwi  r5, r4, 0x10
/* 07D13C 800826DC 80DC3294 */  lwz     r6, 0x3294(r28)
/* 07D140 800826E0 7C030214 */  add     r0, r3, r0
/* 07D144 800826E4 5400003C */  rlwinm  r0, r0, 0, 0, 0x1e
/* 07D148 800826E8 7C660214 */  add     r3, r6, r0
/* 07D14C 800826EC 38800000 */  li      r4, 0
/* 07D150 800826F0 4BF82CE1 */  bl      memset
/* 07D154 800826F4 4800046C */  b       lbl_80082B60
.global lbl_800826F8
lbl_800826F8:
/* 07D158 800826F8 387C0000 */  addi    r3, r28, 0
/* 07D15C 800826FC 38BE0000 */  addi    r5, r30, 0
/* 07D160 80082700 4800052D */  bl      rspAEnvMixer3
/* 07D164 80082704 4800045C */  b       lbl_80082B60
.global lbl_80082708
lbl_80082708:
/* 07D168 80082708 548356BA */  rlwinm  r3, r4, 0xa, 0x1a, 0x1d
/* 07D16C 8008270C 80BC38E8 */  lwz     r5, 0x38e8(r28)
/* 07D170 80082710 38033254 */  addi    r0, r3, 0x3254
/* 07D174 80082714 8065002C */  lwz     r3, 0x2c(r5)
/* 07D178 80082718 38C00000 */  li      r6, 0
/* 07D17C 8008271C 7CBC002E */  lwzx    r5, r28, r0
/* 07D180 80082720 5480023E */  clrlwi  r0, r4, 8
/* 07D184 80082724 38810034 */  addi    r4, r1, 0x34
/* 07D188 80082728 7CA50214 */  add     r5, r5, r0
/* 07D18C 8008272C 4BFEA975 */  bl      ramGetBuffer
/* 07D190 80082730 2C030000 */  cmpwi   r3, 0
/* 07D194 80082734 4182042C */  beq     lbl_80082B60
/* 07D198 80082738 A01C38D4 */  lhz     r0, 0x38d4(r28)
/* 07D19C 8008273C 57C3FC7E */  rlwinm  r3, r30, 0x1f, 0x11, 0x1f
/* 07D1A0 80082740 80BC3294 */  lwz     r5, 0x3294(r28)
/* 07D1A4 80082744 7C000E70 */  srawi   r0, r0, 1
/* 07D1A8 80082748 80810034 */  lwz     r4, 0x34(r1)
/* 07D1AC 8008274C 7C030214 */  add     r0, r3, r0
/* 07D1B0 80082750 5400083C */  slwi    r0, r0, 1
/* 07D1B4 80082754 7C650214 */  add     r3, r5, r0
/* 07D1B8 80082758 57C5A536 */  rlwinm  r5, r30, 0x14, 0x14, 0x1b
/* 07D1BC 8008275C 4BF84395 */  bl      xlHeapCopy
/* 07D1C0 80082760 48000400 */  b       lbl_80082B60
.global lbl_80082764
lbl_80082764:
/* 07D1C4 80082764 387C0000 */  addi    r3, r28, 0
/* 07D1C8 80082768 38BE0000 */  addi    r5, r30, 0
/* 07D1CC 8008276C 480067A9 */  bl      rspAResample1
/* 07D1D0 80082770 480003F0 */  b       lbl_80082B60
.global lbl_80082774
lbl_80082774:
/* 07D1D4 80082774 548356BA */  rlwinm  r3, r4, 0xa, 0x1a, 0x1d
/* 07D1D8 80082778 80BC38E8 */  lwz     r5, 0x38e8(r28)
/* 07D1DC 8008277C 38033254 */  addi    r0, r3, 0x3254
/* 07D1E0 80082780 8065002C */  lwz     r3, 0x2c(r5)
/* 07D1E4 80082784 38C00000 */  li      r6, 0
/* 07D1E8 80082788 7CBC002E */  lwzx    r5, r28, r0
/* 07D1EC 8008278C 5480023E */  clrlwi  r0, r4, 8
/* 07D1F0 80082790 38810030 */  addi    r4, r1, 0x30
/* 07D1F4 80082794 7CA50214 */  add     r5, r5, r0
/* 07D1F8 80082798 4BFEA909 */  bl      ramGetBuffer
/* 07D1FC 8008279C 2C030000 */  cmpwi   r3, 0
/* 07D200 800827A0 418203C0 */  beq     lbl_80082B60
/* 07D204 800827A4 A01C38D4 */  lhz     r0, 0x38d4(r28)
/* 07D208 800827A8 57C3FC7E */  rlwinm  r3, r30, 0x1f, 0x11, 0x1f
/* 07D20C 800827AC 809C3294 */  lwz     r4, 0x3294(r28)
/* 07D210 800827B0 57C5A536 */  rlwinm  r5, r30, 0x14, 0x14, 0x1b
/* 07D214 800827B4 7C000E70 */  srawi   r0, r0, 1
/* 07D218 800827B8 7C030214 */  add     r0, r3, r0
/* 07D21C 800827BC 80610030 */  lwz     r3, 0x30(r1)
/* 07D220 800827C0 5400083C */  slwi    r0, r0, 1
/* 07D224 800827C4 7C840214 */  add     r4, r4, r0
/* 07D228 800827C8 4BF84329 */  bl      xlHeapCopy
/* 07D22C 800827CC 48000394 */  b       lbl_80082B60
.global lbl_800827D0
lbl_800827D0:
/* 07D230 800827D0 548356BA */  rlwinm  r3, r4, 0xa, 0x1a, 0x1d
/* 07D234 800827D4 5484023E */  clrlwi  r4, r4, 8
/* 07D238 800827D8 38033254 */  addi    r0, r3, 0x3254
/* 07D23C 800827DC 7C9C012E */  stwx    r4, r28, r0
/* 07D240 800827E0 48000380 */  b       lbl_80082B60
.global lbl_800827E4
lbl_800827E4:
/* 07D244 800827E4 387C0000 */  addi    r3, r28, 0
/* 07D248 800827E8 38BE0000 */  addi    r5, r30, 0
/* 07D24C 800827EC 48006621 */  bl      rspASetBuffer1
/* 07D250 800827F0 48000370 */  b       lbl_80082B60
.global lbl_800827F4
lbl_800827F4:
/* 07D254 800827F4 A0BC38D4 */  lhz     r5, 0x38d4(r28)
/* 07D258 800827F8 5480843E */  srwi    r0, r4, 0x10
/* 07D25C 800827FC 57C3043E */  clrlwi  r3, r30, 0x10
/* 07D260 80082800 80FC3294 */  lwz     r7, 0x3294(r28)
/* 07D264 80082804 7C002A14 */  add     r0, r0, r5
/* 07D268 80082808 7C000E70 */  srawi   r0, r0, 1
/* 07D26C 8008280C 7CC32A14 */  add     r6, r3, r5
/* 07D270 80082810 7C000194 */  addze   r0, r0
/* 07D274 80082814 54030BFC */  rlwinm  r3, r0, 1, 0xf, 0x1e
/* 07D278 80082818 54C0003C */  rlwinm  r0, r6, 0, 0, 0x1e
/* 07D27C 8008281C 5485043E */  clrlwi  r5, r4, 0x10
/* 07D280 80082820 7C671A14 */  add     r3, r7, r3
/* 07D284 80082824 7C870214 */  add     r4, r7, r0
/* 07D288 80082828 4BF842C9 */  bl      xlHeapCopy
/* 07D28C 8008282C 48000334 */  b       lbl_80082B60
.global lbl_80082830
lbl_80082830:
/* 07D290 80082830 548356BA */  rlwinm  r3, r4, 0xa, 0x1a, 0x1d
/* 07D294 80082834 80BC38E8 */  lwz     r5, 0x38e8(r28)
/* 07D298 80082838 38033254 */  addi    r0, r3, 0x3254
/* 07D29C 8008283C 8065002C */  lwz     r3, 0x2c(r5)
/* 07D2A0 80082840 38C00000 */  li      r6, 0
/* 07D2A4 80082844 7CBC002E */  lwzx    r5, r28, r0
/* 07D2A8 80082848 5480023E */  clrlwi  r0, r4, 8
/* 07D2AC 8008284C 3881002C */  addi    r4, r1, 0x2c
/* 07D2B0 80082850 7CA50214 */  add     r5, r5, r0
/* 07D2B4 80082854 4BFEA84D */  bl      ramGetBuffer
/* 07D2B8 80082858 2C030000 */  cmpwi   r3, 0
/* 07D2BC 8008285C 41820304 */  beq     lbl_80082B60
/* 07D2C0 80082860 A01C38D6 */  lhz     r0, 0x38d6(r28)
/* 07D2C4 80082864 57C5043E */  clrlwi  r5, r30, 0x10
/* 07D2C8 80082868 807C3294 */  lwz     r3, 0x3294(r28)
/* 07D2CC 8008286C 7C000E70 */  srawi   r0, r0, 1
/* 07D2D0 80082870 8081002C */  lwz     r4, 0x2c(r1)
/* 07D2D4 80082874 5400083C */  slwi    r0, r0, 1
/* 07D2D8 80082878 7C630214 */  add     r3, r3, r0
/* 07D2DC 8008287C 4BF84275 */  bl      xlHeapCopy
/* 07D2E0 80082880 2C030000 */  cmpwi   r3, 0
/* 07D2E4 80082884 418202DC */  beq     lbl_80082B60
/* 07D2E8 80082888 7F83E378 */  mr      r3, r28
/* 07D2EC 8008288C 480087F5 */  bl      rspLoadADPCMCoefTable2
/* 07D2F0 80082890 480002D0 */  b       lbl_80082B60
.global lbl_80082894
lbl_80082894:
/* 07D2F4 80082894 387C0000 */  addi    r3, r28, 0
/* 07D2F8 80082898 38BE0000 */  addi    r5, r30, 0
/* 07D2FC 8008289C 480002F9 */  bl      rspAMix3
/* 07D300 800828A0 480002C0 */  b       lbl_80082B60
.global lbl_800828A4
lbl_800828A4:
/* 07D304 800828A4 A0BC38D4 */  lhz     r5, 0x38d4(r28)
/* 07D308 800828A8 5483843E */  srwi    r3, r4, 0x10
/* 07D30C 800828AC 5480043E */  clrlwi  r0, r4, 0x10
/* 07D310 800828B0 A0DC334E */  lhz     r6, 0x334e(r28)
/* 07D314 800828B4 7C632A14 */  add     r3, r3, r5
/* 07D318 800828B8 7C630E70 */  srawi   r3, r3, 1
/* 07D31C 800828BC 7C630194 */  addze   r3, r3
/* 07D320 800828C0 7C002A14 */  add     r0, r0, r5
/* 07D324 800828C4 7C000E70 */  srawi   r0, r0, 1
/* 07D328 800828C8 7C000194 */  addze   r0, r0
/* 07D32C 800828CC 54640BFC */  rlwinm  r4, r3, 1, 0xf, 0x1e
/* 07D330 800828D0 54050BFC */  rlwinm  r5, r0, 1, 0xf, 0x1e
/* 07D334 800828D4 54C3083C */  slwi    r3, r6, 1
/* 07D338 800828D8 38E00000 */  li      r7, 0
/* 07D33C 800828DC 48000030 */  b       lbl_8008290C
lbl_800828E0:
/* 07D340 800828E0 811C3294 */  lwz     r8, 0x3294(r28)
/* 07D344 800828E4 38030002 */  addi    r0, r3, 2
/* 07D348 800828E8 38E70001 */  addi    r7, r7, 1
/* 07D34C 800828EC 7CC822AE */  lhax    r6, r8, r4
/* 07D350 800828F0 38840002 */  addi    r4, r4, 2
/* 07D354 800828F4 7CC81B2E */  sthx    r6, r8, r3
/* 07D358 800828F8 38630004 */  addi    r3, r3, 4
/* 07D35C 800828FC 811C3294 */  lwz     r8, 0x3294(r28)
/* 07D360 80082900 7CC82AAE */  lhax    r6, r8, r5
/* 07D364 80082904 38A50002 */  addi    r5, r5, 2
/* 07D368 80082908 7CC8032E */  sthx    r6, r8, r0
lbl_8008290C:
/* 07D36C 8008290C A01C3344 */  lhz     r0, 0x3344(r28)
/* 07D370 80082910 7C070040 */  cmplw   r7, r0
/* 07D374 80082914 4180FFCC */  blt     lbl_800828E0
/* 07D378 80082918 48000248 */  b       lbl_80082B60
.global lbl_8008291C
lbl_8008291C:
/* 07D37C 8008291C 387C0000 */  addi    r3, r28, 0
/* 07D380 80082920 38BE0000 */  addi    r5, r30, 0
/* 07D384 80082924 48007559 */  bl      rspAPoleFilter1
/* 07D388 80082928 48000238 */  b       lbl_80082B60
.global lbl_8008292C
lbl_8008292C:
/* 07D38C 8008292C 548356BA */  rlwinm  r3, r4, 0xa, 0x1a, 0x1d
/* 07D390 80082930 38033254 */  addi    r0, r3, 0x3254
/* 07D394 80082934 7C7C002E */  lwzx    r3, r28, r0
/* 07D398 80082938 5480023E */  clrlwi  r0, r4, 8
/* 07D39C 8008293C 7C030214 */  add     r0, r3, r0
/* 07D3A0 80082940 901C3354 */  stw     r0, 0x3354(r28)
/* 07D3A4 80082944 4800021C */  b       lbl_80082B60
.global lbl_80082948
lbl_80082948:
/* 07D3A8 80082948 A0BC38D4 */  lhz     r5, 0x38d4(r28)
/* 07D3AC 8008294C 54847C7E */  srwi    r4, r4, 0x11
/* 07D3B0 80082950 57C3FC7E */  rlwinm  r3, r30, 0x1f, 0x11, 0x1f
/* 07D3B4 80082954 80DC3294 */  lwz     r6, 0x3294(r28)
/* 07D3B8 80082958 7CA50E70 */  srawi   r5, r5, 1
/* 07D3BC 8008295C 7C840734 */  extsh   r4, r4
/* 07D3C0 80082960 7C630734 */  extsh   r3, r3
/* 07D3C4 80082964 57C0863E */  rlwinm  r0, r30, 0x10, 0x18, 0x1f
/* 07D3C8 80082968 7C842A14 */  add     r4, r4, r5
/* 07D3CC 8008296C 7C632A14 */  add     r3, r3, r5
/* 07D3D0 80082970 5485083C */  slwi    r5, r4, 1
/* 07D3D4 80082974 5464083C */  slwi    r4, r3, 1
/* 07D3D8 80082978 7C000734 */  extsh   r0, r0
/* 07D3DC 8008297C 7C662A14 */  add     r3, r6, r5
/* 07D3E0 80082980 7C862214 */  add     r4, r6, r4
/* 07D3E4 80082984 5405083C */  slwi    r5, r0, 1
/* 07D3E8 80082988 4BF84169 */  bl      xlHeapCopy
/* 07D3EC 8008298C 480001D4 */  b       lbl_80082B60
.global lbl_80082990
lbl_80082990:
/* 07D3F0 80082990 A01C38D4 */  lhz     r0, 0x38d4(r28)
/* 07D3F4 80082994 57C7043F */  clrlwi. r7, r30, 0x10
/* 07D3F8 80082998 5483FC7E */  rlwinm  r3, r4, 0x1f, 0x11, 0x1f
/* 07D3FC 8008299C 7C060E70 */  srawi   r6, r0, 1
/* 07D400 800829A0 5480843E */  srwi    r0, r4, 0x10
/* 07D404 800829A4 7C000E70 */  srawi   r0, r0, 1
/* 07D408 800829A8 7CA33214 */  add     r5, r3, r6
/* 07D40C 800829AC 7C003214 */  add     r0, r0, r6
/* 07D410 800829B0 38800000 */  li      r4, 0
/* 07D414 800829B4 408101AC */  ble     lbl_80082B60
/* 07D418 800829B8 2C070008 */  cmpwi   r7, 8
/* 07D41C 800829BC 3907FFF8 */  addi    r8, r7, -8
/* 07D420 800829C0 408101B4 */  ble     lbl_80082B74
/* 07D424 800829C4 38680007 */  addi    r3, r8, 7
/* 07D428 800829C8 5463E8FE */  srwi    r3, r3, 3
/* 07D42C 800829CC 7C060378 */  mr      r6, r0
/* 07D430 800829D0 7C6903A6 */  mtctr   r3
/* 07D434 800829D4 2C080000 */  cmpwi   r8, 0
/* 07D438 800829D8 5408083C */  slwi    r8, r0, 1
/* 07D43C 800829DC 40810198 */  ble     lbl_80082B74
lbl_800829E0:
/* 07D440 800829E0 831C3294 */  lwz     r24, 0x3294(r28)
/* 07D444 800829E4 7C652214 */  add     r3, r5, r4
/* 07D448 800829E8 39830001 */  addi    r12, r3, 1
/* 07D44C 800829EC 7D7842AE */  lhax    r11, r24, r8
/* 07D450 800829F0 5469083C */  slwi    r9, r3, 1
/* 07D454 800829F4 3B230003 */  addi    r25, r3, 3
/* 07D458 800829F8 7D784B2E */  sthx    r11, r24, r9
/* 07D45C 800829FC 39460002 */  addi    r10, r6, 2
/* 07D460 80082A00 5558083C */  slwi    r24, r10, 1
/* 07D464 80082A04 835C3294 */  lwz     r26, 0x3294(r28)
/* 07D468 80082A08 39660004 */  addi    r11, r6, 4
/* 07D46C 80082A0C 39230002 */  addi    r9, r3, 2
/* 07D470 80082A10 7F1AC2AE */  lhax    r24, r26, r24
/* 07D474 80082A14 558C083C */  slwi    r12, r12, 1
/* 07D478 80082A18 3B630004 */  addi    r27, r3, 4
/* 07D47C 80082A1C 7F1A632E */  sthx    r24, r26, r12
/* 07D480 80082A20 3B460008 */  addi    r26, r6, 8
/* 07D484 80082A24 3BC6000A */  addi    r30, r6, 0xa
/* 07D488 80082A28 831C3294 */  lwz     r24, 0x3294(r28)
/* 07D48C 80082A2C 556B083C */  slwi    r11, r11, 1
/* 07D490 80082A30 39830005 */  addi    r12, r3, 5
/* 07D494 80082A34 7D785AAE */  lhax    r11, r24, r11
/* 07D498 80082A38 5529083C */  slwi    r9, r9, 1
/* 07D49C 80082A3C 39460006 */  addi    r10, r6, 6
/* 07D4A0 80082A40 7D784B2E */  sthx    r11, r24, r9
/* 07D4A4 80082A44 5558083C */  slwi    r24, r10, 1
/* 07D4A8 80082A48 39430006 */  addi    r10, r3, 6
/* 07D4AC 80082A4C 82FC3294 */  lwz     r23, 0x3294(r28)
/* 07D4B0 80082A50 3966000C */  addi    r11, r6, 0xc
/* 07D4B4 80082A54 3926000E */  addi    r9, r6, 0xe
/* 07D4B8 80082A58 7F17C2AE */  lhax    r24, r23, r24
/* 07D4BC 80082A5C 5739083C */  slwi    r25, r25, 1
/* 07D4C0 80082A60 38630007 */  addi    r3, r3, 7
/* 07D4C4 80082A64 7F17CB2E */  sthx    r24, r23, r25
/* 07D4C8 80082A68 575A083C */  slwi    r26, r26, 1
/* 07D4CC 80082A6C 577B083C */  slwi    r27, r27, 1
/* 07D4D0 80082A70 82FC3294 */  lwz     r23, 0x3294(r28)
/* 07D4D4 80082A74 57DE083C */  slwi    r30, r30, 1
/* 07D4D8 80082A78 558C083C */  slwi    r12, r12, 1
/* 07D4DC 80082A7C 7F57D2AE */  lhax    r26, r23, r26
/* 07D4E0 80082A80 556B083C */  slwi    r11, r11, 1
/* 07D4E4 80082A84 554A083C */  slwi    r10, r10, 1
/* 07D4E8 80082A88 7F57DB2E */  sthx    r26, r23, r27
/* 07D4EC 80082A8C 5529083C */  slwi    r9, r9, 1
/* 07D4F0 80082A90 5463083C */  slwi    r3, r3, 1
/* 07D4F4 80082A94 82FC3294 */  lwz     r23, 0x3294(r28)
/* 07D4F8 80082A98 38C60010 */  addi    r6, r6, 0x10
/* 07D4FC 80082A9C 39080020 */  addi    r8, r8, 0x20
/* 07D500 80082AA0 7FD7F2AE */  lhax    r30, r23, r30
/* 07D504 80082AA4 38840008 */  addi    r4, r4, 8
/* 07D508 80082AA8 7FD7632E */  sthx    r30, r23, r12
/* 07D50C 80082AAC 819C3294 */  lwz     r12, 0x3294(r28)
/* 07D510 80082AB0 7D6C5AAE */  lhax    r11, r12, r11
/* 07D514 80082AB4 7D6C532E */  sthx    r11, r12, r10
/* 07D518 80082AB8 815C3294 */  lwz     r10, 0x3294(r28)
/* 07D51C 80082ABC 7D2A4AAE */  lhax    r9, r10, r9
/* 07D520 80082AC0 7D2A1B2E */  sthx    r9, r10, r3
/* 07D524 80082AC4 4200FF1C */  bdnz    lbl_800829E0
/* 07D528 80082AC8 480000AC */  b       lbl_80082B74
lbl_80082ACC:
/* 07D52C 80082ACC 7C043850 */  subf    r0, r4, r7
/* 07D530 80082AD0 7C043800 */  cmpw    r4, r7
/* 07D534 80082AD4 7C0903A6 */  mtctr   r0
/* 07D538 80082AD8 5463083C */  slwi    r3, r3, 1
/* 07D53C 80082ADC 40800084 */  bge     lbl_80082B60
lbl_80082AE0:
/* 07D540 80082AE0 80FC3294 */  lwz     r7, 0x3294(r28)
/* 07D544 80082AE4 7C052214 */  add     r0, r5, r4
/* 07D548 80082AE8 5400083C */  slwi    r0, r0, 1
/* 07D54C 80082AEC 7CC71AAE */  lhax    r6, r7, r3
/* 07D550 80082AF0 38630004 */  addi    r3, r3, 4
/* 07D554 80082AF4 38840001 */  addi    r4, r4, 1
/* 07D558 80082AF8 7CC7032E */  sthx    r6, r7, r0
/* 07D55C 80082AFC 4200FFE4 */  bdnz    lbl_80082AE0
/* 07D560 80082B00 48000060 */  b       lbl_80082B60
.global lbl_80082B04
lbl_80082B04:
/* 07D564 80082B04 38A00000 */  li      r5, 0
/* 07D568 80082B08 B0BC3380 */  sth     r5, 0x3380(r28)
/* 07D56C 80082B0C 5483843E */  srwi    r3, r4, 0x10
/* 07D570 80082B10 57C0C42E */  rlwinm  r0, r30, 0x18, 0x10, 0x17
/* 07D574 80082B14 B0BC3382 */  sth     r5, 0x3382(r28)
/* 07D578 80082B18 B0BC3384 */  sth     r5, 0x3384(r28)
/* 07D57C 80082B1C B0BC3386 */  sth     r5, 0x3386(r28)
/* 07D580 80082B20 B0BC3388 */  sth     r5, 0x3388(r28)
/* 07D584 80082B24 B0BC338A */  sth     r5, 0x338a(r28)
/* 07D588 80082B28 B0BC338C */  sth     r5, 0x338c(r28)
/* 07D58C 80082B2C B0BC338E */  sth     r5, 0x338e(r28)
/* 07D590 80082B30 B07C3392 */  sth     r3, 0x3392(r28)
/* 07D594 80082B34 B09C3394 */  sth     r4, 0x3394(r28)
/* 07D598 80082B38 B01C3388 */  sth     r0, 0x3388(r28)
/* 07D59C 80082B3C 48000024 */  b       lbl_80082B60
.global lbl_80082B40
lbl_80082B40:
/* 07D5A0 80082B40 5480843E */  srwi    r0, r4, 0x10
/* 07D5A4 80082B44 B01C3380 */  sth     r0, 0x3380(r28)
/* 07D5A8 80082B48 B09C3384 */  sth     r4, 0x3384(r28)
/* 07D5AC 80082B4C 48000014 */  b       lbl_80082B60
.global lbl_80082B50
lbl_80082B50:
/* 07D5B0 80082B50 38600000 */  li      r3, 0
/* 07D5B4 80082B54 4800002C */  b       lbl_80082B80
lbl_80082B58:
/* 07D5B8 80082B58 3C60800F */  lis     r3, jtbl_800EE5D4@ha
/* 07D5BC 80082B5C 3BE3E5D4 */  addi    r31, r3, jtbl_800EE5D4@l
.global lbl_80082B60
lbl_80082B60:
/* 07D5C0 80082B60 80810038 */  lwz     r4, 0x38(r1)
/* 07D5C4 80082B64 7C04E840 */  cmplw   r4, r29
/* 07D5C8 80082B68 4180FB28 */  blt     lbl_80082690
/* 07D5CC 80082B6C 38600001 */  li      r3, 1
/* 07D5D0 80082B70 48000010 */  b       lbl_80082B80
lbl_80082B74:
/* 07D5D4 80082B74 5483083C */  slwi    r3, r4, 1
/* 07D5D8 80082B78 7C601A14 */  add     r3, r0, r3
/* 07D5DC 80082B7C 4BFFFF50 */  b       lbl_80082ACC
lbl_80082B80:
/* 07D5E0 80082B80 BAE10044 */  lmw     r23, 0x44(r1)
/* 07D5E4 80082B84 8001006C */  lwz     r0, 0x6c(r1)
/* 07D5E8 80082B88 38210068 */  addi    r1, r1, 0x68
/* 07D5EC 80082B8C 7C0803A6 */  mtlr    r0
/* 07D5F0 80082B90 4E800020 */  blr     
