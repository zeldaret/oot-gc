#include "dolphin.h"

char D_800EA520[] = "Can't create video decode thread\n";

static OSThread VideoDecodeThread;
static u8 VideoDecodeThreadStack[4096];
static OSMessageQueue FreeTextureSetQueue;
static OSMessageQueue DecodedTextureSetQueue;
static void* FreeTextureSetMessage[3];
static void* DecodedTextureSetMessage[3];
static s32 VideoDecodeThreadCreated;
static s32 First;

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/PushDecodedTextureSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/PopDecodedTextureSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/PushFreeTextureSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/PopFreeTextureSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/VideoDecode.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/VideoDecoderForOnMemory.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/VideoDecoder.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/VideoDecodeThreadStart.s")

#pragma GLOBAL_ASM("asm/non_matchings/THPVideoDecode/CreateVideoDecodeThread.s")
