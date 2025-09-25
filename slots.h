#ifndef SLOTS_H
#define SLOTS_H

#include "ev.h"

typedef struct {
    EV *ev;       // NULL if free
    int timeLeft; // remaining ticks to finish
} Slot;

/* initialize slots array */
void slots_init(Slot slots[], int n);

/* allocate a free slot with EV*, return index or -1 */
int slots_allocate(Slot slots[], int n, EV *ev, int currentTime);

/* tick: decrement timeLeft, returns number of completions and fills completed[] with EV* */
int slots_tick(Slot slots[], int n, EV *completed[] , int currentTime);

/* print slots */
void slots_print(Slot slots[], int n);

#endif
