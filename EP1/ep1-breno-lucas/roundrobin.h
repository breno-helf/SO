#ifndef ROUND_ROBIN
#define ROUND_ROBIN

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "process.h"
#include "queue.h"
#include "clock.h"


/*
  It pushed each process into the queue once it gets
  to the processor. Then it runs the process in the
  front of the Queue for QUANTUM time and if it is
  not done yet it pushes it into the Queue again.
*/
void round_robin(FILE * output, process * v, int n);

#endif
