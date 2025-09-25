#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_CAP 1024
static Action undoStack[STACK_CAP];
static int undoTop = 0;
static Action redoStack[STACK_CAP];
static int redoTop = 0;

void stack_init() { undoTop = 0; redoTop = 0; }

void stack_push_undo(Action a) {
    if (undoTop < STACK_CAP) undoStack[undoTop++] = a;
    redoTop = 0; // new action clears redo
}

int stack_pop_undo(Action *out) {
    if (undoTop == 0) return 0;
    *out = undoStack[--undoTop];
    return 1;
}

void stack_push_redo(Action a) { if (redoTop < STACK_CAP) redoStack[redoTop++] = a; }

int stack_pop_redo(Action *out) {
    if (redoTop == 0) return 0;
    *out = redoStack[--redoTop];
    return 1;
}

void stack_clear_redo() { redoTop = 0; }
