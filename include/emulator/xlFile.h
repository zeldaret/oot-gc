#ifndef _XL_FILE_H
#define _XL_FILE_H

#include "dolphin.h"
#include "emulator/xlFileGCN.h"

#if IS_EU
typedef enum XlFileTokenType {
    XLFTT_NONE = -1,
    XLFTT_LABEL = 0,
    XLFTT_NUMBER = 1,
    XLFTT_STRING = 2,
    XLFTT_SYMBOL = 3,
    XLFTT_LAST_ = 4,
} XlFileTokenType;

bool xlFileGetSize(s32* pnSize, char* szFileName);

bool xlFileGetLine(tXL_FILE* pFile, char* acLine, s32 nSizeLine);
bool xlTokenGetInteger(char* acToken, u32* pnValue);
bool xlFileSkipLine(tXL_FILE* pFile);
bool xlFileGetToken(tXL_FILE* pFile, XlFileTokenType* peType, char* acToken, s32 nSizeToken);
bool xlFileMatchToken(tXL_FILE* pFile, XlFileTokenType eType, char* acToken, s32 nSizeToken, char* szText);
bool xlFileGetLineSave(tXL_FILE* pFile, tXL_SAVE* pSave);
#endif

#endif
