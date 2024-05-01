#include "emulator/THPAudioDecode.h"
#include "dolphin.h"
#include "emulator/THPPlayer.h"

#define STACK_SIZE 0x1000
#define BUFFER_COUNT 3

static OSThread AudioDecodeThread;
static u8 AudioDecodeThreadStack[4096];
static OSMessageQueue FreeAudioBufferQueue;
static OSMessageQueue DecodedAudioBufferQueue;
static void* FreeAudioBufferMessage[3];
static void* DecodedAudioBufferMessage[3];
static bool AudioDecodeThreadCreated;

static void* AudioDecoder(void* _);
static void* AudioDecoderForOnMemory(void* bufPtr);
static void AudioDecode(THPReadBuffer* readBuffer);

bool CreateAudioDecodeThread(OSPriority prio, void* param) {
    bool res;
    if (param) {
        res = OSCreateThread(&AudioDecodeThread, AudioDecoderForOnMemory, param, AudioDecodeThreadStack + STACK_SIZE,
                             STACK_SIZE, prio, OS_THREAD_ATTR_DETACH);
        if (!res) {
            OSReport("Can't create audio decode thread\n");
            return false;
        }
    } else {
        res = OSCreateThread(&AudioDecodeThread, AudioDecoder, NULL, AudioDecodeThreadStack + STACK_SIZE, STACK_SIZE,
                             prio, OS_THREAD_ATTR_DETACH);
        if (!res) {
            OSReport("Can't create audio decode thread\n");
            return false;
        }
    }

    OSInitMessageQueue(&FreeAudioBufferQueue, FreeAudioBufferMessage, BUFFER_COUNT);
    OSInitMessageQueue(&DecodedAudioBufferQueue, DecodedAudioBufferMessage, BUFFER_COUNT);
    AudioDecodeThreadCreated = true;
    return true;
}

void AudioDecodeThreadStart() {
    if (AudioDecodeThreadCreated) {
        OSResumeThread(&AudioDecodeThread);
    }
}

static void* AudioDecoder(void* _) {
    THPReadBuffer* buf;
    while (true) {
        buf = (THPReadBuffer*)PopReadedBuffer();
        AudioDecode(buf);
        PushReadedBuffer2((OSMessage*)buf);
    }
}

static void* AudioDecoderForOnMemory(void* ptr) {
    THPReadBuffer readBuffer;
    s32 tmp;
    s32 size;
    s32 readFrame;
    s32 frameNumber;

    size = ActivePlayer.initReadSize;
    readBuffer.ptr = (u8*)ptr;
    readFrame = 0;

    while (true) {
        readBuffer.frameNumber = readFrame;
        AudioDecode(&readBuffer);
        frameNumber = (s32)((readFrame + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames);

        if (frameNumber == ActivePlayer.header.numFrames - 1) {
            if (ActivePlayer.playFlag & 1) {
                size = *(s32*)(readBuffer.ptr);
                readBuffer.ptr = ActivePlayer.movieData;
            } else {
                OSSuspendThread(&AudioDecodeThread);
            }
        } else {
            tmp = *(s32*)(readBuffer.ptr);
            readBuffer.ptr += size;
            size = tmp;
        }

        readFrame++;
    }

    return NULL;
}

static void AudioDecode(THPReadBuffer* readBuffer) {
    THPAudioBuffer* audioBuf;
    s32 i;
    u32* offsets;
    u8* audioData;

    offsets = (u32*)(readBuffer->ptr + 8);
    audioData = &readBuffer->ptr[ActivePlayer.compInfo.numComponents * 4] + 8;
    audioBuf = (THPAudioBuffer*)PopFreeAudioBuffer();

    for (i = 0; i < ActivePlayer.compInfo.numComponents; i++) {
        switch (ActivePlayer.compInfo.frameComp[i]) {
            case 1: {
                audioBuf->validSample =
                    THPAudioDecode(audioBuf->buffer, (audioData + *offsets * ActivePlayer.curAudioTrack), 0);
                audioBuf->curPtr = audioBuf->buffer;
                PushDecodedAudioBuffer(audioBuf);
                return;
            }
        }

        audioData += *offsets;
        offsets++;
    }
}

void* PopFreeAudioBuffer() {
    void* buf;
    OSReceiveMessage(&FreeAudioBufferQueue, &buf, 1);
    return buf;
}

void PushFreeAudioBuffer(void* buf) { OSSendMessage(&FreeAudioBufferQueue, buf, OS_MESSAGE_NOBLOCK); }

void* PopDecodedAudioBuffer(s32 flags) {
    void* buf;
    bool res = OSReceiveMessage(&DecodedAudioBufferQueue, &buf, flags);
    if (res == true) {
        return buf;
    }
    return NULL;
}

void PushDecodedAudioBuffer(void* buf) { OSSendMessage(&DecodedAudioBufferQueue, buf, 1); }
