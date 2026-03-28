#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void insertionSortR(long long *arr, long long n){
    if (n <= 1) return;
    insertionSortR(arr, n-1);
    long long last = arr[n-1];
    long long j = n-2;
    while (j >= 0 && arr[j] > last){
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = last;
}

void insertionSortI(long long *arr, long long n){
    for (long long i = 1; i < n; i++){
        long long last = arr[i];
        long long j = i-1;
        while (j >= 0 && arr[j] > last){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = last;
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    long long capacity = 1000;
    long long size = 0;

    long long *numbers = malloc(capacity * sizeof(long long));
    long long *numbers_copy = malloc(capacity * sizeof(long long));

    if (numbers == NULL || numbers_copy == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        return 1;
    }

    while (fscanf(fp, "%lld", &numbers[size]) != EOF) {
        if (size == capacity) {
            capacity *= 2;

            long long *temp1 = realloc(numbers, capacity * sizeof(long long));
            long long *temp2 = realloc(numbers_copy, capacity * sizeof(long long));

            if (temp1 == NULL || temp2 == NULL) {
                perror("Memory reallocation failed");
                free(numbers);
                free(numbers_copy);
                fclose(fp);
                return 1;
            }

            numbers = temp1;
            numbers_copy = temp2;
        }

        numbers_copy[size] = numbers[size];
        size++;
    }
    fclose(fp);

    struct timeval t1, t2;
    double time_taken;

    /* Iterative insertion sort */
    gettimeofday(&t1, NULL);
    insertionSortI(numbers, size);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec)
               + (t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("Iterative insertion sort took %f seconds\n", time_taken);

    /* Recursive insertion sort */
    gettimeofday(&t1, NULL);
    insertionSortR(numbers_copy, size);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec)
               + (t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("Recursive insertion sort took %f seconds\n", time_taken);

    free(numbers);
    free(numbers_copy);

    return 0;
}
