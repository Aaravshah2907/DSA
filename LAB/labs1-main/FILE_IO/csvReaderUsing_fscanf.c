#include <stdio.h>
int main(void)
{
    FILE *fptr;
    char name1[20], name2[20];
    int ID1, ID2;
    fptr = fopen("test.csv", "r");
    fscanf(fptr, "%[^,],%d\n", name1, &ID1);
    fscanf(fptr, "%[^,],%d\n", name2, &ID2);
    // Recall from CP that %[^,] means read until comma
    printf("Name1: %s, ID1: %d\n", name1, ID1);
    printf("Name2: %s, ID2: %d\n", name2, ID2);
    fclose(fptr);
}