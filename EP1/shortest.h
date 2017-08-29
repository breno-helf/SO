#ifndef SHORTEST
#define SHORTEST

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "event.h"
#include "process.h"
#include "heap.h"
#include "clock.h"

void shortest(FILE * output, process * v, int n);

#endif
