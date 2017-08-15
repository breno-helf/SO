#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

const int MAX_SIZE = 1123;
const int START_SIZE = 2;

typedef struct {
    double t0;
    double dt;
    double deadline;
    char * name;    
} process;

int shortest_process_cmp(const void * p1, const void * p2);

void start_vector(process * v, int * cur_pos, int * cur_size,
		  int * complete_process, int * context_change);

void double_size(process ** v, int * cur_size);

void push_process(process * v, int * cur_pos, int * cur_size,
		  process p);

void free_vector(process *v, int * cur_pos, int * cur_size);

void read_trace(FILE * trace, process * v, int * cur_pos,
		int * cur_size);
