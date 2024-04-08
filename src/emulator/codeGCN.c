#include "emulator/codeGCN.h"

_XL_OBJECTTYPE gClassCode = {
    "Code",
    sizeof(Code),
    NULL,
    (EventFunc)codeEvent,
};

static void* gpBufferFunction;
static u32* ganDataCode;

s32 codeEvent(Code* pCode, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            gpBufferFunction = NULL;
            ganDataCode = NULL;
            break;
        case 0:
        case 1:
        case 3:
        case 5:
        case 6:
            break;
        default:
            return 0;
    }

    return 1;
}
