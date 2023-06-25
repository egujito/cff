FLAGS := -std=c11 -Wall -Wextra

all: config.h cfetch.o build

config.h: ./config.def.h
	cp config.def.h config.h

cfetch.o: ./src/cfetch.c ./src/cfetch.h ./src/logo.h config.h
	cc -I./ -Isrc -c src/cfetch.c -o obj/cfetch.o

build: obj/cfetch.o
	cc -Iinclude obj/cfetch.o -o cff ${FALGS}

clean: obj/cfetch.o
	rm cff obj/cfetch.o

install:
	cp cff /bin

uninstall:
	rm /bin/cff
