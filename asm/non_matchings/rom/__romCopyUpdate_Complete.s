glabel __romCopyUpdate_Complete
/* 069520 8006EAC0 808D8920 */  lwz     r4, gpSystem@sda21(r13)
/* 069524 8006EAC4 38000000 */  li      r0, 0
/* 069528 8006EAC8 38600001 */  li      r3, 1
/* 06952C 8006EACC 80840030 */  lwz     r4, 0x30(r4)
/* 069530 8006EAD0 3C840001 */  addis   r4, r4, 1
/* 069534 8006EAD4 90040E24 */  stw     r0, 0xe24(r4)
/* 069538 8006EAD8 4E800020 */  blr     
