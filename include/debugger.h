#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "dolphin.h"

// EXI error codes
typedef enum {
    AMC_EXI_NO_ERROR = 0,
    AMC_EXI_UNSELECTED = 1
} AmcExiError;

void DBInitComm(volatile u8** param_1, __OSInterruptHandler param_2);
int DBInitInterrupts(void);
int DBQueryData(void);
int DBRead(void* param1, u32 param2);
int DBWrite(const void* data, u32 size);
int DBOpen(void);
int DBClose(void);

void EXI2_Init(volatile u8** param_1, __OSInterruptHandler param_2);
int EXI2_EnableInterrupts(void);
int EXI2_Poll(void);
int EXI2_ReadN(void* param1, u32 param2);
int EXI2_WriteN(const void* data, u32 size);
int EXI2_Reserve(void);
int EXI2_Unreserve(void);
bool AMC_IsStub(void);

bool Hu_IsStub(void);

#endif
