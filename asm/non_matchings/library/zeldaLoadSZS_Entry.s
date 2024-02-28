glabel zeldaLoadSZS_Entry
/* 08B524 80090AC4 8083012C */  lwz     r4, 0x12c(r3)
/* 08B528 80090AC8 3804FFC0 */  addi    r0, r4, -64
/* 08B52C 80090ACC 9003012C */  stw     r0, 0x12c(r3)
/* 08B530 80090AD0 38600001 */  li      r3, 1
/* 08B534 80090AD4 4E800020 */  blr     
