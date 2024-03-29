#include "emulator/library.h"
#include "emulator/frame.h"
#include "emulator/library_jumptables.h"
#include "emulator/ram.h"
#include "emulator/system.h"
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
        send_mesg,
        {0},
    },
    {
        "__osEnqueueAndYield",
        __osEnqueueAndYield,
        {0},
    },
    {
        "__osEnqueueThread",
        __osEnqueueThread,
        {0},
    },
    {
        "__osPopThread",
        __osPopThread,
        {0},
    },
    {
        "__osDispatchThread",
        __osDispatchThread,
        {0},
    },
    {
        "osGetMemSize",
        osGetMemSize,
        {0x00000045, 0xE82F9DC4},
    },
    {
        "osInvalDCache",
        NULL,
        {0x0000002C, 0x384D2C37, 0x0000002B, 0x3954FA00},
    },
    {
        "osInvalICache",
        osInvalICache,
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
        __osDisableInt,
        {0x00000020, 0x3F5B05D4, 0x00000022, 0x3F5B35D1, 0x00000008, 0x10310240, 0x0000000C, 0x10310300},
    },
    {
        "__osRestoreInt",
        __osRestoreInt,
        {0x00000007, 0x10000400},
    },
    {
        "__osSpSetStatus",
        __osSpSetStatus,
        {0x00000003, 0x0000F02B, 0x00000004, 0x003CD02B, 0x0000000B, 0x5604E8E1},
    },
    {
        "__cosf",
        __cosf,
        {0x0000007E, 0x0EA800A6, 0x0000005A, 0xA7BF8A16, 0x0000008E, 0x417938C2, 0x000002B5, 0x82283827},
    },
    {
        "__sinf",
        __sinf,
        {0x0000007D, 0x9DDC3AD1, 0x00000070, 0x972CC1AA, 0x000000AB, 0x537273BE, 0x00000090, 0xA23718AB},
    },
    {
        "bzero",
        _bzero,
        {0x00000028, 0x6A68DD7D, 0x00000027, 0x6A68E5DB},
    },
    {
        "bcopy",
        _bcopy,
        {0x000000CE, 0xFF1D6C61, 0x000000F0, 0x082F2020, 0x000000C7, 0xB1771900, 0x000000C7, 0xC732F943},
    },
    {
        "memcpy",
        _memcpy,
        {0x00000026, 0xC912B3A8},
    },
    {
        "osVirtualToPhysical",
        osVirtualToPhysical,
        {0x00000037, 0x5F70CFD6, 0x00000015, 0x17E44014},
    },
    {
        "osPhysicalToVirtual",
        osPhysicalToVirtual,
        {0x0000000D, 0x2B8FBACB, 0x00000003, 0x0000F000},
    },
    {
        "guMtxF2L",
        guMtxF2L,
        {0x00000026, 0x686C0856, 0x00000019, 0x7CC68902, 0x00000040, 0x4425DE45, 0x0000005C, 0x220BB2B0, 0x00000027,
         0x60FF87FD},
    },
    {
        "guMtxCatF",
        guMtxCatF,
        {0x00000037, 0x91255B90},
    },
    {
        "guMtxIdentF",
        guMtxIdentF,
        {0x00000014, 0x14BCF092, 0x00000022, 0x69E2607E, 0x0000003B, 0x03585A21},
    },
    {
        "guMtxIdent",
        guMtxIdent,
        {0x0000003C, 0xA20CBF46},
    },
    {
        "guOrthoF",
        guOrthoF,
        {0x00000055, 0x7F37D860, 0x00000080, 0x7C65E2F4},
    },
    {
        "guOrtho",
        guOrtho,
        {0x0000001A, 0xB0EC9807, 0x00000053, 0xA76A660F},
    },
    {
        "guPerspectiveF",
        guPerspectiveF,
        {0x0000008C, 0x9EC5FEAB},
    },
    {
        "guPerspective",
        guPerspective,
        {0x00000072, 0x2B0214E7, 0x00000016, 0x99A85378, 0x0000001B, 0x8CC9B39E},
    },
    {
        "guScaleF",
        guScaleF,
        {0x00000015, 0xCA91FB16, 0x00000018, 0x8497864D, 0x00000020, 0xBC8FF165},
    },
    {
        "guScale",
        guScale,
        {0x0000001F, 0xA2C19EFB, 0x00000012, 0x3E48EAE5},
    },
    {
        "guRotateF",
        guRotateF,
        {0x00000065, 0xD5CF8FAE, 0x00000057, 0xFA3518F4, 0x00000093, 0x9AA6B979},
    },
    {
        "guRotate",
        guRotate,
        {0x0000005E, 0x06A7BCE6, 0x00000014, 0x698E4905, 0x00000017, 0x36AEAFA5},
    },
    {
        "guTranslateF",
        guTranslateF,
        {0x0000001B, 0xC211F512},
    },
    {
        "guTranslate",
        guTranslate,
        {0x0000001C, 0x80FA01A4, 0x00000015, 0x71F205A8},
    },
    {
        "guLookAtF",
        guLookAtF,
        {0x00000107, 0xB11E3841},
    },
    {
        "guLookAt",
        guLookAt,
        {0x000000E1, 0xE544558C},
    },
    {
        "guLookAtHiliteF",
        guLookAtHiliteF,
        {0x000002E9, 0xCA0CCB5F},
    },
    {
        "guLookAtHilite",
        guLookAtHilite,
        {0x00000035, 0xC2E98EC2, 0x00000035, 0x6B82DCD5},
    },
    {
        "guLookAtReflectF",
        guLookAtReflectF,
        {0x0000015E, 0x55ACFC31, 0x000001BF, 0xBFD63279},
    },
    {
        "guLookAtReflect",
        guLookAtReflect,
        {0x0000001B, 0xD6F88212, 0x00000023, 0xD70B815D},
    },
    {
        "osAiSetFrequency",
        osAiSetFrequency,
        {0x00000046, 0x88F8FC90, 0x00000058, 0xA177D03D, 0x00000051, 0xD3B85DEF},
    },
    {
        "osAiSetNextBuffer",
        osAiSetNextBuffer,
        {0x00000025, 0x5ACF0804, 0x0000002A, 0x978F50F1, 0x0000001D, 0x47200DC9},
    },
    {
        "__osEepStatus",
        __osEepStatus,
        {0x000000A8, 0x8FBCE3BC, 0x00000067, 0x9870CAC4, 0x00000089, 0x807A196A},
    },
    {
        "osEepromRead",
        osEepromRead,
        {0x00000066, 0x380B07CA, 0x000000A5, 0x947050BF, 0x0000007C, 0x66EC38E8},
    },
    {
        "osEepromWrite",
        osEepromWrite,
        {0x0000005A, 0x5FCCA978, 0x00000080, 0xF6971795, 0x0000006C, 0x07B6DF06},
    },
    {
        "osEepromLongRead",
        osEepromLongRead,
        {0x0000001C, 0x63BA7FE0, 0x0000002E, 0xF25B283A, 0x0000004F, 0x5B919EF9},
    },
    {
        "osEepromLongWrite",
        osEepromLongWrite,
        {0x00000039, 0xED7A2E0B, 0x00000044, 0xF6B9E6BD, 0x0000004F, 0x5B919EF9},
    },
    {
        "starfoxCopy",
        starfoxCopy,
        {0x00000026, 0x158C0203},
    },
    {
        "GenPerspective",
        GenPerspective_1080,
        {0x0000002F, 0x3879CA27},
    },
    {
        "pictureSnap_Zelda2",
        pictureSnap_Zelda2,
        {0x000001F0, 0xC2739708},
    },
    {
        "dmaSoundRomHandler_ZELDA1",
        dmaSoundRomHandler_ZELDA1,
        {0x0000001D, 0x7C4D46F6, 0x00000008, 0x008D2AC3},
    },
    {
        "osViSwapBuffer_Entry",
        osViSwapBuffer_Entry,
        {0x00000011, 0x5147109A, 0x00000038, 0xBF405C09, 0x00000014, 0x745C58FD, 0x00000013, 0x6467CCEE},
    },
    {
        "zeldaLoadSZS_Entry",
        zeldaLoadSZS_Entry,
        {0x0000005A, 0x8EA707A2},
    },
    {
        "zeldaLoadSZS_Exit",
        zeldaLoadSZS_Exit,
        {0},
    },
};

char D_800EFF34[] = "TestFunction: INTERNAL ERROR: osViSwapBuffer: No ADDIU opcode: 0x%08x";
char D_800EFF7C[] = "library.c";

void* jtbl_800EFF88[] = {
    &lbl_80097620, &lbl_800971AC, &lbl_80097208, &lbl_80097264, &lbl_80097488,
    &lbl_800974A0, &lbl_800974B4, &lbl_800974BC, &lbl_800974C4,
};

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

#pragma GLOBAL_ASM("asm/non_matchings/library/__osException.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/send_mesg.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__osEnqueueAndYield.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__osEnqueueThread.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__osPopThread.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__osDispatchThread.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osGetMemSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osInvalICache.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__osDisableInt.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__osRestoreInt.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__osSpSetStatus.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__cosf.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/__sinf.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/_bzero.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/_bcopy.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/_memcpy.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osPhysicalToVirtual.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/osVirtualToPhysical.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guMtxCatF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guMtxF2L.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guMtxIdentF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guMtxIdent.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guOrthoF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guOrtho.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/library/GenPerspective_1080.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guScaleF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guScale.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guTranslateF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guTranslate.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guRotateF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guRotate.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAt.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtHiliteF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtHilite.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtReflectF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guLookAtReflect.s")

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

#define DEVICE_GET32(nAddress, pValue)                                                          \
    {                                                                                           \
        CpuDevice* pDevice = apDevice[aiDevice[(u32)(nAddress) >> 16]];                         \
        pDevice->pfGet32(pDevice->pObject, (nAddress) + pDevice->nOffsetAddress, (s32*)pValue); \
    }

static s32 libraryFindException(Library* pLibrary, s32 bException) {
    Cpu* pCPU;
    CpuDevice** apDevice;
    u8* aiDevice;
    u32 anCode[6];

    pCPU = SYSTEM_CPU(pLibrary->pHost);
    apDevice = pCPU->apDevice;
    aiDevice = pCPU->aiDevice;

    if (bException) {
        DEVICE_GET32(pCPU->nPC + 0x00, &anCode[0]);
        DEVICE_GET32(pCPU->nPC + 0x04, &anCode[1]);
        DEVICE_GET32(pCPU->nPC + 0x08, &anCode[2]);
        DEVICE_GET32(pCPU->nPC + 0x0C, &anCode[3]);
        DEVICE_GET32(pCPU->nPC + 0x10, &anCode[4]);
        DEVICE_GET32(pCPU->nPC + 0x14, &anCode[5]);
    } else {
        DEVICE_GET32(0x80000180, &anCode[0]);
        DEVICE_GET32(0x80000184, &anCode[1]);
        DEVICE_GET32(0x80000188, &anCode[2]);
        DEVICE_GET32(0x8000018C, &anCode[3]);
        DEVICE_GET32(0x80000190, &anCode[4]);
        DEVICE_GET32(0x80000194, &anCode[5]);
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

    DEVICE_GET32(pLibrary->nAddressException + 0, &anCode[0]);
    DEVICE_GET32(pLibrary->nAddressException + 4, &anCode[1]);
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
        DEVICE_GET32(nAddress, &nOpcode);
        nAddress += 4;
    } while (nOpcode != 0x03404021 && nOpcode != 0x03404025);

    DEVICE_GET32(nAddress + 0, &anCode[0]);
    DEVICE_GET32(nAddress + 4, &anCode[1]);
    DEVICE_GET32(nAddress + 8, &anCode[2]);
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
        DEVICE_GET32(nAddress, &nOpcode);
        nAddress += 4;
    } while (nOpcode != 0x11200013 && nOpcode != 0x11200011 && nOpcode != 0x1120000D && nOpcode != 0x1120000B &&
             nOpcode != 0x11200009);

    nAddressLast = nAddress;
    DEVICE_GET32(nAddress + 4, &anCode[0]);
    DEVICE_GET32(nAddress + 8, &anCode[1]);

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
        DEVICE_GET32(nAddress, &nOpcode);
        nAddress += 4;
    } while (nOpcode != 0x40895800);

    DEVICE_GET32(nAddress + 0, &anCode[0]);
    DEVICE_GET32(nAddress + 4, &anCode[1]);

    if (MIPS_OP(anCode[0]) == 0x03) {
        nAddress = ((nAddress + 0) & 0xF0000000) | (MIPS_TARGET(anCode[0]) << 2);
    } else {
        nAddress = ((nAddress + 4) & 0xF0000000) | (MIPS_TARGET(anCode[1]) << 2);
    }

    DEVICE_GET32(nAddress + 0, &anCode[0]);
    DEVICE_GET32(nAddress + 4, &anCode[1]);
    DEVICE_GET32(nAddress + 8, &anCode[2]);
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
        DEVICE_GET32(nAddress, &nOpcode);
        if (MIPS_OP(nOpcode) == 0x03) {
            nAddressLast = (nAddress & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
            DEVICE_GET32(nAddress + 8, &nOpcode);
            if (MIPS_OP(nOpcode) == 0x02) {
                nAddressEnqueueThread = nAddressLast;
                nAddressDispatchThread = (nAddress & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
            }
        }
        nAddress += 4;
    } while (nOpcode != 0x400A4000);

    for (iFunction = 0; iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != &send_mesg;
         iFunction++) {}
    if (iFunction < ARRAY_COUNTU(gaFunction)) {
        nAddress = pLibrary->nAddressException;
        do {
            DEVICE_GET32(nAddress, &nOpcode);
            nAddress += 4;
        } while (nOpcode != 0x400A4000);

        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddress + 0x14)) {
            return 0;
        }

        *(pnCode++) = 0x7C000000 | iFunction;
        *(pnCode++) = 0x03E00008;
        *(pnCode++) = 0;
    }

    for (iFunction = 0; iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != &__osEnqueueAndYield;
         iFunction++) {}
    if (iFunction < ARRAY_COUNTU(gaFunction) && (nAddress = nAddressEnqueueThread) != -1) {
        do {
            nAddress -= 4;
            DEVICE_GET32(nAddress, &nOpcode);
        } while (nOpcode != 0x40086000);

        do {
            nAddress -= 4;
            DEVICE_GET32(nAddress, &nOpcode);
        } while (MIPS_OP(nOpcode) != 0x02 && (nOpcode & 0xFFFF0000) != 0x10000000 && MIPS_OP(nOpcode) != 0x00 &&
                 MIPS_FUNCT(nOpcode) != 0x08);

        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddress + 8)) {
            return 0;
        }

        *(pnCode++) = 0x7C000000 | iFunction;
    }

    for (iFunction = 0; iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != &__osEnqueueThread;
         iFunction++) {}
    if (iFunction < ARRAY_COUNTU(gaFunction) && nAddressEnqueueThread != -1) {
        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddressEnqueueThread)) {
            return 0;
        }
        *(pnCode++) = 0x7C000000 | iFunction;
        *(pnCode++) = 0x03E00008;
        *(pnCode++) = 0;
    }

    for (iFunction = 0; iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != &__osPopThread;
         iFunction++) {}
    // bug: Tests if nAddressEnqueueThread + 8 != -1 instead of nAddressEnqueueThread != -1
    if (iFunction < ARRAY_COUNTU(gaFunction) && (nAddress = nAddressEnqueueThread + 8) != -1) {
        do {
            DEVICE_GET32(nAddress, &nOpcode);
            nAddress += 4;
        } while (nOpcode != 0x03E00008);

        if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCode, nAddress + 4)) {
            return 0;
        }

        *(pnCode++) = 0x7C000000 | iFunction;
        *(pnCode++) = 0x03E00008;
        *(pnCode++) = 0;
    }

    for (iFunction = 0; iFunction < ARRAY_COUNTU(gaFunction) && gaFunction[iFunction].pfLibrary != &__osDispatchThread;
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
            if (gaFunction[iFunction].pfLibrary == &osEepromLongRead && nChecksum == 0x5B919EF9) {
                nAddress = (pFunction->nAddress0 & 0xF0000000) | (MIPS_TARGET(pnCode[17]) << 2);
                if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCodeTemp, nAddress)) {
                    return 0;
                }
                if (pnCodeTemp[10] != 0xAFA00030) {
                    bDone = 1;
                    iFunction += 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == &osEepromLongWrite && nChecksum == 0x5B919EF9) {
                nAddress = (pFunction->nAddress0 & 0xF0000000) | (MIPS_TARGET(pnCode[17]) << 2);
                if (!cpuGetAddressBuffer(SYSTEM_CPU(pLibrary->pHost), &pnCodeTemp, nAddress)) {
                    return 0;
                }
                if (pnCodeTemp[10] == 0xAFA00030) {
                    bDone = 1;
                    iFunction -= 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == &__osSpSetStatus) {
                nChecksum = 0;
                for (iCode = 0; iCode < nSizeCode; iCode++) {
                    nChecksum += pnCode[iCode];
                }
                if (nChecksum != 0xC1E27C6E && nChecksum != 0xEDB2A41C && nChecksum != 0x2068A41C) {
                    bFlag = 0;
                }
            } else if (gaFunction[iFunction].pfLibrary == &osInvalICache) {
                if (MIPS_IMM_U16(pnCode[2]) == 0x2000) {
                    bDone = 1;
                    iFunction += 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == 0 && nChecksum == 0x376979EF) {
                if (MIPS_IMM_U16(pnCode[2]) == 0x4000) {
                    bDone = 1;
                    iFunction -= 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == &__osDisableInt) {
                if (pnCode[2] == 0 && pnCode[3] == 0) {
                    pnCode += 4;
                    while (pnCode[0] == 0) {
                        pnCode++;
                    }
                    bFlag = MIPS_OP(pnCode[0]) == 0x1F ? 0 : 1;
                }
            } else if (gaFunction[iFunction].pfLibrary == &osViSwapBuffer_Entry) {
                if (bFlag) {
                    bReturn = 0;
                    if ((nOpcode & 0xFFFF0000) != 0x27BD0000) {
                        xlPostText(D_800EFF34, D_800EFF7C, 6971, nOpcode);
                    } else {
                        pLibrary->nAddStackSwap = MIPS_IMM_S16(nOpcode);
                    }
                }
            } else if (gaFunction[iFunction].pfLibrary == &GenPerspective_1080) {
                if (((System*)pLibrary->pHost)->eTypeROM != SRT_1080) {
                    bFlag = 0;
                }
            } else if (gaFunction[iFunction].pfLibrary == &pictureSnap_Zelda2) {
                if (((System*)pLibrary->pHost)->eTypeROM != SRT_ZELDA2) {
                    bFlag = 0;
                }
            } else if (gaFunction[iFunction].pfLibrary == &zeldaLoadSZS_Entry) {
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
            } else if (gaFunction[iFunction].pfLibrary == &dmaSoundRomHandler_ZELDA1) {
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
    if (gaFunction[iFunction].pfLibrary == &send_mesg) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == &__osEnqueueAndYield) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == &__osEnqueueThread) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == &__osPopThread) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == &__osDispatchThread) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == &__sinf) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == &osViSwapBuffer_Entry) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == &zeldaLoadSZS_Entry) {
        return 0;
    } else if (gaFunction[iFunction].pfLibrary == &zeldaLoadSZS_Exit) {
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
