#ifndef _GLOBALDESTRUCTORCHAIN
#define _GLOBALDESTRUCTORCHAIN

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DestructorChain {
    struct DestructorChain* next;
    void* destructor;
    void* object;
} DestructorChain;

void __destroy_global_chain(void);

#ifdef __cplusplus
}
#endif

#endif
