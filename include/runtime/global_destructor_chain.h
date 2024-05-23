#ifndef _GLOBALDESTRUCTORCHAIN
#define _GLOBALDESTRUCTORCHAIN

#include "dolphin/types.h"

typedef struct DestructorChain {
    struct DestructorChain* next;
    void* destructor;
    void* object;
} DestructorChain;

void __destroy_global_chain(void);

#endif
