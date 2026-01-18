#include "baseCode.c"

void conversion(LIST l1, int k){
    if (l1->head == NULL || k <= 0)
        return;

    NODE tail = l1->head;

    /* Step 1: Reach last node */
    while (tail->next != NULL)
        tail = tail->next;

    /* Step 2: Make circular */
    tail->next = l1->head;

    /* Step 3: Move k steps */
    NODE newTail = l1->head;
    for (int i = 1; i < k; i++)
        newTail = newTail->next;

    /* Step 4: Update head */
    l1->head = newTail->next;

    /* Step 5: Break the circle */
    newTail->next = NULL;
}

void MakeCircular(LIST l1){
    if (l1->head == NULL)
        return;

    NODE tail = l1->head;

    /* Step 1: Reach last node */
    while (tail->next != NULL)
        tail = tail->next;

    /* Step 2: Make circular */
    tail->next = l1->head;
}