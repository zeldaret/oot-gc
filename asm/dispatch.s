# dispatch.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKInitializeDispatcher
/* 0C4A34 800C9FD4 3C608013 */  lis		r3, gTRKDispatchTableSize@ha
/* 0C4A38 800C9FD8 38000020 */  li		r0, 0x20
/* 0C4A3C 800C9FDC 90034548 */  stw		r0, gTRKDispatchTableSize@l(r3)
/* 0C4A40 800C9FE0 38600000 */  li		r3, 0
/* 0C4A44 800C9FE4 4E800020 */  blr		

glabel TRKDispatchMessage
/* 0C4A48 800C9FE8 7C0802A6 */  mflr	r0
/* 0C4A4C 800C9FEC 38800000 */  li		r4, 0
/* 0C4A50 800C9FF0 90010004 */  stw		r0, 4(r1)
/* 0C4A54 800C9FF4 9421FFE8 */  stwu	r1, -0x18(r1)
/* 0C4A58 800C9FF8 93E10014 */  stw		r31, 0x14(r1)
/* 0C4A5C 800C9FFC 3BE00500 */  li		r31, 0x500
/* 0C4A60 800CA000 93C10010 */  stw		r30, 0x10(r1)
/* 0C4A64 800CA004 3BC30000 */  addi	r30, r3, 0
/* 0C4A68 800CA008 4BFFF7A9 */  bl		TRKSetBufferPosition
/* 0C4A6C 800CA00C 387E0000 */  addi	r3, r30, 0
/* 0C4A70 800CA010 38810008 */  addi	r4, r1, 8
/* 0C4A74 800CA014 4BFFFB21 */  bl		TRKReadBuffer1_ui8
/* 0C4A78 800CA018 3C608013 */  lis		r3, gTRKDispatchTableSize@ha
/* 0C4A7C 800CA01C 88810008 */  lbz		r4, 8(r1)
/* 0C4A80 800CA020 80034548 */  lwz		r0, gTRKDispatchTableSize@l(r3)
/* 0C4A84 800CA024 7C040040 */  cmplw	r4, r0
/* 0C4A88 800CA028 40800028 */  bge		lbl_800CA050
/* 0C4A8C 800CA02C 3C60800F */  lis		r3, gTRKDispatchTable@ha
/* 0C4A90 800CA030 5484103A */  slwi	r4, r4, 2
/* 0C4A94 800CA034 38033A20 */  addi	r0, r3, gTRKDispatchTable@l
/* 0C4A98 800CA038 7C602214 */  add		r3, r0, r4
/* 0C4A9C 800CA03C 81830000 */  lwz		r12, 0(r3)
/* 0C4AA0 800CA040 387E0000 */  addi	r3, r30, 0
/* 0C4AA4 800CA044 7D8803A6 */  mtlr	r12
/* 0C4AA8 800CA048 4E800021 */  blrl	
/* 0C4AAC 800CA04C 7C7F1B78 */  mr		r31, r3
lbl_800CA050:
/* 0C4AB0 800CA050 7FE3FB78 */  mr		r3, r31
/* 0C4AB4 800CA054 83E10014 */  lwz		r31, 0x14(r1)
/* 0C4AB8 800CA058 83C10010 */  lwz		r30, 0x10(r1)
/* 0C4ABC 800CA05C 38210018 */  addi	r1, r1, 0x18
/* 0C4AC0 800CA060 80010004 */  lwz		r0, 4(r1)
/* 0C4AC4 800CA064 7C0803A6 */  mtlr	r0
/* 0C4AC8 800CA068 4E800020 */  blr		


.section .data, "wa"

.balign 8

/* 000F0AA0 800F3A20 0084 */
glabel gTRKDispatchTable
    .long TRKDoUnsupported, TRKDoConnect, TRKDoDisconnect, TRKDoReset, TRKDoVersions, TRKDoSupportMask, TRKDoCPUType, TRKDoUnsupported
    .long TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported
    .long TRKDoReadMemory, TRKDoWriteMemory, TRKDoReadRegisters, TRKDoWriteRegisters, TRKDoUnsupported, TRKDoUnsupported, TRKDoFlushCache, TRKDoUnsupported
    .long TRKDoContinue, TRKDoStep, TRKDoStop, TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported, TRKDoUnsupported
    .long 0x00000000


.section .bss, "wa"

.balign 4

/* 001315C8 80134548 0004 */
glabel gTRKDispatchTableSize
    .skip 4


