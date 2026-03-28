#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_POINTS 1000

struct point {
    double x, y;
};

// Node for linked list in each bucket
typedef struct Node {
    struct point p;
    struct Node* next;
} Node;

// Insert at beginning of linked list
Node* insertNode(Node* head, struct point p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->p = p;
    newNode->next = head;
    return newNode;
}

// Convert linked list to array
void listToArray(Node* head, struct point* arr, int* index) {
    Node* temp = head;
    while (temp) {
        arr[(*index)++] = temp->p;
        temp = temp->next;
    }
}

// Insertion sort based on distance from origin
void insertionSort(struct point* arr, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        struct point key = arr[i];
        double keyDist = key.x*key.x + key.y*key.y;
        int j = i - 1;
        while (j >= start && (arr[j].x*arr[j].x + arr[j].y*arr[j].y) > keyDist) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    struct point points[N_POINTS];
    FILE* file = fopen("points.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read points from file
    for (int i = 0; i < N_POINTS; i++) {
        fscanf(file, " (%lf,%lf)", &points[i].x, &points[i].y);
    }
    fclose(file);

    // Create buckets (linked list for each bucket)
    Node* buckets[N_POINTS];
    for (int i = 0; i < N_POINTS; i++) buckets[i] = NULL;

    // Insert points into buckets
    for (int i = 0; i < N_POINTS; i++) {
        double dist = points[i].x*points[i].x + points[i].y*points[i].y;
        int idx = (int)(dist * N_POINTS); // bucket index
        if (idx >= N_POINTS) idx = N_POINTS - 1; // edge case
        buckets[idx] = insertNode(buckets[idx], points[i]);
    }

    // Concatenate buckets back into points array with insertion sort per bucket
    int pos = 0;
    for (int i = 0; i < N_POINTS; i++) {
        // Count elements in bucket
        Node* temp = buckets[i];
        int start = pos;
        while (temp) {
            points[pos++] = temp->p;
            temp = temp->next;
        }
        int end = pos - 1;
        if (end > start) insertionSort(points, start, end); // sort small bucket
    }

    // Print first 1000 points for verification
    printf("First 1000 sorted points by distance:\n");
    for (int i = 0; i < 1000; i++) {
        double d = sqrt(points[i].x*points[i].x + points[i].y*points[i].y);
        printf("(%.5lf, %.5lf) -> distance = %.5lf\n", points[i].x, points[i].y, d);
    }

    return 0;
}