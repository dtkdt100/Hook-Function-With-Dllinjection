#include <iostream>
#include "DllInjection/ProccessInfo.h"

int main()
{
    std::wstring hi = L"explorer.exe";
    const auto p = ProccessInfo(hi);

    std::cout << p.getPid() << std::endl;
    return 0;
}