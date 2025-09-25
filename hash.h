#ifndef HASH_H
#define HASH_H

#include "ev.h"

#define HASH_TABLE_SIZE 257

/* simple chaining hash table storing EV* by id */
void hash_init();
void hash_insert(EV *ev);
EV* hash_lookup(const char *id);

#endif
