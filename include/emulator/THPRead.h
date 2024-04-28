#ifndef _THPREAD_H
#define _THPREAD_H

#include "dolphin.h"

typedef enum MovieMessage {
    M_M_NONE = -1,
    M_M_DISK_COVER_OPEN = 0,
    M_M_DISK_WRONG_DISK = 1,
    M_M_DISK_READING_DISK = 2,
    M_M_DISK_FATAL_ERROR = 3,
    M_M_DISK_RETRY_ERROR = 4,
    M_M_DISK_NO_DISK = 5,
    M_M_DISK_DEFAULT_ERROR = 6,
} MovieMessage;

s32 movieGXInit();
s32 movieDrawImage(TEXPalettePtr tpl, s16 nX0, s16 nY0);
s32 movieDrawErrorMessage(MovieMessage movieMessage);
s32 movieDVDShowError(s32 nStatus, void*, s32, u32);
s32 movieDVDRead(DVDFileInfo* pFileInfo, void* anData, s32 nSizeRead, s32 nOffset);
s32 movieTestReset(s32 IPL, s32 forceMenu);
void movieReset(s32 IPL, s32 forceMenu);

s32 CreateReadThread(OSPriority priority);
void ReadThreadStart(void);
void ReadThreadCancel(void);
void* PopReadedBuffer();
void PushReadedBuffer(void* buffer);
void* PopFreeReadBuffer();
void PushFreeReadBuffer(void* buffer);
void* PopReadedBuffer2();
void PushReadedBuffer2(void* buffer);

extern s32 gMovieErrorToggle;

#endif
