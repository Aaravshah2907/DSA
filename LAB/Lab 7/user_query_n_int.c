#include <stdio.h>
#include <stdlib.h>

int main() {
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

    int k = 0;
    for (int i = 0; i < n; i++){
        if (arr[i]> k) k = arr[i];
    }

    // Step 1: Counting array
    int *count = (int*)calloc(k + 1, sizeof(int));
    
    for (int i = 0; i < n; i++){
        count[arr[i]]++;
    }


    // Step 2: Prefix sum
    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1];
    }


    printf("\nPreprocessing done (Θ(n + k)).\n");

    // Query loop
    while (1) {
        int a, b;
        printf("\nEnter range [a b] (or -1 -1 to exit): ");
        scanf("%d %d", &a, &b);

        if (a == -1 && b == -1)
            break;

        if (a < 0) a = 0;
        if (b > k) b = k;

        int result;
        if (a == 0)
            result = count[b];
        else
            result = count[b] - count[a - 1];

        if (result > 0)
            printf("YES, %d element(s) found in range [%d, %d]\n", result, a, b);
        else
            printf("NO elements found in range [%d, %d]\n", a, b);
    }

    free(arr);
    free(count);

    return 0;
}