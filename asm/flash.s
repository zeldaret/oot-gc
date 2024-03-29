# flash.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel flashEvent
/* 08847C 8008DA1C 7C0802A6 */  mflr    r0
/* 088480 8008DA20 2C040003 */  cmpwi   r4, 3
/* 088484 8008DA24 90010004 */  stw     r0, 4(r1)
/* 088488 8008DA28 9421FFE0 */  stwu    r1, -0x20(r1)
/* 08848C 8008DA2C 93E1001C */  stw     r31, 0x1c(r1)
/* 088490 8008DA30 3BE50000 */  addi    r31, r5, 0
/* 088494 8008DA34 93C10018 */  stw     r30, 0x18(r1)
/* 088498 8008DA38 3BC30000 */  addi    r30, r3, 0
/* 08849C 8008DA3C 41820050 */  beq     lbl_8008DA8C
/* 0884A0 8008DA40 40800018 */  bge     lbl_8008DA58
/* 0884A4 8008DA44 2C040002 */  cmpwi   r4, 2
/* 0884A8 8008DA48 40800028 */  bge     lbl_8008DA70
/* 0884AC 8008DA4C 2C040000 */  cmpwi   r4, 0
/* 0884B0 8008DA50 408000D0 */  bge     lbl_8008DB20
/* 0884B4 8008DA54 480000C4 */  b       lbl_8008DB18
lbl_8008DA58:
/* 0884B8 8008DA58 2C041003 */  cmpwi   r4, 0x1003
/* 0884BC 8008DA5C 418200C4 */  beq     lbl_8008DB20
/* 0884C0 8008DA60 408000B8 */  bge     lbl_8008DB18
/* 0884C4 8008DA64 2C041002 */  cmpwi   r4, 0x1002
/* 0884C8 8008DA68 40800030 */  bge     lbl_8008DA98
/* 0884CC 8008DA6C 480000AC */  b       lbl_8008DB18
lbl_8008DA70:
/* 0884D0 8008DA70 93FE0000 */  stw     r31, 0(r30)
/* 0884D4 8008DA74 38000000 */  li      r0, 0
/* 0884D8 8008DA78 387E0008 */  addi    r3, r30, 8
/* 0884DC 8008DA7C 901E0004 */  stw     r0, 4(r30)
/* 0884E0 8008DA80 38800080 */  li      r4, 0x80
/* 0884E4 8008DA84 4BF79731 */  bl      xlHeapTake
/* 0884E8 8008DA88 48000098 */  b       lbl_8008DB20
lbl_8008DA8C:
/* 0884EC 8008DA8C 387E0008 */  addi    r3, r30, 8
/* 0884F0 8008DA90 4BF79609 */  bl      xlHeapFree
/* 0884F4 8008DA94 4800008C */  b       lbl_8008DB20
lbl_8008DA98:
/* 0884F8 8008DA98 807E0000 */  lwz     r3, 0(r30)
/* 0884FC 8008DA9C 3CA08009 */  lis     r5, flashPut8@ha
/* 088500 8008DAA0 3CC08009 */  lis     r6, flashPut16@ha
/* 088504 8008DAA4 3CE08009 */  lis     r7, flashPut32@ha
/* 088508 8008DAA8 80630024 */  lwz     r3, 0x24(r3)
/* 08850C 8008DAAC 3C808009 */  lis     r4, flashPut64@ha
/* 088510 8008DAB0 3904DBF8 */  addi    r8, r4, flashPut64@l
/* 088514 8008DAB4 38A5DED8 */  addi    r5, r5, flashPut8@l
/* 088518 8008DAB8 38C6DED0 */  addi    r6, r6, flashPut16@l
/* 08851C 8008DABC 38E7DC00 */  addi    r7, r7, flashPut32@l
/* 088520 8008DAC0 389F0000 */  addi    r4, r31, 0
/* 088524 8008DAC4 4BFA7575 */  bl      cpuSetDevicePut
/* 088528 8008DAC8 2C030000 */  cmpwi   r3, 0
/* 08852C 8008DACC 4082000C */  bne     lbl_8008DAD8
/* 088530 8008DAD0 38600000 */  li      r3, 0
/* 088534 8008DAD4 48000050 */  b       lbl_8008DB24
lbl_8008DAD8:
/* 088538 8008DAD8 807E0000 */  lwz     r3, 0(r30)
/* 08853C 8008DADC 3CA08009 */  lis     r5, flashGet8@ha
/* 088540 8008DAE0 3CC08009 */  lis     r6, flashGet16@ha
/* 088544 8008DAE4 3CE08009 */  lis     r7, flashGet32@ha
/* 088548 8008DAE8 80630024 */  lwz     r3, 0x24(r3)
/* 08854C 8008DAEC 3C808009 */  lis     r4, flashGet64@ha
/* 088550 8008DAF0 3904DB3C */  addi    r8, r4, flashGet64@l
/* 088554 8008DAF4 38A5DBF0 */  addi    r5, r5, flashGet8@l
/* 088558 8008DAF8 38C6DBE8 */  addi    r6, r6, flashGet16@l
/* 08855C 8008DAFC 38E7DB44 */  addi    r7, r7, flashGet32@l
/* 088560 8008DB00 389F0000 */  addi    r4, r31, 0
/* 088564 8008DB04 4BFA754D */  bl      cpuSetDeviceGet
/* 088568 8008DB08 2C030000 */  cmpwi   r3, 0
/* 08856C 8008DB0C 40820014 */  bne     lbl_8008DB20
/* 088570 8008DB10 38600000 */  li      r3, 0
/* 088574 8008DB14 48000010 */  b       lbl_8008DB24
lbl_8008DB18:
/* 088578 8008DB18 38600000 */  li      r3, 0
/* 08857C 8008DB1C 48000008 */  b       lbl_8008DB24
lbl_8008DB20:
/* 088580 8008DB20 38600001 */  li      r3, 1
lbl_8008DB24:
/* 088584 8008DB24 80010024 */  lwz     r0, 0x24(r1)
/* 088588 8008DB28 83E1001C */  lwz     r31, 0x1c(r1)
/* 08858C 8008DB2C 83C10018 */  lwz     r30, 0x18(r1)
/* 088590 8008DB30 7C0803A6 */  mtlr    r0
/* 088594 8008DB34 38210020 */  addi    r1, r1, 0x20
/* 088598 8008DB38 4E800020 */  blr     

flashGet64:
/* 08859C 8008DB3C 38600001 */  li      r3, 1
/* 0885A0 8008DB40 4E800020 */  blr     

flashGet32:
/* 0885A4 8008DB44 80830004 */  lwz     r4, 4(r3)
/* 0885A8 8008DB48 3C00F000 */  lis     r0, 0xf000
/* 0885AC 8008DB4C 5484000E */  rlwinm  r4, r4, 0, 0, 7
/* 0885B0 8008DB50 7C040000 */  cmpw    r4, r0
/* 0885B4 8008DB54 41820084 */  beq     lbl_8008DBD8
/* 0885B8 8008DB58 40800044 */  bge     lbl_8008DB9C
/* 0885BC 8008DB5C 3C00D200 */  lis     r0, 0xd200
/* 0885C0 8008DB60 7C040000 */  cmpw    r4, r0
/* 0885C4 8008DB64 41820074 */  beq     lbl_8008DBD8
/* 0885C8 8008DB68 40800024 */  bge     lbl_8008DB8C
/* 0885CC 8008DB6C 3C00B400 */  lis     r0, 0xb400
/* 0885D0 8008DB70 7C040000 */  cmpw    r4, r0
/* 0885D4 8008DB74 41820064 */  beq     lbl_8008DBD8
/* 0885D8 8008DB78 40800068 */  bge     lbl_8008DBE0
/* 0885DC 8008DB7C 3C00A500 */  lis     r0, 0xa500
/* 0885E0 8008DB80 7C040000 */  cmpw    r4, r0
/* 0885E4 8008DB84 41820054 */  beq     lbl_8008DBD8
/* 0885E8 8008DB88 48000058 */  b       lbl_8008DBE0
lbl_8008DB8C:
/* 0885EC 8008DB8C 3C00E100 */  lis     r0, 0xe100
/* 0885F0 8008DB90 7C040000 */  cmpw    r4, r0
/* 0885F4 8008DB94 41820044 */  beq     lbl_8008DBD8
/* 0885F8 8008DB98 48000048 */  b       lbl_8008DBE0
lbl_8008DB9C:
/* 0885FC 8008DB9C 3C004B00 */  lis     r0, 0x4b00
/* 088600 8008DBA0 7C040000 */  cmpw    r4, r0
/* 088604 8008DBA4 41820034 */  beq     lbl_8008DBD8
/* 088608 8008DBA8 40800020 */  bge     lbl_8008DBC8
/* 08860C 8008DBAC 3C003C00 */  lis     r0, 0x3c00
/* 088610 8008DBB0 7C040000 */  cmpw    r4, r0
/* 088614 8008DBB4 41820024 */  beq     lbl_8008DBD8
/* 088618 8008DBB8 40800028 */  bge     lbl_8008DBE0
/* 08861C 8008DBBC 2C040000 */  cmpwi   r4, 0
/* 088620 8008DBC0 41820018 */  beq     lbl_8008DBD8
/* 088624 8008DBC4 4800001C */  b       lbl_8008DBE0
lbl_8008DBC8:
/* 088628 8008DBC8 3C007800 */  lis     r0, 0x7800
/* 08862C 8008DBCC 7C040000 */  cmpw    r4, r0
/* 088630 8008DBD0 41820008 */  beq     lbl_8008DBD8
/* 088634 8008DBD4 4800000C */  b       lbl_8008DBE0
lbl_8008DBD8:
/* 088638 8008DBD8 8003000C */  lwz     r0, 0xc(r3)
/* 08863C 8008DBDC 90050000 */  stw     r0, 0(r5)
lbl_8008DBE0:
/* 088640 8008DBE0 38600001 */  li      r3, 1
/* 088644 8008DBE4 4E800020 */  blr     

flashGet16:
/* 088648 8008DBE8 38600001 */  li      r3, 1
/* 08864C 8008DBEC 4E800020 */  blr     

flashGet8:
/* 088650 8008DBF0 38600001 */  li      r3, 1
/* 088654 8008DBF4 4E800020 */  blr     

flashPut64:
/* 088658 8008DBF8 38600001 */  li      r3, 1
/* 08865C 8008DBFC 4E800020 */  blr     

flashPut32:
/* 088660 8008DC00 7C0802A6 */  mflr    r0
/* 088664 8008DC04 90010004 */  stw     r0, 4(r1)
/* 088668 8008DC08 3C00F000 */  lis     r0, 0xf000
/* 08866C 8008DC0C 9421FF50 */  stwu    r1, -0xb0(r1)
/* 088670 8008DC10 93E100AC */  stw     r31, 0xac(r1)
/* 088674 8008DC14 7CBF2B78 */  mr      r31, r5
/* 088678 8008DC18 93C100A8 */  stw     r30, 0xa8(r1)
/* 08867C 8008DC1C 3BC30000 */  addi    r30, r3, 0
/* 088680 8008DC20 93A100A4 */  stw     r29, 0xa4(r1)
/* 088684 8008DC24 938100A0 */  stw     r28, 0xa0(r1)
/* 088688 8008DC28 80850000 */  lwz     r4, 0(r5)
/* 08868C 8008DC2C 5483000E */  rlwinm  r3, r4, 0, 0, 7
/* 088690 8008DC30 7C030000 */  cmpw    r3, r0
/* 088694 8008DC34 41820264 */  beq     lbl_8008DE98
/* 088698 8008DC38 40800044 */  bge     lbl_8008DC7C
/* 08869C 8008DC3C 3C00D200 */  lis     r0, 0xd200
/* 0886A0 8008DC40 7C030000 */  cmpw    r3, r0
/* 0886A4 8008DC44 41820260 */  beq     lbl_8008DEA4
/* 0886A8 8008DC48 40800024 */  bge     lbl_8008DC6C
/* 0886AC 8008DC4C 3C00B400 */  lis     r0, 0xb400
/* 0886B0 8008DC50 7C030000 */  cmpw    r3, r0
/* 0886B4 8008DC54 41820250 */  beq     lbl_8008DEA4
/* 0886B8 8008DC58 4080024C */  bge     lbl_8008DEA4
/* 0886BC 8008DC5C 3C00A500 */  lis     r0, 0xa500
/* 0886C0 8008DC60 7C030000 */  cmpw    r3, r0
/* 0886C4 8008DC64 41820204 */  beq     lbl_8008DE68
/* 0886C8 8008DC68 4800023C */  b       lbl_8008DEA4
lbl_8008DC6C:
/* 0886CC 8008DC6C 3C00E100 */  lis     r0, 0xe100
/* 0886D0 8008DC70 7C030000 */  cmpw    r3, r0
/* 0886D4 8008DC74 41820044 */  beq     lbl_8008DCB8
/* 0886D8 8008DC78 4800022C */  b       lbl_8008DEA4
lbl_8008DC7C:
/* 0886DC 8008DC7C 3C004B00 */  lis     r0, 0x4b00
/* 0886E0 8008DC80 7C030000 */  cmpw    r3, r0
/* 0886E4 8008DC84 41820220 */  beq     lbl_8008DEA4
/* 0886E8 8008DC88 40800020 */  bge     lbl_8008DCA8
/* 0886EC 8008DC8C 3C003C00 */  lis     r0, 0x3c00
/* 0886F0 8008DC90 7C030000 */  cmpw    r3, r0
/* 0886F4 8008DC94 41820210 */  beq     lbl_8008DEA4
/* 0886F8 8008DC98 4080020C */  bge     lbl_8008DEA4
/* 0886FC 8008DC9C 2C030000 */  cmpwi   r3, 0
/* 088700 8008DCA0 41820204 */  beq     lbl_8008DEA4
/* 088704 8008DCA4 48000200 */  b       lbl_8008DEA4
lbl_8008DCA8:
/* 088708 8008DCA8 3C007800 */  lis     r0, 0x7800
/* 08870C 8008DCAC 7C030000 */  cmpw    r3, r0
/* 088710 8008DCB0 41820018 */  beq     lbl_8008DCC8
/* 088714 8008DCB4 480001F0 */  b       lbl_8008DEA4
lbl_8008DCB8:
/* 088718 8008DCB8 3C601112 */  lis     r3, 0x1112
/* 08871C 8008DCBC 38038001 */  addi    r0, r3, -32767
/* 088720 8008DCC0 901E000C */  stw     r0, 0xc(r30)
/* 088724 8008DCC4 480001E0 */  b       lbl_8008DEA4
lbl_8008DCC8:
/* 088728 8008DCC8 3C601112 */  lis     r3, 0x1112
/* 08872C 8008DCCC 38638008 */  addi    r3, r3, -32760
/* 088730 8008DCD0 38000002 */  li      r0, 2
/* 088734 8008DCD4 907E000C */  stw     r3, 0xc(r30)
/* 088738 8008DCD8 7C0903A6 */  mtctr   r0
/* 08873C 8008DCDC 3861001C */  addi    r3, r1, 0x1c
/* 088740 8008DCE0 38000000 */  li      r0, 0
lbl_8008DCE4:
/* 088744 8008DCE4 98030000 */  stb     r0, 0(r3)
/* 088748 8008DCE8 98030001 */  stb     r0, 1(r3)
/* 08874C 8008DCEC 98030002 */  stb     r0, 2(r3)
/* 088750 8008DCF0 98030003 */  stb     r0, 3(r3)
/* 088754 8008DCF4 98030004 */  stb     r0, 4(r3)
/* 088758 8008DCF8 98030005 */  stb     r0, 5(r3)
/* 08875C 8008DCFC 98030006 */  stb     r0, 6(r3)
/* 088760 8008DD00 98030007 */  stb     r0, 7(r3)
/* 088764 8008DD04 98030008 */  stb     r0, 8(r3)
/* 088768 8008DD08 98030009 */  stb     r0, 9(r3)
/* 08876C 8008DD0C 9803000A */  stb     r0, 0xa(r3)
/* 088770 8008DD10 9803000B */  stb     r0, 0xb(r3)
/* 088774 8008DD14 9803000C */  stb     r0, 0xc(r3)
/* 088778 8008DD18 9803000D */  stb     r0, 0xd(r3)
/* 08877C 8008DD1C 9803000E */  stb     r0, 0xe(r3)
/* 088780 8008DD20 9803000F */  stb     r0, 0xf(r3)
/* 088784 8008DD24 98030010 */  stb     r0, 0x10(r3)
/* 088788 8008DD28 98030011 */  stb     r0, 0x11(r3)
/* 08878C 8008DD2C 98030012 */  stb     r0, 0x12(r3)
/* 088790 8008DD30 98030013 */  stb     r0, 0x13(r3)
/* 088794 8008DD34 98030014 */  stb     r0, 0x14(r3)
/* 088798 8008DD38 98030015 */  stb     r0, 0x15(r3)
/* 08879C 8008DD3C 98030016 */  stb     r0, 0x16(r3)
/* 0887A0 8008DD40 98030017 */  stb     r0, 0x17(r3)
/* 0887A4 8008DD44 98030018 */  stb     r0, 0x18(r3)
/* 0887A8 8008DD48 98030019 */  stb     r0, 0x19(r3)
/* 0887AC 8008DD4C 9803001A */  stb     r0, 0x1a(r3)
/* 0887B0 8008DD50 9803001B */  stb     r0, 0x1b(r3)
/* 0887B4 8008DD54 9803001C */  stb     r0, 0x1c(r3)
/* 0887B8 8008DD58 9803001D */  stb     r0, 0x1d(r3)
/* 0887BC 8008DD5C 9803001E */  stb     r0, 0x1e(r3)
/* 0887C0 8008DD60 9803001F */  stb     r0, 0x1f(r3)
/* 0887C4 8008DD64 98030020 */  stb     r0, 0x20(r3)
/* 0887C8 8008DD68 98030021 */  stb     r0, 0x21(r3)
/* 0887CC 8008DD6C 98030022 */  stb     r0, 0x22(r3)
/* 0887D0 8008DD70 98030023 */  stb     r0, 0x23(r3)
/* 0887D4 8008DD74 98030024 */  stb     r0, 0x24(r3)
/* 0887D8 8008DD78 98030025 */  stb     r0, 0x25(r3)
/* 0887DC 8008DD7C 98030026 */  stb     r0, 0x26(r3)
/* 0887E0 8008DD80 98030027 */  stb     r0, 0x27(r3)
/* 0887E4 8008DD84 98030028 */  stb     r0, 0x28(r3)
/* 0887E8 8008DD88 98030029 */  stb     r0, 0x29(r3)
/* 0887EC 8008DD8C 9803002A */  stb     r0, 0x2a(r3)
/* 0887F0 8008DD90 9803002B */  stb     r0, 0x2b(r3)
/* 0887F4 8008DD94 9803002C */  stb     r0, 0x2c(r3)
/* 0887F8 8008DD98 9803002D */  stb     r0, 0x2d(r3)
/* 0887FC 8008DD9C 9803002E */  stb     r0, 0x2e(r3)
/* 088800 8008DDA0 9803002F */  stb     r0, 0x2f(r3)
/* 088804 8008DDA4 98030030 */  stb     r0, 0x30(r3)
/* 088808 8008DDA8 98030031 */  stb     r0, 0x31(r3)
/* 08880C 8008DDAC 98030032 */  stb     r0, 0x32(r3)
/* 088810 8008DDB0 98030033 */  stb     r0, 0x33(r3)
/* 088814 8008DDB4 98030034 */  stb     r0, 0x34(r3)
/* 088818 8008DDB8 98030035 */  stb     r0, 0x35(r3)
/* 08881C 8008DDBC 98030036 */  stb     r0, 0x36(r3)
/* 088820 8008DDC0 98030037 */  stb     r0, 0x37(r3)
/* 088824 8008DDC4 98030038 */  stb     r0, 0x38(r3)
/* 088828 8008DDC8 98030039 */  stb     r0, 0x39(r3)
/* 08882C 8008DDCC 9803003A */  stb     r0, 0x3a(r3)
/* 088830 8008DDD0 9803003B */  stb     r0, 0x3b(r3)
/* 088834 8008DDD4 9803003C */  stb     r0, 0x3c(r3)
/* 088838 8008DDD8 9803003D */  stb     r0, 0x3d(r3)
/* 08883C 8008DDDC 9803003E */  stb     r0, 0x3e(r3)
/* 088840 8008DDE0 9803003F */  stb     r0, 0x3f(r3)
/* 088844 8008DDE4 38630040 */  addi    r3, r3, 0x40
/* 088848 8008DDE8 4200FEFC */  bdnz    lbl_8008DCE4
/* 08884C 8008DDEC 809E0004 */  lwz     r4, 4(r30)
/* 088850 8008DDF0 5483000E */  rlwinm  r3, r4, 0, 0, 7
/* 088854 8008DDF4 3C03C400 */  addis   r0, r3, 0xc400
/* 088858 8008DDF8 28000000 */  cmplwi  r0, 0
/* 08885C 8008DDFC 40820040 */  bne     lbl_8008DE3C
/* 088860 8008DE00 3B800000 */  li      r28, 0
/* 088864 8008DE04 579D3830 */  slwi    r29, r28, 7
lbl_8008DE08:
/* 088868 8008DE08 387D0000 */  addi    r3, r29, 0
/* 08886C 8008DE0C 3881001C */  addi    r4, r1, 0x1c
/* 088870 8008DE10 38A00080 */  li      r5, 0x80
/* 088874 8008DE14 4BF7AFF9 */  bl      simulatorWriteFLASH
/* 088878 8008DE18 2C030000 */  cmpwi   r3, 0
/* 08887C 8008DE1C 4082000C */  bne     lbl_8008DE28
/* 088880 8008DE20 38600000 */  li      r3, 0
/* 088884 8008DE24 4800008C */  b       lbl_8008DEB0
lbl_8008DE28:
/* 088888 8008DE28 3B9C0001 */  addi    r28, r28, 1
/* 08888C 8008DE2C 2C1C0400 */  cmpwi   r28, 0x400
/* 088890 8008DE30 3BBD0080 */  addi    r29, r29, 0x80
/* 088894 8008DE34 4180FFD4 */  blt     lbl_8008DE08
/* 088898 8008DE38 4800006C */  b       lbl_8008DEA4
lbl_8008DE3C:
/* 08889C 8008DE3C 3C03B500 */  addis   r0, r3, 0xb500
/* 0888A0 8008DE40 28000000 */  cmplwi  r0, 0
/* 0888A4 8008DE44 40820060 */  bne     lbl_8008DEA4
/* 0888A8 8008DE48 54833870 */  rlwinm  r3, r4, 7, 1, 0x18
/* 0888AC 8008DE4C 3881001C */  addi    r4, r1, 0x1c
/* 0888B0 8008DE50 38A00080 */  li      r5, 0x80
/* 0888B4 8008DE54 4BF7AFB9 */  bl      simulatorWriteFLASH
/* 0888B8 8008DE58 2C030000 */  cmpwi   r3, 0
/* 0888BC 8008DE5C 40820048 */  bne     lbl_8008DEA4
/* 0888C0 8008DE60 38600000 */  li      r3, 0
/* 0888C4 8008DE64 4800004C */  b       lbl_8008DEB0
lbl_8008DE68:
/* 0888C8 8008DE68 3C601112 */  lis     r3, 0x1112
/* 0888CC 8008DE6C 38038004 */  addi    r0, r3, -32764
/* 0888D0 8008DE70 901E000C */  stw     r0, 0xc(r30)
/* 0888D4 8008DE74 38A00080 */  li      r5, 0x80
/* 0888D8 8008DE78 801F0000 */  lwz     r0, 0(r31)
/* 0888DC 8008DE7C 809E0008 */  lwz     r4, 8(r30)
/* 0888E0 8008DE80 54033870 */  rlwinm  r3, r0, 7, 1, 0x18
/* 0888E4 8008DE84 4BF7AF89 */  bl      simulatorWriteFLASH
/* 0888E8 8008DE88 2C030000 */  cmpwi   r3, 0
/* 0888EC 8008DE8C 40820018 */  bne     lbl_8008DEA4
/* 0888F0 8008DE90 38600000 */  li      r3, 0
/* 0888F4 8008DE94 4800001C */  b       lbl_8008DEB0
lbl_8008DE98:
/* 0888F8 8008DE98 3C601112 */  lis     r3, 0x1112
/* 0888FC 8008DE9C 38038004 */  addi    r0, r3, -32764
/* 088900 8008DEA0 901E000C */  stw     r0, 0xc(r30)
lbl_8008DEA4:
/* 088904 8008DEA4 801F0000 */  lwz     r0, 0(r31)
/* 088908 8008DEA8 38600001 */  li      r3, 1
/* 08890C 8008DEAC 901E0004 */  stw     r0, 4(r30)
lbl_8008DEB0:
/* 088910 8008DEB0 800100B4 */  lwz     r0, 0xb4(r1)
/* 088914 8008DEB4 83E100AC */  lwz     r31, 0xac(r1)
/* 088918 8008DEB8 83C100A8 */  lwz     r30, 0xa8(r1)
/* 08891C 8008DEBC 7C0803A6 */  mtlr    r0
/* 088920 8008DEC0 83A100A4 */  lwz     r29, 0xa4(r1)
/* 088924 8008DEC4 838100A0 */  lwz     r28, 0xa0(r1)
/* 088928 8008DEC8 382100B0 */  addi    r1, r1, 0xb0
/* 08892C 8008DECC 4E800020 */  blr     

flashPut16:
/* 088930 8008DED0 38600001 */  li      r3, 1
/* 088934 8008DED4 4E800020 */  blr     

flashPut8:
/* 088938 8008DED8 38600001 */  li      r3, 1
/* 08893C 8008DEDC 4E800020 */  blr     

glabel flashTransferFLASH
/* 088940 8008DEE0 7C0802A6 */  mflr    r0
/* 088944 8008DEE4 38A40000 */  addi    r5, r4, 0
/* 088948 8008DEE8 90010004 */  stw     r0, 4(r1)
/* 08894C 8008DEEC 9421FFD8 */  stwu    r1, -0x28(r1)
/* 088950 8008DEF0 93E10024 */  stw     r31, 0x24(r1)
/* 088954 8008DEF4 7C7F1B78 */  mr      r31, r3
/* 088958 8008DEF8 38810018 */  addi    r4, r1, 0x18
/* 08895C 8008DEFC 90C10014 */  stw     r6, 0x14(r1)
/* 088960 8008DF00 38C10014 */  addi    r6, r1, 0x14
/* 088964 8008DF04 80630000 */  lwz     r3, 0(r3)
/* 088968 8008DF08 8063002C */  lwz     r3, 0x2c(r3)
/* 08896C 8008DF0C 4BFDF195 */  bl      ramGetBuffer
/* 088970 8008DF10 2C030000 */  cmpwi   r3, 0
/* 088974 8008DF14 4082000C */  bne     lbl_8008DF20
/* 088978 8008DF18 38600000 */  li      r3, 0
/* 08897C 8008DF1C 480000C4 */  b       lbl_8008DFE0
lbl_8008DF20:
/* 088980 8008DF20 807F0004 */  lwz     r3, 4(r31)
/* 088984 8008DF24 3C00F000 */  lis     r0, 0xf000
/* 088988 8008DF28 5463000E */  rlwinm  r3, r3, 0, 0, 7
/* 08898C 8008DF2C 7C030000 */  cmpw    r3, r0
/* 088990 8008DF30 418200AC */  beq     lbl_8008DFDC
/* 088994 8008DF34 40800044 */  bge     lbl_8008DF78
/* 088998 8008DF38 3C00D200 */  lis     r0, 0xd200
/* 08899C 8008DF3C 7C030000 */  cmpw    r3, r0
/* 0889A0 8008DF40 4182009C */  beq     lbl_8008DFDC
/* 0889A4 8008DF44 40800024 */  bge     lbl_8008DF68
/* 0889A8 8008DF48 3C00B400 */  lis     r0, 0xb400
/* 0889AC 8008DF4C 7C030000 */  cmpw    r3, r0
/* 0889B0 8008DF50 41820064 */  beq     lbl_8008DFB4
/* 0889B4 8008DF54 40800088 */  bge     lbl_8008DFDC
/* 0889B8 8008DF58 3C00A500 */  lis     r0, 0xa500
/* 0889BC 8008DF5C 7C030000 */  cmpw    r3, r0
/* 0889C0 8008DF60 4182007C */  beq     lbl_8008DFDC
/* 0889C4 8008DF64 48000078 */  b       lbl_8008DFDC
lbl_8008DF68:
/* 0889C8 8008DF68 3C00E100 */  lis     r0, 0xe100
/* 0889CC 8008DF6C 7C030000 */  cmpw    r3, r0
/* 0889D0 8008DF70 4182006C */  beq     lbl_8008DFDC
/* 0889D4 8008DF74 48000068 */  b       lbl_8008DFDC
lbl_8008DF78:
/* 0889D8 8008DF78 3C004B00 */  lis     r0, 0x4b00
/* 0889DC 8008DF7C 7C030000 */  cmpw    r3, r0
/* 0889E0 8008DF80 4182005C */  beq     lbl_8008DFDC
/* 0889E4 8008DF84 40800020 */  bge     lbl_8008DFA4
/* 0889E8 8008DF88 3C003C00 */  lis     r0, 0x3c00
/* 0889EC 8008DF8C 7C030000 */  cmpw    r3, r0
/* 0889F0 8008DF90 4182004C */  beq     lbl_8008DFDC
/* 0889F4 8008DF94 40800048 */  bge     lbl_8008DFDC
/* 0889F8 8008DF98 2C030000 */  cmpwi   r3, 0
/* 0889FC 8008DF9C 41820040 */  beq     lbl_8008DFDC
/* 088A00 8008DFA0 4800003C */  b       lbl_8008DFDC
lbl_8008DFA4:
/* 088A04 8008DFA4 3C007800 */  lis     r0, 0x7800
/* 088A08 8008DFA8 7C030000 */  cmpw    r3, r0
/* 088A0C 8008DFAC 41820030 */  beq     lbl_8008DFDC
/* 088A10 8008DFB0 4800002C */  b       lbl_8008DFDC
lbl_8008DFB4:
/* 088A14 8008DFB4 38800000 */  li      r4, 0
/* 088A18 8008DFB8 48000018 */  b       lbl_8008DFD0
lbl_8008DFBC:
/* 088A1C 8008DFBC 80010018 */  lwz     r0, 0x18(r1)
/* 088A20 8008DFC0 807F0008 */  lwz     r3, 8(r31)
/* 088A24 8008DFC4 7C0400AE */  lbzx    r0, r4, r0
/* 088A28 8008DFC8 7C0321AE */  stbx    r0, r3, r4
/* 088A2C 8008DFCC 38840001 */  addi    r4, r4, 1
lbl_8008DFD0:
/* 088A30 8008DFD0 80010014 */  lwz     r0, 0x14(r1)
/* 088A34 8008DFD4 7C040000 */  cmpw    r4, r0
/* 088A38 8008DFD8 4180FFE4 */  blt     lbl_8008DFBC
lbl_8008DFDC:
/* 088A3C 8008DFDC 38600001 */  li      r3, 1
lbl_8008DFE0:
/* 088A40 8008DFE0 8001002C */  lwz     r0, 0x2c(r1)
/* 088A44 8008DFE4 83E10024 */  lwz     r31, 0x24(r1)
/* 088A48 8008DFE8 38210028 */  addi    r1, r1, 0x28
/* 088A4C 8008DFEC 7C0803A6 */  mtlr    r0
/* 088A50 8008DFF0 4E800020 */  blr     

glabel flashCopyFLASH
/* 088A54 8008DFF4 7C0802A6 */  mflr    r0
/* 088A58 8008DFF8 90010004 */  stw     r0, 4(r1)
/* 088A5C 8008DFFC 9421FFD8 */  stwu    r1, -0x28(r1)
/* 088A60 8008E000 93E10024 */  stw     r31, 0x24(r1)
/* 088A64 8008E004 3BE50000 */  addi    r31, r5, 0
/* 088A68 8008E008 38A40000 */  addi    r5, r4, 0
/* 088A6C 8008E00C 93C10020 */  stw     r30, 0x20(r1)
/* 088A70 8008E010 7C7E1B78 */  mr      r30, r3
/* 088A74 8008E014 38810018 */  addi    r4, r1, 0x18
/* 088A78 8008E018 90C10014 */  stw     r6, 0x14(r1)
/* 088A7C 8008E01C 38C10014 */  addi    r6, r1, 0x14
/* 088A80 8008E020 80630000 */  lwz     r3, 0(r3)
/* 088A84 8008E024 8063002C */  lwz     r3, 0x2c(r3)
/* 088A88 8008E028 4BFDF079 */  bl      ramGetBuffer
/* 088A8C 8008E02C 2C030000 */  cmpwi   r3, 0
/* 088A90 8008E030 4082000C */  bne     lbl_8008E03C
/* 088A94 8008E034 38600000 */  li      r3, 0
/* 088A98 8008E038 480000E8 */  b       lbl_8008E120
lbl_8008E03C:
/* 088A9C 8008E03C 809E000C */  lwz     r4, 0xc(r30)
/* 088AA0 8008E040 3C00F000 */  lis     r0, 0xf000
/* 088AA4 8008E044 80610018 */  lwz     r3, 0x18(r1)
/* 088AA8 8008E048 90830000 */  stw     r4, 0(r3)
/* 088AAC 8008E04C 807E0004 */  lwz     r3, 4(r30)
/* 088AB0 8008E050 5463000E */  rlwinm  r3, r3, 0, 0, 7
/* 088AB4 8008E054 7C030000 */  cmpw    r3, r0
/* 088AB8 8008E058 418200A4 */  beq     lbl_8008E0FC
/* 088ABC 8008E05C 40800044 */  bge     lbl_8008E0A0
/* 088AC0 8008E060 3C00D200 */  lis     r0, 0xd200
/* 088AC4 8008E064 7C030000 */  cmpw    r3, r0
/* 088AC8 8008E068 418200B4 */  beq     lbl_8008E11C
/* 088ACC 8008E06C 40800024 */  bge     lbl_8008E090
/* 088AD0 8008E070 3C00B400 */  lis     r0, 0xb400
/* 088AD4 8008E074 7C030000 */  cmpw    r3, r0
/* 088AD8 8008E078 418200A4 */  beq     lbl_8008E11C
/* 088ADC 8008E07C 408000A0 */  bge     lbl_8008E11C
/* 088AE0 8008E080 3C00A500 */  lis     r0, 0xa500
/* 088AE4 8008E084 7C030000 */  cmpw    r3, r0
/* 088AE8 8008E088 41820094 */  beq     lbl_8008E11C
/* 088AEC 8008E08C 48000090 */  b       lbl_8008E11C
lbl_8008E090:
/* 088AF0 8008E090 3C00E100 */  lis     r0, 0xe100
/* 088AF4 8008E094 7C030000 */  cmpw    r3, r0
/* 088AF8 8008E098 41820044 */  beq     lbl_8008E0DC
/* 088AFC 8008E09C 48000080 */  b       lbl_8008E11C
lbl_8008E0A0:
/* 088B00 8008E0A0 3C004B00 */  lis     r0, 0x4b00
/* 088B04 8008E0A4 7C030000 */  cmpw    r3, r0
/* 088B08 8008E0A8 41820074 */  beq     lbl_8008E11C
/* 088B0C 8008E0AC 40800020 */  bge     lbl_8008E0CC
/* 088B10 8008E0B0 3C003C00 */  lis     r0, 0x3c00
/* 088B14 8008E0B4 7C030000 */  cmpw    r3, r0
/* 088B18 8008E0B8 41820064 */  beq     lbl_8008E11C
/* 088B1C 8008E0BC 40800060 */  bge     lbl_8008E11C
/* 088B20 8008E0C0 2C030000 */  cmpwi   r3, 0
/* 088B24 8008E0C4 41820058 */  beq     lbl_8008E11C
/* 088B28 8008E0C8 48000054 */  b       lbl_8008E11C
lbl_8008E0CC:
/* 088B2C 8008E0CC 3C007800 */  lis     r0, 0x7800
/* 088B30 8008E0D0 7C030000 */  cmpw    r3, r0
/* 088B34 8008E0D4 41820048 */  beq     lbl_8008E11C
/* 088B38 8008E0D8 48000044 */  b       lbl_8008E11C
lbl_8008E0DC:
/* 088B3C 8008E0DC 80BE000C */  lwz     r5, 0xc(r30)
/* 088B40 8008E0E0 3C6000C2 */  lis     r3, 0xc2
/* 088B44 8008E0E4 80810018 */  lwz     r4, 0x18(r1)
/* 088B48 8008E0E8 3803001E */  addi    r0, r3, 0x1e
/* 088B4C 8008E0EC 90A40000 */  stw     r5, 0(r4)
/* 088B50 8008E0F0 80610018 */  lwz     r3, 0x18(r1)
/* 088B54 8008E0F4 90030004 */  stw     r0, 4(r3)
/* 088B58 8008E0F8 48000024 */  b       lbl_8008E11C
lbl_8008E0FC:
/* 088B5C 8008E0FC 80810018 */  lwz     r4, 0x18(r1)
/* 088B60 8008E100 57E309FC */  rlwinm  r3, r31, 1, 7, 0x1e
/* 088B64 8008E104 80A10014 */  lwz     r5, 0x14(r1)
/* 088B68 8008E108 4BF7AD39 */  bl      simulatorReadFLASH
/* 088B6C 8008E10C 2C030000 */  cmpwi   r3, 0
/* 088B70 8008E110 4082000C */  bne     lbl_8008E11C
/* 088B74 8008E114 38600000 */  li      r3, 0
/* 088B78 8008E118 48000008 */  b       lbl_8008E120
lbl_8008E11C:
/* 088B7C 8008E11C 38600001 */  li      r3, 1
lbl_8008E120:
/* 088B80 8008E120 8001002C */  lwz     r0, 0x2c(r1)
/* 088B84 8008E124 83E10024 */  lwz     r31, 0x24(r1)
/* 088B88 8008E128 83C10020 */  lwz     r30, 0x20(r1)
/* 088B8C 8008E12C 7C0803A6 */  mtlr    r0
/* 088B90 8008E130 38210028 */  addi    r1, r1, 0x28
/* 088B94 8008E134 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000EB7D8 800EE758 0010 */
glabel gClassFlash
    .long D_801352F8, 0x00000010, 0x00000000, flashEvent

.section .sdata, "wa"

.balign 8

/* 000F1578 801352F8 0006 */
D_801352F8:
    .asciz "FLASH"
    .balign 4
