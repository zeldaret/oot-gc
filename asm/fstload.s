# fstload.c
.include "macros.inc"

.section .text, "ax"

.balign 4

cb:
/* 0B05BC 800B5B5C 7C0802A6 */  mflr    r0
/* 0B05C0 800B5B60 2C030000 */  cmpwi   r3, 0
/* 0B05C4 800B5B64 90010004 */  stw     r0, 4(r1)
/* 0B05C8 800B5B68 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0B05CC 800B5B6C 93E10014 */  stw     r31, 0x14(r1)
/* 0B05D0 800B5B70 3BE40000 */  addi    r31, r4, 0
/* 0B05D4 800B5B74 4081007C */  ble     lbl_800B5BF0
/* 0B05D8 800B5B78 800D8D80 */  lwz     r0, status-_SDA_BASE_(r13)
/* 0B05DC 800B5B7C 2C000001 */  cmpwi   r0, 1
/* 0B05E0 800B5B80 4182003C */  beq     lbl_800B5BBC
/* 0B05E4 800B5B84 4080009C */  bge     lbl_800B5C20
/* 0B05E8 800B5B88 2C000000 */  cmpwi   r0, 0
/* 0B05EC 800B5B8C 40800008 */  bge     lbl_800B5B94
/* 0B05F0 800B5B90 48000090 */  b       lbl_800B5C20
lbl_800B5B94:
/* 0B05F4 800B5B94 38000001 */  li      r0, 1
/* 0B05F8 800B5B98 808D8D84 */  lwz     r4, bb2-_SDA_BASE_(r13)
/* 0B05FC 800B5B9C 3C60800B */  lis     r3, cb@ha
/* 0B0600 800B5BA0 900D8D80 */  stw     r0, status-_SDA_BASE_(r13)
/* 0B0604 800B5BA4 38E35B5C */  addi    r7, r3, cb@l
/* 0B0608 800B5BA8 387F0000 */  addi    r3, r31, 0
/* 0B060C 800B5BAC 38A00020 */  li      r5, 0x20
/* 0B0610 800B5BB0 38C00420 */  li      r6, 0x420
/* 0B0614 800B5BB4 4BFFF085 */  bl      DVDReadAbsAsyncForBS
/* 0B0618 800B5BB8 48000068 */  b       lbl_800B5C20
lbl_800B5BBC:
/* 0B061C 800B5BBC 38000002 */  li      r0, 2
/* 0B0620 800B5BC0 80CD8D84 */  lwz     r6, bb2-_SDA_BASE_(r13)
/* 0B0624 800B5BC4 900D8D80 */  stw     r0, status-_SDA_BASE_(r13)
/* 0B0628 800B5BC8 3C60800B */  lis     r3, cb@ha
/* 0B062C 800B5BCC 38E35B5C */  addi    r7, r3, cb@l
/* 0B0630 800B5BD0 80A60008 */  lwz     r5, 8(r6)
/* 0B0634 800B5BD4 7FE3FB78 */  mr      r3, r31
/* 0B0638 800B5BD8 80860010 */  lwz     r4, 0x10(r6)
/* 0B063C 800B5BDC 3805001F */  addi    r0, r5, 0x1f
/* 0B0640 800B5BE0 80C60004 */  lwz     r6, 4(r6)
/* 0B0644 800B5BE4 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 0B0648 800B5BE8 4BFFF051 */  bl      DVDReadAbsAsyncForBS
/* 0B064C 800B5BEC 48000034 */  b       lbl_800B5C20
lbl_800B5BF0:
/* 0B0650 800B5BF0 2C03FFFF */  cmpwi   r3, -1
/* 0B0654 800B5BF4 4182002C */  beq     lbl_800B5C20
/* 0B0658 800B5BF8 2C03FFFC */  cmpwi   r3, -4
/* 0B065C 800B5BFC 40820024 */  bne     lbl_800B5C20
/* 0B0660 800B5C00 38000000 */  li      r0, 0
/* 0B0664 800B5C04 900D8D80 */  stw     r0, status-_SDA_BASE_(r13)
/* 0B0668 800B5C08 4BFFF361 */  bl      DVDReset
/* 0B066C 800B5C0C 3C60800B */  lis     r3, cb@ha
/* 0B0670 800B5C10 808D8D88 */  lwz     r4, idTmp-_SDA_BASE_(r13)
/* 0B0674 800B5C14 38A35B5C */  addi    r5, r3, cb@l
/* 0B0678 800B5C18 387F0000 */  addi    r3, r31, 0
/* 0B067C 800B5C1C 4BFFF0ED */  bl      DVDReadDiskID
lbl_800B5C20:
/* 0B0680 800B5C20 8001001C */  lwz     r0, 0x1c(r1)
/* 0B0684 800B5C24 83E10014 */  lwz     r31, 0x14(r1)
/* 0B0688 800B5C28 38210018 */  addi    r1, r1, 0x18
/* 0B068C 800B5C2C 7C0803A6 */  mtlr    r0
/* 0B0690 800B5C30 4E800020 */  blr     

glabel __fstLoad
/* 0B0694 800B5C34 7C0802A6 */  mflr    r0
/* 0B0698 800B5C38 3C60800F */  lis     r3, D_800F2628@ha
/* 0B069C 800B5C3C 90010004 */  stw     r0, 4(r1)
/* 0B06A0 800B5C40 9421FFA0 */  stwu    r1, -0x60(r1)
/* 0B06A4 800B5C44 93E1005C */  stw     r31, 0x5c(r1)
/* 0B06A8 800B5C48 3BE32628 */  addi    r31, r3, D_800F2628@l
/* 0B06AC 800B5C4C 93C10058 */  stw     r30, 0x58(r1)
/* 0B06B0 800B5C50 93A10054 */  stw     r29, 0x54(r1)
/* 0B06B4 800B5C54 4BFE7835 */  bl      OSGetArenaHi
/* 0B06B8 800B5C58 3C608013 */  lis     r3, bb2Buf@ha
/* 0B06BC 800B5C5C 38632658 */  addi    r3, r3, bb2Buf@l
/* 0B06C0 800B5C60 3881002B */  addi    r4, r1, 0x2b
/* 0B06C4 800B5C64 3803001F */  addi    r0, r3, 0x1f
/* 0B06C8 800B5C68 54830034 */  rlwinm  r3, r4, 0, 0, 0x1a
/* 0B06CC 800B5C6C 54000034 */  rlwinm  r0, r0, 0, 0, 0x1a
/* 0B06D0 800B5C70 906D8D88 */  stw     r3, idTmp-_SDA_BASE_(r13)
/* 0B06D4 800B5C74 900D8D84 */  stw     r0, bb2-_SDA_BASE_(r13)
/* 0B06D8 800B5C78 4BFFF2F1 */  bl      DVDReset
/* 0B06DC 800B5C7C 3C608013 */  lis     r3, block$18@ha
/* 0B06E0 800B5C80 808D8D88 */  lwz     r4, idTmp-_SDA_BASE_(r13)
/* 0B06E4 800B5C84 3CA0800B */  lis     r5, cb@ha
/* 0B06E8 800B5C88 38632698 */  addi    r3, r3, block$18@l
/* 0B06EC 800B5C8C 38A55B5C */  addi    r5, r5, cb@l
/* 0B06F0 800B5C90 4BFFF079 */  bl      DVDReadDiskID
lbl_800B5C94:
/* 0B06F4 800B5C94 4BFFF365 */  bl      DVDGetDriveStatus
/* 0B06F8 800B5C98 2C030000 */  cmpwi   r3, 0
/* 0B06FC 800B5C9C 4082FFF8 */  bne     lbl_800B5C94
/* 0B0700 800B5CA0 806D8D84 */  lwz     r3, bb2-_SDA_BASE_(r13)
/* 0B0704 800B5CA4 3FA08000 */  lis     r29, 0x8000
/* 0B0708 800B5CA8 3FC08000 */  lis     r30, 0x8000
/* 0B070C 800B5CAC 80030010 */  lwz     r0, 0x10(r3)
/* 0B0710 800B5CB0 387D0000 */  addi    r3, r29, 0
/* 0B0714 800B5CB4 38A00020 */  li      r5, 0x20
/* 0B0718 800B5CB8 901E0038 */  stw     r0, 0x38(r30)
/* 0B071C 800B5CBC 808D8D84 */  lwz     r4, bb2-_SDA_BASE_(r13)
/* 0B0720 800B5CC0 8004000C */  lwz     r0, 0xc(r4)
/* 0B0724 800B5CC4 901E003C */  stw     r0, 0x3c(r30)
/* 0B0728 800B5CC8 808D8D88 */  lwz     r4, idTmp-_SDA_BASE_(r13)
/* 0B072C 800B5CCC 4BF4F7F9 */  bl      memcpy
/* 0B0730 800B5CD0 386D8830 */  addi    r3, r13, D_80135510-_SDA_BASE_
/* 0B0734 800B5CD4 4CC63182 */  crclr   6
/* 0B0738 800B5CD8 4BFE8921 */  bl      OSReport
/* 0B073C 800B5CDC 889D0000 */  lbz     r4, 0(r29)
/* 0B0740 800B5CE0 7FE3FB78 */  mr      r3, r31
/* 0B0744 800B5CE4 88BD0001 */  lbz     r5, 1(r29)
/* 0B0748 800B5CE8 4CC63182 */  crclr   6
/* 0B074C 800B5CEC 88DD0002 */  lbz     r6, 2(r29)
/* 0B0750 800B5CF0 88FD0003 */  lbz     r7, 3(r29)
/* 0B0754 800B5CF4 7C840774 */  extsb   r4, r4
/* 0B0758 800B5CF8 7CA50774 */  extsb   r5, r5
/* 0B075C 800B5CFC 7CC60774 */  extsb   r6, r6
/* 0B0760 800B5D00 7CE70774 */  extsb   r7, r7
/* 0B0764 800B5D04 4BFE88F5 */  bl      OSReport
/* 0B0768 800B5D08 889D0004 */  lbz     r4, 4(r29)
/* 0B076C 800B5D0C 387F001C */  addi    r3, r31, 0x1c
/* 0B0770 800B5D10 88BD0005 */  lbz     r5, 5(r29)
/* 0B0774 800B5D14 4CC63182 */  crclr   6
/* 0B0778 800B5D18 7C840774 */  extsb   r4, r4
/* 0B077C 800B5D1C 7CA50774 */  extsb   r5, r5
/* 0B0780 800B5D20 4BFE88D9 */  bl      OSReport
/* 0B0784 800B5D24 889D0006 */  lbz     r4, 6(r29)
/* 0B0788 800B5D28 387F0034 */  addi    r3, r31, 0x34
/* 0B078C 800B5D2C 4CC63182 */  crclr   6
/* 0B0790 800B5D30 4BFE88C9 */  bl      OSReport
/* 0B0794 800B5D34 889D0007 */  lbz     r4, 7(r29)
/* 0B0798 800B5D38 387F0048 */  addi    r3, r31, 0x48
/* 0B079C 800B5D3C 4CC63182 */  crclr   6
/* 0B07A0 800B5D40 4BFE88B9 */  bl      OSReport
/* 0B07A4 800B5D44 881E0008 */  lbz     r0, 8(r30)
/* 0B07A8 800B5D48 28000000 */  cmplwi  r0, 0
/* 0B07AC 800B5D4C 4082000C */  bne     lbl_800B5D58
/* 0B07B0 800B5D50 388D8834 */  addi    r4, r13, D_80135514-_SDA_BASE_
/* 0B07B4 800B5D54 48000008 */  b       lbl_800B5D5C
lbl_800B5D58:
/* 0B07B8 800B5D58 388D8838 */  addi    r4, r13, D_80135518-_SDA_BASE_
lbl_800B5D5C:
/* 0B07BC 800B5D5C 4CC63182 */  crclr   6
/* 0B07C0 800B5D60 387F005C */  addi    r3, r31, 0x5c
/* 0B07C4 800B5D64 4BFE8895 */  bl      OSReport
/* 0B07C8 800B5D68 386D8830 */  addi    r3, r13, D_80135510-_SDA_BASE_
/* 0B07CC 800B5D6C 4CC63182 */  crclr   6
/* 0B07D0 800B5D70 4BFE8889 */  bl      OSReport
/* 0B07D4 800B5D74 806D8D84 */  lwz     r3, bb2-_SDA_BASE_(r13)
/* 0B07D8 800B5D78 80630010 */  lwz     r3, 0x10(r3)
/* 0B07DC 800B5D7C 4BFE771D */  bl      OSSetArenaHi
/* 0B07E0 800B5D80 80010064 */  lwz     r0, 0x64(r1)
/* 0B07E4 800B5D84 83E1005C */  lwz     r31, 0x5c(r1)
/* 0B07E8 800B5D88 83C10058 */  lwz     r30, 0x58(r1)
/* 0B07EC 800B5D8C 83A10054 */  lwz     r29, 0x54(r1)
/* 0B07F0 800B5D90 38210060 */  addi    r1, r1, 0x60
/* 0B07F4 800B5D94 7C0803A6 */  mtlr    r0
/* 0B07F8 800B5D98 4E800020 */  blr     


.section .data, "wa"

.balign 8

/* 000EF6A8 800F2628 001A */
D_800F2628:
    .asciz "  Game Name ... %c%c%c%c\n"

.balign 4

/* 000EF6C4 800F2644 0016 */
D_800F2644:
    .asciz "  Company ..... %c%c\n"

.balign 4

/* 000EF6DC 800F265C 0014 */
D_800F265C:
    .asciz "  Disk # ...... %d\n"

.balign 4

/* 000EF6F0 800F2670 0014 */
D_800F2670:
    .asciz "  Game ver .... %d\n"

.balign 4

/* 000EF704 800F2684 0014 */
D_800F2684:
    .asciz "  Streaming ... %s\n"


.section .bss, "wa"

.balign 4

/* 0012F6D8 80132658 003F */
bb2Buf:
    .skip 63

.balign 4

/* 0012F718 80132698 0030 */
block$18:
    .skip 48


.section .sdata, "wa"

.balign 8

/* 000F1790 80135510 0002 */
D_80135510:
    .asciz "\n"

.balign 4

/* 000F1794 80135514 0004 */
D_80135514:
    .asciz "OFF"

.balign 4

/* 000F1798 80135518 0003 */
D_80135518:
    .asciz "ON"


.section .sbss, "wa"

.balign 8

/* 000F1CE0 80135A60 0004 */
status:
    .skip 4

.balign 4

/* 000F1CE4 80135A64 0004 */
bb2:
    .skip 4

.balign 4

/* 000F1CE8 80135A68 0004 */
idTmp:
    .skip 4


