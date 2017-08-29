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
	    event("[%lf] Processo %d entrou no sistema\n", cur_time, v[cur].id);
	    cur++;
	}

	if (heap_empty(H) == 0) {
	    process * p = heap_top(H);
	    /* Rodar processo do topo (p) */
	    heap_pop(H);
	}
    }
}
    
