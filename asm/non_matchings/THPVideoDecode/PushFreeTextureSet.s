glabel PushFreeTextureSet
/* 00DDFC 8001339C 7C0802A6 */  mflr    r0
/* 00DE00 800133A0 3CA08010 */  lis     r5, FreeTextureSetQueue@ha
/* 00DE04 800133A4 90010004 */  stw     r0, 4(r1)
/* 00DE08 800133A8 38830000 */  addi    r4, r3, 0
/* 00DE0C 800133AC 3865D908 */  addi    r3, r5, FreeTextureSetQueue@l
/* 00DE10 800133B0 9421FFF8 */  stwu    r1, -8(r1)
/* 00DE14 800133B4 38A00000 */  li      r5, 0
/* 00DE18 800133B8 4808C229 */  bl      OSSendMessage
/* 00DE1C 800133BC 8001000C */  lwz     r0, 0xc(r1)
/* 00DE20 800133C0 38210008 */  addi    r1, r1, 8
/* 00DE24 800133C4 7C0803A6 */  mtlr    r0
/* 00DE28 800133C8 4E800020 */  blr     
