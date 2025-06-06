/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Core\xlFileGCN.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80005E68 -> 0x80006280
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x19EC; // size = 0x10

// size = 0x10, address = 0x800DB7E0
struct _XL_OBJECTTYPE gTypeFile;

typedef struct DVDDiskID {
    /* 0x0 */ char gameName[4];
    /* 0x4 */ char company[2];
    /* 0x6 */ u8 diskNumber;
    /* 0x7 */ u8 gameVersion;
    /* 0x8 */ u8 streaming;
    /* 0x9 */ u8 streamingBufSize;
    /* 0xA */ u8 padding[22];
} __anon_0x1B3D; // size = 0x20

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
} __anon_0x1CAD; // size = 0x30

typedef struct DVDFileInfo {
    /* 0x00 */ struct DVDCommandBlock cb;
    /* 0x30 */ u32 startAddr;
    /* 0x34 */ u32 length;
    /* 0x38 */ void (*callback)(s32, struct DVDFileInfo*);
} __anon_0x1ED3; // size = 0x3C

// size = 0x4, address = 0x801355A0
static int (*gpfOpen)(char*, struct DVDFileInfo*);

// size = 0x4, address = 0x801355A4
static int (*gpfRead)(struct DVDFileInfo*, void*, int, int, void (*)(s32, struct DVDFileInfo*));

typedef struct tXL_FILE {
    /* 0x00 */ int iBuffer;
    /* 0x04 */ void* pData;
    /* 0x08 */ void* pBuffer;
    /* 0x0C */ int nAttributes;
    /* 0x10 */ int nSize;
    /* 0x14 */ int nOffset;
    /* 0x18 */ enum __anon_0x2757 eType;
    /* 0x1C */ struct DVDFileInfo info;
} __anon_0x2085; // size = 0x58

typedef enum __anon_0x2757 {
    XLFT_NONE = -1,
    XLFT_TEXT = 0,
    XLFT_BINARY = 1,
} __anon_0x2757;

// Range: 0x80006274 -> 0x80006280
int xlFileSetOpen(int (*pfOpen)(char*, struct DVDFileInfo*)) {
    // Parameters
    // int (* pfOpen)(char*, struct DVDFileInfo*); // r1+0x0

    // References
    // -> static int (* gpfOpen)(char*, struct DVDFileInfo*);
}

// Range: 0x80006268 -> 0x80006274
int xlFileSetRead(int (*pfRead)(struct DVDFileInfo*, void*, int, int, void (*)(s32, struct DVDFileInfo*))) {
    // Parameters
    // int (* pfRead)(struct DVDFileInfo*, void*, int, int, void (*)(s32, struct DVDFileInfo*)); // r1+0x0

    // References
    // -> static int (* gpfRead)(struct DVDFileInfo*, void*, int, int, void (*)(s32, struct DVDFileInfo*));
}

// Range: 0x8000614C -> 0x80006268
int xlFileGetSize(int* pnSize, char* szFileName) {
    // Parameters
    // int* pnSize; // r31
    // char* szFileName; // r30

    // Local variables
    struct tXL_FILE* pFile; // r1+0x10

    // References
    // -> static int (* gpfOpen)(char*, struct DVDFileInfo*);
    // -> struct _XL_OBJECTTYPE gTypeFile;
}

// Erased
static int xlFileLoad(char* szFileName, void* ppBuffer) {
    // Parameters
    // char* szFileName; // r30
    // void* ppBuffer; // r31

    // Local variables
    int nSize; // r1+0x18
    struct tXL_FILE* pFile; // r1+0x14

    // References
    // -> static int (* gpfOpen)(char*, struct DVDFileInfo*);
    // -> struct _XL_OBJECTTYPE gTypeFile;
}

// Range: 0x80006078 -> 0x8000614C
int xlFileOpen(struct tXL_FILE** ppFile, enum __anon_0x2757 eType, char* szFileName) {
    // Parameters
    // struct tXL_FILE** ppFile; // r29
    // enum __anon_0x2757 eType; // r30
    // char* szFileName; // r31

    // Local variables
    int nStatus; // r3

    // References
    // -> static int (* gpfOpen)(char*, struct DVDFileInfo*);
    // -> struct _XL_OBJECTTYPE gTypeFile;
}

// Erased
static int xlFileCreate() {}

// Range: 0x80006044 -> 0x80006078
int xlFileClose(struct tXL_FILE** ppFile) {
    // Parameters
    // struct tXL_FILE** ppFile; // r3
}

// Range: 0x80005F40 -> 0x80006044
int xlFileGet(struct tXL_FILE* pFile, void* pTarget, int nSizeBytes) {
    // Parameters
    // struct tXL_FILE* pFile; // r27
    // void* pTarget; // r28
    // int nSizeBytes; // r29

    // Local variables
    int nOffset; // r6
    int nOffsetExtra; // r1+0x8
    int nSize; // r5
    int nSizeUsed; // r30

    // References
    // -> static int (* gpfRead)(struct DVDFileInfo*, void*, int, int, void (*)(s32, struct DVDFileInfo*));
}

// Erased
static int xlFileGetFlip(struct tXL_FILE* pFile, void* pTarget, int nSizeBytes) {
    // Parameters
    // struct tXL_FILE* pFile; // r30
    // void* pTarget; // r31
    // int nSizeBytes; // r1+0x10
}

// Erased
static int xlFileGetLine(struct tXL_FILE* pFile, char* acLine, int nSizeLine) {
    // Parameters
    // struct tXL_FILE* pFile; // r28
    // char* acLine; // r29
    // int nSizeLine; // r30

    // Local variables
    int iCharacter; // r31
    char nCharacter; // r1+0x14
}

// Erased
static int xlFilePut() {}

// Erased
static int xlFilePutFlip(int nSizeBytes) {
    // Parameters
    // int nSizeBytes; // r1+0x8
}

// Erased
static int xlFilePutLine() {}

// Range: 0x80005F18 -> 0x80005F40
int xlFileSetPosition(struct tXL_FILE* pFile, int nOffset) {
    // Parameters
    // struct tXL_FILE* pFile; // r1+0x0
    // int nOffset; // r1+0x4
}

// Erased
static int xlFileGetPosition(struct tXL_FILE* pFile, int* pnOffset) {
    // Parameters
    // struct tXL_FILE* pFile; // r1+0x0
    // int* pnOffset; // r1+0x4
}

// Range: 0x80005E68 -> 0x80005F18
int xlFileEvent(struct tXL_FILE* pFile, int nEvent) {
    // Parameters
    // struct tXL_FILE* pFile; // r31
    // int nEvent; // r1+0xC
}
