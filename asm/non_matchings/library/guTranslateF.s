glabel guTranslateF
/* 08EBD4 80094174 7C0802A6 */  mflr    r0
/* 08EBD8 80094178 90010004 */  stw     r0, 4(r1)
/* 08EBDC 8009417C 9421FFD0 */  stwu    r1, -0x30(r1)
/* 08EBE0 80094180 93E1002C */  stw     r31, 0x2c(r1)
/* 08EBE4 80094184 7C7F1B78 */  mr      r31, r3
/* 08EBE8 80094188 38810020 */  addi    r4, r1, 0x20
/* 08EBEC 8009418C C0028388 */  lfs     f0, D_80136088@sda21(r2)
/* 08EBF0 80094190 D001001C */  stfs    f0, 0x1c(r1)
/* 08EBF4 80094194 C00283A4 */  lfs     f0, D_801360A4@sda21(r2)
/* 08EBF8 80094198 D0010014 */  stfs    f0, 0x14(r1)
/* 08EBFC 8009419C 80BF0064 */  lwz     r5, 0x64(r31)
/* 08EC00 800941A0 4BFA05E1 */  bl      cpuGetAddressBuffer
/* 08EC04 800941A4 38000004 */  li      r0, 4
/* 08EC08 800941A8 80E10014 */  lwz     r7, 0x14(r1)
/* 08EC0C 800941AC 7C0903A6 */  mtctr   r0
/* 08EC10 800941B0 8001001C */  lwz     r0, 0x1c(r1)
/* 08EC14 800941B4 39000000 */  li      r8, 0
/* 08EC18 800941B8 38C00000 */  li      r6, 0
lbl_800941BC:
/* 08EC1C 800941BC 38800000 */  li      r4, 0
/* 08EC20 800941C0 7C082000 */  cmpw    r8, r4
/* 08EC24 800941C4 54C3103A */  slwi    r3, r6, 2
/* 08EC28 800941C8 40820010 */  bne     lbl_800941D8
/* 08EC2C 800941CC 80810020 */  lwz     r4, 0x20(r1)
/* 08EC30 800941D0 7CE4192E */  stwx    r7, r4, r3
/* 08EC34 800941D4 4800000C */  b       lbl_800941E0
lbl_800941D8:
/* 08EC38 800941D8 80810020 */  lwz     r4, 0x20(r1)
/* 08EC3C 800941DC 7C04192E */  stwx    r0, r4, r3
lbl_800941E0:
/* 08EC40 800941E0 38800001 */  li      r4, 1
/* 08EC44 800941E4 7C082000 */  cmpw    r8, r4
/* 08EC48 800941E8 38630004 */  addi    r3, r3, 4
/* 08EC4C 800941EC 40820010 */  bne     lbl_800941FC
/* 08EC50 800941F0 80810020 */  lwz     r4, 0x20(r1)
/* 08EC54 800941F4 7CE4192E */  stwx    r7, r4, r3
/* 08EC58 800941F8 4800000C */  b       lbl_80094204
lbl_800941FC:
/* 08EC5C 800941FC 80810020 */  lwz     r4, 0x20(r1)
/* 08EC60 80094200 7C04192E */  stwx    r0, r4, r3
lbl_80094204:
/* 08EC64 80094204 38800002 */  li      r4, 2
/* 08EC68 80094208 7C082000 */  cmpw    r8, r4
/* 08EC6C 8009420C 38A60001 */  addi    r5, r6, 1
/* 08EC70 80094210 38630004 */  addi    r3, r3, 4
/* 08EC74 80094214 40820010 */  bne     lbl_80094224
/* 08EC78 80094218 80810020 */  lwz     r4, 0x20(r1)
/* 08EC7C 8009421C 7CE4192E */  stwx    r7, r4, r3
/* 08EC80 80094220 4800000C */  b       lbl_8009422C
lbl_80094224:
/* 08EC84 80094224 80810020 */  lwz     r4, 0x20(r1)
/* 08EC88 80094228 7C04192E */  stwx    r0, r4, r3
lbl_8009422C:
/* 08EC8C 8009422C 38800003 */  li      r4, 3
/* 08EC90 80094230 7C082000 */  cmpw    r8, r4
/* 08EC94 80094234 38630004 */  addi    r3, r3, 4
/* 08EC98 80094238 40820010 */  bne     lbl_80094248
/* 08EC9C 8009423C 80810020 */  lwz     r4, 0x20(r1)
/* 08ECA0 80094240 7CE4192E */  stwx    r7, r4, r3
/* 08ECA4 80094244 4800000C */  b       lbl_80094250
lbl_80094248:
/* 08ECA8 80094248 80810020 */  lwz     r4, 0x20(r1)
/* 08ECAC 8009424C 7C04192E */  stwx    r0, r4, r3
lbl_80094250:
/* 08ECB0 80094250 38C60004 */  addi    r6, r6, 4
/* 08ECB4 80094254 39080001 */  addi    r8, r8, 1
/* 08ECB8 80094258 4200FF64 */  bdnz    lbl_800941BC
/* 08ECBC 8009425C 801F006C */  lwz     r0, 0x6c(r31)
/* 08ECC0 80094260 80610020 */  lwz     r3, 0x20(r1)
/* 08ECC4 80094264 90030030 */  stw     r0, 0x30(r3)
/* 08ECC8 80094268 801F0074 */  lwz     r0, 0x74(r31)
/* 08ECCC 8009426C 80610020 */  lwz     r3, 0x20(r1)
/* 08ECD0 80094270 90030034 */  stw     r0, 0x34(r3)
/* 08ECD4 80094274 801F007C */  lwz     r0, 0x7c(r31)
/* 08ECD8 80094278 80610020 */  lwz     r3, 0x20(r1)
/* 08ECDC 8009427C 90030038 */  stw     r0, 0x38(r3)
/* 08ECE0 80094280 80010034 */  lwz     r0, 0x34(r1)
/* 08ECE4 80094284 83E1002C */  lwz     r31, 0x2c(r1)
/* 08ECE8 80094288 38210030 */  addi    r1, r1, 0x30
/* 08ECEC 8009428C 7C0803A6 */  mtlr    r0
/* 08ECF0 80094290 4E800020 */  blr     
