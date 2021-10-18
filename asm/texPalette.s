# texPalette.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TEXGet
/* 0C39BC 800C8F5C 80630008 */  lwz     r3, 8(r3)
/* 0C39C0 800C8F60 54801838 */  slwi    r0, r4, 3
/* 0C39C4 800C8F64 7C630214 */  add     r3, r3, r0
/* 0C39C8 800C8F68 4E800020 */  blr     

glabel TEXGetGXTexObjFromPalette
/* 0C39CC 800C8F6C 7C0802A6 */  mflr    r0
/* 0C39D0 800C8F70 90010004 */  stw     r0, 4(r1)
/* 0C39D4 800C8F74 54A01838 */  slwi    r0, r5, 3
/* 0C39D8 800C8F78 9421FFD0 */  stwu    r1, -0x30(r1)
/* 0C39DC 800C8F7C 93E1002C */  stw     r31, 0x2c(r1)
/* 0C39E0 800C8F80 93C10028 */  stw     r30, 0x28(r1)
/* 0C39E4 800C8F84 3BC40000 */  addi    r30, r4, 0
/* 0C39E8 800C8F88 80630008 */  lwz     r3, 8(r3)
/* 0C39EC 800C8F8C 7FE30214 */  add     r31, r3, r0
/* 0C39F0 800C8F90 809F0000 */  lwz     r4, 0(r31)
/* 0C39F4 800C8F94 88640021 */  lbz     r3, 0x21(r4)
/* 0C39F8 800C8F98 88040022 */  lbz     r0, 0x22(r4)
/* 0C39FC 800C8F9C 7C030040 */  cmplw   r3, r0
/* 0C3A00 800C8FA0 4082000C */  bne     lbl_800C8FAC
/* 0C3A04 800C8FA4 39400000 */  li      r10, 0
/* 0C3A08 800C8FA8 48000008 */  b       lbl_800C8FB0
lbl_800C8FAC:
/* 0C3A0C 800C8FAC 39400001 */  li      r10, 1
lbl_800C8FB0:
/* 0C3A10 800C8FB0 813F0000 */  lwz     r9, 0(r31)
/* 0C3A14 800C8FB4 7FC3F378 */  mr      r3, r30
/* 0C3A18 800C8FB8 80890008 */  lwz     r4, 8(r9)
/* 0C3A1C 800C8FBC A0A90002 */  lhz     r5, 2(r9)
/* 0C3A20 800C8FC0 A0C90000 */  lhz     r6, 0(r9)
/* 0C3A24 800C8FC4 80E90004 */  lwz     r7, 4(r9)
/* 0C3A28 800C8FC8 8109000C */  lwz     r8, 0xc(r9)
/* 0C3A2C 800C8FCC 81290010 */  lwz     r9, 0x10(r9)
/* 0C3A30 800C8FD0 4BFE37C9 */  bl      GXInitTexObj
/* 0C3A34 800C8FD4 813F0000 */  lwz     r9, 0(r31)
/* 0C3A38 800C8FD8 3CE04330 */  lis     r7, 0x4330
/* 0C3A3C 800C8FDC C8428538 */  lfd     f2, D_80136238@sda21(r2)
/* 0C3A40 800C8FE0 7FC3F378 */  mr      r3, r30
/* 0C3A44 800C8FE4 88890021 */  lbz     r4, 0x21(r9)
/* 0C3A48 800C8FE8 88090022 */  lbz     r0, 0x22(r9)
/* 0C3A4C 800C8FEC 38C00000 */  li      r6, 0
/* 0C3A50 800C8FF0 90810024 */  stw     r4, 0x24(r1)
/* 0C3A54 800C8FF4 39000000 */  li      r8, 0
/* 0C3A58 800C8FF8 80890014 */  lwz     r4, 0x14(r9)
/* 0C3A5C 800C8FFC 9001001C */  stw     r0, 0x1c(r1)
/* 0C3A60 800C9000 80A90018 */  lwz     r5, 0x18(r9)
/* 0C3A64 800C9004 90E10020 */  stw     r7, 0x20(r1)
/* 0C3A68 800C9008 C069001C */  lfs     f3, 0x1c(r9)
/* 0C3A6C 800C900C 90E10018 */  stw     r7, 0x18(r1)
/* 0C3A70 800C9010 C8210020 */  lfd     f1, 0x20(r1)
/* 0C3A74 800C9014 C8010018 */  lfd     f0, 0x18(r1)
/* 0C3A78 800C9018 EC211028 */  fsubs   f1, f1, f2
/* 0C3A7C 800C901C 88E90020 */  lbz     r7, 0x20(r9)
/* 0C3A80 800C9020 EC401028 */  fsubs   f2, f0, f2
/* 0C3A84 800C9024 4BFE3A09 */  bl      GXInitTexObjLOD
/* 0C3A88 800C9028 80010034 */  lwz     r0, 0x34(r1)
/* 0C3A8C 800C902C 83E1002C */  lwz     r31, 0x2c(r1)
/* 0C3A90 800C9030 83C10028 */  lwz     r30, 0x28(r1)
/* 0C3A94 800C9034 38210030 */  addi    r1, r1, 0x30
/* 0C3A98 800C9038 7C0803A6 */  mtlr    r0
/* 0C3A9C 800C903C 4E800020 */  blr     

.section .sdata2, "wa"

.balign 8

/* 000F1D38 80136238 0008 */
D_80136238:
    .double 4503599627370496.0
