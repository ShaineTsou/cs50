#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Formula of Caesar's cipher is: ci = (pi + k) % 26
// pi is the ith character in p
// k is the secret key (non-negative integer)
// ci is each letter in ciphertext

string get_ciphertext(int k);

int main(int argc, string argv[])
{
    // If the user does not input 2 arguments, print out the error message
    if (argc != 2)
    {
        // Print out the error message
        printf("Usage: ./caesar key\n");

        // Return error code 1
        return 1;
    }
    else
    {
        // Check all the characters of the second command-line argument are digits
        string s = argv[1];

        for (int i = 0, n = strlen(s); i < n; i++)
        {
            // If there's non-digit character in the string, prompt the error message and return error code 1
            if (!(s[i] >= 48 && s[i] <= 57))
            {
                // Print out the error message
                printf("Usage: ./caesar key\n");

                // Return error code 1
                return 1;
            }
        }

        // Convert the command-line argument from a string into a integer
        int k = atoi(s);

        // Get ciphertext
        string ciphertext = get_ciphertext(k);

        // Print out ciphertext
        printf("ciphertext: %s\n", ciphertext);

        return 0;
    }

}

string get_ciphertext(int k)
{
    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Convert plaintext into ciphertext
    // The ciphertext should preserve case
    string ciphertext = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = 65 + ((plaintext[i] - 65 + k) % 26);
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = 97 + ((plaintext[i] - 97 + k) % 26);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    return ciphertext;
}