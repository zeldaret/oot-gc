glabel movieReset
/* 00C66C 80011C0C 7C0802A6 */  mflr    r0
/* 00C670 80011C10 90010004 */  stw     r0, 4(r1)
/* 00C674 80011C14 9421FFE8 */  stwu    r1, -0x18(r1)
/* 00C678 80011C18 93E10014 */  stw     r31, 0x14(r1)
/* 00C67C 80011C1C 3BE40000 */  addi    r31, r4, 0
/* 00C680 80011C20 93C10010 */  stw     r30, 0x10(r1)
/* 00C684 80011C24 3BC30000 */  addi    r30, r3, 0
/* 00C688 80011C28 38600001 */  li      r3, 1
/* 00C68C 80011C2C 48095B7D */  bl      VISetBlack
/* 00C690 80011C30 480959DD */  bl      VIFlush
/* 00C694 80011C34 48094CE9 */  bl      VIWaitForRetrace
/* 00C698 80011C38 3C60F000 */  lis     r3, 0xf000
/* 00C69C 80011C3C 4809EC91 */  bl      PADRecalibrate
/* 00C6A0 80011C40 4809910D */  bl      GXAbortFrame
/* 00C6A4 80011C44 4808BD4D */  bl      LCDisable
/* 00C6A8 80011C48 48094CD5 */  bl      VIWaitForRetrace
/* 00C6AC 80011C4C 2C1E0001 */  cmpwi   r30, 1
/* 00C6B0 80011C50 40820034 */  bne     lbl_80011C84
/* 00C6B4 80011C54 2C1F0001 */  cmpwi   r31, 1
/* 00C6B8 80011C58 40820018 */  bne     lbl_80011C70
/* 00C6BC 80011C5C 38600001 */  li      r3, 1
/* 00C6C0 80011C60 38800000 */  li      r4, 0
/* 00C6C4 80011C64 38A00001 */  li      r5, 1
/* 00C6C8 80011C68 4808E2FD */  bl      OSResetSystem
/* 00C6CC 80011C6C 48000028 */  b       lbl_80011C94
lbl_80011C70:
/* 00C6D0 80011C70 38600001 */  li      r3, 1
/* 00C6D4 80011C74 38800000 */  li      r4, 0
/* 00C6D8 80011C78 38A00000 */  li      r5, 0
/* 00C6DC 80011C7C 4808E2E9 */  bl      OSResetSystem
/* 00C6E0 80011C80 48000014 */  b       lbl_80011C94
lbl_80011C84:
/* 00C6E4 80011C84 38600000 */  li      r3, 0
/* 00C6E8 80011C88 38800000 */  li      r4, 0
/* 00C6EC 80011C8C 38A00000 */  li      r5, 0
/* 00C6F0 80011C90 4808E2D5 */  bl      OSResetSystem
lbl_80011C94:
/* 00C6F4 80011C94 8001001C */  lwz     r0, 0x1c(r1)
/* 00C6F8 80011C98 83E10014 */  lwz     r31, 0x14(r1)
/* 00C6FC 80011C9C 83C10010 */  lwz     r30, 0x10(r1)
/* 00C700 80011CA0 7C0803A6 */  mtlr    r0
/* 00C704 80011CA4 38210018 */  addi    r1, r1, 0x18
/* 00C708 80011CA8 4E800020 */  blr     
