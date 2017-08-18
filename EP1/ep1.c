#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "process.h"

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
    input_name = argv[2];
    output_name = argv[3];
    
    if (type < 1 || type > 3) {
	fprintf(stderr, "Type not supported, the supported types are:\n");
	fprintf(stderr, "1. Shortest Job First\n");
	fprintf(stderr, "2. Round Robin\n");
	fprintf(stderr, "3. Scheduling with Priority\n");

	return -1;
    }

    input = fopen(input_name, "r");
    output = fopen(output_name, "w");

    if (input == NULL) {
	fprintf(stderr, "Fatal error: Failed to open file %s\n", input_name);
	return -1;
    }

    if (output == NULL) {
	fprintf(stderr, "Fatal error: Failed to open file %s\n", output_name);
	return -1;
    }

    process * v;
    int cur_pos, cur_size, complete_process, context_change;

    start_vector(&v, &cur_pos, &cur_size, &complete_process, &context_change);
    read_trace(input, &v, &cur_pos, &cur_size);
    /*
      qsort(v, cur_pos, sizeof(process), shortest_process_cmp);
      qsort(v, cur_pos, sizeof(process), highest_priority_cmp);
    */
    for (int i = 0; i < cur_pos; i++) {
	fprintf (stderr, "%lf %lf %lf %s\n", v[i].t0, v[i].dt, v[i].deadline, v[i].name);
    }
    free_vector(v, &cur_pos, &cur_size);
}