glabel flashCopyFLASH
/* 088A54 8008DFF4 7C0802A6 */  mflr    r0
/* 088A58 8008DFF8 90010004 */  stw     r0, 4(r1)
/* 088A5C 8008DFFC 9421FFD8 */  stwu    r1, -0x28(r1)
/* 088A60 8008E000 93E10024 */  stw     r31, 0x24(r1)
/* 088A64 8008E004 3BE50000 */  addi    r31, r5, 0
/* 088A68 8008E008 38A40000 */  addi    r5, r4, 0
/* 088A6C 8008E00C 93C10020 */  stw     r30, 0x20(r1)
/* 088A70 8008E010 7C7E1B78 */  mr      r30, r3
/* 088A74 8008E014 38810018 */  addi    r4, r1, 0x18
/* 088A78 8008E018 90C10014 */  stw     r6, 0x14(r1)
/* 088A7C 8008E01C 38C10014 */  addi    r6, r1, 0x14
/* 088A80 8008E020 80630000 */  lwz     r3, 0(r3)
/* 088A84 8008E024 8063002C */  lwz     r3, 0x2c(r3)
/* 088A88 8008E028 4BFDF079 */  bl      ramGetBuffer
/* 088A8C 8008E02C 2C030000 */  cmpwi   r3, 0
/* 088A90 8008E030 4082000C */  bne     lbl_8008E03C
/* 088A94 8008E034 38600000 */  li      r3, 0
/* 088A98 8008E038 480000E8 */  b       lbl_8008E120
lbl_8008E03C:
/* 088A9C 8008E03C 809E000C */  lwz     r4, 0xc(r30)
/* 088AA0 8008E040 3C00F000 */  lis     r0, 0xf000
/* 088AA4 8008E044 80610018 */  lwz     r3, 0x18(r1)
/* 088AA8 8008E048 90830000 */  stw     r4, 0(r3)
/* 088AAC 8008E04C 807E0004 */  lwz     r3, 4(r30)
/* 088AB0 8008E050 5463000E */  rlwinm  r3, r3, 0, 0, 7
/* 088AB4 8008E054 7C030000 */  cmpw    r3, r0
/* 088AB8 8008E058 418200A4 */  beq     lbl_8008E0FC
/* 088ABC 8008E05C 40800044 */  bge     lbl_8008E0A0
/* 088AC0 8008E060 3C00D200 */  lis     r0, 0xd200
/* 088AC4 8008E064 7C030000 */  cmpw    r3, r0
/* 088AC8 8008E068 418200B4 */  beq     lbl_8008E11C
/* 088ACC 8008E06C 40800024 */  bge     lbl_8008E090
/* 088AD0 8008E070 3C00B400 */  lis     r0, 0xb400
/* 088AD4 8008E074 7C030000 */  cmpw    r3, r0
/* 088AD8 8008E078 418200A4 */  beq     lbl_8008E11C
/* 088ADC 8008E07C 408000A0 */  bge     lbl_8008E11C
/* 088AE0 8008E080 3C00A500 */  lis     r0, 0xa500
/* 088AE4 8008E084 7C030000 */  cmpw    r3, r0
/* 088AE8 8008E088 41820094 */  beq     lbl_8008E11C
/* 088AEC 8008E08C 48000090 */  b       lbl_8008E11C
lbl_8008E090:
/* 088AF0 8008E090 3C00E100 */  lis     r0, 0xe100
/* 088AF4 8008E094 7C030000 */  cmpw    r3, r0
/* 088AF8 8008E098 41820044 */  beq     lbl_8008E0DC
/* 088AFC 8008E09C 48000080 */  b       lbl_8008E11C
lbl_8008E0A0:
/* 088B00 8008E0A0 3C004B00 */  lis     r0, 0x4b00
/* 088B04 8008E0A4 7C030000 */  cmpw    r3, r0
/* 088B08 8008E0A8 41820074 */  beq     lbl_8008E11C
/* 088B0C 8008E0AC 40800020 */  bge     lbl_8008E0CC
/* 088B10 8008E0B0 3C003C00 */  lis     r0, 0x3c00
/* 088B14 8008E0B4 7C030000 */  cmpw    r3, r0
/* 088B18 8008E0B8 41820064 */  beq     lbl_8008E11C
/* 088B1C 8008E0BC 40800060 */  bge     lbl_8008E11C
/* 088B20 8008E0C0 2C030000 */  cmpwi   r3, 0
/* 088B24 8008E0C4 41820058 */  beq     lbl_8008E11C
/* 088B28 8008E0C8 48000054 */  b       lbl_8008E11C
lbl_8008E0CC:
/* 088B2C 8008E0CC 3C007800 */  lis     r0, 0x7800
/* 088B30 8008E0D0 7C030000 */  cmpw    r3, r0
/* 088B34 8008E0D4 41820048 */  beq     lbl_8008E11C
/* 088B38 8008E0D8 48000044 */  b       lbl_8008E11C
lbl_8008E0DC:
/* 088B3C 8008E0DC 80BE000C */  lwz     r5, 0xc(r30)
/* 088B40 8008E0E0 3C6000C2 */  lis     r3, 0xc2
/* 088B44 8008E0E4 80810018 */  lwz     r4, 0x18(r1)
/* 088B48 8008E0E8 3803001E */  addi    r0, r3, 0x1e
/* 088B4C 8008E0EC 90A40000 */  stw     r5, 0(r4)
/* 088B50 8008E0F0 80610018 */  lwz     r3, 0x18(r1)
/* 088B54 8008E0F4 90030004 */  stw     r0, 4(r3)
/* 088B58 8008E0F8 48000024 */  b       lbl_8008E11C
lbl_8008E0FC:
/* 088B5C 8008E0FC 80810018 */  lwz     r4, 0x18(r1)
/* 088B60 8008E100 57E309FC */  rlwinm  r3, r31, 1, 7, 0x1e
/* 088B64 8008E104 80A10014 */  lwz     r5, 0x14(r1)
/* 088B68 8008E108 4BF7AD39 */  bl      simulatorReadFLASH
/* 088B6C 8008E10C 2C030000 */  cmpwi   r3, 0
/* 088B70 8008E110 4082000C */  bne     lbl_8008E11C
/* 088B74 8008E114 38600000 */  li      r3, 0
/* 088B78 8008E118 48000008 */  b       lbl_8008E120
lbl_8008E11C:
/* 088B7C 8008E11C 38600001 */  li      r3, 1
lbl_8008E120:
/* 088B80 8008E120 8001002C */  lwz     r0, 0x2c(r1)
/* 088B84 8008E124 83E10024 */  lwz     r31, 0x24(r1)
/* 088B88 8008E128 83C10020 */  lwz     r30, 0x20(r1)
/* 088B8C 8008E12C 7C0803A6 */  mtlr    r0
/* 088B90 8008E130 38210028 */  addi    r1, r1, 0x28
/* 088B94 8008E134 4E800020 */  blr     