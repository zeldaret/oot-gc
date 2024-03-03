glabel xlCoreInitMem
/* 0005DC 80005B7C 7C0802A6 */  mflr    r0
/* 0005E0 80005B80 90010004 */  stw     r0, 4(r1)
/* 0005E4 80005B84 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0005E8 80005B88 93E1000C */  stw     r31, 0xc(r1)
/* 0005EC 80005B8C 93C10008 */  stw     r30, 8(r1)
/* 0005F0 80005B90 48097901 */  bl      OSGetArenaLo
/* 0005F4 80005B94 7C7F1B78 */  mr      r31, r3
/* 0005F8 80005B98 93ED88B8 */  stw     r31, gArenaLo@sda21(r13)
/* 0005FC 80005B9C 480978ED */  bl      OSGetArenaHi
/* 000600 80005BA0 906D88B4 */  stw     r3, gArenaHi@sda21(r13)
/* 000604 80005BA4 381F001F */  addi    r0, r31, 0x1f
/* 000608 80005BA8 806D88BC */  lwz     r3, rmode@sda21(r13)
/* 00060C 80005BAC 54000034 */  rlwinm  r0, r0, 0, 0, 0x1a
/* 000610 80005BB0 A0830004 */  lhz     r4, 4(r3)
/* 000614 80005BB4 A0630008 */  lhz     r3, 8(r3)
/* 000618 80005BB8 3884000F */  addi    r4, r4, 0xf
/* 00061C 80005BBC 900D8DB4 */  stw     r0, DemoFrameBuffer1@sda21(r13)
/* 000620 80005BC0 54800436 */  rlwinm  r0, r4, 0, 0x10, 0x1b
/* 000624 80005BC4 7C6019D6 */  mullw   r3, r0, r3
/* 000628 80005BC8 800D8DB4 */  lwz     r0, DemoFrameBuffer1@sda21(r13)
/* 00062C 80005BCC 5463083C */  slwi    r3, r3, 1
/* 000630 80005BD0 3863001F */  addi    r3, r3, 0x1f
/* 000634 80005BD4 7C001A14 */  add     r0, r0, r3
/* 000638 80005BD8 54000034 */  rlwinm  r0, r0, 0, 0, 0x1a
/* 00063C 80005BDC 900D8DB0 */  stw     r0, DemoFrameBuffer2@sda21(r13)
/* 000640 80005BE0 808D8DB0 */  lwz     r4, DemoFrameBuffer2@sda21(r13)
/* 000644 80005BE4 7C041A14 */  add     r0, r4, r3
/* 000648 80005BE8 908D8DAC */  stw     r4, DemoCurrentBuffer@sda21(r13)
/* 00064C 80005BEC 54030034 */  rlwinm  r3, r0, 0, 0, 0x1a
/* 000650 80005BF0 480978B1 */  bl      OSSetArenaLo
/* 000654 80005BF4 4809789D */  bl      OSGetArenaLo
/* 000658 80005BF8 7C7F1B78 */  mr      r31, r3
/* 00065C 80005BFC 4809788D */  bl      OSGetArenaHi
/* 000660 80005C00 3BC30000 */  addi    r30, r3, 0
/* 000664 80005C04 387F0000 */  addi    r3, r31, 0
/* 000668 80005C08 389E0000 */  addi    r4, r30, 0
/* 00066C 80005C0C 38A00001 */  li      r5, 1
/* 000670 80005C10 4809743D */  bl      OSInitAlloc
/* 000674 80005C14 7C7F1B78 */  mr      r31, r3
/* 000678 80005C18 48097889 */  bl      OSSetArenaLo
/* 00067C 80005C1C 381F001F */  addi    r0, r31, 0x1f
/* 000680 80005C20 57DF0034 */  rlwinm  r31, r30, 0, 0, 0x1a
/* 000684 80005C24 54030034 */  rlwinm  r3, r0, 0, 0, 0x1a
/* 000688 80005C28 389F0000 */  addi    r4, r31, 0
/* 00068C 80005C2C 48097491 */  bl      OSCreateHeap
/* 000690 80005C30 4809740D */  bl      OSSetCurrentHeap
/* 000694 80005C34 7FE3FB78 */  mr      r3, r31
/* 000698 80005C38 48097869 */  bl      OSSetArenaLo
/* 00069C 80005C3C 80010014 */  lwz     r0, 0x14(r1)
/* 0006A0 80005C40 83E1000C */  lwz     r31, 0xc(r1)
/* 0006A4 80005C44 83C10008 */  lwz     r30, 8(r1)
/* 0006A8 80005C48 7C0803A6 */  mtlr    r0
/* 0006AC 80005C4C 38210010 */  addi    r1, r1, 0x10
/* 0006B0 80005C50 4E800020 */  blr     
