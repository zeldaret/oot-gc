glabel simulatorReadSRAM
/* 003908 80008EA8 7C0802A6 */  mflr    r0
/* 00390C 80008EAC 38C40000 */  addi    r6, r4, 0
/* 003910 80008EB0 90010004 */  stw     r0, 4(r1)
/* 003914 80008EB4 3CE08010 */  lis     r7, mCard@ha
/* 003918 80008EB8 38830000 */  addi    r4, r3, 0
/* 00391C 80008EBC 9421FFF8 */  stwu    r1, -8(r1)
/* 003920 80008EC0 386779B0 */  addi    r3, r7, mCard@l
/* 003924 80008EC4 4800E951 */  bl      mcardRead
/* 003928 80008EC8 8001000C */  lwz     r0, 0xc(r1)
/* 00392C 80008ECC 38600001 */  li      r3, 1
/* 003930 80008ED0 38210008 */  addi    r1, r1, 8
/* 003934 80008ED4 7C0803A6 */  mtlr    r0
/* 003938 80008ED8 4E800020 */  blr     
