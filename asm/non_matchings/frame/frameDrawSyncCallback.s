glabel frameDrawSyncCallback
/* 026DC0 8002C360 5460043E */  clrlwi  r0, r3, 0x10
/* 026DC4 8002C364 28007D00 */  cmplwi  r0, 0x7d00
/* 026DC8 8002C368 4082000C */  bne     lbl_8002C374
/* 026DCC 8002C36C 38000001 */  li      r0, 1
/* 026DD0 8002C370 900D89C4 */  stw     r0, sCopyFrameSyncReceived@sda21(r13)
lbl_8002C374:
/* 026DD4 8002C374 4E800020 */  blr     
