#include "roundrobin.h"

/*
  It pushes each process into the heap once it gets
  to the processor. Then choose the shortest one
  and run it until the end.
*/


void round_robin(FILE * output, process * v, int n) {
    int cur = 0;
    int context_change = 0;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    Queue Q = create_queue();
    pthread_mutex_t * main_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(main_mutex, NULL);
    
    while (cur < n || queue_size(Q) > 0) {
	double cur_time = get_time(start_time);
	
	while (cur < n && cur_time >= v[cur].t0) {
	    push(&v[cur], Q);
	    event("Processo %d entrou no sistema em %lf\n", v[cur].id, cur_time);
	    cur++;
	}

	if (queue_size(Q) > 0) {
	    process * p = front(Q);
	    int qtd = 0;
	    p->main_mutex = main_mutex;
	    create_thread(p);
	    pthread_mutex_unlock(p->main_mutex);
	    event("Processo %s (%d) começou a usar a CPU\n", p->name, p->id);
	    while (qtd < 1) {
		pthread_mutex_lock(p->main_mutex);
		pthread_mutex_unlock(p->thread_mutex);
		qtd++;
	    }

	    event("Processo %s (%d) liberou a CPU\n", p->name, p->id);
	    cur_time = get_time(start_time);

	    if (p->done == 1) {
		event("%s %lf %lf\n", p->name, cur_time, cur_time - p->t0);
		fprintf(output, "%s %lf %lf\n", p->name, cur_time, cur_time - p->t0);
		pop(Q);
	    } else to_tail(Q);

	    if (queue_size(Q) > 0 && front(Q) != p) context_change++; 
	}
    }

    event("%d\n", context_change);
    fprintf(output, "%d\n", context_change);
}
    
