# mtx.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel PSMTXIdentity
/* 0A282C 800A7DCC C00283E4 */  lfs     f0, D_801360E4-_SDA2_BASE_(r2)
/* 0A2830 800A7DD0 C02283E0 */  lfs     f1, D_801360E0-_SDA2_BASE_(r2)
/* 0A2834 800A7DD4 F0030008 */  psq_st  f0, 8(r3), 0, qr0
/* 0A2838 800A7DD8 10400C60 */  ps_merge01  f2, f0, f1
/* 0A283C 800A7DDC F0030018 */  psq_st  f0, 24(r3), 0, qr0
/* 0A2840 800A7DE0 102104A0 */  ps_merge10  f1, f1, f0
/* 0A2844 800A7DE4 F0030020 */  psq_st  f0, 32(r3), 0, qr0
/* 0A2848 800A7DE8 F0430010 */  psq_st  f2, 16(r3), 0, qr0
/* 0A284C 800A7DEC F0230000 */  psq_st  f1, 0(r3), 0, qr0
/* 0A2850 800A7DF0 F0230028 */  psq_st  f1, 40(r3), 0, qr0
/* 0A2854 800A7DF4 4E800020 */  blr     

glabel PSMTXConcat
/* 0A2858 800A7DF8 9421FFC0 */  stwu    r1, -0x40(r1)
/* 0A285C 800A7DFC E0030000 */  psq_l   f0, 0(r3), 0, qr0
/* 0A2860 800A7E00 D9C10008 */  stfd    f14, 8(r1)
/* 0A2864 800A7E04 E0C40000 */  psq_l   f6, 0(r4), 0, qr0
/* 0A2868 800A7E08 3CC08013 */  lis     r6, Unit01@ha
/* 0A286C 800A7E0C E0E40008 */  psq_l   f7, 8(r4), 0, qr0
/* 0A2870 800A7E10 D9E10010 */  stfd    f15, 0x10(r1)
/* 0A2874 800A7E14 38C65468 */  addi    r6, r6, Unit01@l
/* 0A2878 800A7E18 DBE10028 */  stfd    f31, 0x28(r1)
/* 0A287C 800A7E1C E1040010 */  psq_l   f8, 16(r4), 0, qr0
/* 0A2880 800A7E20 11860018 */  ps_muls0    f12, f6, f0
/* 0A2884 800A7E24 E0430010 */  psq_l   f2, 16(r3), 0, qr0
/* 0A2888 800A7E28 11A70018 */  ps_muls0    f13, f7, f0
/* 0A288C 800A7E2C E3E60000 */  psq_l   f31, 0(r6), 0, qr0
/* 0A2890 800A7E30 11C60098 */  ps_muls0    f14, f6, f2
/* 0A2894 800A7E34 E1240018 */  psq_l   f9, 24(r4), 0, qr0
/* 0A2898 800A7E38 11E70098 */  ps_muls0    f15, f7, f2
/* 0A289C 800A7E3C E0230008 */  psq_l   f1, 8(r3), 0, qr0
/* 0A28A0 800A7E40 1188601E */  ps_madds1   f12, f8, f0, f12
/* 0A28A4 800A7E44 E0630018 */  psq_l   f3, 24(r3), 0, qr0
/* 0A28A8 800A7E48 11C8709E */  ps_madds1   f14, f8, f2, f14
/* 0A28AC 800A7E4C E1440020 */  psq_l   f10, 32(r4), 0, qr0
/* 0A28B0 800A7E50 11A9681E */  ps_madds1   f13, f9, f0, f13
/* 0A28B4 800A7E54 E1640028 */  psq_l   f11, 40(r4), 0, qr0
/* 0A28B8 800A7E58 11E9789E */  ps_madds1   f15, f9, f2, f15
/* 0A28BC 800A7E5C E0830020 */  psq_l   f4, 32(r3), 0, qr0
/* 0A28C0 800A7E60 E0A30028 */  psq_l   f5, 40(r3), 0, qr0
/* 0A28C4 800A7E64 118A605C */  ps_madds0   f12, f10, f1, f12
/* 0A28C8 800A7E68 11AB685C */  ps_madds0   f13, f11, f1, f13
/* 0A28CC 800A7E6C 11CA70DC */  ps_madds0   f14, f10, f3, f14
/* 0A28D0 800A7E70 11EB78DC */  ps_madds0   f15, f11, f3, f15
/* 0A28D4 800A7E74 F1850000 */  psq_st  f12, 0(r5), 0, qr0
/* 0A28D8 800A7E78 10460118 */  ps_muls0    f2, f6, f4
/* 0A28DC 800A7E7C 11BF685E */  ps_madds1   f13, f31, f1, f13
/* 0A28E0 800A7E80 10070118 */  ps_muls0    f0, f7, f4
/* 0A28E4 800A7E84 F1C50010 */  psq_st  f14, 16(r5), 0, qr0
/* 0A28E8 800A7E88 11FF78DE */  ps_madds1   f15, f31, f3, f15
/* 0A28EC 800A7E8C F1A50008 */  psq_st  f13, 8(r5), 0, qr0
/* 0A28F0 800A7E90 1048111E */  ps_madds1   f2, f8, f4, f2
/* 0A28F4 800A7E94 1009011E */  ps_madds1   f0, f9, f4, f0
/* 0A28F8 800A7E98 104A115C */  ps_madds0   f2, f10, f5, f2
/* 0A28FC 800A7E9C C9C10008 */  lfd     f14, 8(r1)
/* 0A2900 800A7EA0 F1E50018 */  psq_st  f15, 24(r5), 0, qr0
/* 0A2904 800A7EA4 100B015C */  ps_madds0   f0, f11, f5, f0
/* 0A2908 800A7EA8 F0450020 */  psq_st  f2, 32(r5), 0, qr0
/* 0A290C 800A7EAC 101F015E */  ps_madds1   f0, f31, f5, f0
/* 0A2910 800A7EB0 C9E10010 */  lfd     f15, 0x10(r1)
/* 0A2914 800A7EB4 F0050028 */  psq_st  f0, 40(r5), 0, qr0
/* 0A2918 800A7EB8 CBE10028 */  lfd     f31, 0x28(r1)
/* 0A291C 800A7EBC 38210040 */  addi    r1, r1, 0x40
/* 0A2920 800A7EC0 4E800020 */  blr     

glabel PSMTXTrans
/* 0A2924 800A7EC4 C00283E4 */  lfs     f0, D_801360E4-_SDA2_BASE_(r2)
/* 0A2928 800A7EC8 C08283E0 */  lfs     f4, D_801360E0-_SDA2_BASE_(r2)
/* 0A292C 800A7ECC D023000C */  stfs    f1, 0xc(r3)
/* 0A2930 800A7ED0 D043001C */  stfs    f2, 0x1c(r3)
/* 0A2934 800A7ED4 F0030004 */  psq_st  f0, 4(r3), 0, qr0
/* 0A2938 800A7ED8 F0030020 */  psq_st  f0, 32(r3), 0, qr0
/* 0A293C 800A7EDC D0030010 */  stfs    f0, 0x10(r3)
/* 0A2940 800A7EE0 D0830014 */  stfs    f4, 0x14(r3)
/* 0A2944 800A7EE4 D0030018 */  stfs    f0, 0x18(r3)
/* 0A2948 800A7EE8 D0830028 */  stfs    f4, 0x28(r3)
/* 0A294C 800A7EEC D063002C */  stfs    f3, 0x2c(r3)
/* 0A2950 800A7EF0 D0830000 */  stfs    f4, 0(r3)
/* 0A2954 800A7EF4 4E800020 */  blr     

glabel PSMTXTransApply
/* 0A2958 800A7EF8 E0830000 */  psq_l   f4, 0(r3), 0, qr0
/* 0A295C 800A7EFC FC200818 */  frsp    f1, f1
/* 0A2960 800A7F00 E0A30008 */  psq_l   f5, 8(r3), 0, qr0
/* 0A2964 800A7F04 FC401018 */  frsp    f2, f2
/* 0A2968 800A7F08 E0E30018 */  psq_l   f7, 24(r3), 0, qr0
/* 0A296C 800A7F0C FC601818 */  frsp    f3, f3
/* 0A2970 800A7F10 E1030028 */  psq_l   f8, 40(r3), 0, qr0
/* 0A2974 800A7F14 F0840000 */  psq_st  f4, 0(r4), 0, qr0
/* 0A2978 800A7F18 10A12956 */  ps_sum1 f5, f1, f5, f5
/* 0A297C 800A7F1C E0C30010 */  psq_l   f6, 16(r3), 0, qr0
/* 0A2980 800A7F20 F0A40008 */  psq_st  f5, 8(r4), 0, qr0
/* 0A2984 800A7F24 10E239D6 */  ps_sum1 f7, f2, f7, f7
/* 0A2988 800A7F28 E1230020 */  psq_l   f9, 32(r3), 0, qr0
/* 0A298C 800A7F2C F0C40010 */  psq_st  f6, 16(r4), 0, qr0
/* 0A2990 800A7F30 11034216 */  ps_sum1 f8, f3, f8, f8
/* 0A2994 800A7F34 F0E40018 */  psq_st  f7, 24(r4), 0, qr0
/* 0A2998 800A7F38 F1240020 */  psq_st  f9, 32(r4), 0, qr0
/* 0A299C 800A7F3C F1040028 */  psq_st  f8, 40(r4), 0, qr0
/* 0A29A0 800A7F40 4E800020 */  blr     

glabel PSMTXScale
/* 0A29A4 800A7F44 C00283E4 */  lfs     f0, D_801360E4-_SDA2_BASE_(r2)
/* 0A29A8 800A7F48 D0230000 */  stfs    f1, 0(r3)
/* 0A29AC 800A7F4C F0030004 */  psq_st  f0, 4(r3), 0, qr0
/* 0A29B0 800A7F50 F003000C */  psq_st  f0, 12(r3), 0, qr0
/* 0A29B4 800A7F54 D0430014 */  stfs    f2, 0x14(r3)
/* 0A29B8 800A7F58 F0030018 */  psq_st  f0, 24(r3), 0, qr0
/* 0A29BC 800A7F5C F0030020 */  psq_st  f0, 32(r3), 0, qr0
/* 0A29C0 800A7F60 D0630028 */  stfs    f3, 0x28(r3)
/* 0A29C4 800A7F64 D003002C */  stfs    f0, 0x2c(r3)
/* 0A29C8 800A7F68 4E800020 */  blr     

glabel PSMTXScaleApply
/* 0A29CC 800A7F6C FC200818 */  frsp    f1, f1
/* 0A29D0 800A7F70 E0830000 */  psq_l   f4, 0(r3), 0, qr0
/* 0A29D4 800A7F74 FC401018 */  frsp    f2, f2
/* 0A29D8 800A7F78 E0A30008 */  psq_l   f5, 8(r3), 0, qr0
/* 0A29DC 800A7F7C FC601818 */  frsp    f3, f3
/* 0A29E0 800A7F80 10840058 */  ps_muls0    f4, f4, f1
/* 0A29E4 800A7F84 E0C30010 */  psq_l   f6, 16(r3), 0, qr0
/* 0A29E8 800A7F88 10A50058 */  ps_muls0    f5, f5, f1
/* 0A29EC 800A7F8C E0E30018 */  psq_l   f7, 24(r3), 0, qr0
/* 0A29F0 800A7F90 10C60098 */  ps_muls0    f6, f6, f2
/* 0A29F4 800A7F94 E1030020 */  psq_l   f8, 32(r3), 0, qr0
/* 0A29F8 800A7F98 F0840000 */  psq_st  f4, 0(r4), 0, qr0
/* 0A29FC 800A7F9C 10E70098 */  ps_muls0    f7, f7, f2
/* 0A2A00 800A7FA0 E0430028 */  psq_l   f2, 40(r3), 0, qr0
/* 0A2A04 800A7FA4 F0A40008 */  psq_st  f5, 8(r4), 0, qr0
/* 0A2A08 800A7FA8 110800D8 */  ps_muls0    f8, f8, f3
/* 0A2A0C 800A7FAC F0C40010 */  psq_st  f6, 16(r4), 0, qr0
/* 0A2A10 800A7FB0 104200D8 */  ps_muls0    f2, f2, f3
/* 0A2A14 800A7FB4 F0E40018 */  psq_st  f7, 24(r4), 0, qr0
/* 0A2A18 800A7FB8 F1040020 */  psq_st  f8, 32(r4), 0, qr0
/* 0A2A1C 800A7FBC F0440028 */  psq_st  f2, 40(r4), 0, qr0
/* 0A2A20 800A7FC0 4E800020 */  blr     

.section .sdata, "wa"

.balign 8

/* 000F16E8 80135468 0008 */
Unit01:
    .float 0.0, 1.0

.section .sdata2, "wa"

.balign 8

/* 000F1BE0 801360E0 0004 */
D_801360E0:
    .float 1.0

/* 000F1BE4 801360E4 0004 */
D_801360E4:
    .float 0.0
