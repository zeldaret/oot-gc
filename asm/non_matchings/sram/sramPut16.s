glabel sramPut16
/* 088DB8 8008E358 7C0802A6 */  mflr    r0
/* 088DBC 8008E35C 5483047E */  clrlwi  r3, r4, 0x11
/* 088DC0 8008E360 90010004 */  stw     r0, 4(r1)
/* 088DC4 8008E364 38850000 */  addi    r4, r5, 0
/* 088DC8 8008E368 38A00002 */  li      r5, 2
/* 088DCC 8008E36C 9421FFF8 */  stwu    r1, -8(r1)
/* 088DD0 8008E370 4BF7AB05 */  bl      simulatorWriteSRAM
/* 088DD4 8008E374 8001000C */  lwz     r0, 0xc(r1)
/* 088DD8 8008E378 38600001 */  li      r3, 1
/* 088DDC 8008E37C 38210008 */  addi    r1, r1, 8
/* 088DE0 8008E380 7C0803A6 */  mtlr    r0
/* 088DE4 8008E384 4E800020 */  blr     
