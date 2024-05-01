#ifndef _DOLPHIN_EXI_H_
#define _DOLPHIN_EXI_H_

#include "dolphin/os.h"
#include "dolphin/types.h"

#ifdef __MWERKS__
u32 OS_EXI[0x40] : 0xCC006800;
#else
#define OS_EXI ((u32*)0xCC006800)
#endif

typedef void (*EXICallback)(s32 chan, OSContext* context);

EXICallback EXISetExiCallback(s32 channel, EXICallback callback);

void EXIInit(void);
bool EXILock(s32 channel, u32 device, EXICallback callback);
bool EXIUnlock(s32 channel);
bool EXISelect(s32 channel, u32 device, u32 frequency);
bool EXIDeselect(s32 channel);
bool EXIImm(s32 channel, void* buffer, s32 length, u32 type, EXICallback callback);
bool EXIImmEx(s32 channel, void* buffer, s32 length, u32 type);
bool EXIDma(s32 channel, void* buffer, s32 length, u32 type, EXICallback callback);
bool EXISync(s32 channel);
bool EXIProbe(s32 channel);
s32 EXIProbeEx(s32 channel);
bool EXIAttach(s32 channel, EXICallback callback);
bool EXIDetach(s32 channel);
u32 EXIGetState(s32 channel);
s32 EXIGetID(s32 channel, u32 device, u32* id);

#endif
