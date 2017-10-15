/*
* * Breno Helfstein Moura       NUSP: 9790972
* * Lucas Daher                 NUSP: 8991769
*/

#ifndef CYCLIST_H
#define CYCLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Cyclist {
    int id;
    int i;
    int j;
    int start;
    int seen;
    int cur_lap;
    int cur_speed;
    int my_speed;
    int points;
    int blocks;
    char finished;
    char broken;
    double cur_time;
    double dist;
    int cont;
    pthread_mutex_t * cont_mutex;
    pthread_cond_t * cont_cond;
    int arrive;
    pthread_mutex_t * arrive_mutex;
    pthread_cond_t * arrive_cond;
    pthread_t * thread;
    int voltas_vantagem;
} Cyclist;

Cyclist * cyclist_create(int id, int i, int j);

int cmp_blocks(const void * a, const void * b);

int cmp_points(const void * a, const void * b);

void cyclist_destroy(Cyclist * C);

#endif
