#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME 30
 
// Task 1

struct student {
    long long int ID;
    char name[MAX_NAME];
};

struct node {
    struct student data;
    struct node *next;
};

struct node* create_node(struct student s) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = s;
    newNode->next = NULL;
    return newNode;
}

int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int prime_less_than(int n) {
    for (int i = n - 1; i >= 2; i--)
        if (isPrime(i))
            return i;
    return 2;
}

int power_of_2_less_than(int n) {
    int p = 1;
    while (p * 2 < n)
        p *= 2;
    return p;
}

int multiplicative_hash(long long int key, int m) {
    double A = 0.6180339887;
    double frac = key * A - floor(key * A);
    return (int)(m * frac);
}

int insert(struct node** table, int index, struct student s) {
    int collision = 0;

    if (table[index] != NULL)
        collision = 1;   // Collision occurs

    struct node* newNode = create_node(s);
    newNode->next = table[index];
    table[index] = newNode;

    return collision;
}

void free_table(struct node** table, int size) {
    for (int i = 0; i < size; i++) {
        struct node* temp = table[i];
        while (temp) {
            struct node* t = temp;
            temp = temp->next;
            free(t);
        }
    }
    free(table);
}

int main() {

    FILE *file = fopen("t1_data.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    int N;
    fscanf(file, "%d", &N);

    int size = 2 * N;

    struct student *students = 
        (struct student*)malloc(N * sizeof(struct student));

    if (!students) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fscanf(file, "%lld,%29[^\n]",
               &students[i].ID,
               students[i].name);
    }

    fclose(file);

    int collisions[6] = {0};

    int prime_size = prime_less_than(size);
    int power2 = power_of_2_less_than(size);
    int prime_09 = prime_less_than((int)(0.9 * size));

    for (int h = 0; h < 6; h++) {

        struct node** table =
            (struct node**)calloc(size, sizeof(struct node*));

        if (!table) {
            printf("Memory allocation failed\n");
            return 1;
        }

        for (int i = 0; i < N; i++) {

            int index = 0;

            switch (h) {
                case 0:
                    index = students[i].ID % size;
                    break;

                case 1:
                    index = students[i].ID % power2;
                    break;

                case 2:
                    index = students[i].ID % prime_size;
                    break;

                case 3:
                    index = multiplicative_hash(students[i].ID, size);
                    break;

                case 4:
                    index = students[i].ID % prime_09;
                    break;

                case 5:
                    index = (students[i].ID * prime_size) % size;
                    break;
            }

            collisions[h] += insert(table, index, students[i]);
        }

        free_table(table, size);
    }

    free(students);

    printf("===== Collision Results =====\n");
    printf("1. ID %% size: %d\n", collisions[0]);
    printf("2. ID %% power_of_2_less_than_size: %d\n", collisions[1]);
    printf("3. ID %% prime_less_than_size: %d\n", collisions[2]);
    printf("4. Multiplicative hash: %d\n", collisions[3]);
    printf("5. ID %% prime_less_than_0.9_size: %d\n", collisions[4]);
    printf("6. (ID * prime_less_than_size) %% size: %d\n", collisions[5]);

    return 0;
}