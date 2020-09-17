# OSLink.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel __OSModuleInit
/* 099FC8 8009F568 3C808000 */  lis		r4, 0x8000
/* 099FCC 8009F56C 38000000 */  li		r0, 0
/* 099FD0 8009F570 900430CC */  stw		r0, 0x30cc(r4)
/* 099FD4 8009F574 900430C8 */  stw		r0, 0x30c8(r4)
/* 099FD8 8009F578 900430D0 */  stw		r0, 0x30d0(r4)
/* 099FDC 8009F57C 4E800020 */  blr		


