#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int words = 1;
    int letters = 0;
    int sentences = 0;

    for (int index = 0; index < strlen(text); index++)
    {
        // it count the sentences by checking if the sentence ends with some special char
        if (text[index] == 33 || text[index] == 63 || text[index] == 46)
        {
            sentences++;
        }
        // it counts the spaces between the words, so then counts how many words exists in the text
        if (text[index] == 32)
        {
            words++;
        }
        // counts how many letters exists in the text
        if (text[index] >= 65 && text[index] <= 122)
        {
            letters++;
        }
    }
    // average number of letters per 100 words
    float L = (float)letters / (float)words * 100;
    // average number of sentences per 100 words
    float S = (float)sentences / (float)words * 100;

    // Coleman-Liau Index
    float coleman = (0.0588 * L - 0.296 * S - 15.8);
    coleman = round(coleman);

    if (coleman < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", coleman);
    }

}