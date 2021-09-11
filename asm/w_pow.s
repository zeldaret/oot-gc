# w_pow.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel pow
/* 0CC8BC 800D1E5C 7C0802A6 */  mflr    r0
/* 0CC8C0 800D1E60 90010004 */  stw     r0, 4(r1)
/* 0CC8C4 800D1E64 9421FFF8 */  stwu    r1, -8(r1)
/* 0CC8C8 800D1E68 4BFFF229 */  bl      __ieee754_pow
/* 0CC8CC 800D1E6C 8001000C */  lwz     r0, 0xc(r1)
/* 0CC8D0 800D1E70 38210008 */  addi    r1, r1, 8
/* 0CC8D4 800D1E74 7C0803A6 */  mtlr    r0
/* 0CC8D8 800D1E78 4E800020 */  blr     
