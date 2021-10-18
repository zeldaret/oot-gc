# THPVideoDecode.c
.include "macros.inc"

.section .text, "ax"

.balign 4

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

VideoDecoder:
/* 00DA98 80013038 7C0802A6 */  mflr    r0
/* 00DA9C 8001303C 3C608010 */  lis     r3, ActivePlayer@ha
/* 00DAA0 80013040 90010004 */  stw     r0, 4(r1)
/* 00DAA4 80013044 9421FFE0 */  stwu    r1, -0x20(r1)
/* 00DAA8 80013048 93E1001C */  stw     r31, 0x1c(r1)
/* 00DAAC 8001304C 3BE39C80 */  addi    r31, r3, ActivePlayer@l
/* 00DAB0 80013050 93C10018 */  stw     r30, 0x18(r1)
/* 00DAB4 80013054 3BDF00D8 */  addi    r30, r31, 0xd8
/* 00DAB8 80013058 93A10014 */  stw     r29, 0x14(r1)
/* 00DABC 8001305C 3BBF00A7 */  addi    r29, r31, 0xa7
/* 00DAC0 80013060 93810010 */  stw     r28, 0x10(r1)
lbl_80013064:
/* 00DAC4 80013064 881D0000 */  lbz     r0, 0(r29)
/* 00DAC8 80013068 28000000 */  cmplwi  r0, 0
/* 00DACC 8001306C 41820074 */  beq     lbl_800130E0
/* 00DAD0 80013070 48000064 */  b       lbl_800130D4
lbl_80013074:
/* 00DAD4 80013074 4BFFE8F5 */  bl      PopReadedBuffer2
/* 00DAD8 80013078 7C7C1B78 */  mr      r28, r3
/* 00DADC 8001307C 80BF0050 */  lwz     r5, 0x50(r31)
/* 00DAE0 80013080 807F00C0 */  lwz     r3, 0xc0(r31)
/* 00DAE4 80013084 809C0004 */  lwz     r4, 4(r28)
/* 00DAE8 80013088 3805FFFF */  addi    r0, r5, -1
/* 00DAEC 8001308C 7C841A14 */  add     r4, r4, r3
/* 00DAF0 80013090 7C642B96 */  divwu   r3, r4, r5
/* 00DAF4 80013094 7C6329D6 */  mullw   r3, r3, r5
/* 00DAF8 80013098 7C632050 */  subf    r3, r3, r4
/* 00DAFC 8001309C 7C030040 */  cmplw   r3, r0
/* 00DB00 800130A0 40820018 */  bne     lbl_800130B8
/* 00DB04 800130A4 881F00A6 */  lbz     r0, 0xa6(r31)
/* 00DB08 800130A8 540007FF */  clrlwi. r0, r0, 0x1f
/* 00DB0C 800130AC 4082000C */  bne     lbl_800130B8
/* 00DB10 800130B0 7F83E378 */  mr      r3, r28
/* 00DB14 800130B4 48000195 */  bl      VideoDecode
lbl_800130B8:
/* 00DB18 800130B8 7F83E378 */  mr      r3, r28
/* 00DB1C 800130BC 4BFFE8E1 */  bl      PushFreeReadBuffer
/* 00DB20 800130C0 4808BC3D */  bl      OSDisableInterrupts
/* 00DB24 800130C4 809E0000 */  lwz     r4, 0(r30)
/* 00DB28 800130C8 38040001 */  addi    r0, r4, 1
/* 00DB2C 800130CC 901E0000 */  stw     r0, 0(r30)
/* 00DB30 800130D0 4808BC55 */  bl      OSRestoreInterrupts
lbl_800130D4:
/* 00DB34 800130D4 801E0000 */  lwz     r0, 0(r30)
/* 00DB38 800130D8 2C000000 */  cmpwi   r0, 0
/* 00DB3C 800130DC 4180FF98 */  blt     lbl_80013074
lbl_800130E0:
/* 00DB40 800130E0 881D0000 */  lbz     r0, 0(r29)
/* 00DB44 800130E4 28000000 */  cmplwi  r0, 0
/* 00DB48 800130E8 41820010 */  beq     lbl_800130F8
/* 00DB4C 800130EC 4BFFE87D */  bl      PopReadedBuffer2
/* 00DB50 800130F0 7C7C1B78 */  mr      r28, r3
/* 00DB54 800130F4 4800000C */  b       lbl_80013100
lbl_800130F8:
/* 00DB58 800130F8 4BFFE8D5 */  bl      PopReadedBuffer
/* 00DB5C 800130FC 7C7C1B78 */  mr      r28, r3
lbl_80013100:
/* 00DB60 80013100 7F83E378 */  mr      r3, r28
/* 00DB64 80013104 48000145 */  bl      VideoDecode
/* 00DB68 80013108 7F83E378 */  mr      r3, r28
/* 00DB6C 8001310C 4BFFE891 */  bl      PushFreeReadBuffer
/* 00DB70 80013110 4BFFFF54 */  b       lbl_80013064

VideoDecoderForOnMemory:
/* 00DB74 80013114 7C0802A6 */  mflr    r0
/* 00DB78 80013118 3C808010 */  lis     r4, ActivePlayer@ha
/* 00DB7C 8001311C 90010004 */  stw     r0, 4(r1)
/* 00DB80 80013120 9421FFC8 */  stwu    r1, -0x38(r1)
/* 00DB84 80013124 BF610024 */  stmw    r27, 0x24(r1)
/* 00DB88 80013128 3BE49C80 */  addi    r31, r4, ActivePlayer@l
/* 00DB8C 8001312C 3C808010 */  lis     r4, VideoDecodeThread@ha
/* 00DB90 80013130 3BDF00D8 */  addi    r30, r31, 0xd8
/* 00DB94 80013134 3B64C5F0 */  addi    r27, r4, VideoDecodeThread@l
/* 00DB98 80013138 3B800000 */  li      r28, 0
/* 00DB9C 8001313C 83BF00BC */  lwz     r29, 0xbc(r31)
/* 00DBA0 80013140 90610010 */  stw     r3, 0x10(r1)
lbl_80013144:
/* 00DBA4 80013144 881F00A7 */  lbz     r0, 0xa7(r31)
/* 00DBA8 80013148 28000000 */  cmplwi  r0, 0
/* 00DBAC 8001314C 41820084 */  beq     lbl_800131D0
/* 00DBB0 80013150 48000074 */  b       lbl_800131C4
lbl_80013154:
/* 00DBB4 80013154 4808BBA9 */  bl      OSDisableInterrupts
/* 00DBB8 80013158 809E0000 */  lwz     r4, 0(r30)
/* 00DBBC 8001315C 38040001 */  addi    r0, r4, 1
/* 00DBC0 80013160 901E0000 */  stw     r0, 0(r30)
/* 00DBC4 80013164 4808BBC1 */  bl      OSRestoreInterrupts
/* 00DBC8 80013168 801F00C0 */  lwz     r0, 0xc0(r31)
/* 00DBCC 8001316C 809F0050 */  lwz     r4, 0x50(r31)
/* 00DBD0 80013170 7C7C0214 */  add     r3, r28, r0
/* 00DBD4 80013174 7C032396 */  divwu   r0, r3, r4
/* 00DBD8 80013178 7C0021D6 */  mullw   r0, r0, r4
/* 00DBDC 8001317C 7C601850 */  subf    r3, r0, r3
/* 00DBE0 80013180 3804FFFF */  addi    r0, r4, -1
/* 00DBE4 80013184 7C030040 */  cmplw   r3, r0
/* 00DBE8 80013188 40820024 */  bne     lbl_800131AC
/* 00DBEC 8001318C 881F00A6 */  lbz     r0, 0xa6(r31)
/* 00DBF0 80013190 540007FF */  clrlwi. r0, r0, 0x1f
/* 00DBF4 80013194 4182003C */  beq     lbl_800131D0
/* 00DBF8 80013198 80610010 */  lwz     r3, 0x10(r1)
/* 00DBFC 8001319C 801F00B4 */  lwz     r0, 0xb4(r31)
/* 00DC00 800131A0 83A30000 */  lwz     r29, 0(r3)
/* 00DC04 800131A4 90010010 */  stw     r0, 0x10(r1)
/* 00DC08 800131A8 48000018 */  b       lbl_800131C0
lbl_800131AC:
/* 00DC0C 800131AC 80610010 */  lwz     r3, 0x10(r1)
/* 00DC10 800131B0 80830000 */  lwz     r4, 0(r3)
/* 00DC14 800131B4 7C03EA14 */  add     r0, r3, r29
/* 00DC18 800131B8 90010010 */  stw     r0, 0x10(r1)
/* 00DC1C 800131BC 7C9D2378 */  mr      r29, r4
lbl_800131C0:
/* 00DC20 800131C0 3B9C0001 */  addi    r28, r28, 1
lbl_800131C4:
/* 00DC24 800131C4 801E0000 */  lwz     r0, 0(r30)
/* 00DC28 800131C8 2C000000 */  cmpwi   r0, 0
/* 00DC2C 800131CC 4180FF88 */  blt     lbl_80013154
lbl_800131D0:
/* 00DC30 800131D0 93810014 */  stw     r28, 0x14(r1)
/* 00DC34 800131D4 38610010 */  addi    r3, r1, 0x10
/* 00DC38 800131D8 48000071 */  bl      VideoDecode
/* 00DC3C 800131DC 801F00C0 */  lwz     r0, 0xc0(r31)
/* 00DC40 800131E0 809F0050 */  lwz     r4, 0x50(r31)
/* 00DC44 800131E4 7C7C0214 */  add     r3, r28, r0
/* 00DC48 800131E8 7C032396 */  divwu   r0, r3, r4
/* 00DC4C 800131EC 7C0021D6 */  mullw   r0, r0, r4
/* 00DC50 800131F0 7C601850 */  subf    r3, r0, r3
/* 00DC54 800131F4 3804FFFF */  addi    r0, r4, -1
/* 00DC58 800131F8 7C030040 */  cmplw   r3, r0
/* 00DC5C 800131FC 40820030 */  bne     lbl_8001322C
/* 00DC60 80013200 881F00A6 */  lbz     r0, 0xa6(r31)
/* 00DC64 80013204 540007FF */  clrlwi. r0, r0, 0x1f
/* 00DC68 80013208 41820018 */  beq     lbl_80013220
/* 00DC6C 8001320C 80610010 */  lwz     r3, 0x10(r1)
/* 00DC70 80013210 801F00B4 */  lwz     r0, 0xb4(r31)
/* 00DC74 80013214 83A30000 */  lwz     r29, 0(r3)
/* 00DC78 80013218 90010010 */  stw     r0, 0x10(r1)
/* 00DC7C 8001321C 48000024 */  b       lbl_80013240
lbl_80013220:
/* 00DC80 80013220 7F63DB78 */  mr      r3, r27
/* 00DC84 80013224 4808EC79 */  bl      OSSuspendThread
/* 00DC88 80013228 48000018 */  b       lbl_80013240
lbl_8001322C:
/* 00DC8C 8001322C 80610010 */  lwz     r3, 0x10(r1)
/* 00DC90 80013230 80830000 */  lwz     r4, 0(r3)
/* 00DC94 80013234 7C03EA14 */  add     r0, r3, r29
/* 00DC98 80013238 90010010 */  stw     r0, 0x10(r1)
/* 00DC9C 8001323C 7C9D2378 */  mr      r29, r4
lbl_80013240:
/* 00DCA0 80013240 3B9C0001 */  addi    r28, r28, 1
/* 00DCA4 80013244 4BFFFF00 */  b       lbl_80013144

VideoDecode:
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

glabel PopFreeTextureSet
/* 00DDC8 80013368 7C0802A6 */  mflr    r0
/* 00DDCC 8001336C 3C608010 */  lis     r3, FreeTextureSetQueue@ha
/* 00DDD0 80013370 90010004 */  stw     r0, 4(r1)
/* 00DDD4 80013374 3863D908 */  addi    r3, r3, FreeTextureSetQueue@l
/* 00DDD8 80013378 38A00001 */  li      r5, 1
/* 00DDDC 8001337C 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00DDE0 80013380 38810008 */  addi    r4, r1, 8
/* 00DDE4 80013384 4808C325 */  bl      OSReceiveMessage
/* 00DDE8 80013388 80010014 */  lwz     r0, 0x14(r1)
/* 00DDEC 8001338C 80610008 */  lwz     r3, 8(r1)
/* 00DDF0 80013390 38210010 */  addi    r1, r1, 0x10
/* 00DDF4 80013394 7C0803A6 */  mtlr    r0
/* 00DDF8 80013398 4E800020 */  blr     

glabel PushFreeTextureSet
/* 00DDFC 8001339C 7C0802A6 */  mflr    r0
/* 00DE00 800133A0 3CA08010 */  lis     r5, FreeTextureSetQueue@ha
/* 00DE04 800133A4 90010004 */  stw     r0, 4(r1)
/* 00DE08 800133A8 38830000 */  addi    r4, r3, 0
/* 00DE0C 800133AC 3865D908 */  addi    r3, r5, FreeTextureSetQueue@l
/* 00DE10 800133B0 9421FFF8 */  stwu    r1, -8(r1)
/* 00DE14 800133B4 38A00000 */  li      r5, 0
/* 00DE18 800133B8 4808C229 */  bl      OSSendMessage
/* 00DE1C 800133BC 8001000C */  lwz     r0, 0xc(r1)
/* 00DE20 800133C0 38210008 */  addi    r1, r1, 8
/* 00DE24 800133C4 7C0803A6 */  mtlr    r0
/* 00DE28 800133C8 4E800020 */  blr     

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

glabel PushDecodedTextureSet
/* 00DE70 80013410 7C0802A6 */  mflr    r0
/* 00DE74 80013414 3CA08010 */  lis     r5, DecodedTextureSetQueue@ha
/* 00DE78 80013418 90010004 */  stw     r0, 4(r1)
/* 00DE7C 8001341C 38830000 */  addi    r4, r3, 0
/* 00DE80 80013420 3865D928 */  addi    r3, r5, DecodedTextureSetQueue@l
/* 00DE84 80013424 9421FFF8 */  stwu    r1, -8(r1)
/* 00DE88 80013428 38A00001 */  li      r5, 1
/* 00DE8C 8001342C 4808C1B5 */  bl      OSSendMessage
/* 00DE90 80013430 8001000C */  lwz     r0, 0xc(r1)
/* 00DE94 80013434 38210008 */  addi    r1, r1, 8
/* 00DE98 80013438 7C0803A6 */  mtlr    r0
/* 00DE9C 8001343C 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000E75A0 800EA520 0022 */
D_800EA520:
    .asciz "Can't create video decode thread\n"
    .balign 4

.section .bss, "wa"

.balign 4

/* 000F9670 800FC5F0 0318 */
VideoDecodeThread:
    .skip 792

/* 000F9988 800FC908 1000 */
VideoDecodeThreadStack:
    .skip 4096

/* 000FA988 800FD908 0020 */
FreeTextureSetQueue:
    .skip 32

/* 000FA9A8 800FD928 0020 */
DecodedTextureSetQueue:
    .skip 32

/* 000FA9C8 800FD948 000C */
FreeTextureSetMessage:
    .skip 12

/* 000FA9D4 800FD954 000C */
DecodedTextureSetMessage:
    .skip 12

.section .sbss, "wa"

.balign 8

/* 000F18D8 80135658 0004 */
VideoDecodeThreadCreated:
    .skip 4

/* 000F18DC 8013565C 0004 */
First:
    .skip 4
