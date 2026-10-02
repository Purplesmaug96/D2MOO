#include "TileLib.h" 
#include "Fog.h"

int __stdcall D2CMP_TileGetType(D2TileLibraryEntryStrc* hTile) { D2_CHECK(hTile); return hTile->nType; } // TODO: Should be line 120 (from D2CMPd)
int __stdcall D2CMP_TileGetStyle(D2TileLibraryEntryStrc* hTile) { D2_CHECK(hTile); return hTile->nStyle; } // TODO: Should be line 121 (from D2CMPd)
int __stdcall D2CMP_TileGetFlags(D2TileLibraryEntryStrc* hTile) { D2_CHECK(hTile); return hTile->nFlags; } // TODO: Should be line 122 (from D2CMPd)

int __stdcall D2CMP_TileGetRarity(D2TileLibraryEntryStrc* hTile) { D2_CHECK(hTile); return hTile->nRarity_Frame; } // TODO: Should be line 124 (from D2CMPd)
int __stdcall D2CMP_TileGetSequence(D2TileLibraryEntryStrc* hTile) { D2_CHECK(hTile); return hTile->nSequence; } // TODO: Should be line 125 (from D2CMPd)
uint8_t* __stdcall D2CMP_TileGetCollisionInfo(D2TileLibraryEntryStrc* hTile) { D2_CHECK(hTile); return hTile->dwTileFlags; } // TODO: Should be line 128 (from D2CMPd)

