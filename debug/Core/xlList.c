/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Core\xlList.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80006280 -> 0x80006648
*/

#include "dolphin/types.h"

typedef struct tXL_LIST {
    /* 0x0 */ int nItemSize;
    /* 0x4 */ int nItemCount;
    /* 0x8 */ void* pNodeHead;
    /* 0xC */ void* pNodeNext;
} __anon_0x2C35; // size = 0x10

// size = 0x10, address = 0x800F3FA0
static struct tXL_LIST gListList;

// Erased
static int xlListWipe(struct tXL_LIST* pList) {
    // Parameters
    // struct tXL_LIST* pList; // r30

    // Local variables
    void* pNode; // r1+0xC
    void* pNodeNext; // r31
}

// Range: 0x80006550 -> 0x80006648
int xlListMake(struct tXL_LIST** ppList, int nItemSize) {
    // Parameters
    // struct tXL_LIST** ppList; // r31
    // int nItemSize; // r29

    // References
    // -> static struct tXL_LIST gListList;
}

// Range: 0x80006494 -> 0x80006550
int xlListFree(struct tXL_LIST** ppList) {
    // Parameters
    // struct tXL_LIST** ppList; // r29

    // References
    // -> static struct tXL_LIST gListList;
}

// Erased
static int xlListTest(struct tXL_LIST* pList) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x0

    // Local variables
    void* pNode; // r4

    // References
    // -> static struct tXL_LIST gListList;
}

// Range: 0x800063E8 -> 0x80006494
int xlListMakeItem(struct tXL_LIST* pList, void* ppItem) {
    // Parameters
    // struct tXL_LIST* pList; // r30
    // void* ppItem; // r31

    // Local variables
    int nSize; // r4
    void* pListNode; // r1+0x10
    void* pNode; // r4
    void* pNodeNext; // r1+0x8
}

// Range: 0x8000633C -> 0x800063E8
int xlListFreeItem(struct tXL_LIST* pList, void* ppItem) {
    // Parameters
    // struct tXL_LIST* pList; // r31
    // void* ppItem; // r1+0xC

    // Local variables
    void* pNode; // r6
    void* pNodeNext; // r1+0x10
}

// Range: 0x800062B0 -> 0x8000633C
int xlListTestItem(struct tXL_LIST* pList, void* pItem) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x0
    // void* pItem; // r1+0x4

    // Local variables
    void* pListNode; // r3

    // References
    // -> static struct tXL_LIST gListList;
}

// Erased
static int xlListFindItem(struct tXL_LIST* pList, int iItem, void* ppItem) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x0
    // int iItem; // r1+0x4
    // void* ppItem; // r1+0x8

    // Local variables
    int nItemCount; // r3
    void* pListNode; // r6
}

// Erased
static int xlListFindItemIndex(struct tXL_LIST* pList, int* piItem, void* pItem) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x0
    // int* piItem; // r1+0x4
    // void* pItem; // r1+0x8

    // Local variables
    int iItem; // r3
    void* pListNode; // r6
}

// Erased
static int xlListEnumerate(struct tXL_LIST* pList, int (*pfCallback)(void*)) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x8
    // int (* pfCallback)(void*); // r30

    // Local variables
    void* pNode; // r31
}

// Erased
static int xlListNodeGetHead(struct tXL_LIST* pList, void* ppListNode) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x0
    // void* ppListNode; // r1+0x4

    // References
    // -> static struct tXL_LIST gListList;
}

// Erased
static int xlListNodeGetNext(struct tXL_LIST* pList, void* ppListNode) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x0
    // void* ppListNode; // r1+0x4

    // References
    // -> static struct tXL_LIST gListList;
}

// Erased
static int xlListMoveItemToHead(struct tXL_LIST* pList, void* pItem) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x0
    // void* pItem; // r1+0x4

    // Local variables
    void* pNode; // r5
    void* pNodeLast; // r6
}

// Erased
static int xlListMoveItemToTail(struct tXL_LIST* pList, void* pItem) {
    // Parameters
    // struct tXL_LIST* pList; // r1+0x0
    // void* pItem; // r1+0x4

    // Local variables
    void* pNode; // r5
    void* pNodeLast; // r6
    void* pNodeItem; // r7
    void* pNodeItemLast; // r8
}

// Range: 0x80006288 -> 0x800062B0
int xlListSetup() {
    // References
    // -> static struct tXL_LIST gListList;
}

// Range: 0x80006280 -> 0x80006288
int xlListReset() {}
