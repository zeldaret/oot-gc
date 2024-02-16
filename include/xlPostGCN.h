#ifndef _XL_POST_GCN_H
#define _XL_POST_GCN_H

#include "types.h"

//! TODO: take this from the SDK
typedef struct GXTexObj {
    /* 0x00 */ unsigned long dummy[8];
} GXTexObj; // size = 0x20

int xlPostReset(void);
int xlPostSetup(void);
int xlPostText(void);

#endif
