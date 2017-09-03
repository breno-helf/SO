#include "roundrobin.h"

void round_robin(FILE * output, process * v, int n) {
    int cur = 0;
    int context_change = 0;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    Queue Q = create_queue();
    process * last = NULL;
    int deadlines_lost = 0;

    while (cur < n || queue_size(Q) > 0) {
	double cur_time = get_time(start_time);
	
	while (cur < n && cur_time >= v[cur].t0) {
	    push(&v[cur], Q);
	    event("Processo da linha %d (%s) entrou no sistema\n",v[cur].id, v[cur].name); 
	    create_thread(&v[cur]);
	    cur++;
	}

	if (queue_size(Q) > 0) {
	    process * p = front(Q);
	    if (p != last && last != NULL && last->done == 0) context_change++;
	    last = p;
	    event("Processo %s (%d) começou a usar a CPU\n", p->name, p->id);
		    
	    p->quantum_num = 1;
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
		pop(Q);
	    } else to_tail(Q);
	}
    }

    free_queue(Q);
    
    event("%d\n", context_change);
    fprintf(output, "%d\n", context_change);
}
    
