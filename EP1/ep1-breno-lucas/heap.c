#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap heap_start() {
    Heap H = (Heap) malloc(sizeof(heap));
    H->cur_size = ST_SZ;
    H->cur_pos = 0;
    H->v = (heap_node **) malloc(sizeof(heap_node *) * ST_SZ);
    return H;
}

int heap_empty(Heap H) {
    return (H->cur_pos == 0) ? 1 : 0;
}

void heap_free(Heap H) {
    while(heap_empty(H) == 0) heap_pop(H);
    free(H);
}

void heap_double(Heap H) {
    heap_node ** temp = H->v;
    int i, old_size = H->cur_size;
    H->cur_size *= 2;

    H->v = (heap_node **) malloc(sizeof(heap_node *) * H->cur_size);

    for (i = 0; i < old_size; i++)
	H->v[i] = temp[i];
    free(temp);    
}

void heap_push(Heap H, double val, process * key) {
    heap_node * N = (heap_node *) malloc(sizeof(heap_node));

    
    N->val = val;
    N->key = key;
    
    if (H->cur_pos == H->cur_size) heap_double(H);
    H->v[H->cur_pos] = N;

    heap_swim(H);

    H->cur_pos++;    
}

process * heap_top(Heap H) {
    return H->v[0]->key;
}

void heap_pop(Heap H) {
    free(H->v[0]);
    H->v[0] = H->v[--H->cur_pos];
    heap_dive(H);
}

void heap_swap(Heap H, int a, int b) {
    heap_node * temp = H->v[a];
    H->v[a] = H->v[b];
    H->v[b] = temp;
}

void heap_swim(Heap H) {
    int i = H->cur_pos;

    while (i > 0 && H->v[i]->val < H->v[(i - 1) / 2]->val) {
	heap_swap(H, i, (i - 1) / 2);
	i = (i - 1) / 2;
    }
}

void heap_dive(Heap H) {
    int i = 0;
    int sz = H->cur_pos;
    
    while (1) {
	int down = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < sz && H->v[down]->val > H->v[left]->val)
	    down = left;

	if (right < sz && H->v[down]->val > H->v[right]->val)
	    down = right;

	if (down == i) break;

	heap_swap(H, down, i);

	i = down;
    }
}
