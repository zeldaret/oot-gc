# mtxvec.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel PSMTXMultVec
/* 0A2A24 800A7FC4 E0040000 */  psq_l   f0, 0(r4), 0, qr0
/* 0A2A28 800A7FC8 E0430000 */  psq_l   f2, 0(r3), 0, qr0
/* 0A2A2C 800A7FCC E0248008 */  psq_l   f1, 8(r4), 1, qr0
/* 0A2A30 800A7FD0 10820032 */  ps_mul  f4, f2, f0
/* 0A2A34 800A7FD4 E0630008 */  psq_l   f3, 8(r3), 0, qr0
/* 0A2A38 800A7FD8 10A3207A */  ps_madd f5, f3, f1, f4
/* 0A2A3C 800A7FDC E1030010 */  psq_l   f8, 16(r3), 0, qr0
/* 0A2A40 800A7FE0 10C52994 */  ps_sum0 f6, f5, f6, f5
/* 0A2A44 800A7FE4 E1230018 */  psq_l   f9, 24(r3), 0, qr0
/* 0A2A48 800A7FE8 11480032 */  ps_mul  f10, f8, f0
/* 0A2A4C 800A7FEC F0C58000 */  psq_st  f6, 0(r5), 1, qr0
/* 0A2A50 800A7FF0 1169507A */  ps_madd f11, f9, f1, f10
/* 0A2A54 800A7FF4 E0430020 */  psq_l   f2, 32(r3), 0, qr0
/* 0A2A58 800A7FF8 118B5B14 */  ps_sum0 f12, f11, f12, f11
/* 0A2A5C 800A7FFC E0630028 */  psq_l   f3, 40(r3), 0, qr0
/* 0A2A60 800A8000 10820032 */  ps_mul  f4, f2, f0
/* 0A2A64 800A8004 F1858004 */  psq_st  f12, 4(r5), 1, qr0
/* 0A2A68 800A8008 10A3207A */  ps_madd f5, f3, f1, f4
/* 0A2A6C 800A800C 10C52994 */  ps_sum0 f6, f5, f6, f5
/* 0A2A70 800A8010 F0C58008 */  psq_st  f6, 8(r5), 1, qr0
/* 0A2A74 800A8014 4E800020 */  blr     


