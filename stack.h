#ifndef STACK_H
#define STACK_H

#include "ev.h"

typedef enum { ACTION_ALLOC } ActionType;
typedef struct {
    ActionType type;
    int slotIndex;
    EV *ev;
    int prevTimeLeft;
} Action;

void stack_init();
void stack_push_undo(Action a);
int stack_pop_undo(Action *out);
void stack_push_redo(Action a);
int stack_pop_redo(Action *out);
void stack_clear_redo();

#endif
