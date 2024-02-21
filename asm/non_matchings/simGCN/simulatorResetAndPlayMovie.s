glabel simulatorResetAndPlayMovie
/* 004284 80009824 7C0802A6 */  mflr    r0
/* 004288 80009828 3C608010 */  lis     r3, mCard@ha
/* 00428C 8000982C 90010004 */  stw     r0, 4(r1)
/* 004290 80009830 386379B0 */  addi    r3, r3, mCard@l
/* 004294 80009834 9421FFD8 */  stwu    r1, -0x28(r1)
/* 004298 80009838 93E10024 */  stw     r31, 0x24(r1)
/* 00429C 8000983C 83ED88BC */  lwz     r31, rmode@sda21(r13)
/* 0042A0 80009840 4800FE31 */  bl      mcardWriteGameDataReset
/* 0042A4 80009844 38600001 */  li      r3, 1
/* 0042A8 80009848 4809DF61 */  bl      VISetBlack
/* 0042AC 8000984C 4809DDC1 */  bl      VIFlush
/* 0042B0 80009850 4809D0CD */  bl      VIWaitForRetrace
/* 0042B4 80009854 3C60F000 */  lis     r3, 0xf000
/* 0042B8 80009858 480A7075 */  bl      PADRecalibrate
/* 0042BC 8000985C 480A14F1 */  bl      GXAbortFrame
/* 0042C0 80009860 48094131 */  bl      LCDisable
/* 0042C4 80009864 4809D0B9 */  bl      VIWaitForRetrace
/* 0042C8 80009868 4BFFC561 */  bl      xlCoreReset
/* 0042CC 8000986C 38800000 */  li      r4, 0
/* 0042D0 80009870 98810014 */  stb     r4, 0x14(r1)
/* 0042D4 80009874 38000001 */  li      r0, 1
/* 0042D8 80009878 38600000 */  li      r3, 0
/* 0042DC 8000987C 98810015 */  stb     r4, 0x15(r1)
/* 0042E0 80009880 98810016 */  stb     r4, 0x16(r1)
/* 0042E4 80009884 98010017 */  stb     r0, 0x17(r1)
/* 0042E8 80009888 480AC515 */  bl      DEMOInit
/* 0042EC 8000988C 93ED88BC */  stw     r31, rmode@sda21(r13)
/* 0042F0 80009890 38600001 */  li      r3, 1
/* 0042F4 80009894 4809DF15 */  bl      VISetBlack
/* 0042F8 80009898 38600000 */  li      r3, 0
/* 0042FC 8000989C 480AEB39 */  bl      AIInit
/* 004300 800098A0 80010014 */  lwz     r0, 0x14(r1)
/* 004304 800098A4 3861000C */  addi    r3, r1, 0xc
/* 004308 800098A8 38800000 */  li      r4, 0
/* 00430C 800098AC 9001000C */  stw     r0, 0xc(r1)
/* 004310 800098B0 480A258D */  bl      GXSetCopyClear
/* 004314 800098B4 48005F51 */  bl      MovieInit
/* 004318 800098B8 3BE10008 */  addi    r31, r1, 8
lbl_800098BC:
/* 00431C 800098BC 48098A05 */  bl      OSGetTick
/* 004320 800098C0 800D8964 */  lwz     r0, gMovieErrorToggle@sda21(r13)
/* 004324 800098C4 2C000001 */  cmpwi   r0, 1
/* 004328 800098C8 4182FFF4 */  beq     lbl_800098BC
/* 00432C 800098CC 480AC8D1 */  bl      DEMOBeforeRender
/* 004330 800098D0 48005EFD */  bl      MovieDraw
/* 004334 800098D4 880D8DC8 */  lbz     r0, DemoStatEnable@sda21(r13)
/* 004338 800098D8 28000000 */  cmplwi  r0, 0
/* 00433C 800098DC 41820020 */  beq     lbl_800098FC
/* 004340 800098E0 480A1735 */  bl      GXDrawDone
/* 004344 800098E4 38600001 */  li      r3, 1
/* 004348 800098E8 480ADCD9 */  bl      DEMOUpdateStats
/* 00434C 800098EC 480ADD2D */  bl      DEMOPrintStats
/* 004350 800098F0 480A1725 */  bl      GXDrawDone
/* 004354 800098F4 38600000 */  li      r3, 0
/* 004358 800098F8 480ADCC9 */  bl      DEMOUpdateStats
lbl_800098FC:
/* 00435C 800098FC 38600001 */  li      r3, 1
/* 004360 80009900 38800003 */  li      r4, 3
/* 004364 80009904 38A00001 */  li      r5, 1
/* 004368 80009908 480A4BDD */  bl      GXSetZMode
/* 00436C 8000990C 38600001 */  li      r3, 1
/* 004370 80009910 480A4B7D */  bl      GXSetColorUpdate
/* 004374 80009914 806D8DAC */  lwz     r3, DemoCurrentBuffer@sda21(r13)
/* 004378 80009918 38800001 */  li      r4, 1
/* 00437C 8000991C 480A27B5 */  bl      GXCopyDisp
/* 004380 80009920 480A16F5 */  bl      GXDrawDone
/* 004384 80009924 806D8DAC */  lwz     r3, DemoCurrentBuffer@sda21(r13)
/* 004388 80009928 4809DE15 */  bl      VISetNextFrameBuffer
/* 00438C 8000992C 4809DCE1 */  bl      VIFlush
/* 004390 80009930 4809CFED */  bl      VIWaitForRetrace
/* 004394 80009934 800D8DAC */  lwz     r0, DemoCurrentBuffer@sda21(r13)
/* 004398 80009938 806D8DB4 */  lwz     r3, DemoFrameBuffer1@sda21(r13)
/* 00439C 8000993C 7C001840 */  cmplw   r0, r3
/* 0043A0 80009940 40820010 */  bne     lbl_80009950
/* 0043A4 80009944 800D8DB0 */  lwz     r0, DemoFrameBuffer2@sda21(r13)
/* 0043A8 80009948 900D8DAC */  stw     r0, DemoCurrentBuffer@sda21(r13)
/* 0043AC 8000994C 48000008 */  b       lbl_80009954
lbl_80009950:
/* 0043B0 80009950 906D8DAC */  stw     r3, DemoCurrentBuffer@sda21(r13)
lbl_80009954:
/* 0043B4 80009954 38600000 */  li      r3, 0
/* 0043B8 80009958 4809DE51 */  bl      VISetBlack
/* 0043BC 8000995C 80010014 */  lwz     r0, 0x14(r1)
/* 0043C0 80009960 387F0000 */  addi    r3, r31, 0
/* 0043C4 80009964 38800000 */  li      r4, 0
/* 0043C8 80009968 90010008 */  stw     r0, 8(r1)
/* 0043CC 8000996C 480A24D1 */  bl      GXSetCopyClear
/* 0043D0 80009970 38600000 */  li      r3, 0
/* 0043D4 80009974 38800000 */  li      r4, 0
/* 0043D8 80009978 48008335 */  bl      movieTestReset
/* 0043DC 8000997C 4BFFFF40 */  b       lbl_800098BC
