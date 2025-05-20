#include "metrotrk/main_TRK.h"
#include "metrotrk/mainloop.h"
#include "metrotrk/nubinit.h"

static int TRK_mainError;

u8 TRKTargetCPUMinorType(void) { return 0x54; }

int TRK_main(void) {
    TRK_mainError = TRKInitializeNub();

    if (!TRK_mainError) {
        TRKNubWelcome();
        TRKNubMainLoop();
    }

    return TRK_mainError = TRKTerminateNub();
}
