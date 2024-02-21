#ifndef _DISK_H
#define _DISK_H

#include <dolphin/types.h>

// __anon_0x73B29
typedef struct Disk {
    /* 0x00 */ void* pHost;
} Disk; // size = 0x04

s32 diskEvent(Disk* pDisk, s32 nEvent, void* pArgument);

#endif
