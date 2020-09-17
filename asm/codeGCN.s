# codeGCN.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel codeEvent
/* 016EA4 8001C444 2C040003 */  cmpwi	r4, 3
/* 016EA8 8001C448 41820048 */  beq		lbl_8001C490
/* 016EAC 8001C44C 40800018 */  bge		lbl_8001C464
/* 016EB0 8001C450 2C040002 */  cmpwi	r4, 2
/* 016EB4 8001C454 40800024 */  bge		lbl_8001C478
/* 016EB8 8001C458 2C040000 */  cmpwi	r4, 0
/* 016EBC 8001C45C 40800034 */  bge		lbl_8001C490
/* 016EC0 8001C460 48000028 */  b		lbl_8001C488
lbl_8001C464:
/* 016EC4 8001C464 2C040007 */  cmpwi	r4, 7
/* 016EC8 8001C468 40800020 */  bge		lbl_8001C488
/* 016ECC 8001C46C 2C040005 */  cmpwi	r4, 5
/* 016ED0 8001C470 40800020 */  bge		lbl_8001C490
/* 016ED4 8001C474 48000014 */  b		lbl_8001C488
lbl_8001C478:
/* 016ED8 8001C478 38000000 */  li		r0, 0
/* 016EDC 8001C47C 900D89A0 */  stw		r0, gpBufferFunction-_SDA_BASE_(r13)
/* 016EE0 8001C480 900D89A4 */  stw		r0, ganDataCode-_SDA_BASE_(r13)
/* 016EE4 8001C484 4800000C */  b		lbl_8001C490
lbl_8001C488:
/* 016EE8 8001C488 38600000 */  li		r3, 0
/* 016EEC 8001C48C 4E800020 */  blr		
lbl_8001C490:
/* 016EF0 8001C490 38600001 */  li		r3, 1
/* 016EF4 8001C494 4E800020 */  blr		


.section .data, "wa"

.balign 8

/* 000E7848 800EA7C8 0010 */
glabel gClassCode
    .long D_80134DC0, 0x00000004, 0x00000000, codeEvent


.section .sdata, "wa"

.balign 8

/* 000F1040 80134DC0 0005 */
D_80134DC0:
    .asciz "Code"


.section .sbss, "wa"

.balign 8

/* 000F1900 80135680 0004 */
gpBufferFunction:
    .skip 4

.balign 4

/* 000F1904 80135684 0004 */
ganDataCode:
    .skip 4


