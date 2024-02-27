FLAGS = -g -Wall

all: StrList
StrList: main.o StrList.o
	gcc $(FLAGS) main.o StrList.o -o StrList
StrList.o: StrList.c StrList.h
	gcc $(FLAGS) -c StrList.c -o StrList.o
main.o: main.c 
	gcc $(FLAGS) -c main.c -o main.o

.PHONY: all clean

clean:
		rm -f *.o *.a StrList Strlistd