glabel VideoDecode
/* 00DCA8 80013248 7C0802A6 */  mflr    r0
/* 00DCAC 8001324C 3C808010 */  lis     r4, ActivePlayer@ha
/* 00DCB0 80013250 90010004 */  stw     r0, 4(r1)
/* 00DCB4 80013254 9421FFC8 */  stwu    r1, -0x38(r1)
/* 00DCB8 80013258 BEE10014 */  stmw    r23, 0x14(r1)
/* 00DCBC 8001325C 3BE49C80 */  addi    r31, r4, ActivePlayer@l
/* 00DCC0 80013260 7C781B78 */  mr      r24, r3
/* 00DCC4 80013264 3BBF006C */  addi    r29, r31, 0x6c
/* 00DCC8 80013268 801F006C */  lwz     r0, 0x6c(r31)
/* 00DCCC 8001326C 80830000 */  lwz     r4, 0(r3)
/* 00DCD0 80013270 5403103A */  slwi    r3, r0, 2
/* 00DCD4 80013274 3B230008 */  addi    r25, r3, 8
/* 00DCD8 80013278 3B440008 */  addi    r26, r4, 8
/* 00DCDC 8001327C 7F24CA14 */  add     r25, r4, r25
/* 00DCE0 80013280 480000E9 */  bl      PopFreeTextureSet
/* 00DCE4 80013284 3C808010 */  lis     r4, VideoDecodeThread@ha
/* 00DCE8 80013288 3B830000 */  addi    r28, r3, 0
/* 00DCEC 8001328C 3BDF0000 */  addi    r30, r31, 0
/* 00DCF0 80013290 3AE4C5F0 */  addi    r23, r4, VideoDecodeThread@l
/* 00DCF4 80013294 3B600000 */  li      r27, 0
/* 00DCF8 80013298 48000094 */  b       lbl_8001332C
lbl_8001329C:
/* 00DCFC 8001329C 881E0070 */  lbz     r0, 0x70(r30)
/* 00DD00 800132A0 2C000000 */  cmpwi   r0, 0
/* 00DD04 800132A4 41820008 */  beq     lbl_800132AC
/* 00DD08 800132A8 48000070 */  b       lbl_80013318
lbl_800132AC:
/* 00DD0C 800132AC 809C0000 */  lwz     r4, 0(r28)
/* 00DD10 800132B0 7F23CB78 */  mr      r3, r25
/* 00DD14 800132B4 80BC0004 */  lwz     r5, 4(r28)
/* 00DD18 800132B8 80DC0008 */  lwz     r6, 8(r28)
/* 00DD1C 800132BC 80FF009C */  lwz     r7, 0x9c(r31)
/* 00DD20 800132C0 480AE205 */  bl      THPVideoDecode
/* 00DD24 800132C4 2C030000 */  cmpwi   r3, 0
/* 00DD28 800132C8 907F00AC */  stw     r3, 0xac(r31)
/* 00DD2C 800132CC 41820028 */  beq     lbl_800132F4
/* 00DD30 800132D0 800D897C */  lwz     r0, First@sda21(r13)
/* 00DD34 800132D4 2C000000 */  cmpwi   r0, 0
/* 00DD38 800132D8 41820014 */  beq     lbl_800132EC
/* 00DD3C 800132DC 38600000 */  li      r3, 0
/* 00DD40 800132E0 4BFFCD11 */  bl      PrepareReady
/* 00DD44 800132E4 38000000 */  li      r0, 0
/* 00DD48 800132E8 900D897C */  stw     r0, First@sda21(r13)
lbl_800132EC:
/* 00DD4C 800132EC 7EE3BB78 */  mr      r3, r23
/* 00DD50 800132F0 4808EBAD */  bl      OSSuspendThread
lbl_800132F4:
/* 00DD54 800132F4 80180004 */  lwz     r0, 4(r24)
/* 00DD58 800132F8 7F83E378 */  mr      r3, r28
/* 00DD5C 800132FC 901C000C */  stw     r0, 0xc(r28)
/* 00DD60 80013300 48000111 */  bl      PushDecodedTextureSet
/* 00DD64 80013304 4808B9F9 */  bl      OSDisableInterrupts
/* 00DD68 80013308 809F00D8 */  lwz     r4, 0xd8(r31)
/* 00DD6C 8001330C 38040001 */  addi    r0, r4, 1
/* 00DD70 80013310 901F00D8 */  stw     r0, 0xd8(r31)
/* 00DD74 80013314 4808BA11 */  bl      OSRestoreInterrupts
lbl_80013318:
/* 00DD78 80013318 801A0000 */  lwz     r0, 0(r26)
/* 00DD7C 8001331C 3B7B0001 */  addi    r27, r27, 1
/* 00DD80 80013320 3B5A0004 */  addi    r26, r26, 4
/* 00DD84 80013324 7F390214 */  add     r25, r25, r0
/* 00DD88 80013328 3BDE0001 */  addi    r30, r30, 1
lbl_8001332C:
/* 00DD8C 8001332C 801D0000 */  lwz     r0, 0(r29)
/* 00DD90 80013330 7C1B0040 */  cmplw   r27, r0
/* 00DD94 80013334 4180FF68 */  blt     lbl_8001329C
/* 00DD98 80013338 800D897C */  lwz     r0, First@sda21(r13)
/* 00DD9C 8001333C 2C000000 */  cmpwi   r0, 0
/* 00DDA0 80013340 41820014 */  beq     lbl_80013354
/* 00DDA4 80013344 38600001 */  li      r3, 1
/* 00DDA8 80013348 4BFFCCA9 */  bl      PrepareReady
/* 00DDAC 8001334C 38000000 */  li      r0, 0
/* 00DDB0 80013350 900D897C */  stw     r0, First@sda21(r13)
lbl_80013354:
/* 00DDB4 80013354 BAE10014 */  lmw     r23, 0x14(r1)
/* 00DDB8 80013358 8001003C */  lwz     r0, 0x3c(r1)
/* 00DDBC 8001335C 38210038 */  addi    r1, r1, 0x38
/* 00DDC0 80013360 7C0803A6 */  mtlr    r0
/* 00DDC4 80013364 4E800020 */  blr     
