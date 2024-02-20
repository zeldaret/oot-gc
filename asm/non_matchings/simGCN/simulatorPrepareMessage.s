glabel simulatorPrepareMessage
/* 007C50 8000D1F0 7C0802A6 */  mflr    r0
/* 007C54 8000D1F4 3C80800E */  lis     r4, gcoverOpen@ha
/* 007C58 8000D1F8 90010004 */  stw     r0, 4(r1)
/* 007C5C 8000D1FC 2C030019 */  cmpwi   r3, 0x19
/* 007C60 8000D200 3CA0800F */  lis     r5, gOrthoMtx@ha
/* 007C64 8000D204 9421FFB0 */  stwu    r1, -0x50(r1)
/* 007C68 8000D208 3884B800 */  addi    r4, r4, gcoverOpen@l
/* 007C6C 8000D20C 93E1004C */  stw     r31, 0x4c(r1)
/* 007C70 8000D210 3BE54540 */  addi    r31, r5, gOrthoMtx@l
/* 007C74 8000D214 41820020 */  beq     lbl_8000D234
/* 007C78 8000D218 40800010 */  bge     lbl_8000D228
/* 007C7C 8000D21C 2C030013 */  cmpwi   r3, 0x13
/* 007C80 8000D220 418200CC */  beq     lbl_8000D2EC
/* 007C84 8000D224 48000120 */  b       lbl_8000D344
lbl_8000D228:
/* 007C88 8000D228 2C03002A */  cmpwi   r3, 0x2a
/* 007C8C 8000D22C 41820064 */  beq     lbl_8000D290
/* 007C90 8000D230 48000114 */  b       lbl_8000D344
lbl_8000D234:
/* 007C94 8000D234 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007C98 8000D238 7C001800 */  cmpw    r0, r3
/* 007C9C 8000D23C 41820108 */  beq     lbl_8000D344
/* 007CA0 8000D240 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007CA4 8000D244 3C640001 */  addis   r3, r4, 1
/* 007CA8 8000D248 3863E914 */  addi    r3, r3, -5868
/* 007CAC 8000D24C 3881000C */  addi    r4, r1, 0xc
/* 007CB0 8000D250 480A57E5 */  bl      DVDOpen
/* 007CB4 8000D254 2C030001 */  cmpwi   r3, 1
/* 007CB8 8000D258 40820024 */  bne     lbl_8000D27C
/* 007CBC 8000D25C 80AD8050 */  lwz     r5, gmsg_in02Size@sda21(r13)
/* 007CC0 8000D260 3861000C */  addi    r3, r1, 0xc
/* 007CC4 8000D264 389F01A0 */  addi    r4, r31, 0x1a0
/* 007CC8 8000D268 3805001F */  addi    r0, r5, 0x1f
/* 007CCC 8000D26C 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 007CD0 8000D270 38C00000 */  li      r6, 0
/* 007CD4 8000D274 38E00000 */  li      r7, 0
/* 007CD8 8000D278 48001A4D */  bl      simulatorDVDRead
lbl_8000D27C:
/* 007CDC 8000D27C 3861000C */  addi    r3, r1, 0xc
/* 007CE0 8000D280 480A587D */  bl      DVDClose
/* 007CE4 8000D284 387F01A0 */  addi    r3, r31, 0x1a0
/* 007CE8 8000D288 48001D99 */  bl      simulatorUnpackTexPalette
/* 007CEC 8000D28C 480000B8 */  b       lbl_8000D344
lbl_8000D290:
/* 007CF0 8000D290 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007CF4 8000D294 7C001800 */  cmpw    r0, r3
/* 007CF8 8000D298 418200AC */  beq     lbl_8000D344
/* 007CFC 8000D29C 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007D00 8000D2A0 3C640001 */  addis   r3, r4, 1
/* 007D04 8000D2A4 3863E928 */  addi    r3, r3, -5848
/* 007D08 8000D2A8 3881000C */  addi    r4, r1, 0xc
/* 007D0C 8000D2AC 480A5789 */  bl      DVDOpen
/* 007D10 8000D2B0 2C030001 */  cmpwi   r3, 1
/* 007D14 8000D2B4 40820024 */  bne     lbl_8000D2D8
/* 007D18 8000D2B8 80AD8094 */  lwz     r5, gmsg_sv09Size@sda21(r13)
/* 007D1C 8000D2BC 3861000C */  addi    r3, r1, 0xc
/* 007D20 8000D2C0 389F01A0 */  addi    r4, r31, 0x1a0
/* 007D24 8000D2C4 3805001F */  addi    r0, r5, 0x1f
/* 007D28 8000D2C8 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 007D2C 8000D2CC 38C00000 */  li      r6, 0
/* 007D30 8000D2D0 38E00000 */  li      r7, 0
/* 007D34 8000D2D4 480019F1 */  bl      simulatorDVDRead
lbl_8000D2D8:
/* 007D38 8000D2D8 3861000C */  addi    r3, r1, 0xc
/* 007D3C 8000D2DC 480A5821 */  bl      DVDClose
/* 007D40 8000D2E0 387F01A0 */  addi    r3, r31, 0x1a0
/* 007D44 8000D2E4 48001D3D */  bl      simulatorUnpackTexPalette
/* 007D48 8000D2E8 4800005C */  b       lbl_8000D344
lbl_8000D2EC:
/* 007D4C 8000D2EC 800D80B4 */  lwz     r0, simulatorMessageCurrent@sda21(r13)
/* 007D50 8000D2F0 7C001800 */  cmpw    r0, r3
/* 007D54 8000D2F4 41820050 */  beq     lbl_8000D344
/* 007D58 8000D2F8 906D80B4 */  stw     r3, simulatorMessageCurrent@sda21(r13)
/* 007D5C 8000D2FC 3C640001 */  addis   r3, r4, 1
/* 007D60 8000D300 3863E93C */  addi    r3, r3, -5828
/* 007D64 8000D304 3881000C */  addi    r4, r1, 0xc
/* 007D68 8000D308 480A572D */  bl      DVDOpen
/* 007D6C 8000D30C 2C030001 */  cmpwi   r3, 1
/* 007D70 8000D310 40820024 */  bne     lbl_8000D334
/* 007D74 8000D314 80AD8038 */  lwz     r5, gmsg_gf02Size@sda21(r13)
/* 007D78 8000D318 3861000C */  addi    r3, r1, 0xc
/* 007D7C 8000D31C 389F01A0 */  addi    r4, r31, 0x1a0
/* 007D80 8000D320 3805001F */  addi    r0, r5, 0x1f
/* 007D84 8000D324 54050034 */  rlwinm  r5, r0, 0, 0, 0x1a
/* 007D88 8000D328 38C00000 */  li      r6, 0
/* 007D8C 8000D32C 38E00000 */  li      r7, 0
/* 007D90 8000D330 48001995 */  bl      simulatorDVDRead
lbl_8000D334:
/* 007D94 8000D334 3861000C */  addi    r3, r1, 0xc
/* 007D98 8000D338 480A57C5 */  bl      DVDClose
/* 007D9C 8000D33C 387F01A0 */  addi    r3, r31, 0x1a0
/* 007DA0 8000D340 48001CE1 */  bl      simulatorUnpackTexPalette
lbl_8000D344:
/* 007DA4 8000D344 80010054 */  lwz     r0, 0x54(r1)
/* 007DA8 8000D348 38600001 */  li      r3, 1
/* 007DAC 8000D34C 83E1004C */  lwz     r31, 0x4c(r1)
/* 007DB0 8000D350 38210050 */  addi    r1, r1, 0x50
/* 007DB4 8000D354 7C0803A6 */  mtlr    r0
/* 007DB8 8000D358 4E800020 */  blr     
