glabel simulatorDrawMCardText
/* 0035A4 80008B44 7C0802A6 */  mflr    r0
/* 0035A8 80008B48 3C60800F */  lis     r3, gOrthoMtx@ha
/* 0035AC 80008B4C 90010004 */  stw     r0, 4(r1)
/* 0035B0 80008B50 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0035B4 80008B54 93E1000C */  stw     r31, 0xc(r1)
/* 0035B8 80008B58 3BE34540 */  addi    r31, r3, gOrthoMtx@l
/* 0035BC 80008B5C 801F01A0 */  lwz     r0, 0x1a0(r31)
/* 0035C0 80008B60 2C000000 */  cmpwi   r0, 0
/* 0035C4 80008B64 40820028 */  bne     lbl_80008B8C
/* 0035C8 80008B68 3C60800F */  lis     r3, D_800E9CDC@ha
/* 0035CC 80008B6C 4CC63182 */  crclr   6
/* 0035D0 80008B70 3C80800F */  lis     r4, D_800E9D08@ha
/* 0035D4 80008B74 38639CDC */  addi    r3, r3, D_800E9CDC@l
/* 0035D8 80008B78 38849D08 */  addi    r4, r4, D_800E9D08@l
/* 0035DC 80008B7C 38A00657 */  li      r5, 0x657
/* 0035E0 80008B80 4BFFD295 */  bl      xlPostText
/* 0035E4 80008B84 3860002A */  li      r3, 0x2a
/* 0035E8 80008B88 48004669 */  bl      simulatorPrepareMessage
lbl_80008B8C:
/* 0035EC 80008B8C 809F01A8 */  lwz     r4, 0x1a8(r31)
/* 0035F0 80008B90 387F01A0 */  addi    r3, r31, 0x1a0
/* 0035F4 80008B94 38C00000 */  li      r6, 0
/* 0035F8 80008B98 80A40000 */  lwz     r5, 0(r4)
/* 0035FC 80008B9C 38E00000 */  li      r7, 0
/* 003600 80008BA0 A0850002 */  lhz     r4, 2(r5)
/* 003604 80008BA4 A0050000 */  lhz     r0, 0(r5)
/* 003608 80008BA8 7C840E70 */  srawi   r4, r4, 1
/* 00360C 80008BAC 7C840194 */  addze   r4, r4
/* 003610 80008BB0 208400A0 */  subfic  r4, r4, 0xa0
/* 003614 80008BB4 7C000E70 */  srawi   r0, r0, 1
/* 003618 80008BB8 7C000194 */  addze   r0, r0
/* 00361C 80008BBC 20A00078 */  subfic  r5, r0, 0x78
/* 003620 80008BC0 480058C5 */  bl      simulatorDrawImage
/* 003624 80008BC4 80010014 */  lwz     r0, 0x14(r1)
/* 003628 80008BC8 38600001 */  li      r3, 1
/* 00362C 80008BCC 83E1000C */  lwz     r31, 0xc(r1)
/* 003630 80008BD0 38210010 */  addi    r1, r1, 0x10
/* 003634 80008BD4 7C0803A6 */  mtlr    r0
/* 003638 80008BD8 4E800020 */  blr     
