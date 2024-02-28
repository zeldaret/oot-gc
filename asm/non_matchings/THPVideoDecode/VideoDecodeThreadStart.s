glabel VideoDecodeThreadStart
/* 00DA64 80013004 7C0802A6 */  mflr    r0
/* 00DA68 80013008 90010004 */  stw     r0, 4(r1)
/* 00DA6C 8001300C 9421FFF8 */  stwu    r1, -8(r1)
/* 00DA70 80013010 800D8978 */  lwz     r0, VideoDecodeThreadCreated@sda21(r13)
/* 00DA74 80013014 2C000000 */  cmpwi   r0, 0
/* 00DA78 80013018 41820010 */  beq     lbl_80013028
/* 00DA7C 8001301C 3C608010 */  lis     r3, VideoDecodeThread@ha
/* 00DA80 80013020 3863C5F0 */  addi    r3, r3, VideoDecodeThread@l
/* 00DA84 80013024 4808EBF1 */  bl      OSResumeThread
lbl_80013028:
/* 00DA88 80013028 8001000C */  lwz     r0, 0xc(r1)
/* 00DA8C 8001302C 38210008 */  addi    r1, r1, 8
/* 00DA90 80013030 7C0803A6 */  mtlr    r0
/* 00DA94 80013034 4E800020 */  blr     
