#include "emulator/xlList.h"
#include "dolphin.h"
#include "emulator/xlHeap.h"
#include "macros.h"

static tXL_LIST gListList;

bool xlListMake(tXL_LIST** ppList, s32 nItemSize) {
    nItemSize = (nItemSize + 3) & ~3;

    if (xlListMakeItem(&gListList, ppList)) {
        (*ppList)->nItemCount = 0;
        (*ppList)->nItemSize = nItemSize;
        (*ppList)->pNodeNext = (void*)0;
        (*ppList)->pNodeHead = (void*)0;
        return true;
    }

    PAD_STACK();
    return false;
}

static inline bool xlListWipe(tXL_LIST* pList) {
    tXL_NODE* pNode;
    tXL_NODE* pNodeNext;

    pNode = pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = pNode->next;
        if (!xlHeapFree((void**)&pNode)) {
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
    tXL_NODE* pListNode;
    tXL_NODE* pNode;
    tXL_NODE* pNodeNext;

    nSize = pList->nItemSize + 4;
    if (!xlHeapTake((void**)&pListNode, nSize)) {
        return false;
    }

    pListNode->next = NULL;
    *ppItem = (void*)pListNode->data;
    pNode = (tXL_NODE*)&pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = pNode->next;
        if (pNodeNext == NULL) {
            pNode->next = pListNode;
            pList->nItemCount++;
            return true;
        }
        pNode = pNodeNext;
    }

    return false;
}

bool xlListFreeItem(tXL_LIST* pList, void** ppItem) {
    tXL_NODE* pNode;
    tXL_NODE* pNodeNext;

    if (pList->pNodeHead == NULL) {
        return false;
    }

    pNode = (tXL_NODE*)&pList->pNodeHead;
    while (pNode != NULL) {
        pNodeNext = pNode->next;
        if (*ppItem == (void*)pNodeNext->data) {
            pNode->next = pNodeNext->next;
            *ppItem = NULL;
            if (!xlHeapFree((void**)&pNodeNext)) {
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
    tXL_NODE* pNode;

    if (pList == &gListList) {
        return true;
    }

    pNode = gListList.pNodeHead;
    while (pNode != NULL) {
        if (pList == (tXL_LIST*)pNode->data) {
            return true;
        }
        pNode = pNode->next;
    }

    return false;
}

bool xlListTestItem(tXL_LIST* pList, void* pItem) {
    tXL_NODE* pListNode;

    if (!xlListTest(pList) || pItem == NULL) {
        return false;
    }

    pListNode = pList->pNodeHead;
    while (pListNode != NULL) {
        if (pItem == pListNode->data) {
            return true;
        }
        pListNode = pListNode->next;
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
