glabel movieDrawImage
/* 00CD94 80012334 7C0802A6 */  mflr    r0
/* 00CD98 80012338 3CC0800D */  lis     r6, D_800D3160@ha
/* 00CD9C 8001233C 90010004 */  stw     r0, 4(r1)
/* 00CDA0 80012340 39063160 */  addi    r8, r6, D_800D3160@l
/* 00CDA4 80012344 3CC0800D */  lis     r6, D_800D3190@ha
/* 00CDA8 80012348 9421FF10 */  stwu    r1, -0xf0(r1)
/* 00CDAC 8001234C 3D208010 */  lis     r9, FreeReadBufferQueue@ha
/* 00CDB0 80012350 BF2100D4 */  stmw    r25, 0xd4(r1)
/* 00CDB4 80012354 3B230000 */  addi    r25, r3, 0
/* 00CDB8 80012358 3B440000 */  addi    r26, r4, 0
/* 00CDBC 8001235C 3B650000 */  addi    r27, r5, 0
/* 00CDC0 80012360 3B89B1C0 */  addi    r28, r9, FreeReadBufferQueue@l
/* 00CDC4 80012364 80E80000 */  lwz     r7, 0(r8)
/* 00CDC8 80012368 80080004 */  lwz     r0, 4(r8)
/* 00CDCC 8001236C 90E10078 */  stw     r7, 0x78(r1)
/* 00CDD0 80012370 9001007C */  stw     r0, 0x7c(r1)
/* 00CDD4 80012374 80680008 */  lwz     r3, 8(r8)
/* 00CDD8 80012378 8008000C */  lwz     r0, 0xc(r8)
/* 00CDDC 8001237C 90610080 */  stw     r3, 0x80(r1)
/* 00CDE0 80012380 90010084 */  stw     r0, 0x84(r1)
/* 00CDE4 80012384 80680010 */  lwz     r3, 0x10(r8)
/* 00CDE8 80012388 80080014 */  lwz     r0, 0x14(r8)
/* 00CDEC 8001238C 90610088 */  stw     r3, 0x88(r1)
/* 00CDF0 80012390 9001008C */  stw     r0, 0x8c(r1)
/* 00CDF4 80012394 80680018 */  lwz     r3, 0x18(r8)
/* 00CDF8 80012398 8008001C */  lwz     r0, 0x1c(r8)
/* 00CDFC 8001239C 90610090 */  stw     r3, 0x90(r1)
/* 00CE00 800123A0 90010094 */  stw     r0, 0x94(r1)
/* 00CE04 800123A4 80680020 */  lwz     r3, 0x20(r8)
/* 00CE08 800123A8 80080024 */  lwz     r0, 0x24(r8)
/* 00CE0C 800123AC 90610098 */  stw     r3, 0x98(r1)
/* 00CE10 800123B0 9001009C */  stw     r0, 0x9c(r1)
/* 00CE14 800123B4 80680028 */  lwz     r3, 0x28(r8)
/* 00CE18 800123B8 8008002C */  lwz     r0, 0x2c(r8)
/* 00CE1C 800123BC 906100A0 */  stw     r3, 0xa0(r1)
/* 00CE20 800123C0 900100A4 */  stw     r0, 0xa4(r1)
/* 00CE24 800123C4 84663190 */  lwzu    r3, D_800D3190@l(r6)
/* 00CE28 800123C8 80060004 */  lwz     r0, 4(r6)
/* 00CE2C 800123CC 90610048 */  stw     r3, 0x48(r1)
/* 00CE30 800123D0 9001004C */  stw     r0, 0x4c(r1)
/* 00CE34 800123D4 80660008 */  lwz     r3, 8(r6)
/* 00CE38 800123D8 8006000C */  lwz     r0, 0xc(r6)
/* 00CE3C 800123DC 90610050 */  stw     r3, 0x50(r1)
/* 00CE40 800123E0 90010054 */  stw     r0, 0x54(r1)
/* 00CE44 800123E4 80660010 */  lwz     r3, 0x10(r6)
/* 00CE48 800123E8 80060014 */  lwz     r0, 0x14(r6)
/* 00CE4C 800123EC 90610058 */  stw     r3, 0x58(r1)
/* 00CE50 800123F0 9001005C */  stw     r0, 0x5c(r1)
/* 00CE54 800123F4 80660018 */  lwz     r3, 0x18(r6)
/* 00CE58 800123F8 8006001C */  lwz     r0, 0x1c(r6)
/* 00CE5C 800123FC 90610060 */  stw     r3, 0x60(r1)
/* 00CE60 80012400 90010064 */  stw     r0, 0x64(r1)
/* 00CE64 80012404 80660020 */  lwz     r3, 0x20(r6)
/* 00CE68 80012408 80060024 */  lwz     r0, 0x24(r6)
/* 00CE6C 8001240C 90610068 */  stw     r3, 0x68(r1)
/* 00CE70 80012410 9001006C */  stw     r0, 0x6c(r1)
/* 00CE74 80012414 80660028 */  lwz     r3, 0x28(r6)
/* 00CE78 80012418 8006002C */  lwz     r0, 0x2c(r6)
/* 00CE7C 8001241C 90610070 */  stw     r3, 0x70(r1)
/* 00CE80 80012420 90010074 */  stw     r0, 0x74(r1)
/* 00CE84 80012424 4800042D */  bl      movieGXInit
/* 00CE88 80012428 4BFF3179 */  bl      xlCoreBeforeRender
/* 00CE8C 8001242C 38600000 */  li      r3, 0
/* 00CE90 80012430 38800003 */  li      r4, 3
/* 00CE94 80012434 38A00000 */  li      r5, 0
/* 00CE98 80012438 4809C0AD */  bl      GXSetZMode
/* 00CE9C 8001243C 38600001 */  li      r3, 1
/* 00CEA0 80012440 4809C0D9 */  bl      GXSetZCompLoc
/* 00CEA4 80012444 38600001 */  li      r3, 1
/* 00CEA8 80012448 4809BAD1 */  bl      GXSetNumTevStages
/* 00CEAC 8001244C 38600001 */  li      r3, 1
/* 00CEB0 80012450 4809A18D */  bl      GXSetNumChans
/* 00CEB4 80012454 38600000 */  li      r3, 0
/* 00CEB8 80012458 4809865D */  bl      GXSetNumTexGens
/* 00CEBC 8001245C C02280B8 */  lfs     f1, D_80135DB8@sda21(r2)
/* 00CEC0 80012460 387C13F0 */  addi    r3, r28, 0x13f0
/* 00CEC4 80012464 C04280BC */  lfs     f2, D_80135DBC@sda21(r2)
/* 00CEC8 80012468 FC600890 */  fmr     f3, f1
/* 00CECC 8001246C C08280C0 */  lfs     f4, D_80135DC0@sda21(r2)
/* 00CED0 80012470 C0A280C4 */  lfs     f5, D_80135DC4@sda21(r2)
/* 00CED4 80012474 C0C280C8 */  lfs     f6, D_80135DC8@sda21(r2)
/* 00CED8 80012478 48095C71 */  bl      C_MTXOrtho
/* 00CEDC 8001247C 387C13F0 */  addi    r3, r28, 0x13f0
/* 00CEE0 80012480 38800001 */  li      r4, 1
/* 00CEE4 80012484 4809C2B5 */  bl      GXSetProjection
/* 00CEE8 80012488 38600001 */  li      r3, 1
/* 00CEEC 8001248C 4809A151 */  bl      GXSetNumChans
/* 00CEF0 80012490 C02280CC */  lfs     f1, D_80135DCC@sda21(r2)
/* 00CEF4 80012494 38610048 */  addi    r3, r1, 0x48
/* 00CEF8 80012498 C04280D0 */  lfs     f2, D_80135DD0@sda21(r2)
/* 00CEFC 8001249C 38810018 */  addi    r4, r1, 0x18
/* 00CF00 800124A0 C06280B8 */  lfs     f3, D_80135DB8@sda21(r2)
/* 00CF04 800124A4 48095A55 */  bl      PSMTXTransApply
/* 00CF08 800124A8 C02280AC */  lfs     f1, D_80135DAC@sda21(r2)
/* 00CF0C 800124AC 38610018 */  addi    r3, r1, 0x18
/* 00CF10 800124B0 C06280D4 */  lfs     f3, D_80135DD4@sda21(r2)
/* 00CF14 800124B4 7C641B78 */  mr      r4, r3
/* 00CF18 800124B8 FC400890 */  fmr     f2, f1
/* 00CF1C 800124BC 48095AB1 */  bl      PSMTXScaleApply
/* 00CF20 800124C0 38610018 */  addi    r3, r1, 0x18
/* 00CF24 800124C4 38800000 */  li      r4, 0
/* 00CF28 800124C8 4809C3A1 */  bl      GXLoadPosMtxImm
/* 00CF2C 800124CC 38610078 */  addi    r3, r1, 0x78
/* 00CF30 800124D0 3880003C */  li      r4, 0x3c
/* 00CF34 800124D4 38A00000 */  li      r5, 0
/* 00CF38 800124D8 4809C465 */  bl      GXLoadTexMtxImm
/* 00CF3C 800124DC 3BA00000 */  li      r29, 0
/* 00CF40 800124E0 9BA100A8 */  stb     r29, 0xa8(r1)
/* 00CF44 800124E4 380000FF */  li      r0, 0xff
/* 00CF48 800124E8 38810014 */  addi    r4, r1, 0x14
/* 00CF4C 800124EC 9BA100A9 */  stb     r29, 0xa9(r1)
/* 00CF50 800124F0 38600001 */  li      r3, 1
/* 00CF54 800124F4 9BA100AA */  stb     r29, 0xaa(r1)
/* 00CF58 800124F8 980100AB */  stb     r0, 0xab(r1)
/* 00CF5C 800124FC 800100A8 */  lwz     r0, 0xa8(r1)
/* 00CF60 80012500 90010014 */  stw     r0, 0x14(r1)
/* 00CF64 80012504 4809B4BD */  bl      GXSetTevColor
/* 00CF68 80012508 38600000 */  li      r3, 0
/* 00CF6C 8001250C 38800000 */  li      r4, 0
/* 00CF70 80012510 38A00000 */  li      r5, 0
/* 00CF74 80012514 38C00000 */  li      r6, 0
/* 00CF78 80012518 38E00000 */  li      r7, 0
/* 00CF7C 8001251C 39000000 */  li      r8, 0
/* 00CF80 80012520 4809B3D1 */  bl      GXSetTevColorOp
/* 00CF84 80012524 38600000 */  li      r3, 0
/* 00CF88 80012528 38800000 */  li      r4, 0
/* 00CF8C 8001252C 38A00000 */  li      r5, 0
/* 00CF90 80012530 38C00000 */  li      r6, 0
/* 00CF94 80012534 38E00000 */  li      r7, 0
/* 00CF98 80012538 39000000 */  li      r8, 0
/* 00CF9C 8001253C 4809B41D */  bl      GXSetTevAlphaOp
/* 00CFA0 80012540 38600000 */  li      r3, 0
/* 00CFA4 80012544 3880000F */  li      r4, 0xf
/* 00CFA8 80012548 38A0000F */  li      r5, 0xf
/* 00CFAC 8001254C 38C0000F */  li      r6, 0xf
/* 00CFB0 80012550 38E00002 */  li      r7, 2
/* 00CFB4 80012554 4809B315 */  bl      GXSetTevColorIn
/* 00CFB8 80012558 38600000 */  li      r3, 0
/* 00CFBC 8001255C 38800007 */  li      r4, 7
/* 00CFC0 80012560 38A00007 */  li      r5, 7
/* 00CFC4 80012564 38C00007 */  li      r6, 7
/* 00CFC8 80012568 38E00006 */  li      r7, 6
/* 00CFCC 8001256C 4809B341 */  bl      GXSetTevAlphaIn
/* 00CFD0 80012570 38600000 */  li      r3, 0
/* 00CFD4 80012574 388000FF */  li      r4, 0xff
/* 00CFD8 80012578 38A000FF */  li      r5, 0xff
/* 00CFDC 8001257C 38C000FF */  li      r6, 0xff
/* 00CFE0 80012580 4809B7FD */  bl      GXSetTevOrder
/* 00CFE4 80012584 38600000 */  li      r3, 0
/* 00CFE8 80012588 38800004 */  li      r4, 4
/* 00CFEC 8001258C 38A00005 */  li      r5, 5
/* 00CFF0 80012590 38C00005 */  li      r6, 5
/* 00CFF4 80012594 4809BEA5 */  bl      GXSetBlendMode
/* 00CFF8 80012598 48097C51 */  bl      GXClearVtxDesc
/* 00CFFC 8001259C 38600009 */  li      r3, 9
/* 00D000 800125A0 38800001 */  li      r4, 1
/* 00D004 800125A4 480977F9 */  bl      GXSetVtxDesc
/* 00D008 800125A8 38600000 */  li      r3, 0
/* 00D00C 800125AC 38800009 */  li      r4, 9
/* 00D010 800125B0 38A00001 */  li      r5, 1
/* 00D014 800125B4 38C00004 */  li      r6, 4
/* 00D018 800125B8 38E00000 */  li      r7, 0
/* 00D01C 800125BC 48097C65 */  bl      GXSetVtxAttrFmt
/* 00D020 800125C0 38600080 */  li      r3, 0x80
/* 00D024 800125C4 38800000 */  li      r4, 0
/* 00D028 800125C8 38A00004 */  li      r5, 4
/* 00D02C 800125CC 48098E95 */  bl      GXBegin
/* 00D030 800125D0 C04280B8 */  lfs     f2, D_80135DB8@sda21(r2)
/* 00D034 800125D4 3FC0CC01 */  lis     r30, 0xcc01
/* 00D038 800125D8 C02280C0 */  lfs     f1, D_80135DC0@sda21(r2)
/* 00D03C 800125DC D05E8000 */  stfs    f2, -0x8000(r30)
/* 00D040 800125E0 C00280BC */  lfs     f0, D_80135DBC@sda21(r2)
/* 00D044 800125E4 D05E8000 */  stfs    f2, -0x8000(r30)
/* 00D048 800125E8 D05E8000 */  stfs    f2, -0x8000(r30)
/* 00D04C 800125EC D03E8000 */  stfs    f1, -0x8000(r30)
/* 00D050 800125F0 D05E8000 */  stfs    f2, -0x8000(r30)
/* 00D054 800125F4 D05E8000 */  stfs    f2, -0x8000(r30)
/* 00D058 800125F8 D03E8000 */  stfs    f1, -0x8000(r30)
/* 00D05C 800125FC D01E8000 */  stfs    f0, -0x8000(r30)
/* 00D060 80012600 D05E8000 */  stfs    f2, -0x8000(r30)
/* 00D064 80012604 D05E8000 */  stfs    f2, -0x8000(r30)
/* 00D068 80012608 D01E8000 */  stfs    f0, -0x8000(r30)
/* 00D06C 8001260C D05E8000 */  stfs    f2, -0x8000(r30)
/* 00D070 80012610 48000241 */  bl      movieGXInit
/* 00D074 80012614 3C60800F */  lis     r3, Vert_s16@ha
/* 00D078 80012618 3BE39960 */  addi    r31, r3, Vert_s16@l
/* 00D07C 8001261C B35F0000 */  sth     r26, 0(r31)
/* 00D080 80012620 7F460734 */  extsh   r6, r26
/* 00D084 80012624 7F670734 */  extsh   r7, r27
/* 00D088 80012628 B37F0002 */  sth     r27, 2(r31)
/* 00D08C 8001262C 387F0000 */  addi    r3, r31, 0
/* 00D090 80012630 38800018 */  li      r4, 0x18
/* 00D094 80012634 80B90008 */  lwz     r5, 8(r25)
/* 00D098 80012638 80A50000 */  lwz     r5, 0(r5)
/* 00D09C 8001263C A0050002 */  lhz     r0, 2(r5)
/* 00D0A0 80012640 7C060214 */  add     r0, r6, r0
/* 00D0A4 80012644 B01F0006 */  sth     r0, 6(r31)
/* 00D0A8 80012648 B37F0008 */  sth     r27, 8(r31)
/* 00D0AC 8001264C 80B90008 */  lwz     r5, 8(r25)
/* 00D0B0 80012650 80A50000 */  lwz     r5, 0(r5)
/* 00D0B4 80012654 A0050002 */  lhz     r0, 2(r5)
/* 00D0B8 80012658 7C060214 */  add     r0, r6, r0
/* 00D0BC 8001265C B01F000C */  sth     r0, 0xc(r31)
/* 00D0C0 80012660 80B90008 */  lwz     r5, 8(r25)
/* 00D0C4 80012664 80A50000 */  lwz     r5, 0(r5)
/* 00D0C8 80012668 A0050000 */  lhz     r0, 0(r5)
/* 00D0CC 8001266C 7C070214 */  add     r0, r7, r0
/* 00D0D0 80012670 B01F000E */  sth     r0, 0xe(r31)
/* 00D0D4 80012674 B35F0012 */  sth     r26, 0x12(r31)
/* 00D0D8 80012678 80B90008 */  lwz     r5, 8(r25)
/* 00D0DC 8001267C 80A50000 */  lwz     r5, 0(r5)
/* 00D0E0 80012680 A0050000 */  lhz     r0, 0(r5)
/* 00D0E4 80012684 7C070214 */  add     r0, r7, r0
/* 00D0E8 80012688 B01F0014 */  sth     r0, 0x14(r31)
/* 00D0EC 8001268C 4808B121 */  bl      DCStoreRange
/* 00D0F0 80012690 C02280B8 */  lfs     f1, D_80135DB8@sda21(r2)
/* 00D0F4 80012694 387C13F0 */  addi    r3, r28, 0x13f0
/* 00D0F8 80012698 C04280BC */  lfs     f2, D_80135DBC@sda21(r2)
/* 00D0FC 8001269C FC600890 */  fmr     f3, f1
/* 00D100 800126A0 C08280C0 */  lfs     f4, D_80135DC0@sda21(r2)
/* 00D104 800126A4 C0A280C4 */  lfs     f5, D_80135DC4@sda21(r2)
/* 00D108 800126A8 C0C280C8 */  lfs     f6, D_80135DC8@sda21(r2)
/* 00D10C 800126AC 48095A3D */  bl      C_MTXOrtho
/* 00D110 800126B0 387C13F0 */  addi    r3, r28, 0x13f0
/* 00D114 800126B4 38800001 */  li      r4, 1
/* 00D118 800126B8 4809C081 */  bl      GXSetProjection
/* 00D11C 800126BC 38600001 */  li      r3, 1
/* 00D120 800126C0 48099F1D */  bl      GXSetNumChans
/* 00D124 800126C4 C02280CC */  lfs     f1, D_80135DCC@sda21(r2)
/* 00D128 800126C8 38610048 */  addi    r3, r1, 0x48
/* 00D12C 800126CC C04280D0 */  lfs     f2, D_80135DD0@sda21(r2)
/* 00D130 800126D0 38810018 */  addi    r4, r1, 0x18
/* 00D134 800126D4 C06280B8 */  lfs     f3, D_80135DB8@sda21(r2)
/* 00D138 800126D8 48095821 */  bl      PSMTXTransApply
/* 00D13C 800126DC C02280AC */  lfs     f1, D_80135DAC@sda21(r2)
/* 00D140 800126E0 38610018 */  addi    r3, r1, 0x18
/* 00D144 800126E4 C06280D4 */  lfs     f3, D_80135DD4@sda21(r2)
/* 00D148 800126E8 7C641B78 */  mr      r4, r3
/* 00D14C 800126EC FC400890 */  fmr     f2, f1
/* 00D150 800126F0 4809587D */  bl      PSMTXScaleApply
/* 00D154 800126F4 38610018 */  addi    r3, r1, 0x18
/* 00D158 800126F8 38800000 */  li      r4, 0
/* 00D15C 800126FC 4809C16D */  bl      GXLoadPosMtxImm
/* 00D160 80012700 38610078 */  addi    r3, r1, 0x78
/* 00D164 80012704 3880003C */  li      r4, 0x3c
/* 00D168 80012708 38A00000 */  li      r5, 0
/* 00D16C 8001270C 4809C231 */  bl      GXLoadTexMtxImm
/* 00D170 80012710 38600001 */  li      r3, 1
/* 00D174 80012714 48099EC9 */  bl      GXSetNumChans
/* 00D178 80012718 48097AD1 */  bl      GXClearVtxDesc
/* 00D17C 8001271C 38600009 */  li      r3, 9
/* 00D180 80012720 38800002 */  li      r4, 2
/* 00D184 80012724 48097679 */  bl      GXSetVtxDesc
/* 00D188 80012728 3860000B */  li      r3, 0xb
/* 00D18C 8001272C 38800002 */  li      r4, 2
/* 00D190 80012730 4809766D */  bl      GXSetVtxDesc
/* 00D194 80012734 3860000D */  li      r3, 0xd
/* 00D198 80012738 38800002 */  li      r4, 2
/* 00D19C 8001273C 48097661 */  bl      GXSetVtxDesc
/* 00D1A0 80012740 389F0000 */  addi    r4, r31, 0
/* 00D1A4 80012744 38600009 */  li      r3, 9
/* 00D1A8 80012748 38A00006 */  li      r5, 6
/* 00D1AC 8001274C 4809804D */  bl      GXSetArray
/* 00D1B0 80012750 3C60800F */  lis     r3, Colors_u32@ha
/* 00D1B4 80012754 38839A00 */  addi    r4, r3, Colors_u32@l
/* 00D1B8 80012758 3860000B */  li      r3, 0xb
/* 00D1BC 8001275C 38A00004 */  li      r5, 4
/* 00D1C0 80012760 48098039 */  bl      GXSetArray
/* 00D1C4 80012764 3C60800F */  lis     r3, TexCoords_u8@ha
/* 00D1C8 80012768 38839A20 */  addi    r4, r3, TexCoords_u8@l
/* 00D1CC 8001276C 3860000D */  li      r3, 0xd
/* 00D1D0 80012770 38A00002 */  li      r5, 2
/* 00D1D4 80012774 48098025 */  bl      GXSetArray
/* 00D1D8 80012778 38600000 */  li      r3, 0
/* 00D1DC 8001277C 38800009 */  li      r4, 9
/* 00D1E0 80012780 38A00001 */  li      r5, 1
/* 00D1E4 80012784 38C00003 */  li      r6, 3
/* 00D1E8 80012788 38E00000 */  li      r7, 0
/* 00D1EC 8001278C 48097A95 */  bl      GXSetVtxAttrFmt
/* 00D1F0 80012790 38600000 */  li      r3, 0
/* 00D1F4 80012794 3880000B */  li      r4, 0xb
/* 00D1F8 80012798 38A00001 */  li      r5, 1
/* 00D1FC 8001279C 38C00001 */  li      r6, 1
/* 00D200 800127A0 38E00000 */  li      r7, 0
/* 00D204 800127A4 48097A7D */  bl      GXSetVtxAttrFmt
/* 00D208 800127A8 38600000 */  li      r3, 0
/* 00D20C 800127AC 3880000D */  li      r4, 0xd
/* 00D210 800127B0 38A00001 */  li      r5, 1
/* 00D214 800127B4 38C00000 */  li      r6, 0
/* 00D218 800127B8 38E00000 */  li      r7, 0
/* 00D21C 800127BC 48097A65 */  bl      GXSetVtxAttrFmt
/* 00D220 800127C0 38790000 */  addi    r3, r25, 0
/* 00D224 800127C4 388100B0 */  addi    r4, r1, 0xb0
/* 00D228 800127C8 38A00000 */  li      r5, 0
/* 00D22C 800127CC 480B67A1 */  bl      TEXGetGXTexObjFromPalette
/* 00D230 800127D0 386100B0 */  addi    r3, r1, 0xb0
/* 00D234 800127D4 38800000 */  li      r4, 0
/* 00D238 800127D8 4809A561 */  bl      GXLoadTexObj
/* 00D23C 800127DC 38600000 */  li      r3, 0
/* 00D240 800127E0 38800001 */  li      r4, 1
/* 00D244 800127E4 4809AFF9 */  bl      GXSetTevOp
/* 00D248 800127E8 38600080 */  li      r3, 0x80
/* 00D24C 800127EC 38800000 */  li      r4, 0
/* 00D250 800127F0 38A00004 */  li      r5, 4
/* 00D254 800127F4 48098C6D */  bl      GXBegin
/* 00D258 800127F8 9BBE8000 */  stb     r29, -0x8000(r30)
/* 00D25C 800127FC 38800001 */  li      r4, 1
/* 00D260 80012800 38600002 */  li      r3, 2
/* 00D264 80012804 9BBE8000 */  stb     r29, -0x8000(r30)
/* 00D268 80012808 38000003 */  li      r0, 3
/* 00D26C 8001280C 9BBE8000 */  stb     r29, -0x8000(r30)
/* 00D270 80012810 989E8000 */  stb     r4, -0x8000(r30)
/* 00D274 80012814 989E8000 */  stb     r4, -0x8000(r30)
/* 00D278 80012818 989E8000 */  stb     r4, -0x8000(r30)
/* 00D27C 8001281C 987E8000 */  stb     r3, -0x8000(r30)
/* 00D280 80012820 987E8000 */  stb     r3, -0x8000(r30)
/* 00D284 80012824 987E8000 */  stb     r3, -0x8000(r30)
/* 00D288 80012828 981E8000 */  stb     r0, -0x8000(r30)
/* 00D28C 8001282C 981E8000 */  stb     r0, -0x8000(r30)
/* 00D290 80012830 981E8000 */  stb     r0, -0x8000(r30)
/* 00D294 80012834 480A3A51 */  bl      DEMODoneRender
/* 00D298 80012838 BB2100D4 */  lmw     r25, 0xd4(r1)
/* 00D29C 8001283C 38600001 */  li      r3, 1
/* 00D2A0 80012840 800100F4 */  lwz     r0, 0xf4(r1)
/* 00D2A4 80012844 382100F0 */  addi    r1, r1, 0xf0
/* 00D2A8 80012848 7C0803A6 */  mtlr    r0
/* 00D2AC 8001284C 4E800020 */  blr     
