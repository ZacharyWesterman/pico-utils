

all: uf2usage

uf2usage: uf2usage.cpp jsondata.hpp
	g++ -lzed --std=c++17 $< -o $@

uf2families.json:
	wget https://raw.githubusercontent.com/microsoft/uf2/master/utils/uf2families.json

jsondata.hpp: json2c uf2families.json
	./$^ > $@

json2c: json2c.cpp
	g++ -lzed --std=c++17 $< -o $@

clean:
	rm uf2usage uf2families.json json2c jsondata.hpp

install: uf2usage
	cp $< ~/.local/bin/

uninstall:
	rm ~/.local/bin/{uf2usage}

.PHONY: clean install uninstall
