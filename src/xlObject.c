#include "xlObject.h"
#include "xlList.h"

static tXL_LIST* gpListData;

inline s32 xlObjectFindData(__anon_0x5062** ppData, _XL_OBJECTTYPE* pType) {
    tXL_NODE* pListNode;

    for (pListNode = (tXL_NODE*)gpListData->pNodeHead; pListNode != NULL; pListNode = pListNode->next) {
        *ppData = (__anon_0x5062*)pListNode->data;
        if ((*ppData)->pType == pType) {
            return 1;
        }
    }

    return 0;
}

inline s32 xlObjectMakeData(__anon_0x5062** ppData, _XL_OBJECTTYPE* pType) {
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
    tXL_NODE* temp1;
    tXL_NODE* temp2;

    if (!xlObjectFindData(&pData, pType)) {
        if (!xlObjectMakeData(&pData, pType)) {
            return 0;
        }
        bFlag = 1;
    } else {
        bFlag = 0;
    }

    if (!xlListMakeItem(pData->pList, ppObject)) {
        return 0;
    }

    temp1 = (tXL_NODE*)*ppObject;
    temp2 = (tXL_NODE*)pData;
    *ppObject = &temp1->data;
    temp1->next = temp2;

    if (bFlag != 0) {
        pType->pfEvent(*ppObject, 0, NULL);
    }

    return pType->pfEvent(*ppObject, 2, pArgument);
}

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

inline s32 xlObjectFindType(void* pObject, _XL_OBJECTTYPE* pType) {
    if (pObject != NULL) {
        __anon_0x5062* pData = *(__anon_0x5062**)((u8*)pObject - 4);
        if (xlListTestItem(gpListData, pData)) {
            if (pData->pType == pType) {
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
            if (xlObjectFindType(pObject, pData->pType)) {
                return pData->pType->pfEvent(pObject, nEvent, pArgument);
            }
        }
    }

    return 0;
}

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
