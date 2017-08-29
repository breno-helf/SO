#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "process.h"

typedef struct node node;

struct node {
    process *val;
    node *next;
};

typedef struct{
    node *header;
    node *tail;
    int size;
} queue_struct;

typedef queue_struct * Queue;

Queue copy_array(process *array, int cur_pos);

Queue create_queue();

node *create_node(process *val);

process * front(Queue queue);

int queue_size(Queue queue);

void push(process *val, Queue queue);

void pop(Queue queue);

void free_queue(Queue queue);

/* Redirect the front of the queue to the end
   of the queue */

void to_tail(Queue queue);

#endif
