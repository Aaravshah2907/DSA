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

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Heap heap_create(){
    Heap h = malloc(sizeof(struct heap));
    h->data = malloc(sizeof(int));
    h->size = 0;
    h->capacity = 1;
    h->depth = 0;
    return h;
}

Node* create_node(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
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

void add_to_tree_node(Node **root, int value) {
    Node* newNode = create_node(value);

    if (*root == NULL) {
        *root = newNode;
        return;
    }

    int capacity = 10;
    Node** queue = (Node**)malloc(capacity * sizeof(Node*));

    int front = 0, rear = 0;
    queue[rear++] = *root;

    while (front < rear) {
        Node* temp = queue[front++];

        if (temp->left == NULL) {
            temp->left = newNode;
            break;
        } else {
            if (rear == capacity) {
                capacity *= 2;
                queue = realloc(queue, capacity * sizeof(Node*));
            }
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = newNode;
            break;
        } else {
            if (rear == capacity) {
                capacity *= 2;
                queue = realloc(queue, capacity * sizeof(Node*));
            }
            queue[rear++] = temp->right;
        }
    }

    free(queue);
}

int heap_memory(Heap h) {
    return sizeof(struct heap) + (h->capacity * sizeof(int));
}

int node_memory(Node *root) {
    if (root == NULL)
        return 0;

    return sizeof(Node) + node_memory(root->left) + node_memory(root->right);
}

int main() {
    // Create structures
    Heap h = heap_create();
    Node *root = NULL;

    // Hardcoded values
    int values[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // Insert into both trees
    for (int i = 0; i < 10; i++) {
        add_to_tree(h, values[i]);
        add_to_tree_node(&root, values[i]);
    }

    // Calculate memory
    int heap_mem = heap_memory(h);
    int node_mem = node_memory(root);

    // Print results
    printf("Heap-based tree memory: %d bytes\n", heap_mem);
    printf("Node-based tree memory: %d bytes\n", node_mem);

    // Extra info (useful for analysis)
    printf("\nHeap details:\n");
    printf("Size = %d, Capacity = %d, Depth = %d\n",
           h->size, h->capacity, h->depth);

    return 0;
}