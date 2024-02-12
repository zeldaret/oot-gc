glabel __romLoadUpdate_Complete
/* 06969C 8006EC3C 808D8920 */  lwz     r4, gpSystem@sda21(r13)
/* 0696A0 8006EC40 38000000 */  li      r0, 0
/* 0696A4 8006EC44 38600001 */  li      r3, 1
/* 0696A8 8006EC48 80840030 */  lwz     r4, 0x30(r4)
/* 0696AC 8006EC4C 3C840001 */  addis   r4, r4, 1
/* 0696B0 8006EC50 90040E38 */  stw     r0, 0xe38(r4)
/* 0696B4 8006EC54 4E800020 */  blr     
