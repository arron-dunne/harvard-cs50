#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "../../lib/cs50.h"

/*
Determine the Coleman-Liau index of input text
(https://cs50.harvard.edu/x/2022/psets/2/readability/)
*/

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Get the user input text
    string input = get_string("Text: ");

    // Get the number of letter, words and sentences
    int letters = count_letters(input);
    int words = count_words(input);
    int sentences = count_sentences(input);

    // Calculate the Coleman-Liau index and round to the nearest integer
    int index = round((0.0588 * ((float) letters / words) * 100) - (0.296 * ((float) sentences / words) * 100) - 15.8);

    // Print the grade level of the text based on the index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Counts the number of letters in the inputted text and returns it
int count_letters(string text)
{
    int n = 0;

    int length = strlen(text);

    // Loop through each letter
    for (int i = 0; i < length; i++)
    {
        // Check if the letter is alphabetical
        if (isalpha(text[i]))
        {
            n++;
        }
    }
    return n;
}

// Counts the number of words in the inputted text and returns it
int count_words(string text)
{
    int n = 1;

    int length = strlen(text);

    // Loop through each letter
    for (int i = 0; i < length; i++)
    {
        // Check if the letter is a space
        if (text[i] == ' ')
        {
            n++;
        }
    }
    return n;
}

// Counts the number of sentences in the inputted text and returns it
int count_sentences(string text)
{
    int n = 0;

    int length = strlen(text);

    // Loop through each letter
    for (int i = 0; i < length; i++)
    {
        // Check if the letter is a period, exclamation point or question mark
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            n++;
        }
    }
    return n;
}