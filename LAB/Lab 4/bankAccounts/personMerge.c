#include "personMerge.h"

void mergeSort(struct person arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(struct person arr[], int l, int m, int r) {
    personMergeAuxIter(arr, l, m, r);
}