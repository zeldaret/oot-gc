# ai.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel AIRegisterDMACallback
/* 0B29E4 800B7F84 7C0802A6 */  mflr    r0
/* 0B29E8 800B7F88 90010004 */  stw     r0, 4(r1)
/* 0B29EC 800B7F8C 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0B29F0 800B7F90 93E10014 */  stw     r31, 0x14(r1)
/* 0B29F4 800B7F94 93C10010 */  stw     r30, 0x10(r1)
/* 0B29F8 800B7F98 7C7E1B78 */  mr      r30, r3
/* 0B29FC 800B7F9C 83ED8E34 */  lwz     r31, __AID_Callback@sda21(r13)
/* 0B2A00 800B7FA0 4BFE6D5D */  bl      OSDisableInterrupts
/* 0B2A04 800B7FA4 93CD8E34 */  stw     r30, __AID_Callback@sda21(r13)
/* 0B2A08 800B7FA8 4BFE6D7D */  bl      OSRestoreInterrupts
/* 0B2A0C 800B7FAC 7FE3FB78 */  mr      r3, r31
/* 0B2A10 800B7FB0 8001001C */  lwz     r0, 0x1c(r1)
/* 0B2A14 800B7FB4 83E10014 */  lwz     r31, 0x14(r1)
/* 0B2A18 800B7FB8 83C10010 */  lwz     r30, 0x10(r1)
/* 0B2A1C 800B7FBC 38210018 */  addi    r1, r1, 0x18
/* 0B2A20 800B7FC0 7C0803A6 */  mtlr    r0
/* 0B2A24 800B7FC4 4E800020 */  blr     

glabel AIInitDMA
/* 0B2A28 800B7FC8 7C0802A6 */  mflr    r0
/* 0B2A2C 800B7FCC 90010004 */  stw     r0, 4(r1)
/* 0B2A30 800B7FD0 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0B2A34 800B7FD4 93E10014 */  stw     r31, 0x14(r1)
/* 0B2A38 800B7FD8 3BE40000 */  addi    r31, r4, 0
/* 0B2A3C 800B7FDC 93C10010 */  stw     r30, 0x10(r1)
/* 0B2A40 800B7FE0 3BC30000 */  addi    r30, r3, 0
/* 0B2A44 800B7FE4 4BFE6D19 */  bl      OSDisableInterrupts
/* 0B2A48 800B7FE8 3C80CC00 */  lis     r4, DSP_REGS_BASE@ha
/* 0B2A4C 800B7FEC A0045030 */  lhz     r0, (DSP_REGS_BASE + DSP_30)@l(r4)
/* 0B2A50 800B7FF0 38A45000 */  addi    r5, r4, DSP_REGS_BASE@l
/* 0B2A54 800B7FF4 38C45000 */  addi    r6, r4, DSP_REGS_BASE@l
/* 0B2A58 800B7FF8 38E45000 */  addi    r7, r4, DSP_REGS_BASE@l
/* 0B2A5C 800B7FFC 5404002A */  rlwinm  r4, r0, 0, 0, 0x15
/* 0B2A60 800B8000 57C0843E */  srwi    r0, r30, 0x10
/* 0B2A64 800B8004 7C800378 */  or      r0, r4, r0
/* 0B2A68 800B8008 B0050030 */  sth     r0, DSP_30(r5)
/* 0B2A6C 800B800C 57C0043E */  clrlwi  r0, r30, 0x10
/* 0B2A70 800B8010 A0860032 */  lhz     r4, DSP_32(r6)
/* 0B2A74 800B8014 548406DE */  rlwinm  r4, r4, 0, 0x1b, 0xf
/* 0B2A78 800B8018 7C800378 */  or      r0, r4, r0
/* 0B2A7C 800B801C B0060032 */  sth     r0, DSP_32(r6)
/* 0B2A80 800B8020 57E0DC3E */  rlwinm  r0, r31, 0x1b, 0x10, 0x1f
/* 0B2A84 800B8024 A0870036 */  lhz     r4, DSP_36(r7)
/* 0B2A88 800B8028 54840020 */  rlwinm  r4, r4, 0, 0, 0x10
/* 0B2A8C 800B802C 7C800378 */  or      r0, r4, r0
/* 0B2A90 800B8030 B0070036 */  sth     r0, DSP_36(r7)
/* 0B2A94 800B8034 4BFE6CF1 */  bl      OSRestoreInterrupts
/* 0B2A98 800B8038 8001001C */  lwz     r0, 0x1c(r1)
/* 0B2A9C 800B803C 83E10014 */  lwz     r31, 0x14(r1)
/* 0B2AA0 800B8040 83C10010 */  lwz     r30, 0x10(r1)
/* 0B2AA4 800B8044 38210018 */  addi    r1, r1, 0x18
/* 0B2AA8 800B8048 7C0803A6 */  mtlr    r0
/* 0B2AAC 800B804C 4E800020 */  blr     

glabel AIGetDMAEnableFlag
/* 0B2AB0 800B8050 3C60CC00 */  lis     r3, DSP_REGS_BASE@ha
/* 0B2AB4 800B8054 A0035036 */  lhz     r0, (DSP_REGS_BASE + DSP_36)@l(r3)
/* 0B2AB8 800B8058 54038FFE */  rlwinm  r3, r0, 0x11, 0x1f, 0x1f
/* 0B2ABC 800B805C 4E800020 */  blr     

glabel AIStartDMA
/* 0B2AC0 800B8060 3C60CC00 */  lis     r3, DSP_REGS_BASE@ha
/* 0B2AC4 800B8064 38635000 */  addi    r3, r3, DSP_REGS_BASE@l
/* 0B2AC8 800B8068 A0030036 */  lhz     r0, DSP_36(r3)
/* 0B2ACC 800B806C 60008000 */  ori     r0, r0, 0x8000
/* 0B2AD0 800B8070 B0030036 */  sth     r0, DSP_36(r3)
/* 0B2AD4 800B8074 4E800020 */  blr     

glabel AIStopDMA
/* 0B2AD8 800B8078 3C60CC00 */  lis     r3, DSP_REGS_BASE@ha
/* 0B2ADC 800B807C 38635000 */  addi    r3, r3, DSP_REGS_BASE@l
/* 0B2AE0 800B8080 A0030036 */  lhz     r0, DSP_36(r3)
/* 0B2AE4 800B8084 5400045E */  rlwinm  r0, r0, 0, 0x11, 0xf
/* 0B2AE8 800B8088 B0030036 */  sth     r0, DSP_36(r3)
/* 0B2AEC 800B808C 4E800020 */  blr     

glabel AIGetDMABytesLeft
/* 0B2AF0 800B8090 3C60CC00 */  lis     r3, DSP_REGS_BASE@ha
/* 0B2AF4 800B8094 A003503A */  lhz     r0, (DSP_REGS_BASE + DSP_3A)@l(r3)
/* 0B2AF8 800B8098 54032B34 */  rlwinm  r3, r0, 5, 0xc, 0x1a
/* 0B2AFC 800B809C 4E800020 */  blr     

glabel AIGetDMAStartAddr
/* 0B2B00 800B80A0 3C60CC00 */  lis     r3, DSP_REGS_BASE@ha
/* 0B2B04 800B80A4 38635000 */  addi    r3, r3, DSP_REGS_BASE@l
/* 0B2B08 800B80A8 A0830030 */  lhz     r4, DSP_30(r3)
/* 0B2B0C 800B80AC A0030032 */  lhz     r0, DSP_32(r3)
/* 0B2B10 800B80B0 54030434 */  rlwinm  r3, r0, 0, 0x10, 0x1a
/* 0B2B14 800B80B4 5083819E */  rlwimi  r3, r4, 0x10, 6, 0xf
/* 0B2B18 800B80B8 4E800020 */  blr     

glabel AISetStreamPlayState
/* 0B2B1C 800B80BC 7C0802A6 */  mflr    r0
/* 0B2B20 800B80C0 90010004 */  stw     r0, 4(r1)
/* 0B2B24 800B80C4 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0B2B28 800B80C8 93E1001C */  stw     r31, 0x1c(r1)
/* 0B2B2C 800B80CC 93C10018 */  stw     r30, 0x18(r1)
/* 0B2B30 800B80D0 93A10014 */  stw     r29, 0x14(r1)
/* 0B2B34 800B80D4 7C7D1B78 */  mr      r29, r3
/* 0B2B38 800B80D8 480000BD */  bl      AIGetStreamPlayState
/* 0B2B3C 800B80DC 7C1D1840 */  cmplw   r29, r3
/* 0B2B40 800B80E0 41820098 */  beq     lbl_800B8178
/* 0B2B44 800B80E4 48000289 */  bl      AIGetStreamSampleRate
/* 0B2B48 800B80E8 28030000 */  cmplwi  r3, 0
/* 0B2B4C 800B80EC 40820078 */  bne     lbl_800B8164
/* 0B2B50 800B80F0 281D0001 */  cmplwi  r29, 1
/* 0B2B54 800B80F4 40820070 */  bne     lbl_800B8164
/* 0B2B58 800B80F8 480002CD */  bl      AIGetStreamVolRight
/* 0B2B5C 800B80FC 7C7E1B78 */  mr      r30, r3
/* 0B2B60 800B8100 48000299 */  bl      AIGetStreamVolLeft
/* 0B2B64 800B8104 3BA30000 */  addi    r29, r3, 0
/* 0B2B68 800B8108 38600000 */  li      r3, 0
/* 0B2B6C 800B810C 4800029D */  bl      AISetStreamVolRight
/* 0B2B70 800B8110 38600000 */  li      r3, 0
/* 0B2B74 800B8114 48000269 */  bl      AISetStreamVolLeft
/* 0B2B78 800B8118 4BFE6BE5 */  bl      OSDisableInterrupts
/* 0B2B7C 800B811C 7C7F1B78 */  mr      r31, r3
/* 0B2B80 800B8120 480005A1 */  bl      __AI_SRC_INIT
/* 0B2B84 800B8124 3C80CC00 */  lis     r4, AI_REGS_BASE@ha
/* 0B2B88 800B8128 80046C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r4)
/* 0B2B8C 800B812C 387F0000 */  addi    r3, r31, 0
/* 0B2B90 800B8130 540006F2 */  rlwinm  r0, r0, 0, 0x1b, 0x19
/* 0B2B94 800B8134 60000020 */  ori     r0, r0, 0x20
/* 0B2B98 800B8138 90046C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r4)
/* 0B2B9C 800B813C 80046C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r4)
/* 0B2BA0 800B8140 5400003C */  rlwinm  r0, r0, 0, 0, 0x1e
/* 0B2BA4 800B8144 60000001 */  ori     r0, r0, 1
/* 0B2BA8 800B8148 90046C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r4)
/* 0B2BAC 800B814C 4BFE6BD9 */  bl      OSRestoreInterrupts
/* 0B2BB0 800B8150 7FC3F378 */  mr      r3, r30
/* 0B2BB4 800B8154 48000229 */  bl      AISetStreamVolLeft
/* 0B2BB8 800B8158 7FA3EB78 */  mr      r3, r29
/* 0B2BBC 800B815C 4800024D */  bl      AISetStreamVolRight
/* 0B2BC0 800B8160 48000018 */  b       lbl_800B8178
lbl_800B8164:
/* 0B2BC4 800B8164 3C60CC00 */  lis     r3, AI_REGS_BASE@ha
/* 0B2BC8 800B8168 80036C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r3)
/* 0B2BCC 800B816C 5400003C */  rlwinm  r0, r0, 0, 0, 0x1e
/* 0B2BD0 800B8170 7C00EB78 */  or      r0, r0, r29
/* 0B2BD4 800B8174 90036C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r3)
lbl_800B8178:
/* 0B2BD8 800B8178 80010024 */  lwz     r0, 0x24(r1)
/* 0B2BDC 800B817C 83E1001C */  lwz     r31, 0x1c(r1)
/* 0B2BE0 800B8180 83C10018 */  lwz     r30, 0x18(r1)
/* 0B2BE4 800B8184 83A10014 */  lwz     r29, 0x14(r1)
/* 0B2BE8 800B8188 38210020 */  addi    r1, r1, 0x20
/* 0B2BEC 800B818C 7C0803A6 */  mtlr    r0
/* 0B2BF0 800B8190 4E800020 */  blr     

glabel AIGetStreamPlayState
/* 0B2BF4 800B8194 3C60CC00 */  lis     r3, AI_REGS_BASE@ha
/* 0B2BF8 800B8198 80036C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r3)
/* 0B2BFC 800B819C 540307FE */  clrlwi  r3, r0, 0x1f
/* 0B2C00 800B81A0 4E800020 */  blr     

glabel AISetDSPSampleRate
/* 0B2C04 800B81A4 7C0802A6 */  mflr    r0
/* 0B2C08 800B81A8 90010004 */  stw     r0, 4(r1)
/* 0B2C0C 800B81AC 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0B2C10 800B81B0 BF410010 */  stmw    r26, 0x10(r1)
/* 0B2C14 800B81B4 7C7A1B78 */  mr      r26, r3
/* 0B2C18 800B81B8 480000CD */  bl      AIGetDSPSampleRate
/* 0B2C1C 800B81BC 7C1A1840 */  cmplw   r26, r3
/* 0B2C20 800B81C0 418200B0 */  beq     lbl_800B8270
/* 0B2C24 800B81C4 3FE0CC00 */  lis     r31, AI_REGS_BASE@ha
/* 0B2C28 800B81C8 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2C2C 800B81CC 281A0000 */  cmplwi  r26, 0
/* 0B2C30 800B81D0 540006B0 */  rlwinm  r0, r0, 0, 0x1a, 0x18
/* 0B2C34 800B81D4 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2C38 800B81D8 40820098 */  bne     lbl_800B8270
/* 0B2C3C 800B81DC 480001BD */  bl      AIGetStreamVolLeft
/* 0B2C40 800B81E0 7C7E1B78 */  mr      r30, r3
/* 0B2C44 800B81E4 480001E1 */  bl      AIGetStreamVolRight
/* 0B2C48 800B81E8 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2C4C 800B81EC 3BA30000 */  addi    r29, r3, 0
/* 0B2C50 800B81F0 541B07FE */  clrlwi  r27, r0, 0x1f
/* 0B2C54 800B81F4 48000179 */  bl      AIGetStreamSampleRate
/* 0B2C58 800B81F8 3B830000 */  addi    r28, r3, 0
/* 0B2C5C 800B81FC 38600000 */  li      r3, 0
/* 0B2C60 800B8200 4800017D */  bl      AISetStreamVolLeft
/* 0B2C64 800B8204 38600000 */  li      r3, 0
/* 0B2C68 800B8208 480001A1 */  bl      AISetStreamVolRight
/* 0B2C6C 800B820C 4BFE6AF1 */  bl      OSDisableInterrupts
/* 0B2C70 800B8210 7C7A1B78 */  mr      r26, r3
/* 0B2C74 800B8214 480004AD */  bl      __AI_SRC_INIT
/* 0B2C78 800B8218 809F6C00 */  lwz     r4, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2C7C 800B821C 5780083C */  slwi    r0, r28, 1
/* 0B2C80 800B8220 387A0000 */  addi    r3, r26, 0
/* 0B2C84 800B8224 548406F2 */  rlwinm  r4, r4, 0, 0x1b, 0x19
/* 0B2C88 800B8228 60840020 */  ori     r4, r4, 0x20
/* 0B2C8C 800B822C 909F6C00 */  stw     r4, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2C90 800B8230 809F6C00 */  lwz     r4, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2C94 800B8234 548407FA */  rlwinm  r4, r4, 0, 0x1f, 0x1d
/* 0B2C98 800B8238 7C800378 */  or      r0, r4, r0
/* 0B2C9C 800B823C 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2CA0 800B8240 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2CA4 800B8244 5400003C */  rlwinm  r0, r0, 0, 0, 0x1e
/* 0B2CA8 800B8248 7C00DB78 */  or      r0, r0, r27
/* 0B2CAC 800B824C 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2CB0 800B8250 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2CB4 800B8254 60000040 */  ori     r0, r0, 0x40
/* 0B2CB8 800B8258 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2CBC 800B825C 4BFE6AC9 */  bl      OSRestoreInterrupts
/* 0B2CC0 800B8260 7FC3F378 */  mr      r3, r30
/* 0B2CC4 800B8264 48000119 */  bl      AISetStreamVolLeft
/* 0B2CC8 800B8268 7FA3EB78 */  mr      r3, r29
/* 0B2CCC 800B826C 4800013D */  bl      AISetStreamVolRight
lbl_800B8270:
/* 0B2CD0 800B8270 BB410010 */  lmw     r26, 0x10(r1)
/* 0B2CD4 800B8274 8001002C */  lwz     r0, 0x2c(r1)
/* 0B2CD8 800B8278 38210028 */  addi    r1, r1, 0x28
/* 0B2CDC 800B827C 7C0803A6 */  mtlr    r0
/* 0B2CE0 800B8280 4E800020 */  blr     

glabel AIGetDSPSampleRate
/* 0B2CE4 800B8284 3C60CC00 */  lis     r3, AI_REGS_BASE@ha
/* 0B2CE8 800B8288 80036C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r3)
/* 0B2CEC 800B828C 5400D7FE */  rlwinm  r0, r0, 0x1a, 0x1f, 0x1f
/* 0B2CF0 800B8290 68030001 */  xori    r3, r0, 1
/* 0B2CF4 800B8294 4E800020 */  blr     

__AI_set_stream_sample_rate:
/* 0B2CF8 800B8298 7C0802A6 */  mflr    r0
/* 0B2CFC 800B829C 90010004 */  stw     r0, 4(r1)
/* 0B2D00 800B82A0 9421FFD0 */  stwu    r1, -0x30(r1)
/* 0B2D04 800B82A4 BF210014 */  stmw    r25, 0x14(r1)
/* 0B2D08 800B82A8 7C791B78 */  mr      r25, r3
/* 0B2D0C 800B82AC 480000C1 */  bl      AIGetStreamSampleRate
/* 0B2D10 800B82B0 7C191840 */  cmplw   r25, r3
/* 0B2D14 800B82B4 418200A4 */  beq     lbl_800B8358
/* 0B2D18 800B82B8 3FE0CC00 */  lis     r31, AI_REGS_BASE@ha
/* 0B2D1C 800B82BC 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D20 800B82C0 540007FE */  clrlwi  r0, r0, 0x1f
/* 0B2D24 800B82C4 7C1D0378 */  mr      r29, r0
/* 0B2D28 800B82C8 480000D1 */  bl      AIGetStreamVolLeft
/* 0B2D2C 800B82CC 7C7C1B78 */  mr      r28, r3
/* 0B2D30 800B82D0 480000F5 */  bl      AIGetStreamVolRight
/* 0B2D34 800B82D4 3B630000 */  addi    r27, r3, 0
/* 0B2D38 800B82D8 38600000 */  li      r3, 0
/* 0B2D3C 800B82DC 480000CD */  bl      AISetStreamVolRight
/* 0B2D40 800B82E0 38600000 */  li      r3, 0
/* 0B2D44 800B82E4 48000099 */  bl      AISetStreamVolLeft
/* 0B2D48 800B82E8 807F6C00 */  lwz     r3, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D4C 800B82EC 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D50 800B82F0 547A0672 */  rlwinm  r26, r3, 0, 0x19, 0x19
/* 0B2D54 800B82F4 540006B0 */  rlwinm  r0, r0, 0, 0x1a, 0x18
/* 0B2D58 800B82F8 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D5C 800B82FC 4BFE6A01 */  bl      OSDisableInterrupts
/* 0B2D60 800B8300 7C7E1B78 */  mr      r30, r3
/* 0B2D64 800B8304 480003BD */  bl      __AI_SRC_INIT
/* 0B2D68 800B8308 809F6C00 */  lwz     r4, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D6C 800B830C 5720083C */  slwi    r0, r25, 1
/* 0B2D70 800B8310 387E0000 */  addi    r3, r30, 0
/* 0B2D74 800B8314 7C84D378 */  or      r4, r4, r26
/* 0B2D78 800B8318 909F6C00 */  stw     r4, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D7C 800B831C 809F6C00 */  lwz     r4, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D80 800B8320 548406F2 */  rlwinm  r4, r4, 0, 0x1b, 0x19
/* 0B2D84 800B8324 60840020 */  ori     r4, r4, 0x20
/* 0B2D88 800B8328 909F6C00 */  stw     r4, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D8C 800B832C 809F6C00 */  lwz     r4, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D90 800B8330 548407FA */  rlwinm  r4, r4, 0, 0x1f, 0x1d
/* 0B2D94 800B8334 7C800378 */  or      r0, r4, r0
/* 0B2D98 800B8338 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2D9C 800B833C 4BFE69E9 */  bl      OSRestoreInterrupts
/* 0B2DA0 800B8340 7FA3EB78 */  mr      r3, r29
/* 0B2DA4 800B8344 4BFFFD79 */  bl      AISetStreamPlayState
/* 0B2DA8 800B8348 7F83E378 */  mr      r3, r28
/* 0B2DAC 800B834C 48000031 */  bl      AISetStreamVolLeft
/* 0B2DB0 800B8350 7F63DB78 */  mr      r3, r27
/* 0B2DB4 800B8354 48000055 */  bl      AISetStreamVolRight
lbl_800B8358:
/* 0B2DB8 800B8358 BB210014 */  lmw     r25, 0x14(r1)
/* 0B2DBC 800B835C 80010034 */  lwz     r0, 0x34(r1)
/* 0B2DC0 800B8360 38210030 */  addi    r1, r1, 0x30
/* 0B2DC4 800B8364 7C0803A6 */  mtlr    r0
/* 0B2DC8 800B8368 4E800020 */  blr     

glabel AIGetStreamSampleRate
/* 0B2DCC 800B836C 3C60CC00 */  lis     r3, AI_REGS_BASE@ha
/* 0B2DD0 800B8370 80036C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r3)
/* 0B2DD4 800B8374 5403FFFE */  rlwinm  r3, r0, 0x1f, 0x1f, 0x1f
/* 0B2DD8 800B8378 4E800020 */  blr     

glabel AISetStreamVolLeft
/* 0B2DDC 800B837C 3C80CC00 */  lis     r4, AI_REGS_BASE@ha
/* 0B2DE0 800B8380 38846C00 */  addi    r4, r4, AI_REGS_BASE@l
/* 0B2DE4 800B8384 80040004 */  lwz     r0, AI_VR(r4)
/* 0B2DE8 800B8388 5400002E */  rlwinm  r0, r0, 0, 0, 0x17
/* 0B2DEC 800B838C 5060063E */  rlwimi  r0, r3, 0, 0x18, 0x1f
/* 0B2DF0 800B8390 90040004 */  stw     r0, AI_VR(r4)
/* 0B2DF4 800B8394 4E800020 */  blr     

glabel AIGetStreamVolLeft
/* 0B2DF8 800B8398 3C60CC00 */  lis     r3, AI_REGS_BASE@ha
/* 0B2DFC 800B839C 80036C04 */  lwz     r0, (AI_REGS_BASE + AI_VR)@l(r3)
/* 0B2E00 800B83A0 5403063E */  clrlwi  r3, r0, 0x18
/* 0B2E04 800B83A4 4E800020 */  blr     

glabel AISetStreamVolRight
/* 0B2E08 800B83A8 3C80CC00 */  lis     r4, AI_REGS_BASE@ha
/* 0B2E0C 800B83AC 38846C00 */  addi    r4, r4, AI_REGS_BASE@l
/* 0B2E10 800B83B0 80040004 */  lwz     r0, AI_VR(r4)
/* 0B2E14 800B83B4 5400061E */  rlwinm  r0, r0, 0, 0x18, 0xf
/* 0B2E18 800B83B8 5060442E */  rlwimi  r0, r3, 8, 0x10, 0x17
/* 0B2E1C 800B83BC 90040004 */  stw     r0, AI_VR(r4)
/* 0B2E20 800B83C0 4E800020 */  blr     

glabel AIGetStreamVolRight
/* 0B2E24 800B83C4 3C60CC00 */  lis     r3, AI_REGS_BASE@ha
/* 0B2E28 800B83C8 80036C04 */  lwz     r0, (AI_REGS_BASE + AI_VR)@l(r3)
/* 0B2E2C 800B83CC 5403C63E */  rlwinm  r3, r0, 0x18, 0x18, 0x1f
/* 0B2E30 800B83D0 4E800020 */  blr     

glabel AIInit
/* 0B2E34 800B83D4 7C0802A6 */  mflr    r0
/* 0B2E38 800B83D8 90010004 */  stw     r0, 4(r1)
/* 0B2E3C 800B83DC 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0B2E40 800B83E0 93E10014 */  stw     r31, 0x14(r1)
/* 0B2E44 800B83E4 93C10010 */  stw     r30, 0x10(r1)
/* 0B2E48 800B83E8 3BC30000 */  addi    r30, r3, 0
/* 0B2E4C 800B83EC 800D8E40 */  lwz     r0, __AI_init_flag@sda21(r13)
/* 0B2E50 800B83F0 2C000001 */  cmpwi   r0, 1
/* 0B2E54 800B83F4 41820134 */  beq     lbl_800B8528
/* 0B2E58 800B83F8 806D8850 */  lwz     r3, __AIVersion@sda21(r13)
/* 0B2E5C 800B83FC 4BFE4295 */  bl      OSRegisterVersion
/* 0B2E60 800B8400 3C608000 */  lis     r3, 0x8000
/* 0B2E64 800B8404 800300F8 */  lwz     r0, 0xf8(r3)
/* 0B2E68 800B8408 3C60431C */  lis     r3, 0x431c
/* 0B2E6C 800B840C 3C800001 */  lis     r4, 1
/* 0B2E70 800B8410 5400F0BE */  srwi    r0, r0, 2
/* 0B2E74 800B8414 3863DE83 */  addi    r3, r3, -8573
/* 0B2E78 800B8418 7C030016 */  mulhwu  r0, r3, r0
/* 0B2E7C 800B841C 54098BFE */  srwi    r9, r0, 0xf
/* 0B2E80 800B8420 38A4A428 */  addi    r5, r4, -23512
/* 0B2E84 800B8424 3864A410 */  addi    r3, r4, -23536
/* 0B2E88 800B8428 3804F618 */  addi    r0, r4, -2536
/* 0B2E8C 800B842C 3C801062 */  lis     r4, 0x1062
/* 0B2E90 800B8430 7CE929D6 */  mullw   r7, r9, r5
/* 0B2E94 800B8434 39444DD3 */  addi    r10, r4, 0x4dd3
/* 0B2E98 800B8438 7CA919D6 */  mullw   r5, r9, r3
/* 0B2E9C 800B843C 7C8901D6 */  mullw   r4, r9, r0
/* 0B2EA0 800B8440 1D097B24 */  mulli   r8, r9, 0x7b24
/* 0B2EA4 800B8444 1C690BB8 */  mulli   r3, r9, 0xbb8
/* 0B2EA8 800B8448 7D0A4016 */  mulhwu  r8, r10, r8
/* 0B2EAC 800B844C 7CEA3816 */  mulhwu  r7, r10, r7
/* 0B2EB0 800B8450 7CAA2816 */  mulhwu  r5, r10, r5
/* 0B2EB4 800B8454 7C8A2016 */  mulhwu  r4, r10, r4
/* 0B2EB8 800B8458 7C6A1816 */  mulhwu  r3, r10, r3
/* 0B2EBC 800B845C 5508BA7E */  srwi    r8, r8, 9
/* 0B2EC0 800B8460 54E7BA7E */  srwi    r7, r7, 9
/* 0B2EC4 800B8464 910D8E4C */  stw     r8, (bound_32KHz + 4)@sda21(r13)
/* 0B2EC8 800B8468 54A5BA7E */  srwi    r5, r5, 9
/* 0B2ECC 800B846C 5484BA7E */  srwi    r4, r4, 9
/* 0B2ED0 800B8470 90ED8E54 */  stw     r7, (bound_48KHz + 4)@sda21(r13)
/* 0B2ED4 800B8474 3BE00000 */  li      r31, 0
/* 0B2ED8 800B8478 5463BA7E */  srwi    r3, r3, 9
/* 0B2EDC 800B847C 90AD8E5C */  stw     r5, (min_wait + 4)@sda21(r13)
/* 0B2EE0 800B8480 3CC0CC00 */  lis     r6, AI_REGS_BASE@ha
/* 0B2EE4 800B8484 906D8E6C */  stw     r3, (buffer + 4)@sda21(r13)
/* 0B2EE8 800B8488 38600001 */  li      r3, 1
/* 0B2EEC 800B848C 80066C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r6)
/* 0B2EF0 800B8490 908D8E64 */  stw     r4, (max_wait + 4)@sda21(r13)
/* 0B2EF4 800B8494 540006F2 */  rlwinm  r0, r0, 0, 0x1b, 0x19
/* 0B2EF8 800B8498 60000020 */  ori     r0, r0, 0x20
/* 0B2EFC 800B849C 93ED8E48 */  stw     r31, bound_32KHz@sda21(r13)
/* 0B2F00 800B84A0 93ED8E50 */  stw     r31, bound_48KHz@sda21(r13)
/* 0B2F04 800B84A4 93ED8E58 */  stw     r31, min_wait@sda21(r13)
/* 0B2F08 800B84A8 93ED8E60 */  stw     r31, max_wait@sda21(r13)
/* 0B2F0C 800B84AC 93ED8E68 */  stw     r31, buffer@sda21(r13)
/* 0B2F10 800B84B0 80A66C04 */  lwz     r5, (AI_REGS_BASE + AI_VR)@l(r6)
/* 0B2F14 800B84B4 90066C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r6)
/* 0B2F18 800B84B8 54A0061E */  rlwinm  r0, r5, 0, 0x18, 0xf
/* 0B2F1C 800B84BC 60000000 */  nop     
/* 0B2F20 800B84C0 90066C04 */  stw     r0, (AI_REGS_BASE + AI_VR)@l(r6)
/* 0B2F24 800B84C4 80066C04 */  lwz     r0, (AI_REGS_BASE + AI_VR)@l(r6)
/* 0B2F28 800B84C8 5400002E */  rlwinm  r0, r0, 0, 0, 0x17
/* 0B2F2C 800B84CC 60000000 */  nop     
/* 0B2F30 800B84D0 90066C04 */  stw     r0, (AI_REGS_BASE + AI_VR)@l(r6)
/* 0B2F34 800B84D4 93E66C0C */  stw     r31, (AI_REGS_BASE + AI_IT)@l(r6)
/* 0B2F38 800B84D8 4BFFFDC1 */  bl      __AI_set_stream_sample_rate
/* 0B2F3C 800B84DC 38600000 */  li      r3, 0
/* 0B2F40 800B84E0 4BFFFCC5 */  bl      AISetDSPSampleRate
/* 0B2F44 800B84E4 3C60800C */  lis     r3, __AIDHandler@ha
/* 0B2F48 800B84E8 93ED8E30 */  stw     r31, __AIS_Callback@sda21(r13)
/* 0B2F4C 800B84EC 388385BC */  addi    r4, r3, __AIDHandler@l
/* 0B2F50 800B84F0 93ED8E34 */  stw     r31, __AID_Callback@sda21(r13)
/* 0B2F54 800B84F4 38600005 */  li      r3, 5
/* 0B2F58 800B84F8 93CD8E38 */  stw     r30, __CallbackStack@sda21(r13)
/* 0B2F5C 800B84FC 4BFE684D */  bl      __OSSetInterruptHandler
/* 0B2F60 800B8500 3C600400 */  lis     r3, 0x400
/* 0B2F64 800B8504 4BFE6C49 */  bl      __OSUnmaskInterrupts
/* 0B2F68 800B8508 3C60800C */  lis     r3, __AISHandler@ha
/* 0B2F6C 800B850C 38838540 */  addi    r4, r3, __AISHandler@l
/* 0B2F70 800B8510 38600008 */  li      r3, 8
/* 0B2F74 800B8514 4BFE6835 */  bl      __OSSetInterruptHandler
/* 0B2F78 800B8518 3C600080 */  lis     r3, 0x80
/* 0B2F7C 800B851C 4BFE6C31 */  bl      __OSUnmaskInterrupts
/* 0B2F80 800B8520 38000001 */  li      r0, 1
/* 0B2F84 800B8524 900D8E40 */  stw     r0, __AI_init_flag@sda21(r13)
lbl_800B8528:
/* 0B2F88 800B8528 8001001C */  lwz     r0, 0x1c(r1)
/* 0B2F8C 800B852C 83E10014 */  lwz     r31, 0x14(r1)
/* 0B2F90 800B8530 83C10010 */  lwz     r30, 0x10(r1)
/* 0B2F94 800B8534 38210018 */  addi    r1, r1, 0x18
/* 0B2F98 800B8538 7C0803A6 */  mtlr    r0
/* 0B2F9C 800B853C 4E800020 */  blr     

__AISHandler:
/* 0B2FA0 800B8540 7C0802A6 */  mflr    r0
/* 0B2FA4 800B8544 90010004 */  stw     r0, 4(r1)
/* 0B2FA8 800B8548 9421FD20 */  stwu    r1, -0x2e0(r1)
/* 0B2FAC 800B854C 93E102DC */  stw     r31, 0x2dc(r1)
/* 0B2FB0 800B8550 3FE0CC00 */  lis     r31, AI_REGS_BASE@ha
/* 0B2FB4 800B8554 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2FB8 800B8558 38610010 */  addi    r3, r1, 0x10
/* 0B2FBC 800B855C 93C102D8 */  stw     r30, 0x2d8(r1)
/* 0B2FC0 800B8560 60000008 */  ori     r0, r0, 8
/* 0B2FC4 800B8564 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B2FC8 800B8568 3BC40000 */  addi    r30, r4, 0
/* 0B2FCC 800B856C 4BFE5C39 */  bl      OSClearContext
/* 0B2FD0 800B8570 38610010 */  addi    r3, r1, 0x10
/* 0B2FD4 800B8574 4BFE5A69 */  bl      OSSetCurrentContext
/* 0B2FD8 800B8578 818D8E30 */  lwz     r12, __AIS_Callback@sda21(r13)
/* 0B2FDC 800B857C 280C0000 */  cmplwi  r12, 0
/* 0B2FE0 800B8580 41820014 */  beq     lbl_800B8594
/* 0B2FE4 800B8584 387F6C00 */  addi    r3, r31, AI_REGS_BASE@l
/* 0B2FE8 800B8588 7D8803A6 */  mtlr    r12
/* 0B2FEC 800B858C 80630008 */  lwz     r3, AI_SCNT(r3)
/* 0B2FF0 800B8590 4E800021 */  blrl    
lbl_800B8594:
/* 0B2FF4 800B8594 38610010 */  addi    r3, r1, 0x10
/* 0B2FF8 800B8598 4BFE5C0D */  bl      OSClearContext
/* 0B2FFC 800B859C 7FC3F378 */  mr      r3, r30
/* 0B3000 800B85A0 4BFE5A3D */  bl      OSSetCurrentContext
/* 0B3004 800B85A4 800102E4 */  lwz     r0, 0x2e4(r1)
/* 0B3008 800B85A8 83E102DC */  lwz     r31, 0x2dc(r1)
/* 0B300C 800B85AC 83C102D8 */  lwz     r30, 0x2d8(r1)
/* 0B3010 800B85B0 382102E0 */  addi    r1, r1, 0x2e0
/* 0B3014 800B85B4 7C0803A6 */  mtlr    r0
/* 0B3018 800B85B8 4E800020 */  blr     

__AIDHandler:
/* 0B301C 800B85BC 7C0802A6 */  mflr    r0
/* 0B3020 800B85C0 3C60CC00 */  lis     r3, DSP_REGS_BASE@ha
/* 0B3024 800B85C4 90010004 */  stw     r0, 4(r1)
/* 0B3028 800B85C8 38635000 */  addi    r3, r3, DSP_REGS_BASE@l
/* 0B302C 800B85CC 3800FF5F */  li      r0, -161
/* 0B3030 800B85D0 9421FD20 */  stwu    r1, -0x2e0(r1)
/* 0B3034 800B85D4 93E102DC */  stw     r31, 0x2dc(r1)
/* 0B3038 800B85D8 3BE40000 */  addi    r31, r4, 0
/* 0B303C 800B85DC A0A3000A */  lhz     r5, DSP_0A(r3)
/* 0B3040 800B85E0 7CA00038 */  and     r0, r5, r0
/* 0B3044 800B85E4 60000008 */  ori     r0, r0, 8
/* 0B3048 800B85E8 B003000A */  sth     r0, DSP_0A(r3)
/* 0B304C 800B85EC 38610010 */  addi    r3, r1, 0x10
/* 0B3050 800B85F0 4BFE5BB5 */  bl      OSClearContext
/* 0B3054 800B85F4 38610010 */  addi    r3, r1, 0x10
/* 0B3058 800B85F8 4BFE59E5 */  bl      OSSetCurrentContext
/* 0B305C 800B85FC 806D8E34 */  lwz     r3, __AID_Callback@sda21(r13)
/* 0B3060 800B8600 28030000 */  cmplwi  r3, 0
/* 0B3064 800B8604 41820040 */  beq     lbl_800B8644
/* 0B3068 800B8608 800D8E44 */  lwz     r0, __AID_Active@sda21(r13)
/* 0B306C 800B860C 2C000000 */  cmpwi   r0, 0
/* 0B3070 800B8610 40820034 */  bne     lbl_800B8644
/* 0B3074 800B8614 800D8E38 */  lwz     r0, __CallbackStack@sda21(r13)
/* 0B3078 800B8618 38800001 */  li      r4, 1
/* 0B307C 800B861C 908D8E44 */  stw     r4, __AID_Active@sda21(r13)
/* 0B3080 800B8620 28000000 */  cmplwi  r0, 0
/* 0B3084 800B8624 4182000C */  beq     lbl_800B8630
/* 0B3088 800B8628 48000041 */  bl      __AICallbackStackSwitch
/* 0B308C 800B862C 48000010 */  b       lbl_800B863C
lbl_800B8630:
/* 0B3090 800B8630 39830000 */  addi    r12, r3, 0
/* 0B3094 800B8634 7D8803A6 */  mtlr    r12
/* 0B3098 800B8638 4E800021 */  blrl    
lbl_800B863C:
/* 0B309C 800B863C 38000000 */  li      r0, 0
/* 0B30A0 800B8640 900D8E44 */  stw     r0, __AID_Active@sda21(r13)
lbl_800B8644:
/* 0B30A4 800B8644 38610010 */  addi    r3, r1, 0x10
/* 0B30A8 800B8648 4BFE5B5D */  bl      OSClearContext
/* 0B30AC 800B864C 7FE3FB78 */  mr      r3, r31
/* 0B30B0 800B8650 4BFE598D */  bl      OSSetCurrentContext
/* 0B30B4 800B8654 800102E4 */  lwz     r0, 0x2e4(r1)
/* 0B30B8 800B8658 83E102DC */  lwz     r31, 0x2dc(r1)
/* 0B30BC 800B865C 382102E0 */  addi    r1, r1, 0x2e0
/* 0B30C0 800B8660 7C0803A6 */  mtlr    r0
/* 0B30C4 800B8664 4E800020 */  blr     

__AICallbackStackSwitch:
/* 0B30C8 800B8668 7C0802A6 */  mflr    r0
/* 0B30CC 800B866C 90010004 */  stw     r0, 4(r1)
/* 0B30D0 800B8670 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0B30D4 800B8674 93E10014 */  stw     r31, 0x14(r1)
/* 0B30D8 800B8678 7C7F1B78 */  mr      r31, r3
/* 0B30DC 800B867C 3CA08013 */  lis     r5, __OldStack@ha
/* 0B30E0 800B8680 38A55B1C */  addi    r5, r5, __OldStack@l
/* 0B30E4 800B8684 90250000 */  stw     r1, 0(r5)
/* 0B30E8 800B8688 3CA08013 */  lis     r5, __CallbackStack@ha
/* 0B30EC 800B868C 38A55B18 */  addi    r5, r5, __CallbackStack@l
/* 0B30F0 800B8690 80250000 */  lwz     r1, 0(r5)
/* 0B30F4 800B8694 3821FFF8 */  addi    r1, r1, -8
/* 0B30F8 800B8698 7FE803A6 */  mtlr    r31
/* 0B30FC 800B869C 4E800021 */  blrl    
/* 0B3100 800B86A0 3CA08013 */  lis     r5, __OldStack@ha
/* 0B3104 800B86A4 38A55B1C */  addi    r5, r5, __OldStack@l
/* 0B3108 800B86A8 80250000 */  lwz     r1, 0(r5)
/* 0B310C 800B86AC 8001001C */  lwz     r0, 0x1c(r1)
/* 0B3110 800B86B0 83E10014 */  lwz     r31, 0x14(r1)
/* 0B3114 800B86B4 38210018 */  addi    r1, r1, 0x18
/* 0B3118 800B86B8 7C0803A6 */  mtlr    r0
/* 0B311C 800B86BC 4E800020 */  blr     

__AI_SRC_INIT:
/* 0B3120 800B86C0 7C0802A6 */  mflr    r0
/* 0B3124 800B86C4 90010004 */  stw     r0, 4(r1)
/* 0B3128 800B86C8 9421FFD0 */  stwu    r1, -0x30(r1)
/* 0B312C 800B86CC BF410018 */  stmw    r26, 0x18(r1)
/* 0B3130 800B86D0 38800000 */  li      r4, 0
/* 0B3134 800B86D4 38600000 */  li      r3, 0
/* 0B3138 800B86D8 38000000 */  li      r0, 0
/* 0B313C 800B86DC 3B800000 */  li      r28, 0
/* 0B3140 800B86E0 3BA00000 */  li      r29, 0
/* 0B3144 800B86E4 48000004 */  b       lbl_800B86E8
lbl_800B86E8:
/* 0B3148 800B86E8 3FE0CC00 */  lis     r31, AI_REGS_BASE@ha
/* 0B314C 800B86EC 48000004 */  b       lbl_800B86F0
lbl_800B86F0:
/* 0B3150 800B86F0 48000164 */  b       lbl_800B8854
lbl_800B86F4:
/* 0B3154 800B86F4 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B3158 800B86F8 3BDF6C00 */  addi    r30, r31, AI_REGS_BASE@l
/* 0B315C 800B86FC 3BDE0008 */  addi    r30, r30, AI_SCNT
/* 0B3160 800B8700 540006F2 */  rlwinm  r0, r0, 0, 0x1b, 0x19
/* 0B3164 800B8704 60000020 */  ori     r0, r0, 0x20
/* 0B3168 800B8708 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B316C 800B870C 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B3170 800B8710 540007FA */  rlwinm  r0, r0, 0, 0x1f, 0x1d
/* 0B3174 800B8714 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B3178 800B8718 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B317C 800B871C 5400003C */  rlwinm  r0, r0, 0, 0, 0x1e
/* 0B3180 800B8720 60000001 */  ori     r0, r0, 1
/* 0B3184 800B8724 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B3188 800B8728 807E0000 */  lwz     r3, 0(r30)
/* 0B318C 800B872C 48000004 */  b       lbl_800B8730
lbl_800B8730:
/* 0B3190 800B8730 48000004 */  b       lbl_800B8734
lbl_800B8734:
/* 0B3194 800B8734 801E0000 */  lwz     r0, 0(r30)
/* 0B3198 800B8738 7C030040 */  cmplw   r3, r0
/* 0B319C 800B873C 4182FFF8 */  beq     lbl_800B8734
/* 0B31A0 800B8740 4BFE9B69 */  bl      OSGetTime
/* 0B31A4 800B8744 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B31A8 800B8748 7C9A2378 */  mr      r26, r4
/* 0B31AC 800B874C 7C7B1B78 */  mr      r27, r3
/* 0B31B0 800B8750 540007FA */  rlwinm  r0, r0, 0, 0x1f, 0x1d
/* 0B31B4 800B8754 60000002 */  ori     r0, r0, 2
/* 0B31B8 800B8758 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B31BC 800B875C 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B31C0 800B8760 5400003C */  rlwinm  r0, r0, 0, 0, 0x1e
/* 0B31C4 800B8764 60000001 */  ori     r0, r0, 1
/* 0B31C8 800B8768 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B31CC 800B876C 807E0000 */  lwz     r3, 0(r30)
/* 0B31D0 800B8770 48000004 */  b       lbl_800B8774
lbl_800B8774:
/* 0B31D4 800B8774 48000004 */  b       lbl_800B8778
lbl_800B8778:
/* 0B31D8 800B8778 801E0000 */  lwz     r0, 0(r30)
/* 0B31DC 800B877C 7C030040 */  cmplw   r3, r0
/* 0B31E0 800B8780 4182FFF8 */  beq     lbl_800B8778
/* 0B31E4 800B8784 4BFE9B25 */  bl      OSGetTime
/* 0B31E8 800B8788 7D1A2010 */  subfc   r8, r26, r4
/* 0B31EC 800B878C 818D8E4C */  lwz     r12, (bound_32KHz + 4)@sda21(r13)
/* 0B31F0 800B8790 80BF6C00 */  lwz     r5, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B31F4 800B8794 7CFB1910 */  subfe   r7, r27, r3
/* 0B31F8 800B8798 814D8E6C */  lwz     r10, (buffer + 4)@sda21(r13)
/* 0B31FC 800B879C 6CE78000 */  xoris   r7, r7, 0x8000
/* 0B3200 800B87A0 54A507FA */  rlwinm  r5, r5, 0, 0x1f, 0x1d
/* 0B3204 800B87A4 816D8E48 */  lwz     r11, bound_32KHz@sda21(r13)
/* 0B3208 800B87A8 7CCA6010 */  subfc   r6, r10, r12
/* 0B320C 800B87AC 812D8E68 */  lwz     r9, buffer@sda21(r13)
/* 0B3210 800B87B0 90BF6C00 */  stw     r5, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B3214 800B87B4 7C095910 */  subfe   r0, r9, r11
/* 0B3218 800B87B8 6C058000 */  xoris   r5, r0, 0x8000
/* 0B321C 800B87BC 7C064010 */  subfc   r0, r6, r8
/* 0B3220 800B87C0 801F6C00 */  lwz     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B3224 800B87C4 7CA53910 */  subfe   r5, r5, r7
/* 0B3228 800B87C8 7CA73910 */  subfe   r5, r7, r7
/* 0B322C 800B87CC 7CA500D0 */  neg     r5, r5
/* 0B3230 800B87D0 5400003C */  rlwinm  r0, r0, 0, 0, 0x1e
/* 0B3234 800B87D4 2C050000 */  cmpwi   r5, 0
/* 0B3238 800B87D8 901F6C00 */  stw     r0, (AI_REGS_BASE + AI_CR)@l(r31)
/* 0B323C 800B87DC 41820014 */  beq     lbl_800B87F0
/* 0B3240 800B87E0 83AD8E58 */  lwz     r29, min_wait@sda21(r13)
/* 0B3244 800B87E4 38000001 */  li      r0, 1
/* 0B3248 800B87E8 838D8E5C */  lwz     r28, (min_wait + 4)@sda21(r13)
/* 0B324C 800B87EC 48000068 */  b       lbl_800B8854
lbl_800B87F0:
/* 0B3250 800B87F0 7CCC5014 */  addc    r6, r12, r10
/* 0B3254 800B87F4 7C0B4914 */  adde    r0, r11, r9
/* 0B3258 800B87F8 6C058000 */  xoris   r5, r0, 0x8000
/* 0B325C 800B87FC 7C064010 */  subfc   r0, r6, r8
/* 0B3260 800B8800 7CA53910 */  subfe   r5, r5, r7
/* 0B3264 800B8804 7CA73910 */  subfe   r5, r7, r7
/* 0B3268 800B8808 7CA500D0 */  neg     r5, r5
/* 0B326C 800B880C 2C050000 */  cmpwi   r5, 0
/* 0B3270 800B8810 40820040 */  bne     lbl_800B8850
/* 0B3274 800B8814 80AD8E54 */  lwz     r5, (bound_48KHz + 4)@sda21(r13)
/* 0B3278 800B8818 800D8E50 */  lwz     r0, bound_48KHz@sda21(r13)
/* 0B327C 800B881C 7CCA2810 */  subfc   r6, r10, r5
/* 0B3280 800B8820 7C090110 */  subfe   r0, r9, r0
/* 0B3284 800B8824 6C058000 */  xoris   r5, r0, 0x8000
/* 0B3288 800B8828 7C064010 */  subfc   r0, r6, r8
/* 0B328C 800B882C 7CA53910 */  subfe   r5, r5, r7
/* 0B3290 800B8830 7CA73910 */  subfe   r5, r7, r7
/* 0B3294 800B8834 7CA500D0 */  neg     r5, r5
/* 0B3298 800B8838 2C050000 */  cmpwi   r5, 0
/* 0B329C 800B883C 41820014 */  beq     lbl_800B8850
/* 0B32A0 800B8840 83AD8E60 */  lwz     r29, max_wait@sda21(r13)
/* 0B32A4 800B8844 38000001 */  li      r0, 1
/* 0B32A8 800B8848 838D8E64 */  lwz     r28, (max_wait + 4)@sda21(r13)
/* 0B32AC 800B884C 48000008 */  b       lbl_800B8854
lbl_800B8850:
/* 0B32B0 800B8850 38000000 */  li      r0, 0
lbl_800B8854:
/* 0B32B4 800B8854 28000000 */  cmplwi  r0, 0
/* 0B32B8 800B8858 4182FE9C */  beq     lbl_800B86F4
/* 0B32BC 800B885C 7F64E014 */  addc    r27, r4, r28
/* 0B32C0 800B8860 7F43E914 */  adde    r26, r3, r29
/* 0B32C4 800B8864 48000004 */  b       lbl_800B8868
lbl_800B8868:
/* 0B32C8 800B8868 48000004 */  b       lbl_800B886C
lbl_800B886C:
/* 0B32CC 800B886C 4BFE9A3D */  bl      OSGetTime
/* 0B32D0 800B8870 6C658000 */  xoris   r5, r3, 0x8000
/* 0B32D4 800B8874 6F438000 */  xoris   r3, r26, 0x8000
/* 0B32D8 800B8878 7C1B2010 */  subfc   r0, r27, r4
/* 0B32DC 800B887C 7C632910 */  subfe   r3, r3, r5
/* 0B32E0 800B8880 7C652910 */  subfe   r3, r5, r5
/* 0B32E4 800B8884 7C6300D0 */  neg     r3, r3
/* 0B32E8 800B8888 2C030000 */  cmpwi   r3, 0
/* 0B32EC 800B888C 4082FFE0 */  bne     lbl_800B886C
/* 0B32F0 800B8890 BB410018 */  lmw     r26, 0x18(r1)
/* 0B32F4 800B8894 80010034 */  lwz     r0, 0x34(r1)
/* 0B32F8 800B8898 38210030 */  addi    r1, r1, 0x30
/* 0B32FC 800B889C 7C0803A6 */  mtlr    r0
/* 0B3300 800B88A0 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000F0608 800F3588 0044 */
D_800F3588:
    .asciz "<< Dolphin SDK - AI\trelease build: Apr 17 2003 12:33:54 (0x2301) >>"
    .balign 4

.section .sdata, "wa"

.balign 8

/* 000F17B0 80135530 0004 */
glabel __AIVersion
    .long D_800F3588

.section .sbss, "wa"

.balign 8

/* 000F1D90 80135B10 0004 */
__AIS_Callback:
    .skip 4

/* 000F1D94 80135B14 0004 */
__AID_Callback:
    .skip 4

/* 000F1D98 80135B18 0004 */
__CallbackStack:
    .skip 4

/* 000F1D9C 80135B1C 0004 */
__OldStack:
    .skip 4

/* 000F1DA0 80135B20 0004 */
__AI_init_flag:
    .skip 4

/* 000F1DA4 80135B24 0004 */
__AID_Active:
    .skip 4

/* 000F1DA8 80135B28 0008 */
bound_32KHz:
    .skip 8

/* 000F1DB0 80135B30 0008 */
bound_48KHz:
    .skip 8

/* 000F1DB8 80135B38 0008 */
min_wait:
    .skip 8

/* 000F1DC0 80135B40 0008 */
max_wait:
    .skip 8

/* 000F1DC8 80135B48 0008 */
buffer:
    .skip 8
