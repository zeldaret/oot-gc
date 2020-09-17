/*
Code sections:
    .init   80003100 - 80005598 : 002498
    .text   800055A0 - 800D2F8C : 0CD9EC
Data sections:
    .ctors  800D2FA0 - 800D2FA8 : 000008
    .dtors  800D2FC0 - 800D2FC8 : 000008
    .rodata 800D2FE0 - 800D3710 : 000730
    .data   800D3720 - 800F3ED8 : 0207B8
    .sdata  80134CE0 - 80135579 : 000899
    .sdata2 80135D00 - 80136420 : 000720
BSS section:
    .bss    800F3EE0 - 80134CD8 : 040DF8
    .sbss   80135580 - 80135CFD : 00077D
    .sbss2  80136420 - 80136420 : 000000
Entry Point: 0x80003154
*/
# glabel
.macro glabel label
    .global \label
    \label:
.endm
# PowerPC Register Constants
.set r0, 0
.set r1, 1
.set r2, 2
.set r3, 3
.set r4, 4
.set r5, 5
.set r6, 6
.set r7, 7
.set r8, 8
.set r9, 9
.set r10, 10
.set r11, 11
.set r12, 12
.set r13, 13
.set r14, 14
.set r15, 15
.set r16, 16
.set r17, 17
.set r18, 18
.set r19, 19
.set r20, 20
.set r21, 21
.set r22, 22
.set r23, 23
.set r24, 24
.set r25, 25
.set r26, 26
.set r27, 27
.set r28, 28
.set r29, 29
.set r30, 30
.set r31, 31
.set f0, 0
.set f1, 1
.set f2, 2
.set f3, 3
.set f4, 4
.set f5, 5
.set f6, 6
.set f7, 7
.set f8, 8
.set f9, 9
.set f10, 10
.set f11, 11
.set f12, 12
.set f13, 13
.set f14, 14
.set f15, 15
.set f16, 16
.set f17, 17
.set f18, 18
.set f19, 19
.set f20, 20
.set f21, 21
.set f22, 22
.set f23, 23
.set f24, 24
.set f25, 25
.set f26, 26
.set f27, 27
.set f28, 28
.set f29, 29
.set f30, 30
.set f31, 31
.set qr0, 0
.set qr1, 1
.set qr2, 2
.set qr3, 3
.set qr4, 4
.set qr5, 5
.set qr6, 6
.set qr7, 7
# Small Data Area (read/write) Base
.set _SDA_BASE_, 0x8013CCE0
# Small Data Area (read only) Base
.set _SDA2_BASE_, 0x8013DD00
