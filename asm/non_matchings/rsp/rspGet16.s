glabel rspGet16
/* 06CCD0 80072270 5480A53E */  rlwinm  r0, r4, 0x14, 0x14, 0x1f
/* 06CCD4 80072274 2C000001 */  cmpwi   r0, 1
/* 06CCD8 80072278 41820028 */  beq     lbl_800722A0
/* 06CCDC 8007227C 40800038 */  bge     lbl_800722B4
/* 06CCE0 80072280 2C000000 */  cmpwi   r0, 0
/* 06CCE4 80072284 40800008 */  bge     lbl_8007228C
/* 06CCE8 80072288 4800002C */  b       lbl_800722B4
lbl_8007228C:
/* 06CCEC 8007228C 806338EC */  lwz     r3, 0x38ec(r3)
/* 06CCF0 80072290 5480053C */  rlwinm  r0, r4, 0, 0x14, 0x1e
/* 06CCF4 80072294 7C0302AE */  lhax    r0, r3, r0
/* 06CCF8 80072298 B0050000 */  sth     r0, 0(r5)
/* 06CCFC 8007229C 48000020 */  b       lbl_800722BC
lbl_800722A0:
/* 06CD00 800722A0 806338F0 */  lwz     r3, 0x38f0(r3)
/* 06CD04 800722A4 5480053C */  rlwinm  r0, r4, 0, 0x14, 0x1e
/* 06CD08 800722A8 7C0302AE */  lhax    r0, r3, r0
/* 06CD0C 800722AC B0050000 */  sth     r0, 0(r5)
/* 06CD10 800722B0 4800000C */  b       lbl_800722BC
lbl_800722B4:
/* 06CD14 800722B4 38600000 */  li      r3, 0
/* 06CD18 800722B8 4E800020 */  blr     
lbl_800722BC:
/* 06CD1C 800722BC 38600001 */  li      r3, 1
/* 06CD20 800722C0 4E800020 */  blr     
