// Txt linker tables (real implementations)
// ---------------------------------------------------------------------
// libD2Common.so's DATATBLS loaders build D2TxtLinkStrc index tables from
// the Excel tables and reference rows by code or by name:
//   * code entries (FOG_10215) go into pTbl  - "code" (first bytes) -> row
//   * text entries (FOG_10216) go into the pFirstNode double-linked list
//     of D2TxtLinkNodeStrc nodes            - row name (<=31 chars) -> row
// nLinkIndex is the row index of the record that inserted the entry
// (insertion order == row order in the loaders).
//
// Structs (Fog.h):
//   D2TxtLinkStrc     { int32_t nRecords; int32_t nAllocatedCells;
//                       D2TxtLinkTblStrc* pTbl; D2TxtLinkNodeStrc* pFirstNode; }
//   D2TxtLinkTblStrc  { union{ char szCode[4]; uint32_t dwCode; };
//                       int32_t nLinkIndex; }
//   D2TxtLinkNodeStrc { char szText[32]; int32_t nLinkIndex;
//                       D2TxtLinkNodeStrc* pPrevious; D2TxtLinkNodeStrc* pNext; }

#include <Fog.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <strings.h>

void* FOG_AllocLinker(const char* szFile, int32_t nLine) {
	return std::calloc(1, sizeof(D2TxtLinkStrc));
}

void FOG_FreeLinker(void* pLinkerV) {
	D2TxtLinkStrc* pLinker = (D2TxtLinkStrc*)pLinkerV;
	if (!pLinker) {
		return;
	}

	D2TxtLinkNodeStrc* pNode = pLinker->pFirstNode;
	while (pNode) {
		D2TxtLinkNodeStrc* pNext = pNode->pNext;
		std::free(pNode);
		pNode = pNext;
	}
	std::free(pLinker->pTbl);
	std::free(pLinker);
}

int32_t FOG_10216_AddRecordToLinkingTable(void* pBin, const char* szText) {
	D2TxtLinkStrc* pLinker = (D2TxtLinkStrc*)pBin;
	if (!pLinker || !szText) {
		return 0;
	}

	D2TxtLinkNodeStrc* pNode = (D2TxtLinkNodeStrc*)std::calloc(1, sizeof(D2TxtLinkNodeStrc));
	if (!pNode) {
		return 0;
	}

	std::strncpy(pNode->szText, szText, sizeof(pNode->szText) - 1);
	pNode->nLinkIndex = pLinker->nRecords;

	// Append to the tail of the double-linked list.
	if (pLinker->pFirstNode) {
		D2TxtLinkNodeStrc* pTail = pLinker->pFirstNode;
		while (pTail->pNext) {
			pTail = pTail->pNext;
		}
		pTail->pNext = pNode;
		pNode->pPrevious = pTail;
	} else {
		pLinker->pFirstNode = pNode;
	}

	return pLinker->nRecords++;
}

int32_t FOG_10215(void* pBin, int32_t nCode) {
	D2TxtLinkStrc* pLinker = (D2TxtLinkStrc*)pBin;
	if (!pLinker) {
		return 0;
	}

	if (!pLinker->pTbl) {
		// Same sizing rule as FOG_AddCodeAndTextToLinkingTable: a linker
		// reached after text-only registrations (FOG_10216) has nRecords > 0
		// while pTbl is still NULL; cap the initial allocation to it.
		int32_t nCap = 16;
		if (pLinker->nRecords >= nCap) {
			nCap = pLinker->nRecords * 2;
		}
		pLinker->nAllocatedCells = nCap;
		pLinker->pTbl = (D2TxtLinkTblStrc*)std::calloc((size_t)pLinker->nAllocatedCells, sizeof(D2TxtLinkTblStrc));
	} else if (pLinker->nRecords >= pLinker->nAllocatedCells) {
		const int32_t nNewCap = pLinker->nAllocatedCells * 2;
		D2TxtLinkTblStrc* pNewTbl = (D2TxtLinkTblStrc*)std::realloc(pLinker->pTbl, (size_t)nNewCap * sizeof(D2TxtLinkTblStrc));
		if (!pNewTbl) {
			return 0;
		}
		pLinker->pTbl = pNewTbl;
		pLinker->nAllocatedCells = nNewCap;
	}
	if (!pLinker->pTbl) {
		return 0;
	}

	D2TxtLinkTblStrc* pEntry = &pLinker->pTbl[pLinker->nRecords];
	pEntry->dwCode = (uint32_t)nCode;
	pEntry->nLinkIndex = pLinker->nRecords;

	return pLinker->nRecords++;
}

// Combined code+text registration used by FOG_10207 to seed identity columns.
// Adds one code entry (pTbl) AND one text node (pFirstNode list), both with
// nLinkIndex = nRecords, then increments nRecords exactly once.  FOG_10215 +
// FOG_10216 used as a pair would desync the indices (10216 would see the
// counter already incremented by 10215), so the pair must never be used when
// both representations need to agree on the same row.
int32_t FOG_AddCodeAndTextToLinkingTable(void* pBin, int32_t nCode, const char* szText) {
	D2TxtLinkStrc* pLinker = (D2TxtLinkStrc*)pBin;
	if (!pLinker || !szText) {
		return 0;
	}

	// Code entry (same growth policy as FOG_10215).  A linker may already
	// hold text-only records (FOG_10216, e.g. pTreasureClassExLinker seeded
	// by DATATBLS_CreateItemTypeTreasureClasses with ~1000 pseudo rows
	// before the treasureclassex.txt compile appends code+text entries); the
	// first code entry then starts with pTbl == NULL but nRecords > 0.  Size
	// the initial table for the existing row count so the write below stays
	// in bounds.
	if (!pLinker->pTbl) {
		int32_t nCap = 16;
		if (pLinker->nRecords >= nCap) {
			nCap = pLinker->nRecords * 2;
		}
		pLinker->nAllocatedCells = nCap;
		pLinker->pTbl = (D2TxtLinkTblStrc*)std::calloc((size_t)pLinker->nAllocatedCells, sizeof(D2TxtLinkTblStrc));
		// Backfill row indices so every slot addresses its row (text-only
		// rows stay consistent for code-table scans).
		if (pLinker->pTbl) {
			for (int32_t i = 0; i < pLinker->nRecords; ++i) {
				pLinker->pTbl[i].nLinkIndex = i;
			}
		}
	} else if (pLinker->nRecords >= pLinker->nAllocatedCells) {
		const int32_t nNewCap = pLinker->nAllocatedCells * 2;
		D2TxtLinkTblStrc* pNewTbl = (D2TxtLinkTblStrc*)std::realloc(pLinker->pTbl, (size_t)nNewCap * sizeof(D2TxtLinkTblStrc));
		if (!pNewTbl) {
			return 0;
		}
		pLinker->pTbl = pNewTbl;
		pLinker->nAllocatedCells = nNewCap;
	}
	if (!pLinker->pTbl) {
		return 0;
	}

	D2TxtLinkTblStrc* pEntry = &pLinker->pTbl[pLinker->nRecords];
	pEntry->dwCode = (uint32_t)nCode;
	pEntry->nLinkIndex = pLinker->nRecords;

	// Text node (same append as FOG_10216) sharing the same row index.
	D2TxtLinkNodeStrc* pNode = (D2TxtLinkNodeStrc*)std::calloc(1, sizeof(D2TxtLinkNodeStrc));
	if (!pNode) {
		return 0;
	}
	std::strncpy(pNode->szText, szText, sizeof(pNode->szText) - 1);
	pNode->nLinkIndex = pLinker->nRecords;

	if (pLinker->pFirstNode) {
		D2TxtLinkNodeStrc* pTail = pLinker->pFirstNode;
		while (pTail->pNext) {
			pTail = pTail->pNext;
		}
		pTail->pNext = pNode;
		pNode->pPrevious = pTail;
	} else {
		pLinker->pFirstNode = pNode;
	}

	return pLinker->nRecords++;
}

int32_t FOG_GetRowFromTxt(void* pBin, char* szText, int32_t nColumn) {
	D2TxtLinkStrc* pLinker = (D2TxtLinkStrc*)pBin;
	if (!pLinker || !szText) {
		return -1;
	}

	// Case-insensitive, and first match wins. Blizzard's own 1.14d data
	// depends on it: charstats.txt spells the innate skills 'fire bolt' and
	// 'raise skeleton' while skills.txt spells the same rows 'Fire Bolt' and
	// 'Raise Skeleton'. With a case-sensitive compare the match lands on a
	// node some reference column (sumskill/reqskill/skilldesc) appended after
	// the identity pass, whose nLinkIndex is a registration counter rather
	// than a skills.txt row -- charstats wStartSkill came out as 567 against
	// 357 skill records, and Skill 1..3 as bogus ids as well.
	for (D2TxtLinkNodeStrc* pNode = pLinker->pFirstNode; pNode; pNode = pNode->pNext) {
		if (strcasecmp(pNode->szText, szText) == 0) {
			return pNode->nLinkIndex;
		}
	}
	return -1;
}

int32_t FOG_GetLinkIndex(void* pLink, uint32_t dwCode, int32_t bLogError) {
	D2TxtLinkStrc* pLinker = (D2TxtLinkStrc*)pLink;
	if (!pLinker || !pLinker->pTbl) {
		return -1;
	}

	for (int32_t i = 0; i < pLinker->nRecords; ++i) {
		if (pLinker->pTbl[i].dwCode == dwCode) {
			return pLinker->pTbl[i].nLinkIndex;
		}
	}
	return -1;
}

int32_t FOG_GetStringFromLinkIndex(void* pLinkerV, int32_t nIndex, char* szString) {
	D2TxtLinkStrc* pLinker = (D2TxtLinkStrc*)pLinkerV;
	if (!pLinker || !szString) {
		return 0;
	}

	for (D2TxtLinkNodeStrc* pNode = pLinker->pFirstNode; pNode; pNode = pNode->pNext) {
		if (pNode->nLinkIndex == nIndex) {
			std::strcpy(szString, pNode->szText);
			return (int32_t)std::strlen(szString);
		}
	}

	// Fall back to the code table (code-only linkers built by FOG_10215, e.g.
	// the item types -> treasure class name lookup in MonsterTbls.cpp).
	if (pLinker->pTbl) {
		for (int32_t i = 0; i < pLinker->nRecords; ++i) {
			if (pLinker->pTbl[i].nLinkIndex == nIndex) {
				char szCode[5] = {};
				std::memcpy(szCode, pLinker->pTbl[i].szCode, 4);
				std::strcpy(szString, szCode);
				return (int32_t)std::strlen(szString);
			}
		}
	}

	return 0;
}

// FOG_10255(linker, nIndex, nFlags): returns the text of the entry whose
// nLinkIndex equals nIndex (callers pass monster row indices, e.g.
// pMonStatsTxt[nId].nId).  Only used for FOG_Trace diagnostics under
// bCompileTxt, so an empty fallback is safe for unknown indices.
char* FOG_10255(void* pLinkerV, int32_t nIndex, int32_t nFlags) {
	D2TxtLinkStrc* pLinker = (D2TxtLinkStrc*)pLinkerV;
	if (!pLinker) {
		return (char*)"";
	}

	for (D2TxtLinkNodeStrc* pNode = pLinker->pFirstNode; pNode; pNode = pNode->pNext) {
		if (pNode->nLinkIndex == nIndex) {
			return pNode->szText;
		}
	}
	return (char*)"";
}