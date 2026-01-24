#include "element.h"
#include "stack.h"
#include <stdlib.h>

#define STACK_SIZE 1000

struct Stack
{
    int top;
    Element data[STACK_SIZE];
};

Stack *newStack()
{
    // Returns a pointer to a new stack. Returns NULL if memory allocation fails
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s != NULL)
        s->top = -1;
    return s;
}

bool isEmpty(Stack *s){
    // Returns true if stack is empty. Returns false otherwise
    return (s == NULL || s->top == -1);
}

bool push(Stack *s, Element e)
{
    // Pushes element onto stack. Returns false if memory allocation fails
    if(s->top == STACK_SIZE - 1)
        return false;
    s->data[++(s->top)] = e;
    return true;
}

Element *top(Stack *s){ 
    // Returns a pointer to the top element. Returns NULL if stack is empty
    if (isEmpty(s))
        return NULL;
    return &s->data[s->top];
}

Element *pop(Stack *s){ 
    // Pops the top element and returns true. Returns false if stack is empty
    if (isEmpty(s))
        return NULL;
    return &s->data[s->top--];
}

void freeStack(Stack *s){ 
    // Frees all memory associated with stack
    if (s != NULL)
        free(s);
}