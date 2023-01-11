#include <cs50.h>
#include <stdio.h>
#include <string.h>
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
    for (int i=0; i<candidate_count ; i++)
    {
        if (strcmp(name,candidates[i])==0)
        {
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int pos_i,pos_j;

    for(int i=0; i<candidate_count ; i++)
    {
        for(int j=0; j<candidate_count;j++)
        {
            for(int x=0; x<candidate_count; x++)
            {
                if(i==ranks[x])
                {
                    pos_i=x;
                }
            }
            for(int y=0; y<candidate_count; y++)
            {
                if (j==ranks[y])
                {
                    pos_j=y;
                }
            }
            if (pos_i<pos_j)
            {
                preferences[i][j]+=1;
            }
        }

    }

    for(int i=0;i<candidate_count;i++)
    {
        for(int j=0; j<candidate_count;j++)
        {
            printf("%d",preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int n=0;
    for(int i=0; i< candidate_count ; i++)
    {
        for (int j=0; j<i ; j++)
        {
            if (preferences[i][j]>preferences[j][i])
            {
                pairs[n].winner=i;
                pairs[n].loser=j;
                n+=1;
            }
            else if (preferences[i][j]<preferences[j][i])
            {
                pairs[n].winner=j;
                pairs[n].loser=i;
                n+=1;
            }

//            printf("%d \n",n);
        }
    }
    pair_count=n;
    for (int i=0; i<pair_count;i++)
    {
//        printf("%d - winner- %d loser-%d\n",i,pairs[i].winner,pairs[i].loser);
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int i, j;
    for (i = 0; i < pair_count - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < pair_count - i - 1; j++)
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j+1].winner][pairs[j+1].loser])
            {
                printf("hi");

                pairs[j+1]=pairs[j];
            }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i=0; i< pair_count ; i++)
    if (locked[pairs[i].winner][pairs[i].loser]==false)
    {
        locked[pairs[i].winner][pairs[i].loser]=true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int n[candidate_count];
    int temp;
    for(int i=0; i<candidate_count ; i++)
    {
        temp=0;
        for (int j=0; j<candidate_count ; j++)
        {
            if (locked[i][j]==true)
            {
                temp+=1;
//                printf("%d-temp\n",temp);
            }
        }
        n[i]=temp;

    }
    for(int i=0;i<candidate_count;i++)
    {
        printf("%s-%d\n",candidates[i],n[i]);
    }
//    printf("%s\n",candidates[m]);

    return;
}