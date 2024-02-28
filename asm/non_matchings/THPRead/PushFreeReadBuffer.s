glabel PushFreeReadBuffer
/* 00C3FC 8001199C 7C0802A6 */  mflr    r0
/* 00C400 800119A0 3CA08010 */  lis     r5, FreeReadBufferQueue@ha
/* 00C404 800119A4 90010004 */  stw     r0, 4(r1)
/* 00C408 800119A8 38830000 */  addi    r4, r3, 0
/* 00C40C 800119AC 3865B1C0 */  addi    r3, r5, FreeReadBufferQueue@l
/* 00C410 800119B0 9421FFF8 */  stwu    r1, -8(r1)
/* 00C414 800119B4 38A00001 */  li      r5, 1
/* 00C418 800119B8 4808DC29 */  bl      OSSendMessage
/* 00C41C 800119BC 8001000C */  lwz     r0, 0xc(r1)
/* 00C420 800119C0 38210008 */  addi    r1, r1, 8
/* 00C424 800119C4 7C0803A6 */  mtlr    r0
/* 00C428 800119C8 4E800020 */  blr     
