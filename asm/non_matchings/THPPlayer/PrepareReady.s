glabel PrepareReady
/* 00AA50 8000FFF0 7C0802A6 */  mflr    r0
/* 00AA54 8000FFF4 3CA08010 */  lis     r5, PrepareReadyQueue@ha
/* 00AA58 8000FFF8 90010004 */  stw     r0, 4(r1)
/* 00AA5C 8000FFFC 38830000 */  addi    r4, r3, 0
/* 00AA60 80010000 38659720 */  addi    r3, r5, PrepareReadyQueue@l
/* 00AA64 80010004 9421FFF8 */  stwu    r1, -8(r1)
/* 00AA68 80010008 38A00001 */  li      r5, 1
/* 00AA6C 8001000C 4808F5D5 */  bl      OSSendMessage
/* 00AA70 80010010 8001000C */  lwz     r0, 0xc(r1)
/* 00AA74 80010014 38210008 */  addi    r1, r1, 8
/* 00AA78 80010018 7C0803A6 */  mtlr    r0
/* 00AA7C 8001001C 4E800020 */  blr     
