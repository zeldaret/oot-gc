#ifndef _DOLPHIN_DB_H
#define _DOLPHIN_DB_H

#include "dolphin/db/DBInterface.h"
#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_DBINTERFACE_ADDR 0x00000040

bool DBIsDebuggerPresent(void);
void DBPrintf(char* str, ...);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_DB_H_
