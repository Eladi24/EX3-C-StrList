flags = -g -Wall

all: StrList

StrList: main.o StrList.o
	gcc $(flags) main.o StrList.o -o StrList
StrList.o: StrList.c StrList.h
	gcc $(flags) -c StrList.c -o StrList.o
main.o: main.c 
	gcc $(flags) -c main.c -o main.o

.PHONY: all clean

clean:
		rm -f *.o StrList