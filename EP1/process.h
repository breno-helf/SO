#ifndef PROCESS
#define PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 1123
#define START_SIZE 2

typedef struct {
    int id;
    double t0;
    double dt;
    double deadline;
    char * name;
} process;

/**
 * Comparator for sorting the process acording to
 * the time that it arrives at the processor.
 */
int first_coming_cmp(const void * p1, const void * p2);

/*
  Build process based on arguments t0, dt, deadline
  and name. Return a pointer to the process created.
*/
process * build_process(int id, double t0, double dt, double deadline,
		   char * name);
/*
  Creates a vector of the process struct.
*/
void start_vector(process ** v, int * cur_pos, int * cur_size,
		  int * complete_process, int * context_change);

/* 
   Doubles the size of a vector of process.
*/
void double_size(process ** v, int * cur_size);

/*
  Push process p to the vector of process v.
*/
void push_process(process ** v, int * cur_pos, int * cur_size,
		  process p);

/*
  Free the memory occupied by the vector v.
*/
void free_vector(process *v, int * cur_pos, int * cur_size);

/*
  Read the trace file and stores it in the vector
  of process v.
*/
void read_trace(FILE * trace, process ** v, int * cur_pos,
		int * cur_size);
#endif
