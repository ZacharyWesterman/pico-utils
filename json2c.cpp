#include <z/core/string.hpp>
#include <iostream>
#include <z/file/inputStream.hpp>
#include <z/core/array.hpp>
#include <map>

zstring jsontrim(const zstring& text)
{
	return text.trim().trimIn(':').trimIn(',').trimIn().trimIn('"');
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "ERROR: No input file." << std::endl;
		return -1;
	}

	std::map<zstring, z::core::array<zstring> > data;

	z::file::inputStream file (argv[1]);
	zstring line;
	while (!file.empty())
	{
		line.readln(file);
		int pos = line.find(":");
		if (pos >= 0)
		{
			auto field = jsontrim(line.substr(0,pos));
			auto value = jsontrim(line.substr(pos+1, line.length()));
			data[field].add(value);
		}
	}

	std::cout << "namespace jsondata\n{" << std::endl;
	for (auto& i : data)
	{
		std::cout << "\tconst z::core::array<zstring> " << i.first << " = {" << std::endl;
		for (auto& value : i.second)
		{
			std::cout << "\t\t\"" << value << "\"," << std::endl;
		}
		std::cout << "\t};" << std::endl;
	}
	std::cout << "}" << std::endl;
}
