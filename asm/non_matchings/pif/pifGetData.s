glabel pifGetData
/* 066AF0 8006C090 7C0802A6 */  mflr    r0
/* 066AF4 8006C094 90010004 */  stw     r0, 4(r1)
/* 066AF8 8006C098 9421FFE8 */  stwu    r1, -0x18(r1)
/* 066AFC 8006C09C 93E10014 */  stw     r31, 0x14(r1)
/* 066B00 8006C0A0 3BE40000 */  addi    r31, r4, 0
/* 066B04 8006C0A4 93C10010 */  stw     r30, 0x10(r1)
/* 066B08 8006C0A8 3BC30000 */  addi    r30, r3, 0
/* 066B0C 8006C0AC 480000B1 */  bl      pifProcessOutputData
/* 066B10 8006C0B0 2C030000 */  cmpwi   r3, 0
/* 066B14 8006C0B4 4082000C */  bne     lbl_8006C0C0
/* 066B18 8006C0B8 38600000 */  li      r3, 0
/* 066B1C 8006C0BC 48000028 */  b       lbl_8006C0E4
lbl_8006C0C0:
/* 066B20 8006C0C0 809E0004 */  lwz     r4, 4(r30)
/* 066B24 8006C0C4 387F0000 */  addi    r3, r31, 0
/* 066B28 8006C0C8 38A00040 */  li      r5, 0x40
/* 066B2C 8006C0CC 4BF9AA25 */  bl      xlHeapCopy
/* 066B30 8006C0D0 2C030000 */  cmpwi   r3, 0
/* 066B34 8006C0D4 4082000C */  bne     lbl_8006C0E0
/* 066B38 8006C0D8 38600000 */  li      r3, 0
/* 066B3C 8006C0DC 48000008 */  b       lbl_8006C0E4
lbl_8006C0E0:
/* 066B40 8006C0E0 38600001 */  li      r3, 1
lbl_8006C0E4:
/* 066B44 8006C0E4 8001001C */  lwz     r0, 0x1c(r1)
/* 066B48 8006C0E8 83E10014 */  lwz     r31, 0x14(r1)
/* 066B4C 8006C0EC 83C10010 */  lwz     r30, 0x10(r1)
/* 066B50 8006C0F0 7C0803A6 */  mtlr    r0
/* 066B54 8006C0F4 38210018 */  addi    r1, r1, 0x18
/* 066B58 8006C0F8 4E800020 */  blr     
