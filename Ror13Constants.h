/*
Pre - processor declarations for ROR 13 constants

Format: #define <LIB>_<FUNC> 0x<ror13 hash>
*/

#ifndef _ROR13_CONSTANTS_H_
	#define _ROR13_CONSTANTS_H_

/*// ***** Kernel32.dll (7 functions) ***** //
#define KERNEL32_DLL_STR                { 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', '\0' }
#define KERNEL32_DLL                            0x8FECD63F // Lowercase kernel32.dll (it is case sensitive)
#define KERNEL32_DLL_HeapAlloc                  0x2500383C
#define KERNEL32_DLL_HeapFree                   0x10C32616
#define KERNEL32_DLL_GetProcessHeap             0xA80EECAE
#define KERNEL32_DLL_LoadLibraryA               0xEC0E4E8E
#define KERNEL32_DLL_FreeLibrary                0x4DC9D5A0
#define KERNEL32_DLL_GetProcAddress             0x7C0DFCAA
#define KERNEL32_DLL_CloseHandle                0xFFD97FB
#define KERNEL32_DLL_IsWow64Process             0xE610CFB8
#define KERNEL32_DLL_VirtualAlloc               0x91AFCA54
#define KERNEL32_DLL_VirtualFree                0x30633AC
#define KERNEL32_DLL_GetConsoleWindow           0x6AF5E778

// ***** Advapi32.dll (2 functions) ***** //
#define ADVAPI32_DLL_STR                { 'A', 'd', 'v', 'a', 'p', 'i', '3', '2', '.', 'd', 'l', 'l', '\0' }
#define ADVAPI32_DLL                            0x428CF79F
#define ADVAPI32_DLL_AdjustTokenPrivileges      0x24488A0F
#define ADVAPI32_DLL_OpenProcessToken           0x591EA70F

// ***** User32.dll (1 functions) ***** //
#define USER32_DLL_STR          { 'U', 's', 'e', 'r', '3', '2', '.', 'd', 'l', 'l', '\0' }
#define USER32_DLL                              0x542DEE26
#define USER32_DLL_ShowWindow					0xC95D4F83

// ***** Wininet.dll (4 functions) ***** //
#define WININET_DLL_STR         { 'W', 'i', 'n', 'i', 'n', 'e', 't', '.', 'd', 'l', 'l', '\0' }
#define WININET_DLL                             0xF22AED5
#define WININET_DLL_InternetOpenA               0x57E84429
#define WININET_DLL_InternetOpenUrlA            0x7E0FED49
#define WININET_DLL_InternetQueryDataAvailable  0xB960F869
#define WININET_DLL_InternetReadFile            0x5FE34B8B
#define WININET_DLL_InternetCloseHandle         0xFA9B69C7
*/

// ***** kernel32.dll (11 functions) ***** //
#define KERNEL32_DLL_STR                { 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', '\0' }
#define KERNEL32_DLL                            0x8FECD63F
#define KERNEL32_DLL_HeapAlloc                  0x4502383C
#define KERNEL32_DLL_HeapFree                   0x50C32A16
#define KERNEL32_DLL_GetProcessHeap             0xF80EECB6
#define KERNEL32_DLL_FreeLibrary                0x4E49D5A8
#define KERNEL32_DLL_LoadLibraryA               0xEC4E52AE
#define KERNEL32_DLL_GetProcAddress             0x8C8DFCB2
#define KERNEL32_DLL_CloseGandle                0xFFD9813
#define KERNEL32_DLL_IsWow64Process             0xF6D0CFB8
#define KERNEL32_DLL_VirtualAlloc               0x91F1CA54
#define KERNEL32_DLL_VirtualFree                0x430633B4
#define KERNEL32_DLL_GetConsoleWindow           0x6AF5E98C

// ***** advapi32.dll (2 functions) ***** //
#define ADVAPI32_DLL_STR                { 'a', 'd', 'v', 'a', 'p', 'i', '3', '2', '.', 'd', 'l', 'l', '\0' }
#define ADVAPI32_DLL                            0x42CCF79F
#define ADVAPI32_DLL_AdjustTokenPrivileges      0x244A0A11
#define ADVAPI32_DLL_OpenProcessToken           0x5960A713

// ***** user32.dll (1 functions) ***** //
#define USER32_DLL_STR          { 'u', 's', 'e', 'r', '3', '2', '.', 'd', 'l', 'l', '\0' }
#define USER32_DLL                              0x542EEE26
#define USER32_DLL_ShowWindow			        0xC95E4F93

// ***** wininet.dll (5 functions) ***** //
#define WININET_DLL_STR         { 'w', 'i', 'n', 'i', 'n', 'e', 't', '.', 'd', 'l', 'l', '\0' }
#define WININET_DLL                             0xF22AEDD
#define WININET_DLL_InternetOpenA               0x57EA4649
#define WININET_DLL_InternetOpenUrlA            0xBE0FF16D
#define WININET_DLL_InternetQueryDataAvailable  0xD960FB6A
#define WININET_DLL_InternetReadFile            0x9FE34F8F
#define WININET_DLL_InternetCloseHandle         0x29B69E0

#endif