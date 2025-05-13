/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\cpu.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80030E70 -> 0x80036870
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x3CBBE; // size = 0x10

// size = 0x10, address = 0x800EB658
struct _XL_OBJECTTYPE gClassCPU;

// size = 0x80, address = 0x800EB668
static char* gaszNameGPR[32];

// size = 0x80, address = 0x800EB6E8
static char* gaszNameFPR[32];

// size = 0x80, address = 0x800EB850
static char* gaszNameCP0[32];

// size = 0x80, address = 0x800EBB04
static char* gaszNameCP1[32];

// size = 0x100, address = 0x800EBB88
static s64 ganMaskGetCP0[32];

// size = 0x100, address = 0x800EBC88
static s64 ganMaskSetCP0[32];

// size = 0x40, address = 0x800EBD88
static u8 Opcode[64];

// size = 0x40, address = 0x800EBDC8
static u8 SpecialOpcode[64];

// size = 0x20, address = 0x800EBE08
static u8 RegimmOpcode[32];

// size = 0x4, address = 0x801356E0
void* gHeapTree;

// size = 0x14, address = 0x800EBE28
static unsigned int ganOpcodeSaveFP1[5];

// size = 0x14, address = 0x800EBE3C
static unsigned int ganOpcodeSaveFP2_0[5];

// size = 0xC, address = 0x800EBE50
static unsigned int ganOpcodeSaveFP2_1[3];

// size = 0x14, address = 0x800EBE5C
static unsigned int ganOpcodeLoadFP[5];

// size = 0x80, address = 0x800EBE70
int ganMapGPR[32];

// size = 0x4, address = 0x801356E4
static int cpuCompile_DSLLV_function;

// size = 0x4, address = 0x801356E8
static int cpuCompile_DSRLV_function;

// size = 0x4, address = 0x801356EC
static int cpuCompile_DSRAV_function;

// size = 0x4, address = 0x801356F0
static int cpuCompile_DMULT_function;

// size = 0x4, address = 0x801356F4
static int cpuCompile_DMULTU_function;

// size = 0x4, address = 0x801356F8
static int cpuCompile_DDIV_function;

// size = 0x4, address = 0x801356FC
static int cpuCompile_DDIVU_function;

// size = 0x4, address = 0x80135700
static int cpuCompile_DADD_function;

// size = 0x4, address = 0x80135704
static int cpuCompile_DADDU_function;

// size = 0x4, address = 0x80135708
static int cpuCompile_DSUB_function;

// size = 0x4, address = 0x8013570C
static int cpuCompile_DSUBU_function;

// size = 0x4, address = 0x80135710
static int cpuCompile_S_SQRT_function;

// size = 0x4, address = 0x80135714
static int cpuCompile_D_SQRT_function;

// size = 0x4, address = 0x80135718
static int cpuCompile_W_CVT_SD_function;

// size = 0x4, address = 0x8013571C
static int cpuCompile_L_CVT_SD_function;

// size = 0x4, address = 0x80135720
static int cpuCompile_CEIL_W_function;

// size = 0x4, address = 0x80135724
static int cpuCompile_FLOOR_W_function;

// size = 0x4, address = 0x80135728
static int cpuCompile_ROUND_W_function;

// size = 0x4, address = 0x8013572C
static int cpuCompile_TRUNC_W_function;

// size = 0x4, address = 0x80135730
static int cpuCompile_LB_function;

// size = 0x4, address = 0x80135734
static int cpuCompile_LH_function;

// size = 0x4, address = 0x80135738
static int cpuCompile_LW_function;

// size = 0x4, address = 0x8013573C
static int cpuCompile_LBU_function;

// size = 0x4, address = 0x80135740
static int cpuCompile_LHU_function;

// size = 0x4, address = 0x80135744
static int cpuCompile_SB_function;

// size = 0x4, address = 0x80135748
static int cpuCompile_SH_function;

// size = 0x4, address = 0x8013574C
static int cpuCompile_SW_function;

// size = 0x4, address = 0x80135750
static int cpuCompile_LDC_function;

// size = 0x4, address = 0x80135754
static int cpuCompile_SDC_function;

// size = 0x4, address = 0x80135758
static int cpuCompile_LWL_function;

// size = 0x4, address = 0x8013575C
static int cpuCompile_LWR_function;

// size = 0x1F4, address = 0x80130A58
unsigned int aHeapTreeFlag[125];

typedef enum __anon_0x3D79A {
    SM_NONE = -1,
    SM_RUNNING = 0,
    SM_STOPPED = 1,
} __anon_0x3D79A;

typedef struct __anon_0x3D7FC {
    /* 0x0 */ int nSize;
    /* 0x4 */ int nOffsetRAM;
    /* 0x8 */ int nOffsetROM;
    /* 0xC */ int (*pCallback)();
} __anon_0x3D7FC; // size = 0x10

typedef enum __anon_0x3D8AD {
    SRT_NONE = -1,
    SRT_MARIO = 0,
    SRT_WAVERACE = 1,
    SRT_MARIOKART = 2,
    SRT_STARFOX = 3,
    SRT_ZELDA1 = 4,
    SRT_ZELDA2 = 5,
    SRT_1080 = 6,
    SRT_PANEL = 7,
    SRT_MARIOPARTY1 = 8,
    SRT_MARIOPARTY2 = 9,
    SRT_MARIOPARTY3 = 10,
    SRT_DRMARIO = 11,
    SRT_UNKNOWN = 12,
} __anon_0x3D8AD;

typedef enum __anon_0x3D9D9 {
    SOT_NONE = -1,
    SOT_CPU = 0,
    SOT_PIF = 1,
    SOT_RAM = 2,
    SOT_ROM = 3,
    SOT_RSP = 4,
    SOT_RDP = 5,
    SOT_MIPS = 6,
    SOT_DISK = 7,
    SOT_FLASH = 8,
    SOT_SRAM = 9,
    SOT_AUDIO = 10,
    SOT_VIDEO = 11,
    SOT_SERIAL = 12,
    SOT_LIBRARY = 13,
    SOT_PERIPHERAL = 14,
    SOT_RDB = 15,
    SOT_COUNT = 16,
} __anon_0x3D9D9;

typedef struct __anon_0x3DB14 {
    /* 0x00 */ void* pFrame;
    /* 0x04 */ void* pSound;
    /* 0x08 */ int bException;
    /* 0x0C */ enum __anon_0x3D79A eMode;
    /* 0x10 */ struct __anon_0x3D7FC romCopy;
    /* 0x20 */ enum __anon_0x3D8AD eTypeROM;
    /* 0x24 */ void* apObject[16];
    /* 0x68 */ u64 nAddressBreak;
    /* 0x70 */ enum __anon_0x3D9D9 storageDevice;
    /* 0x74 */ u8 anException[16];
    /* 0x84 */ int bJapaneseVersion;
} __anon_0x3DB14; // size = 0x88

// size = 0x4, address = 0x80135600
struct __anon_0x3DB14* gpSystem;

typedef struct __anon_0x3DE78 {
    /* 0x0 */ int nOffsetHost;
    /* 0x4 */ int nAddressN64;
} __anon_0x3DE78; // size = 0x8

typedef struct cpu_callerID {
    /* 0x0 */ int N64address;
    /* 0x4 */ int GCNaddress;
} __anon_0x3DEDE; // size = 0x8

typedef struct cpu_function {
    /* 0x00 */ void* pnBase;
    /* 0x04 */ void* pfCode;
    /* 0x08 */ int nCountJump;
    /* 0x0C */ struct __anon_0x3DE78* aJump;
    /* 0x10 */ int nAddress0;
    /* 0x14 */ int nAddress1;
    /* 0x18 */ struct cpu_callerID* block;
    /* 0x1C */ int callerID_total;
    /* 0x20 */ int callerID_flag;
    /* 0x24 */ unsigned int nChecksum;
    /* 0x28 */ int timeToLive;
    /* 0x2C */ int memory_size;
    /* 0x30 */ int heapID;
    /* 0x34 */ int heapWhere;
    /* 0x38 */ int treeheapWhere;
    /* 0x3C */ struct cpu_function* prev;
    /* 0x40 */ struct cpu_function* left;
    /* 0x44 */ struct cpu_function* right;
} __anon_0x3DF51; // size = 0x48

typedef union __anon_0x3E22D {
    /* 0x0 */ char _0s8;
    /* 0x1 */ char _1s8;
    /* 0x2 */ char _2s8;
    /* 0x3 */ char _3s8;
    /* 0x4 */ char _4s8;
    /* 0x5 */ char _5s8;
    /* 0x6 */ char _6s8;
    /* 0x7 */ char s8;
    /* 0x0 */ s16 _0s16;
    /* 0x2 */ s16 _1s16;
    /* 0x4 */ s16 _2s16;
    /* 0x6 */ s16 s16;
    /* 0x0 */ int _0s32;
    /* 0x4 */ int s32;
    /* 0x0 */ s64 s64;
    /* 0x0 */ u8 _0u8;
    /* 0x1 */ u8 _1u8;
    /* 0x2 */ u8 _2u8;
    /* 0x3 */ u8 _3u8;
    /* 0x4 */ u8 _4u8;
    /* 0x5 */ u8 _5u8;
    /* 0x6 */ u8 _6u8;
    /* 0x7 */ u8 u8;
    /* 0x0 */ u16 _0u16;
    /* 0x2 */ u16 _1u16;
    /* 0x4 */ u16 _2u16;
    /* 0x6 */ u16 u16;
    /* 0x0 */ unsigned int _0u32;
    /* 0x4 */ unsigned int u32;
    /* 0x0 */ u64 u64;
} __anon_0x3E22D;

typedef union __anon_0x3E641 {
    /* 0x0 */ f32 _0f32;
    /* 0x4 */ f32 f32;
    /* 0x0 */ f64 f64;
    /* 0x0 */ int _0s32;
    /* 0x4 */ int s32;
    /* 0x0 */ s64 s64;
    /* 0x0 */ unsigned int _0u32;
    /* 0x4 */ unsigned int u32;
    /* 0x0 */ u64 u64;
} __anon_0x3E641;

typedef struct __anon_0x3EB4F {
    /* 0x00 */ int nType;
    /* 0x04 */ void* pObject;
    /* 0x08 */ int nOffsetAddress;
    /* 0x0C */ int (*pfGet8)(void*, unsigned int, char*);
    /* 0x10 */ int (*pfGet16)(void*, unsigned int, s16*);
    /* 0x14 */ int (*pfGet32)(void*, unsigned int, int*);
    /* 0x18 */ int (*pfGet64)(void*, unsigned int, s64*);
    /* 0x1C */ int (*pfPut8)(void*, unsigned int, char*);
    /* 0x20 */ int (*pfPut16)(void*, unsigned int, s16*);
    /* 0x24 */ int (*pfPut32)(void*, unsigned int, int*);
    /* 0x28 */ int (*pfPut64)(void*, unsigned int, s64*);
    /* 0x2C */ unsigned int nAddressPhysical0;
    /* 0x30 */ unsigned int nAddressPhysical1;
} __anon_0x3EB4F; // size = 0x34

typedef struct cpu_treeRoot {
    /* 0x00 */ u16 total;
    /* 0x04 */ int total_memory;
    /* 0x08 */ int root_address;
    /* 0x0C */ int start_range;
    /* 0x10 */ int end_range;
    /* 0x14 */ int cache_miss;
    /* 0x18 */ int cache[20];
    /* 0x68 */ struct cpu_function* left;
    /* 0x6C */ struct cpu_function* right;
    /* 0x70 */ int kill_limit;
    /* 0x74 */ int kill_number;
    /* 0x78 */ int side;
    /* 0x7C */ struct cpu_function* restore;
    /* 0x80 */ int restore_side;
} __anon_0x3EE1D; // size = 0x84

typedef struct __anon_0x3F080 {
    /* 0x0 */ unsigned int nAddress;
    /* 0x4 */ unsigned int nOpcodeOld;
    /* 0x8 */ unsigned int nOpcodeNew;
} __anon_0x3F080; // size = 0xC

typedef struct OSContext {
    /* 0x000 */ u32 gpr[32];
    /* 0x080 */ u32 cr;
    /* 0x084 */ u32 lr;
    /* 0x088 */ u32 ctr;
    /* 0x08C */ u32 xer;
    /* 0x090 */ f64 fpr[32];
    /* 0x190 */ u32 fpscr_pad;
    /* 0x194 */ u32 fpscr;
    /* 0x198 */ u32 srr0;
    /* 0x19C */ u32 srr1;
    /* 0x1A0 */ u16 mode;
    /* 0x1A2 */ u16 state;
    /* 0x1A4 */ u32 gqr[8];
    /* 0x1C4 */ u32 psf_pad;
    /* 0x1C8 */ f64 psf[32];
} __anon_0x3F1AB; // size = 0x2C8

typedef struct OSAlarm {
    /* 0x00 */ void (*handler)(struct OSAlarm*, struct OSContext*);
    /* 0x04 */ u32 tag;
    /* 0x08 */ s64 fire;
    /* 0x10 */ struct OSAlarm* prev;
    /* 0x14 */ struct OSAlarm* next;
    /* 0x18 */ s64 period;
    /* 0x20 */ s64 start;
} __anon_0x3F402; // size = 0x28

typedef struct cpu_optimize {
    /* 0x00 */ unsigned int validCheck;
    /* 0x04 */ unsigned int destGPR_check;
    /* 0x08 */ int destGPR;
    /* 0x0C */ int destGPR_mapping;
    /* 0x10 */ unsigned int destFPR_check;
    /* 0x14 */ int destFPR;
    /* 0x18 */ unsigned int addr_check;
    /* 0x1C */ int addr_last;
    /* 0x20 */ unsigned int checkType;
    /* 0x24 */ unsigned int checkNext;
} __anon_0x3F51D; // size = 0x28

typedef struct _CPU {
    /* 0x00000 */ int nMode;
    /* 0x00004 */ int nTick;
    /* 0x00008 */ void* pHost;
    /* 0x00010 */ s64 nLo;
    /* 0x00018 */ s64 nHi;
    /* 0x00020 */ int nCountAddress;
    /* 0x00024 */ int iDeviceDefault;
    /* 0x00028 */ unsigned int nPC;
    /* 0x0002C */ unsigned int nWaitPC;
    /* 0x00030 */ unsigned int nCallLast;
    /* 0x00034 */ struct cpu_function* pFunctionLast;
    /* 0x00038 */ int nReturnAddrLast;
    /* 0x0003C */ int survivalTimer;
    /* 0x00040 */ union __anon_0x3E22D aGPR[32];
    /* 0x00140 */ union __anon_0x3E641 aFPR[32];
    /* 0x00240 */ u64 aTLB[48][5];
    /* 0x009C0 */ int anFCR[32];
    /* 0x00A40 */ s64 anCP0[32];
    /* 0x00B40 */ int (*pfStep)(struct _CPU*);
    /* 0x00B44 */ int (*pfJump)(struct _CPU*);
    /* 0x00B48 */ int (*pfCall)(struct _CPU*);
    /* 0x00B4C */ int (*pfIdle)(struct _CPU*);
    /* 0x00B50 */ int (*pfRam)(struct _CPU*);
    /* 0x00B54 */ int (*pfRamF)(struct _CPU*);
    /* 0x00B58 */ unsigned int nTickLast;
    /* 0x00B5C */ unsigned int nRetrace;
    /* 0x00B60 */ unsigned int nRetraceUsed;
    /* 0x00B64 */ struct __anon_0x3EB4F* apDevice[256];
    /* 0x00F64 */ u8 aiDevice[65536];
    /* 0x10F64 */ void* gHeap1;
    /* 0x10F68 */ void* gHeap2;
    /* 0x10F6C */ unsigned int aHeap1Flag[192];
    /* 0x1126C */ unsigned int aHeap2Flag[13];
    /* 0x112A0 */ struct cpu_treeRoot* gTree;
    /* 0x112A4 */ struct _CPU_ADDRESS aAddressCache[256];
    /* 0x11EA4 */ int nCountCodeHack;
    /* 0x11EA8 */ struct __anon_0x3F080 aCodeHack[32];
    /* 0x12028 */ s64 nTimeRetrace;
    /* 0x12030 */ struct OSAlarm alarmRetrace;
    /* 0x12058 */ unsigned int nFlagRAM;
    /* 0x1205C */ unsigned int nFlagCODE;
    /* 0x12060 */ unsigned int nCompileFlag;
    /* 0x12064 */ struct cpu_optimize nOptimize;
} __anon_0x3F6CA; // size = 0x12090

typedef struct cpu_disk_node {
    /* 0x00 */ unsigned int functionLength;
    /* 0x04 */ unsigned int checksum;
    /* 0x08 */ int startAddress;
    /* 0x0C */ int endAddress;
    /* 0x10 */ unsigned int specialFlag;
    /* 0x14 */ unsigned int frequency;
    /* 0x18 */ unsigned int inCatalog;
    /* 0x1C */ unsigned int* length;
    /* 0x20 */ unsigned int size;
    /* 0x24 */ unsigned int GCNsize;
    /* 0x28 */ unsigned int* N64code;
    /* 0x2C */ unsigned int* GCNcode;
    /* 0x30 */ struct cpu_disk_node* prev;
    /* 0x34 */ struct cpu_disk_node* left;
    /* 0x38 */ struct cpu_disk_node* right;
    /* 0x3C */ struct cpu_disk_node* same;
} __anon_0x3FE5C; // size = 0x40

typedef enum __anon_0x42F73 {
    CS_NONE = -1,
    CS_32BIT = 0,
    CS_64BIT = 1,
} __anon_0x42F73;

typedef enum __anon_0x43B0A {
    RLM_NONE = -1,
    RLM_PART = 0,
    RLM_FULL = 1,
    RLM_COUNT_ = 2,
} __anon_0x43B0A;

typedef struct __anon_0x43B69 {
    /* 0x0 */ int iCache;
    /* 0x4 */ unsigned int nSize;
    /* 0x8 */ unsigned int nTickUsed;
    /* 0xC */ char keep;
} __anon_0x43B69; // size = 0x10

typedef struct __anon_0x43C7D {
    /* 0x00 */ int bWait;
    /* 0x04 */ int (*pCallback)();
    /* 0x08 */ u8* pTarget;
    /* 0x0C */ unsigned int nSize;
    /* 0x10 */ unsigned int nOffset;
} __anon_0x43C7D; // size = 0x14

typedef struct __anon_0x43D5D {
    /* 0x00 */ int bWait;
    /* 0x04 */ int bDone;
    /* 0x08 */ int nResult;
    /* 0x0C */ u8* anData;
    /* 0x10 */ int (*pCallback)();
    /* 0x14 */ int iCache;
    /* 0x18 */ int iBlock;
    /* 0x1C */ int nOffset;
    /* 0x20 */ unsigned int nOffset0;
    /* 0x24 */ unsigned int nOffset1;
    /* 0x28 */ unsigned int nSize;
    /* 0x2C */ unsigned int nSizeRead;
} __anon_0x43D5D; // size = 0x30

typedef struct DVDDiskID {
    /* 0x0 */ char gameName[4];
    /* 0x4 */ char company[2];
    /* 0x6 */ u8 diskNumber;
    /* 0x7 */ u8 gameVersion;
    /* 0x8 */ u8 streaming;
    /* 0x9 */ u8 streamingBufSize;
    /* 0xA */ u8 padding[22];
} __anon_0x43FA8; // size = 0x20

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
} __anon_0x44118; // size = 0x30

typedef struct DVDFileInfo {
    /* 0x00 */ struct DVDCommandBlock cb;
    /* 0x30 */ u32 startAddr;
    /* 0x34 */ u32 length;
    /* 0x38 */ void (*callback)(s32, struct DVDFileInfo*);
} __anon_0x4433E; // size = 0x3C

typedef struct __anon_0x443F6 {
    /* 0x00000 */ void* pHost;
    /* 0x00004 */ void* pBuffer;
    /* 0x00008 */ int bFlip;
    /* 0x0000C */ int bLoad;
    /* 0x00010 */ char acNameFile[513];
    /* 0x00214 */ unsigned int nSize;
    /* 0x00218 */ enum __anon_0x43B0A eModeLoad;
    /* 0x0021C */ struct __anon_0x43B69 aBlock[4096];
    /* 0x1021C */ unsigned int nTick;
    /* 0x10220 */ u8* pCacheRAM;
    /* 0x10224 */ u8 anBlockCachedRAM[1024];
    /* 0x10624 */ u8 anBlockCachedARAM[2046];
    /* 0x10E24 */ struct __anon_0x43C7D copy;
    /* 0x10E38 */ struct __anon_0x43D5D load;
    /* 0x10E68 */ int nCountBlockRAM;
    /* 0x10E6C */ int nSizeCacheRAM;
    /* 0x10E70 */ u8 acHeader[64];
    /* 0x10EB0 */ unsigned int* anOffsetBlock;
    /* 0x10EB4 */ int nCountOffsetBlocks;
    /* 0x10EB8 */ struct DVDFileInfo fileInfo;
    /* 0x10EF4 */ int offsetToRom;
} __anon_0x443F6; // size = 0x10EF8

// size = 0x0, address = 0x800F3E78
int __float_nan[];

// size = 0x0, address = 0x800F3E7C
int __float_huge[];

// size = 0x4, address = 0x80134E64
f32 fTickScale;

// size = 0x4, address = 0x80134E60
unsigned int nTickMultiplier;

typedef enum __anon_0x44829 {
    RUM_NONE = 0,
    RUM_IDLE = 1,
} __anon_0x44829;

typedef enum __anon_0x44AE9 {
    CM_NONE = -1,
    CM_USER = 0,
    CM_SUPER = 1,
    CM_KERNEL = 2,
} __anon_0x44AE9;

typedef enum __anon_0x45AE1 {
    CEC_NONE = -1,
    CEC_INTERRUPT = 0,
    CEC_TLB_MODIFICATION = 1,
    CEC_TLB_LOAD = 2,
    CEC_TLB_STORE = 3,
    CEC_ADDRESS_LOAD = 4,
    CEC_ADDRESS_STORE = 5,
    CEC_BUS_INSTRUCTION = 6,
    CEC_BUS_DATA = 7,
    CEC_SYSCALL = 8,
    CEC_BREAK = 9,
    CEC_RESERVED = 10,
    CEC_COPROCESSOR = 11,
    CEC_OVERFLOW = 12,
    CEC_TRAP = 13,
    CEC_VCE_INSTRUCTION = 14,
    CEC_FLOAT = 15,
    CEC_RESERVED_16 = 16,
    CEC_RESERVED_17 = 17,
    CEC_RESERVED_18 = 18,
    CEC_RESERVED_19 = 19,
    CEC_RESERVED_20 = 20,
    CEC_RESERVED_21 = 21,
    CEC_RESERVED_22 = 22,
    CEC_WATCH = 23,
    CEC_RESERVED_24 = 24,
    CEC_RESERVED_25 = 25,
    CEC_RESERVED_26 = 26,
    CEC_RESERVED_27 = 27,
    CEC_RESERVED_28 = 28,
    CEC_RESERVED_29 = 29,
    CEC_RESERVED_30 = 30,
    CEC_VCE_DATA = 31,
    CEC_COUNT = 32,
} __anon_0x45AE1;

typedef struct _CPU_ADDRESS {
    /* 0x0 */ int nN64;
    /* 0x4 */ int nHost;
    /* 0x8 */ struct cpu_function* pFunction;
} __anon_0x45F28; // size = 0xC

// size = 0x10, address = 0x800ED6C8
struct _XL_OBJECTTYPE gClassRAM;

// Erased
static int cpuHackIdle(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8

    // Local variables
    struct __anon_0x3DB14* pSystem; // r3
}

// Erased
static int cpuHackCacheInstruction(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    unsigned int* pnCode; // r1+0x10
}

// Range: 0x80036658 -> 0x80036870
static int cpuHackHandler(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r27

    // Local variables
    unsigned int nSize; // r1+0x10
    unsigned int* pnCode; // r1+0xC
    int iCode; // r3
    int iSave1; // r30
    int iSave2; // r29
    int iLoad; // r28

    // References
    // -> static unsigned int ganOpcodeLoadFP[5];
    // -> static unsigned int ganOpcodeSaveFP2_1[3];
    // -> static unsigned int ganOpcodeSaveFP2_0[5];
    // -> static unsigned int ganOpcodeSaveFP1[5];
    // -> struct _XL_OBJECTTYPE gClassRAM;
}

// Erased
static int cpuMakeCachedAddress(struct _CPU* pCPU, int nAddressN64, int nAddressHost, struct cpu_function* pFunction) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int nAddressN64; // r1+0x4
    // int nAddressHost; // r1+0x8
    // struct cpu_function* pFunction; // r1+0xC

    // Local variables
    int iAddress; // r7
    struct _CPU_ADDRESS* aAddressCache; // r9
}

// Range: 0x800365C4 -> 0x80036658
int cpuFreeCachedAddress(struct _CPU* pCPU, int nAddress0, int nAddress1) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int nAddress0; // r1+0x4
    // int nAddress1; // r1+0x8

    // Local variables
    int iAddress; // r10
    int iAddressNext; // r11
    int nAddressN64; // r1+0x0
    struct _CPU_ADDRESS* aAddressCache; // r12
}

// Range: 0x800363E8 -> 0x800365C4
static int cpuFindCachedAddress(struct _CPU* pCPU, int nAddressN64, int* pnAddressHost) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
    // int nAddressN64; // r1+0xC
    // int* pnAddressHost; // r1+0x10

    // Local variables
    int iAddress; // r10
    struct cpu_function* pFunction; // r1+0x8
    struct _CPU_ADDRESS addressFound; // r1+0x14
    struct _CPU_ADDRESS* aAddressCache; // r6
}

// Range: 0x8003630C -> 0x800363E8
int cpuTestInterrupt(struct _CPU* pCPU, int nMaskIP) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
    // int nMaskIP; // r31
}

// Erased
static int cpuResetInterrupt(struct _CPU* pCPU, int nMaskIP) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int nMaskIP; // r1+0x4
}

// Range: 0x8003604C -> 0x8003630C
int cpuException(struct _CPU* pCPU, enum __anon_0x45AE1 eCode, int nMaskIP) {
    // Parameters
    // struct _CPU* pCPU; // r27
    // enum __anon_0x45AE1 eCode; // r28
    // int nMaskIP; // r29
}

// Range: 0x80035F3C -> 0x8003604C
static int cpuMakeDevice(struct _CPU* pCPU, int* piDevice, void* pObject, int nOffset, unsigned int nAddress0,
                         unsigned int nAddress1, int nType) {
    // Parameters
    // struct _CPU* pCPU; // r25
    // int* piDevice; // r1+0xC
    // void* pObject; // r26
    // int nOffset; // r27
    // unsigned int nAddress0; // r28
    // unsigned int nAddress1; // r29
    // int nType; // r30

    // Local variables
    struct __anon_0x3EB4F* pDevice; // r1+0x28
    int iDevice; // r31
}

// Range: 0x80035E98 -> 0x80035F3C
static int cpuFreeDevice(struct _CPU* pCPU, int iDevice) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // int iDevice; // r30

    // Local variables
    int iAddress; // r4
}

// Erased
static int cpuWipeDevices(struct _CPU* pCPU, int bFree) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // int bFree; // r29

    // Local variables
    int iDevice; // r30
}

// Range: 0x80035CD0 -> 0x80035E98
static int cpuMapAddress(struct _CPU* pCPU, int* piDevice, unsigned int nVirtual, unsigned int nPhysical, int nSize) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* piDevice; // r31
    // unsigned int nVirtual; // r28
    // unsigned int nPhysical; // r6
    // int nSize; // r29

    // Local variables
    int iDeviceTarget; // r1+0x1C
    int iDeviceSource; // r5
    unsigned int nAddressVirtual0; // r5
    unsigned int nAddressVirtual1; // r6
}

// Erased
static int cpuCountTLB(struct _CPU* pCPU, int* pnCount) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // int* pnCount; // r1+0x4

    // Local variables
    int iEntry; // r8
    int nCount; // r9
}

// Range: 0x800359EC -> 0x80035CD0
static int cpuSetTLB(struct _CPU* pCPU, int iEntry) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // int iEntry; // r1+0xC

    // Local variables
    int iDevice; // r1+0x10
    unsigned int nMask; // r1+0x8
    unsigned int nVirtual; // r27
    unsigned int nPhysical; // r30
}

// Erased
static int cpuGetTLB(struct _CPU* pCPU, int iEntry) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int iEntry; // r1+0x4
}

// Erased
static int cpuFindTLB(struct _CPU* pCPU, u64 nAddressVirtual, unsigned int* pnAddressPhysical) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // u64 nAddressVirtual; // r1+0x8
    // unsigned int* pnAddressPhysical; // r1+0x10

    // Local variables
    int iEntry; // r12
    unsigned int nMask; // r1+0x0
    unsigned int nVirtual; // r1+0x0
}

// Erased
static int cpuVirtualToPhysical_User32(struct _CPU* pCPU, u64 nAddressVirtual, unsigned int* pnAddressPhysical) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // u64 nAddressVirtual; // r1+0x8
    // unsigned int* pnAddressPhysical; // r1+0x10
}

// Erased
static int cpuVirtualToPhysical_User64(struct _CPU* pCPU, u64 nAddressVirtual, unsigned int* pnAddressPhysical) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // u64 nAddressVirtual; // r1+0x8
    // unsigned int* pnAddressPhysical; // r1+0x10
}

// Erased
static int cpuVirtualToPhysical_Super32(struct _CPU* pCPU, u64 nAddressVirtual, unsigned int* pnAddressPhysical) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // u64 nAddressVirtual; // r1+0x8
    // unsigned int* pnAddressPhysical; // r1+0x10
}

// Erased
static int cpuVirtualToPhysical_Super64(struct _CPU* pCPU, u64 nAddressVirtual, unsigned int* pnAddressPhysical) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // u64 nAddressVirtual; // r1+0x8
    // unsigned int* pnAddressPhysical; // r1+0x10
}

// Erased
static int cpuVirtualToPhysical_Kernel32(struct _CPU* pCPU, u64 nAddressVirtual, unsigned int* pnAddressPhysical) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // u64 nAddressVirtual; // r1+0x8
    // unsigned int* pnAddressPhysical; // r1+0x10
}

// Erased
static int cpuVirtualToPhysical_Kernel64(struct _CPU* pCPU, u64 nAddressVirtual, unsigned int* pnAddressPhysical) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // u64 nAddressVirtual; // r30
    // unsigned int* pnAddressPhysical; // r31
}

// Range: 0x80035914 -> 0x800359EC
static int cpuGetMode(u64 nStatus, enum __anon_0x44AE9* peMode) {
    // Parameters
    // u64 nStatus; // r1+0x0
    // enum __anon_0x44AE9* peMode; // r1+0x8
}

// Range: 0x800357D0 -> 0x80035914
static int cpuGetSize(u64 nStatus, enum __anon_0x42F73* peSize, enum __anon_0x44AE9* peMode) {
    // Parameters
    // u64 nStatus; // r29
    // enum __anon_0x42F73* peSize; // r30
    // enum __anon_0x44AE9* peMode; // r31

    // Local variables
    enum __anon_0x44AE9 eMode; // r1+0x18
}

// Erased
static int cpuSetCP0_Config(struct _CPU* pCPU, unsigned int nConfig) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // unsigned int nConfig; // r1+0x4
}

// Range: 0x8003573C -> 0x800357D0
static int cpuSetCP0_Status(struct _CPU* pCPU, u64 nStatus) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // u64 nStatus; // r31

    // Local variables
    enum __anon_0x44AE9 eMode; // r1+0x28
    enum __anon_0x44AE9 eModeLast; // r1+0x24
    enum __anon_0x42F73 eSize; // r1+0x20
    enum __anon_0x42F73 eSizeLast; // r1+0x1C
}

// Range: 0x80035570 -> 0x8003573C
int cpuSetRegisterCP0(struct _CPU* pCPU, int iRegister, s64 nData) {
    // Parameters
    // struct _CPU* pCPU; // r26
    // int iRegister; // r27
    // s64 nData; // r29

    // Local variables
    int bFlag; // r30

    // References
    // -> static s64 ganMaskSetCP0[32];
}

// Range: 0x800352C8 -> 0x80035570
int cpuGetRegisterCP0(struct _CPU* pCPU, int iRegister, s64* pnData) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // int iRegister; // r1+0xC
    // s64* pnData; // r1+0x10

    // Local variables
    int bFlag; // r1+0x8

    // References
    // -> static s64 ganMaskGetCP0[32];
}

// Range: 0x8003522C -> 0x800352C8
int __cpuERET(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x80035218 -> 0x8003522C
int __cpuBreak(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Erased
static int cpuGetOpcodeText() {}

// Range: 0x80035068 -> 0x80035218
int cpuMapObject(struct _CPU* pCPU, void* pObject, unsigned int nAddress0, unsigned int nAddress1, int nType) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // void* pObject; // r27
    // unsigned int nAddress0; // r28
    // unsigned int nAddress1; // r29
    // int nType; // r30

    // Local variables
    int iDevice; // r1+0x24
    int iAddress; // r4
    unsigned int nAddressVirtual0; // r5
    unsigned int nAddressVirtual1; // r6
}

// Range: 0x80035050 -> 0x80035068
int cpuSetDeviceGet(struct __anon_0x3EB4F* pDevice, int (*pfGet8)(void*, unsigned int, char*),
                    int (*pfGet16)(void*, unsigned int, s16*), int (*pfGet32)(void*, unsigned int, int*),
                    int (*pfGet64)(void*, unsigned int, s64*)) {
    // Parameters
    // struct __anon_0x3EB4F* pDevice; // r1+0x4
    // int (* pfGet8)(void*, unsigned int, char*); // r1+0x8
    // int (* pfGet16)(void*, unsigned int, s16*); // r1+0xC
    // int (* pfGet32)(void*, unsigned int, int*); // r1+0x10
    // int (* pfGet64)(void*, unsigned int, s64*); // r1+0x14
}

// Range: 0x80035038 -> 0x80035050
int cpuSetDevicePut(struct __anon_0x3EB4F* pDevice, int (*pfPut8)(void*, unsigned int, char*),
                    int (*pfPut16)(void*, unsigned int, s16*), int (*pfPut32)(void*, unsigned int, int*),
                    int (*pfPut64)(void*, unsigned int, s64*)) {
    // Parameters
    // struct __anon_0x3EB4F* pDevice; // r1+0x4
    // int (* pfPut8)(void*, unsigned int, char*); // r1+0x8
    // int (* pfPut16)(void*, unsigned int, s16*); // r1+0xC
    // int (* pfPut32)(void*, unsigned int, int*); // r1+0x10
    // int (* pfPut64)(void*, unsigned int, s64*); // r1+0x14
}

// Range: 0x80034FCC -> 0x80035038
int cpuSetCodeHack(struct _CPU* pCPU, int nAddress, int nOpcodeOld, int nOpcodeNew) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // int nAddress; // r1+0x4
    // int nOpcodeOld; // r1+0x8
    // int nOpcodeNew; // r1+0xC

    // Local variables
    int iHack; // r9
}

// Range: 0x80034AE8 -> 0x80034FCC
int cpuReset(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int iRegister; // r1+0x8
    int iTLB; // r1+0x8

    // References
    // -> void* gHeapTree;
    // -> unsigned int aHeapTreeFlag[125];
}

// Erased
static int cpuGetXPC(struct _CPU* pCPU, signed int* pnPC, signed int* pnLo, signed int* pnHi) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // signed int* pnPC; // r29
    // signed int* pnLo; // r30
    // signed int* pnHi; // r31

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Erased
static int cpuGetGPR(struct _CPU* pCPU, signed int* anRegister) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // signed int* anRegister; // r31

    // Local variables
    int iRegister; // r1+0x8
    enum __anon_0x42F73 eSize; // r1+0x18

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Erased
static int cpuGetCP0(struct _CPU* pCPU, signed int* anRegister) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // signed int* anRegister; // r31

    // Local variables
    int iRegister; // r1+0x8

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Erased
static int cpuGetFPR(struct _CPU* pCPU, f64* arRegister, int bDouble) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // f64* arRegister; // r30
    // int bDouble; // r31

    // Local variables
    int iRegister; // r1+0x8

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Erased
static int cpuGetFCR(struct _CPU* pCPU, int* anRegister) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* anRegister; // r31

    // Local variables
    int iRegister; // r1+0x8

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Range: 0x80034A6C -> 0x80034AE8
int cpuSetXPC(struct _CPU* pCPU, s64 nPC, s64 nLo, s64 nHi) {
    // Parameters
    // struct _CPU* pCPU; // r26
    // s64 nPC; // r0
    // s64 nLo; // r29
    // s64 nHi; // r31

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Erased
static int cpuSetGPR(struct _CPU* pCPU, signed int* anRegister) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // signed int* anRegister; // r31

    // Local variables
    int iRegister; // r1+0x8
    enum __anon_0x42F73 eSize; // r1+0x18

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Erased
static int cpuSetCP0(struct _CPU* pCPU, signed int* anRegister) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // signed int* anRegister; // r31

    // Local variables
    int iRegister; // r1+0x8

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Erased
static int cpuSetFPR(struct _CPU* pCPU, f64* arRegister, int bDouble) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // f64* arRegister; // r30
    // int bDouble; // r31

    // Local variables
    int iRegister; // r1+0x8

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Erased
static int cpuSetFCR(struct _CPU* pCPU, int* anRegister) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // int* anRegister; // r31

    // Local variables
    int iRegister; // r1+0x8

    // References
    // -> struct _XL_OBJECTTYPE gClassCPU;
}

// Range: 0x80034864 -> 0x80034A6C
int cpuEvent(struct _CPU* pCPU, int nEvent, void* pArgument) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // int nEvent; // r1+0xC
    // void* pArgument; // r1+0x10
}

// Range: 0x800347F8 -> 0x80034864
int cpuGetAddressOffset(struct _CPU* pCPU, int* pnOffset, unsigned int nAddress) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int* pnOffset; // r1+0x4
    // unsigned int nAddress; // r1+0x8

    // Local variables
    int iDevice; // r1+0x0
}

// Range: 0x80034780 -> 0x800347F8
int cpuGetAddressBuffer(struct _CPU* pCPU, void* ppBuffer, unsigned int nAddress) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
    // void* ppBuffer; // r4
    // unsigned int nAddress; // r5

    // Local variables
    struct __anon_0x3EB4F* pDevice; // r1+0x8
}

// Range: 0x800345F0 -> 0x80034780
int cpuGetOffsetAddress(struct _CPU* pCPU, unsigned int* anAddress, int* pnCount, unsigned int nOffset,
                        unsigned int nSize) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // unsigned int* anAddress; // r1+0xC
    // int* pnCount; // r1+0x10
    // unsigned int nOffset; // r1+0x14
    // unsigned int nSize; // r1+0x18

    // Local variables
    int iEntry; // r1+0x8
    int iAddress; // r7
    unsigned int nAddress; // r1+0x8
    unsigned int nMask; // r1+0x8
    unsigned int nSizeMapped; // r26
}

// Range: 0x80034564 -> 0x800345F0
int cpuInvalidateCache(struct _CPU* pCPU, int nAddress0, int nAddress1) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // int nAddress0; // r30
    // int nAddress1; // r31
}

// Range: 0x80034324 -> 0x80034564
int cpuGetFunctionChecksum(struct _CPU* pCPU, unsigned int* pnChecksum, struct cpu_function* pFunction) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
    // unsigned int* pnChecksum; // r30
    // struct cpu_function* pFunction; // r31

    // Local variables
    int nSize; // r10
    unsigned int* pnBuffer; // r1+0x18
    unsigned int nChecksum; // r11
    unsigned int nData; // r12
}

// Range: 0x80034288 -> 0x80034324
static int cpuHeapReset(unsigned int* array, int count) {
    // Parameters
    // unsigned int* array; // r3
    // int count; // r1+0x4

    // Local variables
    int i; // r6
}

// Range: 0x80034028 -> 0x80034288
int cpuHeapTake(void* heap, struct _CPU* pCPU, struct cpu_function* pFunction, int memory_size) {
    // Parameters
    // void* heap; // r3
    // struct _CPU* pCPU; // r1+0xC
    // struct cpu_function* pFunction; // r1+0x10
    // int memory_size; // r6

    // Local variables
    int done; // r12
    int second; // r7
    unsigned int* anPack; // r8
    int nPackCount; // r9
    int nBlockCount; // r10
    int nOffset; // r27
    int nCount; // r26
    int iPack; // r1+0x8
    unsigned int nPack; // r25
    unsigned int nMask; // r24
    unsigned int nMask0; // r23
}

// Range: 0x80033F3C -> 0x80034028
int cpuHeapFree(struct _CPU* pCPU, struct cpu_function* pFunction) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
    // struct cpu_function* pFunction; // r4

    // Local variables
    unsigned int* anPack; // r8
    int iPack; // r1+0x8
    unsigned int nMask; // r6
}

// Range: 0x80033E88 -> 0x80033F3C
static int cpuTreeTake(void* heap, int* where) {
    // Parameters
    // void* heap; // r1+0x0
    // int* where; // r1+0x4

    // Local variables
    int done; // r5
    int nOffset; // r8
    int nCount; // r1+0x0
    int iPack; // r1+0x0
    unsigned int nPack; // r9
    unsigned int nMask; // r10
    unsigned int nMask0; // r1+0x0

    // References
    // -> void* gHeapTree;
    // -> unsigned int aHeapTreeFlag[125];
}

// Erased
static int cpuTreeFree(struct cpu_function* pFunction) {
    // Parameters
    // struct cpu_function* pFunction; // r1+0x0

    // Local variables
    unsigned int* anPack; // r1+0x0
    int iPack; // r1+0x0
    unsigned int nMask; // r5

    // References
    // -> unsigned int aHeapTreeFlag[125];
}

// Range: 0x80033304 -> 0x80033E88
int cpuFindFunction(struct _CPU* pCPU, int theAddress, struct cpu_function** tree_node) {
    // Parameters
    // struct _CPU* pCPU; // r22
    // int theAddress; // r1+0x38
    // struct cpu_function** tree_node; // r28

    // Local variables
    struct __anon_0x3EB4F** apDevice; // r26
    u8* aiDevice; // r27
    unsigned int opcode; // r1+0x34
    u8 follow; // r1+0x3D
    u8 valid; // r16
    u8 check; // r1+0x3C
    u8 end_flag; // r18
    u8 save_restore; // r14
    u8 alert; // r15
    int beginAddress; // r21
    int cheat_address; // r17
    int current_address; // r31
    int temp_address; // r30
    int branch; // r1+0x8

    // References
    // -> static u8 Opcode[64];
    // -> static u8 RegimmOpcode[32];
    // -> static u8 SpecialOpcode[64];
}

// Range: 0x800331A4 -> 0x80033304
static int cpuDMAUpdateFunction(struct _CPU* pCPU, int start, int end) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // int start; // r29
    // int end; // r30

    // Local variables
    struct cpu_treeRoot* root; // r1+0x8
    int count; // r1+0x8
    int cancel; // r5
}

// Erased
static void treeCallerInit(struct cpu_callerID* block, int total) {
    // Parameters
    // struct cpu_callerID* block; // r3
    // int total; // r1+0x4

    // Local variables
    int count; // r6
}

// Erased
static int treeCallerKill(struct _CPU* pCPU, struct cpu_function* kill) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // struct cpu_function* kill; // r30

    // Local variables
    int left; // r1+0x14
    int right; // r1+0x10
    struct cpu_treeRoot* root; // r31
}

// Range: 0x800330A0 -> 0x800331A4
static int treeCallerCheck(struct _CPU* pCPU, struct cpu_function* tree, int flag, int nAddress0, int nAddress1) {
    // Parameters
    // struct _CPU* pCPU; // r24
    // struct cpu_function* tree; // r25
    // int flag; // r26
    // int nAddress0; // r27
    // int nAddress1; // r28

    // Local variables
    int count; // r30
    int saveGCN; // r6
    int saveN64; // r1+0x8
    int* addr_function; // r1+0x8
    int* addr_call; // r29
}

// Range: 0x80033048 -> 0x800330A0
static int treeInit(struct _CPU* pCPU, int root_address) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int root_address; // r1+0x4

    // Local variables
    struct cpu_treeRoot* root; // r1+0x0
}

// Range: 0x80032F2C -> 0x80033048
static int treeInitNode(struct cpu_function** tree, struct cpu_function* prev, int start, int end) {
    // Parameters
    // struct cpu_function** tree; // r30
    // struct cpu_function* prev; // r31
    // int start; // r28
    // int end; // r29

    // Local variables
    struct cpu_function* node; // r1+0x1C
    int where; // r1+0x18
}

// Range: 0x80032C84 -> 0x80032F2C
static int treeKill(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r28

    // Local variables
    struct cpu_treeRoot* root; // r1+0x8
    int count; // r29

    // References
    // -> unsigned int aHeapTreeFlag[125];
}

// Range: 0x800329D4 -> 0x80032C84
static int treeKillNodes(struct _CPU* pCPU, struct cpu_function* tree) {
    // Parameters
    // struct _CPU* pCPU; // r24
    // struct cpu_function* tree; // r25

    // Local variables
    struct cpu_function* current; // r27
    struct cpu_function* kill; // r28
    int count; // r26

    // References
    // -> unsigned int aHeapTreeFlag[125];
}

// Range: 0x80032674 -> 0x800329D4
static int treeDeleteNode(struct _CPU* pCPU, struct cpu_function** top, struct cpu_function* kill) {
    // Parameters
    // struct _CPU* pCPU; // r30
    // struct cpu_function** top; // r1+0xC
    // struct cpu_function* kill; // r31

    // Local variables
    struct cpu_treeRoot* root; // r3
    struct cpu_function* save1; // r5
    struct cpu_function* save2; // r8
    struct cpu_function* connect; // r1+0x8

    // References
    // -> unsigned int aHeapTreeFlag[125];
}

// Erased
static int treeRebuild(struct _CPU* pCPU, int start_address, struct cpu_function** node) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // int start_address; // r30
    // struct cpu_function** node; // r31
}

// Erased
static int treeInsertAndReturn(struct _CPU* pCPU, int start, int end, struct cpu_function** ppFunction) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // int start; // r28
    // int end; // r29
    // struct cpu_function** ppFunction; // r30

    // Local variables
    struct cpu_treeRoot* root; // r31
    int flag; // r3
}

// Range: 0x80032558 -> 0x80032674
int treeInsert(struct _CPU* pCPU, int start, int end) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // int start; // r29
    // int end; // r30

    // Local variables
    struct cpu_treeRoot* root; // r31
    struct cpu_function* current; // r1+0x14
    int flag; // r3
}

// Range: 0x80032470 -> 0x80032558
static int treeInsertNode(struct cpu_function** tree, int start, int end, struct cpu_function** ppFunction) {
    // Parameters
    // struct cpu_function** tree; // r31
    // int start; // r8
    // int end; // r7
    // struct cpu_function** ppFunction; // r30

    // Local variables
    struct cpu_function** current; // r31
    struct cpu_function* prev; // r4
}

// Range: 0x800322D8 -> 0x80032470
static int treeBalance(struct cpu_treeRoot* root) {
    // Parameters
    // struct cpu_treeRoot* root; // r1+0x0

    // Local variables
    struct cpu_function* tree; // r8
    struct cpu_function* current; // r4
    struct cpu_function* save; // r6
    int total; // r9
    int count; // r7
}

// Range: 0x800320EC -> 0x800322D8
static int treeAdjustRoot(struct _CPU* pCPU, int new_end) {
    // Parameters
    // struct _CPU* pCPU; // r23
    // int new_end; // r24

    // Local variables
    int old_root; // r1+0x8
    int new_root; // r30
    int kill_start; // r29
    int check1; // r1+0x8
    int check2; // r28
    u16 total; // r27
    int total_memory; // r26
    int address; // r22
    struct cpu_treeRoot* root; // r25
    struct cpu_function* node; // r1+0x18
    struct cpu_function* change; // r1+0x14
}

// Erased
static int treeSearch(struct _CPU* pCPU, int target, struct cpu_function** node) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8
    // int target; // r4
    // struct cpu_function** node; // r5

    // Local variables
    struct cpu_treeRoot* root; // r1+0x8
    int flag; // r3
}

// Range: 0x80032088 -> 0x800320EC
static int treeSearchNode(struct cpu_function* tree, int target, struct cpu_function** node) {
    // Parameters
    // struct cpu_function* tree; // r3
    // int target; // r1+0x4
    // struct cpu_function** node; // r1+0x8

    // Local variables
    struct cpu_function* current; // r3
}

// Range: 0x800318F0 -> 0x80032088
static int treeKillRange(struct _CPU* pCPU, struct cpu_function* tree, int start, int end) {
    // Parameters
    // struct _CPU* pCPU; // r31
    // struct cpu_function* tree; // r24
    // int start; // r25
    // int end; // r26

    // Local variables
    struct cpu_treeRoot* root; // r29
    struct cpu_function* node1; // r1+0x3C
    struct cpu_function* node2; // r1+0x38
    struct cpu_function* save1; // r3
    struct cpu_function* save2; // r4
    struct cpu_function* connect; // r5
    int update; // r28
    int count; // r27

    // References
    // -> unsigned int aHeapTreeFlag[125];
}

// Range: 0x80031860 -> 0x800318F0
static int treeKillReason(struct _CPU* pCPU, int* value) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
    // int* value; // r1+0x4
}

// Range: 0x8003174C -> 0x80031860
static int treeTimerCheck(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    struct cpu_treeRoot* root; // r1+0x8
    int begin; // r1+0x10
    int end; // r1+0xC
}

// Erased
static int treeCleanUpCheck(struct _CPU* pCPU, struct cpu_function* node) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // struct cpu_function* node; // r30

    // Local variables
    struct cpu_treeRoot* root; // r31
}

// Range: 0x8003161C -> 0x8003174C
static int treeCleanUp(struct _CPU* pCPU, struct cpu_treeRoot* root) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // struct cpu_treeRoot* root; // r31

    // Local variables
    int done; // r3
    int complete; // r30
}

// Range: 0x8003133C -> 0x8003161C
static int treeCleanNodes(struct _CPU* pCPU, struct cpu_function* top) {
    // Parameters
    // struct _CPU* pCPU; // r27
    // struct cpu_function* top; // r1+0xC

    // Local variables
    struct cpu_function** current; // r30
    struct cpu_function* kill; // r29
    struct cpu_treeRoot* root; // r1+0x8
    int kill_limit; // r28
}

// Erased
static int treeForceCleanUp(struct _CPU* pCPU, struct cpu_function* node, int kill_value) {
    // Parameters
    // struct _CPU* pCPU; // r3
    // struct cpu_function* node; // r1+0xC
    // int kill_value; // r5

    // Local variables
    struct cpu_treeRoot* root; // r31
}

// Range: 0x80031168 -> 0x8003133C
static int treeForceCleanNodes(struct _CPU* pCPU, struct cpu_function* tree, int kill_limit) {
    // Parameters
    // struct _CPU* pCPU; // r28
    // struct cpu_function* tree; // r1+0xC
    // int kill_limit; // r29

    // Local variables
    struct cpu_function* current; // r31
    struct cpu_function* kill; // r30
}

// Erased
static int treePrint(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    struct cpu_treeRoot* root; // r1+0x8
    int left; // r1+0x10
    int right; // r1+0xC
}

// Range: 0x80030F84 -> 0x80031168
static int treePrintNode(struct _CPU* pCPU, struct cpu_function* tree, int print_flag, int* left, int* right) {
    // Parameters
    // struct _CPU* pCPU; // r21
    // struct cpu_function* tree; // r22
    // int print_flag; // r1+0x10
    // int* left; // r23
    // int* right; // r24

    // Local variables
    struct cpu_function* current; // r27
    int flag; // r26
    int level; // r25

    // References
    // -> int ganMapGPR[32];
}

// Erased
static int treeMemory(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x80030E70 -> 0x80030F84
static int cpuOpcodeChecksum(unsigned int opcode) {
    // Parameters
    // unsigned int opcode; // r1+0x0

    // Local variables
    int flag; // r5
}

// Erased
static int cpuDoubleCheckSameChecksum(struct cpu_disk_node* pDisk, int start) {
    // Parameters
    // struct cpu_disk_node* pDisk; // r30
    // int start; // r4

    // Local variables
    int count; // r1+0x8
    int instruction; // r1+0x8
    unsigned int* last; // r31
    unsigned int* current; // r1+0x10

    // References
    // -> struct __anon_0x3DB14* gpSystem;
}

// Erased
static int cpuCheckOpcodeHack(struct _CPU* pCPU, int startAddress, int instruction) {
    // Parameters
    // struct _CPU* pCPU; // r29
    // int startAddress; // r30
    // int instruction; // r31

    // Local variables
    int iHack; // r1+0x8
    unsigned int* opcode; // r1+0x14
}

// Erased
static int cpuUpdateDiskChecksum(unsigned int* checksum, int startAddress, int endAddress) {
    // Parameters
    // unsigned int* checksum; // r29
    // int startAddress; // r4
    // int endAddress; // r1+0x10

    // Local variables
    int count; // r31
    int instruction; // r30
    int check; // r1+0x8
    unsigned int* opcode; // r1+0x14
    unsigned int part; // r27

    // References
    // -> struct __anon_0x3DB14* gpSystem;
}
