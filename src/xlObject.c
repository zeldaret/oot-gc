#include "xlObject.h"
#include "xlList.h"

static struct tXL_LIST* gpListData;

#ifdef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlObject/xlObjectMake.s")
#else
inline s32 xlObjectFindClass(__anon_0x5062** ppData, _XL_OBJECTTYPE* pType) {
    tXL_NODE* pNode;
    for (pNode = (tXL_NODE*)gpListData->pNodeHead; pNode != NULL; pNode = pNode->next) {
        *ppData = (__anon_0x5062*)pNode->data;
        if ((*ppData)->pType == pType) {
            return 1;
        }
    }
    return 0;
}

inline s32 xlObjectNewClass(__anon_0x5062** ppData, _XL_OBJECTTYPE* pType) {
    if (!xlListMakeItem(gpListData, ppData)) {
        return 0;
    }

    (*ppData)->pType = pType;

    if (!xlListMake((tXL_LIST**)*ppData, pType->nSizeObject + 4)) {
        return 0;
    }

    return 1;
}

s32 xlObjectMake(void** ppObject, void* pArgument, _XL_OBJECTTYPE* pType) {
    s32 bFlag;
    __anon_0x5062* pData;

    if (!xlObjectFindClass(&pData, pType)) {
        if (!xlObjectNewClass(&pData, pType)) {
            return 0;
        }
        bFlag = 1;
    } else {
        bFlag = 0;
    }

    if (!xlListMakeItem(pData->pList, ppObject)) {
        return 0;
    }

    ((tXL_NODE*)ppObject)->next = (tXL_NODE*)pData;
    *ppObject = (*((tXL_NODE**)ppObject))->data;

    if (bFlag != 0) {
        pType->pfEvent(*ppObject, 0, NULL);
    }

    return pType->pfEvent(*ppObject, 2, pArgument);
}
#endif

s32 xlObjectFree(void** ppObject) {
    if (ppObject != NULL && *ppObject != NULL) {
        __anon_0x5062* pData = *(__anon_0x5062**)((u8*)*ppObject - 4);

        pData->pType->pfEvent(*ppObject, 3, NULL);
        *ppObject = (void*)((u8*)*ppObject - 4);

        if (xlListFreeItem(pData->pList, ppObject) == 0) {
            return 0;
        }

        *ppObject = NULL;
        return 1;
    }

    return 0;
}

s32 xlObjectTest(void* pObject, _XL_OBJECTTYPE* pType) {
    __anon_0x5062* pData;

    if (pObject != NULL) {
        pData = *(__anon_0x5062**)((u8*)pObject - 4);

        if (xlListTestItem(gpListData, pData) && pData->pType == pType) {
            return 1;
        }
    }

    return 0;
}

// regalloc
#ifdef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlObject/xlObjectEvent.s")
#else
inline s32 xlObjectTestClass(void* pObject, __anon_0x5062* pData2) {
    __anon_0x5062* pData;
    tXL_LIST* pList = pData2->pList;

    if (pObject != NULL) {
        pData = *(__anon_0x5062**)((u8*)pObject - 4);
        if (xlListTestItem(gpListData, pData)) {
            if (pData->pList == pList) {
                return 1;
            }
        }
    }

    return 0;
}

s32 xlObjectEvent(void* pObject, s32 nEvent, void* pArgument) {
    if (pObject != NULL) {
        __anon_0x5062* pData = *(__anon_0x5062**)((u8*)pObject - 4);

        if (xlListTestItem(gpListData, pData)) {
            if (xlObjectTestClass(pObject, pData)) {
                return pData->pType->pfEvent(pObject, nEvent, pArgument);
            }
        }
    }

    return 0;
}
#endif

s32 xlObjectSetup(void) {
    if (!xlListMake(&gpListData, 8)) {
        return 0;
    }

    return 1;
}

s32 xlObjectReset(void) {
    void* pListNode;

    pListNode = gpListData->pNodeHead;

    while (pListNode != NULL) {
        if (!xlListFree((void*)((s8*)pListNode + 4))) {
            return 0;
        }
        pListNode = ((tXL_NODE*)pListNode)->next;
    }

    if (!xlListFree(&gpListData)) {
        return 0;
    }

    return 1;
}
