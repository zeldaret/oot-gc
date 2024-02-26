glabel PushReadedBuffer2
/* 00C398 80011938 7C0802A6 */  mflr    r0
/* 00C39C 8001193C 3CA08010 */  lis     r5, ReadedBufferQueue2@ha
/* 00C3A0 80011940 90010004 */  stw     r0, 4(r1)
/* 00C3A4 80011944 38830000 */  addi    r4, r3, 0
/* 00C3A8 80011948 3865B200 */  addi    r3, r5, ReadedBufferQueue2@l
/* 00C3AC 8001194C 9421FFF8 */  stwu    r1, -8(r1)
/* 00C3B0 80011950 38A00001 */  li      r5, 1
/* 00C3B4 80011954 4808DC8D */  bl      OSSendMessage
/* 00C3B8 80011958 8001000C */  lwz     r0, 0xc(r1)
/* 00C3BC 8001195C 38210008 */  addi    r1, r1, 8
/* 00C3C0 80011960 7C0803A6 */  mtlr    r0
/* 00C3C4 80011964 4E800020 */  blr     
