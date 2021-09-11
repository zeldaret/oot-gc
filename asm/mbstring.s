# mbstring.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel wcstombs
/* 0C9334 800CE8D4 28050000 */  cmplwi  r5, 0
/* 0C9338 800CE8D8 7CA903A6 */  mtctr   r5
/* 0C933C 800CE8DC 38C00000 */  li      r6, 0
/* 0C9340 800CE8E0 40810028 */  ble     lbl_800CE908
lbl_800CE8E4:
/* 0C9344 800CE8E4 A0040000 */  lhz     r0, 0(r4)
/* 0C9348 800CE8E8 38840002 */  addi    r4, r4, 2
/* 0C934C 800CE8EC 7C050774 */  extsb   r5, r0
/* 0C9350 800CE8F0 7CA00775 */  extsb.  r0, r5
/* 0C9354 800CE8F4 98A30000 */  stb     r5, 0(r3)
/* 0C9358 800CE8F8 38630001 */  addi    r3, r3, 1
/* 0C935C 800CE8FC 4182000C */  beq     lbl_800CE908
/* 0C9360 800CE900 38C60001 */  addi    r6, r6, 1
/* 0C9364 800CE904 4200FFE0 */  bdnz    lbl_800CE8E4
lbl_800CE908:
/* 0C9368 800CE908 7CC33378 */  mr      r3, r6
/* 0C936C 800CE90C 4E800020 */  blr     
