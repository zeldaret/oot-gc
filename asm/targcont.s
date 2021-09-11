# targcont.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKTargetContinue
/* 0C81C4 800CD764 7C0802A6 */  mflr    r0
/* 0C81C8 800CD768 38600000 */  li      r3, 0
/* 0C81CC 800CD76C 90010004 */  stw     r0, 4(r1)
/* 0C81D0 800CD770 9421FFF8 */  stwu    r1, -8(r1)
/* 0C81D4 800CD774 4BFFF38D */  bl      TRKTargetSetStopped
/* 0C81D8 800CD778 4BFFFF99 */  bl      UnreserveEXI2Port
/* 0C81DC 800CD77C 4BFFED81 */  bl      TRKSwapAndGo
/* 0C81E0 800CD780 4BFFFF61 */  bl      ReserveEXI2Port
/* 0C81E4 800CD784 38600000 */  li      r3, 0
/* 0C81E8 800CD788 38210008 */  addi    r1, r1, 8
/* 0C81EC 800CD78C 80010004 */  lwz     r0, 4(r1)
/* 0C81F0 800CD790 7C0803A6 */  mtlr    r0
/* 0C81F4 800CD794 4E800020 */  blr     
