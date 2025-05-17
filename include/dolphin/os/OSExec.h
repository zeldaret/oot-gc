#ifndef _DOLPHIN_OS_OSEXEC_H
#define _DOLPHIN_OS_OSEXEC_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    bool valid;
    u32 restartCode;
    u32 bootDol;
    void* regionStart;
    void* regionEnd;
    int argsUseDefault;
    void* argsAddr;
} OSExecParams;

typedef int (*appGetNextCallback)(void*, u32*, u32*);
typedef void (*appInitCallback)(void (*)(char*));
typedef void* (*appGetEntryCallback)();
typedef void (*AppLoaderCallback)(appInitCallback*, appGetNextCallback*, appGetEntryCallback*);

OSExecParams* __OSExecParams AT_ADDRESS(0x800030F0);
s32 __OSAppLoaderOffset AT_ADDRESS(0x800030F4);

void OSExecv(const char* dolfile, const char** argv);
void OSExecl(const char* dolfile, const char* arg0, ...);

#ifdef __cplusplus
}
#endif

#endif
