#include "regex.h"
#include "NFASimulator.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    char * sentence = "ab|c.";
    char * toMatch = "a";
    STATE * ptr = post2nfa(sentence);
    printf("First option : %d\n",ptr->out->out->out->c);
    printf("Second option : %d\n",ptr->out1->out->c);
    printf("Does it match ? : %d\n",match(ptr,toMatch));
    return 0;
}