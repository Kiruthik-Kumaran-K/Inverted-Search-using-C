#include "../inc/main.h"

int IsFileValid(char *filename)
{
      int len = strlen(filename);
      if(len < 4)
      {
            return FAILURE;
      }
      
      int i = len - 4;
      
      if(strcmp(&filename[i],".txt") != 0)
      {
            return FAILURE;
      } 

      FILE *fp = fopen(filename, "r");

      if(fp == NULL)
      {
            return FAILURE;
      }

      int ch = fgetc(fp);

      if(ch == EOF)
      {
            fclose(fp);
            return FILE_EMPTY;
      }

      fclose(fp);

      return SUCCESS;
}


int is_duplicate_file(file_node_t *head, char *f_name)
{
    file_node_t *temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->f_name, f_name) == 0)
        {
            return REPEATED;
        }

        temp = temp->link;
    }

    return SUCCESS;
}

int store_filenames_to_list(char *f_name, file_node_t **head)
{
    file_node_t *new_node = malloc(sizeof(file_node_t));

    if (new_node == NULL)
    {
        return FAILURE;
    }

    strcpy(new_node->f_name, f_name);
    new_node->link = NULL;

    /* If the list is empty */
    if (*head == NULL)
    {
        *head = new_node;
        return SUCCESS;
    }

    /* Traverse to the last node */
    file_node_t *temp = *head;

    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    /* Insert at the end */
    temp->link = new_node;

    return SUCCESS;
}


void validate_n_store_filenames(file_node_t **head, char *filenames[])
{
    int i = 0;

    while (filenames[i] != NULL)
    {
        char *filename = filenames[i];

        int status = IsFileValid(filename);

        if (status != SUCCESS)
        {
        if (status == FILE_EMPTY)
                printf("%s: File is empty\n", filename);
        else
                printf("%s: Invalid extension or inaccessible file\n",filename);

        i++;
        continue;
        }

        /* Check filename length */
        if (strlen(filename) >= NAMELENGTH)
        {
            printf("%s: Filename too long\n", filename);
            i++;
            continue;
        }

        /* Check whether filename is already stored */
        if (is_duplicate_file(*head, filename) == REPEATED)
        {
            printf("%s: Duplicate filename\n", filename);
            i++;
            continue;
        }

        /* Insert valid filename */
        if (store_filenames_to_list(filename, head) == SUCCESS)
        {
            printf("%s: Added successfully\n", filename);
        }
        else
        {
            printf("%s: Failed to allocate memory\n", filename);
        }

        i++;
    }
}
