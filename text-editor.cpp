#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct CursorPosition {
    int line = 0;
    int column = 0;
};

class TextEditor {
private:
    vector<string> content;
    stack<vector<string>> undoStack;
    stack<vector<string>> redoStack;
    CursorPosition cursorPosition;

public:
    void openFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File not found. Do you want to create a new file named '" << filename << "'? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                content.clear();
                saveFile(filename);  // Creates the new file
                cout << "New file created: " << filename << endl;
            }
            else {
                cerr << "Failed to open file!" << endl;
            }
            return;
        }
        content.clear();
        string line;
        while (getline(file, line)) {
            content.push_back(line);
        }
        file.close();
        cursorPosition = { 0, 0 };
        clearHistory();
    }


    void saveFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to save file!" << endl;
            return;
        }
        for (const string& line : content) {
            file << line << endl;
        }
        file.close();
    }

    void displayContent() const {
        for (size_t i = 0; i < content.size(); ++i) {
            cout << i + 1 << ": " << content[i] << endl;
        }
        cout << "\nCursor at line " << cursorPosition.line + 1
            << ", column " << cursorPosition.column + 1 << endl;
    }

    void insertLine(int lineNum, const string& text) {
        if (lineNum < 1 || lineNum > content.size() + 1) {
            cerr << "Invalid line number!" << endl;
            return;
        }
        saveStateForUndo();
        content.insert(content.begin() + (lineNum - 1), text);
        cursorPosition.line = lineNum - 1;
        cursorPosition.column = text.size();
        clearRedoHistory();
    }

    void deleteLine(int lineNum) {
        if (lineNum < 1 || lineNum > content.size()) {
            cerr << "Invalid line number!" << endl;
            return;
        }
        saveStateForUndo();
        content.erase(content.begin() + (lineNum - 1));
        cursorPosition.line = max(0, lineNum - 2);
        cursorPosition.column = 0;
        clearRedoHistory();
    }

    void searchAndReplace(const string& searchText, const string& replaceText) {
        saveStateForUndo();
        for (string& line : content) {
            size_t pos = line.find(searchText);
            while (pos != string::npos) {
                line.replace(pos, searchText.length(), replaceText);
                pos = line.find(searchText, pos + replaceText.length());
            }
        }
        clearRedoHistory();
    }

    void moveCursor(char direction) {
        switch (direction) {
        case 'w': // Move up
            cursorPosition.line = max(0, cursorPosition.line - 1);
            cursorPosition.column = min((int)content[cursorPosition.line].size(), cursorPosition.column);
            break;
        case 's': // Move down
            cursorPosition.line = min((int)content.size() - 1, cursorPosition.line + 1);
            cursorPosition.column = min((int)content[cursorPosition.line].size(), cursorPosition.column);
            break;
        case 'a': // Move left
            if (cursorPosition.column > 0) {
                cursorPosition.column--;
            }
            else if (cursorPosition.line > 0) {
                cursorPosition.line--;
                cursorPosition.column = content[cursorPosition.line].size();
            }
            break;
        case 'd': // Move right
            if (cursorPosition.column < content[cursorPosition.line].size()) {
                cursorPosition.column++;
            }
            else if (cursorPosition.line < content.size() - 1) {
                cursorPosition.line++;
                cursorPosition.column = 0;
            }
            break;
        }
    }

    void insertCharAtCursor(char c) {
        saveStateForUndo();
        content[cursorPosition.line].insert(cursorPosition.column, 1, c);
        cursorPosition.column++;
        clearRedoHistory();
    }

    void deleteCharAtCursor() {
        if (cursorPosition.column == 0 && cursorPosition.line == 0) {
            cerr << "Nothing to delete!" << endl;
            return;
        }
        saveStateForUndo();
        if (cursorPosition.column > 0) {
            content[cursorPosition.line].erase(cursorPosition.column - 1, 1);
            cursorPosition.column--;
        }
        else if (cursorPosition.line > 0) {
            cursorPosition.column = content[cursorPosition.line - 1].size();
            content[cursorPosition.line - 1] += content[cursorPosition.line];
            content.erase(content.begin() + cursorPosition.line);
            cursorPosition.line--;
        }
        clearRedoHistory();
    }

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(content);
            content = undoStack.top();
            undoStack.pop();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(content);
            content = redoStack.top();
            redoStack.pop();
        }
    }

private:
    void saveStateForUndo() {
        undoStack.push(content);
        if (undoStack.size() > 10) undoStack.pop(); // Limit the size of the undo stack
    }

    void clearRedoHistory() {
        while (!redoStack.empty()) redoStack.pop();
    }

    void clearHistory() {
        while (!undoStack.empty()) undoStack.pop();
        while (!redoStack.empty()) redoStack.pop();
    }
};

int main() {
    TextEditor editor;
    string filename;

    cout << "Enter the filename to open: ";
    cin >> filename;

    editor.openFile(filename);
    editor.displayContent();

    while (true) {
        cout << "\nCommands: \n1. Insert line \n2. Delete line \n3. Search and Replace \n4. Undo \n5. Redo \n6. Move cursor \n7. Insert character at cursor \n8. Delete character at cursor \n9. Save \n10. Quit\n";
        int command;
        cin >> command;

        if (command == 1) {
            int lineNum;
            string text;
            cout << "Enter line number to insert at: ";
            cin >> lineNum;
            cin.ignore();
            cout << "Enter text to insert: ";
            getline(cin, text);
            editor.insertLine(lineNum, text);
            editor.displayContent();
        }
        else if (command == 2) {
            int lineNum;
            cout << "Enter line number to delete: ";
            cin >> lineNum;
            editor.deleteLine(lineNum);
            editor.displayContent();
        }
        else if (command == 3) {
            string searchText, replaceText;
            cout << "Enter text to search: ";
            cin.ignore();
            getline(cin, searchText);
            cout << "Enter text to replace with: ";
            getline(cin, replaceText);
            editor.searchAndReplace(searchText, replaceText);
            editor.displayContent();
        }
        else if (command == 4) {
            editor.undo();
            editor.displayContent();
        }
        else if (command == 5) {
            editor.redo();
            editor.displayContent();
        }
        else if (command == 6) {
            char direction;
            cout << "Move cursor (w=up, s=down, a=left, d=right): ";
            cin >> direction;
            editor.moveCursor(direction);
            editor.displayContent();
        }
        else if (command == 7) {
            char c;
            cout << "Enter character to insert at cursor: ";
            cin >> c;
            editor.insertCharAtCursor(c);
            editor.displayContent();
        }
        else if (command == 8) {
            editor.deleteCharAtCursor();
            editor.displayContent();
        }
        else if (command == 9) {
            editor.saveFile(filename);
        }
        else if (command == 10) {
            break;
        }
        else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}



