#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

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
    for (int i = 0; i < candidate_count; i++)
    {
        // If the candidate is valid, store the index (in the candidates array) of the candidate who is the jth ranked preference for the ith voter
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    // If the name doesn't match any of the candidates name, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loop through the preferences array to check
    for (int i = 0; i < voter_count; i++)
    {
        // If their first choice of remaining candidate has not been eliminated, increment the candidate's vote by 1
        // If their first choice of remaining candidate has been eliminated, go to check the next preference of candiddate
        int k = 0;

        while (candidates[preferences[i][k]].eliminated)
        {
            k++;
        }

        candidates[preferences[i][k]].votes = candidates[preferences[i][k]].votes + 1;
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // If any candidate has more than half of the votes, winner_count increments by 1, and assign the candidate's name to winner
    string winner = " ";
    int winner_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > floor(voter_count / 2))
        {
            winner_count++;
            winner = candidates[i].name;
        };
    }

    // If winner is still an empty string, or there is not only one winner
    if (strcmp(winner, " ") == 0 || winner_count != 1)
    {
        return false;
    }
    else
    {
        printf("%s\n", winner);
        return true;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialize a variable called min to be the largest number the vote can be, which is voter_count
    int min = voter_count;

    // Iterate through the candidates array, if the votes the remaining candidate has is less than min, set that value to be min
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes < min)
            {
                min = candidates[i].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // If any of the candidates has the votes greater than min, the election is not tied
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate through the candidates array, eliminate anyone with minimum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
