# math_inlines.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel sqrt
/* 0CCEA4 800D2444 C8028708 */  lfd		f0, D_80136408-_SDA2_BASE_(r2)
/* 0CCEA8 800D2448 FC010040 */  fcmpo	cr0, f1, f0
/* 0CCEAC 800D244C 40810058 */  ble		lbl_800D24A4
/* 0CCEB0 800D2450 FC400834 */  frsqrte	f2, f1
/* 0CCEB4 800D2454 C8828710 */  lfd		f4, D_80136410-_SDA2_BASE_(r2)
/* 0CCEB8 800D2458 C8628718 */  lfd		f3, D_80136418-_SDA2_BASE_(r2)
/* 0CCEBC 800D245C FC0200B2 */  fmul	f0, f2, f2
/* 0CCEC0 800D2460 FC4400B2 */  fmul	f2, f4, f2
/* 0CCEC4 800D2464 FC01183C */  fnmsub	f0, f1, f0, f3
/* 0CCEC8 800D2468 FC420032 */  fmul	f2, f2, f0
/* 0CCECC 800D246C FC0200B2 */  fmul	f0, f2, f2
/* 0CCED0 800D2470 FC4400B2 */  fmul	f2, f4, f2
/* 0CCED4 800D2474 FC01183C */  fnmsub	f0, f1, f0, f3
/* 0CCED8 800D2478 FC420032 */  fmul	f2, f2, f0
/* 0CCEDC 800D247C FC0200B2 */  fmul	f0, f2, f2
/* 0CCEE0 800D2480 FC4400B2 */  fmul	f2, f4, f2
/* 0CCEE4 800D2484 FC01183C */  fnmsub	f0, f1, f0, f3
/* 0CCEE8 800D2488 FC420032 */  fmul	f2, f2, f0
/* 0CCEEC 800D248C FC0200B2 */  fmul	f0, f2, f2
/* 0CCEF0 800D2490 FC4400B2 */  fmul	f2, f4, f2
/* 0CCEF4 800D2494 FC01183C */  fnmsub	f0, f1, f0, f3
/* 0CCEF8 800D2498 FC020032 */  fmul	f0, f2, f0
/* 0CCEFC 800D249C FC210032 */  fmul	f1, f1, f0
/* 0CCF00 800D24A0 4E800020 */  blr		
lbl_800D24A4:
/* 0CCF04 800D24A4 FC000800 */  fcmpu	cr0, f0, f1
/* 0CCF08 800D24A8 4082000C */  bne		lbl_800D24B4
/* 0CCF0C 800D24AC FC200090 */  fmr		f1, f0
/* 0CCF10 800D24B0 4E800020 */  blr		
lbl_800D24B4:
/* 0CCF14 800D24B4 FC010000 */  fcmpu	cr0, f1, f0
/* 0CCF18 800D24B8 41820010 */  beq		lbl_800D24C8
/* 0CCF1C 800D24BC 3C60800F */  lis		r3, __float_nan@ha
/* 0CCF20 800D24C0 C0233E78 */  lfs		f1, __float_nan@l(r3)
/* 0CCF24 800D24C4 4E800020 */  blr		
lbl_800D24C8:
/* 0CCF28 800D24C8 3C60800F */  lis		r3, __float_huge@ha
/* 0CCF2C 800D24CC C0233E7C */  lfs		f1, __float_huge@l(r3)
/* 0CCF30 800D24D0 4E800020 */  blr		


.section .sdata2, "wa"

.balign 8

/* 000F1F08 80136408 0008 */
D_80136408:
    .double 0.0

.balign 8

/* 000F1F10 80136410 0008 */
D_80136410:
    .double 0.5

.balign 8

/* 000F1F18 80136418 0008 */
D_80136418:
    .double 3.0


