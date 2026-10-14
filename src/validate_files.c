#include "../inc/main.h"

/*
 * Function: IsFileValid()
 *
 * Description:
 * Validates an input file by checking its extension,
 * accessibility, and whether it is empty.
 *
 * Algorithm:
 * 1. Calculate the filename length.
 * 2. Check whether the filename is long enough.
 * 3. Verify that the filename ends with ".txt".
 * 4. Open the file in read mode.
 * 5. Check whether the file contains any character.
 * 6. Close the file and return the appropriate status.
 *
 * Return:
 * SUCCESS   - File is valid and contains data.
 * FAILURE   - Invalid filename, extension, or inaccessible file.
 * FILE_EMPTY - File contains no characters.
 */
int IsFileValid(char *filename)
{
    /* Calculate the length of the filename */
    int len = strlen(filename);

    /* Reject filenames that are too short to contain a name and extension */
    if (len < 4)
    {
        return FAILURE;
    }

    /* Find the starting position of the last four characters */
    int i = len - 4;

    /* Check whether the filename ends with ".txt" */
    if (strcmp(&filename[i], ".txt") != 0)
    {
        return FAILURE;
    }

    /* Open the file in read mode */
    FILE *fp = fopen(filename, "r");

    /* Reject the file if it cannot be opened */
    if (fp == NULL)
    {
        return FAILURE;
    }

    /* Read the first character to check whether the file is empty */
    int ch = fgetc(fp);

    /* If EOF is returned immediately, treat the file as empty */
    if (ch == EOF)
    {
        fclose(fp);
        return FILE_EMPTY;
    }

    /* Close the file after validation */
    fclose(fp);

    /* File has the required extension and contains at least one character */
    return SUCCESS;
}

/*
 * Function: is_duplicate_file()
 *
 * Description:
 * Checks whether the given filename already exists
 * in the file linked list.
 *
 * Algorithm:
 * 1. Initialize a temporary pointer to the first node.
 * 2. Traverse the file linked list.
 * 3. Compare each stored filename with the given filename.
 * 4. If a match is found, return REPEATED.
 * 5. If the end of the list is reached without a match,
 *    return SUCCESS.
 *
 * Return:
 * REPEATED - Filename already exists in the list.
 * SUCCESS  - Filename is not present in the list.
 */
int is_duplicate_file(file_node_t *head, char *f_name)
{
    /* Start traversing from the first file node */
    file_node_t *temp = head;

    /* Check each node until the end of the list */
    while (temp != NULL)
    {
        /* Compare the current filename with the given filename */
        if (strcmp(temp->f_name, f_name) == 0)
        {
            /* Filename already exists */
            return REPEATED;
        }

        /* Move to the next file node */
        temp = temp->link;
    }

    /* No matching filename was found */
    return SUCCESS;
}

/*
 * Function: store_filenames_to_list()
 *
 * Description:
 * Creates a new file node and inserts it at the end
 * of the file linked list.
 *
 * Algorithm:
 * 1. Allocate memory for a new file node.
 * 2. Check whether memory allocation succeeded.
 * 3. Copy the filename into the new node.
 * 4. Initialize the new node's link to NULL.
 * 5. If the list is empty, make the new node the head.
 * 6. Otherwise, traverse the list to the last node.
 * 7. Link the last node to the new node.
 *
 * Return:
 * SUCCESS - Filename inserted successfully.
 * FAILURE - Memory allocation failed.
 */
int store_filenames_to_list(char *f_name, file_node_t **head)
{
    /* Allocate memory for a new file node */
    file_node_t *new_node = malloc(sizeof(file_node_t));

    /* Stop if memory allocation fails */
    if (new_node == NULL)
    {
        return FAILURE;
    }

    /* Store the filename in the new node */
    strcpy(new_node->f_name, f_name);

    /* Initialize the new node as the last node */
    new_node->link = NULL;

    /* If the list is empty, make the new node the first node */
    if (*head == NULL)
    {
        *head = new_node;
        return SUCCESS;
    }

    /* Start traversing from the first node */
    file_node_t *temp = *head;

    /* Move until the last node is reached */
    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    /* Connect the current last node to the new node */
    temp->link = new_node;

    return SUCCESS;
}

/*
 * Function: validate_n_store_filenames()
 *
 * Description:
 * Validates a list of filenames and stores valid, unique
 * filenames in the file linked list.
 *
 * Algorithm:
 * 1. Initialize the array index to zero.
 * 2. Process filenames until a NULL entry is encountered.
 * 3. Validate each file's extension, accessibility, and contents.
 * 4. Reject filenames that exceed the maximum allowed length.
 * 5. Check whether the filename already exists in the list.
 * 6. Insert valid, non-duplicate filenames into the list.
 * 7. Display the result of processing each filename.
 *
 * Return:
 * void - Results are reported through printed messages.
 */
void validate_n_store_filenames(file_node_t **head, char *filenames[])
{
    /* Start processing filenames from the first array element */
    int i = 0;

    /* Continue until the NULL sentinel marks the end of the array */
    while (filenames[i] != NULL)
    {
        /* Get the current filename */
        char *filename = filenames[i];

        /* Validate the file's extension, accessibility, and contents */
        int status = IsFileValid(filename);

        /* Handle invalid or empty files */
        if (status != SUCCESS)
        {
            /* Display the appropriate error message */
            if (status == FILE_EMPTY)
                printf("%s: File is empty\n", filename);
            else
                printf("%s: Invalid extension or inaccessible file\n",
                       filename);

            /* Move to the next filename */
            i++;
            continue;
        }

        /* Reject filenames that cannot fit in the filename field */
        if (strlen(filename) >= NAMELENGTH)
        {
            printf("%s: Filename too long\n", filename);

            /* Skip the remaining checks for this filename */
            i++;
            continue;
        }

        /* Reject filenames that are already present in the list */
        if (is_duplicate_file(*head, filename) == REPEATED)
        {
            printf("%s: Duplicate filename\n", filename);

            /* Skip insertion and process the next filename */
            i++;
            continue;
        }

        /* Insert the valid filename into the file linked list */
        if (store_filenames_to_list(filename, head) == SUCCESS)
        {
            printf("%s: Added successfully\n", filename);
        }
        else
        {
            /* Report insertion failure, such as memory allocation failure */
            printf("%s: Failed to allocate memory\n", filename);
        }

        /* Move to the next filename in the array */
        i++;
    }
}