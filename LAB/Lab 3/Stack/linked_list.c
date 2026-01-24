#include "element.h"
#include "linked_list.h"
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