#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

typedef struct HNode {
    EV *ev;
    struct HNode *next;
} HNode;

static HNode *htable[HASH_TABLE_SIZE];

static unsigned int strhash(const char *s) {
    unsigned int h = 2166136261u;
    while (*s) { h ^= (unsigned char)*s; h *= 16777619u; s++; }
    return h % HASH_TABLE_SIZE;
}

void hash_init() {
    for (int i=0;i<HASH_TABLE_SIZE;i++) htable[i]=NULL;
}

void hash_insert(EV *ev) {
    unsigned int idx = strhash(ev->id);
    HNode *n = (HNode*)malloc(sizeof(HNode));
    n->ev = ev;
    n->next = htable[idx];
    htable[idx] = n;
}

EV* hash_lookup(const char *id) {
    unsigned int idx = strhash(id);
    HNode *n = htable[idx];
    while (n) {
        if (strcmp(n->ev->id, id)==0) return n->ev;
        n = n->next;
    }
    return NULL;
}
