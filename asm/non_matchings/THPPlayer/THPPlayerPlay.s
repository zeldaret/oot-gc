glabel THPPlayerPlay
/* 00ACF4 80010294 3C608010 */  lis     r3, WorkBuffer@ha
/* 00ACF8 80010298 38A396E0 */  addi    r5, r3, WorkBuffer@l
/* 00ACFC 8001029C 80050640 */  lwz     r0, 0x640(r5)
/* 00AD00 800102A0 2C000000 */  cmpwi   r0, 0
/* 00AD04 800102A4 41820044 */  beq     lbl_800102E8
/* 00AD08 800102A8 38650644 */  addi    r3, r5, 0x644
/* 00AD0C 800102AC 88050644 */  lbz     r0, 0x644(r5)
/* 00AD10 800102B0 28000001 */  cmplwi  r0, 1
/* 00AD14 800102B4 4182000C */  beq     lbl_800102C0
/* 00AD18 800102B8 28000004 */  cmplwi  r0, 4
/* 00AD1C 800102BC 4082002C */  bne     lbl_800102E8
lbl_800102C0:
/* 00AD20 800102C0 38000002 */  li      r0, 2
/* 00AD24 800102C4 98030000 */  stb     r0, 0(r3)
/* 00AD28 800102C8 38800000 */  li      r4, 0
/* 00AD2C 800102CC 3800FFFF */  li      r0, -1
/* 00AD30 800102D0 90850670 */  stw     r4, 0x670(r5)
/* 00AD34 800102D4 38600001 */  li      r3, 1
/* 00AD38 800102D8 90850674 */  stw     r4, 0x674(r5)
/* 00AD3C 800102DC 9005066C */  stw     r0, 0x66c(r5)
/* 00AD40 800102E0 90050668 */  stw     r0, 0x668(r5)
/* 00AD44 800102E4 4E800020 */  blr     
lbl_800102E8:
/* 00AD48 800102E8 38600000 */  li      r3, 0
/* 00AD4C 800102EC 4E800020 */  blr     
