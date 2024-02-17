#ifndef _DISK_H
#define _DISK_H

#include "types.h"

// based on how other "gClass" works, we can assume this was the struct used for Disk
typedef struct Disk {
    /* 0x00 */ void* pHost;
} Disk; // size = 0x04

s32 diskEvent(Disk* pDisk, s32 nEvent, void* pArgument);

#endif
