#include <stdio.h>
#include <stdlib.h>

typedef struct node* NODE;

struct node{
    int ele;
    NODE next;
};

typedef struct linked_list* LIST;

struct linked_list{
    int count;
    NODE head;
};

LIST createNewList(){
    LIST myList;
    myList = (LIST) malloc(sizeof(struct linked_list));
    myList->count=0;
    myList->head=NULL;
    return myList;
}

NODE createNewNode(int value){
    NODE myNode;
    myNode = (NODE) malloc(sizeof(struct node));
    myNode->ele=value;
    myNode->next=NULL;
    return myNode;

}

void insertAfter(int searchEle, NODE n1, LIST l1){
    if(l1->head==NULL){
        l1->head = n1;
        n1->next = NULL;
        l1->count++;
        }
    else{
        NODE temp = l1->head;
        NODE prev = temp;
        while(temp!=NULL){
            if (temp->ele == searchEle)
                break;
            prev = temp;
            temp = temp->next;
        }
        if(temp==NULL){
            printf("Element not found\n");
            return;
        }
        else{
            if(temp->next == NULL){
                temp->next = n1;
                n1->next = NULL;
                l1->count++;
            }
            else{
                prev = temp;
                temp = temp->next;
                prev->next = n1;
                n1->next = temp;
                l1->count++;
            }
            return;
        }
    }
   
    return;
}

void printList(LIST l1){
    NODE temp = l1->head;
    printf("[HEAD] ->");
    while(temp != NULL){
        printf(" %d ->", temp->ele);
        temp = temp->next;
        }
    printf(" [NULL]\n");
}

void deleteAt(LIST l1, int pos)
{
    NODE temp, prev;

    if (l1->head == NULL || pos < 1 || pos > l1->count)
    {
        printf("Invalid position\n");
        return;
    }

    // Delete first node
    if (pos == 1)
    {
        temp = l1->head;
        l1->head = temp->next;
        free(temp);
        l1->count--;
        return;
    }

    temp = l1->head;
    for (int i = 1; i < pos; i++)
    {
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    free(temp);
    l1->count--;
}

void insertFirst(LIST l1, int data)
{
    NODE n1 = (NODE)malloc(sizeof(struct node));
    if (n1 == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    n1->ele = data;
    n1->next = l1->head;
    l1->head = n1;
    l1->count++;
}

void deleteFirst(LIST l1)
{
    NODE temp;

    if (l1->head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    temp = l1->head;
    l1->head = temp->next;
    free(temp);
    l1->count--;
}

int search(LIST l1, int key)
{
    NODE temp = l1->head;
    int pos = 1;

    while (temp != NULL)
    {
        if (temp->ele == key)
            return pos;

        temp = temp->next;
        pos++;
    }

    return -1;
}

