glabel frameSetColor
/* 020948 80025EE8 7C0802A6 */  mflr    r0
/* 02094C 80025EEC 90010004 */  stw     r0, 4(r1)
/* 020950 80025EF0 9421FFD8 */  stwu    r1, -0x28(r1)
/* 020954 80025EF4 93E10024 */  stw     r31, 0x24(r1)
/* 020958 80025EF8 93C10020 */  stw     r30, 0x20(r1)
/* 02095C 80025EFC 7C7F1B78 */  mr      r31, r3
/* 020960 80025F00 7C9E2378 */  mr      r30, r4
/* 020964 80025F04 3C7F0004 */  addis   r3, r31, 4
/* 020968 80025F08 57C4103A */  slwi    r4, r30, 2
/* 02096C 80025F0C 7CC32214 */  add     r6, r3, r4
/* 020970 80025F10 54A0463E */  srwi    r0, r5, 0x18
/* 020974 80025F14 38C6D124 */  addi    r6, r6, -11996
/* 020978 80025F18 98060000 */  stb     r0, 0(r6)
/* 02097C 80025F1C 54A0863E */  rlwinm  r0, r5, 0x10, 0x18, 0x1f
/* 020980 80025F20 7C632214 */  add     r3, r3, r4
/* 020984 80025F24 9803D125 */  stb     r0, -0x2edb(r3)
/* 020988 80025F28 54A0C63E */  rlwinm  r0, r5, 0x18, 0x18, 0x1f
/* 02098C 80025F2C 2C1E0003 */  cmpwi   r30, 3
/* 020990 80025F30 9803D126 */  stb     r0, -0x2eda(r3)
/* 020994 80025F34 54A0063E */  clrlwi  r0, r5, 0x18
/* 020998 80025F38 9803D127 */  stb     r0, -0x2ed9(r3)
/* 02099C 80025F3C 4082001C */  bne     lbl_80025F58
/* 0209A0 80025F40 80060000 */  lwz     r0, 0(r6)
/* 0209A4 80025F44 38810018 */  addi    r4, r1, 0x18
/* 0209A8 80025F48 38600003 */  li      r3, 3
/* 0209AC 80025F4C 90010018 */  stw     r0, 0x18(r1)
/* 0209B0 80025F50 48087A71 */  bl      GXSetTevColor
/* 0209B4 80025F54 48000020 */  b       lbl_80025F74
lbl_80025F58:
/* 0209B8 80025F58 2C1E0004 */  cmpwi   r30, 4
/* 0209BC 80025F5C 40820018 */  bne     lbl_80025F74
/* 0209C0 80025F60 80060000 */  lwz     r0, 0(r6)
/* 0209C4 80025F64 38810014 */  addi    r4, r1, 0x14
/* 0209C8 80025F68 38600001 */  li      r3, 1
/* 0209CC 80025F6C 90010014 */  stw     r0, 0x14(r1)
/* 0209D0 80025F70 48087B49 */  bl      GXSetTevKColor
lbl_80025F74:
/* 0209D4 80025F74 2C1E0000 */  cmpwi   r30, 0
/* 0209D8 80025F78 4082000C */  bne     lbl_80025F84
/* 0209DC 80025F7C 38000020 */  li      r0, 0x20
/* 0209E0 80025F80 48000008 */  b       lbl_80025F88
lbl_80025F84:
/* 0209E4 80025F84 38000000 */  li      r0, 0
lbl_80025F88:
/* 0209E8 80025F88 809F007C */  lwz     r4, 0x7c(r31)
/* 0209EC 80025F8C 60007F00 */  ori     r0, r0, 0x7f00
/* 0209F0 80025F90 3C608002 */  lis     r3, frameDrawLine_Setup@ha
/* 0209F4 80025F94 7C800378 */  or      r0, r4, r0
/* 0209F8 80025F98 901F007C */  stw     r0, 0x7c(r31)
/* 0209FC 80025F9C 38036D30 */  addi    r0, r3, frameDrawLine_Setup@l
/* 020A00 80025FA0 3C608002 */  lis     r3, frameDrawTriangle_Setup@ha
/* 020A04 80025FA4 901F012C */  stw     r0, 0x12c(r31)
/* 020A08 80025FA8 38037900 */  addi    r0, r3, frameDrawTriangle_Setup@l
/* 020A0C 80025FAC 3C608002 */  lis     r3, frameDrawRectFill_Setup@ha
/* 020A10 80025FB0 901F0130 */  stw     r0, 0x130(r31)
/* 020A14 80025FB4 380369EC */  addi    r0, r3, frameDrawRectFill_Setup@l
/* 020A18 80025FB8 3C608002 */  lis     r3, frameDrawRectTexture_Setup@ha
/* 020A1C 80025FBC 901F0134 */  stw     r0, 0x134(r31)
/* 020A20 80025FC0 38036124 */  addi    r0, r3, frameDrawRectTexture_Setup@l
/* 020A24 80025FC4 38600001 */  li      r3, 1
/* 020A28 80025FC8 901F0138 */  stw     r0, 0x138(r31)
/* 020A2C 80025FCC 8001002C */  lwz     r0, 0x2c(r1)
/* 020A30 80025FD0 83E10024 */  lwz     r31, 0x24(r1)
/* 020A34 80025FD4 83C10020 */  lwz     r30, 0x20(r1)
/* 020A38 80025FD8 7C0803A6 */  mtlr    r0
/* 020A3C 80025FDC 38210028 */  addi    r1, r1, 0x28
/* 020A40 80025FE0 4E800020 */  blr     
