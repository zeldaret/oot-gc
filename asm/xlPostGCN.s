# xlPostGCN.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel xlPostReset
/* 000864 80005E04 38600001 */  li      r3, 1
/* 000868 80005E08 4E800020 */  blr     

glabel xlPostSetup
/* 00086C 80005E0C 38600001 */  li      r3, 1
/* 000870 80005E10 4E800020 */  blr     

glabel xlPostText
/* 000874 80005E14 9421FF88 */  stwu    r1, -0x78(r1)
/* 000878 80005E18 40860024 */  bne     cr1, lbl_80005E3C
/* 00087C 80005E1C D8210028 */  stfd    f1, 0x28(r1)
/* 000880 80005E20 D8410030 */  stfd    f2, 0x30(r1)
/* 000884 80005E24 D8610038 */  stfd    f3, 0x38(r1)
/* 000888 80005E28 D8810040 */  stfd    f4, 0x40(r1)
/* 00088C 80005E2C D8A10048 */  stfd    f5, 0x48(r1)
/* 000890 80005E30 D8C10050 */  stfd    f6, 0x50(r1)
/* 000894 80005E34 D8E10058 */  stfd    f7, 0x58(r1)
/* 000898 80005E38 D9010060 */  stfd    f8, 0x60(r1)
lbl_80005E3C:
/* 00089C 80005E3C 90610008 */  stw     r3, 8(r1)
/* 0008A0 80005E40 38600001 */  li      r3, 1
/* 0008A4 80005E44 9081000C */  stw     r4, 0xc(r1)
/* 0008A8 80005E48 90A10010 */  stw     r5, 0x10(r1)
/* 0008AC 80005E4C 90C10014 */  stw     r6, 0x14(r1)
/* 0008B0 80005E50 90E10018 */  stw     r7, 0x18(r1)
/* 0008B4 80005E54 9101001C */  stw     r8, 0x1c(r1)
/* 0008B8 80005E58 91210020 */  stw     r9, 0x20(r1)
/* 0008BC 80005E5C 91410024 */  stw     r10, 0x24(r1)
/* 0008C0 80005E60 38210078 */  addi    r1, r1, 0x78
/* 0008C4 80005E64 4E800020 */  blr     

.section .bss, "wa"

.balign 4

/* 000F0F9C 800F3F1C 0080 */
glabel g_texMap
    .skip 128
