glabel ramGetRI32
/* 067CE4 8006D284 548006FE */  clrlwi  r0, r4, 0x1b
/* 067CE8 8006D288 2800001C */  cmplwi  r0, 0x1c
/* 067CEC 8006D28C 4181001C */  bgt     lbl_8006D2A8
/* 067CF0 8006D290 3C60800F */  lis     r3, jtbl_800ED6D8@ha
/* 067CF4 8006D294 3863D6D8 */  addi    r3, r3, jtbl_800ED6D8@l
/* 067CF8 8006D298 5400103A */  slwi    r0, r0, 2
/* 067CFC 8006D29C 7C03002E */  lwzx    r0, r3, r0
/* 067D00 8006D2A0 7C0903A6 */  mtctr   r0
/* 067D04 8006D2A4 4E800420 */  bctr    
glabel lbl_8006D2A8
/* 067D08 8006D2A8 38600000 */  li      r3, 0
/* 067D0C 8006D2AC 4E800020 */  blr     
glabel lbl_8006D2B0
/* 067D10 8006D2B0 38600001 */  li      r3, 1
/* 067D14 8006D2B4 4E800020 */  blr     
