#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Coleman Liau index = 0.0588 * L - 0.296 * S - 15.8
// L = average letter count per 100 words
// S = average sentence count per 100 words

int main(void)
{
    string text = get_string("Text:");

    //count spaces and letters
    //iterate through characters until finshed string
    //word count will be one more than spaces, start at 1

    int word_count = 1;
    int letter_count = 0;
    int sentence_count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letter_count ++;
        }
        if (isblank(text[i]))
        {
            word_count ++;
        }
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentence_count ++;
        }
    }

    //calculate L, average letter count per 100 words

    float mean_L = 100.0 * letter_count / word_count;

    //calculate S, average sentence count per 100 words

    float mean_S = 100.0 * sentence_count / word_count;

    //Calculate Coleman Liau index

    int CLI = round((0.0588 * mean_L) - (0.296 * mean_S) - 15.8);

    if (CLI < 1)
    {
        printf("Before Grade 1");
    }
    if (CLI > 1 && CLI < 17)
    {
        printf("Grade %i", CLI);
    }
    if (CLI > 16)
    {
        printf("Grade 16+ ");
    }
    printf("\n");

}