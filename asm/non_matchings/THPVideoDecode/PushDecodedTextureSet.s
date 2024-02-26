glabel PushDecodedTextureSet
/* 00DE70 80013410 7C0802A6 */  mflr    r0
/* 00DE74 80013414 3CA08010 */  lis     r5, DecodedTextureSetQueue@ha
/* 00DE78 80013418 90010004 */  stw     r0, 4(r1)
/* 00DE7C 8001341C 38830000 */  addi    r4, r3, 0
/* 00DE80 80013420 3865D928 */  addi    r3, r5, DecodedTextureSetQueue@l
/* 00DE84 80013424 9421FFF8 */  stwu    r1, -8(r1)
/* 00DE88 80013428 38A00001 */  li      r5, 1
/* 00DE8C 8001342C 4808C1B5 */  bl      OSSendMessage
/* 00DE90 80013430 8001000C */  lwz     r0, 0xc(r1)
/* 00DE94 80013434 38210008 */  addi    r1, r1, 8
/* 00DE98 80013438 7C0803A6 */  mtlr    r0
/* 00DE9C 8001343C 4E800020 */  blr     
