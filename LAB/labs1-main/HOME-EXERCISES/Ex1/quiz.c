#include <stdio.h>
#include <ctype.h>
#include "set.h"

#define QUESTIONS 10

int main(void)
{
    char answers[QUESTIONS];
    char input;
    int score;

    printf("Enter answers for 10 questions (A, B, C, D or N):\n");

    for (int i = 0; i < QUESTIONS; i++)
    {
        while (1)
        {
            printf("Question %d: ", i + 1);
            scanf(" %c", &input);
            input = toupper(input);

            if (input == 'A' || input == 'B' || input == 'C' ||
                input == 'D' || input == 'N')
            {
                answers[i] = input;
                break;
            }
            else
            {
                printf("Invalid input. Try again.\n");
            }
        }
    }

    score = answer_checker(answers);
    printf("\nFinal Score: %d\n", score);

    return 0;
}
