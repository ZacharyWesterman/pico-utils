

all: uf2usage

uf2usage: uf2usage.cpp
	g++ -lzed --std=c++17 $< -o $@

clean:
	rm uf2usage

install: uf2usage
	cp $< ~/.local/bin/

uninstall:
	rm ~/.local/bin/{uf2usage}

.PHONY: clean install uninstall
