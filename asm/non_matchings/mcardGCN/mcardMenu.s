glabel mcardMenu
/* 0118D0 80016E70 7C0802A6 */  mflr    r0
/* 0118D4 80016E74 90010004 */  stw     r0, 4(r1)
/* 0118D8 80016E78 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0118DC 80016E7C 93E10024 */  stw     r31, 0x24(r1)
/* 0118E0 80016E80 93C10020 */  stw     r30, 0x20(r1)
/* 0118E4 80016E84 3BC50000 */  addi    r30, r5, 0
/* 0118E8 80016E88 93A1001C */  stw     r29, 0x1c(r1)
/* 0118EC 80016E8C 7C7D1B78 */  mr      r29, r3
/* 0118F0 80016E90 800307AC */  lwz     r0, 0x7ac(r3)
/* 0118F4 80016E94 2C000001 */  cmpwi   r0, 1
/* 0118F8 80016E98 4082001C */  bne     lbl_80016EB4
/* 0118FC 80016E9C 2C040001 */  cmpwi   r4, 1
/* 011900 80016EA0 41820014 */  beq     lbl_80016EB4
/* 011904 80016EA4 2C04000C */  cmpwi   r4, 0xc
/* 011908 80016EA8 4182000C */  beq     lbl_80016EB4
/* 01190C 80016EAC 808D898C */  lwz     r4, nextMenuEntry@sda21(r13)
/* 011910 80016EB0 48000020 */  b       lbl_80016ED0
lbl_80016EB4:
/* 011914 80016EB4 38000000 */  li      r0, 0
/* 011918 80016EB8 901D07AC */  stw     r0, 0x7ac(r29)
/* 01191C 80016EBC 800D8988 */  lwz     r0, prevMenuEntry@sda21(r13)
/* 011920 80016EC0 7C040000 */  cmpw    r4, r0
/* 011924 80016EC4 40820008 */  bne     lbl_80016ECC
/* 011928 80016EC8 808D898C */  lwz     r4, nextMenuEntry@sda21(r13)
lbl_80016ECC:
/* 01192C 80016ECC 908D898C */  stw     r4, nextMenuEntry@sda21(r13)
lbl_80016ED0:
/* 011930 80016ED0 3BE00001 */  li      r31, 1
/* 011934 80016ED4 28040031 */  cmplwi  r4, 0x31
/* 011938 80016ED8 93FE0000 */  stw     r31, 0(r30)
/* 01193C 80016EDC 41810910 */  bgt     lbl_800177EC
/* 011940 80016EE0 3C60800F */  lis     r3, jtbl_800EA668@ha
/* 011944 80016EE4 3863A668 */  addi    r3, r3, jtbl_800EA668@l
/* 011948 80016EE8 5480103A */  slwi    r0, r4, 2
/* 01194C 80016EEC 7C03002E */  lwzx    r0, r3, r0
/* 011950 80016EF0 7C0903A6 */  mtctr   r0
/* 011954 80016EF4 4E800420 */  bctr    
glabel lbl_80016EF8
/* 011958 80016EF8 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 01195C 80016EFC 38600007 */  li      r3, 7
/* 011960 80016F00 4BFF2B31 */  bl      simulatorDrawErrorMessageWait
/* 011964 80016F04 2C030001 */  cmpwi   r3, 1
/* 011968 80016F08 408208EC */  bne     lbl_800177F4
/* 01196C 80016F0C 38600000 */  li      r3, 0
/* 011970 80016F10 3800000B */  li      r0, 0xb
/* 011974 80016F14 906D8984 */  stw     r3, yes@sda21(r13)
/* 011978 80016F18 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 01197C 80016F1C 93FE0000 */  stw     r31, 0(r30)
/* 011980 80016F20 480008D4 */  b       lbl_800177F4
glabel lbl_80016F24
/* 011984 80016F24 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011988 80016F28 38600008 */  li      r3, 8
/* 01198C 80016F2C 4BFF2B05 */  bl      simulatorDrawErrorMessageWait
/* 011990 80016F30 2C030001 */  cmpwi   r3, 1
/* 011994 80016F34 408208C0 */  bne     lbl_800177F4
/* 011998 80016F38 38600000 */  li      r3, 0
/* 01199C 80016F3C 3800000B */  li      r0, 0xb
/* 0119A0 80016F40 906D8984 */  stw     r3, yes@sda21(r13)
/* 0119A4 80016F44 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 0119A8 80016F48 93FD07B0 */  stw     r31, 0x7b0(r29)
/* 0119AC 80016F4C 93FE0000 */  stw     r31, 0(r30)
/* 0119B0 80016F50 480008A4 */  b       lbl_800177F4
glabel lbl_80016F54
/* 0119B4 80016F54 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 0119B8 80016F58 38600009 */  li      r3, 9
/* 0119BC 80016F5C 4BFF2AD5 */  bl      simulatorDrawErrorMessageWait
/* 0119C0 80016F60 2C030001 */  cmpwi   r3, 1
/* 0119C4 80016F64 40820890 */  bne     lbl_800177F4
/* 0119C8 80016F68 38600000 */  li      r3, 0
/* 0119CC 80016F6C 3800000B */  li      r0, 0xb
/* 0119D0 80016F70 906D8984 */  stw     r3, yes@sda21(r13)
/* 0119D4 80016F74 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 0119D8 80016F78 93FE0000 */  stw     r31, 0(r30)
/* 0119DC 80016F7C 48000878 */  b       lbl_800177F4
glabel lbl_80016F80
/* 0119E0 80016F80 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 0119E4 80016F84 3860000A */  li      r3, 0xa
/* 0119E8 80016F88 4BFF2AA9 */  bl      simulatorDrawErrorMessageWait
/* 0119EC 80016F8C 2C030001 */  cmpwi   r3, 1
/* 0119F0 80016F90 40820864 */  bne     lbl_800177F4
/* 0119F4 80016F94 38600000 */  li      r3, 0
/* 0119F8 80016F98 3800000B */  li      r0, 0xb
/* 0119FC 80016F9C 906D8984 */  stw     r3, yes@sda21(r13)
/* 011A00 80016FA0 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011A04 80016FA4 93FE0000 */  stw     r31, 0(r30)
/* 011A08 80016FA8 4800084C */  b       lbl_800177F4
glabel lbl_80016FAC
/* 011A0C 80016FAC 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011A10 80016FB0 3860000B */  li      r3, 0xb
/* 011A14 80016FB4 4BFF2A7D */  bl      simulatorDrawErrorMessageWait
/* 011A18 80016FB8 2C030001 */  cmpwi   r3, 1
/* 011A1C 80016FBC 40820838 */  bne     lbl_800177F4
/* 011A20 80016FC0 38600000 */  li      r3, 0
/* 011A24 80016FC4 38000006 */  li      r0, 6
/* 011A28 80016FC8 906D8984 */  stw     r3, yes@sda21(r13)
/* 011A2C 80016FCC 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011A30 80016FD0 93FE0000 */  stw     r31, 0(r30)
/* 011A34 80016FD4 48000820 */  b       lbl_800177F4
glabel lbl_80016FD8
/* 011A38 80016FD8 3860000C */  li      r3, 0xc
/* 011A3C 80016FDC 388D8984 */  addi    r4, r13, yes@sda21
/* 011A40 80016FE0 4BFF5B9D */  bl      simulatorDrawYesNoMessage
/* 011A44 80016FE4 2C030001 */  cmpwi   r3, 1
/* 011A48 80016FE8 4082080C */  bne     lbl_800177F4
/* 011A4C 80016FEC 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011A50 80016FF0 2C000001 */  cmpwi   r0, 1
/* 011A54 80016FF4 4082001C */  bne     lbl_80017010
/* 011A58 80016FF8 38600000 */  li      r3, 0
/* 011A5C 80016FFC 38000021 */  li      r0, 0x21
/* 011A60 80017000 906D8984 */  stw     r3, yes@sda21(r13)
/* 011A64 80017004 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011A68 80017008 93FE0000 */  stw     r31, 0(r30)
/* 011A6C 8001700C 480007E8 */  b       lbl_800177F4
lbl_80017010:
/* 011A70 80017010 38000027 */  li      r0, 0x27
/* 011A74 80017014 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011A78 80017018 93FE0000 */  stw     r31, 0(r30)
/* 011A7C 8001701C 480007D8 */  b       lbl_800177F4
glabel lbl_80017020
/* 011A80 80017020 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011A84 80017024 3860000D */  li      r3, 0xd
/* 011A88 80017028 4BFF2A09 */  bl      simulatorDrawErrorMessageWait
/* 011A8C 8001702C 2C030001 */  cmpwi   r3, 1
/* 011A90 80017030 40820014 */  bne     lbl_80017044
/* 011A94 80017034 38000008 */  li      r0, 8
/* 011A98 80017038 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011A9C 8001703C 93FE0000 */  stw     r31, 0(r30)
/* 011AA0 80017040 480007B4 */  b       lbl_800177F4
lbl_80017044:
/* 011AA4 80017044 38000007 */  li      r0, 7
/* 011AA8 80017048 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011AAC 8001704C 93FE0000 */  stw     r31, 0(r30)
/* 011AB0 80017050 480007A4 */  b       lbl_800177F4
glabel lbl_80017054
/* 011AB4 80017054 3860000E */  li      r3, 0xe
/* 011AB8 80017058 4BFF29D9 */  bl      simulatorDrawErrorMessageWait
/* 011ABC 8001705C 2C030001 */  cmpwi   r3, 1
/* 011AC0 80017060 40820794 */  bne     lbl_800177F4
/* 011AC4 80017064 38000009 */  li      r0, 9
/* 011AC8 80017068 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011ACC 8001706C 93FE0000 */  stw     r31, 0(r30)
/* 011AD0 80017070 48000784 */  b       lbl_800177F4
glabel lbl_80017074
/* 011AD4 80017074 3860000F */  li      r3, 0xf
/* 011AD8 80017078 4BFF29B9 */  bl      simulatorDrawErrorMessageWait
/* 011ADC 8001707C 2C030001 */  cmpwi   r3, 1
/* 011AE0 80017080 40820774 */  bne     lbl_800177F4
/* 011AE4 80017084 38600000 */  li      r3, 0
/* 011AE8 80017088 3800000A */  li      r0, 0xa
/* 011AEC 8001708C 906D8984 */  stw     r3, yes@sda21(r13)
/* 011AF0 80017090 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011AF4 80017094 93FE0000 */  stw     r31, 0(r30)
/* 011AF8 80017098 4800075C */  b       lbl_800177F4
glabel lbl_8001709C
/* 011AFC 8001709C 38600010 */  li      r3, 0x10
/* 011B00 800170A0 388D8984 */  addi    r4, r13, yes@sda21
/* 011B04 800170A4 4BFF5AD9 */  bl      simulatorDrawYesNoMessage
/* 011B08 800170A8 2C030001 */  cmpwi   r3, 1
/* 011B0C 800170AC 40820748 */  bne     lbl_800177F4
/* 011B10 800170B0 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011B14 800170B4 2C000001 */  cmpwi   r0, 1
/* 011B18 800170B8 40820018 */  bne     lbl_800170D0
/* 011B1C 800170BC 38000000 */  li      r0, 0
/* 011B20 800170C0 900D8988 */  stw     r0, prevMenuEntry@sda21(r13)
/* 011B24 800170C4 38000002 */  li      r0, 2
/* 011B28 800170C8 901E0000 */  stw     r0, 0(r30)
/* 011B2C 800170CC 48000728 */  b       lbl_800177F4
lbl_800170D0:
/* 011B30 800170D0 38600000 */  li      r3, 0
/* 011B34 800170D4 3800000B */  li      r0, 0xb
/* 011B38 800170D8 906D8984 */  stw     r3, yes@sda21(r13)
/* 011B3C 800170DC 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011B40 800170E0 93FE0000 */  stw     r31, 0(r30)
/* 011B44 800170E4 48000710 */  b       lbl_800177F4
glabel lbl_800170E8
/* 011B48 800170E8 38600011 */  li      r3, 0x11
/* 011B4C 800170EC 388D8984 */  addi    r4, r13, yes@sda21
/* 011B50 800170F0 4BFF5A8D */  bl      simulatorDrawYesNoMessage
/* 011B54 800170F4 2C030001 */  cmpwi   r3, 1
/* 011B58 800170F8 408206FC */  bne     lbl_800177F4
/* 011B5C 800170FC 38800000 */  li      r4, 0
/* 011B60 80017100 909D07AC */  stw     r4, 0x7ac(r29)
/* 011B64 80017104 3860000B */  li      r3, 0xb
/* 011B68 80017108 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011B6C 8001710C 906D898C */  stw     r3, nextMenuEntry@sda21(r13)
/* 011B70 80017110 2C000001 */  cmpwi   r0, 1
/* 011B74 80017114 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011B78 80017118 40820014 */  bne     lbl_8001712C
/* 011B7C 8001711C 909D07B0 */  stw     r4, 0x7b0(r29)
/* 011B80 80017120 38000003 */  li      r0, 3
/* 011B84 80017124 901E0000 */  stw     r0, 0(r30)
/* 011B88 80017128 480006CC */  b       lbl_800177F4
lbl_8001712C:
/* 011B8C 8001712C 93FE0000 */  stw     r31, 0(r30)
/* 011B90 80017130 480006C4 */  b       lbl_800177F4
glabel lbl_80017134
/* 011B94 80017134 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011B98 80017138 3860001D */  li      r3, 0x1d
/* 011B9C 8001713C 4BFF28F5 */  bl      simulatorDrawErrorMessageWait
/* 011BA0 80017140 2C030001 */  cmpwi   r3, 1
/* 011BA4 80017144 408206B0 */  bne     lbl_800177F4
/* 011BA8 80017148 3800000D */  li      r0, 0xd
/* 011BAC 8001714C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011BB0 80017150 93FE0000 */  stw     r31, 0(r30)
/* 011BB4 80017154 480006A0 */  b       lbl_800177F4
glabel lbl_80017158
/* 011BB8 80017158 3860001E */  li      r3, 0x1e
/* 011BBC 8001715C 4BFF28D5 */  bl      simulatorDrawErrorMessageWait
/* 011BC0 80017160 2C030001 */  cmpwi   r3, 1
/* 011BC4 80017164 40820690 */  bne     lbl_800177F4
/* 011BC8 80017168 38600000 */  li      r3, 0
/* 011BCC 8001716C 3800000B */  li      r0, 0xb
/* 011BD0 80017170 906D8984 */  stw     r3, yes@sda21(r13)
/* 011BD4 80017174 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011BD8 80017178 93FE0000 */  stw     r31, 0(r30)
/* 011BDC 8001717C 48000678 */  b       lbl_800177F4
glabel lbl_80017180
/* 011BE0 80017180 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011BE4 80017184 3860001F */  li      r3, 0x1f
/* 011BE8 80017188 4BFF28A9 */  bl      simulatorDrawErrorMessageWait
/* 011BEC 8001718C 2C030001 */  cmpwi   r3, 1
/* 011BF0 80017190 40820664 */  bne     lbl_800177F4
/* 011BF4 80017194 38000020 */  li      r0, 0x20
/* 011BF8 80017198 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011BFC 8001719C 93FD07B0 */  stw     r31, 0x7b0(r29)
/* 011C00 800171A0 93FE0000 */  stw     r31, 0(r30)
/* 011C04 800171A4 48000650 */  b       lbl_800177F4
glabel lbl_800171A8
/* 011C08 800171A8 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011C0C 800171AC 38600020 */  li      r3, 0x20
/* 011C10 800171B0 4BFF2881 */  bl      simulatorDrawErrorMessageWait
/* 011C14 800171B4 2C030001 */  cmpwi   r3, 1
/* 011C18 800171B8 4082063C */  bne     lbl_800177F4
/* 011C1C 800171BC 38000020 */  li      r0, 0x20
/* 011C20 800171C0 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011C24 800171C4 93FE0000 */  stw     r31, 0(r30)
/* 011C28 800171C8 4800062C */  b       lbl_800177F4
glabel lbl_800171CC
/* 011C2C 800171CC 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011C30 800171D0 38600021 */  li      r3, 0x21
/* 011C34 800171D4 4BFF285D */  bl      simulatorDrawErrorMessageWait
/* 011C38 800171D8 2C030001 */  cmpwi   r3, 1
/* 011C3C 800171DC 40820618 */  bne     lbl_800177F4
/* 011C40 800171E0 38000020 */  li      r0, 0x20
/* 011C44 800171E4 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011C48 800171E8 93FE0000 */  stw     r31, 0(r30)
/* 011C4C 800171EC 48000608 */  b       lbl_800177F4
glabel lbl_800171F0
/* 011C50 800171F0 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011C54 800171F4 38600022 */  li      r3, 0x22
/* 011C58 800171F8 4BFF2839 */  bl      simulatorDrawErrorMessageWait
/* 011C5C 800171FC 2C030001 */  cmpwi   r3, 1
/* 011C60 80017200 408205F4 */  bne     lbl_800177F4
/* 011C64 80017204 38600000 */  li      r3, 0
/* 011C68 80017208 38000012 */  li      r0, 0x12
/* 011C6C 8001720C 906D8984 */  stw     r3, yes@sda21(r13)
/* 011C70 80017210 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011C74 80017214 93FE0000 */  stw     r31, 0(r30)
/* 011C78 80017218 480005DC */  b       lbl_800177F4
glabel lbl_8001721C
/* 011C7C 8001721C 3860000C */  li      r3, 0xc
/* 011C80 80017220 388D8984 */  addi    r4, r13, yes@sda21
/* 011C84 80017224 4BFF5959 */  bl      simulatorDrawYesNoMessage
/* 011C88 80017228 2C030001 */  cmpwi   r3, 1
/* 011C8C 8001722C 408205C8 */  bne     lbl_800177F4
/* 011C90 80017230 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011C94 80017234 2C000001 */  cmpwi   r0, 1
/* 011C98 80017238 4082001C */  bne     lbl_80017254
/* 011C9C 8001723C 38600000 */  li      r3, 0
/* 011CA0 80017240 38000022 */  li      r0, 0x22
/* 011CA4 80017244 906D8984 */  stw     r3, yes@sda21(r13)
/* 011CA8 80017248 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011CAC 8001724C 93FE0000 */  stw     r31, 0(r30)
/* 011CB0 80017250 480005A4 */  b       lbl_800177F4
lbl_80017254:
/* 011CB4 80017254 3800001E */  li      r0, 0x1e
/* 011CB8 80017258 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011CBC 8001725C 93FE0000 */  stw     r31, 0(r30)
/* 011CC0 80017260 48000594 */  b       lbl_800177F4
glabel lbl_80017264
/* 011CC4 80017264 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011CC8 80017268 38600023 */  li      r3, 0x23
/* 011CCC 8001726C 4BFF27C5 */  bl      simulatorDrawErrorMessageWait
/* 011CD0 80017270 2C030001 */  cmpwi   r3, 1
/* 011CD4 80017274 40820580 */  bne     lbl_800177F4
/* 011CD8 80017278 38000014 */  li      r0, 0x14
/* 011CDC 8001727C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011CE0 80017280 93FE0000 */  stw     r31, 0(r30)
/* 011CE4 80017284 48000570 */  b       lbl_800177F4
glabel lbl_80017288
/* 011CE8 80017288 38600024 */  li      r3, 0x24
/* 011CEC 8001728C 4BFF27A5 */  bl      simulatorDrawErrorMessageWait
/* 011CF0 80017290 2C030001 */  cmpwi   r3, 1
/* 011CF4 80017294 40820560 */  bne     lbl_800177F4
/* 011CF8 80017298 38000015 */  li      r0, 0x15
/* 011CFC 8001729C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011D00 800172A0 93FE0000 */  stw     r31, 0(r30)
/* 011D04 800172A4 48000550 */  b       lbl_800177F4
glabel lbl_800172A8
/* 011D08 800172A8 38600025 */  li      r3, 0x25
/* 011D0C 800172AC 4BFF2785 */  bl      simulatorDrawErrorMessageWait
/* 011D10 800172B0 2C030001 */  cmpwi   r3, 1
/* 011D14 800172B4 40820540 */  bne     lbl_800177F4
/* 011D18 800172B8 38600000 */  li      r3, 0
/* 011D1C 800172BC 38000016 */  li      r0, 0x16
/* 011D20 800172C0 906D8984 */  stw     r3, yes@sda21(r13)
/* 011D24 800172C4 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011D28 800172C8 93FE0000 */  stw     r31, 0(r30)
/* 011D2C 800172CC 48000528 */  b       lbl_800177F4
glabel lbl_800172D0
/* 011D30 800172D0 38600026 */  li      r3, 0x26
/* 011D34 800172D4 388D8984 */  addi    r4, r13, yes@sda21
/* 011D38 800172D8 4BFF58A5 */  bl      simulatorDrawYesNoMessage
/* 011D3C 800172DC 2C030001 */  cmpwi   r3, 1
/* 011D40 800172E0 40820514 */  bne     lbl_800177F4
/* 011D44 800172E4 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011D48 800172E8 2C000001 */  cmpwi   r0, 1
/* 011D4C 800172EC 4082001C */  bne     lbl_80017308
/* 011D50 800172F0 38600000 */  li      r3, 0
/* 011D54 800172F4 38000017 */  li      r0, 0x17
/* 011D58 800172F8 906D8984 */  stw     r3, yes@sda21(r13)
/* 011D5C 800172FC 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011D60 80017300 93FE0000 */  stw     r31, 0(r30)
/* 011D64 80017304 480004F0 */  b       lbl_800177F4
lbl_80017308:
/* 011D68 80017308 38600000 */  li      r3, 0
/* 011D6C 8001730C 3800000B */  li      r0, 0xb
/* 011D70 80017310 906D8984 */  stw     r3, yes@sda21(r13)
/* 011D74 80017314 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011D78 80017318 93FE0000 */  stw     r31, 0(r30)
/* 011D7C 8001731C 480004D8 */  b       lbl_800177F4
glabel lbl_80017320
/* 011D80 80017320 38600027 */  li      r3, 0x27
/* 011D84 80017324 388D8984 */  addi    r4, r13, yes@sda21
/* 011D88 80017328 4BFF5855 */  bl      simulatorDrawYesNoMessage
/* 011D8C 8001732C 2C030001 */  cmpwi   r3, 1
/* 011D90 80017330 408204C4 */  bne     lbl_800177F4
/* 011D94 80017334 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011D98 80017338 2C000001 */  cmpwi   r0, 1
/* 011D9C 8001733C 40820018 */  bne     lbl_80017354
/* 011DA0 80017340 38000000 */  li      r0, 0
/* 011DA4 80017344 900D8988 */  stw     r0, prevMenuEntry@sda21(r13)
/* 011DA8 80017348 38000002 */  li      r0, 2
/* 011DAC 8001734C 901E0000 */  stw     r0, 0(r30)
/* 011DB0 80017350 480004A4 */  b       lbl_800177F4
lbl_80017354:
/* 011DB4 80017354 38000000 */  li      r0, 0
/* 011DB8 80017358 900D8984 */  stw     r0, yes@sda21(r13)
/* 011DBC 8001735C 900D8988 */  stw     r0, prevMenuEntry@sda21(r13)
/* 011DC0 80017360 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011DC4 80017364 93FE0000 */  stw     r31, 0(r30)
/* 011DC8 80017368 4800048C */  b       lbl_800177F4
glabel lbl_8001736C
/* 011DCC 8001736C 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011DD0 80017370 38600028 */  li      r3, 0x28
/* 011DD4 80017374 4BFF26BD */  bl      simulatorDrawErrorMessageWait
/* 011DD8 80017378 2C030001 */  cmpwi   r3, 1
/* 011DDC 8001737C 40820478 */  bne     lbl_800177F4
/* 011DE0 80017380 38600000 */  li      r3, 0
/* 011DE4 80017384 3800000B */  li      r0, 0xb
/* 011DE8 80017388 906D8984 */  stw     r3, yes@sda21(r13)
/* 011DEC 8001738C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011DF0 80017390 93FE0000 */  stw     r31, 0(r30)
/* 011DF4 80017394 48000460 */  b       lbl_800177F4
glabel lbl_80017398
/* 011DF8 80017398 3860001A */  li      r3, 0x1a
/* 011DFC 8001739C 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011E00 800173A0 38000000 */  li      r0, 0
/* 011E04 800173A4 906D898C */  stw     r3, nextMenuEntry@sda21(r13)
/* 011E08 800173A8 900D8984 */  stw     r0, yes@sda21(r13)
/* 011E0C 800173AC 48000448 */  b       lbl_800177F4
glabel lbl_800173B0
/* 011E10 800173B0 38600029 */  li      r3, 0x29
/* 011E14 800173B4 388D8984 */  addi    r4, r13, yes@sda21
/* 011E18 800173B8 4BFF57C5 */  bl      simulatorDrawYesNoMessage
/* 011E1C 800173BC 2C030001 */  cmpwi   r3, 1
/* 011E20 800173C0 40820434 */  bne     lbl_800177F4
/* 011E24 800173C4 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011E28 800173C8 2C000001 */  cmpwi   r0, 1
/* 011E2C 800173CC 40820010 */  bne     lbl_800173DC
/* 011E30 800173D0 38000005 */  li      r0, 5
/* 011E34 800173D4 901E0000 */  stw     r0, 0(r30)
/* 011E38 800173D8 4800041C */  b       lbl_800177F4
lbl_800173DC:
/* 011E3C 800173DC 38600000 */  li      r3, 0
/* 011E40 800173E0 3800000B */  li      r0, 0xb
/* 011E44 800173E4 906D8984 */  stw     r3, yes@sda21(r13)
/* 011E48 800173E8 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011E4C 800173EC 93FE0000 */  stw     r31, 0(r30)
/* 011E50 800173F0 48000404 */  b       lbl_800177F4
glabel lbl_800173F4
/* 011E54 800173F4 3860001C */  li      r3, 0x1c
/* 011E58 800173F8 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011E5C 800173FC 38000000 */  li      r0, 0
/* 011E60 80017400 906D898C */  stw     r3, nextMenuEntry@sda21(r13)
/* 011E64 80017404 900D8984 */  stw     r0, yes@sda21(r13)
/* 011E68 80017408 480003EC */  b       lbl_800177F4
glabel lbl_8001740C
/* 011E6C 8001740C 38600029 */  li      r3, 0x29
/* 011E70 80017410 388D8984 */  addi    r4, r13, yes@sda21
/* 011E74 80017414 4BFF5769 */  bl      simulatorDrawYesNoMessage
/* 011E78 80017418 2C030001 */  cmpwi   r3, 1
/* 011E7C 8001741C 408203D8 */  bne     lbl_800177F4
/* 011E80 80017420 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011E84 80017424 2C000001 */  cmpwi   r0, 1
/* 011E88 80017428 40820018 */  bne     lbl_80017440
/* 011E8C 8001742C 38000000 */  li      r0, 0
/* 011E90 80017430 900D8988 */  stw     r0, prevMenuEntry@sda21(r13)
/* 011E94 80017434 38000005 */  li      r0, 5
/* 011E98 80017438 901E0000 */  stw     r0, 0(r30)
/* 011E9C 8001743C 480003B8 */  b       lbl_800177F4
lbl_80017440:
/* 011EA0 80017440 38600000 */  li      r3, 0
/* 011EA4 80017444 3800000B */  li      r0, 0xb
/* 011EA8 80017448 906D8984 */  stw     r3, yes@sda21(r13)
/* 011EAC 8001744C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011EB0 80017450 93FE0000 */  stw     r31, 0(r30)
/* 011EB4 80017454 480003A0 */  b       lbl_800177F4
glabel lbl_80017458
/* 011EB8 80017458 93FD07AC */  stw     r31, 0x7ac(r29)
/* 011EBC 8001745C 3860002B */  li      r3, 0x2b
/* 011EC0 80017460 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011EC4 80017464 908D898C */  stw     r4, nextMenuEntry@sda21(r13)
/* 011EC8 80017468 4BFF25C9 */  bl      simulatorDrawErrorMessageWait
/* 011ECC 8001746C 2C030001 */  cmpwi   r3, 1
/* 011ED0 80017470 40820384 */  bne     lbl_800177F4
/* 011ED4 80017474 38000000 */  li      r0, 0
/* 011ED8 80017478 901D07AC */  stw     r0, 0x7ac(r29)
/* 011EDC 8001747C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011EE0 80017480 900D8988 */  stw     r0, prevMenuEntry@sda21(r13)
/* 011EE4 80017484 93FE0000 */  stw     r31, 0(r30)
/* 011EE8 80017488 4800036C */  b       lbl_800177F4
glabel lbl_8001748C
/* 011EEC 8001748C 3860002C */  li      r3, 0x2c
/* 011EF0 80017490 4BFF25A1 */  bl      simulatorDrawErrorMessageWait
/* 011EF4 80017494 2C030001 */  cmpwi   r3, 1
/* 011EF8 80017498 4082035C */  bne     lbl_800177F4
/* 011EFC 8001749C 38000020 */  li      r0, 0x20
/* 011F00 800174A0 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011F04 800174A4 93FE0000 */  stw     r31, 0(r30)
/* 011F08 800174A8 4800034C */  b       lbl_800177F4
glabel lbl_800174AC
/* 011F0C 800174AC 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 011F10 800174B0 3860002D */  li      r3, 0x2d
/* 011F14 800174B4 93FD07AC */  stw     r31, 0x7ac(r29)
/* 011F18 800174B8 4BFF2579 */  bl      simulatorDrawErrorMessageWait
/* 011F1C 800174BC 2C030001 */  cmpwi   r3, 1
/* 011F20 800174C0 40820334 */  bne     lbl_800177F4
/* 011F24 800174C4 38600000 */  li      r3, 0
/* 011F28 800174C8 907D07AC */  stw     r3, 0x7ac(r29)
/* 011F2C 800174CC 38000003 */  li      r0, 3
/* 011F30 800174D0 906D8988 */  stw     r3, prevMenuEntry@sda21(r13)
/* 011F34 800174D4 901E0000 */  stw     r0, 0(r30)
/* 011F38 800174D8 4800031C */  b       lbl_800177F4
glabel lbl_800174DC
/* 011F3C 800174DC 3860002E */  li      r3, 0x2e
/* 011F40 800174E0 4BFF2551 */  bl      simulatorDrawErrorMessageWait
/* 011F44 800174E4 2C030001 */  cmpwi   r3, 1
/* 011F48 800174E8 4082030C */  bne     lbl_800177F4
/* 011F4C 800174EC 38600000 */  li      r3, 0
/* 011F50 800174F0 3800000B */  li      r0, 0xb
/* 011F54 800174F4 906D8984 */  stw     r3, yes@sda21(r13)
/* 011F58 800174F8 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011F5C 800174FC 93FE0000 */  stw     r31, 0(r30)
/* 011F60 80017500 480002F4 */  b       lbl_800177F4
glabel lbl_80017504
/* 011F64 80017504 38600018 */  li      r3, 0x18
/* 011F68 80017508 388D8984 */  addi    r4, r13, yes@sda21
/* 011F6C 8001750C 4BFF5671 */  bl      simulatorDrawYesNoMessage
/* 011F70 80017510 2C030001 */  cmpwi   r3, 1
/* 011F74 80017514 408202E0 */  bne     lbl_800177F4
/* 011F78 80017518 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011F7C 8001751C 2C000001 */  cmpwi   r0, 1
/* 011F80 80017520 40820018 */  bne     lbl_80017538
/* 011F84 80017524 38000000 */  li      r0, 0
/* 011F88 80017528 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011F8C 8001752C 38000006 */  li      r0, 6
/* 011F90 80017530 901E0000 */  stw     r0, 0(r30)
/* 011F94 80017534 480002C0 */  b       lbl_800177F4
lbl_80017538:
/* 011F98 80017538 38000027 */  li      r0, 0x27
/* 011F9C 8001753C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011FA0 80017540 93FE0000 */  stw     r31, 0(r30)
/* 011FA4 80017544 480002B0 */  b       lbl_800177F4
glabel lbl_80017548
/* 011FA8 80017548 38600018 */  li      r3, 0x18
/* 011FAC 8001754C 388D8984 */  addi    r4, r13, yes@sda21
/* 011FB0 80017550 4BFF562D */  bl      simulatorDrawYesNoMessage
/* 011FB4 80017554 2C030001 */  cmpwi   r3, 1
/* 011FB8 80017558 4082029C */  bne     lbl_800177F4
/* 011FBC 8001755C 800D8984 */  lwz     r0, yes@sda21(r13)
/* 011FC0 80017560 2C000001 */  cmpwi   r0, 1
/* 011FC4 80017564 4082001C */  bne     lbl_80017580
/* 011FC8 80017568 38600000 */  li      r3, 0
/* 011FCC 8001756C 906D8988 */  stw     r3, prevMenuEntry@sda21(r13)
/* 011FD0 80017570 38000006 */  li      r0, 6
/* 011FD4 80017574 906D898C */  stw     r3, nextMenuEntry@sda21(r13)
/* 011FD8 80017578 901E0000 */  stw     r0, 0(r30)
/* 011FDC 8001757C 48000278 */  b       lbl_800177F4
lbl_80017580:
/* 011FE0 80017580 3800001E */  li      r0, 0x1e
/* 011FE4 80017584 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 011FE8 80017588 93FE0000 */  stw     r31, 0(r30)
/* 011FEC 8001758C 48000268 */  b       lbl_800177F4
glabel lbl_80017590
/* 011FF0 80017590 93FD07AC */  stw     r31, 0x7ac(r29)
/* 011FF4 80017594 3860001A */  li      r3, 0x1a
/* 011FF8 80017598 4BFF2499 */  bl      simulatorDrawErrorMessageWait
/* 011FFC 8001759C 2C030001 */  cmpwi   r3, 1
/* 012000 800175A0 40820254 */  bne     lbl_800177F4
/* 012004 800175A4 38000000 */  li      r0, 0
/* 012008 800175A8 901D07AC */  stw     r0, 0x7ac(r29)
/* 01200C 800175AC 900D8988 */  stw     r0, prevMenuEntry@sda21(r13)
/* 012010 800175B0 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 012014 800175B4 93FE0000 */  stw     r31, 0(r30)
/* 012018 800175B8 4800023C */  b       lbl_800177F4
glabel lbl_800175BC
/* 01201C 800175BC 93FD07AC */  stw     r31, 0x7ac(r29)
/* 012020 800175C0 3860001B */  li      r3, 0x1b
/* 012024 800175C4 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 012028 800175C8 908D898C */  stw     r4, nextMenuEntry@sda21(r13)
/* 01202C 800175CC 4BFF2465 */  bl      simulatorDrawErrorMessageWait
/* 012030 800175D0 2C030001 */  cmpwi   r3, 1
/* 012034 800175D4 40820220 */  bne     lbl_800177F4
/* 012038 800175D8 38000002 */  li      r0, 2
/* 01203C 800175DC 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 012040 800175E0 93FE0000 */  stw     r31, 0(r30)
/* 012044 800175E4 48000210 */  b       lbl_800177F4
glabel lbl_800175E8
/* 012048 800175E8 93FD07AC */  stw     r31, 0x7ac(r29)
/* 01204C 800175EC 3860001B */  li      r3, 0x1b
/* 012050 800175F0 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 012054 800175F4 908D898C */  stw     r4, nextMenuEntry@sda21(r13)
/* 012058 800175F8 4BFF2439 */  bl      simulatorDrawErrorMessageWait
/* 01205C 800175FC 2C030001 */  cmpwi   r3, 1
/* 012060 80017600 408201F4 */  bne     lbl_800177F4
/* 012064 80017604 3800000E */  li      r0, 0xe
/* 012068 80017608 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 01206C 8001760C 93FE0000 */  stw     r31, 0(r30)
/* 012070 80017610 480001E4 */  b       lbl_800177F4
glabel lbl_80017614
/* 012074 80017614 3860001C */  li      r3, 0x1c
/* 012078 80017618 4BFF2419 */  bl      simulatorDrawErrorMessageWait
/* 01207C 8001761C 2C030001 */  cmpwi   r3, 1
/* 012080 80017620 408201D4 */  bne     lbl_800177F4
/* 012084 80017624 38600000 */  li      r3, 0
/* 012088 80017628 3800000B */  li      r0, 0xb
/* 01208C 8001762C 906D8984 */  stw     r3, yes@sda21(r13)
/* 012090 80017630 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 012094 80017634 93FE0000 */  stw     r31, 0(r30)
/* 012098 80017638 480001BC */  b       lbl_800177F4
glabel lbl_8001763C
/* 01209C 8001763C 38600000 */  li      r3, 0
/* 0120A0 80017640 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 0120A4 80017644 38000029 */  li      r0, 0x29
/* 0120A8 80017648 906D8984 */  stw     r3, yes@sda21(r13)
/* 0120AC 8001764C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 0120B0 80017650 480001A4 */  b       lbl_800177F4
glabel lbl_80017654
/* 0120B4 80017654 38600012 */  li      r3, 0x12
/* 0120B8 80017658 388D8984 */  addi    r4, r13, yes@sda21
/* 0120BC 8001765C 4BFF5521 */  bl      simulatorDrawYesNoMessage
/* 0120C0 80017660 2C030001 */  cmpwi   r3, 1
/* 0120C4 80017664 40820190 */  bne     lbl_800177F4
/* 0120C8 80017668 800D8984 */  lwz     r0, yes@sda21(r13)
/* 0120CC 8001766C 2C000001 */  cmpwi   r0, 1
/* 0120D0 80017670 4082001C */  bne     lbl_8001768C
/* 0120D4 80017674 38600000 */  li      r3, 0
/* 0120D8 80017678 906D8988 */  stw     r3, prevMenuEntry@sda21(r13)
/* 0120DC 8001767C 38000004 */  li      r0, 4
/* 0120E0 80017680 906D898C */  stw     r3, nextMenuEntry@sda21(r13)
/* 0120E4 80017684 901E0000 */  stw     r0, 0(r30)
/* 0120E8 80017688 4800016C */  b       lbl_800177F4
lbl_8001768C:
/* 0120EC 8001768C 38000031 */  li      r0, 0x31
/* 0120F0 80017690 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 0120F4 80017694 93FE0000 */  stw     r31, 0(r30)
/* 0120F8 80017698 4800015C */  b       lbl_800177F4
glabel lbl_8001769C
/* 0120FC 8001769C 38600000 */  li      r3, 0
/* 012100 800176A0 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 012104 800176A4 3800002B */  li      r0, 0x2b
/* 012108 800176A8 906D8984 */  stw     r3, yes@sda21(r13)
/* 01210C 800176AC 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 012110 800176B0 48000144 */  b       lbl_800177F4
glabel lbl_800176B4
/* 012114 800176B4 38600012 */  li      r3, 0x12
/* 012118 800176B8 388D8984 */  addi    r4, r13, yes@sda21
/* 01211C 800176BC 4BFF54C1 */  bl      simulatorDrawYesNoMessage
/* 012120 800176C0 2C030001 */  cmpwi   r3, 1
/* 012124 800176C4 40820130 */  bne     lbl_800177F4
/* 012128 800176C8 800D8984 */  lwz     r0, yes@sda21(r13)
/* 01212C 800176CC 2C000001 */  cmpwi   r0, 1
/* 012130 800176D0 4082001C */  bne     lbl_800176EC
/* 012134 800176D4 38600000 */  li      r3, 0
/* 012138 800176D8 906D8988 */  stw     r3, prevMenuEntry@sda21(r13)
/* 01213C 800176DC 38000004 */  li      r0, 4
/* 012140 800176E0 906D898C */  stw     r3, nextMenuEntry@sda21(r13)
/* 012144 800176E4 901E0000 */  stw     r0, 0(r30)
/* 012148 800176E8 4800010C */  b       lbl_800177F4
lbl_800176EC:
/* 01214C 800176EC 38000030 */  li      r0, 0x30
/* 012150 800176F0 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 012154 800176F4 93FE0000 */  stw     r31, 0(r30)
/* 012158 800176F8 480000FC */  b       lbl_800177F4
glabel lbl_800176FC
/* 01215C 800176FC 93FD07AC */  stw     r31, 0x7ac(r29)
/* 012160 80017700 38600014 */  li      r3, 0x14
/* 012164 80017704 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 012168 80017708 908D898C */  stw     r4, nextMenuEntry@sda21(r13)
/* 01216C 8001770C 4BFF2325 */  bl      simulatorDrawErrorMessageWait
/* 012170 80017710 2C030001 */  cmpwi   r3, 1
/* 012174 80017714 408200E0 */  bne     lbl_800177F4
/* 012178 80017718 38000000 */  li      r0, 0
/* 01217C 8001771C 901D07AC */  stw     r0, 0x7ac(r29)
/* 012180 80017720 38600030 */  li      r3, 0x30
/* 012184 80017724 38000003 */  li      r0, 3
/* 012188 80017728 906D898C */  stw     r3, nextMenuEntry@sda21(r13)
/* 01218C 8001772C 901E0000 */  stw     r0, 0(r30)
/* 012190 80017730 480000C4 */  b       lbl_800177F4
glabel lbl_80017734
/* 012194 80017734 93FD07AC */  stw     r31, 0x7ac(r29)
/* 012198 80017738 38600015 */  li      r3, 0x15
/* 01219C 8001773C 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 0121A0 80017740 908D898C */  stw     r4, nextMenuEntry@sda21(r13)
/* 0121A4 80017744 4BFF22ED */  bl      simulatorDrawErrorMessageWait
/* 0121A8 80017748 2C030001 */  cmpwi   r3, 1
/* 0121AC 8001774C 408200A8 */  bne     lbl_800177F4
/* 0121B0 80017750 38000000 */  li      r0, 0
/* 0121B4 80017754 901D07AC */  stw     r0, 0x7ac(r29)
/* 0121B8 80017758 900D8988 */  stw     r0, prevMenuEntry@sda21(r13)
/* 0121BC 8001775C 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 0121C0 80017760 93FE0000 */  stw     r31, 0(r30)
/* 0121C4 80017764 48000090 */  b       lbl_800177F4
glabel lbl_80017768
/* 0121C8 80017768 93FD07AC */  stw     r31, 0x7ac(r29)
/* 0121CC 8001776C 38600015 */  li      r3, 0x15
/* 0121D0 80017770 908D8988 */  stw     r4, prevMenuEntry@sda21(r13)
/* 0121D4 80017774 908D898C */  stw     r4, nextMenuEntry@sda21(r13)
/* 0121D8 80017778 4BFF22B9 */  bl      simulatorDrawErrorMessageWait
/* 0121DC 8001777C 2C030001 */  cmpwi   r3, 1
/* 0121E0 80017780 40820074 */  bne     lbl_800177F4
/* 0121E4 80017784 38000000 */  li      r0, 0
/* 0121E8 80017788 901D07AC */  stw     r0, 0x7ac(r29)
/* 0121EC 8001778C 900D8988 */  stw     r0, prevMenuEntry@sda21(r13)
/* 0121F0 80017790 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 0121F4 80017794 93FE0000 */  stw     r31, 0(r30)
/* 0121F8 80017798 4800005C */  b       lbl_800177F4
glabel lbl_8001779C
/* 0121FC 8001779C 38600016 */  li      r3, 0x16
/* 012200 800177A0 4BFF2291 */  bl      simulatorDrawErrorMessageWait
/* 012204 800177A4 2C030001 */  cmpwi   r3, 1
/* 012208 800177A8 4082004C */  bne     lbl_800177F4
/* 01220C 800177AC 38600000 */  li      r3, 0
/* 012210 800177B0 3800000B */  li      r0, 0xb
/* 012214 800177B4 906D8984 */  stw     r3, yes@sda21(r13)
/* 012218 800177B8 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 01221C 800177BC 93FE0000 */  stw     r31, 0(r30)
/* 012220 800177C0 48000034 */  b       lbl_800177F4
glabel lbl_800177C4
/* 012224 800177C4 38600017 */  li      r3, 0x17
/* 012228 800177C8 4BFF2269 */  bl      simulatorDrawErrorMessageWait
/* 01222C 800177CC 2C030001 */  cmpwi   r3, 1
/* 012230 800177D0 40820024 */  bne     lbl_800177F4
/* 012234 800177D4 38600000 */  li      r3, 0
/* 012238 800177D8 3800000B */  li      r0, 0xb
/* 01223C 800177DC 906D8984 */  stw     r3, yes@sda21(r13)
/* 012240 800177E0 900D898C */  stw     r0, nextMenuEntry@sda21(r13)
/* 012244 800177E4 93FE0000 */  stw     r31, 0(r30)
/* 012248 800177E8 4800000C */  b       lbl_800177F4
glabel lbl_800177EC
/* 01224C 800177EC 38600000 */  li      r3, 0
/* 012250 800177F0 48000008 */  b       lbl_800177F8
lbl_800177F4:
/* 012254 800177F4 38600001 */  li      r3, 1
lbl_800177F8:
/* 012258 800177F8 8001002C */  lwz     r0, 0x2c(r1)
/* 01225C 800177FC 83E10024 */  lwz     r31, 0x24(r1)
/* 012260 80017800 83C10020 */  lwz     r30, 0x20(r1)
/* 012264 80017804 7C0803A6 */  mtlr    r0
/* 012268 80017808 83A1001C */  lwz     r29, 0x1c(r1)
/* 01226C 8001780C 38210028 */  addi    r1, r1, 0x28
/* 012270 80017810 4E800020 */  blr     
