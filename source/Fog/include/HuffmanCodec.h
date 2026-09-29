// D2GS Huffman codec (custom D2 format)
// ------------------------------------------------------------
// The Diablo II D2GS/D2Net wire protocol uses a proprietary
// fixed-table Huffman codec after compression is negotiated via the
// 0xAF greeting.  This implementation is a clean-room port of the
// tables/algorithm present in MephisTools/diablo2-protocol
// (lib/utils/compression.js), which was itself derived from the
// retail binaries.
//
// Verified byte-exact against real captured D2GS 1.13/1.14 S->C
// traffic: for every frame of a 164-frame capture,
//   compress(decompress(frame)) == frame
// and the decompressor reproduces the same packets as the reference
// implementation (PONG `8f`+32 zero bytes <=> `1f7fffffffc0`, etc.).
//
// Framing rules (frame header, MSB "size" form):
//   payloadSize+1 < 0xF0     -> 1-byte header: [size][payload]
//   payloadSize+1 >= 0xF0    -> 2-byte header: [0xF0|(total>>8)][total&0xFF][payload]
// where total = payloadSize + headerSize.
#pragma once

#include <cstdint>

namespace d2gs {

// Parse the frame header at buf[0..1]; returns the payload size in bytes
// and stores the header size (1 or 2) in *headerSizeOut.
int Huffman_GetPacketSize(const uint8_t* buf, int* headerSizeOut);

// Compress src (srcLen bytes) into dst (dstCap bytes).
// Returns bytes written, or -1 if dstCap is too small.
int Huffman_Compress(const uint8_t* src, int srcLen, uint8_t* dst, int dstCap);

// Decompress src (srcLen bytes) into dst (dstCap bytes).
// Returns bytes written, or -1 on error / output too small.
int Huffman_Decompress(const uint8_t* src, int srcLen, uint8_t* dst, int dstCap);

// Build a complete framed packet: writes the 1- or 2-byte frame header
// followed by payload into frame (frameCap bytes), so the result can be
// written straight to the socket.  Returns total bytes written, or -1.
int Huffman_WriteFrame(uint8_t* frame, int frameCap, const uint8_t* payload, int payloadLen);

} // namespace d2gs