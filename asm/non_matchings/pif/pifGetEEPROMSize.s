glabel pifGetEEPROMSize
/* 067334 8006C8D4 8003002C */  lwz     r0, 0x2c(r3)
/* 067338 8006C8D8 2C000006 */  cmpwi   r0, 6
/* 06733C 8006C8DC 40820010 */  bne     lbl_8006C8EC
/* 067340 8006C8E0 38000200 */  li      r0, 0x200
/* 067344 8006C8E4 90040000 */  stw     r0, 0(r4)
/* 067348 8006C8E8 48000028 */  b       lbl_8006C910
lbl_8006C8EC:
/* 06734C 8006C8EC 2C000007 */  cmpwi   r0, 7
/* 067350 8006C8F0 40820010 */  bne     lbl_8006C900
/* 067354 8006C8F4 38000800 */  li      r0, 0x800
/* 067358 8006C8F8 90040000 */  stw     r0, 0(r4)
/* 06735C 8006C8FC 48000014 */  b       lbl_8006C910
lbl_8006C900:
/* 067360 8006C900 38000000 */  li      r0, 0
/* 067364 8006C904 90040000 */  stw     r0, 0(r4)
/* 067368 8006C908 38600000 */  li      r3, 0
/* 06736C 8006C90C 4E800020 */  blr     
lbl_8006C910:
/* 067370 8006C910 38600001 */  li      r3, 1
/* 067374 8006C914 4E800020 */  blr     
