FLAGS=-Wall -pedantic -g -std=c99 -D _POSIX_C_SOURCE=199309L
FILES=ep1sh

clear:
	rm ${FILES} *~ a.out

ep1sh: ep1sh.c
	gcc ${FLAGS} -o ep1sh ep1sh.c -lreadline

