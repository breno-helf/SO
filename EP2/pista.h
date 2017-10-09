/*
* * Breno Helfstein Moura       NUSP: 9790972
* * Lucas Daher                 NUSP: 8991769
*/

#ifndef PISTA_H
#define PISTA_H

#include <stdio.h>
#include <stdlib.h>
#include "ciclist.h"

typedef struct Track {
    pthread_mutex_t * mutex;
    int sz;
    cilcist * ciclist;
} Track;



#endif
