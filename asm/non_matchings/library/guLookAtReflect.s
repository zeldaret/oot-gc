glabel guLookAtReflect
/* 08BD98 80091338 7C0802A6 */  mflr    r0
/* 08BD9C 8009133C 90010004 */  stw     r0, 4(r1)
/* 08BDA0 80091340 9421FF58 */  stwu    r1, -0xa8(r1)
/* 08BDA4 80091344 DBE100A0 */  stfd    f31, 0xa0(r1)
/* 08BDA8 80091348 38810024 */  addi    r4, r1, 0x24
/* 08BDAC 8009134C DBC10098 */  stfd    f30, 0x98(r1)
/* 08BDB0 80091350 DBA10090 */  stfd    f29, 0x90(r1)
/* 08BDB4 80091354 93E1008C */  stw     r31, 0x8c(r1)
/* 08BDB8 80091358 7C7F1B78 */  mr      r31, r3
/* 08BDBC 8009135C 80A30064 */  lwz     r5, 0x64(r3)
/* 08BDC0 80091360 4BFA3421 */  bl      cpuGetAddressBuffer
/* 08BDC4 80091364 80BF006C */  lwz     r5, 0x6c(r31)
/* 08BDC8 80091368 387F0000 */  addi    r3, r31, 0
/* 08BDCC 8009136C 38810070 */  addi    r4, r1, 0x70
/* 08BDD0 80091370 4BFA3411 */  bl      cpuGetAddressBuffer
/* 08BDD4 80091374 80BF012C */  lwz     r5, 0x12c(r31)
/* 08BDD8 80091378 387F0000 */  addi    r3, r31, 0
/* 08BDDC 8009137C 38810020 */  addi    r4, r1, 0x20
/* 08BDE0 80091380 4BFA3401 */  bl      cpuGetAddressBuffer
/* 08BDE4 80091384 801F0074 */  lwz     r0, 0x74(r31)
/* 08BDE8 80091388 9001006C */  stw     r0, 0x6c(r1)
/* 08BDEC 8009138C C061006C */  lfs     f3, 0x6c(r1)
/* 08BDF0 80091390 801F007C */  lwz     r0, 0x7c(r31)
/* 08BDF4 80091394 9001006C */  stw     r0, 0x6c(r1)
/* 08BDF8 80091398 80610020 */  lwz     r3, 0x20(r1)
/* 08BDFC 8009139C C081006C */  lfs     f4, 0x6c(r1)
/* 08BE00 800913A0 80030010 */  lwz     r0, 0x10(r3)
/* 08BE04 800913A4 9001006C */  stw     r0, 0x6c(r1)
/* 08BE08 800913A8 C0A1006C */  lfs     f5, 0x6c(r1)
/* 08BE0C 800913AC 80030014 */  lwz     r0, 0x14(r3)
/* 08BE10 800913B0 9001006C */  stw     r0, 0x6c(r1)
/* 08BE14 800913B4 C001006C */  lfs     f0, 0x6c(r1)
/* 08BE18 800913B8 80030018 */  lwz     r0, 0x18(r3)
/* 08BE1C 800913BC ECC01828 */  fsubs   f6, f0, f3
/* 08BE20 800913C0 9001006C */  stw     r0, 0x6c(r1)
/* 08BE24 800913C4 C001006C */  lfs     f0, 0x6c(r1)
/* 08BE28 800913C8 8003001C */  lwz     r0, 0x1c(r3)
/* 08BE2C 800913CC ECE02028 */  fsubs   f7, f0, f4
/* 08BE30 800913D0 9001006C */  stw     r0, 0x6c(r1)
/* 08BE34 800913D4 C021006C */  lfs     f1, 0x6c(r1)
/* 08BE38 800913D8 EC0701F2 */  fmuls   f0, f7, f7
/* 08BE3C 800913DC 80030020 */  lwz     r0, 0x20(r3)
/* 08BE40 800913E0 ED012828 */  fsubs   f8, f1, f5
/* 08BE44 800913E4 9001006C */  stw     r0, 0x6c(r1)
/* 08BE48 800913E8 EC2601BA */  fmadds  f1, f6, f6, f0
/* 08BE4C 800913EC C001006C */  lfs     f0, 0x6c(r1)
/* 08BE50 800913F0 80030024 */  lwz     r0, 0x24(r3)
/* 08BE54 800913F4 EDA80A3A */  fmadds  f13, f8, f8, f1
/* 08BE58 800913F8 9001006C */  stw     r0, 0x6c(r1)
/* 08BE5C 800913FC C021006C */  lfs     f1, 0x6c(r1)
/* 08BE60 80091400 80030028 */  lwz     r0, 0x28(r3)
/* 08BE64 80091404 9001006C */  stw     r0, 0x6c(r1)
/* 08BE68 80091408 C1228388 */  lfs     f9, D_80136088@sda21(r2)
/* 08BE6C 8009140C C041006C */  lfs     f2, 0x6c(r1)
/* 08BE70 80091410 FC0D4840 */  fcmpo   cr0, f13, f9
/* 08BE74 80091414 40810050 */  ble     lbl_80091464
/* 08BE78 80091418 FD406834 */  frsqrte f10, f13
/* 08BE7C 8009141C C9828390 */  lfd     f12, D_80136090@sda21(r2)
/* 08BE80 80091420 C9628398 */  lfd     f11, D_80136098@sda21(r2)
/* 08BE84 80091424 FD2A02B2 */  fmul    f9, f10, f10
/* 08BE88 80091428 FD4C02B2 */  fmul    f10, f12, f10
/* 08BE8C 8009142C FD2D5A7C */  fnmsub  f9, f13, f9, f11
/* 08BE90 80091430 FD4A0272 */  fmul    f10, f10, f9
/* 08BE94 80091434 FD2A02B2 */  fmul    f9, f10, f10
/* 08BE98 80091438 FD4C02B2 */  fmul    f10, f12, f10
/* 08BE9C 8009143C FD2D5A7C */  fnmsub  f9, f13, f9, f11
/* 08BEA0 80091440 FD4A0272 */  fmul    f10, f10, f9
/* 08BEA4 80091444 FD2A02B2 */  fmul    f9, f10, f10
/* 08BEA8 80091448 FD4C02B2 */  fmul    f10, f12, f10
/* 08BEAC 8009144C FD2D5A7C */  fnmsub  f9, f13, f9, f11
/* 08BEB0 80091450 FD2A0272 */  fmul    f9, f10, f9
/* 08BEB4 80091454 FD2D0272 */  fmul    f9, f13, f9
/* 08BEB8 80091458 FD204818 */  frsp    f9, f9
/* 08BEBC 8009145C D1210014 */  stfs    f9, 0x14(r1)
/* 08BEC0 80091460 C1A10014 */  lfs     f13, 0x14(r1)
lbl_80091464:
/* 08BEC4 80091464 C12283A0 */  lfs     f9, D_801360A0@sda21(r2)
/* 08BEC8 80091468 C1828388 */  lfs     f12, D_80136088@sda21(r2)
/* 08BECC 8009146C ED296824 */  fdivs   f9, f9, f13
/* 08BED0 80091470 ED080272 */  fmuls   f8, f8, f9
/* 08BED4 80091474 ECC60272 */  fmuls   f6, f6, f9
/* 08BED8 80091478 ECE70272 */  fmuls   f7, f7, f9
/* 08BEDC 8009147C ED400232 */  fmuls   f10, f0, f8
/* 08BEE0 80091480 ED2101B2 */  fmuls   f9, f1, f6
/* 08BEE4 80091484 EDA201F2 */  fmuls   f13, f2, f7
/* 08BEE8 80091488 ED4251B8 */  fmsubs  f10, f2, f6, f10
/* 08BEEC 8009148C ED6049F8 */  fmsubs  f11, f0, f7, f9
/* 08BEF0 80091490 ED216A38 */  fmsubs  f9, f1, f8, f13
/* 08BEF4 80091494 EC0A02B2 */  fmuls   f0, f10, f10
/* 08BEF8 80091498 EC09027A */  fmadds  f0, f9, f9, f0
/* 08BEFC 8009149C EDAB02FA */  fmadds  f13, f11, f11, f0
/* 08BF00 800914A0 FC0D6040 */  fcmpo   cr0, f13, f12
/* 08BF04 800914A4 40810050 */  ble     lbl_800914F4
/* 08BF08 800914A8 FC206834 */  frsqrte f1, f13
/* 08BF0C 800914AC C9828390 */  lfd     f12, D_80136090@sda21(r2)
/* 08BF10 800914B0 C8428398 */  lfd     f2, D_80136098@sda21(r2)
/* 08BF14 800914B4 FC010072 */  fmul    f0, f1, f1
/* 08BF18 800914B8 FC2C0072 */  fmul    f1, f12, f1
/* 08BF1C 800914BC FC0D103C */  fnmsub  f0, f13, f0, f2
/* 08BF20 800914C0 FC210032 */  fmul    f1, f1, f0
/* 08BF24 800914C4 FC010072 */  fmul    f0, f1, f1
/* 08BF28 800914C8 FC2C0072 */  fmul    f1, f12, f1
/* 08BF2C 800914CC FC0D103C */  fnmsub  f0, f13, f0, f2
/* 08BF30 800914D0 FC210032 */  fmul    f1, f1, f0
/* 08BF34 800914D4 FC010072 */  fmul    f0, f1, f1
/* 08BF38 800914D8 FC2C0072 */  fmul    f1, f12, f1
/* 08BF3C 800914DC FC0D103C */  fnmsub  f0, f13, f0, f2
/* 08BF40 800914E0 FC010032 */  fmul    f0, f1, f0
/* 08BF44 800914E4 FC0D0032 */  fmul    f0, f13, f0
/* 08BF48 800914E8 FC000018 */  frsp    f0, f0
/* 08BF4C 800914EC D0010010 */  stfs    f0, 0x10(r1)
/* 08BF50 800914F0 C1A10010 */  lfs     f13, 0x10(r1)
lbl_800914F4:
/* 08BF54 800914F4 C00283A4 */  lfs     f0, D_801360A4@sda21(r2)
/* 08BF58 800914F8 C1828388 */  lfs     f12, D_80136088@sda21(r2)
/* 08BF5C 800914FC EC006824 */  fdivs   f0, f0, f13
/* 08BF60 80091500 ED6B0032 */  fmuls   f11, f11, f0
/* 08BF64 80091504 ED290032 */  fmuls   f9, f9, f0
/* 08BF68 80091508 ED4A0032 */  fmuls   f10, f10, f0
/* 08BF6C 8009150C EC2602F2 */  fmuls   f1, f6, f11
/* 08BF70 80091510 EC070272 */  fmuls   f0, f7, f9
/* 08BF74 80091514 EDA802B2 */  fmuls   f13, f8, f10
/* 08BF78 80091518 EC280A78 */  fmsubs  f1, f8, f9, f1
/* 08BF7C 8009151C EC4602B8 */  fmsubs  f2, f6, f10, f0
/* 08BF80 80091520 EC076AF8 */  fmsubs  f0, f7, f11, f13
/* 08BF84 80091524 EDA10072 */  fmuls   f13, f1, f1
/* 08BF88 80091528 EDA0683A */  fmadds  f13, f0, f0, f13
/* 08BF8C 8009152C EFA268BA */  fmadds  f29, f2, f2, f13
/* 08BF90 80091530 FC1D6040 */  fcmpo   cr0, f29, f12
/* 08BF94 80091534 40810050 */  ble     lbl_80091584
/* 08BF98 80091538 FDA0E834 */  frsqrte f13, f29
/* 08BF9C 8009153C CBC28390 */  lfd     f30, D_80136090@sda21(r2)
/* 08BFA0 80091540 CBE28398 */  lfd     f31, D_80136098@sda21(r2)
/* 08BFA4 80091544 FD8D0372 */  fmul    f12, f13, f13
/* 08BFA8 80091548 FDBE0372 */  fmul    f13, f30, f13
/* 08BFAC 8009154C FD9DFB3C */  fnmsub  f12, f29, f12, f31
/* 08BFB0 80091550 FDAD0332 */  fmul    f13, f13, f12
/* 08BFB4 80091554 FD8D0372 */  fmul    f12, f13, f13
/* 08BFB8 80091558 FDBE0372 */  fmul    f13, f30, f13
/* 08BFBC 8009155C FD9DFB3C */  fnmsub  f12, f29, f12, f31
/* 08BFC0 80091560 FDAD0332 */  fmul    f13, f13, f12
/* 08BFC4 80091564 FD8D0372 */  fmul    f12, f13, f13
/* 08BFC8 80091568 FDBE0372 */  fmul    f13, f30, f13
/* 08BFCC 8009156C FD9DFB3C */  fnmsub  f12, f29, f12, f31
/* 08BFD0 80091570 FD8D0332 */  fmul    f12, f13, f12
/* 08BFD4 80091574 FD9D0332 */  fmul    f12, f29, f12
/* 08BFD8 80091578 FD806018 */  frsp    f12, f12
/* 08BFDC 8009157C D181000C */  stfs    f12, 0xc(r1)
/* 08BFE0 80091580 C3A1000C */  lfs     f29, 0xc(r1)
lbl_80091584:
/* 08BFE4 80091584 C18283A4 */  lfs     f12, D_801360A4@sda21(r2)
/* 08BFE8 80091588 C1A283A8 */  lfs     f13, D_801360A8@sda21(r2)
/* 08BFEC 8009158C EFACE824 */  fdivs   f29, f12, f29
/* 08BFF0 80091590 C18283AC */  lfs     f12, D_801360AC@sda21(r2)
/* 08BFF4 80091594 EDAD0272 */  fmuls   f13, f13, f9
/* 08BFF8 80091598 EC000772 */  fmuls   f0, f0, f29
/* 08BFFC 8009159C EC210772 */  fmuls   f1, f1, f29
/* 08C000 800915A0 FC0D6040 */  fcmpo   cr0, f13, f12
/* 08C004 800915A4 EC420772 */  fmuls   f2, f2, f29
/* 08C008 800915A8 40800008 */  bge     lbl_800915B0
/* 08C00C 800915AC 48000008 */  b       lbl_800915B4
lbl_800915B0:
/* 08C010 800915B0 FDA06090 */  fmr     f13, f12
lbl_800915B4:
/* 08C014 800915B4 FD80681E */  fctiwz  f12, f13
/* 08C018 800915B8 80610070 */  lwz     r3, 0x70(r1)
/* 08C01C 800915BC D9810080 */  stfd    f12, 0x80(r1)
/* 08C020 800915C0 80010084 */  lwz     r0, 0x84(r1)
/* 08C024 800915C4 98030008 */  stb     r0, 8(r3)
/* 08C028 800915C8 C1A283A8 */  lfs     f13, D_801360A8@sda21(r2)
/* 08C02C 800915CC C18283AC */  lfs     f12, D_801360AC@sda21(r2)
/* 08C030 800915D0 EDAD02B2 */  fmuls   f13, f13, f10
/* 08C034 800915D4 FC0D6040 */  fcmpo   cr0, f13, f12
/* 08C038 800915D8 40800008 */  bge     lbl_800915E0
/* 08C03C 800915DC 48000008 */  b       lbl_800915E4
lbl_800915E0:
/* 08C040 800915E0 FDA06090 */  fmr     f13, f12
lbl_800915E4:
/* 08C044 800915E4 FD80681E */  fctiwz  f12, f13
/* 08C048 800915E8 80610070 */  lwz     r3, 0x70(r1)
/* 08C04C 800915EC D9810080 */  stfd    f12, 0x80(r1)
/* 08C050 800915F0 80010084 */  lwz     r0, 0x84(r1)
/* 08C054 800915F4 98030009 */  stb     r0, 9(r3)
/* 08C058 800915F8 C1A283A8 */  lfs     f13, D_801360A8@sda21(r2)
/* 08C05C 800915FC C18283AC */  lfs     f12, D_801360AC@sda21(r2)
/* 08C060 80091600 EDAD02F2 */  fmuls   f13, f13, f11
/* 08C064 80091604 FC0D6040 */  fcmpo   cr0, f13, f12
/* 08C068 80091608 40800008 */  bge     lbl_80091610
/* 08C06C 8009160C 48000008 */  b       lbl_80091614
lbl_80091610:
/* 08C070 80091610 FDA06090 */  fmr     f13, f12
lbl_80091614:
/* 08C074 80091614 FD80681E */  fctiwz  f12, f13
/* 08C078 80091618 80610070 */  lwz     r3, 0x70(r1)
/* 08C07C 8009161C D9810080 */  stfd    f12, 0x80(r1)
/* 08C080 80091620 80010084 */  lwz     r0, 0x84(r1)
/* 08C084 80091624 9803000A */  stb     r0, 0xa(r3)
/* 08C088 80091628 C1A283A8 */  lfs     f13, D_801360A8@sda21(r2)
/* 08C08C 8009162C C18283AC */  lfs     f12, D_801360AC@sda21(r2)
/* 08C090 80091630 EDAD0032 */  fmuls   f13, f13, f0
/* 08C094 80091634 FC0D6040 */  fcmpo   cr0, f13, f12
/* 08C098 80091638 40800008 */  bge     lbl_80091640
/* 08C09C 8009163C 48000008 */  b       lbl_80091644
lbl_80091640:
/* 08C0A0 80091640 FDA06090 */  fmr     f13, f12
lbl_80091644:
/* 08C0A4 80091644 FD80681E */  fctiwz  f12, f13
/* 08C0A8 80091648 80610070 */  lwz     r3, 0x70(r1)
/* 08C0AC 8009164C D9810080 */  stfd    f12, 0x80(r1)
/* 08C0B0 80091650 80010084 */  lwz     r0, 0x84(r1)
/* 08C0B4 80091654 98030018 */  stb     r0, 0x18(r3)
/* 08C0B8 80091658 C1A283A8 */  lfs     f13, D_801360A8@sda21(r2)
/* 08C0BC 8009165C C18283AC */  lfs     f12, D_801360AC@sda21(r2)
/* 08C0C0 80091660 EDAD0072 */  fmuls   f13, f13, f1
/* 08C0C4 80091664 FC0D6040 */  fcmpo   cr0, f13, f12
/* 08C0C8 80091668 40800008 */  bge     lbl_80091670
/* 08C0CC 8009166C 48000008 */  b       lbl_80091674
lbl_80091670:
/* 08C0D0 80091670 FDA06090 */  fmr     f13, f12
lbl_80091674:
/* 08C0D4 80091674 FD80681E */  fctiwz  f12, f13
/* 08C0D8 80091678 80610070 */  lwz     r3, 0x70(r1)
/* 08C0DC 8009167C D9810080 */  stfd    f12, 0x80(r1)
/* 08C0E0 80091680 80010084 */  lwz     r0, 0x84(r1)
/* 08C0E4 80091684 98030019 */  stb     r0, 0x19(r3)
/* 08C0E8 80091688 C1A283A8 */  lfs     f13, D_801360A8@sda21(r2)
/* 08C0EC 8009168C C18283AC */  lfs     f12, D_801360AC@sda21(r2)
/* 08C0F0 80091690 EDAD00B2 */  fmuls   f13, f13, f2
/* 08C0F4 80091694 FC0D6040 */  fcmpo   cr0, f13, f12
/* 08C0F8 80091698 40800008 */  bge     lbl_800916A0
/* 08C0FC 8009169C 48000008 */  b       lbl_800916A4
lbl_800916A0:
/* 08C100 800916A0 FDA06090 */  fmr     f13, f12
lbl_800916A4:
/* 08C104 800916A4 FFE0681E */  fctiwz  f31, f13
/* 08C108 800916A8 38000002 */  li      r0, 2
/* 08C10C 800916AC EDA402B2 */  fmuls   f13, f4, f10
/* 08C110 800916B0 80610070 */  lwz     r3, 0x70(r1)
/* 08C114 800916B4 ED840072 */  fmuls   f12, f4, f1
/* 08C118 800916B8 DBE10080 */  stfd    f31, 0x80(r1)
/* 08C11C 800916BC EDA36A7A */  fmadds  f13, f3, f9, f13
/* 08C120 800916C0 38A00000 */  li      r5, 0
/* 08C124 800916C4 ED83603A */  fmadds  f12, f3, f0, f12
/* 08C128 800916C8 80810084 */  lwz     r4, 0x84(r1)
/* 08C12C 800916CC EFE56AFE */  fnmadds f31, f5, f11, f13
/* 08C130 800916D0 9883001A */  stb     r4, 0x1a(r3)
/* 08C134 800916D4 EC8401F2 */  fmuls   f4, f4, f7
/* 08C138 800916D8 38800080 */  li      r4, 0x80
/* 08C13C 800916DC EDA560BE */  fnmadds f13, f5, f2, f12
/* 08C140 800916E0 80610070 */  lwz     r3, 0x70(r1)
/* 08C144 800916E4 EC6321BA */  fmadds  f3, f3, f6, f4
/* 08C148 800916E8 7C0903A6 */  mtctr   r0
/* 08C14C 800916EC 38C10028 */  addi    r6, r1, 0x28
/* 08C150 800916F0 98A30000 */  stb     r5, 0(r3)
/* 08C154 800916F4 ED851A3E */  fnmadds f12, f5, f8, f3
/* 08C158 800916F8 80610070 */  lwz     r3, 0x70(r1)
/* 08C15C 800916FC 38E00000 */  li      r7, 0
/* 08C160 80091700 98A30001 */  stb     r5, 1(r3)
/* 08C164 80091704 80610070 */  lwz     r3, 0x70(r1)
/* 08C168 80091708 98A30002 */  stb     r5, 2(r3)
/* 08C16C 8009170C 80610070 */  lwz     r3, 0x70(r1)
/* 08C170 80091710 98A30003 */  stb     r5, 3(r3)
/* 08C174 80091714 80610070 */  lwz     r3, 0x70(r1)
/* 08C178 80091718 98A30004 */  stb     r5, 4(r3)
/* 08C17C 8009171C 80610070 */  lwz     r3, 0x70(r1)
/* 08C180 80091720 98A30005 */  stb     r5, 5(r3)
/* 08C184 80091724 80610070 */  lwz     r3, 0x70(r1)
/* 08C188 80091728 98A30006 */  stb     r5, 6(r3)
/* 08C18C 8009172C 80610070 */  lwz     r3, 0x70(r1)
/* 08C190 80091730 98A30007 */  stb     r5, 7(r3)
/* 08C194 80091734 80610070 */  lwz     r3, 0x70(r1)
/* 08C198 80091738 98A30010 */  stb     r5, 0x10(r3)
/* 08C19C 8009173C 80610070 */  lwz     r3, 0x70(r1)
/* 08C1A0 80091740 98830011 */  stb     r4, 0x11(r3)
/* 08C1A4 80091744 80610070 */  lwz     r3, 0x70(r1)
/* 08C1A8 80091748 98A30012 */  stb     r5, 0x12(r3)
/* 08C1AC 8009174C 80610070 */  lwz     r3, 0x70(r1)
/* 08C1B0 80091750 98A30013 */  stb     r5, 0x13(r3)
/* 08C1B4 80091754 80610070 */  lwz     r3, 0x70(r1)
/* 08C1B8 80091758 98A30014 */  stb     r5, 0x14(r3)
/* 08C1BC 8009175C 80610070 */  lwz     r3, 0x70(r1)
/* 08C1C0 80091760 98830015 */  stb     r4, 0x15(r3)
/* 08C1C4 80091764 80610070 */  lwz     r3, 0x70(r1)
/* 08C1C8 80091768 98A30016 */  stb     r5, 0x16(r3)
/* 08C1CC 8009176C 80610070 */  lwz     r3, 0x70(r1)
/* 08C1D0 80091770 98A30017 */  stb     r5, 0x17(r3)
/* 08C1D4 80091774 D1210028 */  stfs    f9, 0x28(r1)
/* 08C1D8 80091778 80610024 */  lwz     r3, 0x24(r1)
/* 08C1DC 8009177C D1410038 */  stfs    f10, 0x38(r1)
/* 08C1E0 80091780 C0A28388 */  lfs     f5, D_80136088@sda21(r2)
/* 08C1E4 80091784 7C691B78 */  mr      r9, r3
/* 08C1E8 80091788 D1610048 */  stfs    f11, 0x48(r1)
/* 08C1EC 8009178C 39430020 */  addi    r10, r3, 0x20
/* 08C1F0 80091790 C08283A4 */  lfs     f4, D_801360A4@sda21(r2)
/* 08C1F4 80091794 D3E10058 */  stfs    f31, 0x58(r1)
/* 08C1F8 80091798 C06283B0 */  lfs     f3, D_801360B0@sda21(r2)
/* 08C1FC 8009179C D001002C */  stfs    f0, 0x2c(r1)
/* 08C200 800917A0 D021003C */  stfs    f1, 0x3c(r1)
/* 08C204 800917A4 D041004C */  stfs    f2, 0x4c(r1)
/* 08C208 800917A8 D1A1005C */  stfs    f13, 0x5c(r1)
/* 08C20C 800917AC D0C10030 */  stfs    f6, 0x30(r1)
/* 08C210 800917B0 D0E10040 */  stfs    f7, 0x40(r1)
/* 08C214 800917B4 D1010050 */  stfs    f8, 0x50(r1)
/* 08C218 800917B8 D1810060 */  stfs    f12, 0x60(r1)
/* 08C21C 800917BC D0A10034 */  stfs    f5, 0x34(r1)
/* 08C220 800917C0 D0A10044 */  stfs    f5, 0x44(r1)
/* 08C224 800917C4 D0A10054 */  stfs    f5, 0x54(r1)
/* 08C228 800917C8 D0810064 */  stfs    f4, 0x64(r1)
lbl_800917CC:
/* 08C22C 800917CC C0260000 */  lfs     f1, 0(r6)
/* 08C230 800917D0 C0060004 */  lfs     f0, 4(r6)
/* 08C234 800917D4 EC230072 */  fmuls   f1, f3, f1
/* 08C238 800917D8 EC030032 */  fmuls   f0, f3, f0
/* 08C23C 800917DC FC20081E */  fctiwz  f1, f1
/* 08C240 800917E0 FC00001E */  fctiwz  f0, f0
/* 08C244 800917E4 D8210080 */  stfd    f1, 0x80(r1)
/* 08C248 800917E8 D8010078 */  stfd    f0, 0x78(r1)
/* 08C24C 800917EC 80A10084 */  lwz     r5, 0x84(r1)
/* 08C250 800917F0 8101007C */  lwz     r8, 0x7c(r1)
/* 08C254 800917F4 54A0801E */  slwi    r0, r5, 0x10
/* 08C258 800917F8 5503843E */  srwi    r3, r8, 0x10
/* 08C25C 800917FC 50A3001E */  rlwimi  r3, r5, 0, 0, 0xf
/* 08C260 80091800 90690000 */  stw     r3, 0(r9)
/* 08C264 80091804 5100043E */  rlwimi  r0, r8, 0, 0x10, 0x1f
/* 08C268 80091808 900A0000 */  stw     r0, 0(r10)
/* 08C26C 8009180C C0260008 */  lfs     f1, 8(r6)
/* 08C270 80091810 C006000C */  lfs     f0, 0xc(r6)
/* 08C274 80091814 38C60010 */  addi    r6, r6, 0x10
/* 08C278 80091818 EC230072 */  fmuls   f1, f3, f1
/* 08C27C 8009181C EC030032 */  fmuls   f0, f3, f0
/* 08C280 80091820 FC20081E */  fctiwz  f1, f1
/* 08C284 80091824 FC00001E */  fctiwz  f0, f0
/* 08C288 80091828 D8210080 */  stfd    f1, 0x80(r1)
/* 08C28C 8009182C D8010078 */  stfd    f0, 0x78(r1)
/* 08C290 80091830 80A10084 */  lwz     r5, 0x84(r1)
/* 08C294 80091834 8101007C */  lwz     r8, 0x7c(r1)
/* 08C298 80091838 54A0801E */  slwi    r0, r5, 0x10
/* 08C29C 8009183C 5503843E */  srwi    r3, r8, 0x10
/* 08C2A0 80091840 50A3001E */  rlwimi  r3, r5, 0, 0, 0xf
/* 08C2A4 80091844 90690004 */  stw     r3, 4(r9)
/* 08C2A8 80091848 5100043E */  rlwimi  r0, r8, 0, 0x10, 0x1f
/* 08C2AC 8009184C 39290008 */  addi    r9, r9, 8
/* 08C2B0 80091850 900A0004 */  stw     r0, 4(r10)
/* 08C2B4 80091854 394A0008 */  addi    r10, r10, 8
/* 08C2B8 80091858 C0260000 */  lfs     f1, 0(r6)
/* 08C2BC 8009185C 38E70001 */  addi    r7, r7, 1
/* 08C2C0 80091860 C0060004 */  lfs     f0, 4(r6)
/* 08C2C4 80091864 EC230072 */  fmuls   f1, f3, f1
/* 08C2C8 80091868 EC030032 */  fmuls   f0, f3, f0
/* 08C2CC 8009186C FC20081E */  fctiwz  f1, f1
/* 08C2D0 80091870 FC00001E */  fctiwz  f0, f0
/* 08C2D4 80091874 D8210080 */  stfd    f1, 0x80(r1)
/* 08C2D8 80091878 D8010078 */  stfd    f0, 0x78(r1)
/* 08C2DC 8009187C 80A10084 */  lwz     r5, 0x84(r1)
/* 08C2E0 80091880 8101007C */  lwz     r8, 0x7c(r1)
/* 08C2E4 80091884 54A0801E */  slwi    r0, r5, 0x10
/* 08C2E8 80091888 5503843E */  srwi    r3, r8, 0x10
/* 08C2EC 8009188C 50A3001E */  rlwimi  r3, r5, 0, 0, 0xf
/* 08C2F0 80091890 90690000 */  stw     r3, 0(r9)
/* 08C2F4 80091894 5100043E */  rlwimi  r0, r8, 0, 0x10, 0x1f
/* 08C2F8 80091898 900A0000 */  stw     r0, 0(r10)
/* 08C2FC 8009189C C0260008 */  lfs     f1, 8(r6)
/* 08C300 800918A0 C006000C */  lfs     f0, 0xc(r6)
/* 08C304 800918A4 38C60010 */  addi    r6, r6, 0x10
/* 08C308 800918A8 EC230072 */  fmuls   f1, f3, f1
/* 08C30C 800918AC EC030032 */  fmuls   f0, f3, f0
/* 08C310 800918B0 FC20081E */  fctiwz  f1, f1
/* 08C314 800918B4 FC00001E */  fctiwz  f0, f0
/* 08C318 800918B8 D8210080 */  stfd    f1, 0x80(r1)
/* 08C31C 800918BC D8010078 */  stfd    f0, 0x78(r1)
/* 08C320 800918C0 80A10084 */  lwz     r5, 0x84(r1)
/* 08C324 800918C4 8101007C */  lwz     r8, 0x7c(r1)
/* 08C328 800918C8 54A0801E */  slwi    r0, r5, 0x10
/* 08C32C 800918CC 5503843E */  srwi    r3, r8, 0x10
/* 08C330 800918D0 50A3001E */  rlwimi  r3, r5, 0, 0, 0xf
/* 08C334 800918D4 90690004 */  stw     r3, 4(r9)
/* 08C338 800918D8 5100043E */  rlwimi  r0, r8, 0, 0x10, 0x1f
/* 08C33C 800918DC 39290008 */  addi    r9, r9, 8
/* 08C340 800918E0 900A0004 */  stw     r0, 4(r10)
/* 08C344 800918E4 394A0008 */  addi    r10, r10, 8
/* 08C348 800918E8 4200FEE4 */  bdnz    lbl_800917CC
/* 08C34C 800918EC 800100AC */  lwz     r0, 0xac(r1)
/* 08C350 800918F0 CBE100A0 */  lfd     f31, 0xa0(r1)
/* 08C354 800918F4 CBC10098 */  lfd     f30, 0x98(r1)
/* 08C358 800918F8 7C0803A6 */  mtlr    r0
/* 08C35C 800918FC CBA10090 */  lfd     f29, 0x90(r1)
/* 08C360 80091900 83E1008C */  lwz     r31, 0x8c(r1)
/* 08C364 80091904 382100A8 */  addi    r1, r1, 0xa8
/* 08C368 80091908 4E800020 */  blr     
