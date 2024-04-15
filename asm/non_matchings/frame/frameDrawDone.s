glabel frameDrawDone
/* 026D44 8002C2E4 7C0802A6 */  mflr    r0
/* 026D48 8002C2E8 90010004 */  stw     r0, 4(r1)
/* 026D4C 8002C2EC 9421FFF0 */  stwu    r1, -0x10(r1)
/* 026D50 8002C2F0 93E1000C */  stw     r31, 0xc(r1)
/* 026D54 8002C2F4 800D89A8 */  lwz     r0, gbFrameValid@sda21(r13)
/* 026D58 8002C2F8 2C000000 */  cmpwi   r0, 0
/* 026D5C 8002C2FC 41820050 */  beq     lbl_8002C34C
/* 026D60 8002C300 800D89DC */  lwz     r0, gNoSwapBuffer@sda21(r13)
/* 026D64 8002C304 3BE00000 */  li      r31, 0
/* 026D68 8002C308 93ED89A8 */  stw     r31, gbFrameValid@sda21(r13)
/* 026D6C 8002C30C 2C000000 */  cmpwi   r0, 0
/* 026D70 8002C310 40820034 */  bne     lbl_8002C344
/* 026D74 8002C314 806D8DAC */  lwz     r3, DemoCurrentBuffer@sda21(r13)
/* 026D78 8002C318 4807B425 */  bl      VISetNextFrameBuffer
/* 026D7C 8002C31C 4807B2F1 */  bl      VIFlush
/* 026D80 8002C320 800D8DAC */  lwz     r0, DemoCurrentBuffer@sda21(r13)
/* 026D84 8002C324 806D8DB4 */  lwz     r3, DemoFrameBuffer1@sda21(r13)
/* 026D88 8002C328 7C001840 */  cmplw   r0, r3
/* 026D8C 8002C32C 40820010 */  bne     lbl_8002C33C
/* 026D90 8002C330 800D8DB0 */  lwz     r0, DemoFrameBuffer2@sda21(r13)
/* 026D94 8002C334 900D8DAC */  stw     r0, DemoCurrentBuffer@sda21(r13)
/* 026D98 8002C338 48000014 */  b       lbl_8002C34C
lbl_8002C33C:
/* 026D9C 8002C33C 906D8DAC */  stw     r3, DemoCurrentBuffer@sda21(r13)
/* 026DA0 8002C340 4800000C */  b       lbl_8002C34C
lbl_8002C344:
/* 026DA4 8002C344 4807B2C9 */  bl      VIFlush
/* 026DA8 8002C348 93ED89DC */  stw     r31, gNoSwapBuffer@sda21(r13)
lbl_8002C34C:
/* 026DAC 8002C34C 80010014 */  lwz     r0, 0x14(r1)
/* 026DB0 8002C350 83E1000C */  lwz     r31, 0xc(r1)
/* 026DB4 8002C354 38210010 */  addi    r1, r1, 0x10
/* 026DB8 8002C358 7C0803A6 */  mtlr    r0
/* 026DBC 8002C35C 4E800020 */  blr     
