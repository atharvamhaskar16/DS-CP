#ifndef EV_H
#define EV_H

#define ID_LEN 20

typedef struct {
    char id[ID_LEN];
    int battery;
    int userType;       // 0 = Normal, 1 = Premium
    int arrivalTime;    // tick when arrives
    int waitingTime;    // startTime - arrivalTime (filled at allocation)
    int priorityScore;  // stored/updated by PQ or computed on the fly
    int chargeNeeded;   // ticks required to charge
    int startTime;      // tick when charging started (-1 if not started)
    int finishTime;     // tick when finished (-1 if not finished)
} EV;

/* allocate and initialize an EV (caller must free using ev_free) */
EV* ev_create(const char *id, int battery, int userType, int arrivalTime, int chargeNeeded);
void ev_free(EV *e);

#endif
