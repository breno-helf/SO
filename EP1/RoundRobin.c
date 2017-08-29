#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int db;
float total, goal;
pthread_mutex_t m_lock;
pthread_mutex_t t_lock;

void *t_func(void *arg) {
    float secs = 0.5;
    struct timespec t;
    t.tv_sec = (int) secs;
    secs -= t.tv_sec;
    t.tv_nsec = secs * 1000000000;
    while (total < goal) {
        pthread_mutex_lock(&t_lock);
        nanosleep(&t, NULL);
        total += secs;
        printf("sleep %f\n", total);
        pthread_mutex_unlock(&m_lock);
    }
    return NULL;
}

int main() {
    struct timespec pause;
    pause.tv_sec = 0;
    pause.tv_nsec = 0.1 * 1000000000;
    pthread_mutex_init(&m_lock, NULL);
    pthread_mutex_init(&t_lock, NULL);
    db = 0;
    pthread_t *thread;
    total = 0.0;
    goal = 1.7;
    thread = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_mutex_lock(&t_lock);
    pthread_create(thread, NULL, t_func, NULL);
    while (total < goal) {
        pthread_mutex_lock(&m_lock);
        pthread_mutex_unlock(&t_lock);
        //pthread_mutex_unlock(&m_lock);
        //nanosleep(&pause, NULL);
        printf("rodou\n");
    }
    pthread_join(*(thread), NULL);
    printf("CheckPoint%d\n", db++);
    return 0;
}