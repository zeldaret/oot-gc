glabel cpuCompile_LWL
/* 062F54 800684F4 7C0802A6 */  mflr    r0
/* 062F58 800684F8 90010004 */  stw     r0, 4(r1)
/* 062F5C 800684FC 3800000C */  li      r0, 0xc
/* 062F60 80068500 5400103A */  slwi    r0, r0, 2
/* 062F64 80068504 9421FFE0 */  stwu    r1, -0x20(r1)
/* 062F68 80068508 93E1001C */  stw     r31, 0x1c(r1)
/* 062F6C 8006850C 3BE40000 */  addi    r31, r4, 0
/* 062F70 80068510 38610010 */  addi    r3, r1, 0x10
/* 062F74 80068514 64043000 */  oris    r4, r0, 0x3000
/* 062F78 80068518 4BF9EC9D */  bl      xlHeapTake
/* 062F7C 8006851C 2C030000 */  cmpwi   r3, 0
/* 062F80 80068520 4082000C */  bne     lbl_8006852C
/* 062F84 80068524 38600000 */  li      r3, 0
/* 062F88 80068528 48000148 */  b       lbl_80068670
lbl_8006852C:
/* 062F8C 8006852C 80010010 */  lwz     r0, 0x10(r1)
/* 062F90 80068530 3CC07D29 */  lis     r6, 0x7d29
/* 062F94 80068534 3CE038C0 */  lis     r7, 0x38c0
/* 062F98 80068538 901F0000 */  stw     r0, 0(r31)
/* 062F9C 8006853C 38000000 */  li      r0, 0
/* 062FA0 80068540 38600001 */  li      r3, 1
/* 062FA4 80068544 80810010 */  lwz     r4, 0x10(r1)
/* 062FA8 80068548 3CA07CA5 */  lis     r5, 0x7ca5
/* 062FAC 8006854C 38E70018 */  addi    r7, r7, 0x18
/* 062FB0 80068550 5400103A */  slwi    r0, r0, 2
/* 062FB4 80068554 7CE4012E */  stwx    r7, r4, r0
/* 062FB8 80068558 38000002 */  li      r0, 2
/* 062FBC 8006855C 3CE03940 */  lis     r7, 0x3940
/* 062FC0 80068560 80810010 */  lwz     r4, 0x10(r1)
/* 062FC4 80068564 5463103A */  slwi    r3, r3, 2
/* 062FC8 80068568 3D0088A7 */  lis     r8, 0x88a7
/* 062FCC 8006856C 7D04192E */  stwx    r8, r4, r3
/* 062FD0 80068570 38800003 */  li      r4, 3
/* 062FD4 80068574 3D007D4A */  lis     r8, 0x7d4a
/* 062FD8 80068578 80610010 */  lwz     r3, 0x10(r1)
/* 062FDC 8006857C 38A53030 */  addi    r5, r5, 0x3030
/* 062FE0 80068580 5400103A */  slwi    r0, r0, 2
/* 062FE4 80068584 7CA3012E */  stwx    r5, r3, r0
/* 062FE8 80068588 38600004 */  li      r3, 4
/* 062FEC 8006858C 38000005 */  li      r0, 5
/* 062FF0 80068590 80A10010 */  lwz     r5, 0x10(r1)
/* 062FF4 80068594 38E700FF */  addi    r7, r7, 0xff
/* 062FF8 80068598 5484103A */  slwi    r4, r4, 2
/* 062FFC 8006859C 7CE5212E */  stwx    r7, r5, r4
/* 063000 800685A0 38800006 */  li      r4, 6
/* 063004 800685A4 3CE038C7 */  lis     r7, 0x38c7
/* 063008 800685A8 80A10010 */  lwz     r5, 0x10(r1)
/* 06300C 800685AC 39083030 */  addi    r8, r8, 0x3030
/* 063010 800685B0 5463103A */  slwi    r3, r3, 2
/* 063014 800685B4 7D05192E */  stwx    r8, r5, r3
/* 063018 800685B8 38600007 */  li      r3, 7
/* 06301C 800685BC 3D2054E5 */  lis     r9, 0x54e5
/* 063020 800685C0 80A10010 */  lwz     r5, 0x10(r1)
/* 063024 800685C4 39065078 */  addi    r8, r6, 0x5078
/* 063028 800685C8 5400103A */  slwi    r0, r0, 2
/* 06302C 800685CC 7D05012E */  stwx    r8, r5, r0
/* 063030 800685D0 38000008 */  li      r0, 8
/* 063034 800685D4 3D0038E7 */  lis     r8, 0x38e7
/* 063038 800685D8 80A10010 */  lwz     r5, 0x10(r1)
/* 06303C 800685DC 38C62B78 */  addi    r6, r6, 0x2b78
/* 063040 800685E0 5484103A */  slwi    r4, r4, 2
/* 063044 800685E4 7CC5212E */  stwx    r6, r5, r4
/* 063048 800685E8 38C00009 */  li      r6, 9
/* 06304C 800685EC 3CA04083 */  lis     r5, 0x4083
/* 063050 800685F0 80810010 */  lwz     r4, 0x10(r1)
/* 063054 800685F4 38E7FFF8 */  addi    r7, r7, -8
/* 063058 800685F8 5463103A */  slwi    r3, r3, 2
/* 06305C 800685FC 7CE4192E */  stwx    r7, r4, r3
/* 063060 80068600 3880000A */  li      r4, 0xa
/* 063064 80068604 3C604E80 */  lis     r3, 0x4e80
/* 063068 80068608 80E10010 */  lwz     r7, 0x10(r1)
/* 06306C 8006860C 392907BF */  addi    r9, r9, 0x7bf
/* 063070 80068610 5400103A */  slwi    r0, r0, 2
/* 063074 80068614 7D27012E */  stwx    r9, r7, r0
/* 063078 80068618 3800000B */  li      r0, 0xb
/* 06307C 8006861C 3920000C */  li      r9, 0xc
/* 063080 80068620 80E10010 */  lwz     r7, 0x10(r1)
/* 063084 80068624 39080001 */  addi    r8, r8, 1
/* 063088 80068628 54C6103A */  slwi    r6, r6, 2
/* 06308C 8006862C 7D07312E */  stwx    r8, r7, r6
/* 063090 80068630 553F103A */  slwi    r31, r9, 2
/* 063094 80068634 38E5FFDC */  addi    r7, r5, -36
/* 063098 80068638 80C10010 */  lwz     r6, 0x10(r1)
/* 06309C 8006863C 5484103A */  slwi    r4, r4, 2
/* 0630A0 80068640 38A30020 */  addi    r5, r3, 0x20
/* 0630A4 80068644 7CE6212E */  stwx    r7, r6, r4
/* 0630A8 80068648 5400103A */  slwi    r0, r0, 2
/* 0630AC 8006864C 389F0000 */  addi    r4, r31, 0
/* 0630B0 80068650 80610010 */  lwz     r3, 0x10(r1)
/* 0630B4 80068654 7CA3012E */  stwx    r5, r3, r0
/* 0630B8 80068658 80610010 */  lwz     r3, 0x10(r1)
/* 0630BC 8006865C 48035151 */  bl      DCStoreRange
/* 0630C0 80068660 80610010 */  lwz     r3, 0x10(r1)
/* 0630C4 80068664 7FE4FB78 */  mr      r4, r31
/* 0630C8 80068668 480351CD */  bl      ICInvalidateRange
/* 0630CC 8006866C 38600001 */  li      r3, 1
lbl_80068670:
/* 0630D0 80068670 80010024 */  lwz     r0, 0x24(r1)
/* 0630D4 80068674 83E1001C */  lwz     r31, 0x1c(r1)
/* 0630D8 80068678 38210020 */  addi    r1, r1, 0x20
/* 0630DC 8006867C 7C0803A6 */  mtlr    r0
/* 0630E0 80068680 4E800020 */  blr     
