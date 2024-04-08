#ifndef _DOLPHIN_DBINTERFACE_H_
#define _DOLPHIN_DBINTERFACE_H_

#define OS_DBINTERFACE_ADDR 0x00000040

void DBInit(void);
void DBPrintf(char* str, ...);

#endif
