#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1000000
#define DEFAULT_THRESHOLD 10

// Lomuto partition scheme
int lomuto_partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
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

// Insertion sort
void insertion_sort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// === METHOD 1: Hybrid Quicksort (Insertion sort on small subarrays) ===
void qsort_hybrid(int arr[], int low, int high, int threshold) {
    if (high - low < threshold) {
        insertion_sort(arr, low, high);
        return;
    }
    if (low < high) {
        // Median-of-3 pivot
        int mid = low + (high - low) / 2;
        if (arr[low] > arr[mid]) { int t = arr[low]; arr[low] = arr[mid]; arr[mid] = t; }
        if (arr[low] > arr[high]) { int t = arr[low]; arr[low] = arr[high]; arr[high] = t; }
        if (arr[mid] > arr[high]) { int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t; }
        int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t;
        
        int p = lomuto_partition(arr, low, high);
        qsort_hybrid(arr, low, p - 1, threshold);
        qsort_hybrid(arr, p + 1, high, threshold);
    }
}

// === METHOD 2: QuickSort + Final Insertion Sort (Post-processing) ===
void quicksort_final_insertion(int arr[], int low, int high) {
    if (low < high) {
        // Median-of-3 pivot (same as above)
        int mid = low + (high - low) / 2;
        if (arr[low] > arr[mid]) { int t = arr[low]; arr[low] = arr[mid]; arr[mid] = t; }
        if (arr[low] > arr[high]) { int t = arr[low]; arr[low] = arr[high]; arr[high] = t; }
        if (arr[mid] > arr[high]) { int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t; }
        int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t;
        
        int p = lomuto_partition(arr, low, high);
        quicksort_final_insertion(arr, low, p - 1);
        quicksort_final_insertion(arr, p + 1, high);
    }
}

double time_hybrid(int* original, int n, int threshold) {
    int* copy = malloc(n * sizeof(int));
    memcpy(copy, original, n * sizeof(int));
    clock_t start = clock();
    qsort_hybrid(copy, 0, n-1, threshold);
    clock_t end = clock();
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
}

double time_quick_final_insert(int* original, int n) {
    int* copy = malloc(n * sizeof(int));
    memcpy(copy, original, n * sizeof(int));
    clock_t start = clock();
    quicksort_final_insertion(copy, 0, n-1);
    insertion_sort(copy, 0, n-1);
    clock_t end = clock();
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
}

double time_vanilla(int* original, int n) {
    int* copy = malloc(n * sizeof(int));
    memcpy(copy, original, n * sizeof(int));
    clock_t start = clock();
    qsort_hybrid(copy, 0, n-1, n+1);  // No insertion sort
    clock_t end = clock();
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
}

int* read_txt_file(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    int* arr = malloc(MAX_SIZE * sizeof(int));
    *count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) && *count < MAX_SIZE) {
        int num;
        if (sscanf(line, "%d", &num) == 1) {
            arr[(*count)++] = num;
        }
    }
    fclose(file);
    
    int* final_arr = malloc(*count * sizeof(int));
    memcpy(final_arr, arr, *count * sizeof(int));
    free(arr);
    return final_arr;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file.txt>\n", argv[0]);
        return 1;
    }
    
    int n;
    int threshold = 10;
    int* data = read_txt_file(argv[1], &n);
    if (!data || n == 0) {
        printf("Failed to read %s\n", argv[1]);
        return 1;
    }
    
    printf("Hybrid QuickSort Comparison:\n\n");
    printf("%-20s %10s\n", "Method", "Time (ms)");
    printf("%-20s %10s\n", "------", "--------");
    
    // FIXED CALLS - No function pointer issues
    double t1 = time_hybrid(data, n, threshold);
    double t2 = time_quick_final_insert(data, n);
    double t3 = time_vanilla(data, n);
    
    printf("%-20s %8.2f\n", "Hybrid (threshold=10)", t1);  // %d then %f
    printf("%-20s %8.2f\n", "Quick+Final-Insertion", t2);
    printf("%-20s %8.2f\n", "Vanilla QuickSort", t3);
    
    free(data);
    return 0;
}