#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 5  // Max elements per bucket before splitting

// Node for linked list in each bucket
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Function to insert at the beginning of linked list
Node* insertNode(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = head;
    return newNode;
}

// Function to convert linked list to array
int* listToArray(Node* head, int* size) {
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }

    int* arr = (int*)malloc(count * sizeof(int));
    temp = head;
    for (int i = 0; i < count; i++) {
        arr[i] = temp->value;
        temp = temp->next;
    }

    *size = count;
    return arr;
}

// Insertion sort for small arrays
void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// Function to free linked list
void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to perform dynamic bucket sort
void dynamicBucketSort(int* arr, int n) {
    if (n <= 1) return;

    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    int range = max - min + 1;
    int numBuckets = n / 2 + 1; // Initial guess (can be sqrt(n) as well)
    int width = (range + numBuckets - 1) / numBuckets; // ceiling division

    // Create buckets (array of linked lists)
    Node** buckets = (Node**)calloc(numBuckets, sizeof(Node*));

    // Insert elements into appropriate bucket
    for (int i = 0; i < n; i++) {
        int idx = (arr[i] - min) / width;
        if (idx >= numBuckets) idx = numBuckets - 1; // edge case
        buckets[idx] = insertNode(buckets[idx], arr[i]);
    }

    // Now process each bucket
    int pos = 0;
    for (int i = 0; i < numBuckets; i++) {
        // If bucket has more than THRESHOLD elements, split recursively
        int bucketSize = 0;
        Node* temp = buckets[i];
        while (temp) {
            bucketSize++;
            temp = temp->next;
        }

        if (bucketSize > THRESHOLD) {
            int* tempArr = listToArray(buckets[i], &bucketSize);
            dynamicBucketSort(tempArr, bucketSize);
            for (int j = 0; j < bucketSize; j++) {
                arr[pos++] = tempArr[j];
            }
            free(tempArr);
        } else {
            // Convert to array and sort using insertion sort
            int* tempArr = listToArray(buckets[i], &bucketSize);
            insertionSort(tempArr, bucketSize);
            for (int j = 0; j < bucketSize; j++) {
                arr[pos++] = tempArr[j];
            }
            free(tempArr);
        }
        freeList(buckets[i]);
    }

    free(buckets);
}