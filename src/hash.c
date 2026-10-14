#include "../inc/main.h"

/*
 * Function: initialize_hash_table()
 *
 * Description:
 * Initializes every bucket in the hash table to NULL,
 * indicating that all buckets are initially empty.
 *
 * Algorithm:
 * 1. Traverse all SIZE buckets.
 * 2. Set each bucket pointer to NULL.
 *
 * Return:
 * void - No value is returned.
 */
void initialize_hash_table(main_node_t *head[])
{
    /* Visit every bucket in the hash table */
    for (int i = 0; i < SIZE; i++)
    {
        /* Mark the current bucket as empty */
        head[i] = NULL;
    }
}


/*
 * Function: hash_function()
 *
 * Description:
 * Calculates the hash index of a word using its first
 * character.
 *
 * Algorithm:
 * 1. Validate the word pointer and check for an empty string.
 * 2. Convert the first character to lowercase.
 * 3. If the character is between 'a' and 'z',
 *    calculate its index using ch - 'a'.
 * 4. Otherwise, return bucket index 26.
 *
 * Return:
 * 0 to 25 - Hash index for alphabetic characters.
 * 26      - Hash index for other first characters.
 * FAILURE - Invalid pointer or empty string.
 */
int hash_function(char *word)
{
    /* Reject a NULL pointer or an empty word */
    if (word == NULL || word[0] == '\0')
    {
        return FAILURE;
    }

    /* Convert the first character to lowercase safely */
    char ch = tolower((unsigned char)word[0]);

    /* Map letters 'a' through 'z' to indices 0 through 25 */
    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 'a';
    }

    /* Map non-alphabetic first characters to bucket 26 */
    return 26;
}