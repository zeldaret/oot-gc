glabel simulatorReadPak
/* 003A98 80009038 7C0802A6 */  mflr    r0
/* 003A9C 8000903C 90010004 */  stw     r0, 4(r1)
/* 003AA0 80009040 9421FFD8 */  stwu    r1, -0x28(r1)
/* 003AA4 80009044 93E10024 */  stw     r31, 0x24(r1)
/* 003AA8 80009048 3BE50000 */  addi    r31, r5, 0
/* 003AAC 8000904C 38A10014 */  addi    r5, r1, 0x14
/* 003AB0 80009050 93C10020 */  stw     r30, 0x20(r1)
/* 003AB4 80009054 3BC40000 */  addi    r30, r4, 0
/* 003AB8 80009058 93A1001C */  stw     r29, 0x1c(r1)
/* 003ABC 8000905C 3BA30000 */  addi    r29, r3, 0
/* 003AC0 80009060 389D0000 */  addi    r4, r29, 0
/* 003AC4 80009064 80CD8920 */  lwz     r6, gpSystem@sda21(r13)
/* 003AC8 80009068 80660028 */  lwz     r3, 0x28(r6)
/* 003ACC 8000906C 48063911 */  bl      pifGetEControllerType
/* 003AD0 80009070 80010014 */  lwz     r0, 0x14(r1)
/* 003AD4 80009074 2C000003 */  cmpwi   r0, 3
/* 003AD8 80009078 4082001C */  bne     lbl_80009094
/* 003ADC 8000907C 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 003AE0 80009080 389D0000 */  addi    r4, r29, 0
/* 003AE4 80009084 38BE0000 */  addi    r5, r30, 0
/* 003AE8 80009088 80630028 */  lwz     r3, 0x28(r3)
/* 003AEC 8000908C 7FE6FB78 */  mr      r6, r31
/* 003AF0 80009090 48063BE5 */  bl      pifReadRumble
lbl_80009094:
/* 003AF4 80009094 8001002C */  lwz     r0, 0x2c(r1)
/* 003AF8 80009098 38600001 */  li      r3, 1
/* 003AFC 8000909C 83E10024 */  lwz     r31, 0x24(r1)
/* 003B00 800090A0 83C10020 */  lwz     r30, 0x20(r1)
/* 003B04 800090A4 7C0803A6 */  mtlr    r0
/* 003B08 800090A8 83A1001C */  lwz     r29, 0x1c(r1)
/* 003B0C 800090AC 38210028 */  addi    r1, r1, 0x28
/* 003B10 800090B0 4E800020 */  blr     
