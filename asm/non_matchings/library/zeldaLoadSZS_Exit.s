glabel zeldaLoadSZS_Exit
/* 08B510 80090AB0 8083012C */  lwz     r4, 0x12c(r3)
/* 08B514 80090AB4 38040040 */  addi    r0, r4, 0x40
/* 08B518 80090AB8 9003012C */  stw     r0, 0x12c(r3)
/* 08B51C 80090ABC 38600001 */  li      r3, 1
/* 08B520 80090AC0 4E800020 */  blr     
