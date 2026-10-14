# Inverted Search in C

## 📌 Overview

The **Inverted Search** project is a file-based search application implemented in C using **hash tables and linked lists**.

Instead of searching every file individually for a word, the program builds an inverted index that maps each unique word to the files in which it appears and the number of times it occurs in each file.

This project demonstrates dynamic memory allocation, pointers, file handling, string manipulation, linked lists, and hash table implementation in C.

## ✨ Features

- **Create Database** — Read input text files and build an inverted index.
- **Display Database** — Display stored words, hash indices, file counts, filenames, and word occurrence counts.
- **Update Database** — Add a new file and index its words without rebuilding the entire database.
- **Search Word** — Search for a word and display the files containing it and its occurrence count in each file.
- **Save Database** — Save the database to a text file for backup.
- **File Validation** — Check file extensions, accessibility, empty files, filename length, and duplicate filenames.

## 🛠️ Technologies Used

- **Programming Language:** C
- **Data Structures:** Hash Table, Singly Linked Lists
- **Concepts:** Pointers, Dynamic Memory Allocation, File Handling, String Processing
- **Compiler:** GCC

## 📂 Project Structure

```text
Inverted Search/
│
├── files/
│   ├── file1.txt
│   ├── file2.txt
│   ├── file3.txt
│   └── test.txt
│
├── inc/
│   └── main.h
│
└── src/
    ├── create_db.c
    ├── display_db.c
    ├── hash.c
    ├── indexing.c
    ├── InvertedSearch
    ├── main.c
    ├── readfile.c
    ├── save_db.c
    ├── search_db.c
    ├── update_db.c
    └── validate_files.c
```

## ⚙️ How It Works

### 1. Hash Table

The application uses a hash table containing **27 buckets**.

- Buckets `0–25` correspond to the letters `a–z`.
- Bucket `26` is used for words whose first character is not an English alphabetic letter, provided the word extraction logic passes them to the hash function.

The hash index for an alphabetic word is calculated using its first character.

```c
index = tolower(word[0]) - 'a';
```

### 2. Main Linked List

Each hash table bucket points to a linked list of main nodes.

Each main node stores:
- The unique word.
- The number of distinct files containing that word.
- A pointer to the linked list of file information.
- A pointer to the next main node.

### 3. Subnode Linked List

Each main node contains a subnode linked list. Each subnode stores:
- The filename containing the word.
- The number of occurrences of the word in that file.
- A pointer to the next subnode.

### Example

Suppose the input files contain:

**file1.txt**
```text
apple mango apple
```

**file2.txt**
```text
apple orange
```

The inverted index for `apple` would conceptually be:

```text
Word: apple
File count: 2

file1.txt → 2 occurrences
file2.txt → 1 occurrence
```

This structure makes it possible to retrieve file information for a word without scanning every input file during each search.

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Terminal or command-line interface
- Basic knowledge of C programming

### Compilation

From the project root directory, compile the source files:

```bash
gcc src/*.c -I inc -o InvertedSearch
```

If the `src` directory contains a separate `main()` function in every source file, compilation may fail. This command assumes that `main.c` is the only file defining `main()`.

### Run the Program

On Linux or WSL:

```bash
./InvertedSearch
```

On Windows, if compiled as an executable:

```powershell
.\InvertedSearch.exe
```

## 📖 How to Use

1. Run the program.
2. Provide the required input filenames when prompted.
3. Select an operation from the menu.
4. Create the database from the validated input files.
5. Display the database to inspect indexed words and file information.
6. Search for a word to find its associated files and occurrence counts.
7. Update the database by adding another valid file.
8. Save the database to a `.txt` backup file.

Follow the prompts displayed by the application for the exact input format and menu navigation.

## 🧠 Concepts Learned

- Implementing a hash table using an array of pointers.
- Handling collisions through linked lists.
- Creating and traversing singly linked lists.
- Using single and double pointers.
- Allocating and managing memory dynamically.
- Reading and writing files using standard C file I/O.
- Processing text character by character.
- Validating input files and preventing duplicate entries.
- Organizing a multi-file C project using header files and separate source files.

## 🔮 Possible Improvements

- Restore the database from a saved backup file.
- Improve error handling for file I/O operations.
- Support more flexible word tokenization and punctuation handling.
- Add case-insensitive filename duplicate detection where appropriate.
- Improve the backup format and validate its contents before restoration.

## 👨‍💻 Author

**Inverted Search — C Programming and Data Structures Project**

This project was developed to strengthen practical knowledge of C programming, pointers, linked lists, hashing, and file operations.
