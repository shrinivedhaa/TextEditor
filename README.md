# Text File Editor

## Introduction
This is a simple command-line text file editor implemented in C++. The program allows users to create, open, save, edit, search, and replace text in files.

## Features

1. **Create a New File**: Create a new text file with a specified name.
2. **Open an Existing File**: Open an existing text file and load its contents into the program.
3. **Save the Current File**: Save the current file's contents either to a new file or overwrite the currently open file.
4. **Edit the Current File**:
   - Insert text at the current cursor position or at the end of the file.
   - Delete specific text from a specified line.
   - Move the cursor to a specific line and position.
   - Display the current contents of the file.
5. **Search the Current File**: Search for a specific text query within the file and display the number of occurrences.
6. **Replace Text in the Current File**: Replace all occurrences of a specified text with another text.

## Usage

1. Compile the Program

    To compile the program, use a C++ compiler such as `g++`:

    ```sh
    g++ -o textfile_editor textfile_editor.cpp
    ```

2. Run the Program
    ```sh
    ./textfile_editor
    ```
