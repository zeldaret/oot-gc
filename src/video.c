#include "video.h"
#include "video_jumptables.h"
#include "xlObject.h"

_XL_OBJECTTYPE gClassVideo = {
    "VIDEO", sizeof(Video), NULL, (EventFunc)videoEvent,
};

void* jtbl_800EE880[] = {
    &lbl_8008EAA8,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EAB4,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EAC0,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EACC,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EADC,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EAF4,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB00,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB0C,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB18,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB24,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB30,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB3C,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB48,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB60,
    &lbl_8008EB54,
};

void* jtbl_800EE954[] = {
    &lbl_8008EBDC,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EBEC,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EC78,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EC88,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EC98,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008ECB4,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008ECC0,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008ECD0,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008ECE0,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008ECF0,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008ED38,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008ED50,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008ED68,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDE8,
    &lbl_8008EDA8,
};

#pragma GLOBAL_ASM("asm/non_matchings/video/videoPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoForceRetrace.s")

#pragma GLOBAL_ASM("asm/non_matchings/video/videoEvent.s")
