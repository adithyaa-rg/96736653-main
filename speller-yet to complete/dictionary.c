// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char initial_letter=word[0];
    initial_letter=toupper(initial_letter);
    //char* strcpy(char* word_lower, const char* word);
    char* word_lower=NULL;

    int n=(int)initial_letter-65;
    node *word_dict=table[n];
    //node *temp;
    printf("%s\n",word_dict->word);

    while(word_dict!=NULL)
    {
        int y=0;
        for(int i=0 , m = strlen(word) ; i <= m ; i++ )
        {
            word_lower[i]=tolower(word[i]);
        }

        if (strcmp(word_lower,word_dict->word)==0)
        {
            return true;
        }
        word_dict=word_dict->next;

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dict\n");
        unload();
        return 1;
    }
    printf("HI");
    /*for(int i=0; i<100 ; i++)
    {
        printf("%c ",dictionary[i]);
    }
    if (dictionary==NULL)
    {
        return false;
    }*/
    char word[LENGTH + 1];
    char c;
    int index=0;
    int i=0;int f=0;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;
            if (f<5)
            {
                printf("%s ",word);
                f+=1;
                printf("HI");
            }
        }

        if (isspace(c) || (int)c == 10 )
        {

            word[index]='\0';
            index=0;

            int first=hash(word);
            node *temp;
            temp=table[first];
            while(temp!=NULL)
            {
                temp=temp->next;
            }
            strcpy((temp->word),word);
            for(int j=0;j<LENGTH+1;j++)
            {
                word[j]=' ';
            }
        }
    }
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

        int n=0;
        for(int i=0;i<26;i++)
        {
            node *temp=table[i];
            if (temp!=NULL)
            {
                n+=1;
                temp=temp->next;
            }
        }
        return n;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i=0 ; i<26 ; i++)
    {
        node *freeing=table[i];
        node *temp;
        temp=freeing->next;
        if(freeing!=NULL)
        {
            free(freeing);
            freeing=temp;
            temp=temp->next;
        }
    }
    if (size()==0)
    {
        return true;
    }
    return false;
}
