#ifndef _DOLPHIN_DVD_H_
#define _DOLPHIN_DVD_H_

#include "dolphin/types.h"

#define DVD_ASSERTMSGLINE(line, cond, msg) \
    if (!(cond))                           \
    OSPanic(__FILE__, line, msg)

#define DVD_ASSERTMSG1LINE(line, cond, msg, arg1) \
    if (!(cond))                                  \
    OSPanic(__FILE__, line, msg, arg1)

#define DVD_ASSERTMSG2LINE(line, cond, msg, arg1, arg2) \
    if (!(cond))                                        \
    OSPanic(__FILE__, line, msg, arg1, arg2)

// DVD Commands
#define DVD_COMMAND_NONE 0
#define DVD_COMMAND_READ 1
#define DVD_COMMAND_SEEK 2
#define DVD_COMMAND_CHANGE_DISK 3
#define DVD_COMMAND_BSREAD 4
#define DVD_COMMAND_READID 5
#define DVD_COMMAND_INITSTREAM 6
#define DVD_COMMAND_CANCELSTREAM 7
#define DVD_COMMAND_STOP_STREAM_AT_END 8
#define DVD_COMMAND_REQUEST_AUDIO_ERROR 9
#define DVD_COMMAND_REQUEST_PLAY_ADDR 10
#define DVD_COMMAND_REQUEST_START_ADDR 11
#define DVD_COMMAND_REQUEST_LENGTH 12
#define DVD_COMMAND_AUDIO_BUFFER_CONFIG 13
#define DVD_COMMAND_INQUIRY 14
#define DVD_COMMAND_BS_CHANGE_DISK 15
#define DVD_COMMAND_UNK_16 16

typedef struct {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDFileInfo DVDFileInfo;
typedef struct DVDQueue DVDQueue;

typedef void (*DVDCallback)(s32 result, DVDFileInfo* fileInfo);
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock* block);
typedef void (*DVDDoneReadCallback)(s32, DVDFileInfo*);

struct DVDCommandBlock {
    /* 0x00 */ DVDCommandBlock* next;
    /* 0x04 */ DVDCommandBlock* prev;
    /* 0x08 */ u32 command;
    /* 0x0C */ s32 state;
    /* 0x10 */ u32 offset;
    /* 0x14 */ u32 length;
    /* 0x18 */ void* addr;
    /* 0x1C */ u32 currTransferSize;
    /* 0x20 */ u32 transferredSize;
    /* 0x24 */ DVDDiskID* id;
    /* 0x28 */ DVDCBCallback callback;
    /* 0x2C */ void* userData;
};

struct DVDFileInfo {
    /* 0x00 */ DVDCommandBlock cb;
    /* 0x30 */ u32 startAddr;
    /* 0x34 */ u32 length;
    /* 0x38 */ DVDCallback callback;
};

struct DVDQueue {
    /* 0x00 */ DVDQueue* mHead;
    /* 0x04 */ DVDQueue* mTail;
};

typedef struct DVDDir {
    u32 entryNum;
    u32 location;
    u32 next;
} DVDDir;

typedef struct DVDDirEntry {
    u32 entryNum;
    bool isDir;
    char* name;
} DVDDirEntry;

void DVDInit(void);
void DVDReset(void);
bool DVDOpen(const char* fileName, DVDFileInfo* fileInfo);
bool DVDClose(DVDFileInfo*);
bool DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio);
s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio);
s32 DVDConvertPathToEntrynum(const char* pathPtr);
bool DVDGetCurrentDir(char* path, u32 maxlen);
s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block);
s32 DVDGetDriveStatus(void);
bool DVDSetAutoInvalidation(bool autoInval);
void DVDResume(void);
bool DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback);
bool DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback);
s32 DVDGetStreamErrorStatus(DVDCommandBlock* block);
s32 DVDCancel(DVDCommandBlock* block);
bool DVDCheckDisk(void);
DVDDiskID* DVDGetCurrentDiskID(void);
bool DVDCompareDiskID(const DVDDiskID* discID1, const DVDDiskID* discID2);
void __DVDLowSetWAType(u32 type, u32 location);
bool DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback);
s32 DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback) ;
s32 DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback);

#define DVDReadAsync(fileInfo, addr, length, offset, callback) \
    DVDReadAsyncPrio((fileInfo), (addr), (length), (offset), (callback), 2)

#define DVD_RESULT_GOOD 0
#define DVD_RESULT_FATAL_ERROR -1
#define DVD_RESULT_IGNORED -2
#define DVD_RESULT_CANCELED -3

#define DVD_STATE_FATAL_ERROR -1
#define DVD_STATE_END 0
#define DVD_STATE_BUSY 1
#define DVD_STATE_WAITING 2
#define DVD_STATE_COVER_CLOSED 3
#define DVD_STATE_NO_DISK 4
#define DVD_STATE_COVER_OPEN 5
#define DVD_STATE_WRONG_DISK 6
#define DVD_STATE_MOTOR_STOPPED 7
#define DVD_STATE_PAUSING 8
#define DVD_STATE_IGNORED 9
#define DVD_STATE_CANCELED 10
#define DVD_STATE_RETRY 11

#define DVD_MIN_TRANSFER_SIZE 32

#define DVD_FILEINFO_READY 0
#define DVD_FILEINFO_BUSY 1

#define DVD_AIS_SUCCESS 0

#endif
