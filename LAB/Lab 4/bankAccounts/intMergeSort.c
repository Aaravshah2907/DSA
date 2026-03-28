#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "intMerge.h"

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    
    FILE *fp = fopen("balances.txt", "r");
    if (!fp) return 1;

    // Use your previous realloc logic here to load balances
    int capacity = 1000;
    int *balances = malloc(capacity * sizeof(int));
    int count = 0;
    while (fscanf(fp, "%d", &balances[count]) == 1) {
        count++;
        if (count >= capacity) {
            capacity *= 2;
            balances = realloc(balances, capacity * sizeof(int));
        }
    }
    fclose(fp);

    clock_t start = clock();
    mergeSort(balances, 0, count - 1);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sorted %d balances in %f seconds\n", count, time_taken);

    // Export result for your .dat file
    FILE *fout = fopen("benchmarks.dat", "a");
    fprintf(fout, "MergeSort\t%d\t%f\n", count, time_taken);
    fclose(fout);

    free(balances);
    return 0;
}