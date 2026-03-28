#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Compile with flag -lm

void countingSort(int arr[], int n, int place)
{
    int output[n];        // temporary array
    int count[10] = {0};  // digits 0–9

    // Step 1: Count occurrences of digits at given place
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / place) % 10;
        count[digit]++;/* code */
    }

    // Step 2: Compute cumulative count (prefix sum)
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Step 3: Build output array (RIGHT to LEFT for stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / place) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Step 4: Copy back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

int main(int argc, char const *argv[])
{

    FILE *file = fopen("n_integers.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);   // first number = length of array

    int *arr = (int*)malloc(n * sizeof(int));

    fscanf(file, ",[");

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    int max = INT_MIN;
    for (int i = 0; i < n; i++){
        if (arr[i] > max) max = arr[i]; 
    }

    int length = ceil(log10(max));
    printf("Max Length : %d\n ", length);
    
    for (int i = 1; i <= max; i++){
        countingSort(arr, n, i);
    }

    
    printf("Array : ");
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
