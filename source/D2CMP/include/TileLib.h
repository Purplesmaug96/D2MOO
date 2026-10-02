#pragma once 
#include <D2BasicTypes.h>

struct D2TileRecordStrc;

struct D2TileLibraryEntryStrc
{
	int32_t nLightDirection;					//0x00
	uint16_t nRoofHeight;						//0x04
	uint16_t nFlags;							//0x06 D2TileMaterialFlags
	int32_t nTotalHeight;						//0x08
	int32_t nWidth;								//0x0C
	int32_t nHeightToBottom;					//0x10
	int32_t nType;								//0x14 aka nOrientation
	int32_t nStyle;								//0x18 aka nIndex
	int32_t nSequence;							//0x1C aka nSubIndex
	int32_t nRarity_Frame;						//0x20 By default this is the rarity of the tile, for animated tiles this is the frame index.
	int32_t transparentColorRGB24;				//0x24
	uint8_t dwTileFlags[4];						//0x28 Collision info
	int32_t dwBlockOffset_pBlock;				//0x2C
	int32_t nBlockSize;							//0x30
	int32_t nBlocks;							//0x34
	D2TileRecordStrc* pParent;					//0x38
	uint16_t unk0x3C;							//0x3C
	uint16_t nCacheIndex;						//0x3E
	uint32_t unk0x40[4];						//0x40
	//int32_t field_50;
	//int32_t field_54;
	//int32_t field_58;
	//int32_t field_5C;
};

struct D2TileLibraryBlockStrc
{
	int16_t nPosX;							//0x00
	int16_t nPosY;							//0x02
	int16_t unk0x04;							//0x04
	uint8_t nGridX;							//0x06
	uint8_t nGridY;							//0x07
	uint16_t nFormat;							//0x08
	int32_t nLength;							//0x0A
	int16_t unk0x0E;							//0x0E
	int32_t dwOffset_pData;						//0x10
};

struct D2TileLibraryHashRefStrc
{
	D2TileLibraryEntryStrc* pTile;			//0x00
	D2TileLibraryHashRefStrc* pPrev;		//0x04
};

struct D2TileLibraryHashNodeStrc
{
	int32_t nStyle;							//0x00 aka nIndex;								
	int32_t nSequence;						//0x04 aka nSequence;							
	int32_t nType;							//0x08 aka nOrientation;						
	D2TileLibraryHashRefStrc* pRef;			//0x0C
	D2TileLibraryHashNodeStrc* pPrev;		//0x10
};

struct D2TileLibraryHashStrc
{
	D2TileLibraryHashNodeStrc* pNodes[128];	//0x00
};

struct D2TileLibraryHeaderStrc
{
	int32_t dwVersion;							//0x00
	int32_t dwFlags;							//0x04
	char szLibraryName[260];				//0x08
	int32_t nTiles;								//0x10C
	int32_t dwTileStart_pFirst;					//0x110
};

// D2Cmp.#10077
int __stdcall D2CMP_TileGetType(D2TileLibraryEntryStrc* hTile);

// D2Cmp.#10078
int __stdcall D2CMP_TileGetStyle(D2TileLibraryEntryStrc* hTile);

// D2Cmp.#10079
int __stdcall D2CMP_TileGetFlags(D2TileLibraryEntryStrc* hTile);

// D2Cmp.#10081
int __stdcall D2CMP_TileGetRarity(D2TileLibraryEntryStrc* hTile);

// D2Cmp.#10082
int __stdcall D2CMP_TileGetSequence(D2TileLibraryEntryStrc* hTile);

// D2Cmp.#10085
uint8_t* __stdcall D2CMP_TileGetCollisionInfo(D2TileLibraryEntryStrc* hTile);
