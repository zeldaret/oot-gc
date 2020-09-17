# OSSync.c
.include "macros.inc"

.section .text, "ax"

.balign 4

SystemCallVector:
/* 09BAB4 800A1054 7D30FAA6 */  mfspr	r9, 0x3f0
/* 09BAB8 800A1058 612A0008 */  ori		r10, r9, 8
/* 09BABC 800A105C 7D50FBA6 */  mtspr	0x3f0, r10
/* 09BAC0 800A1060 4C00012C */  isync	
/* 09BAC4 800A1064 7C0004AC */  sync	0
/* 09BAC8 800A1068 7D30FBA6 */  mtspr	0x3f0, r9
/* 09BACC 800A106C 4C000064 */  rfi		
glabel __OSSystemCallVectorEnd
/* 09BAD0 800A1070 60000000 */  nop		

glabel __OSInitSystemCall
/* 09BAD4 800A1074 7C0802A6 */  mflr	r0
/* 09BAD8 800A1078 90010004 */  stw		r0, 4(r1)
/* 09BADC 800A107C 9421FFF0 */  stwu	r1, -0x10(r1)
/* 09BAE0 800A1080 93E1000C */  stw		r31, 0xc(r1)
/* 09BAE4 800A1084 3CA08000 */  lis		r5, 0x8000
/* 09BAE8 800A1088 3C80800A */  lis		r4, SystemCallVector@ha
/* 09BAEC 800A108C 3C60800A */  lis		r3, __OSSystemCallVectorEnd@ha
/* 09BAF0 800A1090 3BE50C00 */  addi	r31, r5, 0xc00
/* 09BAF4 800A1094 38031070 */  addi	r0, r3, __OSSystemCallVectorEnd@l
/* 09BAF8 800A1098 38841054 */  addi	r4, r4, SystemCallVector@l
/* 09BAFC 800A109C 7FE3FB78 */  mr		r3, r31
/* 09BB00 800A10A0 7CA40050 */  subf	r5, r4, r0
/* 09BB04 800A10A4 4BF64421 */  bl		memcpy
/* 09BB08 800A10A8 7FE3FB78 */  mr		r3, r31
/* 09BB0C 800A10AC 38800100 */  li		r4, 0x100
/* 09BB10 800A10B0 4BFFC72D */  bl		DCFlushRangeNoSync
/* 09BB14 800A10B4 7C0004AC */  sync	0
/* 09BB18 800A10B8 7FE3FB78 */  mr		r3, r31
/* 09BB1C 800A10BC 38800100 */  li		r4, 0x100
/* 09BB20 800A10C0 4BFFC775 */  bl		ICInvalidateRange
/* 09BB24 800A10C4 80010014 */  lwz		r0, 0x14(r1)
/* 09BB28 800A10C8 83E1000C */  lwz		r31, 0xc(r1)
/* 09BB2C 800A10CC 38210010 */  addi	r1, r1, 0x10
/* 09BB30 800A10D0 7C0803A6 */  mtlr	r0
/* 09BB34 800A10D4 4E800020 */  blr		


