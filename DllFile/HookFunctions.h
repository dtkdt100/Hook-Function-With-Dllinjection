#include "pch.h"
#include <stdio.h>
#include "PEParser.h"
//#include <Windows.h>



struct JMP_14Bytes // Absolute Jump for 64bit
{
    BYTE opcode1; // 0x68 : Push
    DWORD lpTarget1; // Address - 4~8
    DWORD opcode2; // 0x042444C7 : MOV [ESP+4], ????
    DWORD lpTarget2; // Address - 0~4
    BYTE opcode3; // 0xC3 : RET
};




#pragma once
class HookFunctions
{
public:
	HookFunctions() {};

	int hookCreateFile() {

        MessageBoxW(NULL, L"hello", NULL, MB_OK);
        PEParser::inject();
        return 0;
    };

    
};

