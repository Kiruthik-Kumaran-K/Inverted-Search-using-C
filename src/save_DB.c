#include "../inc/main.h"

/*
 * Function: save_DB()
 *
 * Description:
 * Saves the contents of the inverted search database
 * into a text backup file.
 *
 * Algorithm:
 * 1. Validate the hash table and filename.
 * 2. Check whether the backup filename ends with ".txt".
 * 3. Open the backup file in write mode.
 * 4. Traverse all buckets of the hash table.
 * 5. Skip buckets that contain no words.
 * 6. Write the bucket index to the file.
 * 7. Traverse the main linked list and write each word
 *    and its file count.
 * 8. Traverse the corresponding subnode list and write
 *    each filename and word occurrence count.
 * 9. Check write and close operations for errors.
 * 10. Return SUCCESS if the database is saved correctly.
 *
 * Return:
 * SUCCESS - Database saved successfully.
 * FAILURE - Invalid input or a file operation failed.
 */
int save_DB(main_node_t *head[], char *fname)
{
    /* Validate the hash table and backup filename */
    if (head == NULL || fname == NULL)
    {
        return FAILURE;
    }

    /* Ensure that the backup filename has a .txt extension */
    if (IsFileValid(fname) != SUCCESS)
    {
        printf("Error: Backup filename must end with .txt\n");
        return FAILURE;
    }

    /* Open the backup file in write mode */
    FILE *fptr = fopen(fname, "w");

    /* Stop if the file could not be opened */
    if (fptr == NULL)
    {
        printf("Error: Unable to open backup file\n");
        return FAILURE;
    }

    /* Traverse every bucket in the hash table */
    for (int i = 0; i < SIZE; i++)
    {
        /* Start at the first main node of the current bucket */
        main_node_t *temp = head[i];

        /* Skip this bucket if it contains no words */
        if (temp == NULL)
        {
            continue;
        }

        /* Write the hash index once for this bucket */
        if (fprintf(fptr, "#[%d]\n", i) < 0)
        {
            fclose(fptr);
            return FAILURE;
        }

        /* Traverse all words in the current bucket */
        while (temp != NULL)
        {
            /* Write the word and the number of files containing it */
            if (fprintf(fptr,"word is [%s]: file_count: %d",temp->word, temp->f_count) < 0)
            {
                fclose(fptr);
                return FAILURE;
            }

            /* Access the filename list associated with this word */
            sub_node_t *sub = temp->sub_link;

            /* Write every filename and its word occurrence count */
            while (sub != NULL)
            {
                if (fprintf(fptr," file: %s and word_count: %d",sub->f_name, sub->w_count) < 0)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                /* Move to the next filename node */
                sub = sub->link;
            }

            /* End the current word's record with a newline */
            if (fprintf(fptr, "\n") < 0)
            {
                fclose(fptr);
                return FAILURE;
            }

            /* Move to the next word in this bucket */
            temp = temp->link;
        }
    }

    /* Check whether closing the file succeeds */
    if (fclose(fptr) != 0)
    {
        printf("Error: Failed to close backup file properly\n");
        return FAILURE;
    }

    /* Confirm that the database was saved successfully */
    printf("Database saved successfully to %s\n", fname);

    return SUCCESS;
}