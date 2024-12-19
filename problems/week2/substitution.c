#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../../lib/cs50.h"

/*
Take in a cypher key as argument and use it to encrypt a given
word by replacing each letter with the letter in the key which 
is in the same position
(https://cs50.harvard.edu/x/2022/psets/2/substitution/)
*/

int main(int argc, string argv[])
{
    // Check command line argument
    if (argc != 2)
    {
        // If incorrect number or command line arguments, show an error
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Get key
    string key = argv[1];

    // Key the key length
    int key_length = strlen(key);

    // Check if key is corrent length
    if (key_length != 26)
    {
        // If key is incorrect length, show an error
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // Validate key
    for (int i = 0; i < key_length; i++)
    {
        // Convert letter to lowercase
        char c1 = tolower(key[i]);

        // Check if letter is alphabetical
        if (!isalpha(c1))
        {
            // Is letter is not alphabetical show an error
            printf("Key must only contain alphabetical characters.\n");
            return 1;
        }

        // Check for repeated characters
        for (int j = i + 1; j < key_length; j++)
        {
            char c2 = tolower(key[j]);

            // Check is characters are the same
            if (c2 == c1)
            {
                // If they are, show an error
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }

        // Assign the lower case character into the key
        key[i] = c1;

    }

    // Get user text to encrypt
    string text = get_string("plaintext:  ");

    int text_length = strlen(text);

    // Convert each character to the cipher
    for (int i = 0; i < text_length; i++)
    {
        char c = text[i];

        if (islower(c))
        {
            c = key[c - 97];
        }
        else if (isupper(c))
        {
            c = toupper(key[c - 65]);
        }

        text[i] = c;
    }

    // Print the encrypted word
    printf("ciphertext: %s\n", text);

}