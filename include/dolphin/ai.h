#ifndef _DOLPHIN_AI_H_
#define _DOLPHIN_AI_H_

#include "dolphin/hw_regs.h"
#include "dolphin/types.h"

typedef void (*AIDCallback)(void);

AIDCallback AIRegisterDMACallback(AIDCallback);
void AIInitDMA(u32 start_addr, u32 length);
bool AIGetDMAEnableFlag(void);
void AIStartDMA(void);
void AIStopDMA(void);
u32 AIGetDMABytesLeft(void);
u32 AIGetDMAStartAddr(void);

void AISetStreamPlayState(u32 state);
u32 AIGetStreamPlayState(void);

#define AI_SAMPLERATE_32KHZ 0
#define AI_SAMPLERATE_48KHZ 1

void AISetDSPSampleRate(u32 rate);
u32 AIGetDSPSampleRate(void);

u32 AIGetStreamSampleRate(void);

void AISetStreamVolLeft(u8 volume);
u8 AIGetStreamVolLeft(void);
void AISetStreamVolRight(u8 volume);
u8 AIGetStreamVolRight(void);
void AIInit(u8* stack);

#endif
