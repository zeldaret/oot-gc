#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

/*
 * Local symbols included but should not be uncommented when types are discovered
 */

#include <dolphin.h>
#include <unk.h>

// ======================= xlCoreGCN.c ================================================
/* 800055A0 global */ extern UNK_TYPE xlCoreBeforeRender(UNK_TYPE...);
/* 80005674 global */ extern UNK_TYPE main(UNK_TYPE...);
/* 800058DC global */ extern UNK_TYPE xlCoreHiResolution(UNK_TYPE...);
/* 800058E4 global */ extern UNK_TYPE xlCoreGetArgument(UNK_TYPE...);
/* 80005918 global */ extern UNK_TYPE xlCoreGetArgumentCount(UNK_TYPE...);
/* 80005920 local  */ // extern UNK_TYPE xlCoreInitGX(UNK_TYPE...);
/* 80005B7C local  */ // extern UNK_TYPE xlCoreInitMem(UNK_TYPE...);
/* 80005C54 local  */ // extern UNK_TYPE xlCoreInitRenderMode(UNK_TYPE...);
/* 80005DC8 global */ extern UNK_TYPE xlCoreReset(UNK_TYPE...);
// ======================= xlPostGCN.c ================================================
/* 80005E04 global */ extern UNK_TYPE xlPostReset(UNK_TYPE...);
/* 80005E0C global */ extern UNK_TYPE xlPostSetup(UNK_TYPE...);
/* 80005E14 global */ extern UNK_TYPE xlPostText(UNK_TYPE...);
// ======================= xlFileGCN.c ================================================
/* 80005E68 global */ extern UNK_TYPE xlFileEvent(UNK_TYPE...);
/* 80005F18 global */ extern UNK_TYPE xlFileSetPosition(UNK_TYPE...);
/* 80005F40 global */ extern UNK_TYPE xlFileGet(UNK_TYPE...);
/* 80006044 global */ extern UNK_TYPE xlFileClose(UNK_TYPE...);
/* 80006078 global */ extern UNK_TYPE xlFileOpen(UNK_TYPE...);
/* 8000614C global */ extern UNK_TYPE xlFileGetSize(UNK_TYPE...);
/* 80006268 global */ extern UNK_TYPE xlFileSetRead(UNK_TYPE...);
/* 80006274 global */ extern UNK_TYPE xlFileSetOpen(UNK_TYPE...);
// ======================= xlList.c ===================================================
/* 80006280 global */ extern UNK_TYPE xlListReset(UNK_TYPE...);
/* 80006288 global */ extern UNK_TYPE xlListSetup(UNK_TYPE...);
/* 800062B0 global */ extern UNK_TYPE xlListTestItem(UNK_TYPE...);
/* 8000633C global */ extern UNK_TYPE xlListFreeItem(UNK_TYPE...);
/* 800063E8 global */ extern UNK_TYPE xlListMakeItem(UNK_TYPE...);
/* 80006494 global */ extern UNK_TYPE xlListFree(UNK_TYPE...);
/* 80006550 global */ extern UNK_TYPE xlListMake(UNK_TYPE...);
// ======================= xlHeap.c ===================================================
/* 80006648 global */ extern UNK_TYPE xlHeapReset(UNK_TYPE...);
/* 800066B0 global */ extern UNK_TYPE xlHeapSetup(UNK_TYPE...);
/* 80006870 global */ extern UNK_TYPE xlHeapGetFree(UNK_TYPE...);
/* 80006908 global */ extern UNK_TYPE xlHeapFill32(UNK_TYPE...);
/* 80006AF0 global */ extern UNK_TYPE xlHeapCopy(UNK_TYPE...);
/* 80006F68 global */ extern UNK_TYPE xlHeapCompact(UNK_TYPE...);
/* 80007098 global */ extern UNK_TYPE xlHeapFree(UNK_TYPE...);
/* 800071B4 global */ extern UNK_TYPE xlHeapTake(UNK_TYPE...);
/* 8000743C local  */ // extern UNK_TYPE xlHeapFindUpperBlock(UNK_TYPE...);
/* 80007540 local  */ // extern UNK_TYPE xlHeapBlockCacheReset(UNK_TYPE...);
/* 8000764C local  */ // extern UNK_TYPE xlHeapBlockCacheClear(UNK_TYPE...);
/* 80007758 local  */ // extern UNK_TYPE xlHeapBlockCacheAdd(UNK_TYPE...);
/* 800079C0 local  */ // extern UNK_TYPE xlHeapBlockCacheGet(UNK_TYPE...);
                      // ======================= xlObject.c =================================================
/* 80007BC0 global */ extern UNK_TYPE xlObjectReset(UNK_TYPE...);
/* 80007C30 global */ extern UNK_TYPE xlObjectSetup(UNK_TYPE...);
/* 80007C6C global */ extern UNK_TYPE xlObjectEvent(UNK_TYPE...);
/* 80007D24 global */ extern UNK_TYPE xlObjectTest(UNK_TYPE...);
/* 80007D8C global */ extern UNK_TYPE xlObjectFree(UNK_TYPE...);
/* 80007E24 global */ extern UNK_TYPE xlObjectMake(UNK_TYPE...);
// ======================= simGCN.c ===================================================
/* 80007F80 global */ extern UNK_TYPE xlMain(UNK_TYPE...);
/* 80008538 global */ extern UNK_TYPE simulatorGetArgument(UNK_TYPE...);
/* 80008578 local  */ // extern UNK_TYPE simulatorParseArguments(UNK_TYPE...);
/* 800086DC local  */ // extern UNK_TYPE simulatorDrawCursor(UNK_TYPE...);
/* 800088E4 global */ extern UNK_TYPE simulatorMCardPollDrawFormatBar(UNK_TYPE...);
/* 80008A14 global */ extern UNK_TYPE simulatorMCardPollDrawBar(UNK_TYPE...);
/* 80008B44 global */ extern UNK_TYPE simulatorDrawMCardText(UNK_TYPE...);
/* 80008BDC global */ extern UNK_TYPE simulatorTestReset(UNK_TYPE...);
/* 80008DBC global */ extern UNK_TYPE simulatorRumbleStop(UNK_TYPE...);
/* 80008DE4 global */ extern UNK_TYPE simulatorRumbleStart(UNK_TYPE...);
/* 80008E0C global */ extern UNK_TYPE simulatorWriteFLASH(UNK_TYPE...);
/* 80008E40 global */ extern UNK_TYPE simulatorReadFLASH(UNK_TYPE...);
/* 80008E74 global */ extern UNK_TYPE simulatorWriteSRAM(UNK_TYPE...);
/* 80008EA8 global */ extern UNK_TYPE simulatorReadSRAM(UNK_TYPE...);
/* 80008EDC global */ extern UNK_TYPE simulatorWriteEEPROM(UNK_TYPE...);
/* 80008F4C global */ extern UNK_TYPE simulatorReadEEPROM(UNK_TYPE...);
/* 80008FBC global */ extern UNK_TYPE simulatorWritePak(UNK_TYPE...);
/* 80009038 global */ extern UNK_TYPE simulatorReadPak(UNK_TYPE...);
/* 800090B4 global */ extern UNK_TYPE simulatorDetectController(UNK_TYPE...);
/* 80009108 global */ extern UNK_TYPE simulatorShowLoad(UNK_TYPE...);
/* 80009110 global */ extern UNK_TYPE simulatorReadController(UNK_TYPE...);
/* 80009684 global */ extern UNK_TYPE simulatorCopyControllerMap(UNK_TYPE...);
/* 8000974C global */ extern UNK_TYPE simulatorSetControllerMap(UNK_TYPE...);
/* 80009824 global */ extern UNK_TYPE simulatorResetAndPlayMovie(UNK_TYPE...);
/* 80009980 global */ extern UNK_TYPE simulatorReset(UNK_TYPE...);
/* 80009A30 global */ extern UNK_TYPE simulatorDrawErrorMessageWait(UNK_TYPE...);
/* 8000CB7C global */ extern UNK_TYPE simulatorDrawYesNoMessage(UNK_TYPE...);
/* 8000CF24 global */ extern UNK_TYPE simulatorDrawYesNoMessageLoop(UNK_TYPE...);
/* 8000D1F0 global */ extern UNK_TYPE simulatorPrepareMessage(UNK_TYPE...);
/* 8000D35C global */ extern UNK_TYPE simulatorDrawErrorMessage(UNK_TYPE...);
/* 8000D58C global */ extern UNK_TYPE simulatorDrawOKImage(UNK_TYPE...);
/* 8000DBB4 global */ extern UNK_TYPE simulatorDrawYesNoImage(UNK_TYPE...);
/* 8000E484 global */ extern UNK_TYPE simulatorDrawImage(UNK_TYPE...);
/* 8000ECA0 global */ extern UNK_TYPE simulatorPlayMovie(UNK_TYPE...);
/* 8000ECC4 global */ extern UNK_TYPE simulatorDVDRead(UNK_TYPE...);
/* 8000EDA8 global */ extern UNK_TYPE simulatorDVDOpen(UNK_TYPE...);
/* 8000EE18 global */ extern UNK_TYPE simulatorDVDShowError(UNK_TYPE...);
/* 8000F020 global */ extern UNK_TYPE simulatorUnpackTexPalette(UNK_TYPE...);
/* 8000F0FC global */ extern UNK_TYPE simulatorGXInit(UNK_TYPE...);
// ======================= movie.c ====================================================
/* 8000F7CC global */ extern UNK_TYPE MovieDraw(UNK_TYPE...);
/* 8000F804 global */ extern UNK_TYPE MovieInit(UNK_TYPE...);
// ======================= THPPlayer.c ================================================
/* 8000F890 global */ extern UNK_TYPE THPPlayerInit(UNK_TYPE...);
/* 8000F9C8 global */ extern UNK_TYPE THPPlayerOpen(UNK_TYPE...);
/* 8000FC40 global */ extern UNK_TYPE THPPlayerCalcNeedMemory(UNK_TYPE...);
/* 8000FCE8 global */ extern UNK_TYPE THPPlayerSetBuffer(UNK_TYPE...);
/* 8000FF24 local  */ // extern UNK_TYPE InitAllMessageQueue(UNK_TYPE...);
/* 8000FFF0 global */ extern UNK_TYPE PrepareReady(UNK_TYPE...);
/* 80010020 global */ extern UNK_TYPE THPPlayerPrepare(UNK_TYPE...);
/* 80010294 global */ extern UNK_TYPE THPPlayerPlay(UNK_TYPE...);
/* 800102F0 local  */ // extern UNK_TYPE PlayControl(UNK_TYPE...);
/* 8001058C local  */ // extern UNK_TYPE ProperTimingForStart(UNK_TYPE...);
/* 800105F8 local  */ // extern UNK_TYPE ProperTimingForGettingNextFrame(UNK_TYPE...);
/* 8001071C global */ extern UNK_TYPE THPPlayerDrawCurrentFrame(UNK_TYPE...);
/* 800107E8 local  */ // extern UNK_TYPE PushUsedTextureSet(UNK_TYPE...);
/* 80010818 global */ extern UNK_TYPE THPPlayerDrawDone(UNK_TYPE...);
/* 80010888 local  */ // extern UNK_TYPE THPAudioMixCallback(UNK_TYPE...);
/* 80010A00 local  */ // extern UNK_TYPE MixAudio(UNK_TYPE...);
// ======================= THPAudioDecode.c ===========================================
/* 80010D9C global */ extern UNK_TYPE CreateAudioDecodeThread(UNK_TYPE...);
/* 80010E7C global */ extern UNK_TYPE AudioDecodeThreadStart(UNK_TYPE...);
/* 80010EB0 local  */ // extern UNK_TYPE AudioDecoder(UNK_TYPE...);
/* 80010ED8 local  */ // extern UNK_TYPE AudioDecoderForOnMemory(UNK_TYPE...);
/* 80010F88 local  */ // extern UNK_TYPE AudioDecode(UNK_TYPE...);
/* 80011060 global */ extern UNK_TYPE PopFreeAudioBuffer(UNK_TYPE...);
/* 80011094 global */ extern UNK_TYPE PushFreeAudioBuffer(UNK_TYPE...);
/* 800110C4 global */ extern UNK_TYPE PopDecodedAudioBuffer(UNK_TYPE...);
/* 80011108 global */ extern UNK_TYPE PushDecodedAudioBuffer(UNK_TYPE...);
// ======================= THPDraw.c ==================================================
/* 80011138 global */ extern UNK_TYPE THPGXRestore(UNK_TYPE...);
/* 80011250 global */ extern UNK_TYPE THPGXYuv2RgbSetup(UNK_TYPE...);
/* 80011754 global */ extern UNK_TYPE THPGXYuv2RgbDraw(UNK_TYPE...);
// ======================= THPRead.c ==================================================
/* 80011938 global */ extern UNK_TYPE PushReadedBuffer2(UNK_TYPE...);
/* 80011968 global */ extern UNK_TYPE PopReadedBuffer2(UNK_TYPE...);
/* 8001199C global */ extern UNK_TYPE PushFreeReadBuffer(UNK_TYPE...);
/* 800119CC global */ extern UNK_TYPE PopReadedBuffer(UNK_TYPE...);
/* 80011A00 local  */ // extern UNK_TYPE Reader(UNK_TYPE...);
/* 80011B2C global */ extern UNK_TYPE ReadThreadStart(UNK_TYPE...);
/* 80011B60 global */ extern UNK_TYPE CreateReadThread(UNK_TYPE...);
/* 80011C0C global */ extern UNK_TYPE movieReset(UNK_TYPE...);
/* 80011CAC global */ extern UNK_TYPE movieTestReset(UNK_TYPE...);
/* 80011E60 global */ extern UNK_TYPE movieDVDRead(UNK_TYPE...);
/* 80011F10 global */ extern UNK_TYPE movieDVDShowError(UNK_TYPE...);
/* 80012170 global */ extern UNK_TYPE movieDrawErrorMessage(UNK_TYPE...);
/* 80012334 global */ extern UNK_TYPE movieDrawImage(UNK_TYPE...);
/* 80012850 global */ extern UNK_TYPE movieGXInit(UNK_TYPE...);
// ======================= THPVideoDecode.c ===========================================
/* 80012F20 global */ extern UNK_TYPE CreateVideoDecodeThread(UNK_TYPE...);
/* 80013004 global */ extern UNK_TYPE VideoDecodeThreadStart(UNK_TYPE...);
/* 80013038 local  */ // extern UNK_TYPE VideoDecoder(UNK_TYPE...);
/* 80013114 local  */ // extern UNK_TYPE VideoDecoderForOnMemory(UNK_TYPE...);
/* 80013248 local  */ // extern UNK_TYPE VideoDecode(UNK_TYPE...);
/* 80013368 global */ extern UNK_TYPE PopFreeTextureSet(UNK_TYPE...);
/* 8001339C global */ extern UNK_TYPE PushFreeTextureSet(UNK_TYPE...);
/* 800133CC global */ extern UNK_TYPE PopDecodedTextureSet(UNK_TYPE...);
/* 80013410 global */ extern UNK_TYPE PushDecodedTextureSet(UNK_TYPE...);
// ======================= mcardGCN.c =================================================
/* 80013440 global */ extern UNK_TYPE mcardUpdate(UNK_TYPE...);
/* 800136F4 global */ extern UNK_TYPE mcardStore(UNK_TYPE...);
/* 800145FC global */ extern UNK_TYPE mcardOpenDuringGame(UNK_TYPE...);
/* 8001514C global */ extern UNK_TYPE mcardOpen(UNK_TYPE...);
/* 80016950 global */ extern UNK_TYPE mcardWrite(UNK_TYPE...);
/* 80016CB0 global */ extern UNK_TYPE mcardOpenDuringGameError(UNK_TYPE...);
/* 80016D90 global */ extern UNK_TYPE mcardOpenError(UNK_TYPE...);
/* 80016E70 global */ extern UNK_TYPE mcardMenu(UNK_TYPE...);
/* 80017814 global */ extern UNK_TYPE mcardRead(UNK_TYPE...);
/* 80017844 global */ extern UNK_TYPE mcardGameRelease(UNK_TYPE...);
/* 800178EC global */ extern UNK_TYPE mcardGameErase(UNK_TYPE...);
/* 80017A94 global */ extern UNK_TYPE mcardFileErase(UNK_TYPE...);
/* 80017C24 global */ extern UNK_TYPE mcardCardErase(UNK_TYPE...);
/* 80017D60 global */ extern UNK_TYPE mcardGameCreate(UNK_TYPE...);
/* 800185F8 global */ extern UNK_TYPE mcardFileCreate(UNK_TYPE...);
/* 80018C50 global */ extern UNK_TYPE mcardGameSet(UNK_TYPE...);
/* 80019058 global */ extern UNK_TYPE mcardFileSet(UNK_TYPE...);
/* 8001947C global */ extern UNK_TYPE mcardInit(UNK_TYPE...);
/* 800194D8 global */ extern UNK_TYPE mcardReInit(UNK_TYPE...);
/* 80019670 global */ extern UNK_TYPE mcardWriteGameDataReset(UNK_TYPE...);
/* 800196D8 global */ extern UNK_TYPE mcardReadGameData(UNK_TYPE...);
/* 80019A70 local  */ // extern UNK_TYPE mcardWriteTimeAsynch(UNK_TYPE...);
/* 80019C74 local  */ // extern UNK_TYPE mcardWriteConfigAsynch(UNK_TYPE...);
/* 80019E38 local  */ // extern UNK_TYPE mcardReadBufferAsynch(UNK_TYPE...);
/* 80019FDC local  */ // extern UNK_TYPE mcardWriteBufferAsynch(UNK_TYPE...);
/* 8001A1C0 local  */ // extern UNK_TYPE mcardWriteFileHeaderInitial(UNK_TYPE...);
/* 8001A3E4 local  */ // extern UNK_TYPE mcardReadFileHeaderInitial(UNK_TYPE...);
/* 8001A53C local  */ // extern UNK_TYPE mcardWriteFileHeader(UNK_TYPE...);
/* 8001A8F8 local  */ // extern UNK_TYPE mcardReadFileHeader(UNK_TYPE...);
/* 8001AB1C local  */ // extern UNK_TYPE mcardWriteAnywherePartial(UNK_TYPE...);
/* 8001ACC8 local  */ // extern UNK_TYPE mcardWriteAnywhere(UNK_TYPE...);
/* 8001AE64 local  */ // extern UNK_TYPE mcardReadAnywhere(UNK_TYPE...);
/* 8001AFD4 local  */ // extern UNK_TYPE mcardReadyCard(UNK_TYPE...);
/* 8001B168 local  */ // extern UNK_TYPE mcardPoll(UNK_TYPE...);
/* 8001B254 local  */ // extern UNK_TYPE mcardVerifyChecksumFileHeader(UNK_TYPE...);
/* 8001B480 local  */ // extern UNK_TYPE mcardCheckChecksumFileHeader(UNK_TYPE...);
/* 8001B794 local  */ // extern UNK_TYPE mcardReplaceFileBlock(UNK_TYPE...);
/* 8001BC14 local  */ // extern UNK_TYPE mcardSaveChecksumFileHeader(UNK_TYPE...);
/* 8001BF70 local  */ // extern UNK_TYPE mcardCalculateChecksumFileBlock2(UNK_TYPE...);
/* 8001C0D8 local  */ // extern UNK_TYPE mcardCalculateChecksumFileBlock1(UNK_TYPE...);
/* 8001C240 local  */ // extern UNK_TYPE mcardCalculateChecksum(UNK_TYPE...);
/* 8001C2A0 local  */ // extern UNK_TYPE mcardGCErrorHandler(UNK_TYPE...);
// ======================= codeGCN.c ==================================================
/* 8001C444 global */ extern UNK_TYPE codeEvent(UNK_TYPE...);
// ======================= soundGCN.c =================================================
/* 8001C498 global */ extern UNK_TYPE soundEvent(UNK_TYPE...);
/* 8001C690 global */ extern UNK_TYPE soundPlayBeep(UNK_TYPE...);
/* 8001C70C global */ extern UNK_TYPE soundLoadBeep(UNK_TYPE...);
/* 8001C824 local  */ // extern UNK_TYPE soundCallbackBeep(UNK_TYPE...);
/* 8001C880 global */ extern UNK_TYPE soundSetBufferSize(UNK_TYPE...);
/* 8001CA20 global */ extern UNK_TYPE soundGetDMABuffer(UNK_TYPE...);
/* 8001CA54 global */ extern UNK_TYPE soundSetAddress(UNK_TYPE...);
/* 8001CA60 global */ extern UNK_TYPE soundSetDACRate(UNK_TYPE...);
/* 8001CA80 global */ extern UNK_TYPE soundSetLength(UNK_TYPE...);
/* 8001CAB8 local  */ // extern UNK_TYPE soundMakeBuffer(UNK_TYPE...);
/* 8001CCA4 local  */ // extern UNK_TYPE soundCallbackDMA(UNK_TYPE...);
/* 8001CCCC local  */ // extern UNK_TYPE soundPlayBuffer(UNK_TYPE...);
/* 8001CD8C local  */ // extern UNK_TYPE soundMakeRamp(UNK_TYPE...);
/* 8001D250 global */ extern UNK_TYPE soundWipeBuffers(UNK_TYPE...);
// ======================= frame.c ====================================================
/* 8001D34C global */ extern UNK_TYPE PSMTX44MultVecNoW(UNK_TYPE...);
/* 8001D39C global */ extern UNK_TYPE frameGetTextureInfo(UNK_TYPE...);
/* 8001D4B8 global */ extern UNK_TYPE frameInvalidateCache(UNK_TYPE...);
/* 8001D624 global */ extern UNK_TYPE frameSetMatrixHint(UNK_TYPE...);
/* 8001D740 global */ extern UNK_TYPE frameFixMatrixHint(UNK_TYPE...);
/* 8001D7F8 global */ extern UNK_TYPE frameSetBuffer(UNK_TYPE...);
/* 8001D830 global */ extern UNK_TYPE frameResetUCode(UNK_TYPE...);
/* 8001D8E0 global */ extern UNK_TYPE frameSetViewport(UNK_TYPE...);
/* 8001DA74 global */ extern UNK_TYPE frameSetLookAt(UNK_TYPE...);
/* 8001DB24 global */ extern UNK_TYPE frameSetLight(UNK_TYPE...);
/* 8001DC4C global */ extern UNK_TYPE frameSetLightCount(UNK_TYPE...);
/* 8001DC58 global */ extern UNK_TYPE frameLoadTMEM(UNK_TYPE...);
/* 8001EBA0 global */ extern UNK_TYPE frameLoadTLUT(UNK_TYPE...);
/* 8001EC80 global */ extern UNK_TYPE frameCullDL(UNK_TYPE...);
/* 8001EDCC global */ extern UNK_TYPE frameLoadVertex(UNK_TYPE...);
/* 8001F850 global */ extern UNK_TYPE frameGetMatrix(UNK_TYPE...);
/* 8001F970 global */ extern UNK_TYPE frameSetMatrix(UNK_TYPE...);
/* 8001FFFC global */ extern UNK_TYPE frameGetMode(UNK_TYPE...);
/* 80020014 global */ extern UNK_TYPE frameSetMode(UNK_TYPE...);
/* 800201A8 global */ extern UNK_TYPE frameSetSize(UNK_TYPE...);
/* 800202D0 global */ extern UNK_TYPE frameSetFill(UNK_TYPE...);
/* 800202FC global */ extern UNK_TYPE frameDrawReset(UNK_TYPE...);
/* 80020340 local  */ // extern UNK_TYPE frameLoadTile(UNK_TYPE...);
/* 80020764 local  */ // extern UNK_TYPE frameUpdateCache(UNK_TYPE...);
/* 80020958 local  */ // extern UNK_TYPE frameSetupCache(UNK_TYPE...);
/* 80020E20 local  */ // extern UNK_TYPE frameMakeTexture(UNK_TYPE...);
/* 80020F3C local  */ // extern UNK_TYPE packFreeBlocks(UNK_TYPE...);
/* 80020FA4 local  */ // extern UNK_TYPE packTakeBlocks(UNK_TYPE...);
/* 80021070 local  */ // extern UNK_TYPE frameConvertYUVtoRGB(UNK_TYPE...);
/* 8002113C global */ extern UNK_TYPE frameScaleMatrix(UNK_TYPE...);
/* 80021204 local  */ // extern UNK_TYPE frameEvent(UNK_TYPE...);
/* 80021588 global */ extern UNK_TYPE frameGetDepth(UNK_TYPE...);
/* 800217F8 global */ extern UNK_TYPE frameHackCIMG_Panel(UNK_TYPE...);
/* 8002303C global */ extern UNK_TYPE frameHackTIMG_Panel(UNK_TYPE...);
/* 800230E0 global */ extern UNK_TYPE PanelDrawFR3D(UNK_TYPE...);
/* 80023194 global */ extern UNK_TYPE PanelDrawBG16(UNK_TYPE...);
/* 80023250 global */ extern UNK_TYPE PanelDrawBG8(UNK_TYPE...);
/* 800232FC global */ extern UNK_TYPE frameHackCIMG_Zelda2_Camera(UNK_TYPE...);
/* 80023430 global */ extern UNK_TYPE frameHackCIMG_Zelda2_Shrink(UNK_TYPE...);
/* 800235A4 global */ extern UNK_TYPE frameHackCIMG_Zelda(UNK_TYPE...);
/* 800239E4 global */ extern UNK_TYPE frameHackCIMG_Zelda2(UNK_TYPE...);
/* 8002403C global */ extern UNK_TYPE frameHackTIMG_Zelda(UNK_TYPE...);
/* 80024204 global */ extern UNK_TYPE ZeldaDrawFrameCamera(UNK_TYPE...);
/* 800244F8 global */ extern UNK_TYPE ZeldaDrawFrameShrink(UNK_TYPE...);
/* 80024A04 local  */ // extern UNK_TYPE ZeldaGreyScaleConvert(UNK_TYPE...);
/* 80024D94 global */ extern UNK_TYPE CopyAndConvertCFB(UNK_TYPE...);
/* 800250D8 global */ extern UNK_TYPE ZeldaDrawFrame(UNK_TYPE...);
/* 800253B8 global */ extern UNK_TYPE ZeldaDrawFrameBlur(UNK_TYPE...);
/* 8002569C global */ extern UNK_TYPE ZeldaDrawFrameNoBlend(UNK_TYPE...);
/* 80025890 global */ extern UNK_TYPE _frameDrawRectangle(UNK_TYPE...);
/* 800259B8 global */ extern UNK_TYPE frameEnd(UNK_TYPE...);
/* 80025C40 global */ extern UNK_TYPE frameBegin(UNK_TYPE...);
/* 80025ECC global */ extern UNK_TYPE frameBeginOK(UNK_TYPE...);
/* 80025EE8 global */ extern UNK_TYPE frameSetColor(UNK_TYPE...);
/* 80025FE4 global */ extern UNK_TYPE frameSetDepth(UNK_TYPE...);
/* 80025FF4 global */ extern UNK_TYPE frameSetScissor(UNK_TYPE...);
/* 8002611C global */ extern UNK_TYPE frameShow(UNK_TYPE...);
/* 80026124 local  */ // extern UNK_TYPE frameDrawRectTexture_Setup(UNK_TYPE...);
/* 80026514 local  */ // extern UNK_TYPE frameDrawRectTexture(UNK_TYPE...);
/* 800269EC local  */ // extern UNK_TYPE frameDrawRectFill_Setup(UNK_TYPE...);
/* 80026A9C local  */ // extern UNK_TYPE frameDrawRectFill(UNK_TYPE...);
/* 80026D30 local  */ // extern UNK_TYPE frameDrawLine_Setup(UNK_TYPE...);
/* 80026E0C local  */ // extern UNK_TYPE frameDrawLine_C2T2(UNK_TYPE...);
/* 80027028 local  */ // extern UNK_TYPE frameDrawLine_C1T2(UNK_TYPE...);
/* 80027234 local  */ // extern UNK_TYPE frameDrawLine_C0T2(UNK_TYPE...);
/* 800273EC local  */ // extern UNK_TYPE frameDrawLine_C2T0(UNK_TYPE...);
/* 800275C4 local  */ // extern UNK_TYPE frameDrawLine_C1T0(UNK_TYPE...);
/* 8002778C local  */ // extern UNK_TYPE frameDrawLine_C0T0(UNK_TYPE...);
/* 80027900 local  */ // extern UNK_TYPE frameDrawTriangle_Setup(UNK_TYPE...);
/* 800279DC local  */ // extern UNK_TYPE frameDrawTriangle_C3T3(UNK_TYPE...);
/* 80027B80 local  */ // extern UNK_TYPE frameCheckTriangleDivide(UNK_TYPE...);
/* 80028A44 local  */ // extern UNK_TYPE frameDrawTriangle_C1T3(UNK_TYPE...);
/* 80028C34 local  */ // extern UNK_TYPE frameDrawTriangle_C0T3(UNK_TYPE...);
/* 80028DC0 local  */ // extern UNK_TYPE frameDrawTriangle_C3T0(UNK_TYPE...);
/* 80028F7C local  */ // extern UNK_TYPE frameDrawTriangle_C1T0(UNK_TYPE...);
/* 80029118 local  */ // extern UNK_TYPE frameDrawTriangle_C0T0(UNK_TYPE...);
/* 80029250 local  */ // extern UNK_TYPE frameDrawSetupDP(UNK_TYPE...);
/* 800297BC local  */ // extern UNK_TYPE frameGetCombineAlpha(UNK_TYPE...);
/* 8002984C local  */ // extern UNK_TYPE frameGetCombineColor(UNK_TYPE...);
/* 80029948 local  */ // extern UNK_TYPE frameDrawSetupSP(UNK_TYPE...);
/* 8002A2FC global */ extern UNK_TYPE frameDrawSetup2D(UNK_TYPE...);
/* 8002A4A8 local  */ // extern UNK_TYPE frameLoadTexture(UNK_TYPE...);
/* 8002A784 local  */ // extern UNK_TYPE frameMakePixels(UNK_TYPE...);
/* 8002C178 local  */ // extern UNK_TYPE frameMakeTLUT(UNK_TYPE...);
/* 8002C2E4 local  */ // extern UNK_TYPE frameDrawDone(UNK_TYPE...);
/* 8002C360 local  */ // extern UNK_TYPE frameDrawSyncCallback(UNK_TYPE...);
/* 8002C378 local  */ // extern UNK_TYPE frameDrawSetupFog_Default(UNK_TYPE...);
/* 8002C67C local  */ // extern UNK_TYPE frameDrawSetupFog_Zelda1(UNK_TYPE...);
// ======================= system.c ===================================================
/* 8002CA14 global */ extern UNK_TYPE systemEvent(UNK_TYPE...);
/* 8002D2EC global */ extern UNK_TYPE systemExceptionPending(UNK_TYPE...);
/* 8002D324 global */ extern UNK_TYPE systemCheckInterrupts(UNK_TYPE...);
/* 8002D47C global */ extern UNK_TYPE systemExecute(UNK_TYPE...);
/* 8002D578 global */ extern UNK_TYPE systemReset(UNK_TYPE...);
/* 8002D730 global */ extern UNK_TYPE systemGetStorageDevice(UNK_TYPE...);
/* 8002D740 global */ extern UNK_TYPE systemSetStorageDevice(UNK_TYPE...);
/* 8002D82C global */ extern UNK_TYPE systemGetMode(UNK_TYPE...);
/* 8002D894 global */ extern UNK_TYPE systemSetMode(UNK_TYPE...);
/* 8002D904 global */ extern UNK_TYPE systemCopyROM(UNK_TYPE...);
/* 8002D9F8 local  */ // extern UNK_TYPE __systemCopyROM_Complete(UNK_TYPE...);
/* 8002DB30 local  */ // extern UNK_TYPE systemPut64(UNK_TYPE...);
/* 8002DB38 local  */ // extern UNK_TYPE systemPut32(UNK_TYPE...);
/* 8002DB40 local  */ // extern UNK_TYPE systemPut16(UNK_TYPE...);
/* 8002DB48 local  */ // extern UNK_TYPE systemPut8(UNK_TYPE...);
/* 8002DB50 local  */ // extern UNK_TYPE systemGet64(UNK_TYPE...);
/* 8002DB64 local  */ // extern UNK_TYPE systemGet32(UNK_TYPE...);
/* 8002DB74 local  */ // extern UNK_TYPE systemGet16(UNK_TYPE...);
/* 8002DB84 local  */ // extern UNK_TYPE systemGet8(UNK_TYPE...);
/* 8002DB94 local  */ // extern UNK_TYPE systemGetException(UNK_TYPE...);
/* 8002DD70 local  */ // extern UNK_TYPE systemSetupGameALL(UNK_TYPE...);
/* 80030364 global */ extern UNK_TYPE systemGetInitialConfiguration(UNK_TYPE...);
/* 80030B38 local  */ // extern UNK_TYPE systemSetupGameRAM(UNK_TYPE...);
// ======================= cpu.c ======================================================
/* 80030E70 local  */ // extern UNK_TYPE cpuOpcodeChecksum(UNK_TYPE...);
/* 80030F84 local  */ // extern UNK_TYPE treePrintNode(UNK_TYPE...);
/* 80031168 local  */ // extern UNK_TYPE treeForceCleanNodes(UNK_TYPE...);
/* 8003133C local  */ // extern UNK_TYPE treeCleanNodes(UNK_TYPE...);
/* 8003161C local  */ // extern UNK_TYPE treeCleanUp(UNK_TYPE...);
/* 8003174C local  */ // extern UNK_TYPE treeTimerCheck(UNK_TYPE...);
/* 80031860 local  */ // extern UNK_TYPE treeKillReason(UNK_TYPE...);
/* 800318F0 local  */ // extern UNK_TYPE treeKillRange(UNK_TYPE...);
/* 80032088 local  */ // extern UNK_TYPE treeSearchNode(UNK_TYPE...);
/* 800320EC local  */ // extern UNK_TYPE treeAdjustRoot(UNK_TYPE...);
/* 800322D8 local  */ // extern UNK_TYPE treeBalance(UNK_TYPE...);
/* 80032470 local  */ // extern UNK_TYPE treeInsertNode(UNK_TYPE...);
/* 80032558 global */ extern UNK_TYPE treeInsert(UNK_TYPE...);
/* 80032674 local  */ // extern UNK_TYPE treeDeleteNode(UNK_TYPE...);
/* 800329D4 local  */ // extern UNK_TYPE treeKillNodes(UNK_TYPE...);
/* 80032C84 local  */ // extern UNK_TYPE treeKill(UNK_TYPE...);
/* 80032F2C local  */ // extern UNK_TYPE treeInitNode(UNK_TYPE...);
/* 80033048 local  */ // extern UNK_TYPE treeInit(UNK_TYPE...);
/* 800330A0 local  */ // extern UNK_TYPE treeCallerCheck(UNK_TYPE...);
/* 800331A4 local  */ // extern UNK_TYPE cpuDMAUpdateFunction(UNK_TYPE...);
/* 80033304 global */ extern UNK_TYPE cpuFindFunction(UNK_TYPE...);
/* 80033E88 local  */ // extern UNK_TYPE cpuTreeTake(UNK_TYPE...);
/* 80033F3C global */ extern UNK_TYPE cpuHeapFree(UNK_TYPE...);
/* 80034028 global */ extern UNK_TYPE cpuHeapTake(UNK_TYPE...);
/* 80034288 local  */ // extern UNK_TYPE cpuHeapReset(UNK_TYPE...);
/* 80034324 global */ extern UNK_TYPE cpuGetFunctionChecksum(UNK_TYPE...);
/* 80034564 global */ extern UNK_TYPE cpuInvalidateCache(UNK_TYPE...);
/* 800345F0 global */ extern UNK_TYPE cpuGetOffsetAddress(UNK_TYPE...);
/* 80034780 global */ extern UNK_TYPE cpuGetAddressBuffer(UNK_TYPE...);
/* 800347F8 global */ extern UNK_TYPE cpuGetAddressOffset(UNK_TYPE...);
/* 80034864 global */ extern UNK_TYPE cpuEvent(UNK_TYPE...);
/* 80034A6C global */ extern UNK_TYPE cpuSetXPC(UNK_TYPE...);
/* 80034AE8 global */ extern UNK_TYPE cpuReset(UNK_TYPE...);
/* 80034FCC global */ extern UNK_TYPE cpuSetCodeHack(UNK_TYPE...);
/* 80035038 global */ extern UNK_TYPE cpuSetDevicePut(UNK_TYPE...);
/* 80035050 global */ extern UNK_TYPE cpuSetDeviceGet(UNK_TYPE...);
/* 80035068 global */ extern UNK_TYPE cpuMapObject(UNK_TYPE...);
/* 80035218 global */ extern UNK_TYPE __cpuBreak(UNK_TYPE...);
/* 8003522C global */ extern UNK_TYPE __cpuERET(UNK_TYPE...);
/* 800352C8 global */ extern UNK_TYPE cpuGetRegisterCP0(UNK_TYPE...);
/* 80035570 global */ extern UNK_TYPE cpuSetRegisterCP0(UNK_TYPE...);
/* 8003573C local  */ // extern UNK_TYPE cpuSetCP0_Status(UNK_TYPE...);
/* 800357D0 local  */ // extern UNK_TYPE cpuGetSize(UNK_TYPE...);
/* 80035914 local  */ // extern UNK_TYPE cpuGetMode(UNK_TYPE...);
/* 800359EC local  */ // extern UNK_TYPE cpuSetTLB(UNK_TYPE...);
/* 80035CD0 local  */ // extern UNK_TYPE cpuMapAddress(UNK_TYPE...);
/* 80035E98 local  */ // extern UNK_TYPE cpuFreeDevice(UNK_TYPE...);
/* 80035F3C local  */ // extern UNK_TYPE cpuMakeDevice(UNK_TYPE...);
/* 8003604C global */ extern UNK_TYPE cpuException(UNK_TYPE...);
/* 8003630C global */ extern UNK_TYPE cpuTestInterrupt(UNK_TYPE...);
/* 800363E8 local  */ // extern UNK_TYPE cpuFindCachedAddress(UNK_TYPE...);
/* 800365C4 global */ extern UNK_TYPE cpuFreeCachedAddress(UNK_TYPE...);
/* 80036658 local  */ // extern UNK_TYPE cpuHackHandler(UNK_TYPE...);
/* 80036870 global */ extern UNK_TYPE cpuExecute(UNK_TYPE...);
/* 800374DC local  */ // extern UNK_TYPE cpuMakeLink(UNK_TYPE...);
/* 8003779C local  */ // extern UNK_TYPE cpuExecuteLoadStoreF(UNK_TYPE...);
/* 800382F8 local  */ // extern UNK_TYPE cpuExecuteLoadStore(UNK_TYPE...);
/* 80039158 local  */ // extern UNK_TYPE cpuExecuteCall(UNK_TYPE...);
/* 800393B8 local  */ // extern UNK_TYPE cpuExecuteJump(UNK_TYPE...);
/* 80039488 local  */ // extern UNK_TYPE cpuExecuteIdle(UNK_TYPE...);
/* 80039594 local  */ // extern UNK_TYPE cpuExecuteOpcode(UNK_TYPE...);
/* 8003DF08 local  */ // extern UNK_TYPE cpuExecuteUpdate(UNK_TYPE...);
/* 8003E204 local  */ // extern UNK_TYPE cpuRetraceCallback(UNK_TYPE...);
/* 8003E214 local  */ // extern UNK_TYPE cpuNextInstruction(UNK_TYPE...);
/* 8003E4D8 local  */ // extern UNK_TYPE cpuFindAddress(UNK_TYPE...);
/* 8003E974 global */ extern UNK_TYPE cpuMakeFunction(UNK_TYPE...);
/* 8003EE04 local  */ // extern UNK_TYPE cpuGetPPC(UNK_TYPE...);
/* 80068238 local  */ // extern UNK_TYPE cpuCheckDelaySlot(UNK_TYPE...);
/* 80068368 local  */ // extern UNK_TYPE cpuCompile_LWR(UNK_TYPE...);
/* 800684F4 local  */ // extern UNK_TYPE cpuCompile_LWL(UNK_TYPE...);
/* 80068684 local  */ // extern UNK_TYPE cpuCompile_SDC(UNK_TYPE...);
/* 8006880C local  */ // extern UNK_TYPE cpuCompile_LDC(UNK_TYPE...);
/* 80068994 local  */ // extern UNK_TYPE cpuCompile_SW(UNK_TYPE...);
/* 80068AF0 local  */ // extern UNK_TYPE cpuCompile_SH(UNK_TYPE...);
/* 80068C4C local  */ // extern UNK_TYPE cpuCompile_SB(UNK_TYPE...);
/* 80068DA8 local  */ // extern UNK_TYPE cpuCompile_LHU(UNK_TYPE...);
/* 80068F00 local  */ // extern UNK_TYPE cpuCompile_LBU(UNK_TYPE...);
/* 80069058 local  */ // extern UNK_TYPE cpuCompile_LW(UNK_TYPE...);
/* 800691B0 local  */ // extern UNK_TYPE cpuCompile_LH(UNK_TYPE...);
/* 8006931C local  */ // extern UNK_TYPE cpuCompile_LB(UNK_TYPE...);
/* 80069488 local  */ // extern UNK_TYPE cpuCompile_FLOOR_W(UNK_TYPE...);
/* 80069644 local  */ // extern UNK_TYPE cpuCompile_CEIL_W(UNK_TYPE...);
/* 80069800 local  */ // extern UNK_TYPE cpuCompile_L_CVT_SD(UNK_TYPE...);
/* 80069D80 local  */ // extern UNK_TYPE cpuCompile_W_CVT_SD(UNK_TYPE...);
/* 80069F30 local  */ // extern UNK_TYPE cpuCompile_D_SQRT(UNK_TYPE...);
/* 8006A364 local  */ // extern UNK_TYPE cpuCompile_S_SQRT(UNK_TYPE...);
/* 8006A6A4 local  */ // extern UNK_TYPE cpuCompile_DDIVU(UNK_TYPE...);
/* 8006AAC0 local  */ // extern UNK_TYPE cpuCompile_DDIV(UNK_TYPE...);
/* 8006B07C local  */ // extern UNK_TYPE cpuCompile_DMULTU(UNK_TYPE...);
/* 8006B390 local  */ // extern UNK_TYPE cpuCompile_DMULT(UNK_TYPE...);
/* 8006B894 local  */ // extern UNK_TYPE cpuCompile_DSRAV(UNK_TYPE...);
/* 8006BA98 local  */ // extern UNK_TYPE cpuCompile_DSRLV(UNK_TYPE...);
/* 8006BC80 local  */ // extern UNK_TYPE cpuCompile_DSLLV(UNK_TYPE...);
// ======================= pif.c ======================================================
/* 8006BE68 global */ extern UNK_TYPE pifEvent(UNK_TYPE...);
/* 8006C090 global */ extern UNK_TYPE pifGetData(UNK_TYPE...);
/* 8006C0FC global */ extern UNK_TYPE pifSetData(UNK_TYPE...);
/* 8006C15C global */ extern UNK_TYPE pifProcessOutputData(UNK_TYPE...);
/* 8006C2F8 global */ extern UNK_TYPE pifProcessInputData(UNK_TYPE...);
/* 8006C488 global */ extern UNK_TYPE pifExecuteCommand(UNK_TYPE...);
/* 8006C72C local  */ // extern UNK_TYPE pifGet64(UNK_TYPE...);
/* 8006C780 local  */ // extern UNK_TYPE pifGet32(UNK_TYPE...);
/* 8006C7BC local  */ // extern UNK_TYPE pifGet16(UNK_TYPE...);
/* 8006C7F8 local  */ // extern UNK_TYPE pifGet8(UNK_TYPE...);
/* 8006C82C local  */ // extern UNK_TYPE pifPut64(UNK_TYPE...);
/* 8006C860 local  */ // extern UNK_TYPE pifPut32(UNK_TYPE...);
/* 8006C888 local  */ // extern UNK_TYPE pifPut16(UNK_TYPE...);
/* 8006C8B0 local  */ // extern UNK_TYPE pifPut8(UNK_TYPE...);
/* 8006C8D4 global */ extern UNK_TYPE pifGetEEPROMSize(UNK_TYPE...);
/* 8006C918 global */ extern UNK_TYPE pifSetEEPROMType(UNK_TYPE...);
/* 8006C97C global */ extern UNK_TYPE pifGetEControllerType(UNK_TYPE...);
/* 8006C994 global */ extern UNK_TYPE pifSetControllerType(UNK_TYPE...);
/* 8006CAA4 local  */ // extern UNK_TYPE pifContDataCrc(UNK_TYPE...);
/* 8006CC1C global */ extern UNK_TYPE pifWriteRumble(UNK_TYPE...);
/* 8006CC74 global */ extern UNK_TYPE pifReadRumble(UNK_TYPE...);
// ======================= ram.c ======================================================
/* 8006CD98 global */ extern UNK_TYPE ramEvent(UNK_TYPE...);
/* 8006CFD0 global */ extern UNK_TYPE ramGetSize(UNK_TYPE...);
/* 8006CFE8 global */ extern UNK_TYPE ramSetSize(UNK_TYPE...);
/* 8006D058 global */ extern UNK_TYPE ramWipe(UNK_TYPE...);
/* 8006D0A0 global */ extern UNK_TYPE ramGetBuffer(UNK_TYPE...);
/* 8006D0F8 local  */ // extern UNK_TYPE ramGet64(UNK_TYPE...);
/* 8006D13C local  */ // extern UNK_TYPE ramGet32(UNK_TYPE...);
/* 8006D170 local  */ // extern UNK_TYPE ramGet16(UNK_TYPE...);
/* 8006D1A4 local  */ // extern UNK_TYPE ramGet8(UNK_TYPE...);
/* 8006D1D4 local  */ // extern UNK_TYPE ramPut64(UNK_TYPE...);
/* 8006D208 local  */ // extern UNK_TYPE ramPut32(UNK_TYPE...);
/* 8006D230 local  */ // extern UNK_TYPE ramPut16(UNK_TYPE...);
/* 8006D258 local  */ // extern UNK_TYPE ramPut8(UNK_TYPE...);
/* 8006D27C local  */ // extern UNK_TYPE ramGetRI64(UNK_TYPE...);
/* 8006D284 local  */ // extern UNK_TYPE ramGetRI32(UNK_TYPE...);
/* 8006D2B8 local  */ // extern UNK_TYPE ramGetRI16(UNK_TYPE...);
/* 8006D2C0 local  */ // extern UNK_TYPE ramGetRI8(UNK_TYPE...);
/* 8006D2C8 local  */ // extern UNK_TYPE ramPutRI64(UNK_TYPE...);
/* 8006D2D0 local  */ // extern UNK_TYPE ramPutRI32(UNK_TYPE...);
/* 8006D304 local  */ // extern UNK_TYPE ramPutRI16(UNK_TYPE...);
/* 8006D30C local  */ // extern UNK_TYPE ramPutRI8(UNK_TYPE...);
/* 8006D314 local  */ // extern UNK_TYPE ramGetControl64(UNK_TYPE...);
/* 8006D31C local  */ // extern UNK_TYPE ramGetControl32(UNK_TYPE...);
/* 8006D350 local  */ // extern UNK_TYPE ramGetControl16(UNK_TYPE...);
/* 8006D358 local  */ // extern UNK_TYPE ramGetControl8(UNK_TYPE...);
/* 8006D360 local  */ // extern UNK_TYPE ramPutControl64(UNK_TYPE...);
/* 8006D368 local  */ // extern UNK_TYPE ramPutControl32(UNK_TYPE...);
/* 8006D39C local  */ // extern UNK_TYPE ramPutControl16(UNK_TYPE...);
/* 8006D3A4 local  */ // extern UNK_TYPE ramPutControl8(UNK_TYPE...);
// ======================= rom.c ======================================================
/* 8006D3AC global */ extern UNK_TYPE romEvent(UNK_TYPE...);
/* 8006D5D8 global */ extern UNK_TYPE romGetImage(UNK_TYPE...);
/* 8006D620 global */ extern UNK_TYPE romSetImage(UNK_TYPE...);
/* 8006D794 global */ extern UNK_TYPE romSetCacheSize(UNK_TYPE...);
/* 8006D830 global */ extern UNK_TYPE romUpdate(UNK_TYPE...);
/* 8006D990 global */ extern UNK_TYPE romCopyImmediate(UNK_TYPE...);
/* 8006DBF8 global */ extern UNK_TYPE romCopy(UNK_TYPE...);
/* 8006DE90 local  */ // extern UNK_TYPE romGetDebug64(UNK_TYPE...);
/* 8006DEA4 local  */ // extern UNK_TYPE romGetDebug32(UNK_TYPE...);
/* 8006DEB4 local  */ // extern UNK_TYPE romGetDebug16(UNK_TYPE...);
/* 8006DEC4 local  */ // extern UNK_TYPE romGetDebug8(UNK_TYPE...);
/* 8006DED4 local  */ // extern UNK_TYPE romPutDebug64(UNK_TYPE...);
/* 8006DEDC local  */ // extern UNK_TYPE romPutDebug32(UNK_TYPE...);
/* 8006DEE4 local  */ // extern UNK_TYPE romPutDebug16(UNK_TYPE...);
/* 8006DEEC local  */ // extern UNK_TYPE romPutDebug8(UNK_TYPE...);
/* 8006DEF4 local  */ // extern UNK_TYPE romGet64(UNK_TYPE...);
/* 8006DF70 local  */ // extern UNK_TYPE romGet32(UNK_TYPE...);
/* 8006DFE0 local  */ // extern UNK_TYPE romGet16(UNK_TYPE...);
/* 8006E050 local  */ // extern UNK_TYPE romGet8(UNK_TYPE...);
/* 8006E0C0 local  */ // extern UNK_TYPE romPut64(UNK_TYPE...);
/* 8006E0C8 local  */ // extern UNK_TYPE romPut32(UNK_TYPE...);
/* 8006E0D0 local  */ // extern UNK_TYPE romPut16(UNK_TYPE...);
/* 8006E0D8 local  */ // extern UNK_TYPE romPut8(UNK_TYPE...);
/* 8006E0E0 global */ extern UNK_TYPE romTestCode(UNK_TYPE...);
/* 8006E1A4 global */ extern UNK_TYPE romGetCode(UNK_TYPE...);
/* 8006E1D8 global */ extern UNK_TYPE romGetPC(UNK_TYPE...);
/* 8006E3D4 local  */ // extern UNK_TYPE romLoadFullOrPart(UNK_TYPE...);
/* 8006E83C local  */ // extern UNK_TYPE romCopyUpdate(UNK_TYPE...);
/* 8006EAC0 local  */ // extern UNK_TYPE __romCopyUpdate_Complete(UNK_TYPE...);
/* 8006EADC local  */ // extern UNK_TYPE romLoadUpdate(UNK_TYPE...);
/* 8006EC3C local  */ // extern UNK_TYPE __romLoadUpdate_Complete(UNK_TYPE...);
/* 8006EC58 local  */ // extern UNK_TYPE romCacheGame(UNK_TYPE...);
/* 8006F208 local  */ // extern UNK_TYPE romCacheGame_ZELDA(UNK_TYPE...);
/* 8006F488 local  */ // extern UNK_TYPE romLoadRange(UNK_TYPE...);
/* 8006F5D4 local  */ // extern UNK_TYPE romLoadBlock(UNK_TYPE...);
/* 8006F6D0 local  */ // extern UNK_TYPE __romLoadBlock_CompleteGCN(UNK_TYPE...);
/* 8006F6EC local  */ // extern UNK_TYPE __romLoadBlock_Complete(UNK_TYPE...);
/* 8006F7E0 local  */ // extern UNK_TYPE romSetBlockCache(UNK_TYPE...);
/* 8006FA38 local  */ // extern UNK_TYPE romMakeFreeCache(UNK_TYPE...);
/* 8006FC4C local  */ // extern UNK_TYPE romFindOldestBlock(UNK_TYPE...);
/* 8006FDFC local  */ // extern UNK_TYPE romFindFreeCache(UNK_TYPE...);
// ======================= rdp.c ======================================================
/* 8006FEC0 global */ extern UNK_TYPE rdpEvent(UNK_TYPE...);
/* 80070064 local  */ // extern UNK_TYPE rdpGetSpan64(UNK_TYPE...);
/* 8007006C local  */ // extern UNK_TYPE rdpGetSpan32(UNK_TYPE...);
/* 800700DC local  */ // extern UNK_TYPE rdpGetSpan16(UNK_TYPE...);
/* 800700E4 local  */ // extern UNK_TYPE rdpGetSpan8(UNK_TYPE...);
/* 800700EC local  */ // extern UNK_TYPE rdpPutSpan64(UNK_TYPE...);
/* 800700F4 local  */ // extern UNK_TYPE rdpPutSpan32(UNK_TYPE...);
/* 80070158 local  */ // extern UNK_TYPE rdpPutSpan16(UNK_TYPE...);
/* 80070160 local  */ // extern UNK_TYPE rdpPutSpan8(UNK_TYPE...);
/* 80070168 local  */ // extern UNK_TYPE rdpGet64(UNK_TYPE...);
/* 80070170 local  */ // extern UNK_TYPE rdpGet32(UNK_TYPE...);
/* 80070214 local  */ // extern UNK_TYPE rdpGet16(UNK_TYPE...);
/* 8007021C local  */ // extern UNK_TYPE rdpGet8(UNK_TYPE...);
/* 80070224 local  */ // extern UNK_TYPE rdpPut64(UNK_TYPE...);
/* 8007022C local  */ // extern UNK_TYPE rdpPut32(UNK_TYPE...);
/* 80070330 local  */ // extern UNK_TYPE rdpPut16(UNK_TYPE...);
/* 80070338 local  */ // extern UNK_TYPE rdpPut8(UNK_TYPE...);
/* 80070340 global */ extern UNK_TYPE rdpParseGBI(UNK_TYPE...);
// ======================= rdb.c ======================================================
/* 800715D0 global */ extern UNK_TYPE rdbEvent(UNK_TYPE...);
/* 800716D8 local  */ // extern UNK_TYPE rdbGet64(UNK_TYPE...);
/* 800716E0 local  */ // extern UNK_TYPE rdbGet32(UNK_TYPE...);
/* 80071714 local  */ // extern UNK_TYPE rdbGet16(UNK_TYPE...);
/* 8007171C local  */ // extern UNK_TYPE rdbGet8(UNK_TYPE...);
/* 80071724 local  */ // extern UNK_TYPE rdbPut64(UNK_TYPE...);
/* 8007172C local  */ // extern UNK_TYPE rdbPut32(UNK_TYPE...);
/* 80071BA8 local  */ // extern UNK_TYPE rdbPut16(UNK_TYPE...);
/* 80071BB0 local  */ // extern UNK_TYPE rdbPut8(UNK_TYPE...);
// ======================= rsp.c ======================================================
/* 80071BB8 global */ extern UNK_TYPE rspEvent(UNK_TYPE...);
/* 80071D8C global */ extern UNK_TYPE rspUpdate(UNK_TYPE...);
/* 80071F6C global */ extern UNK_TYPE rspFrameComplete(UNK_TYPE...);
/* 80071FC0 global */ extern UNK_TYPE rspEnableABI(UNK_TYPE...);
/* 80071FE0 global */ extern UNK_TYPE rspInvalidateCache(UNK_TYPE...);
/* 800720B8 global */ extern UNK_TYPE rspGet64(UNK_TYPE...);
/* 80072124 global */ extern UNK_TYPE rspGet32(UNK_TYPE...);
/* 80072270 global */ extern UNK_TYPE rspGet16(UNK_TYPE...);
/* 800722C4 global */ extern UNK_TYPE rspGet8(UNK_TYPE...);
/* 80072318 global */ extern UNK_TYPE rspPut64(UNK_TYPE...);
/* 80072384 global */ extern UNK_TYPE rspPut32(UNK_TYPE...);
/* 800729B4 global */ extern UNK_TYPE rspPut16(UNK_TYPE...);
/* 80072A08 global */ extern UNK_TYPE rspPut8(UNK_TYPE...);
/* 80072A5C local  */ // extern UNK_TYPE rspParseGBI(UNK_TYPE...);
/* 80072C10 local  */ // extern UNK_TYPE rspParseGBI_Setup(UNK_TYPE...);
/* 80072D6C local  */ // extern UNK_TYPE rspLoadYield(UNK_TYPE...);
/* 80072EF4 local  */ // extern UNK_TYPE rspSaveYield(UNK_TYPE...);
/* 8007306C local  */ // extern UNK_TYPE rspFindUCode(UNK_TYPE...);
/* 800741CC local  */ // extern UNK_TYPE rspLoadMatrix(UNK_TYPE...);
/* 80074454 local  */ // extern UNK_TYPE rspParseGBI_F3DEX2(UNK_TYPE...);
/* 80076024 local  */ // extern UNK_TYPE rspGeometryMode(UNK_TYPE...);
/* 8007610C local  */ // extern UNK_TYPE rspParseGBI_F3DEX1(UNK_TYPE...);
/* 80077790 local  */ // extern UNK_TYPE rspSetGeometryMode1(UNK_TYPE...);
/* 80077850 local  */ // extern UNK_TYPE rspSetupS2DEX(UNK_TYPE...);
/* 800779B0 local  */ // extern UNK_TYPE rspObjMatrix(UNK_TYPE...);
/* 80077B18 global */ extern UNK_TYPE rspBgRectCopy(UNK_TYPE...);
/* 80077CB8 local  */ // extern UNK_TYPE rspObjRectangleR(UNK_TYPE...);
/* 8007876C local  */ // extern UNK_TYPE rspObjSprite(UNK_TYPE...);
/* 80079234 local  */ // extern UNK_TYPE rspObjRectangle(UNK_TYPE...);
/* 800797D0 local  */ // extern UNK_TYPE rspObjLoadTxtr(UNK_TYPE...);
/* 80079C1C global */ extern UNK_TYPE rspFillObjTxtr(UNK_TYPE...);
/* 80079D7C local  */ // extern UNK_TYPE guS2DEmuBgRect1Cyc(UNK_TYPE...);
/* 8007A4B8 local  */ // extern UNK_TYPE tmemLoad(UNK_TYPE...);
/* 8007A728 local  */ // extern UNK_TYPE tmemLoad_A(UNK_TYPE...);
/* 8007A7D4 local  */ // extern UNK_TYPE tmemLoad_B(UNK_TYPE...);
/* 8007A8E8 global */ extern UNK_TYPE rspSetImage(UNK_TYPE...);
/* 8007A97C global */ extern UNK_TYPE rspFillObjBg(UNK_TYPE...);
/* 8007AA74 global */ extern UNK_TYPE rspFillObjBgScale(UNK_TYPE...);
/* 8007AB54 local  */ // extern UNK_TYPE rspFillObjSprite(UNK_TYPE...);
/* 8007AC1C local  */ // extern UNK_TYPE Matrix4by4Identity(UNK_TYPE...);
/* 8007AC6C local  */ // extern UNK_TYPE rspParseJPEG_DecodeZ(UNK_TYPE...);
/* 8007AD68 local  */ // extern UNK_TYPE rspParseJPEG_EncodeZ(UNK_TYPE...);
/* 8007AE64 global */ extern UNK_TYPE rspRecon420Z(UNK_TYPE...);
/* 8007B244 global */ extern UNK_TYPE rspUndoRecon420Z(UNK_TYPE...);
/* 8007B64C global */ extern UNK_TYPE rspUndoLoadColorBufferZ(UNK_TYPE...);
/* 8007B6E0 global */ extern UNK_TYPE rspUndoDCTZ(UNK_TYPE...);
/* 8007B9B0 global */ extern UNK_TYPE rspUndoZigzagDataZ(UNK_TYPE...);
/* 8007BDD8 global */ extern UNK_TYPE rspUndoQuantizeZ(UNK_TYPE...);
/* 8007C3A4 global */ extern UNK_TYPE rspZigzagDataZ(UNK_TYPE...);
/* 8007C8CC local  */ // extern UNK_TYPE rspQuantizeZ(UNK_TYPE...);
/* 8007CEF8 local  */ // extern UNK_TYPE rspDCTZ(UNK_TYPE...);
/* 8007D1C8 local  */ // extern UNK_TYPE rspCreateJPEGArraysZ(UNK_TYPE...);
/* 8007D4C0 local  */ // extern UNK_TYPE rspParseJPEG_Decode(UNK_TYPE...);
/* 8007DD0C local  */ // extern UNK_TYPE rspParseJPEG_Encode(UNK_TYPE...);
/* 8007E744 global */ extern UNK_TYPE rspFormatYUV(UNK_TYPE...);
/* 8007E8F4 global */ extern UNK_TYPE rspUndoYUVtoDCTBuf(UNK_TYPE...);
/* 8007F07C global */ extern UNK_TYPE rspUndoDCT(UNK_TYPE...);
/* 8007F368 global */ extern UNK_TYPE rspUndoQuantize(UNK_TYPE...);
/* 8007F4EC local  */ // extern UNK_TYPE rspQuantize(UNK_TYPE...);
/* 8007F668 local  */ // extern UNK_TYPE rspDCT(UNK_TYPE...);
/* 8007F938 local  */ // extern UNK_TYPE rspYUVtoDCTBuf(UNK_TYPE...);
/* 80080028 local  */ // extern UNK_TYPE rspConvertRGBAtoYUV(UNK_TYPE...);
/* 800801C0 local  */ // extern UNK_TYPE rspCreateJPEGArrays(UNK_TYPE...);
/* 80080AA4 local  */ // extern UNK_TYPE rspParseABI4(UNK_TYPE...);
/* 800811C0 local  */ // extern UNK_TYPE rspInitAudioDMEM4(UNK_TYPE...);
/* 80082624 local  */ // extern UNK_TYPE rspParseABI3(UNK_TYPE...);
/* 80082B94 local  */ // extern UNK_TYPE rspAMix3(UNK_TYPE...);
/* 80082C2C local  */ // extern UNK_TYPE rspAEnvMixer3(UNK_TYPE...);
/* 80082E60 local  */ // extern UNK_TYPE rspInitAudioDMEM3(UNK_TYPE...);
/* 8008429C local  */ // extern UNK_TYPE rspParseABI2(UNK_TYPE...);
/* 80084984 local  */ // extern UNK_TYPE rspAPCM8Dec2(UNK_TYPE...);
/* 80085218 local  */ // extern UNK_TYPE rspAEnvMixer2(UNK_TYPE...);
/* 800854F0 local  */ // extern UNK_TYPE rspADistFilter2(UNK_TYPE...);
/* 800855FC local  */ // extern UNK_TYPE rspAInterleave2(UNK_TYPE...);
/* 80085848 local  */ // extern UNK_TYPE rspAMix2(UNK_TYPE...);
/* 800858D0 local  */ // extern UNK_TYPE rspAFirFilter2(UNK_TYPE...);
/* 80086680 local  */ // extern UNK_TYPE rspAResample2(UNK_TYPE...);
/* 800868B0 local  */ // extern UNK_TYPE rspANMix2(UNK_TYPE...);
/* 8008691C local  */ // extern UNK_TYPE rspANoise2(UNK_TYPE...);
/* 80086BE8 local  */ // extern UNK_TYPE rspAADPCMDec2Fast(UNK_TYPE...);
/* 80087520 local  */ // extern UNK_TYPE rspInitAudioDMEM2(UNK_TYPE...);
/* 800887E8 local  */ // extern UNK_TYPE rspParseABI1(UNK_TYPE...);
/* 80088B48 local  */ // extern UNK_TYPE rspParseABI(UNK_TYPE...);
/* 80088D74 local  */ // extern UNK_TYPE rspASetVolume1(UNK_TYPE...);
/* 80088E0C local  */ // extern UNK_TYPE rspASetBuffer1(UNK_TYPE...);
/* 80088F14 local  */ // extern UNK_TYPE rspAResample1(UNK_TYPE...);
/* 8008920C local  */ // extern UNK_TYPE rspAMix1(UNK_TYPE...);
/* 800892A4 local  */ // extern UNK_TYPE rspAEnvMixer1(UNK_TYPE...);
/* 80089E7C local  */ // extern UNK_TYPE rspAPoleFilter1(UNK_TYPE...);
/* 8008A7E0 local  */ // extern UNK_TYPE rspAADPCMDec1Fast(UNK_TYPE...);
/* 8008B080 local  */ // extern UNK_TYPE rspLoadADPCMCoefTable2(UNK_TYPE...);
/* 8008B1FC local  */ // extern UNK_TYPE rspLoadADPCMCoefTable1(UNK_TYPE...);
/* 8008B378 global */ extern UNK_TYPE rspMultPolef(UNK_TYPE...);
/* 8008B768 global */ extern UNK_TYPE rspDotProduct8x15MatrixBy15x1Vector(UNK_TYPE...);
/* 8008BBDC local  */ // extern UNK_TYPE rspInitAudioDMEM1(UNK_TYPE...);
/* 8008CF0C local  */ // extern UNK_TYPE rspVMADN(UNK_TYPE...);
/* 8008D0B0 local  */ // extern UNK_TYPE rspVMUDN(UNK_TYPE...);
// ======================= mips.c =====================================================
/* 8008D248 global */ extern UNK_TYPE mipsEvent(UNK_TYPE...);
/* 8008D358 global */ extern UNK_TYPE mipsGet64(UNK_TYPE...);
/* 8008D360 global */ extern UNK_TYPE mipsGet32(UNK_TYPE...);
/* 8008D3C8 global */ extern UNK_TYPE mipsGet16(UNK_TYPE...);
/* 8008D3D0 global */ extern UNK_TYPE mipsGet8(UNK_TYPE...);
/* 8008D3D8 global */ extern UNK_TYPE mipsPut64(UNK_TYPE...);
/* 8008D3E0 global */ extern UNK_TYPE mipsPut32(UNK_TYPE...);
/* 8008D5E8 global */ extern UNK_TYPE mipsPut16(UNK_TYPE...);
/* 8008D5F0 global */ extern UNK_TYPE mipsPut8(UNK_TYPE...);
/* 8008D5F8 global */ extern UNK_TYPE mipsResetInterrupt(UNK_TYPE...);
/* 8008D69C global */ extern UNK_TYPE mipsSetInterrupt(UNK_TYPE...);
// ======================= disk.c =====================================================
/* 8008D788 global */ extern UNK_TYPE diskEvent(UNK_TYPE...);
/* 8008D924 local  */ // extern UNK_TYPE diskGetDrive64(UNK_TYPE...);
/* 8008D92C local  */ // extern UNK_TYPE diskGetDrive32(UNK_TYPE...);
/* 8008D964 local  */ // extern UNK_TYPE diskGetDrive16(UNK_TYPE...);
/* 8008D96C local  */ // extern UNK_TYPE diskGetDrive8(UNK_TYPE...);
/* 8008D974 local  */ // extern UNK_TYPE diskPutDrive64(UNK_TYPE...);
/* 8008D97C local  */ // extern UNK_TYPE diskPutDrive32(UNK_TYPE...);
/* 8008D9A8 local  */ // extern UNK_TYPE diskPutDrive16(UNK_TYPE...);
/* 8008D9B0 local  */ // extern UNK_TYPE diskPutDrive8(UNK_TYPE...);
/* 8008D9B8 local  */ // extern UNK_TYPE diskGetROM64(UNK_TYPE...);
/* 8008D9CC local  */ // extern UNK_TYPE diskGetROM32(UNK_TYPE...);
/* 8008D9DC local  */ // extern UNK_TYPE diskGetROM16(UNK_TYPE...);
/* 8008D9EC local  */ // extern UNK_TYPE diskGetROM8(UNK_TYPE...);
/* 8008D9FC local  */ // extern UNK_TYPE diskPutROM64(UNK_TYPE...);
/* 8008DA04 local  */ // extern UNK_TYPE diskPutROM32(UNK_TYPE...);
/* 8008DA0C local  */ // extern UNK_TYPE diskPutROM16(UNK_TYPE...);
/* 8008DA14 local  */ // extern UNK_TYPE diskPutROM8(UNK_TYPE...);
// ======================= flash.c ====================================================
/* 8008DA1C global */ extern UNK_TYPE flashEvent(UNK_TYPE...);
/* 8008DB3C local  */ // extern UNK_TYPE flashGet64(UNK_TYPE...);
/* 8008DB44 local  */ // extern UNK_TYPE flashGet32(UNK_TYPE...);
/* 8008DBE8 local  */ // extern UNK_TYPE flashGet16(UNK_TYPE...);
/* 8008DBF0 local  */ // extern UNK_TYPE flashGet8(UNK_TYPE...);
/* 8008DBF8 local  */ // extern UNK_TYPE flashPut64(UNK_TYPE...);
/* 8008DC00 local  */ // extern UNK_TYPE flashPut32(UNK_TYPE...);
/* 8008DED0 local  */ // extern UNK_TYPE flashPut16(UNK_TYPE...);
/* 8008DED8 local  */ // extern UNK_TYPE flashPut8(UNK_TYPE...);
/* 8008DEE0 global */ extern UNK_TYPE flashTransferFLASH(UNK_TYPE...);
/* 8008DFF4 global */ extern UNK_TYPE flashCopyFLASH(UNK_TYPE...);
// ======================= sram.c =====================================================
/* 8008E138 global */ extern UNK_TYPE sramEvent(UNK_TYPE...);
/* 8008E238 local  */ // extern UNK_TYPE sramGet64(UNK_TYPE...);
/* 8008E268 local  */ // extern UNK_TYPE sramGet32(UNK_TYPE...);
/* 8008E298 local  */ // extern UNK_TYPE sramGet16(UNK_TYPE...);
/* 8008E2C8 local  */ // extern UNK_TYPE sramGet8(UNK_TYPE...);
/* 8008E2F8 local  */ // extern UNK_TYPE sramPut64(UNK_TYPE...);
/* 8008E328 local  */ // extern UNK_TYPE sramPut32(UNK_TYPE...);
/* 8008E358 local  */ // extern UNK_TYPE sramPut16(UNK_TYPE...);
/* 8008E388 local  */ // extern UNK_TYPE sramPut8(UNK_TYPE...);
/* 8008E3B8 global */ extern UNK_TYPE sramTransferSRAM(UNK_TYPE...);
/* 8008E430 global */ extern UNK_TYPE sramCopySRAM(UNK_TYPE...);
// ======================= audio.c ====================================================
/* 8008E4A8 global */ extern UNK_TYPE audioEvent(UNK_TYPE...);
/* 8008E5C8 global */ extern UNK_TYPE audioEnable(UNK_TYPE...);
/* 8008E620 global */ extern UNK_TYPE audioGet64(UNK_TYPE...);
/* 8008E628 global */ extern UNK_TYPE audioGet32(UNK_TYPE...);
/* 8008E730 global */ extern UNK_TYPE audioGet16(UNK_TYPE...);
/* 8008E738 global */ extern UNK_TYPE audioGet8(UNK_TYPE...);
/* 8008E740 global */ extern UNK_TYPE audioPut64(UNK_TYPE...);
/* 8008E748 global */ extern UNK_TYPE audioPut32(UNK_TYPE...);
/* 8008E890 global */ extern UNK_TYPE audioPut16(UNK_TYPE...);
/* 8008E898 global */ extern UNK_TYPE audioPut8(UNK_TYPE...);
// ======================= video.c ====================================================
/* 8008E8A0 global */ extern UNK_TYPE videoEvent(UNK_TYPE...);
/* 8008E9F4 global */ extern UNK_TYPE videoForceRetrace(UNK_TYPE...);
/* 8008EA60 global */ extern UNK_TYPE videoGet64(UNK_TYPE...);
/* 8008EA68 global */ extern UNK_TYPE videoGet32(UNK_TYPE...);
/* 8008EB84 global */ extern UNK_TYPE videoGet16(UNK_TYPE...);
/* 8008EB8C global */ extern UNK_TYPE videoGet8(UNK_TYPE...);
/* 8008EB94 global */ extern UNK_TYPE videoPut64(UNK_TYPE...);
/* 8008EB9C global */ extern UNK_TYPE videoPut32(UNK_TYPE...);
/* 8008EE10 global */ extern UNK_TYPE videoPut16(UNK_TYPE...);
/* 8008EE18 global */ extern UNK_TYPE videoPut8(UNK_TYPE...);
// ======================= serial.c ===================================================
/* 8008EE20 global */ extern UNK_TYPE serialEvent(UNK_TYPE...);
/* 8008EF20 global */ extern UNK_TYPE serialGet64(UNK_TYPE...);
/* 8008EF28 global */ extern UNK_TYPE serialGet32(UNK_TYPE...);
/* 8008EF8C global */ extern UNK_TYPE serialGet16(UNK_TYPE...);
/* 8008EF94 global */ extern UNK_TYPE serialGet8(UNK_TYPE...);
/* 8008EF9C global */ extern UNK_TYPE serialPut64(UNK_TYPE...);
/* 8008EFA4 global */ extern UNK_TYPE serialPut32(UNK_TYPE...);
/* 8008F0E4 global */ extern UNK_TYPE serialPut16(UNK_TYPE...);
/* 8008F0EC global */ extern UNK_TYPE serialPut8(UNK_TYPE...);
// ======================= library.c ==================================================
/* 8008F0F4 global */ extern UNK_TYPE libraryEvent(UNK_TYPE...);
/* 8008F234 global */ extern UNK_TYPE libraryCall(UNK_TYPE...);
/* 8008F32C global */ extern UNK_TYPE libraryFunctionReplaced(UNK_TYPE...);
/* 8008F420 local  */ // extern UNK_TYPE librarySearch(UNK_TYPE...);
/* 8008F584 global */ extern UNK_TYPE libraryTestFunction(UNK_TYPE...);
/* 8008FB6C local  */ // extern UNK_TYPE libraryFindFunctions(UNK_TYPE...);
/* 8009007C local  */ // extern UNK_TYPE libraryFindVariables(UNK_TYPE...);
/* 800907B0 local  */ // extern UNK_TYPE libraryFindException(UNK_TYPE...);
/* 80090AB0 global */ extern UNK_TYPE zeldaLoadSZS_Exit(UNK_TYPE...);
/* 80090AC4 global */ extern UNK_TYPE zeldaLoadSZS_Entry(UNK_TYPE...);
/* 80090AD8 global */ extern UNK_TYPE osViSwapBuffer_Entry(UNK_TYPE...);
/* 80090B40 global */ extern UNK_TYPE dmaSoundRomHandler_ZELDA1(UNK_TYPE...);
/* 80090C68 global */ extern UNK_TYPE pictureSnap_Zelda2(UNK_TYPE...);
/* 80090C78 global */ extern UNK_TYPE starfoxCopy(UNK_TYPE...);
/* 80090DE0 global */ extern UNK_TYPE osEepromLongWrite(UNK_TYPE...);
/* 80090E8C global */ extern UNK_TYPE osEepromLongRead(UNK_TYPE...);
/* 80090F38 global */ extern UNK_TYPE osEepromWrite(UNK_TYPE...);
/* 80090FB0 global */ extern UNK_TYPE osEepromRead(UNK_TYPE...);
/* 80091028 global */ extern UNK_TYPE __osEepStatus(UNK_TYPE...);
/* 80091100 global */ extern UNK_TYPE osAiSetNextBuffer(UNK_TYPE...);
/* 8009120C global */ extern UNK_TYPE osAiSetFrequency(UNK_TYPE...);
/* 80091338 global */ extern UNK_TYPE guLookAtReflect(UNK_TYPE...);
/* 8009190C global */ extern UNK_TYPE guLookAtReflectF(UNK_TYPE...);
/* 80091E60 global */ extern UNK_TYPE guLookAtHilite(UNK_TYPE...);
/* 80092834 global */ extern UNK_TYPE guLookAtHiliteF(UNK_TYPE...);
/* 80093188 global */ extern UNK_TYPE guLookAt(UNK_TYPE...);
/* 800935A0 global */ extern UNK_TYPE guLookAtF(UNK_TYPE...);
/* 8009392C global */ extern UNK_TYPE guRotate(UNK_TYPE...);
/* 80093C78 global */ extern UNK_TYPE guRotateF(UNK_TYPE...);
/* 80093F88 global */ extern UNK_TYPE guTranslate(UNK_TYPE...);
/* 80094174 global */ extern UNK_TYPE guTranslateF(UNK_TYPE...);
/* 80094294 global */ extern UNK_TYPE guScale(UNK_TYPE...);
/* 80094480 global */ extern UNK_TYPE guScaleF(UNK_TYPE...);
/* 800945A8 global */ extern UNK_TYPE GenPerspective_1080(UNK_TYPE...);
/* 80094658 global */ extern UNK_TYPE guPerspective(UNK_TYPE...);
/* 8009491C global */ extern UNK_TYPE guPerspectiveF(UNK_TYPE...);
/* 80094B78 global */ extern UNK_TYPE guOrtho(UNK_TYPE...);
/* 80094E54 global */ extern UNK_TYPE guOrthoF(UNK_TYPE...);
/* 800950C4 global */ extern UNK_TYPE guMtxIdent(UNK_TYPE...);
/* 80095178 global */ extern UNK_TYPE guMtxIdentF(UNK_TYPE...);
/* 8009524C global */ extern UNK_TYPE guMtxF2L(UNK_TYPE...);
/* 80095454 global */ extern UNK_TYPE guMtxCatF(UNK_TYPE...);
/* 8009576C global */ extern UNK_TYPE osVirtualToPhysical(UNK_TYPE...);
/* 800957E0 global */ extern UNK_TYPE osPhysicalToVirtual(UNK_TYPE...);
/* 800957F0 global */ extern UNK_TYPE _memcpy(UNK_TYPE...);
/* 8009584C global */ extern UNK_TYPE _bcopy(UNK_TYPE...);
/* 800958A8 global */ extern UNK_TYPE _bzero(UNK_TYPE...);
/* 800958EC local  */ // extern UNK_TYPE __sinf(UNK_TYPE...);
/* 80095920 local  */ // extern UNK_TYPE __cosf(UNK_TYPE...);
/* 80095954 local  */ // extern UNK_TYPE __osSpSetStatus(UNK_TYPE...);
/* 800959A4 local  */ // extern UNK_TYPE __osRestoreInt(UNK_TYPE...);
/* 80095A30 local  */ // extern UNK_TYPE __osDisableInt(UNK_TYPE...);
/* 80095AC0 local  */ // extern UNK_TYPE osInvalICache(UNK_TYPE...);
/* 80095B48 local  */ // extern UNK_TYPE osGetMemSize(UNK_TYPE...);
/* 80095B9C local  */ // extern UNK_TYPE __osDispatchThread(UNK_TYPE...);
/* 80096140 local  */ // extern UNK_TYPE __osPopThread(UNK_TYPE...);
/* 80096214 local  */ // extern UNK_TYPE __osEnqueueThread(UNK_TYPE...);
/* 8009643C local  */ // extern UNK_TYPE __osEnqueueAndYield(UNK_TYPE...);
/* 80096728 local  */ // extern UNK_TYPE send_mesg(UNK_TYPE...);
/* 80096AB8 local  */ // extern UNK_TYPE __osException(UNK_TYPE...);
// ======================= peripheral.c ===============================================
/* 8009779C global */ extern UNK_TYPE peripheralEvent(UNK_TYPE...);
/* 800978A4 global */ extern UNK_TYPE peripheralGet64(UNK_TYPE...);
/* 800978AC global */ extern UNK_TYPE peripheralGet32(UNK_TYPE...);
/* 800979AC global */ extern UNK_TYPE peripheralGet16(UNK_TYPE...);
/* 800979B4 global */ extern UNK_TYPE peripheralGet8(UNK_TYPE...);
/* 800979BC global */ extern UNK_TYPE peripheralPut64(UNK_TYPE...);
/* 800979C4 global */ extern UNK_TYPE peripheralPut32(UNK_TYPE...);
/* 80097D48 global */ extern UNK_TYPE peripheralPut16(UNK_TYPE...);
/* 80097D50 global */ extern UNK_TYPE peripheralPut8(UNK_TYPE...);
/* 80097D58 local  */ // extern UNK_TYPE peripheralDMA_Complete(UNK_TYPE...);
// ======================= _frameGCNcc.c ==============================================
/* 80097D9C global */ extern UNK_TYPE SetTevStageTable(UNK_TYPE...);
/* 80097E5C global */ extern UNK_TYPE SetTevStages(UNK_TYPE...);
/* 800981E0 global */ extern UNK_TYPE SetNumTexGensChans(UNK_TYPE...);
/* 800983A0 local  */ // extern UNK_TYPE SetTableTevStages(UNK_TYPE...);
// ======================= _buildtev.c ================================================
/* 800986A4 global */ extern UNK_TYPE BuildCombineModeTev(UNK_TYPE...);
/* 80098AE0 global */ extern UNK_TYPE BuildCycle(UNK_TYPE...);
/* 80098BCC global */ extern UNK_TYPE SetupStage(UNK_TYPE...);
/* 8009B6BC local  */ // extern UNK_TYPE AddAlphaTevOrder(UNK_TYPE...);
/* 8009B7DC global */ extern UNK_TYPE SetAlpha(UNK_TYPE...);
/* 8009B914 global */ extern UNK_TYPE SetColor(UNK_TYPE...);
// ======================= PPCArch.c ==================================================
/* 8009BABC global */ extern UNK_TYPE PPCMfmsr(UNK_TYPE...);
/* 8009BAC4 global */ extern UNK_TYPE PPCMtmsr(UNK_TYPE...);
/* 8009BACC global */ extern UNK_TYPE PPCMfhid0(UNK_TYPE...);
/* 8009BAD4 global */ extern UNK_TYPE PPCMthid0(UNK_TYPE...);
/* 8009BADC global */ extern UNK_TYPE PPCMfl2cr(UNK_TYPE...);
/* 8009BAE4 global */ extern UNK_TYPE PPCMtl2cr(UNK_TYPE...);
/* 8009BAEC weak   */ // extern UNK_TYPE PPCMtdec(UNK_TYPE...);
/* 8009BAF4 global */ extern UNK_TYPE PPCSync(UNK_TYPE...);
/* 8009BAFC weak   */ // extern UNK_TYPE PPCHalt(UNK_TYPE...);
/* 8009BB10 global */ extern UNK_TYPE PPCMtmmcr0(UNK_TYPE...);
/* 8009BB18 global */ extern UNK_TYPE PPCMtmmcr1(UNK_TYPE...);
/* 8009BB20 global */ extern UNK_TYPE PPCMtpmc1(UNK_TYPE...);
/* 8009BB28 global */ extern UNK_TYPE PPCMtpmc2(UNK_TYPE...);
/* 8009BB30 global */ extern UNK_TYPE PPCMtpmc3(UNK_TYPE...);
/* 8009BB38 global */ extern UNK_TYPE PPCMtpmc4(UNK_TYPE...);
/* 8009BB40 global */ extern UNK_TYPE PPCMffpscr(UNK_TYPE...);
/* 8009BB60 global */ extern UNK_TYPE PPCMtfpscr(UNK_TYPE...);
/* 8009BB88 global */ extern UNK_TYPE PPCMfhid2(UNK_TYPE...);
/* 8009BB90 global */ extern UNK_TYPE PPCMthid2(UNK_TYPE...);
/* 8009BB98 global */ extern UNK_TYPE PPCMtwpar(UNK_TYPE...);
/* 8009BBA0 global */ extern UNK_TYPE PPCDisableSpeculation(UNK_TYPE...);
/* 8009BBC8 global */ extern UNK_TYPE PPCSetFpNonIEEEMode(UNK_TYPE...);
// ======================= OS.c =======================================================
/* 8009BBD0 global */ extern UNK_TYPE __OSFPRInit(UNK_TYPE...);
/* 8009BCF8 global */ extern u32 OSGetConsoleType(void);
/* 8009BD20 local  */ // extern UNK_TYPE ClearArena(UNK_TYPE...);
/* 8009BE48 local  */ // extern UNK_TYPE InquiryCallback(UNK_TYPE...);
/* 8009BE84 global */ extern void OSInit(void);
/* 8009C25C local  */ // extern UNK_TYPE OSExceptionInit(UNK_TYPE...);
/* 8009C4DC local  */ // extern UNK_TYPE __OSDBIntegrator(UNK_TYPE...);
/* 8009C500 local  */ // extern UNK_TYPE __OSDBJump(UNK_TYPE...);
/* 8009C504 global */ extern __OSExceptionHandler __OSSetExceptionHandler(__OSException exception,
                                                                          __OSExceptionHandler handler);
/* 8009C520 global */ extern __OSExceptionHandler __OSGetExceptionHandler(__OSException exception);
/* 8009C534 local  */ // extern UNK_TYPE OSExceptionVector(UNK_TYPE...);
/* 8009C5D0 global */ extern UNK_TYPE OSDefaultExceptionHandler(UNK_TYPE...);
/* 8009C628 global */ extern UNK_TYPE __OSPSInit(UNK_TYPE...);
/* 8009C67C global */ extern UNK_TYPE __OSGetDIConfig(UNK_TYPE...);
/* 8009C690 global */ extern void OSRegisterVersion(const char* id);
// ======================= OSAlarm.c ==================================================
/* 8009C6BC global */ extern UNK_TYPE OSInitAlarm(UNK_TYPE...);
/* 8009C714 global */ extern void OSCreateAlarm(OSAlarm* alarm);
/* 8009C724 local  */ // extern UNK_TYPE InsertAlarm(UNK_TYPE...);
/* 8009C974 global */ extern void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler);
/* 8009C9DC global */ extern void OSCancelAlarm(OSAlarm* alarm);
/* 8009CAF8 local  */ // extern UNK_TYPE DecrementerExceptionCallback(UNK_TYPE...);
/* 8009CD28 local  */ // extern UNK_TYPE DecrementerExceptionHandler(UNK_TYPE...);
/* 8009CD78 local  */ // extern UNK_TYPE OnReset(UNK_TYPE...);
// ======================= OSAlloc.c ==================================================
/* 8009CE18 local  */ // extern UNK_TYPE DLInsert(UNK_TYPE...);
/* 8009CEC4 global */ extern void* OSAllocFromHeap(OSHeapHandle heap, u32 size);
/* 8009CFC0 global */ extern void OSFreeToHeap(OSHeapHandle heap, void* ptr);
/* 8009D03C global */ extern OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
/* 8009D04C global */ extern void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps);
/* 8009D0BC global */ extern OSHeapHandle OSCreateHeap(void* start, void* end);
/* 8009D128 global */ extern s32 OSCheckHeap(OSHeapHandle heap);
// ======================= OSArena.c ==================================================
/* 8009D488 global */ extern void* OSGetArenaHi(void);
/* 8009D490 global */ extern void* OSGetArenaLo(void);
/* 8009D498 global */ extern void OSSetArenaHi(void* newHi);
/* 8009D4A0 global */ extern void OSSetArenaLo(void* newLo);
// ======================= OSAudioSystem.c ============================================
/* 8009D4A8 global */ extern UNK_TYPE __OSInitAudioSystem(UNK_TYPE...);
/* 8009D664 global */ extern UNK_TYPE __OSStopAudioSystem(UNK_TYPE...);
// ======================= OSCache.c ==================================================
/* 8009D73C global */ extern void DCEnable(void);
/* 8009D750 global */ extern void DCInvalidateRange(void* addr, u32 nBytes);
/* 8009D77C global */ extern void DCFlushRange(void* addr, u32 nBytes);
/* 8009D7AC global */ extern void DCStoreRange(void* addr, u32 nBytes);
/* 8009D7DC global */ extern void DCFlushRangeNoSync(void* addr, u32 nBytes);
/* 8009D808 global */ extern void DCZeroRange(void* addr, u32 nBytes);
/* 8009D834 global */ extern void ICInvalidateRange(void* addr, u32 nBytes);
/* 8009D868 global */ extern void ICFlashInvalidate(void);
/* 8009D878 global */ extern void ICEnable(void);
/* 8009D88C local  */ // extern UNK_TYPE __LCEnable(UNK_TYPE...);
/* 8009D958 global */ extern void LCEnable(void);
/* 8009D990 global */ extern void LCDisable(void);
/* 8009D9B8 global */ extern void LCStoreBlocks(void* destAddr, void* srcTag, u32 numBlocks);
/* 8009D9DC global */ extern u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes);
/* 8009DA88 global */ extern void LCQueueWait(u32 len);
/* 8009DA9C global */ extern void L2GlobalInvalidate(void);
/* 8009DB34 global */ extern UNK_TYPE DMAErrorHandler(UNK_TYPE...);
/* 8009DC94 global */ extern UNK_TYPE __OSCacheInit(UNK_TYPE...);
// ======================= OSContext.c ================================================
/* 8009DD88 local  */ // extern UNK_TYPE __OSLoadFPUContext(UNK_TYPE...);
/* 8009DEAC local  */ // extern UNK_TYPE __OSSaveFPUContext(UNK_TYPE...);
/* 8009DFD4 global */ extern void OSSaveFPUContext(OSContext* context);
/* 8009DFDC global */ extern void OSSetCurrentContext(OSContext* context);
/* 8009E038 global */ extern OSContext* OSGetCurrentContext(void);
/* 8009E044 global */ extern u32 OSSaveContext(OSContext* context);
/* 8009E0C4 global */ extern void OSLoadContext(OSContext* context);
/* 8009E19C global */ extern u32 OSGetStackPointer(void);
/* 8009E1A4 global */ extern void OSClearContext(OSContext* context);
/* 8009E1C8 global */ extern void OSInitContext(OSContext* context, u32 pc, u32 sp);
/* 8009E284 global */ extern void OSDumpContext(OSContext* context);
/* 8009E52C local  */ // extern UNK_TYPE OSSwitchFPUContext(UNK_TYPE...);
/* 8009E5B0 global */ extern UNK_TYPE __OSContextInit(UNK_TYPE...);
/* 8009E5F8 weak   */ // extern UNK_TYPE OSReport(UNK_TYPE...);
// ======================= OSError.c ==================================================
/* 8009E678 weak   */ // extern UNK_TYPE OSPanic(UNK_TYPE...);
/* 8009E7A4 global */ extern OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler);
/* 8009E9BC global */ extern UNK_TYPE __OSUnhandledException(UNK_TYPE...);
// ======================= OSFont.c ===================================================
/* 8009ECA4 global */ extern u16 OSGetFontEncode(void);
// ======================= OSInterrupt.c ==============================================
/* 8009ECFC global */ extern BOOL OSDisableInterrupts(void);
/* 8009ED10 global */ extern BOOL OSEnableInterrupts(void);
/* 8009ED24 global */ extern BOOL OSRestoreInterrupts(BOOL level);
/* 8009ED48 global */ extern __OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt interrupt,
                                                                          __OSInterruptHandler handler);
/* 8009ED64 global */ extern __OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt interrupt);
/* 8009ED78 global */ extern UNK_TYPE __OSInterruptInit(UNK_TYPE...);
/* 8009EDEC local  */ // extern OSInterruptMask OSSetInterruptMask(OSInterruptMask mask);
/* 8009F0C4 global */ extern OSInterruptMask __OSMaskInterrupts(OSInterruptMask mask);
/* 8009F14C global */ extern OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask mask);
/* 8009F1D4 global */ extern void __OSDispatchInterrupt(__OSException exception, OSContext* context);
/* 8009F518 local  */ // extern UNK_TYPE ExternalInterruptHandler(UNK_TYPE...);
// ======================= OSLink.c ===================================================
/* 8009F568 global */ extern UNK_TYPE __OSModuleInit(UNK_TYPE...);
// ======================= OSMessage.c ================================================
/* 8009F580 global */ extern void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* msgArray, s32 msgCount);
/* 8009F5E0 global */ extern BOOL OSSendMessage(OSMessageQueue* mq, OSMessage msg, s32 flags);
/* 8009F6A8 global */ extern BOOL OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, s32 flags);
// ======================= OSMemory.c =================================================
/* 8009F784 local  */ // extern UNK_TYPE OnReset(UNK_TYPE...);
/* 8009F7C0 local  */ // extern UNK_TYPE MEMIntrruptHandler(UNK_TYPE...);
/* 8009F82C local  */ // extern UNK_TYPE Config24MB(UNK_TYPE...);
/* 8009F8AC local  */ // extern UNK_TYPE Config48MB(UNK_TYPE...);
/* 8009F92C local  */ // extern UNK_TYPE RealMode(UNK_TYPE...);
/* 8009F944 global */ extern UNK_TYPE __OSInitMemoryProtection(UNK_TYPE...);
// ======================= OSMutex.c ==================================================
/* 8009FA5C global */ extern UNK_TYPE __OSUnlockAllMutex(UNK_TYPE...);
// ======================= OSReboot.c =================================================
/* 8009FACC local  */ // extern UNK_TYPE Run(UNK_TYPE...);
/* 8009FADC local  */ // extern UNK_TYPE Callback(UNK_TYPE...);
/* 8009FAE8 global */ extern UNK_TYPE __OSReboot(UNK_TYPE...);
// ======================= OSReset.c ==================================================
/* 8009FE28 global */ extern void OSRegisterResetFunction(OSResetFunctionInfo* info);
/* 8009FEAC local  */ // extern UNK_TYPE Reset(UNK_TYPE...);
/* 8009FF1C global */ extern UNK_TYPE __OSDoHotReset(UNK_TYPE...);
/* 8009FF1C global */ extern void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu);
/* 800A021C global */ extern u32 OSGetResetCode(void);
// ======================= OSResetSW.c ================================================
/* 800A024C global */ extern UNK_TYPE __OSResetSWInterruptHandler(UNK_TYPE...);
/* 800A0340 global */ extern BOOL OSGetResetButtonState(void);
// ======================= OSRtc.c ====================================================
/* 800A05D8 local  */ // extern UNK_TYPE WriteSramCallback(UNK_TYPE...);
/* 800A0638 local  */ // extern UNK_TYPE WriteSram(UNK_TYPE...);
/* 800A0750 global */ extern UNK_TYPE __OSInitSram(UNK_TYPE...);
/* 800A088C global */ extern UNK_TYPE __OSLockSram(UNK_TYPE...);
/* 800A08E8 global */ extern UNK_TYPE __OSLockSramEx(UNK_TYPE...);
/* 800A0944 local  */ // extern UNK_TYPE UnlockSram(UNK_TYPE...);
/* 800A0C80 global */ extern UNK_TYPE __OSUnlockSram(UNK_TYPE...);
/* 800A0CA4 global */ extern UNK_TYPE __OSUnlockSramEx(UNK_TYPE...);
/* 800A0CC8 global */ extern UNK_TYPE __OSSyncSram(UNK_TYPE...);
/* 800A0CD8 global */ extern UNK_TYPE OSGetSoundMode(UNK_TYPE...);
/* 800A0D58 global */ extern UNK_TYPE OSSetSoundMode(UNK_TYPE...);
/* 800A0DFC global */ extern UNK_TYPE OSGetWirelessID(UNK_TYPE...);
/* 800A0E80 global */ extern UNK_TYPE OSSetWirelessID(UNK_TYPE...);
/* 800A0F2C global */ extern UNK_TYPE OSGetGbsMode(UNK_TYPE...);
/* 800A0F9C global */ extern UNK_TYPE OSSetGbsMode(UNK_TYPE...);
// ======================= OSSync.c ===================================================
/* 800A1054 local  */ // extern UNK_TYPE SystemCallVector(UNK_TYPE...);
/* 800A1074 global */ extern UNK_TYPE __OSInitSystemCall(UNK_TYPE...);
// ======================= OSThread.c =================================================
/* 800A10D8 local  */ // extern UNK_TYPE DefaultSwitchThreadCallback(UNK_TYPE...);
/* 800A10DC global */ extern UNK_TYPE __OSThreadInit(UNK_TYPE...);
/* 800A1234 global */ extern void OSInitThreadQueue(OSThreadQueue* queue);
/* 800A1244 global */ extern OSThread* OSGetCurrentThread(void);
/* 800A1250 global */ extern s32 OSDisableScheduler(void);
/* 800A1290 global */ extern s32 OSEnableScheduler(void);
/* 800A12D0 local  */ // extern UNK_TYPE UnsetRun(UNK_TYPE...);
/* 800A1338 global */ extern UNK_TYPE __OSGetEffectivePriority(UNK_TYPE...);
/* 800A1374 local  */ // extern UNK_TYPE SetEffectivePriority(UNK_TYPE...);
/* 800A1534 local  */ // extern UNK_TYPE SelectThread(UNK_TYPE...);
/* 800A175C global */ extern UNK_TYPE __OSReschedule(UNK_TYPE...);
/* 800A178C global */ extern BOOL OSCreateThread(OSThread* thread, void* (*func)(void*), void* param, void* stack,
                                                 u32 stackSize, OSPriority priority, u16 attr);
/* 800A1974 global */ extern void OSExitThread(void* val);
/* 800A1A58 global */ extern void OSCancelThread(OSThread* thread);
/* 800A1C14 global */ extern s32 OSResumeThread(OSThread* thread);
/* 800A1E9C global */ extern s32 OSSuspendThread(OSThread* thread);
/* 800A200C global */ extern void OSSleepThread(OSThreadQueue* queue);
/* 800A20F8 global */ extern void OSWakeupThread(OSThreadQueue* queue);
/* 800A21FC global */ extern void OSClearStack(u8 val);
// ======================= OSTime.c ===================================================
/* 800A22A8 global */ extern OSTime OSGetTime(void);
/* 800A22C0 global */ extern OSTick OSGetTick(void);
/* 800A22C8 global */ extern UNK_TYPE __OSGetSystemTime(UNK_TYPE...);
/* 800A232C local  */ // extern UNK_TYPE GetDates(UNK_TYPE...);
/* 800A24C8 global */ extern void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td);
// ======================= __start.c ==================================================
/* 80003100 local  */ // extern UNK_TYPE __check_pad3(UNK_TYPE...);
/* 80003140 local  */ // extern UNK_TYPE __set_debug_bba(UNK_TYPE...);
/* 8000314C local  */ // extern UNK_TYPE __get_debug_bba(UNK_TYPE...);
/* 80003154 weak   */ // extern UNK_TYPE __start(UNK_TYPE...);
/* 800032B0 local  */ // extern UNK_TYPE __init_registers(UNK_TYPE...);
/* 80003340 local  */ // extern UNK_TYPE __init_data(UNK_TYPE...);
// ======================= __ppc_eabi_init.cpp ========================================
/* 80003400 global */ extern UNK_TYPE __init_hardware(UNK_TYPE...);
/* 80003424 global */ extern UNK_TYPE __flush_cache(UNK_TYPE...);
/* 800A26CC weak   */ // extern UNK_TYPE InitMetroTRK_BBA(UNK_TYPE...);
/* 800A26D0 global */ extern UNK_TYPE __init_user(UNK_TYPE...);
/* 800A26F0 local  */ // extern UNK_TYPE __init_cpp(UNK_TYPE...);
/* 800A2744 global */ extern UNK_TYPE _ExitProcess(UNK_TYPE...);
// ======================= EXIBios.c ==================================================
/* 800A2764 local  */ // extern UNK_TYPE SetExiInterruptMask(UNK_TYPE...);
/* 800A2858 global */ extern UNK_TYPE EXIImm(UNK_TYPE...);
/* 800A2AB4 global */ extern UNK_TYPE EXIImmEx(UNK_TYPE...);
/* 800A2B54 global */ extern UNK_TYPE EXIDma(UNK_TYPE...);
/* 800A2C40 global */ extern UNK_TYPE EXISync(UNK_TYPE...);
/* 800A2E8C global */ extern UNK_TYPE EXIClearInterrupts(UNK_TYPE...);
/* 800A2ED4 global */ extern UNK_TYPE EXISetExiCallback(UNK_TYPE...);
/* 800A2F50 local  */ // extern UNK_TYPE __EXIProbe(UNK_TYPE...);
/* 800A30C4 global */ extern BOOL EXIProbe(s32 chan);
/* 800A3144 global */ extern s32 EXIProbeEx(s32 chan);
/* 800A31F8 global */ extern UNK_TYPE EXIAttach(UNK_TYPE...);
/* 800A3304 global */ extern UNK_TYPE EXIDetach(UNK_TYPE...);
/* 800A33C0 global */ extern UNK_TYPE EXISelect(UNK_TYPE...);
/* 800A34EC global */ extern UNK_TYPE EXIDeselect(UNK_TYPE...);
/* 800A35FC local  */ // extern UNK_TYPE EXIIntrruptHandler(UNK_TYPE...);
/* 800A36C4 local  */ // extern UNK_TYPE TCIntrruptHandler(UNK_TYPE...);
/* 800A38DC local  */ // extern UNK_TYPE EXTIntrruptHandler(UNK_TYPE...);
/* 800A39AC global */ extern UNK_TYPE EXIInit(UNK_TYPE...);
/* 800A3B80 global */ extern UNK_TYPE EXILock(UNK_TYPE...);
/* 800A3C74 global */ extern UNK_TYPE EXIUnlock(UNK_TYPE...);
/* 800A3D50 global */ extern UNK_TYPE EXIGetState(UNK_TYPE...);
/* 800A3D68 local  */ // extern UNK_TYPE UnlockedHandler(UNK_TYPE...);
/* 800A3D90 global */ extern UNK_TYPE EXIGetID(UNK_TYPE...);
// ======================= EXIUart.c ==================================================
/* 800A4140 local  */ // extern UNK_TYPE ProbeBarnacle(UNK_TYPE...);
/* 800A42CC global */ extern UNK_TYPE __OSEnableBarnacle(UNK_TYPE...);
/* 800A4488 global */ extern UNK_TYPE InitializeUART(UNK_TYPE...);
/* 800A44F8 global */ extern UNK_TYPE ReadUARTN(UNK_TYPE...);
/* 800A4500 global */ extern UNK_TYPE WriteUARTN(UNK_TYPE...);
// ======================= SIBios.c ===================================================
/* 800A471C global */ extern UNK_TYPE SIBusy(UNK_TYPE...);
/* 800A473C global */ extern UNK_TYPE SIIsChanBusy(UNK_TYPE...);
/* 800A4778 local  */ // extern UNK_TYPE CompleteTransfer(UNK_TYPE...);
/* 800A4A74 local  */ // extern UNK_TYPE SIInterruptHandler(UNK_TYPE...);
/* 800A4DB8 local  */ // extern UNK_TYPE SIEnablePollingInterrupt(UNK_TYPE...);
/* 800A4E50 global */ extern UNK_TYPE SIRegisterPollingHandler(UNK_TYPE...);
/* 800A4F1C global */ extern UNK_TYPE SIUnregisterPollingHandler(UNK_TYPE...);
/* 800A5010 global */ extern UNK_TYPE SIInit(UNK_TYPE...);
/* 800A50C4 local  */ // extern UNK_TYPE __SITransfer(UNK_TYPE...);
/* 800A52D0 global */ extern UNK_TYPE SIGetStatus(UNK_TYPE...);
/* 800A534C global */ extern UNK_TYPE SISetCommand(UNK_TYPE...);
/* 800A5360 global */ extern UNK_TYPE SITransferCommands(UNK_TYPE...);
/* 800A5370 global */ extern UNK_TYPE SISetXY(UNK_TYPE...);
/* 800A53DC global */ extern UNK_TYPE SIEnablePolling(UNK_TYPE...);
/* 800A5478 global */ extern UNK_TYPE SIDisablePolling(UNK_TYPE...);
/* 800A54E4 local  */ // extern UNK_TYPE SIGetResponseRaw(UNK_TYPE...);
/* 800A55B8 global */ extern UNK_TYPE SIGetResponse(UNK_TYPE...);
/* 800A567C local  */ // extern UNK_TYPE AlarmHandler(UNK_TYPE...);
/* 800A5708 global */ extern UNK_TYPE SITransfer(UNK_TYPE...);
/* 800A5874 local  */ // extern UNK_TYPE GetTypeCallback(UNK_TYPE...);
/* 800A5B0C global */ extern UNK_TYPE SIGetType(UNK_TYPE...);
/* 800A5CD0 global */ extern UNK_TYPE SIGetTypeAsync(UNK_TYPE...);
// ======================= SISamplingRate.c ===========================================
/* 800A5E0C global */ extern void SISetSamplingRate(u32 msec);
/* 800A5EF0 global */ extern void SIRefreshSamplingRate(void);
// ======================= vi.c =======================================================
/* 800A5F14 local  */ // extern UNK_TYPE __VIRetraceHandler(UNK_TYPE...);
/* 800A6188 global */ extern VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback);
/* 800A61CC local  */ // extern UNK_TYPE getTiming(UNK_TYPE...);
/* 800A626C global */ extern UNK_TYPE __VIInit(UNK_TYPE...);
/* 800A646C global */ extern void VIInit(void);
/* 800A691C global */ extern void VIWaitForRetrace(void);
/* 800A6970 local  */ // extern UNK_TYPE setFbbRegs(UNK_TYPE...);
/* 800A6C44 local  */ // extern UNK_TYPE setVerticalRegs(UNK_TYPE...);
/* 800A6DE4 global */ extern void VIConfigure(const GXRenderModeObj* rm);
/* 800A760C global */ extern void VIFlush(void);
/* 800A773C global */ extern void VISetNextFrameBuffer(void* fb);
/* 800A77A8 global */ extern void VISetBlack(BOOL black);
/* 800A7824 local  */ // extern UNK_TYPE GetCurrentDisplayPosition(UNK_TYPE...);
/* 800A7860 local  */ // extern UNK_TYPE getCurrentFieldEvenOdd(UNK_TYPE...);
/* 800A78C8 global */ extern u32 VIGetNextField(void);
/* 800A7964 global */ extern u32 VIGetCurrentLine(void);
/* 800A79FC global */ extern u32 VIGetTvFormat(void);
/* 800A7A64 global */ extern UNK_TYPE __VIDisplayPositionToXY(UNK_TYPE...);
/* 800A7C80 global */ extern UNK_TYPE __VIGetCurrentPosition(UNK_TYPE...);
// ======================= db.c =======================================================
/* 800A7CE0 global */ extern UNK_TYPE DBInit(UNK_TYPE...);
/* 800A7D08 global */ extern UNK_TYPE __DBExceptionDestinationAux(UNK_TYPE...);
/* 800A7D50 global */ extern void __DBExceptionDestination(void);
/* 800A7D60 global */ extern BOOL __DBIsExceptionMarked(__OSException exception);
/* 800A7D7C global */ extern void DBPrintf(char* str, ...);
// ======================= mtx.c ======================================================
/* 800A7DCC global */ extern void PSMTXIdentity(Mtx m);
/* 800A7DF8 global */ extern void SMTXConcat(const Mtx a, const Mtx b, Mtx ab);
/* 800A7EC4 global */ extern void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
/* 800A7EF8 global */ extern void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
/* 800A7F44 global */ extern void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
/* 800A7F6C global */ extern void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
// ======================= mtxvec.c ===================================================
/* 800A7FC4 global */ extern void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
// ======================= mtx44.c ====================================================
/* 800A8018 global */ extern void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);
/* 800A80E8 global */ extern void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
/* 800A8180 global */ extern void PSMTX44Concat(const Mtx44 a, const Mtx44 b, Mtx44 ab);
// ======================= GXInit.c ===================================================
/* 800A8284 local  */ // extern UNK_TYPE __GXDefaultTexRegionCallback(UNK_TYPE...);
/* 800A8380 local  */ // extern UNK_TYPE __GXDefaultTlutRegionCallback(UNK_TYPE...);
/* 800A83A4 local  */ // extern UNK_TYPE __GXShutdown(UNK_TYPE...);
/* 800A8534 global */ extern GXFifoObj* GXInit(void* base, u32 size);
/* 800A8CCC global */ extern UNK_TYPE __GXInitGX(UNK_TYPE...);
// ======================= GXFifo.c ===================================================
/* 800A9604 local  */ // extern UNK_TYPE GXCPInterruptHandler(UNK_TYPE...);
/* 800A9738 global */ extern void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size);
/* 800A97A4 global */ extern void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr);
/* 800A9814 global */ extern void GXInitFifoLimits(GXFifoObj* fifo, u32 hiWaterMark, u32 loWaterMark);
/* 800A9820 global */ extern void GXSetCPUFifo(const GXFifoObj* fifo);
/* 800A9948 global */ extern void GXSetGPFifo(const GXFifoObj* fifo);
/* 800A9AC0 global */ extern void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle,
                                                GXBool* brkpt);
/* 800A9B10 global */ extern void* GXGetFifoBase(const GXFifoObj* fifo);
/* 800A9B18 global */ extern u32 GXGetFifoSize(const GXFifoObj* fifo);
/* 800A9B20 global */ extern GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb);
/* 800A9B64 global */ extern UNK_TYPE __GXFifoInit(UNK_TYPE...);
/* 800A9BB0 local  */ // extern UNK_TYPE __GXFifoReadEnable(UNK_TYPE...);
/* 800A9BD4 local  */ // extern UNK_TYPE __GXFifoReadDisable(UNK_TYPE...);
/* 800A9BF8 local  */ // extern UNK_TYPE __GXFifoLink(UNK_TYPE...);
/* 800A9C2C local  */ // extern UNK_TYPE __GXWriteFifoIntEnable(UNK_TYPE...);
/* 800A9C5C local  */ // extern UNK_TYPE __GXWriteFifoIntReset(UNK_TYPE...);
/* 800A9C8C global */ extern UNK_TYPE __GXCleanGPFifo(UNK_TYPE...);
/* 800A9D8C global */ extern GXBool GXGetCPUFifo(GXFifoObj* fifo);
/* 800A9D94 global */ extern GXBool GXGetGPFifo(GXFifoObj* fifo);
// ======================= GXAttr.c ===================================================
/* 800A9D9C global */ extern void GXSetVtxDesc(GXAttr attr, GXAttrType type);
/* 800AA008 global */ extern UNK_TYPE __GXSetVCD(UNK_TYPE...);
/* 800AA0C4 global */ extern UNK_TYPE __GXCalculateVLim(UNK_TYPE...);
/* 800AA1E8 global */ extern void GXClearVtxDesc(void);
/* 800AA220 global */ extern void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type,
                                                  u8 frac);
/* 800AA47C global */ extern void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, const GXVtxAttrFmtList* list);
/* 800AA6FC global */ extern UNK_TYPE __GXSetVAT(UNK_TYPE...);
/* 800AA798 global */ extern void GXSetArray(GXAttr attr, const void* base_ptr, u8 stride);
/* 800AA824 global */ extern void GXInvalidateVtxCache(void);
/* 800AA834 global */ extern void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param,
                                                    u32 mtx, GXBool normalize, u32 postmtx);
/* 800AAAB4 global */ extern void GXSetNumTexGens(u8 nTexGens);
// ======================= GXMisc.c ===================================================
/* 800AAAF0 global */ extern void GXSetMisc(GXMiscToken token, u32 val);
/* 800AAB84 global */ extern void GXFlush(void);
/* 800AABE0 global */ extern UNK_TYPE __GXAbort(UNK_TYPE...);
/* 800AAD4C global */ extern void GXAbortFrame(void);
/* 800AAEBC global */ extern void GXSetDrawSync(u16 token);
/* 800AAF70 global */ extern u16 GXReadDrawSync(void);
/* 800AAF7C global */ extern void GXSetDrawDone(void);
/* 800AB014 global */ extern void GXDrawDone(void);
/* 800AB094 global */ extern void GXPixModeSync(void);
/* 800AB0B8 global */ extern void GXPokeAlphaMode(GXCompare func, u8 threshold);
/* 800AB0CC global */ extern void GXPokeAlphaRead(GXAlphaReadMode mode);
/* 800AB0EC global */ extern void GXPokeAlphaUpdate(GXBool update_enable);
/* 800AB104 global */ extern void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor,
                                                  GXLogicOp op);
/* 800AB168 global */ extern void GXPokeColorUpdate(GXBool update_enable);
/* 800AB180 global */ extern void GXPokeDstAlpha(GXBool enable, u8 alpha);
/* 800AB1A4 global */ extern void GXPokeDither(GXBool dither);
/* 800AB1BC global */ extern void GXPokeZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
/* 800AB1DC global */ extern GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback cb);
/* 800AB220 local  */ // extern UNK_TYPE GXTokenInterruptHandler(UNK_TYPE...);
/* 800AB2A8 global */ extern GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb);
/* 800AB2EC local  */ // extern UNK_TYPE GXFinishInterruptHandler(UNK_TYPE...);
/* 800AB36C global */ extern UNK_TYPE __GXPEInit(UNK_TYPE...);
// ======================= GXGeometry.c ===============================================
/* 800AB3E0 global */ extern UNK_TYPE __GXSetDirtyState(UNK_TYPE...);
/* 800AB460 global */ extern void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
/* 800AB530 global */ extern UNK_TYPE __GXSendFlushPrim(UNK_TYPE...);
/* 800AB5B8 global */ extern void GXSetLineWidth(u8 width, GXTexOffset texOffsets);
/* 800AB5F8 global */ extern void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets);
/* 800AB638 global */ extern void GXEnableTexOffsets(GXTexCoordID coord, GXBool line_enable, GXBool point_enable);
/* 800AB680 global */ extern void GXSetCullMode(GXCullMode mode);
/* 800AB6C4 global */ extern void GXSetCoPlanar(GXBool enable);
/* 800AB6F8 global */ extern UNK_TYPE __GXSetGenMode(UNK_TYPE...);
// ======================= GXFrameBuf.c ===============================================
/* 800AB71C global */ extern void GXAdjustForOverscan(const GXRenderModeObj* rmin, GXRenderModeObj* rmout, u16 hor,
                                                      u16 ver);
/* 800AB860 global */ extern void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht);
/* 800AB8DC global */ extern void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
/* 800AB958 global */ extern void GXSetDispCopyDst(u16 wd, u16 ht);
/* 800AB98C global */ extern void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
/* 800ABABC global */ extern void GXSetDispCopyFrame2Field(GXCopyMode mode);
/* 800ABAE0 global */ extern void GXSetCopyClamp(GXFBClamp clamp);
/* 800ABB38 global */ extern f32 GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight);
/* 800ABD70 global */ extern u32 GXSetDispCopyYScale(f32 vscale);
/* 800ABE3C global */ extern void GXSetCopyClear(GXColor clear_clr, u32 clear_z);
/* 800ABEB4 global */ extern void GXSetCopyFilter(GXBool aa, const u8 sample_pattern[12][2], GXBool vf,
                                                  const u8 vfilter[7]);
/* 800AC0BC global */ extern void GXSetDispCopyGamma(GXGamma gamma);
/* 800AC0D0 global */ extern void GXCopyDisp(void* dest, GXBool clear);
/* 800AC238 global */ extern void GXCopyTex(void* dest, GXBool clear);
/* 800AC3C4 global */ extern void GXClearBoundingBox(void);
// ======================= GXLight.c ==================================================
/* 800AC3FC global */ extern void GXSetChanAmbColor(GXChannelID chan, GXColor amb_color);
/* 800AC4EC global */ extern void GXSetChanMatColor(GXChannelID chan, GXColor mat_color);
/* 800AC5DC global */ extern void GXSetNumChans(u8 nChans);
/* 800AC618 global */ extern void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src,
                                                u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
// ======================= GXTexture.c ================================================
/* 800AC6D0 global */ extern UNK_TYPE __GetImageTileCount(UNK_TYPE...);
/* 800AC798 global */ extern void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format,
                                               GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXBool mipmap);
/* 800AC9E4 global */ extern void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
                                                 GXCITexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t,
                                                 GXBool mipmap, u32 tlut_name);
/* 800ACA2C global */ extern void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
                                                  f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
                                                  GXBool do_edge_lod, GXAnisotropy max_aniso);
/* 800ACB90 global */ extern void* GXGetTexObjData(const GXTexObj* tex_obj);
/* 800ACB9C global */ extern GXTexFmt GXGetTexObjFmt(const GXTexObj* tex_obj);
/* 800ACBA4 global */ extern GXBool GXGetTexObjMipMap(const GXTexObj* tex_obj);
/* 800ACBBC global */ extern void GXLoadTexObjPreLoaded(const GXTexObj* obj, const GXTexRegion* region, GXTexMapID id);
/* 800ACD38 global */ extern void GXLoadTexObj(const GXTexObj* obj, GXTexMapID id);
/* 800ACD8C global */ extern void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt, u16 n_entries);
/* 800ACDC4 global */ extern void GXLoadTlut(const GXTlutObj* tlut_obj, u32 tlut_name);
/* 800ACE5C global */ extern void GXInitTexCacheRegion(GXTexRegion* region, GXBool is_32b_mipmap, u32 tmem_even,
                                                       GXTexCacheSize size_even, u32 tmem_odd, GXTexCacheSize size_odd);
/* 800ACF50 global */ extern void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, GXTlutSize tlut_size);
/* 800ACF88 global */ extern void GXInvalidateTexAll(void);
/* 800ACFD0 global */ extern GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback f);
/* 800ACFE4 global */ extern GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback f);
/* 800ACFF8 local  */ // extern UNK_TYPE __SetSURegs(UNK_TYPE...);
/* 800AD098 global */ extern UNK_TYPE __GXSetSUTexRegs(UNK_TYPE...);
/* 800AD214 global */ extern UNK_TYPE __GXSetTmemConfig(UNK_TYPE...);
// ======================= GXBump.c ===================================================
/* 800AD568 global */ extern void GXSetTevIndirect(GXTevStageID tev_stage, GXIndTexStageID ind_stage,
                                                   GXIndTexFormat format, GXIndTexBiasSel bias_sel,
                                                   GXIndTexMtxID matrix_sel, GXIndTexWrap wrap_s, GXIndTexWrap wrap_t,
                                                   GXBool add_prev, GXBool ind_lod, GXIndTexAlphaSel alpha_sel);
/* 800AD5D4 global */ extern void GXSetIndTexCoordScale(GXIndTexStageID ind_state, GXIndTexScale scale_s,
                                                        GXIndTexScale scale_t);
/* 800AD718 global */ extern void GXSetNumIndStages(u8 nIndStages);
/* 800AD73C global */ extern void GXSetTevDirect(GXTevStageID tev_stage);
/* 800AD784 global */ extern UNK_TYPE __GXUpdateBPMask(UNK_TYPE...);
/* 800AD788 global */ extern void __GXSetIndirectMask(u32 mask);
/* 800AD7B8 global */ extern UNK_TYPE __GXFlushTextureState(UNK_TYPE...);
// ======================= GXTev.c ====================================================
/* 800AD7DC global */ extern void GXSetTevOp(GXTevStageID id, GXTevMode mode);
/* 800AD868 global */ extern void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c,
                                                  GXTevColorArg d);
/* 800AD8AC global */ extern void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c,
                                                  GXTevAlphaArg d);
/* 800AD8F0 global */ extern void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale,
                                                  GXBool clamp, GXTevRegID out_reg);
/* 800AD958 global */ extern void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale,
                                                  GXBool clamp, GXTevRegID out_reg);
/* 800AD9C0 global */ extern void GXSetTevColor(GXTevRegID id, GXColor color);
/* 800ADA3C global */ extern void GXSetTevColorS10(GXTevRegID id, GXColorS10 color);
/* 800ADAB8 global */ extern void GXSetTevKColor(GXTevKColorID id, GXColor color);
/* 800ADB2C global */ extern void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel);
/* 800ADB88 global */ extern void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel);
/* 800ADBE4 global */ extern void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
/* 800ADC2C global */ extern void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red, GXTevColorChan green,
                                                        GXTevColorChan blue, GXTevColorChan alpha);
/* 800ADCAC global */ extern void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
/* 800ADCF0 global */ extern void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias);
/* 800ADD7C global */ extern void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map,
                                                GXChannelID color);
/* 800ADF18 global */ extern void GXSetNumTevStages(u8 nStages);
// ======================= GXPixel.c ==================================================
/* 800ADF40 global */ extern void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
/* 800AE164 global */ extern void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, const f32 projmtx[4][4]);
/* 800AE314 global */ extern void GXSetFogRangeAdj(GXBool enable, u16 center, const GXFogAdjTable* table);
/* 800AE438 global */ extern void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor,
                                                 GXLogicOp op);
/* 800AE48C global */ extern void GXSetColorUpdate(GXBool update_enable);
/* 800AE4B8 global */ extern void GXSetAlphaUpdate(GXBool update_enable);
/* 800AE4E4 global */ extern void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
/* 800AE518 global */ extern void GXSetZCompLoc(GXBool before_tex);
/* 800AE54C global */ extern void GXSetPixelFmt(GXPixelFmt pix_fmt, GXZFmt16 z_fmt);
/* 800AE620 global */ extern void GXSetDither(GXBool dither);
/* 800AE64C global */ extern void GXSetDstAlpha(GXBool enable, u8 alpha);
/* 800AE688 global */ extern void GXSetFieldMask(GXBool odd_mask, GXBool even_mask);
/* 800AE6C0 global */ extern void GXSetFieldMode(GXBool field_mode, GXBool half_aspect_ratio);
// ======================= GXTransform.c ==============================================
/* 800AE738 global */ extern void GXSetProjection(const f32 mtx[4][4], GXProjectionType type);
/* 800AE7DC global */ extern void GXSetProjectionv(const f32* ptr);
/* 800AE868 global */ extern void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
/* 800AE8B8 global */ extern void GXLoadNrmMtxImm(const f32 mtx[3][4], u32 id);
/* 800AE908 global */ extern void GXSetCurrentMtx(u32 id);
/* 800AE93C global */ extern void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
/* 800AE9F0 global */ extern UNK_TYPE __GXSetViewport(UNK_TYPE...);
/* 800AEA80 global */ extern void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz,
                                                      u32 field);
/* 800AEAD8 global */ extern void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);
/* 800AEB20 global */ extern void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
/* 800AEB98 global */ extern void GXGetScissor(u32* left, u32* top, u32* width, u32* height);
/* 800AEBE0 global */ extern void GXSetScissorBoxOffset(s32 x_off, s32 y_off);
/* 800AEC20 global */ extern void GXSetClipMode(GXClipMode mode);
/* 800AEC48 global */ extern UNK_TYPE __GXSetMatrixIndex(UNK_TYPE...);
// ======================= GXPerf.c ===================================================
/* 800AECCC global */ extern void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1);
/* 800AF514 global */ extern void GXReadGPMetric(u32* cnt0, u32* cnt1);
/* 800AF6BC global */ extern void GXClearGPMetric(void);
/* 800AF6CC global */ extern u32 GXReadGP0Metric(void);
/* 800AF6F8 global */ extern u32 GXReadGP1Metric(void);
/* 800AF724 global */ extern void GXReadMemMetric(u32* cp_req, u32* tc_req, u32* cpu_rd_req, u32* cpu_wr_req,
                                                  u32* dsp_req, u32* io_req, u32* vi_req, u32* pe_req, u32* rf_req,
                                                  u32* fi_req);
/* 800AF938 global */ extern void GXClearMemMetric(void);
/* 800AF9E0 global */ extern void GXReadPixMetric(u32* top_pixels_in, u32* top_pixels_out, u32* bot_pixels_in,
                                                  u32* bot_pixels_out, u32* clr_pixels_in, u32* copy_clks);
/* 800AFB18 global */ extern void GXClearPixMetric(void);
/* 800AFB48 global */ extern void GXSetVCacheMetric(GXVCachePerf attr);
/* 800AFB8C global */ extern void GXReadVCacheMetric(u32* check, u32* miss, u32* stall);
/* 800AFC20 global */ extern void GXClearVCacheMetric(void);
/* 800AFC3C global */ extern void GXReadXfRasMetric(u32* xf_wait_in, u32* xf_wait_out, u32* ras_busy, u32* clocks);
// ======================= Padclamp.c =================================================
/* 800AFD00 local  */ // extern UNK_TYPE ClampStick(UNK_TYPE...);
/* 800AFE30 global */ extern void PADClamp(PADStatus* status);
// ======================= Pad.c ======================================================
/* 800AFF44 local  */ // extern UNK_TYPE UpdateOrigin(UNK_TYPE...);
/* 800B00E8 local  */ // extern UNK_TYPE PADOriginCallback(UNK_TYPE...);
/* 800B01AC local  */ // extern UNK_TYPE PADOriginUpdateCallback(UNK_TYPE...);
/* 800B0278 local  */ // extern UNK_TYPE PADProbeCallback(UNK_TYPE...);
/* 800B0350 local  */ // extern UNK_TYPE PADTypeAndStatusCallback(UNK_TYPE...);
/* 800B067C local  */ // extern UNK_TYPE PADReceiveCheckCallback(UNK_TYPE...);
/* 800B07BC global */ extern BOOL PADReset(u32 mask);
/* 800B08CC global */ extern BOOL PADRecalibrate(u32 mask);
/* 800B09E0 global */ extern BOOL PADInit(void);
/* 800B0B30 global */ extern u32 PADRead(PADStatus* status);
/* 800B0E30 global */ extern void PADControlMotor(int chan, u32 command);
/* 800B0EE8 global */ extern void PADSetSpec(u32 model);
/* 800B0F48 local  */ // extern UNK_TYPE SPEC0_MakeStatus(UNK_TYPE...);
/* 800B10BC local  */ // extern UNK_TYPE SPEC1_MakeStatus(UNK_TYPE...);
/* 800B1230 local  */ // extern UNK_TYPE SPEC2_MakeStatus(UNK_TYPE...);
/* 800B16A0 local  */ // extern UNK_TYPE OnReset(UNK_TYPE...);
/* 800B175C local  */ // extern UNK_TYPE SamplingHandler(UNK_TYPE...);
/* 800B17BC global */ extern PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback);
/* 800B1810 global */ extern BOOL __PADDisableRecalibration(BOOL disable);
// ======================= dvdlow.c ===================================================
/* 800B188C weak   */ // extern UNK_TYPE __DVDInitWA(UNK_TYPE...);
/* 800B18CC weak   */ // extern UNK_TYPE __DVDInterruptHandler(UNK_TYPE...);
/* 800B1BAC local  */ // extern UNK_TYPE AlarmHandler(UNK_TYPE...);
/* 800B1C30 local  */ // extern UNK_TYPE AlarmHandlerForTimeout(UNK_TYPE...);
/* 800B1CA0 local  */ // extern UNK_TYPE Read(UNK_TYPE...);
/* 800B1DB0 local  */ // extern UNK_TYPE SeekTwiceBeforeRead(UNK_TYPE...);
/* 800B1E30 weak   */ // extern UNK_TYPE DVDLowRead(UNK_TYPE...);
/* 800B20C8 weak   */ // extern UNK_TYPE DVDLowSeek(UNK_TYPE...);
/* 800B215C weak   */ // extern UNK_TYPE DVDLowWaitCoverClose(UNK_TYPE...);
/* 800B2188 weak   */ // extern UNK_TYPE DVDLowReadDiskID(UNK_TYPE...);
/* 800B222C weak   */ // extern UNK_TYPE DVDLowStopMotor(UNK_TYPE...);
/* 800B22B8 weak   */ // extern UNK_TYPE DVDLowRequestError(UNK_TYPE...);
/* 800B2344 weak   */ // extern UNK_TYPE DVDLowInquiry(UNK_TYPE...);
/* 800B23E0 weak   */ // extern UNK_TYPE DVDLowAudioStream(UNK_TYPE...);
/* 800B2478 weak   */ // extern UNK_TYPE DVDLowRequestAudioStatus(UNK_TYPE...);
/* 800B2504 weak   */ // extern UNK_TYPE DVDLowAudioBufferConfig(UNK_TYPE...);
/* 800B25A0 weak   */ // extern UNK_TYPE DVDLowReset(UNK_TYPE...);
/* 800B265C weak   */ // extern UNK_TYPE DVDLowBreak(UNK_TYPE...);
/* 800B2670 weak   */ // extern UNK_TYPE DVDLowClearCallback(UNK_TYPE...);
/* 800B268C weak   */ // extern UNK_TYPE __DVDLowSetWAType(UNK_TYPE...);
/* 800B26D0 global */ extern UNK_TYPE __DVDLowTestAlarm(UNK_TYPE...);
// ======================= dvdfs.c ====================================================
/* 800B2708 global */ extern UNK_TYPE __DVDFSInit(UNK_TYPE...);
/* 800B2740 global */ extern s32 DVDConvertPathToEntrynum(const char* pathPtr);
/* 800B2A34 global */ extern BOOL DVDOpen(const char* fileName, DVDFileInfo* fileInfo);
/* 800B2AFC global */ extern BOOL DVDClose(DVDFileInfo* fileInfo);
/* 800B2B20 local  */ // extern UNK_TYPE entryToPath(UNK_TYPE...);
/* 800B2C80 global */ extern BOOL DVDGetCurrentDir(char* path, u32 maxlen);
/* 800B2D44 global */ extern BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset,
                                                   DVDCallback callback, s32 prio);
/* 800B2E04 local  */ // extern UNK_TYPE cbForReadAsync(UNK_TYPE...);
/* 800B2E34 global */ extern s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio);
/* 800B2F4C local  */ // extern UNK_TYPE cbForReadSync(UNK_TYPE...);
// ======================= dvd.c ======================================================
/* 800B2F70 local  */ // extern UNK_TYPE defaultOptionalCommandChecker(UNK_TYPE...);
/* 800B2F74 global */ extern void DVDInit(void);
/* 800B3040 local  */ // extern UNK_TYPE stateReadingFST(UNK_TYPE...);
/* 800B30D4 local  */ // extern UNK_TYPE cbForStateReadingFST(UNK_TYPE...);
/* 800B3160 local  */ // extern UNK_TYPE cbForStateError(UNK_TYPE...);
/* 800B320C local  */ // extern UNK_TYPE stateTimeout(UNK_TYPE...);
/* 800B3240 local  */ // extern UNK_TYPE stateGettingError(UNK_TYPE...);
/* 800B3268 local  */ // extern UNK_TYPE CategorizeError(UNK_TYPE...);
/* 800B331C local  */ // extern UNK_TYPE cbForStateGettingError(UNK_TYPE...);
/* 800B35B0 local  */ // extern UNK_TYPE cbForUnrecoveredError(UNK_TYPE...);
/* 800B3618 local  */ // extern UNK_TYPE cbForUnrecoveredErrorRetry(UNK_TYPE...);
/* 800B36B0 local  */ // extern UNK_TYPE stateGoToRetry(UNK_TYPE...);
/* 800B36D8 local  */ // extern UNK_TYPE cbForStateGoToRetry(UNK_TYPE...);
/* 800B3830 local  */ // extern UNK_TYPE stateCheckID(UNK_TYPE...);
/* 800B3910 local  */ // extern UNK_TYPE stateCheckID3(UNK_TYPE...);
/* 800B3944 local  */ // extern UNK_TYPE stateCheckID2a(UNK_TYPE...);
/* 800B3978 local  */ // extern UNK_TYPE cbForStateCheckID2a(UNK_TYPE...);
/* 800B39EC local  */ // extern UNK_TYPE stateCheckID2(UNK_TYPE...);
/* 800B3A24 local  */ // extern UNK_TYPE cbForStateCheckID1(UNK_TYPE...);
/* 800B3B38 local  */ // extern UNK_TYPE cbForStateCheckID2(UNK_TYPE...);
/* 800B3C1C local  */ // extern UNK_TYPE cbForStateCheckID3(UNK_TYPE...);
/* 800B3D18 local  */ // extern UNK_TYPE AlarmHandler(UNK_TYPE...);
/* 800B3D5C local  */ // extern UNK_TYPE stateCoverClosed(UNK_TYPE...);
/* 800B3E28 local  */ // extern UNK_TYPE stateCoverClosed_CMD(UNK_TYPE...);
/* 800B3E58 local  */ // extern UNK_TYPE cbForStateCoverClosed(UNK_TYPE...);
/* 800B3EC8 local  */ // extern UNK_TYPE stateMotorStopped(UNK_TYPE...);
/* 800B3EF0 local  */ // extern UNK_TYPE cbForStateMotorStopped(UNK_TYPE...);
/* 800B3FD4 local  */ // extern UNK_TYPE stateReady(UNK_TYPE...);
/* 800B4204 local  */ // extern UNK_TYPE stateBusy(UNK_TYPE...);
/* 800B4524 local  */ // extern UNK_TYPE cbForStateBusy(UNK_TYPE...);
/* 800B4B5C global */ extern UNK_TYPE DVDReadAbsAsyncPrio(UNK_TYPE...);
/* 800B4C38 global */ extern UNK_TYPE DVDReadAbsAsyncForBS(UNK_TYPE...);
/* 800B4D08 global */ extern UNK_TYPE DVDReadDiskID(UNK_TYPE...);
/* 800B4DDC global */ extern UNK_TYPE DVDCancelStreamAsync(UNK_TYPE...);
/* 800B4E98 global */ extern UNK_TYPE DVDInquiryAsync(UNK_TYPE...);
/* 800B4F68 global */ extern UNK_TYPE DVDReset(UNK_TYPE...);
/* 800B4FAC global */ extern s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block);
/* 800B4FF8 global */ extern s32 DVDGetDriveStatus(void);
/* 800B50A4 global */ extern BOOL DVDSetAutoInvalidation(BOOL autoInval);
/* 800B50B4 global */ extern void DVDResume(void);
/* 800B5104 global */ extern BOOL DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback);
/* 800B5380 global */ extern s32 DVDCancel(DVDCommandBlock* block);
/* 800B542C local  */ // extern UNK_TYPE cbForCancelSync(UNK_TYPE...);
/* 800B5450 global */ extern DVDDiskID* DVDGetCurrentDiskID(void);
/* 800B5458 global */ extern UNK_TYPE DVDCheckDisk(UNK_TYPE...);
/* 800B5550 global */ extern UNK_TYPE __DVDPrepareResetAsync(UNK_TYPE...);
/* 800B566C global */ extern UNK_TYPE __DVDTestAlarm(UNK_TYPE...);
// ======================= dvdqueue.c =================================================
/* 800B56A4 global */ extern UNK_TYPE __DVDClearWaitingQueue(UNK_TYPE...);
/* 800B56DC global */ extern UNK_TYPE __DVDPushWaitingQueue(UNK_TYPE...);
/* 800B5744 global */ extern UNK_TYPE __DVDPopWaitingQueue(UNK_TYPE...);
/* 800B57E4 global */ extern UNK_TYPE __DVDCheckWaitingQueue(UNK_TYPE...);
/* 800B583C global */ extern UNK_TYPE __DVDDequeueWaitingQueue(UNK_TYPE...);
// ======================= dvderror.c =================================================
/* 800B589C local  */ // extern UNK_TYPE ErrorCode2Num(UNK_TYPE...);
/* 800B59B8 global */ extern UNK_TYPE __DVDStoreErrorCode(UNK_TYPE...);
// ======================= dvdidutils.c ===============================================
/* 800B5A34 global */ extern BOOL DVDCompareDiskID(const DVDDiskID* id1, const DVDDiskID* id2);
// ======================= dvdFatal.c =================================================
/* 800B5B2C global */ extern UNK_TYPE __DVDPrintFatalMessage(UNK_TYPE...);
// ======================= fstload.c ==================================================
/* 800B5B5C local  */ // extern UNK_TYPE cb(UNK_TYPE...);
/* 800B5C34 global */ extern UNK_TYPE __fstLoad(UNK_TYPE...);
// ======================= DEMOInit.c =================================================
/* 800B5D9C global */ extern UNK_TYPE DEMOInit(UNK_TYPE...);
/* 800B5E10 local  */ // extern UNK_TYPE __DEMOInitRenderMode(UNK_TYPE...);
/* 800B5F64 local  */ // extern UNK_TYPE __DEMOInitMem(UNK_TYPE...);
/* 800B6038 local  */ // extern UNK_TYPE __DEMOInitGX(UNK_TYPE...);
/* 800B6154 local  */ // extern UNK_TYPE __DEMOInitVI(UNK_TYPE...);
/* 800B619C global */ extern UNK_TYPE DEMOBeforeRender(UNK_TYPE...);
/* 800B6284 global */ extern UNK_TYPE DEMODoneRender(UNK_TYPE...);
/* 800B6308 global */ extern UNK_TYPE DEMOSwapBuffers(UNK_TYPE...);
/* 800B6370 global */ extern UNK_TYPE DEMOGetRenderModeObj(UNK_TYPE...);
/* 800B6378 local  */ // extern UNK_TYPE __NoHangDoneRender(UNK_TYPE...);
/* 800B646C global */ extern UNK_TYPE DEMOSetGPHangMetric(UNK_TYPE...);
/* 800B6528 local  */ // extern UNK_TYPE __DEMODiagnoseHang(UNK_TYPE...);
/* 800B66E4 global */ extern UNK_TYPE DEMOReInit(UNK_TYPE...);
// ======================= DEMOPuts.c =================================================
/* 800B68C4 global */ extern UNK_TYPE DEMOInitCaption(UNK_TYPE...);
/* 800B6B20 global */ extern UNK_TYPE DEMOPuts(UNK_TYPE...);
// ======================= DEMOFont.c =================================================
/* 800B6E30 global */ extern UNK_TYPE DEMOPrintf(UNK_TYPE...);
// ======================= DEMOPad.c ==================================================
/* 800B6EF4 local  */ // extern UNK_TYPE DEMOPadCopy(UNK_TYPE...);
/* 800B708C global */ extern UNK_TYPE DEMOPadRead(UNK_TYPE...);
/* 800B7158 global */ extern UNK_TYPE DEMOPadInit(UNK_TYPE...);
// ======================= DEMOStats.c ================================================
/* 800B722C local  */ // extern UNK_TYPE DEMOWriteStats(UNK_TYPE...);
/* 800B75C0 global */ extern UNK_TYPE DEMOUpdateStats(UNK_TYPE...);
/* 800B7618 global */ extern UNK_TYPE DEMOPrintStats(UNK_TYPE...);
// ======================= ai.c =======================================================
/* 800B7F84 global */ extern AIDCallback AIRegisterDMACallback(AIDCallback callback);
/* 800B7FC8 global */ extern void AIInitDMA(u32 start_addr, u32 length);
/* 800B8050 global */ extern BOOL AIGetDMAEnableFlag(void);
/* 800B8060 global */ extern void AIStartDMA(void);
/* 800B8078 global */ extern void AIStopDMA(void);
/* 800B8090 global */ extern u32 AIGetDMABytesLeft(void);
/* 800B80A0 global */ extern u32 AIGetDMAStartAddr(void);
/* 800B80BC global */ extern UNK_TYPE AISetStreamPlayState(UNK_TYPE...);
/* 800B8194 global */ extern UNK_TYPE AIGetStreamPlayState(UNK_TYPE...);
/* 800B81A4 global */ extern void AISetDSPSampleRate(u32 rate);
/* 800B8284 global */ extern u32 AIGetDSPSampleRate(void);
/* 800B8298 local  */ // extern UNK_TYPE __AI_set_stream_sample_rate(UNK_TYPE...);
/* 800B836C global */ extern UNK_TYPE AIGetStreamSampleRate(UNK_TYPE...);
/* 800B837C global */ extern UNK_TYPE AISetStreamVolLeft(UNK_TYPE...);
/* 800B8398 global */ extern UNK_TYPE AIGetStreamVolLeft(UNK_TYPE...);
/* 800B83A8 global */ extern UNK_TYPE AISetStreamVolRight(UNK_TYPE...);
/* 800B83C4 global */ extern UNK_TYPE AIGetStreamVolRight(UNK_TYPE...);
/* 800B83D4 global */ extern void AIInit(u8* stack);
/* 800B8540 local  */ // extern UNK_TYPE __AISHandler(UNK_TYPE...);
/* 800B85BC local  */ // extern UNK_TYPE __AIDHandler(UNK_TYPE...);
/* 800B8668 local  */ // extern UNK_TYPE __AICallbackStackSwitch(UNK_TYPE...);
/* 800B86C0 local  */ // extern UNK_TYPE __AI_SRC_INIT(UNK_TYPE...);
// ======================= ar.c =======================================================
/* 800B88A4 global */ extern UNK_TYPE ARGetDMAStatus(UNK_TYPE...);
/* 800B88E0 global */ extern UNK_TYPE ARStartDMA(UNK_TYPE...);
/* 800B89D0 global */ extern UNK_TYPE ARInit(UNK_TYPE...);
/* 800B8A94 global */ extern UNK_TYPE ARGetBaseAddress(UNK_TYPE...);
/* 800B8A9C local  */ // extern UNK_TYPE __ARHandler(UNK_TYPE...);
/* 800B8B14 local  */ // extern UNK_TYPE __ARChecksize(UNK_TYPE...);
// ======================= dsp.c ======================================================
/* 800BA308 global */ extern u32 DSPCheckMailToDSP(void);
/* 800BA318 global */ extern u32 DSPCheckMailFromDSP(void);
/* 800BA328 global */ extern u32 DSPReadMailFromDSP(void);
/* 800BA340 global */ extern void DSPSendMailToDSP(u32 mail);
/* 800BA354 global */ extern void DSPInit(void);
/* 800BA418 global */ extern DSPTaskInfo* DSPAddTask(DSPTaskInfo* task);
// ======================= dsp_debug.c ================================================
/* 800BA488 global */ extern UNK_TYPE __DSP_debug_printf(UNK_TYPE...);
// ======================= dsp_task.c =================================================
/* 800BA4D8 global */ extern UNK_TYPE __DSPHandler(UNK_TYPE...);
/* 800BA8FC global */ extern UNK_TYPE __DSP_exec_task(UNK_TYPE...);
/* 800BAA9C global */ extern UNK_TYPE __DSP_boot_task(UNK_TYPE...);
/* 800BAC28 global */ extern UNK_TYPE __DSP_insert_task(UNK_TYPE...);
/* 800BACC8 global */ extern UNK_TYPE __DSP_remove_task(UNK_TYPE...);
// ======================= CARDBios.c =================================================
/* 800BAD5C global */ extern UNK_TYPE __CARDDefaultApiCallback(UNK_TYPE...);
/* 800BAD60 global */ extern UNK_TYPE __CARDSyncCallback(UNK_TYPE...);
/* 800BAD94 global */ extern UNK_TYPE __CARDExtHandler(UNK_TYPE...);
/* 800BAE6C global */ extern UNK_TYPE __CARDExiHandler(UNK_TYPE...);
/* 800BAF84 global */ extern UNK_TYPE __CARDTxHandler(UNK_TYPE...);
/* 800BB02C global */ extern UNK_TYPE __CARDUnlockedHandler(UNK_TYPE...);
/* 800BB0B0 global */ extern UNK_TYPE __CARDEnableInterrupt(UNK_TYPE...);
/* 800BB170 global */ extern UNK_TYPE __CARDReadStatus(UNK_TYPE...);
/* 800BB260 global */ extern UNK_TYPE __CARDClearStatus(UNK_TYPE...);
/* 800BB30C local  */ // extern UNK_TYPE TimeoutHandler(UNK_TYPE...);
/* 800BB3B0 local  */ // extern UNK_TYPE Retry(UNK_TYPE...);
/* 800BB5DC local  */ // extern UNK_TYPE UnlockedCallback(UNK_TYPE...);
/* 800BB6EC local  */ // extern UNK_TYPE __CARDStart(UNK_TYPE...);
/* 800BB8A0 global */ extern UNK_TYPE __CARDReadSegment(UNK_TYPE...);
/* 800BB9D4 global */ extern UNK_TYPE __CARDWritePage(UNK_TYPE...);
/* 800BBAF0 global */ extern UNK_TYPE __CARDEraseSector(UNK_TYPE...);
/* 800BBBD0 global */ extern UNK_TYPE CARDInit(UNK_TYPE...);
/* 800BBC7C global */ extern UNK_TYPE __CARDGetFontEncode(UNK_TYPE...);
/* 800BBC84 global */ extern UNK_TYPE __CARDSetDiskID(UNK_TYPE...);
/* 800BBCBC global */ extern UNK_TYPE __CARDGetControlBlock(UNK_TYPE...);
/* 800BBD74 global */ extern UNK_TYPE __CARDPutControlBlock(UNK_TYPE...);
/* 800BBDD8 global */ extern UNK_TYPE CARDGetResultCode(UNK_TYPE...);
/* 800BBE08 global */ extern UNK_TYPE CARDFreeBlocks(UNK_TYPE...);
/* 800BBF58 global */ extern UNK_TYPE __CARDSync(UNK_TYPE...);
/* 800BBFF0 local  */ // extern UNK_TYPE OnReset(UNK_TYPE...);
// ======================= CARDUnlock.c ===============================================
/* 800BC040 local  */ // extern UNK_TYPE bitrev(UNK_TYPE...);
/* 800BC1AC local  */ // extern UNK_TYPE ReadArrayUnlock(UNK_TYPE...);
/* 800BC2F0 local  */ // extern UNK_TYPE DummyLen(UNK_TYPE...);
/* 800BC3B4 global */ extern UNK_TYPE __CARDUnlock(UNK_TYPE...);
/* 800BCF0C local  */ // extern UNK_TYPE InitCallback(UNK_TYPE...);
/* 800BCF7C local  */ // extern UNK_TYPE DoneCallback(UNK_TYPE...);
// ======================= CARDRdwr.c =================================================
/* 800BD2A0 local  */ // extern UNK_TYPE BlockReadCallback(UNK_TYPE...);
/* 800BD37C global */ extern UNK_TYPE __CARDRead(UNK_TYPE...);
/* 800BD3E0 local  */ // extern UNK_TYPE BlockWriteCallback(UNK_TYPE...);
/* 800BD4BC global */ extern UNK_TYPE __CARDWrite(UNK_TYPE...);
/* 800BD520 global */ extern UNK_TYPE CARDGetXferredBytes(UNK_TYPE...);
// ======================= CARDBlock.c ================================================
/* 800BD538 global */ extern UNK_TYPE __CARDGetFatBlock(UNK_TYPE...);
/* 800BD540 local  */ // extern UNK_TYPE WriteCallback(UNK_TYPE...);
/* 800BD614 local  */ // extern UNK_TYPE EraseCallback(UNK_TYPE...);
/* 800BD6DC global */ extern UNK_TYPE __CARDAllocBlock(UNK_TYPE...);
/* 800BD7F4 global */ extern UNK_TYPE __CARDFreeBlock(UNK_TYPE...);
/* 800BD890 global */ extern UNK_TYPE __CARDUpdateFatBlock(UNK_TYPE...);
// ======================= CARDDir.c ==================================================
/* 800BD93C global */ extern UNK_TYPE __CARDGetDirBlock(UNK_TYPE...);
/* 800BD944 local  */ // extern UNK_TYPE WriteCallback(UNK_TYPE...);
/* 800BDA14 local  */ // extern UNK_TYPE EraseCallback(UNK_TYPE...);
/* 800BDADC global */ extern UNK_TYPE __CARDUpdateDir(UNK_TYPE...);
// ======================= CARDCheck.c ================================================
/* 800BDBA0 global */ extern UNK_TYPE __CARDCheckSum(UNK_TYPE...);
/* 800BDD50 local  */ // extern UNK_TYPE VerifyID(UNK_TYPE...);
/* 800BDFD4 local  */ // extern UNK_TYPE VerifyDir(UNK_TYPE...);
/* 800BE214 local  */ // extern UNK_TYPE VerifyFAT(UNK_TYPE...);
/* 800BE498 global */ extern UNK_TYPE __CARDVerify(UNK_TYPE...);
/* 800BE524 global */ extern UNK_TYPE CARDCheckExAsync(UNK_TYPE...);
/* 800BEAB4 global */ extern UNK_TYPE CARDCheck(UNK_TYPE...);
// ======================= CARDMount.c ================================================
/* 800BEB08 local  */ // extern UNK_TYPE IsCard(UNK_TYPE...);
/* 800BEBD4 global */ extern UNK_TYPE CARDProbeEx(UNK_TYPE...);
/* 800BED50 local  */ // extern UNK_TYPE DoMount(UNK_TYPE...);
/* 800BF160 global */ extern UNK_TYPE __CARDMountCallback(UNK_TYPE...);
/* 800BF298 global */ extern UNK_TYPE CARDMountAsync(UNK_TYPE...);
/* 800BF438 global */ extern UNK_TYPE CARDMount(UNK_TYPE...);
/* 800BF480 local  */ // extern UNK_TYPE DoUnmount(UNK_TYPE...);
/* 800BF51C global */ extern UNK_TYPE CARDUnmount(UNK_TYPE...);
// ======================= CARDFormat.c ===============================================
/* 800BF5C8 local  */ // extern UNK_TYPE FormatCallback(UNK_TYPE...);
/* 800BF70C global */ extern UNK_TYPE __CARDFormatRegionAsync(UNK_TYPE...);
/* 800BFD64 global */ extern UNK_TYPE CARDFormatAsync(UNK_TYPE...);
// ======================= CARDOpen.c =================================================
/* 800BFDAC global */ extern UNK_TYPE __CARDCompareFileName(UNK_TYPE...);
/* 800BFE14 global */ extern UNK_TYPE __CARDAccess(UNK_TYPE...);
/* 800BFEA8 global */ extern UNK_TYPE __CARDIsWritable(UNK_TYPE...);
/* 800BFFDC global */ extern UNK_TYPE __CARDIsReadable(UNK_TYPE...);
/* 800C00D0 global */ extern UNK_TYPE __CARDGetFileNo(UNK_TYPE...);
/* 800C0220 global */ extern UNK_TYPE CARDOpen(UNK_TYPE...);
/* 800C033C global */ extern UNK_TYPE CARDClose(UNK_TYPE...);
/* 800C0390 global */ extern UNK_TYPE __CARDIsOpened(UNK_TYPE...);
// ======================= CARDCreate.c ===============================================
/* 800C0398 local  */ // extern UNK_TYPE CreateCallbackFat(UNK_TYPE...);
/* 800C04C8 global */ extern UNK_TYPE CARDCreateAsync(UNK_TYPE...);
// ======================= CARDRead.c =================================================
/* 800C06E8 global */ extern UNK_TYPE __CARDSeek(UNK_TYPE...);
/* 800C08A0 local  */ // extern UNK_TYPE ReadCallback(UNK_TYPE...);
/* 800C09D0 global */ extern UNK_TYPE CARDReadAsync(UNK_TYPE...);
/* 800C0B14 global */ extern UNK_TYPE CARDRead(UNK_TYPE...);
// ======================= CARDWrite.c ================================================
/* 800C0B5C local  */ // extern UNK_TYPE WriteCallback(UNK_TYPE...);
/* 800C0CCC local  */ // extern UNK_TYPE EraseCallback(UNK_TYPE...);
/* 800C0D7C global */ extern UNK_TYPE CARDWriteAsync(UNK_TYPE...);
// ======================= CARDDelete.c ===============================================
/* 800C0E90 local  */ // extern UNK_TYPE DeleteCallback(UNK_TYPE...);
/* 800C0F34 global */ extern UNK_TYPE CARDDeleteAsync(UNK_TYPE...);
// ======================= CARDStat.c =================================================
/* 800C1044 local  */ // extern UNK_TYPE UpdateIconOffsets(UNK_TYPE...);
/* 800C123C global */ extern UNK_TYPE CARDGetStatus(UNK_TYPE...);
/* 800C1350 global */ extern UNK_TYPE CARDSetStatusAsync(UNK_TYPE...);
// ======================= CARDNet.c ==================================================
// ======================= THPDec.c ===================================================
/* 800C14C4 global */ extern s32 THPVideoDecode(void* file, void* tileY, void* tileU, void* tileV, void* work);
/* 800C1708 local  */ // extern UNK_TYPE __THPSetupBuffers(UNK_TYPE...);
/* 800C174C local  */ // extern UNK_TYPE __THPReadFrameHeader(UNK_TYPE...);
/* 800C1888 local  */ // extern UNK_TYPE __THPReadScaneHeader(UNK_TYPE...);
/* 800C19A4 local  */ // extern UNK_TYPE __THPReadQuantizationTable(UNK_TYPE...);
/* 800C1D60 local  */ // extern UNK_TYPE __THPReadHuffmanTableSpecification(UNK_TYPE...);
/* 800C1F40 local  */ // extern UNK_TYPE __THPHuffGenerateSizeTable(UNK_TYPE...);
/* 800C2030 local  */ // extern UNK_TYPE __THPHuffGenerateCodeTable(UNK_TYPE...);
/* 800C2098 local  */ // extern UNK_TYPE __THPHuffGenerateDecoderTables(UNK_TYPE...);
/* 800C2254 local  */ // extern UNK_TYPE __THPRestartDefinition(UNK_TYPE...);
/* 800C22A8 local  */ // extern UNK_TYPE __THPPrepBitStream(UNK_TYPE...);
/* 800C24F4 local  */ // extern UNK_TYPE __THPDecompressYUV(UNK_TYPE...);
/* 800C2600 local  */ // extern UNK_TYPE __THPDecompressiMCURow512x448(UNK_TYPE...);
/* 800C4088 local  */ // extern UNK_TYPE __THPDecompressiMCURow640x480(UNK_TYPE...);
/* 800C5B14 local  */ // extern UNK_TYPE __THPDecompressiMCURowNxN(UNK_TYPE...);
/* 800C75C0 local  */ // extern UNK_TYPE __THPHuffDecodeDCTCompY(UNK_TYPE...);
/* 800C7C3C local  */ // extern UNK_TYPE __THPHuffDecodeDCTCompU(UNK_TYPE...);
/* 800C82E4 local  */ // extern UNK_TYPE __THPHuffDecodeDCTCompV(UNK_TYPE...);
/* 800C898C global */ extern BOOL THPInit(void);
// ======================= THPAudio.c =================================================
/* 800C8A2C global */ extern u32 THPAudioDecode(s16* buffer, u8* audioFrame, s32 flag);
/* 800C8E90 local  */ // extern UNK_TYPE __THPAudioGetNewSample(UNK_TYPE...);
/* 800C8F20 local  */ // extern UNK_TYPE __THPAudioInitialize(UNK_TYPE...);
// ======================= texPalette.c ===============================================
/* 800C8F5C global */ extern UNK_TYPE TEXGet(UNK_TYPE...);
/* 800C8F6C global */ extern UNK_TYPE TEXGetGXTexObjFromPalette(UNK_TYPE...);
// ======================= mainloop.c =================================================
/* 800C9040 global */ extern UNK_TYPE TRKHandleRequestEvent(UNK_TYPE...);
/* 800C9068 global */ extern UNK_TYPE TRKHandleSupportEvent(UNK_TYPE...);
/* 800C9088 global */ extern UNK_TYPE TRKIdle(UNK_TYPE...);
/* 800C90B4 global */ extern UNK_TYPE TRKNubMainLoop(UNK_TYPE...);
// ======================= nubevent.c =================================================
/* 800C91A8 global */ extern UNK_TYPE TRKInitializeEventQueue(UNK_TYPE...);
/* 800C9204 global */ extern UNK_TYPE TRKCopyEvent(UNK_TYPE...);
/* 800C9228 global */ extern UNK_TYPE TRKGetNextEvent(UNK_TYPE...);
/* 800C92E8 global */ extern UNK_TYPE TRKPostEvent(UNK_TYPE...);
/* 800C93C8 global */ extern UNK_TYPE TRKConstructEvent(UNK_TYPE...);
/* 800C93E0 global */ extern UNK_TYPE TRKDestructEvent(UNK_TYPE...);
// ======================= nubinit.c ==================================================
/* 800C9404 global */ extern UNK_TYPE TRKInitializeNub(UNK_TYPE...);
/* 800C94D8 global */ extern UNK_TYPE TRKTerminateNub(UNK_TYPE...);
/* 800C94FC global */ extern UNK_TYPE TRKNubWelcome(UNK_TYPE...);
/* 800C9524 global */ extern UNK_TYPE TRKInitializeEndian(UNK_TYPE...);
// ======================= msg.c ======================================================
/* 800C9598 global */ extern UNK_TYPE TRKMessageSend(UNK_TYPE...);
// ======================= msgbuf.c ===================================================
/* 800C95C0 local  */ // extern UNK_TYPE TRKSetBufferUsed(UNK_TYPE...);
/* 800C95C8 global */ extern UNK_TYPE TRKInitializeMessageBuffers(UNK_TYPE...);
/* 800C9640 global */ extern UNK_TYPE TRKGetFreeBuffer(UNK_TYPE...);
/* 800C96DC global */ extern UNK_TYPE TRKGetBuffer(UNK_TYPE...);
/* 800C9708 global */ extern UNK_TYPE TRKReleaseBuffer(UNK_TYPE...);
/* 800C9770 global */ extern UNK_TYPE TRKResetBuffer(UNK_TYPE...);
/* 800C97B0 global */ extern UNK_TYPE TRKSetBufferPosition(UNK_TYPE...);
/* 800C97E0 global */ extern UNK_TYPE TRKAppendBuffer(UNK_TYPE...);
/* 800C9884 global */ extern UNK_TYPE TRKReadBuffer(UNK_TYPE...);
/* 800C9910 global */ extern UNK_TYPE TRKAppendBuffer1_ui16(UNK_TYPE...);
/* 800C9964 global */ extern UNK_TYPE TRKAppendBuffer1_ui32(UNK_TYPE...);
/* 800C99C8 global */ extern UNK_TYPE TRKAppendBuffer1_ui64(UNK_TYPE...);
/* 800C9A50 global */ extern UNK_TYPE TRKAppendBuffer_ui8(UNK_TYPE...);
/* 800C9AB8 global */ extern UNK_TYPE TRKAppendBuffer_ui32(UNK_TYPE...);
/* 800C9B34 global */ extern UNK_TYPE TRKReadBuffer1_ui8(UNK_TYPE...);
/* 800C9B58 global */ extern UNK_TYPE TRKReadBuffer1_ui16(UNK_TYPE...);
/* 800C9BD8 global */ extern UNK_TYPE TRKReadBuffer1_ui32(UNK_TYPE...);
/* 800C9C68 global */ extern UNK_TYPE TRKReadBuffer1_ui64(UNK_TYPE...);
/* 800C9D18 global */ extern UNK_TYPE TRKReadBuffer_ui8(UNK_TYPE...);
/* 800C9D8C global */ extern UNK_TYPE TRKReadBuffer_ui32(UNK_TYPE...);
// ======================= serpoll.c ==================================================
/* 800C9E08 global */ extern UNK_TYPE TRKTestForPacket(UNK_TYPE...);
/* 800C9ED8 global */ extern UNK_TYPE TRKGetInput(UNK_TYPE...);
/* 800C9F54 global */ extern UNK_TYPE TRKProcessInput(UNK_TYPE...);
/* 800C9FA4 global */ extern UNK_TYPE TRKInitializeSerialHandler(UNK_TYPE...);
/* 800C9FC8 global */ extern UNK_TYPE TRKTerminateSerialHandler(UNK_TYPE...);
// ======================= usr_put.c ==================================================
/* 800C9FD0 global */ extern UNK_TYPE usr_put_initialize(UNK_TYPE...);
// ======================= dispatch.c =================================================
/* 800C9FD4 global */ extern UNK_TYPE TRKInitializeDispatcher(UNK_TYPE...);
/* 800C9FE8 global */ extern UNK_TYPE TRKDispatchMessage(UNK_TYPE...);
// ======================= msghndlr.c =================================================
/* 800CA06C local  */ // extern UNK_TYPE TRKMessageIntoReply(UNK_TYPE...);
/* 800CA104 global */ extern UNK_TYPE TRKSendACK(UNK_TYPE...);
/* 800CA154 global */ extern UNK_TYPE TRKStandardACK(UNK_TYPE...);
/* 800CA188 global */ extern UNK_TYPE TRKDoUnsupported(UNK_TYPE...);
/* 800CA1B0 global */ extern UNK_TYPE TRKDoConnect(UNK_TYPE...);
/* 800CA1D8 global */ extern UNK_TYPE TRKDoDisconnect(UNK_TYPE...);
/* 800CA228 global */ extern UNK_TYPE TRKDoReset(UNK_TYPE...);
/* 800CA258 global */ extern UNK_TYPE TRKDoVersions(UNK_TYPE...);
/* 800CA3DC global */ extern UNK_TYPE TRKDoSupportMask(UNK_TYPE...);
/* 800CA4B8 global */ extern UNK_TYPE TRKDoCPUType(UNK_TYPE...);
/* 800CA6FC global */ extern UNK_TYPE TRKDoReadMemory(UNK_TYPE...);
/* 800CA8C8 global */ extern UNK_TYPE TRKDoWriteMemory(UNK_TYPE...);
/* 800CAAA8 global */ extern UNK_TYPE TRKDoReadRegisters(UNK_TYPE...);
/* 800CACB4 global */ extern UNK_TYPE TRKDoWriteRegisters(UNK_TYPE...);
/* 800CAEB0 global */ extern UNK_TYPE TRKDoFlushCache(UNK_TYPE...);
/* 800CB008 global */ extern UNK_TYPE TRKDoContinue(UNK_TYPE...);
/* 800CB06C global */ extern UNK_TYPE TRKDoStep(UNK_TYPE...);
/* 800CB280 global */ extern UNK_TYPE TRKDoStop(UNK_TYPE...);
// ======================= support.c ==================================================
/* 800CB2D8 global */ extern UNK_TYPE TRKSuppAccessFile(UNK_TYPE...);
/* 800CB5B0 global */ extern UNK_TYPE TRKRequestSend(UNK_TYPE...);
// ======================= mutex_TRK.c ================================================
/* 800CB754 global */ extern UNK_TYPE TRKInitializeMutex(UNK_TYPE...);
/* 800CB75C global */ extern UNK_TYPE TRKAcquireMutex(UNK_TYPE...);
/* 800CB764 global */ extern UNK_TYPE TRKReleaseMutex(UNK_TYPE...);
// ======================= notify.c ===================================================
/* 800CB76C global */ extern UNK_TYPE TRKDoNotifyStopped(UNK_TYPE...);
// ======================= flush_cache.c ==============================================
/* 800CB844 global */ extern UNK_TYPE TRK_flush_cache(UNK_TYPE...);
// ======================= mem_TRK.c ==================================================
/* 80003458 global */ extern UNK_TYPE TRK_memcpy(UNK_TYPE...);
// ======================= __exception.s ==============================================
/* 8000347C global */ // extern UNK_TYPE gTRKInterruptVectorTable(UNK_TYPE...);
// ======================= targimpl.c =================================================
/* 800CB87C global */ extern UNK_TYPE __TRK_get_MSR(UNK_TYPE...);
/* 800CB884 global */ extern UNK_TYPE __TRK_set_MSR(UNK_TYPE...);
/* 800CB88C global */ extern UNK_TYPE TRKValidMemory32(UNK_TYPE...);
/* 800CB9C4 local  */ // extern UNK_TYPE TRK_ppc_memcpy(UNK_TYPE...);
/* 800CBA00 global */ extern UNK_TYPE TRKTargetAccessMemory(UNK_TYPE...);
/* 800CBB64 global */ extern UNK_TYPE TRKTargetReadInstruction(UNK_TYPE...);
/* 800CBBB0 global */ extern UNK_TYPE TRKTargetAccessDefault(UNK_TYPE...);
/* 800CBCAC global */ extern UNK_TYPE TRKTargetAccessFP(UNK_TYPE...);
/* 800CBDF4 global */ extern UNK_TYPE TRKTargetAccessExtended1(UNK_TYPE...);
/* 800CBF6C global */ extern UNK_TYPE TRKTargetAccessExtended2(UNK_TYPE...);
/* 800CC0E8 global */ extern UNK_TYPE TRKTargetVersions(UNK_TYPE...);
/* 800CC110 global */ extern UNK_TYPE TRKTargetSupportMask(UNK_TYPE...);
/* 800CC1B4 global */ extern UNK_TYPE TRKTargetCPUType(UNK_TYPE...);
/* 800CC21C global */ extern UNK_TYPE TRKInterruptHandler(UNK_TYPE...);
/* 800CC3B0 global */ extern UNK_TYPE TRKExceptionHandler(UNK_TYPE...);
/* 800CC44C global */ extern UNK_TYPE TRKPostInterruptEvent(UNK_TYPE...);
/* 800CC4FC global */ extern UNK_TYPE TRKSwapAndGo(UNK_TYPE...);
/* 800CC5C0 global */ extern UNK_TYPE TRKInterruptHandlerEnableInterrupts(UNK_TYPE...);
/* 800CC614 global */ extern UNK_TYPE TRKTargetInterrupt(UNK_TYPE...);
/* 800CC678 global */ extern UNK_TYPE TRKTargetAddStopInfo(UNK_TYPE...);
/* 800CC708 global */ extern UNK_TYPE TRKTargetAddExceptionInfo(UNK_TYPE...);
/* 800CC790 local  */ // extern UNK_TYPE TRKTargetEnableTrace(UNK_TYPE...);
/* 800CC7CC local  */ // extern UNK_TYPE TRKTargetStepDone(UNK_TYPE...);
/* 800CC850 local  */ // extern UNK_TYPE TRKTargetDoStep(UNK_TYPE...);
/* 800CC8C0 local  */ // extern UNK_TYPE TRKTargetCheckStep(UNK_TYPE...);
/* 800CC928 global */ extern UNK_TYPE TRKTargetSingleStep(UNK_TYPE...);
/* 800CC96C global */ extern UNK_TYPE TRKTargetStepOutOfRange(UNK_TYPE...);
/* 800CC9B4 global */ extern UNK_TYPE TRKTargetGetPC(UNK_TYPE...);
/* 800CC9C4 global */ extern UNK_TYPE TRKTargetSupportRequest(UNK_TYPE...);
/* 800CCAB4 global */ extern UNK_TYPE TRKTargetFlushCache(UNK_TYPE...);
/* 800CCAF0 global */ extern UNK_TYPE TRKTargetStopped(UNK_TYPE...);
/* 800CCB00 global */ extern UNK_TYPE TRKTargetSetStopped(UNK_TYPE...);
/* 800CCB10 global */ extern UNK_TYPE TRKTargetStop(UNK_TYPE...);
/* 800CCB38 global */ extern UNK_TYPE TRKPPCAccessSPR(UNK_TYPE...);
/* 800CCBE8 global */ extern UNK_TYPE TRKPPCAccessPairedSingleRegister(UNK_TYPE...);
/* 800CCC60 global */ extern UNK_TYPE TRKPPCAccessFPRegister(UNK_TYPE...);
/* 800CCDE0 global */ extern UNK_TYPE TRKPPCAccessSpecialReg(UNK_TYPE...);
/* 800CCE48 global */ extern UNK_TYPE TRKTargetSetInputPendingPtr(UNK_TYPE...);
// ======================= dolphin_trk.c ==============================================
/* 800053B0 global */ extern UNK_TYPE __TRK_reset(UNK_TYPE...);
/* 800CCE58 global */ extern UNK_TYPE InitMetroTRK(UNK_TYPE...);
/* 800CCEEC global */ extern UNK_TYPE EnableMetroTRKInterrupts(UNK_TYPE...);
/* 800CCF0C global */ extern UNK_TYPE TRKTargetTranslate(UNK_TYPE...);
/* 800CCF18 global */ extern UNK_TYPE TRK_copy_vector(UNK_TYPE...);
/* 800CCF78 global */ extern UNK_TYPE __TRK_copy_vectors(UNK_TYPE...);
/* 800CD00C global */ extern UNK_TYPE TRKInitializeTarget(UNK_TYPE...);
// ======================= mpc_7xx_603e.c =============================================
/* 800CD04C global */ extern UNK_TYPE TRKSaveExtended1Block(UNK_TYPE...);
/* 800CD204 global */ extern UNK_TYPE TRKRestoreExtended1Block(UNK_TYPE...);
// ======================= main_TRK.c =================================================
/* 800CD3BC global */ extern UNK_TYPE TRKTargetCPUMinorType(UNK_TYPE...);
/* 800CD3C4 global */ extern UNK_TYPE TRK_main(UNK_TYPE...);
// ======================= dolphin_trk_glue.c =========================================
/* 800CD40C global */ extern UNK_TYPE TRKLoadContext(UNK_TYPE...);
/* 800CD494 global */ extern UNK_TYPE TRKEXICallBack(UNK_TYPE...);
/* 800CD4CC global */ extern UNK_TYPE InitMetroTRKCommTable(UNK_TYPE...);
/* 800CD5B4 global */ extern UNK_TYPE TRKUARTInterruptHandler(UNK_TYPE...);
/* 800CD5B8 global */ extern UNK_TYPE TRKInitializeIntDrivenUART(UNK_TYPE...);
/* 800CD5F8 global */ extern UNK_TYPE EnableEXI2Interrupts(UNK_TYPE...);
/* 800CD628 global */ extern UNK_TYPE TRKPollUART(UNK_TYPE...);
/* 800CD658 global */ extern UNK_TYPE TRK_ReadUARTN(UNK_TYPE...);
/* 800CD69C global */ extern UNK_TYPE TRK_WriteUARTN(UNK_TYPE...);
/* 800CD6E0 global */ extern UNK_TYPE ReserveEXI2Port(UNK_TYPE...);
/* 800CD710 global */ extern UNK_TYPE UnreserveEXI2Port(UNK_TYPE...);
/* 800CD740 global */ extern UNK_TYPE TRK_board_display(UNK_TYPE...);
// ======================= targcont.c =================================================
/* 800CD764 global */ extern UNK_TYPE TRKTargetContinue(UNK_TYPE...);
// ======================= __mem.c ====================================================
/* 800053D0 global */ extern void* memset(void* dst, int val, size_t n);
/* 80005400 global */ extern void __fill_mem(void* dst, int val, unsigned long n);
/* 800054C4 global */ extern void* memcpy(void* dst, const void* src, size_t n);
// ======================= __va_arg.c =================================================
/* 800CD798 global */ // extern void* __va_arg(va_list ap, _va_arg_type type);
// ======================= global_destructor_chain.c ==================================
/* 800CD88C global */ extern void __destroy_global_chain(void);
// ======================= runtime.c ================================================== // file is handwritten asm
/* 800CD8D4 global */ extern unsigned long __cvt_fp2unsigned(register double d);
/* 800CD930 global */ extern void __div2u(void);
/* 800CDA1C global */ extern void __div2i(void);
/* 800CDB54 global */ extern void __mod2u(void);
/* 800CDC38 global */ extern void __mod2i(void);
/* 800CDD44 global */ extern void __shl2i(void);
/* 800CDD68 global */ extern void __shr2u(void);
/* 800CDD8C global */ extern void __shr2i(void);
/* 800CDDB4 global */ extern void __cvt_sll_dbl(void);
/* 800CDE64 global */ extern void __cvt_sll_flt(void);
/* 800CDF18 global */ extern void __cvt_dbl_usll(void);
// ======================= abort_exit.c ===============================================
/* 800CDFE4 global */ extern UNK_TYPE exit(UNK_TYPE...);
// ======================= ansi_files.c ===============================================
// ======================= ansi_fp.c ==================================================
/* 800CE0F0 global */ extern void __num2dec(const decform* f, double x, decimal* d);
// ======================= buffer_io.c ================================================
/* 800CE4A4 global */ extern int __flush_buffer(FILE* file, size_t* bytes_flushed);
/* 800CE570 global */ extern void __prep_buffer(FILE* file);
// ======================= critical_regions.ppc_eabi.c ================================
/* 800CE5A4 global */ extern void __kill_critical_regions(void);
// ======================= ctype.c ====================================================
/* 800CE5A8 global */ extern UNK_TYPE toupper(UNK_TYPE...);
/* 800CE5D0 global */ extern UNK_TYPE tolower(UNK_TYPE...);
// ======================= direct_io.c ================================================
/* 800CE5F8 global */ extern size_t fwrite(const void* ptr, size_t memb_size, size_t num_memb, FILE* file);
// ======================= errno.c ====================================================
// ======================= mbstring.c =================================================
/* 800CE8D4 global */ extern size_t wcstombs(char* s, const wchar_t* pwcs, size_t n);
// ======================= mem.c ======================================================
/* 800CE910 global */ extern int memcmp(const void* src1, const void* src2, size_t n);
/* 800CE954 global */ extern void* memchr(const void* src, int val, size_t n);
/* 800CE980 global */ extern void* memmove(void* dst, const void* src, size_t n);
// ======================= mem_funcs.c ================================================
/* 800CEA5C global */ extern void __copy_longs_rev_unaligned(void* dst, const void* src, unsigned long n);
/* 800CEB0C global */ extern void __copy_longs_unaligned(void* dst, const void* src, unsigned long n);
/* 800CEBD0 global */ extern void __copy_longs_rev_aligned(void* dst, const void* src, unsigned long n);
/* 800CEC7C global */ extern void __copy_longs_aligned(void* dst, const void* src, unsigned long n);
// ======================= misc_io.c ==================================================
/* 800CED38 global */ extern void __stdio_atexit(void);
// ======================= printf.c ===================================================
/* 800CED3C global */ extern int sprintf(char* s, const char* format, ...);
/* 800CEE10 global */ extern int vsprintf(char* s, const char* format, va_list arg);
/* 800CEE88 global */ extern int vprintf(const char* format, va_list arg);
/* 800CEF04 global */ extern void* __StringWrite(void* osc, const char* Buffer, size_t NumChars);
/* 800CEF70 global */ extern void* __FileWrite(void* File, const char* Buffer, size_t NumChars);
/* 800CEFC8 local  */ // extern int __pformatter(void *(*WriteProc)(void*, const char*, size_t), void* WriteProcArg,
                      // const char* format_str, va_list arg);
/* 800CF5F8 local  */ // extern char* float2str(long double num, char* buff, print_format format);
/* 800CFC30 local  */ // extern void round_decimal(decimal* dec, int new_length);
/* 800CFD64 local  */ // extern char* longlong2str(long long num, char* buff, print_format format);
/* 800D0044 local  */ // extern char* long2str(long num, char* buff, print_format format);
/* 800D0268 local  */ // extern const char* parse_format(const char* format_string, va_list* arg, print_format* format);
// ======================= scanf.c ====================================================
/* 800D0740 global */ extern int __StringRead(void* isc, int ch, int Action);
// ======================= string.c ===================================================
/* 800D07D0 global */ extern char* strchr(const char* str, int chr);
/* 800D0800 global */ extern int strncmp(const char* str1, const char* str2, size_t n);
/* 800D0840 global */ extern int strcmp(const char* str1, const char* str2);
/* 800D0964 global */ extern char* strncpy(char* dst, const char* src, size_t n);
/* 800D09A8 global */ extern char* strcpy(char* dst, const char* src);
/* 800D0A5C global */ extern size_t strlen(const char* str);
// ======================= strtoul.c ==================================================
/* 800D0A7C global */ extern int atoi(const char* str);
/* 800D0B40 global */ extern u32 __strtoul(int base, int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg,
                                           int* chars_scanned, int* negative, int* overflow);
// ======================= uart_console_io.c ==========================================
/* 800D0E88 global */ extern int __close_console(__file_handle handle);
/* 800D0E90 global */ extern int __write_console(__file_handle handle, unsigned char* buffer, size_t* count,
                                                 __ref_con ref_con);
/* 800D0F28 global */ extern int __read_console(__file_handle handle, unsigned char* buffer, size_t* count,
                                                __ref_con ref_con);
// ======================= float.c ====================================================
// ======================= wchar_io.c =================================================
/* 800D1008 global */ extern int fwide(FILE* stream, int mode);
// ======================= e_asin.c ===================================================
/* 800D1088 weak   */ // extern UNK_TYPE fabs__Fd(UNK_TYPE...);
// ======================= e_pow.c ====================================================
/* 800D1090 global */ extern f64 __ieee754_pow(f64 x, f64 y);
/* 800D18A8 weak   */ // extern UNK_TYPE scalbn(UNK_TYPE...);
// ======================= fminmaxdim.c ===============================================
/* 800D18C8 weak   */ // extern UNK_TYPE __fpclassifyd__Fd(UNK_TYPE...);
// ======================= s_ceil.c ===================================================
/* 800D1948 global */ extern f64 ceil(f64 x);
// ======================= s_copysign.c ===============================================
/* 800D1AB0 global */ extern f64 copysign(f64 x, f64 y);
// ======================= s_floor.c ==================================================
/* 800D1ADC global */ extern f64 floor(f64 x);
// ======================= s_frexp.c ==================================================
/* 800D1C48 global */ extern f64 frexp(f64 x, int* eptr);
// ======================= s_ldexp.c ==================================================
/* 800D1CE4 global */ extern f64 ldexp(f64 x, int n);
// ======================= w_pow.c ====================================================
/* 800D1E5C global */ extern f64 pow(f64 x, f64 y);
// ======================= hyperbolicsf.c =============================================
/* 800D1E7C weak   */ // extern UNK_TYPE fabsf__Ff(UNK_TYPE...);
// ======================= log10f.c ===================================================
/* 800D1E84 global */ extern f32 log10f(f32 x);
// ======================= trigf.c ====================================================
/* 800D2058 global */ extern f32 tanf(f32 x);
/* 800D209C weak   */ // extern UNK_TYPE cos__Ff(UNK_TYPE...);
/* 800D20BC weak   */ // extern UNK_TYPE sin__Ff(UNK_TYPE...);
/* 800D20DC global */ extern f32 cosf(f32 x);
/* 800D2270 global */ extern f32 sinf(f32 x);
/* 800D2414 local  */ // extern UNK_TYPE __sinit_trigf_c(UNK_TYPE...);
// ======================= math_inlines.c =============================================
/* 800D2444 global */ extern f64 sqrt(f64 x);
// ======================= common_float_tables.c ======================================
// ======================= AmcExi2Stubs.c =============================================
/* 800D24D4 global */ extern UNK_TYPE EXI2_Init(UNK_TYPE...);
/* 800D24D8 global */ extern UNK_TYPE EXI2_EnableInterrupts(UNK_TYPE...);
/* 800D24DC global */ extern UNK_TYPE EXI2_Poll(UNK_TYPE...);
/* 800D24E4 global */ extern UNK_TYPE EXI2_ReadN(UNK_TYPE...);
/* 800D24EC global */ extern UNK_TYPE EXI2_WriteN(UNK_TYPE...);
/* 800D24F4 global */ extern UNK_TYPE EXI2_Reserve(UNK_TYPE...);
/* 800D24F8 global */ extern UNK_TYPE EXI2_Unreserve(UNK_TYPE...);
/* 800D24FC global */ extern UNK_TYPE AMC_IsStub(UNK_TYPE...);
// ======================= DebuggerDriver.c ===========================================
/* 800D2504 global */ extern UNK_TYPE DBClose(UNK_TYPE...);
/* 800D2508 global */ extern UNK_TYPE DBOpen(UNK_TYPE...);
/* 800D250C global */ extern UNK_TYPE DBWrite(UNK_TYPE...);
/* 800D276C global */ extern UNK_TYPE DBRead(UNK_TYPE...);
/* 800D27F8 global */ extern UNK_TYPE DBQueryData(UNK_TYPE...);
/* 800D2894 global */ extern UNK_TYPE DBInitInterrupts(UNK_TYPE...);
/* 800D28E8 global */ extern UNK_TYPE DBInitComm(UNK_TYPE...);
/* 800D2960 local  */ // extern UNK_TYPE DBGHandler(UNK_TYPE...);
/* 800D29A0 local  */ // extern UNK_TYPE MWCallback(UNK_TYPE...);
/* 800D29DC local  */ // extern UNK_TYPE DBGReadStatus(UNK_TYPE...);
/* 800D2A88 local  */ // extern UNK_TYPE DBGWrite(UNK_TYPE...);
/* 800D2B64 local  */ // extern UNK_TYPE DBGRead(UNK_TYPE...);
/* 800D2C40 local  */ // extern UNK_TYPE DBGReadMailbox(UNK_TYPE...);
/* 800D2CEC local  */ // extern UNK_TYPE DBGEXIImm(UNK_TYPE...);
// ======================= odenotstub.c ===============================================
/* 800D2F84 weak   */ // extern UNK_TYPE Hu_IsStub(UNK_TYPE...);

#endif
