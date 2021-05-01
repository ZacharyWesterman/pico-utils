#pragma once
#include <z/core/stream.hpp>

uint32_t getInt(z::core::inputStream& stream)
{
	uint32_t res = 0;
	char* buf = (char*)&res;
	for (int i=0; i<4; ++i) buf[i] = stream.get();
	return res;
}
