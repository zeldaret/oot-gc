glabel treeSearchNode
/* 02CAE8 80032088 28030000 */  cmplwi  r3, 0
/* 02CAEC 8003208C 4082000C */  bne     lbl_80032098
/* 02CAF0 80032090 38600000 */  li      r3, 0
/* 02CAF4 80032094 4E800020 */  blr     
lbl_80032098:
/* 02CAF8 80032098 80C30010 */  lwz     r6, 0x10(r3)
/* 02CAFC 8003209C 7C043000 */  cmpw    r4, r6
/* 02CB00 800320A0 4180001C */  blt     lbl_800320BC
/* 02CB04 800320A4 80030014 */  lwz     r0, 0x14(r3)
/* 02CB08 800320A8 7C040000 */  cmpw    r4, r0
/* 02CB0C 800320AC 40800010 */  bge     lbl_800320BC
/* 02CB10 800320B0 90650000 */  stw     r3, 0(r5)
/* 02CB14 800320B4 38600001 */  li      r3, 1
/* 02CB18 800320B8 4E800020 */  blr     
lbl_800320BC:
/* 02CB1C 800320BC 7C043000 */  cmpw    r4, r6
/* 02CB20 800320C0 4080000C */  bge     lbl_800320CC
/* 02CB24 800320C4 80630040 */  lwz     r3, 0x40(r3)
/* 02CB28 800320C8 48000014 */  b       lbl_800320DC
lbl_800320CC:
/* 02CB2C 800320CC 4081000C */  ble     lbl_800320D8
/* 02CB30 800320D0 80630044 */  lwz     r3, 0x44(r3)
/* 02CB34 800320D4 48000008 */  b       lbl_800320DC
lbl_800320D8:
/* 02CB38 800320D8 38600000 */  li      r3, 0
lbl_800320DC:
/* 02CB3C 800320DC 28030000 */  cmplwi  r3, 0
/* 02CB40 800320E0 4082FFB8 */  bne     lbl_80032098
/* 02CB44 800320E4 38600000 */  li      r3, 0
/* 02CB48 800320E8 4E800020 */  blr     
