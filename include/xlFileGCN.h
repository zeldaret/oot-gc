#ifndef _XL_FILE_GCN_H
#define _XL_FILE_GCN_H

// size: 0x20
typedef struct DVDDiskID {
    char gameName[4]; // 0x0
    char company[2]; // 0x4
    unsigned char diskNumber; // 0x6
    unsigned char gameVersion; // 0x7
    unsigned char streaming; // 0x8
    unsigned char streamingBufSize; // 0x9
    unsigned char padding[22]; // 0xA
} DVDDiskID;

typedef struct DVDCommandBlock DVDCommandBlock;

// size: 0x30
struct DVDCommandBlock {
    DVDCommandBlock* next; // 0x0
    DVDCommandBlock* prev; // 0x4
    unsigned long command; // 0x8
    long state; // 0xC
    unsigned long offset; // 0x10
    unsigned long length; // 0x14
    void* addr; // 0x18
    unsigned long currTransferSize; // 0x1C
    unsigned long transferredSize; // 0x20
    DVDDiskID* id; // 0x24
    void (*callback)(long /* unknown0 */, DVDCommandBlock* /* unknown1 */); // 0x28
    void* userData; // 0x2C
};

typedef struct DVDFileInfo DVDFileInfo;

// size: 0x3C
struct DVDFileInfo {
    DVDCommandBlock cb; // 0x0
    unsigned long startAddr; // 0x30
    unsigned long length; // 0x34
    void (*callback)(long /* unknown0 */, DVDFileInfo* /* unknown1 */); // 0x38
};

typedef enum __anon_0x2757 {
    XLFT_NONE = -1,
    XLFT_TEXT = 0,
    XLFT_BINARY = 1
} __anon_0x2757;

// size: 0x58
typedef struct tXL_FILE {
    int iBuffer; // 0x0
    void* pData; // 0x4
    void* pBuffer; // 0x8
    int nAttributes; // 0xC
    int nSize; // 0x10
    int nOffset; // 0x14
    __anon_0x2757 eType; // 0x18
    DVDFileInfo info; // 0x1C
} tXL_FILE;

int xlFileEvent(tXL_FILE* pFile, int nEvent);
int xlFileSetPosition(tXL_FILE* pFile, int nOffset);
int xlFileGet(tXL_FILE* pFile, void* pTarget, int nSizeBytes);
int xlFileClose(tXL_FILE** ppFile);
int xlFileOpen(tXL_FILE** ppFile, __anon_0x2757 eType, char* szFileName);
int xlFileGetSize(int* pnSize, char* szFileName);
int xlFileSetRead(int (*pfRead)(DVDFileInfo* /* unknown0 */, void* /* unknown1 */, int /* unknown2 */,
                                int /* unknown3 */,
                                void (* /* unknown4 */)(long /* unknown0 */, DVDFileInfo* /* unknown1 */)));
int xlFileSetOpen(int (*pfOpen)(char* /* unknown0 */, DVDFileInfo* /* unknown1 */));

#endif
