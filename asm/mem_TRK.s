# mem_TRK.c
.include "macros.inc"

.section .init, "ax"

.balign 4

glabel TRK_memcpy
/* 000358 80003458 3884FFFF */  addi    r4, r4, -1
/* 00035C 8000345C 38C3FFFF */  addi    r6, r3, -1
/* 000360 80003460 38A50001 */  addi    r5, r5, 1
/* 000364 80003464 4800000C */  b       lbl_80003470
lbl_80003468:
/* 000368 80003468 8C040001 */  lbzu    r0, 1(r4)
/* 00036C 8000346C 9C060001 */  stbu    r0, 1(r6)
lbl_80003470:
/* 000370 80003470 34A5FFFF */  addic.  r5, r5, -1
/* 000374 80003474 4082FFF4 */  bne     lbl_80003468
/* 000378 80003478 4E800020 */  blr     


