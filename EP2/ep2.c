/*
* * Breno Helfstein Moura       NUSP: 9790972
* * Lucas Daher                 NUSP: 8991769
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "event.h"
#include "track.h"
#include "cyclist.h"

int min (int a, int b) {
    return (a < b) ? a : b;
}

Cyclist ** Cyclists;
Track ** Pista;
int track_size;
int cyclists_num;
int laps_num;
int running;
int checkpoint;
int lucky;
double sim_time;
pthread_mutex_t * run_mutex;
pthread_mutex_t * checkpoint_mutex;

void try_break (Cyclist * C) {
    int rnd = rand() % 10;
    if (rnd == 0) {
	pthread_mutex_lock(run_mutex);
	if (running > 5) {
	    running--;
	    pthread_cancel(*(C->thread));
	    C->broken = 1;
	    printf("The cyclist %d has just broken at %lf\n", C->id, C->cur_time); 
	}
	pthread_mutex_unlock(run_mutex);
    }
}

void * ciclista(void * ptr) {
    Cyclist * C = (Cyclist *) ptr;
    double dist = 0;
    C->cur_speed = 30;
    
    while (C->cur_lap < laps_num) {	
	C->cur_time += sim_time;
	
	
	
	if (sim_time == 0.06) {
	    dist += (C->cur_speed == 30) ? .5 : 1;
	} else if (sim_time == 0.02) {
	    if (C->cur_speed == 90)
		dist += .5;
	    else if (C->cur_speed == 60)
		dist += 1.0/3.0;
	    else if (C->cur_speed == 30)
		dist += 1.0/6.0;
	}

	if (dist >= 1.0) {
	    /* Anda pra frente */
	    C->blocks++;
	    dist = 0;
	}

	if (dist == 0 && C->i == 0) {
	    int rnd = rand() % 10 + 1;
	    C->cur_lap++;
	    
	    if (C->cur_speed == 30) {
		if (rnd <= 7) C->cur_speed = 60;
		else C->cur_speed = 30;
	    } else if (C->cur_speed == 60) {
		if (rnd <= 5) C->cur_speed = 60;
		else C->cur_speed = 30;
	    }

	    if (C->cur_lap % 15 == 0) try_break(C);

	    pthread_mutex_lock(checkpoint_mutex);
	    if (C->cur_lap % 10 == 0 &&
		C->cur_lap / 10 > checkpoint) {
		checkpoint++;
	    }
	    if (laps_num - C->cur_lap == 2
		&& lucky == 0) {

		/* Sortear o cara cm 90 */
	    }
	    
	    pthread_mutex_unlock(checkpoint_mutex);

	    
	}
	
	C->arrive = 1;
	while (C->cont == 0);
	C->cont = 0;
    }
    pthread_mutex_lock(run_mutex);
    running--;
    C->finished = 1;
    pthread_mutex_unlock(run_mutex);
    
}

int main(int argc, char * argv[]) {
    /*
      d = Track size (in meters)
      v = Number of Circuits
      n = Number of Ciclists
    */
    int d, v, n;
    int i, j, q;
    
    srand(time(NULL));
    
    if (argc < 4) {
	fprintf(stderr, "Fatal error: Not enough arguments\n");
	return -1;
    }
    
    d = atoi(argv[1]);
    n = atoi(argv[2]);
    v = atoi(argv[3]);

    if (d < 250) {
	fprintf(stderr, "Track Size must be greater or equal than 250\n");
	return -1;
    }

    if (n <= 5 || n > 5 * d) {
	fprintf(stderr, "Number of Ciclists must be between 6 and 5 * Track_Size, inclusive\n");
	return -1;
    }

    if (v % 20 != 0) {
	fprintf(stderr, "Number of circuits must be divisible by 20\n");
	return -1;
    }

    /*
      Turn on the debug (event) log
    */
    if (argc > 4 && strcmp(argv[4], "d") == 0) {
	event(NULL);
    }    

    
    /*
      Initializing Variables
    */
    track_size = d;
    cyclists_num = n;
    laps_num = v;
    run_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(run_mutex, NULL);  
    sim_time = 0.06;
    running = cyclists_num;

    /*
      Creating Track
    */    
    Pista = track_create(track_size);
    Cyclists = (Cyclist **) malloc (sizeof(Cyclist *) * cyclists_num);
    q = 0;
    for (i = 0; i < track_size && q < cyclists_num; i++) {
	for (j = 0; j < 10 && q < cyclists_num; j++) {
	    Cyclists[q] = cyclist_create(q, i, j);
	    track_arriving_cyclist(Pista, i, j, Cyclists[q]);
	    q++;
	}
    }

    /* Creating Threads */    
    for (i = 0; i < cyclists_num; i++) {
	pthread_create(Cyclists[i]->thread, NULL, ciclista, (void *) Cyclists[i]);    
    }
    
    /* Coordinator */
    while (running > 0) {
	fprintf(stderr, "Running %d\n", running);
	for (i = 0; i < cyclists_num; i++) {
	    if (Cyclists[i]->finished || Cyclists[i]->broken)
		continue;
	    else {
		while (Cyclists[i]->arrive == 0 && Cyclists[i]->finished == 0 && Cyclists[i]->broken == 0);
		Cyclists[i]->arrive = 0;
	    }
	}

	for (i = 0; i < cyclists_num; i++) {
	    if (Cyclists[i]->finished || Cyclists[i]->broken)
		continue;
	    else {
		Cyclists[i]->cont = 1;
	    }
	}
    }

    return 0;
}
