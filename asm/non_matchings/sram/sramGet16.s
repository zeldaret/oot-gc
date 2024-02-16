glabel sramGet16
/* 088CF8 8008E298 7C0802A6 */  mflr    r0
/* 088CFC 8008E29C 5483047E */  clrlwi  r3, r4, 0x11
/* 088D00 8008E2A0 90010004 */  stw     r0, 4(r1)
/* 088D04 8008E2A4 38850000 */  addi    r4, r5, 0
/* 088D08 8008E2A8 38A00002 */  li      r5, 2
/* 088D0C 8008E2AC 9421FFF8 */  stwu    r1, -8(r1)
/* 088D10 8008E2B0 4BF7ABF9 */  bl      simulatorReadSRAM
/* 088D14 8008E2B4 8001000C */  lwz     r0, 0xc(r1)
/* 088D18 8008E2B8 38600001 */  li      r3, 1
/* 088D1C 8008E2BC 38210008 */  addi    r1, r1, 8
/* 088D20 8008E2C0 7C0803A6 */  mtlr    r0
/* 088D24 8008E2C4 4E800020 */  blr     
