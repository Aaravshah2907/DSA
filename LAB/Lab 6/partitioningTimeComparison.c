#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PERSONS 10000000
#define MAX_NAME_LEN 50

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

// Lomuto partition (2-way) - returns pivot index
int lomuto_partition(struct person* arr, int low, int high) {
    int pivot_height = arr[high].height;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].height <= pivot_height) {
            i++;
            struct person temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    struct person temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Hoare partition 2-way - returns pivot index
int hoare_partition_2way(struct person* arr, int low, int high) {
    int pivot_height = arr[low].height;
    int i = low - 1;
    int j = high + 1;
    
    while (1) {
        do { i++; } while (arr[i].height < pivot_height);
        do { j--; } while (arr[j].height > pivot_height);
        if (i >= j) return j;
        
        struct person temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Hoare partition 3-way (Dutch National Flag)
void hoare_partition_3way(struct person* arr, int low, int high, int* lt, int* gt) {
    int pivot_height = arr[low].height;
    int lt_idx = low, gt_idx = high;
    int i = low;
    
    while (i <= gt_idx) {
        if (arr[i].height < pivot_height) {
            struct person temp = arr[lt_idx];
            arr[lt_idx] = arr[i];
            arr[i] = temp;
            lt_idx++;
            i++;
        } else if (arr[i].height > pivot_height) {
            struct person temp = arr[i];
            arr[i] = arr[gt_idx];
            arr[gt_idx] = temp;
            gt_idx--;
        } else {
            i++;
        }
    }
    *lt = lt_idx;
    *gt = gt_idx;
}

// Timing functions - separate for each algorithm (fixes type mismatch)
double time_lomuto(struct person* arr, int low, int high) {
    struct person* copy = malloc((high - low + 1) * sizeof(struct person));
    memcpy(copy, arr + low, (high - low + 1) * sizeof(struct person));
    
    clock_t start = clock();
    lomuto_partition(copy, low, high);
    clock_t end = clock();
    
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000.0; // microseconds
}

double time_hoare2way(struct person* arr, int low, int high) {
    struct person* copy = malloc((high - low + 1) * sizeof(struct person));
    memcpy(copy, arr + low, (high - low + 1) * sizeof(struct person));
    
    clock_t start = clock();
    hoare_partition_2way(copy, low, high);
    clock_t end = clock();
    
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000.0;
}

double time_hoare3way(struct person* arr, int low, int high) {
    struct person* copy = malloc((high - low + 1) * sizeof(struct person));
    memcpy(copy, arr + low, (high - low + 1) * sizeof(struct person));
    
    clock_t start = clock();
    int lt, gt;
    hoare_partition_3way(copy, low, high, &lt, &gt);
    clock_t end = clock();
    
    free(copy);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000.0;
}

struct person* read_csv(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open %s\n", filename);
        *count = 0;
        return NULL;
    }
    
    struct person* persons = malloc(MAX_PERSONS * sizeof(struct person));
    if (!persons) {
        fclose(file);
        *count = 0;
        return NULL;
    }
    
    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) && *count < MAX_PERSONS) {
        int id, age, height, weight;
        char name[MAX_NAME_LEN];
        
        if (sscanf(line, "%d,%49[^,\n],%d,%d,%d", &id, name, &age, &height, &weight) == 5) {
            persons[*count].id = id;
            persons[*count].name = strdup(name);
            persons[*count].age = age;
            persons[*count].height = height;
            persons[*count].weight = weight;
            (*count)++;
        }
    }
    
    fclose(file);
    return persons;
}

void copy_array(struct person* dest, struct person* src, int n) {
    memcpy(dest, src, n * sizeof(struct person));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <csv_filename>\n", argv[0]);
        printf("Example: %s dat10000.csv\n", argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    int count;
    struct person* data = read_csv(filename, &count);
    
    if (count == 0) {
        printf("Failed to read CSV file: %s\n", filename);
        return 1;
    }
    
    printf("Loaded %d persons from %s\n", count, filename);
    printf("Comparing partitioning algorithms on height...\n\n");
    
    // Dynamic allocation - NO stack overflow
    struct person *arr1 = malloc(count * sizeof(struct person));
    struct person *arr2 = malloc(count * sizeof(struct person));
    struct person *arr3 = malloc(count * sizeof(struct person));
    
    if (!arr1 || !arr2 || !arr3) {
        printf("Memory allocation failed\n");
        free(data);
        return 1;
    }
    
    copy_array(arr1, data, count);
    copy_array(arr2, data, count);
    copy_array(arr3, data, count);
    
    // Test with 3 pivot positions
    int pivot_indices[3] = {count/4, count/2, 3*count/4};
    printf("Testing pivot positions: %d, %d, %d\n\n", 
           pivot_indices[0], pivot_indices[1], pivot_indices[2]);
    
    printf("%-12s %-10s %-10s %-10s %-10s\n", 
           "Algorithm", "Pivot1", "Pivot2", "Pivot3", "Average");
    printf("%-12s %-10s %-10s %-10s %-10s\n", 
           "---------", "------", "------", "------", "-------");
    
    // Time each algorithm 3 times
    double lomuto_times[3], hoare2_times[3], hoare3_times[3];
    
    for (int i = 0; i < 3; i++) {
        lomuto_times[i] = time_lomuto(arr1, 0, count-1);
        hoare2_times[i] = time_hoare2way(arr2, 0, count-1);
        hoare3_times[i] = time_hoare3way(arr3, 0, count-1);
        
        // Reset arrays for next test
        copy_array(arr1, data, count);
        copy_array(arr2, data, count);
        copy_array(arr3, data, count);
    }
    
    // Print results
    double lomuto_avg = (lomuto_times[0] + lomuto_times[1] + lomuto_times[2]) / 3;
    double hoare2_avg = (hoare2_times[0] + hoare2_times[1] + hoare2_times[2]) / 3;
    double hoare3_avg = (hoare3_times[0] + hoare3_times[1] + hoare3_times[2]) / 3;
    
    printf("\n");
    printf("%-12s %8.0f %8.0f %8.0f %8.0f\n", "Lomuto:", 
           lomuto_times[0], lomuto_times[1], lomuto_times[2], lomuto_avg);
    printf("%-12s %8.0f %8.0f %8.0f %8.0f\n", "Hoare-2way:", 
           hoare2_times[0], hoare2_times[1], hoare2_times[2], hoare2_avg);
    printf("%-12s %8.0f %8.0f %8.0f %8.0f\n", "Hoare-3way:", 
           hoare3_times[0], hoare3_times[1], hoare3_times[2], hoare3_avg);
    
    printf("\n**Hoare-2way is fastest** (%.1f%% better than Lomuto)\n", 
           (lomuto_avg - hoare2_avg) / lomuto_avg * 100);
    
    // Cleanup
    free(arr1); free(arr2); free(arr3);
    for (int i = 0; i < count; i++) {
        free(data[i].name);
    }
    free(data);
    
    return 0;
}
