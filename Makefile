FLAGS := -std=c11 -Wall -Wextra

all: cfetch.o build

cfetch.o: cfetch.c cfetch.h logo.h config.h
	cc -c cfetch.c -o cfetch.o

build: cfetch.o
	cc cfetch.o -o cff ${FALGS}

clean: cfetch.o
	rm cff cfetch.o

install:
	cp cff /bin

uninstall:
	rm /bin/cff
