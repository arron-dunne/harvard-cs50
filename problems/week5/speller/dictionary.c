#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

/*
Implements a dictionary's functionality using a hash table.
3 hash functions are available; first_letter, two_letters and sum.
Check a word whether it's in the dictionary by finding the corrent hash value
and then searching the linked list for that word.
*/

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table, based on hash table used

// const unsigned int N = 26; // first letter
// const unsigned int N = 676; // two letter
const unsigned int N = 1000; // sum

// Hash table
node *table[N];

// Size of dictionary
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain hash value
    unsigned int index = hash(word);

    // Access linked list at the index in the hash table
    node *cursor = table[index];

    // Traverse linked list, looking for the word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashed a word by the first letter
unsigned int first_letter_hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Hashed a word by the first two letters
unsigned int two_letter_hash(const char *word)
{
    return ((toupper(word[0]) - 'A') * 26) + (toupper(word[1]) - 'A');
}

// Hashes a word by adding all character ASCII values and taken the mod with 1000
unsigned int sum_hash(const char *word)
{
    int sum = 0;
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        sum += toupper(word[i]);
    }
    return sum % 100;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // Remember to change bucket sizes when changing hash functions
    return sum_hash(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{   

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            dict_size = 0;
            return false;
        }

        strcpy(n->word, word);

        // Hash word to obtain a hash value
        unsigned int index = hash(n->word);

        // Insert node into hash table at that location#
        n->next = table[index];
        table[index] = n;

        dict_size++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }

        free(cursor);
    }
    return true;
}

