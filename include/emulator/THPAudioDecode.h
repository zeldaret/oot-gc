#ifndef THP_AUDIO_DECODE_H
#define THP_AUDIO_DECODE_H

#include "dolphin.h"

bool CreateAudioDecodeThread(OSPriority prio, void* param);
void AudioDecodeThreadStart();
void AudioDecodeThreadCancel();
void* PopFreeAudioBuffer();
void PushFreeAudioBuffer(void* buf);
void* PopDecodedAudioBuffer(s32 flags);
void PushDecodedAudioBuffer(void* buf);

#endif
