#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define SET_SIZE 257

typedef struct SNode {
    char id[20];
    struct SNode *next;
} SNode;

static SNode *settable[SET_SIZE];

static unsigned int strhash2(const char *s) {
    unsigned int h = 5381;
    while (*s) { h = ((h << 5) + h) + (unsigned char)*s++; }
    return h % SET_SIZE;
}

void set_init() {
    for (int i=0;i<SET_SIZE;i++) settable[i] = NULL;
}

int set_contains(const char *id) {
    unsigned int idx = strhash2(id);
    SNode *n = settable[idx];
    while (n) { if (strcmp(n->id, id)==0) return 1; n=n->next; }
    return 0;
}

void set_add(const char *id) {
    if (set_contains(id)) return;
    unsigned int idx = strhash2(id);
    SNode *n = (SNode*)malloc(sizeof(SNode));
    strncpy(n->id, id, sizeof(n->id)-1); n->id[sizeof(n->id)-1]='\0';
    n->next = settable[idx];
    settable[idx] = n;
}

void set_print_all() {
    printf("Completed EVs: ");
    for (int i=0;i<SET_SIZE;i++) {
        SNode *n = settable[i];
        while (n) {
            printf("[%s] ", n->id);
            n = n->next;
        }
    }
    printf("\n");
}
