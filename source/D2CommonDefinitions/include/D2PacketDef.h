#pragma once

#include <cstdint>

#pragma pack(1)

// Originally packets used a single byte for stat id, and prevented any stat with id > 255
// Set PACKETS_USE_16BITS_STATID to 1 if you want to support all stat ids.
#ifndef PACKETS_USE_16BITS_STATID
#define PACKETS_USE_16BITS_STATID 0
#endif

#if PACKETS_USE_16BITS_STATID
using PacketStatId = uint16_t;
#else
using PacketStatId = uint8_t;
#endif // PACKETS_USE_16BITS_STATID

// Sub-Structs
struct D2MessageStrc // sizeof 0x04
{
	uint8_t nMenu;		// 0x00
	uint8_t pad0x01;	// 0x01
	uint16_t nStringId; // 0x02
};

struct D2MessageListStrc // sizeof 0x22
{
	uint8_t nCount;				// 0x00
	uint8_t pad0x01;			// 0x01
	D2MessageStrc pMessages[8]; // 0x02
};

struct D2GSPacketClt01 // size of 0x05
{
	uint8_t nHeader; // 0x00
	uint16_t nPosX;	 // 0x01
	uint16_t nPosY;	 // 0x03
};

struct D2GSPacketClt02 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt03 // size of 0x05
{
	uint8_t nHeader; // 0x00
	uint16_t nPosX;	 // 0x01
	uint16_t nPosY;	 // 0x03
};

struct D2GSPacketClt04 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt05 // size of 0x05
{
	uint8_t nHeader; // 0x00
	uint16_t nPosX;	 // 0x01
	uint16_t nPosY;	 // 0x03
};

struct D2GSPacketClt06 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt07 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt08 // size of 0x05
{
	uint8_t nHeader; // 0x00
	uint16_t nPosX;	 // 0x01
	uint16_t nPosY;	 // 0x03
};

struct D2GSPacketClt09 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt0A // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt0B // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketClt0C // size of 0x05
{
	uint8_t nHeader; // 0x00
	uint16_t nPosX;	 // 0x01
	uint16_t nPosY;	 // 0x03
};

struct D2GSPacketClt0D // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt0E // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt0F // size of 0x05
{
	uint8_t nHeader; // 0x00
	uint16_t nPosX;	 // 0x01
	uint16_t nPosY;	 // 0x03
};

struct D2GSPacketClt10 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt11 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt12 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketClt13 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketClt14 // variable size
{
	uint8_t nHeader;	  // 0x00
	uint8_t nMessageType; // 0x01
	uint8_t nLang;		  // 0x02
	char szMessage[256];  // 0x03
};

struct D2GSPacketClt15 // variable size
{
	uint8_t nHeader;	  // 0x00
	uint8_t nMessageType; // 0x01
	uint8_t nLang;		  // 0x02
	// union
	//{
	//	char szMessage[256];//0x03

	//	//struct
	//	//{
	//	//	uint8_t nPlayerId;	//0x03
	//	//	int32_t nItemId;	//0x04
	//	//	char pExtraData[251];
	//	//};
	//};
	char szMessage[256]; // 0x03
	char szName[16];	 // 0x103
};

struct D2GSPacketClt16 // size of 0x0D
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitType; // 0x01
	uint32_t dwUnitGUID; // 0x05
	uint32_t bCursor;	 // 0x09
};

struct D2GSPacketClt17 // size of 0x05
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwItemGUID; // 0x01
};

struct D2GSPacketClt18 // size of 0x11
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwItemGUID; // 0x01
	uint32_t dwPosX;	 // 0x05
	uint32_t dwPosY;	 // 0x09
	uint32_t dwInvPage;	 // 0x0D
};

struct D2GSPacketClt19 // size of 0x05
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwItemGUID; // 0x01
};

// TODO: 0x1A - 0x1F

struct D2GSPacketClt20 // size of 0x0D
{
	uint8_t nHeader;   // 0x00
	int32_t nItemGUID; // 0x01
	int32_t nPosX;	   // 0x05
	int32_t nPosY;	   // 0x09
};

// TODO: 0x21 - 0x22

struct D2GSPacketClt23 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	int32_t unk0x01;	 // 0x01
	int32_t nBeltSlotId; // 0x05
};

// TODO: 0x24 - 0x25

struct D2GSPacketClt26 // size of 0x0D
{
	uint8_t nHeader;	 // 0x00
	int32_t nItemGUID;	 // 0x01
	uint32_t bUseOnMerc; // 0x05
	int32_t unk0x09;	 // 0x09
};

struct D2GSPacketClt27 // size of 0x09
{
	uint8_t nHeader;		 // 0x00
	int32_t nTargetItemGUID; // 0x01
	int32_t nUseItemGUID;	 // 0x05
};

// TODO: 0x28

struct D2GSPacketClt29 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	int32_t nScrollGUID; // 0x01
	int32_t nBookGUID;	 // 0x05
};

struct D2GSPacketClt2A // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwItemGUID; // 0x01
	uint32_t dwCubeGUID; // 0x05
};

// CUSTOM - Unused in Vanilla
struct D2GSPacketClt2B // size of 0x23
{
	uint8_t nHeader;		   // 0x00
	int32_t nUnitGUID;		   // 0x01
	uint8_t nOptionValues[39]; // 0x05
};

// Unused: 0x2C - 0x2D

// struct D2GSPacketClt2E	//size of 0x05
//{
//	uint8_t nHeader;		//0x00
//	uint32_t dwType;		//0x01
// };

// TODO: 0x2F - 0x30

struct D2GSPacketClt31 // size of 0x09
{
	uint8_t nHeader;	// 0x00
	int32_t unk0x01[2]; // 0x01
};

struct D2GSPacketClt32 // size of 0x11
{
	uint8_t nHeader;		   // 0x00
	int32_t dwNpcGUID;		   // 0x01
	int32_t dwItemGUID;		   // 0x05
	uint16_t nTransactionType; // 0x09
	struct {				   // 0x0B
		uint16_t nItemMode : 15;
		uint16_t bMultibuy : 1;
	};
	int32_t dwCost; // 0x0D
};

struct D2GSPacketClt33 // size of 0x11
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwMonGUID;	 // 0x01
	uint32_t dwItemGUID; // 0x05
	uint16_t nTab;		 // 0x09
	uint16_t unk0x0B;	 // 0x0B
	uint32_t dwGold;	 // 0x0D
};

// TODO: 0x34 - 0x37

struct D2GSPacketClt38 // size of 0x0D
{
	uint8_t nHeader;   // 0x00
	uint32_t nAction;  // 0x01
	int32_t nNpcGUID;  // 0x05
	int32_t nItemGUID; // 0x09
};

// TODO: 0x39

struct D2GSPacketClt3A // size of 0x07
{
	uint8_t nHeader; // 0x00
	uint16_t nStat;	 // 0x01
	int32_t nPoints; // 0x03 ???
};

struct D2GSPacketClt3B // size of 0x03
{
	uint8_t nHeader; // 0x00
	uint16_t nSkill; // 0x01
};

struct D2GSPacketClt3C // size of 0x09
{
	uint8_t nHeader;  // 0x00
	uint16_t nSkill;  // 0x01
	uint16_t nMode;	  // 0x03
	uint32_t dwFlags; // 0x04
};

struct D2GSPacketClt3D // size of 0x05
{
	uint8_t nHeader;   // 0x00
	int32_t nDoorGUID; // 0x01
};

// TODO: 0x3E - 0x40

struct D2GSPacketClt41 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketClt42 // size of 0x0B
{
	uint8_t nHeader;	// 0x00
	char szVersion[10]; // 0x01
};

// TODO: 0x43

struct D2GSPacketClt44 // size of 0x11
{
	uint8_t nHeader;			// 0x00
	int32_t nPlayerGUID;		// 0x01
	int32_t nAnvilInteractGUID; // 0x05
	int32_t nItemGUID;			// 0x09
	short nState;				// 0x0D
	short unk0x0F;				// 0x0F
};

struct D2GSPacketClt45 // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	int32_t nPortalGUID; // 0x01
	int32_t nLevelId;	 // 0x05
};

// TODO: 0x46 - 0x48

struct D2GSPacketClt49 // size of 0x09
{
	uint8_t nHeader;	   // 0x00
	int32_t nWaypointGUID; // 0x01
	int32_t nLevelId;	   // 0x05
};

// TODO: 0x4A - 0x4E

struct D2GSPacketClt4F // size of 0x07
{
	uint8_t nHeader;	// 0x00
	uint16_t nButtonId; // 0x01
	union {
		struct
		{
			uint16_t nParams[2]; // 0x03
		};

		int32_t nItemGUID; // 0x03
	};
};

// TODO: 0x50

struct D2GSPacketClt51 {
	uint8_t nHeader;	// 0x00
	int32_t nSkillId;	// 0x01
	int32_t nOwnerGUID; // 0x05
};

// TODO: 0x52 - 0x57

struct D2GSPacketClt58 // size of 0x03
{
	uint8_t nHeader; // 0x00
	uint16_t nQuest; // 0x01
};

struct D2GSPacketClt59 // size of 0x11
{
	uint8_t nHeader;	 // 0x00
	uint32_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x05
	uint32_t dwTargetX;	 // 0x09
	uint32_t dwTargetY;	 // 0x0D
};

// TODO: 0x5A - 0x5C

struct D2GSPacketClt5D // size of 0x07
{
	uint8_t nHeader;	   // 0x00
	uint8_t nType;		   // 0x01
	uint8_t nToggle;	   // 0x02
	uint32_t dwPlayerGUID; // 0x03
};

struct D2GSPacketClt5E // size of 0x06
{
	uint8_t nHeader;	  // 0x00
	uint8_t nType;		  // 0x01
	int32_t dwPlayerGUID; // 0x02
};

struct D2GSPacketClt5F {
	uint8_t nHeader; // 0x00
	uint16_t nX;	 // 0x01
	uint16_t nY;	 // 0x02
};

// TODO: 0x60 - 0x62

struct D2GSPacketClt63 // size of 0x05
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwItemGUID; // 0x01
};

struct D2GSPacketClt64 // size of 0x09
{
	uint8_t nHeader;	// 0x00
	int32_t unk0x01[2]; // 0x01
};

struct D2GSPacketClt65 // size of 0x11
{
	uint8_t nHeader;	// 0x00
	int32_t unk0x01[4]; // 0x01
};

struct D2GSPacketClt66 // size of 0x2E
{
	uint8_t nHeader;	   // 0x00
	char szGameName[16];   // 0x01
	uint8_t nGameType;	   // 0x11
	uint8_t nPlayerClass;  // 0x12
	int8_t nTemplate;	   // 0x13
	int8_t nDifficulty;	   // 0x14
	char szClientName[16]; // 0x15
	int16_t wArena;		   // 0x25
	uint32_t nGameFlags;   // 0x27
	int8_t unk0x2B;		   // 0x2B
	int8_t unk0x2C;		   // 0x2C
	int8_t nLocale;		   // 0x2D
};

struct D2GSPacketClt67 // size of 0x1D
{
	uint8_t nHeader;	   // 0x00
	int32_t nTokenId;	   // 0x01
	uint16_t nGameId;	   // 0x05
	uint8_t nPlayerClass;  // 0x07
	int32_t unk0x08;	   // 0x08
	uint8_t nLocale;	   // 0x0C
	char szClientName[16]; // 0x0D
};

struct D2GSPacketClt68 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketClt69 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketClt6A // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketClt6B {
	uint8_t nHeader;		// 0x00
	uint8_t nSize;			// 0x01
	uint32_t nTotalSize;	// 0x02
	uint8_t saveData[8192]; // 0x06
							//...
};

struct D2GSPacketClt6C // size of 0x09
{
	uint8_t nHeader; // 0x00
	int32_t unk0x01; // 0x01
	int32_t unk0x05; // 0x05
};

struct D2GSPacketClt6D // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketClt6F // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv00 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv01 // size of 0x08
{
	uint8_t nHeader;	   // 0x00
	uint8_t nDifficulty;   // 0x01
	uint32_t dwArenaFlags; // 0x02
	uint8_t nExpansion;	   // 0x06
	uint8_t nLadder;	   // 0x07
};

struct D2GSPacketSrv02 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv03 // size of 0x0C
{
	uint8_t nHeader;	   // 0x00
	uint8_t nAct;		   // 0x01
	uint32_t dwGameSeed;   // 0x02
	uint16_t nTownLevelId; // 0x06
	uint32_t nObjectSeed;  // 0x08
};

struct D2GSPacketSrv04 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv05 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv06 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv07 // size of 0x06
{
	uint8_t nHeader;  // 0x00
	uint16_t nX;	  // 0x01
	uint16_t nY;	  // 0x03
	uint8_t nLevelId; // 0x05
};

struct D2GSPacketSrv08 // size of 0x06
{
	uint8_t nHeader;  // 0x00
	uint16_t nX;	  // 0x01
	uint16_t nY;	  // 0x03
	uint8_t nLevelId; // 0x04
};

struct D2GSPacketSrv09 // size of 0x0B
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	uint8_t unk0x06;	 // 0x06
	uint16_t nPosX;		 // 0x07
	uint16_t nPosY;		 // 0x09
						 // uint16_t nWarp;				//0x0A
};

struct D2GSPacketSrv0A // size of 0x06
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
};

struct D2GSPacketSrv0B // size of 0x06
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
};

struct D2GSPacketSrv0C // size of 0x09
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	uint8_t unk0x06;	 // 0x06
	uint8_t nHitClass;	 // 0x07
	uint8_t nLife;		 // 0x08
};

struct D2GSPacketSrv0D // size of 0x0D
{
	uint8_t nHeader;	  // 0x00
	uint8_t nUnitType;	  // 0x01
	uint32_t dwUnitGUID;  // 0x02
	uint8_t nHitClass;	  // 0x06
	uint16_t nX;		  // 0x07
	uint16_t nY;		  // 0x09
	uint8_t nHitType;	  // 0x0B
	uint8_t nUnitLifePct; // 0x0C
};

struct D2GSPacketSrv0E // size of 0x0C
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	uint8_t unk0x06;	 // 0x06
	uint8_t unk0x07;	 // 0x07
	uint32_t unk0x08;	 // 0x08
};

struct D2GSPacketSrv0F // size of 0x10
{
	uint8_t nHeader;	   // 0x00
	uint8_t nUnitType;	   // 0x01
	uint32_t dwUnitGUID;   // 0x02
	uint8_t nFlags;		   // 0x06
	uint16_t nDestPosX;	   // 0x07
	uint16_t nDestPosY;	   // 0x09
	uint8_t unk0x00B;	   // 0x0B
	uint16_t nCurrentPosX; // 0x0C
	uint16_t nCurrentPosY; // 0x0E
};

struct D2GSPacketSrv10 // size of 0x10
{
	uint8_t nHeader;	   // 0x00
	uint8_t nUnitType;	   // 0x01
	uint32_t dwUnitGUID;   // 0x02
	uint8_t nFlags;		   // 0x06
	uint8_t nTargetType;   // 0x07
	uint32_t dwTargetGUID; // 0x08
	uint16_t nCurrentPosX; // 0x0C
	uint16_t nCurrentPosY; // 0x0E
};

struct D2GSPacketSrv11 // size of 0x08
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	uint16_t unk0x006;	 // 0x06
};

struct D2GSPacketSrv12 // size of 0x1A
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[25]; // 0x01
};

struct D2GSPacketSrv13 // size of 0x0E
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[13]; // 0x01
};

struct D2GSPacketSrv14 // size of 0x12
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[17]; // 0x01
};

struct D2GSPacketSrv15 // size of 0x0B
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	uint16_t nPosX;		 // 0x06
	uint16_t nPosY;		 // 0x08
	uint8_t unk0x00A;	 // 0x0A
};

struct D2ClientUnitUpdateStrc {
	uint8_t nUnitType; // 0x00
	int32_t nUnitGUID; // 0x01
	uint16_t nX;	   // 0x05
	uint16_t nY;	   // 0x07
};

struct D2GSPacketSrv16 // variable size
{
	uint8_t nHeader;					   // 0x00
	uint16_t nSize;						   // 0x01
	uint8_t nNumUpdates;				   // 0x03
	D2ClientUnitUpdateStrc unitUpdate[55]; // 0x04
};

struct D2GSPacketSrv17 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv18 // size of 0x0F
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[14]; // 0x01
};

struct D2GSPacketSrv19 // size of 0x02
{
	uint8_t nHeader; // 0x00
	uint8_t nGold;	 // 0x01
};

struct D2GSPacketSrv1A // size of 0x02
{
	uint8_t nHeader;	 // 0x00
	uint8_t nExperience; // 0x01
};

struct D2GSPacketSrv1B // size of 0x03
{
	uint8_t nHeader;	  // 0x00
	uint16_t nExperience; // 0x01
};

struct D2GSPacketSrv1C // size of 0x05
{
	uint8_t nHeader;	  // 0x00
	uint32_t nExperience; // 0x01
};

// struct D2GSPacketSrv1D		//size of 0x03
//{
//	uint8_t nHeader;			//0x00
//	uint8_t nStat;				//0x01
//	uint8_t nValue;			//0x02
// };
//
// struct D2GSPacketSrv1E		//size of 0x04
//{
//	uint8_t nHeader;			//0x00
//	uint8_t nStat;				//0x01
//	uint16_t nValue;			//0x02
// };
//
// struct D2GSPacketSrv1F		//size of 0x06
//{
//	uint8_t nHeader;			//0x00
//	uint8_t nStat;				//0x01
//	int32_t nValue;				//0x02
// };
//
// struct D2GSPacketSrv20	//size of 0x0A
//{
//	uint8_t nHeader;			//0x00
//	uint32_t dwUnitGUID;		//0x01
//	uint8_t nStat;				//0x05
//	int32_t nValue;				//0x06
// };

// NOTE(D2MOO): 0x1D/0x1E/0x1F are THREE DIFFERENT wire sizes, not one union.
// The retail client sizes every S->C packet from a fixed per-header table
// (Game.exe: `mov 0x730ae8(,%edx,4),%eax` in the size routine at 0x52b920), which
// says 0x1D=3, 0x1E=4, 0x1F=6.  Sharing one struct here made the engine emit a
// 3-byte 0x1E/0x1F, so the client consumed 1 (resp. 3) extra bytes per packet,
// drifted out of alignment, and started reinterpreting the middle of the stat
// stream as 0x09 "create unit" packets -- which is what made it assert
// "Unable to find room for unit".  Keep these three separate and in sync with
// the client table.
struct D2GSPacketSrv1D // size of 0x03
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint8_t nValue;		// 0x02
};

struct D2GSPacketSrv1E // size of 0x04
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint16_t nValue;	// 0x02
};

struct D2GSPacketSrv1F // size of 0x06
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint32_t nValue;	// 0x02
};

struct D2GSPacketSrvStat // size of 0x03 (the 8-bit-value form; == D2GSPacketSrv1D)
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint8_t nValue;		// 0x02
};

struct D2GSPacketSrv20 // size of 0x0B (originally 0x0A)
{
	uint8_t nHeader;	 // 0x00
	uint32_t dwUnitGUID; // 0x01
	PacketStatId nStat;	 // 0x05
	int32_t nValue;		 // 0x07 (Originally 0x06)
};

struct D2GSPacketSrv21 // size of 0x0C
{
	uint8_t nHeader;		  // 0x00
	uint8_t nUnitType;		  // 0x01
	uint8_t unk0x02;		  // 0x02
	uint32_t nUnitGUID;		  // 0x03
	uint16_t nSkillId;		  // 0x07
	uint8_t nSkillLevel;	  // 0x09
	uint8_t nBonusSkillLevel; // 0x0A
	uint8_t unk0x0B;		  // 0x0B
};

struct D2GSPacketSrv22 // size of 0x0C
{
	uint8_t nHeader;   // 0x00
	uint8_t nUnitType; // 0x01
	uint8_t unk0x02;   // 0x02
	int32_t nUnitGUID; // 0x03
	uint16_t nSkillId; // 0x07
	uint8_t nQuantity; // 0x09
	uint8_t unk0x0A;   // 0x0A
	uint8_t bIsCorpse; // 0x0B
};

struct D2GSPacketSrv23 // size of 0x0D
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	uint8_t nPosition;	 // 0x06
	uint16_t nSkill;	 // 0x07
	uint32_t unk0x009;	 // 0x09
};

struct D2GSPacketSrv24 // size of 0x5A
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[89]; // 0x01
};

struct D2GSPacketSrv25 // size of 0x5A
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[89]; // 0x01
};

struct D2GSPacketSrv26 // variable size
{
	uint8_t nHeader;	   // 0x00
	uint8_t nMessageType;  // 0x01
	uint8_t nLang;		   // 0x02
	uint8_t nUnitType;	   // 0x03
	uint32_t dwUnitGUID;   // 0x04
	uint8_t nMessageColor; // 0x08
	uint8_t nNameColor;	   // 0x09
	char szName[16];	   // 0x0A
	char szMessage[256];   // 0x1A
};

struct D2GSPacketSrv26Args {
	D2GSPacketSrv26* pPacket26; // 0x00
	D2GSPacketClt15* pPacket15; // 0x04
	int32_t nUnitId;			// 0x08
};

struct D2GSPacketSrv27 // size of 0x28
{
	uint8_t nHeader;				// 0x00
	uint8_t nUnitType;				// 0x01
	uint32_t dwUnitGUID;			// 0x02
	D2MessageListStrc pMessageList; // 0x06
};

struct D2GSPacketSrv28 // size of 0x67
{
	uint8_t nHeader;   // 0x00
	uint8_t unk0x01;   // 0x01
	uint32_t unk0x02;  // 0x02
	uint8_t unk0x06;   // 0x06
	uint8_t pData[96]; // 0x07
};

struct D2GSPacketSrv29 // size of 0x61
{
	uint8_t nHeader;   // 0x00
	uint8_t pData[96]; // 0x01
};

struct D2GSPacketSrv2A // size of 0x0F
{
	uint8_t nHeader;  // 0x00
	uint8_t unk0x01;  // 0x01
	uint8_t unk0x02;  // 0x02
	uint32_t unk0x03; // 0x03
	uint32_t unk0x07; // 0x07
	uint32_t unk0x0B; // 0x0B
};

// Unused: 0x2B
struct D2GSPacketSrv2B // size of 0x09
{
	uint8_t nHeader;  // 0x00
	uint32_t dwSkill; // 0x01
	uint32_t dwFrame; // 0x05
};

struct D2GSPacketSrv2C // size of 0x08
{
	uint8_t nHeader;	  // 0x00
	uint8_t nUnitType;	  // 0x01
	uint32_t dwUnitGUID;  // 0x02
	uint16_t nSoundEvent; // 0x06
};

// Unused: 0x2D - 0x3D
// struct D2GSPacketSrv2D		//size of 0x01
//{
//	uint8_t nHeader;					//0x00
//	uint8_t nUnitType;					//0x01
//	uint32_t dwUnitGUID;				//0x02
//	uint32_t dwRecords[3];				//0x06
//	uint32_t dwData[3];				//0x12
//	BOOL bCompleted[3];				//0x1E
//	uint32_t dwCompletionCount[3];		//0x2A
// };
//
// struct D2GSPacketSrv2E		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv2F		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv30		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv31		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv32		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv33		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv34		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv35		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv36		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv37		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv38		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv39		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
struct D2GSPacketSrv3A // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv3B // size of 0x01
{
	uint8_t nHeader; // 0x00
};

// struct D2GSPacketSrv3C		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv3D		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

struct D2GSPacketSrv3E // size of 0x22
{
	uint8_t nHeader;	 // 0x00
	uint8_t nSize;		 // 0x01
	uint8_t pBuffer[32]; // 0x02
};

struct D2GSPacketSrv3F // size of 0x08
{
	uint8_t nHeader;   // 0x00
	uint8_t nCursor;   // 0x01
	uint32_t dwItemId; // 0x02
	uint16_t nSkill;   // 0x06
};

struct D2GSPacketSrv40 // size of 0x0D
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[12]; // 0x01
};

// struct D2GSPacketSrv41		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

struct D2GSPacketSrv42 // size of 0x06
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
};

// struct D2GSPacketSrv43		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv44		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

struct D2GSPacketSrv45 // size of 0x0D
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[12]; // 0x01
};

// struct D2GSPacketSrv46		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

struct D2GSPacketSrv47 // size of 0x0B
{
	uint8_t nHeader;	// 0x00
	uint8_t nUnitType;	// 0x01
	uint8_t unk0x02;	// 0x02
	uint32_t nUnitGUID; // 0x03
	uint32_t unk0x07;	// 0x07
};

struct D2GSPacketSrv48 // size of 0x0B
{
	uint8_t nHeader;	// 0x00
	uint8_t nUnitType;	// 0x01
	uint8_t unk0x02;	// 0x02
	uint32_t nUnitGUID; // 0x03
	uint32_t unk0x07;	// 0x07
};

// struct D2GSPacketSrv49		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv4A		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv4B		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

struct D2GSPacketSrv4C // size of 0x10
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[15]; // 0x01
};

struct D2GSPacketSrv4D // size of 0x11
{
	uint8_t nHeader;  // 0x00
	uint8_t unk0x01;  // 0x01
	uint32_t unk0x02; // 0x02
	uint32_t unk0x06; // 0x06
	uint8_t unk0x0A;  // 0x0A
	uint16_t unk0x0B; // 0x0B
	uint16_t unk0x0D; // 0x0D
	uint16_t unk0x0F; // 0x0F
};

struct D2GSPacketSrv4E // size of 0x07
{
	uint8_t nHeader;	// 0x00
	uint16_t nMercName; // 0x01
	uint32_t nSeed;		// 0x03
};

struct D2GSPacketSrv4F // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv50 // size of 0x0F
{
	uint8_t nHeader;   // 0x00
	uint16_t nQuestId; // 0x01

	union {
		struct
		{
			uint16_t nMonstersToBeKilled;	// 0x03
			uint16_t nStaffTombLevelOffset; // 0x05
			uint16_t nBarbsToBeRescued;		// 0x07
			uint8_t field_9;				// 0x09
			uint8_t field_A;				// 0x0A
			uint8_t field_B;				// 0x0B
			uint16_t field_C;				// 0x0C
			uint8_t field_E;				// 0x0E
		} QuestsStatusPayload;				// Used with QuestId = QUEST_A1Q1_DENOFEVIL(1)

		struct
		{
			uint16_t nHireling;		 // 0x03
			uint16_t padding0x05[5]; // 0x05
		} HirelingPayload;			 // Used with QuestId = QUEST_A1Q2_BLOODRAVEN(2)

		struct
		{
			uint16_t nStaffTombLevelOffset; // 0x03
			uint16_t padding0x05[5];		// 0x05
		} TombOffsetPayload;				// Used with QuestId = QUEST_A2Q6_DURIEL(13)

		struct
		{
			uint16_t nStoneOrder[5]; // 0x03
			uint16_t padding0x0D;	 // 0x0D
		} A1Q4_CainPayload;			 // Used with QuestId = 4 (QUEST_A1Q4_CAIN)

		struct
		{
			uint16_t nZooMonsterId;	 // 0x03
			uint16_t padding0x05[5]; // 0x05
		} A5Q6_BaalPayload;			 // Used with QuestId = 36 (QUEST_A5Q6_BAAL)
	};
};

struct D2GSPacketSrv51 // size of 0x0E
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	uint16_t nObject;	 // 0x06
	uint16_t nPosX;		 // 0x08
	uint16_t nPosY;		 // 0x0A
	uint8_t unk0x0C[2];	 // 0x0C
};

struct D2GSPacketSrv52 // size of 0x2A
{
	uint8_t nHeader;		// 0x00
	uint8_t pQuestList[41]; // 0x01 count:MAX_QUEST_STATUS
};

struct D2GSPacketSrv53 // size of 0x0A
{
	uint8_t nHeader; // 0x00
	int32_t unk0x01; // 0x01
	int32_t unk0x05; // 0x05
	uint8_t unk0x09; // 0x09
};

// NOTE(D2MOO): client size table (Game.exe 0x730AE8) and handler-table
// expected-size (0x7114D0 + 0x54*12 + 4) both say 3; the client's 0x54 handler
// (0x45E3B0) is a bare `ret`, i.e. a no-op stub.
struct D2GSPacketSrv54 // size of 0x03
{
	uint8_t nHeader;	// 0x00
	uint8_t unk0x01[2]; // 0x01
};

struct D2GSPacketSrv55 // size of 0x03
{
	uint8_t nHeader;	 // 0x00
	uint8_t unk0x001[2]; // 0x01
};

// struct D2GSPacketSrv56		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

struct D2GSPacketSrv57 // size of 0x0E
{
	uint8_t nHeader;  // 0x00
	uint32_t unk0x01; // 0x01
	uint8_t unk0x05;  // 0x05
	uint16_t unk0x06; // 0x06
	uint16_t unk0x08; // 0x08
	uint16_t unk0x0A; // 0x0A
	uint16_t unk0x0C; // 0x0C
};

struct D2GSPacketSrv58 // size of 0x0E
{
	uint8_t nHeader; // 0x00
	int32_t nUnitId; // 0x01
	// uint8_t unk0x05[9];		//0x05
	uint8_t unk0x05; // 0x05
	uint8_t unk0x06; // 0x06
};

struct D2GSPacketSrv59 // size of 0x1A
{
	uint8_t nHeader; // 0x00
	uint32_t dwGUID; // 0x01
	uint8_t nClass;	 // 0x05
	char szName[16]; // 0x06
	uint16_t nPosX;	 // 0x16
	uint16_t nPosY;	 // 0x18
};

struct D2GSPacketSrv5A // size of 0x28
{
	uint8_t nHeader; // 0x00
	uint8_t nType;	 // 0x01
	union {
		struct // nType < 0x13
		{
			uint8_t nColor;	  // 0x02
			uint32_t dwParam; // 0x03
			uint8_t nParam;	  // 0x07
			union {
				char szText[32];		// 0x08
				char szTextData[2][16]; // 0x08
			};
		};

		struct // nType 0x13
		{
			uint32_t dwSkill;		 // 0x02
			uint32_t dwEndFrame;	 // 0x06
			uint8_t nExtraData2[30]; // 0x0A
		};

		struct // nType 0x14
		{
			uint8_t nGroup;			  // 0x02
			uint32_t dwGroupEndFrame; // 0x03
			uint8_t nExtraData3[33];  // 0x07
		};

		struct // nType 0x16
		{
			int32_t nItemId;		 // 0x02
			int32_t nPlayerId;		 // 0x06
			uint8_t nExtraData4[30]; // 0x0A
		};

		struct // nType 0x17
		{
			uint8_t nDamageColor;	 // 0x02
			uint32_t dwDamage;		 // 0x03
			int32_t nDefenderGUID;	 // 0x07
			int32_t nDefenderType;	 // 0x0B
			uint8_t nExtraData5[25]; // 0x0F
		};

		struct // nType 0x18
		{
			uint8_t nUnitType;		 // 0x02
			int32_t nItemGUID;		 // 0x03
			uint8_t nAction;		 // 0x07
			int32_t nPosX;			 // 0x08
			int32_t nPosY;			 // 0x0C
			uint8_t nExtraData6[24]; // 0x10
		};

		struct // nType 0x19
		{
			uint8_t nDefenderUnitType;	 // 0x02
			int32_t nDefenderUnitGUID;	 // 0x03
			uint8_t nAttackerUnitType;	 // 0x07
			int32_t nAttackerUnitGUID;	 // 0x08
			uint8_t nAttackMessageColor; // 0x0C
			uint8_t nExtraData7[27];	 // 0x0D
		};

		struct // nType 0x1A
		{
			int32_t nFrames;		 // 0x02
			uint8_t nExtraData8[34]; // 0x06
		};

		struct // nType 0x1B
		{
			int32_t nCount;			 // 0x02
			uint8_t nExtraData9[34]; // 0x06
		};
	};
};

struct D2GSPacketSrv5B // variable size
{
	uint8_t nHeader;	  // 0x00
	uint16_t nPacketLen;  // 0x01
	uint32_t nUnitGUID;	  // 0x03
	uint8_t nClass;		  // 0x07
	char szName[16];	  // 0x08
	uint16_t nLevel;	  // 0x18
	uint16_t nPartyId;	  // 0x1A
	uint16_t unk0x1C;	  // 0x1C
	uint16_t nPartyFlags; // 0x1E
	uint16_t unk0x20;	  // 0x20
	char unk0x22[256];	  // 0x22
};

struct D2GSPacketSrv5C // size of 0x05
{
	uint8_t nHeader;	   // 0x00
	uint32_t dwPlayerGUID; // 0x01
};

struct D2GSPacketSrv5D // size of 0x06
{
	uint8_t nHeader;  // 0x00
	uint8_t nQuestId; // 0x01
	uint8_t nFlags;	  // 0x02
	uint8_t nState;	  // 0x03
	uint16_t field_4; // 0x04
};

struct D2GSPacketSrv5E // size of 0x26
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[37]; // 0x01
};

struct D2GSPacketSrv5F // size of 0x05
{
	uint8_t nHeader;	 // 0x00
	uint8_t unk0x001[4]; // 0x01
};

struct D2GSPacketSrv60 // size of 0x07
{
	uint8_t nHeader;	 // 0x00
	uint8_t nFlags;		 // 0x01
	uint8_t nLevel;		 // 0x02
	uint32_t dwUnitGUID; // 0x03
};

struct D2GSPacketSrv61 // size of 0x02
{
	uint8_t nHeader;  // 0x00
	uint8_t unk0x001; // 0x01
};

struct D2GSPacketSrv62 // size of 0x07
{
	uint8_t nHeader;   // 0x00
	uint8_t nUnitType; // 0x01
	int32_t nUnitId;   // 0x02
	uint8_t unk0x06;   // 0x06
};

struct D2GSPacketSrv63 // variable size
{
	uint8_t nHeader;   // 0x00
	uint32_t dwUnitId; // 0x01
	uint16_t pData[8]; // 0x05
};

// struct D2GSPacketSrv64		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

////TODO: Other Structure
// struct D2GSPacketSrv65		//size of 0x09
//{
//	uint8_t nHeader;			//0x00
//	uint8_t nUpdateTeamScore;	//0x01
//	uint32_t dwPlayerGUID;		//0x02
//	uint32_t dwScore;			//0x06
//	uint32_t dwTeamScore;		//0x0A
// };

struct D2GSPacketSrv65 // size of 0x07
{
	uint8_t nHeader;   // 0x00
	uint32_t dwUnitId; // 0x01
	uint16_t unk0x05;  // 0x05
};

struct D2GSPacketSrv66 // size of 0x07
{
	uint8_t nHeader;	 // 0x00
	uint8_t unk0x001[6]; // 0x01
};

struct D2GSPacketSrv67 // size of 0x10
{
	uint8_t nHeader;   // 0x00
	int32_t nUnitGUID; // 0x01
	uint8_t unk0x05;   // 0x05
	int16_t nX;		   // 0x06
	int16_t nY;		   // 0x08
	int8_t unk0x0A;	   // 0x0A
	int8_t unk0x0B;	   // 0x0B
	int8_t nPathType;  // 0x0C
	int16_t nVelocity; // 0x0D
	int8_t unk0x0F;	   // 0x0F
};

struct D2GSPacketSrv68 // size of 0x15
{
	uint8_t nHeader;   // 0x00
	int32_t nUnitGUID; // 0x01
	uint8_t unk0x05;   // 0x05
	int16_t nX;		   // 0x06
	int16_t nY;		   // 0x08
	int8_t unk0x0A;	   // 0x0A
	int32_t unk0x0B;   // 0x0B
	int8_t unk0x0F;	   // 0x0F
	int8_t unk0x10;	   // 0x10
	int8_t nPathType;  // 0x11
	int16_t nVelocity; // 0x12
	int8_t unk0x14;	   // 0x14
};

struct D2GSPacketSrv69 // size of 0x0C
{
	uint8_t nHeader;  // 0x00
	uint32_t unk0x01; // 0x01
	uint8_t unk0x05;  // 0x05
	uint16_t unk0x06; // 0x06
	uint16_t unk0x08; // 0x08
	uint8_t unk0x0A;  // 0x0A
	uint8_t unk0x0B;  // 0x0B
};

struct D2GSPacketSrv6A // size of 0x0C
{
	uint8_t nHeader;		  // 0x00
	uint32_t nUnitGUID;		  // 0x01
	uint8_t unk0x05;		  // 0x05
	uint8_t nTargetUnitType;  // 0x06
	uint32_t nTargetUnitGuid; // 0x07
	uint8_t nDirection;		  // 0x0B
};

struct D2GSPacketSrv6B // size of 0x10
{
	uint8_t nHeader;  // 0x00
	uint32_t unk0x01; // 0x01
	uint8_t unk0x05;  // 0x05
	uint16_t unk0x06; // 0x06
	uint16_t unk0x08; // 0x08
	uint8_t unk0x0A;  // 0x0A
	uint8_t unk0x0B;  // 0x0B
	uint16_t unk0x0C; // 0x0C
	uint16_t unk0x0E; // 0x0E
};

struct D2GSPacketSrv6C // size of 0x10
{
	uint8_t nHeader;  // 0x00
	uint32_t unk0x01; // 0x01
	uint8_t unk0x05;  // 0x05
	uint8_t unk0x06;  // 0x06
	uint32_t unk0x07; // 0x07
	uint8_t unk0x0B;  // 0x0B
	uint16_t unk0x0C; // 0x0C
	uint16_t unk0x0E; // 0x0E
};

struct D2GSPacketSrv6D // size of 0x0A
{
	uint8_t nHeader;  // 0x00
	uint32_t unk0x01; // 0x01
	uint16_t unk0x05; // 0x05
	uint16_t unk0x07; // 0x07
	uint8_t unk0x09;  // 0x09
};

struct D2GSPacketSrv6E // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv6F // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv70 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv71 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv72 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv73 // size of 0x20
{
	uint8_t nHeader;	   // 0x00
	int32_t unk0x01;	   // 0x01
	int16_t nMissileId;	   // 0x05
	int32_t nX;			   // 0x07
	int32_t nY;			   // 0x0B
	int32_t nFirstX;	   // 0x0F
	int32_t nFirstY;	   // 0x13
	int16_t nCurrentFrame; // 0x17
	uint8_t nUnitType;	   // 0x19
	int32_t nUnitGUID;	   // 0x1A
	uint8_t nLevel;		   // 0x1E
	uint8_t nPierce;	   // 0x1F
};

struct D2GSPacketSrv74 // size of 0x0A
{
	uint8_t nHeader; // 0x00
	uint8_t unk0x01; // 0x01
	int32_t unk0x02; // 0x02
	int32_t unk0x06; // 0x06
};

struct D2GSPacketSrv75 // size of 0x0D
{
	uint8_t nHeader;	// 0x00
	uint32_t nUnitGUID; // 0x01
	uint16_t nPartyId;	// 0x05
	uint16_t nLevel;	// 0x07
	uint16_t nFlags;	// 0x09
	uint16_t unk0x0B;	// 0x0B
};

struct D2GSPacketSrv76 // size of 0x06
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
};

struct D2GSPacketSrv77 // size of 0x02
{
	uint8_t nHeader; // 0x00
	uint8_t nAction; // 0x01
};

struct D2GSPacketSrv78 // size of 0x15
{
	uint8_t nHeader;	   // 0x00
	char szName[16];	   // 0x01
	uint32_t dwPlayerGUID; // 0x11
};

struct D2GSPacketSrv79 // size of 0x06
{
	uint8_t nHeader;	// 0x00
	uint8_t nOwnerGUID; // 0x01
	uint32_t dwGold;	// 0x02
};

struct D2GSPacketSrv7A // size of 0x0D
{
	uint8_t nHeader;  // 0x00
	uint8_t unk0x01;  // 0x01
	uint8_t unk0x02;  // 0x02
	uint16_t unk0x03; // 0x03
	uint32_t unk0x05; // 0x05
	uint32_t unk0x09; // 0x09
};

struct D2GSPacketSrv7B // size of 0x08
{
	uint8_t nHeader; // 0x00
	uint8_t nSlot;	 // 0x01
	struct {		 // 0x02
		uint16_t nSkill : 12;
		uint16_t nHand : 4;
	};
	uint32_t nItemGUID; // 0x04
};

struct D2GSPacketSrv7C // size of 0x06
{
	uint8_t nHeader;   // 0x00
	uint8_t nUnitType; // 0x01
	int32_t nItemGUID; // 0x02
};

struct D2GSPacketSrv7D // size of 0x12
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t nUnitGUID1; // 0x02
	uint32_t nUnitGUID2; // 0x06
	uint32_t unk0x0A;	 // 0x0A
	uint32_t unk0x0E;	 // 0x0E
};

struct D2GSPacketSrv7E // size of 0x05
{
	uint8_t nHeader;	 // 0x00
	uint8_t unk0x001[4]; // 0x01
};

struct D2GSPacketSrv7F // size of 0x0A
{
	uint8_t nHeader;		  // 0x00
	uint8_t bIsPlayer;		  // 0x01
	uint16_t nLifePercentage; // 0x02
	int32_t nUnitGUID;		  // 0x04
	uint16_t nLevelId;		  // 0x08
};

// struct D2GSPacketSrv80		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

struct D2GSPacketSrv81 // size of 0x14
{
	uint8_t nHeader;  // 0x00
	uint8_t unk0x01;  // 0x01
	uint16_t unk0x02; // 0x02
	uint32_t unk0x04; // 0x04
	uint32_t unk0x08; // 0x08
	uint32_t unk0x0C; // 0x0C
	uint32_t unk0x10; // 0x10
};

struct D2GSPacketSrv82 // size of 0x1D
{
	uint8_t nHeader;		  // 0x00
	uint32_t dwOwnerGUID;	  // 0x01
	char szOwnerName[16];	  // 0x05
	uint32_t dwPortalGUID[2]; // 0x15
};

// struct D2GSPacketSrv83		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv84		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv85		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv86		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv87		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };
//
// struct D2GSPacketSrv88		//size of 0x01
//{
//	uint8_t nHeader;			//0x00
// };

struct D2GSPacketSrv89 // size of 0x02
{
	uint8_t nHeader; // 0x00
	uint8_t nEvent;	 // 0x01
};

struct D2GSPacketSrv8A // size of 0x06
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x05
};

struct D2GSPacketSrv8B // size of 0x06
{
	uint8_t nHeader;   // 0x00
	int32_t nUnitGUID; // 0x01
	uint8_t bParty;	   // 0x05
};

struct D2GSPacketSrv8C // size of 0x0B
{
	uint8_t nHeader;		  // 0x00
	uint32_t dwPlayerGUID[2]; // 0x01
	uint16_t nFlags;		  // 0x09
};

struct D2GSPacketSrv8D // size of 0x07
{
	uint8_t nHeader;	   // 0x00
	uint32_t dwPlayerGUID; // 0x01
	uint16_t nPartyGUID;   // 0x05
};

struct D2GSPacketSrv8E // size of 0x0A
{
	uint8_t nHeader;	   // 0x00
	uint8_t nType;		   // 0x01
	uint32_t dwPlayerGUID; // 0x02
	uint32_t dwCorpseGUID; // 0x06
};

struct D2GSPacketSrv8F // size of 0x21
{
	uint8_t nHeader;	  // 0x00
	uint8_t unk0x001[32]; // 0x01
};

struct D2GSPacketSrv90 // size of 0x0D
{
	uint8_t nHeader; // 0x00
	uint32_t dwGUID; // 0x01
	uint32_t dwPosX; // 0x05
	uint32_t dwPosY; // 0x09
};

struct D2GSPacketSrv91 // size of 0x1A
{
	uint8_t nHeader;		// 0x00
	uint8_t nAct;			// 0x01
	uint16_t pNPCFlags[12]; // 0x02
};

struct D2GSPacketSrv92 // size of 0x06
{
	uint8_t nHeader;	 // 0x00
	uint8_t unk0x001[5]; // 0x01
};

struct D2GSPacketSrv93 // size of 0x08
{
	uint8_t nHeader;	 // 0x00
	uint8_t unk0x001[7]; // 0x01
};

struct D2GSPacketSrv94 // variable size
{
	uint8_t nHeader;	 // 0x00
	uint8_t nSkills;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	struct SkillInfo	 // 0x06
	{
		uint16_t nSkill;
		uint8_t nSkillLevel;
	} Skills[255];
};

struct D2GSPacketSrv95 // size of 0x0D
{
	uint8_t nHeader;	 // 0x00
	uint8_t unk0x01[12]; // 0x01
						 // uint32_t dwLife;			//0x01
						 // uint32_t dwMana;			//0x05
						 // uint32_t dwStamina;		//0x09
						 // uint16_t nPosX;				//0x0D
						 // uint16_t nPosY;				//0x0F
						 // uint16_t unk0x011;				//0x11
};

struct D2GSPacketSrv96 // size of 0x09
{
	uint8_t nHeader;	// 0x00
	uint8_t unk0x01[8]; // 0x01
};

struct D2GSPacketSrv97 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

struct D2GSPacketSrv98 // size of 0x07
{
	uint8_t nHeader;  // 0x00
	uint32_t unk0x01; // 0x01
	uint16_t unk0x05; // 0x05
};

struct D2GSPacketSrv99 // size of 0x10
{
	uint8_t nHeader;   // 0x00
	uint8_t unk0x01;   // 0x01
	uint32_t unk0x02;  // 0x02
	uint16_t unk0x06;  // 0x06
	uint8_t unk0x08;   // 0x08
	uint8_t nUnitType; // 0x09
	int32_t nUnitGUID; // 0x0A
	uint16_t unk0x0E;  // 0x0E
};

// Same as D2GSPacketSrv4D
struct D2GSPacketSrv9A // size of 0x11
{
	uint8_t nHeader;  // 0x00
	uint8_t unk0x01;  // 0x01
	uint32_t unk0x02; // 0x02
	uint32_t unk0x06; // 0x06
	uint8_t unk0x0A;  // 0x0A
	uint16_t nX;	  // 0x0B
	uint16_t nY;	  // 0x0D
	uint16_t unk0x0F; // 0x0F
};

struct D2GSPacketSrv9B // size of 0x07
{
	uint8_t nHeader;  // 0x00
	uint16_t unk0x01; // 0x01
	uint32_t unk0x03; // 0x03
};

struct D2GSPacketSrv9C // variable size
{
	uint8_t nHeader;		 // 0x00
	uint8_t nAction;		 // 0x01
	uint8_t nPacketSize;	 // 0x02
	uint8_t nComponent;		 // 0x03
	int32_t nItemId;		 // 0x04
	uint8_t pBitstream[244]; // 0x08

	// variable data
};

struct D2GSPacketSrv9D // variable size
{
	uint8_t nHeader;		 // 0x00
	uint8_t nAction;		 // 0x01
	uint8_t nPacketSize;	 // 0x02
	uint8_t nComponent;		 // 0x03
	int32_t nItemId;		 // 0x04
	uint8_t nUnitType;		 // 0x08
	int32_t nUnitId;		 // 0x09
	uint8_t pBitstream[244]; // 0x0D

	// variable data
};

// struct D2GSPacketSrv9E	//size of 0x07
//{
//	uint8_t nHeader;		//0x00
//	uint8_t nStat;			//0x01
//	uint32_t dwGUID;		//0x02
//	uint8_t nValue;		//0x06
// };
//
// struct D2GSPacketSrv9F	//size of 0x08
//{
//	uint8_t nHeader;		//0x00
//	uint8_t nStat;			//0x01
//	uint32_t dwGUID;		//0x02
//	uint16_t nValue;		//0x06
// };
//
// struct D2GSPacketSrvA0	//size of 0x0A
//{
//	uint8_t nHeader;		//0x00
//	uint8_t nStat;			//0x01
//	uint32_t dwGUID;		//0x02
//	uint32_t nValue;		//0x06
// };
//
// struct D2GSPacketSrvA1	//size of 0x07
//{
//	uint8_t nHeader;		//0x00
//	uint8_t nStat;			//0x01
//	uint32_t dwGUID;		//0x02
//	uint8_t nValue;		//0x06
// };
//
// struct D2GSPacketSrvA2	//size of 0x08
//{
//	uint8_t nHeader;		//0x00
//	uint8_t nStat;			//0x01
//	uint32_t dwGUID;		//0x02
//	uint16_t nValue;		//0x06
// };

// NOTE(D2MOO): same story as D2GSPacketSrv1D/1E/1F above -- the retail client
// uses FIXED per-header sizes (0x9E=7, 0x9F=8, 0xA0=10, 0xA1=7, 0xA2=8), so
// these five must be distinct structs, not one shared union.
struct D2GSPacketSrv9E // size of 0x07
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint32_t dwGUID;	// 0x02
	uint8_t nValue;		// 0x06
};

struct D2GSPacketSrv9F // size of 0x08
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint32_t dwGUID;	// 0x02
	uint16_t nValue;	// 0x06
};

struct D2GSPacketSrvA0 // size of 0x0A
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint32_t dwGUID;	// 0x02
	uint32_t nValue;	// 0x06
};

struct D2GSPacketSrvA1 // size of 0x07
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint32_t dwGUID;	// 0x02
	uint8_t nValue;		// 0x06
};

struct D2GSPacketSrvA2 // size of 0x08
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint32_t dwGUID;	// 0x02
	uint16_t nValue;	// 0x06
};

struct D2GSPacketSrvStatAndGuid // size of 0x07 (the 8-bit-value form; == D2GSPacketSrv9E)
{
	uint8_t nHeader;	// 0x00
	PacketStatId nStat; // 0x01
	uint32_t dwGUID;	// 0x02
	uint8_t nValue;		// 0x06
};

struct D2GSPacketSrvA3 // size of 0x18
{
	uint8_t nHeader;  // 0x00
	uint8_t unk0x01;  // 0x01
	uint16_t unk0x02; // 0x02
	uint16_t unk0x04; // 0x04
	uint8_t unk0x06;  // 0x06
	uint32_t unk0x07; // 0x07
	uint8_t unk0x0B;  // 0x0B
	uint32_t unk0x0C; // 0x0C
	uint32_t unk0x10; // 0x10
	uint32_t unk0x14; // 0x14
};

struct D2GSPacketSrvA4 // size of 0x03
{
	uint8_t nHeader;  // 0x00
	uint16_t unk0x01; // 0x01
};

struct D2GSPacketSrvA5 // size of 0x08
{
	uint8_t nHeader;  // 0x00
	uint8_t unk0x01;  // 0x01
	int32_t unk0x02;  // 0x02
	uint16_t unk0x06; // 0x06
};

struct D2GSPacketSrvA6 // variable size
{
	uint8_t nHeader; // 0x00

	// variable data
};

// NOTE(D2MOO): the retail client reads 0xA7 as a FIXED 7 bytes and 0xA8 as
// `nSize` bytes where nSize lives at offset 6.  With nState widened to 16 bits
// the payload moved one byte forward, so every 0xA7/0xA9 drifted the client's
// packet cursor and every 0xA8 carried its bitstream one byte off.  nState is a
// single byte on the wire; the state ids that exceed 0xFF simply truncate,
// exactly as retail D2GS does.
struct D2GSPacketSrvA7 // size of 0x07
{
	uint8_t nHeader;   // 0x00
	uint8_t nUnitType; // 0x01
	int32_t nUnitId;   // 0x02
	uint8_t nState;	   // 0x06
};

struct D2GSPacketSrvA8 // Variable Size: nSize == total packet size, at 0x06
{
	uint8_t nHeader;	  // 0x00
	uint8_t nUnitType;	  // 0x01
	int32_t nUnitId;	  // 0x02
	uint8_t nSize;		  // 0x06 - client sizes the whole packet from this byte
	uint8_t nState;		  // 0x07
	uint8_t pStream[512]; // 0x08
};

// struct D2GSPacketSrvA7	//size of 0x07
//{
//	uint8_t nHeader;		//0x00
//	uint8_t nUnitType;		//0x01
//	int32_t nUnitId;		//0x02
//	uint8_t nState;		//0x06
// };
//
// struct D2GSPacketSrvA8	//Variable Size
//{
//	uint8_t nHeader;			//0x00
//	uint8_t nUnitType;			//0x01
//	int32_t nUnitId;			//0x02
//	uint8_t nSize;				//0x06
//	uint8_t nState;			//0x07
//	uint8_t pStream[512];		//0x08
// };
//
// struct D2GSPacketSrvA9	//size of 0x07
//{
//	uint8_t nHeader;		//0x00
//	uint8_t nUnitType;		//0x01
//	int32_t nUnitId;		//0x02
//	uint8_t nState;		//0x06
// };

struct D2GSPacketSrvA9 // size of 0x07
{
	uint8_t nHeader;   // 0x00
	uint8_t nUnitType; // 0x01
	int32_t nUnitId;   // 0x02
	uint8_t nState;	   // 0x06
};

struct D2GSPacketSrvAA // variable size
{
	uint8_t nHeader;	  // 0x00
	uint8_t nUnitType;	  // 0x01
	int32_t nUnitId;	  // 0x02
	uint8_t nSize;		  // 0x06
	uint8_t pStream[512]; // 0x07
};

struct D2GSPacketSrvAB // size of 0x07
{
	uint8_t nHeader;	 // 0x00
	uint8_t nUnitType;	 // 0x01
	uint32_t dwUnitGUID; // 0x02
	uint8_t nLife;		 // 0x06
};

struct D2GSPacketSrvAC // variable size
{
	uint8_t nHeader;		// 0x00
	uint32_t dwUnitGUID;	// 0x01
	uint16_t nUnitIndex;	// 0x05
	uint16_t nPosX;			// 0x07
	uint16_t nPosY;			// 0x09
	uint8_t nLifePct;		// 0x0B
	uint8_t nPacketLength;	// 0x0C
	uint8_t bitstream[244]; // 0x0D
							// variable data bitstream
};

struct D2GSPacketSrvAD // size of 0x09
{
	uint8_t nHeader; // 0x00
	int32_t unk0x01; // 0x01
	int32_t unk0x05; // 0x05
};

struct D2GSPacketSrvAE // variable size
{
	uint8_t nHeader; // 0x00

	// variable data
};

// The 1.10f decomp records 0x01, but a 1-byte 0xAF permanently wedges the
// retail client's receive path.  0xAF is a *variable* entry in the client's
// size table (Game.exe 0x730AE8) and the size routine's case 0xAF (0x52BADD)
// needs >= 2 bytes, resolving to BYTE@1 ? BYTE@1 + 1 : 2.  Given a 1-byte 0xAF
// it returns failure, and the frame walker (0x52A8D0) then exits its loop
// before consuming anything and leaves the byte at the head of the receive
// buffer -- so the client can never advance past it again, and every packet
// appended behind it (the rest of the release burst, the game list, everything)
// is silently dropped.
//
// BYTE@1 is a sub-type, not payload: 0x81 carries a 128-byte nibble-encoded
// blob (0x52A8D0); 0 is the plain "server is tearing this client down" form
// used by GAME_EndGame / GAME_DisconnectClient / SERVER_Release.
struct D2GSPacketSrvAF // size of 0x02
{
	uint8_t nHeader;  // 0x00
	uint8_t nSubType; // 0x01
};

struct D2GSPacketSrvB0 // size of 0x01
{
	uint8_t nHeader; // 0x00
};

// NOTE(D2MOO): 0xB1 is one of the headers the client CANNOT size (table entry
// 0, Game.exe 0x730AE8), so it must never appear on the wire.  The block that
// used to sit here was off by one against that table: the 53-byte game-list
// entry belongs to 0xB2, and the 5-byte error code to 0xB4 (0xB3 is variable,
// sized as BYTE@1 + 7).  Naming them by their real ids keeps the senders in
// SCmd.cpp from re-introducing the shift.
struct D2GSPacketSrvB1; // never sent: the client cannot size it

struct D2GSPacketSrvB2 // size of 0x35 (0x35 == 53 in the client table)
{
	uint8_t nHeader;	   // 0x00
	char szGameName[48];   // 0x01
	uint16_t nClientCount; // 0x31
	uint16_t nGameId;	   // 0x33
};

struct D2GSPacketSrvB3 // variable size: BYTE@1 + 7
{
	uint8_t nHeader; // 0x00

	// variable data
};

struct D2GSPacketSrvB4 // size of 0x05
{
	uint8_t nHeader; // 0x00
	uint32_t dwType; // 0x01
};

struct D2GameServerInfoStrc {
	int32_t field_0x0;
	int32_t field_0x4;
	int32_t field_0x8;
	int32_t field_0xc;
	int32_t field_0x10;
	int32_t field_0x14;
	int32_t field_0x18;
	int32_t field_0x1c;
	int32_t field_0x20;
	int32_t field_0x24;
	char szCompilationData[128];
	int32_t field_0xa8;
	int32_t field_0xac;
	int32_t field_0xb0;
	int32_t field_0xb4;
	int32_t field_0xb8;
};

struct D2GameServerInfoExStrc : D2GameServerInfoStrc {
	uint32_t dwords0xBC[6];
	uint16_t word0xD4;
	char szUnk0xD6[20];
	uint16_t word0xEA;
	uint32_t dwords0xD8;
	uint32_t dwords0xF0[8];
	uint32_t dwords0x110;
};

struct D2GSPacketSrvFFFD {
	uint8_t nPacketSubType;			  // 0x00
	D2GameServerInfoStrc tServerInfo; // 0x01
};

struct D2GSPacketSrvFF01 {
	uint8_t nPacketSubType;			  // 0x00
	D2GameServerInfoStrc tServerInfo; // 0x01
	int32_t field_0xbd;
	int32_t aSomeInts[8];
	int32_t field_0xe1;
	int32_t field_0xe5;
	int32_t field_0xe9;
	int32_t field_0xed;
	int32_t field_0xf1;
	int16_t field_0xf5;
	char field_0xf6[20];
	int32_t field_0x10b;
	int32_t field_0x10f;
	int32_t field_0x113;
	int32_t field_0x117;
	char nZeroed[74];
};

// Save-and-exit: the server streams the finished character save back to the
// client in <=255-byte parts; the client reassembles them (Game.exe
// FUN_0045c620, reached only from the `case 0xb3:` arm of the >0xAE S->C
// dispatcher FUN_0045c850) and is the ONLY thing that ever writes the .d2s
// (FUN_0045c520: fopen("<saveDir><charName>.d2s","wb") + fwrite).  Get this id
// wrong and the client neither saves nor complains.
//
// The 1.10f decomp says 0xB2; 1.14d shifted the tail of the range by one
// (0xB1 unused, 0xB2 = the fixed 53-byte game-list entry D2GSPacketSrvB2,
// 0xB3 = variable).  D2NetPacketSize.h's client table agrees: 0xB3 is
// "BYTE@1 + 7", i.e. exactly this 7-byte header plus nPartDataSize bytes.
struct ClientPacketSaveHeaderPart // sizeof(0x107) nHeaderID: 0xB3 (1.10f: 0xB2)
{
	uint8_t nHeaderId;		  // 0x00
	uint8_t nPartDataSize;	  // 0x01
	uint8_t bFirstPart;		  // 0x02
	uint32_t nSaveHeaderSize; // 0x03
	uint8_t aData[256];		  // 0x07
};

#define D2GS_HDR_SAVEHEADERPART 0xB3 // ClientPacketSaveHeaderPart::nHeaderId

#pragma pack()

// ---------------------------------------------------------------------
// Wire-size guards (see D2NetPacketSize.h for the full derivation)
// ---------------------------------------------------------------------
// Every S->C packet struct above is copied to the wire verbatim, and the retail
// client splits the incoming payload using a fixed table of its own.  A struct
// whose sizeof disagrees with that table shifts the client's cursor and the
// remainder of the frame is re-interpreted as arbitrary packets -- which is how
// 0x1D/0x1E/0x1F (three genuinely different sizes sharing one union) ended up
// making the client read a stat update as a 0x09 "create unit" and assert
// "Unable to find room for unit".  These assertions make that class of bug a
// compile error rather than a runtime crash.
//
// Only the fixed-size headers the engine actually emits are listed.  A handful
// of structs further down are still declared-but-undefined and are checked in
// D2NetPacketSize.h's own table; the 0xB1..0xB4 block is variable-size in the
// client and therefore has no fixed number to check against.
#include <D2NetPacketSize.h>
#include <cstddef>

// Fixed-size S->C structs whose sizeof must equal the client table entry.
#define D2GS_ASSERT_WIRE_SIZE(Struct, Header)                            \
	static_assert(sizeof(Struct) == D2NET_ServerPacketSizeTable[Header], \
				  #Struct " must be " #Header " bytes on the wire (retail client size table)")

#if PACKETS_USE_16BITS_STATID
// 0x1D/0x1E/0x1F only keep their retail sizes with an 8-bit stat id; the 16-bit
// build is a deliberate opt-in and is not wire-compatible.
#else
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrv1D, 0x1D);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrv1E, 0x1E);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrv1F, 0x1F);
#endif
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrv54, 0x54);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrv9E, 0x9E);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrv9F, 0x9F);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvA0, 0xA0);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvA1, 0xA1);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvA2, 0xA2);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvA3, 0xA3);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvA4, 0xA4);

// 0xAF is variable-size (table entry -1) so it cannot use
// D2GS_ASSERT_WIRE_SIZE, but the client still refuses to size it below 2 bytes
// and a short one wedges the receive buffer permanently -- see the struct.
static_assert(sizeof(D2GSPacketSrvAF) >= 2,
			  "D2GSPacketSrvAF must be at least 2 bytes (retail client sizes 0xAF as BYTE@1 ? BYTE@1 + 1 : 2)");
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvA5, 0xA5);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvA7, 0xA7);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvA9, 0xA9);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvB0, 0xB0);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvB2, 0xB2);
D2GS_ASSERT_WIRE_SIZE(D2GSPacketSrvB4, 0xB4);
// The save-header stream (ClientPacketSaveHeaderPart) is the one S->C packet
// whose *id* matters as much as its size: the client's >0xAE dispatcher
// FUN_0045c850 switches on 0xaf/0xb0/0xb3/0xb4 only, and its 0xB3 arm is the
// handler that reassembles the save and writes the .d2s (FUN_0045c620 ->
// FUN_0045c520).  Emit it under 0xB2 instead and the client's switch has no
// arm for it at all: the save is silently dropped and the character never
// persists.  Nothing below can see the dispatch table, so pin what we can --
// 0xB3 must be the variable-size entry the client's "BYTE@1 + 7" rule
// resolves, and 0xB2 must stay the fixed 53-byte game-list entry.
static_assert(D2NET_ServerPacketSizeTable[D2GS_HDR_SAVEHEADERPART] < 0,
			  "the save-header stream must live on a variable-size client id (0xB3)");
static_assert(D2NET_ServerPacketSizeTable[0xB2] == 53,
			  "0xB2 is the fixed-size game-list entry, not the save-header stream");
// 0xA8/0xAA carry their own length byte; assert the fixed prefix the client
// uses to locate the bitstream.
static_assert(offsetof(D2GSPacketSrvA8, nSize) == 6 && offsetof(D2GSPacketSrvA8, pStream) == 8,
			  "0xA8: client reads the total size at 0x06 and the bitstream at 0x08");
static_assert(offsetof(D2GSPacketSrvAA, pStream) == 7,
			  "0xAA: client reads the bitstream at 0x07");
#undef D2GS_ASSERT_WIRE_SIZE
