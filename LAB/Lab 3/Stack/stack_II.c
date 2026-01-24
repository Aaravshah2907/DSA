#include "element.h"
#include "linked_list.h"
#include "stack.h"
#include <stdlib.h>

LIST createNewList(){

    // This function allocates memory for a new list and returns a pointer to it.
    // The list is empty and the count is set to 0.

    LIST list = (LIST)malloc(sizeof(struct linked_list));
    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->count = 0;
    return list;
}

NODE createNewNode(Element data){

    // This function allocates memory for a new node and returns a pointer to it.
    // The next pointer is set to NULL and the data is set to the value passed in.

    NODE node = (NODE)malloc(sizeof(struct node));
    if (node == NULL) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

void insertNodeIntoList(NODE node, LIST list){

    // This function inserts a node at the beginning of the list.
    
    if (list == NULL || node == NULL) return;

    node->next = list->head;
    list->head = node;
    list->count++;
    
}

void removeFirstNode(LIST list){

    // This function removes the first node from the list.
    
    if (list == NULL || list->head == NULL) return;

    NODE temp = list->head;
    list->head = temp->next;
    free(temp);
    list->count--;
}


void insertNodeAtEnd(NODE node, LIST list){

    // This function inserts a node at the end of the list.

    if(list == NULL || node == NULL) return;

    node->next = NULL;

    if(list->head == NULL){
        list->head = node;
    } else {
        NODE current = list->head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = node;
    }
    list->count++;
} 

void destroyList(LIST list){

    // free all nodes

    if (list == NULL) return;

    while(list->head != NULL)
        removeFirstNode(list);
    
    free(list);
}

struct Stack{
    LIST list;
};

Stack *newStack(){

    // Returns a pointer to a new stack. Returns NULL if memory allocation fails
    
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if(s==NULL) return NULL;

    s->list = createNewList();
    if (s->list == NULL){
        free(s);
        return NULL;
    }
    return s;
}

bool isEmpty(Stack *s){

    // Returns true if stack is empty. Returns false otherwise

    return (s == NULL || s->list->count == 0);
}

bool push(Stack *s, Element e){

    // Pushes element onto stack. Returns false if memory allocation fails

    NODE node = createNewNode(e);
    if (node == NULL) return false;
    
    insertNodeIntoList(node, s->list);
    return true;
}

Element *top(Stack *s){ 

    // Returns a pointer to the top element. Returns NULL if stack is empty

    if (isEmpty(s))
        return NULL;
    return &s->list->head->data;
}

Element *pop(Stack *s){ 

    // Pops the top element and returns true. Returns false if stack is empty

    if (isEmpty(s))
        return NULL;
    
    Element *e = malloc(sizeof(Element));
    if (e == NULL) return NULL;

    *e = s->list->head->data;
    removeFirstNode(s->list);
    return e;
}

void freeStack(Stack *s){ 
    
    // Frees all memory associated with stack
    
    if (isEmpty(s)) return;

    destroyList(s->list);
    free(s);
}