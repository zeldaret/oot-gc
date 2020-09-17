# abort_exit.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel exit
/* 0C8A44 800CDFE4 7C0802A6 */  mflr	r0
/* 0C8A48 800CDFE8 90010004 */  stw		r0, 4(r1)
/* 0C8A4C 800CDFEC 9421FFE8 */  stwu	r1, -0x18(r1)
/* 0C8A50 800CDFF0 93E10014 */  stw		r31, 0x14(r1)
/* 0C8A54 800CDFF4 800D8FE0 */  lwz		r0, __aborting-_SDA_BASE_(r13)
/* 0C8A58 800CDFF8 2C000000 */  cmpwi	r0, 0
/* 0C8A5C 800CDFFC 40820084 */  bne		lbl_800CE080
/* 0C8A60 800CE000 3C608013 */  lis		r3, atexit_funcs@ha
/* 0C8A64 800CE004 3BE34AD8 */  addi	r31, r3, atexit_funcs@l
/* 0C8A68 800CE008 48000024 */  b		lbl_800CE02C
lbl_800CE00C:
/* 0C8A6C 800CE00C 806D8FE4 */  lwz		r3, atexit_curr_func-_SDA_BASE_(r13)
/* 0C8A70 800CE010 3863FFFF */  addi	r3, r3, -1
/* 0C8A74 800CE014 5460103A */  slwi	r0, r3, 2
/* 0C8A78 800CE018 906D8FE4 */  stw		r3, atexit_curr_func-_SDA_BASE_(r13)
/* 0C8A7C 800CE01C 7C7F0214 */  add		r3, r31, r0
/* 0C8A80 800CE020 81830000 */  lwz		r12, 0(r3)
/* 0C8A84 800CE024 7D8803A6 */  mtlr	r12
/* 0C8A88 800CE028 4E800021 */  blrl	
lbl_800CE02C:
/* 0C8A8C 800CE02C 800D8FE4 */  lwz		r0, atexit_curr_func-_SDA_BASE_(r13)
/* 0C8A90 800CE030 2C000000 */  cmpwi	r0, 0
/* 0C8A94 800CE034 4181FFD8 */  bgt		lbl_800CE00C
/* 0C8A98 800CE038 4BFFF855 */  bl		__destroy_global_chain
/* 0C8A9C 800CE03C 3C60800D */  lis		r3, _dtors@ha
/* 0C8AA0 800CE040 38032FC0 */  addi	r0, r3, _dtors@l
/* 0C8AA4 800CE044 7C1F0378 */  mr		r31, r0
/* 0C8AA8 800CE048 48000010 */  b		lbl_800CE058
lbl_800CE04C:
/* 0C8AAC 800CE04C 7D8803A6 */  mtlr	r12
/* 0C8AB0 800CE050 4E800021 */  blrl	
/* 0C8AB4 800CE054 3BFF0004 */  addi	r31, r31, 4
lbl_800CE058:
/* 0C8AB8 800CE058 819F0000 */  lwz		r12, 0(r31)
/* 0C8ABC 800CE05C 280C0000 */  cmplwi	r12, 0
/* 0C8AC0 800CE060 4082FFEC */  bne		lbl_800CE04C
/* 0C8AC4 800CE064 818D8FEC */  lwz		r12, __stdio_exit-_SDA_BASE_(r13)
/* 0C8AC8 800CE068 280C0000 */  cmplwi	r12, 0
/* 0C8ACC 800CE06C 41820014 */  beq		lbl_800CE080
/* 0C8AD0 800CE070 7D8803A6 */  mtlr	r12
/* 0C8AD4 800CE074 4E800021 */  blrl	
/* 0C8AD8 800CE078 38000000 */  li		r0, 0
/* 0C8ADC 800CE07C 900D8FEC */  stw		r0, __stdio_exit-_SDA_BASE_(r13)
lbl_800CE080:
/* 0C8AE0 800CE080 3C608013 */  lis		r3, __atexit_funcs@ha
/* 0C8AE4 800CE084 3BE34BD8 */  addi	r31, r3, __atexit_funcs@l
/* 0C8AE8 800CE088 48000024 */  b		lbl_800CE0AC
lbl_800CE08C:
/* 0C8AEC 800CE08C 806D8FE8 */  lwz		r3, __atexit_curr_func-_SDA_BASE_(r13)
/* 0C8AF0 800CE090 3863FFFF */  addi	r3, r3, -1
/* 0C8AF4 800CE094 5460103A */  slwi	r0, r3, 2
/* 0C8AF8 800CE098 906D8FE8 */  stw		r3, __atexit_curr_func-_SDA_BASE_(r13)
/* 0C8AFC 800CE09C 7C7F0214 */  add		r3, r31, r0
/* 0C8B00 800CE0A0 81830000 */  lwz		r12, 0(r3)
/* 0C8B04 800CE0A4 7D8803A6 */  mtlr	r12
/* 0C8B08 800CE0A8 4E800021 */  blrl	
lbl_800CE0AC:
/* 0C8B0C 800CE0AC 800D8FE8 */  lwz		r0, __atexit_curr_func-_SDA_BASE_(r13)
/* 0C8B10 800CE0B0 2C000000 */  cmpwi	r0, 0
/* 0C8B14 800CE0B4 4181FFD8 */  bgt		lbl_800CE08C
/* 0C8B18 800CE0B8 480004ED */  bl		__kill_critical_regions
/* 0C8B1C 800CE0BC 818D8FF0 */  lwz		r12, __console_exit-_SDA_BASE_(r13)
/* 0C8B20 800CE0C0 280C0000 */  cmplwi	r12, 0
/* 0C8B24 800CE0C4 41820014 */  beq		lbl_800CE0D8
/* 0C8B28 800CE0C8 7D8803A6 */  mtlr	r12
/* 0C8B2C 800CE0CC 4E800021 */  blrl	
/* 0C8B30 800CE0D0 38000000 */  li		r0, 0
/* 0C8B34 800CE0D4 900D8FF0 */  stw		r0, __console_exit-_SDA_BASE_(r13)
lbl_800CE0D8:
/* 0C8B38 800CE0D8 4BFD466D */  bl		_ExitProcess
/* 0C8B3C 800CE0DC 8001001C */  lwz		r0, 0x1c(r1)
/* 0C8B40 800CE0E0 83E10014 */  lwz		r31, 0x14(r1)
/* 0C8B44 800CE0E4 38210018 */  addi	r1, r1, 0x18
/* 0C8B48 800CE0E8 7C0803A6 */  mtlr	r0
/* 0C8B4C 800CE0EC 4E800020 */  blr		


.section .dtors, "a"

.balign 4

/* 000D0040 800D2FC0 0004 */
glabel _dtors
    .long __destroy_global_chain


.section .bss, "wa"

.balign 8

/* 00131B58 80134AD8 0100 */
atexit_funcs:
    .skip 256

.balign 4

/* 00131C58 80134BD8 0100 */
__atexit_funcs:
    .skip 256


.section .sbss, "wa"

.balign 8

/* 000F1F40 80135CC0 0004 */
glabel __aborting
    .skip 4

.balign 4

/* 000F1F44 80135CC4 0004 */
atexit_curr_func:
    .skip 4

.balign 4

/* 000F1F48 80135CC8 0004 */
__atexit_curr_func:
    .skip 4

.balign 4

/* 000F1F4C 80135CCC 0004 */
glabel __stdio_exit
    .skip 4

.balign 4

/* 000F1F50 80135CD0 0004 */
glabel __console_exit
    .skip 4


