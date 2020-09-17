# mutex_TRK.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKInitializeMutex
/* 0C61B4 800CB754 38600000 */  li		r3, 0
/* 0C61B8 800CB758 4E800020 */  blr		

glabel TRKAcquireMutex
/* 0C61BC 800CB75C 38600000 */  li		r3, 0
/* 0C61C0 800CB760 4E800020 */  blr		

glabel TRKReleaseMutex
/* 0C61C4 800CB764 38600000 */  li		r3, 0
/* 0C61C8 800CB768 4E800020 */  blr		


