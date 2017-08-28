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
} linkedlist;

linkedlist *copy_array(process *array, int cur_pos);

linkedlist *create_list();

node *create_node(process *val);

void push(node *n, linkedlist *queue);

void pop(linkedlist *queue);

//void free_element(node *n);

void free_list(linkedlist *queue);

void to_tail(linkedlist *queue);