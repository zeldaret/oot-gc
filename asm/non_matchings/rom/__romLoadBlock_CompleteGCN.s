glabel __romLoadBlock_CompleteGCN
/* 06A130 8006F6D0 808D8920 */  lwz     r4, gpSystem@sda21(r13)
/* 06A134 8006F6D4 38000001 */  li      r0, 1
/* 06A138 8006F6D8 80840030 */  lwz     r4, 0x30(r4)
/* 06A13C 8006F6DC 3C840001 */  addis   r4, r4, 1
/* 06A140 8006F6E0 90640E40 */  stw     r3, 0xe40(r4)
/* 06A144 8006F6E4 90040E3C */  stw     r0, 0xe3c(r4)
/* 06A148 8006F6E8 4E800020 */  blr     
