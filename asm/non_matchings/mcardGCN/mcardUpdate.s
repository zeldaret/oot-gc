glabel mcardUpdate
/* 00DEA0 80013440 7C0802A6 */  mflr    r0
/* 00DEA4 80013444 3C608010 */  lis     r3, gMCardCardWorkArea@ha
/* 00DEA8 80013448 90010004 */  stw     r0, 4(r1)
/* 00DEAC 8001344C 9421FFC8 */  stwu    r1, -0x38(r1)
/* 00DEB0 80013450 BEC10010 */  stmw    r22, 0x10(r1)
/* 00DEB4 80013454 3B800000 */  li      r28, 0
/* 00DEB8 80013458 3BA3D960 */  addi    r29, r3, gMCardCardWorkArea@l
/* 00DEBC 8001345C 3FDD0001 */  addis   r30, r29, 1
/* 00DEC0 80013460 387E0000 */  addi    r3, r30, 0
/* 00DEC4 80013464 3BE00001 */  li      r31, 1
/* 00DEC8 80013468 3B7EA4C0 */  addi    r27, r30, -23360
/* 00DECC 8001346C 3863A050 */  addi    r3, r3, -24496
/* 00DED0 80013470 93810008 */  stw     r28, 8(r1)
/* 00DED4 80013474 93FEA4C0 */  stw     r31, -0x5b40(r30)
/* 00DED8 80013478 48001185 */  bl      mcardOpenDuringGame
/* 00DEDC 8001347C 801B0000 */  lwz     r0, 0(r27)
/* 00DEE0 80013480 2C000001 */  cmpwi   r0, 1
/* 00DEE4 80013484 40820258 */  bne     lbl_800136DC
/* 00DEE8 80013488 3C600020 */  lis     r3, 0x20
/* 00DEEC 8001348C 3B5EA084 */  addi    r26, r30, -24444
/* 00DEF0 80013490 38830401 */  addi    r4, r3, 0x401
/* 00DEF4 80013494 38A00000 */  li      r5, 0
/* 00DEF8 80013498 48000014 */  b       lbl_800134AC
lbl_8001349C:
/* 00DEFC 8001349C 807EA090 */  lwz     r3, -0x5f70(r30)
/* 00DF00 800134A0 38A50001 */  addi    r5, r5, 1
/* 00DF04 800134A4 7FE3E12E */  stwx    r31, r3, r28
/* 00DF08 800134A8 3B9C0004 */  addi    r28, r28, 4
lbl_800134AC:
/* 00DF0C 800134AC 807A0000 */  lwz     r3, 0(r26)
/* 00DF10 800134B0 38031FFB */  addi    r0, r3, 0x1ffb
/* 00DF14 800134B4 7C640016 */  mulhwu  r3, r4, r0
/* 00DF18 800134B8 7C030050 */  subf    r0, r3, r0
/* 00DF1C 800134BC 5400F87E */  srwi    r0, r0, 1
/* 00DF20 800134C0 7C001A14 */  add     r0, r0, r3
/* 00DF24 800134C4 5400A33E */  srwi    r0, r0, 0xc
/* 00DF28 800134C8 7C050040 */  cmplw   r5, r0
/* 00DF2C 800134CC 4180FFD0 */  blt     lbl_8001349C
/* 00DF30 800134D0 3FFD0001 */  addis   r31, r29, 1
/* 00DF34 800134D4 3C600020 */  lis     r3, 0x20
/* 00DF38 800134D8 3B9FA4D4 */  addi    r28, r31, -23340
/* 00DF3C 800134DC 3BC30401 */  addi    r30, r3, 0x401
/* 00DF40 800134E0 3B000064 */  li      r24, 0x64
/* 00DF44 800134E4 3AC00000 */  li      r22, 0
lbl_800134E8:
/* 00DF48 800134E8 38600000 */  li      r3, 0
/* 00DF4C 800134EC 38800000 */  li      r4, 0
/* 00DF50 800134F0 38A00000 */  li      r5, 0
/* 00DF54 800134F4 38C00000 */  li      r6, 0
/* 00DF58 800134F8 4BFF56E5 */  bl      simulatorTestReset
/* 00DF5C 800134FC 2C030000 */  cmpwi   r3, 0
/* 00DF60 80013500 4082000C */  bne     lbl_8001350C
/* 00DF64 80013504 38600000 */  li      r3, 0
/* 00DF68 80013508 480001D8 */  b       lbl_800136E0
lbl_8001350C:
/* 00DF6C 8001350C 3C7D0001 */  addis   r3, r29, 1
/* 00DF70 80013510 3863A050 */  addi    r3, r3, -24496
/* 00DF74 80013514 480001E1 */  bl      mcardStore
/* 00DF78 80013518 801C0000 */  lwz     r0, 0(r28)
/* 00DF7C 8001351C 2C000000 */  cmpwi   r0, 0
/* 00DF80 80013520 41820018 */  beq     lbl_80013538
/* 00DF84 80013524 38000002 */  li      r0, 2
/* 00DF88 80013528 901FA4DC */  stw     r0, -0x5b24(r31)
/* 00DF8C 8001352C 3860002A */  li      r3, 0x2a
/* 00DF90 80013530 4BFF9CC1 */  bl      simulatorPrepareMessage
/* 00DF94 80013534 4BFF5611 */  bl      simulatorDrawMCardText
lbl_80013538:
/* 00DF98 80013538 807A0000 */  lwz     r3, 0(r26)
/* 00DF9C 8001353C 3B200000 */  li      r25, 0
/* 00DFA0 80013540 809FA090 */  lwz     r4, -0x5f70(r31)
/* 00DFA4 80013544 38A00000 */  li      r5, 0
/* 00DFA8 80013548 38031FFB */  addi    r0, r3, 0x1ffb
/* 00DFAC 8001354C 7C7E0016 */  mulhwu  r3, r30, r0
/* 00DFB0 80013550 7C030050 */  subf    r0, r3, r0
/* 00DFB4 80013554 5400F87E */  srwi    r0, r0, 1
/* 00DFB8 80013558 7C001A14 */  add     r0, r0, r3
/* 00DFBC 8001355C 5403A33E */  srwi    r3, r0, 0xc
/* 00DFC0 80013560 28030000 */  cmplwi  r3, 0
/* 00DFC4 80013564 7C6903A6 */  mtctr   r3
/* 00DFC8 80013568 40810028 */  ble     lbl_80013590
lbl_8001356C:
/* 00DFCC 8001356C 80040000 */  lwz     r0, 0(r4)
/* 00DFD0 80013570 2C000001 */  cmpwi   r0, 1
/* 00DFD4 80013574 40820010 */  bne     lbl_80013584
/* 00DFD8 80013578 3AE50000 */  addi    r23, r5, 0
/* 00DFDC 8001357C 3B200001 */  li      r25, 1
/* 00DFE0 80013580 48000010 */  b       lbl_80013590
lbl_80013584:
/* 00DFE4 80013584 38840004 */  addi    r4, r4, 4
/* 00DFE8 80013588 38A50001 */  addi    r5, r5, 1
/* 00DFEC 8001358C 4200FFE0 */  bdnz    lbl_8001356C
lbl_80013590:
/* 00DFF0 80013590 2C190001 */  cmpwi   r25, 1
/* 00DFF4 80013594 41820030 */  beq     lbl_800135C4
/* 00DFF8 80013598 801FA094 */  lwz     r0, -0x5f6c(r31)
/* 00DFFC 8001359C 2C000001 */  cmpwi   r0, 1
/* 00E000 800135A0 40820010 */  bne     lbl_800135B0
/* 00E004 800135A4 3AE30000 */  addi    r23, r3, 0
/* 00E008 800135A8 3B200001 */  li      r25, 1
/* 00E00C 800135AC 48000018 */  b       lbl_800135C4
lbl_800135B0:
/* 00E010 800135B0 801FA098 */  lwz     r0, -0x5f68(r31)
/* 00E014 800135B4 2C000001 */  cmpwi   r0, 1
/* 00E018 800135B8 4082000C */  bne     lbl_800135C4
/* 00E01C 800135BC 3B200001 */  li      r25, 1
/* 00E020 800135C0 3AE30001 */  addi    r23, r3, 1
lbl_800135C4:
/* 00E024 800135C4 801C0000 */  lwz     r0, 0(r28)
/* 00E028 800135C8 2C000000 */  cmpwi   r0, 0
/* 00E02C 800135CC 4082001C */  bne     lbl_800135E8
/* 00E030 800135D0 7C17C000 */  cmpw    r23, r24
/* 00E034 800135D4 4082000C */  bne     lbl_800135E0
/* 00E038 800135D8 3AD60001 */  addi    r22, r22, 1
/* 00E03C 800135DC 48000008 */  b       lbl_800135E4
lbl_800135E0:
/* 00E040 800135E0 3AC00000 */  li      r22, 0
lbl_800135E4:
/* 00E044 800135E4 7EF8BB78 */  mr      r24, r23
lbl_800135E8:
/* 00E048 800135E8 2C160003 */  cmpwi   r22, 3
/* 00E04C 800135EC 40820018 */  bne     lbl_80013604
/* 00E050 800135F0 38000001 */  li      r0, 1
/* 00E054 800135F4 901FA800 */  stw     r0, -0x5800(r31)
/* 00E058 800135F8 38000000 */  li      r0, 0
/* 00E05C 800135FC 3AC00000 */  li      r22, 0
/* 00E060 80013600 901B0000 */  stw     r0, 0(r27)
lbl_80013604:
/* 00E064 80013604 801B0000 */  lwz     r0, 0(r27)
/* 00E068 80013608 2C000000 */  cmpwi   r0, 0
/* 00E06C 8001360C 40820018 */  bne     lbl_80013624
/* 00E070 80013610 38000001 */  li      r0, 1
/* 00E074 80013614 3C7D0001 */  addis   r3, r29, 1
/* 00E078 80013618 901B0000 */  stw     r0, 0(r27)
/* 00E07C 8001361C 3863A050 */  addi    r3, r3, -24496
/* 00E080 80013620 48000FDD */  bl      mcardOpenDuringGame
lbl_80013624:
/* 00E084 80013624 2C190001 */  cmpwi   r25, 1
/* 00E088 80013628 41820010 */  beq     lbl_80013638
/* 00E08C 8001362C 801C0000 */  lwz     r0, 0(r28)
/* 00E090 80013630 2C000000 */  cmpwi   r0, 0
/* 00E094 80013634 41820010 */  beq     lbl_80013644
lbl_80013638:
/* 00E098 80013638 801B0000 */  lwz     r0, 0(r27)
/* 00E09C 8001363C 2C000001 */  cmpwi   r0, 1
/* 00E0A0 80013640 4182FEA8 */  beq     lbl_800134E8
lbl_80013644:
/* 00E0A4 80013644 38600000 */  li      r3, 0
/* 00E0A8 80013648 38800000 */  li      r4, 0
/* 00E0AC 8001364C 38A00001 */  li      r5, 1
/* 00E0B0 80013650 38C00000 */  li      r6, 0
/* 00E0B4 80013654 4BFF5589 */  bl      simulatorTestReset
/* 00E0B8 80013658 2C030000 */  cmpwi   r3, 0
/* 00E0BC 8001365C 4082000C */  bne     lbl_80013668
/* 00E0C0 80013660 38600000 */  li      r3, 0
/* 00E0C4 80013664 4800007C */  b       lbl_800136E0
lbl_80013668:
/* 00E0C8 80013668 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 00E0CC 8001366C 80030020 */  lwz     r0, 0x20(r3)
/* 00E0D0 80013670 2C000004 */  cmpwi   r0, 4
/* 00E0D4 80013674 40820058 */  bne     lbl_800136CC
/* 00E0D8 80013678 801B0000 */  lwz     r0, 0(r27)
/* 00E0DC 8001367C 2C000001 */  cmpwi   r0, 1
/* 00E0E0 80013680 4082004C */  bne     lbl_800136CC
/* 00E0E4 80013684 3EDD0001 */  addis   r22, r29, 1
lbl_80013688:
/* 00E0E8 80013688 3C7D0001 */  addis   r3, r29, 1
/* 00E0EC 8001368C 38A10008 */  addi    r5, r1, 8
/* 00E0F0 80013690 3880001F */  li      r4, 0x1f
/* 00E0F4 80013694 3863A050 */  addi    r3, r3, -24496
/* 00E0F8 80013698 480037D9 */  bl      mcardMenu
/* 00E0FC 8001369C 38600000 */  li      r3, 0
/* 00E100 800136A0 38800000 */  li      r4, 0
/* 00E104 800136A4 38A00001 */  li      r5, 1
/* 00E108 800136A8 38C00000 */  li      r6, 0
/* 00E10C 800136AC 4BFF5531 */  bl      simulatorTestReset
/* 00E110 800136B0 2C030000 */  cmpwi   r3, 0
/* 00E114 800136B4 4082000C */  bne     lbl_800136C0
/* 00E118 800136B8 38600000 */  li      r3, 0
/* 00E11C 800136BC 48000024 */  b       lbl_800136E0
lbl_800136C0:
/* 00E120 800136C0 8016A7FC */  lwz     r0, -0x5804(r22)
/* 00E124 800136C4 2C000001 */  cmpwi   r0, 1
/* 00E128 800136C8 4182FFC0 */  beq     lbl_80013688
lbl_800136CC:
/* 00E12C 800136CC 38000000 */  li      r0, 0
/* 00E130 800136D0 900D8998 */  stw     r0, bWrite2Card@sda21(r13)
/* 00E134 800136D4 3C7D0001 */  addis   r3, r29, 1
/* 00E138 800136D8 9003A4DC */  stw     r0, -0x5b24(r3)
lbl_800136DC:
/* 00E13C 800136DC 38600001 */  li      r3, 1
lbl_800136E0:
/* 00E140 800136E0 BAC10010 */  lmw     r22, 0x10(r1)
/* 00E144 800136E4 8001003C */  lwz     r0, 0x3c(r1)
/* 00E148 800136E8 38210038 */  addi    r1, r1, 0x38
/* 00E14C 800136EC 7C0803A6 */  mtlr    r0
/* 00E150 800136F0 4E800020 */  blr     
