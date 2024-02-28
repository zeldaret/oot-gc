glabel soundCallbackBeep
/* 017284 8001C824 7C0802A6 */  mflr    r0
/* 017288 8001C828 90010004 */  stw     r0, 4(r1)
/* 01728C 8001C82C 9421FFF0 */  stwu    r1, -0x10(r1)
/* 017290 8001C830 93E1000C */  stw     r31, 0xc(r1)
/* 017294 8001C834 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 017298 8001C838 83E30004 */  lwz     r31, 4(r3)
/* 01729C 8001C83C 807F00B8 */  lwz     r3, 0xb8(r31)
/* 0172A0 8001C840 809F00CC */  lwz     r4, 0xcc(r31)
/* 0172A4 8001C844 4809B785 */  bl      AIInitDMA
/* 0172A8 8001C848 807F0090 */  lwz     r3, 0x90(r31)
/* 0172AC 8001C84C 38030001 */  addi    r0, r3, 1
/* 0172B0 8001C850 2C000002 */  cmpwi   r0, 2
/* 0172B4 8001C854 901F0090 */  stw     r0, 0x90(r31)
/* 0172B8 8001C858 40820014 */  bne     lbl_8001C86C
/* 0172BC 8001C85C 4809B81D */  bl      AIStopDMA
/* 0172C0 8001C860 3C608002 */  lis     r3, soundCallbackDMA@ha
/* 0172C4 8001C864 3863CCA4 */  addi    r3, r3, soundCallbackDMA@l
/* 0172C8 8001C868 4809B71D */  bl      AIRegisterDMACallback
lbl_8001C86C:
/* 0172CC 8001C86C 80010014 */  lwz     r0, 0x14(r1)
/* 0172D0 8001C870 83E1000C */  lwz     r31, 0xc(r1)
/* 0172D4 8001C874 38210010 */  addi    r1, r1, 0x10
/* 0172D8 8001C878 7C0803A6 */  mtlr    r0
/* 0172DC 8001C87C 4E800020 */  blr     
