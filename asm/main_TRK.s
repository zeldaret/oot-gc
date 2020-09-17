# main_TRK.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKTargetCPUMinorType
/* 0C7E1C 800CD3BC 38600054 */  li		r3, 0x54
/* 0C7E20 800CD3C0 4E800020 */  blr		

glabel TRK_main
/* 0C7E24 800CD3C4 7C0802A6 */  mflr	r0
/* 0C7E28 800CD3C8 90010004 */  stw		r0, 4(r1)
/* 0C7E2C 800CD3CC 9421FFF8 */  stwu	r1, -8(r1)
/* 0C7E30 800CD3D0 4BFFC035 */  bl		TRKInitializeNub
/* 0C7E34 800CD3D4 3C808013 */  lis		r4, TRK_mainError@ha
/* 0C7E38 800CD3D8 94644AD0 */  stwu	r3, TRK_mainError@l(r4)
/* 0C7E3C 800CD3DC 80040000 */  lwz		r0, 0(r4)
/* 0C7E40 800CD3E0 2C000000 */  cmpwi	r0, 0
/* 0C7E44 800CD3E4 4082000C */  bne		lbl_800CD3F0
/* 0C7E48 800CD3E8 4BFFC115 */  bl		TRKNubWelcome
/* 0C7E4C 800CD3EC 4BFFBCC9 */  bl		TRKNubMainLoop
lbl_800CD3F0:
/* 0C7E50 800CD3F0 4BFFC0E9 */  bl		TRKTerminateNub
/* 0C7E54 800CD3F4 3C808013 */  lis		r4, TRK_mainError@ha
/* 0C7E58 800CD3F8 90644AD0 */  stw		r3, TRK_mainError@l(r4)
/* 0C7E5C 800CD3FC 38210008 */  addi	r1, r1, 8
/* 0C7E60 800CD400 80010004 */  lwz		r0, 4(r1)
/* 0C7E64 800CD404 7C0803A6 */  mtlr	r0
/* 0C7E68 800CD408 4E800020 */  blr		


.section .bss, "wa"

.balign 4

/* 00131B50 80134AD0 0004 */
TRK_mainError:
    .skip 4


