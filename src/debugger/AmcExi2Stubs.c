#include "debugger.h"

void EXI2_Init(void) {}

void EXI2_EnableInterrupts(void) {}

bool EXI2_Poll(void) { return false; }

AmcExiError EXI2_ReadN(void) { return AMC_EXI_NO_ERROR; }

AmcExiError EXI2_WriteN(void) { return AMC_EXI_NO_ERROR; }

void EXI2_Reserve(void) {}

void EXI2_Unreserve(void) {}

bool AMC_IsStub(void) { return true; }
