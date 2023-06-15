FLAGS := -std=c11 -Wall

all: cfetch.o build

cfetch.o: cfetch.c cfetch.h
	cc -c cfetch.c -o cfetch.o

build: cfetch.o
	cc cfetch.o -o cff ${FALGS}

clean: cfetch.o
	rm cff cfetch.o

install:
	cp cff /bin
