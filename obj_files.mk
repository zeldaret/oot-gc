# Linker order for every file, passed to the Metrowerks linker.

O_FILES :=                                  \
    $(BUILD_DIR)/asm/xlCoreGCN.o            \
    $(BUILD_DIR)/src/xlPostGCN.o            \
    $(BUILD_DIR)/asm/xlFileGCN.o            \
    $(BUILD_DIR)/src/xlList.o               \
    $(BUILD_DIR)/src/xlHeap.o               \
    $(BUILD_DIR)/asm/xlObject.o             \
    $(BUILD_DIR)/src/simGCN.o               \
    $(BUILD_DIR)/src/movie.o                \
    $(BUILD_DIR)/asm/THPPlayer.o            \
    $(BUILD_DIR)/asm/THPAudioDecode.o       \
    $(BUILD_DIR)/asm/THPDraw.o              \
    $(BUILD_DIR)/asm/THPRead.o              \
    $(BUILD_DIR)/asm/THPVideoDecode.o       \
    $(BUILD_DIR)/asm/mcardGCN.o             \
    $(BUILD_DIR)/src/codeGCN.o              \
    $(BUILD_DIR)/src/soundGCN.o             \
    $(BUILD_DIR)/asm/frame.o                \
    $(BUILD_DIR)/src/system.o               \
    $(BUILD_DIR)/src/cpu.o                  \
    $(BUILD_DIR)/src/pif.o                  \
    $(BUILD_DIR)/src/ram.o                  \
    $(BUILD_DIR)/src/rom.o                  \
    $(BUILD_DIR)/src/rdp.o                  \
    $(BUILD_DIR)/src/rdb.o                  \
    $(BUILD_DIR)/src/rsp.o                  \
    $(BUILD_DIR)/src/mips.o                 \
    $(BUILD_DIR)/src/disk.o                 \
    $(BUILD_DIR)/src/flash.o                \
    $(BUILD_DIR)/src/sram.o                 \
    $(BUILD_DIR)/src/audio.o                \
    $(BUILD_DIR)/src/video.o                \
    $(BUILD_DIR)/src/serial.o               \
    $(BUILD_DIR)/src/library.o              \
    $(BUILD_DIR)/src/peripheral.o           \
    $(BUILD_DIR)/asm/_frameGCNcc.o          \
    $(BUILD_DIR)/asm/_buildtev.o            \
    $(BUILD_DIR)/asm/PPCArch.o              \
    $(BUILD_DIR)/asm/OS.o                   \
    $(BUILD_DIR)/asm/OSAlarm.o              \
    $(BUILD_DIR)/asm/OSAlloc.o              \
    $(BUILD_DIR)/asm/OSArena.o              \
    $(BUILD_DIR)/asm/OSAudioSystem.o        \
    $(BUILD_DIR)/asm/OSCache.o              \
    $(BUILD_DIR)/asm/OSContext.o            \
    $(BUILD_DIR)/asm/OSError.o              \
    $(BUILD_DIR)/asm/OSFont.o               \
    $(BUILD_DIR)/asm/OSInterrupt.o          \
    $(BUILD_DIR)/asm/OSLink.o               \
    $(BUILD_DIR)/asm/OSMessage.o            \
    $(BUILD_DIR)/asm/OSMemory.o             \
    $(BUILD_DIR)/asm/OSMutex.o              \
    $(BUILD_DIR)/asm/OSReboot.o             \
    $(BUILD_DIR)/asm/OSReset.o              \
    $(BUILD_DIR)/asm/OSResetSW.o            \
    $(BUILD_DIR)/asm/OSRtc.o                \
    $(BUILD_DIR)/asm/OSSync.o               \
    $(BUILD_DIR)/asm/OSThread.o             \
    $(BUILD_DIR)/asm/OSTime.o               \
    $(BUILD_DIR)/asm/__start.o              \
    $(BUILD_DIR)/asm/__ppc_eabi_init.o      \
    $(BUILD_DIR)/asm/EXIBios.o              \
    $(BUILD_DIR)/asm/EXIUart.o              \
    $(BUILD_DIR)/asm/SIBios.o               \
    $(BUILD_DIR)/asm/SISamplingRate.o       \
    $(BUILD_DIR)/asm/vi.o                   \
    $(BUILD_DIR)/asm/db.o                   \
    $(BUILD_DIR)/asm/mtx.o                  \
    $(BUILD_DIR)/asm/mtxvec.o               \
    $(BUILD_DIR)/asm/mtx44.o                \
    $(BUILD_DIR)/asm/GXInit.o               \
    $(BUILD_DIR)/asm/GXFifo.o               \
    $(BUILD_DIR)/asm/GXAttr.o               \
    $(BUILD_DIR)/asm/GXMisc.o               \
    $(BUILD_DIR)/asm/GXGeometry.o           \
    $(BUILD_DIR)/asm/GXFrameBuf.o           \
    $(BUILD_DIR)/asm/GXLight.o              \
    $(BUILD_DIR)/asm/GXTexture.o            \
    $(BUILD_DIR)/asm/GXBump.o               \
    $(BUILD_DIR)/asm/GXTev.o                \
    $(BUILD_DIR)/asm/GXPixel.o              \
    $(BUILD_DIR)/asm/GXTransform.o          \
    $(BUILD_DIR)/asm/GXPerf.o               \
    $(BUILD_DIR)/asm/Padclamp.o             \
    $(BUILD_DIR)/asm/Pad.o                  \
    $(BUILD_DIR)/asm/dvdlow.o               \
    $(BUILD_DIR)/asm/dvdfs.o                \
    $(BUILD_DIR)/asm/dvd.o                  \
    $(BUILD_DIR)/asm/dvdqueue.o             \
    $(BUILD_DIR)/asm/dvderror.o             \
    $(BUILD_DIR)/asm/dvdidutils.o           \
    $(BUILD_DIR)/asm/dvdFatal.o             \
    $(BUILD_DIR)/asm/fstload.o              \
    $(BUILD_DIR)/asm/DEMOInit.o             \
    $(BUILD_DIR)/asm/DEMOPuts.o             \
    $(BUILD_DIR)/asm/DEMOFont.o             \
    $(BUILD_DIR)/asm/DEMOPad.o              \
    $(BUILD_DIR)/asm/DEMOStats.o            \
    $(BUILD_DIR)/asm/ai.o                   \
    $(BUILD_DIR)/asm/ar.o                   \
    $(BUILD_DIR)/asm/dsp.o                  \
    $(BUILD_DIR)/asm/dsp_debug.o            \
    $(BUILD_DIR)/asm/dsp_task.o             \
    $(BUILD_DIR)/asm/CARDBios.o             \
    $(BUILD_DIR)/asm/CARDUnlock.o           \
    $(BUILD_DIR)/asm/CARDRdwr.o             \
    $(BUILD_DIR)/asm/CARDBlock.o            \
    $(BUILD_DIR)/asm/CARDDir.o              \
    $(BUILD_DIR)/asm/CARDCheck.o            \
    $(BUILD_DIR)/asm/CARDMount.o            \
    $(BUILD_DIR)/asm/CARDFormat.o           \
    $(BUILD_DIR)/asm/CARDOpen.o             \
    $(BUILD_DIR)/asm/CARDCreate.o           \
    $(BUILD_DIR)/asm/CARDRead.o             \
    $(BUILD_DIR)/asm/CARDWrite.o            \
    $(BUILD_DIR)/asm/CARDDelete.o           \
    $(BUILD_DIR)/asm/CARDStat.o             \
    $(BUILD_DIR)/asm/CARDNet.o              \
    $(BUILD_DIR)/asm/THPDec.o               \
    $(BUILD_DIR)/asm/THPAudio.o             \
    $(BUILD_DIR)/asm/texPalette.o           \
    $(BUILD_DIR)/asm/mainloop.o             \
    $(BUILD_DIR)/asm/nubevent.o             \
    $(BUILD_DIR)/asm/nubinit.o              \
    $(BUILD_DIR)/asm/msg.o                  \
    $(BUILD_DIR)/asm/msgbuf.o               \
    $(BUILD_DIR)/asm/serpoll.o              \
    $(BUILD_DIR)/asm/usr_put.o              \
    $(BUILD_DIR)/asm/dispatch.o             \
    $(BUILD_DIR)/asm/msghndlr.o             \
    $(BUILD_DIR)/asm/support.o              \
    $(BUILD_DIR)/asm/mutex_TRK.o            \
    $(BUILD_DIR)/asm/notify.o               \
    $(BUILD_DIR)/asm/flush_cache.o          \
    $(BUILD_DIR)/asm/mem_TRK.o              \
    $(BUILD_DIR)/asm/__exception.o          \
    $(BUILD_DIR)/asm/targimpl.o             \
    $(BUILD_DIR)/asm/dolphin_trk.o          \
    $(BUILD_DIR)/asm/mpc_7xx_603e.o         \
    $(BUILD_DIR)/asm/main_TRK.o             \
    $(BUILD_DIR)/asm/dolphin_trk_glue.o     \
    $(BUILD_DIR)/asm/targcont.o             \
    $(BUILD_DIR)/asm/__mem.o                \
    $(BUILD_DIR)/asm/__va_arg.o             \
    $(BUILD_DIR)/asm/global_destructor_chain.o \
    $(BUILD_DIR)/asm/runtime.o              \
    $(BUILD_DIR)/asm/abort_exit.o           \
    $(BUILD_DIR)/asm/ansi_files.o           \
    $(BUILD_DIR)/asm/ansi_fp.o              \
    $(BUILD_DIR)/asm/buffer_io.o            \
    $(BUILD_DIR)/asm/critical_regions.ppc_eabi.o \
    $(BUILD_DIR)/asm/ctype.o                \
    $(BUILD_DIR)/asm/direct_io.o            \
    $(BUILD_DIR)/asm/errno.o                \
    $(BUILD_DIR)/asm/mbstring.o             \
    $(BUILD_DIR)/asm/mem.o                  \
    $(BUILD_DIR)/asm/mem_funcs.o            \
    $(BUILD_DIR)/asm/misc_io.o              \
    $(BUILD_DIR)/asm/printf.o               \
    $(BUILD_DIR)/asm/scanf.o                \
    $(BUILD_DIR)/asm/string.o               \
    $(BUILD_DIR)/asm/strtoul.o              \
    $(BUILD_DIR)/asm/uart_console_io.o      \
    $(BUILD_DIR)/asm/float.o                \
    $(BUILD_DIR)/asm/wchar_io.o             \
    $(BUILD_DIR)/asm/e_asin.o               \
    $(BUILD_DIR)/asm/e_pow.o                \
    $(BUILD_DIR)/asm/fminmaxdim.o           \
    $(BUILD_DIR)/asm/s_ceil.o               \
    $(BUILD_DIR)/asm/s_copysign.o           \
    $(BUILD_DIR)/asm/s_floor.o              \
    $(BUILD_DIR)/asm/s_frexp.o              \
    $(BUILD_DIR)/asm/s_ldexp.o              \
    $(BUILD_DIR)/asm/w_pow.o                \
    $(BUILD_DIR)/asm/hyperbolicsf.o         \
    $(BUILD_DIR)/asm/log10f.o               \
    $(BUILD_DIR)/asm/trigf.o                \
    $(BUILD_DIR)/asm/math_inlines.o         \
    $(BUILD_DIR)/asm/common_float_tables.o  \
    $(BUILD_DIR)/asm/AmcExi2Stubs.o         \
    $(BUILD_DIR)/asm/DebuggerDriver.o       \
    $(BUILD_DIR)/asm/odenotstub.o           \
