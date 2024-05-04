glabel simulatorDrawYesNoMessage
/* 0075DC 8000CB7C 7C0802A6 */  mflr    r0
/* 0075E0 8000CB80 3CA0800E */  lis     r5, gcoverOpen@ha
/* 0075E4 8000CB84 90010004 */  stw     r0, 4(r1)
/* 0075E8 8000CB88 3803FFF4 */  addi    r0, r3, -12
/* 0075EC 8000CB8C 2800001D */  cmplwi  r0, 0x1d
/* 0075F0 8000CB90 9421FFA8 */  stwu    r1, -0x58(r1)
/* 0075F4 8000CB94 3CC0800F */  lis     r6, gOrthoMtx@ha
/* 0075F8 8000CB98 38A5B800 */  addi    r5, r5, gcoverOpen@l
/* 0075FC 8000CB9C 93E10054 */  stw     r31, 0x54(r1)
/* 007600 8000CBA0 3BE64540 */  addi    r31, r6, gOrthoMtx@l
/* 007604 8000CBA4 93C10050 */  stw     r30, 0x50(r1)
/* 007608 8000CBA8 3BC40000 */  addi    r30, r4, 0
/* 00760C 8000CBAC 4181035C */  bgt     lbl_8000CF08
/* 007610 8000CBB0 3C80800F */  lis     r4, jtbl_800EA09C@ha
/* 007614 8000CBB4 3884A09C */  addi    r4, r4, jtbl_800EA09C@l
/* 007618 8000CBB8 5400103A */  slwi    r0, r0, 2
/* 00761C 8000CBBC 7C04002E */  lwzx    r0, r4, r0
/* 007620 8000CBC0 7C0903A6 */  mtctr   r0
/* 007624 8000CBC4 4E800420 */  bctr    
.global lbl_8000CBC8
lbl_8000CBC8:
/* 007628 8000CBC8 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 00762C 8000CBCC 7C001800 */  cmpw    r0, r3
/* 007630 8000CBD0 41820050 */  beq     lbl_8000CC20
/* 007634 8000CBD4 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007638 8000CBD8 3C650001 */  addis   r3, r5, 1
/* 00763C 8000CBDC 3863E7FC */  addi    r3, r3, -6148
/* 007640 8000CBE0 38810010 */  addi    r4, r1, 0x10
/* 007644 8000CBE4 480A5E51 */  bl      DVDOpen
/* 007648 8000CBE8 2C030001 */  cmpwi   r3, 1
/* 00764C 8000CBEC 40820024 */  bne     lbl_8000CC10
/* 007650 8000CBF0 80AD801C */  lwz     r5, gmsg_ld05_2Size@sda21(r13)
/* 007654 8000CBF4 38610010 */  addi    r3, r1, 0x10
/* 007658 8000CBF8 389F01A0 */  addi    r4, r31, 0x1a0
/* 00765C 8000CBFC 3805001F */  addi    r0, r5, 0x1f
/* 007660 8000CC00 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 007664 8000CC04 38C00000 */  li      r6, 0
/* 007668 8000CC08 38E00000 */  li      r7, 0
/* 00766C 8000CC0C 480020B9 */  bl      simulatorDVDRead
lbl_8000CC10:
/* 007670 8000CC10 38610010 */  addi    r3, r1, 0x10
/* 007674 8000CC14 480A5EE9 */  bl      DVDClose
/* 007678 8000CC18 387F01A0 */  addi    r3, r31, 0x1a0
/* 00767C 8000CC1C 48002405 */  bl      simulatorUnpackTexPalette
lbl_8000CC20:
/* 007680 8000CC20 387F01A0 */  addi    r3, r31, 0x1a0
/* 007684 8000CC24 389E0000 */  addi    r4, r30, 0
/* 007688 8000CC28 480002FD */  bl      simulatorDrawYesNoMessageLoop
/* 00768C 8000CC2C 480002E0 */  b       lbl_8000CF0C
.global lbl_8000CC30
lbl_8000CC30:
/* 007690 8000CC30 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007694 8000CC34 7C001800 */  cmpw    r0, r3
/* 007698 8000CC38 41820050 */  beq     lbl_8000CC88
/* 00769C 8000CC3C 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0076A0 8000CC40 3C650001 */  addis   r3, r5, 1
/* 0076A4 8000CC44 3863E810 */  addi    r3, r3, -6128
/* 0076A8 8000CC48 38810010 */  addi    r4, r1, 0x10
/* 0076AC 8000CC4C 480A5DE9 */  bl      DVDOpen
/* 0076B0 8000CC50 2C030001 */  cmpwi   r3, 1
/* 0076B4 8000CC54 40820024 */  bne     lbl_8000CC78
/* 0076B8 8000CC58 80AD802C */  lwz     r5, gmsg_ld06_4Size@sda21(r13)
/* 0076BC 8000CC5C 38610010 */  addi    r3, r1, 0x10
/* 0076C0 8000CC60 389F01A0 */  addi    r4, r31, 0x1a0
/* 0076C4 8000CC64 3805001F */  addi    r0, r5, 0x1f
/* 0076C8 8000CC68 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0076CC 8000CC6C 38C00000 */  li      r6, 0
/* 0076D0 8000CC70 38E00000 */  li      r7, 0
/* 0076D4 8000CC74 48002051 */  bl      simulatorDVDRead
lbl_8000CC78:
/* 0076D8 8000CC78 38610010 */  addi    r3, r1, 0x10
/* 0076DC 8000CC7C 480A5E81 */  bl      DVDClose
/* 0076E0 8000CC80 387F01A0 */  addi    r3, r31, 0x1a0
/* 0076E4 8000CC84 4800239D */  bl      simulatorUnpackTexPalette
lbl_8000CC88:
/* 0076E8 8000CC88 387F01A0 */  addi    r3, r31, 0x1a0
/* 0076EC 8000CC8C 389E0000 */  addi    r4, r30, 0
/* 0076F0 8000CC90 48000295 */  bl      simulatorDrawYesNoMessageLoop
/* 0076F4 8000CC94 48000278 */  b       lbl_8000CF0C
.global lbl_8000CC98
lbl_8000CC98:
/* 0076F8 8000CC98 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0076FC 8000CC9C 7C001800 */  cmpw    r0, r3
/* 007700 8000CCA0 41820050 */  beq     lbl_8000CCF0
/* 007704 8000CCA4 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007708 8000CCA8 3C650001 */  addis   r3, r5, 1
/* 00770C 8000CCAC 3863E824 */  addi    r3, r3, -6108
/* 007710 8000CCB0 38810010 */  addi    r4, r1, 0x10
/* 007714 8000CCB4 480A5D81 */  bl      DVDOpen
/* 007718 8000CCB8 2C030001 */  cmpwi   r3, 1
/* 00771C 8000CCBC 40820024 */  bne     lbl_8000CCE0
/* 007720 8000CCC0 80AD8030 */  lwz     r5, gmsg_ld07Size@sda21(r13)
/* 007724 8000CCC4 38610010 */  addi    r3, r1, 0x10
/* 007728 8000CCC8 389F01A0 */  addi    r4, r31, 0x1a0
/* 00772C 8000CCCC 3805001F */  addi    r0, r5, 0x1f
/* 007730 8000CCD0 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 007734 8000CCD4 38C00000 */  li      r6, 0
/* 007738 8000CCD8 38E00000 */  li      r7, 0
/* 00773C 8000CCDC 48001FE9 */  bl      simulatorDVDRead
lbl_8000CCE0:
/* 007740 8000CCE0 38610010 */  addi    r3, r1, 0x10
/* 007744 8000CCE4 480A5E19 */  bl      DVDClose
/* 007748 8000CCE8 387F01A0 */  addi    r3, r31, 0x1a0
/* 00774C 8000CCEC 48002335 */  bl      simulatorUnpackTexPalette
lbl_8000CCF0:
/* 007750 8000CCF0 387F01A0 */  addi    r3, r31, 0x1a0
/* 007754 8000CCF4 389E0000 */  addi    r4, r30, 0
/* 007758 8000CCF8 4800022D */  bl      simulatorDrawYesNoMessageLoop
/* 00775C 8000CCFC 48000210 */  b       lbl_8000CF0C
.global lbl_8000CD00
lbl_8000CD00:
/* 007760 8000CD00 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007764 8000CD04 7C001800 */  cmpw    r0, r3
/* 007768 8000CD08 41820050 */  beq     lbl_8000CD58
/* 00776C 8000CD0C 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007770 8000CD10 3C650001 */  addis   r3, r5, 1
/* 007774 8000CD14 3863E838 */  addi    r3, r3, -6088
/* 007778 8000CD18 38810010 */  addi    r4, r1, 0x10
/* 00777C 8000CD1C 480A5D19 */  bl      DVDOpen
/* 007780 8000CD20 2C030001 */  cmpwi   r3, 1
/* 007784 8000CD24 40820024 */  bne     lbl_8000CD48
/* 007788 8000CD28 80AD8034 */  lwz     r5, gmsg_gf01Size@sda21(r13)
/* 00778C 8000CD2C 38610010 */  addi    r3, r1, 0x10
/* 007790 8000CD30 389F01A0 */  addi    r4, r31, 0x1a0
/* 007794 8000CD34 3805001F */  addi    r0, r5, 0x1f
/* 007798 8000CD38 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 00779C 8000CD3C 38C00000 */  li      r6, 0
/* 0077A0 8000CD40 38E00000 */  li      r7, 0
/* 0077A4 8000CD44 48001F81 */  bl      simulatorDVDRead
lbl_8000CD48:
/* 0077A8 8000CD48 38610010 */  addi    r3, r1, 0x10
/* 0077AC 8000CD4C 480A5DB1 */  bl      DVDClose
/* 0077B0 8000CD50 387F01A0 */  addi    r3, r31, 0x1a0
/* 0077B4 8000CD54 480022CD */  bl      simulatorUnpackTexPalette
lbl_8000CD58:
/* 0077B8 8000CD58 387F01A0 */  addi    r3, r31, 0x1a0
/* 0077BC 8000CD5C 389E0000 */  addi    r4, r30, 0
/* 0077C0 8000CD60 480001C5 */  bl      simulatorDrawYesNoMessageLoop
/* 0077C4 8000CD64 480001A8 */  b       lbl_8000CF0C
.global lbl_8000CD68
lbl_8000CD68:
/* 0077C8 8000CD68 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0077CC 8000CD6C 7C001800 */  cmpw    r0, r3
/* 0077D0 8000CD70 41820050 */  beq     lbl_8000CDC0
/* 0077D4 8000CD74 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0077D8 8000CD78 3C650001 */  addis   r3, r5, 1
/* 0077DC 8000CD7C 3863E84C */  addi    r3, r3, -6068
/* 0077E0 8000CD80 38810010 */  addi    r4, r1, 0x10
/* 0077E4 8000CD84 480A5CB1 */  bl      DVDOpen
/* 0077E8 8000CD88 2C030001 */  cmpwi   r3, 1
/* 0077EC 8000CD8C 40820024 */  bne     lbl_8000CDB0
/* 0077F0 8000CD90 80AD804C */  lwz     r5, gmsg_in01Size@sda21(r13)
/* 0077F4 8000CD94 38610010 */  addi    r3, r1, 0x10
/* 0077F8 8000CD98 389F01A0 */  addi    r4, r31, 0x1a0
/* 0077FC 8000CD9C 3805001F */  addi    r0, r5, 0x1f
/* 007800 8000CDA0 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 007804 8000CDA4 38C00000 */  li      r6, 0
/* 007808 8000CDA8 38E00000 */  li      r7, 0
/* 00780C 8000CDAC 48001F19 */  bl      simulatorDVDRead
lbl_8000CDB0:
/* 007810 8000CDB0 38610010 */  addi    r3, r1, 0x10
/* 007814 8000CDB4 480A5D49 */  bl      DVDClose
/* 007818 8000CDB8 387F01A0 */  addi    r3, r31, 0x1a0
/* 00781C 8000CDBC 48002265 */  bl      simulatorUnpackTexPalette
lbl_8000CDC0:
/* 007820 8000CDC0 387F01A0 */  addi    r3, r31, 0x1a0
/* 007824 8000CDC4 389E0000 */  addi    r4, r30, 0
/* 007828 8000CDC8 4800015D */  bl      simulatorDrawYesNoMessageLoop
/* 00782C 8000CDCC 48000140 */  b       lbl_8000CF0C
.global lbl_8000CDD0
lbl_8000CDD0:
/* 007830 8000CDD0 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007834 8000CDD4 7C001800 */  cmpw    r0, r3
/* 007838 8000CDD8 41820050 */  beq     lbl_8000CE28
/* 00783C 8000CDDC 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007840 8000CDE0 3C650001 */  addis   r3, r5, 1
/* 007844 8000CDE4 3863E860 */  addi    r3, r3, -6048
/* 007848 8000CDE8 38810010 */  addi    r4, r1, 0x10
/* 00784C 8000CDEC 480A5C49 */  bl      DVDOpen
/* 007850 8000CDF0 2C030001 */  cmpwi   r3, 1
/* 007854 8000CDF4 40820024 */  bne     lbl_8000CE18
/* 007858 8000CDF8 80AD8084 */  lwz     r5, gmsg_sv06_4Size@sda21(r13)
/* 00785C 8000CDFC 38610010 */  addi    r3, r1, 0x10
/* 007860 8000CE00 389F01A0 */  addi    r4, r31, 0x1a0
/* 007864 8000CE04 3805001F */  addi    r0, r5, 0x1f
/* 007868 8000CE08 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 00786C 8000CE0C 38C00000 */  li      r6, 0
/* 007870 8000CE10 38E00000 */  li      r7, 0
/* 007874 8000CE14 48001EB1 */  bl      simulatorDVDRead
lbl_8000CE18:
/* 007878 8000CE18 38610010 */  addi    r3, r1, 0x10
/* 00787C 8000CE1C 480A5CE1 */  bl      DVDClose
/* 007880 8000CE20 387F01A0 */  addi    r3, r31, 0x1a0
/* 007884 8000CE24 480021FD */  bl      simulatorUnpackTexPalette
lbl_8000CE28:
/* 007888 8000CE28 387F01A0 */  addi    r3, r31, 0x1a0
/* 00788C 8000CE2C 389E0000 */  addi    r4, r30, 0
/* 007890 8000CE30 480000F5 */  bl      simulatorDrawYesNoMessageLoop
/* 007894 8000CE34 480000D8 */  b       lbl_8000CF0C
.global lbl_8000CE38
lbl_8000CE38:
/* 007898 8000CE38 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 00789C 8000CE3C 7C001800 */  cmpw    r0, r3
/* 0078A0 8000CE40 41820050 */  beq     lbl_8000CE90
/* 0078A4 8000CE44 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0078A8 8000CE48 3C650001 */  addis   r3, r5, 1
/* 0078AC 8000CE4C 3863E874 */  addi    r3, r3, -6028
/* 0078B0 8000CE50 38810010 */  addi    r4, r1, 0x10
/* 0078B4 8000CE54 480A5BE1 */  bl      DVDOpen
/* 0078B8 8000CE58 2C030001 */  cmpwi   r3, 1
/* 0078BC 8000CE5C 40820024 */  bne     lbl_8000CE80
/* 0078C0 8000CE60 80AD8088 */  lwz     r5, gmsg_sv06_5Size@sda21(r13)
/* 0078C4 8000CE64 38610010 */  addi    r3, r1, 0x10
/* 0078C8 8000CE68 389F01A0 */  addi    r4, r31, 0x1a0
/* 0078CC 8000CE6C 3805001F */  addi    r0, r5, 0x1f
/* 0078D0 8000CE70 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0078D4 8000CE74 38C00000 */  li      r6, 0
/* 0078D8 8000CE78 38E00000 */  li      r7, 0
/* 0078DC 8000CE7C 48001E49 */  bl      simulatorDVDRead
lbl_8000CE80:
/* 0078E0 8000CE80 38610010 */  addi    r3, r1, 0x10
/* 0078E4 8000CE84 480A5C79 */  bl      DVDClose
/* 0078E8 8000CE88 387F01A0 */  addi    r3, r31, 0x1a0
/* 0078EC 8000CE8C 48002195 */  bl      simulatorUnpackTexPalette
lbl_8000CE90:
/* 0078F0 8000CE90 387F01A0 */  addi    r3, r31, 0x1a0
/* 0078F4 8000CE94 389E0000 */  addi    r4, r30, 0
/* 0078F8 8000CE98 4800008D */  bl      simulatorDrawYesNoMessageLoop
/* 0078FC 8000CE9C 48000070 */  b       lbl_8000CF0C
.global lbl_8000CEA0
lbl_8000CEA0:
/* 007900 8000CEA0 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007904 8000CEA4 7C001800 */  cmpw    r0, r3
/* 007908 8000CEA8 41820050 */  beq     lbl_8000CEF8
/* 00790C 8000CEAC 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007910 8000CEB0 3C650001 */  addis   r3, r5, 1
/* 007914 8000CEB4 3863E888 */  addi    r3, r3, -6008
/* 007918 8000CEB8 38810010 */  addi    r4, r1, 0x10
/* 00791C 8000CEBC 480A5B79 */  bl      DVDOpen
/* 007920 8000CEC0 2C030001 */  cmpwi   r3, 1
/* 007924 8000CEC4 40820024 */  bne     lbl_8000CEE8
/* 007928 8000CEC8 80AD8090 */  lwz     r5, gmsg_sv08Size@sda21(r13)
/* 00792C 8000CECC 38610010 */  addi    r3, r1, 0x10
/* 007930 8000CED0 389F01A0 */  addi    r4, r31, 0x1a0
/* 007934 8000CED4 3805001F */  addi    r0, r5, 0x1f
/* 007938 8000CED8 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 00793C 8000CEDC 38C00000 */  li      r6, 0
/* 007940 8000CEE0 38E00000 */  li      r7, 0
/* 007944 8000CEE4 48001DE1 */  bl      simulatorDVDRead
lbl_8000CEE8:
/* 007948 8000CEE8 38610010 */  addi    r3, r1, 0x10
/* 00794C 8000CEEC 480A5C11 */  bl      DVDClose
/* 007950 8000CEF0 387F01A0 */  addi    r3, r31, 0x1a0
/* 007954 8000CEF4 4800212D */  bl      simulatorUnpackTexPalette
lbl_8000CEF8:
/* 007958 8000CEF8 387F01A0 */  addi    r3, r31, 0x1a0
/* 00795C 8000CEFC 389E0000 */  addi    r4, r30, 0
/* 007960 8000CF00 48000025 */  bl      simulatorDrawYesNoMessageLoop
/* 007964 8000CF04 48000008 */  b       lbl_8000CF0C
.global lbl_8000CF08
lbl_8000CF08:
/* 007968 8000CF08 38600000 */  li      r3, 0
lbl_8000CF0C:
/* 00796C 8000CF0C 8001005C */  lwz     r0, 0x5c(r1)
/* 007970 8000CF10 83E10054 */  lwz     r31, 0x54(r1)
/* 007974 8000CF14 83C10050 */  lwz     r30, 0x50(r1)
/* 007978 8000CF18 7C0803A6 */  mtlr    r0
/* 00797C 8000CF1C 38210058 */  addi    r1, r1, 0x58
/* 007980 8000CF20 4E800020 */  blr     
