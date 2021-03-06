#include <stdio.h>
#include <cs50.h>

int get_height(void);

int main(void)
{
    int height = get_height();

    // Iterate from 1 through height
    for (int i = 1; i <= height; i++)
    {

        // On iteration i, print the layer i of the pyramid on the left-hand side
        // which is made of (height - i) spaces and i hashes
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

        // print the gap between adjacent pyramids
        printf("  ");

        // On iteration i, print the layer i of the pyramid on the right-hand side
        // which is made of i hashes and (height - i) spaces, followed by a newline
        for (int l = 1; l <= i; l++)
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