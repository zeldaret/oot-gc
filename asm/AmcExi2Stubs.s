# AmcExi2Stubs.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel EXI2_Init
/* 0CCF34 800D24D4 4E800020 */  blr     

glabel EXI2_EnableInterrupts
/* 0CCF38 800D24D8 4E800020 */  blr     

glabel EXI2_Poll
/* 0CCF3C 800D24DC 38600000 */  li      r3, 0
/* 0CCF40 800D24E0 4E800020 */  blr     

glabel EXI2_ReadN
/* 0CCF44 800D24E4 38600000 */  li      r3, 0
/* 0CCF48 800D24E8 4E800020 */  blr     

glabel EXI2_WriteN
/* 0CCF4C 800D24EC 38600000 */  li      r3, 0
/* 0CCF50 800D24F0 4E800020 */  blr     

glabel EXI2_Reserve
/* 0CCF54 800D24F4 4E800020 */  blr     

glabel EXI2_Unreserve
/* 0CCF58 800D24F8 4E800020 */  blr     

glabel AMC_IsStub
/* 0CCF5C 800D24FC 38600001 */  li      r3, 1
/* 0CCF60 800D2500 4E800020 */  blr     


