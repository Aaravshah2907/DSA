#include <stdio.h>
#include <stdlib.h>

// Function to find MSB (Most Significant Bit) position
int findMSB(unsigned int x) {
    int msb = 0;
    while (x >>= 1) msb++;
    return msb;
}

void radixExchangeSort(unsigned int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;

    int i = left, j = right;

    while (i <= j) {
        // Move i forward if current bit is 0
        while (i <= j && ((arr[i] >> bit) & 1) == 0) i++;
        // Move j backward if current bit is 1
        while (i <= j && ((arr[j] >> bit) & 1) == 1) j--;

        if (i < j) {
            unsigned int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    // Recur for 0-bit partition
    radixExchangeSort(arr, left, j, bit - 1);
    // Recur for 1-bit partition
    radixExchangeSort(arr, i, right, bit - 1);
}

int main() {
    FILE *file = fopen("n_integers.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);   // first number = length of array

    unsigned int *arr = (int*)malloc(n * sizeof(int));

    fscanf(file, ",[");

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    // Find maximum to get MSB
    unsigned int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    int msb = findMSB(max);

    radixExchangeSort(arr, 0, n - 1, msb);

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++)
        printf("%u ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}