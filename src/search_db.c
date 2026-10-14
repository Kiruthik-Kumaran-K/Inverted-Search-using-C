#include "../inc/main.h"

/*
 * Function: search_DB()
 *
 * Description:
 * Searches for a word in the inverted search database.
 * If the word exists, displays the word, the number of
 * files containing it, and its occurrence count in each file.
 *
 * Algorithm:
 * 1. Validate the hash table and search word.
 * 2. Convert the search word to lowercase.
 * 3. Reject the word if it exceeds the maximum length.
 * 4. Calculate the hash index for the search word.
 * 5. Traverse the main linked list in that bucket.
 * 6. If the word is found, display its file information.
 * 7. If the word is absent, display a not-found message.
 *
 * Return:
 * SUCCESS    - Word found in the database.
 * FAILURE    - Invalid input or invalid hash index.
 * NOT_PRESENT - Word does not exist in the database.
 */
int search_DB(main_node_t *head[], char *word)
{
    /* Validate the hash table and search word */
    if (head == NULL || word == NULL || word[0] == '\0')
    {
        return FAILURE;
    }

    /* Convert the search word to lowercase */
    char search_word[NAMELENGTH];
    int i = 0;

    /* Copy characters while respecting the buffer size */
    while (word[i] != '\0' && i < NAMELENGTH - 1)
    {
        search_word[i] = (char)tolower((unsigned char)word[i]);
        i++;
    }

    /* Terminate the lowercase search string */
    search_word[i] = '\0';

    /* Reject words that exceed the maximum allowed length */
    if (word[i] != '\0')
    {
        return FAILURE;
    }

    /* Find the hash bucket for the search word */
    int index = hash_function(word);

    /* Stop if the hash function reports an invalid index */
    if (index == FAILURE)
    {
        return FAILURE;
    }

    /* Start searching from the first node in this bucket */
    main_node_t *temp = head[index];

    /* Traverse the main linked list in the selected bucket */
    while (temp != NULL)
    {
        /* Compare the stored word with the lowercase search word */
        if (strcmp(temp->word, search_word) == 0)
        {
            /* Display the matching word and its file count */
            printf("Word: %s\n", temp->word);
            printf("File count: %d\n", temp->f_count);

            /* Access the filename list associated with this word */
            sub_node_t *sub = temp->sub_link;

            /* Display every filename and its word occurrence count */
            while (sub != NULL)
            {
                printf("Filename: %s, Word count: %d\n",
                       sub->f_name, sub->w_count);

                /* Move to the next filename node */
                sub = sub->link;
            }

            /* Search completed successfully */
            return SUCCESS;
        }

        /* Move to the next word in the bucket */
        temp = temp->link;
    }

    /* The word was not found in the selected bucket */
    printf("Word '%s' not found in the database.\n", word);
    return NOT_PRESENT;
}
