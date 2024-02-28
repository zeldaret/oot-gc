glabel soundSetDACRate
/* 0174C0 8001CA60 3CA002E7 */  lis     r5, 0x2e7
/* 0174C4 8001CA64 90830008 */  stw     r4, 8(r3)
/* 0174C8 8001CA68 38A5D354 */  addi    r5, r5, -11436
/* 0174CC 8001CA6C 38040001 */  addi    r0, r4, 1
/* 0174D0 8001CA70 7C0503D6 */  divw    r0, r5, r0
/* 0174D4 8001CA74 90030004 */  stw     r0, 4(r3)
/* 0174D8 8001CA78 38600001 */  li      r3, 1
/* 0174DC 8001CA7C 4E800020 */  blr     
