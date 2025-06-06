#include "stackFrames.h"

int func_counter = 0;

stackFrame* head = NULL, *top = NULL;


/*Returns top element from stack*/
stackFrame* topStack() {
    if (isEmpty()) {
        printf("Stack is empty.\n");
        return NULL;
    }
    return top;
}

/*  Pushes into the stack the frame of a function that has been  
    just defined or called / used */
void pushStack(char* functionName,int scope, int scopeOffset){
    stackFrame *frame, *tmp = head;
    frame = (stackFrame*)malloc(sizeof(stackFrame));

    frame->functionName = functionName;
    frame->scope = scope;
    frame->scopeOffset = scopeOffset;
    frame->next = NULL;
    
    if(head == NULL){
        head = frame;
        top = frame;
        
        return;
    }
    while(tmp->next != NULL){
        tmp  = tmp->next;
    }
    
    top = frame;
    tmp->next = frame;
}

/* Pop the last element of the stack which is the current active function frame */
stackFrame* popStack(){
    stackFrame* tmp = head, *prev;
    if(isEmpty()){
        
        return NULL;
    }
    prev = NULL;
    while(tmp->next != NULL){
        prev = tmp;
        tmp = tmp->next;
    }
    if(prev != NULL){
        prev->next = NULL;
    }
    
    top = prev;
    
    return tmp;
}

int isEmpty(){
    return !head;
}

/* Free the stack */
void freeStack(){
    free(head);
}
  


