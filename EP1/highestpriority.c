#include "highestpriority.h"

int calc_quantum(process * p, double cur_time) {
    int ret = 100;
    if (p->deadline >= cur_time) {
	ret = (int)max((50.0 / (p->deadline - cur_time)), 10.0);
    } 

    printf("--> %d\n", ret);
    return ret;
}


void highest_priority(FILE * output, process * v, int n) {
    int cur = 0;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    Heap H = heap_start();
    pthread_mutex_t * main_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(main_mutex, NULL);
    process * last = NULL;
    int context_change = 0;
    
    while (cur < n || heap_empty(H) == 0) {
	double cur_time = get_time(start_time);
	
	while (cur < n && cur_time >= v[cur].t0) {
	    heap_push(H, v[cur].deadline, &v[cur]);
	    v[cur].main_mutex = main_mutex;
	    create_thread(&v[cur]);
	    cur++;
	}

	if (heap_empty(H) == 0) {
	    process * p = heap_top(H);
	    if (p != last && last != NULL) context_change++;
	    last = p;
	    int qtd = 0;
	    int lim = calc_quantum(p, cur_time);
	    pthread_mutex_unlock(p->main_mutex);
	    event("Processo %s (%d) começou a usar a CPU\n", p->name, p->id);	    
	    while (qtd < lim && p->done == 0) {
		pthread_mutex_lock(p->main_mutex);
		pthread_mutex_unlock(p->thread_mutex);
		qtd++;
	    }
	    event("Processo %s (%d) liberou a CPU\n", p->name, p->id);

	    if (p->done == 1) {
		cur_time = get_time(start_time);
		event("%s %lf %lf\n", p->name, cur_time, cur_time - p->t0);
		fprintf(output, "%s %lf %lf\n", p->name, cur_time, cur_time - p->t0);
		
		heap_pop(H);
	    }
	}
    }

    heap_free(H);
    
    event("%d\n", 0);
    fprintf(output, "%d\n", 0);
}
