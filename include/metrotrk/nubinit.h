#ifndef _METROTRK_NUBINIT_H
#define _METROTRK_NUBINIT_H

#include "dolphin/types.h"
#include "metrotrk/dserror.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKInitializeNub(void);
void TRKNubWelcome(void);
DSError TRKTerminateNub(void);
bool TRKInitializeEndian(void);

extern bool gTRKBigEndian;

#ifdef __cplusplus
}
#endif

#endif
