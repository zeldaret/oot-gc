glabel simulatorPlayMovie
/* 009700 8000ECA0 7C0802A6 */  mflr    r0
/* 009704 8000ECA4 90010004 */  stw     r0, 4(r1)
/* 009708 8000ECA8 9421FFF8 */  stwu    r1, -8(r1)
/* 00970C 8000ECAC 4BFFAB79 */  bl      simulatorResetAndPlayMovie
/* 009710 8000ECB0 8001000C */  lwz     r0, 0xc(r1)
/* 009714 8000ECB4 38600001 */  li      r3, 1
/* 009718 8000ECB8 38210008 */  addi    r1, r1, 8
/* 00971C 8000ECBC 7C0803A6 */  mtlr    r0
/* 009720 8000ECC0 4E800020 */  blr     
