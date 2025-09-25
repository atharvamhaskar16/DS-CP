#ifndef PQ_H
#define PQ_H

#include "ev.h"

#define PQ_CAPACITY 512

typedef struct {
    EV *heap[PQ_CAPACITY]; // 1-based indexing (heap[1] is top)
    int size;
} PQueue;

/* initialize */
void pq_init(PQueue *pq);

/* insert (uses currentTime to compute priority inside PQ) */
void pq_insert(PQueue *pq, EV *ev, int currentTime);

/* extract max by currentTime-based priority */
EV* pq_extract_max(PQueue *pq, int currentTime);

/* is empty */
int pq_is_empty(PQueue *pq);

/* rebuild heap order (call if many priorities changed) */
void pq_rebuild(PQueue *pq, int currentTime);

/* print top few */
void pq_print(PQueue *pq, int currentTime);

#endif
