#include "dolphin/base/PPCArch.h"
#include "dolphin/os.h"
#include "macros.h"
#include "string.h"

void __OSSystemCallVectorStart();
void __OSSystemCallVectorEnd();

static ASM void SystemCallVector() {
#ifdef __MWERKS__ // clang-format off
    nofralloc
entry __OSSystemCallVectorStart
    mfspr r9, HID0
    ori r10, r9, 8
    mtspr HID0, r10
    isync
        sync
    mtspr HID0, r9

    rfi

entry __OSSystemCallVectorEnd
    nop
#endif // clang-format on
}

void __OSInitSystemCall() {
    void* addr = OSPhysicalToCached(0x00C00);
    memcpy(addr, __OSSystemCallVectorStart, (size_t)__OSSystemCallVectorEnd - (size_t)__OSSystemCallVectorStart);
    DCFlushRangeNoSync(addr, 0x100);
    __sync();
    ICInvalidateRange(addr, 0x100);
}
