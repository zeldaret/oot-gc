# dvdFatal.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __DVDPrintFatalMessage
/* 0B058C 800B5B2C 7C0802A6 */  mflr	r0
/* 0B0590 800B5B30 90010004 */  stw		r0, 4(r1)
/* 0B0594 800B5B34 9421FFF8 */  stwu	r1, -8(r1)
/* 0B0598 800B5B38 818D8D78 */  lwz		r12, FatalFunc-_SDA_BASE_(r13)
/* 0B059C 800B5B3C 280C0000 */  cmplwi	r12, 0
/* 0B05A0 800B5B40 4182000C */  beq		lbl_800B5B4C
/* 0B05A4 800B5B44 7D8803A6 */  mtlr	r12
/* 0B05A8 800B5B48 4E800021 */  blrl	
lbl_800B5B4C:
/* 0B05AC 800B5B4C 8001000C */  lwz		r0, 0xc(r1)
/* 0B05B0 800B5B50 38210008 */  addi	r1, r1, 8
/* 0B05B4 800B5B54 7C0803A6 */  mtlr	r0
/* 0B05B8 800B5B58 4E800020 */  blr		


.section .sbss, "wa"

.balign 8

/* 000F1CD8 80135A58 0004 */
FatalFunc:
    .skip 4


