glabel sramGet8
/* 088D28 8008E2C8 7C0802A6 */  mflr    r0
/* 088D2C 8008E2CC 5483047E */  clrlwi  r3, r4, 0x11
/* 088D30 8008E2D0 90010004 */  stw     r0, 4(r1)
/* 088D34 8008E2D4 38850000 */  addi    r4, r5, 0
/* 088D38 8008E2D8 38A00001 */  li      r5, 1
/* 088D3C 8008E2DC 9421FFF8 */  stwu    r1, -8(r1)
/* 088D40 8008E2E0 4BF7ABC9 */  bl      simulatorReadSRAM
/* 088D44 8008E2E4 8001000C */  lwz     r0, 0xc(r1)
/* 088D48 8008E2E8 38600001 */  li      r3, 1
/* 088D4C 8008E2EC 38210008 */  addi    r1, r1, 8
/* 088D50 8008E2F0 7C0803A6 */  mtlr    r0
/* 088D54 8008E2F4 4E800020 */  blr     
