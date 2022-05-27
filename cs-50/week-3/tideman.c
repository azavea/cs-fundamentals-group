#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// Each pair has a winner, loser
typedef struct
{
    int index;
    int sum;
}
winner;

winner winmargin;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void shuffle_pairs_for_fun(void);
void sort_pairs(void);
bool check_if_cycle(int og, int loser);
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
    printf("og pairs \n");
    for(int i =0; i<pair_count; i++ ){
        printf("winner: %d ; ", pairs[i].winner);
        printf("loser: %d ; ", pairs[i].loser);
        printf("lead: %d \n", preferences[pairs[i].winner][pairs[i].loser]);
    }
    shuffle_pairs_for_fun();
    printf("shuf pairs \n");
    for(int i =0; i<pair_count; i++ ){
        printf("winner: %d ; ", pairs[i].winner);
        printf("loser: %d ; ", pairs[i].loser);
        printf("lead: %d \n", preferences[pairs[i].winner][pairs[i].loser]);
    }
    sort_pairs();
    printf("sorted pairs \n");
    for(int i =0; i<pair_count; i++ ){
        printf("winner: %d ; ", pairs[i].winner);
        printf("loser: %d ; ", pairs[i].loser);
        printf("lead: %d \n", preferences[pairs[i].winner][pairs[i].loser]);
    }
    lock_pairs();
    printf("locked pairs \n");
    for(int i =0; i<candidate_count; i++ ){
        for(int j =0; j<candidate_count; j++ ){
        printf("%d ",locked[i][j]);
        }
        printf("\n");
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Some background:
        // candidates array = all of the names of our candidates in no particular order, populated at start
        // for each voter, we create an empty ranks array that's the size of the number of candidates
        // then, loop through each candidate
        // for each candidate, populate the voter's ranks array with the candidate at their ranking (if a candidate was voted 3rd, push candidate to ranks[2])
        // EXAMPLE:
            // candidates = [Charlie, Alice, Bob];
            // a voter casts the following votes: 1. Alice, 2. Bob, 3. Charlie
            // at the end of for loop calling vote(), the ranks array should be: [1, 2, 0];
                // candidates[ranks[0]] = Alice
        // this ranks array is then used to populate a global preferences array (?)

    for (int i=0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // 
    // preferences = tideman tally
        // preferences will be candidates x candidates with the value of preferences[i][j] = difference of votes between candidates
    // TODO
    int rank_count = candidate_count;
    for(int i=0; i<rank_count; i++){
        for(int j=i+1; j<rank_count; j++){
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // loop through preferences[i][j]
    // find difference of value at preferences[i][j] from other candidates
    // create a pair
    // populate pairs with pair
    // do not need to be ordered right now
    for(int i=0; i<candidate_count; i++){
        for(int j=i+1; j<candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if(preferences[i][j] < preferences[j][i]){
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }
        }
    }
    return;
}

void shuffle_pairs_for_fun(void)
{
    for(int i=0; i<pair_count; i++){
        int random_index = (int) arc4random_uniform(i + 1);
        pair original_pair_at_index = pairs[random_index];
        pairs[random_index] = pairs[i];
        pairs[i] = original_pair_at_index;
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count-1; i++) {
        for (int j = i+1; j < pair_count; j++) {
            int lead = preferences[pairs[j].winner][pairs[j].loser];
            if (preferences[pairs[i].winner][pairs[i].loser] < lead) {
                pair tmp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmp;
        }
        }
    }
    // for (int k = 0; k < pair_count; k++) {
    //     printf("Winner: %s ", candidates[pairs[k].winner]);
    //     printf("Loser: %s ", candidates[pairs[k].loser]);
    //     printf("Lead: %d\n", preferences[pairs[k].winner][pairs[k].loser]);
    // }
    return;
}

bool check_if_cycle(int og, int loser)
{
    bool return_value = false;
    if (loser == og){
        printf("a cycle!");
        return true;
    }
    for( int j = 0; j < candidate_count; j++){
        if(locked[loser][j] == true){
            return_value = check_if_cycle(og, j);
        }
    }
    return return_value;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // create a 2d array of size candidates x candidates - done
    // locked[i][j] means i is locked in over j
    // populated with null (maybe it's already null in C?) - done
    // lock = candidate @ lock_pairs[row] --> candidate @ lock_pairs[column]
    // if there's a lock (row is winner over column) then populate with 1
    // UNLESS the rest of the column elements are already popualted with 0 because that's a cycle!

    for (int k = 0; k < pair_count; k++){
        bool cycle = check_if_cycle(pairs[k].winner, pairs[k].loser);
        if(!check_if_cycle(pairs[k].winner, pairs[k].loser)){
            locked[pairs[k].winner][pairs[k].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++){
        int sum = 0;
        for (int j =0; j <candidate_count; j++){
            if(locked[i][j] == true){
                sum += 1;
            }
        }
        if (sum > winmargin.sum){
            winmargin.index = i;
            winmargin.sum = sum;
        }
    }

    printf("The winner: %s!\nThe sum of locked edges: %d\n", candidates[winmargin.index], winmargin.sum);
    return;
}
