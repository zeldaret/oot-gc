#include "xlFileGCN.h"
#include "xlObject.h"

_XL_OBJECTTYPE gTypeFile = {
    "FILE",
    sizeof(tXL_FILE),
    NULL,
    (EventFunc)xlFileEvent
};

static FileGcnOpenCallback gpfOpen;
static FileGcnCloseCallback gpfRead;

#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileSetOpen.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileSetRead.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileGetSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileOpen.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileClose.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileGet.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileSetPosition.s")

#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileEvent.s")
