#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
const int MAX = 9;

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
    // Assume that no two candidates will have the same name

    // If name matches one of the names of the cadidates in the election,
    // Update the candidate's vote total
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j].name) == 0)
        {
            candidates[j].votes++;
            return true;
        }
    }
    // If name does not match the name of any of the candidates in the election,
    // No vote totals should change
    return false;
}


// Print the winner (or winners) of the election
void print_winner(void)
{
    // Make the program remember the max number for me
    int max_votes = 0;

    // Loop over all candidates
    // Find the maximum votes and the index the winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Print out the name of the candidate who received the most votes in the election
    // If multitple candidates each have the maximum number of votes,
    // Print out the names of each of the winning candidates, each on a separate line
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

