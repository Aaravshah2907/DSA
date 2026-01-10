#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *src, *dest;
    int ch;

    /* Open source file for reading */
    src = fopen("test1.txt", "r");
    if (src == NULL) {
        perror("Error opening test1.txt");
        return 1;
    }

    /* Open destination file for writing */
    dest = fopen("test2.txt", "w");
    if (dest == NULL) {
        perror("Error opening test2.txt");
        fclose(src);
        return 1;
    }

    /* Copy contents from test1.txt to test2.txt */
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    /* Reopen test1.txt in write mode to clear its contents */
    src = fopen("test1.txt", "w");
    if (src == NULL) {
        perror("Error clearing test1.txt");
        return 1;
    }

    fclose(src);

    printf("Contents moved successfully.\n");
    printf("test1.txt is now empty.\n");

    return 0;
}
