glabel rspFillObjSprite
/* 0755B4 8007AB54 7C0802A6 */  mflr    r0
/* 0755B8 8007AB58 38C00000 */  li      r6, 0
/* 0755BC 8007AB5C 90010004 */  stw     r0, 4(r1)
/* 0755C0 8007AB60 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0755C4 8007AB64 93E1001C */  stw     r31, 0x1c(r1)
/* 0755C8 8007AB68 7CBF2B78 */  mr      r31, r5
/* 0755CC 8007AB6C 38A40000 */  addi    r5, r4, 0
/* 0755D0 8007AB70 806338E8 */  lwz     r3, 0x38e8(r3)
/* 0755D4 8007AB74 38810014 */  addi    r4, r1, 0x14
/* 0755D8 8007AB78 8063002C */  lwz     r3, 0x2c(r3)
/* 0755DC 8007AB7C 4BFF2525 */  bl      ramGetBuffer
/* 0755E0 8007AB80 2C030000 */  cmpwi   r3, 0
/* 0755E4 8007AB84 4082000C */  bne     lbl_8007AB90
/* 0755E8 8007AB88 38600000 */  li      r3, 0
/* 0755EC 8007AB8C 4800007C */  b       lbl_8007AC08
lbl_8007AB90:
/* 0755F0 8007AB90 80810014 */  lwz     r4, 0x14(r1)
/* 0755F4 8007AB94 38600001 */  li      r3, 1
/* 0755F8 8007AB98 A8040000 */  lha     r0, 0(r4)
/* 0755FC 8007AB9C B01F0000 */  sth     r0, 0(r31)
/* 075600 8007ABA0 A0040002 */  lhz     r0, 2(r4)
/* 075604 8007ABA4 B01F0002 */  sth     r0, 2(r31)
/* 075608 8007ABA8 A0040004 */  lhz     r0, 4(r4)
/* 07560C 8007ABAC B01F0004 */  sth     r0, 4(r31)
/* 075610 8007ABB0 A0040006 */  lhz     r0, 6(r4)
/* 075614 8007ABB4 B01F0006 */  sth     r0, 6(r31)
/* 075618 8007ABB8 A8040008 */  lha     r0, 8(r4)
/* 07561C 8007ABBC B01F0008 */  sth     r0, 8(r31)
/* 075620 8007ABC0 A004000A */  lhz     r0, 0xa(r4)
/* 075624 8007ABC4 B01F000A */  sth     r0, 0xa(r31)
/* 075628 8007ABC8 A004000C */  lhz     r0, 0xc(r4)
/* 07562C 8007ABCC B01F000C */  sth     r0, 0xc(r31)
/* 075630 8007ABD0 A004000E */  lhz     r0, 0xe(r4)
/* 075634 8007ABD4 B01F000E */  sth     r0, 0xe(r31)
/* 075638 8007ABD8 A0040010 */  lhz     r0, 0x10(r4)
/* 07563C 8007ABDC B01F0010 */  sth     r0, 0x10(r31)
/* 075640 8007ABE0 A0040012 */  lhz     r0, 0x12(r4)
/* 075644 8007ABE4 B01F0012 */  sth     r0, 0x12(r31)
/* 075648 8007ABE8 88040014 */  lbz     r0, 0x14(r4)
/* 07564C 8007ABEC 981F0014 */  stb     r0, 0x14(r31)
/* 075650 8007ABF0 88040015 */  lbz     r0, 0x15(r4)
/* 075654 8007ABF4 981F0015 */  stb     r0, 0x15(r31)
/* 075658 8007ABF8 88040016 */  lbz     r0, 0x16(r4)
/* 07565C 8007ABFC 981F0016 */  stb     r0, 0x16(r31)
/* 075660 8007AC00 88040017 */  lbz     r0, 0x17(r4)
/* 075664 8007AC04 981F0017 */  stb     r0, 0x17(r31)
lbl_8007AC08:
/* 075668 8007AC08 80010024 */  lwz     r0, 0x24(r1)
/* 07566C 8007AC0C 83E1001C */  lwz     r31, 0x1c(r1)
/* 075670 8007AC10 38210020 */  addi    r1, r1, 0x20
/* 075674 8007AC14 7C0803A6 */  mtlr    r0
/* 075678 8007AC18 4E800020 */  blr     
