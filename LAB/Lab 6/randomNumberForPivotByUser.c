#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int a, b;
    printf("Enter a and b: ");
    scanf("%d %d", &a, &b);
    srand(time(NULL));
    int r = rand() % (b - a + 1) + a;
    printf("Random number between %d and %d is %d\n", a, b, r);
    return 0;
}