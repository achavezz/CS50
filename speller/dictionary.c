// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 250000;

// Hash table
node *table[N];

unsigned int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char copy[strlen(word) + 1];
    strcpy(copy, word);
    char *p = copy;
    for (; *p; ++p)
    {
        *p = tolower(*p);
    }

    unsigned int key = hash(copy);
    node *n = table[key];
    while (n != NULL)
    {
        if (strcmp(n->word, copy) == 0)
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
    // TODO: Improve this hash function
    unsigned int key = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        key = (key << 2) ^ word[i];
    }
    return key % N;
}

void insert_node(node *node, unsigned int key)
{
    if (table[key] == NULL)
    {
        table[key] = node;
        table[key]->next = NULL;
    }
    else
    {
        node->next = table[key];
        table[key] = node;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // table is an array of node pointers
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        unsigned int key = hash(word);

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough space for allocating new node.\n");
            return false;
        }
        strcpy(n->word, word);
        insert_node(n, key);
        words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *next = n->next;
            free(n);
            n = next;
        }
    }
    return true;
}
