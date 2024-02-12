#ifndef _XL_LIST_H
#define _XL_LIST_H

#include "types.h"

typedef struct tXL_NODE tXL_NODE;

struct tXL_NODE {
    tXL_NODE* next;
    u8 data[];
};

// size: 0x10
typedef struct tXL_LIST {
    int nItemSize; // 0x0
    int nItemCount; // 0x4
    void* pNodeHead; // 0x8
    void* pNodeNext; // 0xC
} tXL_LIST;

int xlListReset(void);
int xlListSetup(void);
int xlListTestItem(tXL_LIST* pList, void* pItem);
int xlListFreeItem(tXL_LIST* pList, void** ppItem);
int xlListMakeItem(tXL_LIST* pList, void** ppItem);
int xlListFree(tXL_LIST** ppList);
int xlListMake(tXL_LIST** ppList);

#endif
