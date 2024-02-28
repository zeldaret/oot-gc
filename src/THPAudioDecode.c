#include "dolphin.h"

char D_800EA488[34] = "Can't create audio decode thread\n";

static OSThread AudioDecodeThread;
static u8 AudioDecodeThreadStack[4096];
static OSMessageQueue FreeAudioBufferQueue;
static OSMessageQueue DecodedAudioBufferQueue;
static void* FreeAudioBufferMessage[3];
static void* DecodedAudioBufferMessage[3];
static s32 AudioDecodeThreadCreated;

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/PushDecodedAudioBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/PopDecodedAudioBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/PushFreeAudioBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/PopFreeAudioBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/AudioDecode.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/AudioDecoderForOnMemory.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/AudioDecoder.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/AudioDecodeThreadStart.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPAudioDecode/CreateAudioDecodeThread.s")
