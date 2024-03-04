#ifndef _SIMGCN_H
#define _SIMGCN_H

#include "dolphin.h"
#include "system.h"

typedef struct __anon_0xD7D1 {
    /* 0x00 */ u16 height;
    /* 0x02 */ u16 width;
    /* 0x04 */ u32 format;
    /* 0x08 */ char* data;
    /* 0x0C */ GXTexWrapMode wrapS;
    /* 0x10 */ GXTexWrapMode wrapT;
    /* 0x14 */ GXTexFilter minFilter;
    /* 0x18 */ GXTexFilter magFilter;
    /* 0x1C */ f32 LODBias;
    /* 0x20 */ u8 edgeLODEnable;
    /* 0x21 */ u8 minLOD;
    /* 0x22 */ u8 maxLOD;
    /* 0x23 */ u8 unpacked;
} __anon_0xD7D1; // size = 0x24

typedef struct __anon_0xDA2C {
    /* 0x0 */ u16 numEntries;
    /* 0x2 */ u8 unpacked;
    /* 0x3 */ u8 pad8;
    /* 0x4 */ GXTlutFmt format;
    /* 0x8 */ char* data;
} __anon_0xDA2C; // size = 0xC

typedef struct __anon_0xDAF8 {
    /* 0x0 */ __anon_0xD7D1* textureHeader;
    /* 0x4 */ __anon_0xDA2C* CLUTHeader;
} __anon_0xDAF8; // size = 0x8

typedef struct __anon_0xDB69 {
    /* 0x0 */ u32 versionNumber;
    /* 0x4 */ u32 numDescriptors;
    /* 0x8 */ __anon_0xDAF8* descriptorArray;
} __anon_0xDB69; // size = 0xC

typedef enum __anon_0x61D7 {
    S_M_NONE = -1,
    S_M_DISK_COVER_OPEN = 0,
    S_M_DISK_WRONG_DISK = 1,
    S_M_DISK_READING_DISK = 2,
    S_M_DISK_FATAL_ERROR = 3,
    S_M_DISK_RETRY_ERROR = 4,
    S_M_DISK_NO_DISK = 5,
    S_M_DISK_DEFAULT_ERROR = 6,
    S_M_CARD_LD01 = 7,
    S_M_CARD_LD02 = 8,
    S_M_CARD_LD03 = 9,
    S_M_CARD_LD04 = 10,
    S_M_CARD_LD05_1 = 11,
    S_M_CARD_LD05_2 = 12,
    S_M_CARD_LD06_1 = 13,
    S_M_CARD_LD06_2 = 14,
    S_M_CARD_LD06_3 = 15,
    S_M_CARD_LD06_4 = 16,
    S_M_CARD_LD07 = 17,
    S_M_CARD_GF01 = 18,
    S_M_CARD_GF02 = 19,
    S_M_CARD_GF03 = 20,
    S_M_CARD_GF04 = 21,
    S_M_CARD_GF05 = 22,
    S_M_CARD_GF06 = 23,
    S_M_CARD_IN01 = 24,
    S_M_CARD_IN02 = 25,
    S_M_CARD_IN03 = 26,
    S_M_CARD_IN04 = 27,
    S_M_CARD_IN05 = 28,
    S_M_CARD_SV01 = 29,
    S_M_CARD_SV01_2 = 30,
    S_M_CARD_SV02 = 31,
    S_M_CARD_SV03 = 32,
    S_M_CARD_SV04 = 33,
    S_M_CARD_SV05_1 = 34,
    S_M_CARD_SV06_1 = 35,
    S_M_CARD_SV06_2 = 36,
    S_M_CARD_SV06_3 = 37,
    S_M_CARD_SV06_4 = 38,
    S_M_CARD_SV06_5 = 39,
    S_M_CARD_SV07 = 40,
    S_M_CARD_SV08 = 41,
    S_M_CARD_SV09 = 42,
    S_M_CARD_SV10 = 43,
    S_M_CARD_SV11 = 44,
    S_M_CARD_SV12 = 45,
    S_M_CARD_SV_SHARE = 46,
    S_M_CARD_DEFAULT_ERROR = 47,
} __anon_0x61D7;

// __anon_0xA982
typedef enum SimArgumentType {
    SAT_NONE = -1,
    SAT_NAME = 0,
    SAT_PROGRESSIVE = 1,
    SAT_VIBRATION = 2,
    SAT_CONTROLLER = 3,
    SAT_XTRA = 4,
    SAT_MEMORYCARD = 5,
    SAT_MOVIE = 6,
    SAT_RESET = 7,
    SAT_COUNT = 8
} SimArgumentType;

extern s32 gDVDResetToggle;
extern s32 gbDisplayedError;

extern void* gpFrame;
extern void* gpSound;
extern System* gpSystem;

extern u32 gz_bnrSize;
extern u32 gz_iconSize;

void simulatorUnpackTexPalette(__anon_0xDB69* pal);
s32 simulatorDVDOpen(char* szNameFile, DVDFileInfo* pFileInfo);
s32 simulatorDVDRead(DVDFileInfo* pFileInfo, void* anData, s32 nSizeRead, s32 nOffset, DVDCallback callback);
s32 simulatorShowLoad(s32 /* unknown */, char* szNameFile, f32 rProgress);
s32 simulatorReadSRAM(u32 address, u8* data, s32 size);
s32 simulatorWriteSRAM(u32 address, u8* data, s32 size);
s32 simulatorReadFLASH(u32 address, u8* data, s32 size);
s32 simulatorWriteFLASH(u32 address, u8* data, s32 size);
s32 simulatorCopyControllerMap(u32* mapDataOutput, u32* mapDataInput);
s32 simulatorSetControllerMap(u32* mapData, s32 channel);
void simulatorResetAndPlayMovie();
s32 simulatorDVDShowError(s32 nStatus, void*, s32, u32);
s32 simulatorGetArgument(SimArgumentType eType, char** pszArgument);
s32 simulatorPlayMovie(void);

#endif
