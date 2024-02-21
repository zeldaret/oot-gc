/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\THPAudioDecode.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80010D9C -> 0x80011138
*/

#include "dolphin/types.h"

// size = 0x4, address = 0x80135638
static s32 AudioDecodeThreadCreated;

typedef struct OSContext {
    /* 0x000 */ u32 gpr[32];
    /* 0x080 */ u32 cr;
    /* 0x084 */ u32 lr;
    /* 0x088 */ u32 ctr;
    /* 0x08C */ u32 xer;
    /* 0x090 */ f64 fpr[32];
    /* 0x190 */ u32 fpscr_pad;
    /* 0x194 */ u32 fpscr;
    /* 0x198 */ u32 srr0;
    /* 0x19C */ u32 srr1;
    /* 0x1A0 */ u16 mode;
    /* 0x1A2 */ u16 state;
    /* 0x1A4 */ u32 gqr[8];
    /* 0x1C4 */ u32 psf_pad;
    /* 0x1C8 */ f64 psf[32];
} __anon_0x125F9; // size = 0x2C8

typedef struct OSThreadQueue {
    /* 0x0 */ struct OSThread* head;
    /* 0x4 */ struct OSThread* tail;
} __anon_0x12812; // size = 0x8

typedef struct OSThreadLink {
    /* 0x0 */ struct OSThread* next;
    /* 0x4 */ struct OSThread* prev;
} __anon_0x12884; // size = 0x8

typedef struct OSMutexLink {
    /* 0x0 */ struct OSMutex* next;
    /* 0x4 */ struct OSMutex* prev;
} __anon_0x128F5; // size = 0x8

typedef struct OSMutex {
    /* 0x00 */ struct OSThreadQueue queue;
    /* 0x08 */ struct OSThread* thread;
    /* 0x0C */ s32 count;
    /* 0x10 */ struct OSMutexLink link;
} __anon_0x12965; // size = 0x18

typedef struct OSMutexQueue {
    /* 0x0 */ struct OSMutex* head;
    /* 0x4 */ struct OSMutex* tail;
} __anon_0x12A16; // size = 0x8

typedef struct OSThread {
    /* 0x000 */ struct OSContext context;
    /* 0x2C8 */ u16 state;
    /* 0x2CA */ u16 attr;
    /* 0x2CC */ s32 suspend;
    /* 0x2D0 */ s32 priority;
    /* 0x2D4 */ s32 base;
    /* 0x2D8 */ void* val;
    /* 0x2DC */ struct OSThreadQueue* queue;
    /* 0x2E0 */ struct OSThreadLink link;
    /* 0x2E8 */ struct OSThreadQueue queueJoin;
    /* 0x2F0 */ struct OSMutex* mutex;
    /* 0x2F4 */ struct OSMutexQueue queueMutex;
    /* 0x2FC */ struct OSThreadLink linkActive;
    /* 0x304 */ u8* stackBase;
    /* 0x308 */ u32* stackEnd;
    /* 0x30C */ s32 error;
    /* 0x310 */ void* specific[2];
} __anon_0x12AA7; // size = 0x318

// size = 0x318, address = 0x800F9E50
static struct OSThread AudioDecodeThread;

// size = 0x1000, address = 0x800FA168
static u8 AudioDecodeThreadStack[4096];

typedef struct OSMessageQueue {
    /* 0x00 */ struct OSThreadQueue queueSend;
    /* 0x08 */ struct OSThreadQueue queueReceive;
    /* 0x10 */ void* msgArray;
    /* 0x14 */ s32 msgCount;
    /* 0x18 */ s32 firstIndex;
    /* 0x1C */ s32 usedCount;
} __anon_0x12DC3; // size = 0x20

// size = 0x20, address = 0x800FB168
static struct OSMessageQueue FreeAudioBufferQueue;

// size = 0x20, address = 0x800FB188
static struct OSMessageQueue DecodedAudioBufferQueue;

// size = 0xC, address = 0x800FB1A8
static void* FreeAudioBufferMessage[3];

// size = 0xC, address = 0x800FB1B4
static void* DecodedAudioBufferMessage[3];

typedef struct DVDDiskID {
    /* 0x0 */ char gameName[4];
    /* 0x4 */ char company[2];
    /* 0x6 */ u8 diskNumber;
    /* 0x7 */ u8 gameVersion;
    /* 0x8 */ u8 streaming;
    /* 0x9 */ u8 streamingBufSize;
    /* 0xA */ u8 padding[22];
} __anon_0x131C5; // size = 0x20

typedef struct DVDCommandBlock {
    /* 0x00 */ struct DVDCommandBlock* next;
    /* 0x04 */ struct DVDCommandBlock* prev;
    /* 0x08 */ u32 command;
    /* 0x0C */ s32 state;
    /* 0x10 */ u32 offset;
    /* 0x14 */ u32 length;
    /* 0x18 */ void* addr;
    /* 0x1C */ u32 currTransferSize;
    /* 0x20 */ u32 transferredSize;
    /* 0x24 */ struct DVDDiskID* id;
    /* 0x28 */ void (*callback)(s32, struct DVDCommandBlock*);
    /* 0x2C */ void* userData;
} __anon_0x13335; // size = 0x30

typedef struct DVDFileInfo {
    /* 0x00 */ struct DVDCommandBlock cb;
    /* 0x30 */ u32 startAddr;
    /* 0x34 */ u32 length;
    /* 0x38 */ void (*callback)(s32, struct DVDFileInfo*);
} __anon_0x1355B; // size = 0x3C

typedef struct __anon_0x13633 {
    /* 0x00 */ char magic[4];
    /* 0x04 */ u32 version;
    /* 0x08 */ u32 bufSize;
    /* 0x0C */ u32 audioMaxSamples;
    /* 0x10 */ f32 frameRate;
    /* 0x14 */ u32 numFrames;
    /* 0x18 */ u32 firstFrameSize;
    /* 0x1C */ u32 movieDataSize;
    /* 0x20 */ u32 compInfoDataOffsets;
    /* 0x24 */ u32 offsetDataOffsets;
    /* 0x28 */ u32 movieDataOffsets;
    /* 0x2C */ u32 finalFrameDataOffsets;
} __anon_0x13633; // size = 0x30

typedef struct __anon_0x1385F {
    /* 0x0 */ u32 numComponents;
    /* 0x4 */ u8 frameComp[16];
} __anon_0x1385F; // size = 0x14

typedef struct __anon_0x138C7 {
    /* 0x0 */ u32 xSize;
    /* 0x4 */ u32 ySize;
    /* 0x8 */ u32 videoType;
} __anon_0x138C7; // size = 0xC

typedef struct __anon_0x13947 {
    /* 0x0 */ u32 sndChannels;
    /* 0x4 */ u32 sndFrequency;
    /* 0x8 */ u32 sndNumSamples;
    /* 0xC */ u32 sndNumTracks;
} __anon_0x13947; // size = 0x10

typedef struct __anon_0x13A01 {
    /* 0x0 */ u8* ytexture;
    /* 0x4 */ u8* utexture;
    /* 0x8 */ u8* vtexture;
    /* 0xC */ s32 frameNumber;
} __anon_0x13A01; // size = 0x10

typedef struct __anon_0x13AB7 {
    /* 0x0 */ s16* buffer;
    /* 0x4 */ s16* curPtr;
    /* 0x8 */ u32 validSample;
} __anon_0x13AB7; // size = 0xC

typedef struct __anon_0x13BA7 {
    /* 0x000 */ struct DVDFileInfo fileInfo;
    /* 0x03C */ struct __anon_0x13633 header;
    /* 0x06C */ struct __anon_0x1385F compInfo;
    /* 0x080 */ struct __anon_0x138C7 videoInfo;
    /* 0x08C */ struct __anon_0x13947 audioInfo;
    /* 0x09C */ void* thpWork;
    /* 0x0A0 */ s32 open;
    /* 0x0A4 */ u8 state;
    /* 0x0A5 */ u8 internalState;
    /* 0x0A6 */ u8 playFlag;
    /* 0x0A7 */ u8 audioExist;
    /* 0x0A8 */ s32 dvdError;
    /* 0x0AC */ s32 videoError;
    /* 0x0B0 */ s32 onMemory;
    /* 0x0B4 */ u8* movieData;
    /* 0x0B8 */ s32 initOffset;
    /* 0x0BC */ s32 initReadSize;
    /* 0x0C0 */ s32 initReadFrame;
    /* 0x0C8 */ s64 retraceCount;
    /* 0x0D0 */ s32 prevCount;
    /* 0x0D4 */ s32 curCount;
    /* 0x0D8 */ s32 videoAhead;
    /* 0x0DC */ f32 curVolume;
    /* 0x0E0 */ f32 targetVolume;
    /* 0x0E4 */ f32 deltaVolume;
    /* 0x0E8 */ s32 rampCount;
    /* 0x0EC */ s32 curAudioTrack;
    /* 0x0F0 */ s32 curVideoNumber;
    /* 0x0F4 */ s32 curAudioNumber;
    /* 0x0F8 */ struct __anon_0x13A01* dispTextureSet;
    /* 0x0FC */ struct __anon_0x13AB7* playAudioBuffer;
    /* 0x100 */ struct __anon_0x14130 readBuffer[10];
    /* 0x178 */ struct __anon_0x13A01 textureSet[3];
    /* 0x1A8 */ struct __anon_0x13AB7 audioBuffer[3];
} __anon_0x13BA7; // size = 0x1D0

// size = 0x1D0, address = 0x800F9C80
struct __anon_0x13BA7 ActivePlayer;

typedef struct __anon_0x14130 {
    /* 0x0 */ u8* ptr;
    /* 0x4 */ s32 frameNumber;
    /* 0x8 */ s32 isValid;
} __anon_0x14130; // size = 0xC

// Range: 0x80011108 -> 0x80011138
void PushDecodedAudioBuffer(void* buffer) {
    // Parameters
    // void* buffer; // r4

    // References
    // -> static struct OSMessageQueue DecodedAudioBufferQueue;
}

// Range: 0x800110C4 -> 0x80011108
void* PopDecodedAudioBuffer(s32 flag) {
    // Parameters
    // s32 flag; // r5

    // Local variables
    void* msg; // r1+0xC

    // References
    // -> static struct OSMessageQueue DecodedAudioBufferQueue;
}

// Range: 0x80011094 -> 0x800110C4
void PushFreeAudioBuffer(void* buffer) {
    // Parameters
    // void* buffer; // r4

    // References
    // -> static struct OSMessageQueue FreeAudioBufferQueue;
}

// Range: 0x80011060 -> 0x80011094
void* PopFreeAudioBuffer() {
    // Local variables
    void* msg; // r1+0x8

    // References
    // -> static struct OSMessageQueue FreeAudioBufferQueue;
}

// Range: 0x80010F88 -> 0x80011060
static void AudioDecode(struct __anon_0x14130* readBuffer) {
    // Parameters
    // struct __anon_0x14130* readBuffer; // r1+0x8

    // Local variables
    struct __anon_0x13AB7* audioBuffer; // r30
    u32 i; // r1+0x8
    u32 sample; // r1+0x8
    u32* compSizePtr; // r29
    u8* ptr; // r28

    // References
    // -> struct __anon_0x13BA7 ActivePlayer;
}

// Range: 0x80010ED8 -> 0x80010F88
static void* AudioDecoderForOnMemory(void* ptr) {
    // Parameters
    // void* ptr; // r1+0x8

    // Local variables
    struct __anon_0x14130 readBuffer; // r1+0x10
    s32 tmp; // r4
    s32 size; // r28
    s32 readFrame; // r31

    // References
    // -> static struct OSThread AudioDecodeThread;
    // -> struct __anon_0x13BA7 ActivePlayer;
}

// Range: 0x80010EB0 -> 0x80010ED8
static void* AudioDecoder() {
    // Local variables
    struct __anon_0x14130* readBuffer; // r31
}

// Erased
static void AudioDecodeThreadCancel() {
    // References
    // -> static s32 AudioDecodeThreadCreated;
    // -> static struct OSThread AudioDecodeThread;
}

// Range: 0x80010E7C -> 0x80010EB0
void AudioDecodeThreadStart() {
    // References
    // -> static struct OSThread AudioDecodeThread;
    // -> static s32 AudioDecodeThreadCreated;
}

// Range: 0x80010D9C -> 0x80010E7C
s32 CreateAudioDecodeThread(s32 priority, u8* ptr) {
    // Parameters
    // s32 priority; // r8
    // u8* ptr; // r5

    // References
    // -> static s32 AudioDecodeThreadCreated;
    // -> static void* DecodedAudioBufferMessage[3];
    // -> static struct OSMessageQueue DecodedAudioBufferQueue;
    // -> static void* FreeAudioBufferMessage[3];
    // -> static struct OSMessageQueue FreeAudioBufferQueue;
    // -> static u8 AudioDecodeThreadStack[4096];
    // -> static struct OSThread AudioDecodeThread;
}
