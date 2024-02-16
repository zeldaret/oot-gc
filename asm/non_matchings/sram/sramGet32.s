glabel sramGet32
/* 088CC8 8008E268 7C0802A6 */  mflr    r0
/* 088CCC 8008E26C 5483047E */  clrlwi  r3, r4, 0x11
/* 088CD0 8008E270 90010004 */  stw     r0, 4(r1)
/* 088CD4 8008E274 38850000 */  addi    r4, r5, 0
/* 088CD8 8008E278 38A00004 */  li      r5, 4
/* 088CDC 8008E27C 9421FFF8 */  stwu    r1, -8(r1)
/* 088CE0 8008E280 4BF7AC29 */  bl      simulatorReadSRAM
/* 088CE4 8008E284 8001000C */  lwz     r0, 0xc(r1)
/* 088CE8 8008E288 38600001 */  li      r3, 1
/* 088CEC 8008E28C 38210008 */  addi    r1, r1, 8
/* 088CF0 8008E290 7C0803A6 */  mtlr    r0
/* 088CF4 8008E294 4E800020 */  blr     
