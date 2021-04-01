#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Create strings to store capital letters and small letters of the alphabet
string cptLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string smlLetters = "abcdefghijklmnopqrstuvwxyz";

string get_ciphertext(string key);
int binary_search(char character, string alphabet);

int main(int argc, string argv[])
{
    // If the user does not input 2 arguments, print out the error message
    if (argc != 2)
    {
        // Print out the error message
        printf("Usage: ./substitution key\n");

        // Return error code 1
        return 1;
    }
    else
    {
        string key = argv[1];
        int n = strlen(key);

        // If the number of characters of the second command-line argument is not 26, print out the error message
        if (n != 26)
        {
            // Print out the error message
            printf("Usage: ./substitution key\n");

            // Return error code 1
            return 1;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (isalpha(key[i]) == 0)
                {
                    // Print out the error message
                    printf("Usage: ./substitution key\n");

                    // Return error code 1
                    return 1;
                }
                else
                {
                    // Handle duplicate characters
                    int charCount = 0;

                    for (int j = 0; j < n; j++)
                    {
                        if (key[i] == key[j])
                        {
                            charCount++;
                        }
                        if (charCount > 1)
                        {
                            // Print out the error message
                            printf("Usage: ./substitution key\n");

                            // Return error code 1
                            return 1;
                        }
                    }
                }
            }
        }

        // Get ciphertext
        string ciphertext = get_ciphertext(key);

        // Print out ciphertext
        printf("ciphertext: %s\n", ciphertext);

        return 0;
    }

}


// Check if the character is in alphabet using binary search algorithm
// If it is, return the index of that character in the alphabet. Otherwise, return -1
int binary_search(char character, string alphabet)
{
    int minIndex = 0;
    int maxIndex = strlen(alphabet) - 1;

    while (minIndex <= maxIndex)
    {
        int middleIndex = floor((maxIndex + minIndex) / 2);
        if (character == alphabet[middleIndex])
        {
            return middleIndex;
        }
        else if (character > alphabet[middleIndex])
        {
            minIndex = middleIndex + 1;
        }
        else if (character < alphabet[middleIndex])
        {
            maxIndex = middleIndex - 1;
        }
    }
    return -1;
}

// Get plaintext and encrypt plaintext to ciphertext
string get_ciphertext(string key)
{
    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Encrypt plaintext into ciphertext using the key provided by user
    // The ciphertext should preserve case no matter the key is uppercase or lowercase
    string ciphertext = plaintext;

    for (int i = 0, n = strlen(ciphertext); i < n; i++)
    {
        if (isupper(ciphertext[i]))
        {
            // Find out which capital letter match the current character of the ciphertext
            // Store the position of the matching capital letter as index
            int index = binary_search(ciphertext[i], cptLetters);

            if (islower(key[index]))
            {
                // The difference between the ASCII values of lowercase letter and uppercase letter is 32
                // If the key[index] is lowercase, convert it to uppercase by subtracting it by 32
                key[index] = key[index] - 32;
            }
            ciphertext[i] = key[index];
        }
        else if (islower(ciphertext[i]))
        {
            // Find out which small letter match the current character of the ciphertext
            // Store the position of the matching small letter as index
            int index = binary_search(ciphertext[i], smlLetters);
            if (isupper(key[index]))
            {
                // The difference between the ASCII values of lowercase letter and uppercase letter is 32
                // If the key[index] is uppercase, convert it to lowercase by adding it by 32
                key[index] = key[index] + 32;
            }
            ciphertext[i] = key[index];
        }
        else
        {
            // If the current character is non-alphabet, it should remain unchanged
            ciphertext[i] = plaintext[i];
        }
    }
    return ciphertext;
}