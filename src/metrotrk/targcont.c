#include "metrotrk/targcont.h"
#include "metrotrk/targimpl.h"
#include "metrotrk/dolphin_trk_glue.h"

DSError TRKTargetContinue(void) {
    TRKTargetSetStopped(false);
    UnreserveEXI2Port();
    TRKSwapAndGo();
    ReserveEXI2Port();
    return kNoError;
}
