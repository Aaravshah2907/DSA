#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 10000000

// Lomuto partition scheme (standard)
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

// QuickSort implementations with different pivot selections
void quicksort_first(int arr[], int low, int high) {
    if (low < high) {
        // First element as pivot
        int pivot_idx = low;
        int temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
        int p = lomuto_partition(arr, low, high);
        quicksort_first(arr, low, p - 1);
        quicksort_first(arr, p + 1, high);
    }
}

void quicksort_last(int arr[], int low, int high) {
    if (low < high) {
        // Last element as pivot (default Lomuto)
        int p = lomuto_partition(arr, low, high);
        quicksort_last(arr, low, p - 1);
        quicksort_last(arr, p + 1, high);
    }
}

void quicksort_median3(int arr[], int low, int high) {
    if (low < high) {
        // Median of first, middle, last
        int mid = low + (high - low) / 2;
        if (arr[low] > arr[mid]) {
            int temp = arr[low]; arr[low] = arr[mid]; arr[mid] = temp;
        }
        if (arr[low] > arr[high]) {
            int temp = arr[low]; arr[low] = arr[high]; arr[high] = temp;
        }
        if (arr[mid] > arr[high]) {
            int temp = arr[mid]; arr[mid] = arr[high]; arr[high] = temp;
        }
        // Put median at end
        int temp = arr[mid]; arr[mid] = arr[high]; arr[high] = temp;
        
        int p = lomuto_partition(arr, low, high);
        quicksort_median3(arr, low, p - 1);
        quicksort_median3(arr, p + 1, high);
    }
}

int random_pivot(int low, int high) {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    return low + rand() % (high - low + 1);
}

void quicksort_random(int arr[], int low, int high) {
    if (low < high) {
        // Random pivot
        int pivot_idx = random_pivot(low, high);
        int temp = arr[pivot_idx];
        arr[pivot_idx] = arr[high];
        arr[high] = temp;
        int p = lomuto_partition(arr, low, high);
        quicksort_random(arr, low, p - 1);
        quicksort_random(arr, p + 1, high);
    }
}

// Timing function
double time_sort(void (*sort_func)(int*, int, int), int* original, int n) {
    int* copy = malloc(n * sizeof(int));
    if (!copy) return -1;
    
    memcpy(copy, original, n * sizeof(int));
    
    clock_t start = clock();
    sort_func(copy, 0, n - 1);
    clock_t end = clock();
    
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0; // ms
}

// Read .txt file (1 number per line)
int* read_txt_file(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening %s\n", filename);
        *count = 0;
        return NULL;
    }
    
    int* arr = malloc(MAX_SIZE * sizeof(int));
    if (!arr) {
        fclose(file);
        *count = 0;
        return NULL;
    }
    
    *count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) && *count < MAX_SIZE) {
        int num;
        if (sscanf(line, "%d", &num) == 1) {
            arr[(*count)++] = num;
        }
    }
    fclose(file);
    
    // Resize to exact size
    int* final_arr = malloc(*count * sizeof(int));
    if (final_arr) {
        memcpy(final_arr, arr, *count * sizeof(int));
        free(arr);
        return final_arr;
    }
    free(arr);
    *count = 0;
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file.txt>\n", argv[0]);
        printf("Example: %s int1000.txt\n", argv[0]);
        return 1;
    }
    
    int n;
    int* data = read_txt_file(argv[1], &n);
    if (!data || n == 0) {
        printf("Failed to read %s\n", argv[1]);
        return 1;
    }
    
    printf("Loaded %d integers from %s\n", n, argv[1]);
    printf("Comparing QuickSort pivot selection methods:\n\n");
    
    printf("%-12s %10s\n", "Method", "Time (ms)");
    printf("%-12s %10s\n", "------", "--------");
    
    double t1 = time_sort(quicksort_first, data, n);
    printf("%-12s %8.2f\n", "First", t1);
    
    double t2 = time_sort(quicksort_last, data, n);
    printf("%-12s %8.2f\n", "Last", t2);
    
    double t3 = time_sort(quicksort_median3, data, n);
    printf("%-12s %8.2f\n", "Median-3", t3);
    
    double t4 = time_sort(quicksort_random, data, n);
    printf("%-12s %8.2f\n", "Random", t4);
    
    // Find fastest
    double times[4] = {t1, t2, t3, t4};
    double min_time = times[0];
    int best = 0;
    for (int i = 1; i < 4; i++) {
        if (times[i] < min_time) {
            min_time = times[i];
            best = i;
        }
    }
    
    char* methods[] = {"First", "Last", "Median-3", "Random"};
    printf("\n**Fastest: %s (%.1fms)**\n", methods[best], min_time);
    
    free(data);
    return 0;
}
