glabel PopDecodedTextureSet
/* 00DE2C 800133CC 7C0802A6 */  mflr    r0
/* 00DE30 800133D0 3C808010 */  lis     r4, DecodedTextureSetQueue@ha
/* 00DE34 800133D4 90010004 */  stw     r0, 4(r1)
/* 00DE38 800133D8 38A30000 */  addi    r5, r3, 0
/* 00DE3C 800133DC 3864D928 */  addi    r3, r4, DecodedTextureSetQueue@l
/* 00DE40 800133E0 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00DE44 800133E4 3881000C */  addi    r4, r1, 0xc
/* 00DE48 800133E8 4808C2C1 */  bl      OSReceiveMessage
/* 00DE4C 800133EC 2C030001 */  cmpwi   r3, 1
/* 00DE50 800133F0 4082000C */  bne     lbl_800133FC
/* 00DE54 800133F4 8061000C */  lwz     r3, 0xc(r1)
/* 00DE58 800133F8 48000008 */  b       lbl_80013400
lbl_800133FC:
/* 00DE5C 800133FC 38600000 */  li      r3, 0
lbl_80013400:
/* 00DE60 80013400 80010014 */  lwz     r0, 0x14(r1)
/* 00DE64 80013404 38210010 */  addi    r1, r1, 0x10
/* 00DE68 80013408 7C0803A6 */  mtlr    r0
/* 00DE6C 8001340C 4E800020 */  blr     
