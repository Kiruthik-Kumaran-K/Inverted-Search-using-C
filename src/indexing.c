#include "../inc/main.h"

/*
 * Function: insert_at_last_main()
 *
 * Description:
 * Inserts a new word into the main linked list in alphabetical
 * order. If the word already exists, insertion is not performed.
 *
 * Algorithm:
 * 1. Validate the input arguments and word length.
 * 2. Traverse the linked list to find the correct sorted position.
 * 3. If the word already exists, return REPEATED.
 * 4. Allocate memory for a new main node.
 * 5. Initialize the new node's members.
 * 6. Insert the node at the beginning or after the previous node.
 *
 * Return:
 * SUCCESS - Word inserted successfully.
 * REPEATED - Word already exists in the list.
 * FAILURE - Invalid input or memory allocation failure.
 */
int insert_at_last_main(main_node_t **head, char *word)
{
    /* Validate the head pointer and word */
    if (head == NULL || word == NULL || word[0] == '\0')
    {
        return FAILURE;
    }

    /* Ensure the word fits in the node's word array */
    if (strlen(word) >= NAMELENGTH)
    {
        return FAILURE;
    }

    /*
     * Find the correct alphabetical position.
     * prev points to the previous node.
     * temp points to the current node.
     */
    main_node_t *prev = NULL;
    main_node_t *temp = *head;

    while (temp != NULL)
    {
        /* Compare the current word with the word to be inserted */
        int result = strcmp(temp->word, word);

        /* Word already exists; no duplicate node is needed */
        if (result == 0)
        {
            return REPEATED;
        }

        /*
         * Current word comes after the new word alphabetically.
         * Stop here and insert the new node before temp.
         */
        if (result > 0)
        {
            break;
        }

        /* Move both pointers forward to continue searching */
        prev = temp;
        temp = temp->link;
    }

    /* Allocate memory for the new main node */
    main_node_t *new_node = malloc(sizeof(main_node_t));

    /* Check whether memory allocation succeeded */
    if (new_node == NULL)
    {
        return FAILURE;
    }

    /* Initialize the new node with the word and default values */
    strcpy(new_node->word, word);
    new_node->link = temp;
    new_node->sub_link = NULL;
    new_node->f_count = 0;

    /*
     * Insert the node at the correct position.
     * If prev is NULL, insertion is at the beginning.
     * Otherwise, link the previous node to the new node.
     */
    if (prev == NULL)
    {
        *head = new_node;
    }
    else
    {
        prev->link = new_node;
    }

    return SUCCESS;
}


/*
 * Function: update_sub_node()
 *
 * Description:
 * Updates the subnode list of a main node for a particular filename.
 *
 * If the filename already exists in the subnode list, increments
 * its word count. Otherwise, creates a new subnode for the filename
 * and appends it to the end of the subnode list.
 *
 * Algorithm:
 * 1. Validate the main node and filename.
 * 2. Traverse the subnode list to search for the filename.
 * 3. If the filename exists, increment its word count.
 * 4. If it does not exist, allocate and initialize a new subnode.
 * 5. Insert the new subnode at the end of the list.
 * 6. Increment the main node's file count.
 *
 * Return:
 * SUCCESS - Existing subnode updated or new subnode inserted.
 * FAILURE - Invalid arguments or memory allocation failure.
 */
int update_sub_node(main_node_t *main_node, char *fname)
{
    /* Validate the arguments */
    if (main_node == NULL || fname == NULL || fname[0] == '\0')
    {
        return FAILURE;
    }

    /* Start traversing the subnode list of the current word */
    sub_node_t *temp = main_node->sub_link;

    while (temp != NULL)
    {
        /* Check whether this filename is already present */
        if (strcmp(temp->f_name, fname) == 0)
        {
            /*
             * Filename already exists.
             * Increment the number of times the word occurs
             * in this file and return without creating a node.
             */
            temp->w_count++;
            return SUCCESS;
        }

        /* Move to the next subnode */
        temp = temp->link;
    }

    /*
     * Filename not found.
     * Allocate memory for a new subnode to store this file.
     */
    sub_node_t *new_node = malloc(sizeof(sub_node_t));

    /* Check whether memory allocation succeeded */
    if (new_node == NULL)
    {
        return FAILURE;
    }

    /* Initialize the new subnode */
    strcpy(new_node->f_name, fname);
    new_node->w_count = 1;
    new_node->link = NULL;

    /*
     * Insert the new subnode at the end of the list.
     * If the list is empty, the new node becomes the first node.
     */
    if (main_node->sub_link == NULL)
    {
        main_node->sub_link = new_node;
    }
    else
    {
        /* Find the last subnode */
        temp = main_node->sub_link;

        while (temp->link != NULL)
        {
            temp = temp->link;
        }

        /* Link the last subnode to the new node */
        temp->link = new_node;
    }

    /*
     * A new filename has been added.
     * Increment the number of distinct files containing this word.
     */
    main_node->f_count++;

    return SUCCESS;
}


/*
 * Function: insert_word()
 *
 * Description:
 * Inserts a word into the appropriate hash table bucket and
 * maintains its filename and word-frequency information.
 *
 * Algorithm:
 * 1. Validate the input arguments.
 * 2. Calculate the hash index for the given word.
 * 3. Search for the word in the selected bucket.
 * 4. If the word exists, update its subnode information.
 * 5. If the word does not exist, insert a new main node.
 * 6. Search for the newly inserted main node.
 * 7. Update its filename information by creating or updating
 *    the corresponding subnode.
 *
 * Return:
 * SUCCESS - Word information updated successfully.
 * FAILURE - Invalid input or an operation failed.
 * Other status values may be returned by called functions.
 */
int insert_word(main_node_t *head[], char *word, char *fname)
{
    /* Validate the hash table, word, and filename */
    if (head == NULL || word == NULL || fname == NULL ||
        word[0] == '\0' || fname[0] == '\0')
    {
        return FAILURE;
    }

    /* Step 1: Calculate the hash index for the given word */
    int index = hash_function(word);

    /* Stop if the hash function reports an invalid index */
    if (index == FAILURE)
    {
        return FAILURE;
    }

    /*
     * Step 2: Access the selected hash bucket.
     * temp points to the first main node in this bucket.
     */
    main_node_t *temp = head[index];

    /* Traverse the bucket to search for the word */
    while (temp != NULL)
    {
        /* Check whether the word already exists */
        if (strcmp(temp->word, word) == 0)
        {
            /*
             * Word exists.
             * Update its filename information:
             * - Increment w_count if the filename already exists.
             * - Create a new subnode if the filename is not present.
             */
            return update_sub_node(temp, fname);
        }

        /* Move to the next main node in the bucket */
        temp = temp->link;
    }

    /*
     * Step 3: Word does not exist.
     * Insert a new main node at the correct alphabetical
     * position in the selected bucket.
     */
    int status = insert_at_last_main(&head[index], word);

    /* Check whether main-node insertion succeeded */
    if (status != SUCCESS)
    {
        return status;
    }

    /*
     * Step 4: Search the bucket again to find the newly
     * inserted main node.
     */
    temp = head[index];

    while (temp != NULL)
    {
        /* Locate the main node containing the given word */
        if (strcmp(temp->word, word) == 0)
        {
            /*
             * Step 5: Add the filename information to this node.
             * Since the main node is new, its subnode list is empty.
             */
            return update_sub_node(temp, fname);
        }

        /* Continue searching the bucket */
        temp = temp->link;
    }

    /* Return failure if the inserted word cannot be located */
    return FAILURE;
}