#include "pch.h"
#include "HookFunctions.h"
//
//struct JMP_14Bytes // Absolute Jump for 64bit
//{
//    BYTE opcode1; // 0x68 : Push
//    DWORD lpTarget1; // Address - 4~8
//    DWORD opcode2; // 0x042444C7 : MOV [ESP+4], ????
//    DWORD lpTarget2; // Address - 0~4
//    BYTE opcode3; // 0xC3 : RET
//};
//
//BOOL WINAPI newCreateFileW(
//    _In_ LPCWSTR lpFileName,
//    _In_ DWORD dwDesiredAccess,
//    _In_ DWORD dwShareMode,
//    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
//    _In_ DWORD dwCreationDisposition,
//    _In_ DWORD dwFlagsAndAttributes,
//    _In_opt_ HANDLE hTemplateFile
//) {
//        MessageBoxW(NULL, lpFileName, NULL, NULL);
//
////#ifdef _WIN64
////    Unhook64();
////    BOOL ret = WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
////    Hook64();
////#else
////    Unhook32();
////    BOOL ret = WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
////    Hook32();
////#endif
//
//    return 1;
//};
//
//int HookFunctions::hookCreateFile()
//{
//
    //LPVOID lpOrgFunc = NULL;
    //if ((lpOrgFunc = GetProcAddress(GetModuleHandleA("kernel32.dll"), "CreateFile")) == NULL)
    //    return -1;

    //if (*(SHORT*)lpOrgFunc == 0x25FF)
    //{
    //    if ((lpOrgFunc = GetProcAddress(GetModuleHandleA("kernelbase.dll"), "CreateFile")) == NULL)
    //        return -1;
    //}
    //JMP_14Bytes orgFP;

    //// Inline Hook
    //// Backup old protect
    //DWORD dwOldProtect;
    //if (VirtualProtect(lpOrgFunc, sizeof(JMP_14Bytes), PAGE_EXECUTE_READWRITE, &dwOldProtect) == NULL)
    //    return -1;

    //memcpy_s(&orgFP, sizeof(JMP_14Bytes), lpOrgFunc, sizeof(JMP_14Bytes));

    //JMP_14Bytes newFuncObj;
    //newFuncObj.opcode1 = 0x68; // Push ????
    //newFuncObj.lpTarget1 = (DWORD)((DWORD64)(&newCreateFileW) & 0xFFFFFFFF);
    //newFuncObj.opcode2 = 0x042444C7; // MOV [ESP+4], ????
    //newFuncObj.lpTarget2 = (DWORD)((DWORD64)(&newCreateFileW) >> 32);
    //newFuncObj.opcode3 = 0xC3; // RET

    //memcpy_s(lpOrgFunc, sizeof(JMP_14Bytes), &newFuncObj, sizeof(JMP_14Bytes)); // Replacing

    //                                                                            // Rollback protection
    //VirtualProtect(lpOrgFunc, sizeof(JMP_14Bytes), dwOldProtect, NULL);
//
//    return 0;
//}
