glabel mcardCalculateChecksumFileBlock2
/* 0169D0 8001BF70 3CA08010 */  lis     r5, mCard@ha
/* 0169D4 8001BF74 38A579B0 */  addi    r5, r5, mCard@l
/* 0169D8 8001BF78 80050470 */  lwz     r0, 0x470(r5)
/* 0169DC 8001BF7C 2C000001 */  cmpwi   r0, 1
/* 0169E0 8001BF80 40820150 */  bne     lbl_8001C0D0
/* 0169E4 8001BF84 38E00000 */  li      r7, 0
/* 0169E8 8001BF88 38000100 */  li      r0, 0x100
/* 0169EC 8001BF8C 90E40000 */  stw     r7, 0(r4)
/* 0169F0 8001BF90 7C0903A6 */  mtctr   r0
/* 0169F4 8001BF94 39000000 */  li      r8, 0
lbl_8001BF98:
/* 0169F8 8001BF98 2808041B */  cmplwi  r8, 0x41b
/* 0169FC 8001BF9C 41820018 */  beq     lbl_8001BFB4
/* 016A00 8001BFA0 80A30474 */  lwz     r5, 0x474(r3)
/* 016A04 8001BFA4 80C40000 */  lwz     r6, 0(r4)
/* 016A08 8001BFA8 7C05382E */  lwzx    r0, r5, r7
/* 016A0C 8001BFAC 7C060214 */  add     r0, r6, r0
/* 016A10 8001BFB0 90040000 */  stw     r0, 0(r4)
lbl_8001BFB4:
/* 016A14 8001BFB4 39080001 */  addi    r8, r8, 1
/* 016A18 8001BFB8 2808041B */  cmplwi  r8, 0x41b
/* 016A1C 8001BFBC 38E70004 */  addi    r7, r7, 4
/* 016A20 8001BFC0 41820018 */  beq     lbl_8001BFD8
/* 016A24 8001BFC4 80A30474 */  lwz     r5, 0x474(r3)
/* 016A28 8001BFC8 80C40000 */  lwz     r6, 0(r4)
/* 016A2C 8001BFCC 7C05382E */  lwzx    r0, r5, r7
/* 016A30 8001BFD0 7C060214 */  add     r0, r6, r0
/* 016A34 8001BFD4 90040000 */  stw     r0, 0(r4)
lbl_8001BFD8:
/* 016A38 8001BFD8 39080001 */  addi    r8, r8, 1
/* 016A3C 8001BFDC 2808041B */  cmplwi  r8, 0x41b
/* 016A40 8001BFE0 38E70004 */  addi    r7, r7, 4
/* 016A44 8001BFE4 41820018 */  beq     lbl_8001BFFC
/* 016A48 8001BFE8 80A30474 */  lwz     r5, 0x474(r3)
/* 016A4C 8001BFEC 80C40000 */  lwz     r6, 0(r4)
/* 016A50 8001BFF0 7C05382E */  lwzx    r0, r5, r7
/* 016A54 8001BFF4 7C060214 */  add     r0, r6, r0
/* 016A58 8001BFF8 90040000 */  stw     r0, 0(r4)
lbl_8001BFFC:
/* 016A5C 8001BFFC 39080001 */  addi    r8, r8, 1
/* 016A60 8001C000 2808041B */  cmplwi  r8, 0x41b
/* 016A64 8001C004 38E70004 */  addi    r7, r7, 4
/* 016A68 8001C008 41820018 */  beq     lbl_8001C020
/* 016A6C 8001C00C 80A30474 */  lwz     r5, 0x474(r3)
/* 016A70 8001C010 80C40000 */  lwz     r6, 0(r4)
/* 016A74 8001C014 7C05382E */  lwzx    r0, r5, r7
/* 016A78 8001C018 7C060214 */  add     r0, r6, r0
/* 016A7C 8001C01C 90040000 */  stw     r0, 0(r4)
lbl_8001C020:
/* 016A80 8001C020 39080001 */  addi    r8, r8, 1
/* 016A84 8001C024 2808041B */  cmplwi  r8, 0x41b
/* 016A88 8001C028 38E70004 */  addi    r7, r7, 4
/* 016A8C 8001C02C 41820018 */  beq     lbl_8001C044
/* 016A90 8001C030 80A30474 */  lwz     r5, 0x474(r3)
/* 016A94 8001C034 80C40000 */  lwz     r6, 0(r4)
/* 016A98 8001C038 7C05382E */  lwzx    r0, r5, r7
/* 016A9C 8001C03C 7C060214 */  add     r0, r6, r0
/* 016AA0 8001C040 90040000 */  stw     r0, 0(r4)
lbl_8001C044:
/* 016AA4 8001C044 39080001 */  addi    r8, r8, 1
/* 016AA8 8001C048 2808041B */  cmplwi  r8, 0x41b
/* 016AAC 8001C04C 38E70004 */  addi    r7, r7, 4
/* 016AB0 8001C050 41820018 */  beq     lbl_8001C068
/* 016AB4 8001C054 80A30474 */  lwz     r5, 0x474(r3)
/* 016AB8 8001C058 80C40000 */  lwz     r6, 0(r4)
/* 016ABC 8001C05C 7C05382E */  lwzx    r0, r5, r7
/* 016AC0 8001C060 7C060214 */  add     r0, r6, r0
/* 016AC4 8001C064 90040000 */  stw     r0, 0(r4)
lbl_8001C068:
/* 016AC8 8001C068 39080001 */  addi    r8, r8, 1
/* 016ACC 8001C06C 2808041B */  cmplwi  r8, 0x41b
/* 016AD0 8001C070 38E70004 */  addi    r7, r7, 4
/* 016AD4 8001C074 41820018 */  beq     lbl_8001C08C
/* 016AD8 8001C078 80A30474 */  lwz     r5, 0x474(r3)
/* 016ADC 8001C07C 80C40000 */  lwz     r6, 0(r4)
/* 016AE0 8001C080 7C05382E */  lwzx    r0, r5, r7
/* 016AE4 8001C084 7C060214 */  add     r0, r6, r0
/* 016AE8 8001C088 90040000 */  stw     r0, 0(r4)
lbl_8001C08C:
/* 016AEC 8001C08C 39080001 */  addi    r8, r8, 1
/* 016AF0 8001C090 2808041B */  cmplwi  r8, 0x41b
/* 016AF4 8001C094 38E70004 */  addi    r7, r7, 4
/* 016AF8 8001C098 41820018 */  beq     lbl_8001C0B0
/* 016AFC 8001C09C 80A30474 */  lwz     r5, 0x474(r3)
/* 016B00 8001C0A0 80C40000 */  lwz     r6, 0(r4)
/* 016B04 8001C0A4 7C05382E */  lwzx    r0, r5, r7
/* 016B08 8001C0A8 7C060214 */  add     r0, r6, r0
/* 016B0C 8001C0AC 90040000 */  stw     r0, 0(r4)
lbl_8001C0B0:
/* 016B10 8001C0B0 38E70004 */  addi    r7, r7, 4
/* 016B14 8001C0B4 39080001 */  addi    r8, r8, 1
/* 016B18 8001C0B8 4200FEE0 */  bdnz    lbl_8001BF98
/* 016B1C 8001C0BC 80040000 */  lwz     r0, 0(r4)
/* 016B20 8001C0C0 2C000000 */  cmpwi   r0, 0
/* 016B24 8001C0C4 4082000C */  bne     lbl_8001C0D0
/* 016B28 8001C0C8 38000001 */  li      r0, 1
/* 016B2C 8001C0CC 90040000 */  stw     r0, 0(r4)
lbl_8001C0D0:
/* 016B30 8001C0D0 38600001 */  li      r3, 1
/* 016B34 8001C0D4 4E800020 */  blr     
