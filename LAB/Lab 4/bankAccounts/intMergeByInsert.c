#include "intMerge.h"

void merge(int arr[], int l, int m, int r) {
    int start2 = m + 1;
    if (arr[m] <= arr[start2]) return;

    while (l <= m && start2 <= r) {
        if (arr[l] <= arr[start2]) {
            l++;
        } else {
            int value = arr[start2];
            int index = start2;
            while (index != l) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[l] = value;
            l++; m++; start2++;
        }
    }
}