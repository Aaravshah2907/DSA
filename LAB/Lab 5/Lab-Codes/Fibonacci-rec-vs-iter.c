#include <stdio.h>
#include <sys/time.h>

long long fibiterative(int n) {
    long long a = 0, b = 1;

    if (n == 0) return 0;
    if (n == 1) return 1;

    for (int i = 2; i <= n; i++) {
        long long temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

long long fibrecursive(int n) {
    if (n <= 1)
        return n;
    return fibrecursive(n - 1) + fibrecursive(n - 2);
}

int main(void) {
    struct timeval t1, t2;
    double time_taken;

    gettimeofday(&t1, NULL);
    fibiterative(40);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec)
               + (t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("Iterative Fibonacci took %f seconds\n", time_taken);

    gettimeofday(&t1, NULL);
    fibrecursive(40);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec)
               + (t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("Recursive Fibonacci took %f seconds\n", time_taken);

    return 0;
}
