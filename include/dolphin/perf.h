#ifndef _DOLPHIN_PERF_H_
#define _DOLPHIN_PERF_H_

#include <dolphin/types.h>

typedef u8 PERFId;

typedef enum 
{
    PERF_CPU_EVENT,
    PERF_CPU_GP_EVENT,
    PERF_GP_EVENT,
} PerfType;

typedef void *(*PERFAllocator)(u32 size);
typedef void (*PERFDeallocator)(void *block);
typedef void (*PERFDrawCallback)(void);

u32 PERFInit(u32 numSamples, u32 numFramesHistory, u32 numTypes,
    PERFAllocator allocator, PERFDeallocator deallocator, PERFDrawCallback initDraw);
void PERFEventStart(PERFId id);
void PERFEventEnd(PERFId id);
void PERFSetEvent(PERFId id, char *name, PerfType type);
void PERFSetDrawBWBarKey(BOOL tf);
void PERFDumpScreen(void);
void PERFStartFrame(void);
void PERFEndFrame(void);
void PERFStartAutoSampling(f32 msInterval);
void PERFStopAutoSampling(void);
void PERFPreDraw(void);
void PERFPostDraw(void);

#endif
