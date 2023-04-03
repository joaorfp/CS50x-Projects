#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // gives the result base on the points for each word given
    if (score1 > score2)
    {
        printf("Player 1 wins !\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins !\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int totalScore = 0;
    for (int index = 0; index < strlen(word); index ++)
    {
        // this if only pass letters through, so it doesnt count special chars
        if (word[index] >= 65 && word[index] <= 122)
        {
            // put all letter in uppercase to count it
            word[index] = toupper(word[index]);
            // add points and sum it
            // also it gets the ASCII pos of the letter and subtract by 65 since it is on uppercase
            totalScore += POINTS[word[index] - 65];
        }
    }
    return totalScore;
}
