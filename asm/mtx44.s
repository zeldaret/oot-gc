# mtx44.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel C_MTXPerspective
/* 0A2A78 800A8018 7C0802A6 */  mflr    r0
/* 0A2A7C 800A801C 90010004 */  stw     r0, 4(r1)
/* 0A2A80 800A8020 9421FFC0 */  stwu    r1, -0x40(r1)
/* 0A2A84 800A8024 DBE10038 */  stfd    f31, 0x38(r1)
/* 0A2A88 800A8028 FFE02090 */  fmr     f31, f4
/* 0A2A8C 800A802C DBC10030 */  stfd    f30, 0x30(r1)
/* 0A2A90 800A8030 FFC01890 */  fmr     f30, f3
/* 0A2A94 800A8034 DBA10028 */  stfd    f29, 0x28(r1)
/* 0A2A98 800A8038 FFA01090 */  fmr     f29, f2
/* 0A2A9C 800A803C 93E10024 */  stw     r31, 0x24(r1)
/* 0A2AA0 800A8040 7C7F1B78 */  mr      r31, r3
/* 0A2AA4 800A8044 C0A283F8 */  lfs     f5, D_801360F8-_SDA2_BASE_(r2)
/* 0A2AA8 800A8048 C00283FC */  lfs     f0, D_801360FC-_SDA2_BASE_(r2)
/* 0A2AAC 800A804C EC250072 */  fmuls   f1, f5, f1
/* 0A2AB0 800A8050 EC200072 */  fmuls   f1, f0, f1
/* 0A2AB4 800A8054 4802A005 */  bl      tanf
/* 0A2AB8 800A8058 C06283E8 */  lfs     f3, D_801360E8-_SDA2_BASE_(r2)
/* 0A2ABC 800A805C EC5FF028 */  fsubs   f2, f31, f30
/* 0A2AC0 800A8060 EC1F07B2 */  fmuls   f0, f31, f30
/* 0A2AC4 800A8064 EC830824 */  fdivs   f4, f3, f1
/* 0A2AC8 800A8068 EC24E824 */  fdivs   f1, f4, f29
/* 0A2ACC 800A806C D03F0000 */  stfs    f1, 0(r31)
/* 0A2AD0 800A8070 EC631024 */  fdivs   f3, f3, f2
/* 0A2AD4 800A8074 C04283F0 */  lfs     f2, D_801360F0-_SDA2_BASE_(r2)
/* 0A2AD8 800A8078 D05F0004 */  stfs    f2, 4(r31)
/* 0A2ADC 800A807C D05F0008 */  stfs    f2, 8(r31)
/* 0A2AE0 800A8080 D05F000C */  stfs    f2, 0xc(r31)
/* 0A2AE4 800A8084 D05F0010 */  stfs    f2, 0x10(r31)
/* 0A2AE8 800A8088 FC20F050 */  fneg    f1, f30
/* 0A2AEC 800A808C FC000050 */  fneg    f0, f0
/* 0A2AF0 800A8090 D09F0014 */  stfs    f4, 0x14(r31)
/* 0A2AF4 800A8094 EC2100F2 */  fmuls   f1, f1, f3
/* 0A2AF8 800A8098 D05F0018 */  stfs    f2, 0x18(r31)
/* 0A2AFC 800A809C EC030032 */  fmuls   f0, f3, f0
/* 0A2B00 800A80A0 D05F001C */  stfs    f2, 0x1c(r31)
/* 0A2B04 800A80A4 D05F0020 */  stfs    f2, 0x20(r31)
/* 0A2B08 800A80A8 D05F0024 */  stfs    f2, 0x24(r31)
/* 0A2B0C 800A80AC D03F0028 */  stfs    f1, 0x28(r31)
/* 0A2B10 800A80B0 D01F002C */  stfs    f0, 0x2c(r31)
/* 0A2B14 800A80B4 D05F0030 */  stfs    f2, 0x30(r31)
/* 0A2B18 800A80B8 D05F0034 */  stfs    f2, 0x34(r31)
/* 0A2B1C 800A80BC C00283F4 */  lfs     f0, D_801360F4-_SDA2_BASE_(r2)
/* 0A2B20 800A80C0 D01F0038 */  stfs    f0, 0x38(r31)
/* 0A2B24 800A80C4 D05F003C */  stfs    f2, 0x3c(r31)
/* 0A2B28 800A80C8 80010044 */  lwz     r0, 0x44(r1)
/* 0A2B2C 800A80CC CBE10038 */  lfd     f31, 0x38(r1)
/* 0A2B30 800A80D0 CBC10030 */  lfd     f30, 0x30(r1)
/* 0A2B34 800A80D4 CBA10028 */  lfd     f29, 0x28(r1)
/* 0A2B38 800A80D8 83E10024 */  lwz     r31, 0x24(r1)
/* 0A2B3C 800A80DC 38210040 */  addi    r1, r1, 0x40
/* 0A2B40 800A80E0 7C0803A6 */  mtlr    r0
/* 0A2B44 800A80E4 4E800020 */  blr     

glabel C_MTXOrtho
/* 0A2B48 800A80E8 ED041828 */  fsubs   f8, f4, f3
/* 0A2B4C 800A80EC C12283E8 */  lfs     f9, D_801360E8-_SDA2_BASE_(r2)
/* 0A2B50 800A80F0 EC011028 */  fsubs   f0, f1, f2
/* 0A2B54 800A80F4 C0E283EC */  lfs     f7, D_801360EC-_SDA2_BASE_(r2)
/* 0A2B58 800A80F8 EC64182A */  fadds   f3, f4, f3
/* 0A2B5C 800A80FC ED494024 */  fdivs   f10, f9, f8
/* 0A2B60 800A8100 ED090024 */  fdivs   f8, f9, f0
/* 0A2B64 800A8104 EC8702B2 */  fmuls   f4, f7, f10
/* 0A2B68 800A8108 FC601850 */  fneg    f3, f3
/* 0A2B6C 800A810C EC062828 */  fsubs   f0, f6, f5
/* 0A2B70 800A8110 D0830000 */  stfs    f4, 0(r3)
/* 0A2B74 800A8114 EC21102A */  fadds   f1, f1, f2
/* 0A2B78 800A8118 EC4A00F2 */  fmuls   f2, f10, f3
/* 0A2B7C 800A811C C06283F0 */  lfs     f3, D_801360F0-_SDA2_BASE_(r2)
/* 0A2B80 800A8120 FC200850 */  fneg    f1, f1
/* 0A2B84 800A8124 D0630004 */  stfs    f3, 4(r3)
/* 0A2B88 800A8128 EC890024 */  fdivs   f4, f9, f0
/* 0A2B8C 800A812C D0630008 */  stfs    f3, 8(r3)
/* 0A2B90 800A8130 D043000C */  stfs    f2, 0xc(r3)
/* 0A2B94 800A8134 D0630010 */  stfs    f3, 0x10(r3)
/* 0A2B98 800A8138 EC470232 */  fmuls   f2, f7, f8
/* 0A2B9C 800A813C FC003050 */  fneg    f0, f6
/* 0A2BA0 800A8140 EC280072 */  fmuls   f1, f8, f1
/* 0A2BA4 800A8144 D0430014 */  stfs    f2, 0x14(r3)
/* 0A2BA8 800A8148 EC000132 */  fmuls   f0, f0, f4
/* 0A2BAC 800A814C D0630018 */  stfs    f3, 0x18(r3)
/* 0A2BB0 800A8150 D023001C */  stfs    f1, 0x1c(r3)
/* 0A2BB4 800A8154 D0630020 */  stfs    f3, 0x20(r3)
/* 0A2BB8 800A8158 D0630024 */  stfs    f3, 0x24(r3)
/* 0A2BBC 800A815C C02283F4 */  lfs     f1, D_801360F4-_SDA2_BASE_(r2)
/* 0A2BC0 800A8160 EC210132 */  fmuls   f1, f1, f4
/* 0A2BC4 800A8164 D0230028 */  stfs    f1, 0x28(r3)
/* 0A2BC8 800A8168 D003002C */  stfs    f0, 0x2c(r3)
/* 0A2BCC 800A816C D0630030 */  stfs    f3, 0x30(r3)
/* 0A2BD0 800A8170 D0630034 */  stfs    f3, 0x34(r3)
/* 0A2BD4 800A8174 D0630038 */  stfs    f3, 0x38(r3)
/* 0A2BD8 800A8178 D123003C */  stfs    f9, 0x3c(r3)
/* 0A2BDC 800A817C 4E800020 */  blr     

glabel PSMTX44Concat
/* 0A2BE0 800A8180 E0030000 */  psq_l   f0, 0(r3), 0, qr0
/* 0A2BE4 800A8184 E0440000 */  psq_l   f2, 0(r4), 0, qr0
/* 0A2BE8 800A8188 10C20018 */  ps_muls0    f6, f2, f0
/* 0A2BEC 800A818C E0640010 */  psq_l   f3, 16(r4), 0, qr0
/* 0A2BF0 800A8190 E0840020 */  psq_l   f4, 32(r4), 0, qr0
/* 0A2BF4 800A8194 10C3301E */  ps_madds1   f6, f3, f0, f6
/* 0A2BF8 800A8198 E0230008 */  psq_l   f1, 8(r3), 0, qr0
/* 0A2BFC 800A819C E0A40030 */  psq_l   f5, 48(r4), 0, qr0
/* 0A2C00 800A81A0 10C4305C */  ps_madds0   f6, f4, f1, f6
/* 0A2C04 800A81A4 E0030010 */  psq_l   f0, 16(r3), 0, qr0
/* 0A2C08 800A81A8 10C5305E */  ps_madds1   f6, f5, f1, f6
/* 0A2C0C 800A81AC E0230018 */  psq_l   f1, 24(r3), 0, qr0
/* 0A2C10 800A81B0 11020018 */  ps_muls0    f8, f2, f0
/* 0A2C14 800A81B4 1103401E */  ps_madds1   f8, f3, f0, f8
/* 0A2C18 800A81B8 E0030020 */  psq_l   f0, 32(r3), 0, qr0
/* 0A2C1C 800A81BC 1104405C */  ps_madds0   f8, f4, f1, f8
/* 0A2C20 800A81C0 1105405E */  ps_madds1   f8, f5, f1, f8
/* 0A2C24 800A81C4 E0230028 */  psq_l   f1, 40(r3), 0, qr0
/* 0A2C28 800A81C8 11420018 */  ps_muls0    f10, f2, f0
/* 0A2C2C 800A81CC 1143501E */  ps_madds1   f10, f3, f0, f10
/* 0A2C30 800A81D0 E0030030 */  psq_l   f0, 48(r3), 0, qr0
/* 0A2C34 800A81D4 1144505C */  ps_madds0   f10, f4, f1, f10
/* 0A2C38 800A81D8 1145505E */  ps_madds1   f10, f5, f1, f10
/* 0A2C3C 800A81DC E0230038 */  psq_l   f1, 56(r3), 0, qr0
/* 0A2C40 800A81E0 11820018 */  ps_muls0    f12, f2, f0
/* 0A2C44 800A81E4 E0440008 */  psq_l   f2, 8(r4), 0, qr0
/* 0A2C48 800A81E8 1183601E */  ps_madds1   f12, f3, f0, f12
/* 0A2C4C 800A81EC E0030000 */  psq_l   f0, 0(r3), 0, qr0
/* 0A2C50 800A81F0 1184605C */  ps_madds0   f12, f4, f1, f12
/* 0A2C54 800A81F4 E0640018 */  psq_l   f3, 24(r4), 0, qr0
/* 0A2C58 800A81F8 1185605E */  ps_madds1   f12, f5, f1, f12
/* 0A2C5C 800A81FC E0230008 */  psq_l   f1, 8(r3), 0, qr0
/* 0A2C60 800A8200 10E20018 */  ps_muls0    f7, f2, f0
/* 0A2C64 800A8204 E0840028 */  psq_l   f4, 40(r4), 0, qr0
/* 0A2C68 800A8208 10E3381E */  ps_madds1   f7, f3, f0, f7
/* 0A2C6C 800A820C E0A40038 */  psq_l   f5, 56(r4), 0, qr0
/* 0A2C70 800A8210 10E4385C */  ps_madds0   f7, f4, f1, f7
/* 0A2C74 800A8214 E0030010 */  psq_l   f0, 16(r3), 0, qr0
/* 0A2C78 800A8218 10E5385E */  ps_madds1   f7, f5, f1, f7
/* 0A2C7C 800A821C E0230018 */  psq_l   f1, 24(r3), 0, qr0
/* 0A2C80 800A8220 11220018 */  ps_muls0    f9, f2, f0
/* 0A2C84 800A8224 F0C50000 */  psq_st  f6, 0(r5), 0, qr0
/* 0A2C88 800A8228 1123481E */  ps_madds1   f9, f3, f0, f9
/* 0A2C8C 800A822C E0030020 */  psq_l   f0, 32(r3), 0, qr0
/* 0A2C90 800A8230 1124485C */  ps_madds0   f9, f4, f1, f9
/* 0A2C94 800A8234 F1050010 */  psq_st  f8, 16(r5), 0, qr0
/* 0A2C98 800A8238 1125485E */  ps_madds1   f9, f5, f1, f9
/* 0A2C9C 800A823C E0230028 */  psq_l   f1, 40(r3), 0, qr0
/* 0A2CA0 800A8240 11620018 */  ps_muls0    f11, f2, f0
/* 0A2CA4 800A8244 F1450020 */  psq_st  f10, 32(r5), 0, qr0
/* 0A2CA8 800A8248 1163581E */  ps_madds1   f11, f3, f0, f11
/* 0A2CAC 800A824C E0030030 */  psq_l   f0, 48(r3), 0, qr0
/* 0A2CB0 800A8250 1164585C */  ps_madds0   f11, f4, f1, f11
/* 0A2CB4 800A8254 F1850030 */  psq_st  f12, 48(r5), 0, qr0
/* 0A2CB8 800A8258 1165585E */  ps_madds1   f11, f5, f1, f11
/* 0A2CBC 800A825C E0230038 */  psq_l   f1, 56(r3), 0, qr0
/* 0A2CC0 800A8260 11A20018 */  ps_muls0    f13, f2, f0
/* 0A2CC4 800A8264 F0E50008 */  psq_st  f7, 8(r5), 0, qr0
/* 0A2CC8 800A8268 11A3681E */  ps_madds1   f13, f3, f0, f13
/* 0A2CCC 800A826C F1250018 */  psq_st  f9, 24(r5), 0, qr0
/* 0A2CD0 800A8270 11A4685C */  ps_madds0   f13, f4, f1, f13
/* 0A2CD4 800A8274 F1650028 */  psq_st  f11, 40(r5), 0, qr0
/* 0A2CD8 800A8278 11A5685E */  ps_madds1   f13, f5, f1, f13
/* 0A2CDC 800A827C F1A50038 */  psq_st  f13, 56(r5), 0, qr0
/* 0A2CE0 800A8280 4E800020 */  blr     

.section .sdata2, "wa"

.balign 8

/* 000F1BE8 801360E8 0004 */
D_801360E8:
    .float 1.0

/* 000F1BEC 801360EC 0004 */
D_801360EC:
    .float 2.0

/* 000F1BF0 801360F0 0004 */
D_801360F0:
    .float 0.0

/* 000F1BF4 801360F4 0004 */
D_801360F4:
    .float -1.0

/* 000F1BF8 801360F8 0004 */
D_801360F8:
    .float 0.5

/* 000F1BFC 801360FC 0004 */
D_801360FC:
    .float 0.01745329238474369
