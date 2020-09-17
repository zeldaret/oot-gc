# s_copysign.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel copysign
/* 0CC510 800D1AB0 9421FFE8 */  stwu	r1, -0x18(r1)
/* 0CC514 800D1AB4 D8210008 */  stfd	f1, 8(r1)
/* 0CC518 800D1AB8 D8410010 */  stfd	f2, 0x10(r1)
/* 0CC51C 800D1ABC 80610008 */  lwz		r3, 8(r1)
/* 0CC520 800D1AC0 80010010 */  lwz		r0, 0x10(r1)
/* 0CC524 800D1AC4 54000000 */  rlwinm	r0, r0, 0, 0, 0
/* 0CC528 800D1AC8 5060007E */  rlwimi	r0, r3, 0, 1, 0x1f
/* 0CC52C 800D1ACC 90010008 */  stw		r0, 8(r1)
/* 0CC530 800D1AD0 C8210008 */  lfd		f1, 8(r1)
/* 0CC534 800D1AD4 38210018 */  addi	r1, r1, 0x18
/* 0CC538 800D1AD8 4E800020 */  blr		


