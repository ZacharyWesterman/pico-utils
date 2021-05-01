#include <z/all.hpp>
#include <iostream>

uint32_t getInt(z::core::inputStream& stream)
{
	uint32_t res = 0;
	char* buf = (char*)&res;
	for (int i=0; i<4; ++i) buf[i] = stream.get();
	return res;
}

enum uf2flags
{
	UF2_SKIP = 0x00000001, //Not in main flash, skip this block
	UF2_FILE = 0x00001000, //File container
	UF2_FAM  = 0x00002000, //Family ID present
	UF2_MD5  = 0x00004000, //MD5 checksum present
	UF2_EXT  = 0x00008000, //Extension tags present
};

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

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "ERROR: No input file." << std::endl;
		return -1;
	}
	// zpath fname = "/home/zachary/repos/pico-sandbox/build/test.uf2";
	z::file::inputStream file (argv[1]);

	/*
	std::cout << "Address \tBytes\tBlock\tMisc    \tFlags" << std::endl;
	std::cout << "-"_asc.repeat(80) << std::endl;
	*/

	uf2block block;
	int totalBlocks = 1;
	int totalBytes = 0;
	for (int i=0; i<totalBlocks; ++i)
	{
		if (!block.read(file))
		{
			std::cerr << "Error at block " << i << ", exiting." << std::endl;
			return -1;
		}

		/*
		std::cout << "0x" << zstring(block.address, 16, 8) << '\t';
		std::cout << block.bytes << '\t';
		std::cout << block.block << '\t';
		std::cout << "0x" << zstring(block.misc, 16, 8) << '\t';
		std::cout << block.flagstr() << '\t';
		std::cout << std::endl;
		*/

		totalBlocks = block.length;
		totalBytes += block.bytes;
	}

	// std::cout << "-"_asc.repeat(80) << std::endl;
	std::cout << "Flash Usage: " << totalBytes << " Bytes (" << ((float)totalBytes / 1024) << " KiB)" << std::endl;

}
