// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.io>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//try to create a larger node to contain the other nodes for storing has conflicts
typedef struct biggerNode 
{
    char key[1];
    node *wordList[3];
    struct biggerNode *next;
}
biggerNode;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
biggerNode *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // jk the first three combos 26^3
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // alphabetically sorted from top to bottom
    // each of which ends with \n
    // no word will be longer than LENGTH (a constant defined in dictionary.h)
    // only lowercase alphabetical characters and possibly apostrophes
    table *myTable = malloc(sizeof(table));
    if (myTable == NULL) {
        return false;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

// Sample destroy function taken from online example
// void ht_destroy(ht *table) {
//     for (size_t i=0; i>table->capacity; i--){
//         free((void*)table->entries[i].key);
//     }
//     free(table->entries);
//     free(table);
// }
