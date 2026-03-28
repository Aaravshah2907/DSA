#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char userString[100];
    int counter[26] = {0};

    printf("Enter a String: ");
    scanf("%s", userString);

    int length = strlen(userString);

    // Convert to lowercase and count frequency
    for(int i = 0; i < length; i++) {
        userString[i] = tolower(userString[i]);

        if(userString[i] >= 'a' && userString[i] <= 'z') {
            counter[userString[i] - 'a']++;
        }
    }

    printf("Sorted String: ");
    for(int i = 0; i < 26; i++) {
        while(counter[i] > 0) {
            printf("%c", i + 'a');
            counter[i]--;
        }
    }

    printf("\n");

    return 0;
}