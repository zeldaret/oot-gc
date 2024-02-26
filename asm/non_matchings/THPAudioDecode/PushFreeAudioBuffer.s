glabel PushFreeAudioBuffer
/* 00BAF4 80011094 7C0802A6 */  mflr    r0
/* 00BAF8 80011098 3CA08010 */  lis     r5, FreeAudioBufferQueue@ha
/* 00BAFC 8001109C 90010004 */  stw     r0, 4(r1)
/* 00BB00 800110A0 38830000 */  addi    r4, r3, 0
/* 00BB04 800110A4 3865B168 */  addi    r3, r5, FreeAudioBufferQueue@l
/* 00BB08 800110A8 9421FFF8 */  stwu    r1, -8(r1)
/* 00BB0C 800110AC 38A00000 */  li      r5, 0
/* 00BB10 800110B0 4808E531 */  bl      OSSendMessage
/* 00BB14 800110B4 8001000C */  lwz     r0, 0xc(r1)
/* 00BB18 800110B8 38210008 */  addi    r1, r1, 8
/* 00BB1C 800110BC 7C0803A6 */  mtlr    r0
/* 00BB20 800110C0 4E800020 */  blr     
