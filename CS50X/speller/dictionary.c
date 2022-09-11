// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

int dictionary_count;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int I = 46;
const unsigned int J = 27;
const unsigned int K = 27;
const unsigned int L = 27;
const unsigned int M = 27;

unsigned int letter_value(char Letter);

// Hash table
node *table[I][J][K][L];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int A = strlen(word);
    int B = letter_value(word[0]);
    int C = letter_value(word[1]);
    int D = letter_value(word[A - 1]);

    node *tmp = table[A][B][C][D];
    if (tmp == NULL)
    {
        return false;
    }
    while (tmp != NULL)
    {
        if (strcasecmp(tmp -> word, word) == 0)
        {
            return true;
        }
        else
        {
            tmp = tmp -> next;
        }
    }
    return false;
}


// changes a letter to a number
unsigned int letter_value(char Letter)
{
    if(isalpha(Letter) != 0)
    {
        return toupper(Letter) - 'A';
    }
    else
    {
        return 26;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    dictionary_count = 0;

    //initialise hash table
    for (int i = 0; i < I; i ++)
    {
        for (int j = 0; j < J; j ++)
        {
            for (int k = 0; k < K; k ++)
            {
                for (int l = 0; l < L; l ++)
                {
                    table[i][j][k][l] = NULL;
                }
            }
        }
    }


    //open dictionary file pointer
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("failed to load dictionary\n");
        return false;
    }
    //define word to LENGTH to avoid molloc'ing
    char word[LENGTH];

    //scan words from dictionary to memory one by one
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("failed malloc new_node\n");
            return false;
        }
        //initialise node
        new_node -> next = NULL;
        strcpy(new_node -> word, word);

        int A = strlen(word);
        int B = letter_value(word[0]);
        int C = letter_value(word[1]);
        int D = letter_value(word[A - 1]);

        new_node -> next = table[A][B][C][D];
        table[A][B][C][D] = new_node;
        dictionary_count ++;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (dictionary_count == 0)
    {
        return 0;
    }
    else
    {
        return dictionary_count;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *temp1 = NULL;
    node *temp2 = NULL;

   for (int i = 0; i < I; i ++)
    {
        for (int j = 0; j < J; j ++)
        {
            for (int k = 0; k < K; k ++)
            {
                for (int l = 0; l < L; l ++)
                {
                    temp1 = table[i][j][k][l];
                    temp2 = table[i][j][k][l];

                    while (temp1 != NULL)
                    {
                        temp2 = temp2 -> next;
                        free(temp1);
                        temp1 = temp2;
                    }
                }
            }
        }
    }
    return true;
}
