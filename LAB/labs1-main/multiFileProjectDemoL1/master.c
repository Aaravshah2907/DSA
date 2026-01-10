#include "count.h"

int main(void){
    char s[100];
    printf("Enter a String: ");
    scanf("%[^\n]", s); // Anything except newline

    int counterv = countVow(s);
    printf("Vowels: %d\n", counterv);
    int counterc = countCon(s);
    printf("Consonants: %d\n", counterc);
}