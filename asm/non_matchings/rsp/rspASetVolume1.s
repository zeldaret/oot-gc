glabel rspASetVolume1
/* 0837D4 80088D74 54A08739 */  rlwinm. r0, r5, 0x10, 0x1c, 0x1c
/* 0837D8 80088D78 54A6863E */  rlwinm  r6, r5, 0x10, 0x18, 0x1f
/* 0837DC 80088D7C 54A5043E */  clrlwi  r5, r5, 0x10
/* 0837E0 80088D80 5487843E */  srwi    r7, r4, 0x10
/* 0837E4 80088D84 5488043E */  clrlwi  r8, r4, 0x10
/* 0837E8 80088D88 41820018 */  beq     lbl_80088DA0
/* 0837EC 80088D8C 80833294 */  lwz     r4, 0x3294(r3)
/* 0837F0 80088D90 B0A4037C */  sth     r5, 0x37c(r4)
/* 0837F4 80088D94 80633294 */  lwz     r3, 0x3294(r3)
/* 0837F8 80088D98 B103037E */  sth     r8, 0x37e(r3)
/* 0837FC 80088D9C 48000068 */  b       lbl_80088E04
lbl_80088DA0:
/* 083800 80088DA0 54C0077B */  rlwinm. r0, r6, 0, 0x1d, 0x1d
/* 083804 80088DA4 41820024 */  beq     lbl_80088DC8
/* 083808 80088DA8 54C007BD */  rlwinm. r0, r6, 0, 0x1e, 0x1e
/* 08380C 80088DAC 41820010 */  beq     lbl_80088DBC
/* 083810 80088DB0 80633294 */  lwz     r3, 0x3294(r3)
/* 083814 80088DB4 B0A30366 */  sth     r5, 0x366(r3)
/* 083818 80088DB8 4800004C */  b       lbl_80088E04
lbl_80088DBC:
/* 08381C 80088DBC 80633294 */  lwz     r3, 0x3294(r3)
/* 083820 80088DC0 B0A30368 */  sth     r5, 0x368(r3)
/* 083824 80088DC4 48000040 */  b       lbl_80088E04
lbl_80088DC8:
/* 083828 80088DC8 54C007BD */  rlwinm. r0, r6, 0, 0x1e, 0x1e
/* 08382C 80088DCC 41820020 */  beq     lbl_80088DEC
/* 083830 80088DD0 80833294 */  lwz     r4, 0x3294(r3)
/* 083834 80088DD4 B0A40370 */  sth     r5, 0x370(r4)
/* 083838 80088DD8 80833294 */  lwz     r4, 0x3294(r3)
/* 08383C 80088DDC B0E40372 */  sth     r7, 0x372(r4)
/* 083840 80088DE0 80633294 */  lwz     r3, 0x3294(r3)
/* 083844 80088DE4 B1030374 */  sth     r8, 0x374(r3)
/* 083848 80088DE8 4800001C */  b       lbl_80088E04
lbl_80088DEC:
/* 08384C 80088DEC 80833294 */  lwz     r4, 0x3294(r3)
/* 083850 80088DF0 B0A40376 */  sth     r5, 0x376(r4)
/* 083854 80088DF4 80833294 */  lwz     r4, 0x3294(r3)
/* 083858 80088DF8 B0E40378 */  sth     r7, 0x378(r4)
/* 08385C 80088DFC 80633294 */  lwz     r3, 0x3294(r3)
/* 083860 80088E00 B103037A */  sth     r8, 0x37a(r3)
lbl_80088E04:
/* 083864 80088E04 38600001 */  li      r3, 1
/* 083868 80088E08 4E800020 */  blr     
