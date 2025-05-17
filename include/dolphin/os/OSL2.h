#ifndef _DOLPHIN_OS_OSL2_H
#define _DOLPHIN_OS_OSL2_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void L2Enable(void);
void L2Disable(void);
void L2GlobalInvalidate(void);
void L2SetDataOnly(bool dataOnly);
void L2SetWriteThrough(bool writeThrough);

#ifdef __cplusplus
}
#endif

#endif
