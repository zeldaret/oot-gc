glabel simulatorWriteSRAM
/* 0038D4 80008E74 7C0802A6 */  mflr    r0
/* 0038D8 80008E78 38C40000 */  addi    r6, r4, 0
/* 0038DC 80008E7C 90010004 */  stw     r0, 4(r1)
/* 0038E0 80008E80 3CE08010 */  lis     r7, mCard@ha
/* 0038E4 80008E84 38830000 */  addi    r4, r3, 0
/* 0038E8 80008E88 9421FFF8 */  stwu    r1, -8(r1)
/* 0038EC 80008E8C 386779B0 */  addi    r3, r7, mCard@l
/* 0038F0 80008E90 4800DAC1 */  bl      mcardWrite
/* 0038F4 80008E94 8001000C */  lwz     r0, 0xc(r1)
/* 0038F8 80008E98 38600001 */  li      r3, 1
/* 0038FC 80008E9C 38210008 */  addi    r1, r1, 8
/* 003900 80008EA0 7C0803A6 */  mtlr    r0
/* 003904 80008EA4 4E800020 */  blr     
