glabel pifEvent
/* 0668C8 8006BE68 7C0802A6 */  mflr    r0
/* 0668CC 8006BE6C 2C040003 */  cmpwi   r4, 3
/* 0668D0 8006BE70 90010004 */  stw     r0, 4(r1)
/* 0668D4 8006BE74 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0668D8 8006BE78 93E1001C */  stw     r31, 0x1c(r1)
/* 0668DC 8006BE7C 3BE50000 */  addi    r31, r5, 0
/* 0668E0 8006BE80 93C10018 */  stw     r30, 0x18(r1)
/* 0668E4 8006BE84 3BC30000 */  addi    r30, r3, 0
/* 0668E8 8006BE88 418200BC */  beq     lbl_8006BF44
/* 0668EC 8006BE8C 40800018 */  bge     lbl_8006BEA4
/* 0668F0 8006BE90 2C040002 */  cmpwi   r4, 2
/* 0668F4 8006BE94 40800028 */  bge     lbl_8006BEBC
/* 0668F8 8006BE98 2C040000 */  cmpwi   r4, 0
/* 0668FC 8006BE9C 408001D8 */  bge     lbl_8006C074
/* 066900 8006BEA0 480001CC */  b       lbl_8006C06C
lbl_8006BEA4:
/* 066904 8006BEA4 2C041003 */  cmpwi   r4, 0x1003
/* 066908 8006BEA8 418201CC */  beq     lbl_8006C074
/* 06690C 8006BEAC 408001C0 */  bge     lbl_8006C06C
/* 066910 8006BEB0 2C041002 */  cmpwi   r4, 0x1002
/* 066914 8006BEB4 40800138 */  bge     lbl_8006BFEC
/* 066918 8006BEB8 480001B4 */  b       lbl_8006C06C
lbl_8006BEBC:
/* 06691C 8006BEBC 93FE0008 */  stw     r31, 8(r30)
/* 066920 8006BEC0 387E0000 */  addi    r3, r30, 0
/* 066924 8006BEC4 38800800 */  li      r4, 0x800
/* 066928 8006BEC8 4BF9B2ED */  bl      xlHeapTake
/* 06692C 8006BECC 2C030000 */  cmpwi   r3, 0
/* 066930 8006BED0 4082000C */  bne     lbl_8006BEDC
/* 066934 8006BED4 38600000 */  li      r3, 0
/* 066938 8006BED8 480001A0 */  b       lbl_8006C078
lbl_8006BEDC:
/* 06693C 8006BEDC 387E0004 */  addi    r3, r30, 4
/* 066940 8006BEE0 38800040 */  li      r4, 0x40
/* 066944 8006BEE4 4BF9B2D1 */  bl      xlHeapTake
/* 066948 8006BEE8 2C030000 */  cmpwi   r3, 0
/* 06694C 8006BEEC 4082000C */  bne     lbl_8006BEF8
/* 066950 8006BEF0 38600000 */  li      r3, 0
/* 066954 8006BEF4 48000184 */  b       lbl_8006C078
lbl_8006BEF8:
/* 066958 8006BEF8 3BE00000 */  li      r31, 0
lbl_8006BEFC:
/* 06695C 8006BEFC 387E0000 */  addi    r3, r30, 0
/* 066960 8006BF00 389F0000 */  addi    r4, r31, 0
/* 066964 8006BF04 38A00000 */  li      r5, 0
/* 066968 8006BF08 48000A8D */  bl      pifSetControllerType
/* 06696C 8006BF0C 2C030000 */  cmpwi   r3, 0
/* 066970 8006BF10 4082000C */  bne     lbl_8006BF1C
/* 066974 8006BF14 38600000 */  li      r3, 0
/* 066978 8006BF18 48000160 */  b       lbl_8006C078
lbl_8006BF1C:
/* 06697C 8006BF1C 3BFF0001 */  addi    r31, r31, 1
/* 066980 8006BF20 2C1F0005 */  cmpwi   r31, 5
/* 066984 8006BF24 4180FFD8 */  blt     lbl_8006BEFC
/* 066988 8006BF28 387E0000 */  addi    r3, r30, 0
/* 06698C 8006BF2C 38800000 */  li      r4, 0
/* 066990 8006BF30 480009E9 */  bl      pifSetEEPROMType
/* 066994 8006BF34 2C030000 */  cmpwi   r3, 0
/* 066998 8006BF38 4082013C */  bne     lbl_8006C074
/* 06699C 8006BF3C 38600000 */  li      r3, 0
/* 0669A0 8006BF40 48000138 */  b       lbl_8006C078
lbl_8006BF44:
/* 0669A4 8006BF44 3BE00000 */  li      r31, 0
lbl_8006BF48:
/* 0669A8 8006BF48 387E0000 */  addi    r3, r30, 0
/* 0669AC 8006BF4C 389F0000 */  addi    r4, r31, 0
/* 0669B0 8006BF50 38A00000 */  li      r5, 0
/* 0669B4 8006BF54 48000A41 */  bl      pifSetControllerType
/* 0669B8 8006BF58 2C030000 */  cmpwi   r3, 0
/* 0669BC 8006BF5C 4082000C */  bne     lbl_8006BF68
/* 0669C0 8006BF60 38600000 */  li      r3, 0
/* 0669C4 8006BF64 48000114 */  b       lbl_8006C078
lbl_8006BF68:
/* 0669C8 8006BF68 3BFF0001 */  addi    r31, r31, 1
/* 0669CC 8006BF6C 2C1F0005 */  cmpwi   r31, 5
/* 0669D0 8006BF70 4180FFD8 */  blt     lbl_8006BF48
/* 0669D4 8006BF74 387E0000 */  addi    r3, r30, 0
/* 0669D8 8006BF78 38800000 */  li      r4, 0
/* 0669DC 8006BF7C 4800099D */  bl      pifSetEEPROMType
/* 0669E0 8006BF80 2C030000 */  cmpwi   r3, 0
/* 0669E4 8006BF84 4082000C */  bne     lbl_8006BF90
/* 0669E8 8006BF88 38600000 */  li      r3, 0
/* 0669EC 8006BF8C 480000EC */  b       lbl_8006C078
lbl_8006BF90:
/* 0669F0 8006BF90 801E0000 */  lwz     r0, 0(r30)
/* 0669F4 8006BF94 28000000 */  cmplwi  r0, 0
/* 0669F8 8006BF98 4182001C */  beq     lbl_8006BFB4
/* 0669FC 8006BF9C 7FC3F378 */  mr      r3, r30
/* 066A00 8006BFA0 4BF9B0F9 */  bl      xlHeapFree
/* 066A04 8006BFA4 2C030000 */  cmpwi   r3, 0
/* 066A08 8006BFA8 4082000C */  bne     lbl_8006BFB4
/* 066A0C 8006BFAC 38600000 */  li      r3, 0
/* 066A10 8006BFB0 480000C8 */  b       lbl_8006C078
lbl_8006BFB4:
/* 066A14 8006BFB4 38000000 */  li      r0, 0
/* 066A18 8006BFB8 901E0000 */  stw     r0, 0(r30)
/* 066A1C 8006BFBC 801E0004 */  lwz     r0, 4(r30)
/* 066A20 8006BFC0 28000000 */  cmplwi  r0, 0
/* 066A24 8006BFC4 4182001C */  beq     lbl_8006BFE0
/* 066A28 8006BFC8 387E0004 */  addi    r3, r30, 4
/* 066A2C 8006BFCC 4BF9B0CD */  bl      xlHeapFree
/* 066A30 8006BFD0 2C030000 */  cmpwi   r3, 0
/* 066A34 8006BFD4 4082000C */  bne     lbl_8006BFE0
/* 066A38 8006BFD8 38600000 */  li      r3, 0
/* 066A3C 8006BFDC 4800009C */  b       lbl_8006C078
lbl_8006BFE0:
/* 066A40 8006BFE0 38000000 */  li      r0, 0
/* 066A44 8006BFE4 901E0004 */  stw     r0, 4(r30)
/* 066A48 8006BFE8 4800008C */  b       lbl_8006C074
lbl_8006BFEC:
/* 066A4C 8006BFEC 807E0008 */  lwz     r3, 8(r30)
/* 066A50 8006BFF0 3CA08007 */  lis     r5, pifPut8@ha
/* 066A54 8006BFF4 3CC08007 */  lis     r6, pifPut16@ha
/* 066A58 8006BFF8 3CE08007 */  lis     r7, pifPut32@ha
/* 066A5C 8006BFFC 80630024 */  lwz     r3, 0x24(r3)
/* 066A60 8006C000 3C808007 */  lis     r4, pifPut64@ha
/* 066A64 8006C004 3904C82C */  addi    r8, r4, pifPut64@l
/* 066A68 8006C008 38A5C8B0 */  addi    r5, r5, pifPut8@l
/* 066A6C 8006C00C 38C6C888 */  addi    r6, r6, pifPut16@l
/* 066A70 8006C010 38E7C860 */  addi    r7, r7, pifPut32@l
/* 066A74 8006C014 389F0000 */  addi    r4, r31, 0
/* 066A78 8006C018 4BFC9021 */  bl      cpuSetDevicePut
/* 066A7C 8006C01C 2C030000 */  cmpwi   r3, 0
/* 066A80 8006C020 4082000C */  bne     lbl_8006C02C
/* 066A84 8006C024 38600000 */  li      r3, 0
/* 066A88 8006C028 48000050 */  b       lbl_8006C078
lbl_8006C02C:
/* 066A8C 8006C02C 807E0008 */  lwz     r3, 8(r30)
/* 066A90 8006C030 3CA08007 */  lis     r5, pifGet8@ha
/* 066A94 8006C034 3CC08007 */  lis     r6, pifGet16@ha
/* 066A98 8006C038 3CE08007 */  lis     r7, pifGet32@ha
/* 066A9C 8006C03C 80630024 */  lwz     r3, 0x24(r3)
/* 066AA0 8006C040 3C808007 */  lis     r4, pifGet64@ha
/* 066AA4 8006C044 3904C72C */  addi    r8, r4, pifGet64@l
/* 066AA8 8006C048 38A5C7F8 */  addi    r5, r5, pifGet8@l
/* 066AAC 8006C04C 38C6C7BC */  addi    r6, r6, pifGet16@l
/* 066AB0 8006C050 38E7C780 */  addi    r7, r7, pifGet32@l
/* 066AB4 8006C054 389F0000 */  addi    r4, r31, 0
/* 066AB8 8006C058 4BFC8FF9 */  bl      cpuSetDeviceGet
/* 066ABC 8006C05C 2C030000 */  cmpwi   r3, 0
/* 066AC0 8006C060 40820014 */  bne     lbl_8006C074
/* 066AC4 8006C064 38600000 */  li      r3, 0
/* 066AC8 8006C068 48000010 */  b       lbl_8006C078
lbl_8006C06C:
/* 066ACC 8006C06C 38600000 */  li      r3, 0
/* 066AD0 8006C070 48000008 */  b       lbl_8006C078
lbl_8006C074:
/* 066AD4 8006C074 38600001 */  li      r3, 1
lbl_8006C078:
/* 066AD8 8006C078 80010024 */  lwz     r0, 0x24(r1)
/* 066ADC 8006C07C 83E1001C */  lwz     r31, 0x1c(r1)
/* 066AE0 8006C080 83C10018 */  lwz     r30, 0x18(r1)
/* 066AE4 8006C084 7C0803A6 */  mtlr    r0
/* 066AE8 8006C088 38210020 */  addi    r1, r1, 0x20
/* 066AEC 8006C08C 4E800020 */  blr     
