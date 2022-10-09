#pragma once
#include <string>
#include "Handle.h"

class ProccessInfo
{
public:
	explicit ProccessInfo(const std::wstring& pName);

	uint32_t getPid() const;

private:
	Handle findCorrectProccess(const std::wstring& pName) const;

	Handle m_proccess;
};

