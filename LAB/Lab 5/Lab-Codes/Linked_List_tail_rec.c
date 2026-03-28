#include <stdio.h>
#include <stdlib.h>


typedef struct node * NODE;
struct node{
    int ele;
    NODE next;
};


typedef struct linked_list * LIST;
struct linked_list{
    unsigned long long count;
    NODE head;
};


LIST createNewList()
{
    LIST myList;
    myList = (LIST) malloc(sizeof(struct linked_list));
    myList->count=0;
    myList->head=NULL;
    return myList;
}


NODE createNewNode(int value)
{
    NODE myNode;
    myNode = (NODE) malloc(sizeof(struct node));
    myNode->ele=value;
    myNode->next=NULL;
    return myNode;
}

// Recursive function to compute sum of integers in a linked list
long long llSumNTR(NODE head)
{
    if (head == NULL)
        return 0;
    return head->ele + llSumNTR(head->next); // Pay close attention here
}

// This is just a wrapper function to take LIST as input, but run the recursive sum function on its NODEs starting from the head
long long llSumNTRWrapper(LIST list)
{
    return llSumNTR(list->head);
}

long long llSumTR(NODE head, long long acc){
    if (head == NULL) return acc;
    //printf("%d %lld\n", head->ele, acc);
    return llSumTR(head->next, acc + head->ele);
}

long long llSumTRWrapper(LIST list)
{
    return llSumTR(list->head, 0);
}

long long llSumI(NODE head){
    long long sum = 0;
    while(head != NULL){
        sum = sum + head->ele;
        head = head->next;
    }
    return sum;
}

long long llSumIWrapper(LIST list)
{
    return llSumI(list->head);
}

// Driver code
#include <sys/time.h>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    int num;
    LIST myList = createNewList();

    while (fscanf(fp, "%d", &num) != EOF) {
        NODE myNode = createNewNode(num);
        myNode->next = myList->head;
        myList->head = myNode;
        myList->count++;
    }
    fclose(fp);

    struct timeval t1, t2;
    double time_taken;
    long long result;

    /* Non-tail recursive sum */
    gettimeofday(&t1, NULL);
    result = llSumNTRWrapper(myList);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec)
               + (t2.tv_usec - t1.tv_usec) * 1e-6;

    printf("Non-tail recursive sum = %lld, time = %f seconds\n",
           result, time_taken);

    /* Tail-recursive sum */
    gettimeofday(&t1, NULL);
    result = llSumTRWrapper(myList);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec)
               + (t2.tv_usec - t1.tv_usec) * 1e-6;

    printf("Tail-recursive sum     = %lld, time = %f seconds\n",
           result, time_taken);

    /* Iterative sum */
    gettimeofday(&t1, NULL);
    result = llSumIWrapper(myList);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec)
               + (t2.tv_usec - t1.tv_usec) * 1e-6;

    printf("Iterative sum          = %lld, time = %f seconds\n",
           result, time_taken);

    return 0;
}
