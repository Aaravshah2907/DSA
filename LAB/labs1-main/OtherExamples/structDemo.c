#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct name {
    char first[20];
    char last[20];
} Name;

int main()
{
    int n;
    printf("Enter size of the array: ");
    scanf("%d", &n);

    Name* arr = calloc(n, sizeof(Name)); // Creating enough space for 'n' names.
    if (arr == NULL){
        printf("Unable to allocate memory\n");
        return -1;
    }
    printf("Enter the names (space separated): ");
    for (int i = 0; i < n; i++)
    {
        // Using . to access members of the struct
        scanf("%s %s", arr[i].first, arr[i].last);
        // Note that arr[i].first is equivalent to (arr+i)->first
        }
    printf("\nGiven array of names: ");
    for (int i = 0; i < n; i++)
        printf("%s %s\n", arr[i].first, arr[i].last);
    printf("\n");

    printf("Adding an element to the array.\n");
    Name newname;
    printf("Enter the name to be added: ");
    scanf("%s %s", newname.first, newname.last);

    arr = realloc(arr, (n + 1) * sizeof(Name));

    // Copying the new name to the end of the array
    strcpy(arr[n].first, newname.first);
    strcpy(arr[n].last, newname.last);

    printf("\nModified Array: ");
    for (int i = 0; i < n + 1; i++)
    printf("%s %s\n", arr[i].first, arr[i].last);
    printf("\n");

    free(arr);
}