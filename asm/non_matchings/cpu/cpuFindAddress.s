glabel cpuFindAddress
/* 038F38 8003E4D8 7C0802A6 */  mflr    r0
/* 038F3C 8003E4DC 90010004 */  stw     r0, 4(r1)
/* 038F40 8003E4E0 9421FFC8 */  stwu    r1, -0x38(r1)
/* 038F44 8003E4E4 93E10034 */  stw     r31, 0x34(r1)
/* 038F48 8003E4E8 3BE50000 */  addi    r31, r5, 0
/* 038F4C 8003E4EC 93C10030 */  stw     r30, 0x30(r1)
/* 038F50 8003E4F0 3BC40000 */  addi    r30, r4, 0
/* 038F54 8003E4F4 93A1002C */  stw     r29, 0x2c(r1)
/* 038F58 8003E4F8 7C7D1B78 */  mr      r29, r3
/* 038F5C 8003E4FC 80630000 */  lwz     r3, 0(r3)
/* 038F60 8003E500 546006B5 */  rlwinm. r0, r3, 0, 0x1a, 0x1a
/* 038F64 8003E504 4182000C */  beq     lbl_8003E510
/* 038F68 8003E508 546006F2 */  rlwinm  r0, r3, 0, 0x1b, 0x19
/* 038F6C 8003E50C 901D0000 */  stw     r0, 0(r29)
lbl_8003E510:
/* 038F70 8003E510 387D0000 */  addi    r3, r29, 0
/* 038F74 8003E514 389E0000 */  addi    r4, r30, 0
/* 038F78 8003E518 38BF0000 */  addi    r5, r31, 0
/* 038F7C 8003E51C 4BFF7ECD */  bl      cpuFindCachedAddress
/* 038F80 8003E520 2C030000 */  cmpwi   r3, 0
/* 038F84 8003E524 4182000C */  beq     lbl_8003E530
/* 038F88 8003E528 38600001 */  li      r3, 1
/* 038F8C 8003E52C 4800042C */  b       lbl_8003E958
lbl_8003E530:
/* 038F90 8003E530 801D0034 */  lwz     r0, 0x34(r29)
/* 038F94 8003E534 28000000 */  cmplwi  r0, 0
/* 038F98 8003E538 90010018 */  stw     r0, 0x18(r1)
/* 038F9C 8003E53C 41820020 */  beq     lbl_8003E55C
/* 038FA0 8003E540 80610018 */  lwz     r3, 0x18(r1)
/* 038FA4 8003E544 80030010 */  lwz     r0, 0x10(r3)
/* 038FA8 8003E548 7C1E0000 */  cmpw    r30, r0
/* 038FAC 8003E54C 41800010 */  blt     lbl_8003E55C
/* 038FB0 8003E550 80030014 */  lwz     r0, 0x14(r3)
/* 038FB4 8003E554 7C00F000 */  cmpw    r0, r30
/* 038FB8 8003E558 40800024 */  bge     lbl_8003E57C
lbl_8003E55C:
/* 038FBC 8003E55C 387D0000 */  addi    r3, r29, 0
/* 038FC0 8003E560 38BE0000 */  addi    r5, r30, 0
/* 038FC4 8003E564 38810018 */  addi    r4, r1, 0x18
/* 038FC8 8003E568 4800040D */  bl      cpuMakeFunction
/* 038FCC 8003E56C 2C030000 */  cmpwi   r3, 0
/* 038FD0 8003E570 4082000C */  bne     lbl_8003E57C
/* 038FD4 8003E574 38600000 */  li      r3, 0
/* 038FD8 8003E578 480003E0 */  b       lbl_8003E958
lbl_8003E57C:
/* 038FDC 8003E57C 80A10018 */  lwz     r5, 0x18(r1)
/* 038FE0 8003E580 38C00000 */  li      r6, 0
/* 038FE4 8003E584 38600000 */  li      r3, 0
/* 038FE8 8003E588 80050008 */  lwz     r0, 8(r5)
/* 038FEC 8003E58C 2C000000 */  cmpwi   r0, 0
/* 038FF0 8003E590 7C0903A6 */  mtctr   r0
/* 038FF4 8003E594 408101A0 */  ble     lbl_8003E734
lbl_8003E598:
/* 038FF8 8003E598 8085000C */  lwz     r4, 0xc(r5)
/* 038FFC 8003E59C 38030004 */  addi    r0, r3, 4
/* 039000 8003E5A0 7C04002E */  lwzx    r0, r4, r0
/* 039004 8003E5A4 7C1E0000 */  cmpw    r30, r0
/* 039008 8003E5A8 40820180 */  bne     lbl_8003E728
/* 03900C 8003E5AC 54C01838 */  slwi    r0, r6, 3
/* 039010 8003E5B0 80650004 */  lwz     r3, 4(r5)
/* 039014 8003E5B4 7C04002E */  lwzx    r0, r4, r0
/* 039018 8003E5B8 5400103A */  slwi    r0, r0, 2
/* 03901C 8003E5BC 7C030214 */  add     r0, r3, r0
/* 039020 8003E5C0 901F0000 */  stw     r0, 0(r31)
/* 039024 8003E5C4 80610018 */  lwz     r3, 0x18(r1)
/* 039028 8003E5C8 84030028 */  lwzu    r0, 0x28(r3)
/* 03902C 8003E5CC 2C000000 */  cmpwi   r0, 0
/* 039030 8003E5D0 4081000C */  ble     lbl_8003E5DC
/* 039034 8003E5D4 801D003C */  lwz     r0, 0x3c(r29)
/* 039038 8003E5D8 90030000 */  stw     r0, 0(r3)
lbl_8003E5DC:
/* 03903C 8003E5DC 80BD0020 */  lwz     r5, 0x20(r29)
/* 039040 8003E5E0 3C9D0001 */  addis   r4, r29, 1
/* 039044 8003E5E4 80E10018 */  lwz     r7, 0x18(r1)
/* 039048 8003E5E8 388412A4 */  addi    r4, r4, 0x12a4
/* 03904C 8003E5EC 2C050100 */  cmpwi   r5, 0x100
/* 039050 8003E5F0 80DF0000 */  lwz     r6, 0(r31)
/* 039054 8003E5F4 4082000C */  bne     lbl_8003E600
/* 039058 8003E5F8 38A5FFFF */  addi    r5, r5, -1
/* 03905C 8003E5FC 48000344 */  b       lbl_8003E940
lbl_8003E600:
/* 039060 8003E600 38050001 */  addi    r0, r5, 1
/* 039064 8003E604 901D0020 */  stw     r0, 0x20(r29)
/* 039068 8003E608 48000338 */  b       lbl_8003E940
lbl_8003E60C:
/* 03906C 8003E60C 2C050000 */  cmpwi   r5, 0
/* 039070 8003E610 40810104 */  ble     lbl_8003E714
/* 039074 8003E614 54A0E8FF */  rlwinm. r0, r5, 0x1d, 3, 0x1f
/* 039078 8003E618 7C0903A6 */  mtctr   r0
/* 03907C 8003E61C 418200D4 */  beq     lbl_8003E6F0
lbl_8003E620:
/* 039080 8003E620 8068FFF4 */  lwz     r3, -0xc(r8)
/* 039084 8003E624 8008FFF8 */  lwz     r0, -8(r8)
/* 039088 8003E628 90680000 */  stw     r3, 0(r8)
/* 03908C 8003E62C 90080004 */  stw     r0, 4(r8)
/* 039090 8003E630 8008FFFC */  lwz     r0, -4(r8)
/* 039094 8003E634 90080008 */  stw     r0, 8(r8)
/* 039098 8003E638 8068FFE8 */  lwz     r3, -0x18(r8)
/* 03909C 8003E63C 8008FFEC */  lwz     r0, -0x14(r8)
/* 0390A0 8003E640 9068FFF4 */  stw     r3, -0xc(r8)
/* 0390A4 8003E644 9008FFF8 */  stw     r0, -8(r8)
/* 0390A8 8003E648 8008FFF0 */  lwz     r0, -0x10(r8)
/* 0390AC 8003E64C 9008FFFC */  stw     r0, -4(r8)
/* 0390B0 8003E650 8068FFDC */  lwz     r3, -0x24(r8)
/* 0390B4 8003E654 8008FFE0 */  lwz     r0, -0x20(r8)
/* 0390B8 8003E658 9068FFE8 */  stw     r3, -0x18(r8)
/* 0390BC 8003E65C 9008FFEC */  stw     r0, -0x14(r8)
/* 0390C0 8003E660 8008FFE4 */  lwz     r0, -0x1c(r8)
/* 0390C4 8003E664 9008FFF0 */  stw     r0, -0x10(r8)
/* 0390C8 8003E668 8068FFD0 */  lwz     r3, -0x30(r8)
/* 0390CC 8003E66C 8008FFD4 */  lwz     r0, -0x2c(r8)
/* 0390D0 8003E670 9068FFDC */  stw     r3, -0x24(r8)
/* 0390D4 8003E674 9008FFE0 */  stw     r0, -0x20(r8)
/* 0390D8 8003E678 8008FFD8 */  lwz     r0, -0x28(r8)
/* 0390DC 8003E67C 9008FFE4 */  stw     r0, -0x1c(r8)
/* 0390E0 8003E680 8068FFC4 */  lwz     r3, -0x3c(r8)
/* 0390E4 8003E684 8008FFC8 */  lwz     r0, -0x38(r8)
/* 0390E8 8003E688 9068FFD0 */  stw     r3, -0x30(r8)
/* 0390EC 8003E68C 9008FFD4 */  stw     r0, -0x2c(r8)
/* 0390F0 8003E690 8008FFCC */  lwz     r0, -0x34(r8)
/* 0390F4 8003E694 9008FFD8 */  stw     r0, -0x28(r8)
/* 0390F8 8003E698 8068FFB8 */  lwz     r3, -0x48(r8)
/* 0390FC 8003E69C 8008FFBC */  lwz     r0, -0x44(r8)
/* 039100 8003E6A0 9068FFC4 */  stw     r3, -0x3c(r8)
/* 039104 8003E6A4 9008FFC8 */  stw     r0, -0x38(r8)
/* 039108 8003E6A8 8008FFC0 */  lwz     r0, -0x40(r8)
/* 03910C 8003E6AC 9008FFCC */  stw     r0, -0x34(r8)
/* 039110 8003E6B0 8068FFAC */  lwz     r3, -0x54(r8)
/* 039114 8003E6B4 8008FFB0 */  lwz     r0, -0x50(r8)
/* 039118 8003E6B8 9068FFB8 */  stw     r3, -0x48(r8)
/* 03911C 8003E6BC 9008FFBC */  stw     r0, -0x44(r8)
/* 039120 8003E6C0 8008FFB4 */  lwz     r0, -0x4c(r8)
/* 039124 8003E6C4 9008FFC0 */  stw     r0, -0x40(r8)
/* 039128 8003E6C8 8068FFA0 */  lwz     r3, -0x60(r8)
/* 03912C 8003E6CC 8008FFA4 */  lwz     r0, -0x5c(r8)
/* 039130 8003E6D0 9068FFAC */  stw     r3, -0x54(r8)
/* 039134 8003E6D4 9008FFB0 */  stw     r0, -0x50(r8)
/* 039138 8003E6D8 8008FFA8 */  lwz     r0, -0x58(r8)
/* 03913C 8003E6DC 9008FFB4 */  stw     r0, -0x4c(r8)
/* 039140 8003E6E0 3908FFA0 */  addi    r8, r8, -96
/* 039144 8003E6E4 4200FF3C */  bdnz    lbl_8003E620
/* 039148 8003E6E8 70A50007 */  andi.   r5, r5, 7
/* 03914C 8003E6EC 41820028 */  beq     lbl_8003E714
lbl_8003E6F0:
/* 039150 8003E6F0 7CA903A6 */  mtctr   r5
lbl_8003E6F4:
/* 039154 8003E6F4 8068FFF4 */  lwz     r3, -0xc(r8)
/* 039158 8003E6F8 8008FFF8 */  lwz     r0, -8(r8)
/* 03915C 8003E6FC 90680000 */  stw     r3, 0(r8)
/* 039160 8003E700 90080004 */  stw     r0, 4(r8)
/* 039164 8003E704 8008FFFC */  lwz     r0, -4(r8)
/* 039168 8003E708 90080008 */  stw     r0, 8(r8)
/* 03916C 8003E70C 3908FFF4 */  addi    r8, r8, -12
/* 039170 8003E710 4200FFE4 */  bdnz    lbl_8003E6F4
lbl_8003E714:
/* 039174 8003E714 93C40000 */  stw     r30, 0(r4)
/* 039178 8003E718 38600001 */  li      r3, 1
/* 03917C 8003E71C 90C40004 */  stw     r6, 4(r4)
/* 039180 8003E720 90E40008 */  stw     r7, 8(r4)
/* 039184 8003E724 48000234 */  b       lbl_8003E958
lbl_8003E728:
/* 039188 8003E728 38630008 */  addi    r3, r3, 8
/* 03918C 8003E72C 38C60001 */  addi    r6, r6, 1
/* 039190 8003E730 4200FE68 */  bdnz    lbl_8003E598
lbl_8003E734:
/* 039194 8003E734 3C7D0001 */  addis   r3, r29, 1
/* 039198 8003E738 3C002000 */  lis     r0, 0x2000
/* 03919C 8003E73C 90032058 */  stw     r0, 0x2058(r3)
/* 0391A0 8003E740 38800000 */  li      r4, 0
/* 0391A4 8003E744 38000021 */  li      r0, 0x21
/* 0391A8 8003E748 9083205C */  stw     r4, 0x205c(r3)
/* 0391AC 8003E74C 80610018 */  lwz     r3, 0x18(r1)
/* 0391B0 8003E750 90030020 */  stw     r0, 0x20(r3)
/* 0391B4 8003E754 90810020 */  stw     r4, 0x20(r1)
/* 0391B8 8003E758 80610018 */  lwz     r3, 0x18(r1)
/* 0391BC 8003E75C 80030010 */  lwz     r0, 0x10(r3)
/* 0391C0 8003E760 7C00F000 */  cmpw    r0, r30
/* 0391C4 8003E764 41820008 */  beq     lbl_8003E76C
/* 0391C8 8003E768 90830028 */  stw     r4, 0x28(r3)
lbl_8003E76C:
/* 0391CC 8003E76C 80610018 */  lwz     r3, 0x18(r1)
/* 0391D0 8003E770 80030010 */  lwz     r0, 0x10(r3)
/* 0391D4 8003E774 9001001C */  stw     r0, 0x1c(r1)
/* 0391D8 8003E778 480001AC */  b       lbl_8003E924
lbl_8003E77C:
/* 0391DC 8003E77C 7C03F000 */  cmpw    r3, r30
/* 0391E0 8003E780 4082017C */  bne     lbl_8003E8FC
/* 0391E4 8003E784 80010020 */  lwz     r0, 0x20(r1)
/* 0391E8 8003E788 80650004 */  lwz     r3, 4(r5)
/* 0391EC 8003E78C 5400103A */  slwi    r0, r0, 2
/* 0391F0 8003E790 7C030214 */  add     r0, r3, r0
/* 0391F4 8003E794 901F0000 */  stw     r0, 0(r31)
/* 0391F8 8003E798 80610018 */  lwz     r3, 0x18(r1)
/* 0391FC 8003E79C 84030028 */  lwzu    r0, 0x28(r3)
/* 039200 8003E7A0 2C000000 */  cmpwi   r0, 0
/* 039204 8003E7A4 4081000C */  ble     lbl_8003E7B0
/* 039208 8003E7A8 801D003C */  lwz     r0, 0x3c(r29)
/* 03920C 8003E7AC 90030000 */  stw     r0, 0(r3)
lbl_8003E7B0:
/* 039210 8003E7B0 807D0020 */  lwz     r3, 0x20(r29)
/* 039214 8003E7B4 3CBD0001 */  addis   r5, r29, 1
/* 039218 8003E7B8 80E10018 */  lwz     r7, 0x18(r1)
/* 03921C 8003E7BC 38A512A4 */  addi    r5, r5, 0x12a4
/* 039220 8003E7C0 2C030100 */  cmpwi   r3, 0x100
/* 039224 8003E7C4 80DF0000 */  lwz     r6, 0(r31)
/* 039228 8003E7C8 4082000C */  bne     lbl_8003E7D4
/* 03922C 8003E7CC 3863FFFF */  addi    r3, r3, -1
/* 039230 8003E7D0 4800017C */  b       lbl_8003E94C
lbl_8003E7D4:
/* 039234 8003E7D4 38030001 */  addi    r0, r3, 1
/* 039238 8003E7D8 901D0020 */  stw     r0, 0x20(r29)
/* 03923C 8003E7DC 48000170 */  b       lbl_8003E94C
lbl_8003E7E0:
/* 039240 8003E7E0 2C030000 */  cmpwi   r3, 0
/* 039244 8003E7E4 40810104 */  ble     lbl_8003E8E8
/* 039248 8003E7E8 5460E8FF */  rlwinm. r0, r3, 0x1d, 3, 0x1f
/* 03924C 8003E7EC 7C0903A6 */  mtctr   r0
/* 039250 8003E7F0 418200D4 */  beq     lbl_8003E8C4
lbl_8003E7F4:
/* 039254 8003E7F4 8088FFF4 */  lwz     r4, -0xc(r8)
/* 039258 8003E7F8 8008FFF8 */  lwz     r0, -8(r8)
/* 03925C 8003E7FC 90880000 */  stw     r4, 0(r8)
/* 039260 8003E800 90080004 */  stw     r0, 4(r8)
/* 039264 8003E804 8008FFFC */  lwz     r0, -4(r8)
/* 039268 8003E808 90080008 */  stw     r0, 8(r8)
/* 03926C 8003E80C 8088FFE8 */  lwz     r4, -0x18(r8)
/* 039270 8003E810 8008FFEC */  lwz     r0, -0x14(r8)
/* 039274 8003E814 9088FFF4 */  stw     r4, -0xc(r8)
/* 039278 8003E818 9008FFF8 */  stw     r0, -8(r8)
/* 03927C 8003E81C 8008FFF0 */  lwz     r0, -0x10(r8)
/* 039280 8003E820 9008FFFC */  stw     r0, -4(r8)
/* 039284 8003E824 8088FFDC */  lwz     r4, -0x24(r8)
/* 039288 8003E828 8008FFE0 */  lwz     r0, -0x20(r8)
/* 03928C 8003E82C 9088FFE8 */  stw     r4, -0x18(r8)
/* 039290 8003E830 9008FFEC */  stw     r0, -0x14(r8)
/* 039294 8003E834 8008FFE4 */  lwz     r0, -0x1c(r8)
/* 039298 8003E838 9008FFF0 */  stw     r0, -0x10(r8)
/* 03929C 8003E83C 8088FFD0 */  lwz     r4, -0x30(r8)
/* 0392A0 8003E840 8008FFD4 */  lwz     r0, -0x2c(r8)
/* 0392A4 8003E844 9088FFDC */  stw     r4, -0x24(r8)
/* 0392A8 8003E848 9008FFE0 */  stw     r0, -0x20(r8)
/* 0392AC 8003E84C 8008FFD8 */  lwz     r0, -0x28(r8)
/* 0392B0 8003E850 9008FFE4 */  stw     r0, -0x1c(r8)
/* 0392B4 8003E854 8088FFC4 */  lwz     r4, -0x3c(r8)
/* 0392B8 8003E858 8008FFC8 */  lwz     r0, -0x38(r8)
/* 0392BC 8003E85C 9088FFD0 */  stw     r4, -0x30(r8)
/* 0392C0 8003E860 9008FFD4 */  stw     r0, -0x2c(r8)
/* 0392C4 8003E864 8008FFCC */  lwz     r0, -0x34(r8)
/* 0392C8 8003E868 9008FFD8 */  stw     r0, -0x28(r8)
/* 0392CC 8003E86C 8088FFB8 */  lwz     r4, -0x48(r8)
/* 0392D0 8003E870 8008FFBC */  lwz     r0, -0x44(r8)
/* 0392D4 8003E874 9088FFC4 */  stw     r4, -0x3c(r8)
/* 0392D8 8003E878 9008FFC8 */  stw     r0, -0x38(r8)
/* 0392DC 8003E87C 8008FFC0 */  lwz     r0, -0x40(r8)
/* 0392E0 8003E880 9008FFCC */  stw     r0, -0x34(r8)
/* 0392E4 8003E884 8088FFAC */  lwz     r4, -0x54(r8)
/* 0392E8 8003E888 8008FFB0 */  lwz     r0, -0x50(r8)
/* 0392EC 8003E88C 9088FFB8 */  stw     r4, -0x48(r8)
/* 0392F0 8003E890 9008FFBC */  stw     r0, -0x44(r8)
/* 0392F4 8003E894 8008FFB4 */  lwz     r0, -0x4c(r8)
/* 0392F8 8003E898 9008FFC0 */  stw     r0, -0x40(r8)
/* 0392FC 8003E89C 8088FFA0 */  lwz     r4, -0x60(r8)
/* 039300 8003E8A0 8008FFA4 */  lwz     r0, -0x5c(r8)
/* 039304 8003E8A4 9088FFAC */  stw     r4, -0x54(r8)
/* 039308 8003E8A8 9008FFB0 */  stw     r0, -0x50(r8)
/* 03930C 8003E8AC 8008FFA8 */  lwz     r0, -0x58(r8)
/* 039310 8003E8B0 9008FFB4 */  stw     r0, -0x4c(r8)
/* 039314 8003E8B4 3908FFA0 */  addi    r8, r8, -96
/* 039318 8003E8B8 4200FF3C */  bdnz    lbl_8003E7F4
/* 03931C 8003E8BC 70630007 */  andi.   r3, r3, 7
/* 039320 8003E8C0 41820028 */  beq     lbl_8003E8E8
lbl_8003E8C4:
/* 039324 8003E8C4 7C6903A6 */  mtctr   r3
lbl_8003E8C8:
/* 039328 8003E8C8 8088FFF4 */  lwz     r4, -0xc(r8)
/* 03932C 8003E8CC 8008FFF8 */  lwz     r0, -8(r8)
/* 039330 8003E8D0 90880000 */  stw     r4, 0(r8)
/* 039334 8003E8D4 90080004 */  stw     r0, 4(r8)
/* 039338 8003E8D8 8008FFFC */  lwz     r0, -4(r8)
/* 03933C 8003E8DC 90080008 */  stw     r0, 8(r8)
/* 039340 8003E8E0 3908FFF4 */  addi    r8, r8, -12
/* 039344 8003E8E4 4200FFE4 */  bdnz    lbl_8003E8C8
lbl_8003E8E8:
/* 039348 8003E8E8 93C50000 */  stw     r30, 0(r5)
/* 03934C 8003E8EC 38600001 */  li      r3, 1
/* 039350 8003E8F0 90C50004 */  stw     r6, 4(r5)
/* 039354 8003E8F4 90E50008 */  stw     r7, 8(r5)
/* 039358 8003E8F8 48000060 */  b       lbl_8003E958
lbl_8003E8FC:
/* 03935C 8003E8FC 387D0000 */  addi    r3, r29, 0
/* 039360 8003E900 3881001C */  addi    r4, r1, 0x1c
/* 039364 8003E904 38E10020 */  addi    r7, r1, 0x20
/* 039368 8003E908 38C00000 */  li      r6, 0
/* 03936C 8003E90C 39000000 */  li      r8, 0
/* 039370 8003E910 480004F5 */  bl      cpuGetPPC
/* 039374 8003E914 2C030000 */  cmpwi   r3, 0
/* 039378 8003E918 4082000C */  bne     lbl_8003E924
/* 03937C 8003E91C 38600000 */  li      r3, 0
/* 039380 8003E920 48000038 */  b       lbl_8003E958
lbl_8003E924:
/* 039384 8003E924 80A10018 */  lwz     r5, 0x18(r1)
/* 039388 8003E928 8061001C */  lwz     r3, 0x1c(r1)
/* 03938C 8003E92C 80050014 */  lwz     r0, 0x14(r5)
/* 039390 8003E930 7C030000 */  cmpw    r3, r0
/* 039394 8003E934 4081FE48 */  ble     lbl_8003E77C
/* 039398 8003E938 38600000 */  li      r3, 0
/* 03939C 8003E93C 4800001C */  b       lbl_8003E958
lbl_8003E940:
/* 0393A0 8003E940 1C05000C */  mulli   r0, r5, 0xc
/* 0393A4 8003E944 7D040214 */  add     r8, r4, r0
/* 0393A8 8003E948 4BFFFCC4 */  b       lbl_8003E60C
lbl_8003E94C:
/* 0393AC 8003E94C 1C03000C */  mulli   r0, r3, 0xc
/* 0393B0 8003E950 7D050214 */  add     r8, r5, r0
/* 0393B4 8003E954 4BFFFE8C */  b       lbl_8003E7E0
lbl_8003E958:
/* 0393B8 8003E958 8001003C */  lwz     r0, 0x3c(r1)
/* 0393BC 8003E95C 83E10034 */  lwz     r31, 0x34(r1)
/* 0393C0 8003E960 83C10030 */  lwz     r30, 0x30(r1)
/* 0393C4 8003E964 7C0803A6 */  mtlr    r0
/* 0393C8 8003E968 83A1002C */  lwz     r29, 0x2c(r1)
/* 0393CC 8003E96C 38210038 */  addi    r1, r1, 0x38
/* 0393D0 8003E970 4E800020 */  blr     
