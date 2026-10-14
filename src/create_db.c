#include "../inc/main.h"

/*
 * Function: create_DB()
 *
 * Description:
 * Creates the inverted search database by reading every file
 * stored in the file linked list and inserting its words into
 * the hash table.
 *
 * Algorithm:
 * 1. Validate the file list and hash table.
 * 2. Initialize a temporary pointer to the first file node.
 * 3. Traverse the file linked list.
 * 4. Process each file using read_datafile().
 * 5. Stop and return the error status if processing fails.
 * 6. Continue until all files have been processed.
 *
 * Return:
 * SUCCESS - All files processed successfully.
 * FAILURE - Invalid arguments or a processing failure.
 */
int create_DB(file_node_t *file_head, main_node_t *head[])
{
    /* Validate the hash table and file list */
    if (head == NULL || file_head == NULL)
    {
        return FAILURE;
    }

    /* Start traversing from the first file node */
    file_node_t *temp = file_head;

    /* Process every file in the linked list */
    while (temp != NULL)
    {
        /*
         * Read the current file and insert its words
         * into the inverted search database.
         */
        int status = read_datafile(head, temp->f_name);

        /* Stop if the current file could not be processed */
        if (status != SUCCESS)
        {
            return status;
        }

        /* Move to the next file node */
        temp = temp->link;
    }

    /* All files have been processed successfully */
    return SUCCESS;
}