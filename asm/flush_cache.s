# flush_cache.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRK_flush_cache
/* 0C62A4 800CB844 3CA0FFFF */  lis     r5, 0xffff
/* 0C62A8 800CB848 60A5FFF1 */  ori     r5, r5, 0xfff1
/* 0C62AC 800CB84C 7CA51838 */  and     r5, r5, r3
/* 0C62B0 800CB850 7C651850 */  subf    r3, r5, r3
/* 0C62B4 800CB854 7C841A14 */  add     r4, r4, r3
lbl_800CB858:
/* 0C62B8 800CB858 7C00286C */  dcbst   0, r5
/* 0C62BC 800CB85C 7C0028AC */  dcbf    0, r5
/* 0C62C0 800CB860 7C0004AC */  sync    0
/* 0C62C4 800CB864 7C002FAC */  icbi    0, r5
/* 0C62C8 800CB868 30A50008 */  addic   r5, r5, 8
/* 0C62CC 800CB86C 3484FFF8 */  addic.  r4, r4, -8
/* 0C62D0 800CB870 4080FFE8 */  bge     lbl_800CB858
/* 0C62D4 800CB874 4C00012C */  isync   
/* 0C62D8 800CB878 4E800020 */  blr     
