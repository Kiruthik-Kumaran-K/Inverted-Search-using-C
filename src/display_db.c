#include "../inc/main.h"

/*
 * Function: display_DB()
 *
 * Description:
 * Displays all words stored in the inverted search database,
 * along with their hash index, file count, filenames, and
 * the number of occurrences of each word in each file.
 *
 * Algorithm:
 * 1. Validate the hash table.
 * 2. Print the database column headings.
 * 3. Traverse all buckets of the hash table.
 * 4. Traverse the main linked list in each bucket.
 * 5. Display the word, its hash index, and file count.
 * 6. Traverse the subnode list and display filenames
 *    and their corresponding word counts.
 * 7. If no words are found, display an empty database
 *    message and return EMPTYLIST.
 * 8. Otherwise, return SUCCESS.
 *
 * Return:
 * SUCCESS  - Database contains words and is displayed.
 * FAILURE  - Invalid hash table.
 * EMPTYLIST - Database contains no words.
 */
int display_DB(main_node_t *head[])
{
    /* Validate the hash table */
    if (head == NULL)
    {
        return FAILURE;
    }

    /* Print the column headings */
    printf("\n%-10s %-20s %-15s %s\n",
           "[index]", "[word]", "file_count",
           "File_name and word_count");

    /* Print a separator below the headings */
    printf("------------------------------------------------"
           "-----------------------------------------------\n");

    /* Tracks whether at least one word exists in the database */
    int found = 0;

    /* Traverse all buckets of the hash table */
    for (int i = 0; i < SIZE; i++)
    {
        /* Start at the first main node in the current bucket */
        main_node_t *temp = head[i];

        /* Traverse the main linked list of this bucket */
        while (temp != NULL)
        {
            /* At least one word exists in the database */
            found = 1;

            /* Convert the file count into a printable string */
            char count_str[20];
            snprintf(count_str, sizeof(count_str),"%d file/s", temp->f_count);

            /* Display the bucket index, word, and file count */
            printf("[%-3d]      %-20s %-15s ",i, temp->word, count_str);

            /* Access the subnode list of the current word */
            sub_node_t *sub = temp->sub_link;

            /* Traverse all filenames associated with this word */
            while (sub != NULL)
            {
                /* Display filename and word occurrence count */
                printf("%-15s -> %d",sub->f_name, sub->w_count);

                /* Move to the next filename node */
                sub = sub->link;

                /* Separate multiple filename entries */
                if (sub != NULL)
                {
                    printf("  ");
                }
            }

            /* Move to the next line after displaying this word */
            printf("\n");

            /* Move to the next word in the current bucket */
            temp = temp->link;
        }
    }

    /* Check whether any word was displayed */
    if (found == 0)
    {
        printf("Database is empty.\n");
        return EMPTYLIST;
    }

    /* All database entries have been displayed successfully */
    return SUCCESS;
}
