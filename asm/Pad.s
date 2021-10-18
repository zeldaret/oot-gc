# Pad.c
.include "macros.inc"

.section .text, "ax"

.balign 4

UpdateOrigin:
/* 0AA9A4 800AFF44 7C0802A6 */  mflr    r0
/* 0AA9A8 800AFF48 3CA08013 */  lis     r5, Origin@ha
/* 0AA9AC 800AFF4C 90010004 */  stw     r0, 4(r1)
/* 0AA9B0 800AFF50 1CC3000C */  mulli   r6, r3, 0xc
/* 0AA9B4 800AFF54 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AA9B8 800AFF58 38A52478 */  addi    r5, r5, Origin@l
/* 0AA9BC 800AFF5C 93E10014 */  stw     r31, 0x14(r1)
/* 0AA9C0 800AFF60 7FE53214 */  add     r31, r5, r6
/* 0AA9C4 800AFF64 800D87F4 */  lwz     r0, AnalogMode@sda21(r13)
/* 0AA9C8 800AFF68 5404056E */  rlwinm  r4, r0, 0, 0x15, 0x17
/* 0AA9CC 800AFF6C 2C040400 */  cmpwi   r4, 0x400
/* 0AA9D0 800AFF70 3C008000 */  lis     r0, 0x8000
/* 0AA9D4 800AFF74 7C001C30 */  srw     r0, r0, r3
/* 0AA9D8 800AFF78 418200F4 */  beq     lbl_800B006C
/* 0AA9DC 800AFF7C 40800034 */  bge     lbl_800AFFB0
/* 0AA9E0 800AFF80 2C040200 */  cmpwi   r4, 0x200
/* 0AA9E4 800AFF84 418200B8 */  beq     lbl_800B003C
/* 0AA9E8 800AFF88 4080001C */  bge     lbl_800AFFA4
/* 0AA9EC 800AFF8C 2C040100 */  cmpwi   r4, 0x100
/* 0AA9F0 800AFF90 41820078 */  beq     lbl_800B0008
/* 0AA9F4 800AFF94 408000D8 */  bge     lbl_800B006C
/* 0AA9F8 800AFF98 2C040000 */  cmpwi   r4, 0
/* 0AA9FC 800AFF9C 41820038 */  beq     lbl_800AFFD4
/* 0AAA00 800AFFA0 480000CC */  b       lbl_800B006C
lbl_800AFFA4:
/* 0AAA04 800AFFA4 2C040300 */  cmpwi   r4, 0x300
/* 0AAA08 800AFFA8 418200C4 */  beq     lbl_800B006C
/* 0AAA0C 800AFFAC 480000C0 */  b       lbl_800B006C
lbl_800AFFB0:
/* 0AAA10 800AFFB0 2C040600 */  cmpwi   r4, 0x600
/* 0AAA14 800AFFB4 41820020 */  beq     lbl_800AFFD4
/* 0AAA18 800AFFB8 40800010 */  bge     lbl_800AFFC8
/* 0AAA1C 800AFFBC 2C040500 */  cmpwi   r4, 0x500
/* 0AAA20 800AFFC0 41820014 */  beq     lbl_800AFFD4
/* 0AAA24 800AFFC4 480000A8 */  b       lbl_800B006C
lbl_800AFFC8:
/* 0AAA28 800AFFC8 2C040700 */  cmpwi   r4, 0x700
/* 0AAA2C 800AFFCC 41820008 */  beq     lbl_800AFFD4
/* 0AAA30 800AFFD0 4800009C */  b       lbl_800B006C
lbl_800AFFD4:
/* 0AAA34 800AFFD4 889F0006 */  lbz     r4, 6(r31)
/* 0AAA38 800AFFD8 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAA3C 800AFFDC 989F0006 */  stb     r4, 6(r31)
/* 0AAA40 800AFFE0 889F0007 */  lbz     r4, 7(r31)
/* 0AAA44 800AFFE4 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAA48 800AFFE8 989F0007 */  stb     r4, 7(r31)
/* 0AAA4C 800AFFEC 889F0008 */  lbz     r4, 8(r31)
/* 0AAA50 800AFFF0 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAA54 800AFFF4 989F0008 */  stb     r4, 8(r31)
/* 0AAA58 800AFFF8 889F0009 */  lbz     r4, 9(r31)
/* 0AAA5C 800AFFFC 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAA60 800B0000 989F0009 */  stb     r4, 9(r31)
/* 0AAA64 800B0004 48000068 */  b       lbl_800B006C
lbl_800B0008:
/* 0AAA68 800B0008 889F0004 */  lbz     r4, 4(r31)
/* 0AAA6C 800B000C 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAA70 800B0010 989F0004 */  stb     r4, 4(r31)
/* 0AAA74 800B0014 889F0005 */  lbz     r4, 5(r31)
/* 0AAA78 800B0018 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAA7C 800B001C 989F0005 */  stb     r4, 5(r31)
/* 0AAA80 800B0020 889F0008 */  lbz     r4, 8(r31)
/* 0AAA84 800B0024 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAA88 800B0028 989F0008 */  stb     r4, 8(r31)
/* 0AAA8C 800B002C 889F0009 */  lbz     r4, 9(r31)
/* 0AAA90 800B0030 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAA94 800B0034 989F0009 */  stb     r4, 9(r31)
/* 0AAA98 800B0038 48000034 */  b       lbl_800B006C
lbl_800B003C:
/* 0AAA9C 800B003C 889F0004 */  lbz     r4, 4(r31)
/* 0AAAA0 800B0040 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAAA4 800B0044 989F0004 */  stb     r4, 4(r31)
/* 0AAAA8 800B0048 889F0005 */  lbz     r4, 5(r31)
/* 0AAAAC 800B004C 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAAB0 800B0050 989F0005 */  stb     r4, 5(r31)
/* 0AAAB4 800B0054 889F0006 */  lbz     r4, 6(r31)
/* 0AAAB8 800B0058 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAABC 800B005C 989F0006 */  stb     r4, 6(r31)
/* 0AAAC0 800B0060 889F0007 */  lbz     r4, 7(r31)
/* 0AAAC4 800B0064 54840036 */  rlwinm  r4, r4, 0, 0, 0x1b
/* 0AAAC8 800B0068 989F0007 */  stb     r4, 7(r31)
lbl_800B006C:
/* 0AAACC 800B006C 889F0002 */  lbz     r4, 2(r31)
/* 0AAAD0 800B0070 3884FF80 */  addi    r4, r4, -128
/* 0AAAD4 800B0074 989F0002 */  stb     r4, 2(r31)
/* 0AAAD8 800B0078 889F0003 */  lbz     r4, 3(r31)
/* 0AAADC 800B007C 3884FF80 */  addi    r4, r4, -128
/* 0AAAE0 800B0080 989F0003 */  stb     r4, 3(r31)
/* 0AAAE4 800B0084 889F0004 */  lbz     r4, 4(r31)
/* 0AAAE8 800B0088 3884FF80 */  addi    r4, r4, -128
/* 0AAAEC 800B008C 989F0004 */  stb     r4, 4(r31)
/* 0AAAF0 800B0090 889F0005 */  lbz     r4, 5(r31)
/* 0AAAF4 800B0094 3884FF80 */  addi    r4, r4, -128
/* 0AAAF8 800B0098 989F0005 */  stb     r4, 5(r31)
/* 0AAAFC 800B009C 808D87F0 */  lwz     r4, XPatchBits@sda21(r13)
/* 0AAB00 800B00A0 7C800039 */  and.    r0, r4, r0
/* 0AAB04 800B00A4 41820030 */  beq     lbl_800B00D4
/* 0AAB08 800B00A8 881F0002 */  lbz     r0, 2(r31)
/* 0AAB0C 800B00AC 7C000774 */  extsb   r0, r0
/* 0AAB10 800B00B0 2C000040 */  cmpwi   r0, 0x40
/* 0AAB14 800B00B4 40810020 */  ble     lbl_800B00D4
/* 0AAB18 800B00B8 4BFF5A55 */  bl      SIGetType
/* 0AAB1C 800B00BC 5463001E */  rlwinm  r3, r3, 0, 0, 0xf
/* 0AAB20 800B00C0 3C03F700 */  addis   r0, r3, 0xf700
/* 0AAB24 800B00C4 28000000 */  cmplwi  r0, 0
/* 0AAB28 800B00C8 4082000C */  bne     lbl_800B00D4
/* 0AAB2C 800B00CC 38000000 */  li      r0, 0
/* 0AAB30 800B00D0 981F0002 */  stb     r0, 2(r31)
lbl_800B00D4:
/* 0AAB34 800B00D4 8001001C */  lwz     r0, 0x1c(r1)
/* 0AAB38 800B00D8 83E10014 */  lwz     r31, 0x14(r1)
/* 0AAB3C 800B00DC 38210018 */  addi    r1, r1, 0x18
/* 0AAB40 800B00E0 7C0803A6 */  mtlr    r0
/* 0AAB44 800B00E4 4E800020 */  blr     

PADOriginCallback:
/* 0AAB48 800B00E8 7C0802A6 */  mflr    r0
/* 0AAB4C 800B00EC 90010004 */  stw     r0, 4(r1)
/* 0AAB50 800B00F0 5480073F */  clrlwi. r0, r4, 0x1c
/* 0AAB54 800B00F4 9421FFD0 */  stwu    r1, -0x30(r1)
/* 0AAB58 800B00F8 93E1002C */  stw     r31, 0x2c(r1)
/* 0AAB5C 800B00FC 40820048 */  bne     lbl_800B0144
/* 0AAB60 800B0100 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AAB64 800B0104 4BFFFE41 */  bl      UpdateOrigin
/* 0AAB68 800B0108 83ED87EC */  lwz     r31, ResettingChan@sda21(r13)
/* 0AAB6C 800B010C 3C008000 */  lis     r0, 0x8000
/* 0AAB70 800B0110 806D8C9C */  lwz     r3, EnabledBits@sda21(r13)
/* 0AAB74 800B0114 3881001C */  addi    r4, r1, 0x1c
/* 0AAB78 800B0118 7C00FC30 */  srw     r0, r0, r31
/* 0AAB7C 800B011C 7C600378 */  or      r0, r3, r0
/* 0AAB80 800B0120 900D8C9C */  stw     r0, EnabledBits@sda21(r13)
/* 0AAB84 800B0124 7FE3FB78 */  mr      r3, r31
/* 0AAB88 800B0128 4BFF5491 */  bl      SIGetResponse
/* 0AAB8C 800B012C 800D87F4 */  lwz     r0, AnalogMode@sda21(r13)
/* 0AAB90 800B0130 387F0000 */  addi    r3, r31, 0
/* 0AAB94 800B0134 64040040 */  oris    r4, r0, 0x40
/* 0AAB98 800B0138 4BFF5215 */  bl      SISetCommand
/* 0AAB9C 800B013C 806D8C9C */  lwz     r3, EnabledBits@sda21(r13)
/* 0AABA0 800B0140 4BFF529D */  bl      SIEnablePolling
lbl_800B0144:
/* 0AABA4 800B0144 80AD8CA0 */  lwz     r5, ResettingBits@sda21(r13)
/* 0AABA8 800B0148 7CA00034 */  cntlzw  r0, r5
/* 0AABAC 800B014C 900D87EC */  stw     r0, ResettingChan@sda21(r13)
/* 0AABB0 800B0150 808D87EC */  lwz     r4, ResettingChan@sda21(r13)
/* 0AABB4 800B0154 2C040020 */  cmpwi   r4, 0x20
/* 0AABB8 800B0158 41820040 */  beq     lbl_800B0198
/* 0AABBC 800B015C 3C008000 */  lis     r0, 0x8000
/* 0AABC0 800B0160 7C002430 */  srw     r0, r0, r4
/* 0AABC4 800B0164 7CA00078 */  andc    r0, r5, r0
/* 0AABC8 800B0168 1C84000C */  mulli   r4, r4, 0xc
/* 0AABCC 800B016C 900D8CA0 */  stw     r0, ResettingBits@sda21(r13)
/* 0AABD0 800B0170 3C608013 */  lis     r3, Origin@ha
/* 0AABD4 800B0174 38032478 */  addi    r0, r3, Origin@l
/* 0AABD8 800B0178 7C602214 */  add     r3, r0, r4
/* 0AABDC 800B017C 38800000 */  li      r4, 0
/* 0AABE0 800B0180 38A0000C */  li      r5, 0xc
/* 0AABE4 800B0184 4BF5524D */  bl      memset
/* 0AABE8 800B0188 3C80800B */  lis     r4, PADTypeAndStatusCallback@ha
/* 0AABEC 800B018C 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AABF0 800B0190 38840350 */  addi    r4, r4, PADTypeAndStatusCallback@l
/* 0AABF4 800B0194 4BFF5B3D */  bl      SIGetTypeAsync
lbl_800B0198:
/* 0AABF8 800B0198 80010034 */  lwz     r0, 0x34(r1)
/* 0AABFC 800B019C 83E1002C */  lwz     r31, 0x2c(r1)
/* 0AAC00 800B01A0 38210030 */  addi    r1, r1, 0x30
/* 0AAC04 800B01A4 7C0803A6 */  mtlr    r0
/* 0AAC08 800B01A8 4E800020 */  blr     

PADOriginUpdateCallback:
/* 0AAC0C 800B01AC 7C0802A6 */  mflr    r0
/* 0AAC10 800B01B0 90010004 */  stw     r0, 4(r1)
/* 0AAC14 800B01B4 3C008000 */  lis     r0, 0x8000
/* 0AAC18 800B01B8 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0AAC1C 800B01BC 93E10024 */  stw     r31, 0x24(r1)
/* 0AAC20 800B01C0 3BE40000 */  addi    r31, r4, 0
/* 0AAC24 800B01C4 93C10020 */  stw     r30, 0x20(r1)
/* 0AAC28 800B01C8 93A1001C */  stw     r29, 0x1c(r1)
/* 0AAC2C 800B01CC 7C7D1B78 */  mr      r29, r3
/* 0AAC30 800B01D0 7C1EEC30 */  srw     r30, r0, r29
/* 0AAC34 800B01D4 806D8C9C */  lwz     r3, EnabledBits@sda21(r13)
/* 0AAC38 800B01D8 7C60F039 */  and.    r0, r3, r30
/* 0AAC3C 800B01DC 41820080 */  beq     lbl_800B025C
/* 0AAC40 800B01E0 57E0073F */  clrlwi. r0, r31, 0x1c
/* 0AAC44 800B01E4 4082000C */  bne     lbl_800B01F0
/* 0AAC48 800B01E8 7FA3EB78 */  mr      r3, r29
/* 0AAC4C 800B01EC 4BFFFD59 */  bl      UpdateOrigin
lbl_800B01F0:
/* 0AAC50 800B01F0 57E00739 */  rlwinm. r0, r31, 0, 0x1c, 0x1c
/* 0AAC54 800B01F4 41820068 */  beq     lbl_800B025C
/* 0AAC58 800B01F8 4BFEEB05 */  bl      OSDisableInterrupts
/* 0AAC5C 800B01FC 3BE30000 */  addi    r31, r3, 0
/* 0AAC60 800B0200 387E0000 */  addi    r3, r30, 0
/* 0AAC64 800B0204 4BFF5275 */  bl      SIDisablePolling
/* 0AAC68 800B0208 800D8C9C */  lwz     r0, EnabledBits@sda21(r13)
/* 0AAC6C 800B020C 7FC9F0F8 */  nor     r9, r30, r30
/* 0AAC70 800B0210 80CD8CA8 */  lwz     r6, WaitingBits@sda21(r13)
/* 0AAC74 800B0214 7FA3EB78 */  mr      r3, r29
/* 0AAC78 800B0218 80AD8CAC */  lwz     r5, CheckingBits@sda21(r13)
/* 0AAC7C 800B021C 808D8CB0 */  lwz     r4, PendingBits@sda21(r13)
/* 0AAC80 800B0220 7C084838 */  and     r8, r0, r9
/* 0AAC84 800B0224 800D8CB4 */  lwz     r0, BarrelBits@sda21(r13)
/* 0AAC88 800B0228 7CC74838 */  and     r7, r6, r9
/* 0AAC8C 800B022C 7CA64838 */  and     r6, r5, r9
/* 0AAC90 800B0230 7C854838 */  and     r5, r4, r9
/* 0AAC94 800B0234 910D8C9C */  stw     r8, EnabledBits@sda21(r13)
/* 0AAC98 800B0238 7C004838 */  and     r0, r0, r9
/* 0AAC9C 800B023C 90ED8CA8 */  stw     r7, WaitingBits@sda21(r13)
/* 0AACA0 800B0240 38800000 */  li      r4, 0
/* 0AACA4 800B0244 90CD8CAC */  stw     r6, CheckingBits@sda21(r13)
/* 0AACA8 800B0248 90AD8CB0 */  stw     r5, PendingBits@sda21(r13)
/* 0AACAC 800B024C 900D8CB4 */  stw     r0, BarrelBits@sda21(r13)
/* 0AACB0 800B0250 4BFF0C31 */  bl      OSSetWirelessID
/* 0AACB4 800B0254 7FE3FB78 */  mr      r3, r31
/* 0AACB8 800B0258 4BFEEACD */  bl      OSRestoreInterrupts
lbl_800B025C:
/* 0AACBC 800B025C 8001002C */  lwz     r0, 0x2c(r1)
/* 0AACC0 800B0260 83E10024 */  lwz     r31, 0x24(r1)
/* 0AACC4 800B0264 83C10020 */  lwz     r30, 0x20(r1)
/* 0AACC8 800B0268 83A1001C */  lwz     r29, 0x1c(r1)
/* 0AACCC 800B026C 38210028 */  addi    r1, r1, 0x28
/* 0AACD0 800B0270 7C0803A6 */  mtlr    r0
/* 0AACD4 800B0274 4E800020 */  blr     

PADProbeCallback:
/* 0AACD8 800B0278 7C0802A6 */  mflr    r0
/* 0AACDC 800B027C 90010004 */  stw     r0, 4(r1)
/* 0AACE0 800B0280 5480073F */  clrlwi. r0, r4, 0x1c
/* 0AACE4 800B0284 9421FFD0 */  stwu    r1, -0x30(r1)
/* 0AACE8 800B0288 93E1002C */  stw     r31, 0x2c(r1)
/* 0AACEC 800B028C 93C10028 */  stw     r30, 0x28(r1)
/* 0AACF0 800B0290 40820054 */  bne     lbl_800B02E4
/* 0AACF4 800B0294 83CD87EC */  lwz     r30, ResettingChan@sda21(r13)
/* 0AACF8 800B0298 3FE08000 */  lis     r31, 0x8000
/* 0AACFC 800B029C 806D8C9C */  lwz     r3, EnabledBits@sda21(r13)
/* 0AAD00 800B02A0 3881001C */  addi    r4, r1, 0x1c
/* 0AAD04 800B02A4 7FE0F430 */  srw     r0, r31, r30
/* 0AAD08 800B02A8 7C600378 */  or      r0, r3, r0
/* 0AAD0C 800B02AC 900D8C9C */  stw     r0, EnabledBits@sda21(r13)
/* 0AAD10 800B02B0 7FC3F378 */  mr      r3, r30
/* 0AAD14 800B02B4 4BFF5305 */  bl      SIGetResponse
/* 0AAD18 800B02B8 800D87F4 */  lwz     r0, AnalogMode@sda21(r13)
/* 0AAD1C 800B02BC 387E0000 */  addi    r3, r30, 0
/* 0AAD20 800B02C0 64040040 */  oris    r4, r0, 0x40
/* 0AAD24 800B02C4 4BFF5089 */  bl      SISetCommand
/* 0AAD28 800B02C8 806D8C9C */  lwz     r3, EnabledBits@sda21(r13)
/* 0AAD2C 800B02CC 4BFF5111 */  bl      SIEnablePolling
/* 0AAD30 800B02D0 800D87EC */  lwz     r0, ResettingChan@sda21(r13)
/* 0AAD34 800B02D4 806D8CA8 */  lwz     r3, WaitingBits@sda21(r13)
/* 0AAD38 800B02D8 7FE00430 */  srw     r0, r31, r0
/* 0AAD3C 800B02DC 7C600378 */  or      r0, r3, r0
/* 0AAD40 800B02E0 900D8CA8 */  stw     r0, WaitingBits@sda21(r13)
lbl_800B02E4:
/* 0AAD44 800B02E4 80AD8CA0 */  lwz     r5, ResettingBits@sda21(r13)
/* 0AAD48 800B02E8 7CA00034 */  cntlzw  r0, r5
/* 0AAD4C 800B02EC 900D87EC */  stw     r0, ResettingChan@sda21(r13)
/* 0AAD50 800B02F0 808D87EC */  lwz     r4, ResettingChan@sda21(r13)
/* 0AAD54 800B02F4 2C040020 */  cmpwi   r4, 0x20
/* 0AAD58 800B02F8 41820040 */  beq     lbl_800B0338
/* 0AAD5C 800B02FC 3C008000 */  lis     r0, 0x8000
/* 0AAD60 800B0300 7C002430 */  srw     r0, r0, r4
/* 0AAD64 800B0304 7CA00078 */  andc    r0, r5, r0
/* 0AAD68 800B0308 1C84000C */  mulli   r4, r4, 0xc
/* 0AAD6C 800B030C 900D8CA0 */  stw     r0, ResettingBits@sda21(r13)
/* 0AAD70 800B0310 3C608013 */  lis     r3, Origin@ha
/* 0AAD74 800B0314 38032478 */  addi    r0, r3, Origin@l
/* 0AAD78 800B0318 7C602214 */  add     r3, r0, r4
/* 0AAD7C 800B031C 38800000 */  li      r4, 0
/* 0AAD80 800B0320 38A0000C */  li      r5, 0xc
/* 0AAD84 800B0324 4BF550AD */  bl      memset
/* 0AAD88 800B0328 3C80800B */  lis     r4, PADTypeAndStatusCallback@ha
/* 0AAD8C 800B032C 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AAD90 800B0330 38840350 */  addi    r4, r4, PADTypeAndStatusCallback@l
/* 0AAD94 800B0334 4BFF599D */  bl      SIGetTypeAsync
lbl_800B0338:
/* 0AAD98 800B0338 80010034 */  lwz     r0, 0x34(r1)
/* 0AAD9C 800B033C 83E1002C */  lwz     r31, 0x2c(r1)
/* 0AADA0 800B0340 83C10028 */  lwz     r30, 0x28(r1)
/* 0AADA4 800B0344 38210030 */  addi    r1, r1, 0x30
/* 0AADA8 800B0348 7C0803A6 */  mtlr    r0
/* 0AADAC 800B034C 4E800020 */  blr     

PADTypeAndStatusCallback:
/* 0AADB0 800B0350 7C0802A6 */  mflr    r0
/* 0AADB4 800B0354 3CC08013 */  lis     r6, Type@ha
/* 0AADB8 800B0358 90010004 */  stw     r0, 4(r1)
/* 0AADBC 800B035C 5480073F */  clrlwi. r0, r4, 0x1c
/* 0AADC0 800B0360 9421FFC0 */  stwu    r1, -0x40(r1)
/* 0AADC4 800B0364 93E1003C */  stw     r31, 0x3c(r1)
/* 0AADC8 800B0368 3FE08000 */  lis     r31, 0x8000
/* 0AADCC 800B036C 93C10038 */  stw     r30, 0x38(r1)
/* 0AADD0 800B0370 3BC62468 */  addi    r30, r6, Type@l
/* 0AADD4 800B0374 93A10034 */  stw     r29, 0x34(r1)
/* 0AADD8 800B0378 93810030 */  stw     r28, 0x30(r1)
/* 0AADDC 800B037C 83AD87EC */  lwz     r29, ResettingChan@sda21(r13)
/* 0AADE0 800B0380 80AD8CA4 */  lwz     r5, RecalibrateBits@sda21(r13)
/* 0AADE4 800B0384 7FFCEC30 */  srw     r28, r31, r29
/* 0AADE8 800B0388 7CA3E078 */  andc    r3, r5, r28
/* 0AADEC 800B038C 906D8CA4 */  stw     r3, RecalibrateBits@sda21(r13)
/* 0AADF0 800B0390 7CA5E038 */  and     r5, r5, r28
/* 0AADF4 800B0394 38600001 */  li      r3, 1
/* 0AADF8 800B0398 41820054 */  beq     lbl_800B03EC
/* 0AADFC 800B039C 808D8CA0 */  lwz     r4, ResettingBits@sda21(r13)
/* 0AAE00 800B03A0 7C800034 */  cntlzw  r0, r4
/* 0AAE04 800B03A4 900D87EC */  stw     r0, ResettingChan@sda21(r13)
/* 0AAE08 800B03A8 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AAE0C 800B03AC 2C030020 */  cmpwi   r3, 0x20
/* 0AAE10 800B03B0 418202AC */  beq     lbl_800B065C
/* 0AAE14 800B03B4 1C03000C */  mulli   r0, r3, 0xc
/* 0AAE18 800B03B8 7FE31C30 */  srw     r3, r31, r3
/* 0AAE1C 800B03BC 7C841878 */  andc    r4, r4, r3
/* 0AAE20 800B03C0 7C7E0214 */  add     r3, r30, r0
/* 0AAE24 800B03C4 908D8CA0 */  stw     r4, ResettingBits@sda21(r13)
/* 0AAE28 800B03C8 38800000 */  li      r4, 0
/* 0AAE2C 800B03CC 38A0000C */  li      r5, 0xc
/* 0AAE30 800B03D0 38630010 */  addi    r3, r3, 0x10
/* 0AAE34 800B03D4 4BF54FFD */  bl      memset
/* 0AAE38 800B03D8 3C80800B */  lis     r4, PADTypeAndStatusCallback@ha
/* 0AAE3C 800B03DC 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AAE40 800B03E0 38840350 */  addi    r4, r4, PADTypeAndStatusCallback@l
/* 0AAE44 800B03E4 4BFF58ED */  bl      SIGetTypeAsync
/* 0AAE48 800B03E8 48000274 */  b       lbl_800B065C
lbl_800B03EC:
/* 0AAE4C 800B03EC 5486002E */  rlwinm  r6, r4, 0, 0, 0x17
/* 0AAE50 800B03F0 548400C8 */  rlwinm  r4, r4, 0, 3, 4
/* 0AAE54 800B03F4 3C04F800 */  addis   r0, r4, 0xf800
/* 0AAE58 800B03F8 57A4103A */  slwi    r4, r29, 2
/* 0AAE5C 800B03FC 28000000 */  cmplwi  r0, 0
/* 0AAE60 800B0400 7CDE212E */  stwx    r6, r30, r4
/* 0AAE64 800B0404 4082000C */  bne     lbl_800B0410
/* 0AAE68 800B0408 54C001CF */  rlwinm. r0, r6, 0, 7, 7
/* 0AAE6C 800B040C 40820058 */  bne     lbl_800B0464
lbl_800B0410:
/* 0AAE70 800B0410 80AD8CA0 */  lwz     r5, ResettingBits@sda21(r13)
/* 0AAE74 800B0414 7CA00034 */  cntlzw  r0, r5
/* 0AAE78 800B0418 900D87EC */  stw     r0, ResettingChan@sda21(r13)
/* 0AAE7C 800B041C 808D87EC */  lwz     r4, ResettingChan@sda21(r13)
/* 0AAE80 800B0420 2C040020 */  cmpwi   r4, 0x20
/* 0AAE84 800B0424 41820238 */  beq     lbl_800B065C
/* 0AAE88 800B0428 3C608000 */  lis     r3, 0x8000
/* 0AAE8C 800B042C 1C04000C */  mulli   r0, r4, 0xc
/* 0AAE90 800B0430 7C632430 */  srw     r3, r3, r4
/* 0AAE94 800B0434 7CA41878 */  andc    r4, r5, r3
/* 0AAE98 800B0438 7C7E0214 */  add     r3, r30, r0
/* 0AAE9C 800B043C 908D8CA0 */  stw     r4, ResettingBits@sda21(r13)
/* 0AAEA0 800B0440 38800000 */  li      r4, 0
/* 0AAEA4 800B0444 38A0000C */  li      r5, 0xc
/* 0AAEA8 800B0448 38630010 */  addi    r3, r3, 0x10
/* 0AAEAC 800B044C 4BF54F85 */  bl      memset
/* 0AAEB0 800B0450 3C80800B */  lis     r4, PADTypeAndStatusCallback@ha
/* 0AAEB4 800B0454 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AAEB8 800B0458 38840350 */  addi    r4, r4, PADTypeAndStatusCallback@l
/* 0AAEBC 800B045C 4BFF5875 */  bl      SIGetTypeAsync
/* 0AAEC0 800B0460 480001FC */  b       lbl_800B065C
lbl_800B0464:
/* 0AAEC4 800B0464 800D87F8 */  lwz     r0, Spec@sda21(r13)
/* 0AAEC8 800B0468 28000002 */  cmplwi  r0, 2
/* 0AAECC 800B046C 40800084 */  bge     lbl_800B04F0
/* 0AAED0 800B0470 800D8C9C */  lwz     r0, EnabledBits@sda21(r13)
/* 0AAED4 800B0474 387D0000 */  addi    r3, r29, 0
/* 0AAED8 800B0478 3881001C */  addi    r4, r1, 0x1c
/* 0AAEDC 800B047C 7C00E378 */  or      r0, r0, r28
/* 0AAEE0 800B0480 900D8C9C */  stw     r0, EnabledBits@sda21(r13)
/* 0AAEE4 800B0484 4BFF5135 */  bl      SIGetResponse
/* 0AAEE8 800B0488 800D87F4 */  lwz     r0, AnalogMode@sda21(r13)
/* 0AAEEC 800B048C 387D0000 */  addi    r3, r29, 0
/* 0AAEF0 800B0490 64040040 */  oris    r4, r0, 0x40
/* 0AAEF4 800B0494 4BFF4EB9 */  bl      SISetCommand
/* 0AAEF8 800B0498 806D8C9C */  lwz     r3, EnabledBits@sda21(r13)
/* 0AAEFC 800B049C 4BFF4F41 */  bl      SIEnablePolling
/* 0AAF00 800B04A0 808D8CA0 */  lwz     r4, ResettingBits@sda21(r13)
/* 0AAF04 800B04A4 7C800034 */  cntlzw  r0, r4
/* 0AAF08 800B04A8 900D87EC */  stw     r0, ResettingChan@sda21(r13)
/* 0AAF0C 800B04AC 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AAF10 800B04B0 2C030020 */  cmpwi   r3, 0x20
/* 0AAF14 800B04B4 418201A8 */  beq     lbl_800B065C
/* 0AAF18 800B04B8 1C03000C */  mulli   r0, r3, 0xc
/* 0AAF1C 800B04BC 7FE31C30 */  srw     r3, r31, r3
/* 0AAF20 800B04C0 7C841878 */  andc    r4, r4, r3
/* 0AAF24 800B04C4 7C7E0214 */  add     r3, r30, r0
/* 0AAF28 800B04C8 908D8CA0 */  stw     r4, ResettingBits@sda21(r13)
/* 0AAF2C 800B04CC 38800000 */  li      r4, 0
/* 0AAF30 800B04D0 38A0000C */  li      r5, 0xc
/* 0AAF34 800B04D4 38630010 */  addi    r3, r3, 0x10
/* 0AAF38 800B04D8 4BF54EF9 */  bl      memset
/* 0AAF3C 800B04DC 3C80800B */  lis     r4, PADTypeAndStatusCallback@ha
/* 0AAF40 800B04E0 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AAF44 800B04E4 38840350 */  addi    r4, r4, PADTypeAndStatusCallback@l
/* 0AAF48 800B04E8 4BFF57E9 */  bl      SIGetTypeAsync
/* 0AAF4C 800B04EC 48000170 */  b       lbl_800B065C
lbl_800B04F0:
/* 0AAF50 800B04F0 54C00001 */  rlwinm. r0, r6, 0, 0, 0
/* 0AAF54 800B04F4 4182000C */  beq     lbl_800B0500
/* 0AAF58 800B04F8 54C0014B */  rlwinm. r0, r6, 0, 5, 5
/* 0AAF5C 800B04FC 41820074 */  beq     lbl_800B0570
lbl_800B0500:
/* 0AAF60 800B0500 28050000 */  cmplwi  r5, 0
/* 0AAF64 800B0504 41820038 */  beq     lbl_800B053C
/* 0AAF68 800B0508 1C1D000C */  mulli   r0, r29, 0xc
/* 0AAF6C 800B050C 3C60800B */  lis     r3, PADOriginCallback@ha
/* 0AAF70 800B0510 7CDE0214 */  add     r6, r30, r0
/* 0AAF74 800B0514 390300E8 */  addi    r8, r3, PADOriginCallback@l
/* 0AAF78 800B0518 387D0000 */  addi    r3, r29, 0
/* 0AAF7C 800B051C 388D8804 */  addi    r4, r13, CmdCalibrate@sda21
/* 0AAF80 800B0520 38A00003 */  li      r5, 3
/* 0AAF84 800B0524 38E0000A */  li      r7, 0xa
/* 0AAF88 800B0528 39400000 */  li      r10, 0
/* 0AAF8C 800B052C 39200000 */  li      r9, 0
/* 0AAF90 800B0530 38C60010 */  addi    r6, r6, 0x10
/* 0AAF94 800B0534 4BFF51D5 */  bl      SITransfer
/* 0AAF98 800B0538 480000C0 */  b       lbl_800B05F8
lbl_800B053C:
/* 0AAF9C 800B053C 1C1D000C */  mulli   r0, r29, 0xc
/* 0AAFA0 800B0540 3C60800B */  lis     r3, PADOriginCallback@ha
/* 0AAFA4 800B0544 7CDE0214 */  add     r6, r30, r0
/* 0AAFA8 800B0548 390300E8 */  addi    r8, r3, PADOriginCallback@l
/* 0AAFAC 800B054C 387D0000 */  addi    r3, r29, 0
/* 0AAFB0 800B0550 388D8800 */  addi    r4, r13, CmdReadOrigin@sda21
/* 0AAFB4 800B0554 38A00001 */  li      r5, 1
/* 0AAFB8 800B0558 38E0000A */  li      r7, 0xa
/* 0AAFBC 800B055C 39400000 */  li      r10, 0
/* 0AAFC0 800B0560 39200000 */  li      r9, 0
/* 0AAFC4 800B0564 38C60010 */  addi    r6, r6, 0x10
/* 0AAFC8 800B0568 4BFF51A1 */  bl      SITransfer
/* 0AAFCC 800B056C 4800008C */  b       lbl_800B05F8
lbl_800B0570:
/* 0AAFD0 800B0570 54C002D7 */  rlwinm. r0, r6, 0, 0xb, 0xb
/* 0AAFD4 800B0574 41820084 */  beq     lbl_800B05F8
/* 0AAFD8 800B0578 54C00319 */  rlwinm. r0, r6, 0, 0xc, 0xc
/* 0AAFDC 800B057C 4082007C */  bne     lbl_800B05F8
/* 0AAFE0 800B0580 54C0035B */  rlwinm. r0, r6, 0, 0xd, 0xd
/* 0AAFE4 800B0584 40820074 */  bne     lbl_800B05F8
/* 0AAFE8 800B0588 54C00043 */  rlwinm. r0, r6, 0, 1, 1
/* 0AAFEC 800B058C 41820038 */  beq     lbl_800B05C4
/* 0AAFF0 800B0590 1C1D000C */  mulli   r0, r29, 0xc
/* 0AAFF4 800B0594 3C60800B */  lis     r3, PADOriginCallback@ha
/* 0AAFF8 800B0598 7CDE0214 */  add     r6, r30, r0
/* 0AAFFC 800B059C 390300E8 */  addi    r8, r3, PADOriginCallback@l
/* 0AB000 800B05A0 387D0000 */  addi    r3, r29, 0
/* 0AB004 800B05A4 388D8800 */  addi    r4, r13, CmdReadOrigin@sda21
/* 0AB008 800B05A8 38A00001 */  li      r5, 1
/* 0AB00C 800B05AC 38E0000A */  li      r7, 0xa
/* 0AB010 800B05B0 39400000 */  li      r10, 0
/* 0AB014 800B05B4 39200000 */  li      r9, 0
/* 0AB018 800B05B8 38C60010 */  addi    r6, r6, 0x10
/* 0AB01C 800B05BC 4BFF514D */  bl      SITransfer
/* 0AB020 800B05C0 48000038 */  b       lbl_800B05F8
lbl_800B05C4:
/* 0AB024 800B05C4 1C1D000C */  mulli   r0, r29, 0xc
/* 0AB028 800B05C8 3C60800B */  lis     r3, PADProbeCallback@ha
/* 0AB02C 800B05CC 7C9E2214 */  add     r4, r30, r4
/* 0AB030 800B05D0 7CDE0214 */  add     r6, r30, r0
/* 0AB034 800B05D4 39030278 */  addi    r8, r3, PADProbeCallback@l
/* 0AB038 800B05D8 387D0000 */  addi    r3, r29, 0
/* 0AB03C 800B05DC 38A00003 */  li      r5, 3
/* 0AB040 800B05E0 38E00008 */  li      r7, 8
/* 0AB044 800B05E4 39400000 */  li      r10, 0
/* 0AB048 800B05E8 39200000 */  li      r9, 0
/* 0AB04C 800B05EC 38840040 */  addi    r4, r4, 0x40
/* 0AB050 800B05F0 38C60010 */  addi    r6, r6, 0x10
/* 0AB054 800B05F4 4BFF5115 */  bl      SITransfer
lbl_800B05F8:
/* 0AB058 800B05F8 2C030000 */  cmpwi   r3, 0
/* 0AB05C 800B05FC 40820060 */  bne     lbl_800B065C
/* 0AB060 800B0600 80AD8CA0 */  lwz     r5, ResettingBits@sda21(r13)
/* 0AB064 800B0604 806D8CB0 */  lwz     r3, PendingBits@sda21(r13)
/* 0AB068 800B0608 7CA00034 */  cntlzw  r0, r5
/* 0AB06C 800B060C 900D87EC */  stw     r0, ResettingChan@sda21(r13)
/* 0AB070 800B0610 7C60E378 */  or      r0, r3, r28
/* 0AB074 800B0614 808D87EC */  lwz     r4, ResettingChan@sda21(r13)
/* 0AB078 800B0618 900D8CB0 */  stw     r0, PendingBits@sda21(r13)
/* 0AB07C 800B061C 2C040020 */  cmpwi   r4, 0x20
/* 0AB080 800B0620 4182003C */  beq     lbl_800B065C
/* 0AB084 800B0624 3C608000 */  lis     r3, 0x8000
/* 0AB088 800B0628 1C04000C */  mulli   r0, r4, 0xc
/* 0AB08C 800B062C 7C632430 */  srw     r3, r3, r4
/* 0AB090 800B0630 7CA41878 */  andc    r4, r5, r3
/* 0AB094 800B0634 7C7E0214 */  add     r3, r30, r0
/* 0AB098 800B0638 908D8CA0 */  stw     r4, ResettingBits@sda21(r13)
/* 0AB09C 800B063C 38800000 */  li      r4, 0
/* 0AB0A0 800B0640 38A0000C */  li      r5, 0xc
/* 0AB0A4 800B0644 38630010 */  addi    r3, r3, 0x10
/* 0AB0A8 800B0648 4BF54D89 */  bl      memset
/* 0AB0AC 800B064C 3C80800B */  lis     r4, PADTypeAndStatusCallback@ha
/* 0AB0B0 800B0650 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AB0B4 800B0654 38840350 */  addi    r4, r4, PADTypeAndStatusCallback@l
/* 0AB0B8 800B0658 4BFF5679 */  bl      SIGetTypeAsync
lbl_800B065C:
/* 0AB0BC 800B065C 80010044 */  lwz     r0, 0x44(r1)
/* 0AB0C0 800B0660 83E1003C */  lwz     r31, 0x3c(r1)
/* 0AB0C4 800B0664 83C10038 */  lwz     r30, 0x38(r1)
/* 0AB0C8 800B0668 83A10034 */  lwz     r29, 0x34(r1)
/* 0AB0CC 800B066C 83810030 */  lwz     r28, 0x30(r1)
/* 0AB0D0 800B0670 38210040 */  addi    r1, r1, 0x40
/* 0AB0D4 800B0674 7C0803A6 */  mtlr    r0
/* 0AB0D8 800B0678 4E800020 */  blr     

PADReceiveCheckCallback:
/* 0AB0DC 800B067C 7C0802A6 */  mflr    r0
/* 0AB0E0 800B0680 90010004 */  stw     r0, 4(r1)
/* 0AB0E4 800B0684 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0AB0E8 800B0688 93E1001C */  stw     r31, 0x1c(r1)
/* 0AB0EC 800B068C 7C7F1B78 */  mr      r31, r3
/* 0AB0F0 800B0690 3C608000 */  lis     r3, 0x8000
/* 0AB0F4 800B0694 93C10018 */  stw     r30, 0x18(r1)
/* 0AB0F8 800B0698 93A10014 */  stw     r29, 0x14(r1)
/* 0AB0FC 800B069C 7C7DFC30 */  srw     r29, r3, r31
/* 0AB100 800B06A0 800D8C9C */  lwz     r0, EnabledBits@sda21(r13)
/* 0AB104 800B06A4 7C00E839 */  and.    r0, r0, r29
/* 0AB108 800B06A8 418200F8 */  beq     lbl_800B07A0
/* 0AB10C 800B06AC 80AD8CA8 */  lwz     r5, WaitingBits@sda21(r13)
/* 0AB110 800B06B0 7FA6E8F8 */  nor     r6, r29, r29
/* 0AB114 800B06B4 806D8CAC */  lwz     r3, CheckingBits@sda21(r13)
/* 0AB118 800B06B8 5480073F */  clrlwi. r0, r4, 0x1c
/* 0AB11C 800B06BC 7CA53038 */  and     r5, r5, r6
/* 0AB120 800B06C0 7C633038 */  and     r3, r3, r6
/* 0AB124 800B06C4 90AD8CA8 */  stw     r5, WaitingBits@sda21(r13)
/* 0AB128 800B06C8 906D8CAC */  stw     r3, CheckingBits@sda21(r13)
/* 0AB12C 800B06CC 5483002E */  rlwinm  r3, r4, 0, 0, 0x17
/* 0AB130 800B06D0 4082006C */  bne     lbl_800B073C
/* 0AB134 800B06D4 54600001 */  rlwinm. r0, r3, 0, 0, 0
/* 0AB138 800B06D8 41820064 */  beq     lbl_800B073C
/* 0AB13C 800B06DC 546002D7 */  rlwinm. r0, r3, 0, 0xb, 0xb
/* 0AB140 800B06E0 4182005C */  beq     lbl_800B073C
/* 0AB144 800B06E4 54600043 */  rlwinm. r0, r3, 0, 1, 1
/* 0AB148 800B06E8 41820054 */  beq     lbl_800B073C
/* 0AB14C 800B06EC 5460014B */  rlwinm. r0, r3, 0, 5, 5
/* 0AB150 800B06F0 4082004C */  bne     lbl_800B073C
/* 0AB154 800B06F4 54600319 */  rlwinm. r0, r3, 0, 0xc, 0xc
/* 0AB158 800B06F8 40820044 */  bne     lbl_800B073C
/* 0AB15C 800B06FC 5460035B */  rlwinm. r0, r3, 0, 0xd, 0xd
/* 0AB160 800B0700 4082003C */  bne     lbl_800B073C
/* 0AB164 800B0704 1C9F000C */  mulli   r4, r31, 0xc
/* 0AB168 800B0708 3C608013 */  lis     r3, Origin@ha
/* 0AB16C 800B070C 38032478 */  addi    r0, r3, Origin@l
/* 0AB170 800B0710 3C60800B */  lis     r3, PADOriginUpdateCallback@ha
/* 0AB174 800B0714 7CC02214 */  add     r6, r0, r4
/* 0AB178 800B0718 390301AC */  addi    r8, r3, PADOriginUpdateCallback@l
/* 0AB17C 800B071C 387F0000 */  addi    r3, r31, 0
/* 0AB180 800B0720 388D8800 */  addi    r4, r13, CmdReadOrigin@sda21
/* 0AB184 800B0724 38A00001 */  li      r5, 1
/* 0AB188 800B0728 38E0000A */  li      r7, 0xa
/* 0AB18C 800B072C 39400000 */  li      r10, 0
/* 0AB190 800B0730 39200000 */  li      r9, 0
/* 0AB194 800B0734 4BFF4FD5 */  bl      SITransfer
/* 0AB198 800B0738 48000068 */  b       lbl_800B07A0
lbl_800B073C:
/* 0AB19C 800B073C 4BFEE5C1 */  bl      OSDisableInterrupts
/* 0AB1A0 800B0740 3BC30000 */  addi    r30, r3, 0
/* 0AB1A4 800B0744 387D0000 */  addi    r3, r29, 0
/* 0AB1A8 800B0748 4BFF4D31 */  bl      SIDisablePolling
/* 0AB1AC 800B074C 800D8C9C */  lwz     r0, EnabledBits@sda21(r13)
/* 0AB1B0 800B0750 7FA9E8F8 */  nor     r9, r29, r29
/* 0AB1B4 800B0754 80CD8CA8 */  lwz     r6, WaitingBits@sda21(r13)
/* 0AB1B8 800B0758 7FE3FB78 */  mr      r3, r31
/* 0AB1BC 800B075C 80AD8CAC */  lwz     r5, CheckingBits@sda21(r13)
/* 0AB1C0 800B0760 808D8CB0 */  lwz     r4, PendingBits@sda21(r13)
/* 0AB1C4 800B0764 7C084838 */  and     r8, r0, r9
/* 0AB1C8 800B0768 800D8CB4 */  lwz     r0, BarrelBits@sda21(r13)
/* 0AB1CC 800B076C 7CC74838 */  and     r7, r6, r9
/* 0AB1D0 800B0770 7CA64838 */  and     r6, r5, r9
/* 0AB1D4 800B0774 7C854838 */  and     r5, r4, r9
/* 0AB1D8 800B0778 910D8C9C */  stw     r8, EnabledBits@sda21(r13)
/* 0AB1DC 800B077C 7C004838 */  and     r0, r0, r9
/* 0AB1E0 800B0780 90ED8CA8 */  stw     r7, WaitingBits@sda21(r13)
/* 0AB1E4 800B0784 38800000 */  li      r4, 0
/* 0AB1E8 800B0788 90CD8CAC */  stw     r6, CheckingBits@sda21(r13)
/* 0AB1EC 800B078C 90AD8CB0 */  stw     r5, PendingBits@sda21(r13)
/* 0AB1F0 800B0790 900D8CB4 */  stw     r0, BarrelBits@sda21(r13)
/* 0AB1F4 800B0794 4BFF06ED */  bl      OSSetWirelessID
/* 0AB1F8 800B0798 7FC3F378 */  mr      r3, r30
/* 0AB1FC 800B079C 4BFEE589 */  bl      OSRestoreInterrupts
lbl_800B07A0:
/* 0AB200 800B07A0 80010024 */  lwz     r0, 0x24(r1)
/* 0AB204 800B07A4 83E1001C */  lwz     r31, 0x1c(r1)
/* 0AB208 800B07A8 83C10018 */  lwz     r30, 0x18(r1)
/* 0AB20C 800B07AC 83A10014 */  lwz     r29, 0x14(r1)
/* 0AB210 800B07B0 38210020 */  addi    r1, r1, 0x20
/* 0AB214 800B07B4 7C0803A6 */  mtlr    r0
/* 0AB218 800B07B8 4E800020 */  blr     

glabel PADReset
/* 0AB21C 800B07BC 7C0802A6 */  mflr    r0
/* 0AB220 800B07C0 90010004 */  stw     r0, 4(r1)
/* 0AB224 800B07C4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AB228 800B07C8 93E10014 */  stw     r31, 0x14(r1)
/* 0AB22C 800B07CC 93C10010 */  stw     r30, 0x10(r1)
/* 0AB230 800B07D0 7C7E1B78 */  mr      r30, r3
/* 0AB234 800B07D4 4BFEE529 */  bl      OSDisableInterrupts
/* 0AB238 800B07D8 808D8CB0 */  lwz     r4, PendingBits@sda21(r13)
/* 0AB23C 800B07DC 39000000 */  li      r8, 0
/* 0AB240 800B07E0 80AD8CA8 */  lwz     r5, WaitingBits@sda21(r13)
/* 0AB244 800B07E4 7C7F1B78 */  mr      r31, r3
/* 0AB248 800B07E8 800D8CAC */  lwz     r0, CheckingBits@sda21(r13)
/* 0AB24C 800B07EC 7FDE2378 */  or      r30, r30, r4
/* 0AB250 800B07F0 808D8CA0 */  lwz     r4, ResettingBits@sda21(r13)
/* 0AB254 800B07F4 7CA50378 */  or      r5, r5, r0
/* 0AB258 800B07F8 800D87F8 */  lwz     r0, Spec@sda21(r13)
/* 0AB25C 800B07FC 7FDE2878 */  andc    r30, r30, r5
/* 0AB260 800B0800 80CD8C9C */  lwz     r6, EnabledBits@sda21(r13)
/* 0AB264 800B0804 7C85F378 */  or      r5, r4, r30
/* 0AB268 800B0808 808D8CB4 */  lwz     r4, BarrelBits@sda21(r13)
/* 0AB26C 800B080C 7FC7F0F8 */  nor     r7, r30, r30
/* 0AB270 800B0810 90AD8CA0 */  stw     r5, ResettingBits@sda21(r13)
/* 0AB274 800B0814 7CC53838 */  and     r5, r6, r7
/* 0AB278 800B0818 7C843838 */  and     r4, r4, r7
/* 0AB27C 800B081C 80ED8CA0 */  lwz     r7, ResettingBits@sda21(r13)
/* 0AB280 800B0820 28000004 */  cmplwi  r0, 4
/* 0AB284 800B0824 910D8CB0 */  stw     r8, PendingBits@sda21(r13)
/* 0AB288 800B0828 7CE33038 */  and     r3, r7, r6
/* 0AB28C 800B082C 90AD8C9C */  stw     r5, EnabledBits@sda21(r13)
/* 0AB290 800B0830 908D8CB4 */  stw     r4, BarrelBits@sda21(r13)
/* 0AB294 800B0834 40820010 */  bne     lbl_800B0844
/* 0AB298 800B0838 800D8CA4 */  lwz     r0, RecalibrateBits@sda21(r13)
/* 0AB29C 800B083C 7C00F378 */  or      r0, r0, r30
/* 0AB2A0 800B0840 900D8CA4 */  stw     r0, RecalibrateBits@sda21(r13)
lbl_800B0844:
/* 0AB2A4 800B0844 4BFF4C35 */  bl      SIDisablePolling
/* 0AB2A8 800B0848 800D87EC */  lwz     r0, ResettingChan@sda21(r13)
/* 0AB2AC 800B084C 2C000020 */  cmpwi   r0, 0x20
/* 0AB2B0 800B0850 40820058 */  bne     lbl_800B08A8
/* 0AB2B4 800B0854 80AD8CA0 */  lwz     r5, ResettingBits@sda21(r13)
/* 0AB2B8 800B0858 7CA00034 */  cntlzw  r0, r5
/* 0AB2BC 800B085C 900D87EC */  stw     r0, ResettingChan@sda21(r13)
/* 0AB2C0 800B0860 808D87EC */  lwz     r4, ResettingChan@sda21(r13)
/* 0AB2C4 800B0864 2C040020 */  cmpwi   r4, 0x20
/* 0AB2C8 800B0868 41820040 */  beq     lbl_800B08A8
/* 0AB2CC 800B086C 3C008000 */  lis     r0, 0x8000
/* 0AB2D0 800B0870 7C002430 */  srw     r0, r0, r4
/* 0AB2D4 800B0874 7CA00078 */  andc    r0, r5, r0
/* 0AB2D8 800B0878 1C84000C */  mulli   r4, r4, 0xc
/* 0AB2DC 800B087C 900D8CA0 */  stw     r0, ResettingBits@sda21(r13)
/* 0AB2E0 800B0880 3C608013 */  lis     r3, Origin@ha
/* 0AB2E4 800B0884 38032478 */  addi    r0, r3, Origin@l
/* 0AB2E8 800B0888 7C602214 */  add     r3, r0, r4
/* 0AB2EC 800B088C 38800000 */  li      r4, 0
/* 0AB2F0 800B0890 38A0000C */  li      r5, 0xc
/* 0AB2F4 800B0894 4BF54B3D */  bl      memset
/* 0AB2F8 800B0898 3C80800B */  lis     r4, PADTypeAndStatusCallback@ha
/* 0AB2FC 800B089C 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AB300 800B08A0 38840350 */  addi    r4, r4, PADTypeAndStatusCallback@l
/* 0AB304 800B08A4 4BFF542D */  bl      SIGetTypeAsync
lbl_800B08A8:
/* 0AB308 800B08A8 7FE3FB78 */  mr      r3, r31
/* 0AB30C 800B08AC 4BFEE479 */  bl      OSRestoreInterrupts
/* 0AB310 800B08B0 8001001C */  lwz     r0, 0x1c(r1)
/* 0AB314 800B08B4 38600001 */  li      r3, 1
/* 0AB318 800B08B8 83E10014 */  lwz     r31, 0x14(r1)
/* 0AB31C 800B08BC 83C10010 */  lwz     r30, 0x10(r1)
/* 0AB320 800B08C0 38210018 */  addi    r1, r1, 0x18
/* 0AB324 800B08C4 7C0803A6 */  mtlr    r0
/* 0AB328 800B08C8 4E800020 */  blr     

glabel PADRecalibrate
/* 0AB32C 800B08CC 7C0802A6 */  mflr    r0
/* 0AB330 800B08D0 90010004 */  stw     r0, 4(r1)
/* 0AB334 800B08D4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AB338 800B08D8 93E10014 */  stw     r31, 0x14(r1)
/* 0AB33C 800B08DC 93C10010 */  stw     r30, 0x10(r1)
/* 0AB340 800B08E0 7C7E1B78 */  mr      r30, r3
/* 0AB344 800B08E4 4BFEE419 */  bl      OSDisableInterrupts
/* 0AB348 800B08E8 80AD8CB0 */  lwz     r5, PendingBits@sda21(r13)
/* 0AB34C 800B08EC 39000000 */  li      r8, 0
/* 0AB350 800B08F0 80CD8CA8 */  lwz     r6, WaitingBits@sda21(r13)
/* 0AB354 800B08F4 3C808000 */  lis     r4, 0x8000
/* 0AB358 800B08F8 800D8CAC */  lwz     r0, CheckingBits@sda21(r13)
/* 0AB35C 800B08FC 7FDE2B78 */  or      r30, r30, r5
/* 0AB360 800B0900 80AD8CA0 */  lwz     r5, ResettingBits@sda21(r13)
/* 0AB364 800B0904 7CC60378 */  or      r6, r6, r0
/* 0AB368 800B0908 880430E3 */  lbz     r0, 0x30e3(r4)
/* 0AB36C 800B090C 7FDE3078 */  andc    r30, r30, r6
/* 0AB370 800B0910 80CD8C9C */  lwz     r6, EnabledBits@sda21(r13)
/* 0AB374 800B0914 7CA5F378 */  or      r5, r5, r30
/* 0AB378 800B0918 808D8CB4 */  lwz     r4, BarrelBits@sda21(r13)
/* 0AB37C 800B091C 90AD8CA0 */  stw     r5, ResettingBits@sda21(r13)
/* 0AB380 800B0920 7FC9F0F8 */  nor     r9, r30, r30
/* 0AB384 800B0924 7CC54838 */  and     r5, r6, r9
/* 0AB388 800B0928 7C844838 */  and     r4, r4, r9
/* 0AB38C 800B092C 80ED8CA0 */  lwz     r7, ResettingBits@sda21(r13)
/* 0AB390 800B0930 7C7F1B78 */  mr      r31, r3
/* 0AB394 800B0934 910D8CB0 */  stw     r8, PendingBits@sda21(r13)
/* 0AB398 800B0938 54000673 */  rlwinm. r0, r0, 0, 0x19, 0x19
/* 0AB39C 800B093C 90AD8C9C */  stw     r5, EnabledBits@sda21(r13)
/* 0AB3A0 800B0940 7CE33038 */  and     r3, r7, r6
/* 0AB3A4 800B0944 908D8CB4 */  stw     r4, BarrelBits@sda21(r13)
/* 0AB3A8 800B0948 40820010 */  bne     lbl_800B0958
/* 0AB3AC 800B094C 800D8CA4 */  lwz     r0, RecalibrateBits@sda21(r13)
/* 0AB3B0 800B0950 7C00F378 */  or      r0, r0, r30
/* 0AB3B4 800B0954 900D8CA4 */  stw     r0, RecalibrateBits@sda21(r13)
lbl_800B0958:
/* 0AB3B8 800B0958 4BFF4B21 */  bl      SIDisablePolling
/* 0AB3BC 800B095C 800D87EC */  lwz     r0, ResettingChan@sda21(r13)
/* 0AB3C0 800B0960 2C000020 */  cmpwi   r0, 0x20
/* 0AB3C4 800B0964 40820058 */  bne     lbl_800B09BC
/* 0AB3C8 800B0968 80AD8CA0 */  lwz     r5, ResettingBits@sda21(r13)
/* 0AB3CC 800B096C 7CA00034 */  cntlzw  r0, r5
/* 0AB3D0 800B0970 900D87EC */  stw     r0, ResettingChan@sda21(r13)
/* 0AB3D4 800B0974 808D87EC */  lwz     r4, ResettingChan@sda21(r13)
/* 0AB3D8 800B0978 2C040020 */  cmpwi   r4, 0x20
/* 0AB3DC 800B097C 41820040 */  beq     lbl_800B09BC
/* 0AB3E0 800B0980 3C008000 */  lis     r0, 0x8000
/* 0AB3E4 800B0984 7C002430 */  srw     r0, r0, r4
/* 0AB3E8 800B0988 7CA00078 */  andc    r0, r5, r0
/* 0AB3EC 800B098C 1C84000C */  mulli   r4, r4, 0xc
/* 0AB3F0 800B0990 900D8CA0 */  stw     r0, ResettingBits@sda21(r13)
/* 0AB3F4 800B0994 3C608013 */  lis     r3, Origin@ha
/* 0AB3F8 800B0998 38032478 */  addi    r0, r3, Origin@l
/* 0AB3FC 800B099C 7C602214 */  add     r3, r0, r4
/* 0AB400 800B09A0 38800000 */  li      r4, 0
/* 0AB404 800B09A4 38A0000C */  li      r5, 0xc
/* 0AB408 800B09A8 4BF54A29 */  bl      memset
/* 0AB40C 800B09AC 3C80800B */  lis     r4, PADTypeAndStatusCallback@ha
/* 0AB410 800B09B0 806D87EC */  lwz     r3, ResettingChan@sda21(r13)
/* 0AB414 800B09B4 38840350 */  addi    r4, r4, PADTypeAndStatusCallback@l
/* 0AB418 800B09B8 4BFF5319 */  bl      SIGetTypeAsync
lbl_800B09BC:
/* 0AB41C 800B09BC 7FE3FB78 */  mr      r3, r31
/* 0AB420 800B09C0 4BFEE365 */  bl      OSRestoreInterrupts
/* 0AB424 800B09C4 8001001C */  lwz     r0, 0x1c(r1)
/* 0AB428 800B09C8 38600001 */  li      r3, 1
/* 0AB42C 800B09CC 83E10014 */  lwz     r31, 0x14(r1)
/* 0AB430 800B09D0 83C10010 */  lwz     r30, 0x10(r1)
/* 0AB434 800B09D4 38210018 */  addi    r1, r1, 0x18
/* 0AB438 800B09D8 7C0803A6 */  mtlr    r0
/* 0AB43C 800B09DC 4E800020 */  blr     

glabel PADInit
/* 0AB440 800B09E0 7C0802A6 */  mflr    r0
/* 0AB444 800B09E4 3C608013 */  lis     r3, Type@ha
/* 0AB448 800B09E8 90010004 */  stw     r0, 4(r1)
/* 0AB44C 800B09EC 9421FFC8 */  stwu    r1, -0x38(r1)
/* 0AB450 800B09F0 BF21001C */  stmw    r25, 0x1c(r1)
/* 0AB454 800B09F4 3BE32468 */  addi    r31, r3, Type@l
/* 0AB458 800B09F8 800D8C98 */  lwz     r0, Initialized@sda21(r13)
/* 0AB45C 800B09FC 2C000000 */  cmpwi   r0, 0
/* 0AB460 800B0A00 4182000C */  beq     lbl_800B0A0C
/* 0AB464 800B0A04 38600001 */  li      r3, 1
/* 0AB468 800B0A08 48000114 */  b       lbl_800B0B1C
lbl_800B0A0C:
/* 0AB46C 800B0A0C 806D87E8 */  lwz     r3, __PADVersion@sda21(r13)
/* 0AB470 800B0A10 4BFEBC81 */  bl      OSRegisterVersion
/* 0AB474 800B0A14 806D8CC0 */  lwz     r3, __PADSpec@sda21(r13)
/* 0AB478 800B0A18 28030000 */  cmplwi  r3, 0
/* 0AB47C 800B0A1C 41820008 */  beq     lbl_800B0A24
/* 0AB480 800B0A20 480004C9 */  bl      PADSetSpec
lbl_800B0A24:
/* 0AB484 800B0A24 800D8BC0 */  lwz     r0, __PADFixBits@sda21(r13)
/* 0AB488 800B0A28 38600001 */  li      r3, 1
/* 0AB48C 800B0A2C 906D8C98 */  stw     r3, Initialized@sda21(r13)
/* 0AB490 800B0A30 28000000 */  cmplwi  r0, 0
/* 0AB494 800B0A34 4182008C */  beq     lbl_800B0AC0
/* 0AB498 800B0A38 4BFF1871 */  bl      OSGetTime
/* 0AB49C 800B0A3C 3B240000 */  addi    r25, r4, 0
/* 0AB4A0 800B0A40 3B430000 */  addi    r26, r3, 0
/* 0AB4A4 800B0A44 38A00010 */  li      r5, 0x10
/* 0AB4A8 800B0A48 4801D345 */  bl      __shr2i
/* 0AB4AC 800B0A4C 3CA00001 */  lis     r5, 1
/* 0AB4B0 800B0A50 3B65FFFF */  addi    r27, r5, -1
/* 0AB4B4 800B0A54 3B800000 */  li      r28, 0
/* 0AB4B8 800B0A58 7C86D838 */  and     r6, r4, r27
/* 0AB4BC 800B0A5C 7F24D838 */  and     r4, r25, r27
/* 0AB4C0 800B0A60 7C65E038 */  and     r5, r3, r28
/* 0AB4C4 800B0A64 7F40E038 */  and     r0, r26, r28
/* 0AB4C8 800B0A68 7FA43014 */  addc    r29, r4, r6
/* 0AB4CC 800B0A6C 387A0000 */  addi    r3, r26, 0
/* 0AB4D0 800B0A70 38990000 */  addi    r4, r25, 0
/* 0AB4D4 800B0A74 7FC02914 */  adde    r30, r0, r5
/* 0AB4D8 800B0A78 38A00020 */  li      r5, 0x20
/* 0AB4DC 800B0A7C 4801D311 */  bl      __shr2i
/* 0AB4E0 800B0A80 7C84D838 */  and     r4, r4, r27
/* 0AB4E4 800B0A84 7C60E038 */  and     r0, r3, r28
/* 0AB4E8 800B0A88 7FA4E814 */  addc    r29, r4, r29
/* 0AB4EC 800B0A8C 387A0000 */  addi    r3, r26, 0
/* 0AB4F0 800B0A90 38990000 */  addi    r4, r25, 0
/* 0AB4F4 800B0A94 7FC0F114 */  adde    r30, r0, r30
/* 0AB4F8 800B0A98 38A00030 */  li      r5, 0x30
/* 0AB4FC 800B0A9C 4801D2F1 */  bl      __shr2i
/* 0AB500 800B0AA0 7C80D838 */  and     r0, r4, r27
/* 0AB504 800B0AA4 7CA0E814 */  addc    r5, r0, r29
/* 0AB508 800B0AA8 3C00F000 */  lis     r0, 0xf000
/* 0AB50C 800B0AAC 38803FFF */  li      r4, 0x3fff
/* 0AB510 800B0AB0 900D8CA4 */  stw     r0, RecalibrateBits@sda21(r13)
/* 0AB514 800B0AB4 7CA02038 */  and     r0, r5, r4
/* 0AB518 800B0AB8 3C608000 */  lis     r3, 0x8000
/* 0AB51C 800B0ABC B00330E0 */  sth     r0, 0x30e0(r3)
lbl_800B0AC0:
/* 0AB520 800B0AC0 3C608000 */  lis     r3, 0x8000
/* 0AB524 800B0AC4 A00330E0 */  lhz     r0, 0x30e0(r3)
/* 0AB528 800B0AC8 540042AE */  rlwinm  r0, r0, 8, 0xa, 0x17
/* 0AB52C 800B0ACC 64004D00 */  oris    r0, r0, 0x4d00
/* 0AB530 800B0AD0 901F0040 */  stw     r0, 0x40(r31)
/* 0AB534 800B0AD4 A00330E0 */  lhz     r0, 0x30e0(r3)
/* 0AB538 800B0AD8 540042AE */  rlwinm  r0, r0, 8, 0xa, 0x17
/* 0AB53C 800B0ADC 64004D40 */  oris    r0, r0, 0x4d40
/* 0AB540 800B0AE0 901F0044 */  stw     r0, 0x44(r31)
/* 0AB544 800B0AE4 A00330E0 */  lhz     r0, 0x30e0(r3)
/* 0AB548 800B0AE8 540042AE */  rlwinm  r0, r0, 8, 0xa, 0x17
/* 0AB54C 800B0AEC 64004D80 */  oris    r0, r0, 0x4d80
/* 0AB550 800B0AF0 901F0048 */  stw     r0, 0x48(r31)
/* 0AB554 800B0AF4 A00330E0 */  lhz     r0, 0x30e0(r3)
/* 0AB558 800B0AF8 540042AE */  rlwinm  r0, r0, 8, 0xa, 0x17
/* 0AB55C 800B0AFC 64004DC0 */  oris    r0, r0, 0x4dc0
/* 0AB560 800B0B00 901F004C */  stw     r0, 0x4c(r31)
/* 0AB564 800B0B04 4BFF53ED */  bl      SIRefreshSamplingRate
/* 0AB568 800B0B08 3C60800F */  lis     r3, ResetFunctionInfo@ha
/* 0AB56C 800B0B0C 386322E8 */  addi    r3, r3, ResetFunctionInfo@l
/* 0AB570 800B0B10 4BFEF319 */  bl      OSRegisterResetFunction
/* 0AB574 800B0B14 3C60F000 */  lis     r3, 0xf000
/* 0AB578 800B0B18 4BFFFCA5 */  bl      PADReset
lbl_800B0B1C:
/* 0AB57C 800B0B1C BB21001C */  lmw     r25, 0x1c(r1)
/* 0AB580 800B0B20 8001003C */  lwz     r0, 0x3c(r1)
/* 0AB584 800B0B24 38210038 */  addi    r1, r1, 0x38
/* 0AB588 800B0B28 7C0803A6 */  mtlr    r0
/* 0AB58C 800B0B2C 4E800020 */  blr     

glabel PADRead
/* 0AB590 800B0B30 7C0802A6 */  mflr    r0
/* 0AB594 800B0B34 90010004 */  stw     r0, 4(r1)
/* 0AB598 800B0B38 9421FFC0 */  stwu    r1, -0x40(r1)
/* 0AB59C 800B0B3C BEC10018 */  stmw    r22, 0x18(r1)
/* 0AB5A0 800B0B40 7C771B78 */  mr      r23, r3
/* 0AB5A4 800B0B44 4BFEE1B9 */  bl      OSDisableInterrupts
/* 0AB5A8 800B0B48 3B200000 */  li      r25, 0
/* 0AB5AC 800B0B4C 1CB9000C */  mulli   r5, r25, 0xc
/* 0AB5B0 800B0B50 3C808013 */  lis     r4, Origin@ha
/* 0AB5B4 800B0B54 38042478 */  addi    r0, r4, Origin@l
/* 0AB5B8 800B0B58 7F802A14 */  add     r28, r0, r5
/* 0AB5BC 800B0B5C 3C80800B */  lis     r4, PADOriginUpdateCallback@ha
/* 0AB5C0 800B0B60 3CA0800B */  lis     r5, PADReceiveCheckCallback@ha
/* 0AB5C4 800B0B64 3B430000 */  addi    r26, r3, 0
/* 0AB5C8 800B0B68 3AC401AC */  addi    r22, r4, PADOriginUpdateCallback@l
/* 0AB5CC 800B0B6C 3BE5067C */  addi    r31, r5, PADReceiveCheckCallback@l
/* 0AB5D0 800B0B70 3B000000 */  li      r24, 0
/* 0AB5D4 800B0B74 3FC08000 */  lis     r30, 0x8000
lbl_800B0B78:
/* 0AB5D8 800B0B78 800D8CB0 */  lwz     r0, PendingBits@sda21(r13)
/* 0AB5DC 800B0B7C 7FDBCC30 */  srw     r27, r30, r25
/* 0AB5E0 800B0B80 7C00D839 */  and.    r0, r0, r27
/* 0AB5E4 800B0B84 41820028 */  beq     lbl_800B0BAC
/* 0AB5E8 800B0B88 38600000 */  li      r3, 0
/* 0AB5EC 800B0B8C 4BFFFC31 */  bl      PADReset
/* 0AB5F0 800B0B90 3800FFFE */  li      r0, -2
/* 0AB5F4 800B0B94 9817000A */  stb     r0, 0xa(r23)
/* 0AB5F8 800B0B98 38770000 */  addi    r3, r23, 0
/* 0AB5FC 800B0B9C 38800000 */  li      r4, 0
/* 0AB600 800B0BA0 38A0000A */  li      r5, 0xa
/* 0AB604 800B0BA4 4BF5482D */  bl      memset
/* 0AB608 800B0BA8 48000254 */  b       lbl_800B0DFC
lbl_800B0BAC:
/* 0AB60C 800B0BAC 800D8CA0 */  lwz     r0, ResettingBits@sda21(r13)
/* 0AB610 800B0BB0 7C00D839 */  and.    r0, r0, r27
/* 0AB614 800B0BB4 40820010 */  bne     lbl_800B0BC4
/* 0AB618 800B0BB8 800D87EC */  lwz     r0, ResettingChan@sda21(r13)
/* 0AB61C 800B0BBC 7C00C800 */  cmpw    r0, r25
/* 0AB620 800B0BC0 40820020 */  bne     lbl_800B0BE0
lbl_800B0BC4:
/* 0AB624 800B0BC4 3800FFFE */  li      r0, -2
/* 0AB628 800B0BC8 9817000A */  stb     r0, 0xa(r23)
/* 0AB62C 800B0BCC 38770000 */  addi    r3, r23, 0
/* 0AB630 800B0BD0 38800000 */  li      r4, 0
/* 0AB634 800B0BD4 38A0000A */  li      r5, 0xa
/* 0AB638 800B0BD8 4BF547F9 */  bl      memset
/* 0AB63C 800B0BDC 48000220 */  b       lbl_800B0DFC
lbl_800B0BE0:
/* 0AB640 800B0BE0 800D8C9C */  lwz     r0, EnabledBits@sda21(r13)
/* 0AB644 800B0BE4 7C00D839 */  and.    r0, r0, r27
/* 0AB648 800B0BE8 40820020 */  bne     lbl_800B0C08
/* 0AB64C 800B0BEC 3800FFFF */  li      r0, -1
/* 0AB650 800B0BF0 9817000A */  stb     r0, 0xa(r23)
/* 0AB654 800B0BF4 38770000 */  addi    r3, r23, 0
/* 0AB658 800B0BF8 38800000 */  li      r4, 0
/* 0AB65C 800B0BFC 38A0000A */  li      r5, 0xa
/* 0AB660 800B0C00 4BF547D1 */  bl      memset
/* 0AB664 800B0C04 480001F8 */  b       lbl_800B0DFC
lbl_800B0C08:
/* 0AB668 800B0C08 7F23CB78 */  mr      r3, r25
/* 0AB66C 800B0C0C 4BFF3B31 */  bl      SIIsChanBusy
/* 0AB670 800B0C10 2C030000 */  cmpwi   r3, 0
/* 0AB674 800B0C14 41820020 */  beq     lbl_800B0C34
/* 0AB678 800B0C18 3800FFFD */  li      r0, -3
/* 0AB67C 800B0C1C 9817000A */  stb     r0, 0xa(r23)
/* 0AB680 800B0C20 38770000 */  addi    r3, r23, 0
/* 0AB684 800B0C24 38800000 */  li      r4, 0
/* 0AB688 800B0C28 38A0000A */  li      r5, 0xa
/* 0AB68C 800B0C2C 4BF547A5 */  bl      memset
/* 0AB690 800B0C30 480001CC */  b       lbl_800B0DFC
lbl_800B0C34:
/* 0AB694 800B0C34 7F23CB78 */  mr      r3, r25
/* 0AB698 800B0C38 4BFF4699 */  bl      SIGetStatus
/* 0AB69C 800B0C3C 54600739 */  rlwinm. r0, r3, 0, 0x1c, 0x1c
/* 0AB6A0 800B0C40 418200D8 */  beq     lbl_800B0D18
/* 0AB6A4 800B0C44 38790000 */  addi    r3, r25, 0
/* 0AB6A8 800B0C48 38810010 */  addi    r4, r1, 0x10
/* 0AB6AC 800B0C4C 4BFF496D */  bl      SIGetResponse
/* 0AB6B0 800B0C50 800D8CA8 */  lwz     r0, WaitingBits@sda21(r13)
/* 0AB6B4 800B0C54 7C00D839 */  and.    r0, r0, r27
/* 0AB6B8 800B0C58 41820040 */  beq     lbl_800B0C98
/* 0AB6BC 800B0C5C 38000000 */  li      r0, 0
/* 0AB6C0 800B0C60 9817000A */  stb     r0, 0xa(r23)
/* 0AB6C4 800B0C64 38770000 */  addi    r3, r23, 0
/* 0AB6C8 800B0C68 38800000 */  li      r4, 0
/* 0AB6CC 800B0C6C 38A0000A */  li      r5, 0xa
/* 0AB6D0 800B0C70 4BF54761 */  bl      memset
/* 0AB6D4 800B0C74 806D8CAC */  lwz     r3, CheckingBits@sda21(r13)
/* 0AB6D8 800B0C78 7C60D839 */  and.    r0, r3, r27
/* 0AB6DC 800B0C7C 40820180 */  bne     lbl_800B0DFC
/* 0AB6E0 800B0C80 7C60DB78 */  or      r0, r3, r27
/* 0AB6E4 800B0C84 900D8CAC */  stw     r0, CheckingBits@sda21(r13)
/* 0AB6E8 800B0C88 38790000 */  addi    r3, r25, 0
/* 0AB6EC 800B0C8C 389F0000 */  addi    r4, r31, 0
/* 0AB6F0 800B0C90 4BFF5041 */  bl      SIGetTypeAsync
/* 0AB6F4 800B0C94 48000168 */  b       lbl_800B0DFC
lbl_800B0C98:
/* 0AB6F8 800B0C98 4BFEE065 */  bl      OSDisableInterrupts
/* 0AB6FC 800B0C9C 3BA30000 */  addi    r29, r3, 0
/* 0AB700 800B0CA0 387B0000 */  addi    r3, r27, 0
/* 0AB704 800B0CA4 4BFF47D5 */  bl      SIDisablePolling
/* 0AB708 800B0CA8 800D8C9C */  lwz     r0, EnabledBits@sda21(r13)
/* 0AB70C 800B0CAC 7F69D8F8 */  nor     r9, r27, r27
/* 0AB710 800B0CB0 80CD8CA8 */  lwz     r6, WaitingBits@sda21(r13)
/* 0AB714 800B0CB4 7F23CB78 */  mr      r3, r25
/* 0AB718 800B0CB8 80AD8CAC */  lwz     r5, CheckingBits@sda21(r13)
/* 0AB71C 800B0CBC 808D8CB0 */  lwz     r4, PendingBits@sda21(r13)
/* 0AB720 800B0CC0 7C084838 */  and     r8, r0, r9
/* 0AB724 800B0CC4 800D8CB4 */  lwz     r0, BarrelBits@sda21(r13)
/* 0AB728 800B0CC8 7CC74838 */  and     r7, r6, r9
/* 0AB72C 800B0CCC 7CA64838 */  and     r6, r5, r9
/* 0AB730 800B0CD0 7C854838 */  and     r5, r4, r9
/* 0AB734 800B0CD4 910D8C9C */  stw     r8, EnabledBits@sda21(r13)
/* 0AB738 800B0CD8 7C004838 */  and     r0, r0, r9
/* 0AB73C 800B0CDC 90ED8CA8 */  stw     r7, WaitingBits@sda21(r13)
/* 0AB740 800B0CE0 38800000 */  li      r4, 0
/* 0AB744 800B0CE4 90CD8CAC */  stw     r6, CheckingBits@sda21(r13)
/* 0AB748 800B0CE8 90AD8CB0 */  stw     r5, PendingBits@sda21(r13)
/* 0AB74C 800B0CEC 900D8CB4 */  stw     r0, BarrelBits@sda21(r13)
/* 0AB750 800B0CF0 4BFF0191 */  bl      OSSetWirelessID
/* 0AB754 800B0CF4 7FA3EB78 */  mr      r3, r29
/* 0AB758 800B0CF8 4BFEE02D */  bl      OSRestoreInterrupts
/* 0AB75C 800B0CFC 3800FFFF */  li      r0, -1
/* 0AB760 800B0D00 9817000A */  stb     r0, 0xa(r23)
/* 0AB764 800B0D04 38770000 */  addi    r3, r23, 0
/* 0AB768 800B0D08 38800000 */  li      r4, 0
/* 0AB76C 800B0D0C 38A0000A */  li      r5, 0xa
/* 0AB770 800B0D10 4BF546C1 */  bl      memset
/* 0AB774 800B0D14 480000E8 */  b       lbl_800B0DFC
lbl_800B0D18:
/* 0AB778 800B0D18 7F23CB78 */  mr      r3, r25
/* 0AB77C 800B0D1C 4BFF4DF1 */  bl      SIGetType
/* 0AB780 800B0D20 54600085 */  rlwinm. r0, r3, 0, 2, 2
/* 0AB784 800B0D24 40820008 */  bne     lbl_800B0D2C
/* 0AB788 800B0D28 7F18DB78 */  or      r24, r24, r27
lbl_800B0D2C:
/* 0AB78C 800B0D2C 38790000 */  addi    r3, r25, 0
/* 0AB790 800B0D30 38810010 */  addi    r4, r1, 0x10
/* 0AB794 800B0D34 4BFF4885 */  bl      SIGetResponse
/* 0AB798 800B0D38 2C030000 */  cmpwi   r3, 0
/* 0AB79C 800B0D3C 40820020 */  bne     lbl_800B0D5C
/* 0AB7A0 800B0D40 3800FFFD */  li      r0, -3
/* 0AB7A4 800B0D44 9817000A */  stb     r0, 0xa(r23)
/* 0AB7A8 800B0D48 38770000 */  addi    r3, r23, 0
/* 0AB7AC 800B0D4C 38800000 */  li      r4, 0
/* 0AB7B0 800B0D50 38A0000A */  li      r5, 0xa
/* 0AB7B4 800B0D54 4BF5467D */  bl      memset
/* 0AB7B8 800B0D58 480000A4 */  b       lbl_800B0DFC
lbl_800B0D5C:
/* 0AB7BC 800B0D5C 80010010 */  lwz     r0, 0x10(r1)
/* 0AB7C0 800B0D60 54000001 */  rlwinm. r0, r0, 0, 0, 0
/* 0AB7C4 800B0D64 41820020 */  beq     lbl_800B0D84
/* 0AB7C8 800B0D68 3800FFFD */  li      r0, -3
/* 0AB7CC 800B0D6C 9817000A */  stb     r0, 0xa(r23)
/* 0AB7D0 800B0D70 38770000 */  addi    r3, r23, 0
/* 0AB7D4 800B0D74 38800000 */  li      r4, 0
/* 0AB7D8 800B0D78 38A0000A */  li      r5, 0xa
/* 0AB7DC 800B0D7C 4BF54655 */  bl      memset
/* 0AB7E0 800B0D80 4800007C */  b       lbl_800B0DFC
lbl_800B0D84:
/* 0AB7E4 800B0D84 818D87FC */  lwz     r12, MakeStatus@sda21(r13)
/* 0AB7E8 800B0D88 38790000 */  addi    r3, r25, 0
/* 0AB7EC 800B0D8C 38970000 */  addi    r4, r23, 0
/* 0AB7F0 800B0D90 7D8803A6 */  mtlr    r12
/* 0AB7F4 800B0D94 38A10010 */  addi    r5, r1, 0x10
/* 0AB7F8 800B0D98 4E800021 */  blrl    
/* 0AB7FC 800B0D9C A0170000 */  lhz     r0, 0(r23)
/* 0AB800 800B0DA0 540004A5 */  rlwinm. r0, r0, 0, 0x12, 0x12
/* 0AB804 800B0DA4 41820044 */  beq     lbl_800B0DE8
/* 0AB808 800B0DA8 3800FFFD */  li      r0, -3
/* 0AB80C 800B0DAC 9817000A */  stb     r0, 0xa(r23)
/* 0AB810 800B0DB0 38770000 */  addi    r3, r23, 0
/* 0AB814 800B0DB4 38800000 */  li      r4, 0
/* 0AB818 800B0DB8 38A0000A */  li      r5, 0xa
/* 0AB81C 800B0DBC 4BF54615 */  bl      memset
/* 0AB820 800B0DC0 38790000 */  addi    r3, r25, 0
/* 0AB824 800B0DC4 38DC0000 */  addi    r6, r28, 0
/* 0AB828 800B0DC8 39160000 */  addi    r8, r22, 0
/* 0AB82C 800B0DCC 388D8800 */  addi    r4, r13, CmdReadOrigin@sda21
/* 0AB830 800B0DD0 38A00001 */  li      r5, 1
/* 0AB834 800B0DD4 38E0000A */  li      r7, 0xa
/* 0AB838 800B0DD8 39400000 */  li      r10, 0
/* 0AB83C 800B0DDC 39200000 */  li      r9, 0
/* 0AB840 800B0DE0 4BFF4929 */  bl      SITransfer
/* 0AB844 800B0DE4 48000018 */  b       lbl_800B0DFC
lbl_800B0DE8:
/* 0AB848 800B0DE8 38000000 */  li      r0, 0
/* 0AB84C 800B0DEC 9817000A */  stb     r0, 0xa(r23)
/* 0AB850 800B0DF0 A0170000 */  lhz     r0, 0(r23)
/* 0AB854 800B0DF4 5400066E */  rlwinm  r0, r0, 0, 0x19, 0x17
/* 0AB858 800B0DF8 B0170000 */  sth     r0, 0(r23)
lbl_800B0DFC:
/* 0AB85C 800B0DFC 3B390001 */  addi    r25, r25, 1
/* 0AB860 800B0E00 2C190004 */  cmpwi   r25, 4
/* 0AB864 800B0E04 3B9C000C */  addi    r28, r28, 0xc
/* 0AB868 800B0E08 3AF7000C */  addi    r23, r23, 0xc
/* 0AB86C 800B0E0C 4180FD6C */  blt     lbl_800B0B78
/* 0AB870 800B0E10 7F43D378 */  mr      r3, r26
/* 0AB874 800B0E14 4BFEDF11 */  bl      OSRestoreInterrupts
/* 0AB878 800B0E18 7F03C378 */  mr      r3, r24
/* 0AB87C 800B0E1C BAC10018 */  lmw     r22, 0x18(r1)
/* 0AB880 800B0E20 80010044 */  lwz     r0, 0x44(r1)
/* 0AB884 800B0E24 38210040 */  addi    r1, r1, 0x40
/* 0AB888 800B0E28 7C0803A6 */  mtlr    r0
/* 0AB88C 800B0E2C 4E800020 */  blr     

glabel PADControlMotor
/* 0AB890 800B0E30 7C0802A6 */  mflr    r0
/* 0AB894 800B0E34 90010004 */  stw     r0, 4(r1)
/* 0AB898 800B0E38 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0AB89C 800B0E3C 93E10024 */  stw     r31, 0x24(r1)
/* 0AB8A0 800B0E40 93C10020 */  stw     r30, 0x20(r1)
/* 0AB8A4 800B0E44 3BC40000 */  addi    r30, r4, 0
/* 0AB8A8 800B0E48 93A1001C */  stw     r29, 0x1c(r1)
/* 0AB8AC 800B0E4C 3BA30000 */  addi    r29, r3, 0
/* 0AB8B0 800B0E50 4BFEDEAD */  bl      OSDisableInterrupts
/* 0AB8B4 800B0E54 3C008000 */  lis     r0, 0x8000
/* 0AB8B8 800B0E58 808D8C9C */  lwz     r4, EnabledBits@sda21(r13)
/* 0AB8BC 800B0E5C 7C00EC30 */  srw     r0, r0, r29
/* 0AB8C0 800B0E60 7C800039 */  and.    r0, r4, r0
/* 0AB8C4 800B0E64 3BE30000 */  addi    r31, r3, 0
/* 0AB8C8 800B0E68 4182005C */  beq     lbl_800B0EC4
/* 0AB8CC 800B0E6C 7FA3EB78 */  mr      r3, r29
/* 0AB8D0 800B0E70 4BFF4C9D */  bl      SIGetType
/* 0AB8D4 800B0E74 54600085 */  rlwinm. r0, r3, 0, 2, 2
/* 0AB8D8 800B0E78 4082004C */  bne     lbl_800B0EC4
/* 0AB8DC 800B0E7C 800D87F8 */  lwz     r0, Spec@sda21(r13)
/* 0AB8E0 800B0E80 28000002 */  cmplwi  r0, 2
/* 0AB8E4 800B0E84 40800010 */  bge     lbl_800B0E94
/* 0AB8E8 800B0E88 281E0002 */  cmplwi  r30, 2
/* 0AB8EC 800B0E8C 40820008 */  bne     lbl_800B0E94
/* 0AB8F0 800B0E90 3BC00000 */  li      r30, 0
lbl_800B0E94:
/* 0AB8F4 800B0E94 3C608000 */  lis     r3, 0x8000
/* 0AB8F8 800B0E98 880330E3 */  lbz     r0, 0x30e3(r3)
/* 0AB8FC 800B0E9C 540006B5 */  rlwinm. r0, r0, 0, 0x1a, 0x1a
/* 0AB900 800B0EA0 41820008 */  beq     lbl_800B0EA8
/* 0AB904 800B0EA4 3BC00000 */  li      r30, 0
lbl_800B0EA8:
/* 0AB908 800B0EA8 808D87F4 */  lwz     r4, AnalogMode@sda21(r13)
/* 0AB90C 800B0EAC 57C007BE */  clrlwi  r0, r30, 0x1e
/* 0AB910 800B0EB0 387D0000 */  addi    r3, r29, 0
/* 0AB914 800B0EB4 64840040 */  oris    r4, r4, 0x40
/* 0AB918 800B0EB8 7C840378 */  or      r4, r4, r0
/* 0AB91C 800B0EBC 4BFF4491 */  bl      SISetCommand
/* 0AB920 800B0EC0 4BFF44A1 */  bl      SITransferCommands
lbl_800B0EC4:
/* 0AB924 800B0EC4 7FE3FB78 */  mr      r3, r31
/* 0AB928 800B0EC8 4BFEDE5D */  bl      OSRestoreInterrupts
/* 0AB92C 800B0ECC 8001002C */  lwz     r0, 0x2c(r1)
/* 0AB930 800B0ED0 83E10024 */  lwz     r31, 0x24(r1)
/* 0AB934 800B0ED4 83C10020 */  lwz     r30, 0x20(r1)
/* 0AB938 800B0ED8 83A1001C */  lwz     r29, 0x1c(r1)
/* 0AB93C 800B0EDC 38210028 */  addi    r1, r1, 0x28
/* 0AB940 800B0EE0 7C0803A6 */  mtlr    r0
/* 0AB944 800B0EE4 4E800020 */  blr     

glabel PADSetSpec
/* 0AB948 800B0EE8 38000000 */  li      r0, 0
/* 0AB94C 800B0EEC 2C030001 */  cmpwi   r3, 1
/* 0AB950 800B0EF0 900D8CC0 */  stw     r0, __PADSpec@sda21(r13)
/* 0AB954 800B0EF4 41820030 */  beq     lbl_800B0F24
/* 0AB958 800B0EF8 40800010 */  bge     lbl_800B0F08
/* 0AB95C 800B0EFC 2C030000 */  cmpwi   r3, 0
/* 0AB960 800B0F00 40800014 */  bge     lbl_800B0F14
/* 0AB964 800B0F04 4800003C */  b       lbl_800B0F40
lbl_800B0F08:
/* 0AB968 800B0F08 2C030006 */  cmpwi   r3, 6
/* 0AB96C 800B0F0C 40800034 */  bge     lbl_800B0F40
/* 0AB970 800B0F10 48000024 */  b       lbl_800B0F34
lbl_800B0F14:
/* 0AB974 800B0F14 3C80800B */  lis     r4, SPEC0_MakeStatus@ha
/* 0AB978 800B0F18 38040F48 */  addi    r0, r4, SPEC0_MakeStatus@l
/* 0AB97C 800B0F1C 900D87FC */  stw     r0, MakeStatus@sda21(r13)
/* 0AB980 800B0F20 48000020 */  b       lbl_800B0F40
lbl_800B0F24:
/* 0AB984 800B0F24 3C80800B */  lis     r4, SPEC1_MakeStatus@ha
/* 0AB988 800B0F28 380410BC */  addi    r0, r4, SPEC1_MakeStatus@l
/* 0AB98C 800B0F2C 900D87FC */  stw     r0, MakeStatus@sda21(r13)
/* 0AB990 800B0F30 48000010 */  b       lbl_800B0F40
lbl_800B0F34:
/* 0AB994 800B0F34 3C80800B */  lis     r4, SPEC2_MakeStatus@ha
/* 0AB998 800B0F38 38041230 */  addi    r0, r4, SPEC2_MakeStatus@l
/* 0AB99C 800B0F3C 900D87FC */  stw     r0, MakeStatus@sda21(r13)
lbl_800B0F40:
/* 0AB9A0 800B0F40 906D87F8 */  stw     r3, Spec@sda21(r13)
/* 0AB9A4 800B0F44 4E800020 */  blr     

SPEC0_MakeStatus:
/* 0AB9A8 800B0F48 38600000 */  li      r3, 0
/* 0AB9AC 800B0F4C B0640000 */  sth     r3, 0(r4)
/* 0AB9B0 800B0F50 80050000 */  lwz     r0, 0(r5)
/* 0AB9B4 800B0F54 54008739 */  rlwinm. r0, r0, 0x10, 0x1c, 0x1c
/* 0AB9B8 800B0F58 41820008 */  beq     lbl_800B0F60
/* 0AB9BC 800B0F5C 38600100 */  li      r3, 0x100
lbl_800B0F60:
/* 0AB9C0 800B0F60 A0040000 */  lhz     r0, 0(r4)
/* 0AB9C4 800B0F64 7C001B78 */  or      r0, r0, r3
/* 0AB9C8 800B0F68 B0040000 */  sth     r0, 0(r4)
/* 0AB9CC 800B0F6C 80050000 */  lwz     r0, 0(r5)
/* 0AB9D0 800B0F70 540086B5 */  rlwinm. r0, r0, 0x10, 0x1a, 0x1a
/* 0AB9D4 800B0F74 4182000C */  beq     lbl_800B0F80
/* 0AB9D8 800B0F78 38600200 */  li      r3, 0x200
/* 0AB9DC 800B0F7C 48000008 */  b       lbl_800B0F84
lbl_800B0F80:
/* 0AB9E0 800B0F80 38600000 */  li      r3, 0
lbl_800B0F84:
/* 0AB9E4 800B0F84 A0040000 */  lhz     r0, 0(r4)
/* 0AB9E8 800B0F88 7C001B78 */  or      r0, r0, r3
/* 0AB9EC 800B0F8C B0040000 */  sth     r0, 0(r4)
/* 0AB9F0 800B0F90 80050000 */  lwz     r0, 0(r5)
/* 0AB9F4 800B0F94 540085EF */  rlwinm. r0, r0, 0x10, 0x17, 0x17
/* 0AB9F8 800B0F98 4182000C */  beq     lbl_800B0FA4
/* 0AB9FC 800B0F9C 38600400 */  li      r3, 0x400
/* 0ABA00 800B0FA0 48000008 */  b       lbl_800B0FA8
lbl_800B0FA4:
/* 0ABA04 800B0FA4 38600000 */  li      r3, 0
lbl_800B0FA8:
/* 0ABA08 800B0FA8 A0040000 */  lhz     r0, 0(r4)
/* 0ABA0C 800B0FAC 7C001B78 */  or      r0, r0, r3
/* 0ABA10 800B0FB0 B0040000 */  sth     r0, 0(r4)
/* 0ABA14 800B0FB4 80050000 */  lwz     r0, 0(r5)
/* 0ABA18 800B0FB8 540087FF */  rlwinm. r0, r0, 0x10, 0x1f, 0x1f
/* 0ABA1C 800B0FBC 4182000C */  beq     lbl_800B0FC8
/* 0ABA20 800B0FC0 38600800 */  li      r3, 0x800
/* 0ABA24 800B0FC4 48000008 */  b       lbl_800B0FCC
lbl_800B0FC8:
/* 0ABA28 800B0FC8 38600000 */  li      r3, 0
lbl_800B0FCC:
/* 0ABA2C 800B0FCC A0040000 */  lhz     r0, 0(r4)
/* 0ABA30 800B0FD0 7C001B78 */  or      r0, r0, r3
/* 0ABA34 800B0FD4 B0040000 */  sth     r0, 0(r4)
/* 0ABA38 800B0FD8 80050000 */  lwz     r0, 0(r5)
/* 0ABA3C 800B0FDC 540086F7 */  rlwinm. r0, r0, 0x10, 0x1b, 0x1b
/* 0ABA40 800B0FE0 4182000C */  beq     lbl_800B0FEC
/* 0ABA44 800B0FE4 38C01000 */  li      r6, 0x1000
/* 0ABA48 800B0FE8 48000008 */  b       lbl_800B0FF0
lbl_800B0FEC:
/* 0ABA4C 800B0FEC 38C00000 */  li      r6, 0
lbl_800B0FF0:
/* 0ABA50 800B0FF0 A0640000 */  lhz     r3, 0(r4)
/* 0ABA54 800B0FF4 38000000 */  li      r0, 0
/* 0ABA58 800B0FF8 7C633378 */  or      r3, r3, r6
/* 0ABA5C 800B0FFC B0640000 */  sth     r3, 0(r4)
/* 0ABA60 800B1000 80650004 */  lwz     r3, 4(r5)
/* 0ABA64 800B1004 5463843E */  srwi    r3, r3, 0x10
/* 0ABA68 800B1008 7C630774 */  extsb   r3, r3
/* 0ABA6C 800B100C 98640002 */  stb     r3, 2(r4)
/* 0ABA70 800B1010 80650004 */  lwz     r3, 4(r5)
/* 0ABA74 800B1014 5463463E */  srwi    r3, r3, 0x18
/* 0ABA78 800B1018 7C630774 */  extsb   r3, r3
/* 0ABA7C 800B101C 98640003 */  stb     r3, 3(r4)
/* 0ABA80 800B1020 80650004 */  lwz     r3, 4(r5)
/* 0ABA84 800B1024 7C630774 */  extsb   r3, r3
/* 0ABA88 800B1028 98640004 */  stb     r3, 4(r4)
/* 0ABA8C 800B102C 80650004 */  lwz     r3, 4(r5)
/* 0ABA90 800B1030 5463C23E */  srwi    r3, r3, 8
/* 0ABA94 800B1034 7C630774 */  extsb   r3, r3
/* 0ABA98 800B1038 98640005 */  stb     r3, 5(r4)
/* 0ABA9C 800B103C 80650000 */  lwz     r3, 0(r5)
/* 0ABAA0 800B1040 5463C63E */  rlwinm  r3, r3, 0x18, 0x18, 0x1f
/* 0ABAA4 800B1044 98640006 */  stb     r3, 6(r4)
/* 0ABAA8 800B1048 80650000 */  lwz     r3, 0(r5)
/* 0ABAAC 800B104C 98640007 */  stb     r3, 7(r4)
/* 0ABAB0 800B1050 98040008 */  stb     r0, 8(r4)
/* 0ABAB4 800B1054 98040009 */  stb     r0, 9(r4)
/* 0ABAB8 800B1058 88040006 */  lbz     r0, 6(r4)
/* 0ABABC 800B105C 280000AA */  cmplwi  r0, 0xaa
/* 0ABAC0 800B1060 41800010 */  blt     lbl_800B1070
/* 0ABAC4 800B1064 A0040000 */  lhz     r0, 0(r4)
/* 0ABAC8 800B1068 60000040 */  ori     r0, r0, 0x40
/* 0ABACC 800B106C B0040000 */  sth     r0, 0(r4)
lbl_800B1070:
/* 0ABAD0 800B1070 88040007 */  lbz     r0, 7(r4)
/* 0ABAD4 800B1074 280000AA */  cmplwi  r0, 0xaa
/* 0ABAD8 800B1078 41800010 */  blt     lbl_800B1088
/* 0ABADC 800B107C A0040000 */  lhz     r0, 0(r4)
/* 0ABAE0 800B1080 60000020 */  ori     r0, r0, 0x20
/* 0ABAE4 800B1084 B0040000 */  sth     r0, 0(r4)
lbl_800B1088:
/* 0ABAE8 800B1088 88640002 */  lbz     r3, 2(r4)
/* 0ABAEC 800B108C 3803FF80 */  addi    r0, r3, -128
/* 0ABAF0 800B1090 98040002 */  stb     r0, 2(r4)
/* 0ABAF4 800B1094 88640003 */  lbz     r3, 3(r4)
/* 0ABAF8 800B1098 3803FF80 */  addi    r0, r3, -128
/* 0ABAFC 800B109C 98040003 */  stb     r0, 3(r4)
/* 0ABB00 800B10A0 88640004 */  lbz     r3, 4(r4)
/* 0ABB04 800B10A4 3803FF80 */  addi    r0, r3, -128
/* 0ABB08 800B10A8 98040004 */  stb     r0, 4(r4)
/* 0ABB0C 800B10AC 88640005 */  lbz     r3, 5(r4)
/* 0ABB10 800B10B0 3803FF80 */  addi    r0, r3, -128
/* 0ABB14 800B10B4 98040005 */  stb     r0, 5(r4)
/* 0ABB18 800B10B8 4E800020 */  blr     

SPEC1_MakeStatus:
/* 0ABB1C 800B10BC 38600000 */  li      r3, 0
/* 0ABB20 800B10C0 B0640000 */  sth     r3, 0(r4)
/* 0ABB24 800B10C4 80050000 */  lwz     r0, 0(r5)
/* 0ABB28 800B10C8 54008631 */  rlwinm. r0, r0, 0x10, 0x18, 0x18
/* 0ABB2C 800B10CC 41820008 */  beq     lbl_800B10D4
/* 0ABB30 800B10D0 38600100 */  li      r3, 0x100
lbl_800B10D4:
/* 0ABB34 800B10D4 A0040000 */  lhz     r0, 0(r4)
/* 0ABB38 800B10D8 7C001B78 */  or      r0, r0, r3
/* 0ABB3C 800B10DC B0040000 */  sth     r0, 0(r4)
/* 0ABB40 800B10E0 80050000 */  lwz     r0, 0(r5)
/* 0ABB44 800B10E4 540085EF */  rlwinm. r0, r0, 0x10, 0x17, 0x17
/* 0ABB48 800B10E8 4182000C */  beq     lbl_800B10F4
/* 0ABB4C 800B10EC 38600200 */  li      r3, 0x200
/* 0ABB50 800B10F0 48000008 */  b       lbl_800B10F8
lbl_800B10F4:
/* 0ABB54 800B10F4 38600000 */  li      r3, 0
lbl_800B10F8:
/* 0ABB58 800B10F8 A0040000 */  lhz     r0, 0(r4)
/* 0ABB5C 800B10FC 7C001B78 */  or      r0, r0, r3
/* 0ABB60 800B1100 B0040000 */  sth     r0, 0(r4)
/* 0ABB64 800B1104 80050000 */  lwz     r0, 0(r5)
/* 0ABB68 800B1108 540086B5 */  rlwinm. r0, r0, 0x10, 0x1a, 0x1a
/* 0ABB6C 800B110C 4182000C */  beq     lbl_800B1118
/* 0ABB70 800B1110 38600400 */  li      r3, 0x400
/* 0ABB74 800B1114 48000008 */  b       lbl_800B111C
lbl_800B1118:
/* 0ABB78 800B1118 38600000 */  li      r3, 0
lbl_800B111C:
/* 0ABB7C 800B111C A0040000 */  lhz     r0, 0(r4)
/* 0ABB80 800B1120 7C001B78 */  or      r0, r0, r3
/* 0ABB84 800B1124 B0040000 */  sth     r0, 0(r4)
/* 0ABB88 800B1128 80050000 */  lwz     r0, 0(r5)
/* 0ABB8C 800B112C 540086F7 */  rlwinm. r0, r0, 0x10, 0x1b, 0x1b
/* 0ABB90 800B1130 4182000C */  beq     lbl_800B113C
/* 0ABB94 800B1134 38600800 */  li      r3, 0x800
/* 0ABB98 800B1138 48000008 */  b       lbl_800B1140
lbl_800B113C:
/* 0ABB9C 800B113C 38600000 */  li      r3, 0
lbl_800B1140:
/* 0ABBA0 800B1140 A0040000 */  lhz     r0, 0(r4)
/* 0ABBA4 800B1144 7C001B78 */  or      r0, r0, r3
/* 0ABBA8 800B1148 B0040000 */  sth     r0, 0(r4)
/* 0ABBAC 800B114C 80050000 */  lwz     r0, 0(r5)
/* 0ABBB0 800B1150 540085AD */  rlwinm. r0, r0, 0x10, 0x16, 0x16
/* 0ABBB4 800B1154 4182000C */  beq     lbl_800B1160
/* 0ABBB8 800B1158 38C01000 */  li      r6, 0x1000
/* 0ABBBC 800B115C 48000008 */  b       lbl_800B1164
lbl_800B1160:
/* 0ABBC0 800B1160 38C00000 */  li      r6, 0
lbl_800B1164:
/* 0ABBC4 800B1164 A0640000 */  lhz     r3, 0(r4)
/* 0ABBC8 800B1168 38000000 */  li      r0, 0
/* 0ABBCC 800B116C 7C633378 */  or      r3, r3, r6
/* 0ABBD0 800B1170 B0640000 */  sth     r3, 0(r4)
/* 0ABBD4 800B1174 80650004 */  lwz     r3, 4(r5)
/* 0ABBD8 800B1178 5463843E */  srwi    r3, r3, 0x10
/* 0ABBDC 800B117C 7C630774 */  extsb   r3, r3
/* 0ABBE0 800B1180 98640002 */  stb     r3, 2(r4)
/* 0ABBE4 800B1184 80650004 */  lwz     r3, 4(r5)
/* 0ABBE8 800B1188 5463463E */  srwi    r3, r3, 0x18
/* 0ABBEC 800B118C 7C630774 */  extsb   r3, r3
/* 0ABBF0 800B1190 98640003 */  stb     r3, 3(r4)
/* 0ABBF4 800B1194 80650004 */  lwz     r3, 4(r5)
/* 0ABBF8 800B1198 7C630774 */  extsb   r3, r3
/* 0ABBFC 800B119C 98640004 */  stb     r3, 4(r4)
/* 0ABC00 800B11A0 80650004 */  lwz     r3, 4(r5)
/* 0ABC04 800B11A4 5463C23E */  srwi    r3, r3, 8
/* 0ABC08 800B11A8 7C630774 */  extsb   r3, r3
/* 0ABC0C 800B11AC 98640005 */  stb     r3, 5(r4)
/* 0ABC10 800B11B0 80650000 */  lwz     r3, 0(r5)
/* 0ABC14 800B11B4 5463C63E */  rlwinm  r3, r3, 0x18, 0x18, 0x1f
/* 0ABC18 800B11B8 98640006 */  stb     r3, 6(r4)
/* 0ABC1C 800B11BC 80650000 */  lwz     r3, 0(r5)
/* 0ABC20 800B11C0 98640007 */  stb     r3, 7(r4)
/* 0ABC24 800B11C4 98040008 */  stb     r0, 8(r4)
/* 0ABC28 800B11C8 98040009 */  stb     r0, 9(r4)
/* 0ABC2C 800B11CC 88040006 */  lbz     r0, 6(r4)
/* 0ABC30 800B11D0 280000AA */  cmplwi  r0, 0xaa
/* 0ABC34 800B11D4 41800010 */  blt     lbl_800B11E4
/* 0ABC38 800B11D8 A0040000 */  lhz     r0, 0(r4)
/* 0ABC3C 800B11DC 60000040 */  ori     r0, r0, 0x40
/* 0ABC40 800B11E0 B0040000 */  sth     r0, 0(r4)
lbl_800B11E4:
/* 0ABC44 800B11E4 88040007 */  lbz     r0, 7(r4)
/* 0ABC48 800B11E8 280000AA */  cmplwi  r0, 0xaa
/* 0ABC4C 800B11EC 41800010 */  blt     lbl_800B11FC
/* 0ABC50 800B11F0 A0040000 */  lhz     r0, 0(r4)
/* 0ABC54 800B11F4 60000020 */  ori     r0, r0, 0x20
/* 0ABC58 800B11F8 B0040000 */  sth     r0, 0(r4)
lbl_800B11FC:
/* 0ABC5C 800B11FC 88640002 */  lbz     r3, 2(r4)
/* 0ABC60 800B1200 3803FF80 */  addi    r0, r3, -128
/* 0ABC64 800B1204 98040002 */  stb     r0, 2(r4)
/* 0ABC68 800B1208 88640003 */  lbz     r3, 3(r4)
/* 0ABC6C 800B120C 3803FF80 */  addi    r0, r3, -128
/* 0ABC70 800B1210 98040003 */  stb     r0, 3(r4)
/* 0ABC74 800B1214 88640004 */  lbz     r3, 4(r4)
/* 0ABC78 800B1218 3803FF80 */  addi    r0, r3, -128
/* 0ABC7C 800B121C 98040004 */  stb     r0, 4(r4)
/* 0ABC80 800B1220 88640005 */  lbz     r3, 5(r4)
/* 0ABC84 800B1224 3803FF80 */  addi    r0, r3, -128
/* 0ABC88 800B1228 98040005 */  stb     r0, 5(r4)
/* 0ABC8C 800B122C 4E800020 */  blr     

SPEC2_MakeStatus:
/* 0ABC90 800B1230 80050000 */  lwz     r0, 0(r5)
/* 0ABC94 800B1234 540084BE */  rlwinm  r0, r0, 0x10, 0x12, 0x1f
/* 0ABC98 800B1238 B0040000 */  sth     r0, 0(r4)
/* 0ABC9C 800B123C 80050000 */  lwz     r0, 0(r5)
/* 0ABCA0 800B1240 5400C23E */  srwi    r0, r0, 8
/* 0ABCA4 800B1244 7C000774 */  extsb   r0, r0
/* 0ABCA8 800B1248 98040002 */  stb     r0, 2(r4)
/* 0ABCAC 800B124C 80050000 */  lwz     r0, 0(r5)
/* 0ABCB0 800B1250 7C000774 */  extsb   r0, r0
/* 0ABCB4 800B1254 98040003 */  stb     r0, 3(r4)
/* 0ABCB8 800B1258 800D87F4 */  lwz     r0, AnalogMode@sda21(r13)
/* 0ABCBC 800B125C 5400056E */  rlwinm  r0, r0, 0, 0x15, 0x17
/* 0ABCC0 800B1260 2C000400 */  cmpwi   r0, 0x400
/* 0ABCC4 800B1264 41820198 */  beq     lbl_800B13FC
/* 0ABCC8 800B1268 40800034 */  bge     lbl_800B129C
/* 0ABCCC 800B126C 2C000200 */  cmpwi   r0, 0x200
/* 0ABCD0 800B1270 418200F8 */  beq     lbl_800B1368
/* 0ABCD4 800B1274 4080001C */  bge     lbl_800B1290
/* 0ABCD8 800B1278 2C000100 */  cmpwi   r0, 0x100
/* 0ABCDC 800B127C 41820098 */  beq     lbl_800B1314
/* 0ABCE0 800B1280 408001BC */  bge     lbl_800B143C
/* 0ABCE4 800B1284 2C000000 */  cmpwi   r0, 0
/* 0ABCE8 800B1288 41820038 */  beq     lbl_800B12C0
/* 0ABCEC 800B128C 480001B0 */  b       lbl_800B143C
lbl_800B1290:
/* 0ABCF0 800B1290 2C000300 */  cmpwi   r0, 0x300
/* 0ABCF4 800B1294 41820124 */  beq     lbl_800B13B8
/* 0ABCF8 800B1298 480001A4 */  b       lbl_800B143C
lbl_800B129C:
/* 0ABCFC 800B129C 2C000600 */  cmpwi   r0, 0x600
/* 0ABD00 800B12A0 41820020 */  beq     lbl_800B12C0
/* 0ABD04 800B12A4 40800010 */  bge     lbl_800B12B4
/* 0ABD08 800B12A8 2C000500 */  cmpwi   r0, 0x500
/* 0ABD0C 800B12AC 41820014 */  beq     lbl_800B12C0
/* 0ABD10 800B12B0 4800018C */  b       lbl_800B143C
lbl_800B12B4:
/* 0ABD14 800B12B4 2C000700 */  cmpwi   r0, 0x700
/* 0ABD18 800B12B8 41820008 */  beq     lbl_800B12C0
/* 0ABD1C 800B12BC 48000180 */  b       lbl_800B143C
lbl_800B12C0:
/* 0ABD20 800B12C0 80050004 */  lwz     r0, 4(r5)
/* 0ABD24 800B12C4 5400463E */  srwi    r0, r0, 0x18
/* 0ABD28 800B12C8 7C000774 */  extsb   r0, r0
/* 0ABD2C 800B12CC 98040004 */  stb     r0, 4(r4)
/* 0ABD30 800B12D0 80050004 */  lwz     r0, 4(r5)
/* 0ABD34 800B12D4 5400843E */  srwi    r0, r0, 0x10
/* 0ABD38 800B12D8 7C000774 */  extsb   r0, r0
/* 0ABD3C 800B12DC 98040005 */  stb     r0, 5(r4)
/* 0ABD40 800B12E0 80050004 */  lwz     r0, 4(r5)
/* 0ABD44 800B12E4 5400C636 */  rlwinm  r0, r0, 0x18, 0x18, 0x1b
/* 0ABD48 800B12E8 98040006 */  stb     r0, 6(r4)
/* 0ABD4C 800B12EC 80050004 */  lwz     r0, 4(r5)
/* 0ABD50 800B12F0 5400E636 */  rlwinm  r0, r0, 0x1c, 0x18, 0x1b
/* 0ABD54 800B12F4 98040007 */  stb     r0, 7(r4)
/* 0ABD58 800B12F8 80050004 */  lwz     r0, 4(r5)
/* 0ABD5C 800B12FC 54000636 */  rlwinm  r0, r0, 0, 0x18, 0x1b
/* 0ABD60 800B1300 98040008 */  stb     r0, 8(r4)
/* 0ABD64 800B1304 80050004 */  lwz     r0, 4(r5)
/* 0ABD68 800B1308 54002636 */  rlwinm  r0, r0, 4, 0x18, 0x1b
/* 0ABD6C 800B130C 98040009 */  stb     r0, 9(r4)
/* 0ABD70 800B1310 4800012C */  b       lbl_800B143C
lbl_800B1314:
/* 0ABD74 800B1314 80050004 */  lwz     r0, 4(r5)
/* 0ABD78 800B1318 54004636 */  rlwinm  r0, r0, 8, 0x18, 0x1b
/* 0ABD7C 800B131C 7C000774 */  extsb   r0, r0
/* 0ABD80 800B1320 98040004 */  stb     r0, 4(r4)
/* 0ABD84 800B1324 80050004 */  lwz     r0, 4(r5)
/* 0ABD88 800B1328 54006636 */  rlwinm  r0, r0, 0xc, 0x18, 0x1b
/* 0ABD8C 800B132C 7C000774 */  extsb   r0, r0
/* 0ABD90 800B1330 98040005 */  stb     r0, 5(r4)
/* 0ABD94 800B1334 80050004 */  lwz     r0, 4(r5)
/* 0ABD98 800B1338 5400863E */  rlwinm  r0, r0, 0x10, 0x18, 0x1f
/* 0ABD9C 800B133C 98040006 */  stb     r0, 6(r4)
/* 0ABDA0 800B1340 80050004 */  lwz     r0, 4(r5)
/* 0ABDA4 800B1344 5400C63E */  rlwinm  r0, r0, 0x18, 0x18, 0x1f
/* 0ABDA8 800B1348 98040007 */  stb     r0, 7(r4)
/* 0ABDAC 800B134C 80050004 */  lwz     r0, 4(r5)
/* 0ABDB0 800B1350 54000636 */  rlwinm  r0, r0, 0, 0x18, 0x1b
/* 0ABDB4 800B1354 98040008 */  stb     r0, 8(r4)
/* 0ABDB8 800B1358 80050004 */  lwz     r0, 4(r5)
/* 0ABDBC 800B135C 54002636 */  rlwinm  r0, r0, 4, 0x18, 0x1b
/* 0ABDC0 800B1360 98040009 */  stb     r0, 9(r4)
/* 0ABDC4 800B1364 480000D8 */  b       lbl_800B143C
lbl_800B1368:
/* 0ABDC8 800B1368 80050004 */  lwz     r0, 4(r5)
/* 0ABDCC 800B136C 54004636 */  rlwinm  r0, r0, 8, 0x18, 0x1b
/* 0ABDD0 800B1370 7C000774 */  extsb   r0, r0
/* 0ABDD4 800B1374 98040004 */  stb     r0, 4(r4)
/* 0ABDD8 800B1378 80050004 */  lwz     r0, 4(r5)
/* 0ABDDC 800B137C 54006636 */  rlwinm  r0, r0, 0xc, 0x18, 0x1b
/* 0ABDE0 800B1380 7C000774 */  extsb   r0, r0
/* 0ABDE4 800B1384 98040005 */  stb     r0, 5(r4)
/* 0ABDE8 800B1388 80050004 */  lwz     r0, 4(r5)
/* 0ABDEC 800B138C 54008636 */  rlwinm  r0, r0, 0x10, 0x18, 0x1b
/* 0ABDF0 800B1390 98040006 */  stb     r0, 6(r4)
/* 0ABDF4 800B1394 80050004 */  lwz     r0, 4(r5)
/* 0ABDF8 800B1398 5400A636 */  rlwinm  r0, r0, 0x14, 0x18, 0x1b
/* 0ABDFC 800B139C 98040007 */  stb     r0, 7(r4)
/* 0ABE00 800B13A0 80050004 */  lwz     r0, 4(r5)
/* 0ABE04 800B13A4 5400C63E */  rlwinm  r0, r0, 0x18, 0x18, 0x1f
/* 0ABE08 800B13A8 98040008 */  stb     r0, 8(r4)
/* 0ABE0C 800B13AC 80050004 */  lwz     r0, 4(r5)
/* 0ABE10 800B13B0 98040009 */  stb     r0, 9(r4)
/* 0ABE14 800B13B4 48000088 */  b       lbl_800B143C
lbl_800B13B8:
/* 0ABE18 800B13B8 80C50004 */  lwz     r6, 4(r5)
/* 0ABE1C 800B13BC 38000000 */  li      r0, 0
/* 0ABE20 800B13C0 54C6463E */  srwi    r6, r6, 0x18
/* 0ABE24 800B13C4 7CC60774 */  extsb   r6, r6
/* 0ABE28 800B13C8 98C40004 */  stb     r6, 4(r4)
/* 0ABE2C 800B13CC 80C50004 */  lwz     r6, 4(r5)
/* 0ABE30 800B13D0 54C6843E */  srwi    r6, r6, 0x10
/* 0ABE34 800B13D4 7CC60774 */  extsb   r6, r6
/* 0ABE38 800B13D8 98C40005 */  stb     r6, 5(r4)
/* 0ABE3C 800B13DC 80C50004 */  lwz     r6, 4(r5)
/* 0ABE40 800B13E0 54C6C63E */  rlwinm  r6, r6, 0x18, 0x18, 0x1f
/* 0ABE44 800B13E4 98C40006 */  stb     r6, 6(r4)
/* 0ABE48 800B13E8 80A50004 */  lwz     r5, 4(r5)
/* 0ABE4C 800B13EC 98A40007 */  stb     r5, 7(r4)
/* 0ABE50 800B13F0 98040008 */  stb     r0, 8(r4)
/* 0ABE54 800B13F4 98040009 */  stb     r0, 9(r4)
/* 0ABE58 800B13F8 48000044 */  b       lbl_800B143C
lbl_800B13FC:
/* 0ABE5C 800B13FC 80C50004 */  lwz     r6, 4(r5)
/* 0ABE60 800B1400 38000000 */  li      r0, 0
/* 0ABE64 800B1404 54C6463E */  srwi    r6, r6, 0x18
/* 0ABE68 800B1408 7CC60774 */  extsb   r6, r6
/* 0ABE6C 800B140C 98C40004 */  stb     r6, 4(r4)
/* 0ABE70 800B1410 80C50004 */  lwz     r6, 4(r5)
/* 0ABE74 800B1414 54C6843E */  srwi    r6, r6, 0x10
/* 0ABE78 800B1418 7CC60774 */  extsb   r6, r6
/* 0ABE7C 800B141C 98C40005 */  stb     r6, 5(r4)
/* 0ABE80 800B1420 98040006 */  stb     r0, 6(r4)
/* 0ABE84 800B1424 98040007 */  stb     r0, 7(r4)
/* 0ABE88 800B1428 80050004 */  lwz     r0, 4(r5)
/* 0ABE8C 800B142C 5400C63E */  rlwinm  r0, r0, 0x18, 0x18, 0x1f
/* 0ABE90 800B1430 98040008 */  stb     r0, 8(r4)
/* 0ABE94 800B1434 80050004 */  lwz     r0, 4(r5)
/* 0ABE98 800B1438 98040009 */  stb     r0, 9(r4)
lbl_800B143C:
/* 0ABE9C 800B143C 88E40002 */  lbz     r7, 2(r4)
/* 0ABEA0 800B1440 3CA08013 */  lis     r5, Type@ha
/* 0ABEA4 800B1444 5466103A */  slwi    r6, r3, 2
/* 0ABEA8 800B1448 3807FF80 */  addi    r0, r7, -128
/* 0ABEAC 800B144C 98040002 */  stb     r0, 2(r4)
/* 0ABEB0 800B1450 38052468 */  addi    r0, r5, Type@l
/* 0ABEB4 800B1454 7CA03214 */  add     r5, r0, r6
/* 0ABEB8 800B1458 88C40003 */  lbz     r6, 3(r4)
/* 0ABEBC 800B145C 3806FF80 */  addi    r0, r6, -128
/* 0ABEC0 800B1460 98040003 */  stb     r0, 3(r4)
/* 0ABEC4 800B1464 88C40004 */  lbz     r6, 4(r4)
/* 0ABEC8 800B1468 3806FF80 */  addi    r0, r6, -128
/* 0ABECC 800B146C 98040004 */  stb     r0, 4(r4)
/* 0ABED0 800B1470 88C40005 */  lbz     r6, 5(r4)
/* 0ABED4 800B1474 3806FF80 */  addi    r0, r6, -128
/* 0ABED8 800B1478 98040005 */  stb     r0, 5(r4)
/* 0ABEDC 800B147C 80050000 */  lwz     r0, 0(r5)
/* 0ABEE0 800B1480 5405001E */  rlwinm  r5, r0, 0, 0, 0xf
/* 0ABEE4 800B1484 3C05F700 */  addis   r0, r5, 0xf700
/* 0ABEE8 800B1488 28000000 */  cmplwi  r0, 0
/* 0ABEEC 800B148C 40820044 */  bne     lbl_800B14D0
/* 0ABEF0 800B1490 A0040000 */  lhz     r0, 0(r4)
/* 0ABEF4 800B1494 54000630 */  rlwinm  r0, r0, 0, 0x18, 0x18
/* 0ABEF8 800B1498 68000080 */  xori    r0, r0, 0x80
/* 0ABEFC 800B149C 2C000000 */  cmpwi   r0, 0
/* 0ABF00 800B14A0 41820030 */  beq     lbl_800B14D0
/* 0ABF04 800B14A4 3C008000 */  lis     r0, 0x8000
/* 0ABF08 800B14A8 80AD8CB4 */  lwz     r5, BarrelBits@sda21(r13)
/* 0ABF0C 800B14AC 7C001C30 */  srw     r0, r0, r3
/* 0ABF10 800B14B0 7CA00378 */  or      r0, r5, r0
/* 0ABF14 800B14B4 900D8CB4 */  stw     r0, BarrelBits@sda21(r13)
/* 0ABF18 800B14B8 38000000 */  li      r0, 0
/* 0ABF1C 800B14BC 98040002 */  stb     r0, 2(r4)
/* 0ABF20 800B14C0 98040003 */  stb     r0, 3(r4)
/* 0ABF24 800B14C4 98040004 */  stb     r0, 4(r4)
/* 0ABF28 800B14C8 98040005 */  stb     r0, 5(r4)
/* 0ABF2C 800B14CC 4E800020 */  blr     
lbl_800B14D0:
/* 0ABF30 800B14D0 3C008000 */  lis     r0, 0x8000
/* 0ABF34 800B14D4 80AD8CB4 */  lwz     r5, BarrelBits@sda21(r13)
/* 0ABF38 800B14D8 7C001C30 */  srw     r0, r0, r3
/* 0ABF3C 800B14DC 7CA00078 */  andc    r0, r5, r0
/* 0ABF40 800B14E0 900D8CB4 */  stw     r0, BarrelBits@sda21(r13)
/* 0ABF44 800B14E4 3CA08013 */  lis     r5, Origin@ha
/* 0ABF48 800B14E8 1C63000C */  mulli   r3, r3, 0xc
/* 0ABF4C 800B14EC 88C40002 */  lbz     r6, 2(r4)
/* 0ABF50 800B14F0 38052478 */  addi    r0, r5, Origin@l
/* 0ABF54 800B14F4 7C601A14 */  add     r3, r0, r3
/* 0ABF58 800B14F8 88E30002 */  lbz     r7, 2(r3)
/* 0ABF5C 800B14FC 7CE00775 */  extsb.  r0, r7
/* 0ABF60 800B1500 40810024 */  ble     lbl_800B1524
/* 0ABF64 800B1504 7CE50774 */  extsb   r5, r7
/* 0ABF68 800B1508 3805FF80 */  addi    r0, r5, -128
/* 0ABF6C 800B150C 7C050774 */  extsb   r5, r0
/* 0ABF70 800B1510 7CC00774 */  extsb   r0, r6
/* 0ABF74 800B1514 7C002800 */  cmpw    r0, r5
/* 0ABF78 800B1518 40800030 */  bge     lbl_800B1548
/* 0ABF7C 800B151C 7CA62B78 */  mr      r6, r5
/* 0ABF80 800B1520 48000028 */  b       lbl_800B1548
lbl_800B1524:
/* 0ABF84 800B1524 7CE00775 */  extsb.  r0, r7
/* 0ABF88 800B1528 40800020 */  bge     lbl_800B1548
/* 0ABF8C 800B152C 7CE50774 */  extsb   r5, r7
/* 0ABF90 800B1530 3805007F */  addi    r0, r5, 0x7f
/* 0ABF94 800B1534 7C050774 */  extsb   r5, r0
/* 0ABF98 800B1538 7CC00774 */  extsb   r0, r6
/* 0ABF9C 800B153C 7C050000 */  cmpw    r5, r0
/* 0ABFA0 800B1540 40800008 */  bge     lbl_800B1548
/* 0ABFA4 800B1544 7CA62B78 */  mr      r6, r5
lbl_800B1548:
/* 0ABFA8 800B1548 7CC73050 */  subf    r6, r7, r6
/* 0ABFAC 800B154C 98C40002 */  stb     r6, 2(r4)
/* 0ABFB0 800B1550 88E30003 */  lbz     r7, 3(r3)
/* 0ABFB4 800B1554 88C40003 */  lbz     r6, 3(r4)
/* 0ABFB8 800B1558 7CE00775 */  extsb.  r0, r7
/* 0ABFBC 800B155C 40810024 */  ble     lbl_800B1580
/* 0ABFC0 800B1560 7CE50774 */  extsb   r5, r7
/* 0ABFC4 800B1564 3805FF80 */  addi    r0, r5, -128
/* 0ABFC8 800B1568 7C050774 */  extsb   r5, r0
/* 0ABFCC 800B156C 7CC00774 */  extsb   r0, r6
/* 0ABFD0 800B1570 7C002800 */  cmpw    r0, r5
/* 0ABFD4 800B1574 40800030 */  bge     lbl_800B15A4
/* 0ABFD8 800B1578 7CA62B78 */  mr      r6, r5
/* 0ABFDC 800B157C 48000028 */  b       lbl_800B15A4
lbl_800B1580:
/* 0ABFE0 800B1580 7CE00775 */  extsb.  r0, r7
/* 0ABFE4 800B1584 40800020 */  bge     lbl_800B15A4
/* 0ABFE8 800B1588 7CE50774 */  extsb   r5, r7
/* 0ABFEC 800B158C 3805007F */  addi    r0, r5, 0x7f
/* 0ABFF0 800B1590 7C050774 */  extsb   r5, r0
/* 0ABFF4 800B1594 7CC00774 */  extsb   r0, r6
/* 0ABFF8 800B1598 7C050000 */  cmpw    r5, r0
/* 0ABFFC 800B159C 40800008 */  bge     lbl_800B15A4
/* 0AC000 800B15A0 7CA62B78 */  mr      r6, r5
lbl_800B15A4:
/* 0AC004 800B15A4 7CC73050 */  subf    r6, r7, r6
/* 0AC008 800B15A8 98C40003 */  stb     r6, 3(r4)
/* 0AC00C 800B15AC 88E30004 */  lbz     r7, 4(r3)
/* 0AC010 800B15B0 88C40004 */  lbz     r6, 4(r4)
/* 0AC014 800B15B4 7CE00775 */  extsb.  r0, r7
/* 0AC018 800B15B8 40810024 */  ble     lbl_800B15DC
/* 0AC01C 800B15BC 7CE50774 */  extsb   r5, r7
/* 0AC020 800B15C0 3805FF80 */  addi    r0, r5, -128
/* 0AC024 800B15C4 7C050774 */  extsb   r5, r0
/* 0AC028 800B15C8 7CC00774 */  extsb   r0, r6
/* 0AC02C 800B15CC 7C002800 */  cmpw    r0, r5
/* 0AC030 800B15D0 40800030 */  bge     lbl_800B1600
/* 0AC034 800B15D4 7CA62B78 */  mr      r6, r5
/* 0AC038 800B15D8 48000028 */  b       lbl_800B1600
lbl_800B15DC:
/* 0AC03C 800B15DC 7CE00775 */  extsb.  r0, r7
/* 0AC040 800B15E0 40800020 */  bge     lbl_800B1600
/* 0AC044 800B15E4 7CE50774 */  extsb   r5, r7
/* 0AC048 800B15E8 3805007F */  addi    r0, r5, 0x7f
/* 0AC04C 800B15EC 7C050774 */  extsb   r5, r0
/* 0AC050 800B15F0 7CC00774 */  extsb   r0, r6
/* 0AC054 800B15F4 7C050000 */  cmpw    r5, r0
/* 0AC058 800B15F8 40800008 */  bge     lbl_800B1600
/* 0AC05C 800B15FC 7CA62B78 */  mr      r6, r5
lbl_800B1600:
/* 0AC060 800B1600 7CC73050 */  subf    r6, r7, r6
/* 0AC064 800B1604 98C40004 */  stb     r6, 4(r4)
/* 0AC068 800B1608 88E30005 */  lbz     r7, 5(r3)
/* 0AC06C 800B160C 88C40005 */  lbz     r6, 5(r4)
/* 0AC070 800B1610 7CE00775 */  extsb.  r0, r7
/* 0AC074 800B1614 40810024 */  ble     lbl_800B1638
/* 0AC078 800B1618 7CE50774 */  extsb   r5, r7
/* 0AC07C 800B161C 3805FF80 */  addi    r0, r5, -128
/* 0AC080 800B1620 7C050774 */  extsb   r5, r0
/* 0AC084 800B1624 7CC00774 */  extsb   r0, r6
/* 0AC088 800B1628 7C002800 */  cmpw    r0, r5
/* 0AC08C 800B162C 40800030 */  bge     lbl_800B165C
/* 0AC090 800B1630 7CA62B78 */  mr      r6, r5
/* 0AC094 800B1634 48000028 */  b       lbl_800B165C
lbl_800B1638:
/* 0AC098 800B1638 7CE00775 */  extsb.  r0, r7
/* 0AC09C 800B163C 40800020 */  bge     lbl_800B165C
/* 0AC0A0 800B1640 7CE50774 */  extsb   r5, r7
/* 0AC0A4 800B1644 3805007F */  addi    r0, r5, 0x7f
/* 0AC0A8 800B1648 7C050774 */  extsb   r5, r0
/* 0AC0AC 800B164C 7CC00774 */  extsb   r0, r6
/* 0AC0B0 800B1650 7C050000 */  cmpw    r5, r0
/* 0AC0B4 800B1654 40800008 */  bge     lbl_800B165C
/* 0AC0B8 800B1658 7CA62B78 */  mr      r6, r5
lbl_800B165C:
/* 0AC0BC 800B165C 7CC73050 */  subf    r6, r7, r6
/* 0AC0C0 800B1660 98C40005 */  stb     r6, 5(r4)
/* 0AC0C4 800B1664 88030006 */  lbz     r0, 6(r3)
/* 0AC0C8 800B1668 88A40006 */  lbz     r5, 6(r4)
/* 0AC0CC 800B166C 7C050040 */  cmplw   r5, r0
/* 0AC0D0 800B1670 40800008 */  bge     lbl_800B1678
/* 0AC0D4 800B1674 7C050378 */  mr      r5, r0
lbl_800B1678:
/* 0AC0D8 800B1678 7CA02850 */  subf    r5, r0, r5
/* 0AC0DC 800B167C 98A40006 */  stb     r5, 6(r4)
/* 0AC0E0 800B1680 88030007 */  lbz     r0, 7(r3)
/* 0AC0E4 800B1684 88640007 */  lbz     r3, 7(r4)
/* 0AC0E8 800B1688 7C030040 */  cmplw   r3, r0
/* 0AC0EC 800B168C 40800008 */  bge     lbl_800B1694
/* 0AC0F0 800B1690 7C030378 */  mr      r3, r0
lbl_800B1694:
/* 0AC0F4 800B1694 7C601850 */  subf    r3, r0, r3
/* 0AC0F8 800B1698 98640007 */  stb     r3, 7(r4)
/* 0AC0FC 800B169C 4E800020 */  blr     

OnReset:
/* 0AC100 800B16A0 7C0802A6 */  mflr    r0
/* 0AC104 800B16A4 90010004 */  stw     r0, 4(r1)
/* 0AC108 800B16A8 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0AC10C 800B16AC 93E1001C */  stw     r31, 0x1c(r1)
/* 0AC110 800B16B0 3BE30000 */  addi    r31, r3, 0
/* 0AC114 800B16B4 800D8CB8 */  lwz     r0, SamplingCallback@sda21(r13)
/* 0AC118 800B16B8 28000000 */  cmplwi  r0, 0
/* 0AC11C 800B16BC 4182000C */  beq     lbl_800B16C8
/* 0AC120 800B16C0 38600000 */  li      r3, 0
/* 0AC124 800B16C4 480000F9 */  bl      PADSetSamplingCallback
lbl_800B16C8:
/* 0AC128 800B16C8 2C1F0000 */  cmpwi   r31, 0
/* 0AC12C 800B16CC 40820070 */  bne     lbl_800B173C
/* 0AC130 800B16D0 800D8CA0 */  lwz     r0, ResettingBits@sda21(r13)
/* 0AC134 800B16D4 3BE00000 */  li      r31, 0
/* 0AC138 800B16D8 387F0000 */  addi    r3, r31, 0
/* 0AC13C 800B16DC 28000000 */  cmplwi  r0, 0
/* 0AC140 800B16E0 40820014 */  bne     lbl_800B16F4
/* 0AC144 800B16E4 800D87EC */  lwz     r0, ResettingChan@sda21(r13)
/* 0AC148 800B16E8 2C000020 */  cmpwi   r0, 0x20
/* 0AC14C 800B16EC 40820008 */  bne     lbl_800B16F4
/* 0AC150 800B16F0 38600001 */  li      r3, 1
lbl_800B16F4:
/* 0AC154 800B16F4 2C030000 */  cmpwi   r3, 0
/* 0AC158 800B16F8 41820014 */  beq     lbl_800B170C
/* 0AC15C 800B16FC 4BFF3021 */  bl      SIBusy
/* 0AC160 800B1700 2C030000 */  cmpwi   r3, 0
/* 0AC164 800B1704 40820008 */  bne     lbl_800B170C
/* 0AC168 800B1708 3BE00001 */  li      r31, 1
lbl_800B170C:
/* 0AC16C 800B170C 800D8CBC */  lwz     r0, recalibrated$388@sda21(r13)
/* 0AC170 800B1710 2C000000 */  cmpwi   r0, 0
/* 0AC174 800B1714 40820020 */  bne     lbl_800B1734
/* 0AC178 800B1718 2C1F0000 */  cmpwi   r31, 0
/* 0AC17C 800B171C 41820018 */  beq     lbl_800B1734
/* 0AC180 800B1720 3C60F000 */  lis     r3, 0xf000
/* 0AC184 800B1724 4BFFF1A9 */  bl      PADRecalibrate
/* 0AC188 800B1728 906D8CBC */  stw     r3, recalibrated$388@sda21(r13)
/* 0AC18C 800B172C 38600000 */  li      r3, 0
/* 0AC190 800B1730 48000018 */  b       lbl_800B1748
lbl_800B1734:
/* 0AC194 800B1734 7FE3FB78 */  mr      r3, r31
/* 0AC198 800B1738 48000010 */  b       lbl_800B1748
lbl_800B173C:
/* 0AC19C 800B173C 38000000 */  li      r0, 0
/* 0AC1A0 800B1740 900D8CBC */  stw     r0, recalibrated$388@sda21(r13)
/* 0AC1A4 800B1744 38600001 */  li      r3, 1
lbl_800B1748:
/* 0AC1A8 800B1748 80010024 */  lwz     r0, 0x24(r1)
/* 0AC1AC 800B174C 83E1001C */  lwz     r31, 0x1c(r1)
/* 0AC1B0 800B1750 38210020 */  addi    r1, r1, 0x20
/* 0AC1B4 800B1754 7C0803A6 */  mtlr    r0
/* 0AC1B8 800B1758 4E800020 */  blr     

SamplingHandler:
/* 0AC1BC 800B175C 7C0802A6 */  mflr    r0
/* 0AC1C0 800B1760 90010004 */  stw     r0, 4(r1)
/* 0AC1C4 800B1764 9421FD20 */  stwu    r1, -0x2e0(r1)
/* 0AC1C8 800B1768 93E102DC */  stw     r31, 0x2dc(r1)
/* 0AC1CC 800B176C 3BE40000 */  addi    r31, r4, 0
/* 0AC1D0 800B1770 800D8CB8 */  lwz     r0, SamplingCallback@sda21(r13)
/* 0AC1D4 800B1774 28000000 */  cmplwi  r0, 0
/* 0AC1D8 800B1778 41820030 */  beq     lbl_800B17A8
/* 0AC1DC 800B177C 38610010 */  addi    r3, r1, 0x10
/* 0AC1E0 800B1780 4BFECA25 */  bl      OSClearContext
/* 0AC1E4 800B1784 38610010 */  addi    r3, r1, 0x10
/* 0AC1E8 800B1788 4BFEC855 */  bl      OSSetCurrentContext
/* 0AC1EC 800B178C 818D8CB8 */  lwz     r12, SamplingCallback@sda21(r13)
/* 0AC1F0 800B1790 7D8803A6 */  mtlr    r12
/* 0AC1F4 800B1794 4E800021 */  blrl    
/* 0AC1F8 800B1798 38610010 */  addi    r3, r1, 0x10
/* 0AC1FC 800B179C 4BFECA09 */  bl      OSClearContext
/* 0AC200 800B17A0 7FE3FB78 */  mr      r3, r31
/* 0AC204 800B17A4 4BFEC839 */  bl      OSSetCurrentContext
lbl_800B17A8:
/* 0AC208 800B17A8 800102E4 */  lwz     r0, 0x2e4(r1)
/* 0AC20C 800B17AC 83E102DC */  lwz     r31, 0x2dc(r1)
/* 0AC210 800B17B0 382102E0 */  addi    r1, r1, 0x2e0
/* 0AC214 800B17B4 7C0803A6 */  mtlr    r0
/* 0AC218 800B17B8 4E800020 */  blr     

glabel PADSetSamplingCallback
/* 0AC21C 800B17BC 7C0802A6 */  mflr    r0
/* 0AC220 800B17C0 28030000 */  cmplwi  r3, 0
/* 0AC224 800B17C4 90010004 */  stw     r0, 4(r1)
/* 0AC228 800B17C8 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AC22C 800B17CC 93E10014 */  stw     r31, 0x14(r1)
/* 0AC230 800B17D0 83ED8CB8 */  lwz     r31, SamplingCallback@sda21(r13)
/* 0AC234 800B17D4 906D8CB8 */  stw     r3, SamplingCallback@sda21(r13)
/* 0AC238 800B17D8 41820014 */  beq     lbl_800B17EC
/* 0AC23C 800B17DC 3C60800B */  lis     r3, SamplingHandler@ha
/* 0AC240 800B17E0 3863175C */  addi    r3, r3, SamplingHandler@l
/* 0AC244 800B17E4 4BFF366D */  bl      SIRegisterPollingHandler
/* 0AC248 800B17E8 48000010 */  b       lbl_800B17F8
lbl_800B17EC:
/* 0AC24C 800B17EC 3C60800B */  lis     r3, SamplingHandler@ha
/* 0AC250 800B17F0 3863175C */  addi    r3, r3, SamplingHandler@l
/* 0AC254 800B17F4 4BFF3729 */  bl      SIUnregisterPollingHandler
lbl_800B17F8:
/* 0AC258 800B17F8 7FE3FB78 */  mr      r3, r31
/* 0AC25C 800B17FC 8001001C */  lwz     r0, 0x1c(r1)
/* 0AC260 800B1800 83E10014 */  lwz     r31, 0x14(r1)
/* 0AC264 800B1804 38210018 */  addi    r1, r1, 0x18
/* 0AC268 800B1808 7C0803A6 */  mtlr    r0
/* 0AC26C 800B180C 4E800020 */  blr     

glabel __PADDisableRecalibration
/* 0AC270 800B1810 7C0802A6 */  mflr    r0
/* 0AC274 800B1814 90010004 */  stw     r0, 4(r1)
/* 0AC278 800B1818 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AC27C 800B181C 93E10014 */  stw     r31, 0x14(r1)
/* 0AC280 800B1820 93C10010 */  stw     r30, 0x10(r1)
/* 0AC284 800B1824 7C7E1B78 */  mr      r30, r3
/* 0AC288 800B1828 4BFED4D5 */  bl      OSDisableInterrupts
/* 0AC28C 800B182C 3C808000 */  lis     r4, 0x8000
/* 0AC290 800B1830 880430E3 */  lbz     r0, 0x30e3(r4)
/* 0AC294 800B1834 54000673 */  rlwinm. r0, r0, 0, 0x19, 0x19
/* 0AC298 800B1838 4182000C */  beq     lbl_800B1844
/* 0AC29C 800B183C 3BE00001 */  li      r31, 1
/* 0AC2A0 800B1840 48000008 */  b       lbl_800B1848
lbl_800B1844:
/* 0AC2A4 800B1844 3BE00000 */  li      r31, 0
lbl_800B1848:
/* 0AC2A8 800B1848 3C808000 */  lis     r4, 0x8000
/* 0AC2AC 800B184C 880430E3 */  lbz     r0, 0x30e3(r4)
/* 0AC2B0 800B1850 2C1E0000 */  cmpwi   r30, 0
/* 0AC2B4 800B1854 540006B0 */  rlwinm  r0, r0, 0, 0x1a, 0x18
/* 0AC2B8 800B1858 980430E3 */  stb     r0, 0x30e3(r4)
/* 0AC2BC 800B185C 41820010 */  beq     lbl_800B186C
/* 0AC2C0 800B1860 880430E3 */  lbz     r0, 0x30e3(r4)
/* 0AC2C4 800B1864 60000040 */  ori     r0, r0, 0x40
/* 0AC2C8 800B1868 980430E3 */  stb     r0, 0x30e3(r4)
lbl_800B186C:
/* 0AC2CC 800B186C 4BFED4B9 */  bl      OSRestoreInterrupts
/* 0AC2D0 800B1870 7FE3FB78 */  mr      r3, r31
/* 0AC2D4 800B1874 8001001C */  lwz     r0, 0x1c(r1)
/* 0AC2D8 800B1878 83E10014 */  lwz     r31, 0x14(r1)
/* 0AC2DC 800B187C 83C10010 */  lwz     r30, 0x10(r1)
/* 0AC2E0 800B1880 38210018 */  addi    r1, r1, 0x18
/* 0AC2E4 800B1884 7C0803A6 */  mtlr    r0
/* 0AC2E8 800B1888 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000EF320 800F22A0 0045 */
D_800F22A0:
    .asciz "<< Dolphin SDK - PAD\trelease build: Aug  6 2003 04:30:02 (0x2301) >>"
    .balign 4

/* 000EF368 800F22E8 0010 */
ResetFunctionInfo:
    .long OnReset, 0x0000007F, 0x00000000, 0x00000000

.section .bss, "wa"

.balign 4

/* 0012F4E8 80132468 0010 */
Type:
    .skip 16

/* 0012F4F8 80132478 0030 */
Origin:
    .skip 48

/* 0012F528 801324A8 0010 */
CmdProbeDevice:
    .skip 16

.section .sdata, "wa"

.balign 8

/* 000F1748 801354C8 0004 */
glabel __PADVersion
    .long D_800F22A0

/* 000F174C 801354CC 0004 */
ResettingChan:
    .long 0x00000020

/* 000F1750 801354D0 0004 */
XPatchBits:
    .long 0xF0000000

/* 000F1754 801354D4 0004 */
AnalogMode:
    .long 0x00000300

/* 000F1758 801354D8 0004 */
Spec:
    .long 0x00000005

/* 000F175C 801354DC 0004 */
MakeStatus:
    .long SPEC2_MakeStatus

/* 000F1760 801354E0 0004 */
CmdReadOrigin:
    .long 0x41000000

/* 000F1764 801354E4 0004 */
CmdCalibrate:
    .long 0x42000000

.section .sbss, "wa"

.balign 8

/* 000F1BF8 80135978 0004 */
Initialized:
    .skip 4

/* 000F1BFC 8013597C 0004 */
EnabledBits:
    .skip 4

/* 000F1C00 80135980 0004 */
ResettingBits:
    .skip 4

/* 000F1C04 80135984 0004 */
RecalibrateBits:
    .skip 4

/* 000F1C08 80135988 0004 */
WaitingBits:
    .skip 4

/* 000F1C0C 8013598C 0004 */
CheckingBits:
    .skip 4

/* 000F1C10 80135990 0004 */
PendingBits:
    .skip 4

/* 000F1C14 80135994 0004 */
BarrelBits:
    .skip 4

/* 000F1C18 80135998 0004 */
SamplingCallback:
    .skip 4

/* 000F1C1C 8013599C 0004 */
recalibrated$388:
    .skip 4

/* 000F1C20 801359A0 0004 */
glabel __PADSpec
    .skip 4
