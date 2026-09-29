// Real FOG_F* file-I/O layer (strong definitions win over Fog.cpp's weak
// stubs). Backed by squall's SFile API; with WHOA_SFILE_MODE=STORMLIB the
// SFile calls go through the vendored StormLib, so FOG_FOpenFile can serve
// files straight out of the retail MPQs — exactly what the decompiled
// DATATBLS_* loaders and the level generator need.
//
// The D2Server module registers the data archives through the D2FOG_AddData*
// helper (FogFileIO.h) in highest-priority-first order; every open searches
// the list in that order, mirroring the D2GS "global archive stack" model.
// For retail 1.14d that is: Patch_D2.mpq (1.14 overlay, wins), d2data.mpq,
// d2exp.mpq.
//
// The squall SFile entry points are declared locally (not via squall
// headers) so this TU only ever sees D2MOOPortable's HSFILE__/HSARCHIVE__
// definitions from StormHandles.h — squall's Handle.hpp would redeclare the
// same struct tags and trip a redefinition error.

#include <Fog.h>

#include <cstdint>
#include <cstdio>

#include <FogFileIO.h>

// ---------------------------------------------------------------------
// squall SFile API (StormLib-backed when WHOA_SFILE_MODE=STORMLIB).
// Signatures must match squall's storm/file/SFile.cpp exactly (they mangle
// to the same symbols; STORMAPI == __stdcall == empty on Linux).
// ---------------------------------------------------------------------

extern int32_t SFileOpenArchive(const char* archivename, int32_t priority, uint32_t flags, HSARCHIVE* handle);
extern int32_t SFileCloseArchive(HSARCHIVE handle);
extern int32_t SFileOpenFileEx(HSARCHIVE archivehandle, const char* filename, uint32_t flags, HSFILE* handle);
extern int32_t SFileReadFile(HSFILE handle, void* buffer, uint32_t bytestoread, uint32_t* bytesread, void* overlapped);
extern uint32_t SFileGetFileSize(HSFILE handle, uint32_t* filesizehigh);
extern uint32_t SFileSetFilePointer(HSFILE handle, int32_t distancetomove, int32_t* distancetomovehigh, uint32_t movemethod);
extern int32_t SFileCloseFile(HSFILE handle);

// ---------------------------------------------------------------------
// Data archive stack (highest priority first)
// ---------------------------------------------------------------------

namespace {
constexpr int kMaxDataArchives = 8;
HSARCHIVE g_dataArchives[kMaxDataArchives] = {};
int g_dataArchiveCount = 0;
} // namespace

// Fog.#10102
BOOL FOG_FOpenFile(const char* szFile, HSFILE* pFileHandle) {
	if (pFileHandle == nullptr) {
		return FALSE;
	}

	*pFileHandle = nullptr;

	for (int i = 0; i < g_dataArchiveCount; ++i) {
		if (SFileOpenFileEx(g_dataArchives[i], szFile, 0, pFileHandle)) {
			return TRUE;
		}
		*pFileHandle = nullptr;
	}

	fprintf(stderr, "[FogFileIO] FOpenFile FAILED: '%s'\n", szFile);
	return FALSE;
}

// Fog.#10103
void FOG_FCloseFile(HSFILE pFile) {
	if (pFile != nullptr) {
		SFileCloseFile(pFile);
	}
}

// Fog.#10104
BOOL FOG_FReadFile(HSFILE pFile, void* pBuffer, size_t nSize, int* nBytesRead, uint32_t a5, uint32_t a6, uint32_t a7) {
	uint32_t nBytesReadU32 = 0;
	const int32_t nResult = SFileReadFile(pFile, pBuffer, static_cast<uint32_t>(nSize), &nBytesReadU32, nullptr);
	if (nBytesRead != nullptr) {
		*nBytesRead = static_cast<int32_t>(nBytesReadU32);
	}

	return (BOOL)nResult;
}

// Fog.#10105
uint32_t FOG_FGetFileSize(HSFILE pFileHandle, size_t* lpFileSizeHigh) {
	uint32_t nFileSizeHigh = 0;
	const uint32_t nFileSizeLow = SFileGetFileSize(pFileHandle, lpFileSizeHigh != nullptr ? &nFileSizeHigh : nullptr);
	if (lpFileSizeHigh != nullptr) {
		*lpFileSizeHigh = nFileSizeHigh;
	}

	return nFileSizeLow;
}

// Fog.#10106
size_t FOG_FSetFilePointer(HSFILE hFile, int32_t lDistanceToMove, int32_t* lpDistanceToMoveHigh, uint32_t dwMoveMethod) {
	return SFileSetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
}

// ---------------------------------------------------------------------
// D2FOG_* module-facing archive helpers
// ---------------------------------------------------------------------

extern "C" int32_t D2FOG_AddDataArchive(const char* szMpqPath, void** ppArchiveHandle) {
	if (ppArchiveHandle != nullptr) {
		*ppArchiveHandle = nullptr;
	}

	if (g_dataArchiveCount >= kMaxDataArchives) {
		fprintf(stderr, "[FogFileIO] too many data archives (max %d); ignoring '%s'\n", kMaxDataArchives, szMpqPath);
		return 0;
	}

	HSARCHIVE hArchive = nullptr;
	// The real D2GS opens archives with flags=2 (SFILE_ARCHIVE_ENABLE_OVERLAPPED),
	// but this vendored StormLib errors on that flag on Linux; flags=0 works.
	const int32_t nResult = SFileOpenArchive(szMpqPath, 0, 0, &hArchive);
	if (!nResult || hArchive == nullptr) {
		return 0;
	}

	g_dataArchives[g_dataArchiveCount++] = hArchive;
	if (ppArchiveHandle != nullptr) {
		*ppArchiveHandle = hArchive;
	}

	return 1;
}

extern "C" void D2FOG_CloseDataArchive(void) {
	for (int i = 0; i < g_dataArchiveCount; ++i) {
		SFileCloseArchive(g_dataArchives[i]);
	}
	g_dataArchiveCount = 0;
}