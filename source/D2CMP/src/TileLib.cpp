// TODO: Rewrite using D2CMPd.dll from 1.07 Beta

// TileLib.cpp - real D2CMP tile-library subsystem (DT1 load + lookup).
//
// Strong definitions for D2CMP.#10077/78/79/81/82/85/87/88; D2CMP.cpp
// (stubbed via D2FUNC_DLL_STUB) provides strong stubs for the remaining
// non-tile D2CMP exports. TileLib's strong implementations satisfy the
// tile functions directly.
//
// Ground truth: retail 1.14d D2CMP.dll (TileLib.cpp @0x100163D0, internal
// loader 0x10016870, hash builder 0x10015B70, hash insert 0x1000BF00, per-slot
// lookup 0x1000C170, GetTileFileSize 0x10014580).
//
// The D2GS consumes the tile library as pure *metadata*: the level generator
// (D2Common DRLG) asks for candidate tiles with (nType, nStyle, nSequence)
// and reads size/flags/etc. off the returned D2TileLibraryEntryStrc. Tile
// pixel blocks are never needed on the server.
//
// DT1 layout (validated against real floor.dt1 files from d2data.mpq):
//   header (0x114 bytes): dwVersion@0x00 (== 7), dwFlags@0x04,
//       szLibraryName[260]@0x08, dwNumTiles@0x10C, dwTileEntryOffset@0x110.
//   tile entries: 96 bytes each, starting at dwTileEntryOffset (0x114).
//
// Lookup hash: 128 buckets; bucket index = (int8)(2*nSequence - nType +
// nStyle) in byte arithmetic; each bucket chains D2TileLibraryHashNodeStrc
// keyed by (nStyle, nSequence, nType); each node holds a pRef chain of every
// tile that shares the key (the caller picks by rarity via
// D2CMP_10081_GetTileRarity).

#include "TileLib.h"

#include <D2CMP.h>
#include <Fog.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>

// ---------------------------------------------------------------------------
// Constants (from the retail 1.14d DT1 parser)
// ---------------------------------------------------------------------------
namespace {

constexpr int32_t kDt1Version = 7;           // DT1 signature
constexpr int32_t kDt1HeaderSize = 0x114;    // header through dwTileEntryOffset
constexpr int32_t kDt1TileEntrySize = 0x60;  // 96-byte tile entry
constexpr int32_t kMaxTileLibraries = 32;    // "MAX_TILEPROJECT": slot array size
constexpr int32_t kTileEntryReserved0 = 0x54; // must be zero in retail files
constexpr int32_t kTileEntryReserved1 = 0x5C; // must be zero in retail files
constexpr int32_t kTileEntryNameLink = 0x58; // retail backlink to library name

constexpr int32_t kHeaderFlagNeedsFinalize = 0x2; // fresh file image
constexpr int32_t kHeaderFlagFinalized = 0x4;     // entry offset patched

// Retail 0x1013F9E4: list of every tile library loaded this session, keyed by
// file path, so repeated LoadTileLibrarySlot calls share one hash block.
D2TileRecordStrc* g_pTileLibraryList = nullptr;

// Retail 0x10014580. Open the DT1 and return the size of its load image:
// 96 * dwTileEntryOffset + 0x114 (header + tile entries; tile block data is
// not needed on the server). Returns 0 when the file is missing/unreadable.
int32_t GetTileFileSize(const char* szFileName) {
	HSFILE hFile = nullptr;
	if (!FOG_FOpenFile(szFileName, &hFile)) {
		fprintf(stderr, "[D2CMP] GetTileFileSize: cannot open '%s'\n", szFileName);
		return 0;
	}

	const uint32_t dwFileSize = FOG_FGetFileSize(hFile, nullptr);
	if (dwFileSize < kDt1HeaderSize) {
		fprintf(stderr, "[D2CMP] GetTileFileSize: '%s' is only %u bytes\n", szFileName, dwFileSize);
		FOG_FCloseFile(hFile);
		return 0;
	}

	uint8_t header[kDt1HeaderSize] = {};
	int nBytesRead = 0;
	const BOOL bRead = FOG_FReadFile(hFile, header, sizeof(header), &nBytesRead, 0, 0, 0);
	FOG_FCloseFile(hFile);
	if (!bRead || nBytesRead < kDt1HeaderSize) {
		fprintf(stderr, "[D2CMP] GetTileFileSize: failed to read '%s'\n", szFileName);
		return 0;
	}

	const int32_t dwTileEntryOffset = *reinterpret_cast<const int32_t*>(&header[0x110]);
	if (dwTileEntryOffset <= 0) {
		fprintf(stderr, "[D2CMP] GetTileFileSize: '%s' has bogus tile entry offset %d\n", szFileName, dwTileEntryOffset);
		return 0;
	}

	const int64_t nImageSize = 96 * static_cast<int64_t>(dwTileEntryOffset) + kDt1HeaderSize;
	if (nImageSize > INT32_MAX) {
		fprintf(stderr, "[D2CMP] GetTileFileSize: '%s' image size %lld is too large\n", szFileName, static_cast<long long>(nImageSize));
		return 0;
	}

	return static_cast<int32_t>(nImageSize);
}

// Retail 0x1000BF00. Insert one tile entry into the 128-bucket hash, chaining
// nodes by (nStyle, nSequence, nType) and collecting every entry that shares
// the key in the node's pRef chain.
void InsertTileIntoHash(D2TileLibraryHashStrc* pHash, D2TileLibraryEntryStrc* pEntry) {
	// Retail computes the bucket from an 8-bit wrapping expression and masks
	// the result to the 128-bucket range: index = (2*seq - type + style) & 0x7F.
	// Values that go negative in signed math (e.g. seq 0, type 8, style 3 -> -5)
	// wrap back into 0..127 instead of being dropped; the "out of range" branch
	// in the retail assembly (1000BF7D) is unreachable once the mask is applied.
	const uint8_t nHashIndex = static_cast<uint8_t>(2 * (uint8_t)(pEntry->nSequence & 0xFF) -
	                                                (uint8_t)(pEntry->nType & 0xFF) +
	                                                (uint8_t)(pEntry->nStyle & 0xFF)) &
	                           0x7F;
	D2TileLibraryHashNodeStrc** ppBucket = &pHash->pNodes[nHashIndex];

	// Find an existing node with the same key.
	D2TileLibraryHashNodeStrc* pNode = *ppBucket;
	while (pNode != nullptr &&
	       !(pNode->nSequence == pEntry->nSequence &&
	         pNode->nStyle == pEntry->nStyle &&
	         pNode->nType == pEntry->nType)) {
		pNode = pNode->pPrev;
	}

	if (pNode != nullptr) {
		// Key exists: add this entry to the node's reference chain unless it
		// is already there (dedup by tile pointer).
		for (D2TileLibraryHashRefStrc* pRef = pNode->pRef; pRef != nullptr; pRef = pRef->pPrev) {
			if (pRef->pTile == pEntry) {
				return;
			}
		}

		D2TileLibraryHashRefStrc* pNewRef = (D2TileLibraryHashRefStrc*)D2_CALLOC_STRC(D2TileLibraryHashRefStrc);
		D2_ASSERT(pNewRef != nullptr);
		pNewRef->pTile = pEntry;
		pNewRef->pPrev = pNode->pRef;
		pNode->pRef = pNewRef;
		return;
	}

	// New key: allocate a hash node and its first reference.
	D2TileLibraryHashNodeStrc* pNewNode = (D2TileLibraryHashNodeStrc*)D2_CALLOC_STRC(D2TileLibraryHashNodeStrc);
	D2_ASSERT(pNewNode != nullptr);
	pNewNode->nSequence = pEntry->nSequence;
	pNewNode->nStyle = pEntry->nStyle;
	pNewNode->nType = pEntry->nType;
	pNewNode->pPrev = *ppBucket;

	D2TileLibraryHashRefStrc* pNewRef = (D2TileLibraryHashRefStrc*)D2_CALLOC_STRC(D2TileLibraryHashRefStrc);
	D2_ASSERT(pNewRef != nullptr);
	pNewRef->pTile = pEntry;
	pNewRef->pPrev = nullptr;
	pNewNode->pRef = pNewRef;

	*ppBucket = pNewNode;
}

// Retail 0x10015B70. Allocate the (zeroed) hash table and index every tile
// entry of the image.
D2TileLibraryHashStrc* BuildTileLibraryHash(const D2TileLibraryHeaderStrc* pHeader, const uint8_t* pTileEntries) {
	D2TileLibraryHashStrc* pHash = (D2TileLibraryHashStrc*)D2_CALLOC_STRC(D2TileLibraryHashStrc);
	D2_ASSERT(pHash != nullptr);

	for (int32_t i = 0; i < pHeader->nTiles; ++i) {
		InsertTileIntoHash(pHash, (D2TileLibraryEntryStrc*)(pTileEntries + (size_t)i * kDt1TileEntrySize));
	}

	return pHash;
}

// Retail 0x10016870. Load (or reuse) the tile library for szFileName and
// publish its hash block through *ppOut.
void InternalLoadTileLibrarySlot(D2TileLibraryHashStrc** ppOut, const char* szFileName) {
	// Reuse an already-loaded library for the same path.
	for (D2TileRecordStrc* pRec = g_pTileLibraryList; pRec != nullptr; pRec = pRec->pPrev) {
		if (std::strcmp(pRec->szLibraryName, szFileName) == 0) {
			*ppOut = pRec->pHashBlock;
			return;
		}
	}

	const int32_t nImageSize = GetTileFileSize(szFileName);
	if (nImageSize == 0) {
		fprintf(stderr, "[D2CMP] LoadTileLibrarySlot: cannot load '%s'\n", szFileName);
		*ppOut = nullptr;
		return;
	}

	HSFILE hFile = nullptr;
	if (!FOG_FOpenFile(szFileName, &hFile)) {
		fprintf(stderr, "[D2CMP] LoadTileLibrarySlot: cannot open '%s'\n", szFileName);
		*ppOut = nullptr;
		return;
	}

	const uint32_t dwFileSize = FOG_FGetFileSize(hFile, nullptr);
	const uint32_t nAllocSize = std::min<uint32_t>(static_cast<uint32_t>(nImageSize), dwFileSize);

	uint8_t* pImage = (uint8_t*)D2_ALLOC(nAllocSize);
	std::memset(pImage, 0x00, nAllocSize);

	int nBytesRead = 0;
	const BOOL bRead = FOG_FReadFile(hFile, pImage, nAllocSize, &nBytesRead, 0, 0, 0);
	FOG_FCloseFile(hFile);
	if ((!bRead && nBytesRead < kDt1HeaderSize) || nBytesRead < kDt1HeaderSize) {
		fprintf(stderr, "[D2CMP] LoadTileLibrarySlot: failed to read '%s' (%d of %u bytes)\n", szFileName, nBytesRead, nAllocSize);
		*ppOut = nullptr;
		return;
	}

	// Validate the in-memory DT1 header.
	D2TileLibraryHeaderStrc* pHeader = (D2TileLibraryHeaderStrc*)pImage;
	if (pHeader->dwVersion != kDt1Version) {
		fprintf(stderr, "[D2CMP] LoadTileLibrarySlot: '%s' has unsupported DT1 version %d\n", szFileName, pHeader->dwVersion);
		*ppOut = nullptr;
		return;
	}
	if ((pHeader->dwFlags & kHeaderFlagNeedsFinalize) == 0) {
		fprintf(stderr, "[D2CMP] LoadTileLibrarySlot: '%s' flags 0x%X lack the finalize bit\n", szFileName, pHeader->dwFlags);
		*ppOut = nullptr;
		return;
	}

	const int32_t nTiles = pHeader->nTiles;
	if (nTiles < 0 || (int64_t)kDt1HeaderSize + (int64_t)nTiles * kDt1TileEntrySize > nBytesRead) {
		fprintf(stderr, "[D2CMP] LoadTileLibrarySlot: '%s' declares %d tiles but only %d bytes were read\n", szFileName, nTiles, nBytesRead);
		*ppOut = nullptr;
		return;
	}

	// The file's tile entries start at dwTileStart_pFirst *relative to the
	// image base* (0x114 in v7 files). Retail patches the field to an absolute
	// pointer; this 64-bit port keeps the field relative (int32 cannot hold a
	// pointer) and computes the real base here instead.
	const uint8_t* pTileEntries = pImage + static_cast<uint32_t>(pHeader->dwTileStart_pFirst);

	// Retail 0x10015A40 also records the source path in the header and links
	// every entry back to it (entry+0x58). Nothing the server builds reads
	// either backlink, and the 32-bit field cannot hold a 64-bit pointer, so
	// only the reserved-word validation is kept.
	for (int32_t i = 0; i < nTiles; ++i) {
		const uint8_t* pEntry = pTileEntries + (size_t)i * kDt1TileEntrySize;
		if (*reinterpret_cast<const int32_t*>(pEntry + kTileEntryReserved0) != 0 ||
		    *reinterpret_cast<const int32_t*>(pEntry + kTileEntryReserved1) != 0) {
			fprintf(stderr, "[D2CMP] LoadTileLibrarySlot: '%s' entry %d has non-zero reserved fields\n", szFileName, i);
			break;
		}
	}

	D2TileLibraryHashStrc* pHash = BuildTileLibraryHash(pHeader, pTileEntries);

	// Register the library in the global list so a second load of the same
	// path reuses this hash block (retail allocates 0x110-byte records).
	D2TileRecordStrc* pRecord = (D2TileRecordStrc*)D2_CALLOC_STRC(D2TileRecordStrc);
	D2_ASSERT(pRecord != nullptr);
	std::memset(pRecord->szLibraryName, 0x00, sizeof(pRecord->szLibraryName));
	std::strcpy(pRecord->szLibraryName, szFileName);
	pRecord->pLibrary = pHeader;
	pRecord->pHashBlock = pHash;
	pRecord->pPrev = g_pTileLibraryList;
	g_pTileLibraryList = pRecord;

	*ppOut = pHash;
	fprintf(stderr, "[D2CMP] loaded tile library '%s' (%d tiles)\n", szFileName, nTiles);
}

// Retail 0x1000C170: one hash block's worth of candidates. Matches nodes by
// the full (nStyle, nSequence, nType) triple and appends the node's whole
// reference chain (up to nTileListSize entries). Returns the count appended.
int32_t GetTilesFromHash(D2TileLibraryHashStrc* pHash, int32_t nType, int32_t nStyle, int32_t nSequence,
                         D2TileLibraryEntryStrc** pTileList, int32_t nTileListSize) {
	D2_ASSERT(pHash != nullptr);
	D2_ASSERT(pTileList != nullptr);
	if (nTileListSize == 0) {
		return 0;
	}

	// Same masking as InsertTileIntoHash: (2*seq - type + style) computed in
	// 8-bit wrapping arithmetic, masked with 0x7F into the 128-bucket range.
	const uint8_t nHashIndex = static_cast<uint8_t>(2 * (uint8_t)(nSequence & 0xFF) -
	                                                (uint8_t)(nType & 0xFF) +
	                                                (uint8_t)(nStyle & 0xFF)) &
	                           0x7F;

	int32_t nFound = 0;
	for (D2TileLibraryHashNodeStrc* pNode = pHash->pNodes[nHashIndex]; pNode != nullptr; pNode = pNode->pPrev) {
		if (pNode->nSequence == nSequence && pNode->nStyle == nStyle && pNode->nType == nType) {
			for (D2TileLibraryHashRefStrc* pRef = pNode->pRef; pRef != nullptr && nFound < nTileListSize; pRef = pRef->pPrev) {
				pTileList[nFound++] = pRef->pTile;
			}
			return nFound;
		}
	}

	return 0;
}

} // namespace

// ---------------------------------------------------------------------------
// D2CMP tile library exports
// ---------------------------------------------------------------------------

// D2CMP.#10077 (retail 0x10016560) - nOrientation @ 0x14
D2CMP_DLL_DECL int __stdcall D2CMP_10077_GetTileType(D2TileLibraryEntryStrc* pTileLibraryEntry) {
	D2_ASSERT(pTileLibraryEntry != nullptr);
	return pTileLibraryEntry->nType;
}

// D2CMP.#10078 (retail 0x100165A0) - nIndex @ 0x18
D2CMP_DLL_DECL int __stdcall D2CMP_10078_GetTileStyle(D2TileLibraryEntryStrc* pTileLibraryEntry) {
	D2_ASSERT(pTileLibraryEntry != nullptr);
	return pTileLibraryEntry->nStyle;
}

// D2CMP.#10079 (retail 0x100165E0) - material flags @ 0x06
D2CMP_DLL_DECL int __stdcall D2CMP_10079_GetTileFlags(D2TileLibraryEntryStrc* pTileLibraryEntry) {
	D2_ASSERT(pTileLibraryEntry != nullptr);
	return pTileLibraryEntry->nFlags;
}

// D2CMP.#10081 (retail 0x10016660) - rarity / (animated) frame @ 0x20
D2CMP_DLL_DECL int __stdcall D2CMP_10081_GetTileRarity(D2TileLibraryEntryStrc* pTileLibraryEntry) {
	D2_ASSERT(pTileLibraryEntry != nullptr);
	return pTileLibraryEntry->nRarity_Frame;
}

// D2CMP.#10082 (retail 0x100166A0) - nSubIndex @ 0x1C
D2CMP_DLL_DECL int __stdcall D2CMP_10082_GetTileSequence(D2TileLibraryEntryStrc* pTileLibraryEntry) {
	D2_ASSERT(pTileLibraryEntry != nullptr);
	return pTileLibraryEntry->nSequence;
}

// D2CMP.#10085 (retail 0x10016760) - collision info @ 0x28
D2CMP_DLL_DECL uint8_t* __stdcall D2CMP_10085_GetTileFlagArray(D2TileLibraryEntryStrc* pTileLibraryEntry) {
	D2_ASSERT(pTileLibraryEntry != nullptr);
	return pTileLibraryEntry->dwTileFlags;
}

// D2CMP.#10087 (retail 0x100163D0). Load the DT1 into the first free slot of
// the 32-slot tile library array.
D2CMP_DLL_DECL void __stdcall D2CMP_10087_LoadTileLibrarySlot(D2TileLibraryHashStrc** ppTileLibraryHash, const char* szFileName) {
	D2_ASSERT(ppTileLibraryHash != nullptr);
	D2_ASSERT(szFileName != nullptr);

	int32_t nSlot = 0;
	while (nSlot < kMaxTileLibraries && ppTileLibraryHash[nSlot] != nullptr) {
		++nSlot;
	}

	if (nSlot >= kMaxTileLibraries) {
		fprintf(stderr, "[D2CMP] LoadTileLibrarySlot: no free slot for '%s' (all %d slots in use)\n", szFileName, kMaxTileLibraries);
		D2_ASSERT(nSlot < kMaxTileLibraries); // "ii < MAX_TILEPROJECT"
		return;
	}

	InternalLoadTileLibrarySlot(&ppTileLibraryHash[nSlot], szFileName);
}

// D2CMP.#10088 (retail 0x10016490). Aggregate candidate tiles across all
// loaded library slots (slots are filled contiguously, so scanning stops at
// the first empty one). Returns the number of entries written to pTileList.
D2CMP_DLL_DECL int __stdcall D2CMP_10088_GetTiles(D2TileLibraryHashStrc** ppTileLibraryHash, int nType, int nStyle, int nSequence,
                                                  D2TileLibraryEntryStrc** pTileList, int nTileListSize) {
	D2_ASSERT(ppTileLibraryHash != nullptr);
	if (nTileListSize <= 0) {
		return 0;
	}

	int32_t nFound = 0;
	for (int32_t nSlot = 0; nSlot < kMaxTileLibraries; ++nSlot) {
		D2TileLibraryHashStrc* pHash = ppTileLibraryHash[nSlot];
		if (pHash == nullptr) {
			break;
		}

		const int32_t nGot = GetTilesFromHash(pHash, nType, nStyle, nSequence, &pTileList[nFound], nTileListSize - nFound);
		nFound += nGot;
		if (nFound >= nTileListSize) {
			break;
		}
	}

	return nFound;
}