/*
* * Breno Helfstein Moura       NUSP: 9790972
* * Lucas Daher                 NUSP: 8991769
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "event.h"
#include "track.h"

Track ** track_create(int len) {
    Track ** T;
    int i, j;
    T = (Track **) malloc(sizeof(Track *) * len);
    for (i = 0; i < len; i++) {
	T[i] = (Track *) malloc(sizeof(Track) * 10);
	for (j = 0; j < 10; j++) {
	    T[i][j].mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	    pthread_mutex_init(T[i][j].mutex, NULL);
	}
    }
    return T;
}

void track_arriving_cyclist(Track ** T, int i, int j, Cyclist * C) {
    pthread_mutex_lock(T[i][j].mutex);
    assert(T[i][j].cyclist == NULL);
    T[i][j].cyclist = C;
}

void track_leaving_cyclist(Track ** T, int i, int j) {
    assert(T[i][j].cyclist != NULL);
    T[i][j].cyclist = NULL;
    pthread_mutex_unlock(T[i][j].mutex);
}

void track_print(Track ** T, int len, double cur_time) {
    int i, j;
    event("Current time: %lf\n", cur_time);
    event("Track: Empty positions are shown as -1\n");
    for (i = 0; i < len; i++) {
	for (j = 0; j < 10; j++) {
	    event("%2d ", (T[i][j].cyclist != NULL) ? T[i][j].cyclist->id : -1);
	}
	event("\n");
    }
    event("\n\n");
}

void track_destroy(Track ** T, int len) {
    int i, j;
    for (i = 0; i < len; i++) {
	for (j = 0; j < 10; j++) {
	    free(T[i][j].mutex);
	}
	free(T[i]);
    }
    free(T);
}
