# trigf.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel tanf
/* 0CCAB8 800D2058 7C0802A6 */  mflr    r0
/* 0CCABC 800D205C 90010004 */  stw     r0, 4(r1)
/* 0CCAC0 800D2060 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0CCAC4 800D2064 DBE10018 */  stfd    f31, 0x18(r1)
/* 0CCAC8 800D2068 DBC10010 */  stfd    f30, 0x10(r1)
/* 0CCACC 800D206C FFC00890 */  fmr     f30, f1
/* 0CCAD0 800D2070 4800002D */  bl      cos__Ff
/* 0CCAD4 800D2074 FFE00890 */  fmr     f31, f1
/* 0CCAD8 800D2078 FC20F090 */  fmr     f1, f30
/* 0CCADC 800D207C 48000041 */  bl      sin__Ff
/* 0CCAE0 800D2080 EC21F824 */  fdivs   f1, f1, f31
/* 0CCAE4 800D2084 80010024 */  lwz     r0, 0x24(r1)
/* 0CCAE8 800D2088 CBE10018 */  lfd     f31, 0x18(r1)
/* 0CCAEC 800D208C CBC10010 */  lfd     f30, 0x10(r1)
/* 0CCAF0 800D2090 7C0803A6 */  mtlr    r0
/* 0CCAF4 800D2094 38210020 */  addi    r1, r1, 0x20
/* 0CCAF8 800D2098 4E800020 */  blr     

glabel cos__Ff
/* 0CCAFC 800D209C 7C0802A6 */  mflr    r0
/* 0CCB00 800D20A0 90010004 */  stw     r0, 4(r1)
/* 0CCB04 800D20A4 9421FFF8 */  stwu    r1, -8(r1)
/* 0CCB08 800D20A8 48000035 */  bl      cosf
/* 0CCB0C 800D20AC 8001000C */  lwz     r0, 0xc(r1)
/* 0CCB10 800D20B0 38210008 */  addi    r1, r1, 8
/* 0CCB14 800D20B4 7C0803A6 */  mtlr    r0
/* 0CCB18 800D20B8 4E800020 */  blr     

glabel sin__Ff
/* 0CCB1C 800D20BC 7C0802A6 */  mflr    r0
/* 0CCB20 800D20C0 90010004 */  stw     r0, 4(r1)
/* 0CCB24 800D20C4 9421FFF8 */  stwu    r1, -8(r1)
/* 0CCB28 800D20C8 480001A9 */  bl      sinf
/* 0CCB2C 800D20CC 8001000C */  lwz     r0, 0xc(r1)
/* 0CCB30 800D20D0 38210008 */  addi    r1, r1, 8
/* 0CCB34 800D20D4 7C0803A6 */  mtlr    r0
/* 0CCB38 800D20D8 4E800020 */  blr     

glabel cosf
/* 0CCB3C 800D20DC 7C0802A6 */  mflr    r0
/* 0CCB40 800D20E0 3C60800F */  lis     r3, __four_over_pi_m1@ha
/* 0CCB44 800D20E4 90010004 */  stw     r0, 4(r1)
/* 0CCB48 800D20E8 38633E80 */  addi    r3, r3, __four_over_pi_m1@l
/* 0CCB4C 800D20EC 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0CCB50 800D20F0 DBE10020 */  stfd    f31, 0x20(r1)
/* 0CCB54 800D20F4 93E1001C */  stw     r31, 0x1c(r1)
/* 0CCB58 800D20F8 D0210008 */  stfs    f1, 8(r1)
/* 0CCB5C 800D20FC C00286F0 */  lfs     f0, D_801363F0@sda21(r2)
/* 0CCB60 800D2100 80010008 */  lwz     r0, 8(r1)
/* 0CCB64 800D2104 C0C10008 */  lfs     f6, 8(r1)
/* 0CCB68 800D2108 54000001 */  rlwinm. r0, r0, 0, 0, 0
/* 0CCB6C 800D210C EC2001B2 */  fmuls   f1, f0, f6
/* 0CCB70 800D2110 4182001C */  beq     lbl_800D212C
/* 0CCB74 800D2114 C00286F4 */  lfs     f0, D_801363F4@sda21(r2)
/* 0CCB78 800D2118 EC010028 */  fsubs   f0, f1, f0
/* 0CCB7C 800D211C FC00001E */  fctiwz  f0, f0
/* 0CCB80 800D2120 D8010010 */  stfd    f0, 0x10(r1)
/* 0CCB84 800D2124 80810014 */  lwz     r4, 0x14(r1)
/* 0CCB88 800D2128 48000018 */  b       lbl_800D2140
lbl_800D212C:
/* 0CCB8C 800D212C C00286F4 */  lfs     f0, D_801363F4@sda21(r2)
/* 0CCB90 800D2130 EC00082A */  fadds   f0, f0, f1
/* 0CCB94 800D2134 FC00001E */  fctiwz  f0, f0
/* 0CCB98 800D2138 D8010010 */  stfd    f0, 0x10(r1)
/* 0CCB9C 800D213C 80810014 */  lwz     r4, 0x14(r1)
lbl_800D2140:
/* 0CCBA0 800D2140 5480083C */  slwi    r0, r4, 1
/* 0CCBA4 800D2144 C8228700 */  lfd     f1, D_80136400@sda21(r2)
/* 0CCBA8 800D2148 6C008000 */  xoris   r0, r0, 0x8000
/* 0CCBAC 800D214C C0430000 */  lfs     f2, 0(r3)
/* 0CCBB0 800D2150 90010014 */  stw     r0, 0x14(r1)
/* 0CCBB4 800D2154 3C004330 */  lis     r0, 0x4330
/* 0CCBB8 800D2158 C0630004 */  lfs     f3, 4(r3)
/* 0CCBBC 800D215C 549F07BE */  clrlwi  r31, r4, 0x1e
/* 0CCBC0 800D2160 90010010 */  stw     r0, 0x10(r1)
/* 0CCBC4 800D2164 C0830008 */  lfs     f4, 8(r3)
/* 0CCBC8 800D2168 C8010010 */  lfd     f0, 0x10(r1)
/* 0CCBCC 800D216C C0A3000C */  lfs     f5, 0xc(r3)
/* 0CCBD0 800D2170 EC000828 */  fsubs   f0, f0, f1
/* 0CCBD4 800D2174 EC060028 */  fsubs   f0, f6, f0
/* 0CCBD8 800D2178 EC0201BA */  fmadds  f0, f2, f6, f0
/* 0CCBDC 800D217C EC0301BA */  fmadds  f0, f3, f6, f0
/* 0CCBE0 800D2180 EC0401BA */  fmadds  f0, f4, f6, f0
/* 0CCBE4 800D2184 EFE501BA */  fmadds  f31, f5, f6, f0
/* 0CCBE8 800D2188 FC20F890 */  fmr     f1, f31
/* 0CCBEC 800D218C 4BFFFCF1 */  bl      fabsf__Ff
/* 0CCBF0 800D2190 C00286F8 */  lfs     f0, D_801363F8@sda21(r2)
/* 0CCBF4 800D2194 FC010040 */  fcmpo   cr0, f1, f0
/* 0CCBF8 800D2198 40800024 */  bge     lbl_800D21BC
/* 0CCBFC 800D219C 3C60800F */  lis     r3, __sincos_on_quadrant@ha
/* 0CCC00 800D21A0 57E41838 */  slwi    r4, r31, 3
/* 0CCC04 800D21A4 38033E90 */  addi    r0, r3, __sincos_on_quadrant@l
/* 0CCC08 800D21A8 7C602214 */  add     r3, r0, r4
/* 0CCC0C 800D21AC C0230000 */  lfs     f1, 0(r3)
/* 0CCC10 800D21B0 C0030004 */  lfs     f0, 4(r3)
/* 0CCC14 800D21B4 EC3F007C */  fnmsubs f1, f31, f1, f0
/* 0CCC18 800D21B8 480000A0 */  b       lbl_800D2258
lbl_800D21BC:
/* 0CCC1C 800D21BC 57E007FF */  clrlwi. r0, r31, 0x1f
/* 0CCC20 800D21C0 EC9F07F2 */  fmuls   f4, f31, f31
/* 0CCC24 800D21C4 41820050 */  beq     lbl_800D2214
/* 0CCC28 800D21C8 3C60800F */  lis     r3, __sincos_poly@ha
/* 0CCC2C 800D21CC 38833EB0 */  addi    r4, r3, __sincos_poly@l
/* 0CCC30 800D21D0 C0440004 */  lfs     f2, 4(r4)
/* 0CCC34 800D21D4 3C60800F */  lis     r3, __sincos_on_quadrant@ha
/* 0CCC38 800D21D8 C024000C */  lfs     f1, 0xc(r4)
/* 0CCC3C 800D21DC 38033E90 */  addi    r0, r3, __sincos_on_quadrant@l
/* 0CCC40 800D21E0 C0040014 */  lfs     f0, 0x14(r4)
/* 0CCC44 800D21E4 EC62093A */  fmadds  f3, f2, f4, f1
/* 0CCC48 800D21E8 C044001C */  lfs     f2, 0x1c(r4)
/* 0CCC4C 800D21EC C0240024 */  lfs     f1, 0x24(r4)
/* 0CCC50 800D21F0 57E41838 */  slwi    r4, r31, 3
/* 0CCC54 800D21F4 7C602214 */  add     r3, r0, r4
/* 0CCC58 800D21F8 EC6400FA */  fmadds  f3, f4, f3, f0
/* 0CCC5C 800D21FC C0030000 */  lfs     f0, 0(r3)
/* 0CCC60 800D2200 EC4410FA */  fmadds  f2, f4, f3, f2
/* 0CCC64 800D2204 EC2408BE */  fnmadds f1, f4, f2, f1
/* 0CCC68 800D2208 EC3F0072 */  fmuls   f1, f31, f1
/* 0CCC6C 800D220C EC210032 */  fmuls   f1, f1, f0
/* 0CCC70 800D2210 48000048 */  b       lbl_800D2258
lbl_800D2214:
/* 0CCC74 800D2214 3C60800F */  lis     r3, __sincos_poly@ha
/* 0CCC78 800D2218 38833EB0 */  addi    r4, r3, __sincos_poly@l
/* 0CCC7C 800D221C C0440000 */  lfs     f2, 0(r4)
/* 0CCC80 800D2220 3C60800F */  lis     r3, __sincos_on_quadrant@ha
/* 0CCC84 800D2224 C0240008 */  lfs     f1, 8(r4)
/* 0CCC88 800D2228 38633E90 */  addi    r3, r3, __sincos_on_quadrant@l
/* 0CCC8C 800D222C 57E01838 */  slwi    r0, r31, 3
/* 0CCC90 800D2230 EC62093A */  fmadds  f3, f2, f4, f1
/* 0CCC94 800D2234 C0040010 */  lfs     f0, 0x10(r4)
/* 0CCC98 800D2238 C0440018 */  lfs     f2, 0x18(r4)
/* 0CCC9C 800D223C 7C630214 */  add     r3, r3, r0
/* 0CCCA0 800D2240 C0240020 */  lfs     f1, 0x20(r4)
/* 0CCCA4 800D2244 EC6400FA */  fmadds  f3, f4, f3, f0
/* 0CCCA8 800D2248 C0030004 */  lfs     f0, 4(r3)
/* 0CCCAC 800D224C EC4410FA */  fmadds  f2, f4, f3, f2
/* 0CCCB0 800D2250 EC2408BA */  fmadds  f1, f4, f2, f1
/* 0CCCB4 800D2254 EC210032 */  fmuls   f1, f1, f0
lbl_800D2258:
/* 0CCCB8 800D2258 8001002C */  lwz     r0, 0x2c(r1)
/* 0CCCBC 800D225C CBE10020 */  lfd     f31, 0x20(r1)
/* 0CCCC0 800D2260 83E1001C */  lwz     r31, 0x1c(r1)
/* 0CCCC4 800D2264 7C0803A6 */  mtlr    r0
/* 0CCCC8 800D2268 38210028 */  addi    r1, r1, 0x28
/* 0CCCCC 800D226C 4E800020 */  blr     

glabel sinf
/* 0CCCD0 800D2270 7C0802A6 */  mflr    r0
/* 0CCCD4 800D2274 3C60800F */  lis     r3, __four_over_pi_m1@ha
/* 0CCCD8 800D2278 90010004 */  stw     r0, 4(r1)
/* 0CCCDC 800D227C 38633E80 */  addi    r3, r3, __four_over_pi_m1@l
/* 0CCCE0 800D2280 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0CCCE4 800D2284 DBE10020 */  stfd    f31, 0x20(r1)
/* 0CCCE8 800D2288 93E1001C */  stw     r31, 0x1c(r1)
/* 0CCCEC 800D228C D0210008 */  stfs    f1, 8(r1)
/* 0CCCF0 800D2290 C00286F0 */  lfs     f0, D_801363F0@sda21(r2)
/* 0CCCF4 800D2294 80010008 */  lwz     r0, 8(r1)
/* 0CCCF8 800D2298 C0C10008 */  lfs     f6, 8(r1)
/* 0CCCFC 800D229C 54000001 */  rlwinm. r0, r0, 0, 0, 0
/* 0CCD00 800D22A0 EC2001B2 */  fmuls   f1, f0, f6
/* 0CCD04 800D22A4 4182001C */  beq     lbl_800D22C0
/* 0CCD08 800D22A8 C00286F4 */  lfs     f0, D_801363F4@sda21(r2)
/* 0CCD0C 800D22AC EC010028 */  fsubs   f0, f1, f0
/* 0CCD10 800D22B0 FC00001E */  fctiwz  f0, f0
/* 0CCD14 800D22B4 D8010010 */  stfd    f0, 0x10(r1)
/* 0CCD18 800D22B8 80810014 */  lwz     r4, 0x14(r1)
/* 0CCD1C 800D22BC 48000018 */  b       lbl_800D22D4
lbl_800D22C0:
/* 0CCD20 800D22C0 C00286F4 */  lfs     f0, D_801363F4@sda21(r2)
/* 0CCD24 800D22C4 EC00082A */  fadds   f0, f0, f1
/* 0CCD28 800D22C8 FC00001E */  fctiwz  f0, f0
/* 0CCD2C 800D22CC D8010010 */  stfd    f0, 0x10(r1)
/* 0CCD30 800D22D0 80810014 */  lwz     r4, 0x14(r1)
lbl_800D22D4:
/* 0CCD34 800D22D4 5480083C */  slwi    r0, r4, 1
/* 0CCD38 800D22D8 C8228700 */  lfd     f1, D_80136400@sda21(r2)
/* 0CCD3C 800D22DC 6C008000 */  xoris   r0, r0, 0x8000
/* 0CCD40 800D22E0 C0430000 */  lfs     f2, 0(r3)
/* 0CCD44 800D22E4 90010014 */  stw     r0, 0x14(r1)
/* 0CCD48 800D22E8 3C004330 */  lis     r0, 0x4330
/* 0CCD4C 800D22EC C0630004 */  lfs     f3, 4(r3)
/* 0CCD50 800D22F0 549F07BE */  clrlwi  r31, r4, 0x1e
/* 0CCD54 800D22F4 90010010 */  stw     r0, 0x10(r1)
/* 0CCD58 800D22F8 C0830008 */  lfs     f4, 8(r3)
/* 0CCD5C 800D22FC C8010010 */  lfd     f0, 0x10(r1)
/* 0CCD60 800D2300 C0A3000C */  lfs     f5, 0xc(r3)
/* 0CCD64 800D2304 EC000828 */  fsubs   f0, f0, f1
/* 0CCD68 800D2308 EC060028 */  fsubs   f0, f6, f0
/* 0CCD6C 800D230C EC0201BA */  fmadds  f0, f2, f6, f0
/* 0CCD70 800D2310 EC0301BA */  fmadds  f0, f3, f6, f0
/* 0CCD74 800D2314 EC0401BA */  fmadds  f0, f4, f6, f0
/* 0CCD78 800D2318 EFE501BA */  fmadds  f31, f5, f6, f0
/* 0CCD7C 800D231C FC20F890 */  fmr     f1, f31
/* 0CCD80 800D2320 4BFFFB5D */  bl      fabsf__Ff
/* 0CCD84 800D2324 C00286F8 */  lfs     f0, D_801363F8@sda21(r2)
/* 0CCD88 800D2328 FC010040 */  fcmpo   cr0, f1, f0
/* 0CCD8C 800D232C 40800034 */  bge     lbl_800D2360
/* 0CCD90 800D2330 3C60800F */  lis     r3, __sincos_on_quadrant@ha
/* 0CCD94 800D2334 57E41838 */  slwi    r4, r31, 3
/* 0CCD98 800D2338 38033E90 */  addi    r0, r3, __sincos_on_quadrant@l
/* 0CCD9C 800D233C 7C602214 */  add     r3, r0, r4
/* 0CCDA0 800D2340 C0230004 */  lfs     f1, 4(r3)
/* 0CCDA4 800D2344 3C80800F */  lis     r4, __sincos_poly@ha
/* 0CCDA8 800D2348 38843EB0 */  addi    r4, r4, __sincos_poly@l
/* 0CCDAC 800D234C C0030000 */  lfs     f0, 0(r3)
/* 0CCDB0 800D2350 EC3F0072 */  fmuls   f1, f31, f1
/* 0CCDB4 800D2354 C0440024 */  lfs     f2, 0x24(r4)
/* 0CCDB8 800D2358 EC22007A */  fmadds  f1, f2, f1, f0
/* 0CCDBC 800D235C 480000A0 */  b       lbl_800D23FC
lbl_800D2360:
/* 0CCDC0 800D2360 57E007FF */  clrlwi. r0, r31, 0x1f
/* 0CCDC4 800D2364 EC9F07F2 */  fmuls   f4, f31, f31
/* 0CCDC8 800D2368 4182004C */  beq     lbl_800D23B4
/* 0CCDCC 800D236C 3C60800F */  lis     r3, __sincos_poly@ha
/* 0CCDD0 800D2370 38833EB0 */  addi    r4, r3, __sincos_poly@l
/* 0CCDD4 800D2374 C0440000 */  lfs     f2, 0(r4)
/* 0CCDD8 800D2378 3C60800F */  lis     r3, __sincos_on_quadrant@ha
/* 0CCDDC 800D237C C0240008 */  lfs     f1, 8(r4)
/* 0CCDE0 800D2380 38033E90 */  addi    r0, r3, __sincos_on_quadrant@l
/* 0CCDE4 800D2384 C0040010 */  lfs     f0, 0x10(r4)
/* 0CCDE8 800D2388 EC62093A */  fmadds  f3, f2, f4, f1
/* 0CCDEC 800D238C C0440018 */  lfs     f2, 0x18(r4)
/* 0CCDF0 800D2390 C0240020 */  lfs     f1, 0x20(r4)
/* 0CCDF4 800D2394 57E41838 */  slwi    r4, r31, 3
/* 0CCDF8 800D2398 7C602214 */  add     r3, r0, r4
/* 0CCDFC 800D239C EC6400FA */  fmadds  f3, f4, f3, f0
/* 0CCE00 800D23A0 C0030000 */  lfs     f0, 0(r3)
/* 0CCE04 800D23A4 EC4410FA */  fmadds  f2, f4, f3, f2
/* 0CCE08 800D23A8 EC2408BA */  fmadds  f1, f4, f2, f1
/* 0CCE0C 800D23AC EC210032 */  fmuls   f1, f1, f0
/* 0CCE10 800D23B0 4800004C */  b       lbl_800D23FC
lbl_800D23B4:
/* 0CCE14 800D23B4 3C60800F */  lis     r3, __sincos_poly@ha
/* 0CCE18 800D23B8 38833EB0 */  addi    r4, r3, __sincos_poly@l
/* 0CCE1C 800D23BC C0440004 */  lfs     f2, 4(r4)
/* 0CCE20 800D23C0 3C60800F */  lis     r3, __sincos_on_quadrant@ha
/* 0CCE24 800D23C4 C024000C */  lfs     f1, 0xc(r4)
/* 0CCE28 800D23C8 38633E90 */  addi    r3, r3, __sincos_on_quadrant@l
/* 0CCE2C 800D23CC 57E01838 */  slwi    r0, r31, 3
/* 0CCE30 800D23D0 EC62093A */  fmadds  f3, f2, f4, f1
/* 0CCE34 800D23D4 C0040014 */  lfs     f0, 0x14(r4)
/* 0CCE38 800D23D8 C044001C */  lfs     f2, 0x1c(r4)
/* 0CCE3C 800D23DC 7C630214 */  add     r3, r3, r0
/* 0CCE40 800D23E0 C0240024 */  lfs     f1, 0x24(r4)
/* 0CCE44 800D23E4 EC6400FA */  fmadds  f3, f4, f3, f0
/* 0CCE48 800D23E8 C0030004 */  lfs     f0, 4(r3)
/* 0CCE4C 800D23EC EC4410FA */  fmadds  f2, f4, f3, f2
/* 0CCE50 800D23F0 EC2408BA */  fmadds  f1, f4, f2, f1
/* 0CCE54 800D23F4 EC3F0072 */  fmuls   f1, f31, f1
/* 0CCE58 800D23F8 EC210032 */  fmuls   f1, f1, f0
lbl_800D23FC:
/* 0CCE5C 800D23FC 8001002C */  lwz     r0, 0x2c(r1)
/* 0CCE60 800D2400 CBE10020 */  lfd     f31, 0x20(r1)
/* 0CCE64 800D2404 83E1001C */  lwz     r31, 0x1c(r1)
/* 0CCE68 800D2408 7C0803A6 */  mtlr    r0
/* 0CCE6C 800D240C 38210028 */  addi    r1, r1, 0x28
/* 0CCE70 800D2410 4E800020 */  blr     

__sinit_trigf_c:
/* 0CCE74 800D2414 3C60800D */  lis     r3, tmp_float@ha
/* 0CCE78 800D2418 38833700 */  addi    r4, r3, tmp_float@l
/* 0CCE7C 800D241C C0040000 */  lfs     f0, 0(r4)
/* 0CCE80 800D2420 3C60800F */  lis     r3, __four_over_pi_m1@ha
/* 0CCE84 800D2424 D4033E80 */  stfsu   f0, __four_over_pi_m1@l(r3)
/* 0CCE88 800D2428 C0040004 */  lfs     f0, 4(r4)
/* 0CCE8C 800D242C D0030004 */  stfs    f0, 4(r3)
/* 0CCE90 800D2430 C0040008 */  lfs     f0, 8(r4)
/* 0CCE94 800D2434 D0030008 */  stfs    f0, 8(r3)
/* 0CCE98 800D2438 C004000C */  lfs     f0, 0xc(r4)
/* 0CCE9C 800D243C D003000C */  stfs    f0, 0xc(r3)
/* 0CCEA0 800D2440 4E800020 */  blr     

.section .ctors, "a"

.balign 4

/* 000D0020 800D2FA0 0004 */
glabel _ctors
    .long __sinit_trigf_c

.section .rodata, "a"

.balign 8

/* 000D0780 800D3700 0010 */
tmp_float:
    .float 0.25, 0.0232393741608, 1.70555722434e-7, 1.86736494323e-11

.section .data, "wa"

.balign 8

/* 000F0F00 800F3E80 0010 */
__four_over_pi_m1:
    .float 0.0, 0.0, 0.0, 0.0

.section .sdata2, "wa"

.balign 8

/* 000F1EF0 801363F0 0004 */
D_801363F0:
    .float 0.6366197466850281

/* 000F1EF4 801363F4 0004 */
D_801363F4:
    .float 0.5

/* 000F1EF8 801363F8 0004 */
D_801363F8:
    .float 0.0003452669770922512

.balign 8

/* 000F1F00 80136400 0008 */
D_80136400:
    .double 4503601774854144.0
