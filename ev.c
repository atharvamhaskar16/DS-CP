#include <stdlib.h>
#include <string.h>
#include "ev.h"

EV* ev_create(const char *id, int battery, int userType, int arrivalTime, int chargeNeeded) {
    EV *e = (EV*)malloc(sizeof(EV));
    if (!e) return NULL;
    strncpy(e->id, id, ID_LEN-1);
    e->id[ID_LEN-1] = '\0';
    e->battery = battery;
    e->userType = userType;
    e->arrivalTime = arrivalTime;
    e->waitingTime = 0;
    e->priorityScore = 0;
    e->chargeNeeded = chargeNeeded;
    e->startTime = -1;
    e->finishTime = -1;
    return e;
}

void ev_free(EV *e) {
    if (e) free(e);
}
