#ifndef _FRAME_H
#define _FRAME_H

#include "dolphin.h"
#include "emulator/rdp.h"
#include "emulator/rsp.h"
#include "emulator/xlObject.h"

#define FRAME_SYNC_TOKEN 0x7D00

// N64 frame buffer dimensions
#define N64_FRAME_WIDTH 320
#define N64_FRAME_HEIGHT 240

// GC is rendered at double the resolution
#define GC_FRAME_WIDTH (N64_FRAME_WIDTH * 2)
#define GC_FRAME_HEIGHT (N64_FRAME_HEIGHT * 2)

// Dimensions of the player preview on the equipment menu of the Zelda pause screen
#define ZELDA_PAUSE_EQUIP_PLAYER_WIDTH 64
#define ZELDA_PAUSE_EQUIP_PLAYER_HEIGHT 112

#define ZELDA2_CAMERA_WIDTH 160
#define ZELDA2_CAMERA_HEIGHT 128

typedef bool (*FrameDrawFunc)(void*, void*);

// __anon_0x27B8C
typedef enum FrameMatrixType {
    FMT_MODELVIEW = 0,
    FMT_PROJECTION = 1,
} FrameMatrixType;

// __anon_0x27E96
typedef enum FrameModeType {
    FMT_NONE = -1,
    FMT_FOG = 0,
    FMT_GEOMETRY = 1,
    FMT_TEXTURE1 = 2,
    FMT_TEXTURE2 = 3,
    FMT_OTHER0 = 4,
    FMT_OTHER1 = 5,
    FMT_COMBINE_COLOR1 = 6,
    FMT_COMBINE_COLOR2 = 7,
    FMT_COMBINE_ALPHA1 = 8,
    FMT_COMBINE_ALPHA2 = 9,
    FMT_COUNT = 10,
} FrameModeType;

// __anon_0x2813A
typedef enum FrameSize {
    FS_NONE = -1,
    FS_SOURCE = 0,
    FS_TARGET = 1,
    FS_COUNT = 2,
} FrameSize;

// __anon_0x2614E
typedef enum FrameBufferType {
    FBT_NONE = -1,
    FBT_DEPTH = 0,
    FBT_IMAGE = 1,
    FBT_COLOR_SHOW = 2,
    FBT_COLOR_DRAW = 3,
    FBT_COUNT = 4,
} FrameBufferType;

// __anon_0x2625D
typedef enum FrameResetType {
    FRT_NONE = -1,
    FRT_COLD = 0,
    FRT_WARM = 1,
} FrameResetType;

// __anon_0x26C3F
typedef enum FrameLoadType {
    FLT_NONE = -1,
    FLT_TILE = 0,
    FLT_BLOCK = 1,
} FrameLoadType;

// __anon_0x25D5E
typedef enum FrameMatrixProjection {
    FMP_NONE = -1,
    FMP_PERSPECTIVE = 0,
    FMP_ORTHOGRAPHIC = 1,
} FrameMatrixProjection;

// __anon_0x2D223
typedef enum FrameColorType {
    FCT_NONE = -1,
    FCT_FOG,
    FCT_FILL,
    FCT_BLEND,
    FCT_PRIMITIVE,
    FCT_ENVIRONMENT,
    FCT_COUNT
} FrameColorType;

// __anon_0x2D45B
typedef struct Primitive {
    /* 0x0 */ s32 nCount;
    /* 0x4 */ u8 anData[768];
} Primitive; // size = 0x304

// __anon_0x23B04
typedef struct Viewport {
    /* 0x0 */ f32 rX;
    /* 0x4 */ f32 rY;
    /* 0x8 */ f32 rSizeX;
    /* 0xC */ f32 rSizeY;
} Viewport; // size = 0x10

// __anon_0x23B9E
typedef struct FrameBuffer {
    /* 0x00 */ s32 nSize;
    /* 0x04 */ s32 nWidth;
    /* 0x08 */ s32 nFormat;
    /* 0x0C */ void* pData;
    /* 0x10 */ s32 nAddress;
} FrameBuffer; // size = 0x14

// __anon_0x274AD
typedef struct Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec3f; // size = 0xC

// __anon_0x23CAB
typedef struct Light {
    /* 0x00 */ bool bTransformed;
    /* 0x04 */ Vec3f rVecOrigTowards;
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
} Light; // size = 0x3C

// __anon_0x23EDB
typedef struct LookAt {
    /* 0x00 */ bool bTransformed;
    /* 0x04 */ Vec3f rS;
    /* 0x10 */ Vec3f rT;
    /* 0x1C */ Vec3f rSRaw;
    /* 0x28 */ Vec3f rTRaw;
} LookAt; // size = 0x34

// __anon_0x23FC4
typedef struct Vertex {
    /* 0x00 */ f32 rSum;
    /* 0x04 */ f32 rS;
    /* 0x08 */ f32 rT;
    /* 0x0C */ Vec3f vec;
    /* 0x18 */ u8 anColor[4];
} Vertex; // size = 0x1C

// __anon_0x24123
typedef union TMEM_Block {
    /* 0x0 */ u8 u8[4096];
    /* 0x0 */ u16 u16[2048];
    /* 0x0 */ u32 u32[1024];
    /* 0x0 */ u64 u64[512];
} TMEM_Block;

// __anon_0x241C0
typedef struct TextureMemory {
    /* 0x0 */ TMEM_Block data;
} TextureMemory; // size = 0x1000

// __anon_0x25A82
typedef struct TextureInfo {
    /* 0x0 */ s32 nSizeTextures;
    /* 0x4 */ s32 nCountTextures;
} TextureInfo; // size = 0x8

// _FRAME_TEXTURE
// __anon_0x24462
typedef struct FrameTexture FrameTexture;

struct FrameTexture {
    /* 0x00 */ s32 nMode;
    /* 0x04 */ s32 iPackPixel;
    /* 0x08 */ s32 iPackColor;
    /* 0x0C */ s32 nFrameLast;
    /* 0x10 */ s16 nSizeX;
    /* 0x12 */ s16 nSizeY;
    /* 0x14 */ u32 nAddress;
    /* 0x18 */ u32 nCodePixel;
    /* 0x1C */ u32 nCodeColor;
    /* 0x20 */ FrameTexture* pTextureNext;
    /* 0x24 */ u32 nData0;
    /* 0x28 */ u32 nData1;
    /* 0x2C */ u32 nData2;
    /* 0x30 */ u32 nData3;
    /* 0x34 */ GXTexFmt eFormat;
    /* 0x38 */ GXTlutObj objectTLUT;
    /* 0x44 */ GXTexObj objectTexture;
    /* 0x64 */ GXTexWrapMode eWrapS;
    /* 0x68 */ GXTexWrapMode eWrapT;
}; // size = 0x6C

// __anon_0x247BF
typedef struct Tile {
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
} Tile; // size = 0x2C

// __anon_0x24A81
typedef struct MatrixHint {
    /* 0x00 */ s32 nCount;
    /* 0x04 */ f32 rScale;
    /* 0x08 */ f32 rAspect;
    /* 0x0C */ f32 rFieldOfViewY;
    /* 0x10 */ f32 rClipNear;
    /* 0x14 */ f32 rClipFar;
    /* 0x18 */ u32 nAddressFloat;
    /* 0x1C */ u32 nAddressFixed;
    /* 0x20 */ FrameMatrixProjection eProjection;
} MatrixHint; // size = 0x24

typedef struct Rectangle {
    /* 0x00 */ bool bFlip;
    /* 0x04 */ s32 iTile;
    /* 0x08 */ s32 nX0;
    /* 0x0C */ s32 nY0;
    /* 0x10 */ s32 nX1;
    /* 0x14 */ s32 nY1;
    /* 0x18 */ f32 rS;
    /* 0x1C */ f32 rT;
    /* 0x20 */ f32 rDeltaS;
    /* 0x24 */ f32 rDeltaT;
} Rectangle; // size = 0x28

// __anon_0x24C38
typedef struct Frame {
    /* 0x00000 */ u32 anCIMGAddresses[8];
    /* 0x00020 */ u16 nNumCIMGAddresses;
    /* 0x00024 */ bool bBlurOn;
    /* 0x00028 */ bool bHackPause;
    /* 0x0002C */ s32 nHackCount;
    /* 0x00030 */ s32 nFrameCounter;
    /* 0x00034 */ bool bPauseThisFrame;
    /* 0x00038 */ bool bCameFromBomberNotes;
    /* 0x0003C */ bool bInBomberNotes;
    /* 0x00040 */ s32 bShrinking; // bitfield (not a bool)
    /* 0x00044 */ bool bSnapShot;
    /* 0x00048 */ bool bUsingLens;
    /* 0x0004C */ u8 cBlurAlpha;
    /* 0x00050 */ bool bBlurredThisFrame;
    /* 0x00054 */ s32 nFrameCIMGCalls;
    /* 0x00058 */ bool bModifyZBuffer;
    /* 0x0005C */ bool bOverrideDepth;
    /* 0x00060 */ s32 nZBufferSets;
    /* 0x00064 */ s32 nLastFrameZSets;
    /* 0x00068 */ bool bPauseBGDrawn;
    /* 0x0006C */ bool bFrameOn;
    /* 0x00070 */ bool bBackBufferDrawn;
    /* 0x00074 */ bool bGrabbedFrame;
    /* 0x00078 */ u64* pnGBI;
    /* 0x0007C */ u32 nFlag;
    /* 0x00080 */ f32 rScaleX;
    /* 0x00084 */ f32 rScaleY;
    /* 0x00088 */ u32 nCountFrames;
    /* 0x0008C */ u32 nMode;
    /* 0x00090 */ u32 aMode[FMT_COUNT];
    /* 0x000B8 */ Viewport viewport;
    /* 0x000C8 */ FrameBuffer aBuffer[FBT_COUNT];
    /* 0x00118 */ u32 nOffsetDepth0;
    /* 0x0011C */ u32 nOffsetDepth1;
    /* 0x00120 */ s32 nWidthLine;
    /* 0x00124 */ f32 rDepth;
    /* 0x00128 */ f32 rDelta;
    /* 0x0012C */ FrameDrawFunc aDraw[4];
    /* 0x0013C */ s32 nCountLight;
    /* 0x00140 */ Light aLight[8];
    /* 0x00320 */ LookAt lookAt;
    /* 0x00354 */ s32 nCountVertex;
    /* 0x00358 */ Vertex aVertex[80];
    /* 0x00C18 */ TextureMemory TMEM;
    /* 0x01C18 */ void* aPixelData;
    /* 0x01C1C */ void* aColorData;
    /* 0x01C20 */ s32 nBlocksPixel;
    /* 0x01C24 */ s32 nBlocksMaxPixel;
    /* 0x01C28 */ s32 nBlocksColor;
    /* 0x01C2C */ s32 nBlocksMaxColor;
    /* 0x01C30 */ s32 nBlocksTexture;
    /* 0x01C34 */ s32 nBlocksMaxTexture;
    /* 0x01C38 */ u32 anPackPixel[48];
    /* 0x01CF8 */ u32 anPackColor[N64_FRAME_WIDTH];
    /* 0x021F8 */ u32 nAddressLoad;
    /* 0x021FC */ u32 nCodePixel;
    /* 0x02200 */ u32 nTlutCode[16];
    /* 0x02240 */ FrameTexture aTexture[2048];
    /* 0x38240 */ u32 anTextureUsed[64];
    /* 0x38340 */ FrameTexture* apTextureCached[4096];
    /* 0x3C340 */ s32 iTileLoad;
    /* 0x3C344 */ u32 n2dLoadTexType;
    /* 0x3C348 */ s32 nLastX0;
    /* 0x3C34C */ s32 nLastY0;
    /* 0x3C350 */ s32 nLastX1;
    /* 0x3C354 */ s32 nLastY1;
    /* 0x3C358 */ Tile aTile[8];
    /* 0x3C4B8 */ s32 anSizeX[2];
    /* 0x3C4C0 */ s32 anSizeY[2];
    /* 0x3C4C8 */ s32 iHintMatrix;
    /* 0x3C4CC */ s32 iMatrixModel;
    /* 0x3C4D0 */ s32 iHintProjection;
    /* 0x3C4D4 */ Mtx44 matrixView;
    /* 0x3C514 */ s32 iHintLast;
    /* 0x3C518 */ s32 iHintHack;
    /* 0x3C51C */ FrameMatrixProjection eTypeProjection;
    /* 0x3C520 */ Mtx44 aMatrixModel[10];
    /* 0x3C7A0 */ Mtx44 matrixProjection;
    /* 0x3C7E0 */ Mtx44 matrixProjectionExtra;
    /* 0x3C820 */ MatrixHint aMatrixHint[64];
    /* 0x3D120 */ u8 primLODmin;
    /* 0x3D121 */ u8 primLODfrac;
    /* 0x3D122 */ u8 lastTile;
    /* 0x3D123 */ u8 iTileDrawn;
    /* 0x3D124 */ GXColor aColor[5];
    /* 0x3D138 */ u32 nModeVtx;
    /* 0x3D13C */ u16* nTempBuffer;
    /* 0x3D140 */ u16* nCopyBuffer;
    /* 0x3D144 */ u32* nLensBuffer;
    /* 0x3D148 */ u16* nCameraBuffer;
} Frame; // size = 0x3D150

extern _XL_OBJECTTYPE gClassFrame;
extern bool gNoSwapBuffer;

bool frameDrawSetup2D(Frame* pFrame);
bool _frameDrawRectangle(Frame* pFrame, u32 nColor, s32 nX, s32 nY, s32 nSizeX, s32 nSizeY);
bool frameEvent(Frame* pFrame, s32 nEvent, void* pArgument);

void ZeldaDrawFrameNoBlend(Frame* pFrame, u16* pData);
void ZeldaDrawFrame(Frame* pFrame, u16* pData);
bool frameHackTIMG_Zelda(Frame* pFrame, u64** pnGBI, u32* pnCommandLo, u32* pnCommandHi);
bool frameHackCIMG_Zelda2(Frame* pFrame, FrameBuffer* pBuffer, u64* pnGBI, u32 nCommandLo, u32 nCommandHi);
bool frameHackCIMG_Zelda(Frame* pFrame, FrameBuffer* pBuffer, u64* pnGBI, u32 nCommandLo, u32 nCommandHi);
bool frameHackCIMG_Zelda2_Shrink(Rdp* pRDP, Frame* pFrame, u64** ppnGBI);
bool frameHackCIMG_Zelda2_Camera(Frame* pFrame, FrameBuffer* pBuffer, u32 nCommandHi, u32 nCommandLo);
bool frameHackTIMG_Panel(Frame* pFrame, FrameBuffer* pBuffer);
bool frameHackCIMG_Panel(Rdp* pRDP, Frame* pFrame, FrameBuffer* pBuffer, u64** ppnGBI);

bool frameGetDepth(Frame* pFrame, u16* pnData, s32 nAddress);
bool frameShow(Frame* pFrame);
bool frameSetScissor(Frame* pFrame, Rectangle* pScissor);
bool frameSetDepth(Frame* pFrame, f32 rDepth, f32 rDelta);
bool frameSetColor(Frame* pFrame, FrameColorType eType, u32 nRGBA);

bool frameBeginOK(Frame* pFrame);
bool frameBegin(Frame* pFrame, s32 nCountVertex);
bool frameEnd(Frame* pFrame);
bool frameDrawReset(Frame* pFrame, s32 nFlag);

bool frameSetFill(Frame* pFrame, bool bFill);
bool frameSetSize(Frame* pFrame, FrameSize eSize, s32 nSizeX, s32 nSizeY);
bool frameSetMode(Frame* pFrame, FrameModeType eType, u32 nMode);
bool frameGetMode(Frame* pFrame, FrameModeType eType, u32* pnMode);
bool frameSetMatrix(Frame* pFrame, Mtx44 matrix, FrameMatrixType eType, bool bLoad, bool bPush, s32 nAddressN64);
bool frameGetMatrix(Frame* pFrame, Mtx44 matrix, FrameMatrixType eType, bool bPull);
bool frameLoadVertex(Frame* pFrame, void* pBuffer, s32 iVertex0, s32 nCount);
bool frameCullDL(Frame* pFrame, s32 nVertexStart, s32 nVertexEnd);
bool frameLoadTLUT(Frame* pFrame, s32 nCount, s32 iTile);
bool frameLoadTMEM(Frame* pFrame, FrameLoadType eType, s32 iTile);
bool frameSetLightCount(Frame* pFrame, s32 nCount);
bool frameSetLight(Frame* pFrame, s32 iLight, s8* pData);
bool frameSetLookAt(Frame* pFrame, s32 iLookAt, s8* pData);
bool frameSetViewport(Frame* pFrame, s16* pData);
bool frameResetUCode(Frame* pFrame, RspUCodeType eType);
bool frameSetBuffer(Frame* pFrame, FrameBufferType eType);
bool frameFixMatrixHint(Frame* pFrame, s32 nAddressFloat, s32 nAddressFixed);
bool frameSetMatrixHint(Frame* pFrame, FrameMatrixProjection eProjection, s32 nAddressFloat, s32 nAddressFixed,
                        f32 rNear, f32 rFar, f32 rFOVY, f32 rAspect, f32 rScale);
bool frameInvalidateCache(Frame* pFrame, s32 nOffset0, s32 nOffset1);

void SetNumTexGensChans(Frame* pFrame, s32 numCycles);
void SetTevStages(Frame* pFrame, s32 cycle);
bool SetTevStageTable(Frame* pFrame, s32 numCycles);

extern GXTexMapID ganNamePixel[];
extern GXTexCoordID ganNameTexCoord[];

#endif
