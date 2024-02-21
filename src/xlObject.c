#include "xlObject.h"
#include "xlList.h"

static struct tXL_LIST* gpListData;

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlObject/xlObjectMake.s")
#else
#endif

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlObject/xlObjectFree.s")
#else
s32 xlObjectFree(void** ppObject) {
    __anon_0x5062* pData;

    if (ppObject != NULL) {
        if (*ppObject != NULL) {
            pData = (__anon_0x5062*)((__anon_0x5062*)*ppObject)->pList;
            pData->pType->pfEvent(pData->pType, 3, NULL);
            *ppObject = (void*)((s32)ppObject - 4);

            if (xlListFreeItem(pData->pList, ppObject) == 0) {
                return 0;
            }

            *ppObject = NULL;
            return 1;
        }
    }

    return 0;
}
#endif

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlObject/xlObjectTest.s")
#else
s32 xlObjectTest(void* pObject, _XL_OBJECTTYPE* pType) {
    __anon_0x5062* pData;

    if (pObject != NULL) {
        pData = (__anon_0x5062*)((__anon_0x5062*)pObject)->pType;

        if (xlListTestItem(gpListData, pData) && pData->pType == pType) {
            return 1;
        }
    }

    return 0;
}

#endif

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlObject/xlObjectEvent.s")
#else
s32 xlObjectEvent(void* pObject, s32 nEvent, void* pArgument) {
    s32 var_r0;
    void* temp_r29;
    void* temp_r30;
    void* temp_r31;

    if (pObject != NULL) {
        temp_r29 = pObject->unk-4;
        if (xlListTestItem(gpListData, temp_r29)) {
            temp_r30 = temp_r29->unk4;

            if ((pObject != NULL) && (temp_r31 = *(pObject - 4), ((xlListTestItem(gpListData, temp_r31) == 0) == 0)) && ((u32) temp_r31->unk4 == temp_r30)) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }

            if (var_r0 != 0) {
                return temp_r29->unk4->unkC(pObject, nEvent, pArgument);
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
