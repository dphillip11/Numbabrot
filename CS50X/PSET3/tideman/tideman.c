#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
//some merge sort prototypes, seemed like a fun exercise :)
void sort(int[], int);
void merge(int[], int, int[], int);
//check for loop for lock_pairs
bool loop_check(int i, int j);

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
        if (strcmp(candidates[i], name) == 0)
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
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = i + 1; j < candidate_count; j ++)
        {
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            if ((preferences[i][j]) > (preferences[j][i]))
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    typedef struct
    {
        int index;
        int strength;
    }
    strength;

    // create an index of pair locations and strengths

    strength strengths[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strengths[i].index = i;
        strengths[i].strength = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    //sort the strength values
    int strength_values[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strength_values[i] = strengths[i].strength;
    }

    sort(strength_values, pair_count);

    //assign pairs to temp array using index values
    pair temp[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        temp[i] = pairs[i];
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (strength_values[i] == strengths[j].strength)
            {
                temp[i] = pairs[strengths[j].index];
                //avoid repeats
                strengths[j].strength = 0;
            }
        }
    }
    //copy temp array into pairs array
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = temp[i];
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // use recursion to check for loop, if loop ends at beginning, do not lock
    for (int i = 0; i < pair_count; i ++)
    {
        if (loop_check(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}



// Print the winner of the election
void print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = true;
        //cycle through lines of locked to check that all are false
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                winner = false;
            }
        }
        if (winner == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool loop_check(int winner, int loser)
{
    if (loser  == winner)
    {
        return true;
    }
    for (int k = 0; k < candidate_count; k++)
    {
        if (locked[loser][k] == true && loop_check(winner, k) == true)
        {
            return true;
        }
    }
    return false;
}



void sort(int arr[], int length)
{
    if (length == 1)
    {
        return;
    }

    int midpoint = floor(length / 2);

    int left_array[midpoint];
    int right_array[length - midpoint];

    //define lefet and right groups
    for (int i = 0; i < midpoint; i ++)
    {
        left_array[i] = arr[i];
    }
    for (int j = midpoint; j < length; j ++)
    {
        right_array[j - midpoint] = arr[j];
    }

    sort(left_array, midpoint);
    sort(right_array, length - midpoint);
    merge(left_array, midpoint, right_array, length - midpoint);
    for (int k = 0; k < length; k++)
    {
        if (k < midpoint)
        {
            arr[k] = left_array[k];
        }
        else
        {
            arr[k] = right_array[k - midpoint];
        }
    }


}

void merge(int left[], int length_l, int right[], int length_r)
{
    int left_index = 0;
    int right_index = 0;
    int temp_arr[length_l + length_r];

    //create a temporary array to preserve data, then rearrange back into left and right
    for (int i = 0; i < length_l + length_r; i++)
    {
        if (left[left_index] > right[right_index] && left_index < length_l)
        {
            temp_arr[i] = left[left_index];
            left_index ++;
        }
        else
        {
            if (right_index < length_r)
            {
                temp_arr[i] = right[right_index];
                right_index ++;
            }
            else
            {
                temp_arr[i] = left[left_index];
                left_index ++;
            }
        }
    }

    for (int j = 0; j < length_l + length_r; j++)
    {
        if (j < length_l)
        {
            left[j] = temp_arr[j];
        }
        else
        {
            right[j - length_l] = temp_arr[j];
        }
    }
}