#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// The Coleman-Liau formula is "index = 0.0588 * L - 0.296 * S - 15.8"
// L is the average number of letters per 100 words in the text.
// S is the average number of sentences per 100 words in the text.
// The index number computed by the Coleman-Liau formula should be rounded to the nearest integer

int cal_index_num(string text);

int main(void)
{
    // Prompt user for a string of text
    string text = get_string("Text: ");

    // Store the result from cal_index_num(text) as indexNum
    int indexNum = cal_index_num(text);


    if (indexNum >= 1 && indexNum < 16)
    {
        // Program should print as output "Grade X" where X is the index number
        printf("Grade %i\n", indexNum);
    }
    else if (indexNum < 1)
    {
        // If the index number is less than 1, print out "Before Grade 1"
        printf("Before Grade 1\n");
    }
    else
    {
        // If the index number is 16 or higher, print out "Grade 16+"
        printf("Grade 16+\n");
    }
}

int cal_index_num(string text)
{
    int numOfLetters = 0;
    int numOfSpaces = 0;
    int numOfSentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] < 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            // Caculate the number of letters
            numOfLetters += 1;
        }
        else if (text[i] == ' ')
        {
            // Caculate the number of spaces
            numOfSpaces += 1;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            // Caculate the number of sentences ( = the total number of periods, exclamation points and question marks)
            numOfSentences += 1;
        }
    }

    // Caculate the number of words ( = the number of spaces plus 1)
    int numOfWords = numOfSpaces + 1;

    // Caculate (L) the average number of letters per 100 words in the text
    // Caculate (S) the average number of sentences per 100 words in the text.
    // Caluculate the index number
    double l = (double) numOfLetters * 100 / (double) numOfWords;
    double s = (double) numOfSentences * 100 / (double) numOfWords;
    int indexNum = round((0.0588 * l) - (0.296 * s) - 15.8);

    return indexNum;
}
