// Module-facing helpers for the real FOG_F* file-I/O layer
// (implemented in src/File/FogFileIO.cpp, backed by squall's StormLib
// SFile API when WHOA_SFILE_MODE=STORMLIB).
//
// The wholesale engine host (D2Server module) registers the retail data
// archives through D2FOG_AddDataArchive in highest-priority-first order;
// FOG_FOpenFile and friends then serve every file the decompiled
// D2Game/D2Common code asks for (excel txt tables at boot, DS1/DT1 for level
// generation later) straight out of the MPQs, no loose files required.
// 1.14d order: Patch_D2.mpq, d2data.mpq, d2exp.mpq.
#pragma once

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

// Open an MPQ archive and append it to the data archive stack searched by
// FOG_FOpenFile (highest priority first). Returns 1 on success and stores
// the opaque archive handle in *ppArchiveHandle (valid until
// D2FOG_CloseDataArchive).
int32_t D2FOG_AddDataArchive(const char* szMpqPath, void** ppArchiveHandle);

// Close every archive registered by D2FOG_AddDataArchive (if any).
void D2FOG_CloseDataArchive(void);

#ifdef __cplusplus
}
#endif