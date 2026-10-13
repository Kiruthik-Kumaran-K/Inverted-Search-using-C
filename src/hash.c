#include "../inc/main.h"

void initialize_hash_table(main_node_t *head[])
{
    for (int i = 0; i < SIZE; i++)
    {
        head[i] = NULL;
    }
}


int hash_function(char *word)
{
    if (word == NULL || word[0] == '\0')
    {
        return FAILURE;
    }

    char ch = tolower((unsigned char)word[0]);

    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 'a';
    }

    return 26;
}
