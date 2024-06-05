#include "dolphin/__ppc_eabi_init.h"
#include "dolphin/base/PPCArch.h"
#include "macros.h"

void __OSPSInit(void);
void __OSCacheInit(void);

ASM void __init_hardware(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfmsr r0
    ori r0, r0, 0x2000
    mtmsr r0

    mflr r31
    bl __OSPSInit

#if IS_CE
    bl __OSFPRInit
#endif

    bl __OSCacheInit
    mtlr r31
    blr
#endif // clang-format on
}

ASM void __flush_cache(register void* address, register unsigned int size) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    lis r5,  ~0
    ori r5, r5, ~14
    and r5, r5, r3
    subf r3, r5, r3
    add r4, r4, r3

loop:
    dcbst r0, r5
    sync
    icbi r0, r5
    addic r5, r5, 8
    subic. r4, r4, 8
    bge loop
    isync
    blr
#endif // clang-format on
}

void InitMetroTRK_BBA(void) { return; }

void __init_user(void) { __init_cpp(); }

typedef void (*voidfunctionptr)(void); // pointer to function returning void
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];

void __init_cpp(void) {
    voidfunctionptr* constructor;

    /*
     * call static initializers
     */
    for (constructor = _ctors; *constructor; constructor++) {
        (*constructor)();
    }
}

void _ExitProcess(void) { PPCHalt(); }
