#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "linkedlist.h"
#include <pthread.h>

void *np_func(void *arg) {
    float secs = *((double*) arg);
    struct timespec t;
    t.tv_sec = (int) secs;
    secs -= t.tv_sec;
    t.tv_nsec = secs * 1000000000;
    nanosleep(&t, NULL);
    return NULL;
}

void *np_func(void *arg) {
    float secs = *((double*) arg);
    struct timespec t;
    t.tv_sec = (int) secs;
    secs -= t.tv_sec;
    t.tv_nsec = secs * 1000000000;
    nanosleep(&t, NULL);
    return NULL;
}

int main(int argc, char * argv[]) {
    int db = 0;
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
    if (type == 1) {
        qsort(v, cur_pos, sizeof(process), shortest_process_cmp);
        linkedlist *list = copy_array(v, cur_pos);
        printf("cp%d\n", db++);
        printf("%d\n", list->size);
        while(list->size > 0) {
            printf("%s\n", (list->header->val)->name);
            pop(list);
        }
        for(int i = 0; i < cur_pos; i++) {
            void *pt = &(v[i].dt);
            pthread_create(v[i].thread, NULL, t_func, pt);
            pthread_join(*(v[i].thread), NULL);
        }
    }
    if (type == 3) {
        qsort(v, cur_pos, sizeof(process), highest_priority_cmp);
        for(int i = 0; i < cur_pos; i++) {
            void *pt = &(v[i].dt);
            pthread_create(v[i].thread, NULL, t_func, pt);
            pthread_join(*(v[i].thread), NULL);
        }
    }
    for (int i = 0; i < cur_pos; i++) {
	    fprintf (stderr, "%lf %lf %lf %s\n", v[i].t0, v[i].dt, v[i].deadline, v[i].name);
    }
    free_vector(v, &cur_pos, &cur_size);
}
