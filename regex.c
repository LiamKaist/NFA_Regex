#include <stdio.h> /* For NULL */
#include <stdlib.h> /* For malloc */
#include "regex.h"
#include <assert.h>

/* Helper functions for PTR_LIST */
PTR_LIST* list1(STATE* stateAddr)
{
    /* List is always empty at first */
    PTR_LIST_CELL* cell = malloc(sizeof(PTR_LIST_CELL));
    cell->state_ptr = stateAddr;
    /* Creating List */
    PTR_LIST* list = malloc(sizeof(PTR_LIST));
    list->first = cell;
    list->last = cell;
    return list;
}

PTR_LIST* append(PTR_LIST* l1, PTR_LIST* l2)
{
    if ((l1 == NULL) || (l2 == NULL))
    {
        /* Empty list check */
        l1 = NULL;
    }
    else
    {
        /* Any number of elements in the lists */
        l1->last->next_ptr = l2->first;
    }
    return l1;
}

void patch(PTR_LIST* l, STATE* s)
{
    if((l != NULL) && (s != NULL))
    {
        /* Go through the PTR_LIST*/
        PTR_LIST_CELL* temp_ptr = l->first;
        while(temp_ptr != NULL)
        {
            /* Assign s to each state_ptr */
            temp_ptr->state_ptr->out = s;
            temp_ptr = temp_ptr->next_ptr;
        }
    }
}

/* Function definition */

STATE* state(int c,STATE* out, STATE* out1)
{
    /* Allocating memory */
    STATE* s = malloc(sizeof(STATE));
    /* Filling state with values */
    s->c = c;
    s->out = out;
    s->out1 = out1;
    return s;
}
FRAG frag(STATE* start, PTR_LIST* out)
{
    /* Allocating memory */
    FRAG f;
    /* Filling frag with values */
    f.start = start;
    f.out = out;
    return f;
}

STATE* post2nfa(char* postfix)
{
    char *p;
    FRAG stack[1000], *stackp, e1, e2, e;
    STATE *s;

    #define push(fragment) *stackp++ = fragment
    #define pop() *--stackp

    stackp = stack;
    for(p=postfix; *p;p++)
    {
        switch(*p)
        {
            /* Concatenation */
            case '.':
                e2 = pop();
                e1 = pop();
                patch(e1.out,e2.start);
                push(frag(e1.start, e2.out));
                break;

            case '|':
                e2 = pop();
                e1 = pop();
                s = state(SPLIT, e1.start, e2.start);
                push(frag(s,append(e1.out,e2.out)));
                break;

            /* Literal Characters */
            default:
                s = state(*p,NULL,NULL);
                push(frag(s,list1(s)));
                break;
        }
    }
    e = pop();
    e.start;
    patch(e.out,state(257,NULL,NULL)); /* Last state is matchstate */
    return  e.start;
}
