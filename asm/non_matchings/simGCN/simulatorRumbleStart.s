glabel simulatorRumbleStart
/* 003844 80008DE4 7C0802A6 */  mflr    r0
/* 003848 80008DE8 38800001 */  li      r4, 1
/* 00384C 80008DEC 90010004 */  stw     r0, 4(r1)
/* 003850 80008DF0 9421FFF8 */  stwu    r1, -8(r1)
/* 003854 80008DF4 480A803D */  bl      PADControlMotor
/* 003858 80008DF8 8001000C */  lwz     r0, 0xc(r1)
/* 00385C 80008DFC 38600001 */  li      r3, 1
/* 003860 80008E00 38210008 */  addi    r1, r1, 8
/* 003864 80008E04 7C0803A6 */  mtlr    r0
/* 003868 80008E08 4E800020 */  blr     
