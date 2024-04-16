glabel PSMTX44MultVecNoW
/* 017DAC 8001D34C E0040000 */  psq_l   f0, 0(r4), 0, qr0
/* 017DB0 8001D350 E0248008 */  psq_l   f1, 8(r4), 1, qr0
/* 017DB4 8001D354 E0830000 */  psq_l   f4, 0(r3), 0, qr0
/* 017DB8 8001D358 E0A30008 */  psq_l   f5, 8(r3), 0, qr0
/* 017DBC 8001D35C E0C30010 */  psq_l   f6, 16(r3), 0, qr0
/* 017DC0 8001D360 E0E30018 */  psq_l   f7, 24(r3), 0, qr0
/* 017DC4 8001D364 E1030020 */  psq_l   f8, 32(r3), 0, qr0
/* 017DC8 8001D368 E1230028 */  psq_l   f9, 40(r3), 0, qr0
/* 017DCC 8001D36C 10800132 */  ps_mul  f4, f0, f4
/* 017DD0 8001D370 1041217A */  ps_madd f2, f1, f5, f4
/* 017DD4 8001D374 10C001B2 */  ps_mul  f6, f0, f6
/* 017DD8 8001D378 106131FA */  ps_madd f3, f1, f7, f6
/* 017DDC 8001D37C 11000232 */  ps_mul  f8, f0, f8
/* 017DE0 8001D380 10421094 */  ps_sum0 f2, f2, f2, f2
/* 017DE4 8001D384 1121427A */  ps_madd f9, f1, f9, f8
/* 017DE8 8001D388 10431896 */  ps_sum1 f2, f3, f2, f3
/* 017DEC 8001D38C 10694A54 */  ps_sum0 f3, f9, f9, f9
/* 017DF0 8001D390 F0450000 */  psq_st  f2, 0(r5), 0, qr0
/* 017DF4 8001D394 F0658008 */  psq_st  f3, 8(r5), 1, qr0
/* 017DF8 8001D398 4E800020 */  blr     
