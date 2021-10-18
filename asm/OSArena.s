# OSArena.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel OSGetArenaHi
/* 097EE8 8009D488 806D8B28 */  lwz     r3, __OSArenaHi@sda21(r13)
/* 097EEC 8009D48C 4E800020 */  blr     

glabel OSGetArenaLo
/* 097EF0 8009D490 806D8748 */  lwz     r3, __OSArenaLo@sda21(r13)
/* 097EF4 8009D494 4E800020 */  blr     

glabel OSSetArenaHi
/* 097EF8 8009D498 906D8B28 */  stw     r3, __OSArenaHi@sda21(r13)
/* 097EFC 8009D49C 4E800020 */  blr     

glabel OSSetArenaLo
/* 097F00 8009D4A0 906D8748 */  stw     r3, __OSArenaLo@sda21(r13)
/* 097F04 8009D4A4 4E800020 */  blr     

.section .sdata, "wa"

.balign 8

/* 000F16A8 80135428 0004 */
__OSArenaLo:
    .long 0xFFFFFFFF

.section .sbss, "wa"

.balign 8

/* 000F1A88 80135808 0004 */
__OSArenaHi:
    .skip 4
