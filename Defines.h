/*
All macros and type definitions required for Windows types
*/

#ifndef _DEFINES_H_
	#define _DEFINES_H_

#define WIN32_LEAN_AND_MEAN
#include <Pdh.h>

#ifndef SW_HIDE
	#define SW_HIDE					0x0
#endif

#ifndef MEM_COMMIT
	#define MEM_COMMIT				0x1000
#endif

#ifndef MEM_RELEASE
	#define MEM_RELEASE				0x4000
#endif

#ifndef PAGE_EXECUTE_READWRITE
	#define PAGE_EXECUTE_READWRITE	0x40
#endif

#define INTERNET_OPEN_TYPE_PRECONFIG	0			// use registry configuration
#define INTERNET_OPEN_TYPE_DIRECT		0x1
#define INTERNET_FLAG_ASYNC				0x10000000  // this request is asynchronous (where supported)

#define INTERNET_FLAG_NO_CACHE_WRITE    0x04000000  // don't write this item to the cache
#define INTERNET_FLAG_NO_AUTH           0x00040000  // no automatic authentication handling
#define INTERNET_FLAG_RESYNCHRONIZE     0x00000800  // asking wininet to update an item if it is newer
#define INTERNET_FLAG_HYPERLINK         0x00000400  // asking wininet to do hyperlinking semantic which works right for scripts
#define INTERNET_FLAG_NO_UI             0x00000200  // no cookie popup
#define INTERNET_FLAG_PRAGMA_NOCACHE    0x00000100  // asking wininet to add "pragma: no-cache"
#define INTERNET_FLAG_CACHE_ASYNC       0x00000080  // ok to perform lazy cache-write
#define INTERNET_FLAG_FORMS_SUBMIT      0x00000040  // this is a forms submit
#define INTERNET_FLAG_FWD_BACK          0x00000020  // fwd-back button op
#define INTERNET_FLAG_NEED_FILE         0x00000010  // need a file for this request
#define INTERNET_FLAG_MUST_CACHE_REQUEST INTERNET_FLAG_NEED_FILE

#define HEAP_ZERO_MEMORY				0x00000008

#define WINAPI __stdcall

#define TRUE 1
#define FALSE 0

#define NANO_TO_SECOND 100000000

typedef void* LPVOID;

typedef void *PVOID;
typedef PVOID HANDLE;
typedef HANDLE HINTERNET;

typedef unsigned long DWORD;

typedef unsigned long __w64 ULONGPTR;
typedef ULONGPTR SIZE_T;

typedef int BOOL;

/* This requires linking kernel32.lib at runtime (only for these functions though) */
#define malloc(bytes) \
	( HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, bytes) )
#define free(ptr) \
	if (ptr)( HeapFree(GetProcessHeap(), 0, ptr) )

#endif