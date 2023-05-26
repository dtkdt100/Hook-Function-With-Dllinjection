#include <iostream>
#include "DllInjection/ProccessInfo.h"
#include "DllInjection/DllInjector.h"

const auto evilDllPath = "C:\\Users\\dolev\\source\\repos\\DllInjection\\x64\\Debug\\DllFile.dll";
const auto processName = L"Notepad.exe";

int main()
{   
    try {
        const auto pid = ProccessInfo(processName);
        const auto d = DllInjector(pid.m_proccess, evilDllPath);
    }
    catch (const std::exception& e) {
        std::cout << "Got error " << e.what() << std::endl;
    }
    return 0;
}