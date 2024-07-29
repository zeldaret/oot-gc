#include "emulator/xlObject.h"
#include "emulator/xlList.h"

static tXL_LIST* gpListData;

static inline bool xlObjectFindData(__anon_0x5062** ppData, _XL_OBJECTTYPE* pType) {
    void* pListNode;

    for (pListNode = gpListData->pNodeHead; pListNode != NULL; pListNode = NODE_NEXT(pListNode)) {
        *ppData = (__anon_0x5062*)NODE_DATA(pListNode);
        if ((*ppData)->pType == pType) {
            return true;
        }
    }

    return false;
}

static inline bool xlObjectMakeData(__anon_0x5062** ppData, _XL_OBJECTTYPE* pType) {
    if (!xlListMakeItem(gpListData, (void**)ppData)) {
        return false;
    }

    (*ppData)->pType = pType;

    if (!xlListMake((tXL_LIST**)*ppData, pType->nSizeObject + 4)) {
        return false;
    }

    return true;
}

bool xlObjectMake(void** ppObject, void* pArgument, _XL_OBJECTTYPE* pType) {
    bool bFlag;
    __anon_0x5062* pData;
    void* temp1;
    void* temp2;

    if (!xlObjectFindData(&pData, pType)) {
        if (!xlObjectMakeData(&pData, pType)) {
            return false;
        }
        bFlag = true;
    } else {
        bFlag = false;
    }

    if (!xlListMakeItem(pData->pList, ppObject)) {
        return false;
    }

    temp1 = *ppObject;
    temp2 = pData;
    *ppObject = ((u8*)*ppObject + 4);
    NODE_NEXT(temp1) = temp2;

    if (bFlag) {
        pType->pfEvent(*ppObject, 0, NULL);
    }

    return pType->pfEvent(*ppObject, 2, pArgument);
}

bool xlObjectFree(void** ppObject) {
    if (ppObject != NULL && *ppObject != NULL) {
        __anon_0x5062* pData = *(__anon_0x5062**)((u8*)*ppObject - 4);

        pData->pType->pfEvent(*ppObject, 3, NULL);
        *ppObject = ((u8*)*ppObject - 4);

        if (xlListFreeItem(pData->pList, ppObject) == 0) {
            return false;
        }

        *ppObject = NULL;
        return true;
    }

    return false;
}

bool xlObjectTest(void* pObject, _XL_OBJECTTYPE* pType) {
    __anon_0x5062* pData;

    if (pObject != NULL) {
        pData = *(__anon_0x5062**)((u8*)pObject - 4);

        if (xlListTestItem(gpListData, pData) && pData->pType == pType) {
            return true;
        }
    }

    return false;
}

static inline bool xlObjectFindType(void* pObject, _XL_OBJECTTYPE* pType) {
    if (pObject != NULL) {
        __anon_0x5062* pData = *(__anon_0x5062**)((u8*)pObject - 4);
        if (xlListTestItem(gpListData, pData)) {
            if (pData->pType == pType) {
                return true;
            }
        }
    }

    return false;
}

bool xlObjectEvent(void* pObject, s32 nEvent, void* pArgument) {
    if (pObject != NULL) {
        __anon_0x5062* pData = *(__anon_0x5062**)((u8*)pObject - 4);

        if (xlListTestItem(gpListData, pData)) {
            if (xlObjectFindType(pObject, pData->pType)) {
                return pData->pType->pfEvent(pObject, nEvent, pArgument);
            }
        }
    }

    return false;
}

bool xlObjectSetup(void) {
    if (!xlListMake(&gpListData, 8)) {
        return false;
    }

    return true;
}

bool xlObjectReset(void) {
    void* pListNode;

    pListNode = gpListData->pNodeHead;

    while (pListNode != NULL) {
        if (!xlListFree((void*)((u8*)pListNode + 4))) {
            return false;
        }
        pListNode = NODE_NEXT(pListNode);
    }

    if (!xlListFree(&gpListData)) {
        return false;
    }

    return true;
}
