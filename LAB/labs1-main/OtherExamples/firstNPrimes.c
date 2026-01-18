#include <stdio.h>

int firstNPrimes(int n)
{
    int count = 0;
    int num = 2;

    while (count < n)
    {
        int isPrime = 1;

        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0)
            {
                isPrime = 0;
                break;
            }
        }

        if (isPrime)
        {
            printf("%d ", num);
            count++;
        }

        num++;
    }
    printf("\n");
    return 0;
}

int firstNPrimesToFile(int n)
{
    FILE *fp = fopen("primes.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }

    int count = 0;
    int num = 2;

    while (count < n)
    {
        int isPrime = 1;

        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0)
            {
                isPrime = 0;
                break;
            }
        }

        if (isPrime)
        {
            fprintf(fp, "%d ", num);
            count++;
        }

        num++;
    }

    fprintf(fp, "\n");
    fclose(fp);
    return 0;
}
