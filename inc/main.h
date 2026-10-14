#ifndef MAIN_H
#define MAIN_H

/* Standard input/output functions */
#include <stdio.h>

/* Dynamic memory allocation functions */
#include <stdlib.h>

/* String handling functions */
#include <string.h>

/* Character checking and conversion functions */
#include <ctype.h>


/*--------------------------------------------------
 * Return Status Definitions
 *--------------------------------------------------*/

/* Operation completed successfully */
#define SUCCESS 0

/* Operation failed */
#define FAILURE -1

/* No element found */
#define NOELEMENT -2

/* Linked list is empty */
#define EMPTYLIST -3

/* Duplicate element detected */
#define REPEATED -4

/* Input file contains no readable characters */
#define FILE_EMPTY -5

/* Requested word is absent from the database */
#define NOT_PRESENT -6


/*--------------------------------------------------
 * General Constants
 *--------------------------------------------------*/

/* Number of buckets in the hash table:
 * 0-25 represent letters a-z, and 26 represents
 * words beginning with non-alphabetic characters.
 */
#define SIZE 27

/* General-purpose buffer size */
#define BUFF_SIZE 255

/* Maximum size of a word or filename buffer,
 * including the terminating null character.
 */
#define NAMELENGTH 20


/*--------------------------------------------------
 * Data Structure Definitions
 *--------------------------------------------------*/

/*
 * Structure: sub_node_t
 *
 * Purpose:
 * Stores information about a word in a particular file.
 *
 * Members:
 * f_name - Name of the file containing the word.
 * w_count - Number of occurrences of the word in that file.
 * link - Pointer to the next subnode.
 *
 * Each main node can have a linked list of subnodes,
 * one for each file containing that word.
 */
typedef struct sub_node
{
    char f_name[NAMELENGTH];
    int w_count;
    struct sub_node *link;
} sub_node_t;


/*
 * Structure: main_node_t
 *
 * Purpose:
 * Stores a unique word in the inverted search database.
 *
 * Members:
 * word - The word stored in the database.
 * link - Pointer to the next main node in the same bucket.
 * sub_link - Pointer to the first subnode containing file details.
 * f_count - Number of distinct files containing the word.
 *
 * Main nodes are organized into hash table buckets.
 */
typedef struct node
{
    char word[NAMELENGTH];
    struct node *link;
    sub_node_t *sub_link;
    int f_count;
} main_node_t;


/*
 * Structure: file_node_t
 *
 * Purpose:
 * Maintains a linked list of input filenames processed
 * or registered by the application.
 *
 * Members:
 * f_name - Name of the input file.
 * link - Pointer to the next file node.
 */
typedef struct file_node
{
    char f_name[NAMELENGTH];
    struct file_node *link;
} file_node_t;


/*--------------------------------------------------
 * File Validation and Filename List Operations
 *--------------------------------------------------*/

/*
 * Validates multiple input filenames and stores valid,
 * non-duplicate filenames in the file linked list.
 */
void validate_n_store_filenames(file_node_t **head, char *filenames[]);

/*
 * Checks the filename extension, file accessibility,
 * and whether the file is empty.
 */
int IsFileValid(char *filename);

/*
 * Creates a file node and inserts the filename at the
 * end of the file linked list.
 */
int store_filenames_to_list(char *f_name, file_node_t **head);

/*
 * Checks whether a filename already exists in the
 * file linked list.
 */
int is_duplicate_file(file_node_t *head, char *f_name);


/*--------------------------------------------------
 * Database Creation and Word Insertion
 *--------------------------------------------------*/

/*
 * Creates the inverted search database by processing
 * every filename in the file linked list.
 */
int create_DB(file_node_t *file_head, main_node_t *head[]);

/*
 * Reads a file, extracts words, and inserts them into
 * the inverted search database.
 */
int read_datafile(main_node_t *head[], char *f_name);

/*
 * Inserts a new main node at its appropriate sorted
 * position in a bucket's main linked list.
 */
int insert_at_last_main(main_node_t **head, char *word);

/*
 * Adds a filename to a word's subnode list or increments
 * the occurrence count if that filename already exists.
 */
int update_sub_node(main_node_t *main_node, char *fname);

/*
 * Inserts a word into the appropriate hash table bucket.
 * Updates existing word information or creates a new node.
 */
int insert_word(main_node_t *head[], char *word, char *fname);


/*--------------------------------------------------
 * Hash Table Operations
 *--------------------------------------------------*/

/*
 * Calculates the hash index based on the first character
 * of a word.
 */
int hash_function(char *word);

/*
 * Initializes all hash table bucket pointers to NULL.
 */
void initialize_hash_table(main_node_t *head[]);


/*--------------------------------------------------
 * Database Display
 *--------------------------------------------------*/

/*
 * Displays each stored word, its file count, and the
 * filenames and occurrence counts associated with it.
 */
int display_DB(main_node_t *head[]);


/*--------------------------------------------------
 * Database Update
 *--------------------------------------------------*/

/*
 * Validates and registers a new input file, then indexes
 * its words in the existing database.
 */
int update_existing_DB(file_node_t **file_head, main_node_t *head[]);


/*--------------------------------------------------
 * Database Search
 *--------------------------------------------------*/

/*
 * Searches for a word and displays its file information
 * if it exists in the database.
 */
int search_DB(main_node_t *head[], char *word);


/*--------------------------------------------------
 * Database Backup
 *--------------------------------------------------*/

/*
 * Saves the inverted search database to a text file.
 */
int save_DB(main_node_t *head[], char *fname);

#endif