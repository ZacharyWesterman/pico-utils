#pragma once
#include "getInt.hpp"
#include "uf2flags.hpp"
#include <iostream>
#include <z/core/string.hpp>

struct uf2block
{
	uint32_t flags;
	uint32_t address; //address in flash where data should be written
	uint32_t bytes; //number of bytes used in data
	uint32_t block; //sequential block number; starts at 0
	uint32_t length; //total number of blocks in file
	uint32_t misc; //file size or board family ID or zero
	char data[476];

	bool read(z::core::inputStream& stream)
	{
		//Check that we're in a valid UF2 block
		uint32_t magic1 = getInt(stream);
		uint32_t magic2 = getInt(stream);
		if ((magic1 != 0x0a324655) || (magic2 != 0x9e5d5157))
		{
			std::cerr << "Invalid UF2 block!" << std::endl;
			return false;
		}

		//Read UF2 block
		flags = getInt(stream);
		address = getInt(stream); //address in flash where data should be written
		bytes = getInt(stream); //number of bytes used in data
		block = getInt(stream); //sequential block number; starts at 0
		length = getInt(stream); //total number of blocks in file
		misc = getInt(stream); //file size or board family ID or zero

		char data[476];
		for (int i=0; i<476; ++i) data[i] = stream.get();

		//Check that UF2 block ended correctly
		uint32_t magic3 = getInt(stream);
		if (magic3 != 0x0ab16f30)
		{
			std::cerr << "Incorrect UF2 block terminator!" << std::endl;
			return false;
		}

		return true;
	}

	zstring flagstr()
	{
		switch (flags)
		{
			case UF2_SKIP:
				return "not main flash";
			case UF2_FILE:
				return "file container";
			case UF2_FAM:
				return "familyID present";
			case UF2_MD5:
				return "MD5 checksum present";
			case UF2_EXT:
				return "extension tags present";
			default:
				return "unknown";
		}
	}

};
