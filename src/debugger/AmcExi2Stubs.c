#include "debugger.h"

void EXI2_Init(volatile u8** param_1, __OSInterruptHandler param_2)) {}

int EXI2_EnableInterrupts(void) {}

int EXI2_Poll(void) { return false; }

int EXI2_ReadN(void* param1, u32 param2) { return AMC_EXI_NO_ERROR; }

int EXI2_WriteN(const void* data, u32 size) { return AMC_EXI_NO_ERROR; }

int EXI2_Reserve(void) {}

int EXI2_Unreserve(void) {}

bool AMC_IsStub(void) { return true; }
