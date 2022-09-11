// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"
#include <stdint.h>
//dictionary word count
int dwc = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 262144;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *list_index = NULL;
    int HV = hash(word);
    if (table[HV] == NULL)
    {
        return false;
    }

    list_index = table[HV];
    while (list_index != NULL)
    {
        if (strcasecmp(list_index -> word, word) == 0)
        {
            return true;
        }
        else
        {
            list_index = list_index -> next;
        }
    }
    return false;

}


//Hashes word to a number
unsigned int hash(const char *word)
{
    // //Calculate hash sum
    unsigned int hashsum = 0;
    unsigned int a = 0;
    unsigned int b = 0;
    unsigned int c = 0;
    unsigned int l = strlen(word);


    a = toupper(word[0]) ;

    b = toupper(word[l - 1]) ;

    c = toupper(word[(l - 1) / 2]) ;

    hashsum = a + (27 * b) + (729 * c) + (19683 * l);

    //this formula maintains non-commutativity because the multiples do not overlap
    return (hashsum % 262144) ;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    dwc = 0;
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("failed to load dictionary");
        return false;
    }

    char word[45];

    //initialise hash table
    for (int i = 0; i < N; i ++)
    {
        table[i] = NULL;
    }

    while (fscanf(file, "%s", word) != EOF)
    {

        //allocate space for node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("failed malloc new node");
            return false;
        }
        //copy word to node
        strcpy(new_node -> word, word);
        new_node -> next = NULL;
        //calculate hash value
        int HV = hash(word);

        if (table[HV] == NULL)
        {
            table[HV] = new_node;
        }
        else
        {
            new_node -> next = table[HV];
            table[HV] = new_node;
        }
        dwc ++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (dwc == 0)
    {
        printf("no words loaded into dictionary");
        return 0;
    }
    else
    {
        return dwc;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *temp1 = NULL;
    node *temp2 = NULL;
    //int list_length = 0;

    for (int i = 0; i < N; i ++)
    {
        //list_length = 0;
        temp1 = table[i];
        temp2 = table[i];

        while (temp1 != NULL)
        {
            temp2 = temp2 -> next;
            free(temp1);
            temp1 = temp2;
            //list_length ++;
        }
        //printf("%i ", list_length);
    }
    return true;
}
