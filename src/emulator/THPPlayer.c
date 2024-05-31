#include "emulator/THPPlayer.h"
#include "emulator/THPAudioDecode.h"
#include "emulator/THPDraw.h"
#include "emulator/THPRead.h"
#include "emulator/THPVideoDecode.h"
#include "macros.h"
#include "string.h"

u16 VolumeTable[128] = {
    0x0000, 0x0002, 0x0008, 0x0012, 0x0020, 0x0032, 0x0049, 0x0063, 0x0082, 0x00A4, 0x00CB, 0x00F5, 0x0124,
    0x0157, 0x018E, 0x01C9, 0x0208, 0x024B, 0x0292, 0x02DD, 0x032C, 0x037F, 0x03D7, 0x0432, 0x0492, 0x04F5,
    0x055D, 0x05C9, 0x0638, 0x06AC, 0x0724, 0x07A0, 0x0820, 0x08A4, 0x092C, 0x09B8, 0x0A48, 0x0ADD, 0x0B75,
    0x0C12, 0x0CB2, 0x0D57, 0x0DFF, 0x0EAC, 0x0F5D, 0x1012, 0x10CA, 0x1187, 0x1248, 0x130D, 0x13D7, 0x14A4,
    0x1575, 0x164A, 0x1724, 0x1801, 0x18E3, 0x19C8, 0x1AB2, 0x1BA0, 0x1C91, 0x1D87, 0x1E81, 0x1F7F, 0x2081,
    0x2187, 0x2291, 0x239F, 0x24B2, 0x25C8, 0x26E2, 0x2801, 0x2923, 0x2A4A, 0x2B75, 0x2CA3, 0x2DD6, 0x2F0D,
    0x3048, 0x3187, 0x32CA, 0x3411, 0x355C, 0x36AB, 0x37FF, 0x3956, 0x3AB1, 0x3C11, 0x3D74, 0x3EDC, 0x4048,
    0x41B7, 0x432B, 0x44A3, 0x461F, 0x479F, 0x4923, 0x4AAB, 0x4C37, 0x4DC7, 0x4F5C, 0x50F4, 0x5290, 0x5431,
    0x55D6, 0x577E, 0x592B, 0x5ADC, 0x5C90, 0x5E49, 0x6006, 0x61C7, 0x638C, 0x6555, 0x6722, 0x68F4, 0x6AC9,
    0x6CA2, 0x6E80, 0x7061, 0x7247, 0x7430, 0x761E, 0x7810, 0x7A06, 0x7C00, 0x7DFE, 0x8000,
};

static s32 WorkBuffer[16];
static OSMessageQueue PrepareReadyQueue;
static OSMessageQueue UsedTextureSetQueue;
static void* UsedTextureSetMessage[3];
static s16 SoundBuffer[2][320] ATTRIBUTE_ALIGN(32);
THPPlayer ActivePlayer;

static bool Initialized;
static void* PrepareReadyMessage;
static void (*OldVIPostCallback)(u32);
static s32 SoundBufferIndex;
static void (*OldAIDCallback)(void);
static s16* LastAudioBuffer;
static s16* CurAudioBuffer;
static bool AudioSystem;

static void PlayControl(u32 retraceCnt);
static bool ProperTimingForStart(void);
static bool ProperTimingForGettingNextFrame(void);
static void PushUsedTextureSet(OSMessage msg);
static OSMessage PopUsedTextureSet(void);
static void MixAudio(s16* destination, s16* source, u32 sample);
static void THPAudioMixCallback(void);

void THPGXYuv2RgbDraw(u8* y_data, u8* u_data, u8* v_data, s16 x, s16 y, s16 textureWidth, s16 textureHeight,
                      s16 polygonWidth, s16 polygonHeight);

bool THPPlayerInit(bool audioSystem) {
    bool old;

    memset(&ActivePlayer, 0, sizeof(THPPlayer));
    LCEnable();
    OSInitMessageQueue(&UsedTextureSetQueue, UsedTextureSetMessage, 3);

    if (!THPInit()) {
        return false;
    }

    old = OSDisableInterrupts();

    AudioSystem = audioSystem;
    SoundBufferIndex = 0;
    LastAudioBuffer = NULL;
    CurAudioBuffer = NULL;
    OldAIDCallback = AIRegisterDMACallback(THPAudioMixCallback);
    if (OldAIDCallback == NULL && AudioSystem) {
        AIRegisterDMACallback(NULL);
        OSRestoreInterrupts(old);
        OSReport("Pleae call AXInit or sndInit before you call THPPlayerInit\n");
        return false;
    }

    OSRestoreInterrupts(old);

    if (!AudioSystem) {
        memset(SoundBuffer, 0, sizeof(SoundBuffer));
        DCFlushRange(SoundBuffer, sizeof(SoundBuffer));
        AIInitDMA((u32)&SoundBuffer[SoundBufferIndex], 320 * 2);
        AIStartDMA();
    }

    Initialized = true;
    return true;
}

bool THPPlayerOpen(char* fileName, bool onMemory) {
    s32 readOffset;
    s32 i;

    if (!Initialized) {
        OSReport("You must call THPPlayerInit before you call this function\n");
        return false;
    }

    if (ActivePlayer.open) {
        OSReport("Can't open %s because a thp file is already opened.\n");
        return false;
    }

    memset(&ActivePlayer.videoInfo, 0, sizeof(THPVideoInfo));
    memset(&ActivePlayer.audioInfo, 0, sizeof(THPAudioInfo));

    if (DVDOpen((char*)fileName, &ActivePlayer.fileInfo) == false) {
        OSReport("Can't open %s.\n", fileName);
        return false;
    }

    movieDVDRead(&ActivePlayer.fileInfo, WorkBuffer, 64, 0);
    memcpy(&ActivePlayer.header.magic, WorkBuffer, sizeof(THPHeader));

    if (strcmp(ActivePlayer.header.magic, "THP") != 0) {
        OSReport("This file is not a THP file.\n");
        DVDClose(&ActivePlayer.fileInfo);
        return false;
    }

    if (ActivePlayer.header.version != 0x11000) {
        OSReport("invalid version.\n");
        DVDClose(&ActivePlayer.fileInfo);
        return false;
    }

    readOffset = ActivePlayer.header.compInfoDataOffsets;
    movieDVDRead(&ActivePlayer.fileInfo, WorkBuffer, 32, readOffset);
    memcpy(&ActivePlayer.compInfo, WorkBuffer, sizeof(THPFrameCompInfo));
    readOffset += sizeof(THPFrameCompInfo);
    ActivePlayer.audioExist = false;

    for (i = 0; i < ActivePlayer.compInfo.numComponents; i++) {
        switch (ActivePlayer.compInfo.frameComp[i]) {
            case 0:
                movieDVDRead(&ActivePlayer.fileInfo, WorkBuffer, 32, readOffset);
                memcpy(&ActivePlayer.videoInfo, WorkBuffer, sizeof(THPVideoInfo));
                readOffset += sizeof(THPVideoInfo);
                break;
            case 1:
                movieDVDRead(&ActivePlayer.fileInfo, WorkBuffer, 32, readOffset);
                memcpy(&ActivePlayer.audioInfo, WorkBuffer, sizeof(THPAudioInfo));
                readOffset += sizeof(THPAudioInfo);
                ActivePlayer.audioExist = true;
                break;
            default:
                OSReport("Unknown frame components.\n");
                return false;
        }
    }

    ActivePlayer.internalState = 0;
    ActivePlayer.state = 0;
    ActivePlayer.playFlag = 0;
    ActivePlayer.onMemory = onMemory;
    ActivePlayer.open = true;
    ActivePlayer.curVolume = 127.0f;
    ActivePlayer.targetVolume = ActivePlayer.curVolume;
    ActivePlayer.rampCount = 0;

    return true;
}

u32 THPPlayerCalcNeedMemory(void) {
    u32 size;

    if (ActivePlayer.open) {
        if (ActivePlayer.onMemory) {
            size = OSRoundUp32B(ActivePlayer.header.movieDataSize);
        } else {
            size = OSRoundUp32B(ActivePlayer.header.bufSize) * 10;
        }

        size += OSRoundUp32B(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize) * 3;
        size += OSRoundUp32B(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize / 4) * 3;
        size += OSRoundUp32B(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize / 4) * 3;

        if (ActivePlayer.audioExist) {
            size += OSRoundUp32B(ActivePlayer.header.audioMaxSamples * 4) * 3;
        }

        size += 0x1000;
        return size;
    }

    return 0;
}

bool THPPlayerSetBuffer(u8* buffer) {
    u32 i;
    u8* workPtr;
    u32 ySampleSize;
    u32 uvSampleSize;

    if (ActivePlayer.open && ActivePlayer.state == 0) {
        workPtr = buffer;

        if (ActivePlayer.onMemory) {
            ActivePlayer.movieData = buffer;
            workPtr += ActivePlayer.header.movieDataSize;
        } else {
            for (i = 0; i < ARRAY_COUNT(ActivePlayer.readBuffer); i++) {
                ActivePlayer.readBuffer[i].ptr = workPtr;
                workPtr += ALIGN_NEXT(ActivePlayer.header.bufSize, 32);
            }
        }

        ySampleSize = ALIGN_NEXT(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize, 32);
        uvSampleSize = ALIGN_NEXT(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize / 4, 32);

        for (i = 0; i < ARRAY_COUNT(ActivePlayer.textureSet); i++) {
            ActivePlayer.textureSet[i].yTexture = workPtr;

            DCInvalidateRange(workPtr, ySampleSize);
            workPtr += ySampleSize;

            ActivePlayer.textureSet[i].uTexture = workPtr;
            DCInvalidateRange(workPtr, uvSampleSize);
            workPtr += uvSampleSize;

            ActivePlayer.textureSet[i].vTexture = workPtr;
            DCInvalidateRange(workPtr, uvSampleSize);
            workPtr += uvSampleSize;
        }

        if (ActivePlayer.audioExist) {
            for (i = 0; i < ARRAY_COUNT(ActivePlayer.audioBuffer); i++) {
                ActivePlayer.audioBuffer[i].buffer = (s16*)workPtr;
                ActivePlayer.audioBuffer[i].curPtr = (s16*)workPtr;
                ActivePlayer.audioBuffer[i].validSample = 0;
                workPtr += ALIGN_NEXT(ActivePlayer.header.audioMaxSamples * 4, 32);
            }
        }

        ActivePlayer.thpWork = workPtr;
        return true;
    }

    return false;
}

void InitAllMessageQueue(void) {
    s32 i;
    THPReadBuffer* readBuffer;
    THPTextureSet* textureSet;
    THPAudioBuffer* audioBuffer;

    if (ActivePlayer.onMemory == false) {
        for (i = 0; i < 10; i++) {
            readBuffer = &ActivePlayer.readBuffer[i];
            PushFreeReadBuffer(readBuffer);
        }
    }

    for (i = 0; i < 3; i++) {
        textureSet = &ActivePlayer.textureSet[i];
        PushFreeTextureSet(textureSet);
    }

    if (ActivePlayer.audioExist) {
        for (i = 0; i < 3; i++) {
            audioBuffer = &ActivePlayer.audioBuffer[i];
            PushFreeAudioBuffer(audioBuffer);
        }
    }
    OSInitMessageQueue(&PrepareReadyQueue, &PrepareReadyMessage, 1);
}

static inline bool WaitUntilPrepare(void) {
    OSMessage msg;

    OSReceiveMessage(&PrepareReadyQueue, &msg, OS_MESSAGE_BLOCK);

    if ((bool)msg) {
        return true;
    } else {
        return false;
    }
}

void PrepareReady(s32 msg) { OSSendMessage(&PrepareReadyQueue, (OSMessage)msg, OS_MESSAGE_BLOCK); }

bool THPPlayerPrepare(s32 frame, s32 flag, s32 audioTrack) {
    s32 offset;
    u8* threadData;

    if (ActivePlayer.open && ActivePlayer.state == 0) {
        if (frame > 0) {
            if (ActivePlayer.header.offsetDataOffsets == 0) {
                OSReport("This thp file doesn't have the offset data\n");
                return false;
            }

            if (ActivePlayer.header.numFrames > frame) {
                offset = ActivePlayer.header.offsetDataOffsets + (frame - 1) * 4;
                movieDVDRead(&ActivePlayer.fileInfo, WorkBuffer, 0x20, offset);
                ActivePlayer.initOffset = (s32)(ActivePlayer.header.movieDataOffsets + WorkBuffer[0]);
                ActivePlayer.initReadFrame = frame;
                ActivePlayer.initReadSize = (s32)(WorkBuffer[1] - WorkBuffer[0]);

            } else {
                OSReport("Specified frame number is over total frame number\n");
                return false;
            }

        } else {
            ActivePlayer.initOffset = ActivePlayer.header.movieDataOffsets;
            ActivePlayer.initReadSize = ActivePlayer.header.firstFrameSize;
            ActivePlayer.initReadFrame = frame;
        }

        if (ActivePlayer.audioExist) {
            if (audioTrack < 0 || audioTrack >= ActivePlayer.audioInfo.sndNumTracks) {
                OSReport("Specified audio track number is invalid\n");
                return false;
            }
            ActivePlayer.curAudioTrack = audioTrack;
        }

        flag &= 1;
        ActivePlayer.playFlag = flag;
        ActivePlayer.videoAhead = 0;

        if (ActivePlayer.onMemory) {
            movieDVDRead(&ActivePlayer.fileInfo, ActivePlayer.movieData, ActivePlayer.header.movieDataSize,
                         ActivePlayer.header.movieDataOffsets);

            threadData = ActivePlayer.movieData + ActivePlayer.initOffset - ActivePlayer.header.movieDataOffsets;
            CreateVideoDecodeThread(20, threadData);

            if (ActivePlayer.audioExist) {
                CreateAudioDecodeThread(12, threadData);
            }

        } else {
            CreateVideoDecodeThread(20, NULL);
            if (ActivePlayer.audioExist) {
                CreateAudioDecodeThread(12, NULL);
            }
            CreateReadThread(8);
        }

        InitAllMessageQueue();
        VideoDecodeThreadStart();

        if (ActivePlayer.audioExist) {
            AudioDecodeThreadStart();
        }

        if (!ActivePlayer.onMemory) {
            ReadThreadStart();
        }

        if (!WaitUntilPrepare()) {
            return false;
        }

        ActivePlayer.state = 1;
        ActivePlayer.internalState = 0;
        ActivePlayer.dispTextureSet = NULL;
        ActivePlayer.playAudioBuffer = NULL;
        ActivePlayer.curVideoNumber = 0;
        ActivePlayer.curAudioNumber = 0;
        OldVIPostCallback = VISetPostRetraceCallback(PlayControl);

        return true;
    }

    return false;
}

bool THPPlayerPlay(void) {
    if (ActivePlayer.open && (ActivePlayer.state == 1 || ActivePlayer.state == 4)) {
        ActivePlayer.state = 2;
        ActivePlayer.prevCount = 0;
        ActivePlayer.curCount = 0;
        ActivePlayer.retraceCount = -1;

        return true;
    }
    return false;
}

static void PlayControl(u32 retraceCnt) {
    s32 audioFrame;
    s32 curFrame;
    THPTextureSet* decodedTexture;

    if (OldVIPostCallback != NULL) {
        OldVIPostCallback(retraceCnt);
    }

    decodedTexture = (THPTextureSet*)0xFFFFFFFF;
    if (ActivePlayer.open && ActivePlayer.state == 2) {
        if (ActivePlayer.dvdError || ActivePlayer.videoError) {
            ActivePlayer.state = ActivePlayer.internalState = 5;
            return;
        }

        ActivePlayer.retraceCount++;
        if (ActivePlayer.retraceCount == 0) {
            if (ProperTimingForStart()) {
                if (ActivePlayer.audioExist) {
                    if (ActivePlayer.curVideoNumber - ActivePlayer.curAudioNumber <= 1) {
                        decodedTexture = (THPTextureSet*)PopDecodedTextureSet(0);

                        ActivePlayer.videoAhead--;
                        ActivePlayer.curVideoNumber++;

                    } else {
                        ActivePlayer.internalState = 2;
                    }
                } else {
                    decodedTexture = (THPTextureSet*)PopDecodedTextureSet(0);
                }

            } else {
                ActivePlayer.retraceCount = -1;
            }

        } else {
            if (ActivePlayer.retraceCount == 1) {
                ActivePlayer.internalState = 2;
            }

            if (ProperTimingForGettingNextFrame()) {
                if (ActivePlayer.audioExist) {
                    if (ActivePlayer.curVideoNumber - ActivePlayer.curAudioNumber <= 1) {
                        decodedTexture = (THPTextureSet*)PopDecodedTextureSet(0);
                        ActivePlayer.videoAhead--;
                        ActivePlayer.curVideoNumber++;
                    }
                } else {
                    decodedTexture = (THPTextureSet*)PopDecodedTextureSet(0);
                }
            }
        }

        if (decodedTexture && decodedTexture != (THPTextureSet*)0xFFFFFFFF) {
            if (ActivePlayer.dispTextureSet) {
                PushUsedTextureSet(ActivePlayer.dispTextureSet);
            }
            ActivePlayer.dispTextureSet = decodedTexture;
        }

        if ((ActivePlayer.playFlag & 1) == 0) {
            if (ActivePlayer.audioExist) {
                audioFrame = ActivePlayer.curAudioNumber + ActivePlayer.initReadFrame;
                if (audioFrame == ActivePlayer.header.numFrames && ActivePlayer.playAudioBuffer == NULL) {
                    ActivePlayer.internalState = 3;
                    ActivePlayer.state = 3;
                }
            } else {
                if (ActivePlayer.dispTextureSet != NULL) {
                    curFrame = ActivePlayer.dispTextureSet->frameNumber + ActivePlayer.initReadFrame;
                } else {
                    curFrame = ActivePlayer.initReadFrame - 1;
                }

                if (curFrame == ActivePlayer.header.numFrames - 1 && decodedTexture == NULL) {
                    ActivePlayer.internalState = 3;
                    ActivePlayer.state = 3;
                }
            }
        }
    }
}

static bool ProperTimingForStart(void) {
    if (ActivePlayer.videoInfo.videoType & 1) {
        if (VIGetNextField() == 0) {
            return true;
        }
    } else if (ActivePlayer.videoInfo.videoType & 2) {
        if (VIGetNextField() == 1) {
            return true;
        }
    } else {
        return true;
    }

    NO_INLINE();
    return false;
}

static bool ProperTimingForGettingNextFrame(void) {
    s32 frameRate;

    if (ActivePlayer.videoInfo.videoType & 1) {
        if (VIGetNextField() == 0) {
            return true;
        }
    } else if (ActivePlayer.videoInfo.videoType & 2) {
        if (VIGetNextField() == 1) {
            return true;
        }
    } else {
        frameRate = ActivePlayer.header.frameRate * 100.0f;
        if (VIGetTvFormat() == VI_PAL) {
            ActivePlayer.curCount = ActivePlayer.retraceCount * frameRate / 5000;
        } else {
            ActivePlayer.curCount = ActivePlayer.retraceCount * frameRate / 5994;
        }

        if (ActivePlayer.prevCount != ActivePlayer.curCount) {
            ActivePlayer.prevCount = ActivePlayer.curCount;
            return true;
        }
    }

    return false;
}

s32 THPPlayerDrawCurrentFrame(GXRenderModeObj* obj, u32 x, u32 y, u32 polyWidth, u32 polyHeight) {
    if (ActivePlayer.open && ActivePlayer.state != 0 && ActivePlayer.dispTextureSet) {
        THPGXYuv2RgbSetup(obj);
        THPGXYuv2RgbDraw(ActivePlayer.dispTextureSet->yTexture, ActivePlayer.dispTextureSet->uTexture,
                         ActivePlayer.dispTextureSet->vTexture, x, y, ActivePlayer.videoInfo.xSize,
                         ActivePlayer.videoInfo.ySize, polyWidth, polyHeight);
        THPGXRestore();
        return (ActivePlayer.dispTextureSet->frameNumber + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
    }
    return -1;
}

static void PushUsedTextureSet(OSMessage msg) {
    OSSendMessage(&UsedTextureSetQueue, msg, OS_MESSAGE_NOBLOCK);
    NO_INLINE();
}

static inline OSMessage PopUsedTextureSet(void) {
    OSMessage msg;
    if (OSReceiveMessage(&UsedTextureSetQueue, &msg, OS_MESSAGE_NOBLOCK) == true) {
        return msg;
    }

    return NULL;
}

void THPPlayerDrawDone(void) {
    if (Initialized) {
        while (true) {
            OSMessage msg = PopUsedTextureSet();
            if (msg) {
                PushFreeTextureSet((OSMessage*)msg);
            } else {
                break;
            }
        }
    }
}

static void THPAudioMixCallback(void) {
    bool old;

    if (AudioSystem == 0) {
        SoundBufferIndex ^= 1;
        AIInitDMA((u32)&SoundBuffer[SoundBufferIndex], 0x280);
        old = OSEnableInterrupts();
        MixAudio(SoundBuffer[SoundBufferIndex], NULL, 0xA0);
        DCFlushRange(SoundBuffer[SoundBufferIndex], 0x280);
        OSRestoreInterrupts(old);
        return;
    }

    if (AudioSystem == true) {
        if (LastAudioBuffer != NULL) {
            CurAudioBuffer = LastAudioBuffer;
        }
        OldAIDCallback();
        LastAudioBuffer = (s16*)(AIGetDMAStartAddr() + 0x80000000);
    } else {
        OldAIDCallback();
        CurAudioBuffer = (s16*)(AIGetDMAStartAddr() + 0x80000000);
    }

    SoundBufferIndex ^= 1;
    AIInitDMA((u32)&SoundBuffer[SoundBufferIndex], 0x280);
    old = OSEnableInterrupts();

    if (CurAudioBuffer != NULL) {
        DCInvalidateRange(CurAudioBuffer, 0x280);
    }

    MixAudio(SoundBuffer[SoundBufferIndex], CurAudioBuffer, 0xA0U);
    DCFlushRange(SoundBuffer[SoundBufferIndex], 0x280);
    OSRestoreInterrupts(old);
}

static void MixAudio(s16* destination, s16* source, u32 sample) {
    u32 sampleNum;
    u32 requestSample;
    u32 i;
    s32 mix;
    s16* dst;
    s16* libsrc;
    s16* thpsrc;
    u16 attenuation;

    if (source != NULL) {
        if (ActivePlayer.open && ActivePlayer.internalState == 2 && ActivePlayer.audioExist) {
            requestSample = sample;
            dst = destination;
            libsrc = source;

            while (true) {
                if (ActivePlayer.playAudioBuffer == NULL) {
                    if ((ActivePlayer.playAudioBuffer = (THPAudioBuffer*)PopDecodedAudioBuffer(0)) == NULL) {
                        memcpy(dst, libsrc, requestSample << 2);
                        break;
                    } else {
                        ActivePlayer.curAudioNumber++;
                    }
                }

                if (ActivePlayer.playAudioBuffer->validSample) {
                    if (ActivePlayer.playAudioBuffer->validSample >= requestSample) {
                        sampleNum = requestSample;
                    } else {
                        sampleNum = ActivePlayer.playAudioBuffer->validSample;
                    }

                    thpsrc = ActivePlayer.playAudioBuffer->curPtr;

                    for (i = 0; i < sampleNum; i++) {
                        if (ActivePlayer.rampCount) {
                            ActivePlayer.rampCount--;
                            ActivePlayer.curVolume += ActivePlayer.deltaVolume;
                        } else {
                            ActivePlayer.curVolume = ActivePlayer.targetVolume;
                        }

                        attenuation = VolumeTable[(s32)ActivePlayer.curVolume];
                        mix = *libsrc + ((attenuation * (*thpsrc)) >> 15);

                        if (mix < -32768) {
                            mix = -32768;
                        }
                        if (mix > 32767) {
                            mix = 32767;
                        }

                        *dst = (s16)mix;
                        dst++;
                        libsrc++;
                        thpsrc++;
                        mix = *libsrc + ((attenuation * (*thpsrc)) >> 15);

                        if (mix < -32768) {
                            mix = -32768;
                        }
                        if (mix > 32767) {
                            mix = 32767;
                        }

                        *dst = (s16)mix;
                        dst++;
                        libsrc++;
                        thpsrc++;
                    }

                    requestSample -= sampleNum;
                    ActivePlayer.playAudioBuffer->validSample -= sampleNum;
                    ActivePlayer.playAudioBuffer->curPtr = thpsrc;
                    if (ActivePlayer.playAudioBuffer->validSample == 0) {
                        PushFreeAudioBuffer(ActivePlayer.playAudioBuffer);
                        ActivePlayer.playAudioBuffer = NULL;
                    }
                    if (!requestSample) {
                        break;
                    }
                }
            }
        } else {
            memcpy(destination, source, sample << 2);
        }
    } else {
        if (ActivePlayer.open && ActivePlayer.internalState == 2 && ActivePlayer.audioExist) {
            requestSample = sample;
            dst = destination;

            while (true) {
                if (ActivePlayer.playAudioBuffer == NULL) {
                    if ((ActivePlayer.playAudioBuffer = (THPAudioBuffer*)PopDecodedAudioBuffer(0)) == NULL) {
                        memset(dst, 0, requestSample * 4);
                        break;
                    } else {
                        ActivePlayer.curAudioNumber++;
                    }
                }

                if (ActivePlayer.playAudioBuffer->validSample) {
                    if (ActivePlayer.playAudioBuffer->validSample >= requestSample) {
                        sampleNum = requestSample;
                    } else {
                        sampleNum = ActivePlayer.playAudioBuffer->validSample;
                    }

                    thpsrc = ActivePlayer.playAudioBuffer->curPtr;
                    for (i = 0; i < sampleNum; i++) {
                        if (ActivePlayer.rampCount != 0) {
                            ActivePlayer.rampCount--;
                            ActivePlayer.curVolume += ActivePlayer.deltaVolume;
                        } else {
                            ActivePlayer.curVolume = ActivePlayer.targetVolume;
                        }

                        attenuation = VolumeTable[(s32)ActivePlayer.curVolume];
                        mix = (attenuation * (*thpsrc)) >> 15;
                        if (mix < -32768) {
                            mix = -32768;
                        }
                        if (mix > 32767) {
                            mix = 32767;
                        }

                        *dst = mix;
                        dst++;
                        thpsrc++;
                        mix = (attenuation * (*thpsrc)) >> 15;

                        if (mix < -32768) {
                            mix = -32768;
                        }
                        if (mix > 32767) {
                            mix = 32767;
                        }
                        *dst = mix;
                        dst++;
                        thpsrc++;
                    }

                    requestSample -= sampleNum;
                    ActivePlayer.playAudioBuffer->validSample -= sampleNum;
                    ActivePlayer.playAudioBuffer->curPtr = thpsrc;

                    if ((ActivePlayer.playAudioBuffer)->validSample == 0) {
                        PushFreeAudioBuffer(ActivePlayer.playAudioBuffer);
                        ActivePlayer.playAudioBuffer = NULL;
                    }

                    if (!requestSample) {
                        break;
                    }
                }
            }
        } else {
            memset(destination, 0, sample << 2);
        }
    }
}
