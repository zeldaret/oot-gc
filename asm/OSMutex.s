# OSMutex.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __OSUnlockAllMutex
/* 09A4BC 8009FA5C 7C0802A6 */  mflr    r0
/* 09A4C0 8009FA60 90010004 */  stw     r0, 4(r1)
/* 09A4C4 8009FA64 9421FFE8 */  stwu    r1, -0x18(r1)
/* 09A4C8 8009FA68 93E10014 */  stw     r31, 0x14(r1)
/* 09A4CC 8009FA6C 3BE00000 */  li      r31, 0
/* 09A4D0 8009FA70 93C10010 */  stw     r30, 0x10(r1)
/* 09A4D4 8009FA74 3BC30000 */  addi    r30, r3, 0
/* 09A4D8 8009FA78 48000030 */  b       lbl_8009FAA8
lbl_8009FA7C:
/* 09A4DC 8009FA7C 80A40010 */  lwz     r5, 0x10(r4)
/* 09A4E0 8009FA80 38640000 */  addi    r3, r4, 0
/* 09A4E4 8009FA84 28050000 */  cmplwi  r5, 0
/* 09A4E8 8009FA88 4082000C */  bne     lbl_8009FA94
/* 09A4EC 8009FA8C 93FE02F8 */  stw     r31, 0x2f8(r30)
/* 09A4F0 8009FA90 48000008 */  b       lbl_8009FA98
lbl_8009FA94:
/* 09A4F4 8009FA94 93E50014 */  stw     r31, 0x14(r5)
lbl_8009FA98:
/* 09A4F8 8009FA98 90BE02F4 */  stw     r5, 0x2f4(r30)
/* 09A4FC 8009FA9C 93E4000C */  stw     r31, 0xc(r4)
/* 09A500 8009FAA0 93E40008 */  stw     r31, 8(r4)
/* 09A504 8009FAA4 48002655 */  bl      OSWakeupThread
lbl_8009FAA8:
/* 09A508 8009FAA8 809E02F4 */  lwz     r4, 0x2f4(r30)
/* 09A50C 8009FAAC 28040000 */  cmplwi  r4, 0
/* 09A510 8009FAB0 4082FFCC */  bne     lbl_8009FA7C
/* 09A514 8009FAB4 8001001C */  lwz     r0, 0x1c(r1)
/* 09A518 8009FAB8 83E10014 */  lwz     r31, 0x14(r1)
/* 09A51C 8009FABC 83C10010 */  lwz     r30, 0x10(r1)
/* 09A520 8009FAC0 38210018 */  addi    r1, r1, 0x18
/* 09A524 8009FAC4 7C0803A6 */  mtlr    r0
/* 09A528 8009FAC8 4E800020 */  blr     


