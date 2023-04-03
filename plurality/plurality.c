#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
    // TODO
    // iterate the candidate_count to look if the names match
    // if match, plus 1 vote for the candidate name and return true
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // if no match, return false without adding any vote
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int totalVotes = 0;
    // it makes a check condition that store in the variable totalVotes the number of votes
    for (int index = 0; index < candidate_count; index++)
    {
        // it checks if the last time totalVotes received a new value, the value is bigger in the next iterate or not
        if (candidates[index].votes > totalVotes)
        {
            //store in totalVotes the biggest number of votes in candidates[index]
            totalVotes = candidates[index].votes;
        }
    }

    for (int index = 0; index < candidate_count; index++)
    {
        // checks if the storage in totalVotes matches any candidates.votes and print the name
        if (candidates[index].votes == totalVotes)
        {
            printf("%s\n", candidates[index].name);
        }
    }

    return;
}