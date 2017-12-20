/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define TRIE_NODE_SIZE 27
#define LOWER_A_CHAR_CODE 97
#define LOWER_Z_CHAR_CODE 122

typedef struct trieNode {
    struct trieNode *nodes[TRIE_NODE_SIZE];
    bool isWord;
}
trieNode;

/**
 * Returns the appropriate index a char belongs to
 */
int getMapIndex(char c);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Creates a new node
 */
trieNode *createNode();

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Frees a node in the dictionary
 */
void freeNode(trieNode *node);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
