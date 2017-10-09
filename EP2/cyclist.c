/*
* * Breno Helfstein Moura       NUSP: 9790972
* * Lucas Daher                 NUSP: 8991769
*/

#include <stdio.h>
#include <stdlib.h>
#include "cyclist.h"

Cyclist * cyclist_create(int id, int i, int j) {
    Cyclist * C = (Cyclist *) malloc(sizeof(Cyclist));
    C->id = id;
    C->i = i;
    C->j = j;
    C->start = C->seen = C->cur_speed = C->cur_lap = 0;
    C->blocks = C->points = C->finished = C->broken = 0;
    C->cur_time = 0.0;
    C->cont = 0;
    C->arrive = 0;
    C->thread = (pthread_t *) malloc(sizeof(pthread_t));
    return C;
}

int cmp_blocks(const void * a, const void * b) {
    Cyclist * A = (Cyclist *) a;
    Cyclist * B = (Cyclist *) b;

    if (A->blocks > B->blocks) return -1;
    if (A->blocks == B->blocks) return 0;
    if (A->blocks < B->blocks) return 1;

    return 0;
}

int cmp_points(const void * a, const void * b) {
    Cyclist * A = (Cyclist *) a;
    Cyclist * B = (Cyclist *) b;
    
    if (A->points > B->points) return -1;
    if (A->points == B->points) return 0;
    if (A->points < B->points) return 1; 

    return 0;
}