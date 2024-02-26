glabel movieDrawErrorMessage
/* 00CBD0 80012170 7C0802A6 */  mflr    r0
/* 00CBD4 80012174 28030006 */  cmplwi  r3, 6
/* 00CBD8 80012178 90010004 */  stw     r0, 4(r1)
/* 00CBDC 8001217C 9421FFF8 */  stwu    r1, -8(r1)
/* 00CBE0 80012180 418101A0 */  bgt     lbl_80012320
/* 00CBE4 80012184 3C80800F */  lis     r4, jtbl_800EA500@ha
/* 00CBE8 80012188 3884A500 */  addi    r4, r4, jtbl_800EA500@l
/* 00CBEC 8001218C 5460103A */  slwi    r0, r3, 2
/* 00CBF0 80012190 7C04002E */  lwzx    r0, r4, r0
/* 00CBF4 80012194 7C0903A6 */  mtctr   r0
/* 00CBF8 80012198 4E800420 */  bctr    
glabel lbl_8001219C
/* 00CBFC 8001219C 3C60800E */  lis     r3, gcoverOpen@ha
/* 00CC00 800121A0 3863B800 */  addi    r3, r3, gcoverOpen@l
/* 00CC04 800121A4 80830008 */  lwz     r4, 8(r3)
/* 00CC08 800121A8 80A40000 */  lwz     r5, 0(r4)
/* 00CC0C 800121AC A0850002 */  lhz     r4, 2(r5)
/* 00CC10 800121B0 A0050000 */  lhz     r0, 0(r5)
/* 00CC14 800121B4 7C840E70 */  srawi   r4, r4, 1
/* 00CC18 800121B8 7C840194 */  addze   r4, r4
/* 00CC1C 800121BC 208400A0 */  subfic  r4, r4, 0xa0
/* 00CC20 800121C0 7C000E70 */  srawi   r0, r0, 1
/* 00CC24 800121C4 7C000194 */  addze   r0, r0
/* 00CC28 800121C8 20A00078 */  subfic  r5, r0, 0x78
/* 00CC2C 800121CC 48000169 */  bl      movieDrawImage
/* 00CC30 800121D0 48000150 */  b       lbl_80012320
glabel lbl_800121D4
/* 00CC34 800121D4 3C60800E */  lis     r3, gwrongDisk@ha
/* 00CC38 800121D8 38635760 */  addi    r3, r3, gwrongDisk@l
/* 00CC3C 800121DC 80830008 */  lwz     r4, 8(r3)
/* 00CC40 800121E0 80A40000 */  lwz     r5, 0(r4)
/* 00CC44 800121E4 A0850002 */  lhz     r4, 2(r5)
/* 00CC48 800121E8 A0050000 */  lhz     r0, 0(r5)
/* 00CC4C 800121EC 7C840E70 */  srawi   r4, r4, 1
/* 00CC50 800121F0 7C840194 */  addze   r4, r4
/* 00CC54 800121F4 208400A0 */  subfic  r4, r4, 0xa0
/* 00CC58 800121F8 7C000E70 */  srawi   r0, r0, 1
/* 00CC5C 800121FC 7C000194 */  addze   r0, r0
/* 00CC60 80012200 20A00078 */  subfic  r5, r0, 0x78
/* 00CC64 80012204 48000131 */  bl      movieDrawImage
/* 00CC68 80012208 48000118 */  b       lbl_80012320
glabel lbl_8001220C
/* 00CC6C 8001220C 3C60800E */  lis     r3, greadingDisk@ha
/* 00CC70 80012210 38637680 */  addi    r3, r3, greadingDisk@l
/* 00CC74 80012214 80830008 */  lwz     r4, 8(r3)
/* 00CC78 80012218 80A40000 */  lwz     r5, 0(r4)
/* 00CC7C 8001221C A0850002 */  lhz     r4, 2(r5)
/* 00CC80 80012220 A0050000 */  lhz     r0, 0(r5)
/* 00CC84 80012224 7C840E70 */  srawi   r4, r4, 1
/* 00CC88 80012228 7C840194 */  addze   r4, r4
/* 00CC8C 8001222C 208400A0 */  subfic  r4, r4, 0xa0
/* 00CC90 80012230 7C000E70 */  srawi   r0, r0, 1
/* 00CC94 80012234 7C000194 */  addze   r0, r0
/* 00CC98 80012238 20A00078 */  subfic  r5, r0, 0x78
/* 00CC9C 8001223C 480000F9 */  bl      movieDrawImage
/* 00CCA0 80012240 480000E0 */  b       lbl_80012320
glabel lbl_80012244
/* 00CCA4 80012244 3C60800E */  lis     r3, gretryErr@ha
/* 00CCA8 80012248 38630000 */  addi    r3, r3, gretryErr@l
/* 00CCAC 8001224C 80830008 */  lwz     r4, 8(r3)
/* 00CCB0 80012250 80A40000 */  lwz     r5, 0(r4)
/* 00CCB4 80012254 A0850002 */  lhz     r4, 2(r5)
/* 00CCB8 80012258 A0050000 */  lhz     r0, 0(r5)
/* 00CCBC 8001225C 7C840E70 */  srawi   r4, r4, 1
/* 00CCC0 80012260 7C840194 */  addze   r4, r4
/* 00CCC4 80012264 208400A0 */  subfic  r4, r4, 0xa0
/* 00CCC8 80012268 7C000E70 */  srawi   r0, r0, 1
/* 00CCCC 8001226C 7C000194 */  addze   r0, r0
/* 00CCD0 80012270 20A00078 */  subfic  r5, r0, 0x78
/* 00CCD4 80012274 480000C1 */  bl      movieDrawImage
/* 00CCD8 80012278 480000A8 */  b       lbl_80012320
glabel lbl_8001227C
/* 00CCDC 8001227C 3C60800E */  lis     r3, gfatalErr@ha
/* 00CCE0 80012280 38632460 */  addi    r3, r3, gfatalErr@l
/* 00CCE4 80012284 80830008 */  lwz     r4, 8(r3)
/* 00CCE8 80012288 80A40000 */  lwz     r5, 0(r4)
/* 00CCEC 8001228C A0850002 */  lhz     r4, 2(r5)
/* 00CCF0 80012290 A0050000 */  lhz     r0, 0(r5)
/* 00CCF4 80012294 7C840E70 */  srawi   r4, r4, 1
/* 00CCF8 80012298 7C840194 */  addze   r4, r4
/* 00CCFC 8001229C 208400A0 */  subfic  r4, r4, 0xa0
/* 00CD00 800122A0 7C000E70 */  srawi   r0, r0, 1
/* 00CD04 800122A4 7C000194 */  addze   r0, r0
/* 00CD08 800122A8 20A00078 */  subfic  r5, r0, 0x78
/* 00CD0C 800122AC 48000089 */  bl      movieDrawImage
/* 00CD10 800122B0 48000070 */  b       lbl_80012320
glabel lbl_800122B4
/* 00CD14 800122B4 3C60800E */  lis     r3, gnoDisk@ha
/* 00CD18 800122B8 3863E0E0 */  addi    r3, r3, gnoDisk@l
/* 00CD1C 800122BC 80830008 */  lwz     r4, 8(r3)
/* 00CD20 800122C0 80A40000 */  lwz     r5, 0(r4)
/* 00CD24 800122C4 A0850002 */  lhz     r4, 2(r5)
/* 00CD28 800122C8 A0050000 */  lhz     r0, 0(r5)
/* 00CD2C 800122CC 7C840E70 */  srawi   r4, r4, 1
/* 00CD30 800122D0 7C840194 */  addze   r4, r4
/* 00CD34 800122D4 208400A0 */  subfic  r4, r4, 0xa0
/* 00CD38 800122D8 7C000E70 */  srawi   r0, r0, 1
/* 00CD3C 800122DC 7C000194 */  addze   r0, r0
/* 00CD40 800122E0 20A00078 */  subfic  r5, r0, 0x78
/* 00CD44 800122E4 48000051 */  bl      movieDrawImage
/* 00CD48 800122E8 48000038 */  b       lbl_80012320
glabel lbl_800122EC
/* 00CD4C 800122EC 3C60800E */  lis     r3, gfatalErr@ha
/* 00CD50 800122F0 38632460 */  addi    r3, r3, gfatalErr@l
/* 00CD54 800122F4 80830008 */  lwz     r4, 8(r3)
/* 00CD58 800122F8 80A40000 */  lwz     r5, 0(r4)
/* 00CD5C 800122FC A0850002 */  lhz     r4, 2(r5)
/* 00CD60 80012300 A0050000 */  lhz     r0, 0(r5)
/* 00CD64 80012304 7C840E70 */  srawi   r4, r4, 1
/* 00CD68 80012308 7C840194 */  addze   r4, r4
/* 00CD6C 8001230C 208400A0 */  subfic  r4, r4, 0xa0
/* 00CD70 80012310 7C000E70 */  srawi   r0, r0, 1
/* 00CD74 80012314 7C000194 */  addze   r0, r0
/* 00CD78 80012318 20A00078 */  subfic  r5, r0, 0x78
/* 00CD7C 8001231C 48000019 */  bl      movieDrawImage
lbl_80012320:
/* 00CD80 80012320 8001000C */  lwz     r0, 0xc(r1)
/* 00CD84 80012324 38600001 */  li      r3, 1
/* 00CD88 80012328 38210008 */  addi    r1, r1, 8
/* 00CD8C 8001232C 7C0803A6 */  mtlr    r0
/* 00CD90 80012330 4E800020 */  blr     
