#ifndef _METROTRK_TRK_H
#define _METROTRK_TRK_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void InitMetroTRK(void);
void InitMetroTRK_BBA(void);

void EnableMetroTRKInterrupts(void);

#ifdef __cplusplus
}
#endif

#endif
