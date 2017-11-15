# Breno Helfstein Moura       NUSP: 9790972
# Lucas Daher                 NUSP: 8991769

FLAGS = -Wall -pedantic -g
OBJS = ep3.o trace.hpp BestFit.o fifo.o BinFile.o
EXEC = ep3

.PHONY: clean

all: ep3

ep3: $(OBJS)
	g++ $(FLAGS) $^ -o $@
	make clean

%.o: %.cpp %.hpp
	g++ $(FLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *~
