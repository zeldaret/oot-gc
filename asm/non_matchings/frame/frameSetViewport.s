glabel frameSetViewport
/* 018340 8001D8E0 9421FFB0 */  stwu    r1, -0x50(r1)
/* 018344 8001D8E4 A8040000 */  lha     r0, 0(r4)
/* 018348 8001D8E8 3CA04330 */  lis     r5, 0x4330
/* 01834C 8001D8EC C8428110 */  lfd     f2, D_80135E10@sda21(r2)
/* 018350 8001D8F0 38C10028 */  addi    r6, r1, 0x28
/* 018354 8001D8F4 6C008000 */  xoris   r0, r0, 0x8000
/* 018358 8001D8F8 9001004C */  stw     r0, 0x4c(r1)
/* 01835C 8001D8FC C0228104 */  lfs     f1, D_80135E04@sda21(r2)
/* 018360 8001D900 90A10048 */  stw     r5, 0x48(r1)
/* 018364 8001D904 C8010048 */  lfd     f0, 0x48(r1)
/* 018368 8001D908 EC001028 */  fsubs   f0, f0, f2
/* 01836C 8001D90C EC000072 */  fmuls   f0, f0, f1
/* 018370 8001D910 D0010028 */  stfs    f0, 0x28(r1)
/* 018374 8001D914 A8040002 */  lha     r0, 2(r4)
/* 018378 8001D918 6C008000 */  xoris   r0, r0, 0x8000
/* 01837C 8001D91C 90010044 */  stw     r0, 0x44(r1)
/* 018380 8001D920 90A10040 */  stw     r5, 0x40(r1)
/* 018384 8001D924 C8010040 */  lfd     f0, 0x40(r1)
/* 018388 8001D928 EC001028 */  fsubs   f0, f0, f2
/* 01838C 8001D92C EC000072 */  fmuls   f0, f0, f1
/* 018390 8001D930 D001002C */  stfs    f0, 0x2c(r1)
/* 018394 8001D934 A8040004 */  lha     r0, 4(r4)
/* 018398 8001D938 6C008000 */  xoris   r0, r0, 0x8000
/* 01839C 8001D93C 9001003C */  stw     r0, 0x3c(r1)
/* 0183A0 8001D940 90A10038 */  stw     r5, 0x38(r1)
/* 0183A4 8001D944 C8010038 */  lfd     f0, 0x38(r1)
/* 0183A8 8001D948 EC001028 */  fsubs   f0, f0, f2
/* 0183AC 8001D94C EC000072 */  fmuls   f0, f0, f1
/* 0183B0 8001D950 D0010030 */  stfs    f0, 0x30(r1)
/* 0183B4 8001D954 48000004 */  b       lbl_8001D958
lbl_8001D958:
/* 0183B8 8001D958 C0228100 */  lfs     f1, D_80135E00@sda21(r2)
/* 0183BC 8001D95C 48000004 */  b       lbl_8001D960
lbl_8001D960:
/* 0183C0 8001D960 C0010028 */  lfs     f0, 0x28(r1)
/* 0183C4 8001D964 FC000840 */  fcmpo   cr0, f0, f1
/* 0183C8 8001D968 4080000C */  bge     lbl_8001D974
/* 0183CC 8001D96C FC000050 */  fneg    f0, f0
/* 0183D0 8001D970 D0010028 */  stfs    f0, 0x28(r1)
lbl_8001D974:
/* 0183D4 8001D974 38C60004 */  addi    r6, r6, 4
/* 0183D8 8001D978 C0060000 */  lfs     f0, 0(r6)
/* 0183DC 8001D97C FC000840 */  fcmpo   cr0, f0, f1
/* 0183E0 8001D980 4080000C */  bge     lbl_8001D98C
/* 0183E4 8001D984 FC000050 */  fneg    f0, f0
/* 0183E8 8001D988 D0060000 */  stfs    f0, 0(r6)
lbl_8001D98C:
/* 0183EC 8001D98C 38C60004 */  addi    r6, r6, 4
/* 0183F0 8001D990 C0060000 */  lfs     f0, 0(r6)
/* 0183F4 8001D994 FC000840 */  fcmpo   cr0, f0, f1
/* 0183F8 8001D998 4080000C */  bge     lbl_8001D9A4
/* 0183FC 8001D99C FC000050 */  fneg    f0, f0
/* 018400 8001D9A0 D0060000 */  stfs    f0, 0(r6)
lbl_8001D9A4:
/* 018404 8001D9A4 A8040008 */  lha     r0, 8(r4)
/* 018408 8001D9A8 3CE08002 */  lis     r7, frameDrawLine_Setup@ha
/* 01840C 8001D9AC A884000A */  lha     r4, 0xa(r4)
/* 018410 8001D9B0 3CC08002 */  lis     r6, frameDrawTriangle_Setup@ha
/* 018414 8001D9B4 6C008000 */  xoris   r0, r0, 0x8000
/* 018418 8001D9B8 90010044 */  stw     r0, 0x44(r1)
/* 01841C 8001D9BC 6C848000 */  xoris   r4, r4, 0x8000
/* 018420 8001D9C0 3C004330 */  lis     r0, 0x4330
/* 018424 8001D9C4 C8628110 */  lfd     f3, D_80135E10@sda21(r2)
/* 018428 8001D9C8 9081003C */  stw     r4, 0x3c(r1)
/* 01842C 8001D9CC 3CA08002 */  lis     r5, frameDrawRectFill_Setup@ha
/* 018430 8001D9D0 C0228104 */  lfs     f1, D_80135E04@sda21(r2)
/* 018434 8001D9D4 90010040 */  stw     r0, 0x40(r1)
/* 018438 8001D9D8 3C808002 */  lis     r4, frameDrawRectTexture_Setup@ha
/* 01843C 8001D9DC C0E10028 */  lfs     f7, 0x28(r1)
/* 018440 8001D9E0 38E76D30 */  addi    r7, r7, frameDrawLine_Setup@l
/* 018444 8001D9E4 90010038 */  stw     r0, 0x38(r1)
/* 018448 8001D9E8 C8010040 */  lfd     f0, 0x40(r1)
/* 01844C 8001D9EC 38C67900 */  addi    r6, r6, frameDrawTriangle_Setup@l
/* 018450 8001D9F0 C8410038 */  lfd     f2, 0x38(r1)
/* 018454 8001D9F4 38A569EC */  addi    r5, r5, frameDrawRectFill_Setup@l
/* 018458 8001D9F8 EC001828 */  fsubs   f0, f0, f3
/* 01845C 8001D9FC EC421828 */  fsubs   f2, f2, f3
/* 018460 8001DA00 C0828108 */  lfs     f4, D_80135E08@sda21(r2)
/* 018464 8001DA04 C0A1002C */  lfs     f5, 0x2c(r1)
/* 018468 8001DA08 38046124 */  addi    r0, r4, frameDrawRectTexture_Setup@l
/* 01846C 8001DA0C EC000072 */  fmuls   f0, f0, f1
/* 018470 8001DA10 EC220072 */  fmuls   f1, f2, f1
/* 018474 8001DA14 C1030080 */  lfs     f8, 0x80(r3)
/* 018478 8001DA18 C0C30084 */  lfs     f6, 0x84(r3)
/* 01847C 8001DA1C EC6401F2 */  fmuls   f3, f4, f7
/* 018480 8001DA20 EC003828 */  fsubs   f0, f0, f7
/* 018484 8001DA24 EC212828 */  fsubs   f1, f1, f5
/* 018488 8001DA28 EC440172 */  fmuls   f2, f4, f5
/* 01848C 8001DA2C EC080032 */  fmuls   f0, f8, f0
/* 018490 8001DA30 EC260072 */  fmuls   f1, f6, f1
/* 018494 8001DA34 EC630232 */  fmuls   f3, f3, f8
/* 018498 8001DA38 D00300B8 */  stfs    f0, 0xb8(r3)
/* 01849C 8001DA3C EC0201B2 */  fmuls   f0, f2, f6
/* 0184A0 8001DA40 D02300BC */  stfs    f1, 0xbc(r3)
/* 0184A4 8001DA44 D06300C0 */  stfs    f3, 0xc0(r3)
/* 0184A8 8001DA48 D00300C4 */  stfs    f0, 0xc4(r3)
/* 0184AC 8001DA4C 8083007C */  lwz     r4, 0x7c(r3)
/* 0184B0 8001DA50 64840001 */  oris    r4, r4, 1
/* 0184B4 8001DA54 9083007C */  stw     r4, 0x7c(r3)
/* 0184B8 8001DA58 90E3012C */  stw     r7, 0x12c(r3)
/* 0184BC 8001DA5C 90C30130 */  stw     r6, 0x130(r3)
/* 0184C0 8001DA60 90A30134 */  stw     r5, 0x134(r3)
/* 0184C4 8001DA64 90030138 */  stw     r0, 0x138(r3)
/* 0184C8 8001DA68 38600001 */  li      r3, 1
/* 0184CC 8001DA6C 38210050 */  addi    r1, r1, 0x50
/* 0184D0 8001DA70 4E800020 */  blr     
