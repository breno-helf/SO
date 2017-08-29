#include<stdio.h>
#include<time.h>

void *t_func(void *arg) {
    float secs = *((float*) arg);
    struct timespec t;
    t.tv_sec = (int) secs;
    secs -= t.tv_sec;
    t.tv_nsec = secs * 1000000000;
    nanosleep(&t, NULL);
    return NULL;
}

void ShortestJobFirst (&v, &cur_pos, &cur_size, &complete_process, &context_change) {
    for(int i = 0; v[i] != NULL; i++) {
        void *pt = v[i]->dt;
        pthread_create(v[i]->thread, NULL, t_func, pt);
        pthread_join(v[i]->thread, NULL);
    }
}