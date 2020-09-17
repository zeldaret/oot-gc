# disk.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel diskEvent
/* 0881E8 8008D788 7C0802A6 */  mflr    r0
/* 0881EC 8008D78C 2C040003 */  cmpwi   r4, 3
/* 0881F0 8008D790 90010004 */  stw     r0, 4(r1)
/* 0881F4 8008D794 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0881F8 8008D798 93E1001C */  stw     r31, 0x1c(r1)
/* 0881FC 8008D79C 3BE50000 */  addi    r31, r5, 0
/* 088200 8008D7A0 93C10018 */  stw     r30, 0x18(r1)
/* 088204 8008D7A4 3BC30000 */  addi    r30, r3, 0
/* 088208 8008D7A8 41820160 */  beq     lbl_8008D908
/* 08820C 8008D7AC 40800018 */  bge     lbl_8008D7C4
/* 088210 8008D7B0 2C040002 */  cmpwi   r4, 2
/* 088214 8008D7B4 40800028 */  bge     lbl_8008D7DC
/* 088218 8008D7B8 2C040000 */  cmpwi   r4, 0
/* 08821C 8008D7BC 4080014C */  bge     lbl_8008D908
/* 088220 8008D7C0 48000140 */  b       lbl_8008D900
lbl_8008D7C4:
/* 088224 8008D7C4 2C041003 */  cmpwi   r4, 0x1003
/* 088228 8008D7C8 41820140 */  beq     lbl_8008D908
/* 08822C 8008D7CC 40800134 */  bge     lbl_8008D900
/* 088230 8008D7D0 2C041002 */  cmpwi   r4, 0x1002
/* 088234 8008D7D4 40800010 */  bge     lbl_8008D7E4
/* 088238 8008D7D8 48000128 */  b       lbl_8008D900
lbl_8008D7DC:
/* 08823C 8008D7DC 93FE0000 */  stw     r31, 0(r30)
/* 088240 8008D7E0 48000128 */  b       lbl_8008D908
lbl_8008D7E4:
/* 088244 8008D7E4 801F0000 */  lwz     r0, 0(r31)
/* 088248 8008D7E8 2C000001 */  cmpwi   r0, 1
/* 08824C 8008D7EC 41820094 */  beq     lbl_8008D880
/* 088250 8008D7F0 40800118 */  bge     lbl_8008D908
/* 088254 8008D7F4 2C000000 */  cmpwi   r0, 0
/* 088258 8008D7F8 40800008 */  bge     lbl_8008D800
/* 08825C 8008D7FC 4800010C */  b       lbl_8008D908
lbl_8008D800:
/* 088260 8008D800 807E0000 */  lwz     r3, 0(r30)
/* 088264 8008D804 3CA08009 */  lis     r5, diskPutDrive8@ha
/* 088268 8008D808 3CC08009 */  lis     r6, diskPutDrive16@ha
/* 08826C 8008D80C 3CE08009 */  lis     r7, diskPutDrive32@ha
/* 088270 8008D810 80630024 */  lwz     r3, 0x24(r3)
/* 088274 8008D814 3C808009 */  lis     r4, diskPutDrive64@ha
/* 088278 8008D818 3904D974 */  addi    r8, r4, diskPutDrive64@l
/* 08827C 8008D81C 38A5D9B0 */  addi    r5, r5, diskPutDrive8@l
/* 088280 8008D820 38C6D9A8 */  addi    r6, r6, diskPutDrive16@l
/* 088284 8008D824 38E7D97C */  addi    r7, r7, diskPutDrive32@l
/* 088288 8008D828 389F0000 */  addi    r4, r31, 0
/* 08828C 8008D82C 4BFA780D */  bl      cpuSetDevicePut
/* 088290 8008D830 2C030000 */  cmpwi   r3, 0
/* 088294 8008D834 4082000C */  bne     lbl_8008D840
/* 088298 8008D838 38600000 */  li      r3, 0
/* 08829C 8008D83C 480000D0 */  b       lbl_8008D90C
lbl_8008D840:
/* 0882A0 8008D840 807E0000 */  lwz     r3, 0(r30)
/* 0882A4 8008D844 3CA08009 */  lis     r5, diskGetDrive8@ha
/* 0882A8 8008D848 3CC08009 */  lis     r6, diskGetDrive16@ha
/* 0882AC 8008D84C 3CE08009 */  lis     r7, diskGetDrive32@ha
/* 0882B0 8008D850 80630024 */  lwz     r3, 0x24(r3)
/* 0882B4 8008D854 3C808009 */  lis     r4, diskGetDrive64@ha
/* 0882B8 8008D858 3904D924 */  addi    r8, r4, diskGetDrive64@l
/* 0882BC 8008D85C 38A5D96C */  addi    r5, r5, diskGetDrive8@l
/* 0882C0 8008D860 38C6D964 */  addi    r6, r6, diskGetDrive16@l
/* 0882C4 8008D864 38E7D92C */  addi    r7, r7, diskGetDrive32@l
/* 0882C8 8008D868 389F0000 */  addi    r4, r31, 0
/* 0882CC 8008D86C 4BFA77E5 */  bl      cpuSetDeviceGet
/* 0882D0 8008D870 2C030000 */  cmpwi   r3, 0
/* 0882D4 8008D874 40820094 */  bne     lbl_8008D908
/* 0882D8 8008D878 38600000 */  li      r3, 0
/* 0882DC 8008D87C 48000090 */  b       lbl_8008D90C
lbl_8008D880:
/* 0882E0 8008D880 807E0000 */  lwz     r3, 0(r30)
/* 0882E4 8008D884 3CA08009 */  lis     r5, diskPutROM8@ha
/* 0882E8 8008D888 3CC08009 */  lis     r6, diskPutROM16@ha
/* 0882EC 8008D88C 3CE08009 */  lis     r7, diskPutROM32@ha
/* 0882F0 8008D890 80630024 */  lwz     r3, 0x24(r3)
/* 0882F4 8008D894 3C808009 */  lis     r4, diskPutROM64@ha
/* 0882F8 8008D898 3904D9FC */  addi    r8, r4, diskPutROM64@l
/* 0882FC 8008D89C 38A5DA14 */  addi    r5, r5, diskPutROM8@l
/* 088300 8008D8A0 38C6DA0C */  addi    r6, r6, diskPutROM16@l
/* 088304 8008D8A4 38E7DA04 */  addi    r7, r7, diskPutROM32@l
/* 088308 8008D8A8 389F0000 */  addi    r4, r31, 0
/* 08830C 8008D8AC 4BFA778D */  bl      cpuSetDevicePut
/* 088310 8008D8B0 2C030000 */  cmpwi   r3, 0
/* 088314 8008D8B4 4082000C */  bne     lbl_8008D8C0
/* 088318 8008D8B8 38600000 */  li      r3, 0
/* 08831C 8008D8BC 48000050 */  b       lbl_8008D90C
lbl_8008D8C0:
/* 088320 8008D8C0 807E0000 */  lwz     r3, 0(r30)
/* 088324 8008D8C4 3CA08009 */  lis     r5, diskGetROM8@ha
/* 088328 8008D8C8 3CC08009 */  lis     r6, diskGetROM16@ha
/* 08832C 8008D8CC 3CE08009 */  lis     r7, diskGetROM32@ha
/* 088330 8008D8D0 80630024 */  lwz     r3, 0x24(r3)
/* 088334 8008D8D4 3C808009 */  lis     r4, diskGetROM64@ha
/* 088338 8008D8D8 3904D9B8 */  addi    r8, r4, diskGetROM64@l
/* 08833C 8008D8DC 38A5D9EC */  addi    r5, r5, diskGetROM8@l
/* 088340 8008D8E0 38C6D9DC */  addi    r6, r6, diskGetROM16@l
/* 088344 8008D8E4 38E7D9CC */  addi    r7, r7, diskGetROM32@l
/* 088348 8008D8E8 389F0000 */  addi    r4, r31, 0
/* 08834C 8008D8EC 4BFA7765 */  bl      cpuSetDeviceGet
/* 088350 8008D8F0 2C030000 */  cmpwi   r3, 0
/* 088354 8008D8F4 40820014 */  bne     lbl_8008D908
/* 088358 8008D8F8 38600000 */  li      r3, 0
/* 08835C 8008D8FC 48000010 */  b       lbl_8008D90C
lbl_8008D900:
/* 088360 8008D900 38600000 */  li      r3, 0
/* 088364 8008D904 48000008 */  b       lbl_8008D90C
lbl_8008D908:
/* 088368 8008D908 38600001 */  li      r3, 1
lbl_8008D90C:
/* 08836C 8008D90C 80010024 */  lwz     r0, 0x24(r1)
/* 088370 8008D910 83E1001C */  lwz     r31, 0x1c(r1)
/* 088374 8008D914 83C10018 */  lwz     r30, 0x18(r1)
/* 088378 8008D918 7C0803A6 */  mtlr    r0
/* 08837C 8008D91C 38210020 */  addi    r1, r1, 0x20
/* 088380 8008D920 4E800020 */  blr     

diskGetDrive64:
/* 088384 8008D924 38600001 */  li      r3, 1
/* 088388 8008D928 4E800020 */  blr     

diskGetDrive32:
/* 08838C 8008D92C 5480023E */  clrlwi  r0, r4, 8
/* 088390 8008D930 2C000510 */  cmpwi   r0, 0x510
/* 088394 8008D934 41820020 */  beq     lbl_8008D954
/* 088398 8008D938 40800024 */  bge     lbl_8008D95C
/* 08839C 8008D93C 2C000508 */  cmpwi   r0, 0x508
/* 0883A0 8008D940 41820008 */  beq     lbl_8008D948
/* 0883A4 8008D944 48000018 */  b       lbl_8008D95C
lbl_8008D948:
/* 0883A8 8008D948 38000000 */  li      r0, 0
/* 0883AC 8008D94C 90050000 */  stw     r0, 0(r5)
/* 0883B0 8008D950 4800000C */  b       lbl_8008D95C
lbl_8008D954:
/* 0883B4 8008D954 38600000 */  li      r3, 0
/* 0883B8 8008D958 4E800020 */  blr     
lbl_8008D95C:
/* 0883BC 8008D95C 38600001 */  li      r3, 1
/* 0883C0 8008D960 4E800020 */  blr     

diskGetDrive16:
/* 0883C4 8008D964 38600001 */  li      r3, 1
/* 0883C8 8008D968 4E800020 */  blr     

diskGetDrive8:
/* 0883CC 8008D96C 38600001 */  li      r3, 1
/* 0883D0 8008D970 4E800020 */  blr     

diskPutDrive64:
/* 0883D4 8008D974 38600001 */  li      r3, 1
/* 0883D8 8008D978 4E800020 */  blr     

diskPutDrive32:
/* 0883DC 8008D97C 5480023E */  clrlwi  r0, r4, 8
/* 0883E0 8008D980 2C000510 */  cmpwi   r0, 0x510
/* 0883E4 8008D984 4182001C */  beq     lbl_8008D9A0
/* 0883E8 8008D988 40800018 */  bge     lbl_8008D9A0
/* 0883EC 8008D98C 2C000508 */  cmpwi   r0, 0x508
/* 0883F0 8008D990 41820008 */  beq     lbl_8008D998
/* 0883F4 8008D994 4800000C */  b       lbl_8008D9A0
lbl_8008D998:
/* 0883F8 8008D998 38600000 */  li      r3, 0
/* 0883FC 8008D99C 4E800020 */  blr     
lbl_8008D9A0:
/* 088400 8008D9A0 38600001 */  li      r3, 1
/* 088404 8008D9A4 4E800020 */  blr     

diskPutDrive16:
/* 088408 8008D9A8 38600001 */  li      r3, 1
/* 08840C 8008D9AC 4E800020 */  blr     

diskPutDrive8:
/* 088410 8008D9B0 38600001 */  li      r3, 1
/* 088414 8008D9B4 4E800020 */  blr     

diskGetROM64:
/* 088418 8008D9B8 38000000 */  li      r0, 0
/* 08841C 8008D9BC 90050004 */  stw     r0, 4(r5)
/* 088420 8008D9C0 38600001 */  li      r3, 1
/* 088424 8008D9C4 90050000 */  stw     r0, 0(r5)
/* 088428 8008D9C8 4E800020 */  blr     

diskGetROM32:
/* 08842C 8008D9CC 38000000 */  li      r0, 0
/* 088430 8008D9D0 90050000 */  stw     r0, 0(r5)
/* 088434 8008D9D4 38600001 */  li      r3, 1
/* 088438 8008D9D8 4E800020 */  blr     

diskGetROM16:
/* 08843C 8008D9DC 38000000 */  li      r0, 0
/* 088440 8008D9E0 B0050000 */  sth     r0, 0(r5)
/* 088444 8008D9E4 38600001 */  li      r3, 1
/* 088448 8008D9E8 4E800020 */  blr     

diskGetROM8:
/* 08844C 8008D9EC 38000000 */  li      r0, 0
/* 088450 8008D9F0 98050000 */  stb     r0, 0(r5)
/* 088454 8008D9F4 38600001 */  li      r3, 1
/* 088458 8008D9F8 4E800020 */  blr     

diskPutROM64:
/* 08845C 8008D9FC 38600001 */  li      r3, 1
/* 088460 8008DA00 4E800020 */  blr     

diskPutROM32:
/* 088464 8008DA04 38600001 */  li      r3, 1
/* 088468 8008DA08 4E800020 */  blr     

diskPutROM16:
/* 08846C 8008DA0C 38600001 */  li      r3, 1
/* 088470 8008DA10 4E800020 */  blr     

diskPutROM8:
/* 088474 8008DA14 38600001 */  li      r3, 1
/* 088478 8008DA18 4E800020 */  blr     


.section .data, "wa"

.balign 8

/* 000EB7C8 800EE748 0010 */
glabel gClassDisk
    .long D_801352F0, 0x00000004, 0x00000000, diskEvent


.section .sdata, "wa"

.balign 8

/* 000F1570 801352F0 0005 */
D_801352F0:
    .asciz "DISK"


