# audio.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel audioEvent
/* 088F08 8008E4A8 7C0802A6 */  mflr    r0
/* 088F0C 8008E4AC 2C040003 */  cmpwi   r4, 3
/* 088F10 8008E4B0 90010004 */  stw     r0, 4(r1)
/* 088F14 8008E4B4 9421FFE0 */  stwu    r1, -0x20(r1)
/* 088F18 8008E4B8 93E1001C */  stw     r31, 0x1c(r1)
/* 088F1C 8008E4BC 3BE50000 */  addi    r31, r5, 0
/* 088F20 8008E4C0 93C10018 */  stw     r30, 0x18(r1)
/* 088F24 8008E4C4 3BC30000 */  addi    r30, r3, 0
/* 088F28 8008E4C8 418200E4 */  beq     lbl_8008E5AC
/* 088F2C 8008E4CC 40800018 */  bge     lbl_8008E4E4
/* 088F30 8008E4D0 2C040002 */  cmpwi   r4, 2
/* 088F34 8008E4D4 40800028 */  bge     lbl_8008E4FC
/* 088F38 8008E4D8 2C040000 */  cmpwi   r4, 0
/* 088F3C 8008E4DC 408000D0 */  bge     lbl_8008E5AC
/* 088F40 8008E4E0 480000C4 */  b       lbl_8008E5A4
lbl_8008E4E4:
/* 088F44 8008E4E4 2C041003 */  cmpwi   r4, 0x1003
/* 088F48 8008E4E8 418200C4 */  beq     lbl_8008E5AC
/* 088F4C 8008E4EC 408000B8 */  bge     lbl_8008E5A4
/* 088F50 8008E4F0 2C041002 */  cmpwi   r4, 0x1002
/* 088F54 8008E4F4 40800030 */  bge     lbl_8008E524
/* 088F58 8008E4F8 480000AC */  b       lbl_8008E5A4
lbl_8008E4FC:
/* 088F5C 8008E4FC 38600000 */  li      r3, 0
/* 088F60 8008E500 907E0000 */  stw     r3, 0(r30)
/* 088F64 8008E504 38000001 */  li      r0, 1
/* 088F68 8008E508 901E000C */  stw     r0, 0xc(r30)
/* 088F6C 8008E50C 907E0010 */  stw     r3, 0x10(r30)
/* 088F70 8008E510 907E0014 */  stw     r3, 0x14(r30)
/* 088F74 8008E514 907E0018 */  stw     r3, 0x18(r30)
/* 088F78 8008E518 93FE0008 */  stw     r31, 8(r30)
/* 088F7C 8008E51C 901E0004 */  stw     r0, 4(r30)
/* 088F80 8008E520 4800008C */  b       lbl_8008E5AC
lbl_8008E524:
/* 088F84 8008E524 807E0008 */  lwz     r3, 8(r30)
/* 088F88 8008E528 3CA08009 */  lis     r5, audioPut8@ha
/* 088F8C 8008E52C 3CC08009 */  lis     r6, audioPut16@ha
/* 088F90 8008E530 3CE08009 */  lis     r7, audioPut32@ha
/* 088F94 8008E534 80630024 */  lwz     r3, 0x24(r3)
/* 088F98 8008E538 3C808009 */  lis     r4, audioPut64@ha
/* 088F9C 8008E53C 3904E740 */  addi    r8, r4, audioPut64@l
/* 088FA0 8008E540 38A5E898 */  addi    r5, r5, audioPut8@l
/* 088FA4 8008E544 38C6E890 */  addi    r6, r6, audioPut16@l
/* 088FA8 8008E548 38E7E748 */  addi    r7, r7, audioPut32@l
/* 088FAC 8008E54C 389F0000 */  addi    r4, r31, 0
/* 088FB0 8008E550 4BFA6AE9 */  bl      cpuSetDevicePut
/* 088FB4 8008E554 2C030000 */  cmpwi   r3, 0
/* 088FB8 8008E558 4082000C */  bne     lbl_8008E564
/* 088FBC 8008E55C 38600000 */  li      r3, 0
/* 088FC0 8008E560 48000050 */  b       lbl_8008E5B0
lbl_8008E564:
/* 088FC4 8008E564 807E0008 */  lwz     r3, 8(r30)
/* 088FC8 8008E568 3CA08009 */  lis     r5, audioGet8@ha
/* 088FCC 8008E56C 3CC08009 */  lis     r6, audioGet16@ha
/* 088FD0 8008E570 3CE08009 */  lis     r7, audioGet32@ha
/* 088FD4 8008E574 80630024 */  lwz     r3, 0x24(r3)
/* 088FD8 8008E578 3C808009 */  lis     r4, audioGet64@ha
/* 088FDC 8008E57C 3904E620 */  addi    r8, r4, audioGet64@l
/* 088FE0 8008E580 38A5E738 */  addi    r5, r5, audioGet8@l
/* 088FE4 8008E584 38C6E730 */  addi    r6, r6, audioGet16@l
/* 088FE8 8008E588 38E7E628 */  addi    r7, r7, audioGet32@l
/* 088FEC 8008E58C 389F0000 */  addi    r4, r31, 0
/* 088FF0 8008E590 4BFA6AC1 */  bl      cpuSetDeviceGet
/* 088FF4 8008E594 2C030000 */  cmpwi   r3, 0
/* 088FF8 8008E598 40820014 */  bne     lbl_8008E5AC
/* 088FFC 8008E59C 38600000 */  li      r3, 0
/* 089000 8008E5A0 48000010 */  b       lbl_8008E5B0
lbl_8008E5A4:
/* 089004 8008E5A4 38600000 */  li      r3, 0
/* 089008 8008E5A8 48000008 */  b       lbl_8008E5B0
lbl_8008E5AC:
/* 08900C 8008E5AC 38600001 */  li      r3, 1
lbl_8008E5B0:
/* 089010 8008E5B0 80010024 */  lwz     r0, 0x24(r1)
/* 089014 8008E5B4 83E1001C */  lwz     r31, 0x1c(r1)
/* 089018 8008E5B8 83C10018 */  lwz     r30, 0x18(r1)
/* 08901C 8008E5BC 7C0803A6 */  mtlr    r0
/* 089020 8008E5C0 38210020 */  addi    r1, r1, 0x20
/* 089024 8008E5C4 4E800020 */  blr     

glabel audioEnable
/* 089028 8008E5C8 7C0802A6 */  mflr    r0
/* 08902C 8008E5CC 2C040000 */  cmpwi   r4, 0
/* 089030 8008E5D0 90010004 */  stw     r0, 4(r1)
/* 089034 8008E5D4 9421FFF8 */  stwu    r1, -8(r1)
/* 089038 8008E5D8 4182000C */  beq     lbl_8008E5E4
/* 08903C 8008E5DC 38000001 */  li      r0, 1
/* 089040 8008E5E0 48000008 */  b       lbl_8008E5E8
lbl_8008E5E4:
/* 089044 8008E5E4 38000000 */  li      r0, 0
lbl_8008E5E8:
/* 089048 8008E5E8 90030004 */  stw     r0, 4(r3)
/* 08904C 8008E5EC 80A30008 */  lwz     r5, 8(r3)
/* 089050 8008E5F0 80830004 */  lwz     r4, 4(r3)
/* 089054 8008E5F4 80650034 */  lwz     r3, 0x34(r5)
/* 089058 8008E5F8 4BFE39C9 */  bl      rspEnableABI
/* 08905C 8008E5FC 2C030000 */  cmpwi   r3, 0
/* 089060 8008E600 4082000C */  bne     lbl_8008E60C
/* 089064 8008E604 38600000 */  li      r3, 0
/* 089068 8008E608 48000008 */  b       lbl_8008E610
lbl_8008E60C:
/* 08906C 8008E60C 38600001 */  li      r3, 1
lbl_8008E610:
/* 089070 8008E610 8001000C */  lwz     r0, 0xc(r1)
/* 089074 8008E614 38210008 */  addi    r1, r1, 8
/* 089078 8008E618 7C0803A6 */  mtlr    r0
/* 08907C 8008E61C 4E800020 */  blr     

glabel audioGet64
/* 089080 8008E620 38600000 */  li      r3, 0
/* 089084 8008E624 4E800020 */  blr     

glabel audioGet32
/* 089088 8008E628 7C0802A6 */  mflr    r0
/* 08908C 8008E62C 90010004 */  stw     r0, 4(r1)
/* 089090 8008E630 548006FE */  clrlwi  r0, r4, 0x1b
/* 089094 8008E634 28000014 */  cmplwi  r0, 0x14
/* 089098 8008E638 9421FFE0 */  stwu    r1, -0x20(r1)
/* 08909C 8008E63C 93E1001C */  stw     r31, 0x1c(r1)
/* 0890A0 8008E640 3BE50000 */  addi    r31, r5, 0
/* 0890A4 8008E644 93C10018 */  stw     r30, 0x18(r1)
/* 0890A8 8008E648 3BC30000 */  addi    r30, r3, 0
/* 0890AC 8008E64C 418100C0 */  bgt     lbl_8008E70C
/* 0890B0 8008E650 3C60800F */  lis     r3, jtbl_800EE7C4@ha
/* 0890B4 8008E654 3863E7C4 */  addi    r3, r3, jtbl_800EE7C4@l
/* 0890B8 8008E658 5400103A */  slwi    r0, r0, 2
/* 0890BC 8008E65C 7C03002E */  lwzx    r0, r3, r0
/* 0890C0 8008E660 7C0903A6 */  mtctr   r0
/* 0890C4 8008E664 4E800420 */  bctr    
glabel lbl_8008E668
/* 0890C8 8008E668 801E0010 */  lwz     r0, 0x10(r30)
/* 0890CC 8008E66C 3C60800F */  lis     r3, D_800EE788@ha
/* 0890D0 8008E670 3863E788 */  addi    r3, r3, D_800EE788@l
/* 0890D4 8008E674 4CC63182 */  crclr   6
/* 0890D8 8008E678 901F0000 */  stw     r0, 0(r31)
/* 0890DC 8008E67C 388D8630 */  addi    r4, r13, D_80135310-_SDA_BASE_
/* 0890E0 8008E680 38A000DA */  li      r5, 0xda
/* 0890E4 8008E684 4BF77791 */  bl      xlPostText
/* 0890E8 8008E688 4800008C */  b       lbl_8008E714
glabel lbl_8008E68C
/* 0890EC 8008E68C 807E0008 */  lwz     r3, 8(r30)
/* 0890F0 8008E690 7FE4FB78 */  mr      r4, r31
/* 0890F4 8008E694 80630004 */  lwz     r3, 4(r3)
/* 0890F8 8008E698 4BF8E389 */  bl      soundGetDMABuffer
/* 0890FC 8008E69C 2C030000 */  cmpwi   r3, 0
/* 089100 8008E6A0 40820074 */  bne     lbl_8008E714
/* 089104 8008E6A4 801E0000 */  lwz     r0, 0(r30)
/* 089108 8008E6A8 901F0000 */  stw     r0, 0(r31)
/* 08910C 8008E6AC 48000068 */  b       lbl_8008E714
glabel lbl_8008E6B0
/* 089110 8008E6B0 801E000C */  lwz     r0, 0xc(r30)
/* 089114 8008E6B4 3C60800F */  lis     r3, D_800EE7A8@ha
/* 089118 8008E6B8 3863E7A8 */  addi    r3, r3, D_800EE7A8@l
/* 08911C 8008E6BC 4CC63182 */  crclr   6
/* 089120 8008E6C0 901F0000 */  stw     r0, 0(r31)
/* 089124 8008E6C4 388D8630 */  addi    r4, r13, D_80135310-_SDA_BASE_
/* 089128 8008E6C8 38A000E4 */  li      r5, 0xe4
/* 08912C 8008E6CC 4BF77749 */  bl      xlPostText
/* 089130 8008E6D0 48000044 */  b       lbl_8008E714
glabel lbl_8008E6D4
/* 089134 8008E6D4 480299BD */  bl      AIGetDMABytesLeft
/* 089138 8008E6D8 28030000 */  cmplwi  r3, 0
/* 08913C 8008E6DC 4182000C */  beq     lbl_8008E6E8
/* 089140 8008E6E0 3C004000 */  lis     r0, 0x4000
/* 089144 8008E6E4 48000008 */  b       lbl_8008E6EC
lbl_8008E6E8:
/* 089148 8008E6E8 38000000 */  li      r0, 0
lbl_8008E6EC:
/* 08914C 8008E6EC 901F0000 */  stw     r0, 0(r31)
/* 089150 8008E6F0 48000024 */  b       lbl_8008E714
glabel lbl_8008E6F4
/* 089154 8008E6F4 801E0018 */  lwz     r0, 0x18(r30)
/* 089158 8008E6F8 901F0000 */  stw     r0, 0(r31)
/* 08915C 8008E6FC 48000018 */  b       lbl_8008E714
glabel lbl_8008E700
/* 089160 8008E700 801E0014 */  lwz     r0, 0x14(r30)
/* 089164 8008E704 901F0000 */  stw     r0, 0(r31)
/* 089168 8008E708 4800000C */  b       lbl_8008E714
glabel lbl_8008E70C
/* 08916C 8008E70C 38600000 */  li      r3, 0
/* 089170 8008E710 48000008 */  b       lbl_8008E718
lbl_8008E714:
/* 089174 8008E714 38600001 */  li      r3, 1
lbl_8008E718:
/* 089178 8008E718 80010024 */  lwz     r0, 0x24(r1)
/* 08917C 8008E71C 83E1001C */  lwz     r31, 0x1c(r1)
/* 089180 8008E720 83C10018 */  lwz     r30, 0x18(r1)
/* 089184 8008E724 7C0803A6 */  mtlr    r0
/* 089188 8008E728 38210020 */  addi    r1, r1, 0x20
/* 08918C 8008E72C 4E800020 */  blr     

glabel audioGet16
/* 089190 8008E730 38600000 */  li      r3, 0
/* 089194 8008E734 4E800020 */  blr     

glabel audioGet8
/* 089198 8008E738 38600000 */  li      r3, 0
/* 08919C 8008E73C 4E800020 */  blr     

glabel audioPut64
/* 0891A0 8008E740 38600000 */  li      r3, 0
/* 0891A4 8008E744 4E800020 */  blr     

glabel audioPut32
/* 0891A8 8008E748 7C0802A6 */  mflr    r0
/* 0891AC 8008E74C 90010004 */  stw     r0, 4(r1)
/* 0891B0 8008E750 548006FE */  clrlwi  r0, r4, 0x1b
/* 0891B4 8008E754 28000014 */  cmplwi  r0, 0x14
/* 0891B8 8008E758 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0891BC 8008E75C 93E1001C */  stw     r31, 0x1c(r1)
/* 0891C0 8008E760 3BE30000 */  addi    r31, r3, 0
/* 0891C4 8008E764 4181010C */  bgt     lbl_8008E870
/* 0891C8 8008E768 3C60800F */  lis     r3, jtbl_800EE818@ha
/* 0891CC 8008E76C 3863E818 */  addi    r3, r3, jtbl_800EE818@l
/* 0891D0 8008E770 5400103A */  slwi    r0, r0, 2
/* 0891D4 8008E774 7C03002E */  lwzx    r0, r3, r0
/* 0891D8 8008E778 7C0903A6 */  mtctr   r0
/* 0891DC 8008E77C 4E800420 */  bctr    
glabel lbl_8008E780
/* 0891E0 8008E780 80050000 */  lwz     r0, 0(r5)
/* 0891E4 8008E784 5400023F */  clrlwi. r0, r0, 8
/* 0891E8 8008E788 901F0010 */  stw     r0, 0x10(r31)
/* 0891EC 8008E78C 418200EC */  beq     lbl_8008E878
/* 0891F0 8008E790 807F0008 */  lwz     r3, 8(r31)
/* 0891F4 8008E794 38810014 */  addi    r4, r1, 0x14
/* 0891F8 8008E798 80BF0010 */  lwz     r5, 0x10(r31)
/* 0891FC 8008E79C 38C00000 */  li      r6, 0
/* 089200 8008E7A0 8063002C */  lwz     r3, 0x2c(r3)
/* 089204 8008E7A4 4BFDE8FD */  bl      ramGetBuffer
/* 089208 8008E7A8 2C030000 */  cmpwi   r3, 0
/* 08920C 8008E7AC 4082000C */  bne     lbl_8008E7B8
/* 089210 8008E7B0 38600000 */  li      r3, 0
/* 089214 8008E7B4 480000C8 */  b       lbl_8008E87C
lbl_8008E7B8:
/* 089218 8008E7B8 801F0004 */  lwz     r0, 4(r31)
/* 08921C 8008E7BC 2C000000 */  cmpwi   r0, 0
/* 089220 8008E7C0 418200B8 */  beq     lbl_8008E878
/* 089224 8008E7C4 807F0008 */  lwz     r3, 8(r31)
/* 089228 8008E7C8 80810014 */  lwz     r4, 0x14(r1)
/* 08922C 8008E7CC 80630004 */  lwz     r3, 4(r3)
/* 089230 8008E7D0 4BF8E285 */  bl      soundSetAddress
/* 089234 8008E7D4 480000A4 */  b       lbl_8008E878
glabel lbl_8008E7D8
/* 089238 8008E7D8 80050000 */  lwz     r0, 0(r5)
/* 08923C 8008E7DC 540003B8 */  rlwinm  r0, r0, 0, 0xe, 0x1c
/* 089240 8008E7E0 901F0000 */  stw     r0, 0(r31)
/* 089244 8008E7E4 801F000C */  lwz     r0, 0xc(r31)
/* 089248 8008E7E8 2C000000 */  cmpwi   r0, 0
/* 08924C 8008E7EC 4182008C */  beq     lbl_8008E878
/* 089250 8008E7F0 801F0004 */  lwz     r0, 4(r31)
/* 089254 8008E7F4 2C000000 */  cmpwi   r0, 0
/* 089258 8008E7F8 41820080 */  beq     lbl_8008E878
/* 08925C 8008E7FC 807F0008 */  lwz     r3, 8(r31)
/* 089260 8008E800 809F0000 */  lwz     r4, 0(r31)
/* 089264 8008E804 80630004 */  lwz     r3, 4(r3)
/* 089268 8008E808 4BF8E279 */  bl      soundSetLength
/* 08926C 8008E80C 4800006C */  b       lbl_8008E878
glabel lbl_8008E810
/* 089270 8008E810 80050000 */  lwz     r0, 0(r5)
/* 089274 8008E814 540007FE */  clrlwi  r0, r0, 0x1f
/* 089278 8008E818 901F000C */  stw     r0, 0xc(r31)
/* 08927C 8008E81C 4800005C */  b       lbl_8008E878
glabel lbl_8008E820
/* 089280 8008E820 807F0008 */  lwz     r3, 8(r31)
/* 089284 8008E824 38801001 */  li      r4, 0x1001
/* 089288 8008E828 38A00007 */  li      r5, 7
/* 08928C 8008E82C 4BF79441 */  bl      xlObjectEvent
/* 089290 8008E830 48000048 */  b       lbl_8008E878
glabel lbl_8008E834
/* 089294 8008E834 80050000 */  lwz     r0, 0(r5)
/* 089298 8008E838 540004BE */  clrlwi  r0, r0, 0x12
/* 08929C 8008E83C 901F0018 */  stw     r0, 0x18(r31)
/* 0892A0 8008E840 801F0004 */  lwz     r0, 4(r31)
/* 0892A4 8008E844 2C000000 */  cmpwi   r0, 0
/* 0892A8 8008E848 41820030 */  beq     lbl_8008E878
/* 0892AC 8008E84C 807F0008 */  lwz     r3, 8(r31)
/* 0892B0 8008E850 809F0018 */  lwz     r4, 0x18(r31)
/* 0892B4 8008E854 80630004 */  lwz     r3, 4(r3)
/* 0892B8 8008E858 4BF8E209 */  bl      soundSetDACRate
/* 0892BC 8008E85C 4800001C */  b       lbl_8008E878
glabel lbl_8008E860
/* 0892C0 8008E860 80050000 */  lwz     r0, 0(r5)
/* 0892C4 8008E864 5400073E */  clrlwi  r0, r0, 0x1c
/* 0892C8 8008E868 901F0014 */  stw     r0, 0x14(r31)
/* 0892CC 8008E86C 4800000C */  b       lbl_8008E878
glabel lbl_8008E870
/* 0892D0 8008E870 38600000 */  li      r3, 0
/* 0892D4 8008E874 48000008 */  b       lbl_8008E87C
lbl_8008E878:
/* 0892D8 8008E878 38600001 */  li      r3, 1
lbl_8008E87C:
/* 0892DC 8008E87C 80010024 */  lwz     r0, 0x24(r1)
/* 0892E0 8008E880 83E1001C */  lwz     r31, 0x1c(r1)
/* 0892E4 8008E884 38210020 */  addi    r1, r1, 0x20
/* 0892E8 8008E888 7C0803A6 */  mtlr    r0
/* 0892EC 8008E88C 4E800020 */  blr     

glabel audioPut16
/* 0892F0 8008E890 38600000 */  li      r3, 0
/* 0892F4 8008E894 4E800020 */  blr     

glabel audioPut8
/* 0892F8 8008E898 38600000 */  li      r3, 0
/* 0892FC 8008E89C 4E800020 */  blr     


.section .data, "wa"

.balign 8

/* 000EB7F8 800EE778 0010 */
glabel gClassAudio
    .long D_80135308, 0x00000020, 0x00000000, audioEvent

.balign 4

/* 000EB808 800EE788 001F */
D_800EE788:
    .asciz "Get: DRAM Address: WRITE-ONLY?"

.balign 4

/* 000EB828 800EE7A8 001A */
D_800EE7A8:
    .asciz "Get: CONTROL: WRITE-ONLY?"

.balign 4

/* 000EB844 800EE7C4 0054 */
jtbl_800EE7C4:
    .long lbl_8008E668
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E68C
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E6B0
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E6D4
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E6F4
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E70C
    .long lbl_8008E700

.balign 4

/* 000EB898 800EE818 0054 */
jtbl_800EE818:
    .long lbl_8008E780
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E7D8
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E810
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E820
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E834
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E870
    .long lbl_8008E860


.section .sdata, "wa"

.balign 8

/* 000F1588 80135308 0006 */
D_80135308:
    .asciz "AUDIO"

.balign 8

/* 000F1590 80135310 0008 */
D_80135310:
    .asciz "audio.c"


