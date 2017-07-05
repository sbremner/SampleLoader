#include "Utils.h"

PPEB get_peb(void)
{
	PPEB peb;

	__asm {
		xor eax, eax
		mov eax, fs:[eax + 0x30]
		mov peb, eax
	}

	return peb;
}

DWORD __stdcall unicode_ror13_hash(const WCHAR *unicode_string)
{
	DWORD hash = 0;

	while (*unicode_string != 0)
	{
		DWORD val = (DWORD)*unicode_string++;
		hash = (hash >> 13) | (hash << 19); // ROR 13
		hash += val;
	}
	return hash;
}

DWORD __stdcall ror13_hash(const char *string)
{
	DWORD hash = 0;

	while (*string) {
		DWORD val = (DWORD)*string++;
		hash = (hash >> 13) | (hash << 19);  // ROR 13
		hash += val;
	}
	return hash;
}

HMODULE __stdcall find_module_by_hash(DWORD hash)
{
	PPEB peb;
	LDR_DATA_TABLE_ENTRY *module_ptr, *first_mod;

	peb = get_peb();

	module_ptr = (PLDR_DATA_TABLE_ENTRY)peb->Ldr->InMemoryOrderModuleList.Flink;
	first_mod = module_ptr;

	do {
		WCHAR * pwLower = tolower((WCHAR *)module_ptr->FullDllName.Buffer, length((WCHAR *)module_ptr->FullDllName.Buffer));

		if (unicode_ror13_hash(pwLower) == hash){
			free(pwLower);
			return (HMODULE)module_ptr->Reserved2[0];
		}
		else{
			module_ptr = (PLDR_DATA_TABLE_ENTRY)module_ptr->Reserved1[0];
		}
		free(pwLower);
	} while (module_ptr && module_ptr != first_mod);   // because the list wraps,

	return (HMODULE)INVALID_HANDLE_VALUE;
}

FARPROC __stdcall find_function(HMODULE module, DWORD hash)
{
	IMAGE_DOS_HEADER *dos_header;
	IMAGE_NT_HEADERS *nt_headers;
	IMAGE_EXPORT_DIRECTORY *export_dir;
	DWORD *names, *funcs;
	WORD *nameords;
	DWORD i;

	dos_header = (IMAGE_DOS_HEADER *)module;
	nt_headers = (IMAGE_NT_HEADERS *)((char *)module + dos_header->e_lfanew);
	export_dir = (IMAGE_EXPORT_DIRECTORY *)((char *)module + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	names = (DWORD *)((char *)module + export_dir->AddressOfNames);
	funcs = (DWORD *)((char *)module + export_dir->AddressOfFunctions);
	nameords = (WORD *)((char *)module + export_dir->AddressOfNameOrdinals);

	for (i = 0; i < export_dir->NumberOfNames; i++)
	{
		char *string = (char *)module + names[i];
		char * pLower = tolower(string, length(string));

		if (hash == ror13_hash(pLower)) // added tolower to make sure always lower for comparing
		{
			WORD nameord = nameords[i];
			DWORD funcrva = funcs[nameord];
			free(pLower);
			return (FARPROC)((char *)module + funcrva);
		}
		
		free(pLower);
	}

	return NULL;
}

void __cdecl memcpy(PVOID dest, PVOID src, DWORD dwSize)
{
	unsigned char * pDest = (unsigned char *)dest;
	unsigned char * pSrc = (unsigned char *)src;

	for (int k = 0; k < dwSize; k++)
	{
		pDest[k] = pSrc[k];
	}
}

void __cdecl memset(void * pMem, DWORD dwLength, UCHAR value)
{
	unsigned char * pData = (unsigned char *)pMem;

	for (unsigned int __iter__ = 0; __iter__ < dwLength; __iter__++)
	{
		pData[__iter__] = value;
	}
}

void * resize(PVOID pBuf, DWORD dwCurrentSize, DWORD dwNewSize)
{
	void * pNewBuf = malloc(dwNewSize);

	if (pBuf != NULL && dwCurrentSize != 0)
	{
		memcpy(pNewBuf, pBuf, min(dwCurrentSize, dwNewSize));
		free(pBuf); // deallocate the old buffer since we have a new one
	}

	return pNewBuf;
}

char * decode(char * buf, int length, unsigned char key, unsigned char offset)
{
	char * result = (char *)malloc(length + 1);
	memset(result, length + 1, 0);

	for (int i = 0; i < length; i++)
	{
		result[i] = DECODE_CHAR(buf[i], key, offset);
	}

	return result;
}

/*char toupper(char ch)
{
	if (ch >= 97 && ch <= 122)
	{
		return ch & 0xdf;
	}

	return ch;
}*/

char tolower(char ch)
{
	if (ch >= 65 && ch <= 90)
	{
		return ch | 0x20;
	}

	return ch;
}

char * tolower(char * pString, DWORD dwLength)
{
	char * pLower = (char *)malloc(sizeof(char) * dwLength + 1);
	pLower[dwLength] = 0;

	for (int k = 0; k < dwLength; k++)
	{
		pLower[k] = tolower(pString[k]);
	}

	return pLower;
}

WCHAR tolower(WCHAR ch)
{
	if ((ch >> 8) == 0) // High end byte is 0
	{
		// Let's convert the low end byte to lower like an ASCII char
		// Since high end byte is 0, we can just return this value as a WCHAR
		return (WCHAR)tolower((char)(ch & 0xFF));
	}

	return ch; // Not in our ascii character set (don't care)
}

WCHAR * tolower(WCHAR * pwString, DWORD dwLength)
{
	WCHAR * pwLower = (WCHAR *)malloc(sizeof(WCHAR) * dwLength + 1);
	pwLower[dwLength] = 0;

	for (int k = 0; k < dwLength; k++)
	{
		pwLower[k] = tolower(pwString[k]);
	}

	return pwLower;
}


DWORD length(char * pString)
{
	DWORD count = 0;
	char * iter = pString;

	for (; *iter != NULL; iter++){
		count++;
	}

	return count;
}

DWORD length(WCHAR * pwString)
{
	DWORD count = 0;
	WCHAR * iter = pwString;

	for (; *iter != NULL; iter++){
		count++;
	}

	return count;
}