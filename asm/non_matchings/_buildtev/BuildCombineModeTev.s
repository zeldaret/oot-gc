glabel BuildCombineModeTev
/* 093104 800986A4 7C0802A6 */  mflr    r0
/* 093108 800986A8 3D008013 */  lis     r8, tevStages@ha
/* 09310C 800986AC 90010004 */  stw     r0, 4(r1)
/* 093110 800986B0 38000057 */  li      r0, 0x57
/* 093114 800986B4 7C0903A6 */  mtctr   r0
/* 093118 800986B8 38000000 */  li      r0, 0
/* 09311C 800986BC 9421FF98 */  stwu    r1, -0x68(r1)
/* 093120 800986C0 BE810038 */  stmw    r20, 0x38(r1)
/* 093124 800986C4 3BE80C50 */  addi    r31, r8, tevStages@l
/* 093128 800986C8 3B430000 */  addi    r26, r3, 0
/* 09312C 800986CC 3B640000 */  addi    r27, r4, 0
/* 093130 800986D0 3B850000 */  addi    r28, r5, 0
/* 093134 800986D4 3BA60000 */  addi    r29, r6, 0
/* 093138 800986D8 3BC70000 */  addi    r30, r7, 0
/* 09313C 800986DC 387F0000 */  addi    r3, r31, 0
lbl_800986E0:
/* 093140 800986E0 98030000 */  stb     r0, 0(r3)
/* 093144 800986E4 98030001 */  stb     r0, 1(r3)
/* 093148 800986E8 98030002 */  stb     r0, 2(r3)
/* 09314C 800986EC 98030003 */  stb     r0, 3(r3)
/* 093150 800986F0 98030004 */  stb     r0, 4(r3)
/* 093154 800986F4 98030005 */  stb     r0, 5(r3)
/* 093158 800986F8 98030006 */  stb     r0, 6(r3)
/* 09315C 800986FC 98030007 */  stb     r0, 7(r3)
/* 093160 80098700 38630008 */  addi    r3, r3, 8
/* 093164 80098704 4200FFDC */  bdnz    lbl_800986E0
/* 093168 80098708 3A800000 */  li      r20, 0
/* 09316C 8009870C 56802036 */  slwi    r0, r20, 4
/* 093170 80098710 3C80800F */  lis     r4, sUsualCArgs@ha
/* 093174 80098714 3C60800F */  lis     r3, sUsualAArgs@ha
/* 093178 80098718 3ADF0000 */  addi    r22, r31, 0
/* 09317C 8009871C 7EBF0214 */  add     r21, r31, r0
/* 093180 80098720 3B040518 */  addi    r24, r4, sUsualCArgs@l
/* 093184 80098724 3B230528 */  addi    r25, r3, sUsualAArgs@l
/* 093188 80098728 3AE000FF */  li      r23, 0xff
lbl_8009872C:
/* 09318C 8009872C 92F60018 */  stw     r23, 0x18(r22)
/* 093190 80098730 38980000 */  addi    r4, r24, 0
/* 093194 80098734 387501B8 */  addi    r3, r21, 0x1b8
/* 093198 80098738 92F6001C */  stw     r23, 0x1c(r22)
/* 09319C 8009873C 38A00010 */  li      r5, 0x10
/* 0931A0 80098740 92F60020 */  stw     r23, 0x20(r22)
/* 0931A4 80098744 4BF6E3AD */  bl      xlHeapCopy
/* 0931A8 80098748 38990000 */  addi    r4, r25, 0
/* 0931AC 8009874C 38750238 */  addi    r3, r21, 0x238
/* 0931B0 80098750 38A00010 */  li      r5, 0x10
/* 0931B4 80098754 4BF6E39D */  bl      xlHeapCopy
/* 0931B8 80098758 3A940001 */  addi    r20, r20, 1
/* 0931BC 8009875C 2C140008 */  cmpwi   r20, 8
/* 0931C0 80098760 3AD6000C */  addi    r22, r22, 0xc
/* 0931C4 80098764 3AB50010 */  addi    r21, r21, 0x10
/* 0931C8 80098768 4180FFC4 */  blt     lbl_8009872C
/* 0931CC 8009876C 9BDF0010 */  stb     r30, 0x10(r31)
/* 0931D0 80098770 389A0000 */  addi    r4, r26, 0
/* 0931D4 80098774 38610028 */  addi    r3, r1, 0x28
/* 0931D8 80098778 935F0000 */  stw     r26, 0(r31)
/* 0931DC 8009877C 38A00001 */  li      r5, 1
/* 0931E0 80098780 937F0004 */  stw     r27, 4(r31)
/* 0931E4 80098784 48003191 */  bl      SetColor
/* 0931E8 80098788 389B0000 */  addi    r4, r27, 0
/* 0931EC 8009878C 38DA0000 */  addi    r6, r26, 0
/* 0931F0 80098790 38FC0000 */  addi    r7, r28, 0
/* 0931F4 80098794 391D0000 */  addi    r8, r29, 0
/* 0931F8 80098798 3861002C */  addi    r3, r1, 0x2c
/* 0931FC 8009879C 38A00001 */  li      r5, 1
/* 093200 800987A0 4800303D */  bl      SetAlpha
/* 093204 800987A4 281E0002 */  cmplwi  r30, 2
/* 093208 800987A8 40820038 */  bne     lbl_800987E0
/* 09320C 800987AC 939F0008 */  stw     r28, 8(r31)
/* 093210 800987B0 389C0000 */  addi    r4, r28, 0
/* 093214 800987B4 38610030 */  addi    r3, r1, 0x30
/* 093218 800987B8 93BF000C */  stw     r29, 0xc(r31)
/* 09321C 800987BC 38A00002 */  li      r5, 2
/* 093220 800987C0 48003155 */  bl      SetColor
/* 093224 800987C4 389D0000 */  addi    r4, r29, 0
/* 093228 800987C8 38DA0000 */  addi    r6, r26, 0
/* 09322C 800987CC 38FC0000 */  addi    r7, r28, 0
/* 093230 800987D0 391D0000 */  addi    r8, r29, 0
/* 093234 800987D4 38610034 */  addi    r3, r1, 0x34
/* 093238 800987D8 38A00002 */  li      r5, 2
/* 09323C 800987DC 48003001 */  bl      SetAlpha
lbl_800987E0:
/* 093240 800987E0 38610028 */  addi    r3, r1, 0x28
/* 093244 800987E4 38800000 */  li      r4, 0
/* 093248 800987E8 48000228 */  b       lbl_80098A10
lbl_800987EC:
/* 09324C 800987EC 38000002 */  li      r0, 2
/* 093250 800987F0 7C0903A6 */  mtctr   r0
/* 093254 800987F4 38A30000 */  addi    r5, r3, 0
/* 093258 800987F8 38C00000 */  li      r6, 0
lbl_800987FC:
/* 09325C 800987FC 88050000 */  lbz     r0, 0(r5)
/* 093260 80098800 28000003 */  cmplwi  r0, 3
/* 093264 80098804 40820014 */  bne     lbl_80098818
/* 093268 80098808 801F0014 */  lwz     r0, 0x14(r31)
/* 09326C 8009880C 60000002 */  ori     r0, r0, 2
/* 093270 80098810 901F0014 */  stw     r0, 0x14(r31)
/* 093274 80098814 48000078 */  b       lbl_8009888C
lbl_80098818:
/* 093278 80098818 2800000A */  cmplwi  r0, 0xa
/* 09327C 8009881C 40820014 */  bne     lbl_80098830
/* 093280 80098820 801F0014 */  lwz     r0, 0x14(r31)
/* 093284 80098824 60000002 */  ori     r0, r0, 2
/* 093288 80098828 901F0014 */  stw     r0, 0x14(r31)
/* 09328C 8009882C 48000060 */  b       lbl_8009888C
lbl_80098830:
/* 093290 80098830 28000005 */  cmplwi  r0, 5
/* 093294 80098834 40820014 */  bne     lbl_80098848
/* 093298 80098838 801F0014 */  lwz     r0, 0x14(r31)
/* 09329C 8009883C 60000001 */  ori     r0, r0, 1
/* 0932A0 80098840 901F0014 */  stw     r0, 0x14(r31)
/* 0932A4 80098844 48000048 */  b       lbl_8009888C
lbl_80098848:
/* 0932A8 80098848 2800000C */  cmplwi  r0, 0xc
/* 0932AC 8009884C 40820014 */  bne     lbl_80098860
/* 0932B0 80098850 801F0014 */  lwz     r0, 0x14(r31)
/* 0932B4 80098854 60000001 */  ori     r0, r0, 1
/* 0932B8 80098858 901F0014 */  stw     r0, 0x14(r31)
/* 0932BC 8009885C 48000030 */  b       lbl_8009888C
lbl_80098860:
/* 0932C0 80098860 2800000E */  cmplwi  r0, 0xe
/* 0932C4 80098864 40820014 */  bne     lbl_80098878
/* 0932C8 80098868 801F0014 */  lwz     r0, 0x14(r31)
/* 0932CC 8009886C 60000004 */  ori     r0, r0, 4
/* 0932D0 80098870 901F0014 */  stw     r0, 0x14(r31)
/* 0932D4 80098874 48000018 */  b       lbl_8009888C
lbl_80098878:
/* 0932D8 80098878 28000004 */  cmplwi  r0, 4
/* 0932DC 8009887C 40820010 */  bne     lbl_8009888C
/* 0932E0 80098880 801F0014 */  lwz     r0, 0x14(r31)
/* 0932E4 80098884 60000400 */  ori     r0, r0, 0x400
/* 0932E8 80098888 901F0014 */  stw     r0, 0x14(r31)
lbl_8009888C:
/* 0932EC 8009888C 8C050001 */  lbzu    r0, 1(r5)
/* 0932F0 80098890 28000003 */  cmplwi  r0, 3
/* 0932F4 80098894 40820014 */  bne     lbl_800988A8
/* 0932F8 80098898 801F0014 */  lwz     r0, 0x14(r31)
/* 0932FC 8009889C 60000002 */  ori     r0, r0, 2
/* 093300 800988A0 901F0014 */  stw     r0, 0x14(r31)
/* 093304 800988A4 48000078 */  b       lbl_8009891C
lbl_800988A8:
/* 093308 800988A8 2800000A */  cmplwi  r0, 0xa
/* 09330C 800988AC 40820014 */  bne     lbl_800988C0
/* 093310 800988B0 801F0014 */  lwz     r0, 0x14(r31)
/* 093314 800988B4 60000002 */  ori     r0, r0, 2
/* 093318 800988B8 901F0014 */  stw     r0, 0x14(r31)
/* 09331C 800988BC 48000060 */  b       lbl_8009891C
lbl_800988C0:
/* 093320 800988C0 28000005 */  cmplwi  r0, 5
/* 093324 800988C4 40820014 */  bne     lbl_800988D8
/* 093328 800988C8 801F0014 */  lwz     r0, 0x14(r31)
/* 09332C 800988CC 60000001 */  ori     r0, r0, 1
/* 093330 800988D0 901F0014 */  stw     r0, 0x14(r31)
/* 093334 800988D4 48000048 */  b       lbl_8009891C
lbl_800988D8:
/* 093338 800988D8 2800000C */  cmplwi  r0, 0xc
/* 09333C 800988DC 40820014 */  bne     lbl_800988F0
/* 093340 800988E0 801F0014 */  lwz     r0, 0x14(r31)
/* 093344 800988E4 60000001 */  ori     r0, r0, 1
/* 093348 800988E8 901F0014 */  stw     r0, 0x14(r31)
/* 09334C 800988EC 48000030 */  b       lbl_8009891C
lbl_800988F0:
/* 093350 800988F0 2800000E */  cmplwi  r0, 0xe
/* 093354 800988F4 40820014 */  bne     lbl_80098908
/* 093358 800988F8 801F0014 */  lwz     r0, 0x14(r31)
/* 09335C 800988FC 60000004 */  ori     r0, r0, 4
/* 093360 80098900 901F0014 */  stw     r0, 0x14(r31)
/* 093364 80098904 48000018 */  b       lbl_8009891C
lbl_80098908:
/* 093368 80098908 28000004 */  cmplwi  r0, 4
/* 09336C 8009890C 40820010 */  bne     lbl_8009891C
/* 093370 80098910 801F0014 */  lwz     r0, 0x14(r31)
/* 093374 80098914 60000400 */  ori     r0, r0, 0x400
/* 093378 80098918 901F0014 */  stw     r0, 0x14(r31)
lbl_8009891C:
/* 09337C 8009891C 38A50001 */  addi    r5, r5, 1
/* 093380 80098920 38C60001 */  addi    r6, r6, 1
/* 093384 80098924 4200FED8 */  bdnz    lbl_800987FC
/* 093388 80098928 38000002 */  li      r0, 2
/* 09338C 8009892C 7C0903A6 */  mtctr   r0
/* 093390 80098930 38A30000 */  addi    r5, r3, 0
/* 093394 80098934 38C00000 */  li      r6, 0
lbl_80098938:
/* 093398 80098938 88050004 */  lbz     r0, 4(r5)
/* 09339C 8009893C 28000003 */  cmplwi  r0, 3
/* 0933A0 80098940 40820014 */  bne     lbl_80098954
/* 0933A4 80098944 801F0014 */  lwz     r0, 0x14(r31)
/* 0933A8 80098948 60000002 */  ori     r0, r0, 2
/* 0933AC 8009894C 901F0014 */  stw     r0, 0x14(r31)
/* 0933B0 80098950 48000048 */  b       lbl_80098998
lbl_80098954:
/* 0933B4 80098954 28000005 */  cmplwi  r0, 5
/* 0933B8 80098958 40820014 */  bne     lbl_8009896C
/* 0933BC 8009895C 801F0014 */  lwz     r0, 0x14(r31)
/* 0933C0 80098960 60000001 */  ori     r0, r0, 1
/* 0933C4 80098964 901F0014 */  stw     r0, 0x14(r31)
/* 0933C8 80098968 48000030 */  b       lbl_80098998
lbl_8009896C:
/* 0933CC 8009896C 28000009 */  cmplwi  r0, 9
/* 0933D0 80098970 40820014 */  bne     lbl_80098984
/* 0933D4 80098974 801F0014 */  lwz     r0, 0x14(r31)
/* 0933D8 80098978 60000004 */  ori     r0, r0, 4
/* 0933DC 8009897C 901F0014 */  stw     r0, 0x14(r31)
/* 0933E0 80098980 48000018 */  b       lbl_80098998
lbl_80098984:
/* 0933E4 80098984 28000004 */  cmplwi  r0, 4
/* 0933E8 80098988 40820010 */  bne     lbl_80098998
/* 0933EC 8009898C 801F0014 */  lwz     r0, 0x14(r31)
/* 0933F0 80098990 60000400 */  ori     r0, r0, 0x400
/* 0933F4 80098994 901F0014 */  stw     r0, 0x14(r31)
lbl_80098998:
/* 0933F8 80098998 88050005 */  lbz     r0, 5(r5)
/* 0933FC 8009899C 38A50001 */  addi    r5, r5, 1
/* 093400 800989A0 28000003 */  cmplwi  r0, 3
/* 093404 800989A4 40820014 */  bne     lbl_800989B8
/* 093408 800989A8 801F0014 */  lwz     r0, 0x14(r31)
/* 09340C 800989AC 60000002 */  ori     r0, r0, 2
/* 093410 800989B0 901F0014 */  stw     r0, 0x14(r31)
/* 093414 800989B4 48000048 */  b       lbl_800989FC
lbl_800989B8:
/* 093418 800989B8 28000005 */  cmplwi  r0, 5
/* 09341C 800989BC 40820014 */  bne     lbl_800989D0
/* 093420 800989C0 801F0014 */  lwz     r0, 0x14(r31)
/* 093424 800989C4 60000001 */  ori     r0, r0, 1
/* 093428 800989C8 901F0014 */  stw     r0, 0x14(r31)
/* 09342C 800989CC 48000030 */  b       lbl_800989FC
lbl_800989D0:
/* 093430 800989D0 28000009 */  cmplwi  r0, 9
/* 093434 800989D4 40820014 */  bne     lbl_800989E8
/* 093438 800989D8 801F0014 */  lwz     r0, 0x14(r31)
/* 09343C 800989DC 60000004 */  ori     r0, r0, 4
/* 093440 800989E0 901F0014 */  stw     r0, 0x14(r31)
/* 093444 800989E4 48000018 */  b       lbl_800989FC
lbl_800989E8:
/* 093448 800989E8 28000004 */  cmplwi  r0, 4
/* 09344C 800989EC 40820010 */  bne     lbl_800989FC
/* 093450 800989F0 801F0014 */  lwz     r0, 0x14(r31)
/* 093454 800989F4 60000400 */  ori     r0, r0, 0x400
/* 093458 800989F8 901F0014 */  stw     r0, 0x14(r31)
lbl_800989FC:
/* 09345C 800989FC 38A50001 */  addi    r5, r5, 1
/* 093460 80098A00 38C60001 */  addi    r6, r6, 1
/* 093464 80098A04 4200FF34 */  bdnz    lbl_80098938
/* 093468 80098A08 38630008 */  addi    r3, r3, 8
/* 09346C 80098A0C 38840001 */  addi    r4, r4, 1
lbl_80098A10:
/* 093470 80098A10 7C04F040 */  cmplw   r4, r30
/* 093474 80098A14 4180FDD8 */  blt     lbl_800987EC
/* 093478 80098A18 387F0000 */  addi    r3, r31, 0
/* 09347C 80098A1C 38810028 */  addi    r4, r1, 0x28
/* 093480 80098A20 480000C1 */  bl      BuildCycle
/* 093484 80098A24 281E0002 */  cmplwi  r30, 2
/* 093488 80098A28 40820010 */  bne     lbl_80098A38
/* 09348C 80098A2C 387F0000 */  addi    r3, r31, 0
/* 093490 80098A30 38810030 */  addi    r4, r1, 0x30
/* 093494 80098A34 480000AD */  bl      BuildCycle
lbl_80098A38:
/* 093498 80098A38 389F0000 */  addi    r4, r31, 0
/* 09349C 80098A3C 38A00000 */  li      r5, 0
/* 0934A0 80098A40 38600001 */  li      r3, 1
/* 0934A4 80098A44 4800004C */  b       lbl_80098A90
lbl_80098A48:
/* 0934A8 80098A48 80040020 */  lwz     r0, 0x20(r4)
/* 0934AC 80098A4C 2C0000FF */  cmpwi   r0, 0xff
/* 0934B0 80098A50 41820008 */  beq     lbl_80098A58
/* 0934B4 80098A54 987F0013 */  stb     r3, 0x13(r31)
lbl_80098A58:
/* 0934B8 80098A58 80040018 */  lwz     r0, 0x18(r4)
/* 0934BC 80098A5C 2C0000FF */  cmpwi   r0, 0xff
/* 0934C0 80098A60 41820028 */  beq     lbl_80098A88
/* 0934C4 80098A64 2C000000 */  cmpwi   r0, 0
/* 0934C8 80098A68 40820014 */  bne     lbl_80098A7C
/* 0934CC 80098A6C 881F0012 */  lbz     r0, 0x12(r31)
/* 0934D0 80098A70 60000001 */  ori     r0, r0, 1
/* 0934D4 80098A74 981F0012 */  stb     r0, 0x12(r31)
/* 0934D8 80098A78 48000010 */  b       lbl_80098A88
lbl_80098A7C:
/* 0934DC 80098A7C 881F0012 */  lbz     r0, 0x12(r31)
/* 0934E0 80098A80 60000002 */  ori     r0, r0, 2
/* 0934E4 80098A84 981F0012 */  stb     r0, 0x12(r31)
lbl_80098A88:
/* 0934E8 80098A88 3884000C */  addi    r4, r4, 0xc
/* 0934EC 80098A8C 38A50001 */  addi    r5, r5, 1
lbl_80098A90:
/* 0934F0 80098A90 881F0011 */  lbz     r0, 0x11(r31)
/* 0934F4 80098A94 7C050000 */  cmpw    r5, r0
/* 0934F8 80098A98 4180FFB0 */  blt     lbl_80098A48
/* 0934FC 80098A9C 387F0012 */  addi    r3, r31, 0x12
/* 093500 80098AA0 881F0012 */  lbz     r0, 0x12(r31)
/* 093504 80098AA4 28000003 */  cmplwi  r0, 3
/* 093508 80098AA8 40820010 */  bne     lbl_80098AB8
/* 09350C 80098AAC 38000002 */  li      r0, 2
/* 093510 80098AB0 98030000 */  stb     r0, 0(r3)
/* 093514 80098AB4 48000014 */  b       lbl_80098AC8
lbl_80098AB8:
/* 093518 80098AB8 28000000 */  cmplwi  r0, 0
/* 09351C 80098ABC 4182000C */  beq     lbl_80098AC8
/* 093520 80098AC0 38000001 */  li      r0, 1
/* 093524 80098AC4 98030000 */  stb     r0, 0(r3)
lbl_80098AC8:
/* 093528 80098AC8 7FE3FB78 */  mr      r3, r31
/* 09352C 80098ACC BA810038 */  lmw     r20, 0x38(r1)
/* 093530 80098AD0 8001006C */  lwz     r0, 0x6c(r1)
/* 093534 80098AD4 38210068 */  addi    r1, r1, 0x68
/* 093538 80098AD8 7C0803A6 */  mtlr    r0
/* 09353C 80098ADC 4E800020 */  blr     
