#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/////////////////////////////////////////////////STRUCTURES

typedef struct trie
{
    int isWord;  //initialise to 0, set to 1 for word end
    struct trie *letter[27]; //extra node for apostrophe's
}
trie;

trie *root = NULL;


/////////////////////////////////////////////////PROTOTYPES

trie *create_node();
int load(char *dictionary);
void unload(trie *root);
int char_value(char);
int check(char *text);


/////////////////////////////////////////////////MAIN

int main(int argc, char *argv[])
{
    //check number of arguments
    if (argc != 3)
    {
        printf("Example: ./tries dict.txt, text.txt\n");
    }

    //initialise root node
    root = create_node();

    //load dictionary, check fail condition
    if (load(argv[1]) == 1)
    {
        printf("failed to load dictionary");
    }

    check(argv[2]);

    unload(root);
}


/////////////////////////////////////////////////FUNCTIONS

//Load dictionary to memory
int load(char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("failed to load dictionary");
        return 1;
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
    }
    fclose(file);
    return 0;
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
void unload(trie *node)
{
    for (int i = 0; i < 27; i ++)
    {
        if (node -> letter[i] != NULL)
        {
            unload(node -> letter[i]);
        }
    }
    free(node);
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

int check(char *text)
{
    //follow from root through letters using a cursor, if word ends at isWord = 1, match else not
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("failed to load dictionary");
        return 1;
    }

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
                break;
            }
            else
            {
                cursor = cursor -> letter[v];
            }

        }
        if (cursor -> isWord != 1)
            printf("%s\n", word);
    }
    fclose(file);
    return 0;
}
