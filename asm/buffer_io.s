# buffer_io.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __flush_buffer
/* 0C8F04 800CE4A4 7C0802A6 */  mflr    r0
/* 0C8F08 800CE4A8 90010004 */  stw     r0, 4(r1)
/* 0C8F0C 800CE4AC 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0C8F10 800CE4B0 93E10014 */  stw     r31, 0x14(r1)
/* 0C8F14 800CE4B4 7C7F1B78 */  mr      r31, r3
/* 0C8F18 800CE4B8 93C10010 */  stw     r30, 0x10(r1)
/* 0C8F1C 800CE4BC 7C9E2378 */  mr      r30, r4
/* 0C8F20 800CE4C0 80630018 */  lwz     r3, 0x18(r3)
/* 0C8F24 800CE4C4 801F0020 */  lwz     r0, 0x20(r31)
/* 0C8F28 800CE4C8 7C030051 */  subf.   r0, r3, r0
/* 0C8F2C 800CE4CC 41820058 */  beq     lbl_800CE524
/* 0C8F30 800CE4D0 901F0024 */  stw     r0, 0x24(r31)
/* 0C8F34 800CE4D4 881F0005 */  lbz     r0, 5(r31)
/* 0C8F38 800CE4D8 5400EFFF */  rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 0C8F3C 800CE4DC 819F003C */  lwz     r12, 0x3c(r31)
/* 0C8F40 800CE4E0 38BF0024 */  addi    r5, r31, 0x24
/* 0C8F44 800CE4E4 807F0000 */  lwz     r3, 0(r31)
/* 0C8F48 800CE4E8 7D8803A6 */  mtlr    r12
/* 0C8F4C 800CE4EC 809F0018 */  lwz     r4, 0x18(r31)
/* 0C8F50 800CE4F0 80DF0044 */  lwz     r6, 0x44(r31)
/* 0C8F54 800CE4F4 4E800021 */  blrl    
/* 0C8F58 800CE4F8 281E0000 */  cmplwi  r30, 0
/* 0C8F5C 800CE4FC 4182000C */  beq     lbl_800CE508
/* 0C8F60 800CE500 801F0024 */  lwz     r0, 0x24(r31)
/* 0C8F64 800CE504 901E0000 */  stw     r0, 0(r30)
lbl_800CE508:
/* 0C8F68 800CE508 2C030000 */  cmpwi   r3, 0
/* 0C8F6C 800CE50C 41820008 */  beq     lbl_800CE514
/* 0C8F70 800CE510 48000048 */  b       lbl_800CE558
lbl_800CE514:
/* 0C8F74 800CE514 807F0014 */  lwz     r3, 0x14(r31)
/* 0C8F78 800CE518 801F0024 */  lwz     r0, 0x24(r31)
/* 0C8F7C 800CE51C 7C030214 */  add     r0, r3, r0
/* 0C8F80 800CE520 901F0014 */  stw     r0, 0x14(r31)
lbl_800CE524:
/* 0C8F84 800CE524 801F0018 */  lwz     r0, 0x18(r31)
/* 0C8F88 800CE528 38600000 */  li      r3, 0
/* 0C8F8C 800CE52C 901F0020 */  stw     r0, 0x20(r31)
/* 0C8F90 800CE530 801F001C */  lwz     r0, 0x1c(r31)
/* 0C8F94 800CE534 901F0024 */  stw     r0, 0x24(r31)
/* 0C8F98 800CE538 80BF0014 */  lwz     r5, 0x14(r31)
/* 0C8F9C 800CE53C 809F0028 */  lwz     r4, 0x28(r31)
/* 0C8FA0 800CE540 801F0024 */  lwz     r0, 0x24(r31)
/* 0C8FA4 800CE544 7CA42038 */  and     r4, r5, r4
/* 0C8FA8 800CE548 7C040050 */  subf    r0, r4, r0
/* 0C8FAC 800CE54C 901F0024 */  stw     r0, 0x24(r31)
/* 0C8FB0 800CE550 801F0014 */  lwz     r0, 0x14(r31)
/* 0C8FB4 800CE554 901F0030 */  stw     r0, 0x30(r31)
lbl_800CE558:
/* 0C8FB8 800CE558 8001001C */  lwz     r0, 0x1c(r1)
/* 0C8FBC 800CE55C 83E10014 */  lwz     r31, 0x14(r1)
/* 0C8FC0 800CE560 83C10010 */  lwz     r30, 0x10(r1)
/* 0C8FC4 800CE564 7C0803A6 */  mtlr    r0
/* 0C8FC8 800CE568 38210018 */  addi    r1, r1, 0x18
/* 0C8FCC 800CE56C 4E800020 */  blr     

glabel __prep_buffer
/* 0C8FD0 800CE570 80030018 */  lwz     r0, 0x18(r3)
/* 0C8FD4 800CE574 90030020 */  stw     r0, 0x20(r3)
/* 0C8FD8 800CE578 8003001C */  lwz     r0, 0x1c(r3)
/* 0C8FDC 800CE57C 90030024 */  stw     r0, 0x24(r3)
/* 0C8FE0 800CE580 80A30014 */  lwz     r5, 0x14(r3)
/* 0C8FE4 800CE584 80830028 */  lwz     r4, 0x28(r3)
/* 0C8FE8 800CE588 80030024 */  lwz     r0, 0x24(r3)
/* 0C8FEC 800CE58C 7CA42038 */  and     r4, r5, r4
/* 0C8FF0 800CE590 7C040050 */  subf    r0, r4, r0
/* 0C8FF4 800CE594 90030024 */  stw     r0, 0x24(r3)
/* 0C8FF8 800CE598 80030014 */  lwz     r0, 0x14(r3)
/* 0C8FFC 800CE59C 90030030 */  stw     r0, 0x30(r3)
/* 0C9000 800CE5A0 4E800020 */  blr     


