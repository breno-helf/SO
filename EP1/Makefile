FLAGS = -pthread -Wall -pedantic -g -std=c99 -D _POSIX_C_SOURCE=199309L
FILES = ep1.c process.c process.h clock.c clock.h event.h heap.h heap.c shortest.c shortest.h linkedlist.h linkedlist.c
EXEC = ep1sh ep1

clear:
	rm ${EXEC} *~ a.out

ep1sh: ep1sh.c
	gcc ${FLAGS} -o ep1sh ep1sh.c -lreadline

ep1: ${FILES}
	gcc ${FLAGS} -o ep1 ${FILES}
