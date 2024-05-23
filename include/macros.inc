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

# Gamecube Hardware Regs
.set HW_REGS_BASE, 0xCC000000

.set CP_REGS_BASE, 0xCC000000
.set CP_SR,         0x00 # Status Register
.set CP_CR,         0x02 # Control Register
.set CP_04,         0x04 # Clear Register
.set CP_0E,         0x0E # token register
.set CP_10,         0x10 # bounding box - left
.set CP_12,         0x12 # bounding box - right
.set CP_14,         0x14 # bounding box - top
.set CP_16,         0x16 # bounding box - bottom
.set CP_20,         0x20 # cp FIFO base lo
.set CP_22,         0x22 # cp FIFO base hi
.set CP_24,         0x24 # cp FIFO end lo
.set CP_26,         0x26 # cp FIFO end hi
.set CP_28,         0x28 # cp FIFO high watermark lo
.set CP_2A,         0x2A # cp FIFO high watermark hi
.set CP_2C,         0x2C # cp FIFO low watermark lo
.set CP_2E,         0x2E # cp FIFO low watermark hi
.set CP_30,         0x30 # cp FIFO read/write distance lo
.set CP_32,         0x32 # cp FIFO read/write distance hi
.set CP_34,         0x34 # cp FIFO write pointer lo
.set CP_36,         0x36 # cp FIFO write pointer hi
.set CP_38,         0x38 # cp FIFO read pointer lo
.set CP_3A,         0x3A # cp FIFO read pointer hi
.set CP_3C,         0x3C # cp FIFO bp lo
.set CP_3E,         0x3E # cp FIFO bp hi

.set PE_REGS_BASE, 0xCC001000
.set PE_00,         0x00 # Z configuration
.set PE_02,         0x02 # Alpha configuration
.set PE_04,         0x04 # destination alpha
.set PE_06,         0x06 # Alpha Mode
.set PE_08,         0x08 # Alpha Read (?)
.set PE_0A,         0x0A # Interrupt Status Register
.set PE_0E,         0x0E # PE Token ?

.set VI_REGS_BASE, 0xCC002000
.set VI_VTR,        0x00 # Vertical Timing Register
.set VI_DCR,        0x02 # Display Configuration Register
.set VI_HTR0,       0x04 # Horizontal Timing 0
.set VI_06,         0x06 # ?
.set VI_HTR1,       0x08 # Horizontal Timing 1
.set VI_0A,         0x0A # ?
.set VI_VTO,        0x0C # Odd Field Vertical Timing Register
.set VI_0E,         0x0E # ?
.set VI_VTE,        0x10 # Even Field Vertical Timing Register
.set VI_12,         0x12 # ?
.set VI_BBEI,       0x14 # Odd Field Burst Blanking Interval Register
.set VI_16,         0x16 # ?
.set VI_BBOI,       0x18 # Even Field Burst Blanking Interval Register
.set VI_1A,         0x1A # ?
.set VI_TFBL,       0x1C # Top Field Base Register (L) (External Framebuffer Half 1)
.set VI_TFBR,       0x20 # Top Field Base Register (R) (Only valid in 3D Mode)
.set VI_BFBL,       0x24 # Bottom Field Base Register (L) (External Framebuffer Half 2)
.set VI_BFBR,       0x28 # Bottom Field Base Register (R) (Only valid in 3D Mode)
.set VI_DPV,        0x2C # Current vertical Position
.set VI_DPH,        0x2E # Current horizontal Position (?)
.set VI_DI0,        0x30 # Display Interrupt 0
.set VI_32,         0x32 # ?
.set VI_DI1,        0x34 # DIsplay Interrupt 1
.set VI_36,         0x36 # ?
.set VI_DI2,        0x38 # Display Interrupt 2
.set VI_DI3,        0x3C # Display Interrupt 3
.set VI_DL0,        0x40 # Display Latch Register 0
.set VI_DL1,        0x44 # Display Latch Register 1
.set VI_HSW,        0x48 # Scaling Width Register
.set VI_HSR,        0x4A # Horizontal Scaling Register
.set VI_FCT0,       0x4C # Filter Coefficient Table 0 (AA stuff)
.set VI_4E,         0x4E # ?
.set VI_FCT1,       0x50 # Filter Coefficient Table 1 (AA stuff)
.set VI_52,         0x52 # ?
.set VI_FCT2,       0x54 # Filter Coefficient Table 2 (AA stuff)
.set VI_56,         0x56 # ?
.set VI_FCT3,       0x58 # FCT3 - Filter Coefficient Table 3 (AA stuff)
.set VI_5A,         0x5A # ?
.set VI_FCT4,       0x5C # FCT4 - Filter Coefficient Table 4 (AA stuff)
.set VI_5E,         0x5E # ?
.set VI_FCT5,       0x60 # FCT5 - Filter Coefficient Table 5 (AA stuff)
.set VI_62,         0x62 # ?
.set VI_FCT6,       0x64 # FCT6 - Filter Coefficient Table 6 (AA stuff)
.set VI_66,         0x66 # ?
.set VI_68,         0x68 # ? (AA stuff)
.set VI_CLK,        0x6C # VI Clock Select Register
.set VI_SEL,        0x6E # VI DTV Status Register
.set VI_70,         0x70 # ?
.set VI_HBE,        0x72 # Border HBE
.set VI_HBS,        0x74 # Border HBS
.set VI_76,         0x76 # ?
.set VI_78,         0x78 # ?
.set VI_7C,         0x7C # ?

.set PI_REGS_BASE, 0xCC003000
.set PI_INTSR,      0x00 # interrupt cause
.set PI_INTMR,      0x04 # interrupt mask
.set PI_0C,         0x0C # FIFO Base Start
.set PI_10,         0x10 # FIFO Base End?
.set PI_14,         0x14 # PI (cpu) FIFO current Write Pointer?
.set PI_18,         0x18 # ?
.set PI_1C,         0x1C # ?
.set PI_20,         0x20 # ?
.set PI_24,         0x24 # Reset?
.set PI_2C,         0x2C # ?

.set MI_REGS_BASE, 0xCC004000
.set MI_00,         0x00 # Protected Region No1
.set MI_04,         0x04 # Protected Region No2
.set MI_08,         0x08 # Protected Region No3
.set MI_0C,         0x0C # Protected Region No4
.set MI_10,         0x10 # type of the protection, 4*2 bits
.set MI_1C,         0x1C # MI interrupt mask
.set MI_1E,         0x1E # interrupt cause
.set MI_20,         0x20 # ?
.set MI_22,         0x22 # ADDRLO - address which failed protection rules
.set MI_24,         0x24 # ADDRHI - address, which failed protection rules
.set MI_28,         0x28 # ?
.set MI_32,         0x32 # TIMERHI
.set MI_34,         0x34 # TIMERLO
.set MI_36,         0x36 # TIMERHI
.set MI_38,         0x38 # TIMERLO
.set MI_3A,         0x3A # TIMERHI
.set MI_3C,         0x3C # TIMERLO
.set MI_3E,         0x3E # TIMERHI
.set MI_40,         0x40 # TIMERLO
.set MI_42,         0x42 # TIMERHI
.set MI_44,         0x44 # TIMERLO
.set MI_46,         0x46 # TIMERHI
.set MI_48,         0x48 # TIMERLO
.set MI_4A,         0x4A # TIMERHI
.set MI_4C,         0x4C # TIMERLO
.set MI_4E,         0x4E # TIMERHI
.set MI_50,         0x50 # TIMERLO
.set MI_52,         0x52 # TIMERHI
.set MI_54,         0x54 # TIMERLO
.set MI_56,         0x56 # TIMERHI
.set MI_58,         0x58 # TIMERLO
.set MI_5A,         0x5A # ?

.set DSP_REGS_BASE, 0xCC005000
.set DSP_00,        0x00 # DSP Mailbox High (to DSP)
.set DSP_02,        0x02 # DSP Mailbox Low (to DSP)
.set DSP_04,        0x04 # CPU Mailbox High (from DSP)
.set DSP_06,        0x06 # CPU Mailbox Low (from DSP)
.set DSP_0A,        0x0A # AI DSP CSR - Control Status Register (DSP Status)
.set DSP_12,        0x12 # AR_SIZE
.set DSP_14,        0x14 #
.set DSP_16,        0x16 # AR_MODE
.set DSP_1A,        0x1A # AR_REFRESH
.set DSP_20,        0x20 # AR_DMA_MMADDR_H
.set DSP_22,        0x22 # AR_DMA_MMADDR_L
.set DSP_24,        0x24 # AR_DMA_ARADDR_H
.set DSP_26,        0x26 # AR_DMA_ARADDR_L
.set DSP_28,        0x28 # AR_DMA_CNT_H
.set DSP_2A,        0x2A # AR_DMA_CNT_L
.set DSP_30,        0x30 # DMA Start address (High)
.set DSP_32,        0x32 # DMA Start address (Low)
.set DSP_36,        0x36 # DMA Control/DMA length (Length of Audio Data)
.set DSP_3A,        0x3A # DMA Bytes left

.set DI_REGS_BASE, 0xCC006000
.set DI_DISR,       0x00 # DI Status Register
.set DI_DICVR,      0x04 # DI Cover Register (status2)
.set DI_DICMDBUF0,  0x08 # DI Command Buffer 0
.set DI_DICMDBUF1,  0x0C # DI Command Buffer 1 (offset in 32 bit words)
.set DI_DICMDBUF2,  0x10 # DI Command Buffer 2 (source length)
.set DI_DIMAR,      0x14 # DMA Memory Address Register
.set DI_DILENGTH,   0x18 # DI DMA Transfer Length Register
.set DI_DICR,       0x1C # DI Control Register
.set DI_DIIMMBUF,   0x20 # DI immediate data buffer (error code ?)
.set DI_DICFG,      0x24 # DI Configuration Register

.set SI_REGS_BASE, 0xCC006400
.set SI_C0OUTBUF,   0x00 # SI Channel 0 Output Buffer (Joy-channel 1 Command)
.set SI_04,         0x04 # Joy-channel 1 Buttons 1
.set SI_08,         0x08 # Joy-channel 1 Buttons 2
.set SI_C1OUTBUF,   0x0C # SI Channel 1 Output Buffer (Joy-channel 2 Command)
.set SI_C1INBUFH,   0x10 # SI Channel 1 Input Buffer High (Joy-channel 2 Buttons 1)
.set SI_14,         0x14 # Joy-channel 2 Buttons 2
.set SI_C2OUTBUF,   0x18 # SI Channel 2 Output Buffer (Joy-channel 3 Command)
.set SI_1C,         0x1C # Joy-channel 3 Buttons 1
.set SI_20,         0x20 # Joy-channel 3 Buttons 2
.set SI_C3OUTBUF,   0x24 # SI Channel 3 Output Buffer (Joy-channel 4 Command)
.set SI_28,         0x28 # Joy-channel 4 Buttons 1
.set SI_C3INBUFL,   0x2C # SI Channel 3 Input Buffer Low (Joy-channel 4 Buttons 2)
.set SI_POLL,       0x30 # SI Poll Register (Joy-channel Control (?) (Calibration gun ?))
.set SI_COMCSR,     0x34 # SI Communication Control Status Register (command)
.set SI_SR,         0x38 # SI Status Register (channel select & status2)
.set SI_EXILK,      0x3C # SI EXI Clock Lock
.set SI_IOBUF,      0x80 # SI i/o buffer (access by word)

.set EXI_REGS_BASE, 0xCC006800
.set EXI_00,        0x00 # EXI0CSR - EXI Channel 0 Parameter Register (Status?)
.set EXI_04,        0x04 # EXI0MAR - EXI Channel 0 DMA Start Address
.set EXI_08,        0x08 # EXI0LENGTH - EXI Channel 0 DMA Transfer Length
.set EXI_0CR,       0x0C # EXI Channel 0 Control Register
.set EXI_0DATA,     0x10 # EXI Channel 0 Immediate Data
.set EXI_14,        0x14 # EXI1CSR - EXI Channel 1 Parameter Register
.set EXI_18,        0x18 # EXI1MAR - EXI Channel 1 DMA Start Address
.set EXI_1c,        0x1C # EXI Channel 1 DMA Transfer Length
.set EXI_1CR,       0x20 # EXI Channel 1 Control Register
.set EXI_1DATA,     0x24 # EXI Channel 1 Immediate Data
.set EXI_28,        0x28 # EXI2CSR - EXI Channel 2 Parameter Register
.set EXI_2c,        0x2C # EXI2MAR - EXI Channel 2 DMA Start Address
.set EXI_30,        0x30 # EXI Channel 2 DMA Transfer Length
.set EXI_2CR,       0x34 # EXI Channel 2 Control Register
.set EXI_2DATA,     0x38 # EXI Channel 2 Immediate Data

.set AI_REGS_BASE, 0xCC006C00
.set AI_CR,         0x00 # Audio Interface Control Register
.set AI_VR,         0x04 # Audio Interface Volume Register
.set AI_SCNT,       0x08 # Audio Interface Sample Counter
.set AI_IT,         0x0C # Audio Interface Interrupt Timing

.set GX_FIFO_BASE, 0xCC008000
