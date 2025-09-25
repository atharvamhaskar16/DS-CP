#include <stdio.h>
#include <string.h>
#include "pq.h"

/* Priority formula weights (tunable) */
static int W_BATTERY = 2;   // battery weight
static int W_WAIT = 1;      // waiting time weight
static int PREMIUM_BONUS = 50;

/* compute priority for an EV given current time */
static int compute_priority(EV *e, int currentTime) {
    int wait = currentTime - e->arrivalTime;
    if (wait < 0) wait = 0;
    int score = (100 - e->battery) * W_BATTERY + wait * W_WAIT + (e->userType ? PREMIUM_BONUS : 0);
    return score;
}

void pq_init(PQueue *pq) {
    pq->size = 0;
    memset(pq->heap, 0, sizeof(pq->heap));
}

static void swap_ptr(EV **a, EV **b) {
    EV *t = *a; *a = *b; *b = t;
}

void pq_insert(PQueue *pq, EV *ev, int currentTime) {
    if (pq->size + 1 >= PQ_CAPACITY) {
        printf("PQ full, cannot insert %s\n", ev->id);
        return;
    }
    pq->heap[++pq->size] = ev;
    int i = pq->size;
    while (i > 1) {
        int parent = i / 2;
        if (compute_priority(pq->heap[i], currentTime) > compute_priority(pq->heap[parent], currentTime)) {
            swap_ptr(&pq->heap[i], &pq->heap[parent]);
            i = parent;
        } else break;
    }
}

EV* pq_extract_max(PQueue *pq, int currentTime) {
    if (pq->size == 0) return NULL;
    EV *top = pq->heap[1];
    pq->heap[1] = pq->heap[pq->size--];
    int i = 1;
    while (1) {
        int left = 2*i, right = 2*i+1, largest = i;
        if (left <= pq->size && compute_priority(pq->heap[left], currentTime) >
            compute_priority(pq->heap[largest], currentTime)) largest = left;
        if (right <= pq->size && compute_priority(pq->heap[right], currentTime) >
            compute_priority(pq->heap[largest], currentTime)) largest = right;
        if (largest != i) {
            swap_ptr(&pq->heap[i], &pq->heap[largest]);
            i = largest;
        } else break;
    }
    return top;
}

int pq_is_empty(PQueue *pq) { return pq->size == 0; }

void pq_rebuild(PQueue *pq, int currentTime) {
    for (int i = pq->size/2; i >= 1; i--) {
        int idx = i;
        while (1) {
            int left = 2*idx, right = 2*idx+1, largest = idx;
            if (left <= pq->size && compute_priority(pq->heap[left], currentTime) >
                compute_priority(pq->heap[largest], currentTime)) largest = left;
            if (right <= pq->size && compute_priority(pq->heap[right], currentTime) >
                compute_priority(pq->heap[largest], currentTime)) largest = right;
            if (largest != idx) {
                swap_ptr(&pq->heap[idx], &pq->heap[largest]);
                idx = largest;
            } else break;
        }
    }
}

void pq_print(PQueue *pq, int currentTime) {
    if (pq->size == 0) { printf("PQ: empty\n"); return; }
    printf("PQ (top 6): ");
    int limit = pq->size < 6 ? pq->size : 6;
    for (int i=1;i<=limit;i++) {
        printf("[%s:%d] ", pq->heap[i]->id, compute_priority(pq->heap[i], currentTime));
    }
    printf("\n");
}
