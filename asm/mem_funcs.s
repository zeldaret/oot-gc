# mem_funcs.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __copy_longs_rev_unaligned
/* 0C94BC 800CEA5C 7D832A14 */  add     r12, r3, r5
/* 0C94C0 800CEA60 558007BF */  clrlwi. r0, r12, 0x1e
/* 0C94C4 800CEA64 7D642A14 */  add     r11, r4, r5
/* 0C94C8 800CEA68 7C030378 */  mr      r3, r0
/* 0C94CC 800CEA6C 41820018 */  beq     lbl_800CEA84
/* 0C94D0 800CEA70 7CA32850 */  subf    r5, r3, r5
lbl_800CEA74:
/* 0C94D4 800CEA74 8C0BFFFF */  lbzu    r0, -1(r11)
/* 0C94D8 800CEA78 3463FFFF */  addic.  r3, r3, -1
/* 0C94DC 800CEA7C 9C0CFFFF */  stbu    r0, -1(r12)
/* 0C94E0 800CEA80 4082FFF4 */  bne     lbl_800CEA74
lbl_800CEA84:
/* 0C94E4 800CEA84 55641EF8 */  rlwinm  r4, r11, 3, 0x1b, 0x1c
/* 0C94E8 800CEA88 556907BE */  clrlwi  r9, r11, 0x1e
/* 0C94EC 800CEA8C 21440020 */  subfic  r10, r4, 0x20
/* 0C94F0 800CEA90 20090004 */  subfic  r0, r9, 4
/* 0C94F4 800CEA94 7D6B0214 */  add     r11, r11, r0
/* 0C94F8 800CEA98 84EBFFFC */  lwzu    r7, -4(r11)
/* 0C94FC 800CEA9C 54A6E8FE */  srwi    r6, r5, 3
lbl_800CEAA0:
/* 0C9500 800CEAA0 810BFFFC */  lwz     r8, -4(r11)
/* 0C9504 800CEAA4 7CE05430 */  srw     r0, r7, r10
/* 0C9508 800CEAA8 34C6FFFF */  addic.  r6, r6, -1
/* 0C950C 800CEAAC 7D032030 */  slw     r3, r8, r4
/* 0C9510 800CEAB0 7C600378 */  or      r0, r3, r0
/* 0C9514 800CEAB4 900CFFFC */  stw     r0, -4(r12)
/* 0C9518 800CEAB8 7D005430 */  srw     r0, r8, r10
/* 0C951C 800CEABC 84EBFFF8 */  lwzu    r7, -8(r11)
/* 0C9520 800CEAC0 7CE32030 */  slw     r3, r7, r4
/* 0C9524 800CEAC4 7C600378 */  or      r0, r3, r0
/* 0C9528 800CEAC8 940CFFF8 */  stwu    r0, -8(r12)
/* 0C952C 800CEACC 4082FFD4 */  bne     lbl_800CEAA0
/* 0C9530 800CEAD0 54A0077B */  rlwinm. r0, r5, 0, 0x1d, 0x1d
/* 0C9534 800CEAD4 41820018 */  beq     lbl_800CEAEC
/* 0C9538 800CEAD8 846BFFFC */  lwzu    r3, -4(r11)
/* 0C953C 800CEADC 7CE05430 */  srw     r0, r7, r10
/* 0C9540 800CEAE0 7C632030 */  slw     r3, r3, r4
/* 0C9544 800CEAE4 7C600378 */  or      r0, r3, r0
/* 0C9548 800CEAE8 940CFFFC */  stwu    r0, -4(r12)
lbl_800CEAEC:
/* 0C954C 800CEAEC 54A507BF */  clrlwi. r5, r5, 0x1e
/* 0C9550 800CEAF0 4D820020 */  beqlr   
/* 0C9554 800CEAF4 7D6B4A14 */  add     r11, r11, r9
lbl_800CEAF8:
/* 0C9558 800CEAF8 8C0BFFFF */  lbzu    r0, -1(r11)
/* 0C955C 800CEAFC 34A5FFFF */  addic.  r5, r5, -1
/* 0C9560 800CEB00 9C0CFFFF */  stbu    r0, -1(r12)
/* 0C9564 800CEB04 4082FFF4 */  bne     lbl_800CEAF8
/* 0C9568 800CEB08 4E800020 */  blr     

glabel __copy_longs_unaligned
/* 0C956C 800CEB0C 7C0300D0 */  neg     r0, r3
/* 0C9570 800CEB10 540607BF */  clrlwi. r6, r0, 0x1e
/* 0C9574 800CEB14 3884FFFF */  addi    r4, r4, -1
/* 0C9578 800CEB18 3863FFFF */  addi    r3, r3, -1
/* 0C957C 800CEB1C 41820018 */  beq     lbl_800CEB34
/* 0C9580 800CEB20 7CA62850 */  subf    r5, r6, r5
lbl_800CEB24:
/* 0C9584 800CEB24 8C040001 */  lbzu    r0, 1(r4)
/* 0C9588 800CEB28 34C6FFFF */  addic.  r6, r6, -1
/* 0C958C 800CEB2C 9C030001 */  stbu    r0, 1(r3)
/* 0C9590 800CEB30 4082FFF4 */  bne     lbl_800CEB24
lbl_800CEB34:
/* 0C9594 800CEB34 38040001 */  addi    r0, r4, 1
/* 0C9598 800CEB38 540B07BE */  clrlwi  r11, r0, 0x1e
/* 0C959C 800CEB3C 7C8B2050 */  subf    r4, r11, r4
/* 0C95A0 800CEB40 3904FFFD */  addi    r8, r4, -3
/* 0C95A4 800CEB44 85280004 */  lwzu    r9, 4(r8)
/* 0C95A8 800CEB48 54041EF8 */  rlwinm  r4, r0, 3, 0x1b, 0x1c
/* 0C95AC 800CEB4C 21840020 */  subfic  r12, r4, 0x20
/* 0C95B0 800CEB50 38C3FFFD */  addi    r6, r3, -3
/* 0C95B4 800CEB54 54A7E8FE */  srwi    r7, r5, 3
lbl_800CEB58:
/* 0C95B8 800CEB58 81480004 */  lwz     r10, 4(r8)
/* 0C95BC 800CEB5C 7D232030 */  slw     r3, r9, r4
/* 0C95C0 800CEB60 34E7FFFF */  addic.  r7, r7, -1
/* 0C95C4 800CEB64 7D406430 */  srw     r0, r10, r12
/* 0C95C8 800CEB68 7C600378 */  or      r0, r3, r0
/* 0C95CC 800CEB6C 90060004 */  stw     r0, 4(r6)
/* 0C95D0 800CEB70 7D432030 */  slw     r3, r10, r4
/* 0C95D4 800CEB74 85280008 */  lwzu    r9, 8(r8)
/* 0C95D8 800CEB78 7D206430 */  srw     r0, r9, r12
/* 0C95DC 800CEB7C 7C600378 */  or      r0, r3, r0
/* 0C95E0 800CEB80 94060008 */  stwu    r0, 8(r6)
/* 0C95E4 800CEB84 4082FFD4 */  bne     lbl_800CEB58
/* 0C95E8 800CEB88 54A0077B */  rlwinm. r0, r5, 0, 0x1d, 0x1d
/* 0C95EC 800CEB8C 41820018 */  beq     lbl_800CEBA4
/* 0C95F0 800CEB90 84080004 */  lwzu    r0, 4(r8)
/* 0C95F4 800CEB94 7D232030 */  slw     r3, r9, r4
/* 0C95F8 800CEB98 7C006430 */  srw     r0, r0, r12
/* 0C95FC 800CEB9C 7C600378 */  or      r0, r3, r0
/* 0C9600 800CEBA0 94060004 */  stwu    r0, 4(r6)
lbl_800CEBA4:
/* 0C9604 800CEBA4 54A507BF */  clrlwi. r5, r5, 0x1e
/* 0C9608 800CEBA8 38880003 */  addi    r4, r8, 3
/* 0C960C 800CEBAC 38660003 */  addi    r3, r6, 3
/* 0C9610 800CEBB0 4D820020 */  beqlr   
/* 0C9614 800CEBB4 200B0004 */  subfic  r0, r11, 4
/* 0C9618 800CEBB8 7C802050 */  subf    r4, r0, r4
lbl_800CEBBC:
/* 0C961C 800CEBBC 8C040001 */  lbzu    r0, 1(r4)
/* 0C9620 800CEBC0 34A5FFFF */  addic.  r5, r5, -1
/* 0C9624 800CEBC4 9C030001 */  stbu    r0, 1(r3)
/* 0C9628 800CEBC8 4082FFF4 */  bne     lbl_800CEBBC
/* 0C962C 800CEBCC 4E800020 */  blr     

glabel __copy_longs_rev_aligned
/* 0C9630 800CEBD0 7CC32A14 */  add     r6, r3, r5
/* 0C9634 800CEBD4 54C007BF */  clrlwi. r0, r6, 0x1e
/* 0C9638 800CEBD8 7C842A14 */  add     r4, r4, r5
/* 0C963C 800CEBDC 7C030378 */  mr      r3, r0
/* 0C9640 800CEBE0 41820018 */  beq     lbl_800CEBF8
/* 0C9644 800CEBE4 7CA32850 */  subf    r5, r3, r5
lbl_800CEBE8:
/* 0C9648 800CEBE8 8C04FFFF */  lbzu    r0, -1(r4)
/* 0C964C 800CEBEC 3463FFFF */  addic.  r3, r3, -1
/* 0C9650 800CEBF0 9C06FFFF */  stbu    r0, -1(r6)
/* 0C9654 800CEBF4 4082FFF4 */  bne     lbl_800CEBE8
lbl_800CEBF8:
/* 0C9658 800CEBF8 54A3D97F */  rlwinm. r3, r5, 0x1b, 5, 0x1f
/* 0C965C 800CEBFC 4182004C */  beq     lbl_800CEC48
lbl_800CEC00:
/* 0C9660 800CEC00 8004FFFC */  lwz     r0, -4(r4)
/* 0C9664 800CEC04 3463FFFF */  addic.  r3, r3, -1
/* 0C9668 800CEC08 9006FFFC */  stw     r0, -4(r6)
/* 0C966C 800CEC0C 8004FFF8 */  lwz     r0, -8(r4)
/* 0C9670 800CEC10 9006FFF8 */  stw     r0, -8(r6)
/* 0C9674 800CEC14 8004FFF4 */  lwz     r0, -0xc(r4)
/* 0C9678 800CEC18 9006FFF4 */  stw     r0, -0xc(r6)
/* 0C967C 800CEC1C 8004FFF0 */  lwz     r0, -0x10(r4)
/* 0C9680 800CEC20 9006FFF0 */  stw     r0, -0x10(r6)
/* 0C9684 800CEC24 8004FFEC */  lwz     r0, -0x14(r4)
/* 0C9688 800CEC28 9006FFEC */  stw     r0, -0x14(r6)
/* 0C968C 800CEC2C 8004FFE8 */  lwz     r0, -0x18(r4)
/* 0C9690 800CEC30 9006FFE8 */  stw     r0, -0x18(r6)
/* 0C9694 800CEC34 8004FFE4 */  lwz     r0, -0x1c(r4)
/* 0C9698 800CEC38 9006FFE4 */  stw     r0, -0x1c(r6)
/* 0C969C 800CEC3C 8404FFE0 */  lwzu    r0, -0x20(r4)
/* 0C96A0 800CEC40 9406FFE0 */  stwu    r0, -0x20(r6)
/* 0C96A4 800CEC44 4082FFBC */  bne     lbl_800CEC00
lbl_800CEC48:
/* 0C96A8 800CEC48 54A3F77F */  rlwinm. r3, r5, 0x1e, 0x1d, 0x1f
/* 0C96AC 800CEC4C 41820014 */  beq     lbl_800CEC60
lbl_800CEC50:
/* 0C96B0 800CEC50 8404FFFC */  lwzu    r0, -4(r4)
/* 0C96B4 800CEC54 3463FFFF */  addic.  r3, r3, -1
/* 0C96B8 800CEC58 9406FFFC */  stwu    r0, -4(r6)
/* 0C96BC 800CEC5C 4082FFF4 */  bne     lbl_800CEC50
lbl_800CEC60:
/* 0C96C0 800CEC60 54A507BF */  clrlwi. r5, r5, 0x1e
/* 0C96C4 800CEC64 4D820020 */  beqlr   
lbl_800CEC68:
/* 0C96C8 800CEC68 8C04FFFF */  lbzu    r0, -1(r4)
/* 0C96CC 800CEC6C 34A5FFFF */  addic.  r5, r5, -1
/* 0C96D0 800CEC70 9C06FFFF */  stbu    r0, -1(r6)
/* 0C96D4 800CEC74 4082FFF4 */  bne     lbl_800CEC68
/* 0C96D8 800CEC78 4E800020 */  blr     

glabel __copy_longs_aligned
/* 0C96DC 800CEC7C 7C0300D0 */  neg     r0, r3
/* 0C96E0 800CEC80 540607BF */  clrlwi. r6, r0, 0x1e
/* 0C96E4 800CEC84 38E4FFFF */  addi    r7, r4, -1
/* 0C96E8 800CEC88 3863FFFF */  addi    r3, r3, -1
/* 0C96EC 800CEC8C 41820018 */  beq     lbl_800CECA4
/* 0C96F0 800CEC90 7CA62850 */  subf    r5, r6, r5
lbl_800CEC94:
/* 0C96F4 800CEC94 8C070001 */  lbzu    r0, 1(r7)
/* 0C96F8 800CEC98 34C6FFFF */  addic.  r6, r6, -1
/* 0C96FC 800CEC9C 9C030001 */  stbu    r0, 1(r3)
/* 0C9700 800CECA0 4082FFF4 */  bne     lbl_800CEC94
lbl_800CECA4:
/* 0C9704 800CECA4 54A4D97F */  rlwinm. r4, r5, 0x1b, 5, 0x1f
/* 0C9708 800CECA8 38C7FFFD */  addi    r6, r7, -3
/* 0C970C 800CECAC 3863FFFD */  addi    r3, r3, -3
/* 0C9710 800CECB0 4182004C */  beq     lbl_800CECFC
lbl_800CECB4:
/* 0C9714 800CECB4 80060004 */  lwz     r0, 4(r6)
/* 0C9718 800CECB8 3484FFFF */  addic.  r4, r4, -1
/* 0C971C 800CECBC 90030004 */  stw     r0, 4(r3)
/* 0C9720 800CECC0 80060008 */  lwz     r0, 8(r6)
/* 0C9724 800CECC4 90030008 */  stw     r0, 8(r3)
/* 0C9728 800CECC8 8006000C */  lwz     r0, 0xc(r6)
/* 0C972C 800CECCC 9003000C */  stw     r0, 0xc(r3)
/* 0C9730 800CECD0 80060010 */  lwz     r0, 0x10(r6)
/* 0C9734 800CECD4 90030010 */  stw     r0, 0x10(r3)
/* 0C9738 800CECD8 80060014 */  lwz     r0, 0x14(r6)
/* 0C973C 800CECDC 90030014 */  stw     r0, 0x14(r3)
/* 0C9740 800CECE0 80060018 */  lwz     r0, 0x18(r6)
/* 0C9744 800CECE4 90030018 */  stw     r0, 0x18(r3)
/* 0C9748 800CECE8 8006001C */  lwz     r0, 0x1c(r6)
/* 0C974C 800CECEC 9003001C */  stw     r0, 0x1c(r3)
/* 0C9750 800CECF0 84060020 */  lwzu    r0, 0x20(r6)
/* 0C9754 800CECF4 94030020 */  stwu    r0, 0x20(r3)
/* 0C9758 800CECF8 4082FFBC */  bne     lbl_800CECB4
lbl_800CECFC:
/* 0C975C 800CECFC 54A4F77F */  rlwinm. r4, r5, 0x1e, 0x1d, 0x1f
/* 0C9760 800CED00 41820014 */  beq     lbl_800CED14
lbl_800CED04:
/* 0C9764 800CED04 84060004 */  lwzu    r0, 4(r6)
/* 0C9768 800CED08 3484FFFF */  addic.  r4, r4, -1
/* 0C976C 800CED0C 94030004 */  stwu    r0, 4(r3)
/* 0C9770 800CED10 4082FFF4 */  bne     lbl_800CED04
lbl_800CED14:
/* 0C9774 800CED14 54A507BF */  clrlwi. r5, r5, 0x1e
/* 0C9778 800CED18 38860003 */  addi    r4, r6, 3
/* 0C977C 800CED1C 38630003 */  addi    r3, r3, 3
/* 0C9780 800CED20 4D820020 */  beqlr   
lbl_800CED24:
/* 0C9784 800CED24 8C040001 */  lbzu    r0, 1(r4)
/* 0C9788 800CED28 34A5FFFF */  addic.  r5, r5, -1
/* 0C978C 800CED2C 9C030001 */  stbu    r0, 1(r3)
/* 0C9790 800CED30 4082FFF4 */  bne     lbl_800CED24
/* 0C9794 800CED34 4E800020 */  blr     


