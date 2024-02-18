#ifndef _DOLPHIN_ARQ_H_
#define _DOLPHIN_ARQ_H_

#include <dolphin/types.h>

typedef void (*ARQCallback)(u32 pointerToARQRequest);

struct ARQRequest
{
    struct ARQRequest *next;
    u32 owner;
    u32 type;
    u32 priority;
    u32 source;
    u32 dest;
    u32 length;
    ARQCallback callback;
};

typedef struct ARQRequest ARQRequest;

void ARQInit(void);
void ARQPostRequest(ARQRequest *task, u32 owner, u32 type, u32 priority,
    u32 source, u32 dest, u32 length, ARQCallback callback);

#define ARQ_TYPE_MRAM_TO_ARAM ARAM_DIR_MRAM_TO_ARAM
#define ARQ_TYPE_ARAM_TO_MRAM ARAM_DIR_ARAM_TO_MRAM

#define ARQ_PRIORITY_LOW  0
#define ARQ_PRIORITY_HIGH 1
                                
#endif
