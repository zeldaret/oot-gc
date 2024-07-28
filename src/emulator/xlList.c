#include "emulator/xlList.h"
#include "dolphin.h"
#include "emulator/xlHeap.h"
#include "macros.h"

static tXL_LIST gListList;

bool xlListMake(tXL_LIST** ppList, s32 nItemSize) {
    nItemSize = (nItemSize + 3) & ~3;

    if (xlListMakeItem(&gListList, (void**)ppList)) {
        (*ppList)->nItemCount = 0;
        (*ppList)->nItemSize = nItemSize;
        (*ppList)->pNodeNext = NULL;
        (*ppList)->pNodeHead = NULL;
        return true;
    }

    PAD_STACK();
    return false;
}

static inline bool xlListWipe(tXL_LIST* pList) {
    void* pNode;
    void* pNodeNext;

    pNode = pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = NODE_NEXT(pNode);
        if (!xlHeapFree(&pNode)) {
            return false;
        }
        pNode = pNodeNext;
    }

    pList->nItemCount = 0;
    pList->pNodeNext = NULL;
    pList->pNodeHead = NULL;
    return true;
}

bool xlListFree(tXL_LIST** ppList) {
    if (!xlListWipe(*ppList)) {
        return false;
    }

    if (!xlListFreeItem(&gListList, (void**)ppList)) {
        return false;
    }

    return true;
}

bool xlListMakeItem(tXL_LIST* pList, void** ppItem) {
    s32 nSize;
    void* pListNode;
    void* pNode;
    void* pNodeNext;

    nSize = pList->nItemSize + 4;
    if (!xlHeapTake(&pListNode, nSize)) {
        return false;
    }

    NODE_NEXT(pListNode) = NULL;
    *ppItem = NODE_DATA(pListNode);
    pNode = &pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = NODE_NEXT(pNode);
        if (pNodeNext == NULL) {
            NODE_NEXT(pNode) = pListNode;
            pList->nItemCount++;
            return true;
        }
        pNode = pNodeNext;
    }

    return false;
}

bool xlListFreeItem(tXL_LIST* pList, void** ppItem) {
    void* pNode;
    void* pNodeNext;

    if (pList->pNodeHead == NULL) {
        return false;
    }

    pNode = &pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = NODE_NEXT(pNode);
        if (*ppItem == NODE_DATA(pNodeNext)) {
            NODE_NEXT(pNode) = NODE_NEXT(pNodeNext);
            *ppItem = NULL;
            if (!xlHeapFree(&pNodeNext)) {
                return false;
            }
            pList->nItemCount--;
            return true;
        }
        pNode = pNodeNext;
    }

    NO_INLINE();
    return false;
}

static inline bool xlListTest(tXL_LIST* pList) {
    void* pNode;

    if (pList == &gListList) {
        return true;
    }

    pNode = gListList.pNodeHead;
    while (pNode != NULL) {
        if (pList == (tXL_LIST*)NODE_DATA(pNode)) {
            return true;
        }
        pNode = NODE_NEXT(pNode);
    }

    return false;
}

bool xlListTestItem(tXL_LIST* pList, void* pItem) {
    void* pListNode;

    if (!xlListTest(pList) || pItem == NULL) {
        return false;
    }

    pListNode = pList->pNodeHead;
    while (pListNode != NULL) {
        if (pItem == NODE_DATA(pListNode)) {
            return true;
        }
        pListNode = NODE_NEXT(pListNode);
    }

    return false;
}

bool xlListSetup(void) {
    gListList.nItemCount = 0;
    gListList.nItemSize = sizeof(tXL_LIST);
    gListList.pNodeNext = NULL;
    gListList.pNodeHead = NULL;
    return true;
}

bool xlListReset(void) { return true; }
