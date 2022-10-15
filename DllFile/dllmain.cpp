// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <TlHelp32.h>
#include <tchar.h>
#pragma comment (lib, "user32.lib")

DWORD dwGetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID)
{
    DWORD dwBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
    MODULEENTRY32 moduleEntry32 = { 0 };
    moduleEntry32.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hSnapshot, &moduleEntry32))
    {
        do {
            if (_tcscmp(moduleEntry32.szModule, lpszModuleName) == 0)
            {
                dwBaseAddress = (DWORD)moduleEntry32.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &moduleEntry32));
    }
    CloseHandle(hSnapshot);
    return dwBaseAddress;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(
            NULL,
            L"ddd",
            L"=sss^=",
            MB_OK
        );
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

