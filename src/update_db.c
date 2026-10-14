#include "../inc/main.h"

/*
 * Function: update_existing_DB()
 *
 * Description:
 * Updates the existing inverted search database by adding
 * a new file and indexing all its words.
 *
 * Algorithm:
 * 1. Validate the file list pointer and hash table.
 * 2. Read the filename from the user.
 * 3. Validate the input file.
 * 4. Check whether the file is already in the database.
 * 5. Add the filename to the file linked list.
 * 6. Locate the newly added file node.
 * 7. Read the file and insert its words into the hash table.
 * 8. Display the result and return the appropriate status.
 *
 * Return:
 * SUCCESS - File indexed successfully.
 * FAILURE - Invalid input or an operation failed.
 * REPEATED - File is already present in the database.
 */
int update_existing_DB(file_node_t **file_head, main_node_t *head[])
{
    /* Validate the file list pointer and hash table */
    if (file_head == NULL || head == NULL)
    {
        return FAILURE;
    }

    /* Buffer to store the filename entered by the user */
    char fname[NAMELENGTH];

    /* Ask the user for the filename */
    printf("Enter the file name to update database: ");

    /* Read the filename and reject unsuccessful input */
    if (scanf("%19s", fname) != 1)
    {
        return FAILURE;
    }

    /* Check whether the specified file is valid */
    if (IsFileValid(fname) != SUCCESS)
    {
        printf("Error: Invalid input file\n");
        return FAILURE;
    }

    /* Prevent the same file from being added more than once */
    if (is_duplicate_file(*file_head, fname))
    {
        printf("Error: File is already present in the database\n");
        return REPEATED;
    }

    /* Add the new filename to the file linked list */
    if (store_filenames_to_list(fname, file_head) != SUCCESS)
    {
        printf("Error: Unable to add filename\n");
        return FAILURE;
    }

    /* Start searching from the head of the file linked list */
    file_node_t *new_file = *file_head;

    /* Locate the node containing the newly added filename */
    while (new_file != NULL && strcmp(new_file->f_name, fname) != 0)
    {
        new_file = new_file->link;
    }

    /* Stop if the filename node could not be found */
    if (new_file == NULL)
    {
        return FAILURE;
    }

    /* Read the new file and index its words in the hash table */
    if (read_datafile(head, fname) != SUCCESS)
    {
        printf("Error: Failed to index new file\n");
        return FAILURE;
    }

    /* Confirm that the database update was successful */
    printf("Database updated successfully with %s\n", fname);

    return SUCCESS;
}