/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\library.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008F0F4 -> 0x8009779C
*/

#include "dolphin/types.h"

typedef struct _XL_OBJECTTYPE {
    /* 0x0 */ char* szName;
    /* 0x4 */ s32 nSizeObject;
    /* 0x8 */ struct _XL_OBJECTTYPE* pClassBase;
    /* 0xC */ s32 (*pfEvent)(void*, s32, void*);
} __anon_0x78CD6; // size = 0x10

// size = 0x10, address = 0x800EEB0C
struct _XL_OBJECTTYPE gClassLibrary;

// size = 0x100, address = 0x800EEB1C
static u32 __osRcpImTable[64];

// size = 0x4, address = 0x80135328
static f32 dtor$466;

// size = 0x4, address = 0x8013532C
static f32 dtor$480;

// size = 0x4, address = 0x80135330
static u32 nAddress$605;

typedef struct __anon_0x78E87 {
    /* 0x0 */ s32 nOffsetHost;
    /* 0x4 */ s32 nAddressN64;
} __anon_0x78E87; // size = 0x8

typedef struct cpu_callerID {
    /* 0x0 */ s32 N64address;
    /* 0x4 */ s32 GCNaddress;
} __anon_0x78EED; // size = 0x8

typedef struct cpu_function {
    /* 0x00 */ void* pnBase;
    /* 0x04 */ void* pfCode;
    /* 0x08 */ s32 nCountJump;
    /* 0x0C */ struct __anon_0x78E87* aJump;
    /* 0x10 */ s32 nAddress0;
    /* 0x14 */ s32 nAddress1;
    /* 0x18 */ struct cpu_callerID* block;
    /* 0x1C */ s32 callerID_total;
    /* 0x20 */ s32 callerID_flag;
    /* 0x24 */ u32 nChecksum;
    /* 0x28 */ s32 timeToLive;
    /* 0x2C */ s32 memory_size;
    /* 0x30 */ s32 heapID;
    /* 0x34 */ s32 heapWhere;
    /* 0x38 */ s32 treeheapWhere;
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
    /* 0x0 */ s32 _0s32;
    /* 0x4 */ s32 s32;
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
    /* 0x0 */ u32 _0u32;
    /* 0x4 */ u32 u32;
    /* 0x0 */ u64 u64;
} __anon_0x7923C;

typedef struct __anon_0x79A22 {
    /* 0x00 */ s32 nType;
    /* 0x04 */ void* pObject;
    /* 0x08 */ s32 nOffsetAddress;
    /* 0x0C */ s32 (*pfGet8)(void*, u32, char*);
    /* 0x10 */ s32 (*pfGet16)(void*, u32, s16*);
    /* 0x14 */ s32 (*pfGet32)(void*, u32, s32*);
    /* 0x18 */ s32 (*pfGet64)(void*, u32, s64*);
    /* 0x1C */ s32 (*pfPut8)(void*, u32, char*);
    /* 0x20 */ s32 (*pfPut16)(void*, u32, s16*);
    /* 0x24 */ s32 (*pfPut32)(void*, u32, s32*);
    /* 0x28 */ s32 (*pfPut64)(void*, u32, s64*);
    /* 0x2C */ u32 nAddressPhysical0;
    /* 0x30 */ u32 nAddressPhysical1;
} __anon_0x79A22; // size = 0x34

typedef struct cpu_treeRoot {
    /* 0x00 */ u16 total;
    /* 0x04 */ s32 total_memory;
    /* 0x08 */ s32 root_address;
    /* 0x0C */ s32 start_range;
    /* 0x10 */ s32 end_range;
    /* 0x14 */ s32 cache_miss;
    /* 0x18 */ s32 cache[20];
    /* 0x68 */ struct cpu_function* left;
    /* 0x6C */ struct cpu_function* right;
    /* 0x70 */ s32 kill_limit;
    /* 0x74 */ s32 kill_number;
    /* 0x78 */ s32 side;
    /* 0x7C */ struct cpu_function* restore;
    /* 0x80 */ s32 restore_side;
} __anon_0x79CF0; // size = 0x84

typedef struct _CPU_ADDRESS {
    /* 0x0 */ s32 nN64;
    /* 0x4 */ s32 nHost;
    /* 0x8 */ struct cpu_function* pFunction;
} __anon_0x79F31; // size = 0xC

typedef struct __anon_0x79FE6 {
    /* 0x0 */ u32 nAddress;
    /* 0x4 */ u32 nOpcodeOld;
    /* 0x8 */ u32 nOpcodeNew;
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
    /* 0x00 */ u32 validCheck;
    /* 0x04 */ u32 destGPR_check;
    /* 0x08 */ s32 destGPR;
    /* 0x0C */ s32 destGPR_mapping;
    /* 0x10 */ u32 destFPR_check;
    /* 0x14 */ s32 destFPR;
    /* 0x18 */ u32 addr_check;
    /* 0x1C */ s32 addr_last;
    /* 0x20 */ u32 checkType;
    /* 0x24 */ u32 checkNext;
} __anon_0x7A483; // size = 0x28

typedef struct _CPU {
    /* 0x00000 */ s32 nMode;
    /* 0x00004 */ s32 nTick;
    /* 0x00008 */ void* pHost;
    /* 0x00010 */ s64 nLo;
    /* 0x00018 */ s64 nHi;
    /* 0x00020 */ s32 nCountAddress;
    /* 0x00024 */ s32 iDeviceDefault;
    /* 0x00028 */ u32 nPC;
    /* 0x0002C */ u32 nWaitPC;
    /* 0x00030 */ u32 nCallLast;
    /* 0x00034 */ struct cpu_function* pFunctionLast;
    /* 0x00038 */ s32 nReturnAddrLast;
    /* 0x0003C */ s32 survivalTimer;
    /* 0x00040 */ union __anon_0x7923C aGPR[32];
    /* 0x00140 */ union __anon_0x7D2DB aFPR[32];
    /* 0x00240 */ u64 aTLB[48][5];
    /* 0x009C0 */ s32 anFCR[32];
    /* 0x00A40 */ s64 anCP0[32];
    /* 0x00B40 */ s32 (*pfStep)(struct _CPU*);
    /* 0x00B44 */ s32 (*pfJump)(struct _CPU*);
    /* 0x00B48 */ s32 (*pfCall)(struct _CPU*);
    /* 0x00B4C */ s32 (*pfIdle)(struct _CPU*);
    /* 0x00B50 */ s32 (*pfRam)(struct _CPU*);
    /* 0x00B54 */ s32 (*pfRamF)(struct _CPU*);
    /* 0x00B58 */ u32 nTickLast;
    /* 0x00B5C */ u32 nRetrace;
    /* 0x00B60 */ u32 nRetraceUsed;
    /* 0x00B64 */ struct __anon_0x79A22* apDevice[256];
    /* 0x00F64 */ u8 aiDevice[65536];
    /* 0x10F64 */ void* gHeap1;
    /* 0x10F68 */ void* gHeap2;
    /* 0x10F6C */ u32 aHeap1Flag[192];
    /* 0x1126C */ u32 aHeap2Flag[13];
    /* 0x112A0 */ struct cpu_treeRoot* gTree;
    /* 0x112A4 */ struct _CPU_ADDRESS aAddressCache[256];
    /* 0x11EA4 */ s32 nCountCodeHack;
    /* 0x11EA8 */ struct __anon_0x79FE6 aCodeHack[32];
    /* 0x12028 */ s64 nTimeRetrace;
    /* 0x12030 */ struct OSAlarm alarmRetrace;
    /* 0x12058 */ u32 nFlagRAM;
    /* 0x1205C */ u32 nFlagCODE;
    /* 0x12060 */ u32 nCompileFlag;
    /* 0x12064 */ struct cpu_optimize nOptimize;
} __anon_0x7A630; // size = 0x12090

typedef struct __anon_0x7AD10 {
    /* 0x0 */ char* szName;
    /* 0x4 */ void (*pfLibrary)(struct _CPU*);
    /* 0x8 */ u32 anData[17];
} __anon_0x7AD10; // size = 0x4C

// size = 0x1008, address = 0x800EEF2C
struct __anon_0x7AD10 gaFunction[54];

typedef struct __anon_0x7AE26 {
    /* 0x00 */ s32 nFlag;
    /* 0x04 */ void* pHost;
    /* 0x08 */ s32 nAddStackSwap;
    /* 0x0C */ s32 nCountFunction;
    /* 0x10 */ s32 nAddressException;
    /* 0x14 */ struct __anon_0x7AD10* aFunction;
    /* 0x18 */ void* apData[10];
    /* 0x40 */ s32 anAddress[10];
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
    /* 0x0F8 */ u32 sr;
    /* 0x0FC */ u32 pc;
    /* 0x100 */ u32 cause;
    /* 0x104 */ u32 badvaddr;
    /* 0x108 */ u32 rcp;
    /* 0x10C */ u32 fpcsr;
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
    /* 0x04 */ s32 priority;
    /* 0x08 */ struct __OSThread_s** queue;
    /* 0x0C */ struct __OSThread_s* tlnext;
    /* 0x10 */ u16 state;
    /* 0x12 */ u16 flags;
    /* 0x14 */ s32 id;
    /* 0x18 */ s32 fp;
    /* 0x20 */ struct __anon_0x7BC50 context;
} __anon_0x7C319; // size = 0x1B0

typedef struct OSMesgQueue_s {
    /* 0x00 */ struct __OSThread_s* mtqueue;
    /* 0x04 */ struct __OSThread_s* fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
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
    /* 0x0 */ s32 _0s32;
    /* 0x4 */ s32 s32;
    /* 0x0 */ s64 s64;
    /* 0x0 */ u32 _0u32;
    /* 0x4 */ u32 u32;
    /* 0x0 */ u64 u64;
} __anon_0x7D2DB;

typedef struct __anon_0x7DB47 {
    /* 0x0 */ s32 x1;
    /* 0x4 */ s32 y1;
    /* 0x8 */ s32 x2;
    /* 0xC */ s32 y2;
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
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nWidth;
    /* 0x08 */ s32 nFormat;
    /* 0x0C */ void* pData;
    /* 0x10 */ s32 nAddress;
} __anon_0x7FA72; // size = 0x14

typedef struct __anon_0x7FBB3 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} __anon_0x7FBB3; // size = 0xC

typedef struct __anon_0x7FC23 {
    /* 0x00 */ s32 bTransformed;
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
    /* 0x00 */ s32 bTransformed;
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
    /* 0x0 */ u32 u32[1024];
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
    /* 0x00 */ s32 nMode;
    /* 0x04 */ s32 iPackPixel;
    /* 0x08 */ s32 iPackColor;
    /* 0x0C */ s32 nFrameLast;
    /* 0x10 */ s16 nSizeX;
    /* 0x12 */ s16 nSizeY;
    /* 0x14 */ u32 nAddress;
    /* 0x18 */ u32 nCodePixel;
    /* 0x1C */ u32 nCodeColor;
    /* 0x20 */ struct _FRAME_TEXTURE* pTextureNext;
    /* 0x24 */ u32 nData0;
    /* 0x28 */ u32 nData1;
    /* 0x2C */ u32 nData2;
    /* 0x30 */ u32 nData3;
    /* 0x34 */ enum _GXTexFmt eFormat;
    /* 0x38 */ struct _GXTlutObj objectTLUT;
    /* 0x44 */ struct _GXTexObj objectTexture;
    /* 0x64 */ enum _GXTexWrapMode eWrapS;
    /* 0x68 */ enum _GXTexWrapMode eWrapT;
} __anon_0x804A9; // size = 0x6C

typedef struct __anon_0x80806 {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nTMEM;
    /* 0x08 */ s32 iTLUT;
    /* 0x0C */ s32 nSizeX;
    /* 0x10 */ s32 nFormat;
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
    /* 0x28 */ u32 nCodePixel;
} __anon_0x80806; // size = 0x2C

typedef enum __anon_0x80AE8 {
    FMP_NONE = -1,
    FMP_PERSPECTIVE = 0,
    FMP_ORTHOGRAPHIC = 1,
} __anon_0x80AE8;

typedef struct __anon_0x80B6D {
    /* 0x00 */ s32 nCount;
    /* 0x04 */ f32 rScale;
    /* 0x08 */ f32 rAspect;
    /* 0x0C */ f32 rFieldOfViewY;
    /* 0x10 */ f32 rClipNear;
    /* 0x14 */ f32 rClipFar;
    /* 0x18 */ u32 nAddressFloat;
    /* 0x1C */ u32 nAddressFixed;
    /* 0x20 */ enum __anon_0x80AE8 eProjection;
} __anon_0x80B6D; // size = 0x24

typedef struct _GXColor {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} __anon_0x80D02; // size = 0x4

typedef struct __anon_0x80DBD {
    /* 0x00000 */ u32 anCIMGAddresses[8];
    /* 0x00020 */ u16 nNumCIMGAddresses;
    /* 0x00024 */ s32 bBlurOn;
    /* 0x00028 */ s32 bHackPause;
    /* 0x0002C */ s32 nHackCount;
    /* 0x00030 */ s32 nFrameCounter;
    /* 0x00034 */ s32 bPauseThisFrame;
    /* 0x00038 */ s32 bCameFromBomberNotes;
    /* 0x0003C */ s32 bInBomberNotes;
    /* 0x00040 */ s32 bShrinking;
    /* 0x00044 */ s32 bSnapShot;
    /* 0x00048 */ s32 bUsingLens;
    /* 0x0004C */ u8 cBlurAlpha;
    /* 0x00050 */ s32 bBlurredThisFrame;
    /* 0x00054 */ s32 nFrameCIMGCalls;
    /* 0x00058 */ s32 bModifyZBuffer;
    /* 0x0005C */ s32 bOverrideDepth;
    /* 0x00060 */ s32 nZBufferSets;
    /* 0x00064 */ s32 nLastFrameZSets;
    /* 0x00068 */ s32 bPauseBGDrawn;
    /* 0x0006C */ s32 bFrameOn;
    /* 0x00070 */ s32 bBackBufferDrawn;
    /* 0x00074 */ s32 bGrabbedFrame;
    /* 0x00078 */ u64* pnGBI;
    /* 0x0007C */ u32 nFlag;
    /* 0x00080 */ f32 rScaleX;
    /* 0x00084 */ f32 rScaleY;
    /* 0x00088 */ u32 nCountFrames;
    /* 0x0008C */ u32 nMode;
    /* 0x00090 */ u32 aMode[10];
    /* 0x000B8 */ struct __anon_0x7F9D8 viewport;
    /* 0x000C8 */ struct __anon_0x7FA72 aBuffer[4];
    /* 0x00118 */ u32 nOffsetDepth0;
    /* 0x0011C */ u32 nOffsetDepth1;
    /* 0x00120 */ s32 nWidthLine;
    /* 0x00124 */ f32 rDepth;
    /* 0x00128 */ f32 rDelta;
    /* 0x0012C */ s32 (*aDraw[4])(void*, void*);
    /* 0x0013C */ s32 nCountLight;
    /* 0x00140 */ struct __anon_0x7FC23 aLight[8];
    /* 0x00320 */ struct __anon_0x7FE53 lookAt;
    /* 0x00354 */ s32 nCountVertex;
    /* 0x00358 */ struct __anon_0x7FF3C aVertex[80];
    /* 0x00C18 */ struct __anon_0x80138 TMEM;
    /* 0x01C18 */ void* aPixelData;
    /* 0x01C1C */ void* aColorData;
    /* 0x01C20 */ s32 nBlocksPixel;
    /* 0x01C24 */ s32 nBlocksMaxPixel;
    /* 0x01C28 */ s32 nBlocksColor;
    /* 0x01C2C */ s32 nBlocksMaxColor;
    /* 0x01C30 */ s32 nBlocksTexture;
    /* 0x01C34 */ s32 nBlocksMaxTexture;
    /* 0x01C38 */ u32 anPackPixel[48];
    /* 0x01CF8 */ u32 anPackColor[320];
    /* 0x021F8 */ u32 nAddressLoad;
    /* 0x021FC */ u32 nCodePixel;
    /* 0x02200 */ u32 nTlutCode[16];
    /* 0x02240 */ struct _FRAME_TEXTURE aTexture[2048];
    /* 0x38240 */ u32 anTextureUsed[64];
    /* 0x38340 */ struct _FRAME_TEXTURE* apTextureCached[4096];
    /* 0x3C340 */ s32 iTileLoad;
    /* 0x3C344 */ u32 n2dLoadTexType;
    /* 0x3C348 */ s32 nLastX0;
    /* 0x3C34C */ s32 nLastY0;
    /* 0x3C350 */ s32 nLastX1;
    /* 0x3C354 */ s32 nLastY1;
    /* 0x3C358 */ struct __anon_0x80806 aTile[8];
    /* 0x3C4B8 */ s32 anSizeX[2];
    /* 0x3C4C0 */ s32 anSizeY[2];
    /* 0x3C4C8 */ s32 iHintMatrix;
    /* 0x3C4CC */ s32 iMatrixModel;
    /* 0x3C4D0 */ s32 iHintProjection;
    /* 0x3C4D4 */ f32 matrixView[4][4];
    /* 0x3C514 */ s32 iHintLast;
    /* 0x3C518 */ s32 iHintHack;
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
    /* 0x3D138 */ u32 nModeVtx;
    /* 0x3D13C */ u16* nTempBuffer;
    /* 0x3D140 */ u16* nCopyBuffer;
    /* 0x3D144 */ u32* nLensBuffer;
    /* 0x3D148 */ u16* nCameraBuffer;
} __anon_0x80DBD; // size = 0x3D150

// Range: 0x80096AB8 -> 0x8009779C
static s32 __osException(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    s32 iBit; // r3
    struct __anon_0x7AE26* pLibrary; // r1+0x8
    s64 nData64; // r1+0x28
    s64 nCause; // r1+0x20
    struct __OSThread_s* __osRunningThread; // r1+0x18
    struct __anon_0x79A22** apDevice; // r31
    u8* aiDevice; // r30
    u32 nStatus; // r22
    u32 nStatusRSP; // r1+0x14
    u32 nData32; // r1+0x10
    u32 __OSGlobalIntMask; // r23
    u32 nS0; // r18
    u32 nS1; // r17
    u32 nMask; // r1+0xC
}

// Range: 0x80096728 -> 0x80096AB8
static s32 send_mesg(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r28

    // Local variables
    struct __anon_0x7AE26* pLibrary; // r1+0x8
    struct __anon_0x79A22** apDevice; // r30
    u8* aiDevice; // r29
}

// Range: 0x8009643C -> 0x80096728
static s32 __osEnqueueAndYield(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    s64 nData64; // r1+0x18
    struct __anon_0x7AE26* pLibrary; // r3
    struct __OSThread_s* __osRunningThread; // r1+0x10
    u32 __OSGlobalIntMask; // r31
    u32 nStatus; // r1+0x8
    u32 nData32; // r5
    u32 nMask; // r1+0xC
    struct __anon_0x79A22** apDevice; // r6
    u8* aiDevice; // r7
}

// Range: 0x80096214 -> 0x8009643C
static s32 __osEnqueueThread(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    struct __anon_0x79A22** apDevice; // r31
    u8* aiDevice; // r30
}

// Range: 0x80096140 -> 0x80096214
static s32 __osPopThread(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    struct __anon_0x79A22** apDevice; // r31
    u8* aiDevice; // r30
}

// Range: 0x80095B9C -> 0x80096140
static s32 __osDispatchThread(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r27

    // Local variables
    struct __anon_0x7AE26* pLibrary; // r29
    u32 nAddress; // r5
    u64 nData64; // r0
    struct __OSThread_s* __osRunningThread; // r1+0x10
    u32 nData32; // r1+0xC
    u32 __OSGlobalIntMask; // r28
    u32 nStatus; // r6
    u32 nMask; // r6

    // References
    // -> static u32 __osRcpImTable[64];
}

// Erased
static s32 __ptException() {}

// Range: 0x80095B48 -> 0x80095B9C
static s32 osGetMemSize(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    u32 nSize; // r1+0xC
}

// Range: 0x80095AC0 -> 0x80095B48
static s32 osInvalICache(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r29

    // Local variables
    u32 nAddress; // r30
    u32 nSize; // r1+0x8
}

// Range: 0x80095A30 -> 0x80095AC0
static s32 __osDisableInt(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    u32 nStatus; // r1+0x8
    u64 nData64; // r1+0x18
}

// Range: 0x800959A4 -> 0x80095A30
static s32 __osRestoreInt(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    u64 nStatus; // r1+0x10
}

// Range: 0x80095954 -> 0x800959A4
static s32 __osSpSetStatus(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8

    // Local variables
    u32 nData32; // r1+0xC
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
    s32 nSize; // r5
    void* pBuffer; // r1+0xC
}

// Range: 0x8009584C -> 0x800958A8
void _bcopy(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    s32 nSize; // r5
    void* pSource; // r1+0x10
    void* pTarget; // r1+0xC
}

// Range: 0x800957F0 -> 0x8009584C
void _memcpy(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    s32 nSize; // r5
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
    s32 i; // r9
    s32 j; // r23
    f32 temp[4][4]; // r1+0x38
    union __anon_0x7D2DB data1; // r1+0x30
    union __anon_0x7D2DB data2; // r1+0x28
    u32* mf; // r1+0x24
    u32* nf; // r1+0x20
    u32* res; // r1+0x1C
}

// Range: 0x8009524C -> 0x80095454
void guMtxF2L(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    f32* mf; // r1+0x24
    s32 e1; // r6
    s32 e2; // r7
    s32 i; // r8
    s32 j; // r1+0x8
    s32* m; // r1+0x20
    union __anon_0x7D2DB data; // r1+0x18
    s32* ai; // r9
    s32* af; // r10
}

// Range: 0x80095178 -> 0x8009524C
void guMtxIdentF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r3

    // Local variables
    f32* mf; // r1+0x20
    s32 i; // r7
    s32 j; // r1+0x8
    union __anon_0x7D2DB data1; // r1+0x18
    union __anon_0x7D2DB data0; // r1+0x10
}

// Range: 0x800950C4 -> 0x80095178
void guMtxIdent(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r3

    // Local variables
    s32* m; // r1+0xC
}

// Range: 0x80094E54 -> 0x800950C4
void guOrthoF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    s32 i; // r8
    s32 j; // r4
    u32* mf; // r1+0x2C
    u32* sp; // r1+0x28
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
    s32* m; // r1+0x60
    s32 i; // r6
    s32 j; // r1+0x8
    s32 e1; // r7
    s32 e2; // r8
    union __anon_0x7D2DB data; // r1+0x58
    f32 mf[4][4]; // r1+0x18
    u32* sp; // r1+0x14
    s32* ai; // r9
    s32* af; // r10
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
    s32 i; // r8
    s32 j; // r4
    f32 cot; // f2
    s16* perspNorm; // r1+0x30
    u32* mf; // r1+0x2C
    u32* sp; // r1+0x28
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
    s32* m; // r1+0x60
    f32 fovy; // f30
    f32 aspect; // f29
    f32 rNear; // f28
    f32 rFar; // f27
    f32 scale; // f5
    f32 _cot; // f2
    s32 i; // r6
    s32 j; // r1+0x8
    union __anon_0x7D2DB data; // r1+0x58
    f32 mf[4][4]; // r1+0x18
    s32 e1; // r7
    s32 e2; // r8
    u32* sp; // r1+0x14
    s32* ai; // r9
    s32* af; // r10
}

// Range: 0x800945A8 -> 0x80094658
void GenPerspective_1080(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    union __anon_0x7D2DB data; // r1+0x18
    u32* mf; // r1+0x10
    u32* sp; // r1+0xC
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
    s32 i; // r8
    s32 j; // r4
    u32* mf; // r1+0x20
    union __anon_0x7D2DB data0; // r1+0x18
    union __anon_0x7D2DB data1; // r1+0x10
}

// Range: 0x80094294 -> 0x80094480
void guScale(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    f32 mf[4][4]; // r1+0x24
    s32* m; // r1+0x20
    s32 i; // r6
    s32 j; // r1+0x8
    s32 e1; // r7
    s32 e2; // r8
    union __anon_0x7D2DB data; // r1+0x18
    s32* ai; // r9
    s32* af; // r10
}

// Range: 0x80094174 -> 0x80094294
void guTranslateF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    s32 i; // r8
    s32 j; // r4
    u32* mf; // r1+0x20
    union __anon_0x7D2DB data0; // r1+0x18
    union __anon_0x7D2DB data1; // r1+0x10
}

// Range: 0x80093F88 -> 0x80094174
void guTranslate(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    s32* m; // r1+0x60
    s32 i; // r6
    s32 j; // r1+0x8
    s32 e1; // r7
    s32 e2; // r8
    union __anon_0x7D2DB data; // r1+0x58
    f32 mf[4][4]; // r1+0x14
    s32* ai; // r9
    s32* af; // r10
}

// Range: 0x80093C78 -> 0x80093F88
void guRotateF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    f32 m; // f2
    s32 i; // r8
    s32 j; // r4
    f32 a; // f31
    f32 x; // f30
    f32 y; // f29
    f32 z; // f28
    u32* mf; // r1+0x2C
    u32* sp; // r1+0x28
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
    s32* m; // r1+0x64
    u32* sp; // r1+0x60
    union __anon_0x7D2DB data; // r1+0x58
    s32 i; // r6
    s32 j; // r1+0x8
    s32 e1; // r7
    s32 e2; // r8
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
    s32* ai; // r9
    s32* af; // r10

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
    u32* mf; // r1+0x34
    u32* sp; // r1+0x30
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
    s32* m; // r1+0x2C
    u32* sp; // r1+0x28
    union __anon_0x7D2DB data; // r1+0x20
    s32 i; // r6
    s32 j; // r1+0x8
    s32 e1; // r7
    s32 e2; // r8
    s32* ai; // r9
    s32* af; // r10
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
static s32 __float2int(f32 x) {
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
    u32* mf; // r1+0x2C
    u32* sp; // r1+0x28
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
    s32 twidth; // r6
    s32 theight; // r7
}

// Range: 0x80091E60 -> 0x80092834
void guLookAtHilite(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    struct __anon_0x7D2A5* l; // r1+0x84
    union __anon_0x7DBF9* h; // r1+0x80
    s32 i; // r7
    s32 j; // r1+0x8
    s32 e1; // r5
    s32 e2; // r8
    union __anon_0x7D2DB data; // r1+0x78
    f32 mf[4][4]; // r1+0x38
    u32* m; // r1+0x34
    u32* sp; // r1+0x30
    s32* ai; // r9
    s32* af; // r10
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
    s32 twidth; // r6
    s32 theight; // r7
}

// Range: 0x8009190C -> 0x80091E60
void guLookAtReflectF(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    struct __anon_0x7D2A5* l; // r1+0x28
    union __anon_0x7D2DB data; // r1+0x20
    u32* mf; // r1+0x1C
    u32* sp; // r1+0x18
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
    s32 i; // r7
    s32 j; // r1+0x8
    s32 e1; // r5
    s32 e2; // r8
    union __anon_0x7D2DB data; // r1+0x68
    f32 mf[4][4]; // r1+0x28
    u32* m; // r1+0x24
    u32* sp; // r1+0x20
    s32* ai; // r9
    s32* af; // r10
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
s32 osAiSetFrequency(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    u32 dacRate; // r1+0x8
    u8 bitRate; // r28
    u32 nData32; // r1+0x10
}

// Range: 0x80091100 -> 0x8009120C
s32 osAiSetNextBuffer(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    u32 size; // r31
    u32 nData32; // r1+0x10
}

// Range: 0x80091028 -> 0x80091100
s32 __osEepStatus(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    s32 ret; // r5
    s32 nSize; // r1+0x10
    u8* status; // r1+0xC
}

// Range: 0x80090FB0 -> 0x80091028
s32 osEepromRead(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    u8 address; // r31
    u8* buffer; // r1+0xC
}

// Range: 0x80090F38 -> 0x80090FB0
s32 osEepromWrite(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r30

    // Local variables
    u8 address; // r31
    u8* buffer; // r1+0xC
}

// Range: 0x80090E8C -> 0x80090F38
s32 osEepromLongRead(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r28

    // Local variables
    s32 length; // r31
    s32 ret; // r30
    u8 address; // r29
    u8* buffer; // r1+0xC
}

// Range: 0x80090DE0 -> 0x80090E8C
s32 osEepromLongWrite(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r28

    // Local variables
    s32 length; // r31
    s32 ret; // r30
    u8 address; // r29
    u8* buffer; // r1+0xC
}

// Range: 0x80090C78 -> 0x80090DE0
s32 starfoxCopy(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r25

    // Local variables
    s32* A0; // r1+0x18
    s32 A1; // r31
    s32 A2; // r30
    s32 A3; // r29
    s32 T0; // r28
    s32 T1; // r24
    s32 T2; // r1+0x8
    s32 T3; // r23
    s32 T8; // r27
    s32 T9; // r26
    s16* pData16; // r1+0x14
    char* source; // r1+0x10
    char* target; // r1+0xC
}

// Range: 0x80090C68 -> 0x80090C78
s32 pictureSnap_Zelda2(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x80090B40 -> 0x80090C68
s32 dmaSoundRomHandler_ZELDA1(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r31

    // Local variables
    void* pTarget; // r1+0x18
    struct OSMesgQueue_s* mq; // r1+0x14
    u32* msg; // r1+0x10
    struct __anon_0x7C62D* pIOMessage; // r1+0xC
    s32 first; // r30
    s32 msgCount; // r29
    s32 validCount; // r28
    s32 nSize; // r6
    s32 nAddress; // r5
    s32 nOffsetRAM; // r5
    s32 nOffsetROM; // r5
}

// Range: 0x80090AD8 -> 0x80090B40
s32 osViSwapBuffer_Entry(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x8

    // References
    // -> static u32 nAddress$605;
}

// Range: 0x80090AC4 -> 0x80090AD8
s32 zeldaLoadSZS_Entry(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x80090AB0 -> 0x80090AC4
s32 zeldaLoadSZS_Exit(struct _CPU* pCPU) {
    // Parameters
    // struct _CPU* pCPU; // r1+0x0
}

// Range: 0x800907B0 -> 0x80090AB0
static s32 libraryFindException(struct __anon_0x7AE26* pLibrary, s32 bException) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r27
    // s32 bException; // r28

    // Local variables
    struct _CPU* pCPU; // r30
    struct __anon_0x79A22** apDevice; // r29
    u8* aiDevice; // r31
    u32 anCode[6]; // r1+0x10
}

// Range: 0x8009007C -> 0x800907B0
static s32 libraryFindVariables(struct __anon_0x7AE26* pLibrary) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r24

    // Local variables
    struct _CPU* pCPU; // r27
    struct __anon_0x79A22** apDevice; // r26
    u8* aiDevice; // r25
    u32 nAddress; // r23
    u32 nAddressLast; // r28
    u32 nOffset; // r1+0x28
    u32 nOpcode; // r1+0x24
    u32 anCode[6]; // r1+0xC
}

// Range: 0x8008FB6C -> 0x8009007C
static s32 libraryFindFunctions(struct __anon_0x7AE26* pLibrary) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r24

    // Local variables
    struct _CPU* pCPU; // r3
    s32 iFunction; // r29
    struct __anon_0x79A22** apDevice; // r28
    u8* aiDevice; // r27
    u32 nOpcode; // r1+0x10
    u32* pnCode; // r1+0xC
    u32 nAddress; // r29
    u32 nAddressLast; // r31
    u32 nAddressEnqueueThread; // r26
    u32 nAddressDispatchThread; // r25

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}

// Erased
static s32 libraryCheckHandler(struct __anon_0x7AE26* pLibrary, s32 bException) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r31
    // s32 bException; // r4
}

// Range: 0x8008F584 -> 0x8008FB6C
s32 libraryTestFunction(struct __anon_0x7AE26* pLibrary, struct cpu_function* pFunction) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r30
    // struct cpu_function* pFunction; // r26

    // Local variables
    s32 iFunction; // r31
    s32 iData; // r24
    s32 bFlag; // r29
    s32 bDone; // r27
    s32 bReturn; // r21
    u32 iCode; // r5
    u32* pnCode; // r1+0x1C
    u32* pnCodeTemp; // r1+0x18
    u32 nSizeCode; // r1+0x8
    u32 nChecksum; // r1+0x14
    u32 nOpcode; // r1+0x8
    u32 nAddress; // r1+0x8

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}

// Range: 0x8008F420 -> 0x8008F584
static s32 librarySearch(struct __anon_0x7AE26* pLibrary, struct cpu_function* pFunction) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r29
    // struct cpu_function* pFunction; // r30
}

// Erased
static s32 libraryUpdate(struct __anon_0x7AE26* pLibrary) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r31

    // Local variables
    struct _CPU* pCPU; // r29
    struct cpu_function* pFunction; // r1+0xC
}

// Range: 0x8008F32C -> 0x8008F420
s32 libraryFunctionReplaced(s32 iFunction) {
    // Parameters
    // s32 iFunction; // r1+0x4

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}

// Range: 0x8008F234 -> 0x8008F32C
s32 libraryCall(struct __anon_0x7AE26* pLibrary, struct _CPU* pCPU, s32 iFunction) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r29
    // struct _CPU* pCPU; // r30
    // s32 iFunction; // r31

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}

// Range: 0x8008F0F4 -> 0x8008F234
s32 libraryEvent(struct __anon_0x7AE26* pLibrary, s32 nEvent, void* pArgument) {
    // Parameters
    // struct __anon_0x7AE26* pLibrary; // r30
    // s32 nEvent; // r1+0xC
    // void* pArgument; // r1+0x10

    // References
    // -> struct __anon_0x7AD10 gaFunction[54];
}
