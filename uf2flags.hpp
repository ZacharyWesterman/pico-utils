#pragma once

enum uf2flags
{
	UF2_SKIP = 0x00000001, //Not in main flash, skip this block
	UF2_FILE = 0x00001000, //File container
	UF2_FAM  = 0x00002000, //Family ID present
	UF2_MD5  = 0x00004000, //MD5 checksum present
	UF2_EXT  = 0x00008000, //Extension tags present
};
