#include "../inc/main.h"


int is_txt_filename(char *fname)
{
    if (fname == NULL)
    {
        return FAILURE;
    }

    size_t len = strlen(fname);

    if (len <= 4)
    {
        return FAILURE;
    }

    if (strcmp(fname + len - 4, ".txt") != 0)
    {
        return FAILURE;
    }

    return SUCCESS;
}


// int save_DB(main_node_t *head[], char *fname)
// {
//     if (head == NULL || fname == NULL)
//     {
//         return FAILURE;
//     }

//     if (is_txt_filename(fname) != SUCCESS)
//     {
//         printf("Error: Backup filename must end with .txt\n");
//         return FAILURE;
//     }

//     FILE *fptr = fopen(fname, "w");

//     if (fptr == NULL)
//     {
//         printf("Error: Unable to open backup file\n");
//         return FAILURE;
//     }
    


//     for (int i = 0; i < SIZE; i++)
//     {
//         main_node_t *m_temp = head[i];

//         while (m_temp != NULL)
//         {
//             if (fprintf(fptr, "#%d;%s;%d",i, m_temp->word, m_temp->f_count) < 0)
//             {
//                 fclose(fptr);
//                 return FAILURE;
//             }

//             sub_node_t *sub = m_temp->sub_link;

//             while (sub != NULL)
//             {
//                 if (fprintf(fptr, ";%s;%d",
//                             sub->f_name, sub->w_count) < 0)
//                 {
//                     fclose(fptr);
//                     return FAILURE;
//                 }

//                 sub = sub->link;
//             }

//             if (fprintf(fptr, "#\n") < 0)
//             {
//                 fclose(fptr);
//                 return FAILURE;
//             }

//             m_temp = m_temp->link;
//         }
//     }

//     if (fclose(fptr) != 0)
//     {
//         printf("Error: Failed to close backup file properly\n");
//         return FAILURE;
//     }

//     printf("Database saved successfully to %s\n", fname);
//     return SUCCESS;
// }

int save_DB(main_node_t *head[], char *fname)
{
    if (head == NULL || fname == NULL)
    {
        return FAILURE;
    }

    if (is_txt_filename(fname) != SUCCESS)
    {
        printf("Error: Backup filename must end with .txt\n");
        return FAILURE;
    }

    FILE *fptr = fopen(fname, "w");

    if (fptr == NULL)
    {
        printf("Error: Unable to open backup file\n");
        return FAILURE;
    }

    for (int i = 0; i < SIZE; i++)
    {
        main_node_t *temp = head[i];

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

        while (temp != NULL)
        {
            if (fprintf(fptr, "word is [%s]: file_count: %d",
                        temp->word, temp->f_count) < 0)
            {
                fclose(fptr);
                return FAILURE;
            }

            sub_node_t *sub = temp->sub_link;

            while (sub != NULL)
            {
                if (fprintf(fptr, " file: %s and word_count: %d",
                            sub->f_name, sub->w_count) < 0)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                sub = sub->link;
            }

            if (fprintf(fptr, "\n") < 0)
            {
                fclose(fptr);
                return FAILURE;
            }

            temp = temp->link;
        }
    }

    if (fclose(fptr) != 0)
    {
        printf("Error: Failed to close backup file properly\n");
        return FAILURE;
    }

    printf("Database saved successfully to %s\n", fname);
    return SUCCESS;
}

