glabel ReadThreadStart
/* 00C58C 80011B2C 7C0802A6 */  mflr    r0
/* 00C590 80011B30 90010004 */  stw     r0, 4(r1)
/* 00C594 80011B34 9421FFF8 */  stwu    r1, -8(r1)
/* 00C598 80011B38 800D8960 */  lwz     r0, ReadThreadCreated@sda21(r13)
/* 00C59C 80011B3C 2C000000 */  cmpwi   r0, 0
/* 00C5A0 80011B40 41820010 */  beq     lbl_80011B50
/* 00C5A4 80011B44 3C608010 */  lis     r3, ReadThread@ha
/* 00C5A8 80011B48 3863B298 */  addi    r3, r3, ReadThread@l
/* 00C5AC 80011B4C 480900C9 */  bl      OSResumeThread
lbl_80011B50:
/* 00C5B0 80011B50 8001000C */  lwz     r0, 0xc(r1)
/* 00C5B4 80011B54 38210008 */  addi    r1, r1, 8
/* 00C5B8 80011B58 7C0803A6 */  mtlr    r0
/* 00C5BC 80011B5C 4E800020 */  blr     
