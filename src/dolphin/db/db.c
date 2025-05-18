#include "dolphin/db.h"
#include "dolphin/base/PPCArch.h"
#include "dolphin/os.h"

DBInterface* __DBInterface = NULL;
int DBVerbose;

void __DBExceptionDestination(void);

void DBInit(void) {
    __DBInterface = (DBInterface*)OSPhysicalToCached(OS_DBINTERFACE_ADDR);
    __DBInterface->ExceptionDestination = (void (*)())OSCachedToPhysical(__DBExceptionDestination);
    DBVerbose = true;
}

void __DBExceptionDestinationAux(void) {
    u32* contextAddr = (void*)0x00C0;
    OSContext* context = (OSContext*)OSPhysicalToCached(*contextAddr);

    OSReport("DBExceptionDestination\n");
    OSDumpContext(context);
    PPCHalt();
}

ASM void __DBExceptionDestination(void) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfmsr   r3
    ori     r3, r3, 0x10 | 0x20
    mtmsr   r3
    b __DBExceptionDestinationAux
#endif // clang-format on
}

bool __DBIsExceptionMarked(__OSException exception) {
    u32 mask = 1 << exception;

    return (bool)(__DBInterface->exceptionMask & mask);
}

void DBPrintf(char* format, ...) {}
