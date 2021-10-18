# movie.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel MovieDraw
/* 00A22C 8000F7CC 7C0802A6 */  mflr    r0
/* 00A230 8000F7D0 38800000 */  li      r4, 0
/* 00A234 8000F7D4 90010004 */  stw     r0, 4(r1)
/* 00A238 8000F7D8 38A0FFF8 */  li      r5, -8
/* 00A23C 8000F7DC 38C00280 */  li      r6, 0x280
/* 00A240 8000F7E0 9421FFF8 */  stwu    r1, -8(r1)
/* 00A244 8000F7E4 38E001B8 */  li      r7, 0x1b8
/* 00A248 8000F7E8 806D88BC */  lwz     r3, rmode@sda21(r13)
/* 00A24C 8000F7EC 48000F31 */  bl      THPPlayerDrawCurrentFrame
/* 00A250 8000F7F0 48001029 */  bl      THPPlayerDrawDone
/* 00A254 8000F7F4 8001000C */  lwz     r0, 0xc(r1)
/* 00A258 8000F7F8 38210008 */  addi    r1, r1, 8
/* 00A25C 8000F7FC 7C0803A6 */  mtlr    r0
/* 00A260 8000F800 4E800020 */  blr     

glabel MovieInit
/* 00A264 8000F804 7C0802A6 */  mflr    r0
/* 00A268 8000F808 38600000 */  li      r3, 0
/* 00A26C 8000F80C 90010004 */  stw     r0, 4(r1)
/* 00A270 8000F810 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00A274 8000F814 4800007D */  bl      THPPlayerInit
/* 00A278 8000F818 38600006 */  li      r3, 6
/* 00A27C 8000F81C 38810008 */  addi    r4, r1, 8
/* 00A280 8000F820 4BFF8D19 */  bl      simulatorGetArgument
/* 00A284 8000F824 2C030000 */  cmpwi   r3, 0
/* 00A288 8000F828 40820018 */  bne     lbl_8000F840
/* 00A28C 8000F82C 3C60800F */  lis     r3, D_800EA1C8@ha
/* 00A290 8000F830 3863A1C8 */  addi    r3, r3, D_800EA1C8@l
/* 00A294 8000F834 38800000 */  li      r4, 0
/* 00A298 8000F838 48000191 */  bl      THPPlayerOpen
/* 00A29C 8000F83C 48000010 */  b       lbl_8000F84C
lbl_8000F840:
/* 00A2A0 8000F840 80610008 */  lwz     r3, 8(r1)
/* 00A2A4 8000F844 38800000 */  li      r4, 0
/* 00A2A8 8000F848 48000181 */  bl      THPPlayerOpen
lbl_8000F84C:
/* 00A2AC 8000F84C 480003F5 */  bl      THPPlayerCalcNeedMemory
/* 00A2B0 8000F850 7C601B78 */  mr      r0, r3
/* 00A2B4 8000F854 806D8740 */  lwz     r3, __OSCurrHeap@sda21(r13)
/* 00A2B8 8000F858 7C040378 */  mr      r4, r0
/* 00A2BC 8000F85C 4808D669 */  bl      OSAllocFromHeap
/* 00A2C0 8000F860 906D8930 */  stw     r3, gBufferP@sda21(r13)
/* 00A2C4 8000F864 806D8930 */  lwz     r3, gBufferP@sda21(r13)
/* 00A2C8 8000F868 48000481 */  bl      THPPlayerSetBuffer
/* 00A2CC 8000F86C 38600000 */  li      r3, 0
/* 00A2D0 8000F870 38800000 */  li      r4, 0
/* 00A2D4 8000F874 38A00000 */  li      r5, 0
/* 00A2D8 8000F878 480007A9 */  bl      THPPlayerPrepare
/* 00A2DC 8000F87C 48000A19 */  bl      THPPlayerPlay
/* 00A2E0 8000F880 80010014 */  lwz     r0, 0x14(r1)
/* 00A2E4 8000F884 38210010 */  addi    r1, r1, 0x10
/* 00A2E8 8000F888 7C0803A6 */  mtlr    r0
/* 00A2EC 8000F88C 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000E7248 800EA1C8 001E */
D_800EA1C8:
    .asciz "final_zelda_credits_sound.thp"
    .balign 4

.section .sbss, "wa"

.balign 8

/* 000F1890 80135610 0004 */
glabel gBufferP
    .skip 4
