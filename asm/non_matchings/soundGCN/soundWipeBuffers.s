glabel soundWipeBuffers
/* 017CB0 8001D250 7C0802A6 */  mflr    r0
/* 017CB4 8001D254 90010004 */  stw     r0, 4(r1)
/* 017CB8 8001D258 9421FFE8 */  stwu    r1, -0x18(r1)
/* 017CBC 8001D25C 93E10014 */  stw     r31, 0x14(r1)
/* 017CC0 8001D260 7C7F1B78 */  mr      r31, r3
/* 017CC4 8001D264 93C10010 */  stw     r30, 0x10(r1)
/* 017CC8 8001D268 800300B8 */  lwz     r0, 0xb8(r3)
/* 017CCC 8001D26C 28000000 */  cmplwi  r0, 0
/* 017CD0 8001D270 4182001C */  beq     lbl_8001D28C
/* 017CD4 8001D274 387F00B8 */  addi    r3, r31, 0xb8
/* 017CD8 8001D278 4BFE9E21 */  bl      xlHeapFree
/* 017CDC 8001D27C 2C030000 */  cmpwi   r3, 0
/* 017CE0 8001D280 4082000C */  bne     lbl_8001D28C
/* 017CE4 8001D284 38600000 */  li      r3, 0
/* 017CE8 8001D288 480000AC */  b       lbl_8001D334
lbl_8001D28C:
/* 017CEC 8001D28C 801F00BC */  lwz     r0, 0xbc(r31)
/* 017CF0 8001D290 28000000 */  cmplwi  r0, 0
/* 017CF4 8001D294 4182001C */  beq     lbl_8001D2B0
/* 017CF8 8001D298 387F00BC */  addi    r3, r31, 0xbc
/* 017CFC 8001D29C 4BFE9DFD */  bl      xlHeapFree
/* 017D00 8001D2A0 2C030000 */  cmpwi   r3, 0
/* 017D04 8001D2A4 4082000C */  bne     lbl_8001D2B0
/* 017D08 8001D2A8 38600000 */  li      r3, 0
/* 017D0C 8001D2AC 48000088 */  b       lbl_8001D334
lbl_8001D2B0:
/* 017D10 8001D2B0 801F00C0 */  lwz     r0, 0xc0(r31)
/* 017D14 8001D2B4 28000000 */  cmplwi  r0, 0
/* 017D18 8001D2B8 4182001C */  beq     lbl_8001D2D4
/* 017D1C 8001D2BC 387F00C0 */  addi    r3, r31, 0xc0
/* 017D20 8001D2C0 4BFE9DD9 */  bl      xlHeapFree
/* 017D24 8001D2C4 2C030000 */  cmpwi   r3, 0
/* 017D28 8001D2C8 4082000C */  bne     lbl_8001D2D4
/* 017D2C 8001D2CC 38600000 */  li      r3, 0
/* 017D30 8001D2D0 48000064 */  b       lbl_8001D334
lbl_8001D2D4:
/* 017D34 8001D2D4 801F00C4 */  lwz     r0, 0xc4(r31)
/* 017D38 8001D2D8 28000000 */  cmplwi  r0, 0
/* 017D3C 8001D2DC 4182001C */  beq     lbl_8001D2F8
/* 017D40 8001D2E0 387F00C4 */  addi    r3, r31, 0xc4
/* 017D44 8001D2E4 4BFE9DB5 */  bl      xlHeapFree
/* 017D48 8001D2E8 2C030000 */  cmpwi   r3, 0
/* 017D4C 8001D2EC 4082000C */  bne     lbl_8001D2F8
/* 017D50 8001D2F0 38600000 */  li      r3, 0
/* 017D54 8001D2F4 48000040 */  b       lbl_8001D334
lbl_8001D2F8:
/* 017D58 8001D2F8 3BC00000 */  li      r30, 0
lbl_8001D2FC:
/* 017D5C 8001D2FC 801F0010 */  lwz     r0, 0x10(r31)
/* 017D60 8001D300 28000000 */  cmplwi  r0, 0
/* 017D64 8001D304 4182001C */  beq     lbl_8001D320
/* 017D68 8001D308 387F0010 */  addi    r3, r31, 0x10
/* 017D6C 8001D30C 4BFE9D8D */  bl      xlHeapFree
/* 017D70 8001D310 2C030000 */  cmpwi   r3, 0
/* 017D74 8001D314 4082000C */  bne     lbl_8001D320
/* 017D78 8001D318 38600000 */  li      r3, 0
/* 017D7C 8001D31C 48000018 */  b       lbl_8001D334
lbl_8001D320:
/* 017D80 8001D320 3BDE0001 */  addi    r30, r30, 1
/* 017D84 8001D324 2C1E0010 */  cmpwi   r30, 0x10
/* 017D88 8001D328 3BFF0004 */  addi    r31, r31, 4
/* 017D8C 8001D32C 4180FFD0 */  blt     lbl_8001D2FC
/* 017D90 8001D330 38600001 */  li      r3, 1
lbl_8001D334:
/* 017D94 8001D334 8001001C */  lwz     r0, 0x1c(r1)
/* 017D98 8001D338 83E10014 */  lwz     r31, 0x14(r1)
/* 017D9C 8001D33C 83C10010 */  lwz     r30, 0x10(r1)
/* 017DA0 8001D340 7C0803A6 */  mtlr    r0
/* 017DA4 8001D344 38210018 */  addi    r1, r1, 0x18
/* 017DA8 8001D348 4E800020 */  blr     
