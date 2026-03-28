#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

unsigned long long factNTR(unsigned long long n){
    if (n == 0) return 1;
    else {
        return n * factNTR(n-1);
    }
}

unsigned long long factTR(unsigned long long n, unsigned long long acc){
    if (n == 0) return acc;
    else {
        return factTR(n-1, n * acc);
    }
}

unsigned long long factI(unsigned long long n){
    unsigned long long acc =1;
    while (n > 0)
    {
        acc = acc * n;
        n = n - 1;
    }
    
    return acc;
}

int main(void)
{
    unsigned long long n;
    struct timeval t1, t2;
    double time_taken;

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1 || n < 0) {
        printf("Invalid input\n");
        return 1;
    }

    /* Non-tail recursive factorial */
    gettimeofday(&t1, NULL);
    unsigned long long res_ntr = factNTR(n);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("factNTR(%lld) = %lld, time = %f seconds\n", n, res_ntr, time_taken);

    /* Tail-recursive factorial */
    gettimeofday(&t1, NULL);
    unsigned long long res_tr = factTR(n, 1);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("factTR(%lld) = %lld, time = %f seconds\n", n, res_tr, time_taken);

    /* Iterative factorial */
    gettimeofday(&t1, NULL);
    unsigned long long res_i = factI(n);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("factI(%lld) = %lld, time = %f seconds\n", n, res_i, time_taken);

    return 0;
}
