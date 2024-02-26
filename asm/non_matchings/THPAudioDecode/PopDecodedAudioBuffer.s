glabel PopDecodedAudioBuffer
/* 00BB24 800110C4 7C0802A6 */  mflr    r0
/* 00BB28 800110C8 3C808010 */  lis     r4, DecodedAudioBufferQueue@ha
/* 00BB2C 800110CC 90010004 */  stw     r0, 4(r1)
/* 00BB30 800110D0 38A30000 */  addi    r5, r3, 0
/* 00BB34 800110D4 3864B188 */  addi    r3, r4, DecodedAudioBufferQueue@l
/* 00BB38 800110D8 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00BB3C 800110DC 3881000C */  addi    r4, r1, 0xc
/* 00BB40 800110E0 4808E5C9 */  bl      OSReceiveMessage
/* 00BB44 800110E4 2C030001 */  cmpwi   r3, 1
/* 00BB48 800110E8 4082000C */  bne     lbl_800110F4
/* 00BB4C 800110EC 8061000C */  lwz     r3, 0xc(r1)
/* 00BB50 800110F0 48000008 */  b       lbl_800110F8
lbl_800110F4:
/* 00BB54 800110F4 38600000 */  li      r3, 0
lbl_800110F8:
/* 00BB58 800110F8 80010014 */  lwz     r0, 0x14(r1)
/* 00BB5C 800110FC 38210010 */  addi    r1, r1, 0x10
/* 00BB60 80011100 7C0803A6 */  mtlr    r0
/* 00BB64 80011104 4E800020 */  blr     
