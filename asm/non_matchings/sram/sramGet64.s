glabel sramGet64
/* 088C98 8008E238 7C0802A6 */  mflr    r0
/* 088C9C 8008E23C 5483047E */  clrlwi  r3, r4, 0x11
/* 088CA0 8008E240 90010004 */  stw     r0, 4(r1)
/* 088CA4 8008E244 38850000 */  addi    r4, r5, 0
/* 088CA8 8008E248 38A00008 */  li      r5, 8
/* 088CAC 8008E24C 9421FFF8 */  stwu    r1, -8(r1)
/* 088CB0 8008E250 4BF7AC59 */  bl      simulatorReadSRAM
/* 088CB4 8008E254 8001000C */  lwz     r0, 0xc(r1)
/* 088CB8 8008E258 38600001 */  li      r3, 1
/* 088CBC 8008E25C 38210008 */  addi    r1, r1, 8
/* 088CC0 8008E260 7C0803A6 */  mtlr    r0
/* 088CC4 8008E264 4E800020 */  blr     
