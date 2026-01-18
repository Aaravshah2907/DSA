// Checks for Circular Linked Lists

#include "convertToCircularLinkedList.c"

int hasCycle(LIST L1){
    NODE HARE = L1->head;
    NODE TORTOISE = L1->head;
    int counter = 0;

    while (HARE != NULL && HARE->next != NULL)
    {
        counter++;
        TORTOISE = TORTOISE->next;
        HARE = HARE->next->next;

        if (TORTOISE == HARE){
            printf("Counter: %d\n", counter);
            return 1;   // Cycle detected

        }
    }

    printf("Counter: %d\n", counter);
    return 0; 
}
