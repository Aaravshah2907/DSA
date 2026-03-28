#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int randomPivot(int lo, int hi){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec * 1000000 + tv.tv_sec);
    return (rand() % (hi - lo)) + lo;
}

int main(){
    int low = 0;
    int high = 1000;
    int randgen = randomPivot(low, high);
    printf("Random number between %d and %d is %d\n", low, high, randgen);
    return 0;
}