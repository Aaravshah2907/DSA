#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void insertionSort(struct person arr[], int n)
{
    for (int i = 1; i < n; i++) {
        struct person key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].height > key.height) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printPersons(struct person arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d %s %d %d %d\n",
               arr[i].id,
               arr[i].name,
               arr[i].age,
               arr[i].height,
               arr[i].weight);
    }
}

int main(void)
{
    int n;
    printf("Enter number of persons: ");
    scanf("%d", &n);

    struct person *people = malloc(n * sizeof(struct person));
    if (people == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        char buffer[100];

        printf("\nPerson %d\n", i + 1);

        printf("ID: ");
        scanf("%d", &people[i].id);

        printf("Name: ");
        scanf("%s", buffer);
        people[i].name = malloc(strlen(buffer) + 1);
        strcpy(people[i].name, buffer);

        printf("Age: ");
        scanf("%d", &people[i].age);

        printf("Height: ");
        scanf("%d", &people[i].height);

        printf("Weight: ");
        scanf("%d", &people[i].weight);
    }

    insertionSort(people, n);

    printf("\nSorted data (by height):\n");
    printPersons(people, n);

    for (int i = 0; i < n; i++) {
        free(people[i].name);
    }
    free(people);

    return 0;
}
