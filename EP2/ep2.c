/*
* * Breno Helfstein Moura       NUSP: 9790972
* * Lucas Daher                 NUSP: 8991769
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "event.h"
#include "clock.h"


int main(int argc, char * argv[]) {
    /*
      d = Track size (in meters)
      v = Number of Circuits
      n = Number of Ciclists
    */
    int d, v, n;

    srand(time(NULL));
    
    if (argc < 4) {
	fprintf(stderr, "Fatal error: Not enough arguments\n");
	return -1;
    }
    
    d = atoi(argv[1]);
    n = atoi(argv[2]);
    v = atoi(argv[3]);

    if (d < 250) {
	fprintf(stderr, "Track Size must be greater or equal than 250\n");
	return -1;
    }

    if (n <= 5 || n > 5 * d) {
	fprintf(stderr, "Number of Ciclists must be between 6 and 5 * Track_Size, inclusive\n");
	return -1;
    }

    if (v % 20 != 0) {
	fprintf(stderr, "Number of circuits must be divisible by 20\n");
	return -1;
    }

    /*
      Turn on the debug (event) log
    */
    if (argc > 4 && strcmp(argv[4], "d") == 0) {
	event(NULL);
    }    
    
    return 0;
}
