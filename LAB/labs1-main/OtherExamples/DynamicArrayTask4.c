#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

/* Function prototypes */
void addEnd(char ***arr, int *size);
void addBeginning(char ***arr, int *size);
void deleteAtIndex(char ***arr, int *size);
void displayLength(int size);
void displayElements(char **arr, int size);
void freeArray(char **arr, int size);

void addEnd(char ***arr, int *size) {
    *arr = realloc(*arr, (*size + 1) * sizeof(char *));
    (*arr)[*size] = malloc(MAX_LEN * sizeof(char));

    printf("Enter string: ");
    fgets((*arr)[*size], MAX_LEN, stdin);
    (*arr)[*size][strcspn((*arr)[*size], "\n")] = '\0';

    (*size)++;
}

void addBeginning(char ***arr, int *size) {
    *arr = realloc(*arr, (*size + 1) * sizeof(char *));

    for (int i = *size; i > 0; i--) {
        (*arr)[i] = (*arr)[i - 1];
    }

    (*arr)[0] = malloc(MAX_LEN * sizeof(char));
    printf("Enter string: ");
    fgets((*arr)[0], MAX_LEN, stdin);
    (*arr)[0][strcspn((*arr)[0], "\n")] = '\0';

    (*size)++;
}

void deleteAtIndex(char ***arr, int *size) {
    int index;
    printf("Enter index to delete (0 to %d): ", *size - 1);
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= *size) {
        printf("Invalid index!\n");
        return;
    }

    free((*arr)[index]);

    for (int i = index; i < *size - 1; i++) {
        (*arr)[i] = (*arr)[i + 1];
    }

    *arr = realloc(*arr, (*size - 1) * sizeof(char *));
    (*size)--;
}

void displayLength(int size) {
    printf("Current array length: %d\n", size);
}

void displayElements(char **arr, int size) {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("[%d]: %s\n", i, arr[i]);
    }
}

void freeArray(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}


/* Main */
int main() {
    char **array;
    int size;
    int choice;

    printf("Enter initial number of strings: ");
    scanf("%d", &size);
    getchar(); // consume newline

    array = (char **)malloc(size * sizeof(char *));
    if (!array) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        array[i] = (char *)malloc(MAX_LEN * sizeof(char));
        printf("Enter string %d: ", i + 1);
        fgets(array[i], MAX_LEN, stdin);
        array[i][strcspn(array[i], "\n")] = '\0';
    }

    do {
        printf("\n----- MENU -----\n");
        printf("1. Add string to end\n");
        printf("2. Add string to beginning\n");
        printf("3. Delete string at index\n");
        printf("4. Display array length\n");
        printf("5. Display all strings\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline
        printf("------------------------\n\n");

        switch (choice) {
            case 1:
                addEnd(&array, &size);
                break;
            case 2:
                addBeginning(&array, &size);
                break;
            case 3:
                deleteAtIndex(&array, &size);
                break;
            case 4:
                displayLength(size);
                break;
            case 5:
                displayElements(array, size);
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    freeArray(array, size);
    return 0;
}
