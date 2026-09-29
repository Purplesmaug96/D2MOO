// Excel txt -> D2BinFileStrc parser (real implementations)
// ---------------------------------------------------------------------
// libD2Common.so imports FOG_CreateBinFile / FOG_GetRecordCountFromBinFile /
// FOG_10207 / FOG_FreeBinFile as part of DATATBLS_CompileTxt, which parses
// DATA\GLOBAL\EXCEL\*.txt into the typed record buffers the engine uses.
//
// D2BinFileStrc (Fog.h):
//   uint8_t* pDataBuffer; uint8_t* pData; int32_t nRecordCount; int32_t nCellCount;
// pData points at an internal FogExcelTxt (owned by us).
//
// Parsing rules:
//   * lines are split on '\n' (CR stripped); empty lines and '//' comment
//     lines are skipped
//   * the first remaining line is the header; cells split on '\t' with empty
//     cells preserved ("a\t\tc" -> 3 cells)
//   * FOG_10207 matches fields by header name (exact, then case-insensitive)
//     and converts the cell per the field's TXTFIELD_* type; linker types
//     (NAMETO*/KEYTOWORD/CODE*) resolve through the txt linker tables via
//     FOG_GetRowFromTxt (TxtLink.cpp).

#include <Fog.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <strings.h>

// Writer callbacks installed on CALCTODWORD/CUSTOMLINK/DWORD-with-fn fields
// (DATATBLS_ItemParamLinker, DATATBLS_SkillCalcLinker, ...).
typedef void(__fastcall* D2TxtLinkerFn)(char* pSrc, void* pRecord, int nOffset, int nPosition, int nTxtRow, int nTxtColumn);
// Key-to-string-id resolver installed on KEYTOWORD fields.
typedef uint16_t(__fastcall* D2KeyToWordFn)(char* pSrc);

// Txt linker API (TxtLink.cpp, strong implementations in this library).
extern int32_t FOG_10215(void* pBin, int32_t nCode);
extern int32_t FOG_10216_AddRecordToLinkingTable(void* pBin, const char* szText);
extern int32_t FOG_AddCodeAndTextToLinkingTable(void* pBin, int32_t nCode, const char* szText);
extern int32_t FOG_GetRowFromTxt(void* pBin, char* szText, int32_t nColumn);
extern int32_t FOG_GetLinkIndex(void* pLink, uint32_t dwCode, int32_t bLogError);

namespace {

struct FogExcelTxt {
	int32_t nRows = 0; // data rows (excluding the header line)
	int32_t nCols = 0; // header column count
	char** pHeader = nullptr; // [nCols] pointers into pHeaderStore
	char* pHeaderStore = nullptr;
	char** pCells = nullptr; // [nRows * nCols] pointers into pCellStore
	char* pCellStore = nullptr;
};

// Flatten a vector of cells into a contiguous store; fills out with pointers
// into the store. Cells may be empty strings (empty cells preserved).
void FlattenCells(const std::vector<std::string>& src, char* pStore, char** out, size_t* pOffset) {
	for (size_t i = 0; i < src.size(); ++i) {
		const size_t nLen = src[i].size();
		std::memcpy(pStore + *pOffset, src[i].c_str(), nLen + 1);
		out[i] = pStore + *pOffset;
		*pOffset += nLen + 1;
	}
}

// Split a line into columns, preserving empty cells ("a\t\tc" -> 3 cells).
void SplitCellsManual(const char* pLine, std::vector<std::string>* out) {
	const char* pStart = pLine;
	for (const char* p = pLine;; ++p) {
		if (*p == '\t' || *p == '\0') {
			out->emplace_back(pStart, (size_t)(p - pStart));
			if (*p == '\0') {
				break;
			}
			pStart = p + 1;
		}
	}
}

void FreeTable(FogExcelTxt* pTable) {
	if (!pTable) {
		return;
	}
	std::free(pTable->pHeader);
	std::free(pTable->pHeaderStore);
	std::free(pTable->pCells);
	std::free(pTable->pCellStore);
	std::free(pTable);
}

} // namespace

D2BinFileStrc* FOG_CreateBinFile(void* pDataBuffer, int32_t nBufferSize) {
	if (!pDataBuffer || nBufferSize <= 0) {
		return nullptr;
	}

	// Working copy (split below references it while we build the stores).
	std::vector<char> working((size_t)nBufferSize + 1);
	std::memcpy(working.data(), pDataBuffer, (size_t)nBufferSize);
	const char* pBuf = working.data();

	// Split into lines on '\n'.
	std::vector<std::string> rawLines;
	{
		const char* pStart = pBuf;
		for (const char* p = pBuf;; ++p) {
			if (*p == '\n' || *p == '\0') {
				std::string line(pStart, (size_t)(p - pStart));
				// Strip trailing '\r' and blanks.
				while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t')) {
					line.pop_back();
				}
				rawLines.push_back(std::move(line));
				if (*p == '\0') {
					break;
				}
				pStart = p + 1;
			}
		}
	}

	// First non-empty, non-comment line = header; rest = data rows.
	FogExcelTxt* pTable = (FogExcelTxt*)std::calloc(1, sizeof(FogExcelTxt));
	if (!pTable) {
		return nullptr;
	}

	std::vector<std::string> headerCells;
	std::vector<std::vector<std::string>> rowCells;
	// pTable->pHeader is the caller-visible out-array (allocated below), so it
	// cannot double as the "header line seen" flag.
	bool bGotHeader = false;

	for (const std::string& rawLine : rawLines) {
		const char* pTrim = rawLine.c_str();
		while (*pTrim == ' ' || *pTrim == '\t') {
			++pTrim;
		}
		if (*pTrim == '\0' || strncmp(pTrim, "//", 2) == 0) {
			continue;
		}

		std::vector<std::string> cells;
		SplitCellsManual(rawLine.c_str(), &cells);

		if (!bGotHeader) {
			headerCells = cells;
			pTable->nCols = (int32_t)cells.size();
			bGotHeader = true;
		} else {
			// Pad short rows to the header width.
			cells.resize((size_t)pTable->nCols);
			rowCells.push_back(std::move(cells));
		}
	}

	if (pTable->nCols == 0) {
		std::free(pTable);
		return nullptr;
	}

	pTable->nRows = (int32_t)rowCells.size();

	// Allocate stores: header store + cell store.
	size_t nHeaderBytes = 0;
	for (const auto& cell : headerCells) {
		nHeaderBytes += cell.size() + 1;
	}
	size_t nCellBytes = 0;
	for (const auto& row : rowCells) {
		for (const auto& cell : row) {
			nCellBytes += cell.size() + 1;
		}
	}

	pTable->pHeader = (char**)std::calloc((size_t)pTable->nCols, sizeof(char*));
	pTable->pHeaderStore = (char*)std::calloc(nHeaderBytes ? nHeaderBytes : 1, 1);
	pTable->pCells = (char**)std::calloc((size_t)pTable->nRows * (size_t)pTable->nCols, sizeof(char*));
	pTable->pCellStore = (char*)std::calloc(nCellBytes ? nCellBytes : 1, 1);

	if (!pTable->pHeader || !pTable->pHeaderStore || (!pTable->pCells && pTable->nRows > 0) || !pTable->pCellStore) {
		FreeTable(pTable);
		return nullptr;
	}

	size_t nHeaderOffset = 0;
	FlattenCells(headerCells, pTable->pHeaderStore, pTable->pHeader, &nHeaderOffset);
	size_t nCellOffset = 0;
	for (int32_t r = 0; r < pTable->nRows; ++r) {
		FlattenCells(rowCells[(size_t)r], pTable->pCellStore, pTable->pCells + (size_t)r * (size_t)pTable->nCols, &nCellOffset);
	}

	D2BinFileStrc* pBinFile = (D2BinFileStrc*)std::calloc(1, sizeof(D2BinFileStrc));
	if (!pBinFile) {
		FreeTable(pTable);
		return nullptr;
	}

	pBinFile->pDataBuffer = (uint8_t*)pDataBuffer; // owned by caller
	pBinFile->pData = (uint8_t*)pTable;
	pBinFile->nRecordCount = pTable->nRows;
	pBinFile->nCellCount = pTable->nCols;

	return pBinFile;
}

int32_t FOG_GetRecordCountFromBinFile(D2BinFileStrc* pBinFile) {
	if (!pBinFile || !pBinFile->pData) {
		return 0;
	}
	const FogExcelTxt* pTable = (const FogExcelTxt*)pBinFile->pData;
	return pTable->nRows;
}

void FOG_FreeBinFile(D2BinFileStrc* pBinFile) {
	if (!pBinFile) {
		return;
	}
	FreeTable((FogExcelTxt*)pBinFile->pData);
	std::free(pBinFile);
}

static int32_t FindColumnIndex(const FogExcelTxt* pTable, const char* szFieldName) {
	if (!pTable->pHeader || !szFieldName) {
		return -1;
	}
	for (int32_t c = 0; c < pTable->nCols; ++c) {
		const char* pHeaderCell = pTable->pHeader[(size_t)c];
		if (pHeaderCell && strcmp(pHeaderCell, szFieldName) == 0) {
			return c;
		}
	}
	// Case-insensitive fallback
	for (int32_t c = 0; c < pTable->nCols; ++c) {
		const char* pHeaderCell = pTable->pHeader[(size_t)c];
		if (pHeaderCell && strcasecmp(pHeaderCell, szFieldName) == 0) {
			return c;
		}
	}
	return -1;
}

void FOG_10207(D2BinFileStrc* pBinFile, D2BinFieldStrc* pBinField, void* pTxt, int32_t nRecordCount, int32_t nRecordSize) {
	if (!pBinFile || !pBinFile->pData || !pBinField || !pTxt) {
		return;
	}

	const FogExcelTxt* pTable = (const FogExcelTxt*)pBinFile->pData;
	if (!pTable->pHeader) {
		return;
	}

	const int32_t nRows = nRecordCount < pTable->nRows ? nRecordCount : pTable->nRows;

	for (; pBinField->szFieldName != nullptr; ++pBinField) {
		if (strcmp(pBinField->szFieldName, "end") == 0) {
			break;
		}

		const int32_t nCol = FindColumnIndex(pTable, pBinField->szFieldName);
		if (nCol < 0) {
			continue; // fields stay zeroed (calloc'd records)
		}

		const uint32_t nFieldType = (uint32_t)pBinField->nFieldType;
		const int32_t nFieldLength = pBinField->nFieldLength;

		for (int32_t r = 0; r < nRows; ++r) {
			const char* pCell = pTable->pCells[(size_t)r * (size_t)pTable->nCols + (size_t)nCol];
			if (!pCell) {
				pCell = "";
			}
			uint8_t* pTarget = (uint8_t*)pTxt + (size_t)r * (size_t)nRecordSize + (size_t)pBinField->nFieldOffset;
			// Writer-callback linkers (DATATBLS_MonPresetPlaceLinker,
			// DATATBLS_MonStats2CompositLinker, the Horadric cube
			// input/output parsers, ...) take the *row base* and use
			// pBinField->nFieldOffset as a component index INTO the
			// record struct, not as a byte offset.  Passing pTarget would
			// add the offset twice; passing the whole array (pTxt) -- which
			// this used to do -- made every callback write row 0 only.
			uint8_t* pRecord = (uint8_t*)pTxt + (size_t)r * (size_t)nRecordSize;

			switch (nFieldType) {
			case TXTFIELD_ASCII: {
				size_t nLen = std::strlen(pCell);
				if (nFieldLength > 0 && nLen > (size_t)nFieldLength) {
					nLen = (size_t)nFieldLength;
				}
				std::memcpy(pTarget, pCell, nLen);
				break;
			}
			case TXTFIELD_ASCIITOCODE: {
				// ASCII code column: stores the raw string bytes in the
				// record (monmode "code" -> "death"; items "code" -> "gcv ");
				// with a linker slot it also registers the 4-byte code + text.
				// Registration must NOT depend on the linker being empty: the
				// items loader compiles weapons/armor/misc into the same
				// pItemsLinker, so all three passes have to land in the linker
				// for later code lookups (gems "code", cube rune1..3) to
				// resolve.
				size_t nLen = std::strlen(pCell);
				if (nFieldLength > 0 && nLen > (size_t)nFieldLength) {
					nLen = (size_t)nFieldLength;
				}
				std::memcpy(pTarget, pCell, nLen);
				if (pBinField->pLinkField != nullptr) {
					D2TxtLinkStrc* pLinker = *(D2TxtLinkStrc**)pBinField->pLinkField;
					if (pLinker != nullptr) {
						// Every row must consume one linker slot, including
						// rows with an empty "code" cell: the link index is
						// used as a row index into the record array
						// (DATATBLS_GetItemRecordFromItemCode returns
						// &pItemsTxt[id] unchecked), and the .bin path seeds the
						// linker with an unconditional FOG_10215 per row. 1.14d
						// weapons/armor/misc each carry an "Expansion"
						// separator row with a blank code to keep pre-expansion
						// item indices stable; skipping those shortens nRecords
						// and shifts every later row by one. A blank cell only
						// skips the text node, never the code slot.
						if (pCell[0] == '\0') {
							FOG_10215(pLinker, 0);
						} else {
							char szCode[4] = {};
							size_t nCodeLen = std::strlen(pCell);
							if (nCodeLen > 4) {
								nCodeLen = 4;
							}
							std::memcpy(szCode, pCell, nCodeLen);
							int32_t nCode4 = 0;
							std::memcpy(&nCode4, szCode, 4);
							FOG_AddCodeAndTextToLinkingTable(pLinker, nCode4, pCell);
						}
					}
				}
				break;
			}
			case TXTFIELD_UNKNOWN3: {
				// Code column referencing an already-populated linker (gems
				// "code", cube "rune1..3" -> pItemsLinker): the 4-byte code
				// is resolved to its row index (Blizzard's own gems.bin stores
				// the item row index here, not the code).
				// An empty cell means "no item" and must not resolve: a blank
				// code of 0 is a legitimate linker entry (the "Expansion"
				// separator rows), so looking it up would hand a recipe a
				// phantom item instead of the 0xFFFFFFFF sentinel.
				uint32_t nIndex = 0xFFFFFFFF;
				if (pBinField->pLinkField != nullptr && pCell[0] != '\0') {
					char szCode[4] = {};
					size_t nCodeLen = std::strlen(pCell);
					if (nCodeLen > 4) {
						nCodeLen = 4;
					}
					std::memcpy(szCode, pCell, nCodeLen);
					int32_t nCode4 = 0;
					std::memcpy(&nCode4, szCode, 4);
					D2TxtLinkStrc* pLinker = *(D2TxtLinkStrc**)pBinField->pLinkField;
					if (pLinker != nullptr) {
						nIndex = (uint32_t)FOG_GetLinkIndex(pLinker, (uint32_t)nCode4, 0);
					}
				}
				*(uint32_t*)pTarget = nIndex;
				break;
			}
			case TXTFIELD_DWORD:
			case TXTFIELD_DWORD2:
				// A DWORD carrying a link function (e.g.
				// DATATBLS_CubeMainParamLinker) is a writer callback.
				if (pBinField->pLinkField != nullptr) {
					((D2TxtLinkerFn)pBinField->pLinkField)((char*)pCell, pTxt, pBinField->nFieldOffset, r, r, nCol);
				} else {
					*(uint32_t*)pTarget = (uint32_t)std::strtoul(pCell, nullptr, 10);
				}
				break;
			case TXTFIELD_WORD:
				*(uint16_t*)pTarget = (uint16_t)std::strtoul(pCell, nullptr, 10);
				break;
			case TXTFIELD_BYTE:
			case TXTFIELD_BYTE2:
			case TXTFIELD_UNKNOWN2:
				// UNKNOWN2 fields (items "mindam"/"maxdam"/"block"/"missile"/
				// "gemsockets"/"TMogMin"...) land on consecutive uint8_t
				// members of D2ItemsTxt, so they are byte quantities.
				*(uint8_t*)pTarget = (uint8_t)std::strtoul(pCell, nullptr, 10);
				break;
			case TXTFIELD_RAW: {
				size_t nLen = std::strlen(pCell);
				if (nFieldLength > 0 && nLen > (size_t)nFieldLength) {
					nLen = (size_t)nFieldLength;
				}
				std::memcpy(pTarget, pCell, nLen);
				// With a linker slot (level preset item codes) the raw code is
				// also recorded into the linker.
				if (pBinField->pLinkField != nullptr) {
					D2TxtLinkStrc* pLinker = *(D2TxtLinkStrc**)pBinField->pLinkField;
					if (pLinker != nullptr && pLinker->nRecords == 0) {
						char szCode[4] = {};
						size_t nCodeLen = std::strlen(pCell);
						if (nCodeLen > 4) {
							nCodeLen = 4;
						}
						std::memcpy(szCode, pCell, nCodeLen);
						int32_t nCode4 = 0;
						std::memcpy(&nCode4, szCode, 4);
						FOG_AddCodeAndTextToLinkingTable(pLinker, nCode4, pCell);
					}
				}
				break;
			}
			case TXTFIELD_NAMETOINDEX:
			case TXTFIELD_NAMETOINDEX2:
			case TXTFIELD_NAMETODWORD:
			case TXTFIELD_NAMETOWORD:
			case TXTFIELD_NAMETOWORD2:
			case TXTFIELD_CODETOBYTE:
			case TXTFIELD_CODETOWORD: {
				// pLinkField is the address of a D2TxtLinkStrc* slot in
				// sgptDataTables (e.g. &sgptDataTables->pMonStatsLinker).
				D2TxtLinkStrc* pLinker =
					pBinField->pLinkField != nullptr ? *(D2TxtLinkStrc**)pBinField->pLinkField : nullptr;
				const bool bCodeLink = (nFieldType == TXTFIELD_CODETOBYTE || nFieldType == TXTFIELD_CODETOWORD);
				int32_t nIndex = -1;

				// Empty cells do not register a linker entry.  The stored
				// value matches the shipped 1.14d .bin files:
				//  - linker still empty (the very first cell of the first
				//    linker field, e.g. monseq "sequence" row 0 which is
				//    blank) stores 0  (verified: monseq.bin wSequence=0);
				//  - linker already populated (reference fields, e.g.
				//    monstats "NextInClass" tail rows) stores -1
				//    (verified: monstats.bin wNextInClass=0xFFFF for the
				//    empty tail of every monster class chain).
				if (pLinker != nullptr && pCell[0] == '\0' && pLinker->nRecords == 0) {
					nIndex = 0;
				} else if (pLinker != nullptr && pCell[0] != '\0') {
					// Code entries are the first 4 bytes of the cell, zero
					// padded when shorter (" h2h" -> ' h2h'; "fallen1" ->
					// 'fale').
					char szCode[4] = {};
					size_t nCellLen = std::strlen(pCell);
					if (nCellLen > 4) {
						nCellLen = 4;
					}
					std::memcpy(szCode, pCell, nCellLen);
					int32_t nCode4 = 0;
					std::memcpy(&nCode4, szCode, 4);

					// Every non-empty cell registers code + text into the
					// linker with nLinkIndex = nRecords (in row order).  The
					// first field to touch a linker is the table's identity
					// column (monstats "Id", itemstatcost "Stat", ...) and
					// registers all rows; later reference fields register
					// duplicates, which is harmless because lookups below use
					// first-match semantics.  This is required for the items
					// loader, which compiles weapons/armor/misc into the same
					// pItemsLinker.  The stored value is the first-match row
					// index, so duplicate Ids (e.g. "cr_lancer8") all resolve
					// to the first occurrence, and identity rows resolve to
					// their own index.
					FOG_AddCodeAndTextToLinkingTable(pLinker, nCode4, pCell);

					if (bCodeLink) {
						nIndex = FOG_GetLinkIndex(pLinker, (uint32_t)nCode4, 0);
					} else {
						nIndex = FOG_GetRowFromTxt(pLinker, (char*)pCell, 0);
					}
				}

				switch (nFieldType) {
				case TXTFIELD_NAMETOINDEX:
					// 16-bit (proven by the skills loader's temp passing pass
					// with recordSize 2; D2MonStatsTxt.nId / D2SuperUniquesTxt
					// .wSuperUnique / D2PropertiesTxt.wProp are all 16-bit).
					*(uint16_t*)pTarget = (uint16_t)nIndex;
					break;
				case TXTFIELD_NAMETOINDEX2:
					// 32-bit (D2MonPropTxt.dwId / D2PetTypeTxt.dwHcIdx).
					*(uint32_t*)pTarget = (uint32_t)nIndex;
					break;
				case TXTFIELD_NAMETODWORD:
					*(uint32_t*)pTarget = (uint32_t)nIndex;
					break;
				case TXTFIELD_NAMETOWORD:
				case TXTFIELD_NAMETOWORD2:
				case TXTFIELD_CODETOWORD:
					*(uint16_t*)pTarget = (uint16_t)nIndex;
					break;
				case TXTFIELD_CODETOBYTE:
				default:
					*(uint8_t*)pTarget = (uint8_t)nIndex;
					break;
				}
				break;
			}
			case TXTFIELD_BIT:
				// A TXTFIELD_BIT entry sets ONE bit of the flag word that starts
				// at nFieldOffset; nFieldLength carries the bit index, not a
				// width.  The window is 64 bits wide because several tables
				// index past bit 31 into a second dword: states.txt (bossinv
				// 37 / meleeonly 38 -> dwStateFlagsEx at +0x04) and skills.txt
				// (TgtPlaceCheck 32, ItemCheckStart 33, usemanaondo 37 -> the
				// dwFlags[2] at 0x04).  For the 32-bit-only tables (monstats
				// 0x0C, missiles 0x04, items 0x10) the read-modify-write leaves
				// the neighbouring dword untouched.
				//
				// This used to store a whole byte at nFieldOffset, so every flag
				// column of a record overwrote the same address and whichever
				// column was compiled last won: MonStats.txt has 29 flag
				// columns (enabled, npc, interact, inTown, ...) that all target
				// dwMonStatsFlags 0x0C, so MONSTATSFLAGINDEX_INTERACT / NPC /
				// INTOWN never survived the load and every interact check in the
				// engine (D2Game.0x6FC61C70) bailed out.  The cell is a 0/1
				// string: "1" sets the bit, any other value clears it.
				if (pCell[0] == '1') {
					*(uint64_t*)pTarget |= (uint64_t)1 << nFieldLength;
				} else {
					*(uint64_t*)pTarget &= ~((uint64_t)1 << nFieldLength);
				}
				break;
			case TXTFIELD_KEYTOWORD:
				// pLinkField is a key->string-id resolver (e.g.
				// DATATBLS_GetStringIdFromReferenceString); result is a WORD.
				if (pBinField->pLinkField != nullptr) {
					*(uint16_t*)pTarget = (uint16_t)((D2KeyToWordFn)pBinField->pLinkField)((char*)pCell);
				}
				break;
			case TXTFIELD_CALCTODWORD:
				// A CALCTODWORD carrying a link function (DATATBLS_*CalcLinker)
				// is a writer callback that parses the calc expression itself.
				if (pBinField->pLinkField != nullptr) {
					((D2TxtLinkerFn)pBinField->pLinkField)((char*)pCell, pRecord, pBinField->nFieldOffset, r, r, nCol);
				} else {
					*(uint32_t*)pTarget = (uint32_t)std::strtoul(pCell, nullptr, 10);
				}
				break;
			case TXTFIELD_CUSTOMLINK:
			default:
				// Writer callbacks (DATATBLS_MonStats2CompositLinker etc.).
				if (pBinField->pLinkField != nullptr) {
					((D2TxtLinkerFn)pBinField->pLinkField)((char*)pCell, pRecord, pBinField->nFieldOffset, r, r, nCol);
				}
				break;
			}
		}
	}
}