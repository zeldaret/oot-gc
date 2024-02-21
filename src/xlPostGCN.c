#include "xlPostGCN.h"

#pragma GLOBAL_ASM("asm/non_matchings/xlPostGCN/xlPostText.s")

s32 xlPostSetup(void) {
    return 1;
}

s32 xlPostReset(void) {
    return 1;
}
