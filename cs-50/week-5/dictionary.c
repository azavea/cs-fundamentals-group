// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

//hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *n = table[index];
    while(n != NULL){
        int unequal = strcmp(n->word, word);
        if(!unequal){
            return true;
        }
        n = n->next;
    }
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
    char word[LENGTH + 1];
    // open file
    FILE * dictionaryFile = fopen(dictionary, "r");
    if (dictionaryFile == NULL) {
        return false;
    }
    // individual word
    while(fscanf(dictionaryFile, "%s", word) != EOF){
        // malloc
        node *n = malloc(sizeof(node));
        if(n == NULL){
            return false;
        }
        // make node
        strcpy(n->word, word);
        n->next = NULL;
        // add to bucket
        unsigned int index = hash(word);
        if(table[index] == NULL){
            table[index] = n;
        }
        else if(table[index]->next == NULL){
            table[index]->next = n;
        }
        else{
            n->next = table[index]->next;
            table[index] = n;
        }
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
