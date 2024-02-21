/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Core\xlObject.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80007BC0 -> 0x80007F80
*/

#include "dolphin/types.h"

typedef struct tXL_LIST {
    /* 0x0 */ s32 nItemSize;
    /* 0x4 */ s32 nItemCount;
    /* 0x8 */ void* pNodeHead;
    /* 0xC */ void* pNodeNext;
} __anon_0x4E6F; // size = 0x10

// size = 0x4, address = 0x801355C8
static struct tXL_LIST* gpListData;

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x4F98; // size = 0x10

typedef struct __anon_0x5062 {
    /* 0x0 */ struct tXL_LIST* pList;
    /* 0x4 */ struct _XL_OBJECTTYPE* pType;
} __anon_0x5062; // size = 0x8

// Erased
static s32 xlObjectFindData(struct __anon_0x5062** ppData, struct _XL_OBJECTTYPE* pType) {
    // Parameters
    // struct __anon_0x5062** ppData; // r1+0x0
    // struct _XL_OBJECTTYPE* pType; // r1+0x4

    // Local variables
    void* pListNode; // r6

    // References
    // -> static struct tXL_LIST* gpListData;
}

// Erased
static s32 xlObjectMakeData(struct __anon_0x5062** ppData, struct _XL_OBJECTTYPE* pType) {
    // Parameters
    // struct __anon_0x5062** ppData; // r30
    // struct _XL_OBJECTTYPE* pType; // r31

    // References
    // -> static struct tXL_LIST* gpListData;
}

// Range: 0x80007E24 -> 0x80007F80
s32 xlObjectMake(void* ppObject, void* pArgument, struct _XL_OBJECTTYPE* pType) {
    // Parameters
    // void* ppObject; // r28
    // void* pArgument; // r29
    // struct _XL_OBJECTTYPE* pType; // r30

    // Local variables
    s32 bFlag; // r31
    struct __anon_0x5062* pData; // r1+0x14

    // References
    // -> static struct tXL_LIST* gpListData;
}

// Range: 0x80007D8C -> 0x80007E24
s32 xlObjectFree(void* ppObject) {
    // Parameters
    // void* ppObject; // r30

    // Local variables
    struct __anon_0x5062* pData; // r31
}

// Range: 0x80007D24 -> 0x80007D8C
s32 xlObjectTest(void* pObject, struct _XL_OBJECTTYPE* pType) {
    // Parameters
    // void* pObject; // r1+0x8
    // struct _XL_OBJECTTYPE* pType; // r30

    // Local variables
    struct __anon_0x5062* pData; // r31

    // References
    // -> static struct tXL_LIST* gpListData;
}

// Erased
static s32 xlObjectFindType(void* pObject, struct _XL_OBJECTTYPE** ppType) {
    // Parameters
    // void* pObject; // r1+0x8
    // struct _XL_OBJECTTYPE** ppType; // r30

    // Local variables
    struct __anon_0x5062* pData; // r31

    // References
    // -> static struct tXL_LIST* gpListData;
}

// Range: 0x80007C6C -> 0x80007D24
s32 xlObjectEvent(void* pObject, s32 nEvent, void* pArgument) {
    // Parameters
    // void* pObject; // r26
    // s32 nEvent; // r27
    // void* pArgument; // r28

    // Local variables
    struct __anon_0x5062* pData; // r29

    // References
    // -> static struct tXL_LIST* gpListData;
}

// Range: 0x80007C30 -> 0x80007C6C
s32 xlObjectSetup() {
    // References
    // -> static struct tXL_LIST* gpListData;
}

// Range: 0x80007BC0 -> 0x80007C30
s32 xlObjectReset() {
    // Local variables
    struct __anon_0x5062* pData; // r3
    void* pListNode; // r31

    // References
    // -> static struct tXL_LIST* gpListData;
}
