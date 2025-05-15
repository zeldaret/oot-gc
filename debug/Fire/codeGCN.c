/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\codeGCN.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8001C444 -> 0x8001C498
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x1F88E; // size = 0x10

// size = 0x10, address = 0x800EA7C8
struct _XL_OBJECTTYPE gClassCode;

typedef enum __anon_0x1F980 {
    XLFT_NONE = -1,
    XLFT_TEXT = 0,
    XLFT_BINARY = 1,
} __anon_0x1F980;

typedef struct DVDDiskID {
    /* 0x0 */ char gameName[4];
    /* 0x4 */ char company[2];
    /* 0x6 */ u8 diskNumber;
    /* 0x7 */ u8 gameVersion;
    /* 0x8 */ u8 streaming;
    /* 0x9 */ u8 streamingBufSize;
    /* 0xA */ u8 padding[22];
} __anon_0x1FA38; // size = 0x20

typedef struct DVDCommandBlock {
    /* 0x00 */ struct DVDCommandBlock* next;
    /* 0x04 */ struct DVDCommandBlock* prev;
    /* 0x08 */ u32 command;
    /* 0x0C */ s32 state;
    /* 0x10 */ u32 offset;
    /* 0x14 */ u32 length;
    /* 0x18 */ void* addr;
    /* 0x1C */ u32 currTransferSize;
    /* 0x20 */ u32 transferredSize;
    /* 0x24 */ struct DVDDiskID* id;
    /* 0x28 */ void (*callback)(s32, struct DVDCommandBlock*);
    /* 0x2C */ void* userData;
} __anon_0x1FBA8; // size = 0x30

typedef struct DVDFileInfo {
    /* 0x00 */ struct DVDCommandBlock cb;
    /* 0x30 */ u32 startAddr;
    /* 0x34 */ u32 length;
    /* 0x38 */ void (*callback)(s32, struct DVDFileInfo*);
} __anon_0x1FDCE; // size = 0x3C

typedef struct tXL_FILE {
    /* 0x00 */ int iBuffer;
    /* 0x04 */ void* pData;
    /* 0x08 */ void* pBuffer;
    /* 0x0C */ int nAttributes;
    /* 0x10 */ int nSize;
    /* 0x14 */ int nOffset;
    /* 0x18 */ enum __anon_0x1F980 eType;
    /* 0x1C */ struct DVDFileInfo info;
} __anon_0x1FE86; // size = 0x58

// size = 0x4, address = 0x80135680
static void* gpBufferFunction;

// size = 0x4, address = 0x80135684
static unsigned int* ganDataCode;

typedef struct _CODE_CACHE_NODE {
    /* 0x0 */ int checksum;
    /* 0x4 */ int length;
    /* 0x8 */ struct _CODE_CACHE_NODE* next;
    /* 0xC */ struct _CODE_CACHE_NODE* child;
} __anon_0x20141; // size = 0x10

// Erased
static int hioInitSend() {}

// Erased
static int hioCallbackDevice() {}

// Erased
static void hioCallback() {}

// Erased
static int hioSendBuffer() {}

// Erased
static int hioInit() {}

// Erased
static int codeSendFilePart() {}

// Erased
static int codeCheckCatalog(int nAddress0, int nAddress1) {
    // Parameters
    // int nAddress0; // r4
    // int nAddress1; // r5

    // Local variables
    int iFunction; // r1+0x8
    int instruction; // r31
    unsigned int checksum; // r1+0x14

    // References
    // -> static unsigned int gnCountFunction;
    // -> static unsigned int* ganDataCode;
    // -> static int gCatalogLoaded;
}

// Range: 0x8001C444 -> 0x8001C498
int codeEvent(int nEvent) {
    // Parameters
    // int nEvent; // r1+0x4

    // References
    // -> static unsigned int* ganDataCode;
    // -> static void* gpBufferFunction;
}
