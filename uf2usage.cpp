#include <z/all.hpp>
#include <iostream>
#include "uf2block.hpp"
#include "jsondata.hpp" //file gets auto-generated

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "ERROR: No input file." << std::endl;
		return -1;
	}
	z::file::inputStream file (argv[1]);

	/*
	std::cout << "Address \tBytes\tBlock" << std::endl;
	std::cout << "-"_asc.repeat(70) << std::endl;
	*/

	uf2block block;
	int totalBlocks = 1;
	int totalBytes = 0;
	zstring family;
	for (int i=0; i<totalBlocks; ++i)
	{
		if (!block.read(file))
		{
			std::cerr << "Error at block " << i << ", exiting." << std::endl;
			return -1;
		}

		// std::cout << "0x" << zstring(block.address, 16, 8) << '\t';
		// std::cout << block.bytes << '\t';
		// std::cout << block.block << '\t';
		if (block.flags & UF2_FAM)
		{
			int pos = jsondata::id.find(block.misc);
			if (pos >= 0)
			{
				// std::cout << "Family: " << jsondata::short_name[pos];
				family = jsondata::description[pos];
			}
			else
			{
				family = "0x"_u32 + zstring(block.misc, 16, 8);
				// std::cout << "Family: " << "0x" << zstring(block.misc, 16, 8);
			}
		}
		// std::cout << "0x" << zstring(block.misc, 16, 8) << '\t';
		// std::cout << block.flagstr() << '\t';
		// std::cout << std::endl;

		totalBlocks = block.length;
		totalBytes += block.bytes;
	}

	// std::cout << "-"_asc.repeat(70) << std::endl;
	std::cout << "Family ID: " << family << std::endl;
	std::cout << "Flash Usage: " << totalBytes << " Bytes (" << ((float)totalBytes / 1024) << " KiB)" << std::endl;

}
