#include "convertToCircularLinkedList.c"

int main()
{
    LIST l1 = createNewList();
    NODE n;

    printf("Initial list:\n");
    printList(l1);

    /* Insert at beginning */
    printf("\nInserting at beginning:\n");
    insertFirst(l1, 10);
    insertFirst(l1, 20);
    insertFirst(l1, 30);
    printList(l1);

    /* Insert after a given element */
    printf("\nInsert 25 after 20:\n");
    n = createNewNode(25);
    insertAfter(20, n, l1);
    printList(l1);

    printf("\nInsert 5 after 10:\n");
    n = createNewNode(5);
    insertAfter(10, n, l1);
    printList(l1);

    /* Search elements */
    printf("\nSearching elements:\n");
    int pos = search(l1, 25);
    if (pos != -1)
        printf("Element 25 found at position %d\n", pos);
    else
        printf("Element 25 not found\n");

    pos = search(l1, 100);
    if (pos != -1)
        printf("Element 100 found at position %d\n", pos);
    else
        printf("Element 100 not found\n");

    /* Delete first node */
    printf("\nDeleting first node:\n");
    deleteFirst(l1);
    printList(l1);

    /* Delete at a specific position */
    printf("\nDeleting node at position 3:\n");
    deleteAt(l1, 3);
    printList(l1);
    printf("\nFinal list count: %d\n", l1->count);

    printf("\nFinal list:\n");
    printList(l1);

    conversion(l1, 0);
    
    printf("\nFinal list 0 :\n");
    printList(l1);
    
    conversion(l1, 1);
    
    printf("\nFinal list 1 :\n");
    printList(l1);
    
    conversion(l1, 2);
    
    printf("\nFinal list 2 :\n");
    printList(l1);

    return 0;
}
