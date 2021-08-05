// Implements a dictionary's functionality
#define _GNU_SOURCE

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
} node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];
unsigned int tableSize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *currentNode = table[0];
    while (currentNode)
    {
        if (strcasecmp(word, currentNode->word) == 0)
        {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // There's only one bucket, return it's index.
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open file: %s\n", dictionary);
        exit(1);
    }

    char *line = NULL;
    unsigned long len = 0;
    int lineLength = 0;
    table[0] = (node *)malloc(sizeof(node));
    node *lastNode = table[0];
    while ((getline(&line, &len, file)) != -1)
    {
        tableSize++;
        lineLength = strlen(line);

        // Remove newline character from the line.
        line[lineLength - 1] = '\0';

        memcpy(lastNode->word, line, lineLength - 1);
        lastNode->next = (node *)malloc(sizeof(node));
        lastNode = lastNode->next;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return tableSize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current = table[0];
    node *next = NULL;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    return true;
}
