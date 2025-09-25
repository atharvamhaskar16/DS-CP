#include <stdio.h>
#include <stdlib.h>
#include "slots.h"

void slots_init(Slot slots[], int n) {
    for (int i=0;i<n;i++){ slots[i].ev = NULL; slots[i].timeLeft = 0; }
}

int slots_allocate(Slot slots[], int n, EV *ev, int currentTime) {
    for (int i=0;i<n;i++) {
        if (slots[i].ev == NULL) {
            slots[i].ev = ev;
            slots[i].timeLeft = ev->chargeNeeded;
            ev->startTime = currentTime;
            return i;
        }
    }
    return -1;
}

int slots_tick(Slot slots[], int n, EV *completed[], int currentTime) {
    int c = 0;
    for (int i=0;i<n;i++) {
        if (slots[i].ev) {
            slots[i].timeLeft--;
            if (slots[i].timeLeft <= 0) {
                EV *f = slots[i].ev;
                f->finishTime = currentTime + 1;
                completed[c++] = f;
                slots[i].ev = NULL;
                slots[i].timeLeft = 0;
            }
        }
    }
    return c;
}

void slots_print(Slot slots[], int n) {
    for (int i=0;i<n;i++) {
        if (slots[i].ev)
            printf("Slot %d: %s (left=%d)  ", i+1, slots[i].ev->id, slots[i].timeLeft);
        else
            printf("Slot %d: EMPTY  ", i+1);
    }
    printf("\n");
}
