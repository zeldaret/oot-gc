#ifndef _XL_LIST_H
#define _XL_LIST_H

#include "dolphin.h"

// List nodes consist of a pointer to the next node followed by an arbitrary amount of data.
#define NODE_NEXT(pNode) (*(void**)(pNode))
#define NODE_DATA(pNode) (((u8*)(pNode) + 4))

typedef struct tXL_LIST {
    /* 0x0 */ s32 nItemSize;
    /* 0x4 */ s32 nItemCount;
    /* 0x8 */ void* pNodeHead;
    /* 0xC */ void* pNodeNext;
} tXL_LIST; // size = 0x10

bool xlListMake(tXL_LIST** ppList, s32 nItemSize);
bool xlListFree(tXL_LIST** ppList);
bool xlListMakeItem(tXL_LIST* pList, void** ppItem);
bool xlListFreeItem(tXL_LIST* pList, void** ppItem);
bool xlListTestItem(tXL_LIST* pList, void* pItem);
bool xlListSetup(void);
bool xlListReset(void);

#endif
