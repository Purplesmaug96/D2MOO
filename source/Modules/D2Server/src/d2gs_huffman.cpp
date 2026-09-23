// D2GS Huffman codec implementation (see d2gs_huffman.h for details).
#include "d2gs_huffman.h"
#include "d2gs_huffman_tables.h"

namespace d2gs {

int Huffman_GetPacketSize(const uint8_t* buf, int* headerSizeOut) {
    if (buf[0] < 0xF0) {
        *headerSizeOut = 1;
        return (int)buf[0] - 1;
    }
    *headerSizeOut = 2;
    return (int)(((buf[0] & 0x0F) << 8) + buf[1]) - 2;
}

int Huffman_Compress(const uint8_t* src, int srcLen, uint8_t* dst, int dstCap) {
    uint32_t buffer = 0;   // bit accumulator, MSB-first
    int bitCount = 0;      // valid bits in buffer (<= 7 between symbols)
    int out = 0;

    for (int x = 0; x < srcLen; x++) {
        const uint32_t a = kCompressionTable[src[x]];
        const int mainLen = (int)((a >> 16) & 0xFF); // main code length (usually 8)
        const int extraLen  = (int)((a >> 8) & 0xFF); // secondary code length (0 or <= 8)

        // Main 8-bit code field goes just below the valid bits.
        buffer |= (a >> 24) << (24 - bitCount);
        bitCount += mainLen;

        if (extraLen != 0) {
            buffer |= ((a & 0xFF) << (8 - extraLen)) << (24 - bitCount);
            bitCount += extraLen;
        }

        // Emit complete bytes; keep at most 7 bits buffered so the next
        // (24 - bitCount) shift is always non-negative.
        while (bitCount >= 8) {
            if (out >= dstCap) {
                return -1;
            }
            dst[out++] = (uint8_t)(buffer >> 24);
            buffer <<= 8;
            bitCount -= 8;
        }
    }

    // Flush the final partial byte, zero-padded (matches the reference
    // compressor: trailing bits are ignored by the decompressor's
    // end-of-stream check).
    if (bitCount > 0) {
        if (out >= dstCap) {
            return -1;
        }
        dst[out++] = (uint8_t)(buffer >> 24);
    }
    return out;
}

int Huffman_Decompress(const uint8_t* src, int srcLen, uint8_t* dst, int dstCap) {
    int remaining = srcLen;
    int in = 0;
    int out = 0;
    uint32_t b = 0;         // bit window (4 bytes loaded, MSB-first)
    int bitCount = 32;      // bits remaining before the window is exhausted

    for (;;) {
        // Refill the 32-bit window.
        if (bitCount >= 8) {
            while (remaining > 0 && bitCount >= 8) {
                bitCount -= 8;
                remaining--;
                b |= ((uint32_t)src[in++]) << bitCount;
            }
        }

        // Decode one symbol through the fast tables.
        const uint32_t index = kIndexTable[b >> 24];
        const uint32_t a = kCharacterTable[index];
        const uint32_t d = (b >> (24 - a)) & kBitMasks[a];
        const uint32_t c = kCharacterTable[index + 2 * d + 2];

        bitCount += (int)c;
        if (bitCount > 32) {
            // End of stream: all real bits consumed.
            return out;
        }
        if (out >= dstCap) {
            return -1;
        }
        dst[out++] = (uint8_t)kCharacterTable[index + 2 * d + 1];
        b <<= c;
    }
}

int Huffman_WriteFrame(uint8_t* frame, int frameCap, const uint8_t* payload, int payloadLen) {
    const int total = payloadLen + 1 + (payloadLen + 1 >= 0xF0 ? 1 : 0);
    if (total > frameCap) {
        return -1;
    }
    int headerSize;
    if (payloadLen + 1 < 0xF0) {
        frame[0] = (uint8_t)(payloadLen + 1);
        headerSize = 1;
    } else {
        frame[0] = (uint8_t)(0xF0 | ((total >> 8) & 0x0F));
        frame[1] = (uint8_t)(total & 0xFF);
        headerSize = 2;
    }
    if (payloadLen > 0) {
        for (int i = 0; i < payloadLen; i++) {
            frame[headerSize + i] = payload[i];
        }
    }
    return headerSize + payloadLen;
}

} // namespace d2gs