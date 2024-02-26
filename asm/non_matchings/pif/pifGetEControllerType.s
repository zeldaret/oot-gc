glabel pifGetEControllerType
/* 0673DC 8006C97C 5480103A */  slwi    r0, r4, 2
/* 0673E0 8006C980 7C630214 */  add     r3, r3, r0
/* 0673E4 8006C984 8003001C */  lwz     r0, 0x1c(r3)
/* 0673E8 8006C988 38600001 */  li      r3, 1
/* 0673EC 8006C98C 90050000 */  stw     r0, 0(r5)
/* 0673F0 8006C990 4E800020 */  blr     
