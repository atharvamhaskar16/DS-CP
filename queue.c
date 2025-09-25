#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void queue_init(Queue *q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

int queue_is_empty(Queue *q) {
    return q->front == NULL;
}

void queue_enqueue(Queue *q, EV *ev) {
    QNode *n = (QNode*)malloc(sizeof(QNode));
    n->ev = ev;
    n->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
    q->size++;
}

EV* queue_dequeue(Queue *q) {
    if (queue_is_empty(q)) return NULL;
    QNode *t = q->front;
    EV *ev = t->ev;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(t);
    q->size--;
    return ev;
}

int queue_size(Queue *q) {
    return q->size;
}

void queue_print(Queue *q) {
    QNode *cur = q->front;
    printf("Queue (front -> rear): ");
    while (cur) {
        printf("[%s|%d%%|%s] ", cur->ev->id, cur->ev->battery, cur->ev->userType ? "P" : "N");
        cur = cur->next;
    }
    printf("\n");
}
