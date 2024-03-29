# mpc_7xx_603e.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKSaveExtended1Block
/* 0C7AAC 800CD04C 3C408013 */  lis     r2, gTRKCPUState@h
/* 0C7AB0 800CD050 604246A0 */  ori     r2, r2, gTRKCPUState@l
/* 0C7AB4 800CD054 7E0004A6 */  mfsr    r16, 0
/* 0C7AB8 800CD058 7E2104A6 */  mfsr    r17, 1
/* 0C7ABC 800CD05C 7E4204A6 */  mfsr    r18, 2
/* 0C7AC0 800CD060 7E6304A6 */  mfsr    r19, 3
/* 0C7AC4 800CD064 7E8404A6 */  mfsr    r20, 4
/* 0C7AC8 800CD068 7EA504A6 */  mfsr    r21, 5
/* 0C7ACC 800CD06C 7EC604A6 */  mfsr    r22, 6
/* 0C7AD0 800CD070 7EE704A6 */  mfsr    r23, 7
/* 0C7AD4 800CD074 7F0804A6 */  mfsr    r24, 8
/* 0C7AD8 800CD078 7F2904A6 */  mfsr    r25, 9
/* 0C7ADC 800CD07C 7F4A04A6 */  mfsr    r26, 0xa
/* 0C7AE0 800CD080 7F6B04A6 */  mfsr    r27, 0xb
/* 0C7AE4 800CD084 7F8C04A6 */  mfsr    r28, 0xc
/* 0C7AE8 800CD088 7FAD04A6 */  mfsr    r29, 0xd
/* 0C7AEC 800CD08C 7FCE04A6 */  mfsr    r30, 0xe
/* 0C7AF0 800CD090 7FEF04A6 */  mfsr    r31, 0xf
/* 0C7AF4 800CD094 BE0201A8 */  stmw    r16, 0x1a8(r2)
/* 0C7AF8 800CD098 7D4C42E6 */  mftb    r10, 0x10c
/* 0C7AFC 800CD09C 7D6D42E6 */  mftbu   r11
/* 0C7B00 800CD0A0 7D90FAA6 */  mfspr   r12, 0x3f0
/* 0C7B04 800CD0A4 7DB1FAA6 */  mfspr   r13, 0x3f1
/* 0C7B08 800CD0A8 7DDB02A6 */  mfspr   r14, 0x1b
/* 0C7B0C 800CD0AC 7DFF42A6 */  mfpvr   r15
/* 0C7B10 800CD0B0 7E1082A6 */  mfibatu r16, 0
/* 0C7B14 800CD0B4 7E3182A6 */  mfibatl r17, 0
/* 0C7B18 800CD0B8 7E5282A6 */  mfibatu r18, 1
/* 0C7B1C 800CD0BC 7E7382A6 */  mfibatl r19, 1
/* 0C7B20 800CD0C0 7E9482A6 */  mfibatu r20, 2
/* 0C7B24 800CD0C4 7EB582A6 */  mfibatl r21, 2
/* 0C7B28 800CD0C8 7ED682A6 */  mfibatu r22, 3
/* 0C7B2C 800CD0CC 7EF782A6 */  mfibatl r23, 3
/* 0C7B30 800CD0D0 7F1882A6 */  mfdbatu r24, 0
/* 0C7B34 800CD0D4 7F3982A6 */  mfdbatl r25, 0
/* 0C7B38 800CD0D8 7F5A82A6 */  mfdbatu r26, 1
/* 0C7B3C 800CD0DC 7F7B82A6 */  mfdbatl r27, 1
/* 0C7B40 800CD0E0 7F9C82A6 */  mfdbatu r28, 2
/* 0C7B44 800CD0E4 7FBD82A6 */  mfdbatl r29, 2
/* 0C7B48 800CD0E8 7FDE82A6 */  mfdbatu r30, 3
/* 0C7B4C 800CD0EC 7FFF82A6 */  mfdbatl r31, 3
/* 0C7B50 800CD0F0 BD4201E8 */  stmw    r10, 0x1e8(r2)
/* 0C7B54 800CD0F4 7ED902A6 */  mfspr   r22, 0x19
/* 0C7B58 800CD0F8 7EF302A6 */  mfdar   r23
/* 0C7B5C 800CD0FC 7F1202A6 */  mfdsisr r24
/* 0C7B60 800CD100 7F3042A6 */  mfspr   r25, 0x110
/* 0C7B64 800CD104 7F5142A6 */  mfspr   r26, 0x111
/* 0C7B68 800CD108 7F7242A6 */  mfspr   r27, 0x112
/* 0C7B6C 800CD10C 7F9342A6 */  mfspr   r28, 0x113
/* 0C7B70 800CD110 3BA00000 */  li      r29, 0
/* 0C7B74 800CD114 7FD2FAA6 */  mfspr   r30, 0x3f2
/* 0C7B78 800CD118 7FFA42A6 */  mfspr   r31, 0x11a
/* 0C7B7C 800CD11C BEC2025C */  stmw    r22, 0x25c(r2)
/* 0C7B80 800CD120 7E90E2A6 */  mfspr   r20, 0x390
/* 0C7B84 800CD124 7EB1E2A6 */  mfspr   r21, 0x391
/* 0C7B88 800CD128 7ED2E2A6 */  mfspr   r22, 0x392
/* 0C7B8C 800CD12C 7EF3E2A6 */  mfspr   r23, 0x393
/* 0C7B90 800CD130 7F14E2A6 */  mfspr   r24, 0x394
/* 0C7B94 800CD134 7F35E2A6 */  mfspr   r25, 0x395
/* 0C7B98 800CD138 7F56E2A6 */  mfspr   r26, 0x396
/* 0C7B9C 800CD13C 7F77E2A6 */  mfspr   r27, 0x397
/* 0C7BA0 800CD140 7F98E2A6 */  mfspr   r28, 0x398
/* 0C7BA4 800CD144 7FB9E2A6 */  mfspr   r29, 0x399
/* 0C7BA8 800CD148 7FDAE2A6 */  mfspr   r30, 0x39a
/* 0C7BAC 800CD14C 7FFBE2A6 */  mfspr   r31, 0x39b
/* 0C7BB0 800CD150 BE8202FC */  stmw    r20, 0x2fc(r2)
/* 0C7BB4 800CD154 48000048 */  b       lbl_800CD19C
/* 0C7BB8 800CD158 7E00EAA6 */  mfspr   r16, 0x3a0
/* 0C7BBC 800CD15C 7E27EAA6 */  mfspr   r17, 0x3a7
/* 0C7BC0 800CD160 7E48EAA6 */  mfspr   r18, 0x3a8
/* 0C7BC4 800CD164 7E69EAA6 */  mfspr   r19, 0x3a9
/* 0C7BC8 800CD168 7E8AEAA6 */  mfspr   r20, 0x3aa
/* 0C7BCC 800CD16C 7EABEAA6 */  mfspr   r21, 0x3ab
/* 0C7BD0 800CD170 7ECCEAA6 */  mfspr   r22, 0x3ac
/* 0C7BD4 800CD174 7EEDEAA6 */  mfspr   r23, 0x3ad
/* 0C7BD8 800CD178 7F0EEAA6 */  mfspr   r24, 0x3ae
/* 0C7BDC 800CD17C 7F2FEAA6 */  mfspr   r25, 0x3af
/* 0C7BE0 800CD180 7F50EAA6 */  mfspr   r26, 0x3b0
/* 0C7BE4 800CD184 7F77EAA6 */  mfspr   r27, 0x3b7
/* 0C7BE8 800CD188 7F9FEAA6 */  mfspr   r28, 0x3bf
/* 0C7BEC 800CD18C 7FB6FAA6 */  mfspr   r29, 0x3f6
/* 0C7BF0 800CD190 7FD7FAA6 */  mfspr   r30, 0x3f7
/* 0C7BF4 800CD194 7FFFFAA6 */  mfspr   r31, 0x3ff
/* 0C7BF8 800CD198 BE0202B8 */  stmw    r16, 0x2b8(r2)
lbl_800CD19C:
/* 0C7BFC 800CD19C 7E75FAA6 */  mfspr   r19, 0x3f5
/* 0C7C00 800CD1A0 7E99EAA6 */  mfspr   r20, 0x3b9
/* 0C7C04 800CD1A4 7EBAEAA6 */  mfspr   r21, 0x3ba
/* 0C7C08 800CD1A8 7EDDEAA6 */  mfspr   r22, 0x3bd
/* 0C7C0C 800CD1AC 7EFEEAA6 */  mfspr   r23, 0x3be
/* 0C7C10 800CD1B0 7F1BEAA6 */  mfspr   r24, 0x3bb
/* 0C7C14 800CD1B4 7F38EAA6 */  mfspr   r25, 0x3b8
/* 0C7C18 800CD1B8 7F5CEAA6 */  mfspr   r26, 0x3bc
/* 0C7C1C 800CD1BC 7F7CFAA6 */  mfspr   r27, 0x3fc
/* 0C7C20 800CD1C0 7F9DFAA6 */  mfspr   r28, 0x3fd
/* 0C7C24 800CD1C4 7FBEFAA6 */  mfspr   r29, 0x3fe
/* 0C7C28 800CD1C8 7FDBFAA6 */  mfspr   r30, 0x3FB
/* 0C7C2C 800CD1CC 7FF9FAA6 */  mfspr   r31, 0x3f9
/* 0C7C30 800CD1D0 BE620284 */  stmw    r19, 0x284(r2)
/* 0C7C34 800CD1D4 4800002C */  b       lbl_800CD200
/* 0C7C38 800CD1D8 7F30F2A6 */  mfspr   r25, 0x3d0
/* 0C7C3C 800CD1DC 7F51F2A6 */  mfspr   r26, 0x3d1
/* 0C7C40 800CD1E0 7F72F2A6 */  mfspr   r27, 0x3d2
/* 0C7C44 800CD1E4 7F93F2A6 */  mfspr   r28, 0x3d3
/* 0C7C48 800CD1E8 7FB4F2A6 */  mfspr   r29, 0x3D4
/* 0C7C4C 800CD1EC 7FD5F2A6 */  mfspr   r30, 0x3D5
/* 0C7C50 800CD1F0 7FF6F2A6 */  mfspr   r31, 0x3d6
/* 0C7C54 800CD1F4 BF220240 */  stmw    r25, 0x240(r2)
/* 0C7C58 800CD1F8 7FF602A6 */  mfspr   r31, 0x16
/* 0C7C5C 800CD1FC 93E20278 */  stw     r31, 0x278(r2)
lbl_800CD200:
/* 0C7C60 800CD200 4E800020 */  blr     

glabel TRKRestoreExtended1Block
/* 0C7C64 800CD204 3C408013 */  lis     r2, gTRKCPUState@h
/* 0C7C68 800CD208 604246A0 */  ori     r2, r2, gTRKCPUState@l
/* 0C7C6C 800CD20C 3CA0800F */  lis     r5, gTRKRestoreFlags@h
/* 0C7C70 800CD210 60A53AA8 */  ori     r5, r5, gTRKRestoreFlags@l
/* 0C7C74 800CD214 88650000 */  lbz     r3, 0(r5)
/* 0C7C78 800CD218 88C50001 */  lbz     r6, 1(r5)
/* 0C7C7C 800CD21C 38000000 */  li      r0, 0
/* 0C7C80 800CD220 98050000 */  stb     r0, 0(r5)
/* 0C7C84 800CD224 98050001 */  stb     r0, 1(r5)
/* 0C7C88 800CD228 2C030000 */  cmpwi   r3, 0
/* 0C7C8C 800CD22C 41820014 */  beq     lbl_800CD240
/* 0C7C90 800CD230 830201E8 */  lwz     r24, 0x1e8(r2)
/* 0C7C94 800CD234 832201EC */  lwz     r25, 0x1ec(r2)
/* 0C7C98 800CD238 7F1C43A6 */  mttbl   r24
/* 0C7C9C 800CD23C 7F3D43A6 */  mttbu   r25
lbl_800CD240:
/* 0C7CA0 800CD240 BA8202FC */  lmw     r20, 0x2fc(r2)
/* 0C7CA4 800CD244 7E90E3A6 */  mtspr   0x390, r20
/* 0C7CA8 800CD248 7EB1E3A6 */  mtspr   0x391, r21
/* 0C7CAC 800CD24C 7ED2E3A6 */  mtspr   0x392, r22
/* 0C7CB0 800CD250 7EF3E3A6 */  mtspr   0x393, r23
/* 0C7CB4 800CD254 7F14E3A6 */  mtspr   0x394, r24
/* 0C7CB8 800CD258 7F35E3A6 */  mtspr   0x395, r25
/* 0C7CBC 800CD25C 7F56E3A6 */  mtspr   0x396, r26
/* 0C7CC0 800CD260 7F77E3A6 */  mtspr   0x397, r27
/* 0C7CC4 800CD264 7F98E3A6 */  mtspr   0x398, r28
/* 0C7CC8 800CD268 7FDAE3A6 */  mtspr   0x39a, r30
/* 0C7CCC 800CD26C 7FFBE3A6 */  mtspr   0x39b, r31
/* 0C7CD0 800CD270 4800001C */  b       lbl_800CD28C
/* 0C7CD4 800CD274 BB4202E0 */  lmw     r26, 0x2e0(r2)
/* 0C7CD8 800CD278 7F50EBA6 */  mtspr   0x3b0, r26
/* 0C7CDC 800CD27C 7F77EBA6 */  mtspr   0x3b7, r27
/* 0C7CE0 800CD280 7FB6FBA6 */  mtspr   0x3f6, r29
/* 0C7CE4 800CD284 7FD7FBA6 */  mtspr   0x3f7, r30
/* 0C7CE8 800CD288 7FFFFBA6 */  mtspr   0x3ff, r31
lbl_800CD28C:
/* 0C7CEC 800CD28C BA620284 */  lmw     r19, 0x284(r2)
/* 0C7CF0 800CD290 7E75FBA6 */  mtspr   0x3f5, r19
/* 0C7CF4 800CD294 7E99EBA6 */  mtspr   0x3b9, r20
/* 0C7CF8 800CD298 7EBAEBA6 */  mtspr   0x3ba, r21
/* 0C7CFC 800CD29C 7EDDEBA6 */  mtspr   0x3bd, r22
/* 0C7D00 800CD2A0 7EFEEBA6 */  mtspr   0x3be, r23
/* 0C7D04 800CD2A4 7F1BEBA6 */  mtspr   0x3bb, r24
/* 0C7D08 800CD2A8 7F38EBA6 */  mtspr   0x3b8, r25
/* 0C7D0C 800CD2AC 7F5CEBA6 */  mtspr   0x3bc, r26
/* 0C7D10 800CD2B0 7F7CFBA6 */  mtspr   0x3fc, r27
/* 0C7D14 800CD2B4 7F9DFBA6 */  mtspr   0x3fd, r28
/* 0C7D18 800CD2B8 7FBEFBA6 */  mtspr   0x3fe, r29
/* 0C7D1C 800CD2BC 7FDBFBA6 */  mtictc  r30
/* 0C7D20 800CD2C0 7FF9FBA6 */  mtspr   0x3f9, r31
/* 0C7D24 800CD2C4 48000034 */  b       lbl_800CD2F8
/* 0C7D28 800CD2C8 2C060000 */  cmpwi   r6, 0
/* 0C7D2C 800CD2CC 4182000C */  beq     lbl_800CD2D8
/* 0C7D30 800CD2D0 83420278 */  lwz     r26, 0x278(r2)
/* 0C7D34 800CD2D4 7F5603A6 */  mtspr   0x16, r26
lbl_800CD2D8:
/* 0C7D38 800CD2D8 BB220240 */  lmw     r25, 0x240(r2)
/* 0C7D3C 800CD2DC 7F30F3A6 */  mtspr   0x3d0, r25
/* 0C7D40 800CD2E0 7F51F3A6 */  mtspr   0x3d1, r26
/* 0C7D44 800CD2E4 7F72F3A6 */  mtspr   0x3d2, r27
/* 0C7D48 800CD2E8 7F93F3A6 */  mtspr   0x3d3, r28
/* 0C7D4C 800CD2EC 7FB4F3A6 */  mtspr   0x3D4, r29
/* 0C7D50 800CD2F0 7FD5F3A6 */  mtspr   0x3D5, r30
/* 0C7D54 800CD2F4 7FF6F3A6 */  mtspr   0x3d6, r31
lbl_800CD2F8:
/* 0C7D58 800CD2F8 BA0201A8 */  lmw     r16, 0x1a8(r2)
/* 0C7D5C 800CD2FC 7E0001A4 */  mtsr    0, r16
/* 0C7D60 800CD300 7E2101A4 */  mtsr    1, r17
/* 0C7D64 800CD304 7E4201A4 */  mtsr    2, r18
/* 0C7D68 800CD308 7E6301A4 */  mtsr    3, r19
/* 0C7D6C 800CD30C 7E8401A4 */  mtsr    4, r20
/* 0C7D70 800CD310 7EA501A4 */  mtsr    5, r21
/* 0C7D74 800CD314 7EC601A4 */  mtsr    6, r22
/* 0C7D78 800CD318 7EE701A4 */  mtsr    7, r23
/* 0C7D7C 800CD31C 7F0801A4 */  mtsr    8, r24
/* 0C7D80 800CD320 7F2901A4 */  mtsr    9, r25
/* 0C7D84 800CD324 7F4A01A4 */  mtsr    0xa, r26
/* 0C7D88 800CD328 7F6B01A4 */  mtsr    0xb, r27
/* 0C7D8C 800CD32C 7F8C01A4 */  mtsr    0xc, r28
/* 0C7D90 800CD330 7FAD01A4 */  mtsr    0xd, r29
/* 0C7D94 800CD334 7FCE01A4 */  mtsr    0xe, r30
/* 0C7D98 800CD338 7FEF01A4 */  mtsr    0xf, r31
/* 0C7D9C 800CD33C B98201F0 */  lmw     r12, 0x1f0(r2)
/* 0C7DA0 800CD340 7D90FBA6 */  mtspr   0x3f0, r12
/* 0C7DA4 800CD344 7DB1FBA6 */  mtspr   0x3f1, r13
/* 0C7DA8 800CD348 7DDB03A6 */  mtspr   0x1b, r14
/* 0C7DAC 800CD34C 7DFF43A6 */  mtspr   0x11f, r15
/* 0C7DB0 800CD350 7E1083A6 */  mtibatu 0, r16
/* 0C7DB4 800CD354 7E3183A6 */  mtibatl 0, r17
/* 0C7DB8 800CD358 7E5283A6 */  mtibatu 1, r18
/* 0C7DBC 800CD35C 7E7383A6 */  mtibatl 1, r19
/* 0C7DC0 800CD360 7E9483A6 */  mtibatu 2, r20
/* 0C7DC4 800CD364 7EB583A6 */  mtibatl 2, r21
/* 0C7DC8 800CD368 7ED683A6 */  mtibatu 3, r22
/* 0C7DCC 800CD36C 7EF783A6 */  mtibatl 3, r23
/* 0C7DD0 800CD370 7F1883A6 */  mtdbatu 0, r24
/* 0C7DD4 800CD374 7F3983A6 */  mtdbatl 0, r25
/* 0C7DD8 800CD378 7F5A83A6 */  mtdbatu 1, r26
/* 0C7DDC 800CD37C 7F7B83A6 */  mtdbatl 1, r27
/* 0C7DE0 800CD380 7F9C83A6 */  mtdbatu 2, r28
/* 0C7DE4 800CD384 7FBD83A6 */  mtdbatl 2, r29
/* 0C7DE8 800CD388 7FDE83A6 */  mtdbatu 3, r30
/* 0C7DEC 800CD38C 7FFF83A6 */  mtdbatl 3, r31
/* 0C7DF0 800CD390 BAC2025C */  lmw     r22, 0x25c(r2)
/* 0C7DF4 800CD394 7ED903A6 */  mtspr   0x19, r22
/* 0C7DF8 800CD398 7EF303A6 */  mtdar   r23
/* 0C7DFC 800CD39C 7F1203A6 */  mtdsisr r24
/* 0C7E00 800CD3A0 7F3043A6 */  mtspr   0x110, r25
/* 0C7E04 800CD3A4 7F5143A6 */  mtspr   0x111, r26
/* 0C7E08 800CD3A8 7F7243A6 */  mtspr   0x112, r27
/* 0C7E0C 800CD3AC 7F9343A6 */  mtspr   0x113, r28
/* 0C7E10 800CD3B0 7FD2FBA6 */  mtspr   0x3f2, r30
/* 0C7E14 800CD3B4 7FFA43A6 */  mtspr   0x11a, r31
/* 0C7E18 800CD3B8 4E800020 */  blr     
