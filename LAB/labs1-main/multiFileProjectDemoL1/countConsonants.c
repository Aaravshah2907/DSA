#include "count.h"

int countCon(char *string) {
    int count = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        char character = tolower(string[i]);

        if (isalpha(character) &&
            !(character == 'a' || character == 'e' ||
              character == 'i' || character == 'o' ||
              character == 'u')) {
            count++;
        }
    }

    return count;
}