#ifndef _DOLPHIN_OS_OSREBOOT_H
#define _DOLPHIN_OS_OSREBOOT_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void OSSetSaveRegion(void* start, void* end);
void OSGetSaveRegion(void** start, void** end);
void OSGetSavedRegion(void** start, void** end);
void __OSReboot(u32 resetCode, u32 bootDol);

#ifdef __cplusplus
}
#endif

#endif
