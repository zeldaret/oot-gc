glabel guScaleF
/* 08EEE0 80094480 7C0802A6 */  mflr    r0
/* 08EEE4 80094484 90010004 */  stw     r0, 4(r1)
/* 08EEE8 80094488 9421FFD0 */  stwu    r1, -0x30(r1)
/* 08EEEC 8009448C 93E1002C */  stw     r31, 0x2c(r1)
/* 08EEF0 80094490 7C7F1B78 */  mr      r31, r3
/* 08EEF4 80094494 38810020 */  addi    r4, r1, 0x20
/* 08EEF8 80094498 C0028388 */  lfs     f0, D_80136088@sda21(r2)
/* 08EEFC 8009449C D001001C */  stfs    f0, 0x1c(r1)
/* 08EF00 800944A0 C00283A4 */  lfs     f0, D_801360A4@sda21(r2)
/* 08EF04 800944A4 D0010014 */  stfs    f0, 0x14(r1)
/* 08EF08 800944A8 80BF0064 */  lwz     r5, 0x64(r31)
/* 08EF0C 800944AC 4BFA02D5 */  bl      cpuGetAddressBuffer
/* 08EF10 800944B0 38000004 */  li      r0, 4
/* 08EF14 800944B4 80E10014 */  lwz     r7, 0x14(r1)
/* 08EF18 800944B8 7C0903A6 */  mtctr   r0
/* 08EF1C 800944BC 8001001C */  lwz     r0, 0x1c(r1)
/* 08EF20 800944C0 39000000 */  li      r8, 0
/* 08EF24 800944C4 38C00000 */  li      r6, 0
lbl_800944C8:
/* 08EF28 800944C8 38800000 */  li      r4, 0
/* 08EF2C 800944CC 7C082000 */  cmpw    r8, r4
/* 08EF30 800944D0 54C3103A */  slwi    r3, r6, 2
/* 08EF34 800944D4 40820010 */  bne     lbl_800944E4
/* 08EF38 800944D8 80810020 */  lwz     r4, 0x20(r1)
/* 08EF3C 800944DC 7CE4192E */  stwx    r7, r4, r3
/* 08EF40 800944E0 4800000C */  b       lbl_800944EC
lbl_800944E4:
/* 08EF44 800944E4 80810020 */  lwz     r4, 0x20(r1)
/* 08EF48 800944E8 7C04192E */  stwx    r0, r4, r3
lbl_800944EC:
/* 08EF4C 800944EC 38800001 */  li      r4, 1
/* 08EF50 800944F0 7C082000 */  cmpw    r8, r4
/* 08EF54 800944F4 38630004 */  addi    r3, r3, 4
/* 08EF58 800944F8 40820010 */  bne     lbl_80094508
/* 08EF5C 800944FC 80810020 */  lwz     r4, 0x20(r1)
/* 08EF60 80094500 7CE4192E */  stwx    r7, r4, r3
/* 08EF64 80094504 4800000C */  b       lbl_80094510
lbl_80094508:
/* 08EF68 80094508 80810020 */  lwz     r4, 0x20(r1)
/* 08EF6C 8009450C 7C04192E */  stwx    r0, r4, r3
lbl_80094510:
/* 08EF70 80094510 38800002 */  li      r4, 2
/* 08EF74 80094514 7C082000 */  cmpw    r8, r4
/* 08EF78 80094518 38A60001 */  addi    r5, r6, 1
/* 08EF7C 8009451C 38630004 */  addi    r3, r3, 4
/* 08EF80 80094520 40820010 */  bne     lbl_80094530
/* 08EF84 80094524 80810020 */  lwz     r4, 0x20(r1)
/* 08EF88 80094528 7CE4192E */  stwx    r7, r4, r3
/* 08EF8C 8009452C 4800000C */  b       lbl_80094538
lbl_80094530:
/* 08EF90 80094530 80810020 */  lwz     r4, 0x20(r1)
/* 08EF94 80094534 7C04192E */  stwx    r0, r4, r3
lbl_80094538:
/* 08EF98 80094538 38800003 */  li      r4, 3
/* 08EF9C 8009453C 7C082000 */  cmpw    r8, r4
/* 08EFA0 80094540 38630004 */  addi    r3, r3, 4
/* 08EFA4 80094544 40820010 */  bne     lbl_80094554
/* 08EFA8 80094548 80810020 */  lwz     r4, 0x20(r1)
/* 08EFAC 8009454C 7CE4192E */  stwx    r7, r4, r3
/* 08EFB0 80094550 4800000C */  b       lbl_8009455C
lbl_80094554:
/* 08EFB4 80094554 80810020 */  lwz     r4, 0x20(r1)
/* 08EFB8 80094558 7C04192E */  stwx    r0, r4, r3
lbl_8009455C:
/* 08EFBC 8009455C 38C60004 */  addi    r6, r6, 4
/* 08EFC0 80094560 39080001 */  addi    r8, r8, 1
/* 08EFC4 80094564 4200FF64 */  bdnz    lbl_800944C8
/* 08EFC8 80094568 801F006C */  lwz     r0, 0x6c(r31)
/* 08EFCC 8009456C 80610020 */  lwz     r3, 0x20(r1)
/* 08EFD0 80094570 90030000 */  stw     r0, 0(r3)
/* 08EFD4 80094574 801F0074 */  lwz     r0, 0x74(r31)
/* 08EFD8 80094578 80610020 */  lwz     r3, 0x20(r1)
/* 08EFDC 8009457C 90030014 */  stw     r0, 0x14(r3)
/* 08EFE0 80094580 801F007C */  lwz     r0, 0x7c(r31)
/* 08EFE4 80094584 80610020 */  lwz     r3, 0x20(r1)
/* 08EFE8 80094588 90030028 */  stw     r0, 0x28(r3)
/* 08EFEC 8009458C 80610020 */  lwz     r3, 0x20(r1)
/* 08EFF0 80094590 90E3003C */  stw     r7, 0x3c(r3)
/* 08EFF4 80094594 80010034 */  lwz     r0, 0x34(r1)
/* 08EFF8 80094598 83E1002C */  lwz     r31, 0x2c(r1)
/* 08EFFC 8009459C 38210030 */  addi    r1, r1, 0x30
/* 08F000 800945A0 7C0803A6 */  mtlr    r0
/* 08F004 800945A4 4E800020 */  blr     
