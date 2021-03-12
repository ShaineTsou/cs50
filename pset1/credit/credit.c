#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

long get_cardNum(void);

int main(void)
{
    // Import cardNum from get_cardNum function
    long cardNum = get_cardNum();

    // Multiply every other digit by 2, starting from the second-to-last digit
    // Sum up all the digits
    int multipliedDigit = 0;
    int sumOfMultipliedDigit = 0;
    int notMultipliedDigit = 0;
    int sumOfNotMultipliedDigit = 0;
    int totalSum = 0;

    // Use counter to keep track of the position of the digit
    int counter = 1;

    // Initalize the cardType variable with the value of empty string
    string cardType = "";

    do
    {
        // Get the sum of multiplied digits and the sum of digits without multiplication
        if (counter % 2 == 0)
        {
            // When the counter is even, mutiple the current digit by 2
            multipliedDigit = (cardNum % 10) * 2;

            // If the product has more than 1 digit, separate it into 2 digits
            if (multipliedDigit > 9)
            {
                multipliedDigit = floor(multipliedDigit / 10) + (multipliedDigit % 10);
            }

            // Sum up the digit multiplied
            sumOfMultipliedDigit = sumOfMultipliedDigit + multipliedDigit;
        }
        else if (counter % 2 == 1)
        {
            // When the counter is odd, store the current digit and sum up the digit that is not multiplied
            notMultipliedDigit = cardNum % 10;
            sumOfNotMultipliedDigit = sumOfNotMultipliedDigit + notMultipliedDigit;
        }

        // Check card type
        // American Express uses 15-digit numbers starting with 34 or 37
        // MasterCard uses 16-digit numbers starting with 51, 52, 53, 54, or 55
        // Visa uses 13- and 16-digit numbers starting with 4
        if (cardNum < 100)
        {
            if (cardNum == 34 || cardNum == 37)
            {
                if (counter == 14)
                {
                    cardType = "AMEX";
                }
            }
            else if (cardNum >= 40 && cardNum <= 49)
            {
                if (counter == 12 || counter == 15)
                {
                    cardType = "VISA";
                }
            }
            else if (cardNum >= 51 && cardNum <= 55 && counter == 15)
            {
                if (counter == 15)
                {
                    cardType = "MASTERCARD";
                }
            }
        }


        cardNum = cardNum / 10;
        counter++;
    }
    while (cardNum > 0);

    // Add all digits together
    totalSum = totalSum + sumOfMultipliedDigit + sumOfNotMultipliedDigit;

    // Check if the card number is invalid
    int res = strcmp(cardType, "");

    if (totalSum % 10 != 0 || res == 0)
    {
        cardType = "INVALID";
    }

    // Print out card type
    printf("%s\n", cardType);
}

long get_cardNum(void)
{
    // Prompt the user for a credit card number
    // If the input value is non-numeric or negative, re-prompt again
    long cardNum;
    do
    {
        cardNum = get_long("Number: ");
    }
    while (cardNum < 0);
    return cardNum;
}