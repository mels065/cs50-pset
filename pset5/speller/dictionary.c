#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

trieNode *head;
unsigned int wordCount = 0;

int getCharIndex(char c)
{
    if (c == '\'')
    {
        return TRIE_NODE_SIZE-1;
    }
    else if (tolower(c) >= LOWER_A_CHAR_CODE && tolower(c) <= LOWER_Z_CHAR_CODE)
    {
        return ((int) tolower(c)) - LOWER_A_CHAR_CODE;
    }
    return -1;
}

bool check(const char *word)
{
    int word_i = 0;
    int node_i;
    trieNode *currentNode = head;
    while (word[word_i] != '\0')
    {
        if (currentNode == NULL)
        {
            return false;
        }
        node_i = getCharIndex(word[word_i]);
        word_i++;
        if (node_i == -1)
        {
            return false;
        }
        currentNode = currentNode->nodes[node_i];
    }

    if (currentNode != NULL)
    {
        return currentNode->isWord;
    }

    return false;
}

trieNode *createNode()
{
    trieNode *node = malloc(sizeof(trieNode));
    node->isWord = false;
    for (int i = 0; i < TRIE_NODE_SIZE; i++)
    {
        node->nodes[i] = NULL;
    }
    return node;
}

bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");

    head = createNode();

    int node_i;
    trieNode *currentNode = head;
    for (int c = fgetc(inptr); c != EOF; c = fgetc(inptr))
    {
        if (c == '\n')
        {
            currentNode->isWord = true;
            currentNode = head;
            wordCount++;
        }
        else
        {
            node_i = getCharIndex((char) c);
            if (currentNode->nodes[node_i] == NULL)
            {
                currentNode->nodes[node_i] = createNode();
            }

            currentNode = currentNode->nodes[node_i];
        }
    }

    if (ferror(inptr))
    {
        fclose(inptr);
        return false;
    }

    fclose(inptr);
    return true;
}

unsigned int size(void)
{
    return wordCount;
}

void freeNode(trieNode *node)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < TRIE_NODE_SIZE; i++)
    {
        if (node->nodes[i] == NULL)
        {
            continue;
        }
        freeNode(node->nodes[i]);
    }

    if (node->isWord)
    {
        wordCount--;
    }
    free(node);
}

bool unload(void)
{
    freeNode(head);
    if (size() != 0)
    {
        return false;
    }

    return true;
}
