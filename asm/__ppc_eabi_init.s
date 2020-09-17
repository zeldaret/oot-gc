# __ppc_eabi_init.cpp
.include "macros.inc"

.section .init, "ax"

.balign 4

glabel __init_hardware
/* 000300 80003400 7C0000A6 */  mfmsr   r0
/* 000304 80003404 60002000 */  ori     r0, r0, 0x2000
/* 000308 80003408 7C000124 */  mtmsr   r0
/* 00030C 8000340C 7FE802A6 */  mflr    r31
/* 000310 80003410 48099219 */  bl      __OSPSInit
/* 000314 80003414 480987BD */  bl      __OSFPRInit
/* 000318 80003418 4809A87D */  bl      __OSCacheInit
/* 00031C 8000341C 7FE803A6 */  mtlr    r31
/* 000320 80003420 4E800020 */  blr     

glabel __flush_cache
/* 000324 80003424 3CA0FFFF */  lis     r5, 0xffff
/* 000328 80003428 60A5FFF1 */  ori     r5, r5, 0xfff1
/* 00032C 8000342C 7CA51838 */  and     r5, r5, r3
/* 000330 80003430 7C651850 */  subf    r3, r5, r3
/* 000334 80003434 7C841A14 */  add     r4, r4, r3
lbl_80003438:
/* 000338 80003438 7C00286C */  dcbst   0, r5
/* 00033C 8000343C 7C0004AC */  sync    0
/* 000340 80003440 7C002FAC */  icbi    0, r5
/* 000344 80003444 30A50008 */  addic   r5, r5, 8
/* 000348 80003448 3484FFF8 */  addic.  r4, r4, -8
/* 00034C 8000344C 4080FFEC */  bge     lbl_80003438
/* 000350 80003450 4C00012C */  isync   
/* 000354 80003454 4E800020 */  blr     


.section .text, "ax"

.balign 4

glabel InitMetroTRK_BBA
/* 09D12C 800A26CC 4E800020 */  blr     

glabel __init_user
/* 09D130 800A26D0 7C0802A6 */  mflr    r0
/* 09D134 800A26D4 90010004 */  stw     r0, 4(r1)
/* 09D138 800A26D8 9421FFF8 */  stwu    r1, -8(r1)
/* 09D13C 800A26DC 48000015 */  bl      __init_cpp
/* 09D140 800A26E0 8001000C */  lwz     r0, 0xc(r1)
/* 09D144 800A26E4 38210008 */  addi    r1, r1, 8
/* 09D148 800A26E8 7C0803A6 */  mtlr    r0
/* 09D14C 800A26EC 4E800020 */  blr     

__init_cpp:
/* 09D150 800A26F0 7C0802A6 */  mflr    r0
/* 09D154 800A26F4 90010004 */  stw     r0, 4(r1)
/* 09D158 800A26F8 9421FFF0 */  stwu    r1, -0x10(r1)
/* 09D15C 800A26FC 93E1000C */  stw     r31, 0xc(r1)
/* 09D160 800A2700 3C60800D */  lis     r3, _ctors@ha
/* 09D164 800A2704 38032FA0 */  addi    r0, r3, _ctors@l
/* 09D168 800A2708 7C1F0378 */  mr      r31, r0
/* 09D16C 800A270C 48000004 */  b       lbl_800A2710
lbl_800A2710:
/* 09D170 800A2710 48000004 */  b       lbl_800A2714
lbl_800A2714:
/* 09D174 800A2714 48000010 */  b       lbl_800A2724
lbl_800A2718:
/* 09D178 800A2718 7D8803A6 */  mtlr    r12
/* 09D17C 800A271C 4E800021 */  blrl    
/* 09D180 800A2720 3BFF0004 */  addi    r31, r31, 4
lbl_800A2724:
/* 09D184 800A2724 819F0000 */  lwz     r12, 0(r31)
/* 09D188 800A2728 280C0000 */  cmplwi  r12, 0
/* 09D18C 800A272C 4082FFEC */  bne     lbl_800A2718
/* 09D190 800A2730 80010014 */  lwz     r0, 0x14(r1)
/* 09D194 800A2734 83E1000C */  lwz     r31, 0xc(r1)
/* 09D198 800A2738 38210010 */  addi    r1, r1, 0x10
/* 09D19C 800A273C 7C0803A6 */  mtlr    r0
/* 09D1A0 800A2740 4E800020 */  blr     

glabel _ExitProcess
/* 09D1A4 800A2744 7C0802A6 */  mflr    r0
/* 09D1A8 800A2748 90010004 */  stw     r0, 4(r1)
/* 09D1AC 800A274C 9421FFF8 */  stwu    r1, -8(r1)
/* 09D1B0 800A2750 4BFF93AD */  bl      PPCHalt
/* 09D1B4 800A2754 8001000C */  lwz     r0, 0xc(r1)
/* 09D1B8 800A2758 38210008 */  addi    r1, r1, 8
/* 09D1BC 800A275C 7C0803A6 */  mtlr    r0
/* 09D1C0 800A2760 4E800020 */  blr     


