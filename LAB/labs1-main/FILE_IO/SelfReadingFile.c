#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    char line[1024];

    /* Open the current source file using __FILE__ */
    fp = fopen(__FILE__, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    /* Read and display each line */
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
