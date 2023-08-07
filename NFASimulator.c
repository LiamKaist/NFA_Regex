#include "NFASimulator.h"

/* Pre-allocating memory for the lists */
STATE* stateVector1[10];
STATE* stateVector2[10];

LIST l1 = {stateVector1,0}; /* A pointer to the address that contains the start address of the preallocated arrays*/
LIST l2 = {stateVector2,0};

int listid = 0;

int match(STATE* start, char* s)
{
    LIST* clist, *nlist, *t;

    /* l1 and l2 are preallocated globals */
    clist = startList(start, &l1); /* List with the first state, or in our case 2 separate states due to |*/
    nlist = &l2;
    for(; *s;s++)
    {
        step(clist,*s,nlist);
        t = clist; clist = nlist; nlist = t; /* Swapping lists */
    }
    return ismatch(clist);
}

int ismatch(LIST* l)
{
    int i;
    for(i=0;i<l->n;i++)
        if(l->s[i]->c == 257)
            return 1;
    return 0;
}

void addState(LIST *l, STATE * s)
{
    if(s == NULL || s->lastlist == listid)
    {
        return;
    }
    s->lastlist = listid;
    if(s->c == SPLIT)
    {
        /* Follow unlabeled arrows */
        addState(l, s->out);
        addState(l, s->out1);
        return;
    }
    l->s[l->n++] = s;
}

LIST* startList(STATE * s, LIST* l)
{
    listid++;
    l->n = 0;
    addState(l,s);
    return l;
}

void step(LIST* clist, int c, LIST* nlist)
{
    int i;
    STATE* s;
    listid++;
    nlist->n = 0;
    for(i=0; i<clist->n; i++)
    {
        s = clist->s[i];
        if(s->c == c)
        {
            addState(nlist, s->out);
        }
    }
}