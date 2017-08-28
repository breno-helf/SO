FLAGS = -pthread -Wall -pedantic -g -std=c99 -D _POSIX_C_SOURCE=199309L
FILES = ep1sh ep1
OBJS = process.o linkedlist.o

clear:
	rm ${FILES} *~ a.out

ep1sh: ep1sh.c
	gcc ${FLAGS} -o ep1sh ep1sh.c -lreadline

ep1: ep1.c process.c process.h linkedlist.c linkedlist.h
	gcc ${FLAGS} -o ep1 ep1.c process.c linkedlist.c
