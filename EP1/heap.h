#ifndef HEAP
#define HEAP

#include <stdio.h>
#include <stdlib.h>
#include "process.h"

#define MAX_SZ 1123
#define ST_SZ 2

/* Min Heap */

typedef struct {
    double val;
    process * key;
} heap_node;

typedef struct {
    heap_node ** v;
    int cur_size;
    int cur_pos;
} heap;

typedef heap * Heap;

Heap heap_start();

int heap_empty(Heap H);

void heap_free(Heap H);

void heap_push(Heap H, double val, process * key);

process * heap_top(Heap H);

void heap_pop(Heap H);

/* try to promote the last node */
void heap_swim(Heap H);

/* try to unpromote the first node */
void heap_dive(Heap H);

void heap_swap(Heap H, int a, int b);

#endif
