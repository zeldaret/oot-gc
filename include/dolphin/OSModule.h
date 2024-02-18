#ifndef _DOLPHIN_OSMODULE_H_
#define _DOLPHIN_OSMODULE_H_

#include <dolphin/types.h>

typedef u32 OSModuleID;

struct OSModuleInfo;
typedef struct OSModuleInfo OSModuleInfo;

typedef struct OSModuleLink
{
    OSModuleInfo *next;
    OSModuleInfo *prev;
} OSModuleLink;

struct OSModuleInfo
{
    /*0x00*/ OSModuleID id;
    /*0x04*/ OSModuleLink link;
    /*0x0C*/ u32 numSections;
    /*0x10*/ u32 sectionInfoOffset;
    /*0x14*/ u32 nameOffset;
    /*0x18*/ u32 nameSize;
    /*0x1C*/ u32 version;
};

void OSSetStringTable(void *);
BOOL OSLink(OSModuleInfo *newModule, void *bss);
BOOL OSUnlink(OSModuleInfo *oldModule);

#endif
