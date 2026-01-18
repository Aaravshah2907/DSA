#include "set.h"

int answer_checker(char answers[])
{
    char key[10] = {'B','C','D','A','B','C','D','A','B','C'};
    int score = 0;

    for (int i = 0; i < 10; i++)
    {
        if (answers[i] == 'N')
            continue;
        else if (answers[i] == key[i])
            score += 4;
        else
            score -= 1;
    }

    if (score < 0)
        score = 0;

    return score;
}
