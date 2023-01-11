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

 //   for (int i = 0; i < candidate_count; i++)
 //   {
 //        printf("%s ",candidates[i].name);
 //    }

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
    int l=0;
    int u=candidate_count-1;
//    printf("u-%d",u);
    int m;
//    printf("%d-m",m);
    while (l<=u)
    {
//       printf("%d\n",m);
        m==(u+l)/2;
        if (strcmp(candidates[m].name,name)==0)
        {
            candidates[m].votes+=1;
            return true;

        }
        else if (strcmp(candidates[m].name,name)>0)
        {
            u=m-1;
//            printf("<0 l-%d,u-%d,m-%d\n",l,u,m);
        }
        else
        {
            l=m+1;
//            printf(">0 l-%d,u-%d,m-%d\n",l,u,m);
        }
//        printf("%d-l,%d-u \n",l,u);
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate temp;
    for(int i=0; i<candidate_count-1 ; i++)
    {
        for(int j=0; j<candidate_count-i-1 ; j++)
        {
            if(candidates[j].votes>candidates[j+1].votes)
            {
                temp=candidates[j];
                candidates[j]=candidates[j+1];
                candidates[j+1]=temp;
            }
        }
    }
    int count=candidates[candidate_count-1].votes;
    for(int i=1; i<=candidate_count;i++)
    {
        if (candidates[candidate_count-i].votes==count)
        {
//            printf("%d votes :",candidates[candidate_count-i].votes);
            printf("%s\n",candidates[candidate_count-i].name);
        }
    }
}