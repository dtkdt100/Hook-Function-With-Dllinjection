#pragma once
#include <string>
#include "Handle.h"

class ProccessInfo
{
public:
	explicit ProccessInfo(const std::wstring& pName);

	uint32_t getPid() const;

	Handle m_proccess;


private:
	Handle findCorrectProccess(const std::wstring& pName) const;

};

