
EXECLIST = uf2usage picoterm uf2topico

uf2usage: uf2usage.cpp jsondata.hpp
	g++ --std=c++17 $< -lzed -o $@

uf2families.json:
	wget https://raw.githubusercontent.com/microsoft/uf2/master/utils/uf2families.json

jsondata.hpp: json2c uf2families.json
	./$^ > $@

json2c: json2c.cpp
	g++ --std=c++17 $< -lzed -o $@

clean:
	rm -f uf2usage uf2families.json json2c jsondata.hpp

install: $(EXECLIST)
	cp $^ ~/.local/bin/

uninstall:
	cd ~/.local/bin && rm -f $(EXECLIST)

.PHONY: clean install uninstall
