#pragma once

// S->C packet sizing, verbatim from the retail client
// ---------------------------------------------------------------------
// The retail client splits an incoming S->C payload into packets using a table
// of its own.  In Game.exe the size routine at 0x52B920 does
// `mov 0x730ae8(,%edx,4),%eax` (0xB5 four-byte entries at VA 0x730AE8) and, for
// a negative entry, resolves the size through the jump table at 0x52BB44 indexed
// by the byte table at 0x52BB80.  Entry semantics:
//
//   > 0  fixed size in bytes
//     0  a header the client CANNOT size.  0x52B94C returns failure and the
//        client's frame walker (0x45F809) silently abandons the REST of the
//        frame -- the engine must never emit one of these.
//    < 0  variable size, resolved by the switch below
//
// This table lives in a header rather than in D2Net/src/Server.cpp because the
// libFog transport shim has to walk engine frames with the *same* numbers, and
// libFog does not link against libD2Net.  There is exactly one copy, so the two
// walkers cannot drift apart.
//
// Why it has to be exact: the client also compares each computed size against a
// second, independent copy of the numbers in its handler table (0x7114D0, stride
// 12) and asserts "unexpected packet size" (0x45F93D) on a mismatch, and asserts
// "unhandled packet" (0x45F91E) for any header >= 0xAF.  Since the engine only
// ever *appends* packets into a frame, one header whose sizeof(struct) disagrees
// with this table shifts the client's cursor permanently and the remainder of the
// frame is re-interpreted as arbitrary packets.  That is how a stat update ended
// up being read as a 0x09 "create unit" and made the client assert
// "Unable to find room for unit".

#include <cstddef>
#include <cstdint>
#include <iterator>

// Client table, Game.exe VA 0x730AE8, entries 0x00..0xB4.
inline constexpr int32_t D2NET_ServerPacketSizeTable[] = {
	1, 8, 1, 12, 1, 1, 1, 6,		// 0x00
	6, 11, 6, 6, 9, 13, 12, 16,	// 0x08
	16, 8, 26, 14, 18, 11, -1, 0,	// 0x10
	15, 2, 2, 3, 5, 3, 4, 6,		// 0x18
	10, 12, 12, 13, 90, 90, -1, 40,	// 0x20
	103, 97, 15, 0, 8, 0, 0, 0,	// 0x28
	0, 0, 0, 0, 0, 0, 0, 0,		// 0x30
	0, 0, 0, 0, 0, 0, -1, 8,		// 0x38
	13, 0, 6, 0, 0, 13, 0, 11,		// 0x40
	11, 0, 0, 0, 16, 17, 7, 1,		// 0x48
	15, 14, 42, 10, 3, 0, 0, 14,	// 0x50
	7, 26, 40, -1, 5, 6, 38, 5,		// 0x58
	7, 2, 7, 21, 0, 7, 7, 16,		// 0x60
	21, 12, 12, 16, 16, 10, 1, 1,	// 0x68
	1, 1, 1, 32, 10, 13, 6, 2,		// 0x70
	21, 6, 13, 8, 6, 18, 5, 10,		// 0x78
	0, 20, 29, 0, 0, 0, 0, 0,		// 0x80
	0, 2, 6, 6, 11, 7, 10, 33,		// 0x88
	13, 26, 6, 8, -1, 13, 9, 1,		// 0x90
	7, 16, 17, 7, -1, -1, 7, 8,		// 0x98
	10, 7, 8, 24, 3, 8, -1, 7,		// 0xA0
	-1, 7, -1, 7, -1, 0, -1, -1,	// 0xA8
	1, 0, 53, -1, 5					// 0xB0
};

static_assert(std::size(D2NET_ServerPacketSizeTable) == 0xB5, "table must cover headers 0x00..0xB4");

// Size of the S->C packet at pData, exactly as the retail client computes it.
// Returns the size, or 0 on failure (unsizable header, header >= 0xB5, or a
// variable packet whose declared length does not fit in nBufferSize) with
// *pSize set to 0.
inline int32_t __fastcall D2NET_GetServerPacketSizeFromBuffer(const uint8_t* pData, uint32_t nBufferSize, int32_t* pSize) {
	if (nBufferSize == 0) {
		return 0;
	}

	const uint8_t nHeader = pData[0];
	if (nHeader >= std::size(D2NET_ServerPacketSizeTable)) {
		return 0;
	}

	*pSize = D2NET_ServerPacketSizeTable[nHeader];
	if (*pSize >= 0) {
		return *pSize;
	}

	// Variable-size headers, in the client's jump-table order.
	switch (nHeader) {
	case 0x16u: { // 0x52B977: needs 0x0D, size = WORD@1
		if (nBufferSize < 0x0Du) {
			return 0;
		}
		*pSize = *(const uint16_t*)&pData[1];
		return *pSize;
	}
	case 0x26u: { // 0x52B98E: needs 0x0A, two NUL-terminated strings
		if (nBufferSize < 10u) {
			return 0;
		}
		auto nStrLen = [](const char* s) {
			int32_t nLen = 0;
			while (s[nLen]) {
				nLen++;
			}
			return nLen;
		};
		const char* pStr = (const char*)&pData[10];
		const int32_t nFirstLen = nStrLen(pStr);
		const int32_t nFirst = nFirstLen + 11; // 10 fixed bytes + string + NUL
		if (nBufferSize < (uint32_t)nFirst) {
			return 0;
		}
		*pSize = nFirst + nStrLen(&pStr[nFirstLen + 1]) + 1;
		if (nBufferSize < (uint32_t)*pSize) {
			return 0;
		}
		return *pSize;
	}
	case 0x3Eu: { // 0x52BA1A: needs 2, size = BYTE@1
		if (nBufferSize < 2u) {
			return 0;
		}
		*pSize = pData[1];
		return *pSize;
	}
	case 0x5Bu: { // 0x52B9CF: needs 0x22, size = WORD@1
		if (nBufferSize < 0x22u) {
			return 0;
		}
		*pSize = *(const uint16_t*)&pData[1];
		return *pSize;
	}
	case 0x94u: { // 0x52B9E6: needs 9, size = 3 * (BYTE@1 + 2)
		if (nBufferSize < 9u) {
			return 0;
		}
		*pSize = 3 * (pData[1] + 2);
		return *pSize;
	}
	case 0x9Cu: // 0x52BA03 / 0x52BA31: needs 3, size = BYTE@2
	case 0x9Du: {
		if (nBufferSize < 3u) {
			return 0;
		}
		*pSize = pData[2];
		return *pSize;
	}
	case 0xA6u: { // 0x52BA48: needs 4, size = WORD@2
		if (nBufferSize < 4u) {
			return 0;
		}
		*pSize = *(const uint16_t*)&pData[2];
		return *pSize;
	}
	case 0xA8u: // 0x52BA63: needs 7, size = BYTE@6 (the WHOLE packet size)
	case 0xAAu: { // 0x52BA7E: needs 7, size = BYTE@6
		if (nBufferSize < 7u) {
			return 0;
		}
		*pSize = pData[6];
		return *pSize;
	}
	case 0xACu: { // 0x52BA99: needs 0x0D, size = BYTE@0x0C
		if (nBufferSize < 0x0Du) {
			return 0;
		}
		*pSize = pData[12];
		return *pSize;
	}
	case 0xAEu: { // 0x52BAB4: needs 3, size = min(WORD@1, 0x1FD) + 3
		if (nBufferSize < 3u) {
			return 0;
		}
		uint16_t nValue = *(const uint16_t*)&pData[1];
		if (nValue > 0x1FDu) {
			nValue = 0; // the client zeroes anything it considers too large
		}
		*pSize = (int32_t)nValue + 3;
		return *pSize;
	}
	case 0xAFu: { // 0x52BADD: needs 2, size = BYTE@1 ? BYTE@1 + 1 : 2
		if (nBufferSize < 2u) {
			return 0;
		}
		*pSize = pData[1] ? (int32_t)pData[1] + 1 : 2;
		return *pSize;
	}
	case 0xB3u: { // 0x52BB13: needs 8, size = BYTE@1 + 7
		if (nBufferSize < 8u) {
			return 0;
		}
		*pSize = (int32_t)pData[1] + 7;
		return *pSize;
	}
	default: { // a -1 entry with no case above: unsizable
		*pSize = 0;
		return 0;
	}
	}
}
