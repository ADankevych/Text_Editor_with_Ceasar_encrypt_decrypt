# Text Editor

## Overview

This project is a simple text editor implemented in C++, featuring basic text manipulation functions and file operations. It includes functionality for editing text, searching and replacing content, and basic encryption/decryption of text and files. The editor operates via a command-line interface (CLI), providing users with a menu of options for interacting with the text.

## Features

- Exit: Safely exit the text editor.
- Append Text: Add text to the end of the document.
- Start New Line: Begin a new line in the text.
- Save to File: Save the current text to a file.
- Load from File: Load text from a file into the editor.
- Print Text: Display the current text in the console.
- Insert Text: Insert text at a specified line and symbol index.
- Search: Find occurrences of a specific string in the text.
- Delete: Remove text by line and symbol index or a range.
- Copy: Copy a portion of text to the clipboard.
- Cut: Cut a portion of text, remove it from the document, and store it in the clipboard.
- Paste: Paste the text from the clipboard into the document.
- Undo: Revert 3 last change made to the text.
- Redo: Reapply 3 last undone change.
- Replace: Replace occurrences of a specific string with another string.
- Encrypt: Encrypt the current text using a basic algorithm.
- Decrypt: Decrypt previously encrypted text.
- Encrypt File: Encrypt the contents of a file.
- Decrypt File: Decrypt the contents of a file.

## Usage

The text editor provides a CLI with numbered options for each feature. Users can navigate through these options by entering the corresponding number.

Example:
```
0 - exit 
1 - Append text symbols to the end 
2 - Start the new line 
...
Enter your choice: 1
Enter the text to append: Hello, World!
```


### Installation and Running

Compile the Program: Use a C++ compiler to compile the source code.
```
g++ -o main main.cpp
```

Run the Program: Execute the compiled program from the command line.
```
./main
```

### File Operations

Saving: Saves the current text to a specified file, allowing users to persist in their work.  
Loading: Loads text from a specified file, enabling editing of existing documents.

### Text Editing Features

Search and Replace: Facilitates finding and replacing text, useful for quick edits.  
Clipboard Operations: Copy, cut, and paste functionalities mimic basic clipboard usage found in most text editors.

### Encryption/Decryption

Basic Encryption and Decryption: Allows users to secure their text by encrypting it. A corresponding decryption function ensures the text can be returned to its original form.

## Conclusion

This text editor serves as a simple, yet functional tool for basic text editing and file management. Its CLI-based approach makes it lightweight and easy to use for quick text manipulation tasks.
