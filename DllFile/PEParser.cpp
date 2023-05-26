#include "pch.h"
#include "PEParser.h"
#include <iostream>
#include <sstream>

using PrototypeCreateFileW = HANDLE(WINAPI*)(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
	);

PrototypeCreateFileW originalCreateFileW = CreateFileW;

HANDLE WINAPI newCreateFileW(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
) {
	MessageBoxW(NULL, L"Hola from hooke CreateFileW", NULL, MB_OK);

	return originalCreateFileW(lpFileName, dwDesiredAccess,
		dwShareMode, lpSecurityAttributes, dwCreationDisposition,
		dwFlagsAndAttributes, hTemplateFile);
};


PEParser::PEParser()
{
	
}

void PEParser::inject()
{
	LPVOID imageBase = GetModuleHandleA(NULL);
	PIMAGE_DOS_HEADER dosHeaders = (PIMAGE_DOS_HEADER)imageBase;
	PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)imageBase + dosHeaders->e_lfanew);
	IMAGE_OPTIONAL_HEADER imageOptionalHeaders = ntHeaders->OptionalHeader;
	IMAGE_DATA_DIRECTORY imageDirEntryImport = imageOptionalHeaders.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	// pointer to an array


	// null ending list:
	PIMAGE_IMPORT_DESCRIPTOR imageImportDes = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD_PTR)imageBase + imageDirEntryImport.VirtualAddress);

	PIMAGE_IMPORT_BY_NAME functionName = NULL;

	int i = 0;

	while (imageImportDes->Name != NULL) {
		// name of the DLL file:
		LPCSTR Name = (LPCSTR)((DWORD_PTR)imageBase + imageImportDes->Name);

		HMODULE library = LoadLibraryA(Name);

		if (!library) return;


		// INT - import name table
		PIMAGE_THUNK_DATA originalFirstTrunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + imageImportDes->OriginalFirstThunk);
		// IAT - import address table
		PIMAGE_THUNK_DATA firstTrunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + imageImportDes->FirstThunk);
		// both IAT and IAT are in the same size and one represetes the other addresses

		while (originalFirstTrunk->u1.AddressOfData != NULL) {

			//function name:
			functionName = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)imageBase + originalFirstTrunk->u1.AddressOfData);

			if (std::string(functionName->Name).compare("CreateFileW") == 0) {
				SIZE_T bytesWritten = 0;
				DWORD oldProtect = 0;
				VirtualProtect((LPVOID)(&firstTrunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);

				firstTrunk->u1.Function = (DWORD_PTR)newCreateFileW;

				MessageBoxW(NULL, L"Done hooking message", NULL, MB_OK);

				return;
			}
			++originalFirstTrunk;
			++firstTrunk;
		}
		imageImportDes++;
		i++;
	}	
}
