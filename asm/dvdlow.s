# dvdlow.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __DVDInitWA
/* 0AC2EC 800B188C 7C0802A6 */  mflr    r0
/* 0AC2F0 800B1890 3C608013 */  lis     r3, CommandList@ha
/* 0AC2F4 800B1894 90010004 */  stw     r0, 4(r1)
/* 0AC2F8 800B1898 38000000 */  li      r0, 0
/* 0AC2FC 800B189C 38800000 */  li      r4, 0
/* 0AC300 800B18A0 9421FFF8 */  stwu    r1, -8(r1)
/* 0AC304 800B18A4 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
/* 0AC308 800B18A8 3800FFFF */  li      r0, -1
/* 0AC30C 800B18AC 900324B8 */  stw     r0, CommandList@l(r3)
/* 0AC310 800B18B0 38600000 */  li      r3, 0
/* 0AC314 800B18B4 48000DD9 */  bl      __DVDLowSetWAType
/* 0AC318 800B18B8 4BFEAE05 */  bl      OSInitAlarm
/* 0AC31C 800B18BC 8001000C */  lwz     r0, 0xc(r1)
/* 0AC320 800B18C0 38210008 */  addi    r1, r1, 8
/* 0AC324 800B18C4 7C0803A6 */  mtlr    r0
/* 0AC328 800B18C8 4E800020 */  blr     

glabel __DVDInterruptHandler
/* 0AC32C 800B18CC 7C0802A6 */  mflr    r0
/* 0AC330 800B18D0 3C608013 */  lis     r3, CommandList@ha
/* 0AC334 800B18D4 90010004 */  stw     r0, 4(r1)
/* 0AC338 800B18D8 9421FD10 */  stwu    r1, -0x2f0(r1)
/* 0AC33C 800B18DC BF6102DC */  stmw    r27, 0x2dc(r1)
/* 0AC340 800B18E0 3B840000 */  addi    r28, r4, 0
/* 0AC344 800B18E4 3BC324B8 */  addi    r30, r3, CommandList@l
/* 0AC348 800B18E8 3BA00000 */  li      r29, 0
/* 0AC34C 800B18EC 800D8D08 */  lwz     r0, LastCommandWasRead@sda21(r13)
/* 0AC350 800B18F0 2C000000 */  cmpwi   r0, 0
/* 0AC354 800B18F4 41820040 */  beq     lbl_800B1934
/* 0AC358 800B18F8 4BFF09D1 */  bl      __OSGetSystemTime
/* 0AC35C 800B18FC 908D8CFC */  stw     r4, (LastReadFinished + 4)@sda21(r13)
/* 0AC360 800B1900 38000000 */  li      r0, 0
/* 0AC364 800B1904 906D8CF8 */  stw     r3, LastReadFinished@sda21(r13)
/* 0AC368 800B1908 900D8808 */  stw     r0, FirstRead@sda21(r13)
/* 0AC36C 800B190C 801E00C4 */  lwz     r0, 0xc4(r30)
/* 0AC370 800B1910 901E00B8 */  stw     r0, 0xb8(r30)
/* 0AC374 800B1914 801E00C8 */  lwz     r0, 0xc8(r30)
/* 0AC378 800B1918 901E00BC */  stw     r0, 0xbc(r30)
/* 0AC37C 800B191C 801E00CC */  lwz     r0, 0xcc(r30)
/* 0AC380 800B1920 901E00C0 */  stw     r0, 0xc0(r30)
/* 0AC384 800B1924 800D8CC8 */  lwz     r0, StopAtNextInt@sda21(r13)
/* 0AC388 800B1928 2C000001 */  cmpwi   r0, 1
/* 0AC38C 800B192C 40820008 */  bne     lbl_800B1934
/* 0AC390 800B1930 63BD0008 */  ori     r29, r29, 8
lbl_800B1934:
/* 0AC394 800B1934 38000000 */  li      r0, 0
/* 0AC398 800B1938 900D8D08 */  stw     r0, LastCommandWasRead@sda21(r13)
/* 0AC39C 800B193C 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AC3A0 800B1940 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0AC3A4 800B1944 80036000 */  lwz     r0, (DI_REGS_BASE + DI_DISR)@l(r3)
/* 0AC3A8 800B1948 701F002A */  andi.   r31, r0, 0x2a
/* 0AC3AC 800B194C 70030054 */  andi.   r3, r0, 0x54
/* 0AC3B0 800B1950 57E0083C */  slwi    r0, r31, 1
/* 0AC3B4 800B1954 7C7B0038 */  and     r27, r3, r0
/* 0AC3B8 800B1958 57600673 */  rlwinm. r0, r27, 0, 0x19, 0x19
/* 0AC3BC 800B195C 41820008 */  beq     lbl_800B1964
/* 0AC3C0 800B1960 63BD0008 */  ori     r29, r29, 8
lbl_800B1964:
/* 0AC3C4 800B1964 576006F7 */  rlwinm. r0, r27, 0, 0x1b, 0x1b
/* 0AC3C8 800B1968 41820008 */  beq     lbl_800B1970
/* 0AC3CC 800B196C 63BD0001 */  ori     r29, r29, 1
lbl_800B1970:
/* 0AC3D0 800B1970 5760077B */  rlwinm. r0, r27, 0, 0x1d, 0x1d
/* 0AC3D4 800B1974 41820008 */  beq     lbl_800B197C
/* 0AC3D8 800B1978 63BD0002 */  ori     r29, r29, 2
lbl_800B197C:
/* 0AC3DC 800B197C 281D0000 */  cmplwi  r29, 0
/* 0AC3E0 800B1980 41820014 */  beq     lbl_800B1994
/* 0AC3E4 800B1984 38000000 */  li      r0, 0
/* 0AC3E8 800B1988 900D8CE0 */  stw     r0, ResetOccurred@sda21(r13)
/* 0AC3EC 800B198C 387E0068 */  addi    r3, r30, 0x68
/* 0AC3F0 800B1990 4BFEB04D */  bl      OSCancelAlarm
lbl_800B1994:
/* 0AC3F4 800B1994 7F60FB78 */  or      r0, r27, r31
/* 0AC3F8 800B1998 3FE0CC00 */  lis     r31, DI_REGS_BASE@ha
/* 0AC3FC 800B199C 901F6000 */  stw     r0, (DI_REGS_BASE + DI_DISR)@l(r31)
/* 0AC400 800B19A0 800D8CE0 */  lwz     r0, ResetOccurred@sda21(r13)
/* 0AC404 800B19A4 28000000 */  cmplwi  r0, 0
/* 0AC408 800B19A8 418200A0 */  beq     lbl_800B1A48
/* 0AC40C 800B19AC 4BFF091D */  bl      __OSGetSystemTime
/* 0AC410 800B19B0 3CA08000 */  lis     r5, 0x8000
/* 0AC414 800B19B4 80ED8CD8 */  lwz     r7, LastResetEnd@sda21(r13)
/* 0AC418 800B19B8 80C500F8 */  lwz     r6, 0xf8(r5)
/* 0AC41C 800B19BC 3CA01062 */  lis     r5, 0x1062
/* 0AC420 800B19C0 38A54DD3 */  addi    r5, r5, 0x4dd3
/* 0AC424 800B19C4 810D8CDC */  lwz     r8, (LastResetEnd + 4)@sda21(r13)
/* 0AC428 800B19C8 54C6F0BE */  srwi    r6, r6, 2
/* 0AC42C 800B19CC 7CA53016 */  mulhwu  r5, r5, r6
/* 0AC430 800B19D0 54A5D1BE */  srwi    r5, r5, 6
/* 0AC434 800B19D4 1CA500C8 */  mulli   r5, r5, 0xc8
/* 0AC438 800B19D8 7CC82010 */  subfc   r6, r8, r4
/* 0AC43C 800B19DC 7C671910 */  subfe   r3, r7, r3
/* 0AC440 800B19E0 38000000 */  li      r0, 0
/* 0AC444 800B19E4 6C648000 */  xoris   r4, r3, 0x8000
/* 0AC448 800B19E8 6C038000 */  xoris   r3, r0, 0x8000
/* 0AC44C 800B19EC 7C053010 */  subfc   r0, r5, r6
/* 0AC450 800B19F0 7C632110 */  subfe   r3, r3, r4
/* 0AC454 800B19F4 7C642110 */  subfe   r3, r4, r4
/* 0AC458 800B19F8 7C6300D1 */  neg.    r3, r3
/* 0AC45C 800B19FC 4182004C */  beq     lbl_800B1A48
/* 0AC460 800B1A00 3B7F6000 */  addi    r27, r31, DI_REGS_BASE@l
/* 0AC464 800B1A04 841B0004 */  lwzu    r0, DI_DICVR(r27)
/* 0AC468 800B1A08 5403077A */  rlwinm  r3, r0, 0, 0x1d, 0x1d
/* 0AC46C 800B1A0C 54000F7A */  rlwinm  r0, r0, 1, 0x1d, 0x1d
/* 0AC470 800B1A10 7C600038 */  and     r0, r3, r0
/* 0AC474 800B1A14 5400077B */  rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 0AC478 800B1A18 41820024 */  beq     lbl_800B1A3C
/* 0AC47C 800B1A1C 818D8CD4 */  lwz     r12, ResetCoverCallback@sda21(r13)
/* 0AC480 800B1A20 280C0000 */  cmplwi  r12, 0
/* 0AC484 800B1A24 41820010 */  beq     lbl_800B1A34
/* 0AC488 800B1A28 7D8803A6 */  mtlr    r12
/* 0AC48C 800B1A2C 38600004 */  li      r3, 4
/* 0AC490 800B1A30 4E800021 */  blrl    
lbl_800B1A34:
/* 0AC494 800B1A34 38000000 */  li      r0, 0
/* 0AC498 800B1A38 900D8CD4 */  stw     r0, ResetCoverCallback@sda21(r13)
lbl_800B1A3C:
/* 0AC49C 800B1A3C 801B0000 */  lwz     r0, 0(r27)
/* 0AC4A0 800B1A40 901B0000 */  stw     r0, 0(r27)
/* 0AC4A4 800B1A44 48000058 */  b       lbl_800B1A9C
lbl_800B1A48:
/* 0AC4A8 800B1A48 800D8CE4 */  lwz     r0, WaitingCoverClose@sda21(r13)
/* 0AC4AC 800B1A4C 2C000000 */  cmpwi   r0, 0
/* 0AC4B0 800B1A50 41820040 */  beq     lbl_800B1A90
/* 0AC4B4 800B1A54 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AC4B8 800B1A58 38A36000 */  addi    r5, r3, DI_REGS_BASE@l
/* 0AC4BC 800B1A5C 84050004 */  lwzu    r0, DI_DICVR(r5)
/* 0AC4C0 800B1A60 540407BC */  rlwinm  r4, r0, 0, 0x1e, 0x1e
/* 0AC4C4 800B1A64 5403077A */  rlwinm  r3, r0, 0, 0x1d, 0x1d
/* 0AC4C8 800B1A68 54000F7A */  rlwinm  r0, r0, 1, 0x1d, 0x1d
/* 0AC4CC 800B1A6C 7C630038 */  and     r3, r3, r0
/* 0AC4D0 800B1A70 5460077B */  rlwinm. r0, r3, 0, 0x1d, 0x1d
/* 0AC4D4 800B1A74 41820008 */  beq     lbl_800B1A7C
/* 0AC4D8 800B1A78 63BD0004 */  ori     r29, r29, 4
lbl_800B1A7C:
/* 0AC4DC 800B1A7C 7C602378 */  or      r0, r3, r4
/* 0AC4E0 800B1A80 90050000 */  stw     r0, DI_DISR(r5)
/* 0AC4E4 800B1A84 38000000 */  li      r0, 0
/* 0AC4E8 800B1A88 900D8CE4 */  stw     r0, WaitingCoverClose@sda21(r13)
/* 0AC4EC 800B1A8C 48000010 */  b       lbl_800B1A9C
lbl_800B1A90:
/* 0AC4F0 800B1A90 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AC4F4 800B1A94 38000000 */  li      r0, 0
/* 0AC4F8 800B1A98 90036004 */  stw     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
lbl_800B1A9C:
/* 0AC4FC 800B1A9C 57A00739 */  rlwinm. r0, r29, 0, 0x1c, 0x1c
/* 0AC500 800B1AA0 41820014 */  beq     lbl_800B1AB4
/* 0AC504 800B1AA4 800D8CE8 */  lwz     r0, Breaking@sda21(r13)
/* 0AC508 800B1AA8 2C000000 */  cmpwi   r0, 0
/* 0AC50C 800B1AAC 40820008 */  bne     lbl_800B1AB4
/* 0AC510 800B1AB0 57BD0776 */  rlwinm  r29, r29, 0, 0x1d, 0x1b
lbl_800B1AB4:
/* 0AC514 800B1AB4 57A007FF */  clrlwi. r0, r29, 0x1f
/* 0AC518 800B1AB8 41820080 */  beq     lbl_800B1B38
/* 0AC51C 800B1ABC 800D8D0C */  lwz     r0, NextCommandNumber@sda21(r13)
/* 0AC520 800B1AC0 1C000014 */  mulli   r0, r0, 0x14
/* 0AC524 800B1AC4 7C7E002E */  lwzx    r3, r30, r0
/* 0AC528 800B1AC8 2C030001 */  cmpwi   r3, 1
/* 0AC52C 800B1ACC 40820030 */  bne     lbl_800B1AFC
/* 0AC530 800B1AD0 806D8D0C */  lwz     r3, NextCommandNumber@sda21(r13)
/* 0AC534 800B1AD4 7CDE0214 */  add     r6, r30, r0
/* 0AC538 800B1AD8 38030001 */  addi    r0, r3, 1
/* 0AC53C 800B1ADC 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
/* 0AC540 800B1AE0 80660004 */  lwz     r3, 4(r6)
/* 0AC544 800B1AE4 80860008 */  lwz     r4, 8(r6)
/* 0AC548 800B1AE8 80A6000C */  lwz     r5, 0xc(r6)
/* 0AC54C 800B1AEC 80C60010 */  lwz     r6, 0x10(r6)
/* 0AC550 800B1AF0 480001B1 */  bl      Read
/* 0AC554 800B1AF4 38000001 */  li      r0, 1
/* 0AC558 800B1AF8 48000034 */  b       lbl_800B1B2C
lbl_800B1AFC:
/* 0AC55C 800B1AFC 2C030002 */  cmpwi   r3, 2
/* 0AC560 800B1B00 40820028 */  bne     lbl_800B1B28
/* 0AC564 800B1B04 806D8D0C */  lwz     r3, NextCommandNumber@sda21(r13)
/* 0AC568 800B1B08 7C9E0214 */  add     r4, r30, r0
/* 0AC56C 800B1B0C 38030001 */  addi    r0, r3, 1
/* 0AC570 800B1B10 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
/* 0AC574 800B1B14 8064000C */  lwz     r3, 0xc(r4)
/* 0AC578 800B1B18 80840010 */  lwz     r4, 0x10(r4)
/* 0AC57C 800B1B1C 480005AD */  bl      DVDLowSeek
/* 0AC580 800B1B20 38000001 */  li      r0, 1
/* 0AC584 800B1B24 48000008 */  b       lbl_800B1B2C
lbl_800B1B28:
/* 0AC588 800B1B28 38000000 */  li      r0, 0
lbl_800B1B2C:
/* 0AC58C 800B1B2C 2C000000 */  cmpwi   r0, 0
/* 0AC590 800B1B30 41820018 */  beq     lbl_800B1B48
/* 0AC594 800B1B34 48000064 */  b       lbl_800B1B98
lbl_800B1B38:
/* 0AC598 800B1B38 3800FFFF */  li      r0, -1
/* 0AC59C 800B1B3C 901E0000 */  stw     r0, 0(r30)
/* 0AC5A0 800B1B40 38000000 */  li      r0, 0
/* 0AC5A4 800B1B44 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
lbl_800B1B48:
/* 0AC5A8 800B1B48 38610010 */  addi    r3, r1, 0x10
/* 0AC5AC 800B1B4C 4BFEC659 */  bl      OSClearContext
/* 0AC5B0 800B1B50 38610010 */  addi    r3, r1, 0x10
/* 0AC5B4 800B1B54 4BFEC489 */  bl      OSSetCurrentContext
/* 0AC5B8 800B1B58 281D0000 */  cmplwi  r29, 0
/* 0AC5BC 800B1B5C 4182002C */  beq     lbl_800B1B88
/* 0AC5C0 800B1B60 818D8CD0 */  lwz     r12, Callback@sda21(r13)
/* 0AC5C4 800B1B64 38000000 */  li      r0, 0
/* 0AC5C8 800B1B68 280C0000 */  cmplwi  r12, 0
/* 0AC5CC 800B1B6C 900D8CD0 */  stw     r0, Callback@sda21(r13)
/* 0AC5D0 800B1B70 41820010 */  beq     lbl_800B1B80
/* 0AC5D4 800B1B74 7D8803A6 */  mtlr    r12
/* 0AC5D8 800B1B78 387D0000 */  addi    r3, r29, 0
/* 0AC5DC 800B1B7C 4E800021 */  blrl    
lbl_800B1B80:
/* 0AC5E0 800B1B80 38000000 */  li      r0, 0
/* 0AC5E4 800B1B84 900D8CE8 */  stw     r0, Breaking@sda21(r13)
lbl_800B1B88:
/* 0AC5E8 800B1B88 38610010 */  addi    r3, r1, 0x10
/* 0AC5EC 800B1B8C 4BFEC619 */  bl      OSClearContext
/* 0AC5F0 800B1B90 7F83E378 */  mr      r3, r28
/* 0AC5F4 800B1B94 4BFEC449 */  bl      OSSetCurrentContext
lbl_800B1B98:
/* 0AC5F8 800B1B98 BB6102DC */  lmw     r27, 0x2dc(r1)
/* 0AC5FC 800B1B9C 800102F4 */  lwz     r0, 0x2f4(r1)
/* 0AC600 800B1BA0 382102F0 */  addi    r1, r1, 0x2f0
/* 0AC604 800B1BA4 7C0803A6 */  mtlr    r0
/* 0AC608 800B1BA8 4E800020 */  blr     

AlarmHandler:
/* 0AC60C 800B1BAC 7C0802A6 */  mflr    r0
/* 0AC610 800B1BB0 3C608013 */  lis     r3, CommandList@ha
/* 0AC614 800B1BB4 90010004 */  stw     r0, 4(r1)
/* 0AC618 800B1BB8 388324B8 */  addi    r4, r3, CommandList@l
/* 0AC61C 800B1BBC 9421FFF8 */  stwu    r1, -8(r1)
/* 0AC620 800B1BC0 800D8D0C */  lwz     r0, NextCommandNumber@sda21(r13)
/* 0AC624 800B1BC4 1C000014 */  mulli   r0, r0, 0x14
/* 0AC628 800B1BC8 7C64002E */  lwzx    r3, r4, r0
/* 0AC62C 800B1BCC 2C030001 */  cmpwi   r3, 1
/* 0AC630 800B1BD0 4082002C */  bne     lbl_800B1BFC
/* 0AC634 800B1BD4 806D8D0C */  lwz     r3, NextCommandNumber@sda21(r13)
/* 0AC638 800B1BD8 7CC40214 */  add     r6, r4, r0
/* 0AC63C 800B1BDC 38030001 */  addi    r0, r3, 1
/* 0AC640 800B1BE0 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
/* 0AC644 800B1BE4 80660004 */  lwz     r3, 4(r6)
/* 0AC648 800B1BE8 80860008 */  lwz     r4, 8(r6)
/* 0AC64C 800B1BEC 80A6000C */  lwz     r5, 0xc(r6)
/* 0AC650 800B1BF0 80C60010 */  lwz     r6, 0x10(r6)
/* 0AC654 800B1BF4 480000AD */  bl      Read
/* 0AC658 800B1BF8 48000028 */  b       lbl_800B1C20
lbl_800B1BFC:
/* 0AC65C 800B1BFC 2C030002 */  cmpwi   r3, 2
/* 0AC660 800B1C00 40820020 */  bne     lbl_800B1C20
/* 0AC664 800B1C04 806D8D0C */  lwz     r3, NextCommandNumber@sda21(r13)
/* 0AC668 800B1C08 7C840214 */  add     r4, r4, r0
/* 0AC66C 800B1C0C 38030001 */  addi    r0, r3, 1
/* 0AC670 800B1C10 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
/* 0AC674 800B1C14 8064000C */  lwz     r3, 0xc(r4)
/* 0AC678 800B1C18 80840010 */  lwz     r4, 0x10(r4)
/* 0AC67C 800B1C1C 480004AD */  bl      DVDLowSeek
lbl_800B1C20:
/* 0AC680 800B1C20 8001000C */  lwz     r0, 0xc(r1)
/* 0AC684 800B1C24 38210008 */  addi    r1, r1, 8
/* 0AC688 800B1C28 7C0803A6 */  mtlr    r0
/* 0AC68C 800B1C2C 4E800020 */  blr     

AlarmHandlerForTimeout:
/* 0AC690 800B1C30 7C0802A6 */  mflr    r0
/* 0AC694 800B1C34 38600400 */  li      r3, 0x400
/* 0AC698 800B1C38 90010004 */  stw     r0, 4(r1)
/* 0AC69C 800B1C3C 9421FD20 */  stwu    r1, -0x2e0(r1)
/* 0AC6A0 800B1C40 93E102DC */  stw     r31, 0x2dc(r1)
/* 0AC6A4 800B1C44 3BE40000 */  addi    r31, r4, 0
/* 0AC6A8 800B1C48 4BFED47D */  bl      __OSMaskInterrupts
/* 0AC6AC 800B1C4C 38610010 */  addi    r3, r1, 0x10
/* 0AC6B0 800B1C50 4BFEC555 */  bl      OSClearContext
/* 0AC6B4 800B1C54 38610010 */  addi    r3, r1, 0x10
/* 0AC6B8 800B1C58 4BFEC385 */  bl      OSSetCurrentContext
/* 0AC6BC 800B1C5C 818D8CD0 */  lwz     r12, Callback@sda21(r13)
/* 0AC6C0 800B1C60 38000000 */  li      r0, 0
/* 0AC6C4 800B1C64 280C0000 */  cmplwi  r12, 0
/* 0AC6C8 800B1C68 900D8CD0 */  stw     r0, Callback@sda21(r13)
/* 0AC6CC 800B1C6C 41820010 */  beq     lbl_800B1C7C
/* 0AC6D0 800B1C70 7D8803A6 */  mtlr    r12
/* 0AC6D4 800B1C74 38600010 */  li      r3, 0x10
/* 0AC6D8 800B1C78 4E800021 */  blrl    
lbl_800B1C7C:
/* 0AC6DC 800B1C7C 38610010 */  addi    r3, r1, 0x10
/* 0AC6E0 800B1C80 4BFEC525 */  bl      OSClearContext
/* 0AC6E4 800B1C84 7FE3FB78 */  mr      r3, r31
/* 0AC6E8 800B1C88 4BFEC355 */  bl      OSSetCurrentContext
/* 0AC6EC 800B1C8C 800102E4 */  lwz     r0, 0x2e4(r1)
/* 0AC6F0 800B1C90 83E102DC */  lwz     r31, 0x2dc(r1)
/* 0AC6F4 800B1C94 382102E0 */  addi    r1, r1, 0x2e0
/* 0AC6F8 800B1C98 7C0803A6 */  mtlr    r0
/* 0AC6FC 800B1C9C 4E800020 */  blr     

Read:
/* 0AC700 800B1CA0 7C0802A6 */  mflr    r0
/* 0AC704 800B1CA4 90010004 */  stw     r0, 4(r1)
/* 0AC708 800B1CA8 38000000 */  li      r0, 0
/* 0AC70C 800B1CAC 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0AC710 800B1CB0 93E10024 */  stw     r31, 0x24(r1)
/* 0AC714 800B1CB4 93C10020 */  stw     r30, 0x20(r1)
/* 0AC718 800B1CB8 3BC50000 */  addi    r30, r5, 0
/* 0AC71C 800B1CBC 93A1001C */  stw     r29, 0x1c(r1)
/* 0AC720 800B1CC0 3BA40000 */  addi    r29, r4, 0
/* 0AC724 800B1CC4 93810018 */  stw     r28, 0x18(r1)
/* 0AC728 800B1CC8 3B830000 */  addi    r28, r3, 0
/* 0AC72C 800B1CCC 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0AC730 800B1CD0 38000001 */  li      r0, 1
/* 0AC734 800B1CD4 90CD8CD0 */  stw     r6, Callback@sda21(r13)
/* 0AC738 800B1CD8 3CC08013 */  lis     r6, CommandList@ha
/* 0AC73C 800B1CDC 3BE624B8 */  addi    r31, r6, CommandList@l
/* 0AC740 800B1CE0 900D8D08 */  stw     r0, LastCommandWasRead@sda21(r13)
/* 0AC744 800B1CE4 4BFF05E5 */  bl      __OSGetSystemTime
/* 0AC748 800B1CE8 908D8D04 */  stw     r4, (LastReadIssued + 4)@sda21(r13)
/* 0AC74C 800B1CEC 3C80CC00 */  lis     r4, DI_REGS_BASE@ha
/* 0AC750 800B1CF0 3C0000A0 */  lis     r0, 0xa0
/* 0AC754 800B1CF4 906D8D00 */  stw     r3, LastReadIssued@sda21(r13)
/* 0AC758 800B1CF8 38846000 */  addi    r4, r4, DI_REGS_BASE@l
/* 0AC75C 800B1CFC 3C60A800 */  lis     r3, 0xa800
/* 0AC760 800B1D00 90640008 */  stw     r3, DI_DICMDBUF0(r4)
/* 0AC764 800B1D04 57C3F0BE */  srwi    r3, r30, 2
/* 0AC768 800B1D08 7C1D0040 */  cmplw   r29, r0
/* 0AC76C 800B1D0C 9064000C */  stw     r3, DI_DICMDBUF1(r4)
/* 0AC770 800B1D10 38000003 */  li      r0, 3
/* 0AC774 800B1D14 93A40010 */  stw     r29, DI_DICMDBUF2(r4)
/* 0AC778 800B1D18 93840014 */  stw     r28, DI_DIMAR(r4)
/* 0AC77C 800B1D1C 93A40018 */  stw     r29, DI_DILENGTH(r4)
/* 0AC780 800B1D20 93AD8CCC */  stw     r29, LastLength@sda21(r13)
/* 0AC784 800B1D24 9004001C */  stw     r0, DI_DICR(r4)
/* 0AC788 800B1D28 40810038 */  ble     lbl_800B1D60
/* 0AC78C 800B1D2C 3C608000 */  lis     r3, 0x8000
/* 0AC790 800B1D30 800300F8 */  lwz     r0, 0xf8(r3)
/* 0AC794 800B1D34 387F0068 */  addi    r3, r31, 0x68
/* 0AC798 800B1D38 5400F0BE */  srwi    r0, r0, 2
/* 0AC79C 800B1D3C 1FC00014 */  mulli   r30, r0, 0x14
/* 0AC7A0 800B1D40 4BFEA9D5 */  bl      OSCreateAlarm
/* 0AC7A4 800B1D44 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0AC7A8 800B1D48 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0AC7AC 800B1D4C 38DE0000 */  addi    r6, r30, 0
/* 0AC7B0 800B1D50 387F0068 */  addi    r3, r31, 0x68
/* 0AC7B4 800B1D54 38A00000 */  li      r5, 0
/* 0AC7B8 800B1D58 4BFEAC1D */  bl      OSSetAlarm
/* 0AC7BC 800B1D5C 48000034 */  b       lbl_800B1D90
lbl_800B1D60:
/* 0AC7C0 800B1D60 3C608000 */  lis     r3, 0x8000
/* 0AC7C4 800B1D64 800300F8 */  lwz     r0, 0xf8(r3)
/* 0AC7C8 800B1D68 387F0068 */  addi    r3, r31, 0x68
/* 0AC7CC 800B1D6C 5400F0BE */  srwi    r0, r0, 2
/* 0AC7D0 800B1D70 1FC0000A */  mulli   r30, r0, 0xa
/* 0AC7D4 800B1D74 4BFEA9A1 */  bl      OSCreateAlarm
/* 0AC7D8 800B1D78 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0AC7DC 800B1D7C 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0AC7E0 800B1D80 38DE0000 */  addi    r6, r30, 0
/* 0AC7E4 800B1D84 387F0068 */  addi    r3, r31, 0x68
/* 0AC7E8 800B1D88 38A00000 */  li      r5, 0
/* 0AC7EC 800B1D8C 4BFEABE9 */  bl      OSSetAlarm
lbl_800B1D90:
/* 0AC7F0 800B1D90 8001002C */  lwz     r0, 0x2c(r1)
/* 0AC7F4 800B1D94 83E10024 */  lwz     r31, 0x24(r1)
/* 0AC7F8 800B1D98 83C10020 */  lwz     r30, 0x20(r1)
/* 0AC7FC 800B1D9C 83A1001C */  lwz     r29, 0x1c(r1)
/* 0AC800 800B1DA0 83810018 */  lwz     r28, 0x18(r1)
/* 0AC804 800B1DA4 38210028 */  addi    r1, r1, 0x28
/* 0AC808 800B1DA8 7C0803A6 */  mtlr    r0
/* 0AC80C 800B1DAC 4E800020 */  blr     

SeekTwiceBeforeRead:
/* 0AC810 800B1DB0 7C0802A6 */  mflr    r0
/* 0AC814 800B1DB4 3CE08013 */  lis     r7, CommandList@ha
/* 0AC818 800B1DB8 90010004 */  stw     r0, 4(r1)
/* 0AC81C 800B1DBC 54A80021 */  rlwinm. r8, r5, 0, 0, 0x10
/* 0AC820 800B1DC0 392724B8 */  addi    r9, r7, CommandList@l
/* 0AC824 800B1DC4 9421FFF8 */  stwu    r1, -8(r1)
/* 0AC828 800B1DC8 4082000C */  bne     lbl_800B1DD4
/* 0AC82C 800B1DCC 39400000 */  li      r10, 0
/* 0AC830 800B1DD0 4800000C */  b       lbl_800B1DDC
lbl_800B1DD4:
/* 0AC834 800B1DD4 800D8CF0 */  lwz     r0, WorkAroundSeekLocation@sda21(r13)
/* 0AC838 800B1DD8 7D480214 */  add     r10, r8, r0
lbl_800B1DDC:
/* 0AC83C 800B1DDC 38000002 */  li      r0, 2
/* 0AC840 800B1DE0 90090000 */  stw     r0, 0(r9)
/* 0AC844 800B1DE4 39000001 */  li      r8, 1
/* 0AC848 800B1DE8 38E0FFFF */  li      r7, -1
/* 0AC84C 800B1DEC 9149000C */  stw     r10, 0xc(r9)
/* 0AC850 800B1DF0 38000000 */  li      r0, 0
/* 0AC854 800B1DF4 90C90010 */  stw     r6, 0x10(r9)
/* 0AC858 800B1DF8 91090014 */  stw     r8, 0x14(r9)
/* 0AC85C 800B1DFC 90690018 */  stw     r3, 0x18(r9)
/* 0AC860 800B1E00 7D435378 */  mr      r3, r10
/* 0AC864 800B1E04 9089001C */  stw     r4, 0x1c(r9)
/* 0AC868 800B1E08 7CC43378 */  mr      r4, r6
/* 0AC86C 800B1E0C 90A90020 */  stw     r5, 0x20(r9)
/* 0AC870 800B1E10 90C90024 */  stw     r6, 0x24(r9)
/* 0AC874 800B1E14 90E90028 */  stw     r7, 0x28(r9)
/* 0AC878 800B1E18 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
/* 0AC87C 800B1E1C 480002AD */  bl      DVDLowSeek
/* 0AC880 800B1E20 8001000C */  lwz     r0, 0xc(r1)
/* 0AC884 800B1E24 38210008 */  addi    r1, r1, 8
/* 0AC888 800B1E28 7C0803A6 */  mtlr    r0
/* 0AC88C 800B1E2C 4E800020 */  blr     

glabel DVDLowRead
/* 0AC890 800B1E30 7C0802A6 */  mflr    r0
/* 0AC894 800B1E34 3CE0CC00 */  lis     r7, DI_REGS_BASE@ha
/* 0AC898 800B1E38 90010004 */  stw     r0, 4(r1)
/* 0AC89C 800B1E3C 9421FFC0 */  stwu    r1, -0x40(r1)
/* 0AC8A0 800B1E40 BEC10018 */  stmw    r22, 0x18(r1)
/* 0AC8A4 800B1E44 3B240000 */  addi    r25, r4, 0
/* 0AC8A8 800B1E48 38876000 */  addi    r4, r7, DI_REGS_BASE@l
/* 0AC8AC 800B1E4C 3CE08013 */  lis     r7, CommandList@ha
/* 0AC8B0 800B1E50 3BE724B8 */  addi    r31, r7, CommandList@l
/* 0AC8B4 800B1E54 3B030000 */  addi    r24, r3, 0
/* 0AC8B8 800B1E58 3B450000 */  addi    r26, r5, 0
/* 0AC8BC 800B1E5C 3BDF00CC */  addi    r30, r31, 0xcc
/* 0AC8C0 800B1E60 7CDB3378 */  mr      r27, r6
/* 0AC8C4 800B1E64 93240018 */  stw     r25, DI_DILENGTH(r4)
/* 0AC8C8 800B1E68 931F00C4 */  stw     r24, 0xc4(r31)
/* 0AC8CC 800B1E6C 933F00C8 */  stw     r25, 0xc8(r31)
/* 0AC8D0 800B1E70 935F00CC */  stw     r26, 0xcc(r31)
/* 0AC8D4 800B1E74 800D8CEC */  lwz     r0, WorkAroundType@sda21(r13)
/* 0AC8D8 800B1E78 28000000 */  cmplwi  r0, 0
/* 0AC8DC 800B1E7C 4082002C */  bne     lbl_800B1EA8
/* 0AC8E0 800B1E80 3800FFFF */  li      r0, -1
/* 0AC8E4 800B1E84 901F0000 */  stw     r0, 0(r31)
/* 0AC8E8 800B1E88 38000000 */  li      r0, 0
/* 0AC8EC 800B1E8C 38780000 */  addi    r3, r24, 0
/* 0AC8F0 800B1E90 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
/* 0AC8F4 800B1E94 38990000 */  addi    r4, r25, 0
/* 0AC8F8 800B1E98 38BA0000 */  addi    r5, r26, 0
/* 0AC8FC 800B1E9C 38DB0000 */  addi    r6, r27, 0
/* 0AC900 800B1EA0 4BFFFE01 */  bl      Read
/* 0AC904 800B1EA4 4800020C */  b       lbl_800B20B0
lbl_800B1EA8:
/* 0AC908 800B1EA8 800D8CEC */  lwz     r0, WorkAroundType@sda21(r13)
/* 0AC90C 800B1EAC 28000001 */  cmplwi  r0, 1
/* 0AC910 800B1EB0 40820200 */  bne     lbl_800B20B0
/* 0AC914 800B1EB4 800D8808 */  lwz     r0, FirstRead@sda21(r13)
/* 0AC918 800B1EB8 2C000000 */  cmpwi   r0, 0
/* 0AC91C 800B1EBC 4182001C */  beq     lbl_800B1ED8
/* 0AC920 800B1EC0 38780000 */  addi    r3, r24, 0
/* 0AC924 800B1EC4 38990000 */  addi    r4, r25, 0
/* 0AC928 800B1EC8 38BA0000 */  addi    r5, r26, 0
/* 0AC92C 800B1ECC 38DB0000 */  addi    r6, r27, 0
/* 0AC930 800B1ED0 4BFFFEE1 */  bl      SeekTwiceBeforeRead
/* 0AC934 800B1ED4 480001DC */  b       lbl_800B20B0
lbl_800B1ED8:
/* 0AC938 800B1ED8 3BBF00BC */  addi    r29, r31, 0xbc
/* 0AC93C 800B1EDC 801E0000 */  lwz     r0, 0(r30)
/* 0AC940 800B1EE0 3B9F00C0 */  addi    r28, r31, 0xc0
/* 0AC944 800B1EE4 807F00BC */  lwz     r3, 0xbc(r31)
/* 0AC948 800B1EE8 809F00C0 */  lwz     r4, 0xc0(r31)
/* 0AC94C 800B1EEC 54178BFE */  srwi    r23, r0, 0xf
/* 0AC950 800B1EF0 3803FFFF */  addi    r0, r3, -1
/* 0AC954 800B1EF4 7C040214 */  add     r0, r4, r0
/* 0AC958 800B1EF8 54168BFE */  srwi    r22, r0, 0xf
/* 0AC95C 800B1EFC 48003555 */  bl      DVDGetCurrentDiskID
/* 0AC960 800B1F00 88030008 */  lbz     r0, 8(r3)
/* 0AC964 800B1F04 28000000 */  cmplwi  r0, 0
/* 0AC968 800B1F08 4182000C */  beq     lbl_800B1F14
/* 0AC96C 800B1F0C 38000001 */  li      r0, 1
/* 0AC970 800B1F10 48000008 */  b       lbl_800B1F18
lbl_800B1F14:
/* 0AC974 800B1F14 38000000 */  li      r0, 0
lbl_800B1F18:
/* 0AC978 800B1F18 2C000000 */  cmpwi   r0, 0
/* 0AC97C 800B1F1C 4182000C */  beq     lbl_800B1F28
/* 0AC980 800B1F20 38600005 */  li      r3, 5
/* 0AC984 800B1F24 48000008 */  b       lbl_800B1F2C
lbl_800B1F28:
/* 0AC988 800B1F28 3860000F */  li      r3, 0xf
lbl_800B1F2C:
/* 0AC98C 800B1F2C 3816FFFE */  addi    r0, r22, -2
/* 0AC990 800B1F30 7C170040 */  cmplw   r23, r0
/* 0AC994 800B1F34 41810014 */  bgt     lbl_800B1F48
/* 0AC998 800B1F38 38030003 */  addi    r0, r3, 3
/* 0AC99C 800B1F3C 7C160214 */  add     r0, r22, r0
/* 0AC9A0 800B1F40 7C170040 */  cmplw   r23, r0
/* 0AC9A4 800B1F44 4080000C */  bge     lbl_800B1F50
lbl_800B1F48:
/* 0AC9A8 800B1F48 38000001 */  li      r0, 1
/* 0AC9AC 800B1F4C 48000008 */  b       lbl_800B1F54
lbl_800B1F50:
/* 0AC9B0 800B1F50 38000000 */  li      r0, 0
lbl_800B1F54:
/* 0AC9B4 800B1F54 2C000000 */  cmpwi   r0, 0
/* 0AC9B8 800B1F58 4082002C */  bne     lbl_800B1F84
/* 0AC9BC 800B1F5C 3800FFFF */  li      r0, -1
/* 0AC9C0 800B1F60 901F0000 */  stw     r0, 0(r31)
/* 0AC9C4 800B1F64 38000000 */  li      r0, 0
/* 0AC9C8 800B1F68 38780000 */  addi    r3, r24, 0
/* 0AC9CC 800B1F6C 900D8D0C */  stw     r0, NextCommandNumber@sda21(r13)
/* 0AC9D0 800B1F70 38990000 */  addi    r4, r25, 0
/* 0AC9D4 800B1F74 38BA0000 */  addi    r5, r26, 0
/* 0AC9D8 800B1F78 38DB0000 */  addi    r6, r27, 0
/* 0AC9DC 800B1F7C 4BFFFD25 */  bl      Read
/* 0AC9E0 800B1F80 48000130 */  b       lbl_800B20B0
lbl_800B1F84:
/* 0AC9E4 800B1F84 807D0000 */  lwz     r3, 0(r29)
/* 0AC9E8 800B1F88 809C0000 */  lwz     r4, 0(r28)
/* 0AC9EC 800B1F8C 3863FFFF */  addi    r3, r3, -1
/* 0AC9F0 800B1F90 801E0000 */  lwz     r0, 0(r30)
/* 0AC9F4 800B1F94 7C641A14 */  add     r3, r4, r3
/* 0AC9F8 800B1F98 54638BFE */  srwi    r3, r3, 0xf
/* 0AC9FC 800B1F9C 54048BFE */  srwi    r4, r0, 0xf
/* 0ACA00 800B1FA0 7C032040 */  cmplw   r3, r4
/* 0ACA04 800B1FA4 41820010 */  beq     lbl_800B1FB4
/* 0ACA08 800B1FA8 38030001 */  addi    r0, r3, 1
/* 0ACA0C 800B1FAC 7C002040 */  cmplw   r0, r4
/* 0ACA10 800B1FB0 408200EC */  bne     lbl_800B209C
lbl_800B1FB4:
/* 0ACA14 800B1FB4 4BFF0315 */  bl      __OSGetSystemTime
/* 0ACA18 800B1FB8 3CA08000 */  lis     r5, 0x8000
/* 0ACA1C 800B1FBC 810D8CF8 */  lwz     r8, LastReadFinished@sda21(r13)
/* 0ACA20 800B1FC0 800500F8 */  lwz     r0, 0xf8(r5)
/* 0ACA24 800B1FC4 3CA01062 */  lis     r5, 0x1062
/* 0ACA28 800B1FC8 812D8CFC */  lwz     r9, (LastReadFinished + 4)@sda21(r13)
/* 0ACA2C 800B1FCC 38C00000 */  li      r6, 0
/* 0ACA30 800B1FD0 5407F0BE */  srwi    r7, r0, 2
/* 0ACA34 800B1FD4 38054DD3 */  addi    r0, r5, 0x4dd3
/* 0ACA38 800B1FD8 7C003816 */  mulhwu  r0, r0, r7
/* 0ACA3C 800B1FDC 5400D1BE */  srwi    r0, r0, 6
/* 0ACA40 800B1FE0 7D292010 */  subfc   r9, r9, r4
/* 0ACA44 800B1FE4 7D081910 */  subfe   r8, r8, r3
/* 0ACA48 800B1FE8 1CA00005 */  mulli   r5, r0, 5
/* 0ACA4C 800B1FEC 6CC48000 */  xoris   r4, r6, 0x8000
/* 0ACA50 800B1FF0 6D038000 */  xoris   r3, r8, 0x8000
/* 0ACA54 800B1FF4 7C092810 */  subfc   r0, r9, r5
/* 0ACA58 800B1FF8 7C632110 */  subfe   r3, r3, r4
/* 0ACA5C 800B1FFC 7C642110 */  subfe   r3, r4, r4
/* 0ACA60 800B2000 7C6300D1 */  neg.    r3, r3
/* 0ACA64 800B2004 41820028 */  beq     lbl_800B202C
/* 0ACA68 800B2008 3800FFFF */  li      r0, -1
/* 0ACA6C 800B200C 901F0000 */  stw     r0, 0(r31)
/* 0ACA70 800B2010 38780000 */  addi    r3, r24, 0
/* 0ACA74 800B2014 38990000 */  addi    r4, r25, 0
/* 0ACA78 800B2018 90CD8D0C */  stw     r6, NextCommandNumber@sda21(r13)
/* 0ACA7C 800B201C 38BA0000 */  addi    r5, r26, 0
/* 0ACA80 800B2020 38DB0000 */  addi    r6, r27, 0
/* 0ACA84 800B2024 4BFFFC7D */  bl      Read
/* 0ACA88 800B2028 48000088 */  b       lbl_800B20B0
lbl_800B202C:
/* 0ACA8C 800B202C 38000001 */  li      r0, 1
/* 0ACA90 800B2030 901F0000 */  stw     r0, 0(r31)
/* 0ACA94 800B2034 3C60431C */  lis     r3, 0x431c
/* 0ACA98 800B2038 3803DE83 */  addi    r0, r3, -8573
/* 0ACA9C 800B203C 931F0004 */  stw     r24, 4(r31)
/* 0ACAA0 800B2040 7C003816 */  mulhwu  r0, r0, r7
/* 0ACAA4 800B2044 933F0008 */  stw     r25, 8(r31)
/* 0ACAA8 800B2048 935F000C */  stw     r26, 0xc(r31)
/* 0ACAAC 800B204C 54008BFE */  srwi    r0, r0, 0xf
/* 0ACAB0 800B2050 1C6001F4 */  mulli   r3, r0, 0x1f4
/* 0ACAB4 800B2054 937F0010 */  stw     r27, 0x10(r31)
/* 0ACAB8 800B2058 3800FFFF */  li      r0, -1
/* 0ACABC 800B205C 901F0014 */  stw     r0, 0x14(r31)
/* 0ACAC0 800B2060 7CA92810 */  subfc   r5, r9, r5
/* 0ACAC4 800B2064 7C883110 */  subfe   r4, r8, r6
/* 0ACAC8 800B2068 5460E8FE */  srwi    r0, r3, 3
/* 0ACACC 800B206C 90CD8D0C */  stw     r6, NextCommandNumber@sda21(r13)
/* 0ACAD0 800B2070 7EE50014 */  addc    r23, r5, r0
/* 0ACAD4 800B2074 7EC43114 */  adde    r22, r4, r6
/* 0ACAD8 800B2078 387F0040 */  addi    r3, r31, 0x40
/* 0ACADC 800B207C 4BFEA699 */  bl      OSCreateAlarm
/* 0ACAE0 800B2080 3C60800B */  lis     r3, AlarmHandler@ha
/* 0ACAE4 800B2084 38E31BAC */  addi    r7, r3, AlarmHandler@l
/* 0ACAE8 800B2088 38D70000 */  addi    r6, r23, 0
/* 0ACAEC 800B208C 38B60000 */  addi    r5, r22, 0
/* 0ACAF0 800B2090 387F0040 */  addi    r3, r31, 0x40
/* 0ACAF4 800B2094 4BFEA8E1 */  bl      OSSetAlarm
/* 0ACAF8 800B2098 48000018 */  b       lbl_800B20B0
lbl_800B209C:
/* 0ACAFC 800B209C 38780000 */  addi    r3, r24, 0
/* 0ACB00 800B20A0 38990000 */  addi    r4, r25, 0
/* 0ACB04 800B20A4 38BA0000 */  addi    r5, r26, 0
/* 0ACB08 800B20A8 38DB0000 */  addi    r6, r27, 0
/* 0ACB0C 800B20AC 4BFFFD05 */  bl      SeekTwiceBeforeRead
lbl_800B20B0:
/* 0ACB10 800B20B0 BAC10018 */  lmw     r22, 0x18(r1)
/* 0ACB14 800B20B4 38600001 */  li      r3, 1
/* 0ACB18 800B20B8 80010044 */  lwz     r0, 0x44(r1)
/* 0ACB1C 800B20BC 38210040 */  addi    r1, r1, 0x40
/* 0ACB20 800B20C0 7C0803A6 */  mtlr    r0
/* 0ACB24 800B20C4 4E800020 */  blr     

glabel DVDLowSeek
/* 0ACB28 800B20C8 7C0802A6 */  mflr    r0
/* 0ACB2C 800B20CC 90010004 */  stw     r0, 4(r1)
/* 0ACB30 800B20D0 38000000 */  li      r0, 0
/* 0ACB34 800B20D4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0ACB38 800B20D8 93E10014 */  stw     r31, 0x14(r1)
/* 0ACB3C 800B20DC 93C10010 */  stw     r30, 0x10(r1)
/* 0ACB40 800B20E0 908D8CD0 */  stw     r4, Callback@sda21(r13)
/* 0ACB44 800B20E4 3C80CC00 */  lis     r4, DI_REGS_BASE@ha
/* 0ACB48 800B20E8 38846000 */  addi    r4, r4, DI_REGS_BASE@l
/* 0ACB4C 800B20EC 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0ACB50 800B20F0 3C00AB00 */  lis     r0, 0xab00
/* 0ACB54 800B20F4 90040008 */  stw     r0, DI_DICMDBUF0(r4)
/* 0ACB58 800B20F8 5460F0BE */  srwi    r0, r3, 2
/* 0ACB5C 800B20FC 3C608013 */  lis     r3, AlarmForTimeout@ha
/* 0ACB60 800B2100 9004000C */  stw     r0, DI_DICMDBUF1(r4)
/* 0ACB64 800B2104 38000001 */  li      r0, 1
/* 0ACB68 800B2108 3BE32520 */  addi    r31, r3, AlarmForTimeout@l
/* 0ACB6C 800B210C 9004001C */  stw     r0, DI_DICR(r4)
/* 0ACB70 800B2110 3C808000 */  lis     r4, 0x8000
/* 0ACB74 800B2114 387F0000 */  addi    r3, r31, 0
/* 0ACB78 800B2118 800400F8 */  lwz     r0, 0xf8(r4)
/* 0ACB7C 800B211C 5400F0BE */  srwi    r0, r0, 2
/* 0ACB80 800B2120 1FC0000A */  mulli   r30, r0, 0xa
/* 0ACB84 800B2124 4BFEA5F1 */  bl      OSCreateAlarm
/* 0ACB88 800B2128 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0ACB8C 800B212C 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0ACB90 800B2130 387F0000 */  addi    r3, r31, 0
/* 0ACB94 800B2134 38DE0000 */  addi    r6, r30, 0
/* 0ACB98 800B2138 38A00000 */  li      r5, 0
/* 0ACB9C 800B213C 4BFEA839 */  bl      OSSetAlarm
/* 0ACBA0 800B2140 8001001C */  lwz     r0, 0x1c(r1)
/* 0ACBA4 800B2144 38600001 */  li      r3, 1
/* 0ACBA8 800B2148 83E10014 */  lwz     r31, 0x14(r1)
/* 0ACBAC 800B214C 83C10010 */  lwz     r30, 0x10(r1)
/* 0ACBB0 800B2150 38210018 */  addi    r1, r1, 0x18
/* 0ACBB4 800B2154 7C0803A6 */  mtlr    r0
/* 0ACBB8 800B2158 4E800020 */  blr     

glabel DVDLowWaitCoverClose
/* 0ACBBC 800B215C 38000001 */  li      r0, 1
/* 0ACBC0 800B2160 906D8CD0 */  stw     r3, Callback@sda21(r13)
/* 0ACBC4 800B2164 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0ACBC8 800B2168 900D8CE4 */  stw     r0, WaitingCoverClose@sda21(r13)
/* 0ACBCC 800B216C 38000000 */  li      r0, 0
/* 0ACBD0 800B2170 38836000 */  addi    r4, r3, DI_REGS_BASE@l
/* 0ACBD4 800B2174 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0ACBD8 800B2178 38000002 */  li      r0, 2
/* 0ACBDC 800B217C 38600001 */  li      r3, 1
/* 0ACBE0 800B2180 90040004 */  stw     r0, DI_DICVR(r4)
/* 0ACBE4 800B2184 4E800020 */  blr     

glabel DVDLowReadDiskID
/* 0ACBE8 800B2188 7C0802A6 */  mflr    r0
/* 0ACBEC 800B218C 39000000 */  li      r8, 0
/* 0ACBF0 800B2190 90010004 */  stw     r0, 4(r1)
/* 0ACBF4 800B2194 3CA0A800 */  lis     r5, 0xa800
/* 0ACBF8 800B2198 38050040 */  addi    r0, r5, 0x40
/* 0ACBFC 800B219C 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0ACC00 800B21A0 38C00020 */  li      r6, 0x20
/* 0ACC04 800B21A4 3CA08000 */  lis     r5, 0x8000
/* 0ACC08 800B21A8 93E10014 */  stw     r31, 0x14(r1)
/* 0ACC0C 800B21AC 93C10010 */  stw     r30, 0x10(r1)
/* 0ACC10 800B21B0 908D8CD0 */  stw     r4, Callback@sda21(r13)
/* 0ACC14 800B21B4 3C80CC00 */  lis     r4, DI_REGS_BASE@ha
/* 0ACC18 800B21B8 38E46000 */  addi    r7, r4, DI_REGS_BASE@l
/* 0ACC1C 800B21BC 910D8CC8 */  stw     r8, StopAtNextInt@sda21(r13)
/* 0ACC20 800B21C0 90046008 */  stw     r0, (DI_REGS_BASE + DI_DICMDBUF0)@l(r4)
/* 0ACC24 800B21C4 3C808013 */  lis     r4, AlarmForTimeout@ha
/* 0ACC28 800B21C8 38000003 */  li      r0, 3
/* 0ACC2C 800B21CC 9107000C */  stw     r8, DI_DICMDBUF1(r7)
/* 0ACC30 800B21D0 3BE42520 */  addi    r31, r4, AlarmForTimeout@l
/* 0ACC34 800B21D4 90C70010 */  stw     r6, DI_DICMDBUF2(r7)
/* 0ACC38 800B21D8 90670014 */  stw     r3, DI_DIMAR(r7)
/* 0ACC3C 800B21DC 7FE3FB78 */  mr      r3, r31
/* 0ACC40 800B21E0 90C70018 */  stw     r6, DI_DILENGTH(r7)
/* 0ACC44 800B21E4 9007001C */  stw     r0, DI_DICR(r7)
/* 0ACC48 800B21E8 800500F8 */  lwz     r0, 0xf8(r5)
/* 0ACC4C 800B21EC 5400F0BE */  srwi    r0, r0, 2
/* 0ACC50 800B21F0 1FC0000A */  mulli   r30, r0, 0xa
/* 0ACC54 800B21F4 4BFEA521 */  bl      OSCreateAlarm
/* 0ACC58 800B21F8 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0ACC5C 800B21FC 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0ACC60 800B2200 387F0000 */  addi    r3, r31, 0
/* 0ACC64 800B2204 38DE0000 */  addi    r6, r30, 0
/* 0ACC68 800B2208 38A00000 */  li      r5, 0
/* 0ACC6C 800B220C 4BFEA769 */  bl      OSSetAlarm
/* 0ACC70 800B2210 8001001C */  lwz     r0, 0x1c(r1)
/* 0ACC74 800B2214 38600001 */  li      r3, 1
/* 0ACC78 800B2218 83E10014 */  lwz     r31, 0x14(r1)
/* 0ACC7C 800B221C 83C10010 */  lwz     r30, 0x10(r1)
/* 0ACC80 800B2220 38210018 */  addi    r1, r1, 0x18
/* 0ACC84 800B2224 7C0803A6 */  mtlr    r0
/* 0ACC88 800B2228 4E800020 */  blr     

glabel DVDLowStopMotor
/* 0ACC8C 800B222C 7C0802A6 */  mflr    r0
/* 0ACC90 800B2230 90010004 */  stw     r0, 4(r1)
/* 0ACC94 800B2234 38000000 */  li      r0, 0
/* 0ACC98 800B2238 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0ACC9C 800B223C 93E10014 */  stw     r31, 0x14(r1)
/* 0ACCA0 800B2240 93C10010 */  stw     r30, 0x10(r1)
/* 0ACCA4 800B2244 906D8CD0 */  stw     r3, Callback@sda21(r13)
/* 0ACCA8 800B2248 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0ACCAC 800B224C 38836000 */  addi    r4, r3, DI_REGS_BASE@l
/* 0ACCB0 800B2250 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0ACCB4 800B2254 3C00E300 */  lis     r0, 0xe300
/* 0ACCB8 800B2258 90036008 */  stw     r0, (DI_REGS_BASE + DI_DICMDBUF0)@l(r3)
/* 0ACCBC 800B225C 38000001 */  li      r0, 1
/* 0ACCC0 800B2260 3C608013 */  lis     r3, AlarmForTimeout@ha
/* 0ACCC4 800B2264 9004001C */  stw     r0, DI_DICR(r4)
/* 0ACCC8 800B2268 3C808000 */  lis     r4, 0x8000
/* 0ACCCC 800B226C 3BE32520 */  addi    r31, r3, AlarmForTimeout@l
/* 0ACCD0 800B2270 800400F8 */  lwz     r0, 0xf8(r4)
/* 0ACCD4 800B2274 387F0000 */  addi    r3, r31, 0
/* 0ACCD8 800B2278 5400F0BE */  srwi    r0, r0, 2
/* 0ACCDC 800B227C 1FC0000A */  mulli   r30, r0, 0xa
/* 0ACCE0 800B2280 4BFEA495 */  bl      OSCreateAlarm
/* 0ACCE4 800B2284 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0ACCE8 800B2288 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0ACCEC 800B228C 387F0000 */  addi    r3, r31, 0
/* 0ACCF0 800B2290 38DE0000 */  addi    r6, r30, 0
/* 0ACCF4 800B2294 38A00000 */  li      r5, 0
/* 0ACCF8 800B2298 4BFEA6DD */  bl      OSSetAlarm
/* 0ACCFC 800B229C 8001001C */  lwz     r0, 0x1c(r1)
/* 0ACD00 800B22A0 38600001 */  li      r3, 1
/* 0ACD04 800B22A4 83E10014 */  lwz     r31, 0x14(r1)
/* 0ACD08 800B22A8 83C10010 */  lwz     r30, 0x10(r1)
/* 0ACD0C 800B22AC 38210018 */  addi    r1, r1, 0x18
/* 0ACD10 800B22B0 7C0803A6 */  mtlr    r0
/* 0ACD14 800B22B4 4E800020 */  blr     

glabel DVDLowRequestError
/* 0ACD18 800B22B8 7C0802A6 */  mflr    r0
/* 0ACD1C 800B22BC 90010004 */  stw     r0, 4(r1)
/* 0ACD20 800B22C0 38000000 */  li      r0, 0
/* 0ACD24 800B22C4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0ACD28 800B22C8 93E10014 */  stw     r31, 0x14(r1)
/* 0ACD2C 800B22CC 93C10010 */  stw     r30, 0x10(r1)
/* 0ACD30 800B22D0 906D8CD0 */  stw     r3, Callback@sda21(r13)
/* 0ACD34 800B22D4 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0ACD38 800B22D8 38836000 */  addi    r4, r3, DI_REGS_BASE@l
/* 0ACD3C 800B22DC 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0ACD40 800B22E0 3C00E000 */  lis     r0, 0xe000
/* 0ACD44 800B22E4 90036008 */  stw     r0, (DI_REGS_BASE + DI_DICMDBUF0)@l(r3)
/* 0ACD48 800B22E8 38000001 */  li      r0, 1
/* 0ACD4C 800B22EC 3C608013 */  lis     r3, AlarmForTimeout@ha
/* 0ACD50 800B22F0 9004001C */  stw     r0, DI_DICR(r4)
/* 0ACD54 800B22F4 3C808000 */  lis     r4, 0x8000
/* 0ACD58 800B22F8 3BE32520 */  addi    r31, r3, AlarmForTimeout@l
/* 0ACD5C 800B22FC 800400F8 */  lwz     r0, 0xf8(r4)
/* 0ACD60 800B2300 387F0000 */  addi    r3, r31, 0
/* 0ACD64 800B2304 5400F0BE */  srwi    r0, r0, 2
/* 0ACD68 800B2308 1FC0000A */  mulli   r30, r0, 0xa
/* 0ACD6C 800B230C 4BFEA409 */  bl      OSCreateAlarm
/* 0ACD70 800B2310 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0ACD74 800B2314 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0ACD78 800B2318 387F0000 */  addi    r3, r31, 0
/* 0ACD7C 800B231C 38DE0000 */  addi    r6, r30, 0
/* 0ACD80 800B2320 38A00000 */  li      r5, 0
/* 0ACD84 800B2324 4BFEA651 */  bl      OSSetAlarm
/* 0ACD88 800B2328 8001001C */  lwz     r0, 0x1c(r1)
/* 0ACD8C 800B232C 38600001 */  li      r3, 1
/* 0ACD90 800B2330 83E10014 */  lwz     r31, 0x14(r1)
/* 0ACD94 800B2334 83C10010 */  lwz     r30, 0x10(r1)
/* 0ACD98 800B2338 38210018 */  addi    r1, r1, 0x18
/* 0ACD9C 800B233C 7C0803A6 */  mtlr    r0
/* 0ACDA0 800B2340 4E800020 */  blr     

glabel DVDLowInquiry
/* 0ACDA4 800B2344 7C0802A6 */  mflr    r0
/* 0ACDA8 800B2348 38C00020 */  li      r6, 0x20
/* 0ACDAC 800B234C 90010004 */  stw     r0, 4(r1)
/* 0ACDB0 800B2350 38000000 */  li      r0, 0
/* 0ACDB4 800B2354 3CA08000 */  lis     r5, 0x8000
/* 0ACDB8 800B2358 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0ACDBC 800B235C 93E10014 */  stw     r31, 0x14(r1)
/* 0ACDC0 800B2360 93C10010 */  stw     r30, 0x10(r1)
/* 0ACDC4 800B2364 908D8CD0 */  stw     r4, Callback@sda21(r13)
/* 0ACDC8 800B2368 3C80CC00 */  lis     r4, DI_REGS_BASE@ha
/* 0ACDCC 800B236C 38E46000 */  addi    r7, r4, DI_REGS_BASE@l
/* 0ACDD0 800B2370 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0ACDD4 800B2374 3C001200 */  lis     r0, 0x1200
/* 0ACDD8 800B2378 90046008 */  stw     r0, (DI_REGS_BASE + DI_DICMDBUF0)@l(r4)
/* 0ACDDC 800B237C 3C808013 */  lis     r4, AlarmForTimeout@ha
/* 0ACDE0 800B2380 38000003 */  li      r0, 3
/* 0ACDE4 800B2384 90C70010 */  stw     r6, DI_DICMDBUF2(r7)
/* 0ACDE8 800B2388 3BE42520 */  addi    r31, r4, AlarmForTimeout@l
/* 0ACDEC 800B238C 90670014 */  stw     r3, DI_DIMAR(r7)
/* 0ACDF0 800B2390 387F0000 */  addi    r3, r31, 0
/* 0ACDF4 800B2394 90C70018 */  stw     r6, DI_DILENGTH(r7)
/* 0ACDF8 800B2398 9007001C */  stw     r0, DI_DICR(r7)
/* 0ACDFC 800B239C 800500F8 */  lwz     r0, 0xf8(r5)
/* 0ACE00 800B23A0 5400F0BE */  srwi    r0, r0, 2
/* 0ACE04 800B23A4 1FC0000A */  mulli   r30, r0, 0xa
/* 0ACE08 800B23A8 4BFEA36D */  bl      OSCreateAlarm
/* 0ACE0C 800B23AC 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0ACE10 800B23B0 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0ACE14 800B23B4 387F0000 */  addi    r3, r31, 0
/* 0ACE18 800B23B8 38DE0000 */  addi    r6, r30, 0
/* 0ACE1C 800B23BC 38A00000 */  li      r5, 0
/* 0ACE20 800B23C0 4BFEA5B5 */  bl      OSSetAlarm
/* 0ACE24 800B23C4 8001001C */  lwz     r0, 0x1c(r1)
/* 0ACE28 800B23C8 38600001 */  li      r3, 1
/* 0ACE2C 800B23CC 83E10014 */  lwz     r31, 0x14(r1)
/* 0ACE30 800B23D0 83C10010 */  lwz     r30, 0x10(r1)
/* 0ACE34 800B23D4 38210018 */  addi    r1, r1, 0x18
/* 0ACE38 800B23D8 7C0803A6 */  mtlr    r0
/* 0ACE3C 800B23DC 4E800020 */  blr     

glabel DVDLowAudioStream
/* 0ACE40 800B23E0 7C0802A6 */  mflr    r0
/* 0ACE44 800B23E4 90010004 */  stw     r0, 4(r1)
/* 0ACE48 800B23E8 38000000 */  li      r0, 0
/* 0ACE4C 800B23EC 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0ACE50 800B23F0 93E1001C */  stw     r31, 0x1c(r1)
/* 0ACE54 800B23F4 93C10018 */  stw     r30, 0x18(r1)
/* 0ACE58 800B23F8 90CD8CD0 */  stw     r6, Callback@sda21(r13)
/* 0ACE5C 800B23FC 3CC0CC00 */  lis     r6, DI_REGS_BASE@ha
/* 0ACE60 800B2400 38C66000 */  addi    r6, r6, DI_REGS_BASE@l
/* 0ACE64 800B2404 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0ACE68 800B2408 6460E100 */  oris    r0, r3, 0xe100
/* 0ACE6C 800B240C 3C608013 */  lis     r3, AlarmForTimeout@ha
/* 0ACE70 800B2410 90060008 */  stw     r0, DI_DICMDBUF0(r6)
/* 0ACE74 800B2414 54A0F0BE */  srwi    r0, r5, 2
/* 0ACE78 800B2418 3BE32520 */  addi    r31, r3, AlarmForTimeout@l
/* 0ACE7C 800B241C 9006000C */  stw     r0, DI_DICMDBUF1(r6)
/* 0ACE80 800B2420 38000001 */  li      r0, 1
/* 0ACE84 800B2424 387F0000 */  addi    r3, r31, 0
/* 0ACE88 800B2428 90860010 */  stw     r4, DI_DICMDBUF2(r6)
/* 0ACE8C 800B242C 3C808000 */  lis     r4, 0x8000
/* 0ACE90 800B2430 9006001C */  stw     r0, DI_DICR(r6)
/* 0ACE94 800B2434 800400F8 */  lwz     r0, 0xf8(r4)
/* 0ACE98 800B2438 5400F0BE */  srwi    r0, r0, 2
/* 0ACE9C 800B243C 1FC0000A */  mulli   r30, r0, 0xa
/* 0ACEA0 800B2440 4BFEA2D5 */  bl      OSCreateAlarm
/* 0ACEA4 800B2444 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0ACEA8 800B2448 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0ACEAC 800B244C 387F0000 */  addi    r3, r31, 0
/* 0ACEB0 800B2450 38DE0000 */  addi    r6, r30, 0
/* 0ACEB4 800B2454 38A00000 */  li      r5, 0
/* 0ACEB8 800B2458 4BFEA51D */  bl      OSSetAlarm
/* 0ACEBC 800B245C 80010024 */  lwz     r0, 0x24(r1)
/* 0ACEC0 800B2460 38600001 */  li      r3, 1
/* 0ACEC4 800B2464 83E1001C */  lwz     r31, 0x1c(r1)
/* 0ACEC8 800B2468 83C10018 */  lwz     r30, 0x18(r1)
/* 0ACECC 800B246C 38210020 */  addi    r1, r1, 0x20
/* 0ACED0 800B2470 7C0803A6 */  mtlr    r0
/* 0ACED4 800B2474 4E800020 */  blr     

glabel DVDLowRequestAudioStatus
/* 0ACED8 800B2478 7C0802A6 */  mflr    r0
/* 0ACEDC 800B247C 90010004 */  stw     r0, 4(r1)
/* 0ACEE0 800B2480 38000000 */  li      r0, 0
/* 0ACEE4 800B2484 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0ACEE8 800B2488 93E10014 */  stw     r31, 0x14(r1)
/* 0ACEEC 800B248C 93C10010 */  stw     r30, 0x10(r1)
/* 0ACEF0 800B2490 908D8CD0 */  stw     r4, Callback@sda21(r13)
/* 0ACEF4 800B2494 3C80CC00 */  lis     r4, DI_REGS_BASE@ha
/* 0ACEF8 800B2498 38846000 */  addi    r4, r4, DI_REGS_BASE@l
/* 0ACEFC 800B249C 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0ACF00 800B24A0 6460E200 */  oris    r0, r3, 0xe200
/* 0ACF04 800B24A4 3C608013 */  lis     r3, AlarmForTimeout@ha
/* 0ACF08 800B24A8 90040008 */  stw     r0, DI_DICMDBUF0(r4)
/* 0ACF0C 800B24AC 38000001 */  li      r0, 1
/* 0ACF10 800B24B0 3BE32520 */  addi    r31, r3, AlarmForTimeout@l
/* 0ACF14 800B24B4 9004001C */  stw     r0, DI_DICR(r4)
/* 0ACF18 800B24B8 3C808000 */  lis     r4, 0x8000
/* 0ACF1C 800B24BC 387F0000 */  addi    r3, r31, 0
/* 0ACF20 800B24C0 800400F8 */  lwz     r0, 0xf8(r4)
/* 0ACF24 800B24C4 5400F0BE */  srwi    r0, r0, 2
/* 0ACF28 800B24C8 1FC0000A */  mulli   r30, r0, 0xa
/* 0ACF2C 800B24CC 4BFEA249 */  bl      OSCreateAlarm
/* 0ACF30 800B24D0 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0ACF34 800B24D4 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0ACF38 800B24D8 387F0000 */  addi    r3, r31, 0
/* 0ACF3C 800B24DC 38DE0000 */  addi    r6, r30, 0
/* 0ACF40 800B24E0 38A00000 */  li      r5, 0
/* 0ACF44 800B24E4 4BFEA491 */  bl      OSSetAlarm
/* 0ACF48 800B24E8 8001001C */  lwz     r0, 0x1c(r1)
/* 0ACF4C 800B24EC 38600001 */  li      r3, 1
/* 0ACF50 800B24F0 83E10014 */  lwz     r31, 0x14(r1)
/* 0ACF54 800B24F4 83C10010 */  lwz     r30, 0x10(r1)
/* 0ACF58 800B24F8 38210018 */  addi    r1, r1, 0x18
/* 0ACF5C 800B24FC 7C0803A6 */  mtlr    r0
/* 0ACF60 800B2500 4E800020 */  blr     

glabel DVDLowAudioBufferConfig
/* 0ACF64 800B2504 7C0802A6 */  mflr    r0
/* 0ACF68 800B2508 2C030000 */  cmpwi   r3, 0
/* 0ACF6C 800B250C 90010004 */  stw     r0, 4(r1)
/* 0ACF70 800B2510 38000000 */  li      r0, 0
/* 0ACF74 800B2514 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0ACF78 800B2518 93E1001C */  stw     r31, 0x1c(r1)
/* 0ACF7C 800B251C 93C10018 */  stw     r30, 0x18(r1)
/* 0ACF80 800B2520 90AD8CD0 */  stw     r5, Callback@sda21(r13)
/* 0ACF84 800B2524 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0ACF88 800B2528 41820008 */  beq     lbl_800B2530
/* 0ACF8C 800B252C 3C000001 */  lis     r0, 1
lbl_800B2530:
/* 0ACF90 800B2530 6400E400 */  oris    r0, r0, 0xe400
/* 0ACF94 800B2534 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0ACF98 800B2538 7C800378 */  or      r0, r4, r0
/* 0ACF9C 800B253C 38636000 */  addi    r3, r3, DI_REGS_BASE@l
/* 0ACFA0 800B2540 90030008 */  stw     r0, DI_DICMDBUF0(r3)
/* 0ACFA4 800B2544 38000001 */  li      r0, 1
/* 0ACFA8 800B2548 3C808000 */  lis     r4, 0x8000
/* 0ACFAC 800B254C 9003001C */  stw     r0, DI_DICR(r3)
/* 0ACFB0 800B2550 3C608013 */  lis     r3, AlarmForTimeout@ha
/* 0ACFB4 800B2554 3BE32520 */  addi    r31, r3, AlarmForTimeout@l
/* 0ACFB8 800B2558 800400F8 */  lwz     r0, 0xf8(r4)
/* 0ACFBC 800B255C 387F0000 */  addi    r3, r31, 0
/* 0ACFC0 800B2560 5400F0BE */  srwi    r0, r0, 2
/* 0ACFC4 800B2564 1FC0000A */  mulli   r30, r0, 0xa
/* 0ACFC8 800B2568 4BFEA1AD */  bl      OSCreateAlarm
/* 0ACFCC 800B256C 3C60800B */  lis     r3, AlarmHandlerForTimeout@ha
/* 0ACFD0 800B2570 38E31C30 */  addi    r7, r3, AlarmHandlerForTimeout@l
/* 0ACFD4 800B2574 387F0000 */  addi    r3, r31, 0
/* 0ACFD8 800B2578 38DE0000 */  addi    r6, r30, 0
/* 0ACFDC 800B257C 38A00000 */  li      r5, 0
/* 0ACFE0 800B2580 4BFEA3F5 */  bl      OSSetAlarm
/* 0ACFE4 800B2584 80010024 */  lwz     r0, 0x24(r1)
/* 0ACFE8 800B2588 38600001 */  li      r3, 1
/* 0ACFEC 800B258C 83E1001C */  lwz     r31, 0x1c(r1)
/* 0ACFF0 800B2590 83C10018 */  lwz     r30, 0x18(r1)
/* 0ACFF4 800B2594 38210020 */  addi    r1, r1, 0x20
/* 0ACFF8 800B2598 7C0803A6 */  mtlr    r0
/* 0ACFFC 800B259C 4E800020 */  blr     

glabel DVDLowReset
/* 0AD000 800B25A0 7C0802A6 */  mflr    r0
/* 0AD004 800B25A4 3C80CC00 */  lis     r4, HW_REGS_BASE@ha
/* 0AD008 800B25A8 90010004 */  stw     r0, 4(r1)
/* 0AD00C 800B25AC 38000002 */  li      r0, 2
/* 0AD010 800B25B0 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0AD014 800B25B4 BF410008 */  stmw    r26, 8(r1)
/* 0AD018 800B25B8 3BE43000 */  addi    r31, r4, PI_REGS_BASE@l
/* 0AD01C 800B25BC 90046004 */  stw     r0, (DI_REGS_BASE + DI_DICVR)@l(r4)
/* 0AD020 800B25C0 83C43024 */  lwz     r30, (PI_REGS_BASE + PI_24)@l(r4)
/* 0AD024 800B25C4 57C007B8 */  rlwinm  r0, r30, 0, 0x1e, 0x1c
/* 0AD028 800B25C8 60000001 */  ori     r0, r0, 1
/* 0AD02C 800B25CC 941F0024 */  stwu    r0, PI_24(r31)
/* 0AD030 800B25D0 4BFEFCF9 */  bl      __OSGetSystemTime
/* 0AD034 800B25D4 3CA08000 */  lis     r5, 0x8000
/* 0AD038 800B25D8 800500F8 */  lwz     r0, 0xf8(r5)
/* 0AD03C 800B25DC 3CA0431C */  lis     r5, 0x431c
/* 0AD040 800B25E0 38A5DE83 */  addi    r5, r5, -8573
/* 0AD044 800B25E4 5400F0BE */  srwi    r0, r0, 2
/* 0AD048 800B25E8 7C050016 */  mulhwu  r0, r5, r0
/* 0AD04C 800B25EC 54008BFE */  srwi    r0, r0, 0xf
/* 0AD050 800B25F0 1C00000C */  mulli   r0, r0, 0xc
/* 0AD054 800B25F4 3B440000 */  addi    r26, r4, 0
/* 0AD058 800B25F8 3B630000 */  addi    r27, r3, 0
/* 0AD05C 800B25FC 541CE8FE */  srwi    r28, r0, 3
/* 0AD060 800B2600 3BA00000 */  li      r29, 0
lbl_800B2604:
/* 0AD064 800B2604 4BFEFCC5 */  bl      __OSGetSystemTime
/* 0AD068 800B2608 7CBA2010 */  subfc   r5, r26, r4
/* 0AD06C 800B260C 7C1B1910 */  subfe   r0, r27, r3
/* 0AD070 800B2610 6C048000 */  xoris   r4, r0, 0x8000
/* 0AD074 800B2614 6FA38000 */  xoris   r3, r29, 0x8000
/* 0AD078 800B2618 7C1C2810 */  subfc   r0, r28, r5
/* 0AD07C 800B261C 7C632110 */  subfe   r3, r3, r4
/* 0AD080 800B2620 7C642110 */  subfe   r3, r4, r4
/* 0AD084 800B2624 7C6300D1 */  neg.    r3, r3
/* 0AD088 800B2628 4082FFDC */  bne     lbl_800B2604
/* 0AD08C 800B262C 63C00005 */  ori     r0, r30, 5
/* 0AD090 800B2630 901F0000 */  stw     r0, 0(r31)
/* 0AD094 800B2634 38000001 */  li      r0, 1
/* 0AD098 800B2638 900D8CE0 */  stw     r0, ResetOccurred@sda21(r13)
/* 0AD09C 800B263C 4BFEFC8D */  bl      __OSGetSystemTime
/* 0AD0A0 800B2640 908D8CDC */  stw     r4, (LastResetEnd + 4)@sda21(r13)
/* 0AD0A4 800B2644 906D8CD8 */  stw     r3, LastResetEnd@sda21(r13)
/* 0AD0A8 800B2648 BB410008 */  lmw     r26, 8(r1)
/* 0AD0AC 800B264C 80010024 */  lwz     r0, 0x24(r1)
/* 0AD0B0 800B2650 38210020 */  addi    r1, r1, 0x20
/* 0AD0B4 800B2654 7C0803A6 */  mtlr    r0
/* 0AD0B8 800B2658 4E800020 */  blr     

glabel DVDLowBreak
/* 0AD0BC 800B265C 38000001 */  li      r0, 1
/* 0AD0C0 800B2660 900D8CC8 */  stw     r0, StopAtNextInt@sda21(r13)
/* 0AD0C4 800B2664 38600001 */  li      r3, 1
/* 0AD0C8 800B2668 900D8CE8 */  stw     r0, Breaking@sda21(r13)
/* 0AD0CC 800B266C 4E800020 */  blr     

glabel DVDLowClearCallback
/* 0AD0D0 800B2670 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AD0D4 800B2674 38000000 */  li      r0, 0
/* 0AD0D8 800B2678 90036004 */  stw     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AD0DC 800B267C 806D8CD0 */  lwz     r3, Callback@sda21(r13)
/* 0AD0E0 800B2680 900D8CE4 */  stw     r0, WaitingCoverClose@sda21(r13)
/* 0AD0E4 800B2684 900D8CD0 */  stw     r0, Callback@sda21(r13)
/* 0AD0E8 800B2688 4E800020 */  blr     

glabel __DVDLowSetWAType
/* 0AD0EC 800B268C 7C0802A6 */  mflr    r0
/* 0AD0F0 800B2690 90010004 */  stw     r0, 4(r1)
/* 0AD0F4 800B2694 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AD0F8 800B2698 93E10014 */  stw     r31, 0x14(r1)
/* 0AD0FC 800B269C 3BE40000 */  addi    r31, r4, 0
/* 0AD100 800B26A0 93C10010 */  stw     r30, 0x10(r1)
/* 0AD104 800B26A4 3BC30000 */  addi    r30, r3, 0
/* 0AD108 800B26A8 4BFEC655 */  bl      OSDisableInterrupts
/* 0AD10C 800B26AC 93CD8CEC */  stw     r30, WorkAroundType@sda21(r13)
/* 0AD110 800B26B0 93ED8CF0 */  stw     r31, WorkAroundSeekLocation@sda21(r13)
/* 0AD114 800B26B4 4BFEC671 */  bl      OSRestoreInterrupts
/* 0AD118 800B26B8 8001001C */  lwz     r0, 0x1c(r1)
/* 0AD11C 800B26BC 83E10014 */  lwz     r31, 0x14(r1)
/* 0AD120 800B26C0 83C10010 */  lwz     r30, 0x10(r1)
/* 0AD124 800B26C4 38210018 */  addi    r1, r1, 0x18
/* 0AD128 800B26C8 7C0803A6 */  mtlr    r0
/* 0AD12C 800B26CC 4E800020 */  blr     

glabel __DVDLowTestAlarm
/* 0AD130 800B26D0 3C808013 */  lis     r4, AlarmForBreak@ha
/* 0AD134 800B26D4 38042548 */  addi    r0, r4, AlarmForBreak@l
/* 0AD138 800B26D8 7C030040 */  cmplw   r3, r0
/* 0AD13C 800B26DC 4082000C */  bne     lbl_800B26E8
/* 0AD140 800B26E0 38600001 */  li      r3, 1
/* 0AD144 800B26E4 4E800020 */  blr     
lbl_800B26E8:
/* 0AD148 800B26E8 3C808013 */  lis     r4, AlarmForTimeout@ha
/* 0AD14C 800B26EC 38042520 */  addi    r0, r4, AlarmForTimeout@l
/* 0AD150 800B26F0 7C030040 */  cmplw   r3, r0
/* 0AD154 800B26F4 4082000C */  bne     lbl_800B2700
/* 0AD158 800B26F8 38600001 */  li      r3, 1
/* 0AD15C 800B26FC 4E800020 */  blr     
lbl_800B2700:
/* 0AD160 800B2700 38600000 */  li      r3, 0
/* 0AD164 800B2704 4E800020 */  blr     

.section .bss, "wa"

.balign 4

/* 0012F538 801324B8 003C */
CommandList:
    .skip 60

.balign 8

/* 0012F578 801324F8 0028 */
AlarmForWA:
    .skip 40

/* 0012F5A0 80132520 0028 */
AlarmForTimeout:
    .skip 40

/* 0012F5C8 80132548 0028 */
AlarmForBreak:
    .skip 40

/* 0012F5F0 80132570 000C */
Prev:
    .skip 12

/* 0012F5FC 8013257C 000C */
Curr:
    .skip 12

.section .sdata, "wa"

.balign 8

/* 000F1768 801354E8 0004 */
FirstRead:
    .long 0x00000001

.section .sbss, "wa"

.balign 8

/* 000F1C28 801359A8 0004 */
StopAtNextInt:
    .skip 4

/* 000F1C2C 801359AC 0004 */
LastLength:
    .skip 4

/* 000F1C30 801359B0 0004 */
Callback:
    .skip 4

/* 000F1C34 801359B4 0004 */
ResetCoverCallback:
    .skip 4

/* 000F1C38 801359B8 0008 */
LastResetEnd:
    .skip 8

/* 000F1C40 801359C0 0004 */
ResetOccurred:
    .skip 4

/* 000F1C44 801359C4 0004 */
WaitingCoverClose:
    .skip 4

/* 000F1C48 801359C8 0004 */
Breaking:
    .skip 4

/* 000F1C4C 801359CC 0004 */
WorkAroundType:
    .skip 4

/* 000F1C50 801359D0 0004 */
WorkAroundSeekLocation:
    .skip 4

.balign 8

/* 000F1C58 801359D8 0008 */
LastReadFinished:
    .skip 8

/* 000F1C60 801359E0 0008 */
LastReadIssued:
    .skip 8

/* 000F1C68 801359E8 0004 */
LastCommandWasRead:
    .skip 4

/* 000F1C6C 801359EC 0004 */
NextCommandNumber:
    .skip 4
