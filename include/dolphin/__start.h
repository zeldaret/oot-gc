#ifndef _DOLPHIN__START
#define _DOLPHIN__START

#include "dolphin/db.h"
#include "dolphin/types.h"
#include "macros.h"

#define PAD3_BUTTON_ADDR 0x800030E4
#define OS_RESET_RESTART 0
#define EXCEPTIONMASK_ADDR 0x80000044
#define BOOTINFO2_ADDR 0x800000F4
#define OS_BI2_DEBUGFLAG_OFFSET 0xC
#define ARENAHI_ADDR 0x80000034
#define DEBUGFLAG_ADDR 0x800030E8
#define DVD_DEVICECODE_ADDR 0x800030E6

extern void InitMetroTRK(void);

extern u16 Pad3Button;

extern int main(int argc, char* argv[]);
extern void exit(int);
extern void __init_user(void);
extern void InitMetroTRK_BBA(void);
extern void OSInit(void);
extern void DBInit(void);
extern void OSResetSystem(bool reset, u32 resetCode, bool forceMenu);
extern void __OSCacheInit(void);
extern void __OSPSInit(void);

INIT extern void __check_pad3(void);
INIT extern void __start(void);
INIT extern void __init_registers(void);
INIT extern void __init_data(void);

INIT extern char _stack_addr[];
INIT extern char _SDA_BASE_[];
INIT extern char _SDA2_BASE_[];

#endif // _DOLPHIN__START
