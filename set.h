#ifndef SET_H
#define SET_H

/* small string-hash set for completed EV IDs */
void set_init();
int set_contains(const char *id);
void set_add(const char *id);
void set_print_all();

#endif
