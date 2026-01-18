#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

typedef struct {
    char ID[14];  // assuming IDs are max 13 chars
    float CGPA;
} Student;

double timeCalc(int (*func)(int), int n){
    struct timeval t1, t2;
    double time_taken;
    gettimeofday(&t1, NULL);
    func(n);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    return time_taken;
}

// Create a dynamic array for n students
Student* createArray(int n) {
    Student* arr = (Student*)malloc(n * sizeof(Student));
    if (!arr) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    return arr;
}

// Insert at specific position (0-based)
void insertArray(Student** arr, int* size, int pos, Student s) {
    if (pos < 0 || pos > *size) return;

    *arr = (Student*)realloc(*arr, (*size + 1) * sizeof(Student));
    if (!*arr) {
        printf("Realloc failed!\n");
        exit(1);
    }

    for (int i = *size; i > pos; i--) {
        (*arr)[i] = (*arr)[i - 1];
    }

    (*arr)[pos] = s;
    (*size)++;
}

// Delete last element
void deleteLastArray(Student** arr, int* size) {
    if (*size == 0) return;
    *size -= 1;
    *arr = (Student*)realloc(*arr, (*size) * sizeof(Student));
}

// Retrieve element at position
Student getArray(Student* arr, int size, int pos) {
    if (pos < 0 || pos >= size) {
        printf("Invalid position\n");
        exit(1);
    }
    return arr[pos];
}

// Display array (first few entries for verification)
void displayArray(Student* arr, int size, int count) {
    for (int i = 0; i < size && i < count; i++) {
        printf("%s, %.2f\n", arr[i].ID, arr[i].CGPA);
    }
}

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int count;
} LinkedList;

LinkedList* createList() {
    LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
    l->head = NULL;
    l->count = 0;
    return l;
}

// Insert at end
void insertEndList(LinkedList* l, Student s) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = s;
    n->next = NULL;

    if (!l->head) {
        l->head = n;
    } else {
        Node* temp = l->head;
        while (temp->next) temp = temp->next;
        temp->next = n;
    }
    l->count++;
}

// Insert at position (0-based)
void insertPosList(LinkedList* l, int pos, Student s) {
    if (pos < 0 || pos > l->count) return;

    Node* n = (Node*)malloc(sizeof(Node));
    n->data = s;
    n->next = NULL;

    if (pos == 0) {
        n->next = l->head;
        l->head = n;
    } else {
        Node* temp = l->head;
        for (int i = 0; i < pos - 1; i++) temp = temp->next;
        n->next = temp->next;
        temp->next = n;
    }
    l->count++;
}

// Retrieve element
Student getPosList(LinkedList* l, int pos) {
    if (pos < 0 || pos >= l->count) {
        printf("Invalid position\n");
        exit(1);
    }
    Node* temp = l->head;
    for (int i = 0; i < pos; i++) temp = temp->next;
    return temp->data;
}

// Delete last element
void deleteLastList(LinkedList* l) {
    if (!l->head) return;
    if (!l->head->next) {
        free(l->head);
        l->head = NULL;
        l->count--;
        return;
    }
    Node* temp = l->head;
    while (temp->next->next) temp = temp->next;
    free(temp->next);
    temp->next = NULL;
    l->count--;
}

// Display list (first few entries)
void displayList(LinkedList* l, int count) {
    Node* temp = l->head;
    int i = 0;
    while (temp && i < count) {
        printf("%s, %.2f\n", temp->data.ID, temp->data.CGPA);
        temp = temp->next;
        i++;
    }
}

void readDataArray(Student** arr, int* size) {
    FILE* fp = fopen("data.txt", "r");
    if (!fp) {
        printf("Cannot open file\n");
        exit(1);
    }

    *size = 0;
    *arr = NULL;
    char line[100];
    clock_t start = clock();

    while (fgets(line, sizeof(line), fp)) {
        Student s;
        sscanf(line, "%[^,],%f", s.ID, &s.CGPA); // read ID,CGPA
        *arr = (Student*)realloc(*arr, (*size + 1) * sizeof(Student));
        (*arr)[*size] = s;
        (*size)++;
    }

    clock_t end = clock();
    fclose(fp);

    printf("Time to read into array: %.6f sec\n", (double)(end - start)/CLOCKS_PER_SEC);
}

void readDataList(LinkedList* l) {
    FILE* fp = fopen("data.txt", "r");
    if (!fp) {
        printf("Cannot open file\n");
        exit(1);
    }

    char line[100];
    clock_t start = clock();
    while (fgets(line, sizeof(line), fp)) {
        Student s;
        sscanf(line, "%[^,],%f", s.ID, &s.CGPA);
        insertEndList(l, s);
    }
    clock_t end = clock();
    fclose(fp);

    printf("Time to read into linked list: %.6f sec\n", (double)(end - start)/CLOCKS_PER_SEC);
}

int main()
{
    Student* arr;
    int arrSize;
    LinkedList* list = createList();

    // --- Task 10a ---
    printf("\n\t----------READ----------\n");
    readDataArray(&arr, &arrSize);
    readDataList(list);

    //displayArray(arr, arrSize, 5);    // verify first 5
    //displayList(list, 5);

    // --- Task 10b ---
    // Example: insert 10 new students at user-specified positions
    Student newEntries[10] = {
        {"S10001", 3.5},{"S10002", 3.6},{"S10003",3.7},
        {"S10004", 3.8},{"S10005", 3.9},{"S10006", 3.4},
        {"S10007", 3.2},{"S10008", 3.1},{"S10009",3.0},
        {"S10010", 3.3}
    };
    int positions[10] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450};

    printf("\n\t----------INSERTION----------\n");
    clock_t start = clock();
    for (int i = 0; i < 10; i++)
        insertArray(&arr, &arrSize, positions[i], newEntries[i]);
    clock_t end = clock();
    printf("Array insertion time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < 10; i++)
        insertPosList(list, positions[i], newEntries[i]);
    end = clock();
    printf("Linked list insertion time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);

    // --- Task 10c: Retrieve ---
    printf("\n\t----------RETRIEVAL----------\n");
    int retrievePos = 5000;
    start = clock();
    Student s1 = getArray(arr, arrSize, retrievePos);
    end = clock();
    printf("Array retrieval time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);
    printf("Retrieved from array: %s, %.2f\n\n", s1.ID, s1.CGPA);

    start = clock();
    Student s2 = getPosList(list, retrievePos);
    end = clock();
    printf("Linked list retrieval time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);
    printf("Retrieved from list: %s, %.2f\n", s2.ID, s2.CGPA);

    // --- Task 10d: Delete all ---
    printf("\n\t----------DELETE----------\n");
    start = clock();
    while (arrSize > 0) deleteLastArray(&arr, &arrSize);
    end = clock();
    printf("Array deletion time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    while (list->count > 0) deleteLastList(list);
    end = clock();
    printf("Linked list deletion time: %.6f sec\n", (double)(end-start)/CLOCKS_PER_SEC);

    free(arr);
    free(list);

    return 0;
}
