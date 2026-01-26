#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int *leftArr = (int *)malloc(leftSize * sizeof(int));
    int *rightArr = (int *)malloc(rightSize * sizeof(int));
    
    for (int i = 0; i < leftSize; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < rightSize; i++) rightArr[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftSize) arr[k++] = leftArr[i++];
    while (j < rightSize) arr[k++] = rightArr[j++];
    
    free(leftArr);
    free(rightArr);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
void insertionSort(int arr[], int n) {
    // Order of n^2
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

/*
int main() {
    srand(time(NULL));

    // Static array experiment
    printf("=== Static Array (size: %d) ===\n", ARRAY_SIZE);
    int staticArr[ARRAY_SIZE];

    clock_t start = clock();
    generateRandomArray(staticArr, ARRAY_SIZE);
    insertionSort(staticArr, ARRAY_SIZE);
    clock_t end = clock();

    double staticTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %.6e seconds\n\n", staticTime);

    // Dynamic array experiment
    printf("=== Dynamic Array (initial size: 1, final size: %d) ===\n", ARRAY_SIZE);
    int *dynamicArr = (int *)malloc(sizeof(int));
    int capacity = 1;

    start = clock();

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (i >= capacity) {
            capacity *= 2;
            dynamicArr = (int *)realloc(dynamicArr, capacity * sizeof(int));
        }
        dynamicArr[i] = rand() % 100 + 1;
    }
    insertionSort(dynamicArr, ARRAY_SIZE);

    end = clock();

    double dynamicTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %.6e seconds\n", dynamicTime);

    free(dynamicArr);
    return 0;
}
*/