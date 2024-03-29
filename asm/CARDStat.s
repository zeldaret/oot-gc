# CARDStat.c
.include "macros.inc"

.section .text, "ax"

.balign 4

UpdateIconOffsets:
/* 0BBAA4 800C1044 8103002C */  lwz     r8, 0x2c(r3)
/* 0BBAA8 800C1048 3C080001 */  addis   r0, r8, 1
/* 0BBAAC 800C104C 2800FFFF */  cmplwi  r0, 0xffff
/* 0BBAB0 800C1050 40820018 */  bne     lbl_800C1068
/* 0BBAB4 800C1054 38000000 */  li      r0, 0
/* 0BBAB8 800C1058 9804002E */  stb     r0, 0x2e(r4)
/* 0BBABC 800C105C 39000000 */  li      r8, 0
/* 0BBAC0 800C1060 B0040034 */  sth     r0, 0x34(r4)
/* 0BBAC4 800C1064 B0040036 */  sth     r0, 0x36(r4)
lbl_800C1068:
/* 0BBAC8 800C1068 88030007 */  lbz     r0, 7(r3)
/* 0BBACC 800C106C 39200000 */  li      r9, 0
/* 0BBAD0 800C1070 540007BE */  clrlwi  r0, r0, 0x1e
/* 0BBAD4 800C1074 2C000002 */  cmpwi   r0, 2
/* 0BBAD8 800C1078 41820028 */  beq     lbl_800C10A0
/* 0BBADC 800C107C 40800038 */  bge     lbl_800C10B4
/* 0BBAE0 800C1080 2C000001 */  cmpwi   r0, 1
/* 0BBAE4 800C1084 40800008 */  bge     lbl_800C108C
/* 0BBAE8 800C1088 4800002C */  b       lbl_800C10B4
lbl_800C108C:
/* 0BBAEC 800C108C 9104003C */  stw     r8, 0x3c(r4)
/* 0BBAF0 800C1090 38080C00 */  addi    r0, r8, 0xc00
/* 0BBAF4 800C1094 39080E00 */  addi    r8, r8, 0xe00
/* 0BBAF8 800C1098 90040040 */  stw     r0, 0x40(r4)
/* 0BBAFC 800C109C 48000024 */  b       lbl_800C10C0
lbl_800C10A0:
/* 0BBB00 800C10A0 9104003C */  stw     r8, 0x3c(r4)
/* 0BBB04 800C10A4 3800FFFF */  li      r0, -1
/* 0BBB08 800C10A8 39081800 */  addi    r8, r8, 0x1800
/* 0BBB0C 800C10AC 90040040 */  stw     r0, 0x40(r4)
/* 0BBB10 800C10B0 48000010 */  b       lbl_800C10C0
lbl_800C10B4:
/* 0BBB14 800C10B4 3800FFFF */  li      r0, -1
/* 0BBB18 800C10B8 9004003C */  stw     r0, 0x3c(r4)
/* 0BBB1C 800C10BC 90040040 */  stw     r0, 0x40(r4)
lbl_800C10C0:
/* 0BBB20 800C10C0 38000002 */  li      r0, 2
/* 0BBB24 800C10C4 7C0903A6 */  mtctr   r0
/* 0BBB28 800C10C8 38E40000 */  addi    r7, r4, 0
/* 0BBB2C 800C10CC 39400000 */  li      r10, 0
/* 0BBB30 800C10D0 38C00000 */  li      r6, 0
/* 0BBB34 800C10D4 3800FFFF */  li      r0, -1
lbl_800C10D8:
/* 0BBB38 800C10D8 A0A30030 */  lhz     r5, 0x30(r3)
/* 0BBB3C 800C10DC 7CA53630 */  sraw    r5, r5, r6
/* 0BBB40 800C10E0 54A507BE */  clrlwi  r5, r5, 0x1e
/* 0BBB44 800C10E4 2C050002 */  cmpwi   r5, 2
/* 0BBB48 800C10E8 41820024 */  beq     lbl_800C110C
/* 0BBB4C 800C10EC 4080002C */  bge     lbl_800C1118
/* 0BBB50 800C10F0 2C050001 */  cmpwi   r5, 1
/* 0BBB54 800C10F4 40800008 */  bge     lbl_800C10FC
/* 0BBB58 800C10F8 48000020 */  b       lbl_800C1118
lbl_800C10FC:
/* 0BBB5C 800C10FC 91070044 */  stw     r8, 0x44(r7)
/* 0BBB60 800C1100 39200001 */  li      r9, 1
/* 0BBB64 800C1104 39080400 */  addi    r8, r8, 0x400
/* 0BBB68 800C1108 48000014 */  b       lbl_800C111C
lbl_800C110C:
/* 0BBB6C 800C110C 91070044 */  stw     r8, 0x44(r7)
/* 0BBB70 800C1110 39080800 */  addi    r8, r8, 0x800
/* 0BBB74 800C1114 48000008 */  b       lbl_800C111C
lbl_800C1118:
/* 0BBB78 800C1118 90070044 */  stw     r0, 0x44(r7)
lbl_800C111C:
/* 0BBB7C 800C111C A0A30030 */  lhz     r5, 0x30(r3)
/* 0BBB80 800C1120 38C60002 */  addi    r6, r6, 2
/* 0BBB84 800C1124 38E70004 */  addi    r7, r7, 4
/* 0BBB88 800C1128 7CA53630 */  sraw    r5, r5, r6
/* 0BBB8C 800C112C 54A507BE */  clrlwi  r5, r5, 0x1e
/* 0BBB90 800C1130 2C050002 */  cmpwi   r5, 2
/* 0BBB94 800C1134 41820024 */  beq     lbl_800C1158
/* 0BBB98 800C1138 4080002C */  bge     lbl_800C1164
/* 0BBB9C 800C113C 2C050001 */  cmpwi   r5, 1
/* 0BBBA0 800C1140 40800008 */  bge     lbl_800C1148
/* 0BBBA4 800C1144 48000020 */  b       lbl_800C1164
lbl_800C1148:
/* 0BBBA8 800C1148 91070044 */  stw     r8, 0x44(r7)
/* 0BBBAC 800C114C 39200001 */  li      r9, 1
/* 0BBBB0 800C1150 39080400 */  addi    r8, r8, 0x400
/* 0BBBB4 800C1154 48000014 */  b       lbl_800C1168
lbl_800C1158:
/* 0BBBB8 800C1158 91070044 */  stw     r8, 0x44(r7)
/* 0BBBBC 800C115C 39080800 */  addi    r8, r8, 0x800
/* 0BBBC0 800C1160 48000008 */  b       lbl_800C1168
lbl_800C1164:
/* 0BBBC4 800C1164 90070044 */  stw     r0, 0x44(r7)
lbl_800C1168:
/* 0BBBC8 800C1168 A0A30030 */  lhz     r5, 0x30(r3)
/* 0BBBCC 800C116C 38C60002 */  addi    r6, r6, 2
/* 0BBBD0 800C1170 394A0001 */  addi    r10, r10, 1
/* 0BBBD4 800C1174 7CA53630 */  sraw    r5, r5, r6
/* 0BBBD8 800C1178 54A507BE */  clrlwi  r5, r5, 0x1e
/* 0BBBDC 800C117C 2C050002 */  cmpwi   r5, 2
/* 0BBBE0 800C1180 38E70004 */  addi    r7, r7, 4
/* 0BBBE4 800C1184 41820024 */  beq     lbl_800C11A8
/* 0BBBE8 800C1188 4080002C */  bge     lbl_800C11B4
/* 0BBBEC 800C118C 2C050001 */  cmpwi   r5, 1
/* 0BBBF0 800C1190 40800008 */  bge     lbl_800C1198
/* 0BBBF4 800C1194 48000020 */  b       lbl_800C11B4
lbl_800C1198:
/* 0BBBF8 800C1198 91070044 */  stw     r8, 0x44(r7)
/* 0BBBFC 800C119C 39200001 */  li      r9, 1
/* 0BBC00 800C11A0 39080400 */  addi    r8, r8, 0x400
/* 0BBC04 800C11A4 48000014 */  b       lbl_800C11B8
lbl_800C11A8:
/* 0BBC08 800C11A8 91070044 */  stw     r8, 0x44(r7)
/* 0BBC0C 800C11AC 39080800 */  addi    r8, r8, 0x800
/* 0BBC10 800C11B0 48000008 */  b       lbl_800C11B8
lbl_800C11B4:
/* 0BBC14 800C11B4 90070044 */  stw     r0, 0x44(r7)
lbl_800C11B8:
/* 0BBC18 800C11B8 A0A30030 */  lhz     r5, 0x30(r3)
/* 0BBC1C 800C11BC 38C60002 */  addi    r6, r6, 2
/* 0BBC20 800C11C0 394A0001 */  addi    r10, r10, 1
/* 0BBC24 800C11C4 7CA53630 */  sraw    r5, r5, r6
/* 0BBC28 800C11C8 54A507BE */  clrlwi  r5, r5, 0x1e
/* 0BBC2C 800C11CC 2C050002 */  cmpwi   r5, 2
/* 0BBC30 800C11D0 38E70004 */  addi    r7, r7, 4
/* 0BBC34 800C11D4 41820024 */  beq     lbl_800C11F8
/* 0BBC38 800C11D8 4080002C */  bge     lbl_800C1204
/* 0BBC3C 800C11DC 2C050001 */  cmpwi   r5, 1
/* 0BBC40 800C11E0 40800008 */  bge     lbl_800C11E8
/* 0BBC44 800C11E4 48000020 */  b       lbl_800C1204
lbl_800C11E8:
/* 0BBC48 800C11E8 91070044 */  stw     r8, 0x44(r7)
/* 0BBC4C 800C11EC 39200001 */  li      r9, 1
/* 0BBC50 800C11F0 39080400 */  addi    r8, r8, 0x400
/* 0BBC54 800C11F4 48000014 */  b       lbl_800C1208
lbl_800C11F8:
/* 0BBC58 800C11F8 91070044 */  stw     r8, 0x44(r7)
/* 0BBC5C 800C11FC 39080800 */  addi    r8, r8, 0x800
/* 0BBC60 800C1200 48000008 */  b       lbl_800C1208
lbl_800C1204:
/* 0BBC64 800C1204 90070044 */  stw     r0, 0x44(r7)
lbl_800C1208:
/* 0BBC68 800C1208 38C60002 */  addi    r6, r6, 2
/* 0BBC6C 800C120C 38E70004 */  addi    r7, r7, 4
/* 0BBC70 800C1210 394A0001 */  addi    r10, r10, 1
/* 0BBC74 800C1214 4200FEC4 */  bdnz    lbl_800C10D8
/* 0BBC78 800C1218 2C090000 */  cmpwi   r9, 0
/* 0BBC7C 800C121C 41820010 */  beq     lbl_800C122C
/* 0BBC80 800C1220 91040064 */  stw     r8, 0x64(r4)
/* 0BBC84 800C1224 39080200 */  addi    r8, r8, 0x200
/* 0BBC88 800C1228 4800000C */  b       lbl_800C1234
lbl_800C122C:
/* 0BBC8C 800C122C 3800FFFF */  li      r0, -1
/* 0BBC90 800C1230 90040064 */  stw     r0, 0x64(r4)
lbl_800C1234:
/* 0BBC94 800C1234 91040068 */  stw     r8, 0x68(r4)
/* 0BBC98 800C1238 4E800020 */  blr     

glabel CARDGetStatus
/* 0BBC9C 800C123C 7C0802A6 */  mflr    r0
/* 0BBCA0 800C1240 90010004 */  stw     r0, 4(r1)
/* 0BBCA4 800C1244 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0BBCA8 800C1248 93E10024 */  stw     r31, 0x24(r1)
/* 0BBCAC 800C124C 3BE50000 */  addi    r31, r5, 0
/* 0BBCB0 800C1250 93C10020 */  stw     r30, 0x20(r1)
/* 0BBCB4 800C1254 93A1001C */  stw     r29, 0x1c(r1)
/* 0BBCB8 800C1258 7C9D2379 */  or.     r29, r4, r4
/* 0BBCBC 800C125C 4180000C */  blt     lbl_800C1268
/* 0BBCC0 800C1260 2C1D007F */  cmpwi   r29, 0x7f
/* 0BBCC4 800C1264 4180000C */  blt     lbl_800C1270
lbl_800C1268:
/* 0BBCC8 800C1268 3860FF80 */  li      r3, -128
/* 0BBCCC 800C126C 480000C8 */  b       lbl_800C1334
lbl_800C1270:
/* 0BBCD0 800C1270 38810014 */  addi    r4, r1, 0x14
/* 0BBCD4 800C1274 4BFFAA49 */  bl      __CARDGetControlBlock
/* 0BBCD8 800C1278 2C030000 */  cmpwi   r3, 0
/* 0BBCDC 800C127C 40800008 */  bge     lbl_800C1284
/* 0BBCE0 800C1280 480000B4 */  b       lbl_800C1334
lbl_800C1284:
/* 0BBCE4 800C1284 80610014 */  lwz     r3, 0x14(r1)
/* 0BBCE8 800C1288 4BFFC6B5 */  bl      __CARDGetDirBlock
/* 0BBCEC 800C128C 57A03032 */  slwi    r0, r29, 6
/* 0BBCF0 800C1290 7FA30214 */  add     r29, r3, r0
/* 0BBCF4 800C1294 80610014 */  lwz     r3, 0x14(r1)
/* 0BBCF8 800C1298 7FA4EB78 */  mr      r4, r29
/* 0BBCFC 800C129C 4BFFED41 */  bl      __CARDIsReadable
/* 0BBD00 800C12A0 7C7E1B79 */  or.     r30, r3, r3
/* 0BBD04 800C12A4 41800084 */  blt     lbl_800C1328
/* 0BBD08 800C12A8 389D0000 */  addi    r4, r29, 0
/* 0BBD0C 800C12AC 387F0028 */  addi    r3, r31, 0x28
/* 0BBD10 800C12B0 38A00004 */  li      r5, 4
/* 0BBD14 800C12B4 4BF44211 */  bl      memcpy
/* 0BBD18 800C12B8 387F002C */  addi    r3, r31, 0x2c
/* 0BBD1C 800C12BC 389D0004 */  addi    r4, r29, 4
/* 0BBD20 800C12C0 38A00002 */  li      r5, 2
/* 0BBD24 800C12C4 4BF44201 */  bl      memcpy
/* 0BBD28 800C12C8 80A10014 */  lwz     r5, 0x14(r1)
/* 0BBD2C 800C12CC 7FE3FB78 */  mr      r3, r31
/* 0BBD30 800C12D0 A0DD0038 */  lhz     r6, 0x38(r29)
/* 0BBD34 800C12D4 389D0008 */  addi    r4, r29, 8
/* 0BBD38 800C12D8 8005000C */  lwz     r0, 0xc(r5)
/* 0BBD3C 800C12DC 38A00020 */  li      r5, 0x20
/* 0BBD40 800C12E0 7C0601D6 */  mullw   r0, r6, r0
/* 0BBD44 800C12E4 901F0020 */  stw     r0, 0x20(r31)
/* 0BBD48 800C12E8 4BF441DD */  bl      memcpy
/* 0BBD4C 800C12EC 801D0028 */  lwz     r0, 0x28(r29)
/* 0BBD50 800C12F0 387D0000 */  addi    r3, r29, 0
/* 0BBD54 800C12F4 389F0000 */  addi    r4, r31, 0
/* 0BBD58 800C12F8 901F0024 */  stw     r0, 0x24(r31)
/* 0BBD5C 800C12FC 881D0007 */  lbz     r0, 7(r29)
/* 0BBD60 800C1300 981F002E */  stb     r0, 0x2e(r31)
/* 0BBD64 800C1304 801D002C */  lwz     r0, 0x2c(r29)
/* 0BBD68 800C1308 901F0030 */  stw     r0, 0x30(r31)
/* 0BBD6C 800C130C A01D0030 */  lhz     r0, 0x30(r29)
/* 0BBD70 800C1310 B01F0034 */  sth     r0, 0x34(r31)
/* 0BBD74 800C1314 A01D0032 */  lhz     r0, 0x32(r29)
/* 0BBD78 800C1318 B01F0036 */  sth     r0, 0x36(r31)
/* 0BBD7C 800C131C 801D003C */  lwz     r0, 0x3c(r29)
/* 0BBD80 800C1320 901F0038 */  stw     r0, 0x38(r31)
/* 0BBD84 800C1324 4BFFFD21 */  bl      UpdateIconOffsets
lbl_800C1328:
/* 0BBD88 800C1328 80610014 */  lwz     r3, 0x14(r1)
/* 0BBD8C 800C132C 7FC4F378 */  mr      r4, r30
/* 0BBD90 800C1330 4BFFAA45 */  bl      __CARDPutControlBlock
lbl_800C1334:
/* 0BBD94 800C1334 8001002C */  lwz     r0, 0x2c(r1)
/* 0BBD98 800C1338 83E10024 */  lwz     r31, 0x24(r1)
/* 0BBD9C 800C133C 83C10020 */  lwz     r30, 0x20(r1)
/* 0BBDA0 800C1340 83A1001C */  lwz     r29, 0x1c(r1)
/* 0BBDA4 800C1344 38210028 */  addi    r1, r1, 0x28
/* 0BBDA8 800C1348 7C0803A6 */  mtlr    r0
/* 0BBDAC 800C134C 4E800020 */  blr     

glabel CARDSetStatusAsync
/* 0BBDB0 800C1350 7C0802A6 */  mflr    r0
/* 0BBDB4 800C1354 90010004 */  stw     r0, 4(r1)
/* 0BBDB8 800C1358 9421FFD0 */  stwu    r1, -0x30(r1)
/* 0BBDBC 800C135C 93E1002C */  stw     r31, 0x2c(r1)
/* 0BBDC0 800C1360 7C9F2379 */  or.     r31, r4, r4
/* 0BBDC4 800C1364 93C10028 */  stw     r30, 0x28(r1)
/* 0BBDC8 800C1368 3BC60000 */  addi    r30, r6, 0
/* 0BBDCC 800C136C 93A10024 */  stw     r29, 0x24(r1)
/* 0BBDD0 800C1370 3BA50000 */  addi    r29, r5, 0
/* 0BBDD4 800C1374 93810020 */  stw     r28, 0x20(r1)
/* 0BBDD8 800C1378 3B830000 */  addi    r28, r3, 0
/* 0BBDDC 800C137C 41800040 */  blt     lbl_800C13BC
/* 0BBDE0 800C1380 2C1F007F */  cmpwi   r31, 0x7f
/* 0BBDE4 800C1384 40800038 */  bge     lbl_800C13BC
/* 0BBDE8 800C1388 807D0030 */  lwz     r3, 0x30(r29)
/* 0BBDEC 800C138C 3C030001 */  addis   r0, r3, 1
/* 0BBDF0 800C1390 2800FFFF */  cmplwi  r0, 0xffff
/* 0BBDF4 800C1394 4182000C */  beq     lbl_800C13A0
/* 0BBDF8 800C1398 28030200 */  cmplwi  r3, 0x200
/* 0BBDFC 800C139C 40800020 */  bge     lbl_800C13BC
lbl_800C13A0:
/* 0BBE00 800C13A0 807D0038 */  lwz     r3, 0x38(r29)
/* 0BBE04 800C13A4 3C030001 */  addis   r0, r3, 1
/* 0BBE08 800C13A8 2800FFFF */  cmplwi  r0, 0xffff
/* 0BBE0C 800C13AC 41820018 */  beq     lbl_800C13C4
/* 0BBE10 800C13B0 546004FE */  clrlwi  r0, r3, 0x13
/* 0BBE14 800C13B4 28001FC0 */  cmplwi  r0, 0x1fc0
/* 0BBE18 800C13B8 4081000C */  ble     lbl_800C13C4
lbl_800C13BC:
/* 0BBE1C 800C13BC 3860FF80 */  li      r3, -128
/* 0BBE20 800C13C0 480000E4 */  b       lbl_800C14A4
lbl_800C13C4:
/* 0BBE24 800C13C4 387C0000 */  addi    r3, r28, 0
/* 0BBE28 800C13C8 38810018 */  addi    r4, r1, 0x18
/* 0BBE2C 800C13CC 4BFFA8F1 */  bl      __CARDGetControlBlock
/* 0BBE30 800C13D0 2C030000 */  cmpwi   r3, 0
/* 0BBE34 800C13D4 40800008 */  bge     lbl_800C13DC
/* 0BBE38 800C13D8 480000CC */  b       lbl_800C14A4
lbl_800C13DC:
/* 0BBE3C 800C13DC 80610018 */  lwz     r3, 0x18(r1)
/* 0BBE40 800C13E0 4BFFC55D */  bl      __CARDGetDirBlock
/* 0BBE44 800C13E4 57E03032 */  slwi    r0, r31, 6
/* 0BBE48 800C13E8 7FE30214 */  add     r31, r3, r0
/* 0BBE4C 800C13EC 80610018 */  lwz     r3, 0x18(r1)
/* 0BBE50 800C13F0 7FE4FB78 */  mr      r4, r31
/* 0BBE54 800C13F4 4BFFEAB5 */  bl      __CARDIsWritable
/* 0BBE58 800C13F8 7C641B79 */  or.     r4, r3, r3
/* 0BBE5C 800C13FC 40800010 */  bge     lbl_800C140C
/* 0BBE60 800C1400 80610018 */  lwz     r3, 0x18(r1)
/* 0BBE64 800C1404 4BFFA971 */  bl      __CARDPutControlBlock
/* 0BBE68 800C1408 4800009C */  b       lbl_800C14A4
lbl_800C140C:
/* 0BBE6C 800C140C 881D002E */  lbz     r0, 0x2e(r29)
/* 0BBE70 800C1410 387F0000 */  addi    r3, r31, 0
/* 0BBE74 800C1414 389D0000 */  addi    r4, r29, 0
/* 0BBE78 800C1418 981F0007 */  stb     r0, 7(r31)
/* 0BBE7C 800C141C 801D0030 */  lwz     r0, 0x30(r29)
/* 0BBE80 800C1420 901F002C */  stw     r0, 0x2c(r31)
/* 0BBE84 800C1424 A01D0034 */  lhz     r0, 0x34(r29)
/* 0BBE88 800C1428 B01F0030 */  sth     r0, 0x30(r31)
/* 0BBE8C 800C142C A01D0036 */  lhz     r0, 0x36(r29)
/* 0BBE90 800C1430 B01F0032 */  sth     r0, 0x32(r31)
/* 0BBE94 800C1434 801D0038 */  lwz     r0, 0x38(r29)
/* 0BBE98 800C1438 901F003C */  stw     r0, 0x3c(r31)
/* 0BBE9C 800C143C 4BFFFC09 */  bl      UpdateIconOffsets
/* 0BBEA0 800C1440 807F002C */  lwz     r3, 0x2c(r31)
/* 0BBEA4 800C1444 3C030001 */  addis   r0, r3, 1
/* 0BBEA8 800C1448 2800FFFF */  cmplwi  r0, 0xffff
/* 0BBEAC 800C144C 40820014 */  bne     lbl_800C1460
/* 0BBEB0 800C1450 A01F0032 */  lhz     r0, 0x32(r31)
/* 0BBEB4 800C1454 5400003A */  rlwinm  r0, r0, 0, 0, 0x1d
/* 0BBEB8 800C1458 60000001 */  ori     r0, r0, 1
/* 0BBEBC 800C145C B01F0032 */  sth     r0, 0x32(r31)
lbl_800C1460:
/* 0BBEC0 800C1460 3C608000 */  lis     r3, 0x8000
/* 0BBEC4 800C1464 800300F8 */  lwz     r0, 0xf8(r3)
/* 0BBEC8 800C1468 541DF0BE */  srwi    r29, r0, 2
/* 0BBECC 800C146C 4BFE0E3D */  bl      OSGetTime
/* 0BBED0 800C1470 38DD0000 */  addi    r6, r29, 0
/* 0BBED4 800C1474 38A00000 */  li      r5, 0
/* 0BBED8 800C1478 4800C5A5 */  bl      __div2i
/* 0BBEDC 800C147C 909F0028 */  stw     r4, 0x28(r31)
/* 0BBEE0 800C1480 387C0000 */  addi    r3, r28, 0
/* 0BBEE4 800C1484 389E0000 */  addi    r4, r30, 0
/* 0BBEE8 800C1488 4BFFC655 */  bl      __CARDUpdateDir
/* 0BBEEC 800C148C 7C7C1B79 */  or.     r28, r3, r3
/* 0BBEF0 800C1490 40800010 */  bge     lbl_800C14A0
/* 0BBEF4 800C1494 80610018 */  lwz     r3, 0x18(r1)
/* 0BBEF8 800C1498 7F84E378 */  mr      r4, r28
/* 0BBEFC 800C149C 4BFFA8D9 */  bl      __CARDPutControlBlock
lbl_800C14A0:
/* 0BBF00 800C14A0 7F83E378 */  mr      r3, r28
lbl_800C14A4:
/* 0BBF04 800C14A4 80010034 */  lwz     r0, 0x34(r1)
/* 0BBF08 800C14A8 83E1002C */  lwz     r31, 0x2c(r1)
/* 0BBF0C 800C14AC 83C10028 */  lwz     r30, 0x28(r1)
/* 0BBF10 800C14B0 83A10024 */  lwz     r29, 0x24(r1)
/* 0BBF14 800C14B4 83810020 */  lwz     r28, 0x20(r1)
/* 0BBF18 800C14B8 38210030 */  addi    r1, r1, 0x30
/* 0BBF1C 800C14BC 7C0803A6 */  mtlr    r0
/* 0BBF20 800C14C0 4E800020 */  blr     
