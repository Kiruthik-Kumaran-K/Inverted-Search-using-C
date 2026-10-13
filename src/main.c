#include "../inc/main.h"

int main(int argc, char *argv[])
{
    file_node_t *file_head = NULL;
    main_node_t *head[SIZE];

    if (argc < 2)
    {
        printf("Usage: %s file1.txt file2.txt ...\n", argv[0]);
        return FAILURE;
    }

    initialize_hash_table(head);

    validate_n_store_filenames(&file_head, &argv[1]);


    int choice;
    char proceed;
    char word[NAMELENGTH];
    char backup_name[NAMELENGTH];

    while (1)
    {
        printf("\nSelect your choice:\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Update Database\n");
        printf("4. Search\n");
        printf("5. Save Database\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            break;
        }

        switch (choice)
        {
            case 1:
                if (create_DB(file_head, head) == SUCCESS)
                    printf("Database created successfully\n");
                else
                    printf("Database creation failed\n");
                break;

            case 2:
                display_DB(head);
                break;

            case 3:
                /* Call your update function here */
                int status = update_existing_DB(&file_head, head);

                if (status == SUCCESS)
                {
                    printf("Update operation completed\n");
                }

                break;

            case 4:
                printf("Enter the word to search: ");
                if (scanf("%19s", word) == 1)
                    search_DB(head, word);
                break;

            case 5:
                printf("Enter backup filename: ");
                if (scanf("%19s", backup_name) == 1)
                    save_DB(head, backup_name);
                break;

            default:
                printf("Invalid choice\n");
                break;
        }

        printf("\nDo you want to continue (y/n)?: ");

        if (scanf(" %c", &proceed) != 1 ||
            (proceed != 'y' && proceed != 'Y'))
        {
            break;
        }
    }

    return SUCCESS;
}
