glabel frameBeginOK
/* 02092C 80025ECC 800D89A8 */  lwz     r0, gbFrameValid@sda21(r13)
/* 020930 80025ED0 2C000000 */  cmpwi   r0, 0
/* 020934 80025ED4 4182000C */  beq     lbl_80025EE0
/* 020938 80025ED8 38600000 */  li      r3, 0
/* 02093C 80025EDC 48000008 */  b       lbl_80025EE4
lbl_80025EE0:
/* 020940 80025EE0 38600001 */  li      r3, 1
lbl_80025EE4:
/* 020944 80025EE4 4E800020 */  blr     