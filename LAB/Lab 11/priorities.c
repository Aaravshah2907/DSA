#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct heap {
    int *data;
    int size;
    int capacity;
    int depth;
};

typedef struct heap* Heap;

// --- Helper functions (assume these exist) ---
int parent(Heap h, int i) { return (i - 1) / 2; }
int left_child(Heap h, int i) { return 2*i + 1 < h->size ? 2*i + 1 : -1; }
int right_child(Heap h, int i) { return 2*i + 2 < h->size ? 2*i + 2 : -1; }

void update_depth(Heap h) {
    if (h->size == 0) h->depth = 0;
    else h->depth = (int)floor(log2(h->size)) + 1;
}

void add_to_heap(Heap h, int value) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity * sizeof(int));
        if (!h->data) { printf("Memory allocation failed\n"); exit(1); }
    }
    h->data[h->size++] = value;
    update_depth(h);
}

void max_heapify(Heap h, int index) {
    int left = left_child(h, index);
    int right = right_child(h, index);
    int largest = index;

    if (left != -1 && h->data[left] > h->data[largest])
        largest = left;
    if (right != -1 && h->data[right] > h->data[largest])
        largest = right;

    if (largest != index) {
        int temp = h->data[index];
        h->data[index] = h->data[largest];
        h->data[largest] = temp;
        max_heapify(h, largest);
    }
}

// --- Priority Queue Functions ---

void insert(Heap h, int value) {
    // Insert with -infinity
    add_to_heap(h, value);  // value temporarily at end
    int i = h->size - 1;

    // Bubble up to maintain max-heap property
    while (i != 0 && h->data[parent(h, i)] < h->data[i]) {
        int p = parent(h, i);
        int temp = h->data[i];
        h->data[i] = h->data[p];
        h->data[p] = temp;
        i = p;
    }
}

int maximum(Heap h) {
    if (h->size == 0) return -1;
    return h->data[0];
}

int extract_maximum(Heap h) {
    if (h->size < 1) return -1;  // empty heap

    int max = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    max_heapify(h, 0);
    update_depth(h);
    return max;
}

void increase_key(Heap h, int i, int k) {
    if (k < h->data[i]) {
        printf("New key is smaller than current key\n");
        return;
    }

    h->data[i] = k;
    // Bubble up to restore heap property
    while (i != 0 && h->data[parent(h, i)] < h->data[i]) {
        int p = parent(h, i);
        int temp = h->data[i];
        h->data[i] = h->data[p];
        h->data[p] = temp;
        i = p;
    }
}