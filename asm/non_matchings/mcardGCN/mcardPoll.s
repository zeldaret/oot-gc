glabel mcardPoll
/* 015BC8 8001B168 7C0802A6 */  mflr    r0
/* 015BCC 8001B16C 3C808010 */  lis     r4, mCard@ha
/* 015BD0 8001B170 90010004 */  stw     r0, 4(r1)
/* 015BD4 8001B174 388479B0 */  addi    r4, r4, mCard@l
/* 015BD8 8001B178 9421FFE8 */  stwu    r1, -0x18(r1)
/* 015BDC 8001B17C 93E10014 */  stw     r31, 0x14(r1)
/* 015BE0 8001B180 3BE30000 */  addi    r31, r3, 0
/* 015BE4 8001B184 80040470 */  lwz     r0, 0x470(r4)
/* 015BE8 8001B188 2C000001 */  cmpwi   r0, 1
/* 015BEC 8001B18C 408200B0 */  bne     lbl_8001B23C
/* 015BF0 8001B190 807F0360 */  lwz     r3, 0x360(r31)
/* 015BF4 8001B194 480A0C45 */  bl      CARDGetResultCode
/* 015BF8 8001B198 38830000 */  addi    r4, r3, 0
/* 015BFC 8001B19C 387F0000 */  addi    r3, r31, 0
/* 015C00 8001B1A0 48001101 */  bl      mcardGCErrorHandler
/* 015C04 8001B1A4 801F035C */  lwz     r0, 0x35c(r31)
/* 015C08 8001B1A8 2C000001 */  cmpwi   r0, 1
/* 015C0C 8001B1AC 41820084 */  beq     lbl_8001B230
/* 015C10 8001B1B0 2C000000 */  cmpwi   r0, 0
/* 015C14 8001B1B4 4182007C */  beq     lbl_8001B230
/* 015C18 8001B1B8 38600000 */  li      r3, 0
/* 015C1C 8001B1BC 48000084 */  b       lbl_8001B240
/* 015C20 8001B1C0 48000070 */  b       lbl_8001B230
lbl_8001B1C4:
/* 015C24 8001B1C4 807F0360 */  lwz     r3, 0x360(r31)
/* 015C28 8001B1C8 480A0C11 */  bl      CARDGetResultCode
/* 015C2C 8001B1CC 38830000 */  addi    r4, r3, 0
/* 015C30 8001B1D0 387F0000 */  addi    r3, r31, 0
/* 015C34 8001B1D4 480010CD */  bl      mcardGCErrorHandler
/* 015C38 8001B1D8 801F035C */  lwz     r0, 0x35c(r31)
/* 015C3C 8001B1DC 2C000001 */  cmpwi   r0, 1
/* 015C40 8001B1E0 41820014 */  beq     lbl_8001B1F4
/* 015C44 8001B1E4 2C000000 */  cmpwi   r0, 0
/* 015C48 8001B1E8 4182000C */  beq     lbl_8001B1F4
/* 015C4C 8001B1EC 38600000 */  li      r3, 0
/* 015C50 8001B1F0 48000050 */  b       lbl_8001B240
lbl_8001B1F4:
/* 015C54 8001B1F4 801F0364 */  lwz     r0, 0x364(r31)
/* 015C58 8001B1F8 28000000 */  cmplwi  r0, 0
/* 015C5C 8001B1FC 41820034 */  beq     lbl_8001B230
/* 015C60 8001B200 38600000 */  li      r3, 0
/* 015C64 8001B204 38800000 */  li      r4, 0
/* 015C68 8001B208 38A00000 */  li      r5, 0
/* 015C6C 8001B20C 38C00000 */  li      r6, 0
/* 015C70 8001B210 4BFED9CD */  bl      simulatorTestReset
/* 015C74 8001B214 2C030000 */  cmpwi   r3, 0
/* 015C78 8001B218 4082000C */  bne     lbl_8001B224
/* 015C7C 8001B21C 38600000 */  li      r3, 0
/* 015C80 8001B220 48000020 */  b       lbl_8001B240
lbl_8001B224:
/* 015C84 8001B224 819F0364 */  lwz     r12, 0x364(r31)
/* 015C88 8001B228 7D8803A6 */  mtlr    r12
/* 015C8C 8001B22C 4E800021 */  blrl    
lbl_8001B230:
/* 015C90 8001B230 801F035C */  lwz     r0, 0x35c(r31)
/* 015C94 8001B234 2C000001 */  cmpwi   r0, 1
/* 015C98 8001B238 4182FF8C */  beq     lbl_8001B1C4
lbl_8001B23C:
/* 015C9C 8001B23C 38600001 */  li      r3, 1
lbl_8001B240:
/* 015CA0 8001B240 8001001C */  lwz     r0, 0x1c(r1)
/* 015CA4 8001B244 83E10014 */  lwz     r31, 0x14(r1)
/* 015CA8 8001B248 38210018 */  addi    r1, r1, 0x18
/* 015CAC 8001B24C 7C0803A6 */  mtlr    r0
/* 015CB0 8001B250 4E800020 */  blr     
