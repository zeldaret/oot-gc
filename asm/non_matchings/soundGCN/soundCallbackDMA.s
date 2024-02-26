glabel soundCallbackDMA
/* 017704 8001CCA4 7C0802A6 */  mflr    r0
/* 017708 8001CCA8 90010004 */  stw     r0, 4(r1)
/* 01770C 8001CCAC 9421FFF8 */  stwu    r1, -8(r1)
/* 017710 8001CCB0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 017714 8001CCB4 80630004 */  lwz     r3, 4(r3)
/* 017718 8001CCB8 48000015 */  bl      soundPlayBuffer
/* 01771C 8001CCBC 8001000C */  lwz     r0, 0xc(r1)
/* 017720 8001CCC0 38210008 */  addi    r1, r1, 8
/* 017724 8001CCC4 7C0803A6 */  mtlr    r0
/* 017728 8001CCC8 4E800020 */  blr     
