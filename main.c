#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ev.h"
#include "queue.h"
#include "pq.h"
#include "hash.h"
#include "set.h"
#include "bst.h"
#include "stack.h"
#include "slots.h"

#define NUM_SLOTS 3

int main() {
    /* init modules */
    hash_init();
    set_init();
    stack_init();

    Queue premiumQ, normalQ;
    queue_init(&premiumQ);
    queue_init(&normalQ);

    PQueue pq; pq_init(&pq);

    Slot slots[NUM_SLOTS]; slots_init(slots, NUM_SLOTS);

    BSTNode *bstRoot = NULL;

    /* Hardcoded arrivals (id, battery, userType, arrivalTime, chargeNeeded) */
    EV *arrivals[] = {
        ev_create("EV101", 20, 1, 0, 5),
        ev_create("EV102", 50, 0, 2, 3),
        ev_create("EV103", 10, 0, 3, 4),
        ev_create("EV104", 70, 1, 5, 6),
        ev_create("EV105", 15, 0, 6, 2),
        ev_create("EV106", 40, 0, 8, 3)
    };
    int numArrivals = sizeof(arrivals)/sizeof(arrivals[0]);

    int arrivalIndex = 0;
    int currentTime = 0;
    int servedCount = 0;
    int totalPremiumWait = 0, totalNormalWait = 0;

    printf("=== Phase 3 Simulation Start ===\n");

    while (1) {
        printf("\n--- Time %d ---\n", currentTime);

        /* arrivals that happen at this tick */
        while (arrivalIndex < numArrivals && arrivals[arrivalIndex]->arrivalTime == currentTime) {
            EV *e = arrivals[arrivalIndex++];
            printf("ARRIVAL: %s bat=%d%% type=%s needs=%d\n", e->id, e->battery, e->userType? "Premium":"Normal", e->chargeNeeded);
            /* enqueue in respective FIFO queue (for tracking if needed) */
            if (e->userType) queue_enqueue(&premiumQ, e);
            else queue_enqueue(&normalQ, e);
            /* insert in hash & bst for lookup/filter */
            hash_insert(e);
            bstRoot = bst_insert(bstRoot, e);
            /* insert into priority queue (eligible for allocation) */
            pq_insert(&pq, e, currentTime);
        }

        /* rebuild PQ to reflect waiting-time change */
        pq_rebuild(&pq, currentTime);

        /* allocate free slots from PQ (highest priority) */
        for (int s=0; s<NUM_SLOTS; s++) {
            if (slots[s].ev == NULL) {
                EV *candidate = NULL;
                /* Try to prefer premium FIFO: if premium queue has someone, and that EV is in PQ, allocate them first */
                if (!queue_is_empty(&premiumQ)) {
                    /* dequeue premium FIFO; then remove that specific EV from PQ by extracting until found */
                    EV *p = queue_dequeue(&premiumQ);
                    /* remove p from PQ by rebuilding temp list (simple but OK for small sim) */
                    EV *temp[ PQ_CAPACITY ];
                    int tp = 0;
                    while (!pq_is_empty(&pq)) {
                        EV *t = pq_extract_max(&pq, currentTime);
                        if (t && strcmp(t->id, p->id) != 0) temp[++tp] = t;
                        else { candidate = t; break; }
                    }
                    /* put back temp into pq */
                    for (int i=1;i<=tp;i++) pq_insert(&pq, temp[i], currentTime);
                    /* if candidate not found in PQ (unlikely), candidate will be p */
                    if (!candidate) candidate = p;
                } else {
                    /* normal path: just extract max from PQ */
                    candidate = pq_extract_max(&pq, currentTime);
                }

                if (candidate) {
                    int idx = slots_allocate(slots, NUM_SLOTS, candidate, currentTime);
                    if (idx >= 0) {
                        printf("ALLOC: Slot %d <- %s (start=%d wait=%d)\n", idx+1, candidate->id, candidate->startTime, candidate->waitingTime);
                        /* push undo action */
                        Action a; a.type = ACTION_ALLOC; a.slotIndex = idx; a.ev = candidate; a.prevTimeLeft = 0;
                        stack_push_undo(a);
                    } else {
                        /* no slot free (shouldn't reach) */
                        printf("No slot free for %s\n", candidate->id);
                    }
                }
            }
        }

        /* tick slots */
        EV *completed[NUM_SLOTS];
        int c = slots_tick(slots, NUM_SLOTS, completed, currentTime);
        for (int i=0;i<c;i++) {
            EV *f = completed[i];
            set_add(f->id);
            if (f->userType) totalPremiumWait += f->waitingTime;
            else totalNormalWait += f->waitingTime;
            servedCount++;
            printf("COMPLETE: %s finished at t=%d (wait=%d)\n", f->id, f->finishTime, f->waitingTime);
        }

        /* diagnostics */
        slots_print(slots, NUM_SLOTS);
        pq_print(&pq, currentTime);
        printf("Pending arrivals: %d (index %d/%d), served: %d\n", numArrivals - arrivalIndex, arrivalIndex, numArrivals, servedCount);

        /* termination: when all arrivals processed and no slots busy and pq empty */
        int slotsBusy = 0;
        for (int i=0;i<NUM_SLOTS;i++) if (slots[i].ev) slotsBusy = 1;
        if (arrivalIndex >= numArrivals && !slotsBusy && pq_is_empty(&pq)) {
            printf("\nAll done by time %d\n", currentTime+1);
            break;
        }

        currentTime++;
    }

    /* stats */
    printf("\n=== Simulation Summary ===\n");
    int premiumCount=0, normalCount=0;
    for (int i=0;i<numArrivals;i++) { if (arrivals[i]->userType) premiumCount++; else normalCount++; }
    if (premiumCount) printf("Avg wait Premium = %.2f\n", (double)totalPremiumWait / premiumCount);
    if (normalCount) printf("Avg wait Normal  = %.2f\n", (double)totalNormalWait / normalCount);

    printf("\nCompleted list:\n"); set_print_all();

    printf("\nLow battery filter (<30%%):\n"); bst_filter_below(bstRoot, 30);

    /* free EVs */
    for (int i=0;i<numArrivals;i++) ev_free(arrivals[i]);

    return 0;
}
