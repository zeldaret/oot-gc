glabel romGet64
/* 068954 8006DEF4 7C0802A6 */  mflr    r0
/* 068958 8006DEF8 5484017E */  clrlwi  r4, r4, 5
/* 06895C 8006DEFC 90010004 */  stw     r0, 4(r1)
/* 068960 8006DF00 9421FFD8 */  stwu    r1, -0x28(r1)
/* 068964 8006DF04 93E10024 */  stw     r31, 0x24(r1)
/* 068968 8006DF08 3BE50000 */  addi    r31, r5, 0
/* 06896C 8006DF0C 80030214 */  lwz     r0, 0x214(r3)
/* 068970 8006DF10 7C040040 */  cmplw   r4, r0
/* 068974 8006DF14 40800038 */  bge     lbl_8006DF4C
/* 068978 8006DF18 38A40000 */  addi    r5, r4, 0
/* 06897C 8006DF1C 38810018 */  addi    r4, r1, 0x18
/* 068980 8006DF20 38C00008 */  li      r6, 8
/* 068984 8006DF24 38E00000 */  li      r7, 0
/* 068988 8006DF28 4BFFFCD1 */  bl      romCopy
/* 06898C 8006DF2C 2C030000 */  cmpwi   r3, 0
/* 068990 8006DF30 4182001C */  beq     lbl_8006DF4C
/* 068994 8006DF34 80010018 */  lwz     r0, 0x18(r1)
/* 068998 8006DF38 38600001 */  li      r3, 1
/* 06899C 8006DF3C 8081001C */  lwz     r4, 0x1c(r1)
/* 0689A0 8006DF40 909F0004 */  stw     r4, 4(r31)
/* 0689A4 8006DF44 901F0000 */  stw     r0, 0(r31)
/* 0689A8 8006DF48 48000014 */  b       lbl_8006DF5C
lbl_8006DF4C:
/* 0689AC 8006DF4C 38000000 */  li      r0, 0
/* 0689B0 8006DF50 901F0004 */  stw     r0, 4(r31)
/* 0689B4 8006DF54 38600001 */  li      r3, 1
/* 0689B8 8006DF58 901F0000 */  stw     r0, 0(r31)
lbl_8006DF5C:
/* 0689BC 8006DF5C 8001002C */  lwz     r0, 0x2c(r1)
/* 0689C0 8006DF60 83E10024 */  lwz     r31, 0x24(r1)
/* 0689C4 8006DF64 38210028 */  addi    r1, r1, 0x28
/* 0689C8 8006DF68 7C0803A6 */  mtlr    r0
/* 0689CC 8006DF6C 4E800020 */  blr     
