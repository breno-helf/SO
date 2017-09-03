#ifndef HIGHEST_PRIORITY
#define HIGHEST_PRIORITY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "process.h"
#include "heap.h"
#include "clock.h"

/*
  Calculates how many QUANTUMs the process p should
  run for, if the current time is cur_time. If the process
  is more close to reaching the deadline it runs for more time,
  if the deadline is gone, it just runs for 20 QUANTUMs.
*/
int calc_quantum(process * p, double cur_time);

/* 
  It pushes each process into the heap once it gets
  to the processor. Then choose the one with highest
  priotixy, and run it for QUANTUM * x where x is a
  variable that depends on how high the priority is
  (It is calculated by calc_quantum function).
*/
void highest_priority(FILE * output, process * v, int n);

#endif
