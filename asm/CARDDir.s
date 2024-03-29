# CARDDir.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __CARDGetDirBlock
/* 0B839C 800BD93C 80630084 */  lwz     r3, 0x84(r3)
/* 0B83A0 800BD940 4E800020 */  blr     

WriteCallback:
/* 0B83A4 800BD944 7C0802A6 */  mflr    r0
/* 0B83A8 800BD948 90010004 */  stw     r0, 4(r1)
/* 0B83AC 800BD94C 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0B83B0 800BD950 93E1001C */  stw     r31, 0x1c(r1)
/* 0B83B4 800BD954 93C10018 */  stw     r30, 0x18(r1)
/* 0B83B8 800BD958 7C9E2379 */  or.     r30, r4, r4
/* 0B83BC 800BD95C 93A10014 */  stw     r29, 0x14(r1)
/* 0B83C0 800BD960 3BA30000 */  addi    r29, r3, 0
/* 0B83C4 800BD964 1CBD0110 */  mulli   r5, r29, 0x110
/* 0B83C8 800BD968 3C608013 */  lis     r3, __CARDBlock@ha
/* 0B83CC 800BD96C 380327D0 */  addi    r0, r3, __CARDBlock@l
/* 0B83D0 800BD970 7FE02A14 */  add     r31, r0, r5
/* 0B83D4 800BD974 41800044 */  blt     lbl_800BD9B8
/* 0B83D8 800BD978 807F0080 */  lwz     r3, 0x80(r31)
/* 0B83DC 800BD97C 801F0084 */  lwz     r0, 0x84(r31)
/* 0B83E0 800BD980 38832000 */  addi    r4, r3, 0x2000
/* 0B83E4 800BD984 7C002040 */  cmplw   r0, r4
/* 0B83E8 800BD988 38034000 */  addi    r0, r3, 0x4000
/* 0B83EC 800BD98C 40820018 */  bne     lbl_800BD9A4
/* 0B83F0 800BD990 901F0084 */  stw     r0, 0x84(r31)
/* 0B83F4 800BD994 7C030378 */  mr      r3, r0
/* 0B83F8 800BD998 38A02000 */  li      r5, 0x2000
/* 0B83FC 800BD99C 4BF47B29 */  bl      memcpy
/* 0B8400 800BD9A0 48000018 */  b       lbl_800BD9B8
lbl_800BD9A4:
/* 0B8404 800BD9A4 909F0084 */  stw     r4, 0x84(r31)
/* 0B8408 800BD9A8 38640000 */  addi    r3, r4, 0
/* 0B840C 800BD9AC 7C040378 */  mr      r4, r0
/* 0B8410 800BD9B0 38A02000 */  li      r5, 0x2000
/* 0B8414 800BD9B4 4BF47B11 */  bl      memcpy
lbl_800BD9B8:
/* 0B8418 800BD9B8 801F00D0 */  lwz     r0, 0xd0(r31)
/* 0B841C 800BD9BC 28000000 */  cmplwi  r0, 0
/* 0B8420 800BD9C0 40820010 */  bne     lbl_800BD9D0
/* 0B8424 800BD9C4 387F0000 */  addi    r3, r31, 0
/* 0B8428 800BD9C8 389E0000 */  addi    r4, r30, 0
/* 0B842C 800BD9CC 4BFFE3A9 */  bl      __CARDPutControlBlock
lbl_800BD9D0:
/* 0B8430 800BD9D0 801F00D8 */  lwz     r0, 0xd8(r31)
/* 0B8434 800BD9D4 28000000 */  cmplwi  r0, 0
/* 0B8438 800BD9D8 7C0C0378 */  mr      r12, r0
/* 0B843C 800BD9DC 4182001C */  beq     lbl_800BD9F8
/* 0B8440 800BD9E0 38000000 */  li      r0, 0
/* 0B8444 800BD9E4 7D8803A6 */  mtlr    r12
/* 0B8448 800BD9E8 901F00D8 */  stw     r0, 0xd8(r31)
/* 0B844C 800BD9EC 387D0000 */  addi    r3, r29, 0
/* 0B8450 800BD9F0 389E0000 */  addi    r4, r30, 0
/* 0B8454 800BD9F4 4E800021 */  blrl    
lbl_800BD9F8:
/* 0B8458 800BD9F8 80010024 */  lwz     r0, 0x24(r1)
/* 0B845C 800BD9FC 83E1001C */  lwz     r31, 0x1c(r1)
/* 0B8460 800BDA00 83C10018 */  lwz     r30, 0x18(r1)
/* 0B8464 800BDA04 83A10014 */  lwz     r29, 0x14(r1)
/* 0B8468 800BDA08 38210020 */  addi    r1, r1, 0x20
/* 0B846C 800BDA0C 7C0803A6 */  mtlr    r0
/* 0B8470 800BDA10 4E800020 */  blr     

EraseCallback:
/* 0B8474 800BDA14 7C0802A6 */  mflr    r0
/* 0B8478 800BDA18 90010004 */  stw     r0, 4(r1)
/* 0B847C 800BDA1C 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0B8480 800BDA20 93E10024 */  stw     r31, 0x24(r1)
/* 0B8484 800BDA24 3BE30000 */  addi    r31, r3, 0
/* 0B8488 800BDA28 3C608013 */  lis     r3, __CARDBlock@ha
/* 0B848C 800BDA2C 93C10020 */  stw     r30, 0x20(r1)
/* 0B8490 800BDA30 1CBF0110 */  mulli   r5, r31, 0x110
/* 0B8494 800BDA34 93A1001C */  stw     r29, 0x1c(r1)
/* 0B8498 800BDA38 380327D0 */  addi    r0, r3, __CARDBlock@l
/* 0B849C 800BDA3C 7C9D2379 */  or.     r29, r4, r4
/* 0B84A0 800BDA40 7FC02A14 */  add     r30, r0, r5
/* 0B84A4 800BDA44 4180003C */  blt     lbl_800BDA80
/* 0B84A8 800BDA48 80BE0084 */  lwz     r5, 0x84(r30)
/* 0B84AC 800BDA4C 3C60800C */  lis     r3, WriteCallback@ha
/* 0B84B0 800BDA50 801E0080 */  lwz     r0, 0x80(r30)
/* 0B84B4 800BDA54 38E3D944 */  addi    r7, r3, WriteCallback@l
/* 0B84B8 800BDA58 807E000C */  lwz     r3, 0xc(r30)
/* 0B84BC 800BDA5C 7C002850 */  subf    r0, r0, r5
/* 0B84C0 800BDA60 54009B7E */  srwi    r0, r0, 0xd
/* 0B84C4 800BDA64 7C8301D6 */  mullw   r4, r3, r0
/* 0B84C8 800BDA68 38C50000 */  addi    r6, r5, 0
/* 0B84CC 800BDA6C 387F0000 */  addi    r3, r31, 0
/* 0B84D0 800BDA70 38A02000 */  li      r5, 0x2000
/* 0B84D4 800BDA74 4BFFFA49 */  bl      __CARDWrite
/* 0B84D8 800BDA78 7C7D1B79 */  or.     r29, r3, r3
/* 0B84DC 800BDA7C 40800044 */  bge     lbl_800BDAC0
lbl_800BDA80:
/* 0B84E0 800BDA80 801E00D0 */  lwz     r0, 0xd0(r30)
/* 0B84E4 800BDA84 28000000 */  cmplwi  r0, 0
/* 0B84E8 800BDA88 40820010 */  bne     lbl_800BDA98
/* 0B84EC 800BDA8C 387E0000 */  addi    r3, r30, 0
/* 0B84F0 800BDA90 389D0000 */  addi    r4, r29, 0
/* 0B84F4 800BDA94 4BFFE2E1 */  bl      __CARDPutControlBlock
lbl_800BDA98:
/* 0B84F8 800BDA98 801E00D8 */  lwz     r0, 0xd8(r30)
/* 0B84FC 800BDA9C 28000000 */  cmplwi  r0, 0
/* 0B8500 800BDAA0 7C0C0378 */  mr      r12, r0
/* 0B8504 800BDAA4 4182001C */  beq     lbl_800BDAC0
/* 0B8508 800BDAA8 38000000 */  li      r0, 0
/* 0B850C 800BDAAC 7D8803A6 */  mtlr    r12
/* 0B8510 800BDAB0 901E00D8 */  stw     r0, 0xd8(r30)
/* 0B8514 800BDAB4 387F0000 */  addi    r3, r31, 0
/* 0B8518 800BDAB8 389D0000 */  addi    r4, r29, 0
/* 0B851C 800BDABC 4E800021 */  blrl    
lbl_800BDAC0:
/* 0B8520 800BDAC0 8001002C */  lwz     r0, 0x2c(r1)
/* 0B8524 800BDAC4 83E10024 */  lwz     r31, 0x24(r1)
/* 0B8528 800BDAC8 83C10020 */  lwz     r30, 0x20(r1)
/* 0B852C 800BDACC 83A1001C */  lwz     r29, 0x1c(r1)
/* 0B8530 800BDAD0 38210028 */  addi    r1, r1, 0x28
/* 0B8534 800BDAD4 7C0803A6 */  mtlr    r0
/* 0B8538 800BDAD8 4E800020 */  blr     

glabel __CARDUpdateDir
/* 0B853C 800BDADC 7C0802A6 */  mflr    r0
/* 0B8540 800BDAE0 90010004 */  stw     r0, 4(r1)
/* 0B8544 800BDAE4 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0B8548 800BDAE8 93E10024 */  stw     r31, 0x24(r1)
/* 0B854C 800BDAEC 93C10020 */  stw     r30, 0x20(r1)
/* 0B8550 800BDAF0 93A1001C */  stw     r29, 0x1c(r1)
/* 0B8554 800BDAF4 3BA40000 */  addi    r29, r4, 0
/* 0B8558 800BDAF8 93810018 */  stw     r28, 0x18(r1)
/* 0B855C 800BDAFC 3B830000 */  addi    r28, r3, 0
/* 0B8560 800BDB00 1CBC0110 */  mulli   r5, r28, 0x110
/* 0B8564 800BDB04 3C608013 */  lis     r3, __CARDBlock@ha
/* 0B8568 800BDB08 380327D0 */  addi    r0, r3, __CARDBlock@l
/* 0B856C 800BDB0C 7FC02A14 */  add     r30, r0, r5
/* 0B8570 800BDB10 801E0000 */  lwz     r0, 0(r30)
/* 0B8574 800BDB14 2C000000 */  cmpwi   r0, 0
/* 0B8578 800BDB18 4082000C */  bne     lbl_800BDB24
/* 0B857C 800BDB1C 3860FFFD */  li      r3, -3
/* 0B8580 800BDB20 48000060 */  b       lbl_800BDB80
lbl_800BDB24:
/* 0B8584 800BDB24 83FE0084 */  lwz     r31, 0x84(r30)
/* 0B8588 800BDB28 38801FFC */  li      r4, 0x1ffc
/* 0B858C 800BDB2C A8BF1FFA */  lha     r5, 0x1ffa(r31)
/* 0B8590 800BDB30 38DF1FC0 */  addi    r6, r31, 0x1fc0
/* 0B8594 800BDB34 387F0000 */  addi    r3, r31, 0
/* 0B8598 800BDB38 38050001 */  addi    r0, r5, 1
/* 0B859C 800BDB3C B01F1FFA */  sth     r0, 0x1ffa(r31)
/* 0B85A0 800BDB40 38A6003C */  addi    r5, r6, 0x3c
/* 0B85A4 800BDB44 38C6003E */  addi    r6, r6, 0x3e
/* 0B85A8 800BDB48 48000059 */  bl      __CARDCheckSum
/* 0B85AC 800BDB4C 387F0000 */  addi    r3, r31, 0
/* 0B85B0 800BDB50 38802000 */  li      r4, 0x2000
/* 0B85B4 800BDB54 4BFDFC59 */  bl      DCStoreRange
/* 0B85B8 800BDB58 93BE00D8 */  stw     r29, 0xd8(r30)
/* 0B85BC 800BDB5C 3C60800C */  lis     r3, EraseCallback@ha
/* 0B85C0 800BDB60 38A3DA14 */  addi    r5, r3, EraseCallback@l
/* 0B85C4 800BDB64 801E0080 */  lwz     r0, 0x80(r30)
/* 0B85C8 800BDB68 7F83E378 */  mr      r3, r28
/* 0B85CC 800BDB6C 809E000C */  lwz     r4, 0xc(r30)
/* 0B85D0 800BDB70 7C00F850 */  subf    r0, r0, r31
/* 0B85D4 800BDB74 54009B7E */  srwi    r0, r0, 0xd
/* 0B85D8 800BDB78 7C8401D6 */  mullw   r4, r4, r0
/* 0B85DC 800BDB7C 4BFFDF75 */  bl      __CARDEraseSector
lbl_800BDB80:
/* 0B85E0 800BDB80 8001002C */  lwz     r0, 0x2c(r1)
/* 0B85E4 800BDB84 83E10024 */  lwz     r31, 0x24(r1)
/* 0B85E8 800BDB88 83C10020 */  lwz     r30, 0x20(r1)
/* 0B85EC 800BDB8C 83A1001C */  lwz     r29, 0x1c(r1)
/* 0B85F0 800BDB90 83810018 */  lwz     r28, 0x18(r1)
/* 0B85F4 800BDB94 38210028 */  addi    r1, r1, 0x28
/* 0B85F8 800BDB98 7C0803A6 */  mtlr    r0
/* 0B85FC 800BDB9C 4E800020 */  blr     
