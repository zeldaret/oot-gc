glabel rspUndoDCT
/* 079ADC 8007F07C 9421FF00 */  stwu    r1, -0x100(r1)
/* 079AE0 8007F080 BDC100B8 */  stmw    r14, 0xb8(r1)
/* 079AE4 8007F084 3801001C */  addi    r0, r1, 0x1c
/* 079AE8 8007F088 900100A8 */  stw     r0, 0xa8(r1)
/* 079AEC 8007F08C 38000000 */  li      r0, 0
/* 079AF0 8007F090 900100A4 */  stw     r0, 0xa4(r1)
/* 079AF4 8007F094 38000000 */  li      r0, 0
/* 079AF8 8007F098 900100AC */  stw     r0, 0xac(r1)
lbl_8007F09C:
/* 079AFC 8007F09C 800100A8 */  lwz     r0, 0xa8(r1)
/* 079B00 8007F0A0 826100AC */  lwz     r19, 0xac(r1)
/* 079B04 8007F0A4 900100B0 */  stw     r0, 0xb0(r1)
/* 079B08 8007F0A8 38000000 */  li      r0, 0
/* 079B0C 8007F0AC 5672103A */  slwi    r18, r19, 2
/* 079B10 8007F0B0 900100A0 */  stw     r0, 0xa0(r1)
lbl_8007F0B4:
/* 079B14 8007F0B4 38000008 */  li      r0, 8
/* 079B18 8007F0B8 808100B0 */  lwz     r4, 0xb0(r1)
/* 079B1C 8007F0BC 7C0903A6 */  mtctr   r0
/* 079B20 8007F0C0 38130006 */  addi    r0, r19, 6
/* 079B24 8007F0C4 39530007 */  addi    r10, r19, 7
/* 079B28 8007F0C8 540E103A */  slwi    r14, r0, 2
/* 079B2C 8007F0CC 5540103A */  slwi    r0, r10, 2
/* 079B30 8007F0D0 39330001 */  addi    r9, r19, 1
/* 079B34 8007F0D4 900100B4 */  stw     r0, 0xb4(r1)
/* 079B38 8007F0D8 39130002 */  addi    r8, r19, 2
/* 079B3C 8007F0DC 38F30003 */  addi    r7, r19, 3
/* 079B40 8007F0E0 38D30004 */  addi    r6, r19, 4
/* 079B44 8007F0E4 38B30005 */  addi    r5, r19, 5
/* 079B48 8007F0E8 54F1103A */  slwi    r17, r7, 2
/* 079B4C 8007F0EC 54AF103A */  slwi    r15, r5, 2
/* 079B50 8007F0F0 5534103A */  slwi    r20, r9, 2
/* 079B54 8007F0F4 5515103A */  slwi    r21, r8, 2
/* 079B58 8007F0F8 54D0103A */  slwi    r16, r6, 2
/* 079B5C 8007F0FC 38A00000 */  li      r5, 0
/* 079B60 8007F100 38E00000 */  li      r7, 0
lbl_8007F104:
/* 079B64 8007F104 38050008 */  addi    r0, r5, 8
/* 079B68 8007F108 816339A8 */  lwz     r11, 0x39a8(r3)
/* 079B6C 8007F10C 5400103A */  slwi    r0, r0, 2
/* 079B70 8007F110 80C339C8 */  lwz     r6, 0x39c8(r3)
/* 079B74 8007F114 39050010 */  addi    r8, r5, 0x10
/* 079B78 8007F118 7F0B002E */  lwzx    r24, r11, r0
/* 079B7C 8007F11C 5509103A */  slwi    r9, r8, 2
/* 079B80 8007F120 7D4B382E */  lwzx    r10, r11, r7
/* 079B84 8007F124 39050018 */  addi    r8, r5, 0x18
/* 079B88 8007F128 7F8B482E */  lwzx    r28, r11, r9
/* 079B8C 8007F12C 38050020 */  addi    r0, r5, 0x20
/* 079B90 8007F130 7D86902E */  lwzx    r12, r6, r18
/* 079B94 8007F134 5508103A */  slwi    r8, r8, 2
/* 079B98 8007F138 7EE6A02E */  lwzx    r23, r6, r20
/* 079B9C 8007F13C 5400103A */  slwi    r0, r0, 2
/* 079BA0 8007F140 7ECB402E */  lwzx    r22, r11, r8
/* 079BA4 8007F144 39250028 */  addi    r9, r5, 0x28
/* 079BA8 8007F148 7F4B002E */  lwzx    r26, r11, r0
/* 079BAC 8007F14C 39050030 */  addi    r8, r5, 0x30
/* 079BB0 8007F150 7F66A82E */  lwzx    r27, r6, r21
/* 079BB4 8007F154 38050038 */  addi    r0, r5, 0x38
/* 079BB8 8007F158 7F26882E */  lwzx    r25, r6, r17
/* 079BBC 8007F15C 5529103A */  slwi    r9, r9, 2
/* 079BC0 8007F160 7FA6802E */  lwzx    r29, r6, r16
/* 079BC4 8007F164 5400103A */  slwi    r0, r0, 2
/* 079BC8 8007F168 7FCB482E */  lwzx    r30, r11, r9
/* 079BCC 8007F16C 5508103A */  slwi    r8, r8, 2
/* 079BD0 8007F170 7C0B002E */  lwzx    r0, r11, r0
/* 079BD4 8007F174 7D2B402E */  lwzx    r9, r11, r8
/* 079BD8 8007F178 7D4A61D6 */  mullw   r10, r10, r12
/* 079BDC 8007F17C 816100B4 */  lwz     r11, 0xb4(r1)
/* 079BE0 8007F180 7D06702E */  lwzx    r8, r6, r14
/* 079BE4 8007F184 7D86582E */  lwzx    r12, r6, r11
/* 079BE8 8007F188 7FE6782E */  lwzx    r31, r6, r15
/* 079BEC 8007F18C 7CD8B9D6 */  mullw   r6, r24, r23
/* 079BF0 8007F190 7CCA3214 */  add     r6, r10, r6
/* 079BF4 8007F194 7D7CD9D6 */  mullw   r11, r28, r27
/* 079BF8 8007F198 7CC65A14 */  add     r6, r6, r11
/* 079BFC 8007F19C 7D56C9D6 */  mullw   r10, r22, r25
/* 079C00 8007F1A0 7CC65214 */  add     r6, r6, r10
/* 079C04 8007F1A4 7D7AE9D6 */  mullw   r11, r26, r29
/* 079C08 8007F1A8 7D5EF9D6 */  mullw   r10, r30, r31
/* 079C0C 8007F1AC 7CC65A14 */  add     r6, r6, r11
/* 079C10 8007F1B0 7D0941D6 */  mullw   r8, r9, r8
/* 079C14 8007F1B4 7CC65214 */  add     r6, r6, r10
/* 079C18 8007F1B8 7C0061D6 */  mullw   r0, r0, r12
/* 079C1C 8007F1BC 7CC64214 */  add     r6, r6, r8
/* 079C20 8007F1C0 7CC60214 */  add     r6, r6, r0
/* 079C24 8007F1C4 38060800 */  addi    r0, r6, 0x800
/* 079C28 8007F1C8 7C006670 */  srawi   r0, r0, 0xc
/* 079C2C 8007F1CC 7C000734 */  extsh   r0, r0
/* 079C30 8007F1D0 B0040000 */  sth     r0, 0(r4)
/* 079C34 8007F1D4 38840002 */  addi    r4, r4, 2
/* 079C38 8007F1D8 38A50001 */  addi    r5, r5, 1
/* 079C3C 8007F1DC 38E70004 */  addi    r7, r7, 4
/* 079C40 8007F1E0 4200FF24 */  bdnz    lbl_8007F104
/* 079C44 8007F1E4 808100A0 */  lwz     r4, 0xa0(r1)
/* 079C48 8007F1E8 3A730008 */  addi    r19, r19, 8
/* 079C4C 8007F1EC 3A520020 */  addi    r18, r18, 0x20
/* 079C50 8007F1F0 38840001 */  addi    r4, r4, 1
/* 079C54 8007F1F4 908100A0 */  stw     r4, 0xa0(r1)
/* 079C58 8007F1F8 808100B0 */  lwz     r4, 0xb0(r1)
/* 079C5C 8007F1FC 800100A0 */  lwz     r0, 0xa0(r1)
/* 079C60 8007F200 38840010 */  addi    r4, r4, 0x10
/* 079C64 8007F204 2C000008 */  cmpwi   r0, 8
/* 079C68 8007F208 908100B0 */  stw     r4, 0xb0(r1)
/* 079C6C 8007F20C 4180FEA8 */  blt     lbl_8007F0B4
/* 079C70 8007F210 80A100A8 */  lwz     r5, 0xa8(r1)
/* 079C74 8007F214 3A400000 */  li      r18, 0
lbl_8007F218:
/* 079C78 8007F218 38000008 */  li      r0, 8
/* 079C7C 8007F21C 808100AC */  lwz     r4, 0xac(r1)
/* 079C80 8007F220 7C0903A6 */  mtctr   r0
/* 079C84 8007F224 38C00000 */  li      r6, 0
/* 079C88 8007F228 39000000 */  li      r8, 0
lbl_8007F22C:
/* 079C8C 8007F22C 38060008 */  addi    r0, r6, 8
/* 079C90 8007F230 80E339A8 */  lwz     r7, 0x39a8(r3)
/* 079C94 8007F234 540B103A */  slwi    r11, r0, 2
/* 079C98 8007F238 A8050000 */  lha     r0, 0(r5)
/* 079C9C 8007F23C 39260010 */  addi    r9, r6, 0x10
/* 079CA0 8007F240 7D87402E */  lwzx    r12, r7, r8
/* 079CA4 8007F244 5529103A */  slwi    r9, r9, 2
/* 079CA8 8007F248 AAA50010 */  lha     r21, 0x10(r5)
/* 079CAC 8007F24C 39460018 */  addi    r10, r6, 0x18
/* 079CB0 8007F250 7F27582E */  lwzx    r25, r7, r11
/* 079CB4 8007F254 554A103A */  slwi    r10, r10, 2
/* 079CB8 8007F258 AA850020 */  lha     r20, 0x20(r5)
/* 079CBC 8007F25C 39660020 */  addi    r11, r6, 0x20
/* 079CC0 8007F260 7F07482E */  lwzx    r24, r7, r9
/* 079CC4 8007F264 5569103A */  slwi    r9, r11, 2
/* 079CC8 8007F268 AA650030 */  lha     r19, 0x30(r5)
/* 079CCC 8007F26C 39660028 */  addi    r11, r6, 0x28
/* 079CD0 8007F270 7EE7502E */  lwzx    r23, r7, r10
/* 079CD4 8007F274 556A103A */  slwi    r10, r11, 2
/* 079CD8 8007F278 AAC50040 */  lha     r22, 0x40(r5)
/* 079CDC 8007F27C 39660030 */  addi    r11, r6, 0x30
/* 079CE0 8007F280 7F67482E */  lwzx    r27, r7, r9
/* 079CE4 8007F284 5569103A */  slwi    r9, r11, 2
/* 079CE8 8007F288 AB450050 */  lha     r26, 0x50(r5)
/* 079CEC 8007F28C 39660038 */  addi    r11, r6, 0x38
/* 079CF0 8007F290 7FA7502E */  lwzx    r29, r7, r10
/* 079CF4 8007F294 556A103A */  slwi    r10, r11, 2
/* 079CF8 8007F298 AB850060 */  lha     r28, 0x60(r5)
/* 079CFC 8007F29C 7FC7482E */  lwzx    r30, r7, r9
/* 079D00 8007F2A0 7D6061D6 */  mullw   r11, r0, r12
/* 079D04 8007F2A4 A9250070 */  lha     r9, 0x70(r5)
/* 079D08 8007F2A8 7C07502E */  lwzx    r0, r7, r10
/* 079D0C 8007F2AC 83E339C8 */  lwz     r31, 0x39c8(r3)
/* 079D10 8007F2B0 7CF5C9D6 */  mullw   r7, r21, r25
/* 079D14 8007F2B4 7D922214 */  add     r12, r18, r4
/* 079D18 8007F2B8 7D54C1D6 */  mullw   r10, r20, r24
/* 079D1C 8007F2BC 7CEB3A14 */  add     r7, r11, r7
/* 079D20 8007F2C0 7D73B9D6 */  mullw   r11, r19, r23
/* 079D24 8007F2C4 7CE75214 */  add     r7, r7, r10
/* 079D28 8007F2C8 7D56D9D6 */  mullw   r10, r22, r27
/* 079D2C 8007F2CC 7CE75A14 */  add     r7, r7, r11
/* 079D30 8007F2D0 7D7AE9D6 */  mullw   r11, r26, r29
/* 079D34 8007F2D4 7CE75214 */  add     r7, r7, r10
/* 079D38 8007F2D8 7D5CF1D6 */  mullw   r10, r28, r30
/* 079D3C 8007F2DC 7CE75A14 */  add     r7, r7, r11
/* 079D40 8007F2E0 7C0901D6 */  mullw   r0, r9, r0
/* 079D44 8007F2E4 7CE75214 */  add     r7, r7, r10
/* 079D48 8007F2E8 7CE70214 */  add     r7, r7, r0
/* 079D4C 8007F2EC 38074000 */  addi    r0, r7, 0x4000
/* 079D50 8007F2F0 7C007E70 */  srawi   r0, r0, 0xf
/* 079D54 8007F2F4 5587103A */  slwi    r7, r12, 2
/* 079D58 8007F2F8 7C1F392E */  stwx    r0, r31, r7
/* 079D5C 8007F2FC 800339C8 */  lwz     r0, 0x39c8(r3)
/* 079D60 8007F300 7CE03A14 */  add     r7, r0, r7
/* 079D64 8007F304 80070000 */  lwz     r0, 0(r7)
/* 079D68 8007F308 2C000000 */  cmpwi   r0, 0
/* 079D6C 8007F30C 4080000C */  bge     lbl_8007F318
/* 079D70 8007F310 38000000 */  li      r0, 0
/* 079D74 8007F314 90070000 */  stw     r0, 0(r7)
lbl_8007F318:
/* 079D78 8007F318 38840008 */  addi    r4, r4, 8
/* 079D7C 8007F31C 38C60001 */  addi    r6, r6, 1
/* 079D80 8007F320 39080004 */  addi    r8, r8, 4
/* 079D84 8007F324 4200FF08 */  bdnz    lbl_8007F22C
/* 079D88 8007F328 3A520001 */  addi    r18, r18, 1
/* 079D8C 8007F32C 2C120008 */  cmpwi   r18, 8
/* 079D90 8007F330 38A50002 */  addi    r5, r5, 2
/* 079D94 8007F334 4180FEE4 */  blt     lbl_8007F218
/* 079D98 8007F338 808100A4 */  lwz     r4, 0xa4(r1)
/* 079D9C 8007F33C 38840001 */  addi    r4, r4, 1
/* 079DA0 8007F340 908100A4 */  stw     r4, 0xa4(r1)
/* 079DA4 8007F344 808100AC */  lwz     r4, 0xac(r1)
/* 079DA8 8007F348 800100A4 */  lwz     r0, 0xa4(r1)
/* 079DAC 8007F34C 38840040 */  addi    r4, r4, 0x40
/* 079DB0 8007F350 2C000006 */  cmpwi   r0, 6
/* 079DB4 8007F354 908100AC */  stw     r4, 0xac(r1)
/* 079DB8 8007F358 4180FD44 */  blt     lbl_8007F09C
/* 079DBC 8007F35C B9C100B8 */  lmw     r14, 0xb8(r1)
/* 079DC0 8007F360 38210100 */  addi    r1, r1, 0x100
/* 079DC4 8007F364 4E800020 */  blr     
