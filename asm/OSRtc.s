# OSRtc.c
.include "macros.inc"

.section .text, "ax"

.balign 4

WriteSramCallback:
/* 09B038 800A05D8 7C0802A6 */  mflr    r0
/* 09B03C 800A05DC 3C608013 */  lis     r3, Scb@ha
/* 09B040 800A05E0 90010004 */  stw     r0, 4(r1)
/* 09B044 800A05E4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 09B048 800A05E8 93E10014 */  stw     r31, 0x14(r1)
/* 09B04C 800A05EC 3BE30FE0 */  addi    r31, r3, Scb@l
/* 09B050 800A05F0 93C10010 */  stw     r30, 0x10(r1)
/* 09B054 800A05F4 3BDF0040 */  addi    r30, r31, 0x40
/* 09B058 800A05F8 809F0040 */  lwz     r4, 0x40(r31)
/* 09B05C 800A05FC 7C7F2214 */  add     r3, r31, r4
/* 09B060 800A0600 20A40040 */  subfic  r5, r4, 0x40
/* 09B064 800A0604 48000035 */  bl      WriteSram
/* 09B068 800A0608 907F004C */  stw     r3, 0x4c(r31)
/* 09B06C 800A060C 801F004C */  lwz     r0, 0x4c(r31)
/* 09B070 800A0610 2C000000 */  cmpwi   r0, 0
/* 09B074 800A0614 4182000C */  beq     lbl_800A0620
/* 09B078 800A0618 38000040 */  li      r0, 0x40
/* 09B07C 800A061C 901E0000 */  stw     r0, 0(r30)
lbl_800A0620:
/* 09B080 800A0620 8001001C */  lwz     r0, 0x1c(r1)
/* 09B084 800A0624 83E10014 */  lwz     r31, 0x14(r1)
/* 09B088 800A0628 83C10010 */  lwz     r30, 0x10(r1)
/* 09B08C 800A062C 38210018 */  addi    r1, r1, 0x18
/* 09B090 800A0630 7C0803A6 */  mtlr    r0
/* 09B094 800A0634 4E800020 */  blr     

WriteSram:
/* 09B098 800A0638 7C0802A6 */  mflr    r0
/* 09B09C 800A063C 3CC0800A */  lis     r6, WriteSramCallback@ha
/* 09B0A0 800A0640 90010004 */  stw     r0, 4(r1)
/* 09B0A4 800A0644 380605D8 */  addi    r0, r6, WriteSramCallback@l
/* 09B0A8 800A0648 9421FFD8 */  stwu    r1, -0x28(r1)
/* 09B0AC 800A064C 93E10024 */  stw     r31, 0x24(r1)
/* 09B0B0 800A0650 3BE40000 */  addi    r31, r4, 0
/* 09B0B4 800A0654 38800001 */  li      r4, 1
/* 09B0B8 800A0658 93C10020 */  stw     r30, 0x20(r1)
/* 09B0BC 800A065C 3BC50000 */  addi    r30, r5, 0
/* 09B0C0 800A0660 7C050378 */  mr      r5, r0
/* 09B0C4 800A0664 93A1001C */  stw     r29, 0x1c(r1)
/* 09B0C8 800A0668 3BA30000 */  addi    r29, r3, 0
/* 09B0CC 800A066C 38600000 */  li      r3, 0
/* 09B0D0 800A0670 48003511 */  bl      EXILock
/* 09B0D4 800A0674 2C030000 */  cmpwi   r3, 0
/* 09B0D8 800A0678 4082000C */  bne     lbl_800A0684
/* 09B0DC 800A067C 38600000 */  li      r3, 0
/* 09B0E0 800A0680 480000B4 */  b       lbl_800A0734
lbl_800A0684:
/* 09B0E4 800A0684 38600000 */  li      r3, 0
/* 09B0E8 800A0688 38800001 */  li      r4, 1
/* 09B0EC 800A068C 38A00003 */  li      r5, 3
/* 09B0F0 800A0690 48002D31 */  bl      EXISelect
/* 09B0F4 800A0694 2C030000 */  cmpwi   r3, 0
/* 09B0F8 800A0698 40820014 */  bne     lbl_800A06AC
/* 09B0FC 800A069C 38600000 */  li      r3, 0
/* 09B100 800A06A0 480035D5 */  bl      EXIUnlock
/* 09B104 800A06A4 38600000 */  li      r3, 0
/* 09B108 800A06A8 4800008C */  b       lbl_800A0734
lbl_800A06AC:
/* 09B10C 800A06AC 57FF3032 */  slwi    r31, r31, 6
/* 09B110 800A06B0 381F0100 */  addi    r0, r31, 0x100
/* 09B114 800A06B4 6400A000 */  oris    r0, r0, 0xa000
/* 09B118 800A06B8 90010014 */  stw     r0, 0x14(r1)
/* 09B11C 800A06BC 38810014 */  addi    r4, r1, 0x14
/* 09B120 800A06C0 38600000 */  li      r3, 0
/* 09B124 800A06C4 38A00004 */  li      r5, 4
/* 09B128 800A06C8 38C00001 */  li      r6, 1
/* 09B12C 800A06CC 38E00000 */  li      r7, 0
/* 09B130 800A06D0 48002189 */  bl      EXIImm
/* 09B134 800A06D4 7C600034 */  cntlzw  r0, r3
/* 09B138 800A06D8 541FD97E */  srwi    r31, r0, 5
/* 09B13C 800A06DC 38600000 */  li      r3, 0
/* 09B140 800A06E0 48002561 */  bl      EXISync
/* 09B144 800A06E4 7C600034 */  cntlzw  r0, r3
/* 09B148 800A06E8 5400D97E */  srwi    r0, r0, 5
/* 09B14C 800A06EC 389D0000 */  addi    r4, r29, 0
/* 09B150 800A06F0 38BE0000 */  addi    r5, r30, 0
/* 09B154 800A06F4 7FFF0378 */  or      r31, r31, r0
/* 09B158 800A06F8 38600000 */  li      r3, 0
/* 09B15C 800A06FC 38C00001 */  li      r6, 1
/* 09B160 800A0700 480023B5 */  bl      EXIImmEx
/* 09B164 800A0704 7C600034 */  cntlzw  r0, r3
/* 09B168 800A0708 5400D97E */  srwi    r0, r0, 5
/* 09B16C 800A070C 7FFF0378 */  or      r31, r31, r0
/* 09B170 800A0710 38600000 */  li      r3, 0
/* 09B174 800A0714 48002DD9 */  bl      EXIDeselect
/* 09B178 800A0718 7C600034 */  cntlzw  r0, r3
/* 09B17C 800A071C 5400D97E */  srwi    r0, r0, 5
/* 09B180 800A0720 7FFF0378 */  or      r31, r31, r0
/* 09B184 800A0724 38600000 */  li      r3, 0
/* 09B188 800A0728 4800354D */  bl      EXIUnlock
/* 09B18C 800A072C 7FE00034 */  cntlzw  r0, r31
/* 09B190 800A0730 5403D97E */  srwi    r3, r0, 5
lbl_800A0734:
/* 09B194 800A0734 8001002C */  lwz     r0, 0x2c(r1)
/* 09B198 800A0738 83E10024 */  lwz     r31, 0x24(r1)
/* 09B19C 800A073C 83C10020 */  lwz     r30, 0x20(r1)
/* 09B1A0 800A0740 83A1001C */  lwz     r29, 0x1c(r1)
/* 09B1A4 800A0744 38210028 */  addi    r1, r1, 0x28
/* 09B1A8 800A0748 7C0803A6 */  mtlr    r0
/* 09B1AC 800A074C 4E800020 */  blr     

glabel __OSInitSram
/* 09B1B0 800A0750 7C0802A6 */  mflr    r0
/* 09B1B4 800A0754 3C608013 */  lis     r3, Scb@ha
/* 09B1B8 800A0758 90010004 */  stw     r0, 4(r1)
/* 09B1BC 800A075C 38800040 */  li      r4, 0x40
/* 09B1C0 800A0760 9421FFE8 */  stwu    r1, -0x18(r1)
/* 09B1C4 800A0764 93E10014 */  stw     r31, 0x14(r1)
/* 09B1C8 800A0768 3BE00000 */  li      r31, 0
/* 09B1CC 800A076C 93C10010 */  stw     r30, 0x10(r1)
/* 09B1D0 800A0770 3BC30FE0 */  addi    r30, r3, Scb@l
/* 09B1D4 800A0774 387E0000 */  addi    r3, r30, 0
/* 09B1D8 800A0778 93FE0044 */  stw     r31, 0x44(r30)
/* 09B1DC 800A077C 93FE0048 */  stw     r31, 0x48(r30)
/* 09B1E0 800A0780 4BFFCFD1 */  bl      DCInvalidateRange
/* 09B1E4 800A0784 38600000 */  li      r3, 0
/* 09B1E8 800A0788 38800001 */  li      r4, 1
/* 09B1EC 800A078C 38A00000 */  li      r5, 0
/* 09B1F0 800A0790 480033F1 */  bl      EXILock
/* 09B1F4 800A0794 2C030000 */  cmpwi   r3, 0
/* 09B1F8 800A0798 40820008 */  bne     lbl_800A07A0
/* 09B1FC 800A079C 480000C4 */  b       lbl_800A0860
lbl_800A07A0:
/* 09B200 800A07A0 38600000 */  li      r3, 0
/* 09B204 800A07A4 38800001 */  li      r4, 1
/* 09B208 800A07A8 38A00003 */  li      r5, 3
/* 09B20C 800A07AC 48002C15 */  bl      EXISelect
/* 09B210 800A07B0 2C030000 */  cmpwi   r3, 0
/* 09B214 800A07B4 40820010 */  bne     lbl_800A07C4
/* 09B218 800A07B8 38600000 */  li      r3, 0
/* 09B21C 800A07BC 480034B9 */  bl      EXIUnlock
/* 09B220 800A07C0 480000A0 */  b       lbl_800A0860
lbl_800A07C4:
/* 09B224 800A07C4 3C602000 */  lis     r3, 0x2000
/* 09B228 800A07C8 38030100 */  addi    r0, r3, 0x100
/* 09B22C 800A07CC 90010008 */  stw     r0, 8(r1)
/* 09B230 800A07D0 38810008 */  addi    r4, r1, 8
/* 09B234 800A07D4 38600000 */  li      r3, 0
/* 09B238 800A07D8 38A00004 */  li      r5, 4
/* 09B23C 800A07DC 38C00001 */  li      r6, 1
/* 09B240 800A07E0 38E00000 */  li      r7, 0
/* 09B244 800A07E4 48002075 */  bl      EXIImm
/* 09B248 800A07E8 7C600034 */  cntlzw  r0, r3
/* 09B24C 800A07EC 541FD97E */  srwi    r31, r0, 5
/* 09B250 800A07F0 38600000 */  li      r3, 0
/* 09B254 800A07F4 4800244D */  bl      EXISync
/* 09B258 800A07F8 7C600034 */  cntlzw  r0, r3
/* 09B25C 800A07FC 5400D97E */  srwi    r0, r0, 5
/* 09B260 800A0800 389E0000 */  addi    r4, r30, 0
/* 09B264 800A0804 7FFF0378 */  or      r31, r31, r0
/* 09B268 800A0808 38600000 */  li      r3, 0
/* 09B26C 800A080C 38A00040 */  li      r5, 0x40
/* 09B270 800A0810 38C00000 */  li      r6, 0
/* 09B274 800A0814 38E00000 */  li      r7, 0
/* 09B278 800A0818 4800233D */  bl      EXIDma
/* 09B27C 800A081C 7C600034 */  cntlzw  r0, r3
/* 09B280 800A0820 5400D97E */  srwi    r0, r0, 5
/* 09B284 800A0824 7FFF0378 */  or      r31, r31, r0
/* 09B288 800A0828 38600000 */  li      r3, 0
/* 09B28C 800A082C 48002415 */  bl      EXISync
/* 09B290 800A0830 7C600034 */  cntlzw  r0, r3
/* 09B294 800A0834 5400D97E */  srwi    r0, r0, 5
/* 09B298 800A0838 7FFF0378 */  or      r31, r31, r0
/* 09B29C 800A083C 38600000 */  li      r3, 0
/* 09B2A0 800A0840 48002CAD */  bl      EXIDeselect
/* 09B2A4 800A0844 7C600034 */  cntlzw  r0, r3
/* 09B2A8 800A0848 5400D97E */  srwi    r0, r0, 5
/* 09B2AC 800A084C 7FFF0378 */  or      r31, r31, r0
/* 09B2B0 800A0850 38600000 */  li      r3, 0
/* 09B2B4 800A0854 48003421 */  bl      EXIUnlock
/* 09B2B8 800A0858 7FE00034 */  cntlzw  r0, r31
/* 09B2BC 800A085C 541FD97E */  srwi    r31, r0, 5
lbl_800A0860:
/* 09B2C0 800A0860 93FE004C */  stw     r31, 0x4c(r30)
/* 09B2C4 800A0864 38000040 */  li      r0, 0x40
/* 09B2C8 800A0868 901E0040 */  stw     r0, 0x40(r30)
/* 09B2CC 800A086C 480006C1 */  bl      OSGetGbsMode
/* 09B2D0 800A0870 4800072D */  bl      OSSetGbsMode
/* 09B2D4 800A0874 8001001C */  lwz     r0, 0x1c(r1)
/* 09B2D8 800A0878 83E10014 */  lwz     r31, 0x14(r1)
/* 09B2DC 800A087C 83C10010 */  lwz     r30, 0x10(r1)
/* 09B2E0 800A0880 38210018 */  addi    r1, r1, 0x18
/* 09B2E4 800A0884 7C0803A6 */  mtlr    r0
/* 09B2E8 800A0888 4E800020 */  blr     

glabel __OSLockSram
/* 09B2EC 800A088C 7C0802A6 */  mflr    r0
/* 09B2F0 800A0890 3C608013 */  lis     r3, Scb@ha
/* 09B2F4 800A0894 90010004 */  stw     r0, 4(r1)
/* 09B2F8 800A0898 9421FFF0 */  stwu    r1, -0x10(r1)
/* 09B2FC 800A089C 93E1000C */  stw     r31, 0xc(r1)
/* 09B300 800A08A0 3BE30FE0 */  addi    r31, r3, Scb@l
/* 09B304 800A08A4 4BFFE459 */  bl      OSDisableInterrupts
/* 09B308 800A08A8 801F0048 */  lwz     r0, 0x48(r31)
/* 09B30C 800A08AC 389F0048 */  addi    r4, r31, 0x48
/* 09B310 800A08B0 2C000000 */  cmpwi   r0, 0
/* 09B314 800A08B4 41820010 */  beq     lbl_800A08C4
/* 09B318 800A08B8 4BFFE46D */  bl      OSRestoreInterrupts
/* 09B31C 800A08BC 3BE00000 */  li      r31, 0
/* 09B320 800A08C0 48000010 */  b       lbl_800A08D0
lbl_800A08C4:
/* 09B324 800A08C4 907F0044 */  stw     r3, 0x44(r31)
/* 09B328 800A08C8 38000001 */  li      r0, 1
/* 09B32C 800A08CC 90040000 */  stw     r0, 0(r4)
lbl_800A08D0:
/* 09B330 800A08D0 7FE3FB78 */  mr      r3, r31
/* 09B334 800A08D4 80010014 */  lwz     r0, 0x14(r1)
/* 09B338 800A08D8 83E1000C */  lwz     r31, 0xc(r1)
/* 09B33C 800A08DC 38210010 */  addi    r1, r1, 0x10
/* 09B340 800A08E0 7C0803A6 */  mtlr    r0
/* 09B344 800A08E4 4E800020 */  blr     

glabel __OSLockSramEx
/* 09B348 800A08E8 7C0802A6 */  mflr    r0
/* 09B34C 800A08EC 3C608013 */  lis     r3, Scb@ha
/* 09B350 800A08F0 90010004 */  stw     r0, 4(r1)
/* 09B354 800A08F4 9421FFF0 */  stwu    r1, -0x10(r1)
/* 09B358 800A08F8 93E1000C */  stw     r31, 0xc(r1)
/* 09B35C 800A08FC 3BE30FE0 */  addi    r31, r3, Scb@l
/* 09B360 800A0900 4BFFE3FD */  bl      OSDisableInterrupts
/* 09B364 800A0904 801F0048 */  lwz     r0, 0x48(r31)
/* 09B368 800A0908 389F0048 */  addi    r4, r31, 0x48
/* 09B36C 800A090C 2C000000 */  cmpwi   r0, 0
/* 09B370 800A0910 41820010 */  beq     lbl_800A0920
/* 09B374 800A0914 4BFFE411 */  bl      OSRestoreInterrupts
/* 09B378 800A0918 38600000 */  li      r3, 0
/* 09B37C 800A091C 48000014 */  b       lbl_800A0930
lbl_800A0920:
/* 09B380 800A0920 907F0044 */  stw     r3, 0x44(r31)
/* 09B384 800A0924 38000001 */  li      r0, 1
/* 09B388 800A0928 387F0014 */  addi    r3, r31, 0x14
/* 09B38C 800A092C 90040000 */  stw     r0, 0(r4)
lbl_800A0930:
/* 09B390 800A0930 80010014 */  lwz     r0, 0x14(r1)
/* 09B394 800A0934 83E1000C */  lwz     r31, 0xc(r1)
/* 09B398 800A0938 38210010 */  addi    r1, r1, 0x10
/* 09B39C 800A093C 7C0803A6 */  mtlr    r0
/* 09B3A0 800A0940 4E800020 */  blr     

UnlockSram:
/* 09B3A4 800A0944 7C0802A6 */  mflr    r0
/* 09B3A8 800A0948 2C030000 */  cmpwi   r3, 0
/* 09B3AC 800A094C 90010004 */  stw     r0, 4(r1)
/* 09B3B0 800A0950 3C608013 */  lis     r3, Scb@ha
/* 09B3B4 800A0954 9421FFD0 */  stwu    r1, -0x30(r1)
/* 09B3B8 800A0958 BF61001C */  stmw    r27, 0x1c(r1)
/* 09B3BC 800A095C 3BE30FE0 */  addi    r31, r3, Scb@l
/* 09B3C0 800A0960 418202F8 */  beq     lbl_800A0C58
/* 09B3C4 800A0964 28040000 */  cmplwi  r4, 0
/* 09B3C8 800A0968 408201B0 */  bne     lbl_800A0B18
/* 09B3CC 800A096C 887F0013 */  lbz     r3, 0x13(r31)
/* 09B3D0 800A0970 546007BE */  clrlwi  r0, r3, 0x1e
/* 09B3D4 800A0974 28000002 */  cmplwi  r0, 2
/* 09B3D8 800A0978 4081000C */  ble     lbl_800A0984
/* 09B3DC 800A097C 5460003A */  rlwinm  r0, r3, 0, 0, 0x1d
/* 09B3E0 800A0980 981F0013 */  stb     r0, 0x13(r31)
lbl_800A0984:
/* 09B3E4 800A0984 38000000 */  li      r0, 0
/* 09B3E8 800A0988 B01F0002 */  sth     r0, 2(r31)
/* 09B3EC 800A098C 38BF0014 */  addi    r5, r31, 0x14
/* 09B3F0 800A0990 38DF000C */  addi    r6, r31, 0xc
/* 09B3F4 800A0994 38650001 */  addi    r3, r5, 1
/* 09B3F8 800A0998 B01F0000 */  sth     r0, 0(r31)
/* 09B3FC 800A099C 7C661850 */  subf    r3, r6, r3
/* 09B400 800A09A0 7C062840 */  cmplw   r6, r5
/* 09B404 800A09A4 5463F87E */  srwi    r3, r3, 1
/* 09B408 800A09A8 40800170 */  bge     lbl_800A0B18
/* 09B40C 800A09AC 5460E8FF */  rlwinm. r0, r3, 0x1d, 3, 0x1f
/* 09B410 800A09B0 7C0903A6 */  mtctr   r0
/* 09B414 800A09B4 41820134 */  beq     lbl_800A0AE8
lbl_800A09B8:
/* 09B418 800A09B8 A0BF0000 */  lhz     r5, 0(r31)
/* 09B41C 800A09BC A0060000 */  lhz     r0, 0(r6)
/* 09B420 800A09C0 7C050214 */  add     r0, r5, r0
/* 09B424 800A09C4 B01F0000 */  sth     r0, 0(r31)
/* 09B428 800A09C8 A0060000 */  lhz     r0, 0(r6)
/* 09B42C 800A09CC A0BF0002 */  lhz     r5, 2(r31)
/* 09B430 800A09D0 7C0000F8 */  nor     r0, r0, r0
/* 09B434 800A09D4 7C050214 */  add     r0, r5, r0
/* 09B438 800A09D8 B01F0002 */  sth     r0, 2(r31)
/* 09B43C 800A09DC A0BF0000 */  lhz     r5, 0(r31)
/* 09B440 800A09E0 A0060002 */  lhz     r0, 2(r6)
/* 09B444 800A09E4 7C050214 */  add     r0, r5, r0
/* 09B448 800A09E8 B01F0000 */  sth     r0, 0(r31)
/* 09B44C 800A09EC A0060002 */  lhz     r0, 2(r6)
/* 09B450 800A09F0 A0BF0002 */  lhz     r5, 2(r31)
/* 09B454 800A09F4 7C0000F8 */  nor     r0, r0, r0
/* 09B458 800A09F8 7C050214 */  add     r0, r5, r0
/* 09B45C 800A09FC B01F0002 */  sth     r0, 2(r31)
/* 09B460 800A0A00 A0BF0000 */  lhz     r5, 0(r31)
/* 09B464 800A0A04 A0060004 */  lhz     r0, 4(r6)
/* 09B468 800A0A08 7C050214 */  add     r0, r5, r0
/* 09B46C 800A0A0C B01F0000 */  sth     r0, 0(r31)
/* 09B470 800A0A10 A0060004 */  lhz     r0, 4(r6)
/* 09B474 800A0A14 A0BF0002 */  lhz     r5, 2(r31)
/* 09B478 800A0A18 7C0000F8 */  nor     r0, r0, r0
/* 09B47C 800A0A1C 7C050214 */  add     r0, r5, r0
/* 09B480 800A0A20 B01F0002 */  sth     r0, 2(r31)
/* 09B484 800A0A24 A0BF0000 */  lhz     r5, 0(r31)
/* 09B488 800A0A28 A0060006 */  lhz     r0, 6(r6)
/* 09B48C 800A0A2C 7C050214 */  add     r0, r5, r0
/* 09B490 800A0A30 B01F0000 */  sth     r0, 0(r31)
/* 09B494 800A0A34 A0060006 */  lhz     r0, 6(r6)
/* 09B498 800A0A38 A0BF0002 */  lhz     r5, 2(r31)
/* 09B49C 800A0A3C 7C0000F8 */  nor     r0, r0, r0
/* 09B4A0 800A0A40 7C050214 */  add     r0, r5, r0
/* 09B4A4 800A0A44 B01F0002 */  sth     r0, 2(r31)
/* 09B4A8 800A0A48 A0BF0000 */  lhz     r5, 0(r31)
/* 09B4AC 800A0A4C A0060008 */  lhz     r0, 8(r6)
/* 09B4B0 800A0A50 7C050214 */  add     r0, r5, r0
/* 09B4B4 800A0A54 B01F0000 */  sth     r0, 0(r31)
/* 09B4B8 800A0A58 A0060008 */  lhz     r0, 8(r6)
/* 09B4BC 800A0A5C A0BF0002 */  lhz     r5, 2(r31)
/* 09B4C0 800A0A60 7C0000F8 */  nor     r0, r0, r0
/* 09B4C4 800A0A64 7C050214 */  add     r0, r5, r0
/* 09B4C8 800A0A68 B01F0002 */  sth     r0, 2(r31)
/* 09B4CC 800A0A6C A0BF0000 */  lhz     r5, 0(r31)
/* 09B4D0 800A0A70 A006000A */  lhz     r0, 0xa(r6)
/* 09B4D4 800A0A74 7C050214 */  add     r0, r5, r0
/* 09B4D8 800A0A78 B01F0000 */  sth     r0, 0(r31)
/* 09B4DC 800A0A7C A006000A */  lhz     r0, 0xa(r6)
/* 09B4E0 800A0A80 A0BF0002 */  lhz     r5, 2(r31)
/* 09B4E4 800A0A84 7C0000F8 */  nor     r0, r0, r0
/* 09B4E8 800A0A88 7C050214 */  add     r0, r5, r0
/* 09B4EC 800A0A8C B01F0002 */  sth     r0, 2(r31)
/* 09B4F0 800A0A90 A0BF0000 */  lhz     r5, 0(r31)
/* 09B4F4 800A0A94 A006000C */  lhz     r0, 0xc(r6)
/* 09B4F8 800A0A98 7C050214 */  add     r0, r5, r0
/* 09B4FC 800A0A9C B01F0000 */  sth     r0, 0(r31)
/* 09B500 800A0AA0 A006000C */  lhz     r0, 0xc(r6)
/* 09B504 800A0AA4 A0BF0002 */  lhz     r5, 2(r31)
/* 09B508 800A0AA8 7C0000F8 */  nor     r0, r0, r0
/* 09B50C 800A0AAC 7C050214 */  add     r0, r5, r0
/* 09B510 800A0AB0 B01F0002 */  sth     r0, 2(r31)
/* 09B514 800A0AB4 A0BF0000 */  lhz     r5, 0(r31)
/* 09B518 800A0AB8 A006000E */  lhz     r0, 0xe(r6)
/* 09B51C 800A0ABC 7C050214 */  add     r0, r5, r0
/* 09B520 800A0AC0 B01F0000 */  sth     r0, 0(r31)
/* 09B524 800A0AC4 A006000E */  lhz     r0, 0xe(r6)
/* 09B528 800A0AC8 38C60010 */  addi    r6, r6, 0x10
/* 09B52C 800A0ACC A0BF0002 */  lhz     r5, 2(r31)
/* 09B530 800A0AD0 7C0000F8 */  nor     r0, r0, r0
/* 09B534 800A0AD4 7C050214 */  add     r0, r5, r0
/* 09B538 800A0AD8 B01F0002 */  sth     r0, 2(r31)
/* 09B53C 800A0ADC 4200FEDC */  bdnz    lbl_800A09B8
/* 09B540 800A0AE0 70630007 */  andi.   r3, r3, 7
/* 09B544 800A0AE4 41820034 */  beq     lbl_800A0B18
lbl_800A0AE8:
/* 09B548 800A0AE8 7C6903A6 */  mtctr   r3
lbl_800A0AEC:
/* 09B54C 800A0AEC A0BF0000 */  lhz     r5, 0(r31)
/* 09B550 800A0AF0 A0060000 */  lhz     r0, 0(r6)
/* 09B554 800A0AF4 7C050214 */  add     r0, r5, r0
/* 09B558 800A0AF8 B01F0000 */  sth     r0, 0(r31)
/* 09B55C 800A0AFC A0060000 */  lhz     r0, 0(r6)
/* 09B560 800A0B00 38C60002 */  addi    r6, r6, 2
/* 09B564 800A0B04 A0BF0002 */  lhz     r5, 2(r31)
/* 09B568 800A0B08 7C0000F8 */  nor     r0, r0, r0
/* 09B56C 800A0B0C 7C050214 */  add     r0, r5, r0
/* 09B570 800A0B10 B01F0002 */  sth     r0, 2(r31)
/* 09B574 800A0B14 4200FFD8 */  bdnz    lbl_800A0AEC
lbl_800A0B18:
/* 09B578 800A0B18 3BDF0040 */  addi    r30, r31, 0x40
/* 09B57C 800A0B1C 801F0040 */  lwz     r0, 0x40(r31)
/* 09B580 800A0B20 7C040040 */  cmplw   r4, r0
/* 09B584 800A0B24 40800008 */  bge     lbl_800A0B2C
/* 09B588 800A0B28 909E0000 */  stw     r4, 0(r30)
lbl_800A0B2C:
/* 09B58C 800A0B2C 801E0000 */  lwz     r0, 0(r30)
/* 09B590 800A0B30 28000014 */  cmplwi  r0, 0x14
/* 09B594 800A0B34 4181002C */  bgt     lbl_800A0B60
/* 09B598 800A0B38 389F0014 */  addi    r4, r31, 0x14
/* 09B59C 800A0B3C A07F003C */  lhz     r3, 0x3c(r31)
/* 09B5A0 800A0B40 5460046A */  rlwinm  r0, r3, 0, 0x11, 0x15
/* 09B5A4 800A0B44 28005000 */  cmplwi  r0, 0x5000
/* 09B5A8 800A0B48 41820010 */  beq     lbl_800A0B58
/* 09B5AC 800A0B4C 54600632 */  rlwinm  r0, r3, 0, 0x18, 0x19
/* 09B5B0 800A0B50 280000C0 */  cmplwi  r0, 0xc0
/* 09B5B4 800A0B54 4082000C */  bne     lbl_800A0B60
lbl_800A0B58:
/* 09B5B8 800A0B58 38000000 */  li      r0, 0
/* 09B5BC 800A0B5C B0040028 */  sth     r0, 0x28(r4)
lbl_800A0B60:
/* 09B5C0 800A0B60 83BE0000 */  lwz     r29, 0(r30)
/* 09B5C4 800A0B64 3C60800A */  lis     r3, WriteSramCallback@ha
/* 09B5C8 800A0B68 38A305D8 */  addi    r5, r3, WriteSramCallback@l
/* 09B5CC 800A0B6C 237D0040 */  subfic  r27, r29, 0x40
/* 09B5D0 800A0B70 7F9FEA14 */  add     r28, r31, r29
/* 09B5D4 800A0B74 38600000 */  li      r3, 0
/* 09B5D8 800A0B78 38800001 */  li      r4, 1
/* 09B5DC 800A0B7C 48003005 */  bl      EXILock
/* 09B5E0 800A0B80 2C030000 */  cmpwi   r3, 0
/* 09B5E4 800A0B84 4082000C */  bne     lbl_800A0B90
/* 09B5E8 800A0B88 38000000 */  li      r0, 0
/* 09B5EC 800A0B8C 480000B4 */  b       lbl_800A0C40
lbl_800A0B90:
/* 09B5F0 800A0B90 38600000 */  li      r3, 0
/* 09B5F4 800A0B94 38800001 */  li      r4, 1
/* 09B5F8 800A0B98 38A00003 */  li      r5, 3
/* 09B5FC 800A0B9C 48002825 */  bl      EXISelect
/* 09B600 800A0BA0 2C030000 */  cmpwi   r3, 0
/* 09B604 800A0BA4 40820014 */  bne     lbl_800A0BB8
/* 09B608 800A0BA8 38600000 */  li      r3, 0
/* 09B60C 800A0BAC 480030C9 */  bl      EXIUnlock
/* 09B610 800A0BB0 38000000 */  li      r0, 0
/* 09B614 800A0BB4 4800008C */  b       lbl_800A0C40
lbl_800A0BB8:
/* 09B618 800A0BB8 57A33032 */  slwi    r3, r29, 6
/* 09B61C 800A0BBC 38030100 */  addi    r0, r3, 0x100
/* 09B620 800A0BC0 6400A000 */  oris    r0, r0, 0xa000
/* 09B624 800A0BC4 90010010 */  stw     r0, 0x10(r1)
/* 09B628 800A0BC8 38810010 */  addi    r4, r1, 0x10
/* 09B62C 800A0BCC 38600000 */  li      r3, 0
/* 09B630 800A0BD0 38A00004 */  li      r5, 4
/* 09B634 800A0BD4 38C00001 */  li      r6, 1
/* 09B638 800A0BD8 38E00000 */  li      r7, 0
/* 09B63C 800A0BDC 48001C7D */  bl      EXIImm
/* 09B640 800A0BE0 7C600034 */  cntlzw  r0, r3
/* 09B644 800A0BE4 541DD97E */  srwi    r29, r0, 5
/* 09B648 800A0BE8 38600000 */  li      r3, 0
/* 09B64C 800A0BEC 48002055 */  bl      EXISync
/* 09B650 800A0BF0 7C600034 */  cntlzw  r0, r3
/* 09B654 800A0BF4 5400D97E */  srwi    r0, r0, 5
/* 09B658 800A0BF8 389C0000 */  addi    r4, r28, 0
/* 09B65C 800A0BFC 38BB0000 */  addi    r5, r27, 0
/* 09B660 800A0C00 7FBD0378 */  or      r29, r29, r0
/* 09B664 800A0C04 38600000 */  li      r3, 0
/* 09B668 800A0C08 38C00001 */  li      r6, 1
/* 09B66C 800A0C0C 48001EA9 */  bl      EXIImmEx
/* 09B670 800A0C10 7C600034 */  cntlzw  r0, r3
/* 09B674 800A0C14 5400D97E */  srwi    r0, r0, 5
/* 09B678 800A0C18 7FBD0378 */  or      r29, r29, r0
/* 09B67C 800A0C1C 38600000 */  li      r3, 0
/* 09B680 800A0C20 480028CD */  bl      EXIDeselect
/* 09B684 800A0C24 7C600034 */  cntlzw  r0, r3
/* 09B688 800A0C28 5400D97E */  srwi    r0, r0, 5
/* 09B68C 800A0C2C 7FBD0378 */  or      r29, r29, r0
/* 09B690 800A0C30 38600000 */  li      r3, 0
/* 09B694 800A0C34 48003041 */  bl      EXIUnlock
/* 09B698 800A0C38 7FA00034 */  cntlzw  r0, r29
/* 09B69C 800A0C3C 5400D97E */  srwi    r0, r0, 5
lbl_800A0C40:
/* 09B6A0 800A0C40 901F004C */  stw     r0, 0x4c(r31)
/* 09B6A4 800A0C44 801F004C */  lwz     r0, 0x4c(r31)
/* 09B6A8 800A0C48 2C000000 */  cmpwi   r0, 0
/* 09B6AC 800A0C4C 4182000C */  beq     lbl_800A0C58
/* 09B6B0 800A0C50 38000040 */  li      r0, 0x40
/* 09B6B4 800A0C54 901E0000 */  stw     r0, 0(r30)
lbl_800A0C58:
/* 09B6B8 800A0C58 38000000 */  li      r0, 0
/* 09B6BC 800A0C5C 901F0048 */  stw     r0, 0x48(r31)
/* 09B6C0 800A0C60 807F0044 */  lwz     r3, 0x44(r31)
/* 09B6C4 800A0C64 4BFFE0C1 */  bl      OSRestoreInterrupts
/* 09B6C8 800A0C68 807F004C */  lwz     r3, 0x4c(r31)
/* 09B6CC 800A0C6C BB61001C */  lmw     r27, 0x1c(r1)
/* 09B6D0 800A0C70 80010034 */  lwz     r0, 0x34(r1)
/* 09B6D4 800A0C74 38210030 */  addi    r1, r1, 0x30
/* 09B6D8 800A0C78 7C0803A6 */  mtlr    r0
/* 09B6DC 800A0C7C 4E800020 */  blr     

glabel __OSUnlockSram
/* 09B6E0 800A0C80 7C0802A6 */  mflr    r0
/* 09B6E4 800A0C84 38800000 */  li      r4, 0
/* 09B6E8 800A0C88 90010004 */  stw     r0, 4(r1)
/* 09B6EC 800A0C8C 9421FFF8 */  stwu    r1, -8(r1)
/* 09B6F0 800A0C90 4BFFFCB5 */  bl      UnlockSram
/* 09B6F4 800A0C94 8001000C */  lwz     r0, 0xc(r1)
/* 09B6F8 800A0C98 38210008 */  addi    r1, r1, 8
/* 09B6FC 800A0C9C 7C0803A6 */  mtlr    r0
/* 09B700 800A0CA0 4E800020 */  blr     

glabel __OSUnlockSramEx
/* 09B704 800A0CA4 7C0802A6 */  mflr    r0
/* 09B708 800A0CA8 38800014 */  li      r4, 0x14
/* 09B70C 800A0CAC 90010004 */  stw     r0, 4(r1)
/* 09B710 800A0CB0 9421FFF8 */  stwu    r1, -8(r1)
/* 09B714 800A0CB4 4BFFFC91 */  bl      UnlockSram
/* 09B718 800A0CB8 8001000C */  lwz     r0, 0xc(r1)
/* 09B71C 800A0CBC 38210008 */  addi    r1, r1, 8
/* 09B720 800A0CC0 7C0803A6 */  mtlr    r0
/* 09B724 800A0CC4 4E800020 */  blr     

glabel __OSSyncSram
/* 09B728 800A0CC8 3C608013 */  lis     r3, Scb@ha
/* 09B72C 800A0CCC 38630FE0 */  addi    r3, r3, Scb@l
/* 09B730 800A0CD0 8063004C */  lwz     r3, 0x4c(r3)
/* 09B734 800A0CD4 4E800020 */  blr     

glabel OSGetSoundMode
/* 09B738 800A0CD8 7C0802A6 */  mflr    r0
/* 09B73C 800A0CDC 3C608013 */  lis     r3, Scb@ha
/* 09B740 800A0CE0 90010004 */  stw     r0, 4(r1)
/* 09B744 800A0CE4 9421FFE0 */  stwu    r1, -0x20(r1)
/* 09B748 800A0CE8 93E1001C */  stw     r31, 0x1c(r1)
/* 09B74C 800A0CEC 3BE30FE0 */  addi    r31, r3, Scb@l
/* 09B750 800A0CF0 4BFFE00D */  bl      OSDisableInterrupts
/* 09B754 800A0CF4 801F0048 */  lwz     r0, 0x48(r31)
/* 09B758 800A0CF8 389F0048 */  addi    r4, r31, 0x48
/* 09B75C 800A0CFC 2C000000 */  cmpwi   r0, 0
/* 09B760 800A0D00 41820010 */  beq     lbl_800A0D10
/* 09B764 800A0D04 4BFFE021 */  bl      OSRestoreInterrupts
/* 09B768 800A0D08 3BE00000 */  li      r31, 0
/* 09B76C 800A0D0C 48000010 */  b       lbl_800A0D1C
lbl_800A0D10:
/* 09B770 800A0D10 907F0044 */  stw     r3, 0x44(r31)
/* 09B774 800A0D14 38000001 */  li      r0, 1
/* 09B778 800A0D18 90040000 */  stw     r0, 0(r4)
lbl_800A0D1C:
/* 09B77C 800A0D1C 881F0013 */  lbz     r0, 0x13(r31)
/* 09B780 800A0D20 5400077B */  rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 09B784 800A0D24 4182000C */  beq     lbl_800A0D30
/* 09B788 800A0D28 3BE00001 */  li      r31, 1
/* 09B78C 800A0D2C 48000008 */  b       lbl_800A0D34
lbl_800A0D30:
/* 09B790 800A0D30 3BE00000 */  li      r31, 0
lbl_800A0D34:
/* 09B794 800A0D34 38600000 */  li      r3, 0
/* 09B798 800A0D38 38800000 */  li      r4, 0
/* 09B79C 800A0D3C 4BFFFC09 */  bl      UnlockSram
/* 09B7A0 800A0D40 7FE3FB78 */  mr      r3, r31
/* 09B7A4 800A0D44 80010024 */  lwz     r0, 0x24(r1)
/* 09B7A8 800A0D48 83E1001C */  lwz     r31, 0x1c(r1)
/* 09B7AC 800A0D4C 38210020 */  addi    r1, r1, 0x20
/* 09B7B0 800A0D50 7C0803A6 */  mtlr    r0
/* 09B7B4 800A0D54 4E800020 */  blr     

glabel OSSetSoundMode
/* 09B7B8 800A0D58 7C0802A6 */  mflr    r0
/* 09B7BC 800A0D5C 3C808013 */  lis     r4, Scb@ha
/* 09B7C0 800A0D60 90010004 */  stw     r0, 4(r1)
/* 09B7C4 800A0D64 9421FFE0 */  stwu    r1, -0x20(r1)
/* 09B7C8 800A0D68 93E1001C */  stw     r31, 0x1c(r1)
/* 09B7CC 800A0D6C 3BE40FE0 */  addi    r31, r4, Scb@l
/* 09B7D0 800A0D70 93C10018 */  stw     r30, 0x18(r1)
/* 09B7D4 800A0D74 547E177A */  rlwinm  r30, r3, 2, 0x1d, 0x1d
/* 09B7D8 800A0D78 4BFFDF85 */  bl      OSDisableInterrupts
/* 09B7DC 800A0D7C 801F0048 */  lwz     r0, 0x48(r31)
/* 09B7E0 800A0D80 389F0048 */  addi    r4, r31, 0x48
/* 09B7E4 800A0D84 2C000000 */  cmpwi   r0, 0
/* 09B7E8 800A0D88 41820010 */  beq     lbl_800A0D98
/* 09B7EC 800A0D8C 4BFFDF99 */  bl      OSRestoreInterrupts
/* 09B7F0 800A0D90 3BE00000 */  li      r31, 0
/* 09B7F4 800A0D94 48000010 */  b       lbl_800A0DA4
lbl_800A0D98:
/* 09B7F8 800A0D98 907F0044 */  stw     r3, 0x44(r31)
/* 09B7FC 800A0D9C 38000001 */  li      r0, 1
/* 09B800 800A0DA0 90040000 */  stw     r0, 0(r4)
lbl_800A0DA4:
/* 09B804 800A0DA4 887F0013 */  lbz     r3, 0x13(r31)
/* 09B808 800A0DA8 5460077A */  rlwinm  r0, r3, 0, 0x1d, 0x1d
/* 09B80C 800A0DAC 7C1E0040 */  cmplw   r30, r0
/* 09B810 800A0DB0 40820014 */  bne     lbl_800A0DC4
/* 09B814 800A0DB4 38600000 */  li      r3, 0
/* 09B818 800A0DB8 38800000 */  li      r4, 0
/* 09B81C 800A0DBC 4BFFFB89 */  bl      UnlockSram
/* 09B820 800A0DC0 48000024 */  b       lbl_800A0DE4
lbl_800A0DC4:
/* 09B824 800A0DC4 546007B8 */  rlwinm  r0, r3, 0, 0x1e, 0x1c
/* 09B828 800A0DC8 981F0013 */  stb     r0, 0x13(r31)
/* 09B82C 800A0DCC 38600001 */  li      r3, 1
/* 09B830 800A0DD0 38800000 */  li      r4, 0
/* 09B834 800A0DD4 881F0013 */  lbz     r0, 0x13(r31)
/* 09B838 800A0DD8 7C00F378 */  or      r0, r0, r30
/* 09B83C 800A0DDC 981F0013 */  stb     r0, 0x13(r31)
/* 09B840 800A0DE0 4BFFFB65 */  bl      UnlockSram
lbl_800A0DE4:
/* 09B844 800A0DE4 80010024 */  lwz     r0, 0x24(r1)
/* 09B848 800A0DE8 83E1001C */  lwz     r31, 0x1c(r1)
/* 09B84C 800A0DEC 83C10018 */  lwz     r30, 0x18(r1)
/* 09B850 800A0DF0 38210020 */  addi    r1, r1, 0x20
/* 09B854 800A0DF4 7C0803A6 */  mtlr    r0
/* 09B858 800A0DF8 4E800020 */  blr     

glabel OSGetWirelessID
/* 09B85C 800A0DFC 7C0802A6 */  mflr    r0
/* 09B860 800A0E00 3C808013 */  lis     r4, Scb@ha
/* 09B864 800A0E04 90010004 */  stw     r0, 4(r1)
/* 09B868 800A0E08 9421FFE0 */  stwu    r1, -0x20(r1)
/* 09B86C 800A0E0C 93E1001C */  stw     r31, 0x1c(r1)
/* 09B870 800A0E10 3BE40FE0 */  addi    r31, r4, Scb@l
/* 09B874 800A0E14 93C10018 */  stw     r30, 0x18(r1)
/* 09B878 800A0E18 3BC30000 */  addi    r30, r3, 0
/* 09B87C 800A0E1C 4BFFDEE1 */  bl      OSDisableInterrupts
/* 09B880 800A0E20 801F0048 */  lwz     r0, 0x48(r31)
/* 09B884 800A0E24 389F0048 */  addi    r4, r31, 0x48
/* 09B888 800A0E28 2C000000 */  cmpwi   r0, 0
/* 09B88C 800A0E2C 41820010 */  beq     lbl_800A0E3C
/* 09B890 800A0E30 4BFFDEF5 */  bl      OSRestoreInterrupts
/* 09B894 800A0E34 38600000 */  li      r3, 0
/* 09B898 800A0E38 48000014 */  b       lbl_800A0E4C
lbl_800A0E3C:
/* 09B89C 800A0E3C 907F0044 */  stw     r3, 0x44(r31)
/* 09B8A0 800A0E40 38000001 */  li      r0, 1
/* 09B8A4 800A0E44 387F0014 */  addi    r3, r31, 0x14
/* 09B8A8 800A0E48 90040000 */  stw     r0, 0(r4)
lbl_800A0E4C:
/* 09B8AC 800A0E4C 57C0083C */  slwi    r0, r30, 1
/* 09B8B0 800A0E50 7C630214 */  add     r3, r3, r0
/* 09B8B4 800A0E54 A3E3001C */  lhz     r31, 0x1c(r3)
/* 09B8B8 800A0E58 38600000 */  li      r3, 0
/* 09B8BC 800A0E5C 38800014 */  li      r4, 0x14
/* 09B8C0 800A0E60 4BFFFAE5 */  bl      UnlockSram
/* 09B8C4 800A0E64 7FE3FB78 */  mr      r3, r31
/* 09B8C8 800A0E68 80010024 */  lwz     r0, 0x24(r1)
/* 09B8CC 800A0E6C 83E1001C */  lwz     r31, 0x1c(r1)
/* 09B8D0 800A0E70 83C10018 */  lwz     r30, 0x18(r1)
/* 09B8D4 800A0E74 38210020 */  addi    r1, r1, 0x20
/* 09B8D8 800A0E78 7C0803A6 */  mtlr    r0
/* 09B8DC 800A0E7C 4E800020 */  blr     

glabel OSSetWirelessID
/* 09B8E0 800A0E80 7C0802A6 */  mflr    r0
/* 09B8E4 800A0E84 3CA08013 */  lis     r5, Scb@ha
/* 09B8E8 800A0E88 90010004 */  stw     r0, 4(r1)
/* 09B8EC 800A0E8C 9421FFD8 */  stwu    r1, -0x28(r1)
/* 09B8F0 800A0E90 93E10024 */  stw     r31, 0x24(r1)
/* 09B8F4 800A0E94 3BE50FE0 */  addi    r31, r5, Scb@l
/* 09B8F8 800A0E98 93C10020 */  stw     r30, 0x20(r1)
/* 09B8FC 800A0E9C 3BC40000 */  addi    r30, r4, 0
/* 09B900 800A0EA0 93A1001C */  stw     r29, 0x1c(r1)
/* 09B904 800A0EA4 3BA30000 */  addi    r29, r3, 0
/* 09B908 800A0EA8 4BFFDE55 */  bl      OSDisableInterrupts
/* 09B90C 800A0EAC 801F0048 */  lwz     r0, 0x48(r31)
/* 09B910 800A0EB0 389F0048 */  addi    r4, r31, 0x48
/* 09B914 800A0EB4 2C000000 */  cmpwi   r0, 0
/* 09B918 800A0EB8 41820010 */  beq     lbl_800A0EC8
/* 09B91C 800A0EBC 4BFFDE69 */  bl      OSRestoreInterrupts
/* 09B920 800A0EC0 38600000 */  li      r3, 0
/* 09B924 800A0EC4 48000014 */  b       lbl_800A0ED8
lbl_800A0EC8:
/* 09B928 800A0EC8 907F0044 */  stw     r3, 0x44(r31)
/* 09B92C 800A0ECC 38000001 */  li      r0, 1
/* 09B930 800A0ED0 387F0014 */  addi    r3, r31, 0x14
/* 09B934 800A0ED4 90040000 */  stw     r0, 0(r4)
lbl_800A0ED8:
/* 09B938 800A0ED8 57A0083C */  slwi    r0, r29, 1
/* 09B93C 800A0EDC 7C830214 */  add     r4, r3, r0
/* 09B940 800A0EE0 A464001C */  lhzu    r3, 0x1c(r4)
/* 09B944 800A0EE4 57C0043E */  clrlwi  r0, r30, 0x10
/* 09B948 800A0EE8 7C030040 */  cmplw   r3, r0
/* 09B94C 800A0EEC 41820018 */  beq     lbl_800A0F04
/* 09B950 800A0EF0 B3C40000 */  sth     r30, 0(r4)
/* 09B954 800A0EF4 38600001 */  li      r3, 1
/* 09B958 800A0EF8 38800014 */  li      r4, 0x14
/* 09B95C 800A0EFC 4BFFFA49 */  bl      UnlockSram
/* 09B960 800A0F00 48000010 */  b       lbl_800A0F10
lbl_800A0F04:
/* 09B964 800A0F04 38600000 */  li      r3, 0
/* 09B968 800A0F08 38800014 */  li      r4, 0x14
/* 09B96C 800A0F0C 4BFFFA39 */  bl      UnlockSram
lbl_800A0F10:
/* 09B970 800A0F10 8001002C */  lwz     r0, 0x2c(r1)
/* 09B974 800A0F14 83E10024 */  lwz     r31, 0x24(r1)
/* 09B978 800A0F18 83C10020 */  lwz     r30, 0x20(r1)
/* 09B97C 800A0F1C 83A1001C */  lwz     r29, 0x1c(r1)
/* 09B980 800A0F20 38210028 */  addi    r1, r1, 0x28
/* 09B984 800A0F24 7C0803A6 */  mtlr    r0
/* 09B988 800A0F28 4E800020 */  blr     

glabel OSGetGbsMode
/* 09B98C 800A0F2C 7C0802A6 */  mflr    r0
/* 09B990 800A0F30 3C608013 */  lis     r3, Scb@ha
/* 09B994 800A0F34 90010004 */  stw     r0, 4(r1)
/* 09B998 800A0F38 9421FFE8 */  stwu    r1, -0x18(r1)
/* 09B99C 800A0F3C 93E10014 */  stw     r31, 0x14(r1)
/* 09B9A0 800A0F40 3BE30FE0 */  addi    r31, r3, Scb@l
/* 09B9A4 800A0F44 4BFFDDB9 */  bl      OSDisableInterrupts
/* 09B9A8 800A0F48 801F0048 */  lwz     r0, 0x48(r31)
/* 09B9AC 800A0F4C 389F0048 */  addi    r4, r31, 0x48
/* 09B9B0 800A0F50 2C000000 */  cmpwi   r0, 0
/* 09B9B4 800A0F54 41820010 */  beq     lbl_800A0F64
/* 09B9B8 800A0F58 4BFFDDCD */  bl      OSRestoreInterrupts
/* 09B9BC 800A0F5C 38600000 */  li      r3, 0
/* 09B9C0 800A0F60 48000014 */  b       lbl_800A0F74
lbl_800A0F64:
/* 09B9C4 800A0F64 907F0044 */  stw     r3, 0x44(r31)
/* 09B9C8 800A0F68 38000001 */  li      r0, 1
/* 09B9CC 800A0F6C 387F0014 */  addi    r3, r31, 0x14
/* 09B9D0 800A0F70 90040000 */  stw     r0, 0(r4)
lbl_800A0F74:
/* 09B9D4 800A0F74 A3E30028 */  lhz     r31, 0x28(r3)
/* 09B9D8 800A0F78 38600000 */  li      r3, 0
/* 09B9DC 800A0F7C 38800014 */  li      r4, 0x14
/* 09B9E0 800A0F80 4BFFF9C5 */  bl      UnlockSram
/* 09B9E4 800A0F84 7FE3FB78 */  mr      r3, r31
/* 09B9E8 800A0F88 8001001C */  lwz     r0, 0x1c(r1)
/* 09B9EC 800A0F8C 83E10014 */  lwz     r31, 0x14(r1)
/* 09B9F0 800A0F90 38210018 */  addi    r1, r1, 0x18
/* 09B9F4 800A0F94 7C0803A6 */  mtlr    r0
/* 09B9F8 800A0F98 4E800020 */  blr     

glabel OSSetGbsMode
/* 09B9FC 800A0F9C 7C0802A6 */  mflr    r0
/* 09BA00 800A0FA0 5464043E */  clrlwi  r4, r3, 0x10
/* 09BA04 800A0FA4 90010004 */  stw     r0, 4(r1)
/* 09BA08 800A0FA8 5460046A */  rlwinm  r0, r3, 0, 0x11, 0x15
/* 09BA0C 800A0FAC 28005000 */  cmplwi  r0, 0x5000
/* 09BA10 800A0FB0 9421FFE0 */  stwu    r1, -0x20(r1)
/* 09BA14 800A0FB4 93E1001C */  stw     r31, 0x1c(r1)
/* 09BA18 800A0FB8 93C10018 */  stw     r30, 0x18(r1)
/* 09BA1C 800A0FBC 3BC30000 */  addi    r30, r3, 0
/* 09BA20 800A0FC0 3C608013 */  lis     r3, Scb@ha
/* 09BA24 800A0FC4 3BE30FE0 */  addi    r31, r3, Scb@l
/* 09BA28 800A0FC8 41820010 */  beq     lbl_800A0FD8
/* 09BA2C 800A0FCC 54800632 */  rlwinm  r0, r4, 0, 0x18, 0x19
/* 09BA30 800A0FD0 280000C0 */  cmplwi  r0, 0xc0
/* 09BA34 800A0FD4 40820008 */  bne     lbl_800A0FDC
lbl_800A0FD8:
/* 09BA38 800A0FD8 3BC00000 */  li      r30, 0
lbl_800A0FDC:
/* 09BA3C 800A0FDC 4BFFDD21 */  bl      OSDisableInterrupts
/* 09BA40 800A0FE0 801F0048 */  lwz     r0, 0x48(r31)
/* 09BA44 800A0FE4 38BF0048 */  addi    r5, r31, 0x48
/* 09BA48 800A0FE8 2C000000 */  cmpwi   r0, 0
/* 09BA4C 800A0FEC 41820010 */  beq     lbl_800A0FFC
/* 09BA50 800A0FF0 4BFFDD35 */  bl      OSRestoreInterrupts
/* 09BA54 800A0FF4 38800000 */  li      r4, 0
/* 09BA58 800A0FF8 48000014 */  b       lbl_800A100C
lbl_800A0FFC:
/* 09BA5C 800A0FFC 907F0044 */  stw     r3, 0x44(r31)
/* 09BA60 800A1000 38000001 */  li      r0, 1
/* 09BA64 800A1004 389F0014 */  addi    r4, r31, 0x14
/* 09BA68 800A1008 90050000 */  stw     r0, 0(r5)
lbl_800A100C:
/* 09BA6C 800A100C A0040028 */  lhz     r0, 0x28(r4)
/* 09BA70 800A1010 57C3043E */  clrlwi  r3, r30, 0x10
/* 09BA74 800A1014 7C030040 */  cmplw   r3, r0
/* 09BA78 800A1018 40820014 */  bne     lbl_800A102C
/* 09BA7C 800A101C 38600000 */  li      r3, 0
/* 09BA80 800A1020 38800014 */  li      r4, 0x14
/* 09BA84 800A1024 4BFFF921 */  bl      UnlockSram
/* 09BA88 800A1028 48000014 */  b       lbl_800A103C
lbl_800A102C:
/* 09BA8C 800A102C B3C40028 */  sth     r30, 0x28(r4)
/* 09BA90 800A1030 38600001 */  li      r3, 1
/* 09BA94 800A1034 38800014 */  li      r4, 0x14
/* 09BA98 800A1038 4BFFF90D */  bl      UnlockSram
lbl_800A103C:
/* 09BA9C 800A103C 80010024 */  lwz     r0, 0x24(r1)
/* 09BAA0 800A1040 83E1001C */  lwz     r31, 0x1c(r1)
/* 09BAA4 800A1044 83C10018 */  lwz     r30, 0x18(r1)
/* 09BAA8 800A1048 38210020 */  addi    r1, r1, 0x20
/* 09BAAC 800A104C 7C0803A6 */  mtlr    r0
/* 09BAB0 800A1050 4E800020 */  blr     

.section .bss, "wa"

.balign 4

/* 0012E060 80130FE0 0054 */
Scb:
    .skip 84
