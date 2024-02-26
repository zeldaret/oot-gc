#ifndef _DOLPHIN_OS_H_
#define _DOLPHIN_OS_H_

#include "dolphin/os/OSAlarm.h"
#include "dolphin/os/OSAlloc.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSError.h"
#include "dolphin/os/OSFont.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSMessage.h"
#include "dolphin/os/OSModule.h"
#include "dolphin/os/OSMutex.h"
#include "dolphin/os/OSReset.h"
#include "dolphin/os/OSResetSW.h"
#include "dolphin/os/OSRtc.h"
#include "dolphin/os/OSThread.h"
#include "dolphin/os/OSTime.h"

#define OS_BASE_CACHED 0x80000000
#define OS_BASE_UNCACHED 0xC0000000

#ifdef __MWERKS__
u32 __OSBusClock : (OS_BASE_CACHED | 0x00F8);
u32 __OSCoreClock : (OS_BASE_CACHED | 0x00FC);
OSThread* __gUnkThread1 : (OS_BASE_CACHED | 0x00D8);
OSThreadQueue __OSActiveThreadQueue : (OS_BASE_CACHED | 0x00DC);
OSThread* __gCurrentThread : (OS_BASE_CACHED | 0x00E4);
#else
#define __OSBusClock (*(u32*)(OS_BASE_CACHED | 0x00F8))
#define __OSCoreClock (*(u32*)(OS_BASE_CACHED | 0x00FC))
#endif
#define OS_BUS_CLOCK __OSBusClock
#define OS_CORE_CLOCK __OSCoreClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

#define OSTicksToSeconds(ticks) ((ticks) / (OS_TIMER_CLOCK))
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))
#define OSTicksToMicroseconds(ticks) ((ticks)*8 / (OS_TIMER_CLOCK / 125000))
#define OSSecondsToTicks(sec) ((sec) * (OS_TIMER_CLOCK))
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSNanosecondsToTicks(nsec) (((nsec) * (OS_TIMER_CLOCK / 125000)) / 8000)

void OSInit(void);

void* OSGetArenaHi(void);
void* OSGetArenaLo(void);
void OSSetArenaHi(void*);
void OSSetArenaLo(void*);

typedef u8 __OSException;
typedef void (*__OSExceptionHandler)(__OSException exception, OSContext* context);

__OSExceptionHandler __OSSetExceptionHandler(__OSException exception, __OSExceptionHandler handler);
__OSExceptionHandler __OSGetExceptionHandler(__OSException exception);

u32 OSGetConsoleType(void);
void __OSPSInit(void);
void __OSFPRInit(void);
void OSRegisterVersion(const char* id);

typedef struct OSCalendarTime {
    /* 0x00 */ s32 sec;
    /* 0x04 */ s32 min;
    /* 0x08 */ s32 hour;
    /* 0x0C */ s32 mday;
    /* 0x10 */ s32 mon;
    /* 0x14 */ s32 year;
    /* 0x18 */ s32 wday;
    /* 0x1C */ s32 yday;
    /* 0x20 */ s32 msec;
    /* 0x24 */ s32 usec;
} OSCalendarTime;

OSTick OSGetTick(void);
OSTime OSGetTime(void);
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td);
BOOL OSEnableInterrupts(void);
BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);

#define OS_SOUND_MODE_MONO 0
#define OS_SOUND_MODE_STEREO 1

u32 OSGetSoundMode(void);
void OSSetSoundMode(u32 mode);

void OSReport(char*, ...);
void OSPanic(char* file, s32 line, char* msg, ...);

#define OSRoundUp32B(x) (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

#endif
