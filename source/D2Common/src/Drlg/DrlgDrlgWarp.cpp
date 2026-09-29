#include "Drlg/D2DrlgDrlgWarp.h"

#include "D2DataTbls.h"
#include "D2Seed.h"
#include "Drlg/D2DrlgActivate.h"
#include "Drlg/D2DrlgDrlg.h"
#include "Drlg/D2DrlgDrlgRoom.h"
#include "Drlg/D2DrlgPreset.h"
#include <Units/Units.h>

// D2Common.0x6FD78780
D2ActiveRoomStrc* __fastcall DRLGWARP_GetDestinationRoom(D2DrlgRoomStrc* pDrlgRoom, int nSourceLevel, int* pDestinationLevel, D2LvlWarpTxt** ppLvlWarpTxtRecord) {
	for (D2RoomTileStrc* pSourceRoomTile = pDrlgRoom->pRoomTiles; pSourceRoomTile; pSourceRoomTile = pSourceRoomTile->pNext) {
		if (pSourceRoomTile->nWarpId == nSourceLevel) {
			for (D2RoomTileStrc* pDestinationRoomTile = pSourceRoomTile->pDrlgRoom->pRoomTiles; pDestinationRoomTile; pDestinationRoomTile = pDestinationRoomTile->pNext) {
				if (pDestinationRoomTile->pDrlgRoom == pDrlgRoom) {
					*pDestinationLevel = pDestinationRoomTile->nWarpId;
					*ppLvlWarpTxtRecord = DATATBLS_GetLvlWarpTxtRecord(pDestinationRoomTile->nWarpId);

					if (!pSourceRoomTile->pDrlgRoom->pRoom) {
						DRLGACTIVATE_InitializeRoomEx(pSourceRoomTile->pDrlgRoom);
					}

					return pSourceRoomTile->pDrlgRoom->pRoom;
				}
			}
		}
	}

	return NULL;
}

// D2Common.0x6FD787F0
void __fastcall DRLGWARP_ToggleRoomTilesEnableFlag(D2DrlgRoomStrc* pDrlgRoom, BOOL bEnabled) {
	for (D2RoomTileStrc* i = pDrlgRoom->pRoomTiles; i; i = i->pNext) {
		i->bEnabled = bEnabled;
	}
}

// D2Common.0x6FD78810
void __fastcall DRLGWARP_UpdateWarpRoomSelect(D2DrlgRoomStrc* pDrlgRoom, int nLevelId) {
	for (D2RoomTileStrc* pRoomTile = pDrlgRoom->pRoomTiles; pRoomTile; pRoomTile = pRoomTile->pNext) {
		if (pRoomTile->nWarpId == nLevelId) {
			if (pRoomTile->unk0x0C) {
				for (D2DrlgTileDataStrc* i = pRoomTile->unk0x0C; i; i = i->unk0x20) {
					i->dwFlags &= 0xFFFFFFF7;
				}

				for (D2DrlgTileDataStrc* i = pRoomTile->unk0x10; i; i = i->unk0x20) {
					i->dwFlags |= 8;
				}
			}
		}
	}
}

// D2Common.0x6FD78870
void __fastcall DRLGWARP_UpdateWarpRoomDeselect(D2DrlgRoomStrc* pDrlgRoom, int nLevelId) {
	for (D2RoomTileStrc* pRoomTile = pDrlgRoom->pRoomTiles; pRoomTile; pRoomTile = pRoomTile->pNext) {
		if (pRoomTile->nWarpId == nLevelId) {
			if (pRoomTile->unk0x10) {
				for (D2DrlgTileDataStrc* i = pRoomTile->unk0x10; i; i = i->unk0x20) {
					i->dwFlags &= 0xFFFFFFF7;
				}

				for (D2DrlgTileDataStrc* i = pRoomTile->unk0x0C; i; i = i->unk0x20) {
					i->dwFlags |= 8;
				}
			}
		}
	}
}

// D2Common.0x6FD788D0
// TODO: Name
D2ActiveRoomStrc* __fastcall sub_6FD788D0(D2DrlgStrc* pDrlg, int nLevelId, int nTileIndex, int* pX, int* pY) {
	static const D2CoordStrc stru_6FDCE6A0[] = {
		{ 1, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ 0, 1 },
		{ 0, 1 },
		{ 0, 1 },
		{ 0, 2 },
		{ 0, 3 },
		{ 0, 4 },
		{ 0, 5 }
	};

	D2LevelDefBin* pLevelDefBinRecord = NULL;
	D2DrlgLevelStrc* pLevel = NULL;
	D2DrlgRoomStrc* pDrlgRoom = NULL;
	unsigned int nMatches = 0;
	int nCounter = 0;
	int nFlags = 0;
	int nRand = 0;

	pLevelDefBinRecord = DATATBLS_GetLevelDefRecord(nLevelId);
	*pX = -1;
	*pY = -1;

	pLevel = DRLG_GetLevel(pDrlg, nLevelId);
	if (!pLevel->pFirstRoomEx) {
		DRLG_InitLevel(pLevel);
	}

	if (pLevelDefBinRecord->dwPosition) {
		if (nTileIndex == 13) {
			pDrlgRoom = DRLGWARP_GetWaypointRoomExFromLevel(pLevel, pX, pY);
			DRLGACTIVATE_InitializeRoomEx(pDrlgRoom);
			return pDrlgRoom->pRoom;
		}

		nMatches = 0;
		nRand = 0;
		for (int i = 0; i < pLevel->nTileInfo; ++i) {
			if (nTileIndex == pLevel->pTileInfo[i].nTileIndex || stru_6FDCE6A0[nTileIndex].nX && stru_6FDCE6A0[nTileIndex].nY == stru_6FDCE6A0[pLevel->pTileInfo[i].nTileIndex].nY) {
				++nMatches;
			}
		}

		if (nMatches) {
			nRand = SEED_RollLimitedRandomNumber(&pLevel->pSeed, nMatches) + 1;
		}

		for (int i = 0; i < pLevel->nTileInfo; ++i) {
			if (nTileIndex == pLevel->pTileInfo[i].nTileIndex || stru_6FDCE6A0[nTileIndex].nX && stru_6FDCE6A0[nTileIndex].nY == stru_6FDCE6A0[pLevel->pTileInfo[i].nTileIndex].nY) {
				--nRand;
			}

			if (nRand <= 0) {
				*pX = pLevel->pTileInfo[i].nPosX;
				*pY = pLevel->pTileInfo[i].nPosY;

				pDrlgRoom = DRLG_GetRoomExFromCoordinates(*pX, *pY, pLevel->pDrlg, 0, pLevel);
				DRLGACTIVATE_InitializeRoomEx(pDrlgRoom);
				return pDrlgRoom->pRoom;
			}
		}

		*pX = pLevel->pTileInfo[pLevel->nTileInfo].nPosX;
		*pY = pLevel->pTileInfo[pLevel->nTileInfo].nPosY;

		pDrlgRoom = DRLG_GetRoomExFromCoordinates(*pX, *pY, pLevel->pDrlg, 0, pLevel);
		DRLGACTIVATE_InitializeRoomEx(pDrlgRoom);
		return pDrlgRoom->pRoom;
	}

	pDrlgRoom = DRLGWARP_GetWaypointRoomExFromLevel(pLevel, pX, pY);
	if (!pDrlgRoom) {
		for (D2DrlgRoomStrc* i = pLevel->pFirstRoomEx; i; i = i->pDrlgRoomNext) {
			if (i->dwFlags & DRLGROOMFLAG_HAS_WARP_MASK) {
				nFlags = DRLGROOMFLAG_HAS_WARP_0;
				nCounter = 0;
				do {
					if (nFlags & i->dwFlags && DRLGWARP_GetWarpIdArrayFromLevelId(pLevel->pDrlg, pLevel->nLevelId)[nCounter] != -1) {
						if (*pX == -1 || *pY == -1) {
							*pX = i->nTileXPos + i->nTileWidth / 2;
							*pY = i->nTileYPos + i->nTileHeight / 2;
						}

						DRLGACTIVATE_InitializeRoomEx(i);
						return i->pRoom;
					}

					nFlags *= 2;
					++nCounter;
				} while (nFlags & DRLGROOMFLAG_HAS_WARP_MASK);
			}
		}

		pDrlgRoom = DRLG_GetRoomExFromLevelAndCoordinates(pLevel, pLevel->nWidth / 2 + pLevel->nPosX - 2, pLevel->nHeight / 2 + pLevel->nPosY - 2);
		if (!pDrlgRoom) {
			D2_CHECK(pLevel->pFirstRoomEx);

			pDrlgRoom = pLevel->pFirstRoomEx;

			for (int i = SEED_RollLimitedRandomNumber(&pLevel->pSeed, pLevel->nRooms); i; --i) {
				pDrlgRoom = pDrlgRoom->pDrlgRoomNext;
			}
		}
	}

	if (pDrlgRoom) {
		if (*pX == -1 || *pY == -1) {
			*pX = pDrlgRoom->nTileXPos + pDrlgRoom->nTileWidth / 2;
			*pY = pDrlgRoom->nTileYPos + pDrlgRoom->nTileHeight / 2;
		}

		DRLGACTIVATE_InitializeRoomEx(pDrlgRoom);
		return pDrlgRoom->pRoom;
	}

	return NULL;
}

// Helper function
static D2DrlgRoomStrc* DRLG_FindWaypointRoom(D2DrlgLevelStrc* pLevel) {
	for (D2DrlgRoomStrc* pDrlgRoom = pLevel->pFirstRoomEx; pDrlgRoom; pDrlgRoom = pDrlgRoom->pDrlgRoomNext) {
		if (DRLGROOM_CheckWaypointFlags(pDrlgRoom)) {
			return pDrlgRoom;
		}
	}
	return nullptr;
}

// D2Common.0x6FD78C10
D2DrlgRoomStrc* __fastcall DRLGWARP_GetWaypointRoomExFromLevel(D2DrlgLevelStrc* pLevel, int* pX, int* pY) {
	D2DrlgRoomStrc* pWaypointRoom = DRLG_FindWaypointRoom(pLevel);
	if (pWaypointRoom) {
		DRLGACTIVATE_InitializeRoomEx(pWaypointRoom);

		for (D2PresetUnitStrc* pPresetUnit = pWaypointRoom->pPresetUnits; pPresetUnit; pPresetUnit = pPresetUnit->pNext) {
			if (pPresetUnit->nUnitType == UNIT_OBJECT && pPresetUnit->nIndex < 573 && (DATATBLS_GetObjectsTxtRecord(pPresetUnit->nIndex)->nSubClass & OBJSUBCLASS_WAYPOINT)) {
				*pX = pWaypointRoom->nTileXPos + pPresetUnit->nXpos / 5;
				*pY = pWaypointRoom->nTileYPos + pPresetUnit->nYpos / 5;
				return pWaypointRoom;
			}
		}
	}
	return pWaypointRoom;
}

// D2Common.0x6FD78CC0
int* __fastcall DRLGWARP_GetWarpIdArrayFromLevelId(D2DrlgStrc* pDrlg, int nLevelId) {
	for (D2DrlgWarpStrc* pDrlgWarp = pDrlg->pWarp; pDrlgWarp; pDrlgWarp = pDrlgWarp->pNext) {
		if (!pDrlgWarp->nLevel) {
			FOG_DisplayWarning("ptVisInfo->eLevelId != LEVEL_ID_NONE", __FILE__, __LINE__);
		}

		if (nLevelId == pDrlgWarp->nLevel) {
			return pDrlgWarp->nWarp;
		}
	}

	return (int*)DATATBLS_GetLevelDefRecord(nLevelId)->dwWarp;
}

// 1.10f:D2Common.0x6FD78D10
// 1.11 :D2Common.0x6FD77400
// The array element is a lvlwarp *row index*, not a destination level id --
// cross-checked against the shipped data: the Blood Moor (levels.txt id 2) has
// Warp0..Warp7 = 2,-1,-1,-1,0,1,2,3, and lvlwarp rows 0..3 are the four
// "Wilderness to Cave" warps.  Retail 1.14d feeds this straight into
// DATATBLS_GetLvlWarpTxtRecord.
int __fastcall DRLGWARP_GetWarpIdFromArray(D2DrlgLevelStrc* pLevel, uint8_t nArrayId) {
	return DRLGWARP_GetWarpIdArrayFromLevelId(pLevel->pDrlg, pLevel->nLevelId)[nArrayId];
}

// 1.11 replaces the 1.10f "...AndDirection" variant: lvlwarp.txt has no
// Direction column, so retail just indexes the record.  Verified in
// D2Common.dll: walk pDrlg->pWarp for pLevel->nLevelId, take &warp[0x24],
// index it with the packed tile's style, then DATATBLS_GetLvlWarpTxtRecord().
D2LvlWarpTxt* __fastcall DRLGWARP_GetLvlWarpTxtRecordFromWarpId(D2DrlgLevelStrc* pLevel, uint8_t nWarpId) {
	return DATATBLS_GetLvlWarpTxtRecord(DRLGWARP_GetWarpIdFromArray(pLevel, nWarpId));
}

// D2Common.0x6FD78DF0
D2LvlWarpTxt* __fastcall DRLGWARP_GetLvlWarpTxtRecordFromUnit(D2DrlgRoomStrc* pDrlgRoom, D2UnitStrc* pUnit) {
	D2RoomTileStrc* pRoomTile = pDrlgRoom->pRoomTiles;
	int nClassId = 0;

	if (pUnit) {
		nClassId = pUnit->dwClassId;
	} else {
		nClassId = -1;
	}

	while (pRoomTile) {
		if (pRoomTile->nWarpId == nClassId && pRoomTile->bEnabled) {
			return DATATBLS_GetLvlWarpTxtRecord(pRoomTile->nWarpId);
		}

		pRoomTile = pRoomTile->pNext;
	}

	return NULL;
}
