#ifndef _MACROS_H
#define _MACROS_H

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

// No-ops increate the function's size, preventing automatic inline
#define NO_INLINE \
    {             \
        (void)0;  \
        (void)0;  \
        (void)0;  \
        (void)0;  \
    }

#define SYSTEM_CPU(pSystem) ((Cpu*)(((System*)(pSystem))->apObject[SOT_CPU]))
#define SYSTEM_PIF(pSystem) ((Pif*)(((System*)(pSystem))->apObject[SOT_PIF]))
#define SYSTEM_RAM(pSystem) ((Ram*)(((System*)(pSystem))->apObject[SOT_RAM]))
#define SYSTEM_ROM(pSystem) ((Rom*)(((System*)(pSystem))->apObject[SOT_ROM]))
#define SYSTEM_RSP(pSystem) ((Rsp*)(((System*)(pSystem))->apObject[SOT_RSP]))
#define SYSTEM_MIPS(pSystem) ((Mips*)(((System*)(pSystem))->apObject[SOT_MIPS]))

#endif
