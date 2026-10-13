#include "../inc/main.h"

int insert_at_last_main(main_node_t **head, char *word)
{
    if (head == NULL || word == NULL || word[0] == '\0')
    {
        return FAILURE;
    }

    if (strlen(word) >= NAMELENGTH)
    {
        return FAILURE;
    }

    /* Find the correct sorted position */
    main_node_t *prev = NULL;
    main_node_t *temp = *head;

    while (temp != NULL)
    {
        int result = strcmp(temp->word, word);

        /* Word already exists */
        if (result == 0)
        {
            return REPEATED;
        }

        /* New word belongs before current word */
        if (result > 0)
        {
            break;
        }

        prev = temp;
        temp = temp->link;
    }

    /* Allocate the new node */
    main_node_t *new_node = malloc(sizeof(main_node_t));

    if (new_node == NULL)
    {
        return FAILURE;
    }

    strcpy(new_node->word, word);
    new_node->link = temp;
    new_node->sub_link = NULL;
    new_node->f_count = 0;

    /* Insert at the beginning or after prev */
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


int update_sub_node(main_node_t *main_node, char *fname)
{
    /* Validate the arguments */
    if (main_node == NULL || fname == NULL || fname[0] == '\0')
    {
        return FAILURE;
    }

    /* Traverse the existing subnode list */
    sub_node_t *temp = main_node->sub_link;

    while (temp != NULL)
    {
        /* Check whether this filename already exists */
        if (strcmp(temp->f_name, fname) == 0)
        {
            temp->w_count++;
            return SUCCESS;
        }

        temp = temp->link;
    }

    /* Filename not found: create a new subnode */
    sub_node_t *new_node = malloc(sizeof(sub_node_t));

    if (new_node == NULL)
    {
        return FAILURE;
    }

    strcpy(new_node->f_name, fname);
    new_node->w_count = 1;
    new_node->link = NULL;

    /* Insert the subnode at the end */
    if (main_node->sub_link == NULL)
    {
        main_node->sub_link = new_node;
    }
    else
    {
        temp = main_node->sub_link;

        while (temp->link != NULL)
        {
            temp = temp->link;
        }

        temp->link = new_node;
    }

    main_node->f_count++;

    return SUCCESS;
}


int insert_word(main_node_t *head[], char *word, char *fname)
{
    if (head == NULL || word == NULL || fname == NULL ||
        word[0] == '\0' || fname[0] == '\0')
    {
        return FAILURE;
    }

    /* Step 1: Find the appropriate bucket */
    int index = hash_function(word);

    if (index == FAILURE)
    {
        return FAILURE;
    }

    /* Step 2: Search for the word in that bucket */
    main_node_t *temp = head[index];

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
        {
            /* Word exists: update its filename information */
            return update_sub_node(temp, fname);
        }

        temp = temp->link;
    }

    /* Step 3: Word does not exist: create its main node */
    int status = insert_at_last_main(&head[index], word);

    if (status != SUCCESS)
    {
        return status;
    }

    /* Step 4: Find the newly inserted main node */
    temp = head[index];

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
        {
            return update_sub_node(temp, fname);
        }

        temp = temp->link;
    }

    return FAILURE;
}



int read_datafile(file_node_t *file_node,  main_node_t *head[], char *f_name)
{
    (void)file_node;

    if (head == NULL || f_name == NULL || f_name[0] == '\0')
    {
        return FAILURE;
    }

    FILE *fptr = fopen(f_name, "r");

    if (fptr == NULL)
    {
        printf("Error: Unable to open %s\n", f_name);
        return FAILURE;
    }

    char word[NAMELENGTH];
    int index = 0;
    int ch;

    while ((ch = fgetc(fptr)) != EOF)
    {
        if (isalpha((unsigned char)ch))
        {
            if (index < NAMELENGTH - 1)
            {
                word[index++] = (char)tolower((unsigned char)ch);
            }
        }
        else
        {
            if (index > 0)
            {
            word[index] = '\0';

            int status = insert_word(head, word, f_name);

            if (status != SUCCESS)
            {
                  fclose(fptr);
                  return status;
            }

            index = 0;
            }
        }
    }

    /* Process the final word if the file ends with a letter */
      if (index > 0)
      {
      word[index] = '\0';

      int status = insert_word(head, word, f_name);

      if (status != SUCCESS)
      {
            fclose(fptr);
            return status;
      }

      }

    return SUCCESS;
}


int create_DB(file_node_t *file_head, main_node_t *head[])
{
    if (head == NULL || file_head == NULL)
    {
        return FAILURE;
    }

    file_node_t *temp = file_head;

    while (temp != NULL)
    {
        int status = read_datafile(temp, head, temp->f_name);

        if (status != SUCCESS)
        {
            return status;
        }

        temp = temp->link;
    }

    return SUCCESS;
}

// int display_DB(main_node_t *head[])
// {
//     if (head == NULL)
//     {
//         return FAILURE;
//     }

//     int found = 0;

//     for (int i = 0; i < SIZE; i++)
//     {
//         main_node_t *temp = head[i];

//         while (temp != NULL)
//         {
//             found = 1;

//             printf("\nWord: %s\n", temp->word);
//             printf("File count: %d\n", temp->f_count);

//             sub_node_t *sub = temp->sub_link;

//             while (sub != NULL)
//             {
//                 printf("Filename: %s, Word count: %d\n",
//                        sub->f_name, sub->w_count);

//                 sub = sub->link;
//             }

//             temp = temp->link;
//         }
//     }

//     if (found == 0)
//     {
//         printf("Database is empty.\n");
//         return EMPTYLIST;
//     }

//     return SUCCESS;
// }


int display_DB(main_node_t *head[])
{
    if (head == NULL)
    {
        return FAILURE;
    }

    printf("\n%-10s %-20s %-15s %s\n",
           "[index]", "[word]", "file_count",
           "File_name and word_count");

    printf("------------------------------------------------"
           "-----------------------------------------------\n");

    int found = 0;

    for (int i = 0; i < SIZE; i++)
    {
        main_node_t *temp = head[i];

        while (temp != NULL)
        {
            found = 1;

            // printf("[%-3d]      %-20s %d file/s",
            //        i, temp->word, temp->f_count);

            // printf(" ");
            char count_str[20];
            snprintf(count_str, sizeof(count_str), "%d file/s", temp->f_count);

            printf("[%-3d]      %-20s %-15s ",i, temp->word, count_str);

            sub_node_t *sub = temp->sub_link;

            while (sub != NULL)
            {
                printf("%-15s -> %d",
                       sub->f_name, sub->w_count);

                sub = sub->link;

                if (sub != NULL)
                {
                    printf("  ");
                }
            }

            printf("\n");

            temp = temp->link;
        }
    }

    if (found == 0)
    {
        printf("Database is empty.\n");
        return EMPTYLIST;
    }

    return SUCCESS;
}




int search_DB(main_node_t *head[], char *word)
{
    if (head == NULL || word == NULL || word[0] == '\0')
    {
        return FAILURE;
    }

    /* Find the appropriate bucket */
    int index = hash_function(word);

    if (index == FAILURE)
    {
        return FAILURE;
    }

    /* Search for the word in that bucket */
    main_node_t *temp = head[index];

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
        {
            printf("Word: %s\n", temp->word);
            printf("File count: %d\n", temp->f_count);

            sub_node_t *sub = temp->sub_link;

            while (sub != NULL)
            {
                printf("Filename: %s, Word count: %d\n",
                       sub->f_name, sub->w_count);

                sub = sub->link;
            }

            return SUCCESS;
        }

        temp = temp->link;
    }

    printf("Word '%s' not found in the database.\n", word);
    return NOT_PRESENT;
}

int update_existing_DB(file_node_t **file_head, main_node_t *head[])
{
    if (file_head == NULL || head == NULL)
    {
        return FAILURE;
    }

    char fname[NAMELENGTH];

    printf("Enter the file name to update database: ");

    if (scanf("%19s", fname) != 1)
    {
        return FAILURE;
    }

    if (IsFileValid(fname) != SUCCESS)
    {
        printf("Error: Invalid input file\n");
        return FAILURE;
    }

    if (is_duplicate_file(*file_head, fname))
    {
        printf("Error: File is already present in the database\n");
        return REPEATED;
    }

    if (store_filenames_to_list(fname, file_head) != SUCCESS)
    {
        printf("Error: Unable to add filename\n");
        return FAILURE;
    }

    file_node_t *new_file = *file_head;

    while (new_file != NULL && strcmp(new_file->f_name, fname) != 0)
    {
        new_file = new_file->link;
    }

    if (new_file == NULL)
    {
        return FAILURE;
    }

    if (read_datafile(new_file, head, fname) != SUCCESS)
    {
        printf("Error: Failed to index new file\n");
        return FAILURE;
    }

    printf("Database updated successfully with %s\n", fname);

    return SUCCESS;
}


