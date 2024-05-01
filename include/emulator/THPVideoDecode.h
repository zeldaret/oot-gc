#ifndef THP_VIDEO_DECODE_H
#define THP_VIDEO_DECODE_H

#include "dolphin.h"

bool CreateVideoDecodeThread(OSPriority priority, u8* ptr);
void VideoDecodeThreadStart(void);
void VideoDecodeThreadCancel(void);
void* PopFreeTextureSet(void);
void PushFreeTextureSet(void* buffer);
void* PopDecodedTextureSet(s32 flag);
void PushDecodedTextureSet(void* buffer);

#endif
