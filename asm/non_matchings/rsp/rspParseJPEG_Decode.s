glabel rspParseJPEG_Decode
/* 077F20 8007D4C0 7C0802A6 */  mflr    r0
/* 077F24 8007D4C4 90010004 */  stw     r0, 4(r1)
/* 077F28 8007D4C8 9421FFA0 */  stwu    r1, -0x60(r1)
/* 077F2C 8007D4CC BE810030 */  stmw    r20, 0x30(r1)
/* 077F30 8007D4D0 3BC30000 */  addi    r30, r3, 0
/* 077F34 8007D4D4 3A840000 */  addi    r20, r4, 0
/* 077F38 8007D4D8 48002CE9 */  bl      rspCreateJPEGArrays
/* 077F3C 8007D4DC 807E38E8 */  lwz     r3, 0x38e8(r30)
/* 077F40 8007D4E0 3881001C */  addi    r4, r1, 0x1c
/* 077F44 8007D4E4 80B40030 */  lwz     r5, 0x30(r20)
/* 077F48 8007D4E8 38C00000 */  li      r6, 0
/* 077F4C 8007D4EC 8063002C */  lwz     r3, 0x2c(r3)
/* 077F50 8007D4F0 4BFEFBB1 */  bl      ramGetBuffer
/* 077F54 8007D4F4 2C030000 */  cmpwi   r3, 0
/* 077F58 8007D4F8 4082000C */  bne     lbl_8007D504
/* 077F5C 8007D4FC 38600000 */  li      r3, 0
/* 077F60 8007D500 480007F8 */  b       lbl_8007DCF8
lbl_8007D504:
/* 077F64 8007D504 83E1001C */  lwz     r31, 0x1c(r1)
/* 077F68 8007D508 3BA00000 */  li      r29, 0
/* 077F6C 8007D50C 82B40034 */  lwz     r21, 0x34(r20)
/* 077F70 8007D510 7FB7EB78 */  mr      r23, r29
/* 077F74 8007D514 82D4003C */  lwz     r22, 0x3c(r20)
/* 077F78 8007D518 3B1D0000 */  addi    r24, r29, 0
/* 077F7C 8007D51C 3B5F0000 */  addi    r26, r31, 0
/* 077F80 8007D520 3B200000 */  li      r25, 0
/* 077F84 8007D524 3B80003F */  li      r28, 0x3f
/* 077F88 8007D528 3B600038 */  li      r27, 0x38
/* 077F8C 8007D52C 4800079C */  b       lbl_8007DCC8
lbl_8007D530:
/* 077F90 8007D530 38C00000 */  li      r6, 0
/* 077F94 8007D534 38E60000 */  addi    r7, r6, 0
/* 077F98 8007D538 38600000 */  li      r3, 0
lbl_8007D53C:
/* 077F9C 8007D53C 881F0000 */  lbz     r0, 0(r31)
/* 077FA0 8007D540 2C1C0008 */  cmpwi   r28, 8
/* 077FA4 8007D544 88BF0001 */  lbz     r5, 1(r31)
/* 077FA8 8007D548 3BFF0002 */  addi    r31, r31, 2
/* 077FAC 8007D54C 5005442E */  rlwimi  r5, r0, 8, 0x10, 0x17
/* 077FB0 8007D550 7CA50734 */  extsh   r5, r5
/* 077FB4 8007D554 809E39C8 */  lwz     r4, 0x39c8(r30)
/* 077FB8 8007D558 7C05EA14 */  add     r0, r5, r29
/* 077FBC 8007D55C 7C04312E */  stwx    r0, r4, r6
/* 077FC0 8007D560 7FBD2A14 */  add     r29, r29, r5
/* 077FC4 8007D564 38800001 */  li      r4, 1
/* 077FC8 8007D568 40810770 */  ble     lbl_8007DCD8
/* 077FCC 8007D56C 3800003E */  li      r0, 0x3e
/* 077FD0 8007D570 5400E8FE */  srwi    r0, r0, 3
/* 077FD4 8007D574 2C1B0001 */  cmpwi   r27, 1
/* 077FD8 8007D578 7C0903A6 */  mtctr   r0
/* 077FDC 8007D57C 38A00004 */  li      r5, 4
/* 077FE0 8007D580 40810758 */  ble     lbl_8007DCD8
lbl_8007D584:
/* 077FE4 8007D584 813E39BC */  lwz     r9, 0x39bc(r30)
/* 077FE8 8007D588 39050004 */  addi    r8, r5, 4
/* 077FEC 8007D58C 897F0000 */  lbz     r11, 0(r31)
/* 077FF0 8007D590 7C09282E */  lwzx    r0, r9, r5
/* 077FF4 8007D594 899F0001 */  lbz     r12, 1(r31)
/* 077FF8 8007D598 516C442E */  rlwimi  r12, r11, 8, 0x10, 0x17
/* 077FFC 8007D59C 7C091E70 */  srawi   r9, r0, 3
/* 078000 8007D5A0 815E39C8 */  lwz     r10, 0x39c8(r30)
/* 078004 8007D5A4 54001EB8 */  rlwinm  r0, r0, 3, 0x1a, 0x1c
/* 078008 8007D5A8 7C004A14 */  add     r0, r0, r9
/* 07800C 8007D5AC 7C070214 */  add     r0, r7, r0
/* 078010 8007D5B0 7D890734 */  extsh   r9, r12
/* 078014 8007D5B4 5400103A */  slwi    r0, r0, 2
/* 078018 8007D5B8 7D2A012E */  stwx    r9, r10, r0
/* 07801C 8007D5BC 39450008 */  addi    r10, r5, 8
/* 078020 8007D5C0 3925000C */  addi    r9, r5, 0xc
/* 078024 8007D5C4 817E39BC */  lwz     r11, 0x39bc(r30)
/* 078028 8007D5C8 881F0002 */  lbz     r0, 2(r31)
/* 07802C 8007D5CC 7D8B402E */  lwzx    r12, r11, r8
/* 078030 8007D5D0 8A9F0003 */  lbz     r20, 3(r31)
/* 078034 8007D5D4 5014442E */  rlwimi  r20, r0, 8, 0x10, 0x17
/* 078038 8007D5D8 7D881E70 */  srawi   r8, r12, 3
/* 07803C 8007D5DC 817E39C8 */  lwz     r11, 0x39c8(r30)
/* 078040 8007D5E0 55801EB8 */  rlwinm  r0, r12, 3, 0x1a, 0x1c
/* 078044 8007D5E4 7C004214 */  add     r0, r0, r8
/* 078048 8007D5E8 7C070214 */  add     r0, r7, r0
/* 07804C 8007D5EC 7E880734 */  extsh   r8, r20
/* 078050 8007D5F0 5400103A */  slwi    r0, r0, 2
/* 078054 8007D5F4 7D0B012E */  stwx    r8, r11, r0
/* 078058 8007D5F8 39050010 */  addi    r8, r5, 0x10
/* 07805C 8007D5FC 817E39BC */  lwz     r11, 0x39bc(r30)
/* 078060 8007D600 881F0004 */  lbz     r0, 4(r31)
/* 078064 8007D604 7D8B502E */  lwzx    r12, r11, r10
/* 078068 8007D608 8A9F0005 */  lbz     r20, 5(r31)
/* 07806C 8007D60C 5014442E */  rlwimi  r20, r0, 8, 0x10, 0x17
/* 078070 8007D610 7D8A1E70 */  srawi   r10, r12, 3
/* 078074 8007D614 817E39C8 */  lwz     r11, 0x39c8(r30)
/* 078078 8007D618 55801EB8 */  rlwinm  r0, r12, 3, 0x1a, 0x1c
/* 07807C 8007D61C 7C005214 */  add     r0, r0, r10
/* 078080 8007D620 7C070214 */  add     r0, r7, r0
/* 078084 8007D624 7E8A0734 */  extsh   r10, r20
/* 078088 8007D628 5400103A */  slwi    r0, r0, 2
/* 07808C 8007D62C 7D4B012E */  stwx    r10, r11, r0
/* 078090 8007D630 815E39BC */  lwz     r10, 0x39bc(r30)
/* 078094 8007D634 881F0006 */  lbz     r0, 6(r31)
/* 078098 8007D638 7D6A482E */  lwzx    r11, r10, r9
/* 07809C 8007D63C 899F0007 */  lbz     r12, 7(r31)
/* 0780A0 8007D640 500C442E */  rlwimi  r12, r0, 8, 0x10, 0x17
/* 0780A4 8007D644 7D691E70 */  srawi   r9, r11, 3
/* 0780A8 8007D648 815E39C8 */  lwz     r10, 0x39c8(r30)
/* 0780AC 8007D64C 55601EB8 */  rlwinm  r0, r11, 3, 0x1a, 0x1c
/* 0780B0 8007D650 7C004A14 */  add     r0, r0, r9
/* 0780B4 8007D654 7C070214 */  add     r0, r7, r0
/* 0780B8 8007D658 7D890734 */  extsh   r9, r12
/* 0780BC 8007D65C 5400103A */  slwi    r0, r0, 2
/* 0780C0 8007D660 7D2A012E */  stwx    r9, r10, r0
/* 0780C4 8007D664 813E39BC */  lwz     r9, 0x39bc(r30)
/* 0780C8 8007D668 881F0008 */  lbz     r0, 8(r31)
/* 0780CC 8007D66C 7D49402E */  lwzx    r10, r9, r8
/* 0780D0 8007D670 897F0009 */  lbz     r11, 9(r31)
/* 0780D4 8007D674 500B442E */  rlwimi  r11, r0, 8, 0x10, 0x17
/* 0780D8 8007D678 7D481E70 */  srawi   r8, r10, 3
/* 0780DC 8007D67C 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 0780E0 8007D680 55401EB8 */  rlwinm  r0, r10, 3, 0x1a, 0x1c
/* 0780E4 8007D684 7C004214 */  add     r0, r0, r8
/* 0780E8 8007D688 7C070214 */  add     r0, r7, r0
/* 0780EC 8007D68C 7D680734 */  extsh   r8, r11
/* 0780F0 8007D690 5400103A */  slwi    r0, r0, 2
/* 0780F4 8007D694 7D09012E */  stwx    r8, r9, r0
/* 0780F8 8007D698 3BFF000A */  addi    r31, r31, 0xa
/* 0780FC 8007D69C 811E39BC */  lwz     r8, 0x39bc(r30)
/* 078100 8007D6A0 38050014 */  addi    r0, r5, 0x14
/* 078104 8007D6A4 895F0000 */  lbz     r10, 0(r31)
/* 078108 8007D6A8 38840008 */  addi    r4, r4, 8
/* 07810C 8007D6AC 7C08002E */  lwzx    r0, r8, r0
/* 078110 8007D6B0 897F0001 */  lbz     r11, 1(r31)
/* 078114 8007D6B4 514B442E */  rlwimi  r11, r10, 8, 0x10, 0x17
/* 078118 8007D6B8 7C081E70 */  srawi   r8, r0, 3
/* 07811C 8007D6BC 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 078120 8007D6C0 54001EB8 */  rlwinm  r0, r0, 3, 0x1a, 0x1c
/* 078124 8007D6C4 7C004214 */  add     r0, r0, r8
/* 078128 8007D6C8 7C070214 */  add     r0, r7, r0
/* 07812C 8007D6CC 7D680734 */  extsh   r8, r11
/* 078130 8007D6D0 5400103A */  slwi    r0, r0, 2
/* 078134 8007D6D4 7D09012E */  stwx    r8, r9, r0
/* 078138 8007D6D8 39250018 */  addi    r9, r5, 0x18
/* 07813C 8007D6DC 3905001C */  addi    r8, r5, 0x1c
/* 078140 8007D6E0 815E39BC */  lwz     r10, 0x39bc(r30)
/* 078144 8007D6E4 38A50020 */  addi    r5, r5, 0x20
/* 078148 8007D6E8 881F0002 */  lbz     r0, 2(r31)
/* 07814C 8007D6EC 7D6A482E */  lwzx    r11, r10, r9
/* 078150 8007D6F0 899F0003 */  lbz     r12, 3(r31)
/* 078154 8007D6F4 500C442E */  rlwimi  r12, r0, 8, 0x10, 0x17
/* 078158 8007D6F8 7D691E70 */  srawi   r9, r11, 3
/* 07815C 8007D6FC 815E39C8 */  lwz     r10, 0x39c8(r30)
/* 078160 8007D700 55601EB8 */  rlwinm  r0, r11, 3, 0x1a, 0x1c
/* 078164 8007D704 7C004A14 */  add     r0, r0, r9
/* 078168 8007D708 7C070214 */  add     r0, r7, r0
/* 07816C 8007D70C 7D890734 */  extsh   r9, r12
/* 078170 8007D710 5400103A */  slwi    r0, r0, 2
/* 078174 8007D714 7D2A012E */  stwx    r9, r10, r0
/* 078178 8007D718 813E39BC */  lwz     r9, 0x39bc(r30)
/* 07817C 8007D71C 881F0004 */  lbz     r0, 4(r31)
/* 078180 8007D720 7D49402E */  lwzx    r10, r9, r8
/* 078184 8007D724 897F0005 */  lbz     r11, 5(r31)
/* 078188 8007D728 500B442E */  rlwimi  r11, r0, 8, 0x10, 0x17
/* 07818C 8007D72C 7D481E70 */  srawi   r8, r10, 3
/* 078190 8007D730 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 078194 8007D734 55401EB8 */  rlwinm  r0, r10, 3, 0x1a, 0x1c
/* 078198 8007D738 7C004214 */  add     r0, r0, r8
/* 07819C 8007D73C 7C070214 */  add     r0, r7, r0
/* 0781A0 8007D740 7D680734 */  extsh   r8, r11
/* 0781A4 8007D744 5400103A */  slwi    r0, r0, 2
/* 0781A8 8007D748 7D09012E */  stwx    r8, r9, r0
/* 0781AC 8007D74C 3BFF0006 */  addi    r31, r31, 6
/* 0781B0 8007D750 4200FE34 */  bdnz    lbl_8007D584
/* 0781B4 8007D754 48000584 */  b       lbl_8007DCD8
lbl_8007D758:
/* 0781B8 8007D758 20040040 */  subfic  r0, r4, 0x40
/* 0781BC 8007D75C 2C040040 */  cmpwi   r4, 0x40
/* 0781C0 8007D760 7C0903A6 */  mtctr   r0
/* 0781C4 8007D764 40800044 */  bge     lbl_8007D7A8
lbl_8007D768:
/* 0781C8 8007D768 809E39BC */  lwz     r4, 0x39bc(r30)
/* 0781CC 8007D76C 891F0000 */  lbz     r8, 0(r31)
/* 0781D0 8007D770 7C04482E */  lwzx    r0, r4, r9
/* 0781D4 8007D774 39290004 */  addi    r9, r9, 4
/* 0781D8 8007D778 895F0001 */  lbz     r10, 1(r31)
/* 0781DC 8007D77C 510A442E */  rlwimi  r10, r8, 8, 0x10, 0x17
/* 0781E0 8007D780 7C041E70 */  srawi   r4, r0, 3
/* 0781E4 8007D784 54001EB8 */  rlwinm  r0, r0, 3, 0x1a, 0x1c
/* 0781E8 8007D788 80BE39C8 */  lwz     r5, 0x39c8(r30)
/* 0781EC 8007D78C 7C002214 */  add     r0, r0, r4
/* 0781F0 8007D790 7C070214 */  add     r0, r7, r0
/* 0781F4 8007D794 7D440734 */  extsh   r4, r10
/* 0781F8 8007D798 5400103A */  slwi    r0, r0, 2
/* 0781FC 8007D79C 7C85012E */  stwx    r4, r5, r0
/* 078200 8007D7A0 3BFF0002 */  addi    r31, r31, 2
/* 078204 8007D7A4 4200FFC4 */  bdnz    lbl_8007D768
lbl_8007D7A8:
/* 078208 8007D7A8 38630001 */  addi    r3, r3, 1
/* 07820C 8007D7AC 2C030004 */  cmpwi   r3, 4
/* 078210 8007D7B0 38C60100 */  addi    r6, r6, 0x100
/* 078214 8007D7B4 38E70040 */  addi    r7, r7, 0x40
/* 078218 8007D7B8 4180FD84 */  blt     lbl_8007D53C
/* 07821C 8007D7BC 889F0000 */  lbz     r4, 0(r31)
/* 078220 8007D7C0 2C1C0008 */  cmpwi   r28, 8
/* 078224 8007D7C4 88DF0001 */  lbz     r6, 1(r31)
/* 078228 8007D7C8 38030000 */  addi    r0, r3, 0
/* 07822C 8007D7CC 5086442E */  rlwimi  r6, r4, 8, 0x10, 0x17
/* 078230 8007D7D0 7CC70734 */  extsh   r7, r6
/* 078234 8007D7D4 80BE39C8 */  lwz     r5, 0x39c8(r30)
/* 078238 8007D7D8 7CC7BA14 */  add     r6, r7, r23
/* 07823C 8007D7DC 5464402E */  slwi    r4, r3, 8
/* 078240 8007D7E0 7CC5212E */  stwx    r6, r5, r4
/* 078244 8007D7E4 7EF73A14 */  add     r23, r23, r7
/* 078248 8007D7E8 38800001 */  li      r4, 1
/* 07824C 8007D7EC 38630001 */  addi    r3, r3, 1
/* 078250 8007D7F0 3BFF0002 */  addi    r31, r31, 2
/* 078254 8007D7F4 408104EC */  ble     lbl_8007DCE0
/* 078258 8007D7F8 38A00007 */  li      r5, 7
/* 07825C 8007D7FC 7CA903A6 */  mtctr   r5
/* 078260 8007D800 54063032 */  slwi    r6, r0, 6
/* 078264 8007D804 38A00004 */  li      r5, 4
lbl_8007D808:
/* 078268 8007D808 80FE39BC */  lwz     r7, 0x39bc(r30)
/* 07826C 8007D80C 39050004 */  addi    r8, r5, 4
/* 078270 8007D810 897F0000 */  lbz     r11, 0(r31)
/* 078274 8007D814 7CE7282E */  lwzx    r7, r7, r5
/* 078278 8007D818 899F0001 */  lbz     r12, 1(r31)
/* 07827C 8007D81C 516C442E */  rlwimi  r12, r11, 8, 0x10, 0x17
/* 078280 8007D820 7CE91E70 */  srawi   r9, r7, 3
/* 078284 8007D824 815E39C8 */  lwz     r10, 0x39c8(r30)
/* 078288 8007D828 54E71EB8 */  rlwinm  r7, r7, 3, 0x1a, 0x1c
/* 07828C 8007D82C 7CE74A14 */  add     r7, r7, r9
/* 078290 8007D830 7CE63A14 */  add     r7, r6, r7
/* 078294 8007D834 7D890734 */  extsh   r9, r12
/* 078298 8007D838 54E7103A */  slwi    r7, r7, 2
/* 07829C 8007D83C 7D2A392E */  stwx    r9, r10, r7
/* 0782A0 8007D840 39450008 */  addi    r10, r5, 8
/* 0782A4 8007D844 3925000C */  addi    r9, r5, 0xc
/* 0782A8 8007D848 817E39BC */  lwz     r11, 0x39bc(r30)
/* 0782AC 8007D84C 88FF0002 */  lbz     r7, 2(r31)
/* 0782B0 8007D850 7D8B402E */  lwzx    r12, r11, r8
/* 0782B4 8007D854 8A9F0003 */  lbz     r20, 3(r31)
/* 0782B8 8007D858 50F4442E */  rlwimi  r20, r7, 8, 0x10, 0x17
/* 0782BC 8007D85C 7D881E70 */  srawi   r8, r12, 3
/* 0782C0 8007D860 817E39C8 */  lwz     r11, 0x39c8(r30)
/* 0782C4 8007D864 55871EB8 */  rlwinm  r7, r12, 3, 0x1a, 0x1c
/* 0782C8 8007D868 7CE74214 */  add     r7, r7, r8
/* 0782CC 8007D86C 7CE63A14 */  add     r7, r6, r7
/* 0782D0 8007D870 7E880734 */  extsh   r8, r20
/* 0782D4 8007D874 54E7103A */  slwi    r7, r7, 2
/* 0782D8 8007D878 7D0B392E */  stwx    r8, r11, r7
/* 0782DC 8007D87C 39050010 */  addi    r8, r5, 0x10
/* 0782E0 8007D880 817E39BC */  lwz     r11, 0x39bc(r30)
/* 0782E4 8007D884 88FF0004 */  lbz     r7, 4(r31)
/* 0782E8 8007D888 7D8B502E */  lwzx    r12, r11, r10
/* 0782EC 8007D88C 8A9F0005 */  lbz     r20, 5(r31)
/* 0782F0 8007D890 50F4442E */  rlwimi  r20, r7, 8, 0x10, 0x17
/* 0782F4 8007D894 7D8A1E70 */  srawi   r10, r12, 3
/* 0782F8 8007D898 817E39C8 */  lwz     r11, 0x39c8(r30)
/* 0782FC 8007D89C 55871EB8 */  rlwinm  r7, r12, 3, 0x1a, 0x1c
/* 078300 8007D8A0 7CE75214 */  add     r7, r7, r10
/* 078304 8007D8A4 7CE63A14 */  add     r7, r6, r7
/* 078308 8007D8A8 7E8A0734 */  extsh   r10, r20
/* 07830C 8007D8AC 54E7103A */  slwi    r7, r7, 2
/* 078310 8007D8B0 7D4B392E */  stwx    r10, r11, r7
/* 078314 8007D8B4 815E39BC */  lwz     r10, 0x39bc(r30)
/* 078318 8007D8B8 88FF0006 */  lbz     r7, 6(r31)
/* 07831C 8007D8BC 7D6A482E */  lwzx    r11, r10, r9
/* 078320 8007D8C0 899F0007 */  lbz     r12, 7(r31)
/* 078324 8007D8C4 50EC442E */  rlwimi  r12, r7, 8, 0x10, 0x17
/* 078328 8007D8C8 7D691E70 */  srawi   r9, r11, 3
/* 07832C 8007D8CC 815E39C8 */  lwz     r10, 0x39c8(r30)
/* 078330 8007D8D0 55671EB8 */  rlwinm  r7, r11, 3, 0x1a, 0x1c
/* 078334 8007D8D4 7CE74A14 */  add     r7, r7, r9
/* 078338 8007D8D8 7CE63A14 */  add     r7, r6, r7
/* 07833C 8007D8DC 7D890734 */  extsh   r9, r12
/* 078340 8007D8E0 54E7103A */  slwi    r7, r7, 2
/* 078344 8007D8E4 7D2A392E */  stwx    r9, r10, r7
/* 078348 8007D8E8 813E39BC */  lwz     r9, 0x39bc(r30)
/* 07834C 8007D8EC 88FF0008 */  lbz     r7, 8(r31)
/* 078350 8007D8F0 7D49402E */  lwzx    r10, r9, r8
/* 078354 8007D8F4 897F0009 */  lbz     r11, 9(r31)
/* 078358 8007D8F8 50EB442E */  rlwimi  r11, r7, 8, 0x10, 0x17
/* 07835C 8007D8FC 7D481E70 */  srawi   r8, r10, 3
/* 078360 8007D900 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 078364 8007D904 55471EB8 */  rlwinm  r7, r10, 3, 0x1a, 0x1c
/* 078368 8007D908 7CE74214 */  add     r7, r7, r8
/* 07836C 8007D90C 7CE63A14 */  add     r7, r6, r7
/* 078370 8007D910 7D680734 */  extsh   r8, r11
/* 078374 8007D914 54E7103A */  slwi    r7, r7, 2
/* 078378 8007D918 7D09392E */  stwx    r8, r9, r7
/* 07837C 8007D91C 3BFF000A */  addi    r31, r31, 0xa
/* 078380 8007D920 811E39BC */  lwz     r8, 0x39bc(r30)
/* 078384 8007D924 38E50014 */  addi    r7, r5, 0x14
/* 078388 8007D928 895F0000 */  lbz     r10, 0(r31)
/* 07838C 8007D92C 38840008 */  addi    r4, r4, 8
/* 078390 8007D930 7CE8382E */  lwzx    r7, r8, r7
/* 078394 8007D934 897F0001 */  lbz     r11, 1(r31)
/* 078398 8007D938 514B442E */  rlwimi  r11, r10, 8, 0x10, 0x17
/* 07839C 8007D93C 7CE81E70 */  srawi   r8, r7, 3
/* 0783A0 8007D940 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 0783A4 8007D944 54E71EB8 */  rlwinm  r7, r7, 3, 0x1a, 0x1c
/* 0783A8 8007D948 7CE74214 */  add     r7, r7, r8
/* 0783AC 8007D94C 7CE63A14 */  add     r7, r6, r7
/* 0783B0 8007D950 7D680734 */  extsh   r8, r11
/* 0783B4 8007D954 54E7103A */  slwi    r7, r7, 2
/* 0783B8 8007D958 7D09392E */  stwx    r8, r9, r7
/* 0783BC 8007D95C 39250018 */  addi    r9, r5, 0x18
/* 0783C0 8007D960 3905001C */  addi    r8, r5, 0x1c
/* 0783C4 8007D964 815E39BC */  lwz     r10, 0x39bc(r30)
/* 0783C8 8007D968 38A50020 */  addi    r5, r5, 0x20
/* 0783CC 8007D96C 88FF0002 */  lbz     r7, 2(r31)
/* 0783D0 8007D970 7D6A482E */  lwzx    r11, r10, r9
/* 0783D4 8007D974 899F0003 */  lbz     r12, 3(r31)
/* 0783D8 8007D978 50EC442E */  rlwimi  r12, r7, 8, 0x10, 0x17
/* 0783DC 8007D97C 7D691E70 */  srawi   r9, r11, 3
/* 0783E0 8007D980 815E39C8 */  lwz     r10, 0x39c8(r30)
/* 0783E4 8007D984 55671EB8 */  rlwinm  r7, r11, 3, 0x1a, 0x1c
/* 0783E8 8007D988 7CE74A14 */  add     r7, r7, r9
/* 0783EC 8007D98C 7CE63A14 */  add     r7, r6, r7
/* 0783F0 8007D990 7D890734 */  extsh   r9, r12
/* 0783F4 8007D994 54E7103A */  slwi    r7, r7, 2
/* 0783F8 8007D998 7D2A392E */  stwx    r9, r10, r7
/* 0783FC 8007D99C 813E39BC */  lwz     r9, 0x39bc(r30)
/* 078400 8007D9A0 88FF0004 */  lbz     r7, 4(r31)
/* 078404 8007D9A4 7D49402E */  lwzx    r10, r9, r8
/* 078408 8007D9A8 897F0005 */  lbz     r11, 5(r31)
/* 07840C 8007D9AC 50EB442E */  rlwimi  r11, r7, 8, 0x10, 0x17
/* 078410 8007D9B0 7D481E70 */  srawi   r8, r10, 3
/* 078414 8007D9B4 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 078418 8007D9B8 55471EB8 */  rlwinm  r7, r10, 3, 0x1a, 0x1c
/* 07841C 8007D9BC 7CE74214 */  add     r7, r7, r8
/* 078420 8007D9C0 7CE63A14 */  add     r7, r6, r7
/* 078424 8007D9C4 7D680734 */  extsh   r8, r11
/* 078428 8007D9C8 54E7103A */  slwi    r7, r7, 2
/* 07842C 8007D9CC 7D09392E */  stwx    r8, r9, r7
/* 078430 8007D9D0 3BFF0006 */  addi    r31, r31, 6
/* 078434 8007D9D4 4200FE34 */  bdnz    lbl_8007D808
/* 078438 8007D9D8 48000308 */  b       lbl_8007DCE0
lbl_8007D9DC:
/* 07843C 8007D9DC 20040040 */  subfic  r0, r4, 0x40
/* 078440 8007D9E0 2C040040 */  cmpwi   r4, 0x40
/* 078444 8007D9E4 7C0903A6 */  mtctr   r0
/* 078448 8007D9E8 40800044 */  bge     lbl_8007DA2C
lbl_8007D9EC:
/* 07844C 8007D9EC 809E39BC */  lwz     r4, 0x39bc(r30)
/* 078450 8007D9F0 88DF0000 */  lbz     r6, 0(r31)
/* 078454 8007D9F4 7C04382E */  lwzx    r0, r4, r7
/* 078458 8007D9F8 38E70004 */  addi    r7, r7, 4
/* 07845C 8007D9FC 893F0001 */  lbz     r9, 1(r31)
/* 078460 8007DA00 50C9442E */  rlwimi  r9, r6, 8, 0x10, 0x17
/* 078464 8007DA04 7C041E70 */  srawi   r4, r0, 3
/* 078468 8007DA08 54001EB8 */  rlwinm  r0, r0, 3, 0x1a, 0x1c
/* 07846C 8007DA0C 80BE39C8 */  lwz     r5, 0x39c8(r30)
/* 078470 8007DA10 7C002214 */  add     r0, r0, r4
/* 078474 8007DA14 7C080214 */  add     r0, r8, r0
/* 078478 8007DA18 7D240734 */  extsh   r4, r9
/* 07847C 8007DA1C 5400103A */  slwi    r0, r0, 2
/* 078480 8007DA20 7C85012E */  stwx    r4, r5, r0
/* 078484 8007DA24 3BFF0002 */  addi    r31, r31, 2
/* 078488 8007DA28 4200FFC4 */  bdnz    lbl_8007D9EC
lbl_8007DA2C:
/* 07848C 8007DA2C 889F0000 */  lbz     r4, 0(r31)
/* 078490 8007DA30 38030000 */  addi    r0, r3, 0
/* 078494 8007DA34 88BF0001 */  lbz     r5, 1(r31)
/* 078498 8007DA38 5463402E */  slwi    r3, r3, 8
/* 07849C 8007DA3C 5085442E */  rlwimi  r5, r4, 8, 0x10, 0x17
/* 0784A0 8007DA40 7CA60734 */  extsh   r6, r5
/* 0784A4 8007DA44 809E39C8 */  lwz     r4, 0x39c8(r30)
/* 0784A8 8007DA48 7CA6C214 */  add     r5, r6, r24
/* 0784AC 8007DA4C 7CA4192E */  stwx    r5, r4, r3
/* 0784B0 8007DA50 2C1C0008 */  cmpwi   r28, 8
/* 0784B4 8007DA54 7F183214 */  add     r24, r24, r6
/* 0784B8 8007DA58 38600001 */  li      r3, 1
/* 0784BC 8007DA5C 3BFF0002 */  addi    r31, r31, 2
/* 0784C0 8007DA60 4081028C */  ble     lbl_8007DCEC
/* 0784C4 8007DA64 38800007 */  li      r4, 7
/* 0784C8 8007DA68 7C8903A6 */  mtctr   r4
/* 0784CC 8007DA6C 54053032 */  slwi    r5, r0, 6
/* 0784D0 8007DA70 38800004 */  li      r4, 4
lbl_8007DA74:
/* 0784D4 8007DA74 80DE39BC */  lwz     r6, 0x39bc(r30)
/* 0784D8 8007DA78 38E40004 */  addi    r7, r4, 4
/* 0784DC 8007DA7C 895F0000 */  lbz     r10, 0(r31)
/* 0784E0 8007DA80 7CC6202E */  lwzx    r6, r6, r4
/* 0784E4 8007DA84 897F0001 */  lbz     r11, 1(r31)
/* 0784E8 8007DA88 514B442E */  rlwimi  r11, r10, 8, 0x10, 0x17
/* 0784EC 8007DA8C 7CC81E70 */  srawi   r8, r6, 3
/* 0784F0 8007DA90 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 0784F4 8007DA94 54C61EB8 */  rlwinm  r6, r6, 3, 0x1a, 0x1c
/* 0784F8 8007DA98 7CC64214 */  add     r6, r6, r8
/* 0784FC 8007DA9C 7CC53214 */  add     r6, r5, r6
/* 078500 8007DAA0 7D680734 */  extsh   r8, r11
/* 078504 8007DAA4 54C6103A */  slwi    r6, r6, 2
/* 078508 8007DAA8 7D09312E */  stwx    r8, r9, r6
/* 07850C 8007DAAC 39240008 */  addi    r9, r4, 8
/* 078510 8007DAB0 3904000C */  addi    r8, r4, 0xc
/* 078514 8007DAB4 815E39BC */  lwz     r10, 0x39bc(r30)
/* 078518 8007DAB8 88DF0002 */  lbz     r6, 2(r31)
/* 07851C 8007DABC 7D6A382E */  lwzx    r11, r10, r7
/* 078520 8007DAC0 899F0003 */  lbz     r12, 3(r31)
/* 078524 8007DAC4 50CC442E */  rlwimi  r12, r6, 8, 0x10, 0x17
/* 078528 8007DAC8 7D671E70 */  srawi   r7, r11, 3
/* 07852C 8007DACC 815E39C8 */  lwz     r10, 0x39c8(r30)
/* 078530 8007DAD0 55661EB8 */  rlwinm  r6, r11, 3, 0x1a, 0x1c
/* 078534 8007DAD4 7CC63A14 */  add     r6, r6, r7
/* 078538 8007DAD8 7CC53214 */  add     r6, r5, r6
/* 07853C 8007DADC 7D870734 */  extsh   r7, r12
/* 078540 8007DAE0 54C6103A */  slwi    r6, r6, 2
/* 078544 8007DAE4 7CEA312E */  stwx    r7, r10, r6
/* 078548 8007DAE8 38E40010 */  addi    r7, r4, 0x10
/* 07854C 8007DAEC 815E39BC */  lwz     r10, 0x39bc(r30)
/* 078550 8007DAF0 88DF0004 */  lbz     r6, 4(r31)
/* 078554 8007DAF4 7D6A482E */  lwzx    r11, r10, r9
/* 078558 8007DAF8 899F0005 */  lbz     r12, 5(r31)
/* 07855C 8007DAFC 50CC442E */  rlwimi  r12, r6, 8, 0x10, 0x17
/* 078560 8007DB00 7D691E70 */  srawi   r9, r11, 3
/* 078564 8007DB04 815E39C8 */  lwz     r10, 0x39c8(r30)
/* 078568 8007DB08 55661EB8 */  rlwinm  r6, r11, 3, 0x1a, 0x1c
/* 07856C 8007DB0C 7CC64A14 */  add     r6, r6, r9
/* 078570 8007DB10 7CC53214 */  add     r6, r5, r6
/* 078574 8007DB14 7D890734 */  extsh   r9, r12
/* 078578 8007DB18 54C6103A */  slwi    r6, r6, 2
/* 07857C 8007DB1C 7D2A312E */  stwx    r9, r10, r6
/* 078580 8007DB20 813E39BC */  lwz     r9, 0x39bc(r30)
/* 078584 8007DB24 88DF0006 */  lbz     r6, 6(r31)
/* 078588 8007DB28 7D49402E */  lwzx    r10, r9, r8
/* 07858C 8007DB2C 897F0007 */  lbz     r11, 7(r31)
/* 078590 8007DB30 50CB442E */  rlwimi  r11, r6, 8, 0x10, 0x17
/* 078594 8007DB34 7D481E70 */  srawi   r8, r10, 3
/* 078598 8007DB38 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 07859C 8007DB3C 55461EB8 */  rlwinm  r6, r10, 3, 0x1a, 0x1c
/* 0785A0 8007DB40 7CC64214 */  add     r6, r6, r8
/* 0785A4 8007DB44 7CC53214 */  add     r6, r5, r6
/* 0785A8 8007DB48 7D680734 */  extsh   r8, r11
/* 0785AC 8007DB4C 54C6103A */  slwi    r6, r6, 2
/* 0785B0 8007DB50 7D09312E */  stwx    r8, r9, r6
/* 0785B4 8007DB54 811E39BC */  lwz     r8, 0x39bc(r30)
/* 0785B8 8007DB58 88DF0008 */  lbz     r6, 8(r31)
/* 0785BC 8007DB5C 7D28382E */  lwzx    r9, r8, r7
/* 0785C0 8007DB60 895F0009 */  lbz     r10, 9(r31)
/* 0785C4 8007DB64 50CA442E */  rlwimi  r10, r6, 8, 0x10, 0x17
/* 0785C8 8007DB68 7D271E70 */  srawi   r7, r9, 3
/* 0785CC 8007DB6C 811E39C8 */  lwz     r8, 0x39c8(r30)
/* 0785D0 8007DB70 55261EB8 */  rlwinm  r6, r9, 3, 0x1a, 0x1c
/* 0785D4 8007DB74 7CC63A14 */  add     r6, r6, r7
/* 0785D8 8007DB78 7CC53214 */  add     r6, r5, r6
/* 0785DC 8007DB7C 7D470734 */  extsh   r7, r10
/* 0785E0 8007DB80 54C6103A */  slwi    r6, r6, 2
/* 0785E4 8007DB84 7CE8312E */  stwx    r7, r8, r6
/* 0785E8 8007DB88 3BFF000A */  addi    r31, r31, 0xa
/* 0785EC 8007DB8C 80FE39BC */  lwz     r7, 0x39bc(r30)
/* 0785F0 8007DB90 38C40014 */  addi    r6, r4, 0x14
/* 0785F4 8007DB94 893F0000 */  lbz     r9, 0(r31)
/* 0785F8 8007DB98 38630008 */  addi    r3, r3, 8
/* 0785FC 8007DB9C 7CC7302E */  lwzx    r6, r7, r6
/* 078600 8007DBA0 895F0001 */  lbz     r10, 1(r31)
/* 078604 8007DBA4 512A442E */  rlwimi  r10, r9, 8, 0x10, 0x17
/* 078608 8007DBA8 7CC71E70 */  srawi   r7, r6, 3
/* 07860C 8007DBAC 811E39C8 */  lwz     r8, 0x39c8(r30)
/* 078610 8007DBB0 54C61EB8 */  rlwinm  r6, r6, 3, 0x1a, 0x1c
/* 078614 8007DBB4 7CC63A14 */  add     r6, r6, r7
/* 078618 8007DBB8 7CC53214 */  add     r6, r5, r6
/* 07861C 8007DBBC 7D470734 */  extsh   r7, r10
/* 078620 8007DBC0 54C6103A */  slwi    r6, r6, 2
/* 078624 8007DBC4 7CE8312E */  stwx    r7, r8, r6
/* 078628 8007DBC8 39040018 */  addi    r8, r4, 0x18
/* 07862C 8007DBCC 38E4001C */  addi    r7, r4, 0x1c
/* 078630 8007DBD0 813E39BC */  lwz     r9, 0x39bc(r30)
/* 078634 8007DBD4 38840020 */  addi    r4, r4, 0x20
/* 078638 8007DBD8 88DF0002 */  lbz     r6, 2(r31)
/* 07863C 8007DBDC 7D49402E */  lwzx    r10, r9, r8
/* 078640 8007DBE0 897F0003 */  lbz     r11, 3(r31)
/* 078644 8007DBE4 50CB442E */  rlwimi  r11, r6, 8, 0x10, 0x17
/* 078648 8007DBE8 7D481E70 */  srawi   r8, r10, 3
/* 07864C 8007DBEC 813E39C8 */  lwz     r9, 0x39c8(r30)
/* 078650 8007DBF0 55461EB8 */  rlwinm  r6, r10, 3, 0x1a, 0x1c
/* 078654 8007DBF4 7CC64214 */  add     r6, r6, r8
/* 078658 8007DBF8 7CC53214 */  add     r6, r5, r6
/* 07865C 8007DBFC 7D680734 */  extsh   r8, r11
/* 078660 8007DC00 54C6103A */  slwi    r6, r6, 2
/* 078664 8007DC04 7D09312E */  stwx    r8, r9, r6
/* 078668 8007DC08 811E39BC */  lwz     r8, 0x39bc(r30)
/* 07866C 8007DC0C 88DF0004 */  lbz     r6, 4(r31)
/* 078670 8007DC10 7D28382E */  lwzx    r9, r8, r7
/* 078674 8007DC14 895F0005 */  lbz     r10, 5(r31)
/* 078678 8007DC18 50CA442E */  rlwimi  r10, r6, 8, 0x10, 0x17
/* 07867C 8007DC1C 7D271E70 */  srawi   r7, r9, 3
/* 078680 8007DC20 811E39C8 */  lwz     r8, 0x39c8(r30)
/* 078684 8007DC24 55261EB8 */  rlwinm  r6, r9, 3, 0x1a, 0x1c
/* 078688 8007DC28 7CC63A14 */  add     r6, r6, r7
/* 07868C 8007DC2C 7CC53214 */  add     r6, r5, r6
/* 078690 8007DC30 7D470734 */  extsh   r7, r10
/* 078694 8007DC34 54C6103A */  slwi    r6, r6, 2
/* 078698 8007DC38 7CE8312E */  stwx    r7, r8, r6
/* 07869C 8007DC3C 3BFF0006 */  addi    r31, r31, 6
/* 0786A0 8007DC40 4200FE34 */  bdnz    lbl_8007DA74
/* 0786A4 8007DC44 480000A8 */  b       lbl_8007DCEC
lbl_8007DC48:
/* 0786A8 8007DC48 20030040 */  subfic  r0, r3, 0x40
/* 0786AC 8007DC4C 2C030040 */  cmpwi   r3, 0x40
/* 0786B0 8007DC50 7C0903A6 */  mtctr   r0
/* 0786B4 8007DC54 40800044 */  bge     lbl_8007DC98
lbl_8007DC58:
/* 0786B8 8007DC58 807E39BC */  lwz     r3, 0x39bc(r30)
/* 0786BC 8007DC5C 88BF0000 */  lbz     r5, 0(r31)
/* 0786C0 8007DC60 7C03302E */  lwzx    r0, r3, r6
/* 0786C4 8007DC64 38C60004 */  addi    r6, r6, 4
/* 0786C8 8007DC68 891F0001 */  lbz     r8, 1(r31)
/* 0786CC 8007DC6C 50A8442E */  rlwimi  r8, r5, 8, 0x10, 0x17
/* 0786D0 8007DC70 7C031E70 */  srawi   r3, r0, 3
/* 0786D4 8007DC74 54001EB8 */  rlwinm  r0, r0, 3, 0x1a, 0x1c
/* 0786D8 8007DC78 809E39C8 */  lwz     r4, 0x39c8(r30)
/* 0786DC 8007DC7C 7C001A14 */  add     r0, r0, r3
/* 0786E0 8007DC80 7C070214 */  add     r0, r7, r0
/* 0786E4 8007DC84 7D030734 */  extsh   r3, r8
/* 0786E8 8007DC88 5400103A */  slwi    r0, r0, 2
/* 0786EC 8007DC8C 7C64012E */  stwx    r3, r4, r0
/* 0786F0 8007DC90 3BFF0002 */  addi    r31, r31, 2
/* 0786F4 8007DC94 4200FFC4 */  bdnz    lbl_8007DC58
lbl_8007DC98:
/* 0786F8 8007DC98 387E0000 */  addi    r3, r30, 0
/* 0786FC 8007DC9C 38960000 */  addi    r4, r22, 0
/* 078700 8007DCA0 480016C9 */  bl      rspUndoQuantize
/* 078704 8007DCA4 7FC3F378 */  mr      r3, r30
/* 078708 8007DCA8 480013D5 */  bl      rspUndoDCT
/* 07870C 8007DCAC 7FC3F378 */  mr      r3, r30
/* 078710 8007DCB0 48000C45 */  bl      rspUndoYUVtoDCTBuf
/* 078714 8007DCB4 387E0000 */  addi    r3, r30, 0
/* 078718 8007DCB8 389A0000 */  addi    r4, r26, 0
/* 07871C 8007DCBC 48000A89 */  bl      rspFormatYUV
/* 078720 8007DCC0 3B5A0300 */  addi    r26, r26, 0x300
/* 078724 8007DCC4 3B390001 */  addi    r25, r25, 1
lbl_8007DCC8:
/* 078728 8007DCC8 7C19A800 */  cmpw    r25, r21
/* 07872C 8007DCCC 4180F864 */  blt     lbl_8007D530
/* 078730 8007DCD0 38600001 */  li      r3, 1
/* 078734 8007DCD4 48000024 */  b       lbl_8007DCF8
lbl_8007DCD8:
/* 078738 8007DCD8 5489103A */  slwi    r9, r4, 2
/* 07873C 8007DCDC 4BFFFA7C */  b       lbl_8007D758
lbl_8007DCE0:
/* 078740 8007DCE0 5487103A */  slwi    r7, r4, 2
/* 078744 8007DCE4 54083032 */  slwi    r8, r0, 6
/* 078748 8007DCE8 4BFFFCF4 */  b       lbl_8007D9DC
lbl_8007DCEC:
/* 07874C 8007DCEC 5466103A */  slwi    r6, r3, 2
/* 078750 8007DCF0 54073032 */  slwi    r7, r0, 6
/* 078754 8007DCF4 4BFFFF54 */  b       lbl_8007DC48
lbl_8007DCF8:
/* 078758 8007DCF8 BA810030 */  lmw     r20, 0x30(r1)
/* 07875C 8007DCFC 80010064 */  lwz     r0, 0x64(r1)
/* 078760 8007DD00 38210060 */  addi    r1, r1, 0x60
/* 078764 8007DD04 7C0803A6 */  mtlr    r0
/* 078768 8007DD08 4E800020 */  blr     
