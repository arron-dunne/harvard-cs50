#include <stdio.h>
#include <string.h>
#include "../../lib/cs50.h"

/*
Implement a tideman election (each voter ranks all of the candidates
and the winner is the candidate who would of won any head-to-head matchup
against an oponent, the "Condorcet winner"). Take in the candidate names
as arguments and then prompt the user for the number of voters. For each 
voter, prompt the user for their ranked candidates. Finally, show the
winner according to the tideman algorithm.

https://cs50.harvard.edu/x/2022/psets/3/tideman/
*/

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool makes_cycle(int start, int current);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // Get votes from user
    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Check name entered is a valid candidate
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Add candidate to the ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        // Check name entered is a valid candidate
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update preferences matrix with voters votes
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If pairing has a majority, create a new pair for them with winner and loser
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                // Increment pair count
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Selection Sort
    for (int i = 0; i < pair_count - 1; i++)
    {
        // Initalize the first pair as the current highest
        pair most_preffered = pairs[i];
        int most_preffered_index = i;

        // Loop through each other pair
        for (int j = i + 1; j < pair_count; j++)
        {
            // If pair is better than the current highest, update the current highest
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[most_preffered.winner][most_preffered.loser])
            {
                most_preffered = pairs[j];
                most_preffered_index = j;
            }
        }

        // Swap first pair and most voted pair
        pairs[most_preffered_index] = pairs[i];
        pairs[i] = most_preffered;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through each pair
    for (int i = 0; i < pair_count; i++)
    {
        // Check if the pair creates a closed cycle using recursion
        if (!makes_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            continue;
        }

    }
    return;
}

bool makes_cycle(int start, int current)
{
    // If the current is the same as the start, then a cycle has been made
    if (start == current)
    {
        return true;
    }

    // Loop through each connection from current and check if a cycle is made
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][current])
        {
            if (makes_cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Loop through each candidate and find the source
    for (int i = 0; i < candidate_count; i++)
    {

        bool isSource = true;

        // Check each candiate if they point to the current one
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                // Update is source
                isSource = false;
            }
        }

        // Print the winner
        if (isSource)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}