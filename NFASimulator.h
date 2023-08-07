#ifndef NFA_SIMULATOR_H
#define NFA_SIMULATOR_H
#include "stdio.h"
#include "regex.h"

/* List to track STATE sets */
typedef struct List
{
    STATE **s;
    int n;
}LIST;

int match(STATE* start, char* s);
int ismatch(LIST* l);
void addState(LIST *l, STATE * s);
LIST* startList(STATE * s, LIST* l);
void step(LIST* clist, int c, LIST* nlist);

#endif