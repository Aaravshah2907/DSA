#include <stdlib.h>
#include <string.h>
#include "personMerge.h"

void personMergeAuxIter(struct person arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    struct person *L = malloc(n1 * sizeof(struct person));
    struct person *R = malloc(n2 * sizeof(struct person));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        // Sorting by height as the key field
        if (L[i].height <= R[j].height) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}