# nubinit.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKInitializeNub
/* 0C3E64 800C9404 7C0802A6 */  mflr    r0
/* 0C3E68 800C9408 90010004 */  stw     r0, 4(r1)
/* 0C3E6C 800C940C 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0C3E70 800C9410 93E1000C */  stw     r31, 0xc(r1)
/* 0C3E74 800C9414 93C10008 */  stw     r30, 8(r1)
/* 0C3E78 800C9418 4800010D */  bl      TRKInitializeEndian
/* 0C3E7C 800C941C 7C7E1B79 */  or.     r30, r3, r3
/* 0C3E80 800C9420 40820008 */  bne     lbl_800C9428
/* 0C3E84 800C9424 48000BAD */  bl      usr_put_initialize
lbl_800C9428:
/* 0C3E88 800C9428 2C1E0000 */  cmpwi   r30, 0
/* 0C3E8C 800C942C 4082000C */  bne     lbl_800C9438
/* 0C3E90 800C9430 4BFFFD79 */  bl      TRKInitializeEventQueue
/* 0C3E94 800C9434 7C7E1B78 */  mr      r30, r3
lbl_800C9438:
/* 0C3E98 800C9438 2C1E0000 */  cmpwi   r30, 0
/* 0C3E9C 800C943C 4082000C */  bne     lbl_800C9448
/* 0C3EA0 800C9440 48000189 */  bl      TRKInitializeMessageBuffers
/* 0C3EA4 800C9444 7C7E1B78 */  mr      r30, r3
lbl_800C9448:
/* 0C3EA8 800C9448 2C1E0000 */  cmpwi   r30, 0
/* 0C3EAC 800C944C 4082000C */  bne     lbl_800C9458
/* 0C3EB0 800C9450 48000B85 */  bl      TRKInitializeDispatcher
/* 0C3EB4 800C9454 7C7E1B78 */  mr      r30, r3
lbl_800C9458:
/* 0C3EB8 800C9458 2C1E0000 */  cmpwi   r30, 0
/* 0C3EBC 800C945C 40820040 */  bne     lbl_800C949C
/* 0C3EC0 800C9460 3C608013 */  lis     r3, gTRKInputPendingPtr@ha
/* 0C3EC4 800C9464 3BE34544 */  addi    r31, r3, gTRKInputPendingPtr@l
/* 0C3EC8 800C9468 3C600001 */  lis     r3, 1
/* 0C3ECC 800C946C 38DF0000 */  addi    r6, r31, 0
/* 0C3ED0 800C9470 3863E100 */  addi    r3, r3, -7936
/* 0C3ED4 800C9474 38800001 */  li      r4, 1
/* 0C3ED8 800C9478 38A00000 */  li      r5, 0
/* 0C3EDC 800C947C 4800413D */  bl      TRKInitializeIntDrivenUART
/* 0C3EE0 800C9480 7C601B78 */  mr      r0, r3
/* 0C3EE4 800C9484 807F0000 */  lwz     r3, 0(r31)
/* 0C3EE8 800C9488 7C1F0378 */  mr      r31, r0
/* 0C3EEC 800C948C 480039BD */  bl      TRKTargetSetInputPendingPtr
/* 0C3EF0 800C9490 2C1F0000 */  cmpwi   r31, 0
/* 0C3EF4 800C9494 41820008 */  beq     lbl_800C949C
/* 0C3EF8 800C9498 7FFEFB78 */  mr      r30, r31
lbl_800C949C:
/* 0C3EFC 800C949C 2C1E0000 */  cmpwi   r30, 0
/* 0C3F00 800C94A0 4082000C */  bne     lbl_800C94AC
/* 0C3F04 800C94A4 48000B01 */  bl      TRKInitializeSerialHandler
/* 0C3F08 800C94A8 7C7E1B78 */  mr      r30, r3
lbl_800C94AC:
/* 0C3F0C 800C94AC 2C1E0000 */  cmpwi   r30, 0
/* 0C3F10 800C94B0 4082000C */  bne     lbl_800C94BC
/* 0C3F14 800C94B4 48003B59 */  bl      TRKInitializeTarget
/* 0C3F18 800C94B8 7C7E1B78 */  mr      r30, r3
lbl_800C94BC:
/* 0C3F1C 800C94BC 7FC3F378 */  mr      r3, r30
/* 0C3F20 800C94C0 83E1000C */  lwz     r31, 0xc(r1)
/* 0C3F24 800C94C4 83C10008 */  lwz     r30, 8(r1)
/* 0C3F28 800C94C8 38210010 */  addi    r1, r1, 0x10
/* 0C3F2C 800C94CC 80010004 */  lwz     r0, 4(r1)
/* 0C3F30 800C94D0 7C0803A6 */  mtlr    r0
/* 0C3F34 800C94D4 4E800020 */  blr     

glabel TRKTerminateNub
/* 0C3F38 800C94D8 7C0802A6 */  mflr    r0
/* 0C3F3C 800C94DC 90010004 */  stw     r0, 4(r1)
/* 0C3F40 800C94E0 9421FFF8 */  stwu    r1, -8(r1)
/* 0C3F44 800C94E4 48000AE5 */  bl      TRKTerminateSerialHandler
/* 0C3F48 800C94E8 38600000 */  li      r3, 0
/* 0C3F4C 800C94EC 38210008 */  addi    r1, r1, 8
/* 0C3F50 800C94F0 80010004 */  lwz     r0, 4(r1)
/* 0C3F54 800C94F4 7C0803A6 */  mtlr    r0
/* 0C3F58 800C94F8 4E800020 */  blr     

glabel TRKNubWelcome
/* 0C3F5C 800C94FC 7C0802A6 */  mflr    r0
/* 0C3F60 800C9500 3C60800D */  lis     r3, D_800D32A0@ha
/* 0C3F64 800C9504 90010004 */  stw     r0, 4(r1)
/* 0C3F68 800C9508 386332A0 */  addi    r3, r3, D_800D32A0@l
/* 0C3F6C 800C950C 9421FFF8 */  stwu    r1, -8(r1)
/* 0C3F70 800C9510 48004231 */  bl      TRK_board_display
/* 0C3F74 800C9514 38210008 */  addi    r1, r1, 8
/* 0C3F78 800C9518 80010004 */  lwz     r0, 4(r1)
/* 0C3F7C 800C951C 7C0803A6 */  mtlr    r0
/* 0C3F80 800C9520 4E800020 */  blr     

glabel TRKInitializeEndian
/* 0C3F84 800C9524 3C608013 */  lis     r3, gTRKBigEndian@ha
/* 0C3F88 800C9528 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0C3F8C 800C952C 38A32B78 */  addi    r5, r3, gTRKBigEndian@l
/* 0C3F90 800C9530 38C00001 */  li      r6, 1
/* 0C3F94 800C9534 90C50000 */  stw     r6, 0(r5)
/* 0C3F98 800C9538 38000012 */  li      r0, 0x12
/* 0C3F9C 800C953C 38600034 */  li      r3, 0x34
/* 0C3FA0 800C9540 98010008 */  stb     r0, 8(r1)
/* 0C3FA4 800C9544 38800056 */  li      r4, 0x56
/* 0C3FA8 800C9548 38000078 */  li      r0, 0x78
/* 0C3FAC 800C954C 98610009 */  stb     r3, 9(r1)
/* 0C3FB0 800C9550 38600000 */  li      r3, 0
/* 0C3FB4 800C9554 9881000A */  stb     r4, 0xa(r1)
/* 0C3FB8 800C9558 9801000B */  stb     r0, 0xb(r1)
/* 0C3FBC 800C955C 80810008 */  lwz     r4, 8(r1)
/* 0C3FC0 800C9560 3C04EDCC */  addis   r0, r4, 0xedcc
/* 0C3FC4 800C9564 28005678 */  cmplwi  r0, 0x5678
/* 0C3FC8 800C9568 4082000C */  bne     lbl_800C9574
/* 0C3FCC 800C956C 90C50000 */  stw     r6, 0(r5)
/* 0C3FD0 800C9570 48000020 */  b       lbl_800C9590
lbl_800C9574:
/* 0C3FD4 800C9574 3C0487AA */  addis   r0, r4, 0x87aa
/* 0C3FD8 800C9578 28003412 */  cmplwi  r0, 0x3412
/* 0C3FDC 800C957C 40820010 */  bne     lbl_800C958C
/* 0C3FE0 800C9580 38000000 */  li      r0, 0
/* 0C3FE4 800C9584 90050000 */  stw     r0, 0(r5)
/* 0C3FE8 800C9588 48000008 */  b       lbl_800C9590
lbl_800C958C:
/* 0C3FEC 800C958C 38600001 */  li      r3, 1
lbl_800C9590:
/* 0C3FF0 800C9590 38210010 */  addi    r1, r1, 0x10
/* 0C3FF4 800C9594 4E800020 */  blr     

.section .rodata, "a"

.balign 8

/* 000D0320 800D32A0 001A */
D_800D32A0:
    .asciz "MetroTRK for Dolphin v0.5"
    .balign 4

.section .bss, "wa"

.balign 4

/* 0012FBF8 80132B78 0004 */
glabel gTRKBigEndian
    .skip 4
