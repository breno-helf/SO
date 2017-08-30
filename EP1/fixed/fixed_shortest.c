#include "shortest.h"

/*
  It pushes each process into the heap once it gets
  to the processor. Then choose the shortest one
  and run it until the end.
*/


void shortest(FILE * output, process * v, int n) {
    int cur = 0;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    Heap H = heap_start();
    pthread_mutex_t * main_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(main_mutex, NULL);
    
    while (cur < n || heap_empty(H) == 0) {
	double cur_time = get_time(start_time);
	
	while (cur < n && cur_time >= v[cur].t0) {
	    heap_push(H, v[cur].dt, &v[cur]);
	    event("Processo da linha %d (%s) entrou no sistema\n",v[cur].id, v[cur].name); 
	    v[cur].main_mutex = main_mutex;
	    create_thread(&v[cur]);
	    cur++;
	}

	if (heap_empty(H) == 0) {
	    process * p = heap_top(H);
	    p->main_mutex = main_mutex;
	    event("Processo %s (%d) começou a usar a CPU\n", p->name, p->id);
	    p->quantum_num = 10 * (p->dt) + 5;
	    while (p->done == 0) {
		pthread_mutex_unlock(p->thread_mutex);
		pthread_mutex_lock(p->thread_mutex);
	    }
	    event("Processo %s (%d) liberou a CPU\n", p->name, p->id);

	    event("Processo linha %d (%s) terminou\n", p->id, p->name);	    
	    cur_time = get_time(start_time);
	    event("%s %lf %lf\n", p->name, cur_time, cur_time - p->t0);
	    fprintf(output, "%s %lf %lf\n", p->name, cur_time, cur_time - p->t0); 		    
	    heap_pop(H);
	}
    }

    heap_free(H);
    
    event("%d\n", 0);
    fprintf(output, "%d\n", 0);
}
