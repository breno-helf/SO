#include "shortest.h"

/*
  It pushes each process into the heap once it gets
  to the processor. Then choose the shortest one
  and run it until the end.
*/


void shortest(FILE * output, process * v, int n) {
    int cur = 0;
    clock_t start_time = clock();
    Heap H = heap_start();
    
    while (cur < n || heap_empty(H) == 0) {
	double cur_time = get_time(start_time, clock());
	
	while (cur < n && cur_time >= v[cur].t0) {
	    heap_push(H, v[cur].dt, &v[cur]);
	    event("Processo %d entrou no sistema em %lf\n", v[cur].id, cur_time);
	    cur++;
	}

	if (heap_empty(H) == 0) {
	    process * p = heap_top(H);	    
	    create_thread(p);
	    pthread_mutex_unlock(p->mutex);
	    while (p->done == 0);
	    cur_time = get_time(start_time, clock());
	    event("%s %lf %lf\n", p->name, cur_time, cur_time - p->t0);
	    fprintf(output, "%s %lf %lf\n", p->name, cur_time, cur_time - p->t0); 		    
	    heap_pop(H);
	}
    }

    event("%d\n", 0);
    fprintf(output, "%d\n", 0);
}
    
