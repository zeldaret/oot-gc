glabel ramWipe
/* 067AB8 8006D058 7C0802A6 */  mflr    r0
/* 067ABC 8006D05C 90010004 */  stw     r0, 4(r1)
/* 067AC0 8006D060 9421FFF8 */  stwu    r1, -8(r1)
/* 067AC4 8006D064 80830008 */  lwz     r4, 8(r3)
/* 067AC8 8006D068 28040000 */  cmplwi  r4, 0
/* 067ACC 8006D06C 41820020 */  beq     lbl_8006D08C
/* 067AD0 8006D070 80630004 */  lwz     r3, 4(r3)
/* 067AD4 8006D074 38A00000 */  li      r5, 0
/* 067AD8 8006D078 4BF99891 */  bl      xlHeapFill32
/* 067ADC 8006D07C 2C030000 */  cmpwi   r3, 0
/* 067AE0 8006D080 4082000C */  bne     lbl_8006D08C
/* 067AE4 8006D084 38600000 */  li      r3, 0
/* 067AE8 8006D088 48000008 */  b       lbl_8006D090
lbl_8006D08C:
/* 067AEC 8006D08C 38600001 */  li      r3, 1
lbl_8006D090:
/* 067AF0 8006D090 8001000C */  lwz     r0, 0xc(r1)
/* 067AF4 8006D094 38210008 */  addi    r1, r1, 8
/* 067AF8 8006D098 7C0803A6 */  mtlr    r0
/* 067AFC 8006D09C 4E800020 */  blr     
