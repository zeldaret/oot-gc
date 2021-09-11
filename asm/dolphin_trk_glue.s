# dolphin_trk_glue.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKLoadContext
/* 0C7E6C 800CD40C 80030000 */  lwz     r0, 0(r3)
/* 0C7E70 800CD410 80230004 */  lwz     r1, 4(r3)
/* 0C7E74 800CD414 80430008 */  lwz     r2, 8(r3)
/* 0C7E78 800CD418 A0A301A2 */  lhz     r5, 0x1a2(r3)
/* 0C7E7C 800CD41C 54A607BD */  rlwinm. r6, r5, 0, 0x1e, 0x1e
/* 0C7E80 800CD420 41820014 */  beq     lbl_800CD434
/* 0C7E84 800CD424 54A507FA */  rlwinm  r5, r5, 0, 0x1f, 0x1d
/* 0C7E88 800CD428 B0A301A2 */  sth     r5, 0x1a2(r3)
/* 0C7E8C 800CD42C B8A30014 */  lmw     r5, 0x14(r3)
/* 0C7E90 800CD430 48000008 */  b       lbl_800CD438
lbl_800CD434:
/* 0C7E94 800CD434 B9A30034 */  lmw     r13, 0x34(r3)
lbl_800CD438:
/* 0C7E98 800CD438 7C7F1B78 */  mr      r31, r3
/* 0C7E9C 800CD43C 7C832378 */  mr      r3, r4
/* 0C7EA0 800CD440 809F0080 */  lwz     r4, 0x80(r31)
/* 0C7EA4 800CD444 7C8FF120 */  mtcrf   0xff, r4
/* 0C7EA8 800CD448 809F0084 */  lwz     r4, 0x84(r31)
/* 0C7EAC 800CD44C 7C8803A6 */  mtlr    r4
/* 0C7EB0 800CD450 809F0088 */  lwz     r4, 0x88(r31)
/* 0C7EB4 800CD454 7C8903A6 */  mtctr   r4
/* 0C7EB8 800CD458 809F008C */  lwz     r4, 0x8c(r31)
/* 0C7EBC 800CD45C 7C8103A6 */  mtxer   r4
/* 0C7EC0 800CD460 7C8000A6 */  mfmsr   r4
/* 0C7EC4 800CD464 5484045E */  rlwinm  r4, r4, 0, 0x11, 0xf
/* 0C7EC8 800CD468 548407FA */  rlwinm  r4, r4, 0, 0x1f, 0x1d
/* 0C7ECC 800CD46C 7C800124 */  mtmsr   r4
/* 0C7ED0 800CD470 7C5143A6 */  mtspr   0x111, r2
/* 0C7ED4 800CD474 809F000C */  lwz     r4, 0xc(r31)
/* 0C7ED8 800CD478 7C9243A6 */  mtspr   0x112, r4
/* 0C7EDC 800CD47C 809F0010 */  lwz     r4, 0x10(r31)
/* 0C7EE0 800CD480 7C9343A6 */  mtspr   0x113, r4
/* 0C7EE4 800CD484 805F0198 */  lwz     r2, 0x198(r31)
/* 0C7EE8 800CD488 809F019C */  lwz     r4, 0x19c(r31)
/* 0C7EEC 800CD48C 83FF007C */  lwz     r31, 0x7c(r31)
/* 0C7EF0 800CD490 4BFFED8C */  b       TRKInterruptHandler

glabel TRKEXICallBack
/* 0C7EF4 800CD494 7C0802A6 */  mflr    r0
/* 0C7EF8 800CD498 90010004 */  stw     r0, 4(r1)
/* 0C7EFC 800CD49C 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0C7F00 800CD4A0 93E1000C */  stw     r31, 0xc(r1)
/* 0C7F04 800CD4A4 7C9F2378 */  mr      r31, r4
/* 0C7F08 800CD4A8 4BFD3DE9 */  bl      OSEnableScheduler
/* 0C7F0C 800CD4AC 7FE3FB78 */  mr      r3, r31
/* 0C7F10 800CD4B0 38800500 */  li      r4, 0x500
/* 0C7F14 800CD4B4 4BFFFF59 */  bl      TRKLoadContext
/* 0C7F18 800CD4B8 83E1000C */  lwz     r31, 0xc(r1)
/* 0C7F1C 800CD4BC 38210010 */  addi    r1, r1, 0x10
/* 0C7F20 800CD4C0 80010004 */  lwz     r0, 4(r1)
/* 0C7F24 800CD4C4 7C0803A6 */  mtlr    r0
/* 0C7F28 800CD4C8 4E800020 */  blr     

glabel InitMetroTRKCommTable
/* 0C7F2C 800CD4CC 7C0802A6 */  mflr    r0
/* 0C7F30 800CD4D0 90010004 */  stw     r0, 4(r1)
/* 0C7F34 800CD4D4 9421FFF8 */  stwu    r1, -8(r1)
/* 0C7F38 800CD4D8 2C030001 */  cmpwi   r3, 1
/* 0C7F3C 800CD4DC 40820068 */  bne     lbl_800CD544
/* 0C7F40 800CD4E0 48005AA5 */  bl      Hu_IsStub
/* 0C7F44 800CD4E4 3CA0800D */  lis     r5, DBInitComm@ha
/* 0C7F48 800CD4E8 3C80800F */  lis     r4, gDBCommTable@ha
/* 0C7F4C 800CD4EC 380528E8 */  addi    r0, r5, DBInitComm@l
/* 0C7F50 800CD4F0 38A43B18 */  addi    r5, r4, gDBCommTable@l
/* 0C7F54 800CD4F4 3C80800D */  lis     r4, DBInitInterrupts@ha
/* 0C7F58 800CD4F8 90050000 */  stw     r0, 0(r5)
/* 0C7F5C 800CD4FC 38042894 */  addi    r0, r4, DBInitInterrupts@l
/* 0C7F60 800CD500 3C80800D */  lis     r4, DBQueryData@ha
/* 0C7F64 800CD504 90050004 */  stw     r0, 4(r5)
/* 0C7F68 800CD508 380427F8 */  addi    r0, r4, DBQueryData@l
/* 0C7F6C 800CD50C 3C80800D */  lis     r4, DBRead@ha
/* 0C7F70 800CD510 90050008 */  stw     r0, 8(r5)
/* 0C7F74 800CD514 3804276C */  addi    r0, r4, DBRead@l
/* 0C7F78 800CD518 3C80800D */  lis     r4, DBWrite@ha
/* 0C7F7C 800CD51C 9005000C */  stw     r0, 0xc(r5)
/* 0C7F80 800CD520 3804250C */  addi    r0, r4, DBWrite@l
/* 0C7F84 800CD524 3C80800D */  lis     r4, DBOpen@ha
/* 0C7F88 800CD528 90050010 */  stw     r0, 0x10(r5)
/* 0C7F8C 800CD52C 38042508 */  addi    r0, r4, DBOpen@l
/* 0C7F90 800CD530 3C80800D */  lis     r4, DBClose@ha
/* 0C7F94 800CD534 90050014 */  stw     r0, 0x14(r5)
/* 0C7F98 800CD538 38042504 */  addi    r0, r4, DBClose@l
/* 0C7F9C 800CD53C 90050018 */  stw     r0, 0x18(r5)
/* 0C7FA0 800CD540 48000064 */  b       lbl_800CD5A4
lbl_800CD544:
/* 0C7FA4 800CD544 48004FB9 */  bl      AMC_IsStub
/* 0C7FA8 800CD548 3CA0800D */  lis     r5, EXI2_Init@ha
/* 0C7FAC 800CD54C 3C80800F */  lis     r4, gDBCommTable@ha
/* 0C7FB0 800CD550 380524D4 */  addi    r0, r5, EXI2_Init@l
/* 0C7FB4 800CD554 38A43B18 */  addi    r5, r4, gDBCommTable@l
/* 0C7FB8 800CD558 3C80800D */  lis     r4, EXI2_EnableInterrupts@ha
/* 0C7FBC 800CD55C 90050000 */  stw     r0, 0(r5)
/* 0C7FC0 800CD560 380424D8 */  addi    r0, r4, EXI2_EnableInterrupts@l
/* 0C7FC4 800CD564 3C80800D */  lis     r4, EXI2_Poll@ha
/* 0C7FC8 800CD568 90050004 */  stw     r0, 4(r5)
/* 0C7FCC 800CD56C 380424DC */  addi    r0, r4, EXI2_Poll@l
/* 0C7FD0 800CD570 3C80800D */  lis     r4, EXI2_ReadN@ha
/* 0C7FD4 800CD574 90050008 */  stw     r0, 8(r5)
/* 0C7FD8 800CD578 380424E4 */  addi    r0, r4, EXI2_ReadN@l
/* 0C7FDC 800CD57C 3C80800D */  lis     r4, EXI2_WriteN@ha
/* 0C7FE0 800CD580 9005000C */  stw     r0, 0xc(r5)
/* 0C7FE4 800CD584 380424EC */  addi    r0, r4, EXI2_WriteN@l
/* 0C7FE8 800CD588 3C80800D */  lis     r4, EXI2_Reserve@ha
/* 0C7FEC 800CD58C 90050010 */  stw     r0, 0x10(r5)
/* 0C7FF0 800CD590 380424F4 */  addi    r0, r4, EXI2_Reserve@l
/* 0C7FF4 800CD594 3C80800D */  lis     r4, EXI2_Unreserve@ha
/* 0C7FF8 800CD598 90050014 */  stw     r0, 0x14(r5)
/* 0C7FFC 800CD59C 380424F8 */  addi    r0, r4, EXI2_Unreserve@l
/* 0C8000 800CD5A0 90050018 */  stw     r0, 0x18(r5)
lbl_800CD5A4:
/* 0C8004 800CD5A4 38210008 */  addi    r1, r1, 8
/* 0C8008 800CD5A8 80010004 */  lwz     r0, 4(r1)
/* 0C800C 800CD5AC 7C0803A6 */  mtlr    r0
/* 0C8010 800CD5B0 4E800020 */  blr     

glabel TRKUARTInterruptHandler
/* 0C8014 800CD5B4 4E800020 */  blr     

glabel TRKInitializeIntDrivenUART
/* 0C8018 800CD5B8 7C0802A6 */  mflr    r0
/* 0C801C 800CD5BC 90010004 */  stw     r0, 4(r1)
/* 0C8020 800CD5C0 9421FFF8 */  stwu    r1, -8(r1)
/* 0C8024 800CD5C4 3C60800F */  lis     r3, gDBCommTable@ha
/* 0C8028 800CD5C8 38633B18 */  addi    r3, r3, gDBCommTable@l
/* 0C802C 800CD5CC 3C80800D */  lis     r4, TRKEXICallBack@ha
/* 0C8030 800CD5D0 81830000 */  lwz     r12, 0(r3)
/* 0C8034 800CD5D4 3884D494 */  addi    r4, r4, TRKEXICallBack@l
/* 0C8038 800CD5D8 7CC33378 */  mr      r3, r6
/* 0C803C 800CD5DC 7D8803A6 */  mtlr    r12
/* 0C8040 800CD5E0 4E800021 */  blrl    
/* 0C8044 800CD5E4 38600000 */  li      r3, 0
/* 0C8048 800CD5E8 38210008 */  addi    r1, r1, 8
/* 0C804C 800CD5EC 80010004 */  lwz     r0, 4(r1)
/* 0C8050 800CD5F0 7C0803A6 */  mtlr    r0
/* 0C8054 800CD5F4 4E800020 */  blr     

glabel EnableEXI2Interrupts
/* 0C8058 800CD5F8 7C0802A6 */  mflr    r0
/* 0C805C 800CD5FC 90010004 */  stw     r0, 4(r1)
/* 0C8060 800CD600 9421FFF8 */  stwu    r1, -8(r1)
/* 0C8064 800CD604 3C60800F */  lis     r3, gDBCommTable@ha
/* 0C8068 800CD608 38633B18 */  addi    r3, r3, gDBCommTable@l
/* 0C806C 800CD60C 81830004 */  lwz     r12, 4(r3)
/* 0C8070 800CD610 7D8803A6 */  mtlr    r12
/* 0C8074 800CD614 4E800021 */  blrl    
/* 0C8078 800CD618 38210008 */  addi    r1, r1, 8
/* 0C807C 800CD61C 80010004 */  lwz     r0, 4(r1)
/* 0C8080 800CD620 7C0803A6 */  mtlr    r0
/* 0C8084 800CD624 4E800020 */  blr     

glabel TRKPollUART
/* 0C8088 800CD628 7C0802A6 */  mflr    r0
/* 0C808C 800CD62C 90010004 */  stw     r0, 4(r1)
/* 0C8090 800CD630 9421FFF8 */  stwu    r1, -8(r1)
/* 0C8094 800CD634 3C60800F */  lis     r3, gDBCommTable@ha
/* 0C8098 800CD638 38633B18 */  addi    r3, r3, gDBCommTable@l
/* 0C809C 800CD63C 81830008 */  lwz     r12, 8(r3)
/* 0C80A0 800CD640 7D8803A6 */  mtlr    r12
/* 0C80A4 800CD644 4E800021 */  blrl    
/* 0C80A8 800CD648 38210008 */  addi    r1, r1, 8
/* 0C80AC 800CD64C 80010004 */  lwz     r0, 4(r1)
/* 0C80B0 800CD650 7C0803A6 */  mtlr    r0
/* 0C80B4 800CD654 4E800020 */  blr     

glabel TRK_ReadUARTN
/* 0C80B8 800CD658 7C0802A6 */  mflr    r0
/* 0C80BC 800CD65C 90010004 */  stw     r0, 4(r1)
/* 0C80C0 800CD660 9421FFF8 */  stwu    r1, -8(r1)
/* 0C80C4 800CD664 3CA0800F */  lis     r5, gDBCommTable@ha
/* 0C80C8 800CD668 38A53B18 */  addi    r5, r5, gDBCommTable@l
/* 0C80CC 800CD66C 8185000C */  lwz     r12, 0xc(r5)
/* 0C80D0 800CD670 7D8803A6 */  mtlr    r12
/* 0C80D4 800CD674 4E800021 */  blrl    
/* 0C80D8 800CD678 2C030000 */  cmpwi   r3, 0
/* 0C80DC 800CD67C 4082000C */  bne     lbl_800CD688
/* 0C80E0 800CD680 38600000 */  li      r3, 0
/* 0C80E4 800CD684 48000008 */  b       lbl_800CD68C
lbl_800CD688:
/* 0C80E8 800CD688 3860FFFF */  li      r3, -1
lbl_800CD68C:
/* 0C80EC 800CD68C 38210008 */  addi    r1, r1, 8
/* 0C80F0 800CD690 80010004 */  lwz     r0, 4(r1)
/* 0C80F4 800CD694 7C0803A6 */  mtlr    r0
/* 0C80F8 800CD698 4E800020 */  blr     

glabel TRK_WriteUARTN
/* 0C80FC 800CD69C 7C0802A6 */  mflr    r0
/* 0C8100 800CD6A0 90010004 */  stw     r0, 4(r1)
/* 0C8104 800CD6A4 9421FFF8 */  stwu    r1, -8(r1)
/* 0C8108 800CD6A8 3CA0800F */  lis     r5, gDBCommTable@ha
/* 0C810C 800CD6AC 38A53B18 */  addi    r5, r5, gDBCommTable@l
/* 0C8110 800CD6B0 81850010 */  lwz     r12, 0x10(r5)
/* 0C8114 800CD6B4 7D8803A6 */  mtlr    r12
/* 0C8118 800CD6B8 4E800021 */  blrl    
/* 0C811C 800CD6BC 2C030000 */  cmpwi   r3, 0
/* 0C8120 800CD6C0 4082000C */  bne     lbl_800CD6CC
/* 0C8124 800CD6C4 38600000 */  li      r3, 0
/* 0C8128 800CD6C8 48000008 */  b       lbl_800CD6D0
lbl_800CD6CC:
/* 0C812C 800CD6CC 3860FFFF */  li      r3, -1
lbl_800CD6D0:
/* 0C8130 800CD6D0 38210008 */  addi    r1, r1, 8
/* 0C8134 800CD6D4 80010004 */  lwz     r0, 4(r1)
/* 0C8138 800CD6D8 7C0803A6 */  mtlr    r0
/* 0C813C 800CD6DC 4E800020 */  blr     

glabel ReserveEXI2Port
/* 0C8140 800CD6E0 7C0802A6 */  mflr    r0
/* 0C8144 800CD6E4 90010004 */  stw     r0, 4(r1)
/* 0C8148 800CD6E8 9421FFF8 */  stwu    r1, -8(r1)
/* 0C814C 800CD6EC 3C60800F */  lis     r3, gDBCommTable@ha
/* 0C8150 800CD6F0 38633B18 */  addi    r3, r3, gDBCommTable@l
/* 0C8154 800CD6F4 81830014 */  lwz     r12, 0x14(r3)
/* 0C8158 800CD6F8 7D8803A6 */  mtlr    r12
/* 0C815C 800CD6FC 4E800021 */  blrl    
/* 0C8160 800CD700 38210008 */  addi    r1, r1, 8
/* 0C8164 800CD704 80010004 */  lwz     r0, 4(r1)
/* 0C8168 800CD708 7C0803A6 */  mtlr    r0
/* 0C816C 800CD70C 4E800020 */  blr     

glabel UnreserveEXI2Port
/* 0C8170 800CD710 7C0802A6 */  mflr    r0
/* 0C8174 800CD714 90010004 */  stw     r0, 4(r1)
/* 0C8178 800CD718 9421FFF8 */  stwu    r1, -8(r1)
/* 0C817C 800CD71C 3C60800F */  lis     r3, gDBCommTable@ha
/* 0C8180 800CD720 38633B18 */  addi    r3, r3, gDBCommTable@l
/* 0C8184 800CD724 81830018 */  lwz     r12, 0x18(r3)
/* 0C8188 800CD728 7D8803A6 */  mtlr    r12
/* 0C818C 800CD72C 4E800021 */  blrl    
/* 0C8190 800CD730 38210008 */  addi    r1, r1, 8
/* 0C8194 800CD734 80010004 */  lwz     r0, 4(r1)
/* 0C8198 800CD738 7C0803A6 */  mtlr    r0
/* 0C819C 800CD73C 4E800020 */  blr     

glabel TRK_board_display
/* 0C81A0 800CD740 7C0802A6 */  mflr    r0
/* 0C81A4 800CD744 90010004 */  stw     r0, 4(r1)
/* 0C81A8 800CD748 9421FFF8 */  stwu    r1, -8(r1)
/* 0C81AC 800CD74C 4CC63182 */  crclr   6
/* 0C81B0 800CD750 4BFD0EA9 */  bl      OSReport
/* 0C81B4 800CD754 38210008 */  addi    r1, r1, 8
/* 0C81B8 800CD758 80010004 */  lwz     r0, 4(r1)
/* 0C81BC 800CD75C 7C0803A6 */  mtlr    r0
/* 0C81C0 800CD760 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000F0B98 800F3B18 001C */
glabel gDBCommTable
    .long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
