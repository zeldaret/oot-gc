# THPAudioDecode.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel CreateAudioDecodeThread
/* 00B7FC 80010D9C 7C0802A6 */  mflr    r0
/* 00B800 80010DA0 7C852379 */  or.     r5, r4, r4
/* 00B804 80010DA4 90010004 */  stw     r0, 4(r1)
/* 00B808 80010DA8 3C808010 */  lis     r4, AudioDecodeThread@ha
/* 00B80C 80010DAC 39030000 */  addi    r8, r3, 0
/* 00B810 80010DB0 9421FFE8 */  stwu    r1, -0x18(r1)
/* 00B814 80010DB4 93E10014 */  stw     r31, 0x14(r1)
/* 00B818 80010DB8 3BE49E50 */  addi    r31, r4, AudioDecodeThread@l
/* 00B81C 80010DBC 41820040 */  beq     lbl_80010DFC
/* 00B820 80010DC0 3C608001 */  lis     r3, AudioDecoderForOnMemory@ha
/* 00B824 80010DC4 38830ED8 */  addi    r4, r3, AudioDecoderForOnMemory@l
/* 00B828 80010DC8 387F0000 */  addi    r3, r31, 0
/* 00B82C 80010DCC 38DF1318 */  addi    r6, r31, 0x1318
/* 00B830 80010DD0 38E01000 */  li      r7, 0x1000
/* 00B834 80010DD4 39200001 */  li      r9, 1
/* 00B838 80010DD8 480909B5 */  bl      OSCreateThread
/* 00B83C 80010DDC 2C030000 */  cmpwi   r3, 0
/* 00B840 80010DE0 4082005C */  bne     lbl_80010E3C
/* 00B844 80010DE4 3C60800F */  lis     r3, D_800EA488@ha
/* 00B848 80010DE8 4CC63182 */  crclr   6
/* 00B84C 80010DEC 3863A488 */  addi    r3, r3, D_800EA488@l
/* 00B850 80010DF0 4808D809 */  bl      OSReport
/* 00B854 80010DF4 38600000 */  li      r3, 0
/* 00B858 80010DF8 48000070 */  b       lbl_80010E68
lbl_80010DFC:
/* 00B85C 80010DFC 3C608001 */  lis     r3, AudioDecoder@ha
/* 00B860 80010E00 38830EB0 */  addi    r4, r3, AudioDecoder@l
/* 00B864 80010E04 387F0000 */  addi    r3, r31, 0
/* 00B868 80010E08 38DF1318 */  addi    r6, r31, 0x1318
/* 00B86C 80010E0C 38A00000 */  li      r5, 0
/* 00B870 80010E10 38E01000 */  li      r7, 0x1000
/* 00B874 80010E14 39200001 */  li      r9, 1
/* 00B878 80010E18 48090975 */  bl      OSCreateThread
/* 00B87C 80010E1C 2C030000 */  cmpwi   r3, 0
/* 00B880 80010E20 4082001C */  bne     lbl_80010E3C
/* 00B884 80010E24 3C60800F */  lis     r3, D_800EA488@ha
/* 00B888 80010E28 4CC63182 */  crclr   6
/* 00B88C 80010E2C 3863A488 */  addi    r3, r3, D_800EA488@l
/* 00B890 80010E30 4808D7C9 */  bl      OSReport
/* 00B894 80010E34 38600000 */  li      r3, 0
/* 00B898 80010E38 48000030 */  b       lbl_80010E68
lbl_80010E3C:
/* 00B89C 80010E3C 387F1318 */  addi    r3, r31, 0x1318
/* 00B8A0 80010E40 389F1358 */  addi    r4, r31, 0x1358
/* 00B8A4 80010E44 38A00003 */  li      r5, 3
/* 00B8A8 80010E48 4808E739 */  bl      OSInitMessageQueue
/* 00B8AC 80010E4C 387F1338 */  addi    r3, r31, 0x1338
/* 00B8B0 80010E50 389F1364 */  addi    r4, r31, 0x1364
/* 00B8B4 80010E54 38A00003 */  li      r5, 3
/* 00B8B8 80010E58 4808E729 */  bl      OSInitMessageQueue
/* 00B8BC 80010E5C 38000001 */  li      r0, 1
/* 00B8C0 80010E60 900D8958 */  stw     r0, AudioDecodeThreadCreated-_SDA_BASE_(r13)
/* 00B8C4 80010E64 38600001 */  li      r3, 1
lbl_80010E68:
/* 00B8C8 80010E68 8001001C */  lwz     r0, 0x1c(r1)
/* 00B8CC 80010E6C 83E10014 */  lwz     r31, 0x14(r1)
/* 00B8D0 80010E70 38210018 */  addi    r1, r1, 0x18
/* 00B8D4 80010E74 7C0803A6 */  mtlr    r0
/* 00B8D8 80010E78 4E800020 */  blr     

glabel AudioDecodeThreadStart
/* 00B8DC 80010E7C 7C0802A6 */  mflr    r0
/* 00B8E0 80010E80 90010004 */  stw     r0, 4(r1)
/* 00B8E4 80010E84 9421FFF8 */  stwu    r1, -8(r1)
/* 00B8E8 80010E88 800D8958 */  lwz     r0, AudioDecodeThreadCreated-_SDA_BASE_(r13)
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

AudioDecoder:
/* 00B910 80010EB0 7C0802A6 */  mflr    r0
/* 00B914 80010EB4 90010004 */  stw     r0, 4(r1)
/* 00B918 80010EB8 9421FFE8 */  stwu    r1, -0x18(r1)
/* 00B91C 80010EBC 93E10014 */  stw     r31, 0x14(r1)
lbl_80010EC0:
/* 00B920 80010EC0 48000B0D */  bl      PopReadedBuffer
/* 00B924 80010EC4 7C7F1B78 */  mr      r31, r3
/* 00B928 80010EC8 480000C1 */  bl      AudioDecode
/* 00B92C 80010ECC 7FE3FB78 */  mr      r3, r31
/* 00B930 80010ED0 48000A69 */  bl      PushReadedBuffer2
/* 00B934 80010ED4 4BFFFFEC */  b       lbl_80010EC0

AudioDecoderForOnMemory:
/* 00B938 80010ED8 7C0802A6 */  mflr    r0
/* 00B93C 80010EDC 3C808010 */  lis     r4, ActivePlayer@ha
/* 00B940 80010EE0 90010004 */  stw     r0, 4(r1)
/* 00B944 80010EE4 9421FFD0 */  stwu    r1, -0x30(r1)
/* 00B948 80010EE8 93E1002C */  stw     r31, 0x2c(r1)
/* 00B94C 80010EEC 3BE00000 */  li      r31, 0
/* 00B950 80010EF0 93C10028 */  stw     r30, 0x28(r1)
/* 00B954 80010EF4 93A10024 */  stw     r29, 0x24(r1)
/* 00B958 80010EF8 3BA49C80 */  addi    r29, r4, ActivePlayer@l
/* 00B95C 80010EFC 3C808010 */  lis     r4, AudioDecodeThread@ha
/* 00B960 80010F00 93810020 */  stw     r28, 0x20(r1)
/* 00B964 80010F04 3BC49E50 */  addi    r30, r4, AudioDecodeThread@l
/* 00B968 80010F08 839D00BC */  lwz     r28, 0xbc(r29)
/* 00B96C 80010F0C 90610010 */  stw     r3, 0x10(r1)
lbl_80010F10:
/* 00B970 80010F10 93E10014 */  stw     r31, 0x14(r1)
/* 00B974 80010F14 38610010 */  addi    r3, r1, 0x10
/* 00B978 80010F18 48000071 */  bl      AudioDecode
/* 00B97C 80010F1C 801D00C0 */  lwz     r0, 0xc0(r29)
/* 00B980 80010F20 809D0050 */  lwz     r4, 0x50(r29)
/* 00B984 80010F24 7C7F0214 */  add     r3, r31, r0
/* 00B988 80010F28 7C032396 */  divwu   r0, r3, r4
/* 00B98C 80010F2C 7C0021D6 */  mullw   r0, r0, r4
/* 00B990 80010F30 7C601850 */  subf    r3, r0, r3
/* 00B994 80010F34 3804FFFF */  addi    r0, r4, -1
/* 00B998 80010F38 7C030040 */  cmplw   r3, r0
/* 00B99C 80010F3C 40820030 */  bne     lbl_80010F6C
/* 00B9A0 80010F40 881D00A6 */  lbz     r0, 0xa6(r29)
/* 00B9A4 80010F44 540007FF */  clrlwi. r0, r0, 0x1f
/* 00B9A8 80010F48 41820018 */  beq     lbl_80010F60
/* 00B9AC 80010F4C 80610010 */  lwz     r3, 0x10(r1)
/* 00B9B0 80010F50 801D00B4 */  lwz     r0, 0xb4(r29)
/* 00B9B4 80010F54 83830000 */  lwz     r28, 0(r3)
/* 00B9B8 80010F58 90010010 */  stw     r0, 0x10(r1)
/* 00B9BC 80010F5C 48000024 */  b       lbl_80010F80
lbl_80010F60:
/* 00B9C0 80010F60 7FC3F378 */  mr      r3, r30
/* 00B9C4 80010F64 48090F39 */  bl      OSSuspendThread
/* 00B9C8 80010F68 48000018 */  b       lbl_80010F80
lbl_80010F6C:
/* 00B9CC 80010F6C 80610010 */  lwz     r3, 0x10(r1)
/* 00B9D0 80010F70 80830000 */  lwz     r4, 0(r3)
/* 00B9D4 80010F74 7C03E214 */  add     r0, r3, r28
/* 00B9D8 80010F78 90010010 */  stw     r0, 0x10(r1)
/* 00B9DC 80010F7C 7C9C2378 */  mr      r28, r4
lbl_80010F80:
/* 00B9E0 80010F80 3BFF0001 */  addi    r31, r31, 1
/* 00B9E4 80010F84 4BFFFF8C */  b       lbl_80010F10

AudioDecode:
/* 00B9E8 80010F88 7C0802A6 */  mflr    r0
/* 00B9EC 80010F8C 3C808010 */  lis     r4, ActivePlayer@ha
/* 00B9F0 80010F90 90010004 */  stw     r0, 4(r1)
/* 00B9F4 80010F94 9421FFE0 */  stwu    r1, -0x20(r1)
/* 00B9F8 80010F98 93E1001C */  stw     r31, 0x1c(r1)
/* 00B9FC 80010F9C 3BE49C80 */  addi    r31, r4, ActivePlayer@l
/* 00BA00 80010FA0 93C10018 */  stw     r30, 0x18(r1)
/* 00BA04 80010FA4 3BDF006C */  addi    r30, r31, 0x6c
/* 00BA08 80010FA8 93A10014 */  stw     r29, 0x14(r1)
/* 00BA0C 80010FAC 93810010 */  stw     r28, 0x10(r1)
/* 00BA10 80010FB0 801F006C */  lwz     r0, 0x6c(r31)
/* 00BA14 80010FB4 80A30000 */  lwz     r5, 0(r3)
/* 00BA18 80010FB8 5403103A */  slwi    r3, r0, 2
/* 00BA1C 80010FBC 3B830008 */  addi    r28, r3, 8
/* 00BA20 80010FC0 3BA50008 */  addi    r29, r5, 8
/* 00BA24 80010FC4 7F85E214 */  add     r28, r5, r28
/* 00BA28 80010FC8 48000099 */  bl      PopFreeAudioBuffer
/* 00BA2C 80010FCC 801E0000 */  lwz     r0, 0(r30)
/* 00BA30 80010FD0 3BC30000 */  addi    r30, r3, 0
/* 00BA34 80010FD4 28000000 */  cmplwi  r0, 0
/* 00BA38 80010FD8 7C0903A6 */  mtctr   r0
/* 00BA3C 80010FDC 40810064 */  ble     lbl_80011040
lbl_80010FE0:
/* 00BA40 80010FE0 881F0070 */  lbz     r0, 0x70(r31)
/* 00BA44 80010FE4 2C000001 */  cmpwi   r0, 1
/* 00BA48 80010FE8 41820008 */  beq     lbl_80010FF0
/* 00BA4C 80010FEC 48000040 */  b       lbl_8001102C
lbl_80010FF0:
/* 00BA50 80010FF0 3C608010 */  lis     r3, ActivePlayer@ha
/* 00BA54 80010FF4 80DD0000 */  lwz     r6, 0(r29)
/* 00BA58 80010FF8 38839C80 */  addi    r4, r3, ActivePlayer@l
/* 00BA5C 80010FFC 807E0000 */  lwz     r3, 0(r30)
/* 00BA60 80011000 800400EC */  lwz     r0, 0xec(r4)
/* 00BA64 80011004 38A00000 */  li      r5, 0
/* 00BA68 80011008 7C0601D6 */  mullw   r0, r6, r0
/* 00BA6C 8001100C 7C9C0214 */  add     r4, r28, r0
/* 00BA70 80011010 480B7A1D */  bl      THPAudioDecode
/* 00BA74 80011014 907E0008 */  stw     r3, 8(r30)
/* 00BA78 80011018 7FC3F378 */  mr      r3, r30
/* 00BA7C 8001101C 801E0000 */  lwz     r0, 0(r30)
/* 00BA80 80011020 901E0004 */  stw     r0, 4(r30)
/* 00BA84 80011024 480000E5 */  bl      PushDecodedAudioBuffer
/* 00BA88 80011028 48000018 */  b       lbl_80011040
lbl_8001102C:
/* 00BA8C 8001102C 801D0000 */  lwz     r0, 0(r29)
/* 00BA90 80011030 3BBD0004 */  addi    r29, r29, 4
/* 00BA94 80011034 3BFF0001 */  addi    r31, r31, 1
/* 00BA98 80011038 7F9C0214 */  add     r28, r28, r0
/* 00BA9C 8001103C 4200FFA4 */  bdnz    lbl_80010FE0
lbl_80011040:
/* 00BAA0 80011040 80010024 */  lwz     r0, 0x24(r1)
/* 00BAA4 80011044 83E1001C */  lwz     r31, 0x1c(r1)
/* 00BAA8 80011048 83C10018 */  lwz     r30, 0x18(r1)
/* 00BAAC 8001104C 7C0803A6 */  mtlr    r0
/* 00BAB0 80011050 83A10014 */  lwz     r29, 0x14(r1)
/* 00BAB4 80011054 83810010 */  lwz     r28, 0x10(r1)
/* 00BAB8 80011058 38210020 */  addi    r1, r1, 0x20
/* 00BABC 8001105C 4E800020 */  blr     

glabel PopFreeAudioBuffer
/* 00BAC0 80011060 7C0802A6 */  mflr    r0
/* 00BAC4 80011064 3C608010 */  lis     r3, FreeAudioBufferQueue@ha
/* 00BAC8 80011068 90010004 */  stw     r0, 4(r1)
/* 00BACC 8001106C 3863B168 */  addi    r3, r3, FreeAudioBufferQueue@l
/* 00BAD0 80011070 38A00001 */  li      r5, 1
/* 00BAD4 80011074 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00BAD8 80011078 38810008 */  addi    r4, r1, 8
/* 00BADC 8001107C 4808E62D */  bl      OSReceiveMessage
/* 00BAE0 80011080 80010014 */  lwz     r0, 0x14(r1)
/* 00BAE4 80011084 80610008 */  lwz     r3, 8(r1)
/* 00BAE8 80011088 38210010 */  addi    r1, r1, 0x10
/* 00BAEC 8001108C 7C0803A6 */  mtlr    r0
/* 00BAF0 80011090 4E800020 */  blr     

glabel PushFreeAudioBuffer
/* 00BAF4 80011094 7C0802A6 */  mflr    r0
/* 00BAF8 80011098 3CA08010 */  lis     r5, FreeAudioBufferQueue@ha
/* 00BAFC 8001109C 90010004 */  stw     r0, 4(r1)
/* 00BB00 800110A0 38830000 */  addi    r4, r3, 0
/* 00BB04 800110A4 3865B168 */  addi    r3, r5, FreeAudioBufferQueue@l
/* 00BB08 800110A8 9421FFF8 */  stwu    r1, -8(r1)
/* 00BB0C 800110AC 38A00000 */  li      r5, 0
/* 00BB10 800110B0 4808E531 */  bl      OSSendMessage
/* 00BB14 800110B4 8001000C */  lwz     r0, 0xc(r1)
/* 00BB18 800110B8 38210008 */  addi    r1, r1, 8
/* 00BB1C 800110BC 7C0803A6 */  mtlr    r0
/* 00BB20 800110C0 4E800020 */  blr     

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

glabel PushDecodedAudioBuffer
/* 00BB68 80011108 7C0802A6 */  mflr    r0
/* 00BB6C 8001110C 3CA08010 */  lis     r5, DecodedAudioBufferQueue@ha
/* 00BB70 80011110 90010004 */  stw     r0, 4(r1)
/* 00BB74 80011114 38830000 */  addi    r4, r3, 0
/* 00BB78 80011118 3865B188 */  addi    r3, r5, DecodedAudioBufferQueue@l
/* 00BB7C 8001111C 9421FFF8 */  stwu    r1, -8(r1)
/* 00BB80 80011120 38A00001 */  li      r5, 1
/* 00BB84 80011124 4808E4BD */  bl      OSSendMessage
/* 00BB88 80011128 8001000C */  lwz     r0, 0xc(r1)
/* 00BB8C 8001112C 38210008 */  addi    r1, r1, 8
/* 00BB90 80011130 7C0803A6 */  mtlr    r0
/* 00BB94 80011134 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000E7508 800EA488 0022 */
D_800EA488:
    .asciz "Can't create audio decode thread\n"
    .balign 4

.section .bss, "wa"

.balign 4

/* 000F6ED0 800F9E50 0318 */
AudioDecodeThread:
    .skip 792

/* 000F71E8 800FA168 1000 */
AudioDecodeThreadStack:
    .skip 4096

/* 000F81E8 800FB168 0020 */
FreeAudioBufferQueue:
    .skip 32

/* 000F8208 800FB188 0020 */
DecodedAudioBufferQueue:
    .skip 32

/* 000F8228 800FB1A8 000C */
FreeAudioBufferMessage:
    .skip 12

/* 000F8234 800FB1B4 000C */
DecodedAudioBufferMessage:
    .skip 12

.section .sbss, "wa"

.balign 8

/* 000F18B8 80135638 0004 */
AudioDecodeThreadCreated:
    .skip 4
