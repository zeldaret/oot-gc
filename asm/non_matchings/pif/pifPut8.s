glabel pifPut8
/* 067310 8006C8B0 5486057E */  clrlwi  r6, r4, 0x15
/* 067314 8006C8B4 280607C0 */  cmplwi  r6, 0x7c0
/* 067318 8006C8B8 41800014 */  blt     lbl_8006C8CC
/* 06731C 8006C8BC 88850000 */  lbz     r4, 0(r5)
/* 067320 8006C8C0 3806F840 */  addi    r0, r6, -1984
/* 067324 8006C8C4 80630004 */  lwz     r3, 4(r3)
/* 067328 8006C8C8 7C8301AE */  stbx    r4, r3, r0
lbl_8006C8CC:
/* 06732C 8006C8CC 38600001 */  li      r3, 1
/* 067330 8006C8D0 4E800020 */  blr     
