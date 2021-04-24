#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
const int MAX_VOTERS = 100;
const int MAX_CANDIDATES = 9;

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check the votes of each candidate
        for (int k = 0; k < candidate_count; k++)
        {
            printf("%s gets %i votes\n", candidates[k].name, candidates[k].votes);
        }
        break;

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Check if the name entered is valid
    // If the candidate is valid, store the index (in the candidates array) of the candidate who is the jth ranked preference for the ith voter
    // If the name is not one of the candidates, return false
    for (int i = 0; i < candidate_count; i++)
    {
        // printf("Compare %s with %s, the value return from strcmp is %i\n", name, candidates[i].name, strcmp(name, candidates[i].name));
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            // printf("\nVoter%i\'s rank%i is %s\n", voter + 1, rank + 1, candidates[preferences[voter][rank]].name);
            return true;
        }
    }

    // What if the voter rank the same candidates different ranks?
    // Say, Voter0's rank0 is Peter, Voter0's rank1 is also Peter?

    // printf("%s does not match any of the name in the candidates array\n", name);
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loop through the preferences array to check 
    // If their top choice candidate has not been eliminated, increment the candidate's vote by 1
    for (int i = 0; i < voter_count; i++)
    {
        if (!candidates[preferences[i][0]].eliminated)
        {
            candidates[preferences[i][0]].votes = candidates[preferences[i][0]].votes + 1;
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    return;
}
