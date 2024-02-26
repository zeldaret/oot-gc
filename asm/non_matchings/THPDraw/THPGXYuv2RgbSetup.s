glabel THPGXYuv2RgbSetup
/* 00BCB0 80011250 7C0802A6 */  mflr    r0
/* 00BCB4 80011254 38800000 */  li      r4, 0
/* 00BCB8 80011258 90010004 */  stw     r0, 4(r1)
/* 00BCBC 8001125C 9421FF10 */  stwu    r1, -0xf0(r1)
/* 00BCC0 80011260 BF6100DC */  stmw    r27, 0xdc(r1)
/* 00BCC4 80011264 A3830004 */  lhz     r28, 4(r3)
/* 00BCC8 80011268 A3630006 */  lhz     r27, 6(r3)
/* 00BCCC 8001126C 38600000 */  li      r3, 0
/* 00BCD0 80011270 4809D2DD */  bl      GXSetPixelFmt
/* 00BCD4 80011274 6F7D8000 */  xoris   r29, r27, 0x8000
/* 00BCD8 80011278 C022808C */  lfs     f1, D_80135D8C@sda21(r2)
/* 00BCDC 8001127C 6F9F8000 */  xoris   r31, r28, 0x8000
/* 00BCE0 80011280 93A100D4 */  stw     r29, 0xd4(r1)
/* 00BCE4 80011284 3FC04330 */  lis     r30, 0x4330
/* 00BCE8 80011288 C8828098 */  lfd     f4, D_80135D98@sda21(r2)
/* 00BCEC 8001128C 93E100CC */  stw     r31, 0xcc(r1)
/* 00BCF0 80011290 FC600890 */  fmr     f3, f1
/* 00BCF4 80011294 FCA00890 */  fmr     f5, f1
/* 00BCF8 80011298 C0C28090 */  lfs     f6, D_80135D90@sda21(r2)
/* 00BCFC 8001129C 93C100D0 */  stw     r30, 0xd0(r1)
/* 00BD00 800112A0 38610074 */  addi    r3, r1, 0x74
/* 00BD04 800112A4 93C100C8 */  stw     r30, 0xc8(r1)
/* 00BD08 800112A8 C84100D0 */  lfd     f2, 0xd0(r1)
/* 00BD0C 800112AC C80100C8 */  lfd     f0, 0xc8(r1)
/* 00BD10 800112B0 EC422028 */  fsubs   f2, f2, f4
/* 00BD14 800112B4 EC802028 */  fsubs   f4, f0, f4
/* 00BD18 800112B8 48096E31 */  bl      C_MTXOrtho
/* 00BD1C 800112BC 38610074 */  addi    r3, r1, 0x74
/* 00BD20 800112C0 38800001 */  li      r4, 1
/* 00BD24 800112C4 4809D475 */  bl      GXSetProjection
/* 00BD28 800112C8 93E100C4 */  stw     r31, 0xc4(r1)
/* 00BD2C 800112CC C022808C */  lfs     f1, D_80135D8C@sda21(r2)
/* 00BD30 800112D0 93A100BC */  stw     r29, 0xbc(r1)
/* 00BD34 800112D4 C8828098 */  lfd     f4, D_80135D98@sda21(r2)
/* 00BD38 800112D8 FC400890 */  fmr     f2, f1
/* 00BD3C 800112DC 93C100C0 */  stw     r30, 0xc0(r1)
/* 00BD40 800112E0 FCA00890 */  fmr     f5, f1
/* 00BD44 800112E4 C0C28094 */  lfs     f6, D_80135D94@sda21(r2)
/* 00BD48 800112E8 93C100B8 */  stw     r30, 0xb8(r1)
/* 00BD4C 800112EC C86100C0 */  lfd     f3, 0xc0(r1)
/* 00BD50 800112F0 C80100B8 */  lfd     f0, 0xb8(r1)
/* 00BD54 800112F4 EC632028 */  fsubs   f3, f3, f4
/* 00BD58 800112F8 EC802028 */  fsubs   f4, f0, f4
/* 00BD5C 800112FC 4809D7DD */  bl      GXSetViewport
/* 00BD60 80011300 38BC0000 */  addi    r5, r28, 0
/* 00BD64 80011304 38DB0000 */  addi    r6, r27, 0
/* 00BD68 80011308 38600000 */  li      r3, 0
/* 00BD6C 8001130C 38800000 */  li      r4, 0
/* 00BD70 80011310 4809D811 */  bl      GXSetScissor
/* 00BD74 80011314 38610044 */  addi    r3, r1, 0x44
/* 00BD78 80011318 48096AB5 */  bl      PSMTXIdentity
/* 00BD7C 8001131C 38610044 */  addi    r3, r1, 0x44
/* 00BD80 80011320 38800000 */  li      r4, 0
/* 00BD84 80011324 4809D545 */  bl      GXLoadPosMtxImm
/* 00BD88 80011328 38600000 */  li      r3, 0
/* 00BD8C 8001132C 4809D5DD */  bl      GXSetCurrentMtx
/* 00BD90 80011330 38600001 */  li      r3, 1
/* 00BD94 80011334 38800007 */  li      r4, 7
/* 00BD98 80011338 38A00000 */  li      r5, 0
/* 00BD9C 8001133C 4809D1A9 */  bl      GXSetZMode
/* 00BDA0 80011340 38600000 */  li      r3, 0
/* 00BDA4 80011344 38800001 */  li      r4, 1
/* 00BDA8 80011348 38A00000 */  li      r5, 0
/* 00BDAC 8001134C 38C00000 */  li      r6, 0
/* 00BDB0 80011350 4809D0E9 */  bl      GXSetBlendMode
/* 00BDB4 80011354 38600001 */  li      r3, 1
/* 00BDB8 80011358 4809D135 */  bl      GXSetColorUpdate
/* 00BDBC 8001135C 38600000 */  li      r3, 0
/* 00BDC0 80011360 4809D159 */  bl      GXSetAlphaUpdate
/* 00BDC4 80011364 38600000 */  li      r3, 0
/* 00BDC8 80011368 4809AD55 */  bl      GXSetDispCopyGamma
/* 00BDCC 8001136C 38600000 */  li      r3, 0
/* 00BDD0 80011370 4809A311 */  bl      GXSetCullMode
/* 00BDD4 80011374 38600007 */  li      r3, 7
/* 00BDD8 80011378 38800000 */  li      r4, 0
/* 00BDDC 8001137C 38A00000 */  li      r5, 0
/* 00BDE0 80011380 38C00007 */  li      r6, 7
/* 00BDE4 80011384 38E00000 */  li      r7, 0
/* 00BDE8 80011388 4809C925 */  bl      GXSetAlphaCompare
/* 00BDEC 8001138C 38600000 */  li      r3, 0
/* 00BDF0 80011390 38800011 */  li      r4, 0x11
/* 00BDF4 80011394 38A00000 */  li      r5, 0
/* 00BDF8 80011398 4809C959 */  bl      GXSetZTexture
/* 00BDFC 8001139C 38600000 */  li      r3, 0
/* 00BE00 800113A0 4809B23D */  bl      GXSetNumChans
/* 00BE04 800113A4 38600002 */  li      r3, 2
/* 00BE08 800113A8 4809970D */  bl      GXSetNumTexGens
/* 00BE0C 800113AC 38600000 */  li      r3, 0
/* 00BE10 800113B0 38800001 */  li      r4, 1
/* 00BE14 800113B4 38A00004 */  li      r5, 4
/* 00BE18 800113B8 38C0003C */  li      r6, 0x3c
/* 00BE1C 800113BC 38E00000 */  li      r7, 0
/* 00BE20 800113C0 3900007D */  li      r8, 0x7d
/* 00BE24 800113C4 48099471 */  bl      GXSetTexCoordGen2
/* 00BE28 800113C8 38600001 */  li      r3, 1
/* 00BE2C 800113CC 38800001 */  li      r4, 1
/* 00BE30 800113D0 38A00004 */  li      r5, 4
/* 00BE34 800113D4 38C0003C */  li      r6, 0x3c
/* 00BE38 800113D8 38E00000 */  li      r7, 0
/* 00BE3C 800113DC 3900007D */  li      r8, 0x7d
/* 00BE40 800113E0 48099455 */  bl      GXSetTexCoordGen2
/* 00BE44 800113E4 4809BBA5 */  bl      GXInvalidateTexAll
/* 00BE48 800113E8 48098E01 */  bl      GXClearVtxDesc
/* 00BE4C 800113EC 38600009 */  li      r3, 9
/* 00BE50 800113F0 38800001 */  li      r4, 1
/* 00BE54 800113F4 480989A9 */  bl      GXSetVtxDesc
/* 00BE58 800113F8 3860000D */  li      r3, 0xd
/* 00BE5C 800113FC 38800001 */  li      r4, 1
/* 00BE60 80011400 4809899D */  bl      GXSetVtxDesc
/* 00BE64 80011404 38600007 */  li      r3, 7
/* 00BE68 80011408 38800009 */  li      r4, 9
/* 00BE6C 8001140C 38A00001 */  li      r5, 1
/* 00BE70 80011410 38C00003 */  li      r6, 3
/* 00BE74 80011414 38E00000 */  li      r7, 0
/* 00BE78 80011418 48098E09 */  bl      GXSetVtxAttrFmt
/* 00BE7C 8001141C 38600007 */  li      r3, 7
/* 00BE80 80011420 3880000D */  li      r4, 0xd
/* 00BE84 80011424 38A00001 */  li      r5, 1
/* 00BE88 80011428 38C00002 */  li      r6, 2
/* 00BE8C 8001142C 38E00000 */  li      r7, 0
/* 00BE90 80011430 48098DF1 */  bl      GXSetVtxAttrFmt
/* 00BE94 80011434 38600004 */  li      r3, 4
/* 00BE98 80011438 4809CAE1 */  bl      GXSetNumTevStages
/* 00BE9C 8001143C 38600000 */  li      r3, 0
/* 00BEA0 80011440 38800001 */  li      r4, 1
/* 00BEA4 80011444 38A00001 */  li      r5, 1
/* 00BEA8 80011448 38C000FF */  li      r6, 0xff
/* 00BEAC 8001144C 4809C931 */  bl      GXSetTevOrder
/* 00BEB0 80011450 38600000 */  li      r3, 0
/* 00BEB4 80011454 3880000F */  li      r4, 0xf
/* 00BEB8 80011458 38A00008 */  li      r5, 8
/* 00BEBC 8001145C 38C0000E */  li      r6, 0xe
/* 00BEC0 80011460 38E00002 */  li      r7, 2
/* 00BEC4 80011464 4809C405 */  bl      GXSetTevColorIn
/* 00BEC8 80011468 38600000 */  li      r3, 0
/* 00BECC 8001146C 38800000 */  li      r4, 0
/* 00BED0 80011470 38A00000 */  li      r5, 0
/* 00BED4 80011474 38C00000 */  li      r6, 0
/* 00BED8 80011478 38E00000 */  li      r7, 0
/* 00BEDC 8001147C 39000000 */  li      r8, 0
/* 00BEE0 80011480 4809C471 */  bl      GXSetTevColorOp
/* 00BEE4 80011484 38600000 */  li      r3, 0
/* 00BEE8 80011488 38800007 */  li      r4, 7
/* 00BEEC 8001148C 38A00004 */  li      r5, 4
/* 00BEF0 80011490 38C00006 */  li      r6, 6
/* 00BEF4 80011494 38E00001 */  li      r7, 1
/* 00BEF8 80011498 4809C415 */  bl      GXSetTevAlphaIn
/* 00BEFC 8001149C 38600000 */  li      r3, 0
/* 00BF00 800114A0 38800001 */  li      r4, 1
/* 00BF04 800114A4 38A00000 */  li      r5, 0
/* 00BF08 800114A8 38C00000 */  li      r6, 0
/* 00BF0C 800114AC 38E00000 */  li      r7, 0
/* 00BF10 800114B0 39000000 */  li      r8, 0
/* 00BF14 800114B4 4809C4A5 */  bl      GXSetTevAlphaOp
/* 00BF18 800114B8 38600000 */  li      r3, 0
/* 00BF1C 800114BC 3880000C */  li      r4, 0xc
/* 00BF20 800114C0 4809C66D */  bl      GXSetTevKColorSel
/* 00BF24 800114C4 38600000 */  li      r3, 0
/* 00BF28 800114C8 3880001C */  li      r4, 0x1c
/* 00BF2C 800114CC 4809C6BD */  bl      GXSetTevKAlphaSel
/* 00BF30 800114D0 38600000 */  li      r3, 0
/* 00BF34 800114D4 38800000 */  li      r4, 0
/* 00BF38 800114D8 38A00000 */  li      r5, 0
/* 00BF3C 800114DC 4809C709 */  bl      GXSetTevSwapMode
/* 00BF40 800114E0 38600001 */  li      r3, 1
/* 00BF44 800114E4 38800001 */  li      r4, 1
/* 00BF48 800114E8 38A00002 */  li      r5, 2
/* 00BF4C 800114EC 38C000FF */  li      r6, 0xff
/* 00BF50 800114F0 4809C88D */  bl      GXSetTevOrder
/* 00BF54 800114F4 38600001 */  li      r3, 1
/* 00BF58 800114F8 3880000F */  li      r4, 0xf
/* 00BF5C 800114FC 38A00008 */  li      r5, 8
/* 00BF60 80011500 38C0000E */  li      r6, 0xe
/* 00BF64 80011504 38E00000 */  li      r7, 0
/* 00BF68 80011508 4809C361 */  bl      GXSetTevColorIn
/* 00BF6C 8001150C 38600001 */  li      r3, 1
/* 00BF70 80011510 38800000 */  li      r4, 0
/* 00BF74 80011514 38A00000 */  li      r5, 0
/* 00BF78 80011518 38C00001 */  li      r6, 1
/* 00BF7C 8001151C 38E00000 */  li      r7, 0
/* 00BF80 80011520 39000000 */  li      r8, 0
/* 00BF84 80011524 4809C3CD */  bl      GXSetTevColorOp
/* 00BF88 80011528 38600001 */  li      r3, 1
/* 00BF8C 8001152C 38800007 */  li      r4, 7
/* 00BF90 80011530 38A00004 */  li      r5, 4
/* 00BF94 80011534 38C00006 */  li      r6, 6
/* 00BF98 80011538 38E00000 */  li      r7, 0
/* 00BF9C 8001153C 4809C371 */  bl      GXSetTevAlphaIn
/* 00BFA0 80011540 38600001 */  li      r3, 1
/* 00BFA4 80011544 38800001 */  li      r4, 1
/* 00BFA8 80011548 38A00000 */  li      r5, 0
/* 00BFAC 8001154C 38C00000 */  li      r6, 0
/* 00BFB0 80011550 38E00000 */  li      r7, 0
/* 00BFB4 80011554 39000000 */  li      r8, 0
/* 00BFB8 80011558 4809C401 */  bl      GXSetTevAlphaOp
/* 00BFBC 8001155C 38600001 */  li      r3, 1
/* 00BFC0 80011560 3880000D */  li      r4, 0xd
/* 00BFC4 80011564 4809C5C9 */  bl      GXSetTevKColorSel
/* 00BFC8 80011568 38600001 */  li      r3, 1
/* 00BFCC 8001156C 3880001D */  li      r4, 0x1d
/* 00BFD0 80011570 4809C619 */  bl      GXSetTevKAlphaSel
/* 00BFD4 80011574 38600001 */  li      r3, 1
/* 00BFD8 80011578 38800000 */  li      r4, 0
/* 00BFDC 8001157C 38A00000 */  li      r5, 0
/* 00BFE0 80011580 4809C665 */  bl      GXSetTevSwapMode
/* 00BFE4 80011584 38600002 */  li      r3, 2
/* 00BFE8 80011588 38800000 */  li      r4, 0
/* 00BFEC 8001158C 38A00000 */  li      r5, 0
/* 00BFF0 80011590 38C000FF */  li      r6, 0xff
/* 00BFF4 80011594 4809C7E9 */  bl      GXSetTevOrder
/* 00BFF8 80011598 38600002 */  li      r3, 2
/* 00BFFC 8001159C 3880000F */  li      r4, 0xf
/* 00C000 800115A0 38A00008 */  li      r5, 8
/* 00C004 800115A4 38C0000C */  li      r6, 0xc
/* 00C008 800115A8 38E00000 */  li      r7, 0
/* 00C00C 800115AC 4809C2BD */  bl      GXSetTevColorIn
/* 00C010 800115B0 38600002 */  li      r3, 2
/* 00C014 800115B4 38800000 */  li      r4, 0
/* 00C018 800115B8 38A00000 */  li      r5, 0
/* 00C01C 800115BC 38C00000 */  li      r6, 0
/* 00C020 800115C0 38E00001 */  li      r7, 1
/* 00C024 800115C4 39000000 */  li      r8, 0
/* 00C028 800115C8 4809C329 */  bl      GXSetTevColorOp
/* 00C02C 800115CC 38600002 */  li      r3, 2
/* 00C030 800115D0 38800004 */  li      r4, 4
/* 00C034 800115D4 38A00007 */  li      r5, 7
/* 00C038 800115D8 38C00007 */  li      r6, 7
/* 00C03C 800115DC 38E00000 */  li      r7, 0
/* 00C040 800115E0 4809C2CD */  bl      GXSetTevAlphaIn
/* 00C044 800115E4 38600002 */  li      r3, 2
/* 00C048 800115E8 38800000 */  li      r4, 0
/* 00C04C 800115EC 38A00000 */  li      r5, 0
/* 00C050 800115F0 38C00000 */  li      r6, 0
/* 00C054 800115F4 38E00001 */  li      r7, 1
/* 00C058 800115F8 39000000 */  li      r8, 0
/* 00C05C 800115FC 4809C35D */  bl      GXSetTevAlphaOp
/* 00C060 80011600 38600002 */  li      r3, 2
/* 00C064 80011604 38800000 */  li      r4, 0
/* 00C068 80011608 38A00000 */  li      r5, 0
/* 00C06C 8001160C 4809C5D9 */  bl      GXSetTevSwapMode
/* 00C070 80011610 38600003 */  li      r3, 3
/* 00C074 80011614 388000FF */  li      r4, 0xff
/* 00C078 80011618 38A000FF */  li      r5, 0xff
/* 00C07C 8001161C 38C000FF */  li      r6, 0xff
/* 00C080 80011620 4809C75D */  bl      GXSetTevOrder
/* 00C084 80011624 38600003 */  li      r3, 3
/* 00C088 80011628 38800001 */  li      r4, 1
/* 00C08C 8001162C 38A00000 */  li      r5, 0
/* 00C090 80011630 38C0000E */  li      r6, 0xe
/* 00C094 80011634 38E0000F */  li      r7, 0xf
/* 00C098 80011638 4809C231 */  bl      GXSetTevColorIn
/* 00C09C 8001163C 38600003 */  li      r3, 3
/* 00C0A0 80011640 38800000 */  li      r4, 0
/* 00C0A4 80011644 38A00000 */  li      r5, 0
/* 00C0A8 80011648 38C00000 */  li      r6, 0
/* 00C0AC 8001164C 38E00001 */  li      r7, 1
/* 00C0B0 80011650 39000000 */  li      r8, 0
/* 00C0B4 80011654 4809C29D */  bl      GXSetTevColorOp
/* 00C0B8 80011658 38600003 */  li      r3, 3
/* 00C0BC 8001165C 38800007 */  li      r4, 7
/* 00C0C0 80011660 38A00007 */  li      r5, 7
/* 00C0C4 80011664 38C00007 */  li      r6, 7
/* 00C0C8 80011668 38E00007 */  li      r7, 7
/* 00C0CC 8001166C 4809C241 */  bl      GXSetTevAlphaIn
/* 00C0D0 80011670 38600003 */  li      r3, 3
/* 00C0D4 80011674 38800000 */  li      r4, 0
/* 00C0D8 80011678 38A00000 */  li      r5, 0
/* 00C0DC 8001167C 38C00000 */  li      r6, 0
/* 00C0E0 80011680 38E00001 */  li      r7, 1
/* 00C0E4 80011684 39000000 */  li      r8, 0
/* 00C0E8 80011688 4809C2D1 */  bl      GXSetTevAlphaOp
/* 00C0EC 8001168C 38600003 */  li      r3, 3
/* 00C0F0 80011690 38800000 */  li      r4, 0
/* 00C0F4 80011694 38A00000 */  li      r5, 0
/* 00C0F8 80011698 4809C54D */  bl      GXSetTevSwapMode
/* 00C0FC 8001169C 38600003 */  li      r3, 3
/* 00C100 800116A0 3880000E */  li      r4, 0xe
/* 00C104 800116A4 4809C489 */  bl      GXSetTevKColorSel
/* 00C108 800116A8 80628078 */  lwz     r3, D_80135D78@sda21(r2)
/* 00C10C 800116AC 3881003C */  addi    r4, r1, 0x3c
/* 00C110 800116B0 8002807C */  lwz     r0, (D_80135D78 + 4)@sda21(r2)
/* 00C114 800116B4 90610034 */  stw     r3, 0x34(r1)
/* 00C118 800116B8 38600001 */  li      r3, 1
/* 00C11C 800116BC 90010038 */  stw     r0, 0x38(r1)
/* 00C120 800116C0 80A10034 */  lwz     r5, 0x34(r1)
/* 00C124 800116C4 80010038 */  lwz     r0, 0x38(r1)
/* 00C128 800116C8 90A1003C */  stw     r5, 0x3c(r1)
/* 00C12C 800116CC 90010040 */  stw     r0, 0x40(r1)
/* 00C130 800116D0 4809C36D */  bl      GXSetTevColorS10
/* 00C134 800116D4 80028080 */  lwz     r0, D_80135D80@sda21(r2)
/* 00C138 800116D8 38810030 */  addi    r4, r1, 0x30
/* 00C13C 800116DC 38600000 */  li      r3, 0
/* 00C140 800116E0 9001002C */  stw     r0, 0x2c(r1)
/* 00C144 800116E4 8001002C */  lwz     r0, 0x2c(r1)
/* 00C148 800116E8 90010030 */  stw     r0, 0x30(r1)
/* 00C14C 800116EC 4809C3CD */  bl      GXSetTevKColor
/* 00C150 800116F0 80028084 */  lwz     r0, D_80135D84@sda21(r2)
/* 00C154 800116F4 38810028 */  addi    r4, r1, 0x28
/* 00C158 800116F8 38600001 */  li      r3, 1
/* 00C15C 800116FC 90010024 */  stw     r0, 0x24(r1)
/* 00C160 80011700 80010024 */  lwz     r0, 0x24(r1)
/* 00C164 80011704 90010028 */  stw     r0, 0x28(r1)
/* 00C168 80011708 4809C3B1 */  bl      GXSetTevKColor
/* 00C16C 8001170C 80028088 */  lwz     r0, D_80135D88@sda21(r2)
/* 00C170 80011710 38810020 */  addi    r4, r1, 0x20
/* 00C174 80011714 38600002 */  li      r3, 2
/* 00C178 80011718 9001001C */  stw     r0, 0x1c(r1)
/* 00C17C 8001171C 8001001C */  lwz     r0, 0x1c(r1)
/* 00C180 80011720 90010020 */  stw     r0, 0x20(r1)
/* 00C184 80011724 4809C395 */  bl      GXSetTevKColor
/* 00C188 80011728 38600000 */  li      r3, 0
/* 00C18C 8001172C 38800000 */  li      r4, 0
/* 00C190 80011730 38A00001 */  li      r5, 1
/* 00C194 80011734 38C00002 */  li      r6, 2
/* 00C198 80011738 38E00003 */  li      r7, 3
/* 00C19C 8001173C 4809C4F1 */  bl      GXSetTevSwapModeTable
/* 00C1A0 80011740 BB6100DC */  lmw     r27, 0xdc(r1)
/* 00C1A4 80011744 800100F4 */  lwz     r0, 0xf4(r1)
/* 00C1A8 80011748 382100F0 */  addi    r1, r1, 0xf0
/* 00C1AC 8001174C 7C0803A6 */  mtlr    r0
/* 00C1B0 80011750 4E800020 */  blr     