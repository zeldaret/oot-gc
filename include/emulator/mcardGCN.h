#ifndef _MCARD_H
#define _MCARD_H

#include "dolphin.h"

typedef enum MemCardCommand {
    MC_C_NONE = 0,
    MC_C_CONTINUE = 1,
    MC_C_IPL = 2,
    MC_C_GO_TO_GAME = 3,
    MC_C_CREATE_GAME = 4,
    MC_C_DELETE_GAME = 5,
    MC_C_FORMAT_CARD = 6,
} MemCardCommand;

typedef enum MemCardError {
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
} MemCardError;

typedef enum MemCardMessage {
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
} MemCardMessage;

typedef struct MemCardGameInfo {
    /* 0x00 */ s32 configuration;
    /* 0x04 */ s32 size;
    /* 0x08 */ s32 offset;
    /* 0x0C */ char* buffer;
    /* 0x10 */ bool* writtenBlocks;
    /* 0x14 */ bool writtenConfig;
} MemCardGameInfo; // size = 0x18

typedef struct MemCardFileInfo {
    /* 0x000 */ s32 currentGame;
    /* 0x004 */ s32 fileSize;
    /* 0x008 */ char name[33];
    /* 0x02C */ s32 numberOfGames;
    /* 0x030 */ MemCardGameInfo game;
    /* 0x048 */ bool changedDate;
    /* 0x04C */ bool changedChecksum;
    /* 0x050 */ s32 gameSize[16];
    /* 0x090 */ s32 gameOffset[16];
    /* 0x0D0 */ s32 gameConfigIndex[16];
    /* 0x110 */ char gameName[16][33];
    /* 0x320 */ OSCalendarTime time;
    /* 0x348 */ CARDFileInfo fileInfo;
} MemCardFileInfo; // size = 0x35C

// __anon_0x1B36F
typedef struct _MCARD {
    /* 0x000 */ MemCardFileInfo file;
    /* 0x35C */ MemCardError error;
    /* 0x360 */ s32 slot;
    /* 0x364 */ bool (*pPollFunction)(void);
    /* 0x368 */ s32 pollPrevBytes;
    /* 0x36C */ s32 pollSize;
    /* 0x370 */ char pollMessage[256];
    /* 0x470 */ bool saveToggle;
    /* 0x474 */ char* writeBuffer;
    /* 0x478 */ char* readBuffer;
    /* 0x47C */ bool writeToggle;
    /* 0x480 */ bool soundToggle;
    /* 0x484 */ s32 writeStatus;
    /* 0x488 */ s32 writeIndex;
    /* 0x48C */ s32 accessType;
    /* 0x490 */ bool gameIsLoaded;
    /* 0x494 */ char saveFileName[256];
    /* 0x594 */ char saveComment[256];
    /* 0x694 */ char* saveIcon;
    /* 0x698 */ char* saveBanner;
    /* 0x69C */ char saveGameName[256];
    /* 0x79C */ s32 saveFileSize;
    /* 0x7A0 */ s32 saveGameSize;
    /* 0x7A4 */ bool bufferCreated;
    /* 0x7A8 */ s32 cardSize;
    /* 0x7AC */ bool wait;
#if VERSION != MQ_J
    /* 0x7B0 */ bool isBroken;
#endif
    /* 0x7B4 */ s32 saveConfiguration;
} MemCard; // size = 0x7B8

extern MemCard mCard;

bool mcardReadGameData(MemCard* pMCard);
bool mcardWriteGameDataReset(MemCard* pMCard);
bool mcardReInit(MemCard* pMCard);
bool mcardInit(MemCard* pMCard);
bool mcardFileSet(MemCard* pMCard, char* name);
bool mcardGameSet(MemCard* pMCard, char* name);
bool mcardFileCreate(MemCard* pMCard, char* name, char* comment, char* icon, char* banner, s32 size);
bool mcardGameCreate(MemCard* pMCard, char* name, s32 defaultConfiguration, s32 size);
bool mcardCardErase(MemCard* pMCard);
bool mcardFileErase(MemCard* pMCard);
bool mcardGameErase(MemCard* pMCard, s32 index);
bool mcardGameRelease(MemCard* pMCard);
bool mcardRead(MemCard* pMCard, s32 address, s32 size, char* data);
bool mcardMenu(MemCard* pMCard, MemCardMessage menuEntry, MemCardCommand* pCommand);
bool mcardOpenError(MemCard* pMCard, MemCardCommand* pCommand);
bool mcardOpenDuringGameError(MemCard* pMCard, MemCardCommand* pCommand);
bool mcardWrite(MemCard* pMCard, s32 address, s32 size, char* data);
bool mcardOpen(MemCard* pMCard, char* fileName, char* comment, char* icon, char* banner, char* gameName,
               s32* defaultConfiguration, s32 fileSize, s32 gameSize);
bool mcardOpenDuringGame(MemCard* pMCard);
bool mcardStore(MemCard* pMCard);
bool mcardUpdate(void);

#endif
