# dsp_debug.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __DSP_debug_printf
/* 0B4EE8 800BA488 9421FF90 */  stwu    r1, -0x70(r1)
/* 0B4EEC 800BA48C 40860024 */  bne     cr1, lbl_800BA4B0
/* 0B4EF0 800BA490 D8210028 */  stfd    f1, 0x28(r1)
/* 0B4EF4 800BA494 D8410030 */  stfd    f2, 0x30(r1)
/* 0B4EF8 800BA498 D8610038 */  stfd    f3, 0x38(r1)
/* 0B4EFC 800BA49C D8810040 */  stfd    f4, 0x40(r1)
/* 0B4F00 800BA4A0 D8A10048 */  stfd    f5, 0x48(r1)
/* 0B4F04 800BA4A4 D8C10050 */  stfd    f6, 0x50(r1)
/* 0B4F08 800BA4A8 D8E10058 */  stfd    f7, 0x58(r1)
/* 0B4F0C 800BA4AC D9010060 */  stfd    f8, 0x60(r1)
lbl_800BA4B0:
/* 0B4F10 800BA4B0 90610008 */  stw     r3, 8(r1)
/* 0B4F14 800BA4B4 9081000C */  stw     r4, 0xc(r1)
/* 0B4F18 800BA4B8 90A10010 */  stw     r5, 0x10(r1)
/* 0B4F1C 800BA4BC 90C10014 */  stw     r6, 0x14(r1)
/* 0B4F20 800BA4C0 90E10018 */  stw     r7, 0x18(r1)
/* 0B4F24 800BA4C4 9101001C */  stw     r8, 0x1c(r1)
/* 0B4F28 800BA4C8 91210020 */  stw     r9, 0x20(r1)
/* 0B4F2C 800BA4CC 91410024 */  stw     r10, 0x24(r1)
/* 0B4F30 800BA4D0 38210070 */  addi    r1, r1, 0x70
/* 0B4F34 800BA4D4 4E800020 */  blr     
