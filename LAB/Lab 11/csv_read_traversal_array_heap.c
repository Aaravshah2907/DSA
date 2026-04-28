#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
} Person;

struct heap_person {
    Person *data;
    int size;
    int capacity;
    int depth;
};
typedef struct heap_person* HeapPerson;

HeapPerson heap_person_create() {
    HeapPerson h = malloc(sizeof(struct heap_person));
    h->data = malloc(sizeof(Person));  // initial capacity 1
    h->size = 0;
    h->capacity = 1;
    h->depth = 0;
    return h;
}

void update_depth_person(HeapPerson h) {
    if (h->size == 0)
        h->depth = 0;
    else
        h->depth = (int)floor(log2(h->size)) + 1;
}

void add_to_heap_person(HeapPerson h, Person p) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity * sizeof(Person));
        if (!h->data) { printf("Memory allocation failed\n"); exit(1); }
    }
    h->data[h->size++] = p;
    update_depth_person(h);
}

int left_child_person(HeapPerson h, int node) { int idx = 2*node+1; return idx >= h->size ? -1 : idx; }
int right_child_person(HeapPerson h, int node) { int idx = 2*node+2; return idx >= h->size ? -1 : idx; }

void max_heapify_person(HeapPerson h, int index) {
    int left = left_child_person(h, index);
    int right = right_child_person(h, index);
    int largest = index;

    if (left != -1 && h->data[left].height > h->data[largest].height)
        largest = left;
    if (right != -1 && h->data[right].height > h->data[largest].height)
        largest = right;

    if (largest != index) {
        Person temp = h->data[index];
        h->data[index] = h->data[largest];
        h->data[largest] = temp;
        max_heapify_person(h, largest);
    }
}

void build_max_heap_person(HeapPerson h) {
    for (int i = (h->size / 2) - 1; i >= 0; i--)
        max_heapify_person(h, i);
}

void heap_sort_person(Person arr[], int n) {
    HeapPerson h = heap_person_create();
    for (int i = 0; i < n; i++)
        add_to_heap_person(h, arr[i]);

    build_max_heap_person(h);

    for (int i = n-1; i > 0; i--) {
        // swap root with last
        Person temp = h->data[0];
        h->data[0] = h->data[i];
        h->data[i] = temp;

        h->size--;  // reduce heap size
        max_heapify_person(h, 0);
    }

    // copy back to original array
    for (int i = 0; i < n; i++)
        arr[i] = h->data[i];

    free(h->data);
    free(h);
}

Person* read_csv(const char* filename, int *count) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { printf("Cannot open file\n"); exit(1); }

    int capacity = 10;
    Person *arr = malloc(capacity * sizeof(Person));
    *count = 0;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (*count >= capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(Person));
        }

        char *token = strtok(line, ",");
        arr[*count].id = atoi(token);

        token = strtok(NULL, ",");
        arr[*count].name = strdup(token);  // allocate string

        token = strtok(NULL, ",");
        arr[*count].age = atoi(token);

        token = strtok(NULL, ",");
        arr[*count].height = atoi(token);

        token = strtok(NULL, ",");
        arr[*count].weight = atoi(token);

        (*count)++;
    }

    fclose(fp);
    return arr;
}

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s filename\n", argv[0]); return 1; }

    int n;
    Person *arr = read_csv(argv[1], &n);

    clock_t start = clock();
    heap_sort_person(arr, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Heap sort completed in %.6f seconds\n", time_taken);

    //printf("Sorted by height:\n");
    //for (int i = 0; i < n; i++)
        //printf("%d, %s, %d, %d, %d\n", arr[i].id, arr[i].name, arr[i].age, arr[i].height, arr[i].weight);

    // free memory

    printf("Maximum heap memory used: %zu bytes\n", sizeof(struct heap_person) + n * sizeof(Person));
    for (int i = 0; i < n; i++) free(arr[i].name);
    free(arr);

    return 0;
}