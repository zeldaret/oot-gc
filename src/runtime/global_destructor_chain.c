#include "runtime/global_destructor_chain.h"
#include "macros.h"

#define DTORCALL_COMPLETE(dtor, objptr) (((void (*)(void*, int))dtor)(objptr, -1))

DestructorChain* __global_destructor_chain;

void __destroy_global_chain(void) {
    DestructorChain* iter;

    while ((iter = __global_destructor_chain) != 0) {
        __global_destructor_chain = iter->next;
        DTORCALL_COMPLETE(iter->destructor, iter->object);
    }
}

DTORS extern void* const __destroy_global_chain_reference = __destroy_global_chain;
