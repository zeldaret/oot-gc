glabel libraryTestFunction
/* 089FE4 8008F584 7C0802A6 */  mflr    r0
/* 089FE8 8008F588 90010004 */  stw     r0, 4(r1)
/* 089FEC 8008F58C 9421FF88 */  stwu    r1, -0x78(r1)
/* 089FF0 8008F590 BDC10030 */  stmw    r14, 0x30(r1)
/* 089FF4 8008F594 3B440000 */  addi    r26, r4, 0
/* 089FF8 8008F598 7C7E1B78 */  mr      r30, r3
/* 089FFC 8008F59C 3C80800F */  lis     r4, D_800EEB00@ha
/* 08A000 8008F5A0 3B24EB00 */  addi    r25, r4, D_800EEB00@l
/* 08A004 8008F5A4 38BA0000 */  addi    r5, r26, 0
/* 08A008 8008F5A8 38810014 */  addi    r4, r1, 0x14
/* 08A00C 8008F5AC 80630004 */  lwz     r3, 4(r3)
/* 08A010 8008F5B0 80630024 */  lwz     r3, 0x24(r3)
/* 08A014 8008F5B4 4BFA4D71 */  bl      cpuGetFunctionChecksum
/* 08A018 8008F5B8 2C030000 */  cmpwi   r3, 0
/* 08A01C 8008F5BC 4082000C */  bne     lbl_8008F5C8
/* 08A020 8008F5C0 38600000 */  li      r3, 0
/* 08A024 8008F5C4 48000594 */  b       lbl_8008FB58
lbl_8008F5C8:
/* 08A028 8008F5C8 807A0010 */  lwz     r3, 0x10(r26)
/* 08A02C 8008F5CC 3CE08009 */  lis     r7, GenPerspective_1080@ha
/* 08A030 8008F5D0 801A0014 */  lwz     r0, 0x14(r26)
/* 08A034 8008F5D4 3C808009 */  lis     r4, __osDisableInt@ha
/* 08A038 8008F5D8 3CA08009 */  lis     r5, zeldaLoadSZS_Entry@ha
/* 08A03C 8008F5DC 7C030050 */  subf    r0, r3, r0
/* 08A040 8008F5E0 7C031670 */  srawi   r3, r0, 2
/* 08A044 8008F5E4 38050AC4 */  addi    r0, r5, zeldaLoadSZS_Entry@l
/* 08A048 8008F5E8 3B830001 */  addi    r28, r3, 1
/* 08A04C 8008F5EC 90010024 */  stw     r0, 0x24(r1)
/* 08A050 8008F5F0 3CC08009 */  lis     r6, pictureSnap_Zelda2@ha
/* 08A054 8008F5F4 38060C68 */  addi    r0, r6, pictureSnap_Zelda2@l
/* 08A058 8008F5F8 3C608009 */  lis     r3, osViSwapBuffer_Entry@ha
/* 08A05C 8008F5FC 90010020 */  stw     r0, 0x20(r1)
/* 08A060 8008F600 3D808009 */  lis     r12, dmaSoundRomHandler_ZELDA1@ha
/* 08A064 8008F604 380C0B40 */  addi    r0, r12, dmaSoundRomHandler_ZELDA1@l
/* 08A068 8008F608 3D008009 */  lis     r8, osInvalICache@ha
/* 08A06C 8008F60C 90010028 */  stw     r0, 0x28(r1)
/* 08A070 8008F610 3D208009 */  lis     r9, __osSpSetStatus@ha
/* 08A074 8008F614 3D408009 */  lis     r10, osEepromLongWrite@ha
/* 08A078 8008F618 3D608009 */  lis     r11, osEepromLongRead@ha
/* 08A07C 8008F61C 39C745A8 */  addi    r14, r7, GenPerspective_1080@l
/* 08A080 8008F620 39E30AD8 */  addi    r15, r3, osViSwapBuffer_Entry@l
/* 08A084 8008F624 3A045A30 */  addi    r16, r4, __osDisableInt@l
/* 08A088 8008F628 3A285AC0 */  addi    r17, r8, osInvalICache@l
/* 08A08C 8008F62C 3ADCFFF8 */  addi    r22, r28, -8
/* 08A090 8008F630 3A495954 */  addi    r18, r9, __osSpSetStatus@l
/* 08A094 8008F634 3A6A0DE0 */  addi    r19, r10, osEepromLongWrite@l
/* 08A098 8008F638 3A8B0E8C */  addi    r20, r11, osEepromLongRead@l
/* 08A09C 8008F63C 3BE00000 */  li      r31, 0
/* 08A0A0 8008F640 480004FC */  b       lbl_8008FB3C
lbl_8008F644:
/* 08A0A4 8008F644 3B000000 */  li      r24, 0
/* 08A0A8 8008F648 3AE00000 */  li      r23, 0
/* 08A0AC 8008F64C 480004D0 */  b       lbl_8008FB1C
lbl_8008F650:
/* 08A0B0 8008F650 80010014 */  lwz     r0, 0x14(r1)
/* 08A0B4 8008F654 8063000C */  lwz     r3, 0xc(r3)
/* 08A0B8 8008F658 7C001840 */  cmplw   r0, r3
/* 08A0BC 8008F65C 408204B8 */  bne     lbl_8008FB14
/* 08A0C0 8008F660 7C1C2040 */  cmplw   r28, r4
/* 08A0C4 8008F664 408204B0 */  bne     lbl_8008FB14
/* 08A0C8 8008F668 807E0004 */  lwz     r3, 4(r30)
/* 08A0CC 8008F66C 3881001C */  addi    r4, r1, 0x1c
/* 08A0D0 8008F670 80BA0010 */  lwz     r5, 0x10(r26)
/* 08A0D4 8008F674 3B600000 */  li      r27, 0
/* 08A0D8 8008F678 80630024 */  lwz     r3, 0x24(r3)
/* 08A0DC 8008F67C 3AA00001 */  li      r21, 1
/* 08A0E0 8008F680 4BFA5101 */  bl      cpuGetAddressBuffer
/* 08A0E4 8008F684 2C030000 */  cmpwi   r3, 0
/* 08A0E8 8008F688 4082000C */  bne     lbl_8008F694
/* 08A0EC 8008F68C 38600000 */  li      r3, 0
/* 08A0F0 8008F690 480004C8 */  b       lbl_8008FB58
lbl_8008F694:
/* 08A0F4 8008F694 8061001C */  lwz     r3, 0x1c(r1)
/* 08A0F8 8008F698 80C30000 */  lwz     r6, 0(r3)
/* 08A0FC 8008F69C 54C036BE */  srwi    r0, r6, 0x1a
/* 08A100 8008F6A0 2800001F */  cmplwi  r0, 0x1f
/* 08A104 8008F6A4 4082000C */  bne     lbl_8008F6B0
/* 08A108 8008F6A8 38000000 */  li      r0, 0
/* 08A10C 8008F6AC 48000008 */  b       lbl_8008F6B4
lbl_8008F6B0:
/* 08A110 8008F6B0 38000001 */  li      r0, 1
lbl_8008F6B4:
/* 08A114 8008F6B4 809D0004 */  lwz     r4, 4(r29)
/* 08A118 8008F6B8 7C1D0378 */  mr      r29, r0
/* 08A11C 8008F6BC 7C04A040 */  cmplw   r4, r20
/* 08A120 8008F6C0 40820064 */  bne     lbl_8008F724
/* 08A124 8008F6C4 80A10014 */  lwz     r5, 0x14(r1)
/* 08A128 8008F6C8 3CA5A46F */  addis   r5, r5, 0xa46f
/* 08A12C 8008F6CC 28059EF9 */  cmplwi  r5, 0x9ef9
/* 08A130 8008F6D0 40820054 */  bne     lbl_8008F724
/* 08A134 8008F6D4 80A30044 */  lwz     r5, 0x44(r3)
/* 08A138 8008F6D8 38810018 */  addi    r4, r1, 0x18
/* 08A13C 8008F6DC 807E0004 */  lwz     r3, 4(r30)
/* 08A140 8008F6E0 801A0010 */  lwz     r0, 0x10(r26)
/* 08A144 8008F6E4 54A5113A */  rlwinm  r5, r5, 2, 4, 0x1d
/* 08A148 8008F6E8 80630024 */  lwz     r3, 0x24(r3)
/* 08A14C 8008F6EC 50050006 */  rlwimi  r5, r0, 0, 0, 3
/* 08A150 8008F6F0 4BFA5091 */  bl      cpuGetAddressBuffer
/* 08A154 8008F6F4 2C030000 */  cmpwi   r3, 0
/* 08A158 8008F6F8 4082000C */  bne     lbl_8008F704
/* 08A15C 8008F6FC 38600000 */  li      r3, 0
/* 08A160 8008F700 48000458 */  b       lbl_8008FB58
lbl_8008F704:
/* 08A164 8008F704 80610018 */  lwz     r3, 0x18(r1)
/* 08A168 8008F708 80630028 */  lwz     r3, 0x28(r3)
/* 08A16C 8008F70C 3C035060 */  addis   r0, r3, 0x5060
/* 08A170 8008F710 28000030 */  cmplwi  r0, 0x30
/* 08A174 8008F714 41820394 */  beq     lbl_8008FAA8
/* 08A178 8008F718 3B600001 */  li      r27, 1
/* 08A17C 8008F71C 3BFF0001 */  addi    r31, r31, 1
/* 08A180 8008F720 48000388 */  b       lbl_8008FAA8
lbl_8008F724:
/* 08A184 8008F724 7C049840 */  cmplw   r4, r19
/* 08A188 8008F728 40820064 */  bne     lbl_8008F78C
/* 08A18C 8008F72C 80A10014 */  lwz     r5, 0x14(r1)
/* 08A190 8008F730 3CA5A46F */  addis   r5, r5, 0xa46f
/* 08A194 8008F734 28059EF9 */  cmplwi  r5, 0x9ef9
/* 08A198 8008F738 40820054 */  bne     lbl_8008F78C
/* 08A19C 8008F73C 80A30044 */  lwz     r5, 0x44(r3)
/* 08A1A0 8008F740 38810018 */  addi    r4, r1, 0x18
/* 08A1A4 8008F744 807E0004 */  lwz     r3, 4(r30)
/* 08A1A8 8008F748 801A0010 */  lwz     r0, 0x10(r26)
/* 08A1AC 8008F74C 54A5113A */  rlwinm  r5, r5, 2, 4, 0x1d
/* 08A1B0 8008F750 80630024 */  lwz     r3, 0x24(r3)
/* 08A1B4 8008F754 50050006 */  rlwimi  r5, r0, 0, 0, 3
/* 08A1B8 8008F758 4BFA5029 */  bl      cpuGetAddressBuffer
/* 08A1BC 8008F75C 2C030000 */  cmpwi   r3, 0
/* 08A1C0 8008F760 4082000C */  bne     lbl_8008F76C
/* 08A1C4 8008F764 38600000 */  li      r3, 0
/* 08A1C8 8008F768 480003F0 */  b       lbl_8008FB58
lbl_8008F76C:
/* 08A1CC 8008F76C 80610018 */  lwz     r3, 0x18(r1)
/* 08A1D0 8008F770 80630028 */  lwz     r3, 0x28(r3)
/* 08A1D4 8008F774 3C035060 */  addis   r0, r3, 0x5060
/* 08A1D8 8008F778 28000030 */  cmplwi  r0, 0x30
/* 08A1DC 8008F77C 4082032C */  bne     lbl_8008FAA8
/* 08A1E0 8008F780 3B600001 */  li      r27, 1
/* 08A1E4 8008F784 3BFFFFFF */  addi    r31, r31, -1
/* 08A1E8 8008F788 48000320 */  b       lbl_8008FAA8
lbl_8008F78C:
/* 08A1EC 8008F78C 7C049040 */  cmplw   r4, r18
/* 08A1F0 8008F790 40820120 */  bne     lbl_8008F8B0
/* 08A1F4 8008F794 38000000 */  li      r0, 0
/* 08A1F8 8008F798 281C0000 */  cmplwi  r28, 0
/* 08A1FC 8008F79C 90010014 */  stw     r0, 0x14(r1)
/* 08A200 8008F7A0 38A00000 */  li      r5, 0
/* 08A204 8008F7A4 408100DC */  ble     lbl_8008F880
/* 08A208 8008F7A8 281C0008 */  cmplwi  r28, 8
/* 08A20C 8008F7AC 408103A0 */  ble     lbl_8008FB4C
/* 08A210 8008F7B0 38160007 */  addi    r0, r22, 7
/* 08A214 8008F7B4 5400E8FE */  srwi    r0, r0, 3
/* 08A218 8008F7B8 28160000 */  cmplwi  r22, 0
/* 08A21C 8008F7BC 7C0903A6 */  mtctr   r0
/* 08A220 8008F7C0 38830000 */  addi    r4, r3, 0
/* 08A224 8008F7C4 40810388 */  ble     lbl_8008FB4C
lbl_8008F7C8:
/* 08A228 8008F7C8 80C10014 */  lwz     r6, 0x14(r1)
/* 08A22C 8008F7CC 38A50008 */  addi    r5, r5, 8
/* 08A230 8008F7D0 80040000 */  lwz     r0, 0(r4)
/* 08A234 8008F7D4 7C060214 */  add     r0, r6, r0
/* 08A238 8008F7D8 90010014 */  stw     r0, 0x14(r1)
/* 08A23C 8008F7DC 80C10014 */  lwz     r6, 0x14(r1)
/* 08A240 8008F7E0 80040004 */  lwz     r0, 4(r4)
/* 08A244 8008F7E4 7C060214 */  add     r0, r6, r0
/* 08A248 8008F7E8 90010014 */  stw     r0, 0x14(r1)
/* 08A24C 8008F7EC 80C10014 */  lwz     r6, 0x14(r1)
/* 08A250 8008F7F0 80040008 */  lwz     r0, 8(r4)
/* 08A254 8008F7F4 7C060214 */  add     r0, r6, r0
/* 08A258 8008F7F8 90010014 */  stw     r0, 0x14(r1)
/* 08A25C 8008F7FC 80C10014 */  lwz     r6, 0x14(r1)
/* 08A260 8008F800 8004000C */  lwz     r0, 0xc(r4)
/* 08A264 8008F804 7C060214 */  add     r0, r6, r0
/* 08A268 8008F808 90010014 */  stw     r0, 0x14(r1)
/* 08A26C 8008F80C 80C10014 */  lwz     r6, 0x14(r1)
/* 08A270 8008F810 80040010 */  lwz     r0, 0x10(r4)
/* 08A274 8008F814 7C060214 */  add     r0, r6, r0
/* 08A278 8008F818 90010014 */  stw     r0, 0x14(r1)
/* 08A27C 8008F81C 80C10014 */  lwz     r6, 0x14(r1)
/* 08A280 8008F820 80040014 */  lwz     r0, 0x14(r4)
/* 08A284 8008F824 7C060214 */  add     r0, r6, r0
/* 08A288 8008F828 90010014 */  stw     r0, 0x14(r1)
/* 08A28C 8008F82C 80C10014 */  lwz     r6, 0x14(r1)
/* 08A290 8008F830 80040018 */  lwz     r0, 0x18(r4)
/* 08A294 8008F834 7C060214 */  add     r0, r6, r0
/* 08A298 8008F838 90010014 */  stw     r0, 0x14(r1)
/* 08A29C 8008F83C 8004001C */  lwz     r0, 0x1c(r4)
/* 08A2A0 8008F840 38840020 */  addi    r4, r4, 0x20
/* 08A2A4 8008F844 80C10014 */  lwz     r6, 0x14(r1)
/* 08A2A8 8008F848 7C060214 */  add     r0, r6, r0
/* 08A2AC 8008F84C 90010014 */  stw     r0, 0x14(r1)
/* 08A2B0 8008F850 4200FF78 */  bdnz    lbl_8008F7C8
/* 08A2B4 8008F854 480002F8 */  b       lbl_8008FB4C
lbl_8008F858:
/* 08A2B8 8008F858 7C05E050 */  subf    r0, r5, r28
/* 08A2BC 8008F85C 7C05E040 */  cmplw   r5, r28
/* 08A2C0 8008F860 7C0903A6 */  mtctr   r0
/* 08A2C4 8008F864 4080001C */  bge     lbl_8008F880
lbl_8008F868:
/* 08A2C8 8008F868 80030000 */  lwz     r0, 0(r3)
/* 08A2CC 8008F86C 38630004 */  addi    r3, r3, 4
/* 08A2D0 8008F870 80810014 */  lwz     r4, 0x14(r1)
/* 08A2D4 8008F874 7C040214 */  add     r0, r4, r0
/* 08A2D8 8008F878 90010014 */  stw     r0, 0x14(r1)
/* 08A2DC 8008F87C 4200FFEC */  bdnz    lbl_8008F868
lbl_8008F880:
/* 08A2E0 8008F880 80610014 */  lwz     r3, 0x14(r1)
/* 08A2E4 8008F884 3C033E1E */  addis   r0, r3, 0x3e1e
/* 08A2E8 8008F888 28007C6E */  cmplwi  r0, 0x7c6e
/* 08A2EC 8008F88C 4182021C */  beq     lbl_8008FAA8
/* 08A2F0 8008F890 3C03124E */  addis   r0, r3, 0x124e
/* 08A2F4 8008F894 2800A41C */  cmplwi  r0, 0xa41c
/* 08A2F8 8008F898 41820210 */  beq     lbl_8008FAA8
/* 08A2FC 8008F89C 3C03DF98 */  addis   r0, r3, 0xdf98
/* 08A300 8008F8A0 2800A41C */  cmplwi  r0, 0xa41c
/* 08A304 8008F8A4 41820204 */  beq     lbl_8008FAA8
/* 08A308 8008F8A8 3BA00000 */  li      r29, 0
/* 08A30C 8008F8AC 480001FC */  b       lbl_8008FAA8
lbl_8008F8B0:
/* 08A310 8008F8B0 7C048840 */  cmplw   r4, r17
/* 08A314 8008F8B4 40820020 */  bne     lbl_8008F8D4
/* 08A318 8008F8B8 80030008 */  lwz     r0, 8(r3)
/* 08A31C 8008F8BC 5400043E */  clrlwi  r0, r0, 0x10
/* 08A320 8008F8C0 28002000 */  cmplwi  r0, 0x2000
/* 08A324 8008F8C4 408201E4 */  bne     lbl_8008FAA8
/* 08A328 8008F8C8 3B600001 */  li      r27, 1
/* 08A32C 8008F8CC 3BFF0001 */  addi    r31, r31, 1
/* 08A330 8008F8D0 480001D8 */  b       lbl_8008FAA8
lbl_8008F8D4:
/* 08A334 8008F8D4 28040000 */  cmplwi  r4, 0
/* 08A338 8008F8D8 40820030 */  bne     lbl_8008F908
/* 08A33C 8008F8DC 80A10014 */  lwz     r5, 0x14(r1)
/* 08A340 8008F8E0 3CA5C897 */  addis   r5, r5, 0xc897
/* 08A344 8008F8E4 280579EF */  cmplwi  r5, 0x79ef
/* 08A348 8008F8E8 40820020 */  bne     lbl_8008F908
/* 08A34C 8008F8EC 80030008 */  lwz     r0, 8(r3)
/* 08A350 8008F8F0 5400043E */  clrlwi  r0, r0, 0x10
/* 08A354 8008F8F4 28004000 */  cmplwi  r0, 0x4000
/* 08A358 8008F8F8 408201B0 */  bne     lbl_8008FAA8
/* 08A35C 8008F8FC 3B600001 */  li      r27, 1
/* 08A360 8008F900 3BFFFFFF */  addi    r31, r31, -1
/* 08A364 8008F904 480001A4 */  b       lbl_8008FAA8
lbl_8008F908:
/* 08A368 8008F908 7C048040 */  cmplw   r4, r16
/* 08A36C 8008F90C 40820068 */  bne     lbl_8008F974
/* 08A370 8008F910 80030008 */  lwz     r0, 8(r3)
/* 08A374 8008F914 28000000 */  cmplwi  r0, 0
/* 08A378 8008F918 40820190 */  bne     lbl_8008FAA8
/* 08A37C 8008F91C 8003000C */  lwz     r0, 0xc(r3)
/* 08A380 8008F920 28000000 */  cmplwi  r0, 0
/* 08A384 8008F924 40820184 */  bne     lbl_8008FAA8
/* 08A388 8008F928 8061001C */  lwz     r3, 0x1c(r1)
/* 08A38C 8008F92C 38030010 */  addi    r0, r3, 0x10
/* 08A390 8008F930 9001001C */  stw     r0, 0x1c(r1)
/* 08A394 8008F934 48000010 */  b       lbl_8008F944
lbl_8008F938:
/* 08A398 8008F938 8061001C */  lwz     r3, 0x1c(r1)
/* 08A39C 8008F93C 38030004 */  addi    r0, r3, 4
/* 08A3A0 8008F940 9001001C */  stw     r0, 0x1c(r1)
lbl_8008F944:
/* 08A3A4 8008F944 8061001C */  lwz     r3, 0x1c(r1)
/* 08A3A8 8008F948 80030000 */  lwz     r0, 0(r3)
/* 08A3AC 8008F94C 28000000 */  cmplwi  r0, 0
/* 08A3B0 8008F950 4182FFE8 */  beq     lbl_8008F938
/* 08A3B4 8008F954 540036BE */  srwi    r0, r0, 0x1a
/* 08A3B8 8008F958 2800001F */  cmplwi  r0, 0x1f
/* 08A3BC 8008F95C 4082000C */  bne     lbl_8008F968
/* 08A3C0 8008F960 38000000 */  li      r0, 0
/* 08A3C4 8008F964 48000008 */  b       lbl_8008F96C
lbl_8008F968:
/* 08A3C8 8008F968 38000001 */  li      r0, 1
lbl_8008F96C:
/* 08A3CC 8008F96C 7C1D0378 */  mr      r29, r0
/* 08A3D0 8008F970 48000138 */  b       lbl_8008FAA8
lbl_8008F974:
/* 08A3D4 8008F974 7C047840 */  cmplw   r4, r15
/* 08A3D8 8008F978 40820048 */  bne     lbl_8008F9C0
/* 08A3DC 8008F97C 2C000000 */  cmpwi   r0, 0
/* 08A3E0 8008F980 41820128 */  beq     lbl_8008FAA8
/* 08A3E4 8008F984 54C3001E */  rlwinm  r3, r6, 0, 0, 0xf
/* 08A3E8 8008F988 3C03D843 */  addis   r0, r3, 0xd843
/* 08A3EC 8008F98C 28000000 */  cmplwi  r0, 0
/* 08A3F0 8008F990 3AA00000 */  li      r21, 0
/* 08A3F4 8008F994 4182001C */  beq     lbl_8008F9B0
/* 08A3F8 8008F998 4CC63182 */  crclr   6
/* 08A3FC 8008F99C 38791434 */  addi    r3, r25, 0x1434
/* 08A400 8008F9A0 3899147C */  addi    r4, r25, 0x147c
/* 08A404 8008F9A4 38A01B3B */  li      r5, 0x1b3b
/* 08A408 8008F9A8 4BF7646D */  bl      xlPostText
/* 08A40C 8008F9AC 480000FC */  b       lbl_8008FAA8
lbl_8008F9B0:
/* 08A410 8008F9B0 54C0043E */  clrlwi  r0, r6, 0x10
/* 08A414 8008F9B4 7C000734 */  extsh   r0, r0
/* 08A418 8008F9B8 901E0008 */  stw     r0, 8(r30)
/* 08A41C 8008F9BC 480000EC */  b       lbl_8008FAA8
lbl_8008F9C0:
/* 08A420 8008F9C0 7C047040 */  cmplw   r4, r14
/* 08A424 8008F9C4 4082001C */  bne     lbl_8008F9E0
/* 08A428 8008F9C8 807E0004 */  lwz     r3, 4(r30)
/* 08A42C 8008F9CC 80030020 */  lwz     r0, 0x20(r3)
/* 08A430 8008F9D0 2C000006 */  cmpwi   r0, 6
/* 08A434 8008F9D4 418200D4 */  beq     lbl_8008FAA8
/* 08A438 8008F9D8 3BA00000 */  li      r29, 0
/* 08A43C 8008F9DC 480000CC */  b       lbl_8008FAA8
lbl_8008F9E0:
/* 08A440 8008F9E0 80010020 */  lwz     r0, 0x20(r1)
/* 08A444 8008F9E4 7C040040 */  cmplw   r4, r0
/* 08A448 8008F9E8 4082001C */  bne     lbl_8008FA04
/* 08A44C 8008F9EC 807E0004 */  lwz     r3, 4(r30)
/* 08A450 8008F9F0 80030020 */  lwz     r0, 0x20(r3)
/* 08A454 8008F9F4 2C000005 */  cmpwi   r0, 5
/* 08A458 8008F9F8 418200B0 */  beq     lbl_8008FAA8
/* 08A45C 8008F9FC 3BA00000 */  li      r29, 0
/* 08A460 8008FA00 480000A8 */  b       lbl_8008FAA8
lbl_8008FA04:
/* 08A464 8008FA04 80010024 */  lwz     r0, 0x24(r1)
/* 08A468 8008FA08 7C040040 */  cmplw   r4, r0
/* 08A46C 8008FA0C 4082005C */  bne     lbl_8008FA68
/* 08A470 8008FA10 809E0004 */  lwz     r4, 4(r30)
/* 08A474 8008FA14 80040020 */  lwz     r0, 0x20(r4)
/* 08A478 8008FA18 2C000004 */  cmpwi   r0, 4
/* 08A47C 8008FA1C 41820008 */  beq     lbl_8008FA24
/* 08A480 8008FA20 3BA00000 */  li      r29, 0
lbl_8008FA24:
/* 08A484 8008FA24 2C1D0000 */  cmpwi   r29, 0
/* 08A488 8008FA28 41820080 */  beq     lbl_8008FAA8
/* 08A48C 8008FA2C 90610018 */  stw     r3, 0x18(r1)
/* 08A490 8008FA30 3AA00000 */  li      r21, 0
/* 08A494 8008FA34 48000010 */  b       lbl_8008FA44
lbl_8008FA38:
/* 08A498 8008FA38 80610018 */  lwz     r3, 0x18(r1)
/* 08A49C 8008FA3C 38030004 */  addi    r0, r3, 4
/* 08A4A0 8008FA40 90010018 */  stw     r0, 0x18(r1)
lbl_8008FA44:
/* 08A4A4 8008FA44 80810018 */  lwz     r4, 0x18(r1)
/* 08A4A8 8008FA48 80640000 */  lwz     r3, 0(r4)
/* 08A4AC 8008FA4C 3C03D843 */  addis   r0, r3, 0xd843
/* 08A4B0 8008FA50 28000040 */  cmplwi  r0, 0x40
/* 08A4B4 8008FA54 4082FFE4 */  bne     lbl_8008FA38
/* 08A4B8 8008FA58 381F0001 */  addi    r0, r31, 1
/* 08A4BC 8008FA5C 64007C00 */  oris    r0, r0, 0x7c00
/* 08A4C0 8008FA60 90040000 */  stw     r0, 0(r4)
/* 08A4C4 8008FA64 48000044 */  b       lbl_8008FAA8
lbl_8008FA68:
/* 08A4C8 8008FA68 80010028 */  lwz     r0, 0x28(r1)
/* 08A4CC 8008FA6C 7C040040 */  cmplw   r4, r0
/* 08A4D0 8008FA70 40820038 */  bne     lbl_8008FAA8
/* 08A4D4 8008FA74 809E0004 */  lwz     r4, 4(r30)
/* 08A4D8 8008FA78 80040020 */  lwz     r0, 0x20(r4)
/* 08A4DC 8008FA7C 2C000004 */  cmpwi   r0, 4
/* 08A4E0 8008FA80 4182000C */  beq     lbl_8008FA8C
/* 08A4E4 8008FA84 3BA00000 */  li      r29, 0
/* 08A4E8 8008FA88 48000020 */  b       lbl_8008FAA8
lbl_8008FA8C:
/* 08A4EC 8008FA8C 2C180000 */  cmpwi   r24, 0
/* 08A4F0 8008FA90 80630008 */  lwz     r3, 8(r3)
/* 08A4F4 8008FA94 41820014 */  beq     lbl_8008FAA8
/* 08A4F8 8008FA98 3C03F400 */  addis   r0, r3, 0xf400
/* 08A4FC 8008FA9C 28000F3C */  cmplwi  r0, 0xf3c
/* 08A500 8008FAA0 41820008 */  beq     lbl_8008FAA8
/* 08A504 8008FAA4 3BA00000 */  li      r29, 0
lbl_8008FAA8:
/* 08A508 8008FAA8 2C1D0000 */  cmpwi   r29, 0
/* 08A50C 8008FAAC 41820058 */  beq     lbl_8008FB04
/* 08A510 8008FAB0 38000000 */  li      r0, 0
/* 08A514 8008FAB4 901A0028 */  stw     r0, 0x28(r26)
/* 08A518 8008FAB8 2C150000 */  cmpwi   r21, 0
/* 08A51C 8008FABC 67E57C00 */  oris    r5, r31, 0x7c00
/* 08A520 8008FAC0 8081001C */  lwz     r4, 0x1c(r1)
/* 08A524 8008FAC4 38640004 */  addi    r3, r4, 4
/* 08A528 8008FAC8 9061001C */  stw     r3, 0x1c(r1)
/* 08A52C 8008FACC 90A40000 */  stw     r5, 0(r4)
/* 08A530 8008FAD0 4182002C */  beq     lbl_8008FAFC
/* 08A534 8008FAD4 8081001C */  lwz     r4, 0x1c(r1)
/* 08A538 8008FAD8 3C6003E0 */  lis     r3, 0x3e0
/* 08A53C 8008FADC 38A30008 */  addi    r5, r3, 8
/* 08A540 8008FAE0 38640004 */  addi    r3, r4, 4
/* 08A544 8008FAE4 9061001C */  stw     r3, 0x1c(r1)
/* 08A548 8008FAE8 90A40000 */  stw     r5, 0(r4)
/* 08A54C 8008FAEC 8081001C */  lwz     r4, 0x1c(r1)
/* 08A550 8008FAF0 38640004 */  addi    r3, r4, 4
/* 08A554 8008FAF4 9061001C */  stw     r3, 0x1c(r1)
/* 08A558 8008FAF8 90040000 */  stw     r0, 0(r4)
lbl_8008FAFC:
/* 08A55C 8008FAFC 38600001 */  li      r3, 1
/* 08A560 8008FB00 48000058 */  b       lbl_8008FB58
lbl_8008FB04:
/* 08A564 8008FB04 2C1B0000 */  cmpwi   r27, 0
/* 08A568 8008FB08 4182000C */  beq     lbl_8008FB14
/* 08A56C 8008FB0C 38600001 */  li      r3, 1
/* 08A570 8008FB10 48000048 */  b       lbl_8008FB58
lbl_8008FB14:
/* 08A574 8008FB14 3AF70008 */  addi    r23, r23, 8
/* 08A578 8008FB18 3B180002 */  addi    r24, r24, 2
lbl_8008FB1C:
/* 08A57C 8008FB1C 1C1F004C */  mulli   r0, r31, 0x4c
/* 08A580 8008FB20 7FB90214 */  add     r29, r25, r0
/* 08A584 8008FB24 3BBD042C */  addi    r29, r29, 0x42c
/* 08A588 8008FB28 7C7DBA14 */  add     r3, r29, r23
/* 08A58C 8008FB2C 80830008 */  lwz     r4, 8(r3)
/* 08A590 8008FB30 28040000 */  cmplwi  r4, 0
/* 08A594 8008FB34 4082FB1C */  bne     lbl_8008F650
/* 08A598 8008FB38 3BFF0001 */  addi    r31, r31, 1
lbl_8008FB3C:
/* 08A59C 8008FB3C 281F0036 */  cmplwi  r31, 0x36
/* 08A5A0 8008FB40 4180FB04 */  blt     lbl_8008F644
/* 08A5A4 8008FB44 38600001 */  li      r3, 1
/* 08A5A8 8008FB48 48000010 */  b       lbl_8008FB58
lbl_8008FB4C:
/* 08A5AC 8008FB4C 54A0103A */  slwi    r0, r5, 2
/* 08A5B0 8008FB50 7C630214 */  add     r3, r3, r0
/* 08A5B4 8008FB54 4BFFFD04 */  b       lbl_8008F858
lbl_8008FB58:
/* 08A5B8 8008FB58 B9C10030 */  lmw     r14, 0x30(r1)
/* 08A5BC 8008FB5C 8001007C */  lwz     r0, 0x7c(r1)
/* 08A5C0 8008FB60 38210078 */  addi    r1, r1, 0x78
/* 08A5C4 8008FB64 7C0803A6 */  mtlr    r0
/* 08A5C8 8008FB68 4E800020 */  blr     
