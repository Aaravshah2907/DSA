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

Heap heap_create(){
    Heap h = malloc(sizeof(struct heap));
    h->data = malloc(sizeof(int));
    h->size = 0;
    h->capacity = 1;
    h->depth = 0;
    return h;
}

void update_depth(Heap h) {
    if (h->size == 0) {
        h->depth = 0;
    } else {
        h->depth = (int)floor(log2(h->size)) + 1;
    }
}

void add_to_tree(Heap h, int value) {
    // Resize if needed
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->data = (int*)realloc(h->data, h->capacity * sizeof(int));
        if (h->data == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    // Insert at next free slot
    h->data[h->size++] = value;

    // Update depth
    update_depth(h);
}

int heap_memory(Heap h) {
    return sizeof(struct heap) + (h->capacity * sizeof(int));
}

int parent(Heap h, int node) {
    if (node <= 0 || node >= h->size)
        return -1; // invalid or root has no parent
    return (node - 1) / 2;
}

int left_child(Heap h, int node) {
    int idx = 2 * node + 1;
    if (idx >= h->size)
        return -1; // no left child
    return idx;
}

int right_child(Heap h, int node) {
    int idx = 2 * node + 2;
    if (idx >= h->size)
        return -1; // no right child
    return idx;
}

void max_heapify(Heap h, int index){
    int left = left_child(h, index);
    int right = right_child(h, index);
    int largest = index;
    if (left < h->size && h->data[left] > h->data[largest])
        largest = left;
    if (right < h->size && h->data[right] > h->data[largest])
        largest = right;

    if (largest != index){
        int temp = h->data[index];
        h->data[index] = h->data[largest];
        h->data[largest] = temp;
        max_heapify(h, largest);
    }
}

void build_max_heap(Heap h) {
    // Start from last non-leaf node
    for (int i = (h->size / 2) - 1; i >= 0; i--) {
        max_heapify(h, i);
    }
}

int nodes_at_depth(Heap h, int depth) {
    if (depth < 0)
        return 0;

    int start = (1 << depth) - 1;          // 2^depth - 1
    int end   = (1 << (depth + 1)) - 2;    // 2^(depth+1) - 2

    if (start >= h->size)
        return 0; // no nodes at this depth

    if (end >= h->size)
        end = h->size - 1;

    return end - start + 1;
}