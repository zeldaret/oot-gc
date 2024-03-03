glabel PushDecodedAudioBuffer
/* 00BB68 80011108 7C0802A6 */  mflr    r0
/* 00BB6C 8001110C 3CA08010 */  lis     r5, DecodedAudioBufferQueue@ha
/* 00BB70 80011110 90010004 */  stw     r0, 4(r1)
/* 00BB74 80011114 38830000 */  addi    r4, r3, 0
/* 00BB78 80011118 3865B188 */  addi    r3, r5, DecodedAudioBufferQueue@l
/* 00BB7C 8001111C 9421FFF8 */  stwu    r1, -8(r1)
/* 00BB80 80011120 38A00001 */  li      r5, 1
/* 00BB84 80011124 4808E4BD */  bl      OSSendMessage
/* 00BB88 80011128 8001000C */  lwz     r0, 0xc(r1)
/* 00BB8C 8001112C 38210008 */  addi    r1, r1, 8
/* 00BB90 80011130 7C0803A6 */  mtlr    r0
/* 00BB94 80011134 4E800020 */  blr     
