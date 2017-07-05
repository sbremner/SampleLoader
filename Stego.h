/*
	This is the header file for code pertaining to stegonography.

	It will be used to extract LSB encoded bitmaps.
*/

#ifndef _STEGO_H_
	#define _STEGO_H_

#include "Defines.h"

#define BITMAP_HEADER_LENGTH 54	// 54 Byte header size for bitmaps (we skip bytes 0-53 while decoding)

#define LSB_HEADER_OFFSET BITMAP_HEADER_LENGTH

#pragma pack(push, 4)
typedef struct LSBHeader{
	DWORD PayloadSize;	// Length of the payload (useful for VirtualAlloc/memcpy)
	DWORD PayloadType;	// Reserved DWORD for future works
} LSBHeader;
#pragma pack(pop)

#define LSB_HEADER_LENGTH ( sizeof(LSBHeader) * 8 )	// Takes 8 bytes of bitmap for 1 byte of information

#define LSB_PAYLOAD_OFFSET (LSB_HEADER_OFFSET + LSB_HEADER_LENGTH)

#define ENCODED_LENGTH(d_length) ( d_length * 8 )
#define DECODED_LENGTH(e_length) ( e_length / 8 )

#define LSB(byte) ( byte & 0x1 )

LSBHeader * GetLSBHeader(unsigned char * buffer, DWORD dwBufferLength, DWORD dwHeaderOffset);
void * GetLSBPayload(unsigned char * buffer, DWORD dwBufferLength, DWORD dwPayloadLength, DWORD dwPayloadOffset);

#endif