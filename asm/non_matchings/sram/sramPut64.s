glabel sramPut64
/* 088D58 8008E2F8 7C0802A6 */  mflr    r0
/* 088D5C 8008E2FC 5483047E */  clrlwi  r3, r4, 0x11
/* 088D60 8008E300 90010004 */  stw     r0, 4(r1)
/* 088D64 8008E304 38850000 */  addi    r4, r5, 0
/* 088D68 8008E308 38A00008 */  li      r5, 8
/* 088D6C 8008E30C 9421FFF8 */  stwu    r1, -8(r1)
/* 088D70 8008E310 4BF7AB65 */  bl      simulatorWriteSRAM
/* 088D74 8008E314 8001000C */  lwz     r0, 0xc(r1)
/* 088D78 8008E318 38600001 */  li      r3, 1
/* 088D7C 8008E31C 38210008 */  addi    r1, r1, 8
/* 088D80 8008E320 7C0803A6 */  mtlr    r0
/* 088D84 8008E324 4E800020 */  blr     
