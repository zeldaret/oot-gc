# xlCoreGCN.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel xlCoreBeforeRender
/* 000000 800055A0 7C0802A6 */  mflr    r0
/* 000004 800055A4 90010004 */  stw     r0, 4(r1)
/* 000008 800055A8 9421FFE0 */  stwu    r1, -0x20(r1)
/* 00000C 800055AC 93E1001C */  stw     r31, 0x1c(r1)
/* 000010 800055B0 83ED88BC */  lwz     r31, rmode@sda21(r13)
/* 000014 800055B4 881F0018 */  lbz     r0, 0x18(r31)
/* 000018 800055B8 28000000 */  cmplwi  r0, 0
/* 00001C 800055BC 41820050 */  beq     lbl_8000560C
/* 000020 800055C0 480A2309 */  bl      VIGetNextField
/* 000024 800055C4 A0BF0004 */  lhz     r5, 4(r31)
/* 000028 800055C8 3C804330 */  lis     r4, 0x4330
/* 00002C 800055CC A01F0006 */  lhz     r0, 6(r31)
/* 000030 800055D0 90A10014 */  stw     r5, 0x14(r1)
/* 000034 800055D4 C0228004 */  lfs     f1, D_80135D04@sda21(r2)
/* 000038 800055D8 9001000C */  stw     r0, 0xc(r1)
/* 00003C 800055DC C8828010 */  lfd     f4, D_80135D10@sda21(r2)
/* 000040 800055E0 FC400890 */  fmr     f2, f1
/* 000044 800055E4 90810010 */  stw     r4, 0x10(r1)
/* 000048 800055E8 FCA00890 */  fmr     f5, f1
/* 00004C 800055EC C0C28008 */  lfs     f6, D_80135D08@sda21(r2)
/* 000050 800055F0 90810008 */  stw     r4, 8(r1)
/* 000054 800055F4 C8610010 */  lfd     f3, 0x10(r1)
/* 000058 800055F8 C8010008 */  lfd     f0, 8(r1)
/* 00005C 800055FC EC632028 */  fsubs   f3, f3, f4
/* 000060 80005600 EC802028 */  fsubs   f4, f0, f4
/* 000064 80005604 480A947D */  bl      GXSetViewportJitter
/* 000068 80005608 48000048 */  b       lbl_80005650
lbl_8000560C:
/* 00006C 8000560C A09F0004 */  lhz     r4, 4(r31)
/* 000070 80005610 3C604330 */  lis     r3, 0x4330
/* 000074 80005614 A01F0006 */  lhz     r0, 6(r31)
/* 000078 80005618 9081000C */  stw     r4, 0xc(r1)
/* 00007C 8000561C C0228004 */  lfs     f1, D_80135D04@sda21(r2)
/* 000080 80005620 90010014 */  stw     r0, 0x14(r1)
/* 000084 80005624 C8828010 */  lfd     f4, D_80135D10@sda21(r2)
/* 000088 80005628 FC400890 */  fmr     f2, f1
/* 00008C 8000562C 90610008 */  stw     r3, 8(r1)
/* 000090 80005630 FCA00890 */  fmr     f5, f1
/* 000094 80005634 C0C28008 */  lfs     f6, D_80135D08@sda21(r2)
/* 000098 80005638 90610010 */  stw     r3, 0x10(r1)
/* 00009C 8000563C C8610008 */  lfd     f3, 8(r1)
/* 0000A0 80005640 C8010010 */  lfd     f0, 0x10(r1)
/* 0000A4 80005644 EC632028 */  fsubs   f3, f3, f4
/* 0000A8 80005648 EC802028 */  fsubs   f4, f0, f4
/* 0000AC 8000564C 480A948D */  bl      GXSetViewport
lbl_80005650:
/* 0000B0 80005650 480A51D5 */  bl      GXInvalidateVtxCache
/* 0000B4 80005654 480A7935 */  bl      GXInvalidateTexAll
/* 0000B8 80005658 38600000 */  li      r3, 0
/* 0000BC 8000565C 480A5861 */  bl      GXSetDrawSync
/* 0000C0 80005660 80010024 */  lwz     r0, 0x24(r1)
/* 0000C4 80005664 83E1001C */  lwz     r31, 0x1c(r1)
/* 0000C8 80005668 38210020 */  addi    r1, r1, 0x20
/* 0000CC 8000566C 7C0803A6 */  mtlr    r0
/* 0000D0 80005670 4E800020 */  blr     

glabel main
/* 0000D4 80005674 7C0802A6 */  mflr    r0
/* 0000D8 80005678 3CA0800D */  lis     r5, gTgPcTPL@ha
/* 0000DC 8000567C 90010004 */  stw     r0, 4(r1)
/* 0000E0 80005680 9421FFD0 */  stwu    r1, -0x30(r1)
/* 0000E4 80005684 BF410018 */  stmw    r26, 0x18(r1)
/* 0000E8 80005688 3B853720 */  addi    r28, r5, gTgPcTPL@l
/* 0000EC 8000568C 906D88A0 */  stw     r3, gnCountArgument@sda21(r13)
/* 0000F0 80005690 38600001 */  li      r3, 1
/* 0000F4 80005694 908D88A4 */  stw     r4, gaszArgument@sda21(r13)
/* 0000F8 80005698 480AC179 */  bl      __PADDisableRecalibration
/* 0000FC 8000569C 48097021 */  bl      OSInitAlarm
/* 000100 800056A0 38600004 */  li      r3, 4
/* 000104 800056A4 64630004 */  oris    r3, r3, 4
/* 000108 800056A8 7C72E3A6 */  mtspr   0x392, r3
/* 00010C 800056AC 38600005 */  li      r3, 5
/* 000110 800056B0 64630005 */  oris    r3, r3, 5
/* 000114 800056B4 7C73E3A6 */  mtspr   0x393, r3
/* 000118 800056B8 38600006 */  li      r3, 6
/* 00011C 800056BC 64630006 */  oris    r3, r3, 6
/* 000120 800056C0 7C74E3A6 */  mtspr   0x394, r3
/* 000124 800056C4 38600007 */  li      r3, 7
/* 000128 800056C8 64630007 */  oris    r3, r3, 7
/* 00012C 800056CC 7C75E3A6 */  mtspr   0x395, r3
/* 000130 800056D0 38600000 */  li      r3, 0
/* 000134 800056D4 38800000 */  li      r4, 0
/* 000138 800056D8 480B32F9 */  bl      ARInit
/* 00013C 800056DC 480967A9 */  bl      OSInit
/* 000140 800056E0 480AD895 */  bl      DVDInit
/* 000144 800056E4 480A0D89 */  bl      VIInit
/* 000148 800056E8 480B1A71 */  bl      DEMOPadInit
/* 00014C 800056EC 38600000 */  li      r3, 0
/* 000150 800056F0 48000565 */  bl      xlCoreInitRenderMode
/* 000154 800056F4 48000489 */  bl      xlCoreInitMem
/* 000158 800056F8 806D88BC */  lwz     r3, rmode@sda21(r13)
/* 00015C 800056FC 480A16E9 */  bl      VIConfigure
/* 000160 80005700 806D8740 */  lwz     r3, __OSCurrHeap@sda21(r13)
/* 000164 80005704 3C800004 */  lis     r4, 4
/* 000168 80005708 480977BD */  bl      OSAllocFromHeap
/* 00016C 8000570C 906D88A8 */  stw     r3, DefaultFifo@sda21(r13)
/* 000170 80005710 3C800004 */  lis     r4, 4
/* 000174 80005714 806D88A8 */  lwz     r3, DefaultFifo@sda21(r13)
/* 000178 80005718 480A2E1D */  bl      GXInit
/* 00017C 8000571C 906D88AC */  stw     r3, DefaultFifoObj@sda21(r13)
/* 000180 80005720 48000201 */  bl      xlCoreInitGX
/* 000184 80005724 806D8DB4 */  lwz     r3, DemoFrameBuffer1@sda21(r13)
/* 000188 80005728 480A2015 */  bl      VISetNextFrameBuffer
/* 00018C 8000572C 800D8DB0 */  lwz     r0, DemoFrameBuffer2@sda21(r13)
/* 000190 80005730 900D8DAC */  stw     r0, DemoCurrentBuffer@sda21(r13)
/* 000194 80005734 480A1ED9 */  bl      VIFlush
/* 000198 80005738 480A11E5 */  bl      VIWaitForRetrace
/* 00019C 8000573C 808D88BC */  lwz     r4, rmode@sda21(r13)
/* 0001A0 80005740 80040000 */  lwz     r0, 0(r4)
/* 0001A4 80005744 540007FF */  clrlwi. r0, r0, 0x1f
/* 0001A8 80005748 41820008 */  beq     lbl_80005750
/* 0001AC 8000574C 480A11D1 */  bl      VIWaitForRetrace
lbl_80005750:
/* 0001B0 80005750 7F83E378 */  mr      r3, r28
/* 0001B4 80005754 480098CD */  bl      simulatorUnpackTexPalette
/* 0001B8 80005758 80028000 */  lwz     r0, D_80135D00@sda21(r2)
/* 0001BC 8000575C 3C80800F */  lis     r4, g_texMap@ha
/* 0001C0 80005760 3BA43F1C */  addi    r29, r4, g_texMap@l
/* 0001C4 80005764 90010010 */  stw     r0, 0x10(r1)
/* 0001C8 80005768 3B400000 */  li      r26, 0
/* 0001CC 8000576C 3BC00000 */  li      r30, 0
lbl_80005770:
/* 0001D0 80005770 387C0000 */  addi    r3, r28, 0
/* 0001D4 80005774 389A0000 */  addi    r4, r26, 0
/* 0001D8 80005778 480C37E5 */  bl      TEXGet
/* 0001DC 8000577C 80E30000 */  lwz     r7, 0(r3)
/* 0001E0 80005780 7C7DF214 */  add     r3, r29, r30
/* 0001E4 80005784 39000000 */  li      r8, 0
/* 0001E8 80005788 80870008 */  lwz     r4, 8(r7)
/* 0001EC 8000578C 39200000 */  li      r9, 0
/* 0001F0 80005790 A0A70002 */  lhz     r5, 2(r7)
/* 0001F4 80005794 39400000 */  li      r10, 0
/* 0001F8 80005798 A0C70000 */  lhz     r6, 0(r7)
/* 0001FC 8000579C 80E70004 */  lwz     r7, 4(r7)
/* 000200 800057A0 480A6FF9 */  bl      GXInitTexObj
/* 000204 800057A4 3B5A0001 */  addi    r26, r26, 1
/* 000208 800057A8 281A0002 */  cmplwi  r26, 2
/* 00020C 800057AC 3BDE0020 */  addi    r30, r30, 0x20
/* 000210 800057B0 4180FFC0 */  blt     lbl_80005770
/* 000214 800057B4 38600000 */  li      r3, 0
/* 000218 800057B8 480A6905 */  bl      GXSetDispCopyGamma
/* 00021C 800057BC 806D8740 */  lwz     r3, __OSCurrHeap@sda21(r13)
/* 000220 800057C0 48097969 */  bl      OSCheckHeap
/* 000224 800057C4 2C03FFFF */  cmpwi   r3, -1
/* 000228 800057C8 4182002C */  beq     lbl_800057F4
/* 00022C 800057CC 3BE30000 */  addi    r31, r3, 0
/* 000230 800057D0 3C000400 */  lis     r0, 0x400
/* 000234 800057D4 7C1F0000 */  cmpw    r31, r0
/* 000238 800057D8 40810008 */  ble     lbl_800057E0
/* 00023C 800057DC 3FE00400 */  lis     r31, 0x400
lbl_800057E0:
/* 000240 800057E0 806D8740 */  lwz     r3, __OSCurrHeap@sda21(r13)
/* 000244 800057E4 7FE4FB78 */  mr      r4, r31
/* 000248 800057E8 480976DD */  bl      OSAllocFromHeap
/* 00024C 800057EC 7C7B1B78 */  mr      r27, r3
/* 000250 800057F0 936D88B0 */  stw     r27, gpHeap@sda21(r13)
lbl_800057F4:
/* 000254 800057F4 48000619 */  bl      xlPostSetup
/* 000258 800057F8 2C030000 */  cmpwi   r3, 0
/* 00025C 800057FC 4082000C */  bne     lbl_80005808
/* 000260 80005800 38600000 */  li      r3, 0
/* 000264 80005804 480000C4 */  b       lbl_800058C8
lbl_80005808:
/* 000268 80005808 387B0000 */  addi    r3, r27, 0
/* 00026C 8000580C 389F0000 */  addi    r4, r31, 0
/* 000270 80005810 48000EA1 */  bl      xlHeapSetup
/* 000274 80005814 2C030000 */  cmpwi   r3, 0
/* 000278 80005818 4082000C */  bne     lbl_80005824
/* 00027C 8000581C 38600000 */  li      r3, 0
/* 000280 80005820 480000A8 */  b       lbl_800058C8
lbl_80005824:
/* 000284 80005824 48000A65 */  bl      xlListSetup
/* 000288 80005828 2C030000 */  cmpwi   r3, 0
/* 00028C 8000582C 4082000C */  bne     lbl_80005838
/* 000290 80005830 38600000 */  li      r3, 0
/* 000294 80005834 48000094 */  b       lbl_800058C8
lbl_80005838:
/* 000298 80005838 480023F9 */  bl      xlObjectSetup
/* 00029C 8000583C 2C030000 */  cmpwi   r3, 0
/* 0002A0 80005840 4082000C */  bne     lbl_8000584C
/* 0002A4 80005844 38600000 */  li      r3, 0
/* 0002A8 80005848 48000080 */  b       lbl_800058C8
lbl_8000584C:
/* 0002AC 8000584C 38600000 */  li      r3, 0
/* 0002B0 80005850 480ABFC1 */  bl      __PADDisableRecalibration
/* 0002B4 80005854 4800272D */  bl      xlMain
/* 0002B8 80005858 48002369 */  bl      xlObjectReset
/* 0002BC 8000585C 2C030000 */  cmpwi   r3, 0
/* 0002C0 80005860 4082000C */  bne     lbl_8000586C
/* 0002C4 80005864 38600000 */  li      r3, 0
/* 0002C8 80005868 48000060 */  b       lbl_800058C8
lbl_8000586C:
/* 0002CC 8000586C 48000A15 */  bl      xlListReset
/* 0002D0 80005870 2C030000 */  cmpwi   r3, 0
/* 0002D4 80005874 4082000C */  bne     lbl_80005880
/* 0002D8 80005878 38600000 */  li      r3, 0
/* 0002DC 8000587C 4800004C */  b       lbl_800058C8
lbl_80005880:
/* 0002E0 80005880 48000DC9 */  bl      xlHeapReset
/* 0002E4 80005884 2C030000 */  cmpwi   r3, 0
/* 0002E8 80005888 4082000C */  bne     lbl_80005894
/* 0002EC 8000588C 38600000 */  li      r3, 0
/* 0002F0 80005890 48000038 */  b       lbl_800058C8
lbl_80005894:
/* 0002F4 80005894 48000571 */  bl      xlPostReset
/* 0002F8 80005898 2C030000 */  cmpwi   r3, 0
/* 0002FC 8000589C 4082000C */  bne     lbl_800058A8
/* 000300 800058A0 38600000 */  li      r3, 0
/* 000304 800058A4 48000024 */  b       lbl_800058C8
lbl_800058A8:
/* 000308 800058A8 3C7C0001 */  addis   r3, r28, 1
/* 00030C 800058AC 4CC63182 */  crclr   6
/* 000310 800058B0 3CBC0001 */  addis   r5, r28, 1
/* 000314 800058B4 38800241 */  li      r4, 0x241
/* 000318 800058B8 38638084 */  addi    r3, r3, -32636
/* 00031C 800058BC 38A58090 */  addi    r5, r5, -32624
/* 000320 800058C0 48098DB9 */  bl      OSPanic
/* 000324 800058C4 38600000 */  li      r3, 0
lbl_800058C8:
/* 000328 800058C8 BB410018 */  lmw     r26, 0x18(r1)
/* 00032C 800058CC 80010034 */  lwz     r0, 0x34(r1)
/* 000330 800058D0 38210030 */  addi    r1, r1, 0x30
/* 000334 800058D4 7C0803A6 */  mtlr    r0
/* 000338 800058D8 4E800020 */  blr     

glabel xlCoreHiResolution
/* 00033C 800058DC 38600001 */  li      r3, 1
/* 000340 800058E0 4E800020 */  blr     

glabel xlCoreGetArgument
/* 000344 800058E4 2C030000 */  cmpwi   r3, 0
/* 000348 800058E8 41800028 */  blt     lbl_80005910
/* 00034C 800058EC 800D88A0 */  lwz     r0, gnCountArgument@sda21(r13)
/* 000350 800058F0 7C030000 */  cmpw    r3, r0
/* 000354 800058F4 4080001C */  bge     lbl_80005910
/* 000358 800058F8 80AD88A4 */  lwz     r5, gaszArgument@sda21(r13)
/* 00035C 800058FC 5460103A */  slwi    r0, r3, 2
/* 000360 80005900 38600001 */  li      r3, 1
/* 000364 80005904 7C05002E */  lwzx    r0, r5, r0
/* 000368 80005908 90040000 */  stw     r0, 0(r4)
/* 00036C 8000590C 4E800020 */  blr     
lbl_80005910:
/* 000370 80005910 38600000 */  li      r3, 0
/* 000374 80005914 4E800020 */  blr     

glabel xlCoreGetArgumentCount
/* 000378 80005918 806D88A0 */  lwz     r3, gnCountArgument@sda21(r13)
/* 00037C 8000591C 4E800020 */  blr     

xlCoreInitGX:
/* 000380 80005920 7C0802A6 */  mflr    r0
/* 000384 80005924 90010004 */  stw     r0, 4(r1)
/* 000388 80005928 9421FF40 */  stwu    r1, -0xc0(r1)
/* 00038C 8000592C 93E100BC */  stw     r31, 0xbc(r1)
/* 000390 80005930 3FE04330 */  lis     r31, 0x4330
/* 000394 80005934 808D88BC */  lwz     r4, rmode@sda21(r13)
/* 000398 80005938 C0228004 */  lfs     f1, D_80135D04@sda21(r2)
/* 00039C 8000593C A0640004 */  lhz     r3, 4(r4)
/* 0003A0 80005940 A0040006 */  lhz     r0, 6(r4)
/* 0003A4 80005944 FC400890 */  fmr     f2, f1
/* 0003A8 80005948 906100B4 */  stw     r3, 0xb4(r1)
/* 0003AC 8000594C FCA00890 */  fmr     f5, f1
/* 0003B0 80005950 C8828010 */  lfd     f4, D_80135D10@sda21(r2)
/* 0003B4 80005954 900100AC */  stw     r0, 0xac(r1)
/* 0003B8 80005958 C0C28008 */  lfs     f6, D_80135D08@sda21(r2)
/* 0003BC 8000595C 93E100B0 */  stw     r31, 0xb0(r1)
/* 0003C0 80005960 93E100A8 */  stw     r31, 0xa8(r1)
/* 0003C4 80005964 C86100B0 */  lfd     f3, 0xb0(r1)
/* 0003C8 80005968 C80100A8 */  lfd     f0, 0xa8(r1)
/* 0003CC 8000596C EC632028 */  fsubs   f3, f3, f4
/* 0003D0 80005970 EC802028 */  fsubs   f4, f0, f4
/* 0003D4 80005974 480A9165 */  bl      GXSetViewport
/* 0003D8 80005978 80CD88BC */  lwz     r6, rmode@sda21(r13)
/* 0003DC 8000597C 38600000 */  li      r3, 0
/* 0003E0 80005980 38800000 */  li      r4, 0
/* 0003E4 80005984 A0A60004 */  lhz     r5, 4(r6)
/* 0003E8 80005988 A0C60006 */  lhz     r6, 6(r6)
/* 0003EC 8000598C 480A9195 */  bl      GXSetScissor
/* 0003F0 80005990 80CD88BC */  lwz     r6, rmode@sda21(r13)
/* 0003F4 80005994 38600000 */  li      r3, 0
/* 0003F8 80005998 38800000 */  li      r4, 0
/* 0003FC 8000599C A0A60004 */  lhz     r5, 4(r6)
/* 000400 800059A0 A0C60006 */  lhz     r6, 6(r6)
/* 000404 800059A4 480A5EBD */  bl      GXSetDispCopySrc
/* 000408 800059A8 808D88BC */  lwz     r4, rmode@sda21(r13)
/* 00040C 800059AC A0640004 */  lhz     r3, 4(r4)
/* 000410 800059B0 A0840008 */  lhz     r4, 8(r4)
/* 000414 800059B4 480A5FA5 */  bl      GXSetDispCopyDst
/* 000418 800059B8 808D88BC */  lwz     r4, rmode@sda21(r13)
/* 00041C 800059BC C8428010 */  lfd     f2, D_80135D10@sda21(r2)
/* 000420 800059C0 A0640008 */  lhz     r3, 8(r4)
/* 000424 800059C4 A0040006 */  lhz     r0, 6(r4)
/* 000428 800059C8 906100A4 */  stw     r3, 0xa4(r1)
/* 00042C 800059CC 9001009C */  stw     r0, 0x9c(r1)
/* 000430 800059D0 93E100A0 */  stw     r31, 0xa0(r1)
/* 000434 800059D4 93E10098 */  stw     r31, 0x98(r1)
/* 000438 800059D8 C82100A0 */  lfd     f1, 0xa0(r1)
/* 00043C 800059DC C8010098 */  lfd     f0, 0x98(r1)
/* 000440 800059E0 EC211028 */  fsubs   f1, f1, f2
/* 000444 800059E4 EC001028 */  fsubs   f0, f0, f2
/* 000448 800059E8 EC210024 */  fdivs   f1, f1, f0
/* 00044C 800059EC 480A6385 */  bl      GXSetDispCopyYScale
/* 000450 800059F0 80ED88BC */  lwz     r7, rmode@sda21(r13)
/* 000454 800059F4 38C10018 */  addi    r6, r1, 0x18
/* 000458 800059F8 C8428010 */  lfd     f2, D_80135D10@sda21(r2)
/* 00045C 800059FC 38A00001 */  li      r5, 1
/* 000460 80005A00 88070032 */  lbz     r0, 0x32(r7)
/* 000464 80005A04 C0228008 */  lfs     f1, D_80135D08@sda21(r2)
/* 000468 80005A08 3887001A */  addi    r4, r7, 0x1a
/* 00046C 80005A0C 90010094 */  stw     r0, 0x94(r1)
/* 000470 80005A10 93E10090 */  stw     r31, 0x90(r1)
/* 000474 80005A14 C8010090 */  lfd     f0, 0x90(r1)
/* 000478 80005A18 EC001028 */  fsubs   f0, f0, f2
/* 00047C 80005A1C EC000072 */  fmuls   f0, f0, f1
/* 000480 80005A20 FC00001E */  fctiwz  f0, f0
/* 000484 80005A24 D8010088 */  stfd    f0, 0x88(r1)
/* 000488 80005A28 8001008C */  lwz     r0, 0x8c(r1)
/* 00048C 80005A2C 98010018 */  stb     r0, 0x18(r1)
/* 000490 80005A30 88070033 */  lbz     r0, 0x33(r7)
/* 000494 80005A34 90010084 */  stw     r0, 0x84(r1)
/* 000498 80005A38 93E10080 */  stw     r31, 0x80(r1)
/* 00049C 80005A3C C8010080 */  lfd     f0, 0x80(r1)
/* 0004A0 80005A40 EC001028 */  fsubs   f0, f0, f2
/* 0004A4 80005A44 EC000072 */  fmuls   f0, f0, f1
/* 0004A8 80005A48 FC00001E */  fctiwz  f0, f0
/* 0004AC 80005A4C D8010078 */  stfd    f0, 0x78(r1)
/* 0004B0 80005A50 8001007C */  lwz     r0, 0x7c(r1)
/* 0004B4 80005A54 98010019 */  stb     r0, 0x19(r1)
/* 0004B8 80005A58 88070034 */  lbz     r0, 0x34(r7)
/* 0004BC 80005A5C 90010074 */  stw     r0, 0x74(r1)
/* 0004C0 80005A60 93E10070 */  stw     r31, 0x70(r1)
/* 0004C4 80005A64 C8010070 */  lfd     f0, 0x70(r1)
/* 0004C8 80005A68 EC001028 */  fsubs   f0, f0, f2
/* 0004CC 80005A6C EC000072 */  fmuls   f0, f0, f1
/* 0004D0 80005A70 FC00001E */  fctiwz  f0, f0
/* 0004D4 80005A74 D8010068 */  stfd    f0, 0x68(r1)
/* 0004D8 80005A78 8001006C */  lwz     r0, 0x6c(r1)
/* 0004DC 80005A7C 9801001A */  stb     r0, 0x1a(r1)
/* 0004E0 80005A80 88070035 */  lbz     r0, 0x35(r7)
/* 0004E4 80005A84 90010064 */  stw     r0, 0x64(r1)
/* 0004E8 80005A88 93E10060 */  stw     r31, 0x60(r1)
/* 0004EC 80005A8C C8010060 */  lfd     f0, 0x60(r1)
/* 0004F0 80005A90 EC001028 */  fsubs   f0, f0, f2
/* 0004F4 80005A94 EC000072 */  fmuls   f0, f0, f1
/* 0004F8 80005A98 FC00001E */  fctiwz  f0, f0
/* 0004FC 80005A9C D8010058 */  stfd    f0, 0x58(r1)
/* 000500 80005AA0 8001005C */  lwz     r0, 0x5c(r1)
/* 000504 80005AA4 9801001B */  stb     r0, 0x1b(r1)
/* 000508 80005AA8 88070036 */  lbz     r0, 0x36(r7)
/* 00050C 80005AAC 90010054 */  stw     r0, 0x54(r1)
/* 000510 80005AB0 93E10050 */  stw     r31, 0x50(r1)
/* 000514 80005AB4 C8010050 */  lfd     f0, 0x50(r1)
/* 000518 80005AB8 EC001028 */  fsubs   f0, f0, f2
/* 00051C 80005ABC EC000072 */  fmuls   f0, f0, f1
/* 000520 80005AC0 FC00001E */  fctiwz  f0, f0
/* 000524 80005AC4 D8010048 */  stfd    f0, 0x48(r1)
/* 000528 80005AC8 8001004C */  lwz     r0, 0x4c(r1)
/* 00052C 80005ACC 9801001C */  stb     r0, 0x1c(r1)
/* 000530 80005AD0 88070037 */  lbz     r0, 0x37(r7)
/* 000534 80005AD4 90010044 */  stw     r0, 0x44(r1)
/* 000538 80005AD8 93E10040 */  stw     r31, 0x40(r1)
/* 00053C 80005ADC C8010040 */  lfd     f0, 0x40(r1)
/* 000540 80005AE0 EC001028 */  fsubs   f0, f0, f2
/* 000544 80005AE4 EC000072 */  fmuls   f0, f0, f1
/* 000548 80005AE8 FC00001E */  fctiwz  f0, f0
/* 00054C 80005AEC D8010038 */  stfd    f0, 0x38(r1)
/* 000550 80005AF0 8001003C */  lwz     r0, 0x3c(r1)
/* 000554 80005AF4 9801001D */  stb     r0, 0x1d(r1)
/* 000558 80005AF8 88070038 */  lbz     r0, 0x38(r7)
/* 00055C 80005AFC 90010034 */  stw     r0, 0x34(r1)
/* 000560 80005B00 93E10030 */  stw     r31, 0x30(r1)
/* 000564 80005B04 C8010030 */  lfd     f0, 0x30(r1)
/* 000568 80005B08 EC001028 */  fsubs   f0, f0, f2
/* 00056C 80005B0C EC000072 */  fmuls   f0, f0, f1
/* 000570 80005B10 FC00001E */  fctiwz  f0, f0
/* 000574 80005B14 D8010028 */  stfd    f0, 0x28(r1)
/* 000578 80005B18 8001002C */  lwz     r0, 0x2c(r1)
/* 00057C 80005B1C 9801001E */  stb     r0, 0x1e(r1)
/* 000580 80005B20 88670019 */  lbz     r3, 0x19(r7)
/* 000584 80005B24 480A6391 */  bl      GXSetCopyFilter
/* 000588 80005B28 806D88BC */  lwz     r3, rmode@sda21(r13)
/* 00058C 80005B2C 88030019 */  lbz     r0, 0x19(r3)
/* 000590 80005B30 28000000 */  cmplwi  r0, 0
/* 000594 80005B34 41820014 */  beq     lbl_80005B48
/* 000598 80005B38 38600002 */  li      r3, 2
/* 00059C 80005B3C 38800000 */  li      r4, 0
/* 0005A0 80005B40 480A8A0D */  bl      GXSetPixelFmt
/* 0005A4 80005B44 48000010 */  b       lbl_80005B54
lbl_80005B48:
/* 0005A8 80005B48 38600000 */  li      r3, 0
/* 0005AC 80005B4C 38800000 */  li      r4, 0
/* 0005B0 80005B50 480A89FD */  bl      GXSetPixelFmt
lbl_80005B54:
/* 0005B4 80005B54 806D8DAC */  lwz     r3, DemoCurrentBuffer@sda21(r13)
/* 0005B8 80005B58 38800001 */  li      r4, 1
/* 0005BC 80005B5C 480A6575 */  bl      GXCopyDisp
/* 0005C0 80005B60 38600000 */  li      r3, 0
/* 0005C4 80005B64 480A6559 */  bl      GXSetDispCopyGamma
/* 0005C8 80005B68 800100C4 */  lwz     r0, 0xc4(r1)
/* 0005CC 80005B6C 83E100BC */  lwz     r31, 0xbc(r1)
/* 0005D0 80005B70 382100C0 */  addi    r1, r1, 0xc0
/* 0005D4 80005B74 7C0803A6 */  mtlr    r0
/* 0005D8 80005B78 4E800020 */  blr     

xlCoreInitMem:
/* 0005DC 80005B7C 7C0802A6 */  mflr    r0
/* 0005E0 80005B80 90010004 */  stw     r0, 4(r1)
/* 0005E4 80005B84 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0005E8 80005B88 93E1000C */  stw     r31, 0xc(r1)
/* 0005EC 80005B8C 93C10008 */  stw     r30, 8(r1)
/* 0005F0 80005B90 48097901 */  bl      OSGetArenaLo
/* 0005F4 80005B94 7C7F1B78 */  mr      r31, r3
/* 0005F8 80005B98 93ED88B8 */  stw     r31, gArenaLo@sda21(r13)
/* 0005FC 80005B9C 480978ED */  bl      OSGetArenaHi
/* 000600 80005BA0 906D88B4 */  stw     r3, gArenaHi@sda21(r13)
/* 000604 80005BA4 381F001F */  addi    r0, r31, 0x1f
/* 000608 80005BA8 806D88BC */  lwz     r3, rmode@sda21(r13)
/* 00060C 80005BAC 54000034 */  rlwinm  r0, r0, 0, 0, 0x1a
/* 000610 80005BB0 A0830004 */  lhz     r4, 4(r3)
/* 000614 80005BB4 A0630008 */  lhz     r3, 8(r3)
/* 000618 80005BB8 3884000F */  addi    r4, r4, 0xf
/* 00061C 80005BBC 900D8DB4 */  stw     r0, DemoFrameBuffer1@sda21(r13)
/* 000620 80005BC0 54800436 */  rlwinm  r0, r4, 0, 0x10, 0x1b
/* 000624 80005BC4 7C6019D6 */  mullw   r3, r0, r3
/* 000628 80005BC8 800D8DB4 */  lwz     r0, DemoFrameBuffer1@sda21(r13)
/* 00062C 80005BCC 5463083C */  slwi    r3, r3, 1
/* 000630 80005BD0 3863001F */  addi    r3, r3, 0x1f
/* 000634 80005BD4 7C001A14 */  add     r0, r0, r3
/* 000638 80005BD8 54000034 */  rlwinm  r0, r0, 0, 0, 0x1a
/* 00063C 80005BDC 900D8DB0 */  stw     r0, DemoFrameBuffer2@sda21(r13)
/* 000640 80005BE0 808D8DB0 */  lwz     r4, DemoFrameBuffer2@sda21(r13)
/* 000644 80005BE4 7C041A14 */  add     r0, r4, r3
/* 000648 80005BE8 908D8DAC */  stw     r4, DemoCurrentBuffer@sda21(r13)
/* 00064C 80005BEC 54030034 */  rlwinm  r3, r0, 0, 0, 0x1a
/* 000650 80005BF0 480978B1 */  bl      OSSetArenaLo
/* 000654 80005BF4 4809789D */  bl      OSGetArenaLo
/* 000658 80005BF8 7C7F1B78 */  mr      r31, r3
/* 00065C 80005BFC 4809788D */  bl      OSGetArenaHi
/* 000660 80005C00 3BC30000 */  addi    r30, r3, 0
/* 000664 80005C04 387F0000 */  addi    r3, r31, 0
/* 000668 80005C08 389E0000 */  addi    r4, r30, 0
/* 00066C 80005C0C 38A00001 */  li      r5, 1
/* 000670 80005C10 4809743D */  bl      OSInitAlloc
/* 000674 80005C14 7C7F1B78 */  mr      r31, r3
/* 000678 80005C18 48097889 */  bl      OSSetArenaLo
/* 00067C 80005C1C 381F001F */  addi    r0, r31, 0x1f
/* 000680 80005C20 57DF0034 */  rlwinm  r31, r30, 0, 0, 0x1a
/* 000684 80005C24 54030034 */  rlwinm  r3, r0, 0, 0, 0x1a
/* 000688 80005C28 389F0000 */  addi    r4, r31, 0
/* 00068C 80005C2C 48097491 */  bl      OSCreateHeap
/* 000690 80005C30 4809740D */  bl      OSSetCurrentHeap
/* 000694 80005C34 7FE3FB78 */  mr      r3, r31
/* 000698 80005C38 48097869 */  bl      OSSetArenaLo
/* 00069C 80005C3C 80010014 */  lwz     r0, 0x14(r1)
/* 0006A0 80005C40 83E1000C */  lwz     r31, 0xc(r1)
/* 0006A4 80005C44 83C10008 */  lwz     r30, 8(r1)
/* 0006A8 80005C48 7C0803A6 */  mtlr    r0
/* 0006AC 80005C4C 38210010 */  addi    r1, r1, 0x10
/* 0006B0 80005C50 4E800020 */  blr     

xlCoreInitRenderMode:
/* 0006B4 80005C54 7C0802A6 */  mflr    r0
/* 0006B8 80005C58 28030000 */  cmplwi  r3, 0
/* 0006BC 80005C5C 90010004 */  stw     r0, 4(r1)
/* 0006C0 80005C60 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0006C4 80005C64 93E10014 */  stw     r31, 0x14(r1)
/* 0006C8 80005C68 4182000C */  beq     lbl_80005C74
/* 0006CC 80005C6C 906D88BC */  stw     r3, rmode@sda21(r13)
/* 0006D0 80005C70 48000144 */  b       lbl_80005DB4
lbl_80005C74:
/* 0006D4 80005C74 480A1D89 */  bl      VIGetTvFormat
/* 0006D8 80005C78 2C030001 */  cmpwi   r3, 1
/* 0006DC 80005C7C 418200DC */  beq     lbl_80005D58
/* 0006E0 80005C80 40800010 */  bge     lbl_80005C90
/* 0006E4 80005C84 2C030000 */  cmpwi   r3, 0
/* 0006E8 80005C88 40800014 */  bge     lbl_80005C9C
/* 0006EC 80005C8C 480000EC */  b       lbl_80005D78
lbl_80005C90:
/* 0006F0 80005C90 2C030003 */  cmpwi   r3, 3
/* 0006F4 80005C94 408000E4 */  bge     lbl_80005D78
/* 0006F8 80005C98 480000D0 */  b       lbl_80005D68
lbl_80005C9C:
/* 0006FC 80005C9C 808D88A0 */  lwz     r4, gnCountArgument@sda21(r13)
/* 000700 80005CA0 3C60800F */  lis     r3, GXNtsc480IntDf@ha
/* 000704 80005CA4 38031E60 */  addi    r0, r3, GXNtsc480IntDf@l
/* 000708 80005CA8 806D88A4 */  lwz     r3, gaszArgument@sda21(r13)
/* 00070C 80005CAC 2C040000 */  cmpwi   r4, 0
/* 000710 80005CB0 900D88BC */  stw     r0, rmode@sda21(r13)
/* 000714 80005CB4 7C8903A6 */  mtctr   r4
/* 000718 80005CB8 38A00000 */  li      r5, 0
/* 00071C 80005CBC 40810078 */  ble     lbl_80005D34
lbl_80005CC0:
/* 000720 80005CC0 2C050000 */  cmpwi   r5, 0
/* 000724 80005CC4 41800010 */  blt     lbl_80005CD4
/* 000728 80005CC8 7C052000 */  cmpw    r5, r4
/* 00072C 80005CCC 40800008 */  bge     lbl_80005CD4
/* 000730 80005CD0 83E30000 */  lwz     r31, 0(r3)
lbl_80005CD4:
/* 000734 80005CD4 881F0000 */  lbz     r0, 0(r31)
/* 000738 80005CD8 7C000774 */  extsb   r0, r0
/* 00073C 80005CDC 2C00002D */  cmpwi   r0, 0x2d
/* 000740 80005CE0 41820014 */  beq     lbl_80005CF4
/* 000744 80005CE4 2C00002F */  cmpwi   r0, 0x2f
/* 000748 80005CE8 4182000C */  beq     lbl_80005CF4
/* 00074C 80005CEC 2C00005C */  cmpwi   r0, 0x5c
/* 000750 80005CF0 40820038 */  bne     lbl_80005D28
lbl_80005CF4:
/* 000754 80005CF4 881F0001 */  lbz     r0, 1(r31)
/* 000758 80005CF8 7C000774 */  extsb   r0, r0
/* 00075C 80005CFC 2C000070 */  cmpwi   r0, 0x70
/* 000760 80005D00 4182000C */  beq     lbl_80005D0C
/* 000764 80005D04 2C000050 */  cmpwi   r0, 0x50
/* 000768 80005D08 40820020 */  bne     lbl_80005D28
lbl_80005D0C:
/* 00076C 80005D0C 881F0002 */  lbz     r0, 2(r31)
/* 000770 80005D10 2C000031 */  cmpwi   r0, 0x31
/* 000774 80005D14 40820014 */  bne     lbl_80005D28
/* 000778 80005D18 3C60800F */  lis     r3, GXNtsc480Prog@ha
/* 00077C 80005D1C 38031E9C */  addi    r0, r3, GXNtsc480Prog@l
/* 000780 80005D20 900D88BC */  stw     r0, rmode@sda21(r13)
/* 000784 80005D24 48000010 */  b       lbl_80005D34
lbl_80005D28:
/* 000788 80005D28 38630004 */  addi    r3, r3, 4
/* 00078C 80005D2C 38A50001 */  addi    r5, r5, 1
/* 000790 80005D30 4200FF90 */  bdnz    lbl_80005CC0
lbl_80005D34:
/* 000794 80005D34 808D88BC */  lwz     r4, rmode@sda21(r13)
/* 000798 80005D38 A064000A */  lhz     r3, 0xa(r4)
/* 00079C 80005D3C 3803FFE0 */  addi    r0, r3, -32
/* 0007A0 80005D40 B004000A */  sth     r0, 0xa(r4)
/* 0007A4 80005D44 808D88BC */  lwz     r4, rmode@sda21(r13)
/* 0007A8 80005D48 A064000E */  lhz     r3, 0xe(r4)
/* 0007AC 80005D4C 38030040 */  addi    r0, r3, 0x40
/* 0007B0 80005D50 B004000E */  sth     r0, 0xe(r4)
/* 0007B4 80005D54 48000040 */  b       lbl_80005D94
lbl_80005D58:
/* 0007B8 80005D58 3C60800F */  lis     r3, GXPal528IntDf@ha
/* 0007BC 80005D5C 38031F14 */  addi    r0, r3, GXPal528IntDf@l
/* 0007C0 80005D60 900D88BC */  stw     r0, rmode@sda21(r13)
/* 0007C4 80005D64 48000030 */  b       lbl_80005D94
lbl_80005D68:
/* 0007C8 80005D68 3C60800F */  lis     r3, GXMpal480IntDf@ha
/* 0007CC 80005D6C 38031ED8 */  addi    r0, r3, GXMpal480IntDf@l
/* 0007D0 80005D70 900D88BC */  stw     r0, rmode@sda21(r13)
/* 0007D4 80005D74 48000020 */  b       lbl_80005D94
lbl_80005D78:
/* 0007D8 80005D78 3C60800E */  lis     r3, D_800DB7A4@ha
/* 0007DC 80005D7C 4CC63182 */  crclr   6
/* 0007E0 80005D80 3C80800E */  lis     r4, D_800DB7BC@ha
/* 0007E4 80005D84 38A4B7BC */  addi    r5, r4, D_800DB7BC@l
/* 0007E8 80005D88 3863B7A4 */  addi    r3, r3, D_800DB7A4@l
/* 0007EC 80005D8C 388000B6 */  li      r4, 0xb6
/* 0007F0 80005D90 480988E9 */  bl      OSPanic
lbl_80005D94:
/* 0007F4 80005D94 3C80800F */  lis     r4, rmodeobj@ha
/* 0007F8 80005D98 806D88BC */  lwz     r3, rmode@sda21(r13)
/* 0007FC 80005D9C 3BE43EE0 */  addi    r31, r4, rmodeobj@l
/* 000800 80005DA0 389F0000 */  addi    r4, r31, 0
/* 000804 80005DA4 38A00000 */  li      r5, 0
/* 000808 80005DA8 38C00000 */  li      r6, 0
/* 00080C 80005DAC 480A5971 */  bl      GXAdjustForOverscan
/* 000810 80005DB0 93ED88BC */  stw     r31, rmode@sda21(r13)
lbl_80005DB4:
/* 000814 80005DB4 8001001C */  lwz     r0, 0x1c(r1)
/* 000818 80005DB8 83E10014 */  lwz     r31, 0x14(r1)
/* 00081C 80005DBC 38210018 */  addi    r1, r1, 0x18
/* 000820 80005DC0 7C0803A6 */  mtlr    r0
/* 000824 80005DC4 4E800020 */  blr     

glabel xlCoreReset
/* 000828 80005DC8 7C0802A6 */  mflr    r0
/* 00082C 80005DCC 90010004 */  stw     r0, 4(r1)
/* 000830 80005DD0 9421FFF8 */  stwu    r1, -8(r1)
/* 000834 80005DD4 806D8740 */  lwz     r3, __OSCurrHeap@sda21(r13)
/* 000838 80005DD8 808D88B0 */  lwz     r4, gpHeap@sda21(r13)
/* 00083C 80005DDC 480971E5 */  bl      OSFreeToHeap
/* 000840 80005DE0 806D88B8 */  lwz     r3, gArenaLo@sda21(r13)
/* 000844 80005DE4 480976BD */  bl      OSSetArenaLo
/* 000848 80005DE8 806D88B4 */  lwz     r3, gArenaHi@sda21(r13)
/* 00084C 80005DEC 480976AD */  bl      OSSetArenaHi
/* 000850 80005DF0 8001000C */  lwz     r0, 0xc(r1)
/* 000854 80005DF4 38600001 */  li      r3, 1
/* 000858 80005DF8 38210008 */  addi    r1, r1, 8
/* 00085C 80005DFC 7C0803A6 */  mtlr    r0
/* 000860 80005E00 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000D07A0 800D3720 8081 */
glabel gTgPcTPL
    .incbin "SIM_original.elf", 0x000D07A0, 0x00008081

.balign 4

/* 000D8824 800DB7A4 000C */
D_800DB7A4:
    .asciz "xlCoreGCN.c"
    .balign 4

/* 000D8830 800DB7B0 000B */
D_800DB7B0:
    .asciz "CORE DONE!"
    .balign 4

/* 000D883C 800DB7BC 001D */
D_800DB7BC:
    .asciz "DEMOInit: invalid TV format\n"
    .balign 4

.section .bss, "wa"

.balign 4

/* 000F0F60 800F3EE0 003C */
rmodeobj:
    .skip 60

/* 000F0F9C 800F3F1C 0080 */
glabel g_texMap
    .skip 128

.section .sbss, "wa"

.balign 8

/* 000F1800 80135580 0004 */
gnCountArgument:
    .skip 4

/* 000F1804 80135584 0004 */
gaszArgument:
    .skip 4

/* 000F1808 80135588 0004 */
DefaultFifo:
    .skip 4

/* 000F180C 8013558C 0004 */
DefaultFifoObj:
    .skip 4

/* 000F1810 80135590 0004 */
gpHeap:
    .skip 4

/* 000F1814 80135594 0004 */
gArenaHi:
    .skip 4

/* 000F1818 80135598 0004 */
gArenaLo:
    .skip 4

/* 000F181C 8013559C 0004 */
glabel rmode
    .skip 4

.section .sdata2, "wa"

.balign 8

/* 000F1800 80135D00 0004 */
D_80135D00:
    .long 0x00000000

/* 000F1804 80135D04 0004 */
D_80135D04:
    .float 0.0

/* 000F1808 80135D08 0004 */
D_80135D08:
    .float 1.0

.balign 8

/* 000F1810 80135D10 0008 */
D_80135D10:
    .double 4503599627370496.0
