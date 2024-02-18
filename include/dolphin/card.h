#ifndef _DOLPHIN_CARD_H_
#define _DOLPHIN_CARD_H_

#include <dolphin/OSAlarm.h>
#include <dolphin/dsp.h>
#include <dolphin/dvd.h>

#define CARD_RESULT_UNLOCKED       1
#define CARD_RESULT_READY          0
#define CARD_RESULT_BUSY          -1
#define CARD_RESULT_WRONGDEVICE   -2
#define CARD_RESULT_NOCARD        -3
#define CARD_RESULT_NOFILE        -4
#define CARD_RESULT_IOERROR       -5
#define CARD_RESULT_BROKEN        -6
#define CARD_RESULT_EXIST         -7
#define CARD_RESULT_NOENT         -8
#define CARD_RESULT_INSSPACE      -9
#define CARD_RESULT_NOPERM       -10
#define CARD_RESULT_LIMIT        -11
#define CARD_RESULT_NAMETOOLONG  -12
#define CARD_RESULT_ENCODING     -13
#define CARD_RESULT_CANCELED     -14
#define CARD_RESULT_FATAL_ERROR -128

typedef void (*CARDCallback)(s32 chan, s32 result);

typedef struct CARDFileInfo
{
    /*0x00*/ s32 chan;
    /*0x04*/ s32 fileNo;
    /*0x08*/ s32 offset;
    /*0x0C*/ s32 length;
    /*0x10*/ u16 iBlock;
} CARDFileInfo;

#define CARD_FILENAME_MAX 32
#define CARD_MAX_FILE 127
#define CARD_ICON_MAX 8

typedef struct CARDStat
{
    /*0x00*/ char fileName[CARD_FILENAME_MAX];
    /*0x20*/ u32 length;
    /*0x24*/ u32 time;
    /*0x28*/ u8 gameName[4];
    /*0x2C*/ u8 company[2];
    /*0x2E*/ u8 bannerFormat;
    /*0x30*/ u32 iconAddr;
    /*0x34*/ u16 iconFormat;
    /*0x36*/ u16 iconSpeed;
    /*0x38*/ u32 commentAddr;
    /*0x3C*/ u32 offsetBanner;
    /*0x40*/ u32 offsetBannerTlut;
    /*0x44*/ u32 offsetIcon[CARD_ICON_MAX];
    /*0x64*/ u32 offsetIconTlut;
    /*0x68*/ u32 offsetData;
} CARDStat;

typedef struct CARDDir
{
    /*0x00*/ u8 gameName[4];
    /*0x04*/ u8 company[2];
    /*0x06*/ u8 _padding0;
    /*0x07*/ u8 bannerFormat;
    /*0x08*/ u8 fileName[CARD_FILENAME_MAX];
    /*0x28*/ u32 time;     // seconds since 01/01/2000 midnight
    /*0x2C*/ u32 iconAddr; // 0xffffffff if not used
    /*0x30*/ u16 iconFormat;
    /*0x32*/ u16 iconSpeed;
    /*0x34*/ u8 permission;
    u8 copyTimes;
    /*0x36*/ u16 startBlock;
    u16 length;
    u8 _padding1[2];
    u32 commentAddr; // 0xffffffff if not used
} CARDDir;

typedef struct CARDControl
{
    /*0x00*/ BOOL attached;
    /*0x04*/ s32 result;
    /*0x08*/ u16 size;
    /*0x0A*/ u16 pageSize;
    /*0x0C*/ s32 sectorSize;
    /*0x10*/ u16 cBlock;
    /*0x12*/ u16 vendorID;
    /*0x14*/ s32 latency;
    /*0x18*/ u8 id[12];
    /*0x24*/ int mountStep;
    /*0x28*/ u32 scramble;
    /*0x2C*/ int formatStep;
    DSPTaskInfo task;
    void *workArea;
    /*0x84*/ CARDDir *currentDir;
    u16 *currentFat;
    OSThreadQueue threadQueue;
    u8 cmd[9];
    s32 cmdlen;
    volatile u32 mode;
    int retry;
    int repeat;
    u32 addr;
    void *buffer;
    s32 xferred;
    u16 freeNo;
    u16 startBlock;
    /*0xC0*/ CARDFileInfo *fileInfo;
    CARDCallback extCallback;
    CARDCallback txCallback;
    CARDCallback exiCallback;
    CARDCallback apiCallback;
    CARDCallback xferCallback;
    CARDCallback eraseCallback;
    CARDCallback unlockCallback;
    OSAlarm alarm;
} CARDControl;

void CARDInit(void);
s32 CARDUnmount(s32 chan);
s32 CARDCancel(CARDFileInfo *fileInfo);
s32 CARDOpen(s32 chan, char *fileName, CARDFileInfo *fileInfo);
s32 CARDClose(CARDFileInfo *fileInfo);
s32 CARDProbeEx(s32 chan, s32 *memSize, s32 *sectorSize);
s32 CARDMountAsync(s32 chan, void *workArea, CARDCallback detachCallback,
    CARDCallback attachCallback);
s32 CARDGetResultCode(s32 chan);
s32 CARDCheckAsync(s32 chan, CARDCallback callback);
s32 CARDFreeBlocks(s32 chan, s32 *byteNotUsed, s32 *filesNotUsed);
s32 CARDCreateAsync(s32 chan, char *fileName, u32 size, CARDFileInfo *fileInfo, CARDCallback callback);
s32 CARDWriteAsync(CARDFileInfo* fileInfo, void *addr, s32 length, s32 offset, CARDCallback callback);
s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat *stat, CARDCallback callback);
s32 CARDReadAsync(CARDFileInfo* fileInfo, void *addr, s32 length, s32 offset, CARDCallback callback);
s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat *stat);
s32 CARDFastOpen(s32 chan, s32 fileNo, CARDFileInfo *fileInfo);
s32 CARDFastDeleteAsync(s32 chan, s32 fileNo, CARDCallback callback);
s32 CARDDeleteAsync(s32 chan, char *fileName, CARDCallback callback);
s32 CARDRenameAsync(s32 chan, char *oldName, char *newName, CARDCallback callback);
s32 CARDMount(s32 chan, void *workArea, CARDCallback detachCallback);
s32 CARDDelete(s32 chan, char *fileName);
s32 CARDRename(s32 chan, char *oldName, char *newName);

#endif
