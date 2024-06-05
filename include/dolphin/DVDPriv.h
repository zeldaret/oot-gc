#ifndef _DOLPHIN_DVDPRIV
#define _DOLPHIN_DVDPRIV

#include "dolphin/dvd.h"
#include "dolphin/hw_regs.h"
#include "dolphin/types.h"

typedef struct DVDDriveInfo {
    u16 revisionLevel;
    u16 deviceCode;
    u32 releaseDate;
    u8 padding[24];
} DVDDriveInfo;

typedef struct DVDBB1 {
    u32 appLoaderLength;
    void* appLoaderFunc1;
    void* appLoaderFunc2;
    void* appLoaderFunc3;
} DVDBB1;

typedef struct DVDBB2 {
    u32 bootFilePosition;
    u32 FSTPosition;
    u32 FSTLength;
    u32 FSTMaxLength;
    void* FSTAddress;
    u32 userPosition;
    u32 userLength;

    u32 padding0;
} DVDBB2;

typedef void (*DVDOptionalCommandChecker)(DVDCommandBlock* block, void (*cb)(u32 intType));
typedef void (*DVDLowCallback)(u32 intType);
extern DVDDiskID* DVDGetCurrentDiskID(void);
DVDLowCallback DVDLowClearCallback(void);
bool DVDLowSeek(u32 offset, DVDLowCallback callback);
void __DVDLowSetWAType(u32 type, u32 location);
DVDCommandBlock* __DVDPopWaitingQueue(void);
bool DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info, DVDCBCallback callback);
void __DVDPrepareResetAsync(DVDCBCallback callback);
bool DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback, s32 prio);
bool __DVDLowTestAlarm(struct OSAlarm* alarm);

#endif // _DOLPHIN_DVDPRIV
