#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void segregateZerosOnes(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        if (arr[left] == 0) left++;
        else if (arr[right] == 1) right--;
        else {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++; right--;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr_size;
    printf("Enter Array Size: ");
    scanf("%d", &arr_size);  

    if (arr_size <= 0 || arr_size > MAX_SIZE) {
        printf("Invalid size! Use 1-%d\n", MAX_SIZE);
        return 1;
    }
    
    int *arr = malloc(arr_size * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter %d elements (0s and 1s only):\n", arr_size);
    for (int i = 0; i < arr_size; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Original: "); printArray(arr, arr_size);
    segregateZerosOnes(arr, arr_size);
    printf("Sorted:   "); printArray(arr, arr_size);
    
    free(arr);
    return 0;
}
