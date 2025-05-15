#ifndef _METROTRK_TRK_GLUE_H
#define _METROTRK_TRK_GLUE_H

#include "dolphin/os/OSInterrupt.h"
#include "dolphin/types.h"
#include "metrotrk/UART.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HARDWARE_GDEV = 0,
    HARDWARE_NDEV = 1,
    HARDWARE_BBA = 2
} HardwareType;

typedef int (*DBCommFunc)();
typedef int (*DBCommInitFunc)(void*, __OSInterruptHandler);
typedef int (*DBCommReadFunc)(u8*, int);
typedef int (*DBCommWriteFunc)(const u8*, int);

typedef struct DBCommTable {
    /* 0x00 */ DBCommInitFunc initialize_func;
    /* 0x04 */ DBCommFunc initinterrupts_func;
    /* 0x08 */ DBCommFunc shutdown_func;
    /* 0x0C */ DBCommFunc peek_func;
    /* 0x10 */ DBCommReadFunc read_func;
    /* 0x14 */ DBCommWriteFunc write_func;
    /* 0x18 */ DBCommFunc open_func;
    /* 0x1C */ DBCommFunc close_func;
    /* 0x20 */ DBCommFunc pre_continue_func;
    /* 0x24 */ DBCommFunc post_stop_func;
} DBCommTable; // size = 0x28

int InitMetroTRKCommTable(int);
void TRKUARTInterruptHandler();
UARTError TRK_InitializeIntDrivenUART(u32, u32, void*);
void EnableEXI2Interrupts();
int TRKPollUART();
UARTError TRKReadUARTN(void*, u32);
UARTError TRK_WriteUARTN(const void*, u32);
void ReserveEXI2Port(void);
void UnreserveEXI2Port(void);
void TRK_board_display(char*);
void InitializeProgramEndTrap();

#ifdef __cplusplus
}
#endif

#endif
