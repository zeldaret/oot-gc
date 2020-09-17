# CARDNet.c
.include "macros.inc"

.section .sdata, "wa"

.balign 8

/* 000F17D8 80135558 0002 */
glabel __CARDVendorID
    .short 0xFFFF

/* 000F17DA 8013555A 0001 */
glabel __CARDPermMask
    .byte 0x1C


