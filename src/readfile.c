#include "../inc/main.h"

/*
 * Function: read_datafile()
 *
 * Description:
 * Reads a text file character by character, extracts alphabetic
 * words, converts them to lowercase, and inserts them into the
 * inverted search database.
 *
 * Algorithm:
 * 1. Validate the input arguments.
 * 2. Open the specified file in read mode.
 * 3. Read the file one character at a time.
 * 4. If the character is alphabetic, append it to the word buffer,
 *    provided the buffer has enough space.
 * 5. If the character is not alphabetic, terminate and insert the
 *    accumulated word if the buffer contains a word.
 * 6. At EOF, process any remaining word.
 * 7. Close the file and return the appropriate status.
 *
 * Return:
 * SUCCESS - File processed successfully.
 * FAILURE - Invalid input or file-opening failure.
 * Other status values may be returned by insert_word().
 */
int read_datafile(main_node_t *head[], char *f_name)
{

    /* Validate the hash table and filename */
    if (head == NULL || f_name == NULL || f_name[0] == '\0')
    {
        return FAILURE;
    }

    /* Open the specified file in read mode */
    FILE *fptr = fopen(f_name, "r");

    /* Check whether the file was opened successfully */
    if (fptr == NULL)
    {
        printf("Error: Unable to open %s\n", f_name);
        return FAILURE;
    }

    /* Buffer to temporarily store the current word */
    char word[NAMELENGTH];

    /* Tracks the next position in the word buffer */
    int index = 0;

    /* Stores each character read from the file */
    int ch;

    /* Read the file one character at a time until EOF */
    while ((ch = fgetc(fptr)) != EOF)
    {
        /* Check whether the character is an alphabetic letter */
        if (isalpha((unsigned char)ch))
        {
            /*
             * Append the lowercase character if space is available.
             * One byte must be reserved for the terminating '\0'.
             */
            if (index < NAMELENGTH - 1)
            {
                word[index++] = (char)tolower((unsigned char)ch);
            }
        }
        else
        {
            /*
             * A non-alphabetic character marks the end of a word.
             * Process the word only if at least one character exists
             * in the buffer.
             */
            if (index > 0)
            {
                /* Convert the accumulated characters into a C string */
                word[index] = '\0';

                /* Insert the word and update its file information */
                int status = insert_word(head, word, f_name);

                /* Stop processing if insertion fails */
                if (status != SUCCESS)
                {
                    fclose(fptr);
                    return status;
                }

                /* Reset the buffer position for the next word */
                index = 0;
            }
        }
    }

    /*
     * EOF may occur immediately after a letter.
     * In that case, the final word has not yet been processed
     * because no non-alphabetic delimiter was encountered.
     */
    if (index > 0)
    {
        /* Terminate and insert the final word */
        word[index] = '\0';

        int status = insert_word(head, word, f_name);

        /* Stop processing if insertion fails */
        if (status != SUCCESS)
        {
            fclose(fptr);
            return status;
        }
    }

    /* Close the file after successful processing */
    fclose(fptr);

    return SUCCESS;
}