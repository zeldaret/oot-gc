glabel guRotateF
/* 08E6D8 80093C78 7C0802A6 */  mflr    r0
/* 08E6DC 80093C7C 90010004 */  stw     r0, 4(r1)
/* 08E6E0 80093C80 9421FF88 */  stwu    r1, -0x78(r1)
/* 08E6E4 80093C84 DBE10070 */  stfd    f31, 0x70(r1)
/* 08E6E8 80093C88 38810028 */  addi    r4, r1, 0x28
/* 08E6EC 80093C8C DBC10068 */  stfd    f30, 0x68(r1)
/* 08E6F0 80093C90 DBA10060 */  stfd    f29, 0x60(r1)
/* 08E6F4 80093C94 DB810058 */  stfd    f28, 0x58(r1)
/* 08E6F8 80093C98 DB610050 */  stfd    f27, 0x50(r1)
/* 08E6FC 80093C9C DB410048 */  stfd    f26, 0x48(r1)
/* 08E700 80093CA0 DB210040 */  stfd    f25, 0x40(r1)
/* 08E704 80093CA4 DB010038 */  stfd    f24, 0x38(r1)
/* 08E708 80093CA8 93E10034 */  stw     r31, 0x34(r1)
/* 08E70C 80093CAC 7C7F1B78 */  mr      r31, r3
/* 08E710 80093CB0 80A3012C */  lwz     r5, 0x12c(r3)
/* 08E714 80093CB4 4BFA0ACD */  bl      cpuGetAddressBuffer
/* 08E718 80093CB8 801F006C */  lwz     r0, 0x6c(r31)
/* 08E71C 80093CBC 90010024 */  stw     r0, 0x24(r1)
/* 08E720 80093CC0 C3E10024 */  lfs     f31, 0x24(r1)
/* 08E724 80093CC4 801F0074 */  lwz     r0, 0x74(r31)
/* 08E728 80093CC8 90010024 */  stw     r0, 0x24(r1)
/* 08E72C 80093CCC C3C10024 */  lfs     f30, 0x24(r1)
/* 08E730 80093CD0 801F007C */  lwz     r0, 0x7c(r31)
/* 08E734 80093CD4 90010024 */  stw     r0, 0x24(r1)
/* 08E738 80093CD8 C3A10024 */  lfs     f29, 0x24(r1)
/* 08E73C 80093CDC 80610028 */  lwz     r3, 0x28(r1)
/* 08E740 80093CE0 EC1D0772 */  fmuls   f0, f29, f29
/* 08E744 80093CE4 80030010 */  lwz     r0, 0x10(r3)
/* 08E748 80093CE8 90010024 */  stw     r0, 0x24(r1)
/* 08E74C 80093CEC EC3E07BA */  fmadds  f1, f30, f30, f0
/* 08E750 80093CF0 C3810024 */  lfs     f28, 0x24(r1)
/* 08E754 80093CF4 C0028388 */  lfs     f0, D_80136088@sda21(r2)
/* 08E758 80093CF8 EC9C0F3A */  fmadds  f4, f28, f28, f1
/* 08E75C 80093CFC FC040040 */  fcmpo   cr0, f4, f0
/* 08E760 80093D00 40810050 */  ble     lbl_80093D50
/* 08E764 80093D04 FC202034 */  frsqrte f1, f4
/* 08E768 80093D08 C8628390 */  lfd     f3, D_80136090@sda21(r2)
/* 08E76C 80093D0C C8428398 */  lfd     f2, D_80136098@sda21(r2)
/* 08E770 80093D10 FC010072 */  fmul    f0, f1, f1
/* 08E774 80093D14 FC230072 */  fmul    f1, f3, f1
/* 08E778 80093D18 FC04103C */  fnmsub  f0, f4, f0, f2
/* 08E77C 80093D1C FC210032 */  fmul    f1, f1, f0
/* 08E780 80093D20 FC010072 */  fmul    f0, f1, f1
/* 08E784 80093D24 FC230072 */  fmul    f1, f3, f1
/* 08E788 80093D28 FC04103C */  fnmsub  f0, f4, f0, f2
/* 08E78C 80093D2C FC210032 */  fmul    f1, f1, f0
/* 08E790 80093D30 FC010072 */  fmul    f0, f1, f1
/* 08E794 80093D34 FC230072 */  fmul    f1, f3, f1
/* 08E798 80093D38 FC04103C */  fnmsub  f0, f4, f0, f2
/* 08E79C 80093D3C FC010032 */  fmul    f0, f1, f0
/* 08E7A0 80093D40 FC040032 */  fmul    f0, f4, f0
/* 08E7A4 80093D44 FC000018 */  frsp    f0, f0
/* 08E7A8 80093D48 D001000C */  stfs    f0, 0xc(r1)
/* 08E7AC 80093D4C C081000C */  lfs     f4, 0xc(r1)
lbl_80093D50:
/* 08E7B0 80093D50 C02283A4 */  lfs     f1, D_801360A4@sda21(r2)
/* 08E7B4 80093D54 C00D8648 */  lfs     f0, dtor_466@sda21(r13)
/* 08E7B8 80093D58 EC412024 */  fdivs   f2, f1, f4
/* 08E7BC 80093D5C EFFF0032 */  fmuls   f31, f31, f0
/* 08E7C0 80093D60 EFDE00B2 */  fmuls   f30, f30, f2
/* 08E7C4 80093D64 EFBD00B2 */  fmuls   f29, f29, f2
/* 08E7C8 80093D68 FC20F890 */  fmr     f1, f31
/* 08E7CC 80093D6C EF9C00B2 */  fmuls   f28, f28, f2
/* 08E7D0 80093D70 4803E501 */  bl      sinf
/* 08E7D4 80093D74 FF000890 */  fmr     f24, f1
/* 08E7D8 80093D78 FC20F890 */  fmr     f1, f31
/* 08E7DC 80093D7C 4803E361 */  bl      cosf
/* 08E7E0 80093D80 FFE00890 */  fmr     f31, f1
/* 08E7E4 80093D84 C06283A4 */  lfs     f3, D_801360A4@sda21(r2)
/* 08E7E8 80093D88 C0028388 */  lfs     f0, D_80136088@sda21(r2)
/* 08E7EC 80093D8C EC5E0772 */  fmuls   f2, f30, f29
/* 08E7F0 80093D90 EC3D0732 */  fmuls   f1, f29, f28
/* 08E7F4 80093D94 EC83F828 */  fsubs   f4, f3, f31
/* 08E7F8 80093D98 D001001C */  stfs    f0, 0x1c(r1)
/* 08E7FC 80093D9C EC1C07B2 */  fmuls   f0, f28, f30
/* 08E800 80093DA0 7FE3FB78 */  mr      r3, r31
/* 08E804 80093DA4 D0610014 */  stfs    f3, 0x14(r1)
/* 08E808 80093DA8 EF6400B2 */  fmuls   f27, f4, f2
/* 08E80C 80093DAC 80BF0064 */  lwz     r5, 0x64(r31)
/* 08E810 80093DB0 EF440072 */  fmuls   f26, f4, f1
/* 08E814 80093DB4 3881002C */  addi    r4, r1, 0x2c
/* 08E818 80093DB8 EF240032 */  fmuls   f25, f4, f0
/* 08E81C 80093DBC 4BFA09C5 */  bl      cpuGetAddressBuffer
/* 08E820 80093DC0 38000004 */  li      r0, 4
/* 08E824 80093DC4 80E10014 */  lwz     r7, 0x14(r1)
/* 08E828 80093DC8 7C0903A6 */  mtctr   r0
/* 08E82C 80093DCC 8001001C */  lwz     r0, 0x1c(r1)
/* 08E830 80093DD0 39000000 */  li      r8, 0
/* 08E834 80093DD4 38C00000 */  li      r6, 0
lbl_80093DD8:
/* 08E838 80093DD8 38800000 */  li      r4, 0
/* 08E83C 80093DDC 7C082000 */  cmpw    r8, r4
/* 08E840 80093DE0 54C3103A */  slwi    r3, r6, 2
/* 08E844 80093DE4 40820010 */  bne     lbl_80093DF4
/* 08E848 80093DE8 8081002C */  lwz     r4, 0x2c(r1)
/* 08E84C 80093DEC 7CE4192E */  stwx    r7, r4, r3
/* 08E850 80093DF0 4800000C */  b       lbl_80093DFC
lbl_80093DF4:
/* 08E854 80093DF4 8081002C */  lwz     r4, 0x2c(r1)
/* 08E858 80093DF8 7C04192E */  stwx    r0, r4, r3
lbl_80093DFC:
/* 08E85C 80093DFC 38800001 */  li      r4, 1
/* 08E860 80093E00 7C082000 */  cmpw    r8, r4
/* 08E864 80093E04 38630004 */  addi    r3, r3, 4
/* 08E868 80093E08 40820010 */  bne     lbl_80093E18
/* 08E86C 80093E0C 8081002C */  lwz     r4, 0x2c(r1)
/* 08E870 80093E10 7CE4192E */  stwx    r7, r4, r3
/* 08E874 80093E14 4800000C */  b       lbl_80093E20
lbl_80093E18:
/* 08E878 80093E18 8081002C */  lwz     r4, 0x2c(r1)
/* 08E87C 80093E1C 7C04192E */  stwx    r0, r4, r3
lbl_80093E20:
/* 08E880 80093E20 38800002 */  li      r4, 2
/* 08E884 80093E24 7C082000 */  cmpw    r8, r4
/* 08E888 80093E28 38A60001 */  addi    r5, r6, 1
/* 08E88C 80093E2C 38630004 */  addi    r3, r3, 4
/* 08E890 80093E30 40820010 */  bne     lbl_80093E40
/* 08E894 80093E34 8081002C */  lwz     r4, 0x2c(r1)
/* 08E898 80093E38 7CE4192E */  stwx    r7, r4, r3
/* 08E89C 80093E3C 4800000C */  b       lbl_80093E48
lbl_80093E40:
/* 08E8A0 80093E40 8081002C */  lwz     r4, 0x2c(r1)
/* 08E8A4 80093E44 7C04192E */  stwx    r0, r4, r3
lbl_80093E48:
/* 08E8A8 80093E48 38800003 */  li      r4, 3
/* 08E8AC 80093E4C 7C082000 */  cmpw    r8, r4
/* 08E8B0 80093E50 38630004 */  addi    r3, r3, 4
/* 08E8B4 80093E54 40820010 */  bne     lbl_80093E64
/* 08E8B8 80093E58 8081002C */  lwz     r4, 0x2c(r1)
/* 08E8BC 80093E5C 7CE4192E */  stwx    r7, r4, r3
/* 08E8C0 80093E60 4800000C */  b       lbl_80093E6C
lbl_80093E64:
/* 08E8C4 80093E64 8081002C */  lwz     r4, 0x2c(r1)
/* 08E8C8 80093E68 7C04192E */  stwx    r0, r4, r3
lbl_80093E6C:
/* 08E8CC 80093E6C 38C60004 */  addi    r6, r6, 4
/* 08E8D0 80093E70 39080001 */  addi    r8, r8, 1
/* 08E8D4 80093E74 4200FF64 */  bdnz    lbl_80093DD8
/* 08E8D8 80093E78 EC3E07B2 */  fmuls   f1, f30, f30
/* 08E8DC 80093E7C C06283A4 */  lfs     f3, D_801360A4@sda21(r2)
/* 08E8E0 80093E80 EC9E0632 */  fmuls   f4, f30, f24
/* 08E8E4 80093E84 ECFD0632 */  fmuls   f7, f29, f24
/* 08E8E8 80093E88 EC030828 */  fsubs   f0, f3, f1
/* 08E8EC 80093E8C ED1C0632 */  fmuls   f8, f28, f24
/* 08E8F0 80093E90 ECBD0772 */  fmuls   f5, f29, f29
/* 08E8F4 80093E94 EC1F083A */  fmadds  f0, f31, f0, f1
/* 08E8F8 80093E98 ED3C0732 */  fmuls   f9, f28, f28
/* 08E8FC 80093E9C EC232828 */  fsubs   f1, f3, f5
/* 08E900 80093EA0 D0010024 */  stfs    f0, 0x24(r1)
/* 08E904 80093EA4 EC5A2028 */  fsubs   f2, f26, f4
/* 08E908 80093EA8 EC034828 */  fsubs   f0, f3, f9
/* 08E90C 80093EAC 80010024 */  lwz     r0, 0x24(r1)
/* 08E910 80093EB0 8061002C */  lwz     r3, 0x2c(r1)
/* 08E914 80093EB4 ECDA202A */  fadds   f6, f26, f4
/* 08E918 80093EB8 ECBF287A */  fmadds  f5, f31, f1, f5
/* 08E91C 80093EBC 90030000 */  stw     r0, 0(r3)
/* 08E920 80093EC0 EC99382A */  fadds   f4, f25, f7
/* 08E924 80093EC4 EC793828 */  fsubs   f3, f25, f7
/* 08E928 80093EC8 D0410024 */  stfs    f2, 0x24(r1)
/* 08E92C 80093ECC EC5F483A */  fmadds  f2, f31, f0, f9
/* 08E930 80093ED0 80010024 */  lwz     r0, 0x24(r1)
/* 08E934 80093ED4 EC3B4028 */  fsubs   f1, f27, f8
/* 08E938 80093ED8 8061002C */  lwz     r3, 0x2c(r1)
/* 08E93C 80093EDC EC1B402A */  fadds   f0, f27, f8
/* 08E940 80093EE0 90030024 */  stw     r0, 0x24(r3)
/* 08E944 80093EE4 D0C10024 */  stfs    f6, 0x24(r1)
/* 08E948 80093EE8 80010024 */  lwz     r0, 0x24(r1)
/* 08E94C 80093EEC 8061002C */  lwz     r3, 0x2c(r1)
/* 08E950 80093EF0 90030018 */  stw     r0, 0x18(r3)
/* 08E954 80093EF4 D0A10024 */  stfs    f5, 0x24(r1)
/* 08E958 80093EF8 80010024 */  lwz     r0, 0x24(r1)
/* 08E95C 80093EFC 8061002C */  lwz     r3, 0x2c(r1)
/* 08E960 80093F00 90030014 */  stw     r0, 0x14(r3)
/* 08E964 80093F04 D0810024 */  stfs    f4, 0x24(r1)
/* 08E968 80093F08 80010024 */  lwz     r0, 0x24(r1)
/* 08E96C 80093F0C 8061002C */  lwz     r3, 0x2c(r1)
/* 08E970 80093F10 90030020 */  stw     r0, 0x20(r3)
/* 08E974 80093F14 D0610024 */  stfs    f3, 0x24(r1)
/* 08E978 80093F18 80010024 */  lwz     r0, 0x24(r1)
/* 08E97C 80093F1C 8061002C */  lwz     r3, 0x2c(r1)
/* 08E980 80093F20 90030008 */  stw     r0, 8(r3)
/* 08E984 80093F24 D0410024 */  stfs    f2, 0x24(r1)
/* 08E988 80093F28 80010024 */  lwz     r0, 0x24(r1)
/* 08E98C 80093F2C 8061002C */  lwz     r3, 0x2c(r1)
/* 08E990 80093F30 90030028 */  stw     r0, 0x28(r3)
/* 08E994 80093F34 D0210024 */  stfs    f1, 0x24(r1)
/* 08E998 80093F38 80010024 */  lwz     r0, 0x24(r1)
/* 08E99C 80093F3C 8061002C */  lwz     r3, 0x2c(r1)
/* 08E9A0 80093F40 90030010 */  stw     r0, 0x10(r3)
/* 08E9A4 80093F44 D0010024 */  stfs    f0, 0x24(r1)
/* 08E9A8 80093F48 80010024 */  lwz     r0, 0x24(r1)
/* 08E9AC 80093F4C 8061002C */  lwz     r3, 0x2c(r1)
/* 08E9B0 80093F50 90030004 */  stw     r0, 4(r3)
/* 08E9B4 80093F54 8001007C */  lwz     r0, 0x7c(r1)
/* 08E9B8 80093F58 CBE10070 */  lfd     f31, 0x70(r1)
/* 08E9BC 80093F5C CBC10068 */  lfd     f30, 0x68(r1)
/* 08E9C0 80093F60 CBA10060 */  lfd     f29, 0x60(r1)
/* 08E9C4 80093F64 CB810058 */  lfd     f28, 0x58(r1)
/* 08E9C8 80093F68 CB610050 */  lfd     f27, 0x50(r1)
/* 08E9CC 80093F6C CB410048 */  lfd     f26, 0x48(r1)
/* 08E9D0 80093F70 CB210040 */  lfd     f25, 0x40(r1)
/* 08E9D4 80093F74 CB010038 */  lfd     f24, 0x38(r1)
/* 08E9D8 80093F78 83E10034 */  lwz     r31, 0x34(r1)
/* 08E9DC 80093F7C 38210078 */  addi    r1, r1, 0x78
/* 08E9E0 80093F80 7C0803A6 */  mtlr    r0
/* 08E9E4 80093F84 4E800020 */  blr     
