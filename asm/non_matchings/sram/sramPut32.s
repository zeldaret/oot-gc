glabel sramPut32
/* 088D88 8008E328 7C0802A6 */  mflr    r0
/* 088D8C 8008E32C 5483047E */  clrlwi  r3, r4, 0x11
/* 088D90 8008E330 90010004 */  stw     r0, 4(r1)
/* 088D94 8008E334 38850000 */  addi    r4, r5, 0
/* 088D98 8008E338 38A00004 */  li      r5, 4
/* 088D9C 8008E33C 9421FFF8 */  stwu    r1, -8(r1)
/* 088DA0 8008E340 4BF7AB35 */  bl      simulatorWriteSRAM
/* 088DA4 8008E344 8001000C */  lwz     r0, 0xc(r1)
/* 088DA8 8008E348 38600001 */  li      r3, 1
/* 088DAC 8008E34C 38210008 */  addi    r1, r1, 8
/* 088DB0 8008E350 7C0803A6 */  mtlr    r0
/* 088DB4 8008E354 4E800020 */  blr     
