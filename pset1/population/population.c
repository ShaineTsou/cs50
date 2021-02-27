#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End Size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold

    int population = start_size;
    int years_counter = 0;

    while (population < end_size)
    {
        int new_born_num = population / 3;
        int pass_away_num = population / 4;
        years_counter++;
        population = population + new_born_num - pass_away_num;
    }

    // TODO: Print number of years

    printf("Years: %i\n", years_counter);
}
