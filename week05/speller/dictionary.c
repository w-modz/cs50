// Implements a dictionary's functionality
#define _GNU_SOURCE

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

void print_table(void);
unsigned int get_bucket_index(const char *word);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int BUCKET_COUNT = 10000;

// Hash table
node *table[BUCKET_COUNT];
unsigned int tableSize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int bucketIndex = get_bucket_index(word);
    node *currentNode = table[bucketIndex];
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
    // https://en.wikipedia.org/wiki/Jenkins_hash_function
    unsigned int hash, i;
    const unsigned int wordLength = strlen(word);
    for (hash = i = 0; i < wordLength; ++i)
    {
        hash += tolower(word[i]);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
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

    node *lastNode;
    unsigned int bucketIndex;
    while ((getline(&line, &len, file)) != -1)
    {
        tableSize++;

        // Remove newline character from the line.
        line[strlen(line) - 1] = '\0';

        bucketIndex = get_bucket_index(line);
        // If this bucket is empty...
        if ((lastNode = table[bucketIndex]) == NULL)
        {
            table[bucketIndex] = (node *)malloc(sizeof(node));
            lastNode = table[bucketIndex];
        }
        else
        {
            while (lastNode->next)
            {
                lastNode = lastNode->next;
            }
            lastNode->next = (node *)malloc(sizeof(node));
            lastNode = lastNode->next;
        }

        memcpy(lastNode->word, line, strlen(line));
    }

    free(line);
    fclose(file);
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
    node *current;
    node *next = NULL;
    for (unsigned int i = 0; i < BUCKET_COUNT; i++)
    {
        current = table[i];
        next = NULL;
        while (current)
        {
            next = current->next;
            free(current);
            current = next;
        }
    }
    return true;
}

void print_table(void)
{
    printf("Hashtable contents:\n");
    node *current;
    for (unsigned int i = 0; i < BUCKET_COUNT; i++)
    {
        current = table[i];
        while (current)
        {
            printf("%u: %s\n", i, current->word);
            current = current->next;
        }
    }
}

unsigned int get_bucket_index(const char *word)
{
    return hash(word) % BUCKET_COUNT;
}
