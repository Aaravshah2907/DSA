#include "intMergeAux.h"

void recursiveMerge(int arr[], int l, int m, int r, int temp[], int i, int j, int k) {
    if (i > m && j > r) return;

    if (i <= m && (j > r || arr[i] <= arr[j])) {
        temp[k] = arr[i];
        recursiveMerge(arr, l, m, r, temp, i + 1, j, k + 1);
    } else {
        temp[k] = arr[j];
        recursiveMerge(arr, l, m, r, temp, i, j + 1, k + 1);
    }
}

void mergeAux(int arr[], int l, int m, int r) {
    int size = r - l + 1;
    int *temp = malloc(size * sizeof(int));
    recursiveMerge(arr, l, m, r, temp, l, m + 1, 0);
    for (int i = 0; i < size; i++) arr[l + i] = temp[i];
    free(temp);
}