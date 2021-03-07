#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_cents(void);

int main(void)
{
    int cents = get_cents();

    // Calculate the number of quarters
    int quarters = cents / 25;

    // Calculate the number of dimes
    int dimes = cents % 25 / 10;

    // Calculate the number of nickels
    int nickels = cents % 25 % 10 / 5;

    // Calculate the number of pennies
    int pennies = cents % 25 % 10 % 5;

    // Calculate the total coins of change
    int totalCoins = quarters + dimes + nickels + pennies;
    printf("%i\n", totalCoins);
}

int get_cents(void)
{
    // Prompt the user for the change owed
    // If the input value is negative, re-prompt again
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    // Convert dollars to cents
    int cents = round(dollars * 100);
    return cents;
}