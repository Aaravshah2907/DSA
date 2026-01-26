#include "driver.c"

int main()
{
    srand(time(NULL));

    // Static array experiment
    printf("=== Static Array (size: %d) ===\n", ARRAY_SIZE);
    int staticArr[ARRAY_SIZE];

    clock_t start = clock();
    generateRandomArray(staticArr, ARRAY_SIZE);
    selectionSort(staticArr, ARRAY_SIZE);
    clock_t end = clock();

    double staticTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %.6e seconds\n\n", staticTime);

    // Dynamic array experiment
    printf("=== Dynamic Array (initial size: 1, final size: %d) ===\n", ARRAY_SIZE);
    int *dynamicArr = (int *)malloc(sizeof(int));
    int capacity = 1;

    start = clock();

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (i >= capacity)
        {
            capacity *= 2;
            dynamicArr = (int *)realloc(dynamicArr, capacity * sizeof(int));
        }
        dynamicArr[i] = rand() % 100 + 1;
    }
    selectionSort(dynamicArr, ARRAY_SIZE);

    end = clock();

    double dynamicTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %.6e seconds\n", dynamicTime);

    free(dynamicArr);
    return 0;
}