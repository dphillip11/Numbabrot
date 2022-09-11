// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

typedef struct trie
{
    int isWord;  //initialise to 0, set to 1 for word end
    struct trie *letter[27]; //extra node for apostrophe's
}
trie;



// Prototypes
bool check(const char *word);
//unsigned int hash(const char *word);
trie *create_node();
int char_value(char);
bool load(const char *dictionary);
unsigned int size(void);
bool unload();

#endif // DICTIONARY_H
