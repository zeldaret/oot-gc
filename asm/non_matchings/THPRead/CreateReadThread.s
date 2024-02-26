glabel CreateReadThread
/* 00C5C0 80011B60 7C0802A6 */  mflr    r0
/* 00C5C4 80011B64 3C808010 */  lis     r4, FreeReadBufferQueue@ha
/* 00C5C8 80011B68 90010004 */  stw     r0, 4(r1)
/* 00C5CC 80011B6C 39030000 */  addi    r8, r3, 0
/* 00C5D0 80011B70 38A00000 */  li      r5, 0
/* 00C5D4 80011B74 9421FFE8 */  stwu    r1, -0x18(r1)
/* 00C5D8 80011B78 38E01000 */  li      r7, 0x1000
/* 00C5DC 80011B7C 39200001 */  li      r9, 1
/* 00C5E0 80011B80 93E10014 */  stw     r31, 0x14(r1)
/* 00C5E4 80011B84 3BE4B1C0 */  addi    r31, r4, FreeReadBufferQueue@l
/* 00C5E8 80011B88 3C808001 */  lis     r4, Reader@ha
/* 00C5EC 80011B8C 38841A00 */  addi    r4, r4, Reader@l
/* 00C5F0 80011B90 387F00D8 */  addi    r3, r31, 0xd8
/* 00C5F4 80011B94 38DF13F0 */  addi    r6, r31, 0x13f0
/* 00C5F8 80011B98 4808FBF5 */  bl      OSCreateThread
/* 00C5FC 80011B9C 2C030000 */  cmpwi   r3, 0
/* 00C600 80011BA0 4082001C */  bne     lbl_80011BBC
/* 00C604 80011BA4 3C60800F */  lis     r3, D_800EA4B0@ha
/* 00C608 80011BA8 4CC63182 */  crclr   6
/* 00C60C 80011BAC 3863A4B0 */  addi    r3, r3, D_800EA4B0@l
/* 00C610 80011BB0 4808CA49 */  bl      OSReport
/* 00C614 80011BB4 38600000 */  li      r3, 0
/* 00C618 80011BB8 48000040 */  b       lbl_80011BF8
lbl_80011BBC:
/* 00C61C 80011BBC 387F0000 */  addi    r3, r31, 0
/* 00C620 80011BC0 389F0060 */  addi    r4, r31, 0x60
/* 00C624 80011BC4 38A0000A */  li      r5, 0xa
/* 00C628 80011BC8 4808D9B9 */  bl      OSInitMessageQueue
/* 00C62C 80011BCC 387F0020 */  addi    r3, r31, 0x20
/* 00C630 80011BD0 389F0088 */  addi    r4, r31, 0x88
/* 00C634 80011BD4 38A0000A */  li      r5, 0xa
/* 00C638 80011BD8 4808D9A9 */  bl      OSInitMessageQueue
/* 00C63C 80011BDC 387F0040 */  addi    r3, r31, 0x40
/* 00C640 80011BE0 389F00B0 */  addi    r4, r31, 0xb0
/* 00C644 80011BE4 38A0000A */  li      r5, 0xa
/* 00C648 80011BE8 4808D999 */  bl      OSInitMessageQueue
/* 00C64C 80011BEC 38000001 */  li      r0, 1
/* 00C650 80011BF0 900D8960 */  stw     r0, ReadThreadCreated@sda21(r13)
/* 00C654 80011BF4 38600001 */  li      r3, 1
lbl_80011BF8:
/* 00C658 80011BF8 8001001C */  lwz     r0, 0x1c(r1)
/* 00C65C 80011BFC 83E10014 */  lwz     r31, 0x14(r1)
/* 00C660 80011C00 38210018 */  addi    r1, r1, 0x18
/* 00C664 80011C04 7C0803A6 */  mtlr    r0
/* 00C668 80011C08 4E800020 */  blr     
