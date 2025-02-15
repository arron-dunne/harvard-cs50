#include <stdio.h>
#include <string.h>
#include "../../lib/cs50.h"

/*
Implement a pluratity election (each voter votes for one candidatate and the
candidate with the most votes wins). Take the candidates name as
arguments, and then prompt the user for the number of voters. For each
voter prompt the user for the candidate they vote for. Finally, display
the winner.

(https://cs50.harvard.edu/x/2022/psets/3/plurality/)
*/

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if name is a candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Add 1 to candidates votes
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int most_votes = 0;

    // Loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidates votes are higher than previous highest votes
        if (candidates[i].votes > most_votes)
        {
            // Updates the most votes
            most_votes = candidates[i].votes;
        }
    }

    // Loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate has the most votes
        if (candidates[i].votes == most_votes)
        {
            // Print the candidates name on a new line
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}