#pragma once

#include <D2Dll.h>
#include <D2BasicTypes.h>

#include "TileLib.h"

//1.10f Image base: 0x6FDF0000

#ifdef D2_VERSION_110F
constexpr int D2CMPImageBase = 0x6FDF0000;
#endif

#pragma pack(1)

enum D2TileMaterialFlags : uint16_t 
{
	TILE_FLAGS_OTHER = 0x1,
	TILE_FLAGS_WATER = 0x2,
	TILE_FLAGS_WOOD_OBJ = 0x4, // Blocks reverberation
	TILE_FLAGS_ISTONE = 0x8,   // Indoor stone
	TILE_FLAGS_OSTONE = 0x10,  // Outdoor stone
	TILE_FLAGS_DIRT = 0x20,
	TILE_FLAGS_SAND = 0x40,
	TILE_FLAGS_WOOD = 0x80,
	TILE_FLAGS_LAVA = 0x100, // Special case: Always bright + animated
	TILE_FLAGS_SNOW = 0x400,
};

enum D2TileType
{
	TILETYPE_FLOOR = 0,                 // automap code: fl
	TILETYPE_WALL_LEFT = 1,             // automap code: wl
	TILETYPE_WALL_RIGHT = 2,            // automap code: wr
	TILETYPE_WALL_TOP_CORNER_RIGHT = 3, // automap code: wtlr
	TILETYPE_WALL_TOP_CORNER_LEFT = 4,  // automap code: wtll
	TILETYPE_WALL_TOP_RIGHT = 5,        // automap code: wtr
	TILETYPE_WALL_BOTTOM_LEFT = 6,      // automap code: wbl
	TILETYPE_WALL_BOTTOM_RIGHT = 7,     // automap code: wbr
	TILETYPE_WALL_LEFT_DOOR = 8,        // automap code: wld
	TILETYPE_WALL_RIGHT_DOOR = 9,       // automap code: wrd
	TILETYPE_WALL_LEFT_EXIT = 10,       // automap code: wle
	TILETYPE_WALL_RIGHT_EXIT = 11,      // automap code: wre
	TILETYPE_COLUMN = 12,               // automap code: co
	TILETYPE_SHADOW = 13,               // automap code: sh
	TILETYPE_TREE = 14,                 // automap code: tr
	TILETYPE_ROOF = 15,                 // automap code: rf
	TILETYPE_LEFT_WALL_DOWN = 16,       // automap code: ld
	TILETYPE_RIGHT_WALL_DOWN = 17,      // automap code: rd
	TILETYPE_FULL_WALL_DOWN = 18,       // automap code: fd
	TILETYPE_FRONT_WALL_DOWN = 19,      // automap code: fi
};

struct D2TileStrc
{
	D2TileStrc* pNext;						//0x00
	uint16_t unk0x04;							//0x04
	uint16_t nFlags;							//0x06
	int32_t unk0x08;							//0x08
	int32_t nTile;								//0x0C
	int32_t unk0x10;							//0x10
	int32_t nAct;								//0x14
	int32_t nLevel;								//0x18
	int32_t nTileType;							//0x1C
	uint32_t unk0x20[7];						//0x20
	D2TileRecordStrc* pParent;				//0x3C
	uint32_t unk0x40[33];						//0x40
};

struct D2TileRecordStrc
{
	char szLibraryName[260];				//0x00
	void* pLibrary;							//0x104
	D2TileLibraryHashStrc* pHashBlock;		//0x108
	D2TileRecordStrc* pPrev;				//0x10C
};


struct D2CellFileStrc;
struct D2GfxCellStrc;
struct D2GfxDataStrc;

#pragma pack()

// Helper function
inline bool TileTypeIsAWallWithDoor(int32_t nTileType)
{
	return nTileType == TILETYPE_WALL_RIGHT_DOOR || nTileType == TILETYPE_WALL_LEFT_DOOR;
}


D2FUNC_DLL(D2CMP, GetNearestPaletteIndex, int, __stdcall, (PALETTEENTRY* pPalette, int nPaletteSize, int nRed, int nGreen, int nBlue), 0xAB20)									//D2Cmp.#10004
D2FUNC_DLL(D2CMP, CelFileNormalize, void, __stdcall, (D2CellFileStrc* pFile, D2CellFileStrc** ppOutFile, const char* szFile, int nLine, int nSpecVersion, int nUnused), 0x1EA0)		//D2Cmp.#10024
D2FUNC_DLL(D2CMP, CelFileFreeHardware, BOOL, __stdcall, (D2CellFileStrc* pFile), 0x2750)																				//D2Cmp.#10032
D2FUNC_DLL(D2CMP, CelGetHandle, D2CellFileStrc*, __stdcall, (D2GfxDataStrc*), 0x2540)																					//D2Cmp.#10036
D2FUNC_DLL(D2CMP, CelGetWidth, int, __stdcall, (D2CellFileStrc* pCelFile), 0x25E0)																						//D2Cmp.#10037
D2FUNC_DLL(D2CMP, CelGetHeight, int, __stdcall, (D2CellFileStrc* pCelFile), 0x2610)																						//D2Cmp.#10038
D2FUNC_DLL(D2CMP, CelGetOffsetX, int, __stdcall, (D2CellFileStrc* pCelFile), 0x2640)																					//D2Cmp.#10039
D2FUNC_DLL(D2CMP, CelGetOffsetY, int, __stdcall, (D2CellFileStrc* pCelFile), 0x2670)																					//D2Cmp.#10040
D2FUNC_DLL(D2CMP, CelFileGetCelsPerDirection, int, __stdcall, (D2CellFileStrc* pCelFile), 0x2700)																		//D2Cmp.#10046
D2FUNC_DLL(D2CMP, GetGfxFileExtension, const char*, __stdcall, (BOOL bAllowCompressed), 0xB930)																			//D2Cmp.#10051
D2FUNC_DLL(D2CMP, InitSpriteCache, void, __stdcall, (void* pMemPool, int dwSpriteCacheSize, int dwSize, unsigned int dwMemoryOverride), 0xB9F0)							//D2Cmp.#10052
D2FUNC_DLL(D2CMP, FlushSpriteCache, void, __stdcall, (BOOL bRealloc), 0xBBF0)																							//D2Cmp.#10053
D2FUNC_DLL(D2CMP, SetCompressedDataMode, void, __stdcall, (BOOL bAllowCompressedMode), 0xB9C0)																			//D2Cmp.#10054
// Material flags
D2FUNC_DLL(D2CMP, 10087_LoadTileLibrarySlot, void, __stdcall, (D2TileLibraryHashStrc** ppTileLibraryHash, const char* szFileName), 0xFDE0)								//D2Cmp.#10087
D2FUNC_DLL(D2CMP, 10088_GetTiles, int, __stdcall, (D2TileLibraryHashStrc** ppTileLibraryHash, int nType, int nStyle, int nSequence, D2TileLibraryEntryStrc** pTileList, int nTileListSize), 0xFE70)//D2Cmp.#10088
D2FUNC_DLL(D2CMP, MixPalette, uint8_t*, __stdcall, (uint8_t nTrans, int nColor), 0xB760)																				//D2Cmp.#10098
D2FUNC_DLL(D2CMP, SpriteFreeAsyncLoads, void, __stdcall, (), 0xE000)																									//D2Cmp.#10099
D2FUNC_DLL(D2CMP, TileFreeAsyncLoads, void, __stdcall, (), 0xE860)																										//D2Cmp.#10102
