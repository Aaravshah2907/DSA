#include "HareTortoiseAlg.c"

int main()
{
    LIST l1;
    NODE n1, n2, n3, n4;

    /* ===============================
       Test 1: Acyclic Linked List
       =============================== */
    printf("Test 1: Acyclic List\n");
    l1 = createNewList();

    n1 = createNewNode(10);
    n2 = createNewNode(20);
    n3 = createNewNode(30);

    l1->head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;

    if (hasCycle(l1))
        printf("Cycle detected\n");
    else
        printf("No cycle detected\n");

    /* ===============================
       Test 2: Cyclic Linked List
       (last node points to middle)
       =============================== */
    printf("\nTest 2: Cyclic List\n");
    l1 = createNewList();

    n1 = createNewNode(1);
    n2 = createNewNode(2);
    n3 = createNewNode(3);
    n4 = createNewNode(4);

    l1->head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n2;   // cycle here

    if (hasCycle(l1))
        printf("Cycle detected\n");
    else
        printf("No cycle detected\n");

    /* ===============================
       Test 3: Circular Linked List
       (last node points to head)
       =============================== */
    printf("\nTest 3: Circular List\n");
    l1 = createNewList();

    n1 = createNewNode(100);
    n2 = createNewNode(200);
    n3 = createNewNode(300);

    l1->head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n1;   // circular

    if (hasCycle(l1))
        printf("Cycle detected\n");
    else
        printf("No cycle detected\n");

    return 0;
}
