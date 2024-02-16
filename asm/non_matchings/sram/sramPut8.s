glabel sramPut8
/* 088DE8 8008E388 7C0802A6 */  mflr    r0
/* 088DEC 8008E38C 5483047E */  clrlwi  r3, r4, 0x11
/* 088DF0 8008E390 90010004 */  stw     r0, 4(r1)
/* 088DF4 8008E394 38850000 */  addi    r4, r5, 0
/* 088DF8 8008E398 38A00001 */  li      r5, 1
/* 088DFC 8008E39C 9421FFF8 */  stwu    r1, -8(r1)
/* 088E00 8008E3A0 4BF7AAD5 */  bl      simulatorWriteSRAM
/* 088E04 8008E3A4 8001000C */  lwz     r0, 0xc(r1)
/* 088E08 8008E3A8 38600001 */  li      r3, 1
/* 088E0C 8008E3AC 38210008 */  addi    r1, r1, 8
/* 088E10 8008E3B0 7C0803A6 */  mtlr    r0
/* 088E14 8008E3B4 4E800020 */  blr     
