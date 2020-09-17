# notify.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKDoNotifyStopped
/* 0C61CC 800CB76C 7C0802A6 */  mflr    r0
/* 0C61D0 800CB770 90010004 */  stw     r0, 4(r1)
/* 0C61D4 800CB774 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0C61D8 800CB778 93E1001C */  stw     r31, 0x1c(r1)
/* 0C61DC 800CB77C 3881000C */  addi    r4, r1, 0xc
/* 0C61E0 800CB780 93C10018 */  stw     r30, 0x18(r1)
/* 0C61E4 800CB784 3BC30000 */  addi    r30, r3, 0
/* 0C61E8 800CB788 38610008 */  addi    r3, r1, 8
/* 0C61EC 800CB78C 4BFFDEB5 */  bl      TRKGetFreeBuffer
/* 0C61F0 800CB790 7C7F1B79 */  or.     r31, r3, r3
/* 0C61F4 800CB794 40820094 */  bne     lbl_800CB828
/* 0C61F8 800CB798 80A1000C */  lwz     r5, 0xc(r1)
/* 0C61FC 800CB79C 8065000C */  lwz     r3, 0xc(r5)
/* 0C6200 800CB7A0 28030880 */  cmplwi  r3, 0x880
/* 0C6204 800CB7A4 4180000C */  blt     lbl_800CB7B0
/* 0C6208 800CB7A8 38800301 */  li      r4, 0x301
/* 0C620C 800CB7AC 48000024 */  b       lbl_800CB7D0
lbl_800CB7B0:
/* 0C6210 800CB7B0 38030001 */  addi    r0, r3, 1
/* 0C6214 800CB7B4 7C651A14 */  add     r3, r5, r3
/* 0C6218 800CB7B8 9005000C */  stw     r0, 0xc(r5)
/* 0C621C 800CB7BC 38800000 */  li      r4, 0
/* 0C6220 800CB7C0 9BC30010 */  stb     r30, 0x10(r3)
/* 0C6224 800CB7C4 80650008 */  lwz     r3, 8(r5)
/* 0C6228 800CB7C8 38030001 */  addi    r0, r3, 1
/* 0C622C 800CB7CC 90050008 */  stw     r0, 8(r5)
lbl_800CB7D0:
/* 0C6230 800CB7D0 2C040000 */  cmpwi   r4, 0
/* 0C6234 800CB7D4 40820024 */  bne     lbl_800CB7F8
/* 0C6238 800CB7D8 57C0063E */  clrlwi  r0, r30, 0x18
/* 0C623C 800CB7DC 28000090 */  cmplwi  r0, 0x90
/* 0C6240 800CB7E0 40820010 */  bne     lbl_800CB7F0
/* 0C6244 800CB7E4 8061000C */  lwz     r3, 0xc(r1)
/* 0C6248 800CB7E8 48000E91 */  bl      TRKTargetAddStopInfo
/* 0C624C 800CB7EC 4800000C */  b       lbl_800CB7F8
lbl_800CB7F0:
/* 0C6250 800CB7F0 8061000C */  lwz     r3, 0xc(r1)
/* 0C6254 800CB7F4 48000F15 */  bl      TRKTargetAddExceptionInfo
lbl_800CB7F8:
/* 0C6258 800CB7F8 8061000C */  lwz     r3, 0xc(r1)
/* 0C625C 800CB7FC 38810010 */  addi    r4, r1, 0x10
/* 0C6260 800CB800 38A00002 */  li      r5, 2
/* 0C6264 800CB804 38C00003 */  li      r6, 3
/* 0C6268 800CB808 38E00001 */  li      r7, 1
/* 0C626C 800CB80C 4BFFFDA5 */  bl      TRKRequestSend
/* 0C6270 800CB810 7C7F1B79 */  or.     r31, r3, r3
/* 0C6274 800CB814 4082000C */  bne     lbl_800CB820
/* 0C6278 800CB818 80610010 */  lwz     r3, 0x10(r1)
/* 0C627C 800CB81C 4BFFDEED */  bl      TRKReleaseBuffer
lbl_800CB820:
/* 0C6280 800CB820 80610008 */  lwz     r3, 8(r1)
/* 0C6284 800CB824 4BFFDEE5 */  bl      TRKReleaseBuffer
lbl_800CB828:
/* 0C6288 800CB828 7FE3FB78 */  mr      r3, r31
/* 0C628C 800CB82C 83E1001C */  lwz     r31, 0x1c(r1)
/* 0C6290 800CB830 83C10018 */  lwz     r30, 0x18(r1)
/* 0C6294 800CB834 38210020 */  addi    r1, r1, 0x20
/* 0C6298 800CB838 80010004 */  lwz     r0, 4(r1)
/* 0C629C 800CB83C 7C0803A6 */  mtlr    r0
/* 0C62A0 800CB840 4E800020 */  blr     


