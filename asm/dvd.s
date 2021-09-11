# dvd.c
.include "macros.inc"

.section .text, "ax"

.balign 4

defaultOptionalCommandChecker:
/* 0AD9D0 800B2F70 4E800020 */  blr     

glabel DVDInit
/* 0AD9D4 800B2F74 7C0802A6 */  mflr    r0
/* 0AD9D8 800B2F78 90010004 */  stw     r0, 4(r1)
/* 0AD9DC 800B2F7C 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0AD9E0 800B2F80 93E1000C */  stw     r31, 0xc(r1)
/* 0AD9E4 800B2F84 800D8D70 */  lwz     r0, DVDInitialized-_SDA_BASE_(r13)
/* 0AD9E8 800B2F88 2C000000 */  cmpwi   r0, 0
/* 0AD9EC 800B2F8C 408200A0 */  bne     lbl_800B302C
/* 0AD9F0 800B2F90 806D8818 */  lwz     r3, __DVDVersion-_SDA_BASE_(r13)
/* 0AD9F4 800B2F94 4BFE96FD */  bl      OSRegisterVersion
/* 0AD9F8 800B2F98 3BE00001 */  li      r31, 1
/* 0AD9FC 800B2F9C 93ED8D70 */  stw     r31, DVDInitialized-_SDA_BASE_(r13)
/* 0ADA00 800B2FA0 4BFFF769 */  bl      __DVDFSInit
/* 0ADA04 800B2FA4 48002701 */  bl      __DVDClearWaitingQueue
/* 0ADA08 800B2FA8 4BFFE8E5 */  bl      __DVDInitWA
/* 0ADA0C 800B2FAC 3C008000 */  lis     r0, 0x8000
/* 0ADA10 800B2FB0 3C60800B */  lis     r3, __DVDInterruptHandler@ha
/* 0ADA14 800B2FB4 900D8D38 */  stw     r0, bootInfo-_SDA_BASE_(r13)
/* 0ADA18 800B2FB8 388318CC */  addi    r4, r3, __DVDInterruptHandler@l
/* 0ADA1C 800B2FBC 900D8D34 */  stw     r0, IDShouldBe-_SDA_BASE_(r13)
/* 0ADA20 800B2FC0 38600015 */  li      r3, 0x15
/* 0ADA24 800B2FC4 4BFEBD85 */  bl      __OSSetInterruptHandler
/* 0ADA28 800B2FC8 38600400 */  li      r3, 0x400
/* 0ADA2C 800B2FCC 4BFEC181 */  bl      __OSUnmaskInterrupts
/* 0ADA30 800B2FD0 386D8D28 */  addi    r3, r13, __DVDThreadQueue-_SDA_BASE_
/* 0ADA34 800B2FD4 4BFEE261 */  bl      OSInitThreadQueue
/* 0ADA38 800B2FD8 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0ADA3C 800B2FDC 3800002A */  li      r0, 0x2a
/* 0ADA40 800B2FE0 90036000 */  stw     r0, (DI_REGS_BASE + DI_DISR)@l(r3)
/* 0ADA44 800B2FE4 38000000 */  li      r0, 0
/* 0ADA48 800B2FE8 90036004 */  stw     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0ADA4C 800B2FEC 806D8D38 */  lwz     r3, bootInfo-_SDA_BASE_(r13)
/* 0ADA50 800B2FF0 38630020 */  addi    r3, r3, 0x20
/* 0ADA54 800B2FF4 80630000 */  lwz     r3, 0(r3)
/* 0ADA58 800B2FF8 3C031AE0 */  addis   r0, r3, 0x1ae0
/* 0ADA5C 800B2FFC 28007C22 */  cmplwi  r0, 0x7c22
/* 0ADA60 800B3000 4082001C */  bne     lbl_800B301C
/* 0ADA64 800B3004 3C60800F */  lis     r3, D_800F24A8@ha
/* 0ADA68 800B3008 4CC63182 */  crclr   6
/* 0ADA6C 800B300C 386324A8 */  addi    r3, r3, D_800F24A8@l
/* 0ADA70 800B3010 4BFEB5E9 */  bl      OSReport
/* 0ADA74 800B3014 48002C21 */  bl      __fstLoad
/* 0ADA78 800B3018 48000014 */  b       lbl_800B302C
lbl_800B301C:
/* 0ADA7C 800B301C 3C03F2EB */  addis   r0, r3, 0xf2eb
/* 0ADA80 800B3020 2800EA5E */  cmplwi  r0, 0xea5e
/* 0ADA84 800B3024 41820008 */  beq     lbl_800B302C
/* 0ADA88 800B3028 93ED8D6C */  stw     r31, FirstTimeInBootrom-_SDA_BASE_(r13)
lbl_800B302C:
/* 0ADA8C 800B302C 80010014 */  lwz     r0, 0x14(r1)
/* 0ADA90 800B3030 83E1000C */  lwz     r31, 0xc(r1)
/* 0ADA94 800B3034 38210010 */  addi    r1, r1, 0x10
/* 0ADA98 800B3038 7C0803A6 */  mtlr    r0
/* 0ADA9C 800B303C 4E800020 */  blr     

stateReadingFST:
/* 0ADAA0 800B3040 7C0802A6 */  mflr    r0
/* 0ADAA4 800B3044 3C60800B */  lis     r3, stateReadingFST@ha
/* 0ADAA8 800B3048 90010004 */  stw     r0, 4(r1)
/* 0ADAAC 800B304C 38033040 */  addi    r0, r3, stateReadingFST@l
/* 0ADAB0 800B3050 3C608013 */  lis     r3, BB2@ha
/* 0ADAB4 800B3054 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0ADAB8 800B3058 386325A0 */  addi    r3, r3, BB2@l
/* 0ADABC 800B305C 93E1000C */  stw     r31, 0xc(r1)
/* 0ADAC0 800B3060 3BE30008 */  addi    r31, r3, 8
/* 0ADAC4 800B3064 900D8D74 */  stw     r0, LastState-_SDA_BASE_(r13)
/* 0ADAC8 800B3068 808D8D38 */  lwz     r4, bootInfo-_SDA_BASE_(r13)
/* 0ADACC 800B306C 801F0000 */  lwz     r0, 0(r31)
/* 0ADAD0 800B3070 8064003C */  lwz     r3, 0x3c(r4)
/* 0ADAD4 800B3074 7C030040 */  cmplw   r3, r0
/* 0ADAD8 800B3078 4080001C */  bge     lbl_800B3094
/* 0ADADC 800B307C 3C60800F */  lis     r3, D_800F24B4@ha
/* 0ADAE0 800B3080 4CC63182 */  crclr   6
/* 0ADAE4 800B3084 38A324B4 */  addi    r5, r3, D_800F24B4@l
/* 0ADAE8 800B3088 386D8824 */  addi    r3, r13, D_80135504-_SDA_BASE_
/* 0ADAEC 800B308C 3880028A */  li      r4, 0x28a
/* 0ADAF0 800B3090 4BFEB5E9 */  bl      OSPanic
lbl_800B3094:
/* 0ADAF4 800B3094 3C608013 */  lis     r3, BB2@ha
/* 0ADAF8 800B3098 80DF0000 */  lwz     r6, 0(r31)
/* 0ADAFC 800B309C 38A325A0 */  addi    r5, r3, BB2@l
/* 0ADB00 800B30A0 80ED8D38 */  lwz     r7, bootInfo-_SDA_BASE_(r13)
/* 0ADB04 800B30A4 3C80800B */  lis     r4, cbForStateReadingFST@ha
/* 0ADB08 800B30A8 80A50004 */  lwz     r5, 4(r5)
/* 0ADB0C 800B30AC 3806001F */  addi    r0, r6, 0x1f
/* 0ADB10 800B30B0 80670038 */  lwz     r3, 0x38(r7)
/* 0ADB14 800B30B4 38C430D4 */  addi    r6, r4, cbForStateReadingFST@l
/* 0ADB18 800B30B8 54040034 */  rlwinm  r4, r0, 0, 0, 0x1a
/* 0ADB1C 800B30BC 4BFFED75 */  bl      DVDLowRead
/* 0ADB20 800B30C0 80010014 */  lwz     r0, 0x14(r1)
/* 0ADB24 800B30C4 83E1000C */  lwz     r31, 0xc(r1)
/* 0ADB28 800B30C8 38210010 */  addi    r1, r1, 0x10
/* 0ADB2C 800B30CC 7C0803A6 */  mtlr    r0
/* 0ADB30 800B30D0 4E800020 */  blr     

cbForStateReadingFST:
/* 0ADB34 800B30D4 7C0802A6 */  mflr    r0
/* 0ADB38 800B30D8 28030010 */  cmplwi  r3, 0x10
/* 0ADB3C 800B30DC 90010004 */  stw     r0, 4(r1)
/* 0ADB40 800B30E0 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0ADB44 800B30E4 93E10014 */  stw     r31, 0x14(r1)
/* 0ADB48 800B30E8 40820018 */  bne     lbl_800B3100
/* 0ADB4C 800B30EC 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0ADB50 800B30F0 3800FFFF */  li      r0, -1
/* 0ADB54 800B30F4 9003000C */  stw     r0, 0xc(r3)
/* 0ADB58 800B30F8 48000115 */  bl      stateTimeout
/* 0ADB5C 800B30FC 48000050 */  b       lbl_800B314C
lbl_800B3100:
/* 0ADB60 800B3100 546007FF */  clrlwi. r0, r3, 0x1f
/* 0ADB64 800B3104 41820044 */  beq     lbl_800B3148
/* 0ADB68 800B3108 3BE00000 */  li      r31, 0
/* 0ADB6C 800B310C 93ED8D64 */  stw     r31, NumInternalRetry-_SDA_BASE_(r13)
/* 0ADB70 800B3110 4BFFF5F9 */  bl      __DVDFSInit
/* 0ADB74 800B3114 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0ADB78 800B3118 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0ADB7C 800B311C 380325E0 */  addi    r0, r3, DummyCommandBlock@l
/* 0ADB80 800B3120 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0ADB84 800B3124 93E4000C */  stw     r31, 0xc(r4)
/* 0ADB88 800B3128 81840028 */  lwz     r12, 0x28(r4)
/* 0ADB8C 800B312C 280C0000 */  cmplwi  r12, 0
/* 0ADB90 800B3130 41820010 */  beq     lbl_800B3140
/* 0ADB94 800B3134 7D8803A6 */  mtlr    r12
/* 0ADB98 800B3138 38600000 */  li      r3, 0
/* 0ADB9C 800B313C 4E800021 */  blrl    
lbl_800B3140:
/* 0ADBA0 800B3140 48000E95 */  bl      stateReady
/* 0ADBA4 800B3144 48000008 */  b       lbl_800B314C
lbl_800B3148:
/* 0ADBA8 800B3148 480000F9 */  bl      stateGettingError
lbl_800B314C:
/* 0ADBAC 800B314C 8001001C */  lwz     r0, 0x1c(r1)
/* 0ADBB0 800B3150 83E10014 */  lwz     r31, 0x14(r1)
/* 0ADBB4 800B3154 38210018 */  addi    r1, r1, 0x18
/* 0ADBB8 800B3158 7C0803A6 */  mtlr    r0
/* 0ADBBC 800B315C 4E800020 */  blr     

cbForStateError:
/* 0ADBC0 800B3160 7C0802A6 */  mflr    r0
/* 0ADBC4 800B3164 28030010 */  cmplwi  r3, 0x10
/* 0ADBC8 800B3168 90010004 */  stw     r0, 4(r1)
/* 0ADBCC 800B316C 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0ADBD0 800B3170 93E10014 */  stw     r31, 0x14(r1)
/* 0ADBD4 800B3174 40820018 */  bne     lbl_800B318C
/* 0ADBD8 800B3178 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0ADBDC 800B317C 3800FFFF */  li      r0, -1
/* 0ADBE0 800B3180 9003000C */  stw     r0, 0xc(r3)
/* 0ADBE4 800B3184 48000089 */  bl      stateTimeout
/* 0ADBE8 800B3188 48000070 */  b       lbl_800B31F8
lbl_800B318C:
/* 0ADBEC 800B318C 480029A1 */  bl      __DVDPrintFatalMessage
/* 0ADBF0 800B3190 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0ADBF4 800B3194 83ED8D30 */  lwz     r31, executing-_SDA_BASE_(r13)
/* 0ADBF8 800B3198 380325E0 */  addi    r0, r3, DummyCommandBlock@l
/* 0ADBFC 800B319C 38600001 */  li      r3, 1
/* 0ADC00 800B31A0 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0ADC04 800B31A4 906D8D48 */  stw     r3, FatalErrorFlag-_SDA_BASE_(r13)
/* 0ADC08 800B31A8 819F0028 */  lwz     r12, 0x28(r31)
/* 0ADC0C 800B31AC 280C0000 */  cmplwi  r12, 0
/* 0ADC10 800B31B0 41820014 */  beq     lbl_800B31C4
/* 0ADC14 800B31B4 7D8803A6 */  mtlr    r12
/* 0ADC18 800B31B8 389F0000 */  addi    r4, r31, 0
/* 0ADC1C 800B31BC 3860FFFF */  li      r3, -1
/* 0ADC20 800B31C0 4E800021 */  blrl    
lbl_800B31C4:
/* 0ADC24 800B31C4 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0ADC28 800B31C8 28000000 */  cmplwi  r0, 0
/* 0ADC2C 800B31CC 41820028 */  beq     lbl_800B31F4
/* 0ADC30 800B31D0 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0ADC34 800B31D4 38000000 */  li      r0, 0
/* 0ADC38 800B31D8 900D8D50 */  stw     r0, Canceling-_SDA_BASE_(r13)
/* 0ADC3C 800B31DC 280C0000 */  cmplwi  r12, 0
/* 0ADC40 800B31E0 41820014 */  beq     lbl_800B31F4
/* 0ADC44 800B31E4 7D8803A6 */  mtlr    r12
/* 0ADC48 800B31E8 389F0000 */  addi    r4, r31, 0
/* 0ADC4C 800B31EC 38600000 */  li      r3, 0
/* 0ADC50 800B31F0 4E800021 */  blrl    
lbl_800B31F4:
/* 0ADC54 800B31F4 48000DE1 */  bl      stateReady
lbl_800B31F8:
/* 0ADC58 800B31F8 8001001C */  lwz     r0, 0x1c(r1)
/* 0ADC5C 800B31FC 83E10014 */  lwz     r31, 0x14(r1)
/* 0ADC60 800B3200 38210018 */  addi    r1, r1, 0x18
/* 0ADC64 800B3204 7C0803A6 */  mtlr    r0
/* 0ADC68 800B3208 4E800020 */  blr     

stateTimeout:
/* 0ADC6C 800B320C 7C0802A6 */  mflr    r0
/* 0ADC70 800B3210 3C600123 */  lis     r3, 0x123
/* 0ADC74 800B3214 90010004 */  stw     r0, 4(r1)
/* 0ADC78 800B3218 38634568 */  addi    r3, r3, 0x4568
/* 0ADC7C 800B321C 9421FFF8 */  stwu    r1, -8(r1)
/* 0ADC80 800B3220 48002799 */  bl      __DVDStoreErrorCode
/* 0ADC84 800B3224 48001D45 */  bl      DVDReset
/* 0ADC88 800B3228 38600000 */  li      r3, 0
/* 0ADC8C 800B322C 4BFFFF35 */  bl      cbForStateError
/* 0ADC90 800B3230 8001000C */  lwz     r0, 0xc(r1)
/* 0ADC94 800B3234 38210008 */  addi    r1, r1, 8
/* 0ADC98 800B3238 7C0803A6 */  mtlr    r0
/* 0ADC9C 800B323C 4E800020 */  blr     

stateGettingError:
/* 0ADCA0 800B3240 7C0802A6 */  mflr    r0
/* 0ADCA4 800B3244 3C60800B */  lis     r3, cbForStateGettingError@ha
/* 0ADCA8 800B3248 90010004 */  stw     r0, 4(r1)
/* 0ADCAC 800B324C 3863331C */  addi    r3, r3, cbForStateGettingError@l
/* 0ADCB0 800B3250 9421FFF8 */  stwu    r1, -8(r1)
/* 0ADCB4 800B3254 4BFFF065 */  bl      DVDLowRequestError
/* 0ADCB8 800B3258 8001000C */  lwz     r0, 0xc(r1)
/* 0ADCBC 800B325C 38210008 */  addi    r1, r1, 8
/* 0ADCC0 800B3260 7C0803A6 */  mtlr    r0
/* 0ADCC4 800B3264 4E800020 */  blr     

CategorizeError:
/* 0ADCC8 800B3268 3C03FFFE */  addis   r0, r3, 0xfffe
/* 0ADCCC 800B326C 28000400 */  cmplwi  r0, 0x400
/* 0ADCD0 800B3270 40820010 */  bne     lbl_800B3280
/* 0ADCD4 800B3274 906D8D60 */  stw     r3, LastError-_SDA_BASE_(r13)
/* 0ADCD8 800B3278 38600001 */  li      r3, 1
/* 0ADCDC 800B327C 4E800020 */  blr     
lbl_800B3280:
/* 0ADCE0 800B3280 5464023E */  clrlwi  r4, r3, 8
/* 0ADCE4 800B3284 3C04FFFA */  addis   r0, r4, 0xfffa
/* 0ADCE8 800B3288 28002800 */  cmplwi  r0, 0x2800
/* 0ADCEC 800B328C 4182001C */  beq     lbl_800B32A8
/* 0ADCF0 800B3290 3C04FFFE */  addis   r0, r4, 0xfffe
/* 0ADCF4 800B3294 28003A00 */  cmplwi  r0, 0x3a00
/* 0ADCF8 800B3298 41820010 */  beq     lbl_800B32A8
/* 0ADCFC 800B329C 3C04FFF5 */  addis   r0, r4, 0xfff5
/* 0ADD00 800B32A0 28005A01 */  cmplwi  r0, 0x5a01
/* 0ADD04 800B32A4 4082000C */  bne     lbl_800B32B0
lbl_800B32A8:
/* 0ADD08 800B32A8 38600000 */  li      r3, 0
/* 0ADD0C 800B32AC 4E800020 */  blr     
lbl_800B32B0:
/* 0ADD10 800B32B0 806D8D64 */  lwz     r3, NumInternalRetry-_SDA_BASE_(r13)
/* 0ADD14 800B32B4 38030001 */  addi    r0, r3, 1
/* 0ADD18 800B32B8 900D8D64 */  stw     r0, NumInternalRetry-_SDA_BASE_(r13)
/* 0ADD1C 800B32BC 800D8D64 */  lwz     r0, NumInternalRetry-_SDA_BASE_(r13)
/* 0ADD20 800B32C0 2C000002 */  cmpwi   r0, 2
/* 0ADD24 800B32C4 40820028 */  bne     lbl_800B32EC
/* 0ADD28 800B32C8 800D8D60 */  lwz     r0, LastError-_SDA_BASE_(r13)
/* 0ADD2C 800B32CC 7C040040 */  cmplw   r4, r0
/* 0ADD30 800B32D0 40820010 */  bne     lbl_800B32E0
/* 0ADD34 800B32D4 908D8D60 */  stw     r4, LastError-_SDA_BASE_(r13)
/* 0ADD38 800B32D8 38600001 */  li      r3, 1
/* 0ADD3C 800B32DC 4E800020 */  blr     
lbl_800B32E0:
/* 0ADD40 800B32E0 908D8D60 */  stw     r4, LastError-_SDA_BASE_(r13)
/* 0ADD44 800B32E4 38600002 */  li      r3, 2
/* 0ADD48 800B32E8 4E800020 */  blr     
lbl_800B32EC:
/* 0ADD4C 800B32EC 3C04FFFD */  addis   r0, r4, 0xfffd
/* 0ADD50 800B32F0 908D8D60 */  stw     r4, LastError-_SDA_BASE_(r13)
/* 0ADD54 800B32F4 28001100 */  cmplwi  r0, 0x1100
/* 0ADD58 800B32F8 41820014 */  beq     lbl_800B330C
/* 0ADD5C 800B32FC 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0ADD60 800B3300 80030008 */  lwz     r0, 8(r3)
/* 0ADD64 800B3304 28000005 */  cmplwi  r0, 5
/* 0ADD68 800B3308 4082000C */  bne     lbl_800B3314
lbl_800B330C:
/* 0ADD6C 800B330C 38600002 */  li      r3, 2
/* 0ADD70 800B3310 4E800020 */  blr     
lbl_800B3314:
/* 0ADD74 800B3314 38600003 */  li      r3, 3
/* 0ADD78 800B3318 4E800020 */  blr     

cbForStateGettingError:
/* 0ADD7C 800B331C 7C0802A6 */  mflr    r0
/* 0ADD80 800B3320 28030010 */  cmplwi  r3, 0x10
/* 0ADD84 800B3324 90010004 */  stw     r0, 4(r1)
/* 0ADD88 800B3328 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0ADD8C 800B332C 93E1001C */  stw     r31, 0x1c(r1)
/* 0ADD90 800B3330 93C10018 */  stw     r30, 0x18(r1)
/* 0ADD94 800B3334 93A10014 */  stw     r29, 0x14(r1)
/* 0ADD98 800B3338 93810010 */  stw     r28, 0x10(r1)
/* 0ADD9C 800B333C 4082002C */  bne     lbl_800B3368
/* 0ADDA0 800B3340 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0ADDA4 800B3344 3800FFFF */  li      r0, -1
/* 0ADDA8 800B3348 3C600123 */  lis     r3, 0x123
/* 0ADDAC 800B334C 9004000C */  stw     r0, 0xc(r4)
/* 0ADDB0 800B3350 38634568 */  addi    r3, r3, 0x4568
/* 0ADDB4 800B3354 48002665 */  bl      __DVDStoreErrorCode
/* 0ADDB8 800B3358 48001C11 */  bl      DVDReset
/* 0ADDBC 800B335C 38600000 */  li      r3, 0
/* 0ADDC0 800B3360 4BFFFE01 */  bl      cbForStateError
/* 0ADDC4 800B3364 4800022C */  b       lbl_800B3590
lbl_800B3368:
/* 0ADDC8 800B3368 546007BD */  rlwinm. r0, r3, 0, 0x1e, 0x1e
/* 0ADDCC 800B336C 4182002C */  beq     lbl_800B3398
/* 0ADDD0 800B3370 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0ADDD4 800B3374 3800FFFF */  li      r0, -1
/* 0ADDD8 800B3378 3C600123 */  lis     r3, 0x123
/* 0ADDDC 800B337C 9004000C */  stw     r0, 0xc(r4)
/* 0ADDE0 800B3380 38634567 */  addi    r3, r3, 0x4567
/* 0ADDE4 800B3384 48002635 */  bl      __DVDStoreErrorCode
/* 0ADDE8 800B3388 3C60800B */  lis     r3, cbForStateError@ha
/* 0ADDEC 800B338C 38633160 */  addi    r3, r3, cbForStateError@l
/* 0ADDF0 800B3390 4BFFEE9D */  bl      DVDLowStopMotor
/* 0ADDF4 800B3394 480001FC */  b       lbl_800B3590
lbl_800B3398:
/* 0ADDF8 800B3398 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0ADDFC 800B339C 83A36020 */  lwz     r29, (DI_REGS_BASE + DI_DIIMMBUF)@l(r3)
/* 0ADE00 800B33A0 387D0000 */  addi    r3, r29, 0
/* 0ADE04 800B33A4 57BC000E */  rlwinm  r28, r29, 0, 0, 7
/* 0ADE08 800B33A8 4BFFFEC1 */  bl      CategorizeError
/* 0ADE0C 800B33AC 3BE30000 */  addi    r31, r3, 0
/* 0ADE10 800B33B0 281F0001 */  cmplwi  r31, 1
/* 0ADE14 800B33B4 40820028 */  bne     lbl_800B33DC
/* 0ADE18 800B33B8 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0ADE1C 800B33BC 3800FFFF */  li      r0, -1
/* 0ADE20 800B33C0 387D0000 */  addi    r3, r29, 0
/* 0ADE24 800B33C4 9004000C */  stw     r0, 0xc(r4)
/* 0ADE28 800B33C8 480025F1 */  bl      __DVDStoreErrorCode
/* 0ADE2C 800B33CC 3C60800B */  lis     r3, cbForStateError@ha
/* 0ADE30 800B33D0 38633160 */  addi    r3, r3, cbForStateError@l
/* 0ADE34 800B33D4 4BFFEE59 */  bl      DVDLowStopMotor
/* 0ADE38 800B33D8 480001B8 */  b       lbl_800B3590
lbl_800B33DC:
/* 0ADE3C 800B33DC 381FFFFE */  addi    r0, r31, -2
/* 0ADE40 800B33E0 28000001 */  cmplwi  r0, 1
/* 0ADE44 800B33E4 4181000C */  bgt     lbl_800B33F0
/* 0ADE48 800B33E8 38800000 */  li      r4, 0
/* 0ADE4C 800B33EC 48000044 */  b       lbl_800B3430
lbl_800B33F0:
/* 0ADE50 800B33F0 3C1CFF00 */  addis   r0, r28, 0xff00
/* 0ADE54 800B33F4 28000000 */  cmplwi  r0, 0
/* 0ADE58 800B33F8 4082000C */  bne     lbl_800B3404
/* 0ADE5C 800B33FC 38800004 */  li      r4, 4
/* 0ADE60 800B3400 48000030 */  b       lbl_800B3430
lbl_800B3404:
/* 0ADE64 800B3404 3C1CFE00 */  addis   r0, r28, 0xfe00
/* 0ADE68 800B3408 28000000 */  cmplwi  r0, 0
/* 0ADE6C 800B340C 4082000C */  bne     lbl_800B3418
/* 0ADE70 800B3410 38800006 */  li      r4, 6
/* 0ADE74 800B3414 4800001C */  b       lbl_800B3430
lbl_800B3418:
/* 0ADE78 800B3418 3C1CFD00 */  addis   r0, r28, 0xfd00
/* 0ADE7C 800B341C 28000000 */  cmplwi  r0, 0
/* 0ADE80 800B3420 4082000C */  bne     lbl_800B342C
/* 0ADE84 800B3424 38800003 */  li      r4, 3
/* 0ADE88 800B3428 48000008 */  b       lbl_800B3430
lbl_800B342C:
/* 0ADE8C 800B342C 38800005 */  li      r4, 5
lbl_800B3430:
/* 0ADE90 800B3430 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0ADE94 800B3434 28000000 */  cmplwi  r0, 0
/* 0ADE98 800B3438 4182006C */  beq     lbl_800B34A4
/* 0ADE9C 800B343C 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0ADEA0 800B3440 908D8D58 */  stw     r4, ResumeFromHere-_SDA_BASE_(r13)
/* 0ADEA4 800B3444 38000000 */  li      r0, 0
/* 0ADEA8 800B3448 83CD8D30 */  lwz     r30, executing-_SDA_BASE_(r13)
/* 0ADEAC 800B344C 386325E0 */  addi    r3, r3, DummyCommandBlock@l
/* 0ADEB0 800B3450 900D8D50 */  stw     r0, Canceling-_SDA_BASE_(r13)
/* 0ADEB4 800B3454 3800000A */  li      r0, 0xa
/* 0ADEB8 800B3458 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0ADEBC 800B345C 901E000C */  stw     r0, 0xc(r30)
/* 0ADEC0 800B3460 819E0028 */  lwz     r12, 0x28(r30)
/* 0ADEC4 800B3464 280C0000 */  cmplwi  r12, 0
/* 0ADEC8 800B3468 41820014 */  beq     lbl_800B347C
/* 0ADECC 800B346C 7D8803A6 */  mtlr    r12
/* 0ADED0 800B3470 389E0000 */  addi    r4, r30, 0
/* 0ADED4 800B3474 3860FFFD */  li      r3, -3
/* 0ADED8 800B3478 4E800021 */  blrl    
lbl_800B347C:
/* 0ADEDC 800B347C 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0ADEE0 800B3480 280C0000 */  cmplwi  r12, 0
/* 0ADEE4 800B3484 41820014 */  beq     lbl_800B3498
/* 0ADEE8 800B3488 7D8803A6 */  mtlr    r12
/* 0ADEEC 800B348C 389E0000 */  addi    r4, r30, 0
/* 0ADEF0 800B3490 38600000 */  li      r3, 0
/* 0ADEF4 800B3494 4E800021 */  blrl    
lbl_800B3498:
/* 0ADEF8 800B3498 48000B3D */  bl      stateReady
/* 0ADEFC 800B349C 38000001 */  li      r0, 1
/* 0ADF00 800B34A0 48000008 */  b       lbl_800B34A8
lbl_800B34A4:
/* 0ADF04 800B34A4 38000000 */  li      r0, 0
lbl_800B34A8:
/* 0ADF08 800B34A8 2C000000 */  cmpwi   r0, 0
/* 0ADF0C 800B34AC 408200E4 */  bne     lbl_800B3590
/* 0ADF10 800B34B0 281F0002 */  cmplwi  r31, 2
/* 0ADF14 800B34B4 40820014 */  bne     lbl_800B34C8
/* 0ADF18 800B34B8 7FA3EB78 */  mr      r3, r29
/* 0ADF1C 800B34BC 480024FD */  bl      __DVDStoreErrorCode
/* 0ADF20 800B34C0 480001F1 */  bl      stateGoToRetry
/* 0ADF24 800B34C4 480000CC */  b       lbl_800B3590
lbl_800B34C8:
/* 0ADF28 800B34C8 281F0003 */  cmplwi  r31, 3
/* 0ADF2C 800B34CC 40820040 */  bne     lbl_800B350C
/* 0ADF30 800B34D0 57A3023E */  clrlwi  r3, r29, 8
/* 0ADF34 800B34D4 3C03FFFD */  addis   r0, r3, 0xfffd
/* 0ADF38 800B34D8 28001100 */  cmplwi  r0, 0x1100
/* 0ADF3C 800B34DC 4082001C */  bne     lbl_800B34F8
/* 0ADF40 800B34E0 80AD8D30 */  lwz     r5, executing-_SDA_BASE_(r13)
/* 0ADF44 800B34E4 3C60800B */  lis     r3, cbForUnrecoveredError@ha
/* 0ADF48 800B34E8 388335B0 */  addi    r4, r3, cbForUnrecoveredError@l
/* 0ADF4C 800B34EC 80650010 */  lwz     r3, 0x10(r5)
/* 0ADF50 800B34F0 4BFFEBD9 */  bl      DVDLowSeek
/* 0ADF54 800B34F4 4800009C */  b       lbl_800B3590
lbl_800B34F8:
/* 0ADF58 800B34F8 818D8D74 */  lwz     r12, LastState-_SDA_BASE_(r13)
/* 0ADF5C 800B34FC 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0ADF60 800B3500 7D8803A6 */  mtlr    r12
/* 0ADF64 800B3504 4E800021 */  blrl    
/* 0ADF68 800B3508 48000088 */  b       lbl_800B3590
lbl_800B350C:
/* 0ADF6C 800B350C 3C1CFF00 */  addis   r0, r28, 0xff00
/* 0ADF70 800B3510 28000000 */  cmplwi  r0, 0
/* 0ADF74 800B3514 40820018 */  bne     lbl_800B352C
/* 0ADF78 800B3518 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0ADF7C 800B351C 38000005 */  li      r0, 5
/* 0ADF80 800B3520 9003000C */  stw     r0, 0xc(r3)
/* 0ADF84 800B3524 480009A5 */  bl      stateMotorStopped
/* 0ADF88 800B3528 48000068 */  b       lbl_800B3590
lbl_800B352C:
/* 0ADF8C 800B352C 3C1CFE00 */  addis   r0, r28, 0xfe00
/* 0ADF90 800B3530 28000000 */  cmplwi  r0, 0
/* 0ADF94 800B3534 40820018 */  bne     lbl_800B354C
/* 0ADF98 800B3538 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0ADF9C 800B353C 38000003 */  li      r0, 3
/* 0ADFA0 800B3540 9003000C */  stw     r0, 0xc(r3)
/* 0ADFA4 800B3544 48000819 */  bl      stateCoverClosed
/* 0ADFA8 800B3548 48000048 */  b       lbl_800B3590
lbl_800B354C:
/* 0ADFAC 800B354C 3C1CFD00 */  addis   r0, r28, 0xfd00
/* 0ADFB0 800B3550 28000000 */  cmplwi  r0, 0
/* 0ADFB4 800B3554 40820018 */  bne     lbl_800B356C
/* 0ADFB8 800B3558 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0ADFBC 800B355C 38000004 */  li      r0, 4
/* 0ADFC0 800B3560 9003000C */  stw     r0, 0xc(r3)
/* 0ADFC4 800B3564 48000965 */  bl      stateMotorStopped
/* 0ADFC8 800B3568 48000028 */  b       lbl_800B3590
lbl_800B356C:
/* 0ADFCC 800B356C 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0ADFD0 800B3570 3800FFFF */  li      r0, -1
/* 0ADFD4 800B3574 3C600123 */  lis     r3, 0x123
/* 0ADFD8 800B3578 9004000C */  stw     r0, 0xc(r4)
/* 0ADFDC 800B357C 38634567 */  addi    r3, r3, 0x4567
/* 0ADFE0 800B3580 48002439 */  bl      __DVDStoreErrorCode
/* 0ADFE4 800B3584 3C60800B */  lis     r3, cbForStateError@ha
/* 0ADFE8 800B3588 38633160 */  addi    r3, r3, cbForStateError@l
/* 0ADFEC 800B358C 4BFFECA1 */  bl      DVDLowStopMotor
lbl_800B3590:
/* 0ADFF0 800B3590 80010024 */  lwz     r0, 0x24(r1)
/* 0ADFF4 800B3594 83E1001C */  lwz     r31, 0x1c(r1)
/* 0ADFF8 800B3598 83C10018 */  lwz     r30, 0x18(r1)
/* 0ADFFC 800B359C 83A10014 */  lwz     r29, 0x14(r1)
/* 0AE000 800B35A0 83810010 */  lwz     r28, 0x10(r1)
/* 0AE004 800B35A4 38210020 */  addi    r1, r1, 0x20
/* 0AE008 800B35A8 7C0803A6 */  mtlr    r0
/* 0AE00C 800B35AC 4E800020 */  blr     

cbForUnrecoveredError:
/* 0AE010 800B35B0 7C0802A6 */  mflr    r0
/* 0AE014 800B35B4 28030010 */  cmplwi  r3, 0x10
/* 0AE018 800B35B8 90010004 */  stw     r0, 4(r1)
/* 0AE01C 800B35BC 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE020 800B35C0 4082002C */  bne     lbl_800B35EC
/* 0AE024 800B35C4 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE028 800B35C8 3800FFFF */  li      r0, -1
/* 0AE02C 800B35CC 3C600123 */  lis     r3, 0x123
/* 0AE030 800B35D0 9004000C */  stw     r0, 0xc(r4)
/* 0AE034 800B35D4 38634568 */  addi    r3, r3, 0x4568
/* 0AE038 800B35D8 480023E1 */  bl      __DVDStoreErrorCode
/* 0AE03C 800B35DC 4800198D */  bl      DVDReset
/* 0AE040 800B35E0 38600000 */  li      r3, 0
/* 0AE044 800B35E4 4BFFFB7D */  bl      cbForStateError
/* 0AE048 800B35E8 48000020 */  b       lbl_800B3608
lbl_800B35EC:
/* 0AE04C 800B35EC 546007FF */  clrlwi. r0, r3, 0x1f
/* 0AE050 800B35F0 4182000C */  beq     lbl_800B35FC
/* 0AE054 800B35F4 480000BD */  bl      stateGoToRetry
/* 0AE058 800B35F8 48000010 */  b       lbl_800B3608
lbl_800B35FC:
/* 0AE05C 800B35FC 3C60800B */  lis     r3, cbForUnrecoveredErrorRetry@ha
/* 0AE060 800B3600 38633618 */  addi    r3, r3, cbForUnrecoveredErrorRetry@l
/* 0AE064 800B3604 4BFFECB5 */  bl      DVDLowRequestError
lbl_800B3608:
/* 0AE068 800B3608 8001000C */  lwz     r0, 0xc(r1)
/* 0AE06C 800B360C 38210008 */  addi    r1, r1, 8
/* 0AE070 800B3610 7C0803A6 */  mtlr    r0
/* 0AE074 800B3614 4E800020 */  blr     

cbForUnrecoveredErrorRetry:
/* 0AE078 800B3618 7C0802A6 */  mflr    r0
/* 0AE07C 800B361C 28030010 */  cmplwi  r3, 0x10
/* 0AE080 800B3620 90010004 */  stw     r0, 4(r1)
/* 0AE084 800B3624 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE088 800B3628 4082002C */  bne     lbl_800B3654
/* 0AE08C 800B362C 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE090 800B3630 3800FFFF */  li      r0, -1
/* 0AE094 800B3634 3C600123 */  lis     r3, 0x123
/* 0AE098 800B3638 9004000C */  stw     r0, 0xc(r4)
/* 0AE09C 800B363C 38634568 */  addi    r3, r3, 0x4568
/* 0AE0A0 800B3640 48002379 */  bl      __DVDStoreErrorCode
/* 0AE0A4 800B3644 48001925 */  bl      DVDReset
/* 0AE0A8 800B3648 38600000 */  li      r3, 0
/* 0AE0AC 800B364C 4BFFFB15 */  bl      cbForStateError
/* 0AE0B0 800B3650 48000050 */  b       lbl_800B36A0
lbl_800B3654:
/* 0AE0B4 800B3654 546007BD */  rlwinm. r0, r3, 0, 0x1e, 0x1e
/* 0AE0B8 800B3658 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE0BC 800B365C 3880FFFF */  li      r4, -1
/* 0AE0C0 800B3660 9083000C */  stw     r4, 0xc(r3)
/* 0AE0C4 800B3664 41820020 */  beq     lbl_800B3684
/* 0AE0C8 800B3668 3C600123 */  lis     r3, 0x123
/* 0AE0CC 800B366C 38634567 */  addi    r3, r3, 0x4567
/* 0AE0D0 800B3670 48002349 */  bl      __DVDStoreErrorCode
/* 0AE0D4 800B3674 3C60800B */  lis     r3, cbForStateError@ha
/* 0AE0D8 800B3678 38633160 */  addi    r3, r3, cbForStateError@l
/* 0AE0DC 800B367C 4BFFEBB1 */  bl      DVDLowStopMotor
/* 0AE0E0 800B3680 48000020 */  b       lbl_800B36A0
lbl_800B3684:
/* 0AE0E4 800B3684 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AE0E8 800B3688 38636000 */  addi    r3, r3, DI_REGS_BASE@l
/* 0AE0EC 800B368C 80630020 */  lwz     r3, DI_DIIMMBUF(r3)
/* 0AE0F0 800B3690 48002329 */  bl      __DVDStoreErrorCode
/* 0AE0F4 800B3694 3C60800B */  lis     r3, cbForStateError@ha
/* 0AE0F8 800B3698 38633160 */  addi    r3, r3, cbForStateError@l
/* 0AE0FC 800B369C 4BFFEB91 */  bl      DVDLowStopMotor
lbl_800B36A0:
/* 0AE100 800B36A0 8001000C */  lwz     r0, 0xc(r1)
/* 0AE104 800B36A4 38210008 */  addi    r1, r1, 8
/* 0AE108 800B36A8 7C0803A6 */  mtlr    r0
/* 0AE10C 800B36AC 4E800020 */  blr     

stateGoToRetry:
/* 0AE110 800B36B0 7C0802A6 */  mflr    r0
/* 0AE114 800B36B4 3C60800B */  lis     r3, cbForStateGoToRetry@ha
/* 0AE118 800B36B8 90010004 */  stw     r0, 4(r1)
/* 0AE11C 800B36BC 386336D8 */  addi    r3, r3, cbForStateGoToRetry@l
/* 0AE120 800B36C0 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE124 800B36C4 4BFFEB69 */  bl      DVDLowStopMotor
/* 0AE128 800B36C8 8001000C */  lwz     r0, 0xc(r1)
/* 0AE12C 800B36CC 38210008 */  addi    r1, r1, 8
/* 0AE130 800B36D0 7C0803A6 */  mtlr    r0
/* 0AE134 800B36D4 4E800020 */  blr     

cbForStateGoToRetry:
/* 0AE138 800B36D8 7C0802A6 */  mflr    r0
/* 0AE13C 800B36DC 28030010 */  cmplwi  r3, 0x10
/* 0AE140 800B36E0 90010004 */  stw     r0, 4(r1)
/* 0AE144 800B36E4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AE148 800B36E8 93E10014 */  stw     r31, 0x14(r1)
/* 0AE14C 800B36EC 4082002C */  bne     lbl_800B3718
/* 0AE150 800B36F0 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE154 800B36F4 3800FFFF */  li      r0, -1
/* 0AE158 800B36F8 3C600123 */  lis     r3, 0x123
/* 0AE15C 800B36FC 9004000C */  stw     r0, 0xc(r4)
/* 0AE160 800B3700 38634568 */  addi    r3, r3, 0x4568
/* 0AE164 800B3704 480022B5 */  bl      __DVDStoreErrorCode
/* 0AE168 800B3708 48001861 */  bl      DVDReset
/* 0AE16C 800B370C 38600000 */  li      r3, 0
/* 0AE170 800B3710 4BFFFA51 */  bl      cbForStateError
/* 0AE174 800B3714 48000108 */  b       lbl_800B381C
lbl_800B3718:
/* 0AE178 800B3718 546007BD */  rlwinm. r0, r3, 0, 0x1e, 0x1e
/* 0AE17C 800B371C 4182002C */  beq     lbl_800B3748
/* 0AE180 800B3720 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE184 800B3724 3800FFFF */  li      r0, -1
/* 0AE188 800B3728 3C600123 */  lis     r3, 0x123
/* 0AE18C 800B372C 9004000C */  stw     r0, 0xc(r4)
/* 0AE190 800B3730 38634567 */  addi    r3, r3, 0x4567
/* 0AE194 800B3734 48002285 */  bl      __DVDStoreErrorCode
/* 0AE198 800B3738 3C60800B */  lis     r3, cbForStateError@ha
/* 0AE19C 800B373C 38633160 */  addi    r3, r3, cbForStateError@l
/* 0AE1A0 800B3740 4BFFEAED */  bl      DVDLowStopMotor
/* 0AE1A4 800B3744 480000D8 */  b       lbl_800B381C
lbl_800B3748:
/* 0AE1A8 800B3748 38000000 */  li      r0, 0
/* 0AE1AC 800B374C 900D8D64 */  stw     r0, NumInternalRetry-_SDA_BASE_(r13)
/* 0AE1B0 800B3750 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AE1B4 800B3754 28000004 */  cmplwi  r0, 4
/* 0AE1B8 800B3758 41820028 */  beq     lbl_800B3780
/* 0AE1BC 800B375C 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AE1C0 800B3760 28000005 */  cmplwi  r0, 5
/* 0AE1C4 800B3764 4182001C */  beq     lbl_800B3780
/* 0AE1C8 800B3768 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AE1CC 800B376C 2800000D */  cmplwi  r0, 0xd
/* 0AE1D0 800B3770 41820010 */  beq     lbl_800B3780
/* 0AE1D4 800B3774 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AE1D8 800B3778 2800000F */  cmplwi  r0, 0xf
/* 0AE1DC 800B377C 4082000C */  bne     lbl_800B3788
lbl_800B3780:
/* 0AE1E0 800B3780 38000001 */  li      r0, 1
/* 0AE1E4 800B3784 900D8D68 */  stw     r0, ResetRequired-_SDA_BASE_(r13)
lbl_800B3788:
/* 0AE1E8 800B3788 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AE1EC 800B378C 28000000 */  cmplwi  r0, 0
/* 0AE1F0 800B3790 41820070 */  beq     lbl_800B3800
/* 0AE1F4 800B3794 38000002 */  li      r0, 2
/* 0AE1F8 800B3798 83ED8D30 */  lwz     r31, executing-_SDA_BASE_(r13)
/* 0AE1FC 800B379C 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0AE200 800B37A0 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
/* 0AE204 800B37A4 380325E0 */  addi    r0, r3, DummyCommandBlock@l
/* 0AE208 800B37A8 38600000 */  li      r3, 0
/* 0AE20C 800B37AC 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AE210 800B37B0 3800000A */  li      r0, 0xa
/* 0AE214 800B37B4 906D8D50 */  stw     r3, Canceling-_SDA_BASE_(r13)
/* 0AE218 800B37B8 901F000C */  stw     r0, 0xc(r31)
/* 0AE21C 800B37BC 819F0028 */  lwz     r12, 0x28(r31)
/* 0AE220 800B37C0 280C0000 */  cmplwi  r12, 0
/* 0AE224 800B37C4 41820014 */  beq     lbl_800B37D8
/* 0AE228 800B37C8 7D8803A6 */  mtlr    r12
/* 0AE22C 800B37CC 389F0000 */  addi    r4, r31, 0
/* 0AE230 800B37D0 3860FFFD */  li      r3, -3
/* 0AE234 800B37D4 4E800021 */  blrl    
lbl_800B37D8:
/* 0AE238 800B37D8 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0AE23C 800B37DC 280C0000 */  cmplwi  r12, 0
/* 0AE240 800B37E0 41820014 */  beq     lbl_800B37F4
/* 0AE244 800B37E4 7D8803A6 */  mtlr    r12
/* 0AE248 800B37E8 389F0000 */  addi    r4, r31, 0
/* 0AE24C 800B37EC 38600000 */  li      r3, 0
/* 0AE250 800B37F0 4E800021 */  blrl    
lbl_800B37F4:
/* 0AE254 800B37F4 480007E1 */  bl      stateReady
/* 0AE258 800B37F8 38000001 */  li      r0, 1
/* 0AE25C 800B37FC 48000008 */  b       lbl_800B3804
lbl_800B3800:
/* 0AE260 800B3800 38000000 */  li      r0, 0
lbl_800B3804:
/* 0AE264 800B3804 2C000000 */  cmpwi   r0, 0
/* 0AE268 800B3808 40820014 */  bne     lbl_800B381C
/* 0AE26C 800B380C 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE270 800B3810 3800000B */  li      r0, 0xb
/* 0AE274 800B3814 9003000C */  stw     r0, 0xc(r3)
/* 0AE278 800B3818 480006B1 */  bl      stateMotorStopped
lbl_800B381C:
/* 0AE27C 800B381C 8001001C */  lwz     r0, 0x1c(r1)
/* 0AE280 800B3820 83E10014 */  lwz     r31, 0x14(r1)
/* 0AE284 800B3824 38210018 */  addi    r1, r1, 0x18
/* 0AE288 800B3828 7C0803A6 */  mtlr    r0
/* 0AE28C 800B382C 4E800020 */  blr     

stateCheckID:
/* 0AE290 800B3830 7C0802A6 */  mflr    r0
/* 0AE294 800B3834 3C608013 */  lis     r3, BB2@ha
/* 0AE298 800B3838 90010004 */  stw     r0, 4(r1)
/* 0AE29C 800B383C 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0AE2A0 800B3840 93E1000C */  stw     r31, 0xc(r1)
/* 0AE2A4 800B3844 3BE325A0 */  addi    r31, r3, BB2@l
/* 0AE2A8 800B3848 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AE2AC 800B384C 2C000003 */  cmpwi   r0, 3
/* 0AE2B0 800B3850 41820008 */  beq     lbl_800B3858
/* 0AE2B4 800B3854 4800006C */  b       lbl_800B38C0
lbl_800B3858:
/* 0AE2B8 800B3858 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE2BC 800B385C 387F0020 */  addi    r3, r31, 0x20
/* 0AE2C0 800B3860 80840024 */  lwz     r4, 0x24(r4)
/* 0AE2C4 800B3864 480021D1 */  bl      DVDCompareDiskID
/* 0AE2C8 800B3868 2C030000 */  cmpwi   r3, 0
/* 0AE2CC 800B386C 41820044 */  beq     lbl_800B38B0
/* 0AE2D0 800B3870 806D8D34 */  lwz     r3, IDShouldBe-_SDA_BASE_(r13)
/* 0AE2D4 800B3874 389F0020 */  addi    r4, r31, 0x20
/* 0AE2D8 800B3878 38A00020 */  li      r5, 0x20
/* 0AE2DC 800B387C 4BF51C49 */  bl      memcpy
/* 0AE2E0 800B3880 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE2E4 800B3884 38000001 */  li      r0, 1
/* 0AE2E8 800B3888 387F0000 */  addi    r3, r31, 0
/* 0AE2EC 800B388C 9004000C */  stw     r0, 0xc(r4)
/* 0AE2F0 800B3890 38800020 */  li      r4, 0x20
/* 0AE2F4 800B3894 4BFE9EBD */  bl      DCInvalidateRange
/* 0AE2F8 800B3898 3C80800B */  lis     r4, stateCheckID2a@ha
/* 0AE2FC 800B389C 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE300 800B38A0 38043944 */  addi    r0, r4, stateCheckID2a@l
/* 0AE304 800B38A4 900D8D74 */  stw     r0, LastState-_SDA_BASE_(r13)
/* 0AE308 800B38A8 4800009D */  bl      stateCheckID2a
/* 0AE30C 800B38AC 48000050 */  b       lbl_800B38FC
lbl_800B38B0:
/* 0AE310 800B38B0 3C60800B */  lis     r3, cbForStateCheckID1@ha
/* 0AE314 800B38B4 38633A24 */  addi    r3, r3, cbForStateCheckID1@l
/* 0AE318 800B38B8 4BFFE975 */  bl      DVDLowStopMotor
/* 0AE31C 800B38BC 48000040 */  b       lbl_800B38FC
lbl_800B38C0:
/* 0AE320 800B38C0 808D8D34 */  lwz     r4, IDShouldBe-_SDA_BASE_(r13)
/* 0AE324 800B38C4 387F0020 */  addi    r3, r31, 0x20
/* 0AE328 800B38C8 38A00020 */  li      r5, 0x20
/* 0AE32C 800B38CC 4801B045 */  bl      memcmp
/* 0AE330 800B38D0 2C030000 */  cmpwi   r3, 0
/* 0AE334 800B38D4 41820014 */  beq     lbl_800B38E8
/* 0AE338 800B38D8 3C60800B */  lis     r3, cbForStateCheckID1@ha
/* 0AE33C 800B38DC 38633A24 */  addi    r3, r3, cbForStateCheckID1@l
/* 0AE340 800B38E0 4BFFE94D */  bl      DVDLowStopMotor
/* 0AE344 800B38E4 48000018 */  b       lbl_800B38FC
lbl_800B38E8:
/* 0AE348 800B38E8 3C80800B */  lis     r4, stateCheckID3@ha
/* 0AE34C 800B38EC 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE350 800B38F0 38043910 */  addi    r0, r4, stateCheckID3@l
/* 0AE354 800B38F4 900D8D74 */  stw     r0, LastState-_SDA_BASE_(r13)
/* 0AE358 800B38F8 48000019 */  bl      stateCheckID3
lbl_800B38FC:
/* 0AE35C 800B38FC 80010014 */  lwz     r0, 0x14(r1)
/* 0AE360 800B3900 83E1000C */  lwz     r31, 0xc(r1)
/* 0AE364 800B3904 38210010 */  addi    r1, r1, 0x10
/* 0AE368 800B3908 7C0803A6 */  mtlr    r0
/* 0AE36C 800B390C 4E800020 */  blr     

stateCheckID3:
/* 0AE370 800B3910 7C0802A6 */  mflr    r0
/* 0AE374 800B3914 3C60800B */  lis     r3, cbForStateCheckID3@ha
/* 0AE378 800B3918 90010004 */  stw     r0, 4(r1)
/* 0AE37C 800B391C 38A33C1C */  addi    r5, r3, cbForStateCheckID3@l
/* 0AE380 800B3920 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE384 800B3924 808D8D34 */  lwz     r4, IDShouldBe-_SDA_BASE_(r13)
/* 0AE388 800B3928 88640008 */  lbz     r3, 8(r4)
/* 0AE38C 800B392C 3880000A */  li      r4, 0xa
/* 0AE390 800B3930 4BFFEBD5 */  bl      DVDLowAudioBufferConfig
/* 0AE394 800B3934 8001000C */  lwz     r0, 0xc(r1)
/* 0AE398 800B3938 38210008 */  addi    r1, r1, 8
/* 0AE39C 800B393C 7C0803A6 */  mtlr    r0
/* 0AE3A0 800B3940 4E800020 */  blr     

stateCheckID2a:
/* 0AE3A4 800B3944 7C0802A6 */  mflr    r0
/* 0AE3A8 800B3948 3C60800B */  lis     r3, cbForStateCheckID2a@ha
/* 0AE3AC 800B394C 90010004 */  stw     r0, 4(r1)
/* 0AE3B0 800B3950 38A33978 */  addi    r5, r3, cbForStateCheckID2a@l
/* 0AE3B4 800B3954 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE3B8 800B3958 808D8D34 */  lwz     r4, IDShouldBe-_SDA_BASE_(r13)
/* 0AE3BC 800B395C 88640008 */  lbz     r3, 8(r4)
/* 0AE3C0 800B3960 3880000A */  li      r4, 0xa
/* 0AE3C4 800B3964 4BFFEBA1 */  bl      DVDLowAudioBufferConfig
/* 0AE3C8 800B3968 8001000C */  lwz     r0, 0xc(r1)
/* 0AE3CC 800B396C 38210008 */  addi    r1, r1, 8
/* 0AE3D0 800B3970 7C0803A6 */  mtlr    r0
/* 0AE3D4 800B3974 4E800020 */  blr     

cbForStateCheckID2a:
/* 0AE3D8 800B3978 7C0802A6 */  mflr    r0
/* 0AE3DC 800B397C 28030010 */  cmplwi  r3, 0x10
/* 0AE3E0 800B3980 90010004 */  stw     r0, 4(r1)
/* 0AE3E4 800B3984 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE3E8 800B3988 4082002C */  bne     lbl_800B39B4
/* 0AE3EC 800B398C 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE3F0 800B3990 3800FFFF */  li      r0, -1
/* 0AE3F4 800B3994 3C600123 */  lis     r3, 0x123
/* 0AE3F8 800B3998 9004000C */  stw     r0, 0xc(r4)
/* 0AE3FC 800B399C 38634568 */  addi    r3, r3, 0x4568
/* 0AE400 800B39A0 48002019 */  bl      __DVDStoreErrorCode
/* 0AE404 800B39A4 480015C5 */  bl      DVDReset
/* 0AE408 800B39A8 38600000 */  li      r3, 0
/* 0AE40C 800B39AC 4BFFF7B5 */  bl      cbForStateError
/* 0AE410 800B39B0 4800002C */  b       lbl_800B39DC
lbl_800B39B4:
/* 0AE414 800B39B4 546007FF */  clrlwi. r0, r3, 0x1f
/* 0AE418 800B39B8 41820018 */  beq     lbl_800B39D0
/* 0AE41C 800B39BC 38000000 */  li      r0, 0
/* 0AE420 800B39C0 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE424 800B39C4 900D8D64 */  stw     r0, NumInternalRetry-_SDA_BASE_(r13)
/* 0AE428 800B39C8 48000025 */  bl      stateCheckID2
/* 0AE42C 800B39CC 48000010 */  b       lbl_800B39DC
lbl_800B39D0:
/* 0AE430 800B39D0 3C60800B */  lis     r3, cbForStateGettingError@ha
/* 0AE434 800B39D4 3863331C */  addi    r3, r3, cbForStateGettingError@l
/* 0AE438 800B39D8 4BFFE8E1 */  bl      DVDLowRequestError
lbl_800B39DC:
/* 0AE43C 800B39DC 8001000C */  lwz     r0, 0xc(r1)
/* 0AE440 800B39E0 38210008 */  addi    r1, r1, 8
/* 0AE444 800B39E4 7C0803A6 */  mtlr    r0
/* 0AE448 800B39E8 4E800020 */  blr     

stateCheckID2:
/* 0AE44C 800B39EC 7C0802A6 */  mflr    r0
/* 0AE450 800B39F0 3C608013 */  lis     r3, BB2@ha
/* 0AE454 800B39F4 90010004 */  stw     r0, 4(r1)
/* 0AE458 800B39F8 3C80800B */  lis     r4, cbForStateCheckID2@ha
/* 0AE45C 800B39FC 38C43B38 */  addi    r6, r4, cbForStateCheckID2@l
/* 0AE460 800B3A00 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE464 800B3A04 386325A0 */  addi    r3, r3, BB2@l
/* 0AE468 800B3A08 38800020 */  li      r4, 0x20
/* 0AE46C 800B3A0C 38A00420 */  li      r5, 0x420
/* 0AE470 800B3A10 4BFFE421 */  bl      DVDLowRead
/* 0AE474 800B3A14 8001000C */  lwz     r0, 0xc(r1)
/* 0AE478 800B3A18 38210008 */  addi    r1, r1, 8
/* 0AE47C 800B3A1C 7C0803A6 */  mtlr    r0
/* 0AE480 800B3A20 4E800020 */  blr     

cbForStateCheckID1:
/* 0AE484 800B3A24 7C0802A6 */  mflr    r0
/* 0AE488 800B3A28 28030010 */  cmplwi  r3, 0x10
/* 0AE48C 800B3A2C 90010004 */  stw     r0, 4(r1)
/* 0AE490 800B3A30 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AE494 800B3A34 93E10014 */  stw     r31, 0x14(r1)
/* 0AE498 800B3A38 4082002C */  bne     lbl_800B3A64
/* 0AE49C 800B3A3C 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE4A0 800B3A40 3800FFFF */  li      r0, -1
/* 0AE4A4 800B3A44 3C600123 */  lis     r3, 0x123
/* 0AE4A8 800B3A48 9004000C */  stw     r0, 0xc(r4)
/* 0AE4AC 800B3A4C 38634568 */  addi    r3, r3, 0x4568
/* 0AE4B0 800B3A50 48001F69 */  bl      __DVDStoreErrorCode
/* 0AE4B4 800B3A54 48001515 */  bl      DVDReset
/* 0AE4B8 800B3A58 38600000 */  li      r3, 0
/* 0AE4BC 800B3A5C 4BFFF705 */  bl      cbForStateError
/* 0AE4C0 800B3A60 480000C4 */  b       lbl_800B3B24
lbl_800B3A64:
/* 0AE4C4 800B3A64 546007BD */  rlwinm. r0, r3, 0, 0x1e, 0x1e
/* 0AE4C8 800B3A68 4182002C */  beq     lbl_800B3A94
/* 0AE4CC 800B3A6C 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE4D0 800B3A70 3800FFFF */  li      r0, -1
/* 0AE4D4 800B3A74 3C600123 */  lis     r3, 0x123
/* 0AE4D8 800B3A78 9004000C */  stw     r0, 0xc(r4)
/* 0AE4DC 800B3A7C 38634567 */  addi    r3, r3, 0x4567
/* 0AE4E0 800B3A80 48001F39 */  bl      __DVDStoreErrorCode
/* 0AE4E4 800B3A84 3C60800B */  lis     r3, cbForStateError@ha
/* 0AE4E8 800B3A88 38633160 */  addi    r3, r3, cbForStateError@l
/* 0AE4EC 800B3A8C 4BFFE7A1 */  bl      DVDLowStopMotor
/* 0AE4F0 800B3A90 48000094 */  b       lbl_800B3B24
lbl_800B3A94:
/* 0AE4F4 800B3A94 38800000 */  li      r4, 0
/* 0AE4F8 800B3A98 908D8D64 */  stw     r4, NumInternalRetry-_SDA_BASE_(r13)
/* 0AE4FC 800B3A9C 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AE500 800B3AA0 28000000 */  cmplwi  r0, 0
/* 0AE504 800B3AA4 41820068 */  beq     lbl_800B3B0C
/* 0AE508 800B3AA8 38000001 */  li      r0, 1
/* 0AE50C 800B3AAC 83ED8D30 */  lwz     r31, executing-_SDA_BASE_(r13)
/* 0AE510 800B3AB0 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
/* 0AE514 800B3AB4 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0AE518 800B3AB8 386325E0 */  addi    r3, r3, DummyCommandBlock@l
/* 0AE51C 800B3ABC 908D8D50 */  stw     r4, Canceling-_SDA_BASE_(r13)
/* 0AE520 800B3AC0 3800000A */  li      r0, 0xa
/* 0AE524 800B3AC4 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AE528 800B3AC8 901F000C */  stw     r0, 0xc(r31)
/* 0AE52C 800B3ACC 819F0028 */  lwz     r12, 0x28(r31)
/* 0AE530 800B3AD0 280C0000 */  cmplwi  r12, 0
/* 0AE534 800B3AD4 41820014 */  beq     lbl_800B3AE8
/* 0AE538 800B3AD8 7D8803A6 */  mtlr    r12
/* 0AE53C 800B3ADC 389F0000 */  addi    r4, r31, 0
/* 0AE540 800B3AE0 3860FFFD */  li      r3, -3
/* 0AE544 800B3AE4 4E800021 */  blrl    
lbl_800B3AE8:
/* 0AE548 800B3AE8 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0AE54C 800B3AEC 280C0000 */  cmplwi  r12, 0
/* 0AE550 800B3AF0 41820014 */  beq     lbl_800B3B04
/* 0AE554 800B3AF4 7D8803A6 */  mtlr    r12
/* 0AE558 800B3AF8 389F0000 */  addi    r4, r31, 0
/* 0AE55C 800B3AFC 38600000 */  li      r3, 0
/* 0AE560 800B3B00 4E800021 */  blrl    
lbl_800B3B04:
/* 0AE564 800B3B04 480004D1 */  bl      stateReady
/* 0AE568 800B3B08 38800001 */  li      r4, 1
lbl_800B3B0C:
/* 0AE56C 800B3B0C 2C040000 */  cmpwi   r4, 0
/* 0AE570 800B3B10 40820014 */  bne     lbl_800B3B24
/* 0AE574 800B3B14 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE578 800B3B18 38000006 */  li      r0, 6
/* 0AE57C 800B3B1C 9003000C */  stw     r0, 0xc(r3)
/* 0AE580 800B3B20 480003A9 */  bl      stateMotorStopped
lbl_800B3B24:
/* 0AE584 800B3B24 8001001C */  lwz     r0, 0x1c(r1)
/* 0AE588 800B3B28 83E10014 */  lwz     r31, 0x14(r1)
/* 0AE58C 800B3B2C 38210018 */  addi    r1, r1, 0x18
/* 0AE590 800B3B30 7C0803A6 */  mtlr    r0
/* 0AE594 800B3B34 4E800020 */  blr     

cbForStateCheckID2:
/* 0AE598 800B3B38 7C0802A6 */  mflr    r0
/* 0AE59C 800B3B3C 28030010 */  cmplwi  r3, 0x10
/* 0AE5A0 800B3B40 90010004 */  stw     r0, 4(r1)
/* 0AE5A4 800B3B44 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AE5A8 800B3B48 93E10014 */  stw     r31, 0x14(r1)
/* 0AE5AC 800B3B4C 4082002C */  bne     lbl_800B3B78
/* 0AE5B0 800B3B50 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE5B4 800B3B54 3800FFFF */  li      r0, -1
/* 0AE5B8 800B3B58 3C600123 */  lis     r3, 0x123
/* 0AE5BC 800B3B5C 9004000C */  stw     r0, 0xc(r4)
/* 0AE5C0 800B3B60 38634568 */  addi    r3, r3, 0x4568
/* 0AE5C4 800B3B64 48001E55 */  bl      __DVDStoreErrorCode
/* 0AE5C8 800B3B68 48001401 */  bl      DVDReset
/* 0AE5CC 800B3B6C 38600000 */  li      r3, 0
/* 0AE5D0 800B3B70 4BFFF5F1 */  bl      cbForStateError
/* 0AE5D4 800B3B74 48000094 */  b       lbl_800B3C08
lbl_800B3B78:
/* 0AE5D8 800B3B78 546007FF */  clrlwi. r0, r3, 0x1f
/* 0AE5DC 800B3B7C 41820080 */  beq     lbl_800B3BFC
/* 0AE5E0 800B3B80 3C60800B */  lis     r3, stateReadingFST@ha
/* 0AE5E4 800B3B84 808D8D38 */  lwz     r4, bootInfo-_SDA_BASE_(r13)
/* 0AE5E8 800B3B88 38033040 */  addi    r0, r3, stateReadingFST@l
/* 0AE5EC 800B3B8C 38A00000 */  li      r5, 0
/* 0AE5F0 800B3B90 900D8D74 */  stw     r0, LastState-_SDA_BASE_(r13)
/* 0AE5F4 800B3B94 3C608013 */  lis     r3, BB2@ha
/* 0AE5F8 800B3B98 90AD8D64 */  stw     r5, NumInternalRetry-_SDA_BASE_(r13)
/* 0AE5FC 800B3B9C 386325A0 */  addi    r3, r3, BB2@l
/* 0AE600 800B3BA0 3BE30008 */  addi    r31, r3, 8
/* 0AE604 800B3BA4 8064003C */  lwz     r3, 0x3c(r4)
/* 0AE608 800B3BA8 801F0000 */  lwz     r0, 0(r31)
/* 0AE60C 800B3BAC 7C030040 */  cmplw   r3, r0
/* 0AE610 800B3BB0 4080001C */  bge     lbl_800B3BCC
/* 0AE614 800B3BB4 3C60800F */  lis     r3, D_800F24B4@ha
/* 0AE618 800B3BB8 4CC63182 */  crclr   6
/* 0AE61C 800B3BBC 38A324B4 */  addi    r5, r3, D_800F24B4@l
/* 0AE620 800B3BC0 386D8824 */  addi    r3, r13, D_80135504-_SDA_BASE_
/* 0AE624 800B3BC4 3880028A */  li      r4, 0x28a
/* 0AE628 800B3BC8 4BFEAAB1 */  bl      OSPanic
lbl_800B3BCC:
/* 0AE62C 800B3BCC 3C608013 */  lis     r3, BB2@ha
/* 0AE630 800B3BD0 80DF0000 */  lwz     r6, 0(r31)
/* 0AE634 800B3BD4 38A325A0 */  addi    r5, r3, BB2@l
/* 0AE638 800B3BD8 80ED8D38 */  lwz     r7, bootInfo-_SDA_BASE_(r13)
/* 0AE63C 800B3BDC 3C80800B */  lis     r4, cbForStateReadingFST@ha
/* 0AE640 800B3BE0 80A50004 */  lwz     r5, 4(r5)
/* 0AE644 800B3BE4 3806001F */  addi    r0, r6, 0x1f
/* 0AE648 800B3BE8 80670038 */  lwz     r3, 0x38(r7)
/* 0AE64C 800B3BEC 38C430D4 */  addi    r6, r4, cbForStateReadingFST@l
/* 0AE650 800B3BF0 54040034 */  rlwinm  r4, r0, 0, 0, 0x1a
/* 0AE654 800B3BF4 4BFFE23D */  bl      DVDLowRead
/* 0AE658 800B3BF8 48000010 */  b       lbl_800B3C08
lbl_800B3BFC:
/* 0AE65C 800B3BFC 3C60800B */  lis     r3, cbForStateGettingError@ha
/* 0AE660 800B3C00 3863331C */  addi    r3, r3, cbForStateGettingError@l
/* 0AE664 800B3C04 4BFFE6B5 */  bl      DVDLowRequestError
lbl_800B3C08:
/* 0AE668 800B3C08 8001001C */  lwz     r0, 0x1c(r1)
/* 0AE66C 800B3C0C 83E10014 */  lwz     r31, 0x14(r1)
/* 0AE670 800B3C10 38210018 */  addi    r1, r1, 0x18
/* 0AE674 800B3C14 7C0803A6 */  mtlr    r0
/* 0AE678 800B3C18 4E800020 */  blr     

cbForStateCheckID3:
/* 0AE67C 800B3C1C 7C0802A6 */  mflr    r0
/* 0AE680 800B3C20 28030010 */  cmplwi  r3, 0x10
/* 0AE684 800B3C24 90010004 */  stw     r0, 4(r1)
/* 0AE688 800B3C28 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AE68C 800B3C2C 93E10014 */  stw     r31, 0x14(r1)
/* 0AE690 800B3C30 4082002C */  bne     lbl_800B3C5C
/* 0AE694 800B3C34 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE698 800B3C38 3800FFFF */  li      r0, -1
/* 0AE69C 800B3C3C 3C600123 */  lis     r3, 0x123
/* 0AE6A0 800B3C40 9004000C */  stw     r0, 0xc(r4)
/* 0AE6A4 800B3C44 38634568 */  addi    r3, r3, 0x4568
/* 0AE6A8 800B3C48 48001D71 */  bl      __DVDStoreErrorCode
/* 0AE6AC 800B3C4C 4800131D */  bl      DVDReset
/* 0AE6B0 800B3C50 38600000 */  li      r3, 0
/* 0AE6B4 800B3C54 4BFFF50D */  bl      cbForStateError
/* 0AE6B8 800B3C58 480000AC */  b       lbl_800B3D04
lbl_800B3C5C:
/* 0AE6BC 800B3C5C 546007FF */  clrlwi. r0, r3, 0x1f
/* 0AE6C0 800B3C60 41820098 */  beq     lbl_800B3CF8
/* 0AE6C4 800B3C64 38800000 */  li      r4, 0
/* 0AE6C8 800B3C68 908D8D64 */  stw     r4, NumInternalRetry-_SDA_BASE_(r13)
/* 0AE6CC 800B3C6C 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AE6D0 800B3C70 28000000 */  cmplwi  r0, 0
/* 0AE6D4 800B3C74 41820064 */  beq     lbl_800B3CD8
/* 0AE6D8 800B3C78 908D8D58 */  stw     r4, ResumeFromHere-_SDA_BASE_(r13)
/* 0AE6DC 800B3C7C 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0AE6E0 800B3C80 83ED8D30 */  lwz     r31, executing-_SDA_BASE_(r13)
/* 0AE6E4 800B3C84 386325E0 */  addi    r3, r3, DummyCommandBlock@l
/* 0AE6E8 800B3C88 908D8D50 */  stw     r4, Canceling-_SDA_BASE_(r13)
/* 0AE6EC 800B3C8C 3800000A */  li      r0, 0xa
/* 0AE6F0 800B3C90 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AE6F4 800B3C94 901F000C */  stw     r0, 0xc(r31)
/* 0AE6F8 800B3C98 819F0028 */  lwz     r12, 0x28(r31)
/* 0AE6FC 800B3C9C 280C0000 */  cmplwi  r12, 0
/* 0AE700 800B3CA0 41820014 */  beq     lbl_800B3CB4
/* 0AE704 800B3CA4 7D8803A6 */  mtlr    r12
/* 0AE708 800B3CA8 389F0000 */  addi    r4, r31, 0
/* 0AE70C 800B3CAC 3860FFFD */  li      r3, -3
/* 0AE710 800B3CB0 4E800021 */  blrl    
lbl_800B3CB4:
/* 0AE714 800B3CB4 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0AE718 800B3CB8 280C0000 */  cmplwi  r12, 0
/* 0AE71C 800B3CBC 41820014 */  beq     lbl_800B3CD0
/* 0AE720 800B3CC0 7D8803A6 */  mtlr    r12
/* 0AE724 800B3CC4 389F0000 */  addi    r4, r31, 0
/* 0AE728 800B3CC8 38600000 */  li      r3, 0
/* 0AE72C 800B3CCC 4E800021 */  blrl    
lbl_800B3CD0:
/* 0AE730 800B3CD0 48000305 */  bl      stateReady
/* 0AE734 800B3CD4 38800001 */  li      r4, 1
lbl_800B3CD8:
/* 0AE738 800B3CD8 2C040000 */  cmpwi   r4, 0
/* 0AE73C 800B3CDC 40820028 */  bne     lbl_800B3D04
/* 0AE740 800B3CE0 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE744 800B3CE4 38000001 */  li      r0, 1
/* 0AE748 800B3CE8 9003000C */  stw     r0, 0xc(r3)
/* 0AE74C 800B3CEC 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE750 800B3CF0 48000515 */  bl      stateBusy
/* 0AE754 800B3CF4 48000010 */  b       lbl_800B3D04
lbl_800B3CF8:
/* 0AE758 800B3CF8 3C60800B */  lis     r3, cbForStateGettingError@ha
/* 0AE75C 800B3CFC 3863331C */  addi    r3, r3, cbForStateGettingError@l
/* 0AE760 800B3D00 4BFFE5B9 */  bl      DVDLowRequestError
lbl_800B3D04:
/* 0AE764 800B3D04 8001001C */  lwz     r0, 0x1c(r1)
/* 0AE768 800B3D08 83E10014 */  lwz     r31, 0x14(r1)
/* 0AE76C 800B3D0C 38210018 */  addi    r1, r1, 0x18
/* 0AE770 800B3D10 7C0803A6 */  mtlr    r0
/* 0AE774 800B3D14 4E800020 */  blr     

AlarmHandler:
/* 0AE778 800B3D18 7C0802A6 */  mflr    r0
/* 0AE77C 800B3D1C 90010004 */  stw     r0, 4(r1)
/* 0AE780 800B3D20 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE784 800B3D24 48001245 */  bl      DVDReset
/* 0AE788 800B3D28 3C608013 */  lis     r3, CurrDiskID@ha
/* 0AE78C 800B3D2C 386325C0 */  addi    r3, r3, CurrDiskID@l
/* 0AE790 800B3D30 38800020 */  li      r4, 0x20
/* 0AE794 800B3D34 4BFE9A1D */  bl      DCInvalidateRange
/* 0AE798 800B3D38 3C80800B */  lis     r4, stateCoverClosed_CMD@ha
/* 0AE79C 800B3D3C 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE7A0 800B3D40 38043E28 */  addi    r0, r4, stateCoverClosed_CMD@l
/* 0AE7A4 800B3D44 900D8D74 */  stw     r0, LastState-_SDA_BASE_(r13)
/* 0AE7A8 800B3D48 480000E1 */  bl      stateCoverClosed_CMD
/* 0AE7AC 800B3D4C 8001000C */  lwz     r0, 0xc(r1)
/* 0AE7B0 800B3D50 38210008 */  addi    r1, r1, 8
/* 0AE7B4 800B3D54 7C0803A6 */  mtlr    r0
/* 0AE7B8 800B3D58 4E800020 */  blr     

stateCoverClosed:
/* 0AE7BC 800B3D5C 7C0802A6 */  mflr    r0
/* 0AE7C0 800B3D60 3C608013 */  lis     r3, BB2@ha
/* 0AE7C4 800B3D64 90010004 */  stw     r0, 4(r1)
/* 0AE7C8 800B3D68 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0AE7CC 800B3D6C 93E1000C */  stw     r31, 0xc(r1)
/* 0AE7D0 800B3D70 3BE325A0 */  addi    r31, r3, BB2@l
/* 0AE7D4 800B3D74 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AE7D8 800B3D78 2C00000D */  cmpwi   r0, 0xd
/* 0AE7DC 800B3D7C 41820028 */  beq     lbl_800B3DA4
/* 0AE7E0 800B3D80 40800018 */  bge     lbl_800B3D98
/* 0AE7E4 800B3D84 2C000006 */  cmpwi   r0, 6
/* 0AE7E8 800B3D88 4080004C */  bge     lbl_800B3DD4
/* 0AE7EC 800B3D8C 2C000004 */  cmpwi   r0, 4
/* 0AE7F0 800B3D90 40800014 */  bge     lbl_800B3DA4
/* 0AE7F4 800B3D94 48000040 */  b       lbl_800B3DD4
lbl_800B3D98:
/* 0AE7F8 800B3D98 2C00000F */  cmpwi   r0, 0xf
/* 0AE7FC 800B3D9C 41820008 */  beq     lbl_800B3DA4
/* 0AE800 800B3DA0 48000034 */  b       lbl_800B3DD4
lbl_800B3DA4:
/* 0AE804 800B3DA4 48001901 */  bl      __DVDClearWaitingQueue
/* 0AE808 800B3DA8 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE80C 800B3DAC 381F0040 */  addi    r0, r31, 0x40
/* 0AE810 800B3DB0 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AE814 800B3DB4 81840028 */  lwz     r12, 0x28(r4)
/* 0AE818 800B3DB8 280C0000 */  cmplwi  r12, 0
/* 0AE81C 800B3DBC 41820010 */  beq     lbl_800B3DCC
/* 0AE820 800B3DC0 7D8803A6 */  mtlr    r12
/* 0AE824 800B3DC4 3860FFFC */  li      r3, -4
/* 0AE828 800B3DC8 4E800021 */  blrl    
lbl_800B3DCC:
/* 0AE82C 800B3DCC 48000209 */  bl      stateReady
/* 0AE830 800B3DD0 48000044 */  b       lbl_800B3E14
lbl_800B3DD4:
/* 0AE834 800B3DD4 48001195 */  bl      DVDReset
/* 0AE838 800B3DD8 387F0070 */  addi    r3, r31, 0x70
/* 0AE83C 800B3DDC 4BFE8939 */  bl      OSCreateAlarm
/* 0AE840 800B3DE0 3C608000 */  lis     r3, 0x8000
/* 0AE844 800B3DE4 800300F8 */  lwz     r0, 0xf8(r3)
/* 0AE848 800B3DE8 3C801062 */  lis     r4, 0x1062
/* 0AE84C 800B3DEC 3C60800B */  lis     r3, AlarmHandler@ha
/* 0AE850 800B3DF0 5400F0BE */  srwi    r0, r0, 2
/* 0AE854 800B3DF4 38844DD3 */  addi    r4, r4, 0x4dd3
/* 0AE858 800B3DF8 7C040016 */  mulhwu  r0, r4, r0
/* 0AE85C 800B3DFC 5400D1BE */  srwi    r0, r0, 6
/* 0AE860 800B3E00 1CC0047E */  mulli   r6, r0, 0x47e
/* 0AE864 800B3E04 38E33D18 */  addi    r7, r3, AlarmHandler@l
/* 0AE868 800B3E08 387F0070 */  addi    r3, r31, 0x70
/* 0AE86C 800B3E0C 38A00000 */  li      r5, 0
/* 0AE870 800B3E10 4BFE8B65 */  bl      OSSetAlarm
lbl_800B3E14:
/* 0AE874 800B3E14 80010014 */  lwz     r0, 0x14(r1)
/* 0AE878 800B3E18 83E1000C */  lwz     r31, 0xc(r1)
/* 0AE87C 800B3E1C 38210010 */  addi    r1, r1, 0x10
/* 0AE880 800B3E20 7C0803A6 */  mtlr    r0
/* 0AE884 800B3E24 4E800020 */  blr     

stateCoverClosed_CMD:
/* 0AE888 800B3E28 7C0802A6 */  mflr    r0
/* 0AE88C 800B3E2C 3C608013 */  lis     r3, CurrDiskID@ha
/* 0AE890 800B3E30 90010004 */  stw     r0, 4(r1)
/* 0AE894 800B3E34 3C80800B */  lis     r4, cbForStateCoverClosed@ha
/* 0AE898 800B3E38 386325C0 */  addi    r3, r3, CurrDiskID@l
/* 0AE89C 800B3E3C 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE8A0 800B3E40 38843E58 */  addi    r4, r4, cbForStateCoverClosed@l
/* 0AE8A4 800B3E44 4BFFE345 */  bl      DVDLowReadDiskID
/* 0AE8A8 800B3E48 8001000C */  lwz     r0, 0xc(r1)
/* 0AE8AC 800B3E4C 38210008 */  addi    r1, r1, 8
/* 0AE8B0 800B3E50 7C0803A6 */  mtlr    r0
/* 0AE8B4 800B3E54 4E800020 */  blr     

cbForStateCoverClosed:
/* 0AE8B8 800B3E58 7C0802A6 */  mflr    r0
/* 0AE8BC 800B3E5C 28030010 */  cmplwi  r3, 0x10
/* 0AE8C0 800B3E60 90010004 */  stw     r0, 4(r1)
/* 0AE8C4 800B3E64 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE8C8 800B3E68 4082002C */  bne     lbl_800B3E94
/* 0AE8CC 800B3E6C 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE8D0 800B3E70 3800FFFF */  li      r0, -1
/* 0AE8D4 800B3E74 3C600123 */  lis     r3, 0x123
/* 0AE8D8 800B3E78 9004000C */  stw     r0, 0xc(r4)
/* 0AE8DC 800B3E7C 38634568 */  addi    r3, r3, 0x4568
/* 0AE8E0 800B3E80 48001B39 */  bl      __DVDStoreErrorCode
/* 0AE8E4 800B3E84 480010E5 */  bl      DVDReset
/* 0AE8E8 800B3E88 38600000 */  li      r3, 0
/* 0AE8EC 800B3E8C 4BFFF2D5 */  bl      cbForStateError
/* 0AE8F0 800B3E90 48000028 */  b       lbl_800B3EB8
lbl_800B3E94:
/* 0AE8F4 800B3E94 546007FF */  clrlwi. r0, r3, 0x1f
/* 0AE8F8 800B3E98 41820014 */  beq     lbl_800B3EAC
/* 0AE8FC 800B3E9C 38000000 */  li      r0, 0
/* 0AE900 800B3EA0 900D8D64 */  stw     r0, NumInternalRetry-_SDA_BASE_(r13)
/* 0AE904 800B3EA4 4BFFF98D */  bl      stateCheckID
/* 0AE908 800B3EA8 48000010 */  b       lbl_800B3EB8
lbl_800B3EAC:
/* 0AE90C 800B3EAC 3C60800B */  lis     r3, cbForStateGettingError@ha
/* 0AE910 800B3EB0 3863331C */  addi    r3, r3, cbForStateGettingError@l
/* 0AE914 800B3EB4 4BFFE405 */  bl      DVDLowRequestError
lbl_800B3EB8:
/* 0AE918 800B3EB8 8001000C */  lwz     r0, 0xc(r1)
/* 0AE91C 800B3EBC 38210008 */  addi    r1, r1, 8
/* 0AE920 800B3EC0 7C0803A6 */  mtlr    r0
/* 0AE924 800B3EC4 4E800020 */  blr     

stateMotorStopped:
/* 0AE928 800B3EC8 7C0802A6 */  mflr    r0
/* 0AE92C 800B3ECC 3C60800B */  lis     r3, cbForStateMotorStopped@ha
/* 0AE930 800B3ED0 90010004 */  stw     r0, 4(r1)
/* 0AE934 800B3ED4 38633EF0 */  addi    r3, r3, cbForStateMotorStopped@l
/* 0AE938 800B3ED8 9421FFF8 */  stwu    r1, -8(r1)
/* 0AE93C 800B3EDC 4BFFE281 */  bl      DVDLowWaitCoverClose
/* 0AE940 800B3EE0 8001000C */  lwz     r0, 0xc(r1)
/* 0AE944 800B3EE4 38210008 */  addi    r1, r1, 8
/* 0AE948 800B3EE8 7C0803A6 */  mtlr    r0
/* 0AE94C 800B3EEC 4E800020 */  blr     

cbForStateMotorStopped:
/* 0AE950 800B3EF0 7C0802A6 */  mflr    r0
/* 0AE954 800B3EF4 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AE958 800B3EF8 90010004 */  stw     r0, 4(r1)
/* 0AE95C 800B3EFC 38000000 */  li      r0, 0
/* 0AE960 800B3F00 3C808013 */  lis     r4, BB2@ha
/* 0AE964 800B3F04 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AE968 800B3F08 93E10014 */  stw     r31, 0x14(r1)
/* 0AE96C 800B3F0C 3BE425A0 */  addi    r31, r4, BB2@l
/* 0AE970 800B3F10 90036004 */  stw     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AE974 800B3F14 38000003 */  li      r0, 3
/* 0AE978 800B3F18 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AE97C 800B3F1C 9003000C */  stw     r0, 0xc(r3)
/* 0AE980 800B3F20 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AE984 800B3F24 2C00000D */  cmpwi   r0, 0xd
/* 0AE988 800B3F28 41820028 */  beq     lbl_800B3F50
/* 0AE98C 800B3F2C 40800018 */  bge     lbl_800B3F44
/* 0AE990 800B3F30 2C000006 */  cmpwi   r0, 6
/* 0AE994 800B3F34 4080004C */  bge     lbl_800B3F80
/* 0AE998 800B3F38 2C000004 */  cmpwi   r0, 4
/* 0AE99C 800B3F3C 40800014 */  bge     lbl_800B3F50
/* 0AE9A0 800B3F40 48000040 */  b       lbl_800B3F80
lbl_800B3F44:
/* 0AE9A4 800B3F44 2C00000F */  cmpwi   r0, 0xf
/* 0AE9A8 800B3F48 41820008 */  beq     lbl_800B3F50
/* 0AE9AC 800B3F4C 48000034 */  b       lbl_800B3F80
lbl_800B3F50:
/* 0AE9B0 800B3F50 48001755 */  bl      __DVDClearWaitingQueue
/* 0AE9B4 800B3F54 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AE9B8 800B3F58 381F0040 */  addi    r0, r31, 0x40
/* 0AE9BC 800B3F5C 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AE9C0 800B3F60 81840028 */  lwz     r12, 0x28(r4)
/* 0AE9C4 800B3F64 280C0000 */  cmplwi  r12, 0
/* 0AE9C8 800B3F68 41820010 */  beq     lbl_800B3F78
/* 0AE9CC 800B3F6C 7D8803A6 */  mtlr    r12
/* 0AE9D0 800B3F70 3860FFFC */  li      r3, -4
/* 0AE9D4 800B3F74 4E800021 */  blrl    
lbl_800B3F78:
/* 0AE9D8 800B3F78 4800005D */  bl      stateReady
/* 0AE9DC 800B3F7C 48000044 */  b       lbl_800B3FC0
lbl_800B3F80:
/* 0AE9E0 800B3F80 48000FE9 */  bl      DVDReset
/* 0AE9E4 800B3F84 387F0070 */  addi    r3, r31, 0x70
/* 0AE9E8 800B3F88 4BFE878D */  bl      OSCreateAlarm
/* 0AE9EC 800B3F8C 3C608000 */  lis     r3, 0x8000
/* 0AE9F0 800B3F90 800300F8 */  lwz     r0, 0xf8(r3)
/* 0AE9F4 800B3F94 3C801062 */  lis     r4, 0x1062
/* 0AE9F8 800B3F98 3C60800B */  lis     r3, AlarmHandler@ha
/* 0AE9FC 800B3F9C 5400F0BE */  srwi    r0, r0, 2
/* 0AEA00 800B3FA0 38844DD3 */  addi    r4, r4, 0x4dd3
/* 0AEA04 800B3FA4 7C040016 */  mulhwu  r0, r4, r0
/* 0AEA08 800B3FA8 5400D1BE */  srwi    r0, r0, 6
/* 0AEA0C 800B3FAC 1CC0047E */  mulli   r6, r0, 0x47e
/* 0AEA10 800B3FB0 38E33D18 */  addi    r7, r3, AlarmHandler@l
/* 0AEA14 800B3FB4 387F0070 */  addi    r3, r31, 0x70
/* 0AEA18 800B3FB8 38A00000 */  li      r5, 0
/* 0AEA1C 800B3FBC 4BFE89B9 */  bl      OSSetAlarm
lbl_800B3FC0:
/* 0AEA20 800B3FC0 8001001C */  lwz     r0, 0x1c(r1)
/* 0AEA24 800B3FC4 83E10014 */  lwz     r31, 0x14(r1)
/* 0AEA28 800B3FC8 38210018 */  addi    r1, r1, 0x18
/* 0AEA2C 800B3FCC 7C0803A6 */  mtlr    r0
/* 0AEA30 800B3FD0 4E800020 */  blr     

stateReady:
/* 0AEA34 800B3FD4 7C0802A6 */  mflr    r0
/* 0AEA38 800B3FD8 3C608013 */  lis     r3, BB2@ha
/* 0AEA3C 800B3FDC 90010004 */  stw     r0, 4(r1)
/* 0AEA40 800B3FE0 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0AEA44 800B3FE4 93E1000C */  stw     r31, 0xc(r1)
/* 0AEA48 800B3FE8 3BE325A0 */  addi    r31, r3, BB2@l
/* 0AEA4C 800B3FEC 480017F9 */  bl      __DVDCheckWaitingQueue
/* 0AEA50 800B3FF0 2C030000 */  cmpwi   r3, 0
/* 0AEA54 800B3FF4 40820010 */  bne     lbl_800B4004
/* 0AEA58 800B3FF8 38000000 */  li      r0, 0
/* 0AEA5C 800B3FFC 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AEA60 800B4000 480001F0 */  b       lbl_800B41F0
lbl_800B4004:
/* 0AEA64 800B4004 800D8D3C */  lwz     r0, PauseFlag-_SDA_BASE_(r13)
/* 0AEA68 800B4008 2C000000 */  cmpwi   r0, 0
/* 0AEA6C 800B400C 41820018 */  beq     lbl_800B4024
/* 0AEA70 800B4010 38600001 */  li      r3, 1
/* 0AEA74 800B4014 38000000 */  li      r0, 0
/* 0AEA78 800B4018 906D8D40 */  stw     r3, PausingFlag-_SDA_BASE_(r13)
/* 0AEA7C 800B401C 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AEA80 800B4020 480001D0 */  b       lbl_800B41F0
lbl_800B4024:
/* 0AEA84 800B4024 48001721 */  bl      __DVDPopWaitingQueue
/* 0AEA88 800B4028 800D8D48 */  lwz     r0, FatalErrorFlag-_SDA_BASE_(r13)
/* 0AEA8C 800B402C 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AEA90 800B4030 2C000000 */  cmpwi   r0, 0
/* 0AEA94 800B4034 4182003C */  beq     lbl_800B4070
/* 0AEA98 800B4038 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AEA9C 800B403C 3880FFFF */  li      r4, -1
/* 0AEAA0 800B4040 381F0040 */  addi    r0, r31, 0x40
/* 0AEAA4 800B4044 9083000C */  stw     r4, 0xc(r3)
/* 0AEAA8 800B4048 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AEAAC 800B404C 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AEAB0 800B4050 81840028 */  lwz     r12, 0x28(r4)
/* 0AEAB4 800B4054 280C0000 */  cmplwi  r12, 0
/* 0AEAB8 800B4058 41820010 */  beq     lbl_800B4068
/* 0AEABC 800B405C 7D8803A6 */  mtlr    r12
/* 0AEAC0 800B4060 3860FFFF */  li      r3, -1
/* 0AEAC4 800B4064 4E800021 */  blrl    
lbl_800B4068:
/* 0AEAC8 800B4068 4BFFFF6D */  bl      stateReady
/* 0AEACC 800B406C 48000184 */  b       lbl_800B41F0
lbl_800B4070:
/* 0AEAD0 800B4070 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AEAD4 800B4074 80040008 */  lwz     r0, 8(r4)
/* 0AEAD8 800B4078 900D8D4C */  stw     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AEADC 800B407C 800D8D58 */  lwz     r0, ResumeFromHere-_SDA_BASE_(r13)
/* 0AEAE0 800B4080 28000000 */  cmplwi  r0, 0
/* 0AEAE4 800B4084 4182015C */  beq     lbl_800B41E0
/* 0AEAE8 800B4088 800D8D58 */  lwz     r0, ResumeFromHere-_SDA_BASE_(r13)
/* 0AEAEC 800B408C 2C000004 */  cmpwi   r0, 4
/* 0AEAF0 800B4090 41820064 */  beq     lbl_800B40F4
/* 0AEAF4 800B4094 4080001C */  bge     lbl_800B40B0
/* 0AEAF8 800B4098 2C000002 */  cmpwi   r0, 2
/* 0AEAFC 800B409C 41820028 */  beq     lbl_800B40C4
/* 0AEB00 800B40A0 4080003C */  bge     lbl_800B40DC
/* 0AEB04 800B40A4 2C000001 */  cmpwi   r0, 1
/* 0AEB08 800B40A8 40800064 */  bge     lbl_800B410C
/* 0AEB0C 800B40AC 48000128 */  b       lbl_800B41D4
lbl_800B40B0:
/* 0AEB10 800B40B0 2C000008 */  cmpwi   r0, 8
/* 0AEB14 800B40B4 40800120 */  bge     lbl_800B41D4
/* 0AEB18 800B40B8 2C000006 */  cmpwi   r0, 6
/* 0AEB1C 800B40BC 40800050 */  bge     lbl_800B410C
/* 0AEB20 800B40C0 480000F8 */  b       lbl_800B41B8
lbl_800B40C4:
/* 0AEB24 800B40C4 3800000B */  li      r0, 0xb
/* 0AEB28 800B40C8 3C60800B */  lis     r3, cbForStateMotorStopped@ha
/* 0AEB2C 800B40CC 9004000C */  stw     r0, 0xc(r4)
/* 0AEB30 800B40D0 38633EF0 */  addi    r3, r3, cbForStateMotorStopped@l
/* 0AEB34 800B40D4 4BFFE089 */  bl      DVDLowWaitCoverClose
/* 0AEB38 800B40D8 480000FC */  b       lbl_800B41D4
lbl_800B40DC:
/* 0AEB3C 800B40DC 38000004 */  li      r0, 4
/* 0AEB40 800B40E0 3C60800B */  lis     r3, cbForStateMotorStopped@ha
/* 0AEB44 800B40E4 9004000C */  stw     r0, 0xc(r4)
/* 0AEB48 800B40E8 38633EF0 */  addi    r3, r3, cbForStateMotorStopped@l
/* 0AEB4C 800B40EC 4BFFE071 */  bl      DVDLowWaitCoverClose
/* 0AEB50 800B40F0 480000E4 */  b       lbl_800B41D4
lbl_800B40F4:
/* 0AEB54 800B40F4 38000005 */  li      r0, 5
/* 0AEB58 800B40F8 3C60800B */  lis     r3, cbForStateMotorStopped@ha
/* 0AEB5C 800B40FC 9004000C */  stw     r0, 0xc(r4)
/* 0AEB60 800B4100 38633EF0 */  addi    r3, r3, cbForStateMotorStopped@l
/* 0AEB64 800B4104 4BFFE059 */  bl      DVDLowWaitCoverClose
/* 0AEB68 800B4108 480000CC */  b       lbl_800B41D4
lbl_800B410C:
/* 0AEB6C 800B410C 38000003 */  li      r0, 3
/* 0AEB70 800B4110 9004000C */  stw     r0, 0xc(r4)
/* 0AEB74 800B4114 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AEB78 800B4118 2C00000D */  cmpwi   r0, 0xd
/* 0AEB7C 800B411C 41820028 */  beq     lbl_800B4144
/* 0AEB80 800B4120 40800018 */  bge     lbl_800B4138
/* 0AEB84 800B4124 2C000006 */  cmpwi   r0, 6
/* 0AEB88 800B4128 4080004C */  bge     lbl_800B4174
/* 0AEB8C 800B412C 2C000004 */  cmpwi   r0, 4
/* 0AEB90 800B4130 40800014 */  bge     lbl_800B4144
/* 0AEB94 800B4134 48000040 */  b       lbl_800B4174
lbl_800B4138:
/* 0AEB98 800B4138 2C00000F */  cmpwi   r0, 0xf
/* 0AEB9C 800B413C 41820008 */  beq     lbl_800B4144
/* 0AEBA0 800B4140 48000034 */  b       lbl_800B4174
lbl_800B4144:
/* 0AEBA4 800B4144 48001561 */  bl      __DVDClearWaitingQueue
/* 0AEBA8 800B4148 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AEBAC 800B414C 381F0040 */  addi    r0, r31, 0x40
/* 0AEBB0 800B4150 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AEBB4 800B4154 81840028 */  lwz     r12, 0x28(r4)
/* 0AEBB8 800B4158 280C0000 */  cmplwi  r12, 0
/* 0AEBBC 800B415C 41820010 */  beq     lbl_800B416C
/* 0AEBC0 800B4160 7D8803A6 */  mtlr    r12
/* 0AEBC4 800B4164 3860FFFC */  li      r3, -4
/* 0AEBC8 800B4168 4E800021 */  blrl    
lbl_800B416C:
/* 0AEBCC 800B416C 4BFFFE69 */  bl      stateReady
/* 0AEBD0 800B4170 48000064 */  b       lbl_800B41D4
lbl_800B4174:
/* 0AEBD4 800B4174 48000DF5 */  bl      DVDReset
/* 0AEBD8 800B4178 387F0070 */  addi    r3, r31, 0x70
/* 0AEBDC 800B417C 4BFE8599 */  bl      OSCreateAlarm
/* 0AEBE0 800B4180 3C608000 */  lis     r3, 0x8000
/* 0AEBE4 800B4184 800300F8 */  lwz     r0, 0xf8(r3)
/* 0AEBE8 800B4188 3C801062 */  lis     r4, 0x1062
/* 0AEBEC 800B418C 3C60800B */  lis     r3, AlarmHandler@ha
/* 0AEBF0 800B4190 5400F0BE */  srwi    r0, r0, 2
/* 0AEBF4 800B4194 38844DD3 */  addi    r4, r4, 0x4dd3
/* 0AEBF8 800B4198 7C040016 */  mulhwu  r0, r4, r0
/* 0AEBFC 800B419C 5400D1BE */  srwi    r0, r0, 6
/* 0AEC00 800B41A0 1CC0047E */  mulli   r6, r0, 0x47e
/* 0AEC04 800B41A4 38E33D18 */  addi    r7, r3, AlarmHandler@l
/* 0AEC08 800B41A8 387F0070 */  addi    r3, r31, 0x70
/* 0AEC0C 800B41AC 38A00000 */  li      r5, 0
/* 0AEC10 800B41B0 4BFE87C5 */  bl      OSSetAlarm
/* 0AEC14 800B41B4 48000020 */  b       lbl_800B41D4
lbl_800B41B8:
/* 0AEC18 800B41B8 3800FFFF */  li      r0, -1
/* 0AEC1C 800B41BC 9004000C */  stw     r0, 0xc(r4)
/* 0AEC20 800B41C0 806D8D5C */  lwz     r3, CancelLastError-_SDA_BASE_(r13)
/* 0AEC24 800B41C4 480017F5 */  bl      __DVDStoreErrorCode
/* 0AEC28 800B41C8 3C60800B */  lis     r3, cbForStateError@ha
/* 0AEC2C 800B41CC 38633160 */  addi    r3, r3, cbForStateError@l
/* 0AEC30 800B41D0 4BFFE05D */  bl      DVDLowStopMotor
lbl_800B41D4:
/* 0AEC34 800B41D4 38000000 */  li      r0, 0
/* 0AEC38 800B41D8 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
/* 0AEC3C 800B41DC 48000014 */  b       lbl_800B41F0
lbl_800B41E0:
/* 0AEC40 800B41E0 38000001 */  li      r0, 1
/* 0AEC44 800B41E4 9004000C */  stw     r0, 0xc(r4)
/* 0AEC48 800B41E8 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AEC4C 800B41EC 48000019 */  bl      stateBusy
lbl_800B41F0:
/* 0AEC50 800B41F0 80010014 */  lwz     r0, 0x14(r1)
/* 0AEC54 800B41F4 83E1000C */  lwz     r31, 0xc(r1)
/* 0AEC58 800B41F8 38210010 */  addi    r1, r1, 0x10
/* 0AEC5C 800B41FC 7C0803A6 */  mtlr    r0
/* 0AEC60 800B4200 4E800020 */  blr     

stateBusy:
/* 0AEC64 800B4204 7C0802A6 */  mflr    r0
/* 0AEC68 800B4208 3C80800B */  lis     r4, stateBusy@ha
/* 0AEC6C 800B420C 90010004 */  stw     r0, 4(r1)
/* 0AEC70 800B4210 38044204 */  addi    r0, r4, stateBusy@l
/* 0AEC74 800B4214 7C671B78 */  mr      r7, r3
/* 0AEC78 800B4218 9421FFF8 */  stwu    r1, -8(r1)
/* 0AEC7C 800B421C 900D8D74 */  stw     r0, LastState-_SDA_BASE_(r13)
/* 0AEC80 800B4220 80030008 */  lwz     r0, 8(r3)
/* 0AEC84 800B4224 2800000F */  cmplwi  r0, 0xf
/* 0AEC88 800B4228 418102D4 */  bgt     lbl_800B44FC
/* 0AEC8C 800B422C 3C60800F */  lis     r3, jtbl_800F24E8@ha
/* 0AEC90 800B4230 386324E8 */  addi    r3, r3, jtbl_800F24E8@l
/* 0AEC94 800B4234 5400103A */  slwi    r0, r0, 2
/* 0AEC98 800B4238 7C03002E */  lwzx    r0, r3, r0
/* 0AEC9C 800B423C 7C0903A6 */  mtctr   r0
/* 0AECA0 800B4240 4E800420 */  bctr    
glabel lbl_800B4244
/* 0AECA4 800B4244 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AECA8 800B4248 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AECAC 800B424C 38A36000 */  addi    r5, r3, DI_REGS_BASE@l
/* 0AECB0 800B4250 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AECB4 800B4254 90050004 */  stw     r0, DI_DICVR(r5)
/* 0AECB8 800B4258 38000020 */  li      r0, 0x20
/* 0AECBC 800B425C 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AECC0 800B4260 9007001C */  stw     r0, 0x1c(r7)
/* 0AECC4 800B4264 80670018 */  lwz     r3, 0x18(r7)
/* 0AECC8 800B4268 4BFFDF21 */  bl      DVDLowReadDiskID
/* 0AECCC 800B426C 480002A8 */  b       lbl_800B4514
glabel lbl_800B4270
/* 0AECD0 800B4270 80070014 */  lwz     r0, 0x14(r7)
/* 0AECD4 800B4274 28000000 */  cmplwi  r0, 0
/* 0AECD8 800B4278 4082003C */  bne     lbl_800B42B4
/* 0AECDC 800B427C 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0AECE0 800B4280 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AECE4 800B4284 380325E0 */  addi    r0, r3, DummyCommandBlock@l
/* 0AECE8 800B4288 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AECEC 800B428C 38000000 */  li      r0, 0
/* 0AECF0 800B4290 9004000C */  stw     r0, 0xc(r4)
/* 0AECF4 800B4294 81840028 */  lwz     r12, 0x28(r4)
/* 0AECF8 800B4298 280C0000 */  cmplwi  r12, 0
/* 0AECFC 800B429C 41820010 */  beq     lbl_800B42AC
/* 0AED00 800B42A0 7D8803A6 */  mtlr    r12
/* 0AED04 800B42A4 38600000 */  li      r3, 0
/* 0AED08 800B42A8 4E800021 */  blrl    
lbl_800B42AC:
/* 0AED0C 800B42AC 4BFFFD29 */  bl      stateReady
/* 0AED10 800B42B0 48000264 */  b       lbl_800B4514
lbl_800B42B4:
/* 0AED14 800B42B4 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AED18 800B42B8 38636000 */  addi    r3, r3, DI_REGS_BASE@l
/* 0AED1C 800B42BC 80030004 */  lwz     r0, DI_DICVR(r3)
/* 0AED20 800B42C0 3C800008 */  lis     r4, 8
/* 0AED24 800B42C4 90030004 */  stw     r0, DI_DICVR(r3)
/* 0AED28 800B42C8 80670020 */  lwz     r3, 0x20(r7)
/* 0AED2C 800B42CC 80070014 */  lwz     r0, 0x14(r7)
/* 0AED30 800B42D0 7C030050 */  subf    r0, r3, r0
/* 0AED34 800B42D4 7C002040 */  cmplw   r0, r4
/* 0AED38 800B42D8 40810008 */  ble     lbl_800B42E0
/* 0AED3C 800B42DC 48000008 */  b       lbl_800B42E4
lbl_800B42E0:
/* 0AED40 800B42E0 7C040378 */  mr      r4, r0
lbl_800B42E4:
/* 0AED44 800B42E4 9087001C */  stw     r4, 0x1c(r7)
/* 0AED48 800B42E8 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AED4C 800B42EC 38C34524 */  addi    r6, r3, cbForStateBusy@l
/* 0AED50 800B42F0 80A70020 */  lwz     r5, 0x20(r7)
/* 0AED54 800B42F4 80670018 */  lwz     r3, 0x18(r7)
/* 0AED58 800B42F8 80070010 */  lwz     r0, 0x10(r7)
/* 0AED5C 800B42FC 7C632A14 */  add     r3, r3, r5
/* 0AED60 800B4300 8087001C */  lwz     r4, 0x1c(r7)
/* 0AED64 800B4304 7CA02A14 */  add     r5, r0, r5
/* 0AED68 800B4308 4BFFDB29 */  bl      DVDLowRead
/* 0AED6C 800B430C 48000208 */  b       lbl_800B4514
glabel lbl_800B4310
/* 0AED70 800B4310 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AED74 800B4314 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AED78 800B4318 38A36000 */  addi    r5, r3, DI_REGS_BASE@l
/* 0AED7C 800B431C 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AED80 800B4320 90050004 */  stw     r0, 4(r5)
/* 0AED84 800B4324 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AED88 800B4328 80670010 */  lwz     r3, 0x10(r7)
/* 0AED8C 800B432C 4BFFDD9D */  bl      DVDLowSeek
/* 0AED90 800B4330 480001E4 */  b       lbl_800B4514
glabel lbl_800B4334
/* 0AED94 800B4334 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AED98 800B4338 38634524 */  addi    r3, r3, cbForStateBusy@l
/* 0AED9C 800B433C 4BFFDEF1 */  bl      DVDLowStopMotor
/* 0AEDA0 800B4340 480001D4 */  b       lbl_800B4514
glabel lbl_800B4344
/* 0AEDA4 800B4344 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEDA8 800B4348 38634524 */  addi    r3, r3, cbForStateBusy@l
/* 0AEDAC 800B434C 4BFFDEE1 */  bl      DVDLowStopMotor
/* 0AEDB0 800B4350 480001C4 */  b       lbl_800B4514
glabel lbl_800B4354
/* 0AEDB4 800B4354 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEDB8 800B4358 38636000 */  addi    r3, r3, DI_REGS_BASE@l
/* 0AEDBC 800B435C 80030004 */  lwz     r0, DI_DICVR(r3)
/* 0AEDC0 800B4360 90030004 */  stw     r0, DI_DICVR(r3)
/* 0AEDC4 800B4364 800D8D44 */  lwz     r0, AutoFinishing-_SDA_BASE_(r13)
/* 0AEDC8 800B4368 2C000000 */  cmpwi   r0, 0
/* 0AEDCC 800B436C 41820024 */  beq     lbl_800B4390
/* 0AEDD0 800B4370 80AD8D30 */  lwz     r5, executing-_SDA_BASE_(r13)
/* 0AEDD4 800B4374 38000000 */  li      r0, 0
/* 0AEDD8 800B4378 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEDDC 800B437C 9005001C */  stw     r0, 0x1c(r5)
/* 0AEDE0 800B4380 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AEDE4 800B4384 38600000 */  li      r3, 0
/* 0AEDE8 800B4388 4BFFE0F1 */  bl      DVDLowRequestAudioStatus
/* 0AEDEC 800B438C 48000188 */  b       lbl_800B4514
lbl_800B4390:
/* 0AEDF0 800B4390 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AEDF4 800B4394 38000001 */  li      r0, 1
/* 0AEDF8 800B4398 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEDFC 800B439C 9004001C */  stw     r0, 0x1c(r4)
/* 0AEE00 800B43A0 38C34524 */  addi    r6, r3, cbForStateBusy@l
/* 0AEE04 800B43A4 38600000 */  li      r3, 0
/* 0AEE08 800B43A8 80870014 */  lwz     r4, 0x14(r7)
/* 0AEE0C 800B43AC 80A70010 */  lwz     r5, 0x10(r7)
/* 0AEE10 800B43B0 4BFFE031 */  bl      DVDLowAudioStream
/* 0AEE14 800B43B4 48000160 */  b       lbl_800B4514
glabel lbl_800B43B8
/* 0AEE18 800B43B8 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEE1C 800B43BC 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AEE20 800B43C0 38836000 */  addi    r4, r3, DI_REGS_BASE@l
/* 0AEE24 800B43C4 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEE28 800B43C8 90040004 */  stw     r0, DI_DICVR(r4)
/* 0AEE2C 800B43CC 38C34524 */  addi    r6, r3, cbForStateBusy@l
/* 0AEE30 800B43D0 3C600001 */  lis     r3, 1
/* 0AEE34 800B43D4 38800000 */  li      r4, 0
/* 0AEE38 800B43D8 38A00000 */  li      r5, 0
/* 0AEE3C 800B43DC 4BFFE005 */  bl      DVDLowAudioStream
/* 0AEE40 800B43E0 48000134 */  b       lbl_800B4514
glabel lbl_800B43E4
/* 0AEE44 800B43E4 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEE48 800B43E8 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AEE4C 800B43EC 38836000 */  addi    r4, r3, DI_REGS_BASE@l
/* 0AEE50 800B43F0 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEE54 800B43F4 90040004 */  stw     r0, DI_DICVR(r4)
/* 0AEE58 800B43F8 38000001 */  li      r0, 1
/* 0AEE5C 800B43FC 38C34524 */  addi    r6, r3, cbForStateBusy@l
/* 0AEE60 800B4400 900D8D44 */  stw     r0, AutoFinishing-_SDA_BASE_(r13)
/* 0AEE64 800B4404 38600000 */  li      r3, 0
/* 0AEE68 800B4408 38800000 */  li      r4, 0
/* 0AEE6C 800B440C 38A00000 */  li      r5, 0
/* 0AEE70 800B4410 4BFFDFD1 */  bl      DVDLowAudioStream
/* 0AEE74 800B4414 48000100 */  b       lbl_800B4514
glabel lbl_800B4418
/* 0AEE78 800B4418 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEE7C 800B441C 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AEE80 800B4420 38A36000 */  addi    r5, r3, DI_REGS_BASE@l
/* 0AEE84 800B4424 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEE88 800B4428 90050004 */  stw     r0, DI_DICVR(r5)
/* 0AEE8C 800B442C 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AEE90 800B4430 38600000 */  li      r3, 0
/* 0AEE94 800B4434 4BFFE045 */  bl      DVDLowRequestAudioStatus
/* 0AEE98 800B4438 480000DC */  b       lbl_800B4514
glabel lbl_800B443C
/* 0AEE9C 800B443C 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEEA0 800B4440 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AEEA4 800B4444 38A36000 */  addi    r5, r3, 0x6000
/* 0AEEA8 800B4448 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEEAC 800B444C 90050004 */  stw     r0, 4(r5)
/* 0AEEB0 800B4450 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AEEB4 800B4454 3C600001 */  lis     r3, 1
/* 0AEEB8 800B4458 4BFFE021 */  bl      DVDLowRequestAudioStatus
/* 0AEEBC 800B445C 480000B8 */  b       lbl_800B4514
glabel lbl_800B4460
/* 0AEEC0 800B4460 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEEC4 800B4464 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AEEC8 800B4468 38A36000 */  addi    r5, r3, DI_REGS_BASE@l
/* 0AEECC 800B446C 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEED0 800B4470 90050004 */  stw     r0, DI_DICVR(r5)
/* 0AEED4 800B4474 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AEED8 800B4478 3C600002 */  lis     r3, 2
/* 0AEEDC 800B447C 4BFFDFFD */  bl      DVDLowRequestAudioStatus
/* 0AEEE0 800B4480 48000094 */  b       lbl_800B4514
glabel lbl_800B4484
/* 0AEEE4 800B4484 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEEE8 800B4488 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AEEEC 800B448C 38A36000 */  addi    r5, r3, DI_REGS_BASE@l
/* 0AEEF0 800B4490 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEEF4 800B4494 90050004 */  stw     r0, DI_DICVR(r5)
/* 0AEEF8 800B4498 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AEEFC 800B449C 3C600003 */  lis     r3, 3
/* 0AEF00 800B44A0 4BFFDFD9 */  bl      DVDLowRequestAudioStatus
/* 0AEF04 800B44A4 48000070 */  b       lbl_800B4514
glabel lbl_800B44A8
/* 0AEF08 800B44A8 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEF0C 800B44AC 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AEF10 800B44B0 38836000 */  addi    r4, r3, DI_REGS_BASE@l
/* 0AEF14 800B44B4 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEF18 800B44B8 90040004 */  stw     r0, DI_DICVR(r4)
/* 0AEF1C 800B44BC 38A34524 */  addi    r5, r3, cbForStateBusy@l
/* 0AEF20 800B44C0 80670010 */  lwz     r3, 0x10(r7)
/* 0AEF24 800B44C4 80870014 */  lwz     r4, 0x14(r7)
/* 0AEF28 800B44C8 4BFFE03D */  bl      DVDLowAudioBufferConfig
/* 0AEF2C 800B44CC 48000048 */  b       lbl_800B4514
glabel lbl_800B44D0
/* 0AEF30 800B44D0 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AEF34 800B44D4 80036004 */  lwz     r0, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AEF38 800B44D8 38A36000 */  addi    r5, r3, DI_REGS_BASE@l
/* 0AEF3C 800B44DC 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEF40 800B44E0 90050004 */  stw     r0, DI_DICVR(r5)
/* 0AEF44 800B44E4 38000020 */  li      r0, 0x20
/* 0AEF48 800B44E8 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AEF4C 800B44EC 9007001C */  stw     r0, 0x1c(r7)
/* 0AEF50 800B44F0 80670018 */  lwz     r3, 0x18(r7)
/* 0AEF54 800B44F4 4BFFDE51 */  bl      DVDLowInquiry
/* 0AEF58 800B44F8 4800001C */  b       lbl_800B4514
glabel lbl_800B44FC
/* 0AEF5C 800B44FC 818D8820 */  lwz     r12, checkOptionalCommand-_SDA_BASE_(r13)
/* 0AEF60 800B4500 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AEF64 800B4504 38834524 */  addi    r4, r3, cbForStateBusy@l
/* 0AEF68 800B4508 7D8803A6 */  mtlr    r12
/* 0AEF6C 800B450C 38670000 */  addi    r3, r7, 0
/* 0AEF70 800B4510 4E800021 */  blrl    
lbl_800B4514:
/* 0AEF74 800B4514 8001000C */  lwz     r0, 0xc(r1)
/* 0AEF78 800B4518 38210008 */  addi    r1, r1, 8
/* 0AEF7C 800B451C 7C0803A6 */  mtlr    r0
/* 0AEF80 800B4520 4E800020 */  blr     

cbForStateBusy:
/* 0AEF84 800B4524 7C0802A6 */  mflr    r0
/* 0AEF88 800B4528 28030010 */  cmplwi  r3, 0x10
/* 0AEF8C 800B452C 90010004 */  stw     r0, 4(r1)
/* 0AEF90 800B4530 3C808013 */  lis     r4, BB2@ha
/* 0AEF94 800B4534 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AEF98 800B4538 93E10014 */  stw     r31, 0x14(r1)
/* 0AEF9C 800B453C 3BE425A0 */  addi    r31, r4, BB2@l
/* 0AEFA0 800B4540 93C10010 */  stw     r30, 0x10(r1)
/* 0AEFA4 800B4544 4082002C */  bne     lbl_800B4570
/* 0AEFA8 800B4548 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AEFAC 800B454C 3800FFFF */  li      r0, -1
/* 0AEFB0 800B4550 3C600123 */  lis     r3, 0x123
/* 0AEFB4 800B4554 9004000C */  stw     r0, 0xc(r4)
/* 0AEFB8 800B4558 38634568 */  addi    r3, r3, 0x4568
/* 0AEFBC 800B455C 4800145D */  bl      __DVDStoreErrorCode
/* 0AEFC0 800B4560 48000A09 */  bl      DVDReset
/* 0AEFC4 800B4564 38600000 */  li      r3, 0
/* 0AEFC8 800B4568 4BFFEBF9 */  bl      cbForStateError
/* 0AEFCC 800B456C 480005D8 */  b       lbl_800B4B44
lbl_800B4570:
/* 0AEFD0 800B4570 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AEFD4 800B4574 28000003 */  cmplwi  r0, 3
/* 0AEFD8 800B4578 41820010 */  beq     lbl_800B4588
/* 0AEFDC 800B457C 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AEFE0 800B4580 2800000F */  cmplwi  r0, 0xf
/* 0AEFE4 800B4584 408200EC */  bne     lbl_800B4670
lbl_800B4588:
/* 0AEFE8 800B4588 546007BD */  rlwinm. r0, r3, 0, 0x1e, 0x1e
/* 0AEFEC 800B458C 4182002C */  beq     lbl_800B45B8
/* 0AEFF0 800B4590 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AEFF4 800B4594 3800FFFF */  li      r0, -1
/* 0AEFF8 800B4598 3C600123 */  lis     r3, 0x123
/* 0AEFFC 800B459C 9004000C */  stw     r0, 0xc(r4)
/* 0AF000 800B45A0 38634567 */  addi    r3, r3, 0x4567
/* 0AF004 800B45A4 48001415 */  bl      __DVDStoreErrorCode
/* 0AF008 800B45A8 3C60800B */  lis     r3, cbForStateError@ha
/* 0AF00C 800B45AC 38633160 */  addi    r3, r3, cbForStateError@l
/* 0AF010 800B45B0 4BFFDC7D */  bl      DVDLowStopMotor
/* 0AF014 800B45B4 48000590 */  b       lbl_800B4B44
lbl_800B45B8:
/* 0AF018 800B45B8 38000000 */  li      r0, 0
/* 0AF01C 800B45BC 900D8D64 */  stw     r0, NumInternalRetry-_SDA_BASE_(r13)
/* 0AF020 800B45C0 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF024 800B45C4 2800000F */  cmplwi  r0, 0xf
/* 0AF028 800B45C8 4082000C */  bne     lbl_800B45D4
/* 0AF02C 800B45CC 38000001 */  li      r0, 1
/* 0AF030 800B45D0 900D8D68 */  stw     r0, ResetRequired-_SDA_BASE_(r13)
lbl_800B45D4:
/* 0AF034 800B45D4 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AF038 800B45D8 28000000 */  cmplwi  r0, 0
/* 0AF03C 800B45DC 4182006C */  beq     lbl_800B4648
/* 0AF040 800B45E0 38000007 */  li      r0, 7
/* 0AF044 800B45E4 83CD8D30 */  lwz     r30, executing-_SDA_BASE_(r13)
/* 0AF048 800B45E8 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
/* 0AF04C 800B45EC 387F0040 */  addi    r3, r31, 0x40
/* 0AF050 800B45F0 38000000 */  li      r0, 0
/* 0AF054 800B45F4 900D8D50 */  stw     r0, Canceling-_SDA_BASE_(r13)
/* 0AF058 800B45F8 3800000A */  li      r0, 0xa
/* 0AF05C 800B45FC 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AF060 800B4600 901E000C */  stw     r0, 0xc(r30)
/* 0AF064 800B4604 819E0028 */  lwz     r12, 0x28(r30)
/* 0AF068 800B4608 280C0000 */  cmplwi  r12, 0
/* 0AF06C 800B460C 41820014 */  beq     lbl_800B4620
/* 0AF070 800B4610 7D8803A6 */  mtlr    r12
/* 0AF074 800B4614 389E0000 */  addi    r4, r30, 0
/* 0AF078 800B4618 3860FFFD */  li      r3, -3
/* 0AF07C 800B461C 4E800021 */  blrl    
lbl_800B4620:
/* 0AF080 800B4620 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0AF084 800B4624 280C0000 */  cmplwi  r12, 0
/* 0AF088 800B4628 41820014 */  beq     lbl_800B463C
/* 0AF08C 800B462C 7D8803A6 */  mtlr    r12
/* 0AF090 800B4630 389E0000 */  addi    r4, r30, 0
/* 0AF094 800B4634 38600000 */  li      r3, 0
/* 0AF098 800B4638 4E800021 */  blrl    
lbl_800B463C:
/* 0AF09C 800B463C 4BFFF999 */  bl      stateReady
/* 0AF0A0 800B4640 38000001 */  li      r0, 1
/* 0AF0A4 800B4644 48000008 */  b       lbl_800B464C
lbl_800B4648:
/* 0AF0A8 800B4648 38000000 */  li      r0, 0
lbl_800B464C:
/* 0AF0AC 800B464C 2C000000 */  cmpwi   r0, 0
/* 0AF0B0 800B4650 408204F4 */  bne     lbl_800B4B44
/* 0AF0B4 800B4654 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AF0B8 800B4658 38000007 */  li      r0, 7
/* 0AF0BC 800B465C 3C60800B */  lis     r3, cbForStateMotorStopped@ha
/* 0AF0C0 800B4660 9004000C */  stw     r0, 0xc(r4)
/* 0AF0C4 800B4664 38633EF0 */  addi    r3, r3, cbForStateMotorStopped@l
/* 0AF0C8 800B4668 4BFFDAF5 */  bl      DVDLowWaitCoverClose
/* 0AF0CC 800B466C 480004D8 */  b       lbl_800B4B44
lbl_800B4670:
/* 0AF0D0 800B4670 808D8D4C */  lwz     r4, CurrCommand-_SDA_BASE_(r13)
/* 0AF0D4 800B4674 28040001 */  cmplwi  r4, 1
/* 0AF0D8 800B4678 41820018 */  beq     lbl_800B4690
/* 0AF0DC 800B467C 3804FFFC */  addi    r0, r4, -4
/* 0AF0E0 800B4680 28000001 */  cmplwi  r0, 1
/* 0AF0E4 800B4684 4081000C */  ble     lbl_800B4690
/* 0AF0E8 800B4688 2804000E */  cmplwi  r4, 0xe
/* 0AF0EC 800B468C 4082000C */  bne     lbl_800B4698
lbl_800B4690:
/* 0AF0F0 800B4690 38000001 */  li      r0, 1
/* 0AF0F4 800B4694 4800001C */  b       lbl_800B46B0
lbl_800B4698:
/* 0AF0F8 800B4698 800D882C */  lwz     r0, DmaCommand-_SDA_BASE_(r13)
/* 0AF0FC 800B469C 7C040040 */  cmplw   r4, r0
/* 0AF100 800B46A0 4082000C */  bne     lbl_800B46AC
/* 0AF104 800B46A4 38000001 */  li      r0, 1
/* 0AF108 800B46A8 48000008 */  b       lbl_800B46B0
lbl_800B46AC:
/* 0AF10C 800B46AC 38000000 */  li      r0, 0
lbl_800B46B0:
/* 0AF110 800B46B0 2C000000 */  cmpwi   r0, 0
/* 0AF114 800B46B4 41820028 */  beq     lbl_800B46DC
/* 0AF118 800B46B8 80CD8D30 */  lwz     r6, executing-_SDA_BASE_(r13)
/* 0AF11C 800B46BC 3C80CC00 */  lis     r4, DI_REGS_BASE@ha
/* 0AF120 800B46C0 38846000 */  addi    r4, r4, DI_REGS_BASE@l
/* 0AF124 800B46C4 80840018 */  lwz     r4, DI_DILENGTH(r4)
/* 0AF128 800B46C8 8006001C */  lwz     r0, 0x1c(r6)
/* 0AF12C 800B46CC 80A60020 */  lwz     r5, 0x20(r6)
/* 0AF130 800B46D0 7C040050 */  subf    r0, r4, r0
/* 0AF134 800B46D4 7C050214 */  add     r0, r5, r0
/* 0AF138 800B46D8 90060020 */  stw     r0, 0x20(r6)
lbl_800B46DC:
/* 0AF13C 800B46DC 54600739 */  rlwinm. r0, r3, 0, 0x1c, 0x1c
/* 0AF140 800B46E0 41820060 */  beq     lbl_800B4740
/* 0AF144 800B46E4 83CD8D30 */  lwz     r30, executing-_SDA_BASE_(r13)
/* 0AF148 800B46E8 387F0040 */  addi    r3, r31, 0x40
/* 0AF14C 800B46EC 38000000 */  li      r0, 0
/* 0AF150 800B46F0 900D8D50 */  stw     r0, Canceling-_SDA_BASE_(r13)
/* 0AF154 800B46F4 3800000A */  li      r0, 0xa
/* 0AF158 800B46F8 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AF15C 800B46FC 901E000C */  stw     r0, 0xc(r30)
/* 0AF160 800B4700 819E0028 */  lwz     r12, 0x28(r30)
/* 0AF164 800B4704 280C0000 */  cmplwi  r12, 0
/* 0AF168 800B4708 41820014 */  beq     lbl_800B471C
/* 0AF16C 800B470C 7D8803A6 */  mtlr    r12
/* 0AF170 800B4710 389E0000 */  addi    r4, r30, 0
/* 0AF174 800B4714 3860FFFD */  li      r3, -3
/* 0AF178 800B4718 4E800021 */  blrl    
lbl_800B471C:
/* 0AF17C 800B471C 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0AF180 800B4720 280C0000 */  cmplwi  r12, 0
/* 0AF184 800B4724 41820014 */  beq     lbl_800B4738
/* 0AF188 800B4728 7D8803A6 */  mtlr    r12
/* 0AF18C 800B472C 389E0000 */  addi    r4, r30, 0
/* 0AF190 800B4730 38600000 */  li      r3, 0
/* 0AF194 800B4734 4E800021 */  blrl    
lbl_800B4738:
/* 0AF198 800B4738 4BFFF89D */  bl      stateReady
/* 0AF19C 800B473C 48000408 */  b       lbl_800B4B44
lbl_800B4740:
/* 0AF1A0 800B4740 546007FF */  clrlwi. r0, r3, 0x1f
/* 0AF1A4 800B4744 418202D0 */  beq     lbl_800B4A14
/* 0AF1A8 800B4748 38800000 */  li      r4, 0
/* 0AF1AC 800B474C 908D8D64 */  stw     r4, NumInternalRetry-_SDA_BASE_(r13)
/* 0AF1B0 800B4750 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AF1B4 800B4754 28000000 */  cmplwi  r0, 0
/* 0AF1B8 800B4758 41820060 */  beq     lbl_800B47B8
/* 0AF1BC 800B475C 908D8D58 */  stw     r4, ResumeFromHere-_SDA_BASE_(r13)
/* 0AF1C0 800B4760 387F0040 */  addi    r3, r31, 0x40
/* 0AF1C4 800B4764 83CD8D30 */  lwz     r30, executing-_SDA_BASE_(r13)
/* 0AF1C8 800B4768 3800000A */  li      r0, 0xa
/* 0AF1CC 800B476C 908D8D50 */  stw     r4, Canceling-_SDA_BASE_(r13)
/* 0AF1D0 800B4770 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AF1D4 800B4774 901E000C */  stw     r0, 0xc(r30)
/* 0AF1D8 800B4778 819E0028 */  lwz     r12, 0x28(r30)
/* 0AF1DC 800B477C 280C0000 */  cmplwi  r12, 0
/* 0AF1E0 800B4780 41820014 */  beq     lbl_800B4794
/* 0AF1E4 800B4784 7D8803A6 */  mtlr    r12
/* 0AF1E8 800B4788 389E0000 */  addi    r4, r30, 0
/* 0AF1EC 800B478C 3860FFFD */  li      r3, -3
/* 0AF1F0 800B4790 4E800021 */  blrl    
lbl_800B4794:
/* 0AF1F4 800B4794 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0AF1F8 800B4798 280C0000 */  cmplwi  r12, 0
/* 0AF1FC 800B479C 41820014 */  beq     lbl_800B47B0
/* 0AF200 800B47A0 7D8803A6 */  mtlr    r12
/* 0AF204 800B47A4 389E0000 */  addi    r4, r30, 0
/* 0AF208 800B47A8 38600000 */  li      r3, 0
/* 0AF20C 800B47AC 4E800021 */  blrl    
lbl_800B47B0:
/* 0AF210 800B47B0 4BFFF825 */  bl      stateReady
/* 0AF214 800B47B4 38800001 */  li      r4, 1
lbl_800B47B8:
/* 0AF218 800B47B8 2C040000 */  cmpwi   r4, 0
/* 0AF21C 800B47BC 40820388 */  bne     lbl_800B4B44
/* 0AF220 800B47C0 806D8D4C */  lwz     r3, CurrCommand-_SDA_BASE_(r13)
/* 0AF224 800B47C4 28030001 */  cmplwi  r3, 1
/* 0AF228 800B47C8 41820018 */  beq     lbl_800B47E0
/* 0AF22C 800B47CC 3803FFFC */  addi    r0, r3, -4
/* 0AF230 800B47D0 28000001 */  cmplwi  r0, 1
/* 0AF234 800B47D4 4081000C */  ble     lbl_800B47E0
/* 0AF238 800B47D8 2803000E */  cmplwi  r3, 0xe
/* 0AF23C 800B47DC 4082000C */  bne     lbl_800B47E8
lbl_800B47E0:
/* 0AF240 800B47E0 38000001 */  li      r0, 1
/* 0AF244 800B47E4 4800001C */  b       lbl_800B4800
lbl_800B47E8:
/* 0AF248 800B47E8 800D882C */  lwz     r0, DmaCommand-_SDA_BASE_(r13)
/* 0AF24C 800B47EC 7C030040 */  cmplw   r3, r0
/* 0AF250 800B47F0 4082000C */  bne     lbl_800B47FC
/* 0AF254 800B47F4 38000001 */  li      r0, 1
/* 0AF258 800B47F8 48000008 */  b       lbl_800B4800
lbl_800B47FC:
/* 0AF25C 800B47FC 38000000 */  li      r0, 0
lbl_800B4800:
/* 0AF260 800B4800 2C000000 */  cmpwi   r0, 0
/* 0AF264 800B4804 41820054 */  beq     lbl_800B4858
/* 0AF268 800B4808 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AF26C 800B480C 80830020 */  lwz     r4, 0x20(r3)
/* 0AF270 800B4810 80030014 */  lwz     r0, 0x14(r3)
/* 0AF274 800B4814 7C040040 */  cmplw   r4, r0
/* 0AF278 800B4818 4182000C */  beq     lbl_800B4824
/* 0AF27C 800B481C 4BFFF9E9 */  bl      stateBusy
/* 0AF280 800B4820 48000324 */  b       lbl_800B4B44
lbl_800B4824:
/* 0AF284 800B4824 381F0040 */  addi    r0, r31, 0x40
/* 0AF288 800B4828 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AF28C 800B482C 38000000 */  li      r0, 0
/* 0AF290 800B4830 38830000 */  addi    r4, r3, 0
/* 0AF294 800B4834 9003000C */  stw     r0, 0xc(r3)
/* 0AF298 800B4838 81830028 */  lwz     r12, 0x28(r3)
/* 0AF29C 800B483C 280C0000 */  cmplwi  r12, 0
/* 0AF2A0 800B4840 41820010 */  beq     lbl_800B4850
/* 0AF2A4 800B4844 80640020 */  lwz     r3, 0x20(r4)
/* 0AF2A8 800B4848 7D8803A6 */  mtlr    r12
/* 0AF2AC 800B484C 4E800021 */  blrl    
lbl_800B4850:
/* 0AF2B0 800B4850 4BFFF785 */  bl      stateReady
/* 0AF2B4 800B4854 480002F0 */  b       lbl_800B4B44
lbl_800B4858:
/* 0AF2B8 800B4858 808D8D4C */  lwz     r4, CurrCommand-_SDA_BASE_(r13)
/* 0AF2BC 800B485C 3804FFF7 */  addi    r0, r4, -9
/* 0AF2C0 800B4860 28000003 */  cmplwi  r0, 3
/* 0AF2C4 800B4864 4181000C */  bgt     lbl_800B4870
/* 0AF2C8 800B4868 38000001 */  li      r0, 1
/* 0AF2CC 800B486C 48000048 */  b       lbl_800B48B4
lbl_800B4870:
/* 0AF2D0 800B4870 3C60800F */  lis     r3, ImmCommand@ha
/* 0AF2D4 800B4874 84032528 */  lwzu    r0, ImmCommand@l(r3)
/* 0AF2D8 800B4878 7C040040 */  cmplw   r4, r0
/* 0AF2DC 800B487C 4082000C */  bne     lbl_800B4888
/* 0AF2E0 800B4880 38000001 */  li      r0, 1
/* 0AF2E4 800B4884 48000030 */  b       lbl_800B48B4
lbl_800B4888:
/* 0AF2E8 800B4888 84030004 */  lwzu    r0, 4(r3)
/* 0AF2EC 800B488C 7C040040 */  cmplw   r4, r0
/* 0AF2F0 800B4890 4082000C */  bne     lbl_800B489C
/* 0AF2F4 800B4894 38000001 */  li      r0, 1
/* 0AF2F8 800B4898 4800001C */  b       lbl_800B48B4
lbl_800B489C:
/* 0AF2FC 800B489C 80030004 */  lwz     r0, 4(r3)
/* 0AF300 800B48A0 7C040040 */  cmplw   r4, r0
/* 0AF304 800B48A4 4082000C */  bne     lbl_800B48B0
/* 0AF308 800B48A8 38000001 */  li      r0, 1
/* 0AF30C 800B48AC 48000008 */  b       lbl_800B48B4
lbl_800B48B0:
/* 0AF310 800B48B0 38000000 */  li      r0, 0
lbl_800B48B4:
/* 0AF314 800B48B4 2C000000 */  cmpwi   r0, 0
/* 0AF318 800B48B8 41820068 */  beq     lbl_800B4920
/* 0AF31C 800B48BC 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF320 800B48C0 2800000B */  cmplwi  r0, 0xb
/* 0AF324 800B48C4 41820010 */  beq     lbl_800B48D4
/* 0AF328 800B48C8 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF32C 800B48CC 2800000A */  cmplwi  r0, 0xa
/* 0AF330 800B48D0 40820014 */  bne     lbl_800B48E4
lbl_800B48D4:
/* 0AF334 800B48D4 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AF338 800B48D8 80036020 */  lwz     r0, (DI_REGS_BASE + DI_DIIMMBUF)@l(r3)
/* 0AF33C 800B48DC 5403103A */  slwi    r3, r0, 2
/* 0AF340 800B48E0 48000010 */  b       lbl_800B48F0
lbl_800B48E4:
/* 0AF344 800B48E4 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AF348 800B48E8 38636000 */  addi    r3, r3, DI_REGS_BASE@l
/* 0AF34C 800B48EC 80630020 */  lwz     r3, DI_DIIMMBUF(r3)
lbl_800B48F0:
/* 0AF350 800B48F0 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AF354 800B48F4 38BF0040 */  addi    r5, r31, 0x40
/* 0AF358 800B48F8 38000000 */  li      r0, 0
/* 0AF35C 800B48FC 90AD8D30 */  stw     r5, executing-_SDA_BASE_(r13)
/* 0AF360 800B4900 9004000C */  stw     r0, 0xc(r4)
/* 0AF364 800B4904 81840028 */  lwz     r12, 0x28(r4)
/* 0AF368 800B4908 280C0000 */  cmplwi  r12, 0
/* 0AF36C 800B490C 4182000C */  beq     lbl_800B4918
/* 0AF370 800B4910 7D8803A6 */  mtlr    r12
/* 0AF374 800B4914 4E800021 */  blrl    
lbl_800B4918:
/* 0AF378 800B4918 4BFFF6BD */  bl      stateReady
/* 0AF37C 800B491C 48000228 */  b       lbl_800B4B44
lbl_800B4920:
/* 0AF380 800B4920 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF384 800B4924 28000006 */  cmplwi  r0, 6
/* 0AF388 800B4928 408200B8 */  bne     lbl_800B49E0
/* 0AF38C 800B492C 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AF390 800B4930 38A4001C */  addi    r5, r4, 0x1c
/* 0AF394 800B4934 8004001C */  lwz     r0, 0x1c(r4)
/* 0AF398 800B4938 28000000 */  cmplwi  r0, 0
/* 0AF39C 800B493C 40820074 */  bne     lbl_800B49B0
/* 0AF3A0 800B4940 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AF3A4 800B4944 80036020 */  lwz     r0, (DI_REGS_BASE + DI_DIIMMBUF)@l(r3)
/* 0AF3A8 800B4948 540007FF */  clrlwi. r0, r0, 0x1f
/* 0AF3AC 800B494C 41820034 */  beq     lbl_800B4980
/* 0AF3B0 800B4950 381F0040 */  addi    r0, r31, 0x40
/* 0AF3B4 800B4954 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AF3B8 800B4958 38000009 */  li      r0, 9
/* 0AF3BC 800B495C 9004000C */  stw     r0, 0xc(r4)
/* 0AF3C0 800B4960 81840028 */  lwz     r12, 0x28(r4)
/* 0AF3C4 800B4964 280C0000 */  cmplwi  r12, 0
/* 0AF3C8 800B4968 41820010 */  beq     lbl_800B4978
/* 0AF3CC 800B496C 7D8803A6 */  mtlr    r12
/* 0AF3D0 800B4970 3860FFFE */  li      r3, -2
/* 0AF3D4 800B4974 4E800021 */  blrl    
lbl_800B4978:
/* 0AF3D8 800B4978 4BFFF65D */  bl      stateReady
/* 0AF3DC 800B497C 480001C8 */  b       lbl_800B4B44
lbl_800B4980:
/* 0AF3E0 800B4980 38000000 */  li      r0, 0
/* 0AF3E4 800B4984 900D8D44 */  stw     r0, AutoFinishing-_SDA_BASE_(r13)
/* 0AF3E8 800B4988 38000001 */  li      r0, 1
/* 0AF3EC 800B498C 3C60800B */  lis     r3, cbForStateBusy@ha
/* 0AF3F0 800B4990 90050000 */  stw     r0, 0(r5)
/* 0AF3F4 800B4994 38C34524 */  addi    r6, r3, cbForStateBusy@l
/* 0AF3F8 800B4998 38600000 */  li      r3, 0
/* 0AF3FC 800B499C 80AD8D30 */  lwz     r5, executing-_SDA_BASE_(r13)
/* 0AF400 800B49A0 80850014 */  lwz     r4, 0x14(r5)
/* 0AF404 800B49A4 80A50010 */  lwz     r5, 0x10(r5)
/* 0AF408 800B49A8 4BFFDA39 */  bl      DVDLowAudioStream
/* 0AF40C 800B49AC 48000198 */  b       lbl_800B4B44
lbl_800B49B0:
/* 0AF410 800B49B0 381F0040 */  addi    r0, r31, 0x40
/* 0AF414 800B49B4 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AF418 800B49B8 38000000 */  li      r0, 0
/* 0AF41C 800B49BC 9004000C */  stw     r0, 0xc(r4)
/* 0AF420 800B49C0 81840028 */  lwz     r12, 0x28(r4)
/* 0AF424 800B49C4 280C0000 */  cmplwi  r12, 0
/* 0AF428 800B49C8 41820010 */  beq     lbl_800B49D8
/* 0AF42C 800B49CC 7D8803A6 */  mtlr    r12
/* 0AF430 800B49D0 38600000 */  li      r3, 0
/* 0AF434 800B49D4 4E800021 */  blrl    
lbl_800B49D8:
/* 0AF438 800B49D8 4BFFF5FD */  bl      stateReady
/* 0AF43C 800B49DC 48000168 */  b       lbl_800B4B44
lbl_800B49E0:
/* 0AF440 800B49E0 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AF444 800B49E4 387F0040 */  addi    r3, r31, 0x40
/* 0AF448 800B49E8 38000000 */  li      r0, 0
/* 0AF44C 800B49EC 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AF450 800B49F0 9004000C */  stw     r0, 0xc(r4)
/* 0AF454 800B49F4 81840028 */  lwz     r12, 0x28(r4)
/* 0AF458 800B49F8 280C0000 */  cmplwi  r12, 0
/* 0AF45C 800B49FC 41820010 */  beq     lbl_800B4A0C
/* 0AF460 800B4A00 7D8803A6 */  mtlr    r12
/* 0AF464 800B4A04 38600000 */  li      r3, 0
/* 0AF468 800B4A08 4E800021 */  blrl    
lbl_800B4A0C:
/* 0AF46C 800B4A0C 4BFFF5C9 */  bl      stateReady
/* 0AF470 800B4A10 48000134 */  b       lbl_800B4B44
lbl_800B4A14:
/* 0AF474 800B4A14 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF478 800B4A18 2800000E */  cmplwi  r0, 0xe
/* 0AF47C 800B4A1C 4082002C */  bne     lbl_800B4A48
/* 0AF480 800B4A20 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AF484 800B4A24 3800FFFF */  li      r0, -1
/* 0AF488 800B4A28 3C600123 */  lis     r3, 0x123
/* 0AF48C 800B4A2C 9004000C */  stw     r0, 0xc(r4)
/* 0AF490 800B4A30 38634567 */  addi    r3, r3, 0x4567
/* 0AF494 800B4A34 48000F85 */  bl      __DVDStoreErrorCode
/* 0AF498 800B4A38 3C60800B */  lis     r3, cbForStateError@ha
/* 0AF49C 800B4A3C 38633160 */  addi    r3, r3, cbForStateError@l
/* 0AF4A0 800B4A40 4BFFD7ED */  bl      DVDLowStopMotor
/* 0AF4A4 800B4A44 48000100 */  b       lbl_800B4B44
lbl_800B4A48:
/* 0AF4A8 800B4A48 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF4AC 800B4A4C 28000001 */  cmplwi  r0, 1
/* 0AF4B0 800B4A50 41820028 */  beq     lbl_800B4A78
/* 0AF4B4 800B4A54 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF4B8 800B4A58 28000004 */  cmplwi  r0, 4
/* 0AF4BC 800B4A5C 4182001C */  beq     lbl_800B4A78
/* 0AF4C0 800B4A60 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF4C4 800B4A64 28000005 */  cmplwi  r0, 5
/* 0AF4C8 800B4A68 41820010 */  beq     lbl_800B4A78
/* 0AF4CC 800B4A6C 800D8D4C */  lwz     r0, CurrCommand-_SDA_BASE_(r13)
/* 0AF4D0 800B4A70 2800000E */  cmplwi  r0, 0xe
/* 0AF4D4 800B4A74 408200C4 */  bne     lbl_800B4B38
lbl_800B4A78:
/* 0AF4D8 800B4A78 83CD8D30 */  lwz     r30, executing-_SDA_BASE_(r13)
/* 0AF4DC 800B4A7C 807E0020 */  lwz     r3, 0x20(r30)
/* 0AF4E0 800B4A80 801E0014 */  lwz     r0, 0x14(r30)
/* 0AF4E4 800B4A84 7C030040 */  cmplw   r3, r0
/* 0AF4E8 800B4A88 408200B0 */  bne     lbl_800B4B38
/* 0AF4EC 800B4A8C 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AF4F0 800B4A90 28000000 */  cmplwi  r0, 0
/* 0AF4F4 800B4A94 41820064 */  beq     lbl_800B4AF8
/* 0AF4F8 800B4A98 38800000 */  li      r4, 0
/* 0AF4FC 800B4A9C 908D8D58 */  stw     r4, ResumeFromHere-_SDA_BASE_(r13)
/* 0AF500 800B4AA0 387F0040 */  addi    r3, r31, 0x40
/* 0AF504 800B4AA4 3800000A */  li      r0, 0xa
/* 0AF508 800B4AA8 908D8D50 */  stw     r4, Canceling-_SDA_BASE_(r13)
/* 0AF50C 800B4AAC 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AF510 800B4AB0 901E000C */  stw     r0, 0xc(r30)
/* 0AF514 800B4AB4 819E0028 */  lwz     r12, 0x28(r30)
/* 0AF518 800B4AB8 280C0000 */  cmplwi  r12, 0
/* 0AF51C 800B4ABC 41820014 */  beq     lbl_800B4AD0
/* 0AF520 800B4AC0 7D8803A6 */  mtlr    r12
/* 0AF524 800B4AC4 389E0000 */  addi    r4, r30, 0
/* 0AF528 800B4AC8 3860FFFD */  li      r3, -3
/* 0AF52C 800B4ACC 4E800021 */  blrl    
lbl_800B4AD0:
/* 0AF530 800B4AD0 818D8D54 */  lwz     r12, CancelCallback-_SDA_BASE_(r13)
/* 0AF534 800B4AD4 280C0000 */  cmplwi  r12, 0
/* 0AF538 800B4AD8 41820014 */  beq     lbl_800B4AEC
/* 0AF53C 800B4ADC 7D8803A6 */  mtlr    r12
/* 0AF540 800B4AE0 389E0000 */  addi    r4, r30, 0
/* 0AF544 800B4AE4 38600000 */  li      r3, 0
/* 0AF548 800B4AE8 4E800021 */  blrl    
lbl_800B4AEC:
/* 0AF54C 800B4AEC 4BFFF4E9 */  bl      stateReady
/* 0AF550 800B4AF0 38000001 */  li      r0, 1
/* 0AF554 800B4AF4 48000008 */  b       lbl_800B4AFC
lbl_800B4AF8:
/* 0AF558 800B4AF8 38000000 */  li      r0, 0
lbl_800B4AFC:
/* 0AF55C 800B4AFC 2C000000 */  cmpwi   r0, 0
/* 0AF560 800B4B00 40820044 */  bne     lbl_800B4B44
/* 0AF564 800B4B04 808D8D30 */  lwz     r4, executing-_SDA_BASE_(r13)
/* 0AF568 800B4B08 387F0040 */  addi    r3, r31, 0x40
/* 0AF56C 800B4B0C 38000000 */  li      r0, 0
/* 0AF570 800B4B10 906D8D30 */  stw     r3, executing-_SDA_BASE_(r13)
/* 0AF574 800B4B14 9004000C */  stw     r0, 0xc(r4)
/* 0AF578 800B4B18 81840028 */  lwz     r12, 0x28(r4)
/* 0AF57C 800B4B1C 280C0000 */  cmplwi  r12, 0
/* 0AF580 800B4B20 41820010 */  beq     lbl_800B4B30
/* 0AF584 800B4B24 80640020 */  lwz     r3, 0x20(r4)
/* 0AF588 800B4B28 7D8803A6 */  mtlr    r12
/* 0AF58C 800B4B2C 4E800021 */  blrl    
lbl_800B4B30:
/* 0AF590 800B4B30 4BFFF4A5 */  bl      stateReady
/* 0AF594 800B4B34 48000010 */  b       lbl_800B4B44
lbl_800B4B38:
/* 0AF598 800B4B38 3C60800B */  lis     r3, cbForStateGettingError@ha
/* 0AF59C 800B4B3C 3863331C */  addi    r3, r3, cbForStateGettingError@l
/* 0AF5A0 800B4B40 4BFFD779 */  bl      DVDLowRequestError
lbl_800B4B44:
/* 0AF5A4 800B4B44 8001001C */  lwz     r0, 0x1c(r1)
/* 0AF5A8 800B4B48 83E10014 */  lwz     r31, 0x14(r1)
/* 0AF5AC 800B4B4C 83C10010 */  lwz     r30, 0x10(r1)
/* 0AF5B0 800B4B50 38210018 */  addi    r1, r1, 0x18
/* 0AF5B4 800B4B54 7C0803A6 */  mtlr    r0
/* 0AF5B8 800B4B58 4E800020 */  blr     

glabel DVDReadAbsAsyncPrio
/* 0AF5BC 800B4B5C 7C0802A6 */  mflr    r0
/* 0AF5C0 800B4B60 90010004 */  stw     r0, 4(r1)
/* 0AF5C4 800B4B64 38000001 */  li      r0, 1
/* 0AF5C8 800B4B68 9421FFC8 */  stwu    r1, -0x38(r1)
/* 0AF5CC 800B4B6C 93E10034 */  stw     r31, 0x34(r1)
/* 0AF5D0 800B4B70 3BE80000 */  addi    r31, r8, 0
/* 0AF5D4 800B4B74 93C10030 */  stw     r30, 0x30(r1)
/* 0AF5D8 800B4B78 93A1002C */  stw     r29, 0x2c(r1)
/* 0AF5DC 800B4B7C 3BA30000 */  addi    r29, r3, 0
/* 0AF5E0 800B4B80 90030008 */  stw     r0, 8(r3)
/* 0AF5E4 800B4B84 38000000 */  li      r0, 0
/* 0AF5E8 800B4B88 90830018 */  stw     r4, 0x18(r3)
/* 0AF5EC 800B4B8C 90A30014 */  stw     r5, 0x14(r3)
/* 0AF5F0 800B4B90 90C30010 */  stw     r6, 0x10(r3)
/* 0AF5F4 800B4B94 90030020 */  stw     r0, 0x20(r3)
/* 0AF5F8 800B4B98 90E30028 */  stw     r7, 0x28(r3)
/* 0AF5FC 800B4B9C 800D881C */  lwz     r0, autoInvalidation-_SDA_BASE_(r13)
/* 0AF600 800B4BA0 2C000000 */  cmpwi   r0, 0
/* 0AF604 800B4BA4 41820030 */  beq     lbl_800B4BD4
/* 0AF608 800B4BA8 807D0008 */  lwz     r3, 8(r29)
/* 0AF60C 800B4BAC 28030001 */  cmplwi  r3, 1
/* 0AF610 800B4BB0 41820018 */  beq     lbl_800B4BC8
/* 0AF614 800B4BB4 3803FFFC */  addi    r0, r3, -4
/* 0AF618 800B4BB8 28000001 */  cmplwi  r0, 1
/* 0AF61C 800B4BBC 4081000C */  ble     lbl_800B4BC8
/* 0AF620 800B4BC0 2803000E */  cmplwi  r3, 0xe
/* 0AF624 800B4BC4 40820010 */  bne     lbl_800B4BD4
lbl_800B4BC8:
/* 0AF628 800B4BC8 807D0018 */  lwz     r3, 0x18(r29)
/* 0AF62C 800B4BCC 809D0014 */  lwz     r4, 0x14(r29)
/* 0AF630 800B4BD0 4BFE8B81 */  bl      DCInvalidateRange
lbl_800B4BD4:
/* 0AF634 800B4BD4 4BFEA129 */  bl      OSDisableInterrupts
/* 0AF638 800B4BD8 38000002 */  li      r0, 2
/* 0AF63C 800B4BDC 901D000C */  stw     r0, 0xc(r29)
/* 0AF640 800B4BE0 3BC30000 */  addi    r30, r3, 0
/* 0AF644 800B4BE4 387F0000 */  addi    r3, r31, 0
/* 0AF648 800B4BE8 389D0000 */  addi    r4, r29, 0
/* 0AF64C 800B4BEC 48000AF1 */  bl      __DVDPushWaitingQueue
/* 0AF650 800B4BF0 800D8D30 */  lwz     r0, executing-_SDA_BASE_(r13)
/* 0AF654 800B4BF4 3BE30000 */  addi    r31, r3, 0
/* 0AF658 800B4BF8 28000000 */  cmplwi  r0, 0
/* 0AF65C 800B4BFC 40820014 */  bne     lbl_800B4C10
/* 0AF660 800B4C00 800D8D3C */  lwz     r0, PauseFlag-_SDA_BASE_(r13)
/* 0AF664 800B4C04 2C000000 */  cmpwi   r0, 0
/* 0AF668 800B4C08 40820008 */  bne     lbl_800B4C10
/* 0AF66C 800B4C0C 4BFFF3C9 */  bl      stateReady
lbl_800B4C10:
/* 0AF670 800B4C10 7FC3F378 */  mr      r3, r30
/* 0AF674 800B4C14 4BFEA111 */  bl      OSRestoreInterrupts
/* 0AF678 800B4C18 7FE3FB78 */  mr      r3, r31
/* 0AF67C 800B4C1C 8001003C */  lwz     r0, 0x3c(r1)
/* 0AF680 800B4C20 83E10034 */  lwz     r31, 0x34(r1)
/* 0AF684 800B4C24 83C10030 */  lwz     r30, 0x30(r1)
/* 0AF688 800B4C28 83A1002C */  lwz     r29, 0x2c(r1)
/* 0AF68C 800B4C2C 38210038 */  addi    r1, r1, 0x38
/* 0AF690 800B4C30 7C0803A6 */  mtlr    r0
/* 0AF694 800B4C34 4E800020 */  blr     

glabel DVDReadAbsAsyncForBS
/* 0AF698 800B4C38 7C0802A6 */  mflr    r0
/* 0AF69C 800B4C3C 90010004 */  stw     r0, 4(r1)
/* 0AF6A0 800B4C40 38000004 */  li      r0, 4
/* 0AF6A4 800B4C44 9421FFD0 */  stwu    r1, -0x30(r1)
/* 0AF6A8 800B4C48 93E1002C */  stw     r31, 0x2c(r1)
/* 0AF6AC 800B4C4C 3BE30000 */  addi    r31, r3, 0
/* 0AF6B0 800B4C50 93C10028 */  stw     r30, 0x28(r1)
/* 0AF6B4 800B4C54 90030008 */  stw     r0, 8(r3)
/* 0AF6B8 800B4C58 38000000 */  li      r0, 0
/* 0AF6BC 800B4C5C 90830018 */  stw     r4, 0x18(r3)
/* 0AF6C0 800B4C60 90A30014 */  stw     r5, 0x14(r3)
/* 0AF6C4 800B4C64 90C30010 */  stw     r6, 0x10(r3)
/* 0AF6C8 800B4C68 90030020 */  stw     r0, 0x20(r3)
/* 0AF6CC 800B4C6C 90E30028 */  stw     r7, 0x28(r3)
/* 0AF6D0 800B4C70 800D881C */  lwz     r0, autoInvalidation-_SDA_BASE_(r13)
/* 0AF6D4 800B4C74 2C000000 */  cmpwi   r0, 0
/* 0AF6D8 800B4C78 41820030 */  beq     lbl_800B4CA8
/* 0AF6DC 800B4C7C 807F0008 */  lwz     r3, 8(r31)
/* 0AF6E0 800B4C80 28030001 */  cmplwi  r3, 1
/* 0AF6E4 800B4C84 41820018 */  beq     lbl_800B4C9C
/* 0AF6E8 800B4C88 3803FFFC */  addi    r0, r3, -4
/* 0AF6EC 800B4C8C 28000001 */  cmplwi  r0, 1
/* 0AF6F0 800B4C90 4081000C */  ble     lbl_800B4C9C
/* 0AF6F4 800B4C94 2803000E */  cmplwi  r3, 0xe
/* 0AF6F8 800B4C98 40820010 */  bne     lbl_800B4CA8
lbl_800B4C9C:
/* 0AF6FC 800B4C9C 807F0018 */  lwz     r3, 0x18(r31)
/* 0AF700 800B4CA0 809F0014 */  lwz     r4, 0x14(r31)
/* 0AF704 800B4CA4 4BFE8AAD */  bl      DCInvalidateRange
lbl_800B4CA8:
/* 0AF708 800B4CA8 4BFEA055 */  bl      OSDisableInterrupts
/* 0AF70C 800B4CAC 38000002 */  li      r0, 2
/* 0AF710 800B4CB0 901F000C */  stw     r0, 0xc(r31)
/* 0AF714 800B4CB4 3BC30000 */  addi    r30, r3, 0
/* 0AF718 800B4CB8 389F0000 */  addi    r4, r31, 0
/* 0AF71C 800B4CBC 38600002 */  li      r3, 2
/* 0AF720 800B4CC0 48000A1D */  bl      __DVDPushWaitingQueue
/* 0AF724 800B4CC4 800D8D30 */  lwz     r0, executing-_SDA_BASE_(r13)
/* 0AF728 800B4CC8 3BE30000 */  addi    r31, r3, 0
/* 0AF72C 800B4CCC 28000000 */  cmplwi  r0, 0
/* 0AF730 800B4CD0 40820014 */  bne     lbl_800B4CE4
/* 0AF734 800B4CD4 800D8D3C */  lwz     r0, PauseFlag-_SDA_BASE_(r13)
/* 0AF738 800B4CD8 2C000000 */  cmpwi   r0, 0
/* 0AF73C 800B4CDC 40820008 */  bne     lbl_800B4CE4
/* 0AF740 800B4CE0 4BFFF2F5 */  bl      stateReady
lbl_800B4CE4:
/* 0AF744 800B4CE4 7FC3F378 */  mr      r3, r30
/* 0AF748 800B4CE8 4BFEA03D */  bl      OSRestoreInterrupts
/* 0AF74C 800B4CEC 7FE3FB78 */  mr      r3, r31
/* 0AF750 800B4CF0 80010034 */  lwz     r0, 0x34(r1)
/* 0AF754 800B4CF4 83E1002C */  lwz     r31, 0x2c(r1)
/* 0AF758 800B4CF8 83C10028 */  lwz     r30, 0x28(r1)
/* 0AF75C 800B4CFC 38210030 */  addi    r1, r1, 0x30
/* 0AF760 800B4D00 7C0803A6 */  mtlr    r0
/* 0AF764 800B4D04 4E800020 */  blr     

glabel DVDReadDiskID
/* 0AF768 800B4D08 7C0802A6 */  mflr    r0
/* 0AF76C 800B4D0C 90010004 */  stw     r0, 4(r1)
/* 0AF770 800B4D10 38000005 */  li      r0, 5
/* 0AF774 800B4D14 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0AF778 800B4D18 93E10024 */  stw     r31, 0x24(r1)
/* 0AF77C 800B4D1C 3BE30000 */  addi    r31, r3, 0
/* 0AF780 800B4D20 93C10020 */  stw     r30, 0x20(r1)
/* 0AF784 800B4D24 90030008 */  stw     r0, 8(r3)
/* 0AF788 800B4D28 38600020 */  li      r3, 0x20
/* 0AF78C 800B4D2C 38000000 */  li      r0, 0
/* 0AF790 800B4D30 909F0018 */  stw     r4, 0x18(r31)
/* 0AF794 800B4D34 907F0014 */  stw     r3, 0x14(r31)
/* 0AF798 800B4D38 901F0010 */  stw     r0, 0x10(r31)
/* 0AF79C 800B4D3C 901F0020 */  stw     r0, 0x20(r31)
/* 0AF7A0 800B4D40 90BF0028 */  stw     r5, 0x28(r31)
/* 0AF7A4 800B4D44 800D881C */  lwz     r0, autoInvalidation-_SDA_BASE_(r13)
/* 0AF7A8 800B4D48 2C000000 */  cmpwi   r0, 0
/* 0AF7AC 800B4D4C 41820030 */  beq     lbl_800B4D7C
/* 0AF7B0 800B4D50 807F0008 */  lwz     r3, 8(r31)
/* 0AF7B4 800B4D54 28030001 */  cmplwi  r3, 1
/* 0AF7B8 800B4D58 41820018 */  beq     lbl_800B4D70
/* 0AF7BC 800B4D5C 3803FFFC */  addi    r0, r3, -4
/* 0AF7C0 800B4D60 28000001 */  cmplwi  r0, 1
/* 0AF7C4 800B4D64 4081000C */  ble     lbl_800B4D70
/* 0AF7C8 800B4D68 2803000E */  cmplwi  r3, 0xe
/* 0AF7CC 800B4D6C 40820010 */  bne     lbl_800B4D7C
lbl_800B4D70:
/* 0AF7D0 800B4D70 807F0018 */  lwz     r3, 0x18(r31)
/* 0AF7D4 800B4D74 809F0014 */  lwz     r4, 0x14(r31)
/* 0AF7D8 800B4D78 4BFE89D9 */  bl      DCInvalidateRange
lbl_800B4D7C:
/* 0AF7DC 800B4D7C 4BFE9F81 */  bl      OSDisableInterrupts
/* 0AF7E0 800B4D80 38000002 */  li      r0, 2
/* 0AF7E4 800B4D84 901F000C */  stw     r0, 0xc(r31)
/* 0AF7E8 800B4D88 3BC30000 */  addi    r30, r3, 0
/* 0AF7EC 800B4D8C 389F0000 */  addi    r4, r31, 0
/* 0AF7F0 800B4D90 38600002 */  li      r3, 2
/* 0AF7F4 800B4D94 48000949 */  bl      __DVDPushWaitingQueue
/* 0AF7F8 800B4D98 800D8D30 */  lwz     r0, executing-_SDA_BASE_(r13)
/* 0AF7FC 800B4D9C 3BE30000 */  addi    r31, r3, 0
/* 0AF800 800B4DA0 28000000 */  cmplwi  r0, 0
/* 0AF804 800B4DA4 40820014 */  bne     lbl_800B4DB8
/* 0AF808 800B4DA8 800D8D3C */  lwz     r0, PauseFlag-_SDA_BASE_(r13)
/* 0AF80C 800B4DAC 2C000000 */  cmpwi   r0, 0
/* 0AF810 800B4DB0 40820008 */  bne     lbl_800B4DB8
/* 0AF814 800B4DB4 4BFFF221 */  bl      stateReady
lbl_800B4DB8:
/* 0AF818 800B4DB8 7FC3F378 */  mr      r3, r30
/* 0AF81C 800B4DBC 4BFE9F69 */  bl      OSRestoreInterrupts
/* 0AF820 800B4DC0 7FE3FB78 */  mr      r3, r31
/* 0AF824 800B4DC4 8001002C */  lwz     r0, 0x2c(r1)
/* 0AF828 800B4DC8 83E10024 */  lwz     r31, 0x24(r1)
/* 0AF82C 800B4DCC 83C10020 */  lwz     r30, 0x20(r1)
/* 0AF830 800B4DD0 38210028 */  addi    r1, r1, 0x28
/* 0AF834 800B4DD4 7C0803A6 */  mtlr    r0
/* 0AF838 800B4DD8 4E800020 */  blr     

glabel DVDCancelStreamAsync
/* 0AF83C 800B4DDC 7C0802A6 */  mflr    r0
/* 0AF840 800B4DE0 90010004 */  stw     r0, 4(r1)
/* 0AF844 800B4DE4 38000007 */  li      r0, 7
/* 0AF848 800B4DE8 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0AF84C 800B4DEC 93E1001C */  stw     r31, 0x1c(r1)
/* 0AF850 800B4DF0 3BE30000 */  addi    r31, r3, 0
/* 0AF854 800B4DF4 93C10018 */  stw     r30, 0x18(r1)
/* 0AF858 800B4DF8 90030008 */  stw     r0, 8(r3)
/* 0AF85C 800B4DFC 90830028 */  stw     r4, 0x28(r3)
/* 0AF860 800B4E00 800D881C */  lwz     r0, autoInvalidation-_SDA_BASE_(r13)
/* 0AF864 800B4E04 2C000000 */  cmpwi   r0, 0
/* 0AF868 800B4E08 41820030 */  beq     lbl_800B4E38
/* 0AF86C 800B4E0C 807F0008 */  lwz     r3, 8(r31)
/* 0AF870 800B4E10 28030001 */  cmplwi  r3, 1
/* 0AF874 800B4E14 41820018 */  beq     lbl_800B4E2C
/* 0AF878 800B4E18 3803FFFC */  addi    r0, r3, -4
/* 0AF87C 800B4E1C 28000001 */  cmplwi  r0, 1
/* 0AF880 800B4E20 4081000C */  ble     lbl_800B4E2C
/* 0AF884 800B4E24 2803000E */  cmplwi  r3, 0xe
/* 0AF888 800B4E28 40820010 */  bne     lbl_800B4E38
lbl_800B4E2C:
/* 0AF88C 800B4E2C 807F0018 */  lwz     r3, 0x18(r31)
/* 0AF890 800B4E30 809F0014 */  lwz     r4, 0x14(r31)
/* 0AF894 800B4E34 4BFE891D */  bl      DCInvalidateRange
lbl_800B4E38:
/* 0AF898 800B4E38 4BFE9EC5 */  bl      OSDisableInterrupts
/* 0AF89C 800B4E3C 38000002 */  li      r0, 2
/* 0AF8A0 800B4E40 901F000C */  stw     r0, 0xc(r31)
/* 0AF8A4 800B4E44 3BC30000 */  addi    r30, r3, 0
/* 0AF8A8 800B4E48 389F0000 */  addi    r4, r31, 0
/* 0AF8AC 800B4E4C 38600001 */  li      r3, 1
/* 0AF8B0 800B4E50 4800088D */  bl      __DVDPushWaitingQueue
/* 0AF8B4 800B4E54 800D8D30 */  lwz     r0, executing-_SDA_BASE_(r13)
/* 0AF8B8 800B4E58 3BE30000 */  addi    r31, r3, 0
/* 0AF8BC 800B4E5C 28000000 */  cmplwi  r0, 0
/* 0AF8C0 800B4E60 40820014 */  bne     lbl_800B4E74
/* 0AF8C4 800B4E64 800D8D3C */  lwz     r0, PauseFlag-_SDA_BASE_(r13)
/* 0AF8C8 800B4E68 2C000000 */  cmpwi   r0, 0
/* 0AF8CC 800B4E6C 40820008 */  bne     lbl_800B4E74
/* 0AF8D0 800B4E70 4BFFF165 */  bl      stateReady
lbl_800B4E74:
/* 0AF8D4 800B4E74 7FC3F378 */  mr      r3, r30
/* 0AF8D8 800B4E78 4BFE9EAD */  bl      OSRestoreInterrupts
/* 0AF8DC 800B4E7C 7FE3FB78 */  mr      r3, r31
/* 0AF8E0 800B4E80 80010024 */  lwz     r0, 0x24(r1)
/* 0AF8E4 800B4E84 83E1001C */  lwz     r31, 0x1c(r1)
/* 0AF8E8 800B4E88 83C10018 */  lwz     r30, 0x18(r1)
/* 0AF8EC 800B4E8C 38210020 */  addi    r1, r1, 0x20
/* 0AF8F0 800B4E90 7C0803A6 */  mtlr    r0
/* 0AF8F4 800B4E94 4E800020 */  blr     

glabel DVDInquiryAsync
/* 0AF8F8 800B4E98 7C0802A6 */  mflr    r0
/* 0AF8FC 800B4E9C 90010004 */  stw     r0, 4(r1)
/* 0AF900 800B4EA0 3800000E */  li      r0, 0xe
/* 0AF904 800B4EA4 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0AF908 800B4EA8 93E10024 */  stw     r31, 0x24(r1)
/* 0AF90C 800B4EAC 3BE30000 */  addi    r31, r3, 0
/* 0AF910 800B4EB0 93C10020 */  stw     r30, 0x20(r1)
/* 0AF914 800B4EB4 90030008 */  stw     r0, 8(r3)
/* 0AF918 800B4EB8 38600020 */  li      r3, 0x20
/* 0AF91C 800B4EBC 38000000 */  li      r0, 0
/* 0AF920 800B4EC0 909F0018 */  stw     r4, 0x18(r31)
/* 0AF924 800B4EC4 907F0014 */  stw     r3, 0x14(r31)
/* 0AF928 800B4EC8 901F0020 */  stw     r0, 0x20(r31)
/* 0AF92C 800B4ECC 90BF0028 */  stw     r5, 0x28(r31)
/* 0AF930 800B4ED0 800D881C */  lwz     r0, autoInvalidation-_SDA_BASE_(r13)
/* 0AF934 800B4ED4 2C000000 */  cmpwi   r0, 0
/* 0AF938 800B4ED8 41820030 */  beq     lbl_800B4F08
/* 0AF93C 800B4EDC 807F0008 */  lwz     r3, 8(r31)
/* 0AF940 800B4EE0 28030001 */  cmplwi  r3, 1
/* 0AF944 800B4EE4 41820018 */  beq     lbl_800B4EFC
/* 0AF948 800B4EE8 3803FFFC */  addi    r0, r3, -4
/* 0AF94C 800B4EEC 28000001 */  cmplwi  r0, 1
/* 0AF950 800B4EF0 4081000C */  ble     lbl_800B4EFC
/* 0AF954 800B4EF4 2803000E */  cmplwi  r3, 0xe
/* 0AF958 800B4EF8 40820010 */  bne     lbl_800B4F08
lbl_800B4EFC:
/* 0AF95C 800B4EFC 807F0018 */  lwz     r3, 0x18(r31)
/* 0AF960 800B4F00 809F0014 */  lwz     r4, 0x14(r31)
/* 0AF964 800B4F04 4BFE884D */  bl      DCInvalidateRange
lbl_800B4F08:
/* 0AF968 800B4F08 4BFE9DF5 */  bl      OSDisableInterrupts
/* 0AF96C 800B4F0C 38000002 */  li      r0, 2
/* 0AF970 800B4F10 901F000C */  stw     r0, 0xc(r31)
/* 0AF974 800B4F14 3BC30000 */  addi    r30, r3, 0
/* 0AF978 800B4F18 389F0000 */  addi    r4, r31, 0
/* 0AF97C 800B4F1C 38600002 */  li      r3, 2
/* 0AF980 800B4F20 480007BD */  bl      __DVDPushWaitingQueue
/* 0AF984 800B4F24 800D8D30 */  lwz     r0, executing-_SDA_BASE_(r13)
/* 0AF988 800B4F28 3BE30000 */  addi    r31, r3, 0
/* 0AF98C 800B4F2C 28000000 */  cmplwi  r0, 0
/* 0AF990 800B4F30 40820014 */  bne     lbl_800B4F44
/* 0AF994 800B4F34 800D8D3C */  lwz     r0, PauseFlag-_SDA_BASE_(r13)
/* 0AF998 800B4F38 2C000000 */  cmpwi   r0, 0
/* 0AF99C 800B4F3C 40820008 */  bne     lbl_800B4F44
/* 0AF9A0 800B4F40 4BFFF095 */  bl      stateReady
lbl_800B4F44:
/* 0AF9A4 800B4F44 7FC3F378 */  mr      r3, r30
/* 0AF9A8 800B4F48 4BFE9DDD */  bl      OSRestoreInterrupts
/* 0AF9AC 800B4F4C 7FE3FB78 */  mr      r3, r31
/* 0AF9B0 800B4F50 8001002C */  lwz     r0, 0x2c(r1)
/* 0AF9B4 800B4F54 83E10024 */  lwz     r31, 0x24(r1)
/* 0AF9B8 800B4F58 83C10020 */  lwz     r30, 0x20(r1)
/* 0AF9BC 800B4F5C 38210028 */  addi    r1, r1, 0x28
/* 0AF9C0 800B4F60 7C0803A6 */  mtlr    r0
/* 0AF9C4 800B4F64 4E800020 */  blr     

glabel DVDReset
/* 0AF9C8 800B4F68 7C0802A6 */  mflr    r0
/* 0AF9CC 800B4F6C 90010004 */  stw     r0, 4(r1)
/* 0AF9D0 800B4F70 9421FFF8 */  stwu    r1, -8(r1)
/* 0AF9D4 800B4F74 4BFFD62D */  bl      DVDLowReset
/* 0AF9D8 800B4F78 3C60CC00 */  lis     r3, DI_REGS_BASE@ha
/* 0AF9DC 800B4F7C 3800002A */  li      r0, 0x2a
/* 0AF9E0 800B4F80 90036000 */  stw     r0, (DI_REGS_BASE + DI_DISR)@l(r3)
/* 0AF9E4 800B4F84 38836000 */  addi    r4, r3, DI_REGS_BASE@l
/* 0AF9E8 800B4F88 38000000 */  li      r0, 0
/* 0AF9EC 800B4F8C 80636004 */  lwz     r3, (DI_REGS_BASE + DI_DICVR)@l(r3)
/* 0AF9F0 800B4F90 90640004 */  stw     r3, 4(r4)
/* 0AF9F4 800B4F94 900D8D68 */  stw     r0, ResetRequired-_SDA_BASE_(r13)
/* 0AF9F8 800B4F98 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
/* 0AF9FC 800B4F9C 8001000C */  lwz     r0, 0xc(r1)
/* 0AFA00 800B4FA0 38210008 */  addi    r1, r1, 8
/* 0AFA04 800B4FA4 7C0803A6 */  mtlr    r0
/* 0AFA08 800B4FA8 4E800020 */  blr     

glabel DVDGetCommandBlockStatus
/* 0AFA0C 800B4FAC 7C0802A6 */  mflr    r0
/* 0AFA10 800B4FB0 90010004 */  stw     r0, 4(r1)
/* 0AFA14 800B4FB4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AFA18 800B4FB8 93E10014 */  stw     r31, 0x14(r1)
/* 0AFA1C 800B4FBC 7C7F1B78 */  mr      r31, r3
/* 0AFA20 800B4FC0 4BFE9D3D */  bl      OSDisableInterrupts
/* 0AFA24 800B4FC4 801F000C */  lwz     r0, 0xc(r31)
/* 0AFA28 800B4FC8 2C000003 */  cmpwi   r0, 3
/* 0AFA2C 800B4FCC 4082000C */  bne     lbl_800B4FD8
/* 0AFA30 800B4FD0 3BE00001 */  li      r31, 1
/* 0AFA34 800B4FD4 48000008 */  b       lbl_800B4FDC
lbl_800B4FD8:
/* 0AFA38 800B4FD8 7C1F0378 */  mr      r31, r0
lbl_800B4FDC:
/* 0AFA3C 800B4FDC 4BFE9D49 */  bl      OSRestoreInterrupts
/* 0AFA40 800B4FE0 7FE3FB78 */  mr      r3, r31
/* 0AFA44 800B4FE4 8001001C */  lwz     r0, 0x1c(r1)
/* 0AFA48 800B4FE8 83E10014 */  lwz     r31, 0x14(r1)
/* 0AFA4C 800B4FEC 38210018 */  addi    r1, r1, 0x18
/* 0AFA50 800B4FF0 7C0803A6 */  mtlr    r0
/* 0AFA54 800B4FF4 4E800020 */  blr     

glabel DVDGetDriveStatus
/* 0AFA58 800B4FF8 7C0802A6 */  mflr    r0
/* 0AFA5C 800B4FFC 90010004 */  stw     r0, 4(r1)
/* 0AFA60 800B5000 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AFA64 800B5004 93E10014 */  stw     r31, 0x14(r1)
/* 0AFA68 800B5008 93C10010 */  stw     r30, 0x10(r1)
/* 0AFA6C 800B500C 4BFE9CF1 */  bl      OSDisableInterrupts
/* 0AFA70 800B5010 800D8D48 */  lwz     r0, FatalErrorFlag-_SDA_BASE_(r13)
/* 0AFA74 800B5014 3BC30000 */  addi    r30, r3, 0
/* 0AFA78 800B5018 2C000000 */  cmpwi   r0, 0
/* 0AFA7C 800B501C 4182000C */  beq     lbl_800B5028
/* 0AFA80 800B5020 3BE0FFFF */  li      r31, -1
/* 0AFA84 800B5024 4800005C */  b       lbl_800B5080
lbl_800B5028:
/* 0AFA88 800B5028 800D8D40 */  lwz     r0, PausingFlag-_SDA_BASE_(r13)
/* 0AFA8C 800B502C 2C000000 */  cmpwi   r0, 0
/* 0AFA90 800B5030 4182000C */  beq     lbl_800B503C
/* 0AFA94 800B5034 3BE00008 */  li      r31, 8
/* 0AFA98 800B5038 48000048 */  b       lbl_800B5080
lbl_800B503C:
/* 0AFA9C 800B503C 83ED8D30 */  lwz     r31, executing-_SDA_BASE_(r13)
/* 0AFAA0 800B5040 281F0000 */  cmplwi  r31, 0
/* 0AFAA4 800B5044 4082000C */  bne     lbl_800B5050
/* 0AFAA8 800B5048 3BE00000 */  li      r31, 0
/* 0AFAAC 800B504C 48000034 */  b       lbl_800B5080
lbl_800B5050:
/* 0AFAB0 800B5050 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0AFAB4 800B5054 380325E0 */  addi    r0, r3, DummyCommandBlock@l
/* 0AFAB8 800B5058 7C1F0040 */  cmplw   r31, r0
/* 0AFABC 800B505C 4082000C */  bne     lbl_800B5068
/* 0AFAC0 800B5060 3BE00000 */  li      r31, 0
/* 0AFAC4 800B5064 4800001C */  b       lbl_800B5080
lbl_800B5068:
/* 0AFAC8 800B5068 4BFE9C95 */  bl      OSDisableInterrupts
/* 0AFACC 800B506C 83FF000C */  lwz     r31, 0xc(r31)
/* 0AFAD0 800B5070 2C1F0003 */  cmpwi   r31, 3
/* 0AFAD4 800B5074 40820008 */  bne     lbl_800B507C
/* 0AFAD8 800B5078 3BE00001 */  li      r31, 1
lbl_800B507C:
/* 0AFADC 800B507C 4BFE9CA9 */  bl      OSRestoreInterrupts
lbl_800B5080:
/* 0AFAE0 800B5080 7FC3F378 */  mr      r3, r30
/* 0AFAE4 800B5084 4BFE9CA1 */  bl      OSRestoreInterrupts
/* 0AFAE8 800B5088 7FE3FB78 */  mr      r3, r31
/* 0AFAEC 800B508C 8001001C */  lwz     r0, 0x1c(r1)
/* 0AFAF0 800B5090 83E10014 */  lwz     r31, 0x14(r1)
/* 0AFAF4 800B5094 83C10010 */  lwz     r30, 0x10(r1)
/* 0AFAF8 800B5098 38210018 */  addi    r1, r1, 0x18
/* 0AFAFC 800B509C 7C0803A6 */  mtlr    r0
/* 0AFB00 800B50A0 4E800020 */  blr     

glabel DVDSetAutoInvalidation
/* 0AFB04 800B50A4 800D881C */  lwz     r0, autoInvalidation-_SDA_BASE_(r13)
/* 0AFB08 800B50A8 906D881C */  stw     r3, autoInvalidation-_SDA_BASE_(r13)
/* 0AFB0C 800B50AC 7C030378 */  mr      r3, r0
/* 0AFB10 800B50B0 4E800020 */  blr     

glabel DVDResume
/* 0AFB14 800B50B4 7C0802A6 */  mflr    r0
/* 0AFB18 800B50B8 90010004 */  stw     r0, 4(r1)
/* 0AFB1C 800B50BC 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0AFB20 800B50C0 93E1000C */  stw     r31, 0xc(r1)
/* 0AFB24 800B50C4 4BFE9C39 */  bl      OSDisableInterrupts
/* 0AFB28 800B50C8 38800000 */  li      r4, 0
/* 0AFB2C 800B50CC 908D8D3C */  stw     r4, PauseFlag-_SDA_BASE_(r13)
/* 0AFB30 800B50D0 7C7F1B78 */  mr      r31, r3
/* 0AFB34 800B50D4 800D8D40 */  lwz     r0, PausingFlag-_SDA_BASE_(r13)
/* 0AFB38 800B50D8 2C000000 */  cmpwi   r0, 0
/* 0AFB3C 800B50DC 4182000C */  beq     lbl_800B50E8
/* 0AFB40 800B50E0 908D8D40 */  stw     r4, PausingFlag-_SDA_BASE_(r13)
/* 0AFB44 800B50E4 4BFFEEF1 */  bl      stateReady
lbl_800B50E8:
/* 0AFB48 800B50E8 7FE3FB78 */  mr      r3, r31
/* 0AFB4C 800B50EC 4BFE9C39 */  bl      OSRestoreInterrupts
/* 0AFB50 800B50F0 80010014 */  lwz     r0, 0x14(r1)
/* 0AFB54 800B50F4 83E1000C */  lwz     r31, 0xc(r1)
/* 0AFB58 800B50F8 38210010 */  addi    r1, r1, 0x10
/* 0AFB5C 800B50FC 7C0803A6 */  mtlr    r0
/* 0AFB60 800B5100 4E800020 */  blr     

glabel DVDCancelAsync
/* 0AFB64 800B5104 7C0802A6 */  mflr    r0
/* 0AFB68 800B5108 90010004 */  stw     r0, 4(r1)
/* 0AFB6C 800B510C 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0AFB70 800B5110 93E10024 */  stw     r31, 0x24(r1)
/* 0AFB74 800B5114 93C10020 */  stw     r30, 0x20(r1)
/* 0AFB78 800B5118 3BC40000 */  addi    r30, r4, 0
/* 0AFB7C 800B511C 93A1001C */  stw     r29, 0x1c(r1)
/* 0AFB80 800B5120 3BA30000 */  addi    r29, r3, 0
/* 0AFB84 800B5124 4BFE9BD9 */  bl      OSDisableInterrupts
/* 0AFB88 800B5128 809D000C */  lwz     r4, 0xc(r29)
/* 0AFB8C 800B512C 3BE30000 */  addi    r31, r3, 0
/* 0AFB90 800B5130 38040001 */  addi    r0, r4, 1
/* 0AFB94 800B5134 2800000C */  cmplwi  r0, 0xc
/* 0AFB98 800B5138 41810220 */  bgt     lbl_800B5358
/* 0AFB9C 800B513C 3C60800F */  lis     r3, jtbl_800F2578@ha
/* 0AFBA0 800B5140 38632578 */  addi    r3, r3, jtbl_800F2578@l
/* 0AFBA4 800B5144 5400103A */  slwi    r0, r0, 2
/* 0AFBA8 800B5148 7C03002E */  lwzx    r0, r3, r0
/* 0AFBAC 800B514C 7C0903A6 */  mtctr   r0
/* 0AFBB0 800B5150 4E800420 */  bctr    
glabel lbl_800B5154
/* 0AFBB4 800B5154 281E0000 */  cmplwi  r30, 0
/* 0AFBB8 800B5158 41820200 */  beq     lbl_800B5358
/* 0AFBBC 800B515C 399E0000 */  addi    r12, r30, 0
/* 0AFBC0 800B5160 7D8803A6 */  mtlr    r12
/* 0AFBC4 800B5164 389D0000 */  addi    r4, r29, 0
/* 0AFBC8 800B5168 38600000 */  li      r3, 0
/* 0AFBCC 800B516C 4E800021 */  blrl    
/* 0AFBD0 800B5170 480001E8 */  b       lbl_800B5358
glabel lbl_800B5174
/* 0AFBD4 800B5174 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AFBD8 800B5178 28000000 */  cmplwi  r0, 0
/* 0AFBDC 800B517C 41820014 */  beq     lbl_800B5190
/* 0AFBE0 800B5180 7FE3FB78 */  mr      r3, r31
/* 0AFBE4 800B5184 4BFE9BA1 */  bl      OSRestoreInterrupts
/* 0AFBE8 800B5188 38600000 */  li      r3, 0
/* 0AFBEC 800B518C 480001D8 */  b       lbl_800B5364
lbl_800B5190:
/* 0AFBF0 800B5190 38000001 */  li      r0, 1
/* 0AFBF4 800B5194 93CD8D54 */  stw     r30, CancelCallback-_SDA_BASE_(r13)
/* 0AFBF8 800B5198 900D8D50 */  stw     r0, Canceling-_SDA_BASE_(r13)
/* 0AFBFC 800B519C 801D0008 */  lwz     r0, 8(r29)
/* 0AFC00 800B51A0 28000004 */  cmplwi  r0, 4
/* 0AFC04 800B51A4 4182000C */  beq     lbl_800B51B0
/* 0AFC08 800B51A8 28000001 */  cmplwi  r0, 1
/* 0AFC0C 800B51AC 408201AC */  bne     lbl_800B5358
lbl_800B51B0:
/* 0AFC10 800B51B0 4BFFD4AD */  bl      DVDLowBreak
/* 0AFC14 800B51B4 480001A4 */  b       lbl_800B5358
glabel lbl_800B51B8
/* 0AFC18 800B51B8 7FA3EB78 */  mr      r3, r29
/* 0AFC1C 800B51BC 48000681 */  bl      __DVDDequeueWaitingQueue
/* 0AFC20 800B51C0 3800000A */  li      r0, 0xa
/* 0AFC24 800B51C4 901D000C */  stw     r0, 0xc(r29)
/* 0AFC28 800B51C8 819D0028 */  lwz     r12, 0x28(r29)
/* 0AFC2C 800B51CC 280C0000 */  cmplwi  r12, 0
/* 0AFC30 800B51D0 41820014 */  beq     lbl_800B51E4
/* 0AFC34 800B51D4 7D8803A6 */  mtlr    r12
/* 0AFC38 800B51D8 389D0000 */  addi    r4, r29, 0
/* 0AFC3C 800B51DC 3860FFFD */  li      r3, -3
/* 0AFC40 800B51E0 4E800021 */  blrl    
lbl_800B51E4:
/* 0AFC44 800B51E4 281E0000 */  cmplwi  r30, 0
/* 0AFC48 800B51E8 41820170 */  beq     lbl_800B5358
/* 0AFC4C 800B51EC 399E0000 */  addi    r12, r30, 0
/* 0AFC50 800B51F0 7D8803A6 */  mtlr    r12
/* 0AFC54 800B51F4 389D0000 */  addi    r4, r29, 0
/* 0AFC58 800B51F8 38600000 */  li      r3, 0
/* 0AFC5C 800B51FC 4E800021 */  blrl    
/* 0AFC60 800B5200 48000158 */  b       lbl_800B5358
glabel lbl_800B5204
/* 0AFC64 800B5204 801D0008 */  lwz     r0, 8(r29)
/* 0AFC68 800B5208 2C00000D */  cmpwi   r0, 0xd
/* 0AFC6C 800B520C 41820028 */  beq     lbl_800B5234
/* 0AFC70 800B5210 40800018 */  bge     lbl_800B5228
/* 0AFC74 800B5214 2C000006 */  cmpwi   r0, 6
/* 0AFC78 800B5218 4080003C */  bge     lbl_800B5254
/* 0AFC7C 800B521C 2C000004 */  cmpwi   r0, 4
/* 0AFC80 800B5220 40800014 */  bge     lbl_800B5234
/* 0AFC84 800B5224 48000030 */  b       lbl_800B5254
lbl_800B5228:
/* 0AFC88 800B5228 2C00000F */  cmpwi   r0, 0xf
/* 0AFC8C 800B522C 41820008 */  beq     lbl_800B5234
/* 0AFC90 800B5230 48000024 */  b       lbl_800B5254
lbl_800B5234:
/* 0AFC94 800B5234 281E0000 */  cmplwi  r30, 0
/* 0AFC98 800B5238 41820120 */  beq     lbl_800B5358
/* 0AFC9C 800B523C 399E0000 */  addi    r12, r30, 0
/* 0AFCA0 800B5240 7D8803A6 */  mtlr    r12
/* 0AFCA4 800B5244 389D0000 */  addi    r4, r29, 0
/* 0AFCA8 800B5248 38600000 */  li      r3, 0
/* 0AFCAC 800B524C 4E800021 */  blrl    
/* 0AFCB0 800B5250 48000108 */  b       lbl_800B5358
lbl_800B5254:
/* 0AFCB4 800B5254 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AFCB8 800B5258 28000000 */  cmplwi  r0, 0
/* 0AFCBC 800B525C 41820014 */  beq     lbl_800B5270
/* 0AFCC0 800B5260 7FE3FB78 */  mr      r3, r31
/* 0AFCC4 800B5264 4BFE9AC1 */  bl      OSRestoreInterrupts
/* 0AFCC8 800B5268 38600000 */  li      r3, 0
/* 0AFCCC 800B526C 480000F8 */  b       lbl_800B5364
lbl_800B5270:
/* 0AFCD0 800B5270 38000001 */  li      r0, 1
/* 0AFCD4 800B5274 93CD8D54 */  stw     r30, CancelCallback-_SDA_BASE_(r13)
/* 0AFCD8 800B5278 900D8D50 */  stw     r0, Canceling-_SDA_BASE_(r13)
/* 0AFCDC 800B527C 480000DC */  b       lbl_800B5358
glabel lbl_800B5280
/* 0AFCE0 800B5280 4BFFD3F1 */  bl      DVDLowClearCallback
/* 0AFCE4 800B5284 3C80800B */  lis     r4, cbForStateMotorStopped@ha
/* 0AFCE8 800B5288 38043EF0 */  addi    r0, r4, cbForStateMotorStopped@l
/* 0AFCEC 800B528C 7C030040 */  cmplw   r3, r0
/* 0AFCF0 800B5290 41820014 */  beq     lbl_800B52A4
/* 0AFCF4 800B5294 7FE3FB78 */  mr      r3, r31
/* 0AFCF8 800B5298 4BFE9A8D */  bl      OSRestoreInterrupts
/* 0AFCFC 800B529C 38600000 */  li      r3, 0
/* 0AFD00 800B52A0 480000C4 */  b       lbl_800B5364
lbl_800B52A4:
/* 0AFD04 800B52A4 801D000C */  lwz     r0, 0xc(r29)
/* 0AFD08 800B52A8 2C000004 */  cmpwi   r0, 4
/* 0AFD0C 800B52AC 4082000C */  bne     lbl_800B52B8
/* 0AFD10 800B52B0 38000003 */  li      r0, 3
/* 0AFD14 800B52B4 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_800B52B8:
/* 0AFD18 800B52B8 801D000C */  lwz     r0, 0xc(r29)
/* 0AFD1C 800B52BC 2C000005 */  cmpwi   r0, 5
/* 0AFD20 800B52C0 4082000C */  bne     lbl_800B52CC
/* 0AFD24 800B52C4 38000004 */  li      r0, 4
/* 0AFD28 800B52C8 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_800B52CC:
/* 0AFD2C 800B52CC 801D000C */  lwz     r0, 0xc(r29)
/* 0AFD30 800B52D0 2C000006 */  cmpwi   r0, 6
/* 0AFD34 800B52D4 4082000C */  bne     lbl_800B52E0
/* 0AFD38 800B52D8 38000001 */  li      r0, 1
/* 0AFD3C 800B52DC 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_800B52E0:
/* 0AFD40 800B52E0 801D000C */  lwz     r0, 0xc(r29)
/* 0AFD44 800B52E4 2C00000B */  cmpwi   r0, 0xb
/* 0AFD48 800B52E8 4082000C */  bne     lbl_800B52F4
/* 0AFD4C 800B52EC 38000002 */  li      r0, 2
/* 0AFD50 800B52F0 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_800B52F4:
/* 0AFD54 800B52F4 801D000C */  lwz     r0, 0xc(r29)
/* 0AFD58 800B52F8 2C000007 */  cmpwi   r0, 7
/* 0AFD5C 800B52FC 4082000C */  bne     lbl_800B5308
/* 0AFD60 800B5300 38000007 */  li      r0, 7
/* 0AFD64 800B5304 900D8D58 */  stw     r0, ResumeFromHere-_SDA_BASE_(r13)
lbl_800B5308:
/* 0AFD68 800B5308 3C608013 */  lis     r3, DummyCommandBlock@ha
/* 0AFD6C 800B530C 380325E0 */  addi    r0, r3, DummyCommandBlock@l
/* 0AFD70 800B5310 900D8D30 */  stw     r0, executing-_SDA_BASE_(r13)
/* 0AFD74 800B5314 3800000A */  li      r0, 0xa
/* 0AFD78 800B5318 901D000C */  stw     r0, 0xc(r29)
/* 0AFD7C 800B531C 819D0028 */  lwz     r12, 0x28(r29)
/* 0AFD80 800B5320 280C0000 */  cmplwi  r12, 0
/* 0AFD84 800B5324 41820014 */  beq     lbl_800B5338
/* 0AFD88 800B5328 7D8803A6 */  mtlr    r12
/* 0AFD8C 800B532C 389D0000 */  addi    r4, r29, 0
/* 0AFD90 800B5330 3860FFFD */  li      r3, -3
/* 0AFD94 800B5334 4E800021 */  blrl    
lbl_800B5338:
/* 0AFD98 800B5338 281E0000 */  cmplwi  r30, 0
/* 0AFD9C 800B533C 41820018 */  beq     lbl_800B5354
/* 0AFDA0 800B5340 399E0000 */  addi    r12, r30, 0
/* 0AFDA4 800B5344 7D8803A6 */  mtlr    r12
/* 0AFDA8 800B5348 389D0000 */  addi    r4, r29, 0
/* 0AFDAC 800B534C 38600000 */  li      r3, 0
/* 0AFDB0 800B5350 4E800021 */  blrl    
lbl_800B5354:
/* 0AFDB4 800B5354 4BFFEC81 */  bl      stateReady
glabel lbl_800B5358
/* 0AFDB8 800B5358 7FE3FB78 */  mr      r3, r31
/* 0AFDBC 800B535C 4BFE99C9 */  bl      OSRestoreInterrupts
/* 0AFDC0 800B5360 38600001 */  li      r3, 1
lbl_800B5364:
/* 0AFDC4 800B5364 8001002C */  lwz     r0, 0x2c(r1)
/* 0AFDC8 800B5368 83E10024 */  lwz     r31, 0x24(r1)
/* 0AFDCC 800B536C 83C10020 */  lwz     r30, 0x20(r1)
/* 0AFDD0 800B5370 83A1001C */  lwz     r29, 0x1c(r1)
/* 0AFDD4 800B5374 38210028 */  addi    r1, r1, 0x28
/* 0AFDD8 800B5378 7C0803A6 */  mtlr    r0
/* 0AFDDC 800B537C 4E800020 */  blr     

glabel DVDCancel
/* 0AFDE0 800B5380 7C0802A6 */  mflr    r0
/* 0AFDE4 800B5384 3C80800B */  lis     r4, cbForCancelSync@ha
/* 0AFDE8 800B5388 90010004 */  stw     r0, 4(r1)
/* 0AFDEC 800B538C 3884542C */  addi    r4, r4, cbForCancelSync@l
/* 0AFDF0 800B5390 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0AFDF4 800B5394 93E10014 */  stw     r31, 0x14(r1)
/* 0AFDF8 800B5398 93C10010 */  stw     r30, 0x10(r1)
/* 0AFDFC 800B539C 3BC30000 */  addi    r30, r3, 0
/* 0AFE00 800B53A0 4BFFFD65 */  bl      DVDCancelAsync
/* 0AFE04 800B53A4 2C030000 */  cmpwi   r3, 0
/* 0AFE08 800B53A8 4082000C */  bne     lbl_800B53B4
/* 0AFE0C 800B53AC 3860FFFF */  li      r3, -1
/* 0AFE10 800B53B0 48000064 */  b       lbl_800B5414
lbl_800B53B4:
/* 0AFE14 800B53B4 4BFE9949 */  bl      OSDisableInterrupts
/* 0AFE18 800B53B8 7C7F1B78 */  mr      r31, r3
lbl_800B53BC:
/* 0AFE1C 800B53BC 807E000C */  lwz     r3, 0xc(r30)
/* 0AFE20 800B53C0 38030001 */  addi    r0, r3, 1
/* 0AFE24 800B53C4 28000001 */  cmplwi  r0, 1
/* 0AFE28 800B53C8 40810040 */  ble     lbl_800B5408
/* 0AFE2C 800B53CC 2C03000A */  cmpwi   r3, 0xa
/* 0AFE30 800B53D0 41820038 */  beq     lbl_800B5408
/* 0AFE34 800B53D4 2C030003 */  cmpwi   r3, 3
/* 0AFE38 800B53D8 40820024 */  bne     lbl_800B53FC
/* 0AFE3C 800B53DC 807E0008 */  lwz     r3, 8(r30)
/* 0AFE40 800B53E0 3803FFFC */  addi    r0, r3, -4
/* 0AFE44 800B53E4 28000001 */  cmplwi  r0, 1
/* 0AFE48 800B53E8 40810020 */  ble     lbl_800B5408
/* 0AFE4C 800B53EC 2803000D */  cmplwi  r3, 0xd
/* 0AFE50 800B53F0 41820018 */  beq     lbl_800B5408
/* 0AFE54 800B53F4 2803000F */  cmplwi  r3, 0xf
/* 0AFE58 800B53F8 41820010 */  beq     lbl_800B5408
lbl_800B53FC:
/* 0AFE5C 800B53FC 386D8D28 */  addi    r3, r13, __DVDThreadQueue-_SDA_BASE_
/* 0AFE60 800B5400 4BFECC0D */  bl      OSSleepThread
/* 0AFE64 800B5404 4BFFFFB8 */  b       lbl_800B53BC
lbl_800B5408:
/* 0AFE68 800B5408 7FE3FB78 */  mr      r3, r31
/* 0AFE6C 800B540C 4BFE9919 */  bl      OSRestoreInterrupts
/* 0AFE70 800B5410 38600000 */  li      r3, 0
lbl_800B5414:
/* 0AFE74 800B5414 8001001C */  lwz     r0, 0x1c(r1)
/* 0AFE78 800B5418 83E10014 */  lwz     r31, 0x14(r1)
/* 0AFE7C 800B541C 83C10010 */  lwz     r30, 0x10(r1)
/* 0AFE80 800B5420 38210018 */  addi    r1, r1, 0x18
/* 0AFE84 800B5424 7C0803A6 */  mtlr    r0
/* 0AFE88 800B5428 4E800020 */  blr     

cbForCancelSync:
/* 0AFE8C 800B542C 7C0802A6 */  mflr    r0
/* 0AFE90 800B5430 386D8D28 */  addi    r3, r13, __DVDThreadQueue-_SDA_BASE_
/* 0AFE94 800B5434 90010004 */  stw     r0, 4(r1)
/* 0AFE98 800B5438 9421FFF8 */  stwu    r1, -8(r1)
/* 0AFE9C 800B543C 4BFECCBD */  bl      OSWakeupThread
/* 0AFEA0 800B5440 8001000C */  lwz     r0, 0xc(r1)
/* 0AFEA4 800B5444 38210008 */  addi    r1, r1, 8
/* 0AFEA8 800B5448 7C0803A6 */  mtlr    r0
/* 0AFEAC 800B544C 4E800020 */  blr     

glabel DVDGetCurrentDiskID
/* 0AFEB0 800B5450 3C608000 */  lis     r3, 0x8000
/* 0AFEB4 800B5454 4E800020 */  blr     

glabel DVDCheckDisk
/* 0AFEB8 800B5458 7C0802A6 */  mflr    r0
/* 0AFEBC 800B545C 90010004 */  stw     r0, 4(r1)
/* 0AFEC0 800B5460 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0AFEC4 800B5464 93E1000C */  stw     r31, 0xc(r1)
/* 0AFEC8 800B5468 4BFE9895 */  bl      OSDisableInterrupts
/* 0AFECC 800B546C 800D8D48 */  lwz     r0, FatalErrorFlag-_SDA_BASE_(r13)
/* 0AFED0 800B5470 2C000000 */  cmpwi   r0, 0
/* 0AFED4 800B5474 4182000C */  beq     lbl_800B5480
/* 0AFED8 800B5478 3880FFFF */  li      r4, -1
/* 0AFEDC 800B547C 48000048 */  b       lbl_800B54C4
lbl_800B5480:
/* 0AFEE0 800B5480 800D8D40 */  lwz     r0, PausingFlag-_SDA_BASE_(r13)
/* 0AFEE4 800B5484 2C000000 */  cmpwi   r0, 0
/* 0AFEE8 800B5488 4182000C */  beq     lbl_800B5494
/* 0AFEEC 800B548C 38800008 */  li      r4, 8
/* 0AFEF0 800B5490 48000034 */  b       lbl_800B54C4
lbl_800B5494:
/* 0AFEF4 800B5494 80AD8D30 */  lwz     r5, executing-_SDA_BASE_(r13)
/* 0AFEF8 800B5498 28050000 */  cmplwi  r5, 0
/* 0AFEFC 800B549C 4082000C */  bne     lbl_800B54A8
/* 0AFF00 800B54A0 38800000 */  li      r4, 0
/* 0AFF04 800B54A4 48000020 */  b       lbl_800B54C4
lbl_800B54A8:
/* 0AFF08 800B54A8 3C808013 */  lis     r4, DummyCommandBlock@ha
/* 0AFF0C 800B54AC 380425E0 */  addi    r0, r4, DummyCommandBlock@l
/* 0AFF10 800B54B0 7C050040 */  cmplw   r5, r0
/* 0AFF14 800B54B4 4082000C */  bne     lbl_800B54C0
/* 0AFF18 800B54B8 38800000 */  li      r4, 0
/* 0AFF1C 800B54BC 48000008 */  b       lbl_800B54C4
lbl_800B54C0:
/* 0AFF20 800B54C0 8085000C */  lwz     r4, 0xc(r5)
lbl_800B54C4:
/* 0AFF24 800B54C4 38040001 */  addi    r0, r4, 1
/* 0AFF28 800B54C8 2800000C */  cmplwi  r0, 0xc
/* 0AFF2C 800B54CC 41810068 */  bgt     lbl_800B5534
/* 0AFF30 800B54D0 3C80800F */  lis     r4, jtbl_800F25AC@ha
/* 0AFF34 800B54D4 388425AC */  addi    r4, r4, jtbl_800F25AC@l
/* 0AFF38 800B54D8 5400103A */  slwi    r0, r0, 2
/* 0AFF3C 800B54DC 7C04002E */  lwzx    r0, r4, r0
/* 0AFF40 800B54E0 7C0903A6 */  mtctr   r0
/* 0AFF44 800B54E4 4E800420 */  bctr    
glabel lbl_800B54E8
/* 0AFF48 800B54E8 3BE00001 */  li      r31, 1
/* 0AFF4C 800B54EC 48000048 */  b       lbl_800B5534
glabel lbl_800B54F0
/* 0AFF50 800B54F0 3BE00000 */  li      r31, 0
/* 0AFF54 800B54F4 48000040 */  b       lbl_800B5534
glabel lbl_800B54F8
/* 0AFF58 800B54F8 3C80CC00 */  lis     r4, DI_REGS_BASE@ha
/* 0AFF5C 800B54FC 38846000 */  addi    r4, r4, DI_REGS_BASE@l
/* 0AFF60 800B5500 80840004 */  lwz     r4, DI_DICVR(r4)
/* 0AFF64 800B5504 5480F7FF */  rlwinm. r0, r4, 0x1e, 0x1f, 0x1f
/* 0AFF68 800B5508 4082000C */  bne     lbl_800B5514
/* 0AFF6C 800B550C 548007FF */  clrlwi. r0, r4, 0x1f
/* 0AFF70 800B5510 4182000C */  beq     lbl_800B551C
lbl_800B5514:
/* 0AFF74 800B5514 3BE00000 */  li      r31, 0
/* 0AFF78 800B5518 4800001C */  b       lbl_800B5534
lbl_800B551C:
/* 0AFF7C 800B551C 800D8D58 */  lwz     r0, ResumeFromHere-_SDA_BASE_(r13)
/* 0AFF80 800B5520 28000000 */  cmplwi  r0, 0
/* 0AFF84 800B5524 4182000C */  beq     lbl_800B5530
/* 0AFF88 800B5528 3BE00000 */  li      r31, 0
/* 0AFF8C 800B552C 48000008 */  b       lbl_800B5534
lbl_800B5530:
/* 0AFF90 800B5530 3BE00001 */  li      r31, 1
lbl_800B5534:
/* 0AFF94 800B5534 4BFE97F1 */  bl      OSRestoreInterrupts
/* 0AFF98 800B5538 7FE3FB78 */  mr      r3, r31
/* 0AFF9C 800B553C 80010014 */  lwz     r0, 0x14(r1)
/* 0AFFA0 800B5540 83E1000C */  lwz     r31, 0xc(r1)
/* 0AFFA4 800B5544 38210010 */  addi    r1, r1, 0x10
/* 0AFFA8 800B5548 7C0803A6 */  mtlr    r0
/* 0AFFAC 800B554C 4E800020 */  blr     

glabel __DVDPrepareResetAsync
/* 0AFFB0 800B5550 7C0802A6 */  mflr    r0
/* 0AFFB4 800B5554 90010004 */  stw     r0, 4(r1)
/* 0AFFB8 800B5558 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0AFFBC 800B555C 93E1001C */  stw     r31, 0x1c(r1)
/* 0AFFC0 800B5560 93C10018 */  stw     r30, 0x18(r1)
/* 0AFFC4 800B5564 7C7E1B78 */  mr      r30, r3
/* 0AFFC8 800B5568 93A10014 */  stw     r29, 0x14(r1)
/* 0AFFCC 800B556C 4BFE9791 */  bl      OSDisableInterrupts
/* 0AFFD0 800B5570 7C7D1B78 */  mr      r29, r3
/* 0AFFD4 800B5574 48000131 */  bl      __DVDClearWaitingQueue
/* 0AFFD8 800B5578 800D8D50 */  lwz     r0, Canceling-_SDA_BASE_(r13)
/* 0AFFDC 800B557C 28000000 */  cmplwi  r0, 0
/* 0AFFE0 800B5580 4182000C */  beq     lbl_800B558C
/* 0AFFE4 800B5584 93CD8D54 */  stw     r30, CancelCallback-_SDA_BASE_(r13)
/* 0AFFE8 800B5588 480000C0 */  b       lbl_800B5648
lbl_800B558C:
/* 0AFFEC 800B558C 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0AFFF0 800B5590 28030000 */  cmplwi  r3, 0
/* 0AFFF4 800B5594 4182000C */  beq     lbl_800B55A0
/* 0AFFF8 800B5598 38000000 */  li      r0, 0
/* 0AFFFC 800B559C 90030028 */  stw     r0, 0x28(r3)
lbl_800B55A0:
/* 0B0000 800B55A0 4BFE975D */  bl      OSDisableInterrupts
/* 0B0004 800B55A4 7C7F1B78 */  mr      r31, r3
/* 0B0008 800B55A8 4BFE9755 */  bl      OSDisableInterrupts
/* 0B000C 800B55AC 800D8D30 */  lwz     r0, executing-_SDA_BASE_(r13)
/* 0B0010 800B55B0 38800001 */  li      r4, 1
/* 0B0014 800B55B4 908D8D3C */  stw     r4, PauseFlag-_SDA_BASE_(r13)
/* 0B0018 800B55B8 28000000 */  cmplwi  r0, 0
/* 0B001C 800B55BC 40820008 */  bne     lbl_800B55C4
/* 0B0020 800B55C0 908D8D40 */  stw     r4, PausingFlag-_SDA_BASE_(r13)
lbl_800B55C4:
/* 0B0024 800B55C4 4BFE9761 */  bl      OSRestoreInterrupts
/* 0B0028 800B55C8 4800000C */  b       lbl_800B55D4
lbl_800B55CC:
/* 0B002C 800B55CC 38800000 */  li      r4, 0
/* 0B0030 800B55D0 4BFFFB35 */  bl      DVDCancelAsync
lbl_800B55D4:
/* 0B0034 800B55D4 48000171 */  bl      __DVDPopWaitingQueue
/* 0B0038 800B55D8 28030000 */  cmplwi  r3, 0
/* 0B003C 800B55DC 4082FFF0 */  bne     lbl_800B55CC
/* 0B0040 800B55E0 806D8D30 */  lwz     r3, executing-_SDA_BASE_(r13)
/* 0B0044 800B55E4 28030000 */  cmplwi  r3, 0
/* 0B0048 800B55E8 41820010 */  beq     lbl_800B55F8
/* 0B004C 800B55EC 7FC4F378 */  mr      r4, r30
/* 0B0050 800B55F0 4BFFFB15 */  bl      DVDCancelAsync
/* 0B0054 800B55F4 48000020 */  b       lbl_800B5614
lbl_800B55F8:
/* 0B0058 800B55F8 281E0000 */  cmplwi  r30, 0
/* 0B005C 800B55FC 41820018 */  beq     lbl_800B5614
/* 0B0060 800B5600 399E0000 */  addi    r12, r30, 0
/* 0B0064 800B5604 7D8803A6 */  mtlr    r12
/* 0B0068 800B5608 38600000 */  li      r3, 0
/* 0B006C 800B560C 38800000 */  li      r4, 0
/* 0B0070 800B5610 4E800021 */  blrl    
lbl_800B5614:
/* 0B0074 800B5614 4BFE96E9 */  bl      OSDisableInterrupts
/* 0B0078 800B5618 38800000 */  li      r4, 0
/* 0B007C 800B561C 908D8D3C */  stw     r4, PauseFlag-_SDA_BASE_(r13)
/* 0B0080 800B5620 7C7E1B78 */  mr      r30, r3
/* 0B0084 800B5624 800D8D40 */  lwz     r0, PausingFlag-_SDA_BASE_(r13)
/* 0B0088 800B5628 2C000000 */  cmpwi   r0, 0
/* 0B008C 800B562C 4182000C */  beq     lbl_800B5638
/* 0B0090 800B5630 908D8D40 */  stw     r4, PausingFlag-_SDA_BASE_(r13)
/* 0B0094 800B5634 4BFFE9A1 */  bl      stateReady
lbl_800B5638:
/* 0B0098 800B5638 7FC3F378 */  mr      r3, r30
/* 0B009C 800B563C 4BFE96E9 */  bl      OSRestoreInterrupts
/* 0B00A0 800B5640 7FE3FB78 */  mr      r3, r31
/* 0B00A4 800B5644 4BFE96E1 */  bl      OSRestoreInterrupts
lbl_800B5648:
/* 0B00A8 800B5648 7FA3EB78 */  mr      r3, r29
/* 0B00AC 800B564C 4BFE96D9 */  bl      OSRestoreInterrupts
/* 0B00B0 800B5650 80010024 */  lwz     r0, 0x24(r1)
/* 0B00B4 800B5654 83E1001C */  lwz     r31, 0x1c(r1)
/* 0B00B8 800B5658 83C10018 */  lwz     r30, 0x18(r1)
/* 0B00BC 800B565C 83A10014 */  lwz     r29, 0x14(r1)
/* 0B00C0 800B5660 38210020 */  addi    r1, r1, 0x20
/* 0B00C4 800B5664 7C0803A6 */  mtlr    r0
/* 0B00C8 800B5668 4E800020 */  blr     

glabel __DVDTestAlarm
/* 0B00CC 800B566C 7C0802A6 */  mflr    r0
/* 0B00D0 800B5670 3C808013 */  lis     r4, ResetAlarm@ha
/* 0B00D4 800B5674 90010004 */  stw     r0, 4(r1)
/* 0B00D8 800B5678 38042610 */  addi    r0, r4, ResetAlarm@l
/* 0B00DC 800B567C 7C030040 */  cmplw   r3, r0
/* 0B00E0 800B5680 9421FFF8 */  stwu    r1, -8(r1)
/* 0B00E4 800B5684 4082000C */  bne     lbl_800B5690
/* 0B00E8 800B5688 38600001 */  li      r3, 1
/* 0B00EC 800B568C 48000008 */  b       lbl_800B5694
lbl_800B5690:
/* 0B00F0 800B5690 4BFFD041 */  bl      __DVDLowTestAlarm
lbl_800B5694:
/* 0B00F4 800B5694 8001000C */  lwz     r0, 0xc(r1)
/* 0B00F8 800B5698 38210008 */  addi    r1, r1, 8
/* 0B00FC 800B569C 7C0803A6 */  mtlr    r0
/* 0B0100 800B56A0 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000EF4E0 800F2460 0045 */
D_800F2460:
    .asciz "<< Dolphin SDK - DVD\trelease build: Jul 23 2003 11:27:57 (0x2301) >>"
    .balign 4

/* 000EF528 800F24A8 000A */
D_800F24A8:
    .asciz "load fst\n"
    .balign 4

/* 000EF534 800F24B4 0034 */
D_800F24B4:
    .asciz "DVDChangeDisk(): FST in the new disc is too big.   "
    .balign 4

/* 000EF568 800F24E8 0040 */
jtbl_800F24E8:
    .long lbl_800B44FC
    .long lbl_800B4270
    .long lbl_800B4310
    .long lbl_800B4334
    .long lbl_800B4270
    .long lbl_800B4244
    .long lbl_800B4354
    .long lbl_800B43B8
    .long lbl_800B43E4
    .long lbl_800B4418
    .long lbl_800B443C
    .long lbl_800B4460
    .long lbl_800B4484
    .long lbl_800B44A8
    .long lbl_800B44D0
    .long lbl_800B4344

/* 000EF5A8 800F2528 000C */
ImmCommand:
    .long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF

/* 000EF5B4 800F2534 0041 */
D_800F2534:
    .asciz "DVDChangeDiskAsync(): You can't specify NULL to company name.  \n"
    .balign 4

/* 000EF5F8 800F2578 0034 */
jtbl_800F2578:
    .long lbl_800B5154
    .long lbl_800B5154
    .long lbl_800B5174
    .long lbl_800B51B8
    .long lbl_800B5204
    .long lbl_800B5280
    .long lbl_800B5280
    .long lbl_800B5280
    .long lbl_800B5280
    .long lbl_800B5358
    .long lbl_800B5358
    .long lbl_800B5154
    .long lbl_800B5280

/* 000EF62C 800F25AC 0034 */
jtbl_800F25AC:
    .long lbl_800B54F0
    .long lbl_800B54F8
    .long lbl_800B54E8
    .long lbl_800B54E8
    .long lbl_800B54F0
    .long lbl_800B54F0
    .long lbl_800B54F0
    .long lbl_800B54F0
    .long lbl_800B54F0
    .long lbl_800B54F8
    .long lbl_800B54E8
    .long lbl_800B54E8
    .long lbl_800B54F0

.section .bss, "wa"

.balign 32

/* 0012F620 801325A0 0020 */
BB2:
    .skip 32

/* 0012F640 801325C0 0020 */
CurrDiskID:
    .skip 32

/* 0012F660 801325E0 0030 */
DummyCommandBlock:
    .skip 48

/* 0012F690 80132610 0028 */
ResetAlarm:
    .skip 40

.section .sdata, "wa"

.balign 8

/* 000F1778 801354F8 0004 */
glabel __DVDVersion
    .long D_800F2460

/* 000F177C 801354FC 0004 */
autoInvalidation:
    .long 0x00000001

/* 000F1780 80135500 0004 */
checkOptionalCommand:
    .long defaultOptionalCommandChecker

/* 000F1784 80135504 0006 */
D_80135504:
    .asciz "dvd.c"
    .balign 4

/* 000F178C 8013550C 0004 */
DmaCommand:
    .long 0xFFFFFFFF

.section .sbss, "wa"

.balign 8

/* 000F1C90 80135A10 0004 */
executing:
    .skip 4

/* 000F1C94 80135A14 0004 */
IDShouldBe:
    .skip 4

/* 000F1C98 80135A18 0004 */
bootInfo:
    .skip 4

/* 000F1C9C 80135A1C 0004 */
PauseFlag:
    .skip 4

/* 000F1CA0 80135A20 0004 */
PausingFlag:
    .skip 4

/* 000F1CA4 80135A24 0004 */
AutoFinishing:
    .skip 4

/* 000F1CA8 80135A28 0004 */
FatalErrorFlag:
    .skip 4

/* 000F1CAC 80135A2C 0004 */
CurrCommand:
    .skip 4

/* 000F1CB0 80135A30 0004 */
Canceling:
    .skip 4

/* 000F1CB4 80135A34 0004 */
CancelCallback:
    .skip 4

/* 000F1CB8 80135A38 0004 */
ResumeFromHere:
    .skip 4

/* 000F1CBC 80135A3C 0004 */
CancelLastError:
    .skip 4

/* 000F1CC0 80135A40 0004 */
LastError:
    .skip 4

/* 000F1CC4 80135A44 0004 */
NumInternalRetry:
    .skip 4

/* 000F1CC8 80135A48 0004 */
ResetRequired:
    .skip 4

/* 000F1CCC 80135A4C 0004 */
FirstTimeInBootrom:
    .skip 4

/* 000F1CD0 80135A50 0004 */
DVDInitialized:
    .skip 4

/* 000F1CD4 80135A54 0004 */
glabel LastState
    .skip 4
