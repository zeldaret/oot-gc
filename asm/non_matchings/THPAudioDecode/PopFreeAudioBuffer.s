glabel PopFreeAudioBuffer
/* 00BAC0 80011060 7C0802A6 */  mflr    r0
/* 00BAC4 80011064 3C608010 */  lis     r3, FreeAudioBufferQueue@ha
/* 00BAC8 80011068 90010004 */  stw     r0, 4(r1)
/* 00BACC 8001106C 3863B168 */  addi    r3, r3, FreeAudioBufferQueue@l
/* 00BAD0 80011070 38A00001 */  li      r5, 1
/* 00BAD4 80011074 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00BAD8 80011078 38810008 */  addi    r4, r1, 8
/* 00BADC 8001107C 4808E62D */  bl      OSReceiveMessage
/* 00BAE0 80011080 80010014 */  lwz     r0, 0x14(r1)
/* 00BAE4 80011084 80610008 */  lwz     r3, 8(r1)
/* 00BAE8 80011088 38210010 */  addi    r1, r1, 0x10
/* 00BAEC 8001108C 7C0803A6 */  mtlr    r0
/* 00BAF0 80011090 4E800020 */  blr     
