#ifndef _XL_LIST_H
#define _XL_LIST_H

#include "dolphin.h"

typedef struct tXL_NODE tXL_NODE;

struct tXL_NODE {
    /* 0x0 */ tXL_NODE* next;
    /* 0x4 */ u8 data[];
}; // size = 0x4

typedef struct tXL_LIST {
    /* 0x0 */ s32 nItemSize;
    /* 0x4 */ s32 nItemCount;
    /* 0x8 */ void* pNodeHead;
    /* 0xC */ void* pNodeNext;
} tXL_LIST; // size = 0x10

s32 xlListMake(tXL_LIST** ppList, s32 nItemSize);
s32 xlListFree(tXL_LIST** ppList);
s32 xlListMakeItem(tXL_LIST* pList, void** ppItem);
s32 xlListFreeItem(tXL_LIST* pList, void** ppItem);
s32 xlListTestItem(tXL_LIST* pList, void* pItem);
s32 xlListSetup(void);
s32 xlListReset(void);

#endif
