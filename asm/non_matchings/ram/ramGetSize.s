glabel ramGetSize
/* 067A30 8006CFD0 28040000 */  cmplwi  r4, 0
/* 067A34 8006CFD4 4182000C */  beq     lbl_8006CFE0
/* 067A38 8006CFD8 80030008 */  lwz     r0, 8(r3)
/* 067A3C 8006CFDC 90040000 */  stw     r0, 0(r4)
lbl_8006CFE0:
/* 067A40 8006CFE0 38600001 */  li      r3, 1
/* 067A44 8006CFE4 4E800020 */  blr     
