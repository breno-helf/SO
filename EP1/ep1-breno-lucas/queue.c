#include "queue.h"
#include <assert.h>

Queue copy_array(process *array, int cur_pos) {
    Queue list = create_queue();
    for (int i = 0; i < cur_pos; i++) {
        push(&array[i], list);
    }
    return list;
}

Queue create_queue() {
    Queue q = (Queue) malloc(sizeof(Queue));
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

process * front(Queue  queue) {
    return queue->header->val;
}

int queue_size(Queue  queue) {
    return queue->size;
}

void push(process *val, Queue queue) {
    node *n = create_node(val);
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

void pop(Queue queue) {
    if (queue->size == 0) return;
    node *temp = queue->header;
    queue->header = queue->header->next;
    free(temp);
    queue->size--;
    if (queue->size == 0) queue->tail = NULL;
}

void free_queue(Queue queue) {
    node *curr, *next;
    curr = queue->header;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void to_tail(Queue queue) {
    if (queue->size <= 1) return;
    node *temp = queue->header;
    queue->header = queue->header->next;
    queue->tail->next = temp;
    queue->tail = queue->tail->next;
    queue->tail->next = NULL;
}


/* Unit testing */
/*
int main() {
    Queue Q = create_queue();

    push(NULL, Q);
    push(NULL, Q);

    assert(queue_size(Q) == 2);

    pop(Q);

    assert(queue_size(Q) == 1);

    assert(front(Q) == NULL);

    pop(Q);

    assert(queue_size(Q) == 0);

    push(NULL, Q);
    push(NULL, Q);

    assert(queue_size(Q) == 2);

    pop(Q);

    assert(queue_size(Q) == 1);

    assert(front(Q) == NULL);

    pop(Q);

}
*/
