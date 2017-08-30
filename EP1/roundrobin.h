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

void round_robin(FILE * output, process * v, int n);

#endif
