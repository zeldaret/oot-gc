glabel frameLoadTile
/* 01ADA0 80020340 7C0802A6 */  mflr    r0
/* 01ADA4 80020344 90010004 */  stw     r0, 4(r1)
/* 01ADA8 80020348 9421FFB0 */  stwu    r1, -0x50(r1)
/* 01ADAC 8002034C BEA10024 */  stmw    r21, 0x24(r1)
/* 01ADB0 80020350 7C7D1B78 */  mr      r29, r3
/* 01ADB4 80020354 7C9E2378 */  mr      r30, r4
/* 01ADB8 80020358 7CBF2B78 */  mr      r31, r5
/* 01ADBC 8002035C 57E0073E */  clrlwi  r0, r31, 0x1c
/* 01ADC0 80020360 1C60002C */  mulli   r3, r0, 0x2c
/* 01ADC4 80020364 3C630004 */  addis   r3, r3, 4
/* 01ADC8 80020368 3863C358 */  addi    r3, r3, -15528
/* 01ADCC 8002036C 7C7D1A14 */  add     r3, r29, r3
/* 01ADD0 80020370 A8030020 */  lha     r0, 0x20(r3)
/* 01ADD4 80020374 7C7A1B78 */  mr      r26, r3
/* 01ADD8 80020378 2C000000 */  cmpwi   r0, 0
/* 01ADDC 8002037C 408200F8 */  bne     lbl_80020474
/* 01ADE0 80020380 A81A0022 */  lha     r0, 0x22(r26)
/* 01ADE4 80020384 2C000000 */  cmpwi   r0, 0
/* 01ADE8 80020388 408200EC */  bne     lbl_80020474
/* 01ADEC 8002038C A81A0024 */  lha     r0, 0x24(r26)
/* 01ADF0 80020390 2C000000 */  cmpwi   r0, 0
/* 01ADF4 80020394 408200E0 */  bne     lbl_80020474
/* 01ADF8 80020398 A81A0026 */  lha     r0, 0x26(r26)
/* 01ADFC 8002039C 2C000000 */  cmpwi   r0, 0
/* 01AE00 800203A0 408200D4 */  bne     lbl_80020474
/* 01AE04 800203A4 3CBD0004 */  addis   r5, r29, 4
/* 01AE08 800203A8 8005C340 */  lwz     r0, -0x3cc0(r5)
/* 01AE0C 800203AC 3B600001 */  li      r27, 1
/* 01AE10 800203B0 1C00002C */  mulli   r0, r0, 0x2c
/* 01AE14 800203B4 7C650214 */  add     r3, r5, r0
/* 01AE18 800203B8 A803C378 */  lha     r0, -0x3c88(r3)
/* 01AE1C 800203BC B01A0020 */  sth     r0, 0x20(r26)
/* 01AE20 800203C0 8005C340 */  lwz     r0, -0x3cc0(r5)
/* 01AE24 800203C4 1C00002C */  mulli   r0, r0, 0x2c
/* 01AE28 800203C8 7C650214 */  add     r3, r5, r0
/* 01AE2C 800203CC A803C37A */  lha     r0, -0x3c86(r3)
/* 01AE30 800203D0 B01A0022 */  sth     r0, 0x22(r26)
/* 01AE34 800203D4 8005C340 */  lwz     r0, -0x3cc0(r5)
/* 01AE38 800203D8 1C00002C */  mulli   r0, r0, 0x2c
/* 01AE3C 800203DC 7C650214 */  add     r3, r5, r0
/* 01AE40 800203E0 A803C37C */  lha     r0, -0x3c84(r3)
/* 01AE44 800203E4 B01A0024 */  sth     r0, 0x24(r26)
/* 01AE48 800203E8 8005C340 */  lwz     r0, -0x3cc0(r5)
/* 01AE4C 800203EC 1C00002C */  mulli   r0, r0, 0x2c
/* 01AE50 800203F0 7C650214 */  add     r3, r5, r0
/* 01AE54 800203F4 A803C37E */  lha     r0, -0x3c82(r3)
/* 01AE58 800203F8 B01A0026 */  sth     r0, 0x26(r26)
/* 01AE5C 800203FC 8005C340 */  lwz     r0, -0x3cc0(r5)
/* 01AE60 80020400 809A0000 */  lwz     r4, 0(r26)
/* 01AE64 80020404 1C00002C */  mulli   r0, r0, 0x2c
/* 01AE68 80020408 7C650214 */  add     r3, r5, r0
/* 01AE6C 8002040C 8003C358 */  lwz     r0, -0x3ca8(r3)
/* 01AE70 80020410 7C640050 */  subf    r3, r4, r0
/* 01AE74 80020414 2C030000 */  cmpwi   r3, 0
/* 01AE78 80020418 4080002C */  bge     lbl_80020444
/* 01AE7C 8002041C A81A0020 */  lha     r0, 0x20(r26)
/* 01AE80 80020420 7C6300D0 */  neg     r3, r3
/* 01AE84 80020424 7C001E30 */  sraw    r0, r0, r3
/* 01AE88 80020428 7C000734 */  extsh   r0, r0
/* 01AE8C 8002042C B01A0020 */  sth     r0, 0x20(r26)
/* 01AE90 80020430 A81A0024 */  lha     r0, 0x24(r26)
/* 01AE94 80020434 7C001E30 */  sraw    r0, r0, r3
/* 01AE98 80020438 7C000734 */  extsh   r0, r0
/* 01AE9C 8002043C B01A0024 */  sth     r0, 0x24(r26)
/* 01AEA0 80020440 48000024 */  b       lbl_80020464
lbl_80020444:
/* 01AEA4 80020444 A81A0020 */  lha     r0, 0x20(r26)
/* 01AEA8 80020448 7C001830 */  slw     r0, r0, r3
/* 01AEAC 8002044C 7C000734 */  extsh   r0, r0
/* 01AEB0 80020450 B01A0020 */  sth     r0, 0x20(r26)
/* 01AEB4 80020454 A81A0024 */  lha     r0, 0x24(r26)
/* 01AEB8 80020458 7C001830 */  slw     r0, r0, r3
/* 01AEBC 8002045C 7C000734 */  extsh   r0, r0
/* 01AEC0 80020460 B01A0024 */  sth     r0, 0x24(r26)
lbl_80020464:
/* 01AEC4 80020464 38000002 */  li      r0, 2
/* 01AEC8 80020468 B01A0018 */  sth     r0, 0x18(r26)
/* 01AECC 8002046C B01A001A */  sth     r0, 0x1a(r26)
/* 01AED0 80020470 48000008 */  b       lbl_80020478
lbl_80020474:
/* 01AED4 80020474 3B600000 */  li      r27, 0
lbl_80020478:
/* 01AED8 80020478 A81A0016 */  lha     r0, 0x16(r26)
/* 01AEDC 8002047C A87A0018 */  lha     r3, 0x18(r26)
/* 01AEE0 80020480 AB1A0014 */  lha     r24, 0x14(r26)
/* 01AEE4 80020484 5417073E */  clrlwi  r23, r0, 0x1c
/* 01AEE8 80020488 A81A001A */  lha     r0, 0x1a(r26)
/* 01AEEC 8002048C 5479077E */  clrlwi  r25, r3, 0x1d
/* 01AEF0 80020490 A87A001C */  lha     r3, 0x1c(r26)
/* 01AEF4 80020494 541C077E */  clrlwi  r28, r0, 0x1d
/* 01AEF8 80020498 A89A001E */  lha     r4, 0x1e(r26)
/* 01AEFC 8002049C 5460073E */  clrlwi  r0, r3, 0x1c
/* 01AF00 800204A0 80BA0000 */  lwz     r5, 0(r26)
/* 01AF04 800204A4 5483073E */  clrlwi  r3, r4, 0x1c
/* 01AF08 800204A8 80DA0010 */  lwz     r6, 0x10(r26)
/* 01AF0C 800204AC 817D21F8 */  lwz     r11, 0x21f8(r29)
/* 01AF10 800204B0 54A4077E */  clrlwi  r4, r5, 0x1d
/* 01AF14 800204B4 A91A0024 */  lha     r8, 0x24(r26)
/* 01AF18 800204B8 54C5077E */  clrlwi  r5, r6, 0x1d
/* 01AF1C 800204BC A8FA0026 */  lha     r7, 0x26(r26)
/* 01AF20 800204C0 80DA0008 */  lwz     r6, 8(r26)
/* 01AF24 800204C4 3D8B0001 */  addis   r12, r11, 1
/* 01AF28 800204C8 82BA000C */  lwz     r21, 0xc(r26)
/* 01AF2C 800204CC 5509043E */  clrlwi  r9, r8, 0x10
/* 01AF30 800204D0 A95A0020 */  lha     r10, 0x20(r26)
/* 01AF34 800204D4 A91A0022 */  lha     r8, 0x22(r26)
/* 01AF38 800204D8 54E7043E */  clrlwi  r7, r7, 0x10
/* 01AF3C 800204DC 82DA0004 */  lwz     r22, 4(r26)
/* 01AF40 800204E0 54C6073E */  clrlwi  r6, r6, 0x1c
/* 01AF44 800204E4 56B5043E */  clrlwi  r21, r21, 0x10
/* 01AF48 800204E8 5718073E */  clrlwi  r24, r24, 0x1c
/* 01AF4C 800204EC 56F72036 */  slwi    r23, r23, 4
/* 01AF50 800204F0 5739402E */  slwi    r25, r25, 8
/* 01AF54 800204F4 7F17BB78 */  or      r23, r24, r23
/* 01AF58 800204F8 57985828 */  slwi    r24, r28, 0xb
/* 01AF5C 800204FC 7F37BB78 */  or      r23, r25, r23
/* 01AF60 80020500 54197022 */  slwi    r25, r0, 0xe
/* 01AF64 80020504 7F00BB78 */  or      r0, r24, r23
/* 01AF68 80020508 5463901A */  slwi    r3, r3, 0x12
/* 01AF6C 8002050C 7F200378 */  or      r0, r25, r0
/* 01AF70 80020510 5484B012 */  slwi    r4, r4, 0x16
/* 01AF74 80020514 7C600378 */  or      r0, r3, r0
/* 01AF78 80020518 280CFFFF */  cmplwi  r12, 0xffff
/* 01AF7C 8002051C 54A3C80C */  slwi    r3, r5, 0x19
/* 01AF80 80020520 7C800378 */  or      r0, r4, r0
/* 01AF84 80020524 554A043E */  clrlwi  r10, r10, 0x10
/* 01AF88 80020528 5529801E */  slwi    r9, r9, 0x10
/* 01AF8C 8002052C 5508043E */  clrlwi  r8, r8, 0x10
/* 01AF90 80020530 54E7801E */  slwi    r7, r7, 0x10
/* 01AF94 80020534 54C5E006 */  slwi    r5, r6, 0x1c
/* 01AF98 80020538 7C640378 */  or      r4, r3, r0
/* 01AF9C 8002053C 56C3043E */  clrlwi  r3, r22, 0x10
/* 01AFA0 80020540 56A0801E */  slwi    r0, r21, 0x10
/* 01AFA4 80020544 7D584B78 */  or      r24, r10, r9
/* 01AFA8 80020548 7D173B78 */  or      r23, r8, r7
/* 01AFAC 8002054C 7CB62378 */  or      r22, r5, r4
/* 01AFB0 80020550 7C750378 */  or      r21, r3, r0
/* 01AFB4 80020554 4082000C */  bne     lbl_80020560
/* 01AFB8 80020558 38000000 */  li      r0, 0
/* 01AFBC 8002055C 48000008 */  b       lbl_80020564
lbl_80020560:
/* 01AFC0 80020560 5560AAFE */  srwi    r0, r11, 0xb
lbl_80020564:
/* 01AFC4 80020564 3C7D0004 */  addis   r3, r29, 4
/* 01AFC8 80020568 5400103A */  slwi    r0, r0, 2
/* 01AFCC 8002056C 7F830214 */  add     r28, r3, r0
/* 01AFD0 80020570 3B9C8340 */  addi    r28, r28, -31936
/* 01AFD4 80020574 801C0000 */  lwz     r0, 0(r28)
/* 01AFD8 80020578 90010018 */  stw     r0, 0x18(r1)
/* 01AFDC 8002057C 7C190378 */  mr      r25, r0
/* 01AFE0 80020580 48000004 */  b       lbl_80020584
lbl_80020584:
/* 01AFE4 80020584 48000004 */  b       lbl_80020588
lbl_80020588:
/* 01AFE8 80020588 48000060 */  b       lbl_800205E8
lbl_8002058C:
/* 01AFEC 8002058C 80040024 */  lwz     r0, 0x24(r4)
/* 01AFF0 80020590 7C00C040 */  cmplw   r0, r24
/* 01AFF4 80020594 40820048 */  bne     lbl_800205DC
/* 01AFF8 80020598 80040028 */  lwz     r0, 0x28(r4)
/* 01AFFC 8002059C 7C00B840 */  cmplw   r0, r23
/* 01B000 800205A0 4082003C */  bne     lbl_800205DC
/* 01B004 800205A4 8004002C */  lwz     r0, 0x2c(r4)
/* 01B008 800205A8 7C00B040 */  cmplw   r0, r22
/* 01B00C 800205AC 40820030 */  bne     lbl_800205DC
/* 01B010 800205B0 80040030 */  lwz     r0, 0x30(r4)
/* 01B014 800205B4 7C00A840 */  cmplw   r0, r21
/* 01B018 800205B8 40820024 */  bne     lbl_800205DC
/* 01B01C 800205BC 80640018 */  lwz     r3, 0x18(r4)
/* 01B020 800205C0 801A0028 */  lwz     r0, 0x28(r26)
/* 01B024 800205C4 7C030040 */  cmplw   r3, r0
/* 01B028 800205C8 40820014 */  bne     lbl_800205DC
/* 01B02C 800205CC 80640014 */  lwz     r3, 0x14(r4)
/* 01B030 800205D0 801D21F8 */  lwz     r0, 0x21f8(r29)
/* 01B034 800205D4 7C030040 */  cmplw   r3, r0
/* 01B038 800205D8 4182001C */  beq     lbl_800205F4
lbl_800205DC:
/* 01B03C 800205DC 80040020 */  lwz     r0, 0x20(r4)
/* 01B040 800205E0 7C992378 */  mr      r25, r4
/* 01B044 800205E4 90010018 */  stw     r0, 0x18(r1)
lbl_800205E8:
/* 01B048 800205E8 80810018 */  lwz     r4, 0x18(r1)
/* 01B04C 800205EC 28040000 */  cmplwi  r4, 0
/* 01B050 800205F0 4082FF9C */  bne     lbl_8002058C
lbl_800205F4:
/* 01B054 800205F4 28040000 */  cmplwi  r4, 0
/* 01B058 800205F8 4082009C */  bne     lbl_80020694
/* 01B05C 800205FC 7FA3EB78 */  mr      r3, r29
/* 01B060 80020600 38810018 */  addi    r4, r1, 0x18
/* 01B064 80020604 4800081D */  bl      frameMakeTexture
/* 01B068 80020608 2C030000 */  cmpwi   r3, 0
/* 01B06C 8002060C 4082000C */  bne     lbl_80020618
/* 01B070 80020610 38600000 */  li      r3, 0
/* 01B074 80020614 4800013C */  b       lbl_80020750
lbl_80020618:
/* 01B078 80020618 80810018 */  lwz     r4, 0x18(r1)
/* 01B07C 8002061C 7FA3EB78 */  mr      r3, r29
/* 01B080 80020620 7F45D378 */  mr      r5, r26
/* 01B084 80020624 38C00000 */  li      r6, 0
/* 01B088 80020628 4800A15D */  bl      frameMakePixels
/* 01B08C 8002062C 80610018 */  lwz     r3, 0x18(r1)
/* 01B090 80020630 93030024 */  stw     r24, 0x24(r3)
/* 01B094 80020634 80610018 */  lwz     r3, 0x18(r1)
/* 01B098 80020638 92E30028 */  stw     r23, 0x28(r3)
/* 01B09C 8002063C 80610018 */  lwz     r3, 0x18(r1)
/* 01B0A0 80020640 92C3002C */  stw     r22, 0x2c(r3)
/* 01B0A4 80020644 80610018 */  lwz     r3, 0x18(r1)
/* 01B0A8 80020648 92A30030 */  stw     r21, 0x30(r3)
/* 01B0AC 8002064C 809D21F8 */  lwz     r4, 0x21f8(r29)
/* 01B0B0 80020650 3C040001 */  addis   r0, r4, 1
/* 01B0B4 80020654 2800FFFF */  cmplwi  r0, 0xffff
/* 01B0B8 80020658 40820014 */  bne     lbl_8002066C
/* 01B0BC 8002065C 80610018 */  lwz     r3, 0x18(r1)
/* 01B0C0 80020660 38000000 */  li      r0, 0
/* 01B0C4 80020664 90030014 */  stw     r0, 0x14(r3)
/* 01B0C8 80020668 4800000C */  b       lbl_80020674
lbl_8002066C:
/* 01B0CC 8002066C 80610018 */  lwz     r3, 0x18(r1)
/* 01B0D0 80020670 90830014 */  stw     r4, 0x14(r3)
lbl_80020674:
/* 01B0D4 80020674 28190000 */  cmplwi  r25, 0
/* 01B0D8 80020678 40820010 */  bne     lbl_80020688
/* 01B0DC 8002067C 80010018 */  lwz     r0, 0x18(r1)
/* 01B0E0 80020680 901C0000 */  stw     r0, 0(r28)
/* 01B0E4 80020684 48000048 */  b       lbl_800206CC
lbl_80020688:
/* 01B0E8 80020688 80010018 */  lwz     r0, 0x18(r1)
/* 01B0EC 8002068C 90190020 */  stw     r0, 0x20(r25)
/* 01B0F0 80020690 4800003C */  b       lbl_800206CC
lbl_80020694:
/* 01B0F4 80020694 80040008 */  lwz     r0, 8(r4)
/* 01B0F8 80020698 2C00FFFF */  cmpwi   r0, -1
/* 01B0FC 8002069C 41820030 */  beq     lbl_800206CC
/* 01B100 800206A0 801A0008 */  lwz     r0, 8(r26)
/* 01B104 800206A4 80A4001C */  lwz     r5, 0x1c(r4)
/* 01B108 800206A8 5400103A */  slwi    r0, r0, 2
/* 01B10C 800206AC 7C7D0214 */  add     r3, r29, r0
/* 01B110 800206B0 80032200 */  lwz     r0, 0x2200(r3)
/* 01B114 800206B4 7C050040 */  cmplw   r5, r0
/* 01B118 800206B8 41820014 */  beq     lbl_800206CC
/* 01B11C 800206BC 7FA3EB78 */  mr      r3, r29
/* 01B120 800206C0 7F45D378 */  mr      r5, r26
/* 01B124 800206C4 38C00001 */  li      r6, 1
/* 01B128 800206C8 4800A0BD */  bl      frameMakePixels
lbl_800206CC:
/* 01B12C 800206CC 801D0088 */  lwz     r0, 0x88(r29)
/* 01B130 800206D0 7FA3EB78 */  mr      r3, r29
/* 01B134 800206D4 80810018 */  lwz     r4, 0x18(r1)
/* 01B138 800206D8 7FE5FB78 */  mr      r5, r31
/* 01B13C 800206DC 7F46D378 */  mr      r6, r26
/* 01B140 800206E0 9004000C */  stw     r0, 0xc(r4)
/* 01B144 800206E4 801A0008 */  lwz     r0, 8(r26)
/* 01B148 800206E8 80810018 */  lwz     r4, 0x18(r1)
/* 01B14C 800206EC 5400103A */  slwi    r0, r0, 2
/* 01B150 800206F0 7CFD0214 */  add     r7, r29, r0
/* 01B154 800206F4 80072200 */  lwz     r0, 0x2200(r7)
/* 01B158 800206F8 9004001C */  stw     r0, 0x1c(r4)
/* 01B15C 800206FC 801A0028 */  lwz     r0, 0x28(r26)
/* 01B160 80020700 80810018 */  lwz     r4, 0x18(r1)
/* 01B164 80020704 90040018 */  stw     r0, 0x18(r4)
/* 01B168 80020708 80810018 */  lwz     r4, 0x18(r1)
/* 01B16C 8002070C 48009D9D */  bl      frameLoadTexture
/* 01B170 80020710 2C030000 */  cmpwi   r3, 0
/* 01B174 80020714 4082000C */  bne     lbl_80020720
/* 01B178 80020718 38600000 */  li      r3, 0
/* 01B17C 8002071C 48000034 */  b       lbl_80020750
lbl_80020720:
/* 01B180 80020720 281E0000 */  cmplwi  r30, 0
/* 01B184 80020724 4182000C */  beq     lbl_80020730
/* 01B188 80020728 80010018 */  lwz     r0, 0x18(r1)
/* 01B18C 8002072C 901E0000 */  stw     r0, 0(r30)
lbl_80020730:
/* 01B190 80020730 2C1B0000 */  cmpwi   r27, 0
/* 01B194 80020734 41820018 */  beq     lbl_8002074C
/* 01B198 80020738 38000000 */  li      r0, 0
/* 01B19C 8002073C B01A0026 */  sth     r0, 0x26(r26)
/* 01B1A0 80020740 B01A0024 */  sth     r0, 0x24(r26)
/* 01B1A4 80020744 B01A0022 */  sth     r0, 0x22(r26)
/* 01B1A8 80020748 B01A0020 */  sth     r0, 0x20(r26)
lbl_8002074C:
/* 01B1AC 8002074C 38600001 */  li      r3, 1
lbl_80020750:
/* 01B1B0 80020750 BAA10024 */  lmw     r21, 0x24(r1)
/* 01B1B4 80020754 80010054 */  lwz     r0, 0x54(r1)
/* 01B1B8 80020758 38210050 */  addi    r1, r1, 0x50
/* 01B1BC 8002075C 7C0803A6 */  mtlr    r0
/* 01B1C0 80020760 4E800020 */  blr     
