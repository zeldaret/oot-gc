glabel simulatorDrawErrorMessageWait
/* 004490 80009A30 7C0802A6 */  mflr    r0
/* 004494 80009A34 3CA0800F */  lis     r5, gOrthoMtx@ha
/* 004498 80009A38 90010004 */  stw     r0, 4(r1)
/* 00449C 80009A3C 3803FFF9 */  addi    r0, r3, -7
/* 0044A0 80009A40 28000027 */  cmplwi  r0, 0x27
/* 0044A4 80009A44 9421FF28 */  stwu    r1, -0xd8(r1)
/* 0044A8 80009A48 3C80800E */  lis     r4, gcoverOpen@ha
/* 0044AC 80009A4C BF6100C4 */  stmw    r27, 0xc4(r1)
/* 0044B0 80009A50 3BC54540 */  addi    r30, r5, gOrthoMtx@l
/* 0044B4 80009A54 3BE4B800 */  addi    r31, r4, gcoverOpen@l
/* 0044B8 80009A58 4181310C */  bgt     lbl_8000CB64
/* 0044BC 80009A5C 3C80800F */  lis     r4, jtbl_800E9F5C@ha
/* 0044C0 80009A60 38849F5C */  addi    r4, r4, jtbl_800E9F5C@l
/* 0044C4 80009A64 5400103A */  slwi    r0, r0, 2
/* 0044C8 80009A68 7C04002E */  lwzx    r0, r4, r0
/* 0044CC 80009A6C 7C0903A6 */  mtctr   r0
/* 0044D0 80009A70 4E800420 */  bctr    
glabel lbl_80009A74
/* 0044D4 80009A74 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0044D8 80009A78 7C001800 */  cmpw    r0, r3
/* 0044DC 80009A7C 41820050 */  beq     lbl_80009ACC
/* 0044E0 80009A80 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0044E4 80009A84 3C7F0001 */  addis   r3, r31, 1
/* 0044E8 80009A88 3863E514 */  addi    r3, r3, -6892
/* 0044EC 80009A8C 38810080 */  addi    r4, r1, 0x80
/* 0044F0 80009A90 480A8FA5 */  bl      DVDOpen
/* 0044F4 80009A94 2C030001 */  cmpwi   r3, 1
/* 0044F8 80009A98 40820024 */  bne     lbl_80009ABC
/* 0044FC 80009A9C 80AD8008 */  lwz     r5, gmsg_ld01Size@sda21(r13)
/* 004500 80009AA0 38610080 */  addi    r3, r1, 0x80
/* 004504 80009AA4 389E01A0 */  addi    r4, r30, 0x1a0
/* 004508 80009AA8 3805001F */  addi    r0, r5, 0x1f
/* 00450C 80009AAC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 004510 80009AB0 38C00000 */  li      r6, 0
/* 004514 80009AB4 38E00000 */  li      r7, 0
/* 004518 80009AB8 4800520D */  bl      simulatorDVDRead
lbl_80009ABC:
/* 00451C 80009ABC 38610080 */  addi    r3, r1, 0x80
/* 004520 80009AC0 480A903D */  bl      DVDClose
/* 004524 80009AC4 387E01A0 */  addi    r3, r30, 0x1a0
/* 004528 80009AC8 48005559 */  bl      simulatorUnpackTexPalette
lbl_80009ACC:
/* 00452C 80009ACC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 004530 80009AD0 3C7F0001 */  addis   r3, r31, 1
/* 004534 80009AD4 3BA3D248 */  addi    r29, r3, -11704
/* 004538 80009AD8 80E40000 */  lwz     r7, 0(r4)
/* 00453C 80009ADC 3B83DE08 */  addi    r28, r3, -8696
/* 004540 80009AE0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 004544 80009AE4 3CDF0001 */  addis   r6, r31, 1
/* 004548 80009AE8 A0070002 */  lhz     r0, 2(r7)
/* 00454C 80009AEC 81030000 */  lwz     r8, 0(r3)
/* 004550 80009AF0 3B7E01A8 */  addi    r27, r30, 0x1a8
/* 004554 80009AF4 7C040E70 */  srawi   r4, r0, 1
/* 004558 80009AF8 A0070000 */  lhz     r0, 0(r7)
/* 00455C 80009AFC 7C840194 */  addze   r4, r4
/* 004560 80009B00 80BD0000 */  lwz     r5, 0(r29)
/* 004564 80009B04 208400A0 */  subfic  r4, r4, 0xa0
/* 004568 80009B08 7C000E70 */  srawi   r0, r0, 1
/* 00456C 80009B0C A1080002 */  lhz     r8, 2(r8)
/* 004570 80009B10 80E50000 */  lwz     r7, 0(r5)
/* 004574 80009B14 7C000194 */  addze   r0, r0
/* 004578 80009B18 20A00078 */  subfic  r5, r0, 0x78
/* 00457C 80009B1C A0070000 */  lhz     r0, 0(r7)
/* 004580 80009B20 7D070E70 */  srawi   r7, r8, 1
/* 004584 80009B24 7CE70194 */  addze   r7, r7
/* 004588 80009B28 20E700A0 */  subfic  r7, r7, 0xa0
/* 00458C 80009B2C 7C000E70 */  srawi   r0, r0, 1
/* 004590 80009B30 7C000194 */  addze   r0, r0
/* 004594 80009B34 387E01A0 */  addi    r3, r30, 0x1a0
/* 004598 80009B38 210000B4 */  subfic  r8, r0, 0xb4
/* 00459C 80009B3C 38C6DE00 */  addi    r6, r6, -8704
/* 0045A0 80009B40 48003A4D */  bl      simulatorDrawOKImage
/* 0045A4 80009B44 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 0045A8 80009B48 2C000001 */  cmpwi   r0, 1
/* 0045AC 80009B4C 40820020 */  bne     lbl_80009B6C
/* 0045B0 80009B50 480AD53D */  bl      DEMOPadRead
/* 0045B4 80009B54 3C608013 */  lis     r3, DemoPad@ha
/* 0045B8 80009B58 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 0045BC 80009B5C 28000000 */  cmplwi  r0, 0
/* 0045C0 80009B60 4182000C */  beq     lbl_80009B6C
/* 0045C4 80009B64 38600000 */  li      r3, 0
/* 0045C8 80009B68 48003000 */  b       lbl_8000CB68
lbl_80009B6C:
/* 0045CC 80009B6C 38000000 */  li      r0, 0
/* 0045D0 80009B70 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 0045D4 80009B74 480AD519 */  bl      DEMOPadRead
/* 0045D8 80009B78 80BB0000 */  lwz     r5, 0(r27)
/* 0045DC 80009B7C 3CDF0001 */  addis   r6, r31, 1
/* 0045E0 80009B80 809C0000 */  lwz     r4, 0(r28)
/* 0045E4 80009B84 387E01A0 */  addi    r3, r30, 0x1a0
/* 0045E8 80009B88 80A50000 */  lwz     r5, 0(r5)
/* 0045EC 80009B8C 80E40000 */  lwz     r7, 0(r4)
/* 0045F0 80009B90 38C6DE00 */  addi    r6, r6, -8704
/* 0045F4 80009B94 A0050002 */  lhz     r0, 2(r5)
/* 0045F8 80009B98 809D0000 */  lwz     r4, 0(r29)
/* 0045FC 80009B9C 7C080E70 */  srawi   r8, r0, 1
/* 004600 80009BA0 A0050000 */  lhz     r0, 0(r5)
/* 004604 80009BA4 7D080194 */  addze   r8, r8
/* 004608 80009BA8 80A40000 */  lwz     r5, 0(r4)
/* 00460C 80009BAC 208800A0 */  subfic  r4, r8, 0xa0
/* 004610 80009BB0 A0E70002 */  lhz     r7, 2(r7)
/* 004614 80009BB4 7C080E70 */  srawi   r8, r0, 1
/* 004618 80009BB8 A0050000 */  lhz     r0, 0(r5)
/* 00461C 80009BBC 7D080194 */  addze   r8, r8
/* 004620 80009BC0 20A80078 */  subfic  r5, r8, 0x78
/* 004624 80009BC4 7CE70E70 */  srawi   r7, r7, 1
/* 004628 80009BC8 7CE70194 */  addze   r7, r7
/* 00462C 80009BCC 20E700A0 */  subfic  r7, r7, 0xa0
/* 004630 80009BD0 7C000E70 */  srawi   r0, r0, 1
/* 004634 80009BD4 7C000194 */  addze   r0, r0
/* 004638 80009BD8 210000B4 */  subfic  r8, r0, 0xb4
/* 00463C 80009BDC 480039B1 */  bl      simulatorDrawOKImage
/* 004640 80009BE0 3C608013 */  lis     r3, DemoPad@ha
/* 004644 80009BE4 38632758 */  addi    r3, r3, DemoPad@l
/* 004648 80009BE8 8803000A */  lbz     r0, 0xa(r3)
/* 00464C 80009BEC 7C000775 */  extsb.  r0, r0
/* 004650 80009BF0 4082002C */  bne     lbl_80009C1C
/* 004654 80009BF4 A0030000 */  lhz     r0, 0(r3)
/* 004658 80009BF8 70001100 */  andi.   r0, r0, 0x1100
/* 00465C 80009BFC 41820020 */  beq     lbl_80009C1C
/* 004660 80009C00 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 004664 80009C04 38800000 */  li      r4, 0
/* 004668 80009C08 80630004 */  lwz     r3, 4(r3)
/* 00466C 80009C0C 48012A85 */  bl      soundPlayBeep
/* 004670 80009C10 38600001 */  li      r3, 1
/* 004674 80009C14 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 004678 80009C18 48002F50 */  b       lbl_8000CB68
lbl_80009C1C:
/* 00467C 80009C1C 38600000 */  li      r3, 0
/* 004680 80009C20 48002F48 */  b       lbl_8000CB68
glabel lbl_80009C24
/* 004684 80009C24 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 004688 80009C28 7C001800 */  cmpw    r0, r3
/* 00468C 80009C2C 41820050 */  beq     lbl_80009C7C
/* 004690 80009C30 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 004694 80009C34 3C7F0001 */  addis   r3, r31, 1
/* 004698 80009C38 3863E528 */  addi    r3, r3, -6872
/* 00469C 80009C3C 38810080 */  addi    r4, r1, 0x80
/* 0046A0 80009C40 480A8DF5 */  bl      DVDOpen
/* 0046A4 80009C44 2C030001 */  cmpwi   r3, 1
/* 0046A8 80009C48 40820024 */  bne     lbl_80009C6C
/* 0046AC 80009C4C 80AD800C */  lwz     r5, gmsg_ld02Size@sda21(r13)
/* 0046B0 80009C50 38610080 */  addi    r3, r1, 0x80
/* 0046B4 80009C54 389E01A0 */  addi    r4, r30, 0x1a0
/* 0046B8 80009C58 3805001F */  addi    r0, r5, 0x1f
/* 0046BC 80009C5C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0046C0 80009C60 38C00000 */  li      r6, 0
/* 0046C4 80009C64 38E00000 */  li      r7, 0
/* 0046C8 80009C68 4800505D */  bl      simulatorDVDRead
lbl_80009C6C:
/* 0046CC 80009C6C 38610080 */  addi    r3, r1, 0x80
/* 0046D0 80009C70 480A8E8D */  bl      DVDClose
/* 0046D4 80009C74 387E01A0 */  addi    r3, r30, 0x1a0
/* 0046D8 80009C78 480053A9 */  bl      simulatorUnpackTexPalette
lbl_80009C7C:
/* 0046DC 80009C7C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 0046E0 80009C80 3C7F0001 */  addis   r3, r31, 1
/* 0046E4 80009C84 3B63D248 */  addi    r27, r3, -11704
/* 0046E8 80009C88 80E40000 */  lwz     r7, 0(r4)
/* 0046EC 80009C8C 3B83DE08 */  addi    r28, r3, -8696
/* 0046F0 80009C90 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 0046F4 80009C94 3CDF0001 */  addis   r6, r31, 1
/* 0046F8 80009C98 A0070002 */  lhz     r0, 2(r7)
/* 0046FC 80009C9C 81030000 */  lwz     r8, 0(r3)
/* 004700 80009CA0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 004704 80009CA4 7C040E70 */  srawi   r4, r0, 1
/* 004708 80009CA8 A0070000 */  lhz     r0, 0(r7)
/* 00470C 80009CAC 7C840194 */  addze   r4, r4
/* 004710 80009CB0 80BB0000 */  lwz     r5, 0(r27)
/* 004714 80009CB4 208400A0 */  subfic  r4, r4, 0xa0
/* 004718 80009CB8 7C000E70 */  srawi   r0, r0, 1
/* 00471C 80009CBC A1080002 */  lhz     r8, 2(r8)
/* 004720 80009CC0 80E50000 */  lwz     r7, 0(r5)
/* 004724 80009CC4 7C000194 */  addze   r0, r0
/* 004728 80009CC8 20A00078 */  subfic  r5, r0, 0x78
/* 00472C 80009CCC A0070000 */  lhz     r0, 0(r7)
/* 004730 80009CD0 7D070E70 */  srawi   r7, r8, 1
/* 004734 80009CD4 7CE70194 */  addze   r7, r7
/* 004738 80009CD8 20E700A0 */  subfic  r7, r7, 0xa0
/* 00473C 80009CDC 7C000E70 */  srawi   r0, r0, 1
/* 004740 80009CE0 7C000194 */  addze   r0, r0
/* 004744 80009CE4 387E01A0 */  addi    r3, r30, 0x1a0
/* 004748 80009CE8 210000B4 */  subfic  r8, r0, 0xb4
/* 00474C 80009CEC 38C6DE00 */  addi    r6, r6, -8704
/* 004750 80009CF0 4800389D */  bl      simulatorDrawOKImage
/* 004754 80009CF4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 004758 80009CF8 2C000001 */  cmpwi   r0, 1
/* 00475C 80009CFC 40820020 */  bne     lbl_80009D1C
/* 004760 80009D00 480AD38D */  bl      DEMOPadRead
/* 004764 80009D04 3C608013 */  lis     r3, DemoPad@ha
/* 004768 80009D08 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00476C 80009D0C 28000000 */  cmplwi  r0, 0
/* 004770 80009D10 4182000C */  beq     lbl_80009D1C
/* 004774 80009D14 38600000 */  li      r3, 0
/* 004778 80009D18 48002E50 */  b       lbl_8000CB68
lbl_80009D1C:
/* 00477C 80009D1C 38000000 */  li      r0, 0
/* 004780 80009D20 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 004784 80009D24 480AD369 */  bl      DEMOPadRead
/* 004788 80009D28 80BD0000 */  lwz     r5, 0(r29)
/* 00478C 80009D2C 3CDF0001 */  addis   r6, r31, 1
/* 004790 80009D30 809C0000 */  lwz     r4, 0(r28)
/* 004794 80009D34 387E01A0 */  addi    r3, r30, 0x1a0
/* 004798 80009D38 80A50000 */  lwz     r5, 0(r5)
/* 00479C 80009D3C 80E40000 */  lwz     r7, 0(r4)
/* 0047A0 80009D40 38C6DE00 */  addi    r6, r6, -8704
/* 0047A4 80009D44 A0050002 */  lhz     r0, 2(r5)
/* 0047A8 80009D48 809B0000 */  lwz     r4, 0(r27)
/* 0047AC 80009D4C 7C080E70 */  srawi   r8, r0, 1
/* 0047B0 80009D50 A0050000 */  lhz     r0, 0(r5)
/* 0047B4 80009D54 7D080194 */  addze   r8, r8
/* 0047B8 80009D58 80A40000 */  lwz     r5, 0(r4)
/* 0047BC 80009D5C 208800A0 */  subfic  r4, r8, 0xa0
/* 0047C0 80009D60 A0E70002 */  lhz     r7, 2(r7)
/* 0047C4 80009D64 7C080E70 */  srawi   r8, r0, 1
/* 0047C8 80009D68 A0050000 */  lhz     r0, 0(r5)
/* 0047CC 80009D6C 7D080194 */  addze   r8, r8
/* 0047D0 80009D70 20A80078 */  subfic  r5, r8, 0x78
/* 0047D4 80009D74 7CE70E70 */  srawi   r7, r7, 1
/* 0047D8 80009D78 7CE70194 */  addze   r7, r7
/* 0047DC 80009D7C 20E700A0 */  subfic  r7, r7, 0xa0
/* 0047E0 80009D80 7C000E70 */  srawi   r0, r0, 1
/* 0047E4 80009D84 7C000194 */  addze   r0, r0
/* 0047E8 80009D88 210000B4 */  subfic  r8, r0, 0xb4
/* 0047EC 80009D8C 48003801 */  bl      simulatorDrawOKImage
/* 0047F0 80009D90 3C608013 */  lis     r3, DemoPad@ha
/* 0047F4 80009D94 38632758 */  addi    r3, r3, DemoPad@l
/* 0047F8 80009D98 8803000A */  lbz     r0, 0xa(r3)
/* 0047FC 80009D9C 7C000775 */  extsb.  r0, r0
/* 004800 80009DA0 4082002C */  bne     lbl_80009DCC
/* 004804 80009DA4 A0030000 */  lhz     r0, 0(r3)
/* 004808 80009DA8 70001100 */  andi.   r0, r0, 0x1100
/* 00480C 80009DAC 41820020 */  beq     lbl_80009DCC
/* 004810 80009DB0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 004814 80009DB4 38800000 */  li      r4, 0
/* 004818 80009DB8 80630004 */  lwz     r3, 4(r3)
/* 00481C 80009DBC 480128D5 */  bl      soundPlayBeep
/* 004820 80009DC0 38600001 */  li      r3, 1
/* 004824 80009DC4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 004828 80009DC8 48002DA0 */  b       lbl_8000CB68
lbl_80009DCC:
/* 00482C 80009DCC 38600000 */  li      r3, 0
/* 004830 80009DD0 48002D98 */  b       lbl_8000CB68
glabel lbl_80009DD4
/* 004834 80009DD4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 004838 80009DD8 7C001800 */  cmpw    r0, r3
/* 00483C 80009DDC 41820050 */  beq     lbl_80009E2C
/* 004840 80009DE0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 004844 80009DE4 3C7F0001 */  addis   r3, r31, 1
/* 004848 80009DE8 3863E53C */  addi    r3, r3, -6852
/* 00484C 80009DEC 38810080 */  addi    r4, r1, 0x80
/* 004850 80009DF0 480A8C45 */  bl      DVDOpen
/* 004854 80009DF4 2C030001 */  cmpwi   r3, 1
/* 004858 80009DF8 40820024 */  bne     lbl_80009E1C
/* 00485C 80009DFC 80AD8010 */  lwz     r5, gmsg_ld03Size@sda21(r13)
/* 004860 80009E00 38610080 */  addi    r3, r1, 0x80
/* 004864 80009E04 389E01A0 */  addi    r4, r30, 0x1a0
/* 004868 80009E08 3805001F */  addi    r0, r5, 0x1f
/* 00486C 80009E0C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 004870 80009E10 38C00000 */  li      r6, 0
/* 004874 80009E14 38E00000 */  li      r7, 0
/* 004878 80009E18 48004EAD */  bl      simulatorDVDRead
lbl_80009E1C:
/* 00487C 80009E1C 38610080 */  addi    r3, r1, 0x80
/* 004880 80009E20 480A8CDD */  bl      DVDClose
/* 004884 80009E24 387E01A0 */  addi    r3, r30, 0x1a0
/* 004888 80009E28 480051F9 */  bl      simulatorUnpackTexPalette
lbl_80009E2C:
/* 00488C 80009E2C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 004890 80009E30 3C7F0001 */  addis   r3, r31, 1
/* 004894 80009E34 3B63D248 */  addi    r27, r3, -11704
/* 004898 80009E38 80E40000 */  lwz     r7, 0(r4)
/* 00489C 80009E3C 3B83DE08 */  addi    r28, r3, -8696
/* 0048A0 80009E40 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 0048A4 80009E44 3CDF0001 */  addis   r6, r31, 1
/* 0048A8 80009E48 A0070002 */  lhz     r0, 2(r7)
/* 0048AC 80009E4C 81030000 */  lwz     r8, 0(r3)
/* 0048B0 80009E50 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 0048B4 80009E54 7C040E70 */  srawi   r4, r0, 1
/* 0048B8 80009E58 A0070000 */  lhz     r0, 0(r7)
/* 0048BC 80009E5C 7C840194 */  addze   r4, r4
/* 0048C0 80009E60 80BB0000 */  lwz     r5, 0(r27)
/* 0048C4 80009E64 208400A0 */  subfic  r4, r4, 0xa0
/* 0048C8 80009E68 7C000E70 */  srawi   r0, r0, 1
/* 0048CC 80009E6C A1080002 */  lhz     r8, 2(r8)
/* 0048D0 80009E70 80E50000 */  lwz     r7, 0(r5)
/* 0048D4 80009E74 7C000194 */  addze   r0, r0
/* 0048D8 80009E78 20A00078 */  subfic  r5, r0, 0x78
/* 0048DC 80009E7C A0070000 */  lhz     r0, 0(r7)
/* 0048E0 80009E80 7D070E70 */  srawi   r7, r8, 1
/* 0048E4 80009E84 7CE70194 */  addze   r7, r7
/* 0048E8 80009E88 20E700A0 */  subfic  r7, r7, 0xa0
/* 0048EC 80009E8C 7C000E70 */  srawi   r0, r0, 1
/* 0048F0 80009E90 7C000194 */  addze   r0, r0
/* 0048F4 80009E94 387E01A0 */  addi    r3, r30, 0x1a0
/* 0048F8 80009E98 210000B4 */  subfic  r8, r0, 0xb4
/* 0048FC 80009E9C 38C6DE00 */  addi    r6, r6, -8704
/* 004900 80009EA0 480036ED */  bl      simulatorDrawOKImage
/* 004904 80009EA4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 004908 80009EA8 2C000001 */  cmpwi   r0, 1
/* 00490C 80009EAC 40820020 */  bne     lbl_80009ECC
/* 004910 80009EB0 480AD1DD */  bl      DEMOPadRead
/* 004914 80009EB4 3C608013 */  lis     r3, DemoPad@ha
/* 004918 80009EB8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00491C 80009EBC 28000000 */  cmplwi  r0, 0
/* 004920 80009EC0 4182000C */  beq     lbl_80009ECC
/* 004924 80009EC4 38600000 */  li      r3, 0
/* 004928 80009EC8 48002CA0 */  b       lbl_8000CB68
lbl_80009ECC:
/* 00492C 80009ECC 38000000 */  li      r0, 0
/* 004930 80009ED0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 004934 80009ED4 480AD1B9 */  bl      DEMOPadRead
/* 004938 80009ED8 80BD0000 */  lwz     r5, 0(r29)
/* 00493C 80009EDC 3CDF0001 */  addis   r6, r31, 1
/* 004940 80009EE0 809C0000 */  lwz     r4, 0(r28)
/* 004944 80009EE4 387E01A0 */  addi    r3, r30, 0x1a0
/* 004948 80009EE8 80A50000 */  lwz     r5, 0(r5)
/* 00494C 80009EEC 80E40000 */  lwz     r7, 0(r4)
/* 004950 80009EF0 38C6DE00 */  addi    r6, r6, -8704
/* 004954 80009EF4 A0050002 */  lhz     r0, 2(r5)
/* 004958 80009EF8 809B0000 */  lwz     r4, 0(r27)
/* 00495C 80009EFC 7C080E70 */  srawi   r8, r0, 1
/* 004960 80009F00 A0050000 */  lhz     r0, 0(r5)
/* 004964 80009F04 7D080194 */  addze   r8, r8
/* 004968 80009F08 80A40000 */  lwz     r5, 0(r4)
/* 00496C 80009F0C 208800A0 */  subfic  r4, r8, 0xa0
/* 004970 80009F10 A0E70002 */  lhz     r7, 2(r7)
/* 004974 80009F14 7C080E70 */  srawi   r8, r0, 1
/* 004978 80009F18 A0050000 */  lhz     r0, 0(r5)
/* 00497C 80009F1C 7D080194 */  addze   r8, r8
/* 004980 80009F20 20A80078 */  subfic  r5, r8, 0x78
/* 004984 80009F24 7CE70E70 */  srawi   r7, r7, 1
/* 004988 80009F28 7CE70194 */  addze   r7, r7
/* 00498C 80009F2C 20E700A0 */  subfic  r7, r7, 0xa0
/* 004990 80009F30 7C000E70 */  srawi   r0, r0, 1
/* 004994 80009F34 7C000194 */  addze   r0, r0
/* 004998 80009F38 210000B4 */  subfic  r8, r0, 0xb4
/* 00499C 80009F3C 48003651 */  bl      simulatorDrawOKImage
/* 0049A0 80009F40 3C608013 */  lis     r3, DemoPad@ha
/* 0049A4 80009F44 38632758 */  addi    r3, r3, DemoPad@l
/* 0049A8 80009F48 8803000A */  lbz     r0, 0xa(r3)
/* 0049AC 80009F4C 7C000775 */  extsb.  r0, r0
/* 0049B0 80009F50 4082002C */  bne     lbl_80009F7C
/* 0049B4 80009F54 A0030000 */  lhz     r0, 0(r3)
/* 0049B8 80009F58 70001100 */  andi.   r0, r0, 0x1100
/* 0049BC 80009F5C 41820020 */  beq     lbl_80009F7C
/* 0049C0 80009F60 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 0049C4 80009F64 38800000 */  li      r4, 0
/* 0049C8 80009F68 80630004 */  lwz     r3, 4(r3)
/* 0049CC 80009F6C 48012725 */  bl      soundPlayBeep
/* 0049D0 80009F70 38600001 */  li      r3, 1
/* 0049D4 80009F74 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 0049D8 80009F78 48002BF0 */  b       lbl_8000CB68
lbl_80009F7C:
/* 0049DC 80009F7C 38600000 */  li      r3, 0
/* 0049E0 80009F80 48002BE8 */  b       lbl_8000CB68
glabel lbl_80009F84
/* 0049E4 80009F84 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0049E8 80009F88 7C001800 */  cmpw    r0, r3
/* 0049EC 80009F8C 41820050 */  beq     lbl_80009FDC
/* 0049F0 80009F90 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0049F4 80009F94 3C7F0001 */  addis   r3, r31, 1
/* 0049F8 80009F98 3863E550 */  addi    r3, r3, -6832
/* 0049FC 80009F9C 38810080 */  addi    r4, r1, 0x80
/* 004A00 80009FA0 480A8A95 */  bl      DVDOpen
/* 004A04 80009FA4 2C030001 */  cmpwi   r3, 1
/* 004A08 80009FA8 40820024 */  bne     lbl_80009FCC
/* 004A0C 80009FAC 80AD8014 */  lwz     r5, gmsg_ld04Size@sda21(r13)
/* 004A10 80009FB0 38610080 */  addi    r3, r1, 0x80
/* 004A14 80009FB4 389E01A0 */  addi    r4, r30, 0x1a0
/* 004A18 80009FB8 3805001F */  addi    r0, r5, 0x1f
/* 004A1C 80009FBC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 004A20 80009FC0 38C00000 */  li      r6, 0
/* 004A24 80009FC4 38E00000 */  li      r7, 0
/* 004A28 80009FC8 48004CFD */  bl      simulatorDVDRead
lbl_80009FCC:
/* 004A2C 80009FCC 38610080 */  addi    r3, r1, 0x80
/* 004A30 80009FD0 480A8B2D */  bl      DVDClose
/* 004A34 80009FD4 387E01A0 */  addi    r3, r30, 0x1a0
/* 004A38 80009FD8 48005049 */  bl      simulatorUnpackTexPalette
lbl_80009FDC:
/* 004A3C 80009FDC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 004A40 80009FE0 3C7F0001 */  addis   r3, r31, 1
/* 004A44 80009FE4 3B63D248 */  addi    r27, r3, -11704
/* 004A48 80009FE8 80E40000 */  lwz     r7, 0(r4)
/* 004A4C 80009FEC 3B83DE08 */  addi    r28, r3, -8696
/* 004A50 80009FF0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 004A54 80009FF4 3CDF0001 */  addis   r6, r31, 1
/* 004A58 80009FF8 A0070002 */  lhz     r0, 2(r7)
/* 004A5C 80009FFC 81030000 */  lwz     r8, 0(r3)
/* 004A60 8000A000 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 004A64 8000A004 7C040E70 */  srawi   r4, r0, 1
/* 004A68 8000A008 A0070000 */  lhz     r0, 0(r7)
/* 004A6C 8000A00C 7C840194 */  addze   r4, r4
/* 004A70 8000A010 80BB0000 */  lwz     r5, 0(r27)
/* 004A74 8000A014 208400A0 */  subfic  r4, r4, 0xa0
/* 004A78 8000A018 7C000E70 */  srawi   r0, r0, 1
/* 004A7C 8000A01C A1080002 */  lhz     r8, 2(r8)
/* 004A80 8000A020 80E50000 */  lwz     r7, 0(r5)
/* 004A84 8000A024 7C000194 */  addze   r0, r0
/* 004A88 8000A028 20A00078 */  subfic  r5, r0, 0x78
/* 004A8C 8000A02C A0070000 */  lhz     r0, 0(r7)
/* 004A90 8000A030 7D070E70 */  srawi   r7, r8, 1
/* 004A94 8000A034 7CE70194 */  addze   r7, r7
/* 004A98 8000A038 20E700A0 */  subfic  r7, r7, 0xa0
/* 004A9C 8000A03C 7C000E70 */  srawi   r0, r0, 1
/* 004AA0 8000A040 7C000194 */  addze   r0, r0
/* 004AA4 8000A044 387E01A0 */  addi    r3, r30, 0x1a0
/* 004AA8 8000A048 210000B4 */  subfic  r8, r0, 0xb4
/* 004AAC 8000A04C 38C6DE00 */  addi    r6, r6, -8704
/* 004AB0 8000A050 4800353D */  bl      simulatorDrawOKImage
/* 004AB4 8000A054 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 004AB8 8000A058 2C000001 */  cmpwi   r0, 1
/* 004ABC 8000A05C 40820020 */  bne     lbl_8000A07C
/* 004AC0 8000A060 480AD02D */  bl      DEMOPadRead
/* 004AC4 8000A064 3C608013 */  lis     r3, DemoPad@ha
/* 004AC8 8000A068 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 004ACC 8000A06C 28000000 */  cmplwi  r0, 0
/* 004AD0 8000A070 4182000C */  beq     lbl_8000A07C
/* 004AD4 8000A074 38600000 */  li      r3, 0
/* 004AD8 8000A078 48002AF0 */  b       lbl_8000CB68
lbl_8000A07C:
/* 004ADC 8000A07C 38000000 */  li      r0, 0
/* 004AE0 8000A080 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 004AE4 8000A084 480AD009 */  bl      DEMOPadRead
/* 004AE8 8000A088 80BD0000 */  lwz     r5, 0(r29)
/* 004AEC 8000A08C 3CDF0001 */  addis   r6, r31, 1
/* 004AF0 8000A090 809C0000 */  lwz     r4, 0(r28)
/* 004AF4 8000A094 387E01A0 */  addi    r3, r30, 0x1a0
/* 004AF8 8000A098 80A50000 */  lwz     r5, 0(r5)
/* 004AFC 8000A09C 80E40000 */  lwz     r7, 0(r4)
/* 004B00 8000A0A0 38C6DE00 */  addi    r6, r6, -8704
/* 004B04 8000A0A4 A0050002 */  lhz     r0, 2(r5)
/* 004B08 8000A0A8 809B0000 */  lwz     r4, 0(r27)
/* 004B0C 8000A0AC 7C080E70 */  srawi   r8, r0, 1
/* 004B10 8000A0B0 A0050000 */  lhz     r0, 0(r5)
/* 004B14 8000A0B4 7D080194 */  addze   r8, r8
/* 004B18 8000A0B8 80A40000 */  lwz     r5, 0(r4)
/* 004B1C 8000A0BC 208800A0 */  subfic  r4, r8, 0xa0
/* 004B20 8000A0C0 A0E70002 */  lhz     r7, 2(r7)
/* 004B24 8000A0C4 7C080E70 */  srawi   r8, r0, 1
/* 004B28 8000A0C8 A0050000 */  lhz     r0, 0(r5)
/* 004B2C 8000A0CC 7D080194 */  addze   r8, r8
/* 004B30 8000A0D0 20A80078 */  subfic  r5, r8, 0x78
/* 004B34 8000A0D4 7CE70E70 */  srawi   r7, r7, 1
/* 004B38 8000A0D8 7CE70194 */  addze   r7, r7
/* 004B3C 8000A0DC 20E700A0 */  subfic  r7, r7, 0xa0
/* 004B40 8000A0E0 7C000E70 */  srawi   r0, r0, 1
/* 004B44 8000A0E4 7C000194 */  addze   r0, r0
/* 004B48 8000A0E8 210000B4 */  subfic  r8, r0, 0xb4
/* 004B4C 8000A0EC 480034A1 */  bl      simulatorDrawOKImage
/* 004B50 8000A0F0 3C608013 */  lis     r3, DemoPad@ha
/* 004B54 8000A0F4 38632758 */  addi    r3, r3, DemoPad@l
/* 004B58 8000A0F8 8803000A */  lbz     r0, 0xa(r3)
/* 004B5C 8000A0FC 7C000775 */  extsb.  r0, r0
/* 004B60 8000A100 4082002C */  bne     lbl_8000A12C
/* 004B64 8000A104 A0030000 */  lhz     r0, 0(r3)
/* 004B68 8000A108 70001100 */  andi.   r0, r0, 0x1100
/* 004B6C 8000A10C 41820020 */  beq     lbl_8000A12C
/* 004B70 8000A110 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 004B74 8000A114 38800000 */  li      r4, 0
/* 004B78 8000A118 80630004 */  lwz     r3, 4(r3)
/* 004B7C 8000A11C 48012575 */  bl      soundPlayBeep
/* 004B80 8000A120 38600001 */  li      r3, 1
/* 004B84 8000A124 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 004B88 8000A128 48002A40 */  b       lbl_8000CB68
lbl_8000A12C:
/* 004B8C 8000A12C 38600000 */  li      r3, 0
/* 004B90 8000A130 48002A38 */  b       lbl_8000CB68
glabel lbl_8000A134
/* 004B94 8000A134 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 004B98 8000A138 7C001800 */  cmpw    r0, r3
/* 004B9C 8000A13C 41820050 */  beq     lbl_8000A18C
/* 004BA0 8000A140 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 004BA4 8000A144 3C7F0001 */  addis   r3, r31, 1
/* 004BA8 8000A148 3863E564 */  addi    r3, r3, -6812
/* 004BAC 8000A14C 38810080 */  addi    r4, r1, 0x80
/* 004BB0 8000A150 480A88E5 */  bl      DVDOpen
/* 004BB4 8000A154 2C030001 */  cmpwi   r3, 1
/* 004BB8 8000A158 40820024 */  bne     lbl_8000A17C
/* 004BBC 8000A15C 80AD8018 */  lwz     r5, gmsg_ld05_1Size@sda21(r13)
/* 004BC0 8000A160 38610080 */  addi    r3, r1, 0x80
/* 004BC4 8000A164 389E01A0 */  addi    r4, r30, 0x1a0
/* 004BC8 8000A168 3805001F */  addi    r0, r5, 0x1f
/* 004BCC 8000A16C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 004BD0 8000A170 38C00000 */  li      r6, 0
/* 004BD4 8000A174 38E00000 */  li      r7, 0
/* 004BD8 8000A178 48004B4D */  bl      simulatorDVDRead
lbl_8000A17C:
/* 004BDC 8000A17C 38610080 */  addi    r3, r1, 0x80
/* 004BE0 8000A180 480A897D */  bl      DVDClose
/* 004BE4 8000A184 387E01A0 */  addi    r3, r30, 0x1a0
/* 004BE8 8000A188 48004E99 */  bl      simulatorUnpackTexPalette
lbl_8000A18C:
/* 004BEC 8000A18C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 004BF0 8000A190 3C7F0001 */  addis   r3, r31, 1
/* 004BF4 8000A194 3B63D248 */  addi    r27, r3, -11704
/* 004BF8 8000A198 80E40000 */  lwz     r7, 0(r4)
/* 004BFC 8000A19C 3B83DE08 */  addi    r28, r3, -8696
/* 004C00 8000A1A0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 004C04 8000A1A4 3CDF0001 */  addis   r6, r31, 1
/* 004C08 8000A1A8 A0070002 */  lhz     r0, 2(r7)
/* 004C0C 8000A1AC 81030000 */  lwz     r8, 0(r3)
/* 004C10 8000A1B0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 004C14 8000A1B4 7C040E70 */  srawi   r4, r0, 1
/* 004C18 8000A1B8 A0070000 */  lhz     r0, 0(r7)
/* 004C1C 8000A1BC 7C840194 */  addze   r4, r4
/* 004C20 8000A1C0 80BB0000 */  lwz     r5, 0(r27)
/* 004C24 8000A1C4 208400A0 */  subfic  r4, r4, 0xa0
/* 004C28 8000A1C8 7C000E70 */  srawi   r0, r0, 1
/* 004C2C 8000A1CC A1080002 */  lhz     r8, 2(r8)
/* 004C30 8000A1D0 80E50000 */  lwz     r7, 0(r5)
/* 004C34 8000A1D4 7C000194 */  addze   r0, r0
/* 004C38 8000A1D8 20A00078 */  subfic  r5, r0, 0x78
/* 004C3C 8000A1DC A0070000 */  lhz     r0, 0(r7)
/* 004C40 8000A1E0 7D070E70 */  srawi   r7, r8, 1
/* 004C44 8000A1E4 7CE70194 */  addze   r7, r7
/* 004C48 8000A1E8 20E700A0 */  subfic  r7, r7, 0xa0
/* 004C4C 8000A1EC 7C000E70 */  srawi   r0, r0, 1
/* 004C50 8000A1F0 7C000194 */  addze   r0, r0
/* 004C54 8000A1F4 387E01A0 */  addi    r3, r30, 0x1a0
/* 004C58 8000A1F8 210000B4 */  subfic  r8, r0, 0xb4
/* 004C5C 8000A1FC 38C6DE00 */  addi    r6, r6, -8704
/* 004C60 8000A200 4800338D */  bl      simulatorDrawOKImage
/* 004C64 8000A204 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 004C68 8000A208 2C000001 */  cmpwi   r0, 1
/* 004C6C 8000A20C 40820020 */  bne     lbl_8000A22C
/* 004C70 8000A210 480ACE7D */  bl      DEMOPadRead
/* 004C74 8000A214 3C608013 */  lis     r3, DemoPad@ha
/* 004C78 8000A218 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 004C7C 8000A21C 28000000 */  cmplwi  r0, 0
/* 004C80 8000A220 4182000C */  beq     lbl_8000A22C
/* 004C84 8000A224 38600000 */  li      r3, 0
/* 004C88 8000A228 48002940 */  b       lbl_8000CB68
lbl_8000A22C:
/* 004C8C 8000A22C 38000000 */  li      r0, 0
/* 004C90 8000A230 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 004C94 8000A234 480ACE59 */  bl      DEMOPadRead
/* 004C98 8000A238 80BD0000 */  lwz     r5, 0(r29)
/* 004C9C 8000A23C 3CDF0001 */  addis   r6, r31, 1
/* 004CA0 8000A240 809C0000 */  lwz     r4, 0(r28)
/* 004CA4 8000A244 387E01A0 */  addi    r3, r30, 0x1a0
/* 004CA8 8000A248 80A50000 */  lwz     r5, 0(r5)
/* 004CAC 8000A24C 80E40000 */  lwz     r7, 0(r4)
/* 004CB0 8000A250 38C6DE00 */  addi    r6, r6, -8704
/* 004CB4 8000A254 A0050002 */  lhz     r0, 2(r5)
/* 004CB8 8000A258 809B0000 */  lwz     r4, 0(r27)
/* 004CBC 8000A25C 7C080E70 */  srawi   r8, r0, 1
/* 004CC0 8000A260 A0050000 */  lhz     r0, 0(r5)
/* 004CC4 8000A264 7D080194 */  addze   r8, r8
/* 004CC8 8000A268 80A40000 */  lwz     r5, 0(r4)
/* 004CCC 8000A26C 208800A0 */  subfic  r4, r8, 0xa0
/* 004CD0 8000A270 A0E70002 */  lhz     r7, 2(r7)
/* 004CD4 8000A274 7C080E70 */  srawi   r8, r0, 1
/* 004CD8 8000A278 A0050000 */  lhz     r0, 0(r5)
/* 004CDC 8000A27C 7D080194 */  addze   r8, r8
/* 004CE0 8000A280 20A80078 */  subfic  r5, r8, 0x78
/* 004CE4 8000A284 7CE70E70 */  srawi   r7, r7, 1
/* 004CE8 8000A288 7CE70194 */  addze   r7, r7
/* 004CEC 8000A28C 20E700A0 */  subfic  r7, r7, 0xa0
/* 004CF0 8000A290 7C000E70 */  srawi   r0, r0, 1
/* 004CF4 8000A294 7C000194 */  addze   r0, r0
/* 004CF8 8000A298 210000B4 */  subfic  r8, r0, 0xb4
/* 004CFC 8000A29C 480032F1 */  bl      simulatorDrawOKImage
/* 004D00 8000A2A0 3C608013 */  lis     r3, DemoPad@ha
/* 004D04 8000A2A4 38632758 */  addi    r3, r3, DemoPad@l
/* 004D08 8000A2A8 8803000A */  lbz     r0, 0xa(r3)
/* 004D0C 8000A2AC 7C000775 */  extsb.  r0, r0
/* 004D10 8000A2B0 4082002C */  bne     lbl_8000A2DC
/* 004D14 8000A2B4 A0030000 */  lhz     r0, 0(r3)
/* 004D18 8000A2B8 70001100 */  andi.   r0, r0, 0x1100
/* 004D1C 8000A2BC 41820020 */  beq     lbl_8000A2DC
/* 004D20 8000A2C0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 004D24 8000A2C4 38800000 */  li      r4, 0
/* 004D28 8000A2C8 80630004 */  lwz     r3, 4(r3)
/* 004D2C 8000A2CC 480123C5 */  bl      soundPlayBeep
/* 004D30 8000A2D0 38600001 */  li      r3, 1
/* 004D34 8000A2D4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 004D38 8000A2D8 48002890 */  b       lbl_8000CB68
lbl_8000A2DC:
/* 004D3C 8000A2DC 38600000 */  li      r3, 0
/* 004D40 8000A2E0 48002888 */  b       lbl_8000CB68
glabel lbl_8000A2E4
/* 004D44 8000A2E4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 004D48 8000A2E8 7C001800 */  cmpw    r0, r3
/* 004D4C 8000A2EC 41820050 */  beq     lbl_8000A33C
/* 004D50 8000A2F0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 004D54 8000A2F4 3C7F0001 */  addis   r3, r31, 1
/* 004D58 8000A2F8 3863E578 */  addi    r3, r3, -6792
/* 004D5C 8000A2FC 38810080 */  addi    r4, r1, 0x80
/* 004D60 8000A300 480A8735 */  bl      DVDOpen
/* 004D64 8000A304 2C030001 */  cmpwi   r3, 1
/* 004D68 8000A308 40820024 */  bne     lbl_8000A32C
/* 004D6C 8000A30C 80AD8020 */  lwz     r5, gmsg_ld06_1Size@sda21(r13)
/* 004D70 8000A310 38610080 */  addi    r3, r1, 0x80
/* 004D74 8000A314 389E01A0 */  addi    r4, r30, 0x1a0
/* 004D78 8000A318 3805001F */  addi    r0, r5, 0x1f
/* 004D7C 8000A31C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 004D80 8000A320 38C00000 */  li      r6, 0
/* 004D84 8000A324 38E00000 */  li      r7, 0
/* 004D88 8000A328 4800499D */  bl      simulatorDVDRead
lbl_8000A32C:
/* 004D8C 8000A32C 38610080 */  addi    r3, r1, 0x80
/* 004D90 8000A330 480A87CD */  bl      DVDClose
/* 004D94 8000A334 387E01A0 */  addi    r3, r30, 0x1a0
/* 004D98 8000A338 48004CE9 */  bl      simulatorUnpackTexPalette
lbl_8000A33C:
/* 004D9C 8000A33C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 004DA0 8000A340 3C7F0001 */  addis   r3, r31, 1
/* 004DA4 8000A344 3B63D248 */  addi    r27, r3, -11704
/* 004DA8 8000A348 80E40000 */  lwz     r7, 0(r4)
/* 004DAC 8000A34C 3B83DE08 */  addi    r28, r3, -8696
/* 004DB0 8000A350 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 004DB4 8000A354 3CDF0001 */  addis   r6, r31, 1
/* 004DB8 8000A358 A0070002 */  lhz     r0, 2(r7)
/* 004DBC 8000A35C 81030000 */  lwz     r8, 0(r3)
/* 004DC0 8000A360 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 004DC4 8000A364 7C040E70 */  srawi   r4, r0, 1
/* 004DC8 8000A368 A0070000 */  lhz     r0, 0(r7)
/* 004DCC 8000A36C 7C840194 */  addze   r4, r4
/* 004DD0 8000A370 80BB0000 */  lwz     r5, 0(r27)
/* 004DD4 8000A374 208400A0 */  subfic  r4, r4, 0xa0
/* 004DD8 8000A378 7C000E70 */  srawi   r0, r0, 1
/* 004DDC 8000A37C A1080002 */  lhz     r8, 2(r8)
/* 004DE0 8000A380 80E50000 */  lwz     r7, 0(r5)
/* 004DE4 8000A384 7C000194 */  addze   r0, r0
/* 004DE8 8000A388 20A00078 */  subfic  r5, r0, 0x78
/* 004DEC 8000A38C A0070000 */  lhz     r0, 0(r7)
/* 004DF0 8000A390 7D070E70 */  srawi   r7, r8, 1
/* 004DF4 8000A394 7CE70194 */  addze   r7, r7
/* 004DF8 8000A398 20E700A0 */  subfic  r7, r7, 0xa0
/* 004DFC 8000A39C 7C000E70 */  srawi   r0, r0, 1
/* 004E00 8000A3A0 7C000194 */  addze   r0, r0
/* 004E04 8000A3A4 387E01A0 */  addi    r3, r30, 0x1a0
/* 004E08 8000A3A8 210000B4 */  subfic  r8, r0, 0xb4
/* 004E0C 8000A3AC 38C6DE00 */  addi    r6, r6, -8704
/* 004E10 8000A3B0 480031DD */  bl      simulatorDrawOKImage
/* 004E14 8000A3B4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 004E18 8000A3B8 2C000001 */  cmpwi   r0, 1
/* 004E1C 8000A3BC 40820020 */  bne     lbl_8000A3DC
/* 004E20 8000A3C0 480ACCCD */  bl      DEMOPadRead
/* 004E24 8000A3C4 3C608013 */  lis     r3, DemoPad@ha
/* 004E28 8000A3C8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 004E2C 8000A3CC 28000000 */  cmplwi  r0, 0
/* 004E30 8000A3D0 4182000C */  beq     lbl_8000A3DC
/* 004E34 8000A3D4 38600000 */  li      r3, 0
/* 004E38 8000A3D8 48002790 */  b       lbl_8000CB68
lbl_8000A3DC:
/* 004E3C 8000A3DC 38000000 */  li      r0, 0
/* 004E40 8000A3E0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 004E44 8000A3E4 480ACCA9 */  bl      DEMOPadRead
/* 004E48 8000A3E8 80BD0000 */  lwz     r5, 0(r29)
/* 004E4C 8000A3EC 3CDF0001 */  addis   r6, r31, 1
/* 004E50 8000A3F0 809C0000 */  lwz     r4, 0(r28)
/* 004E54 8000A3F4 387E01A0 */  addi    r3, r30, 0x1a0
/* 004E58 8000A3F8 80A50000 */  lwz     r5, 0(r5)
/* 004E5C 8000A3FC 80E40000 */  lwz     r7, 0(r4)
/* 004E60 8000A400 38C6DE00 */  addi    r6, r6, -8704
/* 004E64 8000A404 A0050002 */  lhz     r0, 2(r5)
/* 004E68 8000A408 809B0000 */  lwz     r4, 0(r27)
/* 004E6C 8000A40C 7C080E70 */  srawi   r8, r0, 1
/* 004E70 8000A410 A0050000 */  lhz     r0, 0(r5)
/* 004E74 8000A414 7D080194 */  addze   r8, r8
/* 004E78 8000A418 80A40000 */  lwz     r5, 0(r4)
/* 004E7C 8000A41C 208800A0 */  subfic  r4, r8, 0xa0
/* 004E80 8000A420 A0E70002 */  lhz     r7, 2(r7)
/* 004E84 8000A424 7C080E70 */  srawi   r8, r0, 1
/* 004E88 8000A428 A0050000 */  lhz     r0, 0(r5)
/* 004E8C 8000A42C 7D080194 */  addze   r8, r8
/* 004E90 8000A430 20A80078 */  subfic  r5, r8, 0x78
/* 004E94 8000A434 7CE70E70 */  srawi   r7, r7, 1
/* 004E98 8000A438 7CE70194 */  addze   r7, r7
/* 004E9C 8000A43C 20E700A0 */  subfic  r7, r7, 0xa0
/* 004EA0 8000A440 7C000E70 */  srawi   r0, r0, 1
/* 004EA4 8000A444 7C000194 */  addze   r0, r0
/* 004EA8 8000A448 210000B4 */  subfic  r8, r0, 0xb4
/* 004EAC 8000A44C 48003141 */  bl      simulatorDrawOKImage
/* 004EB0 8000A450 3C608013 */  lis     r3, DemoPad@ha
/* 004EB4 8000A454 38632758 */  addi    r3, r3, DemoPad@l
/* 004EB8 8000A458 8803000A */  lbz     r0, 0xa(r3)
/* 004EBC 8000A45C 7C000775 */  extsb.  r0, r0
/* 004EC0 8000A460 4082002C */  bne     lbl_8000A48C
/* 004EC4 8000A464 A0030000 */  lhz     r0, 0(r3)
/* 004EC8 8000A468 70001100 */  andi.   r0, r0, 0x1100
/* 004ECC 8000A46C 41820020 */  beq     lbl_8000A48C
/* 004ED0 8000A470 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 004ED4 8000A474 38800000 */  li      r4, 0
/* 004ED8 8000A478 80630004 */  lwz     r3, 4(r3)
/* 004EDC 8000A47C 48012215 */  bl      soundPlayBeep
/* 004EE0 8000A480 38600001 */  li      r3, 1
/* 004EE4 8000A484 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 004EE8 8000A488 480026E0 */  b       lbl_8000CB68
lbl_8000A48C:
/* 004EEC 8000A48C 38600000 */  li      r3, 0
/* 004EF0 8000A490 480026D8 */  b       lbl_8000CB68
glabel lbl_8000A494
/* 004EF4 8000A494 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 004EF8 8000A498 7C001800 */  cmpw    r0, r3
/* 004EFC 8000A49C 41820050 */  beq     lbl_8000A4EC
/* 004F00 8000A4A0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 004F04 8000A4A4 3C7F0001 */  addis   r3, r31, 1
/* 004F08 8000A4A8 3863E58C */  addi    r3, r3, -6772
/* 004F0C 8000A4AC 38810080 */  addi    r4, r1, 0x80
/* 004F10 8000A4B0 480A8585 */  bl      DVDOpen
/* 004F14 8000A4B4 2C030001 */  cmpwi   r3, 1
/* 004F18 8000A4B8 40820024 */  bne     lbl_8000A4DC
/* 004F1C 8000A4BC 80AD8024 */  lwz     r5, gmsg_ld06_2Size@sda21(r13)
/* 004F20 8000A4C0 38610080 */  addi    r3, r1, 0x80
/* 004F24 8000A4C4 389E01A0 */  addi    r4, r30, 0x1a0
/* 004F28 8000A4C8 3805001F */  addi    r0, r5, 0x1f
/* 004F2C 8000A4CC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 004F30 8000A4D0 38C00000 */  li      r6, 0
/* 004F34 8000A4D4 38E00000 */  li      r7, 0
/* 004F38 8000A4D8 480047ED */  bl      simulatorDVDRead
lbl_8000A4DC:
/* 004F3C 8000A4DC 38610080 */  addi    r3, r1, 0x80
/* 004F40 8000A4E0 480A861D */  bl      DVDClose
/* 004F44 8000A4E4 387E01A0 */  addi    r3, r30, 0x1a0
/* 004F48 8000A4E8 48004B39 */  bl      simulatorUnpackTexPalette
lbl_8000A4EC:
/* 004F4C 8000A4EC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 004F50 8000A4F0 3C7F0001 */  addis   r3, r31, 1
/* 004F54 8000A4F4 3B63D248 */  addi    r27, r3, -11704
/* 004F58 8000A4F8 80E40000 */  lwz     r7, 0(r4)
/* 004F5C 8000A4FC 3B83DE08 */  addi    r28, r3, -8696
/* 004F60 8000A500 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 004F64 8000A504 3CDF0001 */  addis   r6, r31, 1
/* 004F68 8000A508 A0070002 */  lhz     r0, 2(r7)
/* 004F6C 8000A50C 81030000 */  lwz     r8, 0(r3)
/* 004F70 8000A510 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 004F74 8000A514 7C040E70 */  srawi   r4, r0, 1
/* 004F78 8000A518 A0070000 */  lhz     r0, 0(r7)
/* 004F7C 8000A51C 7C840194 */  addze   r4, r4
/* 004F80 8000A520 80BB0000 */  lwz     r5, 0(r27)
/* 004F84 8000A524 208400A0 */  subfic  r4, r4, 0xa0
/* 004F88 8000A528 7C000E70 */  srawi   r0, r0, 1
/* 004F8C 8000A52C A1080002 */  lhz     r8, 2(r8)
/* 004F90 8000A530 80E50000 */  lwz     r7, 0(r5)
/* 004F94 8000A534 7C000194 */  addze   r0, r0
/* 004F98 8000A538 20A00078 */  subfic  r5, r0, 0x78
/* 004F9C 8000A53C A0070000 */  lhz     r0, 0(r7)
/* 004FA0 8000A540 7D070E70 */  srawi   r7, r8, 1
/* 004FA4 8000A544 7CE70194 */  addze   r7, r7
/* 004FA8 8000A548 20E700A0 */  subfic  r7, r7, 0xa0
/* 004FAC 8000A54C 7C000E70 */  srawi   r0, r0, 1
/* 004FB0 8000A550 7C000194 */  addze   r0, r0
/* 004FB4 8000A554 387E01A0 */  addi    r3, r30, 0x1a0
/* 004FB8 8000A558 210000B4 */  subfic  r8, r0, 0xb4
/* 004FBC 8000A55C 38C6DE00 */  addi    r6, r6, -8704
/* 004FC0 8000A560 4800302D */  bl      simulatorDrawOKImage
/* 004FC4 8000A564 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 004FC8 8000A568 2C000001 */  cmpwi   r0, 1
/* 004FCC 8000A56C 40820020 */  bne     lbl_8000A58C
/* 004FD0 8000A570 480ACB1D */  bl      DEMOPadRead
/* 004FD4 8000A574 3C608013 */  lis     r3, DemoPad@ha
/* 004FD8 8000A578 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 004FDC 8000A57C 28000000 */  cmplwi  r0, 0
/* 004FE0 8000A580 4182000C */  beq     lbl_8000A58C
/* 004FE4 8000A584 38600000 */  li      r3, 0
/* 004FE8 8000A588 480025E0 */  b       lbl_8000CB68
lbl_8000A58C:
/* 004FEC 8000A58C 38000000 */  li      r0, 0
/* 004FF0 8000A590 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 004FF4 8000A594 480ACAF9 */  bl      DEMOPadRead
/* 004FF8 8000A598 80BD0000 */  lwz     r5, 0(r29)
/* 004FFC 8000A59C 3CDF0001 */  addis   r6, r31, 1
/* 005000 8000A5A0 809C0000 */  lwz     r4, 0(r28)
/* 005004 8000A5A4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005008 8000A5A8 80A50000 */  lwz     r5, 0(r5)
/* 00500C 8000A5AC 80E40000 */  lwz     r7, 0(r4)
/* 005010 8000A5B0 38C6DE00 */  addi    r6, r6, -8704
/* 005014 8000A5B4 A0050002 */  lhz     r0, 2(r5)
/* 005018 8000A5B8 809B0000 */  lwz     r4, 0(r27)
/* 00501C 8000A5BC 7C080E70 */  srawi   r8, r0, 1
/* 005020 8000A5C0 A0050000 */  lhz     r0, 0(r5)
/* 005024 8000A5C4 7D080194 */  addze   r8, r8
/* 005028 8000A5C8 80A40000 */  lwz     r5, 0(r4)
/* 00502C 8000A5CC 208800A0 */  subfic  r4, r8, 0xa0
/* 005030 8000A5D0 A0E70002 */  lhz     r7, 2(r7)
/* 005034 8000A5D4 7C080E70 */  srawi   r8, r0, 1
/* 005038 8000A5D8 A0050000 */  lhz     r0, 0(r5)
/* 00503C 8000A5DC 7D080194 */  addze   r8, r8
/* 005040 8000A5E0 20A80078 */  subfic  r5, r8, 0x78
/* 005044 8000A5E4 7CE70E70 */  srawi   r7, r7, 1
/* 005048 8000A5E8 7CE70194 */  addze   r7, r7
/* 00504C 8000A5EC 20E700A0 */  subfic  r7, r7, 0xa0
/* 005050 8000A5F0 7C000E70 */  srawi   r0, r0, 1
/* 005054 8000A5F4 7C000194 */  addze   r0, r0
/* 005058 8000A5F8 210000B4 */  subfic  r8, r0, 0xb4
/* 00505C 8000A5FC 48002F91 */  bl      simulatorDrawOKImage
/* 005060 8000A600 3C608013 */  lis     r3, DemoPad@ha
/* 005064 8000A604 38632758 */  addi    r3, r3, DemoPad@l
/* 005068 8000A608 8803000A */  lbz     r0, 0xa(r3)
/* 00506C 8000A60C 7C000775 */  extsb.  r0, r0
/* 005070 8000A610 4082002C */  bne     lbl_8000A63C
/* 005074 8000A614 A0030000 */  lhz     r0, 0(r3)
/* 005078 8000A618 70001100 */  andi.   r0, r0, 0x1100
/* 00507C 8000A61C 41820020 */  beq     lbl_8000A63C
/* 005080 8000A620 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 005084 8000A624 38800000 */  li      r4, 0
/* 005088 8000A628 80630004 */  lwz     r3, 4(r3)
/* 00508C 8000A62C 48012065 */  bl      soundPlayBeep
/* 005090 8000A630 38600001 */  li      r3, 1
/* 005094 8000A634 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 005098 8000A638 48002530 */  b       lbl_8000CB68
lbl_8000A63C:
/* 00509C 8000A63C 38600000 */  li      r3, 0
/* 0050A0 8000A640 48002528 */  b       lbl_8000CB68
glabel lbl_8000A644
/* 0050A4 8000A644 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0050A8 8000A648 7C001800 */  cmpw    r0, r3
/* 0050AC 8000A64C 41820050 */  beq     lbl_8000A69C
/* 0050B0 8000A650 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0050B4 8000A654 3C7F0001 */  addis   r3, r31, 1
/* 0050B8 8000A658 3863E5A0 */  addi    r3, r3, -6752
/* 0050BC 8000A65C 38810080 */  addi    r4, r1, 0x80
/* 0050C0 8000A660 480A83D5 */  bl      DVDOpen
/* 0050C4 8000A664 2C030001 */  cmpwi   r3, 1
/* 0050C8 8000A668 40820024 */  bne     lbl_8000A68C
/* 0050CC 8000A66C 80AD8028 */  lwz     r5, gmsg_ld06_3Size@sda21(r13)
/* 0050D0 8000A670 38610080 */  addi    r3, r1, 0x80
/* 0050D4 8000A674 389E01A0 */  addi    r4, r30, 0x1a0
/* 0050D8 8000A678 3805001F */  addi    r0, r5, 0x1f
/* 0050DC 8000A67C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0050E0 8000A680 38C00000 */  li      r6, 0
/* 0050E4 8000A684 38E00000 */  li      r7, 0
/* 0050E8 8000A688 4800463D */  bl      simulatorDVDRead
lbl_8000A68C:
/* 0050EC 8000A68C 38610080 */  addi    r3, r1, 0x80
/* 0050F0 8000A690 480A846D */  bl      DVDClose
/* 0050F4 8000A694 387E01A0 */  addi    r3, r30, 0x1a0
/* 0050F8 8000A698 48004989 */  bl      simulatorUnpackTexPalette
lbl_8000A69C:
/* 0050FC 8000A69C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 005100 8000A6A0 3C7F0001 */  addis   r3, r31, 1
/* 005104 8000A6A4 3B63D248 */  addi    r27, r3, -11704
/* 005108 8000A6A8 80E40000 */  lwz     r7, 0(r4)
/* 00510C 8000A6AC 3B83DE08 */  addi    r28, r3, -8696
/* 005110 8000A6B0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 005114 8000A6B4 3CDF0001 */  addis   r6, r31, 1
/* 005118 8000A6B8 A0070002 */  lhz     r0, 2(r7)
/* 00511C 8000A6BC 81030000 */  lwz     r8, 0(r3)
/* 005120 8000A6C0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 005124 8000A6C4 7C040E70 */  srawi   r4, r0, 1
/* 005128 8000A6C8 A0070000 */  lhz     r0, 0(r7)
/* 00512C 8000A6CC 7C840194 */  addze   r4, r4
/* 005130 8000A6D0 80BB0000 */  lwz     r5, 0(r27)
/* 005134 8000A6D4 208400A0 */  subfic  r4, r4, 0xa0
/* 005138 8000A6D8 7C000E70 */  srawi   r0, r0, 1
/* 00513C 8000A6DC A1080002 */  lhz     r8, 2(r8)
/* 005140 8000A6E0 80E50000 */  lwz     r7, 0(r5)
/* 005144 8000A6E4 7C000194 */  addze   r0, r0
/* 005148 8000A6E8 20A00078 */  subfic  r5, r0, 0x78
/* 00514C 8000A6EC A0070000 */  lhz     r0, 0(r7)
/* 005150 8000A6F0 7D070E70 */  srawi   r7, r8, 1
/* 005154 8000A6F4 7CE70194 */  addze   r7, r7
/* 005158 8000A6F8 20E700A0 */  subfic  r7, r7, 0xa0
/* 00515C 8000A6FC 7C000E70 */  srawi   r0, r0, 1
/* 005160 8000A700 7C000194 */  addze   r0, r0
/* 005164 8000A704 387E01A0 */  addi    r3, r30, 0x1a0
/* 005168 8000A708 210000B4 */  subfic  r8, r0, 0xb4
/* 00516C 8000A70C 38C6DE00 */  addi    r6, r6, -8704
/* 005170 8000A710 48002E7D */  bl      simulatorDrawOKImage
/* 005174 8000A714 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 005178 8000A718 2C000001 */  cmpwi   r0, 1
/* 00517C 8000A71C 40820020 */  bne     lbl_8000A73C
/* 005180 8000A720 480AC96D */  bl      DEMOPadRead
/* 005184 8000A724 3C608013 */  lis     r3, DemoPad@ha
/* 005188 8000A728 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00518C 8000A72C 28000000 */  cmplwi  r0, 0
/* 005190 8000A730 4182000C */  beq     lbl_8000A73C
/* 005194 8000A734 38600000 */  li      r3, 0
/* 005198 8000A738 48002430 */  b       lbl_8000CB68
lbl_8000A73C:
/* 00519C 8000A73C 38000000 */  li      r0, 0
/* 0051A0 8000A740 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 0051A4 8000A744 480AC949 */  bl      DEMOPadRead
/* 0051A8 8000A748 80BD0000 */  lwz     r5, 0(r29)
/* 0051AC 8000A74C 3CDF0001 */  addis   r6, r31, 1
/* 0051B0 8000A750 809C0000 */  lwz     r4, 0(r28)
/* 0051B4 8000A754 387E01A0 */  addi    r3, r30, 0x1a0
/* 0051B8 8000A758 80A50000 */  lwz     r5, 0(r5)
/* 0051BC 8000A75C 80E40000 */  lwz     r7, 0(r4)
/* 0051C0 8000A760 38C6DE00 */  addi    r6, r6, -8704
/* 0051C4 8000A764 A0050002 */  lhz     r0, 2(r5)
/* 0051C8 8000A768 809B0000 */  lwz     r4, 0(r27)
/* 0051CC 8000A76C 7C080E70 */  srawi   r8, r0, 1
/* 0051D0 8000A770 A0050000 */  lhz     r0, 0(r5)
/* 0051D4 8000A774 7D080194 */  addze   r8, r8
/* 0051D8 8000A778 80A40000 */  lwz     r5, 0(r4)
/* 0051DC 8000A77C 208800A0 */  subfic  r4, r8, 0xa0
/* 0051E0 8000A780 A0E70002 */  lhz     r7, 2(r7)
/* 0051E4 8000A784 7C080E70 */  srawi   r8, r0, 1
/* 0051E8 8000A788 A0050000 */  lhz     r0, 0(r5)
/* 0051EC 8000A78C 7D080194 */  addze   r8, r8
/* 0051F0 8000A790 20A80078 */  subfic  r5, r8, 0x78
/* 0051F4 8000A794 7CE70E70 */  srawi   r7, r7, 1
/* 0051F8 8000A798 7CE70194 */  addze   r7, r7
/* 0051FC 8000A79C 20E700A0 */  subfic  r7, r7, 0xa0
/* 005200 8000A7A0 7C000E70 */  srawi   r0, r0, 1
/* 005204 8000A7A4 7C000194 */  addze   r0, r0
/* 005208 8000A7A8 210000B4 */  subfic  r8, r0, 0xb4
/* 00520C 8000A7AC 48002DE1 */  bl      simulatorDrawOKImage
/* 005210 8000A7B0 3C608013 */  lis     r3, DemoPad@ha
/* 005214 8000A7B4 38632758 */  addi    r3, r3, DemoPad@l
/* 005218 8000A7B8 8803000A */  lbz     r0, 0xa(r3)
/* 00521C 8000A7BC 7C000775 */  extsb.  r0, r0
/* 005220 8000A7C0 4082002C */  bne     lbl_8000A7EC
/* 005224 8000A7C4 A0030000 */  lhz     r0, 0(r3)
/* 005228 8000A7C8 70001100 */  andi.   r0, r0, 0x1100
/* 00522C 8000A7CC 41820020 */  beq     lbl_8000A7EC
/* 005230 8000A7D0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 005234 8000A7D4 38800000 */  li      r4, 0
/* 005238 8000A7D8 80630004 */  lwz     r3, 4(r3)
/* 00523C 8000A7DC 48011EB5 */  bl      soundPlayBeep
/* 005240 8000A7E0 38600001 */  li      r3, 1
/* 005244 8000A7E4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 005248 8000A7E8 48002380 */  b       lbl_8000CB68
lbl_8000A7EC:
/* 00524C 8000A7EC 38600000 */  li      r3, 0
/* 005250 8000A7F0 48002378 */  b       lbl_8000CB68
glabel lbl_8000A7F4
/* 005254 8000A7F4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 005258 8000A7F8 7C001800 */  cmpw    r0, r3
/* 00525C 8000A7FC 41820050 */  beq     lbl_8000A84C
/* 005260 8000A800 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 005264 8000A804 3C7F0001 */  addis   r3, r31, 1
/* 005268 8000A808 3863E5B4 */  addi    r3, r3, -6732
/* 00526C 8000A80C 38810080 */  addi    r4, r1, 0x80
/* 005270 8000A810 480A8225 */  bl      DVDOpen
/* 005274 8000A814 2C030001 */  cmpwi   r3, 1
/* 005278 8000A818 40820024 */  bne     lbl_8000A83C
/* 00527C 8000A81C 80AD803C */  lwz     r5, gmsg_gf03Size@sda21(r13)
/* 005280 8000A820 38610080 */  addi    r3, r1, 0x80
/* 005284 8000A824 389E01A0 */  addi    r4, r30, 0x1a0
/* 005288 8000A828 3805001F */  addi    r0, r5, 0x1f
/* 00528C 8000A82C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 005290 8000A830 38C00000 */  li      r6, 0
/* 005294 8000A834 38E00000 */  li      r7, 0
/* 005298 8000A838 4800448D */  bl      simulatorDVDRead
lbl_8000A83C:
/* 00529C 8000A83C 38610080 */  addi    r3, r1, 0x80
/* 0052A0 8000A840 480A82BD */  bl      DVDClose
/* 0052A4 8000A844 387E01A0 */  addi    r3, r30, 0x1a0
/* 0052A8 8000A848 480047D9 */  bl      simulatorUnpackTexPalette
lbl_8000A84C:
/* 0052AC 8000A84C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 0052B0 8000A850 3C7F0001 */  addis   r3, r31, 1
/* 0052B4 8000A854 3B63D248 */  addi    r27, r3, -11704
/* 0052B8 8000A858 80E40000 */  lwz     r7, 0(r4)
/* 0052BC 8000A85C 3B83DE08 */  addi    r28, r3, -8696
/* 0052C0 8000A860 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 0052C4 8000A864 3CDF0001 */  addis   r6, r31, 1
/* 0052C8 8000A868 A0070002 */  lhz     r0, 2(r7)
/* 0052CC 8000A86C 81030000 */  lwz     r8, 0(r3)
/* 0052D0 8000A870 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 0052D4 8000A874 7C040E70 */  srawi   r4, r0, 1
/* 0052D8 8000A878 A0070000 */  lhz     r0, 0(r7)
/* 0052DC 8000A87C 7C840194 */  addze   r4, r4
/* 0052E0 8000A880 80BB0000 */  lwz     r5, 0(r27)
/* 0052E4 8000A884 208400A0 */  subfic  r4, r4, 0xa0
/* 0052E8 8000A888 7C000E70 */  srawi   r0, r0, 1
/* 0052EC 8000A88C A1080002 */  lhz     r8, 2(r8)
/* 0052F0 8000A890 80E50000 */  lwz     r7, 0(r5)
/* 0052F4 8000A894 7C000194 */  addze   r0, r0
/* 0052F8 8000A898 20A00078 */  subfic  r5, r0, 0x78
/* 0052FC 8000A89C A0070000 */  lhz     r0, 0(r7)
/* 005300 8000A8A0 7D070E70 */  srawi   r7, r8, 1
/* 005304 8000A8A4 7CE70194 */  addze   r7, r7
/* 005308 8000A8A8 20E700A0 */  subfic  r7, r7, 0xa0
/* 00530C 8000A8AC 7C000E70 */  srawi   r0, r0, 1
/* 005310 8000A8B0 7C000194 */  addze   r0, r0
/* 005314 8000A8B4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005318 8000A8B8 210000B4 */  subfic  r8, r0, 0xb4
/* 00531C 8000A8BC 38C6DE00 */  addi    r6, r6, -8704
/* 005320 8000A8C0 48002CCD */  bl      simulatorDrawOKImage
/* 005324 8000A8C4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 005328 8000A8C8 2C000001 */  cmpwi   r0, 1
/* 00532C 8000A8CC 40820020 */  bne     lbl_8000A8EC
/* 005330 8000A8D0 480AC7BD */  bl      DEMOPadRead
/* 005334 8000A8D4 3C608013 */  lis     r3, DemoPad@ha
/* 005338 8000A8D8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00533C 8000A8DC 28000000 */  cmplwi  r0, 0
/* 005340 8000A8E0 4182000C */  beq     lbl_8000A8EC
/* 005344 8000A8E4 38600000 */  li      r3, 0
/* 005348 8000A8E8 48002280 */  b       lbl_8000CB68
lbl_8000A8EC:
/* 00534C 8000A8EC 38000000 */  li      r0, 0
/* 005350 8000A8F0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 005354 8000A8F4 480AC799 */  bl      DEMOPadRead
/* 005358 8000A8F8 80BD0000 */  lwz     r5, 0(r29)
/* 00535C 8000A8FC 3CDF0001 */  addis   r6, r31, 1
/* 005360 8000A900 809C0000 */  lwz     r4, 0(r28)
/* 005364 8000A904 387E01A0 */  addi    r3, r30, 0x1a0
/* 005368 8000A908 80A50000 */  lwz     r5, 0(r5)
/* 00536C 8000A90C 80E40000 */  lwz     r7, 0(r4)
/* 005370 8000A910 38C6DE00 */  addi    r6, r6, -8704
/* 005374 8000A914 A0050002 */  lhz     r0, 2(r5)
/* 005378 8000A918 809B0000 */  lwz     r4, 0(r27)
/* 00537C 8000A91C 7C080E70 */  srawi   r8, r0, 1
/* 005380 8000A920 A0050000 */  lhz     r0, 0(r5)
/* 005384 8000A924 7D080194 */  addze   r8, r8
/* 005388 8000A928 80A40000 */  lwz     r5, 0(r4)
/* 00538C 8000A92C 208800A0 */  subfic  r4, r8, 0xa0
/* 005390 8000A930 A0E70002 */  lhz     r7, 2(r7)
/* 005394 8000A934 7C080E70 */  srawi   r8, r0, 1
/* 005398 8000A938 A0050000 */  lhz     r0, 0(r5)
/* 00539C 8000A93C 7D080194 */  addze   r8, r8
/* 0053A0 8000A940 20A80078 */  subfic  r5, r8, 0x78
/* 0053A4 8000A944 7CE70E70 */  srawi   r7, r7, 1
/* 0053A8 8000A948 7CE70194 */  addze   r7, r7
/* 0053AC 8000A94C 20E700A0 */  subfic  r7, r7, 0xa0
/* 0053B0 8000A950 7C000E70 */  srawi   r0, r0, 1
/* 0053B4 8000A954 7C000194 */  addze   r0, r0
/* 0053B8 8000A958 210000B4 */  subfic  r8, r0, 0xb4
/* 0053BC 8000A95C 48002C31 */  bl      simulatorDrawOKImage
/* 0053C0 8000A960 3C608013 */  lis     r3, DemoPad@ha
/* 0053C4 8000A964 38632758 */  addi    r3, r3, DemoPad@l
/* 0053C8 8000A968 8803000A */  lbz     r0, 0xa(r3)
/* 0053CC 8000A96C 7C000775 */  extsb.  r0, r0
/* 0053D0 8000A970 4082002C */  bne     lbl_8000A99C
/* 0053D4 8000A974 A0030000 */  lhz     r0, 0(r3)
/* 0053D8 8000A978 70001100 */  andi.   r0, r0, 0x1100
/* 0053DC 8000A97C 41820020 */  beq     lbl_8000A99C
/* 0053E0 8000A980 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 0053E4 8000A984 38800000 */  li      r4, 0
/* 0053E8 8000A988 80630004 */  lwz     r3, 4(r3)
/* 0053EC 8000A98C 48011D05 */  bl      soundPlayBeep
/* 0053F0 8000A990 38600001 */  li      r3, 1
/* 0053F4 8000A994 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 0053F8 8000A998 480021D0 */  b       lbl_8000CB68
lbl_8000A99C:
/* 0053FC 8000A99C 38600000 */  li      r3, 0
/* 005400 8000A9A0 480021C8 */  b       lbl_8000CB68
glabel lbl_8000A9A4
/* 005404 8000A9A4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 005408 8000A9A8 7C001800 */  cmpw    r0, r3
/* 00540C 8000A9AC 41820050 */  beq     lbl_8000A9FC
/* 005410 8000A9B0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 005414 8000A9B4 3C7F0001 */  addis   r3, r31, 1
/* 005418 8000A9B8 3863E5C8 */  addi    r3, r3, -6712
/* 00541C 8000A9BC 38810080 */  addi    r4, r1, 0x80
/* 005420 8000A9C0 480A8075 */  bl      DVDOpen
/* 005424 8000A9C4 2C030001 */  cmpwi   r3, 1
/* 005428 8000A9C8 40820024 */  bne     lbl_8000A9EC
/* 00542C 8000A9CC 80AD8040 */  lwz     r5, gmsg_gf04Size@sda21(r13)
/* 005430 8000A9D0 38610080 */  addi    r3, r1, 0x80
/* 005434 8000A9D4 389E01A0 */  addi    r4, r30, 0x1a0
/* 005438 8000A9D8 3805001F */  addi    r0, r5, 0x1f
/* 00543C 8000A9DC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 005440 8000A9E0 38C00000 */  li      r6, 0
/* 005444 8000A9E4 38E00000 */  li      r7, 0
/* 005448 8000A9E8 480042DD */  bl      simulatorDVDRead
lbl_8000A9EC:
/* 00544C 8000A9EC 38610080 */  addi    r3, r1, 0x80
/* 005450 8000A9F0 480A810D */  bl      DVDClose
/* 005454 8000A9F4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005458 8000A9F8 48004629 */  bl      simulatorUnpackTexPalette
lbl_8000A9FC:
/* 00545C 8000A9FC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 005460 8000AA00 3C7F0001 */  addis   r3, r31, 1
/* 005464 8000AA04 3B63D248 */  addi    r27, r3, -11704
/* 005468 8000AA08 80E40000 */  lwz     r7, 0(r4)
/* 00546C 8000AA0C 3B83DE08 */  addi    r28, r3, -8696
/* 005470 8000AA10 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 005474 8000AA14 3CDF0001 */  addis   r6, r31, 1
/* 005478 8000AA18 A0070002 */  lhz     r0, 2(r7)
/* 00547C 8000AA1C 81030000 */  lwz     r8, 0(r3)
/* 005480 8000AA20 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 005484 8000AA24 7C040E70 */  srawi   r4, r0, 1
/* 005488 8000AA28 A0070000 */  lhz     r0, 0(r7)
/* 00548C 8000AA2C 7C840194 */  addze   r4, r4
/* 005490 8000AA30 80BB0000 */  lwz     r5, 0(r27)
/* 005494 8000AA34 208400A0 */  subfic  r4, r4, 0xa0
/* 005498 8000AA38 7C000E70 */  srawi   r0, r0, 1
/* 00549C 8000AA3C A1080002 */  lhz     r8, 2(r8)
/* 0054A0 8000AA40 80E50000 */  lwz     r7, 0(r5)
/* 0054A4 8000AA44 7C000194 */  addze   r0, r0
/* 0054A8 8000AA48 20A00078 */  subfic  r5, r0, 0x78
/* 0054AC 8000AA4C A0070000 */  lhz     r0, 0(r7)
/* 0054B0 8000AA50 7D070E70 */  srawi   r7, r8, 1
/* 0054B4 8000AA54 7CE70194 */  addze   r7, r7
/* 0054B8 8000AA58 20E700A0 */  subfic  r7, r7, 0xa0
/* 0054BC 8000AA5C 7C000E70 */  srawi   r0, r0, 1
/* 0054C0 8000AA60 7C000194 */  addze   r0, r0
/* 0054C4 8000AA64 387E01A0 */  addi    r3, r30, 0x1a0
/* 0054C8 8000AA68 210000B4 */  subfic  r8, r0, 0xb4
/* 0054CC 8000AA6C 38C6DE00 */  addi    r6, r6, -8704
/* 0054D0 8000AA70 48002B1D */  bl      simulatorDrawOKImage
/* 0054D4 8000AA74 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 0054D8 8000AA78 2C000001 */  cmpwi   r0, 1
/* 0054DC 8000AA7C 40820020 */  bne     lbl_8000AA9C
/* 0054E0 8000AA80 480AC60D */  bl      DEMOPadRead
/* 0054E4 8000AA84 3C608013 */  lis     r3, DemoPad@ha
/* 0054E8 8000AA88 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 0054EC 8000AA8C 28000000 */  cmplwi  r0, 0
/* 0054F0 8000AA90 4182000C */  beq     lbl_8000AA9C
/* 0054F4 8000AA94 38600000 */  li      r3, 0
/* 0054F8 8000AA98 480020D0 */  b       lbl_8000CB68
lbl_8000AA9C:
/* 0054FC 8000AA9C 38000000 */  li      r0, 0
/* 005500 8000AAA0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 005504 8000AAA4 480AC5E9 */  bl      DEMOPadRead
/* 005508 8000AAA8 80BD0000 */  lwz     r5, 0(r29)
/* 00550C 8000AAAC 3CDF0001 */  addis   r6, r31, 1
/* 005510 8000AAB0 809C0000 */  lwz     r4, 0(r28)
/* 005514 8000AAB4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005518 8000AAB8 80A50000 */  lwz     r5, 0(r5)
/* 00551C 8000AABC 80E40000 */  lwz     r7, 0(r4)
/* 005520 8000AAC0 38C6DE00 */  addi    r6, r6, -8704
/* 005524 8000AAC4 A0050002 */  lhz     r0, 2(r5)
/* 005528 8000AAC8 809B0000 */  lwz     r4, 0(r27)
/* 00552C 8000AACC 7C080E70 */  srawi   r8, r0, 1
/* 005530 8000AAD0 A0050000 */  lhz     r0, 0(r5)
/* 005534 8000AAD4 7D080194 */  addze   r8, r8
/* 005538 8000AAD8 80A40000 */  lwz     r5, 0(r4)
/* 00553C 8000AADC 208800A0 */  subfic  r4, r8, 0xa0
/* 005540 8000AAE0 A0E70002 */  lhz     r7, 2(r7)
/* 005544 8000AAE4 7C080E70 */  srawi   r8, r0, 1
/* 005548 8000AAE8 A0050000 */  lhz     r0, 0(r5)
/* 00554C 8000AAEC 7D080194 */  addze   r8, r8
/* 005550 8000AAF0 20A80078 */  subfic  r5, r8, 0x78
/* 005554 8000AAF4 7CE70E70 */  srawi   r7, r7, 1
/* 005558 8000AAF8 7CE70194 */  addze   r7, r7
/* 00555C 8000AAFC 20E700A0 */  subfic  r7, r7, 0xa0
/* 005560 8000AB00 7C000E70 */  srawi   r0, r0, 1
/* 005564 8000AB04 7C000194 */  addze   r0, r0
/* 005568 8000AB08 210000B4 */  subfic  r8, r0, 0xb4
/* 00556C 8000AB0C 48002A81 */  bl      simulatorDrawOKImage
/* 005570 8000AB10 3C608013 */  lis     r3, DemoPad@ha
/* 005574 8000AB14 38632758 */  addi    r3, r3, DemoPad@l
/* 005578 8000AB18 8803000A */  lbz     r0, 0xa(r3)
/* 00557C 8000AB1C 7C000775 */  extsb.  r0, r0
/* 005580 8000AB20 4082002C */  bne     lbl_8000AB4C
/* 005584 8000AB24 A0030000 */  lhz     r0, 0(r3)
/* 005588 8000AB28 70001100 */  andi.   r0, r0, 0x1100
/* 00558C 8000AB2C 41820020 */  beq     lbl_8000AB4C
/* 005590 8000AB30 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 005594 8000AB34 38800000 */  li      r4, 0
/* 005598 8000AB38 80630004 */  lwz     r3, 4(r3)
/* 00559C 8000AB3C 48011B55 */  bl      soundPlayBeep
/* 0055A0 8000AB40 38600001 */  li      r3, 1
/* 0055A4 8000AB44 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 0055A8 8000AB48 48002020 */  b       lbl_8000CB68
lbl_8000AB4C:
/* 0055AC 8000AB4C 38600000 */  li      r3, 0
/* 0055B0 8000AB50 48002018 */  b       lbl_8000CB68
glabel lbl_8000AB54
/* 0055B4 8000AB54 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0055B8 8000AB58 7C001800 */  cmpw    r0, r3
/* 0055BC 8000AB5C 41820050 */  beq     lbl_8000ABAC
/* 0055C0 8000AB60 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0055C4 8000AB64 3C7F0001 */  addis   r3, r31, 1
/* 0055C8 8000AB68 3863E5DC */  addi    r3, r3, -6692
/* 0055CC 8000AB6C 38810080 */  addi    r4, r1, 0x80
/* 0055D0 8000AB70 480A7EC5 */  bl      DVDOpen
/* 0055D4 8000AB74 2C030001 */  cmpwi   r3, 1
/* 0055D8 8000AB78 40820024 */  bne     lbl_8000AB9C
/* 0055DC 8000AB7C 80AD8044 */  lwz     r5, gmsg_gf05Size@sda21(r13)
/* 0055E0 8000AB80 38610080 */  addi    r3, r1, 0x80
/* 0055E4 8000AB84 389E01A0 */  addi    r4, r30, 0x1a0
/* 0055E8 8000AB88 3805001F */  addi    r0, r5, 0x1f
/* 0055EC 8000AB8C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0055F0 8000AB90 38C00000 */  li      r6, 0
/* 0055F4 8000AB94 38E00000 */  li      r7, 0
/* 0055F8 8000AB98 4800412D */  bl      simulatorDVDRead
lbl_8000AB9C:
/* 0055FC 8000AB9C 38610080 */  addi    r3, r1, 0x80
/* 005600 8000ABA0 480A7F5D */  bl      DVDClose
/* 005604 8000ABA4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005608 8000ABA8 48004479 */  bl      simulatorUnpackTexPalette
lbl_8000ABAC:
/* 00560C 8000ABAC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 005610 8000ABB0 3C7F0001 */  addis   r3, r31, 1
/* 005614 8000ABB4 3B63D248 */  addi    r27, r3, -11704
/* 005618 8000ABB8 80E40000 */  lwz     r7, 0(r4)
/* 00561C 8000ABBC 3B83DE08 */  addi    r28, r3, -8696
/* 005620 8000ABC0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 005624 8000ABC4 3CDF0001 */  addis   r6, r31, 1
/* 005628 8000ABC8 A0070002 */  lhz     r0, 2(r7)
/* 00562C 8000ABCC 81030000 */  lwz     r8, 0(r3)
/* 005630 8000ABD0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 005634 8000ABD4 7C040E70 */  srawi   r4, r0, 1
/* 005638 8000ABD8 A0070000 */  lhz     r0, 0(r7)
/* 00563C 8000ABDC 7C840194 */  addze   r4, r4
/* 005640 8000ABE0 80BB0000 */  lwz     r5, 0(r27)
/* 005644 8000ABE4 208400A0 */  subfic  r4, r4, 0xa0
/* 005648 8000ABE8 7C000E70 */  srawi   r0, r0, 1
/* 00564C 8000ABEC A1080002 */  lhz     r8, 2(r8)
/* 005650 8000ABF0 80E50000 */  lwz     r7, 0(r5)
/* 005654 8000ABF4 7C000194 */  addze   r0, r0
/* 005658 8000ABF8 20A00078 */  subfic  r5, r0, 0x78
/* 00565C 8000ABFC A0070000 */  lhz     r0, 0(r7)
/* 005660 8000AC00 7D070E70 */  srawi   r7, r8, 1
/* 005664 8000AC04 7CE70194 */  addze   r7, r7
/* 005668 8000AC08 20E700A0 */  subfic  r7, r7, 0xa0
/* 00566C 8000AC0C 7C000E70 */  srawi   r0, r0, 1
/* 005670 8000AC10 7C000194 */  addze   r0, r0
/* 005674 8000AC14 387E01A0 */  addi    r3, r30, 0x1a0
/* 005678 8000AC18 210000B4 */  subfic  r8, r0, 0xb4
/* 00567C 8000AC1C 38C6DE00 */  addi    r6, r6, -8704
/* 005680 8000AC20 4800296D */  bl      simulatorDrawOKImage
/* 005684 8000AC24 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 005688 8000AC28 2C000001 */  cmpwi   r0, 1
/* 00568C 8000AC2C 40820020 */  bne     lbl_8000AC4C
/* 005690 8000AC30 480AC45D */  bl      DEMOPadRead
/* 005694 8000AC34 3C608013 */  lis     r3, DemoPad@ha
/* 005698 8000AC38 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00569C 8000AC3C 28000000 */  cmplwi  r0, 0
/* 0056A0 8000AC40 4182000C */  beq     lbl_8000AC4C
/* 0056A4 8000AC44 38600000 */  li      r3, 0
/* 0056A8 8000AC48 48001F20 */  b       lbl_8000CB68
lbl_8000AC4C:
/* 0056AC 8000AC4C 38000000 */  li      r0, 0
/* 0056B0 8000AC50 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 0056B4 8000AC54 480AC439 */  bl      DEMOPadRead
/* 0056B8 8000AC58 80BD0000 */  lwz     r5, 0(r29)
/* 0056BC 8000AC5C 3CDF0001 */  addis   r6, r31, 1
/* 0056C0 8000AC60 809C0000 */  lwz     r4, 0(r28)
/* 0056C4 8000AC64 387E01A0 */  addi    r3, r30, 0x1a0
/* 0056C8 8000AC68 80A50000 */  lwz     r5, 0(r5)
/* 0056CC 8000AC6C 80E40000 */  lwz     r7, 0(r4)
/* 0056D0 8000AC70 38C6DE00 */  addi    r6, r6, -8704
/* 0056D4 8000AC74 A0050002 */  lhz     r0, 2(r5)
/* 0056D8 8000AC78 809B0000 */  lwz     r4, 0(r27)
/* 0056DC 8000AC7C 7C080E70 */  srawi   r8, r0, 1
/* 0056E0 8000AC80 A0050000 */  lhz     r0, 0(r5)
/* 0056E4 8000AC84 7D080194 */  addze   r8, r8
/* 0056E8 8000AC88 80A40000 */  lwz     r5, 0(r4)
/* 0056EC 8000AC8C 208800A0 */  subfic  r4, r8, 0xa0
/* 0056F0 8000AC90 A0E70002 */  lhz     r7, 2(r7)
/* 0056F4 8000AC94 7C080E70 */  srawi   r8, r0, 1
/* 0056F8 8000AC98 A0050000 */  lhz     r0, 0(r5)
/* 0056FC 8000AC9C 7D080194 */  addze   r8, r8
/* 005700 8000ACA0 20A80078 */  subfic  r5, r8, 0x78
/* 005704 8000ACA4 7CE70E70 */  srawi   r7, r7, 1
/* 005708 8000ACA8 7CE70194 */  addze   r7, r7
/* 00570C 8000ACAC 20E700A0 */  subfic  r7, r7, 0xa0
/* 005710 8000ACB0 7C000E70 */  srawi   r0, r0, 1
/* 005714 8000ACB4 7C000194 */  addze   r0, r0
/* 005718 8000ACB8 210000B4 */  subfic  r8, r0, 0xb4
/* 00571C 8000ACBC 480028D1 */  bl      simulatorDrawOKImage
/* 005720 8000ACC0 3C608013 */  lis     r3, DemoPad@ha
/* 005724 8000ACC4 38632758 */  addi    r3, r3, DemoPad@l
/* 005728 8000ACC8 8803000A */  lbz     r0, 0xa(r3)
/* 00572C 8000ACCC 7C000775 */  extsb.  r0, r0
/* 005730 8000ACD0 4082002C */  bne     lbl_8000ACFC
/* 005734 8000ACD4 A0030000 */  lhz     r0, 0(r3)
/* 005738 8000ACD8 70001100 */  andi.   r0, r0, 0x1100
/* 00573C 8000ACDC 41820020 */  beq     lbl_8000ACFC
/* 005740 8000ACE0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 005744 8000ACE4 38800000 */  li      r4, 0
/* 005748 8000ACE8 80630004 */  lwz     r3, 4(r3)
/* 00574C 8000ACEC 480119A5 */  bl      soundPlayBeep
/* 005750 8000ACF0 38600001 */  li      r3, 1
/* 005754 8000ACF4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 005758 8000ACF8 48001E70 */  b       lbl_8000CB68
lbl_8000ACFC:
/* 00575C 8000ACFC 38600000 */  li      r3, 0
/* 005760 8000AD00 48001E68 */  b       lbl_8000CB68
glabel lbl_8000AD04
/* 005764 8000AD04 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 005768 8000AD08 7C001800 */  cmpw    r0, r3
/* 00576C 8000AD0C 41820050 */  beq     lbl_8000AD5C
/* 005770 8000AD10 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 005774 8000AD14 3C7F0001 */  addis   r3, r31, 1
/* 005778 8000AD18 3863E5F0 */  addi    r3, r3, -6672
/* 00577C 8000AD1C 38810080 */  addi    r4, r1, 0x80
/* 005780 8000AD20 480A7D15 */  bl      DVDOpen
/* 005784 8000AD24 2C030001 */  cmpwi   r3, 1
/* 005788 8000AD28 40820024 */  bne     lbl_8000AD4C
/* 00578C 8000AD2C 80AD8048 */  lwz     r5, gmsg_gf06Size@sda21(r13)
/* 005790 8000AD30 38610080 */  addi    r3, r1, 0x80
/* 005794 8000AD34 389E01A0 */  addi    r4, r30, 0x1a0
/* 005798 8000AD38 3805001F */  addi    r0, r5, 0x1f
/* 00579C 8000AD3C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0057A0 8000AD40 38C00000 */  li      r6, 0
/* 0057A4 8000AD44 38E00000 */  li      r7, 0
/* 0057A8 8000AD48 48003F7D */  bl      simulatorDVDRead
lbl_8000AD4C:
/* 0057AC 8000AD4C 38610080 */  addi    r3, r1, 0x80
/* 0057B0 8000AD50 480A7DAD */  bl      DVDClose
/* 0057B4 8000AD54 387E01A0 */  addi    r3, r30, 0x1a0
/* 0057B8 8000AD58 480042C9 */  bl      simulatorUnpackTexPalette
lbl_8000AD5C:
/* 0057BC 8000AD5C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 0057C0 8000AD60 3C7F0001 */  addis   r3, r31, 1
/* 0057C4 8000AD64 3B63D248 */  addi    r27, r3, -11704
/* 0057C8 8000AD68 80E40000 */  lwz     r7, 0(r4)
/* 0057CC 8000AD6C 3B83DE08 */  addi    r28, r3, -8696
/* 0057D0 8000AD70 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 0057D4 8000AD74 3CDF0001 */  addis   r6, r31, 1
/* 0057D8 8000AD78 A0070002 */  lhz     r0, 2(r7)
/* 0057DC 8000AD7C 81030000 */  lwz     r8, 0(r3)
/* 0057E0 8000AD80 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 0057E4 8000AD84 7C040E70 */  srawi   r4, r0, 1
/* 0057E8 8000AD88 A0070000 */  lhz     r0, 0(r7)
/* 0057EC 8000AD8C 7C840194 */  addze   r4, r4
/* 0057F0 8000AD90 80BB0000 */  lwz     r5, 0(r27)
/* 0057F4 8000AD94 208400A0 */  subfic  r4, r4, 0xa0
/* 0057F8 8000AD98 7C000E70 */  srawi   r0, r0, 1
/* 0057FC 8000AD9C A1080002 */  lhz     r8, 2(r8)
/* 005800 8000ADA0 80E50000 */  lwz     r7, 0(r5)
/* 005804 8000ADA4 7C000194 */  addze   r0, r0
/* 005808 8000ADA8 20A00078 */  subfic  r5, r0, 0x78
/* 00580C 8000ADAC A0070000 */  lhz     r0, 0(r7)
/* 005810 8000ADB0 7D070E70 */  srawi   r7, r8, 1
/* 005814 8000ADB4 7CE70194 */  addze   r7, r7
/* 005818 8000ADB8 20E700A0 */  subfic  r7, r7, 0xa0
/* 00581C 8000ADBC 7C000E70 */  srawi   r0, r0, 1
/* 005820 8000ADC0 7C000194 */  addze   r0, r0
/* 005824 8000ADC4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005828 8000ADC8 210000B4 */  subfic  r8, r0, 0xb4
/* 00582C 8000ADCC 38C6DE00 */  addi    r6, r6, -8704
/* 005830 8000ADD0 480027BD */  bl      simulatorDrawOKImage
/* 005834 8000ADD4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 005838 8000ADD8 2C000001 */  cmpwi   r0, 1
/* 00583C 8000ADDC 40820020 */  bne     lbl_8000ADFC
/* 005840 8000ADE0 480AC2AD */  bl      DEMOPadRead
/* 005844 8000ADE4 3C608013 */  lis     r3, DemoPad@ha
/* 005848 8000ADE8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00584C 8000ADEC 28000000 */  cmplwi  r0, 0
/* 005850 8000ADF0 4182000C */  beq     lbl_8000ADFC
/* 005854 8000ADF4 38600000 */  li      r3, 0
/* 005858 8000ADF8 48001D70 */  b       lbl_8000CB68
lbl_8000ADFC:
/* 00585C 8000ADFC 38000000 */  li      r0, 0
/* 005860 8000AE00 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 005864 8000AE04 480AC289 */  bl      DEMOPadRead
/* 005868 8000AE08 80BD0000 */  lwz     r5, 0(r29)
/* 00586C 8000AE0C 3CDF0001 */  addis   r6, r31, 1
/* 005870 8000AE10 809C0000 */  lwz     r4, 0(r28)
/* 005874 8000AE14 387E01A0 */  addi    r3, r30, 0x1a0
/* 005878 8000AE18 80A50000 */  lwz     r5, 0(r5)
/* 00587C 8000AE1C 80E40000 */  lwz     r7, 0(r4)
/* 005880 8000AE20 38C6DE00 */  addi    r6, r6, -8704
/* 005884 8000AE24 A0050002 */  lhz     r0, 2(r5)
/* 005888 8000AE28 809B0000 */  lwz     r4, 0(r27)
/* 00588C 8000AE2C 7C080E70 */  srawi   r8, r0, 1
/* 005890 8000AE30 A0050000 */  lhz     r0, 0(r5)
/* 005894 8000AE34 7D080194 */  addze   r8, r8
/* 005898 8000AE38 80A40000 */  lwz     r5, 0(r4)
/* 00589C 8000AE3C 208800A0 */  subfic  r4, r8, 0xa0
/* 0058A0 8000AE40 A0E70002 */  lhz     r7, 2(r7)
/* 0058A4 8000AE44 7C080E70 */  srawi   r8, r0, 1
/* 0058A8 8000AE48 A0050000 */  lhz     r0, 0(r5)
/* 0058AC 8000AE4C 7D080194 */  addze   r8, r8
/* 0058B0 8000AE50 20A80078 */  subfic  r5, r8, 0x78
/* 0058B4 8000AE54 7CE70E70 */  srawi   r7, r7, 1
/* 0058B8 8000AE58 7CE70194 */  addze   r7, r7
/* 0058BC 8000AE5C 20E700A0 */  subfic  r7, r7, 0xa0
/* 0058C0 8000AE60 7C000E70 */  srawi   r0, r0, 1
/* 0058C4 8000AE64 7C000194 */  addze   r0, r0
/* 0058C8 8000AE68 210000B4 */  subfic  r8, r0, 0xb4
/* 0058CC 8000AE6C 48002721 */  bl      simulatorDrawOKImage
/* 0058D0 8000AE70 3C608013 */  lis     r3, DemoPad@ha
/* 0058D4 8000AE74 38632758 */  addi    r3, r3, DemoPad@l
/* 0058D8 8000AE78 8803000A */  lbz     r0, 0xa(r3)
/* 0058DC 8000AE7C 7C000775 */  extsb.  r0, r0
/* 0058E0 8000AE80 4082002C */  bne     lbl_8000AEAC
/* 0058E4 8000AE84 A0030000 */  lhz     r0, 0(r3)
/* 0058E8 8000AE88 70001100 */  andi.   r0, r0, 0x1100
/* 0058EC 8000AE8C 41820020 */  beq     lbl_8000AEAC
/* 0058F0 8000AE90 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 0058F4 8000AE94 38800000 */  li      r4, 0
/* 0058F8 8000AE98 80630004 */  lwz     r3, 4(r3)
/* 0058FC 8000AE9C 480117F5 */  bl      soundPlayBeep
/* 005900 8000AEA0 38600001 */  li      r3, 1
/* 005904 8000AEA4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 005908 8000AEA8 48001CC0 */  b       lbl_8000CB68
lbl_8000AEAC:
/* 00590C 8000AEAC 38600000 */  li      r3, 0
/* 005910 8000AEB0 48001CB8 */  b       lbl_8000CB68
glabel lbl_8000AEB4
/* 005914 8000AEB4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 005918 8000AEB8 7C001800 */  cmpw    r0, r3
/* 00591C 8000AEBC 41820050 */  beq     lbl_8000AF0C
/* 005920 8000AEC0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 005924 8000AEC4 3C7F0001 */  addis   r3, r31, 1
/* 005928 8000AEC8 3863E604 */  addi    r3, r3, -6652
/* 00592C 8000AECC 38810080 */  addi    r4, r1, 0x80
/* 005930 8000AED0 480A7B65 */  bl      DVDOpen
/* 005934 8000AED4 2C030001 */  cmpwi   r3, 1
/* 005938 8000AED8 40820024 */  bne     lbl_8000AEFC
/* 00593C 8000AEDC 80AD8054 */  lwz     r5, gmsg_in03Size@sda21(r13)
/* 005940 8000AEE0 38610080 */  addi    r3, r1, 0x80
/* 005944 8000AEE4 389E01A0 */  addi    r4, r30, 0x1a0
/* 005948 8000AEE8 3805001F */  addi    r0, r5, 0x1f
/* 00594C 8000AEEC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 005950 8000AEF0 38C00000 */  li      r6, 0
/* 005954 8000AEF4 38E00000 */  li      r7, 0
/* 005958 8000AEF8 48003DCD */  bl      simulatorDVDRead
lbl_8000AEFC:
/* 00595C 8000AEFC 38610080 */  addi    r3, r1, 0x80
/* 005960 8000AF00 480A7BFD */  bl      DVDClose
/* 005964 8000AF04 387E01A0 */  addi    r3, r30, 0x1a0
/* 005968 8000AF08 48004119 */  bl      simulatorUnpackTexPalette
lbl_8000AF0C:
/* 00596C 8000AF0C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 005970 8000AF10 3C7F0001 */  addis   r3, r31, 1
/* 005974 8000AF14 3B63D248 */  addi    r27, r3, -11704
/* 005978 8000AF18 80E40000 */  lwz     r7, 0(r4)
/* 00597C 8000AF1C 3B83DE08 */  addi    r28, r3, -8696
/* 005980 8000AF20 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 005984 8000AF24 3CDF0001 */  addis   r6, r31, 1
/* 005988 8000AF28 A0070002 */  lhz     r0, 2(r7)
/* 00598C 8000AF2C 81030000 */  lwz     r8, 0(r3)
/* 005990 8000AF30 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 005994 8000AF34 7C040E70 */  srawi   r4, r0, 1
/* 005998 8000AF38 A0070000 */  lhz     r0, 0(r7)
/* 00599C 8000AF3C 7C840194 */  addze   r4, r4
/* 0059A0 8000AF40 80BB0000 */  lwz     r5, 0(r27)
/* 0059A4 8000AF44 208400A0 */  subfic  r4, r4, 0xa0
/* 0059A8 8000AF48 7C000E70 */  srawi   r0, r0, 1
/* 0059AC 8000AF4C A1080002 */  lhz     r8, 2(r8)
/* 0059B0 8000AF50 80E50000 */  lwz     r7, 0(r5)
/* 0059B4 8000AF54 7C000194 */  addze   r0, r0
/* 0059B8 8000AF58 20A00078 */  subfic  r5, r0, 0x78
/* 0059BC 8000AF5C A0070000 */  lhz     r0, 0(r7)
/* 0059C0 8000AF60 7D070E70 */  srawi   r7, r8, 1
/* 0059C4 8000AF64 7CE70194 */  addze   r7, r7
/* 0059C8 8000AF68 20E700A0 */  subfic  r7, r7, 0xa0
/* 0059CC 8000AF6C 7C000E70 */  srawi   r0, r0, 1
/* 0059D0 8000AF70 7C000194 */  addze   r0, r0
/* 0059D4 8000AF74 387E01A0 */  addi    r3, r30, 0x1a0
/* 0059D8 8000AF78 210000B4 */  subfic  r8, r0, 0xb4
/* 0059DC 8000AF7C 38C6DE00 */  addi    r6, r6, -8704
/* 0059E0 8000AF80 4800260D */  bl      simulatorDrawOKImage
/* 0059E4 8000AF84 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 0059E8 8000AF88 2C000001 */  cmpwi   r0, 1
/* 0059EC 8000AF8C 40820020 */  bne     lbl_8000AFAC
/* 0059F0 8000AF90 480AC0FD */  bl      DEMOPadRead
/* 0059F4 8000AF94 3C608013 */  lis     r3, DemoPad@ha
/* 0059F8 8000AF98 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 0059FC 8000AF9C 28000000 */  cmplwi  r0, 0
/* 005A00 8000AFA0 4182000C */  beq     lbl_8000AFAC
/* 005A04 8000AFA4 38600000 */  li      r3, 0
/* 005A08 8000AFA8 48001BC0 */  b       lbl_8000CB68
lbl_8000AFAC:
/* 005A0C 8000AFAC 38000000 */  li      r0, 0
/* 005A10 8000AFB0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 005A14 8000AFB4 480AC0D9 */  bl      DEMOPadRead
/* 005A18 8000AFB8 80BD0000 */  lwz     r5, 0(r29)
/* 005A1C 8000AFBC 3CDF0001 */  addis   r6, r31, 1
/* 005A20 8000AFC0 809C0000 */  lwz     r4, 0(r28)
/* 005A24 8000AFC4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005A28 8000AFC8 80A50000 */  lwz     r5, 0(r5)
/* 005A2C 8000AFCC 80E40000 */  lwz     r7, 0(r4)
/* 005A30 8000AFD0 38C6DE00 */  addi    r6, r6, -8704
/* 005A34 8000AFD4 A0050002 */  lhz     r0, 2(r5)
/* 005A38 8000AFD8 809B0000 */  lwz     r4, 0(r27)
/* 005A3C 8000AFDC 7C080E70 */  srawi   r8, r0, 1
/* 005A40 8000AFE0 A0050000 */  lhz     r0, 0(r5)
/* 005A44 8000AFE4 7D080194 */  addze   r8, r8
/* 005A48 8000AFE8 80A40000 */  lwz     r5, 0(r4)
/* 005A4C 8000AFEC 208800A0 */  subfic  r4, r8, 0xa0
/* 005A50 8000AFF0 A0E70002 */  lhz     r7, 2(r7)
/* 005A54 8000AFF4 7C080E70 */  srawi   r8, r0, 1
/* 005A58 8000AFF8 A0050000 */  lhz     r0, 0(r5)
/* 005A5C 8000AFFC 7D080194 */  addze   r8, r8
/* 005A60 8000B000 20A80078 */  subfic  r5, r8, 0x78
/* 005A64 8000B004 7CE70E70 */  srawi   r7, r7, 1
/* 005A68 8000B008 7CE70194 */  addze   r7, r7
/* 005A6C 8000B00C 20E700A0 */  subfic  r7, r7, 0xa0
/* 005A70 8000B010 7C000E70 */  srawi   r0, r0, 1
/* 005A74 8000B014 7C000194 */  addze   r0, r0
/* 005A78 8000B018 210000B4 */  subfic  r8, r0, 0xb4
/* 005A7C 8000B01C 48002571 */  bl      simulatorDrawOKImage
/* 005A80 8000B020 3C608013 */  lis     r3, DemoPad@ha
/* 005A84 8000B024 38632758 */  addi    r3, r3, DemoPad@l
/* 005A88 8000B028 8803000A */  lbz     r0, 0xa(r3)
/* 005A8C 8000B02C 7C000775 */  extsb.  r0, r0
/* 005A90 8000B030 4082002C */  bne     lbl_8000B05C
/* 005A94 8000B034 A0030000 */  lhz     r0, 0(r3)
/* 005A98 8000B038 70001100 */  andi.   r0, r0, 0x1100
/* 005A9C 8000B03C 41820020 */  beq     lbl_8000B05C
/* 005AA0 8000B040 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 005AA4 8000B044 38800000 */  li      r4, 0
/* 005AA8 8000B048 80630004 */  lwz     r3, 4(r3)
/* 005AAC 8000B04C 48011645 */  bl      soundPlayBeep
/* 005AB0 8000B050 38600001 */  li      r3, 1
/* 005AB4 8000B054 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 005AB8 8000B058 48001B10 */  b       lbl_8000CB68
lbl_8000B05C:
/* 005ABC 8000B05C 38600000 */  li      r3, 0
/* 005AC0 8000B060 48001B08 */  b       lbl_8000CB68
glabel lbl_8000B064
/* 005AC4 8000B064 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 005AC8 8000B068 7C001800 */  cmpw    r0, r3
/* 005ACC 8000B06C 41820050 */  beq     lbl_8000B0BC
/* 005AD0 8000B070 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 005AD4 8000B074 3C7F0001 */  addis   r3, r31, 1
/* 005AD8 8000B078 3863E618 */  addi    r3, r3, -6632
/* 005ADC 8000B07C 38810080 */  addi    r4, r1, 0x80
/* 005AE0 8000B080 480A79B5 */  bl      DVDOpen
/* 005AE4 8000B084 2C030001 */  cmpwi   r3, 1
/* 005AE8 8000B088 40820024 */  bne     lbl_8000B0AC
/* 005AEC 8000B08C 80AD8058 */  lwz     r5, gmsg_in04Size@sda21(r13)
/* 005AF0 8000B090 38610080 */  addi    r3, r1, 0x80
/* 005AF4 8000B094 389E01A0 */  addi    r4, r30, 0x1a0
/* 005AF8 8000B098 3805001F */  addi    r0, r5, 0x1f
/* 005AFC 8000B09C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 005B00 8000B0A0 38C00000 */  li      r6, 0
/* 005B04 8000B0A4 38E00000 */  li      r7, 0
/* 005B08 8000B0A8 48003C1D */  bl      simulatorDVDRead
lbl_8000B0AC:
/* 005B0C 8000B0AC 38610080 */  addi    r3, r1, 0x80
/* 005B10 8000B0B0 480A7A4D */  bl      DVDClose
/* 005B14 8000B0B4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005B18 8000B0B8 48003F69 */  bl      simulatorUnpackTexPalette
lbl_8000B0BC:
/* 005B1C 8000B0BC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 005B20 8000B0C0 3C7F0001 */  addis   r3, r31, 1
/* 005B24 8000B0C4 3B63D248 */  addi    r27, r3, -11704
/* 005B28 8000B0C8 80E40000 */  lwz     r7, 0(r4)
/* 005B2C 8000B0CC 3B83DE08 */  addi    r28, r3, -8696
/* 005B30 8000B0D0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 005B34 8000B0D4 3CDF0001 */  addis   r6, r31, 1
/* 005B38 8000B0D8 A0070002 */  lhz     r0, 2(r7)
/* 005B3C 8000B0DC 81030000 */  lwz     r8, 0(r3)
/* 005B40 8000B0E0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 005B44 8000B0E4 7C040E70 */  srawi   r4, r0, 1
/* 005B48 8000B0E8 A0070000 */  lhz     r0, 0(r7)
/* 005B4C 8000B0EC 7C840194 */  addze   r4, r4
/* 005B50 8000B0F0 80BB0000 */  lwz     r5, 0(r27)
/* 005B54 8000B0F4 208400A0 */  subfic  r4, r4, 0xa0
/* 005B58 8000B0F8 7C000E70 */  srawi   r0, r0, 1
/* 005B5C 8000B0FC A1080002 */  lhz     r8, 2(r8)
/* 005B60 8000B100 80E50000 */  lwz     r7, 0(r5)
/* 005B64 8000B104 7C000194 */  addze   r0, r0
/* 005B68 8000B108 20A00078 */  subfic  r5, r0, 0x78
/* 005B6C 8000B10C A0070000 */  lhz     r0, 0(r7)
/* 005B70 8000B110 7D070E70 */  srawi   r7, r8, 1
/* 005B74 8000B114 7CE70194 */  addze   r7, r7
/* 005B78 8000B118 20E700A0 */  subfic  r7, r7, 0xa0
/* 005B7C 8000B11C 7C000E70 */  srawi   r0, r0, 1
/* 005B80 8000B120 7C000194 */  addze   r0, r0
/* 005B84 8000B124 387E01A0 */  addi    r3, r30, 0x1a0
/* 005B88 8000B128 210000B4 */  subfic  r8, r0, 0xb4
/* 005B8C 8000B12C 38C6DE00 */  addi    r6, r6, -8704
/* 005B90 8000B130 4800245D */  bl      simulatorDrawOKImage
/* 005B94 8000B134 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 005B98 8000B138 2C000001 */  cmpwi   r0, 1
/* 005B9C 8000B13C 40820020 */  bne     lbl_8000B15C
/* 005BA0 8000B140 480ABF4D */  bl      DEMOPadRead
/* 005BA4 8000B144 3C608013 */  lis     r3, DemoPad@ha
/* 005BA8 8000B148 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 005BAC 8000B14C 28000000 */  cmplwi  r0, 0
/* 005BB0 8000B150 4182000C */  beq     lbl_8000B15C
/* 005BB4 8000B154 38600000 */  li      r3, 0
/* 005BB8 8000B158 48001A10 */  b       lbl_8000CB68
lbl_8000B15C:
/* 005BBC 8000B15C 38000000 */  li      r0, 0
/* 005BC0 8000B160 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 005BC4 8000B164 480ABF29 */  bl      DEMOPadRead
/* 005BC8 8000B168 80BD0000 */  lwz     r5, 0(r29)
/* 005BCC 8000B16C 3CDF0001 */  addis   r6, r31, 1
/* 005BD0 8000B170 809C0000 */  lwz     r4, 0(r28)
/* 005BD4 8000B174 387E01A0 */  addi    r3, r30, 0x1a0
/* 005BD8 8000B178 80A50000 */  lwz     r5, 0(r5)
/* 005BDC 8000B17C 80E40000 */  lwz     r7, 0(r4)
/* 005BE0 8000B180 38C6DE00 */  addi    r6, r6, -8704
/* 005BE4 8000B184 A0050002 */  lhz     r0, 2(r5)
/* 005BE8 8000B188 809B0000 */  lwz     r4, 0(r27)
/* 005BEC 8000B18C 7C080E70 */  srawi   r8, r0, 1
/* 005BF0 8000B190 A0050000 */  lhz     r0, 0(r5)
/* 005BF4 8000B194 7D080194 */  addze   r8, r8
/* 005BF8 8000B198 80A40000 */  lwz     r5, 0(r4)
/* 005BFC 8000B19C 208800A0 */  subfic  r4, r8, 0xa0
/* 005C00 8000B1A0 A0E70002 */  lhz     r7, 2(r7)
/* 005C04 8000B1A4 7C080E70 */  srawi   r8, r0, 1
/* 005C08 8000B1A8 A0050000 */  lhz     r0, 0(r5)
/* 005C0C 8000B1AC 7D080194 */  addze   r8, r8
/* 005C10 8000B1B0 20A80078 */  subfic  r5, r8, 0x78
/* 005C14 8000B1B4 7CE70E70 */  srawi   r7, r7, 1
/* 005C18 8000B1B8 7CE70194 */  addze   r7, r7
/* 005C1C 8000B1BC 20E700A0 */  subfic  r7, r7, 0xa0
/* 005C20 8000B1C0 7C000E70 */  srawi   r0, r0, 1
/* 005C24 8000B1C4 7C000194 */  addze   r0, r0
/* 005C28 8000B1C8 210000B4 */  subfic  r8, r0, 0xb4
/* 005C2C 8000B1CC 480023C1 */  bl      simulatorDrawOKImage
/* 005C30 8000B1D0 3C608013 */  lis     r3, DemoPad@ha
/* 005C34 8000B1D4 38632758 */  addi    r3, r3, DemoPad@l
/* 005C38 8000B1D8 8803000A */  lbz     r0, 0xa(r3)
/* 005C3C 8000B1DC 7C000775 */  extsb.  r0, r0
/* 005C40 8000B1E0 4082002C */  bne     lbl_8000B20C
/* 005C44 8000B1E4 A0030000 */  lhz     r0, 0(r3)
/* 005C48 8000B1E8 70001100 */  andi.   r0, r0, 0x1100
/* 005C4C 8000B1EC 41820020 */  beq     lbl_8000B20C
/* 005C50 8000B1F0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 005C54 8000B1F4 38800000 */  li      r4, 0
/* 005C58 8000B1F8 80630004 */  lwz     r3, 4(r3)
/* 005C5C 8000B1FC 48011495 */  bl      soundPlayBeep
/* 005C60 8000B200 38600001 */  li      r3, 1
/* 005C64 8000B204 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 005C68 8000B208 48001960 */  b       lbl_8000CB68
lbl_8000B20C:
/* 005C6C 8000B20C 38600000 */  li      r3, 0
/* 005C70 8000B210 48001958 */  b       lbl_8000CB68
glabel lbl_8000B214
/* 005C74 8000B214 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 005C78 8000B218 7C001800 */  cmpw    r0, r3
/* 005C7C 8000B21C 41820050 */  beq     lbl_8000B26C
/* 005C80 8000B220 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 005C84 8000B224 3C7F0001 */  addis   r3, r31, 1
/* 005C88 8000B228 3863E62C */  addi    r3, r3, -6612
/* 005C8C 8000B22C 38810080 */  addi    r4, r1, 0x80
/* 005C90 8000B230 480A7805 */  bl      DVDOpen
/* 005C94 8000B234 2C030001 */  cmpwi   r3, 1
/* 005C98 8000B238 40820024 */  bne     lbl_8000B25C
/* 005C9C 8000B23C 80AD805C */  lwz     r5, gmsg_in05Size@sda21(r13)
/* 005CA0 8000B240 38610080 */  addi    r3, r1, 0x80
/* 005CA4 8000B244 389E01A0 */  addi    r4, r30, 0x1a0
/* 005CA8 8000B248 3805001F */  addi    r0, r5, 0x1f
/* 005CAC 8000B24C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 005CB0 8000B250 38C00000 */  li      r6, 0
/* 005CB4 8000B254 38E00000 */  li      r7, 0
/* 005CB8 8000B258 48003A6D */  bl      simulatorDVDRead
lbl_8000B25C:
/* 005CBC 8000B25C 38610080 */  addi    r3, r1, 0x80
/* 005CC0 8000B260 480A789D */  bl      DVDClose
/* 005CC4 8000B264 387E01A0 */  addi    r3, r30, 0x1a0
/* 005CC8 8000B268 48003DB9 */  bl      simulatorUnpackTexPalette
lbl_8000B26C:
/* 005CCC 8000B26C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 005CD0 8000B270 3C7F0001 */  addis   r3, r31, 1
/* 005CD4 8000B274 3B63D248 */  addi    r27, r3, -11704
/* 005CD8 8000B278 80E40000 */  lwz     r7, 0(r4)
/* 005CDC 8000B27C 3B83DE08 */  addi    r28, r3, -8696
/* 005CE0 8000B280 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 005CE4 8000B284 3CDF0001 */  addis   r6, r31, 1
/* 005CE8 8000B288 A0070002 */  lhz     r0, 2(r7)
/* 005CEC 8000B28C 81030000 */  lwz     r8, 0(r3)
/* 005CF0 8000B290 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 005CF4 8000B294 7C040E70 */  srawi   r4, r0, 1
/* 005CF8 8000B298 A0070000 */  lhz     r0, 0(r7)
/* 005CFC 8000B29C 7C840194 */  addze   r4, r4
/* 005D00 8000B2A0 80BB0000 */  lwz     r5, 0(r27)
/* 005D04 8000B2A4 208400A0 */  subfic  r4, r4, 0xa0
/* 005D08 8000B2A8 7C000E70 */  srawi   r0, r0, 1
/* 005D0C 8000B2AC A1080002 */  lhz     r8, 2(r8)
/* 005D10 8000B2B0 80E50000 */  lwz     r7, 0(r5)
/* 005D14 8000B2B4 7C000194 */  addze   r0, r0
/* 005D18 8000B2B8 20A00078 */  subfic  r5, r0, 0x78
/* 005D1C 8000B2BC A0070000 */  lhz     r0, 0(r7)
/* 005D20 8000B2C0 7D070E70 */  srawi   r7, r8, 1
/* 005D24 8000B2C4 7CE70194 */  addze   r7, r7
/* 005D28 8000B2C8 20E700A0 */  subfic  r7, r7, 0xa0
/* 005D2C 8000B2CC 7C000E70 */  srawi   r0, r0, 1
/* 005D30 8000B2D0 7C000194 */  addze   r0, r0
/* 005D34 8000B2D4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005D38 8000B2D8 210000B4 */  subfic  r8, r0, 0xb4
/* 005D3C 8000B2DC 38C6DE00 */  addi    r6, r6, -8704
/* 005D40 8000B2E0 480022AD */  bl      simulatorDrawOKImage
/* 005D44 8000B2E4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 005D48 8000B2E8 2C000001 */  cmpwi   r0, 1
/* 005D4C 8000B2EC 40820020 */  bne     lbl_8000B30C
/* 005D50 8000B2F0 480ABD9D */  bl      DEMOPadRead
/* 005D54 8000B2F4 3C608013 */  lis     r3, DemoPad@ha
/* 005D58 8000B2F8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 005D5C 8000B2FC 28000000 */  cmplwi  r0, 0
/* 005D60 8000B300 4182000C */  beq     lbl_8000B30C
/* 005D64 8000B304 38600000 */  li      r3, 0
/* 005D68 8000B308 48001860 */  b       lbl_8000CB68
lbl_8000B30C:
/* 005D6C 8000B30C 38000000 */  li      r0, 0
/* 005D70 8000B310 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 005D74 8000B314 480ABD79 */  bl      DEMOPadRead
/* 005D78 8000B318 80BD0000 */  lwz     r5, 0(r29)
/* 005D7C 8000B31C 3CDF0001 */  addis   r6, r31, 1
/* 005D80 8000B320 809C0000 */  lwz     r4, 0(r28)
/* 005D84 8000B324 387E01A0 */  addi    r3, r30, 0x1a0
/* 005D88 8000B328 80A50000 */  lwz     r5, 0(r5)
/* 005D8C 8000B32C 80E40000 */  lwz     r7, 0(r4)
/* 005D90 8000B330 38C6DE00 */  addi    r6, r6, -8704
/* 005D94 8000B334 A0050002 */  lhz     r0, 2(r5)
/* 005D98 8000B338 809B0000 */  lwz     r4, 0(r27)
/* 005D9C 8000B33C 7C080E70 */  srawi   r8, r0, 1
/* 005DA0 8000B340 A0050000 */  lhz     r0, 0(r5)
/* 005DA4 8000B344 7D080194 */  addze   r8, r8
/* 005DA8 8000B348 80A40000 */  lwz     r5, 0(r4)
/* 005DAC 8000B34C 208800A0 */  subfic  r4, r8, 0xa0
/* 005DB0 8000B350 A0E70002 */  lhz     r7, 2(r7)
/* 005DB4 8000B354 7C080E70 */  srawi   r8, r0, 1
/* 005DB8 8000B358 A0050000 */  lhz     r0, 0(r5)
/* 005DBC 8000B35C 7D080194 */  addze   r8, r8
/* 005DC0 8000B360 20A80078 */  subfic  r5, r8, 0x78
/* 005DC4 8000B364 7CE70E70 */  srawi   r7, r7, 1
/* 005DC8 8000B368 7CE70194 */  addze   r7, r7
/* 005DCC 8000B36C 20E700A0 */  subfic  r7, r7, 0xa0
/* 005DD0 8000B370 7C000E70 */  srawi   r0, r0, 1
/* 005DD4 8000B374 7C000194 */  addze   r0, r0
/* 005DD8 8000B378 210000B4 */  subfic  r8, r0, 0xb4
/* 005DDC 8000B37C 48002211 */  bl      simulatorDrawOKImage
/* 005DE0 8000B380 3C608013 */  lis     r3, DemoPad@ha
/* 005DE4 8000B384 38632758 */  addi    r3, r3, DemoPad@l
/* 005DE8 8000B388 8803000A */  lbz     r0, 0xa(r3)
/* 005DEC 8000B38C 7C000775 */  extsb.  r0, r0
/* 005DF0 8000B390 4082002C */  bne     lbl_8000B3BC
/* 005DF4 8000B394 A0030000 */  lhz     r0, 0(r3)
/* 005DF8 8000B398 70001100 */  andi.   r0, r0, 0x1100
/* 005DFC 8000B39C 41820020 */  beq     lbl_8000B3BC
/* 005E00 8000B3A0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 005E04 8000B3A4 38800000 */  li      r4, 0
/* 005E08 8000B3A8 80630004 */  lwz     r3, 4(r3)
/* 005E0C 8000B3AC 480112E5 */  bl      soundPlayBeep
/* 005E10 8000B3B0 38600001 */  li      r3, 1
/* 005E14 8000B3B4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 005E18 8000B3B8 480017B0 */  b       lbl_8000CB68
lbl_8000B3BC:
/* 005E1C 8000B3BC 38600000 */  li      r3, 0
/* 005E20 8000B3C0 480017A8 */  b       lbl_8000CB68
glabel lbl_8000B3C4
/* 005E24 8000B3C4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 005E28 8000B3C8 7C001800 */  cmpw    r0, r3
/* 005E2C 8000B3CC 41820050 */  beq     lbl_8000B41C
/* 005E30 8000B3D0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 005E34 8000B3D4 3C7F0001 */  addis   r3, r31, 1
/* 005E38 8000B3D8 3863E640 */  addi    r3, r3, -6592
/* 005E3C 8000B3DC 38810080 */  addi    r4, r1, 0x80
/* 005E40 8000B3E0 480A7655 */  bl      DVDOpen
/* 005E44 8000B3E4 2C030001 */  cmpwi   r3, 1
/* 005E48 8000B3E8 40820024 */  bne     lbl_8000B40C
/* 005E4C 8000B3EC 80AD8060 */  lwz     r5, gmsg_sv01Size@sda21(r13)
/* 005E50 8000B3F0 38610080 */  addi    r3, r1, 0x80
/* 005E54 8000B3F4 389E01A0 */  addi    r4, r30, 0x1a0
/* 005E58 8000B3F8 3805001F */  addi    r0, r5, 0x1f
/* 005E5C 8000B3FC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 005E60 8000B400 38C00000 */  li      r6, 0
/* 005E64 8000B404 38E00000 */  li      r7, 0
/* 005E68 8000B408 480038BD */  bl      simulatorDVDRead
lbl_8000B40C:
/* 005E6C 8000B40C 38610080 */  addi    r3, r1, 0x80
/* 005E70 8000B410 480A76ED */  bl      DVDClose
/* 005E74 8000B414 387E01A0 */  addi    r3, r30, 0x1a0
/* 005E78 8000B418 48003C09 */  bl      simulatorUnpackTexPalette
lbl_8000B41C:
/* 005E7C 8000B41C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 005E80 8000B420 3C7F0001 */  addis   r3, r31, 1
/* 005E84 8000B424 3B63D248 */  addi    r27, r3, -11704
/* 005E88 8000B428 80E40000 */  lwz     r7, 0(r4)
/* 005E8C 8000B42C 3B83DE08 */  addi    r28, r3, -8696
/* 005E90 8000B430 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 005E94 8000B434 3CDF0001 */  addis   r6, r31, 1
/* 005E98 8000B438 A0070002 */  lhz     r0, 2(r7)
/* 005E9C 8000B43C 81030000 */  lwz     r8, 0(r3)
/* 005EA0 8000B440 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 005EA4 8000B444 7C040E70 */  srawi   r4, r0, 1
/* 005EA8 8000B448 A0070000 */  lhz     r0, 0(r7)
/* 005EAC 8000B44C 7C840194 */  addze   r4, r4
/* 005EB0 8000B450 80BB0000 */  lwz     r5, 0(r27)
/* 005EB4 8000B454 208400A0 */  subfic  r4, r4, 0xa0
/* 005EB8 8000B458 7C000E70 */  srawi   r0, r0, 1
/* 005EBC 8000B45C A1080002 */  lhz     r8, 2(r8)
/* 005EC0 8000B460 80E50000 */  lwz     r7, 0(r5)
/* 005EC4 8000B464 7C000194 */  addze   r0, r0
/* 005EC8 8000B468 20A00078 */  subfic  r5, r0, 0x78
/* 005ECC 8000B46C A0070000 */  lhz     r0, 0(r7)
/* 005ED0 8000B470 7D070E70 */  srawi   r7, r8, 1
/* 005ED4 8000B474 7CE70194 */  addze   r7, r7
/* 005ED8 8000B478 20E700A0 */  subfic  r7, r7, 0xa0
/* 005EDC 8000B47C 7C000E70 */  srawi   r0, r0, 1
/* 005EE0 8000B480 7C000194 */  addze   r0, r0
/* 005EE4 8000B484 387E01A0 */  addi    r3, r30, 0x1a0
/* 005EE8 8000B488 210000B4 */  subfic  r8, r0, 0xb4
/* 005EEC 8000B48C 38C6DE00 */  addi    r6, r6, -8704
/* 005EF0 8000B490 480020FD */  bl      simulatorDrawOKImage
/* 005EF4 8000B494 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 005EF8 8000B498 2C000001 */  cmpwi   r0, 1
/* 005EFC 8000B49C 40820020 */  bne     lbl_8000B4BC
/* 005F00 8000B4A0 480ABBED */  bl      DEMOPadRead
/* 005F04 8000B4A4 3C608013 */  lis     r3, DemoPad@ha
/* 005F08 8000B4A8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 005F0C 8000B4AC 28000000 */  cmplwi  r0, 0
/* 005F10 8000B4B0 4182000C */  beq     lbl_8000B4BC
/* 005F14 8000B4B4 38600000 */  li      r3, 0
/* 005F18 8000B4B8 480016B0 */  b       lbl_8000CB68
lbl_8000B4BC:
/* 005F1C 8000B4BC 38000000 */  li      r0, 0
/* 005F20 8000B4C0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 005F24 8000B4C4 480ABBC9 */  bl      DEMOPadRead
/* 005F28 8000B4C8 80BD0000 */  lwz     r5, 0(r29)
/* 005F2C 8000B4CC 3CDF0001 */  addis   r6, r31, 1
/* 005F30 8000B4D0 809C0000 */  lwz     r4, 0(r28)
/* 005F34 8000B4D4 387E01A0 */  addi    r3, r30, 0x1a0
/* 005F38 8000B4D8 80A50000 */  lwz     r5, 0(r5)
/* 005F3C 8000B4DC 80E40000 */  lwz     r7, 0(r4)
/* 005F40 8000B4E0 38C6DE00 */  addi    r6, r6, -8704
/* 005F44 8000B4E4 A0050002 */  lhz     r0, 2(r5)
/* 005F48 8000B4E8 809B0000 */  lwz     r4, 0(r27)
/* 005F4C 8000B4EC 7C080E70 */  srawi   r8, r0, 1
/* 005F50 8000B4F0 A0050000 */  lhz     r0, 0(r5)
/* 005F54 8000B4F4 7D080194 */  addze   r8, r8
/* 005F58 8000B4F8 80A40000 */  lwz     r5, 0(r4)
/* 005F5C 8000B4FC 208800A0 */  subfic  r4, r8, 0xa0
/* 005F60 8000B500 A0E70002 */  lhz     r7, 2(r7)
/* 005F64 8000B504 7C080E70 */  srawi   r8, r0, 1
/* 005F68 8000B508 A0050000 */  lhz     r0, 0(r5)
/* 005F6C 8000B50C 7D080194 */  addze   r8, r8
/* 005F70 8000B510 20A80078 */  subfic  r5, r8, 0x78
/* 005F74 8000B514 7CE70E70 */  srawi   r7, r7, 1
/* 005F78 8000B518 7CE70194 */  addze   r7, r7
/* 005F7C 8000B51C 20E700A0 */  subfic  r7, r7, 0xa0
/* 005F80 8000B520 7C000E70 */  srawi   r0, r0, 1
/* 005F84 8000B524 7C000194 */  addze   r0, r0
/* 005F88 8000B528 210000B4 */  subfic  r8, r0, 0xb4
/* 005F8C 8000B52C 48002061 */  bl      simulatorDrawOKImage
/* 005F90 8000B530 3C608013 */  lis     r3, DemoPad@ha
/* 005F94 8000B534 38632758 */  addi    r3, r3, DemoPad@l
/* 005F98 8000B538 8803000A */  lbz     r0, 0xa(r3)
/* 005F9C 8000B53C 7C000775 */  extsb.  r0, r0
/* 005FA0 8000B540 4082002C */  bne     lbl_8000B56C
/* 005FA4 8000B544 A0030000 */  lhz     r0, 0(r3)
/* 005FA8 8000B548 70001100 */  andi.   r0, r0, 0x1100
/* 005FAC 8000B54C 41820020 */  beq     lbl_8000B56C
/* 005FB0 8000B550 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 005FB4 8000B554 38800000 */  li      r4, 0
/* 005FB8 8000B558 80630004 */  lwz     r3, 4(r3)
/* 005FBC 8000B55C 48011135 */  bl      soundPlayBeep
/* 005FC0 8000B560 38600001 */  li      r3, 1
/* 005FC4 8000B564 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 005FC8 8000B568 48001600 */  b       lbl_8000CB68
lbl_8000B56C:
/* 005FCC 8000B56C 38600000 */  li      r3, 0
/* 005FD0 8000B570 480015F8 */  b       lbl_8000CB68
glabel lbl_8000B574
/* 005FD4 8000B574 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 005FD8 8000B578 7C001800 */  cmpw    r0, r3
/* 005FDC 8000B57C 41820050 */  beq     lbl_8000B5CC
/* 005FE0 8000B580 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 005FE4 8000B584 3C7F0001 */  addis   r3, r31, 1
/* 005FE8 8000B588 3863E654 */  addi    r3, r3, -6572
/* 005FEC 8000B58C 38810080 */  addi    r4, r1, 0x80
/* 005FF0 8000B590 480A74A5 */  bl      DVDOpen
/* 005FF4 8000B594 2C030001 */  cmpwi   r3, 1
/* 005FF8 8000B598 40820024 */  bne     lbl_8000B5BC
/* 005FFC 8000B59C 80AD8064 */  lwz     r5, gmsg_sv01_2Size@sda21(r13)
/* 006000 8000B5A0 38610080 */  addi    r3, r1, 0x80
/* 006004 8000B5A4 389E01A0 */  addi    r4, r30, 0x1a0
/* 006008 8000B5A8 3805001F */  addi    r0, r5, 0x1f
/* 00600C 8000B5AC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 006010 8000B5B0 38C00000 */  li      r6, 0
/* 006014 8000B5B4 38E00000 */  li      r7, 0
/* 006018 8000B5B8 4800370D */  bl      simulatorDVDRead
lbl_8000B5BC:
/* 00601C 8000B5BC 38610080 */  addi    r3, r1, 0x80
/* 006020 8000B5C0 480A753D */  bl      DVDClose
/* 006024 8000B5C4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006028 8000B5C8 48003A59 */  bl      simulatorUnpackTexPalette
lbl_8000B5CC:
/* 00602C 8000B5CC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 006030 8000B5D0 3C7F0001 */  addis   r3, r31, 1
/* 006034 8000B5D4 3B63D248 */  addi    r27, r3, -11704
/* 006038 8000B5D8 80E40000 */  lwz     r7, 0(r4)
/* 00603C 8000B5DC 3B83DE08 */  addi    r28, r3, -8696
/* 006040 8000B5E0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 006044 8000B5E4 3CDF0001 */  addis   r6, r31, 1
/* 006048 8000B5E8 A0070002 */  lhz     r0, 2(r7)
/* 00604C 8000B5EC 81030000 */  lwz     r8, 0(r3)
/* 006050 8000B5F0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 006054 8000B5F4 7C040E70 */  srawi   r4, r0, 1
/* 006058 8000B5F8 A0070000 */  lhz     r0, 0(r7)
/* 00605C 8000B5FC 7C840194 */  addze   r4, r4
/* 006060 8000B600 80BB0000 */  lwz     r5, 0(r27)
/* 006064 8000B604 208400A0 */  subfic  r4, r4, 0xa0
/* 006068 8000B608 7C000E70 */  srawi   r0, r0, 1
/* 00606C 8000B60C A1080002 */  lhz     r8, 2(r8)
/* 006070 8000B610 80E50000 */  lwz     r7, 0(r5)
/* 006074 8000B614 7C000194 */  addze   r0, r0
/* 006078 8000B618 20A00078 */  subfic  r5, r0, 0x78
/* 00607C 8000B61C A0070000 */  lhz     r0, 0(r7)
/* 006080 8000B620 7D070E70 */  srawi   r7, r8, 1
/* 006084 8000B624 7CE70194 */  addze   r7, r7
/* 006088 8000B628 20E700A0 */  subfic  r7, r7, 0xa0
/* 00608C 8000B62C 7C000E70 */  srawi   r0, r0, 1
/* 006090 8000B630 7C000194 */  addze   r0, r0
/* 006094 8000B634 387E01A0 */  addi    r3, r30, 0x1a0
/* 006098 8000B638 210000B4 */  subfic  r8, r0, 0xb4
/* 00609C 8000B63C 38C6DE00 */  addi    r6, r6, -8704
/* 0060A0 8000B640 48001F4D */  bl      simulatorDrawOKImage
/* 0060A4 8000B644 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 0060A8 8000B648 2C000001 */  cmpwi   r0, 1
/* 0060AC 8000B64C 40820020 */  bne     lbl_8000B66C
/* 0060B0 8000B650 480ABA3D */  bl      DEMOPadRead
/* 0060B4 8000B654 3C608013 */  lis     r3, DemoPad@ha
/* 0060B8 8000B658 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 0060BC 8000B65C 28000000 */  cmplwi  r0, 0
/* 0060C0 8000B660 4182000C */  beq     lbl_8000B66C
/* 0060C4 8000B664 38600000 */  li      r3, 0
/* 0060C8 8000B668 48001500 */  b       lbl_8000CB68
lbl_8000B66C:
/* 0060CC 8000B66C 38000000 */  li      r0, 0
/* 0060D0 8000B670 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 0060D4 8000B674 480ABA19 */  bl      DEMOPadRead
/* 0060D8 8000B678 80BD0000 */  lwz     r5, 0(r29)
/* 0060DC 8000B67C 3CDF0001 */  addis   r6, r31, 1
/* 0060E0 8000B680 809C0000 */  lwz     r4, 0(r28)
/* 0060E4 8000B684 387E01A0 */  addi    r3, r30, 0x1a0
/* 0060E8 8000B688 80A50000 */  lwz     r5, 0(r5)
/* 0060EC 8000B68C 80E40000 */  lwz     r7, 0(r4)
/* 0060F0 8000B690 38C6DE00 */  addi    r6, r6, -8704
/* 0060F4 8000B694 A0050002 */  lhz     r0, 2(r5)
/* 0060F8 8000B698 809B0000 */  lwz     r4, 0(r27)
/* 0060FC 8000B69C 7C080E70 */  srawi   r8, r0, 1
/* 006100 8000B6A0 A0050000 */  lhz     r0, 0(r5)
/* 006104 8000B6A4 7D080194 */  addze   r8, r8
/* 006108 8000B6A8 80A40000 */  lwz     r5, 0(r4)
/* 00610C 8000B6AC 208800A0 */  subfic  r4, r8, 0xa0
/* 006110 8000B6B0 A0E70002 */  lhz     r7, 2(r7)
/* 006114 8000B6B4 7C080E70 */  srawi   r8, r0, 1
/* 006118 8000B6B8 A0050000 */  lhz     r0, 0(r5)
/* 00611C 8000B6BC 7D080194 */  addze   r8, r8
/* 006120 8000B6C0 20A80078 */  subfic  r5, r8, 0x78
/* 006124 8000B6C4 7CE70E70 */  srawi   r7, r7, 1
/* 006128 8000B6C8 7CE70194 */  addze   r7, r7
/* 00612C 8000B6CC 20E700A0 */  subfic  r7, r7, 0xa0
/* 006130 8000B6D0 7C000E70 */  srawi   r0, r0, 1
/* 006134 8000B6D4 7C000194 */  addze   r0, r0
/* 006138 8000B6D8 210000B4 */  subfic  r8, r0, 0xb4
/* 00613C 8000B6DC 48001EB1 */  bl      simulatorDrawOKImage
/* 006140 8000B6E0 3C608013 */  lis     r3, DemoPad@ha
/* 006144 8000B6E4 38632758 */  addi    r3, r3, DemoPad@l
/* 006148 8000B6E8 8803000A */  lbz     r0, 0xa(r3)
/* 00614C 8000B6EC 7C000775 */  extsb.  r0, r0
/* 006150 8000B6F0 4082002C */  bne     lbl_8000B71C
/* 006154 8000B6F4 A0030000 */  lhz     r0, 0(r3)
/* 006158 8000B6F8 70001100 */  andi.   r0, r0, 0x1100
/* 00615C 8000B6FC 41820020 */  beq     lbl_8000B71C
/* 006160 8000B700 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 006164 8000B704 38800000 */  li      r4, 0
/* 006168 8000B708 80630004 */  lwz     r3, 4(r3)
/* 00616C 8000B70C 48010F85 */  bl      soundPlayBeep
/* 006170 8000B710 38600001 */  li      r3, 1
/* 006174 8000B714 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 006178 8000B718 48001450 */  b       lbl_8000CB68
lbl_8000B71C:
/* 00617C 8000B71C 38600000 */  li      r3, 0
/* 006180 8000B720 48001448 */  b       lbl_8000CB68
glabel lbl_8000B724
/* 006184 8000B724 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 006188 8000B728 7C001800 */  cmpw    r0, r3
/* 00618C 8000B72C 41820050 */  beq     lbl_8000B77C
/* 006190 8000B730 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 006194 8000B734 3C7F0001 */  addis   r3, r31, 1
/* 006198 8000B738 3863E668 */  addi    r3, r3, -6552
/* 00619C 8000B73C 38810080 */  addi    r4, r1, 0x80
/* 0061A0 8000B740 480A72F5 */  bl      DVDOpen
/* 0061A4 8000B744 2C030001 */  cmpwi   r3, 1
/* 0061A8 8000B748 40820024 */  bne     lbl_8000B76C
/* 0061AC 8000B74C 80AD8068 */  lwz     r5, gmsg_sv02Size@sda21(r13)
/* 0061B0 8000B750 38610080 */  addi    r3, r1, 0x80
/* 0061B4 8000B754 389E01A0 */  addi    r4, r30, 0x1a0
/* 0061B8 8000B758 3805001F */  addi    r0, r5, 0x1f
/* 0061BC 8000B75C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0061C0 8000B760 38C00000 */  li      r6, 0
/* 0061C4 8000B764 38E00000 */  li      r7, 0
/* 0061C8 8000B768 4800355D */  bl      simulatorDVDRead
lbl_8000B76C:
/* 0061CC 8000B76C 38610080 */  addi    r3, r1, 0x80
/* 0061D0 8000B770 480A738D */  bl      DVDClose
/* 0061D4 8000B774 387E01A0 */  addi    r3, r30, 0x1a0
/* 0061D8 8000B778 480038A9 */  bl      simulatorUnpackTexPalette
lbl_8000B77C:
/* 0061DC 8000B77C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 0061E0 8000B780 3C7F0001 */  addis   r3, r31, 1
/* 0061E4 8000B784 3B63D248 */  addi    r27, r3, -11704
/* 0061E8 8000B788 80E40000 */  lwz     r7, 0(r4)
/* 0061EC 8000B78C 3B83DE08 */  addi    r28, r3, -8696
/* 0061F0 8000B790 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 0061F4 8000B794 3CDF0001 */  addis   r6, r31, 1
/* 0061F8 8000B798 A0070002 */  lhz     r0, 2(r7)
/* 0061FC 8000B79C 81030000 */  lwz     r8, 0(r3)
/* 006200 8000B7A0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 006204 8000B7A4 7C040E70 */  srawi   r4, r0, 1
/* 006208 8000B7A8 A0070000 */  lhz     r0, 0(r7)
/* 00620C 8000B7AC 7C840194 */  addze   r4, r4
/* 006210 8000B7B0 80BB0000 */  lwz     r5, 0(r27)
/* 006214 8000B7B4 208400A0 */  subfic  r4, r4, 0xa0
/* 006218 8000B7B8 7C000E70 */  srawi   r0, r0, 1
/* 00621C 8000B7BC A1080002 */  lhz     r8, 2(r8)
/* 006220 8000B7C0 80E50000 */  lwz     r7, 0(r5)
/* 006224 8000B7C4 7C000194 */  addze   r0, r0
/* 006228 8000B7C8 20A00078 */  subfic  r5, r0, 0x78
/* 00622C 8000B7CC A0070000 */  lhz     r0, 0(r7)
/* 006230 8000B7D0 7D070E70 */  srawi   r7, r8, 1
/* 006234 8000B7D4 7CE70194 */  addze   r7, r7
/* 006238 8000B7D8 20E700A0 */  subfic  r7, r7, 0xa0
/* 00623C 8000B7DC 7C000E70 */  srawi   r0, r0, 1
/* 006240 8000B7E0 7C000194 */  addze   r0, r0
/* 006244 8000B7E4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006248 8000B7E8 210000B4 */  subfic  r8, r0, 0xb4
/* 00624C 8000B7EC 38C6DE00 */  addi    r6, r6, -8704
/* 006250 8000B7F0 48001D9D */  bl      simulatorDrawOKImage
/* 006254 8000B7F4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 006258 8000B7F8 2C000001 */  cmpwi   r0, 1
/* 00625C 8000B7FC 40820020 */  bne     lbl_8000B81C
/* 006260 8000B800 480AB88D */  bl      DEMOPadRead
/* 006264 8000B804 3C608013 */  lis     r3, DemoPad@ha
/* 006268 8000B808 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00626C 8000B80C 28000000 */  cmplwi  r0, 0
/* 006270 8000B810 4182000C */  beq     lbl_8000B81C
/* 006274 8000B814 38600000 */  li      r3, 0
/* 006278 8000B818 48001350 */  b       lbl_8000CB68
lbl_8000B81C:
/* 00627C 8000B81C 38000000 */  li      r0, 0
/* 006280 8000B820 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 006284 8000B824 480AB869 */  bl      DEMOPadRead
/* 006288 8000B828 80BD0000 */  lwz     r5, 0(r29)
/* 00628C 8000B82C 3CDF0001 */  addis   r6, r31, 1
/* 006290 8000B830 809C0000 */  lwz     r4, 0(r28)
/* 006294 8000B834 387E01A0 */  addi    r3, r30, 0x1a0
/* 006298 8000B838 80A50000 */  lwz     r5, 0(r5)
/* 00629C 8000B83C 80E40000 */  lwz     r7, 0(r4)
/* 0062A0 8000B840 38C6DE00 */  addi    r6, r6, -8704
/* 0062A4 8000B844 A0050002 */  lhz     r0, 2(r5)
/* 0062A8 8000B848 809B0000 */  lwz     r4, 0(r27)
/* 0062AC 8000B84C 7C080E70 */  srawi   r8, r0, 1
/* 0062B0 8000B850 A0050000 */  lhz     r0, 0(r5)
/* 0062B4 8000B854 7D080194 */  addze   r8, r8
/* 0062B8 8000B858 80A40000 */  lwz     r5, 0(r4)
/* 0062BC 8000B85C 208800A0 */  subfic  r4, r8, 0xa0
/* 0062C0 8000B860 A0E70002 */  lhz     r7, 2(r7)
/* 0062C4 8000B864 7C080E70 */  srawi   r8, r0, 1
/* 0062C8 8000B868 A0050000 */  lhz     r0, 0(r5)
/* 0062CC 8000B86C 7D080194 */  addze   r8, r8
/* 0062D0 8000B870 20A80078 */  subfic  r5, r8, 0x78
/* 0062D4 8000B874 7CE70E70 */  srawi   r7, r7, 1
/* 0062D8 8000B878 7CE70194 */  addze   r7, r7
/* 0062DC 8000B87C 20E700A0 */  subfic  r7, r7, 0xa0
/* 0062E0 8000B880 7C000E70 */  srawi   r0, r0, 1
/* 0062E4 8000B884 7C000194 */  addze   r0, r0
/* 0062E8 8000B888 210000B4 */  subfic  r8, r0, 0xb4
/* 0062EC 8000B88C 48001D01 */  bl      simulatorDrawOKImage
/* 0062F0 8000B890 3C608013 */  lis     r3, DemoPad@ha
/* 0062F4 8000B894 38632758 */  addi    r3, r3, DemoPad@l
/* 0062F8 8000B898 8803000A */  lbz     r0, 0xa(r3)
/* 0062FC 8000B89C 7C000775 */  extsb.  r0, r0
/* 006300 8000B8A0 4082002C */  bne     lbl_8000B8CC
/* 006304 8000B8A4 A0030000 */  lhz     r0, 0(r3)
/* 006308 8000B8A8 70001100 */  andi.   r0, r0, 0x1100
/* 00630C 8000B8AC 41820020 */  beq     lbl_8000B8CC
/* 006310 8000B8B0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 006314 8000B8B4 38800000 */  li      r4, 0
/* 006318 8000B8B8 80630004 */  lwz     r3, 4(r3)
/* 00631C 8000B8BC 48010DD5 */  bl      soundPlayBeep
/* 006320 8000B8C0 38600001 */  li      r3, 1
/* 006324 8000B8C4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 006328 8000B8C8 480012A0 */  b       lbl_8000CB68
lbl_8000B8CC:
/* 00632C 8000B8CC 38600000 */  li      r3, 0
/* 006330 8000B8D0 48001298 */  b       lbl_8000CB68
glabel lbl_8000B8D4
/* 006334 8000B8D4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 006338 8000B8D8 7C001800 */  cmpw    r0, r3
/* 00633C 8000B8DC 41820050 */  beq     lbl_8000B92C
/* 006340 8000B8E0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 006344 8000B8E4 3C7F0001 */  addis   r3, r31, 1
/* 006348 8000B8E8 3863E67C */  addi    r3, r3, -6532
/* 00634C 8000B8EC 38810080 */  addi    r4, r1, 0x80
/* 006350 8000B8F0 480A7145 */  bl      DVDOpen
/* 006354 8000B8F4 2C030001 */  cmpwi   r3, 1
/* 006358 8000B8F8 40820024 */  bne     lbl_8000B91C
/* 00635C 8000B8FC 80AD806C */  lwz     r5, gmsg_sv03Size@sda21(r13)
/* 006360 8000B900 38610080 */  addi    r3, r1, 0x80
/* 006364 8000B904 389E01A0 */  addi    r4, r30, 0x1a0
/* 006368 8000B908 3805001F */  addi    r0, r5, 0x1f
/* 00636C 8000B90C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 006370 8000B910 38C00000 */  li      r6, 0
/* 006374 8000B914 38E00000 */  li      r7, 0
/* 006378 8000B918 480033AD */  bl      simulatorDVDRead
lbl_8000B91C:
/* 00637C 8000B91C 38610080 */  addi    r3, r1, 0x80
/* 006380 8000B920 480A71DD */  bl      DVDClose
/* 006384 8000B924 387E01A0 */  addi    r3, r30, 0x1a0
/* 006388 8000B928 480036F9 */  bl      simulatorUnpackTexPalette
lbl_8000B92C:
/* 00638C 8000B92C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 006390 8000B930 3C7F0001 */  addis   r3, r31, 1
/* 006394 8000B934 3B63D248 */  addi    r27, r3, -11704
/* 006398 8000B938 80E40000 */  lwz     r7, 0(r4)
/* 00639C 8000B93C 3B83DE08 */  addi    r28, r3, -8696
/* 0063A0 8000B940 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 0063A4 8000B944 3CDF0001 */  addis   r6, r31, 1
/* 0063A8 8000B948 A0070002 */  lhz     r0, 2(r7)
/* 0063AC 8000B94C 81030000 */  lwz     r8, 0(r3)
/* 0063B0 8000B950 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 0063B4 8000B954 7C040E70 */  srawi   r4, r0, 1
/* 0063B8 8000B958 A0070000 */  lhz     r0, 0(r7)
/* 0063BC 8000B95C 7C840194 */  addze   r4, r4
/* 0063C0 8000B960 80BB0000 */  lwz     r5, 0(r27)
/* 0063C4 8000B964 208400A0 */  subfic  r4, r4, 0xa0
/* 0063C8 8000B968 7C000E70 */  srawi   r0, r0, 1
/* 0063CC 8000B96C A1080002 */  lhz     r8, 2(r8)
/* 0063D0 8000B970 80E50000 */  lwz     r7, 0(r5)
/* 0063D4 8000B974 7C000194 */  addze   r0, r0
/* 0063D8 8000B978 20A00078 */  subfic  r5, r0, 0x78
/* 0063DC 8000B97C A0070000 */  lhz     r0, 0(r7)
/* 0063E0 8000B980 7D070E70 */  srawi   r7, r8, 1
/* 0063E4 8000B984 7CE70194 */  addze   r7, r7
/* 0063E8 8000B988 20E700A0 */  subfic  r7, r7, 0xa0
/* 0063EC 8000B98C 7C000E70 */  srawi   r0, r0, 1
/* 0063F0 8000B990 7C000194 */  addze   r0, r0
/* 0063F4 8000B994 387E01A0 */  addi    r3, r30, 0x1a0
/* 0063F8 8000B998 210000B4 */  subfic  r8, r0, 0xb4
/* 0063FC 8000B99C 38C6DE00 */  addi    r6, r6, -8704
/* 006400 8000B9A0 48001BED */  bl      simulatorDrawOKImage
/* 006404 8000B9A4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 006408 8000B9A8 2C000001 */  cmpwi   r0, 1
/* 00640C 8000B9AC 40820020 */  bne     lbl_8000B9CC
/* 006410 8000B9B0 480AB6DD */  bl      DEMOPadRead
/* 006414 8000B9B4 3C608013 */  lis     r3, DemoPad@ha
/* 006418 8000B9B8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00641C 8000B9BC 28000000 */  cmplwi  r0, 0
/* 006420 8000B9C0 4182000C */  beq     lbl_8000B9CC
/* 006424 8000B9C4 38600000 */  li      r3, 0
/* 006428 8000B9C8 480011A0 */  b       lbl_8000CB68
lbl_8000B9CC:
/* 00642C 8000B9CC 38000000 */  li      r0, 0
/* 006430 8000B9D0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 006434 8000B9D4 480AB6B9 */  bl      DEMOPadRead
/* 006438 8000B9D8 80BD0000 */  lwz     r5, 0(r29)
/* 00643C 8000B9DC 3CDF0001 */  addis   r6, r31, 1
/* 006440 8000B9E0 809C0000 */  lwz     r4, 0(r28)
/* 006444 8000B9E4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006448 8000B9E8 80A50000 */  lwz     r5, 0(r5)
/* 00644C 8000B9EC 80E40000 */  lwz     r7, 0(r4)
/* 006450 8000B9F0 38C6DE00 */  addi    r6, r6, -8704
/* 006454 8000B9F4 A0050002 */  lhz     r0, 2(r5)
/* 006458 8000B9F8 809B0000 */  lwz     r4, 0(r27)
/* 00645C 8000B9FC 7C080E70 */  srawi   r8, r0, 1
/* 006460 8000BA00 A0050000 */  lhz     r0, 0(r5)
/* 006464 8000BA04 7D080194 */  addze   r8, r8
/* 006468 8000BA08 80A40000 */  lwz     r5, 0(r4)
/* 00646C 8000BA0C 208800A0 */  subfic  r4, r8, 0xa0
/* 006470 8000BA10 A0E70002 */  lhz     r7, 2(r7)
/* 006474 8000BA14 7C080E70 */  srawi   r8, r0, 1
/* 006478 8000BA18 A0050000 */  lhz     r0, 0(r5)
/* 00647C 8000BA1C 7D080194 */  addze   r8, r8
/* 006480 8000BA20 20A80078 */  subfic  r5, r8, 0x78
/* 006484 8000BA24 7CE70E70 */  srawi   r7, r7, 1
/* 006488 8000BA28 7CE70194 */  addze   r7, r7
/* 00648C 8000BA2C 20E700A0 */  subfic  r7, r7, 0xa0
/* 006490 8000BA30 7C000E70 */  srawi   r0, r0, 1
/* 006494 8000BA34 7C000194 */  addze   r0, r0
/* 006498 8000BA38 210000B4 */  subfic  r8, r0, 0xb4
/* 00649C 8000BA3C 48001B51 */  bl      simulatorDrawOKImage
/* 0064A0 8000BA40 3C608013 */  lis     r3, DemoPad@ha
/* 0064A4 8000BA44 38632758 */  addi    r3, r3, DemoPad@l
/* 0064A8 8000BA48 8803000A */  lbz     r0, 0xa(r3)
/* 0064AC 8000BA4C 7C000775 */  extsb.  r0, r0
/* 0064B0 8000BA50 4082002C */  bne     lbl_8000BA7C
/* 0064B4 8000BA54 A0030000 */  lhz     r0, 0(r3)
/* 0064B8 8000BA58 70001100 */  andi.   r0, r0, 0x1100
/* 0064BC 8000BA5C 41820020 */  beq     lbl_8000BA7C
/* 0064C0 8000BA60 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 0064C4 8000BA64 38800000 */  li      r4, 0
/* 0064C8 8000BA68 80630004 */  lwz     r3, 4(r3)
/* 0064CC 8000BA6C 48010C25 */  bl      soundPlayBeep
/* 0064D0 8000BA70 38600001 */  li      r3, 1
/* 0064D4 8000BA74 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 0064D8 8000BA78 480010F0 */  b       lbl_8000CB68
lbl_8000BA7C:
/* 0064DC 8000BA7C 38600000 */  li      r3, 0
/* 0064E0 8000BA80 480010E8 */  b       lbl_8000CB68
glabel lbl_8000BA84
/* 0064E4 8000BA84 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0064E8 8000BA88 7C001800 */  cmpw    r0, r3
/* 0064EC 8000BA8C 41820050 */  beq     lbl_8000BADC
/* 0064F0 8000BA90 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0064F4 8000BA94 3C7F0001 */  addis   r3, r31, 1
/* 0064F8 8000BA98 3863E690 */  addi    r3, r3, -6512
/* 0064FC 8000BA9C 38810080 */  addi    r4, r1, 0x80
/* 006500 8000BAA0 480A6F95 */  bl      DVDOpen
/* 006504 8000BAA4 2C030001 */  cmpwi   r3, 1
/* 006508 8000BAA8 40820024 */  bne     lbl_8000BACC
/* 00650C 8000BAAC 80AD8070 */  lwz     r5, gmsg_sv04Size@sda21(r13)
/* 006510 8000BAB0 38610080 */  addi    r3, r1, 0x80
/* 006514 8000BAB4 389E01A0 */  addi    r4, r30, 0x1a0
/* 006518 8000BAB8 3805001F */  addi    r0, r5, 0x1f
/* 00651C 8000BABC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 006520 8000BAC0 38C00000 */  li      r6, 0
/* 006524 8000BAC4 38E00000 */  li      r7, 0
/* 006528 8000BAC8 480031FD */  bl      simulatorDVDRead
lbl_8000BACC:
/* 00652C 8000BACC 38610080 */  addi    r3, r1, 0x80
/* 006530 8000BAD0 480A702D */  bl      DVDClose
/* 006534 8000BAD4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006538 8000BAD8 48003549 */  bl      simulatorUnpackTexPalette
lbl_8000BADC:
/* 00653C 8000BADC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 006540 8000BAE0 3C7F0001 */  addis   r3, r31, 1
/* 006544 8000BAE4 3B63D248 */  addi    r27, r3, -11704
/* 006548 8000BAE8 80E40000 */  lwz     r7, 0(r4)
/* 00654C 8000BAEC 3B83DE08 */  addi    r28, r3, -8696
/* 006550 8000BAF0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 006554 8000BAF4 3CDF0001 */  addis   r6, r31, 1
/* 006558 8000BAF8 A0070002 */  lhz     r0, 2(r7)
/* 00655C 8000BAFC 81030000 */  lwz     r8, 0(r3)
/* 006560 8000BB00 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 006564 8000BB04 7C040E70 */  srawi   r4, r0, 1
/* 006568 8000BB08 A0070000 */  lhz     r0, 0(r7)
/* 00656C 8000BB0C 7C840194 */  addze   r4, r4
/* 006570 8000BB10 80BB0000 */  lwz     r5, 0(r27)
/* 006574 8000BB14 208400A0 */  subfic  r4, r4, 0xa0
/* 006578 8000BB18 7C000E70 */  srawi   r0, r0, 1
/* 00657C 8000BB1C A1080002 */  lhz     r8, 2(r8)
/* 006580 8000BB20 80E50000 */  lwz     r7, 0(r5)
/* 006584 8000BB24 7C000194 */  addze   r0, r0
/* 006588 8000BB28 20A00078 */  subfic  r5, r0, 0x78
/* 00658C 8000BB2C A0070000 */  lhz     r0, 0(r7)
/* 006590 8000BB30 7D070E70 */  srawi   r7, r8, 1
/* 006594 8000BB34 7CE70194 */  addze   r7, r7
/* 006598 8000BB38 20E700A0 */  subfic  r7, r7, 0xa0
/* 00659C 8000BB3C 7C000E70 */  srawi   r0, r0, 1
/* 0065A0 8000BB40 7C000194 */  addze   r0, r0
/* 0065A4 8000BB44 387E01A0 */  addi    r3, r30, 0x1a0
/* 0065A8 8000BB48 210000B4 */  subfic  r8, r0, 0xb4
/* 0065AC 8000BB4C 38C6DE00 */  addi    r6, r6, -8704
/* 0065B0 8000BB50 48001A3D */  bl      simulatorDrawOKImage
/* 0065B4 8000BB54 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 0065B8 8000BB58 2C000001 */  cmpwi   r0, 1
/* 0065BC 8000BB5C 40820020 */  bne     lbl_8000BB7C
/* 0065C0 8000BB60 480AB52D */  bl      DEMOPadRead
/* 0065C4 8000BB64 3C608013 */  lis     r3, DemoPad@ha
/* 0065C8 8000BB68 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 0065CC 8000BB6C 28000000 */  cmplwi  r0, 0
/* 0065D0 8000BB70 4182000C */  beq     lbl_8000BB7C
/* 0065D4 8000BB74 38600000 */  li      r3, 0
/* 0065D8 8000BB78 48000FF0 */  b       lbl_8000CB68
lbl_8000BB7C:
/* 0065DC 8000BB7C 38000000 */  li      r0, 0
/* 0065E0 8000BB80 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 0065E4 8000BB84 480AB509 */  bl      DEMOPadRead
/* 0065E8 8000BB88 80BD0000 */  lwz     r5, 0(r29)
/* 0065EC 8000BB8C 3CDF0001 */  addis   r6, r31, 1
/* 0065F0 8000BB90 809C0000 */  lwz     r4, 0(r28)
/* 0065F4 8000BB94 387E01A0 */  addi    r3, r30, 0x1a0
/* 0065F8 8000BB98 80A50000 */  lwz     r5, 0(r5)
/* 0065FC 8000BB9C 80E40000 */  lwz     r7, 0(r4)
/* 006600 8000BBA0 38C6DE00 */  addi    r6, r6, -8704
/* 006604 8000BBA4 A0050002 */  lhz     r0, 2(r5)
/* 006608 8000BBA8 809B0000 */  lwz     r4, 0(r27)
/* 00660C 8000BBAC 7C080E70 */  srawi   r8, r0, 1
/* 006610 8000BBB0 A0050000 */  lhz     r0, 0(r5)
/* 006614 8000BBB4 7D080194 */  addze   r8, r8
/* 006618 8000BBB8 80A40000 */  lwz     r5, 0(r4)
/* 00661C 8000BBBC 208800A0 */  subfic  r4, r8, 0xa0
/* 006620 8000BBC0 A0E70002 */  lhz     r7, 2(r7)
/* 006624 8000BBC4 7C080E70 */  srawi   r8, r0, 1
/* 006628 8000BBC8 A0050000 */  lhz     r0, 0(r5)
/* 00662C 8000BBCC 7D080194 */  addze   r8, r8
/* 006630 8000BBD0 20A80078 */  subfic  r5, r8, 0x78
/* 006634 8000BBD4 7CE70E70 */  srawi   r7, r7, 1
/* 006638 8000BBD8 7CE70194 */  addze   r7, r7
/* 00663C 8000BBDC 20E700A0 */  subfic  r7, r7, 0xa0
/* 006640 8000BBE0 7C000E70 */  srawi   r0, r0, 1
/* 006644 8000BBE4 7C000194 */  addze   r0, r0
/* 006648 8000BBE8 210000B4 */  subfic  r8, r0, 0xb4
/* 00664C 8000BBEC 480019A1 */  bl      simulatorDrawOKImage
/* 006650 8000BBF0 3C608013 */  lis     r3, DemoPad@ha
/* 006654 8000BBF4 38632758 */  addi    r3, r3, DemoPad@l
/* 006658 8000BBF8 8803000A */  lbz     r0, 0xa(r3)
/* 00665C 8000BBFC 7C000775 */  extsb.  r0, r0
/* 006660 8000BC00 4082002C */  bne     lbl_8000BC2C
/* 006664 8000BC04 A0030000 */  lhz     r0, 0(r3)
/* 006668 8000BC08 70001100 */  andi.   r0, r0, 0x1100
/* 00666C 8000BC0C 41820020 */  beq     lbl_8000BC2C
/* 006670 8000BC10 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 006674 8000BC14 38800000 */  li      r4, 0
/* 006678 8000BC18 80630004 */  lwz     r3, 4(r3)
/* 00667C 8000BC1C 48010A75 */  bl      soundPlayBeep
/* 006680 8000BC20 38600001 */  li      r3, 1
/* 006684 8000BC24 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 006688 8000BC28 48000F40 */  b       lbl_8000CB68
lbl_8000BC2C:
/* 00668C 8000BC2C 38600000 */  li      r3, 0
/* 006690 8000BC30 48000F38 */  b       lbl_8000CB68
glabel lbl_8000BC34
/* 006694 8000BC34 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 006698 8000BC38 7C001800 */  cmpw    r0, r3
/* 00669C 8000BC3C 41820050 */  beq     lbl_8000BC8C
/* 0066A0 8000BC40 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0066A4 8000BC44 3C7F0001 */  addis   r3, r31, 1
/* 0066A8 8000BC48 3863E6A4 */  addi    r3, r3, -6492
/* 0066AC 8000BC4C 38810080 */  addi    r4, r1, 0x80
/* 0066B0 8000BC50 480A6DE5 */  bl      DVDOpen
/* 0066B4 8000BC54 2C030001 */  cmpwi   r3, 1
/* 0066B8 8000BC58 40820024 */  bne     lbl_8000BC7C
/* 0066BC 8000BC5C 80AD8074 */  lwz     r5, gmsg_sv05_1Size@sda21(r13)
/* 0066C0 8000BC60 38610080 */  addi    r3, r1, 0x80
/* 0066C4 8000BC64 389E01A0 */  addi    r4, r30, 0x1a0
/* 0066C8 8000BC68 3805001F */  addi    r0, r5, 0x1f
/* 0066CC 8000BC6C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0066D0 8000BC70 38C00000 */  li      r6, 0
/* 0066D4 8000BC74 38E00000 */  li      r7, 0
/* 0066D8 8000BC78 4800304D */  bl      simulatorDVDRead
lbl_8000BC7C:
/* 0066DC 8000BC7C 38610080 */  addi    r3, r1, 0x80
/* 0066E0 8000BC80 480A6E7D */  bl      DVDClose
/* 0066E4 8000BC84 387E01A0 */  addi    r3, r30, 0x1a0
/* 0066E8 8000BC88 48003399 */  bl      simulatorUnpackTexPalette
lbl_8000BC8C:
/* 0066EC 8000BC8C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 0066F0 8000BC90 3C7F0001 */  addis   r3, r31, 1
/* 0066F4 8000BC94 3B63D248 */  addi    r27, r3, -11704
/* 0066F8 8000BC98 80E40000 */  lwz     r7, 0(r4)
/* 0066FC 8000BC9C 3B83DE08 */  addi    r28, r3, -8696
/* 006700 8000BCA0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 006704 8000BCA4 3CDF0001 */  addis   r6, r31, 1
/* 006708 8000BCA8 A0070002 */  lhz     r0, 2(r7)
/* 00670C 8000BCAC 81030000 */  lwz     r8, 0(r3)
/* 006710 8000BCB0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 006714 8000BCB4 7C040E70 */  srawi   r4, r0, 1
/* 006718 8000BCB8 A0070000 */  lhz     r0, 0(r7)
/* 00671C 8000BCBC 7C840194 */  addze   r4, r4
/* 006720 8000BCC0 80BB0000 */  lwz     r5, 0(r27)
/* 006724 8000BCC4 208400A0 */  subfic  r4, r4, 0xa0
/* 006728 8000BCC8 7C000E70 */  srawi   r0, r0, 1
/* 00672C 8000BCCC A1080002 */  lhz     r8, 2(r8)
/* 006730 8000BCD0 80E50000 */  lwz     r7, 0(r5)
/* 006734 8000BCD4 7C000194 */  addze   r0, r0
/* 006738 8000BCD8 20A00078 */  subfic  r5, r0, 0x78
/* 00673C 8000BCDC A0070000 */  lhz     r0, 0(r7)
/* 006740 8000BCE0 7D070E70 */  srawi   r7, r8, 1
/* 006744 8000BCE4 7CE70194 */  addze   r7, r7
/* 006748 8000BCE8 20E700A0 */  subfic  r7, r7, 0xa0
/* 00674C 8000BCEC 7C000E70 */  srawi   r0, r0, 1
/* 006750 8000BCF0 7C000194 */  addze   r0, r0
/* 006754 8000BCF4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006758 8000BCF8 210000B4 */  subfic  r8, r0, 0xb4
/* 00675C 8000BCFC 38C6DE00 */  addi    r6, r6, -8704
/* 006760 8000BD00 4800188D */  bl      simulatorDrawOKImage
/* 006764 8000BD04 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 006768 8000BD08 2C000001 */  cmpwi   r0, 1
/* 00676C 8000BD0C 40820020 */  bne     lbl_8000BD2C
/* 006770 8000BD10 480AB37D */  bl      DEMOPadRead
/* 006774 8000BD14 3C608013 */  lis     r3, DemoPad@ha
/* 006778 8000BD18 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00677C 8000BD1C 28000000 */  cmplwi  r0, 0
/* 006780 8000BD20 4182000C */  beq     lbl_8000BD2C
/* 006784 8000BD24 38600000 */  li      r3, 0
/* 006788 8000BD28 48000E40 */  b       lbl_8000CB68
lbl_8000BD2C:
/* 00678C 8000BD2C 38000000 */  li      r0, 0
/* 006790 8000BD30 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 006794 8000BD34 480AB359 */  bl      DEMOPadRead
/* 006798 8000BD38 80BD0000 */  lwz     r5, 0(r29)
/* 00679C 8000BD3C 3CDF0001 */  addis   r6, r31, 1
/* 0067A0 8000BD40 809C0000 */  lwz     r4, 0(r28)
/* 0067A4 8000BD44 387E01A0 */  addi    r3, r30, 0x1a0
/* 0067A8 8000BD48 80A50000 */  lwz     r5, 0(r5)
/* 0067AC 8000BD4C 80E40000 */  lwz     r7, 0(r4)
/* 0067B0 8000BD50 38C6DE00 */  addi    r6, r6, -8704
/* 0067B4 8000BD54 A0050002 */  lhz     r0, 2(r5)
/* 0067B8 8000BD58 809B0000 */  lwz     r4, 0(r27)
/* 0067BC 8000BD5C 7C080E70 */  srawi   r8, r0, 1
/* 0067C0 8000BD60 A0050000 */  lhz     r0, 0(r5)
/* 0067C4 8000BD64 7D080194 */  addze   r8, r8
/* 0067C8 8000BD68 80A40000 */  lwz     r5, 0(r4)
/* 0067CC 8000BD6C 208800A0 */  subfic  r4, r8, 0xa0
/* 0067D0 8000BD70 A0E70002 */  lhz     r7, 2(r7)
/* 0067D4 8000BD74 7C080E70 */  srawi   r8, r0, 1
/* 0067D8 8000BD78 A0050000 */  lhz     r0, 0(r5)
/* 0067DC 8000BD7C 7D080194 */  addze   r8, r8
/* 0067E0 8000BD80 20A80078 */  subfic  r5, r8, 0x78
/* 0067E4 8000BD84 7CE70E70 */  srawi   r7, r7, 1
/* 0067E8 8000BD88 7CE70194 */  addze   r7, r7
/* 0067EC 8000BD8C 20E700A0 */  subfic  r7, r7, 0xa0
/* 0067F0 8000BD90 7C000E70 */  srawi   r0, r0, 1
/* 0067F4 8000BD94 7C000194 */  addze   r0, r0
/* 0067F8 8000BD98 210000B4 */  subfic  r8, r0, 0xb4
/* 0067FC 8000BD9C 480017F1 */  bl      simulatorDrawOKImage
/* 006800 8000BDA0 3C608013 */  lis     r3, DemoPad@ha
/* 006804 8000BDA4 38632758 */  addi    r3, r3, DemoPad@l
/* 006808 8000BDA8 8803000A */  lbz     r0, 0xa(r3)
/* 00680C 8000BDAC 7C000775 */  extsb.  r0, r0
/* 006810 8000BDB0 4082002C */  bne     lbl_8000BDDC
/* 006814 8000BDB4 A0030000 */  lhz     r0, 0(r3)
/* 006818 8000BDB8 70001100 */  andi.   r0, r0, 0x1100
/* 00681C 8000BDBC 41820020 */  beq     lbl_8000BDDC
/* 006820 8000BDC0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 006824 8000BDC4 38800000 */  li      r4, 0
/* 006828 8000BDC8 80630004 */  lwz     r3, 4(r3)
/* 00682C 8000BDCC 480108C5 */  bl      soundPlayBeep
/* 006830 8000BDD0 38600001 */  li      r3, 1
/* 006834 8000BDD4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 006838 8000BDD8 48000D90 */  b       lbl_8000CB68
lbl_8000BDDC:
/* 00683C 8000BDDC 38600000 */  li      r3, 0
/* 006840 8000BDE0 48000D88 */  b       lbl_8000CB68
glabel lbl_8000BDE4
/* 006844 8000BDE4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 006848 8000BDE8 7C001800 */  cmpw    r0, r3
/* 00684C 8000BDEC 41820050 */  beq     lbl_8000BE3C
/* 006850 8000BDF0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 006854 8000BDF4 3C7F0001 */  addis   r3, r31, 1
/* 006858 8000BDF8 3863E6B8 */  addi    r3, r3, -6472
/* 00685C 8000BDFC 38810080 */  addi    r4, r1, 0x80
/* 006860 8000BE00 480A6C35 */  bl      DVDOpen
/* 006864 8000BE04 2C030001 */  cmpwi   r3, 1
/* 006868 8000BE08 40820024 */  bne     lbl_8000BE2C
/* 00686C 8000BE0C 80AD8078 */  lwz     r5, gmsg_sv06_1Size@sda21(r13)
/* 006870 8000BE10 38610080 */  addi    r3, r1, 0x80
/* 006874 8000BE14 389E01A0 */  addi    r4, r30, 0x1a0
/* 006878 8000BE18 3805001F */  addi    r0, r5, 0x1f
/* 00687C 8000BE1C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 006880 8000BE20 38C00000 */  li      r6, 0
/* 006884 8000BE24 38E00000 */  li      r7, 0
/* 006888 8000BE28 48002E9D */  bl      simulatorDVDRead
lbl_8000BE2C:
/* 00688C 8000BE2C 38610080 */  addi    r3, r1, 0x80
/* 006890 8000BE30 480A6CCD */  bl      DVDClose
/* 006894 8000BE34 387E01A0 */  addi    r3, r30, 0x1a0
/* 006898 8000BE38 480031E9 */  bl      simulatorUnpackTexPalette
lbl_8000BE3C:
/* 00689C 8000BE3C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 0068A0 8000BE40 3C7F0001 */  addis   r3, r31, 1
/* 0068A4 8000BE44 3B63D248 */  addi    r27, r3, -11704
/* 0068A8 8000BE48 80E40000 */  lwz     r7, 0(r4)
/* 0068AC 8000BE4C 3B83DE08 */  addi    r28, r3, -8696
/* 0068B0 8000BE50 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 0068B4 8000BE54 3CDF0001 */  addis   r6, r31, 1
/* 0068B8 8000BE58 A0070002 */  lhz     r0, 2(r7)
/* 0068BC 8000BE5C 81030000 */  lwz     r8, 0(r3)
/* 0068C0 8000BE60 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 0068C4 8000BE64 7C040E70 */  srawi   r4, r0, 1
/* 0068C8 8000BE68 A0070000 */  lhz     r0, 0(r7)
/* 0068CC 8000BE6C 7C840194 */  addze   r4, r4
/* 0068D0 8000BE70 80BB0000 */  lwz     r5, 0(r27)
/* 0068D4 8000BE74 208400A0 */  subfic  r4, r4, 0xa0
/* 0068D8 8000BE78 7C000E70 */  srawi   r0, r0, 1
/* 0068DC 8000BE7C A1080002 */  lhz     r8, 2(r8)
/* 0068E0 8000BE80 80E50000 */  lwz     r7, 0(r5)
/* 0068E4 8000BE84 7C000194 */  addze   r0, r0
/* 0068E8 8000BE88 20A00078 */  subfic  r5, r0, 0x78
/* 0068EC 8000BE8C A0070000 */  lhz     r0, 0(r7)
/* 0068F0 8000BE90 7D070E70 */  srawi   r7, r8, 1
/* 0068F4 8000BE94 7CE70194 */  addze   r7, r7
/* 0068F8 8000BE98 20E700A0 */  subfic  r7, r7, 0xa0
/* 0068FC 8000BE9C 7C000E70 */  srawi   r0, r0, 1
/* 006900 8000BEA0 7C000194 */  addze   r0, r0
/* 006904 8000BEA4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006908 8000BEA8 210000B4 */  subfic  r8, r0, 0xb4
/* 00690C 8000BEAC 38C6DE00 */  addi    r6, r6, -8704
/* 006910 8000BEB0 480016DD */  bl      simulatorDrawOKImage
/* 006914 8000BEB4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 006918 8000BEB8 2C000001 */  cmpwi   r0, 1
/* 00691C 8000BEBC 40820020 */  bne     lbl_8000BEDC
/* 006920 8000BEC0 480AB1CD */  bl      DEMOPadRead
/* 006924 8000BEC4 3C608013 */  lis     r3, DemoPad@ha
/* 006928 8000BEC8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00692C 8000BECC 28000000 */  cmplwi  r0, 0
/* 006930 8000BED0 4182000C */  beq     lbl_8000BEDC
/* 006934 8000BED4 38600000 */  li      r3, 0
/* 006938 8000BED8 48000C90 */  b       lbl_8000CB68
lbl_8000BEDC:
/* 00693C 8000BEDC 38000000 */  li      r0, 0
/* 006940 8000BEE0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 006944 8000BEE4 480AB1A9 */  bl      DEMOPadRead
/* 006948 8000BEE8 80BD0000 */  lwz     r5, 0(r29)
/* 00694C 8000BEEC 3CDF0001 */  addis   r6, r31, 1
/* 006950 8000BEF0 809C0000 */  lwz     r4, 0(r28)
/* 006954 8000BEF4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006958 8000BEF8 80A50000 */  lwz     r5, 0(r5)
/* 00695C 8000BEFC 80E40000 */  lwz     r7, 0(r4)
/* 006960 8000BF00 38C6DE00 */  addi    r6, r6, -8704
/* 006964 8000BF04 A0050002 */  lhz     r0, 2(r5)
/* 006968 8000BF08 809B0000 */  lwz     r4, 0(r27)
/* 00696C 8000BF0C 7C080E70 */  srawi   r8, r0, 1
/* 006970 8000BF10 A0050000 */  lhz     r0, 0(r5)
/* 006974 8000BF14 7D080194 */  addze   r8, r8
/* 006978 8000BF18 80A40000 */  lwz     r5, 0(r4)
/* 00697C 8000BF1C 208800A0 */  subfic  r4, r8, 0xa0
/* 006980 8000BF20 A0E70002 */  lhz     r7, 2(r7)
/* 006984 8000BF24 7C080E70 */  srawi   r8, r0, 1
/* 006988 8000BF28 A0050000 */  lhz     r0, 0(r5)
/* 00698C 8000BF2C 7D080194 */  addze   r8, r8
/* 006990 8000BF30 20A80078 */  subfic  r5, r8, 0x78
/* 006994 8000BF34 7CE70E70 */  srawi   r7, r7, 1
/* 006998 8000BF38 7CE70194 */  addze   r7, r7
/* 00699C 8000BF3C 20E700A0 */  subfic  r7, r7, 0xa0
/* 0069A0 8000BF40 7C000E70 */  srawi   r0, r0, 1
/* 0069A4 8000BF44 7C000194 */  addze   r0, r0
/* 0069A8 8000BF48 210000B4 */  subfic  r8, r0, 0xb4
/* 0069AC 8000BF4C 48001641 */  bl      simulatorDrawOKImage
/* 0069B0 8000BF50 3C608013 */  lis     r3, DemoPad@ha
/* 0069B4 8000BF54 38632758 */  addi    r3, r3, DemoPad@l
/* 0069B8 8000BF58 8803000A */  lbz     r0, 0xa(r3)
/* 0069BC 8000BF5C 7C000775 */  extsb.  r0, r0
/* 0069C0 8000BF60 4082002C */  bne     lbl_8000BF8C
/* 0069C4 8000BF64 A0030000 */  lhz     r0, 0(r3)
/* 0069C8 8000BF68 70001100 */  andi.   r0, r0, 0x1100
/* 0069CC 8000BF6C 41820020 */  beq     lbl_8000BF8C
/* 0069D0 8000BF70 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 0069D4 8000BF74 38800000 */  li      r4, 0
/* 0069D8 8000BF78 80630004 */  lwz     r3, 4(r3)
/* 0069DC 8000BF7C 48010715 */  bl      soundPlayBeep
/* 0069E0 8000BF80 38600001 */  li      r3, 1
/* 0069E4 8000BF84 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 0069E8 8000BF88 48000BE0 */  b       lbl_8000CB68
lbl_8000BF8C:
/* 0069EC 8000BF8C 38600000 */  li      r3, 0
/* 0069F0 8000BF90 48000BD8 */  b       lbl_8000CB68
glabel lbl_8000BF94
/* 0069F4 8000BF94 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0069F8 8000BF98 7C001800 */  cmpw    r0, r3
/* 0069FC 8000BF9C 41820050 */  beq     lbl_8000BFEC
/* 006A00 8000BFA0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 006A04 8000BFA4 3C7F0001 */  addis   r3, r31, 1
/* 006A08 8000BFA8 3863E6CC */  addi    r3, r3, -6452
/* 006A0C 8000BFAC 38810080 */  addi    r4, r1, 0x80
/* 006A10 8000BFB0 480A6A85 */  bl      DVDOpen
/* 006A14 8000BFB4 2C030001 */  cmpwi   r3, 1
/* 006A18 8000BFB8 40820024 */  bne     lbl_8000BFDC
/* 006A1C 8000BFBC 80AD807C */  lwz     r5, gmsg_sv06_2Size@sda21(r13)
/* 006A20 8000BFC0 38610080 */  addi    r3, r1, 0x80
/* 006A24 8000BFC4 389E01A0 */  addi    r4, r30, 0x1a0
/* 006A28 8000BFC8 3805001F */  addi    r0, r5, 0x1f
/* 006A2C 8000BFCC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 006A30 8000BFD0 38C00000 */  li      r6, 0
/* 006A34 8000BFD4 38E00000 */  li      r7, 0
/* 006A38 8000BFD8 48002CED */  bl      simulatorDVDRead
lbl_8000BFDC:
/* 006A3C 8000BFDC 38610080 */  addi    r3, r1, 0x80
/* 006A40 8000BFE0 480A6B1D */  bl      DVDClose
/* 006A44 8000BFE4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006A48 8000BFE8 48003039 */  bl      simulatorUnpackTexPalette
lbl_8000BFEC:
/* 006A4C 8000BFEC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 006A50 8000BFF0 3C7F0001 */  addis   r3, r31, 1
/* 006A54 8000BFF4 3B63D248 */  addi    r27, r3, -11704
/* 006A58 8000BFF8 80E40000 */  lwz     r7, 0(r4)
/* 006A5C 8000BFFC 3B83DE08 */  addi    r28, r3, -8696
/* 006A60 8000C000 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 006A64 8000C004 3CDF0001 */  addis   r6, r31, 1
/* 006A68 8000C008 A0070002 */  lhz     r0, 2(r7)
/* 006A6C 8000C00C 81030000 */  lwz     r8, 0(r3)
/* 006A70 8000C010 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 006A74 8000C014 7C040E70 */  srawi   r4, r0, 1
/* 006A78 8000C018 A0070000 */  lhz     r0, 0(r7)
/* 006A7C 8000C01C 7C840194 */  addze   r4, r4
/* 006A80 8000C020 80BB0000 */  lwz     r5, 0(r27)
/* 006A84 8000C024 208400A0 */  subfic  r4, r4, 0xa0
/* 006A88 8000C028 7C000E70 */  srawi   r0, r0, 1
/* 006A8C 8000C02C A1080002 */  lhz     r8, 2(r8)
/* 006A90 8000C030 80E50000 */  lwz     r7, 0(r5)
/* 006A94 8000C034 7C000194 */  addze   r0, r0
/* 006A98 8000C038 20A00078 */  subfic  r5, r0, 0x78
/* 006A9C 8000C03C A0070000 */  lhz     r0, 0(r7)
/* 006AA0 8000C040 7D070E70 */  srawi   r7, r8, 1
/* 006AA4 8000C044 7CE70194 */  addze   r7, r7
/* 006AA8 8000C048 20E700A0 */  subfic  r7, r7, 0xa0
/* 006AAC 8000C04C 7C000E70 */  srawi   r0, r0, 1
/* 006AB0 8000C050 7C000194 */  addze   r0, r0
/* 006AB4 8000C054 387E01A0 */  addi    r3, r30, 0x1a0
/* 006AB8 8000C058 210000B4 */  subfic  r8, r0, 0xb4
/* 006ABC 8000C05C 38C6DE00 */  addi    r6, r6, -8704
/* 006AC0 8000C060 4800152D */  bl      simulatorDrawOKImage
/* 006AC4 8000C064 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 006AC8 8000C068 2C000001 */  cmpwi   r0, 1
/* 006ACC 8000C06C 40820020 */  bne     lbl_8000C08C
/* 006AD0 8000C070 480AB01D */  bl      DEMOPadRead
/* 006AD4 8000C074 3C608013 */  lis     r3, DemoPad@ha
/* 006AD8 8000C078 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 006ADC 8000C07C 28000000 */  cmplwi  r0, 0
/* 006AE0 8000C080 4182000C */  beq     lbl_8000C08C
/* 006AE4 8000C084 38600000 */  li      r3, 0
/* 006AE8 8000C088 48000AE0 */  b       lbl_8000CB68
lbl_8000C08C:
/* 006AEC 8000C08C 38000000 */  li      r0, 0
/* 006AF0 8000C090 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 006AF4 8000C094 480AAFF9 */  bl      DEMOPadRead
/* 006AF8 8000C098 80BD0000 */  lwz     r5, 0(r29)
/* 006AFC 8000C09C 3CDF0001 */  addis   r6, r31, 1
/* 006B00 8000C0A0 809C0000 */  lwz     r4, 0(r28)
/* 006B04 8000C0A4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006B08 8000C0A8 80A50000 */  lwz     r5, 0(r5)
/* 006B0C 8000C0AC 80E40000 */  lwz     r7, 0(r4)
/* 006B10 8000C0B0 38C6DE00 */  addi    r6, r6, -8704
/* 006B14 8000C0B4 A0050002 */  lhz     r0, 2(r5)
/* 006B18 8000C0B8 809B0000 */  lwz     r4, 0(r27)
/* 006B1C 8000C0BC 7C080E70 */  srawi   r8, r0, 1
/* 006B20 8000C0C0 A0050000 */  lhz     r0, 0(r5)
/* 006B24 8000C0C4 7D080194 */  addze   r8, r8
/* 006B28 8000C0C8 80A40000 */  lwz     r5, 0(r4)
/* 006B2C 8000C0CC 208800A0 */  subfic  r4, r8, 0xa0
/* 006B30 8000C0D0 A0E70002 */  lhz     r7, 2(r7)
/* 006B34 8000C0D4 7C080E70 */  srawi   r8, r0, 1
/* 006B38 8000C0D8 A0050000 */  lhz     r0, 0(r5)
/* 006B3C 8000C0DC 7D080194 */  addze   r8, r8
/* 006B40 8000C0E0 20A80078 */  subfic  r5, r8, 0x78
/* 006B44 8000C0E4 7CE70E70 */  srawi   r7, r7, 1
/* 006B48 8000C0E8 7CE70194 */  addze   r7, r7
/* 006B4C 8000C0EC 20E700A0 */  subfic  r7, r7, 0xa0
/* 006B50 8000C0F0 7C000E70 */  srawi   r0, r0, 1
/* 006B54 8000C0F4 7C000194 */  addze   r0, r0
/* 006B58 8000C0F8 210000B4 */  subfic  r8, r0, 0xb4
/* 006B5C 8000C0FC 48001491 */  bl      simulatorDrawOKImage
/* 006B60 8000C100 3C608013 */  lis     r3, DemoPad@ha
/* 006B64 8000C104 38632758 */  addi    r3, r3, DemoPad@l
/* 006B68 8000C108 8803000A */  lbz     r0, 0xa(r3)
/* 006B6C 8000C10C 7C000775 */  extsb.  r0, r0
/* 006B70 8000C110 4082002C */  bne     lbl_8000C13C
/* 006B74 8000C114 A0030000 */  lhz     r0, 0(r3)
/* 006B78 8000C118 70001100 */  andi.   r0, r0, 0x1100
/* 006B7C 8000C11C 41820020 */  beq     lbl_8000C13C
/* 006B80 8000C120 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 006B84 8000C124 38800000 */  li      r4, 0
/* 006B88 8000C128 80630004 */  lwz     r3, 4(r3)
/* 006B8C 8000C12C 48010565 */  bl      soundPlayBeep
/* 006B90 8000C130 38600001 */  li      r3, 1
/* 006B94 8000C134 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 006B98 8000C138 48000A30 */  b       lbl_8000CB68
lbl_8000C13C:
/* 006B9C 8000C13C 38600000 */  li      r3, 0
/* 006BA0 8000C140 48000A28 */  b       lbl_8000CB68
glabel lbl_8000C144
/* 006BA4 8000C144 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 006BA8 8000C148 7C001800 */  cmpw    r0, r3
/* 006BAC 8000C14C 41820050 */  beq     lbl_8000C19C
/* 006BB0 8000C150 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 006BB4 8000C154 3C7F0001 */  addis   r3, r31, 1
/* 006BB8 8000C158 3863E6E0 */  addi    r3, r3, -6432
/* 006BBC 8000C15C 38810080 */  addi    r4, r1, 0x80
/* 006BC0 8000C160 480A68D5 */  bl      DVDOpen
/* 006BC4 8000C164 2C030001 */  cmpwi   r3, 1
/* 006BC8 8000C168 40820024 */  bne     lbl_8000C18C
/* 006BCC 8000C16C 80AD8080 */  lwz     r5, gmsg_sv06_3Size@sda21(r13)
/* 006BD0 8000C170 38610080 */  addi    r3, r1, 0x80
/* 006BD4 8000C174 389E01A0 */  addi    r4, r30, 0x1a0
/* 006BD8 8000C178 3805001F */  addi    r0, r5, 0x1f
/* 006BDC 8000C17C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 006BE0 8000C180 38C00000 */  li      r6, 0
/* 006BE4 8000C184 38E00000 */  li      r7, 0
/* 006BE8 8000C188 48002B3D */  bl      simulatorDVDRead
lbl_8000C18C:
/* 006BEC 8000C18C 38610080 */  addi    r3, r1, 0x80
/* 006BF0 8000C190 480A696D */  bl      DVDClose
/* 006BF4 8000C194 387E01A0 */  addi    r3, r30, 0x1a0
/* 006BF8 8000C198 48002E89 */  bl      simulatorUnpackTexPalette
lbl_8000C19C:
/* 006BFC 8000C19C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 006C00 8000C1A0 3C7F0001 */  addis   r3, r31, 1
/* 006C04 8000C1A4 3B63D248 */  addi    r27, r3, -11704
/* 006C08 8000C1A8 80E40000 */  lwz     r7, 0(r4)
/* 006C0C 8000C1AC 3B83DE08 */  addi    r28, r3, -8696
/* 006C10 8000C1B0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 006C14 8000C1B4 3CDF0001 */  addis   r6, r31, 1
/* 006C18 8000C1B8 A0070002 */  lhz     r0, 2(r7)
/* 006C1C 8000C1BC 81030000 */  lwz     r8, 0(r3)
/* 006C20 8000C1C0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 006C24 8000C1C4 7C040E70 */  srawi   r4, r0, 1
/* 006C28 8000C1C8 A0070000 */  lhz     r0, 0(r7)
/* 006C2C 8000C1CC 7C840194 */  addze   r4, r4
/* 006C30 8000C1D0 80BB0000 */  lwz     r5, 0(r27)
/* 006C34 8000C1D4 208400A0 */  subfic  r4, r4, 0xa0
/* 006C38 8000C1D8 7C000E70 */  srawi   r0, r0, 1
/* 006C3C 8000C1DC A1080002 */  lhz     r8, 2(r8)
/* 006C40 8000C1E0 80E50000 */  lwz     r7, 0(r5)
/* 006C44 8000C1E4 7C000194 */  addze   r0, r0
/* 006C48 8000C1E8 20A00078 */  subfic  r5, r0, 0x78
/* 006C4C 8000C1EC A0070000 */  lhz     r0, 0(r7)
/* 006C50 8000C1F0 7D070E70 */  srawi   r7, r8, 1
/* 006C54 8000C1F4 7CE70194 */  addze   r7, r7
/* 006C58 8000C1F8 20E700A0 */  subfic  r7, r7, 0xa0
/* 006C5C 8000C1FC 7C000E70 */  srawi   r0, r0, 1
/* 006C60 8000C200 7C000194 */  addze   r0, r0
/* 006C64 8000C204 387E01A0 */  addi    r3, r30, 0x1a0
/* 006C68 8000C208 210000B4 */  subfic  r8, r0, 0xb4
/* 006C6C 8000C20C 38C6DE00 */  addi    r6, r6, -8704
/* 006C70 8000C210 4800137D */  bl      simulatorDrawOKImage
/* 006C74 8000C214 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 006C78 8000C218 2C000001 */  cmpwi   r0, 1
/* 006C7C 8000C21C 40820020 */  bne     lbl_8000C23C
/* 006C80 8000C220 480AAE6D */  bl      DEMOPadRead
/* 006C84 8000C224 3C608013 */  lis     r3, DemoPad@ha
/* 006C88 8000C228 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 006C8C 8000C22C 28000000 */  cmplwi  r0, 0
/* 006C90 8000C230 4182000C */  beq     lbl_8000C23C
/* 006C94 8000C234 38600000 */  li      r3, 0
/* 006C98 8000C238 48000930 */  b       lbl_8000CB68
lbl_8000C23C:
/* 006C9C 8000C23C 38000000 */  li      r0, 0
/* 006CA0 8000C240 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 006CA4 8000C244 480AAE49 */  bl      DEMOPadRead
/* 006CA8 8000C248 80BD0000 */  lwz     r5, 0(r29)
/* 006CAC 8000C24C 3CDF0001 */  addis   r6, r31, 1
/* 006CB0 8000C250 809C0000 */  lwz     r4, 0(r28)
/* 006CB4 8000C254 387E01A0 */  addi    r3, r30, 0x1a0
/* 006CB8 8000C258 80A50000 */  lwz     r5, 0(r5)
/* 006CBC 8000C25C 80E40000 */  lwz     r7, 0(r4)
/* 006CC0 8000C260 38C6DE00 */  addi    r6, r6, -8704
/* 006CC4 8000C264 A0050002 */  lhz     r0, 2(r5)
/* 006CC8 8000C268 809B0000 */  lwz     r4, 0(r27)
/* 006CCC 8000C26C 7C080E70 */  srawi   r8, r0, 1
/* 006CD0 8000C270 A0050000 */  lhz     r0, 0(r5)
/* 006CD4 8000C274 7D080194 */  addze   r8, r8
/* 006CD8 8000C278 80A40000 */  lwz     r5, 0(r4)
/* 006CDC 8000C27C 208800A0 */  subfic  r4, r8, 0xa0
/* 006CE0 8000C280 A0E70002 */  lhz     r7, 2(r7)
/* 006CE4 8000C284 7C080E70 */  srawi   r8, r0, 1
/* 006CE8 8000C288 A0050000 */  lhz     r0, 0(r5)
/* 006CEC 8000C28C 7D080194 */  addze   r8, r8
/* 006CF0 8000C290 20A80078 */  subfic  r5, r8, 0x78
/* 006CF4 8000C294 7CE70E70 */  srawi   r7, r7, 1
/* 006CF8 8000C298 7CE70194 */  addze   r7, r7
/* 006CFC 8000C29C 20E700A0 */  subfic  r7, r7, 0xa0
/* 006D00 8000C2A0 7C000E70 */  srawi   r0, r0, 1
/* 006D04 8000C2A4 7C000194 */  addze   r0, r0
/* 006D08 8000C2A8 210000B4 */  subfic  r8, r0, 0xb4
/* 006D0C 8000C2AC 480012E1 */  bl      simulatorDrawOKImage
/* 006D10 8000C2B0 3C608013 */  lis     r3, DemoPad@ha
/* 006D14 8000C2B4 38632758 */  addi    r3, r3, DemoPad@l
/* 006D18 8000C2B8 8803000A */  lbz     r0, 0xa(r3)
/* 006D1C 8000C2BC 7C000775 */  extsb.  r0, r0
/* 006D20 8000C2C0 4082002C */  bne     lbl_8000C2EC
/* 006D24 8000C2C4 A0030000 */  lhz     r0, 0(r3)
/* 006D28 8000C2C8 70001100 */  andi.   r0, r0, 0x1100
/* 006D2C 8000C2CC 41820020 */  beq     lbl_8000C2EC
/* 006D30 8000C2D0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 006D34 8000C2D4 38800000 */  li      r4, 0
/* 006D38 8000C2D8 80630004 */  lwz     r3, 4(r3)
/* 006D3C 8000C2DC 480103B5 */  bl      soundPlayBeep
/* 006D40 8000C2E0 38600001 */  li      r3, 1
/* 006D44 8000C2E4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 006D48 8000C2E8 48000880 */  b       lbl_8000CB68
lbl_8000C2EC:
/* 006D4C 8000C2EC 38600000 */  li      r3, 0
/* 006D50 8000C2F0 48000878 */  b       lbl_8000CB68
glabel lbl_8000C2F4
/* 006D54 8000C2F4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 006D58 8000C2F8 7C001800 */  cmpw    r0, r3
/* 006D5C 8000C2FC 41820050 */  beq     lbl_8000C34C
/* 006D60 8000C300 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 006D64 8000C304 3C7F0001 */  addis   r3, r31, 1
/* 006D68 8000C308 3863E6F4 */  addi    r3, r3, -6412
/* 006D6C 8000C30C 38810080 */  addi    r4, r1, 0x80
/* 006D70 8000C310 480A6725 */  bl      DVDOpen
/* 006D74 8000C314 2C030001 */  cmpwi   r3, 1
/* 006D78 8000C318 40820024 */  bne     lbl_8000C33C
/* 006D7C 8000C31C 80AD808C */  lwz     r5, gmsg_sv07Size@sda21(r13)
/* 006D80 8000C320 38610080 */  addi    r3, r1, 0x80
/* 006D84 8000C324 389E01A0 */  addi    r4, r30, 0x1a0
/* 006D88 8000C328 3805001F */  addi    r0, r5, 0x1f
/* 006D8C 8000C32C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 006D90 8000C330 38C00000 */  li      r6, 0
/* 006D94 8000C334 38E00000 */  li      r7, 0
/* 006D98 8000C338 4800298D */  bl      simulatorDVDRead
lbl_8000C33C:
/* 006D9C 8000C33C 38610080 */  addi    r3, r1, 0x80
/* 006DA0 8000C340 480A67BD */  bl      DVDClose
/* 006DA4 8000C344 387E01A0 */  addi    r3, r30, 0x1a0
/* 006DA8 8000C348 48002CD9 */  bl      simulatorUnpackTexPalette
lbl_8000C34C:
/* 006DAC 8000C34C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 006DB0 8000C350 3C7F0001 */  addis   r3, r31, 1
/* 006DB4 8000C354 3B63D248 */  addi    r27, r3, -11704
/* 006DB8 8000C358 80E40000 */  lwz     r7, 0(r4)
/* 006DBC 8000C35C 3B83DE08 */  addi    r28, r3, -8696
/* 006DC0 8000C360 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 006DC4 8000C364 3CDF0001 */  addis   r6, r31, 1
/* 006DC8 8000C368 A0070002 */  lhz     r0, 2(r7)
/* 006DCC 8000C36C 81030000 */  lwz     r8, 0(r3)
/* 006DD0 8000C370 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 006DD4 8000C374 7C040E70 */  srawi   r4, r0, 1
/* 006DD8 8000C378 A0070000 */  lhz     r0, 0(r7)
/* 006DDC 8000C37C 7C840194 */  addze   r4, r4
/* 006DE0 8000C380 80BB0000 */  lwz     r5, 0(r27)
/* 006DE4 8000C384 208400A0 */  subfic  r4, r4, 0xa0
/* 006DE8 8000C388 7C000E70 */  srawi   r0, r0, 1
/* 006DEC 8000C38C A1080002 */  lhz     r8, 2(r8)
/* 006DF0 8000C390 80E50000 */  lwz     r7, 0(r5)
/* 006DF4 8000C394 7C000194 */  addze   r0, r0
/* 006DF8 8000C398 20A00078 */  subfic  r5, r0, 0x78
/* 006DFC 8000C39C A0070000 */  lhz     r0, 0(r7)
/* 006E00 8000C3A0 7D070E70 */  srawi   r7, r8, 1
/* 006E04 8000C3A4 7CE70194 */  addze   r7, r7
/* 006E08 8000C3A8 20E700A0 */  subfic  r7, r7, 0xa0
/* 006E0C 8000C3AC 7C000E70 */  srawi   r0, r0, 1
/* 006E10 8000C3B0 7C000194 */  addze   r0, r0
/* 006E14 8000C3B4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006E18 8000C3B8 210000B4 */  subfic  r8, r0, 0xb4
/* 006E1C 8000C3BC 38C6DE00 */  addi    r6, r6, -8704
/* 006E20 8000C3C0 480011CD */  bl      simulatorDrawOKImage
/* 006E24 8000C3C4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 006E28 8000C3C8 2C000001 */  cmpwi   r0, 1
/* 006E2C 8000C3CC 40820020 */  bne     lbl_8000C3EC
/* 006E30 8000C3D0 480AACBD */  bl      DEMOPadRead
/* 006E34 8000C3D4 3C608013 */  lis     r3, DemoPad@ha
/* 006E38 8000C3D8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 006E3C 8000C3DC 28000000 */  cmplwi  r0, 0
/* 006E40 8000C3E0 4182000C */  beq     lbl_8000C3EC
/* 006E44 8000C3E4 38600000 */  li      r3, 0
/* 006E48 8000C3E8 48000780 */  b       lbl_8000CB68
lbl_8000C3EC:
/* 006E4C 8000C3EC 38000000 */  li      r0, 0
/* 006E50 8000C3F0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 006E54 8000C3F4 480AAC99 */  bl      DEMOPadRead
/* 006E58 8000C3F8 80BD0000 */  lwz     r5, 0(r29)
/* 006E5C 8000C3FC 3CDF0001 */  addis   r6, r31, 1
/* 006E60 8000C400 809C0000 */  lwz     r4, 0(r28)
/* 006E64 8000C404 387E01A0 */  addi    r3, r30, 0x1a0
/* 006E68 8000C408 80A50000 */  lwz     r5, 0(r5)
/* 006E6C 8000C40C 80E40000 */  lwz     r7, 0(r4)
/* 006E70 8000C410 38C6DE00 */  addi    r6, r6, -8704
/* 006E74 8000C414 A0050002 */  lhz     r0, 2(r5)
/* 006E78 8000C418 809B0000 */  lwz     r4, 0(r27)
/* 006E7C 8000C41C 7C080E70 */  srawi   r8, r0, 1
/* 006E80 8000C420 A0050000 */  lhz     r0, 0(r5)
/* 006E84 8000C424 7D080194 */  addze   r8, r8
/* 006E88 8000C428 80A40000 */  lwz     r5, 0(r4)
/* 006E8C 8000C42C 208800A0 */  subfic  r4, r8, 0xa0
/* 006E90 8000C430 A0E70002 */  lhz     r7, 2(r7)
/* 006E94 8000C434 7C080E70 */  srawi   r8, r0, 1
/* 006E98 8000C438 A0050000 */  lhz     r0, 0(r5)
/* 006E9C 8000C43C 7D080194 */  addze   r8, r8
/* 006EA0 8000C440 20A80078 */  subfic  r5, r8, 0x78
/* 006EA4 8000C444 7CE70E70 */  srawi   r7, r7, 1
/* 006EA8 8000C448 7CE70194 */  addze   r7, r7
/* 006EAC 8000C44C 20E700A0 */  subfic  r7, r7, 0xa0
/* 006EB0 8000C450 7C000E70 */  srawi   r0, r0, 1
/* 006EB4 8000C454 7C000194 */  addze   r0, r0
/* 006EB8 8000C458 210000B4 */  subfic  r8, r0, 0xb4
/* 006EBC 8000C45C 48001131 */  bl      simulatorDrawOKImage
/* 006EC0 8000C460 3C608013 */  lis     r3, DemoPad@ha
/* 006EC4 8000C464 38632758 */  addi    r3, r3, DemoPad@l
/* 006EC8 8000C468 8803000A */  lbz     r0, 0xa(r3)
/* 006ECC 8000C46C 7C000775 */  extsb.  r0, r0
/* 006ED0 8000C470 4082002C */  bne     lbl_8000C49C
/* 006ED4 8000C474 A0030000 */  lhz     r0, 0(r3)
/* 006ED8 8000C478 70001100 */  andi.   r0, r0, 0x1100
/* 006EDC 8000C47C 41820020 */  beq     lbl_8000C49C
/* 006EE0 8000C480 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 006EE4 8000C484 38800000 */  li      r4, 0
/* 006EE8 8000C488 80630004 */  lwz     r3, 4(r3)
/* 006EEC 8000C48C 48010205 */  bl      soundPlayBeep
/* 006EF0 8000C490 38600001 */  li      r3, 1
/* 006EF4 8000C494 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 006EF8 8000C498 480006D0 */  b       lbl_8000CB68
lbl_8000C49C:
/* 006EFC 8000C49C 38600000 */  li      r3, 0
/* 006F00 8000C4A0 480006C8 */  b       lbl_8000CB68
glabel lbl_8000C4A4
/* 006F04 8000C4A4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 006F08 8000C4A8 7C001800 */  cmpw    r0, r3
/* 006F0C 8000C4AC 41820050 */  beq     lbl_8000C4FC
/* 006F10 8000C4B0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 006F14 8000C4B4 3C7F0001 */  addis   r3, r31, 1
/* 006F18 8000C4B8 3863E708 */  addi    r3, r3, -6392
/* 006F1C 8000C4BC 38810080 */  addi    r4, r1, 0x80
/* 006F20 8000C4C0 480A6575 */  bl      DVDOpen
/* 006F24 8000C4C4 2C030001 */  cmpwi   r3, 1
/* 006F28 8000C4C8 40820024 */  bne     lbl_8000C4EC
/* 006F2C 8000C4CC 80AD8098 */  lwz     r5, gmsg_sv10Size@sda21(r13)
/* 006F30 8000C4D0 38610080 */  addi    r3, r1, 0x80
/* 006F34 8000C4D4 389E01A0 */  addi    r4, r30, 0x1a0
/* 006F38 8000C4D8 3805001F */  addi    r0, r5, 0x1f
/* 006F3C 8000C4DC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 006F40 8000C4E0 38C00000 */  li      r6, 0
/* 006F44 8000C4E4 38E00000 */  li      r7, 0
/* 006F48 8000C4E8 480027DD */  bl      simulatorDVDRead
lbl_8000C4EC:
/* 006F4C 8000C4EC 38610080 */  addi    r3, r1, 0x80
/* 006F50 8000C4F0 480A660D */  bl      DVDClose
/* 006F54 8000C4F4 387E01A0 */  addi    r3, r30, 0x1a0
/* 006F58 8000C4F8 48002B29 */  bl      simulatorUnpackTexPalette
lbl_8000C4FC:
/* 006F5C 8000C4FC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 006F60 8000C500 3C7F0001 */  addis   r3, r31, 1
/* 006F64 8000C504 3B63D248 */  addi    r27, r3, -11704
/* 006F68 8000C508 80E40000 */  lwz     r7, 0(r4)
/* 006F6C 8000C50C 3B83DE08 */  addi    r28, r3, -8696
/* 006F70 8000C510 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 006F74 8000C514 3CDF0001 */  addis   r6, r31, 1
/* 006F78 8000C518 A0070002 */  lhz     r0, 2(r7)
/* 006F7C 8000C51C 81030000 */  lwz     r8, 0(r3)
/* 006F80 8000C520 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 006F84 8000C524 7C040E70 */  srawi   r4, r0, 1
/* 006F88 8000C528 A0070000 */  lhz     r0, 0(r7)
/* 006F8C 8000C52C 7C840194 */  addze   r4, r4
/* 006F90 8000C530 80BB0000 */  lwz     r5, 0(r27)
/* 006F94 8000C534 208400A0 */  subfic  r4, r4, 0xa0
/* 006F98 8000C538 7C000E70 */  srawi   r0, r0, 1
/* 006F9C 8000C53C A1080002 */  lhz     r8, 2(r8)
/* 006FA0 8000C540 80E50000 */  lwz     r7, 0(r5)
/* 006FA4 8000C544 7C000194 */  addze   r0, r0
/* 006FA8 8000C548 20A00078 */  subfic  r5, r0, 0x78
/* 006FAC 8000C54C A0070000 */  lhz     r0, 0(r7)
/* 006FB0 8000C550 7D070E70 */  srawi   r7, r8, 1
/* 006FB4 8000C554 7CE70194 */  addze   r7, r7
/* 006FB8 8000C558 20E700A0 */  subfic  r7, r7, 0xa0
/* 006FBC 8000C55C 7C000E70 */  srawi   r0, r0, 1
/* 006FC0 8000C560 7C000194 */  addze   r0, r0
/* 006FC4 8000C564 387E01A0 */  addi    r3, r30, 0x1a0
/* 006FC8 8000C568 210000B4 */  subfic  r8, r0, 0xb4
/* 006FCC 8000C56C 38C6DE00 */  addi    r6, r6, -8704
/* 006FD0 8000C570 4800101D */  bl      simulatorDrawOKImage
/* 006FD4 8000C574 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 006FD8 8000C578 2C000001 */  cmpwi   r0, 1
/* 006FDC 8000C57C 40820020 */  bne     lbl_8000C59C
/* 006FE0 8000C580 480AAB0D */  bl      DEMOPadRead
/* 006FE4 8000C584 3C608013 */  lis     r3, DemoPad@ha
/* 006FE8 8000C588 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 006FEC 8000C58C 28000000 */  cmplwi  r0, 0
/* 006FF0 8000C590 4182000C */  beq     lbl_8000C59C
/* 006FF4 8000C594 38600000 */  li      r3, 0
/* 006FF8 8000C598 480005D0 */  b       lbl_8000CB68
lbl_8000C59C:
/* 006FFC 8000C59C 38000000 */  li      r0, 0
/* 007000 8000C5A0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 007004 8000C5A4 480AAAE9 */  bl      DEMOPadRead
/* 007008 8000C5A8 80BD0000 */  lwz     r5, 0(r29)
/* 00700C 8000C5AC 3CDF0001 */  addis   r6, r31, 1
/* 007010 8000C5B0 809C0000 */  lwz     r4, 0(r28)
/* 007014 8000C5B4 387E01A0 */  addi    r3, r30, 0x1a0
/* 007018 8000C5B8 80A50000 */  lwz     r5, 0(r5)
/* 00701C 8000C5BC 80E40000 */  lwz     r7, 0(r4)
/* 007020 8000C5C0 38C6DE00 */  addi    r6, r6, -8704
/* 007024 8000C5C4 A0050002 */  lhz     r0, 2(r5)
/* 007028 8000C5C8 809B0000 */  lwz     r4, 0(r27)
/* 00702C 8000C5CC 7C080E70 */  srawi   r8, r0, 1
/* 007030 8000C5D0 A0050000 */  lhz     r0, 0(r5)
/* 007034 8000C5D4 7D080194 */  addze   r8, r8
/* 007038 8000C5D8 80A40000 */  lwz     r5, 0(r4)
/* 00703C 8000C5DC 208800A0 */  subfic  r4, r8, 0xa0
/* 007040 8000C5E0 A0E70002 */  lhz     r7, 2(r7)
/* 007044 8000C5E4 7C080E70 */  srawi   r8, r0, 1
/* 007048 8000C5E8 A0050000 */  lhz     r0, 0(r5)
/* 00704C 8000C5EC 7D080194 */  addze   r8, r8
/* 007050 8000C5F0 20A80078 */  subfic  r5, r8, 0x78
/* 007054 8000C5F4 7CE70E70 */  srawi   r7, r7, 1
/* 007058 8000C5F8 7CE70194 */  addze   r7, r7
/* 00705C 8000C5FC 20E700A0 */  subfic  r7, r7, 0xa0
/* 007060 8000C600 7C000E70 */  srawi   r0, r0, 1
/* 007064 8000C604 7C000194 */  addze   r0, r0
/* 007068 8000C608 210000B4 */  subfic  r8, r0, 0xb4
/* 00706C 8000C60C 48000F81 */  bl      simulatorDrawOKImage
/* 007070 8000C610 3C608013 */  lis     r3, DemoPad@ha
/* 007074 8000C614 38632758 */  addi    r3, r3, DemoPad@l
/* 007078 8000C618 8803000A */  lbz     r0, 0xa(r3)
/* 00707C 8000C61C 7C000775 */  extsb.  r0, r0
/* 007080 8000C620 4082002C */  bne     lbl_8000C64C
/* 007084 8000C624 A0030000 */  lhz     r0, 0(r3)
/* 007088 8000C628 70001100 */  andi.   r0, r0, 0x1100
/* 00708C 8000C62C 41820020 */  beq     lbl_8000C64C
/* 007090 8000C630 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 007094 8000C634 38800000 */  li      r4, 0
/* 007098 8000C638 80630004 */  lwz     r3, 4(r3)
/* 00709C 8000C63C 48010055 */  bl      soundPlayBeep
/* 0070A0 8000C640 38600001 */  li      r3, 1
/* 0070A4 8000C644 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 0070A8 8000C648 48000520 */  b       lbl_8000CB68
lbl_8000C64C:
/* 0070AC 8000C64C 38600000 */  li      r3, 0
/* 0070B0 8000C650 48000518 */  b       lbl_8000CB68
glabel lbl_8000C654
/* 0070B4 8000C654 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 0070B8 8000C658 7C001800 */  cmpw    r0, r3
/* 0070BC 8000C65C 41820050 */  beq     lbl_8000C6AC
/* 0070C0 8000C660 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 0070C4 8000C664 3C7F0001 */  addis   r3, r31, 1
/* 0070C8 8000C668 3863E71C */  addi    r3, r3, -6372
/* 0070CC 8000C66C 38810080 */  addi    r4, r1, 0x80
/* 0070D0 8000C670 480A63C5 */  bl      DVDOpen
/* 0070D4 8000C674 2C030001 */  cmpwi   r3, 1
/* 0070D8 8000C678 40820024 */  bne     lbl_8000C69C
/* 0070DC 8000C67C 80AD809C */  lwz     r5, gmsg_sv11Size@sda21(r13)
/* 0070E0 8000C680 38610080 */  addi    r3, r1, 0x80
/* 0070E4 8000C684 389E01A0 */  addi    r4, r30, 0x1a0
/* 0070E8 8000C688 3805001F */  addi    r0, r5, 0x1f
/* 0070EC 8000C68C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0070F0 8000C690 38C00000 */  li      r6, 0
/* 0070F4 8000C694 38E00000 */  li      r7, 0
/* 0070F8 8000C698 4800262D */  bl      simulatorDVDRead
lbl_8000C69C:
/* 0070FC 8000C69C 38610080 */  addi    r3, r1, 0x80
/* 007100 8000C6A0 480A645D */  bl      DVDClose
/* 007104 8000C6A4 387E01A0 */  addi    r3, r30, 0x1a0
/* 007108 8000C6A8 48002979 */  bl      simulatorUnpackTexPalette
lbl_8000C6AC:
/* 00710C 8000C6AC 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 007110 8000C6B0 3C7F0001 */  addis   r3, r31, 1
/* 007114 8000C6B4 3B63D248 */  addi    r27, r3, -11704
/* 007118 8000C6B8 80E40000 */  lwz     r7, 0(r4)
/* 00711C 8000C6BC 3B83DE08 */  addi    r28, r3, -8696
/* 007120 8000C6C0 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 007124 8000C6C4 3CDF0001 */  addis   r6, r31, 1
/* 007128 8000C6C8 A0070002 */  lhz     r0, 2(r7)
/* 00712C 8000C6CC 81030000 */  lwz     r8, 0(r3)
/* 007130 8000C6D0 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 007134 8000C6D4 7C040E70 */  srawi   r4, r0, 1
/* 007138 8000C6D8 A0070000 */  lhz     r0, 0(r7)
/* 00713C 8000C6DC 7C840194 */  addze   r4, r4
/* 007140 8000C6E0 80BB0000 */  lwz     r5, 0(r27)
/* 007144 8000C6E4 208400A0 */  subfic  r4, r4, 0xa0
/* 007148 8000C6E8 7C000E70 */  srawi   r0, r0, 1
/* 00714C 8000C6EC A1080002 */  lhz     r8, 2(r8)
/* 007150 8000C6F0 80E50000 */  lwz     r7, 0(r5)
/* 007154 8000C6F4 7C000194 */  addze   r0, r0
/* 007158 8000C6F8 20A00078 */  subfic  r5, r0, 0x78
/* 00715C 8000C6FC A0070000 */  lhz     r0, 0(r7)
/* 007160 8000C700 7D070E70 */  srawi   r7, r8, 1
/* 007164 8000C704 7CE70194 */  addze   r7, r7
/* 007168 8000C708 20E700A0 */  subfic  r7, r7, 0xa0
/* 00716C 8000C70C 7C000E70 */  srawi   r0, r0, 1
/* 007170 8000C710 7C000194 */  addze   r0, r0
/* 007174 8000C714 387E01A0 */  addi    r3, r30, 0x1a0
/* 007178 8000C718 210000B4 */  subfic  r8, r0, 0xb4
/* 00717C 8000C71C 38C6DE00 */  addi    r6, r6, -8704
/* 007180 8000C720 48000E6D */  bl      simulatorDrawOKImage
/* 007184 8000C724 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 007188 8000C728 2C000001 */  cmpwi   r0, 1
/* 00718C 8000C72C 40820020 */  bne     lbl_8000C74C
/* 007190 8000C730 480AA95D */  bl      DEMOPadRead
/* 007194 8000C734 3C608013 */  lis     r3, DemoPad@ha
/* 007198 8000C738 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00719C 8000C73C 28000000 */  cmplwi  r0, 0
/* 0071A0 8000C740 4182000C */  beq     lbl_8000C74C
/* 0071A4 8000C744 38600000 */  li      r3, 0
/* 0071A8 8000C748 48000420 */  b       lbl_8000CB68
lbl_8000C74C:
/* 0071AC 8000C74C 38000000 */  li      r0, 0
/* 0071B0 8000C750 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 0071B4 8000C754 480AA939 */  bl      DEMOPadRead
/* 0071B8 8000C758 80BD0000 */  lwz     r5, 0(r29)
/* 0071BC 8000C75C 3CDF0001 */  addis   r6, r31, 1
/* 0071C0 8000C760 809C0000 */  lwz     r4, 0(r28)
/* 0071C4 8000C764 387E01A0 */  addi    r3, r30, 0x1a0
/* 0071C8 8000C768 80A50000 */  lwz     r5, 0(r5)
/* 0071CC 8000C76C 80E40000 */  lwz     r7, 0(r4)
/* 0071D0 8000C770 38C6DE00 */  addi    r6, r6, -8704
/* 0071D4 8000C774 A0050002 */  lhz     r0, 2(r5)
/* 0071D8 8000C778 809B0000 */  lwz     r4, 0(r27)
/* 0071DC 8000C77C 7C080E70 */  srawi   r8, r0, 1
/* 0071E0 8000C780 A0050000 */  lhz     r0, 0(r5)
/* 0071E4 8000C784 7D080194 */  addze   r8, r8
/* 0071E8 8000C788 80A40000 */  lwz     r5, 0(r4)
/* 0071EC 8000C78C 208800A0 */  subfic  r4, r8, 0xa0
/* 0071F0 8000C790 A0E70002 */  lhz     r7, 2(r7)
/* 0071F4 8000C794 7C080E70 */  srawi   r8, r0, 1
/* 0071F8 8000C798 A0050000 */  lhz     r0, 0(r5)
/* 0071FC 8000C79C 7D080194 */  addze   r8, r8
/* 007200 8000C7A0 20A80078 */  subfic  r5, r8, 0x78
/* 007204 8000C7A4 7CE70E70 */  srawi   r7, r7, 1
/* 007208 8000C7A8 7CE70194 */  addze   r7, r7
/* 00720C 8000C7AC 20E700A0 */  subfic  r7, r7, 0xa0
/* 007210 8000C7B0 7C000E70 */  srawi   r0, r0, 1
/* 007214 8000C7B4 7C000194 */  addze   r0, r0
/* 007218 8000C7B8 210000B4 */  subfic  r8, r0, 0xb4
/* 00721C 8000C7BC 48000DD1 */  bl      simulatorDrawOKImage
/* 007220 8000C7C0 3C608013 */  lis     r3, DemoPad@ha
/* 007224 8000C7C4 38632758 */  addi    r3, r3, DemoPad@l
/* 007228 8000C7C8 8803000A */  lbz     r0, 0xa(r3)
/* 00722C 8000C7CC 7C000775 */  extsb.  r0, r0
/* 007230 8000C7D0 4082002C */  bne     lbl_8000C7FC
/* 007234 8000C7D4 A0030000 */  lhz     r0, 0(r3)
/* 007238 8000C7D8 70001100 */  andi.   r0, r0, 0x1100
/* 00723C 8000C7DC 41820020 */  beq     lbl_8000C7FC
/* 007240 8000C7E0 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 007244 8000C7E4 38800000 */  li      r4, 0
/* 007248 8000C7E8 80630004 */  lwz     r3, 4(r3)
/* 00724C 8000C7EC 4800FEA5 */  bl      soundPlayBeep
/* 007250 8000C7F0 38600001 */  li      r3, 1
/* 007254 8000C7F4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 007258 8000C7F8 48000370 */  b       lbl_8000CB68
lbl_8000C7FC:
/* 00725C 8000C7FC 38600000 */  li      r3, 0
/* 007260 8000C800 48000368 */  b       lbl_8000CB68
glabel lbl_8000C804
/* 007264 8000C804 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007268 8000C808 7C001800 */  cmpw    r0, r3
/* 00726C 8000C80C 41820050 */  beq     lbl_8000C85C
/* 007270 8000C810 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007274 8000C814 3C7F0001 */  addis   r3, r31, 1
/* 007278 8000C818 3863E730 */  addi    r3, r3, -6352
/* 00727C 8000C81C 38810080 */  addi    r4, r1, 0x80
/* 007280 8000C820 480A6215 */  bl      DVDOpen
/* 007284 8000C824 2C030001 */  cmpwi   r3, 1
/* 007288 8000C828 40820024 */  bne     lbl_8000C84C
/* 00728C 8000C82C 80AD80A0 */  lwz     r5, gmsg_sv12Size@sda21(r13)
/* 007290 8000C830 38610080 */  addi    r3, r1, 0x80
/* 007294 8000C834 389E01A0 */  addi    r4, r30, 0x1a0
/* 007298 8000C838 3805001F */  addi    r0, r5, 0x1f
/* 00729C 8000C83C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0072A0 8000C840 38C00000 */  li      r6, 0
/* 0072A4 8000C844 38E00000 */  li      r7, 0
/* 0072A8 8000C848 4800247D */  bl      simulatorDVDRead
lbl_8000C84C:
/* 0072AC 8000C84C 38610080 */  addi    r3, r1, 0x80
/* 0072B0 8000C850 480A62AD */  bl      DVDClose
/* 0072B4 8000C854 387E01A0 */  addi    r3, r30, 0x1a0
/* 0072B8 8000C858 480027C9 */  bl      simulatorUnpackTexPalette
lbl_8000C85C:
/* 0072BC 8000C85C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 0072C0 8000C860 3C7F0001 */  addis   r3, r31, 1
/* 0072C4 8000C864 3B63D248 */  addi    r27, r3, -11704
/* 0072C8 8000C868 80E40000 */  lwz     r7, 0(r4)
/* 0072CC 8000C86C 3B83DE08 */  addi    r28, r3, -8696
/* 0072D0 8000C870 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 0072D4 8000C874 3CDF0001 */  addis   r6, r31, 1
/* 0072D8 8000C878 A0070002 */  lhz     r0, 2(r7)
/* 0072DC 8000C87C 81030000 */  lwz     r8, 0(r3)
/* 0072E0 8000C880 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 0072E4 8000C884 7C040E70 */  srawi   r4, r0, 1
/* 0072E8 8000C888 A0070000 */  lhz     r0, 0(r7)
/* 0072EC 8000C88C 7C840194 */  addze   r4, r4
/* 0072F0 8000C890 80BB0000 */  lwz     r5, 0(r27)
/* 0072F4 8000C894 208400A0 */  subfic  r4, r4, 0xa0
/* 0072F8 8000C898 7C000E70 */  srawi   r0, r0, 1
/* 0072FC 8000C89C A1080002 */  lhz     r8, 2(r8)
/* 007300 8000C8A0 80E50000 */  lwz     r7, 0(r5)
/* 007304 8000C8A4 7C000194 */  addze   r0, r0
/* 007308 8000C8A8 20A00078 */  subfic  r5, r0, 0x78
/* 00730C 8000C8AC A0070000 */  lhz     r0, 0(r7)
/* 007310 8000C8B0 7D070E70 */  srawi   r7, r8, 1
/* 007314 8000C8B4 7CE70194 */  addze   r7, r7
/* 007318 8000C8B8 20E700A0 */  subfic  r7, r7, 0xa0
/* 00731C 8000C8BC 7C000E70 */  srawi   r0, r0, 1
/* 007320 8000C8C0 7C000194 */  addze   r0, r0
/* 007324 8000C8C4 387E01A0 */  addi    r3, r30, 0x1a0
/* 007328 8000C8C8 210000B4 */  subfic  r8, r0, 0xb4
/* 00732C 8000C8CC 38C6DE00 */  addi    r6, r6, -8704
/* 007330 8000C8D0 48000CBD */  bl      simulatorDrawOKImage
/* 007334 8000C8D4 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 007338 8000C8D8 2C000001 */  cmpwi   r0, 1
/* 00733C 8000C8DC 40820020 */  bne     lbl_8000C8FC
/* 007340 8000C8E0 480AA7AD */  bl      DEMOPadRead
/* 007344 8000C8E4 3C608013 */  lis     r3, DemoPad@ha
/* 007348 8000C8E8 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 00734C 8000C8EC 28000000 */  cmplwi  r0, 0
/* 007350 8000C8F0 4182000C */  beq     lbl_8000C8FC
/* 007354 8000C8F4 38600000 */  li      r3, 0
/* 007358 8000C8F8 48000270 */  b       lbl_8000CB68
lbl_8000C8FC:
/* 00735C 8000C8FC 38000000 */  li      r0, 0
/* 007360 8000C900 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 007364 8000C904 480AA789 */  bl      DEMOPadRead
/* 007368 8000C908 80BD0000 */  lwz     r5, 0(r29)
/* 00736C 8000C90C 3CDF0001 */  addis   r6, r31, 1
/* 007370 8000C910 809C0000 */  lwz     r4, 0(r28)
/* 007374 8000C914 387E01A0 */  addi    r3, r30, 0x1a0
/* 007378 8000C918 80A50000 */  lwz     r5, 0(r5)
/* 00737C 8000C91C 80E40000 */  lwz     r7, 0(r4)
/* 007380 8000C920 38C6DE00 */  addi    r6, r6, -8704
/* 007384 8000C924 A0050002 */  lhz     r0, 2(r5)
/* 007388 8000C928 809B0000 */  lwz     r4, 0(r27)
/* 00738C 8000C92C 7C080E70 */  srawi   r8, r0, 1
/* 007390 8000C930 A0050000 */  lhz     r0, 0(r5)
/* 007394 8000C934 7D080194 */  addze   r8, r8
/* 007398 8000C938 80A40000 */  lwz     r5, 0(r4)
/* 00739C 8000C93C 208800A0 */  subfic  r4, r8, 0xa0
/* 0073A0 8000C940 A0E70002 */  lhz     r7, 2(r7)
/* 0073A4 8000C944 7C080E70 */  srawi   r8, r0, 1
/* 0073A8 8000C948 A0050000 */  lhz     r0, 0(r5)
/* 0073AC 8000C94C 7D080194 */  addze   r8, r8
/* 0073B0 8000C950 20A80078 */  subfic  r5, r8, 0x78
/* 0073B4 8000C954 7CE70E70 */  srawi   r7, r7, 1
/* 0073B8 8000C958 7CE70194 */  addze   r7, r7
/* 0073BC 8000C95C 20E700A0 */  subfic  r7, r7, 0xa0
/* 0073C0 8000C960 7C000E70 */  srawi   r0, r0, 1
/* 0073C4 8000C964 7C000194 */  addze   r0, r0
/* 0073C8 8000C968 210000B4 */  subfic  r8, r0, 0xb4
/* 0073CC 8000C96C 48000C21 */  bl      simulatorDrawOKImage
/* 0073D0 8000C970 3C608013 */  lis     r3, DemoPad@ha
/* 0073D4 8000C974 38632758 */  addi    r3, r3, DemoPad@l
/* 0073D8 8000C978 8803000A */  lbz     r0, 0xa(r3)
/* 0073DC 8000C97C 7C000775 */  extsb.  r0, r0
/* 0073E0 8000C980 4082002C */  bne     lbl_8000C9AC
/* 0073E4 8000C984 A0030000 */  lhz     r0, 0(r3)
/* 0073E8 8000C988 70001100 */  andi.   r0, r0, 0x1100
/* 0073EC 8000C98C 41820020 */  beq     lbl_8000C9AC
/* 0073F0 8000C990 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 0073F4 8000C994 38800000 */  li      r4, 0
/* 0073F8 8000C998 80630004 */  lwz     r3, 4(r3)
/* 0073FC 8000C99C 4800FCF5 */  bl      soundPlayBeep
/* 007400 8000C9A0 38600001 */  li      r3, 1
/* 007404 8000C9A4 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 007408 8000C9A8 480001C0 */  b       lbl_8000CB68
lbl_8000C9AC:
/* 00740C 8000C9AC 38600000 */  li      r3, 0
/* 007410 8000C9B0 480001B8 */  b       lbl_8000CB68
glabel lbl_8000C9B4
/* 007414 8000C9B4 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007418 8000C9B8 7C001800 */  cmpw    r0, r3
/* 00741C 8000C9BC 41820050 */  beq     lbl_8000CA0C
/* 007420 8000C9C0 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007424 8000C9C4 3C7F0001 */  addis   r3, r31, 1
/* 007428 8000C9C8 3863E744 */  addi    r3, r3, -6332
/* 00742C 8000C9CC 38810080 */  addi    r4, r1, 0x80
/* 007430 8000C9D0 480A6065 */  bl      DVDOpen
/* 007434 8000C9D4 2C030001 */  cmpwi   r3, 1
/* 007438 8000C9D8 40820024 */  bne     lbl_8000C9FC
/* 00743C 8000C9DC 80AD80A4 */  lwz     r5, gmsg_sv_shareSize@sda21(r13)
/* 007440 8000C9E0 38610080 */  addi    r3, r1, 0x80
/* 007444 8000C9E4 389E01A0 */  addi    r4, r30, 0x1a0
/* 007448 8000C9E8 3805001F */  addi    r0, r5, 0x1f
/* 00744C 8000C9EC 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 007450 8000C9F0 38C00000 */  li      r6, 0
/* 007454 8000C9F4 38E00000 */  li      r7, 0
/* 007458 8000C9F8 480022CD */  bl      simulatorDVDRead
lbl_8000C9FC:
/* 00745C 8000C9FC 38610080 */  addi    r3, r1, 0x80
/* 007460 8000CA00 480A60FD */  bl      DVDClose
/* 007464 8000CA04 387E01A0 */  addi    r3, r30, 0x1a0
/* 007468 8000CA08 48002619 */  bl      simulatorUnpackTexPalette
lbl_8000CA0C:
/* 00746C 8000CA0C 809E01A8 */  lwz     r4, 0x1a8(r30)
/* 007470 8000CA10 3C7F0001 */  addis   r3, r31, 1
/* 007474 8000CA14 3B63D248 */  addi    r27, r3, -11704
/* 007478 8000CA18 80E40000 */  lwz     r7, 0(r4)
/* 00747C 8000CA1C 3B83DE08 */  addi    r28, r3, -8696
/* 007480 8000CA20 8063DE08 */  lwz     r3, -0x21f8(r3)
/* 007484 8000CA24 3CDF0001 */  addis   r6, r31, 1
/* 007488 8000CA28 A0070002 */  lhz     r0, 2(r7)
/* 00748C 8000CA2C 81030000 */  lwz     r8, 0(r3)
/* 007490 8000CA30 3BBE01A8 */  addi    r29, r30, 0x1a8
/* 007494 8000CA34 7C040E70 */  srawi   r4, r0, 1
/* 007498 8000CA38 A0070000 */  lhz     r0, 0(r7)
/* 00749C 8000CA3C 7C840194 */  addze   r4, r4
/* 0074A0 8000CA40 80BB0000 */  lwz     r5, 0(r27)
/* 0074A4 8000CA44 208400A0 */  subfic  r4, r4, 0xa0
/* 0074A8 8000CA48 7C000E70 */  srawi   r0, r0, 1
/* 0074AC 8000CA4C A1080002 */  lhz     r8, 2(r8)
/* 0074B0 8000CA50 80E50000 */  lwz     r7, 0(r5)
/* 0074B4 8000CA54 7C000194 */  addze   r0, r0
/* 0074B8 8000CA58 20A00078 */  subfic  r5, r0, 0x78
/* 0074BC 8000CA5C A0070000 */  lhz     r0, 0(r7)
/* 0074C0 8000CA60 7D070E70 */  srawi   r7, r8, 1
/* 0074C4 8000CA64 7CE70194 */  addze   r7, r7
/* 0074C8 8000CA68 20E700A0 */  subfic  r7, r7, 0xa0
/* 0074CC 8000CA6C 7C000E70 */  srawi   r0, r0, 1
/* 0074D0 8000CA70 7C000194 */  addze   r0, r0
/* 0074D4 8000CA74 387E01A0 */  addi    r3, r30, 0x1a0
/* 0074D8 8000CA78 210000B4 */  subfic  r8, r0, 0xb4
/* 0074DC 8000CA7C 38C6DE00 */  addi    r6, r6, -8704
/* 0074E0 8000CA80 48000B0D */  bl      simulatorDrawOKImage
/* 0074E4 8000CA84 800D88F4 */  lwz     r0, gButtonDownToggle@sda21(r13)
/* 0074E8 8000CA88 2C000001 */  cmpwi   r0, 1
/* 0074EC 8000CA8C 40820020 */  bne     lbl_8000CAAC
/* 0074F0 8000CA90 480AA5FD */  bl      DEMOPadRead
/* 0074F4 8000CA94 3C608013 */  lis     r3, DemoPad@ha
/* 0074F8 8000CA98 A0032758 */  lhz     r0, DemoPad@l(r3)
/* 0074FC 8000CA9C 28000000 */  cmplwi  r0, 0
/* 007500 8000CAA0 4182000C */  beq     lbl_8000CAAC
/* 007504 8000CAA4 38600000 */  li      r3, 0
/* 007508 8000CAA8 480000C0 */  b       lbl_8000CB68
lbl_8000CAAC:
/* 00750C 8000CAAC 38000000 */  li      r0, 0
/* 007510 8000CAB0 900D88F4 */  stw     r0, gButtonDownToggle@sda21(r13)
/* 007514 8000CAB4 480AA5D9 */  bl      DEMOPadRead
/* 007518 8000CAB8 80BD0000 */  lwz     r5, 0(r29)
/* 00751C 8000CABC 3CDF0001 */  addis   r6, r31, 1
/* 007520 8000CAC0 809C0000 */  lwz     r4, 0(r28)
/* 007524 8000CAC4 387E01A0 */  addi    r3, r30, 0x1a0
/* 007528 8000CAC8 80A50000 */  lwz     r5, 0(r5)
/* 00752C 8000CACC 80E40000 */  lwz     r7, 0(r4)
/* 007530 8000CAD0 38C6DE00 */  addi    r6, r6, -8704
/* 007534 8000CAD4 A0050002 */  lhz     r0, 2(r5)
/* 007538 8000CAD8 809B0000 */  lwz     r4, 0(r27)
/* 00753C 8000CADC 7C080E70 */  srawi   r8, r0, 1
/* 007540 8000CAE0 A0050000 */  lhz     r0, 0(r5)
/* 007544 8000CAE4 7D080194 */  addze   r8, r8
/* 007548 8000CAE8 80A40000 */  lwz     r5, 0(r4)
/* 00754C 8000CAEC 208800A0 */  subfic  r4, r8, 0xa0
/* 007550 8000CAF0 A0E70002 */  lhz     r7, 2(r7)
/* 007554 8000CAF4 7C080E70 */  srawi   r8, r0, 1
/* 007558 8000CAF8 A0050000 */  lhz     r0, 0(r5)
/* 00755C 8000CAFC 7D080194 */  addze   r8, r8
/* 007560 8000CB00 20A80078 */  subfic  r5, r8, 0x78
/* 007564 8000CB04 7CE70E70 */  srawi   r7, r7, 1
/* 007568 8000CB08 7CE70194 */  addze   r7, r7
/* 00756C 8000CB0C 20E700A0 */  subfic  r7, r7, 0xa0
/* 007570 8000CB10 7C000E70 */  srawi   r0, r0, 1
/* 007574 8000CB14 7C000194 */  addze   r0, r0
/* 007578 8000CB18 210000B4 */  subfic  r8, r0, 0xb4
/* 00757C 8000CB1C 48000A71 */  bl      simulatorDrawOKImage
/* 007580 8000CB20 3C608013 */  lis     r3, DemoPad@ha
/* 007584 8000CB24 38632758 */  addi    r3, r3, DemoPad@l
/* 007588 8000CB28 8803000A */  lbz     r0, 0xa(r3)
/* 00758C 8000CB2C 7C000775 */  extsb.  r0, r0
/* 007590 8000CB30 4082002C */  bne     lbl_8000CB5C
/* 007594 8000CB34 A0030000 */  lhz     r0, 0(r3)
/* 007598 8000CB38 70001100 */  andi.   r0, r0, 0x1100
/* 00759C 8000CB3C 41820020 */  beq     lbl_8000CB5C
/* 0075A0 8000CB40 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 0075A4 8000CB44 38800000 */  li      r4, 0
/* 0075A8 8000CB48 80630004 */  lwz     r3, 4(r3)
/* 0075AC 8000CB4C 4800FB45 */  bl      soundPlayBeep
/* 0075B0 8000CB50 38600001 */  li      r3, 1
/* 0075B4 8000CB54 906D88F4 */  stw     r3, gButtonDownToggle@sda21(r13)
/* 0075B8 8000CB58 48000010 */  b       lbl_8000CB68
lbl_8000CB5C:
/* 0075BC 8000CB5C 38600000 */  li      r3, 0
/* 0075C0 8000CB60 48000008 */  b       lbl_8000CB68
glabel lbl_8000CB64
/* 0075C4 8000CB64 38600000 */  li      r3, 0
lbl_8000CB68:
/* 0075C8 8000CB68 BB6100C4 */  lmw     r27, 0xc4(r1)
/* 0075CC 8000CB6C 800100DC */  lwz     r0, 0xdc(r1)
/* 0075D0 8000CB70 382100D8 */  addi    r1, r1, 0xd8
/* 0075D4 8000CB74 7C0803A6 */  mtlr    r0
/* 0075D8 8000CB78 4E800020 */  blr     
