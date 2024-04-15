glabel frameSetFill
/* 01AD30 800202D0 2C040000 */  cmpwi   r4, 0
/* 01AD34 800202D4 41820014 */  beq     lbl_800202E8
/* 01AD38 800202D8 8003008C */  lwz     r0, 0x8c(r3)
/* 01AD3C 800202DC 64000002 */  oris    r0, r0, 2
/* 01AD40 800202E0 9003008C */  stw     r0, 0x8c(r3)
/* 01AD44 800202E4 48000010 */  b       lbl_800202F4
lbl_800202E8:
/* 01AD48 800202E8 8003008C */  lwz     r0, 0x8c(r3)
/* 01AD4C 800202EC 540003DA */  rlwinm  r0, r0, 0, 0xf, 0xd
/* 01AD50 800202F0 9003008C */  stw     r0, 0x8c(r3)
lbl_800202F4:
/* 01AD54 800202F4 38600001 */  li      r3, 1
/* 01AD58 800202F8 4E800020 */  blr     
