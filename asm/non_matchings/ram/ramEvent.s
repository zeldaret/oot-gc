glabel ramEvent
/* 0677F8 8006CD98 7C0802A6 */  mflr    r0
/* 0677FC 8006CD9C 2C040003 */  cmpwi   r4, 3
/* 067800 8006CDA0 90010004 */  stw     r0, 4(r1)
/* 067804 8006CDA4 9421FFE0 */  stwu    r1, -0x20(r1)
/* 067808 8006CDA8 93E1001C */  stw     r31, 0x1c(r1)
/* 06780C 8006CDAC 3BE50000 */  addi    r31, r5, 0
/* 067810 8006CDB0 93C10018 */  stw     r30, 0x18(r1)
/* 067814 8006CDB4 3BC30000 */  addi    r30, r3, 0
/* 067818 8006CDB8 418201FC */  beq     lbl_8006CFB4
/* 06781C 8006CDBC 40800018 */  bge     lbl_8006CDD4
/* 067820 8006CDC0 2C040002 */  cmpwi   r4, 2
/* 067824 8006CDC4 40800028 */  bge     lbl_8006CDEC
/* 067828 8006CDC8 2C040000 */  cmpwi   r4, 0
/* 06782C 8006CDCC 408001E8 */  bge     lbl_8006CFB4
/* 067830 8006CDD0 480001DC */  b       lbl_8006CFAC
lbl_8006CDD4:
/* 067834 8006CDD4 2C041003 */  cmpwi   r4, 0x1003
/* 067838 8006CDD8 418201DC */  beq     lbl_8006CFB4
/* 06783C 8006CDDC 408001D0 */  bge     lbl_8006CFAC
/* 067840 8006CDE0 2C041002 */  cmpwi   r4, 0x1002
/* 067844 8006CDE4 4080001C */  bge     lbl_8006CE00
/* 067848 8006CDE8 480001C4 */  b       lbl_8006CFAC
lbl_8006CDEC:
/* 06784C 8006CDEC 38000000 */  li      r0, 0
/* 067850 8006CDF0 901E0008 */  stw     r0, 8(r30)
/* 067854 8006CDF4 901E0004 */  stw     r0, 4(r30)
/* 067858 8006CDF8 93FE0000 */  stw     r31, 0(r30)
/* 06785C 8006CDFC 480001B8 */  b       lbl_8006CFB4
lbl_8006CE00:
/* 067860 8006CE00 801F0000 */  lwz     r0, 0(r31)
/* 067864 8006CE04 5400063E */  clrlwi  r0, r0, 0x18
/* 067868 8006CE08 2C000001 */  cmpwi   r0, 1
/* 06786C 8006CE0C 418200A0 */  beq     lbl_8006CEAC
/* 067870 8006CE10 40800010 */  bge     lbl_8006CE20
/* 067874 8006CE14 2C000000 */  cmpwi   r0, 0
/* 067878 8006CE18 40800014 */  bge     lbl_8006CE2C
/* 06787C 8006CE1C 48000198 */  b       lbl_8006CFB4
lbl_8006CE20:
/* 067880 8006CE20 2C000003 */  cmpwi   r0, 3
/* 067884 8006CE24 40800190 */  bge     lbl_8006CFB4
/* 067888 8006CE28 48000104 */  b       lbl_8006CF2C
lbl_8006CE2C:
/* 06788C 8006CE2C 807E0000 */  lwz     r3, 0(r30)
/* 067890 8006CE30 3CA08007 */  lis     r5, ramPut8@ha
/* 067894 8006CE34 3CC08007 */  lis     r6, ramPut16@ha
/* 067898 8006CE38 3CE08007 */  lis     r7, ramPut32@ha
/* 06789C 8006CE3C 80630024 */  lwz     r3, 0x24(r3)
/* 0678A0 8006CE40 3C808007 */  lis     r4, ramPut64@ha
/* 0678A4 8006CE44 3904D1D4 */  addi    r8, r4, ramPut64@l
/* 0678A8 8006CE48 38A5D258 */  addi    r5, r5, ramPut8@l
/* 0678AC 8006CE4C 38C6D230 */  addi    r6, r6, ramPut16@l
/* 0678B0 8006CE50 38E7D208 */  addi    r7, r7, ramPut32@l
/* 0678B4 8006CE54 389F0000 */  addi    r4, r31, 0
/* 0678B8 8006CE58 4BFC81E1 */  bl      cpuSetDevicePut
/* 0678BC 8006CE5C 2C030000 */  cmpwi   r3, 0
/* 0678C0 8006CE60 4082000C */  bne     lbl_8006CE6C
/* 0678C4 8006CE64 38600000 */  li      r3, 0
/* 0678C8 8006CE68 48000150 */  b       lbl_8006CFB8
lbl_8006CE6C:
/* 0678CC 8006CE6C 807E0000 */  lwz     r3, 0(r30)
/* 0678D0 8006CE70 3CA08007 */  lis     r5, ramGet8@ha
/* 0678D4 8006CE74 3CC08007 */  lis     r6, ramGet16@ha
/* 0678D8 8006CE78 3CE08007 */  lis     r7, ramGet32@ha
/* 0678DC 8006CE7C 80630024 */  lwz     r3, 0x24(r3)
/* 0678E0 8006CE80 3C808007 */  lis     r4, ramGet64@ha
/* 0678E4 8006CE84 3904D0F8 */  addi    r8, r4, ramGet64@l
/* 0678E8 8006CE88 38A5D1A4 */  addi    r5, r5, ramGet8@l
/* 0678EC 8006CE8C 38C6D170 */  addi    r6, r6, ramGet16@l
/* 0678F0 8006CE90 38E7D13C */  addi    r7, r7, ramGet32@l
/* 0678F4 8006CE94 389F0000 */  addi    r4, r31, 0
/* 0678F8 8006CE98 4BFC81B9 */  bl      cpuSetDeviceGet
/* 0678FC 8006CE9C 2C030000 */  cmpwi   r3, 0
/* 067900 8006CEA0 40820114 */  bne     lbl_8006CFB4
/* 067904 8006CEA4 38600000 */  li      r3, 0
/* 067908 8006CEA8 48000110 */  b       lbl_8006CFB8
lbl_8006CEAC:
/* 06790C 8006CEAC 807E0000 */  lwz     r3, 0(r30)
/* 067910 8006CEB0 3CA08007 */  lis     r5, ramPutRI8@ha
/* 067914 8006CEB4 3CC08007 */  lis     r6, ramPutRI16@ha
/* 067918 8006CEB8 3CE08007 */  lis     r7, ramPutRI32@ha
/* 06791C 8006CEBC 80630024 */  lwz     r3, 0x24(r3)
/* 067920 8006CEC0 3C808007 */  lis     r4, ramPutRI64@ha
/* 067924 8006CEC4 3904D2C8 */  addi    r8, r4, ramPutRI64@l
/* 067928 8006CEC8 38A5D30C */  addi    r5, r5, ramPutRI8@l
/* 06792C 8006CECC 38C6D304 */  addi    r6, r6, ramPutRI16@l
/* 067930 8006CED0 38E7D2D0 */  addi    r7, r7, ramPutRI32@l
/* 067934 8006CED4 389F0000 */  addi    r4, r31, 0
/* 067938 8006CED8 4BFC8161 */  bl      cpuSetDevicePut
/* 06793C 8006CEDC 2C030000 */  cmpwi   r3, 0
/* 067940 8006CEE0 4082000C */  bne     lbl_8006CEEC
/* 067944 8006CEE4 38600000 */  li      r3, 0
/* 067948 8006CEE8 480000D0 */  b       lbl_8006CFB8
lbl_8006CEEC:
/* 06794C 8006CEEC 807E0000 */  lwz     r3, 0(r30)
/* 067950 8006CEF0 3CA08007 */  lis     r5, ramGetRI8@ha
/* 067954 8006CEF4 3CC08007 */  lis     r6, ramGetRI16@ha
/* 067958 8006CEF8 3CE08007 */  lis     r7, ramGetRI32@ha
/* 06795C 8006CEFC 80630024 */  lwz     r3, 0x24(r3)
/* 067960 8006CF00 3C808007 */  lis     r4, ramGetRI64@ha
/* 067964 8006CF04 3904D27C */  addi    r8, r4, ramGetRI64@l
/* 067968 8006CF08 38A5D2C0 */  addi    r5, r5, ramGetRI8@l
/* 06796C 8006CF0C 38C6D2B8 */  addi    r6, r6, ramGetRI16@l
/* 067970 8006CF10 38E7D284 */  addi    r7, r7, ramGetRI32@l
/* 067974 8006CF14 389F0000 */  addi    r4, r31, 0
/* 067978 8006CF18 4BFC8139 */  bl      cpuSetDeviceGet
/* 06797C 8006CF1C 2C030000 */  cmpwi   r3, 0
/* 067980 8006CF20 40820094 */  bne     lbl_8006CFB4
/* 067984 8006CF24 38600000 */  li      r3, 0
/* 067988 8006CF28 48000090 */  b       lbl_8006CFB8
lbl_8006CF2C:
/* 06798C 8006CF2C 807E0000 */  lwz     r3, 0(r30)
/* 067990 8006CF30 3CA08007 */  lis     r5, ramPutControl8@ha
/* 067994 8006CF34 3CC08007 */  lis     r6, ramPutControl16@ha
/* 067998 8006CF38 3CE08007 */  lis     r7, ramPutControl32@ha
/* 06799C 8006CF3C 80630024 */  lwz     r3, 0x24(r3)
/* 0679A0 8006CF40 3C808007 */  lis     r4, ramPutControl64@ha
/* 0679A4 8006CF44 3904D360 */  addi    r8, r4, ramPutControl64@l
/* 0679A8 8006CF48 38A5D3A4 */  addi    r5, r5, ramPutControl8@l
/* 0679AC 8006CF4C 38C6D39C */  addi    r6, r6, ramPutControl16@l
/* 0679B0 8006CF50 38E7D368 */  addi    r7, r7, ramPutControl32@l
/* 0679B4 8006CF54 389F0000 */  addi    r4, r31, 0
/* 0679B8 8006CF58 4BFC80E1 */  bl      cpuSetDevicePut
/* 0679BC 8006CF5C 2C030000 */  cmpwi   r3, 0
/* 0679C0 8006CF60 4082000C */  bne     lbl_8006CF6C
/* 0679C4 8006CF64 38600000 */  li      r3, 0
/* 0679C8 8006CF68 48000050 */  b       lbl_8006CFB8
lbl_8006CF6C:
/* 0679CC 8006CF6C 807E0000 */  lwz     r3, 0(r30)
/* 0679D0 8006CF70 3CA08007 */  lis     r5, ramGetControl8@ha
/* 0679D4 8006CF74 3CC08007 */  lis     r6, ramGetControl16@ha
/* 0679D8 8006CF78 3CE08007 */  lis     r7, ramGetControl32@ha
/* 0679DC 8006CF7C 80630024 */  lwz     r3, 0x24(r3)
/* 0679E0 8006CF80 3C808007 */  lis     r4, ramGetControl64@ha
/* 0679E4 8006CF84 3904D314 */  addi    r8, r4, ramGetControl64@l
/* 0679E8 8006CF88 38A5D358 */  addi    r5, r5, ramGetControl8@l
/* 0679EC 8006CF8C 38C6D350 */  addi    r6, r6, ramGetControl16@l
/* 0679F0 8006CF90 38E7D31C */  addi    r7, r7, ramGetControl32@l
/* 0679F4 8006CF94 389F0000 */  addi    r4, r31, 0
/* 0679F8 8006CF98 4BFC80B9 */  bl      cpuSetDeviceGet
/* 0679FC 8006CF9C 2C030000 */  cmpwi   r3, 0
/* 067A00 8006CFA0 40820014 */  bne     lbl_8006CFB4
/* 067A04 8006CFA4 38600000 */  li      r3, 0
/* 067A08 8006CFA8 48000010 */  b       lbl_8006CFB8
lbl_8006CFAC:
/* 067A0C 8006CFAC 38600000 */  li      r3, 0
/* 067A10 8006CFB0 48000008 */  b       lbl_8006CFB8
lbl_8006CFB4:
/* 067A14 8006CFB4 38600001 */  li      r3, 1
lbl_8006CFB8:
/* 067A18 8006CFB8 80010024 */  lwz     r0, 0x24(r1)
/* 067A1C 8006CFBC 83E1001C */  lwz     r31, 0x1c(r1)
/* 067A20 8006CFC0 83C10018 */  lwz     r30, 0x18(r1)
/* 067A24 8006CFC4 7C0803A6 */  mtlr    r0
/* 067A28 8006CFC8 38210020 */  addi    r1, r1, 0x20
/* 067A2C 8006CFCC 4E800020 */  blr     
