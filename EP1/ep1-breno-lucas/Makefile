# Breno Helfstein Moura       NUSP: 9790972
# Lucas Daher                 NUSP: 8991769

FLAGS = -pthread -Wall -pedantic -g -std=c99 -D _POSIX_C_SOURCE=199309L
OBJS = ep1.o process.o clock.o event.o heap.o shortest.o queue.o roundrobin.o highestpriority.o
EXEC = ep1sh ep1

.PHONY: clean

all: ep1 ep1sh

ep1sh: ep1sh.o
	$(CC) $(CFLAGS) $^ -o $@ -lreadline
	make clean

ep1: $(OBJS)
	$(CC) $(FLAGS) $^ -o $@
	make clean

%.o: %.c %.h
	$(CC) $(FLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *~
