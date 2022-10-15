#include <iostream>
#include "DllInjection/ProccessInfo.h"
#include "DllInjection/DllInjector.h"

char evilDLL[] = "C:\\Users\\dolev\\source\\repos\\DllInjection\\x64\\Debug\\DllFile.dll";
unsigned int evilLen = sizeof(evilDLL) + 1;

int main()
{
    try {
        const auto processName = L"Notepad.exe";
        const auto pid = ProccessInfo(processName);
        const auto d = DllInjector(pid.m_proccess);
    }
    catch (const std::exception& e) {
        std::cout << "Error " << e.what() << std::endl;
    }
    return 0;
}