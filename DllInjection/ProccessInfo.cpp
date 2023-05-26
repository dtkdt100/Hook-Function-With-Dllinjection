#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include "ProccessInfo.h"

ProccessInfo::ProccessInfo(const std::wstring& pName): m_proccess(findCorrectProccess(pName))
{

}

uint32_t ProccessInfo::getPid() const
{
    uint32_t pid = GetProcessId(m_proccess.getRawHandle());
    if (!pid) {
        throw std::exception(std::to_string(GetLastError()).c_str());
    }
    return pid;
}

Handle ProccessInfo::findCorrectProccess(const std::wstring& pName) const
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    Handle snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot.getRawHandle(), &entry) == TRUE)
    {
        while (Process32Next(snapshot.getRawHandle(), &entry) == TRUE)
        {
            if (entry.szExeFile == pName)
            {
                return Handle(OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID));
            }
        }
    }
    return INVALID_HANDLE_VALUE;
}
