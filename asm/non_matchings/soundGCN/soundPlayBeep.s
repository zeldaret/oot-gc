glabel soundPlayBeep
/* 0170F0 8001C690 7C0802A6 */  mflr    r0
/* 0170F4 8001C694 90010004 */  stw     r0, 4(r1)
/* 0170F8 8001C698 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0170FC 8001C69C 93E1001C */  stw     r31, 0x1c(r1)
/* 017100 8001C6A0 549F103A */  slwi    r31, r4, 2
/* 017104 8001C6A4 93C10018 */  stw     r30, 0x18(r1)
/* 017108 8001C6A8 93A10014 */  stw     r29, 0x14(r1)
/* 01710C 8001C6AC 3BA30000 */  addi    r29, r3, 0
/* 017110 8001C6B0 7FDDFA14 */  add     r30, r29, r31
/* 017114 8001C6B4 841E00A0 */  lwzu    r0, 0xa0(r30)
/* 017118 8001C6B8 28000000 */  cmplwi  r0, 0
/* 01711C 8001C6BC 41820030 */  beq     lbl_8001C6EC
/* 017120 8001C6C0 4809B9B9 */  bl      AIStopDMA
/* 017124 8001C6C4 38000000 */  li      r0, 0
/* 017128 8001C6C8 3C608002 */  lis     r3, soundCallbackBeep@ha
/* 01712C 8001C6CC 901D0090 */  stw     r0, 0x90(r29)
/* 017130 8001C6D0 3863C824 */  addi    r3, r3, soundCallbackBeep@l
/* 017134 8001C6D4 4809B8B1 */  bl      AIRegisterDMACallback
/* 017138 8001C6D8 7C9DFA14 */  add     r4, r29, r31
/* 01713C 8001C6DC 807E0000 */  lwz     r3, 0(r30)
/* 017140 8001C6E0 80840094 */  lwz     r4, 0x94(r4)
/* 017144 8001C6E4 4809B8E5 */  bl      AIInitDMA
/* 017148 8001C6E8 4809B979 */  bl      AIStartDMA
lbl_8001C6EC:
/* 01714C 8001C6EC 80010024 */  lwz     r0, 0x24(r1)
/* 017150 8001C6F0 38600001 */  li      r3, 1
/* 017154 8001C6F4 83E1001C */  lwz     r31, 0x1c(r1)
/* 017158 8001C6F8 83C10018 */  lwz     r30, 0x18(r1)
/* 01715C 8001C6FC 7C0803A6 */  mtlr    r0
/* 017160 8001C700 83A10014 */  lwz     r29, 0x14(r1)
/* 017164 8001C704 38210020 */  addi    r1, r1, 0x20
/* 017168 8001C708 4E800020 */  blr     
