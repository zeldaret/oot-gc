glabel CreateVideoDecodeThread
/* 00D980 80012F20 7C0802A6 */  mflr    r0
/* 00D984 80012F24 7C852379 */  or.     r5, r4, r4
/* 00D988 80012F28 90010004 */  stw     r0, 4(r1)
/* 00D98C 80012F2C 3C808010 */  lis     r4, VideoDecodeThread@ha
/* 00D990 80012F30 39030000 */  addi    r8, r3, 0
/* 00D994 80012F34 9421FFE8 */  stwu    r1, -0x18(r1)
/* 00D998 80012F38 93E10014 */  stw     r31, 0x14(r1)
/* 00D99C 80012F3C 3BE4C5F0 */  addi    r31, r4, VideoDecodeThread@l
/* 00D9A0 80012F40 41820040 */  beq     lbl_80012F80
/* 00D9A4 80012F44 3C608001 */  lis     r3, VideoDecoderForOnMemory@ha
/* 00D9A8 80012F48 38833114 */  addi    r4, r3, VideoDecoderForOnMemory@l
/* 00D9AC 80012F4C 387F0000 */  addi    r3, r31, 0
/* 00D9B0 80012F50 38DF1318 */  addi    r6, r31, 0x1318
/* 00D9B4 80012F54 38E01000 */  li      r7, 0x1000
/* 00D9B8 80012F58 39200001 */  li      r9, 1
/* 00D9BC 80012F5C 4808E831 */  bl      OSCreateThread
/* 00D9C0 80012F60 2C030000 */  cmpwi   r3, 0
/* 00D9C4 80012F64 4082005C */  bne     lbl_80012FC0
/* 00D9C8 80012F68 3C60800F */  lis     r3, D_800EA520@ha
/* 00D9CC 80012F6C 4CC63182 */  crclr   6
/* 00D9D0 80012F70 3863A520 */  addi    r3, r3, D_800EA520@l
/* 00D9D4 80012F74 4808B685 */  bl      OSReport
/* 00D9D8 80012F78 38600000 */  li      r3, 0
/* 00D9DC 80012F7C 48000074 */  b       lbl_80012FF0
lbl_80012F80:
/* 00D9E0 80012F80 3C608001 */  lis     r3, VideoDecoder@ha
/* 00D9E4 80012F84 38833038 */  addi    r4, r3, VideoDecoder@l
/* 00D9E8 80012F88 387F0000 */  addi    r3, r31, 0
/* 00D9EC 80012F8C 38DF1318 */  addi    r6, r31, 0x1318
/* 00D9F0 80012F90 38A00000 */  li      r5, 0
/* 00D9F4 80012F94 38E01000 */  li      r7, 0x1000
/* 00D9F8 80012F98 39200001 */  li      r9, 1
/* 00D9FC 80012F9C 4808E7F1 */  bl      OSCreateThread
/* 00DA00 80012FA0 2C030000 */  cmpwi   r3, 0
/* 00DA04 80012FA4 4082001C */  bne     lbl_80012FC0
/* 00DA08 80012FA8 3C60800F */  lis     r3, D_800EA520@ha
/* 00DA0C 80012FAC 4CC63182 */  crclr   6
/* 00DA10 80012FB0 3863A520 */  addi    r3, r3, D_800EA520@l
/* 00DA14 80012FB4 4808B645 */  bl      OSReport
/* 00DA18 80012FB8 38600000 */  li      r3, 0
/* 00DA1C 80012FBC 48000034 */  b       lbl_80012FF0
lbl_80012FC0:
/* 00DA20 80012FC0 387F1318 */  addi    r3, r31, 0x1318
/* 00DA24 80012FC4 389F1358 */  addi    r4, r31, 0x1358
/* 00DA28 80012FC8 38A00003 */  li      r5, 3
/* 00DA2C 80012FCC 4808C5B5 */  bl      OSInitMessageQueue
/* 00DA30 80012FD0 387F1338 */  addi    r3, r31, 0x1338
/* 00DA34 80012FD4 389F1364 */  addi    r4, r31, 0x1364
/* 00DA38 80012FD8 38A00003 */  li      r5, 3
/* 00DA3C 80012FDC 4808C5A5 */  bl      OSInitMessageQueue
/* 00DA40 80012FE0 38000001 */  li      r0, 1
/* 00DA44 80012FE4 900D8978 */  stw     r0, VideoDecodeThreadCreated@sda21(r13)
/* 00DA48 80012FE8 38600001 */  li      r3, 1
/* 00DA4C 80012FEC 900D897C */  stw     r0, First@sda21(r13)
lbl_80012FF0:
/* 00DA50 80012FF0 8001001C */  lwz     r0, 0x1c(r1)
/* 00DA54 80012FF4 83E10014 */  lwz     r31, 0x14(r1)
/* 00DA58 80012FF8 38210018 */  addi    r1, r1, 0x18
/* 00DA5C 80012FFC 7C0803A6 */  mtlr    r0
/* 00DA60 80013000 4E800020 */  blr     
