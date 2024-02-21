/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\mcardGCN.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80013440 -> 0x8001C444
*/

#include "dolphin/types.h"

// size = 0xA000, address = 0x800FD960
static char gMCardCardWorkArea[40960];

// size = 0x4, address = 0x80135660
s32 currentIdx;

// size = 0x4, address = 0x80135664
static s32 yes$771;

typedef enum __anon_0x1A5F0 {
    MC_M_NONE = 0,
    MC_M_LD01 = 1,
    MC_M_LD02 = 2,
    MC_M_LD03 = 3,
    MC_M_LD04 = 4,
    MC_M_LD05 = 5,
    MC_M_LD05_2 = 6,
    MC_M_LD06 = 7,
    MC_M_LD06_2 = 8,
    MC_M_LD06_3 = 9,
    MC_M_LD06_4 = 10,
    MC_M_LD07 = 11,
    MC_M_SV01 = 12,
    MC_M_SV01_2 = 13,
    MC_M_SV02 = 14,
    MC_M_SV03 = 15,
    MC_M_SV04 = 16,
    MC_M_SV05 = 17,
    MC_M_SV05_2 = 18,
    MC_M_SV06 = 19,
    MC_M_SV06_2 = 20,
    MC_M_SV06_3 = 21,
    MC_M_SV06_4 = 22,
    MC_M_SV06_5 = 23,
    MC_M_SV07 = 24,
    MC_M_SV08_L = 25,
    MC_M_SV08_L_2 = 26,
    MC_M_SV08 = 27,
    MC_M_SV08_2 = 28,
    MC_M_SV10 = 29,
    MC_M_SV11 = 30,
    MC_M_SV12 = 31,
    MC_M_SV_SHARE = 32,
    MC_M_IN01_L = 33,
    MC_M_IN01_S = 34,
    MC_M_IN02 = 35,
    MC_M_IN03 = 36,
    MC_M_IN04_L = 37,
    MC_M_IN04_S = 38,
    MC_M_IN05 = 39,
    MC_M_GF01_L = 40,
    MC_M_GF01_L_2 = 41,
    MC_M_GF01_S = 42,
    MC_M_GF01_S_2 = 43,
    MC_M_GF02 = 44,
    MC_M_GF03 = 45,
    MC_M_GF04_L = 46,
    MC_M_GF04_S = 47,
    MC_M_GF05 = 48,
    MC_M_GF06 = 49,
} __anon_0x1A5F0;

// size = 0x4, address = 0x80135668
static enum __anon_0x1A5F0 prevMenuEntry$772;

// size = 0x4, address = 0x8013566C
static enum __anon_0x1A5F0 nextMenuEntry$773;

// size = 0x4, address = 0x80135670
static s32 toggle2$1029;

// size = 0x4, address = 0x80134DB8
static s32 toggle$1034;

// size = 0x4, address = 0x80135674
static s32 checkFailCount$1490;

typedef struct OSCalendarTime {
    /* 0x00 */ s32 sec;
    /* 0x04 */ s32 min;
    /* 0x08 */ s32 hour;
    /* 0x0C */ s32 mday;
    /* 0x10 */ s32 mon;
    /* 0x14 */ s32 year;
    /* 0x18 */ s32 wday;
    /* 0x1C */ s32 yday;
    /* 0x20 */ s32 msec;
    /* 0x24 */ s32 usec;
} __anon_0x1A9EE; // size = 0x28

// size = 0x28, address = 0x80107960
struct OSCalendarTime gDate;

// size = 0x4, address = 0x80135678
s32 bWrite2Card;

// size = 0x28, address = 0x80107988
s32 bNoWriteInCurrentFrame[10];

typedef struct __anon_0x1AC1A {
    /* 0x00 */ s32 configuration;
    /* 0x04 */ s32 size;
    /* 0x08 */ s32 offset;
    /* 0x0C */ char* buffer;
    /* 0x10 */ s32* writtenBlocks;
    /* 0x14 */ s32 writtenConfig;
} __anon_0x1AC1A; // size = 0x18

typedef struct CARDFileInfo {
    /* 0x00 */ s32 chan;
    /* 0x04 */ s32 fileNo;
    /* 0x08 */ s32 offset;
    /* 0x0C */ s32 length;
    /* 0x10 */ u16 iBlock;
    /* 0x12 */ u16 __padding;
} __anon_0x1ADBD; // size = 0x14

typedef struct __anon_0x1AEB5 {
    /* 0x000 */ s32 currentGame;
    /* 0x004 */ s32 fileSize;
    /* 0x008 */ char name[33];
    /* 0x02C */ s32 numberOfGames;
    /* 0x030 */ struct __anon_0x1AC1A game;
    /* 0x048 */ s32 changedDate;
    /* 0x04C */ s32 changedChecksum;
    /* 0x050 */ s32 gameSize[16];
    /* 0x090 */ s32 gameOffset[16];
    /* 0x0D0 */ s32 gameConfigIndex[16];
    /* 0x110 */ char gameName[16][33];
    /* 0x320 */ struct OSCalendarTime time;
    /* 0x348 */ struct CARDFileInfo fileInfo;
} __anon_0x1AEB5; // size = 0x35C

typedef enum __anon_0x1B0CB {
    MC_E_NONE = 0,
    MC_E_BUSY = 1,
    MC_E_WRONGDEVICE = 2,
    MC_E_NOCARD = 3,
    MC_E_NOFILE = 4,
    MC_E_IOERROR = 5,
    MC_E_BROKEN = 6,
    MC_E_EXIST = 7,
    MC_E_NOENT = 8,
    MC_E_INSSPACE = 9,
    MC_E_NOPERM = 10,
    MC_E_LIMIT = 11,
    MC_E_NAMETOOLONG = 12,
    MC_E_ENCODING = 13,
    MC_E_CANCELED = 14,
    MC_E_FATAL = 15,
    MC_E_SECTOR_SIZE_INVALID = 16,
    MC_E_GAME_NOT_FOUND = 17,
    MC_E_CHECKSUM = 18,
    MC_E_NO_FREE_SPACE = 19,
    MC_E_NO_FREE_FILES = 20,
    MC_E_FILE_EXISTS = 21,
    MC_E_GAME_EXISTS = 22,
    MC_E_TIME_WRONG = 23,
    MC_E_WRITE_CORRUPTED = 24,
    MC_E_UNKNOWN = 25,
} __anon_0x1B0CB;

typedef struct _MCARD {
    /* 0x000 */ struct __anon_0x1AEB5 file;
    /* 0x35C */ enum __anon_0x1B0CB error;
    /* 0x360 */ s32 slot;
    /* 0x364 */ s32 (*pPollFunction)();
    /* 0x368 */ s32 pollPrevBytes;
    /* 0x36C */ s32 pollSize;
    /* 0x370 */ char pollMessage[256];
    /* 0x470 */ s32 saveToggle;
    /* 0x474 */ char* writeBuffer;
    /* 0x478 */ char* readBuffer;
    /* 0x47C */ s32 writeToggle;
    /* 0x480 */ s32 soundToggle;
    /* 0x484 */ s32 writeStatus;
    /* 0x488 */ s32 writeIndex;
    /* 0x48C */ s32 accessType;
    /* 0x490 */ s32 gameIsLoaded;
    /* 0x494 */ char saveFileName[256];
    /* 0x594 */ char saveComment[256];
    /* 0x694 */ char* saveIcon;
    /* 0x698 */ char* saveBanner;
    /* 0x69C */ char saveGameName[256];
    /* 0x79C */ s32 saveFileSize;
    /* 0x7A0 */ s32 saveGameSize;
    /* 0x7A4 */ s32 bufferCreated;
    /* 0x7A8 */ s32 cardSize;
    /* 0x7AC */ s32 wait;
    /* 0x7B0 */ s32 isBroken;
    /* 0x7B4 */ s32 saveConfiguration;
} __anon_0x1B36F; // size = 0x7B8

// size = 0x7B8, address = 0x801079B0
struct _MCARD mCard;

typedef enum __anon_0x1B813 {
    SM_NONE = -1,
    SM_RUNNING = 0,
    SM_STOPPED = 1,
} __anon_0x1B813;

typedef struct __anon_0x1B87B {
    /* 0x0 */ s32 nSize;
    /* 0x4 */ s32 nOffsetRAM;
    /* 0x8 */ s32 nOffsetROM;
    /* 0xC */ s32 (*pCallback)();
} __anon_0x1B87B; // size = 0x10

typedef enum __anon_0x1B92C {
    SRT_NONE = -1,
    SRT_MARIO = 0,
    SRT_WAVERACE = 1,
    SRT_MARIOKART = 2,
    SRT_STARFOX = 3,
    SRT_ZELDA1 = 4,
    SRT_ZELDA2 = 5,
    SRT_1080 = 6,
    SRT_PANEL = 7,
    SRT_MARIOPARTY1 = 8,
    SRT_MARIOPARTY2 = 9,
    SRT_MARIOPARTY3 = 10,
    SRT_DRMARIO = 11,
    SRT_UNKNOWN = 12,
} __anon_0x1B92C;

typedef enum __anon_0x1BA5D {
    SOT_NONE = -1,
    SOT_CPU = 0,
    SOT_PIF = 1,
    SOT_RAM = 2,
    SOT_ROM = 3,
    SOT_RSP = 4,
    SOT_RDP = 5,
    SOT_MIPS = 6,
    SOT_DISK = 7,
    SOT_FLASH = 8,
    SOT_SRAM = 9,
    SOT_AUDIO = 10,
    SOT_VIDEO = 11,
    SOT_SERIAL = 12,
    SOT_LIBRARY = 13,
    SOT_PERIPHERAL = 14,
    SOT_RDB = 15,
    SOT_COUNT = 16,
} __anon_0x1BA5D;

typedef struct __anon_0x1BB9D {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ s32 bException;
    /* 0x0C */ enum __anon_0x1B813 eMode;
    /* 0x10 */ struct __anon_0x1B87B romCopy;
    /* 0x20 */ enum __anon_0x1B92C eTypeROM;
    /* 0x24 */ void* apObject[16];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ enum __anon_0x1BA5D storageDevice;
    /* 0x74 */ u8 anException[16];
    /* 0x84 */ s32 bJapaneseVersion;
} __anon_0x1BB9D; // size = 0x88

// size = 0x4, address = 0x80135600
struct __anon_0x1BB9D* gpSystem;

typedef enum __anon_0x1BD8E {
    MC_C_NONE = 0,
    MC_C_CONTINUE = 1,
    MC_C_IPL = 2,
    MC_C_GO_TO_GAME = 3,
    MC_C_CREATE_GAME = 4,
    MC_C_DELETE_GAME = 5,
    MC_C_FORMAT_CARD = 6,
} __anon_0x1BD8E;

// size = 0x4, address = 0x801355D4
s32 gButtonDownToggle;

typedef struct _GXTexObj {
    /* 0x0 */ u32 dummy[8];
} __anon_0x1CD33; // size = 0x20

typedef struct CARDStat {
    /* 0x00 */ char fileName[32];
    /* 0x20 */ u32 length;
    /* 0x24 */ u32 time;
    /* 0x28 */ u8 gameName[4];
    /* 0x2C */ u8 company[2];
    /* 0x2E */ u8 bannerFormat;
    /* 0x2F */ u8 __padding;
    /* 0x30 */ u32 iconAddr;
    /* 0x34 */ u16 iconFormat;
    /* 0x36 */ u16 iconSpeed;
    /* 0x38 */ u32 commentAddr;
    /* 0x3C */ u32 offsetBanner;
    /* 0x40 */ u32 offsetBannerTlut;
    /* 0x44 */ u32 offsetIcon[8];
    /* 0x64 */ u32 offsetIconTlut;
    /* 0x68 */ u32 offsetData;
} __anon_0x1CDF9; // size = 0x6C

typedef enum _GXTexWrapMode {
    GX_CLAMP = 0,
    GX_REPEAT = 1,
    GX_MIRROR = 2,
    GX_MAX_TEXWRAPMODE = 3,
} __anon_0x1F142;

typedef enum _GXTexFilter {
    GX_NEAR = 0,
    GX_LINEAR = 1,
    GX_NEAR_MIP_NEAR = 2,
    GX_LIN_MIP_NEAR = 3,
    GX_NEAR_MIP_LIN = 4,
    GX_LIN_MIP_LIN = 5,
} __anon_0x1F1AB;

typedef struct __anon_0x1F23C {
    /* 0x00 */ u16 height;
    /* 0x02 */ u16 width;
    /* 0x04 */ u32 format;
    /* 0x08 */ char* data;
    /* 0x0C */ enum _GXTexWrapMode wrapS;
    /* 0x10 */ enum _GXTexWrapMode wrapT;
    /* 0x14 */ enum _GXTexFilter minFilter;
    /* 0x18 */ enum _GXTexFilter magFilter;
    /* 0x1C */ f32 LODBias;
    /* 0x20 */ u8 edgeLODEnable;
    /* 0x21 */ u8 minLOD;
    /* 0x22 */ u8 maxLOD;
    /* 0x23 */ u8 unpacked;
} __anon_0x1F23C; // size = 0x24

typedef enum _GXTlutFmt {
    GX_TL_IA8 = 0,
    GX_TL_RGB565 = 1,
    GX_TL_RGB5A3 = 2,
    GX_MAX_TLUTFMT = 3,
} __anon_0x1F42F;

typedef struct __anon_0x1F497 {
    /* 0x0 */ u16 numEntries;
    /* 0x2 */ u8 unpacked;
    /* 0x3 */ u8 pad8;
    /* 0x4 */ enum _GXTlutFmt format;
    /* 0x8 */ char* data;
} __anon_0x1F497; // size = 0xC

typedef struct __anon_0x1F563 {
    /* 0x0 */ struct __anon_0x1F23C* textureHeader;
    /* 0x4 */ struct __anon_0x1F497* CLUTHeader;
} __anon_0x1F563; // size = 0x8

typedef struct __anon_0x1F5D4 {
    /* 0x0 */ u32 versionNumber;
    /* 0x4 */ u32 numDescriptors;
    /* 0x8 */ struct __anon_0x1F563* descriptorArray;
} __anon_0x1F5D4; // size = 0xC

// Erased
static void mcardUnpackTexPalette(struct __anon_0x1F5D4* pal) {
    // Parameters
    // struct __anon_0x1F5D4* pal; // r1+0x0

    // Local variables
    u16 i; // r4
}

// Range: 0x8001C2A0 -> 0x8001C444
static s32 mcardGCErrorHandler(struct _MCARD* pMCard, s32 gcError) {
    // Parameters
    // struct _MCARD* pMCard; // r1+0x0
    // s32 gcError; // r1+0x4
}

// Range: 0x8001C240 -> 0x8001C2A0
static s32 mcardCalculateChecksum(struct _MCARD* pMCard, s32* checksum) {
    // Parameters
    // struct _MCARD* pMCard; // r1+0x0
    // s32* checksum; // r1+0x4

    // Local variables
    s32 i; // r1+0x0

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001C0D8 -> 0x8001C240
static s32 mcardCalculateChecksumFileBlock1(struct _MCARD* pMCard, s32* checksum) {
    // Parameters
    // struct _MCARD* pMCard; // r1+0x0
    // s32* checksum; // r1+0x4

    // Local variables
    s32 i; // r8

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001BF70 -> 0x8001C0D8
static s32 mcardCalculateChecksumFileBlock2(struct _MCARD* pMCard, s32* checksum) {
    // Parameters
    // struct _MCARD* pMCard; // r1+0x0
    // s32* checksum; // r1+0x4

    // Local variables
    s32 i; // r8

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001BC14 -> 0x8001BF70
static s32 mcardSaveChecksumFileHeader(struct _MCARD* pMCard, char* buffer) {
    // Parameters
    // struct _MCARD* pMCard; // r30
    // char* buffer; // r31

    // Local variables
    char buffer2[8192]; // r1+0x1C
    s32 checksum; // r1+0x18

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardGetFileTime(struct _MCARD* pMCard, struct OSCalendarTime* time) {
    // Parameters
    // struct _MCARD* pMCard; // r29
    // struct OSCalendarTime* time; // r30

    // Local variables
    char buffer[544]; // r1+0x10
}

// Range: 0x8001B794 -> 0x8001BC14
static s32 mcardReplaceFileBlock(struct _MCARD* pMCard, s32 index) {
    // Parameters
    // struct _MCARD* pMCard; // r28
    // s32 index; // r29

    // Local variables
    s32 checksum1; // r1+0x2238
    s32 checksum2; // r30
    char buffer[8192]; // r1+0x238

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001B480 -> 0x8001B794
static s32 mcardCheckChecksumFileHeader(struct _MCARD* pMCard, char* buffer) {
    // Parameters
    // struct _MCARD* pMCard; // r29
    // char* buffer; // r27

    // Local variables
    s32 checksum; // r31
    char buffer2[8192]; // r1+0x18
    s32 toggle; // r30

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001B254 -> 0x8001B480
static s32 mcardVerifyChecksumFileHeader(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30

    // Local variables
    char* buffer; // r1+0xC

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardCompareName(char* name1, char* name2) {
    // Parameters
    // char* name1; // r4
    // char* name2; // r5
}

// Erased
static s32 mcardCopyName(char* name1, char* name2) {
    // Parameters
    // char* name1; // r4
    // char* name2; // r5

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001B168 -> 0x8001B254
static s32 mcardPoll(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r31

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001AFD4 -> 0x8001B168
static s32 mcardReadyCard(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30

    // Local variables
    s32 i; // r31
    s32 sectorSize; // r1+0xC

    // References
    // -> static char gMCardCardWorkArea[40960];
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardFinishCard(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r3
}

// Erased
static s32 mcardReadyFile(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r31
}

// Erased
static s32 mcardFinishFile(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r31
}

// Erased
static s32 mcardReadAnywhereNoTime(struct _MCARD* pMCard, s32 offset, s32 size, char* buffer) {
    // Parameters
    // struct _MCARD* pMCard; // r29
    // s32 offset; // r3
    // s32 size; // r30
    // char* buffer; // r31

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardWriteAnywhereNoTime(struct _MCARD* pMCard, s32 offset, s32 size, char* buffer) {
    // Parameters
    // struct _MCARD* pMCard; // r28
    // s32 offset; // r29
    // s32 size; // r30
    // char* buffer; // r31

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardSetFileTime(struct _MCARD* pMCard, struct OSCalendarTime* time) {
    // Parameters
    // struct _MCARD* pMCard; // r30
    // struct OSCalendarTime* time; // r31

    // Local variables
    char buffer[24608]; // r1+0x10

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardTimeCheck(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30

    // Local variables
    struct OSCalendarTime time; // r1+0x22C
}

// Range: 0x8001AE64 -> 0x8001AFD4
static s32 mcardReadAnywhere(struct _MCARD* pMCard, s32 offset, s32 size, char* buffer) {
    // Parameters
    // struct _MCARD* pMCard; // r27
    // s32 offset; // r28
    // s32 size; // r29
    // char* buffer; // r30

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001ACC8 -> 0x8001AE64
static s32 mcardWriteAnywhere(struct _MCARD* pMCard, s32 offset, s32 size, char* buffer) {
    // Parameters
    // struct _MCARD* pMCard; // r31
    // s32 offset; // r27
    // s32 size; // r28
    // char* buffer; // r29

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001AB1C -> 0x8001ACC8
static s32 mcardWriteAnywherePartial(struct _MCARD* pMCard, s32 offset, s32 size, char* buffer, s32 partialOffset,
                                     s32 totalSize) {
    // Parameters
    // struct _MCARD* pMCard; // r31
    // s32 offset; // r25
    // s32 size; // r26
    // char* buffer; // r27
    // s32 partialOffset; // r28
    // s32 totalSize; // r29

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001A8F8 -> 0x8001AB1C
static s32 mcardReadFileHeader(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r31

    // Local variables
    char buffer[24608]; // r1+0x254

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001A53C -> 0x8001A8F8
static s32 mcardWriteFileHeader(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30

    // Local variables
    char buffer[24608]; // r1+0x49C

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001A3E4 -> 0x8001A53C
static s32 mcardReadFileHeaderInitial(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30

    // Local variables
    char buffer[24608]; // r1+0xC

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x8001A1C0 -> 0x8001A3E4
static s32 mcardWriteFileHeaderInitial(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r31

    // Local variables
    char buffer[24608]; // r1+0xC

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardReadCardHeader(struct _MCARD* pMCard, char* cardHeader) {
    // Parameters
    // struct _MCARD* pMCard; // r30
    // char* cardHeader; // r31

    // Local variables
    char buffer[24608]; // r1+0x258

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardWriteCardHeader(struct _MCARD* pMCard, char* cardHeader) {
    // Parameters
    // struct _MCARD* pMCard; // r29
    // char* cardHeader; // r30

    // Local variables
    char buffer[24608]; // r1+0x4A0

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x80019FDC -> 0x8001A1C0
static s32 mcardWriteBufferAsynch(struct _MCARD* pMCard, s32 offset) {
    // Parameters
    // struct _MCARD* pMCard; // r29
    // s32 offset; // r30

    // Local variables
    struct OSCalendarTime date; // r1+0x258

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x80019E38 -> 0x80019FDC
static s32 mcardReadBufferAsynch(struct _MCARD* pMCard, s32 offset) {
    // Parameters
    // struct _MCARD* pMCard; // r30
    // s32 offset; // r27

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardWriteConfigPrepareWriteBuffer(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r29

    // Local variables
    s32 checksum; // r1+0x4A0

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x80019C74 -> 0x80019E38
static s32 mcardWriteConfigAsynch(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardWriteTimePrepareWriteBuffer(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r29

    // Local variables
    char dateString[32]; // r1+0x4A4
    s32 checksum; // r1+0x4A0

    // References
    // -> struct OSCalendarTime gDate;
    // -> struct _MCARD mCard;
}

// Range: 0x80019A70 -> 0x80019C74
static s32 mcardWriteTimeAsynch(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30

    // References
    // -> struct OSCalendarTime gDate;
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardReplaceBlock(struct _MCARD* pMCard, s32 index) {
    // Parameters
    // struct _MCARD* pMCard; // r27
    // s32 index; // r28

    // Local variables
    s32 checksum1; // r1+0x4A4
    s32 checksum2; // r29

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x800196D8 -> 0x80019A70
s32 mcardReadGameData(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r23

    // Local variables
    s32 checksum1; // r1+0x260
    s32 checksum2; // r26
    s32 i; // r25
    s32 toggle; // r24

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardWriteGameData(struct _MCARD* pMCard, s32 offset) {
    // Parameters
    // struct _MCARD* pMCard; // r3
    // s32 offset; // r4
}

// Erased
static s32 mcardWriteGameDataWait(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r24

    // Local variables
    s32 checksum; // r1+0x258
    s32 i; // r25

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x80019670 -> 0x800196D8
s32 mcardWriteGameDataReset(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x800194D8 -> 0x80019670
s32 mcardReInit(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30
}

// Range: 0x8001947C -> 0x800194D8
s32 mcardInit(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r31
}

// Range: 0x80019058 -> 0x8001947C
s32 mcardFileSet(struct _MCARD* pMCard, char* name) {
    // Parameters
    // struct _MCARD* pMCard; // r30
    // char* name; // r4

    // Local variables
    s32 i; // r7

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardGameSetNoSave(struct _MCARD* pMCard, s32 size) {
    // Parameters
    // struct _MCARD* pMCard; // r30
    // s32 size; // r31

    // References
    // -> struct __anon_0x1BB9D* gpSystem;
}

// Range: 0x80018C50 -> 0x80019058
s32 mcardGameSet(struct _MCARD* pMCard, char* name) {
    // Parameters
    // struct _MCARD* pMCard; // r31
    // char* name; // r28

    // Local variables
    s32 i; // r29

    // References
    // -> struct __anon_0x1BB9D* gpSystem;
}

// Range: 0x800185F8 -> 0x80018C50
s32 mcardFileCreate(struct _MCARD* pMCard, char* name, char* comment, char* icon, char* banner, s32 size) {
    // Parameters
    // struct _MCARD* pMCard; // r31
    // char* name; // r21
    // char* comment; // r25
    // char* icon; // r27
    // char* banner; // r26
    // s32 size; // r1+0x1C

    // Local variables
    s32 freeBytes; // r1+0x104
    s32 freeFiles; // r1+0x100
    s32 totalSize; // r30
    s32 i; // r21
    char* buffer; // r1+0xFC
    struct _GXTexObj texObj; // r1+0xDC
    void* dataP; // r4
    struct CARDStat cardStatus; // r1+0x70
    s32 fileNo; // r21
    struct OSCalendarTime date; // r1+0x48
    char dateString[32]; // r1+0x28

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x80017D60 -> 0x800185F8
s32 mcardGameCreate(struct _MCARD* pMCard, char* name, s32 defaultConfiguration, s32 size) {
    // Parameters
    // struct _MCARD* pMCard; // r25
    // char* name; // r30
    // s32 defaultConfiguration; // r29
    // s32 size; // r27

    // Local variables
    s32 i; // r26

    // References
    // -> struct _MCARD mCard;
}

// Erased
static s32 mcardGameCreateDuringGame(struct _MCARD* pMCard, char* name, s32 size) {
    // Parameters
    // struct _MCARD* pMCard; // r25
    // char* name; // r29
    // s32 size; // r24

    // Local variables
    s32 i; // r26

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x80017C24 -> 0x80017D60
s32 mcardCardErase(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r29

    // Local variables
    s32 slot; // r30
}

// Range: 0x80017A94 -> 0x80017C24
s32 mcardFileErase(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30
}

// Range: 0x800178EC -> 0x80017A94
s32 mcardGameErase(struct _MCARD* pMCard, s32 index) {
    // Parameters
    // struct _MCARD* pMCard; // r31
    // s32 index; // r30
}

// Erased
static s32 mcardFileRelease(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r30
}

// Range: 0x80017844 -> 0x800178EC
s32 mcardGameRelease(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r31
}

// Range: 0x80017814 -> 0x80017844
s32 mcardRead(struct _MCARD* pMCard, s32 address, s32 size, char* data) {
    // Parameters
    // struct _MCARD* pMCard; // r3
    // s32 address; // r4
    // s32 size; // r5
    // char* data; // r6
}

// Range: 0x80016E70 -> 0x80017814
s32 mcardMenu(struct _MCARD* pMCard, enum __anon_0x1A5F0 menuEntry, enum __anon_0x1BD8E* pCommand) {
    // Parameters
    // struct _MCARD* pMCard; // r29
    // enum __anon_0x1A5F0 menuEntry; // r4
    // enum __anon_0x1BD8E* pCommand; // r30

    // References
    // -> static enum __anon_0x1A5F0 nextMenuEntry$773;
    // -> static s32 yes$771;
    // -> static enum __anon_0x1A5F0 prevMenuEntry$772;
}

// Range: 0x80016D90 -> 0x80016E70
s32 mcardOpenError(struct _MCARD* pMCard, enum __anon_0x1BD8E* pCommand) {
    // Parameters
    // struct _MCARD* pMCard; // r3
    // enum __anon_0x1BD8E* pCommand; // r4
}

// Range: 0x80016CB0 -> 0x80016D90
s32 mcardOpenDuringGameError(struct _MCARD* pMCard, enum __anon_0x1BD8E* pCommand) {
    // Parameters
    // struct _MCARD* pMCard; // r3
    // enum __anon_0x1BD8E* pCommand; // r4
}

// Erased
static s32 corruptionCheck(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r23

    // Local variables
    char* buffer; // r1+0x4AC
    s32 checksum1; // r1+0x4A8
    s32 checksum2; // r26
    s32 i; // r25
    s32 toggle; // r24

    // References
    // -> struct _MCARD mCard;
}

// Range: 0x80016950 -> 0x80016CB0
s32 mcardWrite(struct _MCARD* pMCard, s32 address, s32 size, char* data) {
    // Parameters
    // struct _MCARD* pMCard; // r28
    // s32 address; // r29
    // s32 size; // r30
    // char* data; // r31

    // Local variables
    s32 i; // r1+0x8
    char testByte; // r25

    // References
    // -> static s32 toggle2$1029;
    // -> static s32 toggle$1034;
    // -> struct __anon_0x1BB9D* gpSystem;
    // -> s32 currentIdx;
    // -> s32 bNoWriteInCurrentFrame[10];
    // -> s32 bWrite2Card;
}

// Erased
static s32 mcardGetError(struct _MCARD* pMCard, enum __anon_0x1B0CB* pMCardError) {
    // Parameters
    // struct _MCARD* pMCard; // r1+0x0
    // enum __anon_0x1B0CB* pMCardError; // r1+0x4
}

// Erased
static s32 mcardCheckSpace(struct _MCARD* pMCard, s32 size) {
    // Parameters
    // struct _MCARD* pMCard; // r30
    // s32 size; // r31

    // Local variables
    s32 freeBytes; // r1+0x18
    s32 freeFiles; // r1+0x14
}

// Range: 0x8001514C -> 0x80016950
s32 mcardOpen(struct _MCARD* pMCard, char* fileName, char* comment, char* icon, char* banner, char* gameName,
              s32* defaultConfiguration, s32 fileSize, s32 gameSize) {
    // Parameters
    // struct _MCARD* pMCard; // r31
    // char* fileName; // r28
    // char* comment; // r25
    // char* icon; // r23
    // char* banner; // r22
    // char* gameName; // r29
    // s32* defaultConfiguration; // r21
    // s32 fileSize; // r26
    // s32 gameSize; // r30

    // Local variables
    s32 i; // r19
    enum __anon_0x1BD8E command; // r1+0x34

    // References
    // -> struct __anon_0x1BB9D* gpSystem;
    // -> s32 gButtonDownToggle;
}

// Range: 0x800145FC -> 0x8001514C
s32 mcardOpenDuringGame(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r31

    // Local variables
    s32 i; // r28
    enum __anon_0x1BD8E command; // r1+0x18
    s32 loadToggle; // r27

    // References
    // -> s32 gButtonDownToggle;
}

// Range: 0x800136F4 -> 0x800145FC
s32 mcardStore(struct _MCARD* pMCard) {
    // Parameters
    // struct _MCARD* pMCard; // r29

    // Local variables
    s32 i; // r30
    s32 checksum; // r1+0x4DC
    s32 bufferOffset; // r4
    enum __anon_0x1BD8E command; // r1+0x4C8

    // References
    // -> static s32 checkFailCount$1490;
    // -> struct _MCARD mCard;
    // -> struct OSCalendarTime gDate;
}

// Range: 0x80013440 -> 0x800136F4
s32 mcardUpdate() {
    // Local variables
    s32 j; // r5
    s32 i; // r5
    s32 toggle; // r25
    enum __anon_0x1BD8E command; // r1+0x8
    s32 prevIndex; // r24
    s32 index; // r23
    s32 counter; // r22

    // References
    // -> struct _MCARD mCard;
    // -> s32 bWrite2Card;
    // -> struct __anon_0x1BB9D* gpSystem;
}
