#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int shortest_process_cmp(const void * p1, const void * p2) {
    double t1 = ((process * )p1)->dt;
    double t2 = ((process * )p2)->dt;
    if (t1 > t2) return 1;
    if (t1 < t2) return -1;
    return 0;
}

int main(int argc, char * argv[]) {
    int type = 0;
    char * input_name;
    char * output_name;
    FILE * input;
    FILE * output;
    
    if (argc < 4) {
	fprintf(stderr, "Fatal error: Not enough arguments\n");
	return -1;
    }

    type = atoi(argv[1]);

    if (type < 1 || type > 3) {
	fprintf(stderr, "Type not supported, the supported types are:\n");
	fprintf(stderr, "1. Shortest Job First\n");
	fprintf(stderr, "2. Round Robin\n");
	fprintf(stderr, "3. Scheduling with Priority\n");

	return -1;
    }
}
