#include "emulator/library.h"
#include "emulator/audio.h"
#include "emulator/cpu.h"
#include "emulator/frame.h"
#include "emulator/library_jumptables.h"
#include "emulator/peripheral.h"
#include "emulator/ram.h"
#include "emulator/rsp.h"
#include "emulator/serial.h"
#include "emulator/system.h"
#include "emulator/video.h"
#include "emulator/xlPostGCN.h"
#include "libc/math.h"
#include "macros.h"

char D_800EEB00[] = "OS-LIBRARY";

_XL_OBJECTTYPE gClassLibrary = {
    D_800EEB00,
    sizeof(Library),
    NULL,
    (EventFunc)libraryEvent,
};

static u32 __osRcpImTable[] = {
    0x00000555, 0x00000556, 0x00000559, 0x0000055A, 0x00000565, 0x00000566, 0x00000569, 0x0000056A,
    0x00000595, 0x00000596, 0x00000599, 0x0000059A, 0x000005A5, 0x000005A6, 0x000005A9, 0x000005AA,
    0x00000655, 0x00000656, 0x00000659, 0x0000065A, 0x00000665, 0x00000666, 0x00000669, 0x0000066A,
    0x00000695, 0x00000696, 0x00000699, 0x0000069A, 0x000006A5, 0x000006A6, 0x000006A9, 0x000006AA,
    0x00000955, 0x00000956, 0x00000959, 0x0000095A, 0x00000965, 0x00000966, 0x00000969, 0x0000096A,
    0x00000995, 0x00000996, 0x00000999, 0x0000099A, 0x000009A5, 0x000009A6, 0x000009A9, 0x000009AA,
    0x00000A55, 0x00000A56, 0x00000A59, 0x00000A5A, 0x00000A65, 0x00000A66, 0x00000A69, 0x00000A6A,
    0x00000A95, 0x00000A96, 0x00000A99, 0x00000A9A, 0x00000AA5, 0x00000AA6, 0x00000AA9, 0x00000AAA,
};

static f32 dtor_466 = 0.01745329238474369;
static f32 dtor_480 = 0.01745329238474369;
static u32 nAddress = 0xFFFFFFFF;

LibraryFunc gaFunction[54] = {
    {
        "send_mesg",
        (LibraryFuncImpl)send_mesg,
        {0},
    },
    {
        "__osEnqueueAndYield",
        (LibraryFuncImpl)__osEnqueueAndYield,
        {0},
    },
    {
        "__osEnqueueThread",
        (LibraryFuncImpl)__osEnqueueThread,
        {0},
    },
    {
        "__osPopThread",
        (LibraryFuncImpl)__osPopThread,
        {0},
    },
    {
        "__osDispatchThread",
        (LibraryFuncImpl)__osDispatchThread,
        {0},
    },
    {
        "osGetMemSize",
        (LibraryFuncImpl)osGetMemSize,
        {0x00000045, 0xE82F9DC4},
    },
    {
        "osInvalDCache",
        NULL,
        {0x0000002C, 0x384D2C37, 0x0000002B, 0x3954FA00},
    },
    {
        "osInvalICache",
        (LibraryFuncImpl)osInvalICache,
        {0x0000001D, 0x376979EF, 0x0000001D, 0x3769A92F},
    },
    {
        "osWritebackDCache",
        NULL,
        {0x0000001D, 0x376979EF},
    },
    {
        "osWritebackDCacheAll",
        NULL,
        {0x0000000A, 0x0F38926F},
    },
    {
        "__osDisableInt",
        (LibraryFuncImpl)__osDisableInt,
        {0x00000020, 0x3F5B05D4, 0x00000022, 0x3F5B35D1, 0x00000008, 0x10310240, 0x0000000C, 0x10310300},
    },
    {
        "__osRestoreInt",
        (LibraryFuncImpl)__osRestoreInt,
        {0x00000007, 0x10000400},
    },
    {
        "__osSpSetStatus",
        (LibraryFuncImpl)__osSpSetStatus,
        {0x00000003, 0x0000F02B, 0x00000004, 0x003CD02B, 0x0000000B, 0x5604E8E1},
    },
    {
        "__cosf",
        (LibraryFuncImpl)__cosf,
        {0x0000007E, 0x0EA800A6, 0x0000005A, 0xA7BF8A16, 0x0000008E, 0x417938C2, 0x000002B5, 0x82283827},
    },
    {
        "__sinf",
        (LibraryFuncImpl)__sinf,
        {0x0000007D, 0x9DDC3AD1, 0x00000070, 0x972CC1AA, 0x000000AB, 0x537273BE, 0x00000090, 0xA23718AB},
    },
    {
        "bzero",
        (LibraryFuncImpl)_bzero,
        {0x00000028, 0x6A68DD7D, 0x00000027, 0x6A68E5DB},
    },
    {
        "bcopy",
        (LibraryFuncImpl)_bcopy,
        {0x000000CE, 0xFF1D6C61, 0x000000F0, 0x082F2020, 0x000000C7, 0xB1771900, 0x000000C7, 0xC732F943},
    },
    {
        "memcpy",
        (LibraryFuncImpl)_memcpy,
        {0x00000026, 0xC912B3A8},
    },
    {
        "osVirtualToPhysical",
        (LibraryFuncImpl)osVirtualToPhysical,
        {0x00000037, 0x5F70CFD6, 0x00000015, 0x17E44014},
    },
    {
        "osPhysicalToVirtual",
        (LibraryFuncImpl)osPhysicalToVirtual,
        {0x0000000D, 0x2B8FBACB, 0x00000003, 0x0000F000},
    },
    {
        "guMtxF2L",
        (LibraryFuncImpl)guMtxF2L,
        {0x00000026, 0x686C0856, 0x00000019, 0x7CC68902, 0x00000040, 0x4425DE45, 0x0000005C, 0x220BB2B0, 0x00000027,
         0x60FF87FD},
    },
    {
        "guMtxCatF",
        (LibraryFuncImpl)guMtxCatF,
        {0x00000037, 0x91255B90},
    },
    {
        "guMtxIdentF",
        (LibraryFuncImpl)guMtxIdentF,
        {0x00000014, 0x14BCF092, 0x00000022, 0x69E2607E, 0x0000003B, 0x03585A21},
    },
    {
        "guMtxIdent",
        (LibraryFuncImpl)guMtxIdent,
        {0x0000003C, 0xA20CBF46},
    },
    {
        "guOrthoF",
        (LibraryFuncImpl)guOrthoF,
        {0x00000055, 0x7F37D860, 0x00000080, 0x7C65E2F4},
    },
    {
        "guOrtho",
        (LibraryFuncImpl)guOrtho,
        {0x0000001A, 0xB0EC9807, 0x00000053, 0xA76A660F},
    },
    {
        "guPerspectiveF",
        (LibraryFuncImpl)guPerspectiveF,
        {0x0000008C, 0x9EC5FEAB},
    },
    {
        "guPerspective",
        (LibraryFuncImpl)guPerspective,
        {0x00000072, 0x2B0214E7, 0x00000016, 0x99A85378, 0x0000001B, 0x8CC9B39E},
    },
    {
        "guScaleF",
        (LibraryFuncImpl)guScaleF,
        {0x00000015, 0xCA91FB16, 0x00000018, 0x8497864D, 0x00000020, 0xBC8FF165},
    },
    {
        "guScale",
        (LibraryFuncImpl)guScale,
        {0x0000001F, 0xA2C19EFB, 0x00000012, 0x3E48EAE5},
    },
    {
        "guRotateF",
        (LibraryFuncImpl)guRotateF,
        {0x00000065, 0xD5CF8FAE, 0x00000057, 0xFA3518F4, 0x00000093, 0x9AA6B979},
    },
    {
        "guRotate",
        (LibraryFuncImpl)guRotate,
        {0x0000005E, 0x06A7BCE6, 0x00000014, 0x698E4905, 0x00000017, 0x36AEAFA5},
    },
    {
        "guTranslateF",
        (LibraryFuncImpl)guTranslateF,
        {0x0000001B, 0xC211F512},
    },
    {
        "guTranslate",
        (LibraryFuncImpl)guTranslate,
        {0x0000001C, 0x80FA01A4, 0x00000015, 0x71F205A8},
    },
    {
        "guLookAtF",
        (LibraryFuncImpl)guLookAtF,
        {0x00000107, 0xB11E3841},
    },
    {
        "guLookAt",
        (LibraryFuncImpl)guLookAt,
        {0x000000E1, 0xE544558C},
    },
    {
        "guLookAtHiliteF",
        (LibraryFuncImpl)guLookAtHiliteF,
        {0x000002E9, 0xCA0CCB5F},
    },
    {
        "guLookAtHilite",
        (LibraryFuncImpl)guLookAtHilite,
        {0x00000035, 0xC2E98EC2, 0x00000035, 0x6B82DCD5},
    },
    {
        "guLookAtReflectF",
        (LibraryFuncImpl)guLookAtReflectF,
        {0x0000015E, 0x55ACFC31, 0x000001BF, 0xBFD63279},
    },
    {
        "guLookAtReflect",
        (LibraryFuncImpl)guLookAtReflect,
        {0x0000001B, 0xD6F88212, 0x00000023, 0xD70B815D},
    },
    {
        "osAiSetFrequency",
        (LibraryFuncImpl)osAiSetFrequency,
        {0x00000046, 0x88F8FC90, 0x00000058, 0xA177D03D, 0x00000051, 0xD3B85DEF},
    },
    {
        "osAiSetNextBuffer",
        (LibraryFuncImpl)osAiSetNextBuffer,
        {0x00000025, 0x5ACF0804, 0x0000002A, 0x978F50F1, 0x0000001D, 0x47200DC9},
    },
    {
        "__osEepStatus",
        (LibraryFuncImpl)__osEepStatus,
        {0x000000A8, 0x8FBCE3BC, 0x00000067, 0x9870CAC4, 0x00000089, 0x807A196A},
    },
    {
        "osEepromRead",
        (LibraryFuncImpl)osEepromRead,
        {0x00000066, 0x380B07CA, 0x000000A5, 0x947050BF, 0x0000007C, 0x66EC38E8},
    },
    {
        "osEepromWrite",
        (LibraryFuncImpl)osEepromWrite,
        {0x0000005A, 0x5FCCA978, 0x00000080, 0xF6971795, 0x0000006C, 0x07B6DF06},
    },
    {
        "osEepromLongRead",
        (LibraryFuncImpl)osEepromLongRead,
        {0x0000001C, 0x63BA7FE0, 0x0000002E, 0xF25B283A, 0x0000004F, 0x5B919EF9},
    },
    {
        "osEepromLongWrite",
        (LibraryFuncImpl)osEepromLongWrite,
        {0x00000039, 0xED7A2E0B, 0x00000044, 0xF6B9E6BD, 0x0000004F, 0x5B919EF9},
    },
    {
        "starfoxCopy",
        (LibraryFuncImpl)starfoxCopy,
        {0x00000026, 0x158C0203},
    },
    {
        "GenPerspective",
        (LibraryFuncImpl)GenPerspective_1080,
        {0x0000002F, 0x3879CA27},
    },
    {
        "pictureSnap_Zelda2",
        (LibraryFuncImpl)pictureSnap_Zelda2,
        {0x000001F0, 0xC2739708},
    },
    {
        "dmaSoundRomHandler_ZELDA1",
        (LibraryFuncImpl)dmaSoundRomHandler_ZELDA1,
        {0x0000001D, 0x7C4D46F6, 0x00000008, 0x008D2AC3},
    },
    {
        "osViSwapBuffer_Entry",
        (LibraryFuncImpl)osViSwapBuffer_Entry,
        {0x00000011, 0x5147109A, 0x00000038, 0xBF405C09, 0x00000014, 0x745C58FD, 0x00000013, 0x6467CCEE},
    },
    {
        "zeldaLoadSZS_Entry",
        (LibraryFuncImpl)zeldaLoadSZS_Entry,
        {0x0000005A, 0x8EA707A2},
    },
    {
        "zeldaLoadSZS_Exit",
        (LibraryFuncImpl)zeldaLoadSZS_Exit,
        {0},
    },
};

char D_800EFF34[] = "TestFunction: INTERNAL ERROR: osViSwapBuffer: No ADDIU opcode: 0x%08x";
char D_800EFF7C[] = "library.c";

#ifndef NON_MATCHING
// __osException
void* jtbl_800EFF88[9] = {
    &lbl_80097620, &lbl_800971AC, &lbl_80097208, &lbl_80097264, &lbl_80097488,
    &lbl_800974A0, &lbl_800974B4, &lbl_800974BC, &lbl_800974C4,
};
#else
void* jtbl_800EFF88[9] = {0};
#endif

const f32 D_80136078 = 0.5f;
const f32 D_8013607C = 48681812.0f;
const f64 D_80136080 = 4503599627370496.0;
const f32 D_80136088 = 0.0f;
const f64 D_80136090 = 0.5;
const f64 D_80136098 = 3.0;
const f32 D_801360A0 = -1.0f;
const f32 D_801360A4 = 1.0f;
const f32 D_801360A8 = 128.0f;
const f32 D_801360AC = 127.0f;
const f32 D_801360B0 = 65536.0f;
const f64 D_801360B8 = 0.1;
const f32 D_801360C0 = 2.0f;
const f64 D_801360C8 = 4503601774854144.0;
const f32 D_801360D0 = 0.01745329238474369f;
const f32 D_801360D4 = -2.0f;

typedef union __OSfp_s {
    struct {
        /* 0x0 */ f32 f_odd;
        /* 0x4 */ f32 f_even;
    } f;
    f64 d;
    s64 u64;
} __OSfp_s;

typedef struct __OSThreadContext_s {
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
    /* 0x110 */ __OSfp_s fp0;
    /* 0x118 */ __OSfp_s fp2;
    /* 0x120 */ __OSfp_s fp4;
    /* 0x128 */ __OSfp_s fp6;
    /* 0x130 */ __OSfp_s fp8;
    /* 0x138 */ __OSfp_s fp10;
    /* 0x140 */ __OSfp_s fp12;
    /* 0x148 */ __OSfp_s fp14;
    /* 0x150 */ __OSfp_s fp16;
    /* 0x158 */ __OSfp_s fp18;
    /* 0x160 */ __OSfp_s fp20;
    /* 0x168 */ __OSfp_s fp22;
    /* 0x170 */ __OSfp_s fp24;
    /* 0x178 */ __OSfp_s fp26;
    /* 0x180 */ __OSfp_s fp28;
    /* 0x188 */ __OSfp_s fp30;
} __OSThreadContext_s; // size = 0x190

typedef struct __OSThread_s __OSThread_s;

struct __OSThread_s {
    /* 0x00 */ __OSThread_s* next;
    /* 0x04 */ s32 priority;
    /* 0x08 */ __OSThread_s** queue;
    /* 0x0C */ __OSThread_s* tlnext;
    /* 0x10 */ u16 state;
    /* 0x12 */ u16 flags;
    /* 0x14 */ s32 id;
    /* 0x18 */ s32 fp;
    /* 0x20 */ __OSThreadContext_s context;
}; // size = 0x1B0

typedef struct OSMesgQueue_s {
    /* 0x00 */ __OSThread_s* mtqueue;
    /* 0x04 */ __OSThread_s* fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ void* msg;
} OSMesgQueue_s; // size = 0x18

typedef struct OSIoMesgHdr_s {
    /* 0x0 */ u16 type;
    /* 0x2 */ u8 pri;
    /* 0x3 */ u8 status;
    /* 0x4 */ OSMesgQueue_s* retQueue;
} OSIoMesgHdr_s; // size = 0x8

typedef struct OSIoMesg_s {
    /* 0x00 */ OSIoMesgHdr_s hdr;
    /* 0x08 */ void* dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ void* piHandle;
} OSIoMesg_s; // size = 0x18

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/__osException.s")
#else
s32 __osException(Cpu* pCPU) {
    s32 iBit;
    Library* pLibrary;
    s64 nData64;
    s64 nCause;
    __OSThread_s* __osRunningThread;
    CpuDevice** apDevice;
    u8* aiDevice;
    u32 nStatus;
    u32 nStatusRSP;
    u32 nData32;
    u32 __OSGlobalIntMask;
    u32 nS0;
    u32 nS1;
    u32 nMask;

    apDevice = pCPU->apDevice;
    aiDevice = pCPU->aiDevice;
    pLibrary = SYSTEM_LIBRARY(pCPU->pHost);

    nData32 = *(u32*)pLibrary->apData[3];
    __OSGlobalIntMask = nData32;

    if (!cpuGetRegisterCP0(pCPU, 12, &nData64)) {
        return 0;
    }
    nStatus = nData64;
    if (!cpuSetRegisterCP0(pCPU, 12, nData64 & ~3)) {
        return 0;
    }

    CPU_DEVICE_GET32(apDevice, aiDevice, pLibrary->anAddress[8], &pCPU->aGPR[26].u32);
    if (!cpuGetAddressBuffer(pCPU, &__osRunningThread, pCPU->aGPR[26].u32)) {
        return 0;
    }

    __osRunningThread->context.at = pCPU->aGPR[1].u64;
    __osRunningThread->context.sr = nStatus;
    __osRunningThread->context.t0 = pCPU->aGPR[8].u64;
    __osRunningThread->context.t1 = pCPU->aGPR[9].u64;
    __osRunningThread->context.t2 = pCPU->aGPR[10].u64;
    __osRunningThread->context.v0 = pCPU->aGPR[2].u64;
    __osRunningThread->context.v1 = pCPU->aGPR[3].u64;
    __osRunningThread->context.a0 = pCPU->aGPR[4].u64;
    __osRunningThread->context.a1 = pCPU->aGPR[5].u64;
    __osRunningThread->context.a2 = pCPU->aGPR[6].u64;
    __osRunningThread->context.a3 = pCPU->aGPR[7].u64;
    __osRunningThread->context.t3 = pCPU->aGPR[11].u64;
    __osRunningThread->context.t4 = pCPU->aGPR[12].u64;
    __osRunningThread->context.t5 = pCPU->aGPR[13].u64;
    __osRunningThread->context.t6 = pCPU->aGPR[14].u64;
    __osRunningThread->context.t7 = pCPU->aGPR[15].u64;
    __osRunningThread->context.s0 = pCPU->aGPR[16].u64;
    __osRunningThread->context.s1 = pCPU->aGPR[17].u64;
    __osRunningThread->context.s2 = pCPU->aGPR[18].u64;
    __osRunningThread->context.s3 = pCPU->aGPR[19].u64;
    __osRunningThread->context.s4 = pCPU->aGPR[20].u64;
    __osRunningThread->context.s5 = pCPU->aGPR[21].u64;
    __osRunningThread->context.s6 = pCPU->aGPR[22].u64;
    __osRunningThread->context.s7 = pCPU->aGPR[23].u64;
    __osRunningThread->context.t8 = pCPU->aGPR[24].u64;
    __osRunningThread->context.t9 = pCPU->aGPR[25].u64;
    __osRunningThread->context.gp = pCPU->aGPR[28].u64;
    __osRunningThread->context.sp = pCPU->aGPR[29].u64;
    __osRunningThread->context.s8 = pCPU->aGPR[30].u64;
    __osRunningThread->context.ra = pCPU->aGPR[31].u64;
    __osRunningThread->context.lo = pCPU->nLo;
    __osRunningThread->context.hi = pCPU->nHi;

    if (nStatus & 0xFF00) {
        nData32 = ~__OSGlobalIntMask;
        nData32 &= 0xFF00;
        nData32 |= nStatus & 0xFF00;
        nData32 |= nStatus & 0xFFFF00FF;
        __osRunningThread->context.sr = nData32;

        nStatus &= (__OSGlobalIntMask & 0xFF00) | 0xFFFF00FF;
    }

    if (!mipsGet32(SYSTEM_MIPS(pCPU->pHost), 0xA430000C, (s32*)&nMask)) {
        return 0;
    }

    if (nMask != 0) {
        nData32 = __OSGlobalIntMask;
        nData32 >>= 16;
        nData32 = ~nData32;
        nData32 &= 0x3F;
        nData32 &= __osRunningThread->context.rcp;
        nMask |= nData32;
    }
    __osRunningThread->context.rcp = nMask;

    nData32 = pCPU->anCP0[14];
    __osRunningThread->context.pc = nData32;

    __osRunningThread->context.fpcsr = pCPU->anFCR[31];
    __osRunningThread->context.fp0.u64 = pCPU->aFPR[0].u64;
    __osRunningThread->context.fp2.u64 = pCPU->aFPR[2].u64;
    __osRunningThread->context.fp4.u64 = pCPU->aFPR[4].u64;
    __osRunningThread->context.fp6.u64 = pCPU->aFPR[6].u64;
    __osRunningThread->context.fp8.u64 = pCPU->aFPR[8].u64;
    __osRunningThread->context.fp10.u64 = pCPU->aFPR[10].u64;
    __osRunningThread->context.fp12.u64 = pCPU->aFPR[12].u64;
    __osRunningThread->context.fp14.u64 = pCPU->aFPR[14].u64;
    __osRunningThread->context.fp16.u64 = pCPU->aFPR[16].u64;
    __osRunningThread->context.fp18.u64 = pCPU->aFPR[18].u64;
    __osRunningThread->context.fp20.u64 = pCPU->aFPR[20].u64;
    __osRunningThread->context.fp22.u64 = pCPU->aFPR[22].u64;
    __osRunningThread->context.fp24.u64 = pCPU->aFPR[24].u64;
    __osRunningThread->context.fp26.u64 = pCPU->aFPR[26].u64;
    __osRunningThread->context.fp28.u64 = pCPU->aFPR[28].u64;
    __osRunningThread->context.fp30.u64 = pCPU->aFPR[30].u64;

    if (!cpuGetRegisterCP0(pCPU, 13, &nCause)) {
        return 0;
    }

    nData32 = nCause;
    __osRunningThread->context.cause = nData32;

    __osRunningThread->state = 2;
    switch ((nCause & 0x7C) >> 2) {
        case 0: // interrupt
            nS0 = nStatus & nCause;
            while (TRUE) {
                iBit = 0;
                if (nS0 & 0x100) {
                    iBit = 1;
                }
                if (nS0 & 0x200) {
                    iBit = 2;
                }
                if (nS0 & 0x400) {
                    iBit = 3;
                }
                if (nS0 & 0x800) {
                    iBit = 4;
                }
                if (nS0 & 0x1000) {
                    iBit = 5;
                }
                if (nS0 & 0x2000) {
                    iBit = 6;
                }
                if (nS0 & 0x4000) {
                    iBit = 7;
                }
                if (nS0 & 0x8000) {
                    iBit = 8;
                }
                switch (iBit) {
                    case 1:
                        nCause &= ~0x100;
                        if (!cpuSetRegisterCP0(pCPU, 13, nCause)) {
                            return 0;
                        }
                        pCPU->aGPR[4].u32 = 0;
                        send_mesg(pCPU);
                        nS0 &= ~0x100;
                        break;
                    case 2:
                        nCause &= ~0x200;
                        if (!cpuSetRegisterCP0(pCPU, 13, nCause)) {
                            return 0;
                        }
                        pCPU->aGPR[4].u32 = 8;
                        send_mesg(pCPU);
                        nS0 &= ~0x200;
                        break;
                    case 3:
                        if (!mipsGet32(SYSTEM_MIPS(pCPU->pHost), 0xA4300008, (s32*)&nData32)) {
                            return 0;
                        }

                        nS1 = (__OSGlobalIntMask >> 16) & nData32;

                        if (nS1 & 1) {
                            nS1 &= 0x3E;
                            if (!rspGet32(SYSTEM_RSP(pCPU->pHost), 0x04040010, (s32*)&nStatusRSP)) {
                                return 0;
                            }
                            nData32 = 0x8008;
                            if (!rspPut32(SYSTEM_RSP(pCPU->pHost), 0x04040010, (s32*)&nData32)) {
                                return 0;
                            }
                            if (nStatusRSP & 0x300) {
                                pCPU->aGPR[4].u32 = 0x20;
                                send_mesg(pCPU);
                            } else {
                                pCPU->aGPR[4].u32 = 0x58;
                                send_mesg(pCPU);
                            }
                        }

                        if (nS1 & 8) {
                            nData32 = 0;
                            nS1 &= 0x37;
                            if (!videoPut32(SYSTEM_VIDEO(pCPU->pHost), 0xA4400010, (s32*)&nData32)) {
                                return 0;
                            }
                            pCPU->aGPR[4].u32 = 0x38;
                            send_mesg(pCPU);
                        }

                        if (nS1 & 4) {
                            nData32 = 1;
                            nS1 &= 0x3B;
                            if (!audioPut32(SYSTEM_AUDIO(pCPU->pHost), 0xA450000C, (s32*)&nData32)) {
                                return 0;
                            }
                            pCPU->aGPR[4].u32 = 0x30;
                            send_mesg(pCPU);
                        }

                        if (nS1 & 2) {
                            nData32 = 0;
                            nS1 &= 0x3D;
                            if (!serialPut32(SYSTEM_SERIAL(pCPU->pHost), 0xA4800018, (s32*)&nData32)) {
                                return 0;
                            }
                            pCPU->aGPR[4].u32 = 0x28;
                            send_mesg(pCPU);
                        }

                        if (nS1 & 0x10) {
                            nData32 = 2;
                            nS1 &= 0x2F;
                            if (!peripheralPut32(SYSTEM_PERIPHERAL(pCPU->pHost), 0xA4600010, (s32*)&nData32)) {
                                return 0;
                            }
                            pCPU->aGPR[4].u32 = 0x40;
                            send_mesg(pCPU);
                        }

                        if (nS1 & 0x20) {
                            nData32 = 0x800;
                            if (!mipsPut32(SYSTEM_MIPS(pCPU->pHost), 0xA4300000, (s32*)&nData32)) {
                                return 0;
                            }
                            pCPU->aGPR[4].u32 = 0x48;
                            send_mesg(pCPU);
                        }

                        nS0 &= ~0x400;
                        break;
                    case 4:
                        pCPU->aGPR[4].u32 = 0x10;
                        nS0 &= ~0x800;
                        send_mesg(pCPU);
                        break;
                    case 5:
                        __osRunningThread->context.sr &= ~0x1000;
                        goto redispatch;
                    case 6:
                        nS0 &= ~0x2000;
                        break;
                    case 7:
                        nS0 &= ~0x4000;
                        break;
                    case 8:
                        if (!cpuGetRegisterCP0(pCPU, 11, &nData64)) {
                            return 0;
                        }
                        if (!cpuSetRegisterCP0(pCPU, 11, nData64)) {
                            return 0;
                        }
                        pCPU->aGPR[4].u32 = 0x18;
                        send_mesg(pCPU);
                        nS0 &= ~0x8000;
                        break;
                    default:
                        goto redispatch;
                }
            }
            break;
        case 9: // break
            __osRunningThread->flags = 1;
            pCPU->aGPR[4].u32 = 0x50;
            send_mesg(pCPU);
            goto redispatch;
        case 11: // coprocessor unusable
            __osRunningThread->fp = 1;
            if (!cpuGetRegisterCP0(pCPU, 12, &nData64)) {
                return 0;
            }
            nData64 |= 0x20000000;
            if (!cpuSetRegisterCP0(pCPU, 12, nData64)) {
                return 0;
            }
            goto enqueueRunning;
        default:
            *(s32*)pLibrary->apData[7] = pCPU->aGPR[26].s32;
            __osRunningThread->state = 1;
            __osRunningThread->flags = 2;
            if (!cpuGetRegisterCP0(pCPU, 8, &nData64)) {
                return 0;
            }
            nData32 = nData64;
            __osRunningThread->context.badvaddr = nData32;
            pCPU->aGPR[4].u32 = 0x60;
            send_mesg(pCPU);
            __osDispatchThread(pCPU);
            return 1;
    }

redispatch:
    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[26].u32 + 4, &pCPU->aGPR[9].u32);
    CPU_DEVICE_GET32(apDevice, aiDevice, pLibrary->anAddress[4], &pCPU->aGPR[10].u32);
    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[10].u32 + 4, &pCPU->aGPR[11].u32);
    if (pCPU->aGPR[9].u32 < pCPU->aGPR[11].u32) {
        pCPU->aGPR[5].u32 = pCPU->aGPR[26].u32;
        pCPU->aGPR[4].u32 = pLibrary->anAddress[4];
        __osEnqueueThread(pCPU);
        goto dispatchThread;
    }

enqueueRunning:
    pCPU->aGPR[9].u32 = pLibrary->anAddress[4];
    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[9].u32, &pCPU->aGPR[10].u32);
    CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[26].u32, &pCPU->aGPR[10].u32);
    CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[9].u32, &pCPU->aGPR[26].u32);

dispatchThread:
    __osDispatchThread(pCPU);
    return 1;
}
#endif

s32 send_mesg(Cpu* pCPU) {
    Library* pLibrary;
    CpuDevice** apDevice;
    u8* aiDevice;

    aiDevice = pCPU->aiDevice;
    apDevice = pCPU->apDevice;
    pLibrary = SYSTEM_LIBRARY(pCPU->pHost);

    pCPU->aGPR[10].u32 = pLibrary->anAddress[9];
    pCPU->aGPR[10].u32 += pCPU->aGPR[4].u32;
    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[10].u32, &pCPU->aGPR[9].u32);

    if (pCPU->aGPR[9].u32 != 0) {
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[9].u32 + 0x08, &pCPU->aGPR[11].s32);
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[9].u32 + 0x10, &pCPU->aGPR[12].s32);

        if (pCPU->aGPR[11].s32 < pCPU->aGPR[12].s32) {
            CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[9].u32 + 0x0C, &pCPU->aGPR[13].u32);
            pCPU->aGPR[13].u32 += pCPU->aGPR[11].u32;
            pCPU->aGPR[13].u32 %= pCPU->aGPR[12].u32;
            CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[9].u32 + 0x14, &pCPU->aGPR[12].u32);
            pCPU->aGPR[13].u32 *= 4;
            pCPU->aGPR[12].s32 += pCPU->aGPR[13].u32;
            CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[10].u32 + 0x04, &pCPU->aGPR[13].u32);
            CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[12].u32, &pCPU->aGPR[13].u32);
            pCPU->aGPR[10].s32 = pCPU->aGPR[11].s32 + 1;
            CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[9].u32 + 0x08, &pCPU->aGPR[10].u32);
            CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[9].u32 + 0x00, &pCPU->aGPR[10].u32);
            CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[10].u32, &pCPU->aGPR[11].u32);

            if (pCPU->aGPR[11].u32 != 0) {
                pCPU->aGPR[4].u32 = pCPU->aGPR[9].u32;
                CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[4].u32, &pCPU->aGPR[2].u32);
                CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[2].u32, &pCPU->aGPR[25].u32);
                CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[4].u32, &pCPU->aGPR[25].u32);
                pCPU->aGPR[10].u32 = pCPU->aGPR[2].u32;
                pCPU->aGPR[5].u32 = pCPU->aGPR[10].u32;
                pCPU->aGPR[4].u32 = pLibrary->anAddress[4];

                __osEnqueueThread(pCPU);
            }
        }
    }

    return 1;
}

s32 __osEnqueueAndYield(Cpu* pCPU) {
    s64 nData64;
    Library* pLibrary;
    __OSThread_s* __osRunningThread;
    u32 __OSGlobalIntMask;
    u32 nStatus;
    u32 nData32;
    u32 nMask;
    CpuDevice** apDevice;
    u8* aiDevice;

    apDevice = pCPU->apDevice;
    aiDevice = pCPU->aiDevice;
    pLibrary = SYSTEM_LIBRARY(pCPU->pHost);
    __OSGlobalIntMask = *(u32*)pLibrary->apData[3];
    CPU_DEVICE_GET32(apDevice, aiDevice, pLibrary->anAddress[8], &pCPU->aGPR[5].u32);

    if (!cpuGetAddressBuffer(pCPU, &__osRunningThread, pCPU->aGPR[5].u32)) {
        return 0;
    }

    if (!cpuGetRegisterCP0(pCPU, 0xC, &nData64)) {
        return 0;
    }

    nStatus = nData64 | 2;
    __osRunningThread->context.sr = nStatus;

    __osRunningThread->context.s0 = pCPU->aGPR[16].u64;
    __osRunningThread->context.s1 = pCPU->aGPR[17].u64;
    __osRunningThread->context.s2 = pCPU->aGPR[18].u64;
    __osRunningThread->context.s3 = pCPU->aGPR[19].u64;
    __osRunningThread->context.s4 = pCPU->aGPR[20].u64;
    __osRunningThread->context.s5 = pCPU->aGPR[21].u64;
    __osRunningThread->context.s6 = pCPU->aGPR[22].u64;
    __osRunningThread->context.s7 = pCPU->aGPR[23].u64;
    __osRunningThread->context.gp = pCPU->aGPR[28].u64;
    __osRunningThread->context.sp = pCPU->aGPR[29].u64;
    __osRunningThread->context.s8 = pCPU->aGPR[30].u64;
    __osRunningThread->context.ra = pCPU->aGPR[31].u64;

    __osRunningThread->context.pc = pCPU->nReturnAddrLast;
    __osRunningThread->context.fpcsr = pCPU->anFCR[31];

    __osRunningThread->context.fp20.u64 = pCPU->aFPR[20].u64;
    __osRunningThread->context.fp22.u64 = pCPU->aFPR[22].u64;
    __osRunningThread->context.fp24.u64 = pCPU->aFPR[24].u64;
    __osRunningThread->context.fp26.u64 = pCPU->aFPR[26].u64;
    __osRunningThread->context.fp28.u64 = pCPU->aFPR[28].u64;
    __osRunningThread->context.fp30.u64 = pCPU->aFPR[30].u64;

    if (nStatus & 0xFF00) {
        nData32 = ~__OSGlobalIntMask;
        nData32 &= 0xFF00;
        nData32 |= nStatus & 0xFF00;
        nData32 |= nStatus & 0xFFFF00FF;
        __osRunningThread->context.sr = nData32;
    }

    if (!mipsGet32(SYSTEM_MIPS(pCPU->pHost), 0xA430000C, (s32*)&nMask)) {
        return 0;
    }

    if (nMask != 0) {
        nData32 = __OSGlobalIntMask >> 16;
        nData32 = ~nData32;
        nData32 &= 0x3F;
        nMask |= nData32 & __osRunningThread->context.rcp;
    }

    __osRunningThread->context.rcp = nMask;
    if (pCPU->aGPR[4].u32 != 0) {
        __osEnqueueThread(pCPU);
    }

    __osDispatchThread(pCPU);
    return 1;
}

s32 __osEnqueueThread(Cpu* pCPU) {
    CpuDevice** apDevice = pCPU->apDevice;
    u8* aiDevice = pCPU->aiDevice;

    pCPU->aGPR[25].u32 = pCPU->aGPR[4].u32;
    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[4].u32, &pCPU->aGPR[24].u32);
    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[5].u32 + 4, &pCPU->aGPR[15].u32);
    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[24].u32 + 4, &pCPU->aGPR[14].u32);

    while (pCPU->aGPR[14].s32 >= pCPU->aGPR[15].s32) {
        pCPU->aGPR[25].u32 = pCPU->aGPR[24].u32;
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[24].u32, &pCPU->aGPR[24].u32);
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[24].u32 + 4, &pCPU->aGPR[14].u32);
    }

    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[25].u32, &pCPU->aGPR[24].u32);
    CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[5].u32, &pCPU->aGPR[24].u32);
    CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[25].u32, &pCPU->aGPR[5].u32);
    CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[5].u32 + 8, &pCPU->aGPR[4].u32);

    return 1;
}

s32 __osPopThread(Cpu* pCPU) {
    CpuDevice** apDevice = pCPU->apDevice;
    u8* aiDevice = pCPU->aiDevice;

    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[4].u32, &pCPU->aGPR[2].u32);
    CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->aGPR[2].u32, &pCPU->aGPR[25].u32);
    CPU_DEVICE_PUT32(apDevice, aiDevice, pCPU->aGPR[4].u32, &pCPU->aGPR[25].u32);
    return 1;
}

s32 __osDispatchThread(Cpu* pCPU) {
    Library* pLibrary;
    u32 nAddress;
    u64 nData64;
    __OSThread_s* __osRunningThread;
    u32 nData32;
    u32 __OSGlobalIntMask;
    u32 nStatus;
    u32 nMask;

    pLibrary = SYSTEM_LIBRARY(pCPU->pHost);

    nData32 = *(u32*)pLibrary->apData[3];
    __OSGlobalIntMask = nData32;

    pCPU->aGPR[4].u32 = pLibrary->anAddress[4];

    __osPopThread(pCPU);

    nAddress = pCPU->aGPR[2].u32;
    *(u32*)pLibrary->apData[8] = nAddress;

    if (!cpuGetAddressBuffer(pCPU, &__osRunningThread, nAddress)) {
        return 0;
    }

    __osRunningThread->state = 4;
    nStatus = __osRunningThread->context.sr;

    nData32 = __OSGlobalIntMask & 0xFF00;
    nData32 &= nStatus & 0xFF00;

    nStatus = (nStatus & 0xFFFF00FF) | nData32;
    nData64 = nStatus;
    if (!cpuSetRegisterCP0(pCPU, 12, nData64)) {
        return 0;
    }

    pCPU->aGPR[1].u64 = __osRunningThread->context.at;
    pCPU->aGPR[2].u64 = __osRunningThread->context.v0;
    pCPU->aGPR[3].u64 = __osRunningThread->context.v1;
    pCPU->aGPR[4].u64 = __osRunningThread->context.a0;
    pCPU->aGPR[5].u64 = __osRunningThread->context.a1;
    pCPU->aGPR[6].u64 = __osRunningThread->context.a2;
    pCPU->aGPR[7].u64 = __osRunningThread->context.a3;
    pCPU->aGPR[8].u64 = __osRunningThread->context.t0;
    pCPU->aGPR[9].u64 = __osRunningThread->context.t1;
    pCPU->aGPR[10].u64 = __osRunningThread->context.t2;
    pCPU->aGPR[11].u64 = __osRunningThread->context.t3;
    pCPU->aGPR[12].u64 = __osRunningThread->context.t4;
    pCPU->aGPR[13].u64 = __osRunningThread->context.t5;
    pCPU->aGPR[14].u64 = __osRunningThread->context.t6;
    pCPU->aGPR[15].u64 = __osRunningThread->context.t7;
    pCPU->aGPR[16].u64 = __osRunningThread->context.s0;
    pCPU->aGPR[17].u64 = __osRunningThread->context.s1;
    pCPU->aGPR[18].u64 = __osRunningThread->context.s2;
    pCPU->aGPR[19].u64 = __osRunningThread->context.s3;
    pCPU->aGPR[20].u64 = __osRunningThread->context.s4;
    pCPU->aGPR[21].u64 = __osRunningThread->context.s5;
    pCPU->aGPR[22].u64 = __osRunningThread->context.s6;
    pCPU->aGPR[23].u64 = __osRunningThread->context.s7;
    pCPU->aGPR[24].u64 = __osRunningThread->context.t8;
    pCPU->aGPR[25].u64 = __osRunningThread->context.t9;
    pCPU->aGPR[28].u64 = __osRunningThread->context.gp;
    pCPU->aGPR[29].u64 = __osRunningThread->context.sp;
    pCPU->aGPR[30].u64 = __osRunningThread->context.s8;
    pCPU->aGPR[31].u64 = __osRunningThread->context.ra;
    pCPU->nLo = __osRunningThread->context.lo;
    pCPU->nHi = __osRunningThread->context.hi;

    nData32 = __osRunningThread->context.pc;
    pCPU->anCP0[14] = nData32;

    pCPU->anFCR[31] = __osRunningThread->context.fpcsr;
    pCPU->aFPR[0].u64 = __osRunningThread->context.fp0.u64;
    pCPU->aFPR[2].u64 = __osRunningThread->context.fp2.u64;
    pCPU->aFPR[4].u64 = __osRunningThread->context.fp4.u64;
    pCPU->aFPR[6].u64 = __osRunningThread->context.fp6.u64;
    pCPU->aFPR[8].u64 = __osRunningThread->context.fp8.u64;
    pCPU->aFPR[10].u64 = __osRunningThread->context.fp10.u64;
    pCPU->aFPR[12].u64 = __osRunningThread->context.fp12.u64;
    pCPU->aFPR[14].u64 = __osRunningThread->context.fp14.u64;
    pCPU->aFPR[16].u64 = __osRunningThread->context.fp16.u64;
    pCPU->aFPR[18].u64 = __osRunningThread->context.fp18.u64;
    pCPU->aFPR[20].u64 = __osRunningThread->context.fp20.u64;
    pCPU->aFPR[22].u64 = __osRunningThread->context.fp22.u64;
    pCPU->aFPR[24].u64 = __osRunningThread->context.fp24.u64;
    pCPU->aFPR[26].u64 = __osRunningThread->context.fp26.u64;
    pCPU->aFPR[28].u64 = __osRunningThread->context.fp28.u64;
    pCPU->aFPR[30].u64 = __osRunningThread->context.fp30.u64;

    nMask = __osRunningThread->context.rcp;

    nData32 = __OSGlobalIntMask;
    nData32 >>= 16;

    nMask &= nData32;
    nData32 = __osRcpImTable[nMask];

    if (!mipsPut32(SYSTEM_MIPS(pCPU->pHost), 0xA430000C, (s32*)&nData32)) {
        return 0;
    }

    __cpuERET(pCPU);
    return 1;
}

s32 osGetMemSize(Cpu* pCPU) {
    u32 nSize;

    if (!ramGetSize(SYSTEM_RAM(pCPU->pHost), (s32*)&nSize)) {
        return 0;
    }

    pCPU->aGPR[2].u32 = nSize;
    return 1;
}

s32 osInvalICache(Cpu* pCPU) {
    u32 nAddress = pCPU->aGPR[4].u32;
    u32 nSize = pCPU->aGPR[5].u32;

    if (!cpuInvalidateCache(pCPU, nAddress, nAddress + nSize)) {
        return 0;
    }

    if (!rspInvalidateCache(SYSTEM_RSP(pCPU->pHost), nAddress, nAddress + nSize)) {
        return 0;
    }

    return 1;
}

s32 __osDisableInt(Cpu* pCPU) {
    u32 nStatus;
    u64 nData64;
    s32 pad[2];

    if (!cpuGetRegisterCP0(pCPU, 12, (s64*)&nData64)) {
        return 0;
    }

    nStatus = nData64;
    ;
    nData64 = nStatus & ~1;
    if (!cpuSetRegisterCP0(pCPU, 12, nData64)) {
        return 0;
    }

    pCPU->aGPR[2].s32 = nStatus & 1;
    return 1;
}

s32 __osRestoreInt(Cpu* pCPU) {
    u64 nStatus;

    if (!cpuGetRegisterCP0(pCPU, 12, (s64*)&nStatus)) {
        return 0;
    }

    nStatus |= pCPU->aGPR[4].u64;
    if (!cpuSetRegisterCP0(pCPU, 12, nStatus)) {
        return 0;
    }

    return 1;
}

s32 __osSpSetStatus(Cpu* pCPU) {
    u32 nData32 = pCPU->aGPR[4].u32;

    if (!rspPut32(SYSTEM_RSP(pCPU->pHost), 0x04040010, &nData32)) {
        return 0;
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/library/__cosf.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__sinf.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/_bzero.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/_bcopy.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/_memcpy.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osPhysicalToVirtual.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osVirtualToPhysical.s")

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guMtxCatF.s")
#else
void guMtxCatF(Cpu* pCPU) {
    s32 i;
    s32 j;
    s32 k;
    f32 temp[4][4];
    CpuFpr data1;
    CpuFpr data2;
    u32* mf;
    u32* nf;
    u32* res;

    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &nf, pCPU->aGPR[5].u32);
    cpuGetAddressBuffer(pCPU, &res, pCPU->aGPR[6].u32);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp[i][j] = 0.0f;
            for (k = 0; k < 4; k++) {
                data1.u32 = mf[i * 4 + k];
                data2.u32 = nf[k * 4 + j];
                temp[i][j] += data1.f32 * data2.f32;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            data1.f32 = temp[i][j];
            res[i * 4 + j] = data1.u32;
        }
    }
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guMtxF2L.s")
#else
void guMtxF2L(Cpu* pCPU) {
    f32* mf;
    s32 e1;
    s32 e2;
    s32 i;
    s32 j;
    s32* m;
    volatile CpuFpr data;
    s32* ai;
    s32* af;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[5].u32);
    frameFixMatrixHint(SYSTEM_FRAME(pCPU->pHost), pCPU->aGPR[4].u32, pCPU->aGPR[5].u32);

    ai = &m[0];
    af = &m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            data.f32 = mf[i * 4 + j];
            e1 = 0x10000 * data.f32;
            data.f32 = mf[i * 4 + j + 1];
            e2 = 0x10000 * data.f32;
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guMtxIdentF.s")
#else
void guMtxIdentF(Cpu* pCPU) {
    f32* mf;
    s32 i;
    s32 j;
    CpuFpr data1;
    CpuFpr data0;
    f32 float1;
    f32 float0;

    *((volatile f32*)&data0.f32) = 0.0f;
    *((volatile f32*)&data1.f32) = 1.0f;
    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);

    float1 = data1.f32;
    float0 = data0.f32;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                mf[i * 4 + j] = float1;
            } else {
                mf[i * 4 + j] = float0;
            }
        }
    }
}
#endif

void guMtxIdent(Cpu* pCPU) {
    s32* m;

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);
    m[0] = 0x10000;
    m[1] = 0;
    m[2] = 1;
    m[3] = 0;
    m[4] = 0;
    m[5] = 0x10000;
    m[6] = 0;
    m[7] = 1;
    m[8] = 0;
    m[9] = 0;
    m[10] = 0;
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 0;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guOrthoF.s")
#else
void guOrthoF(Cpu* pCPU) {
    s32 i;
    s32 j;
    u32* mf;
    u32* sp;
    f32 l;
    f32 r;
    f32 b;
    f32 t;
    f32 n;
    f32 f;
    f32 scale;
    CpuFpr data0;
    CpuFpr data1;
    CpuFpr data;

    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[5].u32;
    l = data.f32;

    data.u32 = pCPU->aGPR[6].u32;
    r = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    b = data.f32;

    data.u32 = sp[4];
    t = data.f32;

    data.u32 = sp[5];
    n = data.f32;

    data.u32 = sp[6];
    f = data.f32;

    data.u32 = sp[7];
    scale = data.f32;

    data0.f32 = 0.0f;
    data1.f32 = 1.0f;
    frameSetMatrixHint(SYSTEM_FRAME(pCPU->pHost), FMP_ORTHOGRAPHIC, pCPU->aGPR[4].u32, 0, n, f, 0.0f, 0.0f, scale);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                mf[i * 4 + j] = data1.u32;
            } else {
                mf[i * 4 + j] = data0.u32;
            }
        }
    }

    data.f32 = 2 / (r - l);
    mf[0 * 4 + 0] = data.u32;

    data.f32 = 2 / (t - b);
    mf[1 * 4 + 1] = data.u32;

    data.f32 = -2 / (f - n);
    mf[2 * 4 + 2] = data.u32;

    data.f32 = -(r + l) / (r - l);
    mf[3 * 4 + 0] = data.u32;

    data.f32 = -(t + b) / (t - b);
    mf[3 * 4 + 1] = data.u32;

    data.f32 = -(f + n) / (f - n);
    mf[3 * 4 + 2] = data.u32;

    data.f32 = 1.0f;
    mf[3 * 4 + 3] = data.u32;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guOrtho.s")
#else
void guOrtho(Cpu* pCPU) {
    s32* m;
    s32 i;
    s32 j;
    s32 e1;
    s32 e2;
    CpuFpr data;
    f32 mf[4][4];
    u32* sp;
    s32* ai;
    s32* af;
    f32 l;
    f32 r;
    f32 b;
    f32 t;
    f32 n;
    f32 f;
    f32 scale;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[5].u32;
    l = data.f32;

    data.u32 = pCPU->aGPR[6].u32;
    r = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    b = data.f32;

    data.u32 = sp[4];
    t = data.f32;

    data.u32 = sp[5];
    n = data.f32;

    data.u32 = sp[6];
    f = data.f32;

    data.u32 = sp[7];
    scale = data.f32;

    frameSetMatrixHint(SYSTEM_FRAME(pCPU->pHost), FMP_ORTHOGRAPHIC, 0, pCPU->aGPR[4].u32, n, f, 0.0f, 0.0f, scale);

    mf[0][0] = 1.0f;
    mf[0][1] = 0.0f;
    mf[0][2] = 0.0f;
    mf[0][3] = 0.0f;
    mf[1][0] = 0.0f;
    mf[1][1] = 1.0f;
    mf[1][2] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][0] = 0.0f;
    mf[2][1] = 0.0f;
    mf[2][2] = 1.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;

    mf[0][0] = 2 / (r - l);
    mf[1][1] = 2 / (t - b);
    mf[2][2] = -2 / (f - n);
    mf[3][0] = -(r + l) / (r - l);
    mf[3][1] = -(t + b) / (t - b);
    mf[3][2] = -(f + n) / (f - n);
    mf[3][3] = 1.0f;

    ai = &m[0];
    af = &m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            e1 = 0x10000 * mf[i][j];
            e2 = 0x10000 * mf[i][j + 1];
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guPerspectiveF.s")
#else
void guPerspectiveF(Cpu* pCPU) {
    s32 i;
    s32 j;
    f32 cot;
    s16* perspNorm;
    u32* mf;
    u32* sp;
    CpuFpr data0;
    CpuFpr data1;
    CpuFpr data;
    f32 fovy;
    f32 aspect;
    f32 rNear;
    f32 rFar;
    f32 scale;

    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);
    cpuGetAddressBuffer(pCPU, &perspNorm, pCPU->aGPR[5].u32);

    data.u32 = pCPU->aGPR[6].u32;
    fovy = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    aspect = data.f32;

    data.u32 = sp[4];
    rNear = data.f32;

    data.u32 = sp[5];
    rFar = data.f32;

    data.u32 = sp[6];
    scale = data.f32;

    data0.f32 = 0.0f;
    data1.f32 = 1.0f;
    frameSetMatrixHint(SYSTEM_FRAME(pCPU->pHost), FMP_PERSPECTIVE, pCPU->aGPR[4].u32, 0, rNear, rFar, fovy, aspect,
                       scale);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                mf[i * 4 + j] = data1.u32;
            } else {
                mf[i * 4 + j] = data0.u32;
            }
        }
    }

    fovy *= (f32)M_PI / 180;
    cot = cosf(fovy / 2) / sinf(fovy / 2);

    data.f32 = cot / aspect;
    mf[0 * 4 + 0] = data.u32;

    data.f32 = cot;
    mf[1 * 4 + 1] = data.u32;

    data.f32 = (rNear + rFar) / (rNear - rFar);
    mf[2 * 4 + 2] = data.u32;

    data.f32 = -1.0f;
    mf[2 * 4 + 3] = data.u32;

    data.f32 = 2 * rNear * rFar / (rNear - rFar);
    mf[3 * 4 + 2] = data.u32;

    data.f32 = 0.0f;
    mf[3 * 4 + 3] = data.u32;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guPerspective.s")
#else
void guPerspective(Cpu* pCPU) {
    s32* m;
    f32 fovy;
    f32 aspect;
    f32 rNear;
    f32 rFar;
    f32 scale;
    f32 _cot;
    s32 i;
    s32 j;
    CpuFpr data;
    f32 mf[4][4];
    s32 e1;
    s32 e2;
    u32* sp;
    s32* ai;
    s32* af;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[6].u32;
    fovy = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    aspect = data.f32;

    data.u32 = sp[4];
    rNear = data.f32;

    data.u32 = sp[5];
    rFar = data.f32;

    data.u32 = sp[6];
    scale = data.f32;

    frameSetMatrixHint(SYSTEM_FRAME(pCPU->pHost), FMP_PERSPECTIVE, 0, pCPU->aGPR[4].u32, rNear, rFar, fovy, aspect,
                       scale);

    mf[0][0] = 1.0f;
    mf[0][1] = 0.0f;
    mf[0][2] = 0.0f;
    mf[0][3] = 0.0f;
    mf[1][0] = 0.0f;
    mf[1][1] = 1.0f;
    mf[1][2] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][0] = 0.0f;
    mf[2][1] = 0.0f;
    mf[2][2] = 1.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;

    fovy *= (f32)M_PI / 180;
    _cot = cosf(fovy / 2) / sinf(fovy / 2);

    mf[0][0] = _cot / aspect;
    mf[1][1] = _cot;
    mf[2][2] = (rNear + rFar) / (rNear - rFar);
    mf[2][3] = -1.0f;
    mf[3][2] = 2 * rNear * rFar / (rNear - rFar);
    mf[3][3] = 0.0f;

    ai = &m[0];
    af = &m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            e1 = 0x10000 * mf[i][j];
            e2 = 0x10000 * mf[i][j + 1];
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/GenPerspective_1080.s")
#else
void GenPerspective_1080(Cpu* pCPU) {
    CpuFpr data;
    u32* mf;
    u32* sp;
    f32 fovy;
    f32 aspect;
    f32 rNear;
    f32 rFar;
    Frame* pFrame = SYSTEM_FRAME(pCPU->pHost);

    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[5].u32;
    fovy = data.f32;

    data.u32 = pCPU->aGPR[6].u32;
    aspect = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    rNear = data.f32;

    data.u32 = sp[4];
    rFar = data.f32;

    frameSetMatrixHint(SYSTEM_FRAME(pCPU->pHost), 0, pCPU->aGPR[4].u32, 0, rNear, rFar, fovy, aspect, 1.0f);
    pFrame->iHintHack = pFrame->iHintLast;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guScaleF.s")
#else
void guScaleF(Cpu* pCPU) {
    s32 i;
    s32 j;
    u32* mf;
    CpuFpr data0;
    CpuFpr data1;

    data0.f32 = 0.0f;
    data1.f32 = 1.0f;
    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                mf[i * 4 + j] = data1.u32;
            } else {
                mf[i * 4 + j] = data0.u32;
            }
        }
    }

    mf[0 * 4 + 0] = pCPU->aGPR[5].s32;
    mf[1 * 4 + 1] = pCPU->aGPR[6].s32;
    mf[2 * 4 + 2] = pCPU->aGPR[7].s32;
    mf[3 * 4 + 3] = data1.u32;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guScale.s")
#else
void guScale(Cpu* pCPU) {
    f32 mf[4][4];
    s32* m;
    s32 i;
    s32 j;
    s32 e1;
    s32 e2;
    CpuFpr data;
    s32* ai;
    s32* af;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);

    mf[0][0] = 1.0f;
    mf[0][1] = 0.0f;
    mf[0][2] = 0.0f;
    mf[0][3] = 0.0f;
    mf[1][0] = 0.0f;
    mf[1][1] = 1.0f;
    mf[1][2] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][0] = 0.0f;
    mf[2][1] = 0.0f;
    mf[2][2] = 1.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;

    data.s32 = pCPU->aGPR[5].s32;
    mf[0][0] = data.f32;

    data.s32 = pCPU->aGPR[6].s32;
    mf[1][1] = data.f32;

    data.s32 = pCPU->aGPR[7].s32;
    mf[2][2] = data.f32;

    ai = &m[0];
    af = &m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            e1 = 0x10000 * mf[i][j];
            e2 = 0x10000 * mf[i][j + 1];
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guTranslateF.s")
#else
void guTranslateF(Cpu* pCPU) {
    s32 i;
    s32 j;
    u32* mf;
    CpuFpr data0;
    CpuFpr data1;

    data0.f32 = 0.0f;
    data1.f32 = 1.0f;
    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                mf[i * 4 + j] = data1.u32;
            } else {
                mf[i * 4 + j] = data0.u32;
            }
        }
    }

    mf[3 * 4 + 0] = pCPU->aGPR[5].s32;
    mf[3 * 4 + 1] = pCPU->aGPR[6].s32;
    mf[3 * 4 + 2] = pCPU->aGPR[7].s32;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guTranslate.s")
#else
void guTranslate(Cpu* pCPU) {
    s32* m;
    s32 i;
    s32 j;
    s32 e1;
    s32 e2;
    CpuFpr data;
    f32 mf[4][4];
    s32* ai;
    s32* af;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);

    mf[0][0] = 1.0f;
    mf[0][1] = 0.0f;
    mf[0][2] = 0.0f;
    mf[0][3] = 0.0f;
    mf[1][0] = 0.0f;
    mf[1][1] = 1.0f;
    mf[1][2] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][0] = 0.0f;
    mf[2][1] = 0.0f;
    mf[2][2] = 1.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;

    data.s32 = pCPU->aGPR[5].s32;
    mf[3][0] = data.f32;

    data.s32 = pCPU->aGPR[6].s32;
    mf[3][1] = data.f32;

    data.s32 = pCPU->aGPR[7].s32;
    mf[3][2] = data.f32;

    ai = &m[0];
    af = &m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            e1 = 0x10000 * mf[i][j];
            e2 = 0x10000 * mf[i][j + 1];
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guRotateF.s")
#else
void guRotateF(Cpu* pCPU) {
    f32 m;
    s32 i;
    s32 j;
    f32 a;
    f32 x;
    f32 y;
    f32 z;
    u32* mf;
    u32* sp;
    CpuFpr data;
    CpuFpr data0;
    CpuFpr data1;
    f32 sine;
    f32 cosine;
    f32 ab;
    f32 bc;
    f32 ca;
    f32 t;

    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[5].u32;
    a = data.f32;

    data.u32 = pCPU->aGPR[6].u32;
    x = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    y = data.f32;

    data.u32 = sp[4];
    z = data.f32;

    m = 1.0f / sqrtf(x * x + y * y + z * z);

    a *= (f32)M_PI / 180;
    x *= m;
    y *= m;
    z *= m;

    sine = sinf(a);
    cosine = cosf(a);

    t = 1.0f - cosine;
    ab = x * y * t;
    bc = y * z * t;
    ca = z * x * t;

    data0.f32 = 0.0f;
    data1.f32 = 1.0f;
    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) {
                mf[i * 4 + j] = data1.u32;
            } else {
                mf[i * 4 + j] = data0.u32;
            }
        }
    }

    t = x * x;
    data.f32 = t + cosine * (1.0f - t);
    mf[0 * 4 + 0] = data.u32;

    data.f32 = bc - x * sine;
    mf[2 * 4 + 1] = data.u32;

    data.f32 = bc + x * sine;
    mf[1 * 4 + 2] = data.u32;

    t = y * y;
    data.f32 = t + cosine * (1.0f - t);
    mf[1 * 4 + 1] = data.u32;

    data.f32 = ca + y * sine;
    mf[2 * 4 + 0] = data.u32;

    data.f32 = ca - y * sine;
    mf[0 * 4 + 2] = data.u32;

    t = z * z;
    data.f32 = t + cosine * (1.0f - t);
    mf[2 * 4 + 2] = data.u32;

    data.f32 = ab - z * sine;
    mf[1 * 4 + 0] = data.u32;

    data.f32 = ab + z * sine;
    mf[0 * 4 + 1] = data.u32;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guRotate.s")
#else
void guRotate(Cpu* pCPU) {
    s32* m;
    u32* sp;
    CpuFpr data;
    s32 i;
    s32 j;
    s32 e1;
    s32 e2;
    f32 mf[4][4];
    f32 sine;
    f32 cosine;
    f32 a;
    f32 x;
    f32 y;
    f32 z;
    f32 ab;
    f32 bc;
    f32 ca;
    f32 t;
    f32 magnitude;
    s32* ai;
    s32* af;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[5].u32;
    a = data.f32;

    data.u32 = pCPU->aGPR[6].u32;
    x = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    y = data.f32;

    data.u32 = sp[4];
    z = data.f32;

    magnitude = 1.0f / sqrtf(x * x + y * y + z * z);

    a *= (f32)M_PI / 180;
    x *= magnitude;
    y *= magnitude;
    z *= magnitude;

    sine = sinf(a);
    cosine = cosf(a);

    t = 1.0f - cosine;
    ab = x * y * t;
    bc = y * z * t;
    ca = z * x * t;

    mf[0][0] = 1.0f;
    mf[0][1] = 0.0f;
    mf[0][2] = 0.0f;
    mf[0][3] = 0.0f;
    mf[1][0] = 0.0f;
    mf[1][1] = 1.0f;
    mf[1][2] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][0] = 0.0f;
    mf[2][1] = 0.0f;
    mf[2][2] = 1.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;

    t = x * x;
    mf[0][0] = t + cosine * (1.0f - t);
    mf[2][1] = bc - x * sine;
    mf[1][2] = bc + x * sine;
    t = y * y;
    mf[1][1] = t + cosine * (1.0f - t);
    mf[2][0] = ca + y * sine;
    mf[0][2] = ca - y * sine;
    t = z * z;
    mf[2][2] = t + cosine * (1.0f - t);
    mf[1][0] = ab - z * sine;
    mf[0][1] = ab + z * sine;

    ai = &m[0];
    af = &m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            e1 = 0x10000 * mf[i][j];
            e2 = 0x10000 * mf[i][j + 1];
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtF.s")
#else
void guLookAtF(Cpu* pCPU) {
    f32 len;
    f32 xAt;
    f32 yAt;
    f32 zAt;
    f32 xUp;
    f32 yUp;
    f32 zUp;
    f32 xEye;
    f32 yEye;
    f32 zEye;
    u32* mf;
    u32* sp;
    f32 xLook;
    f32 yLook;
    f32 zLook;
    f32 xRight;
    f32 yRight;
    f32 zRight;
    CpuFpr data;
    CpuFpr data0;
    CpuFpr data1;

    data0.f32 = 0.0f;
    data1.f32 = 1.0f;
    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[5].u32;
    xEye = data.f32;

    data.u32 = pCPU->aGPR[6].u32;
    yEye = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    zEye = data.f32;

    data.u32 = sp[4];
    xAt = data.f32;

    data.u32 = sp[5];
    yAt = data.f32;

    data.u32 = sp[6];
    zAt = data.f32;

    data.u32 = sp[7];
    xUp = data.f32;

    data.u32 = sp[8];
    yUp = data.f32;

    data.u32 = sp[9];
    zUp = data.f32;

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;
    len = -1.0f / sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    data.f32 = xRight;
    mf[0 * 4 + 0] = data.u32;

    data.f32 = yRight;
    mf[1 * 4 + 0] = data.u32;

    data.f32 = zRight;
    mf[2 * 4 + 0] = data.u32;

    data.f32 = -(xEye * xRight + yEye * yRight + zEye * zRight);
    mf[3 * 4 + 0] = data.u32;

    data.f32 = xUp;
    mf[0 * 4 + 1] = data.u32;

    data.f32 = yUp;
    mf[1 * 4 + 1] = data.u32;

    data.f32 = zUp;
    mf[2 * 4 + 1] = data.u32;

    data.f32 = -(xEye * xUp + yEye * yUp + zEye * zUp);
    mf[3 * 4 + 1] = data.u32;

    data.f32 = xLook;
    mf[0 * 4 + 2] = data.u32;

    data.f32 = yLook;
    mf[1 * 4 + 2] = data.u32;

    data.f32 = zLook;
    mf[2 * 4 + 2] = data.u32;

    data.f32 = -(xEye * xLook + yEye * yLook + zEye * zLook);
    mf[3 * 4 + 2] = data.u32;

    mf[0 * 4 + 3] = data0.u32;
    mf[1 * 4 + 3] = data0.u32;
    mf[2 * 4 + 3] = data0.u32;
    mf[3 * 4 + 3] = data1.u32;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAt.s")
#else
void guLookAt(Cpu* pCPU) {
    f32 mf[4][4];
    s32* m;
    u32* sp;
    CpuFpr data;
    s32 i;
    s32 j;
    s32 e1;
    s32 e2;
    s32* ai;
    s32* af;
    f32 len;
    f32 xLook;
    f32 yLook;
    f32 zLook;
    f32 xRight;
    f32 yRight;
    f32 zRight;
    f32 xEye;
    f32 yEye;
    f32 zEye;
    f32 xAt;
    f32 yAt;
    f32 zAt;
    f32 xUp;
    f32 yUp;
    f32 zUp;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[5].u32;
    xEye = data.f32;

    data.u32 = pCPU->aGPR[6].u32;
    yEye = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    zEye = data.f32;

    data.u32 = sp[4];
    xAt = data.f32;

    data.u32 = sp[5];
    yAt = data.f32;

    data.u32 = sp[6];
    zAt = data.f32;

    data.u32 = sp[7];
    xUp = data.f32;

    data.u32 = sp[8];
    yUp = data.f32;

    data.u32 = sp[9];
    zUp = data.f32;

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;
    len = -1.0f / sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][3] = 1.0f;

    ai = &m[0];
    af = &m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            e1 = 0x10000 * mf[i][j];
            e2 = 0x10000 * mf[i][j + 1];
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

typedef struct Light_t_s {
    /* 0x0 */ u8 col[3];
    /* 0x3 */ char pad1;
    /* 0x4 */ u8 colc[3];
    /* 0x7 */ char pad2;
    /* 0x8 */ s8 dir[3];
    /* 0xB */ char pad3;
} Light_t_s; // size = 0xC

typedef union Light_s {
    /* 0x0 */ Light_t_s l;
    /* 0x0 */ s64 force_structure_alignment[2];
} Light_s;

typedef struct LookAt_s {
    /* 0x0 */ Light_s l[2];
} LookAt_s; // size = 0x20

typedef struct Hilite_t_s {
    /* 0x0 */ s32 x1;
    /* 0x4 */ s32 y1;
    /* 0x8 */ s32 x2;
    /* 0xC */ s32 y2;
} Hilite_t_s; // size = 0x10

typedef union Hilite_s {
    /* 0x0 */ Hilite_t_s h;
    /* 0x0 */ s32 force_structure_alignment[4];
} Hilite_s;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define FTOFRAC8(x) ((s32)MIN(((x) * (128.0f)), 127.0f) & 0xFF)

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtHiliteF.s")
#else
void guLookAtHiliteF(Cpu* pCPU) {
    LookAt_s* l;
    Hilite_s* h;
    CpuFpr data;
    u32* mf;
    u32* sp;
    f32 len;
    f32 xLook;
    f32 yLook;
    f32 zLook;
    f32 xRight;
    f32 yRight;
    f32 zRight;
    f32 xHilite;
    f32 yHilite;
    f32 zHilite;
    f32 xEye;
    f32 yEye;
    f32 zEye;
    f32 xAt;
    f32 yAt;
    f32 zAt;
    f32 xUp;
    f32 yUp;
    f32 zUp;
    f32 xl1;
    f32 yl1;
    f32 zl1;
    f32 xl2;
    f32 yl2;
    f32 zl2;
    s32 twidth;
    s32 theight;

    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &l, pCPU->aGPR[5].u32);
    cpuGetAddressBuffer(pCPU, &h, pCPU->aGPR[6].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[7].u32;
    xEye = data.f32;

    data.u32 = sp[4];
    yEye = data.f32;

    data.u32 = sp[5];
    zEye = data.f32;

    data.u32 = sp[6];
    xAt = data.f32;

    data.u32 = sp[7];
    yAt = data.f32;

    data.u32 = sp[8];
    zAt = data.f32;

    data.u32 = sp[9];
    xUp = data.f32;

    data.u32 = sp[10];
    yUp = data.f32;

    data.u32 = sp[11];
    zUp = data.f32;

    data.u32 = sp[12];
    xl1 = data.f32;

    data.u32 = sp[13];
    yl1 = data.f32;

    data.u32 = sp[14];
    zl1 = data.f32;

    data.u32 = sp[15];
    xl2 = data.f32;

    data.u32 = sp[16];
    yl2 = data.f32;

    data.u32 = sp[17];
    zl2 = data.f32;

    twidth = sp[18];
    theight = sp[19];

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;
    len = -1.0f / sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    len = 1.0f / sqrtf(xl1 * xl1 + yl1 * yl1 + zl1 * zl1);
    xl1 *= len;
    yl1 *= len;
    zl1 *= len;

    xHilite = xl1 + xLook;
    yHilite = yl1 + yLook;
    zHilite = zl1 + zLook;

    len = sqrtf(xHilite * xHilite + yHilite * yHilite + zHilite * zHilite);
    if (len > 0.1) {
        len = 1.0f / len;
        xHilite *= len;
        yHilite *= len;
        zHilite *= len;

        h->h.x1 = twidth * 4 + (s32)((xHilite * xRight + yHilite * yRight + zHilite * zRight) * twidth * 2);
        h->h.y1 = theight * 4 + (s32)((xHilite * xUp + yHilite * yUp + zHilite * zUp) * theight * 2);
    } else {
        h->h.x1 = twidth * 2;
        h->h.y1 = theight * 2;
    }

    len = 1.0f / sqrtf(xl2 * xl2 + yl2 * yl2 + zl2 * zl2);
    xl2 *= len;
    yl2 *= len;
    zl2 *= len;

    xHilite = xl2 + xLook;
    yHilite = yl2 + yLook;
    zHilite = zl2 + zLook;

    len = sqrtf(xHilite * xHilite + yHilite * yHilite + zHilite * zHilite);
    if (len > 0.1) {
        len = 1.0f / len;
        xHilite *= len;
        yHilite *= len;
        zHilite *= len;

        h->h.x2 = twidth * 4 + (s32)((xHilite * xRight + yHilite * yRight + zHilite * zRight) * twidth * 2);
        h->h.y2 = theight * 4 + (s32)((xHilite * xUp + yHilite * yUp + zHilite * zUp) * theight * 2);
    } else {
        h->h.x2 = twidth * 2;
        h->h.y2 = theight * 2;
    }

    l->l[0].l.dir[0] = FTOFRAC8(xRight);
    l->l[0].l.dir[1] = FTOFRAC8(yRight);
    l->l[0].l.dir[2] = FTOFRAC8(zRight);
    l->l[1].l.dir[0] = FTOFRAC8(xUp);
    l->l[1].l.dir[1] = FTOFRAC8(yUp);
    l->l[1].l.dir[2] = FTOFRAC8(zUp);
    l->l[0].l.col[0] = 0x00;
    l->l[0].l.col[1] = 0x00;
    l->l[0].l.col[2] = 0x00;
    l->l[0].l.pad1 = 0x00;
    l->l[0].l.colc[0] = 0x00;
    l->l[0].l.colc[1] = 0x00;
    l->l[0].l.colc[2] = 0x00;
    l->l[0].l.pad2 = 0x00;
    l->l[1].l.col[0] = 0x00;
    l->l[1].l.col[1] = 0x80;
    l->l[1].l.col[2] = 0x00;
    l->l[1].l.pad1 = 0x00;
    l->l[1].l.colc[0] = 0x00;
    l->l[1].l.colc[1] = 0x80;
    l->l[1].l.colc[2] = 0x00;
    l->l[1].l.pad2 = 0x00;

    data.f32 = xRight;
    mf[0 * 4 + 0] = data.u32;

    data.f32 = yRight;
    mf[1 * 4 + 0] = data.u32;

    data.f32 = zRight;
    mf[2 * 4 + 0] = data.u32;

    data.f32 = -(xEye * xRight + yEye * yRight + zEye * zRight);
    mf[3 * 4 + 0] = data.u32;

    data.f32 = xUp;
    mf[0 * 4 + 1] = data.u32;

    data.f32 = yUp;
    mf[1 * 4 + 1] = data.u32;

    data.f32 = zUp;
    mf[2 * 4 + 1] = data.u32;

    data.f32 = -(xEye * xUp + yEye * yUp + zEye * zUp);
    mf[3 * 4 + 1] = data.u32;

    data.f32 = xLook;
    mf[0 * 4 + 2] = data.u32;

    data.f32 = yLook;
    mf[1 * 4 + 2] = data.u32;

    data.f32 = zLook;
    mf[2 * 4 + 2] = data.u32;

    data.f32 = -(xEye * xLook + yEye * yLook + zEye * zLook);
    mf[3 * 4 + 2] = data.u32;

    data.f32 = 0.0f;
    mf[0 * 4 + 3] = data.u32;

    data.f32 = 0.0f;
    mf[1 * 4 + 3] = data.u32;

    data.f32 = 0.0f;
    mf[2 * 4 + 3] = data.u32;

    data.f32 = 1.0f;
    mf[3 * 4 + 3] = data.u32;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtHilite.s")
#else
void guLookAtHilite(Cpu* pCPU) {
    LookAt_s* l;
    Hilite_s* h;
    s32 i;
    s32 j;
    s32 e1;
    s32 e2;
    CpuFpr data;
    f32 mf[4][4];
    u32* m;
    u32* sp;
    s32* ai;
    s32* af;
    f32 len;
    f32 xLook;
    f32 yLook;
    f32 zLook;
    f32 xRight;
    f32 yRight;
    f32 zRight;
    f32 xHilite;
    f32 yHilite;
    f32 zHilite;
    f32 xEye;
    f32 yEye;
    f32 zEye;
    f32 xAt;
    f32 yAt;
    f32 zAt;
    f32 xUp;
    f32 yUp;
    f32 zUp;
    f32 xl1;
    f32 yl1;
    f32 zl1;
    f32 xl2;
    f32 yl2;
    f32 zl2;
    s32 twidth;
    s32 theight;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &l, pCPU->aGPR[5].u32);
    cpuGetAddressBuffer(pCPU, &h, pCPU->aGPR[6].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[7].u32;
    xEye = data.f32;

    data.u32 = sp[4];
    yEye = data.f32;

    data.u32 = sp[5];
    zEye = data.f32;

    data.u32 = sp[6];
    xAt = data.f32;

    data.u32 = sp[7];
    yAt = data.f32;

    data.u32 = sp[8];
    zAt = data.f32;

    data.u32 = sp[9];
    xUp = data.f32;

    data.u32 = sp[10];
    yUp = data.f32;

    data.u32 = sp[11];
    zUp = data.f32;

    data.u32 = sp[12];
    xl1 = data.f32;

    data.u32 = sp[13];
    yl1 = data.f32;

    data.u32 = sp[14];
    zl1 = data.f32;

    data.u32 = sp[15];
    xl2 = data.f32;

    data.u32 = sp[16];
    yl2 = data.f32;

    data.u32 = sp[17];
    zl2 = data.f32;

    twidth = sp[18];
    theight = sp[19];

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;
    len = -1.0f / sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    len = 1.0f / sqrtf(xl1 * xl1 + yl1 * yl1 + zl1 * zl1);
    xl1 *= len;
    yl1 *= len;
    zl1 *= len;

    xHilite = xl1 + xLook;
    yHilite = yl1 + yLook;
    zHilite = zl1 + zLook;

    len = sqrtf(xHilite * xHilite + yHilite * yHilite + zHilite * zHilite);
    if (len > 0.1) {
        len = 1.0f / len;
        xHilite *= len;
        yHilite *= len;
        zHilite *= len;

        h->h.x1 = twidth * 4 + (s32)((xHilite * xRight + yHilite * yRight + zHilite * zRight) * twidth * 2);
        h->h.y1 = theight * 4 + (s32)((xHilite * xUp + yHilite * yUp + zHilite * zUp) * theight * 2);
    } else {
        h->h.x1 = twidth * 2;
        h->h.y1 = theight * 2;
    }

    len = 1.0f / sqrtf(xl2 * xl2 + yl2 * yl2 + zl2 * zl2);
    xl2 *= len;
    yl2 *= len;
    zl2 *= len;

    xHilite = xl2 + xLook;
    yHilite = yl2 + yLook;
    zHilite = zl2 + zLook;

    len = sqrtf(xHilite * xHilite + yHilite * yHilite + zHilite * zHilite);
    if (len > 0.1) {
        len = 1.0f / len;
        xHilite *= len;
        yHilite *= len;
        zHilite *= len;

        h->h.x2 = twidth * 4 + (s32)((xHilite * xRight + yHilite * yRight + zHilite * zRight) * twidth * 2);
        h->h.y2 = theight * 4 + (s32)((xHilite * xUp + yHilite * yUp + zHilite * zUp) * theight * 2);
    } else {
        h->h.x2 = twidth * 2;
        h->h.y2 = theight * 2;
    }

    l->l[0].l.dir[0] = FTOFRAC8(xRight);
    l->l[0].l.dir[1] = FTOFRAC8(yRight);
    l->l[0].l.dir[2] = FTOFRAC8(zRight);
    l->l[1].l.dir[0] = FTOFRAC8(xUp);
    l->l[1].l.dir[1] = FTOFRAC8(yUp);
    l->l[1].l.dir[2] = FTOFRAC8(zUp);
    l->l[0].l.col[0] = 0x00;
    l->l[0].l.col[1] = 0x00;
    l->l[0].l.col[2] = 0x00;
    l->l[0].l.pad1 = 0x00;
    l->l[0].l.colc[0] = 0x00;
    l->l[0].l.colc[1] = 0x00;
    l->l[0].l.colc[2] = 0x00;
    l->l[0].l.pad2 = 0x00;
    l->l[1].l.col[0] = 0x00;
    l->l[1].l.col[1] = 0x80;
    l->l[1].l.col[2] = 0x00;
    l->l[1].l.pad1 = 0x00;
    l->l[1].l.colc[0] = 0x00;
    l->l[1].l.colc[1] = 0x80;
    l->l[1].l.colc[2] = 0x00;
    l->l[1].l.pad2 = 0x00;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][3] = 1.0f;

    ai = (s32*)&m[0];
    af = (s32*)&m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            e1 = 0x10000 * mf[i][j];
            e2 = 0x10000 * mf[i][j + 1];
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtReflectF.s")
#else
void guLookAtReflectF(Cpu* pCPU) {
    LookAt_s* l;
    CpuFpr data;
    u32* mf;
    u32* sp;
    f32 xEye;
    f32 yEye;
    f32 zEye;
    f32 xAt;
    f32 yAt;
    f32 zAt;
    f32 xUp;
    f32 yUp;
    f32 zUp;
    f32 len;
    f32 xLook;
    f32 yLook;
    f32 zLook;
    f32 xRight;
    f32 yRight;
    f32 zRight;

    cpuGetAddressBuffer(pCPU, &mf, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &l, pCPU->aGPR[5].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[6].u32;
    xEye = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    yEye = data.f32;

    data.u32 = sp[4];
    zEye = data.f32;

    data.u32 = sp[5];
    xAt = data.f32;

    data.u32 = sp[6];
    yAt = data.f32;

    data.u32 = sp[7];
    zAt = data.f32;

    data.u32 = sp[8];
    xUp = data.f32;

    data.u32 = sp[9];
    yUp = data.f32;

    data.u32 = sp[10];
    zUp = data.f32;

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;
    len = -1.0f / sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    l->l[0].l.dir[0] = FTOFRAC8(xRight);
    l->l[0].l.dir[1] = FTOFRAC8(yRight);
    l->l[0].l.dir[2] = FTOFRAC8(zRight);
    l->l[1].l.dir[0] = FTOFRAC8(xUp);
    l->l[1].l.dir[1] = FTOFRAC8(yUp);
    l->l[1].l.dir[2] = FTOFRAC8(zUp);
    l->l[0].l.col[0] = 0x00;
    l->l[0].l.col[1] = 0x00;
    l->l[0].l.col[2] = 0x00;
    l->l[0].l.pad1 = 0x00;
    l->l[0].l.colc[0] = 0x00;
    l->l[0].l.colc[1] = 0x00;
    l->l[0].l.colc[2] = 0x00;
    l->l[0].l.pad2 = 0x00;
    l->l[1].l.col[0] = 0x00;
    l->l[1].l.col[1] = 0x80;
    l->l[1].l.col[2] = 0x00;
    l->l[1].l.pad1 = 0x00;
    l->l[1].l.colc[0] = 0x00;
    l->l[1].l.colc[1] = 0x80;
    l->l[1].l.colc[2] = 0x00;
    l->l[1].l.pad2 = 0x00;

    data.f32 = xRight;
    mf[0 * 4 + 0] = data.u32;

    data.f32 = yRight;
    mf[1 * 4 + 0] = data.u32;

    data.f32 = zRight;
    mf[2 * 4 + 0] = data.u32;

    data.f32 = -(xEye * xRight + yEye * yRight + zEye * zRight);
    mf[3 * 4 + 0] = data.u32;

    data.f32 = xUp;
    mf[0 * 4 + 1] = data.u32;

    data.f32 = yUp;
    mf[1 * 4 + 1] = data.u32;

    data.f32 = zUp;
    mf[2 * 4 + 1] = data.u32;

    data.f32 = -(xEye * xUp + yEye * yUp + zEye * zUp);
    mf[3 * 4 + 1] = data.u32;

    data.f32 = xLook;
    mf[0 * 4 + 2] = data.u32;

    data.f32 = yLook;
    mf[1 * 4 + 2] = data.u32;

    data.f32 = zLook;
    mf[2 * 4 + 2] = data.u32;

    data.f32 = -(xEye * xLook + yEye * yLook + zEye * zLook);
    mf[3 * 4 + 2] = data.u32;

    data.f32 = 0.0f;
    mf[0 * 4 + 3] = data.u32;

    data.f32 = 0.0f;
    mf[1 * 4 + 3] = data.u32;

    data.f32 = 0.0f;
    mf[2 * 4 + 3] = data.u32;

    data.f32 = 1.0f;
    mf[3 * 4 + 3] = data.u32;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtReflect.s")
#else
void guLookAtReflect(Cpu* pCPU) {
    LookAt_s* l;
    s32 i;
    s32 j;
    s32 e1;
    s32 e2;
    CpuFpr data;
    f32 mf[4][4];
    u32* m;
    u32* sp;
    s32* ai;
    s32* af;
    f32 xEye;
    f32 yEye;
    f32 zEye;
    f32 xAt;
    f32 yAt;
    f32 zAt;
    f32 xUp;
    f32 yUp;
    f32 zUp;
    f32 len;
    f32 xLook;
    f32 yLook;
    f32 zLook;
    f32 xRight;
    f32 yRight;
    f32 zRight;
    s32 pad[2];

    cpuGetAddressBuffer(pCPU, &m, pCPU->aGPR[4].u32);
    cpuGetAddressBuffer(pCPU, &l, pCPU->aGPR[5].u32);
    cpuGetAddressBuffer(pCPU, &sp, pCPU->aGPR[29].u32);

    data.u32 = pCPU->aGPR[6].u32;
    xEye = data.f32;

    data.u32 = pCPU->aGPR[7].u32;
    yEye = data.f32;

    data.u32 = sp[4];
    zEye = data.f32;

    data.u32 = sp[5];
    xAt = data.f32;

    data.u32 = sp[6];
    yAt = data.f32;

    data.u32 = sp[7];
    zAt = data.f32;

    data.u32 = sp[8];
    xUp = data.f32;

    data.u32 = sp[9];
    yUp = data.f32;

    data.u32 = sp[10];
    zUp = data.f32;

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;
    len = -1.0f / sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    l->l[0].l.dir[0] = FTOFRAC8(xRight);
    l->l[0].l.dir[1] = FTOFRAC8(yRight);
    l->l[0].l.dir[2] = FTOFRAC8(zRight);
    l->l[1].l.dir[0] = FTOFRAC8(xUp);
    l->l[1].l.dir[1] = FTOFRAC8(yUp);
    l->l[1].l.dir[2] = FTOFRAC8(zUp);
    l->l[0].l.col[0] = 0x00;
    l->l[0].l.col[1] = 0x00;
    l->l[0].l.col[2] = 0x00;
    l->l[0].l.pad1 = 0x00;
    l->l[0].l.colc[0] = 0x00;
    l->l[0].l.colc[1] = 0x00;
    l->l[0].l.colc[2] = 0x00;
    l->l[0].l.pad2 = 0x00;
    l->l[1].l.col[0] = 0x00;
    l->l[1].l.col[1] = 0x80;
    l->l[1].l.col[2] = 0x00;
    l->l[1].l.pad1 = 0x00;
    l->l[1].l.colc[0] = 0x00;
    l->l[1].l.colc[1] = 0x80;
    l->l[1].l.colc[2] = 0x00;
    l->l[1].l.pad2 = 0x00;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][3] = 1.0f;

    ai = (s32*)&m[0];
    af = (s32*)&m[8];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j += 2) {
            e1 = 0x10000 * mf[i][j];
            e2 = 0x10000 * mf[i][j + 1];
            *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
            *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        }
    }
}
#endif

#pragma GLOBAL_ASM("asm/non_matchings/library/osAiSetFrequency.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osAiSetNextBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__osEepStatus.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osEepromRead.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osEepromWrite.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osEepromLongRead.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osEepromLongWrite.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/starfoxCopy.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/pictureSnap_Zelda2.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/dmaSoundRomHandler_ZELDA1.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osViSwapBuffer_Entry.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/zeldaLoadSZS_Entry.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/zeldaLoadSZS_Exit.s")

static s32 libraryFindException(Library* pLibrary, s32 bException) {
    Cpu* pCPU;
    CpuDevice** apDevice;
    u8* aiDevice;
    u32 anCode[6];

    pCPU = SYSTEM_CPU(pLibrary->pHost);
    apDevice = pCPU->apDevice;
    aiDevice = pCPU->aiDevice;

    if (bException) {
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->nPC + 0x00, &anCode[0]);
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->nPC + 0x04, &anCode[1]);
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->nPC + 0x08, &anCode[2]);
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->nPC + 0x0C, &anCode[3]);
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->nPC + 0x10, &anCode[4]);
        CPU_DEVICE_GET32(apDevice, aiDevice, pCPU->nPC + 0x14, &anCode[5]);
    } else {
        CPU_DEVICE_GET32(apDevice, aiDevice, 0x80000180, &anCode[0]);
        CPU_DEVICE_GET32(apDevice, aiDevice, 0x80000184, &anCode[1]);
        CPU_DEVICE_GET32(apDevice, aiDevice, 0x80000188, &anCode[2]);
        CPU_DEVICE_GET32(apDevice, aiDevice, 0x8000018C, &anCode[3]);
        CPU_DEVICE_GET32(apDevice, aiDevice, 0x80000190, &anCode[4]);
        CPU_DEVICE_GET32(apDevice, aiDevice, 0x80000194, &anCode[5]);
    }

    if (MIPS_OP(anCode[0]) == 0x0F && MIPS_OP(anCode[1]) == 0x09 && MIPS_OP(anCode[2]) == 0x00 &&
        (anCode[2] & 0x1F) == 0x08 && anCode[3] == 0) {
        pLibrary->nAddressException = (MIPS_IMM_U16(anCode[0]) << 16) + MIPS_IMM_S16(anCode[1]);
        return 1;
    }

    if (!bException) {
        return 0;
    }

    __cpuBreak(pCPU);
    return 0;
}

static s32 libraryFindVariables(Library* pLibrary) {
    Cpu* pCPU;
    CpuDevice** apDevice;
    u8* aiDevice;
    u32 nAddress;
    u32 nAddressLast;
    u32 nOffset;
    u32 nOpcode;
    u32 anCode[6];

    pCPU = SYSTEM_CPU(pLibrary->pHost);
    apDevice = pCPU->apDevice;
    aiDevice = pCPU->aiDevice;

    CPU_DEVICE_GET32(apDevice, aiDevice, pLibrary->nAddressException + 0, &anCode[0]);
    CPU_DEVICE_GET32(apDevice, aiDevice, pLibrary->nAddressException + 4, &anCode[1]);
    if (MIPS_OP(anCode[0]) == 0x0F && MIPS_OP(anCode[1]) == 0x09) {
        nAddress = (MIPS_IMM_U16(anCode[0]) << 16) + MIPS_IMM_S16(anCode[1]);
        if (!cpuGetAddressOffset(pCPU, (s32*)&nOffset, nAddress)) {
            return 0;
        }

        pLibrary->anAddress[6] = 0x80000000 | nAddress;
        if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[6], nOffset, NULL)) {
            return 0;
        }
    } else {
        return 0;
    }

    nAddress = pLibrary->nAddressException + 8;
    do {
        CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nOpcode);
        nAddress += 4;
    } while (nOpcode != 0x03404021 && nOpcode != 0x03404025);

    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 0, &anCode[0]);
    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 4, &anCode[1]);
    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 8, &anCode[2]);
    nAddressLast = nAddress;
    if (MIPS_OP(anCode[0]) == 0x0F) {
        nAddress = (MIPS_IMM_U16(anCode[0]) << 16) + MIPS_IMM_S16(anCode[1]);
    } else {
        nAddress = (MIPS_IMM_U16(anCode[1]) << 16) + MIPS_IMM_S16(anCode[2]);
    }
    if (!cpuGetAddressOffset(pCPU, (s32*)&nOffset, nAddress)) {
        return 0;
    }

    pLibrary->anAddress[8] = 0x80000000 | nAddress;
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[8], nOffset, NULL)) {
        return 0;
    }

    pLibrary->anAddress[7] = 0x80000000 | (nAddress + 4);
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[7], nOffset + 4, NULL)) {
        return 0;
    }

    pLibrary->anAddress[5] = 0x80000000 | (nAddress - 4);
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[5], nOffset - 4, NULL)) {
        return 0;
    }

    pLibrary->anAddress[4] = 0x80000000 | (nAddress - 8);
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[4], nOffset - 8, NULL)) {
        return 0;
    }

    nAddress = nAddressLast;
    do {
        CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nOpcode);
        nAddress += 4;
    } while (nOpcode != 0x11200013 && nOpcode != 0x11200011 && nOpcode != 0x1120000D && nOpcode != 0x1120000B &&
             nOpcode != 0x11200009);

    nAddressLast = nAddress;
    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 4, &anCode[0]);
    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 8, &anCode[1]);

    nAddress = (MIPS_IMM_U16(anCode[0]) << 16) + MIPS_IMM_S16(anCode[1]);
    if (nAddress == 0xC0000008) {
        return 0;
    }
    if (!cpuGetAddressOffset(pCPU, (s32*)&nOffset, nAddress)) {
        return 0;
    }

    pLibrary->anAddress[3] = 0x80000000 | nAddress;
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[3], nOffset, NULL)) {
        return 0;
    }

    pLibrary->anAddress[2] = 0x80000000 | (nAddress - 4);
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[2], nOffset - 4, NULL)) {
        return 0;
    }

    pLibrary->anAddress[1] = 0x80000000 | (nAddress - 8);
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[1], nOffset - 8, NULL)) {
        return 0;
    }

    pLibrary->anAddress[0] = 0x80000000 | (nAddress - 16);
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[0], nOffset - 16, NULL)) {
        return 0;
    }

    nAddress = nAddressLast;
    do {
        CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nOpcode);
        nAddress += 4;
    } while (nOpcode != 0x40895800);

    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 0, &anCode[0]);
    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 4, &anCode[1]);

    if (MIPS_OP(anCode[0]) == 0x03) {
        nAddress = ((nAddress + 0) & 0xF0000000) | (MIPS_TARGET(anCode[0]) << 2);
    } else {
        nAddress = ((nAddress + 4) & 0xF0000000) | (MIPS_TARGET(anCode[1]) << 2);
    }

    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 0, &anCode[0]);
    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 4, &anCode[1]);
    CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 8, &anCode[2]);
    if (MIPS_OP(anCode[0]) == 0x0F) {
        nAddress = (MIPS_IMM_U16(anCode[0]) << 16) + MIPS_IMM_S16(anCode[1]);
    } else {
        nAddress = (MIPS_IMM_U16(anCode[1]) << 16) + MIPS_IMM_S16(anCode[2]);
    }
    if (!cpuGetAddressOffset(pCPU, (s32*)&nOffset, nAddress)) {
        return 0;
    }

    pLibrary->anAddress[9] = 0x80000000 | nAddress;
    if (!ramGetBuffer(SYSTEM_RAM(pLibrary->pHost), &pLibrary->apData[9], nOffset, NULL)) {
        return 0;
    }

    pLibrary->nFlag |= 4;
    return 1;
}

static s32 libraryFindFunctions(Library* pLibrary) {
    Cpu* pCPU;
    s32 iFunction;
    CpuDevice** apDevice;
    u8* aiDevice;
    u32 nOpcode;
    u32* pnCode;
    u32 nAddress;
    u32 nAddressLast;
    u32 nAddressEnqueueThread;
    u32 nAddressDispatchThread;

    nAddressEnqueueThread = -1;
    nAddressDispatchThread = -1;
    nAddress = pLibrary->nAddressException;

    pCPU = SYSTEM_CPU(pLibrary->pHost);
    apDevice = pCPU->apDevice;
    aiDevice = pCPU->aiDevice;

    do {
        CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nOpcode);
        if (MIPS_OP(nOpcode) == 0x03) {
            nAddressLast = (nAddress & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
            CPU_DEVICE_GET32(apDevice, aiDevice, nAddress + 8, &nOpcode);
            if (MIPS_OP(nOpcode) == 0x02) {
                nAddressEnqueueThread = nAddressLast;
                nAddressDispatchThread = (nAddress & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
            }
        }
        nAddress += 4;
    } while (nOpcode != 0x400A4000);

    for (iFunction = 0;
         iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != (LibraryFuncImpl)send_mesg;
         iFunction++) {}
    if (iFunction < ARRAY_COUNTU(gaFunction)) {
        nAddress = pLibrary->nAddressException;
        do {
            CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nOpcode);
            nAddress += 4;
        } while (nOpcode != 0x400A4000);

        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddress + 0x14)) {
            return 0;
        }

        *(pnCode++) = 0x7C000000 | iFunction;
        *(pnCode++) = 0x03E00008;
        *(pnCode++) = 0;
    }

    for (iFunction = 0; iFunction < ARRAY_COUNTU(gaFunction) &&
                        gaFunction[iFunction].pfLibrary != (LibraryFuncImpl)__osEnqueueAndYield;
         iFunction++) {}
    if (iFunction < ARRAY_COUNTU(gaFunction) && (nAddress = nAddressEnqueueThread) != -1) {
        do {
            nAddress -= 4;
            CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nOpcode);
        } while (nOpcode != 0x40086000);

        do {
            nAddress -= 4;
            CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nOpcode);
        } while (MIPS_OP(nOpcode) != 0x02 && (nOpcode & 0xFFFF0000) != 0x10000000 && MIPS_OP(nOpcode) != 0x00 &&
                 MIPS_FUNCT(nOpcode) != 0x08);

        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddress + 8)) {
            return 0;
        }

        *(pnCode++) = 0x7C000000 | iFunction;
    }

    for (iFunction = 0;
         iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != (LibraryFuncImpl)__osEnqueueThread;
         iFunction++) {}
    if (iFunction < ARRAY_COUNTU(gaFunction) && nAddressEnqueueThread != -1) {
        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddressEnqueueThread)) {
            return 0;
        }
        *(pnCode++) = 0x7C000000 | iFunction;
        *(pnCode++) = 0x03E00008;
        *(pnCode++) = 0;
    }

    for (iFunction = 0;
         iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != (LibraryFuncImpl)__osPopThread;
         iFunction++) {}
    // bug: Tests if nAddressEnqueueThread + 8 != -1 instead of nAddressEnqueueThread != -1
    if (iFunction < ARRAY_COUNTU(gaFunction) && (nAddress = nAddressEnqueueThread + 8) != -1) {
        do {
            CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nOpcode);
            nAddress += 4;
        } while (nOpcode != 0x03E00008);

        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddress + 4)) {
            return 0;
        }

        *(pnCode++) = 0x7C000000 | iFunction;
        *(pnCode++) = 0x03E00008;
        *(pnCode++) = 0;
    }

    for (iFunction = 0;
         iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != (LibraryFuncImpl)__osDispatchThread;
         iFunction++) {}
    if (iFunction < ARRAY_COUNTU(gaFunction) && nAddressDispatchThread != -1) {
        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddressDispatchThread)) {
            return 0;
        }

        *(pnCode++) = 0x7C000000 | iFunction;
    }

    return 1;
}

s32 libraryTestFunction(Library* pLibrary, CpuFunction* pFunction) {
    s32 iFunction;
    s32 iData;
    s32 bFlag;
    s32 bDone;
    s32 bReturn;
    u32 iCode;
    u32* pnCode;
    u32* pnCodeTemp;
    u32 nSizeCode;
    u32 nChecksum;
    u32 nOpcode;
    u32 nAddress;

    s32 var_r0;

    if (!cpuGetFunctionChecksum(SYSTEM_CPU(pLibrary->pHost), &nChecksum, pFunction)) {
        return 0;
    }

    nSizeCode = ((pFunction->nAddress1 - pFunction->nAddress0) >> 2) + 1;

    for (iFunction = 0; iFunction < ARRAY_COUNTU(gaFunction); iFunction++) {
        for (iData = 0; gaFunction[iFunction].anData[iData] != 0; iData += 2) {
            if (gaFunction[iFunction].anData[iData + 1] != nChecksum ||
                gaFunction[iFunction].anData[iData] != nSizeCode) {
                continue;
            }

            bDone = 0;
            bReturn = 1;

            if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, pFunction->nAddress0)) {
                return 0;
            }

            nOpcode = pnCode[0];
            var_r0 = MIPS_OP(nOpcode) == 0x1F ? 0 : 1;
            bFlag = var_r0;
            if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)osEepromLongRead && nChecksum == 0x5B919EF9) {
                nAddress = (pFunction->nAddress0 & 0xF0000000) | (MIPS_TARGET(pnCode[17]) << 2);
                if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCodeTemp, nAddress)) {
                    return 0;
                }
                if (pnCodeTemp[10] != 0xAFA00030) {
                    bDone = 1;
                    iFunction += 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)osEepromLongWrite &&
                       nChecksum == 0x5B919EF9) {
                nAddress = (pFunction->nAddress0 & 0xF0000000) | (MIPS_TARGET(pnCode[17]) << 2);
                if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCodeTemp, nAddress)) {
                    return 0;
                }
                if (pnCodeTemp[10] == 0xAFA00030) {
                    bDone = 1;
                    iFunction -= 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)__osSpSetStatus) {
                nChecksum = 0;
                for (iCode = 0; iCode < nSizeCode; iCode++) {
                    nChecksum += pnCode[iCode];
                }
                if (nChecksum != 0xC1E27C6E && nChecksum != 0xEDB2A41C && nChecksum != 0x2068A41C) {
                    bFlag = 0;
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)osInvalICache) {
                if (MIPS_IMM_U16(pnCode[2]) == 0x2000) {
                    bDone = 1;
                    iFunction += 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == NULL && nChecksum == 0x376979EF) {
                if (MIPS_IMM_U16(pnCode[2]) == 0x4000) {
                    bDone = 1;
                    iFunction -= 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)__osDisableInt) {
                if (pnCode[2] == 0 && pnCode[3] == 0) {
                    pnCode += 4;
                    while (pnCode[0] == 0) {
                        pnCode++;
                    }
                    bFlag = MIPS_OP(pnCode[0]) == 0x1F ? 0 : 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)osViSwapBuffer_Entry) {
                if (bFlag) {
                    bReturn = 0;
                    if ((nOpcode & 0xFFFF0000) != 0x27BD0000) {
                        xlPostText(D_800EFF34, D_800EFF7C, 6971, nOpcode);
                    } else {
                        pLibrary->nAddStackSwap = MIPS_IMM_S16(nOpcode);
                    }
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)GenPerspective_1080) {
                if (((System*)pLibrary->pHost)->eTypeROM != SRT_1080) {
                    bFlag = 0;
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)pictureSnap_Zelda2) {
                if (((System*)pLibrary->pHost)->eTypeROM != SRT_ZELDA2) {
                    bFlag = 0;
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)zeldaLoadSZS_Entry) {
                if (((System*)pLibrary->pHost)->eTypeROM != SRT_ZELDA1) {
                    bFlag = 0;
                }
                if (bFlag) {
                    pnCodeTemp = pnCode;
                    bReturn = 0;
                    while (pnCodeTemp[0] != 0x27BD0040) {
                        pnCodeTemp++;
                    }
                    pnCodeTemp[0] = 0x7C000000 | (iFunction + 1);
                }
            } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)dmaSoundRomHandler_ZELDA1) {
                if (((System*)pLibrary->pHost)->eTypeROM != SRT_ZELDA1) {
                    bFlag = 0;
                } else {
                    nOpcode = pnCode[2];
                    if (iData != 0 && nOpcode != 0x0C000F3C) {
                        bFlag = 0;
                    }
                }
            }

            if (bFlag) {
                pFunction->timeToLive = 0;
                *(pnCode++) = 0x7C000000 | iFunction;
                if (bReturn != 0) {
                    *(pnCode++) = 0x03E00008;
                    *(pnCode++) = 0;
                }
                return 1;
            }

            if (bDone) {
                return 1;
            }
        }
    }

    return 1;
}

static s32 librarySearch(Library* pLibrary, CpuFunction* pFunction) {
    if (pFunction->left != NULL && !librarySearch(pLibrary, pFunction->left)) {
        return 0;
    } else if (pFunction->right != NULL && !librarySearch(pLibrary, pFunction->right)) {
        return 0;
    } else if (!libraryTestFunction(pLibrary, pFunction)) {
        return 0;
    }
    return 1;
}

inline s32 libraryUpdate(Library* pLibrary) {
    Cpu* pCPU;
    CpuFunction* pFunction;

    pCPU = SYSTEM_CPU(pLibrary->pHost);
    if (pCPU->gTree == NULL) {
        cpuFindFunction(pCPU, pCPU->nPC, &pFunction);
    }

    if (pCPU->gTree != NULL) {
        if (pCPU->gTree->left != NULL && !librarySearch(pLibrary, pCPU->gTree->left)) {
            return 0;
        } else if (pCPU->gTree->right != NULL && !librarySearch(pLibrary, pCPU->gTree->right)) {
            return 0;
        }
    }

    return 1;
}

s32 libraryFunctionReplaced(Library* pLibrary, s32 iFunction) {
    if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)send_mesg) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)__osEnqueueAndYield) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)__osEnqueueThread) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)__osPopThread) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)__osDispatchThread) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)__sinf) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)osViSwapBuffer_Entry) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)zeldaLoadSZS_Entry) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == (LibraryFuncImpl)zeldaLoadSZS_Exit) {
        return 0;
    }
    return 1;
}

s32 libraryCall(Library* pLibrary, Cpu* pCPU, s32 iFunction) {
    if (!(pLibrary->nFlag & 1)) {
        if (libraryFindException(pLibrary, iFunction == -1 ? 1 : 0)) {
            pLibrary->nFlag |= 1;
            if (libraryFindVariables(pLibrary)) {
                pLibrary->nFlag |= 2;
                libraryFindFunctions(pLibrary);
            }
        }
    }

    if (iFunction == -1) {
        pLibrary->nFlag |= 1;
        if (pLibrary->nFlag & 2) {
            __osException(pCPU);
        }
    } else {
        if (gaFunction[iFunction].pfLibrary != NULL) {
            gaFunction[iFunction].pfLibrary(pCPU);
        }
    }

    return 1;
}

s32 libraryEvent(Library* pLibrary, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pLibrary->nFlag = 0;
            pLibrary->pHost = pArgument;
            pLibrary->nAddressException = -1;
            pLibrary->nAddStackSwap = 0;
            pLibrary->aFunction = gaFunction;
            pLibrary->nCountFunction = ARRAY_COUNT(gaFunction);
            break;
        case 0:
        case 1:
        case 3:
        case 0x1002:
            break;
        case 0x1003:
            if (!libraryUpdate(pLibrary)) {
                return 0;
            }
            break;
        default:
            return 0;
    }

    return 1;
}
