glabel rspZigzagDataZ
/* 076E04 8007C3A4 9421FFC0 */  stwu    r1, -0x40(r1)
/* 076E08 8007C3A8 38000006 */  li      r0, 6
/* 076E0C 8007C3AC 7C0903A6 */  mtctr   r0
/* 076E10 8007C3B0 38A00000 */  li      r5, 0
/* 076E14 8007C3B4 BEA10014 */  stmw    r21, 0x14(r1)
lbl_8007C3B8:
/* 076E18 8007C3B8 80E339C8 */  lwz     r7, 0x39c8(r3)
/* 076E1C 8007C3BC 38C50020 */  addi    r6, r5, 0x20
/* 076E20 8007C3C0 38050004 */  addi    r0, r5, 4
/* 076E24 8007C3C4 7CE7282E */  lwzx    r7, r7, r5
/* 076E28 8007C3C8 3BE50008 */  addi    r31, r5, 8
/* 076E2C 8007C3CC 3BC50024 */  addi    r30, r5, 0x24
/* 076E30 8007C3D0 7CE70734 */  extsh   r7, r7
/* 076E34 8007C3D4 B0E40000 */  sth     r7, 0(r4)
/* 076E38 8007C3D8 3BA50040 */  addi    r29, r5, 0x40
/* 076E3C 8007C3DC 3B850060 */  addi    r28, r5, 0x60
/* 076E40 8007C3E0 80E339C8 */  lwz     r7, 0x39c8(r3)
/* 076E44 8007C3E4 3B650044 */  addi    r27, r5, 0x44
/* 076E48 8007C3E8 3B450028 */  addi    r26, r5, 0x28
/* 076E4C 8007C3EC 7CC7302E */  lwzx    r6, r7, r6
/* 076E50 8007C3F0 3B25000C */  addi    r25, r5, 0xc
/* 076E54 8007C3F4 3B050010 */  addi    r24, r5, 0x10
/* 076E58 8007C3F8 7CC60734 */  extsh   r6, r6
/* 076E5C 8007C3FC B0C40002 */  sth     r6, 2(r4)
/* 076E60 8007C400 3AE5002C */  addi    r23, r5, 0x2c
/* 076E64 8007C404 3AC50048 */  addi    r22, r5, 0x48
/* 076E68 8007C408 80C339C8 */  lwz     r6, 0x39c8(r3)
/* 076E6C 8007C40C 39850064 */  addi    r12, r5, 0x64
/* 076E70 8007C410 39650080 */  addi    r11, r5, 0x80
/* 076E74 8007C414 7C06002E */  lwzx    r0, r6, r0
/* 076E78 8007C418 394500A0 */  addi    r10, r5, 0xa0
/* 076E7C 8007C41C 39250084 */  addi    r9, r5, 0x84
/* 076E80 8007C420 7C000734 */  extsh   r0, r0
/* 076E84 8007C424 B0040004 */  sth     r0, 4(r4)
/* 076E88 8007C428 39050068 */  addi    r8, r5, 0x68
/* 076E8C 8007C42C 38E5004C */  addi    r7, r5, 0x4c
/* 076E90 8007C430 82A339C8 */  lwz     r21, 0x39c8(r3)
/* 076E94 8007C434 38C50030 */  addi    r6, r5, 0x30
/* 076E98 8007C438 38050014 */  addi    r0, r5, 0x14
/* 076E9C 8007C43C 7FF5F82E */  lwzx    r31, r21, r31
/* 076EA0 8007C440 7FFF0734 */  extsh   r31, r31
/* 076EA4 8007C444 B3E40006 */  sth     r31, 6(r4)
/* 076EA8 8007C448 83E339C8 */  lwz     r31, 0x39c8(r3)
/* 076EAC 8007C44C 7FDFF02E */  lwzx    r30, r31, r30
/* 076EB0 8007C450 7FDE0734 */  extsh   r30, r30
/* 076EB4 8007C454 B3C40008 */  sth     r30, 8(r4)
/* 076EB8 8007C458 83C339C8 */  lwz     r30, 0x39c8(r3)
/* 076EBC 8007C45C 7FBEE82E */  lwzx    r29, r30, r29
/* 076EC0 8007C460 7FBD0734 */  extsh   r29, r29
/* 076EC4 8007C464 B3A4000A */  sth     r29, 0xa(r4)
/* 076EC8 8007C468 83A339C8 */  lwz     r29, 0x39c8(r3)
/* 076ECC 8007C46C 7F9DE02E */  lwzx    r28, r29, r28
/* 076ED0 8007C470 7F9C0734 */  extsh   r28, r28
/* 076ED4 8007C474 B384000C */  sth     r28, 0xc(r4)
/* 076ED8 8007C478 838339C8 */  lwz     r28, 0x39c8(r3)
/* 076EDC 8007C47C 7F7CD82E */  lwzx    r27, r28, r27
/* 076EE0 8007C480 7F7B0734 */  extsh   r27, r27
/* 076EE4 8007C484 B364000E */  sth     r27, 0xe(r4)
/* 076EE8 8007C488 836339C8 */  lwz     r27, 0x39c8(r3)
/* 076EEC 8007C48C 7F5BD02E */  lwzx    r26, r27, r26
/* 076EF0 8007C490 7F5A0734 */  extsh   r26, r26
/* 076EF4 8007C494 B3440010 */  sth     r26, 0x10(r4)
/* 076EF8 8007C498 834339C8 */  lwz     r26, 0x39c8(r3)
/* 076EFC 8007C49C 7F3AC82E */  lwzx    r25, r26, r25
/* 076F00 8007C4A0 7F390734 */  extsh   r25, r25
/* 076F04 8007C4A4 B3240012 */  sth     r25, 0x12(r4)
/* 076F08 8007C4A8 832339C8 */  lwz     r25, 0x39c8(r3)
/* 076F0C 8007C4AC 7F19C02E */  lwzx    r24, r25, r24
/* 076F10 8007C4B0 7F180734 */  extsh   r24, r24
/* 076F14 8007C4B4 B3040014 */  sth     r24, 0x14(r4)
/* 076F18 8007C4B8 830339C8 */  lwz     r24, 0x39c8(r3)
/* 076F1C 8007C4BC 7EF8B82E */  lwzx    r23, r24, r23
/* 076F20 8007C4C0 7EF70734 */  extsh   r23, r23
/* 076F24 8007C4C4 B2E40016 */  sth     r23, 0x16(r4)
/* 076F28 8007C4C8 82E339C8 */  lwz     r23, 0x39c8(r3)
/* 076F2C 8007C4CC 7ED7B02E */  lwzx    r22, r23, r22
/* 076F30 8007C4D0 7ED60734 */  extsh   r22, r22
/* 076F34 8007C4D4 B2C40018 */  sth     r22, 0x18(r4)
/* 076F38 8007C4D8 82C339C8 */  lwz     r22, 0x39c8(r3)
/* 076F3C 8007C4DC 7D96602E */  lwzx    r12, r22, r12
/* 076F40 8007C4E0 7D8C0734 */  extsh   r12, r12
/* 076F44 8007C4E4 B184001A */  sth     r12, 0x1a(r4)
/* 076F48 8007C4E8 818339C8 */  lwz     r12, 0x39c8(r3)
/* 076F4C 8007C4EC 7D6C582E */  lwzx    r11, r12, r11
/* 076F50 8007C4F0 7D6B0734 */  extsh   r11, r11
/* 076F54 8007C4F4 B164001C */  sth     r11, 0x1c(r4)
/* 076F58 8007C4F8 816339C8 */  lwz     r11, 0x39c8(r3)
/* 076F5C 8007C4FC 7D4B502E */  lwzx    r10, r11, r10
/* 076F60 8007C500 7D4A0734 */  extsh   r10, r10
/* 076F64 8007C504 B144001E */  sth     r10, 0x1e(r4)
/* 076F68 8007C508 814339C8 */  lwz     r10, 0x39c8(r3)
/* 076F6C 8007C50C 7D2A482E */  lwzx    r9, r10, r9
/* 076F70 8007C510 7D290734 */  extsh   r9, r9
/* 076F74 8007C514 B1240020 */  sth     r9, 0x20(r4)
/* 076F78 8007C518 812339C8 */  lwz     r9, 0x39c8(r3)
/* 076F7C 8007C51C 7D09402E */  lwzx    r8, r9, r8
/* 076F80 8007C520 7D080734 */  extsh   r8, r8
/* 076F84 8007C524 B1040022 */  sth     r8, 0x22(r4)
/* 076F88 8007C528 810339C8 */  lwz     r8, 0x39c8(r3)
/* 076F8C 8007C52C 7CE8382E */  lwzx    r7, r8, r7
/* 076F90 8007C530 7CE70734 */  extsh   r7, r7
/* 076F94 8007C534 B0E40024 */  sth     r7, 0x24(r4)
/* 076F98 8007C538 80E339C8 */  lwz     r7, 0x39c8(r3)
/* 076F9C 8007C53C 7CC7302E */  lwzx    r6, r7, r6
/* 076FA0 8007C540 7CC60734 */  extsh   r6, r6
/* 076FA4 8007C544 B0C40026 */  sth     r6, 0x26(r4)
/* 076FA8 8007C548 80C339C8 */  lwz     r6, 0x39c8(r3)
/* 076FAC 8007C54C 7C06002E */  lwzx    r0, r6, r0
/* 076FB0 8007C550 7C000734 */  extsh   r0, r0
/* 076FB4 8007C554 B0040028 */  sth     r0, 0x28(r4)
/* 076FB8 8007C558 80C339C8 */  lwz     r6, 0x39c8(r3)
/* 076FBC 8007C55C 38050018 */  addi    r0, r5, 0x18
/* 076FC0 8007C560 38E50034 */  addi    r7, r5, 0x34
/* 076FC4 8007C564 7D06002E */  lwzx    r8, r6, r0
/* 076FC8 8007C568 38C50050 */  addi    r6, r5, 0x50
/* 076FCC 8007C56C 3805006C */  addi    r0, r5, 0x6c
/* 076FD0 8007C570 7D080734 */  extsh   r8, r8
/* 076FD4 8007C574 B104002A */  sth     r8, 0x2a(r4)
/* 076FD8 8007C578 3BC50088 */  addi    r30, r5, 0x88
/* 076FDC 8007C57C 3BA500A4 */  addi    r29, r5, 0xa4
/* 076FE0 8007C580 810339C8 */  lwz     r8, 0x39c8(r3)
/* 076FE4 8007C584 3B8500C0 */  addi    r28, r5, 0xc0
/* 076FE8 8007C588 3B6500E0 */  addi    r27, r5, 0xe0
/* 076FEC 8007C58C 7CE8382E */  lwzx    r7, r8, r7
/* 076FF0 8007C590 3B4500C4 */  addi    r26, r5, 0xc4
/* 076FF4 8007C594 3B2500A8 */  addi    r25, r5, 0xa8
/* 076FF8 8007C598 7CE70734 */  extsh   r7, r7
/* 076FFC 8007C59C B0E4002C */  sth     r7, 0x2c(r4)
/* 077000 8007C5A0 3B05008C */  addi    r24, r5, 0x8c
/* 077004 8007C5A4 3AE50070 */  addi    r23, r5, 0x70
/* 077008 8007C5A8 80E339C8 */  lwz     r7, 0x39c8(r3)
/* 07700C 8007C5AC 3AC50054 */  addi    r22, r5, 0x54
/* 077010 8007C5B0 39850038 */  addi    r12, r5, 0x38
/* 077014 8007C5B4 7CC7302E */  lwzx    r6, r7, r6
/* 077018 8007C5B8 3965001C */  addi    r11, r5, 0x1c
/* 07701C 8007C5BC 3945003C */  addi    r10, r5, 0x3c
/* 077020 8007C5C0 7CC60734 */  extsh   r6, r6
/* 077024 8007C5C4 B0C4002E */  sth     r6, 0x2e(r4)
/* 077028 8007C5C8 39250058 */  addi    r9, r5, 0x58
/* 07702C 8007C5CC 39050074 */  addi    r8, r5, 0x74
/* 077030 8007C5D0 83E339C8 */  lwz     r31, 0x39c8(r3)
/* 077034 8007C5D4 38E50090 */  addi    r7, r5, 0x90
/* 077038 8007C5D8 38C500AC */  addi    r6, r5, 0xac
/* 07703C 8007C5DC 7FFF002E */  lwzx    r31, r31, r0
/* 077040 8007C5E0 380500C8 */  addi    r0, r5, 0xc8
/* 077044 8007C5E4 7FFF0734 */  extsh   r31, r31
/* 077048 8007C5E8 B3E40030 */  sth     r31, 0x30(r4)
/* 07704C 8007C5EC 83E339C8 */  lwz     r31, 0x39c8(r3)
/* 077050 8007C5F0 7FDFF02E */  lwzx    r30, r31, r30
/* 077054 8007C5F4 7FDE0734 */  extsh   r30, r30
/* 077058 8007C5F8 B3C40032 */  sth     r30, 0x32(r4)
/* 07705C 8007C5FC 83C339C8 */  lwz     r30, 0x39c8(r3)
/* 077060 8007C600 7FBEE82E */  lwzx    r29, r30, r29
/* 077064 8007C604 7FBD0734 */  extsh   r29, r29
/* 077068 8007C608 B3A40034 */  sth     r29, 0x34(r4)
/* 07706C 8007C60C 83A339C8 */  lwz     r29, 0x39c8(r3)
/* 077070 8007C610 7F9DE02E */  lwzx    r28, r29, r28
/* 077074 8007C614 7F9C0734 */  extsh   r28, r28
/* 077078 8007C618 B3840036 */  sth     r28, 0x36(r4)
/* 07707C 8007C61C 838339C8 */  lwz     r28, 0x39c8(r3)
/* 077080 8007C620 7F7CD82E */  lwzx    r27, r28, r27
/* 077084 8007C624 7F7B0734 */  extsh   r27, r27
/* 077088 8007C628 B3640038 */  sth     r27, 0x38(r4)
/* 07708C 8007C62C 836339C8 */  lwz     r27, 0x39c8(r3)
/* 077090 8007C630 7F5BD02E */  lwzx    r26, r27, r26
/* 077094 8007C634 7F5A0734 */  extsh   r26, r26
/* 077098 8007C638 B344003A */  sth     r26, 0x3a(r4)
/* 07709C 8007C63C 834339C8 */  lwz     r26, 0x39c8(r3)
/* 0770A0 8007C640 7F3AC82E */  lwzx    r25, r26, r25
/* 0770A4 8007C644 7F390734 */  extsh   r25, r25
/* 0770A8 8007C648 B324003C */  sth     r25, 0x3c(r4)
/* 0770AC 8007C64C 832339C8 */  lwz     r25, 0x39c8(r3)
/* 0770B0 8007C650 7F19C02E */  lwzx    r24, r25, r24
/* 0770B4 8007C654 7F180734 */  extsh   r24, r24
/* 0770B8 8007C658 B304003E */  sth     r24, 0x3e(r4)
/* 0770BC 8007C65C 830339C8 */  lwz     r24, 0x39c8(r3)
/* 0770C0 8007C660 7EF8B82E */  lwzx    r23, r24, r23
/* 0770C4 8007C664 7EF70734 */  extsh   r23, r23
/* 0770C8 8007C668 B2E40040 */  sth     r23, 0x40(r4)
/* 0770CC 8007C66C 82E339C8 */  lwz     r23, 0x39c8(r3)
/* 0770D0 8007C670 7ED7B02E */  lwzx    r22, r23, r22
/* 0770D4 8007C674 7ED60734 */  extsh   r22, r22
/* 0770D8 8007C678 B2C40042 */  sth     r22, 0x42(r4)
/* 0770DC 8007C67C 82C339C8 */  lwz     r22, 0x39c8(r3)
/* 0770E0 8007C680 7D96602E */  lwzx    r12, r22, r12
/* 0770E4 8007C684 7D8C0734 */  extsh   r12, r12
/* 0770E8 8007C688 B1840044 */  sth     r12, 0x44(r4)
/* 0770EC 8007C68C 818339C8 */  lwz     r12, 0x39c8(r3)
/* 0770F0 8007C690 7D6C582E */  lwzx    r11, r12, r11
/* 0770F4 8007C694 7D6B0734 */  extsh   r11, r11
/* 0770F8 8007C698 B1640046 */  sth     r11, 0x46(r4)
/* 0770FC 8007C69C 816339C8 */  lwz     r11, 0x39c8(r3)
/* 077100 8007C6A0 7D4B502E */  lwzx    r10, r11, r10
/* 077104 8007C6A4 7D4A0734 */  extsh   r10, r10
/* 077108 8007C6A8 B1440048 */  sth     r10, 0x48(r4)
/* 07710C 8007C6AC 814339C8 */  lwz     r10, 0x39c8(r3)
/* 077110 8007C6B0 7D2A482E */  lwzx    r9, r10, r9
/* 077114 8007C6B4 7D290734 */  extsh   r9, r9
/* 077118 8007C6B8 B124004A */  sth     r9, 0x4a(r4)
/* 07711C 8007C6BC 812339C8 */  lwz     r9, 0x39c8(r3)
/* 077120 8007C6C0 7D09402E */  lwzx    r8, r9, r8
/* 077124 8007C6C4 7D080734 */  extsh   r8, r8
/* 077128 8007C6C8 B104004C */  sth     r8, 0x4c(r4)
/* 07712C 8007C6CC 810339C8 */  lwz     r8, 0x39c8(r3)
/* 077130 8007C6D0 7CE8382E */  lwzx    r7, r8, r7
/* 077134 8007C6D4 7CE70734 */  extsh   r7, r7
/* 077138 8007C6D8 B0E4004E */  sth     r7, 0x4e(r4)
/* 07713C 8007C6DC 80E339C8 */  lwz     r7, 0x39c8(r3)
/* 077140 8007C6E0 7CC7302E */  lwzx    r6, r7, r6
/* 077144 8007C6E4 7CC60734 */  extsh   r6, r6
/* 077148 8007C6E8 B0C40050 */  sth     r6, 0x50(r4)
/* 07714C 8007C6EC 80C339C8 */  lwz     r6, 0x39c8(r3)
/* 077150 8007C6F0 7C06002E */  lwzx    r0, r6, r0
/* 077154 8007C6F4 7C000734 */  extsh   r0, r0
/* 077158 8007C6F8 B0040052 */  sth     r0, 0x52(r4)
/* 07715C 8007C6FC 80C339C8 */  lwz     r6, 0x39c8(r3)
/* 077160 8007C700 380500E4 */  addi    r0, r5, 0xe4
/* 077164 8007C704 38E500E8 */  addi    r7, r5, 0xe8
/* 077168 8007C708 7D06002E */  lwzx    r8, r6, r0
/* 07716C 8007C70C 38C500CC */  addi    r6, r5, 0xcc
/* 077170 8007C710 380500B0 */  addi    r0, r5, 0xb0
/* 077174 8007C714 7D080734 */  extsh   r8, r8
/* 077178 8007C718 B1040054 */  sth     r8, 0x54(r4)
/* 07717C 8007C71C 3AE50094 */  addi    r23, r5, 0x94
/* 077180 8007C720 3B050078 */  addi    r24, r5, 0x78
/* 077184 8007C724 810339C8 */  lwz     r8, 0x39c8(r3)
/* 077188 8007C728 3B25005C */  addi    r25, r5, 0x5c
/* 07718C 8007C72C 3B45007C */  addi    r26, r5, 0x7c
/* 077190 8007C730 7CE8382E */  lwzx    r7, r8, r7
/* 077194 8007C734 3B650098 */  addi    r27, r5, 0x98
/* 077198 8007C738 3B8500B4 */  addi    r28, r5, 0xb4
/* 07719C 8007C73C 7CE70734 */  extsh   r7, r7
/* 0771A0 8007C740 B0E40056 */  sth     r7, 0x56(r4)
/* 0771A4 8007C744 3BA500D0 */  addi    r29, r5, 0xd0
/* 0771A8 8007C748 3BC500EC */  addi    r30, r5, 0xec
/* 0771AC 8007C74C 80E339C8 */  lwz     r7, 0x39c8(r3)
/* 0771B0 8007C750 3BE500F0 */  addi    r31, r5, 0xf0
/* 0771B4 8007C754 398500D4 */  addi    r12, r5, 0xd4
/* 0771B8 8007C758 7CC7302E */  lwzx    r6, r7, r6
/* 0771BC 8007C75C 396500B8 */  addi    r11, r5, 0xb8
/* 0771C0 8007C760 3945009C */  addi    r10, r5, 0x9c
/* 0771C4 8007C764 7CC60734 */  extsh   r6, r6
/* 0771C8 8007C768 B0C40058 */  sth     r6, 0x58(r4)
/* 0771CC 8007C76C 392500BC */  addi    r9, r5, 0xbc
/* 0771D0 8007C770 390500D8 */  addi    r8, r5, 0xd8
/* 0771D4 8007C774 82C339C8 */  lwz     r22, 0x39c8(r3)
/* 0771D8 8007C778 38E500F4 */  addi    r7, r5, 0xf4
/* 0771DC 8007C77C 38C500F8 */  addi    r6, r5, 0xf8
/* 0771E0 8007C780 7ED6002E */  lwzx    r22, r22, r0
/* 0771E4 8007C784 380500DC */  addi    r0, r5, 0xdc
/* 0771E8 8007C788 7ED60734 */  extsh   r22, r22
/* 0771EC 8007C78C B2C4005A */  sth     r22, 0x5a(r4)
/* 0771F0 8007C790 82C339C8 */  lwz     r22, 0x39c8(r3)
/* 0771F4 8007C794 7EF6B82E */  lwzx    r23, r22, r23
/* 0771F8 8007C798 7EF70734 */  extsh   r23, r23
/* 0771FC 8007C79C B2E4005C */  sth     r23, 0x5c(r4)
/* 077200 8007C7A0 82E339C8 */  lwz     r23, 0x39c8(r3)
/* 077204 8007C7A4 7F17C02E */  lwzx    r24, r23, r24
/* 077208 8007C7A8 7F180734 */  extsh   r24, r24
/* 07720C 8007C7AC B304005E */  sth     r24, 0x5e(r4)
/* 077210 8007C7B0 830339C8 */  lwz     r24, 0x39c8(r3)
/* 077214 8007C7B4 7F38C82E */  lwzx    r25, r24, r25
/* 077218 8007C7B8 7F390734 */  extsh   r25, r25
/* 07721C 8007C7BC B3240060 */  sth     r25, 0x60(r4)
/* 077220 8007C7C0 832339C8 */  lwz     r25, 0x39c8(r3)
/* 077224 8007C7C4 7F59D02E */  lwzx    r26, r25, r26
/* 077228 8007C7C8 7F5A0734 */  extsh   r26, r26
/* 07722C 8007C7CC B3440062 */  sth     r26, 0x62(r4)
/* 077230 8007C7D0 834339C8 */  lwz     r26, 0x39c8(r3)
/* 077234 8007C7D4 7F7AD82E */  lwzx    r27, r26, r27
/* 077238 8007C7D8 7F7B0734 */  extsh   r27, r27
/* 07723C 8007C7DC B3640064 */  sth     r27, 0x64(r4)
/* 077240 8007C7E0 836339C8 */  lwz     r27, 0x39c8(r3)
/* 077244 8007C7E4 7F9BE02E */  lwzx    r28, r27, r28
/* 077248 8007C7E8 7F9C0734 */  extsh   r28, r28
/* 07724C 8007C7EC B3840066 */  sth     r28, 0x66(r4)
/* 077250 8007C7F0 838339C8 */  lwz     r28, 0x39c8(r3)
/* 077254 8007C7F4 7FBCE82E */  lwzx    r29, r28, r29
/* 077258 8007C7F8 7FBD0734 */  extsh   r29, r29
/* 07725C 8007C7FC B3A40068 */  sth     r29, 0x68(r4)
/* 077260 8007C800 83A339C8 */  lwz     r29, 0x39c8(r3)
/* 077264 8007C804 7FDDF02E */  lwzx    r30, r29, r30
/* 077268 8007C808 7FDE0734 */  extsh   r30, r30
/* 07726C 8007C80C B3C4006A */  sth     r30, 0x6a(r4)
/* 077270 8007C810 83C339C8 */  lwz     r30, 0x39c8(r3)
/* 077274 8007C814 7FFEF82E */  lwzx    r31, r30, r31
/* 077278 8007C818 7FFF0734 */  extsh   r31, r31
/* 07727C 8007C81C B3E4006C */  sth     r31, 0x6c(r4)
/* 077280 8007C820 83E339C8 */  lwz     r31, 0x39c8(r3)
/* 077284 8007C824 7D9F602E */  lwzx    r12, r31, r12
/* 077288 8007C828 7D8C0734 */  extsh   r12, r12
/* 07728C 8007C82C B184006E */  sth     r12, 0x6e(r4)
/* 077290 8007C830 818339C8 */  lwz     r12, 0x39c8(r3)
/* 077294 8007C834 7D6C582E */  lwzx    r11, r12, r11
/* 077298 8007C838 7D6B0734 */  extsh   r11, r11
/* 07729C 8007C83C B1640070 */  sth     r11, 0x70(r4)
/* 0772A0 8007C840 816339C8 */  lwz     r11, 0x39c8(r3)
/* 0772A4 8007C844 7D4B502E */  lwzx    r10, r11, r10
/* 0772A8 8007C848 7D4A0734 */  extsh   r10, r10
/* 0772AC 8007C84C B1440072 */  sth     r10, 0x72(r4)
/* 0772B0 8007C850 814339C8 */  lwz     r10, 0x39c8(r3)
/* 0772B4 8007C854 7D2A482E */  lwzx    r9, r10, r9
/* 0772B8 8007C858 7D290734 */  extsh   r9, r9
/* 0772BC 8007C85C B1240074 */  sth     r9, 0x74(r4)
/* 0772C0 8007C860 812339C8 */  lwz     r9, 0x39c8(r3)
/* 0772C4 8007C864 7D09402E */  lwzx    r8, r9, r8
/* 0772C8 8007C868 7D080734 */  extsh   r8, r8
/* 0772CC 8007C86C B1040076 */  sth     r8, 0x76(r4)
/* 0772D0 8007C870 810339C8 */  lwz     r8, 0x39c8(r3)
/* 0772D4 8007C874 7CE8382E */  lwzx    r7, r8, r7
/* 0772D8 8007C878 7CE70734 */  extsh   r7, r7
/* 0772DC 8007C87C B0E40078 */  sth     r7, 0x78(r4)
/* 0772E0 8007C880 80E339C8 */  lwz     r7, 0x39c8(r3)
/* 0772E4 8007C884 7CC7302E */  lwzx    r6, r7, r6
/* 0772E8 8007C888 7CC60734 */  extsh   r6, r6
/* 0772EC 8007C88C B0C4007A */  sth     r6, 0x7a(r4)
/* 0772F0 8007C890 80C339C8 */  lwz     r6, 0x39c8(r3)
/* 0772F4 8007C894 7C06002E */  lwzx    r0, r6, r0
/* 0772F8 8007C898 7C000734 */  extsh   r0, r0
/* 0772FC 8007C89C B004007C */  sth     r0, 0x7c(r4)
/* 077300 8007C8A0 80C339C8 */  lwz     r6, 0x39c8(r3)
/* 077304 8007C8A4 380500FC */  addi    r0, r5, 0xfc
/* 077308 8007C8A8 38A50100 */  addi    r5, r5, 0x100
/* 07730C 8007C8AC 7C06002E */  lwzx    r0, r6, r0
/* 077310 8007C8B0 7C000734 */  extsh   r0, r0
/* 077314 8007C8B4 B004007E */  sth     r0, 0x7e(r4)
/* 077318 8007C8B8 38840080 */  addi    r4, r4, 0x80
/* 07731C 8007C8BC 4200FAFC */  bdnz    lbl_8007C3B8
/* 077320 8007C8C0 BAA10014 */  lmw     r21, 0x14(r1)
/* 077324 8007C8C4 38210040 */  addi    r1, r1, 0x40
/* 077328 8007C8C8 4E800020 */  blr     
