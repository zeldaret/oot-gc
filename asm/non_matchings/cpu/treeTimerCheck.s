glabel treeTimerCheck
/* 02C1AC 8003174C 7C0802A6 */  mflr    r0
/* 02C1B0 80031750 90010004 */  stw     r0, 4(r1)
/* 02C1B4 80031754 9421FFE0 */  stwu    r1, -0x20(r1)
/* 02C1B8 80031758 93E1001C */  stw     r31, 0x1c(r1)
/* 02C1BC 8003175C 93C10018 */  stw     r30, 0x18(r1)
/* 02C1C0 80031760 3BC30000 */  addi    r30, r3, 0
/* 02C1C4 80031764 3C608000 */  lis     r3, 0x8000
/* 02C1C8 80031768 801E003C */  lwz     r0, 0x3c(r30)
/* 02C1CC 8003176C 3883F000 */  addi    r4, r3, -4096
/* 02C1D0 80031770 7C002000 */  cmpw    r0, r4
/* 02C1D4 80031774 408100D0 */  ble     lbl_80031844
/* 02C1D8 80031778 3C7E0001 */  addis   r3, r30, 1
/* 02C1DC 8003177C 83E312A0 */  lwz     r31, 0x12a0(r3)
/* 02C1E0 80031780 801F0070 */  lwz     r0, 0x70(r31)
/* 02C1E4 80031784 2C000000 */  cmpwi   r0, 0
/* 02C1E8 80031788 4182000C */  beq     lbl_80031794
/* 02C1EC 8003178C 38600000 */  li      r3, 0
/* 02C1F0 80031790 480000B8 */  b       lbl_80031848
lbl_80031794:
/* 02C1F4 80031794 38000000 */  li      r0, 0
/* 02C1F8 80031798 9081000C */  stw     r4, 0xc(r1)
/* 02C1FC 8003179C 90010010 */  stw     r0, 0x10(r1)
/* 02C200 800317A0 809F0068 */  lwz     r4, 0x68(r31)
/* 02C204 800317A4 28040000 */  cmplwi  r4, 0
/* 02C208 800317A8 41820018 */  beq     lbl_800317C0
/* 02C20C 800317AC 387E0000 */  addi    r3, r30, 0
/* 02C210 800317B0 38C10010 */  addi    r6, r1, 0x10
/* 02C214 800317B4 38E1000C */  addi    r7, r1, 0xc
/* 02C218 800317B8 38A00100 */  li      r5, 0x100
/* 02C21C 800317BC 4BFFF7C9 */  bl      treePrintNode
lbl_800317C0:
/* 02C220 800317C0 809F006C */  lwz     r4, 0x6c(r31)
/* 02C224 800317C4 28040000 */  cmplwi  r4, 0
/* 02C228 800317C8 41820018 */  beq     lbl_800317E0
/* 02C22C 800317CC 387E0000 */  addi    r3, r30, 0
/* 02C230 800317D0 38C10010 */  addi    r6, r1, 0x10
/* 02C234 800317D4 38E1000C */  addi    r7, r1, 0xc
/* 02C238 800317D8 38A00100 */  li      r5, 0x100
/* 02C23C 800317DC 4BFFF7A9 */  bl      treePrintNode
lbl_800317E0:
/* 02C240 800317E0 8061000C */  lwz     r3, 0xc(r1)
/* 02C244 800317E4 3803FFFD */  addi    r0, r3, -3
/* 02C248 800317E8 90010010 */  stw     r0, 0x10(r1)
/* 02C24C 800317EC 809F0068 */  lwz     r4, 0x68(r31)
/* 02C250 800317F0 28040000 */  cmplwi  r4, 0
/* 02C254 800317F4 41820018 */  beq     lbl_8003180C
/* 02C258 800317F8 387E0000 */  addi    r3, r30, 0
/* 02C25C 800317FC 38C10010 */  addi    r6, r1, 0x10
/* 02C260 80031800 38E1000C */  addi    r7, r1, 0xc
/* 02C264 80031804 38A01000 */  li      r5, 0x1000
/* 02C268 80031808 4BFFF77D */  bl      treePrintNode
lbl_8003180C:
/* 02C26C 8003180C 809F006C */  lwz     r4, 0x6c(r31)
/* 02C270 80031810 28040000 */  cmplwi  r4, 0
/* 02C274 80031814 41820018 */  beq     lbl_8003182C
/* 02C278 80031818 387E0000 */  addi    r3, r30, 0
/* 02C27C 8003181C 38C10010 */  addi    r6, r1, 0x10
/* 02C280 80031820 38E1000C */  addi    r7, r1, 0xc
/* 02C284 80031824 38A01000 */  li      r5, 0x1000
/* 02C288 80031828 4BFFF75D */  bl      treePrintNode
lbl_8003182C:
/* 02C28C 8003182C 80810010 */  lwz     r4, 0x10(r1)
/* 02C290 80031830 38600001 */  li      r3, 1
/* 02C294 80031834 801E003C */  lwz     r0, 0x3c(r30)
/* 02C298 80031838 7C040050 */  subf    r0, r4, r0
/* 02C29C 8003183C 901E003C */  stw     r0, 0x3c(r30)
/* 02C2A0 80031840 48000008 */  b       lbl_80031848
lbl_80031844:
/* 02C2A4 80031844 38600000 */  li      r3, 0
lbl_80031848:
/* 02C2A8 80031848 80010024 */  lwz     r0, 0x24(r1)
/* 02C2AC 8003184C 83E1001C */  lwz     r31, 0x1c(r1)
/* 02C2B0 80031850 83C10018 */  lwz     r30, 0x18(r1)
/* 02C2B4 80031854 7C0803A6 */  mtlr    r0
/* 02C2B8 80031858 38210020 */  addi    r1, r1, 0x20
/* 02C2BC 8003185C 4E800020 */  blr     
