#include "dolphin.h"
#include "debugger.h"

void EXI2_Init(void) {}

void EXI2_EnableInterrupts(void) {}

s32 EXI2_Poll(void) { return 0; }

AmcExiError EXI2_ReadN(void) { return AMC_EXI_NO_ERROR; }

AmcExiError EXI2_WriteN(void) { return AMC_EXI_NO_ERROR; }

void EXI2_Reserve(void) {}

void EXI2_Unreserve(void) {}

s32 AMC_IsStub(void) { return 1; }
