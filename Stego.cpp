/*
	Implementation of Stego functions used to extract LSB encoded bitmaps
*/

#include "Stego.h"

// General formula to decode into raw data returned as void * (called from GetLSBHeader and GetLSBPayload)
void * DecodeLSB(unsigned char * pBuffer, DWORD dwBufferLength, DWORD dwOffset, DWORD dwPayloadSize)
{
	if (dwBufferLength < (dwOffset + ENCODED_LENGTH(dwPayloadSize)))
	{
		return NULL; // Requesting too large of a payload from the pBuffer
	}

	// Allocate room for our payload (we will only be getting exactly this much out of the pBuffer)
	unsigned char * pData = (unsigned char *)malloc(dwPayloadSize);

	unsigned int index = 0;
	for (unsigned int i = dwOffset; i < dwBufferLength && (index / 8) < dwPayloadSize; i++, index++)
	{
		pData[index / 8] |= (LSB(pBuffer[i]) << (index % 8));
	}

	return (void *)pData;
}

LSBHeader * GetLSBHeader(unsigned char * buffer, DWORD dwBufferLength, DWORD dwHeaderOffset)
{
	return (LSBHeader *)DecodeLSB(buffer, dwBufferLength, dwHeaderOffset, sizeof(LSBHeader));
}

void * GetLSBPayload(unsigned char * buffer, DWORD dwBufferLength, DWORD dwPayloadLength, DWORD dwPayloadOffset)
{
	return DecodeLSB(buffer, dwBufferLength, dwPayloadOffset, dwPayloadLength);
}