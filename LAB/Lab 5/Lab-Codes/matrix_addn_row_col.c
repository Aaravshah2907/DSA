#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int **generateMatrix(int n)
{
    int **matrix = malloc(n * sizeof(int *));
    if (!matrix) return NULL;

    int *data = malloc(n * n * sizeof(int));
    if (!data) {
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < n; i++)
        matrix[i] = data + i * n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand() % n;  // smaller numbers for clarity

    return matrix;
}

int **RowAddition(int **A, int **B, int n)
{
    int **C = malloc(n * sizeof(int *));
    int *data = malloc(n * n * sizeof(int));
    for (int i = 0; i < n; i++)
        C[i] = data + i * n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

int **ColAddition(int **A, int **B, int n)
{
    int **C = malloc(n * sizeof(int *));
    int *data = malloc(n * n * sizeof(int));
    for (int i = 0; i < n; i++)
        C[i] = data + i * n;

    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

void printMatrix(int **matrix, int n)
{
    if (!matrix) return;
    printf("------------\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void freeMatrix(int **matrix)
{
    if (!matrix) return;
    free(matrix[0]);  // free data block
    free(matrix);     // free row pointers
}

int main()
{
    int n;
    printf("Enter matrix size n: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int **A = generateMatrix(n);
    int **B = generateMatrix(n);

    struct timeval start, end;
    long long microseconds;

    gettimeofday(&start, NULL);
    int **ROW = RowAddition(A, B, n);
    gettimeofday(&end, NULL);
    microseconds = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
    printf("Row addition time: %lld microseconds\n", microseconds);

    gettimeofday(&start, NULL);
    int **COL = ColAddition(A, B, n);
    gettimeofday(&end, NULL);
    microseconds = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
    printf("Column addition time: %lld microseconds\n", microseconds);

    // Optional: print matrices
    //printMatrix(A,n);
    //printMatrix(B,n);
    //printMatrix(ROW, n);
    //printMatrix(COL, n);

    // Free memory
    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(ROW);
    freeMatrix(COL);

    return 0;
}
