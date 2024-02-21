glabel simulatorRumbleStop
/* 00381C 80008DBC 7C0802A6 */  mflr    r0
/* 003820 80008DC0 38800000 */  li      r4, 0
/* 003824 80008DC4 90010004 */  stw     r0, 4(r1)
/* 003828 80008DC8 9421FFF8 */  stwu    r1, -8(r1)
/* 00382C 80008DCC 480A8065 */  bl      PADControlMotor
/* 003830 80008DD0 8001000C */  lwz     r0, 0xc(r1)
/* 003834 80008DD4 38600001 */  li      r3, 1
/* 003838 80008DD8 38210008 */  addi    r1, r1, 8
/* 00383C 80008DDC 7C0803A6 */  mtlr    r0
/* 003840 80008DE0 4E800020 */  blr     
