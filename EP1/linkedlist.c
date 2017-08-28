#include "linkedlist.h"

linkedlist *copy_array(process *array, int cur_pos) {
    linkedlist *list = create_list();
    for (int i = 0; i < cur_pos; i++) {
        node *n = create_node(&array[i]);
        push(n, list);
    }
    return list;
    
    /*list->size = cur_pos;
    if (cur_pos == 0) {
        list->header = NULL;
        return list;
    }
    list->header = (node *) malloc (sizeof (node));
    node *curr = list->header;
    curr->val = &array[0];
    for (int i = 0; i < cur_pos; i++) {
        node *n = (node*) malloc (sizeof(node));
        n->val = &array[i];
        curr->next = n;
        curr = curr->next;
    }
    curr->next = NULL;
    return list;*/
}

linkedlist *create_list() {
    linkedlist *q = (linkedlist *) malloc(sizeof(linkedlist));
    q->size = 0;
    q->header = NULL;
    q->tail = NULL;
    return q;
}

node *create_node(process *val) {
    node *n = (node*) malloc (sizeof(node));
    n->val = val;
    n->next = NULL;
    return n;
}

void push(node *n, linkedlist *queue) {
    queue->size++;
    if (queue->size == 1) {
        n->next = NULL;
        queue->header = n;
        queue->tail = n;
        return;
    }
    queue->tail->next = n;
    queue->tail = queue->tail->next;
    queue->tail->next = NULL;
}

void pop(linkedlist *queue) {
    if (queue->size == 0) return;
    node *temp = queue->header;
    queue->header = queue->header->next;
    free(temp);
    queue->size--;
    if (queue->size == 0) queue->tail = NULL;
}

void free_list(linkedlist *queue) {
    node *curr, *next;
    curr = queue->header;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void to_tail(linkedlist *queue) {
    if (queue->size <= 1) return;
    node *temp = queue->header;
    queue->header = queue->header->next;
    queue->tail->next = temp;
    queue->tail = queue->tail->next;
    queue->tail->next = NULL;
}