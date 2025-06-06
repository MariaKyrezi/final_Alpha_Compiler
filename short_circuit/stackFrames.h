#include "stdio.h"
#include "stdlib.h"

#ifndef STACKFRAMES_H
#define STACKFRAMES_H
/* Create a stack that stores the active frames of */


typedef struct stackFrame{
    char* functionName;
    int scope;
    int scopeOffset;
    struct stackFrame *next;
}stackFrame;



/*Return top element from stack*/
stackFrame* topStack();

/* Initialize stack for function frames */
void initStack();

/* Push the function frame in the stack */
void pushStack(char* functionName, int scope, int scopeOffset);

/* Pop function frame*/
stackFrame* popStack();

void freeStack();

int isEmpty();


#endif