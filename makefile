

all: uf2usage

uf2usage: uf2usage.cpp json2c uf2families.json
	g++ -lzed --std=c++17 $< -o $@

uf2families.json:
	wget https://github.com/microsoft/uf2/blob/master/utils/uf2families.json

json2c: json2c.cpp
	g++ -lzed --std=c++17 $< -o $@

clean:
	rm uf2usage uf2families.json json2c

install: uf2usage
	cp $< ~/.local/bin/

uninstall:
	rm ~/.local/bin/{uf2usage}

.PHONY: clean install uninstall
