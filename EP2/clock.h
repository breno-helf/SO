#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*
  Get the time elapsed since start
  To get the current time use gettimeofday.
*/
double get_time(struct timeval start);

#endif
