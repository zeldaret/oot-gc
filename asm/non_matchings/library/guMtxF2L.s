glabel guMtxF2L
/* 08FCAC 8009524C 7C0802A6 */  mflr    r0
/* 08FCB0 80095250 90010004 */  stw     r0, 4(r1)
/* 08FCB4 80095254 9421FFC0 */  stwu    r1, -0x40(r1)
/* 08FCB8 80095258 93E1003C */  stw     r31, 0x3c(r1)
/* 08FCBC 8009525C 7C7F1B78 */  mr      r31, r3
/* 08FCC0 80095260 38810024 */  addi    r4, r1, 0x24
/* 08FCC4 80095264 80A30064 */  lwz     r5, 0x64(r3)
/* 08FCC8 80095268 4BF9F519 */  bl      cpuGetAddressBuffer
/* 08FCCC 8009526C 80BF006C */  lwz     r5, 0x6c(r31)
/* 08FCD0 80095270 387F0000 */  addi    r3, r31, 0
/* 08FCD4 80095274 38810020 */  addi    r4, r1, 0x20
/* 08FCD8 80095278 4BF9F509 */  bl      cpuGetAddressBuffer
/* 08FCDC 8009527C 807F0008 */  lwz     r3, 8(r31)
/* 08FCE0 80095280 809F0064 */  lwz     r4, 0x64(r31)
/* 08FCE4 80095284 80630000 */  lwz     r3, 0(r3)
/* 08FCE8 80095288 80BF006C */  lwz     r5, 0x6c(r31)
/* 08FCEC 8009528C 4BF884B5 */  bl      frameFixMatrixHint
/* 08FCF0 80095290 80610020 */  lwz     r3, 0x20(r1)
/* 08FCF4 80095294 38000002 */  li      r0, 2
/* 08FCF8 80095298 7C0903A6 */  mtctr   r0
/* 08FCFC 8009529C C04283B0 */  lfs     f2, D_801360B0@sda21(r2)
/* 08FD00 800952A0 39230000 */  addi    r9, r3, 0
/* 08FD04 800952A4 39430020 */  addi    r10, r3, 0x20
/* 08FD08 800952A8 39000000 */  li      r8, 0
/* 08FD0C 800952AC 38A00000 */  li      r5, 0
lbl_800952B0:
/* 08FD10 800952B0 80010024 */  lwz     r0, 0x24(r1)
/* 08FD14 800952B4 54A3103A */  slwi    r3, r5, 2
/* 08FD18 800952B8 38A50004 */  addi    r5, r5, 4
/* 08FD1C 800952BC 7C801A14 */  add     r4, r0, r3
/* 08FD20 800952C0 C0040000 */  lfs     f0, 0(r4)
/* 08FD24 800952C4 38630008 */  addi    r3, r3, 8
/* 08FD28 800952C8 D001001C */  stfs    f0, 0x1c(r1)
/* 08FD2C 800952CC C021001C */  lfs     f1, 0x1c(r1)
/* 08FD30 800952D0 C0040004 */  lfs     f0, 4(r4)
/* 08FD34 800952D4 EC220072 */  fmuls   f1, f2, f1
/* 08FD38 800952D8 D001001C */  stfs    f0, 0x1c(r1)
/* 08FD3C 800952DC C001001C */  lfs     f0, 0x1c(r1)
/* 08FD40 800952E0 FC20081E */  fctiwz  f1, f1
/* 08FD44 800952E4 EC020032 */  fmuls   f0, f2, f0
/* 08FD48 800952E8 D8210030 */  stfd    f1, 0x30(r1)
/* 08FD4C 800952EC FC00001E */  fctiwz  f0, f0
/* 08FD50 800952F0 80C10034 */  lwz     r6, 0x34(r1)
/* 08FD54 800952F4 54C0801E */  slwi    r0, r6, 0x10
/* 08FD58 800952F8 D8010028 */  stfd    f0, 0x28(r1)
/* 08FD5C 800952FC 80E1002C */  lwz     r7, 0x2c(r1)
/* 08FD60 80095300 54E4843E */  srwi    r4, r7, 0x10
/* 08FD64 80095304 50C4001E */  rlwimi  r4, r6, 0, 0, 0xf
/* 08FD68 80095308 90890000 */  stw     r4, 0(r9)
/* 08FD6C 8009530C 50E0043E */  rlwimi  r0, r7, 0, 0x10, 0x1f
/* 08FD70 80095310 900A0000 */  stw     r0, 0(r10)
/* 08FD74 80095314 80010024 */  lwz     r0, 0x24(r1)
/* 08FD78 80095318 7C801A14 */  add     r4, r0, r3
/* 08FD7C 8009531C C0040000 */  lfs     f0, 0(r4)
/* 08FD80 80095320 D001001C */  stfs    f0, 0x1c(r1)
/* 08FD84 80095324 C021001C */  lfs     f1, 0x1c(r1)
/* 08FD88 80095328 C0040004 */  lfs     f0, 4(r4)
/* 08FD8C 8009532C EC220072 */  fmuls   f1, f2, f1
/* 08FD90 80095330 D001001C */  stfs    f0, 0x1c(r1)
/* 08FD94 80095334 C001001C */  lfs     f0, 0x1c(r1)
/* 08FD98 80095338 FC20081E */  fctiwz  f1, f1
/* 08FD9C 8009533C EC020032 */  fmuls   f0, f2, f0
/* 08FDA0 80095340 D8210030 */  stfd    f1, 0x30(r1)
/* 08FDA4 80095344 FC00001E */  fctiwz  f0, f0
/* 08FDA8 80095348 80C10034 */  lwz     r6, 0x34(r1)
/* 08FDAC 8009534C 54C0801E */  slwi    r0, r6, 0x10
/* 08FDB0 80095350 D8010028 */  stfd    f0, 0x28(r1)
/* 08FDB4 80095354 80E1002C */  lwz     r7, 0x2c(r1)
/* 08FDB8 80095358 54E4843E */  srwi    r4, r7, 0x10
/* 08FDBC 8009535C 50C4001E */  rlwimi  r4, r6, 0, 0, 0xf
/* 08FDC0 80095360 90890004 */  stw     r4, 4(r9)
/* 08FDC4 80095364 50E0043E */  rlwimi  r0, r7, 0, 0x10, 0x1f
/* 08FDC8 80095368 39290008 */  addi    r9, r9, 8
/* 08FDCC 8009536C 900A0004 */  stw     r0, 4(r10)
/* 08FDD0 80095370 394A0008 */  addi    r10, r10, 8
/* 08FDD4 80095374 54A3103A */  slwi    r3, r5, 2
/* 08FDD8 80095378 80010024 */  lwz     r0, 0x24(r1)
/* 08FDDC 8009537C 39080001 */  addi    r8, r8, 1
/* 08FDE0 80095380 38A50004 */  addi    r5, r5, 4
/* 08FDE4 80095384 7C801A14 */  add     r4, r0, r3
/* 08FDE8 80095388 C0040000 */  lfs     f0, 0(r4)
/* 08FDEC 8009538C 38630008 */  addi    r3, r3, 8
/* 08FDF0 80095390 D001001C */  stfs    f0, 0x1c(r1)
/* 08FDF4 80095394 C021001C */  lfs     f1, 0x1c(r1)
/* 08FDF8 80095398 C0040004 */  lfs     f0, 4(r4)
/* 08FDFC 8009539C EC220072 */  fmuls   f1, f2, f1
/* 08FE00 800953A0 D001001C */  stfs    f0, 0x1c(r1)
/* 08FE04 800953A4 C001001C */  lfs     f0, 0x1c(r1)
/* 08FE08 800953A8 FC20081E */  fctiwz  f1, f1
/* 08FE0C 800953AC EC020032 */  fmuls   f0, f2, f0
/* 08FE10 800953B0 D8210030 */  stfd    f1, 0x30(r1)
/* 08FE14 800953B4 FC00001E */  fctiwz  f0, f0
/* 08FE18 800953B8 80C10034 */  lwz     r6, 0x34(r1)
/* 08FE1C 800953BC 54C0801E */  slwi    r0, r6, 0x10
/* 08FE20 800953C0 D8010028 */  stfd    f0, 0x28(r1)
/* 08FE24 800953C4 80E1002C */  lwz     r7, 0x2c(r1)
/* 08FE28 800953C8 54E4843E */  srwi    r4, r7, 0x10
/* 08FE2C 800953CC 50C4001E */  rlwimi  r4, r6, 0, 0, 0xf
/* 08FE30 800953D0 90890000 */  stw     r4, 0(r9)
/* 08FE34 800953D4 50E0043E */  rlwimi  r0, r7, 0, 0x10, 0x1f
/* 08FE38 800953D8 900A0000 */  stw     r0, 0(r10)
/* 08FE3C 800953DC 80010024 */  lwz     r0, 0x24(r1)
/* 08FE40 800953E0 7C801A14 */  add     r4, r0, r3
/* 08FE44 800953E4 C0040000 */  lfs     f0, 0(r4)
/* 08FE48 800953E8 D001001C */  stfs    f0, 0x1c(r1)
/* 08FE4C 800953EC C021001C */  lfs     f1, 0x1c(r1)
/* 08FE50 800953F0 C0040004 */  lfs     f0, 4(r4)
/* 08FE54 800953F4 EC220072 */  fmuls   f1, f2, f1
/* 08FE58 800953F8 D001001C */  stfs    f0, 0x1c(r1)
/* 08FE5C 800953FC C001001C */  lfs     f0, 0x1c(r1)
/* 08FE60 80095400 FC20081E */  fctiwz  f1, f1
/* 08FE64 80095404 EC020032 */  fmuls   f0, f2, f0
/* 08FE68 80095408 D8210030 */  stfd    f1, 0x30(r1)
/* 08FE6C 8009540C FC00001E */  fctiwz  f0, f0
/* 08FE70 80095410 80C10034 */  lwz     r6, 0x34(r1)
/* 08FE74 80095414 54C0801E */  slwi    r0, r6, 0x10
/* 08FE78 80095418 D8010028 */  stfd    f0, 0x28(r1)
/* 08FE7C 8009541C 80E1002C */  lwz     r7, 0x2c(r1)
/* 08FE80 80095420 54E4843E */  srwi    r4, r7, 0x10
/* 08FE84 80095424 50C4001E */  rlwimi  r4, r6, 0, 0, 0xf
/* 08FE88 80095428 90890004 */  stw     r4, 4(r9)
/* 08FE8C 8009542C 50E0043E */  rlwimi  r0, r7, 0, 0x10, 0x1f
/* 08FE90 80095430 39290008 */  addi    r9, r9, 8
/* 08FE94 80095434 900A0004 */  stw     r0, 4(r10)
/* 08FE98 80095438 394A0008 */  addi    r10, r10, 8
/* 08FE9C 8009543C 4200FE74 */  bdnz    lbl_800952B0
/* 08FEA0 80095440 80010044 */  lwz     r0, 0x44(r1)
/* 08FEA4 80095444 83E1003C */  lwz     r31, 0x3c(r1)
/* 08FEA8 80095448 38210040 */  addi    r1, r1, 0x40
/* 08FEAC 8009544C 7C0803A6 */  mtlr    r0
/* 08FEB0 80095450 4E800020 */  blr     
