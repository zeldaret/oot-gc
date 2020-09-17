# hyperbolicsf.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel fabsf__Ff
/* 0CC8DC 800D1E7C FC200A10 */  fabs    f1, f1
/* 0CC8E0 800D1E80 4E800020 */  blr     


