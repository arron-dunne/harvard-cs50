#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../../lib/cs50.h"

/*
Prompt 2 players for a scrabble word each and then determine
which word is worth more.
(https://cs50.harvard.edu/x/2022/labs/2/)
*/

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

    // Print the winner, or if its a tie
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;

    // Get the length of the word
    int length = strlen(word);

    // Iterate over every character in the word
    for (int i = 0; i < length; i++)
    {
        char c = word[i];

        // Check if character is a letter
        if (isalpha(c))
        {
            // Check if character is lowercase
            if (islower(c))
            {
                // Add the value from points array to the score
                score += POINTS[c - 97];
            }
            else
            {
                // Add the value from points array to the score
                score += POINTS[c - 65];
            }
        }
    }

    return score;
}
