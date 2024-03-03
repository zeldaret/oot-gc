glabel PopFreeTextureSet
/* 00DDC8 80013368 7C0802A6 */  mflr    r0
/* 00DDCC 8001336C 3C608010 */  lis     r3, FreeTextureSetQueue@ha
/* 00DDD0 80013370 90010004 */  stw     r0, 4(r1)
/* 00DDD4 80013374 3863D908 */  addi    r3, r3, FreeTextureSetQueue@l
/* 00DDD8 80013378 38A00001 */  li      r5, 1
/* 00DDDC 8001337C 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00DDE0 80013380 38810008 */  addi    r4, r1, 8
/* 00DDE4 80013384 4808C325 */  bl      OSReceiveMessage
/* 00DDE8 80013388 80010014 */  lwz     r0, 0x14(r1)
/* 00DDEC 8001338C 80610008 */  lwz     r3, 8(r1)
/* 00DDF0 80013390 38210010 */  addi    r1, r1, 0x10
/* 00DDF4 80013394 7C0803A6 */  mtlr    r0
/* 00DDF8 80013398 4E800020 */  blr     
