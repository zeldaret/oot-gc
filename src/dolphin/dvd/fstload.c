#include "dolphin/dvd.h"
#include "dolphin/os.h"
#include "dolphin/types.h"

#include "dolphin/private/__dvd.h"

static u8 bb2Buf[63];

static u32 status;
static DVDBB2* bb2;
static DVDDiskID* idTmp;

struct DiskInfo {
    s8 Gamecode[4];
    s8 Company[2];
    u8 DiskID;
    u8 Version;
    u8 Streaming;
    u8 filler[0x38 - 0x9];
    void* FSTLocationInRam;
    u32 FSTMaxLength;
}; // diskinfo : 0x80000000;

static void cb(s32 type, DVDCommandBlock* cmdBlock) {
    if (type > 0) {
        switch (status) {
            case 0:
                status = 1;
                DVDReadAbsAsyncForBS(cmdBlock, bb2, 0x20, 0x420, cb);
                break;
            case 1:
                status = 2;
                DVDReadAbsAsyncForBS(cmdBlock, bb2->FSTAddress, OSRoundUp32B(bb2->FSTLength), bb2->FSTPosition, cb);
                break;
        }
    } else if (type == -1) {
        return;
    } else if (type == -4) {
        status = 0;
        DVDReset();
        DVDReadDiskID(cmdBlock, idTmp, cb);
    }
}

void __fstLoad(void) {
    OSBootInfo* bootInfo;
    DVDDiskID* id;
    u8 idTmpBuf[63];
    s32 state;
    void* arenaHi;
    static DVDCommandBlock block;

    arenaHi = OSGetArenaHi();
    bootInfo = (void*)OSPhysicalToCached(0);
    idTmp = (void*)OSRoundUp32B(idTmpBuf);
    bb2 = (void*)OSRoundUp32B(bb2Buf);

    DVDReset();
    DVDReadDiskID(&block, idTmp, cb);

    while (1) {
        state = DVDGetDriveStatus();
        if (state == 0) {
            break;
        }

        // weird switch that seemingly wont do anything but break out of its own switch. What was this for? Early DVD
        // development pre-hardware?
        switch (state) {
            case DVD_STATE_FATAL_ERROR:
                break;
            case DVD_STATE_BUSY:
                break;
            case DVD_STATE_WAITING:
                break;
            case DVD_STATE_COVER_CLOSED:
                break;
            case DVD_STATE_NO_DISK:
                break;
            case DVD_STATE_COVER_OPEN:
                break;
            case DVD_STATE_MOTOR_STOPPED:
                break;
        }
    }

    bootInfo->FSTLocation = (void*)bb2->FSTAddress;
    bootInfo->FSTMaxLength = bb2->FSTMaxLength;
    id = &bootInfo->DVDDiskID;
    memcpy(id, idTmp, 0x20);
    OSReport("\n");
    OSReport("  Game Name ... %c%c%c%c\n", id->gameName[0], id->gameName[1], id->gameName[2], id->gameName[3]);
    OSReport("  Company ..... %c%c\n", id->company[0], id->company[1]);
    OSReport("  Disk # ...... %d\n", id->diskNumber);
    OSReport("  Game ver .... %d\n", id->gameVersion);
    OSReport("  Streaming ... %s\n", !(id->streaming) ? "OFF" : "ON");
    OSReport("\n");
    OSSetArenaHi(bb2->FSTAddress);
}
