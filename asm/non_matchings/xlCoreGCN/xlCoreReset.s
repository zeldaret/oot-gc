glabel xlCoreReset
/* 000828 80005DC8 7C0802A6 */  mflr    r0
/* 00082C 80005DCC 90010004 */  stw     r0, 4(r1)
/* 000830 80005DD0 9421FFF8 */  stwu    r1, -8(r1)
/* 000834 80005DD4 806D8740 */  lwz     r3, __OSCurrHeap@sda21(r13)
/* 000838 80005DD8 808D88B0 */  lwz     r4, gpHeap@sda21(r13)
/* 00083C 80005DDC 480971E5 */  bl      OSFreeToHeap
/* 000840 80005DE0 806D88B8 */  lwz     r3, gArenaLo@sda21(r13)
/* 000844 80005DE4 480976BD */  bl      OSSetArenaLo
/* 000848 80005DE8 806D88B4 */  lwz     r3, gArenaHi@sda21(r13)
/* 00084C 80005DEC 480976AD */  bl      OSSetArenaHi
/* 000850 80005DF0 8001000C */  lwz     r0, 0xc(r1)
/* 000854 80005DF4 38600001 */  li      r3, 1
/* 000858 80005DF8 38210008 */  addi    r1, r1, 8
/* 00085C 80005DFC 7C0803A6 */  mtlr    r0
/* 000860 80005E00 4E800020 */  blr     
