#include "process.h"

double max(double a, double b) {
    return (a > b) ? a : b;
}

int first_coming_cmp(const void * p1, const void * p2) {
    double t1 = ((process * )p1)->t0;
    double t2 = ((process * )p2)->t0;
    if (t1 > t2) return 1;
    if (t1 < t2) return -1;
    return 0;
}

process * build_process(int id, double t0, double dt, double deadline,
			char * name) {
    process * p;
    p = (process *) malloc(sizeof(process));
    p->done = 0;
    p->running = 0;
    p->id = id;
    p->t0 = t0;
    p->dt = dt;
    p->deadline = deadline;
    p->name = name;
    return p;
}
void start_vector(process ** v, int * cur_pos, int * cur_size,
		  int * complete_process, int * context_change) {
    *cur_pos = 0;
    *cur_size = START_SIZE;
    *complete_process = 0;
    *context_change = 0;
    
    *v = (process *) malloc(sizeof(process) * START_SIZE);
}

void double_size(process ** v, int * cur_size) {
    process * temp = * v;
    int i, old_size = * cur_size;
    *cur_size = (old_size) * 2;
    *v = (process *) malloc(sizeof(process) * (*cur_size));
    
    for (i = 0; i < old_size; i++) {
	(*v)[i] = temp[i];
    }
    free(temp);
}

void push_process(process ** v, int * cur_pos, int * cur_size,
		  process p) {

    int i = *cur_pos;
    int n = *cur_size;
    
    if (i == n) {
	double_size(v, cur_size);
    }

    int name_size = strlen(p.name);

    (*v)[i].running = p.running;
    (*v)[i].done = p.done;
    (*v)[i].id = p.id;
    (*v)[i].t0 = p.t0;
    (*v)[i].dt = p.dt;
    (*v)[i].deadline = p.deadline;
    (*v)[i].thread_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    (*v)[i].main_mutex = NULL;
    
    (*v)[i].thread = (pthread_t *) malloc(sizeof(pthread_t));
    
    (*v)[i].name = (char *) malloc(sizeof(char) * (name_size + 1));

    strcpy((*v)[i].name, p.name);
    
    (*cur_pos) = i + 1;    
}

void free_vector(process *v, int * cur_pos, int * cur_size) {
    int i;
    int n = *cur_pos;

    for (i = 0; i < n; i++)
	free(v[i].name);
    free(v);
    *cur_pos = 0;
    *cur_size = 0;
}

void read_trace(FILE * trace, process ** v, int * cur_pos,
		int * cur_size) {
    char *name;
    double t0, dt, deadline, i = 0;
    name = (char *) malloc(sizeof(char) * MAX_SIZE);
    while (fscanf(trace, "%lf %lf %lf %s", &t0, &dt, &deadline, name) != EOF) {
	process * p;
	p = build_process(i, t0, dt, deadline, name);
	push_process(v, cur_pos, cur_size, * p);
	i++;
	free(p);
    }
    free(name);
}

void create_thread(process * p) {
    pthread_mutex_init(p->thread_mutex, NULL);
    pthread_mutex_lock(p->thread_mutex);
    pthread_create(p->thread, NULL, run_process, (void *) p);
}

void * run_process(void * arg) {
    double cur = 0;
    process * p = (process *)(arg);
    p->running = 1;
    while (cur < p->dt) {
	pthread_mutex_lock(p->thread_mutex);
	struct timespec t;
	t.tv_sec = (int) QUANTUM;
	t.tv_nsec = ((double)QUANTUM - t.tv_sec) * 1000000000;
	cur += QUANTUM;
	nanosleep(&t, NULL);
	pthread_mutex_unlock(p->main_mutex);
    }  

    p->running = 0;
    p->done = 1;
    pthread_mutex_unlock(p->main_mutex);
    return NULL;
}
