glabel AudioDecodeThreadStart
/* 00B8DC 80010E7C 7C0802A6 */  mflr    r0
/* 00B8E0 80010E80 90010004 */  stw     r0, 4(r1)
/* 00B8E4 80010E84 9421FFF8 */  stwu    r1, -8(r1)
/* 00B8E8 80010E88 800D8958 */  lwz     r0, AudioDecodeThreadCreated@sda21(r13)
/* 00B8EC 80010E8C 2C000000 */  cmpwi   r0, 0
/* 00B8F0 80010E90 41820010 */  beq     lbl_80010EA0
/* 00B8F4 80010E94 3C608010 */  lis     r3, AudioDecodeThread@ha
/* 00B8F8 80010E98 38639E50 */  addi    r3, r3, AudioDecodeThread@l
/* 00B8FC 80010E9C 48090D79 */  bl      OSResumeThread
lbl_80010EA0:
/* 00B900 80010EA0 8001000C */  lwz     r0, 0xc(r1)
/* 00B904 80010EA4 38210008 */  addi    r1, r1, 8
/* 00B908 80010EA8 7C0803A6 */  mtlr    r0
/* 00B90C 80010EAC 4E800020 */  blr     
