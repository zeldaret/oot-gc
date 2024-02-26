glabel PushUsedTextureSet
/* 00B248 800107E8 7C0802A6 */  mflr    r0
/* 00B24C 800107EC 3CA08010 */  lis     r5, UsedTextureSetQueue@ha
/* 00B250 800107F0 90010004 */  stw     r0, 4(r1)
/* 00B254 800107F4 38830000 */  addi    r4, r3, 0
/* 00B258 800107F8 38659740 */  addi    r3, r5, UsedTextureSetQueue@l
/* 00B25C 800107FC 9421FFF8 */  stwu    r1, -8(r1)
/* 00B260 80010800 38A00000 */  li      r5, 0
/* 00B264 80010804 4808EDDD */  bl      OSSendMessage
/* 00B268 80010808 8001000C */  lwz     r0, 0xc(r1)
/* 00B26C 8001080C 38210008 */  addi    r1, r1, 8
/* 00B270 80010810 7C0803A6 */  mtlr    r0
/* 00B274 80010814 4E800020 */  blr     
