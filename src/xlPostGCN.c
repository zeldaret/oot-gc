#include "xlPostGCN.h"

GXTexObj g_texMap[4];

int xlPostReset(void) {
    return 1;
}

int xlPostSetup(void) {
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/xlPostGCN/xlPostText.s")
