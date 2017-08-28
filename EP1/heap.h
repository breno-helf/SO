#include <stdio.h>
#include <stdlib.h>
x
#define MAX_SZ 1123
#define ST_SZ 2

/* Min Heap */

typedef struct {
    double val;
    void * key;
} node;

typedef struct {
    node ** v;
    int cur_size;
    int cur_pos;
} heap;

typedef heap * Heap;

Heap heap_start();

void heap_free(Heap H);

void heap_push(Heap H, double val, void * key);

void * heap_top(Heap H);

void heap_pop(Heap H);

void heap_go_up(Heap H);

void heap_go_down(Heap H);

void heap_swap(Heap H, int a, int b);
