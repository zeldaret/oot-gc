glabel MixAudio
/* 00B460 80010A00 7C0802A6 */  mflr    r0
/* 00B464 80010A04 28040000 */  cmplwi  r4, 0
/* 00B468 80010A08 90010004 */  stw     r0, 4(r1)
/* 00B46C 80010A0C 3CC08010 */  lis     r6, WorkBuffer@ha
/* 00B470 80010A10 9421FFC0 */  stwu    r1, -0x40(r1)
/* 00B474 80010A14 BF210024 */  stmw    r25, 0x24(r1)
/* 00B478 80010A18 3BC696E0 */  addi    r30, r6, WorkBuffer@l
/* 00B47C 80010A1C 418201C4 */  beq     lbl_80010BE0
/* 00B480 80010A20 801E0640 */  lwz     r0, 0x640(r30)
/* 00B484 80010A24 2C000000 */  cmpwi   r0, 0
/* 00B488 80010A28 418201AC */  beq     lbl_80010BD4
/* 00B48C 80010A2C 881E0645 */  lbz     r0, 0x645(r30)
/* 00B490 80010A30 28000002 */  cmplwi  r0, 2
/* 00B494 80010A34 408201A0 */  bne     lbl_80010BD4
/* 00B498 80010A38 881E0647 */  lbz     r0, 0x647(r30)
/* 00B49C 80010A3C 28000000 */  cmplwi  r0, 0
/* 00B4A0 80010A40 41820194 */  beq     lbl_80010BD4
/* 00B4A4 80010A44 3CC0800F */  lis     r6, VolumeTable@ha
/* 00B4A8 80010A48 3B450000 */  addi    r26, r5, 0
/* 00B4AC 80010A4C 3B630000 */  addi    r27, r3, 0
/* 00B4B0 80010A50 3B240000 */  addi    r25, r4, 0
/* 00B4B4 80010A54 3B9E0688 */  addi    r28, r30, 0x688
/* 00B4B8 80010A58 3BE6A1E8 */  addi    r31, r6, VolumeTable@l
/* 00B4BC 80010A5C 3BBE069C */  addi    r29, r30, 0x69c
lbl_80010A60:
/* 00B4C0 80010A60 801D0000 */  lwz     r0, 0(r29)
/* 00B4C4 80010A64 28000000 */  cmplwi  r0, 0
/* 00B4C8 80010A68 40820038 */  bne     lbl_80010AA0
/* 00B4CC 80010A6C 38600000 */  li      r3, 0
/* 00B4D0 80010A70 48000655 */  bl      PopDecodedAudioBuffer
/* 00B4D4 80010A74 28030000 */  cmplwi  r3, 0
/* 00B4D8 80010A78 907D0000 */  stw     r3, 0(r29)
/* 00B4DC 80010A7C 40820018 */  bne     lbl_80010A94
/* 00B4E0 80010A80 387B0000 */  addi    r3, r27, 0
/* 00B4E4 80010A84 38990000 */  addi    r4, r25, 0
/* 00B4E8 80010A88 5745103A */  slwi    r5, r26, 2
/* 00B4EC 80010A8C 4BFF4A39 */  bl      memcpy
/* 00B4F0 80010A90 480002F8 */  b       lbl_80010D88
lbl_80010A94:
/* 00B4F4 80010A94 807E0694 */  lwz     r3, 0x694(r30)
/* 00B4F8 80010A98 38030001 */  addi    r0, r3, 1
/* 00B4FC 80010A9C 901E0694 */  stw     r0, 0x694(r30)
lbl_80010AA0:
/* 00B500 80010AA0 807D0000 */  lwz     r3, 0(r29)
/* 00B504 80010AA4 80030008 */  lwz     r0, 8(r3)
/* 00B508 80010AA8 28000000 */  cmplwi  r0, 0
/* 00B50C 80010AAC 4182FFB4 */  beq     lbl_80010A60
/* 00B510 80010AB0 7C00D040 */  cmplw   r0, r26
/* 00B514 80010AB4 41800008 */  blt     lbl_80010ABC
/* 00B518 80010AB8 7F40D378 */  mr      r0, r26
lbl_80010ABC:
/* 00B51C 80010ABC 28000000 */  cmplwi  r0, 0
/* 00B520 80010AC0 7C0903A6 */  mtctr   r0
/* 00B524 80010AC4 80630004 */  lwz     r3, 4(r3)
/* 00B528 80010AC8 408100C8 */  ble     lbl_80010B90
lbl_80010ACC:
/* 00B52C 80010ACC 809C0000 */  lwz     r4, 0(r28)
/* 00B530 80010AD0 2C040000 */  cmpwi   r4, 0
/* 00B534 80010AD4 41820020 */  beq     lbl_80010AF4
/* 00B538 80010AD8 3884FFFF */  addi    r4, r4, -1
/* 00B53C 80010ADC 909C0000 */  stw     r4, 0(r28)
/* 00B540 80010AE0 C03E067C */  lfs     f1, 0x67c(r30)
/* 00B544 80010AE4 C01E0684 */  lfs     f0, 0x684(r30)
/* 00B548 80010AE8 EC01002A */  fadds   f0, f1, f0
/* 00B54C 80010AEC D01E067C */  stfs    f0, 0x67c(r30)
/* 00B550 80010AF0 4800000C */  b       lbl_80010AFC
lbl_80010AF4:
/* 00B554 80010AF4 C01E0680 */  lfs     f0, 0x680(r30)
/* 00B558 80010AF8 D01E067C */  stfs    f0, 0x67c(r30)
lbl_80010AFC:
/* 00B55C 80010AFC C01E067C */  lfs     f0, 0x67c(r30)
/* 00B560 80010B00 A8830000 */  lha     r4, 0(r3)
/* 00B564 80010B04 FC00001E */  fctiwz  f0, f0
/* 00B568 80010B08 A8B90000 */  lha     r5, 0(r25)
/* 00B56C 80010B0C D8010018 */  stfd    f0, 0x18(r1)
/* 00B570 80010B10 80C1001C */  lwz     r6, 0x1c(r1)
/* 00B574 80010B14 54C6083C */  slwi    r6, r6, 1
/* 00B578 80010B18 7CDF3214 */  add     r6, r31, r6
/* 00B57C 80010B1C A0C60000 */  lhz     r6, 0(r6)
/* 00B580 80010B20 7C8621D6 */  mullw   r4, r6, r4
/* 00B584 80010B24 7C847E70 */  srawi   r4, r4, 0xf
/* 00B588 80010B28 7C852214 */  add     r4, r5, r4
/* 00B58C 80010B2C 2C048000 */  cmpwi   r4, -32768
/* 00B590 80010B30 40800008 */  bge     lbl_80010B38
/* 00B594 80010B34 38808000 */  li      r4, -32768
lbl_80010B38:
/* 00B598 80010B38 2C047FFF */  cmpwi   r4, 0x7fff
/* 00B59C 80010B3C 40810008 */  ble     lbl_80010B44
/* 00B5A0 80010B40 38807FFF */  li      r4, 0x7fff
lbl_80010B44:
/* 00B5A4 80010B44 7C840734 */  extsh   r4, r4
/* 00B5A8 80010B48 B09B0000 */  sth     r4, 0(r27)
/* 00B5AC 80010B4C A8830002 */  lha     r4, 2(r3)
/* 00B5B0 80010B50 A8B90002 */  lha     r5, 2(r25)
/* 00B5B4 80010B54 7C8621D6 */  mullw   r4, r6, r4
/* 00B5B8 80010B58 7C847E70 */  srawi   r4, r4, 0xf
/* 00B5BC 80010B5C 7C852214 */  add     r4, r5, r4
/* 00B5C0 80010B60 2C048000 */  cmpwi   r4, -32768
/* 00B5C4 80010B64 40800008 */  bge     lbl_80010B6C
/* 00B5C8 80010B68 38808000 */  li      r4, -32768
lbl_80010B6C:
/* 00B5CC 80010B6C 2C047FFF */  cmpwi   r4, 0x7fff
/* 00B5D0 80010B70 40810008 */  ble     lbl_80010B78
/* 00B5D4 80010B74 38807FFF */  li      r4, 0x7fff
lbl_80010B78:
/* 00B5D8 80010B78 7C840734 */  extsh   r4, r4
/* 00B5DC 80010B7C B09B0002 */  sth     r4, 2(r27)
/* 00B5E0 80010B80 3B7B0004 */  addi    r27, r27, 4
/* 00B5E4 80010B84 3B390004 */  addi    r25, r25, 4
/* 00B5E8 80010B88 38630004 */  addi    r3, r3, 4
/* 00B5EC 80010B8C 4200FF40 */  bdnz    lbl_80010ACC
lbl_80010B90:
/* 00B5F0 80010B90 80BD0000 */  lwz     r5, 0(r29)
/* 00B5F4 80010B94 7F40D050 */  subf    r26, r0, r26
/* 00B5F8 80010B98 80850008 */  lwz     r4, 8(r5)
/* 00B5FC 80010B9C 7C002050 */  subf    r0, r0, r4
/* 00B600 80010BA0 90050008 */  stw     r0, 8(r5)
/* 00B604 80010BA4 809D0000 */  lwz     r4, 0(r29)
/* 00B608 80010BA8 90640004 */  stw     r3, 4(r4)
/* 00B60C 80010BAC 807D0000 */  lwz     r3, 0(r29)
/* 00B610 80010BB0 80030008 */  lwz     r0, 8(r3)
/* 00B614 80010BB4 28000000 */  cmplwi  r0, 0
/* 00B618 80010BB8 40820010 */  bne     lbl_80010BC8
/* 00B61C 80010BBC 480004D9 */  bl      PushFreeAudioBuffer
/* 00B620 80010BC0 38000000 */  li      r0, 0
/* 00B624 80010BC4 901D0000 */  stw     r0, 0(r29)
lbl_80010BC8:
/* 00B628 80010BC8 281A0000 */  cmplwi  r26, 0
/* 00B62C 80010BCC 418201BC */  beq     lbl_80010D88
/* 00B630 80010BD0 4BFFFE90 */  b       lbl_80010A60
lbl_80010BD4:
/* 00B634 80010BD4 54A5103A */  slwi    r5, r5, 2
/* 00B638 80010BD8 4BFF48ED */  bl      memcpy
/* 00B63C 80010BDC 480001AC */  b       lbl_80010D88
lbl_80010BE0:
/* 00B640 80010BE0 801E0640 */  lwz     r0, 0x640(r30)
/* 00B644 80010BE4 2C000000 */  cmpwi   r0, 0
/* 00B648 80010BE8 41820194 */  beq     lbl_80010D7C
/* 00B64C 80010BEC 881E0645 */  lbz     r0, 0x645(r30)
/* 00B650 80010BF0 28000002 */  cmplwi  r0, 2
/* 00B654 80010BF4 40820188 */  bne     lbl_80010D7C
/* 00B658 80010BF8 881E0647 */  lbz     r0, 0x647(r30)
/* 00B65C 80010BFC 28000000 */  cmplwi  r0, 0
/* 00B660 80010C00 4182017C */  beq     lbl_80010D7C
/* 00B664 80010C04 3C80800F */  lis     r4, VolumeTable@ha
/* 00B668 80010C08 3B650000 */  addi    r27, r5, 0
/* 00B66C 80010C0C 3B430000 */  addi    r26, r3, 0
/* 00B670 80010C10 3BBE0688 */  addi    r29, r30, 0x688
/* 00B674 80010C14 3BE4A1E8 */  addi    r31, r4, VolumeTable@l
/* 00B678 80010C18 3B9E069C */  addi    r28, r30, 0x69c
lbl_80010C1C:
/* 00B67C 80010C1C 801C0000 */  lwz     r0, 0(r28)
/* 00B680 80010C20 28000000 */  cmplwi  r0, 0
/* 00B684 80010C24 40820038 */  bne     lbl_80010C5C
/* 00B688 80010C28 38600000 */  li      r3, 0
/* 00B68C 80010C2C 48000499 */  bl      PopDecodedAudioBuffer
/* 00B690 80010C30 28030000 */  cmplwi  r3, 0
/* 00B694 80010C34 907C0000 */  stw     r3, 0(r28)
/* 00B698 80010C38 40820018 */  bne     lbl_80010C50
/* 00B69C 80010C3C 387A0000 */  addi    r3, r26, 0
/* 00B6A0 80010C40 5765103A */  slwi    r5, r27, 2
/* 00B6A4 80010C44 38800000 */  li      r4, 0
/* 00B6A8 80010C48 4BFF4789 */  bl      memset
/* 00B6AC 80010C4C 4800013C */  b       lbl_80010D88
lbl_80010C50:
/* 00B6B0 80010C50 807E0694 */  lwz     r3, 0x694(r30)
/* 00B6B4 80010C54 38030001 */  addi    r0, r3, 1
/* 00B6B8 80010C58 901E0694 */  stw     r0, 0x694(r30)
lbl_80010C5C:
/* 00B6BC 80010C5C 807C0000 */  lwz     r3, 0(r28)
/* 00B6C0 80010C60 80830008 */  lwz     r4, 8(r3)
/* 00B6C4 80010C64 28040000 */  cmplwi  r4, 0
/* 00B6C8 80010C68 4182FFB4 */  beq     lbl_80010C1C
/* 00B6CC 80010C6C 7C04D840 */  cmplw   r4, r27
/* 00B6D0 80010C70 41800008 */  blt     lbl_80010C78
/* 00B6D4 80010C74 7F64DB78 */  mr      r4, r27
lbl_80010C78:
/* 00B6D8 80010C78 28040000 */  cmplwi  r4, 0
/* 00B6DC 80010C7C 7C8903A6 */  mtctr   r4
/* 00B6E0 80010C80 80A30004 */  lwz     r5, 4(r3)
/* 00B6E4 80010C84 408100B4 */  ble     lbl_80010D38
lbl_80010C88:
/* 00B6E8 80010C88 807D0000 */  lwz     r3, 0(r29)
/* 00B6EC 80010C8C 2C030000 */  cmpwi   r3, 0
/* 00B6F0 80010C90 41820020 */  beq     lbl_80010CB0
/* 00B6F4 80010C94 3803FFFF */  addi    r0, r3, -1
/* 00B6F8 80010C98 901D0000 */  stw     r0, 0(r29)
/* 00B6FC 80010C9C C03E067C */  lfs     f1, 0x67c(r30)
/* 00B700 80010CA0 C01E0684 */  lfs     f0, 0x684(r30)
/* 00B704 80010CA4 EC01002A */  fadds   f0, f1, f0
/* 00B708 80010CA8 D01E067C */  stfs    f0, 0x67c(r30)
/* 00B70C 80010CAC 4800000C */  b       lbl_80010CB8
lbl_80010CB0:
/* 00B710 80010CB0 C01E0680 */  lfs     f0, 0x680(r30)
/* 00B714 80010CB4 D01E067C */  stfs    f0, 0x67c(r30)
lbl_80010CB8:
/* 00B718 80010CB8 C01E067C */  lfs     f0, 0x67c(r30)
/* 00B71C 80010CBC A8050000 */  lha     r0, 0(r5)
/* 00B720 80010CC0 FC00001E */  fctiwz  f0, f0
/* 00B724 80010CC4 D8010018 */  stfd    f0, 0x18(r1)
/* 00B728 80010CC8 8061001C */  lwz     r3, 0x1c(r1)
/* 00B72C 80010CCC 5463083C */  slwi    r3, r3, 1
/* 00B730 80010CD0 7C7F1A14 */  add     r3, r31, r3
/* 00B734 80010CD4 A0630000 */  lhz     r3, 0(r3)
/* 00B738 80010CD8 7C0301D6 */  mullw   r0, r3, r0
/* 00B73C 80010CDC 7C007E70 */  srawi   r0, r0, 0xf
/* 00B740 80010CE0 2C008000 */  cmpwi   r0, -32768
/* 00B744 80010CE4 40800008 */  bge     lbl_80010CEC
/* 00B748 80010CE8 38008000 */  li      r0, -32768
lbl_80010CEC:
/* 00B74C 80010CEC 2C007FFF */  cmpwi   r0, 0x7fff
/* 00B750 80010CF0 40810008 */  ble     lbl_80010CF8
/* 00B754 80010CF4 38007FFF */  li      r0, 0x7fff
lbl_80010CF8:
/* 00B758 80010CF8 7C000734 */  extsh   r0, r0
/* 00B75C 80010CFC B01A0000 */  sth     r0, 0(r26)
/* 00B760 80010D00 A8050002 */  lha     r0, 2(r5)
/* 00B764 80010D04 7C0301D6 */  mullw   r0, r3, r0
/* 00B768 80010D08 7C007E70 */  srawi   r0, r0, 0xf
/* 00B76C 80010D0C 2C008000 */  cmpwi   r0, -32768
/* 00B770 80010D10 40800008 */  bge     lbl_80010D18
/* 00B774 80010D14 38008000 */  li      r0, -32768
lbl_80010D18:
/* 00B778 80010D18 2C007FFF */  cmpwi   r0, 0x7fff
/* 00B77C 80010D1C 40810008 */  ble     lbl_80010D24
/* 00B780 80010D20 38007FFF */  li      r0, 0x7fff
lbl_80010D24:
/* 00B784 80010D24 7C000734 */  extsh   r0, r0
/* 00B788 80010D28 B01A0002 */  sth     r0, 2(r26)
/* 00B78C 80010D2C 3B5A0004 */  addi    r26, r26, 4
/* 00B790 80010D30 38A50004 */  addi    r5, r5, 4
/* 00B794 80010D34 4200FF54 */  bdnz    lbl_80010C88
lbl_80010D38:
/* 00B798 80010D38 807C0000 */  lwz     r3, 0(r28)
/* 00B79C 80010D3C 7F64D850 */  subf    r27, r4, r27
/* 00B7A0 80010D40 80030008 */  lwz     r0, 8(r3)
/* 00B7A4 80010D44 7C040050 */  subf    r0, r4, r0
/* 00B7A8 80010D48 90030008 */  stw     r0, 8(r3)
/* 00B7AC 80010D4C 807C0000 */  lwz     r3, 0(r28)
/* 00B7B0 80010D50 90A30004 */  stw     r5, 4(r3)
/* 00B7B4 80010D54 807C0000 */  lwz     r3, 0(r28)
/* 00B7B8 80010D58 80030008 */  lwz     r0, 8(r3)
/* 00B7BC 80010D5C 28000000 */  cmplwi  r0, 0
/* 00B7C0 80010D60 40820010 */  bne     lbl_80010D70
/* 00B7C4 80010D64 48000331 */  bl      PushFreeAudioBuffer
/* 00B7C8 80010D68 38000000 */  li      r0, 0
/* 00B7CC 80010D6C 901C0000 */  stw     r0, 0(r28)
lbl_80010D70:
/* 00B7D0 80010D70 281B0000 */  cmplwi  r27, 0
/* 00B7D4 80010D74 41820014 */  beq     lbl_80010D88
/* 00B7D8 80010D78 4BFFFEA4 */  b       lbl_80010C1C
lbl_80010D7C:
/* 00B7DC 80010D7C 54A5103A */  slwi    r5, r5, 2
/* 00B7E0 80010D80 38800000 */  li      r4, 0
/* 00B7E4 80010D84 4BFF464D */  bl      memset
lbl_80010D88:
/* 00B7E8 80010D88 BB210024 */  lmw     r25, 0x24(r1)
/* 00B7EC 80010D8C 80010044 */  lwz     r0, 0x44(r1)
/* 00B7F0 80010D90 38210040 */  addi    r1, r1, 0x40
/* 00B7F4 80010D94 7C0803A6 */  mtlr    r0
/* 00B7F8 80010D98 4E800020 */  blr     
