/*
* * Breno Helfstein Moura       NUSP: 9790972
* * Lucas Daher                 NUSP: 8991769
*/

#ifndef TRACK_H
#define TRACK_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cyclist.h"

typedef struct Track {
    pthread_mutex_t * mutex;
    Cyclist * cyclist;
} Track; 

/*
  Create the track with size equal len
*/
Track ** track_create(int len);

/*
  Cyclist C arrive in the position i, j of the track T
*/
void track_arriving_cyclist(Track ** T, int i, int j, Cyclist * C);

/*
  The Cyclist that was in i, j leave its Track
*/
void track_leaving_cyclist(Track ** T, int i, int j);

/*
  Mutex to read position i, j
*/
Cyclist * reading_position(Track ** T, int i, int j);

/*
  free Mutex to read position i, j
*/
void stop_reading_position(Track ** T, int i, int j);


/*
  Print the current track and the current time
*/
void track_print(Track ** T, int len, double cur_time);

/*
  Free the memory of Track
*/
void track_destroy(Track ** T, int len);

#endif
