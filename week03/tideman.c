#include <cs50.h>
#include <stdio.h>

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
bool is_circle(int origin, int k);

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

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i] == name)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}
// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int k = 0; k < (candidate_count - 1); k++)
    {
        int i = ranks[k];
        for (int n = k + 1; n < candidate_count; n++)
        {
            int j = ranks[n];
            preferences[i][j]++;
        }
    }
    // TODO
    return;
}
// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    
    // TODO
    return;
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int n = 0; n < pair_count - 1; n++)
    {
        for (int k = 0; k < pair_count - 1; k++)
        {
            pair one = pairs[k];
            pair two = pairs[k + 1];
            
            int victory_strenght1 = preferences[one.winner][one.loser];
            int victory_strenght2 = preferences[two.winner][two.loser];
            if (victory_strenght1 < victory_strenght2)
            {
                pair temp = pairs[k];
                pairs[k] = pairs[k + 1];
                pairs[k + 1] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

bool is_circle(int origin, int k)
{
    //origin is the person from which we want to draw an edge
    //k is the losing person in the matchup against origin
    if(locked[k][origin])
        {
            return true;
        }
    for(int i = 0; i < candidate_count; i++)
    {
        if(locked[i][origin])
        {
            return is_circle(i, k);
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for(int i = 0; i < candidate_count - 1; i++)
    {
        for(int j = 0; j < candidate_count - 1; j++)
        {
            if(locked[j][i])
            {
                break;
            }        
        }
        printf("%s\n", candidates[i]);
        return;
    }
}
