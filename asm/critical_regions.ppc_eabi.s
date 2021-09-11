# critical_regions.ppc_eabi.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __kill_critical_regions
/* 0C9004 800CE5A4 4E800020 */  blr     
