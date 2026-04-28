#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// Task 2

#define TABLE_SIZE 1024
#define MAX_NAME 30

struct student {
    long long int ID;
    char name[MAX_NAME];
};

enum status { EMPTY, FILLED, DELETED };

struct hash_table_element {
    struct student data;
    enum status flag;
};

int multiplicative_hash(long long int key, int m) {
    double A = 0.6180339887;
    double frac = key * A - floor(key * A);
    return (int)(m * frac);
}

int hash(long long int ID, int m, int i, int method) {

    int h1, h2;

    switch(method) {

        case 1:
            // Linear Probing
            h1 = multiplicative_hash(ID, m);
            return (h1 + i) % m;

        case 2:
            // Quadratic Probing
            h1 = multiplicative_hash(ID, m);
            return (h1 + i*i) % m;

        case 3:
            // Double Hashing
            h1 = multiplicative_hash(ID, m);
            h2 = 1 + (ID % 1023);
            return (h1 + i * h2) % m;

        case 4:
            // Double Hashing (different h1)
            h1 = ID % 1024;
            h2 = 1 + (ID % 1023);
            return (h1 + i * h2) % m;
    }

    return 0;
}

void insert(struct hash_table_element *table, struct student *stud, int m, int *collision_count, int method) {
    for (int i = 0; i < m; i++) {
        int index = hash(stud->ID, m, i, method);
        if (table[index].flag == EMPTY ||
            table[index].flag == DELETED) {

            table[index].data = *stud;
            table[index].flag = FILLED;
            return;
        }
        (*collision_count)++;
    }
    printf("Table is full!\n");
}

void delete(struct hash_table_element *table, long long int ID, int m, int *collision_count, int method) {
    for (int i = 0; i < m; i++) {
        int index = hash(ID, m, i, method);
        if (table[index].flag == EMPTY)
            return;
        if (table[index].flag == FILLED &&
            table[index].data.ID == ID) {

            table[index].flag = DELETED;
            return;
        }
        (*collision_count)++;
    }
}

struct student *search(struct hash_table_element *table, long long int ID, int m, int *collision_count, int method) {
    for (int i = 0; i < m; i++) {
        int index = hash(ID, m, i, method);
        if (table[index].flag == EMPTY)
            return NULL;
        if (table[index].flag == FILLED &&
            table[index].data.ID == ID)
            return &table[index].data;
        (*collision_count)++;
    }
    return NULL;
}

int main() {

    for (int method = 1; method <= 4; method++) {
        struct hash_table_element table[TABLE_SIZE];

        for (int i = 0; i < TABLE_SIZE; i++)
            table[i].flag = EMPTY;
        int total_collisions = 0;
        int total_operations = 0;

        FILE *data_file = fopen("t1_data.txt", "r");
        if (!data_file) {
            printf("Cannot open t1_data.txt\n");
            return 1;
        }

        int N;
        fscanf(data_file, "%d", &N);

        for (int i = 0; i < N; i++) {
            struct student s;
            fscanf(data_file, "%lld,%29[^\n]", &s.ID, s.name);
            insert(table, &s, TABLE_SIZE, &total_collisions, method);
            total_operations++;
        }

        fclose(data_file);
        FILE *query_file = fopen("t1_queries.txt", "r");
        if (!query_file) {
            printf("Cannot open t1_queries.txt\n");
            return 1;
        }

        int op;
        char buffer[100];

        while (fscanf(query_file, "%d ", &op) != EOF) {
            total_operations++;
            if (op == 1) {  // INSERT
                struct student s;
                fscanf(query_file, "%lld,%29[^\n]", &s.ID, s.name);
                insert(table, &s, TABLE_SIZE, &total_collisions, method);
            }

            else if (op == 2) {  // DELETE
                long long int ID;
                fscanf(query_file, "%lld", &ID);
                delete(table, ID, TABLE_SIZE, &total_collisions, method);
            }

            else if (op == 3) {  // SEARCH
                long long int ID;
                fscanf(query_file, "%lld", &ID);

                search(table, ID, TABLE_SIZE, &total_collisions, method);
            }
            fgets(buffer, sizeof(buffer), query_file);
        }

        fclose(query_file);

        printf("\nMethod %d Results:\n", method);
        printf("Total Collisions: %d\n", total_collisions);
        printf("Average Collisions per Operation: %.3f\n", (double)total_collisions / total_operations);
    }
    return 0;
}