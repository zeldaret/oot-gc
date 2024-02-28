glabel PopReadedBuffer
/* 00C42C 800119CC 7C0802A6 */  mflr    r0
/* 00C430 800119D0 3C608010 */  lis     r3, ReadedBufferQueue@ha
/* 00C434 800119D4 90010004 */  stw     r0, 4(r1)
/* 00C438 800119D8 3863B1E0 */  addi    r3, r3, ReadedBufferQueue@l
/* 00C43C 800119DC 38A00001 */  li      r5, 1
/* 00C440 800119E0 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00C444 800119E4 38810008 */  addi    r4, r1, 8
/* 00C448 800119E8 4808DCC1 */  bl      OSReceiveMessage
/* 00C44C 800119EC 80010014 */  lwz     r0, 0x14(r1)
/* 00C450 800119F0 80610008 */  lwz     r3, 8(r1)
/* 00C454 800119F4 38210010 */  addi    r1, r1, 0x10
/* 00C458 800119F8 7C0803A6 */  mtlr    r0
/* 00C45C 800119FC 4E800020 */  blr     
