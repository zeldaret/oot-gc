#include "emulator/THPVideoDecode.h"
#include "dolphin.h"
#include "emulator/THPPlayer.h"
#include "emulator/THPRead.h"

#define STACK_SIZE 0x1000
#define BUFFER_COUNT 3

static OSThread VideoDecodeThread;
static u8 VideoDecodeThreadStack[4096];
static OSMessageQueue FreeTextureSetQueue;
static OSMessageQueue DecodedTextureSetQueue;
static void* FreeTextureSetMessage[3];
static void* DecodedTextureSetMessage[3];
static bool VideoDecodeThreadCreated;
static bool First;

static void* VideoDecoder(void* ptr);
static void* VideoDecoderForOnMemory(void* ptr);
static void VideoDecode(THPReadBuffer* readBuffer);

bool CreateVideoDecodeThread(OSPriority priority, u8* ptr) {
    bool res;
    if (ptr) {
        res = OSCreateThread(&VideoDecodeThread, VideoDecoderForOnMemory, ptr, VideoDecodeThreadStack + STACK_SIZE,
                             STACK_SIZE, priority, 1);
        if (res == false) {
            OSReport("Can't create video decode thread\n");
            return false;
        }
    } else {
        res = OSCreateThread(&VideoDecodeThread, VideoDecoder, NULL, VideoDecodeThreadStack + STACK_SIZE, STACK_SIZE,
                             priority, 1);
        if (res == false) {
            OSReport("Can't create video decode thread\n");
            return false;
        }
    }

    OSInitMessageQueue(&FreeTextureSetQueue, FreeTextureSetMessage, BUFFER_COUNT);
    OSInitMessageQueue(&DecodedTextureSetQueue, DecodedTextureSetMessage, BUFFER_COUNT);
    VideoDecodeThreadCreated = true;
    First = true;
    return true;
}

void VideoDecodeThreadStart(void) {
    if (VideoDecodeThreadCreated) {
        OSResumeThread(&VideoDecodeThread);
    }
}

static void* VideoDecoder(void* ptr) {
    THPReadBuffer* readBuffer;
    s32 old;
    s32 decodedFrame = ActivePlayer.videoAhead;
    s32 remaining;

    while (true) {
        if (ActivePlayer.audioExist) {
            for (; ActivePlayer.videoAhead < 0; decodedFrame--) {
                readBuffer = (THPReadBuffer*)PopReadedBuffer2();
                remaining = (readBuffer->frameNumber + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
                if (remaining == (ActivePlayer.header.numFrames - 1) && (ActivePlayer.playFlag & 1) == 0) {
                    VideoDecode(readBuffer);
                }

                PushFreeReadBuffer((OSMessage*)readBuffer);
                old = OSDisableInterrupts();
                ActivePlayer.videoAhead++;
                OSRestoreInterrupts(old);
            }
        }

        if (ActivePlayer.audioExist) {
            readBuffer = (THPReadBuffer*)PopReadedBuffer2();
        } else {
            readBuffer = (THPReadBuffer*)PopReadedBuffer();
        }

        VideoDecode(readBuffer);
        PushFreeReadBuffer((OSMessage*)readBuffer);
    }

    return NULL;
}

static void* VideoDecoderForOnMemory(void* arg) {
    s32 readSize;
    s32 frame;
    u32 i;
    THPReadBuffer readBuffer;
    s32 remaining;

    frame = 0;
    i = 0;
    readSize = ActivePlayer.initReadSize;

    readBuffer.ptr = (u8*)arg;
    while (true) {
        if (ActivePlayer.audioExist) {
            while (ActivePlayer.videoAhead < 0) {
                bool old = OSDisableInterrupts();
                ActivePlayer.videoAhead++;
                OSRestoreInterrupts(old);
                remaining = (frame + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
                if (remaining == ActivePlayer.header.numFrames - 1) {
                    if ((ActivePlayer.playFlag & 1) == 0) {
                        break;
                    }

                    readSize = *(s32*)readBuffer.ptr;
                    readBuffer.ptr = ActivePlayer.movieData;
                } else {
                    s32 size = *(s32*)readBuffer.ptr;
                    readBuffer.ptr += readSize;
                    readSize = size;
                }
                frame++;
            }
        }

        readBuffer.frameNumber = frame;

        VideoDecode(&readBuffer);

        remaining = (frame + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
        if (remaining == ActivePlayer.header.numFrames - 1) {
            if ((ActivePlayer.playFlag & 1)) {
                readSize = *(s32*)readBuffer.ptr;
                readBuffer.ptr = ActivePlayer.movieData;
            } else {
                OSSuspendThread(&VideoDecodeThread);
            }
        } else {
            s32 size = *(s32*)readBuffer.ptr;
            readBuffer.ptr += readSize;
            readSize = size;
        }

        frame++;
    }

    return NULL;
}

static void VideoDecode(THPReadBuffer* readBuffer) {
    THPTextureSet* textureSet;
    s32 i;
    u32* compSizePtr;
    u8* ptr;
    s32 old;

    compSizePtr = (u32*)(readBuffer->ptr + 8);
    ptr = readBuffer->ptr + ActivePlayer.compInfo.numComponents * 4 + 8;
    textureSet = (THPTextureSet*)PopFreeTextureSet();

    for (i = 0; i < ActivePlayer.compInfo.numComponents; i++) {
        switch (ActivePlayer.compInfo.frameComp[i]) {
            case 0:
                if ((ActivePlayer.videoError = THPVideoDecode(ptr, textureSet->yTexture, textureSet->uTexture,
                                                              textureSet->vTexture, ActivePlayer.thpWork))) {
                    if (First) {
                        PrepareReady(false);
                        First = false;
                    }
                    OSSuspendThread(&VideoDecodeThread);
                }
                textureSet->frameNumber = readBuffer->frameNumber;
                PushDecodedTextureSet((OSMessage*)textureSet);
                old = OSDisableInterrupts();
                ActivePlayer.videoAhead++;
                OSRestoreInterrupts(old);
        }

        ptr += *compSizePtr;
        compSizePtr++;
    }

    if (First) {
        PrepareReady(true);
        First = false;
    }
}

void* PopFreeTextureSet(void) {
    void* msg;
    OSReceiveMessage(&FreeTextureSetQueue, &msg, 1);
    return msg;
}

void PushFreeTextureSet(void* buffer) { OSSendMessage(&FreeTextureSetQueue, buffer, 0); }

void* PopDecodedTextureSet(s32 flag) {
    void* msg;
    if (OSReceiveMessage(&DecodedTextureSetQueue, &msg, flag) == true) {
        return msg;
    }
    return NULL;
}

void PushDecodedTextureSet(void* buffer) { OSSendMessage(&DecodedTextureSetQueue, buffer, OS_MESSAGE_BLOCK); }
