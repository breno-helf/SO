#include "highestpriority.h"

int calc_quantum(process * p, double cur_time) {
    int ret = 20;
    if (p->deadline >= cur_time) {
	ret = (int)min((20.0 / (p->deadline - cur_time)), 10.0);
    } 

    return ret;
}

void highest_priority(FILE * output, process * v, int n) {
    int cur = 0;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    Heap H = heap_start();
    process * last = NULL;
    int context_change = 0;
    int deadlines_lost = 0;
    
    while (cur < n || heap_empty(H) == 0) {
	double cur_time = get_time(start_time);
	
	while (cur < n && cur_time >= v[cur].t0) {
	    heap_push(H, v[cur].deadline, &v[cur]);
	    event("Processo da linha %d (%s) entrou no sistema\n",v[cur].id, v[cur].name); 
	    create_thread(&v[cur]);
	    cur++;
	}

	if (heap_empty(H) == 0) {
	    process * p = heap_top(H);
	    if (p != last && last != NULL && last->done == 0) context_change++;
	    last = p;
	    int lim = calc_quantum(p, cur_time);
	    event("Processo %s (%d) começou a usar a CPU\n", p->name, p->id);
	    p->quantum_num = lim;
	    pthread_mutex_unlock(p->thread_mutex);
	    while (p->quantum_num > 0 && p->done == 0);
	    pthread_mutex_lock(p->thread_mutex);
	    
	    event("Processo %s (%d) liberou a CPU\n", p->name, p->id);
	    cur_time = get_time(start_time);
	    if (p->done == 1) {
		if (cur_time > p->deadline) deadlines_lost++;
		event("Processo linha %d (%s) terminou\n", p->id, p->name);
		event("%s %lf %lf\n", p->name, cur_time, cur_time - p->t0);
		fprintf(output, "%s %lf %lf\n", p->name, cur_time, cur_time - p->t0);
		
		heap_pop(H);
	    }
	}
    }

    heap_free(H);
    
    event("%d\n", context_change);
    fprintf(output, "%d\n", context_change);
}
