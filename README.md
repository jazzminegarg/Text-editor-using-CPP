# TextEditor

## Overview
This `TextEditor` is a simple, command-line based text editor implemented in C++. It allows users to open, edit, and save text files with basic text manipulation features like inserting and deleting lines, searching and replacing text, moving the cursor, and undoing or redoing changes.

## Features
- **Open and Create Files:** Load an existing file or create a new file if it doesn't exist.
- **Insert Line:** Add a line of text at a specific line number.
- **Delete Line:** Remove a line from the document.
- **Search and Replace:** Find and replace specific text throughout the document.
- **Cursor Movement:** Navigate through the document using a cursor.
- **Insert Character at Cursor:** Insert a character at the current cursor position.
- **Delete Character at Cursor:** Delete a character at the current cursor position.
- **Undo/Redo:** Undo the last change or redo a previously undone change.
- **Save File:** Save the current document to a file.

## How to Use
1. **Compile the Program:**
   Compile the program using a C++ compiler. For example, with `g++`:
   ```
   g++ -o texteditor texteditor.cpp
   ```
   
2. **Run the Program:**
   ```
   ./texteditor
   ```

3. **Commands:**
   After starting the program, you can perform the following actions:

   - **1. Insert line:** Insert a new line of text at a specified line number.
   - **2. Delete line:** Delete a specific line from the document.
   - **3. Search and Replace:** Replace all instances of a specified text with another text.
   - **4. Undo:** Revert the last change.
   - **5. Redo:** Reapply a change that was undone.
   - **6. Move cursor:** Move the cursor up, down, left, or right within the text.
   - **7. Insert character at cursor:** Insert a character at the current cursor position.
   - **8. Delete character at cursor:** Delete the character at the current cursor position.
   - **9. Save:** Save the current state of the document to the file.
   - **10. Quit:** Exit the program.

## Example Usage
Upon running the program:
1. **Enter the filename to open:**
   - Input the name of the file you want to open. If the file doesn’t exist, you will be prompted to create a new one.
   
2. **Select a Command:**
   - After the file is opened, a menu with commands will be displayed. Input the corresponding number to execute a command.

3. **View Document:**
   - The contents of the file will be displayed with line numbers. The cursor's current position will also be shown.

4. **Perform Editing Operations:**
   - You can add, delete, or modify text using the provided commands. The editor will display the updated document after each command.

5. **Save Your Changes:**
   - Once you're done editing, use the save command to write the changes to the file.

6. **Exit the Program:**
   - Choose the quit command to close the editor.

## Notes
- The undo feature stores the last 10 changes for reversal.
- Moving the cursor respects the boundaries of the text, ensuring it doesn’t go out of bounds.
- The file is automatically created if it doesn't exist when you attempt to open it.

## Conclusion
This `TextEditor` provides a basic, yet functional, text editing experience through the command line, suitable for simple text manipulation tasks.
