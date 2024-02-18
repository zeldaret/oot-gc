#include "xlList.h"
#include "xlHeap.h"
#include "types.h"

static tXL_LIST gListList;

#pragma GLOBAL_ASM("asm/non_matchings/xlList/xlListMake.s")

static inline s32 xlListWipe(tXL_LIST* pList) {
    tXL_NODE* pNode;
    tXL_NODE* pNodeNext;

    pNode = pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = pNode->next;
        if (!xlHeapFree((void**)&pNode)) {
            return 0;
        }
        pNode = pNodeNext;
    }

    pList->nItemCount = 0;
    pList->pNodeNext = NULL;
    pList->pNodeHead = NULL;
    return 1;
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlList/xlListFree.s")
#else
s32 xlListFree(tXL_LIST** ppList) {
    if (!xlListWipe(*ppList)) {
        return 0;
    }

    if (!xlListFreeItem(&gListList, (void**)ppList)) {
        return 0;
    }

    return 1;
}
#endif

s32 xlListMakeItem(tXL_LIST* pList, void** ppItem) {
    s32 nSize;
    tXL_NODE* pListNode;
    tXL_NODE* pNode;
    tXL_NODE* pNodeNext;

    nSize = pList->nItemSize + 4;
    if (!xlHeapTake((void**)&pListNode, nSize)) {
        return 0;
    }

    pListNode->next = NULL;
    *ppItem = (void*)pListNode->data;
    pNode = (tXL_NODE*)&pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = pNode->next;
        if (pNodeNext == NULL) {
            pNode->next = pListNode;
            pList->nItemCount++;
            return 1;
        }
        pNode = pNodeNext;
    }

    return 0;
}

s32 xlListFreeItem(tXL_LIST* pList, void** ppItem) {
    tXL_NODE* pNode;
    tXL_NODE* pNodeNext;

    if (pList->pNodeHead == NULL) {
        return 0;
    }

    pNode = (tXL_NODE*)&pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = pNode->next;
        if (*ppItem == (void*)pNodeNext->data) {
            pNode->next = pNodeNext->next;
            *ppItem = NULL;
            if (!xlHeapFree((void**)&pNodeNext)) {
                return 0;
            }
            pList->nItemCount--;
            return 1;
        }
        pNode = pNodeNext;
    }

    return 0;
}

static inline s32 xlListTest(tXL_LIST* pList) {
    tXL_NODE* pNode;

    if (pList == &gListList) {
        return 1;
    }

    pNode = gListList.pNodeHead;
    while (pNode != NULL) {
        if (pList == (tXL_LIST*)pNode->data) {
            return 1;
        }
        pNode = pNode->next;
    }

    return 0;
}

s32 xlListTestItem(tXL_LIST* pList, void* pItem) {
    tXL_NODE* pListNode;

    if (!xlListTest(pList) || pItem == NULL) {
        return 0;
    }

    pListNode = pList->pNodeHead;
    while (pListNode != NULL) {
        if (pItem == pListNode->data) {
            return 1;
        }
        pListNode = pListNode->next;
    }

    return 0;
}

s32 xlListSetup(void) {
    gListList.nItemCount = 0;
    gListList.nItemSize = sizeof(tXL_LIST);
    gListList.pNodeNext = NULL;
    gListList.pNodeHead = NULL;
    return 1;
}

s32 xlListReset(void) { return 1; }
