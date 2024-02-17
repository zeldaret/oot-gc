#ifndef _RAM_H
#define _RAM_H

#include "types.h"

typedef struct Ram {
    /* 0x00 */ void *pHost;
    /* 0x04 */ void *pBuffer;
    /* 0x08 */ unsigned int nSize;
} Ram; // size = 0x0C

#endif
