#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "personMerge.h"

void mergeSort(struct person arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *fp = fopen(argv[1], "r");
    if (!fp) return 1;

    int capacity = 100;
    struct person *students = malloc(capacity * sizeof(struct person));
    int count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0; // Handle CRLF
        if (strlen(line) < 5) continue;

        if (count >= capacity) {
            capacity *= 2;
            students = realloc(students, capacity * sizeof(struct person));
        }

        if (sscanf(line, "%d,%[^,],%d,%d,%d", 
            &students[count].id, students[count].name, 
            &students[count].age, &students[count].height, 
            &students[count].weight) == 5) {
            count++;
        }
    }
    fclose(fp);

    clock_t start = clock();
    mergeSort(students, 0, count - 1);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("N=%d | Time: %f s\n", count, time_taken);

    // Export for graphing
    FILE *fout = fopen("mergesort_benchmarks.dat", "a");
    if(fout) {
        fprintf(fout, "%d\t%f\n", count, time_taken);
        fclose(fout);
    }

    free(students);
    return 0;
}