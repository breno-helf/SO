#ifndef SHORTEST
#define SHORTEST

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
  It pushes each process into the heap once it gets
  to the processor. Then choose the shortest one
  and run it until the end.
*/
void shortest(FILE * output, process * v, int n);

#endif
