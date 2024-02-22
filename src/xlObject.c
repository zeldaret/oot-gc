#include "xlObject.h"
#include "xlList.h"

static struct tXL_LIST* gpListData;

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlObject/xlObjectMake.s")
#else
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
#ifndef NON_MATCHING
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
