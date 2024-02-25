#include "library.h"
#include "library_jumptables.h"
#include "xlObject.h"

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

LibraryFunction gaFunction[54] = {
    {
        "send_mesg",
        send_mesg,
        {
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__osEnqueueAndYield",
        __osEnqueueAndYield,
        {
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__osEnqueueThread",
        __osEnqueueThread,
        {
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__osPopThread",
        __osPopThread,
        {
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__osDispatchThread",
        __osDispatchThread,
        {
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osGetMemSize",
        osGetMemSize,
        {
            0x00000045,
            0xE82F9DC4,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osInvalDCache",
        NULL,
        {
            0x0000002C,
            0x384D2C37,
            0x0000002B,
            0x3954FA00,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osInvalICache",
        osInvalICache,
        {
            0x0000001D,
            0x376979EF,
            0x0000001D,
            0x3769A92F,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osWritebackDCache",
        NULL,
        {
            0x0000001D,
            0x376979EF,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osWritebackDCacheAll",
        NULL,
        {
            0x0000000A,
            0x0F38926F,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__osDisableInt",
        __osDisableInt,
        {
            0x00000020,
            0x3F5B05D4,
            0x00000022,
            0x3F5B35D1,
            0x00000008,
            0x10310240,
            0x0000000C,
            0x10310300,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__osRestoreInt",
        __osRestoreInt,
        {
            0x00000007,
            0x10000400,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__osSpSetStatus",
        __osSpSetStatus,
        {
            0x00000003,
            0x0000F02B,
            0x00000004,
            0x003CD02B,
            0x0000000B,
            0x5604E8E1,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__cosf",
        __cosf,
        {
            0x0000007E,
            0x0EA800A6,
            0x0000005A,
            0xA7BF8A16,
            0x0000008E,
            0x417938C2,
            0x000002B5,
            0x82283827,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__sinf",
        __sinf,
        {
            0x0000007D,
            0x9DDC3AD1,
            0x00000070,
            0x972CC1AA,
            0x000000AB,
            0x537273BE,
            0x00000090,
            0xA23718AB,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "bzero",
        _bzero,
        {
            0x00000028,
            0x6A68DD7D,
            0x00000027,
            0x6A68E5DB,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "bcopy",
        _bcopy,
        {
            0x000000CE,
            0xFF1D6C61,
            0x000000F0,
            0x082F2020,
            0x000000C7,
            0xB1771900,
            0x000000C7,
            0xC732F943,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "memcpy",
        _memcpy,
        {
            0x00000026,
            0xC912B3A8,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osVirtualToPhysical",
        osVirtualToPhysical,
        {
            0x00000037,
            0x5F70CFD6,
            0x00000015,
            0x17E44014,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osPhysicalToVirtual",
        osPhysicalToVirtual,
        {
            0x0000000D,
            0x2B8FBACB,
            0x00000003,
            0x0000F000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guMtxF2L",
        guMtxF2L,
        {
            0x00000026,
            0x686C0856,
            0x00000019,
            0x7CC68902,
            0x00000040,
            0x4425DE45,
            0x0000005C,
            0x220BB2B0,
            0x00000027,
            0x60FF87FD,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guMtxCatF",
        guMtxCatF,
        {
            0x00000037,
            0x91255B90,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guMtxIdentF",
        guMtxIdentF,
        {
            0x00000014,
            0x14BCF092,
            0x00000022,
            0x69E2607E,
            0x0000003B,
            0x03585A21,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guMtxIdent",
        guMtxIdent,
        {
            0x0000003C,
            0xA20CBF46,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guOrthoF",
        guOrthoF,
        {
            0x00000055,
            0x7F37D860,
            0x00000080,
            0x7C65E2F4,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guOrtho",
        guOrtho,
        {
            0x0000001A,
            0xB0EC9807,
            0x00000053,
            0xA76A660F,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guPerspectiveF",
        guPerspectiveF,
        {
            0x0000008C,
            0x9EC5FEAB,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guPerspective",
        guPerspective,
        {
            0x00000072,
            0x2B0214E7,
            0x00000016,
            0x99A85378,
            0x0000001B,
            0x8CC9B39E,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guScaleF",
        guScaleF,
        {
            0x00000015,
            0xCA91FB16,
            0x00000018,
            0x8497864D,
            0x00000020,
            0xBC8FF165,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guScale",
        guScale,
        {
            0x0000001F,
            0xA2C19EFB,
            0x00000012,
            0x3E48EAE5,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guRotateF",
        guRotateF,
        {
            0x00000065,
            0xD5CF8FAE,
            0x00000057,
            0xFA3518F4,
            0x00000093,
            0x9AA6B979,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guRotate",
        guRotate,
        {
            0x0000005E,
            0x06A7BCE6,
            0x00000014,
            0x698E4905,
            0x00000017,
            0x36AEAFA5,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guTranslateF",
        guTranslateF,
        {
            0x0000001B,
            0xC211F512,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guTranslate",
        guTranslate,
        {
            0x0000001C,
            0x80FA01A4,
            0x00000015,
            0x71F205A8,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guLookAtF",
        guLookAtF,
        {
            0x00000107,
            0xB11E3841,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guLookAt",
        guLookAt,
        {
            0x000000E1,
            0xE544558C,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guLookAtHiliteF",
        guLookAtHiliteF,
        {
            0x000002E9,
            0xCA0CCB5F,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guLookAtHilite",
        guLookAtHilite,
        {
            0x00000035,
            0xC2E98EC2,
            0x00000035,
            0x6B82DCD5,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guLookAtReflectF",
        guLookAtReflectF,
        {
            0x0000015E,
            0x55ACFC31,
            0x000001BF,
            0xBFD63279,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "guLookAtReflect",
        guLookAtReflect,
        {
            0x0000001B,
            0xD6F88212,
            0x00000023,
            0xD70B815D,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osAiSetFrequency",
        osAiSetFrequency,
        {
            0x00000046,
            0x88F8FC90,
            0x00000058,
            0xA177D03D,
            0x00000051,
            0xD3B85DEF,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osAiSetNextBuffer",
        osAiSetNextBuffer,
        {
            0x00000025,
            0x5ACF0804,
            0x0000002A,
            0x978F50F1,
            0x0000001D,
            0x47200DC9,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "__osEepStatus",
        __osEepStatus,
        {
            0x000000A8,
            0x8FBCE3BC,
            0x00000067,
            0x9870CAC4,
            0x00000089,
            0x807A196A,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osEepromRead",
        osEepromRead,
        {
            0x00000066,
            0x380B07CA,
            0x000000A5,
            0x947050BF,
            0x0000007C,
            0x66EC38E8,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osEepromWrite",
        osEepromWrite,
        {
            0x0000005A,
            0x5FCCA978,
            0x00000080,
            0xF6971795,
            0x0000006C,
            0x07B6DF06,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osEepromLongRead",
        osEepromLongRead,
        {
            0x0000001C,
            0x63BA7FE0,
            0x0000002E,
            0xF25B283A,
            0x0000004F,
            0x5B919EF9,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osEepromLongWrite",
        osEepromLongWrite,
        {
            0x00000039,
            0xED7A2E0B,
            0x00000044,
            0xF6B9E6BD,
            0x0000004F,
            0x5B919EF9,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "starfoxCopy",
        starfoxCopy,
        {
            0x00000026,
            0x158C0203,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "GenPerspective",
        GenPerspective_1080,
        {
            0x0000002F,
            0x3879CA27,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "pictureSnap_Zelda2",
        pictureSnap_Zelda2,
        {
            0x000001F0,
            0xC2739708,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "dmaSoundRomHandler_ZELDA1",
        dmaSoundRomHandler_ZELDA1,
        {
            0x0000001D,
            0x7C4D46F6,
            0x00000008,
            0x008D2AC3,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "osViSwapBuffer_Entry",
        osViSwapBuffer_Entry,
        {
            0x00000011,
            0x5147109A,
            0x00000038,
            0xBF405C09,
            0x00000014,
            0x745C58FD,
            0x00000013,
            0x6467CCEE,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "zeldaLoadSZS_Entry",
        zeldaLoadSZS_Entry,
        {
            0x0000005A,
            0x8EA707A2,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
    {
        "zeldaLoadSZS_Exit",
        zeldaLoadSZS_Exit,
        {
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
        },
    },
};

char D_800EFF34[] = "TestFunction: INTERNAL ERROR: osViSwapBuffer: No ADDIU opcode: 0x%08x";
char D_800EFF7C[] = "library.c";

void* jtbl_800EFF88[] = {
    &lbl_80097620, &lbl_800971AC, &lbl_80097208, &lbl_80097264, &lbl_80097488,
    &lbl_800974A0, &lbl_800974B4, &lbl_800974BC, &lbl_800974C4,
};

const f32 D_80136078 = 0.5;
const f32 D_8013607C = 48681812.0;
const f64 D_80136080 = 4503599627370496.0;
const f32 D_80136088 = 0.0;
const f64 D_80136090 = 0.5;
const f64 D_80136098 = 3.0;
const f32 D_801360A0 = -1.0;
const f32 D_801360A4 = 1.0;
const f32 D_801360A8 = 128.0;
const f32 D_801360AC = 127.0;
const f32 D_801360B0 = 65536.0;
const f64 D_801360B8 = 0.1;
const f32 D_801360C0 = 2.0;
const f64 D_801360C8 = 4503601774854144.0;
const f32 D_801360D0 = 0.01745329238474369;
const f32 D_801360D4 = -2.0;

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

#pragma GLOBAL_ASM("asm/non_matchings/library/guPerspectiveF.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/guPerspective.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/library/libraryFindException.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/libraryFindVariables.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/libraryFindFunctions.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/libraryTestFunction.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/librarySearch.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/libraryFunctionReplaced.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/libraryCall.s")

#pragma GLOBAL_ASM("asm/non_matchings/library/libraryEvent.s")
