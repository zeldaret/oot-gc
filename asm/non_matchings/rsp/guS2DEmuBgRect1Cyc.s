glabel guS2DEmuBgRect1Cyc
/* 0747DC 80079D7C 7C0802A6 */  mflr    r0
/* 0747E0 80079D80 90010004 */  stw     r0, 4(r1)
/* 0747E4 80079D84 9421FF20 */  stwu    r1, -0xe0(r1)
/* 0747E8 80079D88 DBE100D8 */  stfd    f31, 0xd8(r1)
/* 0747EC 80079D8C DBC100D0 */  stfd    f30, 0xd0(r1)
/* 0747F0 80079D90 DBA100C8 */  stfd    f29, 0xc8(r1)
/* 0747F4 80079D94 DB8100C0 */  stfd    f28, 0xc0(r1)
/* 0747F8 80079D98 BDC10078 */  stmw    r14, 0x78(r1)
/* 0747FC 80079D9C 7CBA2B78 */  mr      r26, r5
/* 074800 80079DA0 7C6F1B78 */  mr      r15, r3
/* 074804 80079DA4 3BA40000 */  addi    r29, r4, 0
/* 074808 80079DA8 A1C5001C */  lhz     r14, 0x1c(r5)
/* 07480C 80079DAC A2250002 */  lhz     r17, 2(r5)
/* 074810 80079DB0 7DC30734 */  extsh   r3, r14
/* 074814 80079DB4 A005001E */  lhz     r0, 0x1e(r5)
/* 074818 80079DB8 5624502A */  slwi    r4, r17, 0xa
/* 07481C 80079DBC A15A000A */  lhz     r10, 0xa(r26)
/* 074820 80079DC0 7CA41BD6 */  divw    r5, r4, r3
/* 074824 80079DC4 B0010052 */  sth     r0, 0x52(r1)
/* 074828 80079DC8 A07A0006 */  lhz     r3, 6(r26)
/* 07482C 80079DCC A0E10052 */  lhz     r7, 0x52(r1)
/* 074830 80079DD0 A0DA000E */  lhz     r6, 0xe(r26)
/* 074834 80079DD4 3805FFFF */  addi    r0, r5, -1
/* 074838 80079DD8 A89A0004 */  lha     r4, 4(r26)
/* 07483C 80079DDC 5408003A */  rlwinm  r8, r0, 0, 0, 0x1d
/* 074840 80079DE0 A8BA000C */  lha     r5, 0xc(r26)
/* 074844 80079DE4 5540502A */  slwi    r0, r10, 0xa
/* 074848 80079DE8 7CE70734 */  extsh   r7, r7
/* 07484C 80079DEC 7CE03BD6 */  divw    r7, r0, r7
/* 074850 80079DF0 38E7FFFF */  addi    r7, r7, -1
/* 074854 80079DF4 7C081851 */  subf.   r0, r8, r3
/* 074858 80079DF8 54E7003A */  rlwinm  r7, r7, 0, 0, 0x1d
/* 07485C 80079DFC 40800008 */  bge     lbl_80079E04
/* 074860 80079E00 38000000 */  li      r0, 0
lbl_80079E04:
/* 074864 80079E04 7CE73051 */  subf.   r7, r7, r6
/* 074868 80079E08 40800008 */  bge     lbl_80079E10
/* 07486C 80079E0C 38E00000 */  li      r7, 0
lbl_80079E10:
/* 074870 80079E10 A11A001A */  lhz     r8, 0x1a(r26)
/* 074874 80079E14 7C000734 */  extsh   r0, r0
/* 074878 80079E18 7CE70734 */  extsh   r7, r7
/* 07487C 80079E1C 550C07FF */  clrlwi. r12, r8, 0x1f
/* 074880 80079E20 7C601850 */  subf    r3, r0, r3
/* 074884 80079E24 7CE73050 */  subf    r7, r7, r6
/* 074888 80079E28 41820008 */  beq     lbl_80079E30
/* 07488C 80079E2C 7C840214 */  add     r4, r4, r0
lbl_80079E30:
/* 074890 80079E30 A00D8AAC */  lhz     r0, scissorX0@sda21(r13)
/* 074894 80079E34 7C860734 */  extsh   r6, r4
/* 074898 80079E38 A08D8AAE */  lhz     r4, scissorY0@sda21(r13)
/* 07489C 80079E3C 7C690734 */  extsh   r9, r3
/* 0748A0 80079E40 7C060050 */  subf    r0, r6, r0
/* 0748A4 80079E44 7C030734 */  extsh   r3, r0
/* 0748A8 80079E48 A00D85F4 */  lhz     r0, scissorX1@sda21(r13)
/* 0748AC 80079E4C A10D85F6 */  lhz     r8, scissorY1@sda21(r13)
/* 0748B0 80079E50 7CE70734 */  extsh   r7, r7
/* 0748B4 80079E54 7C004850 */  subf    r0, r0, r9
/* 0748B8 80079E58 7D083850 */  subf    r8, r8, r7
/* 0748BC 80079E5C 7C6B0735 */  extsh.  r11, r3
/* 0748C0 80079E60 7C852050 */  subf    r4, r5, r4
/* 0748C4 80079E64 7C060214 */  add     r0, r6, r0
/* 0748C8 80079E68 7D054214 */  add     r8, r5, r8
/* 0748CC 80079E6C 40800008 */  bge     lbl_80079E74
/* 0748D0 80079E70 38600000 */  li      r3, 0
lbl_80079E74:
/* 0748D4 80079E74 7C8B0735 */  extsh.  r11, r4
/* 0748D8 80079E78 40800008 */  bge     lbl_80079E80
/* 0748DC 80079E7C 38800000 */  li      r4, 0
lbl_80079E80:
/* 0748E0 80079E80 7C0B0735 */  extsh.  r11, r0
/* 0748E4 80079E84 40800008 */  bge     lbl_80079E8C
/* 0748E8 80079E88 38000000 */  li      r0, 0
lbl_80079E8C:
/* 0748EC 80079E8C 7D0B0735 */  extsh.  r11, r8
/* 0748F0 80079E90 40800008 */  bge     lbl_80079E98
/* 0748F4 80079E94 39000000 */  li      r8, 0
lbl_80079E98:
/* 0748F8 80079E98 7C630734 */  extsh   r3, r3
/* 0748FC 80079E9C 7C0B0734 */  extsh   r11, r0
/* 074900 80079EA0 7C035A14 */  add     r0, r3, r11
/* 074904 80079EA4 7C840734 */  extsh   r4, r4
/* 074908 80079EA8 7C004850 */  subf    r0, r0, r9
/* 07490C 80079EAC 7D044214 */  add     r8, r4, r8
/* 074910 80079EB0 7C090735 */  extsh.  r9, r0
/* 074914 80079EB4 7CE83850 */  subf    r7, r8, r7
/* 074918 80079EB8 7CC61A14 */  add     r6, r6, r3
/* 07491C 80079EBC 7D052214 */  add     r8, r5, r4
/* 074920 80079EC0 4081000C */  ble     lbl_80079ECC
/* 074924 80079EC4 7CE50735 */  extsh.  r5, r7
/* 074928 80079EC8 4181000C */  bgt     lbl_80079ED4
lbl_80079ECC:
/* 07492C 80079ECC 38600001 */  li      r3, 1
/* 074930 80079ED0 480005C4 */  b       lbl_8007A494
lbl_80079ED4:
/* 074934 80079ED4 7C090734 */  extsh   r9, r0
/* 074938 80079ED8 8A6D8AB0 */  lbz     r19, flagBilerp@sda21(r13)
/* 07493C 80079EDC 7DC00734 */  extsh   r0, r14
/* 074940 80079EE0 7CA901D6 */  mullw   r5, r9, r0
/* 074944 80079EE4 7D080734 */  extsh   r8, r8
/* 074948 80079EE8 7D081670 */  srawi   r8, r8, 2
/* 07494C 80079EEC 7CE70734 */  extsh   r7, r7
/* 074950 80079EF0 7CE71670 */  srawi   r7, r7, 2
/* 074954 80079EF4 7CA53E70 */  srawi   r5, r5, 7
/* 074958 80079EF8 7CD00734 */  extsh   r16, r6
/* 07495C 80079EFC 2C0C0000 */  cmpwi   r12, 0
/* 074960 80079F00 7CB50734 */  extsh   r21, r5
/* 074964 80079F04 7CB04A14 */  add     r5, r16, r9
/* 074968 80079F08 56261838 */  slwi    r6, r17, 3
/* 07496C 80079F0C B0A10050 */  sth     r5, 0x50(r1)
/* 074970 80079F10 566C2834 */  slwi    r12, r19, 5
/* 074974 80079F14 554A1838 */  slwi    r10, r10, 3
/* 074978 80079F18 7CFF0734 */  extsh   r31, r7
/* 07497C 80079F1C 7D170734 */  extsh   r23, r8
/* 074980 80079F20 7CC60734 */  extsh   r6, r6
/* 074984 80079F24 7D470734 */  extsh   r7, r10
/* 074988 80079F28 7D2CAA14 */  add     r9, r12, r21
/* 07498C 80079F2C 41820018 */  beq     lbl_80079F44
/* 074990 80079F30 7CAB01D6 */  mullw   r5, r11, r0
/* 074994 80079F34 A07A0000 */  lhz     r3, 0(r26)
/* 074998 80079F38 7CA53E70 */  srawi   r5, r5, 7
/* 07499C 80079F3C 7C632A14 */  add     r3, r3, r5
/* 0749A0 80079F40 48000014 */  b       lbl_80079F54
lbl_80079F44:
/* 0749A4 80079F44 7CA301D6 */  mullw   r5, r3, r0
/* 0749A8 80079F48 A07A0000 */  lhz     r3, 0(r26)
/* 0749AC 80079F4C 7CA53E70 */  srawi   r5, r5, 7
/* 0749B0 80079F50 7C632A14 */  add     r3, r3, r5
lbl_80079F54:
/* 0749B4 80079F54 A0A10052 */  lhz     r5, 0x52(r1)
/* 0749B8 80079F58 A11A0008 */  lhz     r8, 8(r26)
/* 0749BC 80079F5C 7CB10734 */  extsh   r17, r5
/* 0749C0 80079F60 80BA0020 */  lwz     r5, 0x20(r26)
/* 0749C4 80079F64 7C8489D6 */  mullw   r4, r4, r17
/* 0749C8 80079F68 7C843E70 */  srawi   r4, r4, 7
/* 0749CC 80079F6C 7C882214 */  add     r4, r8, r4
/* 0749D0 80079F70 48000010 */  b       lbl_80079F80
lbl_80079F74:
/* 0749D4 80079F74 7C661850 */  subf    r3, r6, r3
/* 0749D8 80079F78 38840020 */  addi    r4, r4, 0x20
/* 0749DC 80079F7C 38A50020 */  addi    r5, r5, 0x20
lbl_80079F80:
/* 0749E0 80079F80 7C680734 */  extsh   r8, r3
/* 0749E4 80079F84 7C083000 */  cmpw    r8, r6
/* 0749E8 80079F88 4080FFEC */  bge     lbl_80079F74
/* 0749EC 80079F8C 4800000C */  b       lbl_80079F98
lbl_80079F90:
/* 0749F0 80079F90 7C872050 */  subf    r4, r7, r4
/* 0749F4 80079F94 7CA72850 */  subf    r5, r7, r5
lbl_80079F98:
/* 0749F8 80079F98 7C880734 */  extsh   r8, r4
/* 0749FC 80079F9C 7C083800 */  cmpw    r8, r7
/* 074A00 80079FA0 4080FFF0 */  bge     lbl_80079F90
/* 074A04 80079FA4 7C6B0734 */  extsh   r11, r3
/* 074A08 80079FA8 7D230734 */  extsh   r3, r9
/* 074A0C 80079FAC 7D0B1A14 */  add     r8, r11, r3
/* 074A10 80079FB0 38660000 */  addi    r3, r6, 0
/* 074A14 80079FB4 7D09FE70 */  srawi   r9, r8, 0x1f
/* 074A18 80079FB8 7D034010 */  subfc   r8, r3, r8
/* 074A1C 80079FBC 54C60FFE */  srwi    r6, r6, 0x1f
/* 074A20 80079FC0 7CC93114 */  adde    r6, r9, r6
/* 074A24 80079FC4 7CE72E70 */  srawi   r7, r7, 5
/* 074A28 80079FC8 B0CD8AC0 */  sth     r6, flagSplit@sda21(r13)
/* 074A2C 80079FCC 7CE70734 */  extsh   r7, r7
/* 074A30 80079FD0 B0ED8AC8 */  sth     r7, tmemSrcLines@sda21(r13)
/* 074A34 80079FD4 3CC0800F */  lis     r6, TMEMSIZE@ha
/* 074A38 80079FD8 3926E270 */  addi    r9, r6, TMEMSIZE@l
/* 074A3C 80079FDC A0FA0006 */  lhz     r7, 6(r26)
/* 074A40 80079FE0 390D85F8 */  addi    r8, r13, TMEMMASK@sda21
/* 074A44 80079FE4 88DA0016 */  lbz     r6, 0x16(r26)
/* 074A48 80079FE8 394D8600 */  addi    r10, r13, TMEMSHIFT@sda21
/* 074A4C 80079FEC 7CE701D6 */  mullw   r7, r7, r0
/* 074A50 80079FF0 881A0017 */  lbz     r0, 0x17(r26)
/* 074A54 80079FF4 5400083C */  slwi    r0, r0, 1
/* 074A58 80079FF8 7CE73E70 */  srawi   r7, r7, 7
/* 074A5C 80079FFC 7E4802AE */  lhax    r18, r8, r0
/* 074A60 8007A000 7CEC3A14 */  add     r7, r12, r7
/* 074A64 8007A004 7D4A02AE */  lhax    r10, r10, r0
/* 074A68 8007A008 54C0083C */  slwi    r0, r6, 1
/* 074A6C 8007A00C 7CC90214 */  add     r6, r9, r0
/* 074A70 8007A010 A8060000 */  lha     r0, 0(r6)
/* 074A74 8007A014 7C071800 */  cmpw    r7, r3
/* 074A78 8007A018 7CE63B78 */  mr      r6, r7
/* 074A7C 8007A01C 40810008 */  ble     lbl_8007A024
/* 074A80 8007A020 7C661B78 */  mr      r6, r3
lbl_8007A024:
/* 074A84 8007A024 7CC69214 */  add     r6, r6, r18
/* 074A88 8007A028 7CC653D6 */  divw    r6, r6, r10
/* 074A8C 8007A02C 38C60001 */  addi    r6, r6, 1
/* 074A90 8007A030 B0CD8ABC */  sth     r6, tmemSliceWmax@sda21(r13)
/* 074A94 8007A034 7C840734 */  extsh   r4, r4
/* 074A98 8007A038 7C852050 */  subf    r4, r5, r4
/* 074A9C 8007A03C A12D8ABC */  lhz     r9, tmemSliceWmax@sda21(r13)
/* 074AA0 8007A040 54842835 */  rlwinm. r4, r4, 5, 0, 0x1a
/* 074AA4 8007A044 7C004BD6 */  divw    r0, r0, r9
/* 074AA8 8007A048 7C000734 */  extsh   r0, r0
/* 074AAC 8007A04C 7C130050 */  subf    r0, r19, r0
/* 074AB0 8007A050 7C190734 */  extsh   r25, r0
/* 074AB4 8007A054 5720A016 */  slwi    r0, r25, 0x14
/* 074AB8 8007A058 7EC08BD6 */  divw    r22, r0, r17
/* 074ABC 8007A05C 4080000C */  bge     lbl_8007A068
/* 074AC0 8007A060 3811FFFF */  addi    r0, r17, -1
/* 074AC4 8007A064 7C802050 */  subf    r4, r0, r4
lbl_8007A068:
/* 074AC8 8007A068 7C848BD6 */  divw    r4, r4, r17
/* 074ACC 8007A06C 5484502B */  rlwinm. r4, r4, 0xa, 0, 0x15
/* 074AD0 8007A070 4180000C */  blt     lbl_8007A07C
/* 074AD4 8007A074 7C04B3D6 */  divw    r0, r4, r22
/* 074AD8 8007A078 48000010 */  b       lbl_8007A088
lbl_8007A07C:
/* 074ADC 8007A07C 7CD62050 */  subf    r6, r22, r4
/* 074AE0 8007A080 38060001 */  addi    r0, r6, 1
/* 074AE4 8007A084 7C00B3D6 */  divw    r0, r0, r22
lbl_8007A088:
/* 074AE8 8007A088 7CF601D6 */  mullw   r7, r22, r0
/* 074AEC 8007A08C 54E6002A */  rlwinm  r6, r7, 0, 0, 0x15
/* 074AF0 8007A090 7CC62050 */  subf    r6, r6, r4
/* 074AF4 8007A094 7CC45670 */  srawi   r4, r6, 0xa
/* 074AF8 8007A098 7C8489D6 */  mullw   r4, r4, r17
/* 074AFC 8007A09C 5498DEFE */  rlwinm  r24, r4, 0x1b, 0x1b, 0x1f
/* 074B00 8007A0A0 7C845670 */  srawi   r4, r4, 0xa
/* 074B04 8007A0A4 7D1901D6 */  mullw   r8, r25, r0
/* 074B08 8007A0A8 54A00034 */  rlwinm  r0, r5, 0, 0, 0x1a
/* 074B0C 8007A0AC 7C002E70 */  srawi   r0, r0, 5
/* 074B10 8007A0B0 54E505BE */  clrlwi  r5, r7, 0x16
/* 074B14 8007A0B4 7CA5B214 */  add     r5, r5, r22
/* 074B18 8007A0B8 7C870734 */  extsh   r7, r4
/* 074B1C 8007A0BC 7C000194 */  addze   r0, r0
/* 074B20 8007A0C0 7C882214 */  add     r4, r8, r4
/* 074B24 8007A0C4 7C802214 */  add     r4, r0, r4
/* 074B28 8007A0C8 7C800734 */  extsh   r0, r4
/* 074B2C 8007A0CC 7C040735 */  extsh.  r4, r0
/* 074B30 8007A0D0 7FC62850 */  subf    r30, r6, r5
/* 074B34 8007A0D4 7E87C850 */  subf    r20, r7, r25
/* 074B38 8007A0D8 40800010 */  bge     lbl_8007A0E8
/* 074B3C 8007A0DC A09A000A */  lhz     r4, 0xa(r26)
/* 074B40 8007A0E0 7C841670 */  srawi   r4, r4, 2
/* 074B44 8007A0E4 7C002214 */  add     r0, r0, r4
lbl_8007A0E8:
/* 074B48 8007A0E8 A09A000A */  lhz     r4, 0xa(r26)
/* 074B4C 8007A0EC 7C050734 */  extsh   r5, r0
/* 074B50 8007A0F0 7C841670 */  srawi   r4, r4, 2
/* 074B54 8007A0F4 7C052000 */  cmpw    r5, r4
/* 074B58 8007A0F8 41800008 */  blt     lbl_8007A100
/* 074B5C 8007A0FC 7C040050 */  subf    r0, r4, r0
lbl_8007A100:
/* 074B60 8007A100 7C8353D6 */  divw    r4, r3, r10
/* 074B64 8007A104 807A0010 */  lwz     r3, 0x10(r26)
/* 074B68 8007A108 906D8AC4 */  stw     r3, imageTop@sda21(r13)
/* 074B6C 8007A10C 80AD8AC4 */  lwz     r5, imageTop@sda21(r13)
/* 074B70 8007A110 7C6B53D6 */  divw    r3, r11, r10
/* 074B74 8007A114 54841C38 */  rlwinm  r4, r4, 3, 0x10, 0x1c
/* 074B78 8007A118 B08D8ABE */  sth     r4, imageSrcWsize@sda21(r13)
/* 074B7C 8007A11C 54631C38 */  rlwinm  r3, r3, 3, 0x10, 0x1c
/* 074B80 8007A120 7C130734 */  extsh   r19, r0
/* 074B84 8007A124 A08D8ABE */  lhz     r4, imageSrcWsize@sda21(r13)
/* 074B88 8007A128 7D729038 */  and     r18, r11, r18
/* 074B8C 8007A12C B06D8AC2 */  sth     r3, imagePtrX0@sda21(r13)
/* 074B90 8007A130 7C0499D6 */  mullw   r0, r4, r19
/* 074B94 8007A134 A06D8AC2 */  lhz     r3, imagePtrX0@sda21(r13)
/* 074B98 8007A138 7C001A14 */  add     r0, r0, r3
/* 074B9C 8007A13C 7C050214 */  add     r0, r5, r0
/* 074BA0 8007A140 90010044 */  stw     r0, 0x44(r1)
/* 074BA4 8007A144 A01A001A */  lhz     r0, 0x1a(r26)
/* 074BA8 8007A148 540007FF */  clrlwi. r0, r0, 0x1f
/* 074BAC 8007A14C 41820010 */  beq     lbl_8007A15C
/* 074BB0 8007A150 7C12AA14 */  add     r0, r18, r21
/* 074BB4 8007A154 7C0000D0 */  neg     r0, r0
/* 074BB8 8007A158 5412043E */  clrlwi  r18, r0, 0x10
lbl_8007A15C:
/* 074BBC 8007A15C 7C830E70 */  srawi   r3, r4, 1
/* 074BC0 8007A160 3C830010 */  addis   r4, r3, 0x10
/* 074BC4 8007A164 5523482C */  slwi    r3, r9, 9
/* 074BC8 8007A168 3884FFFF */  addi    r4, r4, -1
/* 074BCC 8007A16C 3C030010 */  addis   r0, r3, 0x10
/* 074BD0 8007A170 908D8AB4 */  stw     r4, rdpSetTimg_w0@sda21(r13)
/* 074BD4 8007A174 3F7D0004 */  addis   r27, r29, 4
/* 074BD8 8007A178 900D8AB8 */  stw     r0, rdpSetTile_w0@sda21(r13)
/* 074BDC 8007A17C 38000002 */  li      r0, 2
/* 074BE0 8007A180 3B800000 */  li      r28, 0
/* 074BE4 8007A184 901BC48C */  stw     r0, -0x3b74(r27)
/* 074BE8 8007A188 387D0000 */  addi    r3, r29, 0
/* 074BEC 8007A18C 38800001 */  li      r4, 1
/* 074BF0 8007A190 939BC490 */  stw     r28, -0x3b70(r27)
/* 074BF4 8007A194 939BC494 */  stw     r28, -0x3b6c(r27)
/* 074BF8 8007A198 A00D8ABC */  lhz     r0, tmemSliceWmax@sda21(r13)
/* 074BFC 8007A19C 901BC498 */  stw     r0, -0x3b68(r27)
/* 074C00 8007A1A0 939BC49C */  stw     r28, -0x3b64(r27)
/* 074C04 8007A1A4 B39BC4A0 */  sth     r28, -0x3b60(r27)
/* 074C08 8007A1A8 B39BC4A2 */  sth     r28, -0x3b5e(r27)
/* 074C0C 8007A1AC B39BC4A4 */  sth     r28, -0x3b5c(r27)
/* 074C10 8007A1B0 B39BC4A6 */  sth     r28, -0x3b5a(r27)
/* 074C14 8007A1B4 B39BC4A8 */  sth     r28, -0x3b58(r27)
/* 074C18 8007A1B8 B39BC4AA */  sth     r28, -0x3b56(r27)
/* 074C1C 8007A1BC 4BFA6141 */  bl      frameDrawReset
/* 074C20 8007A1C0 2C030000 */  cmpwi   r3, 0
/* 074C24 8007A1C4 4082000C */  bne     lbl_8007A1D0
/* 074C28 8007A1C8 38600000 */  li      r3, 0
/* 074C2C 8007A1CC 480002C8 */  b       lbl_8007A494
lbl_8007A1D0:
/* 074C30 8007A1D0 887A0017 */  lbz     r3, 0x17(r26)
/* 074C34 8007A1D4 3800000F */  li      r0, 0xf
/* 074C38 8007A1D8 38A00001 */  li      r5, 1
/* 074C3C 8007A1DC 907BC358 */  stw     r3, -0x3ca8(r27)
/* 074C40 8007A1E0 387D0000 */  addi    r3, r29, 0
/* 074C44 8007A1E4 38800001 */  li      r4, 1
/* 074C48 8007A1E8 939BC35C */  stw     r28, -0x3ca4(r27)
/* 074C4C 8007A1EC A0DA0018 */  lhz     r6, 0x18(r26)
/* 074C50 8007A1F0 90DBC360 */  stw     r6, -0x3ca0(r27)
/* 074C54 8007A1F4 A0CD8ABC */  lhz     r6, tmemSliceWmax@sda21(r13)
/* 074C58 8007A1F8 90DBC364 */  stw     r6, -0x3c9c(r27)
/* 074C5C 8007A1FC 88DA0016 */  lbz     r6, 0x16(r26)
/* 074C60 8007A200 90DBC368 */  stw     r6, -0x3c98(r27)
/* 074C64 8007A204 B01BC36C */  sth     r0, -0x3c94(r27)
/* 074C68 8007A208 B01BC36E */  sth     r0, -0x3c92(r27)
/* 074C6C 8007A20C B0BBC370 */  sth     r5, -0x3c90(r27)
/* 074C70 8007A210 B0BBC372 */  sth     r5, -0x3c8e(r27)
/* 074C74 8007A214 B39BC374 */  sth     r28, -0x3c8c(r27)
/* 074C78 8007A218 B39BC376 */  sth     r28, -0x3c8a(r27)
/* 074C7C 8007A21C 4BFA60E1 */  bl      frameDrawReset
/* 074C80 8007A220 2C030000 */  cmpwi   r3, 0
/* 074C84 8007A224 4082000C */  bne     lbl_8007A230
/* 074C88 8007A228 38600000 */  li      r3, 0
/* 074C8C 8007A22C 48000268 */  b       lbl_8007A494
lbl_8007A230:
/* 074C90 8007A230 B39BC378 */  sth     r28, -0x3c88(r27)
/* 074C94 8007A234 387D0000 */  addi    r3, r29, 0
/* 074C98 8007A238 38800001 */  li      r4, 1
/* 074C9C 8007A23C B39BC37A */  sth     r28, -0x3c86(r27)
/* 074CA0 8007A240 B39BC37C */  sth     r28, -0x3c84(r27)
/* 074CA4 8007A244 B39BC37E */  sth     r28, -0x3c82(r27)
/* 074CA8 8007A248 4BFA60B5 */  bl      frameDrawReset
/* 074CAC 8007A24C 2C030000 */  cmpwi   r3, 0
/* 074CB0 8007A250 4082000C */  bne     lbl_8007A25C
/* 074CB4 8007A254 38600000 */  li      r3, 0
/* 074CB8 8007A258 4800023C */  b       lbl_8007A494
lbl_8007A25C:
/* 074CBC 8007A25C A0010052 */  lhz     r0, 0x52(r1)
/* 074CC0 8007A260 7DC30734 */  extsh   r3, r14
/* 074CC4 8007A264 A88D8AC8 */  lha     r4, tmemSrcLines@sda21(r13)
/* 074CC8 8007A268 7E87A378 */  mr      r7, r20
/* 074CCC 8007A26C 7C050734 */  extsh   r5, r0
/* 074CD0 8007A270 7C132050 */  subf    r0, r19, r4
/* 074CD4 8007A274 CBE28348 */  lfd     f31, D_80136048@sda21(r2)
/* 074CD8 8007A278 B0010040 */  sth     r0, 0x40(r1)
/* 074CDC 8007A27C 7FDCF378 */  mr      r28, r30
/* 074CE0 8007A280 C3828340 */  lfs     f28, D_80136040@sda21(r2)
/* 074CE4 8007A284 5652043E */  clrlwi  r18, r18, 0x10
/* 074CE8 8007A288 C3A28370 */  lfs     f29, D_80136070@sda21(r2)
/* 074CEC 8007A28C C3C28368 */  lfs     f30, D_80136068@sda21(r2)
/* 074CF0 8007A290 6C758000 */  xoris   r21, r3, 0x8000
/* 074CF4 8007A294 AA610050 */  lha     r19, 0x50(r1)
/* 074CF8 8007A298 6CB48000 */  xoris   r20, r5, 0x8000
/* 074CFC 8007A29C 3F604330 */  lis     r27, 0x4330
lbl_8007A2A0:
/* 074D00 8007A2A0 7F805670 */  srawi   r0, r28, 0xa
/* 074D04 8007A2A4 7C1E0734 */  extsh   r30, r0
/* 074D08 8007A2A8 7FC00735 */  extsh.  r0, r30
/* 074D0C 8007A2AC 41810064 */  bgt     lbl_8007A310
/* 074D10 8007A2B0 A8010040 */  lha     r0, 0x40(r1)
/* 074D14 8007A2B4 7C070050 */  subf    r0, r7, r0
/* 074D18 8007A2B8 B0010040 */  sth     r0, 0x40(r1)
/* 074D1C 8007A2BC A8010040 */  lha     r0, 0x40(r1)
/* 074D20 8007A2C0 7C030735 */  extsh.  r3, r0
/* 074D24 8007A2C4 40810020 */  ble     lbl_8007A2E4
/* 074D28 8007A2C8 A06D8ABE */  lhz     r3, imageSrcWsize@sda21(r13)
/* 074D2C 8007A2CC 7CE00734 */  extsh   r0, r7
/* 074D30 8007A2D0 80810044 */  lwz     r4, 0x44(r1)
/* 074D34 8007A2D4 7C0301D6 */  mullw   r0, r3, r0
/* 074D38 8007A2D8 7C040214 */  add     r0, r4, r0
/* 074D3C 8007A2DC 90010044 */  stw     r0, 0x44(r1)
/* 074D40 8007A2E0 480001A4 */  b       lbl_8007A484
lbl_8007A2E4:
/* 074D44 8007A2E4 A06D8ABE */  lhz     r3, imageSrcWsize@sda21(r13)
/* 074D48 8007A2E8 A8CD8AC8 */  lha     r6, tmemSrcLines@sda21(r13)
/* 074D4C 8007A2EC 7C8019D6 */  mullw   r4, r0, r3
/* 074D50 8007A2F0 806D8AC4 */  lwz     r3, imageTop@sda21(r13)
/* 074D54 8007A2F4 A0AD8AC2 */  lhz     r5, imagePtrX0@sda21(r13)
/* 074D58 8007A2F8 7C641850 */  subf    r3, r4, r3
/* 074D5C 8007A2FC 7C651A14 */  add     r3, r5, r3
/* 074D60 8007A300 7C003214 */  add     r0, r0, r6
/* 074D64 8007A304 90610044 */  stw     r3, 0x44(r1)
/* 074D68 8007A308 B0010040 */  sth     r0, 0x40(r1)
/* 074D6C 8007A30C 48000178 */  b       lbl_8007A484
lbl_8007A310:
/* 074D70 8007A310 7FFEF850 */  subf    r31, r30, r31
/* 074D74 8007A314 7FE00735 */  extsh.  r0, r31
/* 074D78 8007A318 579C05BE */  clrlwi  r28, r28, 0x16
/* 074D7C 8007A31C 4080002C */  bge     lbl_8007A348
/* 074D80 8007A320 7FE00734 */  extsh   r0, r31
/* 074D84 8007A324 7C0089D6 */  mullw   r0, r0, r17
/* 074D88 8007A328 7C005670 */  srawi   r0, r0, 0xa
/* 074D8C 8007A32C 7CE03A14 */  add     r7, r0, r7
/* 074D90 8007A330 38E70001 */  addi    r7, r7, 1
/* 074D94 8007A334 7CE00734 */  extsh   r0, r7
/* 074D98 8007A338 7C00C800 */  cmpw    r0, r25
/* 074D9C 8007A33C 7FDEFA14 */  add     r30, r30, r31
/* 074DA0 8007A340 40810008 */  ble     lbl_8007A348
/* 074DA4 8007A344 7F27CB78 */  mr      r7, r25
lbl_8007A348:
/* 074DA8 8007A348 890D8AB0 */  lbz     r8, flagBilerp@sda21(r13)
/* 074DAC 8007A34C 387D0000 */  addi    r3, r29, 0
/* 074DB0 8007A350 388F0000 */  addi    r4, r15, 0
/* 074DB4 8007A354 38A10044 */  addi    r5, r1, 0x44
/* 074DB8 8007A358 38C10040 */  addi    r6, r1, 0x40
/* 074DBC 8007A35C 4800015D */  bl      tmemLoad
/* 074DC0 8007A360 38600000 */  li      r3, 0
/* 074DC4 8007A364 92A10064 */  stw     r21, 0x64(r1)
/* 074DC8 8007A368 7EE00734 */  extsh   r0, r23
/* 074DCC 8007A36C 9061001C */  stw     r3, 0x1c(r1)
/* 074DD0 8007A370 7FC0F214 */  add     r30, r0, r30
/* 074DD4 8007A374 90610018 */  stw     r3, 0x18(r1)
/* 074DD8 8007A378 8061001C */  lwz     r3, 0x1c(r1)
/* 074DDC 8007A37C 93610060 */  stw     r27, 0x60(r1)
/* 074DE0 8007A380 1C63002C */  mulli   r3, r3, 0x2c
/* 074DE4 8007A384 9281005C */  stw     r20, 0x5c(r1)
/* 074DE8 8007A388 C8010060 */  lfd     f0, 0x60(r1)
/* 074DEC 8007A38C 7C7D1A14 */  add     r3, r29, r3
/* 074DF0 8007A390 93610058 */  stw     r27, 0x58(r1)
/* 074DF4 8007A394 3C630004 */  addis   r3, r3, 4
/* 074DF8 8007A398 EC20F828 */  fsubs   f1, f0, f31
/* 074DFC 8007A39C A883C378 */  lha     r4, -0x3c88(r3)
/* 074E00 8007A3A0 A863C37A */  lha     r3, -0x3c86(r3)
/* 074E04 8007A3A4 54841838 */  slwi    r4, r4, 3
/* 074E08 8007A3A8 C8010058 */  lfd     f0, 0x58(r1)
/* 074E0C 8007A3AC 7C849050 */  subf    r4, r4, r18
/* 074E10 8007A3B0 EC210772 */  fmuls   f1, f1, f29
/* 074E14 8007A3B4 54631838 */  slwi    r3, r3, 3
/* 074E18 8007A3B8 EC00F828 */  fsubs   f0, f0, f31
/* 074E1C 8007A3BC 7C840734 */  extsh   r4, r4
/* 074E20 8007A3C0 7C63C050 */  subf    r3, r3, r24
/* 074E24 8007A3C4 6C848000 */  xoris   r4, r4, 0x8000
/* 074E28 8007A3C8 EC000772 */  fmuls   f0, f0, f29
/* 074E2C 8007A3CC 90810074 */  stw     r4, 0x74(r1)
/* 074E30 8007A3D0 7C630734 */  extsh   r3, r3
/* 074E34 8007A3D4 6C638000 */  xoris   r3, r3, 0x8000
/* 074E38 8007A3D8 93610070 */  stw     r27, 0x70(r1)
/* 074E3C 8007A3DC 9061006C */  stw     r3, 0x6c(r1)
/* 074E40 8007A3E0 C8410070 */  lfd     f2, 0x70(r1)
/* 074E44 8007A3E4 93610068 */  stw     r27, 0x68(r1)
/* 074E48 8007A3E8 EC62F828 */  fsubs   f3, f2, f31
/* 074E4C 8007A3EC C8410068 */  lfd     f2, 0x68(r1)
/* 074E50 8007A3F0 EC42F828 */  fsubs   f2, f2, f31
/* 074E54 8007A3F4 EC630732 */  fmuls   f3, f3, f28
/* 074E58 8007A3F8 EC420732 */  fmuls   f2, f2, f28
/* 074E5C 8007A3FC D0610030 */  stfs    f3, 0x30(r1)
/* 074E60 8007A400 D0410034 */  stfs    f2, 0x34(r1)
/* 074E64 8007A404 D0210038 */  stfs    f1, 0x38(r1)
/* 074E68 8007A408 D001003C */  stfs    f0, 0x3c(r1)
/* 074E6C 8007A40C A07A001A */  lhz     r3, 0x1a(r26)
/* 074E70 8007A410 546307FF */  clrlwi. r3, r3, 0x1f
/* 074E74 8007A414 4182001C */  beq     lbl_8007A430
/* 074E78 8007A418 C0010030 */  lfs     f0, 0x30(r1)
/* 074E7C 8007A41C EC0007B2 */  fmuls   f0, f0, f30
/* 074E80 8007A420 D0010030 */  stfs    f0, 0x30(r1)
/* 074E84 8007A424 C0010038 */  lfs     f0, 0x38(r1)
/* 074E88 8007A428 EC0007B2 */  fmuls   f0, f0, f30
/* 074E8C 8007A42C D0010038 */  stfs    f0, 0x38(r1)
lbl_8007A430:
/* 074E90 8007A430 92010020 */  stw     r16, 0x20(r1)
/* 074E94 8007A434 5403103A */  slwi    r3, r0, 2
/* 074E98 8007A438 7FC00734 */  extsh   r0, r30
/* 074E9C 8007A43C 90610024 */  stw     r3, 0x24(r1)
/* 074EA0 8007A440 5400103A */  slwi    r0, r0, 2
/* 074EA4 8007A444 387D0000 */  addi    r3, r29, 0
/* 074EA8 8007A448 92610028 */  stw     r19, 0x28(r1)
/* 074EAC 8007A44C 38810018 */  addi    r4, r1, 0x18
/* 074EB0 8007A450 9001002C */  stw     r0, 0x2c(r1)
/* 074EB4 8007A454 819D0138 */  lwz     r12, 0x138(r29)
/* 074EB8 8007A458 7D8803A6 */  mtlr    r12
/* 074EBC 8007A45C 4E800021 */  blrl    
/* 074EC0 8007A460 2C030000 */  cmpwi   r3, 0
/* 074EC4 8007A464 4082000C */  bne     lbl_8007A470
/* 074EC8 8007A468 38600000 */  li      r3, 0
/* 074ECC 8007A46C 48000028 */  b       lbl_8007A494
lbl_8007A470:
/* 074ED0 8007A470 7FE00735 */  extsh.  r0, r31
/* 074ED4 8007A474 3AFE0000 */  addi    r23, r30, 0
/* 074ED8 8007A478 4181000C */  bgt     lbl_8007A484
/* 074EDC 8007A47C 38600001 */  li      r3, 1
/* 074EE0 8007A480 48000014 */  b       lbl_8007A494
lbl_8007A484:
/* 074EE4 8007A484 38F90000 */  addi    r7, r25, 0
/* 074EE8 8007A488 7F9CB214 */  add     r28, r28, r22
/* 074EEC 8007A48C 3B000000 */  li      r24, 0
/* 074EF0 8007A490 4BFFFE10 */  b       lbl_8007A2A0
lbl_8007A494:
/* 074EF4 8007A494 B9C10078 */  lmw     r14, 0x78(r1)
/* 074EF8 8007A498 800100E4 */  lwz     r0, 0xe4(r1)
/* 074EFC 8007A49C CBE100D8 */  lfd     f31, 0xd8(r1)
/* 074F00 8007A4A0 CBC100D0 */  lfd     f30, 0xd0(r1)
/* 074F04 8007A4A4 7C0803A6 */  mtlr    r0
/* 074F08 8007A4A8 CBA100C8 */  lfd     f29, 0xc8(r1)
/* 074F0C 8007A4AC CB8100C0 */  lfd     f28, 0xc0(r1)
/* 074F10 8007A4B0 382100E0 */  addi    r1, r1, 0xe0
/* 074F14 8007A4B4 4E800020 */  blr     
