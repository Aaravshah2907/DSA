#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct person {
    int id;
    char name[256];
    int age;
    int height;
    int weight;
};

// Function to export the results for graphing
void exportResults(long long n, double time_taken) {
    FILE *fout = fopen("benchmarks.dat", "a"); // "a" for append mode
    if (fout) {
        fprintf(fout, "%lld\t%f\n", n, time_taken);
        fclose(fout);
    }
}

void insertionSort(struct person *arr, long long n) {
    for (long long i = 1; i < n; i++) {
        struct person key = arr[i];
        long long j = i - 1;
        while (j >= 0 && arr[j].height > key.height) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *fp = fopen(argv[1], "r");
    if (!fp) return 1;

    long long capacity = 100; // Start with 100
    struct person *students = malloc(capacity * sizeof(struct person));
    long long count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), fp)) {
        // Cleaning line endings to handle LF/CRLF
        line[strcspn(line, "\r\n")] = 0;

        // Check if we need to expand memory
        if (count >= capacity) {
            capacity *= 2; // Double the capacity
            struct person *temp = realloc(students, capacity * sizeof(struct person));
            if (!temp) {
                printf("Memory allocation failed!\n");
                free(students);
                fclose(fp);
                return 1;
            }
            students = temp;
        }

        if (sscanf(line, "%d,%[^,],%d,%d,%d", 
            &students[count].id, 
            students[count].name, 
            &students[count].age, 
            &students[count].height, 
            &students[count].weight) == 5) {
                count++;
        }
    }
    fclose(fp);

    printf("Total records loaded: %lld\n", count);

    if (count > 0) {
        clock_t start = clock();
        insertionSort(students, count);
        clock_t end = clock();
        
        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Sort Time for %lld entries: %f seconds\n", count, time_taken);
        
        // Export to .dat file
        exportResults(count, time_taken);
    }

    free(students);
    return 0;
}