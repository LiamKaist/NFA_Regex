#ifndef REGEX_H
#define REGEX_H
#define SPLIT 256

/* Structure definitions */
typedef struct State STATE;
typedef struct State
{
    int c;
    STATE* out;
    STATE* out1;
    int lastlist;
}STATE;

typedef struct PtrListCell PTR_LIST_CELL;
typedef struct PtrListCell
{
    STATE* state_ptr;
    PTR_LIST_CELL* next_ptr;
}PTR_LIST_CELL;

typedef struct PtrList
{
    PTR_LIST_CELL* first;
    PTR_LIST_CELL* last;
}PTR_LIST;

typedef struct Frag
{
    STATE* start;
    PTR_LIST *out;
}FRAG;

/* Function definitions */

PTR_LIST* list1(STATE* outp);
PTR_LIST* append(PTR_LIST* l1, PTR_LIST* l2);
void patch(PTR_LIST* l, STATE* s);
STATE* state(int c,STATE* out, STATE* out1);
FRAG frag(STATE* start, PTR_LIST* out);

/* Compiler */
STATE* post2nfa(char* postfix);


#endif