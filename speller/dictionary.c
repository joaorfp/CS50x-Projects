// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

int sizeofDict = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash value
    int hashValue = hash(word);

    // access linked node
    node *n = table[hashValue];

    // looks for wordlist
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    long sum = 0;
    for (int index = 0; index < strlen(word); index++)
    {
        sum += tolower(word[index]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dict file to check
    FILE *dict_pointer = fopen(dictionary, "r");

    // checks if dict is not null
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    char nextWord[LENGTH + 1];

    // scan file
    while (fscanf(dict_pointer, "%s", nextWord) != EOF)
    {
        // new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // store word in node
        strcpy(n->word, nextWord);

        int hashValue = hash(nextWord);

        // insert node into hashtable at that location

        n->next = table[hashValue];
        table[hashValue] = n;
        sizeofDict++;
    }

    // close file
    fclose(dict_pointer);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sizeofDict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate over hashtable to free nodes
    for (int index = 0; index < N; index++)
    {
        // assigns cursors
        node *n = table[index];

        // loop into node list
        while (n != NULL)
        {
            // temp variable
            node *tmp = n;

            // points to next element on node list
            n = n->next;

            // free temporary variable
            free(tmp);
        }

        if (n == NULL && index == N - 1)
        {
            return true;
        }
    }
    return false;
}
