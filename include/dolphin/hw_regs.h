#ifndef _DOLPHIN_HW_REGS_H
#define _DOLPHIN_HW_REGS_H

#include "dolphin/types.h"

#ifdef __MWERKS__
volatile u16 __VIRegs[59] AT_ADDRESS(0xCC002000);
volatile u32 __PIRegs[12] AT_ADDRESS(0xCC003000);
volatile u16 __MEMRegs[64] AT_ADDRESS(0xCC004000);
volatile u16 __DSPRegs[] AT_ADDRESS(0xCC005000);
volatile u32 __DIRegs[] AT_ADDRESS(0xCC006000);
volatile u32 __SIRegs[0x100] AT_ADDRESS(0xCC006400);
volatile u32 __EXIRegs[0x40] AT_ADDRESS(0xCC006800);
volatile u32 __AIRegs[8] AT_ADDRESS(0xCC006C00);
#else
#define __VIRegs ((volatile u16*)0xCC002000)
#define __PIRegs ((volatile u32*)0xCC003000)
#define __MEMRegs ((volatile u16*)0xCC004000)
#define __DSPRegs ((volatile u16*)0xCC005000)
#define __DIRegs ((volatile u32*)0xCC006000)
#define __SIRegs ((volatile u32*)0xCC006400)
#define __EXIRegs ((volatile u32*)0xCC006800)
#define __AIRegs ((volatile u32*)0xCC006C00)
#endif

// Offsets for __VIRegs

// offsets for __VIRegs[i]
#define VI_VERT_TIMING (0)
#define VI_DISP_CONFIG (1)
#define VI_HORIZ_TIMING_0L (2)
#define VI_HORIZ_TIMING_0U (3)
#define VI_HORIZ_TIMING_1L (4)
#define VI_HORIZ_TIMING_1U (5)
#define VI_VERT_TIMING_ODD (6)
#define VI_VERT_TIMING_ODD_U (7)
#define VI_VERT_TIMING_EVEN (8)
#define VI_VERT_TIMING_EVEN_U (9)

#define VI_BBI_ODD (10) // burst blanking interval
#define VI_BBI_ODD_U (11) // burst blanking interval
#define VI_BBI_EVEN (12) // burst blanking interval
#define VI_BBI_EVEN_U (13) // burst blanking interval

#define VI_TOP_FIELD_BASE_LEFT (14) // top in 2d, top of left pic in 3d
#define VI_TOP_FIELD_BASE_LEFT_U (15) // top in 2d, top of left pic in 3d

#define VI_TOP_FIELD_BASE_RIGHT (16) // top of right pic in 3d
#define VI_TOP_FIELD_BASE_RIGHT_U (17) // top of right pic in 3d

#define VI_BTTM_FIELD_BASE_LEFT (18) // bottom in 2d, bottom of left pic in 3d
#define VI_BTTM_FIELD_BASE_LEFT_U (19) // bottom in 2d, bottom of left pic in 3d

#define VI_BTTM_FIELD_BASE_RIGHT (20) // bottom of right pic in 3d
#define VI_BTTM_FIELD_BASE_RIGHT_U (21) // bottom of right pic in 3d

#define VI_VERT_COUNT (22) // vertical display position
#define VI_HORIZ_COUNT (23) // horizontal display position

#define VI_DISP_INT_0 (24) // display interrupt 0L
#define VI_DISP_INT_0U (25) // display interrupt 0U
#define VI_DISP_INT_1 (26) // display interrupt 1L
#define VI_DISP_INT_1U (27) // display interrupt 1U
#define VI_DISP_INT_2 (28) // display interrupt 2L
#define VI_DISP_INT_2U (29) // display interrupt 2U
#define VI_DISP_INT_3 (30) // display interrupt 3L
#define VI_DISP_INT_3U (31) // display interrupt 3U

#define VI_HSW (36) // horizontal scaling width
#define VI_HSR (37) // horizontal scaling register

#define VI_FCT_0 (38) // filter coefficient table 0L
#define VI_FCT_0U (39) // filter coefficient table 0U
#define VI_FCT_1 (40) // filter coefficient table 1L
#define VI_FCT_1U (41) // filter coefficient table 1U
#define VI_FCT_2 (42) // filter coefficient table 2L
#define VI_FCT_2U (43) // filter coefficient table 2U
#define VI_FCT_3 (44) // filter coefficient table 3L
#define VI_FCT_3U (45) // filter coefficient table 3U
#define VI_FCT_4 (46) // filter coefficient table 4L
#define VI_FCT_4U (47) // filter coefficient table 4U
#define VI_FCT_5 (48) // filter coefficient table 5L
#define VI_FCT_5U (49) // filter coefficient table 5U
#define VI_FCT_6 (50) // filter coefficient table 6L
#define VI_FCT_6U (51) // filter coefficient table 6U

#define VI_CLOCK_SEL (54) // clock select
#define VI_DTV_STAT (55) // DTV status

#define VI_WIDTH (56)

// offsets for __PIRegs[i]
#define PI_INTRPT_SRC (0) // interrupt cause
#define PI_INTRPT_MASK (1) // interrupt mask
#define PI_FIFO_START (3) // FIFO base start
#define PI_FIFO_END (4) // FIFO base end
#define PI_FIFO_PTR (5) // FIFO current write pointer

#define PI_RESETCODE (9) // reset code, used by OSReset

// PI Interrupt causes.
#define PI_INTRPT_ERR (0x1) // GP runtime error
#define PI_INTRPT_RSW (0x2) // reset switch
#define PI_INTRPT_DVD (0x4) // DVD/DI interrupt
#define PI_INTRPT_SI (0x8) // serial/controller interrupt
#define PI_INTRPT_EXI (0x10) // external mem interrupt
#define PI_INTRPT_AI (0x20) // audio streaming interrupt
#define PI_INTRPT_DSP (0x40) // digital signal proc interrupt
#define PI_INTRPT_MEM (0x80) // memory interface interrupt
#define PI_INTRPT_VI (0x100) // video interface interrupt
#define PI_INTRPT_PE_TOKEN (0x200) // pixel engine token
#define PI_INTRPT_PE_FINISH (0x400) // pixel engine finish
#define PI_INTRPT_CP (0x800) // command FIFO
#define PI_INTRPT_DEBUG (0x1000) // external debugger
#define PI_INTRPT_HSP (0x2000) // high speed port
#define PI_INTRPT_RSWST (0x10000) // reset switch state (1 when pressed)

// offsets for __MEMRegs[i]
#define MEM_PROT_1 (0) // protected region 1
#define MEM_PROT_2 (2) // protected region 1
#define MEM_PROT_3 (4) // protected region 1
#define MEM_PROT_4 (6) // protected region 1
#define MEM_PROT_TYPE (8) // protection type

#define MEM_INTRPT_MASK (14) // interrupt mask
#define MEM_INTRPT_SRC (15) // interrupt cause
#define MEM_INTRPT_FLAG (16) // set when interrupt happens
#define MEM_INTRPT_ADDR_LO (17) // address that caused interrupt
#define MEM_INTRPT_ADDR_HI (18) // address that caused interrupt

#define MEM_UNK_FLAG (20) // unknown memory flag, set in __OSInitMemoryProtection

// offsets for __DSPRegs[i]
#define DSP_MAILBOX_IN_HI (0)
#define DSP_MAILBOX_IN_LO (1)
#define DSP_MAILBOX_OUT_HI (2)
#define DSP_MAILBOX_OUT_LO (3)
#define DSP_CONTROL_STATUS (5)

#define DSP_ARAM_SIZE (9)
#define DSP_ARAM_MODE (11)
#define DSP_ARAM_REFRESH (13)
#define DSP_ARAM_DMA_MM_HI (16) // Main mem address
#define DSP_ARAM_DMA_MM_LO (17)
#define DSP_ARAM_DMA_ARAM_HI (18) // ARAM address
#define DSP_ARAM_DMA_ARAM_LO (19)
#define DSP_ARAM_DMA_SIZE_HI (20) // DMA buffer size
#define DSP_ARAM_DMA_SIZE_LO (21)

#define DSP_DMA_START_HI (24) // DMA start address
#define DSP_DMA_START_LO (25)
#define DSP_DMA_CONTROL_LEN (27)
#define DSP_DMA_BYTES_LEFT (29)

#define DSP_DMA_START_FLAG (0x8000) // set to start DSP

// offsets for __DIRegs[i]
#define DI_STATUS (0)
#define DI_COVER_STATUS (1) // cover status - 0=normal, 1=interrupt/open
#define DI_CMD_BUF_0 (2) // command buffer 0
#define DI_CMD_BUF_1 (3) // command buffer 1
#define DI_CMD_BUF_2 (4) // command buffer 2
#define DI_DMA_MEM_ADDR (5) // DMA address
#define DI_DMA_LENGTH (6) // transfer length address
#define DI_CONTROL (7)
#define DI_MM_BUF (8) // Main memory buffer
#define DI_CONFIG (9)

// offsets for __SIRegs[i]
// Channel 0/Joy-channel 1
#define SI_CHAN_0_BUF (0) // output buffer
#define SI_CHAN_0_BTN_1 (1) // button 1
#define SI_CHAN_0_BTN_2 (2) // button 2
// Channel 1/Joy-channel 2
#define SI_CHAN_1_BUF (3) // output buffer
#define SI_CHAN_1_BTN_1 (4) // button 1
#define SI_CHAN_1_BTN_2 (5) // button 2
// Channel 2/Joy-channel 3
#define SI_CHAN_2_BUF (6) // output buffer
#define SI_CHAN_2_BTN_1 (7) // button 1
#define SI_CHAN_2_BTN_2 (8) // button 2
// Channel 3/Joy-channel 4
#define SI_CHAN_3_BUF (9) // output buffer
#define SI_CHAN_3_BTN_1 (10) // button 1
#define SI_CHAN_3_BTN_2 (11) // button 2

#define SI_POLL (12)
#define SI_CC_STAT (13) // communication control status
#define SI_STAT (14)
#define SI_EXI_LOCK (15) // exi clock lock

#define SI_IO_BUFFER (32) // start of buffer (32 to 63)

// offsets for __EXIRegs[i]
// Channel 0
#define EXI_CHAN_0_STAT (0) // parameters/status
#define EXI_CHAN_0_DMA_ADDR (1) // DMA start address
#define EXI_CHAN_0_LEN (2) // DMA transfer length
#define EXI_CHAN_0_CONTROL (3) // control register
#define EXI_CHAN_0_IMM (4) // immediate data
// Channel 1
#define EXI_CHAN_1_STAT (5) // parameters/status
#define EXI_CHAN_1_DMA_ADDR (6) // DMA start address
#define EXI_CHAN_1_LEN (7) // DMA transfer length
#define EXI_CHAN_1_CONTROL (8) // control register
#define EXI_CHAN_1_IMM (9) // immediate data
// Channel 2
#define EXI_CHAN_2_STAT (10) // parameters/status
#define EXI_CHAN_2_DMA_ADDR (11) // DMA start address
#define EXI_CHAN_2_LEN (12) // DMA transfer length
#define EXI_CHAN_2_CONTROL (13) // control register
#define EXI_CHAN_2_IMM (14) // immediate data

// offsets for __AIRegs[i]
#define AI_CONTROL (0) // control
#define AI_VOLUME (1) // volume
#define AI_SAMPLE_COUNTER (2) // number of stereo samples output
#define AI_INTRPT_TIMING (3) // interrupt timing

#define AI_CONTROL_PLAY_STATE (0x1)
#define AI_CONTROL_STREAM_SAMPLE_RATE (0x2)
#define AI_CONTROL_DSP_SAMPLE_COUNT (0x4)
#define AI_CONTROL_UNKNOWN8 (0x8)
#define AI_CONTROL_STREAM_SAMPLE_COUNT (0x20)
#define AI_CONTROL_DSP_SAMPLE_RATE (0x40)

#define FP0 fp0
#define FP1 fp1
#define FP2 fp2
#define FP3 fp3
#define FP4 fp4
#define FP5 fp5
#define FP6 fp6
#define FP7 fp7
#define FP8 fp8
#define FP9 fp9
#define FP10 fp10
#define FP11 fp11
#define FP12 fp12
#define FP13 fp13
#define FP14 fp14
#define FP15 fp15
#define FP31 fp31

#endif
