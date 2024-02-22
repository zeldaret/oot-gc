glabel simulatorReadFLASH
/* 0038A0 80008E40 7C0802A6 */  mflr    r0
/* 0038A4 80008E44 38C40000 */  addi    r6, r4, 0
/* 0038A8 80008E48 90010004 */  stw     r0, 4(r1)
/* 0038AC 80008E4C 3CE08010 */  lis     r7, mCard@ha
/* 0038B0 80008E50 38830000 */  addi    r4, r3, 0
/* 0038B4 80008E54 9421FFF8 */  stwu    r1, -8(r1)
/* 0038B8 80008E58 386779B0 */  addi    r3, r7, mCard@l
/* 0038BC 80008E5C 4800E9B9 */  bl      mcardRead
/* 0038C0 80008E60 8001000C */  lwz     r0, 0xc(r1)
/* 0038C4 80008E64 38600001 */  li      r3, 1
/* 0038C8 80008E68 38210008 */  addi    r1, r1, 8
/* 0038CC 80008E6C 7C0803A6 */  mtlr    r0
/* 0038D0 80008E70 4E800020 */  blr     
