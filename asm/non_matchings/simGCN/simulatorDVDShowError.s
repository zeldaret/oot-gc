glabel simulatorDVDShowError
/* 009878 8000EE18 7C0802A6 */  mflr    r0
/* 00987C 8000EE1C 3CA0800F */  lis     r5, D_800EA16C@ha
/* 009880 8000EE20 90010004 */  stw     r0, 4(r1)
/* 009884 8000EE24 3C80800F */  lis     r4, D_800E9D08@ha
/* 009888 8000EE28 3CC0800F */  lis     r6, jtbl_800EA194@ha
/* 00988C 8000EE2C 9421FFD0 */  stwu    r1, -0x30(r1)
/* 009890 8000EE30 BF410018 */  stmw    r26, 0x18(r1)
/* 009894 8000EE34 3B430000 */  addi    r26, r3, 0
/* 009898 8000EE38 3BC5A16C */  addi    r30, r5, D_800EA16C@l
/* 00989C 8000EE3C 3BE49D08 */  addi    r31, r4, D_800E9D08@l
/* 0098A0 8000EE40 3BA6A194 */  addi    r29, r6, jtbl_800EA194@l
/* 0098A4 8000EE44 3B60FFFF */  li      r27, -1
lbl_8000EE48:
/* 0098A8 8000EE48 2C1A0001 */  cmpwi   r26, 1
/* 0098AC 8000EE4C 4182003C */  beq     lbl_8000EE88
/* 0098B0 8000EE50 2C1A0000 */  cmpwi   r26, 0
/* 0098B4 8000EE54 41820034 */  beq     lbl_8000EE88
/* 0098B8 8000EE58 2C1A0002 */  cmpwi   r26, 2
/* 0098BC 8000EE5C 4182002C */  beq     lbl_8000EE88
/* 0098C0 8000EE60 2C1A0003 */  cmpwi   r26, 3
/* 0098C4 8000EE64 41820024 */  beq     lbl_8000EE88
/* 0098C8 8000EE68 2C1A0007 */  cmpwi   r26, 7
/* 0098CC 8000EE6C 4182001C */  beq     lbl_8000EE88
/* 0098D0 8000EE70 2C1A0008 */  cmpwi   r26, 8
/* 0098D4 8000EE74 41820014 */  beq     lbl_8000EE88
/* 0098D8 8000EE78 2C1A000A */  cmpwi   r26, 0xa
/* 0098DC 8000EE7C 4182000C */  beq     lbl_8000EE88
/* 0098E0 8000EE80 3B800001 */  li      r28, 1
/* 0098E4 8000EE84 48000008 */  b       lbl_8000EE8C
lbl_8000EE88:
/* 0098E8 8000EE88 3B800000 */  li      r28, 0
lbl_8000EE8C:
/* 0098EC 8000EE8C 381A0001 */  addi    r0, r26, 1
/* 0098F0 8000EE90 2800000C */  cmplwi  r0, 0xc
/* 0098F4 8000EE94 4181003C */  bgt     lbl_8000EED0
/* 0098F8 8000EE98 5400103A */  slwi    r0, r0, 2
/* 0098FC 8000EE9C 7C1D002E */  lwzx    r0, r29, r0
/* 009900 8000EEA0 7C0903A6 */  mtctr   r0
/* 009904 8000EEA4 4E800420 */  bctr    
.global lbl_8000EEA8
lbl_8000EEA8:
/* 009908 8000EEA8 3B600003 */  li      r27, 3
/* 00990C 8000EEAC 48000040 */  b       lbl_8000EEEC
.global lbl_8000EEB0
lbl_8000EEB0:
/* 009910 8000EEB0 3B600005 */  li      r27, 5
/* 009914 8000EEB4 48000038 */  b       lbl_8000EEEC
.global lbl_8000EEB8
lbl_8000EEB8:
/* 009918 8000EEB8 3B600000 */  li      r27, 0
/* 00991C 8000EEBC 48000030 */  b       lbl_8000EEEC
.global lbl_8000EEC0
lbl_8000EEC0:
/* 009920 8000EEC0 3B600001 */  li      r27, 1
/* 009924 8000EEC4 48000028 */  b       lbl_8000EEEC
.global lbl_8000EEC8
lbl_8000EEC8:
/* 009928 8000EEC8 3B600004 */  li      r27, 4
/* 00992C 8000EECC 48000020 */  b       lbl_8000EEEC
lbl_8000EED0:
/* 009930 8000EED0 387E0000 */  addi    r3, r30, 0
/* 009934 8000EED4 4CC63182 */  crclr   6
/* 009938 8000EED8 389F0000 */  addi    r4, r31, 0
/* 00993C 8000EEDC 38DA0000 */  addi    r6, r26, 0
/* 009940 8000EEE0 3B600006 */  li      r27, 6
/* 009944 8000EEE4 38A002FB */  li      r5, 0x2fb
/* 009948 8000EEE8 4BFF6F2D */  bl      xlPostText
.global lbl_8000EEEC
lbl_8000EEEC:
/* 00994C 8000EEEC 2C1A0001 */  cmpwi   r26, 1
/* 009950 8000EEF0 41820040 */  beq     lbl_8000EF30
/* 009954 8000EEF4 2C1A0000 */  cmpwi   r26, 0
/* 009958 8000EEF8 41820038 */  beq     lbl_8000EF30
/* 00995C 8000EEFC 2C1A0002 */  cmpwi   r26, 2
/* 009960 8000EF00 41820030 */  beq     lbl_8000EF30
/* 009964 8000EF04 2C1A0003 */  cmpwi   r26, 3
/* 009968 8000EF08 41820028 */  beq     lbl_8000EF30
/* 00996C 8000EF0C 2C1A0007 */  cmpwi   r26, 7
/* 009970 8000EF10 41820020 */  beq     lbl_8000EF30
/* 009974 8000EF14 2C1A0008 */  cmpwi   r26, 8
/* 009978 8000EF18 41820018 */  beq     lbl_8000EF30
/* 00997C 8000EF1C 2C1A000A */  cmpwi   r26, 0xa
/* 009980 8000EF20 41820010 */  beq     lbl_8000EF30
/* 009984 8000EF24 38000001 */  li      r0, 1
/* 009988 8000EF28 900D88FC */  stw     r0, toggle@sda21(r13)
/* 00998C 8000EF2C 4800001C */  b       lbl_8000EF48
lbl_8000EF30:
/* 009990 8000EF30 800D88FC */  lwz     r0, toggle@sda21(r13)
/* 009994 8000EF34 2C000001 */  cmpwi   r0, 1
/* 009998 8000EF38 40820010 */  bne     lbl_8000EF48
/* 00999C 8000EF3C 38000000 */  li      r0, 0
/* 0099A0 8000EF40 900D88FC */  stw     r0, toggle@sda21(r13)
/* 0099A4 8000EF44 3B600002 */  li      r27, 2
lbl_8000EF48:
/* 0099A8 8000EF48 800D88F8 */  lwz     r0, gDVDResetToggle@sda21(r13)
/* 0099AC 8000EF4C 2C000001 */  cmpwi   r0, 1
/* 0099B0 8000EF50 40820044 */  bne     lbl_8000EF94
/* 0099B4 8000EF54 281A0003 */  cmplwi  r26, 3
/* 0099B8 8000EF58 40810018 */  ble     lbl_8000EF70
/* 0099BC 8000EF5C 381AFFF9 */  addi    r0, r26, -7
/* 0099C0 8000EF60 28000001 */  cmplwi  r0, 1
/* 0099C4 8000EF64 4081000C */  ble     lbl_8000EF70
/* 0099C8 8000EF68 2C1A000A */  cmpwi   r26, 0xa
/* 0099CC 8000EF6C 40820028 */  bne     lbl_8000EF94
lbl_8000EF70:
/* 0099D0 8000EF70 38600000 */  li      r3, 0
/* 0099D4 8000EF74 38800000 */  li      r4, 0
/* 0099D8 8000EF78 38A00001 */  li      r5, 1
/* 0099DC 8000EF7C 38C00000 */  li      r6, 0
/* 0099E0 8000EF80 4BFF9C5D */  bl      simulatorTestReset
/* 0099E4 8000EF84 2C030000 */  cmpwi   r3, 0
/* 0099E8 8000EF88 40820038 */  bne     lbl_8000EFC0
/* 0099EC 8000EF8C 38600000 */  li      r3, 0
/* 0099F0 8000EF90 4800007C */  b       lbl_8000F00C
lbl_8000EF94:
/* 0099F4 8000EF94 2C1AFFFF */  cmpwi   r26, -1
/* 0099F8 8000EF98 41820028 */  beq     lbl_8000EFC0
/* 0099FC 8000EF9C 38600001 */  li      r3, 1
/* 009A00 8000EFA0 38800000 */  li      r4, 0
/* 009A04 8000EFA4 38A00001 */  li      r5, 1
/* 009A08 8000EFA8 38C00000 */  li      r6, 0
/* 009A0C 8000EFAC 4BFF9C31 */  bl      simulatorTestReset
/* 009A10 8000EFB0 2C030000 */  cmpwi   r3, 0
/* 009A14 8000EFB4 4082000C */  bne     lbl_8000EFC0
/* 009A18 8000EFB8 38600000 */  li      r3, 0
/* 009A1C 8000EFBC 48000050 */  b       lbl_8000F00C
lbl_8000EFC0:
/* 009A20 8000EFC0 2C1BFFFF */  cmpwi   r27, -1
/* 009A24 8000EFC4 41820034 */  beq     lbl_8000EFF8
lbl_8000EFC8:
/* 009A28 8000EFC8 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 009A2C 8000EFCC 80630000 */  lwz     r3, 0(r3)
/* 009A30 8000EFD0 48016EFD */  bl      frameBeginOK
/* 009A34 8000EFD4 2C030000 */  cmpwi   r3, 0
/* 009A38 8000EFD8 4182FFF0 */  beq     lbl_8000EFC8
/* 009A3C 8000EFDC 38600000 */  li      r3, 0
/* 009A40 8000EFE0 38800000 */  li      r4, 0
/* 009A44 8000EFE4 480A1E4D */  bl      PADControlMotor
/* 009A48 8000EFE8 387B0000 */  addi    r3, r27, 0
/* 009A4C 8000EFEC 38800000 */  li      r4, 0
/* 009A50 8000EFF0 38A00000 */  li      r5, 0
/* 009A54 8000EFF4 4BFFE369 */  bl      simulatorDrawErrorMessage
lbl_8000EFF8:
/* 009A58 8000EFF8 480A6001 */  bl      DVDGetDriveStatus
/* 009A5C 8000EFFC 2C1C0001 */  cmpwi   r28, 1
/* 009A60 8000F000 3B430000 */  addi    r26, r3, 0
/* 009A64 8000F004 4182FE44 */  beq     lbl_8000EE48
/* 009A68 8000F008 38600001 */  li      r3, 1
lbl_8000F00C:
/* 009A6C 8000F00C BB410018 */  lmw     r26, 0x18(r1)
/* 009A70 8000F010 80010034 */  lwz     r0, 0x34(r1)
/* 009A74 8000F014 38210030 */  addi    r1, r1, 0x30
/* 009A78 8000F018 7C0803A6 */  mtlr    r0
/* 009A7C 8000F01C 4E800020 */  blr     
