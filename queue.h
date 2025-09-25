#ifndef QUEUE_H
#define QUEUE_H

#include "ev.h"

typedef struct QNode {
    EV *ev;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front;
    QNode *rear;
    int size;
} Queue;

void queue_init(Queue *q);
int queue_is_empty(Queue *q);
void queue_enqueue(Queue *q, EV *ev);
EV* queue_dequeue(Queue *q);
int queue_size(Queue *q);
void queue_print(Queue *q);

#endif
