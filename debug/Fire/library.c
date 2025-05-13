/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\library.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008F0F4 -> 0x8009779C
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ int nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ int (*pfEvent)(void*, int, void*);
} __anon_0x78CD6; // size = 0x10

// size = 0x10, address = 0x800EEB0C
struct _XL_OBJECTTYPE gClassLibrary;

// size = 0x100, address = 0x800EEB1C
static unsigned int __osRcpImTable[64];

// size = 0x4, address = 0x80135328
static f32 dtor$466;

// size = 0x4, address = 0x8013532C
static f32 dtor$480;

// size = 0x4, address = 0x80135330
static unsigned int nAddress$605;

typedef struct __anon_0x78E87 {
    /* 0x0 */ int nOffsetHost;
    /* 0x4 */ int nAddressN64;
} __anon_0x78E87; // size = 0x8

typedef struct cpu_callerID {
    /* 0x0 */ int N64address;
    /* 0x4 */ int GCNaddress;
} __anon_0x78EED; // size = 0x8

typedef struct cpu_function {
    /* 0x00 */ void* pnBase;
    /* 0x04 */ void* pfCode;
    /* 0x08 */ int nCountJump;
    /* 0x0C */ struct __anon_0x78E87* aJump;
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
} __anon_0x78F60; // size = 0x48

typedef union __anon_0x7923C {
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
} __anon_0x7923C;

typedef struct __anon_0x79A22 {
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
} __anon_0x79A22; // size = 0x34

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
} __anon_0x79CF0; // size = 0x84

typedef struct _CPU_ADDRESS {
    /* 0x0 */ int nN64;
    /* 0x4 */ int nHost;
    /* 0x8 */ struct cpu_function* pFunction;
} __anon_0x79F31; // size = 0xC

typedef struct __anon_0x79FE6 {
    /* 0x0 */ unsigned int nAddress;
    /* 0x4 */ unsigned int nOpcodeOld;
    /* 0x8 */ unsigned int nOpcodeNew;
} __anon_0x79FE6; // size = 0xC

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
} __anon_0x7A111; // size = 0x2C8

typedef struct OSAlarm {
    /* 0x00 */ void (*handler)(struct OSAlarm*, struct OSContext*);
    /* 0x04 */ u32 tag;
    /* 0x08 */ s64 fire;
    /* 0x10 */ struct OSAlarm* prev;
    /* 0x14 */ struct OSAlarm* next;
    /* 0x18 */ s64 period;
    /* 0x20 */ s64 start;
} __anon_0x7A368; // size = 0x28

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
} __anon_0x7A483; // size = 0x28

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
    /* 0x00040 */ union __anon_0x7923C aGPR[32];
    /* 0x00140 */ union __anon_0x7D2DB aFPR[32];
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
    /* 0x00B64 */ struct __anon_0x79A22* apDevice[256];
    /* 0x00F64 */ u8 aiDevice[65536];
    /* 0x10F64 */ void* gHeap1;
    /* 0x10F68 */ void* gHeap2;
    /* 0x10F6C */ unsigned int aHeap1Flag[192];
    /* 0x1126C */ unsigned int aHeap2Flag[13];
    /* 0x112A0 */ struct cpu_treeRoot* gTree;
    /* 0x112A4 */ struct _CPU_ADDRESS aAddressCache[256];
    /* 0x11EA4 */ int nCountCodeHack;
    /* 0x11EA8 */ struct __anon_0x79FE6 aCodeHack[32];
    /* 0x12028 */ s64 nTimeRetrace;
    /* 0x12030 */ struct OSAlarm alarmRetrace;
    /* 0x12058 */ unsigned int nFlagRAM;
    /* 0x1205C */ unsigned int nFlagCODE;
    /* 0x12060 */ unsigned int nCompileFlag;
    /* 0x12064 */ struct cpu_optimize nOptimize;
} __anon_0x7A630; // size = 0x12090

typedef struct __anon_0x7AD10 {
    /* 0x0 */ char* szName;
    /* 0x4 */ void (*pfLibrary)(struct _CPU*);
    /* 0x8 */ unsigned int anData[17];
} __anon_0x7AD10; // size = 0x4C

// size = 0x1008, address = 0x800EEF2C
struct __anon_0x7AD10 gaFunction[54];

typedef struct __anon_0x7AE26 {
    /* 0x00 */ int nFlag;
    /* 0x04 */ void* pHost;
    /* 0x08 */ int nAddStackSwap;
    /* 0x0C */ int nCountFunction;
    /* 0x10 */ int nAddressException;
    /* 0x14 */ struct __anon_0x7AD10* aFunction;
    /* 0x18 */ void* apData[10];
    /* 0x40 */ int anAddress[10];
} __anon_0x7AE26; // size = 0x68

typedef struct __anon_0x7BB81 {
    /* 0x0 */ f32 f_odd;
    /* 0x4 */ f32 f_even;
} __anon_0x7BB81; // size = 0x8

typedef union __anon_0x7BBDC {
    /* 0x0 */ struct __anon_0x7BB81 f;
    /* 0x0 */ f64 d;
    /* 0x0 */ s64 u64;
} __anon_0x7BBDC;

typedef struct __anon_0x7BC50 {
    /* 0x000 */ u64 at;
    /* 0x008 */ u64 v0;
    /* 0x010 */ u64 v1;
    /* 0x018 */ u64 a0;
    /* 0x020 */ u64 a1;
    /* 0x028 */ u64 a2;
    /* 0x030 */ u64 a3;
    /* 0x038 */ u64 t0;
    /* 0x040 */ u64 t1;
    /* 0x048 */ u64 t2;
    /* 0x050 */ u64 t3;
    /* 0x058 */ u64 t4;
    /* 0x060 */ u64 t5;
    /* 0x068 */ u64 t6;
    /* 0x070 */ u64 t7;
    /* 0x078 */ u64 s0;
    /* 0x080 */ u64 s1;
    /* 0x088 */ u64 s2;
    /* 0x090 */ u64 s3;
    /* 0x098 */ u64 s4;
    /* 0x0A0 */ u64 s5;
    /* 0x0A8 */ u64 s6;
    /* 0x0B0 */ u64 s7;
    /* 0x0B8 */ u64 t8;
    /* 0x0C0 */ u64 t9;
    /* 0x0C8 */ u64 gp;
    /* 0x0D0 */ u64 sp;
    /* 0x0D8 */ u64 s8;
    /* 0x0E0 */ u64 ra;
    /* 0x0E8 */ u64 lo;
    /* 0x0F0 */ u64 hi;
    /* 0x0F8 */ unsigned int sr;
    /* 0x0FC */ unsigned int pc;
    /* 0x100 */ unsigned int cause;
    /* 0x104 */ unsigned int badvaddr;
    /* 0x108 */ unsigned int rcp;
    /* 0x10C */ unsigned int fpcsr;
    /* 0x110 */ union __anon_0x7BBDC fp0;
    /* 0x118 */ union __anon_0x7BBDC fp2;
    /* 0x120 */ union __anon_0x7BBDC fp4;
    /* 0x128 */ union __anon_0x7BBDC fp6;
    /* 0x130 */ union __anon_0x7BBDC fp8;
    /* 0x138 */ union __anon_0x7BBDC fp10;
    /* 0x140 */ union __anon_0x7BBDC fp12;
    /* 0x148 */ union __anon_0x7BBDC fp14;
    /* 0x150 */ union __anon_0x7BBDC fp16;
    /* 0x158 */ union __anon_0x7BBDC fp18;
    /* 0x160 */ union __anon_0x7BBDC fp20;
    /* 0x168 */ union __anon_0x7BBDC fp22;
    /* 0x170 */ union __anon_0x7BBDC fp24;
    /* 0x178 */ union __anon_0x7BBDC fp26;
    /* 0x180 */ union __anon_0x7BBDC fp28;
    /* 0x188 */ union __anon_0x7BBDC fp30;
} __anon_0x7BC50; // size = 0x190

typedef struct __OSThread_s {
    /* 0x00 */ struct __OSThread_s* next;
    /* 0x04 */ int priority;
    /* 0x08 */ struct __OSThread_s** queue;
    /* 0x0C */ struct __OSThread_s* tlnext;
    /* 0x10 */ u16 state;
    /* 0x12 */ u16 flags;
    /* 0x14 */ int id;
    /* 0x18 */ int fp;
    /* 0x20 */ struct __anon_0x7BC50 context;
} __anon_0x7C319; // size = 0x1B0

typedef struct OSMesgQueue_s {
    /* 0x00 */ struct __OSThread_s* mtqueue;
    /* 0x04 */ struct __OSThread_s* fullqueue;
    /* 0x08 */ int validCount;
    /* 0x0C */ int first;
    /* 0x10 */ int msgCount;
    /* 0x14 */ void* msg;
} __anon_0x7C481; // size = 0x18

typedef struct __anon_0x7C589 {
    /* 0x0 */ u16 type;
    /* 0x2 */ u8 pri;
    /* 0x3 */ u8 status;
    /* 0x4 */ struct OSMesgQueue_s* retQueue;
} __anon_0x7C589; // size = 0x8

typedef struct __anon_0x7C62D {
    /* 0x00 */ struct __anon_0x7C589 hdr;
    /* 0x08 */ void* dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ void* piHandle;
} __anon_0x7C62D; // size = 0x18

typedef struct __anon_0x7D115 {
    /* 0x0 */ u8 col[3];
    /* 0x3 */ char pad1;
    /* 0x4 */ u8 colc[3];
    /* 0x7 */ char pad2;
    /* 0x8 */ s8 dir[3];
    /* 0xB */ char pad3;
} __anon_0x7D115; // size = 0xC

typedef union __anon_0x7D215 {
    /* 0x0 */ struct __anon_0x7D115 l;
    /* 0x0 */ s64 force_structure_alignment[2];
} __anon_0x7D215;

typedef struct __anon_0x7D2A5 {
    /* 0x0 */ union __anon_0x7D215 l[2];
} __anon_0x7D2A5; // size = 0x20

typedef union __anon_0x7D2DB {
    /* 0x0 */ f32 _0f32;
    /* 0x4 */ f32 f32;
    /* 0x0 */ f64 f64;
    /* 0x0 */ int _0s32;
    /* 0x4 */ int s32;
    /* 0x0 */ s64 s64;
    /* 0x0 */ unsigned int _0u32;
    /* 0x4 */ unsigned int u32;
    /* 0x0 */ u64 u64;
} __anon_0x7D2DB;

typedef struct __anon_0x7DB47 {
    /* 0x0 */ int x1;
    /* 0x4 */ int y1;
    /* 0x8 */ int x2;
    /* 0xC */ int y2;
} __anon_0x7DB47; // size = 0x10

typedef union __anon_0x7DBF9 {
    /* 0x0 */ struct __anon_0x7DB47 h;
    /* 0x0 */ s32 force_structure_alignment[4];
} __anon_0x7DBF9;

typedef struct __anon_0x7F9D8 {
    /* 0x0 */ f32 rX;
    /* 0x4 */ f32 rY;
    /* 0x8 */ f32 rSizeX;
    /* 0xC */ f32 rSizeY;
} __anon_0x7F9D8; // size = 0x10

typedef struct __anon_0x7FA72 {
    /* 0x00 */ int nSize;
    /* 0x04 */ int nWidth;
    /* 0x08 */ int nFormat;
    /* 0x0C */ void* pData;
    /* 0x10 */ int nAddress;
} __anon_0x7FA72; // size = 0x14

typedef struct __anon_0x7FBB3 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} __anon_0x7FBB3; // size = 0xC

typedef struct __anon_0x7FC23 {
    /* 0x00 */ int bTransformed;
    /* 0x04 */ struct __anon_0x7FBB3 rVecOrigTowards;
    /* 0x10 */ f32 rColorR;
    /* 0x14 */ f32 rColorG;
    /* 0x18 */ f32 rColorB;
    /* 0x1C */ f32 rVectorX;
    /* 0x20 */ f32 rVectorY;
    /* 0x24 */ f32 rVectorZ;
    /* 0x28 */ f32 kc;
    /* 0x2C */ f32 kl;
    /* 0x30 */ f32 kq;
    /* 0x34 */ s16 coordX;
    /* 0x36 */ s16 coordY;
    /* 0x38 */ s16 coordZ;
} __anon_0x7FC23; // size = 0x3C

typedef struct __anon_0x7FE53 {
    /* 0x00 */ int bTransformed;
    /* 0x04 */ struct __anon_0x7FBB3 rS;
    /* 0x10 */ struct __anon_0x7FBB3 rT;
    /* 0x1C */ struct __anon_0x7FBB3 rSRaw;
    /* 0x28 */ struct __anon_0x7FBB3 rTRaw;
} __anon_0x7FE53; // size = 0x34

typedef struct __anon_0x7FF3C {
    /* 0x00 */ f32 rSum;
    /* 0x04 */ f32 rS;
    /* 0x08 */ f32 rT;
    /* 0x0C */ struct __anon_0x7FBB3 vec;
    /* 0x18 */ u8 anColor[4];
} __anon_0x7FF3C; // size = 0x1C

typedef union __anon_0x8009B {
    /* 0x0 */ u8 u8[4096];
    /* 0x0 */ u16 u16[2048];
    /* 0x0 */ unsigned int u32[1024];
    /* 0x0 */ u64 u64[512];
} __anon_0x8009B;

typedef struct __anon_0x80138 {
    /* 0x0 */ union __anon_0x8009B data;
} __anon_0x80138; // size = 0x1000

typedef enum _GXTexFmt {
    GX_TF_I4 = 0,
    GX_TF_I8 = 1,
    GX_TF_IA4 = 2,
    GX_TF_IA8 = 3,
    GX_TF_RGB565 = 4,
    GX_TF_RGB5A3 = 5,
    GX_TF_RGBA8 = 6,
    GX_TF_CMPR = 14,
    GX_CTF_R4 = 32,
    GX_CTF_RA4 = 34,
    GX_CTF_RA8 = 35,
    GX_CTF_YUVA8 = 38,
    GX_CTF_A8 = 39,
    GX_CTF_R8 = 40,
    GX_CTF_G8 = 41,
    GX_CTF_B8 = 42,
    GX_CTF_RG8 = 43,
    GX_CTF_GB8 = 44,
    GX_TF_Z8 = 17,
    GX_TF_Z16 = 19,
    GX_TF_Z24X8 = 22,
    GX_CTF_Z4 = 48,
    GX_CTF_Z8M = 57,
    GX_CTF_Z8L = 58,
    GX_CTF_Z16L = 60,
    GX_TF_A8 = 39,
} __anon_0x801D1;

typedef struct _GXTlutObj {
    /* 0x0 */ u32 dummy[3];
} __anon_0x80393; // size = 0xC

typedef struct _GXTexObj {
    /* 0x0 */ u32 dummy[8];
} __anon_0x803FA; // size = 0x20

typedef enum _GXTexWrapMode {
    GX_CLAMP = 0,
    GX_REPEAT = 1,
    GX_MIRROR = 2,
    GX_MAX_TEXWRAPMODE = 3,
} __anon_0x80440;

typedef struct _FRAME_TEXTURE {
    /* 0x00 */ int nMode;
    /* 0x04 */ int iPackPixel;
    /* 0x08 */ int iPackColor;
    /* 0x0C */ int nFrameLast;
    /* 0x10 */ s16 nSizeX;
    /* 0x12 */ s16 nSizeY;
    /* 0x14 */ unsigned int nAddress;
    /* 0x18 */ unsigned int nCodePixel;
    /* 0x1C */ unsigned int nCodeColor;
    /* 0x20 */ struct _FRAME_TEXTURE* pTextureNext;
    /* 0x24 */ unsigned int nData0;
    /* 0x28 */ unsigned int nData1;
    /* 0x2C */ unsigned int nData2;
    /* 0x30 */ unsigned int nData3;
    /* 0x34 */ enum _GXTexFmt eFormat;
    /* 0x38 */ struct _GXTlutObj objectTLUT;
    /* 0x44 */ struct _GXTexObj objectTexture;
    /* 0x64 */ enum _GXTexWrapMode eWrapS;
    /* 0x68 */ enum _GXTexWrapMode eWrapT;
} __anon_0x804A9; // size = 0x6C

typedef struct __anon_0x80806 {
    /* 0x00 */ int nSize;
    /* 0x04 */ int nTMEM;
    /* 0x08 */ int iTLUT;
    /* 0x0C */ int nSizeX;
    /* 0x10 */ int nFormat;
    /* 0x14 */ s16 nMaskS;
    /* 0x16 */ s16 nMaskT;
    /* 0x18 */ s16 nModeS;
    /* 0x1A */ s16 nModeT;
    /* 0x1C */ s16 nShiftS;
    /* 0x1E */ s16 nShiftT;
    /* 0x20 */ s16 nX0;
    /* 0x22 */ s16 nY0;
    /* 0x24 */ s16 nX1;
    /* 0x26 */ s16 nY1;
    /* 0x28 */ unsigned int nCodePixel;
} __anon_0x80806; // size = 0x2C

typedef enum __anon_0x80AE8 {
    FMP_NONE = -1,
    FMP_PERSPECTIVE = 0,
    FMP_ORTHOGRAPHIC = 1,
} __anon_0x80AE8;

typedef struct __anon_0x80B6D {
    /* 0x00 */ int nCount;
    /* 0x04 */ f32 rScale;
    /* 0x08 */ f32 rAspect;
    /* 0x0C */ f32 rFieldOfViewY;
    /* 0x10 */ f32 rClipNear;
    /* 0x14 */ f32 rClipFar;
    /* 0x18 */ unsigned int nAddressFloat;
    /* 0x1C */ unsigned int nAddressFixed;
    /* 0x20 */ enum __anon_0x80AE8 eProjection;
} __anon_0x80B6D; // size = 0x24

typedef struct _GXColor {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} __anon_0x80D02; // size = 0x4

typedef struct __anon_0x80DBD {
    /* 0x00000 */ unsigned int anCIMGAddresses[8];
    /* 0x00020 */ u16 nNumCIMGAddresses;
    /* 0x00024 */ int bBlurOn;
    /* 0x00028 */ int bHackPause;
    /* 0x0002C */ int nHackCount;
    /* 0x00030 */ int nFrameCounter;
    /* 0x00034 */ int bPauseThisFrame;
    /* 0x00038 */ int bCameFromBomberNotes;
    /* 0x0003C */ int bInBomberNotes;
    /* 0x00040 */ int bShrinking;
    /* 0x00044 */ int bSnapShot;
    /* 0x00048 */ int bUsingLens;
    /* 0x0004C */ u8 cBlurAlpha;
    /* 0x00050 */ int bBlurredThisFrame;
    /* 0x00054 */ int nFrameCIMGCalls;
    /* 0x00058 */ int bModifyZBuffer;
    /* 0x0005C */ int bOverrideDepth;
    /* 0x00060 */ int nZBufferSets;
    /* 0x00064 */ int nLastFrameZSets;
    /* 0x00068 */ int bPauseBGDrawn;
    /* 0x0006C */ int bFrameOn;
    /* 0x00070 */ int bBackBufferDrawn;
    /* 0x00074 */ int bGrabbedFrame;
    /* 0x00078 */ u64* pnGBI;
    /* 0x0007C */ unsigned int nFlag;
    /* 0x00080 */ f32 rScaleX;
    /* 0x00084 */ f32 rScaleY;
    /* 0x00088 */ unsigned int nCountFrames;
    /* 0x0008C */ unsigned int nMode;
    /* 0x00090 */ unsigned int aMode[10];
    /* 0x000B8 */ struct __anon_0x7F9D8 viewport;
    /* 0x000C8 */ struct __anon_0x7FA72 aBuffer[4];
    /* 0x00118 */ unsigned int nOffsetDepth0;
    /* 0x0011C */ unsigned int nOffsetDepth1;
    /* 0x00120 */ int nWidthLine;
    /* 0x00124 */ f32 rDepth;
    /* 0x00128 */ f32 rDelta;
    /* 0x0012C */ int (*aDraw[4])(void*, void*);
    /* 0x0013C */ int nCountLight;
    /* 0x00140 */ struct __anon_0x7FC23 aLight[8];
    /* 0x00320 */ struct __anon_0x7FE53 lookAt;
    /* 0x00354 */ int nCountVertex;
    /* 0x00358 */ struct __anon_0x7FF3C aVertex[80];
    /* 0x00C18 */ struct __anon_0x80138 TMEM;
    /* 0x01C18 */ void* aPixelData;
    /* 0x01C1C */ void* aColorData;
    /* 0x01C20 */ int nBlocksPixel;
    /* 0x01C24 */ int nBlocksMaxPixel;
    /* 0x01C28 */ int nBlocksColor;
    /* 0x01C2C */ int nBlocksMaxColor;
    /* 0x01C30 */ int nBlocksTexture;
    /* 0x01C34 */ int nBlocksMaxTexture;
    /* 0x01C38 */ unsigned int anPackPixel[48];
    /* 0x01CF8 */ unsigned int anPackColor[320];
    /* 0x021F8 */ unsigned int nAddressLoad;
    /* 0x021FC */ unsigned int nCodePixel;
    /* 0x02200 */ unsigned int nTlutCode[16];
    /* 0x02240 */ struct _FRAME_TEXTURE aTexture[2048];
    /* 0x38240 */ unsigned int anTextureUsed[64];
    /* 0x38340 */ struct _FRAME_TEXTURE* apTextureCached[4096];
    /* 0x3C340 */ int iTileLoad;
    /* 0x3C344 */ unsigned int n2dLoadTexType;
    /* 0x3C348 */ int nLastX0;
    /* 0x3C34C */ int nLastY0;
    /* 0x3C350 */ int nLastX1;
    /* 0x3C354 */ int nLastY1;
    /* 0x3C358 */ struct __anon_0x80806 aTile[8];
    /* 0x3C4B8 */ int anSizeX[2];
    /* 0x3C4C0 */ int anSizeY[2];
    /* 0x3C4C8 */ int iHintMatrix;
    /* 0x3C4CC */ int iMatrixModel;
    /* 0x3C4D0 */ int iHintProjection;
    /* 0x3C4D4 */ f32 matrixView[4][4];
    /* 0x3C514 */ int iHintLast;
    /* 0x3C518 */ int iHintHack;
    /* 0x3C51C */ enum __anon_0x80AE8 eTypeProjection;
    /* 0x3C520 */ f32 aMatrixModel[10][4][4];
    /* 0x3C7A0 */ f32 matrixProjection[4][4];
    /* 0x3C7E0 */ f32 matrixProjectionExtra[4][4];
    /* 0x3C820 */ struct __anon_0x80B6D aMatrixHint[64];
    /* 0x3D120 */ u8 primLODmin;
    /* 0x3D121 */ u8 primLODfrac;
    /* 0x3D122 */ u8 lastTile;
    /* 0x3D123 */ u8 iTileDrawn;
    /* 0x3D124 */ struct _GXColor aColor[5];
    /* 0x3D138 */ unsigned int nModeVtx;
    /* 0x3D13C */ u16* nTempBuffer;
    /* 0x3D140 */ u16* nCopyBuffer;
    /* 0x3D144 */ unsigned int* nLensBuffer;
    /* 0x3D148 */ u16* nCameraBuffer;
} __anon_0x80DBD; // size = 0x3D150

// Range: 0x80096AB8 -> 0x8009779C
static int __osException(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    int iBit; // r3
    struct __anon_0x7AE26* pLibrary; // r1+0x8
    s64 nData64; // r1+0x28
    s64 nCause; // r1+0x20
    struct __OSThread_s* __osRunningThread; // r1+0x18
    struct __anon_0x79A22** apDevice; // r31
    u8* aiDevice; // r30
    unsigned int nStatus; // r22
    unsigned int nStatusRSP; // r1+0x14
    unsigned int nData32; // r1+0x10
    unsigned int __OSGlobalIntMask; // r23
    unsigned int nS0; // r18
    unsigned int nS1; // r17
    unsigned int nMask; // r1+0xC
}

// Range: 0x80096728 -> 0x80096AB8
static int send_mesg(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r28

    // Local variables
    struct __anon_0x7AE26* pLibrary; // r1+0x8
    struct __anon_0x79A22** apDevice; // r30
    u8* aiDevice; // r29
}

// Range: 0x8009643C -> 0x80096728
static int __osEnqueueAndYield(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    s64 nData64; // r1+0x18
    struct __anon_0x7AE26* pLibrary; // r3
    struct __OSThread_s* __osRunningThread; // r1+0x10
    unsigned int __OSGlobalIntMask; // r31
    unsigned int nStatus; // r1+0x8
    unsigned int nData32; // r5
    unsigned int nMask; // r1+0xC
    struct __anon_0x79A22** apDevice; // r6
    u8* aiDevice; // r7
}

// Range: 0x80096214 -> 0x8009643C
static int __osEnqueueThread(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    struct __anon_0x79A22** apDevice; // r31
    u8* aiDevice; // r30
}

// Range: 0x80096140 -> 0x80096214
static int __osPopThread(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    struct __anon_0x79A22** apDevice; // r31
    u8* aiDevice; // r30
}

// Range: 0x80095B9C -> 0x80096140
static int __osDispatchThread(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r27

    // Local variables
    struct __anon_0x7AE26* pLibrary; // r29
    unsigned int nAddress; // r5
    u64 nData64; // r0
    struct __OSThread_s* __osRunningThread; // r1+0x10
    unsigned int nData32; // r1+0xC
    unsigned int __OSGlobalIntMask; // r28
    unsigned int nStatus; // r6
    unsigned int nMask; // r6

    // References
    // -> static unsigned int __osRcpImTable[64];
}

// Erased
static int __ptException() {}

// Range: 0x80095B48 -> 0x80095B9C
static int osGetMemSize(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    unsigned int nSize; // r1+0xC
}

// Range: 0x80095AC0 -> 0x80095B48
static int osInvalICache(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    unsigned int nAddress; // r30
    unsigned int nSize; // r1+0x8
}

// Range: 0x80095A30 -> 0x80095AC0
static int __osDisableInt(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    unsigned int nStatus; // r1+0x8
    u64 nData64; // r1+0x18
}

// Range: 0x800959A4 -> 0x80095A30
static int __osRestoreInt(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    u64 nStatus; // r1+0x10
}

// Range: 0x80095954 -> 0x800959A4
static int __osSpSetStatus(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8

    // Local variables
    unsigned int nData32; // r1+0xC
}

// Range: 0x80095920 -> 0x80095954
static void __cosf(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31
}

// Range: 0x800958EC -> 0x80095920
static void __sinf(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31
}

// Range: 0x800958A8 -> 0x800958EC
void _bzero(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int nSize; // r5
    void* pBuffer; // r1+0xC
}

// Range: 0x8009584C -> 0x800958A8
void _bcopy(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int nSize; // r5
    void* pSource; // r1+0x10
    void* pTarget; // r1+0xC
}

// Range: 0x800957F0 -> 0x8009584C
void _memcpy(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int nSize; // r5
    void* pSource; // r1+0x10
    void* pTarget; // r1+0xC
}

// Range: 0x800957E0 -> 0x800957F0
void osPhysicalToVirtual(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x8009576C -> 0x800957E0
void osVirtualToPhysical(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x80095454 -> 0x8009576C
void guMtxCatF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r23

    // Local variables
    int i; // r9
    int j; // r23
    f32 temp[4][4]; // r1+0x38
    union __anon_0x7D2DB data1; // r1+0x30
    union __anon_0x7D2DB data2; // r1+0x28
    unsigned int* mf; // r1+0x24
    unsigned int* nf; // r1+0x20
    unsigned int* res; // r1+0x1C
}

// Range: 0x8009524C -> 0x80095454
void guMtxF2L(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    f32* mf; // r1+0x24
    int e1; // r6
    int e2; // r7
    int i; // r8
    int j; // r1+0x8
    int* m; // r1+0x20
    union __anon_0x7D2DB data; // r1+0x18
    int* ai; // r9
    int* af; // r10
}

// Range: 0x80095178 -> 0x8009524C
void guMtxIdentF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r3

    // Local variables
    f32* mf; // r1+0x20
    int i; // r7
    int j; // r1+0x8
    union __anon_0x7D2DB data1; // r1+0x18
    union __anon_0x7D2DB data0; // r1+0x10
}

// Range: 0x800950C4 -> 0x80095178
void guMtxIdent(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r3

    // Local variables
    int* m; // r1+0xC
}

// Range: 0x80094E54 -> 0x800950C4
void guOrthoF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int i; // r8
    int j; // r4
    unsigned int* mf; // r1+0x2C
    unsigned int* sp; // r1+0x28
    f32 l; // f29
    f32 r; // f28
    f32 b; // f27
    f32 t; // f26
    f32 n; // f31
    f32 f; // f30
    f32 scale; // f5
    union __anon_0x7D2DB data0; // r1+0x20
    union __anon_0x7D2DB data1; // r1+0x18
    union __anon_0x7D2DB data; // r1+0x10
}

// Range: 0x80094B78 -> 0x80094E54
void guOrtho(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int* m; // r1+0x60
    int i; // r6
    int j; // r1+0x8
    int e1; // r7
    int e2; // r8
    union __anon_0x7D2DB data; // r1+0x58
    f32 mf[4][4]; // r1+0x18
    unsigned int* sp; // r1+0x14
    int* ai; // r9
    int* af; // r10
    f32 l; // f31
    f32 r; // f30
    f32 b; // f29
    f32 t; // f28
    f32 n; // f27
    f32 f; // f26
    f32 scale; // f5
}

// Range: 0x8009491C -> 0x80094B78
void guPerspectiveF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int i; // r8
    int j; // r4
    f32 cot; // f2
    s16* perspNorm; // r1+0x30
    unsigned int* mf; // r1+0x2C
    unsigned int* sp; // r1+0x28
    union __anon_0x7D2DB data0; // r1+0x20
    union __anon_0x7D2DB data1; // r1+0x18
    union __anon_0x7D2DB data; // r1+0x10
    f32 fovy; // f29
    f32 aspect; // f28
    f32 rNear; // f27
    f32 rFar; // f31
    f32 scale; // f5
}

// Range: 0x80094658 -> 0x8009491C
void guPerspective(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int* m; // r1+0x60
    f32 fovy; // f30
    f32 aspect; // f29
    f32 rNear; // f28
    f32 rFar; // f27
    f32 scale; // f5
    f32 _cot; // f2
    int i; // r6
    int j; // r1+0x8
    union __anon_0x7D2DB data; // r1+0x58
    f32 mf[4][4]; // r1+0x18
    int e1; // r7
    int e2; // r8
    unsigned int* sp; // r1+0x14
    int* ai; // r9
    int* af; // r10
}

// Range: 0x800945A8 -> 0x80094658
void GenPerspective_1080(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    union __anon_0x7D2DB data; // r1+0x18
    unsigned int* mf; // r1+0x10
    unsigned int* sp; // r1+0xC
    f32 fovy; // f3
    f32 aspect; // f4
    f32 rNear; // f1
    f32 rFar; // f2
    struct __anon_0x80DBD* pFrame; // r31
}

// Range: 0x80094480 -> 0x800945A8
void guScaleF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int i; // r8
    int j; // r4
    unsigned int* mf; // r1+0x20
    union __anon_0x7D2DB data0; // r1+0x18
    union __anon_0x7D2DB data1; // r1+0x10
}

// Range: 0x80094294 -> 0x80094480
void guScale(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    f32 mf[4][4]; // r1+0x24
    int* m; // r1+0x20
    int i; // r6
    int j; // r1+0x8
    int e1; // r7
    int e2; // r8
    union __anon_0x7D2DB data; // r1+0x18
    int* ai; // r9
    int* af; // r10
}

// Range: 0x80094174 -> 0x80094294
void guTranslateF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int i; // r8
    int j; // r4
    unsigned int* mf; // r1+0x20
    union __anon_0x7D2DB data0; // r1+0x18
    union __anon_0x7D2DB data1; // r1+0x10
}

// Range: 0x80093F88 -> 0x80094174
void guTranslate(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int* m; // r1+0x60
    int i; // r6
    int j; // r1+0x8
    int e1; // r7
    int e2; // r8
    union __anon_0x7D2DB data; // r1+0x58
    f32 mf[4][4]; // r1+0x14
    int* ai; // r9
    int* af; // r10
}

// Range: 0x80093C78 -> 0x80093F88
void guRotateF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    f32 m; // f2
    int i; // r8
    int j; // r4
    f32 a; // f31
    f32 x; // f30
    f32 y; // f29
    f32 z; // f28
    unsigned int* mf; // r1+0x2C
    unsigned int* sp; // r1+0x28
    union __anon_0x7D2DB data; // r1+0x20
    union __anon_0x7D2DB data0; // r1+0x18
    union __anon_0x7D2DB data1; // r1+0x10
    f32 sine; // r1+0x8
    f32 cosine; // r1+0x8
    f32 ab; // f27
    f32 bc; // f26
    f32 ca; // f25
    f32 t; // f4

    // References
    // -> static f32 dtor$466;
}

// Range: 0x8009392C -> 0x80093C78
void guRotate(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int* m; // r1+0x64
    unsigned int* sp; // r1+0x60
    union __anon_0x7D2DB data; // r1+0x58
    int i; // r6
    int j; // r1+0x8
    int e1; // r7
    int e2; // r8
    f32 mf[4][4]; // r1+0x18
    f32 sine; // r1+0x8
    f32 cosine; // r1+0x8
    f32 a; // f30
    f32 x; // f29
    f32 y; // f28
    f32 z; // f27
    f32 ab; // f13
    f32 bc; // f30
    f32 ca; // f29
    f32 t; // f26
    f32 magnitude; // f2
    int* ai; // r9
    int* af; // r10

    // References
    // -> static f32 dtor$480;
}

// Range: 0x800935A0 -> 0x8009392C
void guLookAtF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    f32 len; // f9
    f32 xAt; // r1+0x8
    f32 yAt; // r1+0x8
    f32 zAt; // f1
    f32 xUp; // r1+0x8
    f32 yUp; // f1
    f32 zUp; // f2
    f32 xEye; // f3
    f32 yEye; // f4
    f32 zEye; // f5
    unsigned int* mf; // r1+0x34
    unsigned int* sp; // r1+0x30
    f32 xLook; // f6
    f32 yLook; // f7
    f32 zLook; // f8
    f32 xRight; // f9
    f32 yRight; // f10
    f32 zRight; // f11
    union __anon_0x7D2DB data; // r1+0x28
    union __anon_0x7D2DB data0; // r1+0x20
    union __anon_0x7D2DB data1; // r1+0x18
}

// Range: 0x80093188 -> 0x800935A0
void guLookAt(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    f32 mf[4][4]; // r1+0x30
    int* m; // r1+0x2C
    unsigned int* sp; // r1+0x28
    union __anon_0x7D2DB data; // r1+0x20
    int i; // r6
    int j; // r1+0x8
    int e1; // r7
    int e2; // r8
    int* ai; // r9
    int* af; // r10
    f32 len; // f6
    f32 xLook; // f3
    f32 yLook; // f4
    f32 zLook; // f5
    f32 xRight; // f6
    f32 yRight; // f7
    f32 zRight; // f8
    f32 xEye; // f9
    f32 yEye; // f10
    f32 zEye; // f11
    f32 xAt; // r1+0x8
    f32 yAt; // r1+0x8
    f32 zAt; // f1
    f32 xUp; // r1+0x8
    f32 yUp; // f1
    f32 zUp; // f2
}

// Erased
static int __float2int(f32 x) {
    // Parameters
    // f32 x; // r1+0x8
}

// Range: 0x80092834 -> 0x80093188
void guLookAtHiliteF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    struct __anon_0x7D2A5* l; // r1+0x3C
    union __anon_0x7DBF9* h; // r1+0x38
    union __anon_0x7D2DB data; // r1+0x30
    unsigned int* mf; // r1+0x2C
    unsigned int* sp; // r1+0x28
    f32 len; // f5
    f32 xLook; // r1+0x8
    f32 yLook; // f1
    f32 zLook; // f2
    f32 xRight; // f3
    f32 yRight; // f4
    f32 zRight; // f5
    f32 xHilite; // f29
    f32 yHilite; // f28
    f32 zHilite; // f27
    f32 xEye; // f6
    f32 yEye; // f7
    f32 zEye; // f8
    f32 xAt; // r1+0x8
    f32 yAt; // f1
    f32 zAt; // f2
    f32 xUp; // f3
    f32 yUp; // f12
    f32 zUp; // f4
    f32 xl1; // f27
    f32 yl1; // f28
    f32 zl1; // f26
    f32 xl2; // f9
    f32 yl2; // f10
    f32 zl2; // f11
    int twidth; // r6
    int theight; // r7
}

// Range: 0x80091E60 -> 0x80092834
void guLookAtHilite(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    struct __anon_0x7D2A5* l; // r1+0x84
    union __anon_0x7DBF9* h; // r1+0x80
    int i; // r7
    int j; // r1+0x8
    int e1; // r5
    int e2; // r8
    union __anon_0x7D2DB data; // r1+0x78
    f32 mf[4][4]; // r1+0x38
    unsigned int* m; // r1+0x34
    unsigned int* sp; // r1+0x30
    int* ai; // r9
    int* af; // r10
    f32 len; // f5
    f32 xLook; // r1+0x8
    f32 yLook; // f1
    f32 zLook; // f2
    f32 xRight; // f3
    f32 yRight; // f4
    f32 zRight; // f5
    f32 xHilite; // f29
    f32 yHilite; // f28
    f32 zHilite; // f27
    f32 xEye; // f6
    f32 yEye; // f7
    f32 zEye; // f8
    f32 xAt; // r1+0x8
    f32 yAt; // f1
    f32 zAt; // f2
    f32 xUp; // f3
    f32 yUp; // f12
    f32 zUp; // f4
    f32 xl1; // f27
    f32 yl1; // f28
    f32 zl1; // f26
    f32 xl2; // f9
    f32 yl2; // f10
    f32 zl2; // f11
    int twidth; // r6
    int theight; // r7
}

// Range: 0x8009190C -> 0x80091E60
void guLookAtReflectF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    struct __anon_0x7D2A5* l; // r1+0x28
    union __anon_0x7D2DB data; // r1+0x20
    unsigned int* mf; // r1+0x1C
    unsigned int* sp; // r1+0x18
    f32 xEye; // f3
    f32 yEye; // f4
    f32 zEye; // f5
    f32 xAt; // r1+0x8
    f32 yAt; // r1+0x8
    f32 zAt; // f1
    f32 xUp; // r1+0x8
    f32 yUp; // f1
    f32 zUp; // f2
    f32 len; // f9
    f32 xLook; // f6
    f32 yLook; // f7
    f32 zLook; // f8
    f32 xRight; // f9
    f32 yRight; // f10
    f32 zRight; // f11
}

// Range: 0x80091338 -> 0x8009190C
void guLookAtReflect(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    struct __anon_0x7D2A5* l; // r1+0x70
    int i; // r7
    int j; // r1+0x8
    int e1; // r5
    int e2; // r8
    union __anon_0x7D2DB data; // r1+0x68
    f32 mf[4][4]; // r1+0x28
    unsigned int* m; // r1+0x24
    unsigned int* sp; // r1+0x20
    int* ai; // r9
    int* af; // r10
    f32 xEye; // f3
    f32 yEye; // f4
    f32 zEye; // f5
    f32 xAt; // r1+0x8
    f32 yAt; // r1+0x8
    f32 zAt; // f1
    f32 xUp; // r1+0x8
    f32 yUp; // f1
    f32 zUp; // f2
    f32 len; // f9
    f32 xLook; // f6
    f32 yLook; // f7
    f32 zLook; // f8
    f32 xRight; // f9
    f32 yRight; // f10
    f32 zRight; // f11
}

// Range: 0x8009120C -> 0x80091338
int osAiSetFrequency(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    unsigned int dacRate; // r1+0x8
    u8 bitRate; // r28
    unsigned int nData32; // r1+0x10
}

// Range: 0x80091100 -> 0x8009120C
int osAiSetNextBuffer(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    unsigned int size; // r31
    unsigned int nData32; // r1+0x10
}

// Range: 0x80091028 -> 0x80091100
int __osEepStatus(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    int ret; // r5
    int nSize; // r1+0x10
    u8* status; // r1+0xC
}

// Range: 0x80090FB0 -> 0x80091028
int osEepromRead(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    u8 address; // r31
    u8* buffer; // r1+0xC
}

// Range: 0x80090F38 -> 0x80090FB0
int osEepromWrite(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    u8 address; // r31
    u8* buffer; // r1+0xC
}

// Range: 0x80090E8C -> 0x80090F38
int osEepromLongRead(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r28

    // Local variables
    int length; // r31
    int ret; // r30
    u8 address; // r29
    u8* buffer; // r1+0xC
}

// Range: 0x80090DE0 -> 0x80090E8C
int osEepromLongWrite(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r28

    // Local variables
    int length; // r31
    int ret; // r30
    u8 address; // r29
    u8* buffer; // r1+0xC
}

// Range: 0x80090C78 -> 0x80090DE0
int starfoxCopy(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r25

    // Local variables
    int* A0; // r1+0x18
    int A1; // r31
    int A2; // r30
    int A3; // r29
    int T0; // r28
    int T1; // r24
    int T2; // r1+0x8
    int T3; // r23
    int T8; // r27
    int T9; // r26
    s16* pData16; // r1+0x14
    char* source; // r1+0x10
    char* target; // r1+0xC
}

// Range: 0x80090C68 -> 0x80090C78
int pictureSnap_Zelda2(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x80090B40 -> 0x80090C68
int dmaSoundRomHandler_ZELDA1(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    void* pTarget; // r1+0x18
    struct OSMesgQueue_s* mq; // r1+0x14
    unsigned int* msg; // r1+0x10
    struct __anon_0x7C62D* pIOMessage; // r1+0xC
    int first; // r30
    int msgCount; // r29
    int validCount; // r28
    int nSize; // r6
    int nAddress; // r5
    int nOffsetRAM; // r5
    int nOffsetROM; // r5
}

// Range: 0x80090AD8 -> 0x80090B40
int osViSwapBuffer_Entry(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8

    // References
    // -> static unsigned int nAddress$605;
}

// Range: 0x80090AC4 -> 0x80090AD8
int zeldaLoadSZS_Entry(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x80090AB0 -> 0x80090AC4
int zeldaLoadSZS_Exit(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x800907B0 -> 0x80090AB0
static int libraryFindException(struct __anon_0x7AE26* pLibrary, int bException) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r27
    // int bException; // r28

    // Local variables
    struct _CPU* pCPU; // r30
    struct __anon_0x79A22** apDevice; // r29
    u8* aiDevice; // r31
    unsigned int anCode[6]; // r1+0x10
}

// Range: 0x8009007C -> 0x800907B0
static int libraryFindVariables(struct __anon_0x7AE26* pLibrary) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r24

    // Local variables
    struct _CPU* pCPU; // r27
    struct __anon_0x79A22** apDevice; // r26
    u8* aiDevice; // r25
    unsigned int nAddress; // r23
    unsigned int nAddressLast; // r28
    unsigned int nOffset; // r1+0x28
    unsigned int nOpcode; // r1+0x24
    unsigned int anCode[6]; // r1+0xC
}

// Range: 0x8008FB6C -> 0x8009007C
static int libraryFindFunctions(struct __anon_0x7AE26* pLibrary) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r24

    // Local variables
    struct _CPU* pCPU; // r3
    int iFunction; // r29
    struct __anon_0x79A22** apDevice; // r28
    u8* aiDevice; // r27
    unsigned int nOpcode; // r1+0x10
    unsigned int* pnCode; // r1+0xC
    unsigned int nAddress; // r29
    unsigned int nAddressLast; // r31
    unsigned int nAddressEnqueueThread; // r26
    unsigned int nAddressDispatchThread; // r25

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}

// Erased
static int libraryCheckHandler(struct __anon_0x7AE26* pLibrary, int bException) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r31
    // int bException; // r4
}

// Range: 0x8008F584 -> 0x8008FB6C
int libraryTestFunction(struct __anon_0x7AE26* pLibrary, struct cpu_function* pFunction) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r30
    // struct cpu_function* pFunction; // r26

    // Local variables
    int iFunction; // r31
    int iData; // r24
    int bFlag; // r29
    int bDone; // r27
    int bReturn; // r21
    unsigned int iCode; // r5
    unsigned int* pnCode; // r1+0x1C
    unsigned int* pnCodeTemp; // r1+0x18
    unsigned int nSizeCode; // r1+0x8
    unsigned int nChecksum; // r1+0x14
    unsigned int nOpcode; // r1+0x8
    unsigned int nAddress; // r1+0x8

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}

// Range: 0x8008F420 -> 0x8008F584
static int librarySearch(struct __anon_0x7AE26* pLibrary, struct cpu_function* pFunction) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r29
    // struct cpu_function* pFunction; // r30
}

// Erased
static int libraryUpdate(struct __anon_0x7AE26* pLibrary) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r31

    // Local variables
    struct _CPU* pCPU; // r29
    struct cpu_function* pFunction; // r1+0xC
}

// Range: 0x8008F32C -> 0x8008F420
int libraryFunctionReplaced(int iFunction) {
    // Parameters
    // int iFunction; // r1+0x4

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}

// Range: 0x8008F234 -> 0x8008F32C
int libraryCall(struct __anon_0x7AE26* pLibrary, struct _CPU* pCPU, int iFunction) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r29
    // struct _CPU* pCPU; // r30
    // int iFunction; // r31

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}

// Range: 0x8008F0F4 -> 0x8008F234
int libraryEvent(struct __anon_0x7AE26* pLibrary, int nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r30
    // int nEvent; // r1+0xC
    // void* pArgument; // r1+0x10

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}
