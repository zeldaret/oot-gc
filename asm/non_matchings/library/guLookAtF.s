glabel guLookAtF
/* 08E000 800935A0 7C0802A6 */  mflr    r0
/* 08E004 800935A4 90010004 */  stw     r0, 4(r1)
/* 08E008 800935A8 9421FFA8 */  stwu    r1, -0x58(r1)
/* 08E00C 800935AC DBE10050 */  stfd    f31, 0x50(r1)
/* 08E010 800935B0 38810034 */  addi    r4, r1, 0x34
/* 08E014 800935B4 DBC10048 */  stfd    f30, 0x48(r1)
/* 08E018 800935B8 DBA10040 */  stfd    f29, 0x40(r1)
/* 08E01C 800935BC 93E1003C */  stw     r31, 0x3c(r1)
/* 08E020 800935C0 7C7F1B78 */  mr      r31, r3
/* 08E024 800935C4 C0028388 */  lfs     f0, D_80136088@sda21(r2)
/* 08E028 800935C8 D0010024 */  stfs    f0, 0x24(r1)
/* 08E02C 800935CC C00283A4 */  lfs     f0, D_801360A4@sda21(r2)
/* 08E030 800935D0 D001001C */  stfs    f0, 0x1c(r1)
/* 08E034 800935D4 80BF0064 */  lwz     r5, 0x64(r31)
/* 08E038 800935D8 4BFA11A9 */  bl      cpuGetAddressBuffer
/* 08E03C 800935DC 80BF012C */  lwz     r5, 0x12c(r31)
/* 08E040 800935E0 387F0000 */  addi    r3, r31, 0
/* 08E044 800935E4 38810030 */  addi    r4, r1, 0x30
/* 08E048 800935E8 4BFA1199 */  bl      cpuGetAddressBuffer
/* 08E04C 800935EC 801F006C */  lwz     r0, 0x6c(r31)
/* 08E050 800935F0 9001002C */  stw     r0, 0x2c(r1)
/* 08E054 800935F4 C061002C */  lfs     f3, 0x2c(r1)
/* 08E058 800935F8 801F0074 */  lwz     r0, 0x74(r31)
/* 08E05C 800935FC 9001002C */  stw     r0, 0x2c(r1)
/* 08E060 80093600 C081002C */  lfs     f4, 0x2c(r1)
/* 08E064 80093604 801F007C */  lwz     r0, 0x7c(r31)
/* 08E068 80093608 9001002C */  stw     r0, 0x2c(r1)
/* 08E06C 8009360C 80610030 */  lwz     r3, 0x30(r1)
/* 08E070 80093610 C0A1002C */  lfs     f5, 0x2c(r1)
/* 08E074 80093614 80030010 */  lwz     r0, 0x10(r3)
/* 08E078 80093618 9001002C */  stw     r0, 0x2c(r1)
/* 08E07C 8009361C C001002C */  lfs     f0, 0x2c(r1)
/* 08E080 80093620 80030014 */  lwz     r0, 0x14(r3)
/* 08E084 80093624 ECC01828 */  fsubs   f6, f0, f3
/* 08E088 80093628 9001002C */  stw     r0, 0x2c(r1)
/* 08E08C 8009362C C001002C */  lfs     f0, 0x2c(r1)
/* 08E090 80093630 80030018 */  lwz     r0, 0x18(r3)
/* 08E094 80093634 ECE02028 */  fsubs   f7, f0, f4
/* 08E098 80093638 9001002C */  stw     r0, 0x2c(r1)
/* 08E09C 8009363C C021002C */  lfs     f1, 0x2c(r1)
/* 08E0A0 80093640 EC0701F2 */  fmuls   f0, f7, f7
/* 08E0A4 80093644 8003001C */  lwz     r0, 0x1c(r3)
/* 08E0A8 80093648 ED012828 */  fsubs   f8, f1, f5
/* 08E0AC 8009364C 9001002C */  stw     r0, 0x2c(r1)
/* 08E0B0 80093650 EC2601BA */  fmadds  f1, f6, f6, f0
/* 08E0B4 80093654 C001002C */  lfs     f0, 0x2c(r1)
/* 08E0B8 80093658 80030020 */  lwz     r0, 0x20(r3)
/* 08E0BC 8009365C EDA80A3A */  fmadds  f13, f8, f8, f1
/* 08E0C0 80093660 9001002C */  stw     r0, 0x2c(r1)
/* 08E0C4 80093664 C021002C */  lfs     f1, 0x2c(r1)
/* 08E0C8 80093668 80030024 */  lwz     r0, 0x24(r3)
/* 08E0CC 8009366C 9001002C */  stw     r0, 0x2c(r1)
/* 08E0D0 80093670 C1228388 */  lfs     f9, D_80136088@sda21(r2)
/* 08E0D4 80093674 C041002C */  lfs     f2, 0x2c(r1)
/* 08E0D8 80093678 FC0D4840 */  fcmpo   cr0, f13, f9
/* 08E0DC 8009367C 40810050 */  ble     lbl_800936CC
/* 08E0E0 80093680 FD406834 */  frsqrte f10, f13
/* 08E0E4 80093684 C9828390 */  lfd     f12, D_80136090@sda21(r2)
/* 08E0E8 80093688 C9628398 */  lfd     f11, D_80136098@sda21(r2)
/* 08E0EC 8009368C FD2A02B2 */  fmul    f9, f10, f10
/* 08E0F0 80093690 FD4C02B2 */  fmul    f10, f12, f10
/* 08E0F4 80093694 FD2D5A7C */  fnmsub  f9, f13, f9, f11
/* 08E0F8 80093698 FD4A0272 */  fmul    f10, f10, f9
/* 08E0FC 8009369C FD2A02B2 */  fmul    f9, f10, f10
/* 08E100 800936A0 FD4C02B2 */  fmul    f10, f12, f10
/* 08E104 800936A4 FD2D5A7C */  fnmsub  f9, f13, f9, f11
/* 08E108 800936A8 FD4A0272 */  fmul    f10, f10, f9
/* 08E10C 800936AC FD2A02B2 */  fmul    f9, f10, f10
/* 08E110 800936B0 FD4C02B2 */  fmul    f10, f12, f10
/* 08E114 800936B4 FD2D5A7C */  fnmsub  f9, f13, f9, f11
/* 08E118 800936B8 FD2A0272 */  fmul    f9, f10, f9
/* 08E11C 800936BC FD2D0272 */  fmul    f9, f13, f9
/* 08E120 800936C0 FD204818 */  frsp    f9, f9
/* 08E124 800936C4 D1210014 */  stfs    f9, 0x14(r1)
/* 08E128 800936C8 C1A10014 */  lfs     f13, 0x14(r1)
lbl_800936CC:
/* 08E12C 800936CC C12283A0 */  lfs     f9, D_801360A0@sda21(r2)
/* 08E130 800936D0 C1828388 */  lfs     f12, D_80136088@sda21(r2)
/* 08E134 800936D4 ED296824 */  fdivs   f9, f9, f13
/* 08E138 800936D8 ED080272 */  fmuls   f8, f8, f9
/* 08E13C 800936DC ECC60272 */  fmuls   f6, f6, f9
/* 08E140 800936E0 ECE70272 */  fmuls   f7, f7, f9
/* 08E144 800936E4 ED400232 */  fmuls   f10, f0, f8
/* 08E148 800936E8 ED2101B2 */  fmuls   f9, f1, f6
/* 08E14C 800936EC EDA201F2 */  fmuls   f13, f2, f7
/* 08E150 800936F0 ED4251B8 */  fmsubs  f10, f2, f6, f10
/* 08E154 800936F4 ED6049F8 */  fmsubs  f11, f0, f7, f9
/* 08E158 800936F8 ED216A38 */  fmsubs  f9, f1, f8, f13
/* 08E15C 800936FC EC0A02B2 */  fmuls   f0, f10, f10
/* 08E160 80093700 EC09027A */  fmadds  f0, f9, f9, f0
/* 08E164 80093704 EDAB02FA */  fmadds  f13, f11, f11, f0
/* 08E168 80093708 FC0D6040 */  fcmpo   cr0, f13, f12
/* 08E16C 8009370C 40810050 */  ble     lbl_8009375C
/* 08E170 80093710 FC206834 */  frsqrte f1, f13
/* 08E174 80093714 C9828390 */  lfd     f12, D_80136090@sda21(r2)
/* 08E178 80093718 C8428398 */  lfd     f2, D_80136098@sda21(r2)
/* 08E17C 8009371C FC010072 */  fmul    f0, f1, f1
/* 08E180 80093720 FC2C0072 */  fmul    f1, f12, f1
/* 08E184 80093724 FC0D103C */  fnmsub  f0, f13, f0, f2
/* 08E188 80093728 FC210032 */  fmul    f1, f1, f0
/* 08E18C 8009372C FC010072 */  fmul    f0, f1, f1
/* 08E190 80093730 FC2C0072 */  fmul    f1, f12, f1
/* 08E194 80093734 FC0D103C */  fnmsub  f0, f13, f0, f2
/* 08E198 80093738 FC210032 */  fmul    f1, f1, f0
/* 08E19C 8009373C FC010072 */  fmul    f0, f1, f1
/* 08E1A0 80093740 FC2C0072 */  fmul    f1, f12, f1
/* 08E1A4 80093744 FC0D103C */  fnmsub  f0, f13, f0, f2
/* 08E1A8 80093748 FC010032 */  fmul    f0, f1, f0
/* 08E1AC 8009374C FC0D0032 */  fmul    f0, f13, f0
/* 08E1B0 80093750 FC000018 */  frsp    f0, f0
/* 08E1B4 80093754 D0010010 */  stfs    f0, 0x10(r1)
/* 08E1B8 80093758 C1A10010 */  lfs     f13, 0x10(r1)
lbl_8009375C:
/* 08E1BC 8009375C C00283A4 */  lfs     f0, D_801360A4@sda21(r2)
/* 08E1C0 80093760 C1828388 */  lfs     f12, D_80136088@sda21(r2)
/* 08E1C4 80093764 EC006824 */  fdivs   f0, f0, f13
/* 08E1C8 80093768 ED6B0032 */  fmuls   f11, f11, f0
/* 08E1CC 8009376C ED290032 */  fmuls   f9, f9, f0
/* 08E1D0 80093770 ED4A0032 */  fmuls   f10, f10, f0
/* 08E1D4 80093774 EC2602F2 */  fmuls   f1, f6, f11
/* 08E1D8 80093778 EC070272 */  fmuls   f0, f7, f9
/* 08E1DC 8009377C EDA802B2 */  fmuls   f13, f8, f10
/* 08E1E0 80093780 EC280A78 */  fmsubs  f1, f8, f9, f1
/* 08E1E4 80093784 EC4602B8 */  fmsubs  f2, f6, f10, f0
/* 08E1E8 80093788 EC076AF8 */  fmsubs  f0, f7, f11, f13
/* 08E1EC 8009378C EDA10072 */  fmuls   f13, f1, f1
/* 08E1F0 80093790 EDA0683A */  fmadds  f13, f0, f0, f13
/* 08E1F4 80093794 EFA268BA */  fmadds  f29, f2, f2, f13
/* 08E1F8 80093798 FC1D6040 */  fcmpo   cr0, f29, f12
/* 08E1FC 8009379C 40810050 */  ble     lbl_800937EC
/* 08E200 800937A0 FDA0E834 */  frsqrte f13, f29
/* 08E204 800937A4 CBC28390 */  lfd     f30, D_80136090@sda21(r2)
/* 08E208 800937A8 CBE28398 */  lfd     f31, D_80136098@sda21(r2)
/* 08E20C 800937AC FD8D0372 */  fmul    f12, f13, f13
/* 08E210 800937B0 FDBE0372 */  fmul    f13, f30, f13
/* 08E214 800937B4 FD9DFB3C */  fnmsub  f12, f29, f12, f31
/* 08E218 800937B8 FDAD0332 */  fmul    f13, f13, f12
/* 08E21C 800937BC FD8D0372 */  fmul    f12, f13, f13
/* 08E220 800937C0 FDBE0372 */  fmul    f13, f30, f13
/* 08E224 800937C4 FD9DFB3C */  fnmsub  f12, f29, f12, f31
/* 08E228 800937C8 FDAD0332 */  fmul    f13, f13, f12
/* 08E22C 800937CC FD8D0372 */  fmul    f12, f13, f13
/* 08E230 800937D0 FDBE0372 */  fmul    f13, f30, f13
/* 08E234 800937D4 FD9DFB3C */  fnmsub  f12, f29, f12, f31
/* 08E238 800937D8 FD8D0332 */  fmul    f12, f13, f12
/* 08E23C 800937DC FD9D0332 */  fmul    f12, f29, f12
/* 08E240 800937E0 FD806018 */  frsp    f12, f12
/* 08E244 800937E4 D181000C */  stfs    f12, 0xc(r1)
/* 08E248 800937E8 C3A1000C */  lfs     f29, 0xc(r1)
lbl_800937EC:
/* 08E24C 800937EC C3E283A4 */  lfs     f31, D_801360A4@sda21(r2)
/* 08E250 800937F0 EDA402B2 */  fmuls   f13, f4, f10
/* 08E254 800937F4 ED8401F2 */  fmuls   f12, f4, f7
/* 08E258 800937F8 D121002C */  stfs    f9, 0x2c(r1)
/* 08E25C 800937FC EFBFE824 */  fdivs   f29, f31, f29
/* 08E260 80093800 8001002C */  lwz     r0, 0x2c(r1)
/* 08E264 80093804 80610034 */  lwz     r3, 0x34(r1)
/* 08E268 80093808 90030000 */  stw     r0, 0(r3)
/* 08E26C 8009380C D141002C */  stfs    f10, 0x2c(r1)
/* 08E270 80093810 ED236A7A */  fmadds  f9, f3, f9, f13
/* 08E274 80093814 8001002C */  lwz     r0, 0x2c(r1)
/* 08E278 80093818 80610034 */  lwz     r3, 0x34(r1)
/* 08E27C 8009381C EC210772 */  fmuls   f1, f1, f29
/* 08E280 80093820 EC000772 */  fmuls   f0, f0, f29
/* 08E284 80093824 90030010 */  stw     r0, 0x10(r3)
/* 08E288 80093828 ED454AFE */  fnmadds f10, f5, f11, f9
/* 08E28C 8009382C ED240072 */  fmuls   f9, f4, f1
/* 08E290 80093830 D161002C */  stfs    f11, 0x2c(r1)
/* 08E294 80093834 EC8361BA */  fmadds  f4, f3, f6, f12
/* 08E298 80093838 EC420772 */  fmuls   f2, f2, f29
/* 08E29C 8009383C 8001002C */  lwz     r0, 0x2c(r1)
/* 08E2A0 80093840 80610034 */  lwz     r3, 0x34(r1)
/* 08E2A4 80093844 ED23483A */  fmadds  f9, f3, f0, f9
/* 08E2A8 80093848 EC65223E */  fnmadds f3, f5, f8, f4
/* 08E2AC 8009384C 90030020 */  stw     r0, 0x20(r3)
/* 08E2B0 80093850 EC8548BE */  fnmadds f4, f5, f2, f9
/* 08E2B4 80093854 D141002C */  stfs    f10, 0x2c(r1)
/* 08E2B8 80093858 8001002C */  lwz     r0, 0x2c(r1)
/* 08E2BC 8009385C 80610034 */  lwz     r3, 0x34(r1)
/* 08E2C0 80093860 90030030 */  stw     r0, 0x30(r3)
/* 08E2C4 80093864 D001002C */  stfs    f0, 0x2c(r1)
/* 08E2C8 80093868 8001002C */  lwz     r0, 0x2c(r1)
/* 08E2CC 8009386C 80610034 */  lwz     r3, 0x34(r1)
/* 08E2D0 80093870 90030004 */  stw     r0, 4(r3)
/* 08E2D4 80093874 D021002C */  stfs    f1, 0x2c(r1)
/* 08E2D8 80093878 8001002C */  lwz     r0, 0x2c(r1)
/* 08E2DC 8009387C 80610034 */  lwz     r3, 0x34(r1)
/* 08E2E0 80093880 90030014 */  stw     r0, 0x14(r3)
/* 08E2E4 80093884 D041002C */  stfs    f2, 0x2c(r1)
/* 08E2E8 80093888 8001002C */  lwz     r0, 0x2c(r1)
/* 08E2EC 8009388C 80610034 */  lwz     r3, 0x34(r1)
/* 08E2F0 80093890 90030024 */  stw     r0, 0x24(r3)
/* 08E2F4 80093894 D081002C */  stfs    f4, 0x2c(r1)
/* 08E2F8 80093898 8001002C */  lwz     r0, 0x2c(r1)
/* 08E2FC 8009389C 80610034 */  lwz     r3, 0x34(r1)
/* 08E300 800938A0 90030034 */  stw     r0, 0x34(r3)
/* 08E304 800938A4 D0C1002C */  stfs    f6, 0x2c(r1)
/* 08E308 800938A8 8001002C */  lwz     r0, 0x2c(r1)
/* 08E30C 800938AC 80610034 */  lwz     r3, 0x34(r1)
/* 08E310 800938B0 90030008 */  stw     r0, 8(r3)
/* 08E314 800938B4 D0E1002C */  stfs    f7, 0x2c(r1)
/* 08E318 800938B8 8001002C */  lwz     r0, 0x2c(r1)
/* 08E31C 800938BC 80610034 */  lwz     r3, 0x34(r1)
/* 08E320 800938C0 90030018 */  stw     r0, 0x18(r3)
/* 08E324 800938C4 D101002C */  stfs    f8, 0x2c(r1)
/* 08E328 800938C8 8001002C */  lwz     r0, 0x2c(r1)
/* 08E32C 800938CC 80610034 */  lwz     r3, 0x34(r1)
/* 08E330 800938D0 90030028 */  stw     r0, 0x28(r3)
/* 08E334 800938D4 D061002C */  stfs    f3, 0x2c(r1)
/* 08E338 800938D8 8001002C */  lwz     r0, 0x2c(r1)
/* 08E33C 800938DC 80610034 */  lwz     r3, 0x34(r1)
/* 08E340 800938E0 90030038 */  stw     r0, 0x38(r3)
/* 08E344 800938E4 80010024 */  lwz     r0, 0x24(r1)
/* 08E348 800938E8 80610034 */  lwz     r3, 0x34(r1)
/* 08E34C 800938EC 9003000C */  stw     r0, 0xc(r3)
/* 08E350 800938F0 80610034 */  lwz     r3, 0x34(r1)
/* 08E354 800938F4 9003001C */  stw     r0, 0x1c(r3)
/* 08E358 800938F8 80610034 */  lwz     r3, 0x34(r1)
/* 08E35C 800938FC 9003002C */  stw     r0, 0x2c(r3)
/* 08E360 80093900 8001001C */  lwz     r0, 0x1c(r1)
/* 08E364 80093904 80610034 */  lwz     r3, 0x34(r1)
/* 08E368 80093908 9003003C */  stw     r0, 0x3c(r3)
/* 08E36C 8009390C 8001005C */  lwz     r0, 0x5c(r1)
/* 08E370 80093910 CBE10050 */  lfd     f31, 0x50(r1)
/* 08E374 80093914 CBC10048 */  lfd     f30, 0x48(r1)
/* 08E378 80093918 CBA10040 */  lfd     f29, 0x40(r1)
/* 08E37C 8009391C 83E1003C */  lwz     r31, 0x3c(r1)
/* 08E380 80093920 38210058 */  addi    r1, r1, 0x58
/* 08E384 80093924 7C0803A6 */  mtlr    r0
/* 08E388 80093928 4E800020 */  blr     
