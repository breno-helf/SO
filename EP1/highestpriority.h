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

int calc_quantum(process * p, double cur_time);

void highest_priority(FILE * output, process * v, int n);

#endif
