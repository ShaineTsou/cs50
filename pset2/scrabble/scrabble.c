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


    if (score1 > score2)
    {
        // If score1 is greater than score2, announce that Player 1 is the winner
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        // If score1 is less than score2, announce that Player 2 is the winner
        printf("Player 2 wins!");
    }
    else
    {
        // Otherwise, print out "Tie!"
        printf("Tie!");
    }
    printf("\n");
}

int compute_score(string word)
{
    // Compute and return score for string
    int score = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Check whether the character is a uppercase letter, lowercasse letter or non-letter character
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            // Since the points values of each letter of the alphabet is stored in alphabetical order
            // The difference between the index of each letter in the POINTS array and the ASCII number of each uppercase letter is 65
            int indexOfPOINTS = (int)(word[i] - 65);
            score += POINTS[indexOfPOINTS];
        }
        else if (word[i] >= 'a' && word[i] <= 'z')
        {
            // Since the points values of each letter of the alphabet is stored in alphabetical order
            // The difference between the index of each letter in the POINTS array and the ASCII number of each lowercase letter is 97
            int indexOfPOINTS = (int)(word[i] - 97);
            score += POINTS[indexOfPOINTS];
        }
        else
        {
            // Character that is not a letter is given 0 points
            score += 0;
        }
    }
    return score;
}
