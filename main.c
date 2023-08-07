#include "regex.h"
#include "NFASimulator.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    char * regex = "hi.h.e.l.l.o.";
    char * toMatch = "hihello";
    STATE * regex_model = post2nfa(regex);
    printf("Does it match ? : %d\n",match(regex_model,toMatch));
    return 0;
}