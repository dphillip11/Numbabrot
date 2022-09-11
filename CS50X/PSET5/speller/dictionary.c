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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool unloader(trie*node);
/////////////////////////////////////////////////STRUCTURES

trie *root = NULL;
int dwc = 0;


/////////////////////////////////////////////////PROTOTYPES

trie *create_node();
bool unloader(trie *root);
int char_value(char);



/////////////////////////////////////////////////MAIN


    //initialise root node





/////////////////////////////////////////////////FUNCTIONS

//Load dictionary to memory
bool load(const char *dictionary)
{
    root = create_node();
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("failed to load dictionary");
        return false;
    }

    //word buffer, size limit 45
    char word[45];
    //read a line at a time to word buffer
    while (fscanf(file, "%s", word) != EOF)
    {
        //pointer to maintain postion
        trie *cursor = root;
        int len = strlen(word);

        for (int i = 0; i < len; i ++)
        {
            int v = char_value(word[i]);

            if (cursor -> letter[v] == NULL)
            {
                // if the letter node is empty, create a node
                trie *new_node = create_node();
                // point to it
                cursor -> letter[v] = new_node;
                // move the cursor
                cursor = new_node;
            }
            else
            {
                cursor = cursor -> letter[v];
            }

        }
        cursor -> isWord = 1;
        dwc ++;
    }
    fclose(file);
    return true;
}

//Create new node for trie, malloc, assign NULL pointers, return pointer
trie *create_node()
{
    trie *node = malloc(sizeof(trie));

    node -> isWord = 0;

    for (int i = 0; i < 27; i ++)
    {
        node -> letter[i] = NULL;
    }

    return node;
}

//unload dictionary, if root pointers are free, free root, else repeat process for pointers
bool unload()
{
    return unloader(root);

}

//assign a pointer index value for node traversal
int char_value(char c)
{
    if (isalpha(c) == 0)
    {
        return 26;
    }
    c = tolower(c);

    return (c - 'a');

}

bool check(const char *word)
{
    //follow from root through letters using a cursor, if word ends at isWord = 1, match else not


    trie *cursor = root;
    int len = strlen(word);

    for (int i = 0; i < len; i ++)
    {
        int v = char_value(word[i]);

        if (cursor -> letter[v] == NULL)
        {
            break;
        }
        else
        {
            cursor = cursor -> letter[v];
        }

    }
    if (cursor -> isWord != 1)
        return false;

    return true;
}

bool unloader(trie*node)
{
    for (int i = 0; i < 27; i ++)
    {
        if (node -> letter[i] != NULL)
        {
            unloader(node -> letter[i]);
        }
    }
    free(node);
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