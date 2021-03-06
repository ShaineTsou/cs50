#include <stdio.h>
#include <cs50.h>

int get_height(void);

int main(void)
{
    int height = get_height();
    // Iterate from 1 through height
    // On iteration i, print (height - i) spaces and i hashes, and followed by a newline
    for (int i = 1; i <= height; i++)
    {
        int numSpace = height - i;
        int numHash = i;
        for (int j = 1; j <= numSpace; j++)
        {
            printf(" ");
        }
        for (int k = 1; k <= numHash; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// Prompt the user for height
// Re-prompt if height is not an integer or height is not between 1 and 8 inclusively
int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}