# float.c
.include "macros.inc"

.section .data, "wa"

.balign 8

/* 000F0EF8 800F3E78 0004 */
glabel __float_nan
    .float nan

.balign 4

/* 000F0EFC 800F3E7C 0004 */
glabel __float_huge
    .float inf
