FLAGS := -std=c11 -Wall -Wextra

all: directories config.h obj/cfetch.o obj/api.o obj/drw.o build

directories:
	mkdir -p obj

clean:
	rm -r obj

install:
	cp cff /bin

uninstall:
	rm /bin/cff

config.h: ./config.def.h
	cp config.def.h config.h

obj/cfetch.o: ./src/cfetch.c ./src/cfetch.h config.h
	cc -I./ -Isrc -c src/cfetch.c -o obj/cfetch.o

obj/drw.o: ./src/drw.c ./src/drw.h config.h
	cc -I./ -Isrc -c src/drw.c -o obj/drw.o
	
obj/api.o: ./src/api.c ./src/api.h config.h
	cc -I./ -Isrc -c src/api.c -o obj/api.o

build: obj/cfetch.o obj/drw.o obj/api.o
	cc obj/cfetch.o obj/drw.o obj/api.o -o cff ${FALGS}

.PHONY: all directories clean install uninstall
