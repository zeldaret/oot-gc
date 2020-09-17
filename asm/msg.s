# msg.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKMessageSend
/* 0C3FF8 800C9598 7C0802A6 */  mflr	r0
/* 0C3FFC 800C959C 90010004 */  stw		r0, 4(r1)
/* 0C4000 800C95A0 9421FFF8 */  stwu	r1, -8(r1)
/* 0C4004 800C95A4 80830008 */  lwz		r4, 8(r3)
/* 0C4008 800C95A8 38630010 */  addi	r3, r3, 0x10
/* 0C400C 800C95AC 480040F1 */  bl		TRK_WriteUARTN
/* 0C4010 800C95B0 38210008 */  addi	r1, r1, 8
/* 0C4014 800C95B4 80010004 */  lwz		r0, 4(r1)
/* 0C4018 800C95B8 7C0803A6 */  mtlr	r0
/* 0C401C 800C95BC 4E800020 */  blr		


