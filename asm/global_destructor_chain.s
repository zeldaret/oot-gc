# global_destructor_chain.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __destroy_global_chain
/* 0C82EC 800CD88C 7C0802A6 */  mflr    r0
/* 0C82F0 800CD890 90010004 */  stw     r0, 4(r1)
/* 0C82F4 800CD894 9421FFF8 */  stwu    r1, -8(r1)
/* 0C82F8 800CD898 48000020 */  b       lbl_800CD8B8
lbl_800CD89C:
/* 0C82FC 800CD89C 80030000 */  lwz     r0, 0(r3)
/* 0C8300 800CD8A0 3880FFFF */  li      r4, -1
/* 0C8304 800CD8A4 900D8FD8 */  stw     r0, __global_destructor_chain-_SDA_BASE_(r13)
/* 0C8308 800CD8A8 81830004 */  lwz     r12, 4(r3)
/* 0C830C 800CD8AC 80630008 */  lwz     r3, 8(r3)
/* 0C8310 800CD8B0 7D8803A6 */  mtlr    r12
/* 0C8314 800CD8B4 4E800021 */  blrl    
lbl_800CD8B8:
/* 0C8318 800CD8B8 806D8FD8 */  lwz     r3, __global_destructor_chain-_SDA_BASE_(r13)
/* 0C831C 800CD8BC 28030000 */  cmplwi  r3, 0
/* 0C8320 800CD8C0 4082FFDC */  bne     lbl_800CD89C
/* 0C8324 800CD8C4 8001000C */  lwz     r0, 0xc(r1)
/* 0C8328 800CD8C8 38210008 */  addi    r1, r1, 8
/* 0C832C 800CD8CC 7C0803A6 */  mtlr    r0
/* 0C8330 800CD8D0 4E800020 */  blr     


.section .sbss, "wa"

.balign 8

/* 000F1F38 80135CB8 0004 */
glabel __global_destructor_chain
    .skip 4


