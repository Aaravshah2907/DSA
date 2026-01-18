#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "firstNPrimes.c"

double timeCalc(int (*func)(int), int n){
    struct timeval t1, t2;
    double time_taken;
    gettimeofday(&t1, NULL);
    func(n);
    gettimeofday(&t2, NULL);

    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    return time_taken;
}

void main(){

    
    int n = 100000;
    double time_taken = 0.0;

    FILE *fp = fopen("primes_counter_sample.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    
    for (int i = 1; i < n; i*=10){
        printf("Executing %d\n", i);
        time_taken = timeCalc(firstNPrimesToFile, i);
        fprintf(fp, "%d: %f seconds", i, time_taken);
        fprintf(fp, "\n");
    }
    fclose(fp);

    printf("The tasks took %f seconds to execute\n", time_taken);
}