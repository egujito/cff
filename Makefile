FLAGS := -std=c11 -Wall -Wextra

all: config.h obj/cfetch.o obj/api.o obj/drw.o build

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

clean: obj/cfetch.o obj/drw.o obj/api.o
	rm cff obj/cfetch.o obj/drw.o obj/api.o

install:
	cp cff /bin

uninstall:
	rm /bin/cff
